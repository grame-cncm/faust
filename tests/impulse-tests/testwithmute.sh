#!/bin/bash

# set PATH to address faust in place
PATH=$(PWD)/../../build/bin:$PATH
export PATH
faust --version
echo location $(which faust)

#####################################################################
#                                                                   #
#               Compare with the reference impulse responses        #
#               in scalar mode with additional mute checkbox        #
#               on each channel                                     #
#               (c) Grame, 2017                                     #
#                                                                   #
#####################################################################

D=`mktemp -d 2>/dev/null || mktemp -d -t 'mytmpdir'`

REF=reference
cd dsp

echo "==============================================================="
echo 'Impulse response in scalar mode with additional mute checkbox'
echo 'on each output. Impulse responses must be preserved.'
echo "==============================================================="

rm *-mute.dsp
for f in *.dsp; do
	DSP=$(basename $f .dsp)
    echo "process = P : par(i, outputs(P), (_,(1-checkbox(\"fakedisable %2i\")) : *) ) with { P = component(\"${f}\"); };" > $f-mute.dsp
	../faust2impulse -double $f-mute.dsp  > $D/$DSP.ir
	../filesCompare $D/$DSP.ir ../$REF/$DSP.ir && echo "OK $f scalar mode" || echo "ERROR $f-mute scalar mode"
done


