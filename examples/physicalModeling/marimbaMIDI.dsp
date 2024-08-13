// WARNING: this model is incomplete and is only here for testing purposes

declare name "MarimbaMIDI";
declare description "Simple MIDI-controllable marimba physical model.";
declare license "MIT";
declare copyright "(c)Romain Michon, CCRMA (Stanford University), GRAME";

import("pkg:faust/faust/stdfaust.lib@1.0.0");

process = pm.marimba_ui_MIDI <: _,_;
