# C++ vs Mojo — Cubic distortion vec-mode comparison

## Scope

This note compares the generated low-level code for `cubic_distortion` in Faust vec mode, focusing on the
64-bit benchmark path.

The benchmark result is the starting point: in vec mode, C++ improves its throughput, while Mojo reduces it.
The goal is to explain this difference from the generated source shape and the resulting AArch64 assembly.

The point is not to evaluate the DSP algorithm itself. The point is to understand why the same Faust vec-mode
transformation is profitable for C++, but becomes a cost for Mojo.

## Benchmark result to explain

For `cubic_distortion`, the measured C++ vec-mode throughput is higher than the C++ scalar throughput. The
block-oriented Faust transformation is therefore profitable for the C++ backend.

Mojo shows the opposite pattern. The measured Mojo vec-mode throughput is lower than the Mojo scalar
throughput. In this case, vec mode adds block structure and memory traffic, but does not recover enough
performance through vector execution.

The central question is:

```
Why does Faust vec mode help C++, but hurt Mojo?
```

The assembly points to a backend-level difference: Clang extracts substantial packed arithmetic from the
vec-mode shape, while Mojo mostly preserves the structure as scalar work.

## Faust vec-mode context

Faust vec mode rewrites the DSP into block-oriented code. For this report, the relevant point is only that the
generated program is split into loops over temporary buffers, instead of being one direct scalar sample loop.

A simplified scalar shape is:

```
for (int i = 0; i < count; i++) {
    float x = input[i];
    float y = x - drive * x * x * x;
    output[i] = y;
}
```

A simplified vec-mode shape is:

```
for (int i = 0; i < count; i++) {
    tmp0[i] = input[i] * gain;
}

for (int i = 0; i < count; i++) {
    tmp1[i] = tmp0[i] * tmp0[i];
}

for (int i = 0; i < count; i++) {
    output[i] = tmp0[i] - drive * tmp1[i] * tmp0[i];
}
```

This transformation is useful only if the target compiler turns enough of these block loops into packed single
instruction, multiple data (SIMD) arithmetic.

## C++ generated shape

The C++ backend emits regular C-like loops over contiguous arrays.

A representative shape is:

```
for (int i = 0; i < vsize; i++) {
    fTemp0[i] = fConst0 * input0[i];
}
```

This is a familiar pattern for Clang's loop optimizer. If the compiler proves that iterations are independent
enough, it can pack multiple scalar iterations into one NEON (Advanced SIMD) instruction.

C++ still pays the cost of Faust vec mode, but much of that cost is recovered by vector execution.

## Mojo generated shape

The Mojo backend receives the same general vec-mode structure: block loops, temporary buffers, and staged
computation.

The problem is that the generated Mojo code is not auto-vectorized with the same effectiveness. The assembly
suggests that Mojo mostly executes the written block loops literally, with repeated scalar loads, scalar
arithmetic, and scalar stores over temporary buffers.

So the cost is not just "more loops". The cost is continuous memory traffic across the vec-mode temporaries,
with strong pressure on the stack and memory system, but without enough packed arithmetic to compensate.

## Assembly evidence

The assembly is the main evidence because it shows whether the generated vec-mode code actually became
hardware SIMD.

On Apple Silicon AArch64, normal NEON SIMD uses 128-bit vector registers. For packed single precision, the
expected pattern is four 32-bit floats per vector:

```
fmul.4s v0, v1, v2
fmla.4s v0, v1, v2
fadd.4s v0, v1, v2
fsub.4s v0, v1, v2
```

For packed double precision, the expected pattern is two 64-bit floats per vector:

```
fmul.2d v0, v1, v2
fmla.2d v0, v1, v2
fadd.2d v0, v1, v2
fsub.2d v0, v1, v2
fmls.2d v0, v1, v2
```

Scalar floating-point code instead uses scalar `s` or `d` registers:

```
fmul  s0, s1, s2
fmadd s0, s1, s2, s3
fmsub s0, s1, s2, s3

fmul  d0, d1, d2
fmadd d0, d1, d2, d3
fmsub d0, d1, d2, d3
```

The relevant question is not only whether Faust vec mode was enabled. The relevant question is whether the
final assembly contains sustained packed arithmetic in the hot loops.

## Grep checks and instruction counts

The quick inspection used searches for packed arithmetic forms. The most useful checks were:

```
grep -Eo '\b(fmul|fmla|fadd|fsub|fmls)\.(4s|2d)\b' cpp.asm | sort | uniq -c
grep -Eo '\b(fmul|fmla|fadd|fsub|fmls)\.(4s|2d)\b' mojo.asm | sort | uniq -c
```

The rough count over the inspected assembly sections was:

```
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

The exact counts should not be treated as a complete performance model. They are useful because the difference
is large enough to expose the main pattern: C++ contains dense packed SIMD arithmetic, while Mojo does not
show a comparable packed SIMD presence in the same vec-mode case.

## C++ assembly pattern

The C++ section contains many packed single-precision NEON instructions, especially forms like:

```
fmul.4s v..., v..., v...
fmla.4s v..., v..., v...
```

This means that Clang is vectorizing many block loops generated by Faust vec mode.

Even in the 64-bit benchmark path, the generated computation contains many `f32`-shaped internal operations.
That is why the most visible packed SIMD pattern is `f32x4`, not `f64x2`.

The important point is not that the C++ output is clean double-precision SIMD. It is not. The important point
is that C++ extracts substantial packed arithmetic from the vec-mode program, enough to make vec mode faster
than scalar in this benchmark.

## Mojo assembly pattern

The Mojo section does not show the same packed SIMD density.

The dominant pattern is scalar arithmetic and scalar memory traffic:

```
ldr   s...
fmul  s...
fmadd s...
fmsub s...
str   s...
```

There are some vector instructions, but not enough to characterize the hot code as meaningfully vectorized in
the same way as C++.

The missing pattern is sustained packed arithmetic over the vec-mode loops:

```
fmul.4s v..., v..., v...
fmla.4s v..., v..., v...
```

The Mojo output also does not show a meaningful packed double-precision pattern:

```
fmul.2d v..., v..., v...
fmla.2d v..., v..., v...
```

The result is that Mojo largely keeps the vec-mode program as scalar block code: many loops, temporary
buffers, and repeated memory accesses, but too little SIMD throughput.

## Direct interpretation

C++ gets faster because Clang successfully optimizes the kind of loops produced by Faust vec mode. The
generated program still has temporary buffers and multiple passes over block data, but many of those passes
become packed NEON work.

Mojo gets slower because the vec-mode structure is not converted into packed arithmetic with the same
effectiveness. The code mostly follows the generated block structure literally, causing high stack and memory
pressure from continuous reads and writes across temporary buffers.

In C++, the vec-mode cost is compensated by auto-vectorization. In Mojo, the compensation is too small because
most of the work remains scalar.

## Comparison with multibandfilter

The `multibandfilter` case and the `cubic_distortion` case should be kept separate.

In `multibandfilter`, vec mode was already structurally suspicious because the DSP is recurrence-heavy.
Vectorizing across consecutive samples is difficult when later samples depend on earlier state.

`cubic_distortion` is different. It is more favorable to block/vector processing, and the C++ result confirms
that Faust vec mode exposes useful vectorization opportunities in this case.

This makes the Mojo result more informative: Mojo is not only losing on a DSP where vec mode is structurally
bad. It is losing on a case where C++ proves that the vec-mode shape can be profitable.

## Final comparison

The `cubic_distortion` benchmark shows a clear backend-level difference.

C++ benefits from Faust vec mode because Clang turns many generated block loops into packed NEON arithmetic.
The assembly contains a substantial amount of packed `f32x4` work, so the vec-mode transformation produces
real throughput gains.

Mojo does not benefit in the same way. Its vec-mode output keeps the block-oriented structure, but the
assembly remains much more scalar. Therefore Mojo pays the cost of vec mode without recovering enough
performance through SIMD.

The final interpretation is that C++ vec is faster because Clang successfully vectorizes the Faust vec-mode
shape, while Mojo vec is slower because the Mojo toolchain does not vectorize that shape enough.

This does not mean that Faust vec mode is useless. It means that its benefit depends heavily on the target
compiler. In this benchmark, Clang can exploit it; Mojo mostly cannot.
