// Size = 15
ID_0 = W0;
ID_1 = proj0(ID_0);
ID_2 = ID_1';
ID_3 = ID_2+1;
ID_4 = letrec(W0 = (ID_3));
ID_5 = proj0(ID_4);
ID_6 = ID_5@0;
ID_7 = W1;
ID_8 = proj0(ID_7);
ID_9 = ID_8';
ID_10 = ID_9+2;
ID_11 = letrec(W1 = (ID_10));
ID_12 = proj0(ID_11);
ID_13 = ID_12@0;
ID_14 = select2(waveform{...},ID_6,ID_13);
SIG = (ID_14);
