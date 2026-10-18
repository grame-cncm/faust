E0 = max(0.0f, min(1e+02f, hslider("feedback/echo 1000/stereo echo",90.9f,0.0f,1e+02f,0.1f)));  // real block [0, 100] lsb -36
// int block [1, 65536] lsb 0
E1 = 1+(-1+int(0.001f*min(1.92e+05f, max(5e+01f, float(fSamplingFreq)))*max(0.0f, min(1e+03f, hslider("millisecond/echo 1000/stereo echo",16.3f,0.0f,1e+03f,0.1f))))&65535);
R0 = IN[0]+0.01f*E0*R0@E1;                                                                      // real samp [-inf, inf] invalid  <-- invalid from unbounded operands (the recursion)
R1 = IN[1]+0.01f*E0*R1@E1;                                                                      // real samp [-inf, inf] invalid  <-- invalid from unbounded operands (the recursion)
process = (R0, R1);                                                                             // real samp [-inf, inf] invalid ; real samp [-inf, inf] invalid
