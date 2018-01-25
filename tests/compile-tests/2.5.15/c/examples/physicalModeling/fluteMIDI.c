/* ------------------------------------------------------------
copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
license: "MIT"
name: "FluteMIDI"
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
	int iRec15[2];
	int iVec0[2];
	float fRec22[2];
	FAUSTFLOAT fHslider1;
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider2;
	float fRec23[2];
	float fRec24[2];
	FAUSTFLOAT fButton0;
	FAUSTFLOAT fHslider3;
	float fVec1[2];
	FAUSTFLOAT fHslider4;
	float fConst2;
	FAUSTFLOAT fHslider5;
	float fRec25[2];
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	int iRec27[2];
	float fConst7;
	float fConst8;
	float fConst9;
	float fRec26[3];
	float fRec28[2];
	int IOTA;
	float fRec29[2048];
	float fConst10;
	float fConst11;
	FAUSTFLOAT fHslider6;
	FAUSTFLOAT fHslider7;
	float fRec31[2];
	FAUSTFLOAT fHslider8;
	float fRec32[2];
	float fVec2[2];
	float fVec3[2048];
	float fVec4[2];
	float fRec20[2];
	float fRec11[2048];
	float fRec7[2];
	float fRec3[2048];
	float fRec1[2];
	float fRec2[2];
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
	m->declare(m->metaInterface, "description", "Simple MIDI-controllable flute physical model with physical parameters.");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "license", "MIT");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "FluteMIDI");
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
	dsp->fHslider2 = (FAUSTFLOAT)5.0f;
	dsp->fButton0 = (FAUSTFLOAT)0.0f;
	dsp->fHslider3 = (FAUSTFLOAT)0.0f;
	dsp->fHslider4 = (FAUSTFLOAT)0.90000000000000002f;
	dsp->fHslider5 = (FAUSTFLOAT)1.0f;
	dsp->fHslider6 = (FAUSTFLOAT)440.0f;
	dsp->fHslider7 = (FAUSTFLOAT)1.0f;
	dsp->fHslider8 = (FAUSTFLOAT)0.5f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			dsp->iRec15[l0] = 0;
			
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
			dsp->fRec22[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			dsp->fRec23[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			dsp->fRec24[l4] = 0.0f;
			
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
			dsp->fRec25[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			dsp->iRec27[l7] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
			dsp->fRec26[l8] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			dsp->fRec28[l9] = 0.0f;
			
		}
		
	}
	dsp->IOTA = 0;
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 2048); l10 = (l10 + 1)) {
			dsp->fRec29[l10] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			dsp->fRec31[l11] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			dsp->fRec32[l12] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l13;
		for (l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			dsp->fVec2[l13] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l14;
		for (l14 = 0; (l14 < 2048); l14 = (l14 + 1)) {
			dsp->fVec3[l14] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l15;
		for (l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			dsp->fVec4[l15] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l16;
		for (l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			dsp->fRec20[l16] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l17;
		for (l17 = 0; (l17 < 2048); l17 = (l17 + 1)) {
			dsp->fRec11[l17] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l18;
		for (l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			dsp->fRec7[l18] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l19;
		for (l19 = 0; (l19 < 2048); l19 = (l19 + 1)) {
			dsp->fRec3[l19] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l20;
		for (l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			dsp->fRec1[l20] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l21;
		for (l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			dsp->fRec2[l21] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l22;
		for (l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			dsp->fRec0[l22] = 0.0f;
			
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "flute");
	ui_interface->declare(ui_interface->uiInterface, 0, "0", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "midi");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider6, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider6, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "freq", &dsp->fHslider6, 440.0f, 50.0f, 1000.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider7, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider7, "hidden", "1");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider7, "midi", "pitchwheel");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider7, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "bend", &dsp->fHslider7, 1.0f, 0.0f, 10.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "gain", &dsp->fHslider4, 0.899999976f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "envAttack", &dsp->fHslider5, 1.0f, 0.0f, 30.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "4", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "hidden", "1");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "midi", "ctrl 64");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "sustain", &dsp->fHslider3, 0.0f, 0.0f, 1.0f, 1.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "1", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "otherParams");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider8, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider8, "midi", "ctrl 1");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider8, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "mouthPosition", &dsp->fHslider8, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "vibratoFreq", &dsp->fHslider2, 5.0f, 1.0f, 10.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "vibratoGain", &dsp->fHslider1, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "3", "");
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
	float fSlow1 = (0.0399999991f * (float)dsp->fHslider1);
	float fSlow2 = (dsp->fConst1 * (float)dsp->fHslider2);
	float fSlow3 = sinf(fSlow2);
	float fSlow4 = cosf(fSlow2);
	float fSlow5 = (0.0f - fSlow3);
	float fSlow6 = min(1.0f, ((float)dsp->fButton0 + (float)dsp->fHslider3));
	float fSlow7 = expf((0.0f - (dsp->fConst2 / (float)dsp->fHslider5)));
	float fSlow8 = ((fSlow6 * (float)dsp->fHslider4) * (1.0f - fSlow7));
	float fSlow9 = (340.0f / (float)dsp->fHslider6);
	float fSlow10 = (float)dsp->fHslider7;
	int iSlow11 = (fSlow6 == 0.0f);
	float fSlow12 = (0.00100000005f * (float)dsp->fHslider8);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->iRec15[0] = 0;
			dsp->iVec0[0] = 1;
			dsp->fRec22[0] = ((0.699999988f * dsp->fRec22[1]) + (0.284999996f * dsp->fRec20[1]));
			float fRec19 = (dsp->fRec22[0] + (float)dsp->iRec15[1]);
			dsp->fRec23[0] = ((fSlow3 * dsp->fRec24[1]) + (fSlow4 * dsp->fRec23[1]));
			dsp->fRec24[0] = (((fSlow4 * dsp->fRec24[1]) + (fSlow5 * dsp->fRec23[1])) + (float)(1 - dsp->iVec0[1]));
			dsp->fVec1[0] = fSlow6;
			dsp->fRec25[0] = (fSlow8 + (fSlow7 * dsp->fRec25[1]));
			dsp->iRec27[0] = ((1103515245 * dsp->iRec27[1]) + 12345);
			dsp->fRec26[0] = ((4.65661287e-10f * (float)dsp->iRec27[0]) - (dsp->fConst7 * ((dsp->fConst8 * dsp->fRec26[1]) + (dsp->fConst9 * dsp->fRec26[2]))));
			dsp->fRec28[0] = dsp->fRec1[1];
			dsp->fRec29[(dsp->IOTA & 2047)] = (0.949999988f * dsp->fRec28[1]);
			int iRec30 = 0;
			int iTemp0 = ((fSlow6 == dsp->fVec1[1]) | iSlow11);
			dsp->fRec31[0] = ((fSlow10 * (1.0f - (0.999000013f * (float)iTemp0))) + (0.999000013f * ((float)iTemp0 * dsp->fRec31[1])));
			float fTemp1 = ((fSlow9 / dsp->fRec31[0]) + 0.270000011f);
			dsp->fRec32[0] = (fSlow12 + (0.999000013f * dsp->fRec32[1]));
			float fTemp2 = (0.400000006f * (dsp->fRec32[0] + -0.5f));
			float fTemp3 = (dsp->fConst11 * (fTemp1 * (fTemp2 + 0.270000011f)));
			float fTemp4 = (fTemp3 + -1.49999499f);
			int iTemp5 = (int)fTemp4;
			int iTemp6 = ((int)min(dsp->fConst10, (float)max(0, (int)iTemp5)) + 1);
			float fTemp7 = floorf(fTemp4);
			float fTemp8 = (fTemp3 + (-1.0f - fTemp7));
			float fTemp9 = (0.0f - fTemp8);
			float fTemp10 = (fTemp3 + (-2.0f - fTemp7));
			float fTemp11 = (0.0f - (0.5f * fTemp10));
			float fTemp12 = (fTemp3 + (-3.0f - fTemp7));
			float fTemp13 = (0.0f - (0.333333343f * fTemp12));
			float fTemp14 = (fTemp3 + (-4.0f - fTemp7));
			float fTemp15 = (0.0f - (0.25f * fTemp14));
			float fTemp16 = (fTemp3 - fTemp7);
			int iTemp17 = ((int)min(dsp->fConst10, (float)max(0, (int)(iTemp5 + 2))) + 1);
			float fTemp18 = (0.0f - fTemp12);
			float fTemp19 = (0.0f - (0.5f * fTemp14));
			int iTemp20 = ((int)min(dsp->fConst10, (float)max(0, (int)(iTemp5 + 1))) + 1);
			float fTemp21 = (0.0f - fTemp10);
			float fTemp22 = (0.0f - (0.5f * fTemp12));
			float fTemp23 = (0.0f - (0.333333343f * fTemp14));
			float fTemp24 = (fTemp8 * fTemp10);
			int iTemp25 = ((int)min(dsp->fConst10, (float)max(0, (int)(iTemp5 + 3))) + 1);
			float fTemp26 = (0.0f - fTemp14);
			float fTemp27 = (fTemp24 * fTemp12);
			int iTemp28 = ((int)min(dsp->fConst10, (float)max(0, (int)(iTemp5 + 4))) + 1);
			dsp->fVec2[0] = (((((dsp->fRec29[((dsp->IOTA - iTemp6) & 2047)] * fTemp9) * fTemp11) * fTemp13) * fTemp15) + (fTemp16 * ((((0.5f * (((fTemp8 * dsp->fRec29[((dsp->IOTA - iTemp17) & 2047)]) * fTemp18) * fTemp19)) + (((dsp->fRec29[((dsp->IOTA - iTemp20) & 2047)] * fTemp21) * fTemp22) * fTemp23)) + (0.166666672f * ((fTemp24 * dsp->fRec29[((dsp->IOTA - iTemp25) & 2047)]) * fTemp26))) + (0.0416666679f * (fTemp27 * dsp->fRec29[((dsp->IOTA - iTemp28) & 2047)])))));
			float fTemp29 = (((fSlow1 * dsp->fRec23[0]) + (dsp->fRec25[0] * ((dsp->fConst6 * (dsp->fRec26[2] + (dsp->fRec26[0] + (2.0f * dsp->fRec26[1])))) + 1.0f))) - (0.5f * dsp->fVec2[1]));
			float fTemp30 = ((0.5f * dsp->fRec7[1]) + max(-1.0f, min(1.0f, (fTemp29 * (mydsp_faustpower2_f(fTemp29) + -1.0f)))));
			dsp->fVec3[(dsp->IOTA & 2047)] = fTemp30;
			float fTemp31 = (dsp->fConst11 * (fTemp1 * (0.730000019f - fTemp2)));
			float fTemp32 = (fTemp31 + -1.49999499f);
			int iTemp33 = (int)fTemp32;
			int iTemp34 = ((int)min(dsp->fConst10, (float)max(0, (int)iTemp33)) + 1);
			float fTemp35 = floorf(fTemp32);
			float fTemp36 = (fTemp31 + (-1.0f - fTemp35));
			float fTemp37 = (0.0f - fTemp36);
			float fTemp38 = (fTemp31 + (-2.0f - fTemp35));
			float fTemp39 = (0.0f - (0.5f * fTemp38));
			float fTemp40 = (fTemp31 + (-3.0f - fTemp35));
			float fTemp41 = (0.0f - (0.333333343f * fTemp40));
			float fTemp42 = (fTemp31 + (-4.0f - fTemp35));
			float fTemp43 = (0.0f - (0.25f * fTemp42));
			float fTemp44 = (fTemp31 - fTemp35);
			int iTemp45 = ((int)min(dsp->fConst10, (float)max(0, (int)(iTemp33 + 2))) + 1);
			float fTemp46 = (0.0f - fTemp40);
			float fTemp47 = (0.0f - (0.5f * fTemp42));
			int iTemp48 = ((int)min(dsp->fConst10, (float)max(0, (int)(iTemp33 + 1))) + 1);
			float fTemp49 = (0.0f - fTemp38);
			float fTemp50 = (0.0f - (0.5f * fTemp40));
			float fTemp51 = (0.0f - (0.333333343f * fTemp42));
			float fTemp52 = (fTemp36 * fTemp38);
			int iTemp53 = ((int)min(dsp->fConst10, (float)max(0, (int)(iTemp33 + 3))) + 1);
			float fTemp54 = (0.0f - fTemp42);
			float fTemp55 = (fTemp52 * fTemp40);
			int iTemp56 = ((int)min(dsp->fConst10, (float)max(0, (int)(iTemp33 + 4))) + 1);
			dsp->fVec4[0] = (((((dsp->fVec3[((dsp->IOTA - iTemp34) & 2047)] * fTemp37) * fTemp39) * fTemp41) * fTemp43) + (fTemp44 * ((((0.5f * (((fTemp36 * dsp->fVec3[((dsp->IOTA - iTemp45) & 2047)]) * fTemp46) * fTemp47)) + (((dsp->fVec3[((dsp->IOTA - iTemp48) & 2047)] * fTemp49) * fTemp50) * fTemp51)) + (0.166666672f * ((fTemp52 * dsp->fVec3[((dsp->IOTA - iTemp53) & 2047)]) * fTemp54))) + (0.0416666679f * (fTemp55 * dsp->fVec3[((dsp->IOTA - iTemp56) & 2047)])))));
			dsp->fRec20[0] = dsp->fVec4[1];
			int iRec21 = iRec30;
			float fRec16 = fRec19;
			float fRec17 = dsp->fRec20[0];
			float fRec18 = (dsp->fRec20[0] + (float)iRec21);
			dsp->fRec11[(dsp->IOTA & 2047)] = fRec16;
			float fRec12 = (((((fTemp37 * fTemp39) * fTemp41) * fTemp43) * dsp->fRec11[((dsp->IOTA - iTemp34) & 2047)]) + (fTemp44 * (((0.166666672f * ((fTemp52 * fTemp54) * dsp->fRec11[((dsp->IOTA - iTemp53) & 2047)])) + ((((fTemp49 * fTemp50) * fTemp51) * dsp->fRec11[((dsp->IOTA - iTemp48) & 2047)]) + (0.5f * (((fTemp36 * fTemp46) * fTemp47) * dsp->fRec11[((dsp->IOTA - iTemp45) & 2047)])))) + (0.0416666679f * (fTemp55 * dsp->fRec11[((dsp->IOTA - iTemp56) & 2047)])))));
			float fRec13 = fRec17;
			float fRec14 = fRec18;
			dsp->fRec7[0] = fRec12;
			float fRec8 = dsp->fRec7[1];
			float fRec9 = fRec13;
			float fRec10 = fRec14;
			dsp->fRec3[(dsp->IOTA & 2047)] = fRec8;
			float fRec4 = (((((fTemp9 * fTemp11) * fTemp13) * fTemp15) * dsp->fRec3[((dsp->IOTA - iTemp6) & 2047)]) + (fTemp16 * (((0.166666672f * ((fTemp24 * fTemp26) * dsp->fRec3[((dsp->IOTA - iTemp25) & 2047)])) + ((((fTemp21 * fTemp22) * fTemp23) * dsp->fRec3[((dsp->IOTA - iTemp20) & 2047)]) + (0.5f * (((fTemp8 * fTemp18) * fTemp19) * dsp->fRec3[((dsp->IOTA - iTemp17) & 2047)])))) + (0.0416666679f * (fTemp27 * dsp->fRec3[((dsp->IOTA - iTemp28) & 2047)])))));
			float fRec5 = fRec9;
			float fRec6 = fRec10;
			dsp->fRec1[0] = fRec4;
			dsp->fRec2[0] = fRec6;
			dsp->fRec0[0] = ((dsp->fRec2[0] + (0.995000005f * dsp->fRec0[1])) - dsp->fRec2[1]);
			float fTemp57 = (fSlow0 * dsp->fRec0[0]);
			output0[i] = (FAUSTFLOAT)fTemp57;
			output1[i] = (FAUSTFLOAT)fTemp57;
			dsp->iRec15[1] = dsp->iRec15[0];
			dsp->iVec0[1] = dsp->iVec0[0];
			dsp->fRec22[1] = dsp->fRec22[0];
			dsp->fRec23[1] = dsp->fRec23[0];
			dsp->fRec24[1] = dsp->fRec24[0];
			dsp->fVec1[1] = dsp->fVec1[0];
			dsp->fRec25[1] = dsp->fRec25[0];
			dsp->iRec27[1] = dsp->iRec27[0];
			dsp->fRec26[2] = dsp->fRec26[1];
			dsp->fRec26[1] = dsp->fRec26[0];
			dsp->fRec28[1] = dsp->fRec28[0];
			dsp->IOTA = (dsp->IOTA + 1);
			dsp->fRec31[1] = dsp->fRec31[0];
			dsp->fRec32[1] = dsp->fRec32[0];
			dsp->fVec2[1] = dsp->fVec2[0];
			dsp->fVec4[1] = dsp->fVec4[0];
			dsp->fRec20[1] = dsp->fRec20[0];
			dsp->fRec7[1] = dsp->fRec7[0];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec0[1] = dsp->fRec0[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
