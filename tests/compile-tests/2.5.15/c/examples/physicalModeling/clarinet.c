/* ------------------------------------------------------------
copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
license: "MIT"
name: "Clarinet"
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
	FAUSTFLOAT fHslider4;
	float fRec19[2];
	FAUSTFLOAT fHslider5;
	float fConst2;
	FAUSTFLOAT fHslider6;
	int iRec21[2];
	float fRec20[3];
	float fRec14[2];
	FAUSTFLOAT fHslider7;
	int IOTA;
	float fRec15[2048];
	float fConst3;
	float fConst4;
	FAUSTFLOAT fHslider8;
	float fRec22[2];
	float fVec1[2];
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
	m->declare(m->metaInterface, "description", "Simple clarinet physical model with physical parameters.");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "license", "MIT");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "Clarinet");
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
	dsp->fHslider4 = (FAUSTFLOAT)0.0f;
	dsp->fHslider5 = (FAUSTFLOAT)0.10000000000000001f;
	dsp->fHslider6 = (FAUSTFLOAT)2000.0f;
	dsp->fHslider7 = (FAUSTFLOAT)0.5f;
	dsp->fHslider8 = (FAUSTFLOAT)0.80000000000000004f;
	
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
			dsp->fRec19[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			dsp->iRec21[l6] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			dsp->fRec20[l7] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			dsp->fRec14[l8] = 0.0f;
			
		}
		
	}
	dsp->IOTA = 0;
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 2048); l9 = (l9 + 1)) {
			dsp->fRec15[l9] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			dsp->fRec22[l10] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			dsp->fVec1[l11] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			dsp->fRec11[l12] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l13;
		for (l13 = 0; (l13 < 2048); l13 = (l13 + 1)) {
			dsp->fRec2[l13] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l14;
		for (l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			dsp->fRec0[l14] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = (6.28318548f / dsp->fConst0);
	dsp->fConst2 = (3.14159274f / dsp->fConst0);
	dsp->fConst3 = (0.00882352982f * dsp->fConst0);
	dsp->fConst4 = (0.00147058826f * dsp->fConst0);
	
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
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "clarinet");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "blower");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "0", "");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "pressure", &dsp->fHslider4, 0.0f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "1", "");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "breathGain", &dsp->fHslider5, 0.100000001f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider6, "2", "");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "breathCutoff", &dsp->fHslider6, 2000.0f, 20.0f, 20000.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "3", "");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "vibratoFreq", &dsp->fHslider3, 5.0f, 0.100000001f, 10.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "4", "");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "vibratoGain", &dsp->fHslider2, 0.25f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "clarinetModel");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider8, "0", "");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "tubeLength", &dsp->fHslider8, 0.800000012f, 0.00999999978f, 3.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider7, "1", "");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "reedStiffness", &dsp->fHslider7, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "2", "");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "bellOpening", &dsp->fHslider1, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "3", "");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "outGain", &dsp->fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	float fSlow0 = (float)dsp->fHslider0;
	float fSlow1 = (float)dsp->fHslider1;
	float fSlow2 = (1.0f - fSlow1);
	float fSlow3 = (0.0299999993f * (float)dsp->fHslider2);
	float fSlow4 = (dsp->fConst1 * (float)dsp->fHslider3);
	float fSlow5 = sinf(fSlow4);
	float fSlow6 = cosf(fSlow4);
	float fSlow7 = (0.0f - fSlow5);
	float fSlow8 = (0.00100000005f * (float)dsp->fHslider4);
	float fSlow9 = tanf((dsp->fConst2 * (float)dsp->fHslider6));
	float fSlow10 = (1.0f / fSlow9);
	float fSlow11 = (((fSlow10 + 1.41421354f) / fSlow9) + 1.0f);
	float fSlow12 = (0.0500000007f * ((float)dsp->fHslider5 / fSlow11));
	float fSlow13 = (1.0f / fSlow11);
	float fSlow14 = (((fSlow10 + -1.41421354f) / fSlow9) + 1.0f);
	float fSlow15 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fSlow9))));
	float fSlow16 = ((0.25999999f * (float)dsp->fHslider7) + -0.439999998f);
	float fSlow17 = (0.00100000005f * (float)dsp->fHslider8);
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
			dsp->fRec19[0] = (fSlow8 + (0.999000013f * dsp->fRec19[1]));
			dsp->iRec21[0] = ((1103515245 * dsp->iRec21[1]) + 12345);
			dsp->fRec20[0] = ((4.65661287e-10f * (float)dsp->iRec21[0]) - (fSlow13 * ((fSlow14 * dsp->fRec20[2]) + (fSlow15 * dsp->fRec20[1]))));
			float fTemp1 = (dsp->fRec19[0] * ((fSlow12 * (dsp->fRec20[2] + (dsp->fRec20[0] + (2.0f * dsp->fRec20[1])))) + 1.0f));
			dsp->fRec14[0] = ((dsp->fRec0[1] + fTemp0) + fTemp1);
			float fTemp2 = (0.0f - dsp->fRec14[1]);
			dsp->fRec15[(dsp->IOTA & 2047)] = ((fTemp0 + fTemp1) + (fTemp2 * max(-1.0f, min(1.0f, ((fSlow16 * fTemp2) + 0.699999988f)))));
			int iRec16 = 0;
			dsp->fRec22[0] = (fSlow17 + (0.999000013f * dsp->fRec22[1]));
			float fTemp3 = (dsp->fConst4 * ((0.5f * dsp->fRec22[0]) + -0.0500000007f));
			float fTemp4 = (fTemp3 + -1.49999499f);
			int iTemp5 = (int)fTemp4;
			int iTemp6 = ((int)min(dsp->fConst3, (float)max(0, iTemp5)) + 1);
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
			int iTemp17 = ((int)min(dsp->fConst3, (float)max(0, (iTemp5 + 2))) + 1);
			float fTemp18 = (0.0f - fTemp12);
			float fTemp19 = (0.0f - (0.5f * fTemp14));
			int iTemp20 = ((int)min(dsp->fConst3, (float)max(0, (iTemp5 + 1))) + 1);
			float fTemp21 = (0.0f - fTemp10);
			float fTemp22 = (0.0f - (0.5f * fTemp12));
			float fTemp23 = (0.0f - (0.333333343f * fTemp14));
			float fTemp24 = (fTemp8 * fTemp10);
			int iTemp25 = ((int)min(dsp->fConst3, (float)max(0, (iTemp5 + 3))) + 1);
			float fTemp26 = (0.0f - fTemp14);
			float fTemp27 = (fTemp24 * fTemp12);
			int iTemp28 = ((int)min(dsp->fConst3, (float)max(0, (iTemp5 + 4))) + 1);
			dsp->fVec1[0] = (((((dsp->fRec15[((dsp->IOTA - iTemp6) & 2047)] * fTemp9) * fTemp11) * fTemp13) * fTemp15) + (fTemp16 * ((((0.5f * (((fTemp8 * dsp->fRec15[((dsp->IOTA - iTemp17) & 2047)]) * fTemp18) * fTemp19)) + (((dsp->fRec15[((dsp->IOTA - iTemp20) & 2047)] * fTemp21) * fTemp22) * fTemp23)) + (0.166666672f * ((fTemp24 * dsp->fRec15[((dsp->IOTA - iTemp25) & 2047)]) * fTemp26))) + (0.0416666679f * (fTemp27 * dsp->fRec15[((dsp->IOTA - iTemp28) & 2047)])))));
			dsp->fRec11[0] = dsp->fVec1[1];
			int iRec12 = iRec16;
			float fRec7 = fRec10;
			float fRec8 = dsp->fRec11[0];
			float fRec9 = (dsp->fRec11[0] + (float)iRec12);
			dsp->fRec2[(dsp->IOTA & 2047)] = fRec7;
			float fRec3 = (((((fTemp9 * fTemp11) * fTemp13) * fTemp15) * dsp->fRec2[((dsp->IOTA - iTemp6) & 2047)]) + (fTemp16 * (((0.166666672f * ((fTemp24 * fTemp26) * dsp->fRec2[((dsp->IOTA - iTemp25) & 2047)])) + ((((fTemp21 * fTemp22) * fTemp23) * dsp->fRec2[((dsp->IOTA - iTemp20) & 2047)]) + (0.5f * (((fTemp8 * fTemp18) * fTemp19) * dsp->fRec2[((dsp->IOTA - iTemp17) & 2047)])))) + (0.0416666679f * (fTemp27 * dsp->fRec2[((dsp->IOTA - iTemp28) & 2047)])))));
			float fRec4 = fRec8;
			float fRec5 = fRec9;
			dsp->fRec0[0] = fRec3;
			float fRec1 = fRec5;
			float fTemp29 = (fSlow0 * fRec1);
			output0[i] = (FAUSTFLOAT)fTemp29;
			output1[i] = (FAUSTFLOAT)fTemp29;
			dsp->iRec6[1] = dsp->iRec6[0];
			dsp->iVec0[1] = dsp->iVec0[0];
			dsp->fRec13[1] = dsp->fRec13[0];
			dsp->fRec17[1] = dsp->fRec17[0];
			dsp->fRec18[1] = dsp->fRec18[0];
			dsp->fRec19[1] = dsp->fRec19[0];
			dsp->iRec21[1] = dsp->iRec21[0];
			dsp->fRec20[2] = dsp->fRec20[1];
			dsp->fRec20[1] = dsp->fRec20[0];
			dsp->fRec14[1] = dsp->fRec14[0];
			dsp->IOTA = (dsp->IOTA + 1);
			dsp->fRec22[1] = dsp->fRec22[0];
			dsp->fVec1[1] = dsp->fVec1[0];
			dsp->fRec11[1] = dsp->fRec11[0];
			dsp->fRec0[1] = dsp->fRec0[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
