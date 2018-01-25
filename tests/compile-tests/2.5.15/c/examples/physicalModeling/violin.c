/* ------------------------------------------------------------
copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
license: "MIT"
name: "Violin"
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
	
	FAUSTFLOAT fHslider0;
	int iRec10[2];
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	FAUSTFLOAT fHslider1;
	float fRec26[2];
	FAUSTFLOAT fHslider2;
	float fRec27[2];
	float fRec22[2];
	FAUSTFLOAT fHslider3;
	float fRec28[2];
	float fRec29[4];
	int IOTA;
	float fRec30[2048];
	float fVec0[2];
	FAUSTFLOAT fHslider4;
	float fRec32[2];
	float fVec1[2048];
	float fRec18[2048];
	float fRec20[2];
	float fRec16[4];
	float fConst6;
	float fConst7;
	float fRec14[3];
	float fConst8;
	int iRec6[2];
	float fRec2[2048];
	float fRec0[2];
	
} mydsp;

mydsp* newmydsp() { 
	mydsp* dsp = (mydsp*)malloc(sizeof(mydsp));
	return dsp;
}

void deletemydsp(mydsp* dsp) { 
	free(dsp);
}

void metadatamydsp(MetaGlue* m) { 
	m->declare(m->metaInterface, "copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
	m->declare(m->metaInterface, "delays.lib/name", "Faust Delay Library");
	m->declare(m->metaInterface, "delays.lib/version", "0.0");
	m->declare(m->metaInterface, "description", "Simple violin physical model controlled with continuous parameters.");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "license", "MIT");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "Violin");
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
	dsp->fHslider0 = (FAUSTFLOAT)0.5f;
	dsp->fHslider1 = (FAUSTFLOAT)0.69999999999999996f;
	dsp->fHslider2 = (FAUSTFLOAT)0.75f;
	dsp->fHslider3 = (FAUSTFLOAT)0.0f;
	dsp->fHslider4 = (FAUSTFLOAT)0.5f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			dsp->iRec10[l0] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			dsp->fRec26[l1] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			dsp->fRec27[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			dsp->fRec22[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			dsp->fRec28[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 4); l5 = (l5 + 1)) {
			dsp->fRec29[l5] = 0.0f;
			
		}
		
	}
	dsp->IOTA = 0;
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 2048); l6 = (l6 + 1)) {
			dsp->fRec30[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			dsp->fVec0[l7] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			dsp->fRec32[l8] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 2048); l9 = (l9 + 1)) {
			dsp->fVec1[l9] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 2048); l10 = (l10 + 1)) {
			dsp->fRec18[l10] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			dsp->fRec20[l11] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 4); l12 = (l12 + 1)) {
			dsp->fRec16[l12] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l13;
		for (l13 = 0; (l13 < 3); l13 = (l13 + 1)) {
			dsp->fRec14[l13] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l14;
		for (l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			dsp->iRec6[l14] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l15;
		for (l15 = 0; (l15 < 2048); l15 = (l15 + 1)) {
			dsp->fRec2[l15] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l16;
		for (l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			dsp->fRec0[l16] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = tanf((1570.79639f / dsp->fConst0));
	dsp->fConst2 = (1.0f / dsp->fConst1);
	dsp->fConst3 = (1.0f / (((dsp->fConst2 + 0.5f) / dsp->fConst1) + 1.0f));
	dsp->fConst4 = (0.00882352982f * dsp->fConst0);
	dsp->fConst5 = (0.00147058826f * dsp->fConst0);
	dsp->fConst6 = (((dsp->fConst2 + -0.5f) / dsp->fConst1) + 1.0f);
	dsp->fConst7 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(dsp->fConst1))));
	dsp->fConst8 = (0.0f - dsp->fConst2);
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "violin");
	ui_interface->declare(ui_interface->uiInterface, 0, "0", "");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "string");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "0", "");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "length", &dsp->fHslider2, 0.75f, 0.0f, 2.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "1", "");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "bow");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "0", "");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "velocity", &dsp->fHslider3, 0.0f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "1", "");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "pressure", &dsp->fHslider4, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "2", "");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "position", &dsp->fHslider1, 0.699999988f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "outGain", &dsp->fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	float fSlow0 = (float)dsp->fHslider0;
	float fSlow1 = (0.00100000005f * (float)dsp->fHslider1);
	float fSlow2 = (0.00100000005f * (float)dsp->fHslider2);
	float fSlow3 = (0.00100000005f * (float)dsp->fHslider3);
	float fSlow4 = (0.00100000005f * (float)dsp->fHslider4);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->iRec10[0] = 0;
			int iRec11 = dsp->iRec10[1];
			float fRec15 = ((float)dsp->iRec6[1] - (0.989264667f * ((0.600000024f * dsp->fRec16[2]) + (0.200000003f * (dsp->fRec16[1] + dsp->fRec16[3])))));
			dsp->fRec26[0] = (fSlow1 + (0.999000013f * dsp->fRec26[1]));
			dsp->fRec27[0] = (fSlow2 + (0.999000013f * dsp->fRec27[1]));
			float fTemp0 = (dsp->fRec27[0] + -0.0799999982f);
			float fTemp1 = (dsp->fConst5 * ((1.0f - dsp->fRec26[0]) * fTemp0));
			float fTemp2 = (fTemp1 + -1.49999499f);
			int iTemp3 = (int)fTemp2;
			int iTemp4 = (int)min(dsp->fConst4, (float)max(0, iTemp3));
			float fTemp5 = floorf(fTemp2);
			float fTemp6 = (fTemp1 + (-1.0f - fTemp5));
			float fTemp7 = (0.0f - fTemp6);
			float fTemp8 = (fTemp1 + (-2.0f - fTemp5));
			float fTemp9 = (0.0f - (0.5f * fTemp8));
			float fTemp10 = (fTemp1 + (-3.0f - fTemp5));
			float fTemp11 = (0.0f - (0.333333343f * fTemp10));
			float fTemp12 = (fTemp1 + (-4.0f - fTemp5));
			float fTemp13 = (0.0f - (0.25f * fTemp12));
			float fTemp14 = (fTemp1 - fTemp5);
			int iTemp15 = (int)min(dsp->fConst4, (float)max(0, (iTemp3 + 2)));
			float fTemp16 = (0.0f - fTemp10);
			float fTemp17 = (0.0f - (0.5f * fTemp12));
			int iTemp18 = (int)min(dsp->fConst4, (float)max(0, (iTemp3 + 1)));
			float fTemp19 = (0.0f - fTemp8);
			float fTemp20 = (0.0f - (0.5f * fTemp10));
			float fTemp21 = (0.0f - (0.333333343f * fTemp12));
			float fTemp22 = (fTemp6 * fTemp8);
			int iTemp23 = (int)min(dsp->fConst4, (float)max(0, (iTemp3 + 3)));
			float fTemp24 = (0.0f - fTemp12);
			float fTemp25 = (fTemp22 * fTemp10);
			int iTemp26 = (int)min(dsp->fConst4, (float)max(0, (iTemp3 + 4)));
			dsp->fRec22[0] = (((((dsp->fRec2[((dsp->IOTA - (iTemp4 + 1)) & 2047)] * fTemp7) * fTemp9) * fTemp11) * fTemp13) + (fTemp14 * ((((0.5f * (((fTemp6 * dsp->fRec2[((dsp->IOTA - (iTemp15 + 1)) & 2047)]) * fTemp16) * fTemp17)) + (((dsp->fRec2[((dsp->IOTA - (iTemp18 + 1)) & 2047)] * fTemp19) * fTemp20) * fTemp21)) + (0.166666672f * ((fTemp22 * dsp->fRec2[((dsp->IOTA - (iTemp23 + 1)) & 2047)]) * fTemp24))) + (0.0416666679f * (fTemp25 * dsp->fRec2[((dsp->IOTA - (iTemp26 + 1)) & 2047)])))));
			dsp->fRec28[0] = (fSlow3 + (0.999000013f * dsp->fRec28[1]));
			dsp->fRec29[0] = dsp->fRec0[1];
			dsp->fRec30[(dsp->IOTA & 2047)] = (0.0f - (0.99880147f * ((0.800000012f * dsp->fRec29[2]) + (0.100000001f * (dsp->fRec29[1] + dsp->fRec29[3])))));
			int iRec31 = 0;
			float fTemp27 = (dsp->fConst5 * (dsp->fRec26[0] * fTemp0));
			float fTemp28 = (fTemp27 + -1.49999499f);
			int iTemp29 = (int)fTemp28;
			int iTemp30 = (int)min(dsp->fConst4, (float)max(0, iTemp29));
			float fTemp31 = floorf(fTemp28);
			float fTemp32 = (fTemp27 + (-1.0f - fTemp31));
			float fTemp33 = (0.0f - fTemp32);
			float fTemp34 = (fTemp27 + (-2.0f - fTemp31));
			float fTemp35 = (0.0f - (0.5f * fTemp34));
			float fTemp36 = (fTemp27 + (-3.0f - fTemp31));
			float fTemp37 = (0.0f - (0.333333343f * fTemp36));
			float fTemp38 = (fTemp27 + (-4.0f - fTemp31));
			float fTemp39 = (0.0f - (0.25f * fTemp38));
			float fTemp40 = (fTemp27 - fTemp31);
			int iTemp41 = (int)min(dsp->fConst4, (float)max(0, (iTemp29 + 2)));
			float fTemp42 = (0.0f - fTemp36);
			float fTemp43 = (0.0f - (0.5f * fTemp38));
			int iTemp44 = (int)min(dsp->fConst4, (float)max(0, (iTemp29 + 1)));
			float fTemp45 = (0.0f - fTemp34);
			float fTemp46 = (0.0f - (0.5f * fTemp36));
			float fTemp47 = (0.0f - (0.333333343f * fTemp38));
			float fTemp48 = (fTemp32 * fTemp34);
			int iTemp49 = (int)min(dsp->fConst4, (float)max(0, (iTemp29 + 3)));
			float fTemp50 = (0.0f - fTemp38);
			float fTemp51 = (fTemp48 * fTemp36);
			int iTemp52 = (int)min(dsp->fConst4, (float)max(0, (iTemp29 + 4)));
			dsp->fVec0[0] = (((((dsp->fRec30[((dsp->IOTA - (iTemp30 + 2)) & 2047)] * fTemp33) * fTemp35) * fTemp37) * fTemp39) + (fTemp40 * ((((0.5f * (((fTemp32 * dsp->fRec30[((dsp->IOTA - (iTemp41 + 2)) & 2047)]) * fTemp42) * fTemp43)) + (((dsp->fRec30[((dsp->IOTA - (iTemp44 + 2)) & 2047)] * fTemp45) * fTemp46) * fTemp47)) + (0.166666672f * ((fTemp48 * dsp->fRec30[((dsp->IOTA - (iTemp49 + 2)) & 2047)]) * fTemp50))) + (0.0416666679f * (fTemp51 * dsp->fRec30[((dsp->IOTA - (iTemp52 + 2)) & 2047)])))));
			float fTemp53 = (dsp->fRec28[0] - (dsp->fRec22[1] + dsp->fVec0[1]));
			dsp->fRec32[0] = (fSlow4 + (0.999000013f * dsp->fRec32[1]));
			float fTemp54 = (fTemp53 * min(1.0f, (1.0f / mydsp_faustpower4_f((fabsf(((5.0f - (4.0f * dsp->fRec32[0])) * fTemp53)) + 0.75f)))));
			float fRec23 = (dsp->fRec22[1] + fTemp54);
			float fTemp55 = (dsp->fVec0[1] + fTemp54);
			dsp->fVec1[(dsp->IOTA & 2047)] = fTemp55;
			float fRec24 = (((((fTemp7 * fTemp9) * fTemp11) * fTemp13) * dsp->fVec1[((dsp->IOTA - iTemp4) & 2047)]) + (fTemp14 * ((0.0416666679f * (fTemp25 * dsp->fVec1[((dsp->IOTA - iTemp26) & 2047)])) + (((((fTemp19 * fTemp20) * fTemp21) * dsp->fVec1[((dsp->IOTA - iTemp18) & 2047)]) + (0.5f * (((fTemp6 * fTemp16) * fTemp17) * dsp->fVec1[((dsp->IOTA - iTemp15) & 2047)]))) + (0.166666672f * ((fTemp22 * fTemp24) * dsp->fVec1[((dsp->IOTA - iTemp23) & 2047)]))))));
			int iRec25 = iRec31;
			dsp->fRec18[(dsp->IOTA & 2047)] = fRec23;
			float fRec19 = (((((fTemp33 * fTemp35) * fTemp37) * fTemp39) * dsp->fRec18[((dsp->IOTA - (iTemp30 + 1)) & 2047)]) + (fTemp40 * (((0.166666672f * ((fTemp48 * fTemp50) * dsp->fRec18[((dsp->IOTA - (iTemp49 + 1)) & 2047)])) + ((((fTemp45 * fTemp46) * fTemp47) * dsp->fRec18[((dsp->IOTA - (iTemp44 + 1)) & 2047)]) + (0.5f * (((fTemp32 * fTemp42) * fTemp43) * dsp->fRec18[((dsp->IOTA - (iTemp41 + 1)) & 2047)])))) + (0.0416666679f * (fTemp51 * dsp->fRec18[((dsp->IOTA - (iTemp52 + 1)) & 2047)])))));
			dsp->fRec20[0] = fRec24;
			int iRec21 = iRec25;
			dsp->fRec16[0] = dsp->fRec20[1];
			int iRec17 = iRec21;
			dsp->fRec14[0] = (dsp->fRec16[1] - (dsp->fConst3 * ((dsp->fConst6 * dsp->fRec14[2]) + (dsp->fConst7 * dsp->fRec14[1]))));
			float fTemp56 = (dsp->fConst3 * ((dsp->fConst2 * dsp->fRec14[0]) + (dsp->fConst8 * dsp->fRec14[2])));
			float fRec12 = fTemp56;
			float fRec13 = ((float)iRec17 + fTemp56);
			dsp->iRec6[0] = iRec11;
			float fRec7 = fRec15;
			float fRec8 = fRec12;
			float fRec9 = fRec13;
			dsp->fRec2[(dsp->IOTA & 2047)] = fRec7;
			float fRec3 = fRec19;
			float fRec4 = fRec8;
			float fRec5 = fRec9;
			dsp->fRec0[0] = fRec3;
			float fRec1 = fRec5;
			float fTemp57 = (fSlow0 * fRec1);
			output0[i] = (FAUSTFLOAT)fTemp57;
			output1[i] = (FAUSTFLOAT)fTemp57;
			dsp->iRec10[1] = dsp->iRec10[0];
			dsp->fRec26[1] = dsp->fRec26[0];
			dsp->fRec27[1] = dsp->fRec27[0];
			dsp->fRec22[1] = dsp->fRec22[0];
			dsp->fRec28[1] = dsp->fRec28[0];
			/* C99 loop */
			{
				int j0;
				for (j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
					dsp->fRec29[j0] = dsp->fRec29[(j0 - 1)];
					
				}
				
			}
			dsp->IOTA = (dsp->IOTA + 1);
			dsp->fVec0[1] = dsp->fVec0[0];
			dsp->fRec32[1] = dsp->fRec32[0];
			dsp->fRec20[1] = dsp->fRec20[0];
			/* C99 loop */
			{
				int j1;
				for (j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
					dsp->fRec16[j1] = dsp->fRec16[(j1 - 1)];
					
				}
				
			}
			dsp->fRec14[2] = dsp->fRec14[1];
			dsp->fRec14[1] = dsp->fRec14[0];
			dsp->iRec6[1] = dsp->iRec6[0];
			dsp->fRec0[1] = dsp->fRec0[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
