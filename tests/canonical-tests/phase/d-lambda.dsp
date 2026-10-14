// frac(y' + inc) written as a function of y'
import("stdfaust.lib");
inc = hslider("inc", 0.01, 0, 0.1, 0.0001);
clip = max(-1.0) : min(1.0); // a bounded input : the intervals then say something
process = (\(p).(ma.frac(p + inc))) ~ _;
