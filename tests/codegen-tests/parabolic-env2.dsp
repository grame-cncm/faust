//-----------------------------------------------
//
// Parabolic Grain Envelop : from Ross Bencina
//
//-----------------------------------------------

// integrate values of x starting : 0, x(0), x(0)+x(1),...
integrate = +~_ : mem;

durationSamples = 10;
grainAmplitude = 2.8;

rdur 		= 1.0/durationSamples;
rdur2 		= rdur*rdur;
curve 		= -8.0 * grainAmplitude * rdur2;

slope 		= 4* grainAmplitude * (rdur - rdur2) + integrate(curve);
amplitude 	= integrate(slope);

process 	= integrate(1), slope, max(0.0,amplitude);