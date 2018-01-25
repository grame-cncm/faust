/* ------------------------------------------------------------
author: "JOS, revised by RM"
name: "noiseGate"
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
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	float fRec3[2];
	FAUSTFLOAT fHslider2;
	int iVec0[2];
	FAUSTFLOAT fHslider3;
	int iRec4[2];
	float fRec1[2];
	float fRec0[2];
	FAUSTFLOAT fHbargraph0;
	float fRec8[2];
	int iVec1[2];
	int iRec9[2];
	float fRec6[2];
	float fRec5[2];
	
} mydsp;

mydsp* newmydsp() { 
	mydsp* dsp = (mydsp*)malloc(sizeof(mydsp));
	return dsp;
}

void deletemydsp(mydsp* dsp) { 
	free(dsp);
}

void metadatamydsp(MetaGlue* m) { 
	m->declare(m->metaInterface, "analyzers.lib/name", "Faust Analyzer Library");
	m->declare(m->metaInterface, "analyzers.lib/version", "0.0");
	m->declare(m->metaInterface, "author", "JOS, revised by RM");
	m->declare(m->metaInterface, "basics.lib/name", "Faust Basic Element Library");
	m->declare(m->metaInterface, "basics.lib/version", "0.0");
	m->declare(m->metaInterface, "description", "Gate demo application.");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "misceffects.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "misceffects.lib/version", "2.0");
	m->declare(m->metaInterface, "name", "noiseGate");
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
	dsp->fHslider0 = (FAUSTFLOAT)10.0f;
	dsp->fHslider1 = (FAUSTFLOAT)100.0f;
	dsp->fHslider2 = (FAUSTFLOAT)-30.0f;
	dsp->fHslider3 = (FAUSTFLOAT)200.0f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			dsp->fRec3[l0] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			dsp->iVec0[l1] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			dsp->iRec4[l2] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			dsp->fRec1[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			dsp->fRec0[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			dsp->fRec8[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			dsp->iVec1[l6] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			dsp->iRec9[l7] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			dsp->fRec6[l8] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			dsp->fRec5[l9] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = (1.0f / dsp->fConst0);
	dsp->fConst2 = (1.0f / dsp->fConst0);
	
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
	ui_interface->declare(ui_interface->uiInterface, 0, "tooltip", "Reference:   http://en.wikipedia.org/wiki/Noise_gate");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "GATE");
	ui_interface->declare(ui_interface->uiInterface, 0, "0", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox0, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox0, "tooltip", "When this is checked,   the gate has no effect");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Bypass", &dsp->fCheckbox0);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHbargraph0, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHbargraph0, "tooltip", "Current gain of the  gate in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHbargraph0, "unit", "dB");
	ui_interface->addHorizontalBargraph(ui_interface->uiInterface, "Gate Gain", &dsp->fHbargraph0, -50.0f, 10.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "1", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "tooltip", "When   the signal level falls below the Threshold (expressed in dB), the signal is   muted");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "unit", "dB");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Threshold", &dsp->fHslider2, -30.0f, -120.0f, 0.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "tooltip", "Time constant in MICROseconds (1/e smoothing time) for the gate  gain to go (exponentially) from 0 (muted) to 1 (unmuted)");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "unit", "us");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Attack", &dsp->fHslider0, 10.0f, 10.0f, 10000.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "tooltip", "Time in ms to keep the gate open (no muting) after the signal  level falls below the Threshold");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "unit", "ms");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Hold", &dsp->fHslider3, 200.0f, 1.0f, 1000.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "4", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "tooltip", "Time constant in ms (1/e smoothing time) for the gain to go  (exponentially) from 1 (unmuted) to 0 (muted)");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "unit", "ms");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Release", &dsp->fHslider1, 100.0f, 1.0f, 1000.0f, 1.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* input0 = inputs[0];
	FAUSTFLOAT* input1 = inputs[1];
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	int iSlow0 = (int)(float)dsp->fCheckbox0;
	float fSlow1 = max(dsp->fConst2, (9.99999997e-07f * (float)dsp->fHslider0));
	float fSlow2 = max(dsp->fConst2, (0.00100000005f * (float)dsp->fHslider1));
	float fSlow3 = expf((0.0f - (dsp->fConst1 / min(fSlow1, fSlow2))));
	float fSlow4 = (1.0f - fSlow3);
	float fSlow5 = powf(10.0f, (0.0500000007f * (float)dsp->fHslider2));
	int iSlow6 = (int)(dsp->fConst0 * max(dsp->fConst2, (0.00100000005f * (float)dsp->fHslider3)));
	float fSlow7 = expf((0.0f - (dsp->fConst1 / fSlow1)));
	float fSlow8 = expf((0.0f - (dsp->fConst1 / fSlow2)));
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = (float)input0[i];
			float fTemp1 = (iSlow0?0.0f:fTemp0);
			float fTemp2 = (float)input1[i];
			float fTemp3 = (iSlow0?0.0f:fTemp2);
			float fTemp4 = fabsf(fTemp3);
			dsp->fRec3[0] = ((fSlow3 * dsp->fRec3[1]) + (fSlow4 * fabsf((fabsf(fTemp1) + fTemp4))));
			float fRec2 = dsp->fRec3[0];
			int iTemp5 = (fRec2 > fSlow5);
			dsp->iVec0[0] = iTemp5;
			dsp->iRec4[0] = max((int)(iSlow6 * (iTemp5 < dsp->iVec0[1])), (int)(dsp->iRec4[1] + -1));
			float fTemp6 = fabsf(max((float)iTemp5, (float)(dsp->iRec4[0] > 0)));
			float fTemp7 = ((dsp->fRec0[1] > fTemp6)?fSlow8:fSlow7);
			dsp->fRec1[0] = ((dsp->fRec1[1] * fTemp7) + (fTemp6 * (1.0f - fTemp7)));
			dsp->fRec0[0] = dsp->fRec1[0];
			dsp->fHbargraph0 = (FAUSTFLOAT)(20.0f * log10f(dsp->fRec0[0]));
			dsp->fRec8[0] = ((fSlow3 * dsp->fRec8[1]) + (fSlow4 * fabsf((fTemp4 + fabsf(fTemp1)))));
			float fRec7 = dsp->fRec8[0];
			int iTemp8 = (fRec7 > fSlow5);
			dsp->iVec1[0] = iTemp8;
			dsp->iRec9[0] = max((int)(iSlow6 * (iTemp8 < dsp->iVec1[1])), (int)(dsp->iRec9[1] + -1));
			float fTemp9 = fabsf(max((float)iTemp8, (float)(dsp->iRec9[0] > 0)));
			float fTemp10 = ((dsp->fRec5[1] > fTemp9)?fSlow8:fSlow7);
			dsp->fRec6[0] = ((dsp->fRec6[1] * fTemp10) + (fTemp9 * (1.0f - fTemp10)));
			dsp->fRec5[0] = dsp->fRec6[0];
			output0[i] = (FAUSTFLOAT)(iSlow0?fTemp0:(fTemp1 * dsp->fRec5[0]));
			output1[i] = (FAUSTFLOAT)(iSlow0?fTemp2:(fTemp3 * dsp->fRec5[0]));
			dsp->fRec3[1] = dsp->fRec3[0];
			dsp->iVec0[1] = dsp->iVec0[0];
			dsp->iRec4[1] = dsp->iRec4[0];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec8[1] = dsp->fRec8[0];
			dsp->iVec1[1] = dsp->iVec1[0];
			dsp->iRec9[1] = dsp->iRec9[0];
			dsp->fRec6[1] = dsp->fRec6[0];
			dsp->fRec5[1] = dsp->fRec5[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
