// the scaling in the coefficients of the filter
import("stdfaust.lib");
r = (+(12345) ~ *(1103515245)) : float; // the generator of no.noise, before its scaling
R = 2147483647.0;
process = r : fi.iir((0.049922035/R, -0.095993537/R, 0.050612699/R, -0.004408786/R), (-2.494956002, 2.017265875, -0.522189400));
