# interp-ydsp: the FBC compiled by YDSP (phase 0 prototype)

Phase 0 of [ANALYSE_YDSP_JIT.md](../../../ANALYSE_YDSP_JIT.md): does YDSP, the DSP language of the
[YUP](https://github.com/kunitoki/yup) library, compile the interpreter's DSP block faster than the FBC compilers
Faust already has, and why?

[fbc_ydsp_compiler.cpp](fbc_ydsp_compiler.cpp) translates the DSP block of an interpreter factory (the sample loop
of `compute`) to YDSP's typed IR, runs YDSP's scalar optimisation passes, and compiles it to x86-64 or AArch64
machine code with YDSP's asmjit code generator. The other blocks stay interpreted, as with interp-llvm, interp-mir
and interp-fpb. The comment at the top of the file describes the translation, the memory mapping, the promotion
of heap cells to registers and what is not compiled.

The YDSP headers need C++20 and libfaust is C++17, so the translator is not in libfaust: a libfaust built with
`INTERP_COMP` and `INTERP_YDSP_BUILD` only sees the declaration of `createFBCYdspCompiler`
([compiler/generator/interpreter/fbc_ydsp_compiler.hh](../../../compiler/generator/interpreter/fbc_ydsp_compiler.hh)),
and a program using it links `fbc_ydsp_compiler.o` and the YUP modules.

For the comparison, [fbc_mir_compiler.hh](../../../compiler/generator/interpreter/fbc_mir_compiler.hh) has the same
promotion: it separates what comes from the code generator from what comes from the translation. It is on by
default in interp-mir since phase 0 (`FAUST_INTERP_MIR_PROMOTE=0` turns it off; the bench sets the variable either
way). It reaches a defect of MIR's AArch64 code generator, which can allocate lr in a leaf function without saving
it: the promoted block makes one call to an empty function, so that MIR saves lr in its prologue.

## Environment variables

| variable | effect |
| :--- | :--- |
| `FAUST_INTERP_YDSP_TRACE=1` | prints whether the DSP block was compiled (code size, IR size, promoted cells, compile time) or why not |
| `FAUST_INTERP_YDSP_PROMOTE=0` | every FBC heap access stays a memory access, as in interp-mir |
| `FAUST_INTERP_YDSP_LIBMF32=0` | YDSP's strict mode: float32 transcendentals computed in float64 and rounded once (more accurate, about one ulp from the interpreter) |
| `FAUST_INTERP_YDSP_OPT=0` | skips YDSP's optimisation passes |
| `FAUST_INTERP_MIR_PROMOTE=0` | interp-mir without the promotion of heap cells (on by default) |

## Building the libraries

Four static libfaust, built out of the source tree. **Set `LIBSDIR`**: the `staticlib` target writes
`build/lib/libfaust.a` otherwise, over the library of the main build. `LIBSDIR` is relative to `faust/build`.
With a backends file that only has `INTERP_BACKEND STATIC` (first library) or `INTERP_COMP_BACKEND STATIC` (the
three others):

```bash
cmake -S <faust>/build -B <dir>/b-ydsp -C <backends file> -DCMAKE_BUILD_TYPE=Release -DINCLUDE_STATIC=ON \
  -DINCLUDE_EXECUTABLE=OFF -DINCLUDE_OSC=OFF -DINCLUDE_HTTP=OFF -DINCLUDE_EMCC=OFF -DINCLUDE_WASM_GLUE=OFF \
  -DINCLUDE_LLVM=OFF -DLIBSDIR=<path of dir/lib-ydsp relative to faust/build> "-DCMAKE_CXX_FLAGS=-DINTERP_YDSP_BUILD=1"
cmake --build <dir>/b-ydsp --target staticlib -j 10
```

and likewise `-DINTERP_FPB_BUILD=1`, `"-DINTERP_MIR_BUILD=1 -I<MIR headers>"`, and no flag for the interpreter.

YUP needs a configured build of its `yup_dsp_compiler` tool (`<yup>/build/ydsp_compiler/build.ninja`):
`run-bench.py` compiles the same module sources with the same flags into `<out>/yup`, once. Nothing is written in
the YUP repository.

## Benchmark

```bash
python3 run-bench.py --faust <faust> --arch <faust>/architecture --lib <faust>/libraries \
  --libfaust-interp <lib-interp/libfaust.a> --libfaust-fpb <lib-fpb/libfaust.a> \
  --libfaust-mir <lib-mir/libfaust.a> --libmir <libmir.a> --libfaust-ydsp <lib-ydsp/libfaust.a> \
  --yup <YUP repository> --out <build dir>
```

On the 12 DSPs of the interp-fpb bench, every engine's outputs are compared with the interpreter's, bit for bit
(single precision, a parameter change halfway), then timed; the C++ class of each DSP, compiled with `-O3
-ffp-contract=off`, gives the ceiling. Then `-double`, two instances of one factory, and vector mode, for
correctness. The run fails if an engine differs from the interpreter, except `ydsp-strict`, whose differences are
expected and reported. [results.md](results.md) has the latest results.

On an Apple M5 (clang 21 `-O3`, 48 kHz, blocks of 128), on geometric mean over the 12 DSPs, with outputs identical
to the interpreter's everywhere: interp-ydsp is ×9.9 faster than the interpreter (C++: ×14.1, interp-mir: ×5.6,
interp-fpb: ×2.5). Promotion gives ×1.74 to YDSP and ×1.37 to MIR; with the same translation, YDSP beats MIR by
×1.29 with promotion and ×1.02 without. Section 9 of the analysis discusses these results.

## Larger corpus

[run-corpus.py](run-corpus.py) compares interp-mir and interp-ydsp, with their defaults, on every DSP of
directories, with the executables `run-bench.py` built:

```bash
python3 run-corpus.py --bin <run-bench out dir> --faust <faust> --lib <faust>/libraries \
  --corpus <faust>/tests/impulse-tests/dsp --name impulse-tests
python3 run-corpus.py --bin <run-bench out dir> --faust <faust> --lib <faust>/libraries \
  --corpus <faust>/examples --name examples
```

On 337 DSPs both engines compile with the interpreter's outputs (91 of `tests/impulse-tests/dsp`, 246 of
`examples`), interp-ydsp is ×1.24 faster than interp-mir with promotion on geometric mean, faster on 252 of them:
[corpus-impulse-tests.md](corpus-impulse-tests.md), [corpus-examples.md](corpus-examples.md).
