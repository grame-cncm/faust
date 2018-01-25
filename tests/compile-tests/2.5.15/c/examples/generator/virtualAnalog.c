/* ------------------------------------------------------------
author: "JOS, revised by RM"
name: "VirtualAnalog"
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
static float mydsp_faustpower3_f(float value) {
	return ((value * value) * value);
	
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif
#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

typedef struct {
	
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT fHslider0;
	int iVec0[4];
	float fRec0[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fEntry0;
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fVslider2;
	float fRec2[2];
	float fVec1[2];
	float fRec1[2];
	float fConst2;
	float fVec2[2];
	float fConst3;
	float fVec3[2];
	float fVec4[2];
	float fConst4;
	float fVec5[2];
	float fVec6[2];
	float fVec7[2];
	FAUSTFLOAT fVslider3;
	float fVec8[2];
	float fRec3[2];
	float fVec9[2];
	float fVec10[2];
	float fVec11[2];
	float fVec12[2];
	float fVec13[2];
	float fVec14[2];
	FAUSTFLOAT fVslider4;
	float fVec15[2];
	float fRec4[2];
	float fVec16[2];
	float fVec17[2];
	float fVec18[2];
	float fVec19[2];
	float fVec20[2];
	float fVec21[2];
	float fConst5;
	FAUSTFLOAT fVslider5;
	float fVec22[2];
	float fRec5[2];
	float fVec23[2];
	int IOTA;
	float fVec24[4096];
	float fConst6;
	float fVec25[2];
	float fRec6[2];
	float fVec26[2];
	float fVec27[4096];
	float fVec28[2];
	float fRec7[2];
	float fVec29[2];
	float fVec30[4096];
	float fConst7;
	FAUSTFLOAT fVslider6;
	float fRec8[2];
	float fRec9[2];
	float fRec10[2];
	FAUSTFLOAT fVslider7;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fVslider8;
	float fRec11[2];
	float fConst8;
	float fVec31[2];
	float fVec32[2];
	float fVec33[4096];
	float fVec34[2];
	float fVec35[2];
	float fVec36[4096];
	float fVec37[2];
	float fVec38[2];
	float fVec39[4096];
	FAUSTFLOAT fVslider9;
	int iRec13[2];
	float fRec12[4];
	
} mydsp;

mydsp* newmydsp() { 
	mydsp* dsp = (mydsp*)malloc(sizeof(mydsp));
	return dsp;
}

void deletemydsp(mydsp* dsp) { 
	free(dsp);
}

void metadatamydsp(MetaGlue* m) { 
	m->declare(m->metaInterface, "author", "JOS, revised by RM");
	m->declare(m->metaInterface, "basics.lib/name", "Faust Basic Element Library");
	m->declare(m->metaInterface, "basics.lib/version", "0.0");
	m->declare(m->metaInterface, "description", "Virtual analog oscillator demo application.");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "VirtualAnalog");
	m->declare(m->metaInterface, "noises.lib/name", "Faust Noise Generator Library");
	m->declare(m->metaInterface, "noises.lib/version", "0.0");
	m->declare(m->metaInterface, "oscillators.lib/name", "Faust Oscillator Library");
	m->declare(m->metaInterface, "oscillators.lib/version", "0.0");
	m->declare(m->metaInterface, "signals.lib/name", "Faust Signal Routing Library");
	m->declare(m->metaInterface, "signals.lib/version", "0.0");
	m->declare(m->metaInterface, "version", "0.0");
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
	dsp->fVslider0 = (FAUSTFLOAT)0.0f;
	dsp->fHslider0 = (FAUSTFLOAT)-20.0f;
	dsp->fVslider1 = (FAUSTFLOAT)1.0f;
	dsp->fEntry0 = (FAUSTFLOAT)2.0f;
	dsp->fHslider1 = (FAUSTFLOAT)49.0f;
	dsp->fVslider2 = (FAUSTFLOAT)0.10000000000000001f;
	dsp->fVslider3 = (FAUSTFLOAT)-0.10000000000000001f;
	dsp->fVslider4 = (FAUSTFLOAT)0.10000000000000001f;
	dsp->fVslider5 = (FAUSTFLOAT)0.0f;
	dsp->fVslider6 = (FAUSTFLOAT)0.0f;
	dsp->fVslider7 = (FAUSTFLOAT)0.0f;
	dsp->fCheckbox0 = (FAUSTFLOAT)0.0f;
	dsp->fVslider8 = (FAUSTFLOAT)0.5f;
	dsp->fVslider9 = (FAUSTFLOAT)0.0f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 4); l0 = (l0 + 1)) {
			dsp->iVec0[l0] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			dsp->fRec0[l1] = 0.0f;
			
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
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			dsp->fVec1[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			dsp->fRec1[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			dsp->fVec2[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			dsp->fVec3[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			dsp->fVec4[l7] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			dsp->fVec5[l8] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			dsp->fVec6[l9] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			dsp->fVec7[l10] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			dsp->fVec8[l11] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			dsp->fRec3[l12] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l13;
		for (l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			dsp->fVec9[l13] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l14;
		for (l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			dsp->fVec10[l14] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l15;
		for (l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			dsp->fVec11[l15] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l16;
		for (l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			dsp->fVec12[l16] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l17;
		for (l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			dsp->fVec13[l17] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l18;
		for (l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			dsp->fVec14[l18] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l19;
		for (l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			dsp->fVec15[l19] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l20;
		for (l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			dsp->fRec4[l20] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l21;
		for (l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			dsp->fVec16[l21] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l22;
		for (l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			dsp->fVec17[l22] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l23;
		for (l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			dsp->fVec18[l23] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l24;
		for (l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			dsp->fVec19[l24] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l25;
		for (l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			dsp->fVec20[l25] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l26;
		for (l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			dsp->fVec21[l26] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l27;
		for (l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			dsp->fVec22[l27] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l28;
		for (l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			dsp->fRec5[l28] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l29;
		for (l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			dsp->fVec23[l29] = 0.0f;
			
		}
		
	}
	dsp->IOTA = 0;
	/* C99 loop */
	{
		int l30;
		for (l30 = 0; (l30 < 4096); l30 = (l30 + 1)) {
			dsp->fVec24[l30] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l31;
		for (l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			dsp->fVec25[l31] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l32;
		for (l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			dsp->fRec6[l32] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l33;
		for (l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			dsp->fVec26[l33] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l34;
		for (l34 = 0; (l34 < 4096); l34 = (l34 + 1)) {
			dsp->fVec27[l34] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l35;
		for (l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			dsp->fVec28[l35] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l36;
		for (l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			dsp->fRec7[l36] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l37;
		for (l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			dsp->fVec29[l37] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l38;
		for (l38 = 0; (l38 < 4096); l38 = (l38 + 1)) {
			dsp->fVec30[l38] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l39;
		for (l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			dsp->fRec8[l39] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l40;
		for (l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			dsp->fRec9[l40] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l41;
		for (l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			dsp->fRec10[l41] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l42;
		for (l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			dsp->fRec11[l42] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l43;
		for (l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			dsp->fVec31[l43] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l44;
		for (l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			dsp->fVec32[l44] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l45;
		for (l45 = 0; (l45 < 4096); l45 = (l45 + 1)) {
			dsp->fVec33[l45] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l46;
		for (l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			dsp->fVec34[l46] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l47;
		for (l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			dsp->fVec35[l47] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l48;
		for (l48 = 0; (l48 < 4096); l48 = (l48 + 1)) {
			dsp->fVec36[l48] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l49;
		for (l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			dsp->fVec37[l49] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l50;
		for (l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			dsp->fVec38[l50] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l51;
		for (l51 = 0; (l51 < 4096); l51 = (l51 + 1)) {
			dsp->fVec39[l51] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l52;
		for (l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			dsp->iRec13[l52] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l53;
		for (l53 = 0; (l53 < 4); l53 = (l53 + 1)) {
			dsp->fRec12[l53] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = (1.0f / dsp->fConst0);
	dsp->fConst2 = (0.25f * dsp->fConst0);
	dsp->fConst3 = (0.0416666679f * mydsp_faustpower2_f(dsp->fConst0));
	dsp->fConst4 = (0.00520833349f * mydsp_faustpower3_f(dsp->fConst0));
	dsp->fConst5 = (0.0833333358f * dsp->fConst0);
	dsp->fConst6 = (0.5f * dsp->fConst0);
	dsp->fConst7 = (1.33333337f / dsp->fConst0);
	dsp->fConst8 = (0.013888889f * dsp->fConst0);
	
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
	ui_interface->declare(ui_interface->uiInterface, 0, "0", "");
	ui_interface->declare(ui_interface->uiInterface, 0, "tooltip", "See Faust's oscillators.lib for documentation and references");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "VIRTUAL ANALOG OSCILLATORS");
	ui_interface->declare(ui_interface->uiInterface, 0, "0", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "Signal Levels");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider1, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider1, "style", "vslider");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Sawtooth", &dsp->fVslider1, 1.0f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, 0, "1", "");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "Pulse Train");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox0, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox0, "tooltip", "When checked, use 3rd-order aliasing suppression (up from 2)  See if you can hear a difference with the freq high and swept");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Order 3", &dsp->fCheckbox0);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider7, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider7, "style", "vslider");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "0x00", &dsp->fVslider7, 0.0f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider8, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider8, "style", "knob");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Duty Cycle", &dsp->fVslider8, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider5, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider5, "style", "vslider");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Square", &dsp->fVslider5, 0.0f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider6, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider6, "style", "vslider");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Triangle", &dsp->fVslider6, 0.0f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider9, "4", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider9, "style", "vslider");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider9, "tooltip", "Pink Noise (or 1/f noise) is   Constant-Q Noise, meaning that it has the same total power in every octave   (uses only amplitude controls)");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Pink Noise", &dsp->fVslider9, 0.0f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider0, "5", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider0, "style", "vslider");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Ext Input", &dsp->fVslider0, 0.0f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "1", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "Signal Parameters");
	ui_interface->declare(ui_interface->uiInterface, 0, "0", "");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "style", "hslider");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "tooltip", "Sawtooth waveform amplitude");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "unit", "dB");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Mix Amplitude", &dsp->fHslider0, -20.0f, -120.0f, 10.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "style", "hslider");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "tooltip", "Sawtooth   frequency as a Piano Key (PK) number (A440 = key 49)");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "unit", "PK");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Frequency", &dsp->fHslider1, 49.0f, 1.0f, 88.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider3, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider3, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider3, "tooltip", "Percentange frequency-shift up or down for second oscillator");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider3, "unit", "%%");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Detuning 1", &dsp->fVslider3, -0.100000001f, -10.0f, 10.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider4, "4", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider4, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider4, "tooltip", "Percentange frequency-shift up or down for third detuned oscillator");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider4, "unit", "%%");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Detuning 2", &dsp->fVslider4, 0.100000001f, -10.0f, 10.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider2, "5", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider2, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider2, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider2, "tooltip", "Portamento (frequency-glide) time-constant in seconds");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider2, "unit", "sec");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Portamento", &dsp->fVslider2, 0.100000001f, 0.00100000005f, 10.0f, 0.00100000005f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry0, "6", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry0, "tooltip", "Order of sawtooth aliasing  suppression");
	ui_interface->addNumEntry(ui_interface->uiInterface, "Saw Order", &dsp->fEntry0, 2.0f, 1.0f, 4.0f, 1.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* input0 = inputs[0];
	FAUSTFLOAT* output0 = outputs[0];
	float fSlow0 = (float)dsp->fVslider0;
	float fSlow1 = (0.00100000005f * powf(10.0f, (0.0500000007f * (float)dsp->fHslider0)));
	float fSlow2 = (0.333333343f * (float)dsp->fVslider1);
	int iSlow3 = (int)((float)dsp->fEntry0 + -1.0f);
	int iSlow4 = (iSlow3 >= 2);
	int iSlow5 = (iSlow3 >= 1);
	float fSlow6 = expf((0.0f - (dsp->fConst1 / (float)dsp->fVslider2)));
	float fSlow7 = (440.0f * (powf(2.0f, (0.0833333358f * ((float)dsp->fHslider1 + -49.0f))) * (1.0f - fSlow6)));
	int iSlow8 = (iSlow3 >= 3);
	float fSlow9 = (1.0f - (0.00999999978f * (float)dsp->fVslider3));
	float fSlow10 = ((0.00999999978f * (float)dsp->fVslider4) + 1.0f);
	float fSlow11 = (dsp->fConst5 * (float)dsp->fVslider5);
	float fSlow12 = (dsp->fConst7 * (float)dsp->fVslider6);
	float fSlow13 = (dsp->fConst0 * (float)dsp->fVslider7);
	float fSlow14 = (float)dsp->fCheckbox0;
	float fSlow15 = (0.0833333358f * (1.0f - fSlow14));
	float fSlow16 = (0.00999999978f * (float)dsp->fVslider8);
	float fSlow17 = (dsp->fConst8 * fSlow14);
	float fSlow18 = (float)dsp->fVslider9;
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->iVec0[0] = 1;
			dsp->fRec0[0] = (fSlow1 + (0.999000013f * dsp->fRec0[1]));
			dsp->fRec2[0] = (fSlow7 + (fSlow6 * dsp->fRec2[1]));
			float fTemp0 = max(20.0f, fabsf(dsp->fRec2[0]));
			dsp->fVec1[0] = fTemp0;
			float fTemp1 = (dsp->fRec1[1] + (dsp->fConst1 * dsp->fVec1[1]));
			dsp->fRec1[0] = (fTemp1 - floorf(fTemp1));
			float fTemp2 = (2.0f * dsp->fRec1[0]);
			float fTemp3 = (fTemp2 + -1.0f);
			float fTemp4 = mydsp_faustpower2_f(fTemp3);
			dsp->fVec2[0] = fTemp4;
			float fTemp5 = mydsp_faustpower3_f(fTemp3);
			dsp->fVec3[0] = (fTemp5 + (1.0f - fTemp2));
			float fTemp6 = ((fTemp5 + (1.0f - (fTemp2 + dsp->fVec3[1]))) / fTemp0);
			dsp->fVec4[0] = fTemp6;
			float fTemp7 = (fTemp4 * (fTemp4 + -2.0f));
			dsp->fVec5[0] = fTemp7;
			float fTemp8 = ((fTemp7 - dsp->fVec5[1]) / fTemp0);
			dsp->fVec6[0] = fTemp8;
			float fTemp9 = ((fTemp8 - dsp->fVec6[1]) / fTemp0);
			dsp->fVec7[0] = fTemp9;
			float fTemp10 = (fSlow9 * dsp->fRec2[0]);
			float fTemp11 = max(20.0f, fabsf(fTemp10));
			dsp->fVec8[0] = fTemp11;
			float fTemp12 = (dsp->fRec3[1] + (dsp->fConst1 * dsp->fVec8[1]));
			dsp->fRec3[0] = (fTemp12 - floorf(fTemp12));
			float fTemp13 = (2.0f * dsp->fRec3[0]);
			float fTemp14 = (fTemp13 + -1.0f);
			float fTemp15 = mydsp_faustpower2_f(fTemp14);
			dsp->fVec9[0] = fTemp15;
			float fTemp16 = mydsp_faustpower3_f(fTemp14);
			dsp->fVec10[0] = (fTemp16 + (1.0f - fTemp13));
			float fTemp17 = ((fTemp16 + (1.0f - (fTemp13 + dsp->fVec10[1]))) / fTemp11);
			dsp->fVec11[0] = fTemp17;
			float fTemp18 = (fTemp15 * (fTemp15 + -2.0f));
			dsp->fVec12[0] = fTemp18;
			float fTemp19 = ((fTemp18 - dsp->fVec12[1]) / fTemp11);
			dsp->fVec13[0] = fTemp19;
			float fTemp20 = ((fTemp19 - dsp->fVec13[1]) / fTemp11);
			dsp->fVec14[0] = fTemp20;
			float fTemp21 = (fSlow10 * dsp->fRec2[0]);
			float fTemp22 = max(20.0f, fabsf(fTemp21));
			dsp->fVec15[0] = fTemp22;
			float fTemp23 = (dsp->fRec4[1] + (dsp->fConst1 * dsp->fVec15[1]));
			dsp->fRec4[0] = (fTemp23 - floorf(fTemp23));
			float fTemp24 = (2.0f * dsp->fRec4[0]);
			float fTemp25 = (fTemp24 + -1.0f);
			float fTemp26 = mydsp_faustpower2_f(fTemp25);
			dsp->fVec16[0] = fTemp26;
			float fTemp27 = mydsp_faustpower3_f(fTemp25);
			dsp->fVec17[0] = (fTemp27 + (1.0f - fTemp24));
			float fTemp28 = ((fTemp27 + (1.0f - (fTemp24 + dsp->fVec17[1]))) / fTemp22);
			dsp->fVec18[0] = fTemp28;
			float fTemp29 = (fTemp26 * (fTemp26 + -2.0f));
			dsp->fVec19[0] = fTemp29;
			float fTemp30 = ((fTemp29 - dsp->fVec19[1]) / fTemp22);
			dsp->fVec20[0] = fTemp30;
			float fTemp31 = ((fTemp30 - dsp->fVec20[1]) / fTemp22);
			dsp->fVec21[0] = fTemp31;
			float fTemp32 = max(dsp->fRec2[0], 23.4489498f);
			float fTemp33 = max(20.0f, fabsf(fTemp32));
			dsp->fVec22[0] = fTemp33;
			float fTemp34 = (dsp->fRec5[1] + (dsp->fConst1 * dsp->fVec22[1]));
			dsp->fRec5[0] = (fTemp34 - floorf(fTemp34));
			float fTemp35 = (2.0f * dsp->fRec5[0]);
			float fTemp36 = (fTemp35 + -1.0f);
			float fTemp37 = mydsp_faustpower2_f(fTemp36);
			dsp->fVec23[0] = fTemp37;
			float fTemp38 = (((float)dsp->iVec0[1] * (fTemp37 - dsp->fVec23[1])) / fTemp33);
			dsp->fVec24[(dsp->IOTA & 4095)] = fTemp38;
			float fTemp39 = max(0.0f, min(2047.0f, (dsp->fConst6 / fTemp32)));
			int iTemp40 = (int)fTemp39;
			float fTemp41 = floorf(fTemp39);
			float fTemp42 = ((fTemp38 - (dsp->fVec24[((dsp->IOTA - iTemp40) & 4095)] * (fTemp41 + (1.0f - fTemp39)))) - ((fTemp39 - fTemp41) * dsp->fVec24[((dsp->IOTA - (iTemp40 + 1)) & 4095)]));
			float fTemp43 = max(fTemp10, 23.4489498f);
			float fTemp44 = max(20.0f, fabsf(fTemp43));
			dsp->fVec25[0] = fTemp44;
			float fTemp45 = (dsp->fRec6[1] + (dsp->fConst1 * dsp->fVec25[1]));
			dsp->fRec6[0] = (fTemp45 - floorf(fTemp45));
			float fTemp46 = (2.0f * dsp->fRec6[0]);
			float fTemp47 = (fTemp46 + -1.0f);
			float fTemp48 = mydsp_faustpower2_f(fTemp47);
			dsp->fVec26[0] = fTemp48;
			float fTemp49 = (((float)dsp->iVec0[1] * (fTemp48 - dsp->fVec26[1])) / fTemp44);
			dsp->fVec27[(dsp->IOTA & 4095)] = fTemp49;
			float fTemp50 = max(0.0f, min(2047.0f, (dsp->fConst6 / fTemp43)));
			int iTemp51 = (int)fTemp50;
			float fTemp52 = floorf(fTemp50);
			float fTemp53 = ((fTemp49 - (dsp->fVec27[((dsp->IOTA - iTemp51) & 4095)] * (fTemp52 + (1.0f - fTemp50)))) - ((fTemp50 - fTemp52) * dsp->fVec27[((dsp->IOTA - (iTemp51 + 1)) & 4095)]));
			float fTemp54 = max(fTemp21, 23.4489498f);
			float fTemp55 = max(20.0f, fabsf(fTemp54));
			dsp->fVec28[0] = fTemp55;
			float fTemp56 = (dsp->fRec7[1] + (dsp->fConst1 * dsp->fVec28[1]));
			dsp->fRec7[0] = (fTemp56 - floorf(fTemp56));
			float fTemp57 = (2.0f * dsp->fRec7[0]);
			float fTemp58 = (fTemp57 + -1.0f);
			float fTemp59 = mydsp_faustpower2_f(fTemp58);
			dsp->fVec29[0] = fTemp59;
			float fTemp60 = (((float)dsp->iVec0[1] * (fTemp59 - dsp->fVec29[1])) / fTemp55);
			dsp->fVec30[(dsp->IOTA & 4095)] = fTemp60;
			float fTemp61 = max(0.0f, min(2047.0f, (dsp->fConst6 / fTemp54)));
			int iTemp62 = (int)fTemp61;
			float fTemp63 = floorf(fTemp61);
			float fTemp64 = ((fTemp60 - (dsp->fVec30[((dsp->IOTA - iTemp62) & 4095)] * (fTemp63 + (1.0f - fTemp61)))) - ((fTemp61 - fTemp63) * dsp->fVec30[((dsp->IOTA - (iTemp62 + 1)) & 4095)]));
			dsp->fRec8[0] = ((dsp->fConst2 * fTemp42) + (0.999000013f * dsp->fRec8[1]));
			dsp->fRec9[0] = ((dsp->fConst2 * fTemp53) + (0.999000013f * dsp->fRec9[1]));
			dsp->fRec10[0] = ((dsp->fConst2 * fTemp64) + (0.999000013f * dsp->fRec10[1]));
			dsp->fRec11[0] = (fSlow16 + (0.99000001f * dsp->fRec11[1]));
			float fTemp65 = max(0.0f, min(2047.0f, (dsp->fConst0 * (dsp->fRec11[0] / fTemp32))));
			float fTemp66 = floorf(fTemp65);
			float fTemp67 = (fTemp66 + (1.0f - fTemp65));
			int iTemp68 = (int)fTemp65;
			float fTemp69 = (fTemp65 - fTemp66);
			int iTemp70 = (iTemp68 + 1);
			float fTemp71 = max(0.0f, min(2047.0f, (dsp->fConst0 * (dsp->fRec11[0] / fTemp43))));
			float fTemp72 = floorf(fTemp71);
			float fTemp73 = (fTemp72 + (1.0f - fTemp71));
			int iTemp74 = (int)fTemp71;
			float fTemp75 = (fTemp71 - fTemp72);
			int iTemp76 = (iTemp74 + 1);
			float fTemp77 = max(0.0f, min(2047.0f, (dsp->fConst0 * (dsp->fRec11[0] / fTemp54))));
			float fTemp78 = floorf(fTemp77);
			float fTemp79 = (fTemp78 + (1.0f - fTemp77));
			int iTemp80 = (int)fTemp77;
			float fTemp81 = (fTemp77 - fTemp78);
			int iTemp82 = (iTemp80 + 1);
			float fTemp83 = mydsp_faustpower3_f(fTemp36);
			dsp->fVec31[0] = (fTemp83 + (1.0f - fTemp35));
			float fTemp84 = ((fTemp83 + (1.0f - (fTemp35 + dsp->fVec31[1]))) / fTemp33);
			dsp->fVec32[0] = fTemp84;
			float fTemp85 = (((float)dsp->iVec0[2] * (fTemp84 - dsp->fVec32[1])) / fTemp33);
			dsp->fVec33[(dsp->IOTA & 4095)] = fTemp85;
			float fTemp86 = mydsp_faustpower3_f(fTemp47);
			dsp->fVec34[0] = (fTemp86 + (1.0f - fTemp46));
			float fTemp87 = ((fTemp86 + (1.0f - (fTemp46 + dsp->fVec34[1]))) / fTemp44);
			dsp->fVec35[0] = fTemp87;
			float fTemp88 = (((float)dsp->iVec0[2] * (fTemp87 - dsp->fVec35[1])) / fTemp44);
			dsp->fVec36[(dsp->IOTA & 4095)] = fTemp88;
			float fTemp89 = mydsp_faustpower3_f(fTemp58);
			dsp->fVec37[0] = (fTemp89 + (1.0f - fTemp57));
			float fTemp90 = ((fTemp89 + (1.0f - (fTemp57 + dsp->fVec37[1]))) / fTemp55);
			dsp->fVec38[0] = fTemp90;
			float fTemp91 = (((float)dsp->iVec0[2] * (fTemp90 - dsp->fVec38[1])) / fTemp55);
			dsp->fVec39[(dsp->IOTA & 4095)] = fTemp91;
			dsp->iRec13[0] = ((1103515245 * dsp->iRec13[1]) + 12345);
			dsp->fRec12[0] = (((0.522189379f * dsp->fRec12[3]) + ((4.65661287e-10f * (float)dsp->iRec13[0]) + (2.49495602f * dsp->fRec12[1]))) - (2.0172658f * dsp->fRec12[2]));
			output0[i] = (FAUSTFLOAT)((fSlow0 * (float)input0[i]) + (dsp->fRec0[0] * (((((fSlow2 * (((iSlow4?(iSlow8?(dsp->fConst4 * (((float)dsp->iVec0[3] * (fTemp9 - dsp->fVec7[1])) / fTemp0)):(dsp->fConst3 * (((float)dsp->iVec0[2] * (fTemp6 - dsp->fVec4[1])) / fTemp0))):(iSlow5?(dsp->fConst2 * (((float)dsp->iVec0[1] * (fTemp4 - dsp->fVec2[1])) / fTemp0)):fTemp3)) + (iSlow4?(iSlow8?(dsp->fConst4 * (((float)dsp->iVec0[3] * (fTemp20 - dsp->fVec14[1])) / fTemp11)):(dsp->fConst3 * (((float)dsp->iVec0[2] * (fTemp17 - dsp->fVec11[1])) / fTemp11))):(iSlow5?(dsp->fConst2 * (((float)dsp->iVec0[1] * (fTemp15 - dsp->fVec9[1])) / fTemp11)):fTemp14))) + (iSlow4?(iSlow8?(dsp->fConst4 * (((float)dsp->iVec0[3] * (fTemp31 - dsp->fVec21[1])) / fTemp22)):(dsp->fConst3 * (((float)dsp->iVec0[2] * (fTemp28 - dsp->fVec18[1])) / fTemp22))):(iSlow5?(dsp->fConst2 * (((float)dsp->iVec0[1] * (fTemp26 - dsp->fVec16[1])) / fTemp22)):fTemp25)))) + (fSlow11 * ((fTemp42 + fTemp53) + fTemp64))) + (fSlow12 * (dsp->fRec2[0] * ((dsp->fRec8[0] + (fSlow9 * dsp->fRec9[0])) + (fSlow10 * dsp->fRec10[0]))))) + (fSlow13 * ((fSlow15 * ((((fTemp38 - (fTemp67 * dsp->fVec24[((dsp->IOTA - iTemp68) & 4095)])) - (fTemp69 * dsp->fVec24[((dsp->IOTA - iTemp70) & 4095)])) + ((fTemp49 - (fTemp73 * dsp->fVec27[((dsp->IOTA - iTemp74) & 4095)])) - (fTemp75 * dsp->fVec27[((dsp->IOTA - iTemp76) & 4095)]))) + ((fTemp60 - (fTemp79 * dsp->fVec30[((dsp->IOTA - iTemp80) & 4095)])) - (fTemp81 * dsp->fVec30[((dsp->IOTA - iTemp82) & 4095)])))) + (fSlow17 * ((((fTemp85 - (dsp->fVec33[((dsp->IOTA - iTemp68) & 4095)] * fTemp67)) - (fTemp69 * dsp->fVec33[((dsp->IOTA - iTemp70) & 4095)])) + ((fTemp88 - (dsp->fVec36[((dsp->IOTA - iTemp74) & 4095)] * fTemp73)) - (fTemp75 * dsp->fVec36[((dsp->IOTA - iTemp76) & 4095)]))) + ((fTemp91 - (dsp->fVec39[((dsp->IOTA - iTemp80) & 4095)] * fTemp79)) - (fTemp81 * dsp->fVec39[((dsp->IOTA - iTemp82) & 4095)]))))))) + (fSlow18 * (((0.0499220341f * dsp->fRec12[0]) + (0.0506126992f * dsp->fRec12[2])) - ((0.0959935337f * dsp->fRec12[1]) + (0.00440878607f * dsp->fRec12[3])))))));
			/* C99 loop */
			{
				int j0;
				for (j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
					dsp->iVec0[j0] = dsp->iVec0[(j0 - 1)];
					
				}
				
			}
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fVec1[1] = dsp->fVec1[0];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fVec2[1] = dsp->fVec2[0];
			dsp->fVec3[1] = dsp->fVec3[0];
			dsp->fVec4[1] = dsp->fVec4[0];
			dsp->fVec5[1] = dsp->fVec5[0];
			dsp->fVec6[1] = dsp->fVec6[0];
			dsp->fVec7[1] = dsp->fVec7[0];
			dsp->fVec8[1] = dsp->fVec8[0];
			dsp->fRec3[1] = dsp->fRec3[0];
			dsp->fVec9[1] = dsp->fVec9[0];
			dsp->fVec10[1] = dsp->fVec10[0];
			dsp->fVec11[1] = dsp->fVec11[0];
			dsp->fVec12[1] = dsp->fVec12[0];
			dsp->fVec13[1] = dsp->fVec13[0];
			dsp->fVec14[1] = dsp->fVec14[0];
			dsp->fVec15[1] = dsp->fVec15[0];
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fVec16[1] = dsp->fVec16[0];
			dsp->fVec17[1] = dsp->fVec17[0];
			dsp->fVec18[1] = dsp->fVec18[0];
			dsp->fVec19[1] = dsp->fVec19[0];
			dsp->fVec20[1] = dsp->fVec20[0];
			dsp->fVec21[1] = dsp->fVec21[0];
			dsp->fVec22[1] = dsp->fVec22[0];
			dsp->fRec5[1] = dsp->fRec5[0];
			dsp->fVec23[1] = dsp->fVec23[0];
			dsp->IOTA = (dsp->IOTA + 1);
			dsp->fVec25[1] = dsp->fVec25[0];
			dsp->fRec6[1] = dsp->fRec6[0];
			dsp->fVec26[1] = dsp->fVec26[0];
			dsp->fVec28[1] = dsp->fVec28[0];
			dsp->fRec7[1] = dsp->fRec7[0];
			dsp->fVec29[1] = dsp->fVec29[0];
			dsp->fRec8[1] = dsp->fRec8[0];
			dsp->fRec9[1] = dsp->fRec9[0];
			dsp->fRec10[1] = dsp->fRec10[0];
			dsp->fRec11[1] = dsp->fRec11[0];
			dsp->fVec31[1] = dsp->fVec31[0];
			dsp->fVec32[1] = dsp->fVec32[0];
			dsp->fVec34[1] = dsp->fVec34[0];
			dsp->fVec35[1] = dsp->fVec35[0];
			dsp->fVec37[1] = dsp->fVec37[0];
			dsp->fVec38[1] = dsp->fVec38[0];
			dsp->iRec13[1] = dsp->iRec13[0];
			/* C99 loop */
			{
				int j1;
				for (j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
					dsp->fRec12[j1] = dsp->fRec12[(j1 - 1)];
					
				}
				
			}
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
