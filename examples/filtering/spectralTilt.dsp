declare name "spectralTilt";
declare description "Demonstrate the Spectral Tilt effect on test signals";

import("stdfaust.lib");

O = 2; // filter order

process = dm.spectral_tilt_demo(2);
