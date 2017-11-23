#!/bin/bash

#####################################################################
#                                                                   #
#               Compare with the reference impulse responses        #
#               in scalar mode with additional mute checkbox        #
#               on each channel                                     #
#               (c) Grame, 2017                                     #
#                                                                   #
#####################################################################

D=`mktemp -d 2>/dev/null || mktemp -d -t 'mytmpdir'`

cd codes-to-test

echo "==============================================================="
echo 'Impulse response in scalar mode with additional mute checkbox'
echo 'on each output. Impulse responses must be preserved.'
echo "==============================================================="

rm *-mute.dsp
for f in *.dsp; do
    echo "process = P : par(i, outputs(P), (_,(1-checkbox(\"fakedisable %2i\")) : *) ) with { P = component(\"${f}\"); };" > $f-mute.dsp
	faust2impulse -double $f-mute.dsp  > $D/$f.scal.ir
	filesCompare $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f scalar mode" || echo "ERROR $f-mute scalar mode"
done


