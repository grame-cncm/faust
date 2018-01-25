/* ------------------------------------------------------------
name: "granulator1"
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
	int iConst1;
	int iRec3[2];
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	int iRec4[2];
	int iRec2[2];
	int iVec0[2];
	float fConst2;
	float fConst3;
	float fRec5[2];
	float fRec1[2];
	float fRec0[2];
	int iVec1[2];
	float fRec8[2];
	float fRec7[2];
	float fRec6[2];
	int IOTA;
	float fVec2[524288];
	int iConst4;
	int iVec3[2];
	float fRec11[2];
	float fRec10[2];
	float fRec9[2];
	int iConst5;
	int iVec4[2];
	float fRec14[2];
	float fRec13[2];
	float fRec12[2];
	int iConst6;
	int iVec5[2];
	float fRec17[2];
	float fRec16[2];
	float fRec15[2];
	int iConst7;
	int iVec6[2];
	float fRec20[2];
	float fRec19[2];
	float fRec18[2];
	int iConst8;
	int iVec7[2];
	float fRec23[2];
	float fRec22[2];
	float fRec21[2];
	int iConst9;
	int iVec8[2];
	float fRec26[2];
	float fRec25[2];
	float fRec24[2];
	int iConst10;
	int iVec9[2];
	float fRec29[2];
	float fRec28[2];
	float fRec27[2];
	int iConst11;
	int iVec10[2];
	float fRec32[2];
	float fRec31[2];
	float fRec30[2];
	int iConst12;
	int iVec11[2];
	float fRec35[2];
	float fRec34[2];
	float fRec33[2];
	int iConst13;
	int iVec12[2];
	float fRec38[2];
	float fRec37[2];
	float fRec36[2];
	int iConst14;
	int iVec13[2];
	float fRec41[2];
	float fRec40[2];
	float fRec39[2];
	int iConst15;
	int iVec14[2];
	float fRec44[2];
	float fRec43[2];
	float fRec42[2];
	int iConst16;
	int iVec15[2];
	float fRec47[2];
	float fRec46[2];
	float fRec45[2];
	int iConst17;
	int iVec16[2];
	float fRec50[2];
	float fRec49[2];
	float fRec48[2];
	int iConst18;
	int iVec17[2];
	float fRec53[2];
	float fRec52[2];
	float fRec51[2];
	int iConst19;
	int iVec18[2];
	float fRec56[2];
	float fRec55[2];
	float fRec54[2];
	int iConst20;
	int iVec19[2];
	float fRec59[2];
	float fRec58[2];
	float fRec57[2];
	int iConst21;
	int iVec20[2];
	float fRec62[2];
	float fRec61[2];
	float fRec60[2];
	int iConst22;
	int iVec21[2];
	float fRec65[2];
	float fRec64[2];
	float fRec63[2];
	int iConst23;
	int iVec22[2];
	float fRec68[2];
	float fRec67[2];
	float fRec66[2];
	int iConst24;
	int iVec23[2];
	float fRec71[2];
	float fRec70[2];
	float fRec69[2];
	int iConst25;
	int iVec24[2];
	float fRec74[2];
	float fRec73[2];
	float fRec72[2];
	int iConst26;
	int iVec25[2];
	float fRec77[2];
	float fRec76[2];
	float fRec75[2];
	int iConst27;
	int iVec26[2];
	float fRec80[2];
	float fRec79[2];
	float fRec78[2];
	int iConst28;
	int iVec27[2];
	float fRec83[2];
	float fRec82[2];
	float fRec81[2];
	int iConst29;
	int iVec28[2];
	float fRec86[2];
	float fRec85[2];
	float fRec84[2];
	int iConst30;
	int iVec29[2];
	float fRec89[2];
	float fRec88[2];
	float fRec87[2];
	int iConst31;
	int iVec30[2];
	float fRec92[2];
	float fRec91[2];
	float fRec90[2];
	int iConst32;
	int iVec31[2];
	float fRec95[2];
	float fRec94[2];
	float fRec93[2];
	int iConst33;
	int iVec32[2];
	float fRec98[2];
	float fRec97[2];
	float fRec96[2];
	int iConst34;
	
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
	m->declare(m->metaInterface, "name", "granulator1");
}

int getSampleRatemydsp(mydsp* dsp) { return dsp->fSamplingFreq; }

int getNumInputsmydsp(mydsp* dsp) {
	return 1;
	
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
	dsp->fHslider0 = (FAUSTFLOAT)0.0f;
	dsp->fHslider1 = (FAUSTFLOAT)0.0f;
	dsp->fHslider2 = (FAUSTFLOAT)0.0f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			dsp->iRec3[l0] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			dsp->iRec4[l1] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			dsp->iRec2[l2] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			dsp->iVec0[l3] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			dsp->fRec5[l4] = 0.0f;
			
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
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			dsp->iVec1[l7] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			dsp->fRec8[l8] = 0.0f;
			
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
			dsp->fRec6[l10] = 0.0f;
			
		}
		
	}
	dsp->IOTA = 0;
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 524288); l11 = (l11 + 1)) {
			dsp->fVec2[l11] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			dsp->iVec3[l12] = 0;
			
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
			dsp->fRec10[l14] = 0.0f;
			
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
			dsp->iVec4[l16] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l17;
		for (l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			dsp->fRec14[l17] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l18;
		for (l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			dsp->fRec13[l18] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l19;
		for (l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			dsp->fRec12[l19] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l20;
		for (l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			dsp->iVec5[l20] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l21;
		for (l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			dsp->fRec17[l21] = 0.0f;
			
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
			dsp->fRec15[l23] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l24;
		for (l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			dsp->iVec6[l24] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l25;
		for (l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			dsp->fRec20[l25] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l26;
		for (l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			dsp->fRec19[l26] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l27;
		for (l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			dsp->fRec18[l27] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l28;
		for (l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			dsp->iVec7[l28] = 0;
			
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
			dsp->fRec22[l30] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l31;
		for (l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			dsp->fRec21[l31] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l32;
		for (l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			dsp->iVec8[l32] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l33;
		for (l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			dsp->fRec26[l33] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l34;
		for (l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			dsp->fRec25[l34] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l35;
		for (l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			dsp->fRec24[l35] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l36;
		for (l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			dsp->iVec9[l36] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l37;
		for (l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			dsp->fRec29[l37] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l38;
		for (l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			dsp->fRec28[l38] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l39;
		for (l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			dsp->fRec27[l39] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l40;
		for (l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			dsp->iVec10[l40] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l41;
		for (l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			dsp->fRec32[l41] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l42;
		for (l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			dsp->fRec31[l42] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l43;
		for (l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			dsp->fRec30[l43] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l44;
		for (l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			dsp->iVec11[l44] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l45;
		for (l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			dsp->fRec35[l45] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l46;
		for (l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			dsp->fRec34[l46] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l47;
		for (l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			dsp->fRec33[l47] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l48;
		for (l48 = 0; (l48 < 2); l48 = (l48 + 1)) {
			dsp->iVec12[l48] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l49;
		for (l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			dsp->fRec38[l49] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l50;
		for (l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			dsp->fRec37[l50] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l51;
		for (l51 = 0; (l51 < 2); l51 = (l51 + 1)) {
			dsp->fRec36[l51] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l52;
		for (l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			dsp->iVec13[l52] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l53;
		for (l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			dsp->fRec41[l53] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l54;
		for (l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
			dsp->fRec40[l54] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l55;
		for (l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			dsp->fRec39[l55] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l56;
		for (l56 = 0; (l56 < 2); l56 = (l56 + 1)) {
			dsp->iVec14[l56] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l57;
		for (l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			dsp->fRec44[l57] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l58;
		for (l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			dsp->fRec43[l58] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l59;
		for (l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			dsp->fRec42[l59] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l60;
		for (l60 = 0; (l60 < 2); l60 = (l60 + 1)) {
			dsp->iVec15[l60] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l61;
		for (l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			dsp->fRec47[l61] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l62;
		for (l62 = 0; (l62 < 2); l62 = (l62 + 1)) {
			dsp->fRec46[l62] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l63;
		for (l63 = 0; (l63 < 2); l63 = (l63 + 1)) {
			dsp->fRec45[l63] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l64;
		for (l64 = 0; (l64 < 2); l64 = (l64 + 1)) {
			dsp->iVec16[l64] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l65;
		for (l65 = 0; (l65 < 2); l65 = (l65 + 1)) {
			dsp->fRec50[l65] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l66;
		for (l66 = 0; (l66 < 2); l66 = (l66 + 1)) {
			dsp->fRec49[l66] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l67;
		for (l67 = 0; (l67 < 2); l67 = (l67 + 1)) {
			dsp->fRec48[l67] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l68;
		for (l68 = 0; (l68 < 2); l68 = (l68 + 1)) {
			dsp->iVec17[l68] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l69;
		for (l69 = 0; (l69 < 2); l69 = (l69 + 1)) {
			dsp->fRec53[l69] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l70;
		for (l70 = 0; (l70 < 2); l70 = (l70 + 1)) {
			dsp->fRec52[l70] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l71;
		for (l71 = 0; (l71 < 2); l71 = (l71 + 1)) {
			dsp->fRec51[l71] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l72;
		for (l72 = 0; (l72 < 2); l72 = (l72 + 1)) {
			dsp->iVec18[l72] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l73;
		for (l73 = 0; (l73 < 2); l73 = (l73 + 1)) {
			dsp->fRec56[l73] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l74;
		for (l74 = 0; (l74 < 2); l74 = (l74 + 1)) {
			dsp->fRec55[l74] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l75;
		for (l75 = 0; (l75 < 2); l75 = (l75 + 1)) {
			dsp->fRec54[l75] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l76;
		for (l76 = 0; (l76 < 2); l76 = (l76 + 1)) {
			dsp->iVec19[l76] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l77;
		for (l77 = 0; (l77 < 2); l77 = (l77 + 1)) {
			dsp->fRec59[l77] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l78;
		for (l78 = 0; (l78 < 2); l78 = (l78 + 1)) {
			dsp->fRec58[l78] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l79;
		for (l79 = 0; (l79 < 2); l79 = (l79 + 1)) {
			dsp->fRec57[l79] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l80;
		for (l80 = 0; (l80 < 2); l80 = (l80 + 1)) {
			dsp->iVec20[l80] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l81;
		for (l81 = 0; (l81 < 2); l81 = (l81 + 1)) {
			dsp->fRec62[l81] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l82;
		for (l82 = 0; (l82 < 2); l82 = (l82 + 1)) {
			dsp->fRec61[l82] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l83;
		for (l83 = 0; (l83 < 2); l83 = (l83 + 1)) {
			dsp->fRec60[l83] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l84;
		for (l84 = 0; (l84 < 2); l84 = (l84 + 1)) {
			dsp->iVec21[l84] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l85;
		for (l85 = 0; (l85 < 2); l85 = (l85 + 1)) {
			dsp->fRec65[l85] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l86;
		for (l86 = 0; (l86 < 2); l86 = (l86 + 1)) {
			dsp->fRec64[l86] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l87;
		for (l87 = 0; (l87 < 2); l87 = (l87 + 1)) {
			dsp->fRec63[l87] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l88;
		for (l88 = 0; (l88 < 2); l88 = (l88 + 1)) {
			dsp->iVec22[l88] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l89;
		for (l89 = 0; (l89 < 2); l89 = (l89 + 1)) {
			dsp->fRec68[l89] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l90;
		for (l90 = 0; (l90 < 2); l90 = (l90 + 1)) {
			dsp->fRec67[l90] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l91;
		for (l91 = 0; (l91 < 2); l91 = (l91 + 1)) {
			dsp->fRec66[l91] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l92;
		for (l92 = 0; (l92 < 2); l92 = (l92 + 1)) {
			dsp->iVec23[l92] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l93;
		for (l93 = 0; (l93 < 2); l93 = (l93 + 1)) {
			dsp->fRec71[l93] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l94;
		for (l94 = 0; (l94 < 2); l94 = (l94 + 1)) {
			dsp->fRec70[l94] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l95;
		for (l95 = 0; (l95 < 2); l95 = (l95 + 1)) {
			dsp->fRec69[l95] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l96;
		for (l96 = 0; (l96 < 2); l96 = (l96 + 1)) {
			dsp->iVec24[l96] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l97;
		for (l97 = 0; (l97 < 2); l97 = (l97 + 1)) {
			dsp->fRec74[l97] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l98;
		for (l98 = 0; (l98 < 2); l98 = (l98 + 1)) {
			dsp->fRec73[l98] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l99;
		for (l99 = 0; (l99 < 2); l99 = (l99 + 1)) {
			dsp->fRec72[l99] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l100;
		for (l100 = 0; (l100 < 2); l100 = (l100 + 1)) {
			dsp->iVec25[l100] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l101;
		for (l101 = 0; (l101 < 2); l101 = (l101 + 1)) {
			dsp->fRec77[l101] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l102;
		for (l102 = 0; (l102 < 2); l102 = (l102 + 1)) {
			dsp->fRec76[l102] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l103;
		for (l103 = 0; (l103 < 2); l103 = (l103 + 1)) {
			dsp->fRec75[l103] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l104;
		for (l104 = 0; (l104 < 2); l104 = (l104 + 1)) {
			dsp->iVec26[l104] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l105;
		for (l105 = 0; (l105 < 2); l105 = (l105 + 1)) {
			dsp->fRec80[l105] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l106;
		for (l106 = 0; (l106 < 2); l106 = (l106 + 1)) {
			dsp->fRec79[l106] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l107;
		for (l107 = 0; (l107 < 2); l107 = (l107 + 1)) {
			dsp->fRec78[l107] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l108;
		for (l108 = 0; (l108 < 2); l108 = (l108 + 1)) {
			dsp->iVec27[l108] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l109;
		for (l109 = 0; (l109 < 2); l109 = (l109 + 1)) {
			dsp->fRec83[l109] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l110;
		for (l110 = 0; (l110 < 2); l110 = (l110 + 1)) {
			dsp->fRec82[l110] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l111;
		for (l111 = 0; (l111 < 2); l111 = (l111 + 1)) {
			dsp->fRec81[l111] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l112;
		for (l112 = 0; (l112 < 2); l112 = (l112 + 1)) {
			dsp->iVec28[l112] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l113;
		for (l113 = 0; (l113 < 2); l113 = (l113 + 1)) {
			dsp->fRec86[l113] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l114;
		for (l114 = 0; (l114 < 2); l114 = (l114 + 1)) {
			dsp->fRec85[l114] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l115;
		for (l115 = 0; (l115 < 2); l115 = (l115 + 1)) {
			dsp->fRec84[l115] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l116;
		for (l116 = 0; (l116 < 2); l116 = (l116 + 1)) {
			dsp->iVec29[l116] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l117;
		for (l117 = 0; (l117 < 2); l117 = (l117 + 1)) {
			dsp->fRec89[l117] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l118;
		for (l118 = 0; (l118 < 2); l118 = (l118 + 1)) {
			dsp->fRec88[l118] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l119;
		for (l119 = 0; (l119 < 2); l119 = (l119 + 1)) {
			dsp->fRec87[l119] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l120;
		for (l120 = 0; (l120 < 2); l120 = (l120 + 1)) {
			dsp->iVec30[l120] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l121;
		for (l121 = 0; (l121 < 2); l121 = (l121 + 1)) {
			dsp->fRec92[l121] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l122;
		for (l122 = 0; (l122 < 2); l122 = (l122 + 1)) {
			dsp->fRec91[l122] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l123;
		for (l123 = 0; (l123 < 2); l123 = (l123 + 1)) {
			dsp->fRec90[l123] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l124;
		for (l124 = 0; (l124 < 2); l124 = (l124 + 1)) {
			dsp->iVec31[l124] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l125;
		for (l125 = 0; (l125 < 2); l125 = (l125 + 1)) {
			dsp->fRec95[l125] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l126;
		for (l126 = 0; (l126 < 2); l126 = (l126 + 1)) {
			dsp->fRec94[l126] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l127;
		for (l127 = 0; (l127 < 2); l127 = (l127 + 1)) {
			dsp->fRec93[l127] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l128;
		for (l128 = 0; (l128 < 2); l128 = (l128 + 1)) {
			dsp->iVec32[l128] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l129;
		for (l129 = 0; (l129 < 2); l129 = (l129 + 1)) {
			dsp->fRec98[l129] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l130;
		for (l130 = 0; (l130 < 2); l130 = (l130 + 1)) {
			dsp->fRec97[l130] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l131;
		for (l131 = 0; (l131 < 2); l131 = (l131 + 1)) {
			dsp->fRec96[l131] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->iConst1 = (int)(0.00729927002f * dsp->fConst0);
	dsp->fConst2 = (4.0f * ((20.0f - (400.0f / dsp->fConst0)) / dsp->fConst0));
	dsp->fConst3 = (3200.0f / mydsp_faustpower2_f(dsp->fConst0));
	dsp->iConst4 = ((int)(0.3125f * dsp->fConst0) & 524287);
	dsp->iConst5 = ((int)(0.625f * dsp->fConst0) & 524287);
	dsp->iConst6 = ((int)(0.9375f * dsp->fConst0) & 524287);
	dsp->iConst7 = ((int)(1.25f * dsp->fConst0) & 524287);
	dsp->iConst8 = ((int)(1.5625f * dsp->fConst0) & 524287);
	dsp->iConst9 = ((int)(1.875f * dsp->fConst0) & 524287);
	dsp->iConst10 = ((int)(2.1875f * dsp->fConst0) & 524287);
	dsp->iConst11 = ((int)(2.5f * dsp->fConst0) & 524287);
	dsp->iConst12 = ((int)(2.8125f * dsp->fConst0) & 524287);
	dsp->iConst13 = ((int)(3.125f * dsp->fConst0) & 524287);
	dsp->iConst14 = ((int)(3.4375f * dsp->fConst0) & 524287);
	dsp->iConst15 = ((int)(3.75f * dsp->fConst0) & 524287);
	dsp->iConst16 = ((int)(4.0625f * dsp->fConst0) & 524287);
	dsp->iConst17 = ((int)(4.375f * dsp->fConst0) & 524287);
	dsp->iConst18 = ((int)(4.6875f * dsp->fConst0) & 524287);
	dsp->iConst19 = ((int)(0.15625f * dsp->fConst0) & 524287);
	dsp->iConst20 = ((int)(0.46875f * dsp->fConst0) & 524287);
	dsp->iConst21 = ((int)(0.78125f * dsp->fConst0) & 524287);
	dsp->iConst22 = ((int)(1.09375f * dsp->fConst0) & 524287);
	dsp->iConst23 = ((int)(1.40625f * dsp->fConst0) & 524287);
	dsp->iConst24 = ((int)(1.71875f * dsp->fConst0) & 524287);
	dsp->iConst25 = ((int)(2.03125f * dsp->fConst0) & 524287);
	dsp->iConst26 = ((int)(2.34375f * dsp->fConst0) & 524287);
	dsp->iConst27 = ((int)(2.65625f * dsp->fConst0) & 524287);
	dsp->iConst28 = ((int)(2.96875f * dsp->fConst0) & 524287);
	dsp->iConst29 = ((int)(3.28125f * dsp->fConst0) & 524287);
	dsp->iConst30 = ((int)(3.59375f * dsp->fConst0) & 524287);
	dsp->iConst31 = ((int)(3.90625f * dsp->fConst0) & 524287);
	dsp->iConst32 = ((int)(4.21875f * dsp->fConst0) & 524287);
	dsp->iConst33 = ((int)(4.53125f * dsp->fConst0) & 524287);
	dsp->iConst34 = ((int)(4.84375f * dsp->fConst0) & 524287);
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "granulator1");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "lim1", &dsp->fHslider1, 0.0f, 0.0f, 10000.0f, 1.0f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "lim2", &dsp->fHslider2, 0.0f, 0.0f, 10000.0f, 1.0f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "vol", &dsp->fHslider0, 0.0f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* input0 = inputs[0];
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	float fSlow0 = (float)dsp->fHslider0;
	float fSlow1 = (float)dsp->fHslider1;
	float fSlow2 = (float)dsp->fHslider2;
	float fSlow3 = (0.5f * (fSlow1 + fSlow2));
	float fSlow4 = (2.32830644e-10f * (fSlow2 - fSlow1));
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = (float)input0[i];
			dsp->iRec3[0] = ((dsp->iRec3[1] + 1) % dsp->iConst1);
			int iTemp1 = (dsp->iRec3[0] == 0);
			dsp->iRec4[0] = ((1103515245 * dsp->iRec4[1]) + 12345);
			dsp->iRec2[0] = (((1 - iTemp1) * dsp->iRec2[1]) + (iTemp1 * (int)(fSlow3 + (fSlow4 * (float)dsp->iRec4[0]))));
			int iTemp2 = (dsp->iRec2[0] == 0);
			dsp->iVec0[0] = iTemp2;
			int iTemp3 = (((dsp->fRec0[1] > 0.0f) | iTemp2) | dsp->iVec0[1]);
			dsp->fRec5[0] = ((dsp->fRec5[1] - dsp->fConst3) * (float)iTemp3);
			dsp->fRec1[0] = ((float)iTemp3 * (dsp->fConst2 + (dsp->fRec1[1] + dsp->fRec5[1])));
			dsp->fRec0[0] = max(0.0f, dsp->fRec1[1]);
			int iTemp4 = (dsp->iRec2[0] == 2);
			dsp->iVec1[0] = iTemp4;
			int iTemp5 = (((dsp->fRec6[1] > 0.0f) | iTemp4) | dsp->iVec1[1]);
			dsp->fRec8[0] = ((dsp->fRec8[1] - dsp->fConst3) * (float)iTemp5);
			dsp->fRec7[0] = ((float)iTemp5 * (dsp->fConst2 + (dsp->fRec7[1] + dsp->fRec8[1])));
			dsp->fRec6[0] = max(0.0f, dsp->fRec7[1]);
			float fTemp6 = (fSlow0 * fTemp0);
			dsp->fVec2[(dsp->IOTA & 524287)] = fTemp6;
			int iTemp7 = (dsp->iRec2[0] == 4);
			dsp->iVec3[0] = iTemp7;
			int iTemp8 = (((dsp->fRec9[1] > 0.0f) | iTemp7) | dsp->iVec3[1]);
			dsp->fRec11[0] = ((dsp->fRec11[1] - dsp->fConst3) * (float)iTemp8);
			dsp->fRec10[0] = ((float)iTemp8 * (dsp->fConst2 + (dsp->fRec10[1] + dsp->fRec11[1])));
			dsp->fRec9[0] = max(0.0f, dsp->fRec10[1]);
			int iTemp9 = (dsp->iRec2[0] == 6);
			dsp->iVec4[0] = iTemp9;
			int iTemp10 = (((dsp->fRec12[1] > 0.0f) | iTemp9) | dsp->iVec4[1]);
			dsp->fRec14[0] = ((dsp->fRec14[1] - dsp->fConst3) * (float)iTemp10);
			dsp->fRec13[0] = ((float)iTemp10 * (dsp->fConst2 + (dsp->fRec13[1] + dsp->fRec14[1])));
			dsp->fRec12[0] = max(0.0f, dsp->fRec13[1]);
			int iTemp11 = (dsp->iRec2[0] == 8);
			dsp->iVec5[0] = iTemp11;
			int iTemp12 = (((dsp->fRec15[1] > 0.0f) | iTemp11) | dsp->iVec5[1]);
			dsp->fRec17[0] = ((dsp->fRec17[1] - dsp->fConst3) * (float)iTemp12);
			dsp->fRec16[0] = ((float)iTemp12 * (dsp->fConst2 + (dsp->fRec16[1] + dsp->fRec17[1])));
			dsp->fRec15[0] = max(0.0f, dsp->fRec16[1]);
			int iTemp13 = (dsp->iRec2[0] == 10);
			dsp->iVec6[0] = iTemp13;
			int iTemp14 = (((dsp->fRec18[1] > 0.0f) | iTemp13) | dsp->iVec6[1]);
			dsp->fRec20[0] = ((dsp->fRec20[1] - dsp->fConst3) * (float)iTemp14);
			dsp->fRec19[0] = ((float)iTemp14 * (dsp->fConst2 + (dsp->fRec19[1] + dsp->fRec20[1])));
			dsp->fRec18[0] = max(0.0f, dsp->fRec19[1]);
			int iTemp15 = (dsp->iRec2[0] == 12);
			dsp->iVec7[0] = iTemp15;
			int iTemp16 = (((dsp->fRec21[1] > 0.0f) | iTemp15) | dsp->iVec7[1]);
			dsp->fRec23[0] = ((dsp->fRec23[1] - dsp->fConst3) * (float)iTemp16);
			dsp->fRec22[0] = ((float)iTemp16 * (dsp->fConst2 + (dsp->fRec22[1] + dsp->fRec23[1])));
			dsp->fRec21[0] = max(0.0f, dsp->fRec22[1]);
			int iTemp17 = (dsp->iRec2[0] == 14);
			dsp->iVec8[0] = iTemp17;
			int iTemp18 = (((dsp->fRec24[1] > 0.0f) | iTemp17) | dsp->iVec8[1]);
			dsp->fRec26[0] = ((dsp->fRec26[1] - dsp->fConst3) * (float)iTemp18);
			dsp->fRec25[0] = ((float)iTemp18 * (dsp->fConst2 + (dsp->fRec25[1] + dsp->fRec26[1])));
			dsp->fRec24[0] = max(0.0f, dsp->fRec25[1]);
			int iTemp19 = (dsp->iRec2[0] == 16);
			dsp->iVec9[0] = iTemp19;
			int iTemp20 = (((dsp->fRec27[1] > 0.0f) | iTemp19) | dsp->iVec9[1]);
			dsp->fRec29[0] = ((dsp->fRec29[1] - dsp->fConst3) * (float)iTemp20);
			dsp->fRec28[0] = ((float)iTemp20 * (dsp->fConst2 + (dsp->fRec28[1] + dsp->fRec29[1])));
			dsp->fRec27[0] = max(0.0f, dsp->fRec28[1]);
			int iTemp21 = (dsp->iRec2[0] == 18);
			dsp->iVec10[0] = iTemp21;
			int iTemp22 = (((dsp->fRec30[1] > 0.0f) | iTemp21) | dsp->iVec10[1]);
			dsp->fRec32[0] = ((dsp->fRec32[1] - dsp->fConst3) * (float)iTemp22);
			dsp->fRec31[0] = ((float)iTemp22 * (dsp->fConst2 + (dsp->fRec31[1] + dsp->fRec32[1])));
			dsp->fRec30[0] = max(0.0f, dsp->fRec31[1]);
			int iTemp23 = (dsp->iRec2[0] == 20);
			dsp->iVec11[0] = iTemp23;
			int iTemp24 = (((dsp->fRec33[1] > 0.0f) | iTemp23) | dsp->iVec11[1]);
			dsp->fRec35[0] = ((dsp->fRec35[1] - dsp->fConst3) * (float)iTemp24);
			dsp->fRec34[0] = ((float)iTemp24 * (dsp->fConst2 + (dsp->fRec34[1] + dsp->fRec35[1])));
			dsp->fRec33[0] = max(0.0f, dsp->fRec34[1]);
			int iTemp25 = (dsp->iRec2[0] == 22);
			dsp->iVec12[0] = iTemp25;
			int iTemp26 = (((dsp->fRec36[1] > 0.0f) | iTemp25) | dsp->iVec12[1]);
			dsp->fRec38[0] = ((dsp->fRec38[1] - dsp->fConst3) * (float)iTemp26);
			dsp->fRec37[0] = ((float)iTemp26 * (dsp->fConst2 + (dsp->fRec37[1] + dsp->fRec38[1])));
			dsp->fRec36[0] = max(0.0f, dsp->fRec37[1]);
			int iTemp27 = (dsp->iRec2[0] == 24);
			dsp->iVec13[0] = iTemp27;
			int iTemp28 = (((dsp->fRec39[1] > 0.0f) | iTemp27) | dsp->iVec13[1]);
			dsp->fRec41[0] = ((dsp->fRec41[1] - dsp->fConst3) * (float)iTemp28);
			dsp->fRec40[0] = ((float)iTemp28 * (dsp->fConst2 + (dsp->fRec40[1] + dsp->fRec41[1])));
			dsp->fRec39[0] = max(0.0f, dsp->fRec40[1]);
			int iTemp29 = (dsp->iRec2[0] == 26);
			dsp->iVec14[0] = iTemp29;
			int iTemp30 = (((dsp->fRec42[1] > 0.0f) | iTemp29) | dsp->iVec14[1]);
			dsp->fRec44[0] = ((dsp->fRec44[1] - dsp->fConst3) * (float)iTemp30);
			dsp->fRec43[0] = ((float)iTemp30 * (dsp->fConst2 + (dsp->fRec43[1] + dsp->fRec44[1])));
			dsp->fRec42[0] = max(0.0f, dsp->fRec43[1]);
			int iTemp31 = (dsp->iRec2[0] == 28);
			dsp->iVec15[0] = iTemp31;
			int iTemp32 = (((dsp->fRec45[1] > 0.0f) | iTemp31) | dsp->iVec15[1]);
			dsp->fRec47[0] = ((dsp->fRec47[1] - dsp->fConst3) * (float)iTemp32);
			dsp->fRec46[0] = ((float)iTemp32 * (dsp->fConst2 + (dsp->fRec46[1] + dsp->fRec47[1])));
			dsp->fRec45[0] = max(0.0f, dsp->fRec46[1]);
			int iTemp33 = (dsp->iRec2[0] == 30);
			dsp->iVec16[0] = iTemp33;
			int iTemp34 = (((dsp->fRec48[1] > 0.0f) | iTemp33) | dsp->iVec16[1]);
			dsp->fRec50[0] = ((dsp->fRec50[1] - dsp->fConst3) * (float)iTemp34);
			dsp->fRec49[0] = ((float)iTemp34 * (dsp->fConst2 + (dsp->fRec49[1] + dsp->fRec50[1])));
			dsp->fRec48[0] = max(0.0f, dsp->fRec49[1]);
			output0[i] = (FAUSTFLOAT)((((((((((((((((fSlow0 * (fTemp0 * dsp->fRec0[0])) + (dsp->fRec6[0] * dsp->fVec2[((dsp->IOTA - dsp->iConst4) & 524287)])) + (dsp->fRec9[0] * dsp->fVec2[((dsp->IOTA - dsp->iConst5) & 524287)])) + (dsp->fRec12[0] * dsp->fVec2[((dsp->IOTA - dsp->iConst6) & 524287)])) + (dsp->fRec15[0] * dsp->fVec2[((dsp->IOTA - dsp->iConst7) & 524287)])) + (dsp->fRec18[0] * dsp->fVec2[((dsp->IOTA - dsp->iConst8) & 524287)])) + (dsp->fRec21[0] * dsp->fVec2[((dsp->IOTA - dsp->iConst9) & 524287)])) + (dsp->fRec24[0] * dsp->fVec2[((dsp->IOTA - dsp->iConst10) & 524287)])) + (dsp->fRec27[0] * dsp->fVec2[((dsp->IOTA - dsp->iConst11) & 524287)])) + (dsp->fRec30[0] * dsp->fVec2[((dsp->IOTA - dsp->iConst12) & 524287)])) + (dsp->fRec33[0] * dsp->fVec2[((dsp->IOTA - dsp->iConst13) & 524287)])) + (dsp->fRec36[0] * dsp->fVec2[((dsp->IOTA - dsp->iConst14) & 524287)])) + (dsp->fRec39[0] * dsp->fVec2[((dsp->IOTA - dsp->iConst15) & 524287)])) + (dsp->fRec42[0] * dsp->fVec2[((dsp->IOTA - dsp->iConst16) & 524287)])) + (dsp->fRec45[0] * dsp->fVec2[((dsp->IOTA - dsp->iConst17) & 524287)])) + (dsp->fRec48[0] * dsp->fVec2[((dsp->IOTA - dsp->iConst18) & 524287)]));
			int iTemp35 = (dsp->iRec2[0] == 1);
			dsp->iVec17[0] = iTemp35;
			int iTemp36 = (((dsp->fRec51[1] > 0.0f) | iTemp35) | dsp->iVec17[1]);
			dsp->fRec53[0] = ((dsp->fRec53[1] - dsp->fConst3) * (float)iTemp36);
			dsp->fRec52[0] = ((float)iTemp36 * (dsp->fConst2 + (dsp->fRec52[1] + dsp->fRec53[1])));
			dsp->fRec51[0] = max(0.0f, dsp->fRec52[1]);
			int iTemp37 = (dsp->iRec2[0] == 3);
			dsp->iVec18[0] = iTemp37;
			int iTemp38 = (((dsp->fRec54[1] > 0.0f) | iTemp37) | dsp->iVec18[1]);
			dsp->fRec56[0] = ((dsp->fRec56[1] - dsp->fConst3) * (float)iTemp38);
			dsp->fRec55[0] = ((float)iTemp38 * (dsp->fConst2 + (dsp->fRec55[1] + dsp->fRec56[1])));
			dsp->fRec54[0] = max(0.0f, dsp->fRec55[1]);
			int iTemp39 = (dsp->iRec2[0] == 5);
			dsp->iVec19[0] = iTemp39;
			int iTemp40 = (((dsp->fRec57[1] > 0.0f) | iTemp39) | dsp->iVec19[1]);
			dsp->fRec59[0] = ((dsp->fRec59[1] - dsp->fConst3) * (float)iTemp40);
			dsp->fRec58[0] = ((float)iTemp40 * (dsp->fConst2 + (dsp->fRec58[1] + dsp->fRec59[1])));
			dsp->fRec57[0] = max(0.0f, dsp->fRec58[1]);
			int iTemp41 = (dsp->iRec2[0] == 7);
			dsp->iVec20[0] = iTemp41;
			int iTemp42 = (((dsp->fRec60[1] > 0.0f) | iTemp41) | dsp->iVec20[1]);
			dsp->fRec62[0] = ((dsp->fRec62[1] - dsp->fConst3) * (float)iTemp42);
			dsp->fRec61[0] = ((float)iTemp42 * (dsp->fConst2 + (dsp->fRec61[1] + dsp->fRec62[1])));
			dsp->fRec60[0] = max(0.0f, dsp->fRec61[1]);
			int iTemp43 = (dsp->iRec2[0] == 9);
			dsp->iVec21[0] = iTemp43;
			int iTemp44 = (((dsp->fRec63[1] > 0.0f) | iTemp43) | dsp->iVec21[1]);
			dsp->fRec65[0] = ((dsp->fRec65[1] - dsp->fConst3) * (float)iTemp44);
			dsp->fRec64[0] = ((float)iTemp44 * (dsp->fConst2 + (dsp->fRec64[1] + dsp->fRec65[1])));
			dsp->fRec63[0] = max(0.0f, dsp->fRec64[1]);
			int iTemp45 = (dsp->iRec2[0] == 11);
			dsp->iVec22[0] = iTemp45;
			int iTemp46 = (((dsp->fRec66[1] > 0.0f) | iTemp45) | dsp->iVec22[1]);
			dsp->fRec68[0] = ((dsp->fRec68[1] - dsp->fConst3) * (float)iTemp46);
			dsp->fRec67[0] = ((float)iTemp46 * (dsp->fConst2 + (dsp->fRec67[1] + dsp->fRec68[1])));
			dsp->fRec66[0] = max(0.0f, dsp->fRec67[1]);
			int iTemp47 = (dsp->iRec2[0] == 13);
			dsp->iVec23[0] = iTemp47;
			int iTemp48 = (((dsp->fRec69[1] > 0.0f) | iTemp47) | dsp->iVec23[1]);
			dsp->fRec71[0] = ((dsp->fRec71[1] - dsp->fConst3) * (float)iTemp48);
			dsp->fRec70[0] = ((float)iTemp48 * (dsp->fConst2 + (dsp->fRec70[1] + dsp->fRec71[1])));
			dsp->fRec69[0] = max(0.0f, dsp->fRec70[1]);
			int iTemp49 = (dsp->iRec2[0] == 15);
			dsp->iVec24[0] = iTemp49;
			int iTemp50 = (((dsp->fRec72[1] > 0.0f) | iTemp49) | dsp->iVec24[1]);
			dsp->fRec74[0] = ((dsp->fRec74[1] - dsp->fConst3) * (float)iTemp50);
			dsp->fRec73[0] = ((float)iTemp50 * (dsp->fConst2 + (dsp->fRec73[1] + dsp->fRec74[1])));
			dsp->fRec72[0] = max(0.0f, dsp->fRec73[1]);
			int iTemp51 = (dsp->iRec2[0] == 17);
			dsp->iVec25[0] = iTemp51;
			int iTemp52 = (((dsp->fRec75[1] > 0.0f) | iTemp51) | dsp->iVec25[1]);
			dsp->fRec77[0] = ((dsp->fRec77[1] - dsp->fConst3) * (float)iTemp52);
			dsp->fRec76[0] = ((float)iTemp52 * (dsp->fConst2 + (dsp->fRec76[1] + dsp->fRec77[1])));
			dsp->fRec75[0] = max(0.0f, dsp->fRec76[1]);
			int iTemp53 = (dsp->iRec2[0] == 19);
			dsp->iVec26[0] = iTemp53;
			int iTemp54 = (((dsp->fRec78[1] > 0.0f) | iTemp53) | dsp->iVec26[1]);
			dsp->fRec80[0] = ((dsp->fRec80[1] - dsp->fConst3) * (float)iTemp54);
			dsp->fRec79[0] = ((float)iTemp54 * (dsp->fConst2 + (dsp->fRec79[1] + dsp->fRec80[1])));
			dsp->fRec78[0] = max(0.0f, dsp->fRec79[1]);
			int iTemp55 = (dsp->iRec2[0] == 21);
			dsp->iVec27[0] = iTemp55;
			int iTemp56 = (((dsp->fRec81[1] > 0.0f) | iTemp55) | dsp->iVec27[1]);
			dsp->fRec83[0] = ((dsp->fRec83[1] - dsp->fConst3) * (float)iTemp56);
			dsp->fRec82[0] = ((float)iTemp56 * (dsp->fConst2 + (dsp->fRec82[1] + dsp->fRec83[1])));
			dsp->fRec81[0] = max(0.0f, dsp->fRec82[1]);
			int iTemp57 = (dsp->iRec2[0] == 23);
			dsp->iVec28[0] = iTemp57;
			int iTemp58 = (((dsp->fRec84[1] > 0.0f) | iTemp57) | dsp->iVec28[1]);
			dsp->fRec86[0] = ((dsp->fRec86[1] - dsp->fConst3) * (float)iTemp58);
			dsp->fRec85[0] = ((float)iTemp58 * (dsp->fConst2 + (dsp->fRec85[1] + dsp->fRec86[1])));
			dsp->fRec84[0] = max(0.0f, dsp->fRec85[1]);
			int iTemp59 = (dsp->iRec2[0] == 25);
			dsp->iVec29[0] = iTemp59;
			int iTemp60 = (((dsp->fRec87[1] > 0.0f) | iTemp59) | dsp->iVec29[1]);
			dsp->fRec89[0] = ((dsp->fRec89[1] - dsp->fConst3) * (float)iTemp60);
			dsp->fRec88[0] = ((float)iTemp60 * (dsp->fConst2 + (dsp->fRec88[1] + dsp->fRec89[1])));
			dsp->fRec87[0] = max(0.0f, dsp->fRec88[1]);
			int iTemp61 = (dsp->iRec2[0] == 27);
			dsp->iVec30[0] = iTemp61;
			int iTemp62 = (((dsp->fRec90[1] > 0.0f) | iTemp61) | dsp->iVec30[1]);
			dsp->fRec92[0] = ((dsp->fRec92[1] - dsp->fConst3) * (float)iTemp62);
			dsp->fRec91[0] = ((float)iTemp62 * (dsp->fConst2 + (dsp->fRec91[1] + dsp->fRec92[1])));
			dsp->fRec90[0] = max(0.0f, dsp->fRec91[1]);
			int iTemp63 = (dsp->iRec2[0] == 29);
			dsp->iVec31[0] = iTemp63;
			int iTemp64 = (((dsp->fRec93[1] > 0.0f) | iTemp63) | dsp->iVec31[1]);
			dsp->fRec95[0] = ((dsp->fRec95[1] - dsp->fConst3) * (float)iTemp64);
			dsp->fRec94[0] = ((float)iTemp64 * (dsp->fConst2 + (dsp->fRec94[1] + dsp->fRec95[1])));
			dsp->fRec93[0] = max(0.0f, dsp->fRec94[1]);
			int iTemp65 = (dsp->iRec2[0] == 31);
			dsp->iVec32[0] = iTemp65;
			int iTemp66 = (((dsp->fRec96[1] > 0.0f) | iTemp65) | dsp->iVec32[1]);
			dsp->fRec98[0] = ((dsp->fRec98[1] - dsp->fConst3) * (float)iTemp66);
			dsp->fRec97[0] = ((float)iTemp66 * (dsp->fConst2 + (dsp->fRec97[1] + dsp->fRec98[1])));
			dsp->fRec96[0] = max(0.0f, dsp->fRec97[1]);
			output1[i] = (FAUSTFLOAT)((((((((((((((((dsp->fRec51[0] * dsp->fVec2[((dsp->IOTA - dsp->iConst19) & 524287)]) + (dsp->fRec54[0] * dsp->fVec2[((dsp->IOTA - dsp->iConst20) & 524287)])) + (dsp->fRec57[0] * dsp->fVec2[((dsp->IOTA - dsp->iConst21) & 524287)])) + (dsp->fRec60[0] * dsp->fVec2[((dsp->IOTA - dsp->iConst22) & 524287)])) + (dsp->fRec63[0] * dsp->fVec2[((dsp->IOTA - dsp->iConst23) & 524287)])) + (dsp->fRec66[0] * dsp->fVec2[((dsp->IOTA - dsp->iConst24) & 524287)])) + (dsp->fRec69[0] * dsp->fVec2[((dsp->IOTA - dsp->iConst25) & 524287)])) + (dsp->fRec72[0] * dsp->fVec2[((dsp->IOTA - dsp->iConst26) & 524287)])) + (dsp->fRec75[0] * dsp->fVec2[((dsp->IOTA - dsp->iConst27) & 524287)])) + (dsp->fRec78[0] * dsp->fVec2[((dsp->IOTA - dsp->iConst28) & 524287)])) + (dsp->fRec81[0] * dsp->fVec2[((dsp->IOTA - dsp->iConst29) & 524287)])) + (dsp->fRec84[0] * dsp->fVec2[((dsp->IOTA - dsp->iConst30) & 524287)])) + (dsp->fRec87[0] * dsp->fVec2[((dsp->IOTA - dsp->iConst31) & 524287)])) + (dsp->fRec90[0] * dsp->fVec2[((dsp->IOTA - dsp->iConst32) & 524287)])) + (dsp->fRec93[0] * dsp->fVec2[((dsp->IOTA - dsp->iConst33) & 524287)])) + (dsp->fRec96[0] * dsp->fVec2[((dsp->IOTA - dsp->iConst34) & 524287)]));
			dsp->iRec3[1] = dsp->iRec3[0];
			dsp->iRec4[1] = dsp->iRec4[0];
			dsp->iRec2[1] = dsp->iRec2[0];
			dsp->iVec0[1] = dsp->iVec0[0];
			dsp->fRec5[1] = dsp->fRec5[0];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->iVec1[1] = dsp->iVec1[0];
			dsp->fRec8[1] = dsp->fRec8[0];
			dsp->fRec7[1] = dsp->fRec7[0];
			dsp->fRec6[1] = dsp->fRec6[0];
			dsp->IOTA = (dsp->IOTA + 1);
			dsp->iVec3[1] = dsp->iVec3[0];
			dsp->fRec11[1] = dsp->fRec11[0];
			dsp->fRec10[1] = dsp->fRec10[0];
			dsp->fRec9[1] = dsp->fRec9[0];
			dsp->iVec4[1] = dsp->iVec4[0];
			dsp->fRec14[1] = dsp->fRec14[0];
			dsp->fRec13[1] = dsp->fRec13[0];
			dsp->fRec12[1] = dsp->fRec12[0];
			dsp->iVec5[1] = dsp->iVec5[0];
			dsp->fRec17[1] = dsp->fRec17[0];
			dsp->fRec16[1] = dsp->fRec16[0];
			dsp->fRec15[1] = dsp->fRec15[0];
			dsp->iVec6[1] = dsp->iVec6[0];
			dsp->fRec20[1] = dsp->fRec20[0];
			dsp->fRec19[1] = dsp->fRec19[0];
			dsp->fRec18[1] = dsp->fRec18[0];
			dsp->iVec7[1] = dsp->iVec7[0];
			dsp->fRec23[1] = dsp->fRec23[0];
			dsp->fRec22[1] = dsp->fRec22[0];
			dsp->fRec21[1] = dsp->fRec21[0];
			dsp->iVec8[1] = dsp->iVec8[0];
			dsp->fRec26[1] = dsp->fRec26[0];
			dsp->fRec25[1] = dsp->fRec25[0];
			dsp->fRec24[1] = dsp->fRec24[0];
			dsp->iVec9[1] = dsp->iVec9[0];
			dsp->fRec29[1] = dsp->fRec29[0];
			dsp->fRec28[1] = dsp->fRec28[0];
			dsp->fRec27[1] = dsp->fRec27[0];
			dsp->iVec10[1] = dsp->iVec10[0];
			dsp->fRec32[1] = dsp->fRec32[0];
			dsp->fRec31[1] = dsp->fRec31[0];
			dsp->fRec30[1] = dsp->fRec30[0];
			dsp->iVec11[1] = dsp->iVec11[0];
			dsp->fRec35[1] = dsp->fRec35[0];
			dsp->fRec34[1] = dsp->fRec34[0];
			dsp->fRec33[1] = dsp->fRec33[0];
			dsp->iVec12[1] = dsp->iVec12[0];
			dsp->fRec38[1] = dsp->fRec38[0];
			dsp->fRec37[1] = dsp->fRec37[0];
			dsp->fRec36[1] = dsp->fRec36[0];
			dsp->iVec13[1] = dsp->iVec13[0];
			dsp->fRec41[1] = dsp->fRec41[0];
			dsp->fRec40[1] = dsp->fRec40[0];
			dsp->fRec39[1] = dsp->fRec39[0];
			dsp->iVec14[1] = dsp->iVec14[0];
			dsp->fRec44[1] = dsp->fRec44[0];
			dsp->fRec43[1] = dsp->fRec43[0];
			dsp->fRec42[1] = dsp->fRec42[0];
			dsp->iVec15[1] = dsp->iVec15[0];
			dsp->fRec47[1] = dsp->fRec47[0];
			dsp->fRec46[1] = dsp->fRec46[0];
			dsp->fRec45[1] = dsp->fRec45[0];
			dsp->iVec16[1] = dsp->iVec16[0];
			dsp->fRec50[1] = dsp->fRec50[0];
			dsp->fRec49[1] = dsp->fRec49[0];
			dsp->fRec48[1] = dsp->fRec48[0];
			dsp->iVec17[1] = dsp->iVec17[0];
			dsp->fRec53[1] = dsp->fRec53[0];
			dsp->fRec52[1] = dsp->fRec52[0];
			dsp->fRec51[1] = dsp->fRec51[0];
			dsp->iVec18[1] = dsp->iVec18[0];
			dsp->fRec56[1] = dsp->fRec56[0];
			dsp->fRec55[1] = dsp->fRec55[0];
			dsp->fRec54[1] = dsp->fRec54[0];
			dsp->iVec19[1] = dsp->iVec19[0];
			dsp->fRec59[1] = dsp->fRec59[0];
			dsp->fRec58[1] = dsp->fRec58[0];
			dsp->fRec57[1] = dsp->fRec57[0];
			dsp->iVec20[1] = dsp->iVec20[0];
			dsp->fRec62[1] = dsp->fRec62[0];
			dsp->fRec61[1] = dsp->fRec61[0];
			dsp->fRec60[1] = dsp->fRec60[0];
			dsp->iVec21[1] = dsp->iVec21[0];
			dsp->fRec65[1] = dsp->fRec65[0];
			dsp->fRec64[1] = dsp->fRec64[0];
			dsp->fRec63[1] = dsp->fRec63[0];
			dsp->iVec22[1] = dsp->iVec22[0];
			dsp->fRec68[1] = dsp->fRec68[0];
			dsp->fRec67[1] = dsp->fRec67[0];
			dsp->fRec66[1] = dsp->fRec66[0];
			dsp->iVec23[1] = dsp->iVec23[0];
			dsp->fRec71[1] = dsp->fRec71[0];
			dsp->fRec70[1] = dsp->fRec70[0];
			dsp->fRec69[1] = dsp->fRec69[0];
			dsp->iVec24[1] = dsp->iVec24[0];
			dsp->fRec74[1] = dsp->fRec74[0];
			dsp->fRec73[1] = dsp->fRec73[0];
			dsp->fRec72[1] = dsp->fRec72[0];
			dsp->iVec25[1] = dsp->iVec25[0];
			dsp->fRec77[1] = dsp->fRec77[0];
			dsp->fRec76[1] = dsp->fRec76[0];
			dsp->fRec75[1] = dsp->fRec75[0];
			dsp->iVec26[1] = dsp->iVec26[0];
			dsp->fRec80[1] = dsp->fRec80[0];
			dsp->fRec79[1] = dsp->fRec79[0];
			dsp->fRec78[1] = dsp->fRec78[0];
			dsp->iVec27[1] = dsp->iVec27[0];
			dsp->fRec83[1] = dsp->fRec83[0];
			dsp->fRec82[1] = dsp->fRec82[0];
			dsp->fRec81[1] = dsp->fRec81[0];
			dsp->iVec28[1] = dsp->iVec28[0];
			dsp->fRec86[1] = dsp->fRec86[0];
			dsp->fRec85[1] = dsp->fRec85[0];
			dsp->fRec84[1] = dsp->fRec84[0];
			dsp->iVec29[1] = dsp->iVec29[0];
			dsp->fRec89[1] = dsp->fRec89[0];
			dsp->fRec88[1] = dsp->fRec88[0];
			dsp->fRec87[1] = dsp->fRec87[0];
			dsp->iVec30[1] = dsp->iVec30[0];
			dsp->fRec92[1] = dsp->fRec92[0];
			dsp->fRec91[1] = dsp->fRec91[0];
			dsp->fRec90[1] = dsp->fRec90[0];
			dsp->iVec31[1] = dsp->iVec31[0];
			dsp->fRec95[1] = dsp->fRec95[0];
			dsp->fRec94[1] = dsp->fRec94[0];
			dsp->fRec93[1] = dsp->fRec93[0];
			dsp->iVec32[1] = dsp->iVec32[0];
			dsp->fRec98[1] = dsp->fRec98[0];
			dsp->fRec97[1] = dsp->fRec97[0];
			dsp->fRec96[1] = dsp->fRec96[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
