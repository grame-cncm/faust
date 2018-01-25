/* ------------------------------------------------------------
author: "JOS, Revised by RM"
name: "zitaRev"
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
	
	FAUSTFLOAT fVslider0;
	float fRec0[2];
	int IOTA;
	float fVec0[16384];
	FAUSTFLOAT fVslider1;
	float fRec1[2];
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT fVslider5;
	float fConst2;
	float fConst3;
	FAUSTFLOAT fVslider6;
	float fConst4;
	FAUSTFLOAT fVslider7;
	FAUSTFLOAT fVslider8;
	float fConst5;
	FAUSTFLOAT fVslider9;
	float fRec15[2];
	float fRec14[2];
	float fVec1[32768];
	float fConst6;
	int iConst7;
	float fVec2[16384];
	float fConst8;
	FAUSTFLOAT fVslider10;
	float fVec3[2048];
	int iConst9;
	float fRec12[2];
	float fConst10;
	float fConst11;
	float fRec19[2];
	float fRec18[2];
	float fVec4[32768];
	float fConst12;
	int iConst13;
	float fVec5[4096];
	int iConst14;
	float fRec16[2];
	float fConst15;
	float fConst16;
	float fRec23[2];
	float fRec22[2];
	float fVec6[16384];
	float fConst17;
	int iConst18;
	float fVec7[4096];
	int iConst19;
	float fRec20[2];
	float fConst20;
	float fConst21;
	float fRec27[2];
	float fRec26[2];
	float fVec8[32768];
	float fConst22;
	int iConst23;
	float fVec9[4096];
	int iConst24;
	float fRec24[2];
	float fConst25;
	float fConst26;
	float fRec31[2];
	float fRec30[2];
	float fVec10[16384];
	float fConst27;
	int iConst28;
	float fVec11[2048];
	int iConst29;
	float fRec28[2];
	float fConst30;
	float fConst31;
	float fRec35[2];
	float fRec34[2];
	float fVec12[16384];
	float fConst32;
	int iConst33;
	float fVec13[4096];
	int iConst34;
	float fRec32[2];
	float fConst35;
	float fConst36;
	float fRec39[2];
	float fRec38[2];
	float fVec14[16384];
	float fConst37;
	int iConst38;
	float fVec15[4096];
	int iConst39;
	float fRec36[2];
	float fConst40;
	float fConst41;
	float fRec43[2];
	float fRec42[2];
	float fVec16[16384];
	float fConst42;
	int iConst43;
	float fVec17[2048];
	int iConst44;
	float fRec40[2];
	float fRec4[3];
	float fRec5[3];
	float fRec6[3];
	float fRec7[3];
	float fRec8[3];
	float fRec9[3];
	float fRec10[3];
	float fRec11[3];
	float fRec3[3];
	float fRec2[3];
	float fRec45[3];
	float fRec44[3];
	
} mydsp;

mydsp* newmydsp() { 
	mydsp* dsp = (mydsp*)malloc(sizeof(mydsp));
	return dsp;
}

void deletemydsp(mydsp* dsp) { 
	free(dsp);
}

void metadatamydsp(MetaGlue* m) { 
	m->declare(m->metaInterface, "author", "JOS, Revised by RM");
	m->declare(m->metaInterface, "basics.lib/name", "Faust Basic Element Library");
	m->declare(m->metaInterface, "basics.lib/version", "0.0");
	m->declare(m->metaInterface, "delays.lib/name", "Faust Delay Library");
	m->declare(m->metaInterface, "delays.lib/version", "0.0");
	m->declare(m->metaInterface, "description", "Example GUI for `zita_rev1_stereo` (mostly following the Linux `zita-rev1` GUI).");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "zitaRev");
	m->declare(m->metaInterface, "reverbs.lib/name", "Faust Reverb Library");
	m->declare(m->metaInterface, "reverbs.lib/version", "0.0");
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
	dsp->fVslider0 = (FAUSTFLOAT)-20.0f;
	dsp->fVslider1 = (FAUSTFLOAT)0.0f;
	dsp->fVslider2 = (FAUSTFLOAT)1500.0f;
	dsp->fVslider3 = (FAUSTFLOAT)0.0f;
	dsp->fVslider4 = (FAUSTFLOAT)315.0f;
	dsp->fVslider5 = (FAUSTFLOAT)0.0f;
	dsp->fVslider6 = (FAUSTFLOAT)2.0f;
	dsp->fVslider7 = (FAUSTFLOAT)6000.0f;
	dsp->fVslider8 = (FAUSTFLOAT)3.0f;
	dsp->fVslider9 = (FAUSTFLOAT)200.0f;
	dsp->fVslider10 = (FAUSTFLOAT)60.0f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			dsp->fRec0[l0] = 0.0f;
			
		}
		
	}
	dsp->IOTA = 0;
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 16384); l1 = (l1 + 1)) {
			dsp->fVec0[l1] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			dsp->fRec1[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			dsp->fRec15[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			dsp->fRec14[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 32768); l5 = (l5 + 1)) {
			dsp->fVec1[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 16384); l6 = (l6 + 1)) {
			dsp->fVec2[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2048); l7 = (l7 + 1)) {
			dsp->fVec3[l7] = 0.0f;
			
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
			dsp->fRec19[l9] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			dsp->fRec18[l10] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 32768); l11 = (l11 + 1)) {
			dsp->fVec4[l11] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 4096); l12 = (l12 + 1)) {
			dsp->fVec5[l12] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l13;
		for (l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			dsp->fRec16[l13] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l14;
		for (l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			dsp->fRec23[l14] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l15;
		for (l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			dsp->fRec22[l15] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l16;
		for (l16 = 0; (l16 < 16384); l16 = (l16 + 1)) {
			dsp->fVec6[l16] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l17;
		for (l17 = 0; (l17 < 4096); l17 = (l17 + 1)) {
			dsp->fVec7[l17] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l18;
		for (l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			dsp->fRec20[l18] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l19;
		for (l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			dsp->fRec27[l19] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l20;
		for (l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			dsp->fRec26[l20] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l21;
		for (l21 = 0; (l21 < 32768); l21 = (l21 + 1)) {
			dsp->fVec8[l21] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l22;
		for (l22 = 0; (l22 < 4096); l22 = (l22 + 1)) {
			dsp->fVec9[l22] = 0.0f;
			
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
		for (l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			dsp->fRec31[l24] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l25;
		for (l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			dsp->fRec30[l25] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l26;
		for (l26 = 0; (l26 < 16384); l26 = (l26 + 1)) {
			dsp->fVec10[l26] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l27;
		for (l27 = 0; (l27 < 2048); l27 = (l27 + 1)) {
			dsp->fVec11[l27] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l28;
		for (l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			dsp->fRec28[l28] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l29;
		for (l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			dsp->fRec35[l29] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l30;
		for (l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			dsp->fRec34[l30] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l31;
		for (l31 = 0; (l31 < 16384); l31 = (l31 + 1)) {
			dsp->fVec12[l31] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l32;
		for (l32 = 0; (l32 < 4096); l32 = (l32 + 1)) {
			dsp->fVec13[l32] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l33;
		for (l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			dsp->fRec32[l33] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l34;
		for (l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			dsp->fRec39[l34] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l35;
		for (l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			dsp->fRec38[l35] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l36;
		for (l36 = 0; (l36 < 16384); l36 = (l36 + 1)) {
			dsp->fVec14[l36] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l37;
		for (l37 = 0; (l37 < 4096); l37 = (l37 + 1)) {
			dsp->fVec15[l37] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l38;
		for (l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			dsp->fRec36[l38] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l39;
		for (l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			dsp->fRec43[l39] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l40;
		for (l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			dsp->fRec42[l40] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l41;
		for (l41 = 0; (l41 < 16384); l41 = (l41 + 1)) {
			dsp->fVec16[l41] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l42;
		for (l42 = 0; (l42 < 2048); l42 = (l42 + 1)) {
			dsp->fVec17[l42] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l43;
		for (l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			dsp->fRec40[l43] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l44;
		for (l44 = 0; (l44 < 3); l44 = (l44 + 1)) {
			dsp->fRec4[l44] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l45;
		for (l45 = 0; (l45 < 3); l45 = (l45 + 1)) {
			dsp->fRec5[l45] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l46;
		for (l46 = 0; (l46 < 3); l46 = (l46 + 1)) {
			dsp->fRec6[l46] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l47;
		for (l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			dsp->fRec7[l47] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l48;
		for (l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			dsp->fRec8[l48] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l49;
		for (l49 = 0; (l49 < 3); l49 = (l49 + 1)) {
			dsp->fRec9[l49] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l50;
		for (l50 = 0; (l50 < 3); l50 = (l50 + 1)) {
			dsp->fRec10[l50] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l51;
		for (l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			dsp->fRec11[l51] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l52;
		for (l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			dsp->fRec3[l52] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l53;
		for (l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			dsp->fRec2[l53] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l54;
		for (l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			dsp->fRec45[l54] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l55;
		for (l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			dsp->fRec44[l55] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = (6.28318548f / dsp->fConst0);
	dsp->fConst2 = floorf(((0.219990999f * dsp->fConst0) + 0.5f));
	dsp->fConst3 = ((0.0f - (6.90775537f * dsp->fConst2)) / dsp->fConst0);
	dsp->fConst4 = (6.28318548f / dsp->fConst0);
	dsp->fConst5 = (3.14159274f / dsp->fConst0);
	dsp->fConst6 = floorf(((0.0191229992f * dsp->fConst0) + 0.5f));
	dsp->iConst7 = (int)min(16384.0f, max(0.0f, (dsp->fConst2 - dsp->fConst6)));
	dsp->fConst8 = (0.00100000005f * dsp->fConst0);
	dsp->iConst9 = (int)min(1024.0f, max(0.0f, (dsp->fConst6 + -1.0f)));
	dsp->fConst10 = floorf(((0.256891012f * dsp->fConst0) + 0.5f));
	dsp->fConst11 = ((0.0f - (6.90775537f * dsp->fConst10)) / dsp->fConst0);
	dsp->fConst12 = floorf(((0.0273330007f * dsp->fConst0) + 0.5f));
	dsp->iConst13 = (int)min(16384.0f, max(0.0f, (dsp->fConst10 - dsp->fConst12)));
	dsp->iConst14 = (int)min(2048.0f, max(0.0f, (dsp->fConst12 + -1.0f)));
	dsp->fConst15 = floorf(((0.192303002f * dsp->fConst0) + 0.5f));
	dsp->fConst16 = ((0.0f - (6.90775537f * dsp->fConst15)) / dsp->fConst0);
	dsp->fConst17 = floorf(((0.0292910002f * dsp->fConst0) + 0.5f));
	dsp->iConst18 = (int)min(8192.0f, max(0.0f, (dsp->fConst15 - dsp->fConst17)));
	dsp->iConst19 = (int)min(2048.0f, max(0.0f, (dsp->fConst17 + -1.0f)));
	dsp->fConst20 = floorf(((0.210389003f * dsp->fConst0) + 0.5f));
	dsp->fConst21 = ((0.0f - (6.90775537f * dsp->fConst20)) / dsp->fConst0);
	dsp->fConst22 = floorf(((0.0244210009f * dsp->fConst0) + 0.5f));
	dsp->iConst23 = (int)min(16384.0f, max(0.0f, (dsp->fConst20 - dsp->fConst22)));
	dsp->iConst24 = (int)min(2048.0f, max(0.0f, (dsp->fConst22 + -1.0f)));
	dsp->fConst25 = floorf(((0.125f * dsp->fConst0) + 0.5f));
	dsp->fConst26 = ((0.0f - (6.90775537f * dsp->fConst25)) / dsp->fConst0);
	dsp->fConst27 = floorf(((0.0134579996f * dsp->fConst0) + 0.5f));
	dsp->iConst28 = (int)min(8192.0f, max(0.0f, (dsp->fConst25 - dsp->fConst27)));
	dsp->iConst29 = (int)min(1024.0f, max(0.0f, (dsp->fConst27 + -1.0f)));
	dsp->fConst30 = floorf(((0.127837002f * dsp->fConst0) + 0.5f));
	dsp->fConst31 = ((0.0f - (6.90775537f * dsp->fConst30)) / dsp->fConst0);
	dsp->fConst32 = floorf(((0.0316039994f * dsp->fConst0) + 0.5f));
	dsp->iConst33 = (int)min(8192.0f, max(0.0f, (dsp->fConst30 - dsp->fConst32)));
	dsp->iConst34 = (int)min(2048.0f, max(0.0f, (dsp->fConst32 + -1.0f)));
	dsp->fConst35 = floorf(((0.174713001f * dsp->fConst0) + 0.5f));
	dsp->fConst36 = ((0.0f - (6.90775537f * dsp->fConst35)) / dsp->fConst0);
	dsp->fConst37 = floorf(((0.0229039993f * dsp->fConst0) + 0.5f));
	dsp->iConst38 = (int)min(8192.0f, max(0.0f, (dsp->fConst35 - dsp->fConst37)));
	dsp->iConst39 = (int)min(2048.0f, max(0.0f, (dsp->fConst37 + -1.0f)));
	dsp->fConst40 = floorf(((0.153128996f * dsp->fConst0) + 0.5f));
	dsp->fConst41 = ((0.0f - (6.90775537f * dsp->fConst40)) / dsp->fConst0);
	dsp->fConst42 = floorf(((0.0203460008f * dsp->fConst0) + 0.5f));
	dsp->iConst43 = (int)min(8192.0f, max(0.0f, (dsp->fConst40 - dsp->fConst42)));
	dsp->iConst44 = (int)min(1024.0f, max(0.0f, (dsp->fConst42 + -1.0f)));
	
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
	ui_interface->declare(ui_interface->uiInterface, 0, "0", "");
	ui_interface->declare(ui_interface->uiInterface, 0, "tooltip", "~ ZITA REV1 FEEDBACK DELAY NETWORK (FDN) & SCHROEDER  ALLPASS-COMB REVERBERATOR (8x8). See Faust's reverbs.lib for documentation and  references");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "Zita_Rev1");
	ui_interface->declare(ui_interface->uiInterface, 0, "1", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "Input");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider10, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider10, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider10, "tooltip", "Delay in ms   before reverberation begins");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider10, "unit", "ms");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "In Delay", &dsp->fVslider10, 60.0f, 20.0f, 100.0f, 1.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "2", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "Decay Times in Bands (see tooltips)");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider9, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider9, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider9, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider9, "tooltip", "Crossover frequency (Hz) separating low and middle frequencies");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider9, "unit", "Hz");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "LF X", &dsp->fVslider9, 200.0f, 50.0f, 1000.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider8, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider8, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider8, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider8, "tooltip", "T60 = time (in seconds) to decay 60dB in low-frequency band");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider8, "unit", "s");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Low RT60", &dsp->fVslider8, 3.0f, 1.0f, 8.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider6, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider6, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider6, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider6, "tooltip", "T60 = time (in seconds) to decay 60dB in middle band");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider6, "unit", "s");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Mid RT60", &dsp->fVslider6, 2.0f, 1.0f, 8.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider7, "4", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider7, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider7, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider7, "tooltip", "Frequency (Hz) at which the high-frequency T60 is half the middle-band's T60");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider7, "unit", "Hz");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "HF Damping", &dsp->fVslider7, 6000.0f, 1500.0f, 23520.0f, 1.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "3", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "RM Peaking Equalizer 1");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider4, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider4, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider4, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider4, "tooltip", "Center-frequency of second-order Regalia-Mitra peaking equalizer section 1");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider4, "unit", "Hz");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Eq1 Freq", &dsp->fVslider4, 315.0f, 40.0f, 2500.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider5, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider5, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider5, "tooltip", "Peak level   in dB of second-order Regalia-Mitra peaking equalizer section 1");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider5, "unit", "dB");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Eq1 Level", &dsp->fVslider5, 0.0f, -15.0f, 15.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "4", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "RM Peaking Equalizer 2");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider2, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider2, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider2, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider2, "tooltip", "Center-frequency of second-order Regalia-Mitra peaking equalizer section 2");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider2, "unit", "Hz");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Eq2 Freq", &dsp->fVslider2, 1500.0f, 160.0f, 10000.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider3, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider3, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider3, "tooltip", "Peak level   in dB of second-order Regalia-Mitra peaking equalizer section 2");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider3, "unit", "dB");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Eq2 Level", &dsp->fVslider3, 0.0f, -15.0f, 15.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "5", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "Output");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider1, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider1, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider1, "tooltip", "-1 = dry, 1 = wet");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Dry/Wet Mix", &dsp->fVslider1, 0.0f, -1.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider0, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider0, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider0, "tooltip", "Output scale   factor");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider0, "unit", "dB");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Level", &dsp->fVslider0, -20.0f, -70.0f, 40.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* input0 = inputs[0];
	FAUSTFLOAT* input1 = inputs[1];
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	float fSlow0 = (0.00100000005f * powf(10.0f, (0.0500000007f * (float)dsp->fVslider0)));
	float fSlow1 = (0.00100000005f * (float)dsp->fVslider1);
	float fSlow2 = (float)dsp->fVslider2;
	float fSlow3 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider3));
	float fSlow4 = (dsp->fConst1 * (fSlow2 / sqrtf(max(0.0f, fSlow3))));
	float fSlow5 = ((1.0f - fSlow4) / (fSlow4 + 1.0f));
	float fSlow6 = (float)dsp->fVslider4;
	float fSlow7 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider5));
	float fSlow8 = (dsp->fConst1 * (fSlow6 / sqrtf(max(0.0f, fSlow7))));
	float fSlow9 = ((1.0f - fSlow8) / (fSlow8 + 1.0f));
	float fSlow10 = (float)dsp->fVslider6;
	float fSlow11 = expf((dsp->fConst3 / fSlow10));
	float fSlow12 = mydsp_faustpower2_f(fSlow11);
	float fSlow13 = cosf((dsp->fConst4 * (float)dsp->fVslider7));
	float fSlow14 = (1.0f - (fSlow12 * fSlow13));
	float fSlow15 = (1.0f - fSlow12);
	float fSlow16 = (fSlow14 / fSlow15);
	float fSlow17 = sqrtf(max(0.0f, ((mydsp_faustpower2_f(fSlow14) / mydsp_faustpower2_f(fSlow15)) + -1.0f)));
	float fSlow18 = (fSlow16 - fSlow17);
	float fSlow19 = (fSlow11 * (fSlow17 + (1.0f - fSlow16)));
	float fSlow20 = (float)dsp->fVslider8;
	float fSlow21 = ((expf((dsp->fConst3 / fSlow20)) / fSlow11) + -1.0f);
	float fSlow22 = (1.0f / tanf((dsp->fConst5 * (float)dsp->fVslider9)));
	float fSlow23 = (fSlow22 + 1.0f);
	float fSlow24 = (0.0f - ((1.0f - fSlow22) / fSlow23));
	float fSlow25 = (1.0f / fSlow23);
	int iSlow26 = (int)min(8192.0f, max(0.0f, (dsp->fConst8 * (float)dsp->fVslider10)));
	float fSlow27 = expf((dsp->fConst11 / fSlow10));
	float fSlow28 = mydsp_faustpower2_f(fSlow27);
	float fSlow29 = (1.0f - (fSlow13 * fSlow28));
	float fSlow30 = (1.0f - fSlow28);
	float fSlow31 = (fSlow29 / fSlow30);
	float fSlow32 = sqrtf(max(0.0f, ((mydsp_faustpower2_f(fSlow29) / mydsp_faustpower2_f(fSlow30)) + -1.0f)));
	float fSlow33 = (fSlow31 - fSlow32);
	float fSlow34 = (fSlow27 * (fSlow32 + (1.0f - fSlow31)));
	float fSlow35 = ((expf((dsp->fConst11 / fSlow20)) / fSlow27) + -1.0f);
	float fSlow36 = expf((dsp->fConst16 / fSlow10));
	float fSlow37 = mydsp_faustpower2_f(fSlow36);
	float fSlow38 = (1.0f - (fSlow13 * fSlow37));
	float fSlow39 = (1.0f - fSlow37);
	float fSlow40 = (fSlow38 / fSlow39);
	float fSlow41 = sqrtf(max(0.0f, ((mydsp_faustpower2_f(fSlow38) / mydsp_faustpower2_f(fSlow39)) + -1.0f)));
	float fSlow42 = (fSlow40 - fSlow41);
	float fSlow43 = (fSlow36 * (fSlow41 + (1.0f - fSlow40)));
	float fSlow44 = ((expf((dsp->fConst16 / fSlow20)) / fSlow36) + -1.0f);
	float fSlow45 = expf((dsp->fConst21 / fSlow10));
	float fSlow46 = mydsp_faustpower2_f(fSlow45);
	float fSlow47 = (1.0f - (fSlow13 * fSlow46));
	float fSlow48 = (1.0f - fSlow46);
	float fSlow49 = (fSlow47 / fSlow48);
	float fSlow50 = sqrtf(max(0.0f, ((mydsp_faustpower2_f(fSlow47) / mydsp_faustpower2_f(fSlow48)) + -1.0f)));
	float fSlow51 = (fSlow49 - fSlow50);
	float fSlow52 = (fSlow45 * (fSlow50 + (1.0f - fSlow49)));
	float fSlow53 = ((expf((dsp->fConst21 / fSlow20)) / fSlow45) + -1.0f);
	float fSlow54 = expf((dsp->fConst26 / fSlow10));
	float fSlow55 = mydsp_faustpower2_f(fSlow54);
	float fSlow56 = (1.0f - (fSlow13 * fSlow55));
	float fSlow57 = (1.0f - fSlow55);
	float fSlow58 = (fSlow56 / fSlow57);
	float fSlow59 = sqrtf(max(0.0f, ((mydsp_faustpower2_f(fSlow56) / mydsp_faustpower2_f(fSlow57)) + -1.0f)));
	float fSlow60 = (fSlow58 - fSlow59);
	float fSlow61 = (fSlow54 * (fSlow59 + (1.0f - fSlow58)));
	float fSlow62 = ((expf((dsp->fConst26 / fSlow20)) / fSlow54) + -1.0f);
	float fSlow63 = expf((dsp->fConst31 / fSlow10));
	float fSlow64 = mydsp_faustpower2_f(fSlow63);
	float fSlow65 = (1.0f - (fSlow13 * fSlow64));
	float fSlow66 = (1.0f - fSlow64);
	float fSlow67 = (fSlow65 / fSlow66);
	float fSlow68 = sqrtf(max(0.0f, ((mydsp_faustpower2_f(fSlow65) / mydsp_faustpower2_f(fSlow66)) + -1.0f)));
	float fSlow69 = (fSlow67 - fSlow68);
	float fSlow70 = (fSlow63 * (fSlow68 + (1.0f - fSlow67)));
	float fSlow71 = ((expf((dsp->fConst31 / fSlow20)) / fSlow63) + -1.0f);
	float fSlow72 = expf((dsp->fConst36 / fSlow10));
	float fSlow73 = mydsp_faustpower2_f(fSlow72);
	float fSlow74 = (1.0f - (fSlow13 * fSlow73));
	float fSlow75 = (1.0f - fSlow73);
	float fSlow76 = (fSlow74 / fSlow75);
	float fSlow77 = sqrtf(max(0.0f, ((mydsp_faustpower2_f(fSlow74) / mydsp_faustpower2_f(fSlow75)) + -1.0f)));
	float fSlow78 = (fSlow76 - fSlow77);
	float fSlow79 = (fSlow72 * (fSlow77 + (1.0f - fSlow76)));
	float fSlow80 = ((expf((dsp->fConst36 / fSlow20)) / fSlow72) + -1.0f);
	float fSlow81 = expf((dsp->fConst41 / fSlow10));
	float fSlow82 = mydsp_faustpower2_f(fSlow81);
	float fSlow83 = (1.0f - (fSlow13 * fSlow82));
	float fSlow84 = (1.0f - fSlow82);
	float fSlow85 = (fSlow83 / fSlow84);
	float fSlow86 = sqrtf(max(0.0f, ((mydsp_faustpower2_f(fSlow83) / mydsp_faustpower2_f(fSlow84)) + -1.0f)));
	float fSlow87 = (fSlow85 - fSlow86);
	float fSlow88 = (fSlow81 * (fSlow86 + (1.0f - fSlow85)));
	float fSlow89 = ((expf((dsp->fConst41 / fSlow20)) / fSlow81) + -1.0f);
	float fSlow90 = ((0.0f - cosf((dsp->fConst1 * fSlow6))) * (fSlow9 + 1.0f));
	float fSlow91 = ((0.0f - cosf((dsp->fConst1 * fSlow2))) * (fSlow5 + 1.0f));
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->fRec0[0] = (fSlow0 + (0.999000013f * dsp->fRec0[1]));
			float fTemp0 = (float)input0[i];
			dsp->fVec0[(dsp->IOTA & 16383)] = fTemp0;
			dsp->fRec1[0] = (fSlow1 + (0.999000013f * dsp->fRec1[1]));
			float fTemp1 = (dsp->fRec1[0] + 1.0f);
			float fTemp2 = (1.0f - (0.5f * fTemp1));
			dsp->fRec15[0] = ((fSlow24 * dsp->fRec15[1]) + (fSlow25 * (dsp->fRec11[1] + dsp->fRec11[2])));
			dsp->fRec14[0] = ((fSlow18 * dsp->fRec14[1]) + (fSlow19 * (dsp->fRec11[1] + (fSlow21 * dsp->fRec15[0]))));
			dsp->fVec1[(dsp->IOTA & 32767)] = ((0.353553385f * dsp->fRec14[0]) + 9.99999968e-21f);
			float fTemp3 = (float)input1[i];
			dsp->fVec2[(dsp->IOTA & 16383)] = fTemp3;
			float fTemp4 = (0.300000012f * dsp->fVec2[((dsp->IOTA - iSlow26) & 16383)]);
			float fTemp5 = (((0.600000024f * dsp->fRec12[1]) + dsp->fVec1[((dsp->IOTA - dsp->iConst7) & 32767)]) - fTemp4);
			dsp->fVec3[(dsp->IOTA & 2047)] = fTemp5;
			dsp->fRec12[0] = dsp->fVec3[((dsp->IOTA - dsp->iConst9) & 2047)];
			float fRec13 = (0.0f - (0.600000024f * fTemp5));
			dsp->fRec19[0] = ((fSlow24 * dsp->fRec19[1]) + (fSlow25 * (dsp->fRec7[1] + dsp->fRec7[2])));
			dsp->fRec18[0] = ((fSlow33 * dsp->fRec18[1]) + (fSlow34 * (dsp->fRec7[1] + (fSlow35 * dsp->fRec19[0]))));
			dsp->fVec4[(dsp->IOTA & 32767)] = ((0.353553385f * dsp->fRec18[0]) + 9.99999968e-21f);
			float fTemp6 = (((0.600000024f * dsp->fRec16[1]) + dsp->fVec4[((dsp->IOTA - dsp->iConst13) & 32767)]) - fTemp4);
			dsp->fVec5[(dsp->IOTA & 4095)] = fTemp6;
			dsp->fRec16[0] = dsp->fVec5[((dsp->IOTA - dsp->iConst14) & 4095)];
			float fRec17 = (0.0f - (0.600000024f * fTemp6));
			dsp->fRec23[0] = ((fSlow24 * dsp->fRec23[1]) + (fSlow25 * (dsp->fRec9[1] + dsp->fRec9[2])));
			dsp->fRec22[0] = ((fSlow42 * dsp->fRec22[1]) + (fSlow43 * (dsp->fRec9[1] + (fSlow44 * dsp->fRec23[0]))));
			dsp->fVec6[(dsp->IOTA & 16383)] = ((0.353553385f * dsp->fRec22[0]) + 9.99999968e-21f);
			float fTemp7 = (dsp->fVec6[((dsp->IOTA - dsp->iConst18) & 16383)] + (fTemp4 + (0.600000024f * dsp->fRec20[1])));
			dsp->fVec7[(dsp->IOTA & 4095)] = fTemp7;
			dsp->fRec20[0] = dsp->fVec7[((dsp->IOTA - dsp->iConst19) & 4095)];
			float fRec21 = (0.0f - (0.600000024f * fTemp7));
			dsp->fRec27[0] = ((fSlow24 * dsp->fRec27[1]) + (fSlow25 * (dsp->fRec5[1] + dsp->fRec5[2])));
			dsp->fRec26[0] = ((fSlow51 * dsp->fRec26[1]) + (fSlow52 * (dsp->fRec5[1] + (fSlow53 * dsp->fRec27[0]))));
			dsp->fVec8[(dsp->IOTA & 32767)] = ((0.353553385f * dsp->fRec26[0]) + 9.99999968e-21f);
			float fTemp8 = (fTemp4 + ((0.600000024f * dsp->fRec24[1]) + dsp->fVec8[((dsp->IOTA - dsp->iConst23) & 32767)]));
			dsp->fVec9[(dsp->IOTA & 4095)] = fTemp8;
			dsp->fRec24[0] = dsp->fVec9[((dsp->IOTA - dsp->iConst24) & 4095)];
			float fRec25 = (0.0f - (0.600000024f * fTemp8));
			dsp->fRec31[0] = ((fSlow24 * dsp->fRec31[1]) + (fSlow25 * (dsp->fRec10[1] + dsp->fRec10[2])));
			dsp->fRec30[0] = ((fSlow60 * dsp->fRec30[1]) + (fSlow61 * (dsp->fRec10[1] + (fSlow62 * dsp->fRec31[0]))));
			dsp->fVec10[(dsp->IOTA & 16383)] = ((0.353553385f * dsp->fRec30[0]) + 9.99999968e-21f);
			float fTemp9 = (0.300000012f * dsp->fVec0[((dsp->IOTA - iSlow26) & 16383)]);
			float fTemp10 = (dsp->fVec10[((dsp->IOTA - dsp->iConst28) & 16383)] - (fTemp9 + (0.600000024f * dsp->fRec28[1])));
			dsp->fVec11[(dsp->IOTA & 2047)] = fTemp10;
			dsp->fRec28[0] = dsp->fVec11[((dsp->IOTA - dsp->iConst29) & 2047)];
			float fRec29 = (0.600000024f * fTemp10);
			dsp->fRec35[0] = ((fSlow24 * dsp->fRec35[1]) + (fSlow25 * (dsp->fRec6[1] + dsp->fRec6[2])));
			dsp->fRec34[0] = ((fSlow69 * dsp->fRec34[1]) + (fSlow70 * (dsp->fRec6[1] + (fSlow71 * dsp->fRec35[0]))));
			dsp->fVec12[(dsp->IOTA & 16383)] = ((0.353553385f * dsp->fRec34[0]) + 9.99999968e-21f);
			float fTemp11 = (dsp->fVec12[((dsp->IOTA - dsp->iConst33) & 16383)] - (fTemp9 + (0.600000024f * dsp->fRec32[1])));
			dsp->fVec13[(dsp->IOTA & 4095)] = fTemp11;
			dsp->fRec32[0] = dsp->fVec13[((dsp->IOTA - dsp->iConst34) & 4095)];
			float fRec33 = (0.600000024f * fTemp11);
			dsp->fRec39[0] = ((fSlow24 * dsp->fRec39[1]) + (fSlow25 * (dsp->fRec8[1] + dsp->fRec8[2])));
			dsp->fRec38[0] = ((fSlow78 * dsp->fRec38[1]) + (fSlow79 * (dsp->fRec8[1] + (fSlow80 * dsp->fRec39[0]))));
			dsp->fVec14[(dsp->IOTA & 16383)] = ((0.353553385f * dsp->fRec38[0]) + 9.99999968e-21f);
			float fTemp12 = ((fTemp9 + dsp->fVec14[((dsp->IOTA - dsp->iConst38) & 16383)]) - (0.600000024f * dsp->fRec36[1]));
			dsp->fVec15[(dsp->IOTA & 4095)] = fTemp12;
			dsp->fRec36[0] = dsp->fVec15[((dsp->IOTA - dsp->iConst39) & 4095)];
			float fRec37 = (0.600000024f * fTemp12);
			dsp->fRec43[0] = ((fSlow24 * dsp->fRec43[1]) + (fSlow25 * (dsp->fRec4[1] + dsp->fRec4[2])));
			dsp->fRec42[0] = ((fSlow87 * dsp->fRec42[1]) + (fSlow88 * (dsp->fRec4[1] + (fSlow89 * dsp->fRec43[0]))));
			dsp->fVec16[(dsp->IOTA & 16383)] = ((0.353553385f * dsp->fRec42[0]) + 9.99999968e-21f);
			float fTemp13 = ((dsp->fVec16[((dsp->IOTA - dsp->iConst43) & 16383)] + fTemp9) - (0.600000024f * dsp->fRec40[1]));
			dsp->fVec17[(dsp->IOTA & 2047)] = fTemp13;
			dsp->fRec40[0] = dsp->fVec17[((dsp->IOTA - dsp->iConst44) & 2047)];
			float fRec41 = (0.600000024f * fTemp13);
			float fTemp14 = (fRec41 + fRec37);
			float fTemp15 = (fRec29 + (fRec33 + fTemp14));
			dsp->fRec4[0] = (dsp->fRec12[1] + (dsp->fRec16[1] + (dsp->fRec20[1] + (dsp->fRec24[1] + (dsp->fRec28[1] + (dsp->fRec32[1] + (dsp->fRec36[1] + (dsp->fRec40[1] + (fRec13 + (fRec17 + (fRec21 + (fRec25 + fTemp15))))))))))));
			dsp->fRec5[0] = ((dsp->fRec28[1] + (dsp->fRec32[1] + (dsp->fRec36[1] + (dsp->fRec40[1] + fTemp15)))) - (dsp->fRec12[1] + (dsp->fRec16[1] + (dsp->fRec20[1] + (dsp->fRec24[1] + (fRec13 + (fRec17 + (fRec25 + fRec21))))))));
			float fTemp16 = (fRec33 + fRec29);
			dsp->fRec6[0] = ((dsp->fRec20[1] + (dsp->fRec24[1] + (dsp->fRec36[1] + (dsp->fRec40[1] + (fRec21 + (fRec25 + fTemp14)))))) - (dsp->fRec12[1] + (dsp->fRec16[1] + (dsp->fRec28[1] + (dsp->fRec32[1] + (fRec13 + (fRec17 + fTemp16)))))));
			dsp->fRec7[0] = ((dsp->fRec12[1] + (dsp->fRec16[1] + (dsp->fRec36[1] + (dsp->fRec40[1] + (fRec13 + (fRec17 + fTemp14)))))) - (dsp->fRec20[1] + (dsp->fRec24[1] + (dsp->fRec28[1] + (dsp->fRec32[1] + (fRec21 + (fRec25 + fTemp16)))))));
			float fTemp17 = (fRec41 + fRec33);
			float fTemp18 = (fRec37 + fRec29);
			dsp->fRec8[0] = ((dsp->fRec16[1] + (dsp->fRec24[1] + (dsp->fRec32[1] + (dsp->fRec40[1] + (fRec17 + (fRec25 + fTemp17)))))) - (dsp->fRec12[1] + (dsp->fRec20[1] + (dsp->fRec28[1] + (dsp->fRec36[1] + (fRec13 + (fRec21 + fTemp18)))))));
			dsp->fRec9[0] = ((dsp->fRec12[1] + (dsp->fRec20[1] + (dsp->fRec32[1] + (dsp->fRec40[1] + (fRec13 + (fRec21 + fTemp17)))))) - (dsp->fRec16[1] + (dsp->fRec24[1] + (dsp->fRec28[1] + (dsp->fRec36[1] + (fRec17 + (fRec25 + fTemp18)))))));
			float fTemp19 = (fRec41 + fRec29);
			float fTemp20 = (fRec37 + fRec33);
			dsp->fRec10[0] = ((dsp->fRec12[1] + (dsp->fRec24[1] + (dsp->fRec28[1] + (dsp->fRec40[1] + (fRec13 + (fRec25 + fTemp19)))))) - (dsp->fRec16[1] + (dsp->fRec20[1] + (dsp->fRec32[1] + (dsp->fRec36[1] + (fRec17 + (fRec21 + fTemp20)))))));
			dsp->fRec11[0] = ((dsp->fRec16[1] + (dsp->fRec20[1] + (dsp->fRec28[1] + (dsp->fRec40[1] + (fRec17 + (fRec21 + fTemp19)))))) - (dsp->fRec12[1] + (dsp->fRec24[1] + (dsp->fRec32[1] + (dsp->fRec36[1] + (fRec13 + (fRec25 + fTemp20)))))));
			float fTemp21 = (0.370000005f * (dsp->fRec5[0] + dsp->fRec6[0]));
			float fTemp22 = (fSlow90 * dsp->fRec3[1]);
			dsp->fRec3[0] = (fTemp21 - (fTemp22 + (fSlow9 * dsp->fRec3[2])));
			float fTemp23 = (fSlow9 * dsp->fRec3[0]);
			float fTemp24 = (0.5f * ((fTemp23 + (dsp->fRec3[2] + (fTemp21 + fTemp22))) + (fSlow7 * ((fTemp23 + (fTemp22 + dsp->fRec3[2])) - fTemp21))));
			float fTemp25 = (fSlow91 * dsp->fRec2[1]);
			dsp->fRec2[0] = (fTemp24 - (fTemp25 + (fSlow5 * dsp->fRec2[2])));
			float fTemp26 = (fSlow5 * dsp->fRec2[0]);
			output0[i] = (FAUSTFLOAT)(0.5f * (dsp->fRec0[0] * ((fTemp0 * fTemp1) + (fTemp2 * ((fTemp26 + (dsp->fRec2[2] + (fTemp24 + fTemp25))) + (fSlow3 * ((fTemp26 + (fTemp25 + dsp->fRec2[2])) - fTemp24)))))));
			float fTemp27 = (0.370000005f * (dsp->fRec5[0] - dsp->fRec6[0]));
			float fTemp28 = (fSlow90 * dsp->fRec45[1]);
			dsp->fRec45[0] = (fTemp27 - (fTemp28 + (fSlow9 * dsp->fRec45[2])));
			float fTemp29 = (fSlow9 * dsp->fRec45[0]);
			float fTemp30 = (0.5f * ((fTemp29 + (dsp->fRec45[2] + (fTemp27 + fTemp28))) + (fSlow7 * ((fTemp29 + (fTemp28 + dsp->fRec45[2])) - fTemp27))));
			float fTemp31 = (fSlow91 * dsp->fRec44[1]);
			dsp->fRec44[0] = (fTemp30 - (fTemp31 + (fSlow5 * dsp->fRec44[2])));
			float fTemp32 = (fSlow5 * dsp->fRec44[0]);
			output1[i] = (FAUSTFLOAT)(0.5f * (dsp->fRec0[0] * ((fTemp3 * fTemp1) + (fTemp2 * ((fTemp32 + (dsp->fRec44[2] + (fTemp30 + fTemp31))) + (fSlow3 * ((fTemp32 + (fTemp31 + dsp->fRec44[2])) - fTemp30)))))));
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->IOTA = (dsp->IOTA + 1);
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fRec15[1] = dsp->fRec15[0];
			dsp->fRec14[1] = dsp->fRec14[0];
			dsp->fRec12[1] = dsp->fRec12[0];
			dsp->fRec19[1] = dsp->fRec19[0];
			dsp->fRec18[1] = dsp->fRec18[0];
			dsp->fRec16[1] = dsp->fRec16[0];
			dsp->fRec23[1] = dsp->fRec23[0];
			dsp->fRec22[1] = dsp->fRec22[0];
			dsp->fRec20[1] = dsp->fRec20[0];
			dsp->fRec27[1] = dsp->fRec27[0];
			dsp->fRec26[1] = dsp->fRec26[0];
			dsp->fRec24[1] = dsp->fRec24[0];
			dsp->fRec31[1] = dsp->fRec31[0];
			dsp->fRec30[1] = dsp->fRec30[0];
			dsp->fRec28[1] = dsp->fRec28[0];
			dsp->fRec35[1] = dsp->fRec35[0];
			dsp->fRec34[1] = dsp->fRec34[0];
			dsp->fRec32[1] = dsp->fRec32[0];
			dsp->fRec39[1] = dsp->fRec39[0];
			dsp->fRec38[1] = dsp->fRec38[0];
			dsp->fRec36[1] = dsp->fRec36[0];
			dsp->fRec43[1] = dsp->fRec43[0];
			dsp->fRec42[1] = dsp->fRec42[0];
			dsp->fRec40[1] = dsp->fRec40[0];
			dsp->fRec4[2] = dsp->fRec4[1];
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fRec5[2] = dsp->fRec5[1];
			dsp->fRec5[1] = dsp->fRec5[0];
			dsp->fRec6[2] = dsp->fRec6[1];
			dsp->fRec6[1] = dsp->fRec6[0];
			dsp->fRec7[2] = dsp->fRec7[1];
			dsp->fRec7[1] = dsp->fRec7[0];
			dsp->fRec8[2] = dsp->fRec8[1];
			dsp->fRec8[1] = dsp->fRec8[0];
			dsp->fRec9[2] = dsp->fRec9[1];
			dsp->fRec9[1] = dsp->fRec9[0];
			dsp->fRec10[2] = dsp->fRec10[1];
			dsp->fRec10[1] = dsp->fRec10[0];
			dsp->fRec11[2] = dsp->fRec11[1];
			dsp->fRec11[1] = dsp->fRec11[0];
			dsp->fRec3[2] = dsp->fRec3[1];
			dsp->fRec3[1] = dsp->fRec3[0];
			dsp->fRec2[2] = dsp->fRec2[1];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec45[2] = dsp->fRec45[1];
			dsp->fRec45[1] = dsp->fRec45[0];
			dsp->fRec44[2] = dsp->fRec44[1];
			dsp->fRec44[1] = dsp->fRec44[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
