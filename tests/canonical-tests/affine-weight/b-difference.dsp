// a + u (b - a), u = f/4 - 50
import("stdfaust.lib");
clip = max(-1.0) : min(1.0); // a bounded input : the intervals then say something
f = hslider("v", 202, 200, 204, 1);
process = clip, clip <: (_, !), ((!, _), (_, !) : - : *(0.25*f - 50)) :> _;
