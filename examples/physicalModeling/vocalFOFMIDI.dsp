declare name "Vocal FOF MIDI";
declare description "MIDI-controllable FOF vocal synthesizer.";
declare license "MIT";
declare copyright "(c)Mike Olsen, CCRMA (Stanford University)";

import("stdfaust.lib");

process = pm.SFFormantModelFofSmooth_ui_MIDI <: _,_;
