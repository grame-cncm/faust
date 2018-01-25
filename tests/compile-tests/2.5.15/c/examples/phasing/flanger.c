/* ------------------------------------------------------------
author: "JOS, revised by RM"
name: "flanger"
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
	
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fHslider0;
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider1;
	int iVec0[2];
	float fRec0[2];
	float fRec1[2];
	FAUSTFLOAT fHbargraph0;
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	int IOTA;
	float fVec1[4096];
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT fHslider5;
	float fRec2[2];
	float fVec2[4096];
	float fRec3[2];
	
} mydsp;

mydsp* newmydsp() { 
	mydsp* dsp = (mydsp*)malloc(sizeof(mydsp));
	return dsp;
}

void deletemydsp(mydsp* dsp) { 
	free(dsp);
}

void metadatamydsp(MetaGlue* m) { 
	m->declare(m->metaInterface, "author", "JOS, revised by RM");
	m->declare(m->metaInterface, "basics.lib/name", "Faust Basic Element Library");
	m->declare(m->metaInterface, "basics.lib/version", "0.0");
	m->declare(m->metaInterface, "delays.lib/name", "Faust Delay Library");
	m->declare(m->metaInterface, "delays.lib/version", "0.0");
	m->declare(m->metaInterface, "description", "Flanger effect application.");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "flanger");
	m->declare(m->metaInterface, "oscillators.lib/name", "Faust Oscillator Library");
	m->declare(m->metaInterface, "oscillators.lib/version", "0.0");
	m->declare(m->metaInterface, "phaflangers.lib/name", "Faust Phaser and Flanger Library");
	m->declare(m->metaInterface, "phaflangers.lib/version", "0.0");
	m->declare(m->metaInterface, "routes.lib/name", "Faust Signal Routing Library");
	m->declare(m->metaInterface, "routes.lib/version", "0.0");
	m->declare(m->metaInterface, "signals.lib/name", "Faust Signal Routing Library");
	m->declare(m->metaInterface, "signals.lib/version", "0.0");
	m->declare(m->metaInterface, "version", "0.0");
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
	dsp->fCheckbox0 = (FAUSTFLOAT)0.0f;
	dsp->fHslider0 = (FAUSTFLOAT)0.0f;
	dsp->fHslider1 = (FAUSTFLOAT)0.5f;
	dsp->fCheckbox1 = (FAUSTFLOAT)0.0f;
	dsp->fHslider2 = (FAUSTFLOAT)1.0f;
	dsp->fHslider3 = (FAUSTFLOAT)0.0f;
	dsp->fHslider4 = (FAUSTFLOAT)1.0f;
	dsp->fHslider5 = (FAUSTFLOAT)10.0f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			dsp->iVec0[l0] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			dsp->fRec0[l1] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			dsp->fRec1[l2] = 0.0f;
			
		}
		
	}
	dsp->IOTA = 0;
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 4096); l3 = (l3 + 1)) {
			dsp->fVec1[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			dsp->fRec2[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 4096); l5 = (l5 + 1)) {
			dsp->fVec2[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			dsp->fRec3[l6] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = (6.28318548f / dsp->fConst0);
	
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
	ui_interface->declare(ui_interface->uiInterface, 0, "tooltip", "Reference: https://ccrma.stanford.edu/~jos/pasp/Flanging.html");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "FLANGER");
	ui_interface->declare(ui_interface->uiInterface, 0, "0", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox0, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox0, "tooltip", "When this is checked, the flanger   has no effect");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Bypass", &dsp->fCheckbox0);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox1, "1", "");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Invert Flange Sum", &dsp->fCheckbox1);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHbargraph0, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHbargraph0, "style", "led");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHbargraph0, "tooltip", "Display sum of flange delays");
	ui_interface->addHorizontalBargraph(ui_interface->uiInterface, "Flange LFO", &dsp->fHbargraph0, -1.5f, 1.5f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "1", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "unit", "Hz");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Speed", &dsp->fHslider1, 0.5f, 0.0f, 10.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Depth", &dsp->fHslider2, 1.0f, 0.0f, 1.0f, 0.00100000005f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Feedback", &dsp->fHslider3, 0.0f, -0.999000013f, 0.999000013f, 0.00100000005f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "2", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "Delay Controls");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "unit", "ms");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Flange Delay", &dsp->fHslider5, 10.0f, 0.0f, 20.0f, 0.00100000005f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "unit", "ms");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Delay Offset", &dsp->fHslider4, 1.0f, 0.0f, 20.0f, 0.00100000005f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "3", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "unit", "dB");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Flanger Output Level", &dsp->fHslider0, 0.0f, -60.0f, 10.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* input0 = inputs[0];
	FAUSTFLOAT* input1 = inputs[1];
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	int iSlow0 = (int)(float)dsp->fCheckbox0;
	float fSlow1 = powf(10.0f, (0.0500000007f * (float)dsp->fHslider0));
	float fSlow2 = (dsp->fConst1 * (float)dsp->fHslider1);
	float fSlow3 = sinf(fSlow2);
	float fSlow4 = cosf(fSlow2);
	float fSlow5 = (0.0f - fSlow3);
	float fSlow6 = (float)dsp->fHslider2;
	float fSlow7 = ((int)(float)dsp->fCheckbox1?(0.0f - fSlow6):fSlow6);
	float fSlow8 = (float)dsp->fHslider3;
	float fSlow9 = (0.00100000005f * (float)dsp->fHslider4);
	float fSlow10 = (0.000500000024f * (float)dsp->fHslider5);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->iVec0[0] = 1;
			dsp->fRec0[0] = ((fSlow3 * dsp->fRec1[1]) + (fSlow4 * dsp->fRec0[1]));
			dsp->fRec1[0] = (((fSlow4 * dsp->fRec1[1]) + (fSlow5 * dsp->fRec0[1])) + (float)(1 - dsp->iVec0[1]));
			dsp->fHbargraph0 = (FAUSTFLOAT)(dsp->fRec1[0] + dsp->fRec0[0]);
			float fTemp0 = (float)input0[i];
			float fTemp1 = (fSlow1 * (iSlow0?0.0f:fTemp0));
			float fTemp2 = ((fSlow8 * dsp->fRec2[1]) - fTemp1);
			dsp->fVec1[(dsp->IOTA & 4095)] = fTemp2;
			float fTemp3 = (dsp->fConst0 * (fSlow9 + (fSlow10 * (dsp->fRec0[0] + 1.0f))));
			int iTemp4 = (int)fTemp3;
			float fTemp5 = floorf(fTemp3);
			dsp->fRec2[0] = ((dsp->fVec1[((dsp->IOTA - min(2049, max(0, iTemp4))) & 4095)] * (fTemp5 + (1.0f - fTemp3))) + ((fTemp3 - fTemp5) * dsp->fVec1[((dsp->IOTA - min(2049, max(0, (iTemp4 + 1)))) & 4095)]));
			output0[i] = (FAUSTFLOAT)(iSlow0?fTemp0:(0.5f * (fTemp1 + (fSlow7 * dsp->fRec2[0]))));
			float fTemp6 = (float)input1[i];
			float fTemp7 = (fSlow1 * (iSlow0?0.0f:fTemp6));
			float fTemp8 = ((fSlow8 * dsp->fRec3[1]) - fTemp7);
			dsp->fVec2[(dsp->IOTA & 4095)] = fTemp8;
			float fTemp9 = (dsp->fConst0 * (fSlow9 + (fSlow10 * (dsp->fRec1[0] + 1.0f))));
			int iTemp10 = (int)fTemp9;
			float fTemp11 = floorf(fTemp9);
			dsp->fRec3[0] = ((dsp->fVec2[((dsp->IOTA - min(2049, max(0, iTemp10))) & 4095)] * (fTemp11 + (1.0f - fTemp9))) + ((fTemp9 - fTemp11) * dsp->fVec2[((dsp->IOTA - min(2049, max(0, (iTemp10 + 1)))) & 4095)]));
			output1[i] = (FAUSTFLOAT)(iSlow0?fTemp6:(0.5f * (fTemp7 + (fSlow7 * dsp->fRec3[0]))));
			dsp->iVec0[1] = dsp->iVec0[0];
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->IOTA = (dsp->IOTA + 1);
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec3[1] = dsp->fRec3[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
