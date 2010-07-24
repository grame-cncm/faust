import("osc.lib");
import("filter.lib");
process = 
// sawtooth_demo : filterbank_demo : spectral_level_demo <: _,_;
 vgroup("[1]",sawtooth_demo) : 
 vgroup("[2]",filterbank_demo) : 
 vgroup("[3]",spectral_level_demo) <:
  _,_;
