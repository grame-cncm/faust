declare name "parametricEqLab";
declare description "Demonstrate the Parametric Equalizer sections on test signals with spectrum analysis display";

import("stdfaust.lib");

process =
  vgroup("[1]", dm.sawtooth_demo) :
  vgroup("[2]", dm.parametric_eq_demo) :
  vgroup("[3]", dm.mth_octave_spectral_level_demo(2))
  <: _,_;
