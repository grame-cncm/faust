declare name 		"osc";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2009";

//-----------------------------------------------
// 			Sinusoidal Oscillator
//-----------------------------------------------

import("music.lib");

smooth(c)		= *(1-c) : +~*(c);
vol 			= hslider("volume [unit:dB]", 0, -96, 0, 0.1) : db2linear : smooth(0.999) ;
freq 			= hslider("freq [unit:Hz]", 1000, 20, 24000, 1);

process 		= vgroup("Oscillator", osc(freq) * vol);

