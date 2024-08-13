declare name "Vocal FOF MIDI";
declare description "MIDI-controllable FOF vocal synthesizer.";
declare license "MIT";
declare copyright "(c)Mike Olsen, CCRMA (Stanford University)";

import("pkg:faust/faust/stdfaust.lib@1.0.0");

process = pm.SFFormantModelFofSmooth_ui_MIDI <: _,_;
