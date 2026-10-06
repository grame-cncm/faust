// ba.tabulate(1, ...) clamps its index already : no second guard on top of it.
import("stdfaust.lib");
process = ba.tabulate(1, sin, 1024, 0, 1, hslider("x", 0.5, 0, 1, 0.001)).val;
