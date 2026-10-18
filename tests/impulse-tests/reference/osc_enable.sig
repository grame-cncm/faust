R0 = frac(4e+02f/min(1.92e+05f, max(5e+01f, float(fSamplingFreq)))+R0');  // real samp [0, 0.99999994] lsb -27
// real samp [-1, 1] lsb -47
E0 = sigRDTbl(WRTbl2p(65536, sigGen(sin(9.58738e-05f*float(-1+IIR(1; 1))))), max(0, min(int(65536.0f*R0), 65535)));
E1 = waveform{...}!=0.0f;                                                 // int samp [0, 1] lsb 0
// real samp [-1, 1] lsb -33 ; real samp [-1, 1] lsb -47 ; real samp [-1, 1] lsb -80 ; real samp [-1, 1] lsb -33 ; real samp [0, 1.0000002] lsb -33
process = (waveform{...}, control(E0, E1), control(waveform{...}*E0, E1), control(waveform{...}, E1), control(pow(waveform{...}, 2.0f), E1));
