#!/bin/bash

#####################################################################
#                                                                   #
#               Install the architecture file and the script		#
#               needed to run the impulse tests.                    #
#               (c) Grame, 2016-2017                                #
#                                                                   #
#####################################################################

g++ -std=c++11 -O3 filesCompare.cpp -o filesCompare
g++ -std=c++11 -O3 impulsearch3.cpp -lfaust `llvm-config --ldflags --libs all --system-libs` -I/opt/local/include -o impulseinterp
g++ -std=c++11 -O3 impulsearch4.cpp -lfaust `llvm-config --ldflags --libs all --system-libs` -I/opt/local/include -o impulsellvm

cp faust2valgrind /usr/local/bin/

cp faust2impulse /usr/local/bin/
cp faust2impulsebis /usr/local/bin/
cp faust2impulseter /usr/local/bin/

cp faust2impulse1 /usr/local/bin/
cp faust2impulse2 /usr/local/bin/
cp faust2impulse2bis /usr/local/bin/
cp faust2impulse3 /usr/local/bin/
cp faust2impulse3bis /usr/local/bin/
cp faust2impulse4 /usr/local/bin/
cp faust2impulse4bis /usr/local/bin/
cp faust2impulse5 /usr/local/bin/
cp faust2impulse5bis /usr/local/bin/
cp faust2impulse5ter /usr/local/bin/
cp faust2impulse6 /usr/local/bin/
cp faust2impulse7 /usr/local/bin/
cp faust2impulse8 /usr/local/bin/
cp faust2impulse9 /usr/local/bin/

cp impulseinterp /usr/local/bin/
cp impulsellvm /usr/local/bin/

cp filesCompare /usr/local/bin/

cp controlTools.h /usr/local/share/faust/
cp impulsearch.cpp /usr/local/share/faust/
cp impulsearch1.cpp /usr/local/share/faust/
cp impulsearch2.cpp /usr/local/share/faust/
cp impulsearch5.rs /usr/local/share/faust/


