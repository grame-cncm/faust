import("stdfaust.lib");

// Simple synth for vmap exploration
freq = hslider("freq", 440, 20, 2000, 1);
gain = hslider("gain", 0.5, 0, 1, 0.01);
cutoff = hslider("cutoff[scale:log]", 1000, 20, 20000, 1);

synth = os.sawtooth(freq) * gain : fi.lowpass(3, cutoff);
process = synth;
