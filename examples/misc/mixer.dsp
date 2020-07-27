declare name 		"mixer";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2006-2020";

import("stdfaust.lib");

//-------------------------------------------------
// Simple 8x2 mixer
//-------------------------------------------------

vol = component("../dynamic/volume.dsp");
pan = component("../spat/panpot.dsp");
mute = *(1 - checkbox("mute")); 
      
vumeter(i, x) = attach(x, envelop(x) : vbargraph("chan %i[2][unit:dB]", -70, +5))
with {
	envelop = abs : max ~ -(1.0/ma.SR) : max(ba.db2linear(-70)) : ba.linear2db;
};

voice(v) = vgroup("Ch %v",  mute : hgroup("[2]", vol : vumeter(v)) : pan);
stereo = hgroup("stereo out", (vol, vol : vgroup("L", vumeter(0)), vgroup("R", vumeter(1))));

process = hgroup("mixer", par(i, 8, voice(i)) :> stereo);


