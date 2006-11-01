
declare name "pink -- pink noise";
declare author "Albert Graef";
declare version "1.0";

import("music.lib");

// control variables

vol	= nentry("vol", 0.3, 0, 10, 0.01);	// %
pan	= nentry("pan", 0.5, 0, 1, 0.01);	// %

// pink noise filter (-3dB per octave), see musicdsp.org

pink	= f : (+ ~ g) with {
	f(x)	= 0.04957526213389*x - 0.06305581334498*x' +
		  0.01483220320740*x'';
	g(x)	= 1.80116083982126*x - 0.80257737639225*x';
};

// pink noise generator

process	= (noise:pink)*vol : panner(pan);
