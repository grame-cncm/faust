/* ------------------------------------------------------------
author: "RM"
name: "reverbTester"
version: "0.0"
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
	float fVec0[2];
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fButton1;
	float fVec1[2];
	FAUSTFLOAT fCheckbox1;
	int iRec1[2];
	float fRec0[4];
	FAUSTFLOAT fButton2;
	float fVec2[2];
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
	m->declare(m->metaInterface, "author", "RM");
	m->declare(m->metaInterface, "basics.lib/name", "Faust Basic Element Library");
	m->declare(m->metaInterface, "basics.lib/version", "0.0");
	m->declare(m->metaInterface, "description", "Handy test inputs for reverberator demos below.");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "reverbTester");
	m->declare(m->metaInterface, "noises.lib/name", "Faust Noise Generator Library");
	m->declare(m->metaInterface, "noises.lib/version", "0.0");
	m->declare(m->metaInterface, "version", "0.0");
}

int getSampleRatemydsp(mydsp* dsp) { return dsp->fSamplingFreq; }

int getNumInputsmydsp(mydsp* dsp) {
	return 5;
	
}
int getNumOutputsmydsp(mydsp* dsp) {
	return 2;
	
}
int getInputRatemydsp(mydsp* dsp, int channel) {
	int rate;
	switch (channel) {
		case 0: {
			rate = 0;
			break;
		}
		case 1: {
			rate = 0;
			break;
		}
		case 2: {
			rate = 0;
			break;
		}
		case 3: {
			rate = 1;
			break;
		}
		case 4: {
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
	dsp->fButton0 = (FAUSTFLOAT)0.0f;
	dsp->fCheckbox0 = (FAUSTFLOAT)0.0f;
	dsp->fButton1 = (FAUSTFLOAT)0.0f;
	dsp->fCheckbox1 = (FAUSTFLOAT)0.0f;
	dsp->fButton2 = (FAUSTFLOAT)0.0f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			dsp->fVec0[l0] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			dsp->fVec1[l1] = 0.0f;
			
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
		for (l3 = 0; (l3 < 4); l3 = (l3 + 1)) {
			dsp->fRec0[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			dsp->fVec2[l4] = 0.0f;
			
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "reverbTester");
	ui_interface->declare(ui_interface->uiInterface, 0, "1", "");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "Input Config");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox0, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox0, "tooltip", "When this is checked, the stereo external audio inputs are   disabled (good for hearing the impulse response or pink-noise response alone)");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Mute Ext Inputs", &dsp->fCheckbox0);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox1, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox1, "tooltip", "Pink Noise (or 1/f noise) is Constant-Q Noise (useful for adjusting   the EQ sections)");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Pink Noise", &dsp->fCheckbox1);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "2", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "Impulse Selection");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fButton1, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fButton1, "tooltip", "Send impulse into LEFT channel");
	ui_interface->addButton(ui_interface->uiInterface, "Left", &dsp->fButton1);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fButton0, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fButton0, "tooltip", "Send impulse into LEFT and RIGHT channels");
	ui_interface->addButton(ui_interface->uiInterface, "Center", &dsp->fButton0);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fButton2, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fButton2, "tooltip", "Send impulse into RIGHT channel");
	ui_interface->addButton(ui_interface->uiInterface, "Right", &dsp->fButton2);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* input0 = inputs[0];
	FAUSTFLOAT* input1 = inputs[1];
	FAUSTFLOAT* input2 = inputs[2];
	FAUSTFLOAT* input3 = inputs[3];
	FAUSTFLOAT* input4 = inputs[4];
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	float fSlow0 = (float)dsp->fButton0;
	float fSlow1 = (1.0f - (float)dsp->fCheckbox0);
	float fSlow2 = (float)dsp->fButton1;
	float fSlow3 = (0.100000001f * (float)dsp->fCheckbox1);
	float fSlow4 = (float)dsp->fButton2;
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->fVec0[0] = fSlow0;
			int iTemp0 = ((fSlow0 - dsp->fVec0[1]) > 0.0f);
			dsp->fVec1[0] = fSlow2;
			dsp->iRec1[0] = ((1103515245 * dsp->iRec1[1]) + 12345);
			dsp->fRec0[0] = (((0.522189379f * dsp->fRec0[3]) + ((4.65661287e-10f * (float)dsp->iRec1[0]) + (2.49495602f * dsp->fRec0[1]))) - (2.0172658f * dsp->fRec0[2]));
			float fTemp1 = (fSlow3 * (((0.0499220341f * dsp->fRec0[0]) + (0.0506126992f * dsp->fRec0[2])) - ((0.0959935337f * dsp->fRec0[1]) + (0.00440878607f * dsp->fRec0[3]))));
			output0[i] = (FAUSTFLOAT)(((float)iTemp0 + ((fSlow1 * (float)input3[i]) + (float)((fSlow2 - dsp->fVec1[1]) > 0.0f))) + fTemp1);
			dsp->fVec2[0] = fSlow4;
			output1[i] = (FAUSTFLOAT)((float)((fSlow4 - dsp->fVec2[1]) > 0.0f) + ((fSlow1 * (float)input4[i]) + ((float)iTemp0 + fTemp1)));
			dsp->fVec0[1] = dsp->fVec0[0];
			dsp->fVec1[1] = dsp->fVec1[0];
			dsp->iRec1[1] = dsp->iRec1[0];
			/* C99 loop */
			{
				int j0;
				for (j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
					dsp->fRec0[j0] = dsp->fRec0[(j0 - 1)];
					
				}
				
			}
			dsp->fVec2[1] = dsp->fVec2[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
