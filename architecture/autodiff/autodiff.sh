#!/bin/bash

echoHelp() {
  echo "autodiff.sh <autodiff_example_name>"
  exit
}

FAUSTARCH=$(faust -archdir)
AUTODIFF_EXAMPLES=$FAUSTARCH/examples/autodiff

if [ "$#" -eq 0 ]; then
  dirs=($(ls -d $AUTODIFF_EXAMPLES/*/ | xargs -n 1 basename | cut -f1 -d'/'))
  echo 'Please, provide the name of an automatic differentiation example to process.'
  echo "Available examples:"
  printf "%s\n" "${dirs[@]}"
  echo ''
  echoHelp
fi

######################
# Processing Arguments
######################

while [ $1 ]; do
  example=$1

  shift
done

###########################################
# Building and running the autodiff example
###########################################

# Copy files to the output directory.
OUTPUTDIR=~/tmp/faust-autodiff
mkdir -p $OUTPUTDIR

cp $FAUSTARCH/autodiff/autodiff.h $OUTPUTDIR/autodiff.h
cp $FAUSTARCH/autodiff/plot.py $OUTPUTDIR/plot.py

# Run the Faust compiler against the architecture file.
faust --details -diff -a $FAUSTARCH/autodiff/autodiff.cpp \
  -o $OUTPUTDIR/my_autodiff.cpp \
  $AUTODIFF_EXAMPLES/$example/diff.dsp

# Get the OS on which the script is running.
PLATFORM=$(uname -s | tr -s '[:upper:]' '[:lower:]')

FLAGS=$(llvm-config --ldflags --libs all --system-libs)

# Set extra library dirs as necessary.
# (NB. may be better to check against LLVM version rather than OS.)
case $PLATFORM in
darwin)
  FLAGS+=" -L/opt/local/lib"
  ;;
esac

c++ -std=c++14 $OUTPUTDIR/my_autodiff.cpp /usr/local/lib/libfaust.a \
  -o $OUTPUTDIR/my_autodiff $FLAGS

cd $OUTPUTDIR || exit

# Run the compiled executable.
if ! ./my_autodiff \
  --input $AUTODIFF_EXAMPLES/noise.dsp \
  --gt $AUTODIFF_EXAMPLES/$example/gt.dsp \
  --diff $AUTODIFF_EXAMPLES/$example/diff.dsp; then
  exit
fi

# Plot the results
# NB. matplotlib (and numpy) must be installed globally, e.g. `apt install python3-matplotlib`
python3 plot.py
