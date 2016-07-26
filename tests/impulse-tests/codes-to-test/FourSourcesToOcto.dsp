declare name 		"FourSourcesToOcto";
declare version 	"1.0";
declare author 	"CICM";
declare license 	"BSD";
declare copyright 	"(c)CICM 2013";

import("hoa.lib") ;
import("filter.lib") ;
import("oscillator.lib");

r1 = hslider("Radius1", 1.0, 0, 5, 0.001) : smooth(tau2pole(0.02));
a1 = hslider("Angle1", 62831, -6.28318530717959, 6.28318530717959, 0.001) : smooth(tau2pole(0.02));
r2 = hslider("Radius2", 1.0, 0, 5, 0.001) : smooth(tau2pole(0.02));
a2 = hslider("Angle2", 62831, -6.28318530717959, 6.28318530717959, 0.001) : smooth(tau2pole(0.02));
r3 = hslider("Radius3", 1.0, 0, 5, 0.001) : smooth(tau2pole(0.02));
a3 = hslider("Angle3", 62831, -6.28318530717959, 6.28318530717959, 0.001) : smooth(tau2pole(0.02));
r4 = hslider("Radius4", 1.0, 0, 5, 0.001) : smooth(tau2pole(0.02));
a4 = hslider("Angle4", 62831, -6.28318530717959, 6.28318530717959, 0.001) : smooth(tau2pole(0.02));

process(sig1, sig2, sig3, sig4) = map(3, sig1, r1, a1), map(3, sig2, r2, a2), map(3, sig3, r3, a3), map(3, sig4, r4, a4) :> optimInPhase(3) : decoder(3, 8);


