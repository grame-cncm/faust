/* ------------------------------------------------------------
copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
license: "MIT"
name: "ViolinMidi"
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
	
	FAUSTFLOAT fHslider0;
	int iRec10[2];
	int iVec0[2];
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	FAUSTFLOAT fHslider1;
	float fRec26[2];
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT fButton0;
	FAUSTFLOAT fHslider4;
	float fVec1[2];
	float fRec27[2];
	FAUSTFLOAT fHslider5;
	float fConst6;
	FAUSTFLOAT fHslider6;
	float fRec28[2];
	float fRec29[2];
	FAUSTFLOAT fHslider7;
	float fConst7;
	FAUSTFLOAT fHslider8;
	float fRec30[2];
	float fRec22[2];
	float fRec31[4];
	int IOTA;
	float fRec32[2048];
	float fVec2[2];
	FAUSTFLOAT fHslider9;
	float fRec34[2];
	float fVec3[2048];
	float fRec18[2048];
	float fRec20[2];
	float fRec16[4];
	float fConst8;
	float fConst9;
	float fRec14[3];
	float fConst10;
	int iRec6[2];
	float fRec2[2048];
	float fRec0[2];
	
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
	m->declare(m->metaInterface, "copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
	m->declare(m->metaInterface, "delays.lib/name", "Faust Delay Library");
	m->declare(m->metaInterface, "delays.lib/version", "0.0");
	m->declare(m->metaInterface, "description", "Simple MIDI-controllable violin physical model.");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "license", "MIT");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "ViolinMidi");
	m->declare(m->metaInterface, "oscillators.lib/name", "Faust Oscillator Library");
	m->declare(m->metaInterface, "oscillators.lib/version", "0.0");
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
	dsp->fHslider0 = (FAUSTFLOAT)0.5f;
	dsp->fHslider1 = (FAUSTFLOAT)0.69999999999999996f;
	dsp->fHslider2 = (FAUSTFLOAT)440.0f;
	dsp->fHslider3 = (FAUSTFLOAT)1.0f;
	dsp->fButton0 = (FAUSTFLOAT)0.0f;
	dsp->fHslider4 = (FAUSTFLOAT)0.0f;
	dsp->fHslider5 = (FAUSTFLOAT)0.5f;
	dsp->fHslider6 = (FAUSTFLOAT)6.0f;
	dsp->fHslider7 = (FAUSTFLOAT)0.59999999999999998f;
	dsp->fHslider8 = (FAUSTFLOAT)1.0f;
	dsp->fHslider9 = (FAUSTFLOAT)0.5f;
	
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
			dsp->iVec0[l1] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			dsp->fRec26[l2] = 0.0f;
			
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
			dsp->fRec27[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			dsp->fRec28[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			dsp->fRec29[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			dsp->fRec30[l7] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			dsp->fRec22[l8] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 4); l9 = (l9 + 1)) {
			dsp->fRec31[l9] = 0.0f;
			
		}
		
	}
	dsp->IOTA = 0;
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 2048); l10 = (l10 + 1)) {
			dsp->fRec32[l10] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			dsp->fVec2[l11] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			dsp->fRec34[l12] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l13;
		for (l13 = 0; (l13 < 2048); l13 = (l13 + 1)) {
			dsp->fVec3[l13] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l14;
		for (l14 = 0; (l14 < 2048); l14 = (l14 + 1)) {
			dsp->fRec18[l14] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l15;
		for (l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			dsp->fRec20[l15] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l16;
		for (l16 = 0; (l16 < 4); l16 = (l16 + 1)) {
			dsp->fRec16[l16] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l17;
		for (l17 = 0; (l17 < 3); l17 = (l17 + 1)) {
			dsp->fRec14[l17] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l18;
		for (l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			dsp->iRec6[l18] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l19;
		for (l19 = 0; (l19 < 2048); l19 = (l19 + 1)) {
			dsp->fRec2[l19] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l20;
		for (l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			dsp->fRec0[l20] = 0.0f;
			
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
	dsp->fConst5 = (0.00147058826f * dsp->fConst0);
	dsp->fConst6 = (6.28318548f / dsp->fConst0);
	dsp->fConst7 = (1000.0f / dsp->fConst0);
	dsp->fConst8 = (((dsp->fConst2 + -0.5f) / dsp->fConst1) + 1.0f);
	dsp->fConst9 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(dsp->fConst1))));
	dsp->fConst10 = (0.0f - dsp->fConst2);
	
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
	ui_interface->declare(ui_interface->uiInterface, 0, "0", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "midi");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "freq", &dsp->fHslider2, 440.0f, 50.0f, 1000.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "hidden", "1");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "midi", "pitchwheel");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "bend", &dsp->fHslider3, 1.0f, 0.0f, 10.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider7, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider7, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "gain", &dsp->fHslider7, 0.600000024f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider8, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider8, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "envAttack", &dsp->fHslider8, 1.0f, 0.0f, 30.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "4", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "hidden", "1");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "midi", "ctrl 64");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "sustain", &dsp->fHslider4, 0.0f, 0.0f, 1.0f, 1.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "1", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "bow");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider9, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider9, "midi", "ctrl 1");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider9, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "pressure", &dsp->fHslider9, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "position", &dsp->fHslider1, 0.699999988f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "2", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "otherParams");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider6, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider6, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "vibratoFrequency", &dsp->fHslider6, 6.0f, 1.0f, 10.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "vibratoGain", &dsp->fHslider5, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "outGain", &dsp->fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fButton0, "3", "");
	ui_interface->addButton(ui_interface->uiInterface, "gate", &dsp->fButton0);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	float fSlow0 = (float)dsp->fHslider0;
	float fSlow1 = (0.00100000005f * (float)dsp->fHslider1);
	float fSlow2 = (340.0f / (float)dsp->fHslider2);
	float fSlow3 = (float)dsp->fHslider3;
	float fSlow4 = min(1.0f, ((float)dsp->fButton0 + (float)dsp->fHslider4));
	int iSlow5 = (fSlow4 == 0.0f);
	float fSlow6 = (0.00999999978f * (float)dsp->fHslider5);
	float fSlow7 = (dsp->fConst6 * (float)dsp->fHslider6);
	float fSlow8 = sinf(fSlow7);
	float fSlow9 = cosf(fSlow7);
	float fSlow10 = (0.0f - fSlow8);
	float fSlow11 = expf((0.0f - (dsp->fConst7 / (float)dsp->fHslider8)));
	float fSlow12 = ((fSlow4 * (float)dsp->fHslider7) * (1.0f - fSlow11));
	float fSlow13 = (0.00100000005f * (float)dsp->fHslider9);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->iRec10[0] = 0;
			dsp->iVec0[0] = 1;
			int iRec11 = dsp->iRec10[1];
			float fRec15 = ((float)dsp->iRec6[1] - (0.989264667f * ((0.600000024f * dsp->fRec16[2]) + (0.200000003f * (dsp->fRec16[1] + dsp->fRec16[3])))));
			dsp->fRec26[0] = (fSlow1 + (0.999000013f * dsp->fRec26[1]));
			dsp->fVec1[0] = fSlow4;
			int iTemp0 = ((fSlow4 == dsp->fVec1[1]) | iSlow5);
			dsp->fRec27[0] = ((fSlow3 * (1.0f - (0.999000013f * (float)iTemp0))) + (0.999000013f * ((float)iTemp0 * dsp->fRec27[1])));
			dsp->fRec28[0] = ((fSlow8 * dsp->fRec29[1]) + (fSlow9 * dsp->fRec28[1]));
			dsp->fRec29[0] = (((fSlow9 * dsp->fRec29[1]) + (fSlow10 * dsp->fRec28[1])) + (float)(1 - dsp->iVec0[1]));
			dsp->fRec30[0] = (fSlow12 + (fSlow11 * dsp->fRec30[1]));
			float fTemp1 = ((fSlow2 / (dsp->fRec27[0] * ((fSlow6 * (dsp->fRec28[0] * dsp->fRec30[0])) + 1.0f))) + -0.0799999982f);
			float fTemp2 = (dsp->fConst5 * ((1.0f - dsp->fRec26[0]) * fTemp1));
			float fTemp3 = (fTemp2 + -1.49999499f);
			int iTemp4 = (int)fTemp3;
			int iTemp5 = (int)min(dsp->fConst4, (float)max(0, (int)iTemp4));
			float fTemp6 = floorf(fTemp3);
			float fTemp7 = (fTemp2 + (-1.0f - fTemp6));
			float fTemp8 = (0.0f - fTemp7);
			float fTemp9 = (fTemp2 + (-2.0f - fTemp6));
			float fTemp10 = (0.0f - (0.5f * fTemp9));
			float fTemp11 = (fTemp2 + (-3.0f - fTemp6));
			float fTemp12 = (0.0f - (0.333333343f * fTemp11));
			float fTemp13 = (fTemp2 + (-4.0f - fTemp6));
			float fTemp14 = (0.0f - (0.25f * fTemp13));
			float fTemp15 = (fTemp2 - fTemp6);
			int iTemp16 = (int)min(dsp->fConst4, (float)max(0, (int)(iTemp4 + 2)));
			float fTemp17 = (0.0f - fTemp11);
			float fTemp18 = (0.0f - (0.5f * fTemp13));
			int iTemp19 = (int)min(dsp->fConst4, (float)max(0, (int)(iTemp4 + 1)));
			float fTemp20 = (0.0f - fTemp9);
			float fTemp21 = (0.0f - (0.5f * fTemp11));
			float fTemp22 = (0.0f - (0.333333343f * fTemp13));
			float fTemp23 = (fTemp7 * fTemp9);
			int iTemp24 = (int)min(dsp->fConst4, (float)max(0, (int)(iTemp4 + 3)));
			float fTemp25 = (0.0f - fTemp13);
			float fTemp26 = (fTemp23 * fTemp11);
			int iTemp27 = (int)min(dsp->fConst4, (float)max(0, (int)(iTemp4 + 4)));
			dsp->fRec22[0] = (((((dsp->fRec2[((dsp->IOTA - (iTemp5 + 1)) & 2047)] * fTemp8) * fTemp10) * fTemp12) * fTemp14) + (fTemp15 * ((((0.5f * (((fTemp7 * dsp->fRec2[((dsp->IOTA - (iTemp16 + 1)) & 2047)]) * fTemp17) * fTemp18)) + (((dsp->fRec2[((dsp->IOTA - (iTemp19 + 1)) & 2047)] * fTemp20) * fTemp21) * fTemp22)) + (0.166666672f * ((fTemp23 * dsp->fRec2[((dsp->IOTA - (iTemp24 + 1)) & 2047)]) * fTemp25))) + (0.0416666679f * (fTemp26 * dsp->fRec2[((dsp->IOTA - (iTemp27 + 1)) & 2047)])))));
			dsp->fRec31[0] = dsp->fRec0[1];
			dsp->fRec32[(dsp->IOTA & 2047)] = (0.0f - (0.99880147f * ((0.800000012f * dsp->fRec31[2]) + (0.100000001f * (dsp->fRec31[1] + dsp->fRec31[3])))));
			int iRec33 = 0;
			float fTemp28 = (dsp->fConst5 * (dsp->fRec26[0] * fTemp1));
			float fTemp29 = (fTemp28 + -1.49999499f);
			int iTemp30 = (int)fTemp29;
			int iTemp31 = (int)min(dsp->fConst4, (float)max(0, (int)iTemp30));
			float fTemp32 = floorf(fTemp29);
			float fTemp33 = (fTemp28 + (-1.0f - fTemp32));
			float fTemp34 = (0.0f - fTemp33);
			float fTemp35 = (fTemp28 + (-2.0f - fTemp32));
			float fTemp36 = (0.0f - (0.5f * fTemp35));
			float fTemp37 = (fTemp28 + (-3.0f - fTemp32));
			float fTemp38 = (0.0f - (0.333333343f * fTemp37));
			float fTemp39 = (fTemp28 + (-4.0f - fTemp32));
			float fTemp40 = (0.0f - (0.25f * fTemp39));
			float fTemp41 = (fTemp28 - fTemp32);
			int iTemp42 = (int)min(dsp->fConst4, (float)max(0, (int)(iTemp30 + 2)));
			float fTemp43 = (0.0f - fTemp37);
			float fTemp44 = (0.0f - (0.5f * fTemp39));
			int iTemp45 = (int)min(dsp->fConst4, (float)max(0, (int)(iTemp30 + 1)));
			float fTemp46 = (0.0f - fTemp35);
			float fTemp47 = (0.0f - (0.5f * fTemp37));
			float fTemp48 = (0.0f - (0.333333343f * fTemp39));
			float fTemp49 = (fTemp33 * fTemp35);
			int iTemp50 = (int)min(dsp->fConst4, (float)max(0, (int)(iTemp30 + 3)));
			float fTemp51 = (0.0f - fTemp39);
			float fTemp52 = (fTemp49 * fTemp37);
			int iTemp53 = (int)min(dsp->fConst4, (float)max(0, (int)(iTemp30 + 4)));
			dsp->fVec2[0] = (((((dsp->fRec32[((dsp->IOTA - (iTemp31 + 2)) & 2047)] * fTemp34) * fTemp36) * fTemp38) * fTemp40) + (fTemp41 * ((((0.5f * (((fTemp33 * dsp->fRec32[((dsp->IOTA - (iTemp42 + 2)) & 2047)]) * fTemp43) * fTemp44)) + (((dsp->fRec32[((dsp->IOTA - (iTemp45 + 2)) & 2047)] * fTemp46) * fTemp47) * fTemp48)) + (0.166666672f * ((fTemp49 * dsp->fRec32[((dsp->IOTA - (iTemp50 + 2)) & 2047)]) * fTemp51))) + (0.0416666679f * (fTemp52 * dsp->fRec32[((dsp->IOTA - (iTemp53 + 2)) & 2047)])))));
			float fTemp54 = (dsp->fRec30[0] - (dsp->fRec22[1] + dsp->fVec2[1]));
			dsp->fRec34[0] = (fSlow13 + (0.999000013f * dsp->fRec34[1]));
			float fTemp55 = (fTemp54 * min(1.0f, (1.0f / mydsp_faustpower4_f((fabsf(((5.0f - (4.0f * dsp->fRec34[0])) * fTemp54)) + 0.75f)))));
			float fRec23 = (dsp->fRec22[1] + fTemp55);
			float fTemp56 = (dsp->fVec2[1] + fTemp55);
			dsp->fVec3[(dsp->IOTA & 2047)] = fTemp56;
			float fRec24 = (((((fTemp8 * fTemp10) * fTemp12) * fTemp14) * dsp->fVec3[((dsp->IOTA - iTemp5) & 2047)]) + (fTemp15 * ((0.0416666679f * (fTemp26 * dsp->fVec3[((dsp->IOTA - iTemp27) & 2047)])) + (((((fTemp20 * fTemp21) * fTemp22) * dsp->fVec3[((dsp->IOTA - iTemp19) & 2047)]) + (0.5f * (((fTemp7 * fTemp17) * fTemp18) * dsp->fVec3[((dsp->IOTA - iTemp16) & 2047)]))) + (0.166666672f * ((fTemp23 * fTemp25) * dsp->fVec3[((dsp->IOTA - iTemp24) & 2047)]))))));
			int iRec25 = iRec33;
			dsp->fRec18[(dsp->IOTA & 2047)] = fRec23;
			float fRec19 = (((((fTemp34 * fTemp36) * fTemp38) * fTemp40) * dsp->fRec18[((dsp->IOTA - (iTemp31 + 1)) & 2047)]) + (fTemp41 * (((0.166666672f * ((fTemp49 * fTemp51) * dsp->fRec18[((dsp->IOTA - (iTemp50 + 1)) & 2047)])) + ((((fTemp46 * fTemp47) * fTemp48) * dsp->fRec18[((dsp->IOTA - (iTemp45 + 1)) & 2047)]) + (0.5f * (((fTemp33 * fTemp43) * fTemp44) * dsp->fRec18[((dsp->IOTA - (iTemp42 + 1)) & 2047)])))) + (0.0416666679f * (fTemp52 * dsp->fRec18[((dsp->IOTA - (iTemp53 + 1)) & 2047)])))));
			dsp->fRec20[0] = fRec24;
			int iRec21 = iRec25;
			dsp->fRec16[0] = dsp->fRec20[1];
			int iRec17 = iRec21;
			dsp->fRec14[0] = (dsp->fRec16[1] - (dsp->fConst3 * ((dsp->fConst8 * dsp->fRec14[2]) + (dsp->fConst9 * dsp->fRec14[1]))));
			float fTemp57 = (dsp->fConst3 * ((dsp->fConst2 * dsp->fRec14[0]) + (dsp->fConst10 * dsp->fRec14[2])));
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
			float fTemp58 = (fSlow0 * fRec1);
			output0[i] = (FAUSTFLOAT)fTemp58;
			output1[i] = (FAUSTFLOAT)fTemp58;
			dsp->iRec10[1] = dsp->iRec10[0];
			dsp->iVec0[1] = dsp->iVec0[0];
			dsp->fRec26[1] = dsp->fRec26[0];
			dsp->fVec1[1] = dsp->fVec1[0];
			dsp->fRec27[1] = dsp->fRec27[0];
			dsp->fRec28[1] = dsp->fRec28[0];
			dsp->fRec29[1] = dsp->fRec29[0];
			dsp->fRec30[1] = dsp->fRec30[0];
			dsp->fRec22[1] = dsp->fRec22[0];
			/* C99 loop */
			{
				int j0;
				for (j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
					dsp->fRec31[j0] = dsp->fRec31[(j0 - 1)];
					
				}
				
			}
			dsp->IOTA = (dsp->IOTA + 1);
			dsp->fVec2[1] = dsp->fVec2[0];
			dsp->fRec34[1] = dsp->fRec34[0];
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
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
