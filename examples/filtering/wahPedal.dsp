//################################### wahPedal.dsp #######################################
// Wah pedal application.
//
// Author: JOS.
//########################################################################################
// TODO: author JOS

import("stdfaust.lib");


//==================================== GUI Declaration ===================================
//========================================================================================

wah4_group(x) = hgroup("WAH4 [tooltip: Fourth-order wah effect made using moog_vcf]", x);
bp = wah4_group(checkbox("[0] Bypass [tooltip: When this is checked, the wah pedal has 
	no effect]"));
fr = wah4_group(hslider("[1] Resonance Frequency [scale:log] [tooltip: wah resonance 
	frequency in Hz]", 200,100,2000,1));
// Avoid dc with the moog_vcf (amplitude too high when freq comes up from dc)
// Also, avoid very high resonance frequencies (e.g., 5kHz or above).


//============================================ DSP =======================================
//========================================================================================

process = ba.bypass1(bp, ef.wah4(fr));