//-------------------------------------------------
// Simple 8x2 mixer
//-------------------------------------------------


process			= hgroup("mixer", par(i, 8, voice(i)) :> *(master),*(master));
voice(v) 		= vgroup("voice %v", muter : hgroup("", amplifier : vumeter) : panner);

muter			= *(1 - checkbox("mute"));
amplifier		= *(vslider("gain", 0, 0, 1, 0.1));
vumeter(x)		= attach(x, envelop(x) : vbargraph("meter", 0, 1));
panner(x)		= x*g, x*(1-g) with { g=(nentry("pan",0,-8,8,1)-8)/-16; };

master			= vslider("Master", 0, 0, 1.2, 0.1);

envelop			= fabs : fmax ~ -(1.0/SR);

