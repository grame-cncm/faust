# Faust benchmark framework

## Overview

This directory contains a small benchmark and inspection framework for Faust-generated DSP code.

The framework has two main execution modes:

- `bench`: generate runnable benchmark programs, execute them, and collect reports.
- `inspect`: generate low-level artifacts, i.e. `LLVM IR` and `ASM`, around the generated `compute` code.

The two modes intentionally use different Faust architecture files. Benchmark architectures measure runtime
behavior. Inspect architectures keep the generated program minimal so the produced low-level code is easier
to read and compare.

## Directory layout

Current intended layout:

```
faust/architecture/_bench/
  arch/
    cpp/
      bench.cpp
      bench.h
      common.h
      inspect.cpp
    mojo/
      bench.mojo
      inspect.mojo
  script/
    source.sh
    bench.sh
    csvmanip.py
    plot.py
  src/
    *.dsp
  report/
    cpp/
    mojo/
    tmp/
    plots/
    snapshots/
    llvm/
      cpp/
      mojo/
    asm/
      cpp/
      mojo/
```

The `arch/<lang>/` directories contain the Faust architecture files used by the framework. The exact
internal organization of each language backend is language-specific: a backend may use headers, helper
files, symlinks, packages, or modules. The framework only assumes that the language-specific generation
functions know which architecture file to pass to Faust.

## Setup

Enter the benchmark workspace and activate the environment:

```
pixi shell
source script/source.sh
```

The environment should provide Faust, Mojo, Python, pandas, matplotlib, and a C++ compiler.

`source.sh` initializes paths, creates report directories, checks the Mojo architecture link, and loads the
benchmark API from `script/bench.sh`.

## Public API

The framework exposes the following public commands:

```
bench_run <langs> <sample_rates_khz> <buffer_sizes> <sources...>
bench_plot <plot_name>
bench_snapshot <snapshot_name>
inspect_llvm_gen <langs> <sources...>
inspect_asm_gen <langs> <sources...>
```

All other shell functions are internal helpers.

### `bench_run`

Run benchmarks and generate reports.

```
bench_run all all all all
bench_run all 48 64 all
bench_run mojo 48 64 bells
bench_run cpp,mojo 48,192 64,512 carre_volterra
```

Arguments:

- `langs`: `all` or comma-separated entries from `BENCH_LANGS`.
- `sample_rates_khz`: `all`, `48`, `192`, or comma-separated values.
- `buffer_sizes`: `all`, a single integer, or comma-separated integers.
- `sources`: `all`, DSP names, DSP paths, or shell-expanded globs.

Precision is not passed as an argument. Each benchmark run always executes all configured precisions, currently `f32` and `f64`.

`bench_run` is a fresh run: it clears the current global CSV, temporary CSV fragments, tab reports, and plots before running.

### `bench_plot`

Generate an SVG plot from the current global CSV.

```
bench_plot tput_48k_64
```

The output is written to:

```text
report/plots/<plot_name>.svg
```

### `bench_snapshot`

Save the current report state.

```
bench_snapshot after_changes
```

Snapshots are written to:

```text
report/snapshots/<timestamp>_<snapshot_name>/
```

A snapshot copies the current CSV, tab reports, plots, and a small metadata file describing the run context.

### `inspect_llvm_gen`

Generate LLVM IR using the inspect architecture.

```
inspect_llvm_gen all carre_volterra
inspect_llvm_gen mojo all
```

Outputs are written to:

```text
report/llvm/<lang>/<dsp>_<precision>.ll
```

### `inspect_asm_gen`

Generate target assembly using the inspect architecture.

```
inspect_asm_gen all carre_volterra
inspect_asm_gen cpp,mojo bells
```

Outputs are written to:

```text
report/asm/<lang>/<dsp>_<precision>.s
```

## Benchmark workflow

The benchmark workflow is:

```text
.dsp source
  -> Faust + bench architecture
  -> generated backend source
  -> compiler
  -> executable
  -> human-readable .tab report
  -> temporary CSV fragment
  -> merged report/report.csv
  -> optional plot or snapshot
```

For each selected DSP source and language, the framework first generates backend source code using the language's `bench` architecture. It then compiles and runs that source for each sample-rate, buffer-size, and precision case.

The generated executable prints a human-readable report. The shell script redirects that output into a `.tab` file. If CSV writing is enabled, the executable also appends a headerless CSV row to a temporary fragment. The Python CSV helper then merges the fragment into the global report CSV.

## Inspection workflow

The inspection workflow is:

```text
.dsp source
  -> Faust + inspect architecture
  -> generated inspect source
  -> compiler --emit llvm / --emit asm
  -> report/llvm/<lang>/ or report/asm/<lang>/
```

Inspection is not benchmarking. Its purpose is to expose the low-level shape of the generated `compute` code with as little benchmark/report/runtime noise as possible.

`inspect_llvm_gen` and `inspect_asm_gen` therefore use the language's `inspect` architecture, not its `bench` architecture.

## Architecture contract

### Architecture lookup

For each supported language, the framework expects two architecture entry points:

```text
arch/<lang>/bench.*
arch/<lang>/inspect.*
```

Examples:

```text
arch/cpp/bench.cpp
arch/cpp/inspect.cpp
arch/mojo/bench.mojo
arch/mojo/inspect.mojo
```

The exact set of auxiliary files is not prescribed by the framework. For example, the C++ backend may split behavior across headers, while Mojo may use modules imported through the architecture tree.

### Bench architecture

A bench architecture must generate a runnable program that:

- instantiates the Faust-generated DSP;
- initializes it with the configured sample rate;
- allocates input and output buffers;
- optionally fills input buffers;
- runs warmup iterations;
- measures repeated calls to `compute`;
- computes an output checksum;
- prints a human-readable report;
- optionally writes one headerless CSV row for each run case.

The language implementation should provide behavior equivalent to:

```text
fill_inputs
warmup
measure
checksum_outputs
print_report
write_csv
```

The names can differ by language if needed, but the behavior and report model must stay aligned.

A bench architecture is allowed to contain benchmark-specific machinery: timing loops, adaptive batching, report printing, CSV writing, checksums, and compiler optimization barriers.

### Inspect architecture

An inspect architecture must generate a minimal runnable program that:

- instantiates the Faust-generated DSP;
- initializes the DSP and buffers;
- calls the generated `compute` path through a clearly identifiable entry point;
- avoids benchmark reporting, CSV writing, plotting, and adaptive timing logic;
- keeps enough optimizer barriers to prevent the compute path from being removed;
- makes LLVM IR or assembly output easy to inspect.

The core behavior is:

```text
inspect_compute
```

This entry point should be easy to find in generated low-level output. It should isolate the generated DSP compute path as much as reasonably possible.

The inspect architecture can still allocate buffers and call `compute` repeatedly, but it should not include benchmark/report framework noise.

## Reports and outputs

Main output paths:

```text
report/<lang>/*.tab
report/report.csv
report/plots/*.svg
report/snapshots/<timestamp>_<name>/
report/llvm/<lang>/*.ll
report/asm/<lang>/*.s
```

Meaning:

- `.tab` files contain the human-readable output of each benchmark executable.
- `report/report.csv` is the global structured benchmark report.
- `report/tmp/*.csv` files are temporary headerless CSV fragments.
- `report/plots/*.svg` contains plots generated from the global CSV.
- `report/snapshots/` stores copies of the current report state.
- `report/llvm/` and `report/asm/` contain inspection artifacts.

## CSV model

Each backend writes headerless temporary CSV rows. The script layer owns the final CSV header and merge policy.

The global CSV stores:

- identity fields: language, DSP, case, precision, optimization;
- configuration fields: sample rate, buffer size, input/output count;
- timing fields: elapsed time, nanoseconds per compute, frame, and output sample;
- spread fields: fast, slow, absolute spread, percent spread;
- throughput fields: frames per second and output samples per second;
- validation field: checksum.

All languages must write rows in the same column order.

Temporary CSV fragments are merged into `report/report.csv` by replacing the rows for the same language, DSP, and benchmark case. This makes repeated runs deterministic and avoids appending stale duplicate rows.

## Plot model

Plots are generated from `report/report.csv`.

The default plot uses output-sample throughput:

```text
out_samp_per_s
```

Values are normalized per DSP/configuration group so different languages and precisions can be compared visually. Fast and slow throughput values are drawn as whiskers when available.

## Adding a new backend

To add a new language backend:

1. Add the language name to `BENCH_LANGS`.
2. Add a bench architecture under `arch/<lang>/bench.*`.
3. Add an inspect architecture under `arch/<lang>/inspect.*`.
4. Implement source generation for the bench architecture.
5. Implement source generation for the inspect architecture.
6. Implement the run-case compilation and execution logic.
7. Implement LLVM and assembly generation if the backend supports them.
8. Ensure the backend writes the same CSV schema as the other languages.

The split is fixed:

```text
bench_run
  uses the bench architecture

inspect_llvm_gen
inspect_asm_gen
  use the inspect architecture
```

## Useful overrides

Common overrides:

```
BENCH_KEEP_TMP=1
BENCH_SAMPLE_RATES=(48000 192000)
BENCH_BUFFER_SIZES=(64 512)
BENCH_WARMUP_ITERS=50
BENCH_COMPUTE_ITERS=1000000
BENCH_MAX_BATCH_SIZE=10000
  BENCH_INSPECT_COMPUTE_ITERS=1
```

Compiler options are configured through:

```
BENCH_CPP_OPT
BENCH_MOJO_OPT
```

<!-- ## Naming conventions -->
<!---->
<!-- The framework uses a few internal names with precise meanings. -->
<!---->
<!-- The term `source` means the original FAUST `.dsp` files used as input: -->
<!---->
<!--     src/<name>.dsp -->
<!---->
<!-- The term `arch` means the FAUST architecture code to wrap the DSP code. -->
<!---->
<!--     arch/<lang>/bench.* -->
<!--     arch/<lang>/inspect.* -->
<!---->
<!-- The benchmark command uses the `bench` architecture. The inspection commands use the `inspect` architecture. -->
<!---->
<!-- The term `out` is used only inside the private shell API. It means the backend source file generated by -->
<!-- Faust after combining a DSP source with an architecture template. These generated files are written back -->
<!-- into the corresponding language architecture directory: -->
<!---->
<!--     arch/<lang>/<name>.<ext> -->
<!--     arch/<lang>/<name>_inspect.<ext> -->
<!---->
<!-- The basic generation relation is: -->
<!---->
<!--     source + arch -> out -->
<!---->
<!-- For example, for any supported language: -->
<!---->
<!--     src/<name>.dsp + arch/<lang>/bench.* -->
<!--       -> arch/<lang>/<name>.<ext> -->
<!---->
<!--     src/<name>.dsp + arch/<lang>/inspect.* -->
<!--       -> arch/<lang>/<name>_inspect.<ext> -->
<!---->
<!-- The term `report` means generated benchmark or inspection output: -->
<!---->
<!--     report/ -->
<!---->
<!-- In short: -->
<!---->
<!--     source = original Faust DSP input -->
<!--     arch   = Faust architecture template -->
<!--     out    = generated backend source, used as an internal script name -->
<!--     report = generated benchmark or inspection output -->

## Notes

The benchmark and inspect architectures intentionally serve different purposes.

The benchmark architecture should produce trustworthy measurements and structured reports. The inspect
architecture should expose the generated low-level code with minimal noise.

Do not use inspect output as a performance measurement. Use it to understand code generation, compiler
behavior, and optimization differences between backends.
