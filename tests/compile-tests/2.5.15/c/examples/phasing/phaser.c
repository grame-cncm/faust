/* ------------------------------------------------------------
author: "JOS, revised by RM"
name: "phaser"
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

static float mydsp_faustpower2_f(float value) {
	return (value * value);
	
}
static float mydsp_faustpower3_f(float value) {
	return ((value * value) * value);
	
}
static float mydsp_faustpower4_f(float value) {
	return (((value * value) * value) * value);
	
}

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
	int iVec0[2];
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT fHslider1;
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT fHslider4;
	float fConst2;
	FAUSTFLOAT fHslider5;
	FAUSTFLOAT fHslider6;
	FAUSTFLOAT fHslider7;
	float fRec5[2];
	float fRec6[2];
	float fRec4[3];
	float fRec3[3];
	float fRec2[3];
	float fRec1[3];
	float fRec0[2];
	FAUSTFLOAT fCheckbox2;
	float fRec11[3];
	float fRec10[3];
	float fRec9[3];
	float fRec8[3];
	float fRec7[2];
	
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
	m->declare(m->metaInterface, "description", "Phaser demo application.");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "phaser");
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
	dsp->fCheckbox1 = (FAUSTFLOAT)0.0f;
	dsp->fHslider1 = (FAUSTFLOAT)1.0f;
	dsp->fHslider2 = (FAUSTFLOAT)1000.0f;
	dsp->fHslider3 = (FAUSTFLOAT)0.0f;
	dsp->fHslider4 = (FAUSTFLOAT)1.5f;
	dsp->fHslider5 = (FAUSTFLOAT)100.0f;
	dsp->fHslider6 = (FAUSTFLOAT)800.0f;
	dsp->fHslider7 = (FAUSTFLOAT)0.5f;
	dsp->fCheckbox2 = (FAUSTFLOAT)0.0f;
	
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
			dsp->fRec5[l1] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			dsp->fRec6[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 3); l3 = (l3 + 1)) {
			dsp->fRec4[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 3); l4 = (l4 + 1)) {
			dsp->fRec3[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 3); l5 = (l5 + 1)) {
			dsp->fRec2[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 3); l6 = (l6 + 1)) {
			dsp->fRec1[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			dsp->fRec0[l7] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
			dsp->fRec11[l8] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 3); l9 = (l9 + 1)) {
			dsp->fRec10[l9] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 3); l10 = (l10 + 1)) {
			dsp->fRec9[l10] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 3); l11 = (l11 + 1)) {
			dsp->fRec8[l11] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			dsp->fRec7[l12] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = (1.0f / dsp->fConst0);
	dsp->fConst2 = (6.28318548f / dsp->fConst0);
	
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
	ui_interface->declare(ui_interface->uiInterface, 0, "tooltip", "Reference:   https://ccrma.stanford.edu/~jos/pasp/Flanging.html");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "PHASER2");
	ui_interface->declare(ui_interface->uiInterface, 0, "0", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox0, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox0, "tooltip", "When this is checked, the phaser   has no effect");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Bypass", &dsp->fCheckbox0);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox2, "1", "");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Invert Internal Phaser Sum", &dsp->fCheckbox2);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox1, "2", "");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Vibrato Mode", &dsp->fCheckbox1);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "1", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider7, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider7, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider7, "unit", "Hz");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Speed", &dsp->fHslider7, 0.5f, 0.0f, 10.0f, 0.00100000005f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Notch Depth (Intensity)", &dsp->fHslider1, 1.0f, 0.0f, 1.0f, 0.00100000005f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Feedback Gain", &dsp->fHslider3, 0.0f, -0.999000013f, 0.999000013f, 0.00100000005f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "2", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "unit", "Hz");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Notch width", &dsp->fHslider2, 1000.0f, 10.0f, 5000.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "unit", "Hz");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Min Notch1 Freq", &dsp->fHslider5, 100.0f, 20.0f, 5000.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider6, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider6, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider6, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider6, "unit", "Hz");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Max Notch1 Freq", &dsp->fHslider6, 800.0f, 20.0f, 10000.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "4", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Notch Freq Ratio: NotchFreq(n+1)/NotchFreq(n)", &dsp->fHslider4, 1.5f, 1.10000002f, 4.0f, 0.00100000005f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "3", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "unit", "dB");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Phaser Output Level", &dsp->fHslider0, 0.0f, -60.0f, 10.0f, 0.100000001f);
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
	float fSlow2 = (0.5f * ((int)(float)dsp->fCheckbox1?2.0f:(float)dsp->fHslider1));
	float fSlow3 = (1.0f - fSlow2);
	float fSlow4 = expf((dsp->fConst1 * (0.0f - (3.14159274f * (float)dsp->fHslider2))));
	float fSlow5 = mydsp_faustpower2_f(fSlow4);
	float fSlow6 = (float)dsp->fHslider3;
	float fSlow7 = (0.0f - (2.0f * fSlow4));
	float fSlow8 = (float)dsp->fHslider4;
	float fSlow9 = (float)dsp->fHslider5;
	float fSlow10 = (dsp->fConst2 * fSlow9);
	float fSlow11 = (0.5f * (0.0f - (dsp->fConst2 * (fSlow9 - max(fSlow9, (float)dsp->fHslider6)))));
	float fSlow12 = (dsp->fConst2 * (float)dsp->fHslider7);
	float fSlow13 = sinf(fSlow12);
	float fSlow14 = cosf(fSlow12);
	float fSlow15 = (0.0f - fSlow13);
	float fSlow16 = mydsp_faustpower2_f(fSlow8);
	float fSlow17 = mydsp_faustpower3_f(fSlow8);
	float fSlow18 = mydsp_faustpower4_f(fSlow8);
	float fSlow19 = ((int)(float)dsp->fCheckbox2?(0.0f - fSlow2):fSlow2);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = (float)input0[i];
			float fTemp1 = (iSlow0?0.0f:fTemp0);
			dsp->iVec0[0] = 1;
			dsp->fRec5[0] = ((fSlow13 * dsp->fRec6[1]) + (fSlow14 * dsp->fRec5[1]));
			dsp->fRec6[0] = (((fSlow14 * dsp->fRec6[1]) + (fSlow15 * dsp->fRec5[1])) + (float)(1 - dsp->iVec0[1]));
			float fTemp2 = (fSlow10 + (fSlow11 * (1.0f - dsp->fRec5[0])));
			float fTemp3 = (dsp->fRec4[1] * cosf((fSlow8 * fTemp2)));
			dsp->fRec4[0] = (((fSlow1 * fTemp1) + (fSlow6 * dsp->fRec0[1])) - ((fSlow7 * fTemp3) + (fSlow5 * dsp->fRec4[2])));
			float fTemp4 = (dsp->fRec3[1] * cosf((fSlow16 * fTemp2)));
			dsp->fRec3[0] = ((dsp->fRec4[2] + (fSlow7 * (fTemp3 - fTemp4))) + (fSlow5 * (dsp->fRec4[0] - dsp->fRec3[2])));
			float fTemp5 = (dsp->fRec2[1] * cosf((fSlow17 * fTemp2)));
			dsp->fRec2[0] = ((dsp->fRec3[2] + (fSlow7 * (fTemp4 - fTemp5))) + (fSlow5 * (dsp->fRec3[0] - dsp->fRec2[2])));
			float fTemp6 = (dsp->fRec1[1] * cosf((fSlow18 * fTemp2)));
			dsp->fRec1[0] = ((dsp->fRec2[2] + (fSlow7 * (fTemp5 - fTemp6))) + (fSlow5 * (dsp->fRec2[0] - dsp->fRec1[2])));
			dsp->fRec0[0] = ((fSlow5 * dsp->fRec1[0]) + ((fSlow7 * fTemp6) + dsp->fRec1[2]));
			output0[i] = (FAUSTFLOAT)(iSlow0?fTemp0:((fSlow1 * (fTemp1 * fSlow3)) + (dsp->fRec0[0] * fSlow19)));
			float fTemp7 = (float)input1[i];
			float fTemp8 = (iSlow0?0.0f:fTemp7);
			float fTemp9 = (fSlow10 + (fSlow11 * (1.0f - dsp->fRec6[0])));
			float fTemp10 = (dsp->fRec11[1] * cosf((fSlow8 * fTemp9)));
			dsp->fRec11[0] = (((fSlow1 * fTemp8) + (fSlow6 * dsp->fRec7[1])) - ((fSlow7 * fTemp10) + (fSlow5 * dsp->fRec11[2])));
			float fTemp11 = (dsp->fRec10[1] * cosf((fSlow16 * fTemp9)));
			dsp->fRec10[0] = ((dsp->fRec11[2] + (fSlow7 * (fTemp10 - fTemp11))) + (fSlow5 * (dsp->fRec11[0] - dsp->fRec10[2])));
			float fTemp12 = (dsp->fRec9[1] * cosf((fSlow17 * fTemp9)));
			dsp->fRec9[0] = ((dsp->fRec10[2] + (fSlow7 * (fTemp11 - fTemp12))) + (fSlow5 * (dsp->fRec10[0] - dsp->fRec9[2])));
			float fTemp13 = (dsp->fRec8[1] * cosf((fSlow18 * fTemp9)));
			dsp->fRec8[0] = ((dsp->fRec9[2] + (fSlow7 * (fTemp12 - fTemp13))) + (fSlow5 * (dsp->fRec9[0] - dsp->fRec8[2])));
			dsp->fRec7[0] = ((fSlow5 * dsp->fRec8[0]) + ((fSlow7 * fTemp13) + dsp->fRec8[2]));
			output1[i] = (FAUSTFLOAT)(iSlow0?fTemp7:((fSlow1 * (fTemp8 * fSlow3)) + (dsp->fRec7[0] * fSlow19)));
			dsp->iVec0[1] = dsp->iVec0[0];
			dsp->fRec5[1] = dsp->fRec5[0];
			dsp->fRec6[1] = dsp->fRec6[0];
			dsp->fRec4[2] = dsp->fRec4[1];
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fRec3[2] = dsp->fRec3[1];
			dsp->fRec3[1] = dsp->fRec3[0];
			dsp->fRec2[2] = dsp->fRec2[1];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec1[2] = dsp->fRec1[1];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec11[2] = dsp->fRec11[1];
			dsp->fRec11[1] = dsp->fRec11[0];
			dsp->fRec10[2] = dsp->fRec10[1];
			dsp->fRec10[1] = dsp->fRec10[0];
			dsp->fRec9[2] = dsp->fRec9[1];
			dsp->fRec9[1] = dsp->fRec9[0];
			dsp->fRec8[2] = dsp->fRec8[1];
			dsp->fRec8[1] = dsp->fRec8[0];
			dsp->fRec7[1] = dsp->fRec7[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
