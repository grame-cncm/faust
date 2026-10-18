// real samp [0, 0.99999994] lsb -71
R0 = frac(1.0f/min(1.92e+05f, max(5e+01f, float(fSamplingFreq)))*max(5e+01f, min(2e+03f, hslider("freq",4.4e+02f,5e+01f,2e+03f,0.01f)))+R0');
// real samp [-1685.7318, 1685.7318] lsb -136
E0 = sigRDTbl(WRTbl2p(65536, sigGen(FIR(4.656613e-10f*IIR(float(IIR(12345; 1103515245)); 2.494956f, -2.0172658f, 0.5221894f); 0.049922034f, -0.095993534f, 0.0506127f, -0.004408786f))), max(0, min(int(65536.0f*R0), 65535)));
process = (E0, E0);  // real samp [-1685.7318, 1685.7318] lsb -136 ; real samp [-1685.7318, 1685.7318] lsb -136
