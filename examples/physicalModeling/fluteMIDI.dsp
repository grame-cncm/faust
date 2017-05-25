declare name "FluteMIDI";
declare description "Simple MIDI-controllable flute physical model with physical parameters.";
declare license "MIT";
declare copyright "(c)Romain Michon, CCRMA (Stanford University), GRAME";

import("stdfaust.lib");

process = pm.flute_ui_MIDI <: _,_;
