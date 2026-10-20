// the weight (f - 200)/4 and its complement
import("stdfaust.lib");
clip = max(-1.0) : min(1.0); // a bounded input : the intervals then say something
f = hslider("v", 202, 200, 204, 1);
process = clip, clip : *(1 - (f-200)*0.25), *((f-200)*0.25) :> _;
