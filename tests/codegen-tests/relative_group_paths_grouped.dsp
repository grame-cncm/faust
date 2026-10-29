import("stdfaust.lib");

// Relative-group form that previously failed: group uses relative path segment
freq_grouped = hgroup("../FREQ", vslider("Freq", 200, 200, 1000, 0.01));
process = hgroup("V1", os.osc(freq_grouped)), hgroup("V2", os.osc(freq_grouped));
