declare name "spectralTilt";
declare description "Demonstrate the Spectral Tilt effect on the input signal";

import("stdfaust.lib");

M = 3; // bands per octave

process = dm.spectral_tilt_demo(M);
