// the interpolation from the first tap
import("stdfaust.lib");
d = hslider("d", 2.5, 1, 10, 0.001);
clip = max(-1.0) : min(1.0); // a bounded input : the intervals then say something
process = clip : \(x).(x@int(d) + ma.frac(d) * (x@(int(d) + 1) - x@int(d)));
