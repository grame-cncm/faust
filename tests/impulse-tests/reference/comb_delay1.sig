E0 = WRTbl2p(65536, sigGen(sin(9.58738e-05f*float(-1+IIR(1; 1)))));  // real konst [-1, 1] lsb -47
E1 = min(1.92e+05f, max(5e+01f, float(fSamplingFreq)));              // real konst [50, 192000] lsb -27
R0 = frac(4.4e+02f/E1+R0');                                          // real samp [0, 0.99999994] lsb -27
R1 = frac(1e+03f/E1+R1');                                            // real samp [0, 0.99999994] lsb -27
// real samp [-1, 1] lsb -47
process = ((sigRDTbl(E0, max(0, min(int(65536.0f*R0), 65535)))@max(0, min(int(max(0.0f, min(1e+01f, 5.0f*(1.0f+sigRDTbl(E0, max(0, min(int(65536.0f*R1), 65535))))))), 10)))@100);
