/* ------------------------------------------------------------
name: "harmonicExciter"
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
	
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fCheckbox0;
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	float fConst3;
	FAUSTFLOAT fHslider4;
	float fRec3[3];
	FAUSTFLOAT fHslider5;
	float fRec6[2];
	float fRec5[2];
	FAUSTFLOAT fHslider6;
	float fRec4[2];
	float fRec2[2];
	float fRec1[2];
	float fRec0[2];
	FAUSTFLOAT fHbargraph0;
	
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
	m->declare(m->metaInterface, "compressors.lib/name", "Faust Compressor Effect Library");
	m->declare(m->metaInterface, "compressors.lib/version", "0.0");
	m->declare(m->metaInterface, "description", "Psychoacoustic harmonic exciter, with GUI");
	m->declare(m->metaInterface, "exciter_author", "Priyanka Shekar (pshekar@ccrma.stanford.edu), revised by RM");
	m->declare(m->metaInterface, "exciter_copyright", "Copyright (c) 2013 Priyanka Shekar");
	m->declare(m->metaInterface, "exciter_license", "MIT License (MIT)");
	m->declare(m->metaInterface, "exciter_name", "harmonicExciter");
	m->declare(m->metaInterface, "exciter_version", "1.0");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "harmonicExciter");
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
	dsp->fHslider0 = (FAUSTFLOAT)0.5f;
	dsp->fHslider1 = (FAUSTFLOAT)20.0f;
	dsp->fCheckbox0 = (FAUSTFLOAT)0.0f;
	dsp->fHslider2 = (FAUSTFLOAT)50.0f;
	dsp->fHslider3 = (FAUSTFLOAT)5.0f;
	dsp->fHslider4 = (FAUSTFLOAT)5000.0f;
	dsp->fHslider5 = (FAUSTFLOAT)500.0f;
	dsp->fHslider6 = (FAUSTFLOAT)-30.0f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 3); l0 = (l0 + 1)) {
			dsp->fRec3[l0] = 0.0f;
			
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
			dsp->fRec2[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			dsp->fRec1[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			dsp->fRec0[l6] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = (2.0f / dsp->fConst0);
	dsp->fConst2 = (1.0f / dsp->fConst0);
	dsp->fConst3 = (3.14159274f / dsp->fConst0);
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "harmonicExciter");
	ui_interface->declare(ui_interface->uiInterface, 0, "tooltip", "Reference:    http://en.wikipedia.org/wiki/Dynamic_range_compression");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "COMPRESSOR");
	ui_interface->declare(ui_interface->uiInterface, 0, "0", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox0, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox0, "tooltip", "When this is checked,   the compressor has no effect");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Bypass", &dsp->fCheckbox0);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHbargraph0, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHbargraph0, "tooltip", "Current gain   of the compressor in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHbargraph0, "unit", "dB");
	ui_interface->addHorizontalBargraph(ui_interface->uiInterface, "Compressor Gain", &dsp->fHbargraph0, -50.0f, 10.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "1", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, 0, "3", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "Compression Control");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "tooltip", "A compression Ratio  of N means that for each N dB increase in input signal level above Threshold, the  output level goes up 1 dB");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Ratio", &dsp->fHslider3, 5.0f, 1.0f, 20.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider6, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider6, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider6, "tooltip", "When the signal level exceeds the Threshold (in dB), its level is compressed  according to the Ratio");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider6, "unit", "dB");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Threshold", &dsp->fHslider6, -30.0f, -100.0f, 10.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "4", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "Compression Response");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "tooltip", "Time constant in ms (1/e smoothing time) for the compression gain to approach  (exponentially) a new lower target level (the compression `kicking in')");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "unit", "ms");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Attack", &dsp->fHslider2, 50.0f, 0.0f, 500.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "tooltip", "Time constant in ms (1/e smoothing time) for the compression gain to approach  (exponentially) a new higher target level (the compression 'releasing')");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "unit", "ms");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Release", &dsp->fHslider5, 500.0f, 0.0f, 1000.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "tooltip", "Reference: Patent US4150253 A");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "EXCITER");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "tooltip", "Cutoff frequency for highpassed components to be excited");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "unit", "Hz");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Cutoff Frequency", &dsp->fHslider4, 5000.0f, 1000.0f, 10000.0f, 100.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "tooltip", "Percentage of harmonics generated");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "unit", "percent");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Harmonics", &dsp->fHslider1, 20.0f, 0.0f, 200.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "tooltip", "Dry/Wet mix of original signal   to excited signal");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Mix", &dsp->fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* input0 = inputs[0];
	FAUSTFLOAT* output0 = outputs[0];
	float fSlow0 = (float)dsp->fHslider0;
	float fSlow1 = (float)dsp->fHslider1;
	float fSlow2 = (100.0f * (fSlow0 / fSlow1));
	float fSlow3 = (0.00999999978f * fSlow1);
	int iSlow4 = (int)(float)dsp->fCheckbox0;
	float fSlow5 = max(dsp->fConst2, (0.00100000005f * (float)dsp->fHslider2));
	float fSlow6 = expf((0.0f - (dsp->fConst1 / fSlow5)));
	float fSlow7 = (((1.0f / (float)dsp->fHslider3) + -1.0f) * (1.0f - fSlow6));
	float fSlow8 = tanf((dsp->fConst3 * (float)dsp->fHslider4));
	float fSlow9 = (1.0f / fSlow8);
	float fSlow10 = (1.0f / (((fSlow9 + 1.41421354f) / fSlow8) + 1.0f));
	float fSlow11 = (1.0f / mydsp_faustpower2_f(fSlow8));
	float fSlow12 = (((fSlow9 + -1.41421354f) / fSlow8) + 1.0f);
	float fSlow13 = (2.0f * (1.0f - fSlow11));
	float fSlow14 = (2.0f * (0.0f - fSlow11));
	float fSlow15 = expf((0.0f - (dsp->fConst2 / fSlow5)));
	float fSlow16 = expf((0.0f - (dsp->fConst2 / max(dsp->fConst2, (0.00100000005f * (float)dsp->fHslider5)))));
	float fSlow17 = (float)dsp->fHslider6;
	float fSlow18 = (1.0f - fSlow0);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = (float)input0[i];
			dsp->fRec3[0] = (fTemp0 - (fSlow10 * ((fSlow12 * dsp->fRec3[2]) + (fSlow13 * dsp->fRec3[1]))));
			float fTemp1 = (fSlow10 * (((fSlow11 * dsp->fRec3[0]) + (fSlow14 * dsp->fRec3[1])) + (fSlow11 * dsp->fRec3[2])));
			float fTemp2 = (iSlow4?0.0f:fTemp1);
			float fTemp3 = fabsf(fTemp2);
			float fTemp4 = ((dsp->fRec5[1] > fTemp3)?fSlow16:fSlow15);
			dsp->fRec6[0] = ((dsp->fRec6[1] * fTemp4) + (fTemp3 * (1.0f - fTemp4)));
			dsp->fRec5[0] = dsp->fRec6[0];
			dsp->fRec4[0] = ((fSlow6 * dsp->fRec4[1]) + (fSlow7 * max(((20.0f * log10f(dsp->fRec5[0])) - fSlow17), 0.0f)));
			float fTemp5 = (fTemp2 * powf(10.0f, (0.0500000007f * dsp->fRec4[0])));
			float fTemp6 = fabsf(fabsf(fTemp5));
			float fTemp7 = ((dsp->fRec1[1] > fTemp6)?fSlow16:fSlow15);
			dsp->fRec2[0] = ((dsp->fRec2[1] * fTemp7) + (fTemp6 * (1.0f - fTemp7)));
			dsp->fRec1[0] = dsp->fRec2[0];
			dsp->fRec0[0] = ((fSlow6 * dsp->fRec0[1]) + (fSlow7 * max(((20.0f * log10f(dsp->fRec1[0])) - fSlow17), 0.0f)));
			dsp->fHbargraph0 = (FAUSTFLOAT)(20.0f * log10f(powf(10.0f, (0.0500000007f * dsp->fRec0[0]))));
			float fTemp8 = (iSlow4?fTemp1:fTemp5);
			float fTemp9 = (fSlow3 * fTemp8);
			output0[i] = (FAUSTFLOAT)((fSlow2 * (((fSlow3 * (fTemp8 * (float)(fTemp9 < 0.0f))) + ((float)((fTemp9 >= 0.0f) * (fTemp9 <= 1.0f)) * (fTemp9 - (0.333333343f * mydsp_faustpower3_f(fTemp9))))) + (0.666666687f * (float)(fTemp9 > 1.0f)))) + (fSlow18 * fTemp0));
			dsp->fRec3[2] = dsp->fRec3[1];
			dsp->fRec3[1] = dsp->fRec3[0];
			dsp->fRec6[1] = dsp->fRec6[0];
			dsp->fRec5[1] = dsp->fRec5[0];
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fRec0[1] = dsp->fRec0[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
