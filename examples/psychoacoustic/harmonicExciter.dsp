//################################## harmonicExciter.dsp #################################
// Psychoacoustic harmonic exciter, with GUI.
//
// Author: Priyanka Shekar (pshekar@ccrma.stanford.edu).
//########################################################################################

declare exciter_name "Harmonic Exciter";
declare exciter_author "Priyanka Shekar (pshekar@ccrma.stanford.edu)";
declare exciter_copyright "Copyright (c) 2013 Priyanka Shekar";
declare exciter_version "1.0";
declare exciter_license "MIT License (MIT)";

import("stdfaust.lib");


// TODO: not really sure why this doesn't use the standard compressor from compressor.lib:
// needs to be investigated
compressor = ba.bypass1(cbp,compressorMono) 
with{
	comp_group(x) = vgroup("COMPRESSOR  [tooltip: Reference: 
		http://en.wikipedia.org/wiki/Dynamic_range_compression]", x);

    meter_group(x)  = comp_group(hgroup("[0]", x));
    knob_group(x)  = comp_group(hgroup("[1]", x));

    cbp = meter_group(checkbox("[0] Bypass  [tooltip: When this is checked, 
    	the compressor has no effect]"));

    gainview = co.compression_gain_mono(ratio,threshold,attack,release) : ba.linear2db 
    	: meter_group(hbargraph("[1] Compressor Gain [unit:dB] [tooltip: Current gain 
    	of the compressor in dB]",-50,+10));

    displaygain = _ <: _,abs : _,gainview : attach;

    compressorMono = displaygain(co.compressor_mono(ratio,threshold,attack,release));

    ctl_group(x)  = knob_group(hgroup("[3] Compression Control", x));

    ratio = ctl_group(hslider("[0] Ratio [style:knob]  [tooltip: A compression Ratio 
    of N means that for each N dB increase in input signal level above Threshold, the 
    output level goes up 1 dB]", 5, 1, 20, 0.1));

    threshold = ctl_group(hslider("[1] Threshold [unit:dB] [style:knob] [tooltip: 
    When the signal level exceeds the Threshold (in dB), its level is compressed 
    according to the Ratio]", -30, -100, 10, 0.1));

    env_group(x)  = knob_group(hgroup("[4] Compression Response", x));

    attack = env_group(hslider("[1] Attack [unit:ms] [style:knob]  [tooltip: 
    Time constant in ms (1/e smoothing time) for the compression gain to approach 
    (exponentially) a new lower target level (the compression `kicking in')]",
    50, 0, 500, 0.1)) : *(0.001) : max(1/ma.SR);

    release = env_group(hslider("[2] Release [unit:ms] [style: knob]  [tooltip: 
    Time constant in ms (1/e smoothing time) for the compression gain to approach 
    (exponentially) a new higher target level (the compression 'releasing')]",
    500, 0, 1000, 0.1)) : *(0.001) : max(1/ma.SR);
};

//Exciter GUI controls
ex_group(x) = hgroup("EXCITER  [tooltip: Reference: Patent US4150253 A]", x);

//Highpass - selectable cutoff frequency
fc = ex_group(hslider("[0] Cutoff Frequency [unit:Hz] [style:knob] [scale:log]
	[tooltip: Cutoff frequency for highpassed components to be excited]",
    5000, 1000, 10000, 100));
  
//Pre-distortion gain - selectable percentage of harmonics
ph = ex_group(hslider("[1] Harmonics [unit:percent] [style:knob] [tooltip: 
Percentage of harmonics generated]", 20, 0, 200, 1)) / 100;
pregain = * (ph);
  
// TODO: same thing: why doesn't this use cubicnl?
//Asymmetric cubic soft clipper
harmonicCreator(x) = x <: cubDist1, cubDist2, cubDist3 :> _;
cubDist1(x) = (x < 0) * x;
cubDist2(x) = (x >= 0) * (x <= 1) * (x - x ^ 3 / 3);
cubDist3(x) = (x > 1) * 2/3;

//Post-distortion gain - undoes effect of pre-gain
postgain = * (1/ph);

//Balance - selectable dry/wet mix
ml = ex_group(hslider("[2] Mix [style:knob] [tooltip: Dry/Wet mix of original signal 
to excited signal]", 0.50, 0.00, 1.00, 0.01));
balance = (_ * ml), (_ * (1.0 - ml)) :> _;

process = _ <: (fi.highpass(2, fc) : compressor : pregain : harmonicCreator : 
	postgain), _ : balance;

