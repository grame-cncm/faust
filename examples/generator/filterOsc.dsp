//#################################### filterOsc.dsp #####################################
// Simple application demoing filter based oscillators.
//
// Author: JOS.
//########################################################################################
// TODO: author JOS

import("stdfaust.lib");


//==================================== GUI Declaration ===================================
//========================================================================================

osc_group(x) = vgroup("[0] SINE WAVE OSCILLATOR oscrs [tooltip: Sine oscillator based 
	on 2D vector rotation]",x);
ampdb  = osc_group(hslider("[1] Amplitude [unit:dB] [tooltip: Sawtooth waveform 
	amplitude]",-20,-120,10,0.1));
amp = ampdb : ba.db2linear : si.smoo;
freq = osc_group(
	hslider("[2] Frequency [unit:PK]
    [tooltip: Sine wave frequency as a Piano Key (PK) number (A440 = 49 PK)]",
    49,1,88,0.01) : ba.pianokey2hz);
portamento = osc_group(
    hslider("[3] Portamento [unit:sec] [scale:log]
    [tooltip: Portamento (frequency-glide) time-constant in seconds]",
    0.1,0.001,10,0.001));
sfreq = freq : si.smooth(ba.tau2pole(portamento));
signal = amp * ge.oscrs(sfreq);


//============================================ DSP =======================================
//========================================================================================

process = signal;