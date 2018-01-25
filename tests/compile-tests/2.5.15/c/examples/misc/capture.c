/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2006"
license: "BSD"
name: "capture"
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
	
	FAUSTFLOAT fButton0;
	int IOTA;
	float fVec0[1048576];
	int iVec1[2];
	int iRec1[2];
	float fRec0[2];
	FAUSTFLOAT fHslider0;
	float fRec2[2];
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
	m->declare(m->metaInterface, "basics.lib/name", "Faust Basic Element Library");
	m->declare(m->metaInterface, "basics.lib/version", "0.0");
	m->declare(m->metaInterface, "copyright", "(c)GRAME 2006");
	m->declare(m->metaInterface, "delays.lib/name", "Faust Delay Library");
	m->declare(m->metaInterface, "delays.lib/version", "0.0");
	m->declare(m->metaInterface, "license", "BSD");
	m->declare(m->metaInterface, "name", "capture");
	m->declare(m->metaInterface, "signals.lib/name", "Faust Signal Routing Library");
	m->declare(m->metaInterface, "signals.lib/version", "0.0");
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
	dsp->fButton0 = (FAUSTFLOAT)0.0f;
	dsp->fHslider0 = (FAUSTFLOAT)0.0f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	dsp->IOTA = 0;
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 1048576); l0 = (l0 + 1)) {
			dsp->fVec0[l0] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			dsp->iVec1[l1] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			dsp->iRec1[l2] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			dsp->fRec0[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			dsp->fRec2[l4] = 0.0f;
			
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "Audio Capture");
	ui_interface->addButton(ui_interface->uiInterface, "Capture", &dsp->fButton0);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "level (db)", &dsp->fHslider0, 0.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* input0 = inputs[0];
	FAUSTFLOAT* output0 = outputs[0];
	float fSlow0 = (float)dsp->fButton0;
	float fSlow1 = (1.0f - fSlow0);
	int iSlow2 = (int)fSlow0;
	float fSlow3 = (0.00100000005f * powf(10.0f, (0.0500000007f * (float)dsp->fHslider0)));
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->fVec0[(dsp->IOTA & 1048575)] = ((fSlow1 * dsp->fRec0[1]) + (fSlow0 * (float)input0[i]));
			dsp->iVec1[0] = iSlow2;
			dsp->iRec1[0] = ((iSlow2 + dsp->iRec1[1]) * ((iSlow2 - dsp->iVec1[1]) <= 0));
			dsp->fRec0[0] = dsp->fVec0[((dsp->IOTA - min(524288, (int)max(0, (int)(dsp->iRec1[0] + -1)))) & 1048575)];
			dsp->fRec2[0] = (fSlow3 + (0.999000013f * dsp->fRec2[1]));
			output0[i] = (FAUSTFLOAT)(dsp->fRec0[0] * dsp->fRec2[0]);
			dsp->IOTA = (dsp->IOTA + 1);
			dsp->iVec1[1] = dsp->iVec1[0];
			dsp->iRec1[1] = dsp->iRec1[0];
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec2[1] = dsp->fRec2[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
