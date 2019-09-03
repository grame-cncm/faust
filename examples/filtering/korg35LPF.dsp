declare name "korg35LPF";
declare description "Demonstration of the Korg 35 LPF";
declare author "Eric Tarr";

import("stdfaust.lib");

Q = hslider("Q",1,0.5,10,0.01);
normFreq = hslider("freq",0.5,0,1,0.001):si.smoo;
switch = checkbox("Saw/Noise");

inputSignal = (no.noise *switch) , (os.sawtooth(100)*(1-switch)) :> _; 

process = inputSignal : ve.korg35LPF(normFreq,Q) <:_,_;