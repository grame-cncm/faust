import("osc.lib");
import("filter.lib");
import("effect.lib");
process = 
// oscr_demo : cubicnl_demo : spectral_level_demo <: _,_;
   vgroup("[1]",oscr_demo) : 
   vgroup("[2]",cubicnl_demo) : 
   vgroup("[3]",spectral_level_demo) <: _,_;
