# Testing the Faust compiler

This document states what has to be checked before a compiler change is
trusted, and how to run each check so that its result means something.

## The four criteria, in order of importance

1. **Accept and reject.** Every correct program must compile, every
   incorrect program must be rejected, and both in a reasonable time.
2. **Preserve the semantics.** Whatever the compiler's internal
   strategies and whatever the compilation options, a given program must
   produce the same samples.
3. **Speed of the generated code.**
4. **Speed of compilation** — a real criterion, the least critical of the
   four.

This document covers criteria 1 and 2. Criteria 3 and 4 obey different
rules (paired measurement, named C++ judges, reserved machines) and belong
to a separate document.

> **The central invariant.** There is **one** reference set. It is
> produced once, by a trusted compiler, under the default options, and
> *every* option set of the compiler under test is compared against it.
> Not one reference set per backend, not one per mode. That is what
> criterion 2 says: the semantics depend neither on the backend, nor on
> vectorisation, nor on the scheduling strategy. A reference set per
> option would only check each option against itself.

## Gate 1 — the impulse suite

Reference responses are versioned in the repository, so this gate needs no
trusted compiler and is re-derivable from the commit alone.

```sh
rm -rf tests/impulse-tests/ir/          # discard the previous run
make -C tests/impulse-tests all         # everything (long)
make -C tests/impulse-tests help        # what else can be run
```

The two gates select their compiler by **opposite defaults**, which is
worth knowing before reading any result:

| gate | variable | default |
| :--- | :------- | :------ |
| impulse suite | `FAUST` | `../../build/bin/faust` — the tree you are in |
| library specs | `FAUST` | `faust` — the one in the `PATH`, i.e. installed |

So the same `make` command tests a different binary in each. Name the
binary explicitly in both, and have the report say which one was judged.

`all` chains seventeen targets: `cpp`, `cpp1`, `ocpp`, `c`, `c1`, `mute`,
`wasm`, `wast`, `llvm`, `llvm1`, `interp`, `interp1`, `rust`, `dlang`,
`nnx`, `linen`, `julia`. Several need toolchains that are not installed
everywhere, so running a subset is normal — but choose it knowingly:

- `cpp` alone covers twenty-five option sets, **float and double**,
  `-vec` at `lv 0` / `lv 1` / `vs 16` / `-fun`, `-sch`, `-omp`, plus
  `-uim`, `-it`, `-fp`, `-wall`, `-mcd 0`, `-mapp`, `-rui`, `-nvi`,
  `-dlt 0`, `-dlt 256`.
- `ocpp` covers the legacy backend, which the continuous integration
  never exercises.

Do not settle for the double-precision legs. A one-sample float bug can
live for weeks under a double-only gate; the harness has float legs, a
gate built on top of it must use them.

**Delete `ir/` before every run.** The suite writes each leg under a path
that spells out its options (`ir/cpp/double/vec/lv1/…`), so a change of
options cannot be mistaken for an up-to-date result — the libraries gate
has no such protection. But the path says nothing about the *compiler*:
run the same options with another binary and make finds the files already
there and does nothing. Hence the `rm -rf`.

**Always run with `-k`, and read the whole table.** A leg is one run of
`Make.gcc` — an output directory, a language, an architecture, the faust
options — and each leg is a target of its own, `leg/<outdir>`; a family
such as `cpp` is the list of its legs. So `-k` carries past a failing
leg and reports every failure at the end, which it could not do when the
legs were successive lines of one recipe: make abandons a recipe at its
first failing line, and `-k` only carries across targets. Until this
change, the `cpp` target stopped at its third leg on a real branch and
the other twenty-two never ran.

```sh
make -C tests/impulse-tests cpp ocpp -k -j 8 FAUST=<binary under test>
make -C tests/impulse-tests leg/cpp/double/vec/lv1 FAUST=<binary>   # one leg alone
make -C tests/impulse-tests legs                                     # the 113 legs
```

`-j` is shared with the legs through the jobserver, so the legs run in
parallel and the total stays bounded. A leg used by two families
(`cpp/double` by `cpp` and `travis`, for one) is defined once.

**Count what a leg produced.** Four programs are excluded by rules in
`Make.gcc` that succeed by printing a line, so the leg reports success
and the program is simply never tested. The count is the only trace:

| program | legs | reason |
| :------ | :--- | :----- |
| `prefix` | every C++ leg | issue #1071, whose title names only rust with `-vec` |
| `constant` | `cpp/double/mapp` | issue #1074 |
| `osc_enable` | `cpp/double/os` | broken with `-os` |
| `bs` | `cpp/double/os` | foreign variable `count` not allowed in that mode |

An exclusion is legitimate; an exclusion nobody can see is not. A leg
that yields 94 of 96 with no reported failure has silently dropped two
programs, and a report must say which ones and why.

## Gate 2 — the library specifications

The 1236 `*_test` specifications of the `libraries` sub-project are the
widest semantic gate available. Their reference outputs are **not**
versioned — they would take too much space — so they must be computed,
and that computation is where the validity of the whole gate is decided.

The trusted compiler is the latest released version. At the time of
writing: 2.88.0, `171b603ac93e65fa5ec047e13441d3969d1658c7`.

```sh
# 1. with the TRUSTED compiler installed, from the libraries directory
cd libraries
make reference                 # writes tests/reference/*.ref and tests/reference/PARAMS

# 2. with the compiler UNDER TEST installed
make clean
make check FAUST_OPT="-lang cpp  -double -t 0"        -k -j 8
make clean
make check FAUST_OPT="-lang cpp  -double -t 0 -vec"   -k -j 8
make clean
make check FAUST_OPT="-lang ocpp -double -t 0"        -k -j 8
make clean
make check FAUST_OPT="-lang ocpp -double -t 0 -vec"   -k -j 8
```

`make clean` between two option sets is **mandatory, not a precaution**:
see "Known harness defects" below.

**Know where the trusted compiler lies.** It is trusted in the mode that
produces the references — scalar, default options — and nowhere else by
construction. Once per reference set, run it under every option set the
gate uses, against its own references. Any failure there is a defect of
the *reference* compiler, to be listed before a divergence of the
compiler under test can be attributed. Measured on 2.88.0: `freeverb`
diverges under `-vec` and `-omp`, double and float, in the impulse suite
(the output blows up), while the current branch is conforming. Without
that run, the same failure seen the other way round — a branch that
reintroduces it — would look identical to a branch that never had it.

`FAUST` selects the compiler (default: `faust`, i.e. the installed one)
and `FAUST_OPT` its options (default: `-double -t 0`, i.e. the `cpp`
backend in scalar mode). `FAUST_OPT` is also what `make reference` uses,
so it defines the default options of the central invariant.

## What actually decides what is being tested

A gate compares three things one believes one knows: a compiler, a
library, an option set. Each is selected differently from what one
expects.

### The compiler

`make check` calls `$(FAUST)`, which defaults to `faust` — the one in the
`PATH`, that is, the installed one. Pointing `FAUST` at a build tree lets
several compilers coexist on one machine without overwriting anything.

Installing is still worth doing for its own reason: it is the only way to
check that the installation itself works. So the release gate runs an
**installed** compiler; working gates that compare several binaries use
`FAUST=<path>/build/bin/faust`.

Installing needs root. On a machine where `sudo` asks for a password
interactively, only the pointed-binary mode can be run, and the
installation half of the gate stays unexercised — the report must say so
rather than let the reader assume both halves were covered.

Whichever mode is used, the binary says which source it was built from:

```console
$ faust --version
FAUST Version 2.88.0
Source commit: 8c00913e4
```

A version number names a release, not a build: two binaries from
different commits print the same one. The second line is the one to quote
in a report. It carries a `-modified` suffix when the working tree had
uncommitted changes, because a binary built from a modified tree is not
the commit it names — and `unknown` when the build did not go through
CMake, or had no git available.

### The libraries

The `.dsp` specifications say `library("aanl.lib")`, with no path. The
search order is:

1. the **current directory**,
2. the `-I` paths,
3. `FAUST_LIB_PATH`,
4. `INSTALL_PREFIX/share/faust`, then `<exe>/../share/faust`, then
   `<exe>/share/faust`,
5. `/usr/local/share/faust`, then `/usr/share/faust`,
6. the directory of the compiled `.dsp`, **last**.

Two of these ranks are worth stating plainly, because they are not what
one expects. The current directory wins over everything, including `-I`
and `FAUST_LIB_PATH`. And the directory of the `.dsp` comes last, after
the installed prefixes: a library file sitting next to the program that
imports it does **not** shadow an installed library of the same name.

Two consequences for the gate:

- `make check` does test the working copy's libraries, installed compiler
  or not, because its recipe runs with `libraries/` as the current
  directory.
- A gate that compiles the same specifications from **another** directory
  silently falls through to the installed libraries. No message, no
  failure, plausible-looking numbers.

The reference half and the checking half must use the **same** version of
the `libraries` sub-project. Otherwise a divergence may be a library
change taken for a compiler change.

### The arithmetic of the C++ compiler

`CXXFLAGS` defaults to `-O2 -std=c++17`, which leaves the C++ compiler
free to contract `a*b+c` into a fused multiply-add. Scalar and vectorized
code do not offer the same expression shapes, so they do not receive the
same contractions, and the two results differ — by more than the gate's
tolerance on a resonant filter.

That divergence belongs to the C++ compiler, not to the compiler under
test, and it is platform-bound: on arm64 the contraction happens by
default, while a baseline x86-64 has no FMA instruction to contract into.
The same faust binary therefore passes on one machine and fails on the
other. Measured on `SFFormantModelFofSmooth_ui_test` and `fm_test` under
`-lang ocpp -double -t 0 -vec`: divergent on macOS/arm64 with Apple
clang, identical on Linux/x86-64 with g++, and identical on both once
`-ffp-contract=off` is added.

A gate that compares option sets must therefore **pin the arithmetic**,
or it measures the C++ compiler instead of the semantics:

```sh
make check CXXFLAGS="-O2 -std=c++17 -ffp-contract=off" FAUST_OPT="…" -k -j 8
```

And never `-ffast-math`, nor `-Ofast` which implies it: it authorises
reassociation, and then every option set is entitled to its own answer.

### What "conforming" means numerically

The two gates do not use the same criterion, and neither is exact
equality:

| gate | criterion | default |
| :--- | :-------- | :------ |
| impulse suite | absolute difference ≤ tolerance, in `filesCompare` | `2e-6`, with per-file overrides up to `0.015` on some float/omp legs |
| library specs | `math.isclose(rel_tol=t, abs_tol=t)`, `floatdiff.py` | `t = FLOAT_TOL = 1e-5`, so either criterion suffices |

A consequence worth keeping in mind when reading a divergence: the first
differing sample may well be inside the tolerance while a later one is
not — a resonant filter amplifies an initial difference of one ulp. Judge
the **first** divergence, not the loudest.

## Accepted failures

A gate that does not know its legitimate failures stops at the first one
and hides everything after it. Run with `-k`, and read the following as
expected:

- **`control` / `enable` in vector mode.** `ERROR : 'control/enable' can
  only be used in scalar mode` is a documented limitation, not a
  regression. These primitives are scheduled to disappear in favour of
  `ondemand`; nothing is to be invested in making them vectorisable.
- **Divergences that predate the change under test.** They must be listed
  with the date and the commit at which they were observed, otherwise
  they are indistinguishable from the regressions of the day.

A program that is already broken cannot witness a second breakage: an
innocuity test run over an already-failing case has no power there, while
producing a report that looks exactly like a passing one.

A third class must **not** be added to this list: divergences caused by
fused-multiply-add contraction. They are not accepted failures, they are
a gate that was not pinned — see "The arithmetic of the C++ compiler"
above, and fix the flags rather than excuse the tests.

## What continuous integration covers today

| workflow | what it actually does |
| :------- | :-------------------- |
| `ubuntu.yml` | builds, then `tests/impulse-tests make github_action` |
| `macos.yml` | builds only, no test |
| `windows.yml` | builds only, no test |
| `libfaust.yml` | builds and packages libfaust, no test |
| `jax-tests.yml` | builds, then the jax / nnx / linen tests |

`github_action` is three Rust legs and **one** C++ leg, in `-double`
scalar. No `-vec`, no `ocpp`, no float, no library specification. Vector
backend regressions are invisible to it by construction, which is why the
two gates above are run by hand before anything is trusted.

## What a run report must state

A number without its command is not a measurement. A report of any gate
states:

- the exact command line, including `FAUST_OPT`;
- the compiler under test by the `Source commit:` line of its
  `--version`, and the trusted compiler that produced the references, by
  version and commit;
- the sha of the `libraries` sub-project;
- the C++ compiler by name and version, and the machine;
- **how many programs were actually compared** — "zero divergence" means
  nothing without the count, because a gate that fails on both sides
  passes double failures in silence;
- which failures were expected, from the list above.

## Known harness defects

These are the places where the procedure above is correct but the tooling
does not protect it.

1. **Outputs do not depend on the options.** `tests/output/<test>.out`
   records nothing about the options that produced it, so re-running with
   a different `FAUST_OPT` does not invalidate it: make answers `Nothing
   to be done for 'check'` and tests nothing. This is why `make clean` is
   mandatory. *Fix:* make the outputs depend on a stamp holding
   `FAUST_OPT` and the identity of the faust binary.

2. **The reference stamp is written but never read.** `make reference`
   writes `tests/reference/PARAMS` (faust version, `FAUST_OPT`, sample
   count, sample rate, tolerance), but `check` never opens it, and
   `PARAMS` has no prerequisite, so it is never rewritten. After a
   partial deletion of the `.ref` files without `make distclean`, it
   lies. *Fix:* have `check` print `PARAMS` in its header and refuse a
   reference set that was not produced by the declared trusted compiler;
   add the `libraries` sha and the C++ compiler to it. `PARAMS` also
   keeps only the first line of `--version`, so it records the release
   and loses the commit — the `head -1` becomes `head -2` now that the
   commit is on the second line.

3. **The impulse targets chained their legs in one recipe** — fixed:
   every leg is now a target of its own (see Gate 1). Kept here because
   the same shape exists elsewhere: a recipe that chains independent
   runs as successive lines silently stops at the first failure, and
   `-k` will not save it.

4. **The accept/reject criterion is wired to nothing.**
   `tests/error-tests/CMakeLists.txt` declares one `add_test` per file
   with `WILL_FAIL TRUE`, which is exactly right, but no
   `add_subdirectory` includes it and the build registers no ctest tests.
   The same holds for `tests/warning-tests`. The harness for criterion 1
   exists, written, and never runs.

## Still to be settled

- The status of each of the other suites under `tests/` — gate,
  informative, or abandoned. This has to be written down once.
- What "a reasonable time" means for criterion 1: a per-program
  threshold, or a global one over the corpus.
- Whether the library gate should run in float as well as double, as the
  impulse suite already can.
