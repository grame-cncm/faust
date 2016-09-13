#!/bin/bash

#####################################################################
#                                                                   #
#               Compare with the reference impulse responses        #
#               in scalar, vector and scheduler mode                #
#               (c) Grame, 2016                                     #
#                                                                   #
#####################################################################

D=`mktemp -d 2>/dev/null || mktemp -d -t 'mytmpdir'`
BACKEND="all"

for p in $@; do
    if [ $p = "-help" ] || [ $p = "-h" ]; then
        echo "test.sh [-all] [-float] [-cpp] [-c] [-llvm] [-interp] [-ajs] "
        echo "Use '-all' to activate all control test (float compilation and 5 backend)"
        echo "Use '-float' to activate float compilation"
        echo "Use '-cpp' to check 'cpp' backend"
        echo "Use '-c' to check 'c' backend"
        echo "Use '-llvm' to check 'LLVM' backend"
        echo "Use '-interp' to check 'interpreter' backend"
        echo "Use '-ajs' to check 'asm.js' backend"
        exit
    elif [ "$p" = -cpp ]; then
        BACKEND="cpp"
    elif [ $p = "-c" ]; then
        BACKEND="c"
    elif [ $p = "-llvm" ]; then
        BACKEND="llvm"
    elif [ $p = "-interp" ]; then
        BACKEND="interp"
    elif [ $p = "-ajs" ]; then
        BACKEND="ajs"
    elif [ $p = "-float" ]; then
        BACKEND="float"
    fi
done

cd codes-to-test

if [ $BACKEND = "float" ] || [ $BACKEND = "all" ]; then

    echo "========================================="
    echo "Test compilation in default mode (float)"
    echo "========================================="

    for f in *.dsp; do
        echo "Test $f compilation in scalar float mode"
        faust2impulse $f  > $D/$f.scal.ir
    done

    for f in *.dsp; do
        echo "Test $f compilation in vector float mode"
        faust2impulse $f  -vec  > $D/$f.scal.ir
    done

    for f in *.dsp; do
        echo "Test $f compilation in scheduler float mode"
        faust2impulse $f  -sch  > $D/$f.scal.ir
    done
fi

if [ $BACKEND = "cpp" ] || [ $BACKEND = "all" ]; then

    echo "============================================================================="
    echo "Impulse response tests in various compilation modes and double : C++ backend "
    echo "============================================================================="

    for f in *.dsp; do
        faust2impulse -double $f      > $D/$f.scal.ir
        filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f scalar mode" || echo "ERROR $f scalar mode"
    done

    for f in *.dsp; do

        faust2impulse -double -vec -lv 0 $f > $D/$f.vec.ir
        filesCompare $D/$f.vec.ir ../expected-responses/$f.scal.ir && echo "OK $f vector -lv 0 mode" || echo "ERROR $f vector -lv 0 mode"
    done

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
        faust2impulse -double -vec -lv 1 -g -fun $f > $D/$f.vec.ir
        filesCompare $D/$f.vec.ir ../expected-responses/$f.scal.ir && echo "OK $f vector -lv 1 -g -fun mode" || echo "ERROR $f vector -lv 1 -g -fun mode"
    done

    for f in *.dsp; do
        faust2impulse -double -sch $f > $D/$f.sch.ir
        filesCompare $D/$f.sch.ir ../expected-responses/$f.scal.ir && echo "OK $f scheduler mode" || echo "ERROR $f scheduler mode"
    done

    for f in *.dsp; do
        faust2impulse -double -sch -vs 100 $f > $D/$f.sch.ir
        filesCompare $D/$f.sch.ir ../expected-responses/$f.scal.ir && echo "OK $f scheduler -vs 100 mode" || echo "ERROR $f scheduler -vs 100 mode"
    done

    for f in *.dsp; do
        faust2impulse -double -sch -vs 100 -fun $f > $D/$f.sch.ir
        filesCompare $D/$f.sch.ir ../expected-responses/$f.scal.ir && echo "OK $f scheduler -vs 100 -fun mode" || echo "ERROR $f scheduler -vs 100 -fun mode"
    done
fi

if [ $BACKEND = "c" ] || [ $BACKEND = "all" ]; then

    echo "==========================================================================="
    echo "Impulse response tests in various compilation modes and double : C backend "
    echo "==========================================================================="

    for f in *.dsp; do
        faust2impulse2 -double $f      > $D/$f.scal.ir
        filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f scalar mode" || echo "ERROR $f scalar mode"
    done

    for f in *.dsp; do
        faust2impulse2 -double -vec -lv 0 $f > $D/$f.vec.ir
        filesCompare $D/$f.vec.ir ../expected-responses/$f.scal.ir && echo "OK $f vector -lv 0 mode" || echo "ERROR $f vector -lv 0 mode"
    done

    for f in *.dsp; do
        faust2impulse2 -double -vec -lv 1 $f > $D/$f.vec.ir
        filesCompare $D/$f.vec.ir ../expected-responses/$f.scal.ir && echo "OK $f vector -lv 1 mode" || echo "ERROR $f vector -lv 1 mode"
    done

    for f in *.dsp; do
        faust2impulse2 -double -vec -lv 1 -vs 200 $f > $D/$f.vec.ir
        filesCompare $D/$f.vec.ir ../expected-responses/$f.scal.ir && echo "OK $f vector -lv 1 -vs 200 mode" || echo "ERROR $f vector -lv 1 -vs 200 mode"
    done

    for f in *.dsp; do
        faust2impulse2 -double -vec -lv 1 -g $f > $D/$f.vec.ir
        filesCompare $D/$f.vec.ir ../expected-responses/$f.scal.ir && echo "OK $f vector -lv 1 -g mode" || echo "ERROR $f vector -lv 1 -g mode"
    done

    for f in *.dsp; do
        faust2impulse2 -double -vec -lv 1 -g -fun $f > $D/$f.vec.ir
        filesCompare $D/$f.vec.ir ../expected-responses/$f.scal.ir && echo "OK $f vector -lv 1 -g -fun mode" || echo "ERROR $f vector -lv 1 -g -fun mode"
    done

    for f in *.dsp; do
        faust2impulse2 -double -sch $f > $D/$f.sch.ir
        filesCompare $D/$f.sch.ir ../expected-responses/$f.scal.ir && echo "OK $f scheduler mode" || echo "ERROR $f scheduler mode"
    done

    for f in *.dsp; do
        faust2impulse2 -double -sch -vs 100 $f > $D/$f.sch.ir
        filesCompare $D/$f.sch.ir ../expected-responses/$f.scal.ir && echo "OK $f scheduler -vs 100 mode" || echo "ERROR $f scheduler -vs 100 mode"
    done

    for f in *.dsp; do
        faust2impulse2 -double -sch -vs 100 -fun $f > $D/$f.sch.ir
        filesCompare $D/$f.sch.ir ../expected-responses/$f.scal.ir && echo "OK $f scheduler -vs 100 -fun mode" || echo "ERROR $f scheduler -vs 100 -fun mode"
    done
fi

if [ $BACKEND = "interp" ] || [ $BACKEND = "all" ]; then

    echo "================================================================================"
    echo "Impulse response tests in various compilation modes and double : Interp backend "
    echo "================================================================================"

    for f in *.dsp; do
        faust2impulse3 -double  $f      > $D/$f.scal.ir
        filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f scalar mode" || echo "ERROR $f scalar mode"
    done
fi

if [ $BACKEND = "llvm" ] || [ $BACKEND = "all" ]; then

    echo "=============================================================================="
    echo "Impulse response tests in various compilation modes and double : LLVM backend "
    echo "=============================================================================="

    for f in *.dsp; do
        faust2impulse4 $f -double    > $D/$f.scal.ir
        filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f scalar mode" || echo "ERROR $f scalar mode"
    done

    for f in *.dsp; do
        faust2impulse4 $f -double -vec -lv 0 > $D/$f.vec.ir
        filesCompare $D/$f.vec.ir ../expected-responses/$f.scal.ir && echo "OK $f vector -lv 0 mode" || echo "ERROR $f vector -lv 0 mode"
    done

    for f in *.dsp; do
        faust2impulse4 $f -double -vec -lv 1 > $D/$f.vec.ir
        filesCompare $D/$f.vec.ir ../expected-responses/$f.scal.ir && echo "OK $f vector -lv 1 mode" || echo "ERROR $f vector -lv 1 mode"
    done

    for f in *.dsp; do
        faust2impulse4 $f -double -vec -lv 1 -vs 200 > $D/$f.vec.ir
        filesCompare $D/$f.vec.ir ../expected-responses/$f.scal.ir && echo "OK $f vector -lv 1 -vs 200 mode" || echo "ERROR $f vector -lv 1 -vs 200 mode"
    done

    for f in *.dsp; do
        faust2impulse4 $f -double -vec -lv 1 -g > $D/$f.vec.ir
        filesCompare $D/$f.vec.ir ../expected-responses/$f.scal.ir && echo "OK $f vector -lv 1 -g mode" || echo "ERROR $f vector -lv 1 -g mode"
    done

    for f in *.dsp; do
        faust2impulse4 $f -double -vec -lv 1 -g -fun > $D/$f.vec.ir
        filesCompare $D/$f.vec.ir ../expected-responses/$f.scal.ir && echo "OK $f vector -lv 1 -g -fun mode" || echo "ERROR $f vector -lv 1 -g -fun mode"
    done
fi

if [ $BACKEND = "ajs" ] || [ $BACKEND = "all" ]; then

    echo "================================================================================"
    echo "Impulse response tests in various compilation modes and double : asm.js backend "
    echo "================================================================================"

    for f in *.dsp; do
        faust2impulse5  -double $f      > $D/$f.scal.ir
        filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f scalar mode" || echo "ERROR $f scalar mode"
    done
fi


