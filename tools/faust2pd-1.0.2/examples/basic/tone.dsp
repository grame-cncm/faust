
declare name "tone -- sine oscillator with adjustable frequency";
declare author "Albert Graef";
declare version "1.0";

import("music.lib");

// control variables

vol	= nentry("vol", 0.3, 0, 10, 0.01);	// %
pan	= nentry("pan", 0.5, 0, 1, 0.01);	// %
freq	= nentry("pitch", 440, 20, 20000, 0.01);

// simple sine tone generator

process	= osci(freq)*vol : panner(pan);
