declare name "DjembeMIDI";
declare description "Simple MIDI-controllable djembe physical model.";
declare license "MIT";
declare copyright "(c)Romain Michon, CCRMA (Stanford University), GRAME";

import("stdfaust.lib");

process = pm.djembe_ui_MIDI <: _,_;
