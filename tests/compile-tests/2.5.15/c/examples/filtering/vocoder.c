/* ------------------------------------------------------------
author: "RM"
name: "Vocoder"
version: "0.0"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: c, -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__


typedef struct Soundfile Soundfile;

#include "gui/CInterface.h"

#ifndef max
// define min and max (the result doesn't matter)
#define max(a,b) (a)
#define min(a,b) (b)
#endif

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 


#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
#include <stdlib.h>

static float mydsp_faustpower2_f(float value) {
	return (value * value);
	
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif
#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

typedef struct {
	
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fVslider0;
	float fRec1[2];
	float fConst3;
	FAUSTFLOAT fHslider1;
	float fVec0[2];
	float fRec2[2];
	float fConst4;
	float fRec0[3];
	float fRec5[3];
	float fConst5;
	float fConst6;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	float fRec4[2];
	float fRec3[2];
	float fConst7;
	float fConst8;
	float fConst9;
	float fRec6[3];
	float fRec9[3];
	float fConst10;
	float fRec8[2];
	float fRec7[2];
	float fConst11;
	float fConst12;
	float fConst13;
	float fRec10[3];
	float fRec13[3];
	float fConst14;
	float fRec12[2];
	float fRec11[2];
	float fConst15;
	float fConst16;
	float fConst17;
	float fRec14[3];
	float fRec17[3];
	float fConst18;
	float fRec16[2];
	float fRec15[2];
	float fConst19;
	float fConst20;
	float fConst21;
	float fRec18[3];
	float fRec21[3];
	float fConst22;
	float fRec20[2];
	float fRec19[2];
	float fConst23;
	float fConst24;
	float fConst25;
	float fRec22[3];
	float fRec25[3];
	float fConst26;
	float fRec24[2];
	float fRec23[2];
	float fConst27;
	float fConst28;
	float fConst29;
	float fRec26[3];
	float fRec29[3];
	float fConst30;
	float fRec28[2];
	float fRec27[2];
	float fConst31;
	float fConst32;
	float fConst33;
	float fRec30[3];
	float fRec33[3];
	float fConst34;
	float fRec32[2];
	float fRec31[2];
	float fConst35;
	float fConst36;
	float fConst37;
	float fRec34[3];
	float fRec37[3];
	float fConst38;
	float fRec36[2];
	float fRec35[2];
	float fConst39;
	float fConst40;
	float fConst41;
	float fRec38[3];
	float fRec41[3];
	float fConst42;
	float fRec40[2];
	float fRec39[2];
	float fConst43;
	float fConst44;
	float fConst45;
	float fRec42[3];
	float fRec45[3];
	float fConst46;
	float fRec44[2];
	float fRec43[2];
	float fConst47;
	float fConst48;
	float fConst49;
	float fRec46[3];
	float fRec49[3];
	float fConst50;
	float fRec48[2];
	float fRec47[2];
	float fConst51;
	float fConst52;
	float fConst53;
	float fRec50[3];
	float fRec53[3];
	float fConst54;
	float fRec52[2];
	float fRec51[2];
	float fConst55;
	float fConst56;
	float fConst57;
	float fRec54[3];
	float fRec57[3];
	float fConst58;
	float fRec56[2];
	float fRec55[2];
	float fConst59;
	float fConst60;
	float fConst61;
	float fRec58[3];
	float fRec61[3];
	float fConst62;
	float fRec60[2];
	float fRec59[2];
	float fConst63;
	float fConst64;
	float fConst65;
	float fRec62[3];
	float fRec65[3];
	float fConst66;
	float fRec64[2];
	float fRec63[2];
	float fConst67;
	float fConst68;
	float fConst69;
	float fRec66[3];
	float fRec69[3];
	float fConst70;
	float fRec68[2];
	float fRec67[2];
	float fConst71;
	float fConst72;
	float fConst73;
	float fRec70[3];
	float fRec73[3];
	float fConst74;
	float fRec72[2];
	float fRec71[2];
	float fConst75;
	float fConst76;
	float fConst77;
	float fRec74[3];
	float fRec77[3];
	float fConst78;
	float fRec76[2];
	float fRec75[2];
	float fConst79;
	float fConst80;
	float fConst81;
	float fRec78[3];
	float fRec81[3];
	float fConst82;
	float fRec80[2];
	float fRec79[2];
	float fConst83;
	float fConst84;
	float fConst85;
	float fRec82[3];
	float fRec85[3];
	float fConst86;
	float fRec84[2];
	float fRec83[2];
	float fConst87;
	float fConst88;
	float fConst89;
	float fRec86[3];
	float fRec89[3];
	float fConst90;
	float fRec88[2];
	float fRec87[2];
	float fConst91;
	float fConst92;
	float fConst93;
	float fRec90[3];
	float fRec93[3];
	float fConst94;
	float fRec92[2];
	float fRec91[2];
	float fConst95;
	float fConst96;
	float fConst97;
	float fRec94[3];
	float fRec97[3];
	float fConst98;
	float fRec96[2];
	float fRec95[2];
	float fConst99;
	float fConst100;
	float fConst101;
	float fRec98[3];
	float fRec101[3];
	float fConst102;
	float fRec100[2];
	float fRec99[2];
	float fConst103;
	float fConst104;
	float fConst105;
	float fRec102[3];
	float fRec105[3];
	float fConst106;
	float fRec104[2];
	float fRec103[2];
	float fConst107;
	float fConst108;
	float fConst109;
	float fRec106[3];
	float fRec109[3];
	float fConst110;
	float fRec108[2];
	float fRec107[2];
	float fConst111;
	float fConst112;
	float fConst113;
	float fRec110[3];
	float fRec113[3];
	float fConst114;
	float fRec112[2];
	float fRec111[2];
	float fConst115;
	float fConst116;
	float fConst117;
	float fRec114[3];
	float fRec117[3];
	float fConst118;
	float fRec116[2];
	float fRec115[2];
	float fConst119;
	float fConst120;
	float fConst121;
	float fRec118[3];
	float fRec121[3];
	float fConst122;
	float fRec120[2];
	float fRec119[2];
	float fConst123;
	float fConst124;
	float fConst125;
	float fRec122[3];
	float fRec125[3];
	float fConst126;
	float fRec124[2];
	float fRec123[2];
	float fConst127;
	float fConst128;
	float fConst129;
	float fRec126[3];
	float fRec129[3];
	float fConst130;
	float fRec128[2];
	float fRec127[2];
	
} mydsp;

mydsp* newmydsp() { 
	mydsp* dsp = (mydsp*)malloc(sizeof(mydsp));
	return dsp;
}

void deletemydsp(mydsp* dsp) { 
	free(dsp);
}

void metadatamydsp(MetaGlue* m) { 
	m->declare(m->metaInterface, "analyzers.lib/name", "Faust Analyzer Library");
	m->declare(m->metaInterface, "analyzers.lib/version", "0.0");
	m->declare(m->metaInterface, "author", "RM");
	m->declare(m->metaInterface, "basics.lib/name", "Faust Basic Element Library");
	m->declare(m->metaInterface, "basics.lib/version", "0.0");
	m->declare(m->metaInterface, "description", "Use example of the vocoder function where an impulse train is used as excitation.");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "Vocoder");
	m->declare(m->metaInterface, "oscillators.lib/name", "Faust Oscillator Library");
	m->declare(m->metaInterface, "oscillators.lib/version", "0.0");
	m->declare(m->metaInterface, "signals.lib/name", "Faust Signal Routing Library");
	m->declare(m->metaInterface, "signals.lib/version", "0.0");
	m->declare(m->metaInterface, "vaeffects.lib/name", "Faust Virtual Analog Filter Effect Library");
	m->declare(m->metaInterface, "vaeffects.lib/version", "0.0");
	m->declare(m->metaInterface, "version", "0.0");
}

int getSampleRatemydsp(mydsp* dsp) { return dsp->fSamplingFreq; }

int getNumInputsmydsp(mydsp* dsp) {
	return 1;
	
}
int getNumOutputsmydsp(mydsp* dsp) {
	return 2;
	
}
int getInputRatemydsp(mydsp* dsp, int channel) {
	int rate;
	switch (channel) {
		case 0: {
			rate = 1;
			break;
		}
		default: {
			rate = -1;
			break;
		}
		
	}
	return rate;
	
}
int getOutputRatemydsp(mydsp* dsp, int channel) {
	int rate;
	switch (channel) {
		case 0: {
			rate = 1;
			break;
		}
		case 1: {
			rate = 1;
			break;
		}
		default: {
			rate = -1;
			break;
		}
		
	}
	return rate;
	
}

void classInitmydsp(int samplingFreq) {
	
}

void instanceResetUserInterfacemydsp(mydsp* dsp) {
	dsp->fHslider0 = (FAUSTFLOAT)0.5f;
	dsp->fVslider0 = (FAUSTFLOAT)0.5f;
	dsp->fHslider1 = (FAUSTFLOAT)330.0f;
	dsp->fHslider2 = (FAUSTFLOAT)5.0f;
	dsp->fHslider3 = (FAUSTFLOAT)5.0f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			dsp->fRec1[l0] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			dsp->fVec0[l1] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			dsp->fRec2[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 3); l3 = (l3 + 1)) {
			dsp->fRec0[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 3); l4 = (l4 + 1)) {
			dsp->fRec5[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			dsp->fRec4[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			dsp->fRec3[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			dsp->fRec6[l7] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
			dsp->fRec9[l8] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			dsp->fRec8[l9] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			dsp->fRec7[l10] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 3); l11 = (l11 + 1)) {
			dsp->fRec10[l11] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 3); l12 = (l12 + 1)) {
			dsp->fRec13[l12] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l13;
		for (l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			dsp->fRec12[l13] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l14;
		for (l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			dsp->fRec11[l14] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l15;
		for (l15 = 0; (l15 < 3); l15 = (l15 + 1)) {
			dsp->fRec14[l15] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l16;
		for (l16 = 0; (l16 < 3); l16 = (l16 + 1)) {
			dsp->fRec17[l16] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l17;
		for (l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			dsp->fRec16[l17] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l18;
		for (l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			dsp->fRec15[l18] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l19;
		for (l19 = 0; (l19 < 3); l19 = (l19 + 1)) {
			dsp->fRec18[l19] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l20;
		for (l20 = 0; (l20 < 3); l20 = (l20 + 1)) {
			dsp->fRec21[l20] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l21;
		for (l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			dsp->fRec20[l21] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l22;
		for (l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			dsp->fRec19[l22] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l23;
		for (l23 = 0; (l23 < 3); l23 = (l23 + 1)) {
			dsp->fRec22[l23] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l24;
		for (l24 = 0; (l24 < 3); l24 = (l24 + 1)) {
			dsp->fRec25[l24] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l25;
		for (l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			dsp->fRec24[l25] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l26;
		for (l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			dsp->fRec23[l26] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l27;
		for (l27 = 0; (l27 < 3); l27 = (l27 + 1)) {
			dsp->fRec26[l27] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l28;
		for (l28 = 0; (l28 < 3); l28 = (l28 + 1)) {
			dsp->fRec29[l28] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l29;
		for (l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			dsp->fRec28[l29] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l30;
		for (l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			dsp->fRec27[l30] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l31;
		for (l31 = 0; (l31 < 3); l31 = (l31 + 1)) {
			dsp->fRec30[l31] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l32;
		for (l32 = 0; (l32 < 3); l32 = (l32 + 1)) {
			dsp->fRec33[l32] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l33;
		for (l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			dsp->fRec32[l33] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l34;
		for (l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			dsp->fRec31[l34] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l35;
		for (l35 = 0; (l35 < 3); l35 = (l35 + 1)) {
			dsp->fRec34[l35] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l36;
		for (l36 = 0; (l36 < 3); l36 = (l36 + 1)) {
			dsp->fRec37[l36] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l37;
		for (l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			dsp->fRec36[l37] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l38;
		for (l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			dsp->fRec35[l38] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l39;
		for (l39 = 0; (l39 < 3); l39 = (l39 + 1)) {
			dsp->fRec38[l39] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l40;
		for (l40 = 0; (l40 < 3); l40 = (l40 + 1)) {
			dsp->fRec41[l40] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l41;
		for (l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			dsp->fRec40[l41] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l42;
		for (l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			dsp->fRec39[l42] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l43;
		for (l43 = 0; (l43 < 3); l43 = (l43 + 1)) {
			dsp->fRec42[l43] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l44;
		for (l44 = 0; (l44 < 3); l44 = (l44 + 1)) {
			dsp->fRec45[l44] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l45;
		for (l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			dsp->fRec44[l45] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l46;
		for (l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			dsp->fRec43[l46] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l47;
		for (l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			dsp->fRec46[l47] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l48;
		for (l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			dsp->fRec49[l48] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l49;
		for (l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			dsp->fRec48[l49] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l50;
		for (l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			dsp->fRec47[l50] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l51;
		for (l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			dsp->fRec50[l51] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l52;
		for (l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			dsp->fRec53[l52] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l53;
		for (l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			dsp->fRec52[l53] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l54;
		for (l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
			dsp->fRec51[l54] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l55;
		for (l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			dsp->fRec54[l55] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l56;
		for (l56 = 0; (l56 < 3); l56 = (l56 + 1)) {
			dsp->fRec57[l56] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l57;
		for (l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			dsp->fRec56[l57] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l58;
		for (l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			dsp->fRec55[l58] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l59;
		for (l59 = 0; (l59 < 3); l59 = (l59 + 1)) {
			dsp->fRec58[l59] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l60;
		for (l60 = 0; (l60 < 3); l60 = (l60 + 1)) {
			dsp->fRec61[l60] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l61;
		for (l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			dsp->fRec60[l61] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l62;
		for (l62 = 0; (l62 < 2); l62 = (l62 + 1)) {
			dsp->fRec59[l62] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l63;
		for (l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			dsp->fRec62[l63] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l64;
		for (l64 = 0; (l64 < 3); l64 = (l64 + 1)) {
			dsp->fRec65[l64] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l65;
		for (l65 = 0; (l65 < 2); l65 = (l65 + 1)) {
			dsp->fRec64[l65] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l66;
		for (l66 = 0; (l66 < 2); l66 = (l66 + 1)) {
			dsp->fRec63[l66] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l67;
		for (l67 = 0; (l67 < 3); l67 = (l67 + 1)) {
			dsp->fRec66[l67] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l68;
		for (l68 = 0; (l68 < 3); l68 = (l68 + 1)) {
			dsp->fRec69[l68] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l69;
		for (l69 = 0; (l69 < 2); l69 = (l69 + 1)) {
			dsp->fRec68[l69] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l70;
		for (l70 = 0; (l70 < 2); l70 = (l70 + 1)) {
			dsp->fRec67[l70] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l71;
		for (l71 = 0; (l71 < 3); l71 = (l71 + 1)) {
			dsp->fRec70[l71] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l72;
		for (l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			dsp->fRec73[l72] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l73;
		for (l73 = 0; (l73 < 2); l73 = (l73 + 1)) {
			dsp->fRec72[l73] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l74;
		for (l74 = 0; (l74 < 2); l74 = (l74 + 1)) {
			dsp->fRec71[l74] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l75;
		for (l75 = 0; (l75 < 3); l75 = (l75 + 1)) {
			dsp->fRec74[l75] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l76;
		for (l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			dsp->fRec77[l76] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l77;
		for (l77 = 0; (l77 < 2); l77 = (l77 + 1)) {
			dsp->fRec76[l77] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l78;
		for (l78 = 0; (l78 < 2); l78 = (l78 + 1)) {
			dsp->fRec75[l78] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l79;
		for (l79 = 0; (l79 < 3); l79 = (l79 + 1)) {
			dsp->fRec78[l79] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l80;
		for (l80 = 0; (l80 < 3); l80 = (l80 + 1)) {
			dsp->fRec81[l80] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l81;
		for (l81 = 0; (l81 < 2); l81 = (l81 + 1)) {
			dsp->fRec80[l81] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l82;
		for (l82 = 0; (l82 < 2); l82 = (l82 + 1)) {
			dsp->fRec79[l82] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l83;
		for (l83 = 0; (l83 < 3); l83 = (l83 + 1)) {
			dsp->fRec82[l83] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l84;
		for (l84 = 0; (l84 < 3); l84 = (l84 + 1)) {
			dsp->fRec85[l84] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l85;
		for (l85 = 0; (l85 < 2); l85 = (l85 + 1)) {
			dsp->fRec84[l85] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l86;
		for (l86 = 0; (l86 < 2); l86 = (l86 + 1)) {
			dsp->fRec83[l86] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l87;
		for (l87 = 0; (l87 < 3); l87 = (l87 + 1)) {
			dsp->fRec86[l87] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l88;
		for (l88 = 0; (l88 < 3); l88 = (l88 + 1)) {
			dsp->fRec89[l88] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l89;
		for (l89 = 0; (l89 < 2); l89 = (l89 + 1)) {
			dsp->fRec88[l89] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l90;
		for (l90 = 0; (l90 < 2); l90 = (l90 + 1)) {
			dsp->fRec87[l90] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l91;
		for (l91 = 0; (l91 < 3); l91 = (l91 + 1)) {
			dsp->fRec90[l91] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l92;
		for (l92 = 0; (l92 < 3); l92 = (l92 + 1)) {
			dsp->fRec93[l92] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l93;
		for (l93 = 0; (l93 < 2); l93 = (l93 + 1)) {
			dsp->fRec92[l93] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l94;
		for (l94 = 0; (l94 < 2); l94 = (l94 + 1)) {
			dsp->fRec91[l94] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l95;
		for (l95 = 0; (l95 < 3); l95 = (l95 + 1)) {
			dsp->fRec94[l95] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l96;
		for (l96 = 0; (l96 < 3); l96 = (l96 + 1)) {
			dsp->fRec97[l96] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l97;
		for (l97 = 0; (l97 < 2); l97 = (l97 + 1)) {
			dsp->fRec96[l97] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l98;
		for (l98 = 0; (l98 < 2); l98 = (l98 + 1)) {
			dsp->fRec95[l98] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l99;
		for (l99 = 0; (l99 < 3); l99 = (l99 + 1)) {
			dsp->fRec98[l99] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l100;
		for (l100 = 0; (l100 < 3); l100 = (l100 + 1)) {
			dsp->fRec101[l100] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l101;
		for (l101 = 0; (l101 < 2); l101 = (l101 + 1)) {
			dsp->fRec100[l101] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l102;
		for (l102 = 0; (l102 < 2); l102 = (l102 + 1)) {
			dsp->fRec99[l102] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l103;
		for (l103 = 0; (l103 < 3); l103 = (l103 + 1)) {
			dsp->fRec102[l103] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l104;
		for (l104 = 0; (l104 < 3); l104 = (l104 + 1)) {
			dsp->fRec105[l104] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l105;
		for (l105 = 0; (l105 < 2); l105 = (l105 + 1)) {
			dsp->fRec104[l105] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l106;
		for (l106 = 0; (l106 < 2); l106 = (l106 + 1)) {
			dsp->fRec103[l106] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l107;
		for (l107 = 0; (l107 < 3); l107 = (l107 + 1)) {
			dsp->fRec106[l107] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l108;
		for (l108 = 0; (l108 < 3); l108 = (l108 + 1)) {
			dsp->fRec109[l108] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l109;
		for (l109 = 0; (l109 < 2); l109 = (l109 + 1)) {
			dsp->fRec108[l109] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l110;
		for (l110 = 0; (l110 < 2); l110 = (l110 + 1)) {
			dsp->fRec107[l110] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l111;
		for (l111 = 0; (l111 < 3); l111 = (l111 + 1)) {
			dsp->fRec110[l111] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l112;
		for (l112 = 0; (l112 < 3); l112 = (l112 + 1)) {
			dsp->fRec113[l112] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l113;
		for (l113 = 0; (l113 < 2); l113 = (l113 + 1)) {
			dsp->fRec112[l113] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l114;
		for (l114 = 0; (l114 < 2); l114 = (l114 + 1)) {
			dsp->fRec111[l114] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l115;
		for (l115 = 0; (l115 < 3); l115 = (l115 + 1)) {
			dsp->fRec114[l115] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l116;
		for (l116 = 0; (l116 < 3); l116 = (l116 + 1)) {
			dsp->fRec117[l116] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l117;
		for (l117 = 0; (l117 < 2); l117 = (l117 + 1)) {
			dsp->fRec116[l117] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l118;
		for (l118 = 0; (l118 < 2); l118 = (l118 + 1)) {
			dsp->fRec115[l118] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l119;
		for (l119 = 0; (l119 < 3); l119 = (l119 + 1)) {
			dsp->fRec118[l119] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l120;
		for (l120 = 0; (l120 < 3); l120 = (l120 + 1)) {
			dsp->fRec121[l120] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l121;
		for (l121 = 0; (l121 < 2); l121 = (l121 + 1)) {
			dsp->fRec120[l121] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l122;
		for (l122 = 0; (l122 < 2); l122 = (l122 + 1)) {
			dsp->fRec119[l122] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l123;
		for (l123 = 0; (l123 < 3); l123 = (l123 + 1)) {
			dsp->fRec122[l123] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l124;
		for (l124 = 0; (l124 < 3); l124 = (l124 + 1)) {
			dsp->fRec125[l124] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l125;
		for (l125 = 0; (l125 < 2); l125 = (l125 + 1)) {
			dsp->fRec124[l125] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l126;
		for (l126 = 0; (l126 < 2); l126 = (l126 + 1)) {
			dsp->fRec123[l126] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l127;
		for (l127 = 0; (l127 < 3); l127 = (l127 + 1)) {
			dsp->fRec126[l127] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l128;
		for (l128 = 0; (l128 < 3); l128 = (l128 + 1)) {
			dsp->fRec129[l128] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l129;
		for (l129 = 0; (l129 < 2); l129 = (l129 + 1)) {
			dsp->fRec128[l129] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l130;
		for (l130 = 0; (l130 < 2); l130 = (l130 + 1)) {
			dsp->fRec127[l130] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = tanf((95.4453049f / dsp->fConst0));
	dsp->fConst2 = (1.0f / dsp->fConst1);
	dsp->fConst3 = (1.0f / dsp->fConst0);
	dsp->fConst4 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(dsp->fConst1))));
	dsp->fConst5 = (0.0f - dsp->fConst2);
	dsp->fConst6 = (1000.0f / dsp->fConst0);
	dsp->fConst7 = tanf((115.989655f / dsp->fConst0));
	dsp->fConst8 = (1.0f / dsp->fConst7);
	dsp->fConst9 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(dsp->fConst7))));
	dsp->fConst10 = (0.0f - dsp->fConst8);
	dsp->fConst11 = tanf((140.956116f / dsp->fConst0));
	dsp->fConst12 = (1.0f / dsp->fConst11);
	dsp->fConst13 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(dsp->fConst11))));
	dsp->fConst14 = (0.0f - dsp->fConst12);
	dsp->fConst15 = tanf((171.296555f / dsp->fConst0));
	dsp->fConst16 = (1.0f / dsp->fConst15);
	dsp->fConst17 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(dsp->fConst15))));
	dsp->fConst18 = (0.0f - dsp->fConst16);
	dsp->fConst19 = tanf((208.167679f / dsp->fConst0));
	dsp->fConst20 = (1.0f / dsp->fConst19);
	dsp->fConst21 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(dsp->fConst19))));
	dsp->fConst22 = (0.0f - dsp->fConst20);
	dsp->fConst23 = tanf((252.975235f / dsp->fConst0));
	dsp->fConst24 = (1.0f / dsp->fConst23);
	dsp->fConst25 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(dsp->fConst23))));
	dsp->fConst26 = (0.0f - dsp->fConst24);
	dsp->fConst27 = tanf((307.42749f / dsp->fConst0));
	dsp->fConst28 = (1.0f / dsp->fConst27);
	dsp->fConst29 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(dsp->fConst27))));
	dsp->fConst30 = (0.0f - dsp->fConst28);
	dsp->fConst31 = tanf((373.600433f / dsp->fConst0));
	dsp->fConst32 = (1.0f / dsp->fConst31);
	dsp->fConst33 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(dsp->fConst31))));
	dsp->fConst34 = (0.0f - dsp->fConst32);
	dsp->fConst35 = tanf((454.016937f / dsp->fConst0));
	dsp->fConst36 = (1.0f / dsp->fConst35);
	dsp->fConst37 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(dsp->fConst35))));
	dsp->fConst38 = (0.0f - dsp->fConst36);
	dsp->fConst39 = tanf((551.742859f / dsp->fConst0));
	dsp->fConst40 = (1.0f / dsp->fConst39);
	dsp->fConst41 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(dsp->fConst39))));
	dsp->fConst42 = (0.0f - dsp->fConst40);
	dsp->fConst43 = tanf((670.504089f / dsp->fConst0));
	dsp->fConst44 = (1.0f / dsp->fConst43);
	dsp->fConst45 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(dsp->fConst43))));
	dsp->fConst46 = (0.0f - dsp->fConst44);
	dsp->fConst47 = tanf((814.828308f / dsp->fConst0));
	dsp->fConst48 = (1.0f / dsp->fConst47);
	dsp->fConst49 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(dsp->fConst47))));
	dsp->fConst50 = (0.0f - dsp->fConst48);
	dsp->fConst51 = tanf((990.217957f / dsp->fConst0));
	dsp->fConst52 = (1.0f / dsp->fConst51);
	dsp->fConst53 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(dsp->fConst51))));
	dsp->fConst54 = (0.0f - dsp->fConst52);
	dsp->fConst55 = tanf((1203.35974f / dsp->fConst0));
	dsp->fConst56 = (1.0f / dsp->fConst55);
	dsp->fConst57 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(dsp->fConst55))));
	dsp->fConst58 = (0.0f - dsp->fConst56);
	dsp->fConst59 = tanf((1462.37976f / dsp->fConst0));
	dsp->fConst60 = (1.0f / dsp->fConst59);
	dsp->fConst61 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(dsp->fConst59))));
	dsp->fConst62 = (0.0f - dsp->fConst60);
	dsp->fConst63 = tanf((1777.1532f / dsp->fConst0));
	dsp->fConst64 = (1.0f / dsp->fConst63);
	dsp->fConst65 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(dsp->fConst63))));
	dsp->fConst66 = (0.0f - dsp->fConst64);
	dsp->fConst67 = tanf((2159.68066f / dsp->fConst0));
	dsp->fConst68 = (1.0f / dsp->fConst67);
	dsp->fConst69 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(dsp->fConst67))));
	dsp->fConst70 = (0.0f - dsp->fConst68);
	dsp->fConst71 = tanf((2624.54639f / dsp->fConst0));
	dsp->fConst72 = (1.0f / dsp->fConst71);
	dsp->fConst73 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(dsp->fConst71))));
	dsp->fConst74 = (0.0f - dsp->fConst72);
	dsp->fConst75 = tanf((3189.4729f / dsp->fConst0));
	dsp->fConst76 = (1.0f / dsp->fConst75);
	dsp->fConst77 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(dsp->fConst75))));
	dsp->fConst78 = (0.0f - dsp->fConst76);
	dsp->fConst79 = tanf((3875.99854f / dsp->fConst0));
	dsp->fConst80 = (1.0f / dsp->fConst79);
	dsp->fConst81 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(dsp->fConst79))));
	dsp->fConst82 = (0.0f - dsp->fConst80);
	dsp->fConst83 = tanf((4710.29688f / dsp->fConst0));
	dsp->fConst84 = (1.0f / dsp->fConst83);
	dsp->fConst85 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(dsp->fConst83))));
	dsp->fConst86 = (0.0f - dsp->fConst84);
	dsp->fConst87 = tanf((5724.17578f / dsp->fConst0));
	dsp->fConst88 = (1.0f / dsp->fConst87);
	dsp->fConst89 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(dsp->fConst87))));
	dsp->fConst90 = (0.0f - dsp->fConst88);
	dsp->fConst91 = tanf((6956.28955f / dsp->fConst0));
	dsp->fConst92 = (1.0f / dsp->fConst91);
	dsp->fConst93 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(dsp->fConst91))));
	dsp->fConst94 = (0.0f - dsp->fConst92);
	dsp->fConst95 = tanf((8453.61328f / dsp->fConst0));
	dsp->fConst96 = (1.0f / dsp->fConst95);
	dsp->fConst97 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(dsp->fConst95))));
	dsp->fConst98 = (0.0f - dsp->fConst96);
	dsp->fConst99 = tanf((10273.2305f / dsp->fConst0));
	dsp->fConst100 = (1.0f / dsp->fConst99);
	dsp->fConst101 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(dsp->fConst99))));
	dsp->fConst102 = (0.0f - dsp->fConst100);
	dsp->fConst103 = tanf((12484.5166f / dsp->fConst0));
	dsp->fConst104 = (1.0f / dsp->fConst103);
	dsp->fConst105 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(dsp->fConst103))));
	dsp->fConst106 = (0.0f - dsp->fConst104);
	dsp->fConst107 = tanf((15171.7754f / dsp->fConst0));
	dsp->fConst108 = (1.0f / dsp->fConst107);
	dsp->fConst109 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(dsp->fConst107))));
	dsp->fConst110 = (0.0f - dsp->fConst108);
	dsp->fConst111 = tanf((18437.4609f / dsp->fConst0));
	dsp->fConst112 = (1.0f / dsp->fConst111);
	dsp->fConst113 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(dsp->fConst111))));
	dsp->fConst114 = (0.0f - dsp->fConst112);
	dsp->fConst115 = tanf((22406.0742f / dsp->fConst0));
	dsp->fConst116 = (1.0f / dsp->fConst115);
	dsp->fConst117 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(dsp->fConst115))));
	dsp->fConst118 = (0.0f - dsp->fConst116);
	dsp->fConst119 = tanf((27228.9238f / dsp->fConst0));
	dsp->fConst120 = (1.0f / dsp->fConst119);
	dsp->fConst121 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(dsp->fConst119))));
	dsp->fConst122 = (0.0f - dsp->fConst120);
	dsp->fConst123 = tanf((33089.8789f / dsp->fConst0));
	dsp->fConst124 = (1.0f / dsp->fConst123);
	dsp->fConst125 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(dsp->fConst123))));
	dsp->fConst126 = (0.0f - dsp->fConst124);
	dsp->fConst127 = tanf((40212.3867f / dsp->fConst0));
	dsp->fConst128 = (1.0f / dsp->fConst127);
	dsp->fConst129 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(dsp->fConst127))));
	dsp->fConst130 = (0.0f - dsp->fConst128);
	
}

void instanceInitmydsp(mydsp* dsp, int samplingFreq) {
	instanceConstantsmydsp(dsp, samplingFreq);
	instanceResetUserInterfacemydsp(dsp);
	instanceClearmydsp(dsp);
}

void initmydsp(mydsp* dsp, int samplingFreq) {
	classInitmydsp(samplingFreq);
	instanceInitmydsp(dsp, samplingFreq);
}

void buildUserInterfacemydsp(mydsp* dsp, UIGlue* ui_interface) {
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "My Vocoder");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "Excitation");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Freq", &dsp->fHslider1, 330.0f, 50.0f, 2000.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider0, "1", "");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Gain", &dsp->fVslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "Vocoder");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "tooltip", "Attack time in seconds");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Attack", &dsp->fHslider2, 5.0f, 0.100000001f, 100.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "tooltip", "Release time in seconds");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Release", &dsp->fHslider3, 5.0f, 0.100000001f, 100.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "tooltip", "Coefficient to adjust the   bandwidth of each band");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "BW", &dsp->fHslider0, 0.5f, 0.100000001f, 2.0f, 0.00100000005f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* input0 = inputs[0];
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	float fSlow0 = (float)dsp->fHslider0;
	float fSlow1 = (0.177122265f * fSlow0);
	float fSlow2 = (1.0f / ((dsp->fConst2 * (dsp->fConst2 + fSlow1)) + 1.0f));
	float fSlow3 = (0.00100000005f * (float)dsp->fVslider0);
	float fSlow4 = (float)dsp->fHslider1;
	float fSlow5 = ((dsp->fConst2 * (dsp->fConst2 - fSlow1)) + 1.0f);
	float fSlow6 = expf((0.0f - (dsp->fConst6 / (float)dsp->fHslider2)));
	float fSlow7 = expf((0.0f - (dsp->fConst6 / (float)dsp->fHslider3)));
	float fSlow8 = (0.177122265f * fSlow0);
	float fSlow9 = (1.0f / ((dsp->fConst8 * (dsp->fConst8 + fSlow8)) + 1.0f));
	float fSlow10 = ((dsp->fConst8 * (dsp->fConst8 - fSlow8)) + 1.0f);
	float fSlow11 = (1.0f / ((dsp->fConst12 * (dsp->fConst12 + fSlow1)) + 1.0f));
	float fSlow12 = ((dsp->fConst12 * (dsp->fConst12 - fSlow1)) + 1.0f);
	float fSlow13 = (0.177122265f * fSlow0);
	float fSlow14 = (1.0f / ((dsp->fConst16 * (dsp->fConst16 + fSlow13)) + 1.0f));
	float fSlow15 = ((dsp->fConst16 * (dsp->fConst16 - fSlow13)) + 1.0f);
	float fSlow16 = (0.177122265f * fSlow0);
	float fSlow17 = (1.0f / ((dsp->fConst20 * (dsp->fConst20 + fSlow16)) + 1.0f));
	float fSlow18 = ((dsp->fConst20 * (dsp->fConst20 - fSlow16)) + 1.0f);
	float fSlow19 = (0.177122265f * fSlow0);
	float fSlow20 = (1.0f / ((dsp->fConst24 * (dsp->fConst24 + fSlow19)) + 1.0f));
	float fSlow21 = ((dsp->fConst24 * (dsp->fConst24 - fSlow19)) + 1.0f);
	float fSlow22 = (0.177122265f * fSlow0);
	float fSlow23 = (1.0f / ((dsp->fConst28 * (dsp->fConst28 + fSlow22)) + 1.0f));
	float fSlow24 = ((dsp->fConst28 * (dsp->fConst28 - fSlow22)) + 1.0f);
	float fSlow25 = (1.0f / ((dsp->fConst32 * (dsp->fConst32 + fSlow1)) + 1.0f));
	float fSlow26 = ((dsp->fConst32 * (dsp->fConst32 - fSlow1)) + 1.0f);
	float fSlow27 = (1.0f / ((dsp->fConst36 * (dsp->fConst36 + fSlow16)) + 1.0f));
	float fSlow28 = ((dsp->fConst36 * (dsp->fConst36 - fSlow16)) + 1.0f);
	float fSlow29 = (1.0f / ((dsp->fConst40 * (dsp->fConst40 + fSlow8)) + 1.0f));
	float fSlow30 = ((dsp->fConst40 * (dsp->fConst40 - fSlow8)) + 1.0f);
	float fSlow31 = (0.177122265f * fSlow0);
	float fSlow32 = (1.0f / ((dsp->fConst44 * (dsp->fConst44 + fSlow31)) + 1.0f));
	float fSlow33 = ((dsp->fConst44 * (dsp->fConst44 - fSlow31)) + 1.0f);
	float fSlow34 = (0.177122265f * fSlow0);
	float fSlow35 = (1.0f / ((dsp->fConst48 * (dsp->fConst48 + fSlow34)) + 1.0f));
	float fSlow36 = ((dsp->fConst48 * (dsp->fConst48 - fSlow34)) + 1.0f);
	float fSlow37 = (1.0f / ((dsp->fConst52 * (dsp->fConst52 + fSlow31)) + 1.0f));
	float fSlow38 = ((dsp->fConst52 * (dsp->fConst52 - fSlow31)) + 1.0f);
	float fSlow39 = (0.177122265f * fSlow0);
	float fSlow40 = (1.0f / ((dsp->fConst56 * (dsp->fConst56 + fSlow39)) + 1.0f));
	float fSlow41 = ((dsp->fConst56 * (dsp->fConst56 - fSlow39)) + 1.0f);
	float fSlow42 = (1.0f / ((dsp->fConst60 * (dsp->fConst60 + fSlow13)) + 1.0f));
	float fSlow43 = ((dsp->fConst60 * (dsp->fConst60 - fSlow13)) + 1.0f);
	float fSlow44 = (1.0f / ((dsp->fConst64 * (dsp->fConst64 + fSlow13)) + 1.0f));
	float fSlow45 = ((dsp->fConst64 * (dsp->fConst64 - fSlow13)) + 1.0f);
	float fSlow46 = (1.0f / ((dsp->fConst68 * (dsp->fConst68 + fSlow8)) + 1.0f));
	float fSlow47 = ((dsp->fConst68 * (dsp->fConst68 - fSlow8)) + 1.0f);
	float fSlow48 = (0.177122265f * fSlow0);
	float fSlow49 = (1.0f / ((dsp->fConst72 * (dsp->fConst72 + fSlow48)) + 1.0f));
	float fSlow50 = ((dsp->fConst72 * (dsp->fConst72 - fSlow48)) + 1.0f);
	float fSlow51 = (1.0f / ((dsp->fConst76 * (dsp->fConst76 + fSlow16)) + 1.0f));
	float fSlow52 = ((dsp->fConst76 * (dsp->fConst76 - fSlow16)) + 1.0f);
	float fSlow53 = (1.0f / ((dsp->fConst80 * (dsp->fConst80 + fSlow39)) + 1.0f));
	float fSlow54 = ((dsp->fConst80 * (dsp->fConst80 - fSlow39)) + 1.0f);
	float fSlow55 = (1.0f / ((dsp->fConst84 * (dsp->fConst84 + fSlow22)) + 1.0f));
	float fSlow56 = ((dsp->fConst84 * (dsp->fConst84 - fSlow22)) + 1.0f);
	float fSlow57 = (1.0f / ((dsp->fConst88 * (dsp->fConst88 + fSlow39)) + 1.0f));
	float fSlow58 = ((dsp->fConst88 * (dsp->fConst88 - fSlow39)) + 1.0f);
	float fSlow59 = (1.0f / ((dsp->fConst92 * (dsp->fConst92 + fSlow22)) + 1.0f));
	float fSlow60 = ((dsp->fConst92 * (dsp->fConst92 - fSlow22)) + 1.0f);
	float fSlow61 = (0.177122265f * fSlow0);
	float fSlow62 = (1.0f / ((dsp->fConst96 * (dsp->fConst96 + fSlow61)) + 1.0f));
	float fSlow63 = ((dsp->fConst96 * (dsp->fConst96 - fSlow61)) + 1.0f);
	float fSlow64 = (1.0f / ((dsp->fConst100 * (dsp->fConst100 + fSlow13)) + 1.0f));
	float fSlow65 = ((dsp->fConst100 * (dsp->fConst100 - fSlow13)) + 1.0f);
	float fSlow66 = (1.0f / ((dsp->fConst104 * (dsp->fConst104 + fSlow1)) + 1.0f));
	float fSlow67 = ((dsp->fConst104 * (dsp->fConst104 - fSlow1)) + 1.0f);
	float fSlow68 = (1.0f / ((dsp->fConst108 * (dsp->fConst108 + fSlow31)) + 1.0f));
	float fSlow69 = ((dsp->fConst108 * (dsp->fConst108 - fSlow31)) + 1.0f);
	float fSlow70 = (0.177122265f * fSlow0);
	float fSlow71 = (1.0f / ((dsp->fConst112 * (dsp->fConst112 + fSlow70)) + 1.0f));
	float fSlow72 = ((dsp->fConst112 * (dsp->fConst112 - fSlow70)) + 1.0f);
	float fSlow73 = (1.0f / ((dsp->fConst116 * (dsp->fConst116 + fSlow1)) + 1.0f));
	float fSlow74 = ((dsp->fConst116 * (dsp->fConst116 - fSlow1)) + 1.0f);
	float fSlow75 = (1.0f / ((dsp->fConst120 * (dsp->fConst120 + fSlow39)) + 1.0f));
	float fSlow76 = ((dsp->fConst120 * (dsp->fConst120 - fSlow39)) + 1.0f);
	float fSlow77 = (0.177122265f * fSlow0);
	float fSlow78 = (1.0f / ((dsp->fConst124 * (dsp->fConst124 + fSlow77)) + 1.0f));
	float fSlow79 = ((dsp->fConst124 * (dsp->fConst124 - fSlow77)) + 1.0f);
	float fSlow80 = (1.0f / ((dsp->fConst128 * (dsp->fConst128 + fSlow61)) + 1.0f));
	float fSlow81 = ((dsp->fConst128 * (dsp->fConst128 - fSlow61)) + 1.0f);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->fRec1[0] = (fSlow3 + (0.999000013f * dsp->fRec1[1]));
			dsp->fVec0[0] = fSlow4;
			float fTemp0 = (dsp->fRec2[1] + (dsp->fConst3 * dsp->fVec0[1]));
			dsp->fRec2[0] = (fTemp0 - floorf(fTemp0));
			float fTemp1 = (dsp->fRec1[0] * (float)((dsp->fRec2[0] - dsp->fRec2[1]) < 0.0f));
			dsp->fRec0[0] = (fTemp1 - (fSlow2 * ((fSlow5 * dsp->fRec0[2]) + (dsp->fConst4 * dsp->fRec0[1]))));
			float fTemp2 = (float)input0[i];
			dsp->fRec5[0] = (fTemp2 - (fSlow2 * ((dsp->fConst4 * dsp->fRec5[1]) + (fSlow5 * dsp->fRec5[2]))));
			float fTemp3 = fabsf((fSlow2 * ((dsp->fConst2 * dsp->fRec5[0]) + (dsp->fConst5 * dsp->fRec5[2]))));
			float fTemp4 = ((dsp->fRec3[1] > fTemp3)?fSlow7:fSlow6);
			dsp->fRec4[0] = ((dsp->fRec4[1] * fTemp4) + (fTemp3 * (1.0f - fTemp4)));
			dsp->fRec3[0] = dsp->fRec4[0];
			dsp->fRec6[0] = (fTemp1 - (fSlow9 * ((fSlow10 * dsp->fRec6[2]) + (dsp->fConst9 * dsp->fRec6[1]))));
			dsp->fRec9[0] = (fTemp2 - (fSlow9 * ((dsp->fConst9 * dsp->fRec9[1]) + (fSlow10 * dsp->fRec9[2]))));
			float fTemp5 = fabsf((fSlow9 * ((dsp->fConst8 * dsp->fRec9[0]) + (dsp->fConst10 * dsp->fRec9[2]))));
			float fTemp6 = ((dsp->fRec7[1] > fTemp5)?fSlow7:fSlow6);
			dsp->fRec8[0] = ((dsp->fRec8[1] * fTemp6) + (fTemp5 * (1.0f - fTemp6)));
			dsp->fRec7[0] = dsp->fRec8[0];
			dsp->fRec10[0] = (fTemp1 - (fSlow11 * ((fSlow12 * dsp->fRec10[2]) + (dsp->fConst13 * dsp->fRec10[1]))));
			dsp->fRec13[0] = (fTemp2 - (fSlow11 * ((dsp->fConst13 * dsp->fRec13[1]) + (fSlow12 * dsp->fRec13[2]))));
			float fTemp7 = fabsf((fSlow11 * ((dsp->fConst12 * dsp->fRec13[0]) + (dsp->fConst14 * dsp->fRec13[2]))));
			float fTemp8 = ((dsp->fRec11[1] > fTemp7)?fSlow7:fSlow6);
			dsp->fRec12[0] = ((dsp->fRec12[1] * fTemp8) + (fTemp7 * (1.0f - fTemp8)));
			dsp->fRec11[0] = dsp->fRec12[0];
			dsp->fRec14[0] = (fTemp1 - (fSlow14 * ((fSlow15 * dsp->fRec14[2]) + (dsp->fConst17 * dsp->fRec14[1]))));
			dsp->fRec17[0] = (fTemp2 - (fSlow14 * ((dsp->fConst17 * dsp->fRec17[1]) + (fSlow15 * dsp->fRec17[2]))));
			float fTemp9 = fabsf((fSlow14 * ((dsp->fConst16 * dsp->fRec17[0]) + (dsp->fConst18 * dsp->fRec17[2]))));
			float fTemp10 = ((dsp->fRec15[1] > fTemp9)?fSlow7:fSlow6);
			dsp->fRec16[0] = ((dsp->fRec16[1] * fTemp10) + (fTemp9 * (1.0f - fTemp10)));
			dsp->fRec15[0] = dsp->fRec16[0];
			dsp->fRec18[0] = (fTemp1 - (fSlow17 * ((fSlow18 * dsp->fRec18[2]) + (dsp->fConst21 * dsp->fRec18[1]))));
			dsp->fRec21[0] = (fTemp2 - (fSlow17 * ((dsp->fConst21 * dsp->fRec21[1]) + (fSlow18 * dsp->fRec21[2]))));
			float fTemp11 = fabsf((fSlow17 * ((dsp->fConst20 * dsp->fRec21[0]) + (dsp->fConst22 * dsp->fRec21[2]))));
			float fTemp12 = ((dsp->fRec19[1] > fTemp11)?fSlow7:fSlow6);
			dsp->fRec20[0] = ((dsp->fRec20[1] * fTemp12) + (fTemp11 * (1.0f - fTemp12)));
			dsp->fRec19[0] = dsp->fRec20[0];
			dsp->fRec22[0] = (fTemp1 - (fSlow20 * ((fSlow21 * dsp->fRec22[2]) + (dsp->fConst25 * dsp->fRec22[1]))));
			dsp->fRec25[0] = (fTemp2 - (fSlow20 * ((dsp->fConst25 * dsp->fRec25[1]) + (fSlow21 * dsp->fRec25[2]))));
			float fTemp13 = fabsf((fSlow20 * ((dsp->fConst24 * dsp->fRec25[0]) + (dsp->fConst26 * dsp->fRec25[2]))));
			float fTemp14 = ((dsp->fRec23[1] > fTemp13)?fSlow7:fSlow6);
			dsp->fRec24[0] = ((dsp->fRec24[1] * fTemp14) + (fTemp13 * (1.0f - fTemp14)));
			dsp->fRec23[0] = dsp->fRec24[0];
			dsp->fRec26[0] = (fTemp1 - (fSlow23 * ((fSlow24 * dsp->fRec26[2]) + (dsp->fConst29 * dsp->fRec26[1]))));
			dsp->fRec29[0] = (fTemp2 - (fSlow23 * ((dsp->fConst29 * dsp->fRec29[1]) + (fSlow24 * dsp->fRec29[2]))));
			float fTemp15 = fabsf((fSlow23 * ((dsp->fConst28 * dsp->fRec29[0]) + (dsp->fConst30 * dsp->fRec29[2]))));
			float fTemp16 = ((dsp->fRec27[1] > fTemp15)?fSlow7:fSlow6);
			dsp->fRec28[0] = ((dsp->fRec28[1] * fTemp16) + (fTemp15 * (1.0f - fTemp16)));
			dsp->fRec27[0] = dsp->fRec28[0];
			dsp->fRec30[0] = (fTemp1 - (fSlow25 * ((fSlow26 * dsp->fRec30[2]) + (dsp->fConst33 * dsp->fRec30[1]))));
			dsp->fRec33[0] = (fTemp2 - (fSlow25 * ((dsp->fConst33 * dsp->fRec33[1]) + (fSlow26 * dsp->fRec33[2]))));
			float fTemp17 = fabsf((fSlow25 * ((dsp->fConst32 * dsp->fRec33[0]) + (dsp->fConst34 * dsp->fRec33[2]))));
			float fTemp18 = ((dsp->fRec31[1] > fTemp17)?fSlow7:fSlow6);
			dsp->fRec32[0] = ((dsp->fRec32[1] * fTemp18) + (fTemp17 * (1.0f - fTemp18)));
			dsp->fRec31[0] = dsp->fRec32[0];
			dsp->fRec34[0] = (fTemp1 - (fSlow27 * ((fSlow28 * dsp->fRec34[2]) + (dsp->fConst37 * dsp->fRec34[1]))));
			dsp->fRec37[0] = (fTemp2 - (fSlow27 * ((dsp->fConst37 * dsp->fRec37[1]) + (fSlow28 * dsp->fRec37[2]))));
			float fTemp19 = fabsf((fSlow27 * ((dsp->fConst36 * dsp->fRec37[0]) + (dsp->fConst38 * dsp->fRec37[2]))));
			float fTemp20 = ((dsp->fRec35[1] > fTemp19)?fSlow7:fSlow6);
			dsp->fRec36[0] = ((dsp->fRec36[1] * fTemp20) + (fTemp19 * (1.0f - fTemp20)));
			dsp->fRec35[0] = dsp->fRec36[0];
			dsp->fRec38[0] = (fTemp1 - (fSlow29 * ((fSlow30 * dsp->fRec38[2]) + (dsp->fConst41 * dsp->fRec38[1]))));
			dsp->fRec41[0] = (fTemp2 - (fSlow29 * ((dsp->fConst41 * dsp->fRec41[1]) + (fSlow30 * dsp->fRec41[2]))));
			float fTemp21 = fabsf((fSlow29 * ((dsp->fConst40 * dsp->fRec41[0]) + (dsp->fConst42 * dsp->fRec41[2]))));
			float fTemp22 = ((dsp->fRec39[1] > fTemp21)?fSlow7:fSlow6);
			dsp->fRec40[0] = ((dsp->fRec40[1] * fTemp22) + (fTemp21 * (1.0f - fTemp22)));
			dsp->fRec39[0] = dsp->fRec40[0];
			dsp->fRec42[0] = (fTemp1 - (fSlow32 * ((fSlow33 * dsp->fRec42[2]) + (dsp->fConst45 * dsp->fRec42[1]))));
			dsp->fRec45[0] = (fTemp2 - (fSlow32 * ((dsp->fConst45 * dsp->fRec45[1]) + (fSlow33 * dsp->fRec45[2]))));
			float fTemp23 = fabsf((fSlow32 * ((dsp->fConst44 * dsp->fRec45[0]) + (dsp->fConst46 * dsp->fRec45[2]))));
			float fTemp24 = ((dsp->fRec43[1] > fTemp23)?fSlow7:fSlow6);
			dsp->fRec44[0] = ((dsp->fRec44[1] * fTemp24) + (fTemp23 * (1.0f - fTemp24)));
			dsp->fRec43[0] = dsp->fRec44[0];
			dsp->fRec46[0] = (fTemp1 - (fSlow35 * ((fSlow36 * dsp->fRec46[2]) + (dsp->fConst49 * dsp->fRec46[1]))));
			dsp->fRec49[0] = (fTemp2 - (fSlow35 * ((dsp->fConst49 * dsp->fRec49[1]) + (fSlow36 * dsp->fRec49[2]))));
			float fTemp25 = fabsf((fSlow35 * ((dsp->fConst48 * dsp->fRec49[0]) + (dsp->fConst50 * dsp->fRec49[2]))));
			float fTemp26 = ((dsp->fRec47[1] > fTemp25)?fSlow7:fSlow6);
			dsp->fRec48[0] = ((dsp->fRec48[1] * fTemp26) + (fTemp25 * (1.0f - fTemp26)));
			dsp->fRec47[0] = dsp->fRec48[0];
			dsp->fRec50[0] = (fTemp1 - (fSlow37 * ((fSlow38 * dsp->fRec50[2]) + (dsp->fConst53 * dsp->fRec50[1]))));
			dsp->fRec53[0] = (fTemp2 - (fSlow37 * ((dsp->fConst53 * dsp->fRec53[1]) + (fSlow38 * dsp->fRec53[2]))));
			float fTemp27 = fabsf((fSlow37 * ((dsp->fConst52 * dsp->fRec53[0]) + (dsp->fConst54 * dsp->fRec53[2]))));
			float fTemp28 = ((dsp->fRec51[1] > fTemp27)?fSlow7:fSlow6);
			dsp->fRec52[0] = ((dsp->fRec52[1] * fTemp28) + (fTemp27 * (1.0f - fTemp28)));
			dsp->fRec51[0] = dsp->fRec52[0];
			dsp->fRec54[0] = (fTemp1 - (fSlow40 * ((fSlow41 * dsp->fRec54[2]) + (dsp->fConst57 * dsp->fRec54[1]))));
			dsp->fRec57[0] = (fTemp2 - (fSlow40 * ((dsp->fConst57 * dsp->fRec57[1]) + (fSlow41 * dsp->fRec57[2]))));
			float fTemp29 = fabsf((fSlow40 * ((dsp->fConst56 * dsp->fRec57[0]) + (dsp->fConst58 * dsp->fRec57[2]))));
			float fTemp30 = ((dsp->fRec55[1] > fTemp29)?fSlow7:fSlow6);
			dsp->fRec56[0] = ((dsp->fRec56[1] * fTemp30) + (fTemp29 * (1.0f - fTemp30)));
			dsp->fRec55[0] = dsp->fRec56[0];
			dsp->fRec58[0] = (fTemp1 - (fSlow42 * ((fSlow43 * dsp->fRec58[2]) + (dsp->fConst61 * dsp->fRec58[1]))));
			dsp->fRec61[0] = (fTemp2 - (fSlow42 * ((dsp->fConst61 * dsp->fRec61[1]) + (fSlow43 * dsp->fRec61[2]))));
			float fTemp31 = fabsf((fSlow42 * ((dsp->fConst60 * dsp->fRec61[0]) + (dsp->fConst62 * dsp->fRec61[2]))));
			float fTemp32 = ((dsp->fRec59[1] > fTemp31)?fSlow7:fSlow6);
			dsp->fRec60[0] = ((dsp->fRec60[1] * fTemp32) + (fTemp31 * (1.0f - fTemp32)));
			dsp->fRec59[0] = dsp->fRec60[0];
			dsp->fRec62[0] = (fTemp1 - (fSlow44 * ((fSlow45 * dsp->fRec62[2]) + (dsp->fConst65 * dsp->fRec62[1]))));
			dsp->fRec65[0] = (fTemp2 - (fSlow44 * ((dsp->fConst65 * dsp->fRec65[1]) + (fSlow45 * dsp->fRec65[2]))));
			float fTemp33 = fabsf((fSlow44 * ((dsp->fConst64 * dsp->fRec65[0]) + (dsp->fConst66 * dsp->fRec65[2]))));
			float fTemp34 = ((dsp->fRec63[1] > fTemp33)?fSlow7:fSlow6);
			dsp->fRec64[0] = ((dsp->fRec64[1] * fTemp34) + (fTemp33 * (1.0f - fTemp34)));
			dsp->fRec63[0] = dsp->fRec64[0];
			dsp->fRec66[0] = (fTemp1 - (fSlow46 * ((fSlow47 * dsp->fRec66[2]) + (dsp->fConst69 * dsp->fRec66[1]))));
			dsp->fRec69[0] = (fTemp2 - (fSlow46 * ((dsp->fConst69 * dsp->fRec69[1]) + (fSlow47 * dsp->fRec69[2]))));
			float fTemp35 = fabsf((fSlow46 * ((dsp->fConst68 * dsp->fRec69[0]) + (dsp->fConst70 * dsp->fRec69[2]))));
			float fTemp36 = ((dsp->fRec67[1] > fTemp35)?fSlow7:fSlow6);
			dsp->fRec68[0] = ((dsp->fRec68[1] * fTemp36) + (fTemp35 * (1.0f - fTemp36)));
			dsp->fRec67[0] = dsp->fRec68[0];
			dsp->fRec70[0] = (fTemp1 - (fSlow49 * ((fSlow50 * dsp->fRec70[2]) + (dsp->fConst73 * dsp->fRec70[1]))));
			dsp->fRec73[0] = (fTemp2 - (fSlow49 * ((dsp->fConst73 * dsp->fRec73[1]) + (fSlow50 * dsp->fRec73[2]))));
			float fTemp37 = fabsf((fSlow49 * ((dsp->fConst72 * dsp->fRec73[0]) + (dsp->fConst74 * dsp->fRec73[2]))));
			float fTemp38 = ((dsp->fRec71[1] > fTemp37)?fSlow7:fSlow6);
			dsp->fRec72[0] = ((dsp->fRec72[1] * fTemp38) + (fTemp37 * (1.0f - fTemp38)));
			dsp->fRec71[0] = dsp->fRec72[0];
			dsp->fRec74[0] = (fTemp1 - (fSlow51 * ((fSlow52 * dsp->fRec74[2]) + (dsp->fConst77 * dsp->fRec74[1]))));
			dsp->fRec77[0] = (fTemp2 - (fSlow51 * ((dsp->fConst77 * dsp->fRec77[1]) + (fSlow52 * dsp->fRec77[2]))));
			float fTemp39 = fabsf((fSlow51 * ((dsp->fConst76 * dsp->fRec77[0]) + (dsp->fConst78 * dsp->fRec77[2]))));
			float fTemp40 = ((dsp->fRec75[1] > fTemp39)?fSlow7:fSlow6);
			dsp->fRec76[0] = ((dsp->fRec76[1] * fTemp40) + (fTemp39 * (1.0f - fTemp40)));
			dsp->fRec75[0] = dsp->fRec76[0];
			dsp->fRec78[0] = (fTemp1 - (fSlow53 * ((fSlow54 * dsp->fRec78[2]) + (dsp->fConst81 * dsp->fRec78[1]))));
			dsp->fRec81[0] = (fTemp2 - (fSlow53 * ((dsp->fConst81 * dsp->fRec81[1]) + (fSlow54 * dsp->fRec81[2]))));
			float fTemp41 = fabsf((fSlow53 * ((dsp->fConst80 * dsp->fRec81[0]) + (dsp->fConst82 * dsp->fRec81[2]))));
			float fTemp42 = ((dsp->fRec79[1] > fTemp41)?fSlow7:fSlow6);
			dsp->fRec80[0] = ((dsp->fRec80[1] * fTemp42) + (fTemp41 * (1.0f - fTemp42)));
			dsp->fRec79[0] = dsp->fRec80[0];
			dsp->fRec82[0] = (fTemp1 - (fSlow55 * ((fSlow56 * dsp->fRec82[2]) + (dsp->fConst85 * dsp->fRec82[1]))));
			dsp->fRec85[0] = (fTemp2 - (fSlow55 * ((dsp->fConst85 * dsp->fRec85[1]) + (fSlow56 * dsp->fRec85[2]))));
			float fTemp43 = fabsf((fSlow55 * ((dsp->fConst84 * dsp->fRec85[0]) + (dsp->fConst86 * dsp->fRec85[2]))));
			float fTemp44 = ((dsp->fRec83[1] > fTemp43)?fSlow7:fSlow6);
			dsp->fRec84[0] = ((dsp->fRec84[1] * fTemp44) + (fTemp43 * (1.0f - fTemp44)));
			dsp->fRec83[0] = dsp->fRec84[0];
			dsp->fRec86[0] = (fTemp1 - (fSlow57 * ((fSlow58 * dsp->fRec86[2]) + (dsp->fConst89 * dsp->fRec86[1]))));
			dsp->fRec89[0] = (fTemp2 - (fSlow57 * ((dsp->fConst89 * dsp->fRec89[1]) + (fSlow58 * dsp->fRec89[2]))));
			float fTemp45 = fabsf((fSlow57 * ((dsp->fConst88 * dsp->fRec89[0]) + (dsp->fConst90 * dsp->fRec89[2]))));
			float fTemp46 = ((dsp->fRec87[1] > fTemp45)?fSlow7:fSlow6);
			dsp->fRec88[0] = ((dsp->fRec88[1] * fTemp46) + (fTemp45 * (1.0f - fTemp46)));
			dsp->fRec87[0] = dsp->fRec88[0];
			dsp->fRec90[0] = (fTemp1 - (fSlow59 * ((fSlow60 * dsp->fRec90[2]) + (dsp->fConst93 * dsp->fRec90[1]))));
			dsp->fRec93[0] = (fTemp2 - (fSlow59 * ((dsp->fConst93 * dsp->fRec93[1]) + (fSlow60 * dsp->fRec93[2]))));
			float fTemp47 = fabsf((fSlow59 * ((dsp->fConst92 * dsp->fRec93[0]) + (dsp->fConst94 * dsp->fRec93[2]))));
			float fTemp48 = ((dsp->fRec91[1] > fTemp47)?fSlow7:fSlow6);
			dsp->fRec92[0] = ((dsp->fRec92[1] * fTemp48) + (fTemp47 * (1.0f - fTemp48)));
			dsp->fRec91[0] = dsp->fRec92[0];
			dsp->fRec94[0] = (fTemp1 - (fSlow62 * ((fSlow63 * dsp->fRec94[2]) + (dsp->fConst97 * dsp->fRec94[1]))));
			dsp->fRec97[0] = (fTemp2 - (fSlow62 * ((dsp->fConst97 * dsp->fRec97[1]) + (fSlow63 * dsp->fRec97[2]))));
			float fTemp49 = fabsf((fSlow62 * ((dsp->fConst96 * dsp->fRec97[0]) + (dsp->fConst98 * dsp->fRec97[2]))));
			float fTemp50 = ((dsp->fRec95[1] > fTemp49)?fSlow7:fSlow6);
			dsp->fRec96[0] = ((dsp->fRec96[1] * fTemp50) + (fTemp49 * (1.0f - fTemp50)));
			dsp->fRec95[0] = dsp->fRec96[0];
			dsp->fRec98[0] = (fTemp1 - (fSlow64 * ((fSlow65 * dsp->fRec98[2]) + (dsp->fConst101 * dsp->fRec98[1]))));
			dsp->fRec101[0] = (fTemp2 - (fSlow64 * ((dsp->fConst101 * dsp->fRec101[1]) + (fSlow65 * dsp->fRec101[2]))));
			float fTemp51 = fabsf((fSlow64 * ((dsp->fConst100 * dsp->fRec101[0]) + (dsp->fConst102 * dsp->fRec101[2]))));
			float fTemp52 = ((dsp->fRec99[1] > fTemp51)?fSlow7:fSlow6);
			dsp->fRec100[0] = ((dsp->fRec100[1] * fTemp52) + (fTemp51 * (1.0f - fTemp52)));
			dsp->fRec99[0] = dsp->fRec100[0];
			dsp->fRec102[0] = (fTemp1 - (fSlow66 * ((fSlow67 * dsp->fRec102[2]) + (dsp->fConst105 * dsp->fRec102[1]))));
			dsp->fRec105[0] = (fTemp2 - (fSlow66 * ((dsp->fConst105 * dsp->fRec105[1]) + (fSlow67 * dsp->fRec105[2]))));
			float fTemp53 = fabsf((fSlow66 * ((dsp->fConst104 * dsp->fRec105[0]) + (dsp->fConst106 * dsp->fRec105[2]))));
			float fTemp54 = ((dsp->fRec103[1] > fTemp53)?fSlow7:fSlow6);
			dsp->fRec104[0] = ((dsp->fRec104[1] * fTemp54) + (fTemp53 * (1.0f - fTemp54)));
			dsp->fRec103[0] = dsp->fRec104[0];
			dsp->fRec106[0] = (fTemp1 - (fSlow68 * ((fSlow69 * dsp->fRec106[2]) + (dsp->fConst109 * dsp->fRec106[1]))));
			dsp->fRec109[0] = (fTemp2 - (fSlow68 * ((dsp->fConst109 * dsp->fRec109[1]) + (fSlow69 * dsp->fRec109[2]))));
			float fTemp55 = fabsf((fSlow68 * ((dsp->fConst108 * dsp->fRec109[0]) + (dsp->fConst110 * dsp->fRec109[2]))));
			float fTemp56 = ((dsp->fRec107[1] > fTemp55)?fSlow7:fSlow6);
			dsp->fRec108[0] = ((dsp->fRec108[1] * fTemp56) + (fTemp55 * (1.0f - fTemp56)));
			dsp->fRec107[0] = dsp->fRec108[0];
			dsp->fRec110[0] = (fTemp1 - (fSlow71 * ((fSlow72 * dsp->fRec110[2]) + (dsp->fConst113 * dsp->fRec110[1]))));
			dsp->fRec113[0] = (fTemp2 - (fSlow71 * ((dsp->fConst113 * dsp->fRec113[1]) + (fSlow72 * dsp->fRec113[2]))));
			float fTemp57 = fabsf((fSlow71 * ((dsp->fConst112 * dsp->fRec113[0]) + (dsp->fConst114 * dsp->fRec113[2]))));
			float fTemp58 = ((dsp->fRec111[1] > fTemp57)?fSlow7:fSlow6);
			dsp->fRec112[0] = ((dsp->fRec112[1] * fTemp58) + (fTemp57 * (1.0f - fTemp58)));
			dsp->fRec111[0] = dsp->fRec112[0];
			dsp->fRec114[0] = (fTemp1 - (fSlow73 * ((fSlow74 * dsp->fRec114[2]) + (dsp->fConst117 * dsp->fRec114[1]))));
			dsp->fRec117[0] = (fTemp2 - (fSlow73 * ((dsp->fConst117 * dsp->fRec117[1]) + (fSlow74 * dsp->fRec117[2]))));
			float fTemp59 = fabsf((fSlow73 * ((dsp->fConst116 * dsp->fRec117[0]) + (dsp->fConst118 * dsp->fRec117[2]))));
			float fTemp60 = ((dsp->fRec115[1] > fTemp59)?fSlow7:fSlow6);
			dsp->fRec116[0] = ((dsp->fRec116[1] * fTemp60) + (fTemp59 * (1.0f - fTemp60)));
			dsp->fRec115[0] = dsp->fRec116[0];
			dsp->fRec118[0] = (fTemp1 - (fSlow75 * ((fSlow76 * dsp->fRec118[2]) + (dsp->fConst121 * dsp->fRec118[1]))));
			dsp->fRec121[0] = (fTemp2 - (fSlow75 * ((dsp->fConst121 * dsp->fRec121[1]) + (fSlow76 * dsp->fRec121[2]))));
			float fTemp61 = fabsf((fSlow75 * ((dsp->fConst120 * dsp->fRec121[0]) + (dsp->fConst122 * dsp->fRec121[2]))));
			float fTemp62 = ((dsp->fRec119[1] > fTemp61)?fSlow7:fSlow6);
			dsp->fRec120[0] = ((dsp->fRec120[1] * fTemp62) + (fTemp61 * (1.0f - fTemp62)));
			dsp->fRec119[0] = dsp->fRec120[0];
			dsp->fRec122[0] = (fTemp1 - (fSlow78 * ((fSlow79 * dsp->fRec122[2]) + (dsp->fConst125 * dsp->fRec122[1]))));
			dsp->fRec125[0] = (fTemp2 - (fSlow78 * ((dsp->fConst125 * dsp->fRec125[1]) + (fSlow79 * dsp->fRec125[2]))));
			float fTemp63 = fabsf((fSlow78 * ((dsp->fConst124 * dsp->fRec125[0]) + (dsp->fConst126 * dsp->fRec125[2]))));
			float fTemp64 = ((dsp->fRec123[1] > fTemp63)?fSlow7:fSlow6);
			dsp->fRec124[0] = ((dsp->fRec124[1] * fTemp64) + (fTemp63 * (1.0f - fTemp64)));
			dsp->fRec123[0] = dsp->fRec124[0];
			dsp->fRec126[0] = (fTemp1 - (fSlow80 * ((fSlow81 * dsp->fRec126[2]) + (dsp->fConst129 * dsp->fRec126[1]))));
			dsp->fRec129[0] = (fTemp2 - (fSlow80 * ((dsp->fConst129 * dsp->fRec129[1]) + (fSlow81 * dsp->fRec129[2]))));
			float fTemp65 = fabsf((fSlow80 * ((dsp->fConst128 * dsp->fRec129[0]) + (dsp->fConst130 * dsp->fRec129[2]))));
			float fTemp66 = ((dsp->fRec127[1] > fTemp65)?fSlow7:fSlow6);
			dsp->fRec128[0] = ((dsp->fRec128[1] * fTemp66) + (fTemp65 * (1.0f - fTemp66)));
			dsp->fRec127[0] = dsp->fRec128[0];
			float fTemp67 = ((((((((((((((((((((((((((((((((fSlow2 * ((dsp->fRec0[2] * (0.0f - (dsp->fConst2 * dsp->fRec3[0]))) + (dsp->fConst2 * (dsp->fRec0[0] * dsp->fRec3[0])))) + (fSlow9 * ((dsp->fRec6[2] * (0.0f - (dsp->fConst8 * dsp->fRec7[0]))) + (dsp->fConst8 * (dsp->fRec6[0] * dsp->fRec7[0]))))) + (fSlow11 * ((dsp->fRec10[2] * (0.0f - (dsp->fConst12 * dsp->fRec11[0]))) + (dsp->fConst12 * (dsp->fRec10[0] * dsp->fRec11[0]))))) + (fSlow14 * ((dsp->fRec14[2] * (0.0f - (dsp->fConst16 * dsp->fRec15[0]))) + (dsp->fConst16 * (dsp->fRec14[0] * dsp->fRec15[0]))))) + (fSlow17 * ((dsp->fRec18[2] * (0.0f - (dsp->fConst20 * dsp->fRec19[0]))) + (dsp->fConst20 * (dsp->fRec18[0] * dsp->fRec19[0]))))) + (fSlow20 * ((dsp->fRec22[2] * (0.0f - (dsp->fConst24 * dsp->fRec23[0]))) + (dsp->fConst24 * (dsp->fRec22[0] * dsp->fRec23[0]))))) + (fSlow23 * ((dsp->fRec26[2] * (0.0f - (dsp->fConst28 * dsp->fRec27[0]))) + (dsp->fConst28 * (dsp->fRec26[0] * dsp->fRec27[0]))))) + (fSlow25 * ((dsp->fRec30[2] * (0.0f - (dsp->fConst32 * dsp->fRec31[0]))) + (dsp->fConst32 * (dsp->fRec30[0] * dsp->fRec31[0]))))) + (fSlow27 * ((dsp->fRec34[2] * (0.0f - (dsp->fConst36 * dsp->fRec35[0]))) + (dsp->fConst36 * (dsp->fRec34[0] * dsp->fRec35[0]))))) + (fSlow29 * ((dsp->fRec38[2] * (0.0f - (dsp->fConst40 * dsp->fRec39[0]))) + (dsp->fConst40 * (dsp->fRec38[0] * dsp->fRec39[0]))))) + (fSlow32 * ((dsp->fRec42[2] * (0.0f - (dsp->fConst44 * dsp->fRec43[0]))) + (dsp->fConst44 * (dsp->fRec42[0] * dsp->fRec43[0]))))) + (fSlow35 * ((dsp->fRec46[2] * (0.0f - (dsp->fConst48 * dsp->fRec47[0]))) + (dsp->fConst48 * (dsp->fRec46[0] * dsp->fRec47[0]))))) + (fSlow37 * ((dsp->fRec50[2] * (0.0f - (dsp->fConst52 * dsp->fRec51[0]))) + (dsp->fConst52 * (dsp->fRec50[0] * dsp->fRec51[0]))))) + (fSlow40 * ((dsp->fRec54[2] * (0.0f - (dsp->fConst56 * dsp->fRec55[0]))) + (dsp->fConst56 * (dsp->fRec54[0] * dsp->fRec55[0]))))) + (fSlow42 * ((dsp->fRec58[2] * (0.0f - (dsp->fConst60 * dsp->fRec59[0]))) + (dsp->fConst60 * (dsp->fRec58[0] * dsp->fRec59[0]))))) + (fSlow44 * ((dsp->fRec62[2] * (0.0f - (dsp->fConst64 * dsp->fRec63[0]))) + (dsp->fConst64 * (dsp->fRec62[0] * dsp->fRec63[0]))))) + (fSlow46 * ((dsp->fRec66[2] * (0.0f - (dsp->fConst68 * dsp->fRec67[0]))) + (dsp->fConst68 * (dsp->fRec66[0] * dsp->fRec67[0]))))) + (fSlow49 * ((dsp->fRec70[2] * (0.0f - (dsp->fConst72 * dsp->fRec71[0]))) + (dsp->fConst72 * (dsp->fRec70[0] * dsp->fRec71[0]))))) + (fSlow51 * ((dsp->fRec74[2] * (0.0f - (dsp->fConst76 * dsp->fRec75[0]))) + (dsp->fConst76 * (dsp->fRec74[0] * dsp->fRec75[0]))))) + (fSlow53 * ((dsp->fRec78[2] * (0.0f - (dsp->fConst80 * dsp->fRec79[0]))) + (dsp->fConst80 * (dsp->fRec78[0] * dsp->fRec79[0]))))) + (fSlow55 * ((dsp->fRec82[2] * (0.0f - (dsp->fConst84 * dsp->fRec83[0]))) + (dsp->fConst84 * (dsp->fRec82[0] * dsp->fRec83[0]))))) + (fSlow57 * ((dsp->fRec86[2] * (0.0f - (dsp->fConst88 * dsp->fRec87[0]))) + (dsp->fConst88 * (dsp->fRec86[0] * dsp->fRec87[0]))))) + (fSlow59 * ((dsp->fRec90[2] * (0.0f - (dsp->fConst92 * dsp->fRec91[0]))) + (dsp->fConst92 * (dsp->fRec90[0] * dsp->fRec91[0]))))) + (fSlow62 * ((dsp->fRec94[2] * (0.0f - (dsp->fConst96 * dsp->fRec95[0]))) + (dsp->fConst96 * (dsp->fRec94[0] * dsp->fRec95[0]))))) + (fSlow64 * ((dsp->fRec98[2] * (0.0f - (dsp->fConst100 * dsp->fRec99[0]))) + (dsp->fConst100 * (dsp->fRec98[0] * dsp->fRec99[0]))))) + (fSlow66 * ((dsp->fRec102[2] * (0.0f - (dsp->fConst104 * dsp->fRec103[0]))) + (dsp->fConst104 * (dsp->fRec102[0] * dsp->fRec103[0]))))) + (fSlow68 * ((dsp->fRec106[2] * (0.0f - (dsp->fConst108 * dsp->fRec107[0]))) + (dsp->fConst108 * (dsp->fRec106[0] * dsp->fRec107[0]))))) + (fSlow71 * ((dsp->fRec110[2] * (0.0f - (dsp->fConst112 * dsp->fRec111[0]))) + (dsp->fConst112 * (dsp->fRec110[0] * dsp->fRec111[0]))))) + (fSlow73 * ((dsp->fRec114[2] * (0.0f - (dsp->fConst116 * dsp->fRec115[0]))) + (dsp->fConst116 * (dsp->fRec114[0] * dsp->fRec115[0]))))) + (fSlow75 * ((dsp->fRec118[2] * (0.0f - (dsp->fConst120 * dsp->fRec119[0]))) + (dsp->fConst120 * (dsp->fRec118[0] * dsp->fRec119[0]))))) + (fSlow78 * ((dsp->fRec122[2] * (0.0f - (dsp->fConst124 * dsp->fRec123[0]))) + (dsp->fConst124 * (dsp->fRec122[0] * dsp->fRec123[0]))))) + (fSlow80 * ((dsp->fRec126[2] * (0.0f - (dsp->fConst128 * dsp->fRec127[0]))) + (dsp->fConst128 * (dsp->fRec126[0] * dsp->fRec127[0])))));
			output0[i] = (FAUSTFLOAT)fTemp67;
			output1[i] = (FAUSTFLOAT)fTemp67;
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fVec0[1] = dsp->fVec0[0];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec0[2] = dsp->fRec0[1];
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec5[2] = dsp->fRec5[1];
			dsp->fRec5[1] = dsp->fRec5[0];
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fRec3[1] = dsp->fRec3[0];
			dsp->fRec6[2] = dsp->fRec6[1];
			dsp->fRec6[1] = dsp->fRec6[0];
			dsp->fRec9[2] = dsp->fRec9[1];
			dsp->fRec9[1] = dsp->fRec9[0];
			dsp->fRec8[1] = dsp->fRec8[0];
			dsp->fRec7[1] = dsp->fRec7[0];
			dsp->fRec10[2] = dsp->fRec10[1];
			dsp->fRec10[1] = dsp->fRec10[0];
			dsp->fRec13[2] = dsp->fRec13[1];
			dsp->fRec13[1] = dsp->fRec13[0];
			dsp->fRec12[1] = dsp->fRec12[0];
			dsp->fRec11[1] = dsp->fRec11[0];
			dsp->fRec14[2] = dsp->fRec14[1];
			dsp->fRec14[1] = dsp->fRec14[0];
			dsp->fRec17[2] = dsp->fRec17[1];
			dsp->fRec17[1] = dsp->fRec17[0];
			dsp->fRec16[1] = dsp->fRec16[0];
			dsp->fRec15[1] = dsp->fRec15[0];
			dsp->fRec18[2] = dsp->fRec18[1];
			dsp->fRec18[1] = dsp->fRec18[0];
			dsp->fRec21[2] = dsp->fRec21[1];
			dsp->fRec21[1] = dsp->fRec21[0];
			dsp->fRec20[1] = dsp->fRec20[0];
			dsp->fRec19[1] = dsp->fRec19[0];
			dsp->fRec22[2] = dsp->fRec22[1];
			dsp->fRec22[1] = dsp->fRec22[0];
			dsp->fRec25[2] = dsp->fRec25[1];
			dsp->fRec25[1] = dsp->fRec25[0];
			dsp->fRec24[1] = dsp->fRec24[0];
			dsp->fRec23[1] = dsp->fRec23[0];
			dsp->fRec26[2] = dsp->fRec26[1];
			dsp->fRec26[1] = dsp->fRec26[0];
			dsp->fRec29[2] = dsp->fRec29[1];
			dsp->fRec29[1] = dsp->fRec29[0];
			dsp->fRec28[1] = dsp->fRec28[0];
			dsp->fRec27[1] = dsp->fRec27[0];
			dsp->fRec30[2] = dsp->fRec30[1];
			dsp->fRec30[1] = dsp->fRec30[0];
			dsp->fRec33[2] = dsp->fRec33[1];
			dsp->fRec33[1] = dsp->fRec33[0];
			dsp->fRec32[1] = dsp->fRec32[0];
			dsp->fRec31[1] = dsp->fRec31[0];
			dsp->fRec34[2] = dsp->fRec34[1];
			dsp->fRec34[1] = dsp->fRec34[0];
			dsp->fRec37[2] = dsp->fRec37[1];
			dsp->fRec37[1] = dsp->fRec37[0];
			dsp->fRec36[1] = dsp->fRec36[0];
			dsp->fRec35[1] = dsp->fRec35[0];
			dsp->fRec38[2] = dsp->fRec38[1];
			dsp->fRec38[1] = dsp->fRec38[0];
			dsp->fRec41[2] = dsp->fRec41[1];
			dsp->fRec41[1] = dsp->fRec41[0];
			dsp->fRec40[1] = dsp->fRec40[0];
			dsp->fRec39[1] = dsp->fRec39[0];
			dsp->fRec42[2] = dsp->fRec42[1];
			dsp->fRec42[1] = dsp->fRec42[0];
			dsp->fRec45[2] = dsp->fRec45[1];
			dsp->fRec45[1] = dsp->fRec45[0];
			dsp->fRec44[1] = dsp->fRec44[0];
			dsp->fRec43[1] = dsp->fRec43[0];
			dsp->fRec46[2] = dsp->fRec46[1];
			dsp->fRec46[1] = dsp->fRec46[0];
			dsp->fRec49[2] = dsp->fRec49[1];
			dsp->fRec49[1] = dsp->fRec49[0];
			dsp->fRec48[1] = dsp->fRec48[0];
			dsp->fRec47[1] = dsp->fRec47[0];
			dsp->fRec50[2] = dsp->fRec50[1];
			dsp->fRec50[1] = dsp->fRec50[0];
			dsp->fRec53[2] = dsp->fRec53[1];
			dsp->fRec53[1] = dsp->fRec53[0];
			dsp->fRec52[1] = dsp->fRec52[0];
			dsp->fRec51[1] = dsp->fRec51[0];
			dsp->fRec54[2] = dsp->fRec54[1];
			dsp->fRec54[1] = dsp->fRec54[0];
			dsp->fRec57[2] = dsp->fRec57[1];
			dsp->fRec57[1] = dsp->fRec57[0];
			dsp->fRec56[1] = dsp->fRec56[0];
			dsp->fRec55[1] = dsp->fRec55[0];
			dsp->fRec58[2] = dsp->fRec58[1];
			dsp->fRec58[1] = dsp->fRec58[0];
			dsp->fRec61[2] = dsp->fRec61[1];
			dsp->fRec61[1] = dsp->fRec61[0];
			dsp->fRec60[1] = dsp->fRec60[0];
			dsp->fRec59[1] = dsp->fRec59[0];
			dsp->fRec62[2] = dsp->fRec62[1];
			dsp->fRec62[1] = dsp->fRec62[0];
			dsp->fRec65[2] = dsp->fRec65[1];
			dsp->fRec65[1] = dsp->fRec65[0];
			dsp->fRec64[1] = dsp->fRec64[0];
			dsp->fRec63[1] = dsp->fRec63[0];
			dsp->fRec66[2] = dsp->fRec66[1];
			dsp->fRec66[1] = dsp->fRec66[0];
			dsp->fRec69[2] = dsp->fRec69[1];
			dsp->fRec69[1] = dsp->fRec69[0];
			dsp->fRec68[1] = dsp->fRec68[0];
			dsp->fRec67[1] = dsp->fRec67[0];
			dsp->fRec70[2] = dsp->fRec70[1];
			dsp->fRec70[1] = dsp->fRec70[0];
			dsp->fRec73[2] = dsp->fRec73[1];
			dsp->fRec73[1] = dsp->fRec73[0];
			dsp->fRec72[1] = dsp->fRec72[0];
			dsp->fRec71[1] = dsp->fRec71[0];
			dsp->fRec74[2] = dsp->fRec74[1];
			dsp->fRec74[1] = dsp->fRec74[0];
			dsp->fRec77[2] = dsp->fRec77[1];
			dsp->fRec77[1] = dsp->fRec77[0];
			dsp->fRec76[1] = dsp->fRec76[0];
			dsp->fRec75[1] = dsp->fRec75[0];
			dsp->fRec78[2] = dsp->fRec78[1];
			dsp->fRec78[1] = dsp->fRec78[0];
			dsp->fRec81[2] = dsp->fRec81[1];
			dsp->fRec81[1] = dsp->fRec81[0];
			dsp->fRec80[1] = dsp->fRec80[0];
			dsp->fRec79[1] = dsp->fRec79[0];
			dsp->fRec82[2] = dsp->fRec82[1];
			dsp->fRec82[1] = dsp->fRec82[0];
			dsp->fRec85[2] = dsp->fRec85[1];
			dsp->fRec85[1] = dsp->fRec85[0];
			dsp->fRec84[1] = dsp->fRec84[0];
			dsp->fRec83[1] = dsp->fRec83[0];
			dsp->fRec86[2] = dsp->fRec86[1];
			dsp->fRec86[1] = dsp->fRec86[0];
			dsp->fRec89[2] = dsp->fRec89[1];
			dsp->fRec89[1] = dsp->fRec89[0];
			dsp->fRec88[1] = dsp->fRec88[0];
			dsp->fRec87[1] = dsp->fRec87[0];
			dsp->fRec90[2] = dsp->fRec90[1];
			dsp->fRec90[1] = dsp->fRec90[0];
			dsp->fRec93[2] = dsp->fRec93[1];
			dsp->fRec93[1] = dsp->fRec93[0];
			dsp->fRec92[1] = dsp->fRec92[0];
			dsp->fRec91[1] = dsp->fRec91[0];
			dsp->fRec94[2] = dsp->fRec94[1];
			dsp->fRec94[1] = dsp->fRec94[0];
			dsp->fRec97[2] = dsp->fRec97[1];
			dsp->fRec97[1] = dsp->fRec97[0];
			dsp->fRec96[1] = dsp->fRec96[0];
			dsp->fRec95[1] = dsp->fRec95[0];
			dsp->fRec98[2] = dsp->fRec98[1];
			dsp->fRec98[1] = dsp->fRec98[0];
			dsp->fRec101[2] = dsp->fRec101[1];
			dsp->fRec101[1] = dsp->fRec101[0];
			dsp->fRec100[1] = dsp->fRec100[0];
			dsp->fRec99[1] = dsp->fRec99[0];
			dsp->fRec102[2] = dsp->fRec102[1];
			dsp->fRec102[1] = dsp->fRec102[0];
			dsp->fRec105[2] = dsp->fRec105[1];
			dsp->fRec105[1] = dsp->fRec105[0];
			dsp->fRec104[1] = dsp->fRec104[0];
			dsp->fRec103[1] = dsp->fRec103[0];
			dsp->fRec106[2] = dsp->fRec106[1];
			dsp->fRec106[1] = dsp->fRec106[0];
			dsp->fRec109[2] = dsp->fRec109[1];
			dsp->fRec109[1] = dsp->fRec109[0];
			dsp->fRec108[1] = dsp->fRec108[0];
			dsp->fRec107[1] = dsp->fRec107[0];
			dsp->fRec110[2] = dsp->fRec110[1];
			dsp->fRec110[1] = dsp->fRec110[0];
			dsp->fRec113[2] = dsp->fRec113[1];
			dsp->fRec113[1] = dsp->fRec113[0];
			dsp->fRec112[1] = dsp->fRec112[0];
			dsp->fRec111[1] = dsp->fRec111[0];
			dsp->fRec114[2] = dsp->fRec114[1];
			dsp->fRec114[1] = dsp->fRec114[0];
			dsp->fRec117[2] = dsp->fRec117[1];
			dsp->fRec117[1] = dsp->fRec117[0];
			dsp->fRec116[1] = dsp->fRec116[0];
			dsp->fRec115[1] = dsp->fRec115[0];
			dsp->fRec118[2] = dsp->fRec118[1];
			dsp->fRec118[1] = dsp->fRec118[0];
			dsp->fRec121[2] = dsp->fRec121[1];
			dsp->fRec121[1] = dsp->fRec121[0];
			dsp->fRec120[1] = dsp->fRec120[0];
			dsp->fRec119[1] = dsp->fRec119[0];
			dsp->fRec122[2] = dsp->fRec122[1];
			dsp->fRec122[1] = dsp->fRec122[0];
			dsp->fRec125[2] = dsp->fRec125[1];
			dsp->fRec125[1] = dsp->fRec125[0];
			dsp->fRec124[1] = dsp->fRec124[0];
			dsp->fRec123[1] = dsp->fRec123[0];
			dsp->fRec126[2] = dsp->fRec126[1];
			dsp->fRec126[1] = dsp->fRec126[0];
			dsp->fRec129[2] = dsp->fRec129[1];
			dsp->fRec129[1] = dsp->fRec129[0];
			dsp->fRec128[1] = dsp->fRec128[0];
			dsp->fRec127[1] = dsp->fRec127[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
