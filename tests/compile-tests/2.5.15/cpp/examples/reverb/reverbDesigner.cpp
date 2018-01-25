/* ------------------------------------------------------------
name: "reverbDesigner"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: cpp, -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__


// algorithm is required for min and max
#include <algorithm>
#include "gui/UI.h"

using namespace std;

// the struct below are not defined in UI.h
struct dsp {
};

struct Meta {
	void declare(const char*, const char*) {}
};
#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <cmath>
#include <math.h>

float mydsp_faustpower2_f(float value) {
	return (value * value);
	
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif
#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class mydsp : public dsp {
	
 private:
	
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
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "0.0");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "reverbDesigner");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
		m->declare("reverbs.lib/name", "Faust Reverb Library");
		m->declare("reverbs.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
	}

	virtual int getNumInputs() {
		return 4;
		
	}
	virtual int getNumOutputs() {
		return 2;
		
	}
	virtual int getInputRate(int channel) {
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
	virtual int getOutputRate(int channel) {
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
	
	static void classInit(int samplingFreq) {
		
	}
	
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(192000.0f, max(1.0f, float(fSamplingFreq)));
		fConst1 = (1.0f / fConst0);
		fConst2 = (0.002915452f * fConst0);
		fConst3 = (3.14159274f / fConst0);
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(-40.0f);
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fButton0 = FAUSTFLOAT(0.0f);
		fButton1 = FAUSTFLOAT(0.0f);
		fCheckbox1 = FAUSTFLOAT(0.0f);
		fButton2 = FAUSTFLOAT(0.0f);
		fHslider1 = FAUSTFLOAT(46.0f);
		fHslider2 = FAUSTFLOAT(63.0f);
		fVslider0 = FAUSTFLOAT(2.7000000000000002f);
		fHslider3 = FAUSTFLOAT(4000.0f);
		fHslider4 = FAUSTFLOAT(2000.0f);
		fHslider5 = FAUSTFLOAT(1000.0f);
		fHslider6 = FAUSTFLOAT(500.0f);
		fVslider1 = FAUSTFLOAT(3.7999999999999998f);
		fVslider2 = FAUSTFLOAT(5.0f);
		fVslider3 = FAUSTFLOAT(6.5f);
		fVslider4 = FAUSTFLOAT(8.4000000000000004f);
		fButton3 = FAUSTFLOAT(0.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iRec17[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 4); l1 = (l1 + 1)) {
			fRec16[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fVec0[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fVec1[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec22[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) {
			fRec21[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) {
			fRec20[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			fRec19[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
			fRec18[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec28[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 3); l10 = (l10 + 1)) {
			fRec27[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fVec2[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec26[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 3); l13 = (l13 + 1)) {
			fRec25[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 3); l14 = (l14 + 1)) {
			fRec24[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 3); l15 = (l15 + 1)) {
			fRec23[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec33[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 3); l17 = (l17 + 1)) {
			fRec32[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fVec3[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec31[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 3); l20 = (l20 + 1)) {
			fRec30[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 3); l21 = (l21 + 1)) {
			fRec29[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec37[l22] = 0.0f;
			
		}
		for (int l23 = 0; (l23 < 3); l23 = (l23 + 1)) {
			fRec36[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fVec4[l24] = 0.0f;
			
		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fRec35[l25] = 0.0f;
			
		}
		for (int l26 = 0; (l26 < 3); l26 = (l26 + 1)) {
			fRec34[l26] = 0.0f;
			
		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fRec39[l27] = 0.0f;
			
		}
		for (int l28 = 0; (l28 < 3); l28 = (l28 + 1)) {
			fRec38[l28] = 0.0f;
			
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec44[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 3); l30 = (l30 + 1)) {
			fRec43[l30] = 0.0f;
			
		}
		for (int l31 = 0; (l31 < 3); l31 = (l31 + 1)) {
			fRec42[l31] = 0.0f;
			
		}
		for (int l32 = 0; (l32 < 3); l32 = (l32 + 1)) {
			fRec41[l32] = 0.0f;
			
		}
		for (int l33 = 0; (l33 < 3); l33 = (l33 + 1)) {
			fRec40[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fRec50[l34] = 0.0f;
			
		}
		for (int l35 = 0; (l35 < 3); l35 = (l35 + 1)) {
			fRec49[l35] = 0.0f;
			
		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			fVec5[l36] = 0.0f;
			
		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fRec48[l37] = 0.0f;
			
		}
		for (int l38 = 0; (l38 < 3); l38 = (l38 + 1)) {
			fRec47[l38] = 0.0f;
			
		}
		for (int l39 = 0; (l39 < 3); l39 = (l39 + 1)) {
			fRec46[l39] = 0.0f;
			
		}
		for (int l40 = 0; (l40 < 3); l40 = (l40 + 1)) {
			fRec45[l40] = 0.0f;
			
		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fRec55[l41] = 0.0f;
			
		}
		for (int l42 = 0; (l42 < 3); l42 = (l42 + 1)) {
			fRec54[l42] = 0.0f;
			
		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			fVec6[l43] = 0.0f;
			
		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fRec53[l44] = 0.0f;
			
		}
		for (int l45 = 0; (l45 < 3); l45 = (l45 + 1)) {
			fRec52[l45] = 0.0f;
			
		}
		for (int l46 = 0; (l46 < 3); l46 = (l46 + 1)) {
			fRec51[l46] = 0.0f;
			
		}
		for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			fRec59[l47] = 0.0f;
			
		}
		for (int l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			fRec58[l48] = 0.0f;
			
		}
		for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			fVec7[l49] = 0.0f;
			
		}
		for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			fRec57[l50] = 0.0f;
			
		}
		for (int l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			fRec56[l51] = 0.0f;
			
		}
		for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			fRec61[l52] = 0.0f;
			
		}
		for (int l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			fRec60[l53] = 0.0f;
			
		}
		for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
			fRec66[l54] = 0.0f;
			
		}
		for (int l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			fRec65[l55] = 0.0f;
			
		}
		for (int l56 = 0; (l56 < 3); l56 = (l56 + 1)) {
			fRec64[l56] = 0.0f;
			
		}
		for (int l57 = 0; (l57 < 3); l57 = (l57 + 1)) {
			fRec63[l57] = 0.0f;
			
		}
		for (int l58 = 0; (l58 < 3); l58 = (l58 + 1)) {
			fRec62[l58] = 0.0f;
			
		}
		for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			fRec72[l59] = 0.0f;
			
		}
		for (int l60 = 0; (l60 < 3); l60 = (l60 + 1)) {
			fRec71[l60] = 0.0f;
			
		}
		for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			fVec8[l61] = 0.0f;
			
		}
		for (int l62 = 0; (l62 < 2); l62 = (l62 + 1)) {
			fRec70[l62] = 0.0f;
			
		}
		for (int l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			fRec69[l63] = 0.0f;
			
		}
		for (int l64 = 0; (l64 < 3); l64 = (l64 + 1)) {
			fRec68[l64] = 0.0f;
			
		}
		for (int l65 = 0; (l65 < 3); l65 = (l65 + 1)) {
			fRec67[l65] = 0.0f;
			
		}
		for (int l66 = 0; (l66 < 2); l66 = (l66 + 1)) {
			fRec77[l66] = 0.0f;
			
		}
		for (int l67 = 0; (l67 < 3); l67 = (l67 + 1)) {
			fRec76[l67] = 0.0f;
			
		}
		for (int l68 = 0; (l68 < 2); l68 = (l68 + 1)) {
			fVec9[l68] = 0.0f;
			
		}
		for (int l69 = 0; (l69 < 2); l69 = (l69 + 1)) {
			fRec75[l69] = 0.0f;
			
		}
		for (int l70 = 0; (l70 < 3); l70 = (l70 + 1)) {
			fRec74[l70] = 0.0f;
			
		}
		for (int l71 = 0; (l71 < 3); l71 = (l71 + 1)) {
			fRec73[l71] = 0.0f;
			
		}
		for (int l72 = 0; (l72 < 2); l72 = (l72 + 1)) {
			fRec81[l72] = 0.0f;
			
		}
		for (int l73 = 0; (l73 < 3); l73 = (l73 + 1)) {
			fRec80[l73] = 0.0f;
			
		}
		for (int l74 = 0; (l74 < 2); l74 = (l74 + 1)) {
			fVec10[l74] = 0.0f;
			
		}
		for (int l75 = 0; (l75 < 2); l75 = (l75 + 1)) {
			fRec79[l75] = 0.0f;
			
		}
		for (int l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			fRec78[l76] = 0.0f;
			
		}
		for (int l77 = 0; (l77 < 2); l77 = (l77 + 1)) {
			fRec83[l77] = 0.0f;
			
		}
		for (int l78 = 0; (l78 < 3); l78 = (l78 + 1)) {
			fRec82[l78] = 0.0f;
			
		}
		for (int l79 = 0; (l79 < 2); l79 = (l79 + 1)) {
			fRec88[l79] = 0.0f;
			
		}
		for (int l80 = 0; (l80 < 3); l80 = (l80 + 1)) {
			fRec87[l80] = 0.0f;
			
		}
		for (int l81 = 0; (l81 < 3); l81 = (l81 + 1)) {
			fRec86[l81] = 0.0f;
			
		}
		for (int l82 = 0; (l82 < 3); l82 = (l82 + 1)) {
			fRec85[l82] = 0.0f;
			
		}
		for (int l83 = 0; (l83 < 3); l83 = (l83 + 1)) {
			fRec84[l83] = 0.0f;
			
		}
		for (int l84 = 0; (l84 < 2); l84 = (l84 + 1)) {
			fRec94[l84] = 0.0f;
			
		}
		for (int l85 = 0; (l85 < 3); l85 = (l85 + 1)) {
			fRec93[l85] = 0.0f;
			
		}
		for (int l86 = 0; (l86 < 2); l86 = (l86 + 1)) {
			fVec11[l86] = 0.0f;
			
		}
		for (int l87 = 0; (l87 < 2); l87 = (l87 + 1)) {
			fRec92[l87] = 0.0f;
			
		}
		for (int l88 = 0; (l88 < 3); l88 = (l88 + 1)) {
			fRec91[l88] = 0.0f;
			
		}
		for (int l89 = 0; (l89 < 3); l89 = (l89 + 1)) {
			fRec90[l89] = 0.0f;
			
		}
		for (int l90 = 0; (l90 < 3); l90 = (l90 + 1)) {
			fRec89[l90] = 0.0f;
			
		}
		for (int l91 = 0; (l91 < 2); l91 = (l91 + 1)) {
			fRec99[l91] = 0.0f;
			
		}
		for (int l92 = 0; (l92 < 3); l92 = (l92 + 1)) {
			fRec98[l92] = 0.0f;
			
		}
		for (int l93 = 0; (l93 < 2); l93 = (l93 + 1)) {
			fVec12[l93] = 0.0f;
			
		}
		for (int l94 = 0; (l94 < 2); l94 = (l94 + 1)) {
			fRec97[l94] = 0.0f;
			
		}
		for (int l95 = 0; (l95 < 3); l95 = (l95 + 1)) {
			fRec96[l95] = 0.0f;
			
		}
		for (int l96 = 0; (l96 < 3); l96 = (l96 + 1)) {
			fRec95[l96] = 0.0f;
			
		}
		for (int l97 = 0; (l97 < 2); l97 = (l97 + 1)) {
			fRec103[l97] = 0.0f;
			
		}
		for (int l98 = 0; (l98 < 3); l98 = (l98 + 1)) {
			fRec102[l98] = 0.0f;
			
		}
		for (int l99 = 0; (l99 < 2); l99 = (l99 + 1)) {
			fVec13[l99] = 0.0f;
			
		}
		for (int l100 = 0; (l100 < 2); l100 = (l100 + 1)) {
			fRec101[l100] = 0.0f;
			
		}
		for (int l101 = 0; (l101 < 3); l101 = (l101 + 1)) {
			fRec100[l101] = 0.0f;
			
		}
		for (int l102 = 0; (l102 < 2); l102 = (l102 + 1)) {
			fRec105[l102] = 0.0f;
			
		}
		for (int l103 = 0; (l103 < 3); l103 = (l103 + 1)) {
			fRec104[l103] = 0.0f;
			
		}
		for (int l104 = 0; (l104 < 2); l104 = (l104 + 1)) {
			fRec110[l104] = 0.0f;
			
		}
		for (int l105 = 0; (l105 < 3); l105 = (l105 + 1)) {
			fRec109[l105] = 0.0f;
			
		}
		for (int l106 = 0; (l106 < 3); l106 = (l106 + 1)) {
			fRec108[l106] = 0.0f;
			
		}
		for (int l107 = 0; (l107 < 3); l107 = (l107 + 1)) {
			fRec107[l107] = 0.0f;
			
		}
		for (int l108 = 0; (l108 < 3); l108 = (l108 + 1)) {
			fRec106[l108] = 0.0f;
			
		}
		for (int l109 = 0; (l109 < 2); l109 = (l109 + 1)) {
			fRec116[l109] = 0.0f;
			
		}
		for (int l110 = 0; (l110 < 3); l110 = (l110 + 1)) {
			fRec115[l110] = 0.0f;
			
		}
		for (int l111 = 0; (l111 < 2); l111 = (l111 + 1)) {
			fVec14[l111] = 0.0f;
			
		}
		for (int l112 = 0; (l112 < 2); l112 = (l112 + 1)) {
			fRec114[l112] = 0.0f;
			
		}
		for (int l113 = 0; (l113 < 3); l113 = (l113 + 1)) {
			fRec113[l113] = 0.0f;
			
		}
		for (int l114 = 0; (l114 < 3); l114 = (l114 + 1)) {
			fRec112[l114] = 0.0f;
			
		}
		for (int l115 = 0; (l115 < 3); l115 = (l115 + 1)) {
			fRec111[l115] = 0.0f;
			
		}
		for (int l116 = 0; (l116 < 2); l116 = (l116 + 1)) {
			fRec121[l116] = 0.0f;
			
		}
		for (int l117 = 0; (l117 < 3); l117 = (l117 + 1)) {
			fRec120[l117] = 0.0f;
			
		}
		for (int l118 = 0; (l118 < 2); l118 = (l118 + 1)) {
			fVec15[l118] = 0.0f;
			
		}
		for (int l119 = 0; (l119 < 2); l119 = (l119 + 1)) {
			fRec119[l119] = 0.0f;
			
		}
		for (int l120 = 0; (l120 < 3); l120 = (l120 + 1)) {
			fRec118[l120] = 0.0f;
			
		}
		for (int l121 = 0; (l121 < 3); l121 = (l121 + 1)) {
			fRec117[l121] = 0.0f;
			
		}
		for (int l122 = 0; (l122 < 2); l122 = (l122 + 1)) {
			fRec125[l122] = 0.0f;
			
		}
		for (int l123 = 0; (l123 < 3); l123 = (l123 + 1)) {
			fRec124[l123] = 0.0f;
			
		}
		for (int l124 = 0; (l124 < 2); l124 = (l124 + 1)) {
			fVec16[l124] = 0.0f;
			
		}
		for (int l125 = 0; (l125 < 2); l125 = (l125 + 1)) {
			fRec123[l125] = 0.0f;
			
		}
		for (int l126 = 0; (l126 < 3); l126 = (l126 + 1)) {
			fRec122[l126] = 0.0f;
			
		}
		for (int l127 = 0; (l127 < 2); l127 = (l127 + 1)) {
			fRec127[l127] = 0.0f;
			
		}
		for (int l128 = 0; (l128 < 3); l128 = (l128 + 1)) {
			fRec126[l128] = 0.0f;
			
		}
		for (int l129 = 0; (l129 < 2); l129 = (l129 + 1)) {
			fRec132[l129] = 0.0f;
			
		}
		for (int l130 = 0; (l130 < 3); l130 = (l130 + 1)) {
			fRec131[l130] = 0.0f;
			
		}
		for (int l131 = 0; (l131 < 3); l131 = (l131 + 1)) {
			fRec130[l131] = 0.0f;
			
		}
		for (int l132 = 0; (l132 < 3); l132 = (l132 + 1)) {
			fRec129[l132] = 0.0f;
			
		}
		for (int l133 = 0; (l133 < 3); l133 = (l133 + 1)) {
			fRec128[l133] = 0.0f;
			
		}
		for (int l134 = 0; (l134 < 2); l134 = (l134 + 1)) {
			fRec138[l134] = 0.0f;
			
		}
		for (int l135 = 0; (l135 < 3); l135 = (l135 + 1)) {
			fRec137[l135] = 0.0f;
			
		}
		for (int l136 = 0; (l136 < 2); l136 = (l136 + 1)) {
			fVec17[l136] = 0.0f;
			
		}
		for (int l137 = 0; (l137 < 2); l137 = (l137 + 1)) {
			fRec136[l137] = 0.0f;
			
		}
		for (int l138 = 0; (l138 < 3); l138 = (l138 + 1)) {
			fRec135[l138] = 0.0f;
			
		}
		for (int l139 = 0; (l139 < 3); l139 = (l139 + 1)) {
			fRec134[l139] = 0.0f;
			
		}
		for (int l140 = 0; (l140 < 3); l140 = (l140 + 1)) {
			fRec133[l140] = 0.0f;
			
		}
		for (int l141 = 0; (l141 < 2); l141 = (l141 + 1)) {
			fRec143[l141] = 0.0f;
			
		}
		for (int l142 = 0; (l142 < 3); l142 = (l142 + 1)) {
			fRec142[l142] = 0.0f;
			
		}
		for (int l143 = 0; (l143 < 2); l143 = (l143 + 1)) {
			fVec18[l143] = 0.0f;
			
		}
		for (int l144 = 0; (l144 < 2); l144 = (l144 + 1)) {
			fRec141[l144] = 0.0f;
			
		}
		for (int l145 = 0; (l145 < 3); l145 = (l145 + 1)) {
			fRec140[l145] = 0.0f;
			
		}
		for (int l146 = 0; (l146 < 3); l146 = (l146 + 1)) {
			fRec139[l146] = 0.0f;
			
		}
		for (int l147 = 0; (l147 < 2); l147 = (l147 + 1)) {
			fRec147[l147] = 0.0f;
			
		}
		for (int l148 = 0; (l148 < 3); l148 = (l148 + 1)) {
			fRec146[l148] = 0.0f;
			
		}
		for (int l149 = 0; (l149 < 2); l149 = (l149 + 1)) {
			fVec19[l149] = 0.0f;
			
		}
		for (int l150 = 0; (l150 < 2); l150 = (l150 + 1)) {
			fRec145[l150] = 0.0f;
			
		}
		for (int l151 = 0; (l151 < 3); l151 = (l151 + 1)) {
			fRec144[l151] = 0.0f;
			
		}
		for (int l152 = 0; (l152 < 2); l152 = (l152 + 1)) {
			fRec149[l152] = 0.0f;
			
		}
		for (int l153 = 0; (l153 < 3); l153 = (l153 + 1)) {
			fRec148[l153] = 0.0f;
			
		}
		for (int l154 = 0; (l154 < 2); l154 = (l154 + 1)) {
			fRec154[l154] = 0.0f;
			
		}
		for (int l155 = 0; (l155 < 3); l155 = (l155 + 1)) {
			fRec153[l155] = 0.0f;
			
		}
		for (int l156 = 0; (l156 < 3); l156 = (l156 + 1)) {
			fRec152[l156] = 0.0f;
			
		}
		for (int l157 = 0; (l157 < 3); l157 = (l157 + 1)) {
			fRec151[l157] = 0.0f;
			
		}
		for (int l158 = 0; (l158 < 3); l158 = (l158 + 1)) {
			fRec150[l158] = 0.0f;
			
		}
		for (int l159 = 0; (l159 < 2); l159 = (l159 + 1)) {
			fRec160[l159] = 0.0f;
			
		}
		for (int l160 = 0; (l160 < 3); l160 = (l160 + 1)) {
			fRec159[l160] = 0.0f;
			
		}
		for (int l161 = 0; (l161 < 2); l161 = (l161 + 1)) {
			fVec20[l161] = 0.0f;
			
		}
		for (int l162 = 0; (l162 < 2); l162 = (l162 + 1)) {
			fRec158[l162] = 0.0f;
			
		}
		for (int l163 = 0; (l163 < 3); l163 = (l163 + 1)) {
			fRec157[l163] = 0.0f;
			
		}
		for (int l164 = 0; (l164 < 3); l164 = (l164 + 1)) {
			fRec156[l164] = 0.0f;
			
		}
		for (int l165 = 0; (l165 < 3); l165 = (l165 + 1)) {
			fRec155[l165] = 0.0f;
			
		}
		for (int l166 = 0; (l166 < 2); l166 = (l166 + 1)) {
			fRec165[l166] = 0.0f;
			
		}
		for (int l167 = 0; (l167 < 3); l167 = (l167 + 1)) {
			fRec164[l167] = 0.0f;
			
		}
		for (int l168 = 0; (l168 < 2); l168 = (l168 + 1)) {
			fVec21[l168] = 0.0f;
			
		}
		for (int l169 = 0; (l169 < 2); l169 = (l169 + 1)) {
			fRec163[l169] = 0.0f;
			
		}
		for (int l170 = 0; (l170 < 3); l170 = (l170 + 1)) {
			fRec162[l170] = 0.0f;
			
		}
		for (int l171 = 0; (l171 < 3); l171 = (l171 + 1)) {
			fRec161[l171] = 0.0f;
			
		}
		for (int l172 = 0; (l172 < 2); l172 = (l172 + 1)) {
			fRec169[l172] = 0.0f;
			
		}
		for (int l173 = 0; (l173 < 3); l173 = (l173 + 1)) {
			fRec168[l173] = 0.0f;
			
		}
		for (int l174 = 0; (l174 < 2); l174 = (l174 + 1)) {
			fVec22[l174] = 0.0f;
			
		}
		for (int l175 = 0; (l175 < 2); l175 = (l175 + 1)) {
			fRec167[l175] = 0.0f;
			
		}
		for (int l176 = 0; (l176 < 3); l176 = (l176 + 1)) {
			fRec166[l176] = 0.0f;
			
		}
		for (int l177 = 0; (l177 < 2); l177 = (l177 + 1)) {
			fRec171[l177] = 0.0f;
			
		}
		for (int l178 = 0; (l178 < 3); l178 = (l178 + 1)) {
			fRec170[l178] = 0.0f;
			
		}
		for (int l179 = 0; (l179 < 2); l179 = (l179 + 1)) {
			fRec176[l179] = 0.0f;
			
		}
		for (int l180 = 0; (l180 < 3); l180 = (l180 + 1)) {
			fRec175[l180] = 0.0f;
			
		}
		for (int l181 = 0; (l181 < 3); l181 = (l181 + 1)) {
			fRec174[l181] = 0.0f;
			
		}
		for (int l182 = 0; (l182 < 3); l182 = (l182 + 1)) {
			fRec173[l182] = 0.0f;
			
		}
		for (int l183 = 0; (l183 < 3); l183 = (l183 + 1)) {
			fRec172[l183] = 0.0f;
			
		}
		for (int l184 = 0; (l184 < 2); l184 = (l184 + 1)) {
			fRec182[l184] = 0.0f;
			
		}
		for (int l185 = 0; (l185 < 3); l185 = (l185 + 1)) {
			fRec181[l185] = 0.0f;
			
		}
		for (int l186 = 0; (l186 < 2); l186 = (l186 + 1)) {
			fVec23[l186] = 0.0f;
			
		}
		for (int l187 = 0; (l187 < 2); l187 = (l187 + 1)) {
			fRec180[l187] = 0.0f;
			
		}
		for (int l188 = 0; (l188 < 3); l188 = (l188 + 1)) {
			fRec179[l188] = 0.0f;
			
		}
		for (int l189 = 0; (l189 < 3); l189 = (l189 + 1)) {
			fRec178[l189] = 0.0f;
			
		}
		for (int l190 = 0; (l190 < 3); l190 = (l190 + 1)) {
			fRec177[l190] = 0.0f;
			
		}
		for (int l191 = 0; (l191 < 2); l191 = (l191 + 1)) {
			fRec187[l191] = 0.0f;
			
		}
		for (int l192 = 0; (l192 < 3); l192 = (l192 + 1)) {
			fRec186[l192] = 0.0f;
			
		}
		for (int l193 = 0; (l193 < 2); l193 = (l193 + 1)) {
			fVec24[l193] = 0.0f;
			
		}
		for (int l194 = 0; (l194 < 2); l194 = (l194 + 1)) {
			fRec185[l194] = 0.0f;
			
		}
		for (int l195 = 0; (l195 < 3); l195 = (l195 + 1)) {
			fRec184[l195] = 0.0f;
			
		}
		for (int l196 = 0; (l196 < 3); l196 = (l196 + 1)) {
			fRec183[l196] = 0.0f;
			
		}
		for (int l197 = 0; (l197 < 2); l197 = (l197 + 1)) {
			fRec191[l197] = 0.0f;
			
		}
		for (int l198 = 0; (l198 < 3); l198 = (l198 + 1)) {
			fRec190[l198] = 0.0f;
			
		}
		for (int l199 = 0; (l199 < 2); l199 = (l199 + 1)) {
			fVec25[l199] = 0.0f;
			
		}
		for (int l200 = 0; (l200 < 2); l200 = (l200 + 1)) {
			fRec189[l200] = 0.0f;
			
		}
		for (int l201 = 0; (l201 < 3); l201 = (l201 + 1)) {
			fRec188[l201] = 0.0f;
			
		}
		for (int l202 = 0; (l202 < 2); l202 = (l202 + 1)) {
			fRec193[l202] = 0.0f;
			
		}
		for (int l203 = 0; (l203 < 3); l203 = (l203 + 1)) {
			fRec192[l203] = 0.0f;
			
		}
		for (int l204 = 0; (l204 < 2); l204 = (l204 + 1)) {
			fRec198[l204] = 0.0f;
			
		}
		for (int l205 = 0; (l205 < 3); l205 = (l205 + 1)) {
			fRec197[l205] = 0.0f;
			
		}
		for (int l206 = 0; (l206 < 3); l206 = (l206 + 1)) {
			fRec196[l206] = 0.0f;
			
		}
		for (int l207 = 0; (l207 < 3); l207 = (l207 + 1)) {
			fRec195[l207] = 0.0f;
			
		}
		for (int l208 = 0; (l208 < 3); l208 = (l208 + 1)) {
			fRec194[l208] = 0.0f;
			
		}
		for (int l209 = 0; (l209 < 2); l209 = (l209 + 1)) {
			fRec204[l209] = 0.0f;
			
		}
		for (int l210 = 0; (l210 < 3); l210 = (l210 + 1)) {
			fRec203[l210] = 0.0f;
			
		}
		for (int l211 = 0; (l211 < 2); l211 = (l211 + 1)) {
			fVec26[l211] = 0.0f;
			
		}
		for (int l212 = 0; (l212 < 2); l212 = (l212 + 1)) {
			fRec202[l212] = 0.0f;
			
		}
		for (int l213 = 0; (l213 < 3); l213 = (l213 + 1)) {
			fRec201[l213] = 0.0f;
			
		}
		for (int l214 = 0; (l214 < 3); l214 = (l214 + 1)) {
			fRec200[l214] = 0.0f;
			
		}
		for (int l215 = 0; (l215 < 3); l215 = (l215 + 1)) {
			fRec199[l215] = 0.0f;
			
		}
		for (int l216 = 0; (l216 < 2); l216 = (l216 + 1)) {
			fRec209[l216] = 0.0f;
			
		}
		for (int l217 = 0; (l217 < 3); l217 = (l217 + 1)) {
			fRec208[l217] = 0.0f;
			
		}
		for (int l218 = 0; (l218 < 2); l218 = (l218 + 1)) {
			fVec27[l218] = 0.0f;
			
		}
		for (int l219 = 0; (l219 < 2); l219 = (l219 + 1)) {
			fRec207[l219] = 0.0f;
			
		}
		for (int l220 = 0; (l220 < 3); l220 = (l220 + 1)) {
			fRec206[l220] = 0.0f;
			
		}
		for (int l221 = 0; (l221 < 3); l221 = (l221 + 1)) {
			fRec205[l221] = 0.0f;
			
		}
		for (int l222 = 0; (l222 < 2); l222 = (l222 + 1)) {
			fRec213[l222] = 0.0f;
			
		}
		for (int l223 = 0; (l223 < 3); l223 = (l223 + 1)) {
			fRec212[l223] = 0.0f;
			
		}
		for (int l224 = 0; (l224 < 2); l224 = (l224 + 1)) {
			fVec28[l224] = 0.0f;
			
		}
		for (int l225 = 0; (l225 < 2); l225 = (l225 + 1)) {
			fRec211[l225] = 0.0f;
			
		}
		for (int l226 = 0; (l226 < 3); l226 = (l226 + 1)) {
			fRec210[l226] = 0.0f;
			
		}
		for (int l227 = 0; (l227 < 2); l227 = (l227 + 1)) {
			fRec215[l227] = 0.0f;
			
		}
		for (int l228 = 0; (l228 < 3); l228 = (l228 + 1)) {
			fRec214[l228] = 0.0f;
			
		}
		for (int l229 = 0; (l229 < 2); l229 = (l229 + 1)) {
			fRec220[l229] = 0.0f;
			
		}
		for (int l230 = 0; (l230 < 3); l230 = (l230 + 1)) {
			fRec219[l230] = 0.0f;
			
		}
		for (int l231 = 0; (l231 < 3); l231 = (l231 + 1)) {
			fRec218[l231] = 0.0f;
			
		}
		for (int l232 = 0; (l232 < 3); l232 = (l232 + 1)) {
			fRec217[l232] = 0.0f;
			
		}
		for (int l233 = 0; (l233 < 3); l233 = (l233 + 1)) {
			fRec216[l233] = 0.0f;
			
		}
		for (int l234 = 0; (l234 < 2); l234 = (l234 + 1)) {
			fRec226[l234] = 0.0f;
			
		}
		for (int l235 = 0; (l235 < 3); l235 = (l235 + 1)) {
			fRec225[l235] = 0.0f;
			
		}
		for (int l236 = 0; (l236 < 2); l236 = (l236 + 1)) {
			fVec29[l236] = 0.0f;
			
		}
		for (int l237 = 0; (l237 < 2); l237 = (l237 + 1)) {
			fRec224[l237] = 0.0f;
			
		}
		for (int l238 = 0; (l238 < 3); l238 = (l238 + 1)) {
			fRec223[l238] = 0.0f;
			
		}
		for (int l239 = 0; (l239 < 3); l239 = (l239 + 1)) {
			fRec222[l239] = 0.0f;
			
		}
		for (int l240 = 0; (l240 < 3); l240 = (l240 + 1)) {
			fRec221[l240] = 0.0f;
			
		}
		for (int l241 = 0; (l241 < 2); l241 = (l241 + 1)) {
			fRec231[l241] = 0.0f;
			
		}
		for (int l242 = 0; (l242 < 3); l242 = (l242 + 1)) {
			fRec230[l242] = 0.0f;
			
		}
		for (int l243 = 0; (l243 < 2); l243 = (l243 + 1)) {
			fVec30[l243] = 0.0f;
			
		}
		for (int l244 = 0; (l244 < 2); l244 = (l244 + 1)) {
			fRec229[l244] = 0.0f;
			
		}
		for (int l245 = 0; (l245 < 3); l245 = (l245 + 1)) {
			fRec228[l245] = 0.0f;
			
		}
		for (int l246 = 0; (l246 < 3); l246 = (l246 + 1)) {
			fRec227[l246] = 0.0f;
			
		}
		for (int l247 = 0; (l247 < 2); l247 = (l247 + 1)) {
			fRec235[l247] = 0.0f;
			
		}
		for (int l248 = 0; (l248 < 3); l248 = (l248 + 1)) {
			fRec234[l248] = 0.0f;
			
		}
		for (int l249 = 0; (l249 < 2); l249 = (l249 + 1)) {
			fVec31[l249] = 0.0f;
			
		}
		for (int l250 = 0; (l250 < 2); l250 = (l250 + 1)) {
			fRec233[l250] = 0.0f;
			
		}
		for (int l251 = 0; (l251 < 3); l251 = (l251 + 1)) {
			fRec232[l251] = 0.0f;
			
		}
		for (int l252 = 0; (l252 < 2); l252 = (l252 + 1)) {
			fRec237[l252] = 0.0f;
			
		}
		for (int l253 = 0; (l253 < 3); l253 = (l253 + 1)) {
			fRec236[l253] = 0.0f;
			
		}
		for (int l254 = 0; (l254 < 2); l254 = (l254 + 1)) {
			fRec242[l254] = 0.0f;
			
		}
		for (int l255 = 0; (l255 < 3); l255 = (l255 + 1)) {
			fRec241[l255] = 0.0f;
			
		}
		for (int l256 = 0; (l256 < 3); l256 = (l256 + 1)) {
			fRec240[l256] = 0.0f;
			
		}
		for (int l257 = 0; (l257 < 3); l257 = (l257 + 1)) {
			fRec239[l257] = 0.0f;
			
		}
		for (int l258 = 0; (l258 < 3); l258 = (l258 + 1)) {
			fRec238[l258] = 0.0f;
			
		}
		for (int l259 = 0; (l259 < 2); l259 = (l259 + 1)) {
			fRec248[l259] = 0.0f;
			
		}
		for (int l260 = 0; (l260 < 3); l260 = (l260 + 1)) {
			fRec247[l260] = 0.0f;
			
		}
		for (int l261 = 0; (l261 < 2); l261 = (l261 + 1)) {
			fVec32[l261] = 0.0f;
			
		}
		for (int l262 = 0; (l262 < 2); l262 = (l262 + 1)) {
			fRec246[l262] = 0.0f;
			
		}
		for (int l263 = 0; (l263 < 3); l263 = (l263 + 1)) {
			fRec245[l263] = 0.0f;
			
		}
		for (int l264 = 0; (l264 < 3); l264 = (l264 + 1)) {
			fRec244[l264] = 0.0f;
			
		}
		for (int l265 = 0; (l265 < 3); l265 = (l265 + 1)) {
			fRec243[l265] = 0.0f;
			
		}
		for (int l266 = 0; (l266 < 2); l266 = (l266 + 1)) {
			fRec253[l266] = 0.0f;
			
		}
		for (int l267 = 0; (l267 < 3); l267 = (l267 + 1)) {
			fRec252[l267] = 0.0f;
			
		}
		for (int l268 = 0; (l268 < 2); l268 = (l268 + 1)) {
			fVec33[l268] = 0.0f;
			
		}
		for (int l269 = 0; (l269 < 2); l269 = (l269 + 1)) {
			fRec251[l269] = 0.0f;
			
		}
		for (int l270 = 0; (l270 < 3); l270 = (l270 + 1)) {
			fRec250[l270] = 0.0f;
			
		}
		for (int l271 = 0; (l271 < 3); l271 = (l271 + 1)) {
			fRec249[l271] = 0.0f;
			
		}
		for (int l272 = 0; (l272 < 2); l272 = (l272 + 1)) {
			fRec257[l272] = 0.0f;
			
		}
		for (int l273 = 0; (l273 < 3); l273 = (l273 + 1)) {
			fRec256[l273] = 0.0f;
			
		}
		for (int l274 = 0; (l274 < 2); l274 = (l274 + 1)) {
			fVec34[l274] = 0.0f;
			
		}
		for (int l275 = 0; (l275 < 2); l275 = (l275 + 1)) {
			fRec255[l275] = 0.0f;
			
		}
		for (int l276 = 0; (l276 < 3); l276 = (l276 + 1)) {
			fRec254[l276] = 0.0f;
			
		}
		for (int l277 = 0; (l277 < 2); l277 = (l277 + 1)) {
			fRec259[l277] = 0.0f;
			
		}
		for (int l278 = 0; (l278 < 3); l278 = (l278 + 1)) {
			fRec258[l278] = 0.0f;
			
		}
		for (int l279 = 0; (l279 < 2); l279 = (l279 + 1)) {
			fRec264[l279] = 0.0f;
			
		}
		for (int l280 = 0; (l280 < 3); l280 = (l280 + 1)) {
			fRec263[l280] = 0.0f;
			
		}
		for (int l281 = 0; (l281 < 3); l281 = (l281 + 1)) {
			fRec262[l281] = 0.0f;
			
		}
		for (int l282 = 0; (l282 < 3); l282 = (l282 + 1)) {
			fRec261[l282] = 0.0f;
			
		}
		for (int l283 = 0; (l283 < 3); l283 = (l283 + 1)) {
			fRec260[l283] = 0.0f;
			
		}
		for (int l284 = 0; (l284 < 2); l284 = (l284 + 1)) {
			fRec270[l284] = 0.0f;
			
		}
		for (int l285 = 0; (l285 < 3); l285 = (l285 + 1)) {
			fRec269[l285] = 0.0f;
			
		}
		for (int l286 = 0; (l286 < 2); l286 = (l286 + 1)) {
			fVec35[l286] = 0.0f;
			
		}
		for (int l287 = 0; (l287 < 2); l287 = (l287 + 1)) {
			fRec268[l287] = 0.0f;
			
		}
		for (int l288 = 0; (l288 < 3); l288 = (l288 + 1)) {
			fRec267[l288] = 0.0f;
			
		}
		for (int l289 = 0; (l289 < 3); l289 = (l289 + 1)) {
			fRec266[l289] = 0.0f;
			
		}
		for (int l290 = 0; (l290 < 3); l290 = (l290 + 1)) {
			fRec265[l290] = 0.0f;
			
		}
		for (int l291 = 0; (l291 < 2); l291 = (l291 + 1)) {
			fRec275[l291] = 0.0f;
			
		}
		for (int l292 = 0; (l292 < 3); l292 = (l292 + 1)) {
			fRec274[l292] = 0.0f;
			
		}
		for (int l293 = 0; (l293 < 2); l293 = (l293 + 1)) {
			fVec36[l293] = 0.0f;
			
		}
		for (int l294 = 0; (l294 < 2); l294 = (l294 + 1)) {
			fRec273[l294] = 0.0f;
			
		}
		for (int l295 = 0; (l295 < 3); l295 = (l295 + 1)) {
			fRec272[l295] = 0.0f;
			
		}
		for (int l296 = 0; (l296 < 3); l296 = (l296 + 1)) {
			fRec271[l296] = 0.0f;
			
		}
		for (int l297 = 0; (l297 < 2); l297 = (l297 + 1)) {
			fRec279[l297] = 0.0f;
			
		}
		for (int l298 = 0; (l298 < 3); l298 = (l298 + 1)) {
			fRec278[l298] = 0.0f;
			
		}
		for (int l299 = 0; (l299 < 2); l299 = (l299 + 1)) {
			fVec37[l299] = 0.0f;
			
		}
		for (int l300 = 0; (l300 < 2); l300 = (l300 + 1)) {
			fRec277[l300] = 0.0f;
			
		}
		for (int l301 = 0; (l301 < 3); l301 = (l301 + 1)) {
			fRec276[l301] = 0.0f;
			
		}
		for (int l302 = 0; (l302 < 2); l302 = (l302 + 1)) {
			fRec281[l302] = 0.0f;
			
		}
		for (int l303 = 0; (l303 < 3); l303 = (l303 + 1)) {
			fRec280[l303] = 0.0f;
			
		}
		for (int l304 = 0; (l304 < 2); l304 = (l304 + 1)) {
			fRec286[l304] = 0.0f;
			
		}
		for (int l305 = 0; (l305 < 3); l305 = (l305 + 1)) {
			fRec285[l305] = 0.0f;
			
		}
		for (int l306 = 0; (l306 < 3); l306 = (l306 + 1)) {
			fRec284[l306] = 0.0f;
			
		}
		for (int l307 = 0; (l307 < 3); l307 = (l307 + 1)) {
			fRec283[l307] = 0.0f;
			
		}
		for (int l308 = 0; (l308 < 3); l308 = (l308 + 1)) {
			fRec282[l308] = 0.0f;
			
		}
		for (int l309 = 0; (l309 < 2); l309 = (l309 + 1)) {
			fRec292[l309] = 0.0f;
			
		}
		for (int l310 = 0; (l310 < 3); l310 = (l310 + 1)) {
			fRec291[l310] = 0.0f;
			
		}
		for (int l311 = 0; (l311 < 2); l311 = (l311 + 1)) {
			fVec38[l311] = 0.0f;
			
		}
		for (int l312 = 0; (l312 < 2); l312 = (l312 + 1)) {
			fRec290[l312] = 0.0f;
			
		}
		for (int l313 = 0; (l313 < 3); l313 = (l313 + 1)) {
			fRec289[l313] = 0.0f;
			
		}
		for (int l314 = 0; (l314 < 3); l314 = (l314 + 1)) {
			fRec288[l314] = 0.0f;
			
		}
		for (int l315 = 0; (l315 < 3); l315 = (l315 + 1)) {
			fRec287[l315] = 0.0f;
			
		}
		for (int l316 = 0; (l316 < 2); l316 = (l316 + 1)) {
			fRec297[l316] = 0.0f;
			
		}
		for (int l317 = 0; (l317 < 3); l317 = (l317 + 1)) {
			fRec296[l317] = 0.0f;
			
		}
		for (int l318 = 0; (l318 < 2); l318 = (l318 + 1)) {
			fVec39[l318] = 0.0f;
			
		}
		for (int l319 = 0; (l319 < 2); l319 = (l319 + 1)) {
			fRec295[l319] = 0.0f;
			
		}
		for (int l320 = 0; (l320 < 3); l320 = (l320 + 1)) {
			fRec294[l320] = 0.0f;
			
		}
		for (int l321 = 0; (l321 < 3); l321 = (l321 + 1)) {
			fRec293[l321] = 0.0f;
			
		}
		for (int l322 = 0; (l322 < 2); l322 = (l322 + 1)) {
			fRec301[l322] = 0.0f;
			
		}
		for (int l323 = 0; (l323 < 3); l323 = (l323 + 1)) {
			fRec300[l323] = 0.0f;
			
		}
		for (int l324 = 0; (l324 < 2); l324 = (l324 + 1)) {
			fVec40[l324] = 0.0f;
			
		}
		for (int l325 = 0; (l325 < 2); l325 = (l325 + 1)) {
			fRec299[l325] = 0.0f;
			
		}
		for (int l326 = 0; (l326 < 3); l326 = (l326 + 1)) {
			fRec298[l326] = 0.0f;
			
		}
		for (int l327 = 0; (l327 < 2); l327 = (l327 + 1)) {
			fRec303[l327] = 0.0f;
			
		}
		for (int l328 = 0; (l328 < 3); l328 = (l328 + 1)) {
			fRec302[l328] = 0.0f;
			
		}
		for (int l329 = 0; (l329 < 2); l329 = (l329 + 1)) {
			fRec308[l329] = 0.0f;
			
		}
		for (int l330 = 0; (l330 < 3); l330 = (l330 + 1)) {
			fRec307[l330] = 0.0f;
			
		}
		for (int l331 = 0; (l331 < 3); l331 = (l331 + 1)) {
			fRec306[l331] = 0.0f;
			
		}
		for (int l332 = 0; (l332 < 3); l332 = (l332 + 1)) {
			fRec305[l332] = 0.0f;
			
		}
		for (int l333 = 0; (l333 < 3); l333 = (l333 + 1)) {
			fRec304[l333] = 0.0f;
			
		}
		for (int l334 = 0; (l334 < 2); l334 = (l334 + 1)) {
			fRec314[l334] = 0.0f;
			
		}
		for (int l335 = 0; (l335 < 3); l335 = (l335 + 1)) {
			fRec313[l335] = 0.0f;
			
		}
		for (int l336 = 0; (l336 < 2); l336 = (l336 + 1)) {
			fVec41[l336] = 0.0f;
			
		}
		for (int l337 = 0; (l337 < 2); l337 = (l337 + 1)) {
			fRec312[l337] = 0.0f;
			
		}
		for (int l338 = 0; (l338 < 3); l338 = (l338 + 1)) {
			fRec311[l338] = 0.0f;
			
		}
		for (int l339 = 0; (l339 < 3); l339 = (l339 + 1)) {
			fRec310[l339] = 0.0f;
			
		}
		for (int l340 = 0; (l340 < 3); l340 = (l340 + 1)) {
			fRec309[l340] = 0.0f;
			
		}
		for (int l341 = 0; (l341 < 2); l341 = (l341 + 1)) {
			fRec319[l341] = 0.0f;
			
		}
		for (int l342 = 0; (l342 < 3); l342 = (l342 + 1)) {
			fRec318[l342] = 0.0f;
			
		}
		for (int l343 = 0; (l343 < 2); l343 = (l343 + 1)) {
			fVec42[l343] = 0.0f;
			
		}
		for (int l344 = 0; (l344 < 2); l344 = (l344 + 1)) {
			fRec317[l344] = 0.0f;
			
		}
		for (int l345 = 0; (l345 < 3); l345 = (l345 + 1)) {
			fRec316[l345] = 0.0f;
			
		}
		for (int l346 = 0; (l346 < 3); l346 = (l346 + 1)) {
			fRec315[l346] = 0.0f;
			
		}
		for (int l347 = 0; (l347 < 2); l347 = (l347 + 1)) {
			fRec323[l347] = 0.0f;
			
		}
		for (int l348 = 0; (l348 < 3); l348 = (l348 + 1)) {
			fRec322[l348] = 0.0f;
			
		}
		for (int l349 = 0; (l349 < 2); l349 = (l349 + 1)) {
			fVec43[l349] = 0.0f;
			
		}
		for (int l350 = 0; (l350 < 2); l350 = (l350 + 1)) {
			fRec321[l350] = 0.0f;
			
		}
		for (int l351 = 0; (l351 < 3); l351 = (l351 + 1)) {
			fRec320[l351] = 0.0f;
			
		}
		for (int l352 = 0; (l352 < 2); l352 = (l352 + 1)) {
			fRec325[l352] = 0.0f;
			
		}
		for (int l353 = 0; (l353 < 3); l353 = (l353 + 1)) {
			fRec324[l353] = 0.0f;
			
		}
		for (int l354 = 0; (l354 < 2); l354 = (l354 + 1)) {
			fRec330[l354] = 0.0f;
			
		}
		for (int l355 = 0; (l355 < 3); l355 = (l355 + 1)) {
			fRec329[l355] = 0.0f;
			
		}
		for (int l356 = 0; (l356 < 3); l356 = (l356 + 1)) {
			fRec328[l356] = 0.0f;
			
		}
		for (int l357 = 0; (l357 < 3); l357 = (l357 + 1)) {
			fRec327[l357] = 0.0f;
			
		}
		for (int l358 = 0; (l358 < 3); l358 = (l358 + 1)) {
			fRec326[l358] = 0.0f;
			
		}
		for (int l359 = 0; (l359 < 2); l359 = (l359 + 1)) {
			fRec336[l359] = 0.0f;
			
		}
		for (int l360 = 0; (l360 < 3); l360 = (l360 + 1)) {
			fRec335[l360] = 0.0f;
			
		}
		for (int l361 = 0; (l361 < 2); l361 = (l361 + 1)) {
			fVec44[l361] = 0.0f;
			
		}
		for (int l362 = 0; (l362 < 2); l362 = (l362 + 1)) {
			fRec334[l362] = 0.0f;
			
		}
		for (int l363 = 0; (l363 < 3); l363 = (l363 + 1)) {
			fRec333[l363] = 0.0f;
			
		}
		for (int l364 = 0; (l364 < 3); l364 = (l364 + 1)) {
			fRec332[l364] = 0.0f;
			
		}
		for (int l365 = 0; (l365 < 3); l365 = (l365 + 1)) {
			fRec331[l365] = 0.0f;
			
		}
		for (int l366 = 0; (l366 < 2); l366 = (l366 + 1)) {
			fRec341[l366] = 0.0f;
			
		}
		for (int l367 = 0; (l367 < 3); l367 = (l367 + 1)) {
			fRec340[l367] = 0.0f;
			
		}
		for (int l368 = 0; (l368 < 2); l368 = (l368 + 1)) {
			fVec45[l368] = 0.0f;
			
		}
		for (int l369 = 0; (l369 < 2); l369 = (l369 + 1)) {
			fRec339[l369] = 0.0f;
			
		}
		for (int l370 = 0; (l370 < 3); l370 = (l370 + 1)) {
			fRec338[l370] = 0.0f;
			
		}
		for (int l371 = 0; (l371 < 3); l371 = (l371 + 1)) {
			fRec337[l371] = 0.0f;
			
		}
		for (int l372 = 0; (l372 < 2); l372 = (l372 + 1)) {
			fRec345[l372] = 0.0f;
			
		}
		for (int l373 = 0; (l373 < 3); l373 = (l373 + 1)) {
			fRec344[l373] = 0.0f;
			
		}
		for (int l374 = 0; (l374 < 2); l374 = (l374 + 1)) {
			fVec46[l374] = 0.0f;
			
		}
		for (int l375 = 0; (l375 < 2); l375 = (l375 + 1)) {
			fRec343[l375] = 0.0f;
			
		}
		for (int l376 = 0; (l376 < 3); l376 = (l376 + 1)) {
			fRec342[l376] = 0.0f;
			
		}
		for (int l377 = 0; (l377 < 2); l377 = (l377 + 1)) {
			fRec347[l377] = 0.0f;
			
		}
		for (int l378 = 0; (l378 < 3); l378 = (l378 + 1)) {
			fRec346[l378] = 0.0f;
			
		}
		for (int l379 = 0; (l379 < 2); l379 = (l379 + 1)) {
			fRec352[l379] = 0.0f;
			
		}
		for (int l380 = 0; (l380 < 3); l380 = (l380 + 1)) {
			fRec351[l380] = 0.0f;
			
		}
		for (int l381 = 0; (l381 < 3); l381 = (l381 + 1)) {
			fRec350[l381] = 0.0f;
			
		}
		for (int l382 = 0; (l382 < 3); l382 = (l382 + 1)) {
			fRec349[l382] = 0.0f;
			
		}
		for (int l383 = 0; (l383 < 3); l383 = (l383 + 1)) {
			fRec348[l383] = 0.0f;
			
		}
		for (int l384 = 0; (l384 < 2); l384 = (l384 + 1)) {
			fRec358[l384] = 0.0f;
			
		}
		for (int l385 = 0; (l385 < 3); l385 = (l385 + 1)) {
			fRec357[l385] = 0.0f;
			
		}
		for (int l386 = 0; (l386 < 2); l386 = (l386 + 1)) {
			fVec47[l386] = 0.0f;
			
		}
		for (int l387 = 0; (l387 < 2); l387 = (l387 + 1)) {
			fRec356[l387] = 0.0f;
			
		}
		for (int l388 = 0; (l388 < 3); l388 = (l388 + 1)) {
			fRec355[l388] = 0.0f;
			
		}
		for (int l389 = 0; (l389 < 3); l389 = (l389 + 1)) {
			fRec354[l389] = 0.0f;
			
		}
		for (int l390 = 0; (l390 < 3); l390 = (l390 + 1)) {
			fRec353[l390] = 0.0f;
			
		}
		for (int l391 = 0; (l391 < 2); l391 = (l391 + 1)) {
			fRec363[l391] = 0.0f;
			
		}
		for (int l392 = 0; (l392 < 3); l392 = (l392 + 1)) {
			fRec362[l392] = 0.0f;
			
		}
		for (int l393 = 0; (l393 < 2); l393 = (l393 + 1)) {
			fVec48[l393] = 0.0f;
			
		}
		for (int l394 = 0; (l394 < 2); l394 = (l394 + 1)) {
			fRec361[l394] = 0.0f;
			
		}
		for (int l395 = 0; (l395 < 3); l395 = (l395 + 1)) {
			fRec360[l395] = 0.0f;
			
		}
		for (int l396 = 0; (l396 < 3); l396 = (l396 + 1)) {
			fRec359[l396] = 0.0f;
			
		}
		for (int l397 = 0; (l397 < 2); l397 = (l397 + 1)) {
			fRec367[l397] = 0.0f;
			
		}
		for (int l398 = 0; (l398 < 3); l398 = (l398 + 1)) {
			fRec366[l398] = 0.0f;
			
		}
		for (int l399 = 0; (l399 < 2); l399 = (l399 + 1)) {
			fVec49[l399] = 0.0f;
			
		}
		for (int l400 = 0; (l400 < 2); l400 = (l400 + 1)) {
			fRec365[l400] = 0.0f;
			
		}
		for (int l401 = 0; (l401 < 3); l401 = (l401 + 1)) {
			fRec364[l401] = 0.0f;
			
		}
		for (int l402 = 0; (l402 < 2); l402 = (l402 + 1)) {
			fRec369[l402] = 0.0f;
			
		}
		for (int l403 = 0; (l403 < 3); l403 = (l403 + 1)) {
			fRec368[l403] = 0.0f;
			
		}
		IOTA = 0;
		for (int l404 = 0; (l404 < 16384); l404 = (l404 + 1)) {
			fVec50[l404] = 0.0f;
			
		}
		for (int l405 = 0; (l405 < 3); l405 = (l405 + 1)) {
			fRec0[l405] = 0.0f;
			
		}
		for (int l406 = 0; (l406 < 2); l406 = (l406 + 1)) {
			fVec51[l406] = 0.0f;
			
		}
		for (int l407 = 0; (l407 < 16384); l407 = (l407 + 1)) {
			fVec52[l407] = 0.0f;
			
		}
		for (int l408 = 0; (l408 < 3); l408 = (l408 + 1)) {
			fRec1[l408] = 0.0f;
			
		}
		for (int l409 = 0; (l409 < 16384); l409 = (l409 + 1)) {
			fVec53[l409] = 0.0f;
			
		}
		for (int l410 = 0; (l410 < 3); l410 = (l410 + 1)) {
			fRec2[l410] = 0.0f;
			
		}
		for (int l411 = 0; (l411 < 16384); l411 = (l411 + 1)) {
			fVec54[l411] = 0.0f;
			
		}
		for (int l412 = 0; (l412 < 3); l412 = (l412 + 1)) {
			fRec3[l412] = 0.0f;
			
		}
		for (int l413 = 0; (l413 < 16384); l413 = (l413 + 1)) {
			fVec55[l413] = 0.0f;
			
		}
		for (int l414 = 0; (l414 < 3); l414 = (l414 + 1)) {
			fRec4[l414] = 0.0f;
			
		}
		for (int l415 = 0; (l415 < 16384); l415 = (l415 + 1)) {
			fVec56[l415] = 0.0f;
			
		}
		for (int l416 = 0; (l416 < 3); l416 = (l416 + 1)) {
			fRec5[l416] = 0.0f;
			
		}
		for (int l417 = 0; (l417 < 16384); l417 = (l417 + 1)) {
			fVec57[l417] = 0.0f;
			
		}
		for (int l418 = 0; (l418 < 3); l418 = (l418 + 1)) {
			fRec6[l418] = 0.0f;
			
		}
		for (int l419 = 0; (l419 < 16384); l419 = (l419 + 1)) {
			fVec58[l419] = 0.0f;
			
		}
		for (int l420 = 0; (l420 < 3); l420 = (l420 + 1)) {
			fRec7[l420] = 0.0f;
			
		}
		for (int l421 = 0; (l421 < 16384); l421 = (l421 + 1)) {
			fVec59[l421] = 0.0f;
			
		}
		for (int l422 = 0; (l422 < 3); l422 = (l422 + 1)) {
			fRec8[l422] = 0.0f;
			
		}
		for (int l423 = 0; (l423 < 16384); l423 = (l423 + 1)) {
			fVec60[l423] = 0.0f;
			
		}
		for (int l424 = 0; (l424 < 3); l424 = (l424 + 1)) {
			fRec9[l424] = 0.0f;
			
		}
		for (int l425 = 0; (l425 < 16384); l425 = (l425 + 1)) {
			fVec61[l425] = 0.0f;
			
		}
		for (int l426 = 0; (l426 < 3); l426 = (l426 + 1)) {
			fRec10[l426] = 0.0f;
			
		}
		for (int l427 = 0; (l427 < 16384); l427 = (l427 + 1)) {
			fVec62[l427] = 0.0f;
			
		}
		for (int l428 = 0; (l428 < 3); l428 = (l428 + 1)) {
			fRec11[l428] = 0.0f;
			
		}
		for (int l429 = 0; (l429 < 16384); l429 = (l429 + 1)) {
			fVec63[l429] = 0.0f;
			
		}
		for (int l430 = 0; (l430 < 3); l430 = (l430 + 1)) {
			fRec12[l430] = 0.0f;
			
		}
		for (int l431 = 0; (l431 < 16384); l431 = (l431 + 1)) {
			fVec64[l431] = 0.0f;
			
		}
		for (int l432 = 0; (l432 < 3); l432 = (l432 + 1)) {
			fRec13[l432] = 0.0f;
			
		}
		for (int l433 = 0; (l433 < 16384); l433 = (l433 + 1)) {
			fVec65[l433] = 0.0f;
			
		}
		for (int l434 = 0; (l434 < 3); l434 = (l434 + 1)) {
			fRec14[l434] = 0.0f;
			
		}
		for (int l435 = 0; (l435 < 16384); l435 = (l435 + 1)) {
			fVec66[l435] = 0.0f;
			
		}
		for (int l436 = 0; (l436 < 3); l436 = (l436 + 1)) {
			fRec15[l436] = 0.0f;
			
		}
		
	}
	
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void instanceInit(int samplingFreq) {
		instanceConstants(samplingFreq);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual mydsp* clone() {
		return new mydsp();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;
		
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("reverbDesigner");
		ui_interface->declare(0, "tooltip", "See Faust's reverbs.lib for documentation and references");
		ui_interface->openVerticalBox("FEEDBACK DELAY NETWORK (FDN) REVERBERATOR, ORDER 16");
		ui_interface->declare(0, "1", "");
		ui_interface->openVerticalBox("Band Crossover Frequencies");
		ui_interface->declare(&fHslider6, "0", "");
		ui_interface->declare(&fHslider6, "scale", "log");
		ui_interface->declare(&fHslider6, "tooltip", "Each delay-line signal is split into frequency-bands for separate  decay-time control in each band");
		ui_interface->declare(&fHslider6, "unit", "Hz");
		ui_interface->addHorizontalSlider("Band 0 upper edge in Hz", &fHslider6, 500.0f, 100.0f, 10000.0f, 1.0f);
		ui_interface->declare(&fHslider5, "1", "");
		ui_interface->declare(&fHslider5, "scale", "log");
		ui_interface->declare(&fHslider5, "tooltip", "Each delay-line signal is split into frequency-bands for separate  decay-time control in each band");
		ui_interface->declare(&fHslider5, "unit", "Hz");
		ui_interface->addHorizontalSlider("Band 1 upper edge in Hz", &fHslider5, 1000.0f, 100.0f, 10000.0f, 1.0f);
		ui_interface->declare(&fHslider4, "2", "");
		ui_interface->declare(&fHslider4, "scale", "log");
		ui_interface->declare(&fHslider4, "tooltip", "Each delay-line signal is split into frequency-bands for separate  decay-time control in each band");
		ui_interface->declare(&fHslider4, "unit", "Hz");
		ui_interface->addHorizontalSlider("Band 2 upper edge in Hz", &fHslider4, 2000.0f, 100.0f, 10000.0f, 1.0f);
		ui_interface->declare(&fHslider3, "3", "");
		ui_interface->declare(&fHslider3, "scale", "log");
		ui_interface->declare(&fHslider3, "tooltip", "Each delay-line signal is split into frequency-bands for separate  decay-time control in each band");
		ui_interface->declare(&fHslider3, "unit", "Hz");
		ui_interface->addHorizontalSlider("Band 3 upper edge in Hz", &fHslider3, 4000.0f, 100.0f, 10000.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("Band Decay Times (T60)");
		ui_interface->declare(&fVslider4, "0", "");
		ui_interface->declare(&fVslider4, "scale", "log");
		ui_interface->declare(&fVslider4, "tooltip", "T60 is the 60dB   decay-time in seconds. For concert halls, an overall reverberation time (T60) near   1.9 seconds is typical [Beranek 2004]. Here we may set T60 independently in each   frequency band.  In real rooms, higher frequency bands generally decay faster due   to absorption and scattering.");
		ui_interface->declare(&fVslider4, "unit", "s");
		ui_interface->addVerticalSlider("0", &fVslider4, 8.39999962f, 0.100000001f, 100.0f, 0.100000001f);
		ui_interface->declare(&fVslider3, "1", "");
		ui_interface->declare(&fVslider3, "scale", "log");
		ui_interface->declare(&fVslider3, "tooltip", "T60 is the 60dB   decay-time in seconds. For concert halls, an overall reverberation time (T60) near   1.9 seconds is typical [Beranek 2004]. Here we may set T60 independently in each   frequency band.  In real rooms, higher frequency bands generally decay faster due   to absorption and scattering.");
		ui_interface->declare(&fVslider3, "unit", "s");
		ui_interface->addVerticalSlider("1", &fVslider3, 6.5f, 0.100000001f, 100.0f, 0.100000001f);
		ui_interface->declare(&fVslider2, "2", "");
		ui_interface->declare(&fVslider2, "scale", "log");
		ui_interface->declare(&fVslider2, "tooltip", "T60 is the 60dB   decay-time in seconds. For concert halls, an overall reverberation time (T60) near   1.9 seconds is typical [Beranek 2004]. Here we may set T60 independently in each   frequency band.  In real rooms, higher frequency bands generally decay faster due   to absorption and scattering.");
		ui_interface->declare(&fVslider2, "unit", "s");
		ui_interface->addVerticalSlider("2", &fVslider2, 5.0f, 0.100000001f, 100.0f, 0.100000001f);
		ui_interface->declare(&fVslider1, "3", "");
		ui_interface->declare(&fVslider1, "scale", "log");
		ui_interface->declare(&fVslider1, "tooltip", "T60 is the 60dB   decay-time in seconds. For concert halls, an overall reverberation time (T60) near   1.9 seconds is typical [Beranek 2004]. Here we may set T60 independently in each   frequency band.  In real rooms, higher frequency bands generally decay faster due   to absorption and scattering.");
		ui_interface->declare(&fVslider1, "unit", "s");
		ui_interface->addVerticalSlider("3", &fVslider1, 3.79999995f, 0.100000001f, 100.0f, 0.100000001f);
		ui_interface->declare(&fVslider0, "4", "");
		ui_interface->declare(&fVslider0, "scale", "log");
		ui_interface->declare(&fVslider0, "tooltip", "T60 is the 60dB   decay-time in seconds. For concert halls, an overall reverberation time (T60) near   1.9 seconds is typical [Beranek 2004]. Here we may set T60 independently in each   frequency band.  In real rooms, higher frequency bands generally decay faster due   to absorption and scattering.");
		ui_interface->declare(&fVslider0, "unit", "s");
		ui_interface->addVerticalSlider("4", &fVslider0, 2.70000005f, 0.100000001f, 100.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->declare(0, "3", "");
		ui_interface->openVerticalBox("Room Dimensions");
		ui_interface->declare(&fHslider1, "1", "");
		ui_interface->declare(&fHslider1, "scale", "log");
		ui_interface->declare(&fHslider1, "tooltip", "This length (in meters) determines the shortest delay-line used in the FDN  reverberator. Think of it as the shortest wall-to-wall separation in the room.");
		ui_interface->declare(&fHslider1, "unit", "m");
		ui_interface->addHorizontalSlider("min acoustic ray length", &fHslider1, 46.0f, 0.100000001f, 63.0f, 0.100000001f);
		ui_interface->declare(&fHslider2, "2", "");
		ui_interface->declare(&fHslider2, "scale", "log");
		ui_interface->declare(&fHslider2, "tooltip", "This length (in meters) determines the longest delay-line used in the   FDN reverberator. Think of it as the largest wall-to-wall separation in the room.");
		ui_interface->declare(&fHslider2, "unit", "m");
		ui_interface->addHorizontalSlider("max acoustic ray length", &fHslider2, 63.0f, 0.100000001f, 63.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->declare(0, "4", "");
		ui_interface->openHorizontalBox("Input Controls");
		ui_interface->declare(0, "3", "");
		ui_interface->openVerticalBox("Reverb State");
		ui_interface->declare(&fButton2, "1", "");
		ui_interface->declare(&fButton2, "tooltip", "Hold down 'Quench' to clear the reverberator");
		ui_interface->addButton("Quench", &fButton2);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openVerticalBox("Input Config");
		ui_interface->declare(&fCheckbox1, "1", "");
		ui_interface->declare(&fCheckbox1, "tooltip", "When this is checked, the stereo external audio inputs are   disabled (good for hearing the impulse response or pink-noise response alone)");
		ui_interface->addCheckButton("Mute Ext Inputs", &fCheckbox1);
		ui_interface->declare(&fCheckbox0, "2", "");
		ui_interface->declare(&fCheckbox0, "tooltip", "Pink Noise (or 1/f noise) is Constant-Q Noise (useful for adjusting   the EQ sections)");
		ui_interface->addCheckButton("Pink Noise", &fCheckbox0);
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("Impulse Selection");
		ui_interface->declare(&fButton1, "1", "");
		ui_interface->declare(&fButton1, "tooltip", "Send impulse into LEFT channel");
		ui_interface->addButton("Left", &fButton1);
		ui_interface->declare(&fButton0, "2", "");
		ui_interface->declare(&fButton0, "tooltip", "Send impulse into LEFT and RIGHT channels");
		ui_interface->addButton("Center", &fButton0);
		ui_interface->declare(&fButton3, "3", "");
		ui_interface->declare(&fButton3, "tooltip", "Send impulse into RIGHT channel");
		ui_interface->addButton("Right", &fButton3);
		ui_interface->closeBox();
		ui_interface->declare(&fHslider0, "3", "");
		ui_interface->declare(&fHslider0, "tooltip", "Output scale factor");
		ui_interface->declare(&fHslider0, "unit", "dB");
		ui_interface->addHorizontalSlider("Output Level (dB)", &fHslider0, -40.0f, -70.0f, 20.0f, 0.100000001f);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* input2 = inputs[2];
		FAUSTFLOAT* input3 = inputs[3];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = powf(10.0f, (0.0500000007f * float(fHslider0)));
		float fSlow1 = (0.100000001f * float(fCheckbox0));
		float fSlow2 = float(fButton0);
		float fSlow3 = float(fButton1);
		float fSlow4 = (1.0f - float(fCheckbox1));
		float fSlow5 = (0.25f * (1.0f - (0.5f * float(fButton2))));
		float fSlow6 = float(fHslider1);
		float fSlow7 = (float(fHslider2) / fSlow6);
		float fSlow8 = powf(2.0f, floorf(((1.44269502f * logf((fConst2 * (fSlow6 * powf(fSlow7, 0.0f))))) + 0.5f)));
		float fSlow9 = (0.0f - (6.90775537f * fSlow8));
		float fSlow10 = float(fVslider0);
		float fSlow11 = expf((fConst1 * (fSlow9 / fSlow10)));
		float fSlow12 = tanf((fConst3 * float(fHslider3)));
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
		float fSlow24 = tanf((fConst3 * float(fHslider4)));
		float fSlow25 = (1.0f / fSlow24);
		float fSlow26 = (1.0f / (((fSlow25 + 1.0f) / fSlow24) + 1.0f));
		float fSlow27 = (1.0f - ((1.0f - fSlow25) / fSlow24));
		float fSlow28 = (1.0f / mydsp_faustpower2_f(fSlow24));
		float fSlow29 = (2.0f * (1.0f - fSlow28));
		float fSlow30 = tanf((fConst3 * float(fHslider5)));
		float fSlow31 = (1.0f / fSlow30);
		float fSlow32 = (1.0f / (((fSlow31 + 1.0f) / fSlow30) + 1.0f));
		float fSlow33 = (1.0f - ((1.0f - fSlow31) / fSlow30));
		float fSlow34 = (1.0f / mydsp_faustpower2_f(fSlow30));
		float fSlow35 = (2.0f * (1.0f - fSlow34));
		float fSlow36 = tanf((fConst3 * float(fHslider6)));
		float fSlow37 = (1.0f / fSlow36);
		float fSlow38 = (1.0f / (((fSlow37 + 1.0f) / fSlow36) + 1.0f));
		float fSlow39 = (1.0f - ((1.0f - fSlow37) / fSlow36));
		float fSlow40 = (1.0f / mydsp_faustpower2_f(fSlow36));
		float fSlow41 = (2.0f * (1.0f - fSlow40));
		float fSlow42 = float(fVslider1);
		float fSlow43 = expf((fConst1 * (fSlow9 / fSlow42)));
		float fSlow44 = (((fSlow25 + 1.0f) / fSlow24) + 1.0f);
		float fSlow45 = (1.0f / fSlow44);
		float fSlow46 = (fSlow25 + 1.0f);
		float fSlow47 = (0.0f - ((1.0f - fSlow25) / fSlow46));
		float fSlow48 = (1.0f / fSlow46);
		float fSlow49 = (0.0f - fSlow25);
		float fSlow50 = (1.0f / (fSlow14 * fSlow24));
		float fSlow51 = (((fSlow25 + -1.0f) / fSlow24) + 1.0f);
		float fSlow52 = (2.0f * (0.0f - fSlow28));
		float fSlow53 = float(fVslider2);
		float fSlow54 = expf((fConst1 * (fSlow9 / fSlow53)));
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
		float fSlow65 = float(fVslider3);
		float fSlow66 = expf((fConst1 * (fSlow9 / fSlow65)));
		float fSlow67 = (fSlow37 + 1.0f);
		float fSlow68 = (0.0f - ((1.0f - fSlow37) / fSlow67));
		float fSlow69 = (1.0f / fSlow67);
		float fSlow70 = (0.0f - fSlow37);
		float fSlow71 = (1.0f / (fSlow55 * fSlow36));
		float fSlow72 = (((fSlow37 + -1.0f) / fSlow36) + 1.0f);
		float fSlow73 = (2.0f * (0.0f - fSlow40));
		float fSlow74 = float(fVslider4);
		float fSlow75 = expf((fConst1 * (fSlow9 / fSlow74)));
		float fSlow76 = powf(23.0f, floorf(((0.318928987f * logf((fConst2 * (fSlow6 * powf(fSlow7, 0.533333361f))))) + 0.5f)));
		float fSlow77 = (0.0f - (6.90775537f * fSlow76));
		float fSlow78 = expf((fConst1 * (fSlow77 / fSlow10)));
		float fSlow79 = expf((fConst1 * (fSlow77 / fSlow42)));
		float fSlow80 = expf((fConst1 * (fSlow77 / fSlow53)));
		float fSlow81 = expf((fConst1 * (fSlow77 / fSlow65)));
		float fSlow82 = expf((fConst1 * (fSlow77 / fSlow74)));
		float fSlow83 = powf(11.0f, floorf(((0.417032391f * logf((fConst2 * (fSlow6 * powf(fSlow7, 0.266666681f))))) + 0.5f)));
		float fSlow84 = (0.0f - (6.90775537f * fSlow83));
		float fSlow85 = expf((fConst1 * (fSlow84 / fSlow10)));
		float fSlow86 = expf((fConst1 * (fSlow84 / fSlow42)));
		float fSlow87 = expf((fConst1 * (fSlow84 / fSlow53)));
		float fSlow88 = expf((fConst1 * (fSlow84 / fSlow65)));
		float fSlow89 = expf((fConst1 * (fSlow84 / fSlow74)));
		float fSlow90 = powf(41.0f, floorf(((0.26928252f * logf((fConst2 * (fSlow6 * powf(fSlow7, 0.800000012f))))) + 0.5f)));
		float fSlow91 = (0.0f - (6.90775537f * fSlow90));
		float fSlow92 = expf((fConst1 * (fSlow91 / fSlow10)));
		float fSlow93 = expf((fConst1 * (fSlow91 / fSlow42)));
		float fSlow94 = expf((fConst1 * (fSlow91 / fSlow53)));
		float fSlow95 = expf((fConst1 * (fSlow91 / fSlow65)));
		float fSlow96 = expf((fConst1 * (fSlow91 / fSlow74)));
		float fSlow97 = powf(5.0f, floorf(((0.62133491f * logf((fConst2 * (fSlow6 * powf(fSlow7, 0.13333334f))))) + 0.5f)));
		float fSlow98 = (0.0f - (6.90775537f * fSlow97));
		float fSlow99 = expf((fConst1 * (fSlow98 / fSlow10)));
		float fSlow100 = expf((fConst1 * (fSlow98 / fSlow42)));
		float fSlow101 = expf((fConst1 * (fSlow98 / fSlow53)));
		float fSlow102 = expf((fConst1 * (fSlow98 / fSlow65)));
		float fSlow103 = expf((fConst1 * (fSlow98 / fSlow74)));
		float fSlow104 = powf(31.0f, floorf(((0.291206688f * logf((fConst2 * (fSlow6 * powf(fSlow7, 0.666666687f))))) + 0.5f)));
		float fSlow105 = (0.0f - (6.90775537f * fSlow104));
		float fSlow106 = expf((fConst1 * (fSlow105 / fSlow10)));
		float fSlow107 = expf((fConst1 * (fSlow105 / fSlow42)));
		float fSlow108 = expf((fConst1 * (fSlow105 / fSlow53)));
		float fSlow109 = expf((fConst1 * (fSlow105 / fSlow65)));
		float fSlow110 = expf((fConst1 * (fSlow105 / fSlow74)));
		float fSlow111 = powf(17.0f, floorf(((0.352956116f * logf((fConst2 * (fSlow6 * powf(fSlow7, 0.400000006f))))) + 0.5f)));
		float fSlow112 = (0.0f - (6.90775537f * fSlow111));
		float fSlow113 = expf((fConst1 * (fSlow112 / fSlow10)));
		float fSlow114 = expf((fConst1 * (fSlow112 / fSlow42)));
		float fSlow115 = expf((fConst1 * (fSlow112 / fSlow53)));
		float fSlow116 = expf((fConst1 * (fSlow112 / fSlow65)));
		float fSlow117 = expf((fConst1 * (fSlow112 / fSlow74)));
		float fSlow118 = powf(47.0f, floorf(((0.259730309f * logf((fConst2 * (fSlow6 * powf(fSlow7, 0.933333337f))))) + 0.5f)));
		float fSlow119 = (0.0f - (6.90775537f * fSlow118));
		float fSlow120 = expf((fConst1 * (fSlow119 / fSlow10)));
		float fSlow121 = expf((fConst1 * (fSlow119 / fSlow42)));
		float fSlow122 = expf((fConst1 * (fSlow119 / fSlow53)));
		float fSlow123 = expf((fConst1 * (fSlow119 / fSlow65)));
		float fSlow124 = expf((fConst1 * (fSlow119 / fSlow74)));
		float fSlow125 = powf(3.0f, floorf(((0.91023922f * logf((fConst2 * (fSlow6 * powf(fSlow7, 0.0666666701f))))) + 0.5f)));
		float fSlow126 = (0.0f - (6.90775537f * fSlow125));
		float fSlow127 = expf((fConst1 * (fSlow126 / fSlow10)));
		float fSlow128 = expf((fConst1 * (fSlow126 / fSlow42)));
		float fSlow129 = expf((fConst1 * (fSlow126 / fSlow53)));
		float fSlow130 = expf((fConst1 * (fSlow126 / fSlow65)));
		float fSlow131 = expf((fConst1 * (fSlow126 / fSlow74)));
		float fSlow132 = powf(29.0f, floorf(((0.296974212f * logf((fConst2 * (fSlow6 * powf(fSlow7, 0.600000024f))))) + 0.5f)));
		float fSlow133 = (0.0f - (6.90775537f * fSlow132));
		float fSlow134 = expf((fConst1 * (fSlow133 / fSlow10)));
		float fSlow135 = expf((fConst1 * (fSlow133 / fSlow42)));
		float fSlow136 = expf((fConst1 * (fSlow133 / fSlow53)));
		float fSlow137 = expf((fConst1 * (fSlow133 / fSlow65)));
		float fSlow138 = expf((fConst1 * (fSlow133 / fSlow74)));
		float fSlow139 = powf(13.0f, floorf(((0.38987124f * logf((fConst2 * (fSlow6 * powf(fSlow7, 0.333333343f))))) + 0.5f)));
		float fSlow140 = (0.0f - (6.90775537f * fSlow139));
		float fSlow141 = expf((fConst1 * (fSlow140 / fSlow10)));
		float fSlow142 = expf((fConst1 * (fSlow140 / fSlow42)));
		float fSlow143 = expf((fConst1 * (fSlow140 / fSlow53)));
		float fSlow144 = expf((fConst1 * (fSlow140 / fSlow65)));
		float fSlow145 = expf((fConst1 * (fSlow140 / fSlow74)));
		float fSlow146 = powf(43.0f, floorf(((0.265872598f * logf((fConst2 * (fSlow6 * powf(fSlow7, 0.866666675f))))) + 0.5f)));
		float fSlow147 = (0.0f - (6.90775537f * fSlow146));
		float fSlow148 = expf((fConst1 * (fSlow147 / fSlow10)));
		float fSlow149 = expf((fConst1 * (fSlow147 / fSlow42)));
		float fSlow150 = expf((fConst1 * (fSlow147 / fSlow53)));
		float fSlow151 = expf((fConst1 * (fSlow147 / fSlow65)));
		float fSlow152 = expf((fConst1 * (fSlow147 / fSlow74)));
		float fSlow153 = powf(7.0f, floorf(((0.513898313f * logf((fConst2 * (fSlow6 * powf(fSlow7, 0.200000003f))))) + 0.5f)));
		float fSlow154 = (0.0f - (6.90775537f * fSlow153));
		float fSlow155 = expf((fConst1 * (fSlow154 / fSlow10)));
		float fSlow156 = expf((fConst1 * (fSlow154 / fSlow42)));
		float fSlow157 = expf((fConst1 * (fSlow154 / fSlow53)));
		float fSlow158 = expf((fConst1 * (fSlow154 / fSlow65)));
		float fSlow159 = expf((fConst1 * (fSlow154 / fSlow74)));
		float fSlow160 = powf(37.0f, floorf(((0.276937902f * logf((fConst2 * (fSlow6 * powf(fSlow7, 0.733333349f))))) + 0.5f)));
		float fSlow161 = (0.0f - (6.90775537f * fSlow160));
		float fSlow162 = expf((fConst1 * (fSlow161 / fSlow10)));
		float fSlow163 = expf((fConst1 * (fSlow161 / fSlow42)));
		float fSlow164 = expf((fConst1 * (fSlow161 / fSlow53)));
		float fSlow165 = expf((fConst1 * (fSlow161 / fSlow65)));
		float fSlow166 = expf((fConst1 * (fSlow161 / fSlow74)));
		float fSlow167 = powf(19.0f, floorf(((0.339623272f * logf((fConst2 * (fSlow6 * powf(fSlow7, 0.466666669f))))) + 0.5f)));
		float fSlow168 = (0.0f - (6.90775537f * fSlow167));
		float fSlow169 = expf((fConst1 * (fSlow168 / fSlow10)));
		float fSlow170 = expf((fConst1 * (fSlow168 / fSlow42)));
		float fSlow171 = expf((fConst1 * (fSlow168 / fSlow53)));
		float fSlow172 = expf((fConst1 * (fSlow168 / fSlow65)));
		float fSlow173 = expf((fConst1 * (fSlow168 / fSlow74)));
		float fSlow174 = powf(53.0f, floorf(((0.251870662f * logf((fConst2 * (fSlow6 * powf(fSlow7, 1.0f))))) + 0.5f)));
		float fSlow175 = (0.0f - (6.90775537f * fSlow174));
		float fSlow176 = expf((fConst1 * (fSlow175 / fSlow10)));
		float fSlow177 = expf((fConst1 * (fSlow175 / fSlow42)));
		float fSlow178 = expf((fConst1 * (fSlow175 / fSlow53)));
		float fSlow179 = expf((fConst1 * (fSlow175 / fSlow65)));
		float fSlow180 = expf((fConst1 * (fSlow175 / fSlow74)));
		int iSlow181 = int(min(8192.0f, max(0.0f, (fSlow8 + -1.0f))));
		float fSlow182 = float(fButton3);
		int iSlow183 = int(min(8192.0f, max(0.0f, (fSlow125 + -1.0f))));
		int iSlow184 = int(min(8192.0f, max(0.0f, (fSlow97 + -1.0f))));
		int iSlow185 = int(min(8192.0f, max(0.0f, (fSlow153 + -1.0f))));
		int iSlow186 = int(min(8192.0f, max(0.0f, (fSlow83 + -1.0f))));
		int iSlow187 = int(min(8192.0f, max(0.0f, (fSlow139 + -1.0f))));
		int iSlow188 = int(min(8192.0f, max(0.0f, (fSlow111 + -1.0f))));
		int iSlow189 = int(min(8192.0f, max(0.0f, (fSlow167 + -1.0f))));
		int iSlow190 = int(min(8192.0f, max(0.0f, (fSlow76 + -1.0f))));
		int iSlow191 = int(min(8192.0f, max(0.0f, (fSlow132 + -1.0f))));
		int iSlow192 = int(min(8192.0f, max(0.0f, (fSlow104 + -1.0f))));
		int iSlow193 = int(min(8192.0f, max(0.0f, (fSlow160 + -1.0f))));
		int iSlow194 = int(min(8192.0f, max(0.0f, (fSlow90 + -1.0f))));
		int iSlow195 = int(min(8192.0f, max(0.0f, (fSlow146 + -1.0f))));
		int iSlow196 = int(min(8192.0f, max(0.0f, (fSlow118 + -1.0f))));
		int iSlow197 = int(min(8192.0f, max(0.0f, (fSlow174 + -1.0f))));
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec17[0] = ((1103515245 * iRec17[1]) + 12345);
			fRec16[0] = (((0.522189379f * fRec16[3]) + ((4.65661287e-10f * float(iRec17[0])) + (2.49495602f * fRec16[1]))) - (2.0172658f * fRec16[2]));
			float fTemp0 = (fSlow1 * (((0.0499220341f * fRec16[0]) + (0.0506126992f * fRec16[2])) - ((0.0959935337f * fRec16[1]) + (0.00440878607f * fRec16[3]))));
			fVec0[0] = fSlow2;
			int iTemp1 = ((fSlow2 - fVec0[1]) > 0.0f);
			fVec1[0] = fSlow3;
			int iTemp2 = ((fSlow3 - fVec1[1]) > 0.0f);
			float fTemp3 = (fSlow4 * float(input2[i]));
			fRec22[0] = ((fSlow18 * fRec22[1]) + (fSlow19 * ((fSlow13 * fRec0[1]) + (fSlow20 * fRec0[2]))));
			fRec21[0] = (fRec22[0] - (fSlow15 * ((fSlow21 * fRec21[1]) + (fSlow22 * fRec21[2]))));
			float fTemp4 = (fSlow29 * fRec20[1]);
			fRec20[0] = ((fSlow15 * (((fSlow16 * fRec21[0]) + (fSlow23 * fRec21[1])) + (fSlow16 * fRec21[2]))) - (fSlow26 * ((fSlow27 * fRec20[2]) + fTemp4)));
			float fTemp5 = (fSlow35 * fRec19[1]);
			fRec19[0] = ((fRec20[2] + (fSlow26 * (fTemp4 + (fSlow27 * fRec20[0])))) - (fSlow32 * ((fSlow33 * fRec19[2]) + fTemp5)));
			float fTemp6 = (fSlow41 * fRec18[1]);
			fRec18[0] = ((fRec19[2] + (fSlow32 * (fTemp5 + (fSlow33 * fRec19[0])))) - (fSlow38 * ((fSlow39 * fRec18[2]) + fTemp6)));
			fRec28[0] = ((fSlow18 * fRec28[1]) + (fSlow19 * (fRec0[1] + fRec0[2])));
			fRec27[0] = (fRec28[0] - (fSlow15 * ((fSlow21 * fRec27[1]) + (fSlow22 * fRec27[2]))));
			float fTemp7 = (fRec27[2] + (fRec27[0] + (2.0f * fRec27[1])));
			float fTemp8 = (fSlow15 * fTemp7);
			fVec2[0] = fTemp8;
			fRec26[0] = ((fSlow47 * fRec26[1]) + (fSlow48 * ((fSlow49 * fVec2[1]) + (fSlow50 * fTemp7))));
			fRec25[0] = (fRec26[0] - (fSlow45 * ((fSlow29 * fRec25[1]) + (fSlow51 * fRec25[2]))));
			float fTemp9 = (fSlow35 * fRec24[1]);
			fRec24[0] = ((fSlow45 * (((fSlow28 * fRec25[0]) + (fSlow52 * fRec25[1])) + (fSlow28 * fRec25[2]))) - (fSlow32 * (fTemp9 + (fSlow33 * fRec24[2]))));
			float fTemp10 = (fSlow41 * fRec23[1]);
			fRec23[0] = ((fRec24[2] + (fSlow32 * (fTemp9 + (fSlow33 * fRec24[0])))) - (fSlow38 * (fTemp10 + (fSlow39 * fRec23[2]))));
			fRec33[0] = ((fSlow47 * fRec33[1]) + (fSlow48 * (fTemp8 + fVec2[1])));
			fRec32[0] = (fRec33[0] - (fSlow45 * ((fSlow29 * fRec32[1]) + (fSlow51 * fRec32[2]))));
			float fTemp11 = (fRec32[2] + (fRec32[0] + (2.0f * fRec32[1])));
			float fTemp12 = (fSlow45 * fTemp11);
			fVec3[0] = fTemp12;
			fRec31[0] = ((fSlow58 * fRec31[1]) + (fSlow59 * ((fSlow60 * fVec3[1]) + (fSlow61 * fTemp11))));
			fRec30[0] = (fRec31[0] - (fSlow56 * ((fSlow35 * fRec30[1]) + (fSlow62 * fRec30[2]))));
			float fTemp13 = (fSlow41 * fRec29[1]);
			fRec29[0] = ((fSlow56 * (((fSlow34 * fRec30[0]) + (fSlow63 * fRec30[1])) + (fSlow34 * fRec30[2]))) - (fSlow38 * (fTemp13 + (fSlow39 * fRec29[2]))));
			fRec37[0] = ((fSlow58 * fRec37[1]) + (fSlow59 * (fTemp12 + fVec3[1])));
			fRec36[0] = (fRec37[0] - (fSlow56 * ((fSlow35 * fRec36[1]) + (fSlow62 * fRec36[2]))));
			float fTemp14 = (fRec36[2] + (fRec36[0] + (2.0f * fRec36[1])));
			float fTemp15 = (fSlow56 * fTemp14);
			fVec4[0] = fTemp15;
			fRec35[0] = ((fSlow68 * fRec35[1]) + (fSlow69 * ((fSlow70 * fVec4[1]) + (fSlow71 * fTemp14))));
			fRec34[0] = (fRec35[0] - (fSlow64 * ((fSlow41 * fRec34[1]) + (fSlow72 * fRec34[2]))));
			fRec39[0] = ((fSlow68 * fRec39[1]) + (fSlow69 * (fTemp15 + fVec4[1])));
			fRec38[0] = (fRec39[0] - (fSlow64 * ((fSlow41 * fRec38[1]) + (fSlow72 * fRec38[2]))));
			float fTemp16 = ((((fSlow11 * (fRec18[2] + (fSlow38 * (fTemp6 + (fSlow39 * fRec18[0]))))) + (fSlow43 * (fRec23[2] + (fSlow38 * (fTemp10 + (fSlow39 * fRec23[0])))))) + (fSlow54 * (fRec29[2] + (fSlow38 * (fTemp13 + (fSlow39 * fRec29[0])))))) + (fSlow64 * ((fSlow66 * (((fSlow40 * fRec34[0]) + (fSlow73 * fRec34[1])) + (fSlow40 * fRec34[2]))) + (fSlow75 * (fRec38[2] + (fRec38[0] + (2.0f * fRec38[1])))))));
			fRec44[0] = ((fSlow18 * fRec44[1]) + (fSlow19 * ((fSlow13 * fRec8[1]) + (fSlow20 * fRec8[2]))));
			fRec43[0] = (fRec44[0] - (fSlow15 * ((fSlow21 * fRec43[1]) + (fSlow22 * fRec43[2]))));
			float fTemp17 = (fSlow29 * fRec42[1]);
			fRec42[0] = ((fSlow15 * (((fSlow16 * fRec43[0]) + (fSlow23 * fRec43[1])) + (fSlow16 * fRec43[2]))) - (fSlow26 * (fTemp17 + (fSlow27 * fRec42[2]))));
			float fTemp18 = (fSlow35 * fRec41[1]);
			fRec41[0] = ((fRec42[2] + (fSlow26 * (fTemp17 + (fSlow27 * fRec42[0])))) - (fSlow32 * (fTemp18 + (fSlow33 * fRec41[2]))));
			float fTemp19 = (fSlow41 * fRec40[1]);
			fRec40[0] = ((fRec41[2] + (fSlow32 * (fTemp18 + (fSlow33 * fRec41[0])))) - (fSlow38 * (fTemp19 + (fSlow39 * fRec40[2]))));
			fRec50[0] = ((fSlow18 * fRec50[1]) + (fSlow19 * (fRec8[1] + fRec8[2])));
			fRec49[0] = (fRec50[0] - (fSlow15 * ((fSlow21 * fRec49[1]) + (fSlow22 * fRec49[2]))));
			float fTemp20 = (fRec49[2] + (fRec49[0] + (2.0f * fRec49[1])));
			float fTemp21 = (fSlow15 * fTemp20);
			fVec5[0] = fTemp21;
			fRec48[0] = ((fSlow47 * fRec48[1]) + (fSlow48 * ((fSlow49 * fVec5[1]) + (fSlow50 * fTemp20))));
			fRec47[0] = (fRec48[0] - (fSlow45 * ((fSlow29 * fRec47[1]) + (fSlow51 * fRec47[2]))));
			float fTemp22 = (fSlow35 * fRec46[1]);
			fRec46[0] = ((fSlow45 * (((fSlow28 * fRec47[0]) + (fSlow52 * fRec47[1])) + (fSlow28 * fRec47[2]))) - (fSlow32 * (fTemp22 + (fSlow33 * fRec46[2]))));
			float fTemp23 = (fSlow41 * fRec45[1]);
			fRec45[0] = ((fRec46[2] + (fSlow32 * (fTemp22 + (fSlow33 * fRec46[0])))) - (fSlow38 * (fTemp23 + (fSlow39 * fRec45[2]))));
			fRec55[0] = ((fSlow47 * fRec55[1]) + (fSlow48 * (fVec5[1] + fTemp21)));
			fRec54[0] = (fRec55[0] - (fSlow45 * ((fSlow29 * fRec54[1]) + (fSlow51 * fRec54[2]))));
			float fTemp24 = (fRec54[2] + (fRec54[0] + (2.0f * fRec54[1])));
			float fTemp25 = (fSlow45 * fTemp24);
			fVec6[0] = fTemp25;
			fRec53[0] = ((fSlow58 * fRec53[1]) + (fSlow59 * ((fSlow60 * fVec6[1]) + (fSlow61 * fTemp24))));
			fRec52[0] = (fRec53[0] - (fSlow56 * ((fSlow35 * fRec52[1]) + (fSlow62 * fRec52[2]))));
			float fTemp26 = (fSlow41 * fRec51[1]);
			fRec51[0] = ((fSlow56 * (((fSlow34 * fRec52[0]) + (fSlow63 * fRec52[1])) + (fSlow34 * fRec52[2]))) - (fSlow38 * (fTemp26 + (fSlow39 * fRec51[2]))));
			fRec59[0] = ((fSlow58 * fRec59[1]) + (fSlow59 * (fVec6[1] + fTemp25)));
			fRec58[0] = (fRec59[0] - (fSlow56 * ((fSlow35 * fRec58[1]) + (fSlow62 * fRec58[2]))));
			float fTemp27 = (fRec58[2] + (fRec58[0] + (2.0f * fRec58[1])));
			float fTemp28 = (fSlow56 * fTemp27);
			fVec7[0] = fTemp28;
			fRec57[0] = ((fSlow68 * fRec57[1]) + (fSlow69 * ((fSlow70 * fVec7[1]) + (fSlow71 * fTemp27))));
			fRec56[0] = (fRec57[0] - (fSlow64 * ((fSlow41 * fRec56[1]) + (fSlow72 * fRec56[2]))));
			fRec61[0] = ((fSlow68 * fRec61[1]) + (fSlow69 * (fVec7[1] + fTemp28)));
			fRec60[0] = (fRec61[0] - (fSlow64 * ((fSlow41 * fRec60[1]) + (fSlow72 * fRec60[2]))));
			float fTemp29 = ((((fSlow78 * (fRec40[2] + (fSlow38 * (fTemp19 + (fSlow39 * fRec40[0]))))) + (fSlow79 * (fRec45[2] + (fSlow38 * (fTemp23 + (fSlow39 * fRec45[0])))))) + (fSlow80 * (fRec51[2] + (fSlow38 * (fTemp26 + (fSlow39 * fRec51[0])))))) + (fSlow64 * ((fSlow81 * (((fSlow40 * fRec56[0]) + (fSlow73 * fRec56[1])) + (fSlow40 * fRec56[2]))) + (fSlow82 * (fRec60[2] + (fRec60[0] + (2.0f * fRec60[1])))))));
			float fTemp30 = (fTemp16 + fTemp29);
			fRec66[0] = ((fSlow18 * fRec66[1]) + (fSlow19 * ((fSlow13 * fRec4[1]) + (fSlow20 * fRec4[2]))));
			fRec65[0] = (fRec66[0] - (fSlow15 * ((fSlow21 * fRec65[1]) + (fSlow22 * fRec65[2]))));
			float fTemp31 = (fSlow29 * fRec64[1]);
			fRec64[0] = ((fSlow15 * (((fSlow16 * fRec65[0]) + (fSlow23 * fRec65[1])) + (fSlow16 * fRec65[2]))) - (fSlow26 * (fTemp31 + (fSlow27 * fRec64[2]))));
			float fTemp32 = (fSlow35 * fRec63[1]);
			fRec63[0] = ((fRec64[2] + (fSlow26 * (fTemp31 + (fSlow27 * fRec64[0])))) - (fSlow32 * (fTemp32 + (fSlow33 * fRec63[2]))));
			float fTemp33 = (fSlow41 * fRec62[1]);
			fRec62[0] = ((fRec63[2] + (fSlow32 * (fTemp32 + (fSlow33 * fRec63[0])))) - (fSlow38 * (fTemp33 + (fSlow39 * fRec62[2]))));
			fRec72[0] = ((fSlow18 * fRec72[1]) + (fSlow19 * (fRec4[1] + fRec4[2])));
			fRec71[0] = (fRec72[0] - (fSlow15 * ((fSlow21 * fRec71[1]) + (fSlow22 * fRec71[2]))));
			float fTemp34 = (fRec71[2] + (fRec71[0] + (2.0f * fRec71[1])));
			float fTemp35 = (fSlow15 * fTemp34);
			fVec8[0] = fTemp35;
			fRec70[0] = ((fSlow47 * fRec70[1]) + (fSlow48 * ((fSlow49 * fVec8[1]) + (fSlow50 * fTemp34))));
			fRec69[0] = (fRec70[0] - (fSlow45 * ((fSlow29 * fRec69[1]) + (fSlow51 * fRec69[2]))));
			float fTemp36 = (fSlow35 * fRec68[1]);
			fRec68[0] = ((fSlow45 * (((fSlow28 * fRec69[0]) + (fSlow52 * fRec69[1])) + (fSlow28 * fRec69[2]))) - (fSlow32 * (fTemp36 + (fSlow33 * fRec68[2]))));
			float fTemp37 = (fSlow41 * fRec67[1]);
			fRec67[0] = ((fRec68[2] + (fSlow32 * (fTemp36 + (fSlow33 * fRec68[0])))) - (fSlow38 * (fTemp37 + (fSlow39 * fRec67[2]))));
			fRec77[0] = ((fSlow47 * fRec77[1]) + (fSlow48 * (fVec8[1] + fTemp35)));
			fRec76[0] = (fRec77[0] - (fSlow45 * ((fSlow29 * fRec76[1]) + (fSlow51 * fRec76[2]))));
			float fTemp38 = (fRec76[2] + (fRec76[0] + (2.0f * fRec76[1])));
			float fTemp39 = (fSlow45 * fTemp38);
			fVec9[0] = fTemp39;
			fRec75[0] = ((fSlow58 * fRec75[1]) + (fSlow59 * ((fSlow60 * fVec9[1]) + (fSlow61 * fTemp38))));
			fRec74[0] = (fRec75[0] - (fSlow56 * ((fSlow35 * fRec74[1]) + (fSlow62 * fRec74[2]))));
			float fTemp40 = (fSlow41 * fRec73[1]);
			fRec73[0] = ((fSlow56 * (((fSlow34 * fRec74[0]) + (fSlow63 * fRec74[1])) + (fSlow34 * fRec74[2]))) - (fSlow38 * (fTemp40 + (fSlow39 * fRec73[2]))));
			fRec81[0] = ((fSlow58 * fRec81[1]) + (fSlow59 * (fVec9[1] + fTemp39)));
			fRec80[0] = (fRec81[0] - (fSlow56 * ((fSlow35 * fRec80[1]) + (fSlow62 * fRec80[2]))));
			float fTemp41 = (fRec80[2] + (fRec80[0] + (2.0f * fRec80[1])));
			float fTemp42 = (fSlow56 * fTemp41);
			fVec10[0] = fTemp42;
			fRec79[0] = ((fSlow68 * fRec79[1]) + (fSlow69 * ((fSlow70 * fVec10[1]) + (fSlow71 * fTemp41))));
			fRec78[0] = (fRec79[0] - (fSlow64 * ((fSlow41 * fRec78[1]) + (fSlow72 * fRec78[2]))));
			fRec83[0] = ((fSlow68 * fRec83[1]) + (fSlow69 * (fVec10[1] + fTemp42)));
			fRec82[0] = (fRec83[0] - (fSlow64 * ((fSlow41 * fRec82[1]) + (fSlow72 * fRec82[2]))));
			float fTemp43 = ((((fSlow85 * (fRec62[2] + (fSlow38 * (fTemp33 + (fSlow39 * fRec62[0]))))) + (fSlow86 * (fRec67[2] + (fSlow38 * (fTemp37 + (fSlow39 * fRec67[0])))))) + (fSlow87 * (fRec73[2] + (fSlow38 * (fTemp40 + (fSlow39 * fRec73[0])))))) + (fSlow64 * ((fSlow88 * (((fSlow40 * fRec78[0]) + (fSlow73 * fRec78[1])) + (fSlow40 * fRec78[2]))) + (fSlow89 * (fRec82[2] + (fRec82[0] + (2.0f * fRec82[1])))))));
			fRec88[0] = ((fSlow18 * fRec88[1]) + (fSlow19 * ((fSlow13 * fRec12[1]) + (fSlow20 * fRec12[2]))));
			fRec87[0] = (fRec88[0] - (fSlow15 * ((fSlow21 * fRec87[1]) + (fSlow22 * fRec87[2]))));
			float fTemp44 = (fSlow29 * fRec86[1]);
			fRec86[0] = ((fSlow15 * (((fSlow16 * fRec87[0]) + (fSlow23 * fRec87[1])) + (fSlow16 * fRec87[2]))) - (fSlow26 * (fTemp44 + (fSlow27 * fRec86[2]))));
			float fTemp45 = (fSlow35 * fRec85[1]);
			fRec85[0] = ((fRec86[2] + (fSlow26 * (fTemp44 + (fSlow27 * fRec86[0])))) - (fSlow32 * (fTemp45 + (fSlow33 * fRec85[2]))));
			float fTemp46 = (fSlow41 * fRec84[1]);
			fRec84[0] = ((fRec85[2] + (fSlow32 * (fTemp45 + (fSlow33 * fRec85[0])))) - (fSlow38 * (fTemp46 + (fSlow39 * fRec84[2]))));
			fRec94[0] = ((fSlow18 * fRec94[1]) + (fSlow19 * (fRec12[1] + fRec12[2])));
			fRec93[0] = (fRec94[0] - (fSlow15 * ((fSlow21 * fRec93[1]) + (fSlow22 * fRec93[2]))));
			float fTemp47 = (fRec93[2] + (fRec93[0] + (2.0f * fRec93[1])));
			float fTemp48 = (fSlow15 * fTemp47);
			fVec11[0] = fTemp48;
			fRec92[0] = ((fSlow47 * fRec92[1]) + (fSlow48 * ((fSlow49 * fVec11[1]) + (fSlow50 * fTemp47))));
			fRec91[0] = (fRec92[0] - (fSlow45 * ((fSlow29 * fRec91[1]) + (fSlow51 * fRec91[2]))));
			float fTemp49 = (fSlow35 * fRec90[1]);
			fRec90[0] = ((fSlow45 * (((fSlow28 * fRec91[0]) + (fSlow52 * fRec91[1])) + (fSlow28 * fRec91[2]))) - (fSlow32 * (fTemp49 + (fSlow33 * fRec90[2]))));
			float fTemp50 = (fSlow41 * fRec89[1]);
			fRec89[0] = ((fRec90[2] + (fSlow32 * (fTemp49 + (fSlow33 * fRec90[0])))) - (fSlow38 * (fTemp50 + (fSlow39 * fRec89[2]))));
			fRec99[0] = ((fSlow47 * fRec99[1]) + (fSlow48 * (fVec11[1] + fTemp48)));
			fRec98[0] = (fRec99[0] - (fSlow45 * ((fSlow29 * fRec98[1]) + (fSlow51 * fRec98[2]))));
			float fTemp51 = (fRec98[2] + (fRec98[0] + (2.0f * fRec98[1])));
			float fTemp52 = (fSlow45 * fTemp51);
			fVec12[0] = fTemp52;
			fRec97[0] = ((fSlow58 * fRec97[1]) + (fSlow59 * ((fSlow60 * fVec12[1]) + (fSlow61 * fTemp51))));
			fRec96[0] = (fRec97[0] - (fSlow56 * ((fSlow35 * fRec96[1]) + (fSlow62 * fRec96[2]))));
			float fTemp53 = (fSlow41 * fRec95[1]);
			fRec95[0] = ((fSlow56 * (((fSlow34 * fRec96[0]) + (fSlow63 * fRec96[1])) + (fSlow34 * fRec96[2]))) - (fSlow38 * (fTemp53 + (fSlow39 * fRec95[2]))));
			fRec103[0] = ((fSlow58 * fRec103[1]) + (fSlow59 * (fVec12[1] + fTemp52)));
			fRec102[0] = (fRec103[0] - (fSlow56 * ((fSlow35 * fRec102[1]) + (fSlow62 * fRec102[2]))));
			float fTemp54 = (fRec102[2] + (fRec102[0] + (2.0f * fRec102[1])));
			float fTemp55 = (fSlow56 * fTemp54);
			fVec13[0] = fTemp55;
			fRec101[0] = ((fSlow68 * fRec101[1]) + (fSlow69 * ((fSlow70 * fVec13[1]) + (fSlow71 * fTemp54))));
			fRec100[0] = (fRec101[0] - (fSlow64 * ((fSlow41 * fRec100[1]) + (fSlow72 * fRec100[2]))));
			fRec105[0] = ((fSlow68 * fRec105[1]) + (fSlow69 * (fVec13[1] + fTemp55)));
			fRec104[0] = (fRec105[0] - (fSlow64 * ((fSlow41 * fRec104[1]) + (fSlow72 * fRec104[2]))));
			float fTemp56 = ((((fSlow92 * (fRec84[2] + (fSlow38 * (fTemp46 + (fSlow39 * fRec84[0]))))) + (fSlow93 * (fRec89[2] + (fSlow38 * (fTemp50 + (fSlow39 * fRec89[0])))))) + (fSlow94 * (fRec95[2] + (fSlow38 * (fTemp53 + (fSlow39 * fRec95[0])))))) + (fSlow64 * ((fSlow95 * (((fSlow40 * fRec100[0]) + (fSlow73 * fRec100[1])) + (fSlow40 * fRec100[2]))) + (fSlow96 * (fRec104[2] + (fRec104[0] + (2.0f * fRec104[1])))))));
			float fTemp57 = (fTemp43 + fTemp56);
			float fTemp58 = (fTemp30 + fTemp57);
			fRec110[0] = ((fSlow18 * fRec110[1]) + (fSlow19 * ((fSlow13 * fRec2[1]) + (fSlow20 * fRec2[2]))));
			fRec109[0] = (fRec110[0] - (fSlow15 * ((fSlow21 * fRec109[1]) + (fSlow22 * fRec109[2]))));
			float fTemp59 = (fSlow29 * fRec108[1]);
			fRec108[0] = ((fSlow15 * (((fSlow16 * fRec109[0]) + (fSlow23 * fRec109[1])) + (fSlow16 * fRec109[2]))) - (fSlow26 * (fTemp59 + (fSlow27 * fRec108[2]))));
			float fTemp60 = (fSlow35 * fRec107[1]);
			fRec107[0] = ((fRec108[2] + (fSlow26 * (fTemp59 + (fSlow27 * fRec108[0])))) - (fSlow32 * (fTemp60 + (fSlow33 * fRec107[2]))));
			float fTemp61 = (fSlow41 * fRec106[1]);
			fRec106[0] = ((fRec107[2] + (fSlow32 * (fTemp60 + (fSlow33 * fRec107[0])))) - (fSlow38 * (fTemp61 + (fSlow39 * fRec106[2]))));
			fRec116[0] = ((fSlow18 * fRec116[1]) + (fSlow19 * (fRec2[1] + fRec2[2])));
			fRec115[0] = (fRec116[0] - (fSlow15 * ((fSlow21 * fRec115[1]) + (fSlow22 * fRec115[2]))));
			float fTemp62 = (fRec115[2] + (fRec115[0] + (2.0f * fRec115[1])));
			float fTemp63 = (fSlow15 * fTemp62);
			fVec14[0] = fTemp63;
			fRec114[0] = ((fSlow47 * fRec114[1]) + (fSlow48 * ((fSlow49 * fVec14[1]) + (fSlow50 * fTemp62))));
			fRec113[0] = (fRec114[0] - (fSlow45 * ((fSlow29 * fRec113[1]) + (fSlow51 * fRec113[2]))));
			float fTemp64 = (fSlow35 * fRec112[1]);
			fRec112[0] = ((fSlow45 * (((fSlow28 * fRec113[0]) + (fSlow52 * fRec113[1])) + (fSlow28 * fRec113[2]))) - (fSlow32 * (fTemp64 + (fSlow33 * fRec112[2]))));
			float fTemp65 = (fSlow41 * fRec111[1]);
			fRec111[0] = ((fRec112[2] + (fSlow32 * (fTemp64 + (fSlow33 * fRec112[0])))) - (fSlow38 * (fTemp65 + (fSlow39 * fRec111[2]))));
			fRec121[0] = ((fSlow47 * fRec121[1]) + (fSlow48 * (fVec14[1] + fTemp63)));
			fRec120[0] = (fRec121[0] - (fSlow45 * ((fSlow29 * fRec120[1]) + (fSlow51 * fRec120[2]))));
			float fTemp66 = (fRec120[2] + (fRec120[0] + (2.0f * fRec120[1])));
			float fTemp67 = (fSlow45 * fTemp66);
			fVec15[0] = fTemp67;
			fRec119[0] = ((fSlow58 * fRec119[1]) + (fSlow59 * ((fSlow60 * fVec15[1]) + (fSlow61 * fTemp66))));
			fRec118[0] = (fRec119[0] - (fSlow56 * ((fSlow35 * fRec118[1]) + (fSlow62 * fRec118[2]))));
			float fTemp68 = (fSlow41 * fRec117[1]);
			fRec117[0] = ((fSlow56 * (((fSlow34 * fRec118[0]) + (fSlow63 * fRec118[1])) + (fSlow34 * fRec118[2]))) - (fSlow38 * (fTemp68 + (fSlow39 * fRec117[2]))));
			fRec125[0] = ((fSlow58 * fRec125[1]) + (fSlow59 * (fVec15[1] + fTemp67)));
			fRec124[0] = (fRec125[0] - (fSlow56 * ((fSlow35 * fRec124[1]) + (fSlow62 * fRec124[2]))));
			float fTemp69 = (fRec124[2] + (fRec124[0] + (2.0f * fRec124[1])));
			float fTemp70 = (fSlow56 * fTemp69);
			fVec16[0] = fTemp70;
			fRec123[0] = ((fSlow68 * fRec123[1]) + (fSlow69 * ((fSlow70 * fVec16[1]) + (fSlow71 * fTemp69))));
			fRec122[0] = (fRec123[0] - (fSlow64 * ((fSlow41 * fRec122[1]) + (fSlow72 * fRec122[2]))));
			fRec127[0] = ((fSlow68 * fRec127[1]) + (fSlow69 * (fVec16[1] + fTemp70)));
			fRec126[0] = (fRec127[0] - (fSlow64 * ((fSlow41 * fRec126[1]) + (fSlow72 * fRec126[2]))));
			float fTemp71 = ((((fSlow99 * (fRec106[2] + (fSlow38 * (fTemp61 + (fSlow39 * fRec106[0]))))) + (fSlow100 * (fRec111[2] + (fSlow38 * (fTemp65 + (fSlow39 * fRec111[0])))))) + (fSlow101 * (fRec117[2] + (fSlow38 * (fTemp68 + (fSlow39 * fRec117[0])))))) + (fSlow64 * ((fSlow102 * (((fSlow40 * fRec122[0]) + (fSlow73 * fRec122[1])) + (fSlow40 * fRec122[2]))) + (fSlow103 * (fRec126[2] + (fRec126[0] + (2.0f * fRec126[1])))))));
			fRec132[0] = ((fSlow18 * fRec132[1]) + (fSlow19 * ((fSlow13 * fRec10[1]) + (fSlow20 * fRec10[2]))));
			fRec131[0] = (fRec132[0] - (fSlow15 * ((fSlow21 * fRec131[1]) + (fSlow22 * fRec131[2]))));
			float fTemp72 = (fSlow29 * fRec130[1]);
			fRec130[0] = ((fSlow15 * (((fSlow16 * fRec131[0]) + (fSlow23 * fRec131[1])) + (fSlow16 * fRec131[2]))) - (fSlow26 * (fTemp72 + (fSlow27 * fRec130[2]))));
			float fTemp73 = (fSlow35 * fRec129[1]);
			fRec129[0] = ((fRec130[2] + (fSlow26 * (fTemp72 + (fSlow27 * fRec130[0])))) - (fSlow32 * (fTemp73 + (fSlow33 * fRec129[2]))));
			float fTemp74 = (fSlow41 * fRec128[1]);
			fRec128[0] = ((fRec129[2] + (fSlow32 * (fTemp73 + (fSlow33 * fRec129[0])))) - (fSlow38 * (fTemp74 + (fSlow39 * fRec128[2]))));
			fRec138[0] = ((fSlow18 * fRec138[1]) + (fSlow19 * (fRec10[1] + fRec10[2])));
			fRec137[0] = (fRec138[0] - (fSlow15 * ((fSlow21 * fRec137[1]) + (fSlow22 * fRec137[2]))));
			float fTemp75 = (fRec137[2] + (fRec137[0] + (2.0f * fRec137[1])));
			float fTemp76 = (fSlow15 * fTemp75);
			fVec17[0] = fTemp76;
			fRec136[0] = ((fSlow47 * fRec136[1]) + (fSlow48 * ((fSlow49 * fVec17[1]) + (fSlow50 * fTemp75))));
			fRec135[0] = (fRec136[0] - (fSlow45 * ((fSlow29 * fRec135[1]) + (fSlow51 * fRec135[2]))));
			float fTemp77 = (fSlow35 * fRec134[1]);
			fRec134[0] = ((fSlow45 * (((fSlow28 * fRec135[0]) + (fSlow52 * fRec135[1])) + (fSlow28 * fRec135[2]))) - (fSlow32 * (fTemp77 + (fSlow33 * fRec134[2]))));
			float fTemp78 = (fSlow41 * fRec133[1]);
			fRec133[0] = ((fRec134[2] + (fSlow32 * (fTemp77 + (fSlow33 * fRec134[0])))) - (fSlow38 * (fTemp78 + (fSlow39 * fRec133[2]))));
			fRec143[0] = ((fSlow47 * fRec143[1]) + (fSlow48 * (fVec17[1] + fTemp76)));
			fRec142[0] = (fRec143[0] - (fSlow45 * ((fSlow29 * fRec142[1]) + (fSlow51 * fRec142[2]))));
			float fTemp79 = (fRec142[2] + (fRec142[0] + (2.0f * fRec142[1])));
			float fTemp80 = (fSlow45 * fTemp79);
			fVec18[0] = fTemp80;
			fRec141[0] = ((fSlow58 * fRec141[1]) + (fSlow59 * ((fSlow60 * fVec18[1]) + (fSlow61 * fTemp79))));
			fRec140[0] = (fRec141[0] - (fSlow56 * ((fSlow35 * fRec140[1]) + (fSlow62 * fRec140[2]))));
			float fTemp81 = (fSlow41 * fRec139[1]);
			fRec139[0] = ((fSlow56 * (((fSlow34 * fRec140[0]) + (fSlow63 * fRec140[1])) + (fSlow34 * fRec140[2]))) - (fSlow38 * (fTemp81 + (fSlow39 * fRec139[2]))));
			fRec147[0] = ((fSlow58 * fRec147[1]) + (fSlow59 * (fVec18[1] + fTemp80)));
			fRec146[0] = (fRec147[0] - (fSlow56 * ((fSlow35 * fRec146[1]) + (fSlow62 * fRec146[2]))));
			float fTemp82 = (fRec146[2] + (fRec146[0] + (2.0f * fRec146[1])));
			float fTemp83 = (fSlow56 * fTemp82);
			fVec19[0] = fTemp83;
			fRec145[0] = ((fSlow68 * fRec145[1]) + (fSlow69 * ((fSlow70 * fVec19[1]) + (fSlow71 * fTemp82))));
			fRec144[0] = (fRec145[0] - (fSlow64 * ((fSlow41 * fRec144[1]) + (fSlow72 * fRec144[2]))));
			fRec149[0] = ((fSlow68 * fRec149[1]) + (fSlow69 * (fVec19[1] + fTemp83)));
			fRec148[0] = (fRec149[0] - (fSlow64 * ((fSlow41 * fRec148[1]) + (fSlow72 * fRec148[2]))));
			float fTemp84 = ((((fSlow106 * (fRec128[2] + (fSlow38 * (fTemp74 + (fSlow39 * fRec128[0]))))) + (fSlow107 * (fRec133[2] + (fSlow38 * (fTemp78 + (fSlow39 * fRec133[0])))))) + (fSlow108 * (fRec139[2] + (fSlow38 * (fTemp81 + (fSlow39 * fRec139[0])))))) + (fSlow64 * ((fSlow109 * (((fSlow40 * fRec144[0]) + (fSlow73 * fRec144[1])) + (fSlow40 * fRec144[2]))) + (fSlow110 * (fRec148[2] + (fRec148[0] + (2.0f * fRec148[1])))))));
			float fTemp85 = (fTemp71 + fTemp84);
			fRec154[0] = ((fSlow18 * fRec154[1]) + (fSlow19 * ((fSlow13 * fRec6[1]) + (fSlow20 * fRec6[2]))));
			fRec153[0] = (fRec154[0] - (fSlow15 * ((fSlow21 * fRec153[1]) + (fSlow22 * fRec153[2]))));
			float fTemp86 = (fSlow29 * fRec152[1]);
			fRec152[0] = ((fSlow15 * (((fSlow16 * fRec153[0]) + (fSlow23 * fRec153[1])) + (fSlow16 * fRec153[2]))) - (fSlow26 * (fTemp86 + (fSlow27 * fRec152[2]))));
			float fTemp87 = (fSlow35 * fRec151[1]);
			fRec151[0] = ((fRec152[2] + (fSlow26 * (fTemp86 + (fSlow27 * fRec152[0])))) - (fSlow32 * (fTemp87 + (fSlow33 * fRec151[2]))));
			float fTemp88 = (fSlow41 * fRec150[1]);
			fRec150[0] = ((fRec151[2] + (fSlow32 * (fTemp87 + (fSlow33 * fRec151[0])))) - (fSlow38 * (fTemp88 + (fSlow39 * fRec150[2]))));
			fRec160[0] = ((fSlow18 * fRec160[1]) + (fSlow19 * (fRec6[1] + fRec6[2])));
			fRec159[0] = (fRec160[0] - (fSlow15 * ((fSlow21 * fRec159[1]) + (fSlow22 * fRec159[2]))));
			float fTemp89 = (fRec159[2] + (fRec159[0] + (2.0f * fRec159[1])));
			float fTemp90 = (fSlow15 * fTemp89);
			fVec20[0] = fTemp90;
			fRec158[0] = ((fSlow47 * fRec158[1]) + (fSlow48 * ((fSlow49 * fVec20[1]) + (fSlow50 * fTemp89))));
			fRec157[0] = (fRec158[0] - (fSlow45 * ((fSlow29 * fRec157[1]) + (fSlow51 * fRec157[2]))));
			float fTemp91 = (fSlow35 * fRec156[1]);
			fRec156[0] = ((fSlow45 * (((fSlow28 * fRec157[0]) + (fSlow52 * fRec157[1])) + (fSlow28 * fRec157[2]))) - (fSlow32 * (fTemp91 + (fSlow33 * fRec156[2]))));
			float fTemp92 = (fSlow41 * fRec155[1]);
			fRec155[0] = ((fRec156[2] + (fSlow32 * (fTemp91 + (fSlow33 * fRec156[0])))) - (fSlow38 * (fTemp92 + (fSlow39 * fRec155[2]))));
			fRec165[0] = ((fSlow47 * fRec165[1]) + (fSlow48 * (fVec20[1] + fTemp90)));
			fRec164[0] = (fRec165[0] - (fSlow45 * ((fSlow29 * fRec164[1]) + (fSlow51 * fRec164[2]))));
			float fTemp93 = (fRec164[2] + (fRec164[0] + (2.0f * fRec164[1])));
			float fTemp94 = (fSlow45 * fTemp93);
			fVec21[0] = fTemp94;
			fRec163[0] = ((fSlow58 * fRec163[1]) + (fSlow59 * ((fSlow60 * fVec21[1]) + (fSlow61 * fTemp93))));
			fRec162[0] = (fRec163[0] - (fSlow56 * ((fSlow35 * fRec162[1]) + (fSlow62 * fRec162[2]))));
			float fTemp95 = (fSlow41 * fRec161[1]);
			fRec161[0] = ((fSlow56 * (((fSlow34 * fRec162[0]) + (fSlow63 * fRec162[1])) + (fSlow34 * fRec162[2]))) - (fSlow38 * (fTemp95 + (fSlow39 * fRec161[2]))));
			fRec169[0] = ((fSlow58 * fRec169[1]) + (fSlow59 * (fVec21[1] + fTemp94)));
			fRec168[0] = (fRec169[0] - (fSlow56 * ((fSlow35 * fRec168[1]) + (fSlow62 * fRec168[2]))));
			float fTemp96 = (fRec168[2] + (fRec168[0] + (2.0f * fRec168[1])));
			float fTemp97 = (fSlow56 * fTemp96);
			fVec22[0] = fTemp97;
			fRec167[0] = ((fSlow68 * fRec167[1]) + (fSlow69 * ((fSlow70 * fVec22[1]) + (fSlow71 * fTemp96))));
			fRec166[0] = (fRec167[0] - (fSlow64 * ((fSlow41 * fRec166[1]) + (fSlow72 * fRec166[2]))));
			fRec171[0] = ((fSlow68 * fRec171[1]) + (fSlow69 * (fVec22[1] + fTemp97)));
			fRec170[0] = (fRec171[0] - (fSlow64 * ((fSlow41 * fRec170[1]) + (fSlow72 * fRec170[2]))));
			float fTemp98 = ((((fSlow113 * (fRec150[2] + (fSlow38 * (fTemp88 + (fSlow39 * fRec150[0]))))) + (fSlow114 * (fRec155[2] + (fSlow38 * (fTemp92 + (fSlow39 * fRec155[0])))))) + (fSlow115 * (fRec161[2] + (fSlow38 * (fTemp95 + (fSlow39 * fRec161[0])))))) + (fSlow64 * ((fSlow116 * (((fSlow40 * fRec166[0]) + (fSlow73 * fRec166[1])) + (fSlow40 * fRec166[2]))) + (fSlow117 * (fRec170[2] + (fRec170[0] + (2.0f * fRec170[1])))))));
			fRec176[0] = ((fSlow18 * fRec176[1]) + (fSlow19 * ((fSlow13 * fRec14[1]) + (fSlow20 * fRec14[2]))));
			fRec175[0] = (fRec176[0] - (fSlow15 * ((fSlow21 * fRec175[1]) + (fSlow22 * fRec175[2]))));
			float fTemp99 = (fSlow29 * fRec174[1]);
			fRec174[0] = ((fSlow15 * (((fSlow16 * fRec175[0]) + (fSlow23 * fRec175[1])) + (fSlow16 * fRec175[2]))) - (fSlow26 * (fTemp99 + (fSlow27 * fRec174[2]))));
			float fTemp100 = (fSlow35 * fRec173[1]);
			fRec173[0] = ((fRec174[2] + (fSlow26 * (fTemp99 + (fSlow27 * fRec174[0])))) - (fSlow32 * (fTemp100 + (fSlow33 * fRec173[2]))));
			float fTemp101 = (fSlow41 * fRec172[1]);
			fRec172[0] = ((fRec173[2] + (fSlow32 * (fTemp100 + (fSlow33 * fRec173[0])))) - (fSlow38 * (fTemp101 + (fSlow39 * fRec172[2]))));
			fRec182[0] = ((fSlow18 * fRec182[1]) + (fSlow19 * (fRec14[1] + fRec14[2])));
			fRec181[0] = (fRec182[0] - (fSlow15 * ((fSlow21 * fRec181[1]) + (fSlow22 * fRec181[2]))));
			float fTemp102 = (fRec181[2] + (fRec181[0] + (2.0f * fRec181[1])));
			float fTemp103 = (fSlow15 * fTemp102);
			fVec23[0] = fTemp103;
			fRec180[0] = ((fSlow47 * fRec180[1]) + (fSlow48 * ((fSlow49 * fVec23[1]) + (fSlow50 * fTemp102))));
			fRec179[0] = (fRec180[0] - (fSlow45 * ((fSlow29 * fRec179[1]) + (fSlow51 * fRec179[2]))));
			float fTemp104 = (fSlow35 * fRec178[1]);
			fRec178[0] = ((fSlow45 * (((fSlow28 * fRec179[0]) + (fSlow52 * fRec179[1])) + (fSlow28 * fRec179[2]))) - (fSlow32 * (fTemp104 + (fSlow33 * fRec178[2]))));
			float fTemp105 = (fSlow41 * fRec177[1]);
			fRec177[0] = ((fRec178[2] + (fSlow32 * (fTemp104 + (fSlow33 * fRec178[0])))) - (fSlow38 * (fTemp105 + (fSlow39 * fRec177[2]))));
			fRec187[0] = ((fSlow47 * fRec187[1]) + (fSlow48 * (fVec23[1] + fTemp103)));
			fRec186[0] = (fRec187[0] - (fSlow45 * ((fSlow29 * fRec186[1]) + (fSlow51 * fRec186[2]))));
			float fTemp106 = (fRec186[2] + (fRec186[0] + (2.0f * fRec186[1])));
			float fTemp107 = (fSlow45 * fTemp106);
			fVec24[0] = fTemp107;
			fRec185[0] = ((fSlow58 * fRec185[1]) + (fSlow59 * ((fSlow60 * fVec24[1]) + (fSlow61 * fTemp106))));
			fRec184[0] = (fRec185[0] - (fSlow56 * ((fSlow35 * fRec184[1]) + (fSlow62 * fRec184[2]))));
			float fTemp108 = (fSlow41 * fRec183[1]);
			fRec183[0] = ((fSlow56 * (((fSlow34 * fRec184[0]) + (fSlow63 * fRec184[1])) + (fSlow34 * fRec184[2]))) - (fSlow38 * (fTemp108 + (fSlow39 * fRec183[2]))));
			fRec191[0] = ((fSlow58 * fRec191[1]) + (fSlow59 * (fVec24[1] + fTemp107)));
			fRec190[0] = (fRec191[0] - (fSlow56 * ((fSlow35 * fRec190[1]) + (fSlow62 * fRec190[2]))));
			float fTemp109 = (fRec190[2] + (fRec190[0] + (2.0f * fRec190[1])));
			float fTemp110 = (fSlow56 * fTemp109);
			fVec25[0] = fTemp110;
			fRec189[0] = ((fSlow68 * fRec189[1]) + (fSlow69 * ((fSlow70 * fVec25[1]) + (fSlow71 * fTemp109))));
			fRec188[0] = (fRec189[0] - (fSlow64 * ((fSlow41 * fRec188[1]) + (fSlow72 * fRec188[2]))));
			fRec193[0] = ((fSlow68 * fRec193[1]) + (fSlow69 * (fVec25[1] + fTemp110)));
			fRec192[0] = (fRec193[0] - (fSlow64 * ((fSlow41 * fRec192[1]) + (fSlow72 * fRec192[2]))));
			float fTemp111 = ((((fSlow120 * (fRec172[2] + (fSlow38 * (fTemp101 + (fSlow39 * fRec172[0]))))) + (fSlow121 * (fRec177[2] + (fSlow38 * (fTemp105 + (fSlow39 * fRec177[0])))))) + (fSlow122 * (fRec183[2] + (fSlow38 * (fTemp108 + (fSlow39 * fRec183[0])))))) + (fSlow64 * ((fSlow123 * (((fSlow40 * fRec188[0]) + (fSlow73 * fRec188[1])) + (fSlow40 * fRec188[2]))) + (fSlow124 * (fRec192[2] + (fRec192[0] + (2.0f * fRec192[1])))))));
			float fTemp112 = (fTemp98 + fTemp111);
			float fTemp113 = (fTemp85 + fTemp112);
			float fTemp114 = (fTemp58 + fTemp113);
			fRec198[0] = ((fSlow18 * fRec198[1]) + (fSlow19 * ((fSlow13 * fRec1[1]) + (fSlow20 * fRec1[2]))));
			fRec197[0] = (fRec198[0] - (fSlow15 * ((fSlow21 * fRec197[1]) + (fSlow22 * fRec197[2]))));
			float fTemp115 = (fSlow29 * fRec196[1]);
			fRec196[0] = ((fSlow15 * (((fSlow16 * fRec197[0]) + (fSlow23 * fRec197[1])) + (fSlow16 * fRec197[2]))) - (fSlow26 * (fTemp115 + (fSlow27 * fRec196[2]))));
			float fTemp116 = (fSlow35 * fRec195[1]);
			fRec195[0] = ((fRec196[2] + (fSlow26 * (fTemp115 + (fSlow27 * fRec196[0])))) - (fSlow32 * (fTemp116 + (fSlow33 * fRec195[2]))));
			float fTemp117 = (fSlow41 * fRec194[1]);
			fRec194[0] = ((fRec195[2] + (fSlow32 * (fTemp116 + (fSlow33 * fRec195[0])))) - (fSlow38 * (fTemp117 + (fSlow39 * fRec194[2]))));
			fRec204[0] = ((fSlow18 * fRec204[1]) + (fSlow19 * (fRec1[1] + fRec1[2])));
			fRec203[0] = (fRec204[0] - (fSlow15 * ((fSlow21 * fRec203[1]) + (fSlow22 * fRec203[2]))));
			float fTemp118 = (fRec203[2] + (fRec203[0] + (2.0f * fRec203[1])));
			float fTemp119 = (fSlow15 * fTemp118);
			fVec26[0] = fTemp119;
			fRec202[0] = ((fSlow47 * fRec202[1]) + (fSlow48 * ((fSlow49 * fVec26[1]) + (fSlow50 * fTemp118))));
			fRec201[0] = (fRec202[0] - (fSlow45 * ((fSlow29 * fRec201[1]) + (fSlow51 * fRec201[2]))));
			float fTemp120 = (fSlow35 * fRec200[1]);
			fRec200[0] = ((fSlow45 * (((fSlow28 * fRec201[0]) + (fSlow52 * fRec201[1])) + (fSlow28 * fRec201[2]))) - (fSlow32 * (fTemp120 + (fSlow33 * fRec200[2]))));
			float fTemp121 = (fSlow41 * fRec199[1]);
			fRec199[0] = ((fRec200[2] + (fSlow32 * (fTemp120 + (fSlow33 * fRec200[0])))) - (fSlow38 * (fTemp121 + (fSlow39 * fRec199[2]))));
			fRec209[0] = ((fSlow47 * fRec209[1]) + (fSlow48 * (fVec26[1] + fTemp119)));
			fRec208[0] = (fRec209[0] - (fSlow45 * ((fSlow29 * fRec208[1]) + (fSlow51 * fRec208[2]))));
			float fTemp122 = (fRec208[2] + (fRec208[0] + (2.0f * fRec208[1])));
			float fTemp123 = (fSlow45 * fTemp122);
			fVec27[0] = fTemp123;
			fRec207[0] = ((fSlow58 * fRec207[1]) + (fSlow59 * ((fSlow60 * fVec27[1]) + (fSlow61 * fTemp122))));
			fRec206[0] = (fRec207[0] - (fSlow56 * ((fSlow35 * fRec206[1]) + (fSlow62 * fRec206[2]))));
			float fTemp124 = (fSlow41 * fRec205[1]);
			fRec205[0] = ((fSlow56 * (((fSlow34 * fRec206[0]) + (fSlow63 * fRec206[1])) + (fSlow34 * fRec206[2]))) - (fSlow38 * (fTemp124 + (fSlow39 * fRec205[2]))));
			fRec213[0] = ((fSlow58 * fRec213[1]) + (fSlow59 * (fVec27[1] + fTemp123)));
			fRec212[0] = (fRec213[0] - (fSlow56 * ((fSlow35 * fRec212[1]) + (fSlow62 * fRec212[2]))));
			float fTemp125 = (fRec212[2] + (fRec212[0] + (2.0f * fRec212[1])));
			float fTemp126 = (fSlow56 * fTemp125);
			fVec28[0] = fTemp126;
			fRec211[0] = ((fSlow68 * fRec211[1]) + (fSlow69 * ((fSlow70 * fVec28[1]) + (fSlow71 * fTemp125))));
			fRec210[0] = (fRec211[0] - (fSlow64 * ((fSlow41 * fRec210[1]) + (fSlow72 * fRec210[2]))));
			fRec215[0] = ((fSlow68 * fRec215[1]) + (fSlow69 * (fVec28[1] + fTemp126)));
			fRec214[0] = (fRec215[0] - (fSlow64 * ((fSlow41 * fRec214[1]) + (fSlow72 * fRec214[2]))));
			float fTemp127 = ((((fSlow127 * (fRec194[2] + (fSlow38 * (fTemp117 + (fSlow39 * fRec194[0]))))) + (fSlow128 * (fRec199[2] + (fSlow38 * (fTemp121 + (fSlow39 * fRec199[0])))))) + (fSlow129 * (fRec205[2] + (fSlow38 * (fTemp124 + (fSlow39 * fRec205[0])))))) + (fSlow64 * ((fSlow130 * (((fSlow40 * fRec210[0]) + (fSlow73 * fRec210[1])) + (fSlow40 * fRec210[2]))) + (fSlow131 * (fRec214[2] + (fRec214[0] + (2.0f * fRec214[1])))))));
			fRec220[0] = ((fSlow18 * fRec220[1]) + (fSlow19 * ((fSlow13 * fRec9[1]) + (fSlow20 * fRec9[2]))));
			fRec219[0] = (fRec220[0] - (fSlow15 * ((fSlow21 * fRec219[1]) + (fSlow22 * fRec219[2]))));
			float fTemp128 = (fSlow29 * fRec218[1]);
			fRec218[0] = ((fSlow15 * (((fSlow16 * fRec219[0]) + (fSlow23 * fRec219[1])) + (fSlow16 * fRec219[2]))) - (fSlow26 * (fTemp128 + (fSlow27 * fRec218[2]))));
			float fTemp129 = (fSlow35 * fRec217[1]);
			fRec217[0] = ((fRec218[2] + (fSlow26 * (fTemp128 + (fSlow27 * fRec218[0])))) - (fSlow32 * (fTemp129 + (fSlow33 * fRec217[2]))));
			float fTemp130 = (fSlow41 * fRec216[1]);
			fRec216[0] = ((fRec217[2] + (fSlow32 * (fTemp129 + (fSlow33 * fRec217[0])))) - (fSlow38 * (fTemp130 + (fSlow39 * fRec216[2]))));
			fRec226[0] = ((fSlow18 * fRec226[1]) + (fSlow19 * (fRec9[1] + fRec9[2])));
			fRec225[0] = (fRec226[0] - (fSlow15 * ((fSlow21 * fRec225[1]) + (fSlow22 * fRec225[2]))));
			float fTemp131 = (fRec225[2] + (fRec225[0] + (2.0f * fRec225[1])));
			float fTemp132 = (fSlow15 * fTemp131);
			fVec29[0] = fTemp132;
			fRec224[0] = ((fSlow47 * fRec224[1]) + (fSlow48 * ((fSlow49 * fVec29[1]) + (fSlow50 * fTemp131))));
			fRec223[0] = (fRec224[0] - (fSlow45 * ((fSlow29 * fRec223[1]) + (fSlow51 * fRec223[2]))));
			float fTemp133 = (fSlow35 * fRec222[1]);
			fRec222[0] = ((fSlow45 * (((fSlow28 * fRec223[0]) + (fSlow52 * fRec223[1])) + (fSlow28 * fRec223[2]))) - (fSlow32 * (fTemp133 + (fSlow33 * fRec222[2]))));
			float fTemp134 = (fSlow41 * fRec221[1]);
			fRec221[0] = ((fRec222[2] + (fSlow32 * (fTemp133 + (fSlow33 * fRec222[0])))) - (fSlow38 * (fTemp134 + (fSlow39 * fRec221[2]))));
			fRec231[0] = ((fSlow47 * fRec231[1]) + (fSlow48 * (fVec29[1] + fTemp132)));
			fRec230[0] = (fRec231[0] - (fSlow45 * ((fSlow29 * fRec230[1]) + (fSlow51 * fRec230[2]))));
			float fTemp135 = (fRec230[2] + (fRec230[0] + (2.0f * fRec230[1])));
			float fTemp136 = (fSlow45 * fTemp135);
			fVec30[0] = fTemp136;
			fRec229[0] = ((fSlow58 * fRec229[1]) + (fSlow59 * ((fSlow60 * fVec30[1]) + (fSlow61 * fTemp135))));
			fRec228[0] = (fRec229[0] - (fSlow56 * ((fSlow35 * fRec228[1]) + (fSlow62 * fRec228[2]))));
			float fTemp137 = (fSlow41 * fRec227[1]);
			fRec227[0] = ((fSlow56 * (((fSlow34 * fRec228[0]) + (fSlow63 * fRec228[1])) + (fSlow34 * fRec228[2]))) - (fSlow38 * (fTemp137 + (fSlow39 * fRec227[2]))));
			fRec235[0] = ((fSlow58 * fRec235[1]) + (fSlow59 * (fVec30[1] + fTemp136)));
			fRec234[0] = (fRec235[0] - (fSlow56 * ((fSlow35 * fRec234[1]) + (fSlow62 * fRec234[2]))));
			float fTemp138 = (fRec234[2] + (fRec234[0] + (2.0f * fRec234[1])));
			float fTemp139 = (fSlow56 * fTemp138);
			fVec31[0] = fTemp139;
			fRec233[0] = ((fSlow68 * fRec233[1]) + (fSlow69 * ((fSlow70 * fVec31[1]) + (fSlow71 * fTemp138))));
			fRec232[0] = (fRec233[0] - (fSlow64 * ((fSlow41 * fRec232[1]) + (fSlow72 * fRec232[2]))));
			fRec237[0] = ((fSlow68 * fRec237[1]) + (fSlow69 * (fVec31[1] + fTemp139)));
			fRec236[0] = (fRec237[0] - (fSlow64 * ((fSlow41 * fRec236[1]) + (fSlow72 * fRec236[2]))));
			float fTemp140 = ((((fSlow134 * (fRec216[2] + (fSlow38 * (fTemp130 + (fSlow39 * fRec216[0]))))) + (fSlow135 * (fRec221[2] + (fSlow38 * (fTemp134 + (fSlow39 * fRec221[0])))))) + (fSlow136 * (fRec227[2] + (fSlow38 * (fTemp137 + (fSlow39 * fRec227[0])))))) + (fSlow64 * ((fSlow137 * (((fSlow40 * fRec232[0]) + (fSlow73 * fRec232[1])) + (fSlow40 * fRec232[2]))) + (fSlow138 * (fRec236[2] + (fRec236[0] + (2.0f * fRec236[1])))))));
			float fTemp141 = (fTemp127 + fTemp140);
			fRec242[0] = ((fSlow18 * fRec242[1]) + (fSlow19 * ((fSlow13 * fRec5[1]) + (fSlow20 * fRec5[2]))));
			fRec241[0] = (fRec242[0] - (fSlow15 * ((fSlow21 * fRec241[1]) + (fSlow22 * fRec241[2]))));
			float fTemp142 = (fSlow29 * fRec240[1]);
			fRec240[0] = ((fSlow15 * (((fSlow16 * fRec241[0]) + (fSlow23 * fRec241[1])) + (fSlow16 * fRec241[2]))) - (fSlow26 * (fTemp142 + (fSlow27 * fRec240[2]))));
			float fTemp143 = (fSlow35 * fRec239[1]);
			fRec239[0] = ((fRec240[2] + (fSlow26 * (fTemp142 + (fSlow27 * fRec240[0])))) - (fSlow32 * (fTemp143 + (fSlow33 * fRec239[2]))));
			float fTemp144 = (fSlow41 * fRec238[1]);
			fRec238[0] = ((fRec239[2] + (fSlow32 * (fTemp143 + (fSlow33 * fRec239[0])))) - (fSlow38 * (fTemp144 + (fSlow39 * fRec238[2]))));
			fRec248[0] = ((fSlow18 * fRec248[1]) + (fSlow19 * (fRec5[1] + fRec5[2])));
			fRec247[0] = (fRec248[0] - (fSlow15 * ((fSlow21 * fRec247[1]) + (fSlow22 * fRec247[2]))));
			float fTemp145 = (fRec247[2] + (fRec247[0] + (2.0f * fRec247[1])));
			float fTemp146 = (fSlow15 * fTemp145);
			fVec32[0] = fTemp146;
			fRec246[0] = ((fSlow47 * fRec246[1]) + (fSlow48 * ((fSlow49 * fVec32[1]) + (fSlow50 * fTemp145))));
			fRec245[0] = (fRec246[0] - (fSlow45 * ((fSlow29 * fRec245[1]) + (fSlow51 * fRec245[2]))));
			float fTemp147 = (fSlow35 * fRec244[1]);
			fRec244[0] = ((fSlow45 * (((fSlow28 * fRec245[0]) + (fSlow52 * fRec245[1])) + (fSlow28 * fRec245[2]))) - (fSlow32 * (fTemp147 + (fSlow33 * fRec244[2]))));
			float fTemp148 = (fSlow41 * fRec243[1]);
			fRec243[0] = ((fRec244[2] + (fSlow32 * (fTemp147 + (fSlow33 * fRec244[0])))) - (fSlow38 * (fTemp148 + (fSlow39 * fRec243[2]))));
			fRec253[0] = ((fSlow47 * fRec253[1]) + (fSlow48 * (fVec32[1] + fTemp146)));
			fRec252[0] = (fRec253[0] - (fSlow45 * ((fSlow29 * fRec252[1]) + (fSlow51 * fRec252[2]))));
			float fTemp149 = (fRec252[2] + (fRec252[0] + (2.0f * fRec252[1])));
			float fTemp150 = (fSlow45 * fTemp149);
			fVec33[0] = fTemp150;
			fRec251[0] = ((fSlow58 * fRec251[1]) + (fSlow59 * ((fSlow60 * fVec33[1]) + (fSlow61 * fTemp149))));
			fRec250[0] = (fRec251[0] - (fSlow56 * ((fSlow35 * fRec250[1]) + (fSlow62 * fRec250[2]))));
			float fTemp151 = (fSlow41 * fRec249[1]);
			fRec249[0] = ((fSlow56 * (((fSlow34 * fRec250[0]) + (fSlow63 * fRec250[1])) + (fSlow34 * fRec250[2]))) - (fSlow38 * (fTemp151 + (fSlow39 * fRec249[2]))));
			fRec257[0] = ((fSlow58 * fRec257[1]) + (fSlow59 * (fVec33[1] + fTemp150)));
			fRec256[0] = (fRec257[0] - (fSlow56 * ((fSlow35 * fRec256[1]) + (fSlow62 * fRec256[2]))));
			float fTemp152 = (fRec256[2] + (fRec256[0] + (2.0f * fRec256[1])));
			float fTemp153 = (fSlow56 * fTemp152);
			fVec34[0] = fTemp153;
			fRec255[0] = ((fSlow68 * fRec255[1]) + (fSlow69 * ((fSlow70 * fVec34[1]) + (fSlow71 * fTemp152))));
			fRec254[0] = (fRec255[0] - (fSlow64 * ((fSlow41 * fRec254[1]) + (fSlow72 * fRec254[2]))));
			fRec259[0] = ((fSlow68 * fRec259[1]) + (fSlow69 * (fVec34[1] + fTemp153)));
			fRec258[0] = (fRec259[0] - (fSlow64 * ((fSlow41 * fRec258[1]) + (fSlow72 * fRec258[2]))));
			float fTemp154 = ((((fSlow141 * (fRec238[2] + (fSlow38 * (fTemp144 + (fSlow39 * fRec238[0]))))) + (fSlow142 * (fRec243[2] + (fSlow38 * (fTemp148 + (fSlow39 * fRec243[0])))))) + (fSlow143 * (fRec249[2] + (fSlow38 * (fTemp151 + (fSlow39 * fRec249[0])))))) + (fSlow64 * ((fSlow144 * (((fSlow40 * fRec254[0]) + (fSlow73 * fRec254[1])) + (fSlow40 * fRec254[2]))) + (fSlow145 * (fRec258[2] + (fRec258[0] + (2.0f * fRec258[1])))))));
			fRec264[0] = ((fSlow18 * fRec264[1]) + (fSlow19 * ((fSlow13 * fRec13[1]) + (fSlow20 * fRec13[2]))));
			fRec263[0] = (fRec264[0] - (fSlow15 * ((fSlow21 * fRec263[1]) + (fSlow22 * fRec263[2]))));
			float fTemp155 = (fSlow29 * fRec262[1]);
			fRec262[0] = ((fSlow15 * (((fSlow16 * fRec263[0]) + (fSlow23 * fRec263[1])) + (fSlow16 * fRec263[2]))) - (fSlow26 * (fTemp155 + (fSlow27 * fRec262[2]))));
			float fTemp156 = (fSlow35 * fRec261[1]);
			fRec261[0] = ((fRec262[2] + (fSlow26 * (fTemp155 + (fSlow27 * fRec262[0])))) - (fSlow32 * (fTemp156 + (fSlow33 * fRec261[2]))));
			float fTemp157 = (fSlow41 * fRec260[1]);
			fRec260[0] = ((fRec261[2] + (fSlow32 * (fTemp156 + (fSlow33 * fRec261[0])))) - (fSlow38 * (fTemp157 + (fSlow39 * fRec260[2]))));
			fRec270[0] = ((fSlow18 * fRec270[1]) + (fSlow19 * (fRec13[1] + fRec13[2])));
			fRec269[0] = (fRec270[0] - (fSlow15 * ((fSlow21 * fRec269[1]) + (fSlow22 * fRec269[2]))));
			float fTemp158 = (fRec269[2] + (fRec269[0] + (2.0f * fRec269[1])));
			float fTemp159 = (fSlow15 * fTemp158);
			fVec35[0] = fTemp159;
			fRec268[0] = ((fSlow47 * fRec268[1]) + (fSlow48 * ((fSlow49 * fVec35[1]) + (fSlow50 * fTemp158))));
			fRec267[0] = (fRec268[0] - (fSlow45 * ((fSlow29 * fRec267[1]) + (fSlow51 * fRec267[2]))));
			float fTemp160 = (fSlow35 * fRec266[1]);
			fRec266[0] = ((fSlow45 * (((fSlow28 * fRec267[0]) + (fSlow52 * fRec267[1])) + (fSlow28 * fRec267[2]))) - (fSlow32 * (fTemp160 + (fSlow33 * fRec266[2]))));
			float fTemp161 = (fSlow41 * fRec265[1]);
			fRec265[0] = ((fRec266[2] + (fSlow32 * (fTemp160 + (fSlow33 * fRec266[0])))) - (fSlow38 * (fTemp161 + (fSlow39 * fRec265[2]))));
			fRec275[0] = ((fSlow47 * fRec275[1]) + (fSlow48 * (fVec35[1] + fTemp159)));
			fRec274[0] = (fRec275[0] - (fSlow45 * ((fSlow29 * fRec274[1]) + (fSlow51 * fRec274[2]))));
			float fTemp162 = (fRec274[2] + (fRec274[0] + (2.0f * fRec274[1])));
			float fTemp163 = (fSlow45 * fTemp162);
			fVec36[0] = fTemp163;
			fRec273[0] = ((fSlow58 * fRec273[1]) + (fSlow59 * ((fSlow60 * fVec36[1]) + (fSlow61 * fTemp162))));
			fRec272[0] = (fRec273[0] - (fSlow56 * ((fSlow35 * fRec272[1]) + (fSlow62 * fRec272[2]))));
			float fTemp164 = (fSlow41 * fRec271[1]);
			fRec271[0] = ((fSlow56 * (((fSlow34 * fRec272[0]) + (fSlow63 * fRec272[1])) + (fSlow34 * fRec272[2]))) - (fSlow38 * (fTemp164 + (fSlow39 * fRec271[2]))));
			fRec279[0] = ((fSlow58 * fRec279[1]) + (fSlow59 * (fVec36[1] + fTemp163)));
			fRec278[0] = (fRec279[0] - (fSlow56 * ((fSlow35 * fRec278[1]) + (fSlow62 * fRec278[2]))));
			float fTemp165 = (fRec278[2] + (fRec278[0] + (2.0f * fRec278[1])));
			float fTemp166 = (fSlow56 * fTemp165);
			fVec37[0] = fTemp166;
			fRec277[0] = ((fSlow68 * fRec277[1]) + (fSlow69 * ((fSlow70 * fVec37[1]) + (fSlow71 * fTemp165))));
			fRec276[0] = (fRec277[0] - (fSlow64 * ((fSlow41 * fRec276[1]) + (fSlow72 * fRec276[2]))));
			fRec281[0] = ((fSlow68 * fRec281[1]) + (fSlow69 * (fVec37[1] + fTemp166)));
			fRec280[0] = (fRec281[0] - (fSlow64 * ((fSlow41 * fRec280[1]) + (fSlow72 * fRec280[2]))));
			float fTemp167 = ((((fSlow148 * (fRec260[2] + (fSlow38 * (fTemp157 + (fSlow39 * fRec260[0]))))) + (fSlow149 * (fRec265[2] + (fSlow38 * (fTemp161 + (fSlow39 * fRec265[0])))))) + (fSlow150 * (fRec271[2] + (fSlow38 * (fTemp164 + (fSlow39 * fRec271[0])))))) + (fSlow64 * ((fSlow151 * (((fSlow40 * fRec276[0]) + (fSlow73 * fRec276[1])) + (fSlow40 * fRec276[2]))) + (fSlow152 * (fRec280[2] + (fRec280[0] + (2.0f * fRec280[1])))))));
			float fTemp168 = (fTemp154 + fTemp167);
			float fTemp169 = (fTemp141 + fTemp168);
			fRec286[0] = ((fSlow18 * fRec286[1]) + (fSlow19 * ((fSlow13 * fRec3[1]) + (fSlow20 * fRec3[2]))));
			fRec285[0] = (fRec286[0] - (fSlow15 * ((fSlow21 * fRec285[1]) + (fSlow22 * fRec285[2]))));
			float fTemp170 = (fSlow29 * fRec284[1]);
			fRec284[0] = ((fSlow15 * (((fSlow16 * fRec285[0]) + (fSlow23 * fRec285[1])) + (fSlow16 * fRec285[2]))) - (fSlow26 * (fTemp170 + (fSlow27 * fRec284[2]))));
			float fTemp171 = (fSlow35 * fRec283[1]);
			fRec283[0] = ((fRec284[2] + (fSlow26 * (fTemp170 + (fSlow27 * fRec284[0])))) - (fSlow32 * (fTemp171 + (fSlow33 * fRec283[2]))));
			float fTemp172 = (fSlow41 * fRec282[1]);
			fRec282[0] = ((fRec283[2] + (fSlow32 * (fTemp171 + (fSlow33 * fRec283[0])))) - (fSlow38 * (fTemp172 + (fSlow39 * fRec282[2]))));
			fRec292[0] = ((fSlow18 * fRec292[1]) + (fSlow19 * (fRec3[1] + fRec3[2])));
			fRec291[0] = (fRec292[0] - (fSlow15 * ((fSlow21 * fRec291[1]) + (fSlow22 * fRec291[2]))));
			float fTemp173 = (fRec291[2] + (fRec291[0] + (2.0f * fRec291[1])));
			float fTemp174 = (fSlow15 * fTemp173);
			fVec38[0] = fTemp174;
			fRec290[0] = ((fSlow47 * fRec290[1]) + (fSlow48 * ((fSlow49 * fVec38[1]) + (fSlow50 * fTemp173))));
			fRec289[0] = (fRec290[0] - (fSlow45 * ((fSlow29 * fRec289[1]) + (fSlow51 * fRec289[2]))));
			float fTemp175 = (fSlow35 * fRec288[1]);
			fRec288[0] = ((fSlow45 * (((fSlow28 * fRec289[0]) + (fSlow52 * fRec289[1])) + (fSlow28 * fRec289[2]))) - (fSlow32 * (fTemp175 + (fSlow33 * fRec288[2]))));
			float fTemp176 = (fSlow41 * fRec287[1]);
			fRec287[0] = ((fRec288[2] + (fSlow32 * (fTemp175 + (fSlow33 * fRec288[0])))) - (fSlow38 * (fTemp176 + (fSlow39 * fRec287[2]))));
			fRec297[0] = ((fSlow47 * fRec297[1]) + (fSlow48 * (fVec38[1] + fTemp174)));
			fRec296[0] = (fRec297[0] - (fSlow45 * ((fSlow29 * fRec296[1]) + (fSlow51 * fRec296[2]))));
			float fTemp177 = (fRec296[2] + (fRec296[0] + (2.0f * fRec296[1])));
			float fTemp178 = (fSlow45 * fTemp177);
			fVec39[0] = fTemp178;
			fRec295[0] = ((fSlow58 * fRec295[1]) + (fSlow59 * ((fSlow60 * fVec39[1]) + (fSlow61 * fTemp177))));
			fRec294[0] = (fRec295[0] - (fSlow56 * ((fSlow35 * fRec294[1]) + (fSlow62 * fRec294[2]))));
			float fTemp179 = (fSlow41 * fRec293[1]);
			fRec293[0] = ((fSlow56 * (((fSlow34 * fRec294[0]) + (fSlow63 * fRec294[1])) + (fSlow34 * fRec294[2]))) - (fSlow38 * (fTemp179 + (fSlow39 * fRec293[2]))));
			fRec301[0] = ((fSlow58 * fRec301[1]) + (fSlow59 * (fVec39[1] + fTemp178)));
			fRec300[0] = (fRec301[0] - (fSlow56 * ((fSlow35 * fRec300[1]) + (fSlow62 * fRec300[2]))));
			float fTemp180 = (fRec300[2] + (fRec300[0] + (2.0f * fRec300[1])));
			float fTemp181 = (fSlow56 * fTemp180);
			fVec40[0] = fTemp181;
			fRec299[0] = ((fSlow68 * fRec299[1]) + (fSlow69 * ((fSlow70 * fVec40[1]) + (fSlow71 * fTemp180))));
			fRec298[0] = (fRec299[0] - (fSlow64 * ((fSlow41 * fRec298[1]) + (fSlow72 * fRec298[2]))));
			fRec303[0] = ((fSlow68 * fRec303[1]) + (fSlow69 * (fVec40[1] + fTemp181)));
			fRec302[0] = (fRec303[0] - (fSlow64 * ((fSlow41 * fRec302[1]) + (fSlow72 * fRec302[2]))));
			float fTemp182 = ((((fSlow155 * (fRec282[2] + (fSlow38 * (fTemp172 + (fSlow39 * fRec282[0]))))) + (fSlow156 * (fRec287[2] + (fSlow38 * (fTemp176 + (fSlow39 * fRec287[0])))))) + (fSlow157 * (fRec293[2] + (fSlow38 * (fTemp179 + (fSlow39 * fRec293[0])))))) + (fSlow64 * ((fSlow158 * (((fSlow40 * fRec298[0]) + (fSlow73 * fRec298[1])) + (fSlow40 * fRec298[2]))) + (fSlow159 * (fRec302[2] + (fRec302[0] + (2.0f * fRec302[1])))))));
			fRec308[0] = ((fSlow18 * fRec308[1]) + (fSlow19 * ((fSlow13 * fRec11[1]) + (fSlow20 * fRec11[2]))));
			fRec307[0] = (fRec308[0] - (fSlow15 * ((fSlow21 * fRec307[1]) + (fSlow22 * fRec307[2]))));
			float fTemp183 = (fSlow29 * fRec306[1]);
			fRec306[0] = ((fSlow15 * (((fSlow16 * fRec307[0]) + (fSlow23 * fRec307[1])) + (fSlow16 * fRec307[2]))) - (fSlow26 * (fTemp183 + (fSlow27 * fRec306[2]))));
			float fTemp184 = (fSlow35 * fRec305[1]);
			fRec305[0] = ((fRec306[2] + (fSlow26 * (fTemp183 + (fSlow27 * fRec306[0])))) - (fSlow32 * (fTemp184 + (fSlow33 * fRec305[2]))));
			float fTemp185 = (fSlow41 * fRec304[1]);
			fRec304[0] = ((fRec305[2] + (fSlow32 * (fTemp184 + (fSlow33 * fRec305[0])))) - (fSlow38 * (fTemp185 + (fSlow39 * fRec304[2]))));
			fRec314[0] = ((fSlow18 * fRec314[1]) + (fSlow19 * (fRec11[1] + fRec11[2])));
			fRec313[0] = (fRec314[0] - (fSlow15 * ((fSlow21 * fRec313[1]) + (fSlow22 * fRec313[2]))));
			float fTemp186 = (fRec313[2] + (fRec313[0] + (2.0f * fRec313[1])));
			float fTemp187 = (fSlow15 * fTemp186);
			fVec41[0] = fTemp187;
			fRec312[0] = ((fSlow47 * fRec312[1]) + (fSlow48 * ((fSlow49 * fVec41[1]) + (fSlow50 * fTemp186))));
			fRec311[0] = (fRec312[0] - (fSlow45 * ((fSlow29 * fRec311[1]) + (fSlow51 * fRec311[2]))));
			float fTemp188 = (fSlow35 * fRec310[1]);
			fRec310[0] = ((fSlow45 * (((fSlow28 * fRec311[0]) + (fSlow52 * fRec311[1])) + (fSlow28 * fRec311[2]))) - (fSlow32 * (fTemp188 + (fSlow33 * fRec310[2]))));
			float fTemp189 = (fSlow41 * fRec309[1]);
			fRec309[0] = ((fRec310[2] + (fSlow32 * (fTemp188 + (fSlow33 * fRec310[0])))) - (fSlow38 * (fTemp189 + (fSlow39 * fRec309[2]))));
			fRec319[0] = ((fSlow47 * fRec319[1]) + (fSlow48 * (fVec41[1] + fTemp187)));
			fRec318[0] = (fRec319[0] - (fSlow45 * ((fSlow29 * fRec318[1]) + (fSlow51 * fRec318[2]))));
			float fTemp190 = (fRec318[2] + (fRec318[0] + (2.0f * fRec318[1])));
			float fTemp191 = (fSlow45 * fTemp190);
			fVec42[0] = fTemp191;
			fRec317[0] = ((fSlow58 * fRec317[1]) + (fSlow59 * ((fSlow60 * fVec42[1]) + (fSlow61 * fTemp190))));
			fRec316[0] = (fRec317[0] - (fSlow56 * ((fSlow35 * fRec316[1]) + (fSlow62 * fRec316[2]))));
			float fTemp192 = (fSlow41 * fRec315[1]);
			fRec315[0] = ((fSlow56 * (((fSlow34 * fRec316[0]) + (fSlow63 * fRec316[1])) + (fSlow34 * fRec316[2]))) - (fSlow38 * (fTemp192 + (fSlow39 * fRec315[2]))));
			fRec323[0] = ((fSlow58 * fRec323[1]) + (fSlow59 * (fVec42[1] + fTemp191)));
			fRec322[0] = (fRec323[0] - (fSlow56 * ((fSlow35 * fRec322[1]) + (fSlow62 * fRec322[2]))));
			float fTemp193 = (fRec322[2] + (fRec322[0] + (2.0f * fRec322[1])));
			float fTemp194 = (fSlow56 * fTemp193);
			fVec43[0] = fTemp194;
			fRec321[0] = ((fSlow68 * fRec321[1]) + (fSlow69 * ((fSlow70 * fVec43[1]) + (fSlow71 * fTemp193))));
			fRec320[0] = (fRec321[0] - (fSlow64 * ((fSlow41 * fRec320[1]) + (fSlow72 * fRec320[2]))));
			fRec325[0] = ((fSlow68 * fRec325[1]) + (fSlow69 * (fVec43[1] + fTemp194)));
			fRec324[0] = (fRec325[0] - (fSlow64 * ((fSlow41 * fRec324[1]) + (fSlow72 * fRec324[2]))));
			float fTemp195 = ((((fSlow162 * (fRec304[2] + (fSlow38 * (fTemp185 + (fSlow39 * fRec304[0]))))) + (fSlow163 * (fRec309[2] + (fSlow38 * (fTemp189 + (fSlow39 * fRec309[0])))))) + (fSlow164 * (fRec315[2] + (fSlow38 * (fTemp192 + (fSlow39 * fRec315[0])))))) + (fSlow64 * ((fSlow165 * (((fSlow40 * fRec320[0]) + (fSlow73 * fRec320[1])) + (fSlow40 * fRec320[2]))) + (fSlow166 * (fRec324[2] + (fRec324[0] + (2.0f * fRec324[1])))))));
			float fTemp196 = (fTemp182 + fTemp195);
			fRec330[0] = ((fSlow18 * fRec330[1]) + (fSlow19 * ((fSlow13 * fRec7[1]) + (fSlow20 * fRec7[2]))));
			fRec329[0] = (fRec330[0] - (fSlow15 * ((fSlow21 * fRec329[1]) + (fSlow22 * fRec329[2]))));
			float fTemp197 = (fSlow29 * fRec328[1]);
			fRec328[0] = ((fSlow15 * (((fSlow16 * fRec329[0]) + (fSlow23 * fRec329[1])) + (fSlow16 * fRec329[2]))) - (fSlow26 * (fTemp197 + (fSlow27 * fRec328[2]))));
			float fTemp198 = (fSlow35 * fRec327[1]);
			fRec327[0] = ((fRec328[2] + (fSlow26 * (fTemp197 + (fSlow27 * fRec328[0])))) - (fSlow32 * (fTemp198 + (fSlow33 * fRec327[2]))));
			float fTemp199 = (fSlow41 * fRec326[1]);
			fRec326[0] = ((fRec327[2] + (fSlow32 * (fTemp198 + (fSlow33 * fRec327[0])))) - (fSlow38 * (fTemp199 + (fSlow39 * fRec326[2]))));
			fRec336[0] = ((fSlow18 * fRec336[1]) + (fSlow19 * (fRec7[1] + fRec7[2])));
			fRec335[0] = (fRec336[0] - (fSlow15 * ((fSlow21 * fRec335[1]) + (fSlow22 * fRec335[2]))));
			float fTemp200 = (fRec335[2] + (fRec335[0] + (2.0f * fRec335[1])));
			float fTemp201 = (fSlow15 * fTemp200);
			fVec44[0] = fTemp201;
			fRec334[0] = ((fSlow47 * fRec334[1]) + (fSlow48 * ((fSlow49 * fVec44[1]) + (fSlow50 * fTemp200))));
			fRec333[0] = (fRec334[0] - (fSlow45 * ((fSlow29 * fRec333[1]) + (fSlow51 * fRec333[2]))));
			float fTemp202 = (fSlow35 * fRec332[1]);
			fRec332[0] = ((fSlow45 * (((fSlow28 * fRec333[0]) + (fSlow52 * fRec333[1])) + (fSlow28 * fRec333[2]))) - (fSlow32 * (fTemp202 + (fSlow33 * fRec332[2]))));
			float fTemp203 = (fSlow41 * fRec331[1]);
			fRec331[0] = ((fRec332[2] + (fSlow32 * (fTemp202 + (fSlow33 * fRec332[0])))) - (fSlow38 * (fTemp203 + (fSlow39 * fRec331[2]))));
			fRec341[0] = ((fSlow47 * fRec341[1]) + (fSlow48 * (fVec44[1] + fTemp201)));
			fRec340[0] = (fRec341[0] - (fSlow45 * ((fSlow29 * fRec340[1]) + (fSlow51 * fRec340[2]))));
			float fTemp204 = (fRec340[2] + (fRec340[0] + (2.0f * fRec340[1])));
			float fTemp205 = (fSlow45 * fTemp204);
			fVec45[0] = fTemp205;
			fRec339[0] = ((fSlow58 * fRec339[1]) + (fSlow59 * ((fSlow60 * fVec45[1]) + (fSlow61 * fTemp204))));
			fRec338[0] = (fRec339[0] - (fSlow56 * ((fSlow35 * fRec338[1]) + (fSlow62 * fRec338[2]))));
			float fTemp206 = (fSlow41 * fRec337[1]);
			fRec337[0] = ((fSlow56 * (((fSlow34 * fRec338[0]) + (fSlow63 * fRec338[1])) + (fSlow34 * fRec338[2]))) - (fSlow38 * (fTemp206 + (fSlow39 * fRec337[2]))));
			fRec345[0] = ((fSlow58 * fRec345[1]) + (fSlow59 * (fVec45[1] + fTemp205)));
			fRec344[0] = (fRec345[0] - (fSlow56 * ((fSlow35 * fRec344[1]) + (fSlow62 * fRec344[2]))));
			float fTemp207 = (fRec344[2] + (fRec344[0] + (2.0f * fRec344[1])));
			float fTemp208 = (fSlow56 * fTemp207);
			fVec46[0] = fTemp208;
			fRec343[0] = ((fSlow68 * fRec343[1]) + (fSlow69 * ((fSlow70 * fVec46[1]) + (fSlow71 * fTemp207))));
			fRec342[0] = (fRec343[0] - (fSlow64 * ((fSlow41 * fRec342[1]) + (fSlow72 * fRec342[2]))));
			fRec347[0] = ((fSlow68 * fRec347[1]) + (fSlow69 * (fVec46[1] + fTemp208)));
			fRec346[0] = (fRec347[0] - (fSlow64 * ((fSlow41 * fRec346[1]) + (fSlow72 * fRec346[2]))));
			float fTemp209 = ((((fSlow169 * (fRec326[2] + (fSlow38 * (fTemp199 + (fSlow39 * fRec326[0]))))) + (fSlow170 * (fRec331[2] + (fSlow38 * (fTemp203 + (fSlow39 * fRec331[0])))))) + (fSlow171 * (fRec337[2] + (fSlow38 * (fTemp206 + (fSlow39 * fRec337[0])))))) + (fSlow64 * ((fSlow172 * (((fSlow40 * fRec342[0]) + (fSlow73 * fRec342[1])) + (fSlow40 * fRec342[2]))) + (fSlow173 * (fRec346[2] + (fRec346[0] + (2.0f * fRec346[1])))))));
			fRec352[0] = ((fSlow18 * fRec352[1]) + (fSlow19 * ((fSlow13 * fRec15[1]) + (fSlow20 * fRec15[2]))));
			fRec351[0] = (fRec352[0] - (fSlow15 * ((fSlow21 * fRec351[1]) + (fSlow22 * fRec351[2]))));
			float fTemp210 = (fSlow29 * fRec350[1]);
			fRec350[0] = ((fSlow15 * (((fSlow16 * fRec351[0]) + (fSlow23 * fRec351[1])) + (fSlow16 * fRec351[2]))) - (fSlow26 * (fTemp210 + (fSlow27 * fRec350[2]))));
			float fTemp211 = (fSlow35 * fRec349[1]);
			fRec349[0] = ((fRec350[2] + (fSlow26 * (fTemp210 + (fSlow27 * fRec350[0])))) - (fSlow32 * (fTemp211 + (fSlow33 * fRec349[2]))));
			float fTemp212 = (fSlow41 * fRec348[1]);
			fRec348[0] = ((fRec349[2] + (fSlow32 * (fTemp211 + (fSlow33 * fRec349[0])))) - (fSlow38 * (fTemp212 + (fSlow39 * fRec348[2]))));
			fRec358[0] = ((fSlow18 * fRec358[1]) + (fSlow19 * (fRec15[1] + fRec15[2])));
			fRec357[0] = (fRec358[0] - (fSlow15 * ((fSlow21 * fRec357[1]) + (fSlow22 * fRec357[2]))));
			float fTemp213 = (fRec357[2] + (fRec357[0] + (2.0f * fRec357[1])));
			float fTemp214 = (fSlow15 * fTemp213);
			fVec47[0] = fTemp214;
			fRec356[0] = ((fSlow47 * fRec356[1]) + (fSlow48 * ((fSlow49 * fVec47[1]) + (fSlow50 * fTemp213))));
			fRec355[0] = (fRec356[0] - (fSlow45 * ((fSlow29 * fRec355[1]) + (fSlow51 * fRec355[2]))));
			float fTemp215 = (fSlow35 * fRec354[1]);
			fRec354[0] = ((fSlow45 * (((fSlow28 * fRec355[0]) + (fSlow52 * fRec355[1])) + (fSlow28 * fRec355[2]))) - (fSlow32 * (fTemp215 + (fSlow33 * fRec354[2]))));
			float fTemp216 = (fSlow41 * fRec353[1]);
			fRec353[0] = ((fRec354[2] + (fSlow32 * (fTemp215 + (fSlow33 * fRec354[0])))) - (fSlow38 * (fTemp216 + (fSlow39 * fRec353[2]))));
			fRec363[0] = ((fSlow47 * fRec363[1]) + (fSlow48 * (fVec47[1] + fTemp214)));
			fRec362[0] = (fRec363[0] - (fSlow45 * ((fSlow29 * fRec362[1]) + (fSlow51 * fRec362[2]))));
			float fTemp217 = (fRec362[2] + (fRec362[0] + (2.0f * fRec362[1])));
			float fTemp218 = (fSlow45 * fTemp217);
			fVec48[0] = fTemp218;
			fRec361[0] = ((fSlow58 * fRec361[1]) + (fSlow59 * ((fSlow60 * fVec48[1]) + (fSlow61 * fTemp217))));
			fRec360[0] = (fRec361[0] - (fSlow56 * ((fSlow35 * fRec360[1]) + (fSlow62 * fRec360[2]))));
			float fTemp219 = (fSlow41 * fRec359[1]);
			fRec359[0] = ((fSlow56 * (((fSlow34 * fRec360[0]) + (fSlow63 * fRec360[1])) + (fSlow34 * fRec360[2]))) - (fSlow38 * (fTemp219 + (fSlow39 * fRec359[2]))));
			fRec367[0] = ((fSlow58 * fRec367[1]) + (fSlow59 * (fVec48[1] + fTemp218)));
			fRec366[0] = (fRec367[0] - (fSlow56 * ((fSlow35 * fRec366[1]) + (fSlow62 * fRec366[2]))));
			float fTemp220 = (fRec366[2] + (fRec366[0] + (2.0f * fRec366[1])));
			float fTemp221 = (fSlow56 * fTemp220);
			fVec49[0] = fTemp221;
			fRec365[0] = ((fSlow68 * fRec365[1]) + (fSlow69 * ((fSlow70 * fVec49[1]) + (fSlow71 * fTemp220))));
			fRec364[0] = (fRec365[0] - (fSlow64 * ((fSlow41 * fRec364[1]) + (fSlow72 * fRec364[2]))));
			fRec369[0] = ((fSlow68 * fRec369[1]) + (fSlow69 * (fVec49[1] + fTemp221)));
			fRec368[0] = (fRec369[0] - (fSlow64 * ((fSlow41 * fRec368[1]) + (fSlow72 * fRec368[2]))));
			float fTemp222 = ((((fSlow176 * (fRec348[2] + (fSlow38 * (fTemp212 + (fSlow39 * fRec348[0]))))) + (fSlow177 * (fRec353[2] + (fSlow38 * (fTemp216 + (fSlow39 * fRec353[0])))))) + (fSlow178 * (fRec359[2] + (fSlow38 * (fTemp219 + (fSlow39 * fRec359[0])))))) + (fSlow64 * ((fSlow179 * (((fSlow40 * fRec364[0]) + (fSlow73 * fRec364[1])) + (fSlow40 * fRec364[2]))) + (fSlow180 * (fRec368[2] + (fRec368[0] + (2.0f * fRec368[1])))))));
			float fTemp223 = (fTemp209 + fTemp222);
			float fTemp224 = (fTemp196 + fTemp223);
			float fTemp225 = (fTemp169 + fTemp224);
			fVec50[(IOTA & 16383)] = (fTemp0 + (float(iTemp1) + (float(iTemp2) + (fTemp3 + (fSlow5 * (fTemp114 + fTemp225))))));
			fRec0[0] = fVec50[((IOTA - iSlow181) & 16383)];
			fVec51[0] = fSlow182;
			int iTemp226 = ((fSlow182 - fVec51[1]) > 0.0f);
			float fTemp227 = ((fSlow4 * float(input3[i])) + (float(iTemp1) + fTemp0));
			fVec52[(IOTA & 16383)] = (float(iTemp226) + ((fSlow5 * (fTemp114 - fTemp225)) + fTemp227));
			fRec1[0] = fVec52[((IOTA - iSlow183) & 16383)];
			float fTemp228 = ((float(iTemp1) + (fTemp3 + float(iTemp2))) + fTemp0);
			float fTemp229 = (fTemp58 - fTemp113);
			float fTemp230 = (fTemp169 - fTemp224);
			fVec53[(IOTA & 16383)] = (fTemp228 + (fSlow5 * (fTemp229 + fTemp230)));
			fRec2[0] = fVec53[((IOTA - iSlow184) & 16383)];
			float fTemp231 = (float(iTemp226) + fTemp227);
			fVec54[(IOTA & 16383)] = (fTemp231 + (fSlow5 * (fTemp229 - fTemp230)));
			fRec3[0] = fVec54[((IOTA - iSlow185) & 16383)];
			float fTemp232 = (fTemp30 - fTemp57);
			float fTemp233 = (fTemp85 - fTemp112);
			float fTemp234 = (fTemp232 + fTemp233);
			float fTemp235 = (fTemp141 - fTemp168);
			float fTemp236 = (fTemp196 - fTemp223);
			float fTemp237 = (fTemp235 + fTemp236);
			fVec55[(IOTA & 16383)] = (fTemp228 + (fSlow5 * (fTemp234 + fTemp237)));
			fRec4[0] = fVec55[((IOTA - iSlow186) & 16383)];
			fVec56[(IOTA & 16383)] = (fTemp231 + (fSlow5 * (fTemp234 - fTemp237)));
			fRec5[0] = fVec56[((IOTA - iSlow187) & 16383)];
			float fTemp238 = (fTemp232 - fTemp233);
			float fTemp239 = (fTemp235 - fTemp236);
			fVec57[(IOTA & 16383)] = (fTemp228 + (fSlow5 * (fTemp238 + fTemp239)));
			fRec6[0] = fVec57[((IOTA - iSlow188) & 16383)];
			fVec58[(IOTA & 16383)] = (fTemp231 + (fSlow5 * (fTemp238 - fTemp239)));
			fRec7[0] = fVec58[((IOTA - iSlow189) & 16383)];
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
			fVec59[(IOTA & 16383)] = (fTemp228 + (fSlow5 * (fTemp246 + fTemp253)));
			fRec8[0] = fVec59[((IOTA - iSlow190) & 16383)];
			fVec60[(IOTA & 16383)] = (fTemp231 + (fSlow5 * (fTemp246 - fTemp253)));
			fRec9[0] = fVec60[((IOTA - iSlow191) & 16383)];
			float fTemp254 = (fTemp242 - fTemp245);
			float fTemp255 = (fTemp249 - fTemp252);
			fVec61[(IOTA & 16383)] = (fTemp228 + (fSlow5 * (fTemp254 + fTemp255)));
			fRec10[0] = fVec61[((IOTA - iSlow192) & 16383)];
			fVec62[(IOTA & 16383)] = (fTemp231 + (fSlow5 * (fTemp254 - fTemp255)));
			fRec11[0] = fVec62[((IOTA - iSlow193) & 16383)];
			float fTemp256 = (fTemp240 - fTemp241);
			float fTemp257 = (fTemp243 - fTemp244);
			float fTemp258 = (fTemp256 + fTemp257);
			float fTemp259 = (fTemp247 - fTemp248);
			float fTemp260 = (fTemp251 - fTemp250);
			float fTemp261 = (fTemp259 + fTemp260);
			fVec63[(IOTA & 16383)] = (fTemp228 + (fSlow5 * (fTemp258 + fTemp261)));
			fRec12[0] = fVec63[((IOTA - iSlow194) & 16383)];
			fVec64[(IOTA & 16383)] = (fTemp231 + (fSlow5 * (fTemp258 - fTemp261)));
			fRec13[0] = fVec64[((IOTA - iSlow195) & 16383)];
			float fTemp262 = (fTemp256 - fTemp257);
			float fTemp263 = (fTemp259 - fTemp260);
			fVec65[(IOTA & 16383)] = (fTemp228 + (fSlow5 * (fTemp262 + fTemp263)));
			fRec14[0] = fVec65[((IOTA - iSlow196) & 16383)];
			fVec66[(IOTA & 16383)] = (fTemp231 + (fSlow5 * (fTemp262 - fTemp263)));
			fRec15[0] = fVec66[((IOTA - iSlow197) & 16383)];
			output0[i] = FAUSTFLOAT((fSlow0 * (((((((fRec0[0] + fRec2[0]) + fRec4[0]) + fRec6[0]) + fRec8[0]) + fRec10[0]) + fRec12[0]) + fRec14[0])));
			output1[i] = FAUSTFLOAT((fSlow0 * (((((((fRec1[0] + fRec3[0]) + fRec5[0]) + fRec7[0]) + fRec9[0]) + fRec11[0]) + fRec13[0]) + fRec15[0])));
			iRec17[1] = iRec17[0];
			for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				fRec16[j0] = fRec16[(j0 - 1)];
				
			}
			fVec0[1] = fVec0[0];
			fVec1[1] = fVec1[0];
			fRec22[1] = fRec22[0];
			fRec21[2] = fRec21[1];
			fRec21[1] = fRec21[0];
			fRec20[2] = fRec20[1];
			fRec20[1] = fRec20[0];
			fRec19[2] = fRec19[1];
			fRec19[1] = fRec19[0];
			fRec18[2] = fRec18[1];
			fRec18[1] = fRec18[0];
			fRec28[1] = fRec28[0];
			fRec27[2] = fRec27[1];
			fRec27[1] = fRec27[0];
			fVec2[1] = fVec2[0];
			fRec26[1] = fRec26[0];
			fRec25[2] = fRec25[1];
			fRec25[1] = fRec25[0];
			fRec24[2] = fRec24[1];
			fRec24[1] = fRec24[0];
			fRec23[2] = fRec23[1];
			fRec23[1] = fRec23[0];
			fRec33[1] = fRec33[0];
			fRec32[2] = fRec32[1];
			fRec32[1] = fRec32[0];
			fVec3[1] = fVec3[0];
			fRec31[1] = fRec31[0];
			fRec30[2] = fRec30[1];
			fRec30[1] = fRec30[0];
			fRec29[2] = fRec29[1];
			fRec29[1] = fRec29[0];
			fRec37[1] = fRec37[0];
			fRec36[2] = fRec36[1];
			fRec36[1] = fRec36[0];
			fVec4[1] = fVec4[0];
			fRec35[1] = fRec35[0];
			fRec34[2] = fRec34[1];
			fRec34[1] = fRec34[0];
			fRec39[1] = fRec39[0];
			fRec38[2] = fRec38[1];
			fRec38[1] = fRec38[0];
			fRec44[1] = fRec44[0];
			fRec43[2] = fRec43[1];
			fRec43[1] = fRec43[0];
			fRec42[2] = fRec42[1];
			fRec42[1] = fRec42[0];
			fRec41[2] = fRec41[1];
			fRec41[1] = fRec41[0];
			fRec40[2] = fRec40[1];
			fRec40[1] = fRec40[0];
			fRec50[1] = fRec50[0];
			fRec49[2] = fRec49[1];
			fRec49[1] = fRec49[0];
			fVec5[1] = fVec5[0];
			fRec48[1] = fRec48[0];
			fRec47[2] = fRec47[1];
			fRec47[1] = fRec47[0];
			fRec46[2] = fRec46[1];
			fRec46[1] = fRec46[0];
			fRec45[2] = fRec45[1];
			fRec45[1] = fRec45[0];
			fRec55[1] = fRec55[0];
			fRec54[2] = fRec54[1];
			fRec54[1] = fRec54[0];
			fVec6[1] = fVec6[0];
			fRec53[1] = fRec53[0];
			fRec52[2] = fRec52[1];
			fRec52[1] = fRec52[0];
			fRec51[2] = fRec51[1];
			fRec51[1] = fRec51[0];
			fRec59[1] = fRec59[0];
			fRec58[2] = fRec58[1];
			fRec58[1] = fRec58[0];
			fVec7[1] = fVec7[0];
			fRec57[1] = fRec57[0];
			fRec56[2] = fRec56[1];
			fRec56[1] = fRec56[0];
			fRec61[1] = fRec61[0];
			fRec60[2] = fRec60[1];
			fRec60[1] = fRec60[0];
			fRec66[1] = fRec66[0];
			fRec65[2] = fRec65[1];
			fRec65[1] = fRec65[0];
			fRec64[2] = fRec64[1];
			fRec64[1] = fRec64[0];
			fRec63[2] = fRec63[1];
			fRec63[1] = fRec63[0];
			fRec62[2] = fRec62[1];
			fRec62[1] = fRec62[0];
			fRec72[1] = fRec72[0];
			fRec71[2] = fRec71[1];
			fRec71[1] = fRec71[0];
			fVec8[1] = fVec8[0];
			fRec70[1] = fRec70[0];
			fRec69[2] = fRec69[1];
			fRec69[1] = fRec69[0];
			fRec68[2] = fRec68[1];
			fRec68[1] = fRec68[0];
			fRec67[2] = fRec67[1];
			fRec67[1] = fRec67[0];
			fRec77[1] = fRec77[0];
			fRec76[2] = fRec76[1];
			fRec76[1] = fRec76[0];
			fVec9[1] = fVec9[0];
			fRec75[1] = fRec75[0];
			fRec74[2] = fRec74[1];
			fRec74[1] = fRec74[0];
			fRec73[2] = fRec73[1];
			fRec73[1] = fRec73[0];
			fRec81[1] = fRec81[0];
			fRec80[2] = fRec80[1];
			fRec80[1] = fRec80[0];
			fVec10[1] = fVec10[0];
			fRec79[1] = fRec79[0];
			fRec78[2] = fRec78[1];
			fRec78[1] = fRec78[0];
			fRec83[1] = fRec83[0];
			fRec82[2] = fRec82[1];
			fRec82[1] = fRec82[0];
			fRec88[1] = fRec88[0];
			fRec87[2] = fRec87[1];
			fRec87[1] = fRec87[0];
			fRec86[2] = fRec86[1];
			fRec86[1] = fRec86[0];
			fRec85[2] = fRec85[1];
			fRec85[1] = fRec85[0];
			fRec84[2] = fRec84[1];
			fRec84[1] = fRec84[0];
			fRec94[1] = fRec94[0];
			fRec93[2] = fRec93[1];
			fRec93[1] = fRec93[0];
			fVec11[1] = fVec11[0];
			fRec92[1] = fRec92[0];
			fRec91[2] = fRec91[1];
			fRec91[1] = fRec91[0];
			fRec90[2] = fRec90[1];
			fRec90[1] = fRec90[0];
			fRec89[2] = fRec89[1];
			fRec89[1] = fRec89[0];
			fRec99[1] = fRec99[0];
			fRec98[2] = fRec98[1];
			fRec98[1] = fRec98[0];
			fVec12[1] = fVec12[0];
			fRec97[1] = fRec97[0];
			fRec96[2] = fRec96[1];
			fRec96[1] = fRec96[0];
			fRec95[2] = fRec95[1];
			fRec95[1] = fRec95[0];
			fRec103[1] = fRec103[0];
			fRec102[2] = fRec102[1];
			fRec102[1] = fRec102[0];
			fVec13[1] = fVec13[0];
			fRec101[1] = fRec101[0];
			fRec100[2] = fRec100[1];
			fRec100[1] = fRec100[0];
			fRec105[1] = fRec105[0];
			fRec104[2] = fRec104[1];
			fRec104[1] = fRec104[0];
			fRec110[1] = fRec110[0];
			fRec109[2] = fRec109[1];
			fRec109[1] = fRec109[0];
			fRec108[2] = fRec108[1];
			fRec108[1] = fRec108[0];
			fRec107[2] = fRec107[1];
			fRec107[1] = fRec107[0];
			fRec106[2] = fRec106[1];
			fRec106[1] = fRec106[0];
			fRec116[1] = fRec116[0];
			fRec115[2] = fRec115[1];
			fRec115[1] = fRec115[0];
			fVec14[1] = fVec14[0];
			fRec114[1] = fRec114[0];
			fRec113[2] = fRec113[1];
			fRec113[1] = fRec113[0];
			fRec112[2] = fRec112[1];
			fRec112[1] = fRec112[0];
			fRec111[2] = fRec111[1];
			fRec111[1] = fRec111[0];
			fRec121[1] = fRec121[0];
			fRec120[2] = fRec120[1];
			fRec120[1] = fRec120[0];
			fVec15[1] = fVec15[0];
			fRec119[1] = fRec119[0];
			fRec118[2] = fRec118[1];
			fRec118[1] = fRec118[0];
			fRec117[2] = fRec117[1];
			fRec117[1] = fRec117[0];
			fRec125[1] = fRec125[0];
			fRec124[2] = fRec124[1];
			fRec124[1] = fRec124[0];
			fVec16[1] = fVec16[0];
			fRec123[1] = fRec123[0];
			fRec122[2] = fRec122[1];
			fRec122[1] = fRec122[0];
			fRec127[1] = fRec127[0];
			fRec126[2] = fRec126[1];
			fRec126[1] = fRec126[0];
			fRec132[1] = fRec132[0];
			fRec131[2] = fRec131[1];
			fRec131[1] = fRec131[0];
			fRec130[2] = fRec130[1];
			fRec130[1] = fRec130[0];
			fRec129[2] = fRec129[1];
			fRec129[1] = fRec129[0];
			fRec128[2] = fRec128[1];
			fRec128[1] = fRec128[0];
			fRec138[1] = fRec138[0];
			fRec137[2] = fRec137[1];
			fRec137[1] = fRec137[0];
			fVec17[1] = fVec17[0];
			fRec136[1] = fRec136[0];
			fRec135[2] = fRec135[1];
			fRec135[1] = fRec135[0];
			fRec134[2] = fRec134[1];
			fRec134[1] = fRec134[0];
			fRec133[2] = fRec133[1];
			fRec133[1] = fRec133[0];
			fRec143[1] = fRec143[0];
			fRec142[2] = fRec142[1];
			fRec142[1] = fRec142[0];
			fVec18[1] = fVec18[0];
			fRec141[1] = fRec141[0];
			fRec140[2] = fRec140[1];
			fRec140[1] = fRec140[0];
			fRec139[2] = fRec139[1];
			fRec139[1] = fRec139[0];
			fRec147[1] = fRec147[0];
			fRec146[2] = fRec146[1];
			fRec146[1] = fRec146[0];
			fVec19[1] = fVec19[0];
			fRec145[1] = fRec145[0];
			fRec144[2] = fRec144[1];
			fRec144[1] = fRec144[0];
			fRec149[1] = fRec149[0];
			fRec148[2] = fRec148[1];
			fRec148[1] = fRec148[0];
			fRec154[1] = fRec154[0];
			fRec153[2] = fRec153[1];
			fRec153[1] = fRec153[0];
			fRec152[2] = fRec152[1];
			fRec152[1] = fRec152[0];
			fRec151[2] = fRec151[1];
			fRec151[1] = fRec151[0];
			fRec150[2] = fRec150[1];
			fRec150[1] = fRec150[0];
			fRec160[1] = fRec160[0];
			fRec159[2] = fRec159[1];
			fRec159[1] = fRec159[0];
			fVec20[1] = fVec20[0];
			fRec158[1] = fRec158[0];
			fRec157[2] = fRec157[1];
			fRec157[1] = fRec157[0];
			fRec156[2] = fRec156[1];
			fRec156[1] = fRec156[0];
			fRec155[2] = fRec155[1];
			fRec155[1] = fRec155[0];
			fRec165[1] = fRec165[0];
			fRec164[2] = fRec164[1];
			fRec164[1] = fRec164[0];
			fVec21[1] = fVec21[0];
			fRec163[1] = fRec163[0];
			fRec162[2] = fRec162[1];
			fRec162[1] = fRec162[0];
			fRec161[2] = fRec161[1];
			fRec161[1] = fRec161[0];
			fRec169[1] = fRec169[0];
			fRec168[2] = fRec168[1];
			fRec168[1] = fRec168[0];
			fVec22[1] = fVec22[0];
			fRec167[1] = fRec167[0];
			fRec166[2] = fRec166[1];
			fRec166[1] = fRec166[0];
			fRec171[1] = fRec171[0];
			fRec170[2] = fRec170[1];
			fRec170[1] = fRec170[0];
			fRec176[1] = fRec176[0];
			fRec175[2] = fRec175[1];
			fRec175[1] = fRec175[0];
			fRec174[2] = fRec174[1];
			fRec174[1] = fRec174[0];
			fRec173[2] = fRec173[1];
			fRec173[1] = fRec173[0];
			fRec172[2] = fRec172[1];
			fRec172[1] = fRec172[0];
			fRec182[1] = fRec182[0];
			fRec181[2] = fRec181[1];
			fRec181[1] = fRec181[0];
			fVec23[1] = fVec23[0];
			fRec180[1] = fRec180[0];
			fRec179[2] = fRec179[1];
			fRec179[1] = fRec179[0];
			fRec178[2] = fRec178[1];
			fRec178[1] = fRec178[0];
			fRec177[2] = fRec177[1];
			fRec177[1] = fRec177[0];
			fRec187[1] = fRec187[0];
			fRec186[2] = fRec186[1];
			fRec186[1] = fRec186[0];
			fVec24[1] = fVec24[0];
			fRec185[1] = fRec185[0];
			fRec184[2] = fRec184[1];
			fRec184[1] = fRec184[0];
			fRec183[2] = fRec183[1];
			fRec183[1] = fRec183[0];
			fRec191[1] = fRec191[0];
			fRec190[2] = fRec190[1];
			fRec190[1] = fRec190[0];
			fVec25[1] = fVec25[0];
			fRec189[1] = fRec189[0];
			fRec188[2] = fRec188[1];
			fRec188[1] = fRec188[0];
			fRec193[1] = fRec193[0];
			fRec192[2] = fRec192[1];
			fRec192[1] = fRec192[0];
			fRec198[1] = fRec198[0];
			fRec197[2] = fRec197[1];
			fRec197[1] = fRec197[0];
			fRec196[2] = fRec196[1];
			fRec196[1] = fRec196[0];
			fRec195[2] = fRec195[1];
			fRec195[1] = fRec195[0];
			fRec194[2] = fRec194[1];
			fRec194[1] = fRec194[0];
			fRec204[1] = fRec204[0];
			fRec203[2] = fRec203[1];
			fRec203[1] = fRec203[0];
			fVec26[1] = fVec26[0];
			fRec202[1] = fRec202[0];
			fRec201[2] = fRec201[1];
			fRec201[1] = fRec201[0];
			fRec200[2] = fRec200[1];
			fRec200[1] = fRec200[0];
			fRec199[2] = fRec199[1];
			fRec199[1] = fRec199[0];
			fRec209[1] = fRec209[0];
			fRec208[2] = fRec208[1];
			fRec208[1] = fRec208[0];
			fVec27[1] = fVec27[0];
			fRec207[1] = fRec207[0];
			fRec206[2] = fRec206[1];
			fRec206[1] = fRec206[0];
			fRec205[2] = fRec205[1];
			fRec205[1] = fRec205[0];
			fRec213[1] = fRec213[0];
			fRec212[2] = fRec212[1];
			fRec212[1] = fRec212[0];
			fVec28[1] = fVec28[0];
			fRec211[1] = fRec211[0];
			fRec210[2] = fRec210[1];
			fRec210[1] = fRec210[0];
			fRec215[1] = fRec215[0];
			fRec214[2] = fRec214[1];
			fRec214[1] = fRec214[0];
			fRec220[1] = fRec220[0];
			fRec219[2] = fRec219[1];
			fRec219[1] = fRec219[0];
			fRec218[2] = fRec218[1];
			fRec218[1] = fRec218[0];
			fRec217[2] = fRec217[1];
			fRec217[1] = fRec217[0];
			fRec216[2] = fRec216[1];
			fRec216[1] = fRec216[0];
			fRec226[1] = fRec226[0];
			fRec225[2] = fRec225[1];
			fRec225[1] = fRec225[0];
			fVec29[1] = fVec29[0];
			fRec224[1] = fRec224[0];
			fRec223[2] = fRec223[1];
			fRec223[1] = fRec223[0];
			fRec222[2] = fRec222[1];
			fRec222[1] = fRec222[0];
			fRec221[2] = fRec221[1];
			fRec221[1] = fRec221[0];
			fRec231[1] = fRec231[0];
			fRec230[2] = fRec230[1];
			fRec230[1] = fRec230[0];
			fVec30[1] = fVec30[0];
			fRec229[1] = fRec229[0];
			fRec228[2] = fRec228[1];
			fRec228[1] = fRec228[0];
			fRec227[2] = fRec227[1];
			fRec227[1] = fRec227[0];
			fRec235[1] = fRec235[0];
			fRec234[2] = fRec234[1];
			fRec234[1] = fRec234[0];
			fVec31[1] = fVec31[0];
			fRec233[1] = fRec233[0];
			fRec232[2] = fRec232[1];
			fRec232[1] = fRec232[0];
			fRec237[1] = fRec237[0];
			fRec236[2] = fRec236[1];
			fRec236[1] = fRec236[0];
			fRec242[1] = fRec242[0];
			fRec241[2] = fRec241[1];
			fRec241[1] = fRec241[0];
			fRec240[2] = fRec240[1];
			fRec240[1] = fRec240[0];
			fRec239[2] = fRec239[1];
			fRec239[1] = fRec239[0];
			fRec238[2] = fRec238[1];
			fRec238[1] = fRec238[0];
			fRec248[1] = fRec248[0];
			fRec247[2] = fRec247[1];
			fRec247[1] = fRec247[0];
			fVec32[1] = fVec32[0];
			fRec246[1] = fRec246[0];
			fRec245[2] = fRec245[1];
			fRec245[1] = fRec245[0];
			fRec244[2] = fRec244[1];
			fRec244[1] = fRec244[0];
			fRec243[2] = fRec243[1];
			fRec243[1] = fRec243[0];
			fRec253[1] = fRec253[0];
			fRec252[2] = fRec252[1];
			fRec252[1] = fRec252[0];
			fVec33[1] = fVec33[0];
			fRec251[1] = fRec251[0];
			fRec250[2] = fRec250[1];
			fRec250[1] = fRec250[0];
			fRec249[2] = fRec249[1];
			fRec249[1] = fRec249[0];
			fRec257[1] = fRec257[0];
			fRec256[2] = fRec256[1];
			fRec256[1] = fRec256[0];
			fVec34[1] = fVec34[0];
			fRec255[1] = fRec255[0];
			fRec254[2] = fRec254[1];
			fRec254[1] = fRec254[0];
			fRec259[1] = fRec259[0];
			fRec258[2] = fRec258[1];
			fRec258[1] = fRec258[0];
			fRec264[1] = fRec264[0];
			fRec263[2] = fRec263[1];
			fRec263[1] = fRec263[0];
			fRec262[2] = fRec262[1];
			fRec262[1] = fRec262[0];
			fRec261[2] = fRec261[1];
			fRec261[1] = fRec261[0];
			fRec260[2] = fRec260[1];
			fRec260[1] = fRec260[0];
			fRec270[1] = fRec270[0];
			fRec269[2] = fRec269[1];
			fRec269[1] = fRec269[0];
			fVec35[1] = fVec35[0];
			fRec268[1] = fRec268[0];
			fRec267[2] = fRec267[1];
			fRec267[1] = fRec267[0];
			fRec266[2] = fRec266[1];
			fRec266[1] = fRec266[0];
			fRec265[2] = fRec265[1];
			fRec265[1] = fRec265[0];
			fRec275[1] = fRec275[0];
			fRec274[2] = fRec274[1];
			fRec274[1] = fRec274[0];
			fVec36[1] = fVec36[0];
			fRec273[1] = fRec273[0];
			fRec272[2] = fRec272[1];
			fRec272[1] = fRec272[0];
			fRec271[2] = fRec271[1];
			fRec271[1] = fRec271[0];
			fRec279[1] = fRec279[0];
			fRec278[2] = fRec278[1];
			fRec278[1] = fRec278[0];
			fVec37[1] = fVec37[0];
			fRec277[1] = fRec277[0];
			fRec276[2] = fRec276[1];
			fRec276[1] = fRec276[0];
			fRec281[1] = fRec281[0];
			fRec280[2] = fRec280[1];
			fRec280[1] = fRec280[0];
			fRec286[1] = fRec286[0];
			fRec285[2] = fRec285[1];
			fRec285[1] = fRec285[0];
			fRec284[2] = fRec284[1];
			fRec284[1] = fRec284[0];
			fRec283[2] = fRec283[1];
			fRec283[1] = fRec283[0];
			fRec282[2] = fRec282[1];
			fRec282[1] = fRec282[0];
			fRec292[1] = fRec292[0];
			fRec291[2] = fRec291[1];
			fRec291[1] = fRec291[0];
			fVec38[1] = fVec38[0];
			fRec290[1] = fRec290[0];
			fRec289[2] = fRec289[1];
			fRec289[1] = fRec289[0];
			fRec288[2] = fRec288[1];
			fRec288[1] = fRec288[0];
			fRec287[2] = fRec287[1];
			fRec287[1] = fRec287[0];
			fRec297[1] = fRec297[0];
			fRec296[2] = fRec296[1];
			fRec296[1] = fRec296[0];
			fVec39[1] = fVec39[0];
			fRec295[1] = fRec295[0];
			fRec294[2] = fRec294[1];
			fRec294[1] = fRec294[0];
			fRec293[2] = fRec293[1];
			fRec293[1] = fRec293[0];
			fRec301[1] = fRec301[0];
			fRec300[2] = fRec300[1];
			fRec300[1] = fRec300[0];
			fVec40[1] = fVec40[0];
			fRec299[1] = fRec299[0];
			fRec298[2] = fRec298[1];
			fRec298[1] = fRec298[0];
			fRec303[1] = fRec303[0];
			fRec302[2] = fRec302[1];
			fRec302[1] = fRec302[0];
			fRec308[1] = fRec308[0];
			fRec307[2] = fRec307[1];
			fRec307[1] = fRec307[0];
			fRec306[2] = fRec306[1];
			fRec306[1] = fRec306[0];
			fRec305[2] = fRec305[1];
			fRec305[1] = fRec305[0];
			fRec304[2] = fRec304[1];
			fRec304[1] = fRec304[0];
			fRec314[1] = fRec314[0];
			fRec313[2] = fRec313[1];
			fRec313[1] = fRec313[0];
			fVec41[1] = fVec41[0];
			fRec312[1] = fRec312[0];
			fRec311[2] = fRec311[1];
			fRec311[1] = fRec311[0];
			fRec310[2] = fRec310[1];
			fRec310[1] = fRec310[0];
			fRec309[2] = fRec309[1];
			fRec309[1] = fRec309[0];
			fRec319[1] = fRec319[0];
			fRec318[2] = fRec318[1];
			fRec318[1] = fRec318[0];
			fVec42[1] = fVec42[0];
			fRec317[1] = fRec317[0];
			fRec316[2] = fRec316[1];
			fRec316[1] = fRec316[0];
			fRec315[2] = fRec315[1];
			fRec315[1] = fRec315[0];
			fRec323[1] = fRec323[0];
			fRec322[2] = fRec322[1];
			fRec322[1] = fRec322[0];
			fVec43[1] = fVec43[0];
			fRec321[1] = fRec321[0];
			fRec320[2] = fRec320[1];
			fRec320[1] = fRec320[0];
			fRec325[1] = fRec325[0];
			fRec324[2] = fRec324[1];
			fRec324[1] = fRec324[0];
			fRec330[1] = fRec330[0];
			fRec329[2] = fRec329[1];
			fRec329[1] = fRec329[0];
			fRec328[2] = fRec328[1];
			fRec328[1] = fRec328[0];
			fRec327[2] = fRec327[1];
			fRec327[1] = fRec327[0];
			fRec326[2] = fRec326[1];
			fRec326[1] = fRec326[0];
			fRec336[1] = fRec336[0];
			fRec335[2] = fRec335[1];
			fRec335[1] = fRec335[0];
			fVec44[1] = fVec44[0];
			fRec334[1] = fRec334[0];
			fRec333[2] = fRec333[1];
			fRec333[1] = fRec333[0];
			fRec332[2] = fRec332[1];
			fRec332[1] = fRec332[0];
			fRec331[2] = fRec331[1];
			fRec331[1] = fRec331[0];
			fRec341[1] = fRec341[0];
			fRec340[2] = fRec340[1];
			fRec340[1] = fRec340[0];
			fVec45[1] = fVec45[0];
			fRec339[1] = fRec339[0];
			fRec338[2] = fRec338[1];
			fRec338[1] = fRec338[0];
			fRec337[2] = fRec337[1];
			fRec337[1] = fRec337[0];
			fRec345[1] = fRec345[0];
			fRec344[2] = fRec344[1];
			fRec344[1] = fRec344[0];
			fVec46[1] = fVec46[0];
			fRec343[1] = fRec343[0];
			fRec342[2] = fRec342[1];
			fRec342[1] = fRec342[0];
			fRec347[1] = fRec347[0];
			fRec346[2] = fRec346[1];
			fRec346[1] = fRec346[0];
			fRec352[1] = fRec352[0];
			fRec351[2] = fRec351[1];
			fRec351[1] = fRec351[0];
			fRec350[2] = fRec350[1];
			fRec350[1] = fRec350[0];
			fRec349[2] = fRec349[1];
			fRec349[1] = fRec349[0];
			fRec348[2] = fRec348[1];
			fRec348[1] = fRec348[0];
			fRec358[1] = fRec358[0];
			fRec357[2] = fRec357[1];
			fRec357[1] = fRec357[0];
			fVec47[1] = fVec47[0];
			fRec356[1] = fRec356[0];
			fRec355[2] = fRec355[1];
			fRec355[1] = fRec355[0];
			fRec354[2] = fRec354[1];
			fRec354[1] = fRec354[0];
			fRec353[2] = fRec353[1];
			fRec353[1] = fRec353[0];
			fRec363[1] = fRec363[0];
			fRec362[2] = fRec362[1];
			fRec362[1] = fRec362[0];
			fVec48[1] = fVec48[0];
			fRec361[1] = fRec361[0];
			fRec360[2] = fRec360[1];
			fRec360[1] = fRec360[0];
			fRec359[2] = fRec359[1];
			fRec359[1] = fRec359[0];
			fRec367[1] = fRec367[0];
			fRec366[2] = fRec366[1];
			fRec366[1] = fRec366[0];
			fVec49[1] = fVec49[0];
			fRec365[1] = fRec365[0];
			fRec364[2] = fRec364[1];
			fRec364[1] = fRec364[0];
			fRec369[1] = fRec369[0];
			fRec368[2] = fRec368[1];
			fRec368[1] = fRec368[0];
			IOTA = (IOTA + 1);
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			fVec51[1] = fVec51[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fRec4[2] = fRec4[1];
			fRec4[1] = fRec4[0];
			fRec5[2] = fRec5[1];
			fRec5[1] = fRec5[0];
			fRec6[2] = fRec6[1];
			fRec6[1] = fRec6[0];
			fRec7[2] = fRec7[1];
			fRec7[1] = fRec7[0];
			fRec8[2] = fRec8[1];
			fRec8[1] = fRec8[0];
			fRec9[2] = fRec9[1];
			fRec9[1] = fRec9[0];
			fRec10[2] = fRec10[1];
			fRec10[1] = fRec10[0];
			fRec11[2] = fRec11[1];
			fRec11[1] = fRec11[0];
			fRec12[2] = fRec12[1];
			fRec12[1] = fRec12[0];
			fRec13[2] = fRec13[1];
			fRec13[1] = fRec13[0];
			fRec14[2] = fRec14[1];
			fRec14[1] = fRec14[0];
			fRec15[2] = fRec15[1];
			fRec15[1] = fRec15[0];
			
		}
		
	}

	
};

#endif
