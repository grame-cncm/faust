// real block [0.56234115, 1.7782798] lsb -74
E0  = pow(1e+01f, 0.025f*max(-1e+01f, min(1e+01f, hslider("Gain [unit:dB]",0.0f,-1e+01f,1e+01f,0.1f))));
// real block [0.003272492, 1256.6372] lsb -62
E1  = 6.2831855f/min(1.92e+05f, max(5e+01f, float(fSamplingFreq)))*max(0.0f, max(1e+02f, min(1e+04f, hslider("Freq",1e+03f,1e+02f,1e+04f,1.0f))));
E2  = cos(E1);                                                                                      // real block [-1, 1] lsb -62
E3  = -E2;                                                                                          // real block [-1, 1] lsb -62
E4  = mix(E3, 1.0f, E0);                                                                            // real block [0.22172022, 1.7782798] lsb -136
E5  = sqrt(E0)*sin(E1)/max(0.001f, max(0.01f, min(1e+02f, hslider("Q",1.0f,0.01f,1e+02f,0.01f))));  // real block [-133.35217, 133.35217] lsb -136
E6  = E0+E5;                                                                                        // real block [-132.78983, 135.13045] lsb -136
E7  = E4+E6;                                                                                        // real block [-132.5681, 136.90872] lsb -136
E8  = (E0+mix(E3, -1.0f, E0))/E7;                                                                   // real block [-inf, inf] invalid  <-- invalid from here
E9  = E0-E5;                                                                                        // real block [-132.78983, 135.13045] lsb -136
E10 = (E4+E9)/E7;                                                                                   // real block [-inf, inf] invalid  <-- invalid from here
E11 = mix(E2, 1.0f, E0);                                                                            // real block [0.22172022, 1.7782798] lsb -136
E12 = E0*(E11+E6)/E7;                                                                               // real block [-inf, inf] invalid  <-- invalid from here
E13 = E0*(E0+mix(E2, -1.0f, E0))/E7;                                                                // real block [-inf, inf] invalid  <-- invalid from here
E14 = E0*(E11+E9)/E7;                                                                               // real block [-inf, inf] invalid  <-- invalid from here
process = (FIR(IIR(IN[0]; -(2.0f*E8), -E10); E12, -(2.0f*E13), E14));                               // real samp [-inf, inf] invalid
