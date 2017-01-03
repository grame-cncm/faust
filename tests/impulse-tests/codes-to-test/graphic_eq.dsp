
declare name 		"graphic_eq";

ol = library("oscillator.lib");
fl = library("filter.lib");

process = 
// ol.sawtooth_demo : fl.filterbank_demo : fl.spectral_level_demo <: _,_;
 vgroup("[1]",ol.sawtooth_demo) : 
 vgroup("[2]",fl.filterbank_demo) : 
 vgroup("[3]",fl.spectral_level_demo) <:
  _,_;
