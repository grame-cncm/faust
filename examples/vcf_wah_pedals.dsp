import("osc.lib");
import("filter.lib");
import("effect.lib");
// process = sawtooth_demo : crybaby_demo : moog_vcf_demo : wah4_demo : spectral_level_demo <: _,_;
process = 
 vgroup("[1]",sawtooth_demo) : 
 vgroup("[2]",crybaby_demo) : 
 vgroup("[3]",wah4_demo) : 
 vgroup("[4]",moog_vcf_demo) : 
 vgroup("[5]",spectral_level_demo) <:
  _,_;
