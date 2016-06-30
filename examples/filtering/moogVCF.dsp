//#################################### moogVCF.dsp #######################################
// Illustrate and compare all three Moog VCF implementations above.
//
// Author: JOS.
//########################################################################################
// TODO: author JOS

import("stdfaust.lib");

//==================================== GUI Declaration ===================================
//========================================================================================

mvcf_group(x) = hgroup("MOOG VCF (Voltage Controlled Filter) [tooltip: See Faust's 
	effect.lib for info and references]",x);
cb_group(x) = mvcf_group(hgroup("[0]",x));

bp = cb_group(checkbox("[0] Bypass  [tooltip: When this is checked, the Moog VCF 
	has no effect]"));
archsw = cb_group(checkbox("[1] Use Biquads [tooltip: Select moog_vcf_2b (two-biquad) 
	implementation, instead of the default moog_vcf (analog style) implementation]"));
bqsw = cb_group(checkbox("[2] Normalized Ladders [tooltip: If using biquads, make 
	them normalized ladders (moog_vcf_2bn)]"));

freq = mvcf_group(hslider("[1] Corner Frequency [unit:PK] [tooltip: The VCF resonates 
	at the corner frequency (specified in PianoKey (PK) units, with A440 = 49 PK).  
	The VCF response is flat below the corner frequency, and rolls off -24 dB per 
	octave above.]",
   	25, 1, 88, 0.01) : ba.pianokey2hz) : si.smoo;

res = mvcf_group(hslider("[2] Corner Resonance [style:knob] [tooltip: Amount of 
	resonance near VCF corner frequency (specified between 0 and 1)]", 0.9, 0, 1, 0.01));

outgain  = mvcf_group(hslider("[3] VCF Output Level [unit:dB] [style:knob] [tooltip: 
	output level in decibels]", 5, -60, 20, 0.1)) : ba.db2linear : si.smoo;

vcfbq = _ <: select2(bqsw, ef.moog_vcf_2b(res,freq), ef.moog_vcf_2bn(res,freq));
vcfarch = _ <: select2(archsw, ef.moog_vcf(res^4,freq), vcfbq);
vcf = vcfarch : *(outgain);

process = ba.bypass1(bp,vcf);