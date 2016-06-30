//################################### spectralLevel.dsp ##################################
// Demonstrate mth_octave_spectral_level in a standalone GUI.
//
// Author: JOS.
//########################################################################################
// TODO: author JOS

import("stdfaust.lib");


//==================================== GUI Declaration ===================================
//========================================================================================

M = 1.5; // 2/3 octave
ftop = 16000;
Noct = 10; // number of octaves down from ftop
// Lowest band-edge is at ftop*2^(-Noct+2) = 62.5 Hz when ftop=16 kHz:
N = int(Noct*M); // without 'int()', segmentation fault observed for M=1.67
ctl_group(x)  = hgroup("[1] SPECTRUM ANALYZER CONTROLS", x);
tau = ctl_group(hslider("[0] Level Averaging Time [unit:ms] [scale:log]
	[tooltip: band-level averaging time in milliseconds]",
    100,1,10000,1)) * 0.001; 
dB_offset = ctl_group(hslider("[1] Level dB Offset [unit:dB]
    [tooltip: Level offset in decibels]",
    50,0,100,1)); 

//============================================ DSP =======================================
//========================================================================================

process = an.mth_octave_spectral_level_default(M,ftop,N,tau,dB_offset);