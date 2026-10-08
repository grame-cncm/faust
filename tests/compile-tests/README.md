
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
