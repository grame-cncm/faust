// Size = 13
ID_0 = W0;
ID_1 = proj0(ID_0);
ID_10 = proj0(ID_9);
ID_11 = ID_10@0;
ID_12 = IN[0]*ID_11;
ID_2 = ID_1';
ID_3 = ID_2*0.999f;
ID_4 = vslider("[1]",0.0f,-7e+01f,4.0f,0.1f);
ID_5 = ID_4/2e+01f;
ID_6 = pow(1e+01f, ID_5);
ID_7 = ID_6*0.001f;
ID_8 = ID_3+ID_7;
ID_9 = letrec(W0 = (ID_8));
SIG = (ID_12);
