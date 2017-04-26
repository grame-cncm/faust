declare name "Vocal";
declare description "Simple source-filter vocal synthesizer.";
declare license "MIT";
declare copyright "(c)Romain Michon, CCRMA (Stanford University), GRAME";

import("stdfaust.lib");

process = pm.SFFormantModel_ui <: _,_;
