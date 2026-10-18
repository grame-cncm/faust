R0 = (3+R0')%7;  // int samp [0, 6] lsb 0
process = (sigRDTbl(WRTbl2p(7, sigGen(waveform{...})), min(6, max(0, R0))));  // int samp [10, 70] lsb 0
