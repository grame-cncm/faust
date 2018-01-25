/* ------------------------------------------------------------
name: "filterBank"
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
	
	FAUSTFLOAT fCheckbox0;
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	float fConst7;
	float fConst8;
	float fConst9;
	float fConst10;
	float fVec0[2];
	float fConst11;
	float fRec10[2];
	float fConst12;
	float fConst13;
	float fRec9[3];
	float fConst14;
	float fRec8[3];
	float fConst15;
	float fConst16;
	float fConst17;
	float fConst18;
	float fConst19;
	float fConst20;
	float fRec7[3];
	float fConst21;
	float fConst22;
	float fConst23;
	float fConst24;
	float fConst25;
	float fConst26;
	float fRec6[3];
	float fConst27;
	float fConst28;
	float fConst29;
	float fConst30;
	float fConst31;
	float fConst32;
	float fRec5[3];
	float fConst33;
	float fConst34;
	float fConst35;
	float fConst36;
	float fConst37;
	float fConst38;
	float fRec4[3];
	float fConst39;
	float fConst40;
	float fConst41;
	float fConst42;
	float fConst43;
	float fConst44;
	float fRec3[3];
	float fConst45;
	float fConst46;
	float fConst47;
	float fConst48;
	float fConst49;
	float fConst50;
	float fRec2[3];
	float fConst51;
	float fConst52;
	float fConst53;
	float fConst54;
	float fConst55;
	float fConst56;
	float fRec1[3];
	float fConst57;
	float fConst58;
	float fConst59;
	float fConst60;
	float fConst61;
	float fConst62;
	float fRec0[3];
	FAUSTFLOAT fVslider0;
	float fRec11[2];
	float fConst63;
	float fConst64;
	float fConst65;
	float fConst66;
	float fConst67;
	float fConst68;
	float fConst69;
	float fRec24[2];
	float fRec23[3];
	float fRec22[3];
	float fVec1[2];
	float fConst70;
	float fRec21[2];
	float fConst71;
	float fRec20[3];
	float fConst72;
	float fRec19[3];
	float fRec18[3];
	float fRec17[3];
	float fRec16[3];
	float fRec15[3];
	float fRec14[3];
	float fRec13[3];
	float fRec12[3];
	FAUSTFLOAT fVslider1;
	float fRec25[2];
	float fConst73;
	float fConst74;
	float fConst75;
	float fConst76;
	float fConst77;
	float fConst78;
	float fConst79;
	float fRec37[2];
	float fRec36[3];
	float fRec35[3];
	float fVec2[2];
	float fConst80;
	float fRec34[2];
	float fConst81;
	float fRec33[3];
	float fConst82;
	float fRec32[3];
	float fRec31[3];
	float fRec30[3];
	float fRec29[3];
	float fRec28[3];
	float fRec27[3];
	float fRec26[3];
	FAUSTFLOAT fVslider2;
	float fRec38[2];
	float fConst83;
	float fConst84;
	float fConst85;
	float fConst86;
	float fConst87;
	float fConst88;
	float fConst89;
	float fRec49[2];
	float fRec48[3];
	float fRec47[3];
	float fVec3[2];
	float fConst90;
	float fRec46[2];
	float fConst91;
	float fRec45[3];
	float fConst92;
	float fRec44[3];
	float fRec43[3];
	float fRec42[3];
	float fRec41[3];
	float fRec40[3];
	float fRec39[3];
	FAUSTFLOAT fVslider3;
	float fRec50[2];
	float fConst93;
	float fConst94;
	float fConst95;
	float fConst96;
	float fConst97;
	float fConst98;
	float fConst99;
	float fRec60[2];
	float fRec59[3];
	float fRec58[3];
	float fVec4[2];
	float fConst100;
	float fRec57[2];
	float fConst101;
	float fRec56[3];
	float fConst102;
	float fRec55[3];
	float fRec54[3];
	float fRec53[3];
	float fRec52[3];
	float fRec51[3];
	FAUSTFLOAT fVslider4;
	float fRec61[2];
	float fConst103;
	float fConst104;
	float fConst105;
	float fConst106;
	float fConst107;
	float fConst108;
	float fConst109;
	float fRec70[2];
	float fRec69[3];
	float fRec68[3];
	float fVec5[2];
	float fConst110;
	float fRec67[2];
	float fConst111;
	float fRec66[3];
	float fConst112;
	float fRec65[3];
	float fRec64[3];
	float fRec63[3];
	float fRec62[3];
	FAUSTFLOAT fVslider5;
	float fRec71[2];
	float fConst113;
	float fConst114;
	float fConst115;
	float fConst116;
	float fConst117;
	float fConst118;
	float fConst119;
	float fRec79[2];
	float fRec78[3];
	float fRec77[3];
	float fVec6[2];
	float fConst120;
	float fRec76[2];
	float fConst121;
	float fRec75[3];
	float fConst122;
	float fRec74[3];
	float fRec73[3];
	float fRec72[3];
	FAUSTFLOAT fVslider6;
	float fRec80[2];
	float fConst123;
	float fConst124;
	float fConst125;
	float fConst126;
	float fConst127;
	float fConst128;
	float fConst129;
	float fRec87[2];
	float fRec86[3];
	float fRec85[3];
	float fVec7[2];
	float fConst130;
	float fRec84[2];
	float fConst131;
	float fRec83[3];
	float fConst132;
	float fRec82[3];
	float fRec81[3];
	FAUSTFLOAT fVslider7;
	float fRec88[2];
	float fConst133;
	float fConst134;
	float fConst135;
	float fConst136;
	float fConst137;
	float fConst138;
	float fRec94[2];
	float fRec93[3];
	float fRec92[3];
	float fVec8[2];
	float fConst139;
	float fRec91[2];
	float fConst140;
	float fRec90[3];
	float fConst141;
	float fRec89[3];
	FAUSTFLOAT fVslider8;
	float fRec95[2];
	float fRec98[2];
	float fRec97[3];
	float fRec96[3];
	FAUSTFLOAT fVslider9;
	float fRec99[2];
	
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
	m->declare(m->metaInterface, "basics.lib/name", "Faust Basic Element Library");
	m->declare(m->metaInterface, "basics.lib/version", "0.0");
	m->declare(m->metaInterface, "description", "Graphic Equalizer consisting of a filter-bank driving a bank of faders");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "filterBank");
	m->declare(m->metaInterface, "signals.lib/name", "Faust Signal Routing Library");
	m->declare(m->metaInterface, "signals.lib/version", "0.0");
}

int getSampleRatemydsp(mydsp* dsp) { return dsp->fSamplingFreq; }

int getNumInputsmydsp(mydsp* dsp) {
	return 1;
	
}
int getNumOutputsmydsp(mydsp* dsp) {
	return 1;
	
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
	dsp->fCheckbox0 = (FAUSTFLOAT)0.0f;
	dsp->fVslider0 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider1 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider2 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider3 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider4 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider5 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider6 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider7 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider8 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider9 = (FAUSTFLOAT)-10.0f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			dsp->fVec0[l0] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			dsp->fRec10[l1] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 3); l2 = (l2 + 1)) {
			dsp->fRec9[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 3); l3 = (l3 + 1)) {
			dsp->fRec8[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 3); l4 = (l4 + 1)) {
			dsp->fRec7[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 3); l5 = (l5 + 1)) {
			dsp->fRec6[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 3); l6 = (l6 + 1)) {
			dsp->fRec5[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			dsp->fRec4[l7] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
			dsp->fRec3[l8] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 3); l9 = (l9 + 1)) {
			dsp->fRec2[l9] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 3); l10 = (l10 + 1)) {
			dsp->fRec1[l10] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 3); l11 = (l11 + 1)) {
			dsp->fRec0[l11] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			dsp->fRec11[l12] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l13;
		for (l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			dsp->fRec24[l13] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l14;
		for (l14 = 0; (l14 < 3); l14 = (l14 + 1)) {
			dsp->fRec23[l14] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l15;
		for (l15 = 0; (l15 < 3); l15 = (l15 + 1)) {
			dsp->fRec22[l15] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l16;
		for (l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			dsp->fVec1[l16] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l17;
		for (l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			dsp->fRec21[l17] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l18;
		for (l18 = 0; (l18 < 3); l18 = (l18 + 1)) {
			dsp->fRec20[l18] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l19;
		for (l19 = 0; (l19 < 3); l19 = (l19 + 1)) {
			dsp->fRec19[l19] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l20;
		for (l20 = 0; (l20 < 3); l20 = (l20 + 1)) {
			dsp->fRec18[l20] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l21;
		for (l21 = 0; (l21 < 3); l21 = (l21 + 1)) {
			dsp->fRec17[l21] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l22;
		for (l22 = 0; (l22 < 3); l22 = (l22 + 1)) {
			dsp->fRec16[l22] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l23;
		for (l23 = 0; (l23 < 3); l23 = (l23 + 1)) {
			dsp->fRec15[l23] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l24;
		for (l24 = 0; (l24 < 3); l24 = (l24 + 1)) {
			dsp->fRec14[l24] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l25;
		for (l25 = 0; (l25 < 3); l25 = (l25 + 1)) {
			dsp->fRec13[l25] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l26;
		for (l26 = 0; (l26 < 3); l26 = (l26 + 1)) {
			dsp->fRec12[l26] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l27;
		for (l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			dsp->fRec25[l27] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l28;
		for (l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			dsp->fRec37[l28] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l29;
		for (l29 = 0; (l29 < 3); l29 = (l29 + 1)) {
			dsp->fRec36[l29] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l30;
		for (l30 = 0; (l30 < 3); l30 = (l30 + 1)) {
			dsp->fRec35[l30] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l31;
		for (l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			dsp->fVec2[l31] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l32;
		for (l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			dsp->fRec34[l32] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l33;
		for (l33 = 0; (l33 < 3); l33 = (l33 + 1)) {
			dsp->fRec33[l33] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l34;
		for (l34 = 0; (l34 < 3); l34 = (l34 + 1)) {
			dsp->fRec32[l34] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l35;
		for (l35 = 0; (l35 < 3); l35 = (l35 + 1)) {
			dsp->fRec31[l35] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l36;
		for (l36 = 0; (l36 < 3); l36 = (l36 + 1)) {
			dsp->fRec30[l36] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l37;
		for (l37 = 0; (l37 < 3); l37 = (l37 + 1)) {
			dsp->fRec29[l37] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l38;
		for (l38 = 0; (l38 < 3); l38 = (l38 + 1)) {
			dsp->fRec28[l38] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l39;
		for (l39 = 0; (l39 < 3); l39 = (l39 + 1)) {
			dsp->fRec27[l39] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l40;
		for (l40 = 0; (l40 < 3); l40 = (l40 + 1)) {
			dsp->fRec26[l40] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l41;
		for (l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			dsp->fRec38[l41] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l42;
		for (l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			dsp->fRec49[l42] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l43;
		for (l43 = 0; (l43 < 3); l43 = (l43 + 1)) {
			dsp->fRec48[l43] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l44;
		for (l44 = 0; (l44 < 3); l44 = (l44 + 1)) {
			dsp->fRec47[l44] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l45;
		for (l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			dsp->fVec3[l45] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l46;
		for (l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			dsp->fRec46[l46] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l47;
		for (l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			dsp->fRec45[l47] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l48;
		for (l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			dsp->fRec44[l48] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l49;
		for (l49 = 0; (l49 < 3); l49 = (l49 + 1)) {
			dsp->fRec43[l49] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l50;
		for (l50 = 0; (l50 < 3); l50 = (l50 + 1)) {
			dsp->fRec42[l50] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l51;
		for (l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			dsp->fRec41[l51] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l52;
		for (l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			dsp->fRec40[l52] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l53;
		for (l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			dsp->fRec39[l53] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l54;
		for (l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
			dsp->fRec50[l54] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l55;
		for (l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			dsp->fRec60[l55] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l56;
		for (l56 = 0; (l56 < 3); l56 = (l56 + 1)) {
			dsp->fRec59[l56] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l57;
		for (l57 = 0; (l57 < 3); l57 = (l57 + 1)) {
			dsp->fRec58[l57] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l58;
		for (l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			dsp->fVec4[l58] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l59;
		for (l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			dsp->fRec57[l59] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l60;
		for (l60 = 0; (l60 < 3); l60 = (l60 + 1)) {
			dsp->fRec56[l60] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l61;
		for (l61 = 0; (l61 < 3); l61 = (l61 + 1)) {
			dsp->fRec55[l61] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l62;
		for (l62 = 0; (l62 < 3); l62 = (l62 + 1)) {
			dsp->fRec54[l62] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l63;
		for (l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			dsp->fRec53[l63] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l64;
		for (l64 = 0; (l64 < 3); l64 = (l64 + 1)) {
			dsp->fRec52[l64] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l65;
		for (l65 = 0; (l65 < 3); l65 = (l65 + 1)) {
			dsp->fRec51[l65] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l66;
		for (l66 = 0; (l66 < 2); l66 = (l66 + 1)) {
			dsp->fRec61[l66] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l67;
		for (l67 = 0; (l67 < 2); l67 = (l67 + 1)) {
			dsp->fRec70[l67] = 0.0f;
			
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
		for (l69 = 0; (l69 < 3); l69 = (l69 + 1)) {
			dsp->fRec68[l69] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l70;
		for (l70 = 0; (l70 < 2); l70 = (l70 + 1)) {
			dsp->fVec5[l70] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l71;
		for (l71 = 0; (l71 < 2); l71 = (l71 + 1)) {
			dsp->fRec67[l71] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l72;
		for (l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			dsp->fRec66[l72] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l73;
		for (l73 = 0; (l73 < 3); l73 = (l73 + 1)) {
			dsp->fRec65[l73] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l74;
		for (l74 = 0; (l74 < 3); l74 = (l74 + 1)) {
			dsp->fRec64[l74] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l75;
		for (l75 = 0; (l75 < 3); l75 = (l75 + 1)) {
			dsp->fRec63[l75] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l76;
		for (l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			dsp->fRec62[l76] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l77;
		for (l77 = 0; (l77 < 2); l77 = (l77 + 1)) {
			dsp->fRec71[l77] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l78;
		for (l78 = 0; (l78 < 2); l78 = (l78 + 1)) {
			dsp->fRec79[l78] = 0.0f;
			
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
			dsp->fRec77[l80] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l81;
		for (l81 = 0; (l81 < 2); l81 = (l81 + 1)) {
			dsp->fVec6[l81] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l82;
		for (l82 = 0; (l82 < 2); l82 = (l82 + 1)) {
			dsp->fRec76[l82] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l83;
		for (l83 = 0; (l83 < 3); l83 = (l83 + 1)) {
			dsp->fRec75[l83] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l84;
		for (l84 = 0; (l84 < 3); l84 = (l84 + 1)) {
			dsp->fRec74[l84] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l85;
		for (l85 = 0; (l85 < 3); l85 = (l85 + 1)) {
			dsp->fRec73[l85] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l86;
		for (l86 = 0; (l86 < 3); l86 = (l86 + 1)) {
			dsp->fRec72[l86] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l87;
		for (l87 = 0; (l87 < 2); l87 = (l87 + 1)) {
			dsp->fRec80[l87] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l88;
		for (l88 = 0; (l88 < 2); l88 = (l88 + 1)) {
			dsp->fRec87[l88] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l89;
		for (l89 = 0; (l89 < 3); l89 = (l89 + 1)) {
			dsp->fRec86[l89] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l90;
		for (l90 = 0; (l90 < 3); l90 = (l90 + 1)) {
			dsp->fRec85[l90] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l91;
		for (l91 = 0; (l91 < 2); l91 = (l91 + 1)) {
			dsp->fVec7[l91] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l92;
		for (l92 = 0; (l92 < 2); l92 = (l92 + 1)) {
			dsp->fRec84[l92] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l93;
		for (l93 = 0; (l93 < 3); l93 = (l93 + 1)) {
			dsp->fRec83[l93] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l94;
		for (l94 = 0; (l94 < 3); l94 = (l94 + 1)) {
			dsp->fRec82[l94] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l95;
		for (l95 = 0; (l95 < 3); l95 = (l95 + 1)) {
			dsp->fRec81[l95] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l96;
		for (l96 = 0; (l96 < 2); l96 = (l96 + 1)) {
			dsp->fRec88[l96] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l97;
		for (l97 = 0; (l97 < 2); l97 = (l97 + 1)) {
			dsp->fRec94[l97] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l98;
		for (l98 = 0; (l98 < 3); l98 = (l98 + 1)) {
			dsp->fRec93[l98] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l99;
		for (l99 = 0; (l99 < 3); l99 = (l99 + 1)) {
			dsp->fRec92[l99] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l100;
		for (l100 = 0; (l100 < 2); l100 = (l100 + 1)) {
			dsp->fVec8[l100] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l101;
		for (l101 = 0; (l101 < 2); l101 = (l101 + 1)) {
			dsp->fRec91[l101] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l102;
		for (l102 = 0; (l102 < 3); l102 = (l102 + 1)) {
			dsp->fRec90[l102] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l103;
		for (l103 = 0; (l103 < 3); l103 = (l103 + 1)) {
			dsp->fRec89[l103] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l104;
		for (l104 = 0; (l104 < 2); l104 = (l104 + 1)) {
			dsp->fRec95[l104] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l105;
		for (l105 = 0; (l105 < 2); l105 = (l105 + 1)) {
			dsp->fRec98[l105] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l106;
		for (l106 = 0; (l106 < 3); l106 = (l106 + 1)) {
			dsp->fRec97[l106] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l107;
		for (l107 = 0; (l107 < 3); l107 = (l107 + 1)) {
			dsp->fRec96[l107] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l108;
		for (l108 = 0; (l108 < 2); l108 = (l108 + 1)) {
			dsp->fRec99[l108] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = tanf((31415.9258f / dsp->fConst0));
	dsp->fConst2 = (1.0f / dsp->fConst1);
	dsp->fConst3 = (((dsp->fConst2 + 0.618034005f) / dsp->fConst1) + 1.0f);
	dsp->fConst4 = (1.0f / dsp->fConst3);
	dsp->fConst5 = (1.0f / mydsp_faustpower2_f(dsp->fConst1));
	dsp->fConst6 = (2.0f * (0.0f - dsp->fConst5));
	dsp->fConst7 = (1.0f / (((dsp->fConst2 + 1.61803401f) / dsp->fConst1) + 1.0f));
	dsp->fConst8 = (dsp->fConst2 + 1.0f);
	dsp->fConst9 = (0.0f - ((1.0f - dsp->fConst2) / dsp->fConst8));
	dsp->fConst10 = (1.0f / dsp->fConst8);
	dsp->fConst11 = (0.0f - dsp->fConst2);
	dsp->fConst12 = (2.0f * (1.0f - dsp->fConst5));
	dsp->fConst13 = (((dsp->fConst2 + -1.61803401f) / dsp->fConst1) + 1.0f);
	dsp->fConst14 = (((dsp->fConst2 + -0.618034005f) / dsp->fConst1) + 1.0f);
	dsp->fConst15 = tanf((122.71846f / dsp->fConst0));
	dsp->fConst16 = (1.0f / dsp->fConst15);
	dsp->fConst17 = (1.0f / (((dsp->fConst16 + 1.61803401f) / dsp->fConst15) + 1.0f));
	dsp->fConst18 = (((dsp->fConst16 + -1.61803401f) / dsp->fConst15) + 1.0f);
	dsp->fConst19 = (1.0f / mydsp_faustpower2_f(dsp->fConst15));
	dsp->fConst20 = (2.0f * (1.0f - dsp->fConst19));
	dsp->fConst21 = tanf((245.43692f / dsp->fConst0));
	dsp->fConst22 = (1.0f / dsp->fConst21);
	dsp->fConst23 = (1.0f / (((dsp->fConst22 + 1.61803401f) / dsp->fConst21) + 1.0f));
	dsp->fConst24 = (((dsp->fConst22 + -1.61803401f) / dsp->fConst21) + 1.0f);
	dsp->fConst25 = (1.0f / mydsp_faustpower2_f(dsp->fConst21));
	dsp->fConst26 = (2.0f * (1.0f - dsp->fConst25));
	dsp->fConst27 = tanf((490.87384f / dsp->fConst0));
	dsp->fConst28 = (1.0f / dsp->fConst27);
	dsp->fConst29 = (1.0f / (((dsp->fConst28 + 1.61803401f) / dsp->fConst27) + 1.0f));
	dsp->fConst30 = (((dsp->fConst28 + -1.61803401f) / dsp->fConst27) + 1.0f);
	dsp->fConst31 = (1.0f / mydsp_faustpower2_f(dsp->fConst27));
	dsp->fConst32 = (2.0f * (1.0f - dsp->fConst31));
	dsp->fConst33 = tanf((981.747681f / dsp->fConst0));
	dsp->fConst34 = (1.0f / dsp->fConst33);
	dsp->fConst35 = (1.0f / (((dsp->fConst34 + 1.61803401f) / dsp->fConst33) + 1.0f));
	dsp->fConst36 = (((dsp->fConst34 + -1.61803401f) / dsp->fConst33) + 1.0f);
	dsp->fConst37 = (1.0f / mydsp_faustpower2_f(dsp->fConst33));
	dsp->fConst38 = (2.0f * (1.0f - dsp->fConst37));
	dsp->fConst39 = tanf((1963.49536f / dsp->fConst0));
	dsp->fConst40 = (1.0f / dsp->fConst39);
	dsp->fConst41 = (1.0f / (((dsp->fConst40 + 1.61803401f) / dsp->fConst39) + 1.0f));
	dsp->fConst42 = (((dsp->fConst40 + -1.61803401f) / dsp->fConst39) + 1.0f);
	dsp->fConst43 = (1.0f / mydsp_faustpower2_f(dsp->fConst39));
	dsp->fConst44 = (2.0f * (1.0f - dsp->fConst43));
	dsp->fConst45 = tanf((3926.99072f / dsp->fConst0));
	dsp->fConst46 = (1.0f / dsp->fConst45);
	dsp->fConst47 = (1.0f / (((dsp->fConst46 + 1.61803401f) / dsp->fConst45) + 1.0f));
	dsp->fConst48 = (((dsp->fConst46 + -1.61803401f) / dsp->fConst45) + 1.0f);
	dsp->fConst49 = (1.0f / mydsp_faustpower2_f(dsp->fConst45));
	dsp->fConst50 = (2.0f * (1.0f - dsp->fConst49));
	dsp->fConst51 = tanf((7853.98145f / dsp->fConst0));
	dsp->fConst52 = (1.0f / dsp->fConst51);
	dsp->fConst53 = (1.0f / (((dsp->fConst52 + 1.61803401f) / dsp->fConst51) + 1.0f));
	dsp->fConst54 = (((dsp->fConst52 + -1.61803401f) / dsp->fConst51) + 1.0f);
	dsp->fConst55 = (1.0f / mydsp_faustpower2_f(dsp->fConst51));
	dsp->fConst56 = (2.0f * (1.0f - dsp->fConst55));
	dsp->fConst57 = tanf((15707.9629f / dsp->fConst0));
	dsp->fConst58 = (1.0f / dsp->fConst57);
	dsp->fConst59 = (1.0f / (((dsp->fConst58 + 1.61803401f) / dsp->fConst57) + 1.0f));
	dsp->fConst60 = (((dsp->fConst58 + -1.61803401f) / dsp->fConst57) + 1.0f);
	dsp->fConst61 = (1.0f / mydsp_faustpower2_f(dsp->fConst57));
	dsp->fConst62 = (2.0f * (1.0f - dsp->fConst61));
	dsp->fConst63 = (((dsp->fConst58 + 0.618034005f) / dsp->fConst57) + 1.0f);
	dsp->fConst64 = (1.0f / dsp->fConst63);
	dsp->fConst65 = (2.0f * (0.0f - dsp->fConst61));
	dsp->fConst66 = (1.0f / (((dsp->fConst58 + 1.61803401f) / dsp->fConst57) + 1.0f));
	dsp->fConst67 = (dsp->fConst58 + 1.0f);
	dsp->fConst68 = (0.0f - ((1.0f - dsp->fConst58) / dsp->fConst67));
	dsp->fConst69 = (1.0f / (dsp->fConst3 * dsp->fConst67));
	dsp->fConst70 = (0.0f - dsp->fConst58);
	dsp->fConst71 = (((dsp->fConst58 + -1.61803401f) / dsp->fConst57) + 1.0f);
	dsp->fConst72 = (((dsp->fConst58 + -0.618034005f) / dsp->fConst57) + 1.0f);
	dsp->fConst73 = (((dsp->fConst52 + 0.618034005f) / dsp->fConst51) + 1.0f);
	dsp->fConst74 = (1.0f / dsp->fConst73);
	dsp->fConst75 = (2.0f * (0.0f - dsp->fConst55));
	dsp->fConst76 = (1.0f / (((dsp->fConst52 + 1.61803401f) / dsp->fConst51) + 1.0f));
	dsp->fConst77 = (dsp->fConst52 + 1.0f);
	dsp->fConst78 = (0.0f - ((1.0f - dsp->fConst52) / dsp->fConst77));
	dsp->fConst79 = (1.0f / (dsp->fConst63 * dsp->fConst77));
	dsp->fConst80 = (0.0f - dsp->fConst52);
	dsp->fConst81 = (((dsp->fConst52 + -1.61803401f) / dsp->fConst51) + 1.0f);
	dsp->fConst82 = (((dsp->fConst52 + -0.618034005f) / dsp->fConst51) + 1.0f);
	dsp->fConst83 = (((dsp->fConst46 + 0.618034005f) / dsp->fConst45) + 1.0f);
	dsp->fConst84 = (1.0f / dsp->fConst83);
	dsp->fConst85 = (2.0f * (0.0f - dsp->fConst49));
	dsp->fConst86 = (1.0f / (((dsp->fConst46 + 1.61803401f) / dsp->fConst45) + 1.0f));
	dsp->fConst87 = (dsp->fConst46 + 1.0f);
	dsp->fConst88 = (0.0f - ((1.0f - dsp->fConst46) / dsp->fConst87));
	dsp->fConst89 = (1.0f / (dsp->fConst73 * dsp->fConst87));
	dsp->fConst90 = (0.0f - dsp->fConst46);
	dsp->fConst91 = (((dsp->fConst46 + -1.61803401f) / dsp->fConst45) + 1.0f);
	dsp->fConst92 = (((dsp->fConst46 + -0.618034005f) / dsp->fConst45) + 1.0f);
	dsp->fConst93 = (((dsp->fConst40 + 0.618034005f) / dsp->fConst39) + 1.0f);
	dsp->fConst94 = (1.0f / dsp->fConst93);
	dsp->fConst95 = (2.0f * (0.0f - dsp->fConst43));
	dsp->fConst96 = (1.0f / (((dsp->fConst40 + 1.61803401f) / dsp->fConst39) + 1.0f));
	dsp->fConst97 = (dsp->fConst40 + 1.0f);
	dsp->fConst98 = (0.0f - ((1.0f - dsp->fConst40) / dsp->fConst97));
	dsp->fConst99 = (1.0f / (dsp->fConst83 * dsp->fConst97));
	dsp->fConst100 = (0.0f - dsp->fConst40);
	dsp->fConst101 = (((dsp->fConst40 + -1.61803401f) / dsp->fConst39) + 1.0f);
	dsp->fConst102 = (((dsp->fConst40 + -0.618034005f) / dsp->fConst39) + 1.0f);
	dsp->fConst103 = (((dsp->fConst34 + 0.618034005f) / dsp->fConst33) + 1.0f);
	dsp->fConst104 = (1.0f / dsp->fConst103);
	dsp->fConst105 = (2.0f * (0.0f - dsp->fConst37));
	dsp->fConst106 = (1.0f / (((dsp->fConst34 + 1.61803401f) / dsp->fConst33) + 1.0f));
	dsp->fConst107 = (dsp->fConst34 + 1.0f);
	dsp->fConst108 = (0.0f - ((1.0f - dsp->fConst34) / dsp->fConst107));
	dsp->fConst109 = (1.0f / (dsp->fConst93 * dsp->fConst107));
	dsp->fConst110 = (0.0f - dsp->fConst34);
	dsp->fConst111 = (((dsp->fConst34 + -1.61803401f) / dsp->fConst33) + 1.0f);
	dsp->fConst112 = (((dsp->fConst34 + -0.618034005f) / dsp->fConst33) + 1.0f);
	dsp->fConst113 = (((dsp->fConst28 + 0.618034005f) / dsp->fConst27) + 1.0f);
	dsp->fConst114 = (1.0f / dsp->fConst113);
	dsp->fConst115 = (2.0f * (0.0f - dsp->fConst31));
	dsp->fConst116 = (1.0f / (((dsp->fConst28 + 1.61803401f) / dsp->fConst27) + 1.0f));
	dsp->fConst117 = (dsp->fConst28 + 1.0f);
	dsp->fConst118 = (0.0f - ((1.0f - dsp->fConst28) / dsp->fConst117));
	dsp->fConst119 = (1.0f / (dsp->fConst103 * dsp->fConst117));
	dsp->fConst120 = (0.0f - dsp->fConst28);
	dsp->fConst121 = (((dsp->fConst28 + -1.61803401f) / dsp->fConst27) + 1.0f);
	dsp->fConst122 = (((dsp->fConst28 + -0.618034005f) / dsp->fConst27) + 1.0f);
	dsp->fConst123 = (((dsp->fConst22 + 0.618034005f) / dsp->fConst21) + 1.0f);
	dsp->fConst124 = (1.0f / dsp->fConst123);
	dsp->fConst125 = (2.0f * (0.0f - dsp->fConst25));
	dsp->fConst126 = (1.0f / (((dsp->fConst22 + 1.61803401f) / dsp->fConst21) + 1.0f));
	dsp->fConst127 = (dsp->fConst22 + 1.0f);
	dsp->fConst128 = (0.0f - ((1.0f - dsp->fConst22) / dsp->fConst127));
	dsp->fConst129 = (1.0f / (dsp->fConst113 * dsp->fConst127));
	dsp->fConst130 = (0.0f - dsp->fConst22);
	dsp->fConst131 = (((dsp->fConst22 + -1.61803401f) / dsp->fConst21) + 1.0f);
	dsp->fConst132 = (((dsp->fConst22 + -0.618034005f) / dsp->fConst21) + 1.0f);
	dsp->fConst133 = (1.0f / (((dsp->fConst16 + 0.618034005f) / dsp->fConst15) + 1.0f));
	dsp->fConst134 = (2.0f * (0.0f - dsp->fConst19));
	dsp->fConst135 = (1.0f / (((dsp->fConst16 + 1.61803401f) / dsp->fConst15) + 1.0f));
	dsp->fConst136 = (dsp->fConst16 + 1.0f);
	dsp->fConst137 = (0.0f - ((1.0f - dsp->fConst16) / dsp->fConst136));
	dsp->fConst138 = (1.0f / (dsp->fConst123 * dsp->fConst136));
	dsp->fConst139 = (0.0f - dsp->fConst16);
	dsp->fConst140 = (((dsp->fConst16 + -1.61803401f) / dsp->fConst15) + 1.0f);
	dsp->fConst141 = (((dsp->fConst16 + -0.618034005f) / dsp->fConst15) + 1.0f);
	
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
	ui_interface->declare(ui_interface->uiInterface, 0, "tooltip", "See Faust's filters.lib for documentation and references");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "CONSTANT-Q FILTER BANK (Butterworth dyadic tree)");
	ui_interface->declare(ui_interface->uiInterface, 0, "0", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox0, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox0, "tooltip", "When this is checked, the filter-bank has no effect");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Bypass", &dsp->fCheckbox0);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "1", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider9, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider9, "tooltip", "Bandpass filter   gain in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider9, "unit", "dB");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "0x00", &dsp->fVslider9, -10.0f, -70.0f, 10.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider8, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider8, "tooltip", "Bandpass filter   gain in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider8, "unit", "dB");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "0x00", &dsp->fVslider8, -10.0f, -70.0f, 10.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider7, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider7, "tooltip", "Bandpass filter   gain in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider7, "unit", "dB");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "0x00", &dsp->fVslider7, -10.0f, -70.0f, 10.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider6, "4", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider6, "tooltip", "Bandpass filter   gain in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider6, "unit", "dB");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "0x00", &dsp->fVslider6, -10.0f, -70.0f, 10.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider5, "5", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider5, "tooltip", "Bandpass filter   gain in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider5, "unit", "dB");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "0x00", &dsp->fVslider5, -10.0f, -70.0f, 10.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider4, "6", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider4, "tooltip", "Bandpass filter   gain in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider4, "unit", "dB");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "0x00", &dsp->fVslider4, -10.0f, -70.0f, 10.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider3, "7", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider3, "tooltip", "Bandpass filter   gain in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider3, "unit", "dB");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "0x00", &dsp->fVslider3, -10.0f, -70.0f, 10.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider2, "8", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider2, "tooltip", "Bandpass filter   gain in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider2, "unit", "dB");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "0x00", &dsp->fVslider2, -10.0f, -70.0f, 10.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider1, "9", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider1, "tooltip", "Bandpass filter   gain in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider1, "unit", "dB");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "0x00", &dsp->fVslider1, -10.0f, -70.0f, 10.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider0, "10", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider0, "tooltip", "Bandpass filter   gain in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider0, "unit", "dB");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "0x00", &dsp->fVslider0, -10.0f, -70.0f, 10.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* input0 = inputs[0];
	FAUSTFLOAT* output0 = outputs[0];
	int iSlow0 = (int)(float)dsp->fCheckbox0;
	float fSlow1 = (0.00100000005f * (float)dsp->fVslider0);
	float fSlow2 = (0.00100000005f * (float)dsp->fVslider1);
	float fSlow3 = (0.00100000005f * (float)dsp->fVslider2);
	float fSlow4 = (0.00100000005f * (float)dsp->fVslider3);
	float fSlow5 = (0.00100000005f * (float)dsp->fVslider4);
	float fSlow6 = (0.00100000005f * (float)dsp->fVslider5);
	float fSlow7 = (0.00100000005f * (float)dsp->fVslider6);
	float fSlow8 = (0.00100000005f * (float)dsp->fVslider7);
	float fSlow9 = (0.00100000005f * (float)dsp->fVslider8);
	float fSlow10 = (0.00100000005f * (float)dsp->fVslider9);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = (float)input0[i];
			float fTemp1 = (iSlow0?0.0f:fTemp0);
			dsp->fVec0[0] = fTemp1;
			dsp->fRec10[0] = ((dsp->fConst9 * dsp->fRec10[1]) + (dsp->fConst10 * ((dsp->fConst2 * fTemp1) + (dsp->fConst11 * dsp->fVec0[1]))));
			dsp->fRec9[0] = (dsp->fRec10[0] - (dsp->fConst7 * ((dsp->fConst12 * dsp->fRec9[1]) + (dsp->fConst13 * dsp->fRec9[2]))));
			dsp->fRec8[0] = ((dsp->fConst7 * (((dsp->fConst5 * dsp->fRec9[0]) + (dsp->fConst6 * dsp->fRec9[1])) + (dsp->fConst5 * dsp->fRec9[2]))) - (dsp->fConst4 * ((dsp->fConst12 * dsp->fRec8[1]) + (dsp->fConst14 * dsp->fRec8[2]))));
			float fTemp2 = (dsp->fConst20 * dsp->fRec7[1]);
			dsp->fRec7[0] = ((dsp->fConst4 * (((dsp->fConst6 * dsp->fRec8[1]) + (dsp->fConst5 * dsp->fRec8[0])) + (dsp->fConst5 * dsp->fRec8[2]))) - (dsp->fConst17 * ((dsp->fConst18 * dsp->fRec7[2]) + fTemp2)));
			float fTemp3 = (dsp->fConst26 * dsp->fRec6[1]);
			dsp->fRec6[0] = ((dsp->fRec7[2] + (dsp->fConst17 * (fTemp2 + (dsp->fConst18 * dsp->fRec7[0])))) - (dsp->fConst23 * ((dsp->fConst24 * dsp->fRec6[2]) + fTemp3)));
			float fTemp4 = (dsp->fConst32 * dsp->fRec5[1]);
			dsp->fRec5[0] = ((dsp->fRec6[2] + (dsp->fConst23 * (fTemp3 + (dsp->fConst24 * dsp->fRec6[0])))) - (dsp->fConst29 * ((dsp->fConst30 * dsp->fRec5[2]) + fTemp4)));
			float fTemp5 = (dsp->fConst38 * dsp->fRec4[1]);
			dsp->fRec4[0] = ((dsp->fRec5[2] + (dsp->fConst29 * (fTemp4 + (dsp->fConst30 * dsp->fRec5[0])))) - (dsp->fConst35 * ((dsp->fConst36 * dsp->fRec4[2]) + fTemp5)));
			float fTemp6 = (dsp->fConst44 * dsp->fRec3[1]);
			dsp->fRec3[0] = ((dsp->fRec4[2] + (dsp->fConst35 * (fTemp5 + (dsp->fConst36 * dsp->fRec4[0])))) - (dsp->fConst41 * ((dsp->fConst42 * dsp->fRec3[2]) + fTemp6)));
			float fTemp7 = (dsp->fConst50 * dsp->fRec2[1]);
			dsp->fRec2[0] = ((dsp->fRec3[2] + (dsp->fConst41 * (fTemp6 + (dsp->fConst42 * dsp->fRec3[0])))) - (dsp->fConst47 * ((dsp->fConst48 * dsp->fRec2[2]) + fTemp7)));
			float fTemp8 = (dsp->fConst56 * dsp->fRec1[1]);
			dsp->fRec1[0] = ((dsp->fRec2[2] + (dsp->fConst47 * (fTemp7 + (dsp->fConst48 * dsp->fRec2[0])))) - (dsp->fConst53 * ((dsp->fConst54 * dsp->fRec1[2]) + fTemp8)));
			float fTemp9 = (dsp->fConst62 * dsp->fRec0[1]);
			dsp->fRec0[0] = ((dsp->fRec1[2] + (dsp->fConst53 * (fTemp8 + (dsp->fConst54 * dsp->fRec1[0])))) - (dsp->fConst59 * ((dsp->fConst60 * dsp->fRec0[2]) + fTemp9)));
			dsp->fRec11[0] = (fSlow1 + (0.999000013f * dsp->fRec11[1]));
			dsp->fRec24[0] = ((dsp->fConst9 * dsp->fRec24[1]) + (dsp->fConst10 * (fTemp1 + dsp->fVec0[1])));
			dsp->fRec23[0] = (dsp->fRec24[0] - (dsp->fConst7 * ((dsp->fConst12 * dsp->fRec23[1]) + (dsp->fConst13 * dsp->fRec23[2]))));
			dsp->fRec22[0] = ((dsp->fConst7 * (dsp->fRec23[2] + (dsp->fRec23[0] + (2.0f * dsp->fRec23[1])))) - (dsp->fConst4 * ((dsp->fConst12 * dsp->fRec22[1]) + (dsp->fConst14 * dsp->fRec22[2]))));
			float fTemp10 = (dsp->fRec22[2] + (dsp->fRec22[0] + (2.0f * dsp->fRec22[1])));
			dsp->fVec1[0] = fTemp10;
			dsp->fRec21[0] = ((dsp->fConst68 * dsp->fRec21[1]) + (dsp->fConst69 * ((dsp->fConst58 * fTemp10) + (dsp->fConst70 * dsp->fVec1[1]))));
			dsp->fRec20[0] = (dsp->fRec21[0] - (dsp->fConst66 * ((dsp->fConst62 * dsp->fRec20[1]) + (dsp->fConst71 * dsp->fRec20[2]))));
			dsp->fRec19[0] = ((dsp->fConst66 * (((dsp->fConst61 * dsp->fRec20[0]) + (dsp->fConst65 * dsp->fRec20[1])) + (dsp->fConst61 * dsp->fRec20[2]))) - (dsp->fConst64 * ((dsp->fConst62 * dsp->fRec19[1]) + (dsp->fConst72 * dsp->fRec19[2]))));
			float fTemp11 = (dsp->fConst20 * dsp->fRec18[1]);
			dsp->fRec18[0] = ((dsp->fConst64 * (((dsp->fConst65 * dsp->fRec19[1]) + (dsp->fConst61 * dsp->fRec19[0])) + (dsp->fConst61 * dsp->fRec19[2]))) - (dsp->fConst17 * (fTemp11 + (dsp->fConst18 * dsp->fRec18[2]))));
			float fTemp12 = (dsp->fConst26 * dsp->fRec17[1]);
			dsp->fRec17[0] = ((dsp->fRec18[2] + (dsp->fConst17 * (fTemp11 + (dsp->fConst18 * dsp->fRec18[0])))) - (dsp->fConst23 * (fTemp12 + (dsp->fConst24 * dsp->fRec17[2]))));
			float fTemp13 = (dsp->fConst32 * dsp->fRec16[1]);
			dsp->fRec16[0] = ((dsp->fRec17[2] + (dsp->fConst23 * (fTemp12 + (dsp->fConst24 * dsp->fRec17[0])))) - (dsp->fConst29 * (fTemp13 + (dsp->fConst30 * dsp->fRec16[2]))));
			float fTemp14 = (dsp->fConst38 * dsp->fRec15[1]);
			dsp->fRec15[0] = ((dsp->fRec16[2] + (dsp->fConst29 * (fTemp13 + (dsp->fConst30 * dsp->fRec16[0])))) - (dsp->fConst35 * (fTemp14 + (dsp->fConst36 * dsp->fRec15[2]))));
			float fTemp15 = (dsp->fConst44 * dsp->fRec14[1]);
			dsp->fRec14[0] = ((dsp->fRec15[2] + (dsp->fConst35 * (fTemp14 + (dsp->fConst36 * dsp->fRec15[0])))) - (dsp->fConst41 * (fTemp15 + (dsp->fConst42 * dsp->fRec14[2]))));
			float fTemp16 = (dsp->fConst50 * dsp->fRec13[1]);
			dsp->fRec13[0] = ((dsp->fRec14[2] + (dsp->fConst41 * (fTemp15 + (dsp->fConst42 * dsp->fRec14[0])))) - (dsp->fConst47 * (fTemp16 + (dsp->fConst48 * dsp->fRec13[2]))));
			float fTemp17 = (dsp->fConst56 * dsp->fRec12[1]);
			dsp->fRec12[0] = ((dsp->fRec13[2] + (dsp->fConst47 * (fTemp16 + (dsp->fConst48 * dsp->fRec13[0])))) - (dsp->fConst53 * (fTemp17 + (dsp->fConst54 * dsp->fRec12[2]))));
			dsp->fRec25[0] = (fSlow2 + (0.999000013f * dsp->fRec25[1]));
			dsp->fRec37[0] = ((dsp->fConst68 * dsp->fRec37[1]) + (dsp->fConst69 * (fTemp10 + dsp->fVec1[1])));
			dsp->fRec36[0] = (dsp->fRec37[0] - (dsp->fConst66 * ((dsp->fConst62 * dsp->fRec36[1]) + (dsp->fConst71 * dsp->fRec36[2]))));
			dsp->fRec35[0] = ((dsp->fConst66 * (dsp->fRec36[2] + (dsp->fRec36[0] + (2.0f * dsp->fRec36[1])))) - (dsp->fConst64 * ((dsp->fConst62 * dsp->fRec35[1]) + (dsp->fConst72 * dsp->fRec35[2]))));
			float fTemp18 = (dsp->fRec35[2] + (dsp->fRec35[0] + (2.0f * dsp->fRec35[1])));
			dsp->fVec2[0] = fTemp18;
			dsp->fRec34[0] = ((dsp->fConst78 * dsp->fRec34[1]) + (dsp->fConst79 * ((dsp->fConst52 * fTemp18) + (dsp->fConst80 * dsp->fVec2[1]))));
			dsp->fRec33[0] = (dsp->fRec34[0] - (dsp->fConst76 * ((dsp->fConst56 * dsp->fRec33[1]) + (dsp->fConst81 * dsp->fRec33[2]))));
			dsp->fRec32[0] = ((dsp->fConst76 * (((dsp->fConst55 * dsp->fRec33[0]) + (dsp->fConst75 * dsp->fRec33[1])) + (dsp->fConst55 * dsp->fRec33[2]))) - (dsp->fConst74 * ((dsp->fConst56 * dsp->fRec32[1]) + (dsp->fConst82 * dsp->fRec32[2]))));
			float fTemp19 = (dsp->fConst20 * dsp->fRec31[1]);
			dsp->fRec31[0] = ((dsp->fConst74 * (((dsp->fConst75 * dsp->fRec32[1]) + (dsp->fConst55 * dsp->fRec32[0])) + (dsp->fConst55 * dsp->fRec32[2]))) - (dsp->fConst17 * (fTemp19 + (dsp->fConst18 * dsp->fRec31[2]))));
			float fTemp20 = (dsp->fConst26 * dsp->fRec30[1]);
			dsp->fRec30[0] = ((dsp->fRec31[2] + (dsp->fConst17 * (fTemp19 + (dsp->fConst18 * dsp->fRec31[0])))) - (dsp->fConst23 * (fTemp20 + (dsp->fConst24 * dsp->fRec30[2]))));
			float fTemp21 = (dsp->fConst32 * dsp->fRec29[1]);
			dsp->fRec29[0] = ((dsp->fRec30[2] + (dsp->fConst23 * (fTemp20 + (dsp->fConst24 * dsp->fRec30[0])))) - (dsp->fConst29 * (fTemp21 + (dsp->fConst30 * dsp->fRec29[2]))));
			float fTemp22 = (dsp->fConst38 * dsp->fRec28[1]);
			dsp->fRec28[0] = ((dsp->fRec29[2] + (dsp->fConst29 * (fTemp21 + (dsp->fConst30 * dsp->fRec29[0])))) - (dsp->fConst35 * (fTemp22 + (dsp->fConst36 * dsp->fRec28[2]))));
			float fTemp23 = (dsp->fConst44 * dsp->fRec27[1]);
			dsp->fRec27[0] = ((dsp->fRec28[2] + (dsp->fConst35 * (fTemp22 + (dsp->fConst36 * dsp->fRec28[0])))) - (dsp->fConst41 * (fTemp23 + (dsp->fConst42 * dsp->fRec27[2]))));
			float fTemp24 = (dsp->fConst50 * dsp->fRec26[1]);
			dsp->fRec26[0] = ((dsp->fRec27[2] + (dsp->fConst41 * (fTemp23 + (dsp->fConst42 * dsp->fRec27[0])))) - (dsp->fConst47 * (fTemp24 + (dsp->fConst48 * dsp->fRec26[2]))));
			dsp->fRec38[0] = (fSlow3 + (0.999000013f * dsp->fRec38[1]));
			dsp->fRec49[0] = ((dsp->fConst78 * dsp->fRec49[1]) + (dsp->fConst79 * (fTemp18 + dsp->fVec2[1])));
			dsp->fRec48[0] = (dsp->fRec49[0] - (dsp->fConst76 * ((dsp->fConst56 * dsp->fRec48[1]) + (dsp->fConst81 * dsp->fRec48[2]))));
			dsp->fRec47[0] = ((dsp->fConst76 * (dsp->fRec48[2] + (dsp->fRec48[0] + (2.0f * dsp->fRec48[1])))) - (dsp->fConst74 * ((dsp->fConst56 * dsp->fRec47[1]) + (dsp->fConst82 * dsp->fRec47[2]))));
			float fTemp25 = (dsp->fRec47[2] + (dsp->fRec47[0] + (2.0f * dsp->fRec47[1])));
			dsp->fVec3[0] = fTemp25;
			dsp->fRec46[0] = ((dsp->fConst88 * dsp->fRec46[1]) + (dsp->fConst89 * ((dsp->fConst46 * fTemp25) + (dsp->fConst90 * dsp->fVec3[1]))));
			dsp->fRec45[0] = (dsp->fRec46[0] - (dsp->fConst86 * ((dsp->fConst50 * dsp->fRec45[1]) + (dsp->fConst91 * dsp->fRec45[2]))));
			dsp->fRec44[0] = ((dsp->fConst86 * (((dsp->fConst49 * dsp->fRec45[0]) + (dsp->fConst85 * dsp->fRec45[1])) + (dsp->fConst49 * dsp->fRec45[2]))) - (dsp->fConst84 * ((dsp->fConst50 * dsp->fRec44[1]) + (dsp->fConst92 * dsp->fRec44[2]))));
			float fTemp26 = (dsp->fConst20 * dsp->fRec43[1]);
			dsp->fRec43[0] = ((dsp->fConst84 * (((dsp->fConst85 * dsp->fRec44[1]) + (dsp->fConst49 * dsp->fRec44[0])) + (dsp->fConst49 * dsp->fRec44[2]))) - (dsp->fConst17 * (fTemp26 + (dsp->fConst18 * dsp->fRec43[2]))));
			float fTemp27 = (dsp->fConst26 * dsp->fRec42[1]);
			dsp->fRec42[0] = ((dsp->fRec43[2] + (dsp->fConst17 * (fTemp26 + (dsp->fConst18 * dsp->fRec43[0])))) - (dsp->fConst23 * (fTemp27 + (dsp->fConst24 * dsp->fRec42[2]))));
			float fTemp28 = (dsp->fConst32 * dsp->fRec41[1]);
			dsp->fRec41[0] = ((dsp->fRec42[2] + (dsp->fConst23 * (fTemp27 + (dsp->fConst24 * dsp->fRec42[0])))) - (dsp->fConst29 * (fTemp28 + (dsp->fConst30 * dsp->fRec41[2]))));
			float fTemp29 = (dsp->fConst38 * dsp->fRec40[1]);
			dsp->fRec40[0] = ((dsp->fRec41[2] + (dsp->fConst29 * (fTemp28 + (dsp->fConst30 * dsp->fRec41[0])))) - (dsp->fConst35 * (fTemp29 + (dsp->fConst36 * dsp->fRec40[2]))));
			float fTemp30 = (dsp->fConst44 * dsp->fRec39[1]);
			dsp->fRec39[0] = ((dsp->fRec40[2] + (dsp->fConst35 * (fTemp29 + (dsp->fConst36 * dsp->fRec40[0])))) - (dsp->fConst41 * (fTemp30 + (dsp->fConst42 * dsp->fRec39[2]))));
			dsp->fRec50[0] = (fSlow4 + (0.999000013f * dsp->fRec50[1]));
			dsp->fRec60[0] = ((dsp->fConst88 * dsp->fRec60[1]) + (dsp->fConst89 * (fTemp25 + dsp->fVec3[1])));
			dsp->fRec59[0] = (dsp->fRec60[0] - (dsp->fConst86 * ((dsp->fConst50 * dsp->fRec59[1]) + (dsp->fConst91 * dsp->fRec59[2]))));
			dsp->fRec58[0] = ((dsp->fConst86 * (dsp->fRec59[2] + (dsp->fRec59[0] + (2.0f * dsp->fRec59[1])))) - (dsp->fConst84 * ((dsp->fConst50 * dsp->fRec58[1]) + (dsp->fConst92 * dsp->fRec58[2]))));
			float fTemp31 = (dsp->fRec58[2] + (dsp->fRec58[0] + (2.0f * dsp->fRec58[1])));
			dsp->fVec4[0] = fTemp31;
			dsp->fRec57[0] = ((dsp->fConst98 * dsp->fRec57[1]) + (dsp->fConst99 * ((dsp->fConst40 * fTemp31) + (dsp->fConst100 * dsp->fVec4[1]))));
			dsp->fRec56[0] = (dsp->fRec57[0] - (dsp->fConst96 * ((dsp->fConst44 * dsp->fRec56[1]) + (dsp->fConst101 * dsp->fRec56[2]))));
			dsp->fRec55[0] = ((dsp->fConst96 * (((dsp->fConst43 * dsp->fRec56[0]) + (dsp->fConst95 * dsp->fRec56[1])) + (dsp->fConst43 * dsp->fRec56[2]))) - (dsp->fConst94 * ((dsp->fConst44 * dsp->fRec55[1]) + (dsp->fConst102 * dsp->fRec55[2]))));
			float fTemp32 = (dsp->fConst20 * dsp->fRec54[1]);
			dsp->fRec54[0] = ((dsp->fConst94 * (((dsp->fConst95 * dsp->fRec55[1]) + (dsp->fConst43 * dsp->fRec55[0])) + (dsp->fConst43 * dsp->fRec55[2]))) - (dsp->fConst17 * (fTemp32 + (dsp->fConst18 * dsp->fRec54[2]))));
			float fTemp33 = (dsp->fConst26 * dsp->fRec53[1]);
			dsp->fRec53[0] = ((dsp->fRec54[2] + (dsp->fConst17 * (fTemp32 + (dsp->fConst18 * dsp->fRec54[0])))) - (dsp->fConst23 * (fTemp33 + (dsp->fConst24 * dsp->fRec53[2]))));
			float fTemp34 = (dsp->fConst32 * dsp->fRec52[1]);
			dsp->fRec52[0] = ((dsp->fRec53[2] + (dsp->fConst23 * (fTemp33 + (dsp->fConst24 * dsp->fRec53[0])))) - (dsp->fConst29 * (fTemp34 + (dsp->fConst30 * dsp->fRec52[2]))));
			float fTemp35 = (dsp->fConst38 * dsp->fRec51[1]);
			dsp->fRec51[0] = ((dsp->fRec52[2] + (dsp->fConst29 * (fTemp34 + (dsp->fConst30 * dsp->fRec52[0])))) - (dsp->fConst35 * (fTemp35 + (dsp->fConst36 * dsp->fRec51[2]))));
			dsp->fRec61[0] = (fSlow5 + (0.999000013f * dsp->fRec61[1]));
			dsp->fRec70[0] = ((dsp->fConst98 * dsp->fRec70[1]) + (dsp->fConst99 * (fTemp31 + dsp->fVec4[1])));
			dsp->fRec69[0] = (dsp->fRec70[0] - (dsp->fConst96 * ((dsp->fConst44 * dsp->fRec69[1]) + (dsp->fConst101 * dsp->fRec69[2]))));
			dsp->fRec68[0] = ((dsp->fConst96 * (dsp->fRec69[2] + (dsp->fRec69[0] + (2.0f * dsp->fRec69[1])))) - (dsp->fConst94 * ((dsp->fConst44 * dsp->fRec68[1]) + (dsp->fConst102 * dsp->fRec68[2]))));
			float fTemp36 = (dsp->fRec68[2] + (dsp->fRec68[0] + (2.0f * dsp->fRec68[1])));
			dsp->fVec5[0] = fTemp36;
			dsp->fRec67[0] = ((dsp->fConst108 * dsp->fRec67[1]) + (dsp->fConst109 * ((dsp->fConst34 * fTemp36) + (dsp->fConst110 * dsp->fVec5[1]))));
			dsp->fRec66[0] = (dsp->fRec67[0] - (dsp->fConst106 * ((dsp->fConst38 * dsp->fRec66[1]) + (dsp->fConst111 * dsp->fRec66[2]))));
			dsp->fRec65[0] = ((dsp->fConst106 * (((dsp->fConst37 * dsp->fRec66[0]) + (dsp->fConst105 * dsp->fRec66[1])) + (dsp->fConst37 * dsp->fRec66[2]))) - (dsp->fConst104 * ((dsp->fConst38 * dsp->fRec65[1]) + (dsp->fConst112 * dsp->fRec65[2]))));
			float fTemp37 = (dsp->fConst20 * dsp->fRec64[1]);
			dsp->fRec64[0] = ((dsp->fConst104 * (((dsp->fConst105 * dsp->fRec65[1]) + (dsp->fConst37 * dsp->fRec65[0])) + (dsp->fConst37 * dsp->fRec65[2]))) - (dsp->fConst17 * (fTemp37 + (dsp->fConst18 * dsp->fRec64[2]))));
			float fTemp38 = (dsp->fConst26 * dsp->fRec63[1]);
			dsp->fRec63[0] = ((dsp->fRec64[2] + (dsp->fConst17 * (fTemp37 + (dsp->fConst18 * dsp->fRec64[0])))) - (dsp->fConst23 * (fTemp38 + (dsp->fConst24 * dsp->fRec63[2]))));
			float fTemp39 = (dsp->fConst32 * dsp->fRec62[1]);
			dsp->fRec62[0] = ((dsp->fRec63[2] + (dsp->fConst23 * (fTemp38 + (dsp->fConst24 * dsp->fRec63[0])))) - (dsp->fConst29 * (fTemp39 + (dsp->fConst30 * dsp->fRec62[2]))));
			dsp->fRec71[0] = (fSlow6 + (0.999000013f * dsp->fRec71[1]));
			dsp->fRec79[0] = ((dsp->fConst108 * dsp->fRec79[1]) + (dsp->fConst109 * (fTemp36 + dsp->fVec5[1])));
			dsp->fRec78[0] = (dsp->fRec79[0] - (dsp->fConst106 * ((dsp->fConst38 * dsp->fRec78[1]) + (dsp->fConst111 * dsp->fRec78[2]))));
			dsp->fRec77[0] = ((dsp->fConst106 * (dsp->fRec78[2] + (dsp->fRec78[0] + (2.0f * dsp->fRec78[1])))) - (dsp->fConst104 * ((dsp->fConst38 * dsp->fRec77[1]) + (dsp->fConst112 * dsp->fRec77[2]))));
			float fTemp40 = (dsp->fRec77[2] + (dsp->fRec77[0] + (2.0f * dsp->fRec77[1])));
			dsp->fVec6[0] = fTemp40;
			dsp->fRec76[0] = ((dsp->fConst118 * dsp->fRec76[1]) + (dsp->fConst119 * ((dsp->fConst28 * fTemp40) + (dsp->fConst120 * dsp->fVec6[1]))));
			dsp->fRec75[0] = (dsp->fRec76[0] - (dsp->fConst116 * ((dsp->fConst32 * dsp->fRec75[1]) + (dsp->fConst121 * dsp->fRec75[2]))));
			dsp->fRec74[0] = ((dsp->fConst116 * (((dsp->fConst31 * dsp->fRec75[0]) + (dsp->fConst115 * dsp->fRec75[1])) + (dsp->fConst31 * dsp->fRec75[2]))) - (dsp->fConst114 * ((dsp->fConst32 * dsp->fRec74[1]) + (dsp->fConst122 * dsp->fRec74[2]))));
			float fTemp41 = (dsp->fConst20 * dsp->fRec73[1]);
			dsp->fRec73[0] = ((dsp->fConst114 * (((dsp->fConst115 * dsp->fRec74[1]) + (dsp->fConst31 * dsp->fRec74[0])) + (dsp->fConst31 * dsp->fRec74[2]))) - (dsp->fConst17 * (fTemp41 + (dsp->fConst18 * dsp->fRec73[2]))));
			float fTemp42 = (dsp->fConst26 * dsp->fRec72[1]);
			dsp->fRec72[0] = ((dsp->fRec73[2] + (dsp->fConst17 * (fTemp41 + (dsp->fConst18 * dsp->fRec73[0])))) - (dsp->fConst23 * (fTemp42 + (dsp->fConst24 * dsp->fRec72[2]))));
			dsp->fRec80[0] = (fSlow7 + (0.999000013f * dsp->fRec80[1]));
			dsp->fRec87[0] = ((dsp->fConst118 * dsp->fRec87[1]) + (dsp->fConst119 * (fTemp40 + dsp->fVec6[1])));
			dsp->fRec86[0] = (dsp->fRec87[0] - (dsp->fConst116 * ((dsp->fConst32 * dsp->fRec86[1]) + (dsp->fConst121 * dsp->fRec86[2]))));
			dsp->fRec85[0] = ((dsp->fConst116 * (dsp->fRec86[2] + (dsp->fRec86[0] + (2.0f * dsp->fRec86[1])))) - (dsp->fConst114 * ((dsp->fConst32 * dsp->fRec85[1]) + (dsp->fConst122 * dsp->fRec85[2]))));
			float fTemp43 = (dsp->fRec85[2] + (dsp->fRec85[0] + (2.0f * dsp->fRec85[1])));
			dsp->fVec7[0] = fTemp43;
			dsp->fRec84[0] = ((dsp->fConst128 * dsp->fRec84[1]) + (dsp->fConst129 * ((dsp->fConst22 * fTemp43) + (dsp->fConst130 * dsp->fVec7[1]))));
			dsp->fRec83[0] = (dsp->fRec84[0] - (dsp->fConst126 * ((dsp->fConst26 * dsp->fRec83[1]) + (dsp->fConst131 * dsp->fRec83[2]))));
			dsp->fRec82[0] = ((dsp->fConst126 * (((dsp->fConst25 * dsp->fRec83[0]) + (dsp->fConst125 * dsp->fRec83[1])) + (dsp->fConst25 * dsp->fRec83[2]))) - (dsp->fConst124 * ((dsp->fConst26 * dsp->fRec82[1]) + (dsp->fConst132 * dsp->fRec82[2]))));
			float fTemp44 = (dsp->fConst20 * dsp->fRec81[1]);
			dsp->fRec81[0] = ((dsp->fConst124 * (((dsp->fConst125 * dsp->fRec82[1]) + (dsp->fConst25 * dsp->fRec82[0])) + (dsp->fConst25 * dsp->fRec82[2]))) - (dsp->fConst17 * (fTemp44 + (dsp->fConst18 * dsp->fRec81[2]))));
			dsp->fRec88[0] = (fSlow8 + (0.999000013f * dsp->fRec88[1]));
			dsp->fRec94[0] = ((dsp->fConst128 * dsp->fRec94[1]) + (dsp->fConst129 * (fTemp43 + dsp->fVec7[1])));
			dsp->fRec93[0] = (dsp->fRec94[0] - (dsp->fConst126 * ((dsp->fConst26 * dsp->fRec93[1]) + (dsp->fConst131 * dsp->fRec93[2]))));
			dsp->fRec92[0] = ((dsp->fConst126 * (dsp->fRec93[2] + (dsp->fRec93[0] + (2.0f * dsp->fRec93[1])))) - (dsp->fConst124 * ((dsp->fConst26 * dsp->fRec92[1]) + (dsp->fConst132 * dsp->fRec92[2]))));
			float fTemp45 = (dsp->fRec92[2] + (dsp->fRec92[0] + (2.0f * dsp->fRec92[1])));
			dsp->fVec8[0] = fTemp45;
			dsp->fRec91[0] = ((dsp->fConst137 * dsp->fRec91[1]) + (dsp->fConst138 * ((dsp->fConst16 * fTemp45) + (dsp->fConst139 * dsp->fVec8[1]))));
			dsp->fRec90[0] = (dsp->fRec91[0] - (dsp->fConst135 * ((dsp->fConst20 * dsp->fRec90[1]) + (dsp->fConst140 * dsp->fRec90[2]))));
			dsp->fRec89[0] = ((dsp->fConst135 * (((dsp->fConst19 * dsp->fRec90[0]) + (dsp->fConst134 * dsp->fRec90[1])) + (dsp->fConst19 * dsp->fRec90[2]))) - (dsp->fConst133 * ((dsp->fConst20 * dsp->fRec89[1]) + (dsp->fConst141 * dsp->fRec89[2]))));
			dsp->fRec95[0] = (fSlow9 + (0.999000013f * dsp->fRec95[1]));
			dsp->fRec98[0] = ((dsp->fConst137 * dsp->fRec98[1]) + (dsp->fConst138 * (fTemp45 + dsp->fVec8[1])));
			dsp->fRec97[0] = (dsp->fRec98[0] - (dsp->fConst135 * ((dsp->fConst20 * dsp->fRec97[1]) + (dsp->fConst140 * dsp->fRec97[2]))));
			dsp->fRec96[0] = ((dsp->fConst135 * (dsp->fRec97[2] + (dsp->fRec97[0] + (2.0f * dsp->fRec97[1])))) - (dsp->fConst133 * ((dsp->fConst20 * dsp->fRec96[1]) + (dsp->fConst141 * dsp->fRec96[2]))));
			dsp->fRec99[0] = (fSlow10 + (0.999000013f * dsp->fRec99[1]));
			output0[i] = (FAUSTFLOAT)(iSlow0?fTemp0:((((((((((dsp->fRec0[2] + (dsp->fConst59 * (fTemp9 + (dsp->fConst60 * dsp->fRec0[0])))) * powf(10.0f, (0.0500000007f * dsp->fRec11[0]))) + ((dsp->fRec12[2] + (dsp->fConst53 * (fTemp17 + (dsp->fConst54 * dsp->fRec12[0])))) * powf(10.0f, (0.0500000007f * dsp->fRec25[0])))) + ((dsp->fRec26[2] + (dsp->fConst47 * (fTemp24 + (dsp->fConst48 * dsp->fRec26[0])))) * powf(10.0f, (0.0500000007f * dsp->fRec38[0])))) + ((dsp->fRec39[2] + (dsp->fConst41 * (fTemp30 + (dsp->fConst42 * dsp->fRec39[0])))) * powf(10.0f, (0.0500000007f * dsp->fRec50[0])))) + ((dsp->fRec51[2] + (dsp->fConst35 * (fTemp35 + (dsp->fConst36 * dsp->fRec51[0])))) * powf(10.0f, (0.0500000007f * dsp->fRec61[0])))) + ((dsp->fRec62[2] + (dsp->fConst29 * (fTemp39 + (dsp->fConst30 * dsp->fRec62[0])))) * powf(10.0f, (0.0500000007f * dsp->fRec71[0])))) + ((dsp->fRec72[2] + (dsp->fConst23 * (fTemp42 + (dsp->fConst24 * dsp->fRec72[0])))) * powf(10.0f, (0.0500000007f * dsp->fRec80[0])))) + ((dsp->fRec81[2] + (dsp->fConst17 * (fTemp44 + (dsp->fConst18 * dsp->fRec81[0])))) * powf(10.0f, (0.0500000007f * dsp->fRec88[0])))) + (dsp->fConst133 * (((((dsp->fConst134 * dsp->fRec89[1]) + (dsp->fConst19 * dsp->fRec89[0])) + (dsp->fConst19 * dsp->fRec89[2])) * powf(10.0f, (0.0500000007f * dsp->fRec95[0]))) + ((dsp->fRec96[2] + (dsp->fRec96[0] + (2.0f * dsp->fRec96[1]))) * powf(10.0f, (0.0500000007f * dsp->fRec99[0])))))));
			dsp->fVec0[1] = dsp->fVec0[0];
			dsp->fRec10[1] = dsp->fRec10[0];
			dsp->fRec9[2] = dsp->fRec9[1];
			dsp->fRec9[1] = dsp->fRec9[0];
			dsp->fRec8[2] = dsp->fRec8[1];
			dsp->fRec8[1] = dsp->fRec8[0];
			dsp->fRec7[2] = dsp->fRec7[1];
			dsp->fRec7[1] = dsp->fRec7[0];
			dsp->fRec6[2] = dsp->fRec6[1];
			dsp->fRec6[1] = dsp->fRec6[0];
			dsp->fRec5[2] = dsp->fRec5[1];
			dsp->fRec5[1] = dsp->fRec5[0];
			dsp->fRec4[2] = dsp->fRec4[1];
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fRec3[2] = dsp->fRec3[1];
			dsp->fRec3[1] = dsp->fRec3[0];
			dsp->fRec2[2] = dsp->fRec2[1];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec1[2] = dsp->fRec1[1];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fRec0[2] = dsp->fRec0[1];
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec11[1] = dsp->fRec11[0];
			dsp->fRec24[1] = dsp->fRec24[0];
			dsp->fRec23[2] = dsp->fRec23[1];
			dsp->fRec23[1] = dsp->fRec23[0];
			dsp->fRec22[2] = dsp->fRec22[1];
			dsp->fRec22[1] = dsp->fRec22[0];
			dsp->fVec1[1] = dsp->fVec1[0];
			dsp->fRec21[1] = dsp->fRec21[0];
			dsp->fRec20[2] = dsp->fRec20[1];
			dsp->fRec20[1] = dsp->fRec20[0];
			dsp->fRec19[2] = dsp->fRec19[1];
			dsp->fRec19[1] = dsp->fRec19[0];
			dsp->fRec18[2] = dsp->fRec18[1];
			dsp->fRec18[1] = dsp->fRec18[0];
			dsp->fRec17[2] = dsp->fRec17[1];
			dsp->fRec17[1] = dsp->fRec17[0];
			dsp->fRec16[2] = dsp->fRec16[1];
			dsp->fRec16[1] = dsp->fRec16[0];
			dsp->fRec15[2] = dsp->fRec15[1];
			dsp->fRec15[1] = dsp->fRec15[0];
			dsp->fRec14[2] = dsp->fRec14[1];
			dsp->fRec14[1] = dsp->fRec14[0];
			dsp->fRec13[2] = dsp->fRec13[1];
			dsp->fRec13[1] = dsp->fRec13[0];
			dsp->fRec12[2] = dsp->fRec12[1];
			dsp->fRec12[1] = dsp->fRec12[0];
			dsp->fRec25[1] = dsp->fRec25[0];
			dsp->fRec37[1] = dsp->fRec37[0];
			dsp->fRec36[2] = dsp->fRec36[1];
			dsp->fRec36[1] = dsp->fRec36[0];
			dsp->fRec35[2] = dsp->fRec35[1];
			dsp->fRec35[1] = dsp->fRec35[0];
			dsp->fVec2[1] = dsp->fVec2[0];
			dsp->fRec34[1] = dsp->fRec34[0];
			dsp->fRec33[2] = dsp->fRec33[1];
			dsp->fRec33[1] = dsp->fRec33[0];
			dsp->fRec32[2] = dsp->fRec32[1];
			dsp->fRec32[1] = dsp->fRec32[0];
			dsp->fRec31[2] = dsp->fRec31[1];
			dsp->fRec31[1] = dsp->fRec31[0];
			dsp->fRec30[2] = dsp->fRec30[1];
			dsp->fRec30[1] = dsp->fRec30[0];
			dsp->fRec29[2] = dsp->fRec29[1];
			dsp->fRec29[1] = dsp->fRec29[0];
			dsp->fRec28[2] = dsp->fRec28[1];
			dsp->fRec28[1] = dsp->fRec28[0];
			dsp->fRec27[2] = dsp->fRec27[1];
			dsp->fRec27[1] = dsp->fRec27[0];
			dsp->fRec26[2] = dsp->fRec26[1];
			dsp->fRec26[1] = dsp->fRec26[0];
			dsp->fRec38[1] = dsp->fRec38[0];
			dsp->fRec49[1] = dsp->fRec49[0];
			dsp->fRec48[2] = dsp->fRec48[1];
			dsp->fRec48[1] = dsp->fRec48[0];
			dsp->fRec47[2] = dsp->fRec47[1];
			dsp->fRec47[1] = dsp->fRec47[0];
			dsp->fVec3[1] = dsp->fVec3[0];
			dsp->fRec46[1] = dsp->fRec46[0];
			dsp->fRec45[2] = dsp->fRec45[1];
			dsp->fRec45[1] = dsp->fRec45[0];
			dsp->fRec44[2] = dsp->fRec44[1];
			dsp->fRec44[1] = dsp->fRec44[0];
			dsp->fRec43[2] = dsp->fRec43[1];
			dsp->fRec43[1] = dsp->fRec43[0];
			dsp->fRec42[2] = dsp->fRec42[1];
			dsp->fRec42[1] = dsp->fRec42[0];
			dsp->fRec41[2] = dsp->fRec41[1];
			dsp->fRec41[1] = dsp->fRec41[0];
			dsp->fRec40[2] = dsp->fRec40[1];
			dsp->fRec40[1] = dsp->fRec40[0];
			dsp->fRec39[2] = dsp->fRec39[1];
			dsp->fRec39[1] = dsp->fRec39[0];
			dsp->fRec50[1] = dsp->fRec50[0];
			dsp->fRec60[1] = dsp->fRec60[0];
			dsp->fRec59[2] = dsp->fRec59[1];
			dsp->fRec59[1] = dsp->fRec59[0];
			dsp->fRec58[2] = dsp->fRec58[1];
			dsp->fRec58[1] = dsp->fRec58[0];
			dsp->fVec4[1] = dsp->fVec4[0];
			dsp->fRec57[1] = dsp->fRec57[0];
			dsp->fRec56[2] = dsp->fRec56[1];
			dsp->fRec56[1] = dsp->fRec56[0];
			dsp->fRec55[2] = dsp->fRec55[1];
			dsp->fRec55[1] = dsp->fRec55[0];
			dsp->fRec54[2] = dsp->fRec54[1];
			dsp->fRec54[1] = dsp->fRec54[0];
			dsp->fRec53[2] = dsp->fRec53[1];
			dsp->fRec53[1] = dsp->fRec53[0];
			dsp->fRec52[2] = dsp->fRec52[1];
			dsp->fRec52[1] = dsp->fRec52[0];
			dsp->fRec51[2] = dsp->fRec51[1];
			dsp->fRec51[1] = dsp->fRec51[0];
			dsp->fRec61[1] = dsp->fRec61[0];
			dsp->fRec70[1] = dsp->fRec70[0];
			dsp->fRec69[2] = dsp->fRec69[1];
			dsp->fRec69[1] = dsp->fRec69[0];
			dsp->fRec68[2] = dsp->fRec68[1];
			dsp->fRec68[1] = dsp->fRec68[0];
			dsp->fVec5[1] = dsp->fVec5[0];
			dsp->fRec67[1] = dsp->fRec67[0];
			dsp->fRec66[2] = dsp->fRec66[1];
			dsp->fRec66[1] = dsp->fRec66[0];
			dsp->fRec65[2] = dsp->fRec65[1];
			dsp->fRec65[1] = dsp->fRec65[0];
			dsp->fRec64[2] = dsp->fRec64[1];
			dsp->fRec64[1] = dsp->fRec64[0];
			dsp->fRec63[2] = dsp->fRec63[1];
			dsp->fRec63[1] = dsp->fRec63[0];
			dsp->fRec62[2] = dsp->fRec62[1];
			dsp->fRec62[1] = dsp->fRec62[0];
			dsp->fRec71[1] = dsp->fRec71[0];
			dsp->fRec79[1] = dsp->fRec79[0];
			dsp->fRec78[2] = dsp->fRec78[1];
			dsp->fRec78[1] = dsp->fRec78[0];
			dsp->fRec77[2] = dsp->fRec77[1];
			dsp->fRec77[1] = dsp->fRec77[0];
			dsp->fVec6[1] = dsp->fVec6[0];
			dsp->fRec76[1] = dsp->fRec76[0];
			dsp->fRec75[2] = dsp->fRec75[1];
			dsp->fRec75[1] = dsp->fRec75[0];
			dsp->fRec74[2] = dsp->fRec74[1];
			dsp->fRec74[1] = dsp->fRec74[0];
			dsp->fRec73[2] = dsp->fRec73[1];
			dsp->fRec73[1] = dsp->fRec73[0];
			dsp->fRec72[2] = dsp->fRec72[1];
			dsp->fRec72[1] = dsp->fRec72[0];
			dsp->fRec80[1] = dsp->fRec80[0];
			dsp->fRec87[1] = dsp->fRec87[0];
			dsp->fRec86[2] = dsp->fRec86[1];
			dsp->fRec86[1] = dsp->fRec86[0];
			dsp->fRec85[2] = dsp->fRec85[1];
			dsp->fRec85[1] = dsp->fRec85[0];
			dsp->fVec7[1] = dsp->fVec7[0];
			dsp->fRec84[1] = dsp->fRec84[0];
			dsp->fRec83[2] = dsp->fRec83[1];
			dsp->fRec83[1] = dsp->fRec83[0];
			dsp->fRec82[2] = dsp->fRec82[1];
			dsp->fRec82[1] = dsp->fRec82[0];
			dsp->fRec81[2] = dsp->fRec81[1];
			dsp->fRec81[1] = dsp->fRec81[0];
			dsp->fRec88[1] = dsp->fRec88[0];
			dsp->fRec94[1] = dsp->fRec94[0];
			dsp->fRec93[2] = dsp->fRec93[1];
			dsp->fRec93[1] = dsp->fRec93[0];
			dsp->fRec92[2] = dsp->fRec92[1];
			dsp->fRec92[1] = dsp->fRec92[0];
			dsp->fVec8[1] = dsp->fVec8[0];
			dsp->fRec91[1] = dsp->fRec91[0];
			dsp->fRec90[2] = dsp->fRec90[1];
			dsp->fRec90[1] = dsp->fRec90[0];
			dsp->fRec89[2] = dsp->fRec89[1];
			dsp->fRec89[1] = dsp->fRec89[0];
			dsp->fRec95[1] = dsp->fRec95[0];
			dsp->fRec98[1] = dsp->fRec98[0];
			dsp->fRec97[2] = dsp->fRec97[1];
			dsp->fRec97[1] = dsp->fRec97[0];
			dsp->fRec96[2] = dsp->fRec96[1];
			dsp->fRec96[1] = dsp->fRec96[0];
			dsp->fRec99[1] = dsp->fRec99[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
