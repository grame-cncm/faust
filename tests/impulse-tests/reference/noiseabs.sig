// Size = 12
ID_0 = W0;
ID_1 = proj0(ID_0);
ID_2 = ID_1';
ID_3 = clocked(ID_2);
ID_4 = 1103515245*ID_3;
ID_5 = ID_4+12345;
ID_6 = letrec(W0 = (ID_5));
ID_7 = proj0(ID_6);
ID_8 = ID_7@0;
ID_9 = float(ID_8);
ID_10 = 4.656613e-10f*ID_9;
ID_11 = abs(ID_10);
SIG = (ID_11);
