// real block [-1.0000001, 0] lsb -72
E0 = 0.0055555557f*(-9e+01f+max(-9e+01f, min(9e+01f, nentry("[1]pan[style:knob]",0.0f,-9e+01f,9e+01f,1.0f))));
E1 = sqrt(1.0f+E0);  // real block [0, 1] lsb -72 invalid  <-- invalid from here
process = (sqrt(-E0)*IN[0], E1*IN[0]);  // real samp [-inf, inf] invalid ; real samp [-inf, inf] invalid
