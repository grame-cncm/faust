#!/bin/bash

OUTPUTDIR=~/tmp/faust-autodiff

FAUSTARCH=$(faust -archdir)

mkdir -p $OUTPUTDIR

cp $FAUSTARCH/autodiff/autodiff.h $OUTPUTDIR/autodiff.h

faust -diff -a $FAUSTARCH/autodiff/autodiff.cpp \
  -o $OUTPUTDIR/my_autodiff.cpp \
  $FAUSTARCH/examples/autodiff/empty.dsp


c++ -std=c++14 $OUTPUTDIR/my_autodiff.cpp /usr/local/lib/libfaust.a \
  $(llvm-config --ldflags --libs all --system-libs) \
  -o $OUTPUTDIR/my_autodiff

cd $OUTPUTDIR || exit

./my_autodiff \
  --input $FAUSTARCH/examples/autodiff/noise.dsp \
  --gt $FAUSTARCH/examples/autodiff/fixed_gain.dsp \
  --diff $FAUSTARCH/examples/autodiff/gain.dsp
