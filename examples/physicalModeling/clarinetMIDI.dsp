declare name "ClarinetMIDI";
declare description "Simple MIDI-controllable clarinet physical model with physical parameters.";
declare license "MIT";
declare copyright "(c)Romain Michon, CCRMA (Stanford University), GRAME";

import("pkg:faust/faust/stdfaust.lib@1.0.0");

process = pm.clarinet_ui_MIDI <: _,_;
