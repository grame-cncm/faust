declare name "sallenKeyOnePoleLPF";
declare description "Demonstration of the Sallen-Key One Pole generic multi-ouputs Filter";
declare author "Eric Tarr, GRAME";

import("stdfaust.lib");

normFreq = hslider("freq",0.5,0,1,0.001):si.smoo;
switch = checkbox("Saw/Noise");

inputSignal = (no.noise *switch) , (os.sawtooth(100)*(1-switch)) :> _; 

process = inputSignal : ve.sallenKeyOnePole(normFreq);
