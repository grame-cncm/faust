// real samp [0, 0.99999994] lsb -64
R0 = frac(1.0f/min(1.92e+05f, max(5e+01f, float(fSamplingFreq)))*max(2e+01f, min(2.4e+04f, hslider("freq [unit:Hz]/Oscillator",1e+03f,2e+01f,2.4e+04f,1.0f)))+R0');
// real samp [-1.0001324, 1.0001324] lsb -525
process = (sigRDTbl(WRTbl2p(65536, sigGen(sin(9.58738e-05f*float(-1+IIR(1; 1))))), max(0, min(int(65536.0f*R0), 65535)))*(0.001f*IIR(pow(1e+01f, 0.05f*max(-96.0f, min(0.0f, hslider("volume [unit:dB]/Oscillator",0.0f,-96.0f,0.0f,0.1f)))); 0.999f)));
