/* ------------------------------------------------------------
author: "Yann Orlarey"
copyright: "Grame"
license: "STK-4.3"
name: "smoothDelay"
version: "1.0"
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
	float fConst2;
	FAUSTFLOAT fHslider1;
	float fRec1[2];
	float fRec2[2];
	float fRec3[2];
	float fRec4[2];
	FAUSTFLOAT fHslider2;
	int IOTA;
	float fVec0[1048576];
	float fRec0[2];
	float fVec1[1048576];
	float fRec5[2];
	
} mydsp;

mydsp* newmydsp() { 
	mydsp* dsp = (mydsp*)malloc(sizeof(mydsp));
	return dsp;
}

void deletemydsp(mydsp* dsp) { 
	free(dsp);
}

void metadatamydsp(MetaGlue* m) { 
	m->declare(m->metaInterface, "author", "Yann Orlarey");
	m->declare(m->metaInterface, "basics.lib/name", "Faust Basic Element Library");
	m->declare(m->metaInterface, "basics.lib/version", "0.0");
	m->declare(m->metaInterface, "copyright", "Grame");
	m->declare(m->metaInterface, "delays.lib/name", "Faust Delay Library");
	m->declare(m->metaInterface, "delays.lib/version", "0.0");
	m->declare(m->metaInterface, "license", "STK-4.3");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "smoothDelay");
	m->declare(m->metaInterface, "signals.lib/name", "Faust Signal Routing Library");
	m->declare(m->metaInterface, "signals.lib/version", "0.0");
	m->declare(m->metaInterface, "version", "1.0");
}

int getSampleRatemydsp(mydsp* dsp) { return dsp->fSamplingFreq; }

int getNumInputsmydsp(mydsp* dsp) {
	return 2;
	
}
int getNumOutputsmydsp(mydsp* dsp) {
	return 2;
	
}
int getInputRatemydsp(mydsp* dsp, int channel) {
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
	dsp->fHslider1 = (FAUSTFLOAT)10.0f;
	dsp->fHslider2 = (FAUSTFLOAT)0.0f;
	
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
			dsp->fRec3[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			dsp->fRec4[l3] = 0.0f;
			
		}
		
	}
	dsp->IOTA = 0;
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 1048576); l4 = (l4 + 1)) {
			dsp->fVec0[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			dsp->fRec0[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 1048576); l6 = (l6 + 1)) {
			dsp->fVec1[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			dsp->fRec5[l7] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = (0.00100000005f * dsp->fConst0);
	dsp->fConst2 = (1000.0f / dsp->fConst0);
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "smoothDelay");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "unit", "ms");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "delay", &dsp->fHslider0, 0.0f, 0.0f, 5000.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "feedback", &dsp->fHslider2, 0.0f, 0.0f, 100.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "unit", "ms");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "interpolation", &dsp->fHslider1, 10.0f, 1.0f, 100.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* input0 = inputs[0];
	FAUSTFLOAT* input1 = inputs[1];
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	float fSlow0 = (dsp->fConst1 * (float)dsp->fHslider0);
	float fSlow1 = (dsp->fConst2 / (float)dsp->fHslider1);
	float fSlow2 = (0.0f - fSlow1);
	float fSlow3 = (0.00999999978f * (float)dsp->fHslider2);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = ((dsp->fRec1[1] != 0.0f)?(((dsp->fRec2[1] > 0.0f) & (dsp->fRec2[1] < 1.0f))?dsp->fRec1[1]:0.0f):(((dsp->fRec2[1] == 0.0f) & (fSlow0 != dsp->fRec3[1]))?fSlow1:(((dsp->fRec2[1] == 1.0f) & (fSlow0 != dsp->fRec4[1]))?fSlow2:0.0f)));
			dsp->fRec1[0] = fTemp0;
			dsp->fRec2[0] = max(0.0f, min(1.0f, (dsp->fRec2[1] + fTemp0)));
			dsp->fRec3[0] = (((dsp->fRec2[1] >= 1.0f) & (dsp->fRec4[1] != fSlow0))?fSlow0:dsp->fRec3[1]);
			dsp->fRec4[0] = (((dsp->fRec2[1] <= 0.0f) & (dsp->fRec3[1] != fSlow0))?fSlow0:dsp->fRec4[1]);
			float fTemp1 = (1.0f - dsp->fRec2[0]);
			float fTemp2 = ((float)input0[i] + (fSlow3 * dsp->fRec0[1]));
			dsp->fVec0[(dsp->IOTA & 1048575)] = fTemp2;
			int iTemp3 = (int)min(524288.0f, max(0.0f, dsp->fRec3[0]));
			int iTemp4 = (int)min(524288.0f, max(0.0f, dsp->fRec4[0]));
			dsp->fRec0[0] = ((fTemp1 * dsp->fVec0[((dsp->IOTA - iTemp3) & 1048575)]) + (dsp->fRec2[0] * dsp->fVec0[((dsp->IOTA - iTemp4) & 1048575)]));
			output0[i] = (FAUSTFLOAT)dsp->fRec0[0];
			float fTemp5 = ((float)input1[i] + (fSlow3 * dsp->fRec5[1]));
			dsp->fVec1[(dsp->IOTA & 1048575)] = fTemp5;
			dsp->fRec5[0] = ((fTemp1 * dsp->fVec1[((dsp->IOTA - iTemp3) & 1048575)]) + (dsp->fRec2[0] * dsp->fVec1[((dsp->IOTA - iTemp4) & 1048575)]));
			output1[i] = (FAUSTFLOAT)dsp->fRec5[0];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec3[1] = dsp->fRec3[0];
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->IOTA = (dsp->IOTA + 1);
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec5[1] = dsp->fRec5[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
