/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2006"
license: "BSD"
name: "multibandFilter"
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
	FAUSTFLOAT fEntry0;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT fEntry1;
	FAUSTFLOAT fEntry2;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fEntry3;
	FAUSTFLOAT fEntry4;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT fEntry5;
	FAUSTFLOAT fEntry6;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT fEntry7;
	FAUSTFLOAT fEntry8;
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT fEntry9;
	FAUSTFLOAT fEntry10;
	FAUSTFLOAT fVslider5;
	FAUSTFLOAT fEntry11;
	FAUSTFLOAT fEntry12;
	FAUSTFLOAT fVslider6;
	FAUSTFLOAT fEntry13;
	FAUSTFLOAT fEntry14;
	FAUSTFLOAT fVslider7;
	FAUSTFLOAT fEntry15;
	FAUSTFLOAT fEntry16;
	FAUSTFLOAT fVslider8;
	FAUSTFLOAT fEntry17;
	FAUSTFLOAT fEntry18;
	FAUSTFLOAT fVslider9;
	FAUSTFLOAT fEntry19;
	float fRec9[3];
	float fRec8[3];
	float fRec7[3];
	float fRec6[3];
	float fRec5[3];
	float fRec4[3];
	float fRec3[3];
	float fRec2[3];
	float fRec1[3];
	float fRec0[3];
	
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
	m->declare(m->metaInterface, "bandfilter.dsp/author", "Grame");
	m->declare(m->metaInterface, "bandfilter.dsp/copyright", "(c)GRAME 2006");
	m->declare(m->metaInterface, "bandfilter.dsp/license", "BSD");
	m->declare(m->metaInterface, "bandfilter.dsp/name", "bandFilter");
	m->declare(m->metaInterface, "bandfilter.dsp/version", "1.0");
	m->declare(m->metaInterface, "basics.lib/name", "Faust Basic Element Library");
	m->declare(m->metaInterface, "basics.lib/version", "0.0");
	m->declare(m->metaInterface, "copyright", "(c)GRAME 2006");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "license", "BSD");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "multibandFilter");
	m->declare(m->metaInterface, "version", "1.0");
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
	dsp->fEntry0 = (FAUSTFLOAT)10000.0f;
	dsp->fVslider0 = (FAUSTFLOAT)0.0f;
	dsp->fEntry1 = (FAUSTFLOAT)50.0f;
	dsp->fEntry2 = (FAUSTFLOAT)9000.0f;
	dsp->fVslider1 = (FAUSTFLOAT)0.0f;
	dsp->fEntry3 = (FAUSTFLOAT)50.0f;
	dsp->fEntry4 = (FAUSTFLOAT)8000.0f;
	dsp->fVslider2 = (FAUSTFLOAT)0.0f;
	dsp->fEntry5 = (FAUSTFLOAT)50.0f;
	dsp->fEntry6 = (FAUSTFLOAT)7000.0f;
	dsp->fVslider3 = (FAUSTFLOAT)0.0f;
	dsp->fEntry7 = (FAUSTFLOAT)50.0f;
	dsp->fEntry8 = (FAUSTFLOAT)6000.0f;
	dsp->fVslider4 = (FAUSTFLOAT)0.0f;
	dsp->fEntry9 = (FAUSTFLOAT)50.0f;
	dsp->fEntry10 = (FAUSTFLOAT)5000.0f;
	dsp->fVslider5 = (FAUSTFLOAT)0.0f;
	dsp->fEntry11 = (FAUSTFLOAT)50.0f;
	dsp->fEntry12 = (FAUSTFLOAT)4000.0f;
	dsp->fVslider6 = (FAUSTFLOAT)0.0f;
	dsp->fEntry13 = (FAUSTFLOAT)50.0f;
	dsp->fEntry14 = (FAUSTFLOAT)3000.0f;
	dsp->fVslider7 = (FAUSTFLOAT)0.0f;
	dsp->fEntry15 = (FAUSTFLOAT)50.0f;
	dsp->fEntry16 = (FAUSTFLOAT)2000.0f;
	dsp->fVslider8 = (FAUSTFLOAT)0.0f;
	dsp->fEntry17 = (FAUSTFLOAT)50.0f;
	dsp->fEntry18 = (FAUSTFLOAT)1000.0f;
	dsp->fVslider9 = (FAUSTFLOAT)0.0f;
	dsp->fEntry19 = (FAUSTFLOAT)50.0f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 3); l0 = (l0 + 1)) {
			dsp->fRec9[l0] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 3); l1 = (l1 + 1)) {
			dsp->fRec8[l1] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 3); l2 = (l2 + 1)) {
			dsp->fRec7[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 3); l3 = (l3 + 1)) {
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
		for (l5 = 0; (l5 < 3); l5 = (l5 + 1)) {
			dsp->fRec4[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 3); l6 = (l6 + 1)) {
			dsp->fRec3[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			dsp->fRec2[l7] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
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
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = (3.14159274f / min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq)));
	
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
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "Multi Band Filter");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "peak 0");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry19, "style", "knob");
	ui_interface->addNumEntry(ui_interface->uiInterface, "Q factor", &dsp->fEntry19, 50.0f, 0.100000001f, 100.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry18, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry18, "unit", "Hz");
	ui_interface->addNumEntry(ui_interface->uiInterface, "freq", &dsp->fEntry18, 1000.0f, 20.0f, 20000.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider9, "unit", "dB");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "gain", &dsp->fVslider9, 0.0f, -50.0f, 50.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "peak 1");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry17, "style", "knob");
	ui_interface->addNumEntry(ui_interface->uiInterface, "Q factor", &dsp->fEntry17, 50.0f, 0.100000001f, 100.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry16, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry16, "unit", "Hz");
	ui_interface->addNumEntry(ui_interface->uiInterface, "freq", &dsp->fEntry16, 2000.0f, 20.0f, 20000.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider8, "unit", "dB");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "gain", &dsp->fVslider8, 0.0f, -50.0f, 50.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "peak 2");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry15, "style", "knob");
	ui_interface->addNumEntry(ui_interface->uiInterface, "Q factor", &dsp->fEntry15, 50.0f, 0.100000001f, 100.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry14, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry14, "unit", "Hz");
	ui_interface->addNumEntry(ui_interface->uiInterface, "freq", &dsp->fEntry14, 3000.0f, 20.0f, 20000.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider7, "unit", "dB");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "gain", &dsp->fVslider7, 0.0f, -50.0f, 50.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "peak 3");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry13, "style", "knob");
	ui_interface->addNumEntry(ui_interface->uiInterface, "Q factor", &dsp->fEntry13, 50.0f, 0.100000001f, 100.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry12, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry12, "unit", "Hz");
	ui_interface->addNumEntry(ui_interface->uiInterface, "freq", &dsp->fEntry12, 4000.0f, 20.0f, 20000.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider6, "unit", "dB");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "gain", &dsp->fVslider6, 0.0f, -50.0f, 50.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "peak 4");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry11, "style", "knob");
	ui_interface->addNumEntry(ui_interface->uiInterface, "Q factor", &dsp->fEntry11, 50.0f, 0.100000001f, 100.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry10, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry10, "unit", "Hz");
	ui_interface->addNumEntry(ui_interface->uiInterface, "freq", &dsp->fEntry10, 5000.0f, 20.0f, 20000.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider5, "unit", "dB");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "gain", &dsp->fVslider5, 0.0f, -50.0f, 50.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "peak 5");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry9, "style", "knob");
	ui_interface->addNumEntry(ui_interface->uiInterface, "Q factor", &dsp->fEntry9, 50.0f, 0.100000001f, 100.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry8, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry8, "unit", "Hz");
	ui_interface->addNumEntry(ui_interface->uiInterface, "freq", &dsp->fEntry8, 6000.0f, 20.0f, 20000.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider4, "unit", "dB");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "gain", &dsp->fVslider4, 0.0f, -50.0f, 50.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "peak 6");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry7, "style", "knob");
	ui_interface->addNumEntry(ui_interface->uiInterface, "Q factor", &dsp->fEntry7, 50.0f, 0.100000001f, 100.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry6, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry6, "unit", "Hz");
	ui_interface->addNumEntry(ui_interface->uiInterface, "freq", &dsp->fEntry6, 7000.0f, 20.0f, 20000.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider3, "unit", "dB");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "gain", &dsp->fVslider3, 0.0f, -50.0f, 50.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "peak 7");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry5, "style", "knob");
	ui_interface->addNumEntry(ui_interface->uiInterface, "Q factor", &dsp->fEntry5, 50.0f, 0.100000001f, 100.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry4, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry4, "unit", "Hz");
	ui_interface->addNumEntry(ui_interface->uiInterface, "freq", &dsp->fEntry4, 8000.0f, 20.0f, 20000.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider2, "unit", "dB");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "gain", &dsp->fVslider2, 0.0f, -50.0f, 50.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "peak 8");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry3, "style", "knob");
	ui_interface->addNumEntry(ui_interface->uiInterface, "Q factor", &dsp->fEntry3, 50.0f, 0.100000001f, 100.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry2, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry2, "unit", "Hz");
	ui_interface->addNumEntry(ui_interface->uiInterface, "freq", &dsp->fEntry2, 9000.0f, 20.0f, 20000.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider1, "unit", "dB");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "gain", &dsp->fVslider1, 0.0f, -50.0f, 50.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "peak 9");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry1, "style", "knob");
	ui_interface->addNumEntry(ui_interface->uiInterface, "Q factor", &dsp->fEntry1, 50.0f, 0.100000001f, 100.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry0, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry0, "unit", "Hz");
	ui_interface->addNumEntry(ui_interface->uiInterface, "freq", &dsp->fEntry0, 10000.0f, 20.0f, 20000.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider0, "unit", "dB");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "gain", &dsp->fVslider0, 0.0f, -50.0f, 50.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* input0 = inputs[0];
	FAUSTFLOAT* output0 = outputs[0];
	float fSlow0 = tanf((dsp->fConst0 * (float)dsp->fEntry0));
	float fSlow1 = (float)dsp->fEntry1;
	float fSlow2 = (powf(10.0f, (0.0500000007f * (0.0f - (float)dsp->fVslider0))) / fSlow1);
	float fSlow3 = (1.0f / ((fSlow0 * (fSlow0 + fSlow2)) + 1.0f));
	float fSlow4 = (2.0f * (mydsp_faustpower2_f(fSlow0) + -1.0f));
	float fSlow5 = tanf((dsp->fConst0 * (float)dsp->fEntry2));
	float fSlow6 = (float)dsp->fEntry3;
	float fSlow7 = (powf(10.0f, (0.0500000007f * (0.0f - (float)dsp->fVslider1))) / fSlow6);
	float fSlow8 = (1.0f / ((fSlow5 * (fSlow5 + fSlow7)) + 1.0f));
	float fSlow9 = (2.0f * (mydsp_faustpower2_f(fSlow5) + -1.0f));
	float fSlow10 = tanf((dsp->fConst0 * (float)dsp->fEntry4));
	float fSlow11 = (float)dsp->fEntry5;
	float fSlow12 = (powf(10.0f, (0.0500000007f * (0.0f - (float)dsp->fVslider2))) / fSlow11);
	float fSlow13 = (1.0f / ((fSlow10 * (fSlow10 + fSlow12)) + 1.0f));
	float fSlow14 = (2.0f * (mydsp_faustpower2_f(fSlow10) + -1.0f));
	float fSlow15 = tanf((dsp->fConst0 * (float)dsp->fEntry6));
	float fSlow16 = (float)dsp->fEntry7;
	float fSlow17 = (powf(10.0f, (0.0500000007f * (0.0f - (float)dsp->fVslider3))) / fSlow16);
	float fSlow18 = (1.0f / ((fSlow15 * (fSlow15 + fSlow17)) + 1.0f));
	float fSlow19 = (2.0f * (mydsp_faustpower2_f(fSlow15) + -1.0f));
	float fSlow20 = tanf((dsp->fConst0 * (float)dsp->fEntry8));
	float fSlow21 = (float)dsp->fEntry9;
	float fSlow22 = (powf(10.0f, (0.0500000007f * (0.0f - (float)dsp->fVslider4))) / fSlow21);
	float fSlow23 = (1.0f / ((fSlow20 * (fSlow20 + fSlow22)) + 1.0f));
	float fSlow24 = (2.0f * (mydsp_faustpower2_f(fSlow20) + -1.0f));
	float fSlow25 = tanf((dsp->fConst0 * (float)dsp->fEntry10));
	float fSlow26 = (float)dsp->fEntry11;
	float fSlow27 = (powf(10.0f, (0.0500000007f * (0.0f - (float)dsp->fVslider5))) / fSlow26);
	float fSlow28 = (1.0f / ((fSlow25 * (fSlow25 + fSlow27)) + 1.0f));
	float fSlow29 = (2.0f * (mydsp_faustpower2_f(fSlow25) + -1.0f));
	float fSlow30 = tanf((dsp->fConst0 * (float)dsp->fEntry12));
	float fSlow31 = (float)dsp->fEntry13;
	float fSlow32 = (powf(10.0f, (0.0500000007f * (0.0f - (float)dsp->fVslider6))) / fSlow31);
	float fSlow33 = (1.0f / ((fSlow30 * (fSlow30 + fSlow32)) + 1.0f));
	float fSlow34 = (2.0f * (mydsp_faustpower2_f(fSlow30) + -1.0f));
	float fSlow35 = tanf((dsp->fConst0 * (float)dsp->fEntry14));
	float fSlow36 = (float)dsp->fEntry15;
	float fSlow37 = (powf(10.0f, (0.0500000007f * (0.0f - (float)dsp->fVslider7))) / fSlow36);
	float fSlow38 = (1.0f / ((fSlow35 * (fSlow35 + fSlow37)) + 1.0f));
	float fSlow39 = (2.0f * (mydsp_faustpower2_f(fSlow35) + -1.0f));
	float fSlow40 = tanf((dsp->fConst0 * (float)dsp->fEntry16));
	float fSlow41 = (float)dsp->fEntry17;
	float fSlow42 = (powf(10.0f, (0.0500000007f * (0.0f - (float)dsp->fVslider8))) / fSlow41);
	float fSlow43 = (1.0f / ((fSlow40 * (fSlow40 + fSlow42)) + 1.0f));
	float fSlow44 = (2.0f * (mydsp_faustpower2_f(fSlow40) + -1.0f));
	float fSlow45 = tanf((dsp->fConst0 * (float)dsp->fEntry18));
	float fSlow46 = (float)dsp->fEntry19;
	float fSlow47 = (powf(10.0f, (0.0500000007f * (0.0f - (float)dsp->fVslider9))) / fSlow46);
	float fSlow48 = (1.0f / ((fSlow45 * (fSlow45 + fSlow47)) + 1.0f));
	float fSlow49 = (2.0f * (mydsp_faustpower2_f(fSlow45) + -1.0f));
	float fSlow50 = ((fSlow45 * (fSlow45 - fSlow47)) + 1.0f);
	float fSlow51 = (1.0f / fSlow46);
	float fSlow52 = ((fSlow45 * (fSlow45 + fSlow51)) + 1.0f);
	float fSlow53 = (1.0f - (fSlow45 * (fSlow51 - fSlow45)));
	float fSlow54 = ((fSlow40 * (fSlow40 - fSlow42)) + 1.0f);
	float fSlow55 = (1.0f / fSlow41);
	float fSlow56 = ((fSlow40 * (fSlow40 + fSlow55)) + 1.0f);
	float fSlow57 = (1.0f - (fSlow40 * (fSlow55 - fSlow40)));
	float fSlow58 = ((fSlow35 * (fSlow35 - fSlow37)) + 1.0f);
	float fSlow59 = (1.0f / fSlow36);
	float fSlow60 = ((fSlow35 * (fSlow35 + fSlow59)) + 1.0f);
	float fSlow61 = (1.0f - (fSlow35 * (fSlow59 - fSlow35)));
	float fSlow62 = ((fSlow30 * (fSlow30 - fSlow32)) + 1.0f);
	float fSlow63 = (1.0f / fSlow31);
	float fSlow64 = ((fSlow30 * (fSlow30 + fSlow63)) + 1.0f);
	float fSlow65 = (1.0f - (fSlow30 * (fSlow63 - fSlow30)));
	float fSlow66 = ((fSlow25 * (fSlow25 - fSlow27)) + 1.0f);
	float fSlow67 = (1.0f / fSlow26);
	float fSlow68 = ((fSlow25 * (fSlow25 + fSlow67)) + 1.0f);
	float fSlow69 = (1.0f - (fSlow25 * (fSlow67 - fSlow25)));
	float fSlow70 = ((fSlow20 * (fSlow20 - fSlow22)) + 1.0f);
	float fSlow71 = (1.0f / fSlow21);
	float fSlow72 = ((fSlow20 * (fSlow20 + fSlow71)) + 1.0f);
	float fSlow73 = (1.0f - (fSlow20 * (fSlow71 - fSlow20)));
	float fSlow74 = ((fSlow15 * (fSlow15 - fSlow17)) + 1.0f);
	float fSlow75 = (1.0f / fSlow16);
	float fSlow76 = ((fSlow15 * (fSlow15 + fSlow75)) + 1.0f);
	float fSlow77 = (1.0f - (fSlow15 * (fSlow75 - fSlow15)));
	float fSlow78 = ((fSlow10 * (fSlow10 - fSlow12)) + 1.0f);
	float fSlow79 = (1.0f / fSlow11);
	float fSlow80 = ((fSlow10 * (fSlow10 + fSlow79)) + 1.0f);
	float fSlow81 = (1.0f - (fSlow10 * (fSlow79 - fSlow10)));
	float fSlow82 = ((fSlow5 * (fSlow5 - fSlow7)) + 1.0f);
	float fSlow83 = (1.0f / fSlow6);
	float fSlow84 = ((fSlow5 * (fSlow5 + fSlow83)) + 1.0f);
	float fSlow85 = (1.0f - (fSlow5 * (fSlow83 - fSlow5)));
	float fSlow86 = ((fSlow0 * (fSlow0 - fSlow2)) + 1.0f);
	float fSlow87 = (1.0f / fSlow1);
	float fSlow88 = ((fSlow0 * (fSlow0 + fSlow87)) + 1.0f);
	float fSlow89 = (1.0f - (fSlow0 * (fSlow87 - fSlow0)));
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = (fSlow49 * dsp->fRec9[1]);
			dsp->fRec9[0] = ((float)input0[i] - (fSlow48 * ((fSlow50 * dsp->fRec9[2]) + fTemp0)));
			float fTemp1 = (fSlow44 * dsp->fRec8[1]);
			dsp->fRec8[0] = ((fSlow48 * ((fTemp0 + (fSlow52 * dsp->fRec9[0])) + (fSlow53 * dsp->fRec9[2]))) - (fSlow43 * ((fSlow54 * dsp->fRec8[2]) + fTemp1)));
			float fTemp2 = (fSlow39 * dsp->fRec7[1]);
			dsp->fRec7[0] = ((fSlow43 * ((fTemp1 + (fSlow56 * dsp->fRec8[0])) + (fSlow57 * dsp->fRec8[2]))) - (fSlow38 * ((fSlow58 * dsp->fRec7[2]) + fTemp2)));
			float fTemp3 = (fSlow34 * dsp->fRec6[1]);
			dsp->fRec6[0] = ((fSlow38 * ((fTemp2 + (fSlow60 * dsp->fRec7[0])) + (fSlow61 * dsp->fRec7[2]))) - (fSlow33 * ((fSlow62 * dsp->fRec6[2]) + fTemp3)));
			float fTemp4 = (fSlow29 * dsp->fRec5[1]);
			dsp->fRec5[0] = ((fSlow33 * ((fTemp3 + (fSlow64 * dsp->fRec6[0])) + (fSlow65 * dsp->fRec6[2]))) - (fSlow28 * ((fSlow66 * dsp->fRec5[2]) + fTemp4)));
			float fTemp5 = (fSlow24 * dsp->fRec4[1]);
			dsp->fRec4[0] = ((fSlow28 * ((fTemp4 + (fSlow68 * dsp->fRec5[0])) + (fSlow69 * dsp->fRec5[2]))) - (fSlow23 * ((fSlow70 * dsp->fRec4[2]) + fTemp5)));
			float fTemp6 = (fSlow19 * dsp->fRec3[1]);
			dsp->fRec3[0] = ((fSlow23 * ((fTemp5 + (fSlow72 * dsp->fRec4[0])) + (fSlow73 * dsp->fRec4[2]))) - (fSlow18 * ((fSlow74 * dsp->fRec3[2]) + fTemp6)));
			float fTemp7 = (fSlow14 * dsp->fRec2[1]);
			dsp->fRec2[0] = ((fSlow18 * ((fTemp6 + (fSlow76 * dsp->fRec3[0])) + (fSlow77 * dsp->fRec3[2]))) - (fSlow13 * ((fSlow78 * dsp->fRec2[2]) + fTemp7)));
			float fTemp8 = (fSlow9 * dsp->fRec1[1]);
			dsp->fRec1[0] = ((fSlow13 * ((fTemp7 + (fSlow80 * dsp->fRec2[0])) + (fSlow81 * dsp->fRec2[2]))) - (fSlow8 * ((fSlow82 * dsp->fRec1[2]) + fTemp8)));
			float fTemp9 = (fSlow4 * dsp->fRec0[1]);
			dsp->fRec0[0] = ((fSlow8 * ((fTemp8 + (fSlow84 * dsp->fRec1[0])) + (fSlow85 * dsp->fRec1[2]))) - (fSlow3 * ((fSlow86 * dsp->fRec0[2]) + fTemp9)));
			output0[i] = (FAUSTFLOAT)(fSlow3 * ((fTemp9 + (fSlow88 * dsp->fRec0[0])) + (fSlow89 * dsp->fRec0[2])));
			dsp->fRec9[2] = dsp->fRec9[1];
			dsp->fRec9[1] = dsp->fRec9[0];
			dsp->fRec8[2] = dsp->fRec8[1];
			dsp->fRec8[1] = dsp->fRec8[0];
			dsp->fRec7[2] = dsp->fRec7[1];
			dsp->fRec7[1] = dsp->fRec7[0];
			dsp->fRec6[2] = dsp->fRec6[1];
			dsp->fRec6[1] = dsp->fRec6[0];
			dsp->fRec5[2] = dsp->fRec5[1];
			dsp->fRec5[1] = dsp->fRec5[0];
			dsp->fRec4[2] = dsp->fRec4[1];
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fRec3[2] = dsp->fRec3[1];
			dsp->fRec3[1] = dsp->fRec3[0];
			dsp->fRec2[2] = dsp->fRec2[1];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec1[2] = dsp->fRec1[1];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fRec0[2] = dsp->fRec0[1];
			dsp->fRec0[1] = dsp->fRec0[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
