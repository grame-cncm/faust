# NNX Backend Tests

This directory contains tests for the Faust NNX backend using the minimal.py architecture file.

## Structure

- `dsp/` - Directory containing DSP test files
- `generated/` - Directory for generated Python files and test results (created by Makefile)
- `Makefile` - Build and test automation

## Usage

### Running Tests

Run all tests:
```bash
make
# or
make test
```

Test a specific DSP file:
```bash
make test-simple_gain    # Compile and test simple_gain.dsp
```

Only compile a DSP file without running:
```bash
make compile-simple_gain  # Only compile, don't run
```

Run a previously compiled Python file:
```bash
make run-simple_gain      # Run the already compiled simple_gain.py
```

Clean all generated files:
```bash
make clean
```

Show help and all available commands:
```bash
make help
```

### Adding New Tests

1. Add a `.dsp` file to the `dsp/` directory
2. Run `make` to test all files, or `make test-<filename>` to test just your new file

### Test Output

The Makefile will:
1. Compile each `.dsp` file in `dsp/` to a Python file using the NNX backend
2. Run each generated Python file with `--duration 0.1 --jit`
3. Report success/failure for each test
4. Provide a summary of all test results

Generated files in the `generated/` directory:
- `*.py` - Generated Python code (kept for debugging)
- `*.test` - Test result (contains "PASSED" or "FAILED: reason")
- `*.compile.log` - Compilation output
- `*.output.log` - Runtime output

Note: Generated Python files are preserved (not automatically deleted) to help with debugging.

## Options

You can customize the build with environment variables:

```bash
# Use a different Faust compiler
FAUST=../../build/bin/faust make

# Use a different Python interpreter
PYTHON=python3.11 make

# Add additional Faust options
# If you use -double, then the python file should also be executed with "--double"
FAUSTOPTIONS="-lang nnx -a ../../architecture/jax/minimal.py -double" make
```

## Example DSP Files

Place test DSP files in the `dsp/` directory. For example:

```faust
// dsp/simple_gain.dsp
process = *(0.5);
```

## Special Tests

### Random Number Generation Tests

The following tests verify the JAX PRNG integration:
- `random_test.dsp` - Tests basic random_uniform foreign function
- `random_uniform.dsp` - Tests stereo random generation

These tests use a custom test script (`tests/test_random_basic.py`) that verifies:
1. Random values are actually random (not constant)
2. Values are in the correct range [-1, 1]
3. Distribution is roughly uniform
4. JAX PRNG is being used (not linear congruential generator)

To use JAX random generation in your DSP code:
```faust
import("stdfaust.lib");

// Declare JAX's random uniform function as a foreign function
random_uniform = ffunction(float random_uniform(), <math.h>, "");

// Use it to generate random values in [-1, 1]
process = random_uniform;
```

## Requirements

- Faust compiler built with NNX backend support
- Python 3 with the following packages:
  - `jax` and `jaxlib` - JAX framework
  - `numpy` - Numerical operations
  - `tqdm` - Progress bars for JIT benchmarking
  - `flax` - Neural network library used by the NNX backend
  - `librosa` (optional) - For loading audio files
  - `scipy` (optional) - For saving WAV output files

Install requirements:
```bash
pip install jax jaxlib numpy tqdm flax librosa scipy
```

## CI/CD Integration

This test suite is integrated with GitHub Actions via `.github/workflows/jax-tests.yml`. The workflow:
1. Builds Faust once and shares the build artifacts
2. Runs parallel test jobs:
   - NNX and Linen impulse tests (`tests/impulse-tests`)
   - NNX minimal architecture tests (this test suite)
   - The pytest suite
3. Tests are run on Ubuntu with Python 3.11

## Troubleshooting

If a test fails:
1. Check the compilation log: `generated/<testname>.compile.log`
2. Check the runtime output: `generated/<testname>.output.log`
3. Examine the generated Python code: `generated/<testname>.py`
4. The test result file `generated/<testname>.test` will indicate if it was a compilation or runtime error

Known issues:
- **Missing function error (e.g., `fillmydspSIG0SIG0`)**: This is why `waveform_tabulate.dsp` fails. It is excluded from the default `make` run (see `KNOWN_FAILURES` in the Makefile); run it manually with `make test-waveform_tabulate`. See https://github.com/grame-cncm/faust/issues/737
