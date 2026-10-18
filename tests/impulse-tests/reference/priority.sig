R0 = (1'+R0')%65536;                                                          // int samp [0, 65535] lsb 0
E0 = min(1.92e+05f, max(5e+01f, float(fSamplingFreq)));                       // real konst [50, 192000] lsb -27
R1 = (1'+R1')%int(0.5f*E0);                                                   // int samp [0, 95999] lsb 0
E1 = R1<=R1';                                                                 // int samp [0, 1] lsb 0
R2 = (1'+R2')%int(E0);                                                        // int samp [0, 191999] lsb 0
E2 = R2<=R2';                                                                 // int samp [0, 1] lsb 0
R3 = frac(R3'+1.0f/E0*float(200*(1+IIR(E1>E1'; 1)%2+2*(IIR(E2>E2'; 1)%2))));  // real samp [0, 1] lsb -33
// real samp [-1, 1] lsb -47
process = (sigRDTbl(WRTbl2p(65536, sigGen(sin(9.58738e-05f*float(R0)))), max(0, min(int(65536.0f*R3), 65535))));
