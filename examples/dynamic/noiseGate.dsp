//################################## noiseGate.dsp #######################################
// Gate demo application.
//
// Author: JOS.
//########################################################################################
// TODO: author JOS

import("stdfaust.lib");


//==================================== GUI Declaration ===================================
//========================================================================================

gate_group(x) = vgroup("GATE  [tooltip: Reference: 
	http://en.wikipedia.org/wiki/Noise_gate]", x);
meter_group(x) = gate_group(hgroup("[0]", x));
knob_group(x) = gate_group(hgroup("[1]", x));

gbp = meter_group(checkbox("[0] Bypass  [tooltip: When this is checked, 
	the gate has no effect]"));

gateview = ef.gate_gain_mono(gatethr,gateatt,gatehold,gaterel) : ba.linear2db :
     meter_group(hbargraph("[1] Gate Gain [unit:dB] [tooltip: Current gain of the 
     gate in dB]", -50,+10)); // [style:led]

gate_stereo_demo(x,y) = attach(x,gateview(abs(x)+abs(y))),y :
     ef.gate_stereo(gatethr,gateatt,gatehold,gaterel);

gatethr = knob_group(hslider("[1] Threshold [unit:dB] [style:knob] [tooltip: When 
	the signal level falls below the Threshold (expressed in dB), the signal is 
	muted]", -30, -120, 0, 0.1));

gateatt = knob_group(hslider("[2] Attack [unit:us] [style:knob] [scale:log]
     [tooltip: Time constant in MICROseconds (1/e smoothing time) for the gate 
     gain to go (exponentially) from 0 (muted) to 1 (unmuted)]",
     10, 10, 10000, 1)) : *(0.000001) : max(1.0/float(ma.SR));

gatehold = knob_group(hslider("[3] Hold [unit:ms] [style:knob] [scale:log]
     [tooltip: Time in ms to keep the gate open (no muting) after the signal 
     level falls below the Threshold]", 200, 1, 1000, 1)) : *(0.001) : 
     max(1.0/float(ma.SR));

gaterel = knob_group(hslider("[4] Release [unit:ms] [style:knob] [scale:log]
     [tooltip: Time constant in ms (1/e smoothing time) for the gain to go 
     (exponentially) from 1 (unmuted) to 0 (muted)]",
     100, 1, 1000, 1)) : *(0.001) : max(1.0/float(ma.SR));


//============================================ DSP =======================================
//========================================================================================

process = ba.bypass2(gbp,gate_stereo_demo);