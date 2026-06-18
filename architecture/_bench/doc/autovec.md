<!-- NOTE: Modular forum discussion -->

Hi everyone, I am developing a Mojo backend for FAUST, a functional DSL for audio DSP with mature C++
codegen, and studying which Mojo code shapes optimize best.

FAUST has scalar and vec modes. vec mode restructures code for target-compiler auto-vectorization; it does
not emit SIMD intrinsics.

In my benchmarks, Clang often auto-vectorizes scalar mode and also exploits vec mode. Scalar mode can
outperform vec mode because it avoids FAUST vec overhead. In Mojo, the vec-mode overhead is not compensated
by the expected packed SIMD, while scalar mode does not show comparable auto-vectorization.

- Why is Mojo not auto-vectorizing these loops?
- Am I generating a code shape that prevents Mojo or LLVM from recognizing the loop as vectorizable?
- Is explicit SIMD the intended path in Mojo for this kind of performance-sensitive code?

More broadly, is Mojo expected to develop stronger auto-vectorization over time, or is the current design
direction to prefer explicit SIMD? I am trying to understand whether this is a compiler limitation or
whether the generated backend shape should be changed.

Here is a simplified Mojo `compute` method, the hot loop of a generated FAUST DSP (in scalar mode).

```
comptime dfaust = get_defined_dtype["DType.float32"]()
comptime FaustFloat = SIMD[dfaust, 1]
def compute(
    mut dsp,
    var count: S32,
    var inputs: UnsafePointer[UnsafePointer[FaustFloat, ReadUntrackedOrigin], ReadUntrackedOrigin],
    var outputs: UnsafePointer[UnsafePointer[FaustFloat, MutUntrackedOrigin], MutUntrackedOrigin]
) -> None:
    var input0 = inputs[S32(0)]
    var output0 = outputs[S32(0)]
    var output1 = outputs[S32(1)]
    var slow0 = F64(dsp.hslider0)
    for var i0 in range(S32(0), count):
        var temp0 = F64(input0[i0])
        var temp1 = (temp0) * ((1.0) - ((slow0) * (pow_unrolled[2](temp0))))
        output0[i0] = FaustFloat(temp1)
        output1[i0] = FaustFloat(temp1)
```

`FaustFloat` is the external driver precision, typically `f32`. The internal DSP precision can be either
`single` or `double` (as it is in this example).

The equivalent C++ scalar loop is auto-vectorized by Clang, here a sample from the resulting assembly:

```
ldr     q3, [x16], #16
fcvtl   v4.2d, v3.2s
fcvtl2  v3.2d, v3.4s
fmul.2d v5, v3, v3      ; packed 2xf64 mul
fmla.2d v6, v5, v1      ; packed 2xf64 fma
fcvtn   v4.2s, v4.2d
fcvtn2  v4.4s, v3.2d
str     q4, [x15], #16
```

So Clang auto-vectorizes the scalar loop, just as it does for the vec version of the same source.

The Mojo assembly for the same loop remains scalar and is slower, despite being very small:

```
LBB0_1:
    ldr  s2, [x9, x8]
    fcvt d2, s2
    fmul d3, d2, d2
    fmsub d3, d3, d0, d1
    fmul d2, d3, d2
    fcvt s2, d2
    str  s2, [x10, x8]
    str  s2, [x11, x8]
    add  x8, x8, #4
    cmp  x8, #256
    b.ne LBB0_1
```

In vec mode, the shape does not auto-vectorize either; it adds memory traffic making performance worse.

Thanks for reading, and sorry for the long post. I hope this can start a useful discussion.

