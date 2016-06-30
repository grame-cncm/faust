//############################### parametricEqualizer.dsp ################################
// A parametric equalizer application.
//
// Author: JOS.
//########################################################################################
// TODO: author JOS

import("stdfaust.lib");

//==================================== GUI Declaration ===================================
//========================================================================================

eq_group(x) = hgroup("[0] PARAMETRIC EQ SECTIONS [tooltip: See Faust's filter.lib 
	for info and pointers]",x);
ls_group(x) = eq_group(vgroup("[1] Low Shelf",x));

LL = ls_group(hslider("[0] Low Boost|Cut [unit:dB] [style:knob]
	[tooltip: Amount of low-frequency boost or cut in decibels]",0,-40,40,0.1));
FL = ls_group(hslider("[1] Transition Frequency [unit:Hz] [style:knob] [scale:log]
	[tooltip: Transition-frequency from boost (cut) to unity gain]",200,1,5000,1));

pq_group(x) = eq_group(vgroup("[2] Peaking Equalizer[tooltip: Parametric Equalizer 
	sections from filter.lib]",x));
LP = pq_group(hslider("[0] Peak Boost|Cut [unit:dB] [style:knob][tooltip: Amount of 
	local boost or cut in decibels]",0,-40,40,0.1));
FP = pq_group(hslider("[1] Peak Frequency [unit:PK] [style:knob] [tooltip: Peak 
	Frequency in Piano Key (PK) units (A440 = 49PK)]",49,1,100,1)) : si.smooth(0.999) 
	: ba.pianokey2hz;
Q = pq_group(hslider("[2] Peak Q [style:knob] [scale:log] [tooltip: Quality factor 
	(Q) of the peak = center-frequency/bandwidth]",40,1,1000,0.1));

BP = FP/Q;

hs_group(x) = eq_group(vgroup("[3] High Shelf [tooltip: A high shelf provides a boost 
	or cut above some frequency]",x));
LH = hs_group(hslider("[0] High Boost|Cut [unit:dB] [style:knob] [tooltip: Amount of 
	high-frequency boost or cut in decibels]",0,-40,40,.1));
FH = hs_group(hslider("[1] Transition Frequency [unit:Hz] [style:knob] [scale:log]
    [tooltip: Transition-frequency from boost (cut) to unity gain]",8000,20,10000,1));


//============================================ DSP =======================================
//========================================================================================

process = fi.low_shelf(LL,FL) : fi.peak_eq(LP,FP,BP) : fi.high_shelf(LH,FH);
// Recommended: 
//       : mth_octave_spectral_level_demo(2) // half-octave spectrum analyzer