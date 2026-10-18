E0 = max(0.0f, min(8.0f, hslider("[3] destination/Audio Tester",0.0f,0.0f,8.0f,1.0f)));  // real block [0, 8] lsb -32
// real samp [0, 0.99999994] lsb -64
R0 = frac(1.0f/min(1.92e+05f, max(5e+01f, float(fSamplingFreq)))*max(1e+01f, min(2e+04f, hslider("[1] freq [unit:Hz]/Audio Tester",1e+03f,1e+01f,2e+04f,1.0f)))+R0');
E1 = 65536.0f*R0;                                                                        // real samp [0, 65535.996] lsb -80
E2 = WRTbl2p(65537, sigGen(sin(9.58738e-05f*float(-1+IIR(1; 1)))));                      // real konst [-1, 1] lsb -47
E3 = int(E1);                                                                            // int samp [0, 65535] lsb 0
E4 = float(IIR(12345; 1103515245));                                                      // real samp [-2147483648, 2147483648] lsb -1
// real samp [-902.2216, 902.2216] lsb -575
E5 = (mix(frac(E1), sigRDTbl(E2, max(0, min(E3, 65536))), sigRDTbl(E2, max(0, min(1+E3, 65536))))+4.656613e-10f*float(checkbox("white noise/Audio Tester")>0.0f)*E4+1e+01f*float(checkbox("pink noise/Audio Tester")>0.0f)*IIR(FIR(E4; 2.308528e-11f, -2.936265e-11f, 6.906783e-12f); 1.8011608f, -0.8025774f))*(0.001f*IIR(pow(1e+01f, 0.05f*max(-96.0f, min(0.0f, hslider("[2] volume [unit:dB]/Audio Tester",-24.9984f,-96.0f,0.0f,1.0f)))); 0.999f));
// real samp [-902.2216, 902.2216] lsb -576 ; real samp [-902.2216, 902.2216] lsb -576 ; real samp [-902.2216, 902.2216] lsb -576 ; real samp [-902.2216, 902.2216] lsb -576 ; real samp [-902.2216, 902.2216] lsb -576 ; real samp [-902.2216, 902.2216] lsb -576 ; real samp [-902.2216, 902.2216] lsb -576 ; real samp [-902.2216, 902.2216] lsb -576
process = (float(E0==0.0f)*E5, float(E0==1.0f)*E5, float(E0==2.0f)*E5, float(E0==3.0f)*E5, float(E0==4.0f)*E5, float(E0==5.0f)*E5, float(E0==6.0f)*E5, float(E0==7.0f)*E5);
