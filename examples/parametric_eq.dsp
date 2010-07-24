import("osc.lib");
import("filter.lib");
//process = sawtooth_demo : parametric_eq_demo : mth_octave_spectral_level_demo(2) <: _,_;
process =
  vgroup("[1]",sawtooth_demo) : 
  vgroup("[2]",parametric_eq_demo) : 
  vgroup("[3]", mth_octave_spectral_level_demo(2))
  <: _,_;

