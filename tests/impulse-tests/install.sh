#!/bin/bash

#####################################################################
#                                                                   #
#               Install the architecture file and the script		#
#               needed to run the impulse tests.                    #
#               (c) Grame, 2016                                     #
#                                                                   #
#####################################################################

g++ -O3 filesCompare.cpp -o filesCompare

cp faust2impulse /usr/local/bin/
cp impulsearch.cpp /usr/local/lib/faust/
cp filesCompare /usr/local/bin/

