declare name 		"mixer";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2006";

//-------------------------------------------------
// Simple 8x2 mixer
//-------------------------------------------------
import("delay.lib");
import("basic.lib");
import("math.lib");

smooth(c)	= *(1-c) : +~*(c);

vol		= *(vslider("fader", 0, -60, 4, 0.1) : db2linear : smooth(0.99));
mute	= *(1 - checkbox("mute"));  
vumeter(x) 	= attach(x, envelop(x) : vbargraph("", 0, 1))
		with { envelop = abs : min(0.99) : max ~ -(1.0/SR); };
pan 	= _ <: *(sqrt(1-c)), *(sqrt(c))
		with { c = (nentry("pan",0,-8,8,1)-8)/-16 : smooth(0.99); };

voice(v) 	= vgroup("voice %v",  mute : hgroup("", vol : vumeter) : pan);
stereo		= hgroup("stereo out", vol, vol);

process		= hgroup("mixer", par(i, 8, voice(i)) :> stereo);



