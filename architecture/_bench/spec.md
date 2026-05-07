# Faust benchmark workspace specification

## 1. Scope

This document specifies the organization of the Faust benchmark workspace under `architecture/_bench`.

The goal is to keep the benchmark workflow modular, reproducible, and easy to drive both interactively and
through final wrapper scripts.

This specification covers:

- the fixed directory structure;
- the role of each script;
- the benchmark execution model;
- the handling of generated sources and binaries;
- the CSV generation and merge policy;
- cleanup and plotting behavior.

The Faust compiler generation step from `.dsp` to `.cpp` / `.mojo` is intentionally left out for now. The
scripts may assume that generated source files already exist or will be materialized by a later generation
step.

## 2. Fixed directory structure

The current `_bench` directory structure is considered fixed. Only the contents of the `script/` directory
may be reorganized.

```text
.
├── arch
│   ├── cpp
│   │   ├── bench.cpp
│   │   └── include
│   └── mojo -> ../../mojo
├── bin
├── out
├── pixi.lock
├── pixi.toml
├── report
│   ├── cpp
│   ├── mojo
│   ├── plots
│   ├── tmp
│   └── report.csv
├── script
└── src
    └── hello_sine.dsp
```

Some directories may not exist initially and should be created by the setup/source script when needed.

## 3. Directory responsibilities

### `src/`

Contains Faust DSP source files.

Example:

```text
src/hello_sine.dsp
```

The base DSP name is derived from the file name without extension:

```text
hello_sine.dsp -> hello_sine
```

This name is used to derive generated source paths, binary names, report names, and CSV keys.

### `arch/cpp/`

Contains the C++ benchmark Faust architecture.

```text
arch/cpp/bench.cpp
arch/cpp/include/
```

The benchmark C++ source generated from a DSP is compiled against this architecture and its helper headers.

### `arch/mojo`

This is a symlink to the real Mojo architecture directory:

```text
arch/mojo -> ../../mojo
```

The symlink is intentional.

Mojo-generated benchmark source files may need to live inside the real `architecture/mojo` tree so that Mojo
imports, package resolution, LSP diagnostics, and build behavior remain stable.

The scripts must verify that this symlink exists and points to the expected location. If missing, the
setup/source script should create it.

### `out/`

Contains generated or materialized source files when they are kept.

Suggested layout:

```text
out/
├── cpp
│   └── hello_sine.cpp
└── mojo -> ../arch/mojo/out
```

For C++, generated files can live directly under `_bench/out/cpp`.

For Mojo, generated files should live inside the Mojo architecture tree, for example:

```text
arch/mojo/out/hello_sine.mojo
```

Then `_bench/out/mojo` may be a symlink to that directory.

This keeps generated Mojo files inside the location where the Mojo build and LSP behavior are reliable,
while still exposing them from `_bench/out`.

### `bin/`

Contains compiled benchmark executables.

Binary names are deterministic:

```text
bin/<dsp>_cpp
bin/<dsp>_mojo
```

Example:

```text
bin/hello_sine_cpp
bin/hello_sine_mojo
```

Binaries are temporary build artifacts and should be ignored by git.

### `report/`

Contains benchmark outputs.

Suggested layout:

```text
report/
├── cpp
│   └── *.tab
├── mojo
│   └── *.tab
├── plots
│   └── *.svg
├── tmp
│   └── *.csv
└── report.csv
```

Responsibilities:

- `report/cpp/`: textual benchmark outputs for C++ runs;
- `report/mojo/`: textual benchmark outputs for Mojo runs;
- `report/tmp/`: temporary per-sweep CSV files without headers;
- `report/report.csv`: canonical aggregated benchmark CSV;
- `report/plots/`: generated SVG plots.

## 4. Pixi policy

The workspace uses Pixi for the environment.

For robustness, scripts should explicitly use `pixi run` when invoking tools that are provided by the Pixi environment.

Examples:

```bash
pixi run mojo build ...
pixi run python script/bench.py ...
```

The sourced setup script may also ensure that the user is inside a Pixi shell or enter/trigger the Pixi
environment when appropriate.

Preferred behavior:

- user enters `_bench`;
- user sources the benchmark environment script;
- all required paths and functions become available;
- scripts still use `pixi run` for Pixi-managed commands when needed.

## 5. Script organization

The script directory should be modular, but not excessively fragmented.

Proposed structure:

```text
script/
├── source.sh
├── bench.sh
├── plot.sh
├── bench.py
├── clean.sh
└── all.sh
```

Additional helper files may be added only if they clearly reduce duplication without making the workflow
harder to understand.

## 6. `source.sh`

`source.sh` is the main interactive entry point.

It is meant to be sourced from the `_bench` root:

```bash
source script/source.sh
```

Responsibilities:

- detect the benchmark root directory;
- initialize benchmark paths;
- initialize default benchmark parameters;
- initialize sweep values;
- define supported languages;
- create required directories;
- verify or create the `arch/mojo -> ../../mojo` symlink;
- verify or create generated-output directories and symlinks;
- source the shell files that define public benchmark functions;
- make interactive functions available to the user.

It should not run benchmarks by itself.

Suggested default parameters:

```bash
BENCH_WARMUP_ITERS=100
BENCH_COMPUTE_ITERS=100000

BENCH_BUFFER_SWEEP_SAMP_RATE=96000
BENCH_BUFFER_SIZES=(16 32 64 128 256 512 1024 2048)

BENCH_SAMPLE_RATE_SWEEP_BUFF_SIZE=128
BENCH_SAMPLE_RATES=(44100 48000 96000 192000)

BENCH_LANGS=(cpp mojo)
BENCH_PRECISIONS=(f32 f64)
BENCH_OPTS=(O0 O3)
```

The values should be centralized here so that C++ and Mojo benchmarks use the same matrix.

## 7. Naming conventions

Given a DSP name:

```text
hello_sine
```

The derived paths should be deterministic.

Suggested path functions:

```text
bench_dsp_path hello_sine      -> src/hello_sine.dsp
bench_cpp_src hello_sine       -> out/cpp/hello_sine.cpp
bench_mojo_src hello_sine      -> out/mojo/hello_sine.mojo
bench_cpp_bin hello_sine       -> bin/hello_sine_cpp
bench_mojo_bin hello_sine      -> bin/hello_sine_mojo
```

Suggested report names:

```text
report/<lang>/<bench_case>_<dsp>_<precision>_<opt>_sr<samp_rate>_bs<buff_size>.tab
```

Example:

```text
report/cpp/buffer_sweep_hello_sine_f32_O3_sr96000_bs128.tab
report/mojo/sample_rate_sweep_hello_sine_f64_O0_sr44100_bs128.tab
```

Temporary CSV names:

```text
report/tmp/<lang>_<dsp>_<bench_case>.csv
```

Examples:

```text
report/tmp/cpp_hello_sine_buffer_sweep.csv
report/tmp/mojo_hello_sine_sample_rate_sweep.csv
```

## 8. `bench.sh`

`bench.sh` contains the benchmark build/run logic.

It should define public functions that can be used interactively after sourcing `source.sh`.

Suggested public API:

```bash
bench_case <lang> <dsp> <bench_case> <precision> <opt> <samp_rate> <buff_size>
bench_matrix <lang> <dsp> <bench_case> <samp_rate> <buff_size>
bench_bs_sweep <lang> <dsp>
bench_sr_sweep <lang> <dsp>
bench_all <lang> <dsp>
```

Where `<lang>` can be:

```text
cpp
mojo
all
```

If `<lang>` is `all`, the function dispatches to all supported languages.

### Public functions

#### `bench_case`

Runs one exact benchmark configuration.

Example:

```bash
bench_case cpp hello_sine buffer_sweep f32 O3 96000 128
```

Default behavior:

- builds the selected language backend for the selected configuration;
- runs the produced binary;
- writes one `.tab` report;
- does not update `report/report.csv`.

This function is intended for interactive debugging and inspection.

It should not mutate the canonical CSV by default.

#### `bench_matrix`

Runs the precision × optimization matrix for one fixed benchmark case, sample rate, and buffer size.

Example:

```bash
bench_matrix cpp hello_sine buffer_sweep 96000 128
```

This is useful for testing one point of the benchmark space across:

```text
f32/f64 × O0/O3
```

CSV behavior should be explicit. By default, this function may produce `.tab` files only, unless called
internally by a sweep with CSV enabled.

#### `bench_bs_sweep`

Runs the buffer-size sweep for a DSP and language.

Example:

```bash
bench_bs_sweep cpp hello_sine
```

It runs all configured buffer sizes at a fixed sample rate:

```text
sample rate = BENCH_BUFFER_SWEEP_SAMP_RATE
buffer sizes = BENCH_BUFFER_SIZES
```

For each buffer size, it runs the precision × optimization matrix.

This is a structured run and should update the canonical CSV through the staging/merge process.

#### `bench_sr_sweep`

Runs the sample-rate sweep for a DSP and language.

Example:

```bash
bench_sr_sweep mojo hello_sine
```

It runs all configured sample rates at a fixed buffer size:

```text
buffer size = BENCH_SAMPLE_RATE_SWEEP_BUFF_SIZE
sample rates = BENCH_SAMPLE_RATES
```

For each sample rate, it runs the precision × optimization matrix.

This is a structured run and should update the canonical CSV through the staging/merge process.

#### `bench_all`

Runs the full benchmark suite for one DSP.

Example:

```bash
bench_all all hello_sine
```

Expected behavior:

- run buffer-size sweep;
- run sample-rate sweep;
- run selected languages or all supported languages;
- update `report/report.csv` through structured merges;
- optionally generate plots, or leave plotting to `plot.sh` / `all.sh`.

## 9. Language-specific internals

Language-specific implementation details should be hidden behind private helper functions.

Suggested private functions:

```bash
_bench_build_cpp ...
_bench_build_mojo ...
_bench_run_cpp ...
_bench_run_mojo ...
_bench_case_cpp ...
_bench_case_mojo ...
```

The public API should dispatch on the `<lang>` argument.

This keeps user-facing commands stable while allowing C++ and Mojo to have different compile flags.

## 10. C++ build model

The C++ benchmark source path is derived from the DSP name:

```text
out/cpp/<dsp>.cpp
```

The binary path is:

```text
bin/<dsp>_cpp
```

C++ compile-time options are passed as macros.

Expected options include:

```text
BENCH_LANG
BENCH_CASE
BENCH_OPTIM
FAUSTFLOAT
WRITE_CSV
CSV_PATH
FILL_INPUTS
SAMP_RATE
BUFF_SIZE
WARMUP_ITERS
COMPUTE_ITERS
```

Precision mapping:

```text
f32 -> -DFAUSTFLOAT=r32
f64 -> -DFAUSTFLOAT=r64
```

Optimization mapping:

```text
O0 -> -O0
O3 -> -O3
```

The C++ backend should be able to run without writing CSV when `WRITE_CSV=0`.

When CSV writing is enabled, it should append a data row only, without writing the header.

## 11. Mojo build model

The Mojo benchmark source path is derived from the DSP name:

```text
out/mojo/<dsp>.mojo
```

This may resolve through a symlink to:

```text
arch/mojo/out/<dsp>.mojo
```

The binary path is:

```text
bin/<dsp>_mojo
```

Mojo compile-time options are passed through `mojo build -D`.

Expected options include:

```text
BENCH_LANG
BENCH_CASE
BENCH_OPTIM
FAUST_DTYPE
WRITE_CSV
CSV_PATH
FILL_INPUTS
SAMP_RATE
BUFF_SIZE
WARMUP_ITERS
COMPUTE_ITERS
```

Precision mapping:

```text
f32 -> DType.float32
f64 -> DType.float64
```

Optimization mapping:

```text
O0 -> mojo build -O 0
O3 -> mojo build -O 3
```

The Mojo backend should be able to run without writing CSV when `WRITE_CSV=False`.

When CSV writing is enabled, it should append a data row only, without writing the header.

## 12. CSV policy

The canonical CSV file is:

```text
report/report.csv
```

The canonical CSV must be a valid CSV file with exactly one header row.

The backend languages must not own global CSV state.

Language backends should only append raw data rows to a temporary CSV file when explicitly requested.

They should not:

- decide whether the canonical CSV exists;
- write the CSV header;
- remove previous rows;
- update previous rows;
- merge partial benchmark results;
- edit `report/report.csv` directly.

Those responsibilities belong to script/Python level.

## 13. CSV row format

The exact column list should be centralized in `bench.py` and used consistently for parsing, merging, and plotting.

Suggested columns:

```text
dsp,language,bench_case,precision,opt,samp_rate,buff_size,warmup_iters,compute_iters,total_frames,
total_seconds,ns_per_frame,throughput_frames_per_sec,checksum
```

Additional columns may be added if needed, but the merge key must remain explicit.

Suggested merge key:

```text
dsp,language,bench_case,precision,opt,samp_rate,buff_size
```

This key identifies one benchmark result configuration.

If a new result has the same key as an existing row, the new result replaces the old row.

## 14. Temporary CSV staging

Structured runs write to temporary per-sweep CSV files first.

Examples:

```text
report/tmp/cpp_hello_sine_buffer_sweep.csv
report/tmp/cpp_hello_sine_sample_rate_sweep.csv
report/tmp/mojo_hello_sine_buffer_sweep.csv
report/tmp/mojo_hello_sine_sample_rate_sweep.csv
```

Temporary CSV files:

- contain data rows only;
- do not contain headers;
- are deleted before the corresponding sweep starts;
- are produced by backend executables through append-only writes;
- are merged into `report/report.csv` after the sweep completes.

## 15. CSV merge behavior

`bench.py` should own the canonical merge operation.

Given:

```text
report/report.csv
report/tmp/cpp_hello_sine_buffer_sweep.csv
```

The merge operation should:

1. read the canonical CSV if it exists;
2. read the temporary CSV using the canonical column schema;
3. remove from the canonical CSV all rows whose merge key matches rows from the temporary CSV;
4. append the temporary rows;
5. sort rows deterministically;
6. write `report/report.csv` with exactly one header row.

This supports rerunning a single sweep without corrupting or duplicating unrelated results.

## 16. CSV edge cases

### Canonical CSV does not exist

If `report/report.csv` does not exist, merging a temporary CSV creates it and writes the header once.

### Canonical CSV exists and contains other languages

If rerunning only:

```bash
bench_bs_sweep cpp hello_sine
```

existing Mojo rows are preserved.

Only rows matching the incoming C++ buffer-sweep keys are replaced.

### Canonical CSV exists and contains another sweep

If rerunning only:

```bash
bench_bs_sweep cpp hello_sine
```

existing C++ sample-rate-sweep rows are preserved.

Only C++ buffer-sweep rows with matching keys are replaced.

### Temporary CSV is empty

If a temporary CSV is empty, the merge should fail or warn clearly.

It should not silently remove canonical rows.

### Backend writes duplicate rows inside one temporary CSV

`bench.py` should resolve duplicates by merge key before merging.

The last row for a key may win, but this should be reported as a warning.

### Schema mismatch

If the temporary CSV has the wrong number of fields or cannot be parsed using the canonical schema, the
merge should fail.

The canonical CSV should not be modified.

## 17. CSV ownership summary

Backend C++/Mojo:

```text
append one data row to CSV_PATH when WRITE_CSV is enabled
```

Shell scripts:

```text
decide when CSV writing is enabled
choose the temporary CSV path
remove stale temporary CSV before a structured run
call bench.py to merge temporary CSV into report/report.csv
```

Python `bench.py`:

```text
own the canonical header
own the canonical schema
own replacement/merge behavior
own sorting
own plotting data preparation
```

## 18. `.tab` report policy

Every benchmark case may produce a `.tab` report.

Single-case runs should always produce `.tab` files.

Structured runs should also produce `.tab` files for inspection/debugging.

`.tab` files are language-specific and stored under:

```text
report/cpp/
report/mojo/
```

The `.tab` files are not the canonical dataset. They are human-readable logs.

The canonical dataset is `report/report.csv`.

## 19. Single-case behavior

Single-case runs are primarily for debugging.

Example:

```bash
bench_case mojo hello_sine buffer_sweep f64 O3 96000 128
```

Expected behavior:

- build selected binary;
- run selected binary;
- write selected `.tab` report;
- print the report to stdout;
- do not write or merge CSV by default.

An explicit internal or advanced option may enable CSV writing for a single case, but this should not be the
public default.

## 20. Sweep behavior

Sweeps are structured benchmark operations and should update the canonical CSV.

Example:

```bash
bench_bs_sweep cpp hello_sine
```

Expected behavior:

1. remove the matching temporary CSV;
2. run all benchmark configurations for that sweep;
3. each backend execution appends one row to the temporary CSV;
4. write `.tab` reports for each case;
5. merge the temporary CSV into `report/report.csv`;
6. preserve unrelated existing canonical CSV rows.

## 21. Full benchmark behavior

The full benchmark runner should be implemented either as:

```bash
bench_all all hello_sine
```

or as a script:

```bash
script/all.sh hello_sine
```

Expected behavior:

- optionally clean reports first;
- run all configured sweeps;
- run all selected languages;
- produce `.tab` reports;
- produce or update `report/report.csv`;
- optionally generate plots.

Whether `bench_all` clears the canonical CSV or incrementally updates it should be explicit.

Suggested default:

- `bench_all` updates by merge, preserving unrelated DSP rows;
- `script/all.sh --fresh` clears `report/report.csv` before running.

## 22. `bench.py`

`bench.py` is the Python utility for CSV and plots.

It should provide at least two operations:

```bash
pixi run python script/bench.py merge ...
pixi run python script/bench.py plot ...
```

### Merge command

Suggested interface:

```bash
pixi run python script/bench.py merge \
  --main report/report.csv \
  --tmp report/tmp/cpp_hello_sine_buffer_sweep.csv
```

The merge command owns:

- canonical header;
- canonical schema;
- reading headerless temporary CSV files;
- replacing rows by merge key;
- deterministic sorting;
- safe write-back.

### Plot command

Suggested interface:

```bash
pixi run python script/bench.py plot \
  --csv report/report.csv \
  --case buffer_sweep \
  --x buff_size \
  --y ns_per_frame \
  --series language,precision,opt \
  --out report/plots/buff_size_ns_per_frame.svg \
  --title "Faust benchmark: ns/frame by buffer size"
```

The plot command owns:

- reading the canonical CSV;
- filtering by `bench_case`;
- grouping by selected series columns;
- generating SVG plots.

## 23. `plot.sh`

`plot.sh` is a shell wrapper around the plot mode of `bench.py`.

Expected behavior:

```bash
script/plot.sh
```

or:

```bash
script/plot.sh report/report.csv
```

It should generate the standard plots:

```text
report/plots/buff_size_ns_per_frame.svg
report/plots/samp_rate_ns_per_frame.svg
```

It should call Python through Pixi:

```bash
pixi run python script/bench.py plot ...
```

## 24. `clean.sh`

`clean.sh` should provide cleanup functions and optionally direct CLI behavior.

Suggested functions:

```bash
bench_clean_bin
bench_clean_report
bench_clean_tmp
bench_clean_out
bench_clean_all
```

Cleanup rules:

- preserve required directories;
- preserve symlinks;
- remove generated files only;
- do not remove `src/`;
- do not remove `arch/cpp/`;
- do not remove `arch/mojo` symlink;
- do not remove `pixi.toml` or `pixi.lock`.

Suggested cleanup behavior:

```text
bench_clean_bin      -> remove bin/*
bench_clean_tmp      -> remove report/tmp/*
bench_clean_report   -> remove report/cpp/*, report/mojo/*, report/plots/*, report/report.csv
bench_clean_out      -> remove generated files in out/cpp and out/mojo, preserving directories/symlinks
bench_clean_all      -> all of the above
```

## 25. Materialization policy

Generated `.cpp` and `.mojo` files may be materialized in `out/`.

The generation step is out of scope for now, but the benchmark scripts should be compatible with both
workflows:

1. generated source already exists in `out/`;
2. generated source is created by a later script and optionally kept.

Future generation scripts may expose options such as:

```text
--keep
--clean-generated
--materialize
```

Current benchmark scripts should assume source files are already present at their derived paths.

## 26. Error handling

Scripts should fail early and clearly.

Recommended shell settings:

```bash
set -euo pipefail
```

Useful checks:

- unsupported language;
- unsupported precision;
- unsupported optimization level;
- missing generated source file;
- missing `arch/mojo` symlink;
- missing report directories;
- failed build;
- failed benchmark execution;
- empty temporary CSV after a structured run;
- failed CSV merge.

## 27. Public workflow examples

Interactive setup:

```bash
cd architecture/_bench
source script/source.sh
```

Run one debug case without touching CSV:

```bash
bench_case cpp hello_sine buffer_sweep f32 O3 96000 128
```

Run one structured sweep and update canonical CSV:

```bash
bench_bs_sweep cpp hello_sine
```

Run sample-rate sweep for Mojo:

```bash
bench_sr_sweep mojo hello_sine
```

Run all sweeps for all languages:

```bash
bench_all all hello_sine
```

Generate plots:

```bash
script/plot.sh report/report.csv
```

Clean generated reports:

```bash
source script/source.sh
bench_clean_report
```

## 28. Design summary

The benchmark system should follow this ownership model:

```text
source.sh   -> environment, paths, setup, public functions
bench.sh    -> build/run/sweep logic
bench.py    -> CSV schema, merge, plotting
plot.sh     -> standard plot wrapper
clean.sh    -> cleanup functions
all.sh      -> final high-level runner
```

CSV ownership must remain centralized:

```text
backend: append headerless rows only
shell: decide when and where CSV rows are produced
Python: own canonical CSV schema, header, merge, and plots
```

Single cases are for debugging and should not mutate the canonical CSV.

Sweeps are structured benchmark operations and should update the canonical CSV through temporary CSV staging
and Python-level merge.
