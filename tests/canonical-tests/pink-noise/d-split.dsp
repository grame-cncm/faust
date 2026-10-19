// the poles, then the zeros with the first tap apart
import("stdfaust.lib");
r = (+(12345) ~ *(1103515245)) : float; // the generator of no.noise, before its scaling
R = 2147483647.0;
poles = fi.iir((1.0), (-2.494956002, 2.017265875, -0.522189400));
process = r : poles <: (/(R) : fi.fir((0.0, -0.095993537, 0.050612699, -0.004408786))), *(0.049922035/R) :> _;
