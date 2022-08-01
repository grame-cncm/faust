
in = waveform{0.1, 0.56, 1.3, 8.9} : !,_;

process = pow(in*3, 0.5), pow(in*3, 0.25), 
    pow(in*4, 0.125), pow(in*4, 0.0625),
    pow(in*5, 2), pow(in*5, 2.0),
    pow(int(in*6), 2), pow(int(in*6), 2.0),
    pow(in*7, 2.0001), pow(in*7, 2.0000001),
    pow(in*8, 0), pow(in*8, 1),
    pow(in*9, 0.0), pow(in*9, 1.0);
