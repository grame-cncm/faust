R0   = max(-1.0f, min(1.0f, hslider("[0] EchoWarp",0.0f,-1.0f,1.0f,0.001f)));  // real block [-1, 1] lsb -42
R1   = 1e+02f*(1.0f+R0);                                                       // real samp [0, 200] lsb -68
R2.0 = 0.005f*IN[0]+0.995f*R2.0';                                              // real samp [-inf, inf] invalid  <-- invalid from unbounded operands (the recursion)
R2.1 = R2.0@100;                                                               // real samp [-inf, inf] invalid
process = (IN[0]+mix(frac(R1), R2.0@min(1025, max(0, int(R1))), R2.0@min(1025, max(0, 1+int(R1)))));  // real samp [-inf, inf] invalid
