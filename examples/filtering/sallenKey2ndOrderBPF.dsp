declare name "sallenKey2ndOrderBPF";
declare description "Demonstration of the Sallen-Key Second Order Band-Pass Filter";
declare author "Eric Tarr";

import("stdfaust.lib");

Q = hslider("Q",1,0.5,10,0.01);
normFreq = hslider("freq",0.5,0,1,0.001):si.smoo;
switch = checkbox("Saw/Noise");

inputSignal = (no.noise*switch) , (os.sawtooth(100)*(1-switch)) :> _; 

process = inputSignal : ve.sallenKey2ndOrderBPF(normFreq,Q) <:_,_;
