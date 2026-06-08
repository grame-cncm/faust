# C++ vs Mojo — Carre Volterra scalar state-promotion comparison

## Scope

This note compares the generated low-level code for `carre_volterra`, focusing on the scalar C++ and scalar
Mojo benchmark paths.

The benchmark result is the starting point: C++ scalar is the fastest version, while both C++ vec and Mojo vec
slow down. This means that the main question is not why vec mode fails. For this DSP, vec mode is already a
poor fit for both backends.

The relevant question is narrower:

```
If vec mode is bad for both backends, why is Mojo scalar still slower than C++ scalar?
```

The low-level inspection points to one main difference: C++ promotes small recursive DSP state to local
register-carried values inside the hot loop, while the original Mojo output keeps accessing DSP fields
directly from memory.

## Benchmark result to explain

For `carre_volterra`, the fastest observed configuration is C++ scalar.

Both backends slow down in vec mode. That strongly suggests that this DSP is not a good case for the Faust
vec-mode transformation. The program is recurrence-heavy and state-heavy, so splitting the computation into
block loops does not give a useful vectorization path.

Therefore, the direct comparison should be:

```
C++ scalar vs Mojo scalar
```

The remaining gap is about scalar code quality, not about missing vectorization. The question is why the Mojo
scalar path is still around 1.2x slower than the C++ scalar path.

## Why vec mode is not the main question

Vec mode is useful only when the generated block structure can be converted into efficient packed single
instruction, multiple data (SIMD) arithmetic.

For `carre_volterra`, both C++ and Mojo get slower in vec mode. This is different from `cubic_distortion`,
where C++ benefits from vec mode and Mojo does not.

Here, the shared slowdown means that the DSP shape itself is not favorable to the vec-mode transformation. The
recurrence structure makes consecutive samples dependent on previous state, so the optimizer has fewer
independent operations to pack together.

This report therefore focuses on the scalar path.

## Scalar comparison focus

The scalar gap comes from how the two backends handle small loop-carried DSP state.

C++ scalar effectively treats state arrays such as `rec0`, `rec1`, `rec2`, and `rec3` as local values inside
the hot loop. The loop updates registers, then writes the final state back to the DSP object after the loop.

The original Mojo scalar output does not do this reliably. It keeps using expressions such as:

```
dsp.rec3[S32(0)]
dsp.rec3[S32(1)]
dsp.rec2[S32(0)]
dsp.rec2[S32(1)]
```

inside the hot loop.

This creates repeated loads and stores to memory-backed DSP fields. The computation is correct, but the
generated code puts more pressure on the stack and memory system than the C++ output.

## Mojo scalar state-access pattern

The original Mojo generated code updates DSP fields directly inside the hot loop:

```
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

This source shape encourages the compiler to keep materializing field updates as memory operations. The
assembly shows repeated writes and reloads inside the hot loop:

```
str d29, [x9, #168]
ldr d25, [x9, #168]
str d25, [x9, #176]

str d26, [x9, #184]
ldr d25, [x9, #184]
str d25, [x9, #192]
```

The important point is the pattern: Mojo writes a state value to the DSP object, reads it back shortly after,
then writes the shifted state slot. These values are small and statically indexed, so they are good candidates
for register-backed local variables.

## C++ scalar assembly pattern

The C++ compiler performs this promotion automatically.

Inside the hot loop, the recursive state is carried through registers:

```
fmadd s4, s6, s3, s31
fmul  s31, s1, s4

fmadd s4, s0, s31, s30
fmul  s30, s1, s4

fmadd s4, s0, s30, s29
fmul  s29, s1, s4
```

The DSP object is updated after the loop:

```
stp s31, s31, [x8, #120]
stp s30, s30, [x8, #128]
stp s29, s29, [x8, #136]
stp s28, s28, [x8, #144]
```

This is the key difference. C++ does not repeatedly store and reload the small recursive state fields inside
the loop. It keeps them live as local loop-carried values and flushes them at the end.

That directly reduces load/store traffic in the hot path.

## Manual Mojo promotion check

To test the diagnosis, the Mojo source was manually rewritten by loading selected DSP state fields into local
variables before the loop.

Before the loop:

```
var rec3_0 = dsp.rec3[S32(0)]
var rec3_1 = dsp.rec3[S32(1)]
var rec2_0 = dsp.rec2[S32(0)]
var rec2_1 = dsp.rec2[S32(1)]
var rec1_0 = dsp.rec1[S32(0)]
var rec1_1 = dsp.rec1[S32(1)]
var rec0_0 = dsp.rec0[S32(0)]
var rec0_1 = dsp.rec0[S32(1)]
```

Inside the loop:

```
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
```

After the loop:

```
dsp.rec3[S32(0)] = rec3_0
dsp.rec3[S32(1)] = rec3_1
dsp.rec2[S32(0)] = rec2_0
dsp.rec2[S32(1)] = rec2_1
dsp.rec1[S32(0)] = rec1_0
dsp.rec1[S32(1)] = rec1_1
dsp.rec0[S32(0)] = rec0_0
dsp.rec0[S32(1)] = rec0_1
```

After this rewrite, the Mojo assembly changed in the expected direction. The state updates became
register-carried inside the hot loop:

```
fmadd d4, d3, d2, d29
fmul  d29, d1, d4

fmadd d2, d0, d29, d28
fmul  d28, d1, d2

fmadd d2, d0, d28, d26
fmul  d26, d1, d2
```

Then the final state was written back after the loop:

```
stp d29, d29, [x8, #168]
stp d28, d28, [x8, #184]
stp d26, d26, [x8, #200]
stp d5,  d5,  [x8, #216]
```

This confirms the diagnosis: the main scalar gap is not the arithmetic expression itself, but the generated
state-access shape.

## Why noalias is not the main issue

The `as_noalias_ptr()` test on input and output stream pointers did not trigger the same improvement.

With noalias alone, the assembly still contained repeated loads and stores to DSP state fields inside the hot
loop. That means the main problem is not input/output aliasing.

The relevant issue is the mutable DSP field-access pattern itself. Mojo does not currently promote these small
statically indexed state fields as aggressively as Clang does for the equivalent C++ code.

## Final comparison

The `carre_volterra` benchmark should be read as a scalar state-promotion problem.

Vec mode is not the main explanation, because both C++ and Mojo slow down in vec mode. This indicates that the
DSP shape is not suitable for this transformation.

The meaningful gap is scalar C++ versus scalar Mojo. C++ keeps small recursive state in registers during the
hot loop and writes it back after the loop. The original Mojo output keeps touching memory-backed DSP fields
inside the loop, producing extra load/store traffic and higher pressure on the stack and memory system.

Manual promotion in the Mojo source makes the assembly move toward the C++ pattern. This makes local state
promotion the central explanation for the observed scalar gap.
