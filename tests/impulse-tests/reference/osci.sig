// real samp [0, 0.99999994] lsb -64
R0 = frac(1.0f/min(1.92e+05f, max(5e+01f, float(fSamplingFreq)))*max(2e+01f, min(2.4e+04f, hslider("freq [unit:Hz]/Oscillator",564.0f,2e+01f,2.4e+04f,1.0f)))+R0');
E0 = 65536.0f*R0;                                                    // real samp [0, 65535.996] lsb -80
E1 = WRTbl2p(65537, sigGen(sin(9.58738e-05f*float(-1+IIR(1; 1)))));  // real konst [-1, 1] lsb -47
E2 = int(E0);                                                        // int samp [0, 65535] lsb 0
// real samp [-1.0001324, 1.0001324] lsb -558
process = (mix(frac(E0), sigRDTbl(E1, max(0, min(E2, 65536))), sigRDTbl(E1, max(0, min(1+E2, 65536))))*(0.001f*IIR(pow(1e+01f, 0.05f*max(-96.0f, min(0.0f, hslider("volume [unit:dB]/Oscillator",0.0f,-96.0f,0.0f,0.1f)))); 0.999f)));
