/* ------------------------------------------------------------
name: "freeverb"
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
	
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	float fRec9[2];
	int IOTA;
	float fVec0[2048];
	float fRec8[2];
	float fRec11[2];
	float fVec1[2048];
	float fRec10[2];
	float fRec13[2];
	float fVec2[2048];
	float fRec12[2];
	float fRec15[2];
	float fVec3[2048];
	float fRec14[2];
	float fRec17[2];
	float fVec4[2048];
	float fRec16[2];
	float fRec19[2];
	float fVec5[2048];
	float fRec18[2];
	float fRec21[2];
	float fVec6[2048];
	float fRec20[2];
	float fRec23[2];
	float fVec7[2048];
	float fRec22[2];
	float fVec8[1024];
	float fRec6[2];
	float fVec9[512];
	float fRec4[2];
	float fVec10[512];
	float fRec2[2];
	float fVec11[256];
	float fRec0[2];
	float fRec33[2];
	float fVec12[2048];
	float fRec32[2];
	float fRec35[2];
	float fVec13[2048];
	float fRec34[2];
	float fRec37[2];
	float fVec14[2048];
	float fRec36[2];
	float fRec39[2];
	float fVec15[2048];
	float fRec38[2];
	float fRec41[2];
	float fVec16[2048];
	float fRec40[2];
	float fRec43[2];
	float fVec17[2048];
	float fRec42[2];
	float fRec45[2];
	float fVec18[2048];
	float fRec44[2];
	float fRec47[2];
	float fVec19[2048];
	float fRec46[2];
	float fVec20[1024];
	float fRec30[2];
	float fVec21[512];
	float fRec28[2];
	float fVec22[512];
	float fRec26[2];
	float fVec23[256];
	float fRec24[2];
	int fSamplingFreq;
	
} mydsp;

mydsp* newmydsp() { 
	mydsp* dsp = (mydsp*)malloc(sizeof(mydsp));
	return dsp;
}

void deletemydsp(mydsp* dsp) { 
	free(dsp);
}

void metadatamydsp(MetaGlue* m) { 
	m->declare(m->metaInterface, "name", "freeverb");
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
	dsp->fHslider0 = (FAUSTFLOAT)0.33329999999999999f;
	dsp->fHslider1 = (FAUSTFLOAT)0.5f;
	dsp->fHslider2 = (FAUSTFLOAT)0.5f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			dsp->fRec9[l0] = 0.0f;
			
		}
		
	}
	dsp->IOTA = 0;
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 2048); l1 = (l1 + 1)) {
			dsp->fVec0[l1] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			dsp->fRec8[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			dsp->fRec11[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 2048); l4 = (l4 + 1)) {
			dsp->fVec1[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			dsp->fRec10[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			dsp->fRec13[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2048); l7 = (l7 + 1)) {
			dsp->fVec2[l7] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			dsp->fRec12[l8] = 0.0f;
			
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
		for (l10 = 0; (l10 < 2048); l10 = (l10 + 1)) {
			dsp->fVec3[l10] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			dsp->fRec14[l11] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			dsp->fRec17[l12] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l13;
		for (l13 = 0; (l13 < 2048); l13 = (l13 + 1)) {
			dsp->fVec4[l13] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l14;
		for (l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			dsp->fRec16[l14] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l15;
		for (l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			dsp->fRec19[l15] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l16;
		for (l16 = 0; (l16 < 2048); l16 = (l16 + 1)) {
			dsp->fVec5[l16] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l17;
		for (l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			dsp->fRec18[l17] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l18;
		for (l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			dsp->fRec21[l18] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l19;
		for (l19 = 0; (l19 < 2048); l19 = (l19 + 1)) {
			dsp->fVec6[l19] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l20;
		for (l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			dsp->fRec20[l20] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l21;
		for (l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			dsp->fRec23[l21] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l22;
		for (l22 = 0; (l22 < 2048); l22 = (l22 + 1)) {
			dsp->fVec7[l22] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l23;
		for (l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			dsp->fRec22[l23] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l24;
		for (l24 = 0; (l24 < 1024); l24 = (l24 + 1)) {
			dsp->fVec8[l24] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l25;
		for (l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			dsp->fRec6[l25] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l26;
		for (l26 = 0; (l26 < 512); l26 = (l26 + 1)) {
			dsp->fVec9[l26] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l27;
		for (l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			dsp->fRec4[l27] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l28;
		for (l28 = 0; (l28 < 512); l28 = (l28 + 1)) {
			dsp->fVec10[l28] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l29;
		for (l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			dsp->fRec2[l29] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l30;
		for (l30 = 0; (l30 < 256); l30 = (l30 + 1)) {
			dsp->fVec11[l30] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l31;
		for (l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			dsp->fRec0[l31] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l32;
		for (l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			dsp->fRec33[l32] = 0.0f;
			
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
			dsp->fRec32[l34] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l35;
		for (l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			dsp->fRec35[l35] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l36;
		for (l36 = 0; (l36 < 2048); l36 = (l36 + 1)) {
			dsp->fVec13[l36] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l37;
		for (l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			dsp->fRec34[l37] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l38;
		for (l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			dsp->fRec37[l38] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l39;
		for (l39 = 0; (l39 < 2048); l39 = (l39 + 1)) {
			dsp->fVec14[l39] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l40;
		for (l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			dsp->fRec36[l40] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l41;
		for (l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			dsp->fRec39[l41] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l42;
		for (l42 = 0; (l42 < 2048); l42 = (l42 + 1)) {
			dsp->fVec15[l42] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l43;
		for (l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			dsp->fRec38[l43] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l44;
		for (l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			dsp->fRec41[l44] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l45;
		for (l45 = 0; (l45 < 2048); l45 = (l45 + 1)) {
			dsp->fVec16[l45] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l46;
		for (l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			dsp->fRec40[l46] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l47;
		for (l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			dsp->fRec43[l47] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l48;
		for (l48 = 0; (l48 < 2048); l48 = (l48 + 1)) {
			dsp->fVec17[l48] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l49;
		for (l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			dsp->fRec42[l49] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l50;
		for (l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			dsp->fRec45[l50] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l51;
		for (l51 = 0; (l51 < 2048); l51 = (l51 + 1)) {
			dsp->fVec18[l51] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l52;
		for (l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			dsp->fRec44[l52] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l53;
		for (l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			dsp->fRec47[l53] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l54;
		for (l54 = 0; (l54 < 2048); l54 = (l54 + 1)) {
			dsp->fVec19[l54] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l55;
		for (l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			dsp->fRec46[l55] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l56;
		for (l56 = 0; (l56 < 1024); l56 = (l56 + 1)) {
			dsp->fVec20[l56] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l57;
		for (l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			dsp->fRec30[l57] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l58;
		for (l58 = 0; (l58 < 512); l58 = (l58 + 1)) {
			dsp->fVec21[l58] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l59;
		for (l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			dsp->fRec28[l59] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l60;
		for (l60 = 0; (l60 < 512); l60 = (l60 + 1)) {
			dsp->fVec22[l60] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l61;
		for (l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			dsp->fRec26[l61] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l62;
		for (l62 = 0; (l62 < 256); l62 = (l62 + 1)) {
			dsp->fVec23[l62] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l63;
		for (l63 = 0; (l63 < 2); l63 = (l63 + 1)) {
			dsp->fRec24[l63] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "Freeverb");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Damp", &dsp->fHslider2, 0.5f, 0.0f, 1.0f, 0.0250000004f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "RoomSize", &dsp->fHslider1, 0.5f, 0.0f, 1.0f, 0.0250000004f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Wet", &dsp->fHslider0, 0.333299994f, 0.0f, 1.0f, 0.0250000004f);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* input0 = inputs[0];
	FAUSTFLOAT* input1 = inputs[1];
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	float fSlow0 = (float)dsp->fHslider0;
	float fSlow1 = ((0.280000001f * (float)dsp->fHslider1) + 0.699999988f);
	float fSlow2 = (0.400000006f * (float)dsp->fHslider2);
	float fSlow3 = (1.0f - fSlow2);
	float fSlow4 = (1.0f - fSlow0);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->fRec9[0] = ((fSlow2 * dsp->fRec9[1]) + (fSlow3 * dsp->fRec8[1]));
			float fTemp0 = (float)input0[i];
			float fTemp1 = (float)input1[i];
			float fTemp2 = (0.0149999997f * (fTemp0 + fTemp1));
			dsp->fVec0[(dsp->IOTA & 2047)] = ((fSlow1 * dsp->fRec9[0]) + fTemp2);
			dsp->fRec8[0] = dsp->fVec0[((dsp->IOTA - 1116) & 2047)];
			dsp->fRec11[0] = ((fSlow2 * dsp->fRec11[1]) + (fSlow3 * dsp->fRec10[1]));
			dsp->fVec1[(dsp->IOTA & 2047)] = (fTemp2 + (fSlow1 * dsp->fRec11[0]));
			dsp->fRec10[0] = dsp->fVec1[((dsp->IOTA - 1188) & 2047)];
			dsp->fRec13[0] = ((fSlow2 * dsp->fRec13[1]) + (fSlow3 * dsp->fRec12[1]));
			dsp->fVec2[(dsp->IOTA & 2047)] = (fTemp2 + (fSlow1 * dsp->fRec13[0]));
			dsp->fRec12[0] = dsp->fVec2[((dsp->IOTA - 1277) & 2047)];
			dsp->fRec15[0] = ((fSlow2 * dsp->fRec15[1]) + (fSlow3 * dsp->fRec14[1]));
			dsp->fVec3[(dsp->IOTA & 2047)] = (fTemp2 + (fSlow1 * dsp->fRec15[0]));
			dsp->fRec14[0] = dsp->fVec3[((dsp->IOTA - 1356) & 2047)];
			dsp->fRec17[0] = ((fSlow2 * dsp->fRec17[1]) + (fSlow3 * dsp->fRec16[1]));
			dsp->fVec4[(dsp->IOTA & 2047)] = (fTemp2 + (fSlow1 * dsp->fRec17[0]));
			dsp->fRec16[0] = dsp->fVec4[((dsp->IOTA - 1422) & 2047)];
			dsp->fRec19[0] = ((fSlow2 * dsp->fRec19[1]) + (fSlow3 * dsp->fRec18[1]));
			dsp->fVec5[(dsp->IOTA & 2047)] = (fTemp2 + (fSlow1 * dsp->fRec19[0]));
			dsp->fRec18[0] = dsp->fVec5[((dsp->IOTA - 1491) & 2047)];
			dsp->fRec21[0] = ((fSlow2 * dsp->fRec21[1]) + (fSlow3 * dsp->fRec20[1]));
			dsp->fVec6[(dsp->IOTA & 2047)] = (fTemp2 + (fSlow1 * dsp->fRec21[0]));
			dsp->fRec20[0] = dsp->fVec6[((dsp->IOTA - 1557) & 2047)];
			dsp->fRec23[0] = ((fSlow2 * dsp->fRec23[1]) + (fSlow3 * dsp->fRec22[1]));
			dsp->fVec7[(dsp->IOTA & 2047)] = (fTemp2 + (fSlow1 * dsp->fRec23[0]));
			dsp->fRec22[0] = dsp->fVec7[((dsp->IOTA - 1617) & 2047)];
			float fTemp3 = (((((((dsp->fRec8[0] + dsp->fRec10[0]) + dsp->fRec12[0]) + dsp->fRec14[0]) + dsp->fRec16[0]) + dsp->fRec18[0]) + dsp->fRec20[0]) + dsp->fRec22[0]);
			dsp->fVec8[(dsp->IOTA & 1023)] = (fTemp3 + (0.5f * dsp->fRec6[1]));
			dsp->fRec6[0] = dsp->fVec8[((dsp->IOTA - 556) & 1023)];
			float fRec7 = (dsp->fRec6[1] - fTemp3);
			dsp->fVec9[(dsp->IOTA & 511)] = (fRec7 + (0.5f * dsp->fRec4[1]));
			dsp->fRec4[0] = dsp->fVec9[((dsp->IOTA - 441) & 511)];
			float fRec5 = (dsp->fRec4[1] - fRec7);
			dsp->fVec10[(dsp->IOTA & 511)] = (fRec5 + (0.5f * dsp->fRec2[1]));
			dsp->fRec2[0] = dsp->fVec10[((dsp->IOTA - 341) & 511)];
			float fRec3 = (dsp->fRec2[1] - fRec5);
			dsp->fVec11[(dsp->IOTA & 255)] = (fRec3 + (0.5f * dsp->fRec0[1]));
			dsp->fRec0[0] = dsp->fVec11[((dsp->IOTA - 225) & 255)];
			float fRec1 = (dsp->fRec0[1] - fRec3);
			output0[i] = (FAUSTFLOAT)((fSlow0 * fRec1) + (fSlow4 * fTemp0));
			dsp->fRec33[0] = ((fSlow2 * dsp->fRec33[1]) + (fSlow3 * dsp->fRec32[1]));
			dsp->fVec12[(dsp->IOTA & 2047)] = (fTemp2 + (fSlow1 * dsp->fRec33[0]));
			dsp->fRec32[0] = dsp->fVec12[((dsp->IOTA - 1139) & 2047)];
			dsp->fRec35[0] = ((fSlow2 * dsp->fRec35[1]) + (fSlow3 * dsp->fRec34[1]));
			dsp->fVec13[(dsp->IOTA & 2047)] = (fTemp2 + (fSlow1 * dsp->fRec35[0]));
			dsp->fRec34[0] = dsp->fVec13[((dsp->IOTA - 1211) & 2047)];
			dsp->fRec37[0] = ((fSlow2 * dsp->fRec37[1]) + (fSlow3 * dsp->fRec36[1]));
			dsp->fVec14[(dsp->IOTA & 2047)] = (fTemp2 + (fSlow1 * dsp->fRec37[0]));
			dsp->fRec36[0] = dsp->fVec14[((dsp->IOTA - 1300) & 2047)];
			dsp->fRec39[0] = ((fSlow2 * dsp->fRec39[1]) + (fSlow3 * dsp->fRec38[1]));
			dsp->fVec15[(dsp->IOTA & 2047)] = (fTemp2 + (fSlow1 * dsp->fRec39[0]));
			dsp->fRec38[0] = dsp->fVec15[((dsp->IOTA - 1379) & 2047)];
			dsp->fRec41[0] = ((fSlow2 * dsp->fRec41[1]) + (fSlow3 * dsp->fRec40[1]));
			dsp->fVec16[(dsp->IOTA & 2047)] = (fTemp2 + (fSlow1 * dsp->fRec41[0]));
			dsp->fRec40[0] = dsp->fVec16[((dsp->IOTA - 1445) & 2047)];
			dsp->fRec43[0] = ((fSlow2 * dsp->fRec43[1]) + (fSlow3 * dsp->fRec42[1]));
			dsp->fVec17[(dsp->IOTA & 2047)] = (fTemp2 + (fSlow1 * dsp->fRec43[0]));
			dsp->fRec42[0] = dsp->fVec17[((dsp->IOTA - 1514) & 2047)];
			dsp->fRec45[0] = ((fSlow2 * dsp->fRec45[1]) + (fSlow3 * dsp->fRec44[1]));
			dsp->fVec18[(dsp->IOTA & 2047)] = (fTemp2 + (fSlow1 * dsp->fRec45[0]));
			dsp->fRec44[0] = dsp->fVec18[((dsp->IOTA - 1580) & 2047)];
			dsp->fRec47[0] = ((fSlow2 * dsp->fRec47[1]) + (fSlow3 * dsp->fRec46[1]));
			dsp->fVec19[(dsp->IOTA & 2047)] = (fTemp2 + (fSlow1 * dsp->fRec47[0]));
			dsp->fRec46[0] = dsp->fVec19[((dsp->IOTA - 1640) & 2047)];
			float fTemp4 = (((((((dsp->fRec32[0] + dsp->fRec34[0]) + dsp->fRec36[0]) + dsp->fRec38[0]) + dsp->fRec40[0]) + dsp->fRec42[0]) + dsp->fRec44[0]) + dsp->fRec46[0]);
			dsp->fVec20[(dsp->IOTA & 1023)] = (fTemp4 + (0.5f * dsp->fRec30[1]));
			dsp->fRec30[0] = dsp->fVec20[((dsp->IOTA - 579) & 1023)];
			float fRec31 = (dsp->fRec30[1] - fTemp4);
			dsp->fVec21[(dsp->IOTA & 511)] = (fRec31 + (0.5f * dsp->fRec28[1]));
			dsp->fRec28[0] = dsp->fVec21[((dsp->IOTA - 464) & 511)];
			float fRec29 = (dsp->fRec28[1] - fRec31);
			dsp->fVec22[(dsp->IOTA & 511)] = (fRec29 + (0.5f * dsp->fRec26[1]));
			dsp->fRec26[0] = dsp->fVec22[((dsp->IOTA - 364) & 511)];
			float fRec27 = (dsp->fRec26[1] - fRec29);
			dsp->fVec23[(dsp->IOTA & 255)] = (fRec27 + (0.5f * dsp->fRec24[1]));
			dsp->fRec24[0] = dsp->fVec23[((dsp->IOTA - 248) & 255)];
			float fRec25 = (dsp->fRec24[1] - fRec27);
			output1[i] = (FAUSTFLOAT)((fSlow0 * fRec25) + (fSlow4 * fTemp1));
			dsp->fRec9[1] = dsp->fRec9[0];
			dsp->IOTA = (dsp->IOTA + 1);
			dsp->fRec8[1] = dsp->fRec8[0];
			dsp->fRec11[1] = dsp->fRec11[0];
			dsp->fRec10[1] = dsp->fRec10[0];
			dsp->fRec13[1] = dsp->fRec13[0];
			dsp->fRec12[1] = dsp->fRec12[0];
			dsp->fRec15[1] = dsp->fRec15[0];
			dsp->fRec14[1] = dsp->fRec14[0];
			dsp->fRec17[1] = dsp->fRec17[0];
			dsp->fRec16[1] = dsp->fRec16[0];
			dsp->fRec19[1] = dsp->fRec19[0];
			dsp->fRec18[1] = dsp->fRec18[0];
			dsp->fRec21[1] = dsp->fRec21[0];
			dsp->fRec20[1] = dsp->fRec20[0];
			dsp->fRec23[1] = dsp->fRec23[0];
			dsp->fRec22[1] = dsp->fRec22[0];
			dsp->fRec6[1] = dsp->fRec6[0];
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec33[1] = dsp->fRec33[0];
			dsp->fRec32[1] = dsp->fRec32[0];
			dsp->fRec35[1] = dsp->fRec35[0];
			dsp->fRec34[1] = dsp->fRec34[0];
			dsp->fRec37[1] = dsp->fRec37[0];
			dsp->fRec36[1] = dsp->fRec36[0];
			dsp->fRec39[1] = dsp->fRec39[0];
			dsp->fRec38[1] = dsp->fRec38[0];
			dsp->fRec41[1] = dsp->fRec41[0];
			dsp->fRec40[1] = dsp->fRec40[0];
			dsp->fRec43[1] = dsp->fRec43[0];
			dsp->fRec42[1] = dsp->fRec42[0];
			dsp->fRec45[1] = dsp->fRec45[0];
			dsp->fRec44[1] = dsp->fRec44[0];
			dsp->fRec47[1] = dsp->fRec47[0];
			dsp->fRec46[1] = dsp->fRec46[0];
			dsp->fRec30[1] = dsp->fRec30[0];
			dsp->fRec28[1] = dsp->fRec28[0];
			dsp->fRec26[1] = dsp->fRec26[0];
			dsp->fRec24[1] = dsp->fRec24[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
