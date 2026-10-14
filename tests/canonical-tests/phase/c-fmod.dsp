// fmod(y' + inc, 1), the same for a nonnegative phase
import("stdfaust.lib");
inc = hslider("inc", 0.01, 0, 0.1, 0.0001);
clip = max(-1.0) : min(1.0); // a bounded input : the intervals then say something
process = (+(inc) : fmod(_, 1.0)) ~ _;
