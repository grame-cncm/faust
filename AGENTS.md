# AGENTS.md — working on the Faust compiler

Rules for coding agents (and humans in a hurry). They are short on purpose;
the reasons behind each one are in [tests/TESTING.md](tests/TESTING.md),
which is the reference whenever the two seem to disagree.

## Build

- Build with `make` **at the repository root**. Never run `cmake .` (or
  `cmake -C backends/... .`) inside `build/`: it overwrites the
  meta-Makefile tracked by git.
- The binary is `build/bin/faust`. `build/bin/faust --version` prints a
  second line, `Source commit: <sha>`, with `-modified` when the tree had
  uncommitted changes. Quote that line, not the version number: two
  binaries from different commits print the same version.
- The root `make` resets the `libraries` sub-project to its recorded
  commit. Never experiment inside `libraries/` and then rebuild: work on a
  copy, or commit the sub-project first.
- After `git stash`, `checkout` or `pull`, a rebuild in the same second
  may judge objects up to date: touch the changed files, or check that the
  binary's timestamp moved.

## Compiler version — when and how to change it

- Change the version when preparing a compiler release or when explicitly
  asked to identify a new compiler revision. Compiler fixes, changes to
  generated code, new features and public API/backend changes belong in
  that revision. Do not bump it automatically for every commit; documentation,
  tests or formatting alone do not require a new compiler version. Use the
  `Source commit:` line to identify intermediate builds.
- Agree on the target version before changing it. Use three numeric
  components (`major.minor.patch`): normally increment the patch for fixes,
  the minor for a feature release, and reserve a major change for a planned
  compatibility break. Do not invent a release number or publish a release
  as part of an unrelated fix.
- Always run **`./version <major.minor.patch>` from the repository root**;
  do not edit `FAUSTVERSION` or the build version strings individually.
  The script synchronizes the build definitions, CI, exported version
  macros, Windows resources and documentation, runs `make man`, and writes
  `version.txt`. It asks for the exact confirmation `OK`.

For example, only if `2.90.5` is the intended next version:

```sh
./version 2.90.5
# Type OK at the prompt.
git diff --check
git diff
make
build/bin/faust --version
```

Review all changed files and any errors from the script or `make man`;
the script's exit status alone does not prove every update succeeded.
Check that the printed version matches the requested number and read the
`Source commit:` line as well. Commit the coherent tracked version updates
together, preserving unrelated local or untracked files. After committing,
rebuild if a binary identifying the final commit is needed. To reproduce
an older release, check out its tag/commit in a separate worktree; this
script updates the current sources and does not restore older compiler code.

## Git — keep master-dev history linear

- Integrate feature branches and PRs by **rebase, then fast-forward**.
  A linear history keeps changes in one readable sequence and makes it
  easier to identify, bisect and revert individual changes. Do not create
  merge commits on `master-dev`: never use a plain `git merge` or
  `git merge --no-ff` to integrate a branch.
- Start with no uncommitted tracked changes. Preserve local work and
  untracked files. Rebase onto the current `master-dev`, resolve any
  conflicts, and rerun the required tests if conflict resolution changes
  the tested code. Rebase changes commit IDs, so report the new IDs.

For a branch named `codex/topic`, use:

```sh
integration_base=$(git rev-parse master-dev)
git switch codex/topic
git rebase master-dev
# If needed: resolve conflicts, git add <resolved-files>, git rebase --continue.
# Run the required tests before integration.
git switch master-dev
git merge --ff-only codex/topic
git rev-list --merges "$integration_base"..master-dev
```

The final command must print nothing. If `--ff-only` fails because
`master-dev` advanced, rebase the feature branch onto it again; do not
fall back to a merge commit. With separate worktrees, run the rebase in
the feature branch's worktree and the fast-forward in the `master-dev`
worktree, rather than switching a branch already checked out elsewhere.
Do not rewrite published `master-dev` history or force-push without an
explicit request.

## What to run before calling a change tested

| the change touches | run at least |
| :--- | :--- |
| anything in the compiler | Gate 1, the impulse suite: `cpp` and `ocpp`, **float and double** |
| a pass shared by several backends (normal form, typing, promotion, scheduling) | Gate 1, plus Gate 2, the library specifications |
| code that creates trees (`tree(...)`, `sigXxx(...)`, `boxXxx(...)`, fresh names) | Gate 3, determinism (`make -C tests/determinism lint`, then `check`) |
| table accesses, delay lines, the interval library, casts to integers | Gate 4, memory safety |
| public libfaust Signal/Box APIs, symbol visibility, or library build definitions | Gate 5, complete C++ Signal and Box API links against shared libfaust |

Commands, expected results and accepted failures are in TESTING.md, one
section per gate. Do not stop at the first gate that passes.

## Rules that are not up for discussion

- `make -C tests/impulse-tests clean-ir` before every impulse run: the output
  paths spell the options, not the compiler.
- Run gates with `-k`, and read the whole table, one line per leg.
- Name the binary under test explicitly (`FAUST=<path>`) in every gate:
  the impulse suite defaults to the build tree, the library gate to the
  installed `faust`.
- Library gate: `make clean` between two option sets (outputs do not
  depend on `FAUST_OPT`), and the references and the check on the
  **same** commit of `libraries`.
- Shared API gate: run `make -C tests/signal-tests clean-api`, then
  `check-shared-api -k` with explicit `FAUST`, `LIB` and `INC` paths from
  the build under test. Linking only `libfaust.a` cannot detect missing
  shared-library exports. Both API clients must link and run.
- Pin the arithmetic of the C++ compiler in semantic gates
  (`-ffp-contract=off`). Never `-ffast-math` nor `-Ofast` there.
- One reference set, produced by the trusted compiler under default
  options; every option set of the compiler under test is compared with
  it. Never regenerate references to make a gate pass.

## Rules for the code

- **Determinism.** When two arguments of one call (or two operands of an
  unsequenced operator) create trees, compute them in separate
  statements, left to right, then call. The order of evaluation of
  function arguments is unspecified, and the emitted code follows it.
- **Memory safety.** Never remove a guard, size a buffer or accept a
  delay on the strength of a bound computed from floats: the C++ compiler
  (fused multiply-add, reassociation, libm) can move a float past a
  proven bound, and a conversion to an integer turns one ulp into a whole
  unit. Rely on exact integer arithmetic or on a test at run time.
  Control values are not bounded by their declared range unless `-rui`
  is given.
- **Clocks.** Never strip `sigClocked`, not even with a nil clock:
  downstream code pattern-matches on it. The only safe simplification is
  flattening nested clocks, keeping the outer one.
- Comments describe the code and its reasons, never who wrote it or who
  found the bug.
- Do not commit generated files, test outputs or local scratch files.
  Do not push, tag or open pull requests unless asked to.

## What a report must state

A number without its command is not a measurement. For every gate run:

- the exact command line, options included;
- the `Source commit:` line of every binary involved, printed by the gate
  itself and **read first**: a scripted gate that rebuilt the wrong
  commit looks exactly like a passing one;
- the C++ compiler (name and version) and the machine;
- **how many programs were compared** on each leg: "zero divergence"
  means nothing without the count, and a gate that fails on both sides
  passes in silence;
- which failures were expected, from the list in TESTING.md, and which
  were not.

Before trusting a comparison tool, make it fail once: alter an output on
purpose, on a value, and check that the tool says so. Never send the error
channel of a verdict command to `/dev/null`.
