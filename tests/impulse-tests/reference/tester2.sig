// int block [0, 2] lsb 0
E0 = int(max(0.0f, min(2.0f, hslider("[3] signal [style:menu{'white noise':0;'pink noise':1;'sine':2}]/Stereo Audio Tester",0.0f,0.0f,2.0f,1.0f))));
// real samp [0, 0.99999994] lsb -64
R0 = frac(1.0f/min(1.92e+05f, max(5e+01f, float(fSamplingFreq)))*max(4e+01f, min(2e+04f, hslider("[1] freq [unit:Hz][scale:log]/Stereo Audio Tester",3043.0f,4e+01f,2e+04f,1.0f)))+R0');
E1 = 65536.0f*R0;                                                                 // real samp [0, 65535.996] lsb -80
E2 = WRTbl2p(65537, sigGen(sin(9.58738e-05f*float(-1+IIR(1; 1)))));               // real konst [-1, 1] lsb -47
E3 = int(E1);                                                                     // int samp [0, 65535] lsb 0
E4 = float(IIR(12345; 1103515245));                                               // real samp [-2147483648, 2147483648] lsb -1
// real samp [-90.01021, 90.01021] lsb -80
E5 = select2(E0==0, select2(E0==1, mix(frac(E1), sigRDTbl(E2, max(0, min(E3, 65536))), sigRDTbl(E2, max(0, min(1+E3, 65536)))), IIR(FIR(E4; 2.308528e-11f, -2.936265e-11f, 6.906783e-12f); 1.8011608f, -0.8025774f)), 4.656613e-10f*E4);
// real samp [1.584892e-08, 1.0001324] lsb -474
E6 = 0.001f*IIR(pow(1e+01f, 0.05f*max(-96.0f, min(0.0f, hslider("[2] volume [unit:dB]/Stereo Audio Tester",-31.9968f,-96.0f,0.0f,1.0f)))); 0.999f);
// int block [0, 3] lsb 0
E7 = int(max(0.0f, min(3.0f, hslider("[4] channel [style:radio{'none':0;'left':1;'right':2;'both':3}]/Stereo Audio Tester",1.0f,0.0f,3.0f,1.0f))));
E8 = float((E7&1)!=0);                                                            // real block [0, 1] lsb -1
R1 = select2(R1'<E8, max(-0.00022675737f+R1', E8), min(0.00022675737f+R1', E8));  // real samp [0, 1] lsb -45
E9 = float((E7&2)!=0);                                                            // real block [0, 1] lsb -1
R2 = select2(R2'<E9, max(-0.00022675737f+R2', E9), min(0.00022675737f+R2', E9));  // real samp [0, 1] lsb -45
process = (E5*E6*R1, E5*E6*R2);                                                   // real samp [-90.02213, 90.02213] lsb -599 ; real samp [-90.02213, 90.02213] lsb -599
