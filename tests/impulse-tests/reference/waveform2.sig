// Size = 15
ID_0 = sigGen(waveform{...});
ID_1 = WRTbl2p(7,ID_0);
ID_2 = W0;
ID_3 = proj0(ID_2);
ID_4 = ID_3';
ID_5 = clocked(ID_4);
ID_6 = (ID_5+3);
ID_7 = ID_6%7;
ID_8 = letrec(W0 = (ID_7));
ID_9 = proj0(ID_8);
ID_10 = ID_9@0;
ID_11 = max(0, ID_10);
ID_12 = min(6, ID_11);
ID_13 = clocked(ID_12);
ID_14 = sigRDTbl(ID_1,ID_13);
SIG = (ID_14);
