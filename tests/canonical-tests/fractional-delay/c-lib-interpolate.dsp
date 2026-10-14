// it.interpolate_linear (the libraries' writing)
import("stdfaust.lib");
d = hslider("d", 2.5, 1, 10, 0.001);
clip = max(-1.0) : min(1.0); // a bounded input : the intervals then say something
process = clip : \(x).(it.interpolate_linear(ma.frac(d), x@int(d), x@(int(d) + 1)));
