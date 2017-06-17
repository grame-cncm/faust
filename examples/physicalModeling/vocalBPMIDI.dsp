declare name "Vocal BandPass MIDI";
declare description "Simple MIDI-controllable source-filter vocal synthesizer.";
declare license "MIT";
declare copyright "(c)Romain Michon, CCRMA (Stanford University), GRAME";

import("stdfaust.lib");

process = pm.SFFormantModelBP_ui_MIDI <: _,_;
