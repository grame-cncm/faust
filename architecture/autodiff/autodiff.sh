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

###########################
# Processing Arguments
###########################

while [ $1 ]; do
  example=$1

  shift
done

OUTPUTDIR=~/tmp/faust-autodiff

mkdir -p $OUTPUTDIR

cp $FAUSTARCH/autodiff/autodiff.h $OUTPUTDIR/autodiff.h

faust -diff -a $FAUSTARCH/autodiff/autodiff.cpp \
  -o $OUTPUTDIR/my_autodiff.cpp \
  $AUTODIFF_EXAMPLES/noop.dsp

c++ -std=c++14 $OUTPUTDIR/my_autodiff.cpp /usr/local/lib/libfaust.a \
  $(llvm-config --ldflags --libs all --system-libs) \
  -o $OUTPUTDIR/my_autodiff

cd $OUTPUTDIR || exit

./my_autodiff \
  --input $AUTODIFF_EXAMPLES/noise.dsp \
  --gt $AUTODIFF_EXAMPLES/$example/gt.dsp \
  --diff $AUTODIFF_EXAMPLES/$example/diff.dsp
