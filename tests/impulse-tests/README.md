# FAUST Impulse Response Tests #

This test suite allows to check that the compiler generates correct code by comparing the impulse response of a set of Faust programs with the expected one. When the DSP code contains buttons, they are set to 1 at the first sample to simulate button press.

### Prerequisites

- `faust`, `libfaust.a` and `libfaustmachine.a` must be available from the `../../build/bin` and `../../build/lib/` folders. They must be compiled with all backends.
- `NodeJS` must be installed to check the wasm/wast backends. See the [NodeJS](https://nodejs.org/) web site.

### How to run the Tests

Two test systems co-exist for historical reasons:
- a system based on makefiles
- a system based on shell scripts (**deprecated**)

The principle of both test systems is to generate impulse responses for each of the Faust programs that are in the `dsp` folder. Each of these responses is compared with its reference response (with a low tolerance). The `reference` folder contains the reference impulse responses.

There is a significant intersection between the tests performed by the two systems.

#### Using the Makefile

The use of `make` allows to benefit from parallelism (option -j n).
The generated impulse responses are stored in a folder named `ir`.
Type `make help` for details about the available targets.

`make clean-ir` deletes generated impulse-test sources, executables and responses
under `ir/`; run it before each comparison. `make clean` removes the test
harness executables.

##### Java impulse responses

`make java` (or `make leg/java/double`) generates the corpus in `-double`
using `archs/impulsearch.java`, compiles it with `javac`, runs it with `java`,
and compares the results with the existing `reference/` files via
`filesCompare`. Sources, classes and responses are kept in `ir/java/double/`.

```sh
make -C tests/impulse-tests clean-ir
make -C tests/impulse-tests java -k -j4 FAUST="$(pwd)/build/bin/faust" \
  JAVA=/path/to/jdk/bin/java JAVAC=/path/to/jdk/bin/javac
```

The test requires Python 3 and a working JDK. Tool selection uses explicit
`JAVA`/`JAVAC` overrides first, then `JAVA_HOME`, the macOS JDK locator, and
finally `PATH`. For example, with a JDK installed:

```sh
JAVA_HOME=/path/to/jdk make -C tests/impulse-tests java -k -j4 \
  FAUST="$(pwd)/build/bin/faust"
```

`JAVAFLAGS` and `JAVACFLAGS` allow extra toolchain options. Preflight prints
the compiler source commit and JDK versions, compiles and runs a small Java
program, then exercises the validator and comparator with negative controls.
A missing or incompatible JDK fails with instructions for configuring it.

Every invocation regenerates and compiles the selected corpus, executes each
DSP in fixed and fragmented modes and performs all comparisons, including when `ir/` already exists.
The modes use fixed 64-frame blocks and deterministic fragmented blocks
(1, 7, 3, 19, 2, 11, 5 frames), keeping the same input and control timeline.
Each response is compared with the reference and the modes are compared with
each other. A passing program reports two reference comparisons and one
block-partition comparison. `bs.dsp` runs only in fixed mode because its foreign
`count` variable makes the signal depend on block size; this exclusion is
reported explicitly. `-k` continues through the corpus after a failure;
the final success summary is printed only if every selected program passed.

`tools/java-impulse.py` validates header labels, dimensions, frame count,
consecutive indices, channel counts, finite samples and end of file before
calling `filesCompare`. Automatic negative controls cover altered values,
truncated/empty responses, bad headers/indices/channel counts, NaN/infinity
and extra data. Failed generation, compilation, execution or comparison
fails the target; incomplete output is removed.

The architecture matches the first 15000-frame scalar segment of the native
reference: 44100 Hz, an impulse on every input, default UI controls and
buttons pressed for the first 64 frames. `filesCompare -part` compares that
segment without regenerating references. The polyphonic segments of the
C++ harness are not exercised by this architecture.
`sound.dsp` is explicitly excluded because Java has no soundfile support.
Targeted math regressions remain in `tests/compile-tests/java-math.py`.
The Ubuntu workflow runs this gate with Temurin JDK 21.

##### AssemblyScript shortcut

From `tests/impulse-tests`, you can run AssemblyScript impulse tests with:

`make asc`

This is a shortcut for `make -f Make.assemblyscript assemblyscript`.
From the repository root, the equivalent command is:

`make -C tests/impulse-tests asc`

To run the quick reference subset check:

`make -f Make.assemblyscript assemblyscript-compare-quick compare=1`

### Testing the Box, Signal, Type and FIR intermediate steps

- the Box tree (created by the `-e`option) can be generated as a textual file. A set of references files can be created using `make reference-box`, then tested using `make test-box`.
- the Signal tree (created by the `-norm1`option) can be generated as a textual file. A set of references files can be created using `make reference-signal`, then tested using `make test-signal`.
- the Type tree (created by the `-norm2`option) can be generated as a textual file. A set of references files can be created using `make reference-type`, then tested using `make test-type`.
- the FIR output can be generated as a textual file. A set of references files can be created using `make reference-fir`, then tested using `make test-fir`.

### Testing C++ output

- the C++ output can be generated. A set of references files can be created using `make reference-cpp`, then tested using `make test-cpp`.

### Testing CPU performance

- `make bench` test CPU performance using the LLVM backend, C++ backend and old C++ backend. 

### Checking the FIR

An experimental FIR checker can be activated for all backends testing using `export FAUST_DEBUG=FIR_CHECKER`.

**Note**:

When using the make option `-j`, I suggest to also add a `-i` option (`--ignore-errors : Ignore errors from commands`), especially with the 'cpp' and 'c' targets. Indeed, make should first _1)_ build all the C++ and/or C output, _2)_ compile these output and _3)_ finally run the Faust program and check the result.

If `make` fails with the first check and since intermediate files are removed, the steps _1)_ and _2)_ will restart from the beginning (which is quite time consuming) on next run. With the `-i` option, `make` will run to the end and on next run, only the faulty DSP will be rebuilt.

#### Using the shell scripts (**deprecated**)

The main script is `test.sh`. Type `test.sh -help` for details about the available tests.

The generated impulse responses are not preserved by the shell scripts. Intermediate files may be generated in the dsp folder without being deleted.

You should run `make tools` before first run of `tests.sh`.

### NNX and Linen tests

#### Prerequisites

- `faust` must be available from the `../../build/bin` folder. It must be compiled with the NNX and Linen backends
- install the python requirements: `pip install -r requirements.txt`
- install [JAX](https://jax.readthedocs.io/en/latest/) and [Flax](https://flax.readthedocs.io/en/latest/):
  - For new environments: `pip install jax-ai-stack` (includes JAX, Flax, and other useful libraries with pinned versions)
  - For CI/existing environments: `pip install --upgrade jax jaxlib flax` (installs latest versions)

#### Debugging a single failing NNX test

Instead of re-running the full suite, generate, run, and compare one DSP at a time:

```bash
FAUST=$PWD/../../build/bin/faust
mkdir -p ir/nnx/double

# Generate the Python code for a specific file
$FAUST -lang nnx dsp/table2.dsp -a archs/impulse_nnx.py -double > ir/nnx/double/nnx_table2.py

# Run it to produce the impulse response
python3 ir/nnx/double/nnx_table2.py > ir/nnx/double/table2.ir

# Compare against the reference
./filesCompare ir/nnx/double/table2.ir reference/table2.ir
```

When the output differs, two comparisons help locate the problem:

```bash
# Inspect the compiler's intermediate representation
$FAUST -lang nnx dsp/table2.dsp -d > /tmp/table2_debug.txt

# Generate the C++ version of the same DSP to see the expected structure
$FAUST -lang cpp dsp/table2.dsp -o /tmp/table2.cpp
```

The same workflow applies to the Linen backend with `-lang linen` and `archs/impulse_linen.py`.

### TODO

- add precision arg to `filesCompare` (for float and fastmath outputs)
- check that all `test.sh` subscripts are based on the current development branch and don't require any installation
- simplify and rename the `faust2impulse_xxx_` scripts

### Deprecated Files
- `install.sh`
- `testwithmute.sh`
