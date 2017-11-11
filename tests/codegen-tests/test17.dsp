// example of simplification

fv = component("freeverb.dsp");

process = _,_ <: fv, fv : _, _, *(-1), *(-1) :> _,_;