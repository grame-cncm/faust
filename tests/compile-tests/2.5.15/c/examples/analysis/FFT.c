/* ------------------------------------------------------------
author: "JOS"
license: "STK-4.3"
name: "FFT"
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
	
	FAUSTFLOAT fHslider0;
	int fSamplingFreq;
	float fConst0;
	FAUSTFLOAT fHslider1;
	int iVec0[2];
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT fHbargraph0;
	float fRec1[2];
	float fRec2[2];
	int iRec3[2];
	int IOTA;
	float fVec1[32];
	float fRec0[2];
	FAUSTFLOAT fVbargraph0;
	float fRec4[2];
	FAUSTFLOAT fVbargraph1;
	float fRec5[2];
	FAUSTFLOAT fVbargraph2;
	float fRec6[2];
	FAUSTFLOAT fVbargraph3;
	float fRec7[2];
	FAUSTFLOAT fVbargraph4;
	float fRec8[2];
	FAUSTFLOAT fVbargraph5;
	float fRec9[2];
	FAUSTFLOAT fVbargraph6;
	float fRec10[2];
	FAUSTFLOAT fVbargraph7;
	float fRec11[2];
	FAUSTFLOAT fVbargraph8;
	float fRec12[2];
	FAUSTFLOAT fVbargraph9;
	float fRec13[2];
	FAUSTFLOAT fVbargraph10;
	float fRec14[2];
	FAUSTFLOAT fVbargraph11;
	float fRec15[2];
	FAUSTFLOAT fVbargraph12;
	float fRec16[2];
	FAUSTFLOAT fVbargraph13;
	float fRec17[2];
	FAUSTFLOAT fVbargraph14;
	float fRec18[2];
	FAUSTFLOAT fVbargraph15;
	float fRec19[2];
	FAUSTFLOAT fVbargraph16;
	
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
	m->declare(m->metaInterface, "author", "JOS");
	m->declare(m->metaInterface, "basics.lib/name", "Faust Basic Element Library");
	m->declare(m->metaInterface, "basics.lib/version", "0.0");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "license", "STK-4.3");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "FFT");
	m->declare(m->metaInterface, "oscillators.lib/name", "Faust Oscillator Library");
	m->declare(m->metaInterface, "oscillators.lib/version", "0.0");
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
	dsp->fHslider0 = (FAUSTFLOAT)50.0f;
	dsp->fHslider1 = (FAUSTFLOAT)100.0f;
	dsp->fHslider2 = (FAUSTFLOAT)0.10000000000000001f;
	dsp->fHslider3 = (FAUSTFLOAT)8.0f;
	
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
			dsp->fRec1[l1] = 0.0f;
			
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
			dsp->iRec3[l3] = 0;
			
		}
		
	}
	dsp->IOTA = 0;
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 32); l4 = (l4 + 1)) {
			dsp->fVec1[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			dsp->fRec0[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			dsp->fRec4[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			dsp->fRec5[l7] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			dsp->fRec6[l8] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			dsp->fRec7[l9] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			dsp->fRec8[l10] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			dsp->fRec9[l11] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			dsp->fRec10[l12] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l13;
		for (l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			dsp->fRec11[l13] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l14;
		for (l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			dsp->fRec12[l14] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l15;
		for (l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			dsp->fRec13[l15] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l16;
		for (l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			dsp->fRec14[l16] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l17;
		for (l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			dsp->fRec15[l17] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l18;
		for (l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			dsp->fRec16[l18] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l19;
		for (l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			dsp->fRec17[l19] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l20;
		for (l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			dsp->fRec18[l20] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l21;
		for (l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			dsp->fRec19[l21] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = (1000.0f / min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq)));
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "FFT");
	ui_interface->declare(ui_interface->uiInterface, 0, "0", "");
	ui_interface->declare(ui_interface->uiInterface, 0, "tooltip", "fft_spectral_level in Faust's analyzers.lib");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "FFT SPECTRUM ANALYZER, 32 bands");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph0, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph0, "tooltip", "FFT Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph0, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fde158fa360", &dsp->fVbargraph0, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph1, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph1, "tooltip", "FFT Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph1, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fde1590ead0", &dsp->fVbargraph1, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph2, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph2, "tooltip", "FFT Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph2, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fde1591a680", &dsp->fVbargraph2, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph3, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph3, "tooltip", "FFT Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph3, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fde15926030", &dsp->fVbargraph3, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph4, "4", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph4, "tooltip", "FFT Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph4, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fde1592dfd0", &dsp->fVbargraph4, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph5, "5", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph5, "tooltip", "FFT Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph5, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fde15939c50", &dsp->fVbargraph5, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph6, "6", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph6, "tooltip", "FFT Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph6, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fde15940d40", &dsp->fVbargraph6, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph7, "7", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph7, "tooltip", "FFT Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph7, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fde1594b950", &dsp->fVbargraph7, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph8, "8", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph8, "tooltip", "FFT Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph8, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fde159518d0", &dsp->fVbargraph8, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph9, "9", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph9, "tooltip", "FFT Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph9, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fde15958af0", &dsp->fVbargraph9, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph10, "10", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph10, "tooltip", "FFT Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph10, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fde1595fea0", &dsp->fVbargraph10, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph11, "11", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph11, "tooltip", "FFT Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph11, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fde15967b00", &dsp->fVbargraph11, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph12, "12", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph12, "tooltip", "FFT Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph12, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fde1596d090", &dsp->fVbargraph12, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph13, "13", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph13, "tooltip", "FFT Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph13, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fde15974ce0", &dsp->fVbargraph13, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph14, "14", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph14, "tooltip", "FFT Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph14, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fde1597bc90", &dsp->fVbargraph14, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph15, "15", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph15, "tooltip", "FFT Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph15, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fde159838d0", &dsp->fVbargraph15, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph16, "16", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph16, "tooltip", "FFT Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph16, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fde15988770", &dsp->fVbargraph16, -50.0f, 10.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "1", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "FFT SPECTRUM ANALYZER CONTROLS");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "tooltip", "band-level averaging time in milliseconds");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "unit", "ms");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Level Averaging Time", &dsp->fHslider1, 100.0f, 1.0f, 10000.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "tooltip", "Level offset in decibels");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "unit", "dB");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Level dB Offset", &dsp->fHslider0, 50.0f, -50.0f, 100.0f, 1.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "2", "");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "FFT Bin Number", &dsp->fHslider3, 8.0f, 0.0f, 16.0f, 0.00100000005f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHbargraph0, "3", "");
	ui_interface->addHorizontalBargraph(ui_interface->uiInterface, "Measured FFT Bin Number", &dsp->fHbargraph0, 0.0f, 16.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "4", "");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Amplitude", &dsp->fHslider2, 0.100000001f, 0.0f, 1.0f, 0.00100000005f);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	float fSlow0 = (float)dsp->fHslider0;
	float fSlow1 = expf((0.0f - (dsp->fConst0 / (float)dsp->fHslider1)));
	float fSlow2 = (10.0f * (1.0f - fSlow1));
	float fSlow3 = (float)dsp->fHslider2;
	int iSlow4 = (int)(float)dsp->fHslider3;
	dsp->fHbargraph0 = (FAUSTFLOAT)iSlow4;
	int iSlow5 = (iSlow4 == 0);
	int iSlow6 = (iSlow4 == 16);
	float fSlow7 = (0.196349546f * (float)iSlow4);
	float fSlow8 = sinf(fSlow7);
	float fSlow9 = cosf(fSlow7);
	float fSlow10 = (0.0f - fSlow8);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->iVec0[0] = 1;
			dsp->fRec1[0] = ((fSlow8 * dsp->fRec2[1]) + (fSlow9 * dsp->fRec1[1]));
			dsp->fRec2[0] = (((fSlow9 * dsp->fRec2[1]) + (fSlow10 * dsp->fRec1[1])) + (float)(1 - dsp->iVec0[1]));
			dsp->iRec3[0] = (1 - (dsp->iVec0[1] + dsp->iRec3[1]));
			float fTemp0 = (fSlow3 * (iSlow5?1.0f:(iSlow6?(float)dsp->iRec3[0]:(2.0f * dsp->fRec2[0]))));
			dsp->fVec1[(dsp->IOTA & 31)] = fTemp0;
			float fTemp1 = (fTemp0 + dsp->fVec1[((dsp->IOTA - 16) & 31)]);
			float fTemp2 = (dsp->fVec1[((dsp->IOTA - 24) & 31)] + (fTemp1 + dsp->fVec1[((dsp->IOTA - 8) & 31)]));
			float fTemp3 = (dsp->fVec1[((dsp->IOTA - 28) & 31)] + (dsp->fVec1[((dsp->IOTA - 12) & 31)] + (dsp->fVec1[((dsp->IOTA - 20) & 31)] + (dsp->fVec1[((dsp->IOTA - 4) & 31)] + fTemp2))));
			float fTemp4 = (dsp->fVec1[((dsp->IOTA - 30) & 31)] + (dsp->fVec1[((dsp->IOTA - 14) & 31)] + (dsp->fVec1[((dsp->IOTA - 22) & 31)] + (dsp->fVec1[((dsp->IOTA - 6) & 31)] + (dsp->fVec1[((dsp->IOTA - 26) & 31)] + (dsp->fVec1[((dsp->IOTA - 10) & 31)] + (dsp->fVec1[((dsp->IOTA - 18) & 31)] + (dsp->fVec1[((dsp->IOTA - 2) & 31)] + fTemp3))))))));
			dsp->fRec0[0] = ((fSlow1 * dsp->fRec0[1]) + (fSlow2 * log10f(max(1.00000001e-07f, mydsp_faustpower2_f(fabsf((dsp->fVec1[((dsp->IOTA - 31) & 31)] + (dsp->fVec1[((dsp->IOTA - 15) & 31)] + (dsp->fVec1[((dsp->IOTA - 23) & 31)] + (dsp->fVec1[((dsp->IOTA - 7) & 31)] + (dsp->fVec1[((dsp->IOTA - 27) & 31)] + (dsp->fVec1[((dsp->IOTA - 11) & 31)] + (dsp->fVec1[((dsp->IOTA - 19) & 31)] + (dsp->fVec1[((dsp->IOTA - 3) & 31)] + (dsp->fVec1[((dsp->IOTA - 29) & 31)] + (dsp->fVec1[((dsp->IOTA - 13) & 31)] + (dsp->fVec1[((dsp->IOTA - 21) & 31)] + (dsp->fVec1[((dsp->IOTA - 5) & 31)] + (dsp->fVec1[((dsp->IOTA - 25) & 31)] + (dsp->fVec1[((dsp->IOTA - 9) & 31)] + (dsp->fVec1[((dsp->IOTA - 17) & 31)] + (dsp->fVec1[((dsp->IOTA - 1) & 31)] + fTemp4))))))))))))))))))))));
			dsp->fVbargraph0 = (FAUSTFLOAT)(fSlow0 + dsp->fRec0[0]);
			float fTemp5 = (dsp->fVec1[((dsp->IOTA - 15) & 31)] - dsp->fVec1[((dsp->IOTA - 31) & 31)]);
			float fTemp6 = (0.0f - fTemp5);
			float fTemp7 = (dsp->fVec1[((dsp->IOTA - 7) & 31)] - dsp->fVec1[((dsp->IOTA - 23) & 31)]);
			float fTemp8 = (0.707106769f * fTemp7);
			float fTemp9 = ((dsp->fVec1[((dsp->IOTA - 27) & 31)] + (0.707106769f * fTemp6)) - (dsp->fVec1[((dsp->IOTA - 11) & 31)] + fTemp8));
			float fTemp10 = (0.923879504f * fTemp9);
			float fTemp11 = (dsp->fVec1[((dsp->IOTA - 13) & 31)] - dsp->fVec1[((dsp->IOTA - 29) & 31)]);
			float fTemp12 = (0.0f - fTemp11);
			float fTemp13 = (dsp->fVec1[((dsp->IOTA - 25) & 31)] + (0.707106769f * fTemp12));
			float fTemp14 = (dsp->fVec1[((dsp->IOTA - 5) & 31)] - dsp->fVec1[((dsp->IOTA - 21) & 31)]);
			float fTemp15 = (0.707106769f * fTemp14);
			float fTemp16 = (dsp->fVec1[((dsp->IOTA - 9) & 31)] + fTemp15);
			float fTemp17 = (0.707106769f * fTemp6);
			float fTemp18 = (0.707106769f * fTemp7);
			float fTemp19 = ((fTemp17 + (dsp->fVec1[((dsp->IOTA - 3) & 31)] + fTemp18)) - dsp->fVec1[((dsp->IOTA - 19) & 31)]);
			float fTemp20 = ((fTemp10 + fTemp13) - (fTemp16 + (0.382683426f * fTemp19)));
			float fTemp21 = (dsp->fVec1[((dsp->IOTA - 14) & 31)] - dsp->fVec1[((dsp->IOTA - 30) & 31)]);
			float fTemp22 = (0.0f - fTemp21);
			float fTemp23 = (dsp->fVec1[((dsp->IOTA - 6) & 31)] - dsp->fVec1[((dsp->IOTA - 22) & 31)]);
			float fTemp24 = (0.707106769f * fTemp23);
			float fTemp25 = ((dsp->fVec1[((dsp->IOTA - 26) & 31)] + (0.707106769f * fTemp22)) - (dsp->fVec1[((dsp->IOTA - 10) & 31)] + fTemp24));
			float fTemp26 = (dsp->fVec1[((dsp->IOTA - 12) & 31)] - dsp->fVec1[((dsp->IOTA - 28) & 31)]);
			float fTemp27 = (0.0f - fTemp26);
			float fTemp28 = (0.707106769f * fTemp27);
			float fTemp29 = (dsp->fVec1[((dsp->IOTA - 4) & 31)] - dsp->fVec1[((dsp->IOTA - 20) & 31)]);
			float fTemp30 = (0.707106769f * fTemp29);
			float fTemp31 = (fTemp28 + (fTemp0 + fTemp30));
			float fTemp32 = (0.707106769f * fTemp22);
			float fTemp33 = (0.707106769f * fTemp23);
			float fTemp34 = ((fTemp32 + (dsp->fVec1[((dsp->IOTA - 2) & 31)] + fTemp33)) - dsp->fVec1[((dsp->IOTA - 18) & 31)]);
			float fTemp35 = (0.923879504f * fTemp34);
			float fTemp36 = (0.707106769f * fTemp12);
			float fTemp37 = (0.707106769f * fTemp14);
			float fTemp38 = (fTemp36 + (dsp->fVec1[((dsp->IOTA - 1) & 31)] + fTemp37));
			float fTemp39 = (0.923879504f * fTemp19);
			float fTemp40 = (((0.382683426f * fTemp9) + (fTemp38 + fTemp39)) - dsp->fVec1[((dsp->IOTA - 17) & 31)]);
			float fTemp41 = (0.923879504f * fTemp25);
			float fTemp42 = (dsp->fVec1[((dsp->IOTA - 24) & 31)] + (0.707106769f * fTemp27));
			float fTemp43 = (0.707106769f * fTemp29);
			float fTemp44 = (dsp->fVec1[((dsp->IOTA - 8) & 31)] + fTemp43);
			dsp->fRec4[0] = ((fSlow1 * dsp->fRec4[1]) + (fSlow2 * log10f(max(1.00000001e-07f, (mydsp_faustpower2_f(fabsf((((0.195090324f * fTemp20) + (((0.382683426f * fTemp25) + (fTemp31 + fTemp35)) + (0.980785251f * fTemp40))) - dsp->fVec1[((dsp->IOTA - 16) & 31)]))) + mydsp_faustpower2_f(fabsf((((0.980785251f * fTemp20) + (fTemp41 + fTemp42)) - ((fTemp44 + (0.382683426f * fTemp34)) + (0.195090324f * fTemp40))))))))));
			dsp->fVbargraph1 = (FAUSTFLOAT)(fSlow0 + dsp->fRec4[0]);
			float fTemp45 = (dsp->fVec1[((dsp->IOTA - 13) & 31)] + dsp->fVec1[((dsp->IOTA - 29) & 31)]);
			float fTemp46 = (dsp->fVec1[((dsp->IOTA - 7) & 31)] + dsp->fVec1[((dsp->IOTA - 23) & 31)]);
			float fTemp47 = (fTemp46 - (dsp->fVec1[((dsp->IOTA - 15) & 31)] + dsp->fVec1[((dsp->IOTA - 31) & 31)]));
			float fTemp48 = (0.0f - fTemp47);
			float fTemp49 = (dsp->fVec1[((dsp->IOTA - 5) & 31)] + dsp->fVec1[((dsp->IOTA - 21) & 31)]);
			float fTemp50 = (dsp->fVec1[((dsp->IOTA - 3) & 31)] + dsp->fVec1[((dsp->IOTA - 19) & 31)]);
			float fTemp51 = (fTemp50 - (dsp->fVec1[((dsp->IOTA - 11) & 31)] + dsp->fVec1[((dsp->IOTA - 27) & 31)]));
			float fTemp52 = (0.707106769f * fTemp51);
			float fTemp53 = ((fTemp45 + (0.707106769f * fTemp48)) - (fTemp49 + fTemp52));
			float fTemp54 = (dsp->fVec1[((dsp->IOTA - 6) & 31)] + dsp->fVec1[((dsp->IOTA - 22) & 31)]);
			float fTemp55 = (fTemp54 - (dsp->fVec1[((dsp->IOTA - 14) & 31)] + dsp->fVec1[((dsp->IOTA - 30) & 31)]));
			float fTemp56 = (0.0f - fTemp55);
			float fTemp57 = (0.707106769f * fTemp56);
			float fTemp58 = (dsp->fVec1[((dsp->IOTA - 2) & 31)] + dsp->fVec1[((dsp->IOTA - 18) & 31)]);
			float fTemp59 = (fTemp58 - (dsp->fVec1[((dsp->IOTA - 10) & 31)] + dsp->fVec1[((dsp->IOTA - 26) & 31)]));
			float fTemp60 = (0.707106769f * fTemp59);
			float fTemp61 = (0.707106769f * fTemp48);
			float fTemp62 = (dsp->fVec1[((dsp->IOTA - 1) & 31)] + dsp->fVec1[((dsp->IOTA - 17) & 31)]);
			float fTemp63 = (0.707106769f * fTemp51);
			float fTemp64 = (dsp->fVec1[((dsp->IOTA - 9) & 31)] + dsp->fVec1[((dsp->IOTA - 25) & 31)]);
			float fTemp65 = ((fTemp61 + (fTemp62 + fTemp63)) - fTemp64);
			float fTemp66 = (dsp->fVec1[((dsp->IOTA - 8) & 31)] + dsp->fVec1[((dsp->IOTA - 24) & 31)]);
			float fTemp67 = (dsp->fVec1[((dsp->IOTA - 12) & 31)] + dsp->fVec1[((dsp->IOTA - 28) & 31)]);
			float fTemp68 = (dsp->fVec1[((dsp->IOTA - 4) & 31)] + dsp->fVec1[((dsp->IOTA - 20) & 31)]);
			float fTemp69 = (0.707106769f * fTemp59);
			dsp->fRec5[0] = ((fSlow1 * dsp->fRec5[1]) + (fSlow2 * log10f(max(1.00000001e-07f, (mydsp_faustpower2_f(fabsf((((0.382683426f * fTemp53) + ((fTemp57 + (fTemp1 + fTemp60)) + (0.923879504f * fTemp65))) - fTemp66))) + mydsp_faustpower2_f(fabsf((((0.923879504f * fTemp53) + (fTemp67 + (0.707106769f * fTemp56))) - ((0.382683426f * fTemp65) + (fTemp68 + fTemp69))))))))));
			dsp->fVbargraph2 = (FAUSTFLOAT)(fSlow0 + dsp->fRec5[0]);
			float fTemp70 = (0.707106769f * fTemp5);
			float fTemp71 = (dsp->fVec1[((dsp->IOTA - 11) & 31)] - (fTemp70 + (dsp->fVec1[((dsp->IOTA - 27) & 31)] + fTemp18)));
			float fTemp72 = (0.707106769f * fTemp11);
			float fTemp73 = (fTemp72 + (dsp->fVec1[((dsp->IOTA - 25) & 31)] + fTemp37));
			float fTemp74 = ((dsp->fVec1[((dsp->IOTA - 3) & 31)] + (0.707106769f * fTemp5)) - (dsp->fVec1[((dsp->IOTA - 19) & 31)] + fTemp8));
			float fTemp75 = ((dsp->fVec1[((dsp->IOTA - 9) & 31)] + (0.382683426f * fTemp71)) - (fTemp73 + (0.923879504f * fTemp74)));
			float fTemp76 = (0.707106769f * fTemp21);
			float fTemp77 = (dsp->fVec1[((dsp->IOTA - 10) & 31)] - (fTemp76 + (dsp->fVec1[((dsp->IOTA - 26) & 31)] + fTemp33)));
			float fTemp78 = (fTemp0 + (0.707106769f * fTemp26));
			float fTemp79 = ((dsp->fVec1[((dsp->IOTA - 2) & 31)] + (0.707106769f * fTemp21)) - (dsp->fVec1[((dsp->IOTA - 18) & 31)] + fTemp24));
			float fTemp80 = (dsp->fVec1[((dsp->IOTA - 1) & 31)] + (0.707106769f * fTemp11));
			float fTemp81 = (dsp->fVec1[((dsp->IOTA - 17) & 31)] + fTemp15);
			float fTemp82 = (((0.923879504f * fTemp71) + (fTemp80 + (0.382683426f * fTemp74))) - fTemp81);
			float fTemp83 = (dsp->fVec1[((dsp->IOTA - 16) & 31)] + fTemp43);
			float fTemp84 = (0.707106769f * fTemp26);
			float fTemp85 = (fTemp84 + (dsp->fVec1[((dsp->IOTA - 24) & 31)] + fTemp30));
			dsp->fRec6[0] = ((fSlow1 * dsp->fRec6[1]) + (fSlow2 * log10f(max(1.00000001e-07f, (mydsp_faustpower2_f(fabsf((((0.555570245f * fTemp75) + (((0.923879504f * fTemp77) + (fTemp78 + (0.382683426f * fTemp79))) + (0.831469595f * fTemp82))) - fTemp83))) + mydsp_faustpower2_f(fabsf((((0.831469595f * fTemp75) + (dsp->fVec1[((dsp->IOTA - 8) & 31)] + (0.382683426f * fTemp77))) - ((fTemp85 + (0.923879504f * fTemp79)) + (0.555570245f * fTemp82))))))))));
			dsp->fVbargraph3 = (FAUSTFLOAT)(fSlow0 + dsp->fRec6[0]);
			float fTemp86 = (dsp->fVec1[((dsp->IOTA - 27) & 31)] + (fTemp50 + dsp->fVec1[((dsp->IOTA - 11) & 31)]));
			float fTemp87 = (fTemp86 - (dsp->fVec1[((dsp->IOTA - 31) & 31)] + (fTemp46 + dsp->fVec1[((dsp->IOTA - 15) & 31)])));
			float fTemp88 = (0.0f - fTemp87);
			float fTemp89 = (dsp->fVec1[((dsp->IOTA - 25) & 31)] + (fTemp62 + dsp->fVec1[((dsp->IOTA - 9) & 31)]));
			float fTemp90 = (fTemp89 - (dsp->fVec1[((dsp->IOTA - 29) & 31)] + (fTemp49 + dsp->fVec1[((dsp->IOTA - 13) & 31)])));
			float fTemp91 = (0.707106769f * fTemp90);
			float fTemp92 = (dsp->fVec1[((dsp->IOTA - 28) & 31)] + (fTemp68 + dsp->fVec1[((dsp->IOTA - 12) & 31)]));
			float fTemp93 = (dsp->fVec1[((dsp->IOTA - 30) & 31)] + (fTemp54 + dsp->fVec1[((dsp->IOTA - 14) & 31)]));
			float fTemp94 = (dsp->fVec1[((dsp->IOTA - 26) & 31)] + (fTemp58 + dsp->fVec1[((dsp->IOTA - 10) & 31)]));
			float fTemp95 = (0.707106769f * fTemp90);
			dsp->fRec7[0] = ((fSlow1 * dsp->fRec7[1]) + (fSlow2 * log10f(max(1.00000001e-07f, (mydsp_faustpower2_f(fabsf((((0.707106769f * fTemp88) + (fTemp2 + fTemp91)) - fTemp92))) + mydsp_faustpower2_f(fabsf(((fTemp93 + (0.707106769f * fTemp88)) - (fTemp94 + fTemp95)))))))));
			dsp->fVbargraph4 = (FAUSTFLOAT)(fSlow0 + dsp->fRec7[0]);
			float fTemp96 = (dsp->fVec1[((dsp->IOTA - 25) & 31)] + fTemp15);
			float fTemp97 = ((dsp->fVec1[((dsp->IOTA - 27) & 31)] + fTemp8) - (dsp->fVec1[((dsp->IOTA - 11) & 31)] + (0.707106769f * fTemp6)));
			float fTemp98 = (dsp->fVec1[((dsp->IOTA - 9) & 31)] + (0.707106769f * fTemp12));
			float fTemp99 = (0.707106769f * fTemp7);
			float fTemp100 = (dsp->fVec1[((dsp->IOTA - 3) & 31)] - (fTemp17 + (dsp->fVec1[((dsp->IOTA - 19) & 31)] + fTemp99)));
			float fTemp101 = (fTemp96 - ((0.382683426f * fTemp97) + (fTemp98 + (0.923879504f * fTemp100))));
			float fTemp102 = ((dsp->fVec1[((dsp->IOTA - 26) & 31)] + fTemp24) - (dsp->fVec1[((dsp->IOTA - 10) & 31)] + (0.707106769f * fTemp22)));
			float fTemp103 = (0.707106769f * fTemp14);
			float fTemp104 = (fTemp36 + (dsp->fVec1[((dsp->IOTA - 17) & 31)] + fTemp103));
			float fTemp105 = ((dsp->fVec1[((dsp->IOTA - 1) & 31)] + (0.923879504f * fTemp97)) - (fTemp104 + (0.382683426f * fTemp100)));
			float fTemp106 = (0.707106769f * fTemp29);
			float fTemp107 = (fTemp28 + (dsp->fVec1[((dsp->IOTA - 16) & 31)] + fTemp106));
			float fTemp108 = (0.707106769f * fTemp23);
			float fTemp109 = (dsp->fVec1[((dsp->IOTA - 2) & 31)] - (fTemp32 + (dsp->fVec1[((dsp->IOTA - 18) & 31)] + fTemp108)));
			float fTemp110 = (dsp->fVec1[((dsp->IOTA - 24) & 31)] + fTemp43);
			float fTemp111 = (dsp->fVec1[((dsp->IOTA - 8) & 31)] + (0.707106769f * fTemp27));
			dsp->fRec8[0] = ((fSlow1 * dsp->fRec8[1]) + (fSlow2 * log10f(max(1.00000001e-07f, (mydsp_faustpower2_f(fabsf((((0.831469595f * fTemp101) + ((fTemp0 + (0.923879504f * fTemp102)) + (0.555570245f * fTemp105))) - (fTemp107 + (0.382683426f * fTemp109))))) + mydsp_faustpower2_f(fabsf(((fTemp110 + (0.555570245f * fTemp101)) - ((0.831469595f * fTemp105) + ((0.382683426f * fTemp102) + (fTemp111 + (0.923879504f * fTemp109))))))))))));
			dsp->fVbargraph5 = (FAUSTFLOAT)(fSlow0 + dsp->fRec8[0]);
			float fTemp112 = (0.707106769f * fTemp47);
			float fTemp113 = (fTemp49 - (fTemp112 + (fTemp45 + fTemp63)));
			float fTemp114 = ((fTemp62 + (0.707106769f * fTemp47)) - (fTemp64 + fTemp52));
			float fTemp115 = (0.707106769f * fTemp55);
			dsp->fRec9[0] = ((fSlow1 * dsp->fRec9[1]) + (fSlow2 * log10f(max(1.00000001e-07f, (mydsp_faustpower2_f(fabsf((((0.923879504f * fTemp113) + ((fTemp1 + (0.707106769f * fTemp55)) + (0.382683426f * fTemp114))) - (fTemp66 + fTemp69)))) + mydsp_faustpower2_f(fabsf(((fTemp68 + (0.382683426f * fTemp113)) - ((0.923879504f * fTemp114) + (fTemp115 + (fTemp67 + fTemp60)))))))))));
			dsp->fVbargraph6 = (FAUSTFLOAT)(fSlow0 + dsp->fRec9[0]);
			float fTemp116 = (fTemp72 + (dsp->fVec1[((dsp->IOTA - 9) & 31)] + fTemp103));
			float fTemp117 = ((fTemp70 + (dsp->fVec1[((dsp->IOTA - 11) & 31)] + fTemp99)) - dsp->fVec1[((dsp->IOTA - 27) & 31)]);
			float fTemp118 = ((dsp->fVec1[((dsp->IOTA - 3) & 31)] + fTemp8) - (dsp->fVec1[((dsp->IOTA - 19) & 31)] + (0.707106769f * fTemp5)));
			float fTemp119 = (fTemp116 - ((0.923879504f * fTemp117) + (dsp->fVec1[((dsp->IOTA - 25) & 31)] + (0.382683426f * fTemp118))));
			float fTemp120 = (fTemp0 + fTemp43);
			float fTemp121 = ((fTemp76 + (dsp->fVec1[((dsp->IOTA - 10) & 31)] + fTemp108)) - dsp->fVec1[((dsp->IOTA - 26) & 31)]);
			float fTemp122 = (dsp->fVec1[((dsp->IOTA - 1) & 31)] + fTemp15);
			float fTemp123 = (dsp->fVec1[((dsp->IOTA - 17) & 31)] + (0.707106769f * fTemp11));
			float fTemp124 = ((fTemp122 + (0.382683426f * fTemp117)) - (fTemp123 + (0.923879504f * fTemp118)));
			float fTemp125 = (dsp->fVec1[((dsp->IOTA - 16) & 31)] + (0.707106769f * fTemp26));
			float fTemp126 = ((dsp->fVec1[((dsp->IOTA - 2) & 31)] + fTemp24) - (dsp->fVec1[((dsp->IOTA - 18) & 31)] + (0.707106769f * fTemp21)));
			float fTemp127 = (fTemp84 + (dsp->fVec1[((dsp->IOTA - 8) & 31)] + fTemp106));
			dsp->fRec10[0] = ((fSlow1 * dsp->fRec10[1]) + (fSlow2 * log10f(max(1.00000001e-07f, (mydsp_faustpower2_f(fabsf((((0.980785251f * fTemp119) + ((fTemp120 + (0.382683426f * fTemp121)) + (0.195090324f * fTemp124))) - (fTemp125 + (0.923879504f * fTemp126))))) + mydsp_faustpower2_f(fabsf(((fTemp127 + (0.195090324f * fTemp119)) - ((0.980785251f * fTemp124) + ((0.923879504f * fTemp121) + (dsp->fVec1[((dsp->IOTA - 24) & 31)] + (0.382683426f * fTemp126))))))))))));
			dsp->fVbargraph7 = (FAUSTFLOAT)(fSlow0 + dsp->fRec10[0]);
			float fTemp128 = (dsp->fVec1[((dsp->IOTA - 29) & 31)] + (dsp->fVec1[((dsp->IOTA - 13) & 31)] + (dsp->fVec1[((dsp->IOTA - 21) & 31)] + (dsp->fVec1[((dsp->IOTA - 5) & 31)] + fTemp89))));
			dsp->fRec11[0] = ((fSlow1 * dsp->fRec11[1]) + (fSlow2 * log10f(max(1.00000001e-07f, (mydsp_faustpower2_f(fabsf((fTemp3 - (dsp->fVec1[((dsp->IOTA - 30) & 31)] + (dsp->fVec1[((dsp->IOTA - 14) & 31)] + (dsp->fVec1[((dsp->IOTA - 22) & 31)] + (dsp->fVec1[((dsp->IOTA - 6) & 31)] + fTemp94))))))) + mydsp_faustpower2_f(fabsf((0.0f - (fTemp128 - (dsp->fVec1[((dsp->IOTA - 31) & 31)] + (dsp->fVec1[((dsp->IOTA - 15) & 31)] + (dsp->fVec1[((dsp->IOTA - 23) & 31)] + (dsp->fVec1[((dsp->IOTA - 7) & 31)] + fTemp86)))))))))))));
			dsp->fVbargraph8 = (FAUSTFLOAT)(fSlow0 + dsp->fRec11[0]);
			float fTemp129 = ((fTemp13 + (0.382683426f * fTemp19)) - (fTemp10 + fTemp16));
			float fTemp130 = (fTemp38 - ((0.382683426f * fTemp9) + (dsp->fVec1[((dsp->IOTA - 17) & 31)] + fTemp39)));
			dsp->fRec12[0] = ((fSlow1 * dsp->fRec12[1]) + (fSlow2 * log10f(max(1.00000001e-07f, (mydsp_faustpower2_f(fabsf(((fTemp31 + (0.980785251f * fTemp129)) - (((0.382683426f * fTemp25) + (dsp->fVec1[((dsp->IOTA - 16) & 31)] + fTemp35)) + (0.195090324f * fTemp130))))) + mydsp_faustpower2_f(fabsf(((fTemp42 + (0.382683426f * fTemp34)) - ((0.195090324f * fTemp129) + ((fTemp41 + fTemp44) + (0.980785251f * fTemp130)))))))))));
			dsp->fVbargraph9 = (FAUSTFLOAT)(fSlow0 + dsp->fRec12[0]);
			float fTemp131 = ((fTemp45 + fTemp52) - (fTemp49 + (0.707106769f * fTemp48)));
			float fTemp132 = (0.707106769f * fTemp59);
			float fTemp133 = (0.707106769f * fTemp51);
			float fTemp134 = (fTemp62 - (fTemp61 + (fTemp64 + fTemp133)));
			dsp->fRec13[0] = ((fSlow1 * dsp->fRec13[1]) + (fSlow2 * log10f(max(1.00000001e-07f, (mydsp_faustpower2_f(fabsf(((fTemp1 + (0.923879504f * fTemp131)) - ((fTemp57 + (fTemp66 + fTemp132)) + (0.382683426f * fTemp134))))) + mydsp_faustpower2_f(fabsf(((fTemp67 + fTemp69) - ((0.382683426f * fTemp131) + ((fTemp68 + (0.707106769f * fTemp56)) + (0.923879504f * fTemp134)))))))))));
			dsp->fVbargraph10 = (FAUSTFLOAT)(fSlow0 + dsp->fRec13[0]);
			float fTemp135 = ((dsp->fVec1[((dsp->IOTA - 9) & 31)] + (0.923879504f * fTemp74)) - (fTemp73 + (0.382683426f * fTemp71)));
			float fTemp136 = (fTemp80 - ((0.923879504f * fTemp71) + (fTemp81 + (0.382683426f * fTemp74))));
			dsp->fRec14[0] = ((fSlow1 * dsp->fRec14[1]) + (fSlow2 * log10f(max(1.00000001e-07f, (mydsp_faustpower2_f(fabsf(((fTemp78 + (0.831469595f * fTemp135)) - (((0.923879504f * fTemp77) + (fTemp83 + (0.382683426f * fTemp79))) + (0.555570245f * fTemp136))))) + mydsp_faustpower2_f(fabsf(((dsp->fVec1[((dsp->IOTA - 8) & 31)] + (0.923879504f * fTemp79)) - ((0.555570245f * fTemp135) + ((fTemp85 + (0.382683426f * fTemp77)) + (0.831469595f * fTemp136)))))))))));
			dsp->fVbargraph11 = (FAUSTFLOAT)(fSlow0 + dsp->fRec14[0]);
			dsp->fRec15[0] = ((fSlow1 * dsp->fRec15[1]) + (fSlow2 * log10f(max(1.00000001e-07f, (mydsp_faustpower2_f(fabsf(((fTemp2 + (0.707106769f * fTemp87)) - (fTemp92 + fTemp95)))) + mydsp_faustpower2_f(fabsf((fTemp94 - ((0.707106769f * fTemp87) + (fTemp93 + fTemp91))))))))));
			dsp->fVbargraph12 = (FAUSTFLOAT)(fSlow0 + dsp->fRec15[0]);
			float fTemp137 = (((0.382683426f * fTemp97) + (fTemp96 + (0.923879504f * fTemp100))) - fTemp98);
			float fTemp138 = ((dsp->fVec1[((dsp->IOTA - 1) & 31)] + (0.382683426f * fTemp100)) - (fTemp104 + (0.923879504f * fTemp97)));
			dsp->fRec16[0] = ((fSlow1 * dsp->fRec16[1]) + (fSlow2 * log10f(max(1.00000001e-07f, (mydsp_faustpower2_f(fabsf((((fTemp0 + (0.382683426f * fTemp109)) + (0.555570245f * fTemp137)) - ((fTemp107 + (0.923879504f * fTemp102)) + (0.831469595f * fTemp138))))) + mydsp_faustpower2_f(fabsf((((0.382683426f * fTemp102) + (fTemp110 + (0.923879504f * fTemp109))) - ((0.831469595f * fTemp137) + (fTemp111 + (0.555570245f * fTemp138)))))))))));
			dsp->fVbargraph13 = (FAUSTFLOAT)(fSlow0 + dsp->fRec16[0]);
			float fTemp139 = ((fTemp112 + (fTemp49 + fTemp133)) - fTemp45);
			float fTemp140 = ((fTemp62 + fTemp52) - (fTemp64 + (0.707106769f * fTemp47)));
			dsp->fRec17[0] = ((fSlow1 * dsp->fRec17[1]) + (fSlow2 * log10f(max(1.00000001e-07f, (mydsp_faustpower2_f(fabsf((((fTemp1 + fTemp69) + (0.382683426f * fTemp139)) - ((fTemp66 + (0.707106769f * fTemp55)) + (0.923879504f * fTemp140))))) + mydsp_faustpower2_f(fabsf(((fTemp115 + (fTemp68 + fTemp132)) - ((0.923879504f * fTemp139) + (fTemp67 + (0.382683426f * fTemp140)))))))))));
			dsp->fVbargraph14 = (FAUSTFLOAT)(fSlow0 + dsp->fRec17[0]);
			float fTemp141 = (((0.923879504f * fTemp117) + (fTemp116 + (0.382683426f * fTemp118))) - dsp->fVec1[((dsp->IOTA - 25) & 31)]);
			float fTemp142 = ((fTemp122 + (0.923879504f * fTemp118)) - (fTemp123 + (0.382683426f * fTemp117)));
			dsp->fRec18[0] = ((fSlow1 * dsp->fRec18[1]) + (fSlow2 * log10f(max(1.00000001e-07f, (mydsp_faustpower2_f(fabsf((((fTemp120 + (0.923879504f * fTemp126)) + (0.195090324f * fTemp141)) - ((fTemp125 + (0.382683426f * fTemp121)) + (0.980785251f * fTemp142))))) + mydsp_faustpower2_f(fabsf((((0.923879504f * fTemp121) + (fTemp127 + (0.382683426f * fTemp126))) - ((0.980785251f * fTemp141) + (dsp->fVec1[((dsp->IOTA - 24) & 31)] + (0.195090324f * fTemp142)))))))))));
			dsp->fVbargraph15 = (FAUSTFLOAT)(fSlow0 + dsp->fRec18[0]);
			dsp->fRec19[0] = ((fSlow1 * dsp->fRec19[1]) + (fSlow2 * log10f(max(1.00000001e-07f, mydsp_faustpower2_f(fabsf((fTemp4 - (dsp->fVec1[((dsp->IOTA - 31) & 31)] + (dsp->fVec1[((dsp->IOTA - 15) & 31)] + (dsp->fVec1[((dsp->IOTA - 23) & 31)] + (dsp->fVec1[((dsp->IOTA - 7) & 31)] + (dsp->fVec1[((dsp->IOTA - 27) & 31)] + (dsp->fVec1[((dsp->IOTA - 11) & 31)] + (dsp->fVec1[((dsp->IOTA - 19) & 31)] + (dsp->fVec1[((dsp->IOTA - 3) & 31)] + fTemp128)))))))))))))));
			dsp->fVbargraph16 = (FAUSTFLOAT)(fSlow0 + dsp->fRec19[0]);
			output0[i] = (FAUSTFLOAT)fTemp0;
			output1[i] = (FAUSTFLOAT)fTemp0;
			dsp->iVec0[1] = dsp->iVec0[0];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->iRec3[1] = dsp->iRec3[0];
			dsp->IOTA = (dsp->IOTA + 1);
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fRec5[1] = dsp->fRec5[0];
			dsp->fRec6[1] = dsp->fRec6[0];
			dsp->fRec7[1] = dsp->fRec7[0];
			dsp->fRec8[1] = dsp->fRec8[0];
			dsp->fRec9[1] = dsp->fRec9[0];
			dsp->fRec10[1] = dsp->fRec10[0];
			dsp->fRec11[1] = dsp->fRec11[0];
			dsp->fRec12[1] = dsp->fRec12[0];
			dsp->fRec13[1] = dsp->fRec13[0];
			dsp->fRec14[1] = dsp->fRec14[0];
			dsp->fRec15[1] = dsp->fRec15[0];
			dsp->fRec16[1] = dsp->fRec16[0];
			dsp->fRec17[1] = dsp->fRec17[0];
			dsp->fRec18[1] = dsp->fRec18[0];
			dsp->fRec19[1] = dsp->fRec19[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
