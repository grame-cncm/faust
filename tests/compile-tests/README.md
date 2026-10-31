
# Compile tests

### Prerequisites
- `faust` must be available from the command line or from the `build/bin` folder. It must be compiled with all backends but the `interp` backend.

### What's being done
All examples found is the `examples` and `regression` folders are compiled using all the available backends (apart the `interp` backend). In addition and for the c, cpp and ocpp backends, the output is also compiled using the available compilers.


Type `make help` for details on the available targets.


### The regression scripts

Each script below checks one defect once fixed. `make check-scripts
FAUST=<binary>` runs those that need only faust and a C/C++ compiler
(`display-contexts`, `display-tail-sharing`, `division-by-zero`, `exe-path`, `hoist-negation`,
`multiplicative-algebra`,
`infinite-coefficients`, `integer-pow`, `defined-integer-operations`, `power-nature`,
`svg-inner-process`) ;
`make check-scripts-all` runs every one, the others needing Java, Julia,
Cargo, Node, the Xilinx `ap_fixed.h` header or the static libfaust of the build
(`SCRIPT_ARGS` passes their paths). One verdict per script ; the target fails when one script fails.

### Defined integer operations

`defined-integer-operations.py` runs, under the undefined-behaviour sanitizer, the
conversion to an integer of a value that may be NaN (it gives 0 ; a NaN operand of `min` or
`max` makes it return the other one, whose values the conversion then sees), extreme and
negative constant exponents (powers beyond 32 bits in the normal form, a negative constant
left by the constant propagation), an integer remainder by a
divisor that may be 0 or -1 (x % 0 gives 0, -2147483648 % -1 its exact value, 0), a
power of integers whose exponent may be negative, a real (the product of k factors
wrapping on 32 bits, converted ; for a negative exponent, 1 / the wrapped product of |k|
factors, +inf when it is 0) on 15 bases and 111 exponents, and the selector of `-selectn` (a real converted
to the index of a leaf : beyond the integers it saturates, NaN reaches the leaf its failed
comparisons give it), compared with the tree of comparisons. Legs : `cpp`, `ocpp` and `c`,
`ocpp -selectn` for the selector, single and double precision :

```sh
python3 tests/compile-tests/defined-integer-operations.py --faust build/bin/faust
```

### The multiplicative algebra, before the natures

`multiplicative-algebra.py` checks the values of products and quotients simplified before
the natures are known, read through `* 2147483647 + 1` (an integer 1 wraps to
-2147483648, a real 1.0 gives 2147483648.0) : `n/n` and `x/x` are the integer 1,
`(n*4)/(n*2)` is 2, `n*4/2` is `2*n`, `(n*1.0)/n` is 1.0 ; and `(0.5*r)*(0.5*r)`, r the
integer state of a noise generator, stays a real product (no integer square of r, which
would wrap). Legs : `cpp` and `ocpp`, single and double precision :

```sh
python3 tests/compile-tests/multiplicative-algebra.py --faust build/bin/faust
```

### The nature of a power of integers

`power-nature.py` checks that `pow(x, k)` of integers is an integer when the sign of k,
computed on the structure, proves k >= 0, and a real otherwise (the wrapped product
converted, its inverse for k < 0), read through `* 2147483647 + 1` : `pow(2, n) * 2`, n in
[0, 100], is 0 at n = 31 ; `pow(2, m) * 2`, m in [-1, 100], is -4294967296.0 at m = 31 ;
`pow(0, m)`, a possible division by 0, compiles and is +inf at m = -1 ;
the same under `-norui` ; `-fui` folds `pow(2, 34 - 3)` as written by hand, an integer ;
two constants are folded to the value the code computes (`pow(3, 0)` the integer 1,
`pow(2, -31)` 1 / -2147483648) ; `pow(0, -1)` and `pow(2, -32)` are refused. The sign at run
time : each rule that proves an exponent >= 0, pushed to NaN, -0.0, the infinities, values
beyond the integers and divisors 0 and -1, never gives a negative exponent. Legs : `cpp`
and `ocpp`, single and double precision :

```sh
python3 tests/compile-tests/power-nature.py --faust build/bin/faust
```

### The power in the interpreter of the signals

`signal-renderer-pow.py` links a runner with the static libfaust (`build/lib/libfaust.a`,
or `--libfaust`) and runs the interpreter of the signals (`signalRenderer`,
`createSignalDSPFactoryFromString`) on `pow(b, k)` : an integer power for k in [0, 70],
the product wrapping on 32 bits (it was `std::pow` in double converted to int, undefined
beyond the integers : INT_MIN for `pow(3, 21)`), a real power for k in [-40, 70], whose
base 0 gives +inf at run time (the interpreter divided with the folding of constants, which
refuses a divisor 0). 15 bases, double precision :

```sh
python3 tests/compile-tests/signal-renderer-pow.py --faust build/bin/faust
```

### A certain division by 0

`division-by-zero.py` compiles programs that divide by a constant 0, written as a division
(`1/0`, `_/0.0`) or as a power of 0 with a negative exponent (`pow(0.0, -1)`, `pow(0,
-0.5)`, `pow(0.5 - 0.5, -2)`, which stands for 1 / 0^|k|) : each must stop with `ERROR :
division by 0` ; a power of 0 used to be folded to INFINITY. A power of 0 with an exponent
>= 0, and a power whose base may be 0 only at run time, must compile :

```sh
python3 tests/compile-tests/division-by-zero.py --faust build/bin/faust
```

### Infinite coefficients in a sum

`infinite-coefficients.py` compiles a sum whose terms have an infinite
coefficient (`1e308*10`, `ma.INFINITY*2` in single and double precision) :
the normal form must finish within 30 seconds (the common divisor of the
terms keeps its symbols, its coefficient dropped and not divided out) :

```sh
python3 tests/compile-tests/infinite-coefficients.py --faust build/bin/faust
```

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
in both single and double precision for Rust and Julia, including `25^6`, negative bases,
and values near the Int32 limit. An exponent not proven >= 0 (`6*s`, `2*s - 1`) makes the
power real (`power-nature.py`) : the integer product converted, `2^-1` is 0.5.

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
call `sin` 16 times (a node of the block-rate tail with several uses is
computed once), and the bargraph must hold the chain computed on the last
input sample:

```sh
python3 tests/compile-tests/display-tail-sharing.py --faust build/bin/faust
```

### Display contexts

`display-contexts.py` compiles, with the ocpp backend, fifteen programs
whose harvested bargraph displays an expression, and for each a witness
program that outputs the same expression. After each of 30 blocks, the
bargraph must hold the last sample of the witness channel. The cases cover
a negation shared by an output and the display, a node shared with the
branch of `enable`, `control` or `select2` (`-lazyselect`, `-selectn`),
the rewrites `-reassoc`, `-temp 1` and `-mindelay 2`, a block of no sample
(the bargraph keeps its value, 0 at first) and an input read by the display
only under `-ls`, and under `-inpl` and `-ls -inpl` (called in place). The chain of 16 shared
negations must call `sin` 16 times:

```sh
python3 tests/compile-tests/display-contexts.py --faust build/bin/faust
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

### The diagram of a program that calls an inner process

`svg-inner-process.py` draws, with `-svg -f 1`, a program that calls the
`process` of an environment (`synth.process : *(0.5)`), and one that chains
the `process` of two environments. `process.svg` must be the diagram of the
program (the `0.5` included), with one link per inner process to its own
file `process-<serial>.svg`, which links back to `process.svg` : an inner
`process` used to be written to `process.svg` too, over the program's
diagram.

```sh
python3 tests/compile-tests/svg-inner-process.py --faust build/bin/faust
```
