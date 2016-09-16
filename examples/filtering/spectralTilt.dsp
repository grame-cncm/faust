declare name "Spectral Tilt";
declare version "0.0";
declare author "JOS, revised by RM";
declare description "A spectral tilt application";

import("stdfaust.lib");

O = 2; // filter order

process = dm.spectral_tilt_demo(2);