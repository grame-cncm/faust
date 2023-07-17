# Differentiable DSP

Using `[diff:on]` or `[diff:1]` parameter metadata, and the `-diff` compiler flag,
it is possible to create differentiable DSP algorithms.

## Outlook

Algorithms are differentiated symbolically. 
This may be OK for simple algorithms, but _expression swell_ is a risk for more involved
DSP implementations.
A true automatic differentiation implementation may be required if the symbolic
approach proves unwieldy.

Currently, loss and gradient descent are calculated on a per-sample basis.
This is fine for a gain control acting on deterministic noise input, but more
sophisticated approaches will be required to tackle problems involving 
non-deterministic input, or frequency-domain loss.

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
  -o $outputdir/my_autodiff.cpp \
  $archdir/examples/autodiff/noop.dsp
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
c++ -std=c++14 my_autodiff.cpp /usr/local/lib/libfaust.a \
  $(llvm-config --ldflags --libs all --system-libs) \
  -o autodiff_example

./autodiff_example --input $archdir/examples/autodiff/noise.dsp \
  --gt $archdir/examples/autodiff/gain/gt.dsp \
  --diff $archdir/examples/autodiff/gain/diff.dsp
```

## Tips
- Instead of a dummy .dsp file, provide your differentiable DSP algorithm at compile time
  to see the differentiated `compute` method in your output .cpp file.
  - NB. this `compute` method isn't used at runtime, but it may assist with verifying that
    your algorithm is being differentiated correctly.
- Additionally, provide the `-d|--details` flag to the faust compiler to see detailed 
  output of the differentiation process.

E.g. for a differentiable gain slider:
```faust
process = _*(hslider("gain [diff:1]", .5, 0, 1, .001));
```
computation of the derivative is reported as follows:
```
>>> Differentiate wrt. hslider("gain [diff:1]",0.5f,0.0f,1.0f,0.001f)

x: IN[0]
y: hslider("gain [diff:1]",0.5f,0.0f,1.0f,0.001f)
op: MUL

UI/Input: hslider("gain [diff:1]",0.5f,0.0f,1.0f,0.001f)

DERIVATIVE: 1.0f

UI/Input: IN[0]

DERIVATIVE: 0.0f

DERIVATIVE: 0.0f*hslider("gain [diff:1]",0.5f,0.0f,1.0f,0.001f)+IN[0]*1.0f
```
Since this algorithm, $y = gx$, is a product, the product rule is employed:

$\frac{dy}{dg} = x\frac{d}{dg}(g) + g\frac{d}{dg}(x) = x(1) + g(0) = x$
