#!/bin/bash

#####################################################################
#                                                                   #
#               Creates the reference impulse responses				#
#               in scalar and vetor mode            				#
#               (c) Grame, 2016                                     #
#                                                                   #
#####################################################################


cd codes-to-test
for f in *.dsp; do
	faust2impulse $f      > ../expected-responses/$f.scal.ir
	faust2impulse -vec $f > ../expected-responses/$f.vec.ir
    diff ../expected-responses/$f.scal.ir ../expected-responses/$f.vec.ir && echo "OK $f , scalar and vector IR are identical" || echo "ERROR $f, scalar and vector IR are DIFFERENT"
done
