declare name "GuitarMidi";
declare description "Simple acoustic guitar model with steel strings.";
declare license "MIT";
declare copyright "(c)Romain Michon, CCRMA (Stanford University), GRAME";

import("pkg:faust/faust/stdfaust.lib@1.0.0");

process = pm.guitar_ui_MIDI <: _,_;
