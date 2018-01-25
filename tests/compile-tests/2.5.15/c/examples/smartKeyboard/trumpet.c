/* ------------------------------------------------------------
name: "trumpet"
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
	
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider0;
	float fRec2[2];
	FAUSTFLOAT fButton0;
	FAUSTFLOAT fHslider1;
	float fVec0[2];
	FAUSTFLOAT fHslider2;
	float fRec3[2];
	float fConst2;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT fHslider4;
	float fRec6[2];
	float fRec4[2];
	float fVec1[2];
	float fRec1[2];
	float fRec0[3];
	
} mydsp;

mydsp* newmydsp() { 
	mydsp* dsp = (mydsp*)malloc(sizeof(mydsp));
	return dsp;
}

void deletemydsp(mydsp* dsp) { 
	free(dsp);
}

void metadatamydsp(MetaGlue* m) { 
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "interface", "SmartKeyboard{  'Number of Keyboards':'5',  'Max Keyboard Polyphony':'1',  'Mono Mode':'1',  'Keyboard 0 - Number of Keys':'13',  'Keyboard 1 - Number of Keys':'13',  'Keyboard 2 - Number of Keys':'13',  'Keyboard 3 - Number of Keys':'13',  'Keyboard 4 - Number of Keys':'13',  'Keyboard 0 - Lowest Key':'77',  'Keyboard 1 - Lowest Key':'72',  'Keyboard 2 - Lowest Key':'67',  'Keyboard 3 - Lowest Key':'62',  'Keyboard 4 - Lowest Key':'57',  'Rounding Mode':'2',  'Keyboard 0 - Send Y':'1',  'Keyboard 1 - Send Y':'1',  'Keyboard 2 - Send Y':'1',  'Keyboard 3 - Send Y':'1',  'Keyboard 4 - Send Y':'1', }");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "trumpet");
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
	dsp->fHslider0 = (FAUSTFLOAT)1.0f;
	dsp->fButton0 = (FAUSTFLOAT)0.0f;
	dsp->fHslider1 = (FAUSTFLOAT)0.0f;
	dsp->fHslider2 = (FAUSTFLOAT)1.0f;
	dsp->fHslider3 = (FAUSTFLOAT)300.0f;
	dsp->fHslider4 = (FAUSTFLOAT)1.0f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			dsp->fRec2[l0] = 0.0f;
			
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
			dsp->fRec3[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			dsp->fRec6[l3] = 0.0f;
			
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
			dsp->fVec1[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			dsp->fRec1[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			dsp->fRec0[l7] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = (3.14159274f / dsp->fConst0);
	dsp->fConst2 = (1.0f / dsp->fConst0);
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "trumpet");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "midi", "pitchwheel");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "bend", &dsp->fHslider4, 1.0f, 0.0f, 10.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "freq", &dsp->fHslider3, 300.0f, 50.0f, 2000.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "gain", &dsp->fHslider2, 1.0f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->addButton(ui_interface->uiInterface, "gate", &dsp->fButton0);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "midi", "ctrl 64");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "sustain", &dsp->fHslider1, 0.0f, 0.0f, 1.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "midi", "ctrl 1");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "y", &dsp->fHslider0, 1.0f, 0.0f, 1.0f, 0.00100000005f);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	float fSlow0 = (0.00100000005f * (float)dsp->fHslider0);
	float fSlow1 = min(1.0f, ((float)dsp->fButton0 + (float)dsp->fHslider1));
	float fSlow2 = (0.00100000005f * (fSlow1 * (float)dsp->fHslider2));
	float fSlow3 = (float)dsp->fHslider3;
	float fSlow4 = (float)dsp->fHslider4;
	int iSlow5 = (fSlow1 == 0.0f);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->fRec2[0] = (fSlow0 + (0.999000013f * dsp->fRec2[1]));
			float fTemp0 = tanf((dsp->fConst1 * ((4000.0f * dsp->fRec2[0]) + 50.0f)));
			float fTemp1 = (1.0f / fTemp0);
			float fTemp2 = (fTemp1 + 1.0f);
			dsp->fVec0[0] = fSlow1;
			dsp->fRec3[0] = (fSlow2 + (0.999000013f * dsp->fRec3[1]));
			int iTemp3 = ((fSlow1 == dsp->fVec0[1]) | iSlow5);
			dsp->fRec6[0] = ((fSlow4 * (1.0f - (0.999000013f * (float)iTemp3))) + (0.999000013f * ((float)iTemp3 * dsp->fRec6[1])));
			float fTemp4 = max(1.00000001e-07f, fabsf((fSlow3 * dsp->fRec6[0])));
			float fTemp5 = (dsp->fRec4[1] + (dsp->fConst2 * fTemp4));
			float fTemp6 = (fTemp5 + -1.0f);
			int iTemp7 = (fTemp6 < 0.0f);
			dsp->fRec4[0] = (iTemp7?fTemp5:fTemp6);
			float fRec5 = (iTemp7?fTemp5:(fTemp5 + ((1.0f - (dsp->fConst0 / fTemp4)) * fTemp6)));
			float fTemp8 = (dsp->fRec3[0] * ((2.0f * fRec5) + -1.0f));
			dsp->fVec1[0] = fTemp8;
			dsp->fRec1[0] = ((dsp->fRec1[1] * (0.0f - ((1.0f - fTemp1) / fTemp2))) + ((fTemp8 + dsp->fVec1[1]) / fTemp2));
			float fTemp9 = (((fTemp1 + 1.0f) / fTemp0) + 1.0f);
			dsp->fRec0[0] = (dsp->fRec1[0] - (((dsp->fRec0[2] * (((fTemp1 + -1.0f) / fTemp0) + 1.0f)) + (2.0f * (dsp->fRec0[1] * (1.0f - (1.0f / mydsp_faustpower2_f(fTemp0)))))) / fTemp9));
			float fTemp10 = ((dsp->fRec0[2] + (dsp->fRec0[0] + (2.0f * dsp->fRec0[1]))) / fTemp9);
			output0[i] = (FAUSTFLOAT)fTemp10;
			output1[i] = (FAUSTFLOAT)fTemp10;
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fVec0[1] = dsp->fVec0[0];
			dsp->fRec3[1] = dsp->fRec3[0];
			dsp->fRec6[1] = dsp->fRec6[0];
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fVec1[1] = dsp->fVec1[0];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fRec0[2] = dsp->fRec0[1];
			dsp->fRec0[1] = dsp->fRec0[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
