/* ------------------------------------------------------------
name: "acGuitar"
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
	
	int iRec10[2];
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fHslider0;
	float fRec29[2];
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	float fRec30[2];
	float fRec25[2];
	float fRec31[2];
	float fRec33[4];
	int IOTA;
	float fRec34[2048];
	float fVec0[2];
	FAUSTFLOAT fHslider3;
	int iVec1[2];
	float fVec2[2];
	float fRec32[2048];
	float fRec21[2];
	float fRec17[2048];
	float fRec19[2];
	float fRec15[4];
	int iRec6[2];
	float fRec2[2048];
	float fRec0[2];
	int iRec46[2];
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT fHslider5;
	float fRec65[2];
	float fRec61[2];
	float fRec66[2];
	FAUSTFLOAT fHslider6;
	int iVec3[2];
	float fRec68[4];
	float fRec69[2048];
	float fVec4[2];
	float fVec5[2];
	float fRec67[2048];
	float fRec57[2];
	float fRec53[2048];
	float fRec55[2];
	float fRec51[4];
	int iRec42[2];
	float fRec38[2048];
	float fRec36[2];
	int iRec81[2];
	FAUSTFLOAT fHslider7;
	FAUSTFLOAT fHslider8;
	float fRec100[2];
	float fRec96[2];
	float fRec101[2];
	FAUSTFLOAT fHslider9;
	int iVec6[2];
	float fRec103[4];
	float fRec104[2048];
	float fVec7[2];
	float fVec8[2];
	float fRec102[2048];
	float fRec92[2];
	float fRec88[2048];
	float fRec90[2];
	float fRec86[4];
	int iRec77[2];
	float fRec73[2048];
	float fRec71[2];
	int iRec116[2];
	FAUSTFLOAT fHslider10;
	FAUSTFLOAT fHslider11;
	float fRec135[2];
	float fRec131[2];
	float fRec136[2];
	FAUSTFLOAT fHslider12;
	int iVec9[2];
	float fRec138[4];
	float fRec139[2048];
	float fVec10[2];
	float fVec11[2];
	float fRec137[2048];
	float fRec127[2];
	float fRec123[2048];
	float fRec125[2];
	float fRec121[4];
	int iRec112[2];
	float fRec108[2048];
	float fRec106[2];
	int iRec151[2];
	FAUSTFLOAT fHslider13;
	FAUSTFLOAT fHslider14;
	float fRec170[2];
	float fRec166[2];
	float fRec171[2];
	FAUSTFLOAT fHslider15;
	int iVec12[2];
	float fRec173[4];
	float fRec174[2048];
	float fVec13[2];
	float fVec14[2];
	float fRec172[2048];
	float fRec162[2];
	float fRec158[2048];
	float fRec160[2];
	float fRec156[4];
	int iRec147[2];
	float fRec143[2048];
	float fRec141[2];
	int iRec186[2];
	FAUSTFLOAT fHslider16;
	FAUSTFLOAT fHslider17;
	float fRec205[2];
	float fRec201[2];
	float fRec206[2];
	FAUSTFLOAT fHslider18;
	int iVec15[2];
	float fRec208[4];
	float fRec209[2048];
	float fVec16[2];
	float fVec17[2];
	float fRec207[2048];
	float fRec197[2];
	float fRec193[2048];
	float fRec195[2];
	float fRec191[4];
	int iRec182[2];
	float fRec178[2048];
	float fRec176[2];
	
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
	m->declare(m->metaInterface, "interface", "SmartKeyboard{  'Number of Keyboards':'7',  'Max Keyboard Polyphony':'0',  'Rounding Mode':'2',  'Keyboard 0 - Number of Keys':'14',   'Keyboard 1 - Number of Keys':'14',  'Keyboard 2 - Number of Keys':'14',  'Keyboard 3 - Number of Keys':'14',  'Keyboard 4 - Number of Keys':'14',  'Keyboard 5 - Number of Keys':'14',  'Keyboard 6 - Number of Keys':'6',  'Keyboard 0 - Lowest Key':'52',  'Keyboard 1 - Lowest Key':'57',  'Keyboard 2 - Lowest Key':'62',  'Keyboard 3 - Lowest Key':'67',  'Keyboard 4 - Lowest Key':'71',  'Keyboard 5 - Lowest Key':'76',  'Keyboard 0 - Send Keyboard Freq':'1',  'Keyboard 1 - Send Keyboard Freq':'1',  'Keyboard 2 - Send Keyboard Freq':'1',  'Keyboard 3 - Send Keyboard Freq':'1',  'Keyboard 4 - Send Keyboard Freq':'1',  'Keyboard 5 - Send Keyboard Freq':'1',  'Keyboard 6 - Piano Keyboard':'0',  'Keyboard 6 - Send Key Status':'1',  'Keyboard 6 - Key 0 - Label':'S0',  'Keyboard 6 - Key 1 - Label':'S1',  'Keyboard 6 - Key 2 - Label':'S2',  'Keyboard 6 - Key 3 - Label':'S3',  'Keyboard 6 - Key 4 - Label':'S4',  'Keyboard 6 - Key 5 - Label':'S5' }");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "acGuitar");
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
	dsp->fHslider1 = (FAUSTFLOAT)164.80000000000001f;
	dsp->fHslider2 = (FAUSTFLOAT)1.0f;
	dsp->fHslider3 = (FAUSTFLOAT)0.0f;
	dsp->fHslider4 = (FAUSTFLOAT)220.0f;
	dsp->fHslider5 = (FAUSTFLOAT)1.0f;
	dsp->fHslider6 = (FAUSTFLOAT)0.0f;
	dsp->fHslider7 = (FAUSTFLOAT)293.69999999999999f;
	dsp->fHslider8 = (FAUSTFLOAT)1.0f;
	dsp->fHslider9 = (FAUSTFLOAT)0.0f;
	dsp->fHslider10 = (FAUSTFLOAT)392.0f;
	dsp->fHslider11 = (FAUSTFLOAT)1.0f;
	dsp->fHslider12 = (FAUSTFLOAT)0.0f;
	dsp->fHslider13 = (FAUSTFLOAT)493.89999999999998f;
	dsp->fHslider14 = (FAUSTFLOAT)1.0f;
	dsp->fHslider15 = (FAUSTFLOAT)0.0f;
	dsp->fHslider16 = (FAUSTFLOAT)659.20000000000005f;
	dsp->fHslider17 = (FAUSTFLOAT)1.0f;
	dsp->fHslider18 = (FAUSTFLOAT)0.0f;
	
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
			dsp->fRec29[l1] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			dsp->fRec30[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			dsp->fRec25[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			dsp->fRec31[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 4); l5 = (l5 + 1)) {
			dsp->fRec33[l5] = 0.0f;
			
		}
		
	}
	dsp->IOTA = 0;
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 2048); l6 = (l6 + 1)) {
			dsp->fRec34[l6] = 0.0f;
			
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
			dsp->iVec1[l8] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			dsp->fVec2[l9] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 2048); l10 = (l10 + 1)) {
			dsp->fRec32[l10] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			dsp->fRec21[l11] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 2048); l12 = (l12 + 1)) {
			dsp->fRec17[l12] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l13;
		for (l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			dsp->fRec19[l13] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l14;
		for (l14 = 0; (l14 < 4); l14 = (l14 + 1)) {
			dsp->fRec15[l14] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l15;
		for (l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			dsp->iRec6[l15] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l16;
		for (l16 = 0; (l16 < 2048); l16 = (l16 + 1)) {
			dsp->fRec2[l16] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l17;
		for (l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			dsp->fRec0[l17] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l18;
		for (l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			dsp->iRec46[l18] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l19;
		for (l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			dsp->fRec65[l19] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l20;
		for (l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			dsp->fRec61[l20] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l21;
		for (l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			dsp->fRec66[l21] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l22;
		for (l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			dsp->iVec3[l22] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l23;
		for (l23 = 0; (l23 < 4); l23 = (l23 + 1)) {
			dsp->fRec68[l23] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l24;
		for (l24 = 0; (l24 < 2048); l24 = (l24 + 1)) {
			dsp->fRec69[l24] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l25;
		for (l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			dsp->fVec4[l25] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l26;
		for (l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			dsp->fVec5[l26] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l27;
		for (l27 = 0; (l27 < 2048); l27 = (l27 + 1)) {
			dsp->fRec67[l27] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l28;
		for (l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			dsp->fRec57[l28] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l29;
		for (l29 = 0; (l29 < 2048); l29 = (l29 + 1)) {
			dsp->fRec53[l29] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l30;
		for (l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			dsp->fRec55[l30] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l31;
		for (l31 = 0; (l31 < 4); l31 = (l31 + 1)) {
			dsp->fRec51[l31] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l32;
		for (l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			dsp->iRec42[l32] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l33;
		for (l33 = 0; (l33 < 2048); l33 = (l33 + 1)) {
			dsp->fRec38[l33] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l34;
		for (l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			dsp->fRec36[l34] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l35;
		for (l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			dsp->iRec81[l35] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l36;
		for (l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			dsp->fRec100[l36] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l37;
		for (l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			dsp->fRec96[l37] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l38;
		for (l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			dsp->fRec101[l38] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l39;
		for (l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			dsp->iVec6[l39] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l40;
		for (l40 = 0; (l40 < 4); l40 = (l40 + 1)) {
			dsp->fRec103[l40] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l41;
		for (l41 = 0; (l41 < 2048); l41 = (l41 + 1)) {
			dsp->fRec104[l41] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l42;
		for (l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			dsp->fVec7[l42] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l43;
		for (l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			dsp->fVec8[l43] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l44;
		for (l44 = 0; (l44 < 2048); l44 = (l44 + 1)) {
			dsp->fRec102[l44] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l45;
		for (l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			dsp->fRec92[l45] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l46;
		for (l46 = 0; (l46 < 2048); l46 = (l46 + 1)) {
			dsp->fRec88[l46] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l47;
		for (l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			dsp->fRec90[l47] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l48;
		for (l48 = 0; (l48 < 4); l48 = (l48 + 1)) {
			dsp->fRec86[l48] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l49;
		for (l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			dsp->iRec77[l49] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l50;
		for (l50 = 0; (l50 < 2048); l50 = (l50 + 1)) {
			dsp->fRec73[l50] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l51;
		for (l51 = 0; (l51 < 2); l51 = (l51 + 1)) {
			dsp->fRec71[l51] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l52;
		for (l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			dsp->iRec116[l52] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l53;
		for (l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			dsp->fRec135[l53] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l54;
		for (l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
			dsp->fRec131[l54] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l55;
		for (l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			dsp->fRec136[l55] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l56;
		for (l56 = 0; (l56 < 2); l56 = (l56 + 1)) {
			dsp->iVec9[l56] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l57;
		for (l57 = 0; (l57 < 4); l57 = (l57 + 1)) {
			dsp->fRec138[l57] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l58;
		for (l58 = 0; (l58 < 2048); l58 = (l58 + 1)) {
			dsp->fRec139[l58] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l59;
		for (l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			dsp->fVec10[l59] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l60;
		for (l60 = 0; (l60 < 2); l60 = (l60 + 1)) {
			dsp->fVec11[l60] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l61;
		for (l61 = 0; (l61 < 2048); l61 = (l61 + 1)) {
			dsp->fRec137[l61] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l62;
		for (l62 = 0; (l62 < 2); l62 = (l62 + 1)) {
			dsp->fRec127[l62] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l63;
		for (l63 = 0; (l63 < 2048); l63 = (l63 + 1)) {
			dsp->fRec123[l63] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l64;
		for (l64 = 0; (l64 < 2); l64 = (l64 + 1)) {
			dsp->fRec125[l64] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l65;
		for (l65 = 0; (l65 < 4); l65 = (l65 + 1)) {
			dsp->fRec121[l65] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l66;
		for (l66 = 0; (l66 < 2); l66 = (l66 + 1)) {
			dsp->iRec112[l66] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l67;
		for (l67 = 0; (l67 < 2048); l67 = (l67 + 1)) {
			dsp->fRec108[l67] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l68;
		for (l68 = 0; (l68 < 2); l68 = (l68 + 1)) {
			dsp->fRec106[l68] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l69;
		for (l69 = 0; (l69 < 2); l69 = (l69 + 1)) {
			dsp->iRec151[l69] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l70;
		for (l70 = 0; (l70 < 2); l70 = (l70 + 1)) {
			dsp->fRec170[l70] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l71;
		for (l71 = 0; (l71 < 2); l71 = (l71 + 1)) {
			dsp->fRec166[l71] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l72;
		for (l72 = 0; (l72 < 2); l72 = (l72 + 1)) {
			dsp->fRec171[l72] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l73;
		for (l73 = 0; (l73 < 2); l73 = (l73 + 1)) {
			dsp->iVec12[l73] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l74;
		for (l74 = 0; (l74 < 4); l74 = (l74 + 1)) {
			dsp->fRec173[l74] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l75;
		for (l75 = 0; (l75 < 2048); l75 = (l75 + 1)) {
			dsp->fRec174[l75] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l76;
		for (l76 = 0; (l76 < 2); l76 = (l76 + 1)) {
			dsp->fVec13[l76] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l77;
		for (l77 = 0; (l77 < 2); l77 = (l77 + 1)) {
			dsp->fVec14[l77] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l78;
		for (l78 = 0; (l78 < 2048); l78 = (l78 + 1)) {
			dsp->fRec172[l78] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l79;
		for (l79 = 0; (l79 < 2); l79 = (l79 + 1)) {
			dsp->fRec162[l79] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l80;
		for (l80 = 0; (l80 < 2048); l80 = (l80 + 1)) {
			dsp->fRec158[l80] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l81;
		for (l81 = 0; (l81 < 2); l81 = (l81 + 1)) {
			dsp->fRec160[l81] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l82;
		for (l82 = 0; (l82 < 4); l82 = (l82 + 1)) {
			dsp->fRec156[l82] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l83;
		for (l83 = 0; (l83 < 2); l83 = (l83 + 1)) {
			dsp->iRec147[l83] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l84;
		for (l84 = 0; (l84 < 2048); l84 = (l84 + 1)) {
			dsp->fRec143[l84] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l85;
		for (l85 = 0; (l85 < 2); l85 = (l85 + 1)) {
			dsp->fRec141[l85] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l86;
		for (l86 = 0; (l86 < 2); l86 = (l86 + 1)) {
			dsp->iRec186[l86] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l87;
		for (l87 = 0; (l87 < 2); l87 = (l87 + 1)) {
			dsp->fRec205[l87] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l88;
		for (l88 = 0; (l88 < 2); l88 = (l88 + 1)) {
			dsp->fRec201[l88] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l89;
		for (l89 = 0; (l89 < 2); l89 = (l89 + 1)) {
			dsp->fRec206[l89] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l90;
		for (l90 = 0; (l90 < 2); l90 = (l90 + 1)) {
			dsp->iVec15[l90] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l91;
		for (l91 = 0; (l91 < 4); l91 = (l91 + 1)) {
			dsp->fRec208[l91] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l92;
		for (l92 = 0; (l92 < 2048); l92 = (l92 + 1)) {
			dsp->fRec209[l92] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l93;
		for (l93 = 0; (l93 < 2); l93 = (l93 + 1)) {
			dsp->fVec16[l93] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l94;
		for (l94 = 0; (l94 < 2); l94 = (l94 + 1)) {
			dsp->fVec17[l94] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l95;
		for (l95 = 0; (l95 < 2048); l95 = (l95 + 1)) {
			dsp->fRec207[l95] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l96;
		for (l96 = 0; (l96 < 2); l96 = (l96 + 1)) {
			dsp->fRec197[l96] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l97;
		for (l97 = 0; (l97 < 2048); l97 = (l97 + 1)) {
			dsp->fRec193[l97] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l98;
		for (l98 = 0; (l98 < 2); l98 = (l98 + 1)) {
			dsp->fRec195[l98] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l99;
		for (l99 = 0; (l99 < 4); l99 = (l99 + 1)) {
			dsp->fRec191[l99] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l100;
		for (l100 = 0; (l100 < 2); l100 = (l100 + 1)) {
			dsp->iRec182[l100] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l101;
		for (l101 = 0; (l101 < 2048); l101 = (l101 + 1)) {
			dsp->fRec178[l101] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l102;
		for (l102 = 0; (l102 < 2); l102 = (l102 + 1)) {
			dsp->fRec176[l102] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = (0.00882352982f * dsp->fConst0);
	dsp->fConst2 = (0.00147058826f * dsp->fConst0);
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "acGuitar");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb0bend", &dsp->fHslider2, 1.0f, 0.0f, 10.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb0freq", &dsp->fHslider1, 164.800003f, 20.0f, 10000.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb1bend", &dsp->fHslider5, 1.0f, 0.0f, 10.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb1freq", &dsp->fHslider4, 220.0f, 20.0f, 10000.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb2bend", &dsp->fHslider8, 1.0f, 0.0f, 10.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb2freq", &dsp->fHslider7, 293.700012f, 20.0f, 10000.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb3bend", &dsp->fHslider11, 1.0f, 0.0f, 10.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb3freq", &dsp->fHslider10, 392.0f, 20.0f, 10000.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb4bend", &dsp->fHslider14, 1.0f, 0.0f, 10.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb4freq", &dsp->fHslider13, 493.899994f, 20.0f, 10000.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb5bend", &dsp->fHslider17, 1.0f, 0.0f, 10.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb5freq", &dsp->fHslider16, 659.200012f, 20.0f, 10000.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb6k0status", &dsp->fHslider3, 0.0f, 0.0f, 1.0f, 1.0f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb6k1status", &dsp->fHslider6, 0.0f, 0.0f, 1.0f, 1.0f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb6k2status", &dsp->fHslider9, 0.0f, 0.0f, 1.0f, 1.0f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb6k3status", &dsp->fHslider12, 0.0f, 0.0f, 1.0f, 1.0f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb6k4status", &dsp->fHslider15, 0.0f, 0.0f, 1.0f, 1.0f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb6k5status", &dsp->fHslider18, 0.0f, 0.0f, 1.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "acc", "1 0 -10 0 10");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "pluckPosition", &dsp->fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	float fSlow0 = (0.00100000005f * (float)dsp->fHslider0);
	float fSlow1 = (0.340000004f / ((float)dsp->fHslider1 * (float)dsp->fHslider2));
	float fSlow2 = (float)dsp->fHslider3;
	int iSlow3 = ((fSlow2 == 1.0f) | (fSlow2 == 4.0f));
	float fSlow4 = (0.340000004f / ((float)dsp->fHslider4 * (float)dsp->fHslider5));
	float fSlow5 = (float)dsp->fHslider6;
	int iSlow6 = ((fSlow5 == 1.0f) | (fSlow5 == 4.0f));
	float fSlow7 = (0.340000004f / ((float)dsp->fHslider7 * (float)dsp->fHslider8));
	float fSlow8 = (float)dsp->fHslider9;
	int iSlow9 = ((fSlow8 == 1.0f) | (fSlow8 == 4.0f));
	float fSlow10 = (0.340000004f / ((float)dsp->fHslider10 * (float)dsp->fHslider11));
	float fSlow11 = (float)dsp->fHslider12;
	int iSlow12 = ((fSlow11 == 1.0f) | (fSlow11 == 4.0f));
	float fSlow13 = (0.340000004f / ((float)dsp->fHslider13 * (float)dsp->fHslider14));
	float fSlow14 = (float)dsp->fHslider15;
	int iSlow15 = ((fSlow14 == 1.0f) | (fSlow14 == 4.0f));
	float fSlow16 = (0.340000004f / ((float)dsp->fHslider16 * (float)dsp->fHslider17));
	float fSlow17 = (float)dsp->fHslider18;
	int iSlow18 = ((fSlow17 == 1.0f) | (fSlow17 == 4.0f));
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->iRec10[0] = 0;
			int iRec11 = dsp->iRec10[1];
			float fRec14 = ((float)dsp->iRec6[1] - (0.997843683f * ((0.699999988f * dsp->fRec15[2]) + (0.150000006f * (dsp->fRec15[1] + dsp->fRec15[3])))));
			dsp->fRec29[0] = (fSlow0 + (0.999000013f * dsp->fRec29[1]));
			float fTemp0 = (1.0f - dsp->fRec29[0]);
			dsp->fRec30[0] = (fSlow1 + (0.999000013f * dsp->fRec30[1]));
			float fTemp1 = (dsp->fRec30[0] + -0.109999999f);
			float fTemp2 = (dsp->fConst2 * (fTemp0 * fTemp1));
			float fTemp3 = (fTemp2 + -1.49999499f);
			int iTemp4 = (int)fTemp3;
			int iTemp5 = (int)min(dsp->fConst1, (float)max(0, iTemp4));
			float fTemp6 = floorf(fTemp3);
			float fTemp7 = (fTemp2 + (-1.0f - fTemp6));
			float fTemp8 = (0.0f - fTemp7);
			float fTemp9 = (fTemp2 + (-2.0f - fTemp6));
			float fTemp10 = (0.0f - (0.5f * fTemp9));
			float fTemp11 = (fTemp2 + (-3.0f - fTemp6));
			float fTemp12 = (0.0f - (0.333333343f * fTemp11));
			float fTemp13 = (fTemp2 + (-4.0f - fTemp6));
			float fTemp14 = (0.0f - (0.25f * fTemp13));
			float fTemp15 = (fTemp2 - fTemp6);
			int iTemp16 = (int)min(dsp->fConst1, (float)max(0, (iTemp4 + 2)));
			float fTemp17 = (0.0f - fTemp11);
			float fTemp18 = (0.0f - (0.5f * fTemp13));
			int iTemp19 = (int)min(dsp->fConst1, (float)max(0, (iTemp4 + 1)));
			float fTemp20 = (0.0f - fTemp9);
			float fTemp21 = (0.0f - (0.5f * fTemp11));
			float fTemp22 = (0.0f - (0.333333343f * fTemp13));
			float fTemp23 = (fTemp7 * fTemp9);
			int iTemp24 = (int)min(dsp->fConst1, (float)max(0, (iTemp4 + 3)));
			float fTemp25 = (0.0f - fTemp13);
			float fTemp26 = (fTemp23 * fTemp11);
			int iTemp27 = (int)min(dsp->fConst1, (float)max(0, (iTemp4 + 4)));
			dsp->fRec25[0] = (((((dsp->fRec2[((dsp->IOTA - (iTemp5 + 1)) & 2047)] * fTemp8) * fTemp10) * fTemp12) * fTemp14) + (fTemp15 * ((((0.5f * (((fTemp7 * dsp->fRec2[((dsp->IOTA - (iTemp16 + 1)) & 2047)]) * fTemp17) * fTemp18)) + (((dsp->fRec2[((dsp->IOTA - (iTemp19 + 1)) & 2047)] * fTemp20) * fTemp21) * fTemp22)) + (0.166666672f * ((fTemp23 * dsp->fRec2[((dsp->IOTA - (iTemp24 + 1)) & 2047)]) * fTemp25))) + (0.0416666679f * (fTemp26 * dsp->fRec2[((dsp->IOTA - (iTemp27 + 1)) & 2047)])))));
			dsp->fRec31[0] = ((0.400000006f * dsp->fRec31[1]) + (0.600000024f * dsp->fRec25[1]));
			float fRec26 = dsp->fRec31[0];
			dsp->fRec33[0] = dsp->fRec0[1];
			dsp->fRec34[(dsp->IOTA & 2047)] = (0.0f - (0.997843683f * ((0.699999988f * dsp->fRec33[2]) + (0.150000006f * (dsp->fRec33[1] + dsp->fRec33[3])))));
			int iRec35 = 0;
			float fTemp28 = (dsp->fConst2 * (dsp->fRec29[0] * fTemp1));
			float fTemp29 = (fTemp28 + -1.49999499f);
			int iTemp30 = (int)fTemp29;
			int iTemp31 = (int)min(dsp->fConst1, (float)max(0, iTemp30));
			float fTemp32 = floorf(fTemp29);
			float fTemp33 = (fTemp28 + (-1.0f - fTemp32));
			float fTemp34 = (0.0f - fTemp33);
			float fTemp35 = (fTemp28 + (-2.0f - fTemp32));
			float fTemp36 = (0.0f - (0.5f * fTemp35));
			float fTemp37 = (fTemp28 + (-3.0f - fTemp32));
			float fTemp38 = (0.0f - (0.333333343f * fTemp37));
			float fTemp39 = (fTemp28 + (-4.0f - fTemp32));
			float fTemp40 = (0.0f - (0.25f * fTemp39));
			float fTemp41 = (fTemp28 - fTemp32);
			int iTemp42 = (int)min(dsp->fConst1, (float)max(0, (iTemp30 + 2)));
			float fTemp43 = (0.0f - fTemp37);
			float fTemp44 = (0.0f - (0.5f * fTemp39));
			int iTemp45 = (int)min(dsp->fConst1, (float)max(0, (iTemp30 + 1)));
			float fTemp46 = (0.0f - fTemp35);
			float fTemp47 = (0.0f - (0.5f * fTemp37));
			float fTemp48 = (0.0f - (0.333333343f * fTemp39));
			float fTemp49 = (fTemp33 * fTemp35);
			int iTemp50 = (int)min(dsp->fConst1, (float)max(0, (iTemp30 + 3)));
			float fTemp51 = (0.0f - fTemp39);
			float fTemp52 = (fTemp49 * fTemp37);
			int iTemp53 = (int)min(dsp->fConst1, (float)max(0, (iTemp30 + 4)));
			dsp->fVec0[0] = (((((dsp->fRec34[((dsp->IOTA - (iTemp31 + 2)) & 2047)] * fTemp34) * fTemp36) * fTemp38) * fTemp40) + (fTemp41 * ((((0.5f * (((fTemp33 * dsp->fRec34[((dsp->IOTA - (iTemp42 + 2)) & 2047)]) * fTemp43) * fTemp44)) + (((dsp->fRec34[((dsp->IOTA - (iTemp45 + 2)) & 2047)] * fTemp46) * fTemp47) * fTemp48)) + (0.166666672f * ((fTemp49 * dsp->fRec34[((dsp->IOTA - (iTemp50 + 2)) & 2047)]) * fTemp51))) + (0.0416666679f * (fTemp52 * dsp->fRec34[((dsp->IOTA - (iTemp53 + 2)) & 2047)])))));
			dsp->iVec1[0] = iSlow3;
			int iTemp54 = ((iSlow3 - dsp->iVec1[1]) > 0);
			dsp->fVec2[0] = (dsp->fVec0[1] + (float)iTemp54);
			dsp->fRec32[(dsp->IOTA & 2047)] = ((0.400000006f * dsp->fRec32[((dsp->IOTA - 1) & 2047)]) + (0.600000024f * dsp->fVec2[1]));
			float fRec27 = (((((fTemp8 * fTemp10) * fTemp12) * fTemp14) * dsp->fRec32[((dsp->IOTA - iTemp5) & 2047)]) + (fTemp15 * ((0.0416666679f * (fTemp26 * dsp->fRec32[((dsp->IOTA - iTemp27) & 2047)])) + (((((fTemp20 * fTemp21) * fTemp22) * dsp->fRec32[((dsp->IOTA - iTemp19) & 2047)]) + (0.5f * (((fTemp7 * fTemp17) * fTemp18) * dsp->fRec32[((dsp->IOTA - iTemp16) & 2047)]))) + (0.166666672f * ((fTemp23 * fTemp25) * dsp->fRec32[((dsp->IOTA - iTemp24) & 2047)]))))));
			int iRec28 = iRec35;
			dsp->fRec21[0] = fRec26;
			float fRec22 = ((float)iTemp54 + dsp->fRec21[1]);
			float fRec23 = fRec27;
			int iRec24 = iRec28;
			dsp->fRec17[(dsp->IOTA & 2047)] = fRec22;
			float fRec18 = (((((fTemp34 * fTemp36) * fTemp38) * fTemp40) * dsp->fRec17[((dsp->IOTA - (iTemp31 + 1)) & 2047)]) + (fTemp41 * (((0.166666672f * ((fTemp49 * fTemp51) * dsp->fRec17[((dsp->IOTA - (iTemp50 + 1)) & 2047)])) + ((((fTemp46 * fTemp47) * fTemp48) * dsp->fRec17[((dsp->IOTA - (iTemp45 + 1)) & 2047)]) + (0.5f * (((fTemp33 * fTemp43) * fTemp44) * dsp->fRec17[((dsp->IOTA - (iTemp42 + 1)) & 2047)])))) + (0.0416666679f * (fTemp52 * dsp->fRec17[((dsp->IOTA - (iTemp53 + 1)) & 2047)])))));
			dsp->fRec19[0] = fRec23;
			int iRec20 = iRec24;
			dsp->fRec15[0] = dsp->fRec19[1];
			int iRec16 = iRec20;
			float fRec12 = dsp->fRec15[1];
			float fRec13 = ((float)iRec16 + dsp->fRec15[1]);
			dsp->iRec6[0] = iRec11;
			float fRec7 = fRec14;
			float fRec8 = fRec12;
			float fRec9 = fRec13;
			dsp->fRec2[(dsp->IOTA & 2047)] = fRec7;
			float fRec3 = fRec18;
			float fRec4 = fRec8;
			float fRec5 = fRec9;
			dsp->fRec0[0] = fRec3;
			float fRec1 = fRec5;
			dsp->iRec46[0] = 0;
			int iRec47 = dsp->iRec46[1];
			float fRec50 = ((float)dsp->iRec42[1] - (0.997843683f * ((0.699999988f * dsp->fRec51[2]) + (0.150000006f * (dsp->fRec51[1] + dsp->fRec51[3])))));
			dsp->fRec65[0] = (fSlow4 + (0.999000013f * dsp->fRec65[1]));
			float fTemp55 = (dsp->fRec65[0] + -0.109999999f);
			float fTemp56 = (dsp->fConst2 * (fTemp0 * fTemp55));
			float fTemp57 = (fTemp56 + -1.49999499f);
			int iTemp58 = (int)fTemp57;
			int iTemp59 = (int)min(dsp->fConst1, (float)max(0, iTemp58));
			float fTemp60 = floorf(fTemp57);
			float fTemp61 = (fTemp56 + (-1.0f - fTemp60));
			float fTemp62 = (0.0f - fTemp61);
			float fTemp63 = (fTemp56 + (-2.0f - fTemp60));
			float fTemp64 = (0.0f - (0.5f * fTemp63));
			float fTemp65 = (fTemp56 + (-3.0f - fTemp60));
			float fTemp66 = (0.0f - (0.333333343f * fTemp65));
			float fTemp67 = (fTemp56 + (-4.0f - fTemp60));
			float fTemp68 = (0.0f - (0.25f * fTemp67));
			float fTemp69 = (fTemp56 - fTemp60);
			int iTemp70 = (int)min(dsp->fConst1, (float)max(0, (iTemp58 + 2)));
			float fTemp71 = (0.0f - fTemp65);
			float fTemp72 = (0.0f - (0.5f * fTemp67));
			int iTemp73 = (int)min(dsp->fConst1, (float)max(0, (iTemp58 + 1)));
			float fTemp74 = (0.0f - fTemp63);
			float fTemp75 = (0.0f - (0.5f * fTemp65));
			float fTemp76 = (0.0f - (0.333333343f * fTemp67));
			float fTemp77 = (fTemp61 * fTemp63);
			int iTemp78 = (int)min(dsp->fConst1, (float)max(0, (iTemp58 + 3)));
			float fTemp79 = (0.0f - fTemp67);
			float fTemp80 = (fTemp77 * fTemp65);
			int iTemp81 = (int)min(dsp->fConst1, (float)max(0, (iTemp58 + 4)));
			dsp->fRec61[0] = (((((dsp->fRec38[((dsp->IOTA - (iTemp59 + 1)) & 2047)] * fTemp62) * fTemp64) * fTemp66) * fTemp68) + (fTemp69 * ((((0.5f * (((fTemp61 * dsp->fRec38[((dsp->IOTA - (iTemp70 + 1)) & 2047)]) * fTemp71) * fTemp72)) + (((dsp->fRec38[((dsp->IOTA - (iTemp73 + 1)) & 2047)] * fTemp74) * fTemp75) * fTemp76)) + (0.166666672f * ((fTemp77 * dsp->fRec38[((dsp->IOTA - (iTemp78 + 1)) & 2047)]) * fTemp79))) + (0.0416666679f * (fTemp80 * dsp->fRec38[((dsp->IOTA - (iTemp81 + 1)) & 2047)])))));
			dsp->fRec66[0] = ((0.600000024f * dsp->fRec61[1]) + (0.400000006f * dsp->fRec66[1]));
			float fRec62 = dsp->fRec66[0];
			dsp->iVec3[0] = iSlow6;
			int iTemp82 = ((iSlow6 - dsp->iVec3[1]) > 0);
			dsp->fRec68[0] = dsp->fRec36[1];
			dsp->fRec69[(dsp->IOTA & 2047)] = (0.0f - (0.997843683f * ((0.699999988f * dsp->fRec68[2]) + (0.150000006f * (dsp->fRec68[1] + dsp->fRec68[3])))));
			int iRec70 = 0;
			float fTemp83 = (dsp->fConst2 * (dsp->fRec29[0] * fTemp55));
			float fTemp84 = (fTemp83 + -1.49999499f);
			int iTemp85 = (int)fTemp84;
			int iTemp86 = (int)min(dsp->fConst1, (float)max(0, iTemp85));
			float fTemp87 = floorf(fTemp84);
			float fTemp88 = (fTemp83 + (-1.0f - fTemp87));
			float fTemp89 = (0.0f - fTemp88);
			float fTemp90 = (fTemp83 + (-2.0f - fTemp87));
			float fTemp91 = (0.0f - (0.5f * fTemp90));
			float fTemp92 = (fTemp83 + (-3.0f - fTemp87));
			float fTemp93 = (0.0f - (0.333333343f * fTemp92));
			float fTemp94 = (fTemp83 + (-4.0f - fTemp87));
			float fTemp95 = (0.0f - (0.25f * fTemp94));
			float fTemp96 = (fTemp83 - fTemp87);
			int iTemp97 = (int)min(dsp->fConst1, (float)max(0, (iTemp85 + 2)));
			float fTemp98 = (0.0f - fTemp92);
			float fTemp99 = (0.0f - (0.5f * fTemp94));
			int iTemp100 = (int)min(dsp->fConst1, (float)max(0, (iTemp85 + 1)));
			float fTemp101 = (0.0f - fTemp90);
			float fTemp102 = (0.0f - (0.5f * fTemp92));
			float fTemp103 = (0.0f - (0.333333343f * fTemp94));
			float fTemp104 = (fTemp88 * fTemp90);
			int iTemp105 = (int)min(dsp->fConst1, (float)max(0, (iTemp85 + 3)));
			float fTemp106 = (0.0f - fTemp94);
			float fTemp107 = (fTemp104 * fTemp92);
			int iTemp108 = (int)min(dsp->fConst1, (float)max(0, (iTemp85 + 4)));
			dsp->fVec4[0] = (((((dsp->fRec69[((dsp->IOTA - (iTemp86 + 2)) & 2047)] * fTemp89) * fTemp91) * fTemp93) * fTemp95) + (fTemp96 * ((((0.5f * (((fTemp88 * dsp->fRec69[((dsp->IOTA - (iTemp97 + 2)) & 2047)]) * fTemp98) * fTemp99)) + (((dsp->fRec69[((dsp->IOTA - (iTemp100 + 2)) & 2047)] * fTemp101) * fTemp102) * fTemp103)) + (0.166666672f * ((fTemp104 * dsp->fRec69[((dsp->IOTA - (iTemp105 + 2)) & 2047)]) * fTemp106))) + (0.0416666679f * (fTemp107 * dsp->fRec69[((dsp->IOTA - (iTemp108 + 2)) & 2047)])))));
			dsp->fVec5[0] = ((float)iTemp82 + dsp->fVec4[1]);
			dsp->fRec67[(dsp->IOTA & 2047)] = ((0.400000006f * dsp->fRec67[((dsp->IOTA - 1) & 2047)]) + (0.600000024f * dsp->fVec5[1]));
			float fRec63 = (((((fTemp62 * fTemp64) * fTemp66) * fTemp68) * dsp->fRec67[((dsp->IOTA - iTemp59) & 2047)]) + (fTemp69 * ((0.0416666679f * (fTemp80 * dsp->fRec67[((dsp->IOTA - iTemp81) & 2047)])) + (((((fTemp74 * fTemp75) * fTemp76) * dsp->fRec67[((dsp->IOTA - iTemp73) & 2047)]) + (0.5f * (((fTemp61 * fTemp71) * fTemp72) * dsp->fRec67[((dsp->IOTA - iTemp70) & 2047)]))) + (0.166666672f * ((fTemp77 * fTemp79) * dsp->fRec67[((dsp->IOTA - iTemp78) & 2047)]))))));
			int iRec64 = iRec70;
			dsp->fRec57[0] = fRec62;
			float fRec58 = ((float)iTemp82 + dsp->fRec57[1]);
			float fRec59 = fRec63;
			int iRec60 = iRec64;
			dsp->fRec53[(dsp->IOTA & 2047)] = fRec58;
			float fRec54 = (((((fTemp89 * fTemp91) * fTemp93) * fTemp95) * dsp->fRec53[((dsp->IOTA - (iTemp86 + 1)) & 2047)]) + (fTemp96 * (((0.166666672f * ((fTemp104 * fTemp106) * dsp->fRec53[((dsp->IOTA - (iTemp105 + 1)) & 2047)])) + ((((fTemp101 * fTemp102) * fTemp103) * dsp->fRec53[((dsp->IOTA - (iTemp100 + 1)) & 2047)]) + (0.5f * (((fTemp88 * fTemp98) * fTemp99) * dsp->fRec53[((dsp->IOTA - (iTemp97 + 1)) & 2047)])))) + (0.0416666679f * (fTemp107 * dsp->fRec53[((dsp->IOTA - (iTemp108 + 1)) & 2047)])))));
			dsp->fRec55[0] = fRec59;
			int iRec56 = iRec60;
			dsp->fRec51[0] = dsp->fRec55[1];
			int iRec52 = iRec56;
			float fRec48 = dsp->fRec51[1];
			float fRec49 = ((float)iRec52 + dsp->fRec51[1]);
			dsp->iRec42[0] = iRec47;
			float fRec43 = fRec50;
			float fRec44 = fRec48;
			float fRec45 = fRec49;
			dsp->fRec38[(dsp->IOTA & 2047)] = fRec43;
			float fRec39 = fRec54;
			float fRec40 = fRec44;
			float fRec41 = fRec45;
			dsp->fRec36[0] = fRec39;
			float fRec37 = fRec41;
			dsp->iRec81[0] = 0;
			int iRec82 = dsp->iRec81[1];
			float fRec85 = ((float)dsp->iRec77[1] - (0.997843683f * ((0.699999988f * dsp->fRec86[2]) + (0.150000006f * (dsp->fRec86[1] + dsp->fRec86[3])))));
			dsp->fRec100[0] = (fSlow7 + (0.999000013f * dsp->fRec100[1]));
			float fTemp109 = (dsp->fRec100[0] + -0.109999999f);
			float fTemp110 = (dsp->fConst2 * (fTemp0 * fTemp109));
			float fTemp111 = (fTemp110 + -1.49999499f);
			int iTemp112 = (int)fTemp111;
			int iTemp113 = (int)min(dsp->fConst1, (float)max(0, iTemp112));
			float fTemp114 = floorf(fTemp111);
			float fTemp115 = (fTemp110 + (-1.0f - fTemp114));
			float fTemp116 = (0.0f - fTemp115);
			float fTemp117 = (fTemp110 + (-2.0f - fTemp114));
			float fTemp118 = (0.0f - (0.5f * fTemp117));
			float fTemp119 = (fTemp110 + (-3.0f - fTemp114));
			float fTemp120 = (0.0f - (0.333333343f * fTemp119));
			float fTemp121 = (fTemp110 + (-4.0f - fTemp114));
			float fTemp122 = (0.0f - (0.25f * fTemp121));
			float fTemp123 = (fTemp110 - fTemp114);
			int iTemp124 = (int)min(dsp->fConst1, (float)max(0, (iTemp112 + 2)));
			float fTemp125 = (0.0f - fTemp119);
			float fTemp126 = (0.0f - (0.5f * fTemp121));
			int iTemp127 = (int)min(dsp->fConst1, (float)max(0, (iTemp112 + 1)));
			float fTemp128 = (0.0f - fTemp117);
			float fTemp129 = (0.0f - (0.5f * fTemp119));
			float fTemp130 = (0.0f - (0.333333343f * fTemp121));
			float fTemp131 = (fTemp115 * fTemp117);
			int iTemp132 = (int)min(dsp->fConst1, (float)max(0, (iTemp112 + 3)));
			float fTemp133 = (0.0f - fTemp121);
			float fTemp134 = (fTemp131 * fTemp119);
			int iTemp135 = (int)min(dsp->fConst1, (float)max(0, (iTemp112 + 4)));
			dsp->fRec96[0] = (((((dsp->fRec73[((dsp->IOTA - (iTemp113 + 1)) & 2047)] * fTemp116) * fTemp118) * fTemp120) * fTemp122) + (fTemp123 * ((((0.5f * (((fTemp115 * dsp->fRec73[((dsp->IOTA - (iTemp124 + 1)) & 2047)]) * fTemp125) * fTemp126)) + (((dsp->fRec73[((dsp->IOTA - (iTemp127 + 1)) & 2047)] * fTemp128) * fTemp129) * fTemp130)) + (0.166666672f * ((fTemp131 * dsp->fRec73[((dsp->IOTA - (iTemp132 + 1)) & 2047)]) * fTemp133))) + (0.0416666679f * (fTemp134 * dsp->fRec73[((dsp->IOTA - (iTemp135 + 1)) & 2047)])))));
			dsp->fRec101[0] = ((0.600000024f * dsp->fRec96[1]) + (0.400000006f * dsp->fRec101[1]));
			float fRec97 = dsp->fRec101[0];
			dsp->iVec6[0] = iSlow9;
			int iTemp136 = ((iSlow9 - dsp->iVec6[1]) > 0);
			dsp->fRec103[0] = dsp->fRec71[1];
			dsp->fRec104[(dsp->IOTA & 2047)] = (0.0f - (0.997843683f * ((0.699999988f * dsp->fRec103[2]) + (0.150000006f * (dsp->fRec103[1] + dsp->fRec103[3])))));
			int iRec105 = 0;
			float fTemp137 = (dsp->fConst2 * (dsp->fRec29[0] * fTemp109));
			float fTemp138 = (fTemp137 + -1.49999499f);
			int iTemp139 = (int)fTemp138;
			int iTemp140 = (int)min(dsp->fConst1, (float)max(0, iTemp139));
			float fTemp141 = floorf(fTemp138);
			float fTemp142 = (fTemp137 + (-1.0f - fTemp141));
			float fTemp143 = (0.0f - fTemp142);
			float fTemp144 = (fTemp137 + (-2.0f - fTemp141));
			float fTemp145 = (0.0f - (0.5f * fTemp144));
			float fTemp146 = (fTemp137 + (-3.0f - fTemp141));
			float fTemp147 = (0.0f - (0.333333343f * fTemp146));
			float fTemp148 = (fTemp137 + (-4.0f - fTemp141));
			float fTemp149 = (0.0f - (0.25f * fTemp148));
			float fTemp150 = (fTemp137 - fTemp141);
			int iTemp151 = (int)min(dsp->fConst1, (float)max(0, (iTemp139 + 2)));
			float fTemp152 = (0.0f - fTemp146);
			float fTemp153 = (0.0f - (0.5f * fTemp148));
			int iTemp154 = (int)min(dsp->fConst1, (float)max(0, (iTemp139 + 1)));
			float fTemp155 = (0.0f - fTemp144);
			float fTemp156 = (0.0f - (0.5f * fTemp146));
			float fTemp157 = (0.0f - (0.333333343f * fTemp148));
			float fTemp158 = (fTemp142 * fTemp144);
			int iTemp159 = (int)min(dsp->fConst1, (float)max(0, (iTemp139 + 3)));
			float fTemp160 = (0.0f - fTemp148);
			float fTemp161 = (fTemp158 * fTemp146);
			int iTemp162 = (int)min(dsp->fConst1, (float)max(0, (iTemp139 + 4)));
			dsp->fVec7[0] = (((((dsp->fRec104[((dsp->IOTA - (iTemp140 + 2)) & 2047)] * fTemp143) * fTemp145) * fTemp147) * fTemp149) + (fTemp150 * ((((0.5f * (((fTemp142 * dsp->fRec104[((dsp->IOTA - (iTemp151 + 2)) & 2047)]) * fTemp152) * fTemp153)) + (((dsp->fRec104[((dsp->IOTA - (iTemp154 + 2)) & 2047)] * fTemp155) * fTemp156) * fTemp157)) + (0.166666672f * ((fTemp158 * dsp->fRec104[((dsp->IOTA - (iTemp159 + 2)) & 2047)]) * fTemp160))) + (0.0416666679f * (fTemp161 * dsp->fRec104[((dsp->IOTA - (iTemp162 + 2)) & 2047)])))));
			dsp->fVec8[0] = ((float)iTemp136 + dsp->fVec7[1]);
			dsp->fRec102[(dsp->IOTA & 2047)] = ((0.400000006f * dsp->fRec102[((dsp->IOTA - 1) & 2047)]) + (0.600000024f * dsp->fVec8[1]));
			float fRec98 = (((((fTemp116 * fTemp118) * fTemp120) * fTemp122) * dsp->fRec102[((dsp->IOTA - iTemp113) & 2047)]) + (fTemp123 * ((0.0416666679f * (fTemp134 * dsp->fRec102[((dsp->IOTA - iTemp135) & 2047)])) + (((((fTemp128 * fTemp129) * fTemp130) * dsp->fRec102[((dsp->IOTA - iTemp127) & 2047)]) + (0.5f * (((fTemp115 * fTemp125) * fTemp126) * dsp->fRec102[((dsp->IOTA - iTemp124) & 2047)]))) + (0.166666672f * ((fTemp131 * fTemp133) * dsp->fRec102[((dsp->IOTA - iTemp132) & 2047)]))))));
			int iRec99 = iRec105;
			dsp->fRec92[0] = fRec97;
			float fRec93 = ((float)iTemp136 + dsp->fRec92[1]);
			float fRec94 = fRec98;
			int iRec95 = iRec99;
			dsp->fRec88[(dsp->IOTA & 2047)] = fRec93;
			float fRec89 = (((((fTemp143 * fTemp145) * fTemp147) * fTemp149) * dsp->fRec88[((dsp->IOTA - (iTemp140 + 1)) & 2047)]) + (fTemp150 * (((0.166666672f * ((fTemp158 * fTemp160) * dsp->fRec88[((dsp->IOTA - (iTemp159 + 1)) & 2047)])) + ((((fTemp155 * fTemp156) * fTemp157) * dsp->fRec88[((dsp->IOTA - (iTemp154 + 1)) & 2047)]) + (0.5f * (((fTemp142 * fTemp152) * fTemp153) * dsp->fRec88[((dsp->IOTA - (iTemp151 + 1)) & 2047)])))) + (0.0416666679f * (fTemp161 * dsp->fRec88[((dsp->IOTA - (iTemp162 + 1)) & 2047)])))));
			dsp->fRec90[0] = fRec94;
			int iRec91 = iRec95;
			dsp->fRec86[0] = dsp->fRec90[1];
			int iRec87 = iRec91;
			float fRec83 = dsp->fRec86[1];
			float fRec84 = ((float)iRec87 + dsp->fRec86[1]);
			dsp->iRec77[0] = iRec82;
			float fRec78 = fRec85;
			float fRec79 = fRec83;
			float fRec80 = fRec84;
			dsp->fRec73[(dsp->IOTA & 2047)] = fRec78;
			float fRec74 = fRec89;
			float fRec75 = fRec79;
			float fRec76 = fRec80;
			dsp->fRec71[0] = fRec74;
			float fRec72 = fRec76;
			dsp->iRec116[0] = 0;
			int iRec117 = dsp->iRec116[1];
			float fRec120 = ((float)dsp->iRec112[1] - (0.997843683f * ((0.699999988f * dsp->fRec121[2]) + (0.150000006f * (dsp->fRec121[1] + dsp->fRec121[3])))));
			dsp->fRec135[0] = (fSlow10 + (0.999000013f * dsp->fRec135[1]));
			float fTemp163 = (dsp->fRec135[0] + -0.109999999f);
			float fTemp164 = (dsp->fConst2 * (fTemp0 * fTemp163));
			float fTemp165 = (fTemp164 + -1.49999499f);
			int iTemp166 = (int)fTemp165;
			int iTemp167 = (int)min(dsp->fConst1, (float)max(0, iTemp166));
			float fTemp168 = floorf(fTemp165);
			float fTemp169 = (fTemp164 + (-1.0f - fTemp168));
			float fTemp170 = (0.0f - fTemp169);
			float fTemp171 = (fTemp164 + (-2.0f - fTemp168));
			float fTemp172 = (0.0f - (0.5f * fTemp171));
			float fTemp173 = (fTemp164 + (-3.0f - fTemp168));
			float fTemp174 = (0.0f - (0.333333343f * fTemp173));
			float fTemp175 = (fTemp164 + (-4.0f - fTemp168));
			float fTemp176 = (0.0f - (0.25f * fTemp175));
			float fTemp177 = (fTemp164 - fTemp168);
			int iTemp178 = (int)min(dsp->fConst1, (float)max(0, (iTemp166 + 2)));
			float fTemp179 = (0.0f - fTemp173);
			float fTemp180 = (0.0f - (0.5f * fTemp175));
			int iTemp181 = (int)min(dsp->fConst1, (float)max(0, (iTemp166 + 1)));
			float fTemp182 = (0.0f - fTemp171);
			float fTemp183 = (0.0f - (0.5f * fTemp173));
			float fTemp184 = (0.0f - (0.333333343f * fTemp175));
			float fTemp185 = (fTemp169 * fTemp171);
			int iTemp186 = (int)min(dsp->fConst1, (float)max(0, (iTemp166 + 3)));
			float fTemp187 = (0.0f - fTemp175);
			float fTemp188 = (fTemp185 * fTemp173);
			int iTemp189 = (int)min(dsp->fConst1, (float)max(0, (iTemp166 + 4)));
			dsp->fRec131[0] = (((((dsp->fRec108[((dsp->IOTA - (iTemp167 + 1)) & 2047)] * fTemp170) * fTemp172) * fTemp174) * fTemp176) + (fTemp177 * ((((0.5f * (((fTemp169 * dsp->fRec108[((dsp->IOTA - (iTemp178 + 1)) & 2047)]) * fTemp179) * fTemp180)) + (((dsp->fRec108[((dsp->IOTA - (iTemp181 + 1)) & 2047)] * fTemp182) * fTemp183) * fTemp184)) + (0.166666672f * ((fTemp185 * dsp->fRec108[((dsp->IOTA - (iTemp186 + 1)) & 2047)]) * fTemp187))) + (0.0416666679f * (fTemp188 * dsp->fRec108[((dsp->IOTA - (iTemp189 + 1)) & 2047)])))));
			dsp->fRec136[0] = ((0.600000024f * dsp->fRec131[1]) + (0.400000006f * dsp->fRec136[1]));
			float fRec132 = dsp->fRec136[0];
			dsp->iVec9[0] = iSlow12;
			int iTemp190 = ((iSlow12 - dsp->iVec9[1]) > 0);
			dsp->fRec138[0] = dsp->fRec106[1];
			dsp->fRec139[(dsp->IOTA & 2047)] = (0.0f - (0.997843683f * ((0.699999988f * dsp->fRec138[2]) + (0.150000006f * (dsp->fRec138[1] + dsp->fRec138[3])))));
			int iRec140 = 0;
			float fTemp191 = (dsp->fConst2 * (dsp->fRec29[0] * fTemp163));
			float fTemp192 = (fTemp191 + -1.49999499f);
			int iTemp193 = (int)fTemp192;
			int iTemp194 = (int)min(dsp->fConst1, (float)max(0, iTemp193));
			float fTemp195 = floorf(fTemp192);
			float fTemp196 = (fTemp191 + (-1.0f - fTemp195));
			float fTemp197 = (0.0f - fTemp196);
			float fTemp198 = (fTemp191 + (-2.0f - fTemp195));
			float fTemp199 = (0.0f - (0.5f * fTemp198));
			float fTemp200 = (fTemp191 + (-3.0f - fTemp195));
			float fTemp201 = (0.0f - (0.333333343f * fTemp200));
			float fTemp202 = (fTemp191 + (-4.0f - fTemp195));
			float fTemp203 = (0.0f - (0.25f * fTemp202));
			float fTemp204 = (fTemp191 - fTemp195);
			int iTemp205 = (int)min(dsp->fConst1, (float)max(0, (iTemp193 + 2)));
			float fTemp206 = (0.0f - fTemp200);
			float fTemp207 = (0.0f - (0.5f * fTemp202));
			int iTemp208 = (int)min(dsp->fConst1, (float)max(0, (iTemp193 + 1)));
			float fTemp209 = (0.0f - fTemp198);
			float fTemp210 = (0.0f - (0.5f * fTemp200));
			float fTemp211 = (0.0f - (0.333333343f * fTemp202));
			float fTemp212 = (fTemp196 * fTemp198);
			int iTemp213 = (int)min(dsp->fConst1, (float)max(0, (iTemp193 + 3)));
			float fTemp214 = (0.0f - fTemp202);
			float fTemp215 = (fTemp212 * fTemp200);
			int iTemp216 = (int)min(dsp->fConst1, (float)max(0, (iTemp193 + 4)));
			dsp->fVec10[0] = (((((dsp->fRec139[((dsp->IOTA - (iTemp194 + 2)) & 2047)] * fTemp197) * fTemp199) * fTemp201) * fTemp203) + (fTemp204 * ((((0.5f * (((fTemp196 * dsp->fRec139[((dsp->IOTA - (iTemp205 + 2)) & 2047)]) * fTemp206) * fTemp207)) + (((dsp->fRec139[((dsp->IOTA - (iTemp208 + 2)) & 2047)] * fTemp209) * fTemp210) * fTemp211)) + (0.166666672f * ((fTemp212 * dsp->fRec139[((dsp->IOTA - (iTemp213 + 2)) & 2047)]) * fTemp214))) + (0.0416666679f * (fTemp215 * dsp->fRec139[((dsp->IOTA - (iTemp216 + 2)) & 2047)])))));
			dsp->fVec11[0] = ((float)iTemp190 + dsp->fVec10[1]);
			dsp->fRec137[(dsp->IOTA & 2047)] = ((0.400000006f * dsp->fRec137[((dsp->IOTA - 1) & 2047)]) + (0.600000024f * dsp->fVec11[1]));
			float fRec133 = (((((fTemp170 * fTemp172) * fTemp174) * fTemp176) * dsp->fRec137[((dsp->IOTA - iTemp167) & 2047)]) + (fTemp177 * ((0.0416666679f * (fTemp188 * dsp->fRec137[((dsp->IOTA - iTemp189) & 2047)])) + (((((fTemp182 * fTemp183) * fTemp184) * dsp->fRec137[((dsp->IOTA - iTemp181) & 2047)]) + (0.5f * (((fTemp169 * fTemp179) * fTemp180) * dsp->fRec137[((dsp->IOTA - iTemp178) & 2047)]))) + (0.166666672f * ((fTemp185 * fTemp187) * dsp->fRec137[((dsp->IOTA - iTemp186) & 2047)]))))));
			int iRec134 = iRec140;
			dsp->fRec127[0] = fRec132;
			float fRec128 = ((float)iTemp190 + dsp->fRec127[1]);
			float fRec129 = fRec133;
			int iRec130 = iRec134;
			dsp->fRec123[(dsp->IOTA & 2047)] = fRec128;
			float fRec124 = (((((fTemp197 * fTemp199) * fTemp201) * fTemp203) * dsp->fRec123[((dsp->IOTA - (iTemp194 + 1)) & 2047)]) + (fTemp204 * (((0.166666672f * ((fTemp212 * fTemp214) * dsp->fRec123[((dsp->IOTA - (iTemp213 + 1)) & 2047)])) + ((((fTemp209 * fTemp210) * fTemp211) * dsp->fRec123[((dsp->IOTA - (iTemp208 + 1)) & 2047)]) + (0.5f * (((fTemp196 * fTemp206) * fTemp207) * dsp->fRec123[((dsp->IOTA - (iTemp205 + 1)) & 2047)])))) + (0.0416666679f * (fTemp215 * dsp->fRec123[((dsp->IOTA - (iTemp216 + 1)) & 2047)])))));
			dsp->fRec125[0] = fRec129;
			int iRec126 = iRec130;
			dsp->fRec121[0] = dsp->fRec125[1];
			int iRec122 = iRec126;
			float fRec118 = dsp->fRec121[1];
			float fRec119 = ((float)iRec122 + dsp->fRec121[1]);
			dsp->iRec112[0] = iRec117;
			float fRec113 = fRec120;
			float fRec114 = fRec118;
			float fRec115 = fRec119;
			dsp->fRec108[(dsp->IOTA & 2047)] = fRec113;
			float fRec109 = fRec124;
			float fRec110 = fRec114;
			float fRec111 = fRec115;
			dsp->fRec106[0] = fRec109;
			float fRec107 = fRec111;
			dsp->iRec151[0] = 0;
			int iRec152 = dsp->iRec151[1];
			float fRec155 = ((float)dsp->iRec147[1] - (0.997843683f * ((0.699999988f * dsp->fRec156[2]) + (0.150000006f * (dsp->fRec156[1] + dsp->fRec156[3])))));
			dsp->fRec170[0] = (fSlow13 + (0.999000013f * dsp->fRec170[1]));
			float fTemp217 = (dsp->fRec170[0] + -0.109999999f);
			float fTemp218 = (dsp->fConst2 * (fTemp0 * fTemp217));
			float fTemp219 = (fTemp218 + -1.49999499f);
			int iTemp220 = (int)fTemp219;
			int iTemp221 = (int)min(dsp->fConst1, (float)max(0, iTemp220));
			float fTemp222 = floorf(fTemp219);
			float fTemp223 = (fTemp218 + (-1.0f - fTemp222));
			float fTemp224 = (0.0f - fTemp223);
			float fTemp225 = (fTemp218 + (-2.0f - fTemp222));
			float fTemp226 = (0.0f - (0.5f * fTemp225));
			float fTemp227 = (fTemp218 + (-3.0f - fTemp222));
			float fTemp228 = (0.0f - (0.333333343f * fTemp227));
			float fTemp229 = (fTemp218 + (-4.0f - fTemp222));
			float fTemp230 = (0.0f - (0.25f * fTemp229));
			float fTemp231 = (fTemp218 - fTemp222);
			int iTemp232 = (int)min(dsp->fConst1, (float)max(0, (iTemp220 + 2)));
			float fTemp233 = (0.0f - fTemp227);
			float fTemp234 = (0.0f - (0.5f * fTemp229));
			int iTemp235 = (int)min(dsp->fConst1, (float)max(0, (iTemp220 + 1)));
			float fTemp236 = (0.0f - fTemp225);
			float fTemp237 = (0.0f - (0.5f * fTemp227));
			float fTemp238 = (0.0f - (0.333333343f * fTemp229));
			float fTemp239 = (fTemp223 * fTemp225);
			int iTemp240 = (int)min(dsp->fConst1, (float)max(0, (iTemp220 + 3)));
			float fTemp241 = (0.0f - fTemp229);
			float fTemp242 = (fTemp239 * fTemp227);
			int iTemp243 = (int)min(dsp->fConst1, (float)max(0, (iTemp220 + 4)));
			dsp->fRec166[0] = (((((dsp->fRec143[((dsp->IOTA - (iTemp221 + 1)) & 2047)] * fTemp224) * fTemp226) * fTemp228) * fTemp230) + (fTemp231 * ((((0.5f * (((fTemp223 * dsp->fRec143[((dsp->IOTA - (iTemp232 + 1)) & 2047)]) * fTemp233) * fTemp234)) + (((dsp->fRec143[((dsp->IOTA - (iTemp235 + 1)) & 2047)] * fTemp236) * fTemp237) * fTemp238)) + (0.166666672f * ((fTemp239 * dsp->fRec143[((dsp->IOTA - (iTemp240 + 1)) & 2047)]) * fTemp241))) + (0.0416666679f * (fTemp242 * dsp->fRec143[((dsp->IOTA - (iTemp243 + 1)) & 2047)])))));
			dsp->fRec171[0] = ((0.600000024f * dsp->fRec166[1]) + (0.400000006f * dsp->fRec171[1]));
			float fRec167 = dsp->fRec171[0];
			dsp->iVec12[0] = iSlow15;
			int iTemp244 = ((iSlow15 - dsp->iVec12[1]) > 0);
			dsp->fRec173[0] = dsp->fRec141[1];
			dsp->fRec174[(dsp->IOTA & 2047)] = (0.0f - (0.997843683f * ((0.699999988f * dsp->fRec173[2]) + (0.150000006f * (dsp->fRec173[1] + dsp->fRec173[3])))));
			int iRec175 = 0;
			float fTemp245 = (dsp->fConst2 * (dsp->fRec29[0] * fTemp217));
			float fTemp246 = (fTemp245 + -1.49999499f);
			int iTemp247 = (int)fTemp246;
			int iTemp248 = (int)min(dsp->fConst1, (float)max(0, iTemp247));
			float fTemp249 = floorf(fTemp246);
			float fTemp250 = (fTemp245 + (-1.0f - fTemp249));
			float fTemp251 = (0.0f - fTemp250);
			float fTemp252 = (fTemp245 + (-2.0f - fTemp249));
			float fTemp253 = (0.0f - (0.5f * fTemp252));
			float fTemp254 = (fTemp245 + (-3.0f - fTemp249));
			float fTemp255 = (0.0f - (0.333333343f * fTemp254));
			float fTemp256 = (fTemp245 + (-4.0f - fTemp249));
			float fTemp257 = (0.0f - (0.25f * fTemp256));
			float fTemp258 = (fTemp245 - fTemp249);
			int iTemp259 = (int)min(dsp->fConst1, (float)max(0, (iTemp247 + 2)));
			float fTemp260 = (0.0f - fTemp254);
			float fTemp261 = (0.0f - (0.5f * fTemp256));
			int iTemp262 = (int)min(dsp->fConst1, (float)max(0, (iTemp247 + 1)));
			float fTemp263 = (0.0f - fTemp252);
			float fTemp264 = (0.0f - (0.5f * fTemp254));
			float fTemp265 = (0.0f - (0.333333343f * fTemp256));
			float fTemp266 = (fTemp250 * fTemp252);
			int iTemp267 = (int)min(dsp->fConst1, (float)max(0, (iTemp247 + 3)));
			float fTemp268 = (0.0f - fTemp256);
			float fTemp269 = (fTemp266 * fTemp254);
			int iTemp270 = (int)min(dsp->fConst1, (float)max(0, (iTemp247 + 4)));
			dsp->fVec13[0] = (((((dsp->fRec174[((dsp->IOTA - (iTemp248 + 2)) & 2047)] * fTemp251) * fTemp253) * fTemp255) * fTemp257) + (fTemp258 * ((((0.5f * (((fTemp250 * dsp->fRec174[((dsp->IOTA - (iTemp259 + 2)) & 2047)]) * fTemp260) * fTemp261)) + (((dsp->fRec174[((dsp->IOTA - (iTemp262 + 2)) & 2047)] * fTemp263) * fTemp264) * fTemp265)) + (0.166666672f * ((fTemp266 * dsp->fRec174[((dsp->IOTA - (iTemp267 + 2)) & 2047)]) * fTemp268))) + (0.0416666679f * (fTemp269 * dsp->fRec174[((dsp->IOTA - (iTemp270 + 2)) & 2047)])))));
			dsp->fVec14[0] = ((float)iTemp244 + dsp->fVec13[1]);
			dsp->fRec172[(dsp->IOTA & 2047)] = ((0.400000006f * dsp->fRec172[((dsp->IOTA - 1) & 2047)]) + (0.600000024f * dsp->fVec14[1]));
			float fRec168 = (((((fTemp224 * fTemp226) * fTemp228) * fTemp230) * dsp->fRec172[((dsp->IOTA - iTemp221) & 2047)]) + (fTemp231 * ((0.0416666679f * (fTemp242 * dsp->fRec172[((dsp->IOTA - iTemp243) & 2047)])) + (((((fTemp236 * fTemp237) * fTemp238) * dsp->fRec172[((dsp->IOTA - iTemp235) & 2047)]) + (0.5f * (((fTemp223 * fTemp233) * fTemp234) * dsp->fRec172[((dsp->IOTA - iTemp232) & 2047)]))) + (0.166666672f * ((fTemp239 * fTemp241) * dsp->fRec172[((dsp->IOTA - iTemp240) & 2047)]))))));
			int iRec169 = iRec175;
			dsp->fRec162[0] = fRec167;
			float fRec163 = ((float)iTemp244 + dsp->fRec162[1]);
			float fRec164 = fRec168;
			int iRec165 = iRec169;
			dsp->fRec158[(dsp->IOTA & 2047)] = fRec163;
			float fRec159 = (((((fTemp251 * fTemp253) * fTemp255) * fTemp257) * dsp->fRec158[((dsp->IOTA - (iTemp248 + 1)) & 2047)]) + (fTemp258 * (((0.166666672f * ((fTemp266 * fTemp268) * dsp->fRec158[((dsp->IOTA - (iTemp267 + 1)) & 2047)])) + ((((fTemp263 * fTemp264) * fTemp265) * dsp->fRec158[((dsp->IOTA - (iTemp262 + 1)) & 2047)]) + (0.5f * (((fTemp250 * fTemp260) * fTemp261) * dsp->fRec158[((dsp->IOTA - (iTemp259 + 1)) & 2047)])))) + (0.0416666679f * (fTemp269 * dsp->fRec158[((dsp->IOTA - (iTemp270 + 1)) & 2047)])))));
			dsp->fRec160[0] = fRec164;
			int iRec161 = iRec165;
			dsp->fRec156[0] = dsp->fRec160[1];
			int iRec157 = iRec161;
			float fRec153 = dsp->fRec156[1];
			float fRec154 = ((float)iRec157 + dsp->fRec156[1]);
			dsp->iRec147[0] = iRec152;
			float fRec148 = fRec155;
			float fRec149 = fRec153;
			float fRec150 = fRec154;
			dsp->fRec143[(dsp->IOTA & 2047)] = fRec148;
			float fRec144 = fRec159;
			float fRec145 = fRec149;
			float fRec146 = fRec150;
			dsp->fRec141[0] = fRec144;
			float fRec142 = fRec146;
			dsp->iRec186[0] = 0;
			int iRec187 = dsp->iRec186[1];
			float fRec190 = ((float)dsp->iRec182[1] - (0.997843683f * ((0.699999988f * dsp->fRec191[2]) + (0.150000006f * (dsp->fRec191[1] + dsp->fRec191[3])))));
			dsp->fRec205[0] = (fSlow16 + (0.999000013f * dsp->fRec205[1]));
			float fTemp271 = (dsp->fRec205[0] + -0.109999999f);
			float fTemp272 = (dsp->fConst2 * (fTemp0 * fTemp271));
			float fTemp273 = (fTemp272 + -1.49999499f);
			int iTemp274 = (int)fTemp273;
			int iTemp275 = (int)min(dsp->fConst1, (float)max(0, iTemp274));
			float fTemp276 = floorf(fTemp273);
			float fTemp277 = (fTemp272 + (-1.0f - fTemp276));
			float fTemp278 = (0.0f - fTemp277);
			float fTemp279 = (fTemp272 + (-2.0f - fTemp276));
			float fTemp280 = (0.0f - (0.5f * fTemp279));
			float fTemp281 = (fTemp272 + (-3.0f - fTemp276));
			float fTemp282 = (0.0f - (0.333333343f * fTemp281));
			float fTemp283 = (fTemp272 + (-4.0f - fTemp276));
			float fTemp284 = (0.0f - (0.25f * fTemp283));
			float fTemp285 = (fTemp272 - fTemp276);
			int iTemp286 = (int)min(dsp->fConst1, (float)max(0, (iTemp274 + 2)));
			float fTemp287 = (0.0f - fTemp281);
			float fTemp288 = (0.0f - (0.5f * fTemp283));
			int iTemp289 = (int)min(dsp->fConst1, (float)max(0, (iTemp274 + 1)));
			float fTemp290 = (0.0f - fTemp279);
			float fTemp291 = (0.0f - (0.5f * fTemp281));
			float fTemp292 = (0.0f - (0.333333343f * fTemp283));
			float fTemp293 = (fTemp277 * fTemp279);
			int iTemp294 = (int)min(dsp->fConst1, (float)max(0, (iTemp274 + 3)));
			float fTemp295 = (0.0f - fTemp283);
			float fTemp296 = (fTemp293 * fTemp281);
			int iTemp297 = (int)min(dsp->fConst1, (float)max(0, (iTemp274 + 4)));
			dsp->fRec201[0] = (((((dsp->fRec178[((dsp->IOTA - (iTemp275 + 1)) & 2047)] * fTemp278) * fTemp280) * fTemp282) * fTemp284) + (fTemp285 * ((((0.5f * (((fTemp277 * dsp->fRec178[((dsp->IOTA - (iTemp286 + 1)) & 2047)]) * fTemp287) * fTemp288)) + (((dsp->fRec178[((dsp->IOTA - (iTemp289 + 1)) & 2047)] * fTemp290) * fTemp291) * fTemp292)) + (0.166666672f * ((fTemp293 * dsp->fRec178[((dsp->IOTA - (iTemp294 + 1)) & 2047)]) * fTemp295))) + (0.0416666679f * (fTemp296 * dsp->fRec178[((dsp->IOTA - (iTemp297 + 1)) & 2047)])))));
			dsp->fRec206[0] = ((0.600000024f * dsp->fRec201[1]) + (0.400000006f * dsp->fRec206[1]));
			float fRec202 = dsp->fRec206[0];
			dsp->iVec15[0] = iSlow18;
			int iTemp298 = ((iSlow18 - dsp->iVec15[1]) > 0);
			dsp->fRec208[0] = dsp->fRec176[1];
			dsp->fRec209[(dsp->IOTA & 2047)] = (0.0f - (0.997843683f * ((0.699999988f * dsp->fRec208[2]) + (0.150000006f * (dsp->fRec208[1] + dsp->fRec208[3])))));
			int iRec210 = 0;
			float fTemp299 = (dsp->fConst2 * (dsp->fRec29[0] * fTemp271));
			float fTemp300 = (fTemp299 + -1.49999499f);
			int iTemp301 = (int)fTemp300;
			int iTemp302 = (int)min(dsp->fConst1, (float)max(0, iTemp301));
			float fTemp303 = floorf(fTemp300);
			float fTemp304 = (fTemp299 + (-1.0f - fTemp303));
			float fTemp305 = (0.0f - fTemp304);
			float fTemp306 = (fTemp299 + (-2.0f - fTemp303));
			float fTemp307 = (0.0f - (0.5f * fTemp306));
			float fTemp308 = (fTemp299 + (-3.0f - fTemp303));
			float fTemp309 = (0.0f - (0.333333343f * fTemp308));
			float fTemp310 = (fTemp299 + (-4.0f - fTemp303));
			float fTemp311 = (0.0f - (0.25f * fTemp310));
			float fTemp312 = (fTemp299 - fTemp303);
			int iTemp313 = (int)min(dsp->fConst1, (float)max(0, (iTemp301 + 2)));
			float fTemp314 = (0.0f - fTemp308);
			float fTemp315 = (0.0f - (0.5f * fTemp310));
			int iTemp316 = (int)min(dsp->fConst1, (float)max(0, (iTemp301 + 1)));
			float fTemp317 = (0.0f - fTemp306);
			float fTemp318 = (0.0f - (0.5f * fTemp308));
			float fTemp319 = (0.0f - (0.333333343f * fTemp310));
			float fTemp320 = (fTemp304 * fTemp306);
			int iTemp321 = (int)min(dsp->fConst1, (float)max(0, (iTemp301 + 3)));
			float fTemp322 = (0.0f - fTemp310);
			float fTemp323 = (fTemp320 * fTemp308);
			int iTemp324 = (int)min(dsp->fConst1, (float)max(0, (iTemp301 + 4)));
			dsp->fVec16[0] = (((((dsp->fRec209[((dsp->IOTA - (iTemp302 + 2)) & 2047)] * fTemp305) * fTemp307) * fTemp309) * fTemp311) + (fTemp312 * ((((0.5f * (((fTemp304 * dsp->fRec209[((dsp->IOTA - (iTemp313 + 2)) & 2047)]) * fTemp314) * fTemp315)) + (((dsp->fRec209[((dsp->IOTA - (iTemp316 + 2)) & 2047)] * fTemp317) * fTemp318) * fTemp319)) + (0.166666672f * ((fTemp320 * dsp->fRec209[((dsp->IOTA - (iTemp321 + 2)) & 2047)]) * fTemp322))) + (0.0416666679f * (fTemp323 * dsp->fRec209[((dsp->IOTA - (iTemp324 + 2)) & 2047)])))));
			dsp->fVec17[0] = ((float)iTemp298 + dsp->fVec16[1]);
			dsp->fRec207[(dsp->IOTA & 2047)] = ((0.400000006f * dsp->fRec207[((dsp->IOTA - 1) & 2047)]) + (0.600000024f * dsp->fVec17[1]));
			float fRec203 = (((((fTemp278 * fTemp280) * fTemp282) * fTemp284) * dsp->fRec207[((dsp->IOTA - iTemp275) & 2047)]) + (fTemp285 * ((0.0416666679f * (fTemp296 * dsp->fRec207[((dsp->IOTA - iTemp297) & 2047)])) + (((((fTemp290 * fTemp291) * fTemp292) * dsp->fRec207[((dsp->IOTA - iTemp289) & 2047)]) + (0.5f * (((fTemp277 * fTemp287) * fTemp288) * dsp->fRec207[((dsp->IOTA - iTemp286) & 2047)]))) + (0.166666672f * ((fTemp293 * fTemp295) * dsp->fRec207[((dsp->IOTA - iTemp294) & 2047)]))))));
			int iRec204 = iRec210;
			dsp->fRec197[0] = fRec202;
			float fRec198 = ((float)iTemp298 + dsp->fRec197[1]);
			float fRec199 = fRec203;
			int iRec200 = iRec204;
			dsp->fRec193[(dsp->IOTA & 2047)] = fRec198;
			float fRec194 = (((((fTemp305 * fTemp307) * fTemp309) * fTemp311) * dsp->fRec193[((dsp->IOTA - (iTemp302 + 1)) & 2047)]) + (fTemp312 * (((0.166666672f * ((fTemp320 * fTemp322) * dsp->fRec193[((dsp->IOTA - (iTemp321 + 1)) & 2047)])) + ((((fTemp317 * fTemp318) * fTemp319) * dsp->fRec193[((dsp->IOTA - (iTemp316 + 1)) & 2047)]) + (0.5f * (((fTemp304 * fTemp314) * fTemp315) * dsp->fRec193[((dsp->IOTA - (iTemp313 + 1)) & 2047)])))) + (0.0416666679f * (fTemp323 * dsp->fRec193[((dsp->IOTA - (iTemp324 + 1)) & 2047)])))));
			dsp->fRec195[0] = fRec199;
			int iRec196 = iRec200;
			dsp->fRec191[0] = dsp->fRec195[1];
			int iRec192 = iRec196;
			float fRec188 = dsp->fRec191[1];
			float fRec189 = ((float)iRec192 + dsp->fRec191[1]);
			dsp->iRec182[0] = iRec187;
			float fRec183 = fRec190;
			float fRec184 = fRec188;
			float fRec185 = fRec189;
			dsp->fRec178[(dsp->IOTA & 2047)] = fRec183;
			float fRec179 = fRec194;
			float fRec180 = fRec184;
			float fRec181 = fRec185;
			dsp->fRec176[0] = fRec179;
			float fRec177 = fRec181;
			float fTemp325 = (((((fRec1 + fRec37) + fRec72) + fRec107) + fRec142) + fRec177);
			output0[i] = (FAUSTFLOAT)fTemp325;
			output1[i] = (FAUSTFLOAT)fTemp325;
			dsp->iRec10[1] = dsp->iRec10[0];
			dsp->fRec29[1] = dsp->fRec29[0];
			dsp->fRec30[1] = dsp->fRec30[0];
			dsp->fRec25[1] = dsp->fRec25[0];
			dsp->fRec31[1] = dsp->fRec31[0];
			/* C99 loop */
			{
				int j0;
				for (j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
					dsp->fRec33[j0] = dsp->fRec33[(j0 - 1)];
					
				}
				
			}
			dsp->IOTA = (dsp->IOTA + 1);
			dsp->fVec0[1] = dsp->fVec0[0];
			dsp->iVec1[1] = dsp->iVec1[0];
			dsp->fVec2[1] = dsp->fVec2[0];
			dsp->fRec21[1] = dsp->fRec21[0];
			dsp->fRec19[1] = dsp->fRec19[0];
			/* C99 loop */
			{
				int j1;
				for (j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
					dsp->fRec15[j1] = dsp->fRec15[(j1 - 1)];
					
				}
				
			}
			dsp->iRec6[1] = dsp->iRec6[0];
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->iRec46[1] = dsp->iRec46[0];
			dsp->fRec65[1] = dsp->fRec65[0];
			dsp->fRec61[1] = dsp->fRec61[0];
			dsp->fRec66[1] = dsp->fRec66[0];
			dsp->iVec3[1] = dsp->iVec3[0];
			/* C99 loop */
			{
				int j2;
				for (j2 = 3; (j2 > 0); j2 = (j2 - 1)) {
					dsp->fRec68[j2] = dsp->fRec68[(j2 - 1)];
					
				}
				
			}
			dsp->fVec4[1] = dsp->fVec4[0];
			dsp->fVec5[1] = dsp->fVec5[0];
			dsp->fRec57[1] = dsp->fRec57[0];
			dsp->fRec55[1] = dsp->fRec55[0];
			/* C99 loop */
			{
				int j3;
				for (j3 = 3; (j3 > 0); j3 = (j3 - 1)) {
					dsp->fRec51[j3] = dsp->fRec51[(j3 - 1)];
					
				}
				
			}
			dsp->iRec42[1] = dsp->iRec42[0];
			dsp->fRec36[1] = dsp->fRec36[0];
			dsp->iRec81[1] = dsp->iRec81[0];
			dsp->fRec100[1] = dsp->fRec100[0];
			dsp->fRec96[1] = dsp->fRec96[0];
			dsp->fRec101[1] = dsp->fRec101[0];
			dsp->iVec6[1] = dsp->iVec6[0];
			/* C99 loop */
			{
				int j4;
				for (j4 = 3; (j4 > 0); j4 = (j4 - 1)) {
					dsp->fRec103[j4] = dsp->fRec103[(j4 - 1)];
					
				}
				
			}
			dsp->fVec7[1] = dsp->fVec7[0];
			dsp->fVec8[1] = dsp->fVec8[0];
			dsp->fRec92[1] = dsp->fRec92[0];
			dsp->fRec90[1] = dsp->fRec90[0];
			/* C99 loop */
			{
				int j5;
				for (j5 = 3; (j5 > 0); j5 = (j5 - 1)) {
					dsp->fRec86[j5] = dsp->fRec86[(j5 - 1)];
					
				}
				
			}
			dsp->iRec77[1] = dsp->iRec77[0];
			dsp->fRec71[1] = dsp->fRec71[0];
			dsp->iRec116[1] = dsp->iRec116[0];
			dsp->fRec135[1] = dsp->fRec135[0];
			dsp->fRec131[1] = dsp->fRec131[0];
			dsp->fRec136[1] = dsp->fRec136[0];
			dsp->iVec9[1] = dsp->iVec9[0];
			/* C99 loop */
			{
				int j6;
				for (j6 = 3; (j6 > 0); j6 = (j6 - 1)) {
					dsp->fRec138[j6] = dsp->fRec138[(j6 - 1)];
					
				}
				
			}
			dsp->fVec10[1] = dsp->fVec10[0];
			dsp->fVec11[1] = dsp->fVec11[0];
			dsp->fRec127[1] = dsp->fRec127[0];
			dsp->fRec125[1] = dsp->fRec125[0];
			/* C99 loop */
			{
				int j7;
				for (j7 = 3; (j7 > 0); j7 = (j7 - 1)) {
					dsp->fRec121[j7] = dsp->fRec121[(j7 - 1)];
					
				}
				
			}
			dsp->iRec112[1] = dsp->iRec112[0];
			dsp->fRec106[1] = dsp->fRec106[0];
			dsp->iRec151[1] = dsp->iRec151[0];
			dsp->fRec170[1] = dsp->fRec170[0];
			dsp->fRec166[1] = dsp->fRec166[0];
			dsp->fRec171[1] = dsp->fRec171[0];
			dsp->iVec12[1] = dsp->iVec12[0];
			/* C99 loop */
			{
				int j8;
				for (j8 = 3; (j8 > 0); j8 = (j8 - 1)) {
					dsp->fRec173[j8] = dsp->fRec173[(j8 - 1)];
					
				}
				
			}
			dsp->fVec13[1] = dsp->fVec13[0];
			dsp->fVec14[1] = dsp->fVec14[0];
			dsp->fRec162[1] = dsp->fRec162[0];
			dsp->fRec160[1] = dsp->fRec160[0];
			/* C99 loop */
			{
				int j9;
				for (j9 = 3; (j9 > 0); j9 = (j9 - 1)) {
					dsp->fRec156[j9] = dsp->fRec156[(j9 - 1)];
					
				}
				
			}
			dsp->iRec147[1] = dsp->iRec147[0];
			dsp->fRec141[1] = dsp->fRec141[0];
			dsp->iRec186[1] = dsp->iRec186[0];
			dsp->fRec205[1] = dsp->fRec205[0];
			dsp->fRec201[1] = dsp->fRec201[0];
			dsp->fRec206[1] = dsp->fRec206[0];
			dsp->iVec15[1] = dsp->iVec15[0];
			/* C99 loop */
			{
				int j10;
				for (j10 = 3; (j10 > 0); j10 = (j10 - 1)) {
					dsp->fRec208[j10] = dsp->fRec208[(j10 - 1)];
					
				}
				
			}
			dsp->fVec16[1] = dsp->fVec16[0];
			dsp->fVec17[1] = dsp->fVec17[0];
			dsp->fRec197[1] = dsp->fRec197[0];
			dsp->fRec195[1] = dsp->fRec195[0];
			/* C99 loop */
			{
				int j11;
				for (j11 = 3; (j11 > 0); j11 = (j11 - 1)) {
					dsp->fRec191[j11] = dsp->fRec191[(j11 - 1)];
					
				}
				
			}
			dsp->iRec182[1] = dsp->iRec182[0];
			dsp->fRec176[1] = dsp->fRec176[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
