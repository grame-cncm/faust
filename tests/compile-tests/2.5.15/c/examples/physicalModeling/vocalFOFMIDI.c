/* ------------------------------------------------------------
copyright: "(c)Mike Olsen, CCRMA (Stanford University)"
license: "MIT"
name: "Vocal FOF MIDI"
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


typedef struct {
	
	int iRec11[2];
	
} mydspSIG0;

static mydspSIG0* newmydspSIG0() { return (mydspSIG0*)malloc(sizeof(mydspSIG0)); }
static void deletemydspSIG0(mydspSIG0* dsp) { free(dsp); }

int getNumInputsmydspSIG0(mydspSIG0* dsp) {
	return 0;
	
}
int getNumOutputsmydspSIG0(mydspSIG0* dsp) {
	return 1;
	
}
int getInputRatemydspSIG0(mydspSIG0* dsp, int channel) {
	int rate;
	switch (channel) {
		default: {
			rate = -1;
			break;
		}
		
	}
	return rate;
	
}
int getOutputRatemydspSIG0(mydspSIG0* dsp, int channel) {
	int rate;
	switch (channel) {
		case 0: {
			rate = 0;
			break;
		}
		default: {
			rate = -1;
			break;
		}
		
	}
	return rate;
	
}

static void instanceInitmydspSIG0(mydspSIG0* dsp, int samplingFreq) {
	/* C99 loop */
	{
		int l15;
		for (l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			dsp->iRec11[l15] = 0;
			
		}
		
	}
	
}

static void fillmydspSIG0(mydspSIG0* dsp, int count, float* output) {
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->iRec11[0] = (dsp->iRec11[1] + 1);
			output[i] = sinf((9.58738019e-05f * (float)(dsp->iRec11[0] + -1)));
			dsp->iRec11[1] = dsp->iRec11[0];
			
		}
		
	}
	
};

static float ftbl0mydspSIG0[65536];

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif
#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

typedef struct {
	
	FAUSTFLOAT fHslider0;
	int iVec0[2];
	FAUSTFLOAT fButton0;
	FAUSTFLOAT fHslider1;
	float fVec1[2];
	FAUSTFLOAT fHslider2;
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider3;
	float fRec0[2];
	float fConst2;
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT fHslider5;
	float fRec3[2];
	FAUSTFLOAT fHslider6;
	float fConst3;
	FAUSTFLOAT fHslider7;
	float fRec4[2];
	float fRec5[2];
	float fVec2[2];
	float fRec2[2];
	int iVec3[2];
	float fConst4;
	float fConst5;
	float fConst6;
	FAUSTFLOAT fHslider8;
	float fRec7[2];
	FAUSTFLOAT fHslider9;
	float fRec8[2];
	float fRec9[2];
	float fRec6[2];
	float fRec10[2];
	float fRec1[3];
	float fConst7;
	float fRec13[2];
	float fRec12[2];
	float fRec15[2];
	float fRec16[2];
	float fRec14[3];
	float fRec17[2];
	float fRec19[2];
	float fRec20[2];
	float fRec18[3];
	float fRec21[2];
	float fRec23[2];
	float fRec24[2];
	float fRec22[3];
	float fRec25[2];
	float fRec27[2];
	float fRec28[2];
	float fRec26[3];
	float fRec29[2];
	
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
	m->declare(m->metaInterface, "copyright", "(c)Mike Olsen, CCRMA (Stanford University)");
	m->declare(m->metaInterface, "description", "MIDI-controllable FOF vocal synthesizer.");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "license", "MIT");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "Vocal FOF MIDI");
	m->declare(m->metaInterface, "noises.lib/name", "Faust Noise Generator Library");
	m->declare(m->metaInterface, "noises.lib/version", "0.0");
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
	mydspSIG0* sig0 = newmydspSIG0();
	instanceInitmydspSIG0(sig0, samplingFreq);
	fillmydspSIG0(sig0, 65536, ftbl0mydspSIG0);
	deletemydspSIG0(sig0);
	
}

void instanceResetUserInterfacemydsp(mydsp* dsp) {
	dsp->fHslider0 = (FAUSTFLOAT)0.5f;
	dsp->fButton0 = (FAUSTFLOAT)0.0f;
	dsp->fHslider1 = (FAUSTFLOAT)0.0f;
	dsp->fHslider2 = (FAUSTFLOAT)0.90000000000000002f;
	dsp->fHslider3 = (FAUSTFLOAT)10.0f;
	dsp->fHslider4 = (FAUSTFLOAT)440.0f;
	dsp->fHslider5 = (FAUSTFLOAT)1.0f;
	dsp->fHslider6 = (FAUSTFLOAT)0.5f;
	dsp->fHslider7 = (FAUSTFLOAT)6.0f;
	dsp->fHslider8 = (FAUSTFLOAT)0.0f;
	dsp->fHslider9 = (FAUSTFLOAT)0.0f;
	
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
			dsp->fRec4[l4] = 0.0f;
			
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
			dsp->fVec2[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			dsp->fRec2[l7] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			dsp->iVec3[l8] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			dsp->fRec7[l9] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			dsp->fRec8[l10] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			dsp->fRec9[l11] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			dsp->fRec6[l12] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l13;
		for (l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			dsp->fRec10[l13] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l14;
		for (l14 = 0; (l14 < 3); l14 = (l14 + 1)) {
			dsp->fRec1[l14] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l16;
		for (l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			dsp->fRec13[l16] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l17;
		for (l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			dsp->fRec12[l17] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l18;
		for (l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			dsp->fRec15[l18] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l19;
		for (l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			dsp->fRec16[l19] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l20;
		for (l20 = 0; (l20 < 3); l20 = (l20 + 1)) {
			dsp->fRec14[l20] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l21;
		for (l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			dsp->fRec17[l21] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l22;
		for (l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			dsp->fRec19[l22] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l23;
		for (l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			dsp->fRec20[l23] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l24;
		for (l24 = 0; (l24 < 3); l24 = (l24 + 1)) {
			dsp->fRec18[l24] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l25;
		for (l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			dsp->fRec21[l25] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l26;
		for (l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			dsp->fRec23[l26] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l27;
		for (l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			dsp->fRec24[l27] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l28;
		for (l28 = 0; (l28 < 3); l28 = (l28 + 1)) {
			dsp->fRec22[l28] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l29;
		for (l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			dsp->fRec25[l29] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l30;
		for (l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			dsp->fRec27[l30] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l31;
		for (l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			dsp->fRec28[l31] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l32;
		for (l32 = 0; (l32 < 3); l32 = (l32 + 1)) {
			dsp->fRec26[l32] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l33;
		for (l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			dsp->fRec29[l33] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = (1000.0f / dsp->fConst0);
	dsp->fConst2 = (1.0f / dsp->fConst0);
	dsp->fConst3 = (6.28318548f / dsp->fConst0);
	dsp->fConst4 = (3.14159274f / dsp->fConst0);
	dsp->fConst5 = expf((0.0f - dsp->fConst1));
	dsp->fConst6 = (1.0f - dsp->fConst5);
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "vocal");
	ui_interface->declare(ui_interface->uiInterface, 0, "0", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "midi");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "freq", &dsp->fHslider4, 440.0f, 50.0f, 1000.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "hidden", "1");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "midi", "pitchwheel");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "bend", &dsp->fHslider5, 1.0f, 0.0f, 10.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "gain", &dsp->fHslider2, 0.899999976f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "envAttack", &dsp->fHslider3, 10.0f, 0.0f, 30.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "4", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "hidden", "1");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "midi", "ctrl 64");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "sustain", &dsp->fHslider1, 0.0f, 0.0f, 1.0f, 1.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "1", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "otherParams");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider9, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider9, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "voiceType", &dsp->fHslider9, 0.0f, 0.0f, 4.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider8, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider8, "midi", "ctrl 1");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider8, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "vowel", &dsp->fHslider8, 0.0f, 0.0f, 4.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider7, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider7, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "vibratoFreq", &dsp->fHslider7, 6.0f, 1.0f, 10.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider6, "4", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider6, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "vibratoGain", &dsp->fHslider6, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "5", "");
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
	float fSlow1 = min(1.0f, ((float)dsp->fButton0 + (float)dsp->fHslider1));
	float fSlow2 = expf((0.0f - (dsp->fConst1 / (float)dsp->fHslider3)));
	float fSlow3 = (25.0f * ((fSlow1 * (float)dsp->fHslider2) * (1.0f - fSlow2)));
	float fSlow4 = (float)dsp->fHslider4;
	int iSlow5 = (fSlow1 == 0.0f);
	float fSlow6 = (float)dsp->fHslider5;
	float fSlow7 = (0.100000001f * (float)dsp->fHslider6);
	float fSlow8 = (dsp->fConst3 * (float)dsp->fHslider7);
	float fSlow9 = sinf(fSlow8);
	float fSlow10 = cosf(fSlow8);
	float fSlow11 = (0.0f - fSlow9);
	float fSlow12 = (0.00100000005f * (float)dsp->fHslider8);
	float fSlow13 = (float)dsp->fHslider9;
	int iSlow14 = ((fSlow13 == 0.0f)?1:((fSlow13 == 3.0f)?1:0));
	int iSlow15 = (5 * iSlow14);
	int iSlow16 = (iSlow14 >= 1);
	float fSlow17 = (iSlow16?174.610001f:82.4100037f);
	float fSlow18 = (iSlow16?1046.5f:523.25f);
	float fSlow19 = (fSlow18 - fSlow17);
	float fSlow20 = (5.0f * fSlow13);
	float fSlow21 = (5.0f * (1.0f - fSlow13));
	int iSlow22 = (iSlow14 == 0);
	int iSlow23 = (fSlow13 != 2.0f);
	float fSlow24 = (2.0f * fSlow4);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->iVec0[0] = 1;
			dsp->fVec1[0] = fSlow1;
			dsp->fRec0[0] = (fSlow3 + (fSlow2 * dsp->fRec0[1]));
			int iTemp0 = ((fSlow1 == dsp->fVec1[1]) | iSlow5);
			dsp->fRec3[0] = ((0.999000013f * (dsp->fRec3[1] * (float)iTemp0)) + (fSlow6 * (1.0f - (0.999000013f * (float)iTemp0))));
			dsp->fRec4[0] = ((fSlow9 * dsp->fRec5[1]) + (fSlow10 * dsp->fRec4[1]));
			int iTemp1 = (1 - dsp->iVec0[1]);
			dsp->fRec5[0] = (((fSlow10 * dsp->fRec5[1]) + (fSlow11 * dsp->fRec4[1])) + (float)iTemp1);
			float fTemp2 = (dsp->fRec3[0] * ((fSlow7 * dsp->fRec4[0]) + 1.0f));
			float fTemp3 = (fSlow4 * fTemp2);
			dsp->fVec2[0] = fTemp3;
			float fTemp4 = (dsp->fRec2[1] + (dsp->fConst2 * dsp->fVec2[1]));
			dsp->fRec2[0] = (fTemp4 - floorf(fTemp4));
			int iTemp5 = ((dsp->fRec2[0] - dsp->fRec2[1]) < 0.0f);
			dsp->iVec3[0] = iTemp5;
			dsp->fRec7[0] = (fSlow12 + (0.999000013f * dsp->fRec7[1]));
			float fTemp6 = (dsp->fRec7[0] + (float)iSlow15);
			int iTemp7 = (fTemp6 >= 5.0f);
			int iTemp8 = (fTemp6 >= 3.0f);
			int iTemp9 = (fTemp6 >= 2.0f);
			int iTemp10 = (fTemp6 >= 1.0f);
			int iTemp11 = (fTemp6 >= 4.0f);
			int iTemp12 = (fTemp6 >= 8.0f);
			int iTemp13 = (fTemp6 >= 7.0f);
			int iTemp14 = (fTemp6 >= 6.0f);
			float fTemp15 = (iTemp7?(iTemp12?2.0f:(iTemp13?3.0f:(iTemp14?3.0f:2.0f))):(iTemp8?(iTemp11?1.5f:1.0f):(iTemp9?1.25f:(iTemp10?1.25f:1.0f))));
			dsp->fRec8[0] = ((fSlow9 * dsp->fRec9[1]) + (fSlow10 * dsp->fRec8[1]));
			dsp->fRec9[0] = (((fSlow10 * dsp->fRec9[1]) + (fSlow11 * dsp->fRec8[1])) + (float)iTemp1);
			float fTemp16 = (fSlow4 * (dsp->fRec3[0] * ((fSlow7 * dsp->fRec8[0]) + 1.0f)));
			float fTemp17 = (fTemp15 + (((iTemp7?(iTemp12?12.0f:(iTemp13?12.0f:(iTemp14?12.0f:15.0f))):(iTemp8?(iTemp11?4.0f:10.0f):(iTemp9?2.5f:(iTemp10?2.5f:10.0f)))) - fTemp15) * ((fTemp16 <= fSlow17)?0.0f:((fTemp16 >= fSlow18)?1.0f:((fTemp16 - fSlow17) / fSlow19)))));
			float fTemp18 = (fSlow20 + dsp->fRec7[0]);
			int iTemp19 = (fTemp18 < 23.0f);
			int iTemp20 = (fTemp18 < 24.0f);
			float fTemp21 = (fSlow20 + (dsp->fRec7[0] + -23.0f));
			int iTemp22 = (fTemp18 < 22.0f);
			float fTemp23 = (fSlow20 + (dsp->fRec7[0] + -22.0f));
			int iTemp24 = (fTemp18 < 21.0f);
			float fTemp25 = (fSlow20 + (dsp->fRec7[0] + -21.0f));
			int iTemp26 = (fTemp18 < 20.0f);
			float fTemp27 = (fSlow20 + (dsp->fRec7[0] + -20.0f));
			float fTemp28 = (20.0f * fTemp27);
			int iTemp29 = (fTemp18 < 19.0f);
			int iTemp30 = (fTemp18 < 18.0f);
			float fTemp31 = (fSlow20 + (dsp->fRec7[0] + -18.0f));
			int iTemp32 = (fTemp18 < 17.0f);
			float fTemp33 = (fSlow20 + (dsp->fRec7[0] + -17.0f));
			int iTemp34 = (fTemp18 < 16.0f);
			int iTemp35 = (fTemp18 < 15.0f);
			float fTemp36 = (fSlow20 + (dsp->fRec7[0] + -15.0f));
			float fTemp37 = (20.0f * fTemp36);
			int iTemp38 = (fTemp18 < 14.0f);
			float fTemp39 = (fSlow20 + (dsp->fRec7[0] + -14.0f));
			int iTemp40 = (fTemp18 < 13.0f);
			int iTemp41 = (fTemp18 < 12.0f);
			int iTemp42 = (fTemp18 < 11.0f);
			float fTemp43 = (fSlow20 + (dsp->fRec7[0] + -11.0f));
			int iTemp44 = (fTemp18 < 10.0f);
			float fTemp45 = (fSlow20 + (dsp->fRec7[0] + -10.0f));
			float fTemp46 = (10.0f * fTemp45);
			int iTemp47 = (fTemp18 < 9.0f);
			float fTemp48 = (fSlow20 + (dsp->fRec7[0] + -9.0f));
			int iTemp49 = (fTemp18 < 8.0f);
			int iTemp50 = (fTemp18 < 7.0f);
			float fTemp51 = (fSlow20 + (dsp->fRec7[0] + -7.0f));
			int iTemp52 = (fTemp18 < 6.0f);
			float fTemp53 = (fSlow20 + (dsp->fRec7[0] + -6.0f));
			int iTemp54 = (fTemp18 < 5.0f);
			float fTemp55 = (dsp->fRec7[0] - fSlow21);
			int iTemp56 = (fTemp18 < 4.0f);
			float fTemp57 = (fSlow20 + (dsp->fRec7[0] + -4.0f));
			float fTemp58 = (10.0f * fTemp57);
			int iTemp59 = (fTemp18 < 3.0f);
			float fTemp60 = (fSlow20 + (dsp->fRec7[0] + -3.0f));
			float fTemp61 = (20.0f * fTemp60);
			int iTemp62 = (fTemp18 < 2.0f);
			float fTemp63 = (fSlow20 + (dsp->fRec7[0] + -2.0f));
			float fTemp64 = (20.0f * fTemp63);
			int iTemp65 = (fTemp18 < 1.0f);
			float fTemp66 = (fSlow20 + (dsp->fRec7[0] + -1.0f));
			int iTemp67 = (fTemp18 < 0.0f);
			float fTemp68 = (20.0f * fTemp18);
			float fTemp69 = (iTemp19?(iTemp22?(iTemp24?(iTemp26?(iTemp29?(iTemp30?(iTemp32?(iTemp34?(iTemp35?(iTemp38?(iTemp40?(iTemp41?(iTemp42?(iTemp44?(iTemp47?(iTemp49?(iTemp50?(iTemp52?(iTemp54?(iTemp56?(iTemp59?(iTemp62?(iTemp65?(iTemp67?80.0f:(iTemp65?(80.0f - fTemp68):60.0f)):(iTemp62?(60.0f - (10.0f * fTemp66)):50.0f)):(iTemp59?(fTemp64 + 50.0f):70.0f)):(iTemp56?(70.0f - fTemp61):50.0f)):(iTemp54?(fTemp58 + 50.0f):60.0f)):(iTemp52?(60.0f - (20.0f * fTemp55)):40.0f)):(iTemp50?((20.0f * fTemp53) + 40.0f):60.0f)):(iTemp49?(60.0f - (20.0f * fTemp51)):40.0f)):40.0f):(iTemp44?(40.0f * (fTemp48 + 1.0f)):80.0f)):(iTemp42?(80.0f - fTemp46):70.0f)):(iTemp41?(70.0f - (30.0f * fTemp43)):40.0f)):40.0f):40.0f):(iTemp35?(40.0f * (fTemp39 + 1.0f)):80.0f)):(iTemp34?(80.0f - fTemp37):60.0f)):60.0f):(iTemp30?(60.0f - (20.0f * fTemp33)):40.0f)):(iTemp29?((10.0f * fTemp31) + 40.0f):50.0f)):50.0f):(iTemp24?(fTemp28 + 50.0f):70.0f)):(iTemp22?(70.0f - (30.0f * fTemp25)):40.0f)):(iTemp19?((30.0f * fTemp23) + 40.0f):70.0f)):(iTemp20?(70.0f - (30.0f * fTemp21)):40.0f));
			dsp->fRec6[0] = ((dsp->fConst5 * dsp->fRec6[1]) + (dsp->fConst6 * (fTemp17 * fTemp69)));
			float fTemp70 = expf((dsp->fConst4 * (0.0f - dsp->fRec6[0])));
			dsp->fRec10[0] = ((dsp->fConst5 * dsp->fRec10[1]) + (dsp->fConst6 * fTemp69));
			float fTemp71 = expf((dsp->fConst4 * (0.0f - dsp->fRec10[0])));
			dsp->fRec1[0] = ((float)dsp->iVec3[1] - ((dsp->fRec1[1] * (0.0f - (fTemp70 + fTemp71))) + ((fTemp70 * fTemp71) * dsp->fRec1[2])));
			float fTemp72 = ((0.000839999993f * (1000.0f - fTemp16)) + 0.800000012f);
			float fTemp73 = ((0.00366666657f * (400.0f - fTemp16)) + 3.0f);
			int iTemp74 = (1 - (iTemp5 > 0));
			dsp->fRec13[0] = (fSlow12 + (0.999000013f * dsp->fRec13[1]));
			float fTemp75 = (fSlow20 + dsp->fRec13[0]);
			int iTemp76 = (fTemp75 < 23.0f);
			int iTemp77 = (fTemp75 < 24.0f);
			float fTemp78 = (fSlow20 + (dsp->fRec13[0] + -23.0f));
			int iTemp79 = (fTemp75 < 22.0f);
			float fTemp80 = (fSlow20 + (dsp->fRec13[0] + -22.0f));
			int iTemp81 = (fTemp75 < 21.0f);
			float fTemp82 = (fSlow20 + (dsp->fRec13[0] + -21.0f));
			int iTemp83 = (fTemp75 < 20.0f);
			float fTemp84 = (fSlow20 + (dsp->fRec13[0] + -20.0f));
			int iTemp85 = (fTemp75 < 19.0f);
			float fTemp86 = (fSlow20 + (dsp->fRec13[0] + -19.0f));
			int iTemp87 = (fTemp75 < 18.0f);
			float fTemp88 = (fSlow20 + (dsp->fRec13[0] + -18.0f));
			int iTemp89 = (fTemp75 < 17.0f);
			float fTemp90 = (fSlow20 + (dsp->fRec13[0] + -17.0f));
			int iTemp91 = (fTemp75 < 16.0f);
			float fTemp92 = (fSlow20 + (dsp->fRec13[0] + -16.0f));
			int iTemp93 = (fTemp75 < 15.0f);
			float fTemp94 = (fSlow20 + (dsp->fRec13[0] + -15.0f));
			int iTemp95 = (fTemp75 < 14.0f);
			float fTemp96 = (fSlow20 + (dsp->fRec13[0] + -14.0f));
			int iTemp97 = (fTemp75 < 13.0f);
			float fTemp98 = (fSlow20 + (dsp->fRec13[0] + -13.0f));
			int iTemp99 = (fTemp75 < 12.0f);
			float fTemp100 = (fSlow20 + (dsp->fRec13[0] + -12.0f));
			int iTemp101 = (fTemp75 < 11.0f);
			float fTemp102 = (fSlow20 + (dsp->fRec13[0] + -11.0f));
			int iTemp103 = (fTemp75 < 10.0f);
			float fTemp104 = (fSlow20 + (dsp->fRec13[0] + -10.0f));
			int iTemp105 = (fTemp75 < 9.0f);
			float fTemp106 = (fSlow20 + (dsp->fRec13[0] + -9.0f));
			int iTemp107 = (fTemp75 < 8.0f);
			float fTemp108 = (fSlow20 + (dsp->fRec13[0] + -8.0f));
			float fTemp109 = (50.0f * fTemp108);
			int iTemp110 = (fTemp75 < 7.0f);
			float fTemp111 = (fSlow20 + (dsp->fRec13[0] + -7.0f));
			int iTemp112 = (fTemp75 < 6.0f);
			float fTemp113 = (fSlow20 + (dsp->fRec13[0] + -6.0f));
			int iTemp114 = (fTemp75 < 5.0f);
			float fTemp115 = (dsp->fRec13[0] - fSlow21);
			int iTemp116 = (fTemp75 < 4.0f);
			float fTemp117 = (fSlow20 + (dsp->fRec13[0] + -4.0f));
			int iTemp118 = (fTemp75 < 3.0f);
			float fTemp119 = (fSlow20 + (dsp->fRec13[0] + -3.0f));
			int iTemp120 = (fTemp75 < 2.0f);
			float fTemp121 = (fSlow20 + (dsp->fRec13[0] + -2.0f));
			int iTemp122 = (fTemp75 < 1.0f);
			float fTemp123 = (fSlow20 + (dsp->fRec13[0] + -1.0f));
			int iTemp124 = (fTemp75 < 0.0f);
			float fTemp125 = (iTemp76?(iTemp79?(iTemp81?(iTemp83?(iTemp85?(iTemp87?(iTemp89?(iTemp91?(iTemp93?(iTemp95?(iTemp97?(iTemp99?(iTemp101?(iTemp103?(iTemp105?(iTemp107?(iTemp110?(iTemp112?(iTemp114?(iTemp116?(iTemp118?(iTemp120?(iTemp122?(iTemp124?800.0f:(iTemp122?(800.0f - (400.0f * fTemp75)):400.0f)):(iTemp120?(400.0f - (50.0f * fTemp123)):350.0f)):(iTemp118?((100.0f * fTemp121) + 350.0f):450.0f)):(iTemp116?(450.0f - (125.0f * fTemp119)):325.0f)):(iTemp114?((275.0f * fTemp117) + 325.0f):600.0f)):(iTemp112?(600.0f - (200.0f * fTemp115)):400.0f)):(iTemp110?(400.0f - (150.0f * fTemp113)):250.0f)):(iTemp107?((150.0f * fTemp111) + 250.0f):400.0f)):(iTemp105?(400.0f - fTemp109):350.0f)):(iTemp103?((310.0f * fTemp106) + 350.0f):660.0f)):(iTemp101?(660.0f - (220.0f * fTemp104)):440.0f)):(iTemp99?(440.0f - (170.0f * fTemp102)):270.0f)):(iTemp97?((160.0f * fTemp100) + 270.0f):430.0f)):(iTemp95?(430.0f - (60.0f * fTemp98)):370.0f)):(iTemp93?((430.0f * fTemp96) + 370.0f):800.0f)):(iTemp91?(800.0f - (450.0f * fTemp94)):350.0f)):(iTemp89?(350.0f - (80.0f * fTemp92)):270.0f)):(iTemp87?((180.0f * fTemp90) + 270.0f):450.0f)):(iTemp85?(450.0f - (125.0f * fTemp88)):325.0f)):(iTemp83?(325.0f * (fTemp86 + 1.0f)):650.0f)):(iTemp81?(650.0f - (250.0f * fTemp84)):400.0f)):(iTemp79?(400.0f - (110.0f * fTemp82)):290.0f)):(iTemp76?((110.0f * fTemp80) + 290.0f):400.0f)):(iTemp77?(400.0f - (50.0f * fTemp78)):350.0f));
			float fTemp126 = ((dsp->fRec12[1] * (float)iTemp74) + (dsp->fConst7 * ((fTemp125 <= fTemp3)?fTemp3:fTemp125)));
			dsp->fRec12[0] = (fTemp126 - floorf(fTemp126));
			float fTemp127 = (10.0f * fTemp23);
			float fTemp128 = (10.0f * fTemp27);
			float fTemp129 = (fSlow20 + (dsp->fRec7[0] + -19.0f));
			float fTemp130 = (fSlow20 + (dsp->fRec7[0] + -16.0f));
			float fTemp131 = (fSlow20 + (dsp->fRec7[0] + -13.0f));
			float fTemp132 = (fSlow20 + (dsp->fRec7[0] + -12.0f));
			float fTemp133 = (10.0f * fTemp48);
			float fTemp134 = (10.0f * fTemp55);
			float fTemp135 = (iTemp19?(iTemp22?(iTemp24?(iTemp26?(iTemp29?(iTemp30?(iTemp32?(iTemp34?(iTemp35?(iTemp38?(iTemp40?(iTemp41?(iTemp42?(iTemp44?(iTemp47?(iTemp49?(iTemp50?(iTemp52?(iTemp54?(iTemp56?(iTemp59?(iTemp62?(iTemp65?(iTemp67?90.0f:(iTemp65?(90.0f - (10.0f * fTemp18)):80.0f)):(iTemp62?((20.0f * fTemp66) + 80.0f):100.0f)):(iTemp59?(100.0f - fTemp64):80.0f)):(iTemp56?(80.0f - fTemp61):60.0f)):(iTemp54?(fTemp58 + 60.0f):70.0f)):(iTemp52?(fTemp134 + 70.0f):80.0f)):(iTemp50?((10.0f * fTemp53) + 80.0f):90.0f)):(iTemp49?(90.0f - (10.0f * fTemp51)):80.0f)):80.0f):(iTemp44?(fTemp133 + 80.0f):90.0f)):(iTemp42?(90.0f - fTemp46):80.0f)):(iTemp41?((10.0f * fTemp43) + 80.0f):90.0f)):(iTemp40?(90.0f - (10.0f * fTemp132)):80.0f)):(iTemp38?(80.0f - (20.0f * fTemp131)):60.0f)):(iTemp35?((30.0f * fTemp39) + 60.0f):90.0f)):(iTemp34?((10.0f * fTemp36) + 90.0f):100.0f)):(iTemp32?(100.0f - (10.0f * fTemp130)):90.0f)):(iTemp30?(90.0f - (10.0f * fTemp33)):80.0f)):(iTemp29?(80.0f - (20.0f * fTemp31)):60.0f)):(iTemp26?((30.0f * fTemp129) + 60.0f):90.0f)):(iTemp24?(90.0f - fTemp128):80.0f)):(iTemp22?((10.0f * fTemp25) + 80.0f):90.0f)):(iTemp19?(90.0f - fTemp127):80.0f)):(iTemp20?(80.0f - (20.0f * fTemp21)):60.0f));
			dsp->fRec15[0] = ((dsp->fConst5 * dsp->fRec15[1]) + (dsp->fConst6 * (fTemp17 * fTemp135)));
			float fTemp136 = expf((dsp->fConst4 * (0.0f - dsp->fRec15[0])));
			dsp->fRec16[0] = ((dsp->fConst5 * dsp->fRec16[1]) + (dsp->fConst6 * fTemp135));
			float fTemp137 = expf((dsp->fConst4 * (0.0f - dsp->fRec16[0])));
			dsp->fRec14[0] = ((float)dsp->iVec3[1] - ((dsp->fRec14[1] * (0.0f - (fTemp136 + fTemp137))) + ((fTemp136 * fTemp137) * dsp->fRec14[2])));
			float fTemp138 = (fSlow20 + (dsp->fRec7[0] + -8.0f));
			float fTemp139 = (iTemp19?(iTemp22?(iTemp24?(iTemp26?(iTemp29?(iTemp30?(iTemp32?(iTemp34?(iTemp35?(iTemp38?(iTemp40?(iTemp41?(iTemp42?(iTemp44?(iTemp47?(iTemp49?(iTemp50?(iTemp52?(iTemp54?(iTemp56?(iTemp59?(iTemp62?(iTemp65?(iTemp67?0.630957007f:(iTemp65?(0.630957007f - (0.567861021f * fTemp18)):0.0630960017f)):(iTemp62?((0.0369039997f * fTemp66) + 0.0630960017f):0.100000001f)):(iTemp59?((0.254812986f * fTemp63) + 0.100000001f):0.35481301f)):(iTemp56?(0.35481301f - (0.103624001f * fTemp60)):0.251188993f)):(iTemp54?((0.195494995f * fTemp57) + 0.251188993f):0.446684003f)):(iTemp52?(0.446684003f - (0.195494995f * fTemp55)):0.251188993f)):(iTemp50?(0.251188993f - (0.219566002f * fTemp53)):0.0316229984f)):(iTemp49?((0.250214994f * fTemp51) + 0.0316229984f):0.281838f)):(iTemp47?(0.281838f - (0.181838006f * fTemp138)):0.100000001f)):(iTemp44?((0.401187003f * fTemp48) + 0.100000001f):0.501187027f)):(iTemp42?(0.501187027f - (0.301661015f * fTemp45)):0.199525997f)):(iTemp41?(0.199525997f - (0.136429995f * fTemp43)):0.0630960017f)):(iTemp40?((0.253131986f * fTemp132) + 0.0630960017f):0.316228002f)):(iTemp38?(0.316228002f - (0.216227993f * fTemp131)):0.100000001f)):(iTemp35?((0.401187003f * fTemp39) + 0.100000001f):0.501187027f)):(iTemp34?(0.501187027f - (0.401187003f * fTemp36)):0.100000001f)):(iTemp32?((0.151188999f * fTemp130) + 0.100000001f):0.251188993f)):(iTemp30?((0.0306490008f * fTemp33) + 0.251188993f):0.281838f)):(iTemp29?(0.281838f - (0.123349003f * fTemp31)):0.158489004f)):(iTemp26?((0.342698008f * fTemp129) + 0.158489004f):0.501187027f)):(iTemp24?(0.501187027f - (0.301661015f * fTemp27)):0.199525997f)):(iTemp22?(0.199525997f - (0.0216979999f * fTemp25)):0.177827999f)):(iTemp19?((0.138400003f * fTemp23) + 0.177827999f):0.316228002f)):(iTemp20?(0.316228002f - (0.216227993f * fTemp21)):0.100000001f));
			float fTemp140 = (iTemp76?(iTemp79?(iTemp81?(iTemp83?(iTemp85?(iTemp87?(iTemp89?(iTemp91?(iTemp93?(iTemp95?(iTemp97?(iTemp99?(iTemp101?(iTemp103?(iTemp105?(iTemp107?(iTemp110?(iTemp112?(iTemp114?(iTemp116?(iTemp118?(iTemp120?(iTemp122?(iTemp124?1150.0f:(iTemp122?((450.0f * fTemp75) + 1150.0f):1600.0f)):(iTemp120?((100.0f * fTemp123) + 1600.0f):1700.0f)):(iTemp118?(1700.0f - (900.0f * fTemp121)):800.0f)):(iTemp116?(800.0f - (100.0f * fTemp119)):700.0f)):(iTemp114?((340.0f * fTemp117) + 700.0f):1040.0f)):(iTemp112?((580.0f * fTemp115) + 1040.0f):1620.0f)):(iTemp110?((130.0f * fTemp113) + 1620.0f):1750.0f)):(iTemp107?(1750.0f - (1000.0f * fTemp111)):750.0f)):(iTemp105?(750.0f - (150.0f * fTemp108)):600.0f)):(iTemp103?((520.0f * fTemp106) + 600.0f):1120.0f)):(iTemp101?((680.0f * fTemp104) + 1120.0f):1800.0f)):(iTemp99?((50.0f * fTemp102) + 1800.0f):1850.0f)):(iTemp97?(1850.0f - (1030.0f * fTemp100)):820.0f)):(iTemp95?(820.0f - (190.0f * fTemp98)):630.0f)):(iTemp93?((520.0f * fTemp96) + 630.0f):1150.0f)):(iTemp91?((850.0f * fTemp94) + 1150.0f):2000.0f)):(iTemp89?((140.0f * fTemp92) + 2000.0f):2140.0f)):(iTemp87?(2140.0f - (1340.0f * fTemp90)):800.0f)):(iTemp85?(800.0f - (100.0f * fTemp88)):700.0f)):(iTemp83?((380.0f * fTemp86) + 700.0f):1080.0f)):(iTemp81?((620.0f * fTemp84) + 1080.0f):1700.0f)):(iTemp79?((170.0f * fTemp82) + 1700.0f):1870.0f)):(iTemp76?(1870.0f - (1070.0f * fTemp80)):800.0f)):(iTemp77?(800.0f - (200.0f * fTemp78)):600.0f));
			float fTemp141 = ((fSlow24 * fTemp2) + 30.0f);
			float fTemp142 = (((float)iTemp74 * dsp->fRec17[1]) + (dsp->fConst7 * (iSlow23?(((fTemp140 >= 1300.0f) & (fTemp3 >= 200.0f))?(fTemp140 - (0.000952380942f * ((fTemp3 + -200.0f) * (fTemp140 + -1300.0f)))):((fTemp140 <= fTemp141)?fTemp141:fTemp140)):fTemp140)));
			dsp->fRec17[0] = (fTemp142 - floorf(fTemp142));
			float fTemp143 = (50.0f * fTemp129);
			float fTemp144 = (20.0f * fTemp39);
			float fTemp145 = (20.0f * fTemp45);
			float fTemp146 = (20.0f * fTemp48);
			float fTemp147 = (60.0f * fTemp57);
			float fTemp148 = (iTemp19?(iTemp22?(iTemp24?(iTemp26?(iTemp29?(iTemp30?(iTemp32?(iTemp34?(iTemp35?(iTemp38?(iTemp40?(iTemp41?(iTemp42?(iTemp44?(iTemp47?(iTemp49?(iTemp50?(iTemp52?(iTemp54?(iTemp56?(iTemp59?(iTemp62?120.0f:(iTemp59?(120.0f - fTemp64):100.0f)):(iTemp56?((70.0f * fTemp60) + 100.0f):170.0f)):(iTemp54?(170.0f - fTemp147):110.0f)):(iTemp52?(110.0f - fTemp134):100.0f)):100.0f):100.0f):100.0f):(iTemp44?(fTemp146 + 100.0f):120.0f)):(iTemp42?(120.0f - fTemp145):100.0f)):100.0f):100.0f):100.0f):(iTemp35?(fTemp144 + 100.0f):120.0f)):120.0f):(iTemp32?(120.0f - (20.0f * fTemp130)):100.0f)):100.0f):(iTemp29?((70.0f * fTemp31) + 100.0f):170.0f)):(iTemp26?(170.0f - fTemp143):120.0f)):(iTemp24?(120.0f - fTemp28):100.0f)):100.0f):100.0f):100.0f);
			dsp->fRec19[0] = ((dsp->fConst5 * dsp->fRec19[1]) + (dsp->fConst6 * (fTemp17 * fTemp148)));
			float fTemp149 = expf((dsp->fConst4 * (0.0f - dsp->fRec19[0])));
			dsp->fRec20[0] = ((dsp->fConst5 * dsp->fRec20[1]) + (dsp->fConst6 * fTemp148));
			float fTemp150 = expf((dsp->fConst4 * (0.0f - dsp->fRec20[0])));
			dsp->fRec18[0] = ((float)dsp->iVec3[1] - ((dsp->fRec18[1] * (0.0f - (fTemp149 + fTemp150))) + ((fTemp149 * fTemp150) * dsp->fRec18[2])));
			float fTemp151 = (iTemp30?((0.0293140002f * fTemp33) + 0.0501190014f):0.0794330016f);
			float fTemp152 = (iTemp19?(iTemp22?(iTemp24?(iTemp26?(iTemp29?(iTemp30?(iTemp32?(iTemp34?(iTemp35?(iTemp38?(iTemp40?(iTemp41?(iTemp42?(iTemp44?(iTemp47?(iTemp49?(iTemp50?(iTemp52?(iTemp54?(iTemp56?(iTemp59?(iTemp62?(iTemp65?(iTemp67?0.100000001f:(iTemp65?(0.100000001f - (0.0683770031f * fTemp18)):0.0316229984f)):0.0316229984f):(iTemp59?((0.126865998f * fTemp63) + 0.0316229984f):0.158489004f)):(iTemp56?(0.158489004f - (0.126865998f * fTemp60)):0.0316229984f)):(iTemp54?((0.323190004f * fTemp57) + 0.0316229984f):0.35481301f)):0.35481301f):(iTemp50?(0.35481301f - (0.196324006f * fTemp53)):0.158489004f)):(iTemp49?(0.158489004f - (0.0693639964f * fTemp51)):0.0891249999f)):(iTemp47?(0.0891249999f - (0.0640060008f * fTemp138)):0.0251189992f)):(iTemp44?((0.0456760004f * fTemp48) + 0.0251189992f):0.0707949996f)):(iTemp42?((0.0550980009f * fTemp45) + 0.0707949996f):0.125892997f)):(iTemp41?(0.125892997f - (0.0627970025f * fTemp43)):0.0630960017f)):(iTemp40?(0.0630960017f - (0.0129770003f * fTemp132)):0.0501190014f)):(iTemp38?((0.020676f * fTemp131) + 0.0501190014f):0.0707949996f)):(iTemp35?(0.0707949996f - (0.0456760004f * fTemp39)):0.0251189992f)):(iTemp34?((0.152709007f * fTemp36) + 0.0251189992f):0.177827999f)):(iTemp32?(0.177827999f - (0.127709001f * fTemp130)):0.0501190014f)):fTemp151):(iTemp29?(0.0794330016f - (0.0616500005f * fTemp31)):0.0177829992f)):(iTemp26?((0.428900987f * fTemp129) + 0.0177829992f):0.446684003f)):(iTemp24?(0.446684003f - (0.195494995f * fTemp27)):0.251188993f)):(iTemp22?(0.251188993f - (0.125295997f * fTemp25)):0.125892997f)):(iTemp19?((0.125295997f * fTemp23) + 0.125892997f):0.251188993f)):(iTemp20?(0.251188993f - (0.109935001f * fTemp21)):0.141253993f));
			float fTemp153 = (100.0f * fTemp78);
			float fTemp154 = (50.0f * fTemp104);
			float fTemp155 = (((float)iTemp74 * dsp->fRec21[1]) + (dsp->fConst7 * (iTemp76?(iTemp79?(iTemp81?(iTemp83?(iTemp85?(iTemp87?(iTemp89?(iTemp91?(iTemp93?(iTemp95?(iTemp97?(iTemp99?(iTemp101?(iTemp103?(iTemp105?(iTemp107?(iTemp110?(iTemp112?(iTemp114?(iTemp116?(iTemp118?(iTemp120?(iTemp122?(iTemp124?2800.0f:(iTemp122?(2800.0f - (100.0f * fTemp75)):2700.0f)):2700.0f):(iTemp118?((130.0f * fTemp121) + 2700.0f):2830.0f)):(iTemp116?(2830.0f - (300.0f * fTemp119)):2530.0f)):(iTemp114?(2530.0f - (280.0f * fTemp117)):2250.0f)):(iTemp112?((150.0f * fTemp115) + 2250.0f):2400.0f)):(iTemp110?((200.0f * fTemp113) + 2400.0f):2600.0f)):(iTemp107?(2600.0f - (200.0f * fTemp111)):2400.0f)):2400.0f):(iTemp103?((350.0f * fTemp106) + 2400.0f):2750.0f)):(iTemp101?(2750.0f - fTemp154):2700.0f)):(iTemp99?((200.0f * fTemp102) + 2700.0f):2900.0f)):(iTemp97?(2900.0f - (200.0f * fTemp100)):2700.0f)):(iTemp95?((50.0f * fTemp98) + 2700.0f):2750.0f)):(iTemp93?((150.0f * fTemp96) + 2750.0f):2900.0f)):(iTemp91?(2900.0f - (100.0f * fTemp94)):2800.0f)):(iTemp89?((150.0f * fTemp92) + 2800.0f):2950.0f)):(iTemp87?(2950.0f - (120.0f * fTemp90)):2830.0f)):(iTemp85?(2830.0f - (130.0f * fTemp88)):2700.0f)):(iTemp83?(2700.0f - (50.0f * fTemp86)):2650.0f)):(iTemp81?(2650.0f - (50.0f * fTemp84)):2600.0f)):(iTemp79?((200.0f * fTemp82) + 2600.0f):2800.0f)):(iTemp76?(2800.0f - (200.0f * fTemp80)):2600.0f)):(iTemp77?(fTemp153 + 2600.0f):2700.0f))));
			dsp->fRec21[0] = (fTemp155 - floorf(fTemp155));
			float fTemp156 = (iTemp19?(iTemp22?(iTemp24?(iTemp26?(iTemp29?(iTemp30?(iTemp32?(iTemp34?(iTemp35?(iTemp38?(iTemp40?(iTemp41?(iTemp42?(iTemp44?(iTemp47?(iTemp49?(iTemp50?(iTemp52?(iTemp54?(iTemp56?(iTemp59?(iTemp62?(iTemp65?(iTemp67?130.0f:(iTemp65?(fTemp68 + 130.0f):150.0f)):150.0f):(iTemp59?(150.0f - fTemp64):130.0f)):(iTemp56?((50.0f * fTemp60) + 130.0f):180.0f)):(iTemp54?(180.0f - fTemp147):120.0f)):120.0f):120.0f):120.0f):120.0f):(iTemp44?(fTemp133 + 120.0f):130.0f)):(iTemp42?(130.0f - fTemp46):120.0f)):120.0f):120.0f):120.0f):(iTemp35?((10.0f * fTemp39) + 120.0f):130.0f)):(iTemp34?(fTemp37 + 130.0f):150.0f)):(iTemp32?(150.0f - (30.0f * fTemp130)):120.0f)):120.0f):(iTemp29?((60.0f * fTemp31) + 120.0f):180.0f)):(iTemp26?(180.0f - fTemp143):130.0f)):(iTemp24?(130.0f - fTemp128):120.0f)):120.0f):(iTemp19?(fTemp127 + 120.0f):130.0f)):(iTemp20?(130.0f - (10.0f * fTemp21)):120.0f));
			dsp->fRec23[0] = ((dsp->fConst5 * dsp->fRec23[1]) + (dsp->fConst6 * (fTemp17 * fTemp156)));
			float fTemp157 = expf((dsp->fConst4 * (0.0f - dsp->fRec23[0])));
			dsp->fRec24[0] = ((dsp->fConst5 * dsp->fRec24[1]) + (dsp->fConst6 * fTemp156));
			float fTemp158 = expf((dsp->fConst4 * (0.0f - dsp->fRec24[0])));
			dsp->fRec22[0] = ((float)dsp->iVec3[1] - ((dsp->fRec22[1] * (0.0f - (fTemp157 + fTemp158))) + ((fTemp157 * fTemp158) * dsp->fRec22[2])));
			float fTemp159 = (iTemp41?(0.100000001f - (0.0841509998f * fTemp43)):0.0158489998f);
			float fTemp160 = (iTemp19?(iTemp22?(iTemp24?(iTemp26?(iTemp29?(iTemp30?(iTemp32?(iTemp34?(iTemp35?(iTemp38?(iTemp40?(iTemp41?(iTemp42?(iTemp44?(iTemp47?(iTemp49?(iTemp50?(iTemp52?(iTemp54?(iTemp56?(iTemp59?(iTemp62?(iTemp65?(iTemp67?0.0158489998f:(iTemp65?((0.00193400006f * fTemp18) + 0.0158489998f):0.0177829992f)):(iTemp62?(0.0177829992f - (0.00193400006f * fTemp66)):0.0158489998f)):(iTemp59?((0.0239620004f * fTemp63) + 0.0158489998f):0.0398110002f)):(iTemp56?(0.0398110002f - (0.0298110005f * fTemp60)):0.00999999978f)):(iTemp54?((0.344812989f * fTemp57) + 0.00999999978f):0.35481301f)):(iTemp52?(0.35481301f - (0.103624001f * fTemp55)):0.251188993f)):(iTemp50?(0.251188993f - (0.171755999f * fTemp53)):0.0794330016f)):(iTemp49?((0.0205669999f * fTemp51) + 0.0794330016f):0.100000001f)):(iTemp47?(0.100000001f - (0.0601890013f * fTemp138)):0.0398110002f)):(iTemp44?((0.0232849997f * fTemp48) + 0.0398110002f):0.0630960017f)):(iTemp42?((0.0369039997f * fTemp45) + 0.0630960017f):0.100000001f)):fTemp159):(iTemp40?((0.0635839999f * fTemp132) + 0.0158489998f):0.0794330016f)):(iTemp38?(0.0794330016f - (0.0478099994f * fTemp131)):0.0316229984f)):(iTemp35?((0.0683770031f * fTemp39) + 0.0316229984f):0.100000001f)):(iTemp34?(0.100000001f - (0.0900000036f * fTemp36)):0.00999999978f)):(iTemp32?((0.0401189998f * fTemp130) + 0.00999999978f):0.0501190014f)):fTemp151):(iTemp29?(0.0794330016f - (0.0694330037f * fTemp31)):0.00999999978f)):(iTemp26?((0.388107002f * fTemp129) + 0.00999999978f):0.398106992f)):(iTemp24?(0.398106992f - (0.198580995f * fTemp27)):0.199525997f)):(iTemp22?(0.199525997f - (0.099526003f * fTemp25)):0.100000001f)):(iTemp19?((0.151188999f * fTemp23) + 0.100000001f):0.251188993f)):(iTemp20?(0.251188993f - (0.0516630001f * fTemp21)):0.199525997f));
			float fTemp161 = (350.0f * fTemp115);
			float fTemp162 = (((float)iTemp74 * dsp->fRec25[1]) + (dsp->fConst7 * (iTemp76?(iTemp79?(iTemp81?(iTemp83?(iTemp85?(iTemp87?(iTemp89?(iTemp91?(iTemp93?(iTemp95?(iTemp97?(iTemp99?(iTemp101?(iTemp103?(iTemp105?(iTemp107?(iTemp110?(iTemp112?(iTemp114?(iTemp116?(iTemp118?(iTemp120?(iTemp122?(iTemp124?3500.0f:(iTemp122?(3500.0f - (200.0f * fTemp75)):3300.0f)):(iTemp120?((400.0f * fTemp123) + 3300.0f):3700.0f)):(iTemp118?(3700.0f - (200.0f * fTemp121)):3500.0f)):3500.0f):(iTemp114?(3500.0f - (1050.0f * fTemp117)):2450.0f)):(iTemp112?(fTemp161 + 2450.0f):2800.0f)):(iTemp110?((250.0f * fTemp113) + 2800.0f):3050.0f)):(iTemp107?(3050.0f - (450.0f * fTemp111)):2600.0f)):(iTemp105?((75.0f * fTemp108) + 2600.0f):2675.0f)):(iTemp103?((325.0f * fTemp106) + 2675.0f):3000.0f)):3000.0f):(iTemp99?((350.0f * fTemp102) + 3000.0f):3350.0f)):(iTemp97?(3350.0f - (350.0f * fTemp100)):3000.0f)):3000.0f):(iTemp93?((900.0f * fTemp96) + 3000.0f):3900.0f)):(iTemp91?(3900.0f - (300.0f * fTemp94)):3600.0f)):(iTemp89?((300.0f * fTemp92) + 3600.0f):3900.0f)):(iTemp87?(3900.0f - (100.0f * fTemp90)):3800.0f)):3800.0f):(iTemp83?(3800.0f - (900.0f * fTemp86)):2900.0f)):(iTemp81?((300.0f * fTemp84) + 2900.0f):3200.0f)):(iTemp79?((50.0f * fTemp82) + 3200.0f):3250.0f)):(iTemp76?(3250.0f - (450.0f * fTemp80)):2800.0f)):(iTemp77?(fTemp153 + 2800.0f):2900.0f))));
			dsp->fRec25[0] = (fTemp162 - floorf(fTemp162));
			float fTemp163 = (iTemp19?(iTemp22?(iTemp24?(iTemp26?(iTemp29?(iTemp30?(iTemp32?(iTemp34?(iTemp35?(iTemp38?(iTemp40?(iTemp41?(iTemp42?(iTemp44?(iTemp47?(iTemp49?(iTemp50?(iTemp52?(iTemp54?(iTemp56?(iTemp59?(iTemp62?(iTemp65?(iTemp67?140.0f:(iTemp65?((60.0f * fTemp18) + 140.0f):200.0f)):200.0f):(iTemp59?(200.0f - (65.0f * fTemp63)):135.0f)):(iTemp56?((65.0f * fTemp60) + 135.0f):200.0f)):(iTemp54?(200.0f - (70.0f * fTemp57)):130.0f)):(iTemp52?(130.0f - fTemp134):120.0f)):120.0f):120.0f):120.0f):(iTemp44?(fTemp146 + 120.0f):140.0f)):(iTemp42?(140.0f - fTemp145):120.0f)):120.0f):120.0f):120.0f):(iTemp35?(fTemp144 + 120.0f):140.0f)):(iTemp34?((60.0f * fTemp36) + 140.0f):200.0f)):(iTemp32?(200.0f - (80.0f * fTemp130)):120.0f)):120.0f):(iTemp29?((80.0f * fTemp31) + 120.0f):200.0f)):(iTemp26?(200.0f - (60.0f * fTemp129)):140.0f)):(iTemp24?(140.0f - fTemp28):120.0f)):120.0f):(iTemp19?((15.0f * fTemp23) + 120.0f):135.0f)):(iTemp20?(135.0f - (15.0f * fTemp21)):120.0f));
			dsp->fRec27[0] = ((dsp->fConst5 * dsp->fRec27[1]) + (dsp->fConst6 * (fTemp17 * fTemp163)));
			float fTemp164 = expf((dsp->fConst4 * (0.0f - dsp->fRec27[0])));
			dsp->fRec28[0] = ((dsp->fConst5 * dsp->fRec28[1]) + (dsp->fConst6 * fTemp163));
			float fTemp165 = expf((dsp->fConst4 * (0.0f - dsp->fRec28[0])));
			dsp->fRec26[0] = ((float)dsp->iVec3[1] - ((dsp->fRec26[1] * (0.0f - (fTemp164 + fTemp165))) + ((fTemp164 * fTemp165) * dsp->fRec26[2])));
			float fTemp166 = (iTemp19?(iTemp22?(iTemp24?(iTemp26?(iTemp29?(iTemp30?(iTemp32?(iTemp34?(iTemp35?(iTemp38?(iTemp40?(iTemp41?(iTemp42?(iTemp44?(iTemp47?(iTemp49?(iTemp50?(iTemp52?(iTemp54?(iTemp56?(iTemp59?(iTemp62?0.00100000005f:(iTemp59?((0.000777999987f * fTemp63) + 0.00100000005f):0.00177800003f)):(iTemp56?(0.00177800003f - (0.001147f * fTemp60)):0.000630999974f)):(iTemp54?((0.0993689969f * fTemp57) + 0.000630999974f):0.100000001f)):(iTemp52?((0.0258930009f * fTemp55) + 0.100000001f):0.125892997f)):(iTemp50?(0.125892997f - (0.0860819966f * fTemp53)):0.0398110002f)):(iTemp49?(0.0398110002f - (0.0298110005f * fTemp51)):0.00999999978f)):(iTemp47?((0.00584900007f * fTemp138) + 0.00999999978f):0.0158489998f)):(iTemp44?(0.0158489998f - (0.00325999991f * fTemp48)):0.0125890002f)):(iTemp42?((0.0874110013f * fTemp45) + 0.0125890002f):0.100000001f)):fTemp159):(iTemp40?((0.00410400005f * fTemp132) + 0.0158489998f):0.0199529994f)):0.0199529994f):(iTemp35?(0.0199529994f - (0.0167909991f * fTemp39)):0.0031620001f)):(iTemp34?(0.0031620001f - (0.00157700002f * fTemp36)):0.00158499996f)):(iTemp32?((0.00472499989f * fTemp130) + 0.00158499996f):0.00631000008f)):(iTemp30?(0.00631000008f - (0.00314799999f * fTemp33)):0.0031620001f)):(iTemp29?(0.0031620001f - (0.00216199993f * fTemp31)):0.00100000005f)):(iTemp26?((0.0784329996f * fTemp129) + 0.00100000005f):0.0794330016f)):(iTemp24?((0.0205669999f * fTemp27) + 0.0794330016f):0.100000001f)):(iTemp22?(0.100000001f - (0.0683770031f * fTemp25)):0.0316229984f)):(iTemp19?((0.0184959993f * fTemp23) + 0.0316229984f):0.0501190014f)):0.0501190014f);
			float fTemp167 = (((float)iTemp74 * dsp->fRec29[1]) + (dsp->fConst7 * (iTemp76?(iTemp79?(iTemp81?(iTemp83?(iTemp85?(iTemp87?(iTemp89?(iTemp91?(iTemp93?(iTemp95?(iTemp97?(iTemp99?(iTemp101?(iTemp103?(iTemp105?(iTemp107?(iTemp110?(iTemp112?(iTemp114?(iTemp116?4950.0f:(iTemp114?(4950.0f - (2200.0f * fTemp117)):2750.0f)):(iTemp112?(fTemp161 + 2750.0f):3100.0f)):(iTemp110?((240.0f * fTemp113) + 3100.0f):3340.0f)):(iTemp107?(3340.0f - (440.0f * fTemp111)):2900.0f)):(iTemp105?(fTemp109 + 2900.0f):2950.0f)):(iTemp103?((400.0f * fTemp106) + 2950.0f):3350.0f)):(iTemp101?(3350.0f - fTemp154):3300.0f)):(iTemp99?((290.0f * fTemp102) + 3300.0f):3590.0f)):(iTemp97?(3590.0f - (290.0f * fTemp100)):3300.0f)):(iTemp95?((100.0f * fTemp98) + 3300.0f):3400.0f)):(iTemp93?((1550.0f * fTemp96) + 3400.0f):4950.0f)):4950.0f):4950.0f):4950.0f):4950.0f):(iTemp83?(4950.0f - (1700.0f * fTemp86)):3250.0f)):(iTemp81?((330.0f * fTemp84) + 3250.0f):3580.0f)):(iTemp79?(3580.0f - (40.0f * fTemp82)):3540.0f)):(iTemp76?(3540.0f - (540.0f * fTemp80)):3000.0f)):(iTemp77?((300.0f * fTemp78) + 3000.0f):3300.0f))));
			dsp->fRec29[0] = (fTemp167 - floorf(fTemp167));
			float fTemp168 = (fSlow0 * (dsp->fRec0[0] * (((((((dsp->fRec1[0] * (iSlow22?fTemp73:fTemp72)) * (1.0f - (fTemp71 + (fTemp70 * (1.0f - fTemp71))))) * ftbl0mydspSIG0[(int)(65536.0f * dsp->fRec12[0])]) + (((dsp->fRec14[0] * (iSlow22?(fTemp73 * fTemp139):(fTemp72 * fTemp139))) * (1.0f - (fTemp137 + (fTemp136 * (1.0f - fTemp137))))) * ftbl0mydspSIG0[(int)(65536.0f * dsp->fRec17[0])])) + (((dsp->fRec18[0] * (iSlow22?(fTemp73 * fTemp152):(fTemp72 * fTemp152))) * (1.0f - (fTemp150 + (fTemp149 * (1.0f - fTemp150))))) * ftbl0mydspSIG0[(int)(65536.0f * dsp->fRec21[0])])) + (((dsp->fRec22[0] * (iSlow22?(fTemp73 * fTemp160):(fTemp72 * fTemp160))) * (1.0f - (fTemp158 + (fTemp157 * (1.0f - fTemp158))))) * ftbl0mydspSIG0[(int)(65536.0f * dsp->fRec25[0])])) + (((dsp->fRec26[0] * (iSlow22?(fTemp73 * fTemp166):(fTemp72 * fTemp166))) * (1.0f - (fTemp165 + (fTemp164 * (1.0f - fTemp165))))) * ftbl0mydspSIG0[(int)(65536.0f * dsp->fRec29[0])]))));
			output0[i] = (FAUSTFLOAT)fTemp168;
			output1[i] = (FAUSTFLOAT)fTemp168;
			dsp->iVec0[1] = dsp->iVec0[0];
			dsp->fVec1[1] = dsp->fVec1[0];
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec3[1] = dsp->fRec3[0];
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fRec5[1] = dsp->fRec5[0];
			dsp->fVec2[1] = dsp->fVec2[0];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->iVec3[1] = dsp->iVec3[0];
			dsp->fRec7[1] = dsp->fRec7[0];
			dsp->fRec8[1] = dsp->fRec8[0];
			dsp->fRec9[1] = dsp->fRec9[0];
			dsp->fRec6[1] = dsp->fRec6[0];
			dsp->fRec10[1] = dsp->fRec10[0];
			dsp->fRec1[2] = dsp->fRec1[1];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fRec13[1] = dsp->fRec13[0];
			dsp->fRec12[1] = dsp->fRec12[0];
			dsp->fRec15[1] = dsp->fRec15[0];
			dsp->fRec16[1] = dsp->fRec16[0];
			dsp->fRec14[2] = dsp->fRec14[1];
			dsp->fRec14[1] = dsp->fRec14[0];
			dsp->fRec17[1] = dsp->fRec17[0];
			dsp->fRec19[1] = dsp->fRec19[0];
			dsp->fRec20[1] = dsp->fRec20[0];
			dsp->fRec18[2] = dsp->fRec18[1];
			dsp->fRec18[1] = dsp->fRec18[0];
			dsp->fRec21[1] = dsp->fRec21[0];
			dsp->fRec23[1] = dsp->fRec23[0];
			dsp->fRec24[1] = dsp->fRec24[0];
			dsp->fRec22[2] = dsp->fRec22[1];
			dsp->fRec22[1] = dsp->fRec22[0];
			dsp->fRec25[1] = dsp->fRec25[0];
			dsp->fRec27[1] = dsp->fRec27[0];
			dsp->fRec28[1] = dsp->fRec28[0];
			dsp->fRec26[2] = dsp->fRec26[1];
			dsp->fRec26[1] = dsp->fRec26[0];
			dsp->fRec29[1] = dsp->fRec29[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
