//##################################### sawtoothLab.dsp ##################################
// An application demonstrating the different sawtooth oscillators of Faust.
//
// Author: JOS.
//########################################################################################
// TODO: author JOS

import("stdfaust.lib");


//==================================== GUI Declaration ===================================
//========================================================================================

osc_group(x) = vgroup("[0] SAWTOOTH OSCILLATOR [tooltip: See Faust's oscillator.lib 
	for documentation and references]",x);
knob_group(x)  = osc_group(hgroup("[1]", x));
ampdb  = knob_group(vslider("[1] Amplitude [unit:dB] [style:knob] [tooltip: Sawtooth 
	waveform amplitude]",-20,-120,10,0.1));
amp = ampdb : ba.db2linear : si.smoo;
freq = knob_group(vslider("[2] Frequency [unit:PK] [style:knob] [tooltip: Sawtooth 
	frequency as a Piano Key (PK) number (A440 = key 49)]",49,1,88,0.01) : ba.pianokey2hz);
detune1 = 1 + 0.01 * knob_group(
    vslider("[3] Detuning 1 [unit:%%] [style:knob] [tooltip: Percentange frequency-shift 
    up or down for second oscillator]",-0.1,-10,10,0.01));
detune2 = 1 + 0.01 * knob_group(vslider("[4] Detuning 2 [unit:%%] [style:knob] [tooltip: 
	Percentange frequency-shift up or down for third detuned oscillator]",+0.1,-10,10,0.01));
portamento = knob_group(vslider("[5] Portamento [unit:sec] [style:knob] [scale:log]
    [tooltip: Portamento (frequency-glide) time-constant in seconds]",0.1,0.001,10,0.001));
sfreq = freq : si.smooth(ba.tau2pole(portamento));
saworder = knob_group(nentry("[6] Saw Order [tooltip: Order of sawtootn aliasing 
	suppression]",2,1,os.MAX_SAW_ORDER,1));
sawchoice = _ <: par(i,os.MAX_SAW_ORDER,os.sawN(i+1)) : 
	ba.selectn(int(os.MAX_SAW_ORDER), int(saworder-1)); // when max is pwr of 2
tone = (amp/3) * (sawchoice(sfreq) + sawchoice(sfreq*detune1) + sawchoice(sfreq*detune2));
signal = amp * select2(ei, select2(ss, tone, white_or_pink_noise), _);
white_or_pink_noise = select2(wp,no.noise,no.pink_noise);
checkbox_group(x) = knob_group(vgroup("[7] Alternate Signals",x));
ss = checkbox_group(checkbox("[0] Noise (White or Pink - uses only Amplitude control on 
	the left)"));
wp = checkbox_group(checkbox("[1] Pink instead of White Noise (also called 1/f Noise) 
	[tooltip: Pink Noise (or 1/f noise) is Constant-Q Noise, meaning that it has the 
	same total power in every octave]"));
ei = checkbox_group(checkbox("[2] External Signal Input (overrides Sawtooth/Noise 
	selection above)"));


//============================================ DSP =======================================
//========================================================================================

process = signal;