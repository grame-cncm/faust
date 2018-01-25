/* ------------------------------------------------------------
copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
license: "MIT"
name: "ClarinetMIDI"
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
	float fRec13[2];
	FAUSTFLOAT fHslider2;
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider3;
	float fRec17[2];
	float fRec18[2];
	FAUSTFLOAT fButton0;
	FAUSTFLOAT fHslider4;
	float fVec1[2];
	FAUSTFLOAT fHslider5;
	float fConst2;
	FAUSTFLOAT fHslider6;
	float fRec19[2];
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	int iRec21[2];
	float fConst7;
	float fConst8;
	float fConst9;
	float fRec20[3];
	float fRec14[2];
	FAUSTFLOAT fHslider7;
	int IOTA;
	float fRec15[2048];
	float fConst10;
	float fConst11;
	FAUSTFLOAT fHslider8;
	FAUSTFLOAT fHslider9;
	float fRec22[2];
	float fVec2[2];
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
	m->declare(m->metaInterface, "description", "Simple MIDI-controllable clarinet physical model with physical parameters.");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "license", "MIT");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "ClarinetMIDI");
	m->declare(m->metaInterface, "noises.lib/name", "Faust Noise Generator Library");
	m->declare(m->metaInterface, "noises.lib/version", "0.0");
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
	dsp->fHslider2 = (FAUSTFLOAT)0.25f;
	dsp->fHslider3 = (FAUSTFLOAT)5.0f;
	dsp->fButton0 = (FAUSTFLOAT)0.0f;
	dsp->fHslider4 = (FAUSTFLOAT)0.0f;
	dsp->fHslider5 = (FAUSTFLOAT)0.59999999999999998f;
	dsp->fHslider6 = (FAUSTFLOAT)1.0f;
	dsp->fHslider7 = (FAUSTFLOAT)0.5f;
	dsp->fHslider8 = (FAUSTFLOAT)440.0f;
	dsp->fHslider9 = (FAUSTFLOAT)1.0f;
	
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
			dsp->fRec13[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			dsp->fRec17[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			dsp->fRec18[l4] = 0.0f;
			
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
			dsp->fRec19[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			dsp->iRec21[l7] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
			dsp->fRec20[l8] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			dsp->fRec14[l9] = 0.0f;
			
		}
		
	}
	dsp->IOTA = 0;
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 2048); l10 = (l10 + 1)) {
			dsp->fRec15[l10] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			dsp->fRec22[l11] = 0.0f;
			
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
			dsp->fRec11[l13] = 0.0f;
			
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
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = (6.28318548f / dsp->fConst0);
	dsp->fConst2 = (1000.0f / dsp->fConst0);
	dsp->fConst3 = tanf((6283.18555f / dsp->fConst0));
	dsp->fConst4 = (1.0f / dsp->fConst3);
	dsp->fConst5 = (((dsp->fConst4 + 1.41421354f) / dsp->fConst3) + 1.0f);
	dsp->fConst6 = (0.0500000007f / dsp->fConst5);
	dsp->fConst7 = (1.0f / dsp->fConst5);
	dsp->fConst8 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(dsp->fConst3))));
	dsp->fConst9 = (((dsp->fConst4 + -1.41421354f) / dsp->fConst3) + 1.0f);
	dsp->fConst10 = (0.00882352982f * dsp->fConst0);
	dsp->fConst11 = (0.00147058826f * dsp->fConst0);
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "clarinet");
	ui_interface->declare(ui_interface->uiInterface, 0, "0", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "midi");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider8, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider8, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "freq", &dsp->fHslider8, 440.0f, 50.0f, 1000.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider9, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider9, "hidden", "1");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider9, "midi", "pitchwheel");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider9, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "bend", &dsp->fHslider9, 1.0f, 0.0f, 10.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "gain", &dsp->fHslider5, 0.600000024f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider6, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider6, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "envAttack", &dsp->fHslider6, 1.0f, 0.0f, 30.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "4", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "hidden", "1");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "midi", "ctrl 64");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "sustain", &dsp->fHslider4, 0.0f, 0.0f, 1.0f, 1.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "1", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "otherParams");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider7, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider7, "midi", "ctrl 1");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider7, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "reedStiffness", &dsp->fHslider7, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "midi", "ctrl 3");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "bellOpening", &dsp->fHslider1, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "vibratoFreq", &dsp->fHslider3, 5.0f, 1.0f, 10.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "vibratoGain", &dsp->fHslider2, 0.25f, 0.0f, 1.0f, 0.00999999978f);
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
	float fSlow1 = (float)dsp->fHslider1;
	float fSlow2 = (1.0f - fSlow1);
	float fSlow3 = (0.00999999978f * (float)dsp->fHslider2);
	float fSlow4 = (dsp->fConst1 * (float)dsp->fHslider3);
	float fSlow5 = sinf(fSlow4);
	float fSlow6 = cosf(fSlow4);
	float fSlow7 = (0.0f - fSlow5);
	float fSlow8 = min(1.0f, ((float)dsp->fButton0 + (float)dsp->fHslider4));
	float fSlow9 = expf((0.0f - (dsp->fConst2 / (float)dsp->fHslider6)));
	float fSlow10 = ((fSlow8 * (float)dsp->fHslider5) * (1.0f - fSlow9));
	float fSlow11 = ((0.25999999f * (float)dsp->fHslider7) + -0.439999998f);
	float fSlow12 = (170.0f / (float)dsp->fHslider8);
	float fSlow13 = (float)dsp->fHslider9;
	int iSlow14 = (fSlow8 == 0.0f);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->iRec6[0] = 0;
			dsp->iVec0[0] = 1;
			dsp->fRec13[0] = ((fSlow1 * dsp->fRec13[1]) + (fSlow2 * dsp->fRec11[1]));
			float fRec10 = (dsp->fRec13[0] + (float)dsp->iRec6[1]);
			dsp->fRec17[0] = ((fSlow5 * dsp->fRec18[1]) + (fSlow6 * dsp->fRec17[1]));
			dsp->fRec18[0] = (((fSlow6 * dsp->fRec18[1]) + (fSlow7 * dsp->fRec17[1])) + (float)(1 - dsp->iVec0[1]));
			float fTemp0 = (fSlow3 * dsp->fRec17[0]);
			dsp->fVec1[0] = fSlow8;
			dsp->fRec19[0] = (fSlow10 + (fSlow9 * dsp->fRec19[1]));
			dsp->iRec21[0] = ((1103515245 * dsp->iRec21[1]) + 12345);
			dsp->fRec20[0] = ((4.65661287e-10f * (float)dsp->iRec21[0]) - (dsp->fConst7 * ((dsp->fConst8 * dsp->fRec20[1]) + (dsp->fConst9 * dsp->fRec20[2]))));
			float fTemp1 = (dsp->fRec19[0] * ((dsp->fConst6 * (dsp->fRec20[2] + (dsp->fRec20[0] + (2.0f * dsp->fRec20[1])))) + 1.0f));
			dsp->fRec14[0] = ((dsp->fRec0[1] + fTemp0) + fTemp1);
			float fTemp2 = (0.0f - dsp->fRec14[1]);
			dsp->fRec15[(dsp->IOTA & 2047)] = ((fTemp0 + fTemp1) + (fTemp2 * max(-1.0f, min(1.0f, ((fSlow11 * fTemp2) + 0.699999988f)))));
			int iRec16 = 0;
			int iTemp3 = ((fSlow8 == dsp->fVec1[1]) | iSlow14);
			dsp->fRec22[0] = ((fSlow13 * (1.0f - (0.999000013f * (float)iTemp3))) + (0.999000013f * ((float)iTemp3 * dsp->fRec22[1])));
			float fTemp4 = (dsp->fConst11 * ((fSlow12 / (dsp->fRec22[0] * ((fSlow3 * (dsp->fRec19[0] * dsp->fRec17[0])) + 1.0f))) + -0.0500000007f));
			float fTemp5 = (fTemp4 + -1.49999499f);
			int iTemp6 = (int)fTemp5;
			int iTemp7 = ((int)min(dsp->fConst10, (float)max(0, (int)iTemp6)) + 1);
			float fTemp8 = floorf(fTemp5);
			float fTemp9 = (fTemp4 + (-1.0f - fTemp8));
			float fTemp10 = (0.0f - fTemp9);
			float fTemp11 = (fTemp4 + (-2.0f - fTemp8));
			float fTemp12 = (0.0f - (0.5f * fTemp11));
			float fTemp13 = (fTemp4 + (-3.0f - fTemp8));
			float fTemp14 = (0.0f - (0.333333343f * fTemp13));
			float fTemp15 = (fTemp4 + (-4.0f - fTemp8));
			float fTemp16 = (0.0f - (0.25f * fTemp15));
			float fTemp17 = (fTemp4 - fTemp8);
			int iTemp18 = ((int)min(dsp->fConst10, (float)max(0, (int)(iTemp6 + 2))) + 1);
			float fTemp19 = (0.0f - fTemp13);
			float fTemp20 = (0.0f - (0.5f * fTemp15));
			int iTemp21 = ((int)min(dsp->fConst10, (float)max(0, (int)(iTemp6 + 1))) + 1);
			float fTemp22 = (0.0f - fTemp11);
			float fTemp23 = (0.0f - (0.5f * fTemp13));
			float fTemp24 = (0.0f - (0.333333343f * fTemp15));
			float fTemp25 = (fTemp9 * fTemp11);
			int iTemp26 = ((int)min(dsp->fConst10, (float)max(0, (int)(iTemp6 + 3))) + 1);
			float fTemp27 = (0.0f - fTemp15);
			float fTemp28 = (fTemp25 * fTemp13);
			int iTemp29 = ((int)min(dsp->fConst10, (float)max(0, (int)(iTemp6 + 4))) + 1);
			dsp->fVec2[0] = (((((dsp->fRec15[((dsp->IOTA - iTemp7) & 2047)] * fTemp10) * fTemp12) * fTemp14) * fTemp16) + (fTemp17 * ((((0.5f * (((fTemp9 * dsp->fRec15[((dsp->IOTA - iTemp18) & 2047)]) * fTemp19) * fTemp20)) + (((dsp->fRec15[((dsp->IOTA - iTemp21) & 2047)] * fTemp22) * fTemp23) * fTemp24)) + (0.166666672f * ((fTemp25 * dsp->fRec15[((dsp->IOTA - iTemp26) & 2047)]) * fTemp27))) + (0.0416666679f * (fTemp28 * dsp->fRec15[((dsp->IOTA - iTemp29) & 2047)])))));
			dsp->fRec11[0] = dsp->fVec2[1];
			int iRec12 = iRec16;
			float fRec7 = fRec10;
			float fRec8 = dsp->fRec11[0];
			float fRec9 = (dsp->fRec11[0] + (float)iRec12);
			dsp->fRec2[(dsp->IOTA & 2047)] = fRec7;
			float fRec3 = (((((fTemp10 * fTemp12) * fTemp14) * fTemp16) * dsp->fRec2[((dsp->IOTA - iTemp7) & 2047)]) + (fTemp17 * (((0.166666672f * ((fTemp25 * fTemp27) * dsp->fRec2[((dsp->IOTA - iTemp26) & 2047)])) + ((((fTemp22 * fTemp23) * fTemp24) * dsp->fRec2[((dsp->IOTA - iTemp21) & 2047)]) + (0.5f * (((fTemp9 * fTemp19) * fTemp20) * dsp->fRec2[((dsp->IOTA - iTemp18) & 2047)])))) + (0.0416666679f * (fTemp28 * dsp->fRec2[((dsp->IOTA - iTemp29) & 2047)])))));
			float fRec4 = fRec8;
			float fRec5 = fRec9;
			dsp->fRec0[0] = fRec3;
			float fRec1 = fRec5;
			float fTemp30 = (fSlow0 * fRec1);
			output0[i] = (FAUSTFLOAT)fTemp30;
			output1[i] = (FAUSTFLOAT)fTemp30;
			dsp->iRec6[1] = dsp->iRec6[0];
			dsp->iVec0[1] = dsp->iVec0[0];
			dsp->fRec13[1] = dsp->fRec13[0];
			dsp->fRec17[1] = dsp->fRec17[0];
			dsp->fRec18[1] = dsp->fRec18[0];
			dsp->fVec1[1] = dsp->fVec1[0];
			dsp->fRec19[1] = dsp->fRec19[0];
			dsp->iRec21[1] = dsp->iRec21[0];
			dsp->fRec20[2] = dsp->fRec20[1];
			dsp->fRec20[1] = dsp->fRec20[0];
			dsp->fRec14[1] = dsp->fRec14[0];
			dsp->IOTA = (dsp->IOTA + 1);
			dsp->fRec22[1] = dsp->fRec22[0];
			dsp->fVec2[1] = dsp->fVec2[0];
			dsp->fRec11[1] = dsp->fRec11[0];
			dsp->fRec0[1] = dsp->fRec0[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
