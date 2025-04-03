// Size = 13
ID_0 = sigGen(waveform{...});
ID_1 = WRTbl2p(8,ID_0);
ID_2 = W0;
ID_3 = proj0(ID_2);
ID_4 = ID_3';
ID_5 = ID_4+1;
ID_6 = letrec(W0 = (ID_5));
ID_7 = proj0(ID_6);
ID_8 = ID_7@0;
ID_9 = ID_8%8;
ID_10 = sigRDTbl(ID_1,ID_9);
ID_11 = sigWRTbl4p(8,ID_0,ID_9,waveform{...});
ID_12 = sigRDTbl(ID_11,ID_9);
SIG = (ID_10, ID_12);
