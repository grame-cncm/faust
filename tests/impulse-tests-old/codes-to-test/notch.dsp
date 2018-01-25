import("maxmsp.lib");

G = hslider("Gain [unit:dB]", 0, -10, 10, 0.1);
F = hslider("Freq", 1000, 100, 10000, 1);
Q = hslider("Q", 1, 0.01, 100, 0.01);

process(x) = notch(x,F,G,Q);

