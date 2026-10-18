E0  = 3.1415927f/min(1.92e+05f, max(5e+01f, float(fSamplingFreq)));  // real konst [1.636246e-05, 0.06283186] lsb -31
// real block [-inf, inf]  <-- unbounded from here
E1  = tan(E0*max(2e+01f, min(2e+04f, nentry("freq [unit:Hz][style:knob]/peak 0/Multi Band Filter",1e+03f,2e+01f,2e+04f,1.0f))));
E2  = pow(E1, 2.0f);                                                 // real block [-inf, inf]
// real block [0.1, 100] lsb -36
E3  = max(0.1f, min(1e+02f, nentry("Q factor [style:knob]/peak 0/Multi Band Filter",5e+01f,0.1f,1e+02f,0.1f)));
// real block [-inf, inf]
E4  = E1*pow(1e+01f, -(0.05f*max(-5e+01f, min(5e+01f, vslider("gain [unit:dB]/peak 0/Multi Band Filter",0.0f,-5e+01f,5e+01f,0.1f)))))/E3;
E5  = E2+1.0f;                                                       // real block [-inf, inf]
E6  = E4+E5;                                                         // real block [-inf, inf] invalid  <-- invalid from unbounded operands
E7  = 2.0f*((-1.0f+E2)/E6);                                          // real block [-inf, inf] invalid
E8  = E1/E3;                                                         // real block [-inf, inf]
// real block [-inf, inf]  <-- unbounded from here
E9  = tan(E0*max(2e+01f, min(2e+04f, nentry("freq [unit:Hz][style:knob]/peak 1/Multi Band Filter",2e+03f,2e+01f,2e+04f,1.0f))));
E10 = pow(E9, 2.0f);                                                 // real block [-inf, inf]
// real block [0.1, 100] lsb -36
E11 = max(0.1f, min(1e+02f, nentry("Q factor [style:knob]/peak 1/Multi Band Filter",5e+01f,0.1f,1e+02f,0.1f)));
// real block [-inf, inf]
E12 = E9*pow(1e+01f, -(0.05f*max(-5e+01f, min(5e+01f, vslider("gain [unit:dB]/peak 1/Multi Band Filter",0.0f,-5e+01f,5e+01f,0.1f)))))/E11;
E13 = 1.0f+E10;                                                      // real block [-inf, inf]
E14 = E12+E13;                                                       // real block [-inf, inf] invalid  <-- invalid from unbounded operands
E15 = 2.0f*((-1.0f+E10)/E14);                                        // real block [-inf, inf] invalid
E16 = E9/E11;                                                        // real block [-inf, inf]
// real block [-inf, inf]  <-- unbounded from here
E17 = tan(E0*max(2e+01f, min(2e+04f, nentry("freq [unit:Hz][style:knob]/peak 2/Multi Band Filter",3e+03f,2e+01f,2e+04f,1.0f))));
E18 = pow(E17, 2.0f);                                                // real block [-inf, inf]
// real block [0.1, 100] lsb -36
E19 = max(0.1f, min(1e+02f, nentry("Q factor [style:knob]/peak 2/Multi Band Filter",5e+01f,0.1f,1e+02f,0.1f)));
// real block [-inf, inf]
E20 = E17*pow(1e+01f, -(0.05f*max(-5e+01f, min(5e+01f, vslider("gain [unit:dB]/peak 2/Multi Band Filter",0.0f,-5e+01f,5e+01f,0.1f)))))/E19;
E21 = 1.0f+E18;                                                      // real block [-inf, inf]
E22 = E20+E21;                                                       // real block [-inf, inf] invalid  <-- invalid from unbounded operands
E23 = 2.0f*((-1.0f+E18)/E22);                                        // real block [-inf, inf] invalid
E24 = E17/E19;                                                       // real block [-inf, inf]
// real block [-inf, inf]  <-- unbounded from here
E25 = tan(E0*max(2e+01f, min(2e+04f, nentry("freq [unit:Hz][style:knob]/peak 3/Multi Band Filter",4e+03f,2e+01f,2e+04f,1.0f))));
E26 = pow(E25, 2.0f);                                                // real block [-inf, inf]
// real block [0.1, 100] lsb -36
E27 = max(0.1f, min(1e+02f, nentry("Q factor [style:knob]/peak 3/Multi Band Filter",5e+01f,0.1f,1e+02f,0.1f)));
// real block [-inf, inf]
E28 = E25*pow(1e+01f, -(0.05f*max(-5e+01f, min(5e+01f, vslider("gain [unit:dB]/peak 3/Multi Band Filter",0.0f,-5e+01f,5e+01f,0.1f)))))/E27;
E29 = 1.0f+E26;                                                      // real block [-inf, inf]
E30 = E28+E29;                                                       // real block [-inf, inf] invalid  <-- invalid from unbounded operands
E31 = 2.0f*((-1.0f+E26)/E30);                                        // real block [-inf, inf] invalid
E32 = E25/E27;                                                       // real block [-inf, inf]
// real block [-inf, inf]  <-- unbounded from here
E33 = tan(E0*max(2e+01f, min(2e+04f, nentry("freq [unit:Hz][style:knob]/peak 4/Multi Band Filter",5e+03f,2e+01f,2e+04f,1.0f))));
E34 = pow(E33, 2.0f);                                                // real block [-inf, inf]
// real block [0.1, 100] lsb -36
E35 = max(0.1f, min(1e+02f, nentry("Q factor [style:knob]/peak 4/Multi Band Filter",5e+01f,0.1f,1e+02f,0.1f)));
// real block [-inf, inf]
E36 = E33*pow(1e+01f, -(0.05f*max(-5e+01f, min(5e+01f, vslider("gain [unit:dB]/peak 4/Multi Band Filter",0.0f,-5e+01f,5e+01f,0.1f)))))/E35;
E37 = 1.0f+E34;                                                      // real block [-inf, inf]
E38 = E36+E37;                                                       // real block [-inf, inf] invalid  <-- invalid from unbounded operands
E39 = 2.0f*((-1.0f+E34)/E38);                                        // real block [-inf, inf] invalid
E40 = E33/E35;                                                       // real block [-inf, inf]
// real block [-inf, inf]  <-- unbounded from here
E41 = tan(E0*max(2e+01f, min(2e+04f, nentry("freq [unit:Hz][style:knob]/peak 5/Multi Band Filter",6e+03f,2e+01f,2e+04f,1.0f))));
E42 = pow(E41, 2.0f);                                                // real block [-inf, inf]
// real block [0.1, 100] lsb -36
E43 = max(0.1f, min(1e+02f, nentry("Q factor [style:knob]/peak 5/Multi Band Filter",5e+01f,0.1f,1e+02f,0.1f)));
// real block [-inf, inf]
E44 = E41*pow(1e+01f, -(0.05f*max(-5e+01f, min(5e+01f, vslider("gain [unit:dB]/peak 5/Multi Band Filter",0.0f,-5e+01f,5e+01f,0.1f)))))/E43;
E45 = 1.0f+E42;                                                      // real block [-inf, inf]
E46 = E44+E45;                                                       // real block [-inf, inf] invalid  <-- invalid from unbounded operands
E47 = 2.0f*((-1.0f+E42)/E46);                                        // real block [-inf, inf] invalid
E48 = E41/E43;                                                       // real block [-inf, inf]
// real block [-inf, inf]  <-- unbounded from here
E49 = tan(E0*max(2e+01f, min(2e+04f, nentry("freq [unit:Hz][style:knob]/peak 6/Multi Band Filter",7e+03f,2e+01f,2e+04f,1.0f))));
E50 = pow(E49, 2.0f);                                                // real block [-inf, inf]
// real block [0.1, 100] lsb -36
E51 = max(0.1f, min(1e+02f, nentry("Q factor [style:knob]/peak 6/Multi Band Filter",5e+01f,0.1f,1e+02f,0.1f)));
// real block [-inf, inf]
E52 = E49*pow(1e+01f, -(0.05f*max(-5e+01f, min(5e+01f, vslider("gain [unit:dB]/peak 6/Multi Band Filter",0.0f,-5e+01f,5e+01f,0.1f)))))/E51;
E53 = 1.0f+E50;                                                      // real block [-inf, inf]
E54 = E52+E53;                                                       // real block [-inf, inf] invalid  <-- invalid from unbounded operands
E55 = 2.0f*((-1.0f+E50)/E54);                                        // real block [-inf, inf] invalid
E56 = E49/E51;                                                       // real block [-inf, inf]
// real block [-inf, inf]  <-- unbounded from here
E57 = tan(E0*max(2e+01f, min(2e+04f, nentry("freq [unit:Hz][style:knob]/peak 7/Multi Band Filter",8e+03f,2e+01f,2e+04f,1.0f))));
E58 = pow(E57, 2.0f);                                                // real block [-inf, inf]
// real block [0.1, 100] lsb -36
E59 = max(0.1f, min(1e+02f, nentry("Q factor [style:knob]/peak 7/Multi Band Filter",5e+01f,0.1f,1e+02f,0.1f)));
// real block [-inf, inf]
E60 = E57*pow(1e+01f, -(0.05f*max(-5e+01f, min(5e+01f, vslider("gain [unit:dB]/peak 7/Multi Band Filter",0.0f,-5e+01f,5e+01f,0.1f)))))/E59;
E61 = 1.0f+E58;                                                      // real block [-inf, inf]
E62 = E60+E61;                                                       // real block [-inf, inf] invalid  <-- invalid from unbounded operands
E63 = 2.0f*((-1.0f+E58)/E62);                                        // real block [-inf, inf] invalid
E64 = E57/E59;                                                       // real block [-inf, inf]
// real block [-inf, inf]  <-- unbounded from here
E65 = tan(E0*max(2e+01f, min(2e+04f, nentry("freq [unit:Hz][style:knob]/peak 8/Multi Band Filter",9e+03f,2e+01f,2e+04f,1.0f))));
E66 = pow(E65, 2.0f);                                                // real block [-inf, inf]
// real block [0.1, 100] lsb -36
E67 = max(0.1f, min(1e+02f, nentry("Q factor [style:knob]/peak 8/Multi Band Filter",5e+01f,0.1f,1e+02f,0.1f)));
// real block [-inf, inf]
E68 = E65*pow(1e+01f, -(0.05f*max(-5e+01f, min(5e+01f, vslider("gain [unit:dB]/peak 8/Multi Band Filter",0.0f,-5e+01f,5e+01f,0.1f)))))/E67;
E69 = 1.0f+E66;                                                      // real block [-inf, inf]
E70 = E68+E69;                                                       // real block [-inf, inf] invalid  <-- invalid from unbounded operands
E71 = 2.0f*((-1.0f+E66)/E70);                                        // real block [-inf, inf] invalid
E72 = E65/E67;                                                       // real block [-inf, inf]
// real block [-inf, inf]  <-- unbounded from here
E73 = tan(E0*max(2e+01f, min(2e+04f, nentry("freq [unit:Hz][style:knob]/peak 9/Multi Band Filter",1e+04f,2e+01f,2e+04f,1.0f))));
E74 = pow(E73, 2.0f);                                                // real block [-inf, inf]
// real block [0.1, 100] lsb -36
E75 = max(0.1f, min(1e+02f, nentry("Q factor [style:knob]/peak 9/Multi Band Filter",5e+01f,0.1f,1e+02f,0.1f)));
// real block [-inf, inf]
E76 = E73*pow(1e+01f, -(0.05f*max(-5e+01f, min(5e+01f, vslider("gain [unit:dB]/peak 9/Multi Band Filter",0.0f,-5e+01f,5e+01f,0.1f)))))/E75;
E77 = 1.0f+E74;                                                      // real block [-inf, inf]
E78 = E76+E77;                                                       // real block [-inf, inf] invalid  <-- invalid from unbounded operands
E79 = 2.0f*((-1.0f+E74)/E78);                                        // real block [-inf, inf] invalid
E80 = E73/E75;                                                       // real block [-inf, inf]
// real samp [-inf, inf] invalid
process = (FIR(IIR(FIR(IIR(FIR(IIR(FIR(IIR(FIR(IIR(FIR(IIR(FIR(IIR(FIR(IIR(FIR(IIR(FIR(IIR(IN[0]; -E7, -((-E4+E5)/E6)); (E8+E5)/E6, E7, (-E8+E5)/E6); -E15, -((-E12+E13)/E14)); (E16+E13)/E14, E15, (-E16+E13)/E14); -E23, -((-E20+E21)/E22)); (E24+E21)/E22, E23, (-E24+E21)/E22); -E31, -((-E28+E29)/E30)); (E32+E29)/E30, E31, (-E32+E29)/E30); -E39, -((-E36+E37)/E38)); (E40+E37)/E38, E39, (-E40+E37)/E38); -E47, -((-E44+E45)/E46)); (E48+E45)/E46, E47, (-E48+E45)/E46); -E55, -((-E52+E53)/E54)); (E56+E53)/E54, E55, (-E56+E53)/E54); -E63, -((-E60+E61)/E62)); (E64+E61)/E62, E63, (-E64+E61)/E62); -E71, -((-E68+E69)/E70)); (E72+E69)/E70, E71, (-E72+E69)/E70); -E79, -((-E76+E77)/E78)); (E80+E77)/E78, E79, (-E80+E77)/E78));
