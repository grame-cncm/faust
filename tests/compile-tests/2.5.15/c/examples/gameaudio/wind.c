/* ------------------------------------------------------------
name: "wind"
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
	float fRec0[2];
	int iRec1[2];
	float fRec3[2];
	int fSamplingFreq;
	float fConst0;
	float fRec6[2];
	float fRec4[2];
	float fRec9[2];
	float fRec7[2];
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
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "wind");
	m->declare(m->metaInterface, "noises.lib/name", "Faust Noise Generator Library");
	m->declare(m->metaInterface, "noises.lib/version", "0.0");
	m->declare(m->metaInterface, "signals.lib/name", "Faust Signal Routing Library");
	m->declare(m->metaInterface, "signals.lib/version", "0.0");
	m->declare(m->metaInterface, "vaeffects.lib/name", "Faust Virtual Analog Filter Effect Library");
	m->declare(m->metaInterface, "vaeffects.lib/version", "0.0");
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
	dsp->fHslider0 = (FAUSTFLOAT)0.66000000000000003f;
	
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
			dsp->iRec1[l1] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
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
		for (l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			dsp->fRec4[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			dsp->fRec9[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			dsp->fRec7[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			dsp->fRec12[l7] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			dsp->fRec10[l8] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			dsp->fRec15[l9] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			dsp->fRec13[l10] = 0.0f;
			
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "wind");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "force", &dsp->fHslider0, 0.660000026f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	float fSlow0 = (0.00300000003f * (float)dsp->fHslider0);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->fRec0[0] = (fSlow0 + (0.996999979f * dsp->fRec0[1]));
			int iTemp0 = (1103515245 * (dsp->iRec1[1] + 12345));
			dsp->iRec1[0] = (1103515245 * (iTemp0 + 12345));
			int iRec2 = iTemp0;
			float fTemp1 = (4.65661287e-10f * (float)dsp->iRec1[0]);
			dsp->fRec3[0] = (fSlow0 + (0.996999979f * dsp->fRec3[1]));
			float fTemp2 = mydsp_faustpower2_f((1.41419947f * dsp->fRec3[0]));
			float fTemp3 = (1.99997997f * dsp->fRec3[0]);
			float fTemp4 = (fTemp2 + fTemp3);
			float fTemp5 = (fTemp3 + 2.0f);
			float fTemp6 = tanf((dsp->fConst0 * max((440.0f * powf(2.0f, (0.0833333358f * ((87.0f * dsp->fRec3[0]) + -48.0f)))), 20.0f)));
			float fTemp7 = (1.0f / fTemp6);
			float fTemp8 = ((fTemp4 + ((fTemp5 + fTemp7) / fTemp6)) + 1.0f);
			float fTemp9 = ((fTemp4 + (1.0f - ((fTemp5 - fTemp7) / fTemp6))) / fTemp8);
			float fTemp10 = max(-0.999899983f, min(0.999899983f, fTemp9));
			float fTemp11 = (0.0f - fTemp10);
			float fTemp12 = (1.0f - mydsp_faustpower2_f(fTemp10));
			float fTemp13 = sqrtf(max(0.0f, fTemp12));
			float fTemp14 = ((dsp->fRec4[1] * fTemp11) + (fTemp1 * fTemp13));
			float fTemp15 = (1.0f / mydsp_faustpower2_f(fTemp6));
			float fTemp16 = (fTemp4 + (1.0f - fTemp15));
			float fTemp17 = max(-0.999899983f, min(0.999899983f, (2.0f * (fTemp16 / (fTemp8 * (fTemp9 + 1.0f))))));
			float fTemp18 = (0.0f - fTemp17);
			float fTemp19 = (1.0f - mydsp_faustpower2_f(fTemp17));
			float fTemp20 = sqrtf(max(0.0f, fTemp19));
			dsp->fRec6[0] = ((dsp->fRec6[1] * fTemp18) + (fTemp14 * fTemp20));
			dsp->fRec4[0] = ((fTemp14 * fTemp17) + (dsp->fRec6[1] * fTemp20));
			float fRec5 = dsp->fRec6[0];
			float fTemp21 = (1.0f - (fTemp16 / fTemp8));
			float fTemp22 = sqrtf(fTemp12);
			float fTemp23 = ((1.0f - fTemp9) - (2.0f * (fTemp17 * fTemp21)));
			float fTemp24 = (fTemp22 * sqrtf(fTemp19));
			float fTemp25 = ((((fTemp1 * fTemp10) + (dsp->fRec4[1] * fTemp13)) + (2.0f * ((dsp->fRec4[0] * fTemp21) / fTemp22))) + ((fRec5 * fTemp23) / fTemp24));
			float fTemp26 = (2.0f - fTemp3);
			float fTemp27 = (1.0f - fTemp3);
			float fTemp28 = ((fTemp2 + ((fTemp7 + fTemp26) / fTemp6)) + fTemp27);
			float fTemp29 = (((fTemp2 + ((fTemp7 - fTemp26) / fTemp6)) + fTemp27) / fTemp28);
			float fTemp30 = max(-0.999899983f, min(0.999899983f, fTemp29));
			float fTemp31 = (0.0f - fTemp30);
			float fTemp32 = (1.0f - mydsp_faustpower2_f(fTemp30));
			float fTemp33 = sqrtf(max(0.0f, fTemp32));
			float fTemp34 = ((dsp->fRec7[1] * fTemp31) + ((fTemp25 * fTemp33) / fTemp8));
			float fTemp35 = (fTemp2 + (1.0f - (fTemp3 + fTemp15)));
			float fTemp36 = max(-0.999899983f, min(0.999899983f, (2.0f * (fTemp35 / (fTemp28 * (fTemp29 + 1.0f))))));
			float fTemp37 = (0.0f - fTemp36);
			float fTemp38 = (1.0f - mydsp_faustpower2_f(fTemp36));
			float fTemp39 = sqrtf(max(0.0f, fTemp38));
			dsp->fRec9[0] = ((dsp->fRec9[1] * fTemp37) + (fTemp34 * fTemp39));
			dsp->fRec7[0] = ((fTemp34 * fTemp36) + (dsp->fRec9[1] * fTemp39));
			float fRec8 = dsp->fRec9[0];
			float fTemp40 = (1.0f - (fTemp35 / fTemp28));
			float fTemp41 = sqrtf(fTemp32);
			float fTemp42 = ((1.0f - fTemp29) - (2.0f * (fTemp36 * fTemp40)));
			float fTemp43 = (fTemp41 * sqrtf(fTemp38));
			output0[i] = (FAUSTFLOAT)((dsp->fRec0[0] * (((((fTemp25 * fTemp30) / fTemp8) + (dsp->fRec7[1] * fTemp33)) + (2.0f * ((dsp->fRec7[0] * fTemp40) / fTemp41))) + ((fRec8 * fTemp42) / fTemp43))) / fTemp28);
			float fTemp44 = (4.65661287e-10f * (float)iRec2);
			float fTemp45 = ((fTemp11 * dsp->fRec10[1]) + (fTemp13 * fTemp44));
			dsp->fRec12[0] = ((fTemp18 * dsp->fRec12[1]) + (fTemp20 * fTemp45));
			dsp->fRec10[0] = ((fTemp17 * fTemp45) + (fTemp20 * dsp->fRec12[1]));
			float fRec11 = dsp->fRec12[0];
			float fTemp46 = ((((fTemp10 * fTemp44) + (fTemp13 * dsp->fRec10[1])) + (2.0f * ((dsp->fRec10[0] * fTemp21) / fTemp22))) + ((fRec11 * fTemp23) / fTemp24));
			float fTemp47 = ((fTemp31 * dsp->fRec13[1]) + ((fTemp33 * fTemp46) / fTemp8));
			dsp->fRec15[0] = ((fTemp37 * dsp->fRec15[1]) + (fTemp39 * fTemp47));
			dsp->fRec13[0] = ((fTemp36 * fTemp47) + (fTemp39 * dsp->fRec15[1]));
			float fRec14 = dsp->fRec15[0];
			output1[i] = (FAUSTFLOAT)((dsp->fRec0[0] * (((((fTemp30 * fTemp46) / fTemp8) + (fTemp33 * dsp->fRec13[1])) + (2.0f * ((dsp->fRec13[0] * fTemp40) / fTemp41))) + ((fRec14 * fTemp42) / fTemp43))) / fTemp28);
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->iRec1[1] = dsp->iRec1[0];
			dsp->fRec3[1] = dsp->fRec3[0];
			dsp->fRec6[1] = dsp->fRec6[0];
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fRec9[1] = dsp->fRec9[0];
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
