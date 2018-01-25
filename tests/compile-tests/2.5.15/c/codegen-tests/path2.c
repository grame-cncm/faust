/* ------------------------------------------------------------
name: "path2"
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
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT fHslider4;
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
	m->declare(m->metaInterface, "name", "path2");
}

int getSampleRatemydsp(mydsp* dsp) { return dsp->fSamplingFreq; }

int getNumInputsmydsp(mydsp* dsp) {
	return 4;
	
}
int getNumOutputsmydsp(mydsp* dsp) {
	return 4;
	
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
		case 2: {
			rate = 1;
			break;
		}
		case 3: {
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
	dsp->fHslider2 = (FAUSTFLOAT)0.0f;
	dsp->fHslider3 = (FAUSTFLOAT)0.0f;
	dsp->fHslider4 = (FAUSTFLOAT)0.0f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	
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
	ui_interface->openTabBox(ui_interface->uiInterface, "toto");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "common", &dsp->fHslider1, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "foo 0");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "slid", &dsp->fHslider0, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "foo 1");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "slid", &dsp->fHslider2, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "foo 2");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "slid", &dsp->fHslider3, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "foo 3");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "slid", &dsp->fHslider4, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* input0 = inputs[0];
	FAUSTFLOAT* input1 = inputs[1];
	FAUSTFLOAT* input2 = inputs[2];
	FAUSTFLOAT* input3 = inputs[3];
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	FAUSTFLOAT* output2 = outputs[2];
	FAUSTFLOAT* output3 = outputs[3];
	float fSlow0 = (float)dsp->fHslider1;
	float fSlow1 = ((float)dsp->fHslider0 * fSlow0);
	float fSlow2 = (fSlow0 * (float)dsp->fHslider2);
	float fSlow3 = (fSlow0 * (float)dsp->fHslider3);
	float fSlow4 = (fSlow0 * (float)dsp->fHslider4);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			output0[i] = (FAUSTFLOAT)(fSlow1 * (float)input0[i]);
			output1[i] = (FAUSTFLOAT)(fSlow2 * (float)input1[i]);
			output2[i] = (FAUSTFLOAT)(fSlow3 * (float)input2[i]);
			output3[i] = (FAUSTFLOAT)(fSlow4 * (float)input3[i]);
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
