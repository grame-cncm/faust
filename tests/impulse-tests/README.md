# FAUST Impulse Response Tests  #

This test suite allows to check that the compiler generates correct code by comparing the impulse response of a set of Faust programs with the expected one.


### Prerequisites
- `faust` and `libfaust.a` must be available from the `../../build/bin` and `../../build/lib/` folders. They must be compiled with all backends.
- `NodeJS` must be installed to check the asm-js and wasm backends. See the [NodeJS](https://nodejs.org/) web site.

### How to run the Tests
Two test systems co-exist for historical reasons:
- a system based on makefiles
- a system based on shell scripts

The principle of both test systems is to generate impulse responses for each of the Faust programs that are in the `dsp` folder. Each of these responses is compared with its reference response (with a low tolerance). The `reference` folder contains the reference impulse responses.

There is a significant intersection between the tests performed by the two systems.


#### Using the Makefile
The use of `make` allows to benefit from parallelism (option -j n).
The generated impulse responses are stored in a folder named `ir`.
Type `make help` for details about the available targets.

There is no target `clean`: simply delete the `ir` folder or one of its subfolders to regenerate the impulse responses.

**Note**:

when using the make option `-j`, I suggest to also add a `-i` option (`--ignore-errors : Ignore errors from commands`), especially with the 'cpp' and 'c' targets. Indeed, make should first _1)_ build all the C++ and/or C output, _2)_ compile these output and _3)_ finally run the Faust program and check the result.

If `make` fails with the first check and since intermediate files are removed, the steps _1)_ and _2)_ will restart from the beginning (which is quite time consuming) on next run. With the `-i` option, `make` will run to the end and on next run, only the faulty dsp will be rebuild.


#### Using the shell scripts
The main script is `test.sh`. Type `test.sh -help` for details about the available tests.

The generated impulse responses are not preserved by the shell scripts. Intermediate files may be generated in the dsp folder without being deleted.

You should run `make tools` before first run of `tests.sh`.


### To do
- add precision arg to filesCompare (for float and fastmath outputs)
- check that all test.sh subscripts are based on the current development branch and don't require any installation
- simplify and rename the `faust2impulse_xxx_` scripts

### Obsolete Files
- install.sh
- testwithmute.sh
