import("osc.lib");
import("filter.lib");
import("effect.lib");
//process = sawtooth_demo <: flanger_demo : phaser2_demo :> spectral_level_demo <: _,_;
process = 
 vgroup("[1]",sawtooth_demo) <:
 vgroup("[2]",flanger_demo) : 
 vgroup("[3]",phaser2_demo) :>
 vgroup("[4]",spectral_level_demo) <:
  _,_;
