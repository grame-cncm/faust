declare name 		"mixer";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2006";

//-------------------------------------------------
// Simple 8x2 mixer
//-------------------------------------------------

vol 		= component("volume.dsp");
pan 		= component("panpot.dsp");
vumeter 	= component("vumeter.dsp").vmeter;
mute		= *(1 - checkbox("mute"));       

voice(v) 	= vgroup("voice %v",  mute : hgroup("", vol : vumeter) : pan);
stereo		= hgroup("stereo out", vol, vol);

process		= hgroup("mixer", par(i, 8, voice(i)) :> stereo);


