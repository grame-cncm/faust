declare name      "spcap";
declare version   "1.0";
declare author    "Grame";
declare license   "BSD";
declare copyright "(c)GRAME 2026";

import("stdfaust.lib");

// Spatialize 1 sound source on 8 speakers
process = sp.spcap_ui(8);


