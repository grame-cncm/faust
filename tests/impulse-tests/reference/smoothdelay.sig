E0   = min(1.92e+05f, max(5e+01f, float(fSamplingFreq)));                                // real konst [50, 192000] lsb -27
// real block [0, 960000.1] lsb -105
E1   = 0.001f*E0*max(0.0f, min(5e+03f, hslider("delay[unit:ms][style:knob]",114.5f,0.0f,5e+03f,0.1f)));
// real block [5.2083327e-05, 20] lsb -36
E2   = 1e+03f/E0/max(1.0f, min(1e+02f, hslider("interpolation[unit:ms][style:knob]",68.0329f,1.0f,1e+02f,0.1f)));
// real samp [-20, 20] lsb -36
R0.0 = select2(R0.0'!=0.0f, select2(R0.1'==0.0f&E1!=R0.2', select2(R0.1'==1.0f&E1!=R0.3', 0.0f, -E2), E2), select2(R0.1'>0.0f&R0.1'<1.0f, 0.0f, R0.0'));
// real samp [0, 1] lsb -36
R0.1 = max(0.0f, min(1.0f, R0.1'+select2(R0.0'!=0.0f, select2(R0.1'==0.0f&E1!=R0.2', select2(R0.1'==1.0f&E1!=R0.3', 0.0f, -E2), E2), select2(R0.1'>0.0f&R0.1'<1.0f, 0.0f, R0.0'))));
R0.2 = select2(R0.1'>=1.0f&R0.3'!=E1, R0.2', E1);                                        // real samp [0, 960000.1] lsb -105
R0.3 = select2(R0.1'<=0.0f&R0.2'!=E1, R0.3', E1);                                        // real samp [0, 960000.1] lsb -105
E3   = max(0.0f, min(1e+02f, hslider("feedback[style:knob]",87.11f,0.0f,1e+02f,0.1f)));  // real block [0, 100] lsb -36
E4   = IN[0]+0.01f*E3*R1';                                                               // real samp [-inf, inf] invalid
E5   = int(R0.2)&524287;                                                                 // int samp [0, 524287] lsb 0
E6   = int(R0.3)&524287;                                                                 // int samp [0, 524287] lsb 0
R1   = mix(R0.1, E4@E5, E4@E6);                                                          // real samp [-inf, inf] invalid  <-- invalid from unbounded operands (the recursion)
E7   = IN[1]+0.01f*E3*R2';                                                               // real samp [-inf, inf] invalid
R2   = mix(R0.1, E7@E5, E7@E6);                                                          // real samp [-inf, inf] invalid  <-- invalid from unbounded operands (the recursion)
process = (R1, R2);                                                                      // real samp [-inf, inf] invalid ; real samp [-inf, inf] invalid
