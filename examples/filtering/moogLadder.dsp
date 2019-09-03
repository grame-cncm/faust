declare name "moogLadder";
declare description "Demonstration of moogLadder";
declare author "Eric Tarr";

import("stdfaust.lib");

Q = hslider("Q",1,0.7072,25,0.01);
normFreq = hslider("freq",0.1,0,1,0.001):si.smoo;
switch = checkbox("Saw/Noise");
inputSignal = (no.noise *switch) , (os.sawtooth(100)*(1-switch)) :> _; 

process = inputSignal : ve.moogLadder(normFreq,Q) <:_,_;