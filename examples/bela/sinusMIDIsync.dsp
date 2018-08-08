import("stdfaust.lib");

// square signal (1/0), changing state at each received clock
clocker   = checkbox("MIDI clock[midi:clock]");    

// ON/OFF button controlled with MIDI start/stop messages
play      = checkbox("ON/OFF [midi:start] [midi:stop]");    

phasor(f)   = f/ma.SR : (+,1.0:fmod) ~ _ ;
osc(f)      = phasor(f) * 6.28318530718 : sin;

process = osc(hslider("frequence[midi:ctrl 10]", 440, 20, 10000, 0.1)) * play;