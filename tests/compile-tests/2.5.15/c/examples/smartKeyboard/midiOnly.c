/* ------------------------------------------------------------
name: "midiOnly"
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
	
	int iVec0[2];
	int fSamplingFreq;
	float fConst0;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fButton0;
	FAUSTFLOAT fHslider2;
	float fVec1[2];
	float fRec2[2];
	FAUSTFLOAT fHslider3;
	float fRec5[2];
	float fRec3[2];
	float fRec4[2];
	FAUSTFLOAT fHslider4;
	float fRec6[2];
	FAUSTFLOAT fHslider5;
	float fRec7[2];
	float fRec0[2];
	float fRec1[2];
	float fRec8[2];
	
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
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "interface", "SmartKeyboard{  'Number of Keyboards':'1',  'Keyboard 0 - Number of Keys':'2',  'Keyboard 0 - Send Freq':'0',  'Keyboard 0 - Piano Keyboard':'0',  'Keyboard 0 - Static Mode':'1',  'Keyboard 0 - Send Key X':'1',  'Keyboard 0 - Key 0 - Label':'Mod Index',  'Keyboard 0 - Key 1 - Label':'Mod Freq' }");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "midiOnly");
	m->declare(m->metaInterface, "oscillators.lib/name", "Faust Oscillator Library");
	m->declare(m->metaInterface, "oscillators.lib/version", "0.0");
	m->declare(m->metaInterface, "signals.lib/name", "Faust Signal Routing Library");
	m->declare(m->metaInterface, "signals.lib/version", "0.0");
	m->declare(m->metaInterface, "synths.lib/name", "Faust Synthesizer Library");
	m->declare(m->metaInterface, "synths.lib/version", "0.0");
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
	dsp->fHslider0 = (FAUSTFLOAT)300.0f;
	dsp->fHslider1 = (FAUSTFLOAT)1.0f;
	dsp->fButton0 = (FAUSTFLOAT)0.0f;
	dsp->fHslider2 = (FAUSTFLOAT)0.0f;
	dsp->fHslider3 = (FAUSTFLOAT)0.5f;
	dsp->fHslider4 = (FAUSTFLOAT)0.5f;
	dsp->fHslider5 = (FAUSTFLOAT)1.0f;
	
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
			dsp->fVec1[l1] = 0.0f;
			
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
			dsp->fRec5[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			dsp->fRec3[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
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
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			dsp->fRec7[l7] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			dsp->fRec0[l8] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			dsp->fRec1[l9] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			dsp->fRec8[l10] = 0.0f;
			
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "midiOnly");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "midi", "pitchwheel");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "bend", &dsp->fHslider1, 1.0f, 0.0f, 10.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "freq", &dsp->fHslider0, 300.0f, 50.0f, 2000.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "gain", &dsp->fHslider5, 1.0f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->addButton(ui_interface->uiInterface, "gate", &dsp->fButton0);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "midi", "ctrl 1");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb0k0x", &dsp->fHslider4, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "midi", "ctrl 1");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb0k1x", &dsp->fHslider3, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "midi", "ctrl 64");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "sustain", &dsp->fHslider2, 0.0f, 0.0f, 1.0f, 1.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	float fSlow0 = (float)dsp->fHslider0;
	float fSlow1 = (float)dsp->fHslider1;
	float fSlow2 = min(1.0f, ((float)dsp->fButton0 + (float)dsp->fHslider2));
	int iSlow3 = (fSlow2 == 0.0f);
	float fSlow4 = (dsp->fConst0 * fSlow0);
	float fSlow5 = (0.00100000005f * (float)dsp->fHslider3);
	float fSlow6 = (0.00100000005f * (float)dsp->fHslider4);
	float fSlow7 = (0.00100000005f * (fSlow2 * (float)dsp->fHslider5));
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->iVec0[0] = 1;
			dsp->fVec1[0] = fSlow2;
			int iTemp0 = ((fSlow2 == dsp->fVec1[1]) | iSlow3);
			dsp->fRec2[0] = ((fSlow1 * (1.0f - (0.999000013f * (float)iTemp0))) + (0.999000013f * ((float)iTemp0 * dsp->fRec2[1])));
			dsp->fRec5[0] = (fSlow5 + (0.999000013f * dsp->fRec5[1]));
			float fTemp1 = (fSlow4 * (dsp->fRec2[0] * (dsp->fRec5[0] + 1.0f)));
			float fTemp2 = sinf(fTemp1);
			float fTemp3 = cosf(fTemp1);
			dsp->fRec3[0] = ((dsp->fRec4[1] * fTemp2) + (dsp->fRec3[1] * fTemp3));
			int iTemp4 = (1 - dsp->iVec0[1]);
			dsp->fRec4[0] = (((dsp->fRec4[1] * fTemp3) + (dsp->fRec3[1] * (0.0f - fTemp2))) + (float)iTemp4);
			dsp->fRec6[0] = (fSlow6 + (0.999000013f * dsp->fRec6[1]));
			dsp->fRec7[0] = (fSlow7 + (0.999000013f * dsp->fRec7[1]));
			float fTemp5 = (dsp->fConst0 * ((fSlow0 * dsp->fRec2[0]) + (1000.0f * ((dsp->fRec3[0] * dsp->fRec6[0]) * dsp->fRec7[0]))));
			float fTemp6 = sinf(fTemp5);
			float fTemp7 = cosf(fTemp5);
			dsp->fRec0[0] = ((dsp->fRec1[1] * fTemp6) + (dsp->fRec0[1] * fTemp7));
			dsp->fRec1[0] = (((dsp->fRec1[1] * fTemp7) + (dsp->fRec0[1] * (0.0f - fTemp6))) + (float)iTemp4);
			dsp->fRec8[0] = (fSlow7 + (0.999000013f * dsp->fRec8[1]));
			float fTemp8 = (dsp->fRec0[0] * dsp->fRec8[0]);
			output0[i] = (FAUSTFLOAT)fTemp8;
			output1[i] = (FAUSTFLOAT)fTemp8;
			dsp->iVec0[1] = dsp->iVec0[0];
			dsp->fVec1[1] = dsp->fVec1[0];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec5[1] = dsp->fRec5[0];
			dsp->fRec3[1] = dsp->fRec3[0];
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fRec6[1] = dsp->fRec6[0];
			dsp->fRec7[1] = dsp->fRec7[0];
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fRec8[1] = dsp->fRec8[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
