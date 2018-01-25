declare name 		"volume";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2006";

//-----------------------------------------------
// 			Volume control in dB
//-----------------------------------------------

import("music.lib");

smooth(c)	= *(1-c) : +~*(c);
gain		= vslider("[1]", 0, -70, +4, 0.1) : db2linear : smooth(0.999);

process		= *(gain);
