declare name 		"stereoecho";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2007";

//-----------------------------------------------
// 				A 1 second Stereo Echo
//-----------------------------------------------

import("music.lib");

process = vgroup("stereo echo", (echo1s, echo1s))
	with {
		echo1s  = vgroup("echo  1000", +~(delay(65536,   int(hslider("millisecond", 16.3, 0,	1000, 0.10)*millisec)-1) * (hslider("feedback", 90.9, 0,  100, 0.1)/100.0)));
	};
