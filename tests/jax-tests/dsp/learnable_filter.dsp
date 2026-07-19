import("stdfaust.lib");

// Simple lowpass filter with learnable cutoff for gradient testing
cutoff = hslider("cutoff", 1000, 20, 20000, 1) : si.smoo;
process = fi.lowpass(3, cutoff);
