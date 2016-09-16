declare name 		"mixer";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2006";

//-------------------------------------------------
// Simple 8x2 mixer
//-------------------------------------------------

vol 		= component("../dynamic/volume.dsp");
pan 		= component("../spat/panpot.dsp");
vumeter 	= component("../analysis/vumeter.dsp").vmeter;
mute		= *(1 - checkbox("mute"));       

voice(v) 	= vgroup("Ch %v",  mute : hgroup("[2]", vol : vumeter) : pan);
stereo		= hgroup("stereo out", (vol, vol : vgroup("L", vumeter), vgroup("R", vumeter)));

process		= hgroup("mixer", par(i, 8, voice(i)) :> stereo );


