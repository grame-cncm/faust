/* ------------------------------------------------------------
copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
license: "MIT"
name: "GuitarMidi"
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
	int iRec10[2];
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fHslider1;
	float fRec29[2];
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT fButton0;
	FAUSTFLOAT fHslider4;
	float fVec0[2];
	float fRec30[2];
	float fRec25[2];
	float fRec31[2];
	float fRec33[4];
	int IOTA;
	float fRec34[2048];
	float fVec1[2];
	FAUSTFLOAT fHslider5;
	int iRec37[2];
	float fConst3;
	float fRec36[3];
	float fConst4;
	float fVec2[2];
	float fRec38[2];
	float fConst5;
	float fConst6;
	float fVec3[2];
	float fRec32[2048];
	float fRec21[2];
	float fRec17[2048];
	float fRec19[2];
	float fRec15[4];
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
	m->declare(m->metaInterface, "description", "Simple acoustic guitar model with steel strings.");
	m->declare(m->metaInterface, "envelopes.lib/author", "GRAME");
	m->declare(m->metaInterface, "envelopes.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "envelopes.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "envelopes.lib/name", "Faust Envelope Library");
	m->declare(m->metaInterface, "envelopes.lib/version", "0.0");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "license", "MIT");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "GuitarMidi");
	m->declare(m->metaInterface, "noises.lib/name", "Faust Noise Generator Library");
	m->declare(m->metaInterface, "noises.lib/version", "0.0");
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
	dsp->fHslider1 = (FAUSTFLOAT)0.80000000000000004f;
	dsp->fHslider2 = (FAUSTFLOAT)440.0f;
	dsp->fHslider3 = (FAUSTFLOAT)1.0f;
	dsp->fButton0 = (FAUSTFLOAT)0.0f;
	dsp->fHslider4 = (FAUSTFLOAT)0.0f;
	dsp->fHslider5 = (FAUSTFLOAT)0.80000000000000004f;
	
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
			dsp->fRec29[l1] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			dsp->fVec0[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			dsp->fRec30[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			dsp->fRec25[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			dsp->fRec31[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 4); l6 = (l6 + 1)) {
			dsp->fRec33[l6] = 0.0f;
			
		}
		
	}
	dsp->IOTA = 0;
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2048); l7 = (l7 + 1)) {
			dsp->fRec34[l7] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			dsp->fVec1[l8] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			dsp->iRec37[l9] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 3); l10 = (l10 + 1)) {
			dsp->fRec36[l10] = 0.0f;
			
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
			dsp->fRec38[l12] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l13;
		for (l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			dsp->fVec3[l13] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l14;
		for (l14 = 0; (l14 < 2048); l14 = (l14 + 1)) {
			dsp->fRec32[l14] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l15;
		for (l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			dsp->fRec21[l15] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l16;
		for (l16 = 0; (l16 < 2048); l16 = (l16 + 1)) {
			dsp->fRec17[l16] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l17;
		for (l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			dsp->fRec19[l17] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l18;
		for (l18 = 0; (l18 < 4); l18 = (l18 + 1)) {
			dsp->fRec15[l18] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l19;
		for (l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			dsp->iRec6[l19] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l20;
		for (l20 = 0; (l20 < 2048); l20 = (l20 + 1)) {
			dsp->fRec2[l20] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l21;
		for (l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			dsp->fRec0[l21] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = (0.00882352982f * dsp->fConst0);
	dsp->fConst2 = (0.00147058826f * dsp->fConst0);
	dsp->fConst3 = (15.707963f / dsp->fConst0);
	dsp->fConst4 = (0.00400000019f * dsp->fConst0);
	dsp->fConst5 = (0.00200000009f * dsp->fConst0);
	dsp->fConst6 = (500.0f / dsp->fConst0);
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "guitar");
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
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "gain", &dsp->fHslider5, 0.800000012f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "hidden", "1");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "midi", "ctrl 64");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "sustain", &dsp->fHslider4, 0.0f, 0.0f, 1.0f, 1.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fButton0, "4", "");
	ui_interface->addButton(ui_interface->uiInterface, "gate", &dsp->fButton0);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "outGain", &dsp->fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "midi", "ctrl 1");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "pluckPosition", &dsp->fHslider1, 0.800000012f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	float fSlow0 = (float)dsp->fHslider0;
	float fSlow1 = (0.00100000005f * (float)dsp->fHslider1);
	float fSlow2 = (float)dsp->fHslider2;
	float fSlow3 = (340.0f / fSlow2);
	float fSlow4 = (float)dsp->fHslider3;
	float fSlow5 = min(1.0f, ((float)dsp->fButton0 + (float)dsp->fHslider4));
	int iSlow6 = (fSlow5 == 0.0f);
	float fSlow7 = (float)dsp->fHslider5;
	float fSlow8 = (dsp->fConst3 * fSlow2);
	float fSlow9 = (0.00033333333f * fSlow2);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->iRec10[0] = 0;
			int iRec11 = dsp->iRec10[1];
			float fRec14 = ((float)dsp->iRec6[1] - (0.997843683f * ((0.699999988f * dsp->fRec15[2]) + (0.150000006f * (dsp->fRec15[1] + dsp->fRec15[3])))));
			dsp->fRec29[0] = (fSlow1 + (0.999000013f * dsp->fRec29[1]));
			dsp->fVec0[0] = fSlow5;
			int iTemp0 = ((fSlow5 == dsp->fVec0[1]) | iSlow6);
			dsp->fRec30[0] = ((fSlow4 * (1.0f - (0.999000013f * (float)iTemp0))) + (0.999000013f * ((float)iTemp0 * dsp->fRec30[1])));
			float fTemp1 = ((fSlow3 / dsp->fRec30[0]) + -0.100000001f);
			float fTemp2 = (dsp->fConst2 * ((1.0f - dsp->fRec29[0]) * fTemp1));
			float fTemp3 = (fTemp2 + -1.49999499f);
			int iTemp4 = (int)fTemp3;
			int iTemp5 = (int)min(dsp->fConst1, (float)max(0, (int)iTemp4));
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
			int iTemp16 = (int)min(dsp->fConst1, (float)max(0, (int)(iTemp4 + 2)));
			float fTemp17 = (0.0f - fTemp11);
			float fTemp18 = (0.0f - (0.5f * fTemp13));
			int iTemp19 = (int)min(dsp->fConst1, (float)max(0, (int)(iTemp4 + 1)));
			float fTemp20 = (0.0f - fTemp9);
			float fTemp21 = (0.0f - (0.5f * fTemp11));
			float fTemp22 = (0.0f - (0.333333343f * fTemp13));
			float fTemp23 = (fTemp7 * fTemp9);
			int iTemp24 = (int)min(dsp->fConst1, (float)max(0, (int)(iTemp4 + 3)));
			float fTemp25 = (0.0f - fTemp13);
			float fTemp26 = (fTemp23 * fTemp11);
			int iTemp27 = (int)min(dsp->fConst1, (float)max(0, (int)(iTemp4 + 4)));
			dsp->fRec25[0] = (((((dsp->fRec2[((dsp->IOTA - (iTemp5 + 1)) & 2047)] * fTemp8) * fTemp10) * fTemp12) * fTemp14) + (fTemp15 * ((((0.5f * (((fTemp7 * dsp->fRec2[((dsp->IOTA - (iTemp16 + 1)) & 2047)]) * fTemp17) * fTemp18)) + (((dsp->fRec2[((dsp->IOTA - (iTemp19 + 1)) & 2047)] * fTemp20) * fTemp21) * fTemp22)) + (0.166666672f * ((fTemp23 * dsp->fRec2[((dsp->IOTA - (iTemp24 + 1)) & 2047)]) * fTemp25))) + (0.0416666679f * (fTemp26 * dsp->fRec2[((dsp->IOTA - (iTemp27 + 1)) & 2047)])))));
			dsp->fRec31[0] = ((0.0500000007f * dsp->fRec31[1]) + (0.949999988f * dsp->fRec25[1]));
			float fRec26 = dsp->fRec31[0];
			dsp->fRec33[0] = dsp->fRec0[1];
			dsp->fRec34[(dsp->IOTA & 2047)] = (0.0f - (0.997843683f * ((0.699999988f * dsp->fRec33[2]) + (0.150000006f * (dsp->fRec33[1] + dsp->fRec33[3])))));
			int iRec35 = 0;
			float fTemp28 = (dsp->fConst2 * (dsp->fRec29[0] * fTemp1));
			float fTemp29 = (fTemp28 + -1.49999499f);
			int iTemp30 = (int)fTemp29;
			int iTemp31 = (int)min(dsp->fConst1, (float)max(0, (int)iTemp30));
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
			int iTemp42 = (int)min(dsp->fConst1, (float)max(0, (int)(iTemp30 + 2)));
			float fTemp43 = (0.0f - fTemp37);
			float fTemp44 = (0.0f - (0.5f * fTemp39));
			int iTemp45 = (int)min(dsp->fConst1, (float)max(0, (int)(iTemp30 + 1)));
			float fTemp46 = (0.0f - fTemp35);
			float fTemp47 = (0.0f - (0.5f * fTemp37));
			float fTemp48 = (0.0f - (0.333333343f * fTemp39));
			float fTemp49 = (fTemp33 * fTemp35);
			int iTemp50 = (int)min(dsp->fConst1, (float)max(0, (int)(iTemp30 + 3)));
			float fTemp51 = (0.0f - fTemp39);
			float fTemp52 = (fTemp49 * fTemp37);
			int iTemp53 = (int)min(dsp->fConst1, (float)max(0, (int)(iTemp30 + 4)));
			dsp->fVec1[0] = (((((dsp->fRec34[((dsp->IOTA - (iTemp31 + 2)) & 2047)] * fTemp34) * fTemp36) * fTemp38) * fTemp40) + (fTemp41 * ((((0.5f * (((fTemp33 * dsp->fRec34[((dsp->IOTA - (iTemp42 + 2)) & 2047)]) * fTemp43) * fTemp44)) + (((dsp->fRec34[((dsp->IOTA - (iTemp45 + 2)) & 2047)] * fTemp46) * fTemp47) * fTemp48)) + (0.166666672f * ((fTemp49 * dsp->fRec34[((dsp->IOTA - (iTemp50 + 2)) & 2047)]) * fTemp51))) + (0.0416666679f * (fTemp52 * dsp->fRec34[((dsp->IOTA - (iTemp53 + 2)) & 2047)])))));
			dsp->iRec37[0] = ((1103515245 * dsp->iRec37[1]) + 12345);
			float fTemp54 = tanf((fSlow8 * dsp->fRec30[0]));
			float fTemp55 = (1.0f / fTemp54);
			float fTemp56 = (((fTemp55 + 1.41421354f) / fTemp54) + 1.0f);
			dsp->fRec36[0] = ((4.65661287e-10f * (float)dsp->iRec37[0]) - (((dsp->fRec36[2] * (((fTemp55 + -1.41421354f) / fTemp54) + 1.0f)) + (2.0f * (dsp->fRec36[1] * (1.0f - (1.0f / mydsp_faustpower2_f(fTemp54)))))) / fTemp56));
			float fTemp57 = mydsp_faustpower2_f((1.0f - (fSlow9 * dsp->fRec30[0])));
			dsp->fVec2[0] = fTemp57;
			float fTemp58 = (dsp->fConst4 * fTemp57);
			dsp->fRec38[0] = ((((fSlow5 - dsp->fVec0[1]) > 0.0f) > 0)?0.0f:min(fTemp58, ((dsp->fRec38[1] + (dsp->fConst4 * (fTemp57 - dsp->fVec2[1]))) + 1.0f)));
			float fTemp59 = (dsp->fConst5 * fTemp57);
			int iTemp60 = (dsp->fRec38[0] < fTemp59);
			float fTemp61 = (fSlow7 * (((dsp->fRec36[2] + (dsp->fRec36[0] + (2.0f * dsp->fRec36[1]))) * (iTemp60?((dsp->fRec38[0] < 0.0f)?0.0f:(iTemp60?(dsp->fConst6 * (dsp->fRec38[0] / fTemp57)):1.0f)):((dsp->fRec38[0] < fTemp58)?((dsp->fConst6 * ((0.0f - (dsp->fRec38[0] - fTemp59)) / fTemp57)) + 1.0f):0.0f))) / fTemp56));
			dsp->fVec3[0] = (dsp->fVec1[1] + fTemp61);
			dsp->fRec32[(dsp->IOTA & 2047)] = ((0.0500000007f * dsp->fRec32[((dsp->IOTA - 1) & 2047)]) + (0.949999988f * dsp->fVec3[1]));
			float fRec27 = (((((fTemp8 * fTemp10) * fTemp12) * fTemp14) * dsp->fRec32[((dsp->IOTA - iTemp5) & 2047)]) + (fTemp15 * ((0.0416666679f * (fTemp26 * dsp->fRec32[((dsp->IOTA - iTemp27) & 2047)])) + (((((fTemp20 * fTemp21) * fTemp22) * dsp->fRec32[((dsp->IOTA - iTemp19) & 2047)]) + (0.5f * (((fTemp7 * fTemp17) * fTemp18) * dsp->fRec32[((dsp->IOTA - iTemp16) & 2047)]))) + (0.166666672f * ((fTemp23 * fTemp25) * dsp->fRec32[((dsp->IOTA - iTemp24) & 2047)]))))));
			int iRec28 = iRec35;
			dsp->fRec21[0] = fRec26;
			float fRec22 = (fTemp61 + dsp->fRec21[1]);
			float fRec23 = fRec27;
			int iRec24 = iRec28;
			dsp->fRec17[(dsp->IOTA & 2047)] = fRec22;
			float fRec18 = (((((fTemp34 * fTemp36) * fTemp38) * fTemp40) * dsp->fRec17[((dsp->IOTA - (iTemp31 + 1)) & 2047)]) + (fTemp41 * (((0.166666672f * ((fTemp49 * fTemp51) * dsp->fRec17[((dsp->IOTA - (iTemp50 + 1)) & 2047)])) + ((((fTemp46 * fTemp47) * fTemp48) * dsp->fRec17[((dsp->IOTA - (iTemp45 + 1)) & 2047)]) + (0.5f * (((fTemp33 * fTemp43) * fTemp44) * dsp->fRec17[((dsp->IOTA - (iTemp42 + 1)) & 2047)])))) + (0.0416666679f * (fTemp52 * dsp->fRec17[((dsp->IOTA - (iTemp53 + 1)) & 2047)])))));
			dsp->fRec19[0] = fRec23;
			int iRec20 = iRec24;
			dsp->fRec15[0] = dsp->fRec19[1];
			int iRec16 = iRec20;
			float fRec12 = dsp->fRec15[1];
			float fRec13 = ((float)iRec16 + dsp->fRec15[1]);
			dsp->iRec6[0] = iRec11;
			float fRec7 = fRec14;
			float fRec8 = fRec12;
			float fRec9 = fRec13;
			dsp->fRec2[(dsp->IOTA & 2047)] = fRec7;
			float fRec3 = fRec18;
			float fRec4 = fRec8;
			float fRec5 = fRec9;
			dsp->fRec0[0] = fRec3;
			float fRec1 = fRec5;
			float fTemp62 = (fSlow0 * fRec1);
			output0[i] = (FAUSTFLOAT)fTemp62;
			output1[i] = (FAUSTFLOAT)fTemp62;
			dsp->iRec10[1] = dsp->iRec10[0];
			dsp->fRec29[1] = dsp->fRec29[0];
			dsp->fVec0[1] = dsp->fVec0[0];
			dsp->fRec30[1] = dsp->fRec30[0];
			dsp->fRec25[1] = dsp->fRec25[0];
			dsp->fRec31[1] = dsp->fRec31[0];
			/* C99 loop */
			{
				int j0;
				for (j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
					dsp->fRec33[j0] = dsp->fRec33[(j0 - 1)];
					
				}
				
			}
			dsp->IOTA = (dsp->IOTA + 1);
			dsp->fVec1[1] = dsp->fVec1[0];
			dsp->iRec37[1] = dsp->iRec37[0];
			dsp->fRec36[2] = dsp->fRec36[1];
			dsp->fRec36[1] = dsp->fRec36[0];
			dsp->fVec2[1] = dsp->fVec2[0];
			dsp->fRec38[1] = dsp->fRec38[0];
			dsp->fVec3[1] = dsp->fVec3[0];
			dsp->fRec21[1] = dsp->fRec21[0];
			dsp->fRec19[1] = dsp->fRec19[0];
			/* C99 loop */
			{
				int j1;
				for (j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
					dsp->fRec15[j1] = dsp->fRec15[(j1 - 1)];
					
				}
				
			}
			dsp->iRec6[1] = dsp->iRec6[0];
			dsp->fRec0[1] = dsp->fRec0[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
