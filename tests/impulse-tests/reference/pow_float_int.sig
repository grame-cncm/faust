// Size = 6
ID_0 = hslider("x",0.6f,0.0f,1.0f,0.01f);
ID_1 = pow(ID_0, 2.0f);
ID_2 = hslider("n",5e+04f,0.0f,5e+04f,1.0f);
ID_3 = int(ID_2);
ID_4 = pow(ID_3, 2);
ID_5 = float(ID_4);
SIG = (ID_1, ID_5);
