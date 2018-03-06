declare name 		"OneSourceToStereo";
declare version 	"1.0";
declare author 		"CICM";
declare license 	"BSD";
declare copyright 	"(c)CICM 2013";

import("hoa.lib") ;
import("filter.lib") ;
import("oscillator.lib");

r1 = hslider("Radius", 1.0, 0, 5, 0.001) : smooth(tau2pole(0.02));
a1 = hslider("Angle", 62831, -6.28318530717959, 6.28318530717959, 0.001) : smooth(tau2pole(0.02));

process(sig) = map(7, sig, r1, a1) : optimInPhase(7) : decoderStereo(7);
