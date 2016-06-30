//################################### zitaRevFDN.dsp #####################################
// Reverb demo application based on `zita_rev_fdn`.
//
// Author: JOS.
//########################################################################################
// TODO: author JOS

import("stdfaust.lib");


//==================================== GUI Declaration ===================================
//========================================================================================

fsmax = 48000.0;
fdn_group(x) = hgroup("Zita_Rev Internal FDN Reverb [tooltip: ~ Zita_Rev's internal 
	8x8 Feedback Delay Network (FDN) & Schroeder allpass-comb reverberator.  See 
	Faust's effect.lib for documentation and references]",x);
t60dc = fdn_group(vslider("[1] Low RT60 [unit:s] [style:knob][style:knob]
    [tooltip: T60 = time (in seconds) to decay 60dB in low-frequency band]",
    3, 1, 8, 0.1));
f1 = fdn_group(vslider("[2] LF X [unit:Hz] [style:knob] [scale:log]
    [tooltip: Crossover frequency (Hz) separating low and middle frequencies]",
    200, 50, 1000, 1));
t60m = fdn_group(vslider("[3] Mid RT60 [unit:s] [style:knob] [scale:log]
    [tooltip: T60 = time (in seconds) to decay 60dB in middle band]",
    2, 1, 8, 0.1));
f2 = fdn_group(vslider("[4] HF Damping [unit:Hz] [style:knob] [scale:log]
    [tooltip: Frequency (Hz) at which the high-frequency T60 is half the middle-band's T60]",
    6000, 1500, 0.49*fsmax, 1));

//============================================ DSP =======================================
//========================================================================================

process = ef.zita_rev_fdn(f1,f2,t60dc,t60m,fsmax);