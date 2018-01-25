/* ------------------------------------------------------------
name: "violin2"
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

static float mydsp_faustpower4_f(float value) {
	return (((value * value) * value) * value);
	
}
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
	
	int iRec10[2];
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	float fRec26[2];
	float fRec22[2];
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	float fRec28[2];
	float fRec27[2];
	float fRec29[4];
	int IOTA;
	float fRec30[2048];
	float fConst6;
	float fVec0[2];
	float fVec1[2048];
	float fRec18[2048];
	float fRec20[2];
	float fRec16[4];
	float fConst7;
	float fConst8;
	float fRec14[3];
	float fConst9;
	int iRec6[2];
	float fRec2[2048];
	float fRec0[2];
	int iRec42[2];
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT fHslider5;
	float fRec58[2];
	float fRec54[2];
	FAUSTFLOAT fHslider6;
	float fRec59[4];
	float fRec60[2048];
	float fVec2[2];
	float fVec3[2048];
	float fRec50[2048];
	float fRec52[2];
	float fRec48[4];
	float fRec46[3];
	int iRec38[2];
	float fRec34[2048];
	float fRec32[2];
	int iRec72[2];
	FAUSTFLOAT fHslider7;
	FAUSTFLOAT fHslider8;
	float fRec88[2];
	float fRec84[2];
	FAUSTFLOAT fHslider9;
	float fRec89[4];
	float fRec90[2048];
	float fVec4[2];
	float fVec5[2048];
	float fRec80[2048];
	float fRec82[2];
	float fRec78[4];
	float fRec76[3];
	int iRec68[2];
	float fRec64[2048];
	float fRec62[2];
	int iRec102[2];
	FAUSTFLOAT fHslider10;
	FAUSTFLOAT fHslider11;
	float fRec118[2];
	float fRec114[2];
	FAUSTFLOAT fHslider12;
	float fRec119[4];
	float fRec120[2048];
	float fVec6[2];
	float fVec7[2048];
	float fRec110[2048];
	float fRec112[2];
	float fRec108[4];
	float fRec106[3];
	int iRec98[2];
	float fRec94[2048];
	float fRec92[2];
	
} mydsp;

mydsp* newmydsp() { 
	mydsp* dsp = (mydsp*)malloc(sizeof(mydsp));
	return dsp;
}

void deletemydsp(mydsp* dsp) { 
	free(dsp);
}

void metadatamydsp(MetaGlue* m) { 
	m->declare(m->metaInterface, "delays.lib/name", "Faust Delay Library");
	m->declare(m->metaInterface, "delays.lib/version", "0.0");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "interface", "SmartKeyboard{  'Number of Keyboards':'4',  'Max Keyboard Polyphony':'0',  'Rounding Mode':'2',  'Send Fingers Count':'1',  'Keyboard 0 - Number of Keys':'12',  'Keyboard 1 - Number of Keys':'12',  'Keyboard 2 - Number of Keys':'12',  'Keyboard 3 - Number of Keys':'12',  'Keyboard 0 - Lowest Key':'55',  'Keyboard 1 - Lowest Key':'62',  'Keyboard 2 - Lowest Key':'69',  'Keyboard 3 - Lowest Key':'76',  'Keyboard 0 - Send Keyboard Freq':'1',  'Keyboard 1 - Send Keyboard Freq':'1',  'Keyboard 2 - Send Keyboard Freq':'1',  'Keyboard 3 - Send Keyboard Freq':'1',  'Keyboard 0 - Send Y':'1',  'Keyboard 1 - Send Y':'1',  'Keyboard 2 - Send Y':'1',  'Keyboard 3 - Send Y':'1' }");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "violin2");
	m->declare(m->metaInterface, "routes.lib/name", "Faust Signal Routing Library");
	m->declare(m->metaInterface, "routes.lib/version", "0.0");
	m->declare(m->metaInterface, "signals.lib/name", "Faust Signal Routing Library");
	m->declare(m->metaInterface, "signals.lib/version", "0.0");
}

int getSampleRatemydsp(mydsp* dsp) { return dsp->fSamplingFreq; }

int getNumInputsmydsp(mydsp* dsp) {
	return 0;
	
}
int getNumOutputsmydsp(mydsp* dsp) {
	return 2;
	
}
int getInputRatemydsp(mydsp* dsp, int channel) {
	int rate;
	switch (channel) {
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
	dsp->fHslider0 = (FAUSTFLOAT)220.0f;
	dsp->fHslider1 = (FAUSTFLOAT)1.0f;
	dsp->fHslider2 = (FAUSTFLOAT)0.0f;
	dsp->fHslider3 = (FAUSTFLOAT)0.0f;
	dsp->fHslider4 = (FAUSTFLOAT)330.0f;
	dsp->fHslider5 = (FAUSTFLOAT)1.0f;
	dsp->fHslider6 = (FAUSTFLOAT)0.0f;
	dsp->fHslider7 = (FAUSTFLOAT)440.0f;
	dsp->fHslider8 = (FAUSTFLOAT)1.0f;
	dsp->fHslider9 = (FAUSTFLOAT)0.0f;
	dsp->fHslider10 = (FAUSTFLOAT)550.0f;
	dsp->fHslider11 = (FAUSTFLOAT)1.0f;
	dsp->fHslider12 = (FAUSTFLOAT)0.0f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			dsp->iRec10[l0] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			dsp->fRec26[l1] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			dsp->fRec22[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			dsp->fRec28[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			dsp->fRec27[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 4); l5 = (l5 + 1)) {
			dsp->fRec29[l5] = 0.0f;
			
		}
		
	}
	dsp->IOTA = 0;
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 2048); l6 = (l6 + 1)) {
			dsp->fRec30[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			dsp->fVec0[l7] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 2048); l8 = (l8 + 1)) {
			dsp->fVec1[l8] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 2048); l9 = (l9 + 1)) {
			dsp->fRec18[l9] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			dsp->fRec20[l10] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 4); l11 = (l11 + 1)) {
			dsp->fRec16[l11] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 3); l12 = (l12 + 1)) {
			dsp->fRec14[l12] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l13;
		for (l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			dsp->iRec6[l13] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l14;
		for (l14 = 0; (l14 < 2048); l14 = (l14 + 1)) {
			dsp->fRec2[l14] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l15;
		for (l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			dsp->fRec0[l15] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l16;
		for (l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			dsp->iRec42[l16] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l17;
		for (l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			dsp->fRec58[l17] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l18;
		for (l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			dsp->fRec54[l18] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l19;
		for (l19 = 0; (l19 < 4); l19 = (l19 + 1)) {
			dsp->fRec59[l19] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l20;
		for (l20 = 0; (l20 < 2048); l20 = (l20 + 1)) {
			dsp->fRec60[l20] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l21;
		for (l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			dsp->fVec2[l21] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l22;
		for (l22 = 0; (l22 < 2048); l22 = (l22 + 1)) {
			dsp->fVec3[l22] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l23;
		for (l23 = 0; (l23 < 2048); l23 = (l23 + 1)) {
			dsp->fRec50[l23] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l24;
		for (l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			dsp->fRec52[l24] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l25;
		for (l25 = 0; (l25 < 4); l25 = (l25 + 1)) {
			dsp->fRec48[l25] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l26;
		for (l26 = 0; (l26 < 3); l26 = (l26 + 1)) {
			dsp->fRec46[l26] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l27;
		for (l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			dsp->iRec38[l27] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l28;
		for (l28 = 0; (l28 < 2048); l28 = (l28 + 1)) {
			dsp->fRec34[l28] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l29;
		for (l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			dsp->fRec32[l29] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l30;
		for (l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			dsp->iRec72[l30] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l31;
		for (l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			dsp->fRec88[l31] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l32;
		for (l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			dsp->fRec84[l32] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l33;
		for (l33 = 0; (l33 < 4); l33 = (l33 + 1)) {
			dsp->fRec89[l33] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l34;
		for (l34 = 0; (l34 < 2048); l34 = (l34 + 1)) {
			dsp->fRec90[l34] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l35;
		for (l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			dsp->fVec4[l35] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l36;
		for (l36 = 0; (l36 < 2048); l36 = (l36 + 1)) {
			dsp->fVec5[l36] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l37;
		for (l37 = 0; (l37 < 2048); l37 = (l37 + 1)) {
			dsp->fRec80[l37] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l38;
		for (l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			dsp->fRec82[l38] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l39;
		for (l39 = 0; (l39 < 4); l39 = (l39 + 1)) {
			dsp->fRec78[l39] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l40;
		for (l40 = 0; (l40 < 3); l40 = (l40 + 1)) {
			dsp->fRec76[l40] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l41;
		for (l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			dsp->iRec68[l41] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l42;
		for (l42 = 0; (l42 < 2048); l42 = (l42 + 1)) {
			dsp->fRec64[l42] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l43;
		for (l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			dsp->fRec62[l43] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l44;
		for (l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			dsp->iRec102[l44] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l45;
		for (l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			dsp->fRec118[l45] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l46;
		for (l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			dsp->fRec114[l46] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l47;
		for (l47 = 0; (l47 < 4); l47 = (l47 + 1)) {
			dsp->fRec119[l47] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l48;
		for (l48 = 0; (l48 < 2048); l48 = (l48 + 1)) {
			dsp->fRec120[l48] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l49;
		for (l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			dsp->fVec6[l49] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l50;
		for (l50 = 0; (l50 < 2048); l50 = (l50 + 1)) {
			dsp->fVec7[l50] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l51;
		for (l51 = 0; (l51 < 2048); l51 = (l51 + 1)) {
			dsp->fRec110[l51] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l52;
		for (l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			dsp->fRec112[l52] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l53;
		for (l53 = 0; (l53 < 4); l53 = (l53 + 1)) {
			dsp->fRec108[l53] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l54;
		for (l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			dsp->fRec106[l54] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l55;
		for (l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			dsp->iRec98[l55] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l56;
		for (l56 = 0; (l56 < 2048); l56 = (l56 + 1)) {
			dsp->fRec94[l56] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l57;
		for (l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			dsp->fRec92[l57] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = tanf((1570.79639f / dsp->fConst0));
	dsp->fConst2 = (1.0f / dsp->fConst1);
	dsp->fConst3 = (1.0f / (((dsp->fConst2 + 0.5f) / dsp->fConst1) + 1.0f));
	dsp->fConst4 = (0.00882352982f * dsp->fConst0);
	dsp->fConst5 = (0.000441176468f * dsp->fConst0);
	dsp->fConst6 = (0.0010294118f * dsp->fConst0);
	dsp->fConst7 = (((dsp->fConst2 + -0.5f) / dsp->fConst1) + 1.0f);
	dsp->fConst8 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(dsp->fConst1))));
	dsp->fConst9 = (0.0f - dsp->fConst2);
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "violin2");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb0bend", &dsp->fHslider1, 1.0f, 0.0f, 10.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb0fingers", &dsp->fHslider2, 0.0f, 0.0f, 10.0f, 1.0f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb0freq", &dsp->fHslider0, 220.0f, 20.0f, 10000.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb1bend", &dsp->fHslider5, 1.0f, 0.0f, 10.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb1fingers", &dsp->fHslider6, 0.0f, 0.0f, 10.0f, 1.0f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb1freq", &dsp->fHslider4, 330.0f, 20.0f, 10000.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb2bend", &dsp->fHslider8, 1.0f, 0.0f, 10.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb2fingers", &dsp->fHslider9, 0.0f, 0.0f, 10.0f, 1.0f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb2freq", &dsp->fHslider7, 440.0f, 20.0f, 10000.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb3bend", &dsp->fHslider11, 1.0f, 0.0f, 10.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb3fingers", &dsp->fHslider12, 0.0f, 0.0f, 10.0f, 1.0f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb3freq", &dsp->fHslider10, 550.0f, 20.0f, 10000.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "y", &dsp->fHslider3, 0.0f, 0.0f, 1.0f, 1.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	float fSlow0 = (0.340000004f / ((float)dsp->fHslider0 * (float)dsp->fHslider1));
	int iSlow1 = ((int)(float)dsp->fHslider2 > 0);
	float fSlow2 = (0.00100000005f * (float)dsp->fHslider3);
	float fSlow3 = (0.340000004f / ((float)dsp->fHslider4 * (float)dsp->fHslider5));
	int iSlow4 = ((int)(float)dsp->fHslider6 > 0);
	float fSlow5 = (0.340000004f / ((float)dsp->fHslider7 * (float)dsp->fHslider8));
	int iSlow6 = ((int)(float)dsp->fHslider9 > 0);
	float fSlow7 = (0.340000004f / ((float)dsp->fHslider10 * (float)dsp->fHslider11));
	int iSlow8 = ((int)(float)dsp->fHslider12 > 0);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->iRec10[0] = 0;
			int iRec11 = dsp->iRec10[1];
			float fRec15 = ((float)dsp->iRec6[1] - (0.989264667f * ((0.600000024f * dsp->fRec16[2]) + (0.200000003f * (dsp->fRec16[1] + dsp->fRec16[3])))));
			dsp->fRec26[0] = (fSlow0 + (0.999000013f * dsp->fRec26[1]));
			float fTemp0 = (dsp->fRec26[0] + -0.0799999982f);
			float fTemp1 = (dsp->fConst5 * fTemp0);
			float fTemp2 = (fTemp1 + -1.49999499f);
			int iTemp3 = (int)fTemp2;
			int iTemp4 = (int)min(dsp->fConst4, (float)max(0, iTemp3));
			float fTemp5 = floorf(fTemp2);
			float fTemp6 = (fTemp1 + (-1.0f - fTemp5));
			float fTemp7 = (0.0f - fTemp6);
			float fTemp8 = (fTemp1 + (-2.0f - fTemp5));
			float fTemp9 = (0.0f - (0.5f * fTemp8));
			float fTemp10 = (fTemp1 + (-3.0f - fTemp5));
			float fTemp11 = (0.0f - (0.333333343f * fTemp10));
			float fTemp12 = (fTemp1 + (-4.0f - fTemp5));
			float fTemp13 = (0.0f - (0.25f * fTemp12));
			float fTemp14 = (fTemp1 - fTemp5);
			int iTemp15 = (int)min(dsp->fConst4, (float)max(0, (iTemp3 + 2)));
			float fTemp16 = (0.0f - fTemp10);
			float fTemp17 = (0.0f - (0.5f * fTemp12));
			int iTemp18 = (int)min(dsp->fConst4, (float)max(0, (iTemp3 + 1)));
			float fTemp19 = (0.0f - fTemp8);
			float fTemp20 = (0.0f - (0.5f * fTemp10));
			float fTemp21 = (0.0f - (0.333333343f * fTemp12));
			float fTemp22 = (fTemp6 * fTemp8);
			int iTemp23 = (int)min(dsp->fConst4, (float)max(0, (iTemp3 + 3)));
			float fTemp24 = (0.0f - fTemp12);
			float fTemp25 = (fTemp22 * fTemp10);
			int iTemp26 = (int)min(dsp->fConst4, (float)max(0, (iTemp3 + 4)));
			dsp->fRec22[0] = (((((dsp->fRec2[((dsp->IOTA - (iTemp4 + 1)) & 2047)] * fTemp7) * fTemp9) * fTemp11) * fTemp13) + (fTemp14 * ((((0.5f * (((fTemp6 * dsp->fRec2[((dsp->IOTA - (iTemp15 + 1)) & 2047)]) * fTemp16) * fTemp17)) + (((dsp->fRec2[((dsp->IOTA - (iTemp18 + 1)) & 2047)] * fTemp19) * fTemp20) * fTemp21)) + (0.166666672f * ((fTemp22 * dsp->fRec2[((dsp->IOTA - (iTemp23 + 1)) & 2047)]) * fTemp24))) + (0.0416666679f * (fTemp25 * dsp->fRec2[((dsp->IOTA - (iTemp26 + 1)) & 2047)])))));
			dsp->fRec28[0] = (fSlow2 + (0.999000013f * dsp->fRec28[1]));
			dsp->fRec27[0] = ((0.999000013f * dsp->fRec27[1]) + (0.00100000005f * min(1.0f, (3000.0f * fabsf((dsp->fRec28[0] - dsp->fRec28[1]))))));
			dsp->fRec29[0] = dsp->fRec0[1];
			dsp->fRec30[(dsp->IOTA & 2047)] = (0.0f - (0.99880147f * ((0.800000012f * dsp->fRec29[2]) + (0.100000001f * (dsp->fRec29[1] + dsp->fRec29[3])))));
			int iRec31 = 0;
			float fTemp27 = (dsp->fConst6 * fTemp0);
			float fTemp28 = (fTemp27 + -1.49999499f);
			int iTemp29 = (int)fTemp28;
			int iTemp30 = (int)min(dsp->fConst4, (float)max(0, iTemp29));
			float fTemp31 = floorf(fTemp28);
			float fTemp32 = (fTemp27 + (-1.0f - fTemp31));
			float fTemp33 = (0.0f - fTemp32);
			float fTemp34 = (fTemp27 + (-2.0f - fTemp31));
			float fTemp35 = (0.0f - (0.5f * fTemp34));
			float fTemp36 = (fTemp27 + (-3.0f - fTemp31));
			float fTemp37 = (0.0f - (0.333333343f * fTemp36));
			float fTemp38 = (fTemp27 + (-4.0f - fTemp31));
			float fTemp39 = (0.0f - (0.25f * fTemp38));
			float fTemp40 = (fTemp27 - fTemp31);
			int iTemp41 = (int)min(dsp->fConst4, (float)max(0, (iTemp29 + 2)));
			float fTemp42 = (0.0f - fTemp36);
			float fTemp43 = (0.0f - (0.5f * fTemp38));
			int iTemp44 = (int)min(dsp->fConst4, (float)max(0, (iTemp29 + 1)));
			float fTemp45 = (0.0f - fTemp34);
			float fTemp46 = (0.0f - (0.5f * fTemp36));
			float fTemp47 = (0.0f - (0.333333343f * fTemp38));
			float fTemp48 = (fTemp32 * fTemp34);
			int iTemp49 = (int)min(dsp->fConst4, (float)max(0, (iTemp29 + 3)));
			float fTemp50 = (0.0f - fTemp38);
			float fTemp51 = (fTemp48 * fTemp36);
			int iTemp52 = (int)min(dsp->fConst4, (float)max(0, (iTemp29 + 4)));
			dsp->fVec0[0] = (((((dsp->fRec30[((dsp->IOTA - (iTemp30 + 2)) & 2047)] * fTemp33) * fTemp35) * fTemp37) * fTemp39) + (fTemp40 * ((((0.5f * (((fTemp32 * dsp->fRec30[((dsp->IOTA - (iTemp41 + 2)) & 2047)]) * fTemp42) * fTemp43)) + (((dsp->fRec30[((dsp->IOTA - (iTemp44 + 2)) & 2047)] * fTemp45) * fTemp46) * fTemp47)) + (0.166666672f * ((fTemp48 * dsp->fRec30[((dsp->IOTA - (iTemp49 + 2)) & 2047)]) * fTemp50))) + (0.0416666679f * (fTemp51 * dsp->fRec30[((dsp->IOTA - (iTemp52 + 2)) & 2047)])))));
			float fTemp53 = (((float)iSlow1 * dsp->fRec27[0]) - (dsp->fRec22[1] + dsp->fVec0[1]));
			float fTemp54 = (fTemp53 * min(1.0f, (1.0f / mydsp_faustpower4_f((fabsf((3.0f * fTemp53)) + 0.75f)))));
			float fRec23 = (dsp->fRec22[1] + fTemp54);
			float fTemp55 = (dsp->fVec0[1] + fTemp54);
			dsp->fVec1[(dsp->IOTA & 2047)] = fTemp55;
			float fRec24 = (((((fTemp7 * fTemp9) * fTemp11) * fTemp13) * dsp->fVec1[((dsp->IOTA - iTemp4) & 2047)]) + (fTemp14 * ((0.0416666679f * (fTemp25 * dsp->fVec1[((dsp->IOTA - iTemp26) & 2047)])) + (((((fTemp19 * fTemp20) * fTemp21) * dsp->fVec1[((dsp->IOTA - iTemp18) & 2047)]) + (0.5f * (((fTemp6 * fTemp16) * fTemp17) * dsp->fVec1[((dsp->IOTA - iTemp15) & 2047)]))) + (0.166666672f * ((fTemp22 * fTemp24) * dsp->fVec1[((dsp->IOTA - iTemp23) & 2047)]))))));
			int iRec25 = iRec31;
			dsp->fRec18[(dsp->IOTA & 2047)] = fRec23;
			float fRec19 = (((((fTemp33 * fTemp35) * fTemp37) * fTemp39) * dsp->fRec18[((dsp->IOTA - (iTemp30 + 1)) & 2047)]) + (fTemp40 * (((0.166666672f * ((fTemp48 * fTemp50) * dsp->fRec18[((dsp->IOTA - (iTemp49 + 1)) & 2047)])) + ((((fTemp45 * fTemp46) * fTemp47) * dsp->fRec18[((dsp->IOTA - (iTemp44 + 1)) & 2047)]) + (0.5f * (((fTemp32 * fTemp42) * fTemp43) * dsp->fRec18[((dsp->IOTA - (iTemp41 + 1)) & 2047)])))) + (0.0416666679f * (fTemp51 * dsp->fRec18[((dsp->IOTA - (iTemp52 + 1)) & 2047)])))));
			dsp->fRec20[0] = fRec24;
			int iRec21 = iRec25;
			dsp->fRec16[0] = dsp->fRec20[1];
			int iRec17 = iRec21;
			dsp->fRec14[0] = (dsp->fRec16[1] - (dsp->fConst3 * ((dsp->fConst7 * dsp->fRec14[2]) + (dsp->fConst8 * dsp->fRec14[1]))));
			float fTemp56 = (dsp->fConst3 * ((dsp->fConst2 * dsp->fRec14[0]) + (dsp->fConst9 * dsp->fRec14[2])));
			float fRec12 = fTemp56;
			float fRec13 = ((float)iRec17 + fTemp56);
			dsp->iRec6[0] = iRec11;
			float fRec7 = fRec15;
			float fRec8 = fRec12;
			float fRec9 = fRec13;
			dsp->fRec2[(dsp->IOTA & 2047)] = fRec7;
			float fRec3 = fRec19;
			float fRec4 = fRec8;
			float fRec5 = fRec9;
			dsp->fRec0[0] = fRec3;
			float fRec1 = fRec5;
			dsp->iRec42[0] = 0;
			int iRec43 = dsp->iRec42[1];
			float fRec47 = ((float)dsp->iRec38[1] - (0.989264667f * ((0.600000024f * dsp->fRec48[2]) + (0.200000003f * (dsp->fRec48[1] + dsp->fRec48[3])))));
			dsp->fRec58[0] = (fSlow3 + (0.999000013f * dsp->fRec58[1]));
			float fTemp57 = (dsp->fRec58[0] + -0.0799999982f);
			float fTemp58 = (dsp->fConst5 * fTemp57);
			float fTemp59 = (fTemp58 + -1.49999499f);
			int iTemp60 = (int)fTemp59;
			int iTemp61 = (int)min(dsp->fConst4, (float)max(0, iTemp60));
			float fTemp62 = floorf(fTemp59);
			float fTemp63 = (fTemp58 + (-1.0f - fTemp62));
			float fTemp64 = (0.0f - fTemp63);
			float fTemp65 = (fTemp58 + (-2.0f - fTemp62));
			float fTemp66 = (0.0f - (0.5f * fTemp65));
			float fTemp67 = (fTemp58 + (-3.0f - fTemp62));
			float fTemp68 = (0.0f - (0.333333343f * fTemp67));
			float fTemp69 = (fTemp58 + (-4.0f - fTemp62));
			float fTemp70 = (0.0f - (0.25f * fTemp69));
			float fTemp71 = (fTemp58 - fTemp62);
			int iTemp72 = (int)min(dsp->fConst4, (float)max(0, (iTemp60 + 2)));
			float fTemp73 = (0.0f - fTemp67);
			float fTemp74 = (0.0f - (0.5f * fTemp69));
			int iTemp75 = (int)min(dsp->fConst4, (float)max(0, (iTemp60 + 1)));
			float fTemp76 = (0.0f - fTemp65);
			float fTemp77 = (0.0f - (0.5f * fTemp67));
			float fTemp78 = (0.0f - (0.333333343f * fTemp69));
			float fTemp79 = (fTemp63 * fTemp65);
			int iTemp80 = (int)min(dsp->fConst4, (float)max(0, (iTemp60 + 3)));
			float fTemp81 = (0.0f - fTemp69);
			float fTemp82 = (fTemp79 * fTemp67);
			int iTemp83 = (int)min(dsp->fConst4, (float)max(0, (iTemp60 + 4)));
			dsp->fRec54[0] = (((((dsp->fRec34[((dsp->IOTA - (iTemp61 + 1)) & 2047)] * fTemp64) * fTemp66) * fTemp68) * fTemp70) + (fTemp71 * ((((0.5f * (((fTemp63 * dsp->fRec34[((dsp->IOTA - (iTemp72 + 1)) & 2047)]) * fTemp73) * fTemp74)) + (((dsp->fRec34[((dsp->IOTA - (iTemp75 + 1)) & 2047)] * fTemp76) * fTemp77) * fTemp78)) + (0.166666672f * ((fTemp79 * dsp->fRec34[((dsp->IOTA - (iTemp80 + 1)) & 2047)]) * fTemp81))) + (0.0416666679f * (fTemp82 * dsp->fRec34[((dsp->IOTA - (iTemp83 + 1)) & 2047)])))));
			dsp->fRec59[0] = dsp->fRec32[1];
			dsp->fRec60[(dsp->IOTA & 2047)] = (0.0f - (0.99880147f * ((0.800000012f * dsp->fRec59[2]) + (0.100000001f * (dsp->fRec59[1] + dsp->fRec59[3])))));
			int iRec61 = 0;
			float fTemp84 = (dsp->fConst6 * fTemp57);
			float fTemp85 = (fTemp84 + -1.49999499f);
			int iTemp86 = (int)fTemp85;
			int iTemp87 = (int)min(dsp->fConst4, (float)max(0, iTemp86));
			float fTemp88 = floorf(fTemp85);
			float fTemp89 = (fTemp84 + (-1.0f - fTemp88));
			float fTemp90 = (0.0f - fTemp89);
			float fTemp91 = (fTemp84 + (-2.0f - fTemp88));
			float fTemp92 = (0.0f - (0.5f * fTemp91));
			float fTemp93 = (fTemp84 + (-3.0f - fTemp88));
			float fTemp94 = (0.0f - (0.333333343f * fTemp93));
			float fTemp95 = (fTemp84 + (-4.0f - fTemp88));
			float fTemp96 = (0.0f - (0.25f * fTemp95));
			float fTemp97 = (fTemp84 - fTemp88);
			int iTemp98 = (int)min(dsp->fConst4, (float)max(0, (iTemp86 + 2)));
			float fTemp99 = (0.0f - fTemp93);
			float fTemp100 = (0.0f - (0.5f * fTemp95));
			int iTemp101 = (int)min(dsp->fConst4, (float)max(0, (iTemp86 + 1)));
			float fTemp102 = (0.0f - fTemp91);
			float fTemp103 = (0.0f - (0.5f * fTemp93));
			float fTemp104 = (0.0f - (0.333333343f * fTemp95));
			float fTemp105 = (fTemp89 * fTemp91);
			int iTemp106 = (int)min(dsp->fConst4, (float)max(0, (iTemp86 + 3)));
			float fTemp107 = (0.0f - fTemp95);
			float fTemp108 = (fTemp105 * fTemp93);
			int iTemp109 = (int)min(dsp->fConst4, (float)max(0, (iTemp86 + 4)));
			dsp->fVec2[0] = (((((dsp->fRec60[((dsp->IOTA - (iTemp87 + 2)) & 2047)] * fTemp90) * fTemp92) * fTemp94) * fTemp96) + (fTemp97 * ((((0.5f * (((fTemp89 * dsp->fRec60[((dsp->IOTA - (iTemp98 + 2)) & 2047)]) * fTemp99) * fTemp100)) + (((dsp->fRec60[((dsp->IOTA - (iTemp101 + 2)) & 2047)] * fTemp102) * fTemp103) * fTemp104)) + (0.166666672f * ((fTemp105 * dsp->fRec60[((dsp->IOTA - (iTemp106 + 2)) & 2047)]) * fTemp107))) + (0.0416666679f * (fTemp108 * dsp->fRec60[((dsp->IOTA - (iTemp109 + 2)) & 2047)])))));
			float fTemp110 = (((float)iSlow4 * dsp->fRec27[0]) - (dsp->fRec54[1] + dsp->fVec2[1]));
			float fTemp111 = (fTemp110 * min(1.0f, (1.0f / mydsp_faustpower4_f((fabsf((3.0f * fTemp110)) + 0.75f)))));
			float fRec55 = (dsp->fRec54[1] + fTemp111);
			float fTemp112 = (dsp->fVec2[1] + fTemp111);
			dsp->fVec3[(dsp->IOTA & 2047)] = fTemp112;
			float fRec56 = (((((fTemp64 * fTemp66) * fTemp68) * fTemp70) * dsp->fVec3[((dsp->IOTA - iTemp61) & 2047)]) + (fTemp71 * ((0.0416666679f * (fTemp82 * dsp->fVec3[((dsp->IOTA - iTemp83) & 2047)])) + (((((fTemp76 * fTemp77) * fTemp78) * dsp->fVec3[((dsp->IOTA - iTemp75) & 2047)]) + (0.5f * (((fTemp63 * fTemp73) * fTemp74) * dsp->fVec3[((dsp->IOTA - iTemp72) & 2047)]))) + (0.166666672f * ((fTemp79 * fTemp81) * dsp->fVec3[((dsp->IOTA - iTemp80) & 2047)]))))));
			int iRec57 = iRec61;
			dsp->fRec50[(dsp->IOTA & 2047)] = fRec55;
			float fRec51 = (((((fTemp90 * fTemp92) * fTemp94) * fTemp96) * dsp->fRec50[((dsp->IOTA - (iTemp87 + 1)) & 2047)]) + (fTemp97 * (((0.166666672f * ((fTemp105 * fTemp107) * dsp->fRec50[((dsp->IOTA - (iTemp106 + 1)) & 2047)])) + ((((fTemp102 * fTemp103) * fTemp104) * dsp->fRec50[((dsp->IOTA - (iTemp101 + 1)) & 2047)]) + (0.5f * (((fTemp89 * fTemp99) * fTemp100) * dsp->fRec50[((dsp->IOTA - (iTemp98 + 1)) & 2047)])))) + (0.0416666679f * (fTemp108 * dsp->fRec50[((dsp->IOTA - (iTemp109 + 1)) & 2047)])))));
			dsp->fRec52[0] = fRec56;
			int iRec53 = iRec57;
			dsp->fRec48[0] = dsp->fRec52[1];
			int iRec49 = iRec53;
			dsp->fRec46[0] = (dsp->fRec48[1] - (dsp->fConst3 * ((dsp->fConst8 * dsp->fRec46[1]) + (dsp->fConst7 * dsp->fRec46[2]))));
			float fTemp113 = (dsp->fConst3 * ((dsp->fConst2 * dsp->fRec46[0]) + (dsp->fConst9 * dsp->fRec46[2])));
			float fRec44 = fTemp113;
			float fRec45 = ((float)iRec49 + fTemp113);
			dsp->iRec38[0] = iRec43;
			float fRec39 = fRec47;
			float fRec40 = fRec44;
			float fRec41 = fRec45;
			dsp->fRec34[(dsp->IOTA & 2047)] = fRec39;
			float fRec35 = fRec51;
			float fRec36 = fRec40;
			float fRec37 = fRec41;
			dsp->fRec32[0] = fRec35;
			float fRec33 = fRec37;
			dsp->iRec72[0] = 0;
			int iRec73 = dsp->iRec72[1];
			float fRec77 = ((float)dsp->iRec68[1] - (0.989264667f * ((0.600000024f * dsp->fRec78[2]) + (0.200000003f * (dsp->fRec78[1] + dsp->fRec78[3])))));
			dsp->fRec88[0] = (fSlow5 + (0.999000013f * dsp->fRec88[1]));
			float fTemp114 = (dsp->fRec88[0] + -0.0799999982f);
			float fTemp115 = (dsp->fConst5 * fTemp114);
			float fTemp116 = (fTemp115 + -1.49999499f);
			int iTemp117 = (int)fTemp116;
			int iTemp118 = (int)min(dsp->fConst4, (float)max(0, iTemp117));
			float fTemp119 = floorf(fTemp116);
			float fTemp120 = (fTemp115 + (-1.0f - fTemp119));
			float fTemp121 = (0.0f - fTemp120);
			float fTemp122 = (fTemp115 + (-2.0f - fTemp119));
			float fTemp123 = (0.0f - (0.5f * fTemp122));
			float fTemp124 = (fTemp115 + (-3.0f - fTemp119));
			float fTemp125 = (0.0f - (0.333333343f * fTemp124));
			float fTemp126 = (fTemp115 + (-4.0f - fTemp119));
			float fTemp127 = (0.0f - (0.25f * fTemp126));
			float fTemp128 = (fTemp115 - fTemp119);
			int iTemp129 = (int)min(dsp->fConst4, (float)max(0, (iTemp117 + 2)));
			float fTemp130 = (0.0f - fTemp124);
			float fTemp131 = (0.0f - (0.5f * fTemp126));
			int iTemp132 = (int)min(dsp->fConst4, (float)max(0, (iTemp117 + 1)));
			float fTemp133 = (0.0f - fTemp122);
			float fTemp134 = (0.0f - (0.5f * fTemp124));
			float fTemp135 = (0.0f - (0.333333343f * fTemp126));
			float fTemp136 = (fTemp120 * fTemp122);
			int iTemp137 = (int)min(dsp->fConst4, (float)max(0, (iTemp117 + 3)));
			float fTemp138 = (0.0f - fTemp126);
			float fTemp139 = (fTemp136 * fTemp124);
			int iTemp140 = (int)min(dsp->fConst4, (float)max(0, (iTemp117 + 4)));
			dsp->fRec84[0] = (((((dsp->fRec64[((dsp->IOTA - (iTemp118 + 1)) & 2047)] * fTemp121) * fTemp123) * fTemp125) * fTemp127) + (fTemp128 * ((((0.5f * (((fTemp120 * dsp->fRec64[((dsp->IOTA - (iTemp129 + 1)) & 2047)]) * fTemp130) * fTemp131)) + (((dsp->fRec64[((dsp->IOTA - (iTemp132 + 1)) & 2047)] * fTemp133) * fTemp134) * fTemp135)) + (0.166666672f * ((fTemp136 * dsp->fRec64[((dsp->IOTA - (iTemp137 + 1)) & 2047)]) * fTemp138))) + (0.0416666679f * (fTemp139 * dsp->fRec64[((dsp->IOTA - (iTemp140 + 1)) & 2047)])))));
			dsp->fRec89[0] = dsp->fRec62[1];
			dsp->fRec90[(dsp->IOTA & 2047)] = (0.0f - (0.99880147f * ((0.800000012f * dsp->fRec89[2]) + (0.100000001f * (dsp->fRec89[1] + dsp->fRec89[3])))));
			int iRec91 = 0;
			float fTemp141 = (dsp->fConst6 * fTemp114);
			float fTemp142 = (fTemp141 + -1.49999499f);
			int iTemp143 = (int)fTemp142;
			int iTemp144 = (int)min(dsp->fConst4, (float)max(0, iTemp143));
			float fTemp145 = floorf(fTemp142);
			float fTemp146 = (fTemp141 + (-1.0f - fTemp145));
			float fTemp147 = (0.0f - fTemp146);
			float fTemp148 = (fTemp141 + (-2.0f - fTemp145));
			float fTemp149 = (0.0f - (0.5f * fTemp148));
			float fTemp150 = (fTemp141 + (-3.0f - fTemp145));
			float fTemp151 = (0.0f - (0.333333343f * fTemp150));
			float fTemp152 = (fTemp141 + (-4.0f - fTemp145));
			float fTemp153 = (0.0f - (0.25f * fTemp152));
			float fTemp154 = (fTemp141 - fTemp145);
			int iTemp155 = (int)min(dsp->fConst4, (float)max(0, (iTemp143 + 2)));
			float fTemp156 = (0.0f - fTemp150);
			float fTemp157 = (0.0f - (0.5f * fTemp152));
			int iTemp158 = (int)min(dsp->fConst4, (float)max(0, (iTemp143 + 1)));
			float fTemp159 = (0.0f - fTemp148);
			float fTemp160 = (0.0f - (0.5f * fTemp150));
			float fTemp161 = (0.0f - (0.333333343f * fTemp152));
			float fTemp162 = (fTemp146 * fTemp148);
			int iTemp163 = (int)min(dsp->fConst4, (float)max(0, (iTemp143 + 3)));
			float fTemp164 = (0.0f - fTemp152);
			float fTemp165 = (fTemp162 * fTemp150);
			int iTemp166 = (int)min(dsp->fConst4, (float)max(0, (iTemp143 + 4)));
			dsp->fVec4[0] = (((((dsp->fRec90[((dsp->IOTA - (iTemp144 + 2)) & 2047)] * fTemp147) * fTemp149) * fTemp151) * fTemp153) + (fTemp154 * ((((0.5f * (((fTemp146 * dsp->fRec90[((dsp->IOTA - (iTemp155 + 2)) & 2047)]) * fTemp156) * fTemp157)) + (((dsp->fRec90[((dsp->IOTA - (iTemp158 + 2)) & 2047)] * fTemp159) * fTemp160) * fTemp161)) + (0.166666672f * ((fTemp162 * dsp->fRec90[((dsp->IOTA - (iTemp163 + 2)) & 2047)]) * fTemp164))) + (0.0416666679f * (fTemp165 * dsp->fRec90[((dsp->IOTA - (iTemp166 + 2)) & 2047)])))));
			float fTemp167 = (((float)iSlow6 * dsp->fRec27[0]) - (dsp->fRec84[1] + dsp->fVec4[1]));
			float fTemp168 = (fTemp167 * min(1.0f, (1.0f / mydsp_faustpower4_f((fabsf((3.0f * fTemp167)) + 0.75f)))));
			float fRec85 = (dsp->fRec84[1] + fTemp168);
			float fTemp169 = (dsp->fVec4[1] + fTemp168);
			dsp->fVec5[(dsp->IOTA & 2047)] = fTemp169;
			float fRec86 = (((((fTemp121 * fTemp123) * fTemp125) * fTemp127) * dsp->fVec5[((dsp->IOTA - iTemp118) & 2047)]) + (fTemp128 * ((0.0416666679f * (fTemp139 * dsp->fVec5[((dsp->IOTA - iTemp140) & 2047)])) + (((((fTemp133 * fTemp134) * fTemp135) * dsp->fVec5[((dsp->IOTA - iTemp132) & 2047)]) + (0.5f * (((fTemp120 * fTemp130) * fTemp131) * dsp->fVec5[((dsp->IOTA - iTemp129) & 2047)]))) + (0.166666672f * ((fTemp136 * fTemp138) * dsp->fVec5[((dsp->IOTA - iTemp137) & 2047)]))))));
			int iRec87 = iRec91;
			dsp->fRec80[(dsp->IOTA & 2047)] = fRec85;
			float fRec81 = (((((fTemp147 * fTemp149) * fTemp151) * fTemp153) * dsp->fRec80[((dsp->IOTA - (iTemp144 + 1)) & 2047)]) + (fTemp154 * (((0.166666672f * ((fTemp162 * fTemp164) * dsp->fRec80[((dsp->IOTA - (iTemp163 + 1)) & 2047)])) + ((((fTemp159 * fTemp160) * fTemp161) * dsp->fRec80[((dsp->IOTA - (iTemp158 + 1)) & 2047)]) + (0.5f * (((fTemp146 * fTemp156) * fTemp157) * dsp->fRec80[((dsp->IOTA - (iTemp155 + 1)) & 2047)])))) + (0.0416666679f * (fTemp165 * dsp->fRec80[((dsp->IOTA - (iTemp166 + 1)) & 2047)])))));
			dsp->fRec82[0] = fRec86;
			int iRec83 = iRec87;
			dsp->fRec78[0] = dsp->fRec82[1];
			int iRec79 = iRec83;
			dsp->fRec76[0] = (dsp->fRec78[1] - (dsp->fConst3 * ((dsp->fConst8 * dsp->fRec76[1]) + (dsp->fConst7 * dsp->fRec76[2]))));
			float fTemp170 = (dsp->fConst3 * ((dsp->fConst2 * dsp->fRec76[0]) + (dsp->fConst9 * dsp->fRec76[2])));
			float fRec74 = fTemp170;
			float fRec75 = ((float)iRec79 + fTemp170);
			dsp->iRec68[0] = iRec73;
			float fRec69 = fRec77;
			float fRec70 = fRec74;
			float fRec71 = fRec75;
			dsp->fRec64[(dsp->IOTA & 2047)] = fRec69;
			float fRec65 = fRec81;
			float fRec66 = fRec70;
			float fRec67 = fRec71;
			dsp->fRec62[0] = fRec65;
			float fRec63 = fRec67;
			dsp->iRec102[0] = 0;
			int iRec103 = dsp->iRec102[1];
			float fRec107 = ((float)dsp->iRec98[1] - (0.989264667f * ((0.600000024f * dsp->fRec108[2]) + (0.200000003f * (dsp->fRec108[1] + dsp->fRec108[3])))));
			dsp->fRec118[0] = (fSlow7 + (0.999000013f * dsp->fRec118[1]));
			float fTemp171 = (dsp->fRec118[0] + -0.0799999982f);
			float fTemp172 = (dsp->fConst5 * fTemp171);
			float fTemp173 = (fTemp172 + -1.49999499f);
			int iTemp174 = (int)fTemp173;
			int iTemp175 = (int)min(dsp->fConst4, (float)max(0, iTemp174));
			float fTemp176 = floorf(fTemp173);
			float fTemp177 = (fTemp172 + (-1.0f - fTemp176));
			float fTemp178 = (0.0f - fTemp177);
			float fTemp179 = (fTemp172 + (-2.0f - fTemp176));
			float fTemp180 = (0.0f - (0.5f * fTemp179));
			float fTemp181 = (fTemp172 + (-3.0f - fTemp176));
			float fTemp182 = (0.0f - (0.333333343f * fTemp181));
			float fTemp183 = (fTemp172 + (-4.0f - fTemp176));
			float fTemp184 = (0.0f - (0.25f * fTemp183));
			float fTemp185 = (fTemp172 - fTemp176);
			int iTemp186 = (int)min(dsp->fConst4, (float)max(0, (iTemp174 + 2)));
			float fTemp187 = (0.0f - fTemp181);
			float fTemp188 = (0.0f - (0.5f * fTemp183));
			int iTemp189 = (int)min(dsp->fConst4, (float)max(0, (iTemp174 + 1)));
			float fTemp190 = (0.0f - fTemp179);
			float fTemp191 = (0.0f - (0.5f * fTemp181));
			float fTemp192 = (0.0f - (0.333333343f * fTemp183));
			float fTemp193 = (fTemp177 * fTemp179);
			int iTemp194 = (int)min(dsp->fConst4, (float)max(0, (iTemp174 + 3)));
			float fTemp195 = (0.0f - fTemp183);
			float fTemp196 = (fTemp193 * fTemp181);
			int iTemp197 = (int)min(dsp->fConst4, (float)max(0, (iTemp174 + 4)));
			dsp->fRec114[0] = (((((dsp->fRec94[((dsp->IOTA - (iTemp175 + 1)) & 2047)] * fTemp178) * fTemp180) * fTemp182) * fTemp184) + (fTemp185 * ((((0.5f * (((fTemp177 * dsp->fRec94[((dsp->IOTA - (iTemp186 + 1)) & 2047)]) * fTemp187) * fTemp188)) + (((dsp->fRec94[((dsp->IOTA - (iTemp189 + 1)) & 2047)] * fTemp190) * fTemp191) * fTemp192)) + (0.166666672f * ((fTemp193 * dsp->fRec94[((dsp->IOTA - (iTemp194 + 1)) & 2047)]) * fTemp195))) + (0.0416666679f * (fTemp196 * dsp->fRec94[((dsp->IOTA - (iTemp197 + 1)) & 2047)])))));
			dsp->fRec119[0] = dsp->fRec92[1];
			dsp->fRec120[(dsp->IOTA & 2047)] = (0.0f - (0.99880147f * ((0.800000012f * dsp->fRec119[2]) + (0.100000001f * (dsp->fRec119[1] + dsp->fRec119[3])))));
			int iRec121 = 0;
			float fTemp198 = (dsp->fConst6 * fTemp171);
			float fTemp199 = (fTemp198 + -1.49999499f);
			int iTemp200 = (int)fTemp199;
			int iTemp201 = (int)min(dsp->fConst4, (float)max(0, iTemp200));
			float fTemp202 = floorf(fTemp199);
			float fTemp203 = (fTemp198 + (-1.0f - fTemp202));
			float fTemp204 = (0.0f - fTemp203);
			float fTemp205 = (fTemp198 + (-2.0f - fTemp202));
			float fTemp206 = (0.0f - (0.5f * fTemp205));
			float fTemp207 = (fTemp198 + (-3.0f - fTemp202));
			float fTemp208 = (0.0f - (0.333333343f * fTemp207));
			float fTemp209 = (fTemp198 + (-4.0f - fTemp202));
			float fTemp210 = (0.0f - (0.25f * fTemp209));
			float fTemp211 = (fTemp198 - fTemp202);
			int iTemp212 = (int)min(dsp->fConst4, (float)max(0, (iTemp200 + 2)));
			float fTemp213 = (0.0f - fTemp207);
			float fTemp214 = (0.0f - (0.5f * fTemp209));
			int iTemp215 = (int)min(dsp->fConst4, (float)max(0, (iTemp200 + 1)));
			float fTemp216 = (0.0f - fTemp205);
			float fTemp217 = (0.0f - (0.5f * fTemp207));
			float fTemp218 = (0.0f - (0.333333343f * fTemp209));
			float fTemp219 = (fTemp203 * fTemp205);
			int iTemp220 = (int)min(dsp->fConst4, (float)max(0, (iTemp200 + 3)));
			float fTemp221 = (0.0f - fTemp209);
			float fTemp222 = (fTemp219 * fTemp207);
			int iTemp223 = (int)min(dsp->fConst4, (float)max(0, (iTemp200 + 4)));
			dsp->fVec6[0] = (((((dsp->fRec120[((dsp->IOTA - (iTemp201 + 2)) & 2047)] * fTemp204) * fTemp206) * fTemp208) * fTemp210) + (fTemp211 * ((((0.5f * (((fTemp203 * dsp->fRec120[((dsp->IOTA - (iTemp212 + 2)) & 2047)]) * fTemp213) * fTemp214)) + (((dsp->fRec120[((dsp->IOTA - (iTemp215 + 2)) & 2047)] * fTemp216) * fTemp217) * fTemp218)) + (0.166666672f * ((fTemp219 * dsp->fRec120[((dsp->IOTA - (iTemp220 + 2)) & 2047)]) * fTemp221))) + (0.0416666679f * (fTemp222 * dsp->fRec120[((dsp->IOTA - (iTemp223 + 2)) & 2047)])))));
			float fTemp224 = (((float)iSlow8 * dsp->fRec27[0]) - (dsp->fRec114[1] + dsp->fVec6[1]));
			float fTemp225 = (fTemp224 * min(1.0f, (1.0f / mydsp_faustpower4_f((fabsf((3.0f * fTemp224)) + 0.75f)))));
			float fRec115 = (dsp->fRec114[1] + fTemp225);
			float fTemp226 = (dsp->fVec6[1] + fTemp225);
			dsp->fVec7[(dsp->IOTA & 2047)] = fTemp226;
			float fRec116 = (((((fTemp178 * fTemp180) * fTemp182) * fTemp184) * dsp->fVec7[((dsp->IOTA - iTemp175) & 2047)]) + (fTemp185 * ((0.0416666679f * (fTemp196 * dsp->fVec7[((dsp->IOTA - iTemp197) & 2047)])) + (((((fTemp190 * fTemp191) * fTemp192) * dsp->fVec7[((dsp->IOTA - iTemp189) & 2047)]) + (0.5f * (((fTemp177 * fTemp187) * fTemp188) * dsp->fVec7[((dsp->IOTA - iTemp186) & 2047)]))) + (0.166666672f * ((fTemp193 * fTemp195) * dsp->fVec7[((dsp->IOTA - iTemp194) & 2047)]))))));
			int iRec117 = iRec121;
			dsp->fRec110[(dsp->IOTA & 2047)] = fRec115;
			float fRec111 = (((((fTemp204 * fTemp206) * fTemp208) * fTemp210) * dsp->fRec110[((dsp->IOTA - (iTemp201 + 1)) & 2047)]) + (fTemp211 * (((0.166666672f * ((fTemp219 * fTemp221) * dsp->fRec110[((dsp->IOTA - (iTemp220 + 1)) & 2047)])) + ((((fTemp216 * fTemp217) * fTemp218) * dsp->fRec110[((dsp->IOTA - (iTemp215 + 1)) & 2047)]) + (0.5f * (((fTemp203 * fTemp213) * fTemp214) * dsp->fRec110[((dsp->IOTA - (iTemp212 + 1)) & 2047)])))) + (0.0416666679f * (fTemp222 * dsp->fRec110[((dsp->IOTA - (iTemp223 + 1)) & 2047)])))));
			dsp->fRec112[0] = fRec116;
			int iRec113 = iRec117;
			dsp->fRec108[0] = dsp->fRec112[1];
			int iRec109 = iRec113;
			dsp->fRec106[0] = (dsp->fRec108[1] - (dsp->fConst3 * ((dsp->fConst8 * dsp->fRec106[1]) + (dsp->fConst7 * dsp->fRec106[2]))));
			float fTemp227 = (dsp->fConst3 * ((dsp->fConst2 * dsp->fRec106[0]) + (dsp->fConst9 * dsp->fRec106[2])));
			float fRec104 = fTemp227;
			float fRec105 = ((float)iRec109 + fTemp227);
			dsp->iRec98[0] = iRec103;
			float fRec99 = fRec107;
			float fRec100 = fRec104;
			float fRec101 = fRec105;
			dsp->fRec94[(dsp->IOTA & 2047)] = fRec99;
			float fRec95 = fRec111;
			float fRec96 = fRec100;
			float fRec97 = fRec101;
			dsp->fRec92[0] = fRec95;
			float fRec93 = fRec97;
			float fTemp228 = (((fRec1 + fRec33) + fRec63) + fRec93);
			output0[i] = (FAUSTFLOAT)fTemp228;
			output1[i] = (FAUSTFLOAT)fTemp228;
			dsp->iRec10[1] = dsp->iRec10[0];
			dsp->fRec26[1] = dsp->fRec26[0];
			dsp->fRec22[1] = dsp->fRec22[0];
			dsp->fRec28[1] = dsp->fRec28[0];
			dsp->fRec27[1] = dsp->fRec27[0];
			/* C99 loop */
			{
				int j0;
				for (j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
					dsp->fRec29[j0] = dsp->fRec29[(j0 - 1)];
					
				}
				
			}
			dsp->IOTA = (dsp->IOTA + 1);
			dsp->fVec0[1] = dsp->fVec0[0];
			dsp->fRec20[1] = dsp->fRec20[0];
			/* C99 loop */
			{
				int j1;
				for (j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
					dsp->fRec16[j1] = dsp->fRec16[(j1 - 1)];
					
				}
				
			}
			dsp->fRec14[2] = dsp->fRec14[1];
			dsp->fRec14[1] = dsp->fRec14[0];
			dsp->iRec6[1] = dsp->iRec6[0];
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->iRec42[1] = dsp->iRec42[0];
			dsp->fRec58[1] = dsp->fRec58[0];
			dsp->fRec54[1] = dsp->fRec54[0];
			/* C99 loop */
			{
				int j2;
				for (j2 = 3; (j2 > 0); j2 = (j2 - 1)) {
					dsp->fRec59[j2] = dsp->fRec59[(j2 - 1)];
					
				}
				
			}
			dsp->fVec2[1] = dsp->fVec2[0];
			dsp->fRec52[1] = dsp->fRec52[0];
			/* C99 loop */
			{
				int j3;
				for (j3 = 3; (j3 > 0); j3 = (j3 - 1)) {
					dsp->fRec48[j3] = dsp->fRec48[(j3 - 1)];
					
				}
				
			}
			dsp->fRec46[2] = dsp->fRec46[1];
			dsp->fRec46[1] = dsp->fRec46[0];
			dsp->iRec38[1] = dsp->iRec38[0];
			dsp->fRec32[1] = dsp->fRec32[0];
			dsp->iRec72[1] = dsp->iRec72[0];
			dsp->fRec88[1] = dsp->fRec88[0];
			dsp->fRec84[1] = dsp->fRec84[0];
			/* C99 loop */
			{
				int j4;
				for (j4 = 3; (j4 > 0); j4 = (j4 - 1)) {
					dsp->fRec89[j4] = dsp->fRec89[(j4 - 1)];
					
				}
				
			}
			dsp->fVec4[1] = dsp->fVec4[0];
			dsp->fRec82[1] = dsp->fRec82[0];
			/* C99 loop */
			{
				int j5;
				for (j5 = 3; (j5 > 0); j5 = (j5 - 1)) {
					dsp->fRec78[j5] = dsp->fRec78[(j5 - 1)];
					
				}
				
			}
			dsp->fRec76[2] = dsp->fRec76[1];
			dsp->fRec76[1] = dsp->fRec76[0];
			dsp->iRec68[1] = dsp->iRec68[0];
			dsp->fRec62[1] = dsp->fRec62[0];
			dsp->iRec102[1] = dsp->iRec102[0];
			dsp->fRec118[1] = dsp->fRec118[0];
			dsp->fRec114[1] = dsp->fRec114[0];
			/* C99 loop */
			{
				int j6;
				for (j6 = 3; (j6 > 0); j6 = (j6 - 1)) {
					dsp->fRec119[j6] = dsp->fRec119[(j6 - 1)];
					
				}
				
			}
			dsp->fVec6[1] = dsp->fVec6[0];
			dsp->fRec112[1] = dsp->fRec112[0];
			/* C99 loop */
			{
				int j7;
				for (j7 = 3; (j7 > 0); j7 = (j7 - 1)) {
					dsp->fRec108[j7] = dsp->fRec108[(j7 - 1)];
					
				}
				
			}
			dsp->fRec106[2] = dsp->fRec106[1];
			dsp->fRec106[1] = dsp->fRec106[0];
			dsp->iRec98[1] = dsp->iRec98[0];
			dsp->fRec92[1] = dsp->fRec92[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
