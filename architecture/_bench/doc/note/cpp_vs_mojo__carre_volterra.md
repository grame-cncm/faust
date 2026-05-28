# Report: Mojo vs C++ low-level optimization gap

## Context

During the low-level inspection of `carre_volterra`, we compared the assembly generated from the C++ backend and the Mojo backend.

The goal was not to compare the whole benchmark framework, but to isolate the generated DSP `compute` code using the `inspect` architectures.

The main finding is that C++ automatically applies an optimization that Mojo currently does not reliably perform: it promotes small loop-carried DSP state fields to local temporaries/registers, uses them inside the hot loop, and writes them back to the DSP object only after the loop.

This transformation significantly reduces repeated memory loads and stores inside the per-sample loop.

## Main finding

The original Mojo generated code keeps accessing DSP fields directly inside the hot loop:

```mojo
for var i0 in range(S32(0), count):
    dsp.rec3[S32(0)] = (slow2) * ((dsp.rec3[S32(1)]) + ((slow4) * (temp7)))
    dsp.rec2[S32(0)] = (slow2) * ((dsp.rec2[S32(1)]) + ((slow1) * (dsp.rec3[S32(0)])))
    dsp.rec1[S32(0)] = (slow2) * ((dsp.rec1[S32(1)]) + ((slow1) * (dsp.rec2[S32(0)])))
    dsp.rec0[S32(0)] = (slow2) * ((dsp.rec0[S32(1)]) + ((slow1) * (dsp.rec1[S32(0)])))
    ...
    dsp.rec3[S32(1)] = dsp.rec3[S32(0)]
    dsp.rec2[S32(1)] = dsp.rec2[S32(0)]
    dsp.rec1[S32(1)] = dsp.rec1[S32(0)]
    dsp.rec0[S32(1)] = dsp.rec0[S32(0)]
```

This produces assembly with repeated memory traffic inside the hot loop:

```asm
str d29, [x9, #168]
ldr d25, [x9, #168]
str d25, [x9, #176]

str d26, [x9, #184]
ldr d25, [x9, #184]
str d25, [x9, #192]
```

The issue is not that the computation is wrong. The issue is that the generated code repeatedly writes and reloads small DSP state fields from memory even though they could remain in registers during the whole frame loop.

## What C++ does automatically

The C++ compiler recognizes that small recursive state arrays such as `rec0`, `rec1`, `rec2`, etc. can be represented as local loop-carried values.

Instead of writing every intermediate state update to memory inside the loop, C++ keeps those values in registers and flushes them back to the DSP object after the loop.

The C++ assembly shows this pattern clearly:

```asm
; inside the hot loop
fmadd s4, s6, s3, s31
fmul  s31, s1, s4

fmadd s4, s0, s31, s30
fmul  s30, s1, s4

fmadd s4, s0, s30, s29
fmul  s29, s1, s4
```

Then, after the loop:

```asm
stp s31, s31, [x8, #120]
stp s30, s30, [x8, #128]
stp s29, s29, [x8, #136]
stp s28, s28, [x8, #144]
```

This means that C++ effectively transforms memory-backed DSP state into register-backed temporaries during the hot loop.

## Manual Mojo transformation

To test the hypothesis, we manually rewrote the Mojo code by promoting selected DSP state fields to local variables before the loop.

### Before

```mojo
for var i0 in range(S32(0), count):
    dsp.rec3[S32(0)] = (slow2) * ((dsp.rec3[S32(1)]) + ((slow4) * (temp7)))
    dsp.rec2[S32(0)] = (slow2) * ((dsp.rec2[S32(1)]) + ((slow1) * (dsp.rec3[S32(0)])))
    dsp.rec1[S32(0)] = (slow2) * ((dsp.rec1[S32(1)]) + ((slow1) * (dsp.rec2[S32(0)])))
    dsp.rec0[S32(0)] = (slow2) * ((dsp.rec0[S32(1)]) + ((slow1) * (dsp.rec1[S32(0)])))
    ...
    dsp.rec3[S32(1)] = dsp.rec3[S32(0)]
    dsp.rec2[S32(1)] = dsp.rec2[S32(0)]
    dsp.rec1[S32(1)] = dsp.rec1[S32(0)]
    dsp.rec0[S32(1)] = dsp.rec0[S32(0)]
```

### After

```mojo
var rec3_0 = dsp.rec3[S32(0)]
var rec3_1 = dsp.rec3[S32(1)]
var rec2_0 = dsp.rec2[S32(0)]
var rec2_1 = dsp.rec2[S32(1)]
var rec1_0 = dsp.rec1[S32(0)]
var rec1_1 = dsp.rec1[S32(1)]
var rec0_0 = dsp.rec0[S32(0)]
var rec0_1 = dsp.rec0[S32(1)]

for var i0 in range(S32(0), count):
    rec3_0 = (slow2) * ((rec3_1) + ((slow4) * (temp7)))
    rec2_0 = (slow2) * ((rec2_1) + ((slow1) * (rec3_0)))
    rec1_0 = (slow2) * ((rec1_1) + ((slow1) * (rec2_0)))
    rec0_0 = (slow2) * ((rec0_1) + ((slow1) * (rec1_0)))
    ...
    rec3_1 = rec3_0
    rec2_1 = rec2_0
    rec1_1 = rec1_0
    rec0_1 = rec0_0

dsp.rec3[S32(0)] = rec3_0
dsp.rec3[S32(1)] = rec3_1
dsp.rec2[S32(0)] = rec2_0
dsp.rec2[S32(1)] = rec2_1
dsp.rec1[S32(0)] = rec1_0
dsp.rec1[S32(1)] = rec1_1
dsp.rec0[S32(0)] = rec0_0
dsp.rec0[S32(1)] = rec0_1
```

After this rewrite, the Mojo assembly changed in the desired direction. The small state fields were kept in registers inside the loop, then written back at the end:

```asm
; inside the hot loop, state is kept in registers
fmadd d4, d3, d2, d29
fmul  d29, d1, d4

fmadd d2, d0, d29, d28
fmul  d28, d1, d2

fmadd d2, d0, d28, d26
fmul  d26, d1, d2
```

Then, after the loop:

```asm
stp d29, d29, [x8, #168]
stp d28, d28, [x8, #184]
stp d26, d26, [x8, #200]
stp d5,  d5,  [x8, #216]
```

This confirms that the main issue is not the Mojo arithmetic itself, but the shape of the generated state updates.

## Why `noalias` was not enough

We also tested `as_noalias_ptr()` on input/output stream pointers.

This did not trigger the desired scalar replacement by itself. With `noalias` alone, the assembly still contained repeated loads and stores to DSP state fields inside the hot loop.

Therefore, the current issue is not primarily input/output aliasing. It is more likely related to the way Mojo lowers mutable DSP field accesses such as:

```mojo
dsp.rec3[S32(0)]
dsp.rec3[S32(1)]
```

The compiler does not currently promote this pattern as aggressively as Clang does for the equivalent C++ code.

`noalias` can still be useful as future hardening, especially for non-in-place architectures, but it is not the main fix for this case.

## Secondary finding: `pow`

Another difference remains around small integer powers.

C++ lowers expressions such as:

```cpp
pow(x, 2.0)
pow(x, 3.0)
```

to direct multiplications:

```asm
fmul s9, s31, s31
fmul s9, s31, s9
```

Mojo currently lowers the same kind of operation to a small generic exponentiation loop:

```asm
mov w2, #3
fmov d13, #1.00000000

LBB0_6:
    fmul d19, d13, d4
    tst w2, #0x1
    fcsel d13, d13, d19, eq
    fmul d4, d4, d4
    lsr w2, w2, #1
    cbnz w2, LBB0_6
```

This is another optimization gap, but it appears secondary compared to the repeated memory traffic caused by unpromoted DSP state fields.

## Proposed backend-side optimization

The first generator-side optimization should be local state promotion for loop-carried DSP fields.

A conservative first pass can target:

```text
rec*
iota*
```

Later, it can be extended to selected `vec*` fields if they are small and statically indexed.

The transformation should:

1. Scan the hot loop.
2. Detect promotable DSP fields.
3. Emit local loads at the end of the pre-hot-loop block.
4. Rewrite accesses inside the hot loop.
5. Emit final stores at the beginning of the post-hot-loop block.

The basic transformation is:

```text
dsp.recN[i] -> recN_i
```

with:

```mojo
var recN_i = dsp.recN[S32(i)]
```

before the loop, and:

```mojo
dsp.recN[S32(i)] = recN_i
```

after the loop.

## Important constraint

This should be done gradually.

Promoting too many fields can increase register pressure. If register pressure becomes too high, the compiler may start spilling values to the stack, partially undoing the benefit.

Suggested order:

```text
1. Promote rec* fields.
2. Promote iota* counters.
3. Promote vec* fields only when all accesses are statically indexed and the number of slots is small.
```

Dynamic ring buffers such as:

```mojo
dsp.vec3[(iota0 - i_slow19) & S32(4095)]
dsp.vec4[iota0 & S32(4095)]
```

should not be promoted.

## Conclusion

The main optimization gap observed in `carre_volterra` is local state promotion.

C++ automatically transforms small recursive DSP state arrays into register-backed temporaries inside the hot loop. Mojo currently does not do this reliably from the generated field-access form.

Manual promotion in the Mojo source significantly improves the generated assembly and makes it closer to the C++ output.

The next step is to implement this transformation in the Faust→Mojo backend, initially for `rec*` and `iota*`, then later for safely promotable `vec*` fields.
