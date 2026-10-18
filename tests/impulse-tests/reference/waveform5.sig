// int block [10, 50] lsb 0
E0 = sigRDTbl(WRTbl2p(5, sigGen(waveform{...})), max(0, min(int(4.0f*max(0.0f, min(1.0f, hslider("value",0.0f,0.0f,1.0f,0.01f)))), 4)));
process = (IN[0]*sin(float(E0)), E0);  // real samp [-inf, inf] invalid ; int block [10, 50] lsb 0
