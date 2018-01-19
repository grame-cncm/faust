// example exercising filter.lib's spectral_tilt_demo

N = 10; // Number of pole-zero pairs to use

process = sig(ol.sawtooth_demo) 
	 : stg(el.bypass1(bp,fl.spectral_tilt_demo(N)))
	<: sag(fl.spectral_level_demo) 
with {
    fl = library("filter.lib");
    ol = library("oscillator.lib");
    el = library("effect.lib");
    bp = stg(checkbox("[0] Bypass Spectral Tilt"));
    stg(x) = vgroup(
     "[1] Spectral Tilt Filter [tooltip: See Faust's filter.lib for spectral_tilt_demo]",x);
    sig(x) = vgroup(
     "[2] Test Signal [tooltip: See Faust's oscillator.lib for sawtooth_demo]",x);
    sag(x) = vgroup(
     "[4] Spectrum Analyzer [tooltip: See Faust's filter.lib for spectral_level_demo]",x);
};
