E0 = IIR(1; 1);                   // int samp [-2147483648, 2147483647] lsb 0 overflow
E1 = -51+E0;                      // int samp [-50, 2147483598] lsb 0 overflow moves
E2 = 51-E0;                       // int samp [-2147483598, 50] lsb 0 overflow moves
E3 = -4+(-1+E0)%9;                // int samp [-12, 4] lsb 0
E4 = abs(select2(E3==0, E3, 5));  // int samp [0, 12] lsb 0
E5 = E1%select2(E4==0, E4, 1);    // int samp [-11, 11] lsb 0 invalid  <-- invalid from here
process = (float(E1%7), float(E1%-7), float(E2%7), float(E2%-7), float(E5));  // real samp [-6, 6] lsb -1 ; real samp [-6, 6] lsb -1 ; real samp [-6, 6] lsb -1 ; real samp [-6, 6] lsb -1 ; real samp [-11, 11] lsb -1 invalid
