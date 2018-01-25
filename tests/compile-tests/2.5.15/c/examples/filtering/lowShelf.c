/* ------------------------------------------------------------
name: "lowShelf"
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
	FAUSTFLOAT fHslider2;
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
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "maxmsp.lib/author", "GRAME");
	m->declare(m->metaInterface, "maxmsp.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maxmsp.lib/license", "LGPL");
	m->declare(m->metaInterface, "maxmsp.lib/name", "MaxMSP compatibility Library");
	m->declare(m->metaInterface, "maxmsp.lib/version", "1.1");
	m->declare(m->metaInterface, "name", "lowShelf");
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
	dsp->fHslider0 = (FAUSTFLOAT)0.0f;
	dsp->fHslider1 = (FAUSTFLOAT)1000.0f;
	dsp->fHslider2 = (FAUSTFLOAT)1.0f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 3); l0 = (l0 + 1)) {
			dsp->fRec0[l0] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = (6.28318548f / min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq)));
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "lowShelf");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Freq", &dsp->fHslider1, 1000.0f, 100.0f, 10000.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "unit", "dB");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Gain", &dsp->fHslider0, 0.0f, -10.0f, 10.0f, 0.100000001f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Q", &dsp->fHslider2, 1.0f, 0.00999999978f, 100.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* input0 = inputs[0];
	FAUSTFLOAT* output0 = outputs[0];
	float fSlow0 = powf(10.0f, (0.0250000004f * (float)dsp->fHslider0));
	float fSlow1 = (dsp->fConst0 * max(0.0f, (float)dsp->fHslider1));
	float fSlow2 = cosf(fSlow1);
	float fSlow3 = ((fSlow0 + -1.0f) * fSlow2);
	float fSlow4 = (fSlow0 + fSlow3);
	float fSlow5 = ((sqrtf(fSlow0) * sinf(fSlow1)) / max(0.00100000005f, (float)dsp->fHslider2));
	float fSlow6 = ((fSlow4 + fSlow5) + 1.0f);
	float fSlow7 = (fSlow0 / fSlow6);
	float fSlow8 = ((fSlow0 + fSlow5) + (1.0f - fSlow3));
	float fSlow9 = (1.0f / fSlow6);
	float fSlow10 = ((fSlow0 + 1.0f) * fSlow2);
	float fSlow11 = (0.0f - (2.0f * ((fSlow0 + fSlow10) + -1.0f)));
	float fSlow12 = (fSlow4 + (1.0f - fSlow5));
	float fSlow13 = (2.0f * (fSlow0 + (-1.0f - fSlow10)));
	float fSlow14 = (fSlow0 + (1.0f - (fSlow3 + fSlow5)));
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->fRec0[0] = ((float)input0[i] - (fSlow9 * ((fSlow11 * dsp->fRec0[1]) + (fSlow12 * dsp->fRec0[2]))));
			output0[i] = (FAUSTFLOAT)(fSlow7 * (((fSlow8 * dsp->fRec0[0]) + (fSlow13 * dsp->fRec0[1])) + (fSlow14 * dsp->fRec0[2])));
			dsp->fRec0[2] = dsp->fRec0[1];
			dsp->fRec0[1] = dsp->fRec0[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
