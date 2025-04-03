// Size = 16
ID_0 = waveform{...}>0.0f;
ID_1 = prefix(1,ID_0);
ID_2 = float(fSamplingFreq);
ID_3 = max(1.0f, ID_2);
ID_4 = min(1.92e+05f, ID_3);
ID_5 = 7e+02f/ID_4;
ID_6 = W0;
ID_7 = proj0(ID_6);
ID_8 = ID_7';
ID_9 = ID_5+ID_8;
ID_10 = select2(ID_1,ID_9,waveform{...});
ID_11 = floor(ID_10);
ID_12 = ID_10-ID_11;
ID_13 = letrec(W0 = (ID_12));
ID_14 = proj0(ID_13);
ID_15 = ID_14@0;
SIG = (ID_15, waveform{...}, waveform{...});
