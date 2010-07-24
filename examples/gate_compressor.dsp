import("osc.lib");
import("filter.lib");
import("effect.lib");

process = 
// sawtooth_demo <: gate_demo : compressor_demo :> spectral_level_demo <: _,_;
   vgroup("[1]",sawtooth_demo) <:
   vgroup("[2]",gate_demo) : 
   vgroup("[3]",compressor_demo) :>
   vgroup("[4]",spectral_level_demo) <:
    _,_;
