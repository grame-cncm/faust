// real block [-inf, inf]  <-- unbounded from here
E0 = tan(3.1415927f/min(1.92e+05f, max(5e+01f, float(fSamplingFreq)))*max(2e+01f, min(2e+04f, nentry("freq [unit:Hz][style:knob]/Bandfilter",1e+03f,2e+01f,2e+04f,1.0f))));
E1 = pow(E0, 2.0f);                                                                               // real block [-inf, inf]
E2 = max(0.1f, min(1e+02f, nentry("Q factor [style:knob]/Bandfilter",5e+01f,0.1f,1e+02f,0.1f)));  // real block [0.1, 100] lsb -36
// real block [-inf, inf]
E3 = E0*pow(1e+01f, -(0.05f*max(-5e+01f, min(5e+01f, vslider("gain [unit:dB]/Bandfilter",0.0f,-5e+01f,5e+01f,0.1f)))))/E2;
E4 = E1+1.0f;                                                                                     // real block [-inf, inf]
E5 = E3+E4;                                                                                       // real block [-inf, inf] invalid  <-- invalid from unbounded operands
E6 = 2.0f*((-1.0f+E1)/E5);                                                                        // real block [-inf, inf] invalid
E7 = E0/E2;                                                                                       // real block [-inf, inf]
process = (FIR(IIR(IN[0]; -E6, -((-E3+E4)/E5)); (E7+E4)/E5, E6, (-E7+E4)/E5));                    // real samp [-inf, inf] invalid
