/* ------------------------------------------------------------
name: "harp"
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
	float fVec0[2];
	FAUSTFLOAT fHslider0;
	float fConst1;
	FAUSTFLOAT fHslider1;
	int iRec2[2];
	FAUSTFLOAT fButton0;
	float fVec1[2];
	float fConst2;
	float fRec3[2];
	float fConst3;
	int IOTA;
	float fVec2[2048];
	float fRec0[2];
	float fRec1[2];
	
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
	m->declare(m->metaInterface, "envelopes.lib/author", "GRAME");
	m->declare(m->metaInterface, "envelopes.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "envelopes.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "envelopes.lib/name", "Faust Envelope Library");
	m->declare(m->metaInterface, "envelopes.lib/version", "0.0");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "interface", "SmartKeyboard{  'Number of Keyboards':'8',  'Keyboard 0 - Number of Keys':'16',  'Keyboard 1 - Number of Keys':'16',  'Keyboard 2 - Number of Keys':'16',  'Keyboard 3 - Number of Keys':'16',  'Keyboard 4 - Number of Keys':'16',  'Keyboard 5 - Number of Keys':'16',  'Keyboard 6 - Number of Keys':'16',  'Keyboard 7 - Number of Keys':'16',  'Keyboard 0 - Lowest Key':'40',  'Keyboard 1 - Lowest Key':'45',  'Keyboard 2 - Lowest Key':'50',  'Keyboard 3 - Lowest Key':'55',  'Keyboard 4 - Lowest Key':'60',  'Keyboard 5 - Lowest Key':'65',  'Keyboard 6 - Lowest Key':'70',  'Keyboard 7 - Lowest Key':'75',  'Keyboard 0 - Piano Keyboard':'0',  'Keyboard 1 - Piano Keyboard':'0',  'Keyboard 2 - Piano Keyboard':'0',  'Keyboard 3 - Piano Keyboard':'0',  'Keyboard 4 - Piano Keyboard':'0',  'Keyboard 5 - Piano Keyboard':'0',  'Keyboard 6 - Piano Keyboard':'0',  'Keyboard 7 - Piano Keyboard':'0' }");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "harp");
	m->declare(m->metaInterface, "noises.lib/name", "Faust Noise Generator Library");
	m->declare(m->metaInterface, "noises.lib/version", "0.0");
	m->declare(m->metaInterface, "synths.lib/name", "Faust Synthesizer Library");
	m->declare(m->metaInterface, "synths.lib/version", "0.0");
}

int getSampleRatemydsp(mydsp* dsp) { return dsp->fSamplingFreq; }

int getNumInputsmydsp(mydsp* dsp) {
	return 0;
	
}
int getNumOutputsmydsp(mydsp* dsp) {
	return 1;
	
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
	dsp->fHslider0 = (FAUSTFLOAT)400.0f;
	dsp->fHslider1 = (FAUSTFLOAT)2.0f;
	dsp->fButton0 = (FAUSTFLOAT)0.0f;
	
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
			dsp->iRec2[l1] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			dsp->fVec1[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			dsp->fRec3[l3] = 0.0f;
			
		}
		
	}
	dsp->IOTA = 0;
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 2048); l4 = (l4 + 1)) {
			dsp->fVec2[l4] = 0.0f;
			
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
		for (l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			dsp->fRec1[l6] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = (1000.0f / dsp->fConst0);
	dsp->fConst2 = (0.00200000009f * dsp->fConst0);
	dsp->fConst3 = (0.00100000005f * dsp->fConst0);
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "harp");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "freq", &dsp->fHslider0, 400.0f, 50.0f, 2000.0f, 0.00999999978f);
	ui_interface->addButton(ui_interface->uiInterface, "gate", &dsp->fButton0);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "acc", "0 0 -10 0 10");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "res", &dsp->fHslider1, 2.0f, 0.100000001f, 4.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* output0 = outputs[0];
	float fSlow0 = (dsp->fConst0 / (float)dsp->fHslider0);
	float fSlow1 = (fSlow0 + -1.0f);
	float fSlow2 = floorf(fSlow1);
	float fSlow3 = (fSlow2 + (2.0f - fSlow0));
	float fSlow4 = expf((0.0f - (dsp->fConst1 / (float)dsp->fHslider1)));
	float fSlow5 = (float)dsp->fButton0;
	int iSlow6 = (int)fSlow1;
	int iSlow7 = min(1025, max(0, iSlow6));
	float fSlow8 = (fSlow0 + (-1.0f - fSlow2));
	int iSlow9 = min(1025, max(0, (iSlow6 + 1)));
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->fVec0[0] = dsp->fConst0;
			dsp->iRec2[0] = ((1103515245 * dsp->iRec2[1]) + 12345);
			dsp->fVec1[0] = fSlow5;
			dsp->fRec3[0] = ((((fSlow5 - dsp->fVec1[1]) > 0.0f) > 0)?0.0f:min(dsp->fConst2, ((dsp->fRec3[1] + (0.00200000009f * (dsp->fConst0 - dsp->fVec0[1]))) + 1.0f)));
			int iTemp0 = (dsp->fRec3[0] < dsp->fConst3);
			float fTemp1 = ((fSlow4 * dsp->fRec0[1]) + (4.65661287e-10f * ((float)dsp->iRec2[0] * (iTemp0?((dsp->fRec3[0] < 0.0f)?0.0f:(iTemp0?(dsp->fConst1 * dsp->fRec3[0]):1.0f)):((dsp->fRec3[0] < dsp->fConst2)?((dsp->fConst1 * (0.0f - (dsp->fRec3[0] - dsp->fConst3))) + 1.0f):0.0f)))));
			dsp->fVec2[(dsp->IOTA & 2047)] = fTemp1;
			dsp->fRec0[0] = ((fSlow3 * dsp->fVec2[((dsp->IOTA - iSlow7) & 2047)]) + (fSlow8 * dsp->fVec2[((dsp->IOTA - iSlow9) & 2047)]));
			dsp->fRec1[0] = fTemp1;
			output0[i] = (FAUSTFLOAT)dsp->fRec1[1];
			dsp->fVec0[1] = dsp->fVec0[0];
			dsp->iRec2[1] = dsp->iRec2[0];
			dsp->fVec1[1] = dsp->fVec1[0];
			dsp->fRec3[1] = dsp->fRec3[0];
			dsp->IOTA = (dsp->IOTA + 1);
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec1[1] = dsp->fRec1[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
