declare name "ElecGuitarMidi";
declare description "Simple electric guitar model without effect chain.";
declare license "MIT";
declare copyright "(c)Romain Michon, CCRMA (Stanford University), GRAME";

import("pkg:faust/faust/stdfaust.lib@1.0.0");

// TODO: We could potentially add an audio effect chain here

process = pm.elecGuitar_ui_MIDI <: _,_;
