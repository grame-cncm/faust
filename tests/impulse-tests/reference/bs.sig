E0 = 1e+01f/float(count);                                     // real block [-inf, inf]  <-- unbounded from here
E1 = E0+R0';                                                  // real samp [-inf, inf] invalid
E2 = -E0+R0';                                                 // real samp [-inf, inf] invalid
R0 = select2(E1<1e+01f, select2(E2>1e+01f, 1e+01f, E2), E1);  // real samp [-inf, inf] invalid  <-- invalid from unbounded operands (the recursion)
process = (R0);                                               // real samp [-inf, inf] invalid
