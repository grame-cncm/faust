/* ------------------------------------------------------------
name: "felix2"
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
	
	int fSamplingFreq;
	float fConst0;
	int IOTA;
	float fVec0[512];
	float fVec1[512];
	float fVec2[512];
	float fVec3[512];
	float fVec4[512];
	float fVec5[512];
	float fRec0[2];
	FAUSTFLOAT fVbargraph0;
	float fRec1[2];
	FAUSTFLOAT fVbargraph1;
	float fRec2[2];
	FAUSTFLOAT fVbargraph2;
	float fRec3[2];
	FAUSTFLOAT fVbargraph3;
	float fRec4[2];
	FAUSTFLOAT fVbargraph4;
	float fRec5[2];
	FAUSTFLOAT fVbargraph5;
	float fRec6[2];
	FAUSTFLOAT fVbargraph6;
	float fRec7[2];
	FAUSTFLOAT fVbargraph7;
	float fRec8[2];
	FAUSTFLOAT fVbargraph8;
	float fRec9[2];
	FAUSTFLOAT fVbargraph9;
	float fRec10[2];
	FAUSTFLOAT fVbargraph10;
	float fRec11[2];
	FAUSTFLOAT fVbargraph11;
	float fRec12[2];
	FAUSTFLOAT fVbargraph12;
	float fRec13[2];
	FAUSTFLOAT fVbargraph13;
	float fRec14[2];
	FAUSTFLOAT fVbargraph14;
	float fRec15[2];
	FAUSTFLOAT fVbargraph15;
	float fRec16[2];
	FAUSTFLOAT fVbargraph16;
	float fRec17[2];
	FAUSTFLOAT fVbargraph17;
	float fRec18[2];
	FAUSTFLOAT fVbargraph18;
	float fRec19[2];
	FAUSTFLOAT fVbargraph19;
	float fRec20[2];
	FAUSTFLOAT fVbargraph20;
	float fRec21[2];
	FAUSTFLOAT fVbargraph21;
	float fRec22[2];
	FAUSTFLOAT fVbargraph22;
	float fRec23[2];
	FAUSTFLOAT fVbargraph23;
	float fRec24[2];
	FAUSTFLOAT fVbargraph24;
	float fRec25[2];
	FAUSTFLOAT fVbargraph25;
	float fRec26[2];
	FAUSTFLOAT fVbargraph26;
	float fRec27[2];
	FAUSTFLOAT fVbargraph27;
	float fRec28[2];
	FAUSTFLOAT fVbargraph28;
	float fRec29[2];
	FAUSTFLOAT fVbargraph29;
	float fRec30[2];
	FAUSTFLOAT fVbargraph30;
	float fRec31[2];
	FAUSTFLOAT fVbargraph31;
	float fRec32[2];
	FAUSTFLOAT fVbargraph32;
	float fRec33[2];
	FAUSTFLOAT fVbargraph33;
	float fRec34[2];
	FAUSTFLOAT fVbargraph34;
	float fRec35[2];
	FAUSTFLOAT fVbargraph35;
	
} mydsp;

mydsp* newmydsp() { 
	mydsp* dsp = (mydsp*)malloc(sizeof(mydsp));
	return dsp;
}

void deletemydsp(mydsp* dsp) { 
	free(dsp);
}

void metadatamydsp(MetaGlue* m) { 
	m->declare(m->metaInterface, "math.lib/author", "GRAME");
	m->declare(m->metaInterface, "math.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "math.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
	m->declare(m->metaInterface, "math.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "math.lib/name", "Math Library");
	m->declare(m->metaInterface, "math.lib/version", "1.0");
	m->declare(m->metaInterface, "music.lib/author", "GRAME");
	m->declare(m->metaInterface, "music.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "music.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
	m->declare(m->metaInterface, "music.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "music.lib/name", "Music Library");
	m->declare(m->metaInterface, "music.lib/version", "1.0");
	m->declare(m->metaInterface, "name", "felix2");
}

int getSampleRatemydsp(mydsp* dsp) { return dsp->fSamplingFreq; }

int getNumInputsmydsp(mydsp* dsp) {
	return 6;
	
}
int getNumOutputsmydsp(mydsp* dsp) {
	return 36;
	
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
		case 2: {
			rate = 1;
			break;
		}
		case 3: {
			rate = 1;
			break;
		}
		case 4: {
			rate = 1;
			break;
		}
		case 5: {
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
		case 2: {
			rate = 1;
			break;
		}
		case 3: {
			rate = 1;
			break;
		}
		case 4: {
			rate = 1;
			break;
		}
		case 5: {
			rate = 1;
			break;
		}
		case 6: {
			rate = 1;
			break;
		}
		case 7: {
			rate = 1;
			break;
		}
		case 8: {
			rate = 1;
			break;
		}
		case 9: {
			rate = 1;
			break;
		}
		case 10: {
			rate = 1;
			break;
		}
		case 11: {
			rate = 1;
			break;
		}
		case 12: {
			rate = 1;
			break;
		}
		case 13: {
			rate = 1;
			break;
		}
		case 14: {
			rate = 1;
			break;
		}
		case 15: {
			rate = 1;
			break;
		}
		case 16: {
			rate = 1;
			break;
		}
		case 17: {
			rate = 1;
			break;
		}
		case 18: {
			rate = 1;
			break;
		}
		case 19: {
			rate = 1;
			break;
		}
		case 20: {
			rate = 1;
			break;
		}
		case 21: {
			rate = 1;
			break;
		}
		case 22: {
			rate = 1;
			break;
		}
		case 23: {
			rate = 1;
			break;
		}
		case 24: {
			rate = 1;
			break;
		}
		case 25: {
			rate = 1;
			break;
		}
		case 26: {
			rate = 1;
			break;
		}
		case 27: {
			rate = 1;
			break;
		}
		case 28: {
			rate = 1;
			break;
		}
		case 29: {
			rate = 1;
			break;
		}
		case 30: {
			rate = 1;
			break;
		}
		case 31: {
			rate = 1;
			break;
		}
		case 32: {
			rate = 1;
			break;
		}
		case 33: {
			rate = 1;
			break;
		}
		case 34: {
			rate = 1;
			break;
		}
		case 35: {
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
	
}

void instanceClearmydsp(mydsp* dsp) {
	dsp->IOTA = 0;
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 512); l0 = (l0 + 1)) {
			dsp->fVec0[l0] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 512); l1 = (l1 + 1)) {
			dsp->fVec1[l1] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 512); l2 = (l2 + 1)) {
			dsp->fVec2[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 512); l3 = (l3 + 1)) {
			dsp->fVec3[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 512); l4 = (l4 + 1)) {
			dsp->fVec4[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 512); l5 = (l5 + 1)) {
			dsp->fVec5[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			dsp->fRec0[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			dsp->fRec1[l7] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			dsp->fRec2[l8] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			dsp->fRec3[l9] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			dsp->fRec4[l10] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			dsp->fRec5[l11] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			dsp->fRec6[l12] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l13;
		for (l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			dsp->fRec7[l13] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l14;
		for (l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			dsp->fRec8[l14] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l15;
		for (l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			dsp->fRec9[l15] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l16;
		for (l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			dsp->fRec10[l16] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l17;
		for (l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			dsp->fRec11[l17] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l18;
		for (l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			dsp->fRec12[l18] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l19;
		for (l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			dsp->fRec13[l19] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l20;
		for (l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			dsp->fRec14[l20] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l21;
		for (l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			dsp->fRec15[l21] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l22;
		for (l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			dsp->fRec16[l22] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l23;
		for (l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			dsp->fRec17[l23] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l24;
		for (l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			dsp->fRec18[l24] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l25;
		for (l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			dsp->fRec19[l25] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l26;
		for (l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			dsp->fRec20[l26] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l27;
		for (l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			dsp->fRec21[l27] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l28;
		for (l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			dsp->fRec22[l28] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l29;
		for (l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			dsp->fRec23[l29] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l30;
		for (l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			dsp->fRec24[l30] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l31;
		for (l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			dsp->fRec25[l31] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l32;
		for (l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			dsp->fRec26[l32] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l33;
		for (l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			dsp->fRec27[l33] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l34;
		for (l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			dsp->fRec28[l34] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l35;
		for (l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			dsp->fRec29[l35] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l36;
		for (l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			dsp->fRec30[l36] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l37;
		for (l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			dsp->fRec31[l37] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l38;
		for (l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			dsp->fRec32[l38] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l39;
		for (l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			dsp->fRec33[l39] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l40;
		for (l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			dsp->fRec34[l40] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l41;
		for (l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			dsp->fRec35[l41] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = (96.0f / min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq)));
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "felix2");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "ctrl   0");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "ctrl  0", &dsp->fVbargraph0, 0.0f, 1.0f);
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "ctrl  1", &dsp->fVbargraph1, 0.0f, 1.0f);
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "ctrl  2", &dsp->fVbargraph2, 0.0f, 1.0f);
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "ctrl  3", &dsp->fVbargraph3, 0.0f, 1.0f);
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "ctrl  4", &dsp->fVbargraph4, 0.0f, 1.0f);
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "ctrl  5", &dsp->fVbargraph5, 0.0f, 1.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "ctrl   1");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "ctrl 10", &dsp->fVbargraph6, 0.0f, 1.0f);
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "ctrl 11", &dsp->fVbargraph7, 0.0f, 1.0f);
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "ctrl 12", &dsp->fVbargraph8, 0.0f, 1.0f);
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "ctrl 13", &dsp->fVbargraph9, 0.0f, 1.0f);
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "ctrl 14", &dsp->fVbargraph10, 0.0f, 1.0f);
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "ctrl 15", &dsp->fVbargraph11, 0.0f, 1.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "ctrl   2");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "ctrl 20", &dsp->fVbargraph12, 0.0f, 1.0f);
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "ctrl 21", &dsp->fVbargraph13, 0.0f, 1.0f);
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "ctrl 22", &dsp->fVbargraph14, 0.0f, 1.0f);
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "ctrl 23", &dsp->fVbargraph15, 0.0f, 1.0f);
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "ctrl 24", &dsp->fVbargraph16, 0.0f, 1.0f);
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "ctrl 25", &dsp->fVbargraph17, 0.0f, 1.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "ctrl   3");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "ctrl 30", &dsp->fVbargraph18, 0.0f, 1.0f);
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "ctrl 31", &dsp->fVbargraph19, 0.0f, 1.0f);
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "ctrl 32", &dsp->fVbargraph20, 0.0f, 1.0f);
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "ctrl 33", &dsp->fVbargraph21, 0.0f, 1.0f);
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "ctrl 34", &dsp->fVbargraph22, 0.0f, 1.0f);
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "ctrl 35", &dsp->fVbargraph23, 0.0f, 1.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "ctrl   4");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "ctrl 40", &dsp->fVbargraph24, 0.0f, 1.0f);
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "ctrl 41", &dsp->fVbargraph25, 0.0f, 1.0f);
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "ctrl 42", &dsp->fVbargraph26, 0.0f, 1.0f);
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "ctrl 43", &dsp->fVbargraph27, 0.0f, 1.0f);
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "ctrl 44", &dsp->fVbargraph28, 0.0f, 1.0f);
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "ctrl 45", &dsp->fVbargraph29, 0.0f, 1.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "ctrl   5");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "ctrl 50", &dsp->fVbargraph30, 0.0f, 1.0f);
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "ctrl 51", &dsp->fVbargraph31, 0.0f, 1.0f);
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "ctrl 52", &dsp->fVbargraph32, 0.0f, 1.0f);
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "ctrl 53", &dsp->fVbargraph33, 0.0f, 1.0f);
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "ctrl 54", &dsp->fVbargraph34, 0.0f, 1.0f);
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "ctrl 55", &dsp->fVbargraph35, 0.0f, 1.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* input0 = inputs[0];
	FAUSTFLOAT* input1 = inputs[1];
	FAUSTFLOAT* input2 = inputs[2];
	FAUSTFLOAT* input3 = inputs[3];
	FAUSTFLOAT* input4 = inputs[4];
	FAUSTFLOAT* input5 = inputs[5];
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	FAUSTFLOAT* output2 = outputs[2];
	FAUSTFLOAT* output3 = outputs[3];
	FAUSTFLOAT* output4 = outputs[4];
	FAUSTFLOAT* output5 = outputs[5];
	FAUSTFLOAT* output6 = outputs[6];
	FAUSTFLOAT* output7 = outputs[7];
	FAUSTFLOAT* output8 = outputs[8];
	FAUSTFLOAT* output9 = outputs[9];
	FAUSTFLOAT* output10 = outputs[10];
	FAUSTFLOAT* output11 = outputs[11];
	FAUSTFLOAT* output12 = outputs[12];
	FAUSTFLOAT* output13 = outputs[13];
	FAUSTFLOAT* output14 = outputs[14];
	FAUSTFLOAT* output15 = outputs[15];
	FAUSTFLOAT* output16 = outputs[16];
	FAUSTFLOAT* output17 = outputs[17];
	FAUSTFLOAT* output18 = outputs[18];
	FAUSTFLOAT* output19 = outputs[19];
	FAUSTFLOAT* output20 = outputs[20];
	FAUSTFLOAT* output21 = outputs[21];
	FAUSTFLOAT* output22 = outputs[22];
	FAUSTFLOAT* output23 = outputs[23];
	FAUSTFLOAT* output24 = outputs[24];
	FAUSTFLOAT* output25 = outputs[25];
	FAUSTFLOAT* output26 = outputs[26];
	FAUSTFLOAT* output27 = outputs[27];
	FAUSTFLOAT* output28 = outputs[28];
	FAUSTFLOAT* output29 = outputs[29];
	FAUSTFLOAT* output30 = outputs[30];
	FAUSTFLOAT* output31 = outputs[31];
	FAUSTFLOAT* output32 = outputs[32];
	FAUSTFLOAT* output33 = outputs[33];
	FAUSTFLOAT* output34 = outputs[34];
	FAUSTFLOAT* output35 = outputs[35];
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->fVec0[(dsp->IOTA & 511)] = (float)input0[i];
			float fTemp0 = (float)input1[i];
			dsp->fVec1[(dsp->IOTA & 511)] = fTemp0;
			float fTemp1 = (float)input2[i];
			dsp->fVec2[(dsp->IOTA & 511)] = fTemp1;
			float fTemp2 = (float)input3[i];
			dsp->fVec3[(dsp->IOTA & 511)] = fTemp2;
			float fTemp3 = (float)input4[i];
			dsp->fVec4[(dsp->IOTA & 511)] = fTemp3;
			float fTemp4 = (float)input5[i];
			dsp->fVec5[(dsp->IOTA & 511)] = fTemp4;
			dsp->fRec0[0] = max((dsp->fRec0[1] - dsp->fConst0), fabsf((((((dsp->fVec0[((dsp->IOTA - 256) & 511)] + dsp->fVec1[((dsp->IOTA - 244) & 511)]) + dsp->fVec2[((dsp->IOTA - 233) & 511)]) + dsp->fVec3[((dsp->IOTA - 221) & 511)]) + dsp->fVec4[((dsp->IOTA - 209) & 511)]) + dsp->fVec5[((dsp->IOTA - 197) & 511)])));
			dsp->fVbargraph0 = (FAUSTFLOAT)dsp->fRec0[0];
			output0[i] = (FAUSTFLOAT)dsp->fVbargraph0;
			float fTemp5 = (dsp->fVec0[((dsp->IOTA - 256) & 511)] + dsp->fVec1[((dsp->IOTA - 246) & 511)]);
			dsp->fRec1[0] = max((dsp->fRec1[1] - dsp->fConst0), fabsf(((((fTemp5 + dsp->fVec2[((dsp->IOTA - 236) & 511)]) + dsp->fVec3[((dsp->IOTA - 225) & 511)]) + dsp->fVec4[((dsp->IOTA - 215) & 511)]) + dsp->fVec5[((dsp->IOTA - 204) & 511)])));
			dsp->fVbargraph1 = (FAUSTFLOAT)dsp->fRec1[0];
			output1[i] = (FAUSTFLOAT)dsp->fVbargraph1;
			dsp->fRec2[0] = max((dsp->fRec2[1] - dsp->fConst0), fabsf((((((dsp->fVec0[((dsp->IOTA - 256) & 511)] + dsp->fVec1[((dsp->IOTA - 247) & 511)]) + dsp->fVec2[((dsp->IOTA - 239) & 511)]) + dsp->fVec3[((dsp->IOTA - 230) & 511)]) + dsp->fVec4[((dsp->IOTA - 220) & 511)]) + dsp->fVec5[((dsp->IOTA - 211) & 511)])));
			dsp->fVbargraph2 = (FAUSTFLOAT)dsp->fRec2[0];
			output2[i] = (FAUSTFLOAT)dsp->fVbargraph2;
			float fTemp6 = (dsp->fVec0[((dsp->IOTA - 256) & 511)] + dsp->fVec1[((dsp->IOTA - 249) & 511)]);
			float fTemp7 = (fTemp6 + dsp->fVec2[((dsp->IOTA - 241) & 511)]);
			dsp->fRec3[0] = max((dsp->fRec3[1] - dsp->fConst0), fabsf((((fTemp7 + dsp->fVec3[((dsp->IOTA - 233) & 511)]) + dsp->fVec4[((dsp->IOTA - 225) & 511)]) + dsp->fVec5[((dsp->IOTA - 217) & 511)])));
			dsp->fVbargraph3 = (FAUSTFLOAT)dsp->fRec3[0];
			output3[i] = (FAUSTFLOAT)dsp->fVbargraph3;
			float fTemp8 = (dsp->fVec0[((dsp->IOTA - 256) & 511)] + dsp->fVec1[((dsp->IOTA - 250) & 511)]);
			dsp->fRec4[0] = max((dsp->fRec4[1] - dsp->fConst0), fabsf(((((fTemp8 + dsp->fVec2[((dsp->IOTA - 243) & 511)]) + dsp->fVec3[((dsp->IOTA - 236) & 511)]) + dsp->fVec4[((dsp->IOTA - 229) & 511)]) + dsp->fVec5[((dsp->IOTA - 222) & 511)])));
			dsp->fVbargraph4 = (FAUSTFLOAT)dsp->fRec4[0];
			output4[i] = (FAUSTFLOAT)dsp->fVbargraph4;
			dsp->fRec5[0] = max((dsp->fRec5[1] - dsp->fConst0), fabsf(((((fTemp8 + dsp->fVec2[((dsp->IOTA - 245) & 511)]) + dsp->fVec3[((dsp->IOTA - 239) & 511)]) + dsp->fVec4[((dsp->IOTA - 232) & 511)]) + dsp->fVec5[((dsp->IOTA - 225) & 511)])));
			dsp->fVbargraph5 = (FAUSTFLOAT)dsp->fRec5[0];
			output5[i] = (FAUSTFLOAT)dsp->fVbargraph5;
			dsp->fRec6[0] = max((dsp->fRec6[1] - dsp->fConst0), fabsf(((((fTemp5 + dsp->fVec2[((dsp->IOTA - 235) & 511)]) + dsp->fVec3[((dsp->IOTA - 224) & 511)]) + dsp->fVec4[((dsp->IOTA - 213) & 511)]) + dsp->fVec5[((dsp->IOTA - 201) & 511)])));
			dsp->fVbargraph6 = (FAUSTFLOAT)dsp->fRec6[0];
			output6[i] = (FAUSTFLOAT)dsp->fVbargraph6;
			dsp->fRec7[0] = max((dsp->fRec7[1] - dsp->fConst0), fabsf((dsp->fVec4[((dsp->IOTA - 221) & 511)] + (dsp->fVec1[((dsp->IOTA - 248) & 511)] + (dsp->fVec5[((dsp->IOTA - 211) & 511)] + (dsp->fVec3[((dsp->IOTA - 230) & 511)] + (dsp->fVec0[((dsp->IOTA - 256) & 511)] + dsp->fVec2[((dsp->IOTA - 239) & 511)])))))));
			dsp->fVbargraph7 = (FAUSTFLOAT)dsp->fRec7[0];
			output7[i] = (FAUSTFLOAT)dsp->fVbargraph7;
			dsp->fRec8[0] = max((dsp->fRec8[1] - dsp->fConst0), fabsf(((((fTemp6 + dsp->fVec2[((dsp->IOTA - 243) & 511)]) + dsp->fVec3[((dsp->IOTA - 235) & 511)]) + dsp->fVec4[((dsp->IOTA - 227) & 511)]) + dsp->fVec5[((dsp->IOTA - 219) & 511)])));
			dsp->fVbargraph8 = (FAUSTFLOAT)dsp->fRec8[0];
			output8[i] = (FAUSTFLOAT)dsp->fVbargraph8;
			dsp->fRec9[0] = max((dsp->fRec9[1] - dsp->fConst0), fabsf((dsp->fVec1[((dsp->IOTA - 251) & 511)] + (dsp->fVec5[((dsp->IOTA - 225) & 511)] + (dsp->fVec4[((dsp->IOTA - 232) & 511)] + (dsp->fVec3[((dsp->IOTA - 239) & 511)] + (dsp->fVec0[((dsp->IOTA - 256) & 511)] + dsp->fVec2[((dsp->IOTA - 245) & 511)])))))));
			dsp->fVbargraph9 = (FAUSTFLOAT)dsp->fRec9[0];
			output9[i] = (FAUSTFLOAT)dsp->fVbargraph9;
			dsp->fRec10[0] = max((dsp->fRec10[1] - dsp->fConst0), fabsf((((((dsp->fVec0[((dsp->IOTA - 256) & 511)] + dsp->fVec1[((dsp->IOTA - 251) & 511)]) + dsp->fVec2[((dsp->IOTA - 247) & 511)]) + dsp->fVec3[((dsp->IOTA - 241) & 511)]) + dsp->fVec4[((dsp->IOTA - 236) & 511)]) + dsp->fVec5[((dsp->IOTA - 230) & 511)])));
			dsp->fVbargraph10 = (FAUSTFLOAT)dsp->fRec10[0];
			output10[i] = (FAUSTFLOAT)dsp->fVbargraph10;
			float fTemp9 = ((dsp->fVec0[((dsp->IOTA - 256) & 511)] + dsp->fVec1[((dsp->IOTA - 252) & 511)]) + dsp->fVec2[((dsp->IOTA - 248) & 511)]);
			dsp->fRec11[0] = max((dsp->fRec11[1] - dsp->fConst0), fabsf((((fTemp9 + dsp->fVec3[((dsp->IOTA - 243) & 511)]) + dsp->fVec4[((dsp->IOTA - 238) & 511)]) + dsp->fVec5[((dsp->IOTA - 233) & 511)])));
			dsp->fVbargraph11 = (FAUSTFLOAT)dsp->fRec11[0];
			output11[i] = (FAUSTFLOAT)dsp->fVbargraph11;
			dsp->fRec12[0] = max((dsp->fRec12[1] - dsp->fConst0), fabsf((((fTemp7 + dsp->fVec3[((dsp->IOTA - 232) & 511)]) + dsp->fVec4[((dsp->IOTA - 223) & 511)]) + dsp->fVec5[((dsp->IOTA - 212) & 511)])));
			dsp->fVbargraph12 = (FAUSTFLOAT)dsp->fRec12[0];
			output12[i] = (FAUSTFLOAT)dsp->fVbargraph12;
			dsp->fRec13[0] = max((dsp->fRec13[1] - dsp->fConst0), fabsf((dsp->fVec5[((dsp->IOTA - 224) & 511)] + (dsp->fVec3[((dsp->IOTA - 240) & 511)] + (dsp->fVec2[((dsp->IOTA - 246) & 511)] + (dsp->fVec1[((dsp->IOTA - 251) & 511)] + (dsp->fVec0[((dsp->IOTA - 256) & 511)] + dsp->fVec4[((dsp->IOTA - 232) & 511)])))))));
			dsp->fVbargraph13 = (FAUSTFLOAT)dsp->fRec13[0];
			output13[i] = (FAUSTFLOAT)dsp->fVbargraph13;
			dsp->fRec14[0] = max((dsp->fRec14[1] - dsp->fConst0), fabsf((dsp->fVec5[((dsp->IOTA - 231) & 511)] + (dsp->fVec3[((dsp->IOTA - 244) & 511)] + (fTemp9 + dsp->fVec4[((dsp->IOTA - 238) & 511)])))));
			dsp->fVbargraph14 = (FAUSTFLOAT)dsp->fRec14[0];
			output14[i] = (FAUSTFLOAT)dsp->fVbargraph14;
			dsp->fRec15[0] = max((dsp->fRec15[1] - dsp->fConst0), fabsf((((((dsp->fVec0[((dsp->IOTA - 256) & 511)] + dsp->fVec1[((dsp->IOTA - 253) & 511)]) + dsp->fVec2[((dsp->IOTA - 250) & 511)]) + dsp->fVec3[((dsp->IOTA - 246) & 511)]) + dsp->fVec4[((dsp->IOTA - 241) & 511)]) + dsp->fVec5[((dsp->IOTA - 236) & 511)])));
			dsp->fVbargraph15 = (FAUSTFLOAT)dsp->fRec15[0];
			output15[i] = (FAUSTFLOAT)dsp->fVbargraph15;
			float fTemp10 = (dsp->fVec0[((dsp->IOTA - 256) & 511)] + dsp->fVec1[((dsp->IOTA - 254) & 511)]);
			dsp->fRec16[0] = max((dsp->fRec16[1] - dsp->fConst0), fabsf(((((fTemp10 + dsp->fVec2[((dsp->IOTA - 251) & 511)]) + dsp->fVec3[((dsp->IOTA - 248) & 511)]) + dsp->fVec4[((dsp->IOTA - 244) & 511)]) + dsp->fVec5[((dsp->IOTA - 239) & 511)])));
			dsp->fVbargraph16 = (FAUSTFLOAT)dsp->fRec16[0];
			output16[i] = (FAUSTFLOAT)dsp->fVbargraph16;
			dsp->fRec17[0] = max((dsp->fRec17[1] - dsp->fConst0), fabsf(((((fTemp10 + dsp->fVec2[((dsp->IOTA - 252) & 511)]) + dsp->fVec3[((dsp->IOTA - 249) & 511)]) + dsp->fVec4[((dsp->IOTA - 245) & 511)]) + dsp->fVec5[((dsp->IOTA - 242) & 511)])));
			dsp->fVbargraph17 = (FAUSTFLOAT)dsp->fRec17[0];
			output17[i] = (FAUSTFLOAT)dsp->fVbargraph17;
			dsp->fRec18[0] = max((dsp->fRec18[1] - dsp->fConst0), fabsf((dsp->fVec4[((dsp->IOTA - 246) & 511)] + (dsp->fVec3[((dsp->IOTA - 252) & 511)] + (dsp->fVec2[((dsp->IOTA - 256) & 511)] + (dsp->fVec1[((dsp->IOTA - 257) & 511)] + (dsp->fVec0[((dsp->IOTA - 256) & 511)] + dsp->fVec5[((dsp->IOTA - 239) & 511)])))))));
			dsp->fVbargraph18 = (FAUSTFLOAT)dsp->fRec18[0];
			output18[i] = (FAUSTFLOAT)dsp->fVbargraph18;
			float fTemp11 = (dsp->fVec1[((dsp->IOTA - 256) & 511)] + (dsp->fVec0[((dsp->IOTA - 256) & 511)] + dsp->fVec2[((dsp->IOTA - 256) & 511)]));
			dsp->fRec19[0] = max((dsp->fRec19[1] - dsp->fConst0), fabsf((dsp->fVec5[((dsp->IOTA - 245) & 511)] + (dsp->fVec4[((dsp->IOTA - 250) & 511)] + (dsp->fVec3[((dsp->IOTA - 253) & 511)] + fTemp11)))));
			dsp->fVbargraph19 = (FAUSTFLOAT)dsp->fRec19[0];
			output19[i] = (FAUSTFLOAT)dsp->fVbargraph19;
			float fTemp12 = (fTemp11 + dsp->fVec3[((dsp->IOTA - 254) & 511)]);
			dsp->fRec20[0] = max((dsp->fRec20[1] - dsp->fConst0), fabsf(((fTemp12 + dsp->fVec4[((dsp->IOTA - 251) & 511)]) + dsp->fVec5[((dsp->IOTA - 247) & 511)])));
			dsp->fVbargraph20 = (FAUSTFLOAT)dsp->fRec20[0];
			output20[i] = (FAUSTFLOAT)dsp->fVbargraph20;
			dsp->fRec21[0] = max((dsp->fRec21[1] - dsp->fConst0), fabsf(((fTemp12 + dsp->fVec4[((dsp->IOTA - 252) & 511)]) + dsp->fVec5[((dsp->IOTA - 249) & 511)])));
			dsp->fVbargraph21 = (FAUSTFLOAT)dsp->fRec21[0];
			output21[i] = (FAUSTFLOAT)dsp->fVbargraph21;
			dsp->fRec22[0] = max((dsp->fRec22[1] - dsp->fConst0), fabsf(((fTemp12 + dsp->fVec4[((dsp->IOTA - 253) & 511)]) + dsp->fVec5[((dsp->IOTA - 250) & 511)])));
			dsp->fVbargraph22 = (FAUSTFLOAT)dsp->fRec22[0];
			output22[i] = (FAUSTFLOAT)dsp->fVbargraph22;
			dsp->fRec23[0] = max((dsp->fRec23[1] - dsp->fConst0), fabsf((dsp->fVec5[((dsp->IOTA - 251) & 511)] + (dsp->fVec3[((dsp->IOTA - 255) & 511)] + (fTemp11 + dsp->fVec4[((dsp->IOTA - 253) & 511)])))));
			dsp->fVbargraph23 = (FAUSTFLOAT)dsp->fRec23[0];
			output23[i] = (FAUSTFLOAT)dsp->fVbargraph23;
			dsp->fRec24[0] = max((dsp->fRec24[1] - dsp->fConst0), fabsf((((((dsp->fVec0[((dsp->IOTA - 256) & 511)] + dsp->fVec1[((dsp->IOTA - 263) & 511)]) + dsp->fVec2[((dsp->IOTA - 270) & 511)]) + dsp->fVec3[((dsp->IOTA - 274) & 511)]) + dsp->fVec4[((dsp->IOTA - 276) & 511)]) + dsp->fVec5[((dsp->IOTA - 276) & 511)])));
			dsp->fVbargraph24 = (FAUSTFLOAT)dsp->fRec24[0];
			output24[i] = (FAUSTFLOAT)dsp->fVbargraph24;
			dsp->fRec25[0] = max((dsp->fRec25[1] - dsp->fConst0), fabsf((((((dsp->fVec0[((dsp->IOTA - 256) & 511)] + dsp->fVec1[((dsp->IOTA - 261) & 511)]) + dsp->fVec2[((dsp->IOTA - 265) & 511)]) + dsp->fVec3[((dsp->IOTA - 268) & 511)]) + dsp->fVec4[((dsp->IOTA - 269) & 511)]) + dsp->fVec5[((dsp->IOTA - 269) & 511)])));
			dsp->fVbargraph25 = (FAUSTFLOAT)dsp->fRec25[0];
			output25[i] = (FAUSTFLOAT)dsp->fVbargraph25;
			float fTemp13 = ((dsp->fVec0[((dsp->IOTA - 256) & 511)] + dsp->fVec1[((dsp->IOTA - 260) & 511)]) + dsp->fVec2[((dsp->IOTA - 263) & 511)]);
			dsp->fRec26[0] = max((dsp->fRec26[1] - dsp->fConst0), fabsf((((fTemp13 + dsp->fVec3[((dsp->IOTA - 265) & 511)]) + dsp->fVec4[((dsp->IOTA - 265) & 511)]) + dsp->fVec5[((dsp->IOTA - 265) & 511)])));
			dsp->fVbargraph26 = (FAUSTFLOAT)dsp->fRec26[0];
			output26[i] = (FAUSTFLOAT)dsp->fVbargraph26;
			dsp->fRec27[0] = max((dsp->fRec27[1] - dsp->fConst0), fabsf((((((dsp->fVec0[((dsp->IOTA - 256) & 511)] + dsp->fVec1[((dsp->IOTA - 259) & 511)]) + dsp->fVec2[((dsp->IOTA - 261) & 511)]) + dsp->fVec3[((dsp->IOTA - 263) & 511)]) + dsp->fVec4[((dsp->IOTA - 263) & 511)]) + dsp->fVec5[((dsp->IOTA - 263) & 511)])));
			dsp->fVbargraph27 = (FAUSTFLOAT)dsp->fRec27[0];
			output27[i] = (FAUSTFLOAT)dsp->fVbargraph27;
			float fTemp14 = (dsp->fVec0[((dsp->IOTA - 256) & 511)] + dsp->fVec1[((dsp->IOTA - 258) & 511)]);
			dsp->fRec28[0] = max((dsp->fRec28[1] - dsp->fConst0), fabsf(((((fTemp14 + dsp->fVec2[((dsp->IOTA - 260) & 511)]) + dsp->fVec3[((dsp->IOTA - 261) & 511)]) + dsp->fVec4[((dsp->IOTA - 262) & 511)]) + dsp->fVec5[((dsp->IOTA - 262) & 511)])));
			dsp->fVbargraph28 = (FAUSTFLOAT)dsp->fRec28[0];
			output28[i] = (FAUSTFLOAT)dsp->fVbargraph28;
			dsp->fRec29[0] = max((dsp->fRec29[1] - dsp->fConst0), fabsf(((((fTemp14 + dsp->fVec2[((dsp->IOTA - 259) & 511)]) + dsp->fVec3[((dsp->IOTA - 260) & 511)]) + dsp->fVec4[((dsp->IOTA - 261) & 511)]) + dsp->fVec5[((dsp->IOTA - 261) & 511)])));
			dsp->fVbargraph29 = (FAUSTFLOAT)dsp->fRec29[0];
			output29[i] = (FAUSTFLOAT)dsp->fVbargraph29;
			dsp->fRec30[0] = max((dsp->fRec30[1] - dsp->fConst0), fabsf((((((dsp->fVec0[((dsp->IOTA - 256) & 511)] + dsp->fVec1[((dsp->IOTA - 266) & 511)]) + dsp->fVec2[((dsp->IOTA - 276) & 511)]) + dsp->fVec3[((dsp->IOTA - 285) & 511)]) + dsp->fVec4[((dsp->IOTA - 293) & 511)]) + dsp->fVec5[((dsp->IOTA - 300) & 511)])));
			dsp->fVbargraph30 = (FAUSTFLOAT)dsp->fRec30[0];
			output30[i] = (FAUSTFLOAT)dsp->fVbargraph30;
			dsp->fRec31[0] = max((dsp->fRec31[1] - dsp->fConst0), fabsf((((((dsp->fVec0[((dsp->IOTA - 256) & 511)] + dsp->fVec1[((dsp->IOTA - 264) & 511)]) + dsp->fVec2[((dsp->IOTA - 272) & 511)]) + dsp->fVec3[((dsp->IOTA - 278) & 511)]) + dsp->fVec4[((dsp->IOTA - 284) & 511)]) + dsp->fVec5[((dsp->IOTA - 289) & 511)])));
			dsp->fVbargraph31 = (FAUSTFLOAT)dsp->fRec31[0];
			output31[i] = (FAUSTFLOAT)dsp->fVbargraph31;
			dsp->fRec32[0] = max((dsp->fRec32[1] - dsp->fConst0), fabsf((((((dsp->fVec0[((dsp->IOTA - 256) & 511)] + dsp->fVec1[((dsp->IOTA - 262) & 511)]) + dsp->fVec2[((dsp->IOTA - 268) & 511)]) + dsp->fVec3[((dsp->IOTA - 273) & 511)]) + dsp->fVec4[((dsp->IOTA - 278) & 511)]) + dsp->fVec5[((dsp->IOTA - 281) & 511)])));
			dsp->fVbargraph32 = (FAUSTFLOAT)dsp->fRec32[0];
			output32[i] = (FAUSTFLOAT)dsp->fVbargraph32;
			dsp->fRec33[0] = max((dsp->fRec33[1] - dsp->fConst0), fabsf((dsp->fVec4[((dsp->IOTA - 274) & 511)] + (dsp->fVec3[((dsp->IOTA - 270) & 511)] + (dsp->fVec2[((dsp->IOTA - 266) & 511)] + (dsp->fVec1[((dsp->IOTA - 261) & 511)] + (dsp->fVec0[((dsp->IOTA - 256) & 511)] + dsp->fVec5[((dsp->IOTA - 276) & 511)])))))));
			dsp->fVbargraph33 = (FAUSTFLOAT)dsp->fRec33[0];
			output33[i] = (FAUSTFLOAT)dsp->fVbargraph33;
			dsp->fRec34[0] = max((dsp->fRec34[1] - dsp->fConst0), fabsf((((dsp->fVec2[((dsp->IOTA - 264) & 511)] + (dsp->fVec1[((dsp->IOTA - 260) & 511)] + (dsp->fVec0[((dsp->IOTA - 256) & 511)] + dsp->fVec3[((dsp->IOTA - 268) & 511)]))) + dsp->fVec4[((dsp->IOTA - 271) & 511)]) + dsp->fVec5[((dsp->IOTA - 273) & 511)])));
			dsp->fVbargraph34 = (FAUSTFLOAT)dsp->fRec34[0];
			output34[i] = (FAUSTFLOAT)dsp->fVbargraph34;
			dsp->fRec35[0] = max((dsp->fRec35[1] - dsp->fConst0), fabsf((((fTemp13 + dsp->fVec3[((dsp->IOTA - 266) & 511)]) + dsp->fVec4[((dsp->IOTA - 268) & 511)]) + dsp->fVec5[((dsp->IOTA - 270) & 511)])));
			dsp->fVbargraph35 = (FAUSTFLOAT)dsp->fRec35[0];
			output35[i] = (FAUSTFLOAT)dsp->fVbargraph35;
			dsp->IOTA = (dsp->IOTA + 1);
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec3[1] = dsp->fRec3[0];
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
			dsp->fRec20[1] = dsp->fRec20[0];
			dsp->fRec21[1] = dsp->fRec21[0];
			dsp->fRec22[1] = dsp->fRec22[0];
			dsp->fRec23[1] = dsp->fRec23[0];
			dsp->fRec24[1] = dsp->fRec24[0];
			dsp->fRec25[1] = dsp->fRec25[0];
			dsp->fRec26[1] = dsp->fRec26[0];
			dsp->fRec27[1] = dsp->fRec27[0];
			dsp->fRec28[1] = dsp->fRec28[0];
			dsp->fRec29[1] = dsp->fRec29[0];
			dsp->fRec30[1] = dsp->fRec30[0];
			dsp->fRec31[1] = dsp->fRec31[0];
			dsp->fRec32[1] = dsp->fRec32[0];
			dsp->fRec33[1] = dsp->fRec33[0];
			dsp->fRec34[1] = dsp->fRec34[0];
			dsp->fRec35[1] = dsp->fRec35[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
