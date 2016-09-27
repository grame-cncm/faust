declare name "filterBank";
declare version "0.0";
declare author "JOS, revised by RM";
declare description "Graphic Equalizer: Each filter-bank output signal routes through a fader.";

import("stdfaust.lib");

process = dm.filterbank_demo;