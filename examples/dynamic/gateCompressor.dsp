declare name "gateCompressor";

import("pkg:faust/faust/stdfaust.lib@1.0.0");

process =  
    vgroup("[1]", dm.sawtooth_demo) <:
    vgroup("[2]", dm.gate_demo) : 
    vgroup("[3]", dm.compressor_demo) :>
    vgroup("[4]", dm.spectral_level_demo) <:
    _,_;
