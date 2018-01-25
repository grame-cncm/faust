/* ------------------------------------------------------------
copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
license: "MIT"
name: "KarplusStrong"
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
	float fRec11[2];
	int IOTA;
	float fRec7[2048];
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fButton0;
	FAUSTFLOAT fHslider3;
	float fVec0[2];
	float fRec12[2];
	FAUSTFLOAT fHslider4;
	float fVec1[2048];
	float fRec3[2];
	float fRec0[3];
	float fRec1[3];
	
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
	m->declare(m->metaInterface, "copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
	m->declare(m->metaInterface, "delays.lib/name", "Faust Delay Library");
	m->declare(m->metaInterface, "delays.lib/version", "0.0");
	m->declare(m->metaInterface, "description", "Simple call of the Karplus-Strong model for the Faust physical modeling library");
	m->declare(m->metaInterface, "license", "MIT");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "KarplusStrong");
	m->declare(m->metaInterface, "routes.lib/name", "Faust Signal Routing Library");
	m->declare(m->metaInterface, "routes.lib/version", "0.0");
	m->declare(m->metaInterface, "signals.lib/name", "Faust Signal Routing Library");
	m->declare(m->metaInterface, "signals.lib/version", "0.0");
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
	
}

void instanceResetUserInterfacemydsp(mydsp* dsp) {
	dsp->fHslider0 = (FAUSTFLOAT)0.01f;
	dsp->fHslider1 = (FAUSTFLOAT)440.0f;
	dsp->fHslider2 = (FAUSTFLOAT)1.0f;
	dsp->fButton0 = (FAUSTFLOAT)0.0f;
	dsp->fHslider3 = (FAUSTFLOAT)0.0f;
	dsp->fHslider4 = (FAUSTFLOAT)0.80000000000000004f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			dsp->fRec11[l0] = 0.0f;
			
		}
		
	}
	dsp->IOTA = 0;
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 2048); l1 = (l1 + 1)) {
			dsp->fRec7[l1] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			dsp->fVec0[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			dsp->fRec12[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 2048); l4 = (l4 + 1)) {
			dsp->fVec1[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			dsp->fRec3[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 3); l6 = (l6 + 1)) {
			dsp->fRec0[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			dsp->fRec1[l7] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = (0.00882352982f * dsp->fConst0);
	dsp->fConst2 = (0.00147058826f * dsp->fConst0);
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "karplus");
	ui_interface->declare(ui_interface->uiInterface, 0, "0", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "params");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "freq", &dsp->fHslider1, 440.0f, 50.0f, 1000.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "hidden", "1");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "midi", "pitchwheel");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "bend", &dsp->fHslider2, 1.0f, 0.0f, 10.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "midi", "ctrl 1");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "damping", &dsp->fHslider0, 0.00999999978f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "gain", &dsp->fHslider4, 0.800000012f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "hidden", "1");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "midi", "ctrl 64");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "sustain", &dsp->fHslider3, 0.0f, 0.0f, 1.0f, 1.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fButton0, "1", "");
	ui_interface->addButton(ui_interface->uiInterface, "gate", &dsp->fButton0);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	float fSlow0 = (0.00100000005f * (float)dsp->fHslider0);
	float fSlow1 = (340.0f / (float)dsp->fHslider1);
	float fSlow2 = (float)dsp->fHslider2;
	float fSlow3 = min(1.0f, ((float)dsp->fButton0 + (float)dsp->fHslider3));
	int iSlow4 = (fSlow3 == 0.0f);
	float fSlow5 = (float)dsp->fHslider4;
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->fRec11[0] = (fSlow0 + (0.999000013f * dsp->fRec11[1]));
			float fTemp0 = (0.5f * ((dsp->fRec1[1] + dsp->fRec1[2]) * ((0.200000003f * (1.0f - dsp->fRec11[0])) + 0.800000012f)));
			dsp->fRec7[(dsp->IOTA & 2047)] = fTemp0;
			dsp->fVec0[0] = fSlow3;
			int iTemp1 = ((fSlow3 == dsp->fVec0[1]) | iSlow4);
			dsp->fRec12[0] = ((fSlow2 * (1.0f - (0.999000013f * (float)iTemp1))) + (0.999000013f * ((float)iTemp1 * dsp->fRec12[1])));
			float fTemp2 = (dsp->fConst2 * ((fSlow1 / dsp->fRec12[0]) + -0.0500000007f));
			float fTemp3 = (fTemp2 + -1.49999499f);
			int iTemp4 = (int)fTemp3;
			int iTemp5 = ((int)min(dsp->fConst1, (float)max(0, (int)iTemp4)) + 1);
			float fTemp6 = floorf(fTemp3);
			float fTemp7 = (fTemp2 + (-1.0f - fTemp6));
			float fTemp8 = (0.0f - fTemp7);
			float fTemp9 = (fTemp2 + (-2.0f - fTemp6));
			float fTemp10 = (0.0f - (0.5f * fTemp9));
			float fTemp11 = (fTemp2 + (-3.0f - fTemp6));
			float fTemp12 = (0.0f - (0.333333343f * fTemp11));
			float fTemp13 = (fTemp2 + (-4.0f - fTemp6));
			float fTemp14 = (0.0f - (0.25f * fTemp13));
			float fTemp15 = (fTemp2 - fTemp6);
			int iTemp16 = ((int)min(dsp->fConst1, (float)max(0, (int)(iTemp4 + 2))) + 1);
			float fTemp17 = (0.0f - fTemp11);
			float fTemp18 = (0.0f - (0.5f * fTemp13));
			int iTemp19 = ((int)min(dsp->fConst1, (float)max(0, (int)(iTemp4 + 1))) + 1);
			float fTemp20 = (0.0f - fTemp9);
			float fTemp21 = (0.0f - (0.5f * fTemp11));
			float fTemp22 = (0.0f - (0.333333343f * fTemp13));
			float fTemp23 = (fTemp7 * fTemp9);
			int iTemp24 = ((int)min(dsp->fConst1, (float)max(0, (int)(iTemp4 + 3))) + 1);
			float fTemp25 = (0.0f - fTemp13);
			float fTemp26 = (fTemp23 * fTemp11);
			int iTemp27 = ((int)min(dsp->fConst1, (float)max(0, (int)(iTemp4 + 4))) + 1);
			float fRec8 = (((((dsp->fRec7[((dsp->IOTA - iTemp5) & 2047)] * fTemp8) * fTemp10) * fTemp12) * fTemp14) + (fTemp15 * ((((0.5f * (((fTemp7 * dsp->fRec7[((dsp->IOTA - iTemp16) & 2047)]) * fTemp17) * fTemp18)) + (((dsp->fRec7[((dsp->IOTA - iTemp19) & 2047)] * fTemp20) * fTemp21) * fTemp22)) + (0.166666672f * ((fTemp23 * dsp->fRec7[((dsp->IOTA - iTemp24) & 2047)]) * fTemp25))) + (0.0416666679f * (fTemp26 * dsp->fRec7[((dsp->IOTA - iTemp27) & 2047)])))));
			float fTemp28 = (fSlow5 * (float)((fSlow3 - dsp->fVec0[1]) > 0.0f));
			float fTemp29 = (dsp->fRec0[2] + fTemp28);
			dsp->fVec1[(dsp->IOTA & 2047)] = fTemp29;
			float fTemp30 = ((((fTemp8 * fTemp10) * fTemp12) * fTemp14) * dsp->fVec1[((dsp->IOTA - iTemp5) & 2047)]);
			float fTemp31 = (fTemp15 * (((0.166666672f * ((fTemp23 * fTemp25) * dsp->fVec1[((dsp->IOTA - iTemp24) & 2047)])) + ((((fTemp20 * fTemp21) * fTemp22) * dsp->fVec1[((dsp->IOTA - iTemp19) & 2047)]) + (0.5f * (((fTemp7 * fTemp17) * fTemp18) * dsp->fVec1[((dsp->IOTA - iTemp16) & 2047)])))) + (0.0416666679f * (fTemp26 * dsp->fVec1[((dsp->IOTA - iTemp27) & 2047)]))));
			float fRec9 = (fTemp30 + fTemp31);
			float fRec10 = ((fTemp0 + fTemp30) + fTemp31);
			dsp->fRec3[0] = fRec8;
			float fRec4 = (fTemp28 + dsp->fRec3[1]);
			float fRec5 = fRec9;
			float fRec6 = fRec10;
			dsp->fRec0[0] = fRec4;
			dsp->fRec1[0] = fRec5;
			float fRec2 = fRec6;
			output0[i] = (FAUSTFLOAT)fRec2;
			output1[i] = (FAUSTFLOAT)fRec2;
			dsp->fRec11[1] = dsp->fRec11[0];
			dsp->IOTA = (dsp->IOTA + 1);
			dsp->fVec0[1] = dsp->fVec0[0];
			dsp->fRec12[1] = dsp->fRec12[0];
			dsp->fRec3[1] = dsp->fRec3[0];
			dsp->fRec0[2] = dsp->fRec0[1];
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec1[2] = dsp->fRec1[1];
			dsp->fRec1[1] = dsp->fRec1[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
