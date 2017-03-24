import("stdfaust.lib");
declare description "Demonstrate competing variable-lowpass-filter effects on test signals with spectrum analysis display";

declare name "vcfWahLab";

// process = ol.sawtooth_demo : 
//    el.crybaby_demo : el.moog_vcf_demo : el.wah4_demo : 
//    fl.spectral_level_demo <: _,_;
process = 
 vgroup("[1]", dm.sawtooth_demo) : 
 vgroup("[2]", dm.crybaby_demo) : 
 vgroup("[3]", dm.wah4_demo) : 
 vgroup("[4]", dm.moog_vcf_demo) : 
 vgroup("[5]", dm.spectral_level_demo) <:
  _,_;
