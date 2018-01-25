/* ------------------------------------------------------------
name: "turenas"
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
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	int iVec0[2];
	float fRec0[2];
	float fRec1[2];
	FAUSTFLOAT fButton0;
	float fVec1[2];
	FAUSTFLOAT fHslider2;
	float fRec3[2];
	float fVec2[2];
	float fRec2[2];
	float fConst2;
	float fConst3;
	float fConst4;
	float fRec4[2];
	float fRec5[2];
	float fVec3[2];
	float fRec6[2];
	float fRec7[2];
	float fRec8[2];
	float fVec4[2];
	float fRec9[2];
	float fRec10[2];
	float fRec11[2];
	float fVec5[2];
	float fRec12[2];
	float fRec13[2];
	float fRec14[2];
	float fVec6[2];
	float fRec15[2];
	float fRec16[2];
	float fRec17[2];
	float fVec7[2];
	float fRec18[2];
	
} mydsp;

mydsp* newmydsp() { 
	mydsp* dsp = (mydsp*)malloc(sizeof(mydsp));
	return dsp;
}

void deletemydsp(mydsp* dsp) { 
	free(dsp);
}

void metadatamydsp(MetaGlue* m) { 
	m->declare(m->metaInterface, "basics.lib/name", "Faust Basic Element Library");
	m->declare(m->metaInterface, "basics.lib/version", "0.0");
	m->declare(m->metaInterface, "envelopes.lib/author", "GRAME");
	m->declare(m->metaInterface, "envelopes.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "envelopes.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "envelopes.lib/name", "Faust Envelope Library");
	m->declare(m->metaInterface, "envelopes.lib/version", "0.0");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "interface", "SmartKeyboard{  'Number of Keyboards':'10',  'Keyboard 0 - Number of Keys':'18',  'Keyboard 1 - Number of Keys':'18',  'Keyboard 2 - Number of Keys':'18',  'Keyboard 3 - Number of Keys':'18',  'Keyboard 4 - Number of Keys':'18',  'Keyboard 5 - Number of Keys':'18',  'Keyboard 6 - Number of Keys':'18',  'Keyboard 7 - Number of Keys':'18',  'Keyboard 8 - Number of Keys':'18',  'Keyboard 9 - Number of Keys':'18',  'Keyboard 0 - Lowest Key':'50',  'Keyboard 1 - Lowest Key':'55',  'Keyboard 2 - Lowest Key':'60',  'Keyboard 3 - Lowest Key':'65',  'Keyboard 4 - Lowest Key':'70',  'Keyboard 5 - Lowest Key':'75',  'Keyboard 6 - Lowest Key':'80',  'Keyboard 7 - Lowest Key':'85',  'Keyboard 8 - Lowest Key':'90',  'Keyboard 9 - Lowest Key':'95',  'Keyboard 0 - Piano Keyboard':'0',  'Keyboard 1 - Piano Keyboard':'0',  'Keyboard 2 - Piano Keyboard':'0',  'Keyboard 3 - Piano Keyboard':'0',  'Keyboard 4 - Piano Keyboard':'0',  'Keyboard 5 - Piano Keyboard':'0',  'Keyboard 6 - Piano Keyboard':'0',  'Keyboard 7 - Piano Keyboard':'0',  'Keyboard 8 - Piano Keyboard':'0',  'Keyboard 9 - Piano Keyboard':'0',  'Keyboard 0 - Send X':'0',  'Keyboard 1 - Send X':'0',  'Keyboard 2 - Send X':'0',  'Keyboard 3 - Send X':'0',  'Keyboard 4 - Send X':'0',  'Keyboard 5 - Send X':'0',  'Keyboard 6 - Send X':'0',  'Keyboard 7 - Send X':'0',  'Keyboard 8 - Send X':'0',  'Keyboard 9 - Send X':'0' }");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "turenas");
	m->declare(m->metaInterface, "oscillators.lib/name", "Faust Oscillator Library");
	m->declare(m->metaInterface, "oscillators.lib/version", "0.0");
	m->declare(m->metaInterface, "signals.lib/name", "Faust Signal Routing Library");
	m->declare(m->metaInterface, "signals.lib/version", "0.0");
	m->declare(m->metaInterface, "synths.lib/name", "Faust Synthesizer Library");
	m->declare(m->metaInterface, "synths.lib/version", "0.0");
}

int getSampleRatemydsp(mydsp* dsp) { return dsp->fSamplingFreq; }

int getNumInputsmydsp(mydsp* dsp) {
	return 0;
	
}
int getNumOutputsmydsp(mydsp* dsp) {
	return 1;
	
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
	dsp->fHslider0 = (FAUSTFLOAT)400.0f;
	dsp->fHslider1 = (FAUSTFLOAT)0.0f;
	dsp->fButton0 = (FAUSTFLOAT)0.0f;
	dsp->fHslider2 = (FAUSTFLOAT)2.5f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
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
			dsp->fRec1[l2] = 0.0f;
			
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
			dsp->fRec3[l4] = 0.0f;
			
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
			dsp->fRec2[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			dsp->fRec4[l7] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			dsp->fRec5[l8] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			dsp->fVec3[l9] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			dsp->fRec6[l10] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			dsp->fRec7[l11] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			dsp->fRec8[l12] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l13;
		for (l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			dsp->fVec4[l13] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l14;
		for (l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			dsp->fRec9[l14] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l15;
		for (l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			dsp->fRec10[l15] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l16;
		for (l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			dsp->fRec11[l16] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l17;
		for (l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			dsp->fVec5[l17] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l18;
		for (l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			dsp->fRec12[l18] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l19;
		for (l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			dsp->fRec13[l19] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l20;
		for (l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			dsp->fRec14[l20] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l21;
		for (l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			dsp->fVec6[l21] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l22;
		for (l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			dsp->fRec15[l22] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l23;
		for (l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			dsp->fRec16[l23] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l24;
		for (l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			dsp->fRec17[l24] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l25;
		for (l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			dsp->fVec7[l25] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l26;
		for (l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			dsp->fRec18[l26] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = (6.28318548f / dsp->fConst0);
	dsp->fConst2 = (0.00100000005f * dsp->fConst0);
	dsp->fConst3 = (1.0f / dsp->fConst0);
	dsp->fConst4 = (1000.0f / dsp->fConst0);
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "turenas");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "freq", &dsp->fHslider0, 400.0f, 50.0f, 2000.0f, 0.00999999978f);
	ui_interface->addButton(ui_interface->uiInterface, "gate", &dsp->fButton0);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "acc", "0 0 -10 0 10");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "res", &dsp->fHslider2, 2.5f, 0.00999999978f, 5.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "y", &dsp->fHslider1, 0.0f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* output0 = outputs[0];
	float fSlow0 = (float)dsp->fHslider0;
	float fSlow1 = (float)dsp->fHslider1;
	float fSlow2 = (dsp->fConst1 * (fSlow0 * ((0.833333313f * fSlow1) + 1.0f)));
	float fSlow3 = sinf(fSlow2);
	float fSlow4 = cosf(fSlow2);
	float fSlow5 = (0.0f - fSlow3);
	float fSlow6 = (float)dsp->fButton0;
	float fSlow7 = (0.00100000005f * (float)dsp->fHslider2);
	float fSlow8 = (dsp->fConst1 * (fSlow0 * ((1.66666663f * fSlow1) + 1.0f)));
	float fSlow9 = sinf(fSlow8);
	float fSlow10 = cosf(fSlow8);
	float fSlow11 = (0.0f - fSlow9);
	float fSlow12 = (dsp->fConst1 * (fSlow0 * ((2.5f * fSlow1) + 1.0f)));
	float fSlow13 = sinf(fSlow12);
	float fSlow14 = cosf(fSlow12);
	float fSlow15 = (0.0f - fSlow13);
	float fSlow16 = (dsp->fConst1 * (fSlow0 * ((3.33333325f * fSlow1) + 1.0f)));
	float fSlow17 = sinf(fSlow16);
	float fSlow18 = cosf(fSlow16);
	float fSlow19 = (0.0f - fSlow17);
	float fSlow20 = (dsp->fConst1 * (fSlow0 * ((4.16666651f * fSlow1) + 1.0f)));
	float fSlow21 = sinf(fSlow20);
	float fSlow22 = cosf(fSlow20);
	float fSlow23 = (0.0f - fSlow21);
	float fSlow24 = (dsp->fConst1 * (fSlow0 * ((5.0f * fSlow1) + 1.0f)));
	float fSlow25 = sinf(fSlow24);
	float fSlow26 = cosf(fSlow24);
	float fSlow27 = (0.0f - fSlow25);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->iVec0[0] = 1;
			dsp->fRec0[0] = ((fSlow3 * dsp->fRec1[1]) + (fSlow4 * dsp->fRec0[1]));
			int iTemp0 = (1 - dsp->iVec0[1]);
			dsp->fRec1[0] = (((fSlow4 * dsp->fRec1[1]) + (fSlow5 * dsp->fRec0[1])) + (float)iTemp0);
			dsp->fVec1[0] = fSlow6;
			int iTemp1 = (((fSlow6 - dsp->fVec1[1]) > 0.0f) > 0);
			dsp->fRec3[0] = (fSlow7 + (0.999000013f * dsp->fRec3[1]));
			float fTemp2 = (dsp->fRec3[0] + 0.00100000005f);
			dsp->fVec2[0] = fTemp2;
			float fTemp3 = (dsp->fConst0 * fTemp2);
			dsp->fRec2[0] = (iTemp1?0.0f:min(fTemp3, (dsp->fRec2[1] + (1.0f - (dsp->fConst0 * (dsp->fVec2[1] - fTemp2))))));
			int iTemp4 = (dsp->fRec2[0] < dsp->fConst2);
			dsp->fRec4[0] = ((fSlow9 * dsp->fRec5[1]) + (fSlow10 * dsp->fRec4[1]));
			dsp->fRec5[0] = (((fSlow10 * dsp->fRec5[1]) + (fSlow11 * dsp->fRec4[1])) + (float)iTemp0);
			float fTemp5 = ((0.866666675f * dsp->fRec3[0]) + 0.00100000005f);
			dsp->fVec3[0] = fTemp5;
			float fTemp6 = (dsp->fConst0 * fTemp5);
			dsp->fRec6[0] = (iTemp1?0.0f:min(fTemp6, (dsp->fRec6[1] + (1.0f - (dsp->fConst0 * (dsp->fVec3[1] - fTemp5))))));
			int iTemp7 = (dsp->fRec6[0] < dsp->fConst2);
			dsp->fRec7[0] = ((fSlow13 * dsp->fRec8[1]) + (fSlow14 * dsp->fRec7[1]));
			dsp->fRec8[0] = (((fSlow14 * dsp->fRec8[1]) + (fSlow15 * dsp->fRec7[1])) + (float)iTemp0);
			float fTemp8 = ((0.733333349f * dsp->fRec3[0]) + 0.00100000005f);
			dsp->fVec4[0] = fTemp8;
			float fTemp9 = (dsp->fConst0 * fTemp8);
			dsp->fRec9[0] = (iTemp1?0.0f:min(fTemp9, (dsp->fRec9[1] + (1.0f - (dsp->fConst0 * (dsp->fVec4[1] - fTemp8))))));
			int iTemp10 = (dsp->fRec9[0] < dsp->fConst2);
			dsp->fRec10[0] = ((fSlow17 * dsp->fRec11[1]) + (fSlow18 * dsp->fRec10[1]));
			dsp->fRec11[0] = (((fSlow18 * dsp->fRec11[1]) + (fSlow19 * dsp->fRec10[1])) + (float)iTemp0);
			float fTemp11 = ((0.600000024f * dsp->fRec3[0]) + 0.00100000005f);
			dsp->fVec5[0] = fTemp11;
			float fTemp12 = (dsp->fConst0 * fTemp11);
			dsp->fRec12[0] = (iTemp1?0.0f:min(fTemp12, (dsp->fRec12[1] + (1.0f - (dsp->fConst0 * (dsp->fVec5[1] - fTemp11))))));
			int iTemp13 = (dsp->fRec12[0] < dsp->fConst2);
			dsp->fRec13[0] = ((fSlow21 * dsp->fRec14[1]) + (fSlow22 * dsp->fRec13[1]));
			dsp->fRec14[0] = (((fSlow22 * dsp->fRec14[1]) + (fSlow23 * dsp->fRec13[1])) + (float)iTemp0);
			float fTemp14 = ((0.466666669f * dsp->fRec3[0]) + 0.00100000005f);
			dsp->fVec6[0] = fTemp14;
			float fTemp15 = (dsp->fConst0 * fTemp14);
			dsp->fRec15[0] = (iTemp1?0.0f:min(fTemp15, (dsp->fRec15[1] + (1.0f - (dsp->fConst0 * (dsp->fVec6[1] - fTemp14))))));
			int iTemp16 = (dsp->fRec15[0] < dsp->fConst2);
			dsp->fRec16[0] = ((fSlow25 * dsp->fRec17[1]) + (fSlow26 * dsp->fRec16[1]));
			dsp->fRec17[0] = (((fSlow26 * dsp->fRec17[1]) + (fSlow27 * dsp->fRec16[1])) + (float)iTemp0);
			float fTemp17 = ((0.333333343f * dsp->fRec3[0]) + 0.00100000005f);
			dsp->fVec7[0] = fTemp17;
			float fTemp18 = (dsp->fConst0 * fTemp17);
			dsp->fRec18[0] = (iTemp1?0.0f:min(fTemp18, (dsp->fRec18[1] + (1.0f - (dsp->fConst0 * (dsp->fVec7[1] - fTemp17))))));
			int iTemp19 = (dsp->fRec18[0] < dsp->fConst2);
			output0[i] = (FAUSTFLOAT)(0.0500000007f * ((((((0.444444448f * (dsp->fRec0[0] * (iTemp4?((dsp->fRec2[0] < 0.0f)?0.0f:(iTemp4?(dsp->fConst4 * dsp->fRec2[0]):1.0f)):((dsp->fRec2[0] < fTemp3)?((dsp->fConst3 * ((0.0f - (dsp->fRec2[0] - dsp->fConst2)) / (fTemp2 + -0.00100000005f))) + 1.0f):0.0f)))) + (dsp->fRec4[0] * (0.0f - (0.111111112f * (iTemp7?((dsp->fRec6[0] < 0.0f)?0.0f:(iTemp7?(dsp->fConst4 * dsp->fRec6[0]):1.0f)):((dsp->fRec6[0] < fTemp6)?((dsp->fConst3 * ((0.0f - (dsp->fRec6[0] - dsp->fConst2)) / (fTemp5 + -0.00100000005f))) + 1.0f):0.0f)))))) + (dsp->fRec7[0] * (0.0f - (0.666666687f * (iTemp10?((dsp->fRec9[0] < 0.0f)?0.0f:(iTemp10?(dsp->fConst4 * dsp->fRec9[0]):1.0f)):((dsp->fRec9[0] < fTemp9)?((dsp->fConst3 * ((0.0f - (dsp->fRec9[0] - dsp->fConst2)) / (fTemp8 + -0.00100000005f))) + 1.0f):0.0f)))))) + (dsp->fRec10[0] * (0.0f - (1.22222221f * (iTemp13?((dsp->fRec12[0] < 0.0f)?0.0f:(iTemp13?(dsp->fConst4 * dsp->fRec12[0]):1.0f)):((dsp->fRec12[0] < fTemp12)?((dsp->fConst3 * ((0.0f - (dsp->fRec12[0] - dsp->fConst2)) / (fTemp11 + -0.00100000005f))) + 1.0f):0.0f)))))) + (dsp->fRec13[0] * (0.0f - (1.77777779f * (iTemp16?((dsp->fRec15[0] < 0.0f)?0.0f:(iTemp16?(dsp->fConst4 * dsp->fRec15[0]):1.0f)):((dsp->fRec15[0] < fTemp15)?((dsp->fConst3 * ((0.0f - (dsp->fRec15[0] - dsp->fConst2)) / (fTemp14 + -0.00100000005f))) + 1.0f):0.0f)))))) + (dsp->fRec16[0] * (0.0f - (2.33333325f * (iTemp19?((dsp->fRec18[0] < 0.0f)?0.0f:(iTemp19?(dsp->fConst4 * dsp->fRec18[0]):1.0f)):((dsp->fRec18[0] < fTemp18)?((dsp->fConst3 * ((0.0f - (dsp->fRec18[0] - dsp->fConst2)) / (fTemp17 + -0.00100000005f))) + 1.0f):0.0f)))))));
			dsp->iVec0[1] = dsp->iVec0[0];
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fVec1[1] = dsp->fVec1[0];
			dsp->fRec3[1] = dsp->fRec3[0];
			dsp->fVec2[1] = dsp->fVec2[0];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fRec5[1] = dsp->fRec5[0];
			dsp->fVec3[1] = dsp->fVec3[0];
			dsp->fRec6[1] = dsp->fRec6[0];
			dsp->fRec7[1] = dsp->fRec7[0];
			dsp->fRec8[1] = dsp->fRec8[0];
			dsp->fVec4[1] = dsp->fVec4[0];
			dsp->fRec9[1] = dsp->fRec9[0];
			dsp->fRec10[1] = dsp->fRec10[0];
			dsp->fRec11[1] = dsp->fRec11[0];
			dsp->fVec5[1] = dsp->fVec5[0];
			dsp->fRec12[1] = dsp->fRec12[0];
			dsp->fRec13[1] = dsp->fRec13[0];
			dsp->fRec14[1] = dsp->fRec14[0];
			dsp->fVec6[1] = dsp->fVec6[0];
			dsp->fRec15[1] = dsp->fRec15[0];
			dsp->fRec16[1] = dsp->fRec16[0];
			dsp->fRec17[1] = dsp->fRec17[0];
			dsp->fVec7[1] = dsp->fVec7[0];
			dsp->fRec18[1] = dsp->fRec18[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
