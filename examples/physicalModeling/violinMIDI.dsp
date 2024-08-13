declare name "ViolinMidi";
declare description "Simple MIDI-controllable violin physical model.";
declare license "MIT";
declare copyright "(c)Romain Michon, CCRMA (Stanford University), GRAME";

import("pkg:faust/faust/stdfaust.lib@1.0.0");

process = pm.violin_ui_MIDI <: _,_;
