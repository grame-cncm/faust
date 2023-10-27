# Comparator

A fixedpoint/float Faust compilation comparator tool.

## Compile with faust2comparator script

* Run `faust2comparator <file.dsp> [Faust options]`

For example, to impose a fixed width of 48 to fixed-point types in `foo.dsp`, run `faust2comparator foo.dsp -fx-size 48`

# Comparator use 

## Options

Once the comparator program is compiled, it can be invoked with the following options:
* `-l`: log the fixed-point and floating-point samples to a text file (named `samples-<program name>.log`)
* `-w`: write the fixed-point and floating-point outputs to sound files (named respectively `fixed-<program name>.wav` and `float-<program name>.wav`)
* `-n`: number of samples over which the statistical indicators are computed (by default 200)
* `-h`: display help

## Output 

The comparator outputs several statistical indicators regarding the numerical differences between floating-point and fixed-point programs outputs.
It measures this difference over the first $n$ samples (by default 200), and displays the sum of these differences, the mean error for one sample, the maximum error, and the signal-to-noise ratio, defined as follows:

$$SNR = \log(\lVert\frac{s\_{FL}}{s\_{FL} -s\_{FX}}\rVert)$$
