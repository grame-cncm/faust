//############################### virtualAnalog.dsp ######################################
// Virtual analog oscillator demo application.
//
// Author: JOS.
//########################################################################################
// TODO: author JOS

import("stdfaust.lib");


//==================================== GUI Declaration ===================================
//========================================================================================

osc_group(x) = vgroup("[0] VIRTUAL ANALOG OSCILLATORS
	[tooltip: See Faust's oscillator.lib for documentation and references]",x);

// Signals
sawchoice = _ <:
// When MAX_SAW_ORDER is a power of 2:
par(i,ge.MAX_SAW_ORDER,ge.sawN(i+1)) : ba.selectn(int(ge.MAX_SAW_ORDER), int(saworder-1));
// When MAX_SAW_ORDER is NOT a power of 2:
// (par(i,MAX_SAW_ORDER,sawN(i+1)), par(j,MAX_SAW_ORDER_NEXTPOW2-MAX_SAW_ORDER,_))
//   : selectn(MAX_SAW_ORDER_NEXTPOW2, saworder-1);
saw = (amp/3) *
	(sawchoice(sfreq) + sawchoice(sfreq*detune1) + sawchoice(sfreq*detune2));
sq = (amp/3) *
    (ge.square(sfreq) + ge.square(sfreq*detune1) + ge.square(sfreq*detune2));
tri = (amp/3) *
    (ge.triangle(sfreq) + ge.triangle(sfreq*detune1) + ge.triangle(sfreq*detune2));
pt = (amp/3) * (ge.pulsetrain(sfreq,ptd)
                + ge.pulsetrain(sfreq*detune1,ptd)
                + ge.pulsetrain(sfreq*detune2,ptd));
ptN = (amp/3) * (ge.pulsetrainN(N,sfreq,ptd)
                + ge.pulsetrainN(N,sfreq*detune1,ptd)
                + ge.pulsetrainN(N,sfreq*detune2,ptd)) with {N=3;};
pn = amp * ge.pink_noise;

signal = ssaw*saw + ssq*sq + stri*tri
           + spt*((ssptN*ptN)+(1-ssptN)*pt)
           + spn*pn + sei*_;

// Signal controls:
signal_group(x) = osc_group(hgroup("[0] Signal Levels",x));
ssaw = signal_group(vslider("[0] Sawtooth [style:vslider]",1,0,1,0.01));

pt_group(x) = signal_group(vgroup("[1] Pulse Train",x));
ssptN = pt_group(checkbox("[0] Order 3
	[tooltip: When checked, use 3rd-order aliasing suppression (up from 2)
    See if you can hear a difference with the freq high and swept]"));
spt = pt_group(vslider("[1] [style:vslider]",0,0,1,0.01));
ptd = pt_group(vslider("[2] Duty Cycle [style:knob]",0.5,0,1,0.01))
    : si.smooth(0.99);

ssq = signal_group(vslider("[2] Square [style:vslider]",0,0,1,0.01));
stri = signal_group(vslider("[3] Triangle [style:vslider]",0,0,1,0.01));
spn = signal_group(vslider(
	"[4] Pink Noise [style:vslider][tooltip: Pink Noise (or 1/f noise) is 
	Constant-Q Noise, meaning that it has the same total power in every octave 
	(uses only amplitude controls)]",0,0,1,0.01));
sei = signal_group(vslider("[5] Ext Input [style:vslider]",0,0,1,0.01));

// Signal Parameters
knob_group(x) = osc_group(hgroup("[1] Signal Parameters", x));
af_group(x) = knob_group(vgroup("[0]", x));
ampdb = af_group(hslider("[1] Mix Amplitude [unit:dB] [style:hslider]
	[tooltip: Sawtooth waveform amplitude]",-20,-120,10,0.1));
amp = ampdb : ba.db2linear : si.smoo;
freq = af_group(hslider("[2] Frequency [unit:PK] [style:hslider] [tooltip: Sawtooth 
	frequency as a Piano Key (PK) number (A440 = key 49)]",49,1,88,0.01) : ba.pianokey2hz);
	
detune1 = 1 - 0.01 * knob_group(
	vslider("[3] Detuning 1 [unit:%%] [style:knob]
    [tooltip: Percentange frequency-shift up or down for second oscillator]",
    -0.1,-10,10,0.01));
detune2 = 1 + 0.01 * knob_group(
    vslider("[4] Detuning 2 [unit:%%] [style:knob]
    [tooltip: Percentange frequency-shift up or down for third detuned oscillator]",
    +0.1,-10,10,0.01));
portamento = knob_group(
    vslider("[5] Portamento [unit:sec] [style:knob] [scale:log]
    [tooltip: Portamento (frequency-glide) time-constant in seconds]",
    0.1,0.001,10,0.001));
saworder = knob_group(nentry("[6] Saw Order [tooltip: Order of sawtooth aliasing 
suppression]",2,1,ge.MAX_SAW_ORDER,1));
sfreq = freq : si.smooth(ba.tau2pole(portamento));


//============================================ DSP =======================================
//========================================================================================

process = signal;