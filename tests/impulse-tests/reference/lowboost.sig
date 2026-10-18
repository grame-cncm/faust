// real block [-inf, inf]  <-- unbounded from here
E0 = tan(3.1415927f/min(1.92e+05f, max(5e+01f, float(fSamplingFreq)))*max(2e+01f, min(2e+04f, hslider("[1]freq [unit:Hz][style:knob]/low-freq shelving boost",1e+03f,2e+01f,2e+04f,0.1f))));
E1 = pow(E0, 2.0f);     // real block [-inf, inf]
E2 = 1.4142135f*E0;     // real block [-inf, inf]
E3 = E1+1.0f;           // real block [-inf, inf]
E4 = E2+E3;             // real block [-inf, inf] invalid  <-- invalid from unbounded operands
// real block [0.09999996, 10.000005] lsb -73
E5 = pow(1e+01f, 0.05f*max(-2e+01f, min(2e+01f, hslider("[2]gain [unit:dB][style:knob]/low-freq shelving boost",0.0f,-2e+01f,2e+01f,0.1f))));
E6 = sqrt(2.0f*E5)*E0;  // real block [-inf, inf]
E7 = E5*E1;             // real block [-inf, inf]
E8 = 1.0f+E7;           // real block [-inf, inf]
// real samp [-inf, inf] invalid
process = (FIR(IIR(IN[0]; -(2.0f*((-1.0f+E1)/E4)), -((-E2+E3)/E4)); (E6+E8)/E4, 2.0f*((-1.0f+E7)/E4), (-E6+E8)/E4));
