declare name "Vocal BandPass";
declare description "Simple source-filter vocal synthesizer.";
declare license "MIT";
declare copyright "(c)Romain Michon, CCRMA (Stanford University), GRAME";

import("pkg:faust/faust/stdfaust.lib@1.0.0");

process = pm.SFFormantModelBP_ui <: _,_;
