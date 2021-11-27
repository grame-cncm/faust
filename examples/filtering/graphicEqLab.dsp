declare name "graphicEqLab";
declare description "Signal generators through a filter bank with spectrum analysis display";

import("stdfaust.lib");

process = 
 vgroup("[1]",dm.sawtooth_demo) : 
 vgroup("[2]",dm.filterbank_demo) : 
 vgroup("[3]",dm.spectral_level_demo) <:
  _,_;
