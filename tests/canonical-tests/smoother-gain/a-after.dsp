// the gain 0.25 after the smoother
import("stdfaust.lib");
clip = max(-1.0) : min(1.0); // a bounded input : the intervals then say something
process = clip : si.smoo : *(0.25);
