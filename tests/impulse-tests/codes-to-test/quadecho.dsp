declare name 		"quadecho";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2007";

//-----------------------------------------------
// 				A 1 second quadriphonic Echo
//-----------------------------------------------

import("music.lib");


process = vgroup("stereo echo", multi(echo1s, 4))
	with{
		multi(f,1) = f;
		multi(f,n) = f,multi(f,n-1);
		echo1s  = vgroup("echo  1000", +~(delay(65536,   int(hslider("millisecond", 108.7, 0,	1000, 0.10)*millisec)-1) * (hslider("feedback", 100, 0,  100, 0.1)/100.0)));
	};

