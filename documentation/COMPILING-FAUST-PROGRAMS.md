---
title: Compiling Faust programs
subtitle: The options of the cpp and ocpp backends, and how to find good ones
author: The Faust Team
date: September 2026
document-style: article-a4
language: en
---

::: toc+
- **Two C++ backends : `cpp` and `ocpp`** — what each backend is, and which options each honours.
- **The options, stage by stage** — every option, grouped by the stage of compilation it acts on.
  - **Input, output and naming** — backend, sources, libraries, names.
  - **Arithmetic** — precision and the operations where exactness and speed disagree.
  - **Signal transformations** — rewrites of the signal graph.
  - **Recognised forms (ocpp)** — filters, sums, matrices, families.
  - **Delay lines, tables and memory** — the memory layout of the class.
  - **Temporaries and instruction order (ocpp)** — variables and the order of the loop body.
  - **Loop splitting (ocpp, -ls)** — several loops, fused under a cost model.
  - **Vector and parallel modes (cpp)** — vector loops and threads.
  - **Shape of the emitted class** — the form of the C++ class.
  - **Diagnostics and information** — what the compiler can print.
  - **Block diagrams and mathematical documentation** — drawings and documents.
- **Environment variables** — the variables the compiler reads.
- **Finding good options** — the method.
  - **What the options may change in the results** — what is intended, and what is a bug.
  - **Measuring** — how to time without fooling oneself.
  - **What a result is valid for** — machine, compiler family, portfolio.
  - **Searching** — by stage, and the interactions.
  - **An automatic search, step by step** — fcautotool and fcgentool.
  - **Pitfalls** — the traps met so far.
- **Options outside this document** — the other backends.
- **Keeping this document in sync** — the check that keeps it true.
:::

This document is for anyone who compiles Faust programs to C++ and wants the generated code to be fast. It describes every option of the two C++ backends, `cpp` and `ocpp`. It then explains how to find good options for a given program, machine and C++ compiler. The script `tests/doc-tests/check-compiling-doc.py` keeps the list of options in step with the compiler (\ref{sec:sync}).

Three facts shape everything below.

- **No option is good everywhere.** An option that halves the running time of one program can double that of another.
- **The answer depends on the C++ compiler as much as on the program.** The same generated code can run twice as fast under clang as under g++, or the reverse, so a setting is good for a machine and a family of C++ compilers, not in general.
- **Options change the speed, not the program.** Whatever the options, the generated code computes what the Faust program says. The few options that trade exactness for speed on purpose are listed in \ref{sec:results}.

# Two C++ backends : `cpp` and `ocpp` \label{sec:backends}

Both backends emit a C++ class with the same interface (`init`, `buildUserInterface`, `compute` and the rest of the `dsp` API), and both read the same normalized signal graph. They differ in how they turn that graph into code.

- **`cpp`** (`-lang cpp`, the default) goes through the compiler's intermediate language (FIR) and is shared with the other backends (C, LLVM, WebAssembly...). It is the stable, portable choice. It is also the only one with the vector and parallel modes (`-vec`, `-omp`, `-sch`, \ref{sec:vector}).
- **`ocpp`** (`-lang ocpp`) emits C++ directly from the signal graph. It is where the signal-level optimizations live : filter recognition, sum factorization, isomorphic families, loop splitting and instruction scheduling (\ref{sec:signal} to \ref{sec:loops}). Almost all of these are options, off by default, marked *experimental* : tested like the rest of the compiler, but worth using only on the programs where it measures faster.

In the tables, `cpp` means that the `cpp` backend honours the option. Many `ocpp` options are **accepted by `cpp` and silently ignored**, and the column says so, because a command line that "works" under both backends does not mean the option did anything.

Which backend to use is itself an option to search (\ref{sec:search}). Neither backend wins everywhere.

# The options, stage by stage \label{sec:options}

The options are grouped by the stage of compilation they act on, from the source file to the emitted class. `Backends` says which of `cpp` and `ocpp` take the option into account. `Status` is one of :

- **stable** : part of the compiler's long-standing interface ;
- **experimental** : off by default, tested like the rest of the compiler, worth it on some programs only ;
- **contract** : the option makes a promise that the architecture file must keep, and the generated code checks it ;
- **diagnostic** : prints or draws something, never changes the generated code.

## Input, output and naming

These options choose the backend, find the source and the libraries, and name what is produced. They do not change the computation.

| Option | Backends | Status | What it does, when it helps |
| :--- | :--- | :--- | :--- |
| `-lang` | both | stable | The backend : `cpp` (default), `ocpp`, or another language (\ref{sec:outside}). |
| `-a` | both | stable | Wraps the generated class in an architecture file (an audio driver, a plugin format, a test harness). |
| `-i` | both | stable | Inlines the files the architecture file includes, producing a self-contained C++ file. |
| `-A` | both | stable | Adds a directory to the search path of architecture files. |
| `-I` | both | stable | Adds a directory to the search path of Faust libraries. |
| `-o` | both | stable | The output file. Write to a real file : under `cpp`, `-o /dev/stdout` gives a truncated output. |
| `-e` | both | stable | Exports the program with every library it uses expanded, as one Faust file. |
| `-O` | both | stable | The directory where the generated code and the additional files (SVG, XML...) are written. |
| `-uim` | both | stable | Adds the user-interface macros to the output (used by some architecture files). |
| `-xml` | both | stable | Also writes an XML description of the program's interface. |
| `-json` | both | stable | Also writes a JSON description of the program's interface. |
| `-cn` | both | stable | The name of the generated class, instead of `mydsp`. Needed to link several programs into one binary. |
| `-scn` | both | stable | The name of the base class, instead of `dsp`. |
| `-pn` | both | stable | The entry point of the program, instead of `process`. Lets one file hold several programs. |
| `-ns` | cpp | stable | Wraps the generated code in a C++ namespace. `ocpp` refuses it. |
| `-inj` | both | stable | Injects a C++ file into the architecture file instead of compiling a Faust program. |

## Arithmetic

The type of the computation, and the treatment of the few operations where exactness and speed disagree.

| Option | Backends | Status | What it does, when it helps |
| :--- | :--- | :--- | :--- |
| `-single` | both | stable | Computes in `float` (the default). |
| `-double` | both | stable | Computes in `double`. Resonant physical models and long feedback networks often need it. A setting found in double must be checked again in float before it is used in float : the two do not elect the same options. |
| `-quad` | both | stable | Computes in `quad` (`long double` or a quadruple-precision type, depending on the architecture). |
| `-ifp` | both | experimental | With `-single` : does not factor a sum whose constant cofactor would absorb a small term, when the factor is computed at every sample. `x - h*x` stays so instead of `x*(1-h)`, whose constant `1-h` rounded once is a bias a recurrence accumulates (an Euler step off by 0.3 %). Improves the float precision of a few recurrences (`pm.rk_solve` from 8 bits to 16), at a small cost in time on them (+6 % on average on the 43 library tests it changes, up to x2). With `-single` or `-double` : a conversion to an integer computed outside the sample loop, `int(c*x)` with `c` the rounding of a small rational `p/q`, is computed as `int((p*x)/q)`. An exact integer result, such as a delay of 1617 samples at 44.1 kHz scaled to 48 kHz (1760), is then no longer truncated one unit short (1759). |
| `-fx` | both | stable | Computes in fixed point. |
| `-fx-size` | both | stable | The total size of the fixed-point type, in bits (`-1` for a single `fixpoint_t` type). Meaningful with `-fx` only. |
| `-ftz` | both | stable | Flushes denormals to zero in recursive signals : `0` none (default), `1` with `fabs`, `2` with a mask (fastest). Helps on feedback programs that decay into denormals on machines without a hardware flush-to-zero mode. |
| `-mapp` | both | stable | Simpler, faster versions of `floor`, `ceil`, `fmod` and `remainder`. Changes results at the edges of their domains. |
| `-fm` | cpp | stable | Uses the fast mathematical functions of a given file (`def` : `faust/dsp/fastmath.cpp`). Changes results. `ocpp` refuses it. |
| `-exp10` | both | stable | Replaces `pow(10, x)` by `exp10(x)`, when the C library provides it. No effect on a program without `pow(10, x)`. |
| `-cir` | both | stable | Checks the range of float-to-integer conversions and generates safe code for them. |
| `-me` | both | diagnostic | Warns at compile time about divisions by zero and out-of-domain `fmod`, `sqrt`, `log`, `acos`... that the intervals cannot exclude. No change to the generated code. |

## Signal transformations \label{sec:signal}

Rewrites of the normalized signal graph, before any code exists. They change *what* is computed (the order of a sum, the branches of a selection), never the result beyond the rounding.

| Option | Backends | Status | What it does, when it helps |
| :--- | :--- | :--- | :--- |
| `-eta` | both | stable | The eta normalization, on by default : a recursive definition that the simplifications made non-recursive is replaced by its value, iterated until nothing changes. Only needed to undo an earlier `-noeta`. |
| `-etai` | both | stable | The iteration cap of the eta normalization (default 64 ; the loop stops earlier by itself). |
| `-noeta` | both | stable | Turns the eta normalization off. For comparisons only : the normal form without it keeps false recursions. |
| `-etar` | both | experimental | Each eta iteration also regroups the recursive definitions along their strongly connected components. Changes the output on few programs. |
| `-reassoc` | ocpp (cpp ignores it) | experimental | Reassociates the sums inside single-definition recursions so that the recurrence chain is as short as possible. Helps feedback-bound programs (a comb network). |
| `-gatequiv` | ocpp (cpp ignores it) | experimental | Gives one canonical form to the two spellings of a gated signal, so that `-lazyselect` finds more guards. |
| `-lazyselect` | ocpp (cpp ignores it) | experimental | Computes the branches of a selection only when they are selected. Helps programs that switch between costly alternatives. |
| `-selectn` | ocpp (cpp ignores it) | experimental | Rebuilds N-way dispatches from their chains of two-way selections, then emits them lazily (implies `-lazyselect`). |
| `-sts` | cpp | stable | Strict selections : both branches of `select2` are always computed, even stateless ones. For checking only. `ocpp` accepts it without effect. |
| `-es` | both | stable | `1` (default) : `enable` and `control` use their enable semantics ; `0` : a plain multiplication. |
| `-mindelay` | ocpp (cpp ignores it) | experimental | A floor on large variable delays : emits `max(d, n)` when the certified minimum is below `n` and the maximum above `32n`. Changes the semantics of short delays : use it only when the program never needs them. |
| `-lcc` | both | diagnostic | Also checks causality at the local level. Refuses more programs, never changes the code. |

## Recognised forms (ocpp) \label{sec:forms}

The normalization scatters the structures the programmer wrote : a filter becomes a cloud of products and delayed sums, a bank of identical voices a set of unrelated trees. These options recognise such structures in the signal graph and emit them in a dedicated form. The recognition is exact ; whether the dedicated form is faster depends on the program and on the C++ compiler.

| Option | Backends | Status | What it does, when it helps |
| :--- | :--- | :--- | :--- |
| `-fir` | ocpp (cpp ignores it) | experimental | Recognises FIR and IIR kernels (delay lines with coefficients) and emits them as convolutions, sliding sums, symmetric forms or coefficient tables. Wins on large kernels (long FIR filters, equalizers), can lose on small first- and second-order sections. |
| `-fir-hoist` | ocpp (cpp ignores it) | experimental | A bank of constant-coefficient IIRs on one input, whose outputs go through the same kernel, gets the kernel moved before the bank (implies `-fir`). |
| `-iirt` | ocpp (cpp ignores it) | experimental | Emits the all-pole kernels recognised by `-fir` in transposed form, their states in scalars. Needs `-fir`. |
| `-lsum` | ocpp (cpp ignores it) | experimental | Recovers the polynomial form of large sums before emission. |
| `-mxr` | ocpp (cpp ignores it) | experimental | Groups parallel rows over one shared vector into a matrix-vector product (state-space models, dense layers). Reads the rows `-lsum` recovers ; no effect where no such family exists. |
| `-fam` | ocpp (cpp ignores it) | experimental | Finds the families of isomorphic parallel chains (the modes of a bank, the bands of a vocoder, the channels of a matrix, the analysers of a display) and emits each family as one inner loop over arrays of states, coefficients and inputs. Whether the loop is faster depends strongly on the C++ compiler's vectoriser. |
| `-fam-out-min` | ocpp (cpp ignores it) | experimental | With `-fam` : the minimum size, in operations, of a member of a family among the outputs or displays (default 12). |
| `-fam-out-members` | ocpp (cpp ignores it) | experimental | With `-fam` : the minimum number of members of a family among the outputs or displays. |
| `-fam-host` | ocpp (cpp ignores it) | experimental | With `-fam` : the minimum number of members per host sum for a family of sums to be emitted as one loop per host (default 1). |
| `-fam-align` | ocpp (cpp ignores it) | contract | With `-fam` : aligns the family arrays on `n` bytes. The generated class then requires an `n`-aligned address, which the architecture file must provide. A generated constructor checks it and aborts with a `FAUST ERROR` message otherwise. It also means the members are no longer zeroed by `new mydsp()` : call `init` before any other method, `getSampleRate` included. |

## Delay lines, tables and memory \label{sec:delays}

How delay lines, tables and the class members are laid out in memory.

| Option | Backends | Status | What it does, when it helps |
| :--- | :--- | :--- | :--- |
| `-mcd` | both | stable | Delays up to `n` samples use copy delays (a shift of a few scalars), longer ones a dense delay (`ocpp`) or a ring buffer (default 16). A larger value helps programs with many short delays ; the best value depends on the machine. |
| `-mdd` | ocpp | stable | Delays up to `n` samples use a dense delay when dense enough, longer ones a ring buffer (default 1024). |
| `-mdy` | ocpp | stable | The minimum density (100 x number of delays / maximum delay) for a dense delay (default 33). |
| `-dlt` | cpp | stable | Ring buffers up to `n` samples use a mask, longer ones a select (default : all masks). `ocpp` refuses it. |
| `-it` | cpp | stable | Inlines the code of `rdtable` and `rwtable` in the main class. `ocpp` refuses it. |
| `-ct` | both | stable | `1` (default) : checks the index range of `rdtable` and `rwtable` and generates safe accesses ; `0` : no check. |
| `-mem` | both | stable | Allocations through a custom memory manager given by the architecture file. |
| `-mem1` | cpp | stable | Custom memory manager with the `iControl`/`fControl` and `iZone`/`fZone` model. Requires `-it`. |
| `-mem2` | cpp | stable | The same model without an explicit memory manager. Requires `-it`. |
| `-mem3` | none | stable | The same model with access as function parameters : C backend only. |
| `-mem0` | both | stable | The same as `-mem` (not in -h). |

## Temporaries and instruction order (ocpp) \label{sec:order}

Where expressions become named variables, and in which order the statements of the sample loop are emitted. Every order is correct ; on real programs two orders of the same computations can differ by a factor of two.

| Option | Backends | Status | What it does, when it helps |
| :--- | :--- | :--- | :--- |
| `-temp` | ocpp (cpp ignores it) | experimental | Materializes single-use expressions of `n` operations or more as temporaries (`1` : SSA form, `0` : off). |
| `-stage` | ocpp (cpp ignores it) | experimental | Stages expressions nested deeper than `n` into named temporaries. Helps deeply nested expressions that the C++ compiler would otherwise keep entirely in registers. |
| `-xtemp` | ocpp (cpp ignores it) | experimental | The temporaries are decided by a signal pass, and the emitter only obeys them. |
| `-ss` | ocpp (cpp ignores it) | experimental | The order of the loop body : `0` depth-first (default), `8` aligned (identical shapes in consecutive runs, which the C++ vectoriser likes), `9` bank-compositional, `11` and `12` compositional with a deep or a wide spine. The model-based strategies use `-ls-R` and `-ls-U`. The single most effective lever on many programs. |
| `-rp` | ocpp (cpp ignores it) | experimental | Ring-buffer reads leave as a burst at the head of the loop body. |

## Loop splitting (ocpp, -ls) \label{sec:loops}

Instead of one sample loop computing everything, `-ls` emits the computation graph as several loops that communicate through buffers, and `-ls-fuse` merges them back where a cost model says it pays. The cost model describes the machine with a register budget `R` and an issue width `U`. Its weights (`-ls-cl`, `-ls-spill`, `-ls-load`...) only take effect when a fusion decision depends on them.

| Option | Backends | Status | What it does, when it helps |
| :--- | :--- | :--- | :--- |
| `-ls` | ocpp (cpp ignores it) | experimental | Emits the materialized graph as separate loops. |
| `-ls-sched` | ocpp (cpp ignores it) | experimental | The order inside each loop : `df` (default), `bf`, `model`, `layers`, `cs2`, `cs2b`, `profile` (implies `-ls`). |
| `-ls-R` | ocpp (cpp ignores it) | experimental | The register budget of the model schedulers and of the fusion cost model (default 20). The best value is rarely the default : try a small one (2 to 8) and a large one (32). |
| `-ls-U` | ocpp (cpp ignores it) | experimental | The issue width of the model schedulers and of the fusion cost model (default 4). |
| `-ls-sched-R` | ocpp (cpp ignores it) | experimental | A register budget for the emission scheduler alone, the fusion keeping `-ls-R`. |
| `-ls-const-live` | ocpp (cpp ignores it) | experimental | The model scheduler counts the constants and slow values of a loop as live registers (implies `-ls`). |
| `-ls-fuse` | ocpp (cpp ignores it) | experimental | Greedy fusion of the single-consumer loops under the cost model (implies `-ls`). With `-ls-sched model`, the most frequent winning pair of this family. |
| `-ls-fuse-ops` | ocpp (cpp ignores it) | experimental | The maximum number of operations in a fused block (default 1024), a guard on compilation time. |
| `-ls-tile` | ocpp (cpp ignores it) | experimental | Forces the `(k, d)` tiling of every family of isomorphic chains, without the cost model. |
| `-ls-tiles` | ocpp (cpp ignores it) | experimental | Lets the cost model pave every family of isomorphic chains with its cheapest tiling (implies `-ls-fuse`). |
| `-ls-cl` | ocpp (cpp ignores it) | experimental | Cost model : overhead of a loop per chunk (default 20 cycles). |
| `-ls-tile-cl` | ocpp (cpp ignores it) | experimental | Cost model : overhead of a tile per chunk, in the choice of a tiling (default 100 cycles). |
| `-ls-spill` | ocpp (cpp ignores it) | experimental | Cost model : cycles per register above `R` (default 4 ; implies `-ls-fuse`). |
| `-ls-load` | ocpp (cpp ignores it) | experimental | Cost model : issue slots per buffer load (default 1 ; implies `-ls-fuse`). |
| `-ls-cload` | ocpp (cpp ignores it) | experimental | Cost model : memory operations per reload of a spilled constant (default 1). |
| `-ls-latency` | ocpp (cpp ignores it) | experimental | Prices a loop at its steady state, overlapping `k` frames (default 0 : one isolated iteration). |
| `-ls-regs3` | ocpp (cpp ignores it) | experimental | The fusion cost counts three classes of registers : carried states, constants and temporaries, each spilling at its own price. |
| `-ls-regstate` | ocpp (cpp ignores it) | experimental | A member read only inside its own loop, at constant delays, keeps its history in scalars across chunks instead of a buffer. |
| `-ls-acc` | ocpp (cpp ignores it) | experimental | A sum whose operands come from several loops is accumulated in place by those loops, without a join loop. |

## Vector and parallel modes (cpp) \label{sec:vector}

The `cpp` backend can emit the computation as a sequence of loops over vectors of samples (`-vec`), which the C++ compiler vectorises more easily, and can distribute these loops over threads. `ocpp` takes `-vec` and `-omp` through its own loop-splitting emission.

| Option | Backends | Status | What it does, when it helps |
| :--- | :--- | :--- | :--- |
| `-scal` | both | stable | Scalar code : one loop over the samples (the default). |
| `-vec` | both | stable | Vector code : a loop per sub-computation over vectors of samples. Often the fastest `cpp` setting on wide programs (banks, mixers). |
| `-vs` | both | stable | The vector size (default 32 samples). |
| `-lv` | cpp | stable | The loop variant : `0` fixed size with a remainder loop (default), `1` variable size, `2` fixed size. |
| `-omp` | both | stable | OpenMP pragmas (implies `-vec`). |
| `-pl` | both | stable | Parallel loops in `-omp` mode. |
| `-sch` | cpp | stable | Tasks run by a work-stealing scheduler (implies `-vec`). `ocpp` refuses it. |
| `-dfs` | cpp | stable | Schedules the vector loops in depth-first order. |
| `-g` | cpp | stable | Groups sequential single-threaded tasks together (with `-omp` or `-sch`). |
| `-fun` | cpp | stable | Emits the tasks as separate functions (with `-vec`, `-sch` or `-omp`). |
| `-inpl` | both | stable | Code that works when the input and output buffers are the same. Scalar mode only. |

## Shape of the emitted class

The form of the C++ class itself, independent of the computation.

| Option | Backends | Status | What it does, when it helps |
| :--- | :--- | :--- | :--- |
| `-light` | none | stable | Does not generate the entire DSP API : C backend only. |
| `-nvi` | cpp | stable | Omits the `virtual` keyword. Lets the C++ compiler devirtualise calls when the class is used directly. |
| `-os` | cpp | stable | Generates a one-sample computation (`frame`) instead of a buffer loop. `ocpp` refuses it. |
| `-ec` | cpp | stable | Separates the `control` and `compute` functions. `ocpp` refuses it. |
| `-cm` | cpp | stable | Mixes the result into the output buffers instead of overwriting them. `ocpp` refuses it. |
| `-rui` | both | stable | Constrains the values of sliders and numerical entries to their `[min, max]` range. |
| `-fui` | both | stable | Freezes sliders and numerical entries at a given value (their initial value by default), which turns them into constants. |
| `-clang` | cpp | stable | Adds clang pragmas for auto-vectorization. |
| `-fp` | cpp | stable | Always parenthesises binary operations. |

## Diagnostics and information

| Option | Backends | Status | What it does, when it helps |
| :--- | :--- | :--- | :--- |
| `-d` | both | diagnostic | Prints compilation details. |
| `-time` | both | diagnostic | Prints the time of each compilation phase. |
| `-flist` | both | diagnostic | Prints the list of files (libraries included) used to evaluate the program. |
| `-tg` | cpp | diagnostic | Prints the task graph in dot format. |
| `-sg` | both | diagnostic | Prints the signal graph in dot format. |
| `-hg` | ocpp | diagnostic | With `-ls` : prints the loop-split blocks as a hierarchy, in dot format. |
| `-sng` | ocpp | diagnostic | Prints the super-node graph (not in -h). |
| `-rg` | both | diagnostic | Prints the signal graph after retiming, in dot format. |
| `-norm` | both | diagnostic | Prints the signals in normalized form and exits. |
| `-norm1` | both | diagnostic | The same, with identifiers for shared subexpressions. |
| `-norm2` | both | diagnostic | Another printing of the normalized form (not in -h). |
| `-norm3` | both | diagnostic | Another printing of the normalized form (not in -h). |
| `-sig` | ocpp | diagnostic | Prints the program's static signature on one line (size, recurrence bound, selections, streams...), the input of the automatic option search (\ref{sec:searching}). |
| `-wall` | both | diagnostic | Prints all warnings. |
| `-t` | both | stable | Aborts the compilation after `n` seconds (default 120). The costly `ocpp` options can need more. |
| `-hlf` | both | stable | The load factor of the compiler's internal hash tables. Compilation speed only : never changes the generated code. |
| `-h` | both | diagnostic | Prints the help. |
| `-v` | both | diagnostic | Prints the version and the embedded backends. |
| `-libdir` | both | diagnostic | Prints the directory of the Faust libraries. |
| `-includedir` | both | diagnostic | Prints the directory of the Faust headers. |
| `-archdir` | both | diagnostic | Prints the directory of the architecture files. |
| `-dspdir` | both | diagnostic | Prints the directory of the DSP libraries. |
| `-pathslist` | both | diagnostic | Prints the search paths of the architecture files and libraries. |

## Block diagrams and mathematical documentation

These produce drawings and documents from the program. They do not change the generated code.

| Option | Backends | Status | What it does, when it helps |
| :--- | :--- | :--- | :--- |
| `-ps` | both | diagnostic | Draws the block diagram in PostScript. |
| `-svg` | both | diagnostic | Draws the block diagram in SVG. |
| `-style` | both | diagnostic | A style file for the SVG diagrams (not in -h). |
| `-sd` | both | diagnostic | Simplifies the diagrams further before drawing. |
| `-drf` | both | diagnostic | Draws route frames instead of simple cables. |
| `-f` | both | diagnostic | The number of elements above which the diagram is folded (default 25). |
| `-fc` | both | diagnostic | The complexity above which an expression is folded (default 2). |
| `-mns` | both | diagnostic | The maximum length of a name in the diagram (default 40). |
| `-sn` | both | diagnostic | Simple names, without their arguments. |
| `-blur` | both | diagnostic | A shadow blur on the SVG boxes. |
| `-sc` | both | diagnostic | Scalable SVG. |
| `-mdoc` | both | diagnostic | Writes the mathematical documentation of the program in LaTeX. |
| `-mdlang` | both | diagnostic | The language of the mathematical documentation, when a translation exists. |
| `-stripmdoc` | both | diagnostic | Strips the `mdoc` tags from the listings. |

# Environment variables

Most of these print internal traces ; the ones marked *changes the code* are also switches.

| Variable | Effect |
| :--- | :--- |
| `FAUST_LIB_PATH` | Additional directories to search for Faust libraries. |
| `FAUST_ARCH_PATH` | Additional directories to search for architecture files. |
| `FAUST_ARCHS` | C backend : emits one `compute` per listed target architecture (`__attribute__((target("arch=...")))`). |
| `FAUST_DEFAULT_BACKEND` | The backend used when `-lang` is not given. |
| `FAUST_DEBUG` | Internal traces : `FAUST_LLVM1`, `FAUST_LLVM2` (LLVM IR before and after optimisation), `FIR_PRINTER` (the FIR), `FAUST_LLVM_NO_FM`. |
| `FAUST_OPT` | `FAUST_SIG_NO_NORM` turns off the signal normalization (changes the code ; for debugging only). `FAUST_SIG_NO_FACTOR` keeps the normalization but not its factorization by the greatest common divisor (changes the code ; a precision experiment). `FAUST_SIG_FACTOR_GUARD` does the same as `-ifp`. |
| `FAUST_TIMING` | Appends the timing of the compilation phases to the file `FAUST_TIMING_LOG`. |
| `FAUST_WASM` | Options of the WebAssembly backend. |
| `FAUST_INTERP_TRACE` | Traces the interpreter backend. |
| `FAUST_INTERP_OUTPUT` | Output of the interpreter traces. |
| `FAUST_PROPAGATE_PROFILE` | Profiles the propagation of the block diagram. |
| `FAUST_FAM_TRACE` | Traces the family recognition of `-fam`. |
| `FAUST_FAM_SHAPES` | Prints the shape classes seen by `-fam`. |
| `FAUST_RWM_GATEA` | Test probe : each pass built on the minimal rewrite runs a second time with the older rewrite that renames every recursive group, and prints on stderr whether the two results agree (`SAME`, `UNFOLD-SAME`, `DIFF`). The second run creates nodes, so the generated code may differ : never compare code produced with it. |
| `FAUST_FIR_HOIST_TRACE` | Traces `-fir-hoist`. |
| `FAUST_LS_ACC_ONLY` | Restricts `-ls-acc` to selected sums (changes the code ; for experiments only). |

# Finding good options \label{sec:search}

## What the options may change in the results \label{sec:results}

The generated code is correct whatever the options : that is the compiler's job, and its test suites check it (`tests/TESTING.md`). Two kinds of change remain, both intended.

- **Options that trade exactness for speed, on purpose.** `-fm` and `-mapp` use approximate mathematical functions ; `-mindelay` gives short variable delays a floor ; `-ftz` flushes denormals to zero ; `-fui` freezes the controls. Use them knowing what they give up. The same goes for the C++ compiler's own flags : `-ffast-math` lets it change the arithmetic.
- **The last digit.** Options that reorder arithmetic (`-lsum`, `-reassoc`, `-fir`, the scheduling options) can change the rounding of a sum in its last bit. Both results are correct roundings of the same computation. In a program with feedback (a reverberator, a resonant model) such a difference can grow over seconds into a visible one : the two outputs are then two equally valid trajectories, not an error.
- **The precision is a choice.** Pick float or double for what the program needs ; a setting found fastest in double should be timed again in float before it is used there, the two do not always give the same code.

Anything else, an option that changes the result beyond this, is a compiler bug : please report it.

## Measuring \label{sec:measuring}

- **Name the C++ compiler, its version and its flags with every number.** The same generated code can differ by more than a factor of two between g++ and clang.
- **Compare two binaries in the same session, in alternating rounds** (A B A B...), never with a number measured at another time. Machines drift : heat, background work, power source.
- **Take the minimum over repetitions**, each running many blocks after a warm-up. Disturbances only add time. A short busy spin before timing makes the operating system place the process on a performance core at full clock : on asymmetric machines, the same binary otherwise reads 1.6, 2.5 or 4.0 ns per sample depending on the core it lands on. The tools of \ref{sec:auto} do all of this.
- **Know the memory-placement lottery.** On Linux, the stack and heap addresses change at each run, and with them the alignment of the state arrays : the same binary can spread over 50 %. `setarch -R` (no privileges needed) turns the randomisation off ; otherwise many runs are needed, and the minimum measures the best placement found, not the program.
- **Give the measured core to the measurement alone.** When you pin the measurement to a core (`taskset` on Linux), keep the other hardware thread of that core (its SMT sibling) idle too : on an AMD Zen 5, a load on the sibling slowed the measured binary by about 40 % at unchanged clock, while a load on another core cost nothing.
- **Build and measure separately.** A binary measured while something else compiles is not measured.
- **Be suspicious of a tenfold gain.** Check that the two measurements measured what you think : the right binaries, doing the same work.

## What a result is valid for \label{sec:validity}

- **A setting is good for a machine and a C++ compiler family**, not in general. On a corpus of 254 programs measured in September 2026 on two machines with four C++ compilers (Apple clang 21 and clang 22 on an Apple M1, clang 22 and g++ 15 on an AMD Zen 5), taking the elected setting of one configuration to another cost about 3 % when only the compiler version changed, 11 % when the machine changed, and 19 % when the compiler family changed (clang against g++).
- **A portfolio beats a default.** On the same corpus, choosing the best of a short list of settings per program gained 21 to 26 % over the default, where the best single setting gained only 5 to 9 %.
- **A default must hold everywhere.** An option is a candidate for a default only if it loses clearly under none of the configurations tried. An option that wins under one C++ compiler and loses under another stays in the portfolio.

## Searching \label{sec:searching}

- **By stage.** The stages of \ref{sec:options} give the order of the search : backend and precision first, then the recognised forms (\ref{sec:forms}), the loop structure (\ref{sec:loops}), the instruction order (\ref{sec:order}), the delays (\ref{sec:delays}). An option of a later stage is only worth trying on the forms an earlier stage chose.
- **Know the interactions.** `-selectn` implies `-lazyselect` ; `-iirt` and `-mxr` act only on what `-fir` and `-lsum` recognised ; the `-ls-...` options imply `-ls` or `-ls-fuse` ; `-ls-R` and `-ls-U` also set the model of `-ss 9`, `11` and `12`. The fusion escort matters : `-fir` alone can lose where `-fir -ls-fuse -ls-sched model` wins.
- **Automatically**, per program, with the tools of \ref{sec:auto}.
- **Keep what you find**, with the machine, the C++ compiler and the compiler version it was found with. A recipe found elsewhere is a starting point, to be measured again.

## An automatic search, step by step \label{sec:auto}

Two tools of the Faust Compiler Benchmark Tools (<https://github.com/orlarey/faustcompilerbenchtool>) do the work of \ref{sec:measuring} to \ref{sec:searching} for one program :

- **`fcautotool`** elects the best of a jury of known option sets, in a minute or so ;
- **`fcgentool`** breeds new combinations of options by a genetic search, for a program worth hours of machine time.

**Installing.** They need Python 3, a C++ compiler, and `faust` on the `PATH` :

```
git clone https://github.com/orlarey/faustcompilerbenchtool
cd faustcompilerbenchtool
sudo ./install.sh
```

The tools go to `/usr/local/bin`. `fcversion` tells which version is installed.

**Running `fcautotool`.** Plug the machine in first : the tools refuse to time on battery power.

```
fcautotool examples/reverb/freeverb.dsp -o freeverb.cpp
```

::: warning [On Linux]
Run it under `setarch -R` (no privileges needed), so that each candidate keeps the same memory layout from one launch to the next (\ref{sec:measuring}) :

```
setarch -R fcautotool examples/reverb/freeverb.dsp -o freeverb.cpp
```

Without it, on a machine that randomises addresses, the speed of the same binary is itself drawn at each launch (by about 25 % on some programs) : when candidates are close, the name of the winner is decided by the draw, and its reported time leans to the lucky side. macOS does not have this problem.
:::

On an Apple M1 with clang 22, with a development `faust` on the `PATH`, in 49 seconds (the lists are shortened here) :

```
fcautotool: faust = /Users/.../faust/build/bin/faust
fcautotool: c++ = /opt/local/bin/clang++ (clang version 22.1.8) -O3 -ffast-math -fbracket-depth=1024 -march=native
fcautotool: timed in single precision  (--double to elect for a double build)
fcautotool: jury = 28/28 candidates supported: ['al', 'cs2', 'cs2b', 'df', 'fi', ...]
fcautotool: shortlist by signature: 17/28 of the supported jury (--full races them all): ['df', 'lb', 'fu', ...]
  r3s       12.0120 ns  (-lang ocpp -ls-fuse -ls-latency 4 -ls-regs3 -ls-R 40 -ls-load 0 -ls-regstate)
  h2        12.7200 ns  (-lang ocpp -ss 9 -ls-R 2 -ls-U 4)
  r3ks      13.7000 ns  (-lang ocpp -fir -iirt -lsum -ls-fuse -ls-latency 4 -ls-regs3 -ls-R 40 -ls-load 0 -ls-regstate)
  fi        13.7060 ns  (-lang ocpp -fir -iirt)
  df        13.8250 ns  (-lang ocpp)
  ...
  fu        16.5800 ns  (-lang ocpp -ls-fuse -ls-sched model)
  cppmcd0   19.7330 ns  (-lang cpp -mcd 0)
  cpp       24.1540 ns  (-lang cpp)
  cppvec    33.2190 ns  (-lang cpp -vec)
  al        43.2500 ns  (-lang ocpp -ss 8)
  -- 20 timed of 20 raced (0 build failures, 0 without a timing)
fcautotool: winner r3s (12.0120 ns/frame, single precision) -- -lang ocpp -ls-fuse -ls-latency 4 -ls-regs3 -ls-R 40 -ls-load 0 -ls-regstate  [49.1 s]
fcautotool: bare faust output written to freeverb.cpp
```

How to read it :

- **The first three lines name the judge** : the `faust` and the C++ compiler used, its flags, and the precision. The result holds for them (\ref{sec:validity}) : keep these lines with it. The `faust` line is only a path : keep the output of `faust --version` beside them, so that the result says which compiler it is about.
- **The jury** holds only the candidates that this `faust` accepts : a released `faust` gives a smaller jury than a development one. The program's signature (`-sig`) then shortlists the plausible ones ; `--full` races them all.
- **The times** are nanoseconds per frame, the minimum over alternating rounds. The jury includes the `cpp` backend (`cpp`, `cpp -vec`, `cpp -mcd 0`), so the table also answers which backend to use : here `ocpp` with the winning options is twice as fast as `cpp`, and one candidate (`al`) is more than three times slower than the default (`df`). A wrong guess costs more than the right one gains.
- **As a safeguard**, the winner's impulse response is compared with the default's before it is kept ; a candidate that differs beyond rounding is reported `DISQUALIFIED` and the next one is taken. Such a report points to a compiler bug and is worth sending. When the default produces silence on an impulse, there is nothing to compare, and the tool says so (`GATE VOID`).
- **`-o`** writes the plain `faust` output of the winner. To build an application, pass the winning options to `faust` with your own architecture file :

  ```
  faust -lang ocpp -ls-fuse -ls-latency 4 -ls-regs3 -ls-R 40 -ls-load 0 -ls-regstate \
        -a jack-gtk.cpp examples/reverb/freeverb.dsp -o freeverb.cpp
  ```

**Choosing the judge.** Time with the C++ compiler, the flags and the precision you ship with :

| Setting | Default | Role |
| :--- | :--- | :--- |
| `FAUST` | `faust` on the `PATH` | the Faust compiler |
| `CXX` | `clang++` | the C++ compiler that builds and times the candidates |
| `FCBENCH_CXXFLAGS` | `-O3 -ffast-math -fbracket-depth=1024` | its optimisation flags ; the last one is clang's |
| `FCBENCH_ARCH_FLAGS` | `-march=native` | the target flags |
| `--double` | single precision | elect for a double build : the ranking can change between the two |

For example, for g++ and a double build :

```
CXX=g++ FCBENCH_CXXFLAGS="-O3 -ffast-math" fcautotool --double examples/reverb/freeverb.dsp
```

With several entry points in one file, `--pn NAME` elects for one of them.

**Going further with `fcgentool`.** Its genome is made of the options the installed `faust` accepts : scheduler, `R`, `U`, fusion, split, staging, `-fir`, `-lsum`, the selection options, `-rp`. It evolves them by tournament, crossover and mutation under the same judge, and the champion goes through the same safeguard :

```
fcgentool examples/reverb/freeverb.dsp --pop 16 --gens 20
```

A short run (`--pop 6 --gens 3`) prints :

```
fcgentool: faust = /Users/.../faust/build/bin/faust
fcgentool: c++ = /opt/local/bin/clang++ (clang version 22.1.8) -O3 -ffast-math -fbracket-depth=1024 -march=native
fcgentool: bred in single precision  (--double to breed for a double build)
fcgentool: genome = 12 genes ['R', 'U', 'fir', 'fuse', 'gq', 'lazy', 'ls', 'lsum', 'rp', 'sched', 'sn', 'temp'] (115200 combinations)
gen  0 : best=  13.813 (global   13.813) evals=6 : -ls-R 2 -ls-U 2 -lazyselect -gatequiv -selectn {}
...
CHAMPION VALID: 13.813 ns (single precision) : -ls-R 2 -ls-U 2 -lazyselect -gatequiv -selectn
```

A real search takes hours, on mains power. `--pop`, `--gens`, `--stall`, `--mut`, `--elite`, `--tourney`, `--runs` and `--seed` tune it ; `--double` and `--pn` work as for `fcautotool`.

**How the two tools work together.** They share one file, the *recipe book*. `fcgentool` writes its champions into it ; `fcautotool` reads it and races the recipe it finds there against its own jury. The usual circuit :

1. `fcautotool` on every program, in a minute each ;
2. `fcgentool --book` on the programs that matter, overnight ;
3. `fcautotool` again, later, with the book at hand : the champion now runs in the election, beside the jury.

The book is a tab-separated text file, `fcrecipes.tsv` by default, one line per program and precision :

```
# fcgentool recipe book -- per-machine champions, injected by
# fcautotool as candidate 'bk' (correctness-gated at every use).
# basename	date	flags	env	precision
freeverb.dsp	2026-09-26	-ls-R 2 -ls-U 4 -lsum	-	single
```

`fcgentool --book` adds the line of its champion, only if the champion is valid, and replaces the earlier line of the same program in the same precision ; `--book FILE` names another file. `fcautotool` reads `./fcrecipes.tsv`, or the file named by `FCRECIPES`. When it finds the program there, in the precision it is electing in, it says so and races the recipe as candidate `bk` :

```
FCRECIPES=fcrecipes.tsv fcautotool examples/reverb/freeverb.dsp
fcautotool: book recipe joins the race (bk): -ls-R 2 -ls-U 4 -lsum
  ...
  bk        13.8130 ns  (-lang ocpp -ls-R 2 -ls-U 4 -lsum)
  ...
fcautotool: winner r3s (11.9870 ns/frame, single precision) -- ...
```

Here the recipe came from a three-generation run and loses to the jury's `r3s` : a recipe is not trusted, it is raced again and checked again at every use, so a stale or weak one simply loses. A recipe bred in the other precision is left out, and the tool says so :

```
fcautotool: book recipe skipped: bred in single, electing in double
```

Three things the book does not record, so keep them in mind :

- **the machine and the C++ compiler** a recipe was bred with : keep one book per machine and C++ compiler, and point `FCRECIPES` at the right one ;
- **the path of the program** : the key is the file name alone, so two programs named `freeverb.dsp` in different directories share one line ;
- **the entry point** : with `--pn`, two entry points of one file share one line too.

## Pitfalls

- **An inert option still changes the output file.** The generated code records its compilation options (`declare("compile_options", ...)` and a header comment). Remove those lines before deciding that two outputs differ. `-mdd 4096 -mdy 10`, for instance, changes no computation on the test corpus.
- **An option accepted is not an option applied.** Most `ocpp` options are silently ignored by `cpp` (\ref{sec:options}).
- **Contract options** (`-fam-align`) are safe only with an architecture file that keeps the contract.
- **The C++ vectoriser has cliffs.** Two emitted forms that differ by a few lines can run three times apart, because the C++ compiler vectorises one and not the other (the SLP vectoriser of clang is the usual cause). Before blaming registers or cache, compile once with `-fno-slp-vectorize` (clang) or `-fno-tree-slp-vectorize` (g++) : if the gap disappears, it was the vectoriser.
- **Results do not survive a change of C++ compiler family** (\ref{sec:validity}), and sometimes not a change of release : measure again after an upgrade.

# Options outside this document \label{sec:outside}

These options belong to other backends or targets, or are accepted and ignored for the sake of other tools.

| Option | Belongs to |
| :--- | :--- |
| `-L` | the LLVM backend |
| `-noreprc` | the Rust backend |
| `-rnt` | the Rust backend |
| `-rnlm` | the Rust backend |
| `-vhdl-trace` | the VHDL backend |
| `-vhdl-float` | the VHDL backend |
| `-vhdl-components` | the VHDL backend |
| `-fpga-mem` | FPGA targets |
| `-fpga-mem-th` | FPGA targets |
| `-ocl` | OpenCL task generation |
| `-cuda` | CUDA task generation |
| `-lm` | accepted and ignored, for the faust2... scripts (not in -h) |
| `-rm` | accepted and ignored, for the faust2... scripts (not in -h) |
| `-poly` | accepted and ignored, for the faust2... scripts (not in -h) |
| `-voices` | accepted and ignored, for the faust2... scripts (not in -h) |
| `-group` | accepted and ignored, for the faust2... scripts (not in -h) |

# Keeping this document in sync \label{sec:sync}

`tests/doc-tests/check-compiling-doc.py` fails when an option printed by `faust -h` is missing here, when an option listed here is no longer printed by `faust -h` (unless its row says `(not in -h)`), or when an environment variable the compiler reads is not named here. Run it after adding, renaming or removing an option :

```
python3 tests/doc-tests/check-compiling-doc.py build/bin/faust
```

The `Backends` column was established by compiling the test programs of `tests/impulse-tests/dsp/` with and without each option, under each backend, and comparing the generated code with its option lines removed. Re-run such a check when an option moves between backends.
