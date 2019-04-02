declare name 		"gate_compressor";

ol = library("oscillator.lib");
el = library("effect.lib");
fl = library("filter.lib");

process = 
// ol.sawtooth_demo <: 
//      el.gate_demo : el.compressor_demo :> fl.spectral_level_demo <: _,_;
   vgroup("[1]sawtooth", ol.sawtooth_demo) <:
   vgroup("[2]gate", el.gate_demo) : 
   vgroup("[3]compressor", el.compressor_demo) :>
   vgroup("[4]spectral", fl.spectral_level_demo) <:
    _,_;
