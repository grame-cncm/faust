// Size = 16
ID_0 = sigGen(waveform{...});
ID_1 = WRTbl2p(8,ID_0);
ID_2 = W0;
ID_3 = proj0(ID_2);
ID_4 = ID_3';
ID_5 = clocked(ID_4);
ID_6 = ID_5+1;
ID_7 = letrec(W0 = (ID_6));
ID_8 = proj0(ID_7);
ID_9 = ID_8@0;
ID_10 = ID_9%8;
ID_11 = clocked(ID_10);
ID_12 = sigRDTbl(ID_1,ID_11);
ID_13 = clocked(waveform{...});
ID_14 = sigWRTbl4p(8,ID_0,ID_11,ID_13);
ID_15 = sigRDTbl(ID_14,ID_11);
SIG = (ID_12, ID_15);
