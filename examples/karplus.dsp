declare name 		"karplus";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2006";

//-----------------------------------------------
// 				karplus-strong
//-----------------------------------------------

import("music.lib");

// Excitator
//--------

upfront(x) 	= (x-x') > 0.0;
decay(n,x)	= x - (x>0.0)/n;
release(n)	= + ~ decay(n);
trigger(n) 	= upfront : release(n) : >(0.0);

size 		= hslider("excitation [unit:f]", 128, 2, 512, 1);




// resonator
//-----------------

dur 		= hslider("duration [unit:f]", 128, 2, 512, 1);
att 		= hslider("attenuation", 0.1, 0, 1, 0.01);
average(x)	= (x+x')/2;

resonator(d, a) = (+ : delay(4096, d-1.5)) ~ (average : *(1.0-a)) ;

process = noise * hslider("level", 0.5, 0, 1, 0.01)
		: vgroup("excitator", *(button("play"): trigger(size)))
		: vgroup("resonator", resonator(dur, att));
