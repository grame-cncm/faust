// real block [-1.0000001, 0] lsb -72
E0  = 0.0055555557f*(-9e+01f+max(-9e+01f, min(9e+01f, nentry("[1]pan[style:knob]/Ch 0/mixer",0.0f,-9e+01f,9e+01f,1.0f))));
// real samp [-inf, inf] invalid  <-- invalid from unbounded operands
E1  = (1.0f-float(checkbox("mute/Ch 0/mixer")>0.0f))*(IN[0]*(0.001f*IIR(pow(1e+01f, 0.05f*max(-7e+01f, min(4.0f, vslider("[1]/[2]/Ch 0/mixer",0.0f,-7e+01f,4.0f,0.1f)))); 0.999f)));
E2  = -(1.0f/min(1.92e+05f, max(5e+01f, float(fSamplingFreq))));                 // real konst [-0.020000001, -5.2083333e-06] lsb -32
R0  = max(E2+R0', abs(E1));                                                      // real samp [0, inf] invalid
// real samp [-inf, inf] invalid
E3  = attach(E1, vbargraph("[2][unit:dB]/[2]/Ch 0/mixer",-7e+01f,5.0f,2e+01f*log10(max(0.00031622776f, R0))));
// real block [-1.0000001, 0] lsb -72
E4  = 0.0055555557f*(-9e+01f+max(-9e+01f, min(9e+01f, nentry("[1]pan[style:knob]/Ch 4/mixer",0.0f,-9e+01f,9e+01f,1.0f))));
// real samp [-inf, inf] invalid  <-- invalid from unbounded operands
E5  = (1.0f-float(checkbox("mute/Ch 4/mixer")>0.0f))*(IN[4]*(0.001f*IIR(pow(1e+01f, 0.05f*max(-7e+01f, min(4.0f, vslider("[1]/[2]/Ch 4/mixer",0.0f,-7e+01f,4.0f,0.1f)))); 0.999f)));
R1  = max(E2+R1', abs(E5));                                                      // real samp [0, inf] invalid
// real samp [-inf, inf] invalid
E6  = attach(E5, vbargraph("[2][unit:dB]/[2]/Ch 4/mixer",-7e+01f,5.0f,2e+01f*log10(max(0.00031622776f, R1))));
// real block [-1.0000001, 0] lsb -72
E7  = 0.0055555557f*(-9e+01f+max(-9e+01f, min(9e+01f, nentry("[1]pan[style:knob]/Ch 1/mixer",0.0f,-9e+01f,9e+01f,1.0f))));
// real samp [-inf, inf] invalid  <-- invalid from unbounded operands
E8  = (1.0f-float(checkbox("mute/Ch 1/mixer")>0.0f))*(IN[1]*(0.001f*IIR(pow(1e+01f, 0.05f*max(-7e+01f, min(4.0f, vslider("[1]/[2]/Ch 1/mixer",0.0f,-7e+01f,4.0f,0.1f)))); 0.999f)));
R2  = max(E2+R2', abs(E8));                                                      // real samp [0, inf] invalid
// real samp [-inf, inf] invalid
E9  = attach(E8, vbargraph("[2][unit:dB]/[2]/Ch 1/mixer",-7e+01f,5.0f,2e+01f*log10(max(0.00031622776f, R2))));
// real block [-1.0000001, 0] lsb -72
E10 = 0.0055555557f*(-9e+01f+max(-9e+01f, min(9e+01f, nentry("[1]pan[style:knob]/Ch 5/mixer",0.0f,-9e+01f,9e+01f,1.0f))));
// real samp [-inf, inf] invalid  <-- invalid from unbounded operands
E11 = (1.0f-float(checkbox("mute/Ch 5/mixer")>0.0f))*(IN[5]*(0.001f*IIR(pow(1e+01f, 0.05f*max(-7e+01f, min(4.0f, vslider("[1]/[2]/Ch 5/mixer",0.0f,-7e+01f,4.0f,0.1f)))); 0.999f)));
R3  = max(E2+R3', abs(E11));                                                     // real samp [0, inf] invalid
// real samp [-inf, inf] invalid
E12 = attach(E11, vbargraph("[2][unit:dB]/[2]/Ch 5/mixer",-7e+01f,5.0f,2e+01f*log10(max(0.00031622776f, R3))));
// real block [-1.0000001, 0] lsb -72
E13 = 0.0055555557f*(-9e+01f+max(-9e+01f, min(9e+01f, nentry("[1]pan[style:knob]/Ch 2/mixer",0.0f,-9e+01f,9e+01f,1.0f))));
// real samp [-inf, inf] invalid  <-- invalid from unbounded operands
E14 = (1.0f-float(checkbox("mute/Ch 2/mixer")>0.0f))*(IN[2]*(0.001f*IIR(pow(1e+01f, 0.05f*max(-7e+01f, min(4.0f, vslider("[1]/[2]/Ch 2/mixer",0.0f,-7e+01f,4.0f,0.1f)))); 0.999f)));
R4  = max(E2+R4', abs(E14));                                                     // real samp [0, inf] invalid
// real samp [-inf, inf] invalid
E15 = attach(E14, vbargraph("[2][unit:dB]/[2]/Ch 2/mixer",-7e+01f,5.0f,2e+01f*log10(max(0.00031622776f, R4))));
// real block [-1.0000001, 0] lsb -72
E16 = 0.0055555557f*(-9e+01f+max(-9e+01f, min(9e+01f, nentry("[1]pan[style:knob]/Ch 6/mixer",0.0f,-9e+01f,9e+01f,1.0f))));
// real samp [-inf, inf] invalid  <-- invalid from unbounded operands
E17 = (1.0f-float(checkbox("mute/Ch 6/mixer")>0.0f))*(IN[6]*(0.001f*IIR(pow(1e+01f, 0.05f*max(-7e+01f, min(4.0f, vslider("[1]/[2]/Ch 6/mixer",0.0f,-7e+01f,4.0f,0.1f)))); 0.999f)));
R5  = max(E2+R5', abs(E17));                                                     // real samp [0, inf] invalid
// real samp [-inf, inf] invalid
E18 = attach(E17, vbargraph("[2][unit:dB]/[2]/Ch 6/mixer",-7e+01f,5.0f,2e+01f*log10(max(0.00031622776f, R5))));
// real block [-1.0000001, 0] lsb -72
E19 = 0.0055555557f*(-9e+01f+max(-9e+01f, min(9e+01f, nentry("[1]pan[style:knob]/Ch 3/mixer",0.0f,-9e+01f,9e+01f,1.0f))));
// real samp [-inf, inf] invalid  <-- invalid from unbounded operands
E20 = (1.0f-float(checkbox("mute/Ch 3/mixer")>0.0f))*(IN[3]*(0.001f*IIR(pow(1e+01f, 0.05f*max(-7e+01f, min(4.0f, vslider("[1]/[2]/Ch 3/mixer",0.0f,-7e+01f,4.0f,0.1f)))); 0.999f)));
R6  = max(E2+R6', abs(E20));                                                     // real samp [0, inf] invalid
// real samp [-inf, inf] invalid
E21 = attach(E20, vbargraph("[2][unit:dB]/[2]/Ch 3/mixer",-7e+01f,5.0f,2e+01f*log10(max(0.00031622776f, R6))));
// real block [-1.0000001, 0] lsb -72
E22 = 0.0055555557f*(-9e+01f+max(-9e+01f, min(9e+01f, nentry("[1]pan[style:knob]/Ch 7/mixer",0.0f,-9e+01f,9e+01f,1.0f))));
// real samp [-inf, inf] invalid  <-- invalid from unbounded operands
E23 = (1.0f-float(checkbox("mute/Ch 7/mixer")>0.0f))*(IN[7]*(0.001f*IIR(pow(1e+01f, 0.05f*max(-7e+01f, min(4.0f, vslider("[1]/[2]/Ch 7/mixer",0.0f,-7e+01f,4.0f,0.1f)))); 0.999f)));
R7  = max(E2+R7', abs(E23));                                                     // real samp [0, inf] invalid
// real samp [-inf, inf] invalid
E24 = attach(E23, vbargraph("[2][unit:dB]/[2]/Ch 7/mixer",-7e+01f,5.0f,2e+01f*log10(max(0.00031622776f, R7))));
// real samp [3.1622753e-07, 1.585103] lsb -478
E25 = 0.001f*IIR(pow(1e+01f, 0.05f*max(-7e+01f, min(4.0f, vslider("[1]/stereo out/mixer",0.0f,-7e+01f,4.0f,0.1f)))); 0.999f);
// real samp [-inf, inf] invalid
E26 = (sqrt(-E0)*E3+sqrt(-E4)*E6+(sqrt(-E7)*E9+sqrt(-E10)*E12)+(sqrt(-E13)*E15+sqrt(-E16)*E18+(sqrt(-E19)*E21+sqrt(-E22)*E24)))*E25;
R8  = max(E2+R8', abs(E26));                                                     // real samp [0, inf] invalid
E27 = sqrt(1.0f+E0);                                                             // real block [0, 1] lsb -72 invalid  <-- invalid from here
E28 = sqrt(1.0f+E4);                                                             // real block [0, 1] lsb -72 invalid  <-- invalid from here
E29 = sqrt(1.0f+E7);                                                             // real block [0, 1] lsb -72 invalid  <-- invalid from here
E30 = sqrt(1.0f+E10);                                                            // real block [0, 1] lsb -72 invalid  <-- invalid from here
E31 = sqrt(1.0f+E13);                                                            // real block [0, 1] lsb -72 invalid  <-- invalid from here
E32 = sqrt(1.0f+E16);                                                            // real block [0, 1] lsb -72 invalid  <-- invalid from here
E33 = sqrt(1.0f+E19);                                                            // real block [0, 1] lsb -72 invalid  <-- invalid from here
E34 = sqrt(1.0f+E22);                                                            // real block [0, 1] lsb -72 invalid  <-- invalid from here
E35 = E25*(E27*E3+E28*E6+(E29*E9+E30*E12)+(E31*E15+E32*E18+(E33*E21+E34*E24)));  // real samp [-inf, inf] invalid
R9  = max(E2+R9', abs(E35));                                                     // real samp [0, inf] invalid
// real samp [-inf, inf] invalid ; real samp [-inf, inf] invalid
process = (attach(E26, vbargraph("[2][unit:dB]/L/stereo out/mixer",-7e+01f,5.0f,2e+01f*log10(max(0.00031622776f, R8)))), attach(E35, vbargraph("[2][unit:dB]/R/stereo out/mixer",-7e+01f,5.0f,2e+01f*log10(max(0.00031622776f, R9)))));
