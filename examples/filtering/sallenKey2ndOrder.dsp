declare name "sallenKey2ndOrderBPF";
declare description "Demonstration of the Sallen-Key Second Order generic multi-ourputs Filter";
declare author "Eric Tarr, GRAME";

import("stdfaust.lib");

Q = hslider("Q",1,0.5,10,0.01);
normFreq = hslider("freq",0.5,0,1,0.001):si.smoo;
switch = checkbox("Saw/Noise");

inputSignal = (no.noise*switch) , (os.sawtooth(100)*(1-switch)) :> _ ; 

// The LPF and HPF outputs are produced
process = inputSignal : ve.sallenKey2ndOrder(normFreq,Q);
