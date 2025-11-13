import("stdfaust.lib");

// Ultra-simple sawtooth - just oscillator, no filters
freq = hslider("freq", 440, 20, 20000, 1);
gain = hslider("gain", 0.5, 0, 1, 0.01);

process = os.sawtooth(freq) * gain <: _,_;
