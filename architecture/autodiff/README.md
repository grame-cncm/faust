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

Copy required files from the Faust architecture directory to the output directory:

```shell
outputdir=~/tmp/faust-autodiff
autodiffdir=$(faust --archdir)/autodiff
mkdir -p $outputdir
cp $autodiffdir/autodiff.h \
  $autodiffdir/autodiff.cpp \
  $autodiffdir/dspFactoryOwner.h \
  $autodiffdir/plot.py \
  $outputdir
```

Compile the generated cpp file.
Autodiff architecture uses libfaust to dynamically compile Faust algorithms
at runtime, so `llvm-config` must be used to determine the appropriate
LLVM library to link to.

```shell
outputdir=~/tmp/faust-autodiff
cd $outputdir || exit
c++ -std=c++14 autodiff.cpp /usr/local/lib/libfaust.a \
  $(llvm-config --ldflags --libs all --system-libs) \
  -o autodiff_example
```

### Missing library `-lzstd`

For LLVM 16 on Mac OS X, your c++ compiler may not be able to find the
[zstd](https://facebook.github.io/zstd/) library.
The easiest remedy is to install it via homebrew:

```shell
brew install zstd
```

and adjust the call to `c++` as follows:

```shell
c++ -std=c++14 autodiff.cpp /usr/local/lib/libfaust.a \
  $(llvm-config --ldflags --libs all --system-libs) \
  -L/opt/local/lib \
  -o autodiff_example
```

## Running an autodiff example

Run the compiled executable, specifying the following dsp files:

- `--input` &mdash; the signal to run through the ground truth and
  differentiable dsp algorithms;
- `--gt` &mdash; the ground truth dsp;
- `--diff` &mdash; the differentiable dsp to be trained/optimised.

- it is also possible to specify the loss function to use via the optional
  `-lf|--lossfunction <function>` flag.
  Implemented loss functions are:
    - `l1` &mdash; L-1 norm;
    - `l2` (default) &mdash; L-2 norm.

- supply `-lr|--learningrate <rate>` to set a floating-point number to use 
  as the learning rate (if not provided, the default 0.1).

```shell
outputdir=~/tmp/faust-autodiff
cd $outputdir || exit
examplesdir=$(faust --archdir)/examples/autodiff
./autodiff_example --input $examplesdir/noise.dsp \
  --gt $examplesdir/gain/gt.dsp \
  --diff $examplesdir/gain/diff.dsp \
  -lf l2 \
  -lr 0.1
```

> The above commands are encapsulated in [autodiff.sh](autodiff.sh).
>
>```shell
>./autodiff.sh <example_name>
>```
>
>For a list of available examples, execute `./autodiff.sh` without any arguments.

Running the executable displays numerical output describing the gradient descent process:

```
Learnable parameter: /Parallelizer/DSP2/Parallelizer/DSP1/Sequencer/DSP2/diff/alpha, value: 0
    1     Sig GT:   -0.9990000129  Sig Learn:   -0.9990000129       Loss:    0.0000000000
    2     Sig GT:   -1.9870100021  Sig Learn:   -0.9980000257       Loss:    0.9890099764
    .      alpha:      ds/dp:   -0.9990000129       Grad:   -0.9990000129      Value:    0.0998999998
    3     Sig GT:   -1.9850200415  Sig Learn:   -1.0967001915       Loss:    0.8883198500
    .      alpha:      ds/dp:   -0.9980000257       Grad:   -0.9980000257      Value:    0.1996999979
    4     Sig GT:   -1.9830299616  Sig Learn:   -1.1951009035       Loss:    0.7879290581
    .      alpha:      ds/dp:   -0.9969999790       Grad:   -0.9969999790      Value:    0.2994000018
    5     Sig GT:   -1.9810400009  Sig Learn:   -1.2932024002       Loss:    0.6878376007
    .      alpha:      ds/dp:   -0.9959999919       Grad:   -0.9959999919      Value:    0.3989999890
    ...
```

Run `python3 plot.py` in the output directory to produce a plot of loss against parameter 
value and iteration, and parameter value against iteration (requires matplotlib).

![Loss plot example](loss_example.png)

## Tips

- Call the Faust compiler with your differentiable DSP algorithm 
  to see the differentiated `compute` method in your output .cpp file.

```shell
faust -diff -a $archdir/autodiff/autodiff.cpp \
  -o $outputdir/my_autodiff.cpp \
  $archdir/examples/autodiff/gain/diff.dsp
```

The generated `compute` method isn't used at runtime, but it may assist with 
verifying that your algorithm is being differentiated correctly.

- Additionally, provide the `-d|--details` flag to the Faust compiler to see 
  detailed output of the differentiation process.

E.g. for a differentiable gain slider:

```faust
process = _*(hslider("gain [diff:1]", .5, 0, 1, .001));
```

computation of the derivative is reported as follows:

```
>>> Differentiate wrt. hslider("gain [diff:1]",0.5f,0.0f,1.0f,0.001f)

	x: IN[0]	y: hslider("gain [diff:1]",0.5f,0.0f,1.0f,0.001f)	op: MUL

		UI element: hslider("gain [diff:1]",0.5f,0.0f,1.0f,0.001f)

		DERIVATIVE: 1.0f

		Input: IN[0]

		DERIVATIVE: 0.0f

	DERIVATIVE: 0.0f*hslider("gain [diff:1]",0.5f,0.0f,1.0f,0.001f)+IN[0]*1.0f
```

Since this algorithm, $y = gx$, is a product of the input signal and a gain value,
the product rule is employed:

$$
\begin{align}
\frac{dy}{dg} &= x\frac{d}{dg}(g) + g\frac{d}{dg}(x) \\
&= x(1) + g(0) \\
&= x
\end{align}
$$

# Verification via finite differences

The output of a differentiated DSP algorithm can be compared with a numerical 
derivative computed via finite differences.
This can be achieved with the `autodiffVerifier` utility, which takes a differentiable
DSP algorithm, and, for each parameter $p$, and a perturbation of that parameter
$\epsilon$, computes the delta between autodiffed output and finite difference output:

$$
\delta = \left|y'(p) - \frac{y(p + \epsilon) - y(p)}{\epsilon}\right|
$$

To build the verifier, copy the required files and compile `autodiffVerifier.cpp`:

```shell
outputdir=~/tmp/faust-autodiff
autodiffdir=$(faust --archdir)/autodiff
mkdir -p $outputdir
cp $autodiffdir/autodiffVerifier.h \
  $autodiffdir/autodiffVerifier.cpp \
  $autodiffdir/dspFactoryOwner.h \
  $outputdir
cd $outputdir || exit
c++ -std=c++14 autodiffVerifier.cpp /usr/local/lib/libfaust.a \
  $(llvm-config --ldflags --libs all --system-libs) \
  -o verify
```

Then run the resulting executable, specifying input and differentiable DSP files,
and an optional value for $\epsilon$ (default 1e-3).

```shell
outputdir=~/tmp/faust-autodiff
cd $outputdir || exit
examplesdir=$(faust --archdir)/examples/autodiff
./verify --input $examplesdir/noise.dsp \
  --diff $examplesdir/gain/diff.dsp \
  --epsilon 1e-3
```

The differentiable DSP algorithm is compiled in (at least) three forms:
- unmodified: $y(\mathbf{P})$
- with $\epsilon$ applied to each adjustable parameter in turn
  - for multiple parameters, as many copies are made of the DSP as there are
    parameters, each copy having one parameter increased by $\epsilon$
  - for the $k$th parameter: $y(\dots,p_k + \epsilon,\dots)$
- automatically differentiated: $y'(\mathbf{P})$

These are used to compute $\delta$ for each parameter.
