R0 = (IN[0]+E0)@4;  // real samp [-inf, inf] invalid  <-- invalid from unbounded operands (the recursion)
E0 = 0.5f*R0';      // real samp [-inf, inf] invalid
process = (0.5f*IN[0]+E0);  // real samp [-inf, inf] invalid
