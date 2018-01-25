/* ------------------------------------------------------------
name: "bowed"
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
	
	int iVec0[2];
	FAUSTFLOAT fHslider0;
	float fRec2[2];
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	float fRec1[2];
	float fRec0[2];
	float fConst3;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	float fRec6[2];
	float fRec5[2];
	FAUSTFLOAT fHslider4;
	float fRec9[2];
	float fRec7[2];
	float fRec8[2];
	float fRec12[2];
	float fRec11[2];
	float fRec10[2];
	float fRec3[2];
	float fRec4[2];
	float fRec16[2];
	float fRec15[2];
	float fRec17[2];
	float fRec18[2];
	float fRec13[2];
	float fRec14[2];
	float fRec22[2];
	float fRec21[2];
	float fRec23[2];
	float fRec24[2];
	float fRec19[2];
	float fRec20[2];
	float fRec28[2];
	float fRec27[2];
	float fRec29[2];
	float fRec30[2];
	float fRec25[2];
	float fRec26[2];
	
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
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "interface", "SmartKeyboard{  'Number of Keyboards':'5',  'Max Keyboard Polyphony':'0',  'Rounding Mode':'1',  'Keyboard 0 - Number of Keys':'19',  'Keyboard 1 - Number of Keys':'19',  'Keyboard 2 - Number of Keys':'19',  'Keyboard 3 - Number of Keys':'19',  'Keyboard 4 - Number of Keys':'1',  'Keyboard 4 - Send Freq':'0',  'Keyboard 0 - Send X':'0',  'Keyboard 1 - Send X':'0',  'Keyboard 2 - Send X':'0',  'Keyboard 3 - Send X':'0',  'Keyboard 0 - Send Y':'0',  'Keyboard 1 - Send Y':'0',  'Keyboard 2 - Send Y':'0',  'Keyboard 3 - Send Y':'0',  'Keyboard 0 - Lowest Key':'55',  'Keyboard 1 - Lowest Key':'62',  'Keyboard 2 - Lowest Key':'69',  'Keyboard 3 - Lowest Key':'76',  'Keyboard 4 - Piano Keyboard':'0',  'Keyboard 4 - Key 0 - Label':'Bow' }");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "bowed");
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
	dsp->fHslider0 = (FAUSTFLOAT)0.5f;
	dsp->fHslider1 = (FAUSTFLOAT)0.0f;
	dsp->fHslider2 = (FAUSTFLOAT)400.0f;
	dsp->fHslider3 = (FAUSTFLOAT)1.0f;
	dsp->fHslider4 = (FAUSTFLOAT)0.0f;
	
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
			dsp->fRec2[l1] = 0.0f;
			
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
			dsp->fRec0[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			dsp->fRec6[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			dsp->fRec5[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			dsp->fRec9[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			dsp->fRec7[l7] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			dsp->fRec8[l8] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			dsp->fRec12[l9] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			dsp->fRec11[l10] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			dsp->fRec10[l11] = 0.0f;
			
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
			dsp->fRec4[l13] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l14;
		for (l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			dsp->fRec16[l14] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l15;
		for (l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			dsp->fRec15[l15] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l16;
		for (l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			dsp->fRec17[l16] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l17;
		for (l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			dsp->fRec18[l17] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l18;
		for (l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			dsp->fRec13[l18] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l19;
		for (l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			dsp->fRec14[l19] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l20;
		for (l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			dsp->fRec22[l20] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l21;
		for (l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			dsp->fRec21[l21] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l22;
		for (l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			dsp->fRec23[l22] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l23;
		for (l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			dsp->fRec24[l23] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l24;
		for (l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			dsp->fRec19[l24] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l25;
		for (l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			dsp->fRec20[l25] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l26;
		for (l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			dsp->fRec28[l26] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l27;
		for (l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			dsp->fRec27[l27] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l28;
		for (l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			dsp->fRec29[l28] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l29;
		for (l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			dsp->fRec30[l29] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l30;
		for (l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			dsp->fRec25[l30] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l31;
		for (l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			dsp->fRec26[l31] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = expf((0.0f - (10.0f / dsp->fConst0)));
	dsp->fConst2 = expf((0.0f - (1.0f / dsp->fConst0)));
	dsp->fConst3 = (6.28318548f / dsp->fConst0);
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "bowed");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "bend", &dsp->fHslider3, 1.0f, 0.0f, 10.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "freq", &dsp->fHslider2, 400.0f, 50.0f, 2000.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "keyboard", &dsp->fHslider1, 0.0f, 0.0f, 5.0f, 1.0f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "x", &dsp->fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "y", &dsp->fHslider4, 0.0f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	float fSlow0 = (0.00100000005f * (float)dsp->fHslider0);
	int iSlow1 = (int)(float)dsp->fHslider1;
	int iSlow2 = (iSlow1 == 3);
	float fSlow3 = ((float)dsp->fHslider2 * (float)dsp->fHslider3);
	float fSlow4 = (0.00100000005f * (float)dsp->fHslider4);
	int iSlow5 = (iSlow1 == 2);
	int iSlow6 = (iSlow1 == 0);
	int iSlow7 = (iSlow1 == 1);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->iVec0[0] = 1;
			dsp->fRec2[0] = (fSlow0 + (0.999000013f * dsp->fRec2[1]));
			float fTemp0 = fabsf(fabsf((dsp->fRec2[0] - dsp->fRec2[1])));
			float fTemp1 = ((dsp->fRec0[1] > fTemp0)?dsp->fConst2:dsp->fConst1);
			dsp->fRec1[0] = ((dsp->fRec1[1] * fTemp1) + (fTemp0 * (1.0f - fTemp1)));
			dsp->fRec0[0] = dsp->fRec1[0];
			dsp->fRec6[0] = (iSlow2?fSlow3:dsp->fRec6[1]);
			dsp->fRec5[0] = ((0.999000013f * dsp->fRec5[1]) + (0.00100000005f * dsp->fRec6[0]));
			dsp->fRec9[0] = (fSlow4 + (0.999000013f * dsp->fRec9[1]));
			float fTemp2 = ((0.300000012f * dsp->fRec9[0]) + 1.0f);
			float fTemp3 = (dsp->fConst3 * (dsp->fRec5[0] * fTemp2));
			float fTemp4 = sinf(fTemp3);
			float fTemp5 = cosf(fTemp3);
			dsp->fRec7[0] = ((dsp->fRec8[1] * fTemp4) + (dsp->fRec7[1] * fTemp5));
			int iTemp6 = (1 - dsp->iVec0[1]);
			dsp->fRec8[0] = (((dsp->fRec8[1] * fTemp5) + (dsp->fRec7[1] * (0.0f - fTemp4))) + (float)iTemp6);
			dsp->fRec12[0] = (fSlow0 + (0.999000013f * dsp->fRec12[1]));
			float fTemp7 = fabsf(fabsf((dsp->fRec12[0] - dsp->fRec12[1])));
			float fTemp8 = ((dsp->fRec10[1] > fTemp7)?dsp->fConst2:dsp->fConst1);
			dsp->fRec11[0] = ((dsp->fRec11[1] * fTemp8) + (fTemp7 * (1.0f - fTemp8)));
			dsp->fRec10[0] = dsp->fRec11[0];
			float fTemp9 = min(1.0f, (8000.0f * dsp->fRec10[0]));
			float fTemp10 = (dsp->fConst3 * (dsp->fRec5[0] + (1000.0f * (dsp->fRec7[0] * fTemp9))));
			float fTemp11 = sinf(fTemp10);
			float fTemp12 = cosf(fTemp10);
			dsp->fRec3[0] = ((dsp->fRec4[1] * fTemp11) + (dsp->fRec3[1] * fTemp12));
			dsp->fRec4[0] = (((dsp->fRec4[1] * fTemp12) + (dsp->fRec3[1] * (0.0f - fTemp11))) + (float)iTemp6);
			dsp->fRec16[0] = (iSlow5?fSlow3:dsp->fRec16[1]);
			dsp->fRec15[0] = ((0.999000013f * dsp->fRec15[1]) + (0.00100000005f * dsp->fRec16[0]));
			float fTemp13 = (dsp->fConst3 * (dsp->fRec15[0] * fTemp2));
			float fTemp14 = sinf(fTemp13);
			float fTemp15 = cosf(fTemp13);
			dsp->fRec17[0] = ((dsp->fRec18[1] * fTemp14) + (dsp->fRec17[1] * fTemp15));
			dsp->fRec18[0] = (((dsp->fRec18[1] * fTemp15) + (dsp->fRec17[1] * (0.0f - fTemp14))) + (float)iTemp6);
			float fTemp16 = (dsp->fConst3 * (dsp->fRec15[0] + (1000.0f * (dsp->fRec17[0] * fTemp9))));
			float fTemp17 = sinf(fTemp16);
			float fTemp18 = cosf(fTemp16);
			dsp->fRec13[0] = ((dsp->fRec14[1] * fTemp17) + (dsp->fRec13[1] * fTemp18));
			dsp->fRec14[0] = (((dsp->fRec14[1] * fTemp18) + (dsp->fRec13[1] * (0.0f - fTemp17))) + (float)iTemp6);
			dsp->fRec22[0] = (iSlow6?fSlow3:dsp->fRec22[1]);
			dsp->fRec21[0] = ((0.999000013f * dsp->fRec21[1]) + (0.00100000005f * dsp->fRec22[0]));
			float fTemp19 = (dsp->fConst3 * (dsp->fRec21[0] * fTemp2));
			float fTemp20 = sinf(fTemp19);
			float fTemp21 = cosf(fTemp19);
			dsp->fRec23[0] = ((dsp->fRec24[1] * fTemp20) + (dsp->fRec23[1] * fTemp21));
			dsp->fRec24[0] = (((dsp->fRec24[1] * fTemp21) + (dsp->fRec23[1] * (0.0f - fTemp20))) + (float)iTemp6);
			float fTemp22 = (dsp->fConst3 * (dsp->fRec21[0] + (1000.0f * (dsp->fRec23[0] * fTemp9))));
			float fTemp23 = sinf(fTemp22);
			float fTemp24 = cosf(fTemp22);
			dsp->fRec19[0] = ((dsp->fRec20[1] * fTemp23) + (dsp->fRec19[1] * fTemp24));
			dsp->fRec20[0] = (((dsp->fRec20[1] * fTemp24) + (dsp->fRec19[1] * (0.0f - fTemp23))) + (float)iTemp6);
			dsp->fRec28[0] = (iSlow7?fSlow3:dsp->fRec28[1]);
			dsp->fRec27[0] = ((0.999000013f * dsp->fRec27[1]) + (0.00100000005f * dsp->fRec28[0]));
			float fTemp25 = (dsp->fConst3 * (dsp->fRec27[0] * fTemp2));
			float fTemp26 = sinf(fTemp25);
			float fTemp27 = cosf(fTemp25);
			dsp->fRec29[0] = ((dsp->fRec30[1] * fTemp26) + (dsp->fRec29[1] * fTemp27));
			dsp->fRec30[0] = (((dsp->fRec30[1] * fTemp27) + (dsp->fRec29[1] * (0.0f - fTemp26))) + (float)iTemp6);
			float fTemp28 = (dsp->fConst3 * (dsp->fRec27[0] + (1000.0f * (dsp->fRec29[0] * fTemp9))));
			float fTemp29 = sinf(fTemp28);
			float fTemp30 = cosf(fTemp28);
			dsp->fRec25[0] = ((dsp->fRec26[1] * fTemp29) + (dsp->fRec25[1] * fTemp30));
			dsp->fRec26[0] = (((dsp->fRec26[1] * fTemp30) + (dsp->fRec25[1] * (0.0f - fTemp29))) + (float)iTemp6);
			float fTemp31 = (min(1.0f, (8000.0f * dsp->fRec0[0])) * (dsp->fRec3[0] + (dsp->fRec13[0] + (dsp->fRec19[0] + dsp->fRec25[0]))));
			output0[i] = (FAUSTFLOAT)fTemp31;
			output1[i] = (FAUSTFLOAT)fTemp31;
			dsp->iVec0[1] = dsp->iVec0[0];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec6[1] = dsp->fRec6[0];
			dsp->fRec5[1] = dsp->fRec5[0];
			dsp->fRec9[1] = dsp->fRec9[0];
			dsp->fRec7[1] = dsp->fRec7[0];
			dsp->fRec8[1] = dsp->fRec8[0];
			dsp->fRec12[1] = dsp->fRec12[0];
			dsp->fRec11[1] = dsp->fRec11[0];
			dsp->fRec10[1] = dsp->fRec10[0];
			dsp->fRec3[1] = dsp->fRec3[0];
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fRec16[1] = dsp->fRec16[0];
			dsp->fRec15[1] = dsp->fRec15[0];
			dsp->fRec17[1] = dsp->fRec17[0];
			dsp->fRec18[1] = dsp->fRec18[0];
			dsp->fRec13[1] = dsp->fRec13[0];
			dsp->fRec14[1] = dsp->fRec14[0];
			dsp->fRec22[1] = dsp->fRec22[0];
			dsp->fRec21[1] = dsp->fRec21[0];
			dsp->fRec23[1] = dsp->fRec23[0];
			dsp->fRec24[1] = dsp->fRec24[0];
			dsp->fRec19[1] = dsp->fRec19[0];
			dsp->fRec20[1] = dsp->fRec20[0];
			dsp->fRec28[1] = dsp->fRec28[0];
			dsp->fRec27[1] = dsp->fRec27[0];
			dsp->fRec29[1] = dsp->fRec29[0];
			dsp->fRec30[1] = dsp->fRec30[0];
			dsp->fRec25[1] = dsp->fRec25[0];
			dsp->fRec26[1] = dsp->fRec26[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
