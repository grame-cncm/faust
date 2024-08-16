declare name "spectralTilt";
declare description "Demonstrate the Spectral Tilt effect on test signals";

import("pkg:faust/faust/stdfaust.lib@1.0.0");

O = 2; // filter order

process = dm.spectral_tilt_demo(2);
