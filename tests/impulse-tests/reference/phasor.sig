// real samp [0, 0.99999994] lsb -36
R0 = frac(select2(prefix(1, waveform{...}>0.0f), 7e+02f/min(1.92e+05f, max(5e+01f, float(fSamplingFreq)))+R0', waveform{...}));
process = (R0, waveform{...}, waveform{...});  // real samp [0, 0.99999994] lsb -36 ; real samp [0, 1] lsb -32 ; real samp [0.1, 0.9] lsb -36
