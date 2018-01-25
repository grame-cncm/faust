/* ------------------------------------------------------------
name: "brass"
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
	float fRec13[2];
	float fRec14[2];
	FAUSTFLOAT fHslider0;
	float fRec19[2];
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	float fConst3;
	float fConst4;
	int iRec21[2];
	float fConst5;
	float fConst6;
	float fConst7;
	float fRec20[3];
	float fConst8;
	FAUSTFLOAT fHslider1;
	float fRec22[2];
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT fHslider4;
	float fRec23[2];
	float fRec18[3];
	float fVec0[2];
	float fRec17[2];
	int IOTA;
	float fRec15[2048];
	float fConst9;
	float fConst10;
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
	m->declare(m->metaInterface, "basics.lib/name", "Faust Basic Element Library");
	m->declare(m->metaInterface, "basics.lib/version", "0.0");
	m->declare(m->metaInterface, "delays.lib/name", "Faust Delay Library");
	m->declare(m->metaInterface, "delays.lib/version", "0.0");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "interface", "SmartKeyboard{  'Number of Keyboards':'2',  'Max Keyboard Polyphony':'0',  'Keyboard 0 - Number of Keys':'1',   'Keyboard 1 - Number of Keys':'3',  'Keyboard 0 - Send Freq':'0',   'Keyboard 1 - Send Freq':'0',  'Keyboard 0 - Piano Keyboard':'0',   'Keyboard 1 - Piano Keyboard':'0',  'Keyboard 0 - Send Key X':'1',  'Keyboard 1 - Send Key Status':'1',  'Keyboard 0 - Static Mode':'1',  'Keyboard 0 - Key 0 - Label':'Lips Tension',  'Keyboard 1 - Key 0 - Label':'P1',  'Keyboard 1 - Key 1 - Label':'P2',  'Keyboard 1 - Key 2 - Label':'P3' }");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "brass");
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
	dsp->fHslider0 = (FAUSTFLOAT)0.0f;
	dsp->fHslider1 = (FAUSTFLOAT)0.0f;
	dsp->fHslider2 = (FAUSTFLOAT)0.0f;
	dsp->fHslider3 = (FAUSTFLOAT)0.0f;
	dsp->fHslider4 = (FAUSTFLOAT)0.0f;
	
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
			dsp->fRec13[l1] = 0.0f;
			
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
			dsp->fRec19[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			dsp->iRec21[l4] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 3); l5 = (l5 + 1)) {
			dsp->fRec20[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			dsp->fRec22[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			dsp->fRec23[l7] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
			dsp->fRec18[l8] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			dsp->fVec0[l9] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			dsp->fRec17[l10] = 0.0f;
			
		}
		
	}
	dsp->IOTA = 0;
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 2048); l11 = (l11 + 1)) {
			dsp->fRec15[l11] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			dsp->fVec1[l12] = 0.0f;
			
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
	dsp->fConst1 = tanf((6283.18555f / dsp->fConst0));
	dsp->fConst2 = (1.0f / dsp->fConst1);
	dsp->fConst3 = (((dsp->fConst2 + 1.41421354f) / dsp->fConst1) + 1.0f);
	dsp->fConst4 = (0.00499999989f / dsp->fConst3);
	dsp->fConst5 = (1.0f / dsp->fConst3);
	dsp->fConst6 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(dsp->fConst1))));
	dsp->fConst7 = (((dsp->fConst2 + -1.41421354f) / dsp->fConst1) + 1.0f);
	dsp->fConst8 = (2136.28296f / dsp->fConst0);
	dsp->fConst9 = (0.00882352982f * dsp->fConst0);
	dsp->fConst10 = (0.00147058826f * dsp->fConst0);
	
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
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb0k0x", &dsp->fHslider1, 0.0f, 0.0f, 1.0f, 1.0f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb1k0status", &dsp->fHslider2, 0.0f, 0.0f, 1.0f, 1.0f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb1k1status", &dsp->fHslider3, 0.0f, 0.0f, 1.0f, 1.0f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb1k2status", &dsp->fHslider4, 0.0f, 0.0f, 1.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "acc", "1 1 -10 0 10");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "pressure", &dsp->fHslider0, 0.0f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	float fSlow0 = (0.00100000005f * (float)dsp->fHslider0);
	float fSlow1 = (0.00100000005f * (float)dsp->fHslider1);
	int iSlow2 = (int)min(1.0f, (float)dsp->fHslider2);
	int iSlow3 = (int)min(1.0f, (float)dsp->fHslider3);
	int iSlow4 = (iSlow3 == 1);
	int iSlow5 = ((iSlow2 == 0) & iSlow4);
	int iSlow6 = (int)min(1.0f, (float)dsp->fHslider4);
	int iSlow7 = (iSlow6 == 0);
	int iSlow8 = (iSlow2 == 1);
	int iSlow9 = (iSlow8 & (iSlow3 == 0));
	int iSlow10 = (iSlow8 & iSlow4);
	int iSlow11 = (iSlow6 == 1);
	float fSlow12 = (0.000772727246f / powf(2.0f, (0.0833333358f * (-21.0f - (float)((((((iSlow5 & iSlow7) + (2 * (iSlow9 & iSlow7))) + (3 * (iSlow10 & iSlow7))) + (4 * (iSlow5 & iSlow11))) + (5 * (iSlow9 & iSlow11))) + (6 * (iSlow10 & iSlow11)))))));
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->iRec6[0] = 0;
			dsp->fRec13[0] = (0.5f * (dsp->fRec13[1] + dsp->fRec11[1]));
			float fRec10 = (dsp->fRec13[0] + (float)dsp->iRec6[1]);
			dsp->fRec14[0] = dsp->fRec0[1];
			dsp->fRec19[0] = (fSlow0 + (0.999000013f * dsp->fRec19[1]));
			dsp->iRec21[0] = ((1103515245 * dsp->iRec21[1]) + 12345);
			dsp->fRec20[0] = ((4.65661287e-10f * (float)dsp->iRec21[0]) - (dsp->fConst5 * ((dsp->fConst6 * dsp->fRec20[1]) + (dsp->fConst7 * dsp->fRec20[2]))));
			float fTemp0 = (dsp->fRec19[0] * ((dsp->fConst4 * (dsp->fRec20[2] + (dsp->fRec20[0] + (2.0f * dsp->fRec20[1])))) + 1.0f));
			dsp->fRec22[0] = (fSlow1 + (0.999000013f * dsp->fRec22[1]));
			dsp->fRec23[0] = (fSlow12 + (0.999000013f * dsp->fRec23[1]));
			dsp->fRec18[0] = ((0.0299999993f * ((0.300000012f * fTemp0) - (0.850000024f * dsp->fRec14[1]))) - ((dsp->fRec18[1] * (0.0f - (1.99399996f * cosf((dsp->fConst8 * (powf(4.0f, ((2.0f * dsp->fRec22[0]) + -1.0f)) / dsp->fRec23[0])))))) + (0.994009018f * dsp->fRec18[2])));
			float fTemp1 = max(-1.0f, min(1.0f, mydsp_faustpower2_f(dsp->fRec18[0])));
			float fTemp2 = (0.850000024f * (dsp->fRec14[1] * (1.0f - fTemp1)));
			float fTemp3 = (0.300000012f * (fTemp0 * fTemp1));
			dsp->fVec0[0] = (fTemp3 + fTemp2);
			dsp->fRec17[0] = ((fTemp2 + ((0.995000005f * dsp->fRec17[1]) + fTemp3)) - dsp->fVec0[1]);
			dsp->fRec15[(dsp->IOTA & 2047)] = dsp->fRec17[0];
			int iRec16 = 0;
			float fTemp4 = (dsp->fConst10 * dsp->fRec23[0]);
			float fTemp5 = (fTemp4 + -1.49999499f);
			int iTemp6 = (int)fTemp5;
			int iTemp7 = ((int)min(dsp->fConst9, (float)max(0, (int)iTemp6)) + 1);
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
			int iTemp18 = ((int)min(dsp->fConst9, (float)max(0, (int)(iTemp6 + 2))) + 1);
			float fTemp19 = (0.0f - fTemp13);
			float fTemp20 = (0.0f - (0.5f * fTemp15));
			int iTemp21 = ((int)min(dsp->fConst9, (float)max(0, (int)(iTemp6 + 1))) + 1);
			float fTemp22 = (0.0f - fTemp11);
			float fTemp23 = (0.0f - (0.5f * fTemp13));
			float fTemp24 = (0.0f - (0.333333343f * fTemp15));
			float fTemp25 = (fTemp9 * fTemp11);
			int iTemp26 = ((int)min(dsp->fConst9, (float)max(0, (int)(iTemp6 + 3))) + 1);
			float fTemp27 = (0.0f - fTemp15);
			float fTemp28 = (fTemp25 * fTemp13);
			int iTemp29 = ((int)min(dsp->fConst9, (float)max(0, (int)(iTemp6 + 4))) + 1);
			dsp->fVec1[0] = (((((dsp->fRec15[((dsp->IOTA - iTemp7) & 2047)] * fTemp10) * fTemp12) * fTemp14) * fTemp16) + (fTemp17 * ((((0.5f * (((fTemp9 * dsp->fRec15[((dsp->IOTA - iTemp18) & 2047)]) * fTemp19) * fTemp20)) + (((dsp->fRec15[((dsp->IOTA - iTemp21) & 2047)] * fTemp22) * fTemp23) * fTemp24)) + (0.166666672f * ((fTemp25 * dsp->fRec15[((dsp->IOTA - iTemp26) & 2047)]) * fTemp27))) + (0.0416666679f * (fTemp28 * dsp->fRec15[((dsp->IOTA - iTemp29) & 2047)])))));
			dsp->fRec11[0] = dsp->fVec1[1];
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
			output0[i] = (FAUSTFLOAT)fRec1;
			output1[i] = (FAUSTFLOAT)fRec1;
			dsp->iRec6[1] = dsp->iRec6[0];
			dsp->fRec13[1] = dsp->fRec13[0];
			dsp->fRec14[1] = dsp->fRec14[0];
			dsp->fRec19[1] = dsp->fRec19[0];
			dsp->iRec21[1] = dsp->iRec21[0];
			dsp->fRec20[2] = dsp->fRec20[1];
			dsp->fRec20[1] = dsp->fRec20[0];
			dsp->fRec22[1] = dsp->fRec22[0];
			dsp->fRec23[1] = dsp->fRec23[0];
			dsp->fRec18[2] = dsp->fRec18[1];
			dsp->fRec18[1] = dsp->fRec18[0];
			dsp->fVec0[1] = dsp->fVec0[0];
			dsp->fRec17[1] = dsp->fRec17[0];
			dsp->IOTA = (dsp->IOTA + 1);
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
