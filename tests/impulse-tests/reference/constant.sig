E0 = min(1.92e+05f, max(5e+01f, float(fSamplingFreq)));  // real konst [50, 192000] lsb -27
E1 = int(floor(E0))%2;                                   // int konst [0, 1] lsb 0
E2 = int(floor(0.5f*E0))%2;                              // int konst [0, 1] lsb 0
E3 = FIR(IN[0]; 1.0f, 1.0f);                             // real samp [-inf, inf] invalid  <-- invalid from unbounded operands
// real samp [-inf, inf] invalid
process = (1.0f/E0*(select2(E1, 0.0f, IN[0])+select2(E2, 0.0f, E3@max(0, min(E1, 1)))+select2(int(floor(0.25f*E0))%2, 0.0f, (E3+E3@2)@max(0, min(E1+2*E2, 3)))));
