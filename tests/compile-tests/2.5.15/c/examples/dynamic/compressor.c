/* ------------------------------------------------------------
author: "JOS, revised by RM"
name: "compressor"
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
	FAUSTFLOAT fHslider0;
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	float fRec2[2];
	float fRec1[2];
	FAUSTFLOAT fHslider4;
	float fRec0[2];
	float fRec5[2];
	float fRec4[2];
	float fRec3[2];
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
	m->declare(m->metaInterface, "author", "JOS, revised by RM");
	m->declare(m->metaInterface, "basics.lib/name", "Faust Basic Element Library");
	m->declare(m->metaInterface, "basics.lib/version", "0.0");
	m->declare(m->metaInterface, "compressors.lib/name", "Faust Compressor Effect Library");
	m->declare(m->metaInterface, "compressors.lib/version", "0.0");
	m->declare(m->metaInterface, "description", "Compressor demo application");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "compressor");
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
	dsp->fHslider0 = (FAUSTFLOAT)40.0f;
	dsp->fHslider1 = (FAUSTFLOAT)50.0f;
	dsp->fHslider2 = (FAUSTFLOAT)5.0f;
	dsp->fHslider3 = (FAUSTFLOAT)500.0f;
	dsp->fHslider4 = (FAUSTFLOAT)-30.0f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			dsp->fRec2[l0] = 0.0f;
			
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
		int l2;
		for (l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			dsp->fRec0[l2] = 0.0f;
			
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
			dsp->fRec4[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			dsp->fRec3[l5] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = (2.0f / dsp->fConst0);
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
	ui_interface->declare(ui_interface->uiInterface, 0, "tooltip", "Reference:   http://en.wikipedia.org/wiki/Dynamic_range_compression");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "COMPRESSOR");
	ui_interface->declare(ui_interface->uiInterface, 0, "0", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox0, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox0, "tooltip", "When this is checked, the compressor   has no effect");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Bypass", &dsp->fCheckbox0);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHbargraph0, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHbargraph0, "tooltip", "Current gain of  the compressor in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHbargraph0, "unit", "dB");
	ui_interface->addHorizontalBargraph(ui_interface->uiInterface, "Compressor Gain", &dsp->fHbargraph0, -50.0f, 10.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "1", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, 0, "3", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "Compression Control");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "tooltip", "A compression Ratio of N means that for each N dB increase in input  signal level above Threshold, the output level goes up 1 dB");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Ratio", &dsp->fHslider2, 5.0f, 1.0f, 20.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "tooltip", "When the signal level exceeds the Threshold (in dB), its level  is compressed according to the Ratio");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "unit", "dB");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Threshold", &dsp->fHslider4, -30.0f, -100.0f, 10.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "4", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "Compression Response");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "unit", "ms");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Attack     tooltip: Time constant in ms (1/e smoothing time) for the compression gain  to approach (exponentially) a new lower target level (the compression  `kicking in')]", &dsp->fHslider1, 50.0f, 1.0f, 1000.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "tooltip", "Time constant in ms (1/e smoothing time) for the compression gain  to approach (exponentially) a new higher target level (the compression  'releasing')");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "unit", "ms");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Release", &dsp->fHslider3, 500.0f, 1.0f, 1000.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "5", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "tooltip", "The compressed-signal output level is increased by this amount  (in dB) to make up for the level lost due to compression");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "unit", "dB");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Makeup Gain", &dsp->fHslider0, 40.0f, -96.0f, 96.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* input0 = inputs[0];
	FAUSTFLOAT* input1 = inputs[1];
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	int iSlow0 = (int)(float)dsp->fCheckbox0;
	float fSlow1 = powf(10.0f, (0.0500000007f * (float)dsp->fHslider0));
	float fSlow2 = max(dsp->fConst2, (0.00100000005f * (float)dsp->fHslider1));
	float fSlow3 = expf((0.0f - (dsp->fConst1 / fSlow2)));
	float fSlow4 = (((1.0f / (float)dsp->fHslider2) + -1.0f) * (1.0f - fSlow3));
	float fSlow5 = expf((0.0f - (dsp->fConst2 / fSlow2)));
	float fSlow6 = expf((0.0f - (dsp->fConst2 / max(dsp->fConst2, (0.00100000005f * (float)dsp->fHslider3)))));
	float fSlow7 = (float)dsp->fHslider4;
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = (float)input0[i];
			float fTemp1 = (iSlow0?0.0f:fTemp0);
			float fTemp2 = (float)input1[i];
			float fTemp3 = (iSlow0?0.0f:fTemp2);
			float fTemp4 = fabsf((fabsf(fTemp1) + fabsf(fTemp3)));
			float fTemp5 = ((dsp->fRec1[1] > fTemp4)?fSlow6:fSlow5);
			dsp->fRec2[0] = ((dsp->fRec2[1] * fTemp5) + (fTemp4 * (1.0f - fTemp5)));
			dsp->fRec1[0] = dsp->fRec2[0];
			dsp->fRec0[0] = ((fSlow3 * dsp->fRec0[1]) + (fSlow4 * max(((20.0f * log10f(dsp->fRec1[0])) - fSlow7), 0.0f)));
			float fTemp6 = powf(10.0f, (0.0500000007f * dsp->fRec0[0]));
			float fTemp7 = (fTemp1 * fTemp6);
			output0[i] = (FAUSTFLOAT)(iSlow0?fTemp0:(fSlow1 * fTemp7));
			float fTemp8 = (fTemp3 * fTemp6);
			float fTemp9 = fabsf((fabsf(fTemp7) + fabsf(fTemp8)));
			float fTemp10 = ((dsp->fRec4[1] > fTemp9)?fSlow6:fSlow5);
			dsp->fRec5[0] = ((dsp->fRec5[1] * fTemp10) + (fTemp9 * (1.0f - fTemp10)));
			dsp->fRec4[0] = dsp->fRec5[0];
			dsp->fRec3[0] = ((fSlow3 * dsp->fRec3[1]) + (fSlow4 * max(((20.0f * log10f(dsp->fRec4[0])) - fSlow7), 0.0f)));
			dsp->fHbargraph0 = (FAUSTFLOAT)(20.0f * log10f(powf(10.0f, (0.0500000007f * dsp->fRec3[0]))));
			output1[i] = (FAUSTFLOAT)(iSlow0?fTemp2:(fSlow1 * fTemp8));
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec5[1] = dsp->fRec5[0];
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fRec3[1] = dsp->fRec3[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
