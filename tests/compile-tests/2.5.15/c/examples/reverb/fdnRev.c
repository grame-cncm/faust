/* ------------------------------------------------------------
author: "JOS, Revised by RM"
name: "fdnRev"
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
	
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fCheckbox0;
	int iRec17[2];
	float fRec16[4];
	FAUSTFLOAT fButton0;
	float fVec0[2];
	FAUSTFLOAT fButton1;
	float fVec1[2];
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT fButton2;
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fVslider0;
	float fConst3;
	FAUSTFLOAT fHslider3;
	float fRec22[2];
	float fRec21[3];
	FAUSTFLOAT fHslider4;
	float fRec20[3];
	FAUSTFLOAT fHslider5;
	float fRec19[3];
	FAUSTFLOAT fHslider6;
	float fRec18[3];
	FAUSTFLOAT fVslider1;
	float fRec28[2];
	float fRec27[3];
	float fVec2[2];
	float fRec26[2];
	float fRec25[3];
	float fRec24[3];
	float fRec23[3];
	FAUSTFLOAT fVslider2;
	float fRec33[2];
	float fRec32[3];
	float fVec3[2];
	float fRec31[2];
	float fRec30[3];
	float fRec29[3];
	FAUSTFLOAT fVslider3;
	float fRec37[2];
	float fRec36[3];
	float fVec4[2];
	float fRec35[2];
	float fRec34[3];
	FAUSTFLOAT fVslider4;
	float fRec39[2];
	float fRec38[3];
	float fRec44[2];
	float fRec43[3];
	float fRec42[3];
	float fRec41[3];
	float fRec40[3];
	float fRec50[2];
	float fRec49[3];
	float fVec5[2];
	float fRec48[2];
	float fRec47[3];
	float fRec46[3];
	float fRec45[3];
	float fRec55[2];
	float fRec54[3];
	float fVec6[2];
	float fRec53[2];
	float fRec52[3];
	float fRec51[3];
	float fRec59[2];
	float fRec58[3];
	float fVec7[2];
	float fRec57[2];
	float fRec56[3];
	float fRec61[2];
	float fRec60[3];
	float fRec66[2];
	float fRec65[3];
	float fRec64[3];
	float fRec63[3];
	float fRec62[3];
	float fRec72[2];
	float fRec71[3];
	float fVec8[2];
	float fRec70[2];
	float fRec69[3];
	float fRec68[3];
	float fRec67[3];
	float fRec77[2];
	float fRec76[3];
	float fVec9[2];
	float fRec75[2];
	float fRec74[3];
	float fRec73[3];
	float fRec81[2];
	float fRec80[3];
	float fVec10[2];
	float fRec79[2];
	float fRec78[3];
	float fRec83[2];
	float fRec82[3];
	float fRec88[2];
	float fRec87[3];
	float fRec86[3];
	float fRec85[3];
	float fRec84[3];
	float fRec94[2];
	float fRec93[3];
	float fVec11[2];
	float fRec92[2];
	float fRec91[3];
	float fRec90[3];
	float fRec89[3];
	float fRec99[2];
	float fRec98[3];
	float fVec12[2];
	float fRec97[2];
	float fRec96[3];
	float fRec95[3];
	float fRec103[2];
	float fRec102[3];
	float fVec13[2];
	float fRec101[2];
	float fRec100[3];
	float fRec105[2];
	float fRec104[3];
	float fRec110[2];
	float fRec109[3];
	float fRec108[3];
	float fRec107[3];
	float fRec106[3];
	float fRec116[2];
	float fRec115[3];
	float fVec14[2];
	float fRec114[2];
	float fRec113[3];
	float fRec112[3];
	float fRec111[3];
	float fRec121[2];
	float fRec120[3];
	float fVec15[2];
	float fRec119[2];
	float fRec118[3];
	float fRec117[3];
	float fRec125[2];
	float fRec124[3];
	float fVec16[2];
	float fRec123[2];
	float fRec122[3];
	float fRec127[2];
	float fRec126[3];
	float fRec132[2];
	float fRec131[3];
	float fRec130[3];
	float fRec129[3];
	float fRec128[3];
	float fRec138[2];
	float fRec137[3];
	float fVec17[2];
	float fRec136[2];
	float fRec135[3];
	float fRec134[3];
	float fRec133[3];
	float fRec143[2];
	float fRec142[3];
	float fVec18[2];
	float fRec141[2];
	float fRec140[3];
	float fRec139[3];
	float fRec147[2];
	float fRec146[3];
	float fVec19[2];
	float fRec145[2];
	float fRec144[3];
	float fRec149[2];
	float fRec148[3];
	float fRec154[2];
	float fRec153[3];
	float fRec152[3];
	float fRec151[3];
	float fRec150[3];
	float fRec160[2];
	float fRec159[3];
	float fVec20[2];
	float fRec158[2];
	float fRec157[3];
	float fRec156[3];
	float fRec155[3];
	float fRec165[2];
	float fRec164[3];
	float fVec21[2];
	float fRec163[2];
	float fRec162[3];
	float fRec161[3];
	float fRec169[2];
	float fRec168[3];
	float fVec22[2];
	float fRec167[2];
	float fRec166[3];
	float fRec171[2];
	float fRec170[3];
	float fRec176[2];
	float fRec175[3];
	float fRec174[3];
	float fRec173[3];
	float fRec172[3];
	float fRec182[2];
	float fRec181[3];
	float fVec23[2];
	float fRec180[2];
	float fRec179[3];
	float fRec178[3];
	float fRec177[3];
	float fRec187[2];
	float fRec186[3];
	float fVec24[2];
	float fRec185[2];
	float fRec184[3];
	float fRec183[3];
	float fRec191[2];
	float fRec190[3];
	float fVec25[2];
	float fRec189[2];
	float fRec188[3];
	float fRec193[2];
	float fRec192[3];
	float fRec198[2];
	float fRec197[3];
	float fRec196[3];
	float fRec195[3];
	float fRec194[3];
	float fRec204[2];
	float fRec203[3];
	float fVec26[2];
	float fRec202[2];
	float fRec201[3];
	float fRec200[3];
	float fRec199[3];
	float fRec209[2];
	float fRec208[3];
	float fVec27[2];
	float fRec207[2];
	float fRec206[3];
	float fRec205[3];
	float fRec213[2];
	float fRec212[3];
	float fVec28[2];
	float fRec211[2];
	float fRec210[3];
	float fRec215[2];
	float fRec214[3];
	float fRec220[2];
	float fRec219[3];
	float fRec218[3];
	float fRec217[3];
	float fRec216[3];
	float fRec226[2];
	float fRec225[3];
	float fVec29[2];
	float fRec224[2];
	float fRec223[3];
	float fRec222[3];
	float fRec221[3];
	float fRec231[2];
	float fRec230[3];
	float fVec30[2];
	float fRec229[2];
	float fRec228[3];
	float fRec227[3];
	float fRec235[2];
	float fRec234[3];
	float fVec31[2];
	float fRec233[2];
	float fRec232[3];
	float fRec237[2];
	float fRec236[3];
	float fRec242[2];
	float fRec241[3];
	float fRec240[3];
	float fRec239[3];
	float fRec238[3];
	float fRec248[2];
	float fRec247[3];
	float fVec32[2];
	float fRec246[2];
	float fRec245[3];
	float fRec244[3];
	float fRec243[3];
	float fRec253[2];
	float fRec252[3];
	float fVec33[2];
	float fRec251[2];
	float fRec250[3];
	float fRec249[3];
	float fRec257[2];
	float fRec256[3];
	float fVec34[2];
	float fRec255[2];
	float fRec254[3];
	float fRec259[2];
	float fRec258[3];
	float fRec264[2];
	float fRec263[3];
	float fRec262[3];
	float fRec261[3];
	float fRec260[3];
	float fRec270[2];
	float fRec269[3];
	float fVec35[2];
	float fRec268[2];
	float fRec267[3];
	float fRec266[3];
	float fRec265[3];
	float fRec275[2];
	float fRec274[3];
	float fVec36[2];
	float fRec273[2];
	float fRec272[3];
	float fRec271[3];
	float fRec279[2];
	float fRec278[3];
	float fVec37[2];
	float fRec277[2];
	float fRec276[3];
	float fRec281[2];
	float fRec280[3];
	float fRec286[2];
	float fRec285[3];
	float fRec284[3];
	float fRec283[3];
	float fRec282[3];
	float fRec292[2];
	float fRec291[3];
	float fVec38[2];
	float fRec290[2];
	float fRec289[3];
	float fRec288[3];
	float fRec287[3];
	float fRec297[2];
	float fRec296[3];
	float fVec39[2];
	float fRec295[2];
	float fRec294[3];
	float fRec293[3];
	float fRec301[2];
	float fRec300[3];
	float fVec40[2];
	float fRec299[2];
	float fRec298[3];
	float fRec303[2];
	float fRec302[3];
	float fRec308[2];
	float fRec307[3];
	float fRec306[3];
	float fRec305[3];
	float fRec304[3];
	float fRec314[2];
	float fRec313[3];
	float fVec41[2];
	float fRec312[2];
	float fRec311[3];
	float fRec310[3];
	float fRec309[3];
	float fRec319[2];
	float fRec318[3];
	float fVec42[2];
	float fRec317[2];
	float fRec316[3];
	float fRec315[3];
	float fRec323[2];
	float fRec322[3];
	float fVec43[2];
	float fRec321[2];
	float fRec320[3];
	float fRec325[2];
	float fRec324[3];
	float fRec330[2];
	float fRec329[3];
	float fRec328[3];
	float fRec327[3];
	float fRec326[3];
	float fRec336[2];
	float fRec335[3];
	float fVec44[2];
	float fRec334[2];
	float fRec333[3];
	float fRec332[3];
	float fRec331[3];
	float fRec341[2];
	float fRec340[3];
	float fVec45[2];
	float fRec339[2];
	float fRec338[3];
	float fRec337[3];
	float fRec345[2];
	float fRec344[3];
	float fVec46[2];
	float fRec343[2];
	float fRec342[3];
	float fRec347[2];
	float fRec346[3];
	float fRec352[2];
	float fRec351[3];
	float fRec350[3];
	float fRec349[3];
	float fRec348[3];
	float fRec358[2];
	float fRec357[3];
	float fVec47[2];
	float fRec356[2];
	float fRec355[3];
	float fRec354[3];
	float fRec353[3];
	float fRec363[2];
	float fRec362[3];
	float fVec48[2];
	float fRec361[2];
	float fRec360[3];
	float fRec359[3];
	float fRec367[2];
	float fRec366[3];
	float fVec49[2];
	float fRec365[2];
	float fRec364[3];
	float fRec369[2];
	float fRec368[3];
	int IOTA;
	float fVec50[16384];
	float fRec0[3];
	FAUSTFLOAT fButton3;
	float fVec51[2];
	float fVec52[16384];
	float fRec1[3];
	float fVec53[16384];
	float fRec2[3];
	float fVec54[16384];
	float fRec3[3];
	float fVec55[16384];
	float fRec4[3];
	float fVec56[16384];
	float fRec5[3];
	float fVec57[16384];
	float fRec6[3];
	float fVec58[16384];
	float fRec7[3];
	float fVec59[16384];
	float fRec8[3];
	float fVec60[16384];
	float fRec9[3];
	float fVec61[16384];
	float fRec10[3];
	float fVec62[16384];
	float fRec11[3];
	float fVec63[16384];
	float fRec12[3];
	float fVec64[16384];
	float fRec13[3];
	float fVec65[16384];
	float fRec14[3];
	float fVec66[16384];
	float fRec15[3];
	
} mydsp;

mydsp* newmydsp() { 
	mydsp* dsp = (mydsp*)malloc(sizeof(mydsp));
	return dsp;
}

void deletemydsp(mydsp* dsp) { 
	free(dsp);
}

void metadatamydsp(MetaGlue* m) { 
	m->declare(m->metaInterface, "analyzers.lib/name", "Faust Analyzer Library");
	m->declare(m->metaInterface, "analyzers.lib/version", "0.0");
	m->declare(m->metaInterface, "author", "JOS, Revised by RM");
	m->declare(m->metaInterface, "basics.lib/name", "Faust Basic Element Library");
	m->declare(m->metaInterface, "basics.lib/version", "0.0");
	m->declare(m->metaInterface, "delays.lib/name", "Faust Delay Library");
	m->declare(m->metaInterface, "delays.lib/version", "0.0");
	m->declare(m->metaInterface, "description", "A feedback delay network reverb.");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "fdnRev");
	m->declare(m->metaInterface, "noises.lib/name", "Faust Noise Generator Library");
	m->declare(m->metaInterface, "noises.lib/version", "0.0");
	m->declare(m->metaInterface, "reverbs.lib/name", "Faust Reverb Library");
	m->declare(m->metaInterface, "reverbs.lib/version", "0.0");
	m->declare(m->metaInterface, "signals.lib/name", "Faust Signal Routing Library");
	m->declare(m->metaInterface, "signals.lib/version", "0.0");
	m->declare(m->metaInterface, "version", "0.0");
}

int getSampleRatemydsp(mydsp* dsp) { return dsp->fSamplingFreq; }

int getNumInputsmydsp(mydsp* dsp) {
	return 4;
	
}
int getNumOutputsmydsp(mydsp* dsp) {
	return 2;
	
}
int getInputRatemydsp(mydsp* dsp, int channel) {
	int rate;
	switch (channel) {
		case 0: {
			rate = 0;
			break;
		}
		case 1: {
			rate = 0;
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
	dsp->fHslider0 = (FAUSTFLOAT)-40.0f;
	dsp->fCheckbox0 = (FAUSTFLOAT)0.0f;
	dsp->fButton0 = (FAUSTFLOAT)0.0f;
	dsp->fButton1 = (FAUSTFLOAT)0.0f;
	dsp->fCheckbox1 = (FAUSTFLOAT)0.0f;
	dsp->fButton2 = (FAUSTFLOAT)0.0f;
	dsp->fHslider1 = (FAUSTFLOAT)46.0f;
	dsp->fHslider2 = (FAUSTFLOAT)63.0f;
	dsp->fVslider0 = (FAUSTFLOAT)2.7000000000000002f;
	dsp->fHslider3 = (FAUSTFLOAT)4000.0f;
	dsp->fHslider4 = (FAUSTFLOAT)2000.0f;
	dsp->fHslider5 = (FAUSTFLOAT)1000.0f;
	dsp->fHslider6 = (FAUSTFLOAT)500.0f;
	dsp->fVslider1 = (FAUSTFLOAT)3.7999999999999998f;
	dsp->fVslider2 = (FAUSTFLOAT)5.0f;
	dsp->fVslider3 = (FAUSTFLOAT)6.5f;
	dsp->fVslider4 = (FAUSTFLOAT)8.4000000000000004f;
	dsp->fButton3 = (FAUSTFLOAT)0.0f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			dsp->iRec17[l0] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 4); l1 = (l1 + 1)) {
			dsp->fRec16[l1] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			dsp->fVec0[l2] = 0.0f;
			
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
			dsp->fRec22[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 3); l5 = (l5 + 1)) {
			dsp->fRec21[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 3); l6 = (l6 + 1)) {
			dsp->fRec20[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			dsp->fRec19[l7] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
			dsp->fRec18[l8] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			dsp->fRec28[l9] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 3); l10 = (l10 + 1)) {
			dsp->fRec27[l10] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			dsp->fVec2[l11] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			dsp->fRec26[l12] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l13;
		for (l13 = 0; (l13 < 3); l13 = (l13 + 1)) {
			dsp->fRec25[l13] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l14;
		for (l14 = 0; (l14 < 3); l14 = (l14 + 1)) {
			dsp->fRec24[l14] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l15;
		for (l15 = 0; (l15 < 3); l15 = (l15 + 1)) {
			dsp->fRec23[l15] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l16;
		for (l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			dsp->fRec33[l16] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l17;
		for (l17 = 0; (l17 < 3); l17 = (l17 + 1)) {
			dsp->fRec32[l17] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l18;
		for (l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			dsp->fVec3[l18] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l19;
		for (l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			dsp->fRec31[l19] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l20;
		for (l20 = 0; (l20 < 3); l20 = (l20 + 1)) {
			dsp->fRec30[l20] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l21;
		for (l21 = 0; (l21 < 3); l21 = (l21 + 1)) {
			dsp->fRec29[l21] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l22;
		for (l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			dsp->fRec37[l22] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l23;
		for (l23 = 0; (l23 < 3); l23 = (l23 + 1)) {
			dsp->fRec36[l23] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l24;
		for (l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			dsp->fVec4[l24] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l25;
		for (l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			dsp->fRec35[l25] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l26;
		for (l26 = 0; (l26 < 3); l26 = (l26 + 1)) {
			dsp->fRec34[l26] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l27;
		for (l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			dsp->fRec39[l27] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l28;
		for (l28 = 0; (l28 < 3); l28 = (l28 + 1)) {
			dsp->fRec38[l28] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l29;
		for (l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			dsp->fRec44[l29] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l30;
		for (l30 = 0; (l30 < 3); l30 = (l30 + 1)) {
			dsp->fRec43[l30] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l31;
		for (l31 = 0; (l31 < 3); l31 = (l31 + 1)) {
			dsp->fRec42[l31] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l32;
		for (l32 = 0; (l32 < 3); l32 = (l32 + 1)) {
			dsp->fRec41[l32] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l33;
		for (l33 = 0; (l33 < 3); l33 = (l33 + 1)) {
			dsp->fRec40[l33] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l34;
		for (l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			dsp->fRec50[l34] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l35;
		for (l35 = 0; (l35 < 3); l35 = (l35 + 1)) {
			dsp->fRec49[l35] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l36;
		for (l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			dsp->fVec5[l36] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l37;
		for (l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			dsp->fRec48[l37] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l38;
		for (l38 = 0; (l38 < 3); l38 = (l38 + 1)) {
			dsp->fRec47[l38] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l39;
		for (l39 = 0; (l39 < 3); l39 = (l39 + 1)) {
			dsp->fRec46[l39] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l40;
		for (l40 = 0; (l40 < 3); l40 = (l40 + 1)) {
			dsp->fRec45[l40] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l41;
		for (l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			dsp->fRec55[l41] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l42;
		for (l42 = 0; (l42 < 3); l42 = (l42 + 1)) {
			dsp->fRec54[l42] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l43;
		for (l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			dsp->fVec6[l43] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l44;
		for (l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			dsp->fRec53[l44] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l45;
		for (l45 = 0; (l45 < 3); l45 = (l45 + 1)) {
			dsp->fRec52[l45] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l46;
		for (l46 = 0; (l46 < 3); l46 = (l46 + 1)) {
			dsp->fRec51[l46] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l47;
		for (l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			dsp->fRec59[l47] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l48;
		for (l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			dsp->fRec58[l48] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l49;
		for (l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			dsp->fVec7[l49] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l50;
		for (l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			dsp->fRec57[l50] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l51;
		for (l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			dsp->fRec56[l51] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l52;
		for (l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			dsp->fRec61[l52] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l53;
		for (l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			dsp->fRec60[l53] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l54;
		for (l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
			dsp->fRec66[l54] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l55;
		for (l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			dsp->fRec65[l55] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l56;
		for (l56 = 0; (l56 < 3); l56 = (l56 + 1)) {
			dsp->fRec64[l56] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l57;
		for (l57 = 0; (l57 < 3); l57 = (l57 + 1)) {
			dsp->fRec63[l57] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l58;
		for (l58 = 0; (l58 < 3); l58 = (l58 + 1)) {
			dsp->fRec62[l58] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l59;
		for (l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			dsp->fRec72[l59] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l60;
		for (l60 = 0; (l60 < 3); l60 = (l60 + 1)) {
			dsp->fRec71[l60] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l61;
		for (l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			dsp->fVec8[l61] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l62;
		for (l62 = 0; (l62 < 2); l62 = (l62 + 1)) {
			dsp->fRec70[l62] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l63;
		for (l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			dsp->fRec69[l63] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l64;
		for (l64 = 0; (l64 < 3); l64 = (l64 + 1)) {
			dsp->fRec68[l64] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l65;
		for (l65 = 0; (l65 < 3); l65 = (l65 + 1)) {
			dsp->fRec67[l65] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l66;
		for (l66 = 0; (l66 < 2); l66 = (l66 + 1)) {
			dsp->fRec77[l66] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l67;
		for (l67 = 0; (l67 < 3); l67 = (l67 + 1)) {
			dsp->fRec76[l67] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l68;
		for (l68 = 0; (l68 < 2); l68 = (l68 + 1)) {
			dsp->fVec9[l68] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l69;
		for (l69 = 0; (l69 < 2); l69 = (l69 + 1)) {
			dsp->fRec75[l69] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l70;
		for (l70 = 0; (l70 < 3); l70 = (l70 + 1)) {
			dsp->fRec74[l70] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l71;
		for (l71 = 0; (l71 < 3); l71 = (l71 + 1)) {
			dsp->fRec73[l71] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l72;
		for (l72 = 0; (l72 < 2); l72 = (l72 + 1)) {
			dsp->fRec81[l72] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l73;
		for (l73 = 0; (l73 < 3); l73 = (l73 + 1)) {
			dsp->fRec80[l73] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l74;
		for (l74 = 0; (l74 < 2); l74 = (l74 + 1)) {
			dsp->fVec10[l74] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l75;
		for (l75 = 0; (l75 < 2); l75 = (l75 + 1)) {
			dsp->fRec79[l75] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l76;
		for (l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			dsp->fRec78[l76] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l77;
		for (l77 = 0; (l77 < 2); l77 = (l77 + 1)) {
			dsp->fRec83[l77] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l78;
		for (l78 = 0; (l78 < 3); l78 = (l78 + 1)) {
			dsp->fRec82[l78] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l79;
		for (l79 = 0; (l79 < 2); l79 = (l79 + 1)) {
			dsp->fRec88[l79] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l80;
		for (l80 = 0; (l80 < 3); l80 = (l80 + 1)) {
			dsp->fRec87[l80] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l81;
		for (l81 = 0; (l81 < 3); l81 = (l81 + 1)) {
			dsp->fRec86[l81] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l82;
		for (l82 = 0; (l82 < 3); l82 = (l82 + 1)) {
			dsp->fRec85[l82] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l83;
		for (l83 = 0; (l83 < 3); l83 = (l83 + 1)) {
			dsp->fRec84[l83] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l84;
		for (l84 = 0; (l84 < 2); l84 = (l84 + 1)) {
			dsp->fRec94[l84] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l85;
		for (l85 = 0; (l85 < 3); l85 = (l85 + 1)) {
			dsp->fRec93[l85] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l86;
		for (l86 = 0; (l86 < 2); l86 = (l86 + 1)) {
			dsp->fVec11[l86] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l87;
		for (l87 = 0; (l87 < 2); l87 = (l87 + 1)) {
			dsp->fRec92[l87] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l88;
		for (l88 = 0; (l88 < 3); l88 = (l88 + 1)) {
			dsp->fRec91[l88] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l89;
		for (l89 = 0; (l89 < 3); l89 = (l89 + 1)) {
			dsp->fRec90[l89] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l90;
		for (l90 = 0; (l90 < 3); l90 = (l90 + 1)) {
			dsp->fRec89[l90] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l91;
		for (l91 = 0; (l91 < 2); l91 = (l91 + 1)) {
			dsp->fRec99[l91] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l92;
		for (l92 = 0; (l92 < 3); l92 = (l92 + 1)) {
			dsp->fRec98[l92] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l93;
		for (l93 = 0; (l93 < 2); l93 = (l93 + 1)) {
			dsp->fVec12[l93] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l94;
		for (l94 = 0; (l94 < 2); l94 = (l94 + 1)) {
			dsp->fRec97[l94] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l95;
		for (l95 = 0; (l95 < 3); l95 = (l95 + 1)) {
			dsp->fRec96[l95] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l96;
		for (l96 = 0; (l96 < 3); l96 = (l96 + 1)) {
			dsp->fRec95[l96] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l97;
		for (l97 = 0; (l97 < 2); l97 = (l97 + 1)) {
			dsp->fRec103[l97] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l98;
		for (l98 = 0; (l98 < 3); l98 = (l98 + 1)) {
			dsp->fRec102[l98] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l99;
		for (l99 = 0; (l99 < 2); l99 = (l99 + 1)) {
			dsp->fVec13[l99] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l100;
		for (l100 = 0; (l100 < 2); l100 = (l100 + 1)) {
			dsp->fRec101[l100] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l101;
		for (l101 = 0; (l101 < 3); l101 = (l101 + 1)) {
			dsp->fRec100[l101] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l102;
		for (l102 = 0; (l102 < 2); l102 = (l102 + 1)) {
			dsp->fRec105[l102] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l103;
		for (l103 = 0; (l103 < 3); l103 = (l103 + 1)) {
			dsp->fRec104[l103] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l104;
		for (l104 = 0; (l104 < 2); l104 = (l104 + 1)) {
			dsp->fRec110[l104] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l105;
		for (l105 = 0; (l105 < 3); l105 = (l105 + 1)) {
			dsp->fRec109[l105] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l106;
		for (l106 = 0; (l106 < 3); l106 = (l106 + 1)) {
			dsp->fRec108[l106] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l107;
		for (l107 = 0; (l107 < 3); l107 = (l107 + 1)) {
			dsp->fRec107[l107] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l108;
		for (l108 = 0; (l108 < 3); l108 = (l108 + 1)) {
			dsp->fRec106[l108] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l109;
		for (l109 = 0; (l109 < 2); l109 = (l109 + 1)) {
			dsp->fRec116[l109] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l110;
		for (l110 = 0; (l110 < 3); l110 = (l110 + 1)) {
			dsp->fRec115[l110] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l111;
		for (l111 = 0; (l111 < 2); l111 = (l111 + 1)) {
			dsp->fVec14[l111] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l112;
		for (l112 = 0; (l112 < 2); l112 = (l112 + 1)) {
			dsp->fRec114[l112] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l113;
		for (l113 = 0; (l113 < 3); l113 = (l113 + 1)) {
			dsp->fRec113[l113] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l114;
		for (l114 = 0; (l114 < 3); l114 = (l114 + 1)) {
			dsp->fRec112[l114] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l115;
		for (l115 = 0; (l115 < 3); l115 = (l115 + 1)) {
			dsp->fRec111[l115] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l116;
		for (l116 = 0; (l116 < 2); l116 = (l116 + 1)) {
			dsp->fRec121[l116] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l117;
		for (l117 = 0; (l117 < 3); l117 = (l117 + 1)) {
			dsp->fRec120[l117] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l118;
		for (l118 = 0; (l118 < 2); l118 = (l118 + 1)) {
			dsp->fVec15[l118] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l119;
		for (l119 = 0; (l119 < 2); l119 = (l119 + 1)) {
			dsp->fRec119[l119] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l120;
		for (l120 = 0; (l120 < 3); l120 = (l120 + 1)) {
			dsp->fRec118[l120] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l121;
		for (l121 = 0; (l121 < 3); l121 = (l121 + 1)) {
			dsp->fRec117[l121] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l122;
		for (l122 = 0; (l122 < 2); l122 = (l122 + 1)) {
			dsp->fRec125[l122] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l123;
		for (l123 = 0; (l123 < 3); l123 = (l123 + 1)) {
			dsp->fRec124[l123] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l124;
		for (l124 = 0; (l124 < 2); l124 = (l124 + 1)) {
			dsp->fVec16[l124] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l125;
		for (l125 = 0; (l125 < 2); l125 = (l125 + 1)) {
			dsp->fRec123[l125] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l126;
		for (l126 = 0; (l126 < 3); l126 = (l126 + 1)) {
			dsp->fRec122[l126] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l127;
		for (l127 = 0; (l127 < 2); l127 = (l127 + 1)) {
			dsp->fRec127[l127] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l128;
		for (l128 = 0; (l128 < 3); l128 = (l128 + 1)) {
			dsp->fRec126[l128] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l129;
		for (l129 = 0; (l129 < 2); l129 = (l129 + 1)) {
			dsp->fRec132[l129] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l130;
		for (l130 = 0; (l130 < 3); l130 = (l130 + 1)) {
			dsp->fRec131[l130] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l131;
		for (l131 = 0; (l131 < 3); l131 = (l131 + 1)) {
			dsp->fRec130[l131] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l132;
		for (l132 = 0; (l132 < 3); l132 = (l132 + 1)) {
			dsp->fRec129[l132] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l133;
		for (l133 = 0; (l133 < 3); l133 = (l133 + 1)) {
			dsp->fRec128[l133] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l134;
		for (l134 = 0; (l134 < 2); l134 = (l134 + 1)) {
			dsp->fRec138[l134] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l135;
		for (l135 = 0; (l135 < 3); l135 = (l135 + 1)) {
			dsp->fRec137[l135] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l136;
		for (l136 = 0; (l136 < 2); l136 = (l136 + 1)) {
			dsp->fVec17[l136] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l137;
		for (l137 = 0; (l137 < 2); l137 = (l137 + 1)) {
			dsp->fRec136[l137] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l138;
		for (l138 = 0; (l138 < 3); l138 = (l138 + 1)) {
			dsp->fRec135[l138] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l139;
		for (l139 = 0; (l139 < 3); l139 = (l139 + 1)) {
			dsp->fRec134[l139] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l140;
		for (l140 = 0; (l140 < 3); l140 = (l140 + 1)) {
			dsp->fRec133[l140] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l141;
		for (l141 = 0; (l141 < 2); l141 = (l141 + 1)) {
			dsp->fRec143[l141] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l142;
		for (l142 = 0; (l142 < 3); l142 = (l142 + 1)) {
			dsp->fRec142[l142] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l143;
		for (l143 = 0; (l143 < 2); l143 = (l143 + 1)) {
			dsp->fVec18[l143] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l144;
		for (l144 = 0; (l144 < 2); l144 = (l144 + 1)) {
			dsp->fRec141[l144] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l145;
		for (l145 = 0; (l145 < 3); l145 = (l145 + 1)) {
			dsp->fRec140[l145] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l146;
		for (l146 = 0; (l146 < 3); l146 = (l146 + 1)) {
			dsp->fRec139[l146] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l147;
		for (l147 = 0; (l147 < 2); l147 = (l147 + 1)) {
			dsp->fRec147[l147] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l148;
		for (l148 = 0; (l148 < 3); l148 = (l148 + 1)) {
			dsp->fRec146[l148] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l149;
		for (l149 = 0; (l149 < 2); l149 = (l149 + 1)) {
			dsp->fVec19[l149] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l150;
		for (l150 = 0; (l150 < 2); l150 = (l150 + 1)) {
			dsp->fRec145[l150] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l151;
		for (l151 = 0; (l151 < 3); l151 = (l151 + 1)) {
			dsp->fRec144[l151] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l152;
		for (l152 = 0; (l152 < 2); l152 = (l152 + 1)) {
			dsp->fRec149[l152] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l153;
		for (l153 = 0; (l153 < 3); l153 = (l153 + 1)) {
			dsp->fRec148[l153] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l154;
		for (l154 = 0; (l154 < 2); l154 = (l154 + 1)) {
			dsp->fRec154[l154] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l155;
		for (l155 = 0; (l155 < 3); l155 = (l155 + 1)) {
			dsp->fRec153[l155] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l156;
		for (l156 = 0; (l156 < 3); l156 = (l156 + 1)) {
			dsp->fRec152[l156] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l157;
		for (l157 = 0; (l157 < 3); l157 = (l157 + 1)) {
			dsp->fRec151[l157] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l158;
		for (l158 = 0; (l158 < 3); l158 = (l158 + 1)) {
			dsp->fRec150[l158] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l159;
		for (l159 = 0; (l159 < 2); l159 = (l159 + 1)) {
			dsp->fRec160[l159] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l160;
		for (l160 = 0; (l160 < 3); l160 = (l160 + 1)) {
			dsp->fRec159[l160] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l161;
		for (l161 = 0; (l161 < 2); l161 = (l161 + 1)) {
			dsp->fVec20[l161] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l162;
		for (l162 = 0; (l162 < 2); l162 = (l162 + 1)) {
			dsp->fRec158[l162] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l163;
		for (l163 = 0; (l163 < 3); l163 = (l163 + 1)) {
			dsp->fRec157[l163] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l164;
		for (l164 = 0; (l164 < 3); l164 = (l164 + 1)) {
			dsp->fRec156[l164] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l165;
		for (l165 = 0; (l165 < 3); l165 = (l165 + 1)) {
			dsp->fRec155[l165] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l166;
		for (l166 = 0; (l166 < 2); l166 = (l166 + 1)) {
			dsp->fRec165[l166] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l167;
		for (l167 = 0; (l167 < 3); l167 = (l167 + 1)) {
			dsp->fRec164[l167] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l168;
		for (l168 = 0; (l168 < 2); l168 = (l168 + 1)) {
			dsp->fVec21[l168] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l169;
		for (l169 = 0; (l169 < 2); l169 = (l169 + 1)) {
			dsp->fRec163[l169] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l170;
		for (l170 = 0; (l170 < 3); l170 = (l170 + 1)) {
			dsp->fRec162[l170] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l171;
		for (l171 = 0; (l171 < 3); l171 = (l171 + 1)) {
			dsp->fRec161[l171] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l172;
		for (l172 = 0; (l172 < 2); l172 = (l172 + 1)) {
			dsp->fRec169[l172] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l173;
		for (l173 = 0; (l173 < 3); l173 = (l173 + 1)) {
			dsp->fRec168[l173] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l174;
		for (l174 = 0; (l174 < 2); l174 = (l174 + 1)) {
			dsp->fVec22[l174] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l175;
		for (l175 = 0; (l175 < 2); l175 = (l175 + 1)) {
			dsp->fRec167[l175] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l176;
		for (l176 = 0; (l176 < 3); l176 = (l176 + 1)) {
			dsp->fRec166[l176] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l177;
		for (l177 = 0; (l177 < 2); l177 = (l177 + 1)) {
			dsp->fRec171[l177] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l178;
		for (l178 = 0; (l178 < 3); l178 = (l178 + 1)) {
			dsp->fRec170[l178] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l179;
		for (l179 = 0; (l179 < 2); l179 = (l179 + 1)) {
			dsp->fRec176[l179] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l180;
		for (l180 = 0; (l180 < 3); l180 = (l180 + 1)) {
			dsp->fRec175[l180] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l181;
		for (l181 = 0; (l181 < 3); l181 = (l181 + 1)) {
			dsp->fRec174[l181] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l182;
		for (l182 = 0; (l182 < 3); l182 = (l182 + 1)) {
			dsp->fRec173[l182] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l183;
		for (l183 = 0; (l183 < 3); l183 = (l183 + 1)) {
			dsp->fRec172[l183] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l184;
		for (l184 = 0; (l184 < 2); l184 = (l184 + 1)) {
			dsp->fRec182[l184] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l185;
		for (l185 = 0; (l185 < 3); l185 = (l185 + 1)) {
			dsp->fRec181[l185] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l186;
		for (l186 = 0; (l186 < 2); l186 = (l186 + 1)) {
			dsp->fVec23[l186] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l187;
		for (l187 = 0; (l187 < 2); l187 = (l187 + 1)) {
			dsp->fRec180[l187] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l188;
		for (l188 = 0; (l188 < 3); l188 = (l188 + 1)) {
			dsp->fRec179[l188] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l189;
		for (l189 = 0; (l189 < 3); l189 = (l189 + 1)) {
			dsp->fRec178[l189] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l190;
		for (l190 = 0; (l190 < 3); l190 = (l190 + 1)) {
			dsp->fRec177[l190] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l191;
		for (l191 = 0; (l191 < 2); l191 = (l191 + 1)) {
			dsp->fRec187[l191] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l192;
		for (l192 = 0; (l192 < 3); l192 = (l192 + 1)) {
			dsp->fRec186[l192] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l193;
		for (l193 = 0; (l193 < 2); l193 = (l193 + 1)) {
			dsp->fVec24[l193] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l194;
		for (l194 = 0; (l194 < 2); l194 = (l194 + 1)) {
			dsp->fRec185[l194] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l195;
		for (l195 = 0; (l195 < 3); l195 = (l195 + 1)) {
			dsp->fRec184[l195] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l196;
		for (l196 = 0; (l196 < 3); l196 = (l196 + 1)) {
			dsp->fRec183[l196] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l197;
		for (l197 = 0; (l197 < 2); l197 = (l197 + 1)) {
			dsp->fRec191[l197] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l198;
		for (l198 = 0; (l198 < 3); l198 = (l198 + 1)) {
			dsp->fRec190[l198] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l199;
		for (l199 = 0; (l199 < 2); l199 = (l199 + 1)) {
			dsp->fVec25[l199] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l200;
		for (l200 = 0; (l200 < 2); l200 = (l200 + 1)) {
			dsp->fRec189[l200] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l201;
		for (l201 = 0; (l201 < 3); l201 = (l201 + 1)) {
			dsp->fRec188[l201] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l202;
		for (l202 = 0; (l202 < 2); l202 = (l202 + 1)) {
			dsp->fRec193[l202] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l203;
		for (l203 = 0; (l203 < 3); l203 = (l203 + 1)) {
			dsp->fRec192[l203] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l204;
		for (l204 = 0; (l204 < 2); l204 = (l204 + 1)) {
			dsp->fRec198[l204] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l205;
		for (l205 = 0; (l205 < 3); l205 = (l205 + 1)) {
			dsp->fRec197[l205] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l206;
		for (l206 = 0; (l206 < 3); l206 = (l206 + 1)) {
			dsp->fRec196[l206] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l207;
		for (l207 = 0; (l207 < 3); l207 = (l207 + 1)) {
			dsp->fRec195[l207] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l208;
		for (l208 = 0; (l208 < 3); l208 = (l208 + 1)) {
			dsp->fRec194[l208] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l209;
		for (l209 = 0; (l209 < 2); l209 = (l209 + 1)) {
			dsp->fRec204[l209] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l210;
		for (l210 = 0; (l210 < 3); l210 = (l210 + 1)) {
			dsp->fRec203[l210] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l211;
		for (l211 = 0; (l211 < 2); l211 = (l211 + 1)) {
			dsp->fVec26[l211] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l212;
		for (l212 = 0; (l212 < 2); l212 = (l212 + 1)) {
			dsp->fRec202[l212] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l213;
		for (l213 = 0; (l213 < 3); l213 = (l213 + 1)) {
			dsp->fRec201[l213] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l214;
		for (l214 = 0; (l214 < 3); l214 = (l214 + 1)) {
			dsp->fRec200[l214] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l215;
		for (l215 = 0; (l215 < 3); l215 = (l215 + 1)) {
			dsp->fRec199[l215] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l216;
		for (l216 = 0; (l216 < 2); l216 = (l216 + 1)) {
			dsp->fRec209[l216] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l217;
		for (l217 = 0; (l217 < 3); l217 = (l217 + 1)) {
			dsp->fRec208[l217] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l218;
		for (l218 = 0; (l218 < 2); l218 = (l218 + 1)) {
			dsp->fVec27[l218] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l219;
		for (l219 = 0; (l219 < 2); l219 = (l219 + 1)) {
			dsp->fRec207[l219] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l220;
		for (l220 = 0; (l220 < 3); l220 = (l220 + 1)) {
			dsp->fRec206[l220] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l221;
		for (l221 = 0; (l221 < 3); l221 = (l221 + 1)) {
			dsp->fRec205[l221] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l222;
		for (l222 = 0; (l222 < 2); l222 = (l222 + 1)) {
			dsp->fRec213[l222] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l223;
		for (l223 = 0; (l223 < 3); l223 = (l223 + 1)) {
			dsp->fRec212[l223] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l224;
		for (l224 = 0; (l224 < 2); l224 = (l224 + 1)) {
			dsp->fVec28[l224] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l225;
		for (l225 = 0; (l225 < 2); l225 = (l225 + 1)) {
			dsp->fRec211[l225] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l226;
		for (l226 = 0; (l226 < 3); l226 = (l226 + 1)) {
			dsp->fRec210[l226] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l227;
		for (l227 = 0; (l227 < 2); l227 = (l227 + 1)) {
			dsp->fRec215[l227] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l228;
		for (l228 = 0; (l228 < 3); l228 = (l228 + 1)) {
			dsp->fRec214[l228] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l229;
		for (l229 = 0; (l229 < 2); l229 = (l229 + 1)) {
			dsp->fRec220[l229] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l230;
		for (l230 = 0; (l230 < 3); l230 = (l230 + 1)) {
			dsp->fRec219[l230] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l231;
		for (l231 = 0; (l231 < 3); l231 = (l231 + 1)) {
			dsp->fRec218[l231] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l232;
		for (l232 = 0; (l232 < 3); l232 = (l232 + 1)) {
			dsp->fRec217[l232] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l233;
		for (l233 = 0; (l233 < 3); l233 = (l233 + 1)) {
			dsp->fRec216[l233] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l234;
		for (l234 = 0; (l234 < 2); l234 = (l234 + 1)) {
			dsp->fRec226[l234] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l235;
		for (l235 = 0; (l235 < 3); l235 = (l235 + 1)) {
			dsp->fRec225[l235] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l236;
		for (l236 = 0; (l236 < 2); l236 = (l236 + 1)) {
			dsp->fVec29[l236] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l237;
		for (l237 = 0; (l237 < 2); l237 = (l237 + 1)) {
			dsp->fRec224[l237] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l238;
		for (l238 = 0; (l238 < 3); l238 = (l238 + 1)) {
			dsp->fRec223[l238] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l239;
		for (l239 = 0; (l239 < 3); l239 = (l239 + 1)) {
			dsp->fRec222[l239] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l240;
		for (l240 = 0; (l240 < 3); l240 = (l240 + 1)) {
			dsp->fRec221[l240] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l241;
		for (l241 = 0; (l241 < 2); l241 = (l241 + 1)) {
			dsp->fRec231[l241] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l242;
		for (l242 = 0; (l242 < 3); l242 = (l242 + 1)) {
			dsp->fRec230[l242] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l243;
		for (l243 = 0; (l243 < 2); l243 = (l243 + 1)) {
			dsp->fVec30[l243] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l244;
		for (l244 = 0; (l244 < 2); l244 = (l244 + 1)) {
			dsp->fRec229[l244] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l245;
		for (l245 = 0; (l245 < 3); l245 = (l245 + 1)) {
			dsp->fRec228[l245] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l246;
		for (l246 = 0; (l246 < 3); l246 = (l246 + 1)) {
			dsp->fRec227[l246] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l247;
		for (l247 = 0; (l247 < 2); l247 = (l247 + 1)) {
			dsp->fRec235[l247] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l248;
		for (l248 = 0; (l248 < 3); l248 = (l248 + 1)) {
			dsp->fRec234[l248] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l249;
		for (l249 = 0; (l249 < 2); l249 = (l249 + 1)) {
			dsp->fVec31[l249] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l250;
		for (l250 = 0; (l250 < 2); l250 = (l250 + 1)) {
			dsp->fRec233[l250] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l251;
		for (l251 = 0; (l251 < 3); l251 = (l251 + 1)) {
			dsp->fRec232[l251] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l252;
		for (l252 = 0; (l252 < 2); l252 = (l252 + 1)) {
			dsp->fRec237[l252] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l253;
		for (l253 = 0; (l253 < 3); l253 = (l253 + 1)) {
			dsp->fRec236[l253] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l254;
		for (l254 = 0; (l254 < 2); l254 = (l254 + 1)) {
			dsp->fRec242[l254] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l255;
		for (l255 = 0; (l255 < 3); l255 = (l255 + 1)) {
			dsp->fRec241[l255] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l256;
		for (l256 = 0; (l256 < 3); l256 = (l256 + 1)) {
			dsp->fRec240[l256] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l257;
		for (l257 = 0; (l257 < 3); l257 = (l257 + 1)) {
			dsp->fRec239[l257] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l258;
		for (l258 = 0; (l258 < 3); l258 = (l258 + 1)) {
			dsp->fRec238[l258] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l259;
		for (l259 = 0; (l259 < 2); l259 = (l259 + 1)) {
			dsp->fRec248[l259] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l260;
		for (l260 = 0; (l260 < 3); l260 = (l260 + 1)) {
			dsp->fRec247[l260] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l261;
		for (l261 = 0; (l261 < 2); l261 = (l261 + 1)) {
			dsp->fVec32[l261] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l262;
		for (l262 = 0; (l262 < 2); l262 = (l262 + 1)) {
			dsp->fRec246[l262] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l263;
		for (l263 = 0; (l263 < 3); l263 = (l263 + 1)) {
			dsp->fRec245[l263] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l264;
		for (l264 = 0; (l264 < 3); l264 = (l264 + 1)) {
			dsp->fRec244[l264] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l265;
		for (l265 = 0; (l265 < 3); l265 = (l265 + 1)) {
			dsp->fRec243[l265] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l266;
		for (l266 = 0; (l266 < 2); l266 = (l266 + 1)) {
			dsp->fRec253[l266] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l267;
		for (l267 = 0; (l267 < 3); l267 = (l267 + 1)) {
			dsp->fRec252[l267] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l268;
		for (l268 = 0; (l268 < 2); l268 = (l268 + 1)) {
			dsp->fVec33[l268] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l269;
		for (l269 = 0; (l269 < 2); l269 = (l269 + 1)) {
			dsp->fRec251[l269] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l270;
		for (l270 = 0; (l270 < 3); l270 = (l270 + 1)) {
			dsp->fRec250[l270] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l271;
		for (l271 = 0; (l271 < 3); l271 = (l271 + 1)) {
			dsp->fRec249[l271] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l272;
		for (l272 = 0; (l272 < 2); l272 = (l272 + 1)) {
			dsp->fRec257[l272] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l273;
		for (l273 = 0; (l273 < 3); l273 = (l273 + 1)) {
			dsp->fRec256[l273] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l274;
		for (l274 = 0; (l274 < 2); l274 = (l274 + 1)) {
			dsp->fVec34[l274] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l275;
		for (l275 = 0; (l275 < 2); l275 = (l275 + 1)) {
			dsp->fRec255[l275] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l276;
		for (l276 = 0; (l276 < 3); l276 = (l276 + 1)) {
			dsp->fRec254[l276] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l277;
		for (l277 = 0; (l277 < 2); l277 = (l277 + 1)) {
			dsp->fRec259[l277] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l278;
		for (l278 = 0; (l278 < 3); l278 = (l278 + 1)) {
			dsp->fRec258[l278] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l279;
		for (l279 = 0; (l279 < 2); l279 = (l279 + 1)) {
			dsp->fRec264[l279] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l280;
		for (l280 = 0; (l280 < 3); l280 = (l280 + 1)) {
			dsp->fRec263[l280] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l281;
		for (l281 = 0; (l281 < 3); l281 = (l281 + 1)) {
			dsp->fRec262[l281] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l282;
		for (l282 = 0; (l282 < 3); l282 = (l282 + 1)) {
			dsp->fRec261[l282] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l283;
		for (l283 = 0; (l283 < 3); l283 = (l283 + 1)) {
			dsp->fRec260[l283] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l284;
		for (l284 = 0; (l284 < 2); l284 = (l284 + 1)) {
			dsp->fRec270[l284] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l285;
		for (l285 = 0; (l285 < 3); l285 = (l285 + 1)) {
			dsp->fRec269[l285] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l286;
		for (l286 = 0; (l286 < 2); l286 = (l286 + 1)) {
			dsp->fVec35[l286] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l287;
		for (l287 = 0; (l287 < 2); l287 = (l287 + 1)) {
			dsp->fRec268[l287] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l288;
		for (l288 = 0; (l288 < 3); l288 = (l288 + 1)) {
			dsp->fRec267[l288] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l289;
		for (l289 = 0; (l289 < 3); l289 = (l289 + 1)) {
			dsp->fRec266[l289] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l290;
		for (l290 = 0; (l290 < 3); l290 = (l290 + 1)) {
			dsp->fRec265[l290] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l291;
		for (l291 = 0; (l291 < 2); l291 = (l291 + 1)) {
			dsp->fRec275[l291] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l292;
		for (l292 = 0; (l292 < 3); l292 = (l292 + 1)) {
			dsp->fRec274[l292] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l293;
		for (l293 = 0; (l293 < 2); l293 = (l293 + 1)) {
			dsp->fVec36[l293] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l294;
		for (l294 = 0; (l294 < 2); l294 = (l294 + 1)) {
			dsp->fRec273[l294] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l295;
		for (l295 = 0; (l295 < 3); l295 = (l295 + 1)) {
			dsp->fRec272[l295] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l296;
		for (l296 = 0; (l296 < 3); l296 = (l296 + 1)) {
			dsp->fRec271[l296] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l297;
		for (l297 = 0; (l297 < 2); l297 = (l297 + 1)) {
			dsp->fRec279[l297] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l298;
		for (l298 = 0; (l298 < 3); l298 = (l298 + 1)) {
			dsp->fRec278[l298] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l299;
		for (l299 = 0; (l299 < 2); l299 = (l299 + 1)) {
			dsp->fVec37[l299] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l300;
		for (l300 = 0; (l300 < 2); l300 = (l300 + 1)) {
			dsp->fRec277[l300] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l301;
		for (l301 = 0; (l301 < 3); l301 = (l301 + 1)) {
			dsp->fRec276[l301] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l302;
		for (l302 = 0; (l302 < 2); l302 = (l302 + 1)) {
			dsp->fRec281[l302] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l303;
		for (l303 = 0; (l303 < 3); l303 = (l303 + 1)) {
			dsp->fRec280[l303] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l304;
		for (l304 = 0; (l304 < 2); l304 = (l304 + 1)) {
			dsp->fRec286[l304] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l305;
		for (l305 = 0; (l305 < 3); l305 = (l305 + 1)) {
			dsp->fRec285[l305] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l306;
		for (l306 = 0; (l306 < 3); l306 = (l306 + 1)) {
			dsp->fRec284[l306] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l307;
		for (l307 = 0; (l307 < 3); l307 = (l307 + 1)) {
			dsp->fRec283[l307] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l308;
		for (l308 = 0; (l308 < 3); l308 = (l308 + 1)) {
			dsp->fRec282[l308] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l309;
		for (l309 = 0; (l309 < 2); l309 = (l309 + 1)) {
			dsp->fRec292[l309] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l310;
		for (l310 = 0; (l310 < 3); l310 = (l310 + 1)) {
			dsp->fRec291[l310] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l311;
		for (l311 = 0; (l311 < 2); l311 = (l311 + 1)) {
			dsp->fVec38[l311] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l312;
		for (l312 = 0; (l312 < 2); l312 = (l312 + 1)) {
			dsp->fRec290[l312] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l313;
		for (l313 = 0; (l313 < 3); l313 = (l313 + 1)) {
			dsp->fRec289[l313] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l314;
		for (l314 = 0; (l314 < 3); l314 = (l314 + 1)) {
			dsp->fRec288[l314] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l315;
		for (l315 = 0; (l315 < 3); l315 = (l315 + 1)) {
			dsp->fRec287[l315] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l316;
		for (l316 = 0; (l316 < 2); l316 = (l316 + 1)) {
			dsp->fRec297[l316] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l317;
		for (l317 = 0; (l317 < 3); l317 = (l317 + 1)) {
			dsp->fRec296[l317] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l318;
		for (l318 = 0; (l318 < 2); l318 = (l318 + 1)) {
			dsp->fVec39[l318] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l319;
		for (l319 = 0; (l319 < 2); l319 = (l319 + 1)) {
			dsp->fRec295[l319] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l320;
		for (l320 = 0; (l320 < 3); l320 = (l320 + 1)) {
			dsp->fRec294[l320] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l321;
		for (l321 = 0; (l321 < 3); l321 = (l321 + 1)) {
			dsp->fRec293[l321] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l322;
		for (l322 = 0; (l322 < 2); l322 = (l322 + 1)) {
			dsp->fRec301[l322] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l323;
		for (l323 = 0; (l323 < 3); l323 = (l323 + 1)) {
			dsp->fRec300[l323] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l324;
		for (l324 = 0; (l324 < 2); l324 = (l324 + 1)) {
			dsp->fVec40[l324] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l325;
		for (l325 = 0; (l325 < 2); l325 = (l325 + 1)) {
			dsp->fRec299[l325] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l326;
		for (l326 = 0; (l326 < 3); l326 = (l326 + 1)) {
			dsp->fRec298[l326] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l327;
		for (l327 = 0; (l327 < 2); l327 = (l327 + 1)) {
			dsp->fRec303[l327] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l328;
		for (l328 = 0; (l328 < 3); l328 = (l328 + 1)) {
			dsp->fRec302[l328] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l329;
		for (l329 = 0; (l329 < 2); l329 = (l329 + 1)) {
			dsp->fRec308[l329] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l330;
		for (l330 = 0; (l330 < 3); l330 = (l330 + 1)) {
			dsp->fRec307[l330] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l331;
		for (l331 = 0; (l331 < 3); l331 = (l331 + 1)) {
			dsp->fRec306[l331] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l332;
		for (l332 = 0; (l332 < 3); l332 = (l332 + 1)) {
			dsp->fRec305[l332] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l333;
		for (l333 = 0; (l333 < 3); l333 = (l333 + 1)) {
			dsp->fRec304[l333] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l334;
		for (l334 = 0; (l334 < 2); l334 = (l334 + 1)) {
			dsp->fRec314[l334] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l335;
		for (l335 = 0; (l335 < 3); l335 = (l335 + 1)) {
			dsp->fRec313[l335] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l336;
		for (l336 = 0; (l336 < 2); l336 = (l336 + 1)) {
			dsp->fVec41[l336] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l337;
		for (l337 = 0; (l337 < 2); l337 = (l337 + 1)) {
			dsp->fRec312[l337] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l338;
		for (l338 = 0; (l338 < 3); l338 = (l338 + 1)) {
			dsp->fRec311[l338] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l339;
		for (l339 = 0; (l339 < 3); l339 = (l339 + 1)) {
			dsp->fRec310[l339] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l340;
		for (l340 = 0; (l340 < 3); l340 = (l340 + 1)) {
			dsp->fRec309[l340] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l341;
		for (l341 = 0; (l341 < 2); l341 = (l341 + 1)) {
			dsp->fRec319[l341] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l342;
		for (l342 = 0; (l342 < 3); l342 = (l342 + 1)) {
			dsp->fRec318[l342] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l343;
		for (l343 = 0; (l343 < 2); l343 = (l343 + 1)) {
			dsp->fVec42[l343] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l344;
		for (l344 = 0; (l344 < 2); l344 = (l344 + 1)) {
			dsp->fRec317[l344] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l345;
		for (l345 = 0; (l345 < 3); l345 = (l345 + 1)) {
			dsp->fRec316[l345] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l346;
		for (l346 = 0; (l346 < 3); l346 = (l346 + 1)) {
			dsp->fRec315[l346] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l347;
		for (l347 = 0; (l347 < 2); l347 = (l347 + 1)) {
			dsp->fRec323[l347] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l348;
		for (l348 = 0; (l348 < 3); l348 = (l348 + 1)) {
			dsp->fRec322[l348] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l349;
		for (l349 = 0; (l349 < 2); l349 = (l349 + 1)) {
			dsp->fVec43[l349] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l350;
		for (l350 = 0; (l350 < 2); l350 = (l350 + 1)) {
			dsp->fRec321[l350] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l351;
		for (l351 = 0; (l351 < 3); l351 = (l351 + 1)) {
			dsp->fRec320[l351] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l352;
		for (l352 = 0; (l352 < 2); l352 = (l352 + 1)) {
			dsp->fRec325[l352] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l353;
		for (l353 = 0; (l353 < 3); l353 = (l353 + 1)) {
			dsp->fRec324[l353] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l354;
		for (l354 = 0; (l354 < 2); l354 = (l354 + 1)) {
			dsp->fRec330[l354] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l355;
		for (l355 = 0; (l355 < 3); l355 = (l355 + 1)) {
			dsp->fRec329[l355] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l356;
		for (l356 = 0; (l356 < 3); l356 = (l356 + 1)) {
			dsp->fRec328[l356] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l357;
		for (l357 = 0; (l357 < 3); l357 = (l357 + 1)) {
			dsp->fRec327[l357] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l358;
		for (l358 = 0; (l358 < 3); l358 = (l358 + 1)) {
			dsp->fRec326[l358] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l359;
		for (l359 = 0; (l359 < 2); l359 = (l359 + 1)) {
			dsp->fRec336[l359] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l360;
		for (l360 = 0; (l360 < 3); l360 = (l360 + 1)) {
			dsp->fRec335[l360] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l361;
		for (l361 = 0; (l361 < 2); l361 = (l361 + 1)) {
			dsp->fVec44[l361] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l362;
		for (l362 = 0; (l362 < 2); l362 = (l362 + 1)) {
			dsp->fRec334[l362] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l363;
		for (l363 = 0; (l363 < 3); l363 = (l363 + 1)) {
			dsp->fRec333[l363] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l364;
		for (l364 = 0; (l364 < 3); l364 = (l364 + 1)) {
			dsp->fRec332[l364] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l365;
		for (l365 = 0; (l365 < 3); l365 = (l365 + 1)) {
			dsp->fRec331[l365] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l366;
		for (l366 = 0; (l366 < 2); l366 = (l366 + 1)) {
			dsp->fRec341[l366] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l367;
		for (l367 = 0; (l367 < 3); l367 = (l367 + 1)) {
			dsp->fRec340[l367] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l368;
		for (l368 = 0; (l368 < 2); l368 = (l368 + 1)) {
			dsp->fVec45[l368] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l369;
		for (l369 = 0; (l369 < 2); l369 = (l369 + 1)) {
			dsp->fRec339[l369] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l370;
		for (l370 = 0; (l370 < 3); l370 = (l370 + 1)) {
			dsp->fRec338[l370] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l371;
		for (l371 = 0; (l371 < 3); l371 = (l371 + 1)) {
			dsp->fRec337[l371] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l372;
		for (l372 = 0; (l372 < 2); l372 = (l372 + 1)) {
			dsp->fRec345[l372] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l373;
		for (l373 = 0; (l373 < 3); l373 = (l373 + 1)) {
			dsp->fRec344[l373] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l374;
		for (l374 = 0; (l374 < 2); l374 = (l374 + 1)) {
			dsp->fVec46[l374] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l375;
		for (l375 = 0; (l375 < 2); l375 = (l375 + 1)) {
			dsp->fRec343[l375] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l376;
		for (l376 = 0; (l376 < 3); l376 = (l376 + 1)) {
			dsp->fRec342[l376] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l377;
		for (l377 = 0; (l377 < 2); l377 = (l377 + 1)) {
			dsp->fRec347[l377] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l378;
		for (l378 = 0; (l378 < 3); l378 = (l378 + 1)) {
			dsp->fRec346[l378] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l379;
		for (l379 = 0; (l379 < 2); l379 = (l379 + 1)) {
			dsp->fRec352[l379] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l380;
		for (l380 = 0; (l380 < 3); l380 = (l380 + 1)) {
			dsp->fRec351[l380] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l381;
		for (l381 = 0; (l381 < 3); l381 = (l381 + 1)) {
			dsp->fRec350[l381] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l382;
		for (l382 = 0; (l382 < 3); l382 = (l382 + 1)) {
			dsp->fRec349[l382] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l383;
		for (l383 = 0; (l383 < 3); l383 = (l383 + 1)) {
			dsp->fRec348[l383] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l384;
		for (l384 = 0; (l384 < 2); l384 = (l384 + 1)) {
			dsp->fRec358[l384] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l385;
		for (l385 = 0; (l385 < 3); l385 = (l385 + 1)) {
			dsp->fRec357[l385] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l386;
		for (l386 = 0; (l386 < 2); l386 = (l386 + 1)) {
			dsp->fVec47[l386] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l387;
		for (l387 = 0; (l387 < 2); l387 = (l387 + 1)) {
			dsp->fRec356[l387] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l388;
		for (l388 = 0; (l388 < 3); l388 = (l388 + 1)) {
			dsp->fRec355[l388] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l389;
		for (l389 = 0; (l389 < 3); l389 = (l389 + 1)) {
			dsp->fRec354[l389] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l390;
		for (l390 = 0; (l390 < 3); l390 = (l390 + 1)) {
			dsp->fRec353[l390] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l391;
		for (l391 = 0; (l391 < 2); l391 = (l391 + 1)) {
			dsp->fRec363[l391] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l392;
		for (l392 = 0; (l392 < 3); l392 = (l392 + 1)) {
			dsp->fRec362[l392] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l393;
		for (l393 = 0; (l393 < 2); l393 = (l393 + 1)) {
			dsp->fVec48[l393] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l394;
		for (l394 = 0; (l394 < 2); l394 = (l394 + 1)) {
			dsp->fRec361[l394] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l395;
		for (l395 = 0; (l395 < 3); l395 = (l395 + 1)) {
			dsp->fRec360[l395] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l396;
		for (l396 = 0; (l396 < 3); l396 = (l396 + 1)) {
			dsp->fRec359[l396] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l397;
		for (l397 = 0; (l397 < 2); l397 = (l397 + 1)) {
			dsp->fRec367[l397] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l398;
		for (l398 = 0; (l398 < 3); l398 = (l398 + 1)) {
			dsp->fRec366[l398] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l399;
		for (l399 = 0; (l399 < 2); l399 = (l399 + 1)) {
			dsp->fVec49[l399] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l400;
		for (l400 = 0; (l400 < 2); l400 = (l400 + 1)) {
			dsp->fRec365[l400] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l401;
		for (l401 = 0; (l401 < 3); l401 = (l401 + 1)) {
			dsp->fRec364[l401] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l402;
		for (l402 = 0; (l402 < 2); l402 = (l402 + 1)) {
			dsp->fRec369[l402] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l403;
		for (l403 = 0; (l403 < 3); l403 = (l403 + 1)) {
			dsp->fRec368[l403] = 0.0f;
			
		}
		
	}
	dsp->IOTA = 0;
	/* C99 loop */
	{
		int l404;
		for (l404 = 0; (l404 < 16384); l404 = (l404 + 1)) {
			dsp->fVec50[l404] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l405;
		for (l405 = 0; (l405 < 3); l405 = (l405 + 1)) {
			dsp->fRec0[l405] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l406;
		for (l406 = 0; (l406 < 2); l406 = (l406 + 1)) {
			dsp->fVec51[l406] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l407;
		for (l407 = 0; (l407 < 16384); l407 = (l407 + 1)) {
			dsp->fVec52[l407] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l408;
		for (l408 = 0; (l408 < 3); l408 = (l408 + 1)) {
			dsp->fRec1[l408] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l409;
		for (l409 = 0; (l409 < 16384); l409 = (l409 + 1)) {
			dsp->fVec53[l409] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l410;
		for (l410 = 0; (l410 < 3); l410 = (l410 + 1)) {
			dsp->fRec2[l410] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l411;
		for (l411 = 0; (l411 < 16384); l411 = (l411 + 1)) {
			dsp->fVec54[l411] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l412;
		for (l412 = 0; (l412 < 3); l412 = (l412 + 1)) {
			dsp->fRec3[l412] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l413;
		for (l413 = 0; (l413 < 16384); l413 = (l413 + 1)) {
			dsp->fVec55[l413] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l414;
		for (l414 = 0; (l414 < 3); l414 = (l414 + 1)) {
			dsp->fRec4[l414] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l415;
		for (l415 = 0; (l415 < 16384); l415 = (l415 + 1)) {
			dsp->fVec56[l415] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l416;
		for (l416 = 0; (l416 < 3); l416 = (l416 + 1)) {
			dsp->fRec5[l416] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l417;
		for (l417 = 0; (l417 < 16384); l417 = (l417 + 1)) {
			dsp->fVec57[l417] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l418;
		for (l418 = 0; (l418 < 3); l418 = (l418 + 1)) {
			dsp->fRec6[l418] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l419;
		for (l419 = 0; (l419 < 16384); l419 = (l419 + 1)) {
			dsp->fVec58[l419] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l420;
		for (l420 = 0; (l420 < 3); l420 = (l420 + 1)) {
			dsp->fRec7[l420] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l421;
		for (l421 = 0; (l421 < 16384); l421 = (l421 + 1)) {
			dsp->fVec59[l421] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l422;
		for (l422 = 0; (l422 < 3); l422 = (l422 + 1)) {
			dsp->fRec8[l422] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l423;
		for (l423 = 0; (l423 < 16384); l423 = (l423 + 1)) {
			dsp->fVec60[l423] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l424;
		for (l424 = 0; (l424 < 3); l424 = (l424 + 1)) {
			dsp->fRec9[l424] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l425;
		for (l425 = 0; (l425 < 16384); l425 = (l425 + 1)) {
			dsp->fVec61[l425] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l426;
		for (l426 = 0; (l426 < 3); l426 = (l426 + 1)) {
			dsp->fRec10[l426] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l427;
		for (l427 = 0; (l427 < 16384); l427 = (l427 + 1)) {
			dsp->fVec62[l427] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l428;
		for (l428 = 0; (l428 < 3); l428 = (l428 + 1)) {
			dsp->fRec11[l428] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l429;
		for (l429 = 0; (l429 < 16384); l429 = (l429 + 1)) {
			dsp->fVec63[l429] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l430;
		for (l430 = 0; (l430 < 3); l430 = (l430 + 1)) {
			dsp->fRec12[l430] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l431;
		for (l431 = 0; (l431 < 16384); l431 = (l431 + 1)) {
			dsp->fVec64[l431] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l432;
		for (l432 = 0; (l432 < 3); l432 = (l432 + 1)) {
			dsp->fRec13[l432] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l433;
		for (l433 = 0; (l433 < 16384); l433 = (l433 + 1)) {
			dsp->fVec65[l433] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l434;
		for (l434 = 0; (l434 < 3); l434 = (l434 + 1)) {
			dsp->fRec14[l434] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l435;
		for (l435 = 0; (l435 < 16384); l435 = (l435 + 1)) {
			dsp->fVec66[l435] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l436;
		for (l436 = 0; (l436 < 3); l436 = (l436 + 1)) {
			dsp->fRec15[l436] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = (1.0f / dsp->fConst0);
	dsp->fConst2 = (0.002915452f * dsp->fConst0);
	dsp->fConst3 = (3.14159274f / dsp->fConst0);
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "fdnRev");
	ui_interface->declare(ui_interface->uiInterface, 0, "tooltip", "See Faust's reverbs.lib for documentation and references");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "FEEDBACK DELAY NETWORK (FDN) REVERBERATOR, ORDER 16");
	ui_interface->declare(ui_interface->uiInterface, 0, "1", "");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "Band Crossover Frequencies");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider6, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider6, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider6, "tooltip", "Each delay-line signal is split into frequency-bands for separate  decay-time control in each band");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider6, "unit", "Hz");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Band 0 upper edge in Hz", &dsp->fHslider6, 500.0f, 100.0f, 10000.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "tooltip", "Each delay-line signal is split into frequency-bands for separate  decay-time control in each band");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "unit", "Hz");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Band 1 upper edge in Hz", &dsp->fHslider5, 1000.0f, 100.0f, 10000.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "tooltip", "Each delay-line signal is split into frequency-bands for separate  decay-time control in each band");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "unit", "Hz");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Band 2 upper edge in Hz", &dsp->fHslider4, 2000.0f, 100.0f, 10000.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "tooltip", "Each delay-line signal is split into frequency-bands for separate  decay-time control in each band");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "unit", "Hz");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Band 3 upper edge in Hz", &dsp->fHslider3, 4000.0f, 100.0f, 10000.0f, 1.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "2", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "Band Decay Times (T60)");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider4, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider4, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider4, "tooltip", "T60 is the 60dB   decay-time in seconds. For concert halls, an overall reverberation time (T60) near   1.9 seconds is typical [Beranek 2004]. Here we may set T60 independently in each   frequency band.  In real rooms, higher frequency bands generally decay faster due   to absorption and scattering.");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider4, "unit", "s");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "0", &dsp->fVslider4, 8.39999962f, 0.100000001f, 100.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider3, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider3, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider3, "tooltip", "T60 is the 60dB   decay-time in seconds. For concert halls, an overall reverberation time (T60) near   1.9 seconds is typical [Beranek 2004]. Here we may set T60 independently in each   frequency band.  In real rooms, higher frequency bands generally decay faster due   to absorption and scattering.");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider3, "unit", "s");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "1", &dsp->fVslider3, 6.5f, 0.100000001f, 100.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider2, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider2, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider2, "tooltip", "T60 is the 60dB   decay-time in seconds. For concert halls, an overall reverberation time (T60) near   1.9 seconds is typical [Beranek 2004]. Here we may set T60 independently in each   frequency band.  In real rooms, higher frequency bands generally decay faster due   to absorption and scattering.");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider2, "unit", "s");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "2", &dsp->fVslider2, 5.0f, 0.100000001f, 100.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider1, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider1, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider1, "tooltip", "T60 is the 60dB   decay-time in seconds. For concert halls, an overall reverberation time (T60) near   1.9 seconds is typical [Beranek 2004]. Here we may set T60 independently in each   frequency band.  In real rooms, higher frequency bands generally decay faster due   to absorption and scattering.");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider1, "unit", "s");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "3", &dsp->fVslider1, 3.79999995f, 0.100000001f, 100.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider0, "4", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider0, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider0, "tooltip", "T60 is the 60dB   decay-time in seconds. For concert halls, an overall reverberation time (T60) near   1.9 seconds is typical [Beranek 2004]. Here we may set T60 independently in each   frequency band.  In real rooms, higher frequency bands generally decay faster due   to absorption and scattering.");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider0, "unit", "s");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "4", &dsp->fVslider0, 2.70000005f, 0.100000001f, 100.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "3", "");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "Room Dimensions");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "tooltip", "This length (in meters) determines the shortest delay-line used in the FDN  reverberator. Think of it as the shortest wall-to-wall separation in the room.");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "unit", "m");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "min acoustic ray length", &dsp->fHslider1, 46.0f, 0.100000001f, 63.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "tooltip", "This length (in meters) determines the longest delay-line used in the   FDN reverberator. Think of it as the largest wall-to-wall separation in the room.");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "unit", "m");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "max acoustic ray length", &dsp->fHslider2, 63.0f, 0.100000001f, 63.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "4", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "Input Controls");
	ui_interface->declare(ui_interface->uiInterface, 0, "3", "");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "Reverb State");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fButton2, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fButton2, "tooltip", "Hold down 'Quench' to clear the reverberator");
	ui_interface->addButton(ui_interface->uiInterface, "Quench", &dsp->fButton2);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "1", "");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "Input Config");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox1, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox1, "tooltip", "When this is checked, the stereo external audio inputs are   disabled (good for hearing the impulse response or pink-noise response alone)");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Mute Ext Inputs", &dsp->fCheckbox1);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox0, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox0, "tooltip", "Pink Noise (or 1/f noise) is Constant-Q Noise (useful for adjusting   the EQ sections)");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Pink Noise", &dsp->fCheckbox0);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "2", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "Impulse Selection");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fButton1, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fButton1, "tooltip", "Send impulse into LEFT channel");
	ui_interface->addButton(ui_interface->uiInterface, "Left", &dsp->fButton1);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fButton0, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fButton0, "tooltip", "Send impulse into LEFT and RIGHT channels");
	ui_interface->addButton(ui_interface->uiInterface, "Center", &dsp->fButton0);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fButton3, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fButton3, "tooltip", "Send impulse into RIGHT channel");
	ui_interface->addButton(ui_interface->uiInterface, "Right", &dsp->fButton3);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "tooltip", "Output scale factor");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "unit", "dB");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Output Level (dB)", &dsp->fHslider0, -40.0f, -70.0f, 20.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* input0 = inputs[0];
	FAUSTFLOAT* input1 = inputs[1];
	FAUSTFLOAT* input2 = inputs[2];
	FAUSTFLOAT* input3 = inputs[3];
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	float fSlow0 = powf(10.0f, (0.0500000007f * (float)dsp->fHslider0));
	float fSlow1 = (0.100000001f * (float)dsp->fCheckbox0);
	float fSlow2 = (float)dsp->fButton0;
	float fSlow3 = (float)dsp->fButton1;
	float fSlow4 = (1.0f - (float)dsp->fCheckbox1);
	float fSlow5 = (0.25f * (1.0f - (0.5f * (float)dsp->fButton2)));
	float fSlow6 = (float)dsp->fHslider1;
	float fSlow7 = ((float)dsp->fHslider2 / fSlow6);
	float fSlow8 = powf(2.0f, floorf(((1.44269502f * logf((dsp->fConst2 * (fSlow6 * powf(fSlow7, 0.0f))))) + 0.5f)));
	float fSlow9 = (0.0f - (6.90775537f * fSlow8));
	float fSlow10 = (float)dsp->fVslider0;
	float fSlow11 = expf((dsp->fConst1 * (fSlow9 / fSlow10)));
	float fSlow12 = tanf((dsp->fConst3 * (float)dsp->fHslider3));
	float fSlow13 = (1.0f / fSlow12);
	float fSlow14 = (((fSlow13 + 1.0f) / fSlow12) + 1.0f);
	float fSlow15 = (1.0f / fSlow14);
	float fSlow16 = (1.0f / mydsp_faustpower2_f(fSlow12));
	float fSlow17 = (fSlow13 + 1.0f);
	float fSlow18 = (0.0f - ((1.0f - fSlow13) / fSlow17));
	float fSlow19 = (1.0f / fSlow17);
	float fSlow20 = (0.0f - fSlow13);
	float fSlow21 = (2.0f * (1.0f - fSlow16));
	float fSlow22 = (((fSlow13 + -1.0f) / fSlow12) + 1.0f);
	float fSlow23 = (2.0f * (0.0f - fSlow16));
	float fSlow24 = tanf((dsp->fConst3 * (float)dsp->fHslider4));
	float fSlow25 = (1.0f / fSlow24);
	float fSlow26 = (1.0f / (((fSlow25 + 1.0f) / fSlow24) + 1.0f));
	float fSlow27 = (1.0f - ((1.0f - fSlow25) / fSlow24));
	float fSlow28 = (1.0f / mydsp_faustpower2_f(fSlow24));
	float fSlow29 = (2.0f * (1.0f - fSlow28));
	float fSlow30 = tanf((dsp->fConst3 * (float)dsp->fHslider5));
	float fSlow31 = (1.0f / fSlow30);
	float fSlow32 = (1.0f / (((fSlow31 + 1.0f) / fSlow30) + 1.0f));
	float fSlow33 = (1.0f - ((1.0f - fSlow31) / fSlow30));
	float fSlow34 = (1.0f / mydsp_faustpower2_f(fSlow30));
	float fSlow35 = (2.0f * (1.0f - fSlow34));
	float fSlow36 = tanf((dsp->fConst3 * (float)dsp->fHslider6));
	float fSlow37 = (1.0f / fSlow36);
	float fSlow38 = (1.0f / (((fSlow37 + 1.0f) / fSlow36) + 1.0f));
	float fSlow39 = (1.0f - ((1.0f - fSlow37) / fSlow36));
	float fSlow40 = (1.0f / mydsp_faustpower2_f(fSlow36));
	float fSlow41 = (2.0f * (1.0f - fSlow40));
	float fSlow42 = (float)dsp->fVslider1;
	float fSlow43 = expf((dsp->fConst1 * (fSlow9 / fSlow42)));
	float fSlow44 = (((fSlow25 + 1.0f) / fSlow24) + 1.0f);
	float fSlow45 = (1.0f / fSlow44);
	float fSlow46 = (fSlow25 + 1.0f);
	float fSlow47 = (0.0f - ((1.0f - fSlow25) / fSlow46));
	float fSlow48 = (1.0f / fSlow46);
	float fSlow49 = (0.0f - fSlow25);
	float fSlow50 = (1.0f / (fSlow14 * fSlow24));
	float fSlow51 = (((fSlow25 + -1.0f) / fSlow24) + 1.0f);
	float fSlow52 = (2.0f * (0.0f - fSlow28));
	float fSlow53 = (float)dsp->fVslider2;
	float fSlow54 = expf((dsp->fConst1 * (fSlow9 / fSlow53)));
	float fSlow55 = (((fSlow31 + 1.0f) / fSlow30) + 1.0f);
	float fSlow56 = (1.0f / fSlow55);
	float fSlow57 = (fSlow31 + 1.0f);
	float fSlow58 = (0.0f - ((1.0f - fSlow31) / fSlow57));
	float fSlow59 = (1.0f / fSlow57);
	float fSlow60 = (0.0f - fSlow31);
	float fSlow61 = (1.0f / (fSlow44 * fSlow30));
	float fSlow62 = (((fSlow31 + -1.0f) / fSlow30) + 1.0f);
	float fSlow63 = (2.0f * (0.0f - fSlow34));
	float fSlow64 = (1.0f / (((fSlow37 + 1.0f) / fSlow36) + 1.0f));
	float fSlow65 = (float)dsp->fVslider3;
	float fSlow66 = expf((dsp->fConst1 * (fSlow9 / fSlow65)));
	float fSlow67 = (fSlow37 + 1.0f);
	float fSlow68 = (0.0f - ((1.0f - fSlow37) / fSlow67));
	float fSlow69 = (1.0f / fSlow67);
	float fSlow70 = (0.0f - fSlow37);
	float fSlow71 = (1.0f / (fSlow55 * fSlow36));
	float fSlow72 = (((fSlow37 + -1.0f) / fSlow36) + 1.0f);
	float fSlow73 = (2.0f * (0.0f - fSlow40));
	float fSlow74 = (float)dsp->fVslider4;
	float fSlow75 = expf((dsp->fConst1 * (fSlow9 / fSlow74)));
	float fSlow76 = powf(23.0f, floorf(((0.318928987f * logf((dsp->fConst2 * (fSlow6 * powf(fSlow7, 0.533333361f))))) + 0.5f)));
	float fSlow77 = (0.0f - (6.90775537f * fSlow76));
	float fSlow78 = expf((dsp->fConst1 * (fSlow77 / fSlow10)));
	float fSlow79 = expf((dsp->fConst1 * (fSlow77 / fSlow42)));
	float fSlow80 = expf((dsp->fConst1 * (fSlow77 / fSlow53)));
	float fSlow81 = expf((dsp->fConst1 * (fSlow77 / fSlow65)));
	float fSlow82 = expf((dsp->fConst1 * (fSlow77 / fSlow74)));
	float fSlow83 = powf(11.0f, floorf(((0.417032391f * logf((dsp->fConst2 * (fSlow6 * powf(fSlow7, 0.266666681f))))) + 0.5f)));
	float fSlow84 = (0.0f - (6.90775537f * fSlow83));
	float fSlow85 = expf((dsp->fConst1 * (fSlow84 / fSlow10)));
	float fSlow86 = expf((dsp->fConst1 * (fSlow84 / fSlow42)));
	float fSlow87 = expf((dsp->fConst1 * (fSlow84 / fSlow53)));
	float fSlow88 = expf((dsp->fConst1 * (fSlow84 / fSlow65)));
	float fSlow89 = expf((dsp->fConst1 * (fSlow84 / fSlow74)));
	float fSlow90 = powf(41.0f, floorf(((0.26928252f * logf((dsp->fConst2 * (fSlow6 * powf(fSlow7, 0.800000012f))))) + 0.5f)));
	float fSlow91 = (0.0f - (6.90775537f * fSlow90));
	float fSlow92 = expf((dsp->fConst1 * (fSlow91 / fSlow10)));
	float fSlow93 = expf((dsp->fConst1 * (fSlow91 / fSlow42)));
	float fSlow94 = expf((dsp->fConst1 * (fSlow91 / fSlow53)));
	float fSlow95 = expf((dsp->fConst1 * (fSlow91 / fSlow65)));
	float fSlow96 = expf((dsp->fConst1 * (fSlow91 / fSlow74)));
	float fSlow97 = powf(5.0f, floorf(((0.62133491f * logf((dsp->fConst2 * (fSlow6 * powf(fSlow7, 0.13333334f))))) + 0.5f)));
	float fSlow98 = (0.0f - (6.90775537f * fSlow97));
	float fSlow99 = expf((dsp->fConst1 * (fSlow98 / fSlow10)));
	float fSlow100 = expf((dsp->fConst1 * (fSlow98 / fSlow42)));
	float fSlow101 = expf((dsp->fConst1 * (fSlow98 / fSlow53)));
	float fSlow102 = expf((dsp->fConst1 * (fSlow98 / fSlow65)));
	float fSlow103 = expf((dsp->fConst1 * (fSlow98 / fSlow74)));
	float fSlow104 = powf(31.0f, floorf(((0.291206688f * logf((dsp->fConst2 * (fSlow6 * powf(fSlow7, 0.666666687f))))) + 0.5f)));
	float fSlow105 = (0.0f - (6.90775537f * fSlow104));
	float fSlow106 = expf((dsp->fConst1 * (fSlow105 / fSlow10)));
	float fSlow107 = expf((dsp->fConst1 * (fSlow105 / fSlow42)));
	float fSlow108 = expf((dsp->fConst1 * (fSlow105 / fSlow53)));
	float fSlow109 = expf((dsp->fConst1 * (fSlow105 / fSlow65)));
	float fSlow110 = expf((dsp->fConst1 * (fSlow105 / fSlow74)));
	float fSlow111 = powf(17.0f, floorf(((0.352956116f * logf((dsp->fConst2 * (fSlow6 * powf(fSlow7, 0.400000006f))))) + 0.5f)));
	float fSlow112 = (0.0f - (6.90775537f * fSlow111));
	float fSlow113 = expf((dsp->fConst1 * (fSlow112 / fSlow10)));
	float fSlow114 = expf((dsp->fConst1 * (fSlow112 / fSlow42)));
	float fSlow115 = expf((dsp->fConst1 * (fSlow112 / fSlow53)));
	float fSlow116 = expf((dsp->fConst1 * (fSlow112 / fSlow65)));
	float fSlow117 = expf((dsp->fConst1 * (fSlow112 / fSlow74)));
	float fSlow118 = powf(47.0f, floorf(((0.259730309f * logf((dsp->fConst2 * (fSlow6 * powf(fSlow7, 0.933333337f))))) + 0.5f)));
	float fSlow119 = (0.0f - (6.90775537f * fSlow118));
	float fSlow120 = expf((dsp->fConst1 * (fSlow119 / fSlow10)));
	float fSlow121 = expf((dsp->fConst1 * (fSlow119 / fSlow42)));
	float fSlow122 = expf((dsp->fConst1 * (fSlow119 / fSlow53)));
	float fSlow123 = expf((dsp->fConst1 * (fSlow119 / fSlow65)));
	float fSlow124 = expf((dsp->fConst1 * (fSlow119 / fSlow74)));
	float fSlow125 = powf(3.0f, floorf(((0.91023922f * logf((dsp->fConst2 * (fSlow6 * powf(fSlow7, 0.0666666701f))))) + 0.5f)));
	float fSlow126 = (0.0f - (6.90775537f * fSlow125));
	float fSlow127 = expf((dsp->fConst1 * (fSlow126 / fSlow10)));
	float fSlow128 = expf((dsp->fConst1 * (fSlow126 / fSlow42)));
	float fSlow129 = expf((dsp->fConst1 * (fSlow126 / fSlow53)));
	float fSlow130 = expf((dsp->fConst1 * (fSlow126 / fSlow65)));
	float fSlow131 = expf((dsp->fConst1 * (fSlow126 / fSlow74)));
	float fSlow132 = powf(29.0f, floorf(((0.296974212f * logf((dsp->fConst2 * (fSlow6 * powf(fSlow7, 0.600000024f))))) + 0.5f)));
	float fSlow133 = (0.0f - (6.90775537f * fSlow132));
	float fSlow134 = expf((dsp->fConst1 * (fSlow133 / fSlow10)));
	float fSlow135 = expf((dsp->fConst1 * (fSlow133 / fSlow42)));
	float fSlow136 = expf((dsp->fConst1 * (fSlow133 / fSlow53)));
	float fSlow137 = expf((dsp->fConst1 * (fSlow133 / fSlow65)));
	float fSlow138 = expf((dsp->fConst1 * (fSlow133 / fSlow74)));
	float fSlow139 = powf(13.0f, floorf(((0.38987124f * logf((dsp->fConst2 * (fSlow6 * powf(fSlow7, 0.333333343f))))) + 0.5f)));
	float fSlow140 = (0.0f - (6.90775537f * fSlow139));
	float fSlow141 = expf((dsp->fConst1 * (fSlow140 / fSlow10)));
	float fSlow142 = expf((dsp->fConst1 * (fSlow140 / fSlow42)));
	float fSlow143 = expf((dsp->fConst1 * (fSlow140 / fSlow53)));
	float fSlow144 = expf((dsp->fConst1 * (fSlow140 / fSlow65)));
	float fSlow145 = expf((dsp->fConst1 * (fSlow140 / fSlow74)));
	float fSlow146 = powf(43.0f, floorf(((0.265872598f * logf((dsp->fConst2 * (fSlow6 * powf(fSlow7, 0.866666675f))))) + 0.5f)));
	float fSlow147 = (0.0f - (6.90775537f * fSlow146));
	float fSlow148 = expf((dsp->fConst1 * (fSlow147 / fSlow10)));
	float fSlow149 = expf((dsp->fConst1 * (fSlow147 / fSlow42)));
	float fSlow150 = expf((dsp->fConst1 * (fSlow147 / fSlow53)));
	float fSlow151 = expf((dsp->fConst1 * (fSlow147 / fSlow65)));
	float fSlow152 = expf((dsp->fConst1 * (fSlow147 / fSlow74)));
	float fSlow153 = powf(7.0f, floorf(((0.513898313f * logf((dsp->fConst2 * (fSlow6 * powf(fSlow7, 0.200000003f))))) + 0.5f)));
	float fSlow154 = (0.0f - (6.90775537f * fSlow153));
	float fSlow155 = expf((dsp->fConst1 * (fSlow154 / fSlow10)));
	float fSlow156 = expf((dsp->fConst1 * (fSlow154 / fSlow42)));
	float fSlow157 = expf((dsp->fConst1 * (fSlow154 / fSlow53)));
	float fSlow158 = expf((dsp->fConst1 * (fSlow154 / fSlow65)));
	float fSlow159 = expf((dsp->fConst1 * (fSlow154 / fSlow74)));
	float fSlow160 = powf(37.0f, floorf(((0.276937902f * logf((dsp->fConst2 * (fSlow6 * powf(fSlow7, 0.733333349f))))) + 0.5f)));
	float fSlow161 = (0.0f - (6.90775537f * fSlow160));
	float fSlow162 = expf((dsp->fConst1 * (fSlow161 / fSlow10)));
	float fSlow163 = expf((dsp->fConst1 * (fSlow161 / fSlow42)));
	float fSlow164 = expf((dsp->fConst1 * (fSlow161 / fSlow53)));
	float fSlow165 = expf((dsp->fConst1 * (fSlow161 / fSlow65)));
	float fSlow166 = expf((dsp->fConst1 * (fSlow161 / fSlow74)));
	float fSlow167 = powf(19.0f, floorf(((0.339623272f * logf((dsp->fConst2 * (fSlow6 * powf(fSlow7, 0.466666669f))))) + 0.5f)));
	float fSlow168 = (0.0f - (6.90775537f * fSlow167));
	float fSlow169 = expf((dsp->fConst1 * (fSlow168 / fSlow10)));
	float fSlow170 = expf((dsp->fConst1 * (fSlow168 / fSlow42)));
	float fSlow171 = expf((dsp->fConst1 * (fSlow168 / fSlow53)));
	float fSlow172 = expf((dsp->fConst1 * (fSlow168 / fSlow65)));
	float fSlow173 = expf((dsp->fConst1 * (fSlow168 / fSlow74)));
	float fSlow174 = powf(53.0f, floorf(((0.251870662f * logf((dsp->fConst2 * (fSlow6 * powf(fSlow7, 1.0f))))) + 0.5f)));
	float fSlow175 = (0.0f - (6.90775537f * fSlow174));
	float fSlow176 = expf((dsp->fConst1 * (fSlow175 / fSlow10)));
	float fSlow177 = expf((dsp->fConst1 * (fSlow175 / fSlow42)));
	float fSlow178 = expf((dsp->fConst1 * (fSlow175 / fSlow53)));
	float fSlow179 = expf((dsp->fConst1 * (fSlow175 / fSlow65)));
	float fSlow180 = expf((dsp->fConst1 * (fSlow175 / fSlow74)));
	int iSlow181 = (int)min(8192.0f, max(0.0f, (fSlow8 + -1.0f)));
	float fSlow182 = (float)dsp->fButton3;
	int iSlow183 = (int)min(8192.0f, max(0.0f, (fSlow125 + -1.0f)));
	int iSlow184 = (int)min(8192.0f, max(0.0f, (fSlow97 + -1.0f)));
	int iSlow185 = (int)min(8192.0f, max(0.0f, (fSlow153 + -1.0f)));
	int iSlow186 = (int)min(8192.0f, max(0.0f, (fSlow83 + -1.0f)));
	int iSlow187 = (int)min(8192.0f, max(0.0f, (fSlow139 + -1.0f)));
	int iSlow188 = (int)min(8192.0f, max(0.0f, (fSlow111 + -1.0f)));
	int iSlow189 = (int)min(8192.0f, max(0.0f, (fSlow167 + -1.0f)));
	int iSlow190 = (int)min(8192.0f, max(0.0f, (fSlow76 + -1.0f)));
	int iSlow191 = (int)min(8192.0f, max(0.0f, (fSlow132 + -1.0f)));
	int iSlow192 = (int)min(8192.0f, max(0.0f, (fSlow104 + -1.0f)));
	int iSlow193 = (int)min(8192.0f, max(0.0f, (fSlow160 + -1.0f)));
	int iSlow194 = (int)min(8192.0f, max(0.0f, (fSlow90 + -1.0f)));
	int iSlow195 = (int)min(8192.0f, max(0.0f, (fSlow146 + -1.0f)));
	int iSlow196 = (int)min(8192.0f, max(0.0f, (fSlow118 + -1.0f)));
	int iSlow197 = (int)min(8192.0f, max(0.0f, (fSlow174 + -1.0f)));
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->iRec17[0] = ((1103515245 * dsp->iRec17[1]) + 12345);
			dsp->fRec16[0] = (((0.522189379f * dsp->fRec16[3]) + ((4.65661287e-10f * (float)dsp->iRec17[0]) + (2.49495602f * dsp->fRec16[1]))) - (2.0172658f * dsp->fRec16[2]));
			float fTemp0 = (fSlow1 * (((0.0499220341f * dsp->fRec16[0]) + (0.0506126992f * dsp->fRec16[2])) - ((0.0959935337f * dsp->fRec16[1]) + (0.00440878607f * dsp->fRec16[3]))));
			dsp->fVec0[0] = fSlow2;
			int iTemp1 = ((fSlow2 - dsp->fVec0[1]) > 0.0f);
			dsp->fVec1[0] = fSlow3;
			int iTemp2 = ((fSlow3 - dsp->fVec1[1]) > 0.0f);
			float fTemp3 = (fSlow4 * (float)input2[i]);
			dsp->fRec22[0] = ((fSlow18 * dsp->fRec22[1]) + (fSlow19 * ((fSlow13 * dsp->fRec0[1]) + (fSlow20 * dsp->fRec0[2]))));
			dsp->fRec21[0] = (dsp->fRec22[0] - (fSlow15 * ((fSlow21 * dsp->fRec21[1]) + (fSlow22 * dsp->fRec21[2]))));
			float fTemp4 = (fSlow29 * dsp->fRec20[1]);
			dsp->fRec20[0] = ((fSlow15 * (((fSlow16 * dsp->fRec21[0]) + (fSlow23 * dsp->fRec21[1])) + (fSlow16 * dsp->fRec21[2]))) - (fSlow26 * ((fSlow27 * dsp->fRec20[2]) + fTemp4)));
			float fTemp5 = (fSlow35 * dsp->fRec19[1]);
			dsp->fRec19[0] = ((dsp->fRec20[2] + (fSlow26 * (fTemp4 + (fSlow27 * dsp->fRec20[0])))) - (fSlow32 * ((fSlow33 * dsp->fRec19[2]) + fTemp5)));
			float fTemp6 = (fSlow41 * dsp->fRec18[1]);
			dsp->fRec18[0] = ((dsp->fRec19[2] + (fSlow32 * (fTemp5 + (fSlow33 * dsp->fRec19[0])))) - (fSlow38 * ((fSlow39 * dsp->fRec18[2]) + fTemp6)));
			dsp->fRec28[0] = ((fSlow18 * dsp->fRec28[1]) + (fSlow19 * (dsp->fRec0[1] + dsp->fRec0[2])));
			dsp->fRec27[0] = (dsp->fRec28[0] - (fSlow15 * ((fSlow21 * dsp->fRec27[1]) + (fSlow22 * dsp->fRec27[2]))));
			float fTemp7 = (dsp->fRec27[2] + (dsp->fRec27[0] + (2.0f * dsp->fRec27[1])));
			float fTemp8 = (fSlow15 * fTemp7);
			dsp->fVec2[0] = fTemp8;
			dsp->fRec26[0] = ((fSlow47 * dsp->fRec26[1]) + (fSlow48 * ((fSlow49 * dsp->fVec2[1]) + (fSlow50 * fTemp7))));
			dsp->fRec25[0] = (dsp->fRec26[0] - (fSlow45 * ((fSlow29 * dsp->fRec25[1]) + (fSlow51 * dsp->fRec25[2]))));
			float fTemp9 = (fSlow35 * dsp->fRec24[1]);
			dsp->fRec24[0] = ((fSlow45 * (((fSlow28 * dsp->fRec25[0]) + (fSlow52 * dsp->fRec25[1])) + (fSlow28 * dsp->fRec25[2]))) - (fSlow32 * (fTemp9 + (fSlow33 * dsp->fRec24[2]))));
			float fTemp10 = (fSlow41 * dsp->fRec23[1]);
			dsp->fRec23[0] = ((dsp->fRec24[2] + (fSlow32 * (fTemp9 + (fSlow33 * dsp->fRec24[0])))) - (fSlow38 * (fTemp10 + (fSlow39 * dsp->fRec23[2]))));
			dsp->fRec33[0] = ((fSlow47 * dsp->fRec33[1]) + (fSlow48 * (fTemp8 + dsp->fVec2[1])));
			dsp->fRec32[0] = (dsp->fRec33[0] - (fSlow45 * ((fSlow29 * dsp->fRec32[1]) + (fSlow51 * dsp->fRec32[2]))));
			float fTemp11 = (dsp->fRec32[2] + (dsp->fRec32[0] + (2.0f * dsp->fRec32[1])));
			float fTemp12 = (fSlow45 * fTemp11);
			dsp->fVec3[0] = fTemp12;
			dsp->fRec31[0] = ((fSlow58 * dsp->fRec31[1]) + (fSlow59 * ((fSlow60 * dsp->fVec3[1]) + (fSlow61 * fTemp11))));
			dsp->fRec30[0] = (dsp->fRec31[0] - (fSlow56 * ((fSlow35 * dsp->fRec30[1]) + (fSlow62 * dsp->fRec30[2]))));
			float fTemp13 = (fSlow41 * dsp->fRec29[1]);
			dsp->fRec29[0] = ((fSlow56 * (((fSlow34 * dsp->fRec30[0]) + (fSlow63 * dsp->fRec30[1])) + (fSlow34 * dsp->fRec30[2]))) - (fSlow38 * (fTemp13 + (fSlow39 * dsp->fRec29[2]))));
			dsp->fRec37[0] = ((fSlow58 * dsp->fRec37[1]) + (fSlow59 * (fTemp12 + dsp->fVec3[1])));
			dsp->fRec36[0] = (dsp->fRec37[0] - (fSlow56 * ((fSlow35 * dsp->fRec36[1]) + (fSlow62 * dsp->fRec36[2]))));
			float fTemp14 = (dsp->fRec36[2] + (dsp->fRec36[0] + (2.0f * dsp->fRec36[1])));
			float fTemp15 = (fSlow56 * fTemp14);
			dsp->fVec4[0] = fTemp15;
			dsp->fRec35[0] = ((fSlow68 * dsp->fRec35[1]) + (fSlow69 * ((fSlow70 * dsp->fVec4[1]) + (fSlow71 * fTemp14))));
			dsp->fRec34[0] = (dsp->fRec35[0] - (fSlow64 * ((fSlow41 * dsp->fRec34[1]) + (fSlow72 * dsp->fRec34[2]))));
			dsp->fRec39[0] = ((fSlow68 * dsp->fRec39[1]) + (fSlow69 * (fTemp15 + dsp->fVec4[1])));
			dsp->fRec38[0] = (dsp->fRec39[0] - (fSlow64 * ((fSlow41 * dsp->fRec38[1]) + (fSlow72 * dsp->fRec38[2]))));
			float fTemp16 = ((((fSlow11 * (dsp->fRec18[2] + (fSlow38 * (fTemp6 + (fSlow39 * dsp->fRec18[0]))))) + (fSlow43 * (dsp->fRec23[2] + (fSlow38 * (fTemp10 + (fSlow39 * dsp->fRec23[0])))))) + (fSlow54 * (dsp->fRec29[2] + (fSlow38 * (fTemp13 + (fSlow39 * dsp->fRec29[0])))))) + (fSlow64 * ((fSlow66 * (((fSlow40 * dsp->fRec34[0]) + (fSlow73 * dsp->fRec34[1])) + (fSlow40 * dsp->fRec34[2]))) + (fSlow75 * (dsp->fRec38[2] + (dsp->fRec38[0] + (2.0f * dsp->fRec38[1])))))));
			dsp->fRec44[0] = ((fSlow18 * dsp->fRec44[1]) + (fSlow19 * ((fSlow13 * dsp->fRec8[1]) + (fSlow20 * dsp->fRec8[2]))));
			dsp->fRec43[0] = (dsp->fRec44[0] - (fSlow15 * ((fSlow21 * dsp->fRec43[1]) + (fSlow22 * dsp->fRec43[2]))));
			float fTemp17 = (fSlow29 * dsp->fRec42[1]);
			dsp->fRec42[0] = ((fSlow15 * (((fSlow16 * dsp->fRec43[0]) + (fSlow23 * dsp->fRec43[1])) + (fSlow16 * dsp->fRec43[2]))) - (fSlow26 * (fTemp17 + (fSlow27 * dsp->fRec42[2]))));
			float fTemp18 = (fSlow35 * dsp->fRec41[1]);
			dsp->fRec41[0] = ((dsp->fRec42[2] + (fSlow26 * (fTemp17 + (fSlow27 * dsp->fRec42[0])))) - (fSlow32 * (fTemp18 + (fSlow33 * dsp->fRec41[2]))));
			float fTemp19 = (fSlow41 * dsp->fRec40[1]);
			dsp->fRec40[0] = ((dsp->fRec41[2] + (fSlow32 * (fTemp18 + (fSlow33 * dsp->fRec41[0])))) - (fSlow38 * (fTemp19 + (fSlow39 * dsp->fRec40[2]))));
			dsp->fRec50[0] = ((fSlow18 * dsp->fRec50[1]) + (fSlow19 * (dsp->fRec8[1] + dsp->fRec8[2])));
			dsp->fRec49[0] = (dsp->fRec50[0] - (fSlow15 * ((fSlow21 * dsp->fRec49[1]) + (fSlow22 * dsp->fRec49[2]))));
			float fTemp20 = (dsp->fRec49[2] + (dsp->fRec49[0] + (2.0f * dsp->fRec49[1])));
			float fTemp21 = (fSlow15 * fTemp20);
			dsp->fVec5[0] = fTemp21;
			dsp->fRec48[0] = ((fSlow47 * dsp->fRec48[1]) + (fSlow48 * ((fSlow49 * dsp->fVec5[1]) + (fSlow50 * fTemp20))));
			dsp->fRec47[0] = (dsp->fRec48[0] - (fSlow45 * ((fSlow29 * dsp->fRec47[1]) + (fSlow51 * dsp->fRec47[2]))));
			float fTemp22 = (fSlow35 * dsp->fRec46[1]);
			dsp->fRec46[0] = ((fSlow45 * (((fSlow28 * dsp->fRec47[0]) + (fSlow52 * dsp->fRec47[1])) + (fSlow28 * dsp->fRec47[2]))) - (fSlow32 * (fTemp22 + (fSlow33 * dsp->fRec46[2]))));
			float fTemp23 = (fSlow41 * dsp->fRec45[1]);
			dsp->fRec45[0] = ((dsp->fRec46[2] + (fSlow32 * (fTemp22 + (fSlow33 * dsp->fRec46[0])))) - (fSlow38 * (fTemp23 + (fSlow39 * dsp->fRec45[2]))));
			dsp->fRec55[0] = ((fSlow47 * dsp->fRec55[1]) + (fSlow48 * (dsp->fVec5[1] + fTemp21)));
			dsp->fRec54[0] = (dsp->fRec55[0] - (fSlow45 * ((fSlow29 * dsp->fRec54[1]) + (fSlow51 * dsp->fRec54[2]))));
			float fTemp24 = (dsp->fRec54[2] + (dsp->fRec54[0] + (2.0f * dsp->fRec54[1])));
			float fTemp25 = (fSlow45 * fTemp24);
			dsp->fVec6[0] = fTemp25;
			dsp->fRec53[0] = ((fSlow58 * dsp->fRec53[1]) + (fSlow59 * ((fSlow60 * dsp->fVec6[1]) + (fSlow61 * fTemp24))));
			dsp->fRec52[0] = (dsp->fRec53[0] - (fSlow56 * ((fSlow35 * dsp->fRec52[1]) + (fSlow62 * dsp->fRec52[2]))));
			float fTemp26 = (fSlow41 * dsp->fRec51[1]);
			dsp->fRec51[0] = ((fSlow56 * (((fSlow34 * dsp->fRec52[0]) + (fSlow63 * dsp->fRec52[1])) + (fSlow34 * dsp->fRec52[2]))) - (fSlow38 * (fTemp26 + (fSlow39 * dsp->fRec51[2]))));
			dsp->fRec59[0] = ((fSlow58 * dsp->fRec59[1]) + (fSlow59 * (dsp->fVec6[1] + fTemp25)));
			dsp->fRec58[0] = (dsp->fRec59[0] - (fSlow56 * ((fSlow35 * dsp->fRec58[1]) + (fSlow62 * dsp->fRec58[2]))));
			float fTemp27 = (dsp->fRec58[2] + (dsp->fRec58[0] + (2.0f * dsp->fRec58[1])));
			float fTemp28 = (fSlow56 * fTemp27);
			dsp->fVec7[0] = fTemp28;
			dsp->fRec57[0] = ((fSlow68 * dsp->fRec57[1]) + (fSlow69 * ((fSlow70 * dsp->fVec7[1]) + (fSlow71 * fTemp27))));
			dsp->fRec56[0] = (dsp->fRec57[0] - (fSlow64 * ((fSlow41 * dsp->fRec56[1]) + (fSlow72 * dsp->fRec56[2]))));
			dsp->fRec61[0] = ((fSlow68 * dsp->fRec61[1]) + (fSlow69 * (dsp->fVec7[1] + fTemp28)));
			dsp->fRec60[0] = (dsp->fRec61[0] - (fSlow64 * ((fSlow41 * dsp->fRec60[1]) + (fSlow72 * dsp->fRec60[2]))));
			float fTemp29 = ((((fSlow78 * (dsp->fRec40[2] + (fSlow38 * (fTemp19 + (fSlow39 * dsp->fRec40[0]))))) + (fSlow79 * (dsp->fRec45[2] + (fSlow38 * (fTemp23 + (fSlow39 * dsp->fRec45[0])))))) + (fSlow80 * (dsp->fRec51[2] + (fSlow38 * (fTemp26 + (fSlow39 * dsp->fRec51[0])))))) + (fSlow64 * ((fSlow81 * (((fSlow40 * dsp->fRec56[0]) + (fSlow73 * dsp->fRec56[1])) + (fSlow40 * dsp->fRec56[2]))) + (fSlow82 * (dsp->fRec60[2] + (dsp->fRec60[0] + (2.0f * dsp->fRec60[1])))))));
			float fTemp30 = (fTemp16 + fTemp29);
			dsp->fRec66[0] = ((fSlow18 * dsp->fRec66[1]) + (fSlow19 * ((fSlow13 * dsp->fRec4[1]) + (fSlow20 * dsp->fRec4[2]))));
			dsp->fRec65[0] = (dsp->fRec66[0] - (fSlow15 * ((fSlow21 * dsp->fRec65[1]) + (fSlow22 * dsp->fRec65[2]))));
			float fTemp31 = (fSlow29 * dsp->fRec64[1]);
			dsp->fRec64[0] = ((fSlow15 * (((fSlow16 * dsp->fRec65[0]) + (fSlow23 * dsp->fRec65[1])) + (fSlow16 * dsp->fRec65[2]))) - (fSlow26 * (fTemp31 + (fSlow27 * dsp->fRec64[2]))));
			float fTemp32 = (fSlow35 * dsp->fRec63[1]);
			dsp->fRec63[0] = ((dsp->fRec64[2] + (fSlow26 * (fTemp31 + (fSlow27 * dsp->fRec64[0])))) - (fSlow32 * (fTemp32 + (fSlow33 * dsp->fRec63[2]))));
			float fTemp33 = (fSlow41 * dsp->fRec62[1]);
			dsp->fRec62[0] = ((dsp->fRec63[2] + (fSlow32 * (fTemp32 + (fSlow33 * dsp->fRec63[0])))) - (fSlow38 * (fTemp33 + (fSlow39 * dsp->fRec62[2]))));
			dsp->fRec72[0] = ((fSlow18 * dsp->fRec72[1]) + (fSlow19 * (dsp->fRec4[1] + dsp->fRec4[2])));
			dsp->fRec71[0] = (dsp->fRec72[0] - (fSlow15 * ((fSlow21 * dsp->fRec71[1]) + (fSlow22 * dsp->fRec71[2]))));
			float fTemp34 = (dsp->fRec71[2] + (dsp->fRec71[0] + (2.0f * dsp->fRec71[1])));
			float fTemp35 = (fSlow15 * fTemp34);
			dsp->fVec8[0] = fTemp35;
			dsp->fRec70[0] = ((fSlow47 * dsp->fRec70[1]) + (fSlow48 * ((fSlow49 * dsp->fVec8[1]) + (fSlow50 * fTemp34))));
			dsp->fRec69[0] = (dsp->fRec70[0] - (fSlow45 * ((fSlow29 * dsp->fRec69[1]) + (fSlow51 * dsp->fRec69[2]))));
			float fTemp36 = (fSlow35 * dsp->fRec68[1]);
			dsp->fRec68[0] = ((fSlow45 * (((fSlow28 * dsp->fRec69[0]) + (fSlow52 * dsp->fRec69[1])) + (fSlow28 * dsp->fRec69[2]))) - (fSlow32 * (fTemp36 + (fSlow33 * dsp->fRec68[2]))));
			float fTemp37 = (fSlow41 * dsp->fRec67[1]);
			dsp->fRec67[0] = ((dsp->fRec68[2] + (fSlow32 * (fTemp36 + (fSlow33 * dsp->fRec68[0])))) - (fSlow38 * (fTemp37 + (fSlow39 * dsp->fRec67[2]))));
			dsp->fRec77[0] = ((fSlow47 * dsp->fRec77[1]) + (fSlow48 * (dsp->fVec8[1] + fTemp35)));
			dsp->fRec76[0] = (dsp->fRec77[0] - (fSlow45 * ((fSlow29 * dsp->fRec76[1]) + (fSlow51 * dsp->fRec76[2]))));
			float fTemp38 = (dsp->fRec76[2] + (dsp->fRec76[0] + (2.0f * dsp->fRec76[1])));
			float fTemp39 = (fSlow45 * fTemp38);
			dsp->fVec9[0] = fTemp39;
			dsp->fRec75[0] = ((fSlow58 * dsp->fRec75[1]) + (fSlow59 * ((fSlow60 * dsp->fVec9[1]) + (fSlow61 * fTemp38))));
			dsp->fRec74[0] = (dsp->fRec75[0] - (fSlow56 * ((fSlow35 * dsp->fRec74[1]) + (fSlow62 * dsp->fRec74[2]))));
			float fTemp40 = (fSlow41 * dsp->fRec73[1]);
			dsp->fRec73[0] = ((fSlow56 * (((fSlow34 * dsp->fRec74[0]) + (fSlow63 * dsp->fRec74[1])) + (fSlow34 * dsp->fRec74[2]))) - (fSlow38 * (fTemp40 + (fSlow39 * dsp->fRec73[2]))));
			dsp->fRec81[0] = ((fSlow58 * dsp->fRec81[1]) + (fSlow59 * (dsp->fVec9[1] + fTemp39)));
			dsp->fRec80[0] = (dsp->fRec81[0] - (fSlow56 * ((fSlow35 * dsp->fRec80[1]) + (fSlow62 * dsp->fRec80[2]))));
			float fTemp41 = (dsp->fRec80[2] + (dsp->fRec80[0] + (2.0f * dsp->fRec80[1])));
			float fTemp42 = (fSlow56 * fTemp41);
			dsp->fVec10[0] = fTemp42;
			dsp->fRec79[0] = ((fSlow68 * dsp->fRec79[1]) + (fSlow69 * ((fSlow70 * dsp->fVec10[1]) + (fSlow71 * fTemp41))));
			dsp->fRec78[0] = (dsp->fRec79[0] - (fSlow64 * ((fSlow41 * dsp->fRec78[1]) + (fSlow72 * dsp->fRec78[2]))));
			dsp->fRec83[0] = ((fSlow68 * dsp->fRec83[1]) + (fSlow69 * (dsp->fVec10[1] + fTemp42)));
			dsp->fRec82[0] = (dsp->fRec83[0] - (fSlow64 * ((fSlow41 * dsp->fRec82[1]) + (fSlow72 * dsp->fRec82[2]))));
			float fTemp43 = ((((fSlow85 * (dsp->fRec62[2] + (fSlow38 * (fTemp33 + (fSlow39 * dsp->fRec62[0]))))) + (fSlow86 * (dsp->fRec67[2] + (fSlow38 * (fTemp37 + (fSlow39 * dsp->fRec67[0])))))) + (fSlow87 * (dsp->fRec73[2] + (fSlow38 * (fTemp40 + (fSlow39 * dsp->fRec73[0])))))) + (fSlow64 * ((fSlow88 * (((fSlow40 * dsp->fRec78[0]) + (fSlow73 * dsp->fRec78[1])) + (fSlow40 * dsp->fRec78[2]))) + (fSlow89 * (dsp->fRec82[2] + (dsp->fRec82[0] + (2.0f * dsp->fRec82[1])))))));
			dsp->fRec88[0] = ((fSlow18 * dsp->fRec88[1]) + (fSlow19 * ((fSlow13 * dsp->fRec12[1]) + (fSlow20 * dsp->fRec12[2]))));
			dsp->fRec87[0] = (dsp->fRec88[0] - (fSlow15 * ((fSlow21 * dsp->fRec87[1]) + (fSlow22 * dsp->fRec87[2]))));
			float fTemp44 = (fSlow29 * dsp->fRec86[1]);
			dsp->fRec86[0] = ((fSlow15 * (((fSlow16 * dsp->fRec87[0]) + (fSlow23 * dsp->fRec87[1])) + (fSlow16 * dsp->fRec87[2]))) - (fSlow26 * (fTemp44 + (fSlow27 * dsp->fRec86[2]))));
			float fTemp45 = (fSlow35 * dsp->fRec85[1]);
			dsp->fRec85[0] = ((dsp->fRec86[2] + (fSlow26 * (fTemp44 + (fSlow27 * dsp->fRec86[0])))) - (fSlow32 * (fTemp45 + (fSlow33 * dsp->fRec85[2]))));
			float fTemp46 = (fSlow41 * dsp->fRec84[1]);
			dsp->fRec84[0] = ((dsp->fRec85[2] + (fSlow32 * (fTemp45 + (fSlow33 * dsp->fRec85[0])))) - (fSlow38 * (fTemp46 + (fSlow39 * dsp->fRec84[2]))));
			dsp->fRec94[0] = ((fSlow18 * dsp->fRec94[1]) + (fSlow19 * (dsp->fRec12[1] + dsp->fRec12[2])));
			dsp->fRec93[0] = (dsp->fRec94[0] - (fSlow15 * ((fSlow21 * dsp->fRec93[1]) + (fSlow22 * dsp->fRec93[2]))));
			float fTemp47 = (dsp->fRec93[2] + (dsp->fRec93[0] + (2.0f * dsp->fRec93[1])));
			float fTemp48 = (fSlow15 * fTemp47);
			dsp->fVec11[0] = fTemp48;
			dsp->fRec92[0] = ((fSlow47 * dsp->fRec92[1]) + (fSlow48 * ((fSlow49 * dsp->fVec11[1]) + (fSlow50 * fTemp47))));
			dsp->fRec91[0] = (dsp->fRec92[0] - (fSlow45 * ((fSlow29 * dsp->fRec91[1]) + (fSlow51 * dsp->fRec91[2]))));
			float fTemp49 = (fSlow35 * dsp->fRec90[1]);
			dsp->fRec90[0] = ((fSlow45 * (((fSlow28 * dsp->fRec91[0]) + (fSlow52 * dsp->fRec91[1])) + (fSlow28 * dsp->fRec91[2]))) - (fSlow32 * (fTemp49 + (fSlow33 * dsp->fRec90[2]))));
			float fTemp50 = (fSlow41 * dsp->fRec89[1]);
			dsp->fRec89[0] = ((dsp->fRec90[2] + (fSlow32 * (fTemp49 + (fSlow33 * dsp->fRec90[0])))) - (fSlow38 * (fTemp50 + (fSlow39 * dsp->fRec89[2]))));
			dsp->fRec99[0] = ((fSlow47 * dsp->fRec99[1]) + (fSlow48 * (dsp->fVec11[1] + fTemp48)));
			dsp->fRec98[0] = (dsp->fRec99[0] - (fSlow45 * ((fSlow29 * dsp->fRec98[1]) + (fSlow51 * dsp->fRec98[2]))));
			float fTemp51 = (dsp->fRec98[2] + (dsp->fRec98[0] + (2.0f * dsp->fRec98[1])));
			float fTemp52 = (fSlow45 * fTemp51);
			dsp->fVec12[0] = fTemp52;
			dsp->fRec97[0] = ((fSlow58 * dsp->fRec97[1]) + (fSlow59 * ((fSlow60 * dsp->fVec12[1]) + (fSlow61 * fTemp51))));
			dsp->fRec96[0] = (dsp->fRec97[0] - (fSlow56 * ((fSlow35 * dsp->fRec96[1]) + (fSlow62 * dsp->fRec96[2]))));
			float fTemp53 = (fSlow41 * dsp->fRec95[1]);
			dsp->fRec95[0] = ((fSlow56 * (((fSlow34 * dsp->fRec96[0]) + (fSlow63 * dsp->fRec96[1])) + (fSlow34 * dsp->fRec96[2]))) - (fSlow38 * (fTemp53 + (fSlow39 * dsp->fRec95[2]))));
			dsp->fRec103[0] = ((fSlow58 * dsp->fRec103[1]) + (fSlow59 * (dsp->fVec12[1] + fTemp52)));
			dsp->fRec102[0] = (dsp->fRec103[0] - (fSlow56 * ((fSlow35 * dsp->fRec102[1]) + (fSlow62 * dsp->fRec102[2]))));
			float fTemp54 = (dsp->fRec102[2] + (dsp->fRec102[0] + (2.0f * dsp->fRec102[1])));
			float fTemp55 = (fSlow56 * fTemp54);
			dsp->fVec13[0] = fTemp55;
			dsp->fRec101[0] = ((fSlow68 * dsp->fRec101[1]) + (fSlow69 * ((fSlow70 * dsp->fVec13[1]) + (fSlow71 * fTemp54))));
			dsp->fRec100[0] = (dsp->fRec101[0] - (fSlow64 * ((fSlow41 * dsp->fRec100[1]) + (fSlow72 * dsp->fRec100[2]))));
			dsp->fRec105[0] = ((fSlow68 * dsp->fRec105[1]) + (fSlow69 * (dsp->fVec13[1] + fTemp55)));
			dsp->fRec104[0] = (dsp->fRec105[0] - (fSlow64 * ((fSlow41 * dsp->fRec104[1]) + (fSlow72 * dsp->fRec104[2]))));
			float fTemp56 = ((((fSlow92 * (dsp->fRec84[2] + (fSlow38 * (fTemp46 + (fSlow39 * dsp->fRec84[0]))))) + (fSlow93 * (dsp->fRec89[2] + (fSlow38 * (fTemp50 + (fSlow39 * dsp->fRec89[0])))))) + (fSlow94 * (dsp->fRec95[2] + (fSlow38 * (fTemp53 + (fSlow39 * dsp->fRec95[0])))))) + (fSlow64 * ((fSlow95 * (((fSlow40 * dsp->fRec100[0]) + (fSlow73 * dsp->fRec100[1])) + (fSlow40 * dsp->fRec100[2]))) + (fSlow96 * (dsp->fRec104[2] + (dsp->fRec104[0] + (2.0f * dsp->fRec104[1])))))));
			float fTemp57 = (fTemp43 + fTemp56);
			float fTemp58 = (fTemp30 + fTemp57);
			dsp->fRec110[0] = ((fSlow18 * dsp->fRec110[1]) + (fSlow19 * ((fSlow13 * dsp->fRec2[1]) + (fSlow20 * dsp->fRec2[2]))));
			dsp->fRec109[0] = (dsp->fRec110[0] - (fSlow15 * ((fSlow21 * dsp->fRec109[1]) + (fSlow22 * dsp->fRec109[2]))));
			float fTemp59 = (fSlow29 * dsp->fRec108[1]);
			dsp->fRec108[0] = ((fSlow15 * (((fSlow16 * dsp->fRec109[0]) + (fSlow23 * dsp->fRec109[1])) + (fSlow16 * dsp->fRec109[2]))) - (fSlow26 * (fTemp59 + (fSlow27 * dsp->fRec108[2]))));
			float fTemp60 = (fSlow35 * dsp->fRec107[1]);
			dsp->fRec107[0] = ((dsp->fRec108[2] + (fSlow26 * (fTemp59 + (fSlow27 * dsp->fRec108[0])))) - (fSlow32 * (fTemp60 + (fSlow33 * dsp->fRec107[2]))));
			float fTemp61 = (fSlow41 * dsp->fRec106[1]);
			dsp->fRec106[0] = ((dsp->fRec107[2] + (fSlow32 * (fTemp60 + (fSlow33 * dsp->fRec107[0])))) - (fSlow38 * (fTemp61 + (fSlow39 * dsp->fRec106[2]))));
			dsp->fRec116[0] = ((fSlow18 * dsp->fRec116[1]) + (fSlow19 * (dsp->fRec2[1] + dsp->fRec2[2])));
			dsp->fRec115[0] = (dsp->fRec116[0] - (fSlow15 * ((fSlow21 * dsp->fRec115[1]) + (fSlow22 * dsp->fRec115[2]))));
			float fTemp62 = (dsp->fRec115[2] + (dsp->fRec115[0] + (2.0f * dsp->fRec115[1])));
			float fTemp63 = (fSlow15 * fTemp62);
			dsp->fVec14[0] = fTemp63;
			dsp->fRec114[0] = ((fSlow47 * dsp->fRec114[1]) + (fSlow48 * ((fSlow49 * dsp->fVec14[1]) + (fSlow50 * fTemp62))));
			dsp->fRec113[0] = (dsp->fRec114[0] - (fSlow45 * ((fSlow29 * dsp->fRec113[1]) + (fSlow51 * dsp->fRec113[2]))));
			float fTemp64 = (fSlow35 * dsp->fRec112[1]);
			dsp->fRec112[0] = ((fSlow45 * (((fSlow28 * dsp->fRec113[0]) + (fSlow52 * dsp->fRec113[1])) + (fSlow28 * dsp->fRec113[2]))) - (fSlow32 * (fTemp64 + (fSlow33 * dsp->fRec112[2]))));
			float fTemp65 = (fSlow41 * dsp->fRec111[1]);
			dsp->fRec111[0] = ((dsp->fRec112[2] + (fSlow32 * (fTemp64 + (fSlow33 * dsp->fRec112[0])))) - (fSlow38 * (fTemp65 + (fSlow39 * dsp->fRec111[2]))));
			dsp->fRec121[0] = ((fSlow47 * dsp->fRec121[1]) + (fSlow48 * (dsp->fVec14[1] + fTemp63)));
			dsp->fRec120[0] = (dsp->fRec121[0] - (fSlow45 * ((fSlow29 * dsp->fRec120[1]) + (fSlow51 * dsp->fRec120[2]))));
			float fTemp66 = (dsp->fRec120[2] + (dsp->fRec120[0] + (2.0f * dsp->fRec120[1])));
			float fTemp67 = (fSlow45 * fTemp66);
			dsp->fVec15[0] = fTemp67;
			dsp->fRec119[0] = ((fSlow58 * dsp->fRec119[1]) + (fSlow59 * ((fSlow60 * dsp->fVec15[1]) + (fSlow61 * fTemp66))));
			dsp->fRec118[0] = (dsp->fRec119[0] - (fSlow56 * ((fSlow35 * dsp->fRec118[1]) + (fSlow62 * dsp->fRec118[2]))));
			float fTemp68 = (fSlow41 * dsp->fRec117[1]);
			dsp->fRec117[0] = ((fSlow56 * (((fSlow34 * dsp->fRec118[0]) + (fSlow63 * dsp->fRec118[1])) + (fSlow34 * dsp->fRec118[2]))) - (fSlow38 * (fTemp68 + (fSlow39 * dsp->fRec117[2]))));
			dsp->fRec125[0] = ((fSlow58 * dsp->fRec125[1]) + (fSlow59 * (dsp->fVec15[1] + fTemp67)));
			dsp->fRec124[0] = (dsp->fRec125[0] - (fSlow56 * ((fSlow35 * dsp->fRec124[1]) + (fSlow62 * dsp->fRec124[2]))));
			float fTemp69 = (dsp->fRec124[2] + (dsp->fRec124[0] + (2.0f * dsp->fRec124[1])));
			float fTemp70 = (fSlow56 * fTemp69);
			dsp->fVec16[0] = fTemp70;
			dsp->fRec123[0] = ((fSlow68 * dsp->fRec123[1]) + (fSlow69 * ((fSlow70 * dsp->fVec16[1]) + (fSlow71 * fTemp69))));
			dsp->fRec122[0] = (dsp->fRec123[0] - (fSlow64 * ((fSlow41 * dsp->fRec122[1]) + (fSlow72 * dsp->fRec122[2]))));
			dsp->fRec127[0] = ((fSlow68 * dsp->fRec127[1]) + (fSlow69 * (dsp->fVec16[1] + fTemp70)));
			dsp->fRec126[0] = (dsp->fRec127[0] - (fSlow64 * ((fSlow41 * dsp->fRec126[1]) + (fSlow72 * dsp->fRec126[2]))));
			float fTemp71 = ((((fSlow99 * (dsp->fRec106[2] + (fSlow38 * (fTemp61 + (fSlow39 * dsp->fRec106[0]))))) + (fSlow100 * (dsp->fRec111[2] + (fSlow38 * (fTemp65 + (fSlow39 * dsp->fRec111[0])))))) + (fSlow101 * (dsp->fRec117[2] + (fSlow38 * (fTemp68 + (fSlow39 * dsp->fRec117[0])))))) + (fSlow64 * ((fSlow102 * (((fSlow40 * dsp->fRec122[0]) + (fSlow73 * dsp->fRec122[1])) + (fSlow40 * dsp->fRec122[2]))) + (fSlow103 * (dsp->fRec126[2] + (dsp->fRec126[0] + (2.0f * dsp->fRec126[1])))))));
			dsp->fRec132[0] = ((fSlow18 * dsp->fRec132[1]) + (fSlow19 * ((fSlow13 * dsp->fRec10[1]) + (fSlow20 * dsp->fRec10[2]))));
			dsp->fRec131[0] = (dsp->fRec132[0] - (fSlow15 * ((fSlow21 * dsp->fRec131[1]) + (fSlow22 * dsp->fRec131[2]))));
			float fTemp72 = (fSlow29 * dsp->fRec130[1]);
			dsp->fRec130[0] = ((fSlow15 * (((fSlow16 * dsp->fRec131[0]) + (fSlow23 * dsp->fRec131[1])) + (fSlow16 * dsp->fRec131[2]))) - (fSlow26 * (fTemp72 + (fSlow27 * dsp->fRec130[2]))));
			float fTemp73 = (fSlow35 * dsp->fRec129[1]);
			dsp->fRec129[0] = ((dsp->fRec130[2] + (fSlow26 * (fTemp72 + (fSlow27 * dsp->fRec130[0])))) - (fSlow32 * (fTemp73 + (fSlow33 * dsp->fRec129[2]))));
			float fTemp74 = (fSlow41 * dsp->fRec128[1]);
			dsp->fRec128[0] = ((dsp->fRec129[2] + (fSlow32 * (fTemp73 + (fSlow33 * dsp->fRec129[0])))) - (fSlow38 * (fTemp74 + (fSlow39 * dsp->fRec128[2]))));
			dsp->fRec138[0] = ((fSlow18 * dsp->fRec138[1]) + (fSlow19 * (dsp->fRec10[1] + dsp->fRec10[2])));
			dsp->fRec137[0] = (dsp->fRec138[0] - (fSlow15 * ((fSlow21 * dsp->fRec137[1]) + (fSlow22 * dsp->fRec137[2]))));
			float fTemp75 = (dsp->fRec137[2] + (dsp->fRec137[0] + (2.0f * dsp->fRec137[1])));
			float fTemp76 = (fSlow15 * fTemp75);
			dsp->fVec17[0] = fTemp76;
			dsp->fRec136[0] = ((fSlow47 * dsp->fRec136[1]) + (fSlow48 * ((fSlow49 * dsp->fVec17[1]) + (fSlow50 * fTemp75))));
			dsp->fRec135[0] = (dsp->fRec136[0] - (fSlow45 * ((fSlow29 * dsp->fRec135[1]) + (fSlow51 * dsp->fRec135[2]))));
			float fTemp77 = (fSlow35 * dsp->fRec134[1]);
			dsp->fRec134[0] = ((fSlow45 * (((fSlow28 * dsp->fRec135[0]) + (fSlow52 * dsp->fRec135[1])) + (fSlow28 * dsp->fRec135[2]))) - (fSlow32 * (fTemp77 + (fSlow33 * dsp->fRec134[2]))));
			float fTemp78 = (fSlow41 * dsp->fRec133[1]);
			dsp->fRec133[0] = ((dsp->fRec134[2] + (fSlow32 * (fTemp77 + (fSlow33 * dsp->fRec134[0])))) - (fSlow38 * (fTemp78 + (fSlow39 * dsp->fRec133[2]))));
			dsp->fRec143[0] = ((fSlow47 * dsp->fRec143[1]) + (fSlow48 * (dsp->fVec17[1] + fTemp76)));
			dsp->fRec142[0] = (dsp->fRec143[0] - (fSlow45 * ((fSlow29 * dsp->fRec142[1]) + (fSlow51 * dsp->fRec142[2]))));
			float fTemp79 = (dsp->fRec142[2] + (dsp->fRec142[0] + (2.0f * dsp->fRec142[1])));
			float fTemp80 = (fSlow45 * fTemp79);
			dsp->fVec18[0] = fTemp80;
			dsp->fRec141[0] = ((fSlow58 * dsp->fRec141[1]) + (fSlow59 * ((fSlow60 * dsp->fVec18[1]) + (fSlow61 * fTemp79))));
			dsp->fRec140[0] = (dsp->fRec141[0] - (fSlow56 * ((fSlow35 * dsp->fRec140[1]) + (fSlow62 * dsp->fRec140[2]))));
			float fTemp81 = (fSlow41 * dsp->fRec139[1]);
			dsp->fRec139[0] = ((fSlow56 * (((fSlow34 * dsp->fRec140[0]) + (fSlow63 * dsp->fRec140[1])) + (fSlow34 * dsp->fRec140[2]))) - (fSlow38 * (fTemp81 + (fSlow39 * dsp->fRec139[2]))));
			dsp->fRec147[0] = ((fSlow58 * dsp->fRec147[1]) + (fSlow59 * (dsp->fVec18[1] + fTemp80)));
			dsp->fRec146[0] = (dsp->fRec147[0] - (fSlow56 * ((fSlow35 * dsp->fRec146[1]) + (fSlow62 * dsp->fRec146[2]))));
			float fTemp82 = (dsp->fRec146[2] + (dsp->fRec146[0] + (2.0f * dsp->fRec146[1])));
			float fTemp83 = (fSlow56 * fTemp82);
			dsp->fVec19[0] = fTemp83;
			dsp->fRec145[0] = ((fSlow68 * dsp->fRec145[1]) + (fSlow69 * ((fSlow70 * dsp->fVec19[1]) + (fSlow71 * fTemp82))));
			dsp->fRec144[0] = (dsp->fRec145[0] - (fSlow64 * ((fSlow41 * dsp->fRec144[1]) + (fSlow72 * dsp->fRec144[2]))));
			dsp->fRec149[0] = ((fSlow68 * dsp->fRec149[1]) + (fSlow69 * (dsp->fVec19[1] + fTemp83)));
			dsp->fRec148[0] = (dsp->fRec149[0] - (fSlow64 * ((fSlow41 * dsp->fRec148[1]) + (fSlow72 * dsp->fRec148[2]))));
			float fTemp84 = ((((fSlow106 * (dsp->fRec128[2] + (fSlow38 * (fTemp74 + (fSlow39 * dsp->fRec128[0]))))) + (fSlow107 * (dsp->fRec133[2] + (fSlow38 * (fTemp78 + (fSlow39 * dsp->fRec133[0])))))) + (fSlow108 * (dsp->fRec139[2] + (fSlow38 * (fTemp81 + (fSlow39 * dsp->fRec139[0])))))) + (fSlow64 * ((fSlow109 * (((fSlow40 * dsp->fRec144[0]) + (fSlow73 * dsp->fRec144[1])) + (fSlow40 * dsp->fRec144[2]))) + (fSlow110 * (dsp->fRec148[2] + (dsp->fRec148[0] + (2.0f * dsp->fRec148[1])))))));
			float fTemp85 = (fTemp71 + fTemp84);
			dsp->fRec154[0] = ((fSlow18 * dsp->fRec154[1]) + (fSlow19 * ((fSlow13 * dsp->fRec6[1]) + (fSlow20 * dsp->fRec6[2]))));
			dsp->fRec153[0] = (dsp->fRec154[0] - (fSlow15 * ((fSlow21 * dsp->fRec153[1]) + (fSlow22 * dsp->fRec153[2]))));
			float fTemp86 = (fSlow29 * dsp->fRec152[1]);
			dsp->fRec152[0] = ((fSlow15 * (((fSlow16 * dsp->fRec153[0]) + (fSlow23 * dsp->fRec153[1])) + (fSlow16 * dsp->fRec153[2]))) - (fSlow26 * (fTemp86 + (fSlow27 * dsp->fRec152[2]))));
			float fTemp87 = (fSlow35 * dsp->fRec151[1]);
			dsp->fRec151[0] = ((dsp->fRec152[2] + (fSlow26 * (fTemp86 + (fSlow27 * dsp->fRec152[0])))) - (fSlow32 * (fTemp87 + (fSlow33 * dsp->fRec151[2]))));
			float fTemp88 = (fSlow41 * dsp->fRec150[1]);
			dsp->fRec150[0] = ((dsp->fRec151[2] + (fSlow32 * (fTemp87 + (fSlow33 * dsp->fRec151[0])))) - (fSlow38 * (fTemp88 + (fSlow39 * dsp->fRec150[2]))));
			dsp->fRec160[0] = ((fSlow18 * dsp->fRec160[1]) + (fSlow19 * (dsp->fRec6[1] + dsp->fRec6[2])));
			dsp->fRec159[0] = (dsp->fRec160[0] - (fSlow15 * ((fSlow21 * dsp->fRec159[1]) + (fSlow22 * dsp->fRec159[2]))));
			float fTemp89 = (dsp->fRec159[2] + (dsp->fRec159[0] + (2.0f * dsp->fRec159[1])));
			float fTemp90 = (fSlow15 * fTemp89);
			dsp->fVec20[0] = fTemp90;
			dsp->fRec158[0] = ((fSlow47 * dsp->fRec158[1]) + (fSlow48 * ((fSlow49 * dsp->fVec20[1]) + (fSlow50 * fTemp89))));
			dsp->fRec157[0] = (dsp->fRec158[0] - (fSlow45 * ((fSlow29 * dsp->fRec157[1]) + (fSlow51 * dsp->fRec157[2]))));
			float fTemp91 = (fSlow35 * dsp->fRec156[1]);
			dsp->fRec156[0] = ((fSlow45 * (((fSlow28 * dsp->fRec157[0]) + (fSlow52 * dsp->fRec157[1])) + (fSlow28 * dsp->fRec157[2]))) - (fSlow32 * (fTemp91 + (fSlow33 * dsp->fRec156[2]))));
			float fTemp92 = (fSlow41 * dsp->fRec155[1]);
			dsp->fRec155[0] = ((dsp->fRec156[2] + (fSlow32 * (fTemp91 + (fSlow33 * dsp->fRec156[0])))) - (fSlow38 * (fTemp92 + (fSlow39 * dsp->fRec155[2]))));
			dsp->fRec165[0] = ((fSlow47 * dsp->fRec165[1]) + (fSlow48 * (dsp->fVec20[1] + fTemp90)));
			dsp->fRec164[0] = (dsp->fRec165[0] - (fSlow45 * ((fSlow29 * dsp->fRec164[1]) + (fSlow51 * dsp->fRec164[2]))));
			float fTemp93 = (dsp->fRec164[2] + (dsp->fRec164[0] + (2.0f * dsp->fRec164[1])));
			float fTemp94 = (fSlow45 * fTemp93);
			dsp->fVec21[0] = fTemp94;
			dsp->fRec163[0] = ((fSlow58 * dsp->fRec163[1]) + (fSlow59 * ((fSlow60 * dsp->fVec21[1]) + (fSlow61 * fTemp93))));
			dsp->fRec162[0] = (dsp->fRec163[0] - (fSlow56 * ((fSlow35 * dsp->fRec162[1]) + (fSlow62 * dsp->fRec162[2]))));
			float fTemp95 = (fSlow41 * dsp->fRec161[1]);
			dsp->fRec161[0] = ((fSlow56 * (((fSlow34 * dsp->fRec162[0]) + (fSlow63 * dsp->fRec162[1])) + (fSlow34 * dsp->fRec162[2]))) - (fSlow38 * (fTemp95 + (fSlow39 * dsp->fRec161[2]))));
			dsp->fRec169[0] = ((fSlow58 * dsp->fRec169[1]) + (fSlow59 * (dsp->fVec21[1] + fTemp94)));
			dsp->fRec168[0] = (dsp->fRec169[0] - (fSlow56 * ((fSlow35 * dsp->fRec168[1]) + (fSlow62 * dsp->fRec168[2]))));
			float fTemp96 = (dsp->fRec168[2] + (dsp->fRec168[0] + (2.0f * dsp->fRec168[1])));
			float fTemp97 = (fSlow56 * fTemp96);
			dsp->fVec22[0] = fTemp97;
			dsp->fRec167[0] = ((fSlow68 * dsp->fRec167[1]) + (fSlow69 * ((fSlow70 * dsp->fVec22[1]) + (fSlow71 * fTemp96))));
			dsp->fRec166[0] = (dsp->fRec167[0] - (fSlow64 * ((fSlow41 * dsp->fRec166[1]) + (fSlow72 * dsp->fRec166[2]))));
			dsp->fRec171[0] = ((fSlow68 * dsp->fRec171[1]) + (fSlow69 * (dsp->fVec22[1] + fTemp97)));
			dsp->fRec170[0] = (dsp->fRec171[0] - (fSlow64 * ((fSlow41 * dsp->fRec170[1]) + (fSlow72 * dsp->fRec170[2]))));
			float fTemp98 = ((((fSlow113 * (dsp->fRec150[2] + (fSlow38 * (fTemp88 + (fSlow39 * dsp->fRec150[0]))))) + (fSlow114 * (dsp->fRec155[2] + (fSlow38 * (fTemp92 + (fSlow39 * dsp->fRec155[0])))))) + (fSlow115 * (dsp->fRec161[2] + (fSlow38 * (fTemp95 + (fSlow39 * dsp->fRec161[0])))))) + (fSlow64 * ((fSlow116 * (((fSlow40 * dsp->fRec166[0]) + (fSlow73 * dsp->fRec166[1])) + (fSlow40 * dsp->fRec166[2]))) + (fSlow117 * (dsp->fRec170[2] + (dsp->fRec170[0] + (2.0f * dsp->fRec170[1])))))));
			dsp->fRec176[0] = ((fSlow18 * dsp->fRec176[1]) + (fSlow19 * ((fSlow13 * dsp->fRec14[1]) + (fSlow20 * dsp->fRec14[2]))));
			dsp->fRec175[0] = (dsp->fRec176[0] - (fSlow15 * ((fSlow21 * dsp->fRec175[1]) + (fSlow22 * dsp->fRec175[2]))));
			float fTemp99 = (fSlow29 * dsp->fRec174[1]);
			dsp->fRec174[0] = ((fSlow15 * (((fSlow16 * dsp->fRec175[0]) + (fSlow23 * dsp->fRec175[1])) + (fSlow16 * dsp->fRec175[2]))) - (fSlow26 * (fTemp99 + (fSlow27 * dsp->fRec174[2]))));
			float fTemp100 = (fSlow35 * dsp->fRec173[1]);
			dsp->fRec173[0] = ((dsp->fRec174[2] + (fSlow26 * (fTemp99 + (fSlow27 * dsp->fRec174[0])))) - (fSlow32 * (fTemp100 + (fSlow33 * dsp->fRec173[2]))));
			float fTemp101 = (fSlow41 * dsp->fRec172[1]);
			dsp->fRec172[0] = ((dsp->fRec173[2] + (fSlow32 * (fTemp100 + (fSlow33 * dsp->fRec173[0])))) - (fSlow38 * (fTemp101 + (fSlow39 * dsp->fRec172[2]))));
			dsp->fRec182[0] = ((fSlow18 * dsp->fRec182[1]) + (fSlow19 * (dsp->fRec14[1] + dsp->fRec14[2])));
			dsp->fRec181[0] = (dsp->fRec182[0] - (fSlow15 * ((fSlow21 * dsp->fRec181[1]) + (fSlow22 * dsp->fRec181[2]))));
			float fTemp102 = (dsp->fRec181[2] + (dsp->fRec181[0] + (2.0f * dsp->fRec181[1])));
			float fTemp103 = (fSlow15 * fTemp102);
			dsp->fVec23[0] = fTemp103;
			dsp->fRec180[0] = ((fSlow47 * dsp->fRec180[1]) + (fSlow48 * ((fSlow49 * dsp->fVec23[1]) + (fSlow50 * fTemp102))));
			dsp->fRec179[0] = (dsp->fRec180[0] - (fSlow45 * ((fSlow29 * dsp->fRec179[1]) + (fSlow51 * dsp->fRec179[2]))));
			float fTemp104 = (fSlow35 * dsp->fRec178[1]);
			dsp->fRec178[0] = ((fSlow45 * (((fSlow28 * dsp->fRec179[0]) + (fSlow52 * dsp->fRec179[1])) + (fSlow28 * dsp->fRec179[2]))) - (fSlow32 * (fTemp104 + (fSlow33 * dsp->fRec178[2]))));
			float fTemp105 = (fSlow41 * dsp->fRec177[1]);
			dsp->fRec177[0] = ((dsp->fRec178[2] + (fSlow32 * (fTemp104 + (fSlow33 * dsp->fRec178[0])))) - (fSlow38 * (fTemp105 + (fSlow39 * dsp->fRec177[2]))));
			dsp->fRec187[0] = ((fSlow47 * dsp->fRec187[1]) + (fSlow48 * (dsp->fVec23[1] + fTemp103)));
			dsp->fRec186[0] = (dsp->fRec187[0] - (fSlow45 * ((fSlow29 * dsp->fRec186[1]) + (fSlow51 * dsp->fRec186[2]))));
			float fTemp106 = (dsp->fRec186[2] + (dsp->fRec186[0] + (2.0f * dsp->fRec186[1])));
			float fTemp107 = (fSlow45 * fTemp106);
			dsp->fVec24[0] = fTemp107;
			dsp->fRec185[0] = ((fSlow58 * dsp->fRec185[1]) + (fSlow59 * ((fSlow60 * dsp->fVec24[1]) + (fSlow61 * fTemp106))));
			dsp->fRec184[0] = (dsp->fRec185[0] - (fSlow56 * ((fSlow35 * dsp->fRec184[1]) + (fSlow62 * dsp->fRec184[2]))));
			float fTemp108 = (fSlow41 * dsp->fRec183[1]);
			dsp->fRec183[0] = ((fSlow56 * (((fSlow34 * dsp->fRec184[0]) + (fSlow63 * dsp->fRec184[1])) + (fSlow34 * dsp->fRec184[2]))) - (fSlow38 * (fTemp108 + (fSlow39 * dsp->fRec183[2]))));
			dsp->fRec191[0] = ((fSlow58 * dsp->fRec191[1]) + (fSlow59 * (dsp->fVec24[1] + fTemp107)));
			dsp->fRec190[0] = (dsp->fRec191[0] - (fSlow56 * ((fSlow35 * dsp->fRec190[1]) + (fSlow62 * dsp->fRec190[2]))));
			float fTemp109 = (dsp->fRec190[2] + (dsp->fRec190[0] + (2.0f * dsp->fRec190[1])));
			float fTemp110 = (fSlow56 * fTemp109);
			dsp->fVec25[0] = fTemp110;
			dsp->fRec189[0] = ((fSlow68 * dsp->fRec189[1]) + (fSlow69 * ((fSlow70 * dsp->fVec25[1]) + (fSlow71 * fTemp109))));
			dsp->fRec188[0] = (dsp->fRec189[0] - (fSlow64 * ((fSlow41 * dsp->fRec188[1]) + (fSlow72 * dsp->fRec188[2]))));
			dsp->fRec193[0] = ((fSlow68 * dsp->fRec193[1]) + (fSlow69 * (dsp->fVec25[1] + fTemp110)));
			dsp->fRec192[0] = (dsp->fRec193[0] - (fSlow64 * ((fSlow41 * dsp->fRec192[1]) + (fSlow72 * dsp->fRec192[2]))));
			float fTemp111 = ((((fSlow120 * (dsp->fRec172[2] + (fSlow38 * (fTemp101 + (fSlow39 * dsp->fRec172[0]))))) + (fSlow121 * (dsp->fRec177[2] + (fSlow38 * (fTemp105 + (fSlow39 * dsp->fRec177[0])))))) + (fSlow122 * (dsp->fRec183[2] + (fSlow38 * (fTemp108 + (fSlow39 * dsp->fRec183[0])))))) + (fSlow64 * ((fSlow123 * (((fSlow40 * dsp->fRec188[0]) + (fSlow73 * dsp->fRec188[1])) + (fSlow40 * dsp->fRec188[2]))) + (fSlow124 * (dsp->fRec192[2] + (dsp->fRec192[0] + (2.0f * dsp->fRec192[1])))))));
			float fTemp112 = (fTemp98 + fTemp111);
			float fTemp113 = (fTemp85 + fTemp112);
			float fTemp114 = (fTemp58 + fTemp113);
			dsp->fRec198[0] = ((fSlow18 * dsp->fRec198[1]) + (fSlow19 * ((fSlow13 * dsp->fRec1[1]) + (fSlow20 * dsp->fRec1[2]))));
			dsp->fRec197[0] = (dsp->fRec198[0] - (fSlow15 * ((fSlow21 * dsp->fRec197[1]) + (fSlow22 * dsp->fRec197[2]))));
			float fTemp115 = (fSlow29 * dsp->fRec196[1]);
			dsp->fRec196[0] = ((fSlow15 * (((fSlow16 * dsp->fRec197[0]) + (fSlow23 * dsp->fRec197[1])) + (fSlow16 * dsp->fRec197[2]))) - (fSlow26 * (fTemp115 + (fSlow27 * dsp->fRec196[2]))));
			float fTemp116 = (fSlow35 * dsp->fRec195[1]);
			dsp->fRec195[0] = ((dsp->fRec196[2] + (fSlow26 * (fTemp115 + (fSlow27 * dsp->fRec196[0])))) - (fSlow32 * (fTemp116 + (fSlow33 * dsp->fRec195[2]))));
			float fTemp117 = (fSlow41 * dsp->fRec194[1]);
			dsp->fRec194[0] = ((dsp->fRec195[2] + (fSlow32 * (fTemp116 + (fSlow33 * dsp->fRec195[0])))) - (fSlow38 * (fTemp117 + (fSlow39 * dsp->fRec194[2]))));
			dsp->fRec204[0] = ((fSlow18 * dsp->fRec204[1]) + (fSlow19 * (dsp->fRec1[1] + dsp->fRec1[2])));
			dsp->fRec203[0] = (dsp->fRec204[0] - (fSlow15 * ((fSlow21 * dsp->fRec203[1]) + (fSlow22 * dsp->fRec203[2]))));
			float fTemp118 = (dsp->fRec203[2] + (dsp->fRec203[0] + (2.0f * dsp->fRec203[1])));
			float fTemp119 = (fSlow15 * fTemp118);
			dsp->fVec26[0] = fTemp119;
			dsp->fRec202[0] = ((fSlow47 * dsp->fRec202[1]) + (fSlow48 * ((fSlow49 * dsp->fVec26[1]) + (fSlow50 * fTemp118))));
			dsp->fRec201[0] = (dsp->fRec202[0] - (fSlow45 * ((fSlow29 * dsp->fRec201[1]) + (fSlow51 * dsp->fRec201[2]))));
			float fTemp120 = (fSlow35 * dsp->fRec200[1]);
			dsp->fRec200[0] = ((fSlow45 * (((fSlow28 * dsp->fRec201[0]) + (fSlow52 * dsp->fRec201[1])) + (fSlow28 * dsp->fRec201[2]))) - (fSlow32 * (fTemp120 + (fSlow33 * dsp->fRec200[2]))));
			float fTemp121 = (fSlow41 * dsp->fRec199[1]);
			dsp->fRec199[0] = ((dsp->fRec200[2] + (fSlow32 * (fTemp120 + (fSlow33 * dsp->fRec200[0])))) - (fSlow38 * (fTemp121 + (fSlow39 * dsp->fRec199[2]))));
			dsp->fRec209[0] = ((fSlow47 * dsp->fRec209[1]) + (fSlow48 * (dsp->fVec26[1] + fTemp119)));
			dsp->fRec208[0] = (dsp->fRec209[0] - (fSlow45 * ((fSlow29 * dsp->fRec208[1]) + (fSlow51 * dsp->fRec208[2]))));
			float fTemp122 = (dsp->fRec208[2] + (dsp->fRec208[0] + (2.0f * dsp->fRec208[1])));
			float fTemp123 = (fSlow45 * fTemp122);
			dsp->fVec27[0] = fTemp123;
			dsp->fRec207[0] = ((fSlow58 * dsp->fRec207[1]) + (fSlow59 * ((fSlow60 * dsp->fVec27[1]) + (fSlow61 * fTemp122))));
			dsp->fRec206[0] = (dsp->fRec207[0] - (fSlow56 * ((fSlow35 * dsp->fRec206[1]) + (fSlow62 * dsp->fRec206[2]))));
			float fTemp124 = (fSlow41 * dsp->fRec205[1]);
			dsp->fRec205[0] = ((fSlow56 * (((fSlow34 * dsp->fRec206[0]) + (fSlow63 * dsp->fRec206[1])) + (fSlow34 * dsp->fRec206[2]))) - (fSlow38 * (fTemp124 + (fSlow39 * dsp->fRec205[2]))));
			dsp->fRec213[0] = ((fSlow58 * dsp->fRec213[1]) + (fSlow59 * (dsp->fVec27[1] + fTemp123)));
			dsp->fRec212[0] = (dsp->fRec213[0] - (fSlow56 * ((fSlow35 * dsp->fRec212[1]) + (fSlow62 * dsp->fRec212[2]))));
			float fTemp125 = (dsp->fRec212[2] + (dsp->fRec212[0] + (2.0f * dsp->fRec212[1])));
			float fTemp126 = (fSlow56 * fTemp125);
			dsp->fVec28[0] = fTemp126;
			dsp->fRec211[0] = ((fSlow68 * dsp->fRec211[1]) + (fSlow69 * ((fSlow70 * dsp->fVec28[1]) + (fSlow71 * fTemp125))));
			dsp->fRec210[0] = (dsp->fRec211[0] - (fSlow64 * ((fSlow41 * dsp->fRec210[1]) + (fSlow72 * dsp->fRec210[2]))));
			dsp->fRec215[0] = ((fSlow68 * dsp->fRec215[1]) + (fSlow69 * (dsp->fVec28[1] + fTemp126)));
			dsp->fRec214[0] = (dsp->fRec215[0] - (fSlow64 * ((fSlow41 * dsp->fRec214[1]) + (fSlow72 * dsp->fRec214[2]))));
			float fTemp127 = ((((fSlow127 * (dsp->fRec194[2] + (fSlow38 * (fTemp117 + (fSlow39 * dsp->fRec194[0]))))) + (fSlow128 * (dsp->fRec199[2] + (fSlow38 * (fTemp121 + (fSlow39 * dsp->fRec199[0])))))) + (fSlow129 * (dsp->fRec205[2] + (fSlow38 * (fTemp124 + (fSlow39 * dsp->fRec205[0])))))) + (fSlow64 * ((fSlow130 * (((fSlow40 * dsp->fRec210[0]) + (fSlow73 * dsp->fRec210[1])) + (fSlow40 * dsp->fRec210[2]))) + (fSlow131 * (dsp->fRec214[2] + (dsp->fRec214[0] + (2.0f * dsp->fRec214[1])))))));
			dsp->fRec220[0] = ((fSlow18 * dsp->fRec220[1]) + (fSlow19 * ((fSlow13 * dsp->fRec9[1]) + (fSlow20 * dsp->fRec9[2]))));
			dsp->fRec219[0] = (dsp->fRec220[0] - (fSlow15 * ((fSlow21 * dsp->fRec219[1]) + (fSlow22 * dsp->fRec219[2]))));
			float fTemp128 = (fSlow29 * dsp->fRec218[1]);
			dsp->fRec218[0] = ((fSlow15 * (((fSlow16 * dsp->fRec219[0]) + (fSlow23 * dsp->fRec219[1])) + (fSlow16 * dsp->fRec219[2]))) - (fSlow26 * (fTemp128 + (fSlow27 * dsp->fRec218[2]))));
			float fTemp129 = (fSlow35 * dsp->fRec217[1]);
			dsp->fRec217[0] = ((dsp->fRec218[2] + (fSlow26 * (fTemp128 + (fSlow27 * dsp->fRec218[0])))) - (fSlow32 * (fTemp129 + (fSlow33 * dsp->fRec217[2]))));
			float fTemp130 = (fSlow41 * dsp->fRec216[1]);
			dsp->fRec216[0] = ((dsp->fRec217[2] + (fSlow32 * (fTemp129 + (fSlow33 * dsp->fRec217[0])))) - (fSlow38 * (fTemp130 + (fSlow39 * dsp->fRec216[2]))));
			dsp->fRec226[0] = ((fSlow18 * dsp->fRec226[1]) + (fSlow19 * (dsp->fRec9[1] + dsp->fRec9[2])));
			dsp->fRec225[0] = (dsp->fRec226[0] - (fSlow15 * ((fSlow21 * dsp->fRec225[1]) + (fSlow22 * dsp->fRec225[2]))));
			float fTemp131 = (dsp->fRec225[2] + (dsp->fRec225[0] + (2.0f * dsp->fRec225[1])));
			float fTemp132 = (fSlow15 * fTemp131);
			dsp->fVec29[0] = fTemp132;
			dsp->fRec224[0] = ((fSlow47 * dsp->fRec224[1]) + (fSlow48 * ((fSlow49 * dsp->fVec29[1]) + (fSlow50 * fTemp131))));
			dsp->fRec223[0] = (dsp->fRec224[0] - (fSlow45 * ((fSlow29 * dsp->fRec223[1]) + (fSlow51 * dsp->fRec223[2]))));
			float fTemp133 = (fSlow35 * dsp->fRec222[1]);
			dsp->fRec222[0] = ((fSlow45 * (((fSlow28 * dsp->fRec223[0]) + (fSlow52 * dsp->fRec223[1])) + (fSlow28 * dsp->fRec223[2]))) - (fSlow32 * (fTemp133 + (fSlow33 * dsp->fRec222[2]))));
			float fTemp134 = (fSlow41 * dsp->fRec221[1]);
			dsp->fRec221[0] = ((dsp->fRec222[2] + (fSlow32 * (fTemp133 + (fSlow33 * dsp->fRec222[0])))) - (fSlow38 * (fTemp134 + (fSlow39 * dsp->fRec221[2]))));
			dsp->fRec231[0] = ((fSlow47 * dsp->fRec231[1]) + (fSlow48 * (dsp->fVec29[1] + fTemp132)));
			dsp->fRec230[0] = (dsp->fRec231[0] - (fSlow45 * ((fSlow29 * dsp->fRec230[1]) + (fSlow51 * dsp->fRec230[2]))));
			float fTemp135 = (dsp->fRec230[2] + (dsp->fRec230[0] + (2.0f * dsp->fRec230[1])));
			float fTemp136 = (fSlow45 * fTemp135);
			dsp->fVec30[0] = fTemp136;
			dsp->fRec229[0] = ((fSlow58 * dsp->fRec229[1]) + (fSlow59 * ((fSlow60 * dsp->fVec30[1]) + (fSlow61 * fTemp135))));
			dsp->fRec228[0] = (dsp->fRec229[0] - (fSlow56 * ((fSlow35 * dsp->fRec228[1]) + (fSlow62 * dsp->fRec228[2]))));
			float fTemp137 = (fSlow41 * dsp->fRec227[1]);
			dsp->fRec227[0] = ((fSlow56 * (((fSlow34 * dsp->fRec228[0]) + (fSlow63 * dsp->fRec228[1])) + (fSlow34 * dsp->fRec228[2]))) - (fSlow38 * (fTemp137 + (fSlow39 * dsp->fRec227[2]))));
			dsp->fRec235[0] = ((fSlow58 * dsp->fRec235[1]) + (fSlow59 * (dsp->fVec30[1] + fTemp136)));
			dsp->fRec234[0] = (dsp->fRec235[0] - (fSlow56 * ((fSlow35 * dsp->fRec234[1]) + (fSlow62 * dsp->fRec234[2]))));
			float fTemp138 = (dsp->fRec234[2] + (dsp->fRec234[0] + (2.0f * dsp->fRec234[1])));
			float fTemp139 = (fSlow56 * fTemp138);
			dsp->fVec31[0] = fTemp139;
			dsp->fRec233[0] = ((fSlow68 * dsp->fRec233[1]) + (fSlow69 * ((fSlow70 * dsp->fVec31[1]) + (fSlow71 * fTemp138))));
			dsp->fRec232[0] = (dsp->fRec233[0] - (fSlow64 * ((fSlow41 * dsp->fRec232[1]) + (fSlow72 * dsp->fRec232[2]))));
			dsp->fRec237[0] = ((fSlow68 * dsp->fRec237[1]) + (fSlow69 * (dsp->fVec31[1] + fTemp139)));
			dsp->fRec236[0] = (dsp->fRec237[0] - (fSlow64 * ((fSlow41 * dsp->fRec236[1]) + (fSlow72 * dsp->fRec236[2]))));
			float fTemp140 = ((((fSlow134 * (dsp->fRec216[2] + (fSlow38 * (fTemp130 + (fSlow39 * dsp->fRec216[0]))))) + (fSlow135 * (dsp->fRec221[2] + (fSlow38 * (fTemp134 + (fSlow39 * dsp->fRec221[0])))))) + (fSlow136 * (dsp->fRec227[2] + (fSlow38 * (fTemp137 + (fSlow39 * dsp->fRec227[0])))))) + (fSlow64 * ((fSlow137 * (((fSlow40 * dsp->fRec232[0]) + (fSlow73 * dsp->fRec232[1])) + (fSlow40 * dsp->fRec232[2]))) + (fSlow138 * (dsp->fRec236[2] + (dsp->fRec236[0] + (2.0f * dsp->fRec236[1])))))));
			float fTemp141 = (fTemp127 + fTemp140);
			dsp->fRec242[0] = ((fSlow18 * dsp->fRec242[1]) + (fSlow19 * ((fSlow13 * dsp->fRec5[1]) + (fSlow20 * dsp->fRec5[2]))));
			dsp->fRec241[0] = (dsp->fRec242[0] - (fSlow15 * ((fSlow21 * dsp->fRec241[1]) + (fSlow22 * dsp->fRec241[2]))));
			float fTemp142 = (fSlow29 * dsp->fRec240[1]);
			dsp->fRec240[0] = ((fSlow15 * (((fSlow16 * dsp->fRec241[0]) + (fSlow23 * dsp->fRec241[1])) + (fSlow16 * dsp->fRec241[2]))) - (fSlow26 * (fTemp142 + (fSlow27 * dsp->fRec240[2]))));
			float fTemp143 = (fSlow35 * dsp->fRec239[1]);
			dsp->fRec239[0] = ((dsp->fRec240[2] + (fSlow26 * (fTemp142 + (fSlow27 * dsp->fRec240[0])))) - (fSlow32 * (fTemp143 + (fSlow33 * dsp->fRec239[2]))));
			float fTemp144 = (fSlow41 * dsp->fRec238[1]);
			dsp->fRec238[0] = ((dsp->fRec239[2] + (fSlow32 * (fTemp143 + (fSlow33 * dsp->fRec239[0])))) - (fSlow38 * (fTemp144 + (fSlow39 * dsp->fRec238[2]))));
			dsp->fRec248[0] = ((fSlow18 * dsp->fRec248[1]) + (fSlow19 * (dsp->fRec5[1] + dsp->fRec5[2])));
			dsp->fRec247[0] = (dsp->fRec248[0] - (fSlow15 * ((fSlow21 * dsp->fRec247[1]) + (fSlow22 * dsp->fRec247[2]))));
			float fTemp145 = (dsp->fRec247[2] + (dsp->fRec247[0] + (2.0f * dsp->fRec247[1])));
			float fTemp146 = (fSlow15 * fTemp145);
			dsp->fVec32[0] = fTemp146;
			dsp->fRec246[0] = ((fSlow47 * dsp->fRec246[1]) + (fSlow48 * ((fSlow49 * dsp->fVec32[1]) + (fSlow50 * fTemp145))));
			dsp->fRec245[0] = (dsp->fRec246[0] - (fSlow45 * ((fSlow29 * dsp->fRec245[1]) + (fSlow51 * dsp->fRec245[2]))));
			float fTemp147 = (fSlow35 * dsp->fRec244[1]);
			dsp->fRec244[0] = ((fSlow45 * (((fSlow28 * dsp->fRec245[0]) + (fSlow52 * dsp->fRec245[1])) + (fSlow28 * dsp->fRec245[2]))) - (fSlow32 * (fTemp147 + (fSlow33 * dsp->fRec244[2]))));
			float fTemp148 = (fSlow41 * dsp->fRec243[1]);
			dsp->fRec243[0] = ((dsp->fRec244[2] + (fSlow32 * (fTemp147 + (fSlow33 * dsp->fRec244[0])))) - (fSlow38 * (fTemp148 + (fSlow39 * dsp->fRec243[2]))));
			dsp->fRec253[0] = ((fSlow47 * dsp->fRec253[1]) + (fSlow48 * (dsp->fVec32[1] + fTemp146)));
			dsp->fRec252[0] = (dsp->fRec253[0] - (fSlow45 * ((fSlow29 * dsp->fRec252[1]) + (fSlow51 * dsp->fRec252[2]))));
			float fTemp149 = (dsp->fRec252[2] + (dsp->fRec252[0] + (2.0f * dsp->fRec252[1])));
			float fTemp150 = (fSlow45 * fTemp149);
			dsp->fVec33[0] = fTemp150;
			dsp->fRec251[0] = ((fSlow58 * dsp->fRec251[1]) + (fSlow59 * ((fSlow60 * dsp->fVec33[1]) + (fSlow61 * fTemp149))));
			dsp->fRec250[0] = (dsp->fRec251[0] - (fSlow56 * ((fSlow35 * dsp->fRec250[1]) + (fSlow62 * dsp->fRec250[2]))));
			float fTemp151 = (fSlow41 * dsp->fRec249[1]);
			dsp->fRec249[0] = ((fSlow56 * (((fSlow34 * dsp->fRec250[0]) + (fSlow63 * dsp->fRec250[1])) + (fSlow34 * dsp->fRec250[2]))) - (fSlow38 * (fTemp151 + (fSlow39 * dsp->fRec249[2]))));
			dsp->fRec257[0] = ((fSlow58 * dsp->fRec257[1]) + (fSlow59 * (dsp->fVec33[1] + fTemp150)));
			dsp->fRec256[0] = (dsp->fRec257[0] - (fSlow56 * ((fSlow35 * dsp->fRec256[1]) + (fSlow62 * dsp->fRec256[2]))));
			float fTemp152 = (dsp->fRec256[2] + (dsp->fRec256[0] + (2.0f * dsp->fRec256[1])));
			float fTemp153 = (fSlow56 * fTemp152);
			dsp->fVec34[0] = fTemp153;
			dsp->fRec255[0] = ((fSlow68 * dsp->fRec255[1]) + (fSlow69 * ((fSlow70 * dsp->fVec34[1]) + (fSlow71 * fTemp152))));
			dsp->fRec254[0] = (dsp->fRec255[0] - (fSlow64 * ((fSlow41 * dsp->fRec254[1]) + (fSlow72 * dsp->fRec254[2]))));
			dsp->fRec259[0] = ((fSlow68 * dsp->fRec259[1]) + (fSlow69 * (dsp->fVec34[1] + fTemp153)));
			dsp->fRec258[0] = (dsp->fRec259[0] - (fSlow64 * ((fSlow41 * dsp->fRec258[1]) + (fSlow72 * dsp->fRec258[2]))));
			float fTemp154 = ((((fSlow141 * (dsp->fRec238[2] + (fSlow38 * (fTemp144 + (fSlow39 * dsp->fRec238[0]))))) + (fSlow142 * (dsp->fRec243[2] + (fSlow38 * (fTemp148 + (fSlow39 * dsp->fRec243[0])))))) + (fSlow143 * (dsp->fRec249[2] + (fSlow38 * (fTemp151 + (fSlow39 * dsp->fRec249[0])))))) + (fSlow64 * ((fSlow144 * (((fSlow40 * dsp->fRec254[0]) + (fSlow73 * dsp->fRec254[1])) + (fSlow40 * dsp->fRec254[2]))) + (fSlow145 * (dsp->fRec258[2] + (dsp->fRec258[0] + (2.0f * dsp->fRec258[1])))))));
			dsp->fRec264[0] = ((fSlow18 * dsp->fRec264[1]) + (fSlow19 * ((fSlow13 * dsp->fRec13[1]) + (fSlow20 * dsp->fRec13[2]))));
			dsp->fRec263[0] = (dsp->fRec264[0] - (fSlow15 * ((fSlow21 * dsp->fRec263[1]) + (fSlow22 * dsp->fRec263[2]))));
			float fTemp155 = (fSlow29 * dsp->fRec262[1]);
			dsp->fRec262[0] = ((fSlow15 * (((fSlow16 * dsp->fRec263[0]) + (fSlow23 * dsp->fRec263[1])) + (fSlow16 * dsp->fRec263[2]))) - (fSlow26 * (fTemp155 + (fSlow27 * dsp->fRec262[2]))));
			float fTemp156 = (fSlow35 * dsp->fRec261[1]);
			dsp->fRec261[0] = ((dsp->fRec262[2] + (fSlow26 * (fTemp155 + (fSlow27 * dsp->fRec262[0])))) - (fSlow32 * (fTemp156 + (fSlow33 * dsp->fRec261[2]))));
			float fTemp157 = (fSlow41 * dsp->fRec260[1]);
			dsp->fRec260[0] = ((dsp->fRec261[2] + (fSlow32 * (fTemp156 + (fSlow33 * dsp->fRec261[0])))) - (fSlow38 * (fTemp157 + (fSlow39 * dsp->fRec260[2]))));
			dsp->fRec270[0] = ((fSlow18 * dsp->fRec270[1]) + (fSlow19 * (dsp->fRec13[1] + dsp->fRec13[2])));
			dsp->fRec269[0] = (dsp->fRec270[0] - (fSlow15 * ((fSlow21 * dsp->fRec269[1]) + (fSlow22 * dsp->fRec269[2]))));
			float fTemp158 = (dsp->fRec269[2] + (dsp->fRec269[0] + (2.0f * dsp->fRec269[1])));
			float fTemp159 = (fSlow15 * fTemp158);
			dsp->fVec35[0] = fTemp159;
			dsp->fRec268[0] = ((fSlow47 * dsp->fRec268[1]) + (fSlow48 * ((fSlow49 * dsp->fVec35[1]) + (fSlow50 * fTemp158))));
			dsp->fRec267[0] = (dsp->fRec268[0] - (fSlow45 * ((fSlow29 * dsp->fRec267[1]) + (fSlow51 * dsp->fRec267[2]))));
			float fTemp160 = (fSlow35 * dsp->fRec266[1]);
			dsp->fRec266[0] = ((fSlow45 * (((fSlow28 * dsp->fRec267[0]) + (fSlow52 * dsp->fRec267[1])) + (fSlow28 * dsp->fRec267[2]))) - (fSlow32 * (fTemp160 + (fSlow33 * dsp->fRec266[2]))));
			float fTemp161 = (fSlow41 * dsp->fRec265[1]);
			dsp->fRec265[0] = ((dsp->fRec266[2] + (fSlow32 * (fTemp160 + (fSlow33 * dsp->fRec266[0])))) - (fSlow38 * (fTemp161 + (fSlow39 * dsp->fRec265[2]))));
			dsp->fRec275[0] = ((fSlow47 * dsp->fRec275[1]) + (fSlow48 * (dsp->fVec35[1] + fTemp159)));
			dsp->fRec274[0] = (dsp->fRec275[0] - (fSlow45 * ((fSlow29 * dsp->fRec274[1]) + (fSlow51 * dsp->fRec274[2]))));
			float fTemp162 = (dsp->fRec274[2] + (dsp->fRec274[0] + (2.0f * dsp->fRec274[1])));
			float fTemp163 = (fSlow45 * fTemp162);
			dsp->fVec36[0] = fTemp163;
			dsp->fRec273[0] = ((fSlow58 * dsp->fRec273[1]) + (fSlow59 * ((fSlow60 * dsp->fVec36[1]) + (fSlow61 * fTemp162))));
			dsp->fRec272[0] = (dsp->fRec273[0] - (fSlow56 * ((fSlow35 * dsp->fRec272[1]) + (fSlow62 * dsp->fRec272[2]))));
			float fTemp164 = (fSlow41 * dsp->fRec271[1]);
			dsp->fRec271[0] = ((fSlow56 * (((fSlow34 * dsp->fRec272[0]) + (fSlow63 * dsp->fRec272[1])) + (fSlow34 * dsp->fRec272[2]))) - (fSlow38 * (fTemp164 + (fSlow39 * dsp->fRec271[2]))));
			dsp->fRec279[0] = ((fSlow58 * dsp->fRec279[1]) + (fSlow59 * (dsp->fVec36[1] + fTemp163)));
			dsp->fRec278[0] = (dsp->fRec279[0] - (fSlow56 * ((fSlow35 * dsp->fRec278[1]) + (fSlow62 * dsp->fRec278[2]))));
			float fTemp165 = (dsp->fRec278[2] + (dsp->fRec278[0] + (2.0f * dsp->fRec278[1])));
			float fTemp166 = (fSlow56 * fTemp165);
			dsp->fVec37[0] = fTemp166;
			dsp->fRec277[0] = ((fSlow68 * dsp->fRec277[1]) + (fSlow69 * ((fSlow70 * dsp->fVec37[1]) + (fSlow71 * fTemp165))));
			dsp->fRec276[0] = (dsp->fRec277[0] - (fSlow64 * ((fSlow41 * dsp->fRec276[1]) + (fSlow72 * dsp->fRec276[2]))));
			dsp->fRec281[0] = ((fSlow68 * dsp->fRec281[1]) + (fSlow69 * (dsp->fVec37[1] + fTemp166)));
			dsp->fRec280[0] = (dsp->fRec281[0] - (fSlow64 * ((fSlow41 * dsp->fRec280[1]) + (fSlow72 * dsp->fRec280[2]))));
			float fTemp167 = ((((fSlow148 * (dsp->fRec260[2] + (fSlow38 * (fTemp157 + (fSlow39 * dsp->fRec260[0]))))) + (fSlow149 * (dsp->fRec265[2] + (fSlow38 * (fTemp161 + (fSlow39 * dsp->fRec265[0])))))) + (fSlow150 * (dsp->fRec271[2] + (fSlow38 * (fTemp164 + (fSlow39 * dsp->fRec271[0])))))) + (fSlow64 * ((fSlow151 * (((fSlow40 * dsp->fRec276[0]) + (fSlow73 * dsp->fRec276[1])) + (fSlow40 * dsp->fRec276[2]))) + (fSlow152 * (dsp->fRec280[2] + (dsp->fRec280[0] + (2.0f * dsp->fRec280[1])))))));
			float fTemp168 = (fTemp154 + fTemp167);
			float fTemp169 = (fTemp141 + fTemp168);
			dsp->fRec286[0] = ((fSlow18 * dsp->fRec286[1]) + (fSlow19 * ((fSlow13 * dsp->fRec3[1]) + (fSlow20 * dsp->fRec3[2]))));
			dsp->fRec285[0] = (dsp->fRec286[0] - (fSlow15 * ((fSlow21 * dsp->fRec285[1]) + (fSlow22 * dsp->fRec285[2]))));
			float fTemp170 = (fSlow29 * dsp->fRec284[1]);
			dsp->fRec284[0] = ((fSlow15 * (((fSlow16 * dsp->fRec285[0]) + (fSlow23 * dsp->fRec285[1])) + (fSlow16 * dsp->fRec285[2]))) - (fSlow26 * (fTemp170 + (fSlow27 * dsp->fRec284[2]))));
			float fTemp171 = (fSlow35 * dsp->fRec283[1]);
			dsp->fRec283[0] = ((dsp->fRec284[2] + (fSlow26 * (fTemp170 + (fSlow27 * dsp->fRec284[0])))) - (fSlow32 * (fTemp171 + (fSlow33 * dsp->fRec283[2]))));
			float fTemp172 = (fSlow41 * dsp->fRec282[1]);
			dsp->fRec282[0] = ((dsp->fRec283[2] + (fSlow32 * (fTemp171 + (fSlow33 * dsp->fRec283[0])))) - (fSlow38 * (fTemp172 + (fSlow39 * dsp->fRec282[2]))));
			dsp->fRec292[0] = ((fSlow18 * dsp->fRec292[1]) + (fSlow19 * (dsp->fRec3[1] + dsp->fRec3[2])));
			dsp->fRec291[0] = (dsp->fRec292[0] - (fSlow15 * ((fSlow21 * dsp->fRec291[1]) + (fSlow22 * dsp->fRec291[2]))));
			float fTemp173 = (dsp->fRec291[2] + (dsp->fRec291[0] + (2.0f * dsp->fRec291[1])));
			float fTemp174 = (fSlow15 * fTemp173);
			dsp->fVec38[0] = fTemp174;
			dsp->fRec290[0] = ((fSlow47 * dsp->fRec290[1]) + (fSlow48 * ((fSlow49 * dsp->fVec38[1]) + (fSlow50 * fTemp173))));
			dsp->fRec289[0] = (dsp->fRec290[0] - (fSlow45 * ((fSlow29 * dsp->fRec289[1]) + (fSlow51 * dsp->fRec289[2]))));
			float fTemp175 = (fSlow35 * dsp->fRec288[1]);
			dsp->fRec288[0] = ((fSlow45 * (((fSlow28 * dsp->fRec289[0]) + (fSlow52 * dsp->fRec289[1])) + (fSlow28 * dsp->fRec289[2]))) - (fSlow32 * (fTemp175 + (fSlow33 * dsp->fRec288[2]))));
			float fTemp176 = (fSlow41 * dsp->fRec287[1]);
			dsp->fRec287[0] = ((dsp->fRec288[2] + (fSlow32 * (fTemp175 + (fSlow33 * dsp->fRec288[0])))) - (fSlow38 * (fTemp176 + (fSlow39 * dsp->fRec287[2]))));
			dsp->fRec297[0] = ((fSlow47 * dsp->fRec297[1]) + (fSlow48 * (dsp->fVec38[1] + fTemp174)));
			dsp->fRec296[0] = (dsp->fRec297[0] - (fSlow45 * ((fSlow29 * dsp->fRec296[1]) + (fSlow51 * dsp->fRec296[2]))));
			float fTemp177 = (dsp->fRec296[2] + (dsp->fRec296[0] + (2.0f * dsp->fRec296[1])));
			float fTemp178 = (fSlow45 * fTemp177);
			dsp->fVec39[0] = fTemp178;
			dsp->fRec295[0] = ((fSlow58 * dsp->fRec295[1]) + (fSlow59 * ((fSlow60 * dsp->fVec39[1]) + (fSlow61 * fTemp177))));
			dsp->fRec294[0] = (dsp->fRec295[0] - (fSlow56 * ((fSlow35 * dsp->fRec294[1]) + (fSlow62 * dsp->fRec294[2]))));
			float fTemp179 = (fSlow41 * dsp->fRec293[1]);
			dsp->fRec293[0] = ((fSlow56 * (((fSlow34 * dsp->fRec294[0]) + (fSlow63 * dsp->fRec294[1])) + (fSlow34 * dsp->fRec294[2]))) - (fSlow38 * (fTemp179 + (fSlow39 * dsp->fRec293[2]))));
			dsp->fRec301[0] = ((fSlow58 * dsp->fRec301[1]) + (fSlow59 * (dsp->fVec39[1] + fTemp178)));
			dsp->fRec300[0] = (dsp->fRec301[0] - (fSlow56 * ((fSlow35 * dsp->fRec300[1]) + (fSlow62 * dsp->fRec300[2]))));
			float fTemp180 = (dsp->fRec300[2] + (dsp->fRec300[0] + (2.0f * dsp->fRec300[1])));
			float fTemp181 = (fSlow56 * fTemp180);
			dsp->fVec40[0] = fTemp181;
			dsp->fRec299[0] = ((fSlow68 * dsp->fRec299[1]) + (fSlow69 * ((fSlow70 * dsp->fVec40[1]) + (fSlow71 * fTemp180))));
			dsp->fRec298[0] = (dsp->fRec299[0] - (fSlow64 * ((fSlow41 * dsp->fRec298[1]) + (fSlow72 * dsp->fRec298[2]))));
			dsp->fRec303[0] = ((fSlow68 * dsp->fRec303[1]) + (fSlow69 * (dsp->fVec40[1] + fTemp181)));
			dsp->fRec302[0] = (dsp->fRec303[0] - (fSlow64 * ((fSlow41 * dsp->fRec302[1]) + (fSlow72 * dsp->fRec302[2]))));
			float fTemp182 = ((((fSlow155 * (dsp->fRec282[2] + (fSlow38 * (fTemp172 + (fSlow39 * dsp->fRec282[0]))))) + (fSlow156 * (dsp->fRec287[2] + (fSlow38 * (fTemp176 + (fSlow39 * dsp->fRec287[0])))))) + (fSlow157 * (dsp->fRec293[2] + (fSlow38 * (fTemp179 + (fSlow39 * dsp->fRec293[0])))))) + (fSlow64 * ((fSlow158 * (((fSlow40 * dsp->fRec298[0]) + (fSlow73 * dsp->fRec298[1])) + (fSlow40 * dsp->fRec298[2]))) + (fSlow159 * (dsp->fRec302[2] + (dsp->fRec302[0] + (2.0f * dsp->fRec302[1])))))));
			dsp->fRec308[0] = ((fSlow18 * dsp->fRec308[1]) + (fSlow19 * ((fSlow13 * dsp->fRec11[1]) + (fSlow20 * dsp->fRec11[2]))));
			dsp->fRec307[0] = (dsp->fRec308[0] - (fSlow15 * ((fSlow21 * dsp->fRec307[1]) + (fSlow22 * dsp->fRec307[2]))));
			float fTemp183 = (fSlow29 * dsp->fRec306[1]);
			dsp->fRec306[0] = ((fSlow15 * (((fSlow16 * dsp->fRec307[0]) + (fSlow23 * dsp->fRec307[1])) + (fSlow16 * dsp->fRec307[2]))) - (fSlow26 * (fTemp183 + (fSlow27 * dsp->fRec306[2]))));
			float fTemp184 = (fSlow35 * dsp->fRec305[1]);
			dsp->fRec305[0] = ((dsp->fRec306[2] + (fSlow26 * (fTemp183 + (fSlow27 * dsp->fRec306[0])))) - (fSlow32 * (fTemp184 + (fSlow33 * dsp->fRec305[2]))));
			float fTemp185 = (fSlow41 * dsp->fRec304[1]);
			dsp->fRec304[0] = ((dsp->fRec305[2] + (fSlow32 * (fTemp184 + (fSlow33 * dsp->fRec305[0])))) - (fSlow38 * (fTemp185 + (fSlow39 * dsp->fRec304[2]))));
			dsp->fRec314[0] = ((fSlow18 * dsp->fRec314[1]) + (fSlow19 * (dsp->fRec11[1] + dsp->fRec11[2])));
			dsp->fRec313[0] = (dsp->fRec314[0] - (fSlow15 * ((fSlow21 * dsp->fRec313[1]) + (fSlow22 * dsp->fRec313[2]))));
			float fTemp186 = (dsp->fRec313[2] + (dsp->fRec313[0] + (2.0f * dsp->fRec313[1])));
			float fTemp187 = (fSlow15 * fTemp186);
			dsp->fVec41[0] = fTemp187;
			dsp->fRec312[0] = ((fSlow47 * dsp->fRec312[1]) + (fSlow48 * ((fSlow49 * dsp->fVec41[1]) + (fSlow50 * fTemp186))));
			dsp->fRec311[0] = (dsp->fRec312[0] - (fSlow45 * ((fSlow29 * dsp->fRec311[1]) + (fSlow51 * dsp->fRec311[2]))));
			float fTemp188 = (fSlow35 * dsp->fRec310[1]);
			dsp->fRec310[0] = ((fSlow45 * (((fSlow28 * dsp->fRec311[0]) + (fSlow52 * dsp->fRec311[1])) + (fSlow28 * dsp->fRec311[2]))) - (fSlow32 * (fTemp188 + (fSlow33 * dsp->fRec310[2]))));
			float fTemp189 = (fSlow41 * dsp->fRec309[1]);
			dsp->fRec309[0] = ((dsp->fRec310[2] + (fSlow32 * (fTemp188 + (fSlow33 * dsp->fRec310[0])))) - (fSlow38 * (fTemp189 + (fSlow39 * dsp->fRec309[2]))));
			dsp->fRec319[0] = ((fSlow47 * dsp->fRec319[1]) + (fSlow48 * (dsp->fVec41[1] + fTemp187)));
			dsp->fRec318[0] = (dsp->fRec319[0] - (fSlow45 * ((fSlow29 * dsp->fRec318[1]) + (fSlow51 * dsp->fRec318[2]))));
			float fTemp190 = (dsp->fRec318[2] + (dsp->fRec318[0] + (2.0f * dsp->fRec318[1])));
			float fTemp191 = (fSlow45 * fTemp190);
			dsp->fVec42[0] = fTemp191;
			dsp->fRec317[0] = ((fSlow58 * dsp->fRec317[1]) + (fSlow59 * ((fSlow60 * dsp->fVec42[1]) + (fSlow61 * fTemp190))));
			dsp->fRec316[0] = (dsp->fRec317[0] - (fSlow56 * ((fSlow35 * dsp->fRec316[1]) + (fSlow62 * dsp->fRec316[2]))));
			float fTemp192 = (fSlow41 * dsp->fRec315[1]);
			dsp->fRec315[0] = ((fSlow56 * (((fSlow34 * dsp->fRec316[0]) + (fSlow63 * dsp->fRec316[1])) + (fSlow34 * dsp->fRec316[2]))) - (fSlow38 * (fTemp192 + (fSlow39 * dsp->fRec315[2]))));
			dsp->fRec323[0] = ((fSlow58 * dsp->fRec323[1]) + (fSlow59 * (dsp->fVec42[1] + fTemp191)));
			dsp->fRec322[0] = (dsp->fRec323[0] - (fSlow56 * ((fSlow35 * dsp->fRec322[1]) + (fSlow62 * dsp->fRec322[2]))));
			float fTemp193 = (dsp->fRec322[2] + (dsp->fRec322[0] + (2.0f * dsp->fRec322[1])));
			float fTemp194 = (fSlow56 * fTemp193);
			dsp->fVec43[0] = fTemp194;
			dsp->fRec321[0] = ((fSlow68 * dsp->fRec321[1]) + (fSlow69 * ((fSlow70 * dsp->fVec43[1]) + (fSlow71 * fTemp193))));
			dsp->fRec320[0] = (dsp->fRec321[0] - (fSlow64 * ((fSlow41 * dsp->fRec320[1]) + (fSlow72 * dsp->fRec320[2]))));
			dsp->fRec325[0] = ((fSlow68 * dsp->fRec325[1]) + (fSlow69 * (dsp->fVec43[1] + fTemp194)));
			dsp->fRec324[0] = (dsp->fRec325[0] - (fSlow64 * ((fSlow41 * dsp->fRec324[1]) + (fSlow72 * dsp->fRec324[2]))));
			float fTemp195 = ((((fSlow162 * (dsp->fRec304[2] + (fSlow38 * (fTemp185 + (fSlow39 * dsp->fRec304[0]))))) + (fSlow163 * (dsp->fRec309[2] + (fSlow38 * (fTemp189 + (fSlow39 * dsp->fRec309[0])))))) + (fSlow164 * (dsp->fRec315[2] + (fSlow38 * (fTemp192 + (fSlow39 * dsp->fRec315[0])))))) + (fSlow64 * ((fSlow165 * (((fSlow40 * dsp->fRec320[0]) + (fSlow73 * dsp->fRec320[1])) + (fSlow40 * dsp->fRec320[2]))) + (fSlow166 * (dsp->fRec324[2] + (dsp->fRec324[0] + (2.0f * dsp->fRec324[1])))))));
			float fTemp196 = (fTemp182 + fTemp195);
			dsp->fRec330[0] = ((fSlow18 * dsp->fRec330[1]) + (fSlow19 * ((fSlow13 * dsp->fRec7[1]) + (fSlow20 * dsp->fRec7[2]))));
			dsp->fRec329[0] = (dsp->fRec330[0] - (fSlow15 * ((fSlow21 * dsp->fRec329[1]) + (fSlow22 * dsp->fRec329[2]))));
			float fTemp197 = (fSlow29 * dsp->fRec328[1]);
			dsp->fRec328[0] = ((fSlow15 * (((fSlow16 * dsp->fRec329[0]) + (fSlow23 * dsp->fRec329[1])) + (fSlow16 * dsp->fRec329[2]))) - (fSlow26 * (fTemp197 + (fSlow27 * dsp->fRec328[2]))));
			float fTemp198 = (fSlow35 * dsp->fRec327[1]);
			dsp->fRec327[0] = ((dsp->fRec328[2] + (fSlow26 * (fTemp197 + (fSlow27 * dsp->fRec328[0])))) - (fSlow32 * (fTemp198 + (fSlow33 * dsp->fRec327[2]))));
			float fTemp199 = (fSlow41 * dsp->fRec326[1]);
			dsp->fRec326[0] = ((dsp->fRec327[2] + (fSlow32 * (fTemp198 + (fSlow33 * dsp->fRec327[0])))) - (fSlow38 * (fTemp199 + (fSlow39 * dsp->fRec326[2]))));
			dsp->fRec336[0] = ((fSlow18 * dsp->fRec336[1]) + (fSlow19 * (dsp->fRec7[1] + dsp->fRec7[2])));
			dsp->fRec335[0] = (dsp->fRec336[0] - (fSlow15 * ((fSlow21 * dsp->fRec335[1]) + (fSlow22 * dsp->fRec335[2]))));
			float fTemp200 = (dsp->fRec335[2] + (dsp->fRec335[0] + (2.0f * dsp->fRec335[1])));
			float fTemp201 = (fSlow15 * fTemp200);
			dsp->fVec44[0] = fTemp201;
			dsp->fRec334[0] = ((fSlow47 * dsp->fRec334[1]) + (fSlow48 * ((fSlow49 * dsp->fVec44[1]) + (fSlow50 * fTemp200))));
			dsp->fRec333[0] = (dsp->fRec334[0] - (fSlow45 * ((fSlow29 * dsp->fRec333[1]) + (fSlow51 * dsp->fRec333[2]))));
			float fTemp202 = (fSlow35 * dsp->fRec332[1]);
			dsp->fRec332[0] = ((fSlow45 * (((fSlow28 * dsp->fRec333[0]) + (fSlow52 * dsp->fRec333[1])) + (fSlow28 * dsp->fRec333[2]))) - (fSlow32 * (fTemp202 + (fSlow33 * dsp->fRec332[2]))));
			float fTemp203 = (fSlow41 * dsp->fRec331[1]);
			dsp->fRec331[0] = ((dsp->fRec332[2] + (fSlow32 * (fTemp202 + (fSlow33 * dsp->fRec332[0])))) - (fSlow38 * (fTemp203 + (fSlow39 * dsp->fRec331[2]))));
			dsp->fRec341[0] = ((fSlow47 * dsp->fRec341[1]) + (fSlow48 * (dsp->fVec44[1] + fTemp201)));
			dsp->fRec340[0] = (dsp->fRec341[0] - (fSlow45 * ((fSlow29 * dsp->fRec340[1]) + (fSlow51 * dsp->fRec340[2]))));
			float fTemp204 = (dsp->fRec340[2] + (dsp->fRec340[0] + (2.0f * dsp->fRec340[1])));
			float fTemp205 = (fSlow45 * fTemp204);
			dsp->fVec45[0] = fTemp205;
			dsp->fRec339[0] = ((fSlow58 * dsp->fRec339[1]) + (fSlow59 * ((fSlow60 * dsp->fVec45[1]) + (fSlow61 * fTemp204))));
			dsp->fRec338[0] = (dsp->fRec339[0] - (fSlow56 * ((fSlow35 * dsp->fRec338[1]) + (fSlow62 * dsp->fRec338[2]))));
			float fTemp206 = (fSlow41 * dsp->fRec337[1]);
			dsp->fRec337[0] = ((fSlow56 * (((fSlow34 * dsp->fRec338[0]) + (fSlow63 * dsp->fRec338[1])) + (fSlow34 * dsp->fRec338[2]))) - (fSlow38 * (fTemp206 + (fSlow39 * dsp->fRec337[2]))));
			dsp->fRec345[0] = ((fSlow58 * dsp->fRec345[1]) + (fSlow59 * (dsp->fVec45[1] + fTemp205)));
			dsp->fRec344[0] = (dsp->fRec345[0] - (fSlow56 * ((fSlow35 * dsp->fRec344[1]) + (fSlow62 * dsp->fRec344[2]))));
			float fTemp207 = (dsp->fRec344[2] + (dsp->fRec344[0] + (2.0f * dsp->fRec344[1])));
			float fTemp208 = (fSlow56 * fTemp207);
			dsp->fVec46[0] = fTemp208;
			dsp->fRec343[0] = ((fSlow68 * dsp->fRec343[1]) + (fSlow69 * ((fSlow70 * dsp->fVec46[1]) + (fSlow71 * fTemp207))));
			dsp->fRec342[0] = (dsp->fRec343[0] - (fSlow64 * ((fSlow41 * dsp->fRec342[1]) + (fSlow72 * dsp->fRec342[2]))));
			dsp->fRec347[0] = ((fSlow68 * dsp->fRec347[1]) + (fSlow69 * (dsp->fVec46[1] + fTemp208)));
			dsp->fRec346[0] = (dsp->fRec347[0] - (fSlow64 * ((fSlow41 * dsp->fRec346[1]) + (fSlow72 * dsp->fRec346[2]))));
			float fTemp209 = ((((fSlow169 * (dsp->fRec326[2] + (fSlow38 * (fTemp199 + (fSlow39 * dsp->fRec326[0]))))) + (fSlow170 * (dsp->fRec331[2] + (fSlow38 * (fTemp203 + (fSlow39 * dsp->fRec331[0])))))) + (fSlow171 * (dsp->fRec337[2] + (fSlow38 * (fTemp206 + (fSlow39 * dsp->fRec337[0])))))) + (fSlow64 * ((fSlow172 * (((fSlow40 * dsp->fRec342[0]) + (fSlow73 * dsp->fRec342[1])) + (fSlow40 * dsp->fRec342[2]))) + (fSlow173 * (dsp->fRec346[2] + (dsp->fRec346[0] + (2.0f * dsp->fRec346[1])))))));
			dsp->fRec352[0] = ((fSlow18 * dsp->fRec352[1]) + (fSlow19 * ((fSlow13 * dsp->fRec15[1]) + (fSlow20 * dsp->fRec15[2]))));
			dsp->fRec351[0] = (dsp->fRec352[0] - (fSlow15 * ((fSlow21 * dsp->fRec351[1]) + (fSlow22 * dsp->fRec351[2]))));
			float fTemp210 = (fSlow29 * dsp->fRec350[1]);
			dsp->fRec350[0] = ((fSlow15 * (((fSlow16 * dsp->fRec351[0]) + (fSlow23 * dsp->fRec351[1])) + (fSlow16 * dsp->fRec351[2]))) - (fSlow26 * (fTemp210 + (fSlow27 * dsp->fRec350[2]))));
			float fTemp211 = (fSlow35 * dsp->fRec349[1]);
			dsp->fRec349[0] = ((dsp->fRec350[2] + (fSlow26 * (fTemp210 + (fSlow27 * dsp->fRec350[0])))) - (fSlow32 * (fTemp211 + (fSlow33 * dsp->fRec349[2]))));
			float fTemp212 = (fSlow41 * dsp->fRec348[1]);
			dsp->fRec348[0] = ((dsp->fRec349[2] + (fSlow32 * (fTemp211 + (fSlow33 * dsp->fRec349[0])))) - (fSlow38 * (fTemp212 + (fSlow39 * dsp->fRec348[2]))));
			dsp->fRec358[0] = ((fSlow18 * dsp->fRec358[1]) + (fSlow19 * (dsp->fRec15[1] + dsp->fRec15[2])));
			dsp->fRec357[0] = (dsp->fRec358[0] - (fSlow15 * ((fSlow21 * dsp->fRec357[1]) + (fSlow22 * dsp->fRec357[2]))));
			float fTemp213 = (dsp->fRec357[2] + (dsp->fRec357[0] + (2.0f * dsp->fRec357[1])));
			float fTemp214 = (fSlow15 * fTemp213);
			dsp->fVec47[0] = fTemp214;
			dsp->fRec356[0] = ((fSlow47 * dsp->fRec356[1]) + (fSlow48 * ((fSlow49 * dsp->fVec47[1]) + (fSlow50 * fTemp213))));
			dsp->fRec355[0] = (dsp->fRec356[0] - (fSlow45 * ((fSlow29 * dsp->fRec355[1]) + (fSlow51 * dsp->fRec355[2]))));
			float fTemp215 = (fSlow35 * dsp->fRec354[1]);
			dsp->fRec354[0] = ((fSlow45 * (((fSlow28 * dsp->fRec355[0]) + (fSlow52 * dsp->fRec355[1])) + (fSlow28 * dsp->fRec355[2]))) - (fSlow32 * (fTemp215 + (fSlow33 * dsp->fRec354[2]))));
			float fTemp216 = (fSlow41 * dsp->fRec353[1]);
			dsp->fRec353[0] = ((dsp->fRec354[2] + (fSlow32 * (fTemp215 + (fSlow33 * dsp->fRec354[0])))) - (fSlow38 * (fTemp216 + (fSlow39 * dsp->fRec353[2]))));
			dsp->fRec363[0] = ((fSlow47 * dsp->fRec363[1]) + (fSlow48 * (dsp->fVec47[1] + fTemp214)));
			dsp->fRec362[0] = (dsp->fRec363[0] - (fSlow45 * ((fSlow29 * dsp->fRec362[1]) + (fSlow51 * dsp->fRec362[2]))));
			float fTemp217 = (dsp->fRec362[2] + (dsp->fRec362[0] + (2.0f * dsp->fRec362[1])));
			float fTemp218 = (fSlow45 * fTemp217);
			dsp->fVec48[0] = fTemp218;
			dsp->fRec361[0] = ((fSlow58 * dsp->fRec361[1]) + (fSlow59 * ((fSlow60 * dsp->fVec48[1]) + (fSlow61 * fTemp217))));
			dsp->fRec360[0] = (dsp->fRec361[0] - (fSlow56 * ((fSlow35 * dsp->fRec360[1]) + (fSlow62 * dsp->fRec360[2]))));
			float fTemp219 = (fSlow41 * dsp->fRec359[1]);
			dsp->fRec359[0] = ((fSlow56 * (((fSlow34 * dsp->fRec360[0]) + (fSlow63 * dsp->fRec360[1])) + (fSlow34 * dsp->fRec360[2]))) - (fSlow38 * (fTemp219 + (fSlow39 * dsp->fRec359[2]))));
			dsp->fRec367[0] = ((fSlow58 * dsp->fRec367[1]) + (fSlow59 * (dsp->fVec48[1] + fTemp218)));
			dsp->fRec366[0] = (dsp->fRec367[0] - (fSlow56 * ((fSlow35 * dsp->fRec366[1]) + (fSlow62 * dsp->fRec366[2]))));
			float fTemp220 = (dsp->fRec366[2] + (dsp->fRec366[0] + (2.0f * dsp->fRec366[1])));
			float fTemp221 = (fSlow56 * fTemp220);
			dsp->fVec49[0] = fTemp221;
			dsp->fRec365[0] = ((fSlow68 * dsp->fRec365[1]) + (fSlow69 * ((fSlow70 * dsp->fVec49[1]) + (fSlow71 * fTemp220))));
			dsp->fRec364[0] = (dsp->fRec365[0] - (fSlow64 * ((fSlow41 * dsp->fRec364[1]) + (fSlow72 * dsp->fRec364[2]))));
			dsp->fRec369[0] = ((fSlow68 * dsp->fRec369[1]) + (fSlow69 * (dsp->fVec49[1] + fTemp221)));
			dsp->fRec368[0] = (dsp->fRec369[0] - (fSlow64 * ((fSlow41 * dsp->fRec368[1]) + (fSlow72 * dsp->fRec368[2]))));
			float fTemp222 = ((((fSlow176 * (dsp->fRec348[2] + (fSlow38 * (fTemp212 + (fSlow39 * dsp->fRec348[0]))))) + (fSlow177 * (dsp->fRec353[2] + (fSlow38 * (fTemp216 + (fSlow39 * dsp->fRec353[0])))))) + (fSlow178 * (dsp->fRec359[2] + (fSlow38 * (fTemp219 + (fSlow39 * dsp->fRec359[0])))))) + (fSlow64 * ((fSlow179 * (((fSlow40 * dsp->fRec364[0]) + (fSlow73 * dsp->fRec364[1])) + (fSlow40 * dsp->fRec364[2]))) + (fSlow180 * (dsp->fRec368[2] + (dsp->fRec368[0] + (2.0f * dsp->fRec368[1])))))));
			float fTemp223 = (fTemp209 + fTemp222);
			float fTemp224 = (fTemp196 + fTemp223);
			float fTemp225 = (fTemp169 + fTemp224);
			dsp->fVec50[(dsp->IOTA & 16383)] = (fTemp0 + ((float)iTemp1 + ((float)iTemp2 + (fTemp3 + (fSlow5 * (fTemp114 + fTemp225))))));
			dsp->fRec0[0] = dsp->fVec50[((dsp->IOTA - iSlow181) & 16383)];
			dsp->fVec51[0] = fSlow182;
			int iTemp226 = ((fSlow182 - dsp->fVec51[1]) > 0.0f);
			float fTemp227 = ((fSlow4 * (float)input3[i]) + ((float)iTemp1 + fTemp0));
			dsp->fVec52[(dsp->IOTA & 16383)] = ((float)iTemp226 + ((fSlow5 * (fTemp114 - fTemp225)) + fTemp227));
			dsp->fRec1[0] = dsp->fVec52[((dsp->IOTA - iSlow183) & 16383)];
			float fTemp228 = (((float)iTemp1 + (fTemp3 + (float)iTemp2)) + fTemp0);
			float fTemp229 = (fTemp58 - fTemp113);
			float fTemp230 = (fTemp169 - fTemp224);
			dsp->fVec53[(dsp->IOTA & 16383)] = (fTemp228 + (fSlow5 * (fTemp229 + fTemp230)));
			dsp->fRec2[0] = dsp->fVec53[((dsp->IOTA - iSlow184) & 16383)];
			float fTemp231 = ((float)iTemp226 + fTemp227);
			dsp->fVec54[(dsp->IOTA & 16383)] = (fTemp231 + (fSlow5 * (fTemp229 - fTemp230)));
			dsp->fRec3[0] = dsp->fVec54[((dsp->IOTA - iSlow185) & 16383)];
			float fTemp232 = (fTemp30 - fTemp57);
			float fTemp233 = (fTemp85 - fTemp112);
			float fTemp234 = (fTemp232 + fTemp233);
			float fTemp235 = (fTemp141 - fTemp168);
			float fTemp236 = (fTemp196 - fTemp223);
			float fTemp237 = (fTemp235 + fTemp236);
			dsp->fVec55[(dsp->IOTA & 16383)] = (fTemp228 + (fSlow5 * (fTemp234 + fTemp237)));
			dsp->fRec4[0] = dsp->fVec55[((dsp->IOTA - iSlow186) & 16383)];
			dsp->fVec56[(dsp->IOTA & 16383)] = (fTemp231 + (fSlow5 * (fTemp234 - fTemp237)));
			dsp->fRec5[0] = dsp->fVec56[((dsp->IOTA - iSlow187) & 16383)];
			float fTemp238 = (fTemp232 - fTemp233);
			float fTemp239 = (fTemp235 - fTemp236);
			dsp->fVec57[(dsp->IOTA & 16383)] = (fTemp228 + (fSlow5 * (fTemp238 + fTemp239)));
			dsp->fRec6[0] = dsp->fVec57[((dsp->IOTA - iSlow188) & 16383)];
			dsp->fVec58[(dsp->IOTA & 16383)] = (fTemp231 + (fSlow5 * (fTemp238 - fTemp239)));
			dsp->fRec7[0] = dsp->fVec58[((dsp->IOTA - iSlow189) & 16383)];
			float fTemp240 = (fTemp16 - fTemp29);
			float fTemp241 = (fTemp43 - fTemp56);
			float fTemp242 = (fTemp240 + fTemp241);
			float fTemp243 = (fTemp71 - fTemp84);
			float fTemp244 = (fTemp98 - fTemp111);
			float fTemp245 = (fTemp243 + fTemp244);
			float fTemp246 = (fTemp242 + fTemp245);
			float fTemp247 = (fTemp127 - fTemp140);
			float fTemp248 = (fTemp154 - fTemp167);
			float fTemp249 = (fTemp247 + fTemp248);
			float fTemp250 = (fTemp209 - fTemp222);
			float fTemp251 = (fTemp182 - fTemp195);
			float fTemp252 = (fTemp250 + fTemp251);
			float fTemp253 = (fTemp249 + fTemp252);
			dsp->fVec59[(dsp->IOTA & 16383)] = (fTemp228 + (fSlow5 * (fTemp246 + fTemp253)));
			dsp->fRec8[0] = dsp->fVec59[((dsp->IOTA - iSlow190) & 16383)];
			dsp->fVec60[(dsp->IOTA & 16383)] = (fTemp231 + (fSlow5 * (fTemp246 - fTemp253)));
			dsp->fRec9[0] = dsp->fVec60[((dsp->IOTA - iSlow191) & 16383)];
			float fTemp254 = (fTemp242 - fTemp245);
			float fTemp255 = (fTemp249 - fTemp252);
			dsp->fVec61[(dsp->IOTA & 16383)] = (fTemp228 + (fSlow5 * (fTemp254 + fTemp255)));
			dsp->fRec10[0] = dsp->fVec61[((dsp->IOTA - iSlow192) & 16383)];
			dsp->fVec62[(dsp->IOTA & 16383)] = (fTemp231 + (fSlow5 * (fTemp254 - fTemp255)));
			dsp->fRec11[0] = dsp->fVec62[((dsp->IOTA - iSlow193) & 16383)];
			float fTemp256 = (fTemp240 - fTemp241);
			float fTemp257 = (fTemp243 - fTemp244);
			float fTemp258 = (fTemp256 + fTemp257);
			float fTemp259 = (fTemp247 - fTemp248);
			float fTemp260 = (fTemp251 - fTemp250);
			float fTemp261 = (fTemp259 + fTemp260);
			dsp->fVec63[(dsp->IOTA & 16383)] = (fTemp228 + (fSlow5 * (fTemp258 + fTemp261)));
			dsp->fRec12[0] = dsp->fVec63[((dsp->IOTA - iSlow194) & 16383)];
			dsp->fVec64[(dsp->IOTA & 16383)] = (fTemp231 + (fSlow5 * (fTemp258 - fTemp261)));
			dsp->fRec13[0] = dsp->fVec64[((dsp->IOTA - iSlow195) & 16383)];
			float fTemp262 = (fTemp256 - fTemp257);
			float fTemp263 = (fTemp259 - fTemp260);
			dsp->fVec65[(dsp->IOTA & 16383)] = (fTemp228 + (fSlow5 * (fTemp262 + fTemp263)));
			dsp->fRec14[0] = dsp->fVec65[((dsp->IOTA - iSlow196) & 16383)];
			dsp->fVec66[(dsp->IOTA & 16383)] = (fTemp231 + (fSlow5 * (fTemp262 - fTemp263)));
			dsp->fRec15[0] = dsp->fVec66[((dsp->IOTA - iSlow197) & 16383)];
			output0[i] = (FAUSTFLOAT)(fSlow0 * (((((((dsp->fRec0[0] + dsp->fRec2[0]) + dsp->fRec4[0]) + dsp->fRec6[0]) + dsp->fRec8[0]) + dsp->fRec10[0]) + dsp->fRec12[0]) + dsp->fRec14[0]));
			output1[i] = (FAUSTFLOAT)(fSlow0 * (((((((dsp->fRec1[0] + dsp->fRec3[0]) + dsp->fRec5[0]) + dsp->fRec7[0]) + dsp->fRec9[0]) + dsp->fRec11[0]) + dsp->fRec13[0]) + dsp->fRec15[0]));
			dsp->iRec17[1] = dsp->iRec17[0];
			/* C99 loop */
			{
				int j0;
				for (j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
					dsp->fRec16[j0] = dsp->fRec16[(j0 - 1)];
					
				}
				
			}
			dsp->fVec0[1] = dsp->fVec0[0];
			dsp->fVec1[1] = dsp->fVec1[0];
			dsp->fRec22[1] = dsp->fRec22[0];
			dsp->fRec21[2] = dsp->fRec21[1];
			dsp->fRec21[1] = dsp->fRec21[0];
			dsp->fRec20[2] = dsp->fRec20[1];
			dsp->fRec20[1] = dsp->fRec20[0];
			dsp->fRec19[2] = dsp->fRec19[1];
			dsp->fRec19[1] = dsp->fRec19[0];
			dsp->fRec18[2] = dsp->fRec18[1];
			dsp->fRec18[1] = dsp->fRec18[0];
			dsp->fRec28[1] = dsp->fRec28[0];
			dsp->fRec27[2] = dsp->fRec27[1];
			dsp->fRec27[1] = dsp->fRec27[0];
			dsp->fVec2[1] = dsp->fVec2[0];
			dsp->fRec26[1] = dsp->fRec26[0];
			dsp->fRec25[2] = dsp->fRec25[1];
			dsp->fRec25[1] = dsp->fRec25[0];
			dsp->fRec24[2] = dsp->fRec24[1];
			dsp->fRec24[1] = dsp->fRec24[0];
			dsp->fRec23[2] = dsp->fRec23[1];
			dsp->fRec23[1] = dsp->fRec23[0];
			dsp->fRec33[1] = dsp->fRec33[0];
			dsp->fRec32[2] = dsp->fRec32[1];
			dsp->fRec32[1] = dsp->fRec32[0];
			dsp->fVec3[1] = dsp->fVec3[0];
			dsp->fRec31[1] = dsp->fRec31[0];
			dsp->fRec30[2] = dsp->fRec30[1];
			dsp->fRec30[1] = dsp->fRec30[0];
			dsp->fRec29[2] = dsp->fRec29[1];
			dsp->fRec29[1] = dsp->fRec29[0];
			dsp->fRec37[1] = dsp->fRec37[0];
			dsp->fRec36[2] = dsp->fRec36[1];
			dsp->fRec36[1] = dsp->fRec36[0];
			dsp->fVec4[1] = dsp->fVec4[0];
			dsp->fRec35[1] = dsp->fRec35[0];
			dsp->fRec34[2] = dsp->fRec34[1];
			dsp->fRec34[1] = dsp->fRec34[0];
			dsp->fRec39[1] = dsp->fRec39[0];
			dsp->fRec38[2] = dsp->fRec38[1];
			dsp->fRec38[1] = dsp->fRec38[0];
			dsp->fRec44[1] = dsp->fRec44[0];
			dsp->fRec43[2] = dsp->fRec43[1];
			dsp->fRec43[1] = dsp->fRec43[0];
			dsp->fRec42[2] = dsp->fRec42[1];
			dsp->fRec42[1] = dsp->fRec42[0];
			dsp->fRec41[2] = dsp->fRec41[1];
			dsp->fRec41[1] = dsp->fRec41[0];
			dsp->fRec40[2] = dsp->fRec40[1];
			dsp->fRec40[1] = dsp->fRec40[0];
			dsp->fRec50[1] = dsp->fRec50[0];
			dsp->fRec49[2] = dsp->fRec49[1];
			dsp->fRec49[1] = dsp->fRec49[0];
			dsp->fVec5[1] = dsp->fVec5[0];
			dsp->fRec48[1] = dsp->fRec48[0];
			dsp->fRec47[2] = dsp->fRec47[1];
			dsp->fRec47[1] = dsp->fRec47[0];
			dsp->fRec46[2] = dsp->fRec46[1];
			dsp->fRec46[1] = dsp->fRec46[0];
			dsp->fRec45[2] = dsp->fRec45[1];
			dsp->fRec45[1] = dsp->fRec45[0];
			dsp->fRec55[1] = dsp->fRec55[0];
			dsp->fRec54[2] = dsp->fRec54[1];
			dsp->fRec54[1] = dsp->fRec54[0];
			dsp->fVec6[1] = dsp->fVec6[0];
			dsp->fRec53[1] = dsp->fRec53[0];
			dsp->fRec52[2] = dsp->fRec52[1];
			dsp->fRec52[1] = dsp->fRec52[0];
			dsp->fRec51[2] = dsp->fRec51[1];
			dsp->fRec51[1] = dsp->fRec51[0];
			dsp->fRec59[1] = dsp->fRec59[0];
			dsp->fRec58[2] = dsp->fRec58[1];
			dsp->fRec58[1] = dsp->fRec58[0];
			dsp->fVec7[1] = dsp->fVec7[0];
			dsp->fRec57[1] = dsp->fRec57[0];
			dsp->fRec56[2] = dsp->fRec56[1];
			dsp->fRec56[1] = dsp->fRec56[0];
			dsp->fRec61[1] = dsp->fRec61[0];
			dsp->fRec60[2] = dsp->fRec60[1];
			dsp->fRec60[1] = dsp->fRec60[0];
			dsp->fRec66[1] = dsp->fRec66[0];
			dsp->fRec65[2] = dsp->fRec65[1];
			dsp->fRec65[1] = dsp->fRec65[0];
			dsp->fRec64[2] = dsp->fRec64[1];
			dsp->fRec64[1] = dsp->fRec64[0];
			dsp->fRec63[2] = dsp->fRec63[1];
			dsp->fRec63[1] = dsp->fRec63[0];
			dsp->fRec62[2] = dsp->fRec62[1];
			dsp->fRec62[1] = dsp->fRec62[0];
			dsp->fRec72[1] = dsp->fRec72[0];
			dsp->fRec71[2] = dsp->fRec71[1];
			dsp->fRec71[1] = dsp->fRec71[0];
			dsp->fVec8[1] = dsp->fVec8[0];
			dsp->fRec70[1] = dsp->fRec70[0];
			dsp->fRec69[2] = dsp->fRec69[1];
			dsp->fRec69[1] = dsp->fRec69[0];
			dsp->fRec68[2] = dsp->fRec68[1];
			dsp->fRec68[1] = dsp->fRec68[0];
			dsp->fRec67[2] = dsp->fRec67[1];
			dsp->fRec67[1] = dsp->fRec67[0];
			dsp->fRec77[1] = dsp->fRec77[0];
			dsp->fRec76[2] = dsp->fRec76[1];
			dsp->fRec76[1] = dsp->fRec76[0];
			dsp->fVec9[1] = dsp->fVec9[0];
			dsp->fRec75[1] = dsp->fRec75[0];
			dsp->fRec74[2] = dsp->fRec74[1];
			dsp->fRec74[1] = dsp->fRec74[0];
			dsp->fRec73[2] = dsp->fRec73[1];
			dsp->fRec73[1] = dsp->fRec73[0];
			dsp->fRec81[1] = dsp->fRec81[0];
			dsp->fRec80[2] = dsp->fRec80[1];
			dsp->fRec80[1] = dsp->fRec80[0];
			dsp->fVec10[1] = dsp->fVec10[0];
			dsp->fRec79[1] = dsp->fRec79[0];
			dsp->fRec78[2] = dsp->fRec78[1];
			dsp->fRec78[1] = dsp->fRec78[0];
			dsp->fRec83[1] = dsp->fRec83[0];
			dsp->fRec82[2] = dsp->fRec82[1];
			dsp->fRec82[1] = dsp->fRec82[0];
			dsp->fRec88[1] = dsp->fRec88[0];
			dsp->fRec87[2] = dsp->fRec87[1];
			dsp->fRec87[1] = dsp->fRec87[0];
			dsp->fRec86[2] = dsp->fRec86[1];
			dsp->fRec86[1] = dsp->fRec86[0];
			dsp->fRec85[2] = dsp->fRec85[1];
			dsp->fRec85[1] = dsp->fRec85[0];
			dsp->fRec84[2] = dsp->fRec84[1];
			dsp->fRec84[1] = dsp->fRec84[0];
			dsp->fRec94[1] = dsp->fRec94[0];
			dsp->fRec93[2] = dsp->fRec93[1];
			dsp->fRec93[1] = dsp->fRec93[0];
			dsp->fVec11[1] = dsp->fVec11[0];
			dsp->fRec92[1] = dsp->fRec92[0];
			dsp->fRec91[2] = dsp->fRec91[1];
			dsp->fRec91[1] = dsp->fRec91[0];
			dsp->fRec90[2] = dsp->fRec90[1];
			dsp->fRec90[1] = dsp->fRec90[0];
			dsp->fRec89[2] = dsp->fRec89[1];
			dsp->fRec89[1] = dsp->fRec89[0];
			dsp->fRec99[1] = dsp->fRec99[0];
			dsp->fRec98[2] = dsp->fRec98[1];
			dsp->fRec98[1] = dsp->fRec98[0];
			dsp->fVec12[1] = dsp->fVec12[0];
			dsp->fRec97[1] = dsp->fRec97[0];
			dsp->fRec96[2] = dsp->fRec96[1];
			dsp->fRec96[1] = dsp->fRec96[0];
			dsp->fRec95[2] = dsp->fRec95[1];
			dsp->fRec95[1] = dsp->fRec95[0];
			dsp->fRec103[1] = dsp->fRec103[0];
			dsp->fRec102[2] = dsp->fRec102[1];
			dsp->fRec102[1] = dsp->fRec102[0];
			dsp->fVec13[1] = dsp->fVec13[0];
			dsp->fRec101[1] = dsp->fRec101[0];
			dsp->fRec100[2] = dsp->fRec100[1];
			dsp->fRec100[1] = dsp->fRec100[0];
			dsp->fRec105[1] = dsp->fRec105[0];
			dsp->fRec104[2] = dsp->fRec104[1];
			dsp->fRec104[1] = dsp->fRec104[0];
			dsp->fRec110[1] = dsp->fRec110[0];
			dsp->fRec109[2] = dsp->fRec109[1];
			dsp->fRec109[1] = dsp->fRec109[0];
			dsp->fRec108[2] = dsp->fRec108[1];
			dsp->fRec108[1] = dsp->fRec108[0];
			dsp->fRec107[2] = dsp->fRec107[1];
			dsp->fRec107[1] = dsp->fRec107[0];
			dsp->fRec106[2] = dsp->fRec106[1];
			dsp->fRec106[1] = dsp->fRec106[0];
			dsp->fRec116[1] = dsp->fRec116[0];
			dsp->fRec115[2] = dsp->fRec115[1];
			dsp->fRec115[1] = dsp->fRec115[0];
			dsp->fVec14[1] = dsp->fVec14[0];
			dsp->fRec114[1] = dsp->fRec114[0];
			dsp->fRec113[2] = dsp->fRec113[1];
			dsp->fRec113[1] = dsp->fRec113[0];
			dsp->fRec112[2] = dsp->fRec112[1];
			dsp->fRec112[1] = dsp->fRec112[0];
			dsp->fRec111[2] = dsp->fRec111[1];
			dsp->fRec111[1] = dsp->fRec111[0];
			dsp->fRec121[1] = dsp->fRec121[0];
			dsp->fRec120[2] = dsp->fRec120[1];
			dsp->fRec120[1] = dsp->fRec120[0];
			dsp->fVec15[1] = dsp->fVec15[0];
			dsp->fRec119[1] = dsp->fRec119[0];
			dsp->fRec118[2] = dsp->fRec118[1];
			dsp->fRec118[1] = dsp->fRec118[0];
			dsp->fRec117[2] = dsp->fRec117[1];
			dsp->fRec117[1] = dsp->fRec117[0];
			dsp->fRec125[1] = dsp->fRec125[0];
			dsp->fRec124[2] = dsp->fRec124[1];
			dsp->fRec124[1] = dsp->fRec124[0];
			dsp->fVec16[1] = dsp->fVec16[0];
			dsp->fRec123[1] = dsp->fRec123[0];
			dsp->fRec122[2] = dsp->fRec122[1];
			dsp->fRec122[1] = dsp->fRec122[0];
			dsp->fRec127[1] = dsp->fRec127[0];
			dsp->fRec126[2] = dsp->fRec126[1];
			dsp->fRec126[1] = dsp->fRec126[0];
			dsp->fRec132[1] = dsp->fRec132[0];
			dsp->fRec131[2] = dsp->fRec131[1];
			dsp->fRec131[1] = dsp->fRec131[0];
			dsp->fRec130[2] = dsp->fRec130[1];
			dsp->fRec130[1] = dsp->fRec130[0];
			dsp->fRec129[2] = dsp->fRec129[1];
			dsp->fRec129[1] = dsp->fRec129[0];
			dsp->fRec128[2] = dsp->fRec128[1];
			dsp->fRec128[1] = dsp->fRec128[0];
			dsp->fRec138[1] = dsp->fRec138[0];
			dsp->fRec137[2] = dsp->fRec137[1];
			dsp->fRec137[1] = dsp->fRec137[0];
			dsp->fVec17[1] = dsp->fVec17[0];
			dsp->fRec136[1] = dsp->fRec136[0];
			dsp->fRec135[2] = dsp->fRec135[1];
			dsp->fRec135[1] = dsp->fRec135[0];
			dsp->fRec134[2] = dsp->fRec134[1];
			dsp->fRec134[1] = dsp->fRec134[0];
			dsp->fRec133[2] = dsp->fRec133[1];
			dsp->fRec133[1] = dsp->fRec133[0];
			dsp->fRec143[1] = dsp->fRec143[0];
			dsp->fRec142[2] = dsp->fRec142[1];
			dsp->fRec142[1] = dsp->fRec142[0];
			dsp->fVec18[1] = dsp->fVec18[0];
			dsp->fRec141[1] = dsp->fRec141[0];
			dsp->fRec140[2] = dsp->fRec140[1];
			dsp->fRec140[1] = dsp->fRec140[0];
			dsp->fRec139[2] = dsp->fRec139[1];
			dsp->fRec139[1] = dsp->fRec139[0];
			dsp->fRec147[1] = dsp->fRec147[0];
			dsp->fRec146[2] = dsp->fRec146[1];
			dsp->fRec146[1] = dsp->fRec146[0];
			dsp->fVec19[1] = dsp->fVec19[0];
			dsp->fRec145[1] = dsp->fRec145[0];
			dsp->fRec144[2] = dsp->fRec144[1];
			dsp->fRec144[1] = dsp->fRec144[0];
			dsp->fRec149[1] = dsp->fRec149[0];
			dsp->fRec148[2] = dsp->fRec148[1];
			dsp->fRec148[1] = dsp->fRec148[0];
			dsp->fRec154[1] = dsp->fRec154[0];
			dsp->fRec153[2] = dsp->fRec153[1];
			dsp->fRec153[1] = dsp->fRec153[0];
			dsp->fRec152[2] = dsp->fRec152[1];
			dsp->fRec152[1] = dsp->fRec152[0];
			dsp->fRec151[2] = dsp->fRec151[1];
			dsp->fRec151[1] = dsp->fRec151[0];
			dsp->fRec150[2] = dsp->fRec150[1];
			dsp->fRec150[1] = dsp->fRec150[0];
			dsp->fRec160[1] = dsp->fRec160[0];
			dsp->fRec159[2] = dsp->fRec159[1];
			dsp->fRec159[1] = dsp->fRec159[0];
			dsp->fVec20[1] = dsp->fVec20[0];
			dsp->fRec158[1] = dsp->fRec158[0];
			dsp->fRec157[2] = dsp->fRec157[1];
			dsp->fRec157[1] = dsp->fRec157[0];
			dsp->fRec156[2] = dsp->fRec156[1];
			dsp->fRec156[1] = dsp->fRec156[0];
			dsp->fRec155[2] = dsp->fRec155[1];
			dsp->fRec155[1] = dsp->fRec155[0];
			dsp->fRec165[1] = dsp->fRec165[0];
			dsp->fRec164[2] = dsp->fRec164[1];
			dsp->fRec164[1] = dsp->fRec164[0];
			dsp->fVec21[1] = dsp->fVec21[0];
			dsp->fRec163[1] = dsp->fRec163[0];
			dsp->fRec162[2] = dsp->fRec162[1];
			dsp->fRec162[1] = dsp->fRec162[0];
			dsp->fRec161[2] = dsp->fRec161[1];
			dsp->fRec161[1] = dsp->fRec161[0];
			dsp->fRec169[1] = dsp->fRec169[0];
			dsp->fRec168[2] = dsp->fRec168[1];
			dsp->fRec168[1] = dsp->fRec168[0];
			dsp->fVec22[1] = dsp->fVec22[0];
			dsp->fRec167[1] = dsp->fRec167[0];
			dsp->fRec166[2] = dsp->fRec166[1];
			dsp->fRec166[1] = dsp->fRec166[0];
			dsp->fRec171[1] = dsp->fRec171[0];
			dsp->fRec170[2] = dsp->fRec170[1];
			dsp->fRec170[1] = dsp->fRec170[0];
			dsp->fRec176[1] = dsp->fRec176[0];
			dsp->fRec175[2] = dsp->fRec175[1];
			dsp->fRec175[1] = dsp->fRec175[0];
			dsp->fRec174[2] = dsp->fRec174[1];
			dsp->fRec174[1] = dsp->fRec174[0];
			dsp->fRec173[2] = dsp->fRec173[1];
			dsp->fRec173[1] = dsp->fRec173[0];
			dsp->fRec172[2] = dsp->fRec172[1];
			dsp->fRec172[1] = dsp->fRec172[0];
			dsp->fRec182[1] = dsp->fRec182[0];
			dsp->fRec181[2] = dsp->fRec181[1];
			dsp->fRec181[1] = dsp->fRec181[0];
			dsp->fVec23[1] = dsp->fVec23[0];
			dsp->fRec180[1] = dsp->fRec180[0];
			dsp->fRec179[2] = dsp->fRec179[1];
			dsp->fRec179[1] = dsp->fRec179[0];
			dsp->fRec178[2] = dsp->fRec178[1];
			dsp->fRec178[1] = dsp->fRec178[0];
			dsp->fRec177[2] = dsp->fRec177[1];
			dsp->fRec177[1] = dsp->fRec177[0];
			dsp->fRec187[1] = dsp->fRec187[0];
			dsp->fRec186[2] = dsp->fRec186[1];
			dsp->fRec186[1] = dsp->fRec186[0];
			dsp->fVec24[1] = dsp->fVec24[0];
			dsp->fRec185[1] = dsp->fRec185[0];
			dsp->fRec184[2] = dsp->fRec184[1];
			dsp->fRec184[1] = dsp->fRec184[0];
			dsp->fRec183[2] = dsp->fRec183[1];
			dsp->fRec183[1] = dsp->fRec183[0];
			dsp->fRec191[1] = dsp->fRec191[0];
			dsp->fRec190[2] = dsp->fRec190[1];
			dsp->fRec190[1] = dsp->fRec190[0];
			dsp->fVec25[1] = dsp->fVec25[0];
			dsp->fRec189[1] = dsp->fRec189[0];
			dsp->fRec188[2] = dsp->fRec188[1];
			dsp->fRec188[1] = dsp->fRec188[0];
			dsp->fRec193[1] = dsp->fRec193[0];
			dsp->fRec192[2] = dsp->fRec192[1];
			dsp->fRec192[1] = dsp->fRec192[0];
			dsp->fRec198[1] = dsp->fRec198[0];
			dsp->fRec197[2] = dsp->fRec197[1];
			dsp->fRec197[1] = dsp->fRec197[0];
			dsp->fRec196[2] = dsp->fRec196[1];
			dsp->fRec196[1] = dsp->fRec196[0];
			dsp->fRec195[2] = dsp->fRec195[1];
			dsp->fRec195[1] = dsp->fRec195[0];
			dsp->fRec194[2] = dsp->fRec194[1];
			dsp->fRec194[1] = dsp->fRec194[0];
			dsp->fRec204[1] = dsp->fRec204[0];
			dsp->fRec203[2] = dsp->fRec203[1];
			dsp->fRec203[1] = dsp->fRec203[0];
			dsp->fVec26[1] = dsp->fVec26[0];
			dsp->fRec202[1] = dsp->fRec202[0];
			dsp->fRec201[2] = dsp->fRec201[1];
			dsp->fRec201[1] = dsp->fRec201[0];
			dsp->fRec200[2] = dsp->fRec200[1];
			dsp->fRec200[1] = dsp->fRec200[0];
			dsp->fRec199[2] = dsp->fRec199[1];
			dsp->fRec199[1] = dsp->fRec199[0];
			dsp->fRec209[1] = dsp->fRec209[0];
			dsp->fRec208[2] = dsp->fRec208[1];
			dsp->fRec208[1] = dsp->fRec208[0];
			dsp->fVec27[1] = dsp->fVec27[0];
			dsp->fRec207[1] = dsp->fRec207[0];
			dsp->fRec206[2] = dsp->fRec206[1];
			dsp->fRec206[1] = dsp->fRec206[0];
			dsp->fRec205[2] = dsp->fRec205[1];
			dsp->fRec205[1] = dsp->fRec205[0];
			dsp->fRec213[1] = dsp->fRec213[0];
			dsp->fRec212[2] = dsp->fRec212[1];
			dsp->fRec212[1] = dsp->fRec212[0];
			dsp->fVec28[1] = dsp->fVec28[0];
			dsp->fRec211[1] = dsp->fRec211[0];
			dsp->fRec210[2] = dsp->fRec210[1];
			dsp->fRec210[1] = dsp->fRec210[0];
			dsp->fRec215[1] = dsp->fRec215[0];
			dsp->fRec214[2] = dsp->fRec214[1];
			dsp->fRec214[1] = dsp->fRec214[0];
			dsp->fRec220[1] = dsp->fRec220[0];
			dsp->fRec219[2] = dsp->fRec219[1];
			dsp->fRec219[1] = dsp->fRec219[0];
			dsp->fRec218[2] = dsp->fRec218[1];
			dsp->fRec218[1] = dsp->fRec218[0];
			dsp->fRec217[2] = dsp->fRec217[1];
			dsp->fRec217[1] = dsp->fRec217[0];
			dsp->fRec216[2] = dsp->fRec216[1];
			dsp->fRec216[1] = dsp->fRec216[0];
			dsp->fRec226[1] = dsp->fRec226[0];
			dsp->fRec225[2] = dsp->fRec225[1];
			dsp->fRec225[1] = dsp->fRec225[0];
			dsp->fVec29[1] = dsp->fVec29[0];
			dsp->fRec224[1] = dsp->fRec224[0];
			dsp->fRec223[2] = dsp->fRec223[1];
			dsp->fRec223[1] = dsp->fRec223[0];
			dsp->fRec222[2] = dsp->fRec222[1];
			dsp->fRec222[1] = dsp->fRec222[0];
			dsp->fRec221[2] = dsp->fRec221[1];
			dsp->fRec221[1] = dsp->fRec221[0];
			dsp->fRec231[1] = dsp->fRec231[0];
			dsp->fRec230[2] = dsp->fRec230[1];
			dsp->fRec230[1] = dsp->fRec230[0];
			dsp->fVec30[1] = dsp->fVec30[0];
			dsp->fRec229[1] = dsp->fRec229[0];
			dsp->fRec228[2] = dsp->fRec228[1];
			dsp->fRec228[1] = dsp->fRec228[0];
			dsp->fRec227[2] = dsp->fRec227[1];
			dsp->fRec227[1] = dsp->fRec227[0];
			dsp->fRec235[1] = dsp->fRec235[0];
			dsp->fRec234[2] = dsp->fRec234[1];
			dsp->fRec234[1] = dsp->fRec234[0];
			dsp->fVec31[1] = dsp->fVec31[0];
			dsp->fRec233[1] = dsp->fRec233[0];
			dsp->fRec232[2] = dsp->fRec232[1];
			dsp->fRec232[1] = dsp->fRec232[0];
			dsp->fRec237[1] = dsp->fRec237[0];
			dsp->fRec236[2] = dsp->fRec236[1];
			dsp->fRec236[1] = dsp->fRec236[0];
			dsp->fRec242[1] = dsp->fRec242[0];
			dsp->fRec241[2] = dsp->fRec241[1];
			dsp->fRec241[1] = dsp->fRec241[0];
			dsp->fRec240[2] = dsp->fRec240[1];
			dsp->fRec240[1] = dsp->fRec240[0];
			dsp->fRec239[2] = dsp->fRec239[1];
			dsp->fRec239[1] = dsp->fRec239[0];
			dsp->fRec238[2] = dsp->fRec238[1];
			dsp->fRec238[1] = dsp->fRec238[0];
			dsp->fRec248[1] = dsp->fRec248[0];
			dsp->fRec247[2] = dsp->fRec247[1];
			dsp->fRec247[1] = dsp->fRec247[0];
			dsp->fVec32[1] = dsp->fVec32[0];
			dsp->fRec246[1] = dsp->fRec246[0];
			dsp->fRec245[2] = dsp->fRec245[1];
			dsp->fRec245[1] = dsp->fRec245[0];
			dsp->fRec244[2] = dsp->fRec244[1];
			dsp->fRec244[1] = dsp->fRec244[0];
			dsp->fRec243[2] = dsp->fRec243[1];
			dsp->fRec243[1] = dsp->fRec243[0];
			dsp->fRec253[1] = dsp->fRec253[0];
			dsp->fRec252[2] = dsp->fRec252[1];
			dsp->fRec252[1] = dsp->fRec252[0];
			dsp->fVec33[1] = dsp->fVec33[0];
			dsp->fRec251[1] = dsp->fRec251[0];
			dsp->fRec250[2] = dsp->fRec250[1];
			dsp->fRec250[1] = dsp->fRec250[0];
			dsp->fRec249[2] = dsp->fRec249[1];
			dsp->fRec249[1] = dsp->fRec249[0];
			dsp->fRec257[1] = dsp->fRec257[0];
			dsp->fRec256[2] = dsp->fRec256[1];
			dsp->fRec256[1] = dsp->fRec256[0];
			dsp->fVec34[1] = dsp->fVec34[0];
			dsp->fRec255[1] = dsp->fRec255[0];
			dsp->fRec254[2] = dsp->fRec254[1];
			dsp->fRec254[1] = dsp->fRec254[0];
			dsp->fRec259[1] = dsp->fRec259[0];
			dsp->fRec258[2] = dsp->fRec258[1];
			dsp->fRec258[1] = dsp->fRec258[0];
			dsp->fRec264[1] = dsp->fRec264[0];
			dsp->fRec263[2] = dsp->fRec263[1];
			dsp->fRec263[1] = dsp->fRec263[0];
			dsp->fRec262[2] = dsp->fRec262[1];
			dsp->fRec262[1] = dsp->fRec262[0];
			dsp->fRec261[2] = dsp->fRec261[1];
			dsp->fRec261[1] = dsp->fRec261[0];
			dsp->fRec260[2] = dsp->fRec260[1];
			dsp->fRec260[1] = dsp->fRec260[0];
			dsp->fRec270[1] = dsp->fRec270[0];
			dsp->fRec269[2] = dsp->fRec269[1];
			dsp->fRec269[1] = dsp->fRec269[0];
			dsp->fVec35[1] = dsp->fVec35[0];
			dsp->fRec268[1] = dsp->fRec268[0];
			dsp->fRec267[2] = dsp->fRec267[1];
			dsp->fRec267[1] = dsp->fRec267[0];
			dsp->fRec266[2] = dsp->fRec266[1];
			dsp->fRec266[1] = dsp->fRec266[0];
			dsp->fRec265[2] = dsp->fRec265[1];
			dsp->fRec265[1] = dsp->fRec265[0];
			dsp->fRec275[1] = dsp->fRec275[0];
			dsp->fRec274[2] = dsp->fRec274[1];
			dsp->fRec274[1] = dsp->fRec274[0];
			dsp->fVec36[1] = dsp->fVec36[0];
			dsp->fRec273[1] = dsp->fRec273[0];
			dsp->fRec272[2] = dsp->fRec272[1];
			dsp->fRec272[1] = dsp->fRec272[0];
			dsp->fRec271[2] = dsp->fRec271[1];
			dsp->fRec271[1] = dsp->fRec271[0];
			dsp->fRec279[1] = dsp->fRec279[0];
			dsp->fRec278[2] = dsp->fRec278[1];
			dsp->fRec278[1] = dsp->fRec278[0];
			dsp->fVec37[1] = dsp->fVec37[0];
			dsp->fRec277[1] = dsp->fRec277[0];
			dsp->fRec276[2] = dsp->fRec276[1];
			dsp->fRec276[1] = dsp->fRec276[0];
			dsp->fRec281[1] = dsp->fRec281[0];
			dsp->fRec280[2] = dsp->fRec280[1];
			dsp->fRec280[1] = dsp->fRec280[0];
			dsp->fRec286[1] = dsp->fRec286[0];
			dsp->fRec285[2] = dsp->fRec285[1];
			dsp->fRec285[1] = dsp->fRec285[0];
			dsp->fRec284[2] = dsp->fRec284[1];
			dsp->fRec284[1] = dsp->fRec284[0];
			dsp->fRec283[2] = dsp->fRec283[1];
			dsp->fRec283[1] = dsp->fRec283[0];
			dsp->fRec282[2] = dsp->fRec282[1];
			dsp->fRec282[1] = dsp->fRec282[0];
			dsp->fRec292[1] = dsp->fRec292[0];
			dsp->fRec291[2] = dsp->fRec291[1];
			dsp->fRec291[1] = dsp->fRec291[0];
			dsp->fVec38[1] = dsp->fVec38[0];
			dsp->fRec290[1] = dsp->fRec290[0];
			dsp->fRec289[2] = dsp->fRec289[1];
			dsp->fRec289[1] = dsp->fRec289[0];
			dsp->fRec288[2] = dsp->fRec288[1];
			dsp->fRec288[1] = dsp->fRec288[0];
			dsp->fRec287[2] = dsp->fRec287[1];
			dsp->fRec287[1] = dsp->fRec287[0];
			dsp->fRec297[1] = dsp->fRec297[0];
			dsp->fRec296[2] = dsp->fRec296[1];
			dsp->fRec296[1] = dsp->fRec296[0];
			dsp->fVec39[1] = dsp->fVec39[0];
			dsp->fRec295[1] = dsp->fRec295[0];
			dsp->fRec294[2] = dsp->fRec294[1];
			dsp->fRec294[1] = dsp->fRec294[0];
			dsp->fRec293[2] = dsp->fRec293[1];
			dsp->fRec293[1] = dsp->fRec293[0];
			dsp->fRec301[1] = dsp->fRec301[0];
			dsp->fRec300[2] = dsp->fRec300[1];
			dsp->fRec300[1] = dsp->fRec300[0];
			dsp->fVec40[1] = dsp->fVec40[0];
			dsp->fRec299[1] = dsp->fRec299[0];
			dsp->fRec298[2] = dsp->fRec298[1];
			dsp->fRec298[1] = dsp->fRec298[0];
			dsp->fRec303[1] = dsp->fRec303[0];
			dsp->fRec302[2] = dsp->fRec302[1];
			dsp->fRec302[1] = dsp->fRec302[0];
			dsp->fRec308[1] = dsp->fRec308[0];
			dsp->fRec307[2] = dsp->fRec307[1];
			dsp->fRec307[1] = dsp->fRec307[0];
			dsp->fRec306[2] = dsp->fRec306[1];
			dsp->fRec306[1] = dsp->fRec306[0];
			dsp->fRec305[2] = dsp->fRec305[1];
			dsp->fRec305[1] = dsp->fRec305[0];
			dsp->fRec304[2] = dsp->fRec304[1];
			dsp->fRec304[1] = dsp->fRec304[0];
			dsp->fRec314[1] = dsp->fRec314[0];
			dsp->fRec313[2] = dsp->fRec313[1];
			dsp->fRec313[1] = dsp->fRec313[0];
			dsp->fVec41[1] = dsp->fVec41[0];
			dsp->fRec312[1] = dsp->fRec312[0];
			dsp->fRec311[2] = dsp->fRec311[1];
			dsp->fRec311[1] = dsp->fRec311[0];
			dsp->fRec310[2] = dsp->fRec310[1];
			dsp->fRec310[1] = dsp->fRec310[0];
			dsp->fRec309[2] = dsp->fRec309[1];
			dsp->fRec309[1] = dsp->fRec309[0];
			dsp->fRec319[1] = dsp->fRec319[0];
			dsp->fRec318[2] = dsp->fRec318[1];
			dsp->fRec318[1] = dsp->fRec318[0];
			dsp->fVec42[1] = dsp->fVec42[0];
			dsp->fRec317[1] = dsp->fRec317[0];
			dsp->fRec316[2] = dsp->fRec316[1];
			dsp->fRec316[1] = dsp->fRec316[0];
			dsp->fRec315[2] = dsp->fRec315[1];
			dsp->fRec315[1] = dsp->fRec315[0];
			dsp->fRec323[1] = dsp->fRec323[0];
			dsp->fRec322[2] = dsp->fRec322[1];
			dsp->fRec322[1] = dsp->fRec322[0];
			dsp->fVec43[1] = dsp->fVec43[0];
			dsp->fRec321[1] = dsp->fRec321[0];
			dsp->fRec320[2] = dsp->fRec320[1];
			dsp->fRec320[1] = dsp->fRec320[0];
			dsp->fRec325[1] = dsp->fRec325[0];
			dsp->fRec324[2] = dsp->fRec324[1];
			dsp->fRec324[1] = dsp->fRec324[0];
			dsp->fRec330[1] = dsp->fRec330[0];
			dsp->fRec329[2] = dsp->fRec329[1];
			dsp->fRec329[1] = dsp->fRec329[0];
			dsp->fRec328[2] = dsp->fRec328[1];
			dsp->fRec328[1] = dsp->fRec328[0];
			dsp->fRec327[2] = dsp->fRec327[1];
			dsp->fRec327[1] = dsp->fRec327[0];
			dsp->fRec326[2] = dsp->fRec326[1];
			dsp->fRec326[1] = dsp->fRec326[0];
			dsp->fRec336[1] = dsp->fRec336[0];
			dsp->fRec335[2] = dsp->fRec335[1];
			dsp->fRec335[1] = dsp->fRec335[0];
			dsp->fVec44[1] = dsp->fVec44[0];
			dsp->fRec334[1] = dsp->fRec334[0];
			dsp->fRec333[2] = dsp->fRec333[1];
			dsp->fRec333[1] = dsp->fRec333[0];
			dsp->fRec332[2] = dsp->fRec332[1];
			dsp->fRec332[1] = dsp->fRec332[0];
			dsp->fRec331[2] = dsp->fRec331[1];
			dsp->fRec331[1] = dsp->fRec331[0];
			dsp->fRec341[1] = dsp->fRec341[0];
			dsp->fRec340[2] = dsp->fRec340[1];
			dsp->fRec340[1] = dsp->fRec340[0];
			dsp->fVec45[1] = dsp->fVec45[0];
			dsp->fRec339[1] = dsp->fRec339[0];
			dsp->fRec338[2] = dsp->fRec338[1];
			dsp->fRec338[1] = dsp->fRec338[0];
			dsp->fRec337[2] = dsp->fRec337[1];
			dsp->fRec337[1] = dsp->fRec337[0];
			dsp->fRec345[1] = dsp->fRec345[0];
			dsp->fRec344[2] = dsp->fRec344[1];
			dsp->fRec344[1] = dsp->fRec344[0];
			dsp->fVec46[1] = dsp->fVec46[0];
			dsp->fRec343[1] = dsp->fRec343[0];
			dsp->fRec342[2] = dsp->fRec342[1];
			dsp->fRec342[1] = dsp->fRec342[0];
			dsp->fRec347[1] = dsp->fRec347[0];
			dsp->fRec346[2] = dsp->fRec346[1];
			dsp->fRec346[1] = dsp->fRec346[0];
			dsp->fRec352[1] = dsp->fRec352[0];
			dsp->fRec351[2] = dsp->fRec351[1];
			dsp->fRec351[1] = dsp->fRec351[0];
			dsp->fRec350[2] = dsp->fRec350[1];
			dsp->fRec350[1] = dsp->fRec350[0];
			dsp->fRec349[2] = dsp->fRec349[1];
			dsp->fRec349[1] = dsp->fRec349[0];
			dsp->fRec348[2] = dsp->fRec348[1];
			dsp->fRec348[1] = dsp->fRec348[0];
			dsp->fRec358[1] = dsp->fRec358[0];
			dsp->fRec357[2] = dsp->fRec357[1];
			dsp->fRec357[1] = dsp->fRec357[0];
			dsp->fVec47[1] = dsp->fVec47[0];
			dsp->fRec356[1] = dsp->fRec356[0];
			dsp->fRec355[2] = dsp->fRec355[1];
			dsp->fRec355[1] = dsp->fRec355[0];
			dsp->fRec354[2] = dsp->fRec354[1];
			dsp->fRec354[1] = dsp->fRec354[0];
			dsp->fRec353[2] = dsp->fRec353[1];
			dsp->fRec353[1] = dsp->fRec353[0];
			dsp->fRec363[1] = dsp->fRec363[0];
			dsp->fRec362[2] = dsp->fRec362[1];
			dsp->fRec362[1] = dsp->fRec362[0];
			dsp->fVec48[1] = dsp->fVec48[0];
			dsp->fRec361[1] = dsp->fRec361[0];
			dsp->fRec360[2] = dsp->fRec360[1];
			dsp->fRec360[1] = dsp->fRec360[0];
			dsp->fRec359[2] = dsp->fRec359[1];
			dsp->fRec359[1] = dsp->fRec359[0];
			dsp->fRec367[1] = dsp->fRec367[0];
			dsp->fRec366[2] = dsp->fRec366[1];
			dsp->fRec366[1] = dsp->fRec366[0];
			dsp->fVec49[1] = dsp->fVec49[0];
			dsp->fRec365[1] = dsp->fRec365[0];
			dsp->fRec364[2] = dsp->fRec364[1];
			dsp->fRec364[1] = dsp->fRec364[0];
			dsp->fRec369[1] = dsp->fRec369[0];
			dsp->fRec368[2] = dsp->fRec368[1];
			dsp->fRec368[1] = dsp->fRec368[0];
			dsp->IOTA = (dsp->IOTA + 1);
			dsp->fRec0[2] = dsp->fRec0[1];
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fVec51[1] = dsp->fVec51[0];
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
			dsp->fRec8[2] = dsp->fRec8[1];
			dsp->fRec8[1] = dsp->fRec8[0];
			dsp->fRec9[2] = dsp->fRec9[1];
			dsp->fRec9[1] = dsp->fRec9[0];
			dsp->fRec10[2] = dsp->fRec10[1];
			dsp->fRec10[1] = dsp->fRec10[0];
			dsp->fRec11[2] = dsp->fRec11[1];
			dsp->fRec11[1] = dsp->fRec11[0];
			dsp->fRec12[2] = dsp->fRec12[1];
			dsp->fRec12[1] = dsp->fRec12[0];
			dsp->fRec13[2] = dsp->fRec13[1];
			dsp->fRec13[1] = dsp->fRec13[0];
			dsp->fRec14[2] = dsp->fRec14[1];
			dsp->fRec14[1] = dsp->fRec14[0];
			dsp->fRec15[2] = dsp->fRec15[1];
			dsp->fRec15[1] = dsp->fRec15[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
