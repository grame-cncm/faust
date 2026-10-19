// the gain 0.25 after the FIR
import("stdfaust.lib");
clip = max(-1.0) : min(1.0); // a bounded input : the intervals then say something
process = clip : fi.fir((0.5, 0.25, 0.125)) : *(0.25);
