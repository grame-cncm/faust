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

Subject to future modifications to the Faust compiler, compiling and running
an autodiff example demands the following approach:

- Copy the `autodiff.h` header from the Faust architecture directory to the
  output directory;
- call `faust`, specifying the appropriate architecture file 
  (`-a $archdir/autodiff/autodiff.cpp`), the output cpp file to generate,
  and a (syntactically-valid) dummy dsp file;

```shell
outputdir=~/tmp/faust-autodiff
archdir=$(faust --archdir)
mkdir -p $outputdir
cp $(faust --archdir)/autodiff/autodiff.h $outputdir/autodiff.h
faust -diff -a $archdir/autodiff/autodiff.cpp \
  -o $outputdir/autodiff_example.cpp \
  $archdir/examples/autodiff/empty.dsp
```
Next:
- compile the generated cpp file;
  - autodiff architecture uses libfaust to dynamically compile Faust algorithms
    at runtime, so `llvm-config` must be used to determine the appropriate
    LLVM library to link to;
- finally, run the compiled executable, specifying the following dsp files:
  - `--input` &mdash; the signal to run through the ground truth and 
    differentiable dsp algorithms;
  - `--gt` &mdash; the ground truth dsp;
  - `--diff` &mdash; the differentiable dsp to be trained/optimised.

```shell
outputdir=~/tmp/faust-autodiff
archdir=$(faust --archdir)
cd $outputdir || exit
c++ -std=c++14 autodiff_example.cpp /usr/local/lib/libfaust.a \
  $(llvm-config --ldflags --libs all --system-libs) \
  -o autodiff_example

./autodiff_example --input $archdir/examples/autodiff/noise.dsp \
  --gt $archdir/examples/autodiff/fixed_gain.dsp \
  --diff $archdir/examples/autodiff/gain.dsp
```
