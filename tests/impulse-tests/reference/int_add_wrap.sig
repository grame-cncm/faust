E0 = IIR(1; 1);                                                               // int samp [-2147483648, 2147483647] lsb 0 overflow
E1 = -1+E0;                                                                   // int samp [-2147483648, 2147483647] lsb 0 overflow
E2 = sigRDTbl(WRTbl2p(5, sigGen(waveform{...})), max(0, min(E1%5, 4)));       // int samp [-2147483000, 2147483000] lsb 0
E3 = sigRDTbl(WRTbl2p(5, sigGen(waveform{...})), max(0, min((E1>>2)%5, 4)));  // int samp [-1000000000, 1000000000] lsb 0
E4 = E2+E3;                                                                   // int samp [-2147483648, 2147483647] lsb 0 overflow
E5 = -E3;                                                                     // int samp [-1000000000, 1000000000] lsb 0
E6 = E5+E2;                                                                   // int samp [-2147483648, 2147483647] lsb 0 overflow
E7 = -1-E2+E0+E3;                                                             // int samp [-2147483648, 2147483647] lsb 0 overflow
E8 = -1+E5+E0+E2;                                                             // int samp [-2147483648, 2147483647] lsb 0 overflow
// real samp [-1, 0.9999695] lsb -48 ; real samp [0, 0.99998474] lsb -49 ; real samp [-1, 0.9999695] lsb -48 ; real samp [0, 0.99998474] lsb -49 ; real samp [-1, 0.9999695] lsb -48 ; real samp [0, 0.99998474] lsb -49 ; real samp [-1, 0.9999695] lsb -48 ; real samp [0, 0.99998474] lsb -49
process = (3.0517578e-05f*float(E4>>16), 1.5258789e-05f*float(E4&65535), 3.0517578e-05f*float(E6>>16), 1.5258789e-05f*float(E6&65535), 3.0517578e-05f*float(E7>>16), 1.5258789e-05f*float(E7&65535), 3.0517578e-05f*float(E8>>16), 1.5258789e-05f*float(E8&65535));
