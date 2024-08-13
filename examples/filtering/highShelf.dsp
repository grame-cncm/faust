// WARNING: This a "legacy example based on a deprecated library". Check filters.lib
// for more accurate examples of filter functions

declare name "highShelf";

import("pkg:faust/faust/maxmsp.lib@1.1.0");

G = hslider("Gain [unit:dB]", 0, -10, 10, 0.1);
F = hslider("Freq", 1000, 100, 10000, 1);
Q = hslider("Q", 1, 0.01, 100, 0.01);

process(x) = highShelf(x,F,G,Q);

