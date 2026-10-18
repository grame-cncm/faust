E0 = IN[0]-IN[1];                                        // real samp [-inf, inf] invalid  <-- invalid from unbounded operands
E1 = IN[1]-IN[0];                                        // real samp [-inf, inf] invalid  <-- invalid from unbounded operands
E2 = -IN[2]+E0;                                          // real samp [-inf, inf] invalid
E3 = min(1.92e+05f, max(5e+01f, float(fSamplingFreq)));  // real konst [50, 192000] lsb -27
E4 = -E3;                                                // real konst [-192000, -50] lsb -27
E5 = E3*IN[0];                                           // real samp [-inf, inf]
E6 = -E5;                                                // real samp [-inf, inf]
E7 = -(IN[0]+IN[1]);                                     // real samp [-inf, inf] invalid
E8 = 3.0f*IN[0]';                                        // real samp [-inf, inf]
// real samp [-inf, inf] ; real samp [-inf, inf] ; real samp [-inf, inf] ; real samp [-inf, inf] ; real samp [-inf, inf] invalid ; real samp [-inf, inf] invalid ; real samp [-inf, inf] invalid ; real samp [-inf, inf] invalid ; real samp [-inf, inf] invalid ; real samp [-inf, inf] invalid ; real samp [-inf, inf] invalid ; real samp [0, inf] invalid ; real konst [-192000, -50] lsb -27 ; real samp [-inf, inf] ; real samp [-inf, inf] ; real samp [-inf, inf] ; real konst [-192000, -50] lsb -27 ; real samp [-inf, inf] ; real samp [-inf, inf] ; real konst [-192000, -50] lsb -27 ; real samp [-inf, inf] ; real konst [50, 192000] lsb -27 ; real samp [-inf, inf] invalid ; real samp [-inf, inf] invalid ; real samp [-inf, inf] ; real samp [-inf, inf] ; real samp [-inf, inf] ; real samp [-inf, inf] ; real samp [-inf, inf] ; real samp [-inf, inf] ; real samp [-inf, inf] ; real samp [-inf, inf]
process = (-IN[0], -IN[0], -IN[0], IN[0], E0, E1, E0, E2, E2, 3.0f*E1, 3.0f*E0-E0, 4.0f*abs(E1), E4, E6, IN[0], -IN[0], E4, E6, E5, E4, E6, E3, E7, E7, -IN[0]@10, -IN[0]@10, E8, 3.0f*IN[0]@2, E8, 4.0f*IN[0]@2, -(E3*IN[0]'), -(E3*IN[0]@2));
