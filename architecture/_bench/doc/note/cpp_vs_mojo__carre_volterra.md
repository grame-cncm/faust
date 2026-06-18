# C++ vs Mojo - Carre Volterra scalar state promotion

## Scope

This note compares the generated low-level code for `carre_volterra`, focusing on the scalar C++ and scalar
Mojo benchmark paths.

The relevant result is that C++ scalar double is much faster than the other configurations, while Mojo scalar
single and Mojo scalar double are close to each other. Vec mode is slower for both backends, so the interesting
comparison is scalar C++ versus scalar Mojo.
<!-- TODO: add note about vec mode and non parallelizeable algorithm -->

The low-level inspection points to one main difference: C++ scalar double promotes recursive DSP state into
loop-carried register values, while Mojo keeps more of that state memory-backed inside the hot loop.

## Benchmark result

Observed throughput:

```text
configuration                 throughput
------------------------------------------------
C++  scalar single             134.3 Mframes/s
C++  scalar double             220.4 Mframes/s
C++  vec    single             115.6 Mframes/s
C++  vec    double             105.9 Mframes/s
Mojo scalar single             129.7 Mframes/s
Mojo scalar double             128.2 Mframes/s
Mojo vec    single              72.2 Mframes/s
Mojo vec    double              68.6 Mframes/s
```

The scalar single comparison is close:

```text
Mojo scalar single / C++ scalar single = 129.7 / 134.3 = 96.6%
```

The scalar double comparison is the large gap:

```text
Mojo scalar double / C++ scalar double = 128.2 / 220.4 = 58.2%
C++ scalar double is about 1.72x faster than Mojo scalar double
```

This is not a generic scalar-codegen failure. The standout result is specifically C++ scalar double.

## State-promotion model

The core transformation can be shown without the full `carre_volterra` code.

Memory-backed shape:

```text
compute(dsp, count, inputs, outputs):
    input0  = inputs[0]
    output0 = outputs[0]
    for i in 0 .. count:
        x = load input0[i]
        rec_00 = load dsp.rec0[0]
        rec_01 = load dsp.rec0[1]
        y = 0.5 * x + 0.3 * rec_00 - 0.1 * rec_01
        store dsp.rec0[1], rec_00
        store dsp.rec0[0], y
        store output0[i], y
```

Register-carried shape:

```text
compute(dsp, count, inputs, outputs):
    input0  = inputs[0]
    output0 = outputs[0]
    rec_00 = load dsp.rec0[0]
    rec_01 = load dsp.rec0[1]
    for i in 0 .. count:
        x = load input0[i]
        y = 0.5 * x + 0.3 * rec_00 - 0.1 * rec_01
        rec_01 = rec_00
        rec_00 = y
        store output0[i], y
    store dsp.rec0[0], rec_00
    store dsp.rec0[1], rec_01
```

The arithmetic is unchanged. The optimized shape loads the initial recurrence state once, carries it through
the loop as scalar values, and writes the final state back once after the loop.

## Instruction counts

Hot-loop instruction counts:

```text
case              instructions   memory ops   FP core ops
---------------------------------------------------------
C++ single hot          114          45           56
C++ double hot           83           7           56
Mojo single hot         123          52           59
Mojo double hot         126          53           59
```

Whole inspected section counts:

```text
case              instructions   memory ops   FP core ops
---------------------------------------------------------
C++ single              336         116          136
C++ double              303          58          136
Mojo single             201          71           80
Mojo double             214          76           80
```

The hot-loop counts are the relevant ones. C++ scalar double does not win by doing less core DSP arithmetic:
C++ scalar single and C++ scalar double both have 56 counted FP core operations in the hot loop. The major
difference is memory traffic:

```text
C++ single hot memory ops: 45
C++ double hot memory ops:  7
Mojo double hot memory ops: 53
```

C++ scalar double eliminates almost all recurrent-state load/store traffic from the hot loop. Mojo scalar
double does not.

## C++ scalar double

The C++ scalar double loop carries recurrence state directly in floating-point registers:

```asm
fmadd d4, d7, d3, d31
fmul  d31, d1, d4
fmadd d4, d0, d31, d30
fmul  d30, d1, d4
fmadd d4, d0, d30, d29
fmul  d29, d1, d4
fmadd d4, d0, d29, d28
fmul  d28, d1, d4
```

The final state is written back after the loop:

```asm
stp d31, d31, [x8, #160]
stp d30, d30, [x8, #176]
stp d29, d29, [x8, #192]
stp d28, d28, [x8, #208]
```

This is the desirable shape: initial state loads before the loop, recurrence updates in registers, final state
stores after the loop.

## C++ scalar single

C++ scalar single is partially promoted. The LLVM IR contains loop-carried `phi float` values:

```llvm
%222 = phi float ...
%223 = phi float ...
%224 = phi float ...
...
%232 = phi float ...
```

However, the f32 path does not complete the same store-sinking transformation. The hot loop still contains
state stores and state rotations:

```asm
str s28, [x8, #92]
str s29, [x8, #100]
str s30, [x8, #108]
str s31, [x8, #116]
...
ldr s28, [x8, #92]
str s28, [x8, #96]
ldr s29, [x8, #100]
str s29, [x8, #104]
```

The IR has the same partial-promotion pattern:

```llvm
store float %285, ptr %84
...
%326 = load float, ptr %84
store float %326, ptr %85
```

Thus C++ scalar single carries part of the state through SSA values, but it does not reach the cleaner
register-carried shape of C++ scalar double.

## Alias hypothesis

The likely reason for the f64/f32 difference is alias analysis.

In the double-precision DSP case, the external output buffer is still `float`, while the internal recurrence
state is `double`:

```text
output0[i]     -> float
dsp.rec*       -> double
```

Under normal C++ strict-aliasing rules, a write through a `float*` cannot legally modify a `double` object. A
program could force a `float*` to point into the storage of a `double`, but writing the `double` object through
that `float*` would not be a valid typed access to the object. This gives LLVM a strong type-based aliasing
argument:

```text
store float output0[i]
cannot modify
load/store double dsp.rec*
```

Once that non-interference is known, the optimizer can legally load the double recurrence state before the
loop, carry it through phi/register values, and sink the final double stores after the loop.

In the single-precision DSP case, both the output buffer and the DSP recurrence state are `float`:

```text
output0[i]     -> float
dsp.rec*       -> float
```

A `float*` output channel can legally point to any `float` object, including a `float` field inside the DSP
object. For example:

```text
output0 = &dsp.rec0[0]
```

With that aliasing shape, this original order:

```text
loop:
    store dsp.rec0[0], y
    store output0[i], z
```

is not necessarily equivalent to:

```text
loop:
    store output0[i], z
after loop:
    store dsp.rec0[0], final_y
```

If `output0` aliases `dsp.rec0`, moving the DSP-state store after the loop can change observable behavior:
which value is written, which value is later read, and which write is the final visible write.

The final IR/assembly does not prove the exact LLVM pass sequence. It shows the resulting shape:

```text
double:
  initial state loads
  phi double values in the loop
  final state stores after the loop

single:
  phi float values exist
  state stores/reloads remain inside the loop
```

The observed result is consistent with memory promotion and store sinking being enabled by stronger alias
information in the double case.

## Mojo scalar double

Mojo scalar double keeps recurrent DSP state memory-backed in the hot loop:

```asm
fmadd d28, d3, d24, d28
fmul  d28, d1, d28
str   d28, [x9, #152]
fmadd d27, d0, d28, d27
fmul  d27, d1, d27
str   d27, [x9, #168]
fmadd d26, d0, d27, d26
fmul  d26, d1, d26
str   d26, [x9, #184]
```

Later in the same loop, the same state is loaded and shifted through the DSP object:

```asm
ldr d28, [x9, #152]
str d28, [x9, #160]
ldr d27, [x9, #168]
str d27, [x9, #176]
ldr d26, [x9, #184]
str d26, [x9, #192]
```

This is the memory-backed shape from the small model. It is correct, but it creates extra hot-loop load/store
traffic.

The safer conclusion is not that Mojo lacks LLVM optimizations. The generated Mojo IR does not expose the same
promotion opportunity, or does not give LLVM enough alias and memory-shape information to apply the same state
promotion and store sinking here.

## Optimization terminology

The report-level name is:

```text
loop-carried state promotion
```

The compiler-specific breakdown is:

```text
SROA / scalar replacement:
  split aggregate or field-backed state into independent scalar values

memory promotion / mem2reg:
  represent promotable memory locations as SSA values

LICM-style memory promotion:
  hoist the initial load out of the loop and sink the final store after the loop when the memory location is
  known well enough

store sinking:
  delay the final state writeback until the loop exit

register allocation:
  keep the resulting scalar recurrence values in floating-point registers
```

Plain loop-invariant code motion is not precise enough by itself, because the recurrence values are not
invariant. They change every sample. What gets moved is the memory access pattern:

```text
load state before the loop
carry changing state in registers inside the loop
store final state after the loop
```

The precise wording is therefore:

```text
scalar replacement / memory promotion of loop-carried DSP state, with preheader load hoisting and exit-block
store sinking
```

## Direct comparison

The scalar double gap is mainly a state-promotion difference.

C++ scalar double exposes a shape where the optimizer can keep recursive DSP state in registers across the hot
loop. Mojo scalar double materializes many recurrence updates through the DSP object inside the loop.

```text
C++ scalar double:
  register-carried recurrence state
  7 hot-loop memory ops in the counted loop
  220.4 Mframes/s

Mojo scalar double:
  memory-backed recurrence state
  53 hot-loop memory ops in the counted loop
  128.2 Mframes/s
```

The main backend target is to expose recursive state in a form that LLVM can promote:

```text
load rec_00, rec_01, ... before the sample loop
update rec_00, rec_01, ... as local scalar values inside the loop
write dsp.rec* once after the loop
```

The C++ scalar double result suggests why this is legal there: the internal `double` state is easier to prove
independent from the external `float` output buffer. The C++ scalar single result shows the opposite limit:
when state and output are both `float`, LLVM becomes more conservative and keeps more memory traffic in the
loop.
