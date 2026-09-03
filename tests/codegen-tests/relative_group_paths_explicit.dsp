import("stdfaust.lib");

// Explicit path form that previously worked
freq_explicit = vslider("../h:FREQ/Freq", 200, 200, 1000, 0.01);
process = hgroup("V1", os.osc(freq_explicit)), hgroup("V2", os.osc(freq_explicit));