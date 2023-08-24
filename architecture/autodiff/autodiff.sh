#!/bin/bash

echoHelp() {
  echo "autodiff.sh <autodiff_example_name>"
  exit
}

FAUSTARCH=$(faust -archdir)
AUTODIFFDIR=$FAUSTARCH/autodiff
AUTODIFF_EXAMPLES=$FAUSTARCH/examples/autodiff

if [ "$#" -eq 0 ]; then
  dirs=($(ls -d $AUTODIFF_EXAMPLES/*/ | xargs -n 1 basename | cut -f1 -d'/'))
  echo 'Please provide the name of an automatic differentiation example to process.'
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

OUTPUTDIR=~/tmp/faust-autodiff
mkdir -p $OUTPUTDIR
rm ${OUTPUTDIR:?}/*

# Copy the plot script to the output directory
cp $AUTODIFFDIR/plot.py $OUTPUTDIR

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

c++ -std=c++14 $AUTODIFFDIR/autodiff.cpp /usr/local/lib/libfaust.a \
  -o $OUTPUTDIR/my_autodiff $FLAGS

cd $OUTPUTDIR || exit

# Run the compiled executable.
if ! ./my_autodiff \
  --input $AUTODIFF_EXAMPLES/ramp.dsp \
  --gt $AUTODIFF_EXAMPLES/$example/gt.dsp \
  --diff $AUTODIFF_EXAMPLES/$example/diff.dsp \
  --lossfunction l2 \
  --learningrate 0.1; then
  exit
fi

# Plot the results
# NB. matplotlib (and numpy) must be installed globally, e.g. `apt install python3-matplotlib`
python3 plot.py
