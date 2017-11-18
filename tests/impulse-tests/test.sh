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
        echo "test.sh [-all] [-float] [-cpp] [-c] [-rust] [-llvm] [-interp] [-ajs] [-ajs-e] [-lf-ajs] [-wast] [-wasm] [-wavm] [-valgrind] "
        echo "Use '-all' to activate all control test (float compilation and 8 backends)"
        echo "Use '-float' to activate float compilation"
        echo "Use '-cpp' to check 'cpp' backend"
        echo "Use '-c' to check 'c' backend"
        echo "Use '-rust' to check 'Rust' backend"
        echo "Use '-llvm' to check 'LLVM' backend"
        echo "Use '-interp' to check 'interpreter' backend"
        echo "Use '-ajs' to check 'asm.js' backend"
        echo "Use '-ajs-e' to check 'asm.js' backend on expanded code"
        echo "Use '-lf-ajs' to check 'libfaust.js + asm.js' backend on expanded code"
        echo "Use '-wast' to check 'wasm' backend"
        echo "Use '-wasm' to check 'wasm' backend"
        echo "Use '-wavm' to check 'wasm' backend running in WAVM runtime"
        echo "Use '-valgrind' to activate valgrind tests"
        exit
    elif [ $p = "-cpp" ]; then
        BACKEND="cpp"
    elif [ $p = "-c" ]; then
        BACKEND="c"
    elif [ $p = "-llvm" ]; then
        BACKEND="llvm"
    elif [ $p = "-rust" ]; then
        BACKEND="rust"
    elif [ $p = "-interp" ]; then
        BACKEND="interp"
    elif [ $p = "-ajs" ]; then
        BACKEND="ajs"
    elif [ $p = "-ajs-e" ]; then
        BACKEND="ajs-e"
    elif [ $p = "-lf-ajs" ]; then
        BACKEND="lf-ajs"
    elif [ $p = "-wast" ]; then
        BACKEND="wast"
    elif [ $p = "-wasm" ]; then
        BACKEND="wasm"
    elif [ $p = "-wavm" ]; then
        BACKEND="wavm"
    elif [ $p = "-float" ]; then
        BACKEND="float"
    elif [ $p = "-valgrind" ]; then
        BACKEND="valgrind"
    fi
done

cd codes-to-test

if [ $BACKEND = "valgrind" ]; then
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
fi

if [ $BACKEND = "float" ] || [ $BACKEND = "all" ]; then

echo "==============================================================="
echo "Impulse response tests in various compilation modes and double"
echo "==============================================================="

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
        faust2impulse -double  $f > $D/$f.scal.ir
        filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f scalar mode" || echo "ERROR $f scalar mode"
    done

    for f in *.dsp; do
        faust2impulse -double -fm def $f > $D/$f.scal.ir
        filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f scalar -fm mode" || echo "ERROR $f scalar -fm mode"
    done

    for f in *.dsp; do
        faust2impulse1 -double $f > $D/$f.scal.ir
        filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f scalar -mem mode" || echo "ERROR $f scalar -mem mode"
    done

    for f in *.dsp; do
        faust2impulseter -inpl -double $f > $D/$f.scal.ir
        filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f scalar -inpl mode" || echo "ERROR $f scalar -inpl mode"
    done

    for f in *.dsp; do
        faust2impulseter -ftz 1 -double $f > $D/$f.scal.ir
        filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f scalar -ftz 1 mode" || echo "ERROR $f scalar -ftz 1 mode"
    done

    for f in *.dsp; do
        faust2impulseter -ftz 2 -double $f > $D/$f.scal.ir
        filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f scalar -ftz 2 mode" || echo "ERROR $f scalar -ftz 2 mode"
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
        faust2impulse2 -double $f > $D/$f.scal.ir
        filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f scalar mode" || echo "ERROR $f scalar mode"
    done

    for f in *.dsp; do
        faust2impulse2 -double -fm def $f > $D/$f.scal.ir
        filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f scalar -fm mode" || echo "ERROR $f scalar -fm mode"
    done

    for f in *.dsp; do
        faust2impulse2bis -inpl -double $f > $D/$f.scal.ir
        filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f scalar -inpl mode" || echo "ERROR $f scalar -inpl mode"
    done

    for f in *.dsp; do
        faust2impulse2bis -ftz 1 -double $f > $D/$f.scal.ir
        filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f scalar -ftz 1 mode" || echo "ERROR $f scalar -ftz 1 mode"
    done

    for f in *.dsp; do
        faust2impulse2bis -ftz 2 -double $f > $D/$f.scal.ir
        filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f scalar -ftz 2 scalar" || echo "ERROR $f scalar -ftz 2 mode"
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
        faust2impulse3 -double $f > $D/$f.scal.ir
        filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f scalar mode" || echo "ERROR $f scalar mode"
    done

    for f in *.dsp; do
        faust2impulse3bis -inpl -double $f > $D/$f.scal.ir
        filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f -inpl scalar mode" || echo "ERROR $f -inpl scalar mode"
    done

    for f in *.dsp; do
        faust2impulse3 -double -ftz 1 $f > $D/$f.scal.ir
        filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f scalar -ftz 1 mode" || echo "ERROR $f -ftz 1 scalar mode"
    done

fi

if [ $BACKEND = "llvm" ] || [ $BACKEND = "all" ]; then

    echo "=============================================================================="
    echo "Impulse response tests in various compilation modes and double : LLVM backend "
    echo "=============================================================================="

    for f in *.dsp; do
        faust2impulse4 $f -double > $D/$f.scal.ir
        filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f scalar mode" || echo "ERROR $f scalar mode"
    done

    for f in *.dsp; do
        faust2impulse4 $f -double -fm def -L fastmath.bc > $D/$f.scal.ir
        filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f scalar -fm mode" || echo "ERROR $f scalar -fm mode"
    done

    for f in *.dsp; do
        faust2impulse4bis $f -inpl -double > $D/$f.scal.ir
        filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f -inpl scalar mode" || echo "ERROR $f -inpl scalar mode"
    done

    for f in *.dsp; do
        faust2impulse4 $f -double -ftz 1 > $D/$f.scal.ir
        filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f scalar -ftz 1 mode" || echo "ERROR $f scalar -ftz 1 mode"
    done

    for f in *.dsp; do
        faust2impulse4 $f -double -ftz 2 > $D/$f.scal.ir
        filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f scalar -ftz 2 mode" || echo "ERROR $f scalar -ftz 2 mode"
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
        faust2impulse5 -double $f > $D/$f.scal.ir && RES=1 || RES=0
        if [ $RES = "1" ]; then
            filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f scalar mode" || echo "ERROR $f scalar mode"
        else
            echo "ERROR $f scalar mode in node.js"
        fi
    done

    for f in *.dsp; do
        faust2impulse5 -inpl -double $f > $D/$f.scal.ir && RES=1 || RES=0
        if [ $RES = "1" ]; then
            filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f -inpl scalar mode" || echo "ERROR $f -inpl scalar mode"
        else
            echo "ERROR $f scalar mode in node.js"
        fi
    done

fi

if [ $BACKEND = "ajs-e" ] || [ $BACKEND = "all" ]; then

    echo "================================================================================================="
    echo "Impulse response tests in various compilation modes and double : asm.js backend on expanded code "
    echo "================================================================================================="

    for f in *.dsp; do
        faust2impulse5bis -double $f > $D/$f.scal.ir && RES=1 || RES=0
        if [ $RES = "1" ]; then
            filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f scalar mode" || echo "ERROR $f scalar mode"
        else
            echo "ERROR $f scalar mode in node.js"
        fi
    done

    for f in *.dsp; do
        faust2impulse5bis -inpl -double $f > $D/$f.scal.ir && RES=1 || RES=0
        if [ $RES = "1" ]; then
            filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f -inpl scalar mode" || echo "ERROR $f -inpl scalar mode"
        else
            echo "ERROR $f scalar mode in node.js"
        fi
    done

fi

if [ $BACKEND = "lf-ajs" ] || [ $BACKEND = "all" ]; then

    echo "==============================================================================================================="
    echo "Impulse response tests in various compilation modes and double : libfaust.js + asm.js backend on expanded code "
    echo "==============================================================================================================="

    for f in *.dsp; do
        faust2impulse5ter -double $f > $D/$f.scal.ir && RES=1 || RES=0
        if [ $RES = "1" ]; then
            filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f scalar mode" || echo "ERROR $f scalar mode"
        else
            echo "ERROR $f scalar mode in node.js"
        fi
    done

fi

if [ $BACKEND = "wasm" ] || [ $BACKEND = "all" ]; then

    echo "================================================================================"
    echo "Impulse response tests in various compilation modes and double : wasm backend   "
    echo "================================================================================"

    for f in *.dsp; do
        faust2impulse6 -double $f > $D/$f.scal.ir && RES=1 || RES=0
        if [ $RES = "1" ]; then
            filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f scalar mode" || echo "ERROR $f scalar mode"
        else
            echo "ERROR $f scalar mode in node.js"
        fi
    done

    for f in *.dsp; do
        faust2impulse6 -ftz 1 -double $f > $D/$f.scal.ir && RES=1 || RES=0
        if [ $RES = "1" ]; then
            filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f scalar -ftz 1 mode" || echo "ERROR $f scalar -ftz 1 mode"
        else
            echo "ERROR $f scalar mode in node.js"
        fi
    done

# Deactivated for now (bug in nodejs ?)
#    for f in *.dsp; do
#        faust2impulse6 -ftz 2 -double $f > $D/$f.scal.ir && RES=1 || RES=0
#        if [ $RES = "1" ]; then
#            filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f scalar -ftz 2 mode" || echo "ERROR $f scalar -ftz 2 mode"
#        else
#            echo "ERROR $f scalar mode in node.js"
#        fi
#    done

fi

if [ $BACKEND = "wast" ] || [ $BACKEND = "all" ]; then

    echo "================================================================================"
    echo "Impulse response tests in various compilation modes and double : wast backend   "
    echo "================================================================================"

    for f in *.dsp; do
        faust2impulse7 -double $f > $D/$f.scal.ir && RES=1 || RES=0
        if [ $RES = "1" ]; then
            filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f scalar mode" || echo "ERROR $f scalar mode"
        else
            echo "ERROR $f scalar mode in node.js"
        fi
    done

    for f in *.dsp; do
        faust2impulse7 -ftz 1 -double $f > $D/$f.scal.ir && RES=1 || RES=0
        if [ $RES = "1" ]; then
            filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f scalar -ftz 1 mode" || echo "ERROR $f scalar -ftz 1 mode"
        else
            echo "ERROR $f scalar mode in node.js"
        fi
    done

# Deactivated for now (bug in nodejs ?)
#    for f in *.dsp; do
#        faust2impulse7 -ftz 2 -double $f > $D/$f.scal.ir && RES=1 || RES=0
#        if [ $RES = "1" ]; then
#            filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f scalar -ftz 2 mode" || echo "ERROR $f scalar -ftz 2 mode"
#        else
#            echo "ERROR $f scalar mode in node.js"
#        fi
#    done

fi

if [ $BACKEND = "rust" ] || [ $BACKEND = "all" ]; then

    echo "================================================================================"
    echo "Impulse response tests in various compilation modes and double : Rust backend   "
    echo "================================================================================"

    for f in *.dsp; do
        faust2impulse8 -double $f > $D/$f.scal.ir && RES=1 || RES=0
        if [ $RES = "1" ]; then
            filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f scalar mode" || echo "ERROR $f scalar mode"
        else
            echo "ERROR $f scalar mode in node.js"
        fi
    done

fi

if [ $BACKEND = "wavm" ] || [ $BACKEND = "all" ]; then

    echo "================================================================================================"
    echo "Impulse response tests in various compilation modes and double : wasm backend with WAVM runtime "
    echo "================================================================================================"

    for f in *.dsp; do
        faust2impulse9 -double $f > $D/$f.scal.ir && RES=1 || RES=0
        if [ $RES = "1" ]; then
        filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f scalar mode" || echo "ERROR $f scalar mode"
        else
        echo "ERROR $f scalar mode in WAVM"
        fi
    done

fi


