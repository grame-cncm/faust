import("delay.lib");

smooth(c) = *(1-c) : +~*(c);
db2linear(n) = pow(10, n/20.0);

line(i) =  vgroup("line %i", fdelay5(128, d) : *(g) )
    with {  g = vslider("gain (dB)", -60, -60, 4, 0.1) : db2linear : smooth(0.995);
            d = nentry("delay (samp)", 10, 10, 128, 0.1) : smooth(0.995);  };

process = hgroup("", par(i, 8, line(i)));
 
