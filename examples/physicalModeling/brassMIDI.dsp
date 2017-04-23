declare name "BrassMIDI";
declare description "Simple MIDI-controllable brass instrument physical model with physical parameters.";
declare license "MIT";
declare copyright "(c)Romain Michon, CCRMA (Stanford University), GRAME";

import("stdfaust.lib");

process = pm.brass_ui_MIDI <: _,_;
