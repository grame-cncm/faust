# Csound opcode generation tests

These tests run the checkout's `faust2csound` script, load its generated
plugins, and compare rendered samples. They cover audio input and controls,
the sample rate, zero-input DSPs, and an instrument with a local block size.

Run with matching Csound headers and binary, a Faust compiler, and a C++
compiler. For example, on Linux:

```sh
FAUST=/path/to/faust \
CSOUND=/path/to/csound \
CSOUND_INCLUDE_DIR=/path/to/include/csound \
CXX=c++ \
python3 tests/faust2csound-tests/test_faust2csound.py
```

On macOS, use the Csound framework's `Headers` directory. Run the same test
with Csound 6 and Csound 7 to check both plugin APIs. The tests create all
generated files in a temporary directory and require no audio device.
