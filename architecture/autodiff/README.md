# Differentiable DSP

## Faust installation

Faust must be compiled with inclusion of the dynamic Faust library. This is
easily (if not quickly) achieved via:

```shell
cd ../../build
make BACKENDS=all.cmake TARGETS=all.cmake
```
Followed by:
```shell
cd ../../build
sudo make install
```

## Compiling an autodiff example

The appropriate architecture file (`-a`) must be specified to the Faust 
compiler.
Assuming `pwd` is the directory containing this README file:

```shell
cd ../..
cp ./architecture/autodiff/autodiff.h .
faust -diff -a ./architecture/autodiff/autodiff.cpp \
  -o autodiff_gain.cpp \
  ./examples/autodiff/gain.dsp 
```

Then, to compile to C++ and run the compiled executable (again, `pwd` is 
`architecture/autodiff`):

```shell
cd ../..
c++ -std=c++11 autodiff_gain.cpp /usr/local/lib/libfaust.a \
  `llvm-config --ldflags --libs all --system-libs` \
  -o autodiff_gain

./autodiff_gain
```

Or all at once:
```shell
cd ~/devel/faust && \
cp ./architecture/autodiff/autodiff.h . && \
faust -diff -a ./architecture/autodiff/autodiff.cpp -o autodiff_gain.cpp ./examples/autodiff/gain.dsp && \
c++ -std=c++11 autodiff_gain.cpp /usr/local/lib/libfaust.a $(llvm-config --ldflags --libs all --system-libs) -o autodiff_gain && \
./autodiff_gain

```
