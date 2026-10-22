
# Compile tests

### Prerequisites
- `faust` must be available from the command line or from the `build/bin` folder. It must be compiled with all backends but the `interp` backend.

### What's being done
All examples found is the `examples` and `regression` folders are compiled using all the available backends (apart the `interp` backend). In addition and for the c, cpp and ocpp backends, the output is also compiled using the available compilers.


Type `make help` for details on the available targets.


### Files excluded from tests

- `faust-stk` : the 'c' backend doesn't compile due to C++ specific implementation of foreign functions.
- `TODO` : files names containing TODO

### Fixed-point C++ table regression

`fixed-point-tables.py` compiles generated C++ with the shipped
`faust/dsp/fixed-point.h` and the Xilinx `ap_fixed.h` headers. It covers static
and writable real tables, mixed integer/real tables, several fixed-point sizes,
inline tables and the memory manager. Use a C++ compiler compatible with your
Xilinx headers (for example GCC with libstdc++):

```sh
python3 tests/compile-tests/fixed-point-tables.py \
  --faust build/bin/faust --cxx g++ \
  --ap-fixed-include /path/to/xilinx/include
```

### Non-finite constants

`nonfinite-constants.py` generates a program whose outputs are the constants
+inf, -inf and `1e38 * 10` (an infinity in single precision, folded in double)
at its first sample, in single and double precision, and runs it with the
cpp, ocpp, Julia, Rust and Java backends: the sign of -inf is kept, ocpp tests
a constant in the precision of the program, and the languages without the C
macro `INFINITY` use their own constants (`Inf32`, `f32::INFINITY`,
`Float.POSITIVE_INFINITY`, `f32.POSITIVE_INFINITY`...). `--backends dlang`
compiles the D code with `ldc2` (stubs replace the dplug imports), `--backends csharp`
checks the generated C# names, `--backends asc` compiles the AssemblyScript code
with `asc` and runs it with Node (`--asc`, `--node`); Rust needs Cargo with `libm` and `num-traits` (`--offline`
for cached dependencies):

```sh
python3 tests/compile-tests/nonfinite-constants.py --faust build/bin/faust
python3 tests/compile-tests/nonfinite-constants.py --faust build/bin/faust --backends dlang csharp asc
```

### Math functions out of their domain (Julia, Cmajor)

`math-domain.py` reads -2 and runs `sqrt`, `log`, `log10`, `asin`, `acos`,
`acosh`, `atanh` and `pow(x, 0.5)`, which must give NaN as in C (Julia's
functions throw `DomainError` there), then `isnan` and `isinf` as integers
(Cmajor's return a `bool`) and the constant -inf, in Julia and with
`cmaj render`, in single and double precision:

```sh
python3 tests/compile-tests/math-domain.py --faust build/bin/faust
```

### Float-to-integer conversions in Julia

`julia-float-to-int.py` runs `process = _ : int;` in Julia on 0.5, -2.7, NaN,
1e10, -1e10 and 3e9, in single and double precision: the conversion
saturates (0 for a NaN, the nearest bound of the Int32 range beyond it), as
in the C++ (arm64) and WebAssembly backends, where `trunc` threw
`InexactError`:

```sh
python3 tests/compile-tests/julia-float-to-int.py --faust build/bin/faust
```

### Integer powers with run-time exponents

`integer-pow.py` executes the C++ regression, including `-ffast-math`.
`integer-pow-backends.py` compiles and executes six integer-power expressions
in both single and double precision for Rust and Julia. Integer differences
are checked before conversion to sample floats, including `25^6`, negative bases,
negative exponents with half-way rounding, and values near the Int32 limit.

```sh
python3 tests/compile-tests/integer-pow.py --faust build/bin/faust --cxx clang++
python3 tests/compile-tests/integer-pow-backends.py --faust build/bin/faust
```

The backend test requires Cargo (`libm` and `num-traits`) and Julia
with `StaticArrays`. Use `--backends rust julia` to select installed
toolchains, `--offline` for cached Cargo dependencies. A missing toolchain or a failed compilation fails the test;
backends are never silently skipped. Each backend/precision leg compares six
expressions over two samples.

### Hoisting of negated constants

`hoist-negation.py` checks that a negated constant or control-rate
expression (`0 - exp(-k)`, `0 - expm1(-k)`, `y*-1`) used once in a
select2 branch is computed in `instanceConstants` or once per block, not
in the sample loop, with the cpp, c and ocpp backends:

```sh
python3 tests/compile-tests/hoist-negation.py --faust build/bin/faust
```

### Shared nodes in a bargraph's block-rate tail

`display-tail-sharing.py` compiles a bargraph showing a chain of 16
`_ <: sin + cos`, each level using the previous one twice, with the ocpp
and cpp backends in single and double precision. The generated code must
call `sin` 16 times (the ocpp backend used to inline the shared levels,
65535 calls here, and grew past 100 GB on an octave analyzer of the
libraries), and the bargraph must hold the chain computed on the last
input sample:

```sh
python3 tests/compile-tests/display-tail-sharing.py --faust build/bin/faust
```

### Java backend execution

`java-math.py` generates Java, compiles it with `javac`, and executes it with
`java`, in both single and double precision. It checks hyperbolic functions
and their inverses, NaN/infinity classification, signed zeros, `copysign`,
IEEE remainder versus modulo, both rounding modes, integer powers, boolean
conversions, mixed selections, enable conditions, double casts, UI accessors
and integer/real table initialization.
The numeric comparator must reject an intentionally corrupted output before
its results are accepted. A missing JDK, compilation error or wrong value
fails the test; neither precision is skipped.

```sh
python3 tests/compile-tests/java-math.py --faust build/bin/faust \
  --javac /path/to/jdk/bin/javac --java /path/to/jdk/bin/java
```

The default commands are `javac` and `java` from `PATH`. Use
`--work-dir /tmp/faust-java-math` to keep generated sources and diagnostic
logs. The test provides a minimal Java DSP/UI harness with sample types
matching each precision; it does not depend on an installed Faust runtime.

### Locating the faust binary through PATH

`exe-path.py` calls faust by a bare name, through two symbolic links (as
`/usr/bin/faust -> /etc/alternatives/faust -> /usr/bin/faust-x.y.z`), with a
`which` that writes to stderr and fails first in `PATH` (as the deprecated
which(1) of Debian bookworm warns), and a directory and a non-executable
file named `faust` before the real one. faust must find its own directory
without running `which` and without printing on stderr, through a regular,
an empty (the current directory) and a relative `PATH` entry: `--libdir`
must name the `lib` directory next to the binary.

```sh
python3 tests/compile-tests/exe-path.py --faust build/bin/faust
```
