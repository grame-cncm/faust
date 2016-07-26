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
    faust2impulse -sch $f > ../expected-responses/$f.sch.ir
    diff ../expected-responses/$f.scal.ir ../expected-responses/$f.vec.ir && echo "OK $f, scalar and vector IR are identical" || echo "ERROR $f, scalar and vector IR are DIFFERENT"
    diff ../expected-responses/$f.scal.ir ../expected-responses/$f.sch.ir && echo "OK $f, scalar and scheduler IR are identical" || echo "ERROR $f, scalar and scheduler IR are DIFFERENT"
    rm ../expected-responses/$f.vec.ir
    rm ../expected-responses/$f.sch.ir
done
