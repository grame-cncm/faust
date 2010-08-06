ol = library("osc.lib");
fl = library("filter.lib");
el = library("effect.lib");

//process = ol.sawtooth_demo <: 
//  el.flanger_demo : el.phaser2_demo :> fl.spectral_level_demo <: _,_;
process = 
 vgroup("[1]", ol.sawtooth_demo) <:
 vgroup("[2]", el.flanger_demo) : 
 vgroup("[3]", el.phaser2_demo) :>
 vgroup("[4]", fl.spectral_level_demo) <:
  _,_;
