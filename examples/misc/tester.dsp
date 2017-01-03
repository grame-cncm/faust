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

import("stdfaust.lib");

// TODO: this should be rewritten with the pink noise function of noises.lib
pink	= f : (+ ~ g) with {
	f(x) = 0.04957526213389*x - 0.06305581334498*x' + 0.01483220320740*x'';
	g(x) = 1.80116083982126*x - 0.80257737639225*x';
};

// User interface
//----------------
vol 			= hslider("[2] volume [unit:dB]", -96, -96, 0, 1): ba.db2linear : si.smoo;
freq 			= hslider("[1] freq [unit:Hz]", 1000, 10, 20000, 1);
dest 			= hslider("[3] destination", 0, 0, 8, 1);

testsignal		= os.osci(freq)*checkbox("sine wave")
				+ no.noise * checkbox("white noise")
				+ pink(no.noise) * ba.db2linear(20)  * checkbox("pink noise");

process 		= vgroup( "Audio Tester", 
					testsignal*vol 
					<: par(i, 8, *(dest==i)) 
				  );

