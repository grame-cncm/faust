// pow(10, g / 20)
import("stdfaust.lib");
g = hslider("g", -6, -60, 0, 0.1);
clip = max(-1.0) : min(1.0); // a bounded input : the intervals then say something
process = clip : *(pow(10, g / 20));
