# Faustgen tests and issue registry

This document precisely describes the regressions, robustness defects, and
build problems identified while analyzing `faustgen`. Each entry names the test
that reproduces the issue or locks in the expected behavior.

## Running the tests

From `embedded/faustgen`:

```bash
make test
```

The suite requires Python 3 and a C++11 compiler available as `c++`. To enable
AddressSanitizer and UndefinedBehaviorSanitizer:

```bash
FAUSTGEN_TEST_CXXFLAGS="-fsanitize=address,undefined -fno-omit-frame-pointer" make test
```

The tests extract definitions directly from the production C++ files, compile
them with minimal substitutes for the Max and libfaust APIs, and then execute
the native scenarios. They therefore do not maintain a second implementation
of the logic under test.

## Test naming

- `test_factory_dictionary.py`: Max persistence, machine-code cache, and
  compatibility with older patches;
- `test_factory_core.py`: options, buffers, paths, source editing, and compiler
  option messages;
- `test_factory_dsp.py`: factory selection, fallback, precision, and polyphony;
- `test_factory_files.py`: change detection and file input/output;
- `test_factory_commands.py`: macOS/Windows commands, SVG, documentation, and
  libraries;
- `test_faustgen_runtime.py`: parameters, MIDI, OSC, audio processing,
  multichannel behavior, and teardown;
- `cpp_test_support.py`: extraction, compilation, and execution of the C++
  harnesses.

The `file.py::Class::method` notation below identifies the Python test. Scenario
labels match the comments in the C++ `CASES` program in the corresponding file.

## Fixed bugs and corresponding tests

### FG-001 — Editable source disappeared when a valid cache was loaded

**Symptom.** When reopening a patch containing valid `machinecode`, the DSP
could be recreated from the cache while the Faust text and library paths were
not necessarily restored. A subsequent save could then replace the editable
source with the default value.

**Cause.** The successful `machinecode` loading path did not systematically
continue through `load_source_code()` and `load_library_paths()`.

**Risk.** Loss of the editable program after several save/close/reopen cycles,
even though the cached DSP continued to work.

**Verified fix.** After copying the cache, control always reaches
`read_sourcecode`; the UTF-8 source and paths are restored independently of the
cache.

**Test.**
`test_factory_dictionary.py::DictionaryRestoreTest::test_cached_patch_retains_editable_source`,
scenario “Cached DSP and editable source must survive repeated save/reopen
cycles.” Three cycles are executed for both the LLVM and interpreter backends.

### FG-002 — Source-buffer leak while loading the default code

**Symptom.** Each call to `default_source_code()` could abandon the handle
already stored in `fSourceCode`.

**Cause.** A new handle was assigned without calling `free_sourcecode()`. In
particular, the constructor creates an empty handle before any restoration.

**Risk.** Memory leak on every fallback or repeated restoration.

**Verified fix.** `default_source_code()` now frees the previous handle first.

**Test.** `test_factory_core.py::FactoryCoreTest::test_factory_core_behaviour`,
scenario “Installing default source replaces any previous allocation without
leaking it.” The free counter must increase by exactly one.

### FG-003 — Leaks during repeated restoration of the same dictionary

**Symptom.** Calling `getfromdictionary()` several times on a named factory
increased the number of live handles.

**Cause.** `load_source_code()` and the `machinecode` loading path replaced
existing handles without freeing them.

**Risk.** Memory growth when a shared factory receives several restorations.

**Verified fix.** The source is freed at the beginning of `load_source_code()`
and the cache at the beginning of `getfromdictionary()`.

**Test.**
`test_factory_dictionary.py::DictionaryRestoreTest::test_cached_patch_retains_editable_source`,
scenario “Reapplying dictionaries to one named factory replaces, rather than
leaks, source/cache buffers.” The number of live handles must remain stable.

### FG-004 — An old cache survived failed validation of a new patch

**Symptom.** After a valid load, applying a dictionary produced on another
machine could leave `fBitCode` pointing to the old cache.

**Cause.** Error paths for `serial_number`, version, or missing keys jumped to
source loading without first invalidating the current cache.

**Risk.** Execution of a module that does not correspond to the dictionary that
was just loaded.

**Verified fix.** `getfromdictionary()` calls `free_bitcode()` before performing
any validation.

**Test.** The same test and scenario as FG-003: after a valid dictionary, a
dictionary with a different machine number must produce
`fBitCode == nullptr` and `fBitCodeSize == 0` while preserving its source.

### FG-005 — Negative or inconsistent dictionary sizes

**Symptom.** `sourcecode_size` and `machinecode_size` were used directly to
allocate and then copy dictionary strings.

**Cause.** There was no sign validation and no comparison with the actual string
length.

**Risks.** A negative size can become an extremely large allocation when
converted to an unsigned size. A size larger than the string can cause an
out-of-bounds read in `sysmem_copyptr`. A smaller size creates truncated content.

**Verified fix.** Negative sizes are rejected. The machine-code size must equal
`strlen(machinecode)`. The source accepts either its exact length or that length
plus one for FG-007 compatibility, and is then normalized.

**Test.**
`test_factory_dictionary.py::DictionaryRestoreTest::test_cached_patch_retains_editable_source`,
scenario “Corrupt or inconsistent lengths are rejected before
allocation/copying.” It covers a negative source size, an oversized source
length, a negative machine-code size, and an inconsistent machine-code length.

### FG-006 — Invalid `sample_format` value accepted as an enum value

**Symptom.** Any saved integer value was written directly into `fSampleFormat`.

**Cause.** `dictionary_getlong()` wrote into the enum through a pointer cast,
without checking the range.

**Risks.** An impossible state and an indeterminate precision-adapter choice
during DSP creation. The pointer cast also depended on the in-memory
representation of the enum.

**Verified fix.** The value is read into a separate `t_atom_long`, validated
between `kFloat` and `kNone`, and then converted with `static_cast`. Invalid
values produce `kNone`.

**Test.** The same corrupt-dictionary scenario as FG-005, using the values `-1`
and `99`.

### FG-007 — Compatibility with legacy sizes that include the trailing NUL

**Symptom.** Older file imports could save
`sourcecode_size == strlen(source) + 1`. Strict length validation would have
rejected otherwise valid source code.

**Cause.** `compile_file()` used `sysmem_handlesize()` after a read with
`TEXT_NULL_TERMINATE`; that size may include the NUL byte added by Max.

**Risk.** Silent replacement of an older program with `DEFAULT_SOURCE_CODE`
during a version upgrade.

**Verified fix.** The loader accepts both representations and normalizes
`fSourceCodeSize` to `strlen(source)`. New imports use
`strlen(*fSourceCode)` directly.

**Tests.**

- `test_factory_dictionary.py::DictionaryRestoreTest::test_cached_patch_retains_editable_source`,
  scenario “Older file imports counted the null terminator”;
- `test_factory_files.py::FactoryFilesTest::test_file_operations`, scenario
  “Changed files replace source/cache,” which checks the exact UTF-8 length of
  the imported text.

### FG-008 — Incomplete invariant in `free_bitcode()`

**Symptom.** If `fBitCode` was already null while `fBitCodeSize` was nonzero,
`free_bitcode()` preserved the stale size.

**Cause.** Resetting the size and pointer occurred only inside the
`if (fBitCode)` block.

**Risk.** `create_dsp_aux()` could believe a cache existed and invoke the loader
with a null pointer.

**Verified fix.** The size and pointer are reset whether or not a handle needed
to be freed.

**Test.** `test_factory_core.py::FactoryCoreTest::test_factory_core_behaviour`,
scenario “Buffer release is idempotent and always restores the size/pointer
invariant.”

### FG-009 — Possible null-source dereference while saving

**Symptom.** `appendtodictionary()` checked only `fSourceCodeSize` before
dereferencing `fSourceCode`.

**Cause.** The pointer/size invariant was assumed, but several fallback or error
paths can temporarily break it.

**Risk.** Crash while saving a patch whose in-memory state is only partially
constructed or is damaged.

**Verified fix.** Source is written only when the handle is non-null and the
size is strictly positive.

**Test.**
`test_factory_dictionary.py::DictionaryRestoreTest::test_cached_patch_retains_editable_source`,
scenario “A damaged in-memory state must not dereference a null source handle
while saving.” The test forces `fSourceCode == nullptr` with a size of 12 and
verifies that no source key is added.

### FG-010 — Optimization level persisted after removing `-opt`

**Symptom.** After `compileoptions -opt 4`, a later compilation without `-opt`
continued to use level 4.

**Cause.** `default_compile_options()` reset the options and sample format, but
not `fOptLevel`.

**Risk.** The result depended on message history rather than the current
options.

**Verified fix.** Each rebuild starts with
`fOptLevel = LLVM_OPTIMIZATION`.

**Test.** `test_factory_core.py::FactoryCoreTest::test_factory_core_behaviour`,
scenario “Removing -opt restores the documented maximum/default optimization.”

### FG-011 — A trailing `-opt` without a value dereferenced `end()`

**Symptom.** The message `compileoptions -opt` could crash or read invalid
memory.

**Cause.** The iterator was incremented and then dereferenced without checking
whether a value followed.

**Risk.** Undefined behavior in the compilation thread.

**Verified fix.** The value is checked before calling `atoi`; otherwise, a
diagnostic is posted and the default level is preserved.

**Test.** `test_factory_core.py::FactoryCoreTest::test_factory_core_behaviour`,
scenario “A malformed trailing -opt must not dereference fOptions.end().” This
case also passes under UndefinedBehaviorSanitizer.

### FG-012 — Closing an uninitialized file handle

**Symptom.** If `path_opensysfile()` failed during `read`,
`sysfile_close(file_handle)` was still called.

**Cause.** `file_handle` was uninitialized and the close call occurred after the
shared success/error block.

**Risk.** Crash or closure of an arbitrary resource.

**Verified fix.** The handle is initialized to zero and closed only on the path
where opening succeeded.

**Test.** `test_factory_files.py::FactoryFilesTest::test_file_operations`,
scenario “An open failure never attempts to close an uninitialized handle.” The
close counter must remain unchanged.

### FG-013 — Nonnumeric type accepted for a standard parameter

**Symptom.** A symbol atom sent to a parameter was interpreted as a float by
reading `a_w.w_float` from the wrong branch of the union.

**Cause.** The code distinguished only `A_LONG` from “every other type.”

**Risk.** An indeterminate value was injected into the DSP.

**Verified fix.** Only `A_LONG` and `A_FLOAT` are accepted; other types produce a
diagnostic without changing the control.

**Test.** `test_faustgen_runtime.py::FaustgenRuntimeTest::test_runtime_behaviour`,
the `gain` parameter scenario using the `not-a-number` symbol. The number of
control writes must remain unchanged.

### FG-014 — MIDI byte types were not validated

**Symptom.** `midievent` always read `a_w.w_long`, even for a symbol or float
atom.

**Cause.** Only the arity was examined.

**Risk.** Indeterminate MIDI bytes were sent to the handler, with the type and
channel calculated from the wrong union branch.

**Verified fix.** Messages containing one to three bytes now require `A_LONG`
for every atom.

**Test.** `test_faustgen_runtime.py::FaustgenRuntimeTest::test_runtime_behaviour`,
invalid MIDI scenario `{symbol "note", integer 1}`. No new event may be
recorded.

### FG-015 — The test runner depended on its working directory

**Symptom.** From the repository root, Clang could include the local `./version`
script instead of the libc++ `<version>` header.

**Cause.** On some machines, `CPLUS_INCLUDE_PATH` or `C_INCLUDE_PATH` contains an
empty entry, which denotes the current working directory.

**Risk.** The test failed with preprocessor errors inside the `version` shell
script even though the C++ harness was correct.

**Verified fix.** `cpp_test_support.compile_and_run()` removes empty entries from
`CPATH`, `CPLUS_INCLUDE_PATH`, and `C_INCLUDE_PATH`, then compiles from the
harness's temporary directory.

**Corresponding test.** The entire suite exercises this path. It has been run
successfully both from the repository root with
`python3 -m unittest discover -s embedded/faustgen/tests -v` and from the module
with `make test`.

## Important regressions covered

The following behaviors did not all require a new fix, but they are explicitly
locked down because a regression would be serious.

### RG-001 — DSP creation priority

`test_factory_dsp.py::FactoryDSPTest::test_dsp_creation_paths` verifies the
following order: already allocated factory, machine-code cache, source
compilation, and finally the silent fallback DSP. Input/output dimensions and
JSON rebuilding are checked on every exit path.

### RG-002 — Float/double adaptation and polyphony

The same test verifies that the `float -> double` adapter is placed before
`mydsp_poly`, that explicit polyphony overrides the `nvoices` metadata, and that
negative or nonnumeric metadata does not create a polyphonic DSP.

### RG-003 — Source editing and cache invalidation

`test_factory_core.py::FactoryCoreTest::test_factory_core_behaviour` verifies
that identical text triggers no action, while modified UTF-8 text frees the
factory and bitcode, regenerates codebox output with the correct arguments, and
notifies every instance.

### RG-004 — `compileoptions` parsing

The same test covers symbols, integers, invalid floats, the `nc` option,
recompilation, cache invalidation, and instance notification.

### RG-005 — Shell-command safety

`test_factory_commands.py::FactoryCommandsTest::test_commands_for_all_platform_and_backend_branches`
compiles four variants: macOS/Unix and Windows, each using LLVM and the
interpreter. It checks that an unsafe path produces no command, as well as
quoting, fallback between paths, the SVG lifecycle, and the complete library
list. The exhaustive matrix of rejected characters (`"`, backtick, `$`, `|`,
`&`, `;`, `<`, `>`, `%`, LF, CR, and DEL) is in
`test_factory_core.py::FactoryCoreTest::test_factory_core_behaviour`, scenario
“Pure pathname helpers and shell-safety validation.”

### RG-006 — Toggle without an argument array

`test_faustgen_runtime.py::FaustgenRuntimeTest::test_runtime_behaviour` invokes
a button with `ac == 0` and `av == nullptr`. It verifies the exact `0 -> 1 -> 0`
sequence and balanced UI locking.

### RG-007 — OSC and interface lifecycle

The same test rejects incorrect OSC arities and types, verifies the eleven
arguments passed to `OSCUI`, and then checks teardown order: MC adapter before
DSP, DSP before MIDI, MIDI before OSC, and OSC before the control UI.

### RG-008 — Real-time audio callback

The same test verifies that outputs are always zeroed, including while muted or
when the audio lock is unavailable; that the DSP, control outputs, and
`GUI::updateAllGuis()` are called only after the lock has been acquired; and
that the multichannel adapter is reused while the topology remains unchanged.

### RG-009 — File reading and writing

`test_factory_files.py::FactoryFilesTest::test_file_operations` covers:

- identical, modified, and unreadable files;
- cancellation of load and save dialogs;
- files that are missing, cannot be opened, or cannot be created;
- overwriting an existing file and creating a new file;
- rewinding a file after calculating its SHA-1;
- adding the DSP's directory to the `-I` list;
- freeing the cache and notifying instances after a modification.

## Build problems observed with the real SDK

These issues depend on the local installation and are not simulated by the unit
tests. They were verified with a real build.

### BUILD-001 — The Max SDK repository root is not directly usable as `MAXSDK`

With `/Users/letz/Developpements/max-sdk`, CMake incorrectly looks for
`/Users/letz/Developpements/max-sdk/max-includes/ext.h`. In this SDK checkout,
the path compatible with the `CMakeLists.txt` is:

```text
/Users/letz/Developpements/max-sdk/source/max-sdk-base/c74support
```

The initial diagnostic was `fatal error: 'ext.h' file not found`. Both source
files compile with the subdirectory above.

### BUILD-002 — `faust-config --system-libs` omits LLVM on this installation

The static `/usr/local/lib/libfaustwithllvm.a` library contains unresolved LLVM
references, while `faust-config --system-libs` returns only
`-lm -lz -lcurses -lxml2`. Linking requires LLVM 23 from MacPorts:

```text
-L/opt/local/libexec/llvm-devel/lib -lLLVM-23git
```

The bundle must also contain the corresponding rpath:

```text
-Wl,-rpath,/opt/local/libexec/llvm-devel/lib
```

After adding these options to `CMAKE_MODULE_LINKER_FLAGS`, the arm64 Mach-O
bundle links successfully and contains an `LC_RPATH` pointing to that directory.

### BUILD-003 — The linker-generated signature did not seal resources

Immediately after linking, `codesign --verify --deep --strict` reported:
`code has no resources but signature indicates they must be present`. The
command also used by the project's installation step fixes the bundle:

```bash
codesign --sign - --deep --force build/faustgen~.mxo
```

Strict verification then succeeds; 43 resources are sealed and the bundle
identifier is `com.grame.faustgen-`.

## Remaining limitations

The harnesses validate the real business logic, but not bundle loading inside a
Max process. The following scenarios must therefore still be tested manually in
Max:

- actual instantiation of `faustgen~` and `mc.faustgen~` in a patcher;
- interaction with the `jed` editor, JSUI, and an RNBO `codebox~` object;
- audio and MIDI using system devices;
- actual OSC network transport;
- native dialogs and effective opening of SVG/PDF files and editors;
- restoration of a real historical patch produced on another machine.

These limitations are intentional: automating these scenarios requires a Max
host and a separate integration-test infrastructure.
