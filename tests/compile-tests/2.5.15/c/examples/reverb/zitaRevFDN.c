/* ------------------------------------------------------------
author: "JOS, Revised by RM"
name: "zitaRevFDN"
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
	
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fVslider0;
	float fConst3;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fVslider2;
	float fConst4;
	FAUSTFLOAT fVslider3;
	float fRec11[2];
	float fRec10[2];
	int IOTA;
	float fVec0[32768];
	float fConst5;
	int iConst6;
	float fVec1[2048];
	int iConst7;
	float fRec8[2];
	float fConst8;
	float fConst9;
	float fRec15[2];
	float fRec14[2];
	float fVec2[32768];
	float fConst10;
	int iConst11;
	float fVec3[4096];
	int iConst12;
	float fRec12[2];
	float fConst13;
	float fConst14;
	float fRec19[2];
	float fRec18[2];
	float fVec4[16384];
	float fConst15;
	int iConst16;
	float fVec5[4096];
	int iConst17;
	float fRec16[2];
	float fConst18;
	float fConst19;
	float fRec23[2];
	float fRec22[2];
	float fVec6[32768];
	float fConst20;
	int iConst21;
	float fVec7[4096];
	int iConst22;
	float fRec20[2];
	float fConst23;
	float fConst24;
	float fRec27[2];
	float fRec26[2];
	float fVec8[16384];
	float fConst25;
	int iConst26;
	float fVec9[2048];
	int iConst27;
	float fRec24[2];
	float fConst28;
	float fConst29;
	float fRec31[2];
	float fRec30[2];
	float fVec10[16384];
	float fConst30;
	int iConst31;
	float fVec11[4096];
	int iConst32;
	float fRec28[2];
	float fConst33;
	float fConst34;
	float fRec35[2];
	float fRec34[2];
	float fVec12[16384];
	float fConst35;
	int iConst36;
	float fVec13[4096];
	int iConst37;
	float fRec32[2];
	float fConst38;
	float fConst39;
	float fRec39[2];
	float fRec38[2];
	float fVec14[16384];
	float fConst40;
	int iConst41;
	float fVec15[2048];
	int iConst42;
	float fRec36[2];
	float fRec0[3];
	float fRec1[3];
	float fRec2[3];
	float fRec3[3];
	float fRec4[3];
	float fRec5[3];
	float fRec6[3];
	float fRec7[3];
	
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
	m->declare(m->metaInterface, "description", "Reverb demo application based on `zita_rev_fdn`.");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "zitaRevFDN");
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
	return 8;
	
}
int getNumOutputsmydsp(mydsp* dsp) {
	return 8;
	
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
		case 6: {
			rate = 1;
			break;
		}
		case 7: {
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
	dsp->fVslider0 = (FAUSTFLOAT)2.0f;
	dsp->fVslider1 = (FAUSTFLOAT)6000.0f;
	dsp->fVslider2 = (FAUSTFLOAT)3.0f;
	dsp->fVslider3 = (FAUSTFLOAT)200.0f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			dsp->fRec11[l0] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			dsp->fRec10[l1] = 0.0f;
			
		}
		
	}
	dsp->IOTA = 0;
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 32768); l2 = (l2 + 1)) {
			dsp->fVec0[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2048); l3 = (l3 + 1)) {
			dsp->fVec1[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			dsp->fRec8[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			dsp->fRec15[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			dsp->fRec14[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 32768); l7 = (l7 + 1)) {
			dsp->fVec2[l7] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 4096); l8 = (l8 + 1)) {
			dsp->fVec3[l8] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			dsp->fRec12[l9] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			dsp->fRec19[l10] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			dsp->fRec18[l11] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 16384); l12 = (l12 + 1)) {
			dsp->fVec4[l12] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l13;
		for (l13 = 0; (l13 < 4096); l13 = (l13 + 1)) {
			dsp->fVec5[l13] = 0.0f;
			
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
			dsp->fRec23[l15] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l16;
		for (l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			dsp->fRec22[l16] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l17;
		for (l17 = 0; (l17 < 32768); l17 = (l17 + 1)) {
			dsp->fVec6[l17] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l18;
		for (l18 = 0; (l18 < 4096); l18 = (l18 + 1)) {
			dsp->fVec7[l18] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l19;
		for (l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			dsp->fRec20[l19] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l20;
		for (l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			dsp->fRec27[l20] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l21;
		for (l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			dsp->fRec26[l21] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l22;
		for (l22 = 0; (l22 < 16384); l22 = (l22 + 1)) {
			dsp->fVec8[l22] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l23;
		for (l23 = 0; (l23 < 2048); l23 = (l23 + 1)) {
			dsp->fVec9[l23] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l24;
		for (l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			dsp->fRec24[l24] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l25;
		for (l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			dsp->fRec31[l25] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l26;
		for (l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			dsp->fRec30[l26] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l27;
		for (l27 = 0; (l27 < 16384); l27 = (l27 + 1)) {
			dsp->fVec10[l27] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l28;
		for (l28 = 0; (l28 < 4096); l28 = (l28 + 1)) {
			dsp->fVec11[l28] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l29;
		for (l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			dsp->fRec28[l29] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l30;
		for (l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			dsp->fRec35[l30] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l31;
		for (l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			dsp->fRec34[l31] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l32;
		for (l32 = 0; (l32 < 16384); l32 = (l32 + 1)) {
			dsp->fVec12[l32] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l33;
		for (l33 = 0; (l33 < 4096); l33 = (l33 + 1)) {
			dsp->fVec13[l33] = 0.0f;
			
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
			dsp->fRec39[l35] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l36;
		for (l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			dsp->fRec38[l36] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l37;
		for (l37 = 0; (l37 < 16384); l37 = (l37 + 1)) {
			dsp->fVec14[l37] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l38;
		for (l38 = 0; (l38 < 2048); l38 = (l38 + 1)) {
			dsp->fVec15[l38] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l39;
		for (l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			dsp->fRec36[l39] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l40;
		for (l40 = 0; (l40 < 3); l40 = (l40 + 1)) {
			dsp->fRec0[l40] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l41;
		for (l41 = 0; (l41 < 3); l41 = (l41 + 1)) {
			dsp->fRec1[l41] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l42;
		for (l42 = 0; (l42 < 3); l42 = (l42 + 1)) {
			dsp->fRec2[l42] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l43;
		for (l43 = 0; (l43 < 3); l43 = (l43 + 1)) {
			dsp->fRec3[l43] = 0.0f;
			
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
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = floorf(((0.219990999f * dsp->fConst0) + 0.5f));
	dsp->fConst2 = ((0.0f - (6.90775537f * dsp->fConst1)) / dsp->fConst0);
	dsp->fConst3 = (6.28318548f / dsp->fConst0);
	dsp->fConst4 = (3.14159274f / dsp->fConst0);
	dsp->fConst5 = floorf(((0.0191229992f * dsp->fConst0) + 0.5f));
	dsp->iConst6 = (int)min(16384.0f, max(0.0f, (dsp->fConst1 - dsp->fConst5)));
	dsp->iConst7 = (int)min(1024.0f, max(0.0f, (dsp->fConst5 + -1.0f)));
	dsp->fConst8 = floorf(((0.256891012f * dsp->fConst0) + 0.5f));
	dsp->fConst9 = ((0.0f - (6.90775537f * dsp->fConst8)) / dsp->fConst0);
	dsp->fConst10 = floorf(((0.0273330007f * dsp->fConst0) + 0.5f));
	dsp->iConst11 = (int)min(16384.0f, max(0.0f, (dsp->fConst8 - dsp->fConst10)));
	dsp->iConst12 = (int)min(2048.0f, max(0.0f, (dsp->fConst10 + -1.0f)));
	dsp->fConst13 = floorf(((0.192303002f * dsp->fConst0) + 0.5f));
	dsp->fConst14 = ((0.0f - (6.90775537f * dsp->fConst13)) / dsp->fConst0);
	dsp->fConst15 = floorf(((0.0292910002f * dsp->fConst0) + 0.5f));
	dsp->iConst16 = (int)min(8192.0f, max(0.0f, (dsp->fConst13 - dsp->fConst15)));
	dsp->iConst17 = (int)min(2048.0f, max(0.0f, (dsp->fConst15 + -1.0f)));
	dsp->fConst18 = floorf(((0.210389003f * dsp->fConst0) + 0.5f));
	dsp->fConst19 = ((0.0f - (6.90775537f * dsp->fConst18)) / dsp->fConst0);
	dsp->fConst20 = floorf(((0.0244210009f * dsp->fConst0) + 0.5f));
	dsp->iConst21 = (int)min(16384.0f, max(0.0f, (dsp->fConst18 - dsp->fConst20)));
	dsp->iConst22 = (int)min(2048.0f, max(0.0f, (dsp->fConst20 + -1.0f)));
	dsp->fConst23 = floorf(((0.125f * dsp->fConst0) + 0.5f));
	dsp->fConst24 = ((0.0f - (6.90775537f * dsp->fConst23)) / dsp->fConst0);
	dsp->fConst25 = floorf(((0.0134579996f * dsp->fConst0) + 0.5f));
	dsp->iConst26 = (int)min(8192.0f, max(0.0f, (dsp->fConst23 - dsp->fConst25)));
	dsp->iConst27 = (int)min(1024.0f, max(0.0f, (dsp->fConst25 + -1.0f)));
	dsp->fConst28 = floorf(((0.127837002f * dsp->fConst0) + 0.5f));
	dsp->fConst29 = ((0.0f - (6.90775537f * dsp->fConst28)) / dsp->fConst0);
	dsp->fConst30 = floorf(((0.0316039994f * dsp->fConst0) + 0.5f));
	dsp->iConst31 = (int)min(8192.0f, max(0.0f, (dsp->fConst28 - dsp->fConst30)));
	dsp->iConst32 = (int)min(2048.0f, max(0.0f, (dsp->fConst30 + -1.0f)));
	dsp->fConst33 = floorf(((0.174713001f * dsp->fConst0) + 0.5f));
	dsp->fConst34 = ((0.0f - (6.90775537f * dsp->fConst33)) / dsp->fConst0);
	dsp->fConst35 = floorf(((0.0229039993f * dsp->fConst0) + 0.5f));
	dsp->iConst36 = (int)min(8192.0f, max(0.0f, (dsp->fConst33 - dsp->fConst35)));
	dsp->iConst37 = (int)min(2048.0f, max(0.0f, (dsp->fConst35 + -1.0f)));
	dsp->fConst38 = floorf(((0.153128996f * dsp->fConst0) + 0.5f));
	dsp->fConst39 = ((0.0f - (6.90775537f * dsp->fConst38)) / dsp->fConst0);
	dsp->fConst40 = floorf(((0.0203460008f * dsp->fConst0) + 0.5f));
	dsp->iConst41 = (int)min(8192.0f, max(0.0f, (dsp->fConst38 - dsp->fConst40)));
	dsp->iConst42 = (int)min(1024.0f, max(0.0f, (dsp->fConst40 + -1.0f)));
	
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
	ui_interface->declare(ui_interface->uiInterface, 0, "tooltip", "~ Zita_Rev's internal   8x8 Feedback Delay Network (FDN) & Schroeder allpass-comb reverberator.  See   Faust's reverbs.lib for documentation and references");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "Zita_Rev Internal FDN Reverb");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider2, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider2, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider2, "tooltip", "T60 = time (in seconds) to decay 60dB in low-frequency band");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider2, "unit", "s");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Low RT60", &dsp->fVslider2, 3.0f, 1.0f, 8.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider3, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider3, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider3, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider3, "tooltip", "Crossover frequency (Hz) separating low and middle frequencies");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider3, "unit", "Hz");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "LF X", &dsp->fVslider3, 200.0f, 50.0f, 1000.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider0, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider0, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider0, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider0, "tooltip", "T60 = time (in seconds) to decay 60dB in middle band");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider0, "unit", "s");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Mid RT60", &dsp->fVslider0, 2.0f, 1.0f, 8.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider1, "4", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider1, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider1, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider1, "tooltip", "Frequency (Hz) at which the high-frequency T60 is half the middle-band's T60");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider1, "unit", "Hz");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "HF Damping", &dsp->fVslider1, 6000.0f, 1500.0f, 23520.0f, 1.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* input0 = inputs[0];
	FAUSTFLOAT* input1 = inputs[1];
	FAUSTFLOAT* input2 = inputs[2];
	FAUSTFLOAT* input3 = inputs[3];
	FAUSTFLOAT* input4 = inputs[4];
	FAUSTFLOAT* input5 = inputs[5];
	FAUSTFLOAT* input6 = inputs[6];
	FAUSTFLOAT* input7 = inputs[7];
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	FAUSTFLOAT* output2 = outputs[2];
	FAUSTFLOAT* output3 = outputs[3];
	FAUSTFLOAT* output4 = outputs[4];
	FAUSTFLOAT* output5 = outputs[5];
	FAUSTFLOAT* output6 = outputs[6];
	FAUSTFLOAT* output7 = outputs[7];
	float fSlow0 = (float)dsp->fVslider0;
	float fSlow1 = expf((dsp->fConst2 / fSlow0));
	float fSlow2 = mydsp_faustpower2_f(fSlow1);
	float fSlow3 = cosf((dsp->fConst3 * (float)dsp->fVslider1));
	float fSlow4 = (1.0f - (fSlow2 * fSlow3));
	float fSlow5 = (1.0f - fSlow2);
	float fSlow6 = (fSlow4 / fSlow5);
	float fSlow7 = sqrtf(max(0.0f, ((mydsp_faustpower2_f(fSlow4) / mydsp_faustpower2_f(fSlow5)) + -1.0f)));
	float fSlow8 = (fSlow6 - fSlow7);
	float fSlow9 = (fSlow1 * (fSlow7 + (1.0f - fSlow6)));
	float fSlow10 = (float)dsp->fVslider2;
	float fSlow11 = ((expf((dsp->fConst2 / fSlow10)) / fSlow1) + -1.0f);
	float fSlow12 = (1.0f / tanf((dsp->fConst4 * (float)dsp->fVslider3)));
	float fSlow13 = (fSlow12 + 1.0f);
	float fSlow14 = (0.0f - ((1.0f - fSlow12) / fSlow13));
	float fSlow15 = (1.0f / fSlow13);
	float fSlow16 = expf((dsp->fConst9 / fSlow0));
	float fSlow17 = mydsp_faustpower2_f(fSlow16);
	float fSlow18 = (1.0f - (fSlow3 * fSlow17));
	float fSlow19 = (1.0f - fSlow17);
	float fSlow20 = (fSlow18 / fSlow19);
	float fSlow21 = sqrtf(max(0.0f, ((mydsp_faustpower2_f(fSlow18) / mydsp_faustpower2_f(fSlow19)) + -1.0f)));
	float fSlow22 = (fSlow20 - fSlow21);
	float fSlow23 = (fSlow16 * (fSlow21 + (1.0f - fSlow20)));
	float fSlow24 = ((expf((dsp->fConst9 / fSlow10)) / fSlow16) + -1.0f);
	float fSlow25 = expf((dsp->fConst14 / fSlow0));
	float fSlow26 = mydsp_faustpower2_f(fSlow25);
	float fSlow27 = (1.0f - (fSlow3 * fSlow26));
	float fSlow28 = (1.0f - fSlow26);
	float fSlow29 = (fSlow27 / fSlow28);
	float fSlow30 = sqrtf(max(0.0f, ((mydsp_faustpower2_f(fSlow27) / mydsp_faustpower2_f(fSlow28)) + -1.0f)));
	float fSlow31 = (fSlow29 - fSlow30);
	float fSlow32 = (fSlow25 * (fSlow30 + (1.0f - fSlow29)));
	float fSlow33 = ((expf((dsp->fConst14 / fSlow10)) / fSlow25) + -1.0f);
	float fSlow34 = expf((dsp->fConst19 / fSlow0));
	float fSlow35 = mydsp_faustpower2_f(fSlow34);
	float fSlow36 = (1.0f - (fSlow3 * fSlow35));
	float fSlow37 = (1.0f - fSlow35);
	float fSlow38 = (fSlow36 / fSlow37);
	float fSlow39 = sqrtf(max(0.0f, ((mydsp_faustpower2_f(fSlow36) / mydsp_faustpower2_f(fSlow37)) + -1.0f)));
	float fSlow40 = (fSlow38 - fSlow39);
	float fSlow41 = (fSlow34 * (fSlow39 + (1.0f - fSlow38)));
	float fSlow42 = ((expf((dsp->fConst19 / fSlow10)) / fSlow34) + -1.0f);
	float fSlow43 = expf((dsp->fConst24 / fSlow0));
	float fSlow44 = mydsp_faustpower2_f(fSlow43);
	float fSlow45 = (1.0f - (fSlow3 * fSlow44));
	float fSlow46 = (1.0f - fSlow44);
	float fSlow47 = (fSlow45 / fSlow46);
	float fSlow48 = sqrtf(max(0.0f, ((mydsp_faustpower2_f(fSlow45) / mydsp_faustpower2_f(fSlow46)) + -1.0f)));
	float fSlow49 = (fSlow47 - fSlow48);
	float fSlow50 = (fSlow43 * (fSlow48 + (1.0f - fSlow47)));
	float fSlow51 = ((expf((dsp->fConst24 / fSlow10)) / fSlow43) + -1.0f);
	float fSlow52 = expf((dsp->fConst29 / fSlow0));
	float fSlow53 = mydsp_faustpower2_f(fSlow52);
	float fSlow54 = (1.0f - (fSlow3 * fSlow53));
	float fSlow55 = (1.0f - fSlow53);
	float fSlow56 = (fSlow54 / fSlow55);
	float fSlow57 = sqrtf(max(0.0f, ((mydsp_faustpower2_f(fSlow54) / mydsp_faustpower2_f(fSlow55)) + -1.0f)));
	float fSlow58 = (fSlow56 - fSlow57);
	float fSlow59 = (fSlow52 * (fSlow57 + (1.0f - fSlow56)));
	float fSlow60 = ((expf((dsp->fConst29 / fSlow10)) / fSlow52) + -1.0f);
	float fSlow61 = expf((dsp->fConst34 / fSlow0));
	float fSlow62 = mydsp_faustpower2_f(fSlow61);
	float fSlow63 = (1.0f - (fSlow3 * fSlow62));
	float fSlow64 = (1.0f - fSlow62);
	float fSlow65 = (fSlow63 / fSlow64);
	float fSlow66 = sqrtf(max(0.0f, ((mydsp_faustpower2_f(fSlow63) / mydsp_faustpower2_f(fSlow64)) + -1.0f)));
	float fSlow67 = (fSlow65 - fSlow66);
	float fSlow68 = (fSlow61 * (fSlow66 + (1.0f - fSlow65)));
	float fSlow69 = ((expf((dsp->fConst34 / fSlow10)) / fSlow61) + -1.0f);
	float fSlow70 = expf((dsp->fConst39 / fSlow0));
	float fSlow71 = mydsp_faustpower2_f(fSlow70);
	float fSlow72 = (1.0f - (fSlow3 * fSlow71));
	float fSlow73 = (1.0f - fSlow71);
	float fSlow74 = (fSlow72 / fSlow73);
	float fSlow75 = sqrtf(max(0.0f, ((mydsp_faustpower2_f(fSlow72) / mydsp_faustpower2_f(fSlow73)) + -1.0f)));
	float fSlow76 = (fSlow74 - fSlow75);
	float fSlow77 = (fSlow70 * (fSlow75 + (1.0f - fSlow74)));
	float fSlow78 = ((expf((dsp->fConst39 / fSlow10)) / fSlow70) + -1.0f);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->fRec11[0] = ((fSlow14 * dsp->fRec11[1]) + (fSlow15 * (dsp->fRec7[1] + dsp->fRec7[2])));
			dsp->fRec10[0] = ((fSlow8 * dsp->fRec10[1]) + (fSlow9 * (dsp->fRec7[1] + (fSlow11 * dsp->fRec11[0]))));
			dsp->fVec0[(dsp->IOTA & 32767)] = ((0.353553385f * dsp->fRec10[0]) + 9.99999968e-21f);
			float fTemp0 = (dsp->fVec0[((dsp->IOTA - dsp->iConst6) & 32767)] + ((float)input7[i] + (0.600000024f * dsp->fRec8[1])));
			dsp->fVec1[(dsp->IOTA & 2047)] = fTemp0;
			dsp->fRec8[0] = dsp->fVec1[((dsp->IOTA - dsp->iConst7) & 2047)];
			float fRec9 = (0.0f - (0.600000024f * fTemp0));
			dsp->fRec15[0] = ((fSlow14 * dsp->fRec15[1]) + (fSlow15 * (dsp->fRec3[1] + dsp->fRec3[2])));
			dsp->fRec14[0] = ((fSlow22 * dsp->fRec14[1]) + (fSlow23 * (dsp->fRec3[1] + (fSlow24 * dsp->fRec15[0]))));
			dsp->fVec2[(dsp->IOTA & 32767)] = ((0.353553385f * dsp->fRec14[0]) + 9.99999968e-21f);
			float fTemp1 = (dsp->fVec2[((dsp->IOTA - dsp->iConst11) & 32767)] + ((float)input3[i] + (0.600000024f * dsp->fRec12[1])));
			dsp->fVec3[(dsp->IOTA & 4095)] = fTemp1;
			dsp->fRec12[0] = dsp->fVec3[((dsp->IOTA - dsp->iConst12) & 4095)];
			float fRec13 = (0.0f - (0.600000024f * fTemp1));
			dsp->fRec19[0] = ((fSlow14 * dsp->fRec19[1]) + (fSlow15 * (dsp->fRec5[1] + dsp->fRec5[2])));
			dsp->fRec18[0] = ((fSlow31 * dsp->fRec18[1]) + (fSlow32 * (dsp->fRec5[1] + (fSlow33 * dsp->fRec19[0]))));
			dsp->fVec4[(dsp->IOTA & 16383)] = ((0.353553385f * dsp->fRec18[0]) + 9.99999968e-21f);
			float fTemp2 = (dsp->fVec4[((dsp->IOTA - dsp->iConst16) & 16383)] + ((float)input5[i] + (0.600000024f * dsp->fRec16[1])));
			dsp->fVec5[(dsp->IOTA & 4095)] = fTemp2;
			dsp->fRec16[0] = dsp->fVec5[((dsp->IOTA - dsp->iConst17) & 4095)];
			float fRec17 = (0.0f - (0.600000024f * fTemp2));
			dsp->fRec23[0] = ((fSlow14 * dsp->fRec23[1]) + (fSlow15 * (dsp->fRec1[1] + dsp->fRec1[2])));
			dsp->fRec22[0] = ((fSlow40 * dsp->fRec22[1]) + (fSlow41 * (dsp->fRec1[1] + (fSlow42 * dsp->fRec23[0]))));
			dsp->fVec6[(dsp->IOTA & 32767)] = ((0.353553385f * dsp->fRec22[0]) + 9.99999968e-21f);
			float fTemp3 = (dsp->fVec6[((dsp->IOTA - dsp->iConst21) & 32767)] + ((float)input1[i] + (0.600000024f * dsp->fRec20[1])));
			dsp->fVec7[(dsp->IOTA & 4095)] = fTemp3;
			dsp->fRec20[0] = dsp->fVec7[((dsp->IOTA - dsp->iConst22) & 4095)];
			float fRec21 = (0.0f - (0.600000024f * fTemp3));
			dsp->fRec27[0] = ((fSlow14 * dsp->fRec27[1]) + (fSlow15 * (dsp->fRec6[1] + dsp->fRec6[2])));
			dsp->fRec26[0] = ((fSlow49 * dsp->fRec26[1]) + (fSlow50 * (dsp->fRec6[1] + (fSlow51 * dsp->fRec27[0]))));
			dsp->fVec8[(dsp->IOTA & 16383)] = ((0.353553385f * dsp->fRec26[0]) + 9.99999968e-21f);
			float fTemp4 = (((float)input6[i] + dsp->fVec8[((dsp->IOTA - dsp->iConst26) & 16383)]) - (0.600000024f * dsp->fRec24[1]));
			dsp->fVec9[(dsp->IOTA & 2047)] = fTemp4;
			dsp->fRec24[0] = dsp->fVec9[((dsp->IOTA - dsp->iConst27) & 2047)];
			float fRec25 = (0.600000024f * fTemp4);
			dsp->fRec31[0] = ((fSlow14 * dsp->fRec31[1]) + (fSlow15 * (dsp->fRec2[1] + dsp->fRec2[2])));
			dsp->fRec30[0] = ((fSlow58 * dsp->fRec30[1]) + (fSlow59 * (dsp->fRec2[1] + (fSlow60 * dsp->fRec31[0]))));
			dsp->fVec10[(dsp->IOTA & 16383)] = ((0.353553385f * dsp->fRec30[0]) + 9.99999968e-21f);
			float fTemp5 = (((float)input2[i] + dsp->fVec10[((dsp->IOTA - dsp->iConst31) & 16383)]) - (0.600000024f * dsp->fRec28[1]));
			dsp->fVec11[(dsp->IOTA & 4095)] = fTemp5;
			dsp->fRec28[0] = dsp->fVec11[((dsp->IOTA - dsp->iConst32) & 4095)];
			float fRec29 = (0.600000024f * fTemp5);
			dsp->fRec35[0] = ((fSlow14 * dsp->fRec35[1]) + (fSlow15 * (dsp->fRec4[1] + dsp->fRec4[2])));
			dsp->fRec34[0] = ((fSlow67 * dsp->fRec34[1]) + (fSlow68 * (dsp->fRec4[1] + (fSlow69 * dsp->fRec35[0]))));
			dsp->fVec12[(dsp->IOTA & 16383)] = ((0.353553385f * dsp->fRec34[0]) + 9.99999968e-21f);
			float fTemp6 = (((float)input4[i] + dsp->fVec12[((dsp->IOTA - dsp->iConst36) & 16383)]) - (0.600000024f * dsp->fRec32[1]));
			dsp->fVec13[(dsp->IOTA & 4095)] = fTemp6;
			dsp->fRec32[0] = dsp->fVec13[((dsp->IOTA - dsp->iConst37) & 4095)];
			float fRec33 = (0.600000024f * fTemp6);
			dsp->fRec39[0] = ((fSlow14 * dsp->fRec39[1]) + (fSlow15 * (dsp->fRec0[1] + dsp->fRec0[2])));
			dsp->fRec38[0] = ((fSlow76 * dsp->fRec38[1]) + (fSlow77 * (dsp->fRec0[1] + (fSlow78 * dsp->fRec39[0]))));
			dsp->fVec14[(dsp->IOTA & 16383)] = ((0.353553385f * dsp->fRec38[0]) + 9.99999968e-21f);
			float fTemp7 = (((float)input0[i] + dsp->fVec14[((dsp->IOTA - dsp->iConst41) & 16383)]) - (0.600000024f * dsp->fRec36[1]));
			dsp->fVec15[(dsp->IOTA & 2047)] = fTemp7;
			dsp->fRec36[0] = dsp->fVec15[((dsp->IOTA - dsp->iConst42) & 2047)];
			float fRec37 = (0.600000024f * fTemp7);
			float fTemp8 = (fRec37 + fRec33);
			float fTemp9 = (fRec25 + (fRec29 + fTemp8));
			dsp->fRec0[0] = (dsp->fRec8[1] + (dsp->fRec12[1] + (dsp->fRec16[1] + (dsp->fRec20[1] + (dsp->fRec24[1] + (dsp->fRec28[1] + (dsp->fRec32[1] + (dsp->fRec36[1] + (fRec9 + (fRec13 + (fRec17 + (fRec21 + fTemp9))))))))))));
			dsp->fRec1[0] = ((dsp->fRec24[1] + (dsp->fRec28[1] + (dsp->fRec32[1] + (dsp->fRec36[1] + fTemp9)))) - (dsp->fRec8[1] + (dsp->fRec12[1] + (dsp->fRec16[1] + (dsp->fRec20[1] + (fRec9 + (fRec13 + (fRec21 + fRec17))))))));
			float fTemp10 = (fRec29 + fRec25);
			dsp->fRec2[0] = ((dsp->fRec16[1] + (dsp->fRec20[1] + (dsp->fRec32[1] + (dsp->fRec36[1] + (fRec17 + (fRec21 + fTemp8)))))) - (dsp->fRec8[1] + (dsp->fRec12[1] + (dsp->fRec24[1] + (dsp->fRec28[1] + (fRec9 + (fRec13 + fTemp10)))))));
			dsp->fRec3[0] = ((dsp->fRec8[1] + (dsp->fRec12[1] + (dsp->fRec32[1] + (dsp->fRec36[1] + (fRec9 + (fRec13 + fTemp8)))))) - (dsp->fRec16[1] + (dsp->fRec20[1] + (dsp->fRec24[1] + (dsp->fRec28[1] + (fRec17 + (fRec21 + fTemp10)))))));
			float fTemp11 = (fRec37 + fRec29);
			float fTemp12 = (fRec33 + fRec25);
			dsp->fRec4[0] = ((dsp->fRec12[1] + (dsp->fRec20[1] + (dsp->fRec28[1] + (dsp->fRec36[1] + (fRec13 + (fRec21 + fTemp11)))))) - (dsp->fRec8[1] + (dsp->fRec16[1] + (dsp->fRec24[1] + (dsp->fRec32[1] + (fRec9 + (fRec17 + fTemp12)))))));
			dsp->fRec5[0] = ((dsp->fRec8[1] + (dsp->fRec16[1] + (dsp->fRec28[1] + (dsp->fRec36[1] + (fRec9 + (fRec17 + fTemp11)))))) - (dsp->fRec12[1] + (dsp->fRec20[1] + (dsp->fRec24[1] + (dsp->fRec32[1] + (fRec13 + (fRec21 + fTemp12)))))));
			float fTemp13 = (fRec37 + fRec25);
			float fTemp14 = (fRec33 + fRec29);
			dsp->fRec6[0] = ((dsp->fRec8[1] + (dsp->fRec20[1] + (dsp->fRec24[1] + (dsp->fRec36[1] + (fRec9 + (fRec21 + fTemp13)))))) - (dsp->fRec12[1] + (dsp->fRec16[1] + (dsp->fRec28[1] + (dsp->fRec32[1] + (fRec13 + (fRec17 + fTemp14)))))));
			dsp->fRec7[0] = ((dsp->fRec12[1] + (dsp->fRec16[1] + (dsp->fRec24[1] + (dsp->fRec36[1] + (fRec13 + (fRec17 + fTemp13)))))) - (dsp->fRec8[1] + (dsp->fRec20[1] + (dsp->fRec28[1] + (dsp->fRec32[1] + (fRec9 + (fRec21 + fTemp14)))))));
			output0[i] = (FAUSTFLOAT)dsp->fRec0[0];
			output1[i] = (FAUSTFLOAT)dsp->fRec1[0];
			output2[i] = (FAUSTFLOAT)dsp->fRec2[0];
			output3[i] = (FAUSTFLOAT)dsp->fRec3[0];
			output4[i] = (FAUSTFLOAT)dsp->fRec4[0];
			output5[i] = (FAUSTFLOAT)dsp->fRec5[0];
			output6[i] = (FAUSTFLOAT)dsp->fRec6[0];
			output7[i] = (FAUSTFLOAT)dsp->fRec7[0];
			dsp->fRec11[1] = dsp->fRec11[0];
			dsp->fRec10[1] = dsp->fRec10[0];
			dsp->IOTA = (dsp->IOTA + 1);
			dsp->fRec8[1] = dsp->fRec8[0];
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
			dsp->fRec0[2] = dsp->fRec0[1];
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec1[2] = dsp->fRec1[1];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fRec2[2] = dsp->fRec2[1];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec3[2] = dsp->fRec3[1];
			dsp->fRec3[1] = dsp->fRec3[0];
			dsp->fRec4[2] = dsp->fRec4[1];
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fRec5[2] = dsp->fRec5[1];
			dsp->fRec5[1] = dsp->fRec5[0];
			dsp->fRec6[2] = dsp->fRec6[1];
			dsp->fRec6[1] = dsp->fRec6[0];
			dsp->fRec7[2] = dsp->fRec7[1];
			dsp->fRec7[1] = dsp->fRec7[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
