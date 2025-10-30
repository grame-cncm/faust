# Faust Parser Modernization Plan

## 1. Current-State Analysis
- **Legacy Path Handling** – `parser/enrobage.cpp` manually composes file paths using `fopen`, `chdir`, and raw `getcwd` buffers, storing search roots as strings inside `global::gImportDirList`. This approach is brittle (no RAII), thread-hostile (process-wide directory changes), and ignores Unicode or platform-specific nuances.
- **Duplicated Utilities** – Helpers such as `fileBasename`, `fileDirname`, and `buildFullPathname` reimplement functionality offered by `std::filesystem`, relying on ad-hoc separator macros and custom logic for Windows drive prefixes.
- **FILE*-Centric IO** – `SourceReader` and related components still pivot on `FILE*` and C-level globals (`FAUSTin`, `FAUSTfilename`). That complicates error handling, makes resource management manual, and prevents reuse of modern C++ features.
- **Coupled Import Resolution** – URL checks, file checks, and directory stack updates are interwoven, making it hard to test or evolve the import process independently of the parser.

## 2. Rewrite Objectives (C++17 Filesystem)
1. **Adopt `std::filesystem::path`** for all path manipulation: parent directories, basenames, stems, and canonicalisation.
2. **Eliminate `chdir`/`getcwd` usage** by joining paths (`dir / filename`) and probing with `fs::exists`, `fs::canonical`, or `fs::weakly_canonical`.
3. **Transition to RAII streams** (`std::ifstream`, `std::ofstream`) while keeping Flex interfaces working via adapters (e.g. a thin helper that opens a `FILE*` using the resolved `fs::path` only where the lexer requires it).
4. **Centralise resolution logic** in a dedicated service (e.g. `FileResolver`) that operates on vectors of `fs::path`, keeps caches of resolved imports, and returns structured errors.
5. **Refine global state** to store search directories as `fs::path` and expose helper methods (`addImportDir`, `importDirectories`, etc.) so other subsystems can interact without string munging.
6. **Improve diagnostics** by reporting canonical paths and preserving original requests, especially when multiple search roots are involved.

## 3. Testing Strategy (Prepare Before Refactoring)
- Establish this coverage up front so baseline behaviour is locked before any rewrite begins.
### Unit Tests
- **FileResolver coverage**: mock search roots, verify resolution precedence, canonicalisation, and cache updates. Include edge cases (relative traversals, symlinks, non-existent files).
- **Path Utilities**: tests for metadata extraction (`stem`, `filename`, `parent_path`) across POSIX and Windows semantics.
- **Error Handling**: ensure descriptive exceptions/messages when resolution fails or permissions are insufficient.

### Integration Tests
- **Parser Imports**: run the parser on sample projects with nested imports, relative paths, and architecture lookups; compare generated AST/signals before and after the refactor.
- **Mixed Protocols**: confirm that `file://` URLs map correctly to local paths and that HTTP imports still pass through fetcher stubs.
- **Regression Suite**: reuse existing compiler tests (`make check`, existing CI scripts) to guard against behavioural deviations.

### Cross-Platform Validation
- Validate on macOS/Linux and Windows, paying attention to drive-letter handling, UNC paths, and symlink resolution.
- Run tests under both UTF-8 and locale-sensitive directories (paths containing non-ASCII characters) to ensure Unicode-safe behaviour.

### Performance Checks
- Benchmark import-heavy workloads to ensure the resolver’s canonicalisation and caching do not introduce regressions.
- Profile optional features (e.g. repeated inclusion detection) to confirm they function with the new path abstraction.

## 4. Proposed Refactoring Steps
1. **Introduce `FileResolver` Module**
   - Encapsulate search roots, canonicalisation, and relative path updates.
   - Provide APIs: `resolve_import`, `resolve_architecture`, `add_search_root`, `resolved_history`.
2. **Migrate Utility Functions**
   - Replace `fileBasename`, `fileDirname`, `buildFullPathname`, and `isAbsolutePathname` with `std::filesystem` equivalents.
   - Update metadata extraction in `SourceReader` to derive `stem`, `filename`, and `parent_path` through the new API.
3. **Rewrite `fopenSearch` and Friends**
   - Reimplement import search using `FileResolver` without `chdir`.
   - Ensure the directory auto-discovery (adding containing folder after a successful import) uses `fs::path::parent_path()`.
4. **Transition `SourceReader` IO**
   - Wrap `std::ifstream` in a RAII struct that exposes `FILE*` to Flex or integrate Flex's alternative `yyset_in`.
   - Convert `gGlobal->gInputFiles` and related lists to store `fs::path` (or strings derived from them on demand).
5. **Decouple Network Fetching**
   - Isolate the URL-handling code path so local filesystem logic does not depend on `http_fetch`.
6. **Update Global Initialisation**
   - Canonicalise directories during startup; ensure serialization/deserialization of paths works across platforms.
7. **Retire Legacy Helpers**
   - Remove obsolete path utilities once all consumers use the modern code.
8. **Documentation & Migration Notes**
   - Record API changes and migration steps for downstream tools or scripts that rely on the old behaviour.

## 5. Prompt Sequence for Incremental Implementation
0. **Establish Testing Baseline**
   - Prompt: “Set up the parser testing harness: add unit-test scaffolding for `FileResolver`, create sample DSP projects for integration checks, and build a Makefile-driven test target developers can run locally before each step.”
   - Tests: run the new make-based unit/integration suite to capture baseline results; document any gaps or flaky cases.
1. **Create FileResolver Skeleton**
   - Prompt: “Implement a `parser/FileResolver` class using `std::filesystem` to manage search directories and resolve import paths; include initial unit tests.”
   - Tests: run new unit tests for resolver logic.
2. **Refactor Path Utilities**
   - Prompt: “Replace legacy basename/dirname helpers with `std::filesystem` operations throughout `parser/enrobage.cpp`; adjust include paths and add coverage for metadata extraction.”
   - Tests: run resolver tests, plus targeted parser unit tests if available.
3. **Reimplement `fopenSearch` Flow**
   - Prompt: “Rewrite `fopenSearch` and related helpers to use `FileResolver`; ensure the global import directory list is updated via the new API.”
   - Tests: resolver tests + parser integration sample (compile a simple Faust file).
4. **Modernise `SourceReader` IO**
   - Prompt: “Update `SourceReader` to open files via `std::ifstream` (or a RAII adapter) and feed the lexer accordingly; replace raw strings with `fs::path` where feasible.”
   - Tests: parser integration tests (import scenarios, error reporting).
5. **Adapt Global State**
   - Prompt: “Modify `global` to store search directories as `std::filesystem::path` values and expose helper methods for mutation.”
   - Tests: run compiler CLI smoke tests, verify options like `-I` and `-A`.
6. **Isolate Network Fetching**
   - Prompt: “Extract URL-handling into a dedicated layer, ensuring filesystem resolver paths remain clean; adjust tests accordingly.”
   - Tests: integration tests covering HTTP/file imports (using stubs).
7. **Cleanup & Documentation**
   - Prompt: “Remove deprecated helpers, update documentation/README, and note migration requirements; ensure full test suite passes.”
   - Tests: entire regression suite, documentation lint if applicable.

Each step should produce targeted documentation updates (e.g. resolver README, migration notes) and confirm via designated tests before moving on. This keeps the rewrite incremental, testable, and reviewable.
