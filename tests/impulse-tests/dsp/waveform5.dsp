w1(x) = waveform {10,20,30,40,50},int(x):rdtable;

process = *(sin(w1(4*hslider("value",0,0,1,0.01)))), w1(4*hslider("value",0,0,1,0.01));
