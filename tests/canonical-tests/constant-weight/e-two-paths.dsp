// x - 0.5 (1 - s) x
import("stdfaust.lib");
clip = max(-1.0) : min(1.0); // a bounded input : the intervals then say something
s = hslider("s", 0.5, 0, 1, 0.01);
process = clip <: _, *(1-s) : _, *(0.5) : -;
