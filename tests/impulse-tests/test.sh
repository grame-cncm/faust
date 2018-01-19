#!/bin/bash

# set PATH to address faust in place
PATH=$(PWD)/../../build/bin:..:$PATH
export PATH
faust --version
echo location $(which faust)

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

REF=reference	# the reference files location
cd dsp			# the dsp files location

###############################################################
# functions
function check {
	TOOL=$1
	shift
	OPTIONS=$*
	echo ---- check using $TOOL ----
    for f in *.dsp; do
		DSP=$(basename $f .dsp)
        $TOOL $OPTIONS  $f > $D/$f.scal.ir
        filesCompare $D/$f.scal.ir ../$REF/$DSP.ir && echo "OK $f with $OPTIONS" || echo "ERROR $f with $OPTIONS"
    done
}

function check_with_node {
	TOOL=$1
	shift
	OPTIONS=$*
	echo ---- check using $TOOL ----
    for f in *.dsp; do
		DSP=$(basename $f .dsp)
        $TOOL $OPTIONS  $f > $D/$f.scal.ir || (echo "ERROR $f with $OPTIONS"; exit)
        cp $D/$f.scal.ir $f.scal.ir
	    filesCompare $D/$f.scal.ir ../$REF/$DSP.ir && echo "OK $f with $OPTIONS" || echo "ERROR $f with $OPTIONS"
   done
}


###############################################################
# processing starts here
###############################################################
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
	check faust2impulse -double  $f > $D/$f.scal.ir
	check faust2impulse -double -fm def $f > $D/$f.scal.ir
	check faust2impulse1 -double $f > $D/$f.scal.ir
	check faust2impulseter -inpl -double $f > $D/$f.scal.ir
	check faust2impulseter -ftz 1 -double $f > $D/$f.scal.ir
	check faust2impulseter -ftz 2 -double $f > $D/$f.scal.ir
    #   faust2impulsebis -double $f > $D/$f.scal.ir
	check faust2impulse -double -vec -lv 0 $f > $D/$f.vec.ir
    #   faust2impulsebis -double -vec -lv 0 $f > $D/$f.vec.ir
	check faust2impulse -double -vec -lv 1 $f > $D/$f.vec.ir
	check faust2impulse -double -vec -lv 1 -vs 200 $f > $D/$f.vec.ir
	check faust2impulse -double -vec -lv 1 -g $f > $D/$f.vec.ir
	check faust2impulse -double -vec -lv 1 -g -fun $f > $D/$f.vec.ir
	check faust2impulse -double -sch $f > $D/$f.sch.ir
	check faust2impulse -double -sch -vs 100 $f > $D/$f.sch.ir
	check faust2impulse -double -sch -vs 100 -fun $f > $D/$f.sch.ir

fi

if [ $BACKEND = "c" ] || [ $BACKEND = "all" ]; then

    echo "==========================================================================="
    echo "Impulse response tests in various compilation modes and double : C backend "
    echo "==========================================================================="
	check faust2impulse2 -double
	check faust2impulse2 -double -fm def
	check faust2impulse2bis -inpl -double
	check faust2impulse2bis -ftz 1 -double
	check faust2impulse2bis -ftz 2 -double
	check faust2impulse2 -double -vec -lv 0
	check faust2impulse2 -double -vec -lv 1
	check faust2impulse2 -double -vec -lv 1 -vs 200
	check faust2impulse2 -double -vec -lv 1 -g
	check faust2impulse2 -double -vec -lv 1 -g -fun
	check faust2impulse2 -double -sch
	check faust2impulse2 -double -sch -vs 100
	check faust2impulse2 -double -sch -vs 100 -fun
fi

if [ $BACKEND = "interp" ] || [ $BACKEND = "all" ]; then

    echo "================================================================================"
    echo "Impulse response tests in various compilation modes and double : Interp backend "
    echo "================================================================================"
	check faust2impulse3 -double
	check faust2impulse3bis -inpl -double
	check faust2impulse3 -double -ftz 1
fi

if [ $BACKEND = "llvm" ] || [ $BACKEND = "all" ]; then

    echo "=============================================================================="
    echo "Impulse response tests in various compilation modes and double : LLVM backend "
    echo "=============================================================================="
	check faust2impulse4 -double 
	check faust2impulse4 -double -fm def -L fastmath.bc 
	check faust2impulse4bis -inpl -double
	check faust2impulse4 -double -ftz 1 
	check faust2impulse4 -double -ftz 2
	check faust2impulse4 -double -vec -lv 0
	check faust2impulse4 -double -vec -lv 1
	check faust2impulse4 -double -vec -lv 1 -vs 200
	check faust2impulse4 -double -vec -lv 1 -g 
	check faust2impulse4 -double -vec -lv 1 -g -fun 
fi

if [ $BACKEND = "ajs" ] || [ $BACKEND = "all" ]; then

    echo "================================================================================"
    echo "Impulse response tests in various compilation modes and double : asm.js backend "
    echo "================================================================================"
	check_with_node faust2impulse5 -double
	check_with_node faust2impulse5 -inpl -double
fi

if [ $BACKEND = "ajs-e" ] || [ $BACKEND = "all" ]; then

    echo "================================================================================================="
    echo "Impulse response tests in various compilation modes and double : asm.js backend on expanded code "
    echo "================================================================================================="
	check_with_node faust2impulse5bis -double
	check_with_node faust2impulse5bis -inpl -double
fi

if [ $BACKEND = "lf-ajs" ] || [ $BACKEND = "all" ]; then

    echo "==============================================================================================================="
    echo "Impulse response tests in various compilation modes and double : libfaust.js + asm.js backend on expanded code "
    echo "==============================================================================================================="
	check_with_node faust2impulse5ter -double
fi

if [ $BACKEND = "wasm" ] || [ $BACKEND = "all" ]; then

    echo "================================================================================"
    echo "Impulse response tests in various compilation modes and double : wasm backend   "
    echo "================================================================================"
	check_with_node faust2impulse6 -double
	check_with_node faust2impulse6 -double -ftz 1

# Deactivated for now (bug in nodejs ?)
#    for f in *.dsp; do
#        faust2impulse6 -ftz 2 -double $f > $D/$f.scal.ir && RES=1 || RES=0
#        if [ $RES = "1" ]; then
#            filesCompare $D/$f.scal.ir ../$REF/$f.scal.ir && echo "OK $f scalar -ftz 2 mode" || echo "ERROR $f scalar -ftz 2 mode"
#        else
#            echo "ERROR $f scalar mode in node.js"
#        fi
#    done

fi

if [ $BACKEND = "wast" ] || [ $BACKEND = "all" ]; then

    echo "================================================================================"
    echo "Impulse response tests in various compilation modes and double : wast backend   "
    echo "================================================================================"

	check_with_node faust2impulse7 -double
	check_with_node faust2impulse7 -double -ftz 1

#     for f in *.dsp; do
#         faust2impulse7 -double $f > $D/$f.scal.ir && RES=1 || RES=0
#         if [ $RES = "1" ]; then
#             filesCompare $D/$f.scal.ir ../$REF/$f.scal.ir && echo "OK $f scalar mode" || echo "ERROR $f scalar mode"
#         else
#             echo "ERROR $f scalar mode in node.js"
#         fi
#     done
# 
#     for f in *.dsp; do
#         faust2impulse7 -ftz 1 -double $f > $D/$f.scal.ir && RES=1 || RES=0
#         if [ $RES = "1" ]; then
#             filesCompare $D/$f.scal.ir ../$REF/$f.scal.ir && echo "OK $f scalar -ftz 1 mode" || echo "ERROR $f scalar -ftz 1 mode"
#         else
#             echo "ERROR $f scalar mode in node.js"
#         fi
#     done

# Deactivated for now (bug in nodejs ?)
#    for f in *.dsp; do
#        faust2impulse7 -ftz 2 -double $f > $D/$f.scal.ir && RES=1 || RES=0
#        if [ $RES = "1" ]; then
#            filesCompare $D/$f.scal.ir ../$REF/$f.scal.ir && echo "OK $f scalar -ftz 2 mode" || echo "ERROR $f scalar -ftz 2 mode"
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
            filesCompare $D/$f.scal.ir ../$REF/$f.scal.ir && echo "OK $f scalar mode" || echo "ERROR $f scalar mode"
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
        filesCompare $D/$f.scal.ir ../$REF/$f.scal.ir && echo "OK $f scalar mode" || echo "ERROR $f scalar mode"
        else
        echo "ERROR $f scalar mode in WAVM"
        fi
    done

fi


