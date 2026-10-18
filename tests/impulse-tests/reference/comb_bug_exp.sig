E0  = min(1.92e+05f, max(5e+01f, float(fSamplingFreq)));                                             // real konst [50, 192000] lsb -27
E1  = IRM(max(2e+02f, min(8e+02f, hslider("freq",2e+02f,2e+02f,8e+02f,1.0f))); exp(-(1e+03f/E0)));   // real samp [1.038742, 800.0397] lsb -32
E2  = E0/E1;                                                                                         // real samp [0.0624969, 184838.98] lsb -32
E3  = frac(E2);                                                                                      // real samp [0, 0.99999994] lsb -32
E4  = -1.0f+select2(E3<=0.06f, select2(E3>=0.95f, E2, 0.9993265f*E0/E1), 1.0006735f*E0/E1);          // real samp [-0.9375452, 184962.48] lsb -60
E5  = int(E4);                                                                                       // int samp [0, 184962] lsb 0
E6  = max(1.0f, E0*max(0.001f, min(1.0f, hslider("env_a",0.95f,0.001f,1.0f,0.01f))));                // real block [1, 192000] lsb -69
E7  = float(button("gate")>0.0f);                                                                    // real block [0, 1] lsb -1
E8  = E7';                                                                                           // real samp [0, 1] lsb -1
R0  = select2(E7<=E8, 1, R0'+(R0'>0));                                                               // int samp [-2147483648, 2147483647] lsb 0
E9  = E7==0.0f;                                                                                      // int block [0, 1] lsb 0
R1  = E7+R1'*float(E8>=E7);                                                                          // real samp [0, 16777216] lsb -12
// real samp [-4.6216207e+21, 4.6216207e+21] lsb -784
E10 = max(-0.999f, min(0.999f, hslider("comb_res",0.999f,-0.999f,0.999f,0.01f)))*R2'+3.6666243e-12f*max(0.0f, min(127.0f, hslider("vitesse",127.0f,0.0f,127.0f,1.0f)))*(float(IIR(12345; 1103515245))*max(0.0f, min(1.0f/E6*float(R0), 1.0f+1.0f/max(1.0f, E0*max(0.001f, min(1.0f, hslider("env_r",0.95f,0.001f,1.0f,0.01f))))*(E6-float(R0))))*max(0.0f, -(1.0f/max(1.0f, 0.01f*E0)*float(IIR(E9; E9)))+min(1.0f/max(1.0f, 0.1f*E0)*R1, 1.0f)));
R2  = mix(frac(E4), E10@min(1025, max(0, E5)), E10@min(1025, max(0, 1+E5)));                         // real samp [-4.6216305e+21, 4.6216305e+21] lsb -745
E11 = 0.3f*(E10*(0.001f*IIR(max(0.0f, min(1.0f, hslider("gain",0.8f,0.0f,1.0f,0.01f))); 0.999f)))';  // real samp [-1.3866696e+21, 1.3866696e+21] lsb -1262
process = (E11, E11);                                                                                // real samp [-1.3866696e+21, 1.3866696e+21] lsb -1262 ; real samp [-1.3866696e+21, 1.3866696e+21] lsb -1262
