import("stdfaust.lib");
process = vslider("gain", 1, 0, 10, 0.1) * _;

