declare name "Vocal FOF";
declare description "FOF vocal synthesizer.";
declare license "MIT";
declare copyright "(c)Mike Olsen, CCRMA (Stanford University)";

import("pkg:faust/faust/stdfaust.lib@1.0.0");

process = pm.SFFormantModelFofSmooth_ui <: _,_;
