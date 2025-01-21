// Size = 15
ID_0 = float(count);
ID_1 = 1e+01f/ID_0;
ID_2 = W0;
ID_3 = proj0(ID_2);
ID_4 = ID_3';
ID_5 = clocked(ID_4);
ID_6 = ID_1+ID_5;
ID_7 = ID_6<1e+01f;
ID_8 = ID_5-ID_1;
ID_9 = ID_8>1e+01f;
ID_10 = select2(ID_9,1e+01f,ID_8);
ID_11 = select2(ID_7,ID_10,ID_6);
ID_12 = letrec(W0 = (ID_11));
ID_13 = proj0(ID_12);
ID_14 = ID_13@0;
SIG = (ID_14);
