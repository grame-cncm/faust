// Size = 13
ID_0 = waveform{...};
ID_1 = write(7,ID_0,,);
ID_10 = min(ID_9, 6);
ID_11 = max(0, ID_10);
ID_12 = read(ID_1,ID_11);
ID_2 = W0;
ID_3 = proj0(ID_2);
ID_4 = ID_3';
ID_5 = (ID_4+3);
ID_6 = ID_5%7;
ID_7 = letrec(W0 = (ID_6));
ID_8 = proj0(ID_7);
ID_9 = ID_8@0;
SIG = (ID_12);
