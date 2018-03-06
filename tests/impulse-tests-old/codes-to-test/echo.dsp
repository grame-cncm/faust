declare name 		"echo";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2006";
//-----------------------------------------------
// 				A Simple Echo
//-----------------------------------------------

import("music.lib");

process = vgroup("echo-simple", echo1s) with {
	echo1s  = vgroup("echo  1000", +~(delay(65536,   int(hslider("millisecond", 8.1, 0,	1000, 0.10)*millisec)-1) * (hslider("feedback", 98.4, 0,  100, 0.1)/100.0)));
};
