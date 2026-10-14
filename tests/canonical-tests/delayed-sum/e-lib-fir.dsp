// fi.fir((1, 1, 1)) (the libraries' writing)
import("stdfaust.lib");
clip = max(-1.0) : min(1.0); // a bounded input : the intervals then say something
process = clip : fi.fir((1, 1, 1));
