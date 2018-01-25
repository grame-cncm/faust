/* ------------------------------------------------------------
name: "toy"
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
	float fRec1[2];
	int fSamplingFreq;
	float fConst0;
	FAUSTFLOAT fHslider1;
	float fRec2[2];
	float fConst1;
	FAUSTFLOAT fHslider2;
	float fRec5[2];
	float fVec0[2];
	float fRec4[2];
	float fConst2;
	FAUSTFLOAT fHslider3;
	float fRec6[2];
	FAUSTFLOAT fHslider4;
	float fRec7[2];
	float fRec3[3];
	int IOTA;
	float fRec0[131072];
	FAUSTFLOAT fHslider5;
	float fRec8[2];
	
} mydsp;

mydsp* newmydsp() { 
	mydsp* dsp = (mydsp*)malloc(sizeof(mydsp));
	return dsp;
}

void deletemydsp(mydsp* dsp) { 
	free(dsp);
}

void metadatamydsp(MetaGlue* m) { 
	m->declare(m->metaInterface, "delays.lib/name", "Faust Delay Library");
	m->declare(m->metaInterface, "delays.lib/version", "0.0");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "interface", "SmartKeyboard{  'Number of Keyboards':'1',  'Max Keyboard Polyphony':'0',  'Keyboard 0 - Number of Keys':'1',  'Keyboard 0 - Send Freq':'0',  'Keyboard 0 - Static Mode':'1',  'Keyboard 0 - Piano Keyboard':'0',  'Keyboard 0 - Send Numbered X':'1',  'Keyboard 0 - Send Numbered Y':'1' }");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "misceffects.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "misceffects.lib/version", "2.0");
	m->declare(m->metaInterface, "name", "toy");
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
	
}

void instanceResetUserInterfacemydsp(mydsp* dsp) {
	dsp->fHslider0 = (FAUSTFLOAT)0.5f;
	dsp->fHslider1 = (FAUSTFLOAT)0.5f;
	dsp->fHslider2 = (FAUSTFLOAT)0.5f;
	dsp->fHslider3 = (FAUSTFLOAT)0.5f;
	dsp->fHslider4 = (FAUSTFLOAT)30.0f;
	dsp->fHslider5 = (FAUSTFLOAT)0.0f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			dsp->fRec1[l0] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			dsp->fRec2[l1] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			dsp->fRec5[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			dsp->fVec0[l3] = 0.0f;
			
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
			dsp->fRec6[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			dsp->fRec7[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			dsp->fRec3[l7] = 0.0f;
			
		}
		
	}
	dsp->IOTA = 0;
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 131072); l8 = (l8 + 1)) {
			dsp->fRec0[l8] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			dsp->fRec8[l9] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = (1.0f / dsp->fConst0);
	dsp->fConst2 = (3.14159274f / dsp->fConst0);
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "toy");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "acc", "0 0 -10 0 10");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "del", &dsp->fHslider1, 0.5f, 0.00999999978f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "acc", "1 0 -10 0 10");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "fb", &dsp->fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "acc", "0 0 -10 0 10");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "q", &dsp->fHslider4, 30.0f, 10.0f, 50.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "x0", &dsp->fHslider2, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "y0", &dsp->fHslider3, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "y1", &dsp->fHslider5, 0.0f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	float fSlow0 = (0.00100000005f * (float)dsp->fHslider0);
	float fSlow1 = (0.00100000005f * (float)dsp->fHslider1);
	float fSlow2 = (0.00100000005f * (float)dsp->fHslider2);
	float fSlow3 = (0.00100000005f * (float)dsp->fHslider3);
	float fSlow4 = (0.00100000005f * (float)dsp->fHslider4);
	float fSlow5 = (0.00100000005f * (float)dsp->fHslider5);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->fRec1[0] = (fSlow0 + (0.999000013f * dsp->fRec1[1]));
			dsp->fRec2[0] = (fSlow1 + (0.999000013f * dsp->fRec2[1]));
			dsp->fRec5[0] = (fSlow2 + (0.999000013f * dsp->fRec5[1]));
			dsp->fVec0[0] = ((20.0f * dsp->fRec5[0]) + 2.0f);
			float fTemp0 = (dsp->fRec4[1] + (dsp->fConst1 * dsp->fVec0[1]));
			dsp->fRec4[0] = (fTemp0 - floorf(fTemp0));
			dsp->fRec6[0] = (fSlow3 + (0.999000013f * dsp->fRec6[1]));
			float fTemp1 = tanf((dsp->fConst2 * ((3000.0f * dsp->fRec6[0]) + 300.0f)));
			float fTemp2 = (1.0f / fTemp1);
			dsp->fRec7[0] = (fSlow4 + (0.999000013f * dsp->fRec7[1]));
			float fTemp3 = (1.0f / dsp->fRec7[0]);
			float fTemp4 = (((fTemp2 + fTemp3) / fTemp1) + 1.0f);
			dsp->fRec3[0] = ((float)((dsp->fRec4[0] - dsp->fRec4[1]) < 0.0f) - (((dsp->fRec3[2] * (((fTemp2 - fTemp3) / fTemp1) + 1.0f)) + (2.0f * (dsp->fRec3[1] * (1.0f - (1.0f / mydsp_faustpower2_f(fTemp1)))))) / fTemp4));
			dsp->fRec0[(dsp->IOTA & 131071)] = ((dsp->fRec1[0] * dsp->fRec0[((dsp->IOTA - ((int)min(65536.0f, max(0.0f, (dsp->fConst0 * dsp->fRec2[0]))) + 1)) & 131071)]) + ((dsp->fRec3[2] + (dsp->fRec3[0] + (2.0f * dsp->fRec3[1]))) / fTemp4));
			dsp->fRec8[0] = (fSlow5 + (0.999000013f * dsp->fRec8[1]));
			float fTemp5 = max(-1.0f, min(1.0f, (dsp->fRec0[((dsp->IOTA - 0) & 131071)] * powf(10.0f, (2.0f * dsp->fRec8[0])))));
			float fTemp6 = (0.949999988f * (fTemp5 * (1.0f - (0.333333343f * mydsp_faustpower2_f(fTemp5)))));
			output0[i] = (FAUSTFLOAT)fTemp6;
			output1[i] = (FAUSTFLOAT)fTemp6;
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec5[1] = dsp->fRec5[0];
			dsp->fVec0[1] = dsp->fVec0[0];
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fRec6[1] = dsp->fRec6[0];
			dsp->fRec7[1] = dsp->fRec7[0];
			dsp->fRec3[2] = dsp->fRec3[1];
			dsp->fRec3[1] = dsp->fRec3[0];
			dsp->IOTA = (dsp->IOTA + 1);
			dsp->fRec8[1] = dsp->fRec8[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
