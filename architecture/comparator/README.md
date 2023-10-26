# Comparator
fixedpoint/float faust compilation comparator

## Compile with make

* `make all` (to create fixed.cpp float.cpp out)
* `./out`

* to clean everything `make clean`

## Compile with faust2comparator script

* Run `faust2comparator <file.dsp> [Faust options]`

For example, to impose a fixed width of 48 to fixed-point types in `foo.dsp`, run `faust2comparator foo.dsp -fx-size 48`

# Comparator options

Once the comparator program is compiled, it can be invoked with the following options:
* `-l`: log the fixed-point and floating-point samples to a text file (named `samples-<program name>.log`)
* `-w`: write the fixed-point and floating-point outputs to sound files (named respectively `fixed-<program name>.wav` and `float-<program name>.wav`)
* `-h`: display help
