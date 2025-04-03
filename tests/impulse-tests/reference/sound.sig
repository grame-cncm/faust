// Size = 16
ID_0 = soundfile("son[url:{'sound1';'sound2'}]");
ID_1 = W0;
ID_2 = proj0(ID_1);
ID_3 = ID_2';
ID_4 = ID_3+1;
ID_5 = letrec(W0 = (ID_4));
ID_6 = proj0(ID_5);
ID_7 = ID_6@0;
ID_8 = length(ID_0,0);
ID_9 = ID_8+-1;
ID_10 = min(ID_7, ID_9);
ID_11 = max(0, ID_10);
ID_12 = buffer(ID_0,0,0,ID_11);
ID_13 = buffer(ID_0,1,0,ID_11);
ID_14 = buffer(ID_0,2,0,ID_11);
ID_15 = buffer(ID_0,3,0,ID_11);
SIG = (ID_12, ID_13, ID_14, ID_15);
