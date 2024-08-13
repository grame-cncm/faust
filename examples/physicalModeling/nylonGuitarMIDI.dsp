declare name "NylonGuitarMidi";
declare description "Simple acoustic guitar model with nylon strings.";
declare license "MIT";
declare copyright "(c)Romain Michon, CCRMA (Stanford University), GRAME";

import("pkg:faust/faust/stdfaust.lib@1.0.0");

process = pm.nylonGuitar_ui_MIDI <: _,_;
