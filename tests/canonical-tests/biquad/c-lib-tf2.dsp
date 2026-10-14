// fi.tf2 (the libraries' writing)
import("stdfaust.lib");
b0 = 0.2; b1 = 0.4; b2 = 0.2; a1 = -0.5; a2 = 0.25;
clip = max(-1.0) : min(1.0); // a bounded input : the intervals then say something
process = clip : fi.tf2(b0, b1, b2, a1, a2);
