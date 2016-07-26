#!/bin/bash

#####################################################################
#                                                                   #
#               Compare with the reference impulse responses		#
#               in scalar and vetor mode            				#
#               (c) Grame, 2016                                     #
#                                                                   #
#####################################################################

D=`mktemp -d 2>/dev/null || mktemp -d -t 'mytmpdir'`

cd codes-to-test
for f in *.dsp; do
	faust2impulse $f      > $D/$f.scal.ir
	diff $D/$f.scal.ir ../expected-responses/$f.scal.ir && echo "OK $f scalar mode" || echo "ERROR $f scalar mode"

	faust2impulse -vec $f > $D/$f.vec.ir
	diff $D/$f.vec.ir ../expected-responses/$f.vec.ir && echo "OK $f vector mode" || echo "ERROR $f vector mode"
done
