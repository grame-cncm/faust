/* ------------------------------------------------------------
name: "dubDub"
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
	float fRec0[2];
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fButton0;
	float fVec0[2];
	float fRec2[2];
	float fConst3;
	FAUSTFLOAT fHslider1;
	float fRec5[2];
	float fRec3[2];
	float fConst4;
	FAUSTFLOAT fHslider2;
	float fConst5;
	FAUSTFLOAT fHslider3;
	float fVec1[2];
	float fRec6[2];
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
	m->declare(m->metaInterface, "basics.lib/name", "Faust Basic Element Library");
	m->declare(m->metaInterface, "basics.lib/version", "0.0");
	m->declare(m->metaInterface, "envelopes.lib/author", "GRAME");
	m->declare(m->metaInterface, "envelopes.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "envelopes.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "envelopes.lib/name", "Faust Envelope Library");
	m->declare(m->metaInterface, "envelopes.lib/version", "0.0");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "interface", "SmartKeyboard{  'Number of Keyboards':'1',  'Keyboard 0 - Number of Keys':'1',  'Keyboard 0 - Piano Keyboard':'0',  'Keyboard 0 - Static Mode':'1',  'Keyboard 0 - Send X':'1',  'Keyboard 0 - Send Y':'1' }");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "dubDub");
	m->declare(m->metaInterface, "oscillators.lib/name", "Faust Oscillator Library");
	m->declare(m->metaInterface, "oscillators.lib/version", "0.0");
	m->declare(m->metaInterface, "signals.lib/name", "Faust Signal Routing Library");
	m->declare(m->metaInterface, "signals.lib/version", "0.0");
	m->declare(m->metaInterface, "synths.lib/name", "Faust Synthesizer Library");
	m->declare(m->metaInterface, "synths.lib/version", "0.0");
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
	dsp->fButton0 = (FAUSTFLOAT)0.0f;
	dsp->fHslider1 = (FAUSTFLOAT)0.0f;
	dsp->fHslider2 = (FAUSTFLOAT)0.0f;
	dsp->fHslider3 = (FAUSTFLOAT)9.0f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			dsp->fRec0[l0] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			dsp->fVec0[l1] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			dsp->fRec2[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			dsp->fRec5[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			dsp->fRec3[l4] = 0.0f;
			
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
			dsp->fRec6[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			dsp->fRec1[l7] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = expf((0.0f - (100.0f / dsp->fConst0)));
	dsp->fConst2 = (1.0f - dsp->fConst1);
	dsp->fConst3 = (1.0f / dsp->fConst0);
	dsp->fConst4 = (3.14159274f / dsp->fConst0);
	dsp->fConst5 = (1.0f / dsp->fConst0);
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "dubDub");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "acc", "1 0 -10 0 10");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "gain", &dsp->fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->addButton(ui_interface->uiInterface, "gate", &dsp->fButton0);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "acc", "0 0 -10 0 10");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "modFeq", &dsp->fHslider3, 9.0f, 0.5f, 18.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "x", &dsp->fHslider1, 0.0f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "y", &dsp->fHslider2, 0.0f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	float fSlow0 = (0.00100000005f * mydsp_faustpower2_f((float)dsp->fHslider0));
	float fSlow1 = (float)dsp->fButton0;
	float fSlow2 = (dsp->fConst2 * fSlow1);
	float fSlow3 = ((420.0f * (float)dsp->fHslider1) + 80.0f);
	int iSlow4 = (fSlow1 == 0.0f);
	float fSlow5 = (1.0f - (float)dsp->fHslider2);
	float fSlow6 = (float)dsp->fHslider3;
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->fRec0[0] = (fSlow0 + (0.999000013f * dsp->fRec0[1]));
			dsp->fVec0[0] = fSlow1;
			dsp->fRec2[0] = (fSlow2 + (dsp->fConst1 * dsp->fRec2[1]));
			int iTemp0 = ((fSlow1 == dsp->fVec0[1]) | iSlow4);
			dsp->fRec5[0] = ((fSlow3 * (1.0f - (0.999000013f * (float)iTemp0))) + (0.999000013f * ((float)iTemp0 * dsp->fRec5[1])));
			float fTemp1 = max(1.00000001e-07f, fabsf(dsp->fRec5[0]));
			float fTemp2 = (dsp->fRec3[1] + (dsp->fConst3 * fTemp1));
			float fTemp3 = (fTemp2 + -1.0f);
			int iTemp4 = (fTemp3 < 0.0f);
			dsp->fRec3[0] = (iTemp4?fTemp2:fTemp3);
			float fRec4 = (iTemp4?fTemp2:(fTemp2 + ((1.0f - (dsp->fConst0 / fTemp1)) * fTemp3)));
			dsp->fVec1[0] = fSlow6;
			float fTemp5 = ((dsp->fConst5 * dsp->fVec1[1]) + dsp->fRec6[1]);
			dsp->fRec6[0] = (fTemp5 - floorf(fTemp5));
			float fTemp6 = tanf((dsp->fConst4 * ((4950.0f * (1.0f - (fSlow5 * (1.0f - fabsf(((2.0f * dsp->fRec6[0]) + -1.0f)))))) + 50.0f)));
			float fTemp7 = (1.0f / fTemp6);
			float fTemp8 = (((fTemp7 + 0.125f) / fTemp6) + 1.0f);
			dsp->fRec1[0] = ((0.5f * (dsp->fRec2[0] * ((2.0f * fRec4) + -1.0f))) - (((dsp->fRec1[2] * (((fTemp7 + -0.125f) / fTemp6) + 1.0f)) + (2.0f * (dsp->fRec1[1] * (1.0f - (1.0f / mydsp_faustpower2_f(fTemp6)))))) / fTemp8));
			float fTemp9 = ((dsp->fRec0[0] * (dsp->fRec1[2] + (dsp->fRec1[0] + (2.0f * dsp->fRec1[1])))) / fTemp8);
			output0[i] = (FAUSTFLOAT)fTemp9;
			output1[i] = (FAUSTFLOAT)fTemp9;
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fVec0[1] = dsp->fVec0[0];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec5[1] = dsp->fRec5[0];
			dsp->fRec3[1] = dsp->fRec3[0];
			dsp->fVec1[1] = dsp->fVec1[0];
			dsp->fRec6[1] = dsp->fRec6[0];
			dsp->fRec1[2] = dsp->fRec1[1];
			dsp->fRec1[1] = dsp->fRec1[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
