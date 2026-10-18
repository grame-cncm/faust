// real block [0.003272492, 1256.6372] lsb -62
E0  = 6.2831855f/min(1.92e+05f, max(5e+01f, float(fSamplingFreq)))*max(0.0f, max(1e+02f, min(1e+04f, hslider("Freq",1e+03f,1e+02f,1e+04f,1.0f))));
E1  = sin(E0);                                                                                    // real block [-1, 1] lsb -62
E2  = max(0.001f, max(0.01f, min(1e+02f, hslider("Q",1.0f,0.01f,1e+02f,0.01f))));                 // real block [0.01, 100] lsb -42
E3  = sqrt(max(1e-05f, max(0.0f, min(8.0f, hslider("Gain [unit: lin]",1.0f,0.0f,8.0f,0.01f)))));  // real block [0.0031622774, 2.8284273] lsb -49
E4  = 0.5f*(E1/(E2*E3));                                                                          // real block [-15811.392, 15811.392] lsb -124
E5  = 1.0f+E4;                                                                                    // real block [-15810.392, 15812.392] lsb -124
E6  = cos(E0)/E5;                                                                                 // real block [-inf, inf] invalid  <-- invalid from here
E7  = 2.0f*E6;                                                                                    // real block [-inf, inf] invalid
E8  = (1.0f-E4)/E5;                                                                               // real block [-inf, inf] invalid  <-- invalid from here
E9  = 0.5f*(E3*E1/E2);                                                                            // real block [-141.42137, 141.42137] lsb -144
E10 = (1.0f+E9)/E5;                                                                               // real block [-inf, inf] invalid  <-- invalid from here
E11 = (1.0f-E9)/E5;                                                                               // real block [-inf, inf] invalid  <-- invalid from here
process = (FIR(IIR(IN[0]; E7, -E8); E10, -E7, E11));                                              // real samp [-inf, inf] invalid
