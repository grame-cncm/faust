
declare name "white -- white noise";
declare author "Albert Graef";
declare version "1.0";

import("music.lib");

// control variables

vol	= nentry("vol", 0.3, 0, 10, 0.01);	// %
pan	= nentry("pan", 0.5, 0, 1, 0.01);	// %

// white (unfiltered) noise generator

process	= noise*vol : panner(pan);
