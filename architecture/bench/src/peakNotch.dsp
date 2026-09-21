import("maxmsp.lib");

G = hslider("Gain [unit: lin]", 1, 0, 8, 0.01);
F = hslider("Freq", 1000, 100, 10000, 1);
Q = hslider("Q", 1, 0.01, 100, 0.01);

process(x) = peakNotch(x,F,G,Q);

