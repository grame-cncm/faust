/* ------------------------------------------------------------
author: "JOS, revised by RM"
name: "sawtoothLab"
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

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif
#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

typedef struct {
	
	FAUSTFLOAT fVslider0;
	int iVec0[4];
	float fRec0[2];
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT fEntry0;
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fVslider2;
	float fRec2[2];
	float fVec1[2];
	float fRec1[2];
	float fConst2;
	float fVec2[2];
	float fConst3;
	float fVec3[2];
	float fVec4[2];
	float fConst4;
	float fVec5[2];
	float fVec6[2];
	float fVec7[2];
	FAUSTFLOAT fVslider3;
	float fVec8[2];
	float fRec3[2];
	float fVec9[2];
	float fVec10[2];
	float fVec11[2];
	float fVec12[2];
	float fVec13[2];
	float fVec14[2];
	FAUSTFLOAT fVslider4;
	float fVec15[2];
	float fRec4[2];
	float fVec16[2];
	float fVec17[2];
	float fVec18[2];
	float fVec19[2];
	float fVec20[2];
	float fVec21[2];
	FAUSTFLOAT fCheckbox2;
	int iRec5[2];
	float fRec6[4];
	
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
	m->declare(m->metaInterface, "description", "An application demonstrating the different sawtooth oscillators of Faust.");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "sawtoothLab");
	m->declare(m->metaInterface, "noises.lib/name", "Faust Noise Generator Library");
	m->declare(m->metaInterface, "noises.lib/version", "0.0");
	m->declare(m->metaInterface, "oscillators.lib/name", "Faust Oscillator Library");
	m->declare(m->metaInterface, "oscillators.lib/version", "0.0");
	m->declare(m->metaInterface, "signals.lib/name", "Faust Signal Routing Library");
	m->declare(m->metaInterface, "signals.lib/version", "0.0");
	m->declare(m->metaInterface, "version", "0.0");
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
	dsp->fVslider0 = (FAUSTFLOAT)-20.0f;
	dsp->fCheckbox0 = (FAUSTFLOAT)0.0f;
	dsp->fCheckbox1 = (FAUSTFLOAT)0.0f;
	dsp->fEntry0 = (FAUSTFLOAT)2.0f;
	dsp->fVslider1 = (FAUSTFLOAT)49.0f;
	dsp->fVslider2 = (FAUSTFLOAT)0.10000000000000001f;
	dsp->fVslider3 = (FAUSTFLOAT)-0.10000000000000001f;
	dsp->fVslider4 = (FAUSTFLOAT)0.10000000000000001f;
	dsp->fCheckbox2 = (FAUSTFLOAT)0.0f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 4); l0 = (l0 + 1)) {
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
			dsp->fRec2[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			dsp->fVec1[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			dsp->fRec1[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			dsp->fVec2[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			dsp->fVec3[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			dsp->fVec4[l7] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			dsp->fVec5[l8] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			dsp->fVec6[l9] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			dsp->fVec7[l10] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			dsp->fVec8[l11] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			dsp->fRec3[l12] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l13;
		for (l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			dsp->fVec9[l13] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l14;
		for (l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			dsp->fVec10[l14] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l15;
		for (l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			dsp->fVec11[l15] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l16;
		for (l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			dsp->fVec12[l16] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l17;
		for (l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			dsp->fVec13[l17] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l18;
		for (l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			dsp->fVec14[l18] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l19;
		for (l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			dsp->fVec15[l19] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l20;
		for (l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			dsp->fRec4[l20] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l21;
		for (l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			dsp->fVec16[l21] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l22;
		for (l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			dsp->fVec17[l22] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l23;
		for (l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			dsp->fVec18[l23] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l24;
		for (l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			dsp->fVec19[l24] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l25;
		for (l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			dsp->fVec20[l25] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l26;
		for (l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			dsp->fVec21[l26] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l27;
		for (l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			dsp->iRec5[l27] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l28;
		for (l28 = 0; (l28 < 4); l28 = (l28 + 1)) {
			dsp->fRec6[l28] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = (1.0f / dsp->fConst0);
	dsp->fConst2 = (0.25f * dsp->fConst0);
	dsp->fConst3 = (0.0416666679f * mydsp_faustpower2_f(dsp->fConst0));
	dsp->fConst4 = (0.00520833349f * mydsp_faustpower3_f(dsp->fConst0));
	
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
	ui_interface->declare(ui_interface->uiInterface, 0, "0", "");
	ui_interface->declare(ui_interface->uiInterface, 0, "tooltip", "See Faust's oscillators.lib   for documentation and references");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "SAWTOOTH OSCILLATOR");
	ui_interface->declare(ui_interface->uiInterface, 0, "1", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider0, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider0, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider0, "tooltip", "Sawtooth   waveform amplitude");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider0, "unit", "dB");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Amplitude", &dsp->fVslider0, -20.0f, -120.0f, 10.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider1, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider1, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider1, "tooltip", "Sawtooth   frequency as a Piano Key (PK) number (A440 = key 49)");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider1, "unit", "PK");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Frequency", &dsp->fVslider1, 49.0f, 1.0f, 88.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider3, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider3, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider3, "tooltip", "Percentange frequency-shift  up or down for second oscillator");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider3, "unit", "%%");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Detuning 1", &dsp->fVslider3, -0.100000001f, -10.0f, 10.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider4, "4", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider4, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider4, "tooltip", "Percentange frequency-shift up or down for third detuned oscillator");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider4, "unit", "%%");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Detuning 2", &dsp->fVslider4, 0.100000001f, -10.0f, 10.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider2, "5", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider2, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider2, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider2, "tooltip", "Portamento (frequency-glide) time-constant in seconds");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider2, "unit", "sec");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Portamento", &dsp->fVslider2, 0.100000001f, 0.00100000005f, 10.0f, 0.00100000005f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry0, "6", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry0, "tooltip", "Order of sawtootn aliasing   suppression");
	ui_interface->addNumEntry(ui_interface->uiInterface, "Saw Order", &dsp->fEntry0, 2.0f, 1.0f, 4.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, 0, "7", "");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "Alternate Signals");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox1, "0", "");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Noise (White or Pink - uses only Amplitude control on   the left)", &dsp->fCheckbox1);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox2, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox2, "tooltip", "Pink Noise (or 1/f noise) is Constant-Q Noise, meaning that it has the   same total power in every octave");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Pink instead of White Noise (also called 1/f Noise)", &dsp->fCheckbox2);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox0, "2", "");
	ui_interface->addCheckButton(ui_interface->uiInterface, "External Signal Input (overrides Sawtooth/Noise   selection above)", &dsp->fCheckbox0);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* input0 = inputs[0];
	FAUSTFLOAT* output0 = outputs[0];
	float fSlow0 = (0.00100000005f * powf(10.0f, (0.0500000007f * (float)dsp->fVslider0)));
	int iSlow1 = (int)(float)dsp->fCheckbox0;
	int iSlow2 = (int)(float)dsp->fCheckbox1;
	int iSlow3 = (int)((float)dsp->fEntry0 + -1.0f);
	int iSlow4 = (iSlow3 >= 2);
	int iSlow5 = (iSlow3 >= 1);
	float fSlow6 = expf((0.0f - (dsp->fConst1 / (float)dsp->fVslider2)));
	float fSlow7 = (440.0f * (powf(2.0f, (0.0833333358f * ((float)dsp->fVslider1 + -49.0f))) * (1.0f - fSlow6)));
	int iSlow8 = (iSlow3 >= 3);
	float fSlow9 = ((0.00999999978f * (float)dsp->fVslider3) + 1.0f);
	float fSlow10 = ((0.00999999978f * (float)dsp->fVslider4) + 1.0f);
	int iSlow11 = (int)(float)dsp->fCheckbox2;
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->iVec0[0] = 1;
			dsp->fRec0[0] = (fSlow0 + (0.999000013f * dsp->fRec0[1]));
			dsp->fRec2[0] = (fSlow7 + (fSlow6 * dsp->fRec2[1]));
			float fTemp0 = max(20.0f, fabsf(dsp->fRec2[0]));
			dsp->fVec1[0] = fTemp0;
			float fTemp1 = (dsp->fRec1[1] + (dsp->fConst1 * dsp->fVec1[1]));
			dsp->fRec1[0] = (fTemp1 - floorf(fTemp1));
			float fTemp2 = (2.0f * dsp->fRec1[0]);
			float fTemp3 = (fTemp2 + -1.0f);
			float fTemp4 = mydsp_faustpower2_f(fTemp3);
			dsp->fVec2[0] = fTemp4;
			float fTemp5 = mydsp_faustpower3_f(fTemp3);
			dsp->fVec3[0] = (fTemp5 + (1.0f - fTemp2));
			float fTemp6 = ((fTemp5 + (1.0f - (fTemp2 + dsp->fVec3[1]))) / fTemp0);
			dsp->fVec4[0] = fTemp6;
			float fTemp7 = (fTemp4 * (fTemp4 + -2.0f));
			dsp->fVec5[0] = fTemp7;
			float fTemp8 = ((fTemp7 - dsp->fVec5[1]) / fTemp0);
			dsp->fVec6[0] = fTemp8;
			float fTemp9 = ((fTemp8 - dsp->fVec6[1]) / fTemp0);
			dsp->fVec7[0] = fTemp9;
			float fTemp10 = max(20.0f, fabsf((fSlow9 * dsp->fRec2[0])));
			dsp->fVec8[0] = fTemp10;
			float fTemp11 = (dsp->fRec3[1] + (dsp->fConst1 * dsp->fVec8[1]));
			dsp->fRec3[0] = (fTemp11 - floorf(fTemp11));
			float fTemp12 = (2.0f * dsp->fRec3[0]);
			float fTemp13 = (fTemp12 + -1.0f);
			float fTemp14 = mydsp_faustpower2_f(fTemp13);
			dsp->fVec9[0] = fTemp14;
			float fTemp15 = mydsp_faustpower3_f(fTemp13);
			dsp->fVec10[0] = (fTemp15 + (1.0f - fTemp12));
			float fTemp16 = ((fTemp15 + (1.0f - (fTemp12 + dsp->fVec10[1]))) / fTemp10);
			dsp->fVec11[0] = fTemp16;
			float fTemp17 = (fTemp14 * (fTemp14 + -2.0f));
			dsp->fVec12[0] = fTemp17;
			float fTemp18 = ((fTemp17 - dsp->fVec12[1]) / fTemp10);
			dsp->fVec13[0] = fTemp18;
			float fTemp19 = ((fTemp18 - dsp->fVec13[1]) / fTemp10);
			dsp->fVec14[0] = fTemp19;
			float fTemp20 = max(20.0f, fabsf((fSlow10 * dsp->fRec2[0])));
			dsp->fVec15[0] = fTemp20;
			float fTemp21 = (dsp->fRec4[1] + (dsp->fConst1 * dsp->fVec15[1]));
			dsp->fRec4[0] = (fTemp21 - floorf(fTemp21));
			float fTemp22 = (2.0f * dsp->fRec4[0]);
			float fTemp23 = (fTemp22 + -1.0f);
			float fTemp24 = mydsp_faustpower2_f(fTemp23);
			dsp->fVec16[0] = fTemp24;
			float fTemp25 = mydsp_faustpower3_f(fTemp23);
			dsp->fVec17[0] = (fTemp25 + (1.0f - fTemp22));
			float fTemp26 = ((fTemp25 + (1.0f - (fTemp22 + dsp->fVec17[1]))) / fTemp20);
			dsp->fVec18[0] = fTemp26;
			float fTemp27 = (fTemp24 * (fTemp24 + -2.0f));
			dsp->fVec19[0] = fTemp27;
			float fTemp28 = ((fTemp27 - dsp->fVec19[1]) / fTemp20);
			dsp->fVec20[0] = fTemp28;
			float fTemp29 = ((fTemp28 - dsp->fVec20[1]) / fTemp20);
			dsp->fVec21[0] = fTemp29;
			dsp->iRec5[0] = ((1103515245 * dsp->iRec5[1]) + 12345);
			float fTemp30 = (4.65661287e-10f * (float)dsp->iRec5[0]);
			dsp->fRec6[0] = (((0.522189379f * dsp->fRec6[3]) + (fTemp30 + (2.49495602f * dsp->fRec6[1]))) - (2.0172658f * dsp->fRec6[2]));
			output0[i] = (FAUSTFLOAT)(dsp->fRec0[0] * (iSlow1?(float)input0[i]:(iSlow2?(iSlow11?(((0.0499220341f * dsp->fRec6[0]) + (0.0506126992f * dsp->fRec6[2])) - ((0.0959935337f * dsp->fRec6[1]) + (0.00440878607f * dsp->fRec6[3]))):fTemp30):(0.333333343f * (dsp->fRec0[0] * (((iSlow4?(iSlow8?(dsp->fConst4 * (((float)dsp->iVec0[3] * (fTemp9 - dsp->fVec7[1])) / fTemp0)):(dsp->fConst3 * (((float)dsp->iVec0[2] * (fTemp6 - dsp->fVec4[1])) / fTemp0))):(iSlow5?(dsp->fConst2 * (((float)dsp->iVec0[1] * (fTemp4 - dsp->fVec2[1])) / fTemp0)):fTemp3)) + (iSlow4?(iSlow8?(dsp->fConst4 * (((float)dsp->iVec0[3] * (fTemp19 - dsp->fVec14[1])) / fTemp10)):(dsp->fConst3 * (((float)dsp->iVec0[2] * (fTemp16 - dsp->fVec11[1])) / fTemp10))):(iSlow5?(dsp->fConst2 * (((float)dsp->iVec0[1] * (fTemp14 - dsp->fVec9[1])) / fTemp10)):fTemp13))) + (iSlow4?(iSlow8?(dsp->fConst4 * (((float)dsp->iVec0[3] * (fTemp29 - dsp->fVec21[1])) / fTemp20)):(dsp->fConst3 * (((float)dsp->iVec0[2] * (fTemp26 - dsp->fVec18[1])) / fTemp20))):(iSlow5?(dsp->fConst2 * (((float)dsp->iVec0[1] * (fTemp24 - dsp->fVec16[1])) / fTemp20)):fTemp23))))))));
			/* C99 loop */
			{
				int j0;
				for (j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
					dsp->iVec0[j0] = dsp->iVec0[(j0 - 1)];
					
				}
				
			}
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fVec1[1] = dsp->fVec1[0];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fVec2[1] = dsp->fVec2[0];
			dsp->fVec3[1] = dsp->fVec3[0];
			dsp->fVec4[1] = dsp->fVec4[0];
			dsp->fVec5[1] = dsp->fVec5[0];
			dsp->fVec6[1] = dsp->fVec6[0];
			dsp->fVec7[1] = dsp->fVec7[0];
			dsp->fVec8[1] = dsp->fVec8[0];
			dsp->fRec3[1] = dsp->fRec3[0];
			dsp->fVec9[1] = dsp->fVec9[0];
			dsp->fVec10[1] = dsp->fVec10[0];
			dsp->fVec11[1] = dsp->fVec11[0];
			dsp->fVec12[1] = dsp->fVec12[0];
			dsp->fVec13[1] = dsp->fVec13[0];
			dsp->fVec14[1] = dsp->fVec14[0];
			dsp->fVec15[1] = dsp->fVec15[0];
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fVec16[1] = dsp->fVec16[0];
			dsp->fVec17[1] = dsp->fVec17[0];
			dsp->fVec18[1] = dsp->fVec18[0];
			dsp->fVec19[1] = dsp->fVec19[0];
			dsp->fVec20[1] = dsp->fVec20[0];
			dsp->fVec21[1] = dsp->fVec21[0];
			dsp->iRec5[1] = dsp->iRec5[0];
			/* C99 loop */
			{
				int j1;
				for (j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
					dsp->fRec6[j1] = dsp->fRec6[(j1 - 1)];
					
				}
				
			}
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
