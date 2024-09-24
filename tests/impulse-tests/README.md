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

There is no target `clean`: simply delete the `ir` folder or one of its subfolders to regenerate the impulse responses.

### Testing the Box, Signal, Type and FIR intermediate steps

- the Box tree (created by the `-e`option) can be generated as a textual file. A set of references files can be created using `make reference-box`, then tested using `make test-box`.
- the Signal tree (created by the `-norm1`option) can be generated as a textual file. A set of references files can be created using `make reference-signal`, then tested using `make test-signal`.
- the Type tree (created by the `-norm2`option) can be generated as a textual file. A set of references files can be created using `make reference-type`, then tested using `make test-type`.
- the FIR output can be generated as a textual file. A set of references files can be created using `make reference-fir`, then tested using `make test-fir`.

### Testing C++ output

- the C++ output can be generated. A set of references files can be created using `make reference-cpp`, then tested using `make test-cpp`.


### Checking the FIR

An experimental FIR checker can be activated for all backends testing using `export FAUST_DEBUG=FIR_CHECKER`.

**Note**:

When using the make option `-j`, I suggest to also add a `-i` option (`--ignore-errors : Ignore errors from commands`), especially with the 'cpp' and 'c' targets. Indeed, make should first _1)_ build all the C++ and/or C output, _2)_ compile these output and _3)_ finally run the Faust program and check the result.

If `make` fails with the first check and since intermediate files are removed, the steps _1)_ and _2)_ will restart from the beginning (which is quite time consuming) on next run. With the `-i` option, `make` will run to the end and on next run, only the faulty DSP will be rebuilt.

#### Using the shell scripts (**deprecated**)

The main script is `test.sh`. Type `test.sh -help` for details about the available tests.

The generated impulse responses are not preserved by the shell scripts. Intermediate files may be generated in the dsp folder without being deleted.

You should run `make tools` before first run of `tests.sh`.

### JAX tests

#### Prerequisites

- `faust` must be available from the `../../build/bin` folder. It must be compiled with the JAX backend
- install the python requirements: `pip install -r requirements.txt`
- install [JAX](https://jax.readthedocs.io/en/latest/) and [Flax](https://flax.readthedocs.io/en/latest/). These are harder to install, so they're left out of `requirements.txt`

### To do

- add precision arg to `filesCompare` (for float and fastmath outputs)
- check that all `test.sh` subscripts are based on the current development branch and don't require any installation
- simplify and rename the `faust2impulse_xxx_` scripts

### Deprecated Files
- `install.sh`
- `testwithmute.sh`
