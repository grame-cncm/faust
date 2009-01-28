import("filter.lib");

line(i) =  vgroup("line %i", fdelay5(128, d) : *(g) )
    with {  g = vslider("gain (dB)", -60, -60, 4, 0.1) : db2linear : smooth(0.995);
            d = nentry("delay (samp)", 10, 10, 128, 0.1) : smooth(0.995);  };

process = hgroup("", par(i, 8, line(i)) );
 
