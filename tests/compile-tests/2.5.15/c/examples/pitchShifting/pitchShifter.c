/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2006"
license: "BSD"
name: "pitchShifter"
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
	
	int IOTA;
	float fVec0[131072];
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	float fRec0[2];
	FAUSTFLOAT fHslider2;
	int fSamplingFreq;
	
} mydsp;

mydsp* newmydsp() { 
	mydsp* dsp = (mydsp*)malloc(sizeof(mydsp));
	return dsp;
}

void deletemydsp(mydsp* dsp) { 
	free(dsp);
}

void metadatamydsp(MetaGlue* m) { 
	m->declare(m->metaInterface, "author", "Grame");
	m->declare(m->metaInterface, "copyright", "(c)GRAME 2006");
	m->declare(m->metaInterface, "delays.lib/name", "Faust Delay Library");
	m->declare(m->metaInterface, "delays.lib/version", "0.0");
	m->declare(m->metaInterface, "license", "BSD");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "misceffects.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "misceffects.lib/version", "2.0");
	m->declare(m->metaInterface, "name", "pitchShifter");
	m->declare(m->metaInterface, "version", "1.0");
}

int getSampleRatemydsp(mydsp* dsp) { return dsp->fSamplingFreq; }

int getNumInputsmydsp(mydsp* dsp) {
	return 1;
	
}
int getNumOutputsmydsp(mydsp* dsp) {
	return 1;
	
}
int getInputRatemydsp(mydsp* dsp, int channel) {
	int rate;
	switch (channel) {
		case 0: {
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
	dsp->fHslider0 = (FAUSTFLOAT)1000.0f;
	dsp->fHslider1 = (FAUSTFLOAT)0.0f;
	dsp->fHslider2 = (FAUSTFLOAT)10.0f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	dsp->IOTA = 0;
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 131072); l0 = (l0 + 1)) {
			dsp->fVec0[l0] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			dsp->fRec0[l1] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "Pitch Shifter");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "shift (semitones)", &dsp->fHslider1, 0.0f, -12.0f, 12.0f, 0.100000001f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "window (samples)", &dsp->fHslider0, 1000.0f, 50.0f, 10000.0f, 1.0f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "xfade (samples)", &dsp->fHslider2, 10.0f, 1.0f, 10000.0f, 1.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* input0 = inputs[0];
	FAUSTFLOAT* output0 = outputs[0];
	float fSlow0 = (float)dsp->fHslider0;
	float fSlow1 = powf(2.0f, (0.0833333358f * (float)dsp->fHslider1));
	float fSlow2 = (1.0f / (float)dsp->fHslider2);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = (float)input0[i];
			dsp->fVec0[(dsp->IOTA & 131071)] = fTemp0;
			dsp->fRec0[0] = fmodf((fSlow0 + ((dsp->fRec0[1] + 1.0f) - fSlow1)), fSlow0);
			int iTemp1 = (int)dsp->fRec0[0];
			float fTemp2 = floorf(dsp->fRec0[0]);
			float fTemp3 = (1.0f - dsp->fRec0[0]);
			float fTemp4 = min((fSlow2 * dsp->fRec0[0]), 1.0f);
			float fTemp5 = (fSlow0 + dsp->fRec0[0]);
			int iTemp6 = (int)fTemp5;
			float fTemp7 = floorf(fTemp5);
			output0[i] = (FAUSTFLOAT)((((dsp->fVec0[((dsp->IOTA - min(65537, max(0, iTemp1))) & 131071)] * (fTemp2 + fTemp3)) + ((dsp->fRec0[0] - fTemp2) * dsp->fVec0[((dsp->IOTA - min(65537, max(0, (iTemp1 + 1)))) & 131071)])) * fTemp4) + (((dsp->fVec0[((dsp->IOTA - min(65537, max(0, iTemp6))) & 131071)] * ((fTemp7 + fTemp3) - fSlow0)) + ((fSlow0 + (dsp->fRec0[0] - fTemp7)) * dsp->fVec0[((dsp->IOTA - min(65537, max(0, (iTemp6 + 1)))) & 131071)])) * (1.0f - fTemp4)));
			dsp->IOTA = (dsp->IOTA + 1);
			dsp->fRec0[1] = dsp->fRec0[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
