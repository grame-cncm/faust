// A one-pole lowpass, its peak read by a bargraph, and a dry output.
p = hslider("pole [unit:x]", 0.5, 0, 0.99, 0.01);
peak = abs : max ~ *(0.999);
lp = *(1 - p) : + ~ *(p);
meter = _ <: attach(_, peak : hbargraph("level", 0, 1));
process = _ <: (lp : meter), _;
