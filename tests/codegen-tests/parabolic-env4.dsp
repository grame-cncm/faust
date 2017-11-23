//-----------------------------------------------
//
// Parabolic Grain Envelop : from Ross Bencina
//
//-----------------------------------------------

// integrate values of x starting : 0, x(0), x(0)+x(1),...
//integrate = +~_ : mem;
rintegrate(zero) = (+:*(zero))~_ : mem;
integrate = rintegrate(1);

durationSamples = 10;
grainAmplitude = 2.8;

rdur 		= 1.0/durationSamples;
rdur2 		= rdur*rdur;
curve 		= -8.0 * grainAmplitude * rdur2;

slope(zero) 		= 4* grainAmplitude * (rdur - rdur2) + rintegrate(zero,curve);
amplitude(zero) 	= rintegrate(zero, slope(zero));

trig = (integrate(1) == 15) | (integrate(1) == 16);
bidule = (| : amplitude : max(0)) ~ >(0);
//process 	= integrate(1), slope(trig), max(0.0,bidule(trig));
process 	= integrate(1), trig, bidule(trig);
