// the gain 0.25 already in the coefficients
import("stdfaust.lib");
clip = max(-1.0) : min(1.0); // a bounded input : the intervals then say something
process = clip : fi.fir((0.125, 0.0625, 0.03125));
