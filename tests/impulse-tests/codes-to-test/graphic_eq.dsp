
declare name "graphic_eq";

dm = library("demo.lib");

process = 
 vgroup("[1]",dm.sawtooth_demo) :
 vgroup("[2]",dm.filterbank_demo) :
 vgroup("[3]",dm.spectral_level_demo) <:
  _,_;
