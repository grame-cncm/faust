# C++ vs Mojo — Multibandfilter scalar precision comparison

## Scope

This note compares the scalar `multibandfilter` case across C++ and Mojo, focusing on single and double
precision.

Vec mode is not the focus here. The relevant scalar result is:

```
Mojo single > C++ double > C++ single > Mojo double
```

The central question is why C++ improves from single to double, while Mojo loses performance from single to
double.

The analysis is based on the generated AArch64 assembly and LLVM IR inspection for the scalar paths.

## AArch64 notation used in this note

AArch64 floating-point and SIMD registers can be viewed at different widths:

```
s0, s1, ...  scalar 32-bit floating-point view
d0, d1, ...  scalar 64-bit floating-point view
q0, q1, ...  128-bit vector/SIMD view
```

Therefore:

```
fmul  s0, s1, s2    `f32` scalar multiply
fmul  d0, d1, d2    `f64` scalar multiply
fmadd d0, d1, d2, d3    d0 = d1 * d2 + d3
fmsub d0, d1, d2, d3    d0 = d1 * d2 - d3
fnmsub d0, d1, d2, d3   d0 = d3 - d1 * d2
```

The `d` register name does not imply SIMD. It means the scalar 64-bit view of the floating-point register.

## Precision shape

The scalar single paths use `f32` arithmetic:

```
bl _tanf
bl ___exp10f
fmul  s...
fmadd s...
fmsub s...
```

The scalar double paths use `f64` arithmetic:

```
bl _tan
bl ___exp10
fmul  d...
fmadd d...
fmsub d...
```

The input/output layer remains `f32`. Therefore, in the double paths, conversions at the buffer boundary are
expected:

```
fcvt d..., s...    `f32` input/control value extended to `f64`
fcvt s..., d...    `f64` output value narrowed to `f32`
```

The scalar double path is therefore not a pure `f64` I/O path. It is an `f64` DSP compute path over `f32` audio
buffers.

## DSP structure

`multibandfilter` is a recursive filter cascade. Each sample passes through multiple recursive stages, and
each stage depends on state from previous samples.

The efficient scalar shape is:

```
load current sample
run the recursive cascade
update recurrence state
write output sample
```

For this DSP, the dominant question is not only the cost of `f32` versus `f64` arithmetic. The dominant question
is how much recurrence state remains in memory inside the loop.

## C++ single

In the C++ single path, both audio I/O and DSP state are float:

```
input/output buffers: float
recursive state:      float
```

In the LLVM IR, input/output accesses and recursive-state accesses use the same float TBAA class. This means
the type-based alias model does not strongly separate the audio buffers from the DSP state.

The loop still uses some SSA values and phi nodes, so C++ single is not completely unpromoted. However, the
loop retains visible memory-backed state rotation.

Representative assembly pattern:

```
str s24, [x19, #136]
...
str s0,  [x19, #148]
...
ldp s17, s0,  [x19, #136]
stp s17, s0,  [x19, #140]
ldp s1,  s16, [x19, #148]
stp s1,  s16, [x19, #152]
```

This means that part of the recurrence state is written, loaded, and rotated through DSP memory inside the hot
loop.

The result is:

```
C++ single:
  cheaper `f32` arithmetic;
  less type separation between I/O and state;
  more memory-backed state rotation inside the loop.
```

## C++ double

In the C++ double path, the audio I/O remains float, but the DSP recurrence state becomes double:

```
input/output buffers: float
recursive state:      double
```

The LLVM IR exposes this as different TBAA classes:

```
float I/O accesses:       !tbaa !17
double state accesses:    !tbaa !58
```

This gives LLVM a stronger basis for proving that float audio-buffer stores do not clobber double recursive
state.

The resulting loop shape is different. The state is loaded before the loop, carried through `phi double`
values inside the loop, and written back after the loop.

The corresponding assembly shape is state carried in `d` registers inside the loop:

```
fmov  d6,  d9
fmov  d24, d8
fmov  d5,  d31
...
fmadd d9,  ...
fmadd d8,  ...
fmadd d31, ...
```

and final state writeback after the loop:

```
stp d9,  d9,  [x19, #144]
stp d8,  d24, [x19, #176]
stp d6,  d8,  [x19, #160]
```

This is the main reason C++ double improves over C++ single. It pays the cost of `f64` arithmetic, but the loop
has a better recurrence-state form.

The result is:

```
C++ double:
  more expensive `f64` arithmetic;
  stronger type separation between `f32` I/O and `f64` state;
  more recurrence state carried as loop values;
  final state writeback after the loop.
```

## Mojo single

Mojo single is the strongest scalar case because its `f32` loop is compact.

The state is not fully promoted in the C++ double sense. However, the memory-backed state rotation is cheap in
single precision because two adjacent `f32` cells fit in one 64-bit move.

Representative pattern:

```
ldur d..., [x19, #...]
str  d..., [x19, #...]
```

In this context, the `d` register is not double arithmetic. It is a 64-bit move that can copy two adjacent `f32`
state cells.

The result is:

```
Mojo single:
  compact `f32` loop;
  relatively small frame;
  fused scalar operations;
  memory-backed state rotation, but cheap for adjacent `f32` cells.
```

This explains why Mojo single can outperform both C++ scalar paths.

## Mojo double

Mojo double uses `f64` arithmetic, but it does not obtain the same state-promotion shape as C++ double.

The generated Mojo source still expresses the recurrence state directly through DSP fields inside the loop:

```
dsp.rec9[0] = ...
dsp.rec8[0] = ...
...
dsp.rec9[2] = dsp.rec9[1]
dsp.rec9[1] = dsp.rec9[0]
```

This source shape lowers to memory-backed state updates. In the inspected Mojo IR, the DSP argument is marked
`noalias`, but the input/output stream arguments are not marked as `noalias`, and no TBAA metadata comparable
to the C++ IR is visible on the relevant load/store operations.

The important point is that `noalias` on the DSP pointer alone is not sufficient to force scalar replacement
of the `rec` arrays. The optimizer still has to transform field accesses such as:

```
dsp.recN[0]
dsp.recN[1]
dsp.recN[2]
```

into local loop-carried values and perform final writeback after the loop. The inspected Mojo double path does
not show that transformation at the same level as C++ double.

In double precision, memory-backed state rotation becomes much more expensive:

```
`f32`:
  one 64-bit move can cover two state cells

`f64`:
  one 64-bit move covers one state cell
```

Therefore Mojo double loses the main advantage that makes Mojo single strong.

The result is:

```
Mojo double:
  correct `f64` arithmetic;
  larger state cells;
  more expensive memory-backed rotation;
  no equivalent register-carried state form;
  lower throughput than Mojo single.
```

## Cross-comparison

Mojo single is faster than C++ single because the Mojo `f32` scalar loop is more compact. C++ single is limited
by memory-backed state rotation and less separation between float I/O and float state.

C++ double is faster than C++ single because the change to double state creates stronger type separation from
the `f32` I/O buffers. LLVM then obtains a better state form: loop-carried double values and writeback after the
loop.

Mojo double is slower than Mojo single because it pays the cost of `f64` state without obtaining the C++ double
state-promotion pattern. The `f32` compact-rotation advantage disappears.

C++ double is faster than Mojo double because C++ double turns more recurrence state into loop-carried values.
Mojo double keeps more of the recurrence state memory-backed.

Mojo single remains faster than C++ double because the `f32` loop is substantially cheaper and compact enough
that it outweighs the stronger state promotion seen in C++ double.

## Direct conclusion

The scalar `multibandfilter` comparison is primarily about recurrence-state handling.

The C++ single-to-double improvement is explained by the type separation between `f32` I/O and `f64` state. This
improves the aliasing model and enables a stronger scalar replacement of recursive state.

The Mojo single-to-double regression is explained by the opposite effect at the code-shape level. Mojo single
has a compact `f32` loop where memory-backed state rotation is still cheap. Mojo double increases state width
but does not obtain an equivalent register-carried recurrence form.

The relevant optimization gap is therefore not `f64` arithmetic itself. It is the transformation:

```
memory-backed rec arrays
-> local loop-carried recurrence values
-> final state writeback after the loop
```

C++ double obtains this transformation more effectively. Mojo double does not.
