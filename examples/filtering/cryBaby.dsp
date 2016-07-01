//#################################### cryBaby.dsp #######################################
// Crybaby effect application.
//
// Author: JOS.
//########################################################################################
// TODO: author JOS

import("stdfaust.lib");


//==================================== GUI Declaration ===================================
//========================================================================================

crybaby_group(x) = hgroup("CRYBABY [tooltip: Reference: 
	https://ccrma.stanford.edu/~jos/pasp/vegf.html]", x);
bp = crybaby_group(checkbox("[0] Bypass [tooltip: When this is checked, the wah 
	pedal has no effect]"));
wah = crybaby_group(hslider("[1] Wah parameter [tooltip: wah pedal angle between 
	0 (rocked back) and 1 (rocked forward)]",0.8,0,1,0.01));


//============================================ DSP =======================================
//========================================================================================

process = ba.bypass1(bp, ve.crybaby(wah));