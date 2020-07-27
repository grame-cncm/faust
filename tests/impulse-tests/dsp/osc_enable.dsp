import("music.lib");

sig = (waveform{1, 0.5, 0, 0, 0, 0, -0.5, -1, -0.5, 0, 0, 0, 0}:!,_);

process = sig, control(osc(400), sig), enable(osc(400), sig), control(sig, sig), enable(sig, sig);
