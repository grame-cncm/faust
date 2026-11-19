# interp-fpb: the FBC compiled to FPB steps

`compiler/generator/interpreter/fbc_fpb_compiler.hh` is a third FBC compiler for the interpreter, beside the LLVM
and MIR ones: with `INTERP_FPB_BUILD`, the DSP block of a factory (the sample loop of `compute`) is compiled to
FPB-style steps the first time an instance is initialised, and the other blocks (init, control, UI) stay
interpreted. It needs neither LLVM nor MIR, and generates no machine code.

FPB (float patch bytecode) is a register bytecode for targets that cannot compile code. A compiled block is an
array of steps `{ operation, operand pointers }`; each operation is a small C++ function that jumps straight to
the next one (a guaranteed tail call with clang ≥ 13 and GCC ≥ 15, a loop elsewhere). The compiler:

1. runs the stack machine of the sample loop symbolically, so that every store becomes an expression tree;
2. emits 3-address operations that write straight into their destination, with operands pointing into the
   interpreter heaps themselves (the state is shared with the interpreted blocks), temporaries, a constant pool,
   the current frame's samples, or array descriptors;
3. applies peephole optimisations: `a*b + c` and `c - a*b` in one operation, delay line accesses
   (`arr[(i - d) & mask]`) in one operation, pairs of moves, and 12 fused pairs of operations, chosen from the
   most frequent pairs in compiled Faust code.

Every operation computes what the interpreter computes (same expressions, rounded after each operation, no
FMA contraction), so the outputs are identical to the interpreter's. A block it does not handle (vector mode,
soundfiles, `if` blocks, a select branch with a store...) is not compiled, and the interpreter runs it.
`FAUST_INTERP_FPB_TRACE=1` prints what happened.

## Building

As for the other FBC compilers, the interpreter/compiler backend goes in the library, and `INTERP_FPB_BUILD`
selects FPB (uncomment it in `fbc_interpreter.hh`, or pass it to the compiler):

```bash
cd build
cmake -S . -B faustdir -C backends/<your backends file>.cmake -DINCLUDE_STATIC=ON -DCMAKE_CXX_FLAGS="-DINTERP_FPB_BUILD=1"
cmake --build faustdir --target staticlib
```

with, in the backends file, `INTERP_COMP_BACKEND` set to `STATIC` (and `INTERP_BACKEND` to `COMPILER` if the
`faust` executable must also emit FBC). The factory's compile options then say `-lang interp-fpb`.

## Benchmark

`run-bench.py` runs 12 DSPs of the Faust `examples` folder (the `DSPS` list in the script). It needs a `faust`
that emits FBC, a `libfaust.a` with the plain interpreter, and one with interp-fpb:

```bash
python3 run-bench.py --faust <faust> --arch <faust>/architecture --libfaust-interp <interp/libfaust.a> --libfaust-fpb <interp-fpb/libfaust.a> --lib /usr/local/share/faust
```

It checks that both give identical outputs (single and double precision, a parameter change halfway, two
instances of one factory used alternately, and a vector-mode block that falls back to the interpreter), then
times them. [results.md](results.md) has the latest results; on an Apple M5 (clang -O3, 48 kHz, blocks of 128),
interp-fpb is **×2.45 faster** than the interpreter on geometric mean over 12 DSPs (×1.55 to ×5.36), with
identical outputs everywhere.

## Impulse tests

The `interp1` suite of `tests/impulse-tests` (the interpreter with a compiled DSP block) runs with interp-fpb when
`impulseinterp1` is linked with an interp-fpb `libfaust.a`:

```bash
cd tests/impulse-tests
rm -f impulseinterp1
make interp1 MACHINE_LIB=<interp-fpb/libfaust.a>
```

Results on 2026-11-19 (99 DSPs × 8 option sets: default, `-dlt 0`, `-dlt 256`, `-vec -lv 1`, `-vec -lv 1 -vs 16`,
`-vec -lv 1 -g`, `-inpl`, `-ftz 1`), against the same suite with the plain interpreter:

- every test has the same result as with the interpreter, and the 789 `.ir` files are byte for byte identical;
- FPB compiles the DSP block of 97 DSPs out of 99 in scalar mode; `osc_enable` (its DSP block is not a plain
  sample loop) and `sound` (soundfiles) stay interpreted, as do all DSPs in vector mode;
- the failures are the interpreter's own, with or without FPB: `pow_float_int`, `pow_int_float` and
  `subcontainer1` in every option set, plus `prefix` in vector mode; and `faust` itself crashes on `sound` in
  vector mode.

## Limits

- The steps hold absolute pointers, so they are bound to the heaps of each instance when it first runs (one
  binding per instance, kept in the shared compiled block, under a mutex).
- Like the LLVM and MIR compilers, interp-fpb leaves the control block interpreted, and unoptimised (the
  interpreter's FBC optimiser only runs in pure interpreter mode).
- The heap is not folded into constants: init and the control block write it at run time, at any sample rate.
  Hence somewhat more steps than the standalone FPB compiler, which folds everything computed at init for one
  sample rate and removes one-sample copies.
