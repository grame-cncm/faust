// Size = 13
ID_0 = vslider("Volume[style:knob][acc: 0 0 -10 0 10]",0.5f,0.0f,1.0f,0.1f);
ID_1 = 4.656613e-10f*ID_0;
ID_2 = W0;
ID_3 = proj0(ID_2);
ID_4 = ID_3';
ID_5 = clocked(ID_4);
ID_6 = 1103515245*ID_5;
ID_7 = ID_6+12345;
ID_8 = letrec(W0 = (ID_7));
ID_9 = proj0(ID_8);
ID_10 = ID_9@0;
ID_11 = float(ID_10);
ID_12 = ID_1*ID_11;
SIG = (ID_12);
