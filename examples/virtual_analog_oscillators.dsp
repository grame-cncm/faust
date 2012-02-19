ol = library("oscillator.lib");
fl = library("filter.lib");
el = library("effect.lib");

process = 
 vgroup("[1]", ol.virtual_analog_oscillator_demo) : 
 vgroup("[2]", el.moog_vcf_demo) : 
 vgroup("[3]", fl.spectral_level_demo) <:
  _,_;
