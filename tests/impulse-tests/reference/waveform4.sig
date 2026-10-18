R0 = (3+R0')%7;           // int samp [0, 6] lsb 0
E0 = max(0, min(R0, 6));  // int samp [0, 6] lsb 0
// int samp [10, 70] lsb 0 ; real samp [1.1, 7.7] lsb -32
process = (sigRDTbl(WRTbl2p(7, sigGen(waveform{...})), E0), sigRDTbl(WRTbl2p(7, sigGen(waveform{...})), E0));
