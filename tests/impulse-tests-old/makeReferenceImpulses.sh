#!/bin/bash

#####################################################################
#                                                                   #
#               Creates the reference impulse responses				#
#               in scalar, vector and sheduler mode            		#
#               (c) Grame, 2016                                     #
#                                                                   #
#####################################################################

cd codes-to-test
for f in *.dsp; do
    faust2impulse -double $f > ../expected-responses/$f.scal.ir
    faust2impulse -double -vec $f > ../expected-responses/$f.vec.ir
    faust2impulse -double -sch $f > ../expected-responses/$f.sch.ir
    filesCompare ../expected-responses/$f.scal.ir ../expected-responses/$f.vec.ir && echo "OK $f, scalar and vector IR are identical" || echo "ERROR $f, scalar and vector IR are DIFFERENT"
    filesCompare ../expected-responses/$f.scal.ir ../expected-responses/$f.sch.ir && echo "OK $f, scalar and scheduler IR are identical" || echo "ERROR $f, scalar and scheduler IR are DIFFERENT"
    rm ../expected-responses/$f.vec.ir
    rm ../expected-responses/$f.sch.ir
done
