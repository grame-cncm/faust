ol = library("oscillator.lib");
fl = library("filter.lib");

//process = ol.sawtooth_demo : fl.parametric_eq_demo : 
//          fl.mth_octave_spectral_level_demo(2) <: _,_;
process =
  vgroup("[1]", ol.sawtooth_demo) : 
  vgroup("[2]", fl.parametric_eq_demo) : 
  vgroup("[3]", fl.mth_octave_spectral_level_demo(2))
  <: _,_;

