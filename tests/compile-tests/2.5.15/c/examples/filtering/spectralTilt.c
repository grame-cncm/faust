/* ------------------------------------------------------------
name: "spectralTilt"
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
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	float fConst2;
	float fVec0[2];
	float fRec1[2];
	float fVec1[2];
	float fRec0[2];
	
} mydsp;

mydsp* newmydsp() { 
	mydsp* dsp = (mydsp*)malloc(sizeof(mydsp));
	return dsp;
}

void deletemydsp(mydsp* dsp) { 
	free(dsp);
}

void metadatamydsp(MetaGlue* m) { 
	m->declare(m->metaInterface, "description", "Demonstrate the Spectral Tilt effect on test signals");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "spectralTilt");
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
	dsp->fHslider0 = (FAUSTFLOAT)100.0f;
	dsp->fHslider1 = (FAUSTFLOAT)5000.0f;
	dsp->fHslider2 = (FAUSTFLOAT)-0.5f;
	
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
			dsp->fRec1[l1] = 0.0f;
			
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
			dsp->fRec0[l3] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = (3.14159274f / dsp->fConst0);
	dsp->fConst2 = (1.0f / tanf((0.5f / dsp->fConst0)));
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "spectralTilt");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "1", "");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Slope of Spectral Tilt across Band", &dsp->fHslider2, -0.5f, -1.0f, 1.0f, 0.00100000005f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "unit", "Hz");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Band Start Frequency", &dsp->fHslider0, 100.0f, 20.0f, 10000.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "unit", "Hz");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Band Width", &dsp->fHslider1, 5000.0f, 100.0f, 10000.0f, 1.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* input0 = inputs[0];
	FAUSTFLOAT* output0 = outputs[0];
	float fSlow0 = (float)dsp->fHslider0;
	float fSlow1 = powf(((fSlow0 + (float)dsp->fHslider1) / fSlow0), 1.0f);
	float fSlow2 = tanf((dsp->fConst1 * (fSlow0 * fSlow1)));
	float fSlow3 = (float)dsp->fHslider2;
	float fSlow4 = tanf((dsp->fConst1 * (fSlow0 * powf(fSlow1, (1.0f - fSlow3)))));
	float fSlow5 = (fSlow2 / fSlow4);
	float fSlow6 = tanf((dsp->fConst1 * fSlow0));
	float fSlow7 = (6.28318548f * ((fSlow0 * fSlow2) / fSlow6));
	float fSlow8 = (dsp->fConst2 + fSlow7);
	float fSlow9 = (0.0f - ((fSlow7 - dsp->fConst2) / fSlow8));
	float fSlow10 = (1.0f / fSlow8);
	float fSlow11 = (6.28318548f * ((fSlow0 * fSlow4) / fSlow6));
	float fSlow12 = (fSlow11 - dsp->fConst2);
	float fSlow13 = tanf((dsp->fConst1 * (fSlow0 * powf(fSlow1, (0.0f - fSlow3)))));
	float fSlow14 = (fSlow6 / fSlow13);
	float fSlow15 = (6.28318548f * fSlow0);
	float fSlow16 = (dsp->fConst2 + fSlow15);
	float fSlow17 = (0.0f - ((fSlow15 - dsp->fConst2) / fSlow16));
	float fSlow18 = (1.0f / fSlow16);
	float fSlow19 = (6.28318548f * ((fSlow0 * fSlow13) / fSlow6));
	float fSlow20 = (dsp->fConst2 + fSlow19);
	float fSlow21 = (fSlow19 - dsp->fConst2);
	float fSlow22 = ((fSlow6 * (dsp->fConst2 + fSlow11)) / fSlow13);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = (float)input0[i];
			dsp->fVec0[0] = fTemp0;
			dsp->fRec1[0] = ((fSlow17 * dsp->fRec1[1]) + (fSlow18 * ((fSlow20 * fTemp0) + (fSlow21 * dsp->fVec0[1]))));
			dsp->fVec1[0] = (fSlow14 * dsp->fRec1[0]);
			dsp->fRec0[0] = ((fSlow9 * dsp->fRec0[1]) + (fSlow10 * ((fSlow12 * dsp->fVec1[1]) + (fSlow22 * dsp->fRec1[0]))));
			output0[i] = (FAUSTFLOAT)(fSlow5 * dsp->fRec0[0]);
			dsp->fVec0[1] = dsp->fVec0[0];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fVec1[1] = dsp->fVec1[0];
			dsp->fRec0[1] = dsp->fRec0[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
