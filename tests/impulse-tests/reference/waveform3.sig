R0 = (3+R0')%7;  // int samp [0, 6] lsb 0
process = (sigRDTbl(WRTbl2p(7, sigGen(waveform{...})), max(0, min(R0, 6))));  // real samp [1.1, 7.7] lsb -32
