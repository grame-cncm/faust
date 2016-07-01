//################################### freeverb.dsp #######################################
// Freeverb demo application.
//
// Author: ROM.
//########################################################################################
// TODO: author ROM

import("stdfaust.lib");


//==================================== GUI Declaration ===================================
//========================================================================================

scaleroom   = 0.28;
offsetroom  = 0.7;
allpassfeed = 0.5;
scaledamp   = 0.4;
fixedgain   = 0.1;
origSR = 44100;

parameters(x) = hgroup("Freeverb",x);
knobGroup(x) = parameters(vgroup("[0]",x));
damping = knobGroup(vslider("[0] Damp [style: knob] [tooltip: Somehow control the 
	density of the reverb.]",0.5, 0, 1, 0.025)*scaledamp*origSR/ma.SR);
combfeed = knobGroup(vslider("[1] RoomSize [style: knob] [tooltip: The room size 
	between 0 and 1 with 1 for the largest room.]", 0.5, 0, 1, 0.025)*scaleroom*
	origSR/ma.SR + offsetroom);
spatSpread = knobGroup(vslider("[2] Stereo Spread [style: knob] [tooltip: Spatial 
	spread between 0 and 1 with 1 for maximum spread.]",0.5,0,1,0.01)*46*ma.SR/origSR 
	: int);
g = parameters(vslider("[1] Wet [tooltip: The amount of reverb applied to the signal 
	between 0 and 1 with 1 for the maximum amount of reverb.]", 0.3333, 0, 1, 0.025));


//============================================ DSP =======================================
//========================================================================================

process = _,_ <: (*(g)*fixedgain,*(g)*fixedgain : 
	re.stereo_freeverb(combfeed, allpassfeed, damping, spatSpread)), 
	*(1-g), *(1-g) :> _,_ ;