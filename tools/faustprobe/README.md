# faustprobe

`faustprobe` compiles a Faust program with the LLVM JIT, sets its controls from
the command line, renders it offline, and prints numbers. It answers what
reading a program does not: does it compile, what does it output, is it finite,
how does it move with this control.

It is the C++ port of the `faustprobe` of faust-rs (`crates/cranelift-ffi`), with the same flags, the same output and the same exit
statuses, except for the differences listed below.

## Building

It needs a libfaust that holds the LLVM backend, `libfaustwithllvm.a`, and its
headers; `faust -libdir` and `faust -includedir` say where they are.

```sh
make            # FAUST=path/to/faust to use another installation
make test
make install    # PREFIX=/usr/local and DESTDIR= as elsewhere
```

At the root of the repository, `make benchmark` builds it with the rest of the
benchmark tools, against the library of the build tree, and `make devinstall`
installs it.

`make test` runs `tests/unit` (the text of numbers, JSON, audio files, the
analyses) and `tests/run.sh` (the command line, on small programs in `tests/dsp`
whose outputs are known). Neither needs the Faust standard libraries.

## Using it

```sh
# does it compile, and is it finite?
faustprobe --double -n 1 --in zero --quiet file.dsp

# what controls does it have?
faustprobe --list-params file.dsp

# render, with statistics only
faustprobe --double --in sine:440 -n 8192 --skip 2048 --quiet --set cutoff=500 file.dsp

# a sweep, one number per point
faustprobe --double --in sine:440 -n 8192 --skip 2048 --sweep cutoff=200,440,2000 --reduce rms file.dsp

# an expression evaluated in the scope of a file, a library included
faustprobe --double -n 6 --eval 'fi.lowpass(2, 1000)' /usr/local/share/faust/stdfaust.lib

# the frequency response of a filter, refused if it is not linear
faustprobe --double --eval 'fi.lowpass(4, 1000)' --freqresp 16 /usr/local/share/faust/stdfaust.lib

# did this change a sample?
faustprobe --double -n 8192 --quiet --compare new.dsp old.dsp
faustprobe --double -n 8192 --quiet --check all file.dsp

# a polyphonic instrument
faustprobe --double --nvoices 8 --note 60:100@0..22050 -n 44100 --quiet file.dsp

# fit controls by descent: a program whose outputs are a loss and its gradients
faustprobe --double --in white:1 --block 256 --train g1,g2 --fd-check=both tests/dsp/gain_fit.dsp

# block diagrams, into a directory of their own
faustprobe --svg figures --fold 3 file.dsp
```

`faustprobe --help` lists every flag. What the tool says is meant to be read:

- **The exit status is the verdict**: 0, 1 on any failure (a compile error, an
  unknown control, a value outside its range, non-finite samples, a comparison
  that fails), 2 on a command line that was not understood.
- **The default output is one row per frame**: `--quiet` keeps the statistics.
- **Numbers are the shortest text that parses back to the same float**, at the
  width the program was compiled in. `--precision 9` gives fixed decimals.
- **Measure in `-double`.**
- **A value outside its control's range is an error**; `--clamp` accepts it and
  says so.
- A `# note:` line is a fact the statistics do not show: read it.

## Differences from the faust-rs tool

| What | Here | Why |
|---|---|---|
| Compiler | the C++ compiler, LLVM JIT | `--opt-level` is LLVM's |
| `rad`, `ondemand`, `upsampling`... | what this compiler's language has | `--train` works on any program that outputs a loss and its gradients |
| Compile errors | libfaust's text | no codes, no fixes, no columns: `<eval k>:1 : ERROR : ...` |
| `--error-format json` | refused | libfaust has no diagnostics report |
| `--color` | absent | libfaust's text has no colors |
| `-bra-tape`, `-table-init` | not options | they are faust-rs's |
| `-ftz N` | accepted | |
| `--list-params` | the kind column is aligned; in double precision the bounds are exact | |
| `--svg` | the compiler's drawing, moved into DIR and renamed | a file is named after its definition; the title of a sub-diagram is its definition's name |
| Usage errors | same exit status, not the same wording | no argument-parsing library |
| `--check determinism` | the program key is `getSHAKey()` | |

The soundfile a program reads is the in-memory fixture of the impulse tests, as
in faust-rs: the tool does not load audio files for `soundfile`.

### Fast math is off

By default libfaust marks the floating-point operations of its LLVM IR with
fast-math flags, which let LLVM change a result in its last digits. The tool sets
`FAUST_OPT=FAUST_LLVM_NO_FM`, whatever the libfaust it is linked with: what it owes
is the samples of the program, and every `--opt-level` gives the reference of all
99 programs of the impulse-test corpus. What a libfaust host with default settings
gets is what an empty value shows, a `FAUST_OPT` set by the user being left alone:

```sh
FAUST_OPT= faustprobe --opt-level -1 ...
```

With a libfaust older than commit `78de467cb`, this also avoids a wrong result.
Those versions leave the `afn` flag on, and from `-O1` up LLVM then computes
`pow(C, x)` as `exp2(log2(C) * x)`, which is not exact: `pow(53, 1)` gives
52.999999999999986 where `-O0` gives 53, and a length made from it by truncation
loses a sample. Of the powers of the first 16 primes up to the 8th, 51 of 144 end
up one short that way. `reverb_designer.dsp`, whose delay lengths are
`int(pow(prime, floor(...)) - 1)`, departs from its reference by 0.03 at frame 2195.

### The module is reloaded before the JIT

The tool sets `FAUST_LLVM_RELOAD`, which makes libfaust reload its LLVM module from
bitcode before the JIT. On AArch64 the JIT at `-O0` miscompiles some programs:
in `process = d, max(-1, d);` with an integer `d` that depends on a recursion, the
second output folds to -1, though the IR is correct and the reloaded module gives
the right samples. Why the reload avoids it is not known. Five `*_jump_test`
definitions of the Faust libraries depart from faust-rs without it, by up to 28 %.

Any value of the variable turns the reload on, so the tool has no way to turn it
off. A libfaust older than the commit that added the variable ignores it.

`--opt-level` defaults to 0, as in faust-rs. It renders about eight times slower
on a small filter: use `-1` for long renders and with `--time`.

## How it was checked

- the 306 hand-written commands of the faust-rs snapshot test, run through both
  tools, `rad` programs replaced by `tests/dsp/gain_fit.dsp`: the same exit status
  but for the two that pass `-bra-tape`, and the same text and numbers but for the
  differences above and what two compilers leave in the last digits (samples
  apart by 1e-16 in double precision, a level of -334 dB on a null);
- `--protocol impulse-test --double` against the C++ references of
  `tests/impulse-tests/reference`, compared on the 15000 frames of the scalar pass
  with an absolute tolerance of 1e-3: 99 programs of 99, at `--opt-level` 0 and 3;
- the same commands under AddressSanitizer and UndefinedBehaviorSanitizer.

## Layout

| File | Holds |
|---|---|
| `faustprobe.cpp` | `main`, the choice of the mode |
| `cli` | the command line |
| `report` | what the modes share: setup, range checks, how a result is said, failures, measures |
| `engine` | excitation, statistics, schedule, sweep, controls, factory, instance |
| `poly` | the voices of `poly-dsp.h`, at a width chosen at run time |
| `train` | the descent, the grid, the finite differences |
| `eval` | `--eval` |
| `analysis` | comparison, spectrum, descriptors, frequency response, timing: no DSP |
| `audio` | `.wav`, `.npy`, raw samples |
| `text`, `json` | how a number and a document are written |
| `mode_*.cpp` | one mode each |
