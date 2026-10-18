E0 = min(1.92e+05f, max(5e+01f, float(fSamplingFreq)));                                            // real konst [50, 192000] lsb -27
// real samp [0, 0.99999994] lsb -32
R0 = frac(1e+03f/E0/max(1.0f, min(1e+03f, hslider("grainsize [unit:msec]",1e+02f,1.0f,1e+03f,1.0f)))+R0');
E1 = (R0>0.0001f)*(R0'<=0.0001f);                                                                  // int samp [0, 1] lsb 0
E2 = 1.0f+4.656613e-10f*float(IIR(12345; 1103515245));                                             // real samp [0, 2] lsb -64
// real samp [0, 1920000.2] lsb -166
R1 = select2(E1, R1', 0.0005f*E0*max(1e+01f, min(1e+04f, hslider("delaymax",1e+03f,1e+01f,1e+04f,1.0f)))*E2);
E3 = 9.58738e-05f*float(-1+IIR(1; 1));                                                             // real samp [-205887.42, 205887.42] lsb -47
R2 = frac(R2');                                                                                    // real samp [0, 0.99999994] lsb -1 invalid  <-- invalid from here (the recursion)
E4 = max(0, min(int(65536.0f*R2), 65535));                                                         // int samp [0, 65535] lsb 0 invalid
E5 = 3.1415927f*R0;                                                                                // real samp [0, 3.1415927] lsb -63
R3 = select2(E1, R3', 0.5f*E2>max(0.0f, min(1.0f, hslider("rarefaction",0.2f,0.0f,1.0f,0.01f))));  // int samp [0, 1] lsb 0
// real samp [-inf, inf] invalid
process = (mix(frac(R1), IN[0]@min(524289, max(0, int(R1))), IN[0]@min(524289, max(0, 1+int(R1))))*(sigRDTbl(WRTbl2p(65536, sigGen(sin(E3))), E4)*cos(E5)+sigRDTbl(WRTbl2p(65536, sigGen(cos(E3))), E4)*sin(E5))*float(R3));
