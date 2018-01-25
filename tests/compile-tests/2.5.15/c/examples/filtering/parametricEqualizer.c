/* ------------------------------------------------------------
name: "parametricEqualizer"
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

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif
#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

typedef struct {
	
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	float fVec0[2];
	float fRec4[2];
	float fRec3[3];
	FAUSTFLOAT fHslider2;
	float fRec6[2];
	float fRec5[3];
	float fConst2;
	FAUSTFLOAT fHslider3;
	float fRec7[2];
	FAUSTFLOAT fHslider4;
	float fConst3;
	float fConst4;
	FAUSTFLOAT fHslider5;
	float fConst5;
	float fRec2[3];
	float fVec1[2];
	float fRec1[2];
	float fRec0[3];
	FAUSTFLOAT fHslider6;
	float fRec9[2];
	float fRec8[3];
	
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
	m->declare(m->metaInterface, "basics.lib/name", "Faust Basic Element Library");
	m->declare(m->metaInterface, "basics.lib/version", "0.0");
	m->declare(m->metaInterface, "description", "Exercise and compare Parametric Equalizer sections on test signals");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "parametricEqualizer");
	m->declare(m->metaInterface, "signals.lib/name", "Faust Signal Routing Library");
	m->declare(m->metaInterface, "signals.lib/version", "0.0");
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
	dsp->fHslider0 = (FAUSTFLOAT)8000.0f;
	dsp->fHslider1 = (FAUSTFLOAT)200.0f;
	dsp->fHslider2 = (FAUSTFLOAT)0.0f;
	dsp->fHslider3 = (FAUSTFLOAT)49.0f;
	dsp->fHslider4 = (FAUSTFLOAT)0.0f;
	dsp->fHslider5 = (FAUSTFLOAT)40.0f;
	dsp->fHslider6 = (FAUSTFLOAT)0.0f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			dsp->fVec0[l0] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			dsp->fRec4[l1] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 3); l2 = (l2 + 1)) {
			dsp->fRec3[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			dsp->fRec6[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 3); l4 = (l4 + 1)) {
			dsp->fRec5[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			dsp->fRec7[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 3); l6 = (l6 + 1)) {
			dsp->fRec2[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			dsp->fVec1[l7] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			dsp->fRec1[l8] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 3); l9 = (l9 + 1)) {
			dsp->fRec0[l9] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
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
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = (3.14159274f / dsp->fConst0);
	dsp->fConst2 = (1382.30078f / dsp->fConst0);
	dsp->fConst3 = (1.0f / dsp->fConst0);
	dsp->fConst4 = (1382.30078f * dsp->fConst3);
	dsp->fConst5 = (2764.60156f * dsp->fConst3);
	
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
	ui_interface->declare(ui_interface->uiInterface, 0, "tooltip", "See Faust's filters.lib   for info and pointers");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "PARAMETRIC EQ SECTIONS");
	ui_interface->declare(ui_interface->uiInterface, 0, "1", "");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "Low Shelf");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "tooltip", "Amount of low-frequency boost or cut in decibels");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "unit", "dB");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Low Boost|Cut", &dsp->fHslider2, 0.0f, -40.0f, 40.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "tooltip", "Transition-frequency from boost (cut) to unity gain");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "unit", "Hz");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Transition Frequency", &dsp->fHslider1, 200.0f, 1.0f, 5000.0f, 1.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "2", "");
	ui_interface->declare(ui_interface->uiInterface, 0, "tooltip", "Parametric Equalizer   sections from filters.lib");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "Peaking Equalizer");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "tooltip", "Amount of   local boost or cut in decibels");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "unit", "dB");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Peak Boost|Cut", &dsp->fHslider4, 0.0f, -40.0f, 40.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "tooltip", "Peak   Frequency in Piano Key (PK) units (A440 = 49PK)");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "unit", "PK");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Peak Frequency", &dsp->fHslider3, 49.0f, 1.0f, 100.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "tooltip", "Quality factor   (Q) of the peak = center-frequency/bandwidth");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Peak Q", &dsp->fHslider5, 40.0f, 1.0f, 1000.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "3", "");
	ui_interface->declare(ui_interface->uiInterface, 0, "tooltip", "A high shelf provides a boost   or cut above some frequency");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "High Shelf");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider6, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider6, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider6, "tooltip", "Amount of   high-frequency boost or cut in decibels");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider6, "unit", "dB");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "High Boost|Cut", &dsp->fHslider6, 0.0f, -40.0f, 40.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "tooltip", "Transition-frequency from boost (cut) to unity gain");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "unit", "Hz");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Transition Frequency", &dsp->fHslider0, 8000.0f, 20.0f, 10000.0f, 1.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* input0 = inputs[0];
	FAUSTFLOAT* output0 = outputs[0];
	float fSlow0 = tanf((dsp->fConst1 * (float)dsp->fHslider0));
	float fSlow1 = (1.0f / fSlow0);
	float fSlow2 = (1.0f / (((fSlow1 + 1.0f) / fSlow0) + 1.0f));
	float fSlow3 = (fSlow1 + 1.0f);
	float fSlow4 = (0.0f - ((1.0f - fSlow1) / fSlow3));
	float fSlow5 = (1.0f / fSlow3);
	float fSlow6 = tanf((dsp->fConst1 * (float)dsp->fHslider1));
	float fSlow7 = (1.0f / fSlow6);
	float fSlow8 = (1.0f / (((fSlow7 + 1.0f) / fSlow6) + 1.0f));
	float fSlow9 = (1.0f / mydsp_faustpower2_f(fSlow6));
	float fSlow10 = (fSlow7 + 1.0f);
	float fSlow11 = (0.0f - ((1.0f - fSlow7) / fSlow10));
	float fSlow12 = (1.0f / fSlow10);
	float fSlow13 = (0.0f - fSlow7);
	float fSlow14 = (2.0f * (1.0f - fSlow9));
	float fSlow15 = (((fSlow7 + -1.0f) / fSlow6) + 1.0f);
	float fSlow16 = (2.0f * (0.0f - fSlow9));
	float fSlow17 = powf(10.0f, (0.0500000007f * (float)dsp->fHslider2));
	float fSlow18 = (0.00100000005f * (float)dsp->fHslider3);
	float fSlow19 = (float)dsp->fHslider4;
	int iSlow20 = (fSlow19 > 0.0f);
	float fSlow21 = (float)dsp->fHslider5;
	float fSlow22 = (dsp->fConst4 * (powf(10.0f, (0.0500000007f * fabsf(fSlow19))) / fSlow21));
	float fSlow23 = (dsp->fConst4 / fSlow21);
	float fSlow24 = (1.0f / mydsp_faustpower2_f(fSlow0));
	float fSlow25 = (2.0f * (1.0f - fSlow24));
	float fSlow26 = (((fSlow1 + -1.0f) / fSlow0) + 1.0f);
	float fSlow27 = powf(10.0f, (0.0500000007f * (float)dsp->fHslider6));
	float fSlow28 = (0.0f - fSlow1);
	float fSlow29 = (2.0f * (0.0f - fSlow24));
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = (float)input0[i];
			dsp->fVec0[0] = fTemp0;
			dsp->fRec4[0] = ((fSlow11 * dsp->fRec4[1]) + (fSlow12 * ((fSlow7 * fTemp0) + (fSlow13 * dsp->fVec0[1]))));
			dsp->fRec3[0] = (dsp->fRec4[0] - (fSlow8 * ((fSlow14 * dsp->fRec3[1]) + (fSlow15 * dsp->fRec3[2]))));
			dsp->fRec6[0] = ((fSlow11 * dsp->fRec6[1]) + (fSlow12 * (fTemp0 + dsp->fVec0[1])));
			dsp->fRec5[0] = (dsp->fRec6[0] - (fSlow8 * ((fSlow14 * dsp->fRec5[1]) + (fSlow15 * dsp->fRec5[2]))));
			dsp->fRec7[0] = (fSlow18 + (0.999000013f * dsp->fRec7[1]));
			float fTemp1 = powf(2.0f, (0.0833333358f * (dsp->fRec7[0] + -49.0f)));
			float fTemp2 = tanf((dsp->fConst2 * fTemp1));
			float fTemp3 = (1.0f / fTemp2);
			float fTemp4 = (fTemp1 / sinf((dsp->fConst5 * fTemp1)));
			float fTemp5 = (fSlow22 * fTemp4);
			float fTemp6 = (fSlow23 * fTemp4);
			float fTemp7 = (iSlow20?fTemp6:fTemp5);
			float fTemp8 = (2.0f * (dsp->fRec2[1] * (1.0f - (1.0f / mydsp_faustpower2_f(fTemp2)))));
			float fTemp9 = (((fTemp3 + fTemp7) / fTemp2) + 1.0f);
			dsp->fRec2[0] = ((fSlow8 * ((((fSlow9 * dsp->fRec3[0]) + (fSlow16 * dsp->fRec3[1])) + (fSlow9 * dsp->fRec3[2])) + (fSlow17 * (dsp->fRec5[2] + (dsp->fRec5[0] + (2.0f * dsp->fRec5[1])))))) - (((dsp->fRec2[2] * (((fTemp3 - fTemp7) / fTemp2) + 1.0f)) + fTemp8) / fTemp9));
			float fTemp10 = (iSlow20?fTemp5:fTemp6);
			float fTemp11 = (((fTemp8 + (dsp->fRec2[0] * (((fTemp3 + fTemp10) / fTemp2) + 1.0f))) + (dsp->fRec2[2] * (((fTemp3 - fTemp10) / fTemp2) + 1.0f))) / fTemp9);
			dsp->fVec1[0] = fTemp11;
			dsp->fRec1[0] = ((fSlow4 * dsp->fRec1[1]) + (fSlow5 * (dsp->fVec1[1] + fTemp11)));
			dsp->fRec0[0] = (dsp->fRec1[0] - (fSlow2 * ((fSlow25 * dsp->fRec0[1]) + (fSlow26 * dsp->fRec0[2]))));
			dsp->fRec9[0] = ((fSlow4 * dsp->fRec9[1]) + (fSlow5 * ((fSlow28 * dsp->fVec1[1]) + (fSlow1 * fTemp11))));
			dsp->fRec8[0] = (dsp->fRec9[0] - (fSlow2 * ((fSlow25 * dsp->fRec8[1]) + (fSlow26 * dsp->fRec8[2]))));
			output0[i] = (FAUSTFLOAT)(fSlow2 * ((dsp->fRec0[2] + (dsp->fRec0[0] + (2.0f * dsp->fRec0[1]))) + (fSlow27 * (((fSlow24 * dsp->fRec8[0]) + (fSlow29 * dsp->fRec8[1])) + (fSlow24 * dsp->fRec8[2])))));
			dsp->fVec0[1] = dsp->fVec0[0];
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fRec3[2] = dsp->fRec3[1];
			dsp->fRec3[1] = dsp->fRec3[0];
			dsp->fRec6[1] = dsp->fRec6[0];
			dsp->fRec5[2] = dsp->fRec5[1];
			dsp->fRec5[1] = dsp->fRec5[0];
			dsp->fRec7[1] = dsp->fRec7[0];
			dsp->fRec2[2] = dsp->fRec2[1];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fVec1[1] = dsp->fVec1[0];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fRec0[2] = dsp->fRec0[1];
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec9[1] = dsp->fRec9[0];
			dsp->fRec8[2] = dsp->fRec8[1];
			dsp->fRec8[1] = dsp->fRec8[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
