// c (d SR) + (1 - c) y'
import("stdfaust.lib");
d = hslider("d", 1, 0, 2, 0.001);
c = 44.1 / ma.SR;
clip = max(-1.0) : min(1.0); // a bounded input : the intervals then say something
process = (d * ma.SR) : *(c) : + ~ *(1 - c);
