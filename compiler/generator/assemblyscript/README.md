# AssemblyScript Backend (`-lang asc`)

This backend generates AssemblyScript source code from Faust FIR.

## Status

Experimental and incomplete.

Currently implemented:

- backend selection with `-lang asc`
- scalar code generation path
- basic type and instruction emission
- experimental impulse-tests smoke target:
  - `make -C tests/impulse-tests asc`
  - or directly:
    - `make -C tests/impulse-tests -f Make.assemblyscript assemblyscript`
  - Node-based source runner:
    - `tests/impulse-tests/tools/impulseasc.js`
  - quick reference subset check:
    - `make -C tests/impulse-tests -f Make.assemblyscript assemblyscript-compare-quick compare=1`

Not implemented yet:

- vector/OpenMP/scheduler code generation (`-vec`, `-omp`, `-sch`)
- full soundfile/runtime integration
- stable host ABI for generated `.ts` to `.wasm` modules

## Current ABI Contract (Phase 1)

The generated AssemblyScript currently follows this interface:

- one exported DSP class per Faust program:
  - `export class <name> { ... }`
- public instance methods:
  - `metadata(m: Meta): void`
  - `getJSON(): string`
  - `getSampleRate(): i32`
  - `getNumInputs(): i32`
  - `getNumOutputs(): i32`
  - `instanceResetUserInterface(): void`
  - `instanceClear(): void`
  - `instanceConstants(sample_rate: i32): void`
  - `instanceInit(sample_rate: i32): void`
  - `init(sample_rate: i32): void`
  - `compute(count: i32, inputs: Array<Array<f32|f64>>, outputs: Array<Array<f32|f64>>): void`
- public static methods:
  - `classInit(sample_rate: i32): void`
- global helper functions may be emitted for FIR function definitions (for example `fmod` wrappers).

Runtime/data assumptions in this phase:

- scalar DSP path only (`-vec`, `-omp`, `-sch` are rejected).
- floating-point mode maps from Faust:
  - `-single` -> `f32`
  - `-double` -> `f64`
- audio I/O is modeled as nested arrays (`inputs[ch][frame]`, `outputs[ch][frame]`).
- internal delay/state arrays are emitted as class fields and initialized with fixed sizes.
- no soundfile runtime integration.
- current impulse runner is source-level (transpiled to JS), not a true AssemblyScript/WASM runtime.
- no constructor is emitted; initialization is done via `classInit(sample_rate)` + `instanceInit(sample_rate)` / `init(sample_rate)`.

Expected `asc` invocation pattern:

`asc <generated.ts> -O --runtime stub -o <out.wasm>`

Notes on `asc` warnings:

- warning `AS235` ("Only variables, functions and enums become WebAssembly module exports") is expected
  with the current `export class <name>` shape and is non-blocking for impulse tests.

This ABI is still experimental and may change before parity-level stabilization.

## Build Integration

Enable the backend with CMake backend selection variable:

- `AS_BACKEND` (`COMPILER`, `STATIC`, `DYNAMIC`, or `OFF`)

The backend is included by the `scan_backends` function in `build/misc/llvm.cmake`.

## Notes

The generated code shape and runtime contract should still be considered subject to change.

Known current limitation:

- generated class export shape is not yet a finalized WASM host ABI.
