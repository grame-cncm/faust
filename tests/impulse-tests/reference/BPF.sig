// real block [0.003272492, 1256.6372] lsb -62
E0 = 6.2831855f/min(1.92e+05f, max(5e+01f, float(fSamplingFreq)))*max(0.0f, max(1e+02f, min(1e+04f, hslider("Freq",1e+03f,1e+02f,1e+04f,1.0f))));
E1 = sin(E0);                                                                     // real block [-1, 1] lsb -62
E2 = max(0.001f, max(0.01f, min(1e+02f, hslider("Q",1.0f,0.01f,1e+02f,0.01f))));  // real block [0.01, 100] lsb -42
E3 = 0.5f*(E1/E2);                                                                // real block [-50.000004, 50.000004] lsb -95
E4 = 1.0f+E3;                                                                     // real block [-49.000004, 51.000004] lsb -95
E5 = cos(E0)/E4;                                                                  // real block [-inf, inf] invalid  <-- invalid from here
E6 = (1.0f-E3)/E4;                                                                // real block [-inf, inf] invalid  <-- invalid from here
E7 = E1/(E2*E4);                                                                  // real block [-inf, inf] invalid  <-- invalid from here
E8 = 0.5f*E7;                                                                     // real block [-inf, inf] invalid
process = (FIR(IIR(IN[0]; 2.0f*E5, -E6); E8, 0.0f, -E8));                         // real samp [-inf, inf] invalid
