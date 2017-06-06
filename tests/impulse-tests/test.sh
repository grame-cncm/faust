#!/bin/bash

#####################################################################
#                                                                   #
#               Compare with the reference impulse responses        #
#               in scalar, vector and scheduler mode                #
#               (c) Grame, 2016                                     #
#                                                                   #
#####################################################################

D=`mktemp -d 2>/dev/null || mktemp -d -t 'mytmpdir'`

cd codes-to-test

echo "==============================================================="
echo "Impulse response tests in various compilation modes and double"
echo "==============================================================="

for f in *.dsp; do
    faust2impulse -double -inpl $f > $D/$f.scal.ir
    filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f scalar -inpl mode" || echo "ERROR $f scalar -inpl mode"
done

for f in *.dsp; do
    faust2impulse -double $f > $D/$f.scal.ir
    filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f scalar mode" || echo "ERROR $f scalar mode"
done

#for f in *.dsp; do
#    faust2impulsebis -double $f > $D/$f.scal.ir
#    filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f scalar expanded mode" || echo "ERROR $f scalar mode"
#done

for f in *.dsp; do
	faust2impulse -double -vec -lv 0 $f > $D/$f.vec.ir
	filesCompare $D/$f.vec.ir ../expected-responses/$f.scal.ir && echo "OK $f vector -lv 0 mode" || echo "ERROR $f vector -lv 0 mode"
done

#for f in *.dsp; do
#    faust2impulsebis -double -vec -lv 0 $f > $D/$f.vec.ir
#    filesCompare $D/$f.vec.ir ../expected-responses/$f.scal.ir && echo "OK $f vector -lv 0 expanded mode" || echo "ERROR $f vector -lv 0 mode"
#done

for f in *.dsp; do
    faust2impulse -double -vec -lv 1 $f > $D/$f.vec.ir
    filesCompare $D/$f.vec.ir ../expected-responses/$f.scal.ir && echo "OK $f vector -lv 1 mode" || echo "ERROR $f vector -lv 1 mode"
done

for f in *.dsp; do
    faust2impulse -double -vec -lv 1 -vs 200 $f > $D/$f.vec.ir
    filesCompare $D/$f.vec.ir ../expected-responses/$f.scal.ir && echo "OK $f vector -lv 1 -vs 200 mode" || echo "ERROR $f vector -lv 1 -vs 200 mode"
done

for f in *.dsp; do
    faust2impulse -double -vec -lv 1 -g $f > $D/$f.vec.ir
    filesCompare $D/$f.vec.ir ../expected-responses/$f.scal.ir && echo "OK $f vector -lv 1 -g mode" || echo "ERROR $f vector -lv 1 -g mode"
done

for f in *.dsp; do
    faust2impulse -double -sch $f > $D/$f.sch.ir
    filesCompare $D/$f.sch.ir ../expected-responses/$f.scal.ir && echo "OK $f scheduler mode" || echo "ERROR $f scheduler mode"
done

for f in *.dsp; do
    faust2impulse -double -sch -vs 100 $f > $D/$f.sch.ir
    filesCompare $D/$f.sch.ir ../expected-responses/$f.scal.ir && echo "OK $f scheduler -vs 100 mode" || echo "ERROR $f scheduler -vs 100 mode"
done


echo "========================================="
echo "Test compilation in default mode (float)"
echo "========================================="

for f in *.dsp; do
    faust2impulse $f > $D/$f.scal.ir
	filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir 0.001 && echo "OK $f scalar mode" || echo "ERROR $f scalar mode"
done

for f in *.dsp; do
    faust2impulse $f -vec > $D/$f.vec.ir
	filesCompare $D/$f.vec.ir ../expected-responses/$f.scal.ir 0.001 && echo "OK $f vector -lv 0 mode" || echo "ERROR $f vector -lv 0 mode"
done

echo "==============================================================="
echo "Valgrind test in scalar mode "
echo "==============================================================="

for f in *.dsp; do
    echo $f
    faust2valgrind $f > /dev/null
done

grep "uninitialised" *.txt

echo "==============================================================="
echo "Valgrind test in vector mode "
echo "==============================================================="

for f in *.dsp; do
    echo $f
    faust2valgrind -vec -lv 1 $f > /dev/null
done

grep "uninitialised" *.txt

