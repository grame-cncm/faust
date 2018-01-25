declare name 		"StereoAudioTester";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2014";

//-----------------------------------------------
// Stereo Audio Tester : send a test signal (sine,
// noise, pink) on a stereo channel
//-----------------------------------------------

import("music.lib");

pink	= f : (+ ~ g) with {
	f(x) = 0.04957526213389*x - 0.06305581334498*x' + 0.01483220320740*x'';
	g(x) = 1.80116083982126*x - 0.80257737639225*x';
};


// User interface
//----------------
smooth(c)	= *(1-c) : +~*(c);
transition(n) = \(old,new).(if(old<new, min(old+1.0/n,new), max(old-1.0/n,new))) ~ _;

vol  = hslider("[2] volume [unit:dB]", -31.9968, -96, 0, 1): db2linear : smooth(0.999);
freq = hslider("[1] freq [unit:Hz][scale:log]", 3043, 40, 20000, 1);
wave = hslider("[3] signal [style:menu{'white noise':0;'pink noise':1;'sine':2}]", 0, 0, 2, 1) : int;
dest = hslider("[4] channel [style:radio{'none':0;'left':1;'right':2;'both':3}]", 1, 0, 3, 1) : int;

testsignal	= noise, pink(noise), osci(freq): select3(wave);

process 	= vgroup("Stereo Audio Tester",
				testsignal*vol
				<: par(i, 2, *((dest & (i+1)) != 0 : transition(4410)))
            );

