// example exercising filters.lib's spectral_tilt_demo

declare name "spectralTiltLab";

import("stdfaust.lib");

N = 10; // Number of pole-zero pairs to use

process = sig(dm.sawtooth_demo) 
	 : stg(ba.bypass1(bp,dm.spectral_tilt_demo(N)))
	<: sag(dm.spectral_level_demo) 
with {
    bp = stg(checkbox("[0] Bypass Spectral Tilt"));
    stg(x) = vgroup(
     "[1] Spectral Tilt Filter [tooltip: See Faust's filters.lib for spectral_tilt_demo]",x);
    sig(x) = vgroup(
     "[2] Test Signal [tooltip: See Faust's oscillator.lib for sawtooth_demo]",x);
    sag(x) = vgroup(
     "[4] Spectrum Analyzer [tooltip: See Faust's filters.lib for spectral_level_demo]",x);
};
