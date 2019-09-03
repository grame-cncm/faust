declare name "sallenKeyOnePoleLPF";
declare description "Demonstration of the Sallen-Key One Pole Low-Pass Filter";
declare author "Eric Tarr";

import("stdfaust.lib");

normFreq = hslider("freq",0.5,0,1,0.001):si.smoo;
switch = checkbox("Saw/Noise");

inputSignal = (no.noise*switch) , (os.sawtooth(100)*(1-switch)) :> _; 

process = inputSignal : ve.sallenKeyOnePoleLPF(normFreq) <:_,_;
