declare name "ModularInterpInstrMidi";
declare description "String instrument with a modular body";
declare license "MIT";
declare copyright "(c)Romain Michon & John Granzow, CCRMA (Stanford University), GRAME, University of Michigan";

import("stdfaust.lib");

process = pm.modularInterpInstr_ui_MIDI <: _,_;
