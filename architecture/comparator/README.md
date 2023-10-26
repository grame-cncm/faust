# Comparator
fixedpoint/float faust compilation comparator

## Compile with make

* `make all` (to create fixed.cpp float.cpp out)
* `./out`

* to clean everything `make clean`

## Compile with faust2comparator script

## Run the complete test 

Use script `compare.sh <file.dsp>`.

# Comparator options

* `-l`: log the fixed-point and floating-point samples to a text file (named `samples-<program name>.log`)
* `-w`: write the fixed-point and floating-point outputs to sound files (named respectively `fixed-<program name>.wav` and `float-<program name>.wav`)
* `-h`: display help
