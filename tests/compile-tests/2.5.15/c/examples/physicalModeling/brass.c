/* ------------------------------------------------------------
copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
license: "MIT"
name: "Brass"
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
	
	int iRec6[2];
	FAUSTFLOAT fHslider0;
	int iVec0[2];
	float fRec14[2];
	float fRec13[2];
	float fRec15[2];
	FAUSTFLOAT fHslider1;
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider2;
	float fRec20[2];
	float fRec21[2];
	FAUSTFLOAT fHslider3;
	float fRec22[2];
	FAUSTFLOAT fHslider4;
	float fConst2;
	FAUSTFLOAT fHslider5;
	int iRec24[2];
	float fRec23[3];
	float fConst3;
	FAUSTFLOAT fHslider6;
	float fRec25[2];
	FAUSTFLOAT fHslider7;
	float fRec26[2];
	float fRec19[3];
	float fVec1[2];
	float fRec18[2];
	int IOTA;
	float fRec16[2048];
	float fConst4;
	float fConst5;
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
	m->declare(m->metaInterface, "copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
	m->declare(m->metaInterface, "delays.lib/name", "Faust Delay Library");
	m->declare(m->metaInterface, "delays.lib/version", "0.0");
	m->declare(m->metaInterface, "description", "Simple brass instrument physical model with physical parameters.");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "license", "MIT");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "Brass");
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
	dsp->fHslider1 = (FAUSTFLOAT)0.25f;
	dsp->fHslider2 = (FAUSTFLOAT)5.0f;
	dsp->fHslider3 = (FAUSTFLOAT)0.0f;
	dsp->fHslider4 = (FAUSTFLOAT)0.10000000000000001f;
	dsp->fHslider5 = (FAUSTFLOAT)2000.0f;
	dsp->fHslider6 = (FAUSTFLOAT)0.5f;
	dsp->fHslider7 = (FAUSTFLOAT)0.5f;
	
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
			dsp->fRec20[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			dsp->fRec21[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			dsp->fRec22[l7] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			dsp->iRec24[l8] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 3); l9 = (l9 + 1)) {
			dsp->fRec23[l9] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			dsp->fRec25[l10] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			dsp->fRec26[l11] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 3); l12 = (l12 + 1)) {
			dsp->fRec19[l12] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l13;
		for (l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			dsp->fVec1[l13] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l14;
		for (l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			dsp->fRec18[l14] = 0.0f;
			
		}
		
	}
	dsp->IOTA = 0;
	/* C99 loop */
	{
		int l15;
		for (l15 = 0; (l15 < 2048); l15 = (l15 + 1)) {
			dsp->fRec16[l15] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l16;
		for (l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			dsp->fVec2[l16] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l17;
		for (l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			dsp->fRec11[l17] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l18;
		for (l18 = 0; (l18 < 2048); l18 = (l18 + 1)) {
			dsp->fRec2[l18] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l19;
		for (l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			dsp->fRec0[l19] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = (6.28318548f / dsp->fConst0);
	dsp->fConst2 = (3.14159274f / dsp->fConst0);
	dsp->fConst3 = (2136.28296f / dsp->fConst0);
	dsp->fConst4 = (0.00882352982f * dsp->fConst0);
	dsp->fConst5 = (0.00147058826f * dsp->fConst0);
	
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
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "brass");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "blower");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "0", "");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "pressure", &dsp->fHslider3, 0.0f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "1", "");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "breathGain", &dsp->fHslider4, 0.100000001f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "2", "");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "breathCutoff", &dsp->fHslider5, 2000.0f, 20.0f, 20000.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "3", "");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "vibratoFreq", &dsp->fHslider2, 5.0f, 0.100000001f, 10.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "4", "");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "vibratoGain", &dsp->fHslider1, 0.25f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "brassModel");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider7, "1", "");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "tubeLength", &dsp->fHslider7, 0.5f, 0.00999999978f, 2.5f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider6, "2", "");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "lipsTension", &dsp->fHslider6, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "3", "");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "mute", &dsp->fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	float fSlow0 = (0.00100000005f * (float)dsp->fHslider0);
	float fSlow1 = (0.0299999993f * (float)dsp->fHslider1);
	float fSlow2 = (dsp->fConst1 * (float)dsp->fHslider2);
	float fSlow3 = sinf(fSlow2);
	float fSlow4 = cosf(fSlow2);
	float fSlow5 = (0.0f - fSlow3);
	float fSlow6 = (0.00100000005f * (float)dsp->fHslider3);
	float fSlow7 = tanf((dsp->fConst2 * (float)dsp->fHslider5));
	float fSlow8 = (1.0f / fSlow7);
	float fSlow9 = (((fSlow8 + 1.41421354f) / fSlow7) + 1.0f);
	float fSlow10 = (0.0500000007f * ((float)dsp->fHslider4 / fSlow9));
	float fSlow11 = (1.0f / fSlow9);
	float fSlow12 = (((fSlow8 + -1.41421354f) / fSlow7) + 1.0f);
	float fSlow13 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fSlow7))));
	float fSlow14 = (0.00100000005f * (float)dsp->fHslider6);
	float fSlow15 = (0.00100000005f * (float)dsp->fHslider7);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->iRec6[0] = 0;
			dsp->iVec0[0] = 1;
			dsp->fRec14[0] = (fSlow0 + (0.999000013f * dsp->fRec14[1]));
			dsp->fRec13[0] = ((dsp->fRec14[0] * dsp->fRec13[1]) + ((1.0f - dsp->fRec14[0]) * dsp->fRec11[1]));
			float fRec10 = (dsp->fRec13[0] + (float)dsp->iRec6[1]);
			dsp->fRec15[0] = dsp->fRec0[1];
			dsp->fRec20[0] = ((fSlow3 * dsp->fRec21[1]) + (fSlow4 * dsp->fRec20[1]));
			dsp->fRec21[0] = (((fSlow4 * dsp->fRec21[1]) + (fSlow5 * dsp->fRec20[1])) + (float)(1 - dsp->iVec0[1]));
			dsp->fRec22[0] = (fSlow6 + (0.999000013f * dsp->fRec22[1]));
			dsp->iRec24[0] = ((1103515245 * dsp->iRec24[1]) + 12345);
			dsp->fRec23[0] = ((4.65661287e-10f * (float)dsp->iRec24[0]) - (fSlow11 * ((fSlow12 * dsp->fRec23[2]) + (fSlow13 * dsp->fRec23[1]))));
			float fTemp0 = ((fSlow1 * dsp->fRec20[0]) + (dsp->fRec22[0] * ((fSlow10 * (dsp->fRec23[2] + (dsp->fRec23[0] + (2.0f * dsp->fRec23[1])))) + 1.0f)));
			dsp->fRec25[0] = (fSlow14 + (0.999000013f * dsp->fRec25[1]));
			dsp->fRec26[0] = (fSlow15 + (0.999000013f * dsp->fRec26[1]));
			dsp->fRec19[0] = ((0.0299999993f * ((0.300000012f * fTemp0) - (0.850000024f * dsp->fRec15[1]))) - ((dsp->fRec19[1] * (0.0f - (1.99399996f * cosf((dsp->fConst3 * (powf(4.0f, ((2.0f * dsp->fRec25[0]) + -1.0f)) / dsp->fRec26[0])))))) + (0.994009018f * dsp->fRec19[2])));
			float fTemp1 = max(-1.0f, min(1.0f, mydsp_faustpower2_f(dsp->fRec19[0])));
			float fTemp2 = (0.850000024f * (dsp->fRec15[1] * (1.0f - fTemp1)));
			float fTemp3 = (0.300000012f * (fTemp0 * fTemp1));
			dsp->fVec1[0] = (fTemp3 + fTemp2);
			dsp->fRec18[0] = ((fTemp2 + ((0.995000005f * dsp->fRec18[1]) + fTemp3)) - dsp->fVec1[1]);
			dsp->fRec16[(dsp->IOTA & 2047)] = dsp->fRec18[0];
			int iRec17 = 0;
			float fTemp4 = (dsp->fConst5 * dsp->fRec26[0]);
			float fTemp5 = (fTemp4 + -1.49999499f);
			int iTemp6 = (int)fTemp5;
			int iTemp7 = ((int)min(dsp->fConst4, (float)max(0, iTemp6)) + 1);
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
			int iTemp18 = ((int)min(dsp->fConst4, (float)max(0, (iTemp6 + 2))) + 1);
			float fTemp19 = (0.0f - fTemp13);
			float fTemp20 = (0.0f - (0.5f * fTemp15));
			int iTemp21 = ((int)min(dsp->fConst4, (float)max(0, (iTemp6 + 1))) + 1);
			float fTemp22 = (0.0f - fTemp11);
			float fTemp23 = (0.0f - (0.5f * fTemp13));
			float fTemp24 = (0.0f - (0.333333343f * fTemp15));
			float fTemp25 = (fTemp9 * fTemp11);
			int iTemp26 = ((int)min(dsp->fConst4, (float)max(0, (iTemp6 + 3))) + 1);
			float fTemp27 = (0.0f - fTemp15);
			float fTemp28 = (fTemp25 * fTemp13);
			int iTemp29 = ((int)min(dsp->fConst4, (float)max(0, (iTemp6 + 4))) + 1);
			dsp->fVec2[0] = (((((dsp->fRec16[((dsp->IOTA - iTemp7) & 2047)] * fTemp10) * fTemp12) * fTemp14) * fTemp16) + (fTemp17 * ((((0.5f * (((fTemp9 * dsp->fRec16[((dsp->IOTA - iTemp18) & 2047)]) * fTemp19) * fTemp20)) + (((dsp->fRec16[((dsp->IOTA - iTemp21) & 2047)] * fTemp22) * fTemp23) * fTemp24)) + (0.166666672f * ((fTemp25 * dsp->fRec16[((dsp->IOTA - iTemp26) & 2047)]) * fTemp27))) + (0.0416666679f * (fTemp28 * dsp->fRec16[((dsp->IOTA - iTemp29) & 2047)])))));
			dsp->fRec11[0] = dsp->fVec2[1];
			int iRec12 = iRec17;
			float fRec7 = fRec10;
			float fRec8 = dsp->fRec11[0];
			float fRec9 = (dsp->fRec11[0] + (float)iRec12);
			dsp->fRec2[(dsp->IOTA & 2047)] = fRec7;
			float fRec3 = (((((fTemp10 * fTemp12) * fTemp14) * fTemp16) * dsp->fRec2[((dsp->IOTA - iTemp7) & 2047)]) + (fTemp17 * (((0.166666672f * ((fTemp25 * fTemp27) * dsp->fRec2[((dsp->IOTA - iTemp26) & 2047)])) + ((((fTemp22 * fTemp23) * fTemp24) * dsp->fRec2[((dsp->IOTA - iTemp21) & 2047)]) + (0.5f * (((fTemp9 * fTemp19) * fTemp20) * dsp->fRec2[((dsp->IOTA - iTemp18) & 2047)])))) + (0.0416666679f * (fTemp28 * dsp->fRec2[((dsp->IOTA - iTemp29) & 2047)])))));
			float fRec4 = fRec8;
			float fRec5 = fRec9;
			dsp->fRec0[0] = fRec3;
			float fRec1 = fRec5;
			output0[i] = (FAUSTFLOAT)fRec1;
			output1[i] = (FAUSTFLOAT)fRec1;
			dsp->iRec6[1] = dsp->iRec6[0];
			dsp->iVec0[1] = dsp->iVec0[0];
			dsp->fRec14[1] = dsp->fRec14[0];
			dsp->fRec13[1] = dsp->fRec13[0];
			dsp->fRec15[1] = dsp->fRec15[0];
			dsp->fRec20[1] = dsp->fRec20[0];
			dsp->fRec21[1] = dsp->fRec21[0];
			dsp->fRec22[1] = dsp->fRec22[0];
			dsp->iRec24[1] = dsp->iRec24[0];
			dsp->fRec23[2] = dsp->fRec23[1];
			dsp->fRec23[1] = dsp->fRec23[0];
			dsp->fRec25[1] = dsp->fRec25[0];
			dsp->fRec26[1] = dsp->fRec26[0];
			dsp->fRec19[2] = dsp->fRec19[1];
			dsp->fRec19[1] = dsp->fRec19[0];
			dsp->fVec1[1] = dsp->fVec1[0];
			dsp->fRec18[1] = dsp->fRec18[0];
			dsp->IOTA = (dsp->IOTA + 1);
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
