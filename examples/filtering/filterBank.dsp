//################################# filterBank.dsp #######################################
// Graphic Equalizer: Each filter-bank output signal routes through a fader.
//
// Author: JOS.
//########################################################################################
// TODO: author JOS

import("stdfaust.lib");

//==================================== GUI Declaration ===================================
//========================================================================================

bp1 = ba.bypass1;
mofb_group(x) = vgroup("CONSTANT-Q FILTER BANK (Butterworth dyadic tree)
	[tooltip: See Faust's filter.lib for documentation and references]", x);
bypass_group(x) = mofb_group(hgroup("[0]", x));
slider_group(x)  = mofb_group(hgroup("[1]", x));

M = 1;
N = 10*M; // total number of bands (highpass band, octave-bands, dc band)
ftop = 10000;
mthoctavefilterbankdemo = chan;
chan = fi.mth_octave_filterbank_default(M,ftop,N) : sum(i,N,(*(ba.db2linear(fader(N-i)))));
fader(i) = slider_group(vslider("[%2i] [unit:dB] [tooltip: Bandpass filter 
	gain in dB]", -10, -70, 10, 0.1)) : si.smoo;
bp = bypass_group(checkbox("[0] Bypass 
	[tooltip: When this is checked, the filter-bank has no effect]"));

//============================================ DSP =======================================
//========================================================================================

process = bp1(bp,mthoctavefilterbankdemo);
