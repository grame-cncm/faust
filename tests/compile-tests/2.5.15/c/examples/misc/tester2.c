/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2014"
license: "BSD"
name: "tester2"
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
	
	int iRec2[2];
	
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
		int l2;
		for (l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			dsp->iRec2[l2] = 0;
			
		}
		
	}
	
}

static void fillmydspSIG0(mydspSIG0* dsp, int count, float* output) {
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->iRec2[0] = (dsp->iRec2[1] + 1);
			output[i] = sinf((9.58738019e-05f * (float)(dsp->iRec2[0] + -1)));
			dsp->iRec2[1] = dsp->iRec2[0];
			
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
	float fRec0[2];
	FAUSTFLOAT fHslider1;
	float fRec1[2];
	FAUSTFLOAT fHslider2;
	int fSamplingFreq;
	float fConst0;
	FAUSTFLOAT fHslider3;
	float fRec3[2];
	int iRec5[3];
	float fRec4[3];
	float fRec6[2];
	
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
	m->declare(m->metaInterface, "copyright", "(c)GRAME 2014");
	m->declare(m->metaInterface, "license", "BSD");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "tester2");
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
	return 2;
	
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
	dsp->fHslider0 = (FAUSTFLOAT)-96.0f;
	dsp->fHslider1 = (FAUSTFLOAT)0.0f;
	dsp->fHslider2 = (FAUSTFLOAT)0.0f;
	dsp->fHslider3 = (FAUSTFLOAT)440.0f;
	
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
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			dsp->fRec3[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 3); l4 = (l4 + 1)) {
			dsp->iRec5[l4] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 3); l5 = (l5 + 1)) {
			dsp->fRec4[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			dsp->fRec6[l6] = 0.0f;
			
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "Stereo Audio Tester");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "unit", "Hz");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "freq", &dsp->fHslider3, 440.0f, 40.0f, 20000.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "unit", "dB");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "volume", &dsp->fHslider0, -96.0f, -96.0f, 0.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "style", "menu{'white noise':0;'pink noise':1;'sine':2}");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "signal", &dsp->fHslider2, 0.0f, 0.0f, 2.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "4", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "style", "radio{'none':0;'left':1;'right':2;'both':3}");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "channel", &dsp->fHslider1, 0.0f, 0.0f, 3.0f, 1.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	float fSlow0 = (0.00100000005f * powf(10.0f, (0.0500000007f * (float)dsp->fHslider0)));
	int iSlow1 = (int)(float)dsp->fHslider1;
	int iSlow2 = ((iSlow1 & 1) != 0);
	int iSlow3 = (int)(float)dsp->fHslider2;
	int iSlow4 = (iSlow3 == 0);
	int iSlow5 = (iSlow3 == 1);
	float fSlow6 = (dsp->fConst0 * (float)dsp->fHslider3);
	int iSlow7 = ((iSlow1 & 2) != 0);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->fRec0[0] = (fSlow0 + (0.999000013f * dsp->fRec0[1]));
			dsp->fRec1[0] = ((dsp->fRec1[1] < (float)iSlow2)?min((dsp->fRec1[1] + 0.000226757373f), (float)iSlow2):max((dsp->fRec1[1] + -0.000226757373f), (float)iSlow2));
			dsp->fRec3[0] = (fSlow6 + (dsp->fRec3[1] - floorf((fSlow6 + dsp->fRec3[1]))));
			float fTemp0 = (65536.0f * dsp->fRec3[0]);
			int iTemp1 = (int)fTemp0;
			dsp->iRec5[0] = ((1103515245 * dsp->iRec5[1]) + 12345);
			dsp->fRec4[0] = (((6.90678287e-12f * (float)dsp->iRec5[2]) + ((1.80116081f * dsp->fRec4[1]) + (2.30852802e-11f * (float)dsp->iRec5[0]))) - ((0.802577376f * dsp->fRec4[2]) + (2.93626512e-11f * (float)dsp->iRec5[1])));
			float fTemp2 = (iSlow4?(4.65661287e-10f * (float)dsp->iRec5[0]):(iSlow5?dsp->fRec4[0]:(ftbl0mydspSIG0[iTemp1] + ((fTemp0 - floorf(fTemp0)) * (ftbl0mydspSIG0[(iTemp1 + 1)] - ftbl0mydspSIG0[iTemp1])))));
			output0[i] = (FAUSTFLOAT)((dsp->fRec0[0] * dsp->fRec1[0]) * fTemp2);
			dsp->fRec6[0] = ((dsp->fRec6[1] < (float)iSlow7)?min((dsp->fRec6[1] + 0.000226757373f), (float)iSlow7):max((dsp->fRec6[1] + -0.000226757373f), (float)iSlow7));
			output1[i] = (FAUSTFLOAT)((dsp->fRec0[0] * dsp->fRec6[0]) * fTemp2);
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fRec3[1] = dsp->fRec3[0];
			dsp->iRec5[2] = dsp->iRec5[1];
			dsp->iRec5[1] = dsp->iRec5[0];
			dsp->fRec4[2] = dsp->fRec4[1];
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fRec6[1] = dsp->fRec6[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
