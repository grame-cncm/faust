/* ------------------------------------------------------------
name: "multiSynth"
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
	
	int iVec0[2];
	FAUSTFLOAT fButton0;
	FAUSTFLOAT fHslider0;
	float fVec1[2];
	FAUSTFLOAT fHslider1;
	float fRec0[2];
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider2;
	float fRec3[2];
	FAUSTFLOAT fHslider3;
	float fConst2;
	float fConst3;
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT fHslider5;
	float fRec5[2];
	float fVec2[2];
	float fRec4[2];
	float fVec3[2];
	int IOTA;
	float fVec4[4096];
	float fConst4;
	float fConst5;
	float fRec6[2];
	float fConst6;
	float fRec7[2];
	float fRec8[2];
	float fConst7;
	float fRec9[2];
	float fVec5[2];
	float fRec2[2];
	float fRec1[3];
	
} mydsp;

mydsp* newmydsp() { 
	mydsp* dsp = (mydsp*)malloc(sizeof(mydsp));
	return dsp;
}

void deletemydsp(mydsp* dsp) { 
	free(dsp);
}

void metadatamydsp(MetaGlue* m) { 
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "interface", "SmartKeyboard{  'Number of Keyboards':'4',  'Rounding Mode':'2',  'Inter-Keyboard Slide':'0',  'Keyboard 0 - Number of Keys':'13',  'Keyboard 1 - Number of Keys':'13',  'Keyboard 2 - Number of Keys':'13',  'Keyboard 3 - Number of Keys':'13',  'Keyboard 0 - Lowest Key':'60',  'Keyboard 1 - Lowest Key':'60',  'Keyboard 2 - Lowest Key':'60',  'Keyboard 3 - Lowest Key':'60',  'Keyboard 0 - Send Y':'1',  'Keyboard 1 - Send Y':'1',  'Keyboard 2 - Send Y':'1',  'Keyboard 3 - Send Y':'1' }");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "multiSynth");
	m->declare(m->metaInterface, "oscillators.lib/name", "Faust Oscillator Library");
	m->declare(m->metaInterface, "oscillators.lib/version", "0.0");
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
	dsp->fButton0 = (FAUSTFLOAT)0.0f;
	dsp->fHslider0 = (FAUSTFLOAT)0.0f;
	dsp->fHslider1 = (FAUSTFLOAT)1.0f;
	dsp->fHslider2 = (FAUSTFLOAT)1.0f;
	dsp->fHslider3 = (FAUSTFLOAT)0.0f;
	dsp->fHslider4 = (FAUSTFLOAT)300.0f;
	dsp->fHslider5 = (FAUSTFLOAT)1.0f;
	
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
			dsp->fVec1[l1] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			dsp->fRec0[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			dsp->fRec3[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			dsp->fRec5[l4] = 0.0f;
			
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
			dsp->fRec4[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			dsp->fVec3[l7] = 0.0f;
			
		}
		
	}
	dsp->IOTA = 0;
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 4096); l8 = (l8 + 1)) {
			dsp->fVec4[l8] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			dsp->fRec6[l9] = 0.0f;
			
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
		for (l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			dsp->fRec8[l11] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			dsp->fRec9[l12] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l13;
		for (l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			dsp->fVec5[l13] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l14;
		for (l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			dsp->fRec2[l14] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l15;
		for (l15 = 0; (l15 < 3); l15 = (l15 + 1)) {
			dsp->fRec1[l15] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = (3.14159274f / dsp->fConst0);
	dsp->fConst2 = (0.25f * dsp->fConst0);
	dsp->fConst3 = (1.0f / dsp->fConst0);
	dsp->fConst4 = (0.5f * dsp->fConst0);
	dsp->fConst5 = (4.0f / dsp->fConst0);
	dsp->fConst6 = (6.28318548f / dsp->fConst0);
	dsp->fConst7 = (1.0f / dsp->fConst0);
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "multiSynth");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "midi", "pitchwheel");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "bend", &dsp->fHslider5, 1.0f, 0.0f, 10.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "freq", &dsp->fHslider4, 300.0f, 50.0f, 2000.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "gain", &dsp->fHslider1, 1.0f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->addButton(ui_interface->uiInterface, "gate", &dsp->fButton0);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "keyboard", &dsp->fHslider3, 0.0f, 0.0f, 3.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "midi", "ctrl 64");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "sustain", &dsp->fHslider0, 0.0f, 0.0f, 1.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "midi", "ctrl 1");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "y", &dsp->fHslider2, 1.0f, 0.0f, 1.0f, 0.00100000005f);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	float fSlow0 = min(1.0f, ((float)dsp->fButton0 + (float)dsp->fHslider0));
	float fSlow1 = (0.00100000005f * (fSlow0 * (float)dsp->fHslider1));
	float fSlow2 = (0.00100000005f * (float)dsp->fHslider2);
	int iSlow3 = (int)(float)dsp->fHslider3;
	int iSlow4 = (iSlow3 == 2);
	float fSlow5 = (float)dsp->fHslider4;
	float fSlow6 = (float)dsp->fHslider5;
	int iSlow7 = (fSlow0 == 0.0f);
	int iSlow8 = (iSlow3 == 1);
	float fSlow9 = (dsp->fConst5 * fSlow5);
	int iSlow10 = (iSlow3 == 3);
	float fSlow11 = (dsp->fConst6 * fSlow5);
	int iSlow12 = (iSlow3 == 0);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->iVec0[0] = 1;
			dsp->fVec1[0] = fSlow0;
			dsp->fRec0[0] = (fSlow1 + (0.999000013f * dsp->fRec0[1]));
			dsp->fRec3[0] = (fSlow2 + (0.999000013f * dsp->fRec3[1]));
			float fTemp0 = tanf((dsp->fConst1 * ((4000.0f * dsp->fRec3[0]) + 50.0f)));
			float fTemp1 = (1.0f / fTemp0);
			float fTemp2 = (fTemp1 + 1.0f);
			int iTemp3 = ((fSlow0 == dsp->fVec1[1]) | iSlow7);
			dsp->fRec5[0] = ((fSlow6 * (1.0f - (0.999000013f * (float)iTemp3))) + (0.999000013f * ((float)iTemp3 * dsp->fRec5[1])));
			float fTemp4 = (fSlow5 * dsp->fRec5[0]);
			float fTemp5 = max(fTemp4, 23.4489498f);
			float fTemp6 = max(20.0f, fabsf(fTemp5));
			dsp->fVec2[0] = fTemp6;
			float fTemp7 = (dsp->fRec4[1] + (dsp->fConst3 * dsp->fVec2[1]));
			dsp->fRec4[0] = (fTemp7 - floorf(fTemp7));
			float fTemp8 = mydsp_faustpower2_f(((2.0f * dsp->fRec4[0]) + -1.0f));
			dsp->fVec3[0] = fTemp8;
			float fTemp9 = (((float)dsp->iVec0[1] * (fTemp8 - dsp->fVec3[1])) / fTemp6);
			dsp->fVec4[(dsp->IOTA & 4095)] = fTemp9;
			float fTemp10 = max(0.0f, min(2047.0f, (dsp->fConst4 / fTemp5)));
			int iTemp11 = (int)fTemp10;
			float fTemp12 = floorf(fTemp10);
			float fTemp13 = (dsp->fConst2 * ((fTemp9 - (dsp->fVec4[((dsp->IOTA - iTemp11) & 4095)] * (fTemp12 + (1.0f - fTemp10)))) - ((fTemp10 - fTemp12) * dsp->fVec4[((dsp->IOTA - (iTemp11 + 1)) & 4095)])));
			dsp->fRec6[0] = ((0.999000013f * dsp->fRec6[1]) + fTemp13);
			float fTemp14 = (fSlow11 * dsp->fRec5[0]);
			float fTemp15 = sinf(fTemp14);
			float fTemp16 = cosf(fTemp14);
			dsp->fRec7[0] = ((dsp->fRec8[1] * fTemp15) + (dsp->fRec7[1] * fTemp16));
			dsp->fRec8[0] = (((dsp->fRec8[1] * fTemp16) + (dsp->fRec7[1] * (0.0f - fTemp15))) + (float)(1 - dsp->iVec0[1]));
			float fTemp17 = max(1.00000001e-07f, fabsf(fTemp4));
			float fTemp18 = (dsp->fRec9[1] + (dsp->fConst7 * fTemp17));
			float fTemp19 = (fTemp18 + -1.0f);
			int iTemp20 = (fTemp19 < 0.0f);
			dsp->fRec9[0] = (iTemp20?fTemp18:fTemp19);
			float fRec10 = (iTemp20?fTemp18:(fTemp18 + ((1.0f - (dsp->fConst0 / fTemp17)) * fTemp19)));
			float fTemp21 = ((iSlow4?fTemp13:0.0f) + ((iSlow8?(fSlow9 * (dsp->fRec5[0] * dsp->fRec6[0])):0.0f) + ((iSlow10?dsp->fRec7[0]:0.0f) + (iSlow12?((2.0f * fRec10) + -1.0f):0.0f))));
			dsp->fVec5[0] = fTemp21;
			dsp->fRec2[0] = ((dsp->fRec2[1] * (0.0f - ((1.0f - fTemp1) / fTemp2))) + ((fTemp21 + dsp->fVec5[1]) / fTemp2));
			float fTemp22 = (((fTemp1 + 1.0f) / fTemp0) + 1.0f);
			dsp->fRec1[0] = (dsp->fRec2[0] - (((dsp->fRec1[2] * (((fTemp1 + -1.0f) / fTemp0) + 1.0f)) + (2.0f * (dsp->fRec1[1] * (1.0f - (1.0f / mydsp_faustpower2_f(fTemp0)))))) / fTemp22));
			float fTemp23 = ((dsp->fRec0[0] * (dsp->fRec1[2] + (dsp->fRec1[0] + (2.0f * dsp->fRec1[1])))) / fTemp22);
			output0[i] = (FAUSTFLOAT)fTemp23;
			output1[i] = (FAUSTFLOAT)fTemp23;
			dsp->iVec0[1] = dsp->iVec0[0];
			dsp->fVec1[1] = dsp->fVec1[0];
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec3[1] = dsp->fRec3[0];
			dsp->fRec5[1] = dsp->fRec5[0];
			dsp->fVec2[1] = dsp->fVec2[0];
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fVec3[1] = dsp->fVec3[0];
			dsp->IOTA = (dsp->IOTA + 1);
			dsp->fRec6[1] = dsp->fRec6[0];
			dsp->fRec7[1] = dsp->fRec7[0];
			dsp->fRec8[1] = dsp->fRec8[0];
			dsp->fRec9[1] = dsp->fRec9[0];
			dsp->fVec5[1] = dsp->fVec5[0];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec1[2] = dsp->fRec1[1];
			dsp->fRec1[1] = dsp->fRec1[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
