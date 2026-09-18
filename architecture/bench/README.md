## Faust benchmark framework

This directory contains the framework used to measure and compare the performance of DSP code generated
by the FAUST backends, with particular reference to the `C++` and `Mojo` implementations.

The framework orchestrates the steps required to transform the same FAUST program into comparable executable
programs, run them under homogeneous conditions, and collect the results in a common representation.

The general flow can be summarized as follows:

```
    FAUST program
          |
    FAUST compiler + bench architecture
          |
          +---------------------+
          |                     |
       C++ file             Mojo file
          |                     |
       clang++              mojo build
          |                     |
          +----------+----------+
                     |
              benchmark runtime
                     |
              text / CSV report
                     |
              plot and snapshot
```

The same framework also includes an inspection path separate from the benchmark, used to produce `LLVM IR`
and assembly for the generated kernel without introducing measurement and reporting logic into the code
being inspected.

## Quick start

The supplied `pixi.toml` and `pixi.lock` configure an `osx-arm64` environment. Build FAUST at
`../../build/bin/faust` and make sure `clang++` is on `PATH`; the Mojo benchmark and inspection
architectures must be available in the adjacent `architecture/mojo` directory. On macOS, install Pixi if
necessary and, from the repository root, enter the benchmark environment:

```
    brew install pixi
    cd architecture/_bench
    pixi install
    pixi shell
```

The following commands use the Python CLI directly, `source.sh` is optional.

To benchmark *both modes* (`scalar`, `vec`), *both languages* (`cpp`, `mojo`), and *every* `*.dsp` file in
`src`, run the full matrix. The flag `--jobs 4` limits simultaneous generation and build processes.
Measurements run one at a time. Failed cases are reported without discarding successful measurements.

```
    python3 script/bench.py --jobs 4 run all all all
    python3 script/bench.py plot full_matrix
    python3 script/bench.py snapshot full_matrix
```

Results accumulate in `report/report.csv`; rerunning a case replaces its matching row. The command `plot`
writes an SVG under `report/plot`, and `snapshot` copies the current report into `report/snap`. To start
with an empty current report, run `python3 script/bench.py clean` **before** the matrix; this removes
current results and generated artifacts but preserves existing snapshots.

On `bash` or `zsh`, `source script/source.sh` loads optional shell functions and prints their help. Each
function forwards to the Python CLI:

```
    bench_run all all all
    python3 script/bench.py run all all all

    bench_plot full_matrix
    python3 script/bench.py plot full_matrix

    bench_snapshot full_matrix
    python3 script/bench.py snapshot full_matrix
```

The positional `case` in `bench_plot` is optional; `bench_plot <name> all` plots every case, like omitting
`--case` in Python. Use `python3 script/bench.py <command> --help` for command-specific options.

## Directory organization

The main components are organized according to the following structure:

```
    architecture/_bench/
    ├── arch/
    │   └── cpp/
    │       ├── common.h
    │       ├── bench.h
    │       ├── bench.cpp
    │       └── inspect.cpp
    ├── script/
    │   └── Python implementation of the framework
    ├── src/
    │   └── *.dsp
    ├── report/
    │   ├── report.csv
    │   ├── bin/
    │   ├── tab/
    │   ├── tmp/
    │   ├── plot/
    │   ├── snap/
    │   ├── llvm/
    │   └── asm/
    ├── pixi.toml
    └── pixi.lock
```

The `src` directory contains the FAUST sources used as benchmark cases. An explicit path to another DSP
source can also be provided to the framework.

The `arch/cpp` directory contains the architectures dedicated to the C++ backend. The corresponding Mojo
architectures are not duplicated inside `_bench`: they are used directly from `architecture/mojo`.

The `script` directory contains the Python code that coordinates generation, compilation, execution,
reporting, plotting, and inspection of the produced code.

The files transpiled to the target language by the framework are kept under `report/tmp/<run-id>`.
The C++ and Mojo architectures depend on local headers or packages outside this directory. Their respective
paths are therefore passed to the compilers through the `-I` option. This way, the physical location of the
generated file does not need to match the architecture location.

Persistent artifacts produced by the framework are instead organized into the `report` subdirectories,
separating binaries, text outputs, plots, snapshots, and inspection results.

## Pixi environment

The directory is an independent Pixi workspace. `pixi.toml` describes the toolchain and dependencies used
by the framework, while `pixi.lock` stores the concrete environment resolution.

The main dependencies include Mojo and the Python tools used for orchestration and report generation.
Once the environment has been installed with:

```
    pixi install
```

it can be entered with:

```
    pixi shell
```

or a command can be executed without opening an interactive shell through `pixi run`.

Pixi makes the benchmark toolchain reproducible, the logic is implemented in Python, and `source.sh`
provides an optional alias layer for `/zsh`.

## Numerical configuration

The framework assumes a fixed numerical configuration, chosen to compare the backends under the same
conditions used during the development of the Mojo backend.

The internal DSP precision is selected during FAUST transpilation through:

```
    -double
```

The internal computation produced by the generator therefore uses `f64` precision, while the external
architecture interface uses `f32` samples.

For C++, the type is resolved through the `FAUSTFLOAT` macro in the source code and by passing the
corresponding option to the compiler:

```
    -DFAUSTFLOAT=float
```

For Mojo, an equivalent mechanism is used through the `get_defined_dtype` function call in the source code:

```
    dfaust = get_defined_dtype("DFAUST", DType.float32)
```

and by passing the option:

```
    -D DFAUST=DType.float32
```

The numerical configuration therefore uses:

```
    internal DSP computation    f64
    external C++ buffers        f32
    external Mojo buffers       f32
```

The execution configuration uses:

```
    sample rate    48000 Hz
    buffer size    128 frames
```

## Scalar and vector modes

The framework exposes two generation modes:

- `scalar`, corresponding to ordinary FAUST generation;
- `vec`, corresponding to generation through the FAUST vector code container.

Vector mode adds the following FAUST options:

```
    -vec -vs 4 -dfs
```

The `-vec` mode reorganizes the kernel into subloops according to the DSP dependencies. In the C++ backend,
these loops can subsequently be auto-vectorized by the compiler, while the Mojo backend uses this structure
as the basis for the explicit SIMD emission described in the generator documentation.

The `-vs 4` value corresponds to the SIMD configuration used during development on Apple silicon M1 and M4
and must remain consistent with the vector width assumed by the generated Mojo code.

## Running benchmarks

The main command generates, compiles, and executes a benchmark matrix:

```
    bench_run <modes> <langs> <sources...>
```

For example:

```
    bench_run all all all
    bench_run scalar cpp,mojo carre_volterra
    bench_run vec mojo multibandfilter
```

The available selections are:

- mode: `scalar`, `vec`, or `all`;
- language: `cpp`, `mojo`, or `all`;
- source: DSP name, explicit path, glob, or `all`.

The framework resolves the requested combinations and applies the same generation, compilation, and
measurement path to each DSP.

## Generation and compilation

Generation combines the DSP source with the benchmark architecture of the selected language.

For C++:

```
    src/<dsp>.dsp + <path>/bench.cpp
                |
        benchmark C++ file
                |
              clang++
                |
              binary
```

For Mojo:

```
    src/<dsp>.dsp + architecture/mojo/bench.mojo
                      |
              benchmark Mojo file
                      |
                  mojo build
                      |
                    binary
```

The same pipeline is used for scalar and vec modes; what changes is the form of the code produced by FAUST
and, subsequently, the code generated by the target compiler.

## Benchmark architecture

The `bench` architectures transform the generated DSP into a standalone measurable program. They initialize
the DSP, prepare the buffers, and call `compute` in a controlled environment.

The general behavior is equivalent for C++ and Mojo:

```
    DSP initialization
            |
    buffer allocation
            |
    input initialization
            |
          warmup
            |
    compute measurement
            |
    output checksum
            |
            +--> text report
            |
            +--> CSV
```

The warmup prevents the first executions from directly affecting the measurement. The benchmark then calls
`compute` repeatedly and collects the timings needed to compare the different implementations.

The output checksum is not a performance metric; it keeps the computation result observable and allows the
backend executions to be compared.

## Report

Each benchmark produces a text output and updates the global structured report:

```
    report/report.csv
```

The readable outputs of individual executions are stored under:

```
    report/tab/
```

The CSV keeps the different DSPs, languages, modes, and benchmark cases separate, allowing multiple
executions to be accumulated and compared in the same report.

The collected metrics include:

- average time per `compute` invocation;
- time per frame;
- throughput in frames per second;
- throughput in output samples per second;
- fast and slow measurement values;
- result checksum.

## Plot

The command:

```
    bench_plot <name>
```

produces an SVG plot from the contents of `report/report.csv`.

The plot compares results using the average throughput in frames per second for every DSP, including those
with no outputs. Columns are grouped by DSP; for each DSP, the highest average value is set to 100%, and the
height of the other columns represents their respective average value as a percentage of that maximum.

Above each column, the average throughput value is shown in `frames/s`.

The error bars associated with each column show the fast and slow extremes.

## Snapshot

The command:

```
    bench_snapshot <name>
```

saves the current report state under:

```
    report/snap/
```

A snapshot stores a set of results persistently, allowing changes to the generator and architectures and
subsequent comparison of new results with previous ones. For this reason, the normal `cleanup` does not
remove the `report/snap` directory.

## LLVM and assembly inspection

Benchmarking and code inspection are kept separate. The benchmark architectures contain the logic required
for measurement, while the `inspect` architectures keep the computation path minimal in order to inspect
the code produced by the target compiler.

The framework exposes:

```
    inspect_llvm <modes> <langs> <sources...>
    inspect_asm <modes> <langs> <sources...>
```

Generation uses `inspect.cpp` for C++ and `inspect.mojo` for Mojo.

The resulting artifacts are stored respectively under:

```
    report/llvm/<lang>/
    report/asm/<lang>/
```

This mode allows the generated code to be analyzed, the presence of SIMD instructions to be verified, and
the transformations performed by the compilers to be compared without using these outputs as performance
measurements.

## Already transpiled files

The framework can directly compile and execute an already transpiled C++ or Mojo file, skipping the FAUST
generation phase:

```
    bench_run_transpiled <mode> <lang> <path>
```

The specified mode must match the one used when the file was transpiled. For an already transpiled file,
`scalar` or `vec` do not modify the compiled code, but identify the case in the report. Passing the wrong
mode places the result in the wrong column.

This command is useful during optimization when, for example, the code produced by the backend is modified
manually and its performance needs to be measured.

The same principle is available for inspection:

```
    inspect_llvm_transpiled <mode> <lang> <path>
    inspect_asm_transpiled <mode> <lang> <path>
```

The file is compiled directly from its own path using the framework configuration and the compiler of the
target language.

## Cleanup

Files generated during benchmarking and inspection are temporary artifacts and are kept in the
`report/tmp` area. Already transpiled files provided by the user are instead used directly and are not
copied or modified by the framework.

The command:

```
    bench_clean
```

removes the regenerable artifacts produced by the framework. Snapshots remain available unless their
removal is explicitly requested with the `--snapshots` option.

During development, intermediate files can also be preserved with the `--keep-tmp` option, which is useful
when inspecting the code produced by FAUST before target compilation.
