#!/bin/bash

#####################################################################
#                                                                   #
#               Install the architecture file and the script		#
#               needed to run the impulse tests.                    #
#               (c) Grame, 2016                                     #
#                                                                   #
#####################################################################

g++ -O3 -std=c++11 filesCompare.cpp -o filesCompare

cp faust2impulse /usr/local/bin/
cp faust2impulsebis /usr/local/bin/
cp faust2impulseter /usr/local/bin/
cp faust2valgrind /usr/local/bin/
cp impulsearch.cpp /usr/local/share/faust/
cp filesCompare /usr/local/bin/

