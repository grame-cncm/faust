ol = library("oscillator.lib");
fl = library("filter.lib");
el = library("effect.lib");

// process = ol.sawtooth_demo : 
//    el.crybaby_demo : el.moog_vcf_demo : el.wah4_demo : 
//    fl.spectral_level_demo <: _,_;
process = 
 vgroup("[1]", ol.sawtooth_demo) : 
 vgroup("[2]", el.crybaby_demo) : 
 vgroup("[3]", el.wah4_demo) : 
 vgroup("[4]", el.moog_vcf_demo) : 
 vgroup("[5]", fl.spectral_level_demo) <:
  _,_;
