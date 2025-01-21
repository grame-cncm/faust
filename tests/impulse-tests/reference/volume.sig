// Size = 15
ID_0 = clocked(IN[0]);
ID_1 = vslider("[1]",0.0f,-7e+01f,4.0f,0.1f);
ID_2 = 0.05f*ID_1;
ID_3 = pow(1e+01f, ID_2);
ID_4 = 0.001f*ID_3;
ID_5 = W0;
ID_6 = proj0(ID_5);
ID_7 = ID_6';
ID_8 = clocked(ID_7);
ID_9 = 0.999f*ID_8;
ID_10 = ID_4+ID_9;
ID_11 = letrec(W0 = (ID_10));
ID_12 = proj0(ID_11);
ID_13 = ID_12@0;
ID_14 = ID_0*ID_13;
SIG = (ID_14);
