
declare name  "Noise";
declare copyright "(c)GRAME 2018";

import("stdfaust.lib");

// noise level controlled by a slider
process = no.noise * hslider("gain",0,0,1, 0.1);

