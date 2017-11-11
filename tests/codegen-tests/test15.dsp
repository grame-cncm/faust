durationSamples = 100;
grainAmplitude = 2.8;

rdur = 1.0/durationSamples;
rdur2 = rdur*rdur;
curve = -8.0 * grainAmplitude * rdur2;

slope = 4* grainAmplitude * (rdur - rdur2) + (curve : +~_:mem);
amplitude = slope : + ~_:mem;

process = slope, amplitude;