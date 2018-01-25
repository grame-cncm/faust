/* ------------------------------------------------------------
name: "moogVCF"
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

static float mydsp_faustpower4_f(float value) {
	return (((value * value) * value) * value);
	
}
static float mydsp_faustpower2_f(float value) {
	return (value * value);
	
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
	float fRec0[2];
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT fHslider1;
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider2;
	float fRec6[2];
	float fRec5[2];
	float fRec4[2];
	float fRec3[2];
	float fRec2[2];
	float fRec1[2];
	FAUSTFLOAT fCheckbox2;
	float fConst2;
	float fRec9[2];
	float fRec8[3];
	float fRec7[3];
	float fRec12[2];
	float fRec10[2];
	float fRec15[2];
	float fRec13[2];
	
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
	m->declare(m->metaInterface, "description", "Exercise and compare three Moog VCF implementations");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "moogVCF");
	m->declare(m->metaInterface, "signals.lib/name", "Faust Signal Routing Library");
	m->declare(m->metaInterface, "signals.lib/version", "0.0");
	m->declare(m->metaInterface, "vaeffects.lib/name", "Faust Virtual Analog Filter Effect Library");
	m->declare(m->metaInterface, "vaeffects.lib/version", "0.0");
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
	dsp->fCheckbox0 = (FAUSTFLOAT)0.0f;
	dsp->fHslider0 = (FAUSTFLOAT)5.0f;
	dsp->fCheckbox1 = (FAUSTFLOAT)0.0f;
	dsp->fHslider1 = (FAUSTFLOAT)0.90000000000000002f;
	dsp->fHslider2 = (FAUSTFLOAT)25.0f;
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
		int l1;
		for (l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			dsp->fRec6[l1] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			dsp->fRec5[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			dsp->fRec4[l3] = 0.0f;
			
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
			dsp->fRec2[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			dsp->fRec1[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			dsp->fRec9[l7] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
			dsp->fRec8[l8] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 3); l9 = (l9 + 1)) {
			dsp->fRec7[l9] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			dsp->fRec12[l10] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			dsp->fRec10[l11] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			dsp->fRec15[l12] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l13;
		for (l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			dsp->fRec13[l13] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = (6.28318548f / dsp->fConst0);
	dsp->fConst2 = (3.14159274f / dsp->fConst0);
	
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
	ui_interface->declare(ui_interface->uiInterface, 0, "tooltip", "See Faust's   vaeffects.lib for info and references");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "MOOG VCF (Voltage Controlled Filter)");
	ui_interface->declare(ui_interface->uiInterface, 0, "0", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox0, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox0, "tooltip", "When this is checked, the Moog VCF   has no effect");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Bypass", &dsp->fCheckbox0);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox1, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox1, "tooltip", "Select moog_vcf_2b (two-biquad)   implementation, instead of the default moog_vcf (analog style) implementation");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Use Biquads", &dsp->fCheckbox1);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox2, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox2, "tooltip", "If using biquads, make   them normalized ladders (moog_vcf_2bn)");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Normalized Ladders", &dsp->fCheckbox2);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "tooltip", "The VCF resonates   at the corner frequency (specified in PianoKey (PK) units, with A440 = 49 PK).   The VCF response is flat below the corner frequency, and rolls off -24 dB per   octave above.");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "unit", "PK");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Corner Frequency", &dsp->fHslider2, 25.0f, 1.0f, 88.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "tooltip", "Amount of   resonance near VCF corner frequency (specified between 0 and 1)");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Corner Resonance", &dsp->fHslider1, 0.899999976f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "tooltip", "output level in decibels");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "unit", "dB");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "VCF Output Level", &dsp->fHslider0, 5.0f, -60.0f, 20.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* input0 = inputs[0];
	FAUSTFLOAT* output0 = outputs[0];
	int iSlow0 = (int)(float)dsp->fCheckbox0;
	float fSlow1 = (0.00100000005f * powf(10.0f, (0.0500000007f * (float)dsp->fHslider0)));
	int iSlow2 = (int)(float)dsp->fCheckbox1;
	float fSlow3 = (float)dsp->fHslider1;
	float fSlow4 = (0.0f - (4.0f * max(0.0f, min(mydsp_faustpower4_f(fSlow3), 0.999998987f))));
	float fSlow5 = (0.439999998f * powf(2.0f, (0.0833333358f * ((float)dsp->fHslider2 + -49.0f))));
	int iSlow6 = (int)(float)dsp->fCheckbox2;
	float fSlow7 = min(1.41419947f, (1.41421354f * fSlow3));
	float fSlow8 = (fSlow7 * (fSlow7 + 1.41421354f));
	float fSlow9 = (1.41421354f * fSlow7);
	float fSlow10 = (fSlow9 + 2.0f);
	float fSlow11 = (fSlow7 * (fSlow7 + -1.41421354f));
	float fSlow12 = (2.0f - fSlow9);
	float fSlow13 = (1.99997997f * fSlow3);
	float fSlow14 = mydsp_faustpower2_f((1.41419947f * fSlow3));
	float fSlow15 = (fSlow13 + fSlow14);
	float fSlow16 = (fSlow13 + 2.0f);
	float fSlow17 = (2.0f - fSlow13);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->fRec0[0] = (fSlow1 + (0.999000013f * dsp->fRec0[1]));
			float fTemp0 = (float)input0[i];
			float fTemp1 = (iSlow0?0.0f:fTemp0);
			dsp->fRec6[0] = (fSlow5 + (0.999000013f * dsp->fRec6[1]));
			float fTemp2 = (dsp->fConst1 * dsp->fRec6[0]);
			float fTemp3 = (1.0f - fTemp2);
			dsp->fRec5[0] = ((fSlow4 * dsp->fRec1[1]) + (fTemp1 + (fTemp3 * dsp->fRec5[1])));
			dsp->fRec4[0] = (dsp->fRec5[0] + (fTemp3 * dsp->fRec4[1]));
			dsp->fRec3[0] = (dsp->fRec4[0] + (fTemp3 * dsp->fRec3[1]));
			dsp->fRec2[0] = (dsp->fRec3[0] + (dsp->fRec2[1] * fTemp3));
			dsp->fRec1[0] = (dsp->fRec2[0] * powf(fTemp2, 4.0f));
			dsp->fRec9[0] = (fSlow5 + (0.999000013f * dsp->fRec9[1]));
			float fTemp4 = tanf((dsp->fConst2 * max(20.0f, min(10000.0f, dsp->fRec9[0]))));
			float fTemp5 = (1.0f / fTemp4);
			float fTemp6 = (1.0f - (1.0f / mydsp_faustpower2_f(fTemp4)));
			float fTemp7 = (fSlow8 + (((fSlow10 + fTemp5) / fTemp4) + 1.0f));
			dsp->fRec8[0] = (fTemp1 - (((dsp->fRec8[2] * (fSlow8 + (((fTemp5 - fSlow10) / fTemp4) + 1.0f))) + (2.0f * (dsp->fRec8[1] * (fSlow8 + fTemp6)))) / fTemp7));
			float fTemp8 = (fSlow11 + (((fSlow12 + fTemp5) / fTemp4) + 1.0f));
			dsp->fRec7[0] = (((dsp->fRec8[2] + (dsp->fRec8[0] + (2.0f * dsp->fRec8[1]))) / fTemp7) - (((dsp->fRec7[2] * (fSlow11 + (((fTemp5 - fSlow12) / fTemp4) + 1.0f))) + (2.0f * ((fSlow11 + fTemp6) * dsp->fRec7[1]))) / fTemp8));
			float fTemp9 = tanf((dsp->fConst2 * max(dsp->fRec9[0], 20.0f)));
			float fTemp10 = (1.0f / fTemp9);
			float fTemp11 = (fSlow15 + (((fSlow16 + fTemp10) / fTemp9) + 1.0f));
			float fTemp12 = ((fSlow15 + (1.0f - ((fSlow16 - fTemp10) / fTemp9))) / fTemp11);
			float fTemp13 = max(-0.999899983f, min(0.999899983f, fTemp12));
			float fTemp14 = (1.0f - mydsp_faustpower2_f(fTemp13));
			float fTemp15 = sqrtf(max(0.0f, fTemp14));
			float fTemp16 = ((dsp->fRec10[1] * (0.0f - fTemp13)) + (fTemp1 * fTemp15));
			float fTemp17 = (1.0f - (1.0f / mydsp_faustpower2_f(fTemp9)));
			float fTemp18 = (fSlow15 + fTemp17);
			float fTemp19 = max(-0.999899983f, min(0.999899983f, (2.0f * (fTemp18 / (fTemp11 * (fTemp12 + 1.0f))))));
			float fTemp20 = (1.0f - mydsp_faustpower2_f(fTemp19));
			float fTemp21 = sqrtf(max(0.0f, fTemp20));
			dsp->fRec12[0] = ((dsp->fRec12[1] * (0.0f - fTemp19)) + (fTemp16 * fTemp21));
			dsp->fRec10[0] = ((fTemp16 * fTemp19) + (dsp->fRec12[1] * fTemp21));
			float fRec11 = dsp->fRec12[0];
			float fTemp22 = (1.0f - (fTemp18 / fTemp11));
			float fTemp23 = sqrtf(fTemp14);
			float fTemp24 = ((((fTemp1 * fTemp13) + (dsp->fRec10[1] * fTemp15)) + (2.0f * ((dsp->fRec10[0] * fTemp22) / fTemp23))) + ((fRec11 * ((1.0f - fTemp12) - (2.0f * (fTemp19 * fTemp22)))) / (fTemp23 * sqrtf(fTemp20))));
			float fTemp25 = (fSlow14 + ((((fSlow17 + fTemp10) / fTemp9) + 1.0f) - fSlow13));
			float fTemp26 = ((fSlow14 + ((((fTemp10 - fSlow17) / fTemp9) + 1.0f) - fSlow13)) / fTemp25);
			float fTemp27 = max(-0.999899983f, min(0.999899983f, fTemp26));
			float fTemp28 = (1.0f - mydsp_faustpower2_f(fTemp27));
			float fTemp29 = sqrtf(max(0.0f, fTemp28));
			float fTemp30 = ((dsp->fRec13[1] * (0.0f - fTemp27)) + ((fTemp24 * fTemp29) / fTemp11));
			float fTemp31 = (fSlow14 + (fTemp17 - fSlow13));
			float fTemp32 = max(-0.999899983f, min(0.999899983f, (2.0f * (fTemp31 / (fTemp25 * (fTemp26 + 1.0f))))));
			float fTemp33 = (1.0f - mydsp_faustpower2_f(fTemp32));
			float fTemp34 = sqrtf(max(0.0f, fTemp33));
			dsp->fRec15[0] = ((dsp->fRec15[1] * (0.0f - fTemp32)) + (fTemp30 * fTemp34));
			dsp->fRec13[0] = ((fTemp30 * fTemp32) + (dsp->fRec15[1] * fTemp34));
			float fRec14 = dsp->fRec15[0];
			float fTemp35 = (1.0f - (fTemp31 / fTemp25));
			float fTemp36 = sqrtf(fTemp28);
			output0[i] = (FAUSTFLOAT)(iSlow0?fTemp0:(dsp->fRec0[0] * (iSlow2?(iSlow6?((((((fTemp24 * fTemp27) / fTemp11) + (dsp->fRec13[1] * fTemp29)) + (2.0f * ((dsp->fRec13[0] * fTemp35) / fTemp36))) + ((fRec14 * ((1.0f - fTemp26) - (2.0f * (fTemp32 * fTemp35)))) / (fTemp36 * sqrtf(fTemp33)))) / fTemp25):((dsp->fRec7[2] + (dsp->fRec7[0] + (2.0f * dsp->fRec7[1]))) / fTemp8)):dsp->fRec1[0])));
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec6[1] = dsp->fRec6[0];
			dsp->fRec5[1] = dsp->fRec5[0];
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fRec3[1] = dsp->fRec3[0];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fRec9[1] = dsp->fRec9[0];
			dsp->fRec8[2] = dsp->fRec8[1];
			dsp->fRec8[1] = dsp->fRec8[0];
			dsp->fRec7[2] = dsp->fRec7[1];
			dsp->fRec7[1] = dsp->fRec7[0];
			dsp->fRec12[1] = dsp->fRec12[0];
			dsp->fRec10[1] = dsp->fRec10[0];
			dsp->fRec15[1] = dsp->fRec15[0];
			dsp->fRec13[1] = dsp->fRec13[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
