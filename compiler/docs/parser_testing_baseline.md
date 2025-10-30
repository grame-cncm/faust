# Parser Testing Baseline Setup

- Introduced `parser/file_resolver.hh` with a placeholder `FileResolver` interface so the upcoming rewrite has a compilation target while real logic is developed.
- Created `tests/parser/` harness:
  - `Makefile` providing `make run` and `make baseline` targets for local execution.
  - `README.md` documenting harness usage.
  - Fixtures under `fixtures/` (currently a simple DSP file and an architecture directory placeholder) to back future integration tests.
- Added `tests/parser/test_file_resolver.cpp`, which:
  - Checks that import/architecture directories can be registered.
  - Confirms `resolveImport` currently throws until implemented, preserving visibility of unimplemented sections.
- Captured baseline results by running `cd tests/parser && make clean && make run`; the suite builds the test binary and reports successful completion.

## FileResolver Implementation (Step 1)
- Replaced the placeholder with a filesystem-aware resolver that:
  - Normalises search roots, removes duplicates, and ignores URL-style inputs.
  - Resolves relative/absolute filenames against the registered import or architecture directories, returning canonical paths when matches are found.
- Expanded `tests/parser/test_file_resolver.cpp` to validate:
  - Directory registration and duplicate filtering.
  - Resolution of relative, normalised, absolute, and direct paths.
  - Architecture lookups using a new `fixtures/arch/minimal.arch`.
  - Failure cases (missing files, URL schemes).
- Added the minimal architecture fixture to support the tests.
- Re-ran `cd tests/parser && make clean && make run` to confirm all resolver tests pass.

## Path Utility Refactor (Step 2)
- Modernised `parser/enrobage` path helpers to rely on `std::filesystem`:
  - `fileBasename`/`fileDirname` now operate on `std::string` inputs with inline implementations using `fs::path`.
  - Legacy manual separator handling and ad-hoc absolute-path detection were replaced with `std::filesystem` queries.
  - `buildFullPathname` now builds canonical absolute paths via `fs::absolute`/`fs::weakly_canonical`.
- Updated call sites (Documentator, parser tests) to use the new signatures.
- Extended the parser test harness with coverage for the path helpers.
- Executed `cd tests/parser && make clean && make run` to verify the suite after the refactor.

## Resolver-Driven File Opening (Step 3)
- Replaced the legacy `chdir`-based search loops in `parser/enrobage.cpp` with `FileResolver`-powered lookups for both imports and architectures.
- Added canonical directory tracking helpers so directories discovered via successful resolutions are re-inserted into `gGlobal` without duplication.
- Updated `openArchStream`/`fopenSearch` to open canonical paths returned by the resolver and drop the manual `buildFullPathname`/`fopenAt` chain.
- Existing `global` directory lists now seamlessly feed the resolver, keeping CLI behaviour intact while benefiting from canonicalisation at open time.
- Re-ran `cd tests/parser && make clean && make run` to ensure the harness passes with the new resolver-integrated flow.

## Directory utility helpers (Step 4)
- Extracted canonical directory logic into shared helpers inside `parser/file_resolver.hh` so both the resolver and tests share a single implementation.
- Updated tests to verify duplicate suppression and canonicalisation behaviour for the new helper.
- Re-ran `cd tests/parser && make clean && make run` to confirm the suite still passes.

## Canonical global search paths (Step 5)
- Normalised every directory added to `gImportDirList` and `gArchitectureDirList` (command-line, env vars, defaults) via the shared helper so the resolver receives canonical strings.
- Updated master/Faust directory bookkeeping to store canonicalised paths up front.
- Re-ran `cd tests/parser && make clean && make run` to ensure the harness still passes.

## Current status
- Parser still relies on string-based globals; lifetime fixes remain pending after identifying crash regressions.
- FileResolver integrations cover import/architecture lookups, but SourceReader still uses legacy FILE* management.

## Suggested next steps
1. Build focused SourceReader tests using temporary files to reproduce pointer-lifetime bugs deterministically.
2. Introduce a small parser context struct carrying canonical filename strings instead of mutating global state directly.
3. Replace remaining raw `FILE*` usage with RAII wrappers once tests confirm the approach.
4. Extend resolver helpers to feed other subsystems (Documentator, libcode) so canonicalisation is guaranteed end-to-end.
5. Consider a high-level integration test that compiles representative DSPs to catch regressions before releases.
