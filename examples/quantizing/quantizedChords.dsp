/*
MIT License

Copyright (c) 2021 César Chaussinand

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

declare name "quantizedChords";
declare description "Generate chords using the quantizer functions";
declare author "CesarChaussinand";
declare license "MIT";


import("stdfaust.lib");
Nb = 3;

process = chords*gain<:_,_;

chords = freq <: f2quantizedChord, f2quantizedChordSmoo, f2chord :> par(i,Nb,os.osc):>_/Nb;

f2quantizedChord = _ <: par(i,Nb,(_*(i+2)/(i+1):qu.quantize(200,qu.ionian) *(check==0) ));
f2quantizedChordSmoo = _ <: par(i,Nb,(_*(i+2)/(i+1):qu.quantizeSmoothed(200,qu.ionian) *(check==1) ));
f2chord = _ <: par(i,Nb,(_*(i+2)/(i+1)) *(check==2) );

//freq = hslider("freq",200,200,400,2);
freq = os.osc(rate)*100+300;
rate = 0.15;

gain = vslider("gain", -10, -60, 0, 0.1) : ba.db2linear : si.smoo;
check = nentry("quantization[style:radio{'Normal':0;'Smoothed':1;'Off':2}]",0,0,2,1);
