/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2007"
license: "BSD"
name: "stereoEcho"
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
	
	FAUSTFLOAT fHslider0;
	int fSamplingFreq;
	float fConst0;
	FAUSTFLOAT fHslider1;
	int IOTA;
	float fRec0[131072];
	float fRec1[131072];
	
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
	m->declare(m->metaInterface, "basics.lib/name", "Faust Basic Element Library");
	m->declare(m->metaInterface, "basics.lib/version", "0.0");
	m->declare(m->metaInterface, "copyright", "(c)GRAME 2007");
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
	m->declare(m->metaInterface, "name", "stereoEcho");
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
	dsp->fHslider1 = (FAUSTFLOAT)0.0f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	dsp->IOTA = 0;
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 131072); l0 = (l0 + 1)) {
			dsp->fRec0[l0] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 131072); l1 = (l1 + 1)) {
			dsp->fRec1[l1] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = (0.00100000005f * min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq)));
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "stereo echo");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "echo  1000");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "feedback", &dsp->fHslider0, 0.0f, 0.0f, 100.0f, 0.100000001f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "millisecond", &dsp->fHslider1, 0.0f, 0.0f, 1000.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* input0 = inputs[0];
	FAUSTFLOAT* input1 = inputs[1];
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	float fSlow0 = (0.00999999978f * (float)dsp->fHslider0);
	int iSlow1 = (min(65536, max(0, ((int)(dsp->fConst0 * (float)dsp->fHslider1) + -1))) + 1);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->fRec0[(dsp->IOTA & 131071)] = ((float)input0[i] + (fSlow0 * dsp->fRec0[((dsp->IOTA - iSlow1) & 131071)]));
			output0[i] = (FAUSTFLOAT)dsp->fRec0[((dsp->IOTA - 0) & 131071)];
			dsp->fRec1[(dsp->IOTA & 131071)] = ((float)input1[i] + (fSlow0 * dsp->fRec1[((dsp->IOTA - iSlow1) & 131071)]));
			output1[i] = (FAUSTFLOAT)dsp->fRec1[((dsp->IOTA - 0) & 131071)];
			dsp->IOTA = (dsp->IOTA + 1);
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
