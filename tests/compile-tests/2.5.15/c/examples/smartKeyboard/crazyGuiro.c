/* ------------------------------------------------------------
name: "crazyGuiro"
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
	float fRec9[2];
	FAUSTFLOAT fHslider1;
	int fSamplingFreq;
	float fConst0;
	float fVec0[2];
	float fConst1;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	int iRec11[2];
	FAUSTFLOAT fButton0;
	float fVec1[2];
	float fConst2;
	float fRec12[2];
	float fConst3;
	float fConst4;
	float fRec10[3];
	int IOTA;
	float fVec2[8192];
	int iConst5;
	float fRec8[2];
	float fRec14[2];
	float fVec3[8192];
	int iConst6;
	float fRec13[2];
	float fRec16[2];
	float fVec4[8192];
	int iConst7;
	float fRec15[2];
	float fRec18[2];
	float fVec5[8192];
	int iConst8;
	float fRec17[2];
	float fRec20[2];
	float fVec6[8192];
	int iConst9;
	float fRec19[2];
	float fRec22[2];
	float fVec7[8192];
	int iConst10;
	float fRec21[2];
	float fRec24[2];
	float fVec8[8192];
	int iConst11;
	float fRec23[2];
	float fRec26[2];
	float fVec9[8192];
	int iConst12;
	float fRec25[2];
	float fVec10[2048];
	int iConst13;
	float fRec6[2];
	float fVec11[2048];
	int iConst14;
	float fRec4[2];
	float fVec12[2048];
	int iConst15;
	float fRec2[2];
	float fVec13[1024];
	int iConst16;
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
	m->declare(m->metaInterface, "basics.lib/name", "Faust Basic Element Library");
	m->declare(m->metaInterface, "basics.lib/version", "0.0");
	m->declare(m->metaInterface, "delays.lib/name", "Faust Delay Library");
	m->declare(m->metaInterface, "delays.lib/version", "0.0");
	m->declare(m->metaInterface, "envelopes.lib/author", "GRAME");
	m->declare(m->metaInterface, "envelopes.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "envelopes.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "envelopes.lib/name", "Faust Envelope Library");
	m->declare(m->metaInterface, "envelopes.lib/version", "0.0");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "interface", "SmartKeyboard{  'Number of Keyboards':'8',  'Keyboard 0 - Number of Keys':'16',  'Keyboard 1 - Number of Keys':'16',  'Keyboard 2 - Number of Keys':'16',  'Keyboard 3 - Number of Keys':'16',  'Keyboard 4 - Number of Keys':'16',  'Keyboard 5 - Number of Keys':'16',  'Keyboard 6 - Number of Keys':'16',  'Keyboard 7 - Number of Keys':'16',  'Keyboard 0 - Piano Keyboard':'0',  'Keyboard 1 - Piano Keyboard':'0',  'Keyboard 2 - Piano Keyboard':'0',  'Keyboard 3 - Piano Keyboard':'0',  'Keyboard 4 - Piano Keyboard':'0',  'Keyboard 5 - Piano Keyboard':'0',  'Keyboard 6 - Piano Keyboard':'0',  'Keyboard 7 - Piano Keyboard':'0' }");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "crazyGuiro");
	m->declare(m->metaInterface, "noises.lib/name", "Faust Noise Generator Library");
	m->declare(m->metaInterface, "noises.lib/version", "0.0");
	m->declare(m->metaInterface, "reverbs.lib/name", "Faust Reverb Library");
	m->declare(m->metaInterface, "reverbs.lib/version", "0.0");
	m->declare(m->metaInterface, "synths.lib/name", "Faust Synthesizer Library");
	m->declare(m->metaInterface, "synths.lib/version", "0.0");
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
	dsp->fHslider1 = (FAUSTFLOAT)0.0f;
	dsp->fHslider2 = (FAUSTFLOAT)0.0f;
	dsp->fHslider3 = (FAUSTFLOAT)0.0f;
	dsp->fButton0 = (FAUSTFLOAT)0.0f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			dsp->fRec9[l0] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			dsp->fVec0[l1] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			dsp->iRec11[l2] = 0;
			
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
			dsp->fRec12[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 3); l5 = (l5 + 1)) {
			dsp->fRec10[l5] = 0.0f;
			
		}
		
	}
	dsp->IOTA = 0;
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 8192); l6 = (l6 + 1)) {
			dsp->fVec2[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			dsp->fRec8[l7] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			dsp->fRec14[l8] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 8192); l9 = (l9 + 1)) {
			dsp->fVec3[l9] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			dsp->fRec13[l10] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			dsp->fRec16[l11] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 8192); l12 = (l12 + 1)) {
			dsp->fVec4[l12] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l13;
		for (l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			dsp->fRec15[l13] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l14;
		for (l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			dsp->fRec18[l14] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l15;
		for (l15 = 0; (l15 < 8192); l15 = (l15 + 1)) {
			dsp->fVec5[l15] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l16;
		for (l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			dsp->fRec17[l16] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l17;
		for (l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			dsp->fRec20[l17] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l18;
		for (l18 = 0; (l18 < 8192); l18 = (l18 + 1)) {
			dsp->fVec6[l18] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l19;
		for (l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			dsp->fRec19[l19] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l20;
		for (l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			dsp->fRec22[l20] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l21;
		for (l21 = 0; (l21 < 8192); l21 = (l21 + 1)) {
			dsp->fVec7[l21] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l22;
		for (l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			dsp->fRec21[l22] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l23;
		for (l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			dsp->fRec24[l23] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l24;
		for (l24 = 0; (l24 < 8192); l24 = (l24 + 1)) {
			dsp->fVec8[l24] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l25;
		for (l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			dsp->fRec23[l25] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l26;
		for (l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			dsp->fRec26[l26] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l27;
		for (l27 = 0; (l27 < 8192); l27 = (l27 + 1)) {
			dsp->fVec9[l27] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l28;
		for (l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			dsp->fRec25[l28] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l29;
		for (l29 = 0; (l29 < 2048); l29 = (l29 + 1)) {
			dsp->fVec10[l29] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l30;
		for (l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			dsp->fRec6[l30] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l31;
		for (l31 = 0; (l31 < 2048); l31 = (l31 + 1)) {
			dsp->fVec11[l31] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l32;
		for (l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			dsp->fRec4[l32] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l33;
		for (l33 = 0; (l33 < 2048); l33 = (l33 + 1)) {
			dsp->fVec12[l33] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l34;
		for (l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			dsp->fRec2[l34] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l35;
		for (l35 = 0; (l35 < 1024); l35 = (l35 + 1)) {
			dsp->fVec13[l35] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l36;
		for (l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			dsp->fRec0[l36] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = (1382.30078f / dsp->fConst0);
	dsp->fConst2 = (0.00200000009f * dsp->fConst0);
	dsp->fConst3 = (0.00100000005f * dsp->fConst0);
	dsp->fConst4 = (1000.0f / dsp->fConst0);
	dsp->iConst5 = (int)(0.0253061224f * dsp->fConst0);
	dsp->iConst6 = (int)(0.0269387756f * dsp->fConst0);
	dsp->iConst7 = (int)(0.0289569162f * dsp->fConst0);
	dsp->iConst8 = (int)(0.0307482984f * dsp->fConst0);
	dsp->iConst9 = (int)(0.0322448984f * dsp->fConst0);
	dsp->iConst10 = (int)(0.033809524f * dsp->fConst0);
	dsp->iConst11 = (int)(0.0353061222f * dsp->fConst0);
	dsp->iConst12 = (int)(0.0366666652f * dsp->fConst0);
	dsp->iConst13 = min(1024, max(0, ((int)(0.0126077095f * dsp->fConst0) + -1)));
	dsp->iConst14 = min(1024, max(0, ((int)(0.00999999978f * dsp->fConst0) + -1)));
	dsp->iConst15 = min(1024, max(0, ((int)(0.00773242628f * dsp->fConst0) + -1)));
	dsp->iConst16 = min(1024, max(0, ((int)(0.00510204071f * dsp->fConst0) + -1)));
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "crazyGuiro");
	ui_interface->addButton(ui_interface->uiInterface, "gate", &dsp->fButton0);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "key", &dsp->fHslider2, 0.0f, 0.0f, 2.0f, 1.0f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "keyboard", &dsp->fHslider3, 0.0f, 0.0f, 2.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "acc", "1 0 -10 0 10");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "res", &dsp->fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "acc", "0 0 -10 0 10");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "wet", &dsp->fHslider1, 0.0f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	float fSlow0 = (float)dsp->fHslider0;
	float fSlow1 = (float)dsp->fHslider1;
	float fSlow2 = tanf((dsp->fConst1 * powf(2.0f, (0.0833333358f * (((float)dsp->fHslider2 + (8.0f * (float)dsp->fHslider3)) + -19.0f)))));
	float fSlow3 = (1.0f / fSlow2);
	float fSlow4 = (((fSlow3 + 0.125f) / fSlow2) + 1.0f);
	float fSlow5 = (fSlow1 / fSlow4);
	float fSlow6 = (float)dsp->fButton0;
	float fSlow7 = (1.0f / fSlow4);
	float fSlow8 = (((fSlow3 + -0.125f) / fSlow2) + 1.0f);
	float fSlow9 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fSlow2))));
	float fSlow10 = (0.0f - fSlow3);
	float fSlow11 = ((1.0f - fSlow1) / fSlow4);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->fRec9[0] = (0.5f * (dsp->fRec9[1] + dsp->fRec8[1]));
			dsp->fVec0[0] = dsp->fConst0;
			dsp->iRec11[0] = ((1103515245 * dsp->iRec11[1]) + 12345);
			dsp->fVec1[0] = fSlow6;
			dsp->fRec12[0] = ((((fSlow6 - dsp->fVec1[1]) > 0.0f) > 0)?0.0f:min(dsp->fConst2, ((dsp->fRec12[1] + (0.00200000009f * (dsp->fConst0 - dsp->fVec0[1]))) + 1.0f)));
			int iTemp0 = (dsp->fRec12[0] < dsp->fConst3);
			dsp->fRec10[0] = ((4.65661287e-10f * ((float)dsp->iRec11[0] * (iTemp0?((dsp->fRec12[0] < 0.0f)?0.0f:(iTemp0?(dsp->fConst4 * dsp->fRec12[0]):1.0f)):((dsp->fRec12[0] < dsp->fConst2)?((dsp->fConst4 * (0.0f - (dsp->fRec12[0] - dsp->fConst3))) + 1.0f):0.0f)))) - (fSlow7 * ((fSlow8 * dsp->fRec10[2]) + (fSlow9 * dsp->fRec10[1]))));
			float fTemp1 = ((fSlow3 * dsp->fRec10[0]) + (fSlow10 * dsp->fRec10[2]));
			float fTemp2 = (fSlow5 * fTemp1);
			dsp->fVec2[(dsp->IOTA & 8191)] = ((fSlow0 * dsp->fRec9[0]) + fTemp2);
			dsp->fRec8[0] = dsp->fVec2[((dsp->IOTA - dsp->iConst5) & 8191)];
			dsp->fRec14[0] = (0.5f * (dsp->fRec14[1] + dsp->fRec13[1]));
			dsp->fVec3[(dsp->IOTA & 8191)] = (fTemp2 + (fSlow0 * dsp->fRec14[0]));
			dsp->fRec13[0] = dsp->fVec3[((dsp->IOTA - dsp->iConst6) & 8191)];
			dsp->fRec16[0] = (0.5f * (dsp->fRec16[1] + dsp->fRec15[1]));
			dsp->fVec4[(dsp->IOTA & 8191)] = (fTemp2 + (fSlow0 * dsp->fRec16[0]));
			dsp->fRec15[0] = dsp->fVec4[((dsp->IOTA - dsp->iConst7) & 8191)];
			dsp->fRec18[0] = (0.5f * (dsp->fRec18[1] + dsp->fRec17[1]));
			dsp->fVec5[(dsp->IOTA & 8191)] = (fTemp2 + (fSlow0 * dsp->fRec18[0]));
			dsp->fRec17[0] = dsp->fVec5[((dsp->IOTA - dsp->iConst8) & 8191)];
			dsp->fRec20[0] = (0.5f * (dsp->fRec20[1] + dsp->fRec19[1]));
			dsp->fVec6[(dsp->IOTA & 8191)] = (fTemp2 + (fSlow0 * dsp->fRec20[0]));
			dsp->fRec19[0] = dsp->fVec6[((dsp->IOTA - dsp->iConst9) & 8191)];
			dsp->fRec22[0] = (0.5f * (dsp->fRec22[1] + dsp->fRec21[1]));
			dsp->fVec7[(dsp->IOTA & 8191)] = (fTemp2 + (fSlow0 * dsp->fRec22[0]));
			dsp->fRec21[0] = dsp->fVec7[((dsp->IOTA - dsp->iConst10) & 8191)];
			dsp->fRec24[0] = (0.5f * (dsp->fRec24[1] + dsp->fRec23[1]));
			dsp->fVec8[(dsp->IOTA & 8191)] = (fTemp2 + (fSlow0 * dsp->fRec24[0]));
			dsp->fRec23[0] = dsp->fVec8[((dsp->IOTA - dsp->iConst11) & 8191)];
			dsp->fRec26[0] = (0.5f * (dsp->fRec26[1] + dsp->fRec25[1]));
			dsp->fVec9[(dsp->IOTA & 8191)] = (fTemp2 + (fSlow0 * dsp->fRec26[0]));
			dsp->fRec25[0] = dsp->fVec9[((dsp->IOTA - dsp->iConst12) & 8191)];
			float fTemp3 = ((((((((dsp->fRec8[0] + dsp->fRec13[0]) + dsp->fRec15[0]) + dsp->fRec17[0]) + dsp->fRec19[0]) + dsp->fRec21[0]) + dsp->fRec23[0]) + dsp->fRec25[0]) + (0.5f * dsp->fRec6[1]));
			dsp->fVec10[(dsp->IOTA & 2047)] = fTemp3;
			dsp->fRec6[0] = dsp->fVec10[((dsp->IOTA - dsp->iConst13) & 2047)];
			float fRec7 = (0.0f - (0.5f * fTemp3));
			float fTemp4 = (dsp->fRec6[1] + (fRec7 + (0.5f * dsp->fRec4[1])));
			dsp->fVec11[(dsp->IOTA & 2047)] = fTemp4;
			dsp->fRec4[0] = dsp->fVec11[((dsp->IOTA - dsp->iConst14) & 2047)];
			float fRec5 = (0.0f - (0.5f * fTemp4));
			float fTemp5 = (dsp->fRec4[1] + (fRec5 + (0.5f * dsp->fRec2[1])));
			dsp->fVec12[(dsp->IOTA & 2047)] = fTemp5;
			dsp->fRec2[0] = dsp->fVec12[((dsp->IOTA - dsp->iConst15) & 2047)];
			float fRec3 = (0.0f - (0.5f * fTemp5));
			float fTemp6 = (dsp->fRec2[1] + (fRec3 + (0.5f * dsp->fRec0[1])));
			dsp->fVec13[(dsp->IOTA & 1023)] = fTemp6;
			dsp->fRec0[0] = dsp->fVec13[((dsp->IOTA - dsp->iConst16) & 1023)];
			float fRec1 = (0.0f - (0.5f * fTemp6));
			float fTemp7 = (dsp->fRec0[1] + (fRec1 + (fSlow11 * fTemp1)));
			output0[i] = (FAUSTFLOAT)fTemp7;
			output1[i] = (FAUSTFLOAT)fTemp7;
			dsp->fRec9[1] = dsp->fRec9[0];
			dsp->fVec0[1] = dsp->fVec0[0];
			dsp->iRec11[1] = dsp->iRec11[0];
			dsp->fVec1[1] = dsp->fVec1[0];
			dsp->fRec12[1] = dsp->fRec12[0];
			dsp->fRec10[2] = dsp->fRec10[1];
			dsp->fRec10[1] = dsp->fRec10[0];
			dsp->IOTA = (dsp->IOTA + 1);
			dsp->fRec8[1] = dsp->fRec8[0];
			dsp->fRec14[1] = dsp->fRec14[0];
			dsp->fRec13[1] = dsp->fRec13[0];
			dsp->fRec16[1] = dsp->fRec16[0];
			dsp->fRec15[1] = dsp->fRec15[0];
			dsp->fRec18[1] = dsp->fRec18[0];
			dsp->fRec17[1] = dsp->fRec17[0];
			dsp->fRec20[1] = dsp->fRec20[0];
			dsp->fRec19[1] = dsp->fRec19[0];
			dsp->fRec22[1] = dsp->fRec22[0];
			dsp->fRec21[1] = dsp->fRec21[0];
			dsp->fRec24[1] = dsp->fRec24[0];
			dsp->fRec23[1] = dsp->fRec23[0];
			dsp->fRec26[1] = dsp->fRec26[0];
			dsp->fRec25[1] = dsp->fRec25[0];
			dsp->fRec6[1] = dsp->fRec6[0];
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec0[1] = dsp->fRec0[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
