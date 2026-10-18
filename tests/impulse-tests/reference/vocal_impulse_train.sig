E0  = min(1.92e+05f, max(5e+01f, float(fSamplingFreq)));  // real konst [50, 192000] lsb -27
R0  = frac(1.1e+02f/E0+R0');                              // real samp [0, 0.99999994] lsb -27
E1  = float(FIR(R0; 1.0f, -1.0f)<0.0f);                   // real samp [0, 1] lsb -1
E2  = tan(2042.0353f/E0);                                 // real konst [-inf, inf]  <-- unbounded from here
E3  = 1.0f/pow(E2, 2.0f);                                 // real konst [-inf, inf]
E4  = 0.025f/E2;                                          // real konst [-inf, inf]
E5  = 1.0f+E3;                                            // real konst [-inf, inf]
E6  = E4+E5;                                              // real konst [-inf, inf] invalid  <-- invalid from unbounded operands
E7  = 1.0f/(E2*E6);                                       // real konst [-inf, inf] invalid
E8  = tan(3392.9202f/E0);                                 // real konst [-inf, inf]  <-- unbounded from here
E9  = 1.0f/pow(E8, 2.0f);                                 // real konst [-inf, inf]
E10 = 0.02f/E8;                                           // real konst [-inf, inf]
E11 = 1.0f+E9;                                            // real konst [-inf, inf]
E12 = E10+E11;                                            // real konst [-inf, inf] invalid  <-- invalid from unbounded operands
E13 = 0.8f/(E8*E12);                                      // real konst [-inf, inf] invalid
// real samp [-inf, inf] invalid
process = (FIR(IIR(E1; -(2.0f*((1.0f-E3)/E6)), -((-E4+E5)/E6)); E7, 0.0f, -E7)+FIR(IIR(E1; -(2.0f*((1.0f-E9)/E12)), -((-E10+E11)/E12)); E13, 0.0f, -E13));
