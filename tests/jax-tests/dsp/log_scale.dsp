// Log-scale slider regression: the init value 1000 on [100, 10000] must
// survive the normalize/unnormalize round-trip (0.5 in normalized space).
// The DSP is a generator that outputs the slider's physical value.
freq = hslider("freq[scale:log]", 1000, 100, 10000, 1);
process = freq;
