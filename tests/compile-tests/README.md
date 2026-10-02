
# Compile tests

### Prerequisites
- `faust` must be available from the command line or from the `build/bin` folder. It must be compiled with all backends but the `interp` backend.

### What's being done
All examples found is the `examples` and `regression` folders are compiled using all the available backends (apart the `interp` backend). In addition and for the c, cpp and ocpp backends, the output is also compiled using the available compilers.


Type `make help` for details on the available targets.


### Files excluded from tests

- `faust-stk` : the 'c' backend doesn't compile due to C++ specific implementation of foreign functions.
- `TODO` : files names containing TODO

### Fixed-point C++ table regression

`fixed-point-tables.py` compiles generated C++ with the shipped
`faust/dsp/fixed-point.h` and the Xilinx `ap_fixed.h` headers. It covers static
and writable real tables, mixed integer/real tables, several fixed-point sizes,
inline tables and the memory manager. Use a C++ compiler compatible with your
Xilinx headers (for example GCC with libstdc++):

```sh
python3 tests/compile-tests/fixed-point-tables.py \
  --faust build/bin/faust --cxx g++ \
  --ap-fixed-include /path/to/xilinx/include
```
