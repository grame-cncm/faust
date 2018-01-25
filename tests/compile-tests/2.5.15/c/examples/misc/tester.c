/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2006"
license: "BSD"
name: "tester"
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


typedef struct {
	
	int iRec1[2];
	
} mydspSIG0;

static mydspSIG0* newmydspSIG0() { return (mydspSIG0*)malloc(sizeof(mydspSIG0)); }
static void deletemydspSIG0(mydspSIG0* dsp) { free(dsp); }

int getNumInputsmydspSIG0(mydspSIG0* dsp) {
	return 0;
	
}
int getNumOutputsmydspSIG0(mydspSIG0* dsp) {
	return 1;
	
}
int getInputRatemydspSIG0(mydspSIG0* dsp, int channel) {
	int rate;
	switch (channel) {
		default: {
			rate = -1;
			break;
		}
		
	}
	return rate;
	
}
int getOutputRatemydspSIG0(mydspSIG0* dsp, int channel) {
	int rate;
	switch (channel) {
		case 0: {
			rate = 0;
			break;
		}
		default: {
			rate = -1;
			break;
		}
		
	}
	return rate;
	
}

static void instanceInitmydspSIG0(mydspSIG0* dsp, int samplingFreq) {
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			dsp->iRec1[l1] = 0;
			
		}
		
	}
	
}

static void fillmydspSIG0(mydspSIG0* dsp, int count, float* output) {
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->iRec1[0] = (dsp->iRec1[1] + 1);
			output[i] = sinf((9.58738019e-05f * (float)(dsp->iRec1[0] + -1)));
			dsp->iRec1[1] = dsp->iRec1[0];
			
		}
		
	}
	
};

static float ftbl0mydspSIG0[65537];

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
	FAUSTFLOAT fCheckbox0;
	int fSamplingFreq;
	float fConst0;
	FAUSTFLOAT fHslider2;
	float fRec2[2];
	FAUSTFLOAT fCheckbox1;
	int iRec3[3];
	FAUSTFLOAT fCheckbox2;
	float fRec4[3];
	
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
	m->declare(m->metaInterface, "license", "BSD");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "tester");
	m->declare(m->metaInterface, "noises.lib/name", "Faust Noise Generator Library");
	m->declare(m->metaInterface, "noises.lib/version", "0.0");
	m->declare(m->metaInterface, "oscillators.lib/name", "Faust Oscillator Library");
	m->declare(m->metaInterface, "oscillators.lib/version", "0.0");
	m->declare(m->metaInterface, "signals.lib/name", "Faust Signal Routing Library");
	m->declare(m->metaInterface, "signals.lib/version", "0.0");
	m->declare(m->metaInterface, "version", "1.0");
}

int getSampleRatemydsp(mydsp* dsp) { return dsp->fSamplingFreq; }

int getNumInputsmydsp(mydsp* dsp) {
	return 0;
	
}
int getNumOutputsmydsp(mydsp* dsp) {
	return 8;
	
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
	mydspSIG0* sig0 = newmydspSIG0();
	instanceInitmydspSIG0(sig0, samplingFreq);
	fillmydspSIG0(sig0, 65537, ftbl0mydspSIG0);
	deletemydspSIG0(sig0);
	
}

void instanceResetUserInterfacemydsp(mydsp* dsp) {
	dsp->fHslider0 = (FAUSTFLOAT)0.0f;
	dsp->fHslider1 = (FAUSTFLOAT)-96.0f;
	dsp->fCheckbox0 = (FAUSTFLOAT)0.0f;
	dsp->fHslider2 = (FAUSTFLOAT)1000.0f;
	dsp->fCheckbox1 = (FAUSTFLOAT)0.0f;
	dsp->fCheckbox2 = (FAUSTFLOAT)0.0f;
	
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
		int l2;
		for (l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			dsp->fRec2[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 3); l3 = (l3 + 1)) {
			dsp->iRec3[l3] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 3); l4 = (l4 + 1)) {
			dsp->fRec4[l4] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = (1.0f / min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq)));
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "Audio Tester");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "unit", "Hz");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "freq", &dsp->fHslider2, 1000.0f, 10.0f, 20000.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "unit", "dB");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "volume", &dsp->fHslider1, -96.0f, -96.0f, 0.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "3", "");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "destination", &dsp->fHslider0, 0.0f, 0.0f, 8.0f, 1.0f);
	ui_interface->addCheckButton(ui_interface->uiInterface, "pink noise", &dsp->fCheckbox2);
	ui_interface->addCheckButton(ui_interface->uiInterface, "sine wave", &dsp->fCheckbox0);
	ui_interface->addCheckButton(ui_interface->uiInterface, "white noise", &dsp->fCheckbox1);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	FAUSTFLOAT* output2 = outputs[2];
	FAUSTFLOAT* output3 = outputs[3];
	FAUSTFLOAT* output4 = outputs[4];
	FAUSTFLOAT* output5 = outputs[5];
	FAUSTFLOAT* output6 = outputs[6];
	FAUSTFLOAT* output7 = outputs[7];
	float fSlow0 = (float)dsp->fHslider0;
	int iSlow1 = (fSlow0 == 0.0f);
	float fSlow2 = (0.00100000005f * powf(10.0f, (0.0500000007f * (float)dsp->fHslider1)));
	float fSlow3 = (float)dsp->fCheckbox0;
	float fSlow4 = (dsp->fConst0 * (float)dsp->fHslider2);
	float fSlow5 = (4.65661287e-10f * (float)dsp->fCheckbox1);
	float fSlow6 = (10.0f * (float)dsp->fCheckbox2);
	int iSlow7 = (fSlow0 == 1.0f);
	int iSlow8 = (fSlow0 == 2.0f);
	int iSlow9 = (fSlow0 == 3.0f);
	int iSlow10 = (fSlow0 == 4.0f);
	int iSlow11 = (fSlow0 == 5.0f);
	int iSlow12 = (fSlow0 == 6.0f);
	int iSlow13 = (fSlow0 == 7.0f);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->fRec0[0] = (fSlow2 + (0.999000013f * dsp->fRec0[1]));
			dsp->fRec2[0] = (fSlow4 + (dsp->fRec2[1] - floorf((fSlow4 + dsp->fRec2[1]))));
			float fTemp0 = (65536.0f * dsp->fRec2[0]);
			int iTemp1 = (int)fTemp0;
			dsp->iRec3[0] = ((1103515245 * dsp->iRec3[1]) + 12345);
			dsp->fRec4[0] = (((6.90678287e-12f * (float)dsp->iRec3[2]) + ((1.80116081f * dsp->fRec4[1]) + (2.30852802e-11f * (float)dsp->iRec3[0]))) - ((0.802577376f * dsp->fRec4[2]) + (2.93626512e-11f * (float)dsp->iRec3[1])));
			float fTemp2 = (dsp->fRec0[0] * (((fSlow3 * (ftbl0mydspSIG0[iTemp1] + ((fTemp0 - floorf(fTemp0)) * (ftbl0mydspSIG0[(iTemp1 + 1)] - ftbl0mydspSIG0[iTemp1])))) + (fSlow5 * (float)dsp->iRec3[0])) + (fSlow6 * dsp->fRec4[0])));
			output0[i] = (FAUSTFLOAT)((float)iSlow1 * fTemp2);
			output1[i] = (FAUSTFLOAT)((float)iSlow7 * fTemp2);
			output2[i] = (FAUSTFLOAT)((float)iSlow8 * fTemp2);
			output3[i] = (FAUSTFLOAT)((float)iSlow9 * fTemp2);
			output4[i] = (FAUSTFLOAT)((float)iSlow10 * fTemp2);
			output5[i] = (FAUSTFLOAT)((float)iSlow11 * fTemp2);
			output6[i] = (FAUSTFLOAT)((float)iSlow12 * fTemp2);
			output7[i] = (FAUSTFLOAT)((float)iSlow13 * fTemp2);
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->iRec3[2] = dsp->iRec3[1];
			dsp->iRec3[1] = dsp->iRec3[0];
			dsp->fRec4[2] = dsp->fRec4[1];
			dsp->fRec4[1] = dsp->fRec4[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
