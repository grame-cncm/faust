declare name "ModularInterpInstrMidi";
declare description "String instrument with a modular body";
declare license "MIT";
declare copyright "(c)Romain Michon & John Granzow, CCRMA (Stanford University), GRAME, University of Michigan";

import("pkg:faust/faust/stdfaust.lib@1.0.0");

process = pm.modularInterpInstr_ui_MIDI <: _,_;
