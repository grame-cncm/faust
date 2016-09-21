declare name "gateCompressor";

import("stdfaust.lib");

process = 
// ol.sawtooth_demo <: 
//      el.gate_demo : ef.compressor_demo :> fi.spectral_level_demo <: _,_;
   vgroup("[1]", dm.sawtooth_demo) <:
   vgroup("[2]", dm.gate_demo) : 
   vgroup("[3]", dm.compressor_demo) :>
   vgroup("[4]", dm.spectral_level_demo) <:
    _,_;
