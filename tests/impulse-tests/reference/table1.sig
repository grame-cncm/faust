E0 = sigGen(waveform{...});        // real samp [-1, 1] lsb -33
E1 = max(0, min(IIR(1; 1)%8, 7));  // int samp [0, 7] lsb 0
process = (sigRDTbl(WRTbl2p(8, E0), E1), sigRDTbl(sigWRTbl4p(8; E0; E1; waveform{...} ), E1));  // real samp [-1, 1] lsb -33 ; real samp [-11, 11] lsb -33
