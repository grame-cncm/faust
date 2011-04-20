declare name 		"tester";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2006";

//-----------------------------------------------
// Tester : tests louspeakers
// Send a test signal( sine, noise, pink) to one 
// of 8 loudspeakers
//-----------------------------------------------

import("music.lib");

pink	= f : (+ ~ g) with {
	f(x) = 0.04957526213389*x - 0.06305581334498*x' + 0.01483220320740*x'';
	g(x) = 1.80116083982126*x - 0.80257737639225*x';
};


// User interface
//----------------
smooth(c)		= *(1-c) : +~*(c);
vol 			= hslider("(2)volume", -96, -96, 0, 0.1): db2linear : smooth(0.999);
freq 			= hslider("(1) freq", 1000, 0, 24000, 0.1);
dest 			= hslider("(3) destination", 0, 0, 8, 1);

testsignal		= osci(freq)*checkbox("sine wave")
				+ noise * checkbox("white noise")
				+ pink(noise) * db2linear(20)  * checkbox("pink noise");

process 		= vgroup( "Audio Tester", 
					testsignal*vol 
					<: par(i, 8, *(dest==i)) 
				  );

