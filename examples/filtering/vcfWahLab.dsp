import("stdfaust.lib");
declare description "Demonstrate competing variable-lowpass-filter effects on test signals with spectrum analysis display";

declare name "vcfWahLab";

process = 
 vgroup("[1]", dm.sawtooth_demo) : 
 vgroup("[2]", dm.crybaby_demo) : 
 vgroup("[3]", dm.wah4_demo) : 
 vgroup("[4]", dm.moog_vcf_demo) : 
 vgroup("[5]", dm.spectral_level_demo) <:
  _,_;
