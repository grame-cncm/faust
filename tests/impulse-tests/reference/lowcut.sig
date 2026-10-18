// real block [-inf, inf]  <-- unbounded from here
E0 = tan(3.1415927f/min(1.92e+05f, max(5e+01f, float(fSamplingFreq)))*max(2e+01f, min(5e+03f, hslider("freq [unit:Hz][style:knob]/low-freq shelving cut",1e+02f,2e+01f,5e+03f,1.0f))));
E1 = pow(E0, 2.0f);     // real block [-inf, inf]
// real block [0.31622764, 63095.773] lsb -73
E2 = pow(1e+01f, -(0.05f*max(-96.0f, min(1e+01f, hslider("attenuation [unit:dB][style:knob]/low-freq shelving cut",0.0f,-96.0f,1e+01f,0.1f)))));
E3 = E1*E2;             // real block [-inf, inf]
E4 = E0*sqrt(2.0f*E2);  // real block [-inf, inf]
E5 = E3+1.0f;           // real block [-inf, inf]
E6 = E4+E5;             // real block [-inf, inf] invalid  <-- invalid from unbounded operands
E7 = 1.4142135f*E0;     // real block [-inf, inf]
E8 = 1.0f+E1;           // real block [-inf, inf]
// real samp [-inf, inf] invalid
process = (FIR(IIR(IN[0]; -(2.0f*((-1.0f+E3)/E6)), -((-E4+E5)/E6)); (E7+E8)/E6, 2.0f*((-1.0f+E1)/E6), (-E7+E8)/E6));
