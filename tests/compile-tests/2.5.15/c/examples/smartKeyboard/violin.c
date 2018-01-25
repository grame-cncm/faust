/* ------------------------------------------------------------
name: "violin"
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
	FAUSTFLOAT fHslider4;
	float fRec32[2];
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
	int iRec43[2];
	FAUSTFLOAT fHslider5;
	FAUSTFLOAT fHslider6;
	float fRec59[2];
	float fRec55[2];
	FAUSTFLOAT fHslider7;
	float fRec60[4];
	float fRec61[2048];
	float fVec2[2];
	float fVec3[2048];
	float fRec51[2048];
	float fRec53[2];
	float fRec49[4];
	float fRec47[3];
	int iRec39[2];
	float fRec35[2048];
	float fRec33[2];
	int iRec73[2];
	FAUSTFLOAT fHslider8;
	FAUSTFLOAT fHslider9;
	float fRec89[2];
	float fRec85[2];
	FAUSTFLOAT fHslider10;
	float fRec90[4];
	float fRec91[2048];
	float fVec4[2];
	float fVec5[2048];
	float fRec81[2048];
	float fRec83[2];
	float fRec79[4];
	float fRec77[3];
	int iRec69[2];
	float fRec65[2048];
	float fRec63[2];
	int iRec103[2];
	FAUSTFLOAT fHslider11;
	FAUSTFLOAT fHslider12;
	float fRec119[2];
	float fRec115[2];
	FAUSTFLOAT fHslider13;
	float fRec120[4];
	float fRec121[2048];
	float fVec6[2];
	float fVec7[2048];
	float fRec111[2048];
	float fRec113[2];
	float fRec109[4];
	float fRec107[3];
	int iRec99[2];
	float fRec95[2048];
	float fRec93[2];
	
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
	m->declare(m->metaInterface, "interface", "SmartKeyboard{  'Number of Keyboards':'5',  'Max Keyboard Polyphony':'0',  'Rounding Mode':'2',  'Send Fingers Count':'1',  'Keyboard 0 - Number of Keys':'19',  'Keyboard 1 - Number of Keys':'19',  'Keyboard 2 - Number of Keys':'19',  'Keyboard 3 - Number of Keys':'19',  'Keyboard 4 - Number of Keys':'1',  'Keyboard 0 - Lowest Key':'55',  'Keyboard 1 - Lowest Key':'62',  'Keyboard 2 - Lowest Key':'69',  'Keyboard 3 - Lowest Key':'76',  'Keyboard 0 - Send Keyboard Freq':'1',  'Keyboard 1 - Send Keyboard Freq':'1',  'Keyboard 2 - Send Keyboard Freq':'1',  'Keyboard 3 - Send Keyboard Freq':'1',  'Keyboard 4 - Send Freq':'0',  'Keyboard 4 - Send Key X':'1',  'Keyboard 4 - Send Key Y':'1',  'Keyboard 4 - Key 0 - Label':'Bow',  'Keyboard 4 - Static Mode':'1' }");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "violin");
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
	dsp->fHslider4 = (FAUSTFLOAT)0.0f;
	dsp->fHslider5 = (FAUSTFLOAT)330.0f;
	dsp->fHslider6 = (FAUSTFLOAT)1.0f;
	dsp->fHslider7 = (FAUSTFLOAT)0.0f;
	dsp->fHslider8 = (FAUSTFLOAT)440.0f;
	dsp->fHslider9 = (FAUSTFLOAT)1.0f;
	dsp->fHslider10 = (FAUSTFLOAT)0.0f;
	dsp->fHslider11 = (FAUSTFLOAT)550.0f;
	dsp->fHslider12 = (FAUSTFLOAT)1.0f;
	dsp->fHslider13 = (FAUSTFLOAT)0.0f;
	
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
		for (l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			dsp->fRec32[l8] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 2048); l9 = (l9 + 1)) {
			dsp->fVec1[l9] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 2048); l10 = (l10 + 1)) {
			dsp->fRec18[l10] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			dsp->fRec20[l11] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 4); l12 = (l12 + 1)) {
			dsp->fRec16[l12] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l13;
		for (l13 = 0; (l13 < 3); l13 = (l13 + 1)) {
			dsp->fRec14[l13] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l14;
		for (l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			dsp->iRec6[l14] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l15;
		for (l15 = 0; (l15 < 2048); l15 = (l15 + 1)) {
			dsp->fRec2[l15] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l16;
		for (l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			dsp->fRec0[l16] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l17;
		for (l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			dsp->iRec43[l17] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l18;
		for (l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			dsp->fRec59[l18] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l19;
		for (l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			dsp->fRec55[l19] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l20;
		for (l20 = 0; (l20 < 4); l20 = (l20 + 1)) {
			dsp->fRec60[l20] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l21;
		for (l21 = 0; (l21 < 2048); l21 = (l21 + 1)) {
			dsp->fRec61[l21] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l22;
		for (l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			dsp->fVec2[l22] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l23;
		for (l23 = 0; (l23 < 2048); l23 = (l23 + 1)) {
			dsp->fVec3[l23] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l24;
		for (l24 = 0; (l24 < 2048); l24 = (l24 + 1)) {
			dsp->fRec51[l24] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l25;
		for (l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			dsp->fRec53[l25] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l26;
		for (l26 = 0; (l26 < 4); l26 = (l26 + 1)) {
			dsp->fRec49[l26] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l27;
		for (l27 = 0; (l27 < 3); l27 = (l27 + 1)) {
			dsp->fRec47[l27] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l28;
		for (l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			dsp->iRec39[l28] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l29;
		for (l29 = 0; (l29 < 2048); l29 = (l29 + 1)) {
			dsp->fRec35[l29] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l30;
		for (l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			dsp->fRec33[l30] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l31;
		for (l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			dsp->iRec73[l31] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l32;
		for (l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			dsp->fRec89[l32] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l33;
		for (l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			dsp->fRec85[l33] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l34;
		for (l34 = 0; (l34 < 4); l34 = (l34 + 1)) {
			dsp->fRec90[l34] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l35;
		for (l35 = 0; (l35 < 2048); l35 = (l35 + 1)) {
			dsp->fRec91[l35] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l36;
		for (l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			dsp->fVec4[l36] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l37;
		for (l37 = 0; (l37 < 2048); l37 = (l37 + 1)) {
			dsp->fVec5[l37] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l38;
		for (l38 = 0; (l38 < 2048); l38 = (l38 + 1)) {
			dsp->fRec81[l38] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l39;
		for (l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			dsp->fRec83[l39] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l40;
		for (l40 = 0; (l40 < 4); l40 = (l40 + 1)) {
			dsp->fRec79[l40] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l41;
		for (l41 = 0; (l41 < 3); l41 = (l41 + 1)) {
			dsp->fRec77[l41] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l42;
		for (l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			dsp->iRec69[l42] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l43;
		for (l43 = 0; (l43 < 2048); l43 = (l43 + 1)) {
			dsp->fRec65[l43] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l44;
		for (l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			dsp->fRec63[l44] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l45;
		for (l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			dsp->iRec103[l45] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l46;
		for (l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			dsp->fRec119[l46] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l47;
		for (l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			dsp->fRec115[l47] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l48;
		for (l48 = 0; (l48 < 4); l48 = (l48 + 1)) {
			dsp->fRec120[l48] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l49;
		for (l49 = 0; (l49 < 2048); l49 = (l49 + 1)) {
			dsp->fRec121[l49] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l50;
		for (l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			dsp->fVec6[l50] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l51;
		for (l51 = 0; (l51 < 2048); l51 = (l51 + 1)) {
			dsp->fVec7[l51] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l52;
		for (l52 = 0; (l52 < 2048); l52 = (l52 + 1)) {
			dsp->fRec111[l52] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l53;
		for (l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			dsp->fRec113[l53] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l54;
		for (l54 = 0; (l54 < 4); l54 = (l54 + 1)) {
			dsp->fRec109[l54] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l55;
		for (l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			dsp->fRec107[l55] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l56;
		for (l56 = 0; (l56 < 2); l56 = (l56 + 1)) {
			dsp->iRec99[l56] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l57;
		for (l57 = 0; (l57 < 2048); l57 = (l57 + 1)) {
			dsp->fRec95[l57] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l58;
		for (l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			dsp->fRec93[l58] = 0.0f;
			
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "violin");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb0bend", &dsp->fHslider1, 1.0f, 0.0f, 10.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb0fingers", &dsp->fHslider2, 0.0f, 0.0f, 10.0f, 1.0f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb0freq", &dsp->fHslider0, 220.0f, 20.0f, 10000.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb1bend", &dsp->fHslider6, 1.0f, 0.0f, 10.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb1fingers", &dsp->fHslider7, 0.0f, 0.0f, 10.0f, 1.0f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb1freq", &dsp->fHslider5, 330.0f, 20.0f, 10000.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb2bend", &dsp->fHslider9, 1.0f, 0.0f, 10.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb2fingers", &dsp->fHslider10, 0.0f, 0.0f, 10.0f, 1.0f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb2freq", &dsp->fHslider8, 440.0f, 20.0f, 10000.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb3bend", &dsp->fHslider12, 1.0f, 0.0f, 10.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb3fingers", &dsp->fHslider13, 0.0f, 0.0f, 10.0f, 1.0f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb3freq", &dsp->fHslider11, 550.0f, 20.0f, 10000.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb4k0x", &dsp->fHslider3, 0.0f, 0.0f, 1.0f, 1.0f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb4k0y", &dsp->fHslider4, 0.0f, 0.0f, 1.0f, 1.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	float fSlow0 = (0.340000004f / ((float)dsp->fHslider0 * (float)dsp->fHslider1));
	int iSlow1 = ((int)(float)dsp->fHslider2 > 0);
	float fSlow2 = (0.00100000005f * (float)dsp->fHslider3);
	float fSlow3 = (0.00100000005f * (float)dsp->fHslider4);
	float fSlow4 = (0.340000004f / ((float)dsp->fHslider5 * (float)dsp->fHslider6));
	int iSlow5 = ((int)(float)dsp->fHslider7 > 0);
	float fSlow6 = (0.340000004f / ((float)dsp->fHslider8 * (float)dsp->fHslider9));
	int iSlow7 = ((int)(float)dsp->fHslider10 > 0);
	float fSlow8 = (0.340000004f / ((float)dsp->fHslider11 * (float)dsp->fHslider12));
	int iSlow9 = ((int)(float)dsp->fHslider13 > 0);
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
			dsp->fRec27[0] = ((0.999000013f * dsp->fRec27[1]) + (0.00100000005f * min(1.0f, (8000.0f * fabsf((dsp->fRec28[0] - dsp->fRec28[1]))))));
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
			dsp->fRec32[0] = (fSlow3 + (0.999000013f * dsp->fRec32[1]));
			float fTemp54 = (5.0f - (4.0f * dsp->fRec32[0]));
			float fTemp55 = (fTemp53 * min(1.0f, (1.0f / mydsp_faustpower4_f((fabsf((fTemp54 * fTemp53)) + 0.75f)))));
			float fRec23 = (dsp->fRec22[1] + fTemp55);
			float fTemp56 = (dsp->fVec0[1] + fTemp55);
			dsp->fVec1[(dsp->IOTA & 2047)] = fTemp56;
			float fRec24 = (((((fTemp7 * fTemp9) * fTemp11) * fTemp13) * dsp->fVec1[((dsp->IOTA - iTemp4) & 2047)]) + (fTemp14 * ((0.0416666679f * (fTemp25 * dsp->fVec1[((dsp->IOTA - iTemp26) & 2047)])) + (((((fTemp19 * fTemp20) * fTemp21) * dsp->fVec1[((dsp->IOTA - iTemp18) & 2047)]) + (0.5f * (((fTemp6 * fTemp16) * fTemp17) * dsp->fVec1[((dsp->IOTA - iTemp15) & 2047)]))) + (0.166666672f * ((fTemp22 * fTemp24) * dsp->fVec1[((dsp->IOTA - iTemp23) & 2047)]))))));
			int iRec25 = iRec31;
			dsp->fRec18[(dsp->IOTA & 2047)] = fRec23;
			float fRec19 = (((((fTemp33 * fTemp35) * fTemp37) * fTemp39) * dsp->fRec18[((dsp->IOTA - (iTemp30 + 1)) & 2047)]) + (fTemp40 * (((0.166666672f * ((fTemp48 * fTemp50) * dsp->fRec18[((dsp->IOTA - (iTemp49 + 1)) & 2047)])) + ((((fTemp45 * fTemp46) * fTemp47) * dsp->fRec18[((dsp->IOTA - (iTemp44 + 1)) & 2047)]) + (0.5f * (((fTemp32 * fTemp42) * fTemp43) * dsp->fRec18[((dsp->IOTA - (iTemp41 + 1)) & 2047)])))) + (0.0416666679f * (fTemp51 * dsp->fRec18[((dsp->IOTA - (iTemp52 + 1)) & 2047)])))));
			dsp->fRec20[0] = fRec24;
			int iRec21 = iRec25;
			dsp->fRec16[0] = dsp->fRec20[1];
			int iRec17 = iRec21;
			dsp->fRec14[0] = (dsp->fRec16[1] - (dsp->fConst3 * ((dsp->fConst7 * dsp->fRec14[2]) + (dsp->fConst8 * dsp->fRec14[1]))));
			float fTemp57 = (dsp->fConst3 * ((dsp->fConst2 * dsp->fRec14[0]) + (dsp->fConst9 * dsp->fRec14[2])));
			float fRec12 = fTemp57;
			float fRec13 = ((float)iRec17 + fTemp57);
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
			dsp->iRec43[0] = 0;
			int iRec44 = dsp->iRec43[1];
			float fRec48 = ((float)dsp->iRec39[1] - (0.989264667f * ((0.600000024f * dsp->fRec49[2]) + (0.200000003f * (dsp->fRec49[1] + dsp->fRec49[3])))));
			dsp->fRec59[0] = (fSlow4 + (0.999000013f * dsp->fRec59[1]));
			float fTemp58 = (dsp->fRec59[0] + -0.0799999982f);
			float fTemp59 = (dsp->fConst5 * fTemp58);
			float fTemp60 = (fTemp59 + -1.49999499f);
			int iTemp61 = (int)fTemp60;
			int iTemp62 = (int)min(dsp->fConst4, (float)max(0, iTemp61));
			float fTemp63 = floorf(fTemp60);
			float fTemp64 = (fTemp59 + (-1.0f - fTemp63));
			float fTemp65 = (0.0f - fTemp64);
			float fTemp66 = (fTemp59 + (-2.0f - fTemp63));
			float fTemp67 = (0.0f - (0.5f * fTemp66));
			float fTemp68 = (fTemp59 + (-3.0f - fTemp63));
			float fTemp69 = (0.0f - (0.333333343f * fTemp68));
			float fTemp70 = (fTemp59 + (-4.0f - fTemp63));
			float fTemp71 = (0.0f - (0.25f * fTemp70));
			float fTemp72 = (fTemp59 - fTemp63);
			int iTemp73 = (int)min(dsp->fConst4, (float)max(0, (iTemp61 + 2)));
			float fTemp74 = (0.0f - fTemp68);
			float fTemp75 = (0.0f - (0.5f * fTemp70));
			int iTemp76 = (int)min(dsp->fConst4, (float)max(0, (iTemp61 + 1)));
			float fTemp77 = (0.0f - fTemp66);
			float fTemp78 = (0.0f - (0.5f * fTemp68));
			float fTemp79 = (0.0f - (0.333333343f * fTemp70));
			float fTemp80 = (fTemp64 * fTemp66);
			int iTemp81 = (int)min(dsp->fConst4, (float)max(0, (iTemp61 + 3)));
			float fTemp82 = (0.0f - fTemp70);
			float fTemp83 = (fTemp80 * fTemp68);
			int iTemp84 = (int)min(dsp->fConst4, (float)max(0, (iTemp61 + 4)));
			dsp->fRec55[0] = (((((dsp->fRec35[((dsp->IOTA - (iTemp62 + 1)) & 2047)] * fTemp65) * fTemp67) * fTemp69) * fTemp71) + (fTemp72 * ((((0.5f * (((fTemp64 * dsp->fRec35[((dsp->IOTA - (iTemp73 + 1)) & 2047)]) * fTemp74) * fTemp75)) + (((dsp->fRec35[((dsp->IOTA - (iTemp76 + 1)) & 2047)] * fTemp77) * fTemp78) * fTemp79)) + (0.166666672f * ((fTemp80 * dsp->fRec35[((dsp->IOTA - (iTemp81 + 1)) & 2047)]) * fTemp82))) + (0.0416666679f * (fTemp83 * dsp->fRec35[((dsp->IOTA - (iTemp84 + 1)) & 2047)])))));
			dsp->fRec60[0] = dsp->fRec33[1];
			dsp->fRec61[(dsp->IOTA & 2047)] = (0.0f - (0.99880147f * ((0.800000012f * dsp->fRec60[2]) + (0.100000001f * (dsp->fRec60[1] + dsp->fRec60[3])))));
			int iRec62 = 0;
			float fTemp85 = (dsp->fConst6 * fTemp58);
			float fTemp86 = (fTemp85 + -1.49999499f);
			int iTemp87 = (int)fTemp86;
			int iTemp88 = (int)min(dsp->fConst4, (float)max(0, iTemp87));
			float fTemp89 = floorf(fTemp86);
			float fTemp90 = (fTemp85 + (-1.0f - fTemp89));
			float fTemp91 = (0.0f - fTemp90);
			float fTemp92 = (fTemp85 + (-2.0f - fTemp89));
			float fTemp93 = (0.0f - (0.5f * fTemp92));
			float fTemp94 = (fTemp85 + (-3.0f - fTemp89));
			float fTemp95 = (0.0f - (0.333333343f * fTemp94));
			float fTemp96 = (fTemp85 + (-4.0f - fTemp89));
			float fTemp97 = (0.0f - (0.25f * fTemp96));
			float fTemp98 = (fTemp85 - fTemp89);
			int iTemp99 = (int)min(dsp->fConst4, (float)max(0, (iTemp87 + 2)));
			float fTemp100 = (0.0f - fTemp94);
			float fTemp101 = (0.0f - (0.5f * fTemp96));
			int iTemp102 = (int)min(dsp->fConst4, (float)max(0, (iTemp87 + 1)));
			float fTemp103 = (0.0f - fTemp92);
			float fTemp104 = (0.0f - (0.5f * fTemp94));
			float fTemp105 = (0.0f - (0.333333343f * fTemp96));
			float fTemp106 = (fTemp90 * fTemp92);
			int iTemp107 = (int)min(dsp->fConst4, (float)max(0, (iTemp87 + 3)));
			float fTemp108 = (0.0f - fTemp96);
			float fTemp109 = (fTemp106 * fTemp94);
			int iTemp110 = (int)min(dsp->fConst4, (float)max(0, (iTemp87 + 4)));
			dsp->fVec2[0] = (((((dsp->fRec61[((dsp->IOTA - (iTemp88 + 2)) & 2047)] * fTemp91) * fTemp93) * fTemp95) * fTemp97) + (fTemp98 * ((((0.5f * (((fTemp90 * dsp->fRec61[((dsp->IOTA - (iTemp99 + 2)) & 2047)]) * fTemp100) * fTemp101)) + (((dsp->fRec61[((dsp->IOTA - (iTemp102 + 2)) & 2047)] * fTemp103) * fTemp104) * fTemp105)) + (0.166666672f * ((fTemp106 * dsp->fRec61[((dsp->IOTA - (iTemp107 + 2)) & 2047)]) * fTemp108))) + (0.0416666679f * (fTemp109 * dsp->fRec61[((dsp->IOTA - (iTemp110 + 2)) & 2047)])))));
			float fTemp111 = (((float)iSlow5 * dsp->fRec27[0]) - (dsp->fRec55[1] + dsp->fVec2[1]));
			float fTemp112 = (fTemp111 * min(1.0f, (1.0f / mydsp_faustpower4_f((fabsf((fTemp54 * fTemp111)) + 0.75f)))));
			float fRec56 = (dsp->fRec55[1] + fTemp112);
			float fTemp113 = (dsp->fVec2[1] + fTemp112);
			dsp->fVec3[(dsp->IOTA & 2047)] = fTemp113;
			float fRec57 = (((((fTemp65 * fTemp67) * fTemp69) * fTemp71) * dsp->fVec3[((dsp->IOTA - iTemp62) & 2047)]) + (fTemp72 * ((0.0416666679f * (fTemp83 * dsp->fVec3[((dsp->IOTA - iTemp84) & 2047)])) + (((((fTemp77 * fTemp78) * fTemp79) * dsp->fVec3[((dsp->IOTA - iTemp76) & 2047)]) + (0.5f * (((fTemp64 * fTemp74) * fTemp75) * dsp->fVec3[((dsp->IOTA - iTemp73) & 2047)]))) + (0.166666672f * ((fTemp80 * fTemp82) * dsp->fVec3[((dsp->IOTA - iTemp81) & 2047)]))))));
			int iRec58 = iRec62;
			dsp->fRec51[(dsp->IOTA & 2047)] = fRec56;
			float fRec52 = (((((fTemp91 * fTemp93) * fTemp95) * fTemp97) * dsp->fRec51[((dsp->IOTA - (iTemp88 + 1)) & 2047)]) + (fTemp98 * (((0.166666672f * ((fTemp106 * fTemp108) * dsp->fRec51[((dsp->IOTA - (iTemp107 + 1)) & 2047)])) + ((((fTemp103 * fTemp104) * fTemp105) * dsp->fRec51[((dsp->IOTA - (iTemp102 + 1)) & 2047)]) + (0.5f * (((fTemp90 * fTemp100) * fTemp101) * dsp->fRec51[((dsp->IOTA - (iTemp99 + 1)) & 2047)])))) + (0.0416666679f * (fTemp109 * dsp->fRec51[((dsp->IOTA - (iTemp110 + 1)) & 2047)])))));
			dsp->fRec53[0] = fRec57;
			int iRec54 = iRec58;
			dsp->fRec49[0] = dsp->fRec53[1];
			int iRec50 = iRec54;
			dsp->fRec47[0] = (dsp->fRec49[1] - (dsp->fConst3 * ((dsp->fConst8 * dsp->fRec47[1]) + (dsp->fConst7 * dsp->fRec47[2]))));
			float fTemp114 = (dsp->fConst3 * ((dsp->fConst2 * dsp->fRec47[0]) + (dsp->fConst9 * dsp->fRec47[2])));
			float fRec45 = fTemp114;
			float fRec46 = ((float)iRec50 + fTemp114);
			dsp->iRec39[0] = iRec44;
			float fRec40 = fRec48;
			float fRec41 = fRec45;
			float fRec42 = fRec46;
			dsp->fRec35[(dsp->IOTA & 2047)] = fRec40;
			float fRec36 = fRec52;
			float fRec37 = fRec41;
			float fRec38 = fRec42;
			dsp->fRec33[0] = fRec36;
			float fRec34 = fRec38;
			dsp->iRec73[0] = 0;
			int iRec74 = dsp->iRec73[1];
			float fRec78 = ((float)dsp->iRec69[1] - (0.989264667f * ((0.600000024f * dsp->fRec79[2]) + (0.200000003f * (dsp->fRec79[1] + dsp->fRec79[3])))));
			dsp->fRec89[0] = (fSlow6 + (0.999000013f * dsp->fRec89[1]));
			float fTemp115 = (dsp->fRec89[0] + -0.0799999982f);
			float fTemp116 = (dsp->fConst5 * fTemp115);
			float fTemp117 = (fTemp116 + -1.49999499f);
			int iTemp118 = (int)fTemp117;
			int iTemp119 = (int)min(dsp->fConst4, (float)max(0, iTemp118));
			float fTemp120 = floorf(fTemp117);
			float fTemp121 = (fTemp116 + (-1.0f - fTemp120));
			float fTemp122 = (0.0f - fTemp121);
			float fTemp123 = (fTemp116 + (-2.0f - fTemp120));
			float fTemp124 = (0.0f - (0.5f * fTemp123));
			float fTemp125 = (fTemp116 + (-3.0f - fTemp120));
			float fTemp126 = (0.0f - (0.333333343f * fTemp125));
			float fTemp127 = (fTemp116 + (-4.0f - fTemp120));
			float fTemp128 = (0.0f - (0.25f * fTemp127));
			float fTemp129 = (fTemp116 - fTemp120);
			int iTemp130 = (int)min(dsp->fConst4, (float)max(0, (iTemp118 + 2)));
			float fTemp131 = (0.0f - fTemp125);
			float fTemp132 = (0.0f - (0.5f * fTemp127));
			int iTemp133 = (int)min(dsp->fConst4, (float)max(0, (iTemp118 + 1)));
			float fTemp134 = (0.0f - fTemp123);
			float fTemp135 = (0.0f - (0.5f * fTemp125));
			float fTemp136 = (0.0f - (0.333333343f * fTemp127));
			float fTemp137 = (fTemp121 * fTemp123);
			int iTemp138 = (int)min(dsp->fConst4, (float)max(0, (iTemp118 + 3)));
			float fTemp139 = (0.0f - fTemp127);
			float fTemp140 = (fTemp137 * fTemp125);
			int iTemp141 = (int)min(dsp->fConst4, (float)max(0, (iTemp118 + 4)));
			dsp->fRec85[0] = (((((dsp->fRec65[((dsp->IOTA - (iTemp119 + 1)) & 2047)] * fTemp122) * fTemp124) * fTemp126) * fTemp128) + (fTemp129 * ((((0.5f * (((fTemp121 * dsp->fRec65[((dsp->IOTA - (iTemp130 + 1)) & 2047)]) * fTemp131) * fTemp132)) + (((dsp->fRec65[((dsp->IOTA - (iTemp133 + 1)) & 2047)] * fTemp134) * fTemp135) * fTemp136)) + (0.166666672f * ((fTemp137 * dsp->fRec65[((dsp->IOTA - (iTemp138 + 1)) & 2047)]) * fTemp139))) + (0.0416666679f * (fTemp140 * dsp->fRec65[((dsp->IOTA - (iTemp141 + 1)) & 2047)])))));
			dsp->fRec90[0] = dsp->fRec63[1];
			dsp->fRec91[(dsp->IOTA & 2047)] = (0.0f - (0.99880147f * ((0.800000012f * dsp->fRec90[2]) + (0.100000001f * (dsp->fRec90[1] + dsp->fRec90[3])))));
			int iRec92 = 0;
			float fTemp142 = (dsp->fConst6 * fTemp115);
			float fTemp143 = (fTemp142 + -1.49999499f);
			int iTemp144 = (int)fTemp143;
			int iTemp145 = (int)min(dsp->fConst4, (float)max(0, iTemp144));
			float fTemp146 = floorf(fTemp143);
			float fTemp147 = (fTemp142 + (-1.0f - fTemp146));
			float fTemp148 = (0.0f - fTemp147);
			float fTemp149 = (fTemp142 + (-2.0f - fTemp146));
			float fTemp150 = (0.0f - (0.5f * fTemp149));
			float fTemp151 = (fTemp142 + (-3.0f - fTemp146));
			float fTemp152 = (0.0f - (0.333333343f * fTemp151));
			float fTemp153 = (fTemp142 + (-4.0f - fTemp146));
			float fTemp154 = (0.0f - (0.25f * fTemp153));
			float fTemp155 = (fTemp142 - fTemp146);
			int iTemp156 = (int)min(dsp->fConst4, (float)max(0, (iTemp144 + 2)));
			float fTemp157 = (0.0f - fTemp151);
			float fTemp158 = (0.0f - (0.5f * fTemp153));
			int iTemp159 = (int)min(dsp->fConst4, (float)max(0, (iTemp144 + 1)));
			float fTemp160 = (0.0f - fTemp149);
			float fTemp161 = (0.0f - (0.5f * fTemp151));
			float fTemp162 = (0.0f - (0.333333343f * fTemp153));
			float fTemp163 = (fTemp147 * fTemp149);
			int iTemp164 = (int)min(dsp->fConst4, (float)max(0, (iTemp144 + 3)));
			float fTemp165 = (0.0f - fTemp153);
			float fTemp166 = (fTemp163 * fTemp151);
			int iTemp167 = (int)min(dsp->fConst4, (float)max(0, (iTemp144 + 4)));
			dsp->fVec4[0] = (((((dsp->fRec91[((dsp->IOTA - (iTemp145 + 2)) & 2047)] * fTemp148) * fTemp150) * fTemp152) * fTemp154) + (fTemp155 * ((((0.5f * (((fTemp147 * dsp->fRec91[((dsp->IOTA - (iTemp156 + 2)) & 2047)]) * fTemp157) * fTemp158)) + (((dsp->fRec91[((dsp->IOTA - (iTemp159 + 2)) & 2047)] * fTemp160) * fTemp161) * fTemp162)) + (0.166666672f * ((fTemp163 * dsp->fRec91[((dsp->IOTA - (iTemp164 + 2)) & 2047)]) * fTemp165))) + (0.0416666679f * (fTemp166 * dsp->fRec91[((dsp->IOTA - (iTemp167 + 2)) & 2047)])))));
			float fTemp168 = (((float)iSlow7 * dsp->fRec27[0]) - (dsp->fRec85[1] + dsp->fVec4[1]));
			float fTemp169 = (fTemp168 * min(1.0f, (1.0f / mydsp_faustpower4_f((fabsf((fTemp54 * fTemp168)) + 0.75f)))));
			float fRec86 = (dsp->fRec85[1] + fTemp169);
			float fTemp170 = (dsp->fVec4[1] + fTemp169);
			dsp->fVec5[(dsp->IOTA & 2047)] = fTemp170;
			float fRec87 = (((((fTemp122 * fTemp124) * fTemp126) * fTemp128) * dsp->fVec5[((dsp->IOTA - iTemp119) & 2047)]) + (fTemp129 * ((0.0416666679f * (fTemp140 * dsp->fVec5[((dsp->IOTA - iTemp141) & 2047)])) + (((((fTemp134 * fTemp135) * fTemp136) * dsp->fVec5[((dsp->IOTA - iTemp133) & 2047)]) + (0.5f * (((fTemp121 * fTemp131) * fTemp132) * dsp->fVec5[((dsp->IOTA - iTemp130) & 2047)]))) + (0.166666672f * ((fTemp137 * fTemp139) * dsp->fVec5[((dsp->IOTA - iTemp138) & 2047)]))))));
			int iRec88 = iRec92;
			dsp->fRec81[(dsp->IOTA & 2047)] = fRec86;
			float fRec82 = (((((fTemp148 * fTemp150) * fTemp152) * fTemp154) * dsp->fRec81[((dsp->IOTA - (iTemp145 + 1)) & 2047)]) + (fTemp155 * (((0.166666672f * ((fTemp163 * fTemp165) * dsp->fRec81[((dsp->IOTA - (iTemp164 + 1)) & 2047)])) + ((((fTemp160 * fTemp161) * fTemp162) * dsp->fRec81[((dsp->IOTA - (iTemp159 + 1)) & 2047)]) + (0.5f * (((fTemp147 * fTemp157) * fTemp158) * dsp->fRec81[((dsp->IOTA - (iTemp156 + 1)) & 2047)])))) + (0.0416666679f * (fTemp166 * dsp->fRec81[((dsp->IOTA - (iTemp167 + 1)) & 2047)])))));
			dsp->fRec83[0] = fRec87;
			int iRec84 = iRec88;
			dsp->fRec79[0] = dsp->fRec83[1];
			int iRec80 = iRec84;
			dsp->fRec77[0] = (dsp->fRec79[1] - (dsp->fConst3 * ((dsp->fConst8 * dsp->fRec77[1]) + (dsp->fConst7 * dsp->fRec77[2]))));
			float fTemp171 = (dsp->fConst3 * ((dsp->fConst2 * dsp->fRec77[0]) + (dsp->fConst9 * dsp->fRec77[2])));
			float fRec75 = fTemp171;
			float fRec76 = ((float)iRec80 + fTemp171);
			dsp->iRec69[0] = iRec74;
			float fRec70 = fRec78;
			float fRec71 = fRec75;
			float fRec72 = fRec76;
			dsp->fRec65[(dsp->IOTA & 2047)] = fRec70;
			float fRec66 = fRec82;
			float fRec67 = fRec71;
			float fRec68 = fRec72;
			dsp->fRec63[0] = fRec66;
			float fRec64 = fRec68;
			dsp->iRec103[0] = 0;
			int iRec104 = dsp->iRec103[1];
			float fRec108 = ((float)dsp->iRec99[1] - (0.989264667f * ((0.600000024f * dsp->fRec109[2]) + (0.200000003f * (dsp->fRec109[1] + dsp->fRec109[3])))));
			dsp->fRec119[0] = (fSlow8 + (0.999000013f * dsp->fRec119[1]));
			float fTemp172 = (dsp->fRec119[0] + -0.0799999982f);
			float fTemp173 = (dsp->fConst5 * fTemp172);
			float fTemp174 = (fTemp173 + -1.49999499f);
			int iTemp175 = (int)fTemp174;
			int iTemp176 = (int)min(dsp->fConst4, (float)max(0, iTemp175));
			float fTemp177 = floorf(fTemp174);
			float fTemp178 = (fTemp173 + (-1.0f - fTemp177));
			float fTemp179 = (0.0f - fTemp178);
			float fTemp180 = (fTemp173 + (-2.0f - fTemp177));
			float fTemp181 = (0.0f - (0.5f * fTemp180));
			float fTemp182 = (fTemp173 + (-3.0f - fTemp177));
			float fTemp183 = (0.0f - (0.333333343f * fTemp182));
			float fTemp184 = (fTemp173 + (-4.0f - fTemp177));
			float fTemp185 = (0.0f - (0.25f * fTemp184));
			float fTemp186 = (fTemp173 - fTemp177);
			int iTemp187 = (int)min(dsp->fConst4, (float)max(0, (iTemp175 + 2)));
			float fTemp188 = (0.0f - fTemp182);
			float fTemp189 = (0.0f - (0.5f * fTemp184));
			int iTemp190 = (int)min(dsp->fConst4, (float)max(0, (iTemp175 + 1)));
			float fTemp191 = (0.0f - fTemp180);
			float fTemp192 = (0.0f - (0.5f * fTemp182));
			float fTemp193 = (0.0f - (0.333333343f * fTemp184));
			float fTemp194 = (fTemp178 * fTemp180);
			int iTemp195 = (int)min(dsp->fConst4, (float)max(0, (iTemp175 + 3)));
			float fTemp196 = (0.0f - fTemp184);
			float fTemp197 = (fTemp194 * fTemp182);
			int iTemp198 = (int)min(dsp->fConst4, (float)max(0, (iTemp175 + 4)));
			dsp->fRec115[0] = (((((dsp->fRec95[((dsp->IOTA - (iTemp176 + 1)) & 2047)] * fTemp179) * fTemp181) * fTemp183) * fTemp185) + (fTemp186 * ((((0.5f * (((fTemp178 * dsp->fRec95[((dsp->IOTA - (iTemp187 + 1)) & 2047)]) * fTemp188) * fTemp189)) + (((dsp->fRec95[((dsp->IOTA - (iTemp190 + 1)) & 2047)] * fTemp191) * fTemp192) * fTemp193)) + (0.166666672f * ((fTemp194 * dsp->fRec95[((dsp->IOTA - (iTemp195 + 1)) & 2047)]) * fTemp196))) + (0.0416666679f * (fTemp197 * dsp->fRec95[((dsp->IOTA - (iTemp198 + 1)) & 2047)])))));
			dsp->fRec120[0] = dsp->fRec93[1];
			dsp->fRec121[(dsp->IOTA & 2047)] = (0.0f - (0.99880147f * ((0.800000012f * dsp->fRec120[2]) + (0.100000001f * (dsp->fRec120[1] + dsp->fRec120[3])))));
			int iRec122 = 0;
			float fTemp199 = (dsp->fConst6 * fTemp172);
			float fTemp200 = (fTemp199 + -1.49999499f);
			int iTemp201 = (int)fTemp200;
			int iTemp202 = (int)min(dsp->fConst4, (float)max(0, iTemp201));
			float fTemp203 = floorf(fTemp200);
			float fTemp204 = (fTemp199 + (-1.0f - fTemp203));
			float fTemp205 = (0.0f - fTemp204);
			float fTemp206 = (fTemp199 + (-2.0f - fTemp203));
			float fTemp207 = (0.0f - (0.5f * fTemp206));
			float fTemp208 = (fTemp199 + (-3.0f - fTemp203));
			float fTemp209 = (0.0f - (0.333333343f * fTemp208));
			float fTemp210 = (fTemp199 + (-4.0f - fTemp203));
			float fTemp211 = (0.0f - (0.25f * fTemp210));
			float fTemp212 = (fTemp199 - fTemp203);
			int iTemp213 = (int)min(dsp->fConst4, (float)max(0, (iTemp201 + 2)));
			float fTemp214 = (0.0f - fTemp208);
			float fTemp215 = (0.0f - (0.5f * fTemp210));
			int iTemp216 = (int)min(dsp->fConst4, (float)max(0, (iTemp201 + 1)));
			float fTemp217 = (0.0f - fTemp206);
			float fTemp218 = (0.0f - (0.5f * fTemp208));
			float fTemp219 = (0.0f - (0.333333343f * fTemp210));
			float fTemp220 = (fTemp204 * fTemp206);
			int iTemp221 = (int)min(dsp->fConst4, (float)max(0, (iTemp201 + 3)));
			float fTemp222 = (0.0f - fTemp210);
			float fTemp223 = (fTemp220 * fTemp208);
			int iTemp224 = (int)min(dsp->fConst4, (float)max(0, (iTemp201 + 4)));
			dsp->fVec6[0] = (((((dsp->fRec121[((dsp->IOTA - (iTemp202 + 2)) & 2047)] * fTemp205) * fTemp207) * fTemp209) * fTemp211) + (fTemp212 * ((((0.5f * (((fTemp204 * dsp->fRec121[((dsp->IOTA - (iTemp213 + 2)) & 2047)]) * fTemp214) * fTemp215)) + (((dsp->fRec121[((dsp->IOTA - (iTemp216 + 2)) & 2047)] * fTemp217) * fTemp218) * fTemp219)) + (0.166666672f * ((fTemp220 * dsp->fRec121[((dsp->IOTA - (iTemp221 + 2)) & 2047)]) * fTemp222))) + (0.0416666679f * (fTemp223 * dsp->fRec121[((dsp->IOTA - (iTemp224 + 2)) & 2047)])))));
			float fTemp225 = (((float)iSlow9 * dsp->fRec27[0]) - (dsp->fRec115[1] + dsp->fVec6[1]));
			float fTemp226 = (fTemp225 * min(1.0f, (1.0f / mydsp_faustpower4_f((fabsf((fTemp54 * fTemp225)) + 0.75f)))));
			float fRec116 = (dsp->fRec115[1] + fTemp226);
			float fTemp227 = (dsp->fVec6[1] + fTemp226);
			dsp->fVec7[(dsp->IOTA & 2047)] = fTemp227;
			float fRec117 = (((((fTemp179 * fTemp181) * fTemp183) * fTemp185) * dsp->fVec7[((dsp->IOTA - iTemp176) & 2047)]) + (fTemp186 * ((0.0416666679f * (fTemp197 * dsp->fVec7[((dsp->IOTA - iTemp198) & 2047)])) + (((((fTemp191 * fTemp192) * fTemp193) * dsp->fVec7[((dsp->IOTA - iTemp190) & 2047)]) + (0.5f * (((fTemp178 * fTemp188) * fTemp189) * dsp->fVec7[((dsp->IOTA - iTemp187) & 2047)]))) + (0.166666672f * ((fTemp194 * fTemp196) * dsp->fVec7[((dsp->IOTA - iTemp195) & 2047)]))))));
			int iRec118 = iRec122;
			dsp->fRec111[(dsp->IOTA & 2047)] = fRec116;
			float fRec112 = (((((fTemp205 * fTemp207) * fTemp209) * fTemp211) * dsp->fRec111[((dsp->IOTA - (iTemp202 + 1)) & 2047)]) + (fTemp212 * (((0.166666672f * ((fTemp220 * fTemp222) * dsp->fRec111[((dsp->IOTA - (iTemp221 + 1)) & 2047)])) + ((((fTemp217 * fTemp218) * fTemp219) * dsp->fRec111[((dsp->IOTA - (iTemp216 + 1)) & 2047)]) + (0.5f * (((fTemp204 * fTemp214) * fTemp215) * dsp->fRec111[((dsp->IOTA - (iTemp213 + 1)) & 2047)])))) + (0.0416666679f * (fTemp223 * dsp->fRec111[((dsp->IOTA - (iTemp224 + 1)) & 2047)])))));
			dsp->fRec113[0] = fRec117;
			int iRec114 = iRec118;
			dsp->fRec109[0] = dsp->fRec113[1];
			int iRec110 = iRec114;
			dsp->fRec107[0] = (dsp->fRec109[1] - (dsp->fConst3 * ((dsp->fConst8 * dsp->fRec107[1]) + (dsp->fConst7 * dsp->fRec107[2]))));
			float fTemp228 = (dsp->fConst3 * ((dsp->fConst2 * dsp->fRec107[0]) + (dsp->fConst9 * dsp->fRec107[2])));
			float fRec105 = fTemp228;
			float fRec106 = ((float)iRec110 + fTemp228);
			dsp->iRec99[0] = iRec104;
			float fRec100 = fRec108;
			float fRec101 = fRec105;
			float fRec102 = fRec106;
			dsp->fRec95[(dsp->IOTA & 2047)] = fRec100;
			float fRec96 = fRec112;
			float fRec97 = fRec101;
			float fRec98 = fRec102;
			dsp->fRec93[0] = fRec96;
			float fRec94 = fRec98;
			float fTemp229 = (((fRec1 + fRec34) + fRec64) + fRec94);
			output0[i] = (FAUSTFLOAT)fTemp229;
			output1[i] = (FAUSTFLOAT)fTemp229;
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
			dsp->fRec32[1] = dsp->fRec32[0];
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
			dsp->iRec43[1] = dsp->iRec43[0];
			dsp->fRec59[1] = dsp->fRec59[0];
			dsp->fRec55[1] = dsp->fRec55[0];
			/* C99 loop */
			{
				int j2;
				for (j2 = 3; (j2 > 0); j2 = (j2 - 1)) {
					dsp->fRec60[j2] = dsp->fRec60[(j2 - 1)];
					
				}
				
			}
			dsp->fVec2[1] = dsp->fVec2[0];
			dsp->fRec53[1] = dsp->fRec53[0];
			/* C99 loop */
			{
				int j3;
				for (j3 = 3; (j3 > 0); j3 = (j3 - 1)) {
					dsp->fRec49[j3] = dsp->fRec49[(j3 - 1)];
					
				}
				
			}
			dsp->fRec47[2] = dsp->fRec47[1];
			dsp->fRec47[1] = dsp->fRec47[0];
			dsp->iRec39[1] = dsp->iRec39[0];
			dsp->fRec33[1] = dsp->fRec33[0];
			dsp->iRec73[1] = dsp->iRec73[0];
			dsp->fRec89[1] = dsp->fRec89[0];
			dsp->fRec85[1] = dsp->fRec85[0];
			/* C99 loop */
			{
				int j4;
				for (j4 = 3; (j4 > 0); j4 = (j4 - 1)) {
					dsp->fRec90[j4] = dsp->fRec90[(j4 - 1)];
					
				}
				
			}
			dsp->fVec4[1] = dsp->fVec4[0];
			dsp->fRec83[1] = dsp->fRec83[0];
			/* C99 loop */
			{
				int j5;
				for (j5 = 3; (j5 > 0); j5 = (j5 - 1)) {
					dsp->fRec79[j5] = dsp->fRec79[(j5 - 1)];
					
				}
				
			}
			dsp->fRec77[2] = dsp->fRec77[1];
			dsp->fRec77[1] = dsp->fRec77[0];
			dsp->iRec69[1] = dsp->iRec69[0];
			dsp->fRec63[1] = dsp->fRec63[0];
			dsp->iRec103[1] = dsp->iRec103[0];
			dsp->fRec119[1] = dsp->fRec119[0];
			dsp->fRec115[1] = dsp->fRec115[0];
			/* C99 loop */
			{
				int j6;
				for (j6 = 3; (j6 > 0); j6 = (j6 - 1)) {
					dsp->fRec120[j6] = dsp->fRec120[(j6 - 1)];
					
				}
				
			}
			dsp->fVec6[1] = dsp->fVec6[0];
			dsp->fRec113[1] = dsp->fRec113[0];
			/* C99 loop */
			{
				int j7;
				for (j7 = 3; (j7 > 0); j7 = (j7 - 1)) {
					dsp->fRec109[j7] = dsp->fRec109[(j7 - 1)];
					
				}
				
			}
			dsp->fRec107[2] = dsp->fRec107[1];
			dsp->fRec107[1] = dsp->fRec107[0];
			dsp->iRec99[1] = dsp->iRec99[0];
			dsp->fRec93[1] = dsp->fRec93[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
