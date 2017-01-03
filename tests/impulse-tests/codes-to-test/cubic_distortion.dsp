declare name 		"cubic_distortion";

ol = library("oscillator.lib");
fl = library("filter.lib");
el = library("effect.lib");

process = 
// ol.oscr_demo : el.cubicnl_demo : fl.spectral_level_demo <: _,_;
   vgroup("[1]",ol.oscr_demo) : 
   vgroup("[2]",el.cubicnl_demo) : 
   vgroup("[3]",fl.spectral_level_demo) <: _,_;
