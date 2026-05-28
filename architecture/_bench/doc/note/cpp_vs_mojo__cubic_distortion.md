# C++ vs Mojo — `cubic_distortion` low-level comparison

## Scope

This note compares the generated low-level code for `cubic_distortion` in `vec` mode, with focus on the 64-bit benchmark path.

The goal is not to judge the DSP algorithm itself, but to understand why the benchmark shows this pattern:

- C++ benefits from Faust `vec` mode.
- Mojo does not benefit from Faust `vec` mode in the same way.
- Mojo scalar can still be competitive, but Mojo vec pays extra cost without recovering enough performance through SIMD.

The main question is:

> Does the target backend actually produce vector instructions from Faust vec-mode code, or is the vec-shaped program mostly executed as scalar loops over temporary buffers?

## Executive summary

The comparison strongly suggests that C++/Clang currently has a much more effective implicit auto-vectorization path for Faust-generated `vec` code than the Mojo toolchain.

In the uploaded 64-bit vec ASM, neither backend appears to emit true packed `f64x2` arithmetic. There are no meaningful `fmul.2d`, `fmla.2d`, `fadd.2d`, or `fmls.2d` hot-loop patterns. However, C++ emits many packed `f32x4` NEON operations, while Mojo emits very little packed arithmetic at all.

A rough grep count over the provided ASM sections gives:

```text
C++ section:
  fmul.4s: 390
  fmla.4s: 351
  fmul.2d:   0
  fmla.2d:   0

Mojo section:
  fmul.4s:   0
  fmla.4s:   3
  fmul.2s:  13
  fmul.2d:   0
  fmla.2d:   0
```

So the main explanation is:

```text
C++ vec:
  Faust vec-mode block structure
  + Clang auto-vectorization
  = useful packed NEON work

Mojo vec:
  Faust vec-mode block structure
  + weak/no auto-vectorization of that structure
  = extra block/buffer overhead with little SIMD payoff
```

This is different from the custom hand-written `F64x2` experiment, where Mojo explicitly used `SIMD[f64, 2]` and the ASM did lower to real vector-double instructions such as `fmul.2d`, `fmla.2d`, and `fmls.2d`. The problem here is not that Mojo cannot generate SIMD at all. The problem is that Faust `vec` mode relies heavily on the target compiler recognizing vectorizable block loops, and Mojo currently does not seem to recognize this generated shape as effectively as Clang.

## Faust vec mode and the target compiler contract

Faust `vec` mode should not be understood as “the generated code is already guaranteed to execute as hardware SIMD.”

A more accurate model is:

```text
Faust vec mode rewrites the DSP into a block-oriented form.
That form exposes loops over arrays and temporary buffers.
The target compiler is then expected to optimize/vectorize those loops.
```

For C/C++, this is a reasonable strategy because Clang and LLVM have very mature heuristics for C-like loops over arrays. When the generated code contains loops such as:

```text
for i in block:
    tmp[i] = a * x[i] + b * y[i]
```

Clang can often recognize that iterations are independent and lower the loop to packed NEON operations.

For Mojo, this strategy currently appears weaker. The generated source may still be vec-shaped, but the optimizer does not necessarily turn the block loops into packed SIMD instructions. If that happens, the generated program keeps the costs of vec mode:

- temporary buffers;
- larger stack frames;
- multiple loops over intermediate arrays;
- copy/setup phases;
- more control flow;
- more load/store traffic;

without getting the expected SIMD throughput in return.

This explains why Mojo vec can be slower than Mojo scalar.

## How to read the AArch64 SIMD evidence

On Apple Silicon / AArch64, the relevant hardware vector width for normal NEON/Advanced SIMD is 128 bits.

For packed single precision:

```text
4 × f32 = 128 bits
```

The expected instruction forms are:

```asm
fmul.4s
fmla.4s
fadd.4s
fsub.4s
```

For packed double precision:

```text
2 × f64 = 128 bits
```

The expected instruction forms are:

```asm
fmul.2d
fmla.2d
fadd.2d
fsub.2d
fmls.2d
```

Scalar single-precision code uses `s` registers:

```asm
fmul  s...
fmadd s...
fmsub s...
```

Scalar double-precision code uses `d` registers:

```asm
fmul  d...
fmadd d...
fmsub d...
```

In the current `cubic_distortion` vec ASM, the important observation is that neither backend emits the expected packed f64 `.2d` arithmetic. The C++ backend emits a large amount of packed f32 `.4s` arithmetic, while Mojo emits mostly scalar `s` arithmetic and only a very small amount of packed arithmetic.

## Observation 1 — C++ vec is meaningfully auto-vectorized

The C++ ASM contains many operations of this form:

```asm
fmul.4s v..., v..., v...[0]
fmla.4s v..., v..., v...[0]
```

This is the signature of vectorized block arithmetic over four `f32` lanes.

Even though the symbol is the double-stream compute variant, much of the internal generated computation appears to be narrowed to single precision. That is visible through many scalar float math calls and scalar `s`-register operations, for example:

```asm
fcvt s0, d0
bl _sinf
bl _cosf
bl ___exp10f
```

So this is not “clean f64 SIMD.” It is more subtle:

```text
C++ double path:
  double I/O / double-facing compute symbol
  but many internal computations are f32-shaped
  and Clang vectorizes many block loops as f32x4 NEON
```

This is still useful for performance. The Faust vec strategy creates many loops over block buffers, and Clang manages to convert many of those loops into packed f32 vector instructions. Therefore C++ pays the vec-mode restructuring cost, but it also recovers significant throughput through auto-vectorization.

## Observation 2 — Mojo vec is mostly scalarized

The Mojo section does not show the same level of packed SIMD arithmetic.

The dominant pattern is still scalar single-precision operations:

```asm
fmul  s...
fmadd s...
fmsub s...
fnmsub s...
ldr   s...
str   s...
```

There are a few vector instructions, but far too few to characterize the generated code as meaningfully vectorized. The rough count was:

```text
Mojo:
  fmla.4s: 3
  fmul.2s: 13
  fmul.2d / fmla.2d: 0
```

This suggests that Mojo is mostly lowering the Faust vec-mode program literally:

```text
loop over block elements
load scalar temporary
compute scalar operation
store scalar temporary
repeat
```

The result is a poor trade-off:

```text
Mojo scalar:
  one direct scalar DSP loop

Mojo vec:
  block-oriented vec-mode structure
  temporary buffers
  more control/memory traffic
  mostly scalar arithmetic anyway
```

That is why Mojo vec can be slower than Mojo scalar.

## Observation 3 — this is not primarily a `pow` / `exp10` issue

There is a real math-lowering difference between C++ and Mojo.

C++/Clang recognizes and lowers some math patterns better. In this ASM we see specialized libm calls such as:

```asm
___exp10f
_exp2f
_expf
_sinf
_cosf
_log10f
```

Mojo still has generic calls such as:

```asm
std::math::math::pow[..., SIMD,dtype=f32,size=1]
```

For the Mojo backend, replacing `pow(10.0, x)` with a more direct `exp10` or an `exp2`-derived implementation may help. Similarly, the backend can avoid unnecessary generic math paths where the Faust expression is known.

However, this is probably not the main cause of the vec-mode gap.

The bigger issue is structural:

```text
C++ emits hundreds of packed vector arithmetic instructions.
Mojo emits almost none.
```

The missing auto-vectorization dominates the diagnosis. The `pow` / `exp10` issue is a secondary math-canonicalization problem.

## Observation 4 — `pow_unrolled` is not the problem

The uploaded ASM does not show calls to `pow_unrolled` in the Mojo section.

That suggests the compile-time exponent unrolling path is not remaining as a runtime function call. It is either inlined or optimized away as intended.

The remaining visible `pow` calls are generic `std.math.pow` calls, likely corresponding to expressions of the form:

```text
pow(10.0, x)
```

rather than to fixed unsigned integer exponent cases such as:

```text
pow_unrolled[2](x)
```

So the conclusion is:

```text
pow_unrolled appears fine.
The remaining math issue is generic pow, not unrolled integer powers.
```

## Why C++ wins in this case

C++ wins because the generated C++ source shape is more successfully optimized by Clang.

The Faust vec-mode code gives the compiler many loops over arrays. Clang recognizes enough of those loops as vectorizable and emits packed NEON operations. This turns some of the vec-mode temporary-buffer work into actual SIMD throughput.

Mojo receives a similar block/vector-shaped program, but the Mojo toolchain does not seem to auto-vectorize those loops effectively. As a result, Mojo keeps the temporary buffers and block scheduling overhead, while executing most of the arithmetic scalar.

This gives the core performance model:

```text
C++ vec performance:
  overhead of Faust vec mode
  - recovered by auto-vectorized f32x4 loops

Mojo vec performance:
  overhead of Faust vec mode
  - little recovered SIMD throughput
```

So the difference is not generic “C++ is faster.” It is more precise:

```text
Clang is currently better at auto-vectorizing Faust-generated vec-mode code than Mojo.
```

## Relation with the previous `multibandfilter` experiment

This result should be connected carefully to the previous `multibandfilter` findings.

In `multibandfilter`, Faust vec mode was a bad match because the DSP is a recursive filter cascade. The vec mode generated many block-stage loops and temporary buffers, while the scalar version kept a more direct recurrence structure. For recursive/IIR-style DSPs, vectorizing across time is intrinsically hard because each sample depends on previous state.

In `cubic_distortion`, the issue is different. The DSP is more amenable to block/vector processing, so Faust vec mode should have a better chance. C++ confirms this: Clang extracts useful SIMD. Mojo does not, which points more directly to missing or weak auto-vectorization of the generated vec shape.

So the two cases show two different failure modes:

```text
multibandfilter:
  Faust vec mode is structurally a poor fit for recursive cascades.

cubic_distortion:
  Faust vec mode exposes vectorization opportunities,
  but Mojo does not exploit them as effectively as Clang.
```

## Relation with the explicit Mojo SIMD experiment

The hand-written `F64x2` experiment is important because it proves that Mojo can lower explicit SIMD code to real vector instructions.

When the code used Mojo’s SIMD type system directly, the ASM showed real packed f64 operations such as:

```asm
fmul.2d
fmla.2d
fmls.2d
```

Therefore the conclusion is not:

```text
Mojo cannot generate SIMD.
```

The correct conclusion is:

```text
Mojo can generate SIMD when the source explicitly uses SIMD types.
Mojo currently does not auto-vectorize Faust vec-mode block loops as effectively as Clang.
```

This is a crucial distinction for backend strategy.

## Backend implications

For the Mojo backend, there are three separate optimization directions.

### 1. Do not rely too heavily on Faust vec mode yet

For now, Faust `-vec` should not be assumed to produce faster Mojo code.

The benchmark evidence suggests that Mojo may pay the block-mode cost without obtaining the same auto-vectorization benefit as C++.

### 2. Prefer scalar state promotion for recursive DSPs

For recursive/state-heavy DSPs, the best optimization direction is probably not Faust vec mode. It is scalar replacement / state promotion:

```text
load small state arrays into locals before the sample loop
use local scalar state inside the loop
flush final state back after the loop
```

This is especially relevant for cases such as `carre_volterra` and `multibandfilter`.

### 3. Use explicit Mojo SIMD for controlled SIMD experiments

When the DSP structure actually has independent lanes, Mojo’s explicit SIMD type system is promising.

Good use cases:

```text
stereo with independent channels
batched mono instances
polyphonic voices
parallel branches
```

Bad use cases:

```text
single mono IIR stream across consecutive samples
```

For explicit SIMD, the backend should generate types such as:

```text
SIMD[f32, 4]
SIMD[f64, 2]
```

and keep state directly in SIMD values, rather than relying on temporary block arrays and later auto-vectorization.

### 4. Add targeted math canonicalization later

Math canonicalization is still useful, but secondary for this case.

Potential improvements:

```text
pow(10.0, x) -> exp10(x), if available
pow(10.0, x) -> exp2(log2(10.0) * x), if appropriate and numerically acceptable
fixed integer exponent -> pow_unrolled[N](x)
```

The last point already appears to be working: `pow_unrolled` does not remain visible as a runtime call in the current ASM.

## Conclusions

The `cubic_distortion` 64-bit vec comparison shows that C++ benefits from Faust vec mode because Clang successfully auto-vectorizes many of the generated block loops into packed f32 NEON instructions.

Mojo does not show the same behavior. Its vec-mode output is mostly scalarized, with only a very small number of packed arithmetic instructions. Therefore Mojo vec pays the cost of Faust’s block-oriented transformation without receiving enough SIMD benefit.

The main conclusion is:

```text
C++/Clang currently has stronger implicit vectorization for Faust vec-mode code than Mojo.
```

The secondary conclusion is:

```text
Mojo should not rely on Faust vec mode alone for performance.
For Mojo, explicit SIMD generation and scalar state-promotion passes are likely more important than generic vec-mode lowering.
```

The practical backend direction is therefore:

```text
For recursive DSPs:
  implement/promote scalar state replacement.

For feed-forward or independent-lane DSPs:
  investigate explicit Mojo SIMD codegen.

For Faust vec mode:
  treat it as experimental until Mojo auto-vectorization improves or until the generated Mojo shape becomes more vectorizer-friendly.
```
