declare name "cubic_distortion";

dm = library("demo.lib");

process = 
// ol.oscr_demo : el.cubicnl_demo : fl.spectral_level_demo <: _,_;
   vgroup("[1]",dm.oscr_demo) :
   vgroup("[2]",dm.cubicnl_demo) :
   vgroup("[3]",dm.spectral_level_demo) <: _,_;
