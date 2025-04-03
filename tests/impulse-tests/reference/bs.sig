// Size = 14
ID_0 = float(count);
ID_1 = 1e+01f/ID_0;
ID_2 = W0;
ID_3 = proj0(ID_2);
ID_4 = ID_3';
ID_5 = ID_1+ID_4;
ID_6 = ID_5<1e+01f;
ID_7 = ID_4-ID_1;
ID_8 = ID_7>1e+01f;
ID_9 = select2(ID_8,1e+01f,ID_7);
ID_10 = select2(ID_6,ID_9,ID_5);
ID_11 = letrec(W0 = (ID_10));
ID_12 = proj0(ID_11);
ID_13 = ID_12@0;
SIG = (ID_13);
