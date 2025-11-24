import("stdfaust.lib");

// Regression for relative group labels: both oscillators must share the same "Freq" slider.
freq = hgroup("../FREQ", vslider("Freq", 200, 200, 1000, 0.01));

process = hgroup("V1", os.osc(freq)), hgroup("V2", os.osc(freq));
