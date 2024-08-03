// Size = 12
ID_0 = W0;
ID_1 = proj0(ID_0);
ID_10 = vslider("Volume[style:knob][acc: 0 0 -10 0 10]",0.5f,0.0f,1.0f,0.1f);
ID_11 = ID_9*ID_10;
ID_2 = ID_1';
ID_3 = ID_2*1103515245;
ID_4 = ID_3+12345;
ID_5 = letrec(W0 = (ID_4));
ID_6 = proj0(ID_5);
ID_7 = ID_6@0;
ID_8 = float(ID_7);
ID_9 = ID_8/2.1474836e+09f;
SIG = (ID_11);
