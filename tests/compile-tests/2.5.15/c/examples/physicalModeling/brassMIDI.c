/* ------------------------------------------------------------
copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
license: "MIT"
name: "BrassMIDI"
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
	
	FAUSTFLOAT fHslider0;
	int iRec6[2];
	FAUSTFLOAT fHslider1;
	int iVec0[2];
	float fRec14[2];
	float fRec13[2];
	float fRec15[2];
	FAUSTFLOAT fButton0;
	FAUSTFLOAT fHslider2;
	float fVec1[2];
	FAUSTFLOAT fHslider3;
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider4;
	float fRec20[2];
	FAUSTFLOAT fHslider5;
	float fConst2;
	FAUSTFLOAT fHslider6;
	float fRec21[2];
	float fRec22[2];
	FAUSTFLOAT fHslider7;
	FAUSTFLOAT fHslider8;
	float fRec23[2];
	FAUSTFLOAT fHslider9;
	float fRec24[2];
	float fRec19[3];
	float fVec2[2];
	float fRec18[2];
	int IOTA;
	float fRec16[2048];
	float fConst3;
	float fConst4;
	float fVec3[2];
	float fRec11[2];
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
	m->declare(m->metaInterface, "description", "Simple MIDI-controllable brass instrument physical model with physical parameters.");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "license", "MIT");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "BrassMIDI");
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
	dsp->fHslider1 = (FAUSTFLOAT)0.5f;
	dsp->fButton0 = (FAUSTFLOAT)0.0f;
	dsp->fHslider2 = (FAUSTFLOAT)0.0f;
	dsp->fHslider3 = (FAUSTFLOAT)0.5f;
	dsp->fHslider4 = (FAUSTFLOAT)1.0f;
	dsp->fHslider5 = (FAUSTFLOAT)0.5f;
	dsp->fHslider6 = (FAUSTFLOAT)5.0f;
	dsp->fHslider7 = (FAUSTFLOAT)440.0f;
	dsp->fHslider8 = (FAUSTFLOAT)1.0f;
	dsp->fHslider9 = (FAUSTFLOAT)0.5f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			dsp->iRec6[l0] = 0;
			
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
			dsp->fRec14[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			dsp->fRec13[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			dsp->fRec15[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			dsp->fVec1[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			dsp->fRec20[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			dsp->fRec21[l7] = 0.0f;
			
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
		for (l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			dsp->fRec23[l9] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			dsp->fRec24[l10] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 3); l11 = (l11 + 1)) {
			dsp->fRec19[l11] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			dsp->fVec2[l12] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l13;
		for (l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			dsp->fRec18[l13] = 0.0f;
			
		}
		
	}
	dsp->IOTA = 0;
	/* C99 loop */
	{
		int l14;
		for (l14 = 0; (l14 < 2048); l14 = (l14 + 1)) {
			dsp->fRec16[l14] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l15;
		for (l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			dsp->fVec3[l15] = 0.0f;
			
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
		for (l17 = 0; (l17 < 2048); l17 = (l17 + 1)) {
			dsp->fRec2[l17] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l18;
		for (l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			dsp->fRec0[l18] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = (1000.0f / dsp->fConst0);
	dsp->fConst2 = (6.28318548f / dsp->fConst0);
	dsp->fConst3 = (0.00882352982f * dsp->fConst0);
	dsp->fConst4 = (0.5f * dsp->fConst0);
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "brass");
	ui_interface->declare(ui_interface->uiInterface, 0, "0", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "midi");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider7, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider7, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "freq", &dsp->fHslider7, 440.0f, 50.0f, 1000.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider8, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider8, "hidden", "1");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider8, "midi", "pitchwheel");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider8, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "bend", &dsp->fHslider8, 1.0f, 0.0f, 10.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "gain", &dsp->fHslider3, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "envAttack", &dsp->fHslider4, 1.0f, 0.0f, 30.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "4", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "hidden", "1");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "midi", "ctrl 64");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "sustain", &dsp->fHslider2, 0.0f, 0.0f, 1.0f, 1.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "1", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "otherParams");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider9, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider9, "midi", "ctrl 1");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider9, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "lipsTension", &dsp->fHslider9, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "mute", &dsp->fHslider1, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider6, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider6, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "vibratoFreq", &dsp->fHslider6, 5.0f, 1.0f, 10.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "vibratoGain", &dsp->fHslider5, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "4", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "outGain", &dsp->fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fButton0, "2", "");
	ui_interface->addButton(ui_interface->uiInterface, "gate", &dsp->fButton0);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	float fSlow0 = (float)dsp->fHslider0;
	float fSlow1 = (0.00100000005f * (float)dsp->fHslider1);
	float fSlow2 = min(1.0f, ((float)dsp->fButton0 + (float)dsp->fHslider2));
	float fSlow3 = expf((0.0f - (dsp->fConst1 / (float)dsp->fHslider4)));
	float fSlow4 = ((fSlow2 * (float)dsp->fHslider3) * (1.0f - fSlow3));
	float fSlow5 = (0.0399999991f * (float)dsp->fHslider5);
	float fSlow6 = (dsp->fConst2 * (float)dsp->fHslider6);
	float fSlow7 = sinf(fSlow6);
	float fSlow8 = cosf(fSlow6);
	float fSlow9 = (0.0f - fSlow7);
	float fSlow10 = (float)dsp->fHslider7;
	float fSlow11 = (dsp->fConst2 * fSlow10);
	int iSlow12 = (fSlow2 == 0.0f);
	float fSlow13 = (float)dsp->fHslider8;
	float fSlow14 = (0.00100000005f * (float)dsp->fHslider9);
	float fSlow15 = (dsp->fConst4 / fSlow10);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->iRec6[0] = 0;
			dsp->iVec0[0] = 1;
			dsp->fRec14[0] = (fSlow1 + (0.999000013f * dsp->fRec14[1]));
			dsp->fRec13[0] = ((dsp->fRec14[0] * dsp->fRec13[1]) + ((1.0f - dsp->fRec14[0]) * dsp->fRec11[1]));
			float fRec10 = (dsp->fRec13[0] + (float)dsp->iRec6[1]);
			dsp->fRec15[0] = dsp->fRec0[1];
			dsp->fVec1[0] = fSlow2;
			dsp->fRec20[0] = (fSlow4 + (fSlow3 * dsp->fRec20[1]));
			dsp->fRec21[0] = ((fSlow7 * dsp->fRec22[1]) + (fSlow8 * dsp->fRec21[1]));
			dsp->fRec22[0] = (((fSlow8 * dsp->fRec22[1]) + (fSlow9 * dsp->fRec21[1])) + (float)(1 - dsp->iVec0[1]));
			float fTemp0 = (dsp->fRec20[0] * ((fSlow5 * (dsp->fRec20[0] * dsp->fRec21[0])) + 1.0f));
			int iTemp1 = ((fSlow2 == dsp->fVec1[1]) | iSlow12);
			dsp->fRec23[0] = ((0.999000013f * (dsp->fRec23[1] * (float)iTemp1)) + (fSlow13 * (1.0f - (0.999000013f * (float)iTemp1))));
			dsp->fRec24[0] = (fSlow14 + (0.999000013f * dsp->fRec24[1]));
			dsp->fRec19[0] = ((0.0299999993f * ((0.300000012f * fTemp0) - (0.850000024f * dsp->fRec15[1]))) - ((dsp->fRec19[1] * (0.0f - (1.99399996f * cosf((fSlow11 * (dsp->fRec23[0] * powf(4.0f, ((2.0f * dsp->fRec24[0]) + -1.0f)))))))) + (0.994009018f * dsp->fRec19[2])));
			float fTemp2 = max(-1.0f, min(1.0f, mydsp_faustpower2_f(dsp->fRec19[0])));
			float fTemp3 = (0.850000024f * (dsp->fRec15[1] * (1.0f - fTemp2)));
			float fTemp4 = (0.300000012f * (fTemp0 * fTemp2));
			dsp->fVec2[0] = (fTemp4 + fTemp3);
			dsp->fRec18[0] = ((fTemp3 + ((0.995000005f * dsp->fRec18[1]) + fTemp4)) - dsp->fVec2[1]);
			dsp->fRec16[(dsp->IOTA & 2047)] = dsp->fRec18[0];
			int iRec17 = 0;
			float fTemp5 = (fSlow15 / dsp->fRec23[0]);
			float fTemp6 = (fTemp5 + -1.49999499f);
			int iTemp7 = (int)fTemp6;
			int iTemp8 = ((int)min(dsp->fConst3, (float)max(0, (int)iTemp7)) + 1);
			float fTemp9 = floorf(fTemp6);
			float fTemp10 = (fTemp5 + (-1.0f - fTemp9));
			float fTemp11 = (0.0f - fTemp10);
			float fTemp12 = (fTemp5 + (-2.0f - fTemp9));
			float fTemp13 = (0.0f - (0.5f * fTemp12));
			float fTemp14 = (fTemp5 + (-3.0f - fTemp9));
			float fTemp15 = (0.0f - (0.333333343f * fTemp14));
			float fTemp16 = (fTemp5 + (-4.0f - fTemp9));
			float fTemp17 = (0.0f - (0.25f * fTemp16));
			float fTemp18 = (fTemp5 - fTemp9);
			int iTemp19 = ((int)min(dsp->fConst3, (float)max(0, (int)(iTemp7 + 2))) + 1);
			float fTemp20 = (0.0f - fTemp14);
			float fTemp21 = (0.0f - (0.5f * fTemp16));
			int iTemp22 = ((int)min(dsp->fConst3, (float)max(0, (int)(iTemp7 + 1))) + 1);
			float fTemp23 = (0.0f - fTemp12);
			float fTemp24 = (0.0f - (0.5f * fTemp14));
			float fTemp25 = (0.0f - (0.333333343f * fTemp16));
			float fTemp26 = (fTemp10 * fTemp12);
			int iTemp27 = ((int)min(dsp->fConst3, (float)max(0, (int)(iTemp7 + 3))) + 1);
			float fTemp28 = (0.0f - fTemp16);
			float fTemp29 = (fTemp26 * fTemp14);
			int iTemp30 = ((int)min(dsp->fConst3, (float)max(0, (int)(iTemp7 + 4))) + 1);
			dsp->fVec3[0] = (((((dsp->fRec16[((dsp->IOTA - iTemp8) & 2047)] * fTemp11) * fTemp13) * fTemp15) * fTemp17) + (fTemp18 * ((((0.5f * (((fTemp10 * dsp->fRec16[((dsp->IOTA - iTemp19) & 2047)]) * fTemp20) * fTemp21)) + (((dsp->fRec16[((dsp->IOTA - iTemp22) & 2047)] * fTemp23) * fTemp24) * fTemp25)) + (0.166666672f * ((fTemp26 * dsp->fRec16[((dsp->IOTA - iTemp27) & 2047)]) * fTemp28))) + (0.0416666679f * (fTemp29 * dsp->fRec16[((dsp->IOTA - iTemp30) & 2047)])))));
			dsp->fRec11[0] = dsp->fVec3[1];
			int iRec12 = iRec17;
			float fRec7 = fRec10;
			float fRec8 = dsp->fRec11[0];
			float fRec9 = (dsp->fRec11[0] + (float)iRec12);
			dsp->fRec2[(dsp->IOTA & 2047)] = fRec7;
			float fRec3 = (((((fTemp11 * fTemp13) * fTemp15) * fTemp17) * dsp->fRec2[((dsp->IOTA - iTemp8) & 2047)]) + (fTemp18 * (((0.166666672f * ((fTemp26 * fTemp28) * dsp->fRec2[((dsp->IOTA - iTemp27) & 2047)])) + ((((fTemp23 * fTemp24) * fTemp25) * dsp->fRec2[((dsp->IOTA - iTemp22) & 2047)]) + (0.5f * (((fTemp10 * fTemp20) * fTemp21) * dsp->fRec2[((dsp->IOTA - iTemp19) & 2047)])))) + (0.0416666679f * (fTemp29 * dsp->fRec2[((dsp->IOTA - iTemp30) & 2047)])))));
			float fRec4 = fRec8;
			float fRec5 = fRec9;
			dsp->fRec0[0] = fRec3;
			float fRec1 = fRec5;
			float fTemp31 = (fSlow0 * fRec1);
			output0[i] = (FAUSTFLOAT)fTemp31;
			output1[i] = (FAUSTFLOAT)fTemp31;
			dsp->iRec6[1] = dsp->iRec6[0];
			dsp->iVec0[1] = dsp->iVec0[0];
			dsp->fRec14[1] = dsp->fRec14[0];
			dsp->fRec13[1] = dsp->fRec13[0];
			dsp->fRec15[1] = dsp->fRec15[0];
			dsp->fVec1[1] = dsp->fVec1[0];
			dsp->fRec20[1] = dsp->fRec20[0];
			dsp->fRec21[1] = dsp->fRec21[0];
			dsp->fRec22[1] = dsp->fRec22[0];
			dsp->fRec23[1] = dsp->fRec23[0];
			dsp->fRec24[1] = dsp->fRec24[0];
			dsp->fRec19[2] = dsp->fRec19[1];
			dsp->fRec19[1] = dsp->fRec19[0];
			dsp->fVec2[1] = dsp->fVec2[0];
			dsp->fRec18[1] = dsp->fRec18[0];
			dsp->IOTA = (dsp->IOTA + 1);
			dsp->fVec3[1] = dsp->fVec3[0];
			dsp->fRec11[1] = dsp->fRec11[0];
			dsp->fRec0[1] = dsp->fRec0[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
