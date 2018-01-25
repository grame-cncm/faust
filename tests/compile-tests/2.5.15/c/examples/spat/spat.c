/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2006"
license: "BSD"
name: "spat"
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
	FAUSTFLOAT fHslider1;
	float fRec0[2];
	float fRec1[2];
	float fRec2[2];
	float fRec3[2];
	float fRec4[2];
	float fRec5[2];
	float fRec6[2];
	float fRec7[2];
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
	m->declare(m->metaInterface, "license", "BSD");
	m->declare(m->metaInterface, "name", "spat");
	m->declare(m->metaInterface, "signals.lib/name", "Faust Signal Routing Library");
	m->declare(m->metaInterface, "signals.lib/version", "0.0");
	m->declare(m->metaInterface, "spats.lib/name", "Faust Spatialization Library");
	m->declare(m->metaInterface, "spats.lib/version", "0.0");
	m->declare(m->metaInterface, "version", "1.0");
}

int getSampleRatemydsp(mydsp* dsp) { return dsp->fSamplingFreq; }

int getNumInputsmydsp(mydsp* dsp) {
	return 1;
	
}
int getNumOutputsmydsp(mydsp* dsp) {
	return 8;
	
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
		case 1: {
			rate = 1;
			break;
		}
		case 2: {
			rate = 1;
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
		case 5: {
			rate = 1;
			break;
		}
		case 6: {
			rate = 1;
			break;
		}
		case 7: {
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
	dsp->fHslider1 = (FAUSTFLOAT)0.0f;
	
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
			dsp->fRec1[l1] = 0.0f;
			
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
			dsp->fRec3[l3] = 0.0f;
			
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
			dsp->fRec5[l5] = 0.0f;
			
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
		for (l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			dsp->fRec7[l7] = 0.0f;
			
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "Spatializer 1x8");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "angle", &dsp->fHslider1, 0.0f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "distance", &dsp->fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* input0 = inputs[0];
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	FAUSTFLOAT* output2 = outputs[2];
	FAUSTFLOAT* output3 = outputs[3];
	FAUSTFLOAT* output4 = outputs[4];
	FAUSTFLOAT* output5 = outputs[5];
	FAUSTFLOAT* output6 = outputs[6];
	FAUSTFLOAT* output7 = outputs[7];
	float fSlow0 = (float)dsp->fHslider0;
	float fSlow1 = (fSlow0 + 1.0f);
	float fSlow2 = (float)dsp->fHslider1;
	float fSlow3 = (4.99999987e-05f * (fSlow1 * sqrtf(max(0.0f, (1.0f - (8.0f * (fSlow0 * fabsf((fmodf((fSlow2 + 1.5f), 1.0f) + -0.5f)))))))));
	float fSlow4 = (4.99999987e-05f * (fSlow1 * sqrtf(max(0.0f, (1.0f - (8.0f * (fSlow0 * fabsf((fmodf((fSlow2 + 1.375f), 1.0f) + -0.5f)))))))));
	float fSlow5 = (4.99999987e-05f * (fSlow1 * sqrtf(max(0.0f, (1.0f - (8.0f * (fSlow0 * fabsf((fmodf((fSlow2 + 1.25f), 1.0f) + -0.5f)))))))));
	float fSlow6 = (4.99999987e-05f * (fSlow1 * sqrtf(max(0.0f, (1.0f - (8.0f * (fSlow0 * fabsf((fmodf((fSlow2 + 1.125f), 1.0f) + -0.5f)))))))));
	float fSlow7 = (4.99999987e-05f * (fSlow1 * sqrtf(max(0.0f, (1.0f - (8.0f * (fSlow0 * fabsf((fmodf((fSlow2 + 1.0f), 1.0f) + -0.5f)))))))));
	float fSlow8 = (4.99999987e-05f * (fSlow1 * sqrtf(max(0.0f, (1.0f - (8.0f * (fSlow0 * fabsf((fmodf((fSlow2 + 0.875f), 1.0f) + -0.5f)))))))));
	float fSlow9 = (4.99999987e-05f * (fSlow1 * sqrtf(max(0.0f, (1.0f - (8.0f * (fSlow0 * fabsf((fmodf((fSlow2 + 0.75f), 1.0f) + -0.5f)))))))));
	float fSlow10 = (4.99999987e-05f * (fSlow1 * sqrtf(max(0.0f, (1.0f - (8.0f * (fSlow0 * fabsf((fmodf((fSlow2 + 0.625f), 1.0f) + -0.5f)))))))));
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = (float)input0[i];
			dsp->fRec0[0] = (fSlow3 + (0.999899983f * dsp->fRec0[1]));
			output0[i] = (FAUSTFLOAT)(fTemp0 * dsp->fRec0[0]);
			dsp->fRec1[0] = (fSlow4 + (0.999899983f * dsp->fRec1[1]));
			output1[i] = (FAUSTFLOAT)(fTemp0 * dsp->fRec1[0]);
			dsp->fRec2[0] = (fSlow5 + (0.999899983f * dsp->fRec2[1]));
			output2[i] = (FAUSTFLOAT)(fTemp0 * dsp->fRec2[0]);
			dsp->fRec3[0] = (fSlow6 + (0.999899983f * dsp->fRec3[1]));
			output3[i] = (FAUSTFLOAT)(fTemp0 * dsp->fRec3[0]);
			dsp->fRec4[0] = (fSlow7 + (0.999899983f * dsp->fRec4[1]));
			output4[i] = (FAUSTFLOAT)(fTemp0 * dsp->fRec4[0]);
			dsp->fRec5[0] = (fSlow8 + (0.999899983f * dsp->fRec5[1]));
			output5[i] = (FAUSTFLOAT)(fTemp0 * dsp->fRec5[0]);
			dsp->fRec6[0] = (fSlow9 + (0.999899983f * dsp->fRec6[1]));
			output6[i] = (FAUSTFLOAT)(fTemp0 * dsp->fRec6[0]);
			dsp->fRec7[0] = (fSlow10 + (0.999899983f * dsp->fRec7[1]));
			output7[i] = (FAUSTFLOAT)(fTemp0 * dsp->fRec7[0]);
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec3[1] = dsp->fRec3[0];
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fRec5[1] = dsp->fRec5[0];
			dsp->fRec6[1] = dsp->fRec6[0];
			dsp->fRec7[1] = dsp->fRec7[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
