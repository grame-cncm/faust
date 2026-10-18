E0 = -(1.0f/min(1.92e+05f, max(5e+01f, float(fSamplingFreq))));  // real konst [-0.020000001, -5.2083333e-06] lsb -32
R0 = max(E0+R0', abs(IN[0]));                                    // real samp [0, inf]
R1 = max(E0+R1', abs(IN[1]));                                    // real samp [0, inf]
// real samp [-inf, inf] ; real samp [-inf, inf]
process = (attach(IN[0], hbargraph("[2][unit:dB]",-7e+01f,5.0f,2e+01f*log10(max(0.00031622776f, R0)))), attach(IN[1], hbargraph("[2][unit:dB]",-7e+01f,5.0f,2e+01f*log10(max(0.00031622776f, R1)))));
