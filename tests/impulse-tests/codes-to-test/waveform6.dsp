w1(x) = waveform {10,20,30,40,50,60},int(x):rdtable;

process(x,y) = y*(sin(w1(4*abs(x))));