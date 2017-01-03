del = library("delays.lib");
sig = library("signals.lib");
bas = library("basics.lib");

line(i) =  vgroup("line %i", del.fdelay5(128, d) : *(g) )
    with {  g = vslider("gain (dB)", -60, -60, 4, 0.1) : bas.db2linear : sig.smooth(0.995);
            d = nentry("delay (samp)", 10, 10, 128, 0.1) : sig.smooth(0.995);  };

process = hgroup("", par(i, 8, line(i)) );
 
