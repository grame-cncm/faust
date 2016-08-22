#!/bin/bash

#####################################################################
#                                                                   #
#               Install the architecture file and the script		#
#               needed to run the impulse tests.                    #
#               (c) Grame, 2016                                     #
#                                                                   #
#####################################################################

g++ -std=c++11 -O3 filesCompare.cpp -o filesCompare
g++ -std=c++11 -O3 impulsearch3.cpp -lfaust `llvm-config --ldflags --libs all --system-libs` -lcrypto -o impulseinterp
g++ -std=c++11 -O3 impulsearch4.cpp -lfaust `llvm-config --ldflags --libs all --system-libs` -lcrypto -o impulsellvm

cp faust2impulse /usr/local/bin/
cp faust2impulse2 /usr/local/bin/
cp faust2impulse3 /usr/local/bin/
cp faust2impulse4 /usr/local/bin/
cp faust2impulse5 /usr/local/bin/
cp impulseinterp /usr/local/bin/
cp impulsellvm /usr/local/bin/
cp filesCompare /usr/local/bin/

cp impulsearch.cpp /usr/local/lib/faust/
cp impulsearch2.cpp /usr/local/lib/faust/


