// WARNING: this model is incomplete and is only here for testing purposes

declare name "MarimbaMIDI";
declare description "Simple MIDI-controllable marimba physical model.";
declare license "MIT";
declare copyright "(c)Romain Michon, CCRMA (Stanford University), GRAME";

import("stdfaust.lib");

process = pm.marimba_ui_MIDI <: _,_;
