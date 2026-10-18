// real samp [-inf, inf] invalid  <-- invalid from unbounded operands (the recursion)
R0 = IN[0]+0.01f*max(0.0f, min(1e+02f, hslider("feedback/echo 1000/echo-simple",98.4f,0.0f,1e+02f,0.1f)))*R0@(1+(-1+int(0.001f*min(1.92e+05f, max(5e+01f, float(fSamplingFreq)))*max(0.0f, min(1e+03f, hslider("millisecond/echo 1000/echo-simple",8.1f,0.0f,1e+03f,0.1f))))&65535));
process = (R0);  // real samp [-inf, inf] invalid
