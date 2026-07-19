import("stdfaust.lib");

// Simple gain with learnable parameter for gradient testing
gain = hslider("gain", 0.5, 0, 1, 0.01);
process = _ * gain;
