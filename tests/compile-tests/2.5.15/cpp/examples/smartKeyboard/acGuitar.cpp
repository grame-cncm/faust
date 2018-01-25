/* ------------------------------------------------------------
name: "acGuitar"
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


#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif
#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class mydsp : public dsp {
	
 private:
	
	int iRec10[2];
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	float fRec29[2];
	FAUSTFLOAT fHslider2;
	float fRec30[2];
	float fRec25[2];
	float fRec31[2];
	FAUSTFLOAT fHslider3;
	int iVec0[2];
	float fRec33[4];
	int IOTA;
	float fRec34[2048];
	float fVec1[2];
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
	float fRec103[4];
	float fRec104[2048];
	float fVec6[2];
	FAUSTFLOAT fHslider9;
	int iVec7[2];
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
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("interface", "SmartKeyboard{  'Number of Keyboards':'7',  'Max Keyboard Polyphony':'0',  'Rounding Mode':'2',  'Keyboard 0 - Number of Keys':'14',   'Keyboard 1 - Number of Keys':'14',  'Keyboard 2 - Number of Keys':'14',  'Keyboard 3 - Number of Keys':'14',  'Keyboard 4 - Number of Keys':'14',  'Keyboard 5 - Number of Keys':'14',  'Keyboard 6 - Number of Keys':'6',  'Keyboard 0 - Lowest Key':'52',  'Keyboard 1 - Lowest Key':'57',  'Keyboard 2 - Lowest Key':'62',  'Keyboard 3 - Lowest Key':'67',  'Keyboard 4 - Lowest Key':'71',  'Keyboard 5 - Lowest Key':'76',  'Keyboard 0 - Send Keyboard Freq':'1',  'Keyboard 1 - Send Keyboard Freq':'1',  'Keyboard 2 - Send Keyboard Freq':'1',  'Keyboard 3 - Send Keyboard Freq':'1',  'Keyboard 4 - Send Keyboard Freq':'1',  'Keyboard 5 - Send Keyboard Freq':'1',  'Keyboard 6 - Piano Keyboard':'0',  'Keyboard 6 - Send Key Status':'1',  'Keyboard 6 - Key 0 - Label':'S0',  'Keyboard 6 - Key 1 - Label':'S1',  'Keyboard 6 - Key 2 - Label':'S2',  'Keyboard 6 - Key 3 - Label':'S3',  'Keyboard 6 - Key 4 - Label':'S4',  'Keyboard 6 - Key 5 - Label':'S5' }");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "acGuitar");
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
	}

	virtual int getNumInputs() {
		return 0;
		
	}
	virtual int getNumOutputs() {
		return 2;
		
	}
	virtual int getInputRate(int channel) {
		int rate;
		switch (channel) {
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
		fConst1 = (0.00882352982f * fConst0);
		fConst2 = (0.00147058826f * fConst0);
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(392.0f);
		fHslider1 = FAUSTFLOAT(1.0f);
		fHslider2 = FAUSTFLOAT(0.5f);
		fHslider3 = FAUSTFLOAT(0.0f);
		fHslider4 = FAUSTFLOAT(493.89999999999998f);
		fHslider5 = FAUSTFLOAT(1.0f);
		fHslider6 = FAUSTFLOAT(0.0f);
		fHslider7 = FAUSTFLOAT(164.80000000000001f);
		fHslider8 = FAUSTFLOAT(1.0f);
		fHslider9 = FAUSTFLOAT(0.0f);
		fHslider10 = FAUSTFLOAT(220.0f);
		fHslider11 = FAUSTFLOAT(1.0f);
		fHslider12 = FAUSTFLOAT(0.0f);
		fHslider13 = FAUSTFLOAT(293.69999999999999f);
		fHslider14 = FAUSTFLOAT(1.0f);
		fHslider15 = FAUSTFLOAT(0.0f);
		fHslider16 = FAUSTFLOAT(659.20000000000005f);
		fHslider17 = FAUSTFLOAT(1.0f);
		fHslider18 = FAUSTFLOAT(0.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iRec10[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec29[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec30[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec25[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec31[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			iVec0[l5] = 0;
			
		}
		for (int l6 = 0; (l6 < 4); l6 = (l6 + 1)) {
			fRec33[l6] = 0.0f;
			
		}
		IOTA = 0;
		for (int l7 = 0; (l7 < 2048); l7 = (l7 + 1)) {
			fRec34[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fVec1[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fVec2[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2048); l10 = (l10 + 1)) {
			fRec32[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec21[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 2048); l12 = (l12 + 1)) {
			fRec17[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec19[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 4); l14 = (l14 + 1)) {
			fRec15[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			iRec6[l15] = 0;
			
		}
		for (int l16 = 0; (l16 < 2048); l16 = (l16 + 1)) {
			fRec2[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec0[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			iRec46[l18] = 0;
			
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec65[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec61[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec66[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			iVec3[l22] = 0;
			
		}
		for (int l23 = 0; (l23 < 4); l23 = (l23 + 1)) {
			fRec68[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 2048); l24 = (l24 + 1)) {
			fRec69[l24] = 0.0f;
			
		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fVec4[l25] = 0.0f;
			
		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fVec5[l26] = 0.0f;
			
		}
		for (int l27 = 0; (l27 < 2048); l27 = (l27 + 1)) {
			fRec67[l27] = 0.0f;
			
		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fRec57[l28] = 0.0f;
			
		}
		for (int l29 = 0; (l29 < 2048); l29 = (l29 + 1)) {
			fRec53[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fRec55[l30] = 0.0f;
			
		}
		for (int l31 = 0; (l31 < 4); l31 = (l31 + 1)) {
			fRec51[l31] = 0.0f;
			
		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			iRec42[l32] = 0;
			
		}
		for (int l33 = 0; (l33 < 2048); l33 = (l33 + 1)) {
			fRec38[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fRec36[l34] = 0.0f;
			
		}
		for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			iRec81[l35] = 0;
			
		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			fRec100[l36] = 0.0f;
			
		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fRec96[l37] = 0.0f;
			
		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec101[l38] = 0.0f;
			
		}
		for (int l39 = 0; (l39 < 4); l39 = (l39 + 1)) {
			fRec103[l39] = 0.0f;
			
		}
		for (int l40 = 0; (l40 < 2048); l40 = (l40 + 1)) {
			fRec104[l40] = 0.0f;
			
		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fVec6[l41] = 0.0f;
			
		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			iVec7[l42] = 0;
			
		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			fVec8[l43] = 0.0f;
			
		}
		for (int l44 = 0; (l44 < 2048); l44 = (l44 + 1)) {
			fRec102[l44] = 0.0f;
			
		}
		for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			fRec92[l45] = 0.0f;
			
		}
		for (int l46 = 0; (l46 < 2048); l46 = (l46 + 1)) {
			fRec88[l46] = 0.0f;
			
		}
		for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			fRec90[l47] = 0.0f;
			
		}
		for (int l48 = 0; (l48 < 4); l48 = (l48 + 1)) {
			fRec86[l48] = 0.0f;
			
		}
		for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			iRec77[l49] = 0;
			
		}
		for (int l50 = 0; (l50 < 2048); l50 = (l50 + 1)) {
			fRec73[l50] = 0.0f;
			
		}
		for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) {
			fRec71[l51] = 0.0f;
			
		}
		for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			iRec116[l52] = 0;
			
		}
		for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			fRec135[l53] = 0.0f;
			
		}
		for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
			fRec131[l54] = 0.0f;
			
		}
		for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			fRec136[l55] = 0.0f;
			
		}
		for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) {
			iVec9[l56] = 0;
			
		}
		for (int l57 = 0; (l57 < 4); l57 = (l57 + 1)) {
			fRec138[l57] = 0.0f;
			
		}
		for (int l58 = 0; (l58 < 2048); l58 = (l58 + 1)) {
			fRec139[l58] = 0.0f;
			
		}
		for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			fVec10[l59] = 0.0f;
			
		}
		for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) {
			fVec11[l60] = 0.0f;
			
		}
		for (int l61 = 0; (l61 < 2048); l61 = (l61 + 1)) {
			fRec137[l61] = 0.0f;
			
		}
		for (int l62 = 0; (l62 < 2); l62 = (l62 + 1)) {
			fRec127[l62] = 0.0f;
			
		}
		for (int l63 = 0; (l63 < 2048); l63 = (l63 + 1)) {
			fRec123[l63] = 0.0f;
			
		}
		for (int l64 = 0; (l64 < 2); l64 = (l64 + 1)) {
			fRec125[l64] = 0.0f;
			
		}
		for (int l65 = 0; (l65 < 4); l65 = (l65 + 1)) {
			fRec121[l65] = 0.0f;
			
		}
		for (int l66 = 0; (l66 < 2); l66 = (l66 + 1)) {
			iRec112[l66] = 0;
			
		}
		for (int l67 = 0; (l67 < 2048); l67 = (l67 + 1)) {
			fRec108[l67] = 0.0f;
			
		}
		for (int l68 = 0; (l68 < 2); l68 = (l68 + 1)) {
			fRec106[l68] = 0.0f;
			
		}
		for (int l69 = 0; (l69 < 2); l69 = (l69 + 1)) {
			iRec151[l69] = 0;
			
		}
		for (int l70 = 0; (l70 < 2); l70 = (l70 + 1)) {
			fRec170[l70] = 0.0f;
			
		}
		for (int l71 = 0; (l71 < 2); l71 = (l71 + 1)) {
			fRec166[l71] = 0.0f;
			
		}
		for (int l72 = 0; (l72 < 2); l72 = (l72 + 1)) {
			fRec171[l72] = 0.0f;
			
		}
		for (int l73 = 0; (l73 < 2); l73 = (l73 + 1)) {
			iVec12[l73] = 0;
			
		}
		for (int l74 = 0; (l74 < 4); l74 = (l74 + 1)) {
			fRec173[l74] = 0.0f;
			
		}
		for (int l75 = 0; (l75 < 2048); l75 = (l75 + 1)) {
			fRec174[l75] = 0.0f;
			
		}
		for (int l76 = 0; (l76 < 2); l76 = (l76 + 1)) {
			fVec13[l76] = 0.0f;
			
		}
		for (int l77 = 0; (l77 < 2); l77 = (l77 + 1)) {
			fVec14[l77] = 0.0f;
			
		}
		for (int l78 = 0; (l78 < 2048); l78 = (l78 + 1)) {
			fRec172[l78] = 0.0f;
			
		}
		for (int l79 = 0; (l79 < 2); l79 = (l79 + 1)) {
			fRec162[l79] = 0.0f;
			
		}
		for (int l80 = 0; (l80 < 2048); l80 = (l80 + 1)) {
			fRec158[l80] = 0.0f;
			
		}
		for (int l81 = 0; (l81 < 2); l81 = (l81 + 1)) {
			fRec160[l81] = 0.0f;
			
		}
		for (int l82 = 0; (l82 < 4); l82 = (l82 + 1)) {
			fRec156[l82] = 0.0f;
			
		}
		for (int l83 = 0; (l83 < 2); l83 = (l83 + 1)) {
			iRec147[l83] = 0;
			
		}
		for (int l84 = 0; (l84 < 2048); l84 = (l84 + 1)) {
			fRec143[l84] = 0.0f;
			
		}
		for (int l85 = 0; (l85 < 2); l85 = (l85 + 1)) {
			fRec141[l85] = 0.0f;
			
		}
		for (int l86 = 0; (l86 < 2); l86 = (l86 + 1)) {
			iRec186[l86] = 0;
			
		}
		for (int l87 = 0; (l87 < 2); l87 = (l87 + 1)) {
			fRec205[l87] = 0.0f;
			
		}
		for (int l88 = 0; (l88 < 2); l88 = (l88 + 1)) {
			fRec201[l88] = 0.0f;
			
		}
		for (int l89 = 0; (l89 < 2); l89 = (l89 + 1)) {
			fRec206[l89] = 0.0f;
			
		}
		for (int l90 = 0; (l90 < 2); l90 = (l90 + 1)) {
			iVec15[l90] = 0;
			
		}
		for (int l91 = 0; (l91 < 4); l91 = (l91 + 1)) {
			fRec208[l91] = 0.0f;
			
		}
		for (int l92 = 0; (l92 < 2048); l92 = (l92 + 1)) {
			fRec209[l92] = 0.0f;
			
		}
		for (int l93 = 0; (l93 < 2); l93 = (l93 + 1)) {
			fVec16[l93] = 0.0f;
			
		}
		for (int l94 = 0; (l94 < 2); l94 = (l94 + 1)) {
			fVec17[l94] = 0.0f;
			
		}
		for (int l95 = 0; (l95 < 2048); l95 = (l95 + 1)) {
			fRec207[l95] = 0.0f;
			
		}
		for (int l96 = 0; (l96 < 2); l96 = (l96 + 1)) {
			fRec197[l96] = 0.0f;
			
		}
		for (int l97 = 0; (l97 < 2048); l97 = (l97 + 1)) {
			fRec193[l97] = 0.0f;
			
		}
		for (int l98 = 0; (l98 < 2); l98 = (l98 + 1)) {
			fRec195[l98] = 0.0f;
			
		}
		for (int l99 = 0; (l99 < 4); l99 = (l99 + 1)) {
			fRec191[l99] = 0.0f;
			
		}
		for (int l100 = 0; (l100 < 2); l100 = (l100 + 1)) {
			iRec182[l100] = 0;
			
		}
		for (int l101 = 0; (l101 < 2048); l101 = (l101 + 1)) {
			fRec178[l101] = 0.0f;
			
		}
		for (int l102 = 0; (l102 < 2); l102 = (l102 + 1)) {
			fRec176[l102] = 0.0f;
			
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
		ui_interface->openVerticalBox("acGuitar");
		ui_interface->addHorizontalSlider("kb0bend", &fHslider8, 1.0f, 0.0f, 10.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("kb0freq", &fHslider7, 164.800003f, 20.0f, 10000.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("kb1bend", &fHslider11, 1.0f, 0.0f, 10.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("kb1freq", &fHslider10, 220.0f, 20.0f, 10000.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("kb2bend", &fHslider14, 1.0f, 0.0f, 10.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("kb2freq", &fHslider13, 293.700012f, 20.0f, 10000.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("kb3bend", &fHslider1, 1.0f, 0.0f, 10.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("kb3freq", &fHslider0, 392.0f, 20.0f, 10000.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("kb4bend", &fHslider5, 1.0f, 0.0f, 10.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("kb4freq", &fHslider4, 493.899994f, 20.0f, 10000.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("kb5bend", &fHslider17, 1.0f, 0.0f, 10.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("kb5freq", &fHslider16, 659.200012f, 20.0f, 10000.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("kb6k0status", &fHslider9, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->addHorizontalSlider("kb6k1status", &fHslider12, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->addHorizontalSlider("kb6k2status", &fHslider15, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->addHorizontalSlider("kb6k3status", &fHslider3, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->addHorizontalSlider("kb6k4status", &fHslider6, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->addHorizontalSlider("kb6k5status", &fHslider18, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->declare(&fHslider2, "acc", "1 0 -10 0 10");
		ui_interface->addHorizontalSlider("pluckPosition", &fHslider2, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = (0.340000004f / (float(fHslider0) * float(fHslider1)));
		float fSlow1 = (0.00100000005f * float(fHslider2));
		float fSlow2 = float(fHslider3);
		int iSlow3 = ((fSlow2 == 1.0f) | (fSlow2 == 4.0f));
		float fSlow4 = (0.340000004f / (float(fHslider4) * float(fHslider5)));
		float fSlow5 = float(fHslider6);
		int iSlow6 = ((fSlow5 == 1.0f) | (fSlow5 == 4.0f));
		float fSlow7 = (0.340000004f / (float(fHslider7) * float(fHslider8)));
		float fSlow8 = float(fHslider9);
		int iSlow9 = ((fSlow8 == 1.0f) | (fSlow8 == 4.0f));
		float fSlow10 = (0.340000004f / (float(fHslider10) * float(fHslider11)));
		float fSlow11 = float(fHslider12);
		int iSlow12 = ((fSlow11 == 1.0f) | (fSlow11 == 4.0f));
		float fSlow13 = (0.340000004f / (float(fHslider13) * float(fHslider14)));
		float fSlow14 = float(fHslider15);
		int iSlow15 = ((fSlow14 == 1.0f) | (fSlow14 == 4.0f));
		float fSlow16 = (0.340000004f / (float(fHslider16) * float(fHslider17)));
		float fSlow17 = float(fHslider18);
		int iSlow18 = ((fSlow17 == 1.0f) | (fSlow17 == 4.0f));
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec10[0] = 0;
			int iRec11 = iRec10[1];
			float fRec14 = (float(iRec6[1]) - (0.997843683f * ((0.699999988f * fRec15[2]) + (0.150000006f * (fRec15[1] + fRec15[3])))));
			fRec29[0] = (fSlow0 + (0.999000013f * fRec29[1]));
			float fTemp0 = (fRec29[0] + -0.109999999f);
			fRec30[0] = (fSlow1 + (0.999000013f * fRec30[1]));
			float fTemp1 = (1.0f - fRec30[0]);
			float fTemp2 = (fConst2 * (fTemp0 * fTemp1));
			float fTemp3 = (fTemp2 + -1.49999499f);
			int iTemp4 = int(fTemp3);
			int iTemp5 = int(min(fConst1, float(max(0, iTemp4))));
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
			int iTemp16 = int(min(fConst1, float(max(0, (iTemp4 + 2)))));
			float fTemp17 = (0.0f - fTemp11);
			float fTemp18 = (0.0f - (0.5f * fTemp13));
			int iTemp19 = int(min(fConst1, float(max(0, (iTemp4 + 1)))));
			float fTemp20 = (0.0f - fTemp9);
			float fTemp21 = (0.0f - (0.5f * fTemp11));
			float fTemp22 = (0.0f - (0.333333343f * fTemp13));
			float fTemp23 = (fTemp7 * fTemp9);
			int iTemp24 = int(min(fConst1, float(max(0, (iTemp4 + 3)))));
			float fTemp25 = (0.0f - fTemp13);
			float fTemp26 = (fTemp23 * fTemp11);
			int iTemp27 = int(min(fConst1, float(max(0, (iTemp4 + 4)))));
			fRec25[0] = (((((fRec2[((IOTA - (iTemp5 + 1)) & 2047)] * fTemp8) * fTemp10) * fTemp12) * fTemp14) + (fTemp15 * ((((0.5f * (((fTemp7 * fRec2[((IOTA - (iTemp16 + 1)) & 2047)]) * fTemp17) * fTemp18)) + (((fRec2[((IOTA - (iTemp19 + 1)) & 2047)] * fTemp20) * fTemp21) * fTemp22)) + (0.166666672f * ((fTemp23 * fRec2[((IOTA - (iTemp24 + 1)) & 2047)]) * fTemp25))) + (0.0416666679f * (fTemp26 * fRec2[((IOTA - (iTemp27 + 1)) & 2047)])))));
			fRec31[0] = ((0.600000024f * fRec25[1]) + (0.400000006f * fRec31[1]));
			float fRec26 = fRec31[0];
			iVec0[0] = iSlow3;
			int iTemp28 = ((iSlow3 - iVec0[1]) > 0);
			fRec33[0] = fRec0[1];
			fRec34[(IOTA & 2047)] = (0.0f - (0.997843683f * ((0.699999988f * fRec33[2]) + (0.150000006f * (fRec33[1] + fRec33[3])))));
			int iRec35 = 0;
			float fTemp29 = (fConst2 * (fTemp0 * fRec30[0]));
			float fTemp30 = (fTemp29 + -1.49999499f);
			int iTemp31 = int(fTemp30);
			int iTemp32 = int(min(fConst1, float(max(0, iTemp31))));
			float fTemp33 = floorf(fTemp30);
			float fTemp34 = (fTemp29 + (-1.0f - fTemp33));
			float fTemp35 = (0.0f - fTemp34);
			float fTemp36 = (fTemp29 + (-2.0f - fTemp33));
			float fTemp37 = (0.0f - (0.5f * fTemp36));
			float fTemp38 = (fTemp29 + (-3.0f - fTemp33));
			float fTemp39 = (0.0f - (0.333333343f * fTemp38));
			float fTemp40 = (fTemp29 + (-4.0f - fTemp33));
			float fTemp41 = (0.0f - (0.25f * fTemp40));
			float fTemp42 = (fTemp29 - fTemp33);
			int iTemp43 = int(min(fConst1, float(max(0, (iTemp31 + 2)))));
			float fTemp44 = (0.0f - fTemp38);
			float fTemp45 = (0.0f - (0.5f * fTemp40));
			int iTemp46 = int(min(fConst1, float(max(0, (iTemp31 + 1)))));
			float fTemp47 = (0.0f - fTemp36);
			float fTemp48 = (0.0f - (0.5f * fTemp38));
			float fTemp49 = (0.0f - (0.333333343f * fTemp40));
			float fTemp50 = (fTemp34 * fTemp36);
			int iTemp51 = int(min(fConst1, float(max(0, (iTemp31 + 3)))));
			float fTemp52 = (0.0f - fTemp40);
			float fTemp53 = (fTemp50 * fTemp38);
			int iTemp54 = int(min(fConst1, float(max(0, (iTemp31 + 4)))));
			fVec1[0] = (((((fRec34[((IOTA - (iTemp32 + 2)) & 2047)] * fTemp35) * fTemp37) * fTemp39) * fTemp41) + (fTemp42 * ((((0.5f * (((fTemp34 * fRec34[((IOTA - (iTemp43 + 2)) & 2047)]) * fTemp44) * fTemp45)) + (((fRec34[((IOTA - (iTemp46 + 2)) & 2047)] * fTemp47) * fTemp48) * fTemp49)) + (0.166666672f * ((fTemp50 * fRec34[((IOTA - (iTemp51 + 2)) & 2047)]) * fTemp52))) + (0.0416666679f * (fTemp53 * fRec34[((IOTA - (iTemp54 + 2)) & 2047)])))));
			fVec2[0] = (float(iTemp28) + fVec1[1]);
			fRec32[(IOTA & 2047)] = ((0.400000006f * fRec32[((IOTA - 1) & 2047)]) + (0.600000024f * fVec2[1]));
			float fRec27 = (((((fTemp8 * fTemp10) * fTemp12) * fTemp14) * fRec32[((IOTA - iTemp5) & 2047)]) + (fTemp15 * ((0.0416666679f * (fTemp26 * fRec32[((IOTA - iTemp27) & 2047)])) + (((((fTemp20 * fTemp21) * fTemp22) * fRec32[((IOTA - iTemp19) & 2047)]) + (0.5f * (((fTemp7 * fTemp17) * fTemp18) * fRec32[((IOTA - iTemp16) & 2047)]))) + (0.166666672f * ((fTemp23 * fTemp25) * fRec32[((IOTA - iTemp24) & 2047)]))))));
			int iRec28 = iRec35;
			fRec21[0] = fRec26;
			float fRec22 = (float(iTemp28) + fRec21[1]);
			float fRec23 = fRec27;
			int iRec24 = iRec28;
			fRec17[(IOTA & 2047)] = fRec22;
			float fRec18 = (((((fTemp35 * fTemp37) * fTemp39) * fTemp41) * fRec17[((IOTA - (iTemp32 + 1)) & 2047)]) + (fTemp42 * (((0.166666672f * ((fTemp50 * fTemp52) * fRec17[((IOTA - (iTemp51 + 1)) & 2047)])) + ((((fTemp47 * fTemp48) * fTemp49) * fRec17[((IOTA - (iTemp46 + 1)) & 2047)]) + (0.5f * (((fTemp34 * fTemp44) * fTemp45) * fRec17[((IOTA - (iTemp43 + 1)) & 2047)])))) + (0.0416666679f * (fTemp53 * fRec17[((IOTA - (iTemp54 + 1)) & 2047)])))));
			fRec19[0] = fRec23;
			int iRec20 = iRec24;
			fRec15[0] = fRec19[1];
			int iRec16 = iRec20;
			float fRec12 = fRec15[1];
			float fRec13 = (fRec15[1] + float(iRec16));
			iRec6[0] = iRec11;
			float fRec7 = fRec14;
			float fRec8 = fRec12;
			float fRec9 = fRec13;
			fRec2[(IOTA & 2047)] = fRec7;
			float fRec3 = fRec18;
			float fRec4 = fRec8;
			float fRec5 = fRec9;
			fRec0[0] = fRec3;
			float fRec1 = fRec5;
			iRec46[0] = 0;
			int iRec47 = iRec46[1];
			float fRec50 = (float(iRec42[1]) - (0.997843683f * ((0.699999988f * fRec51[2]) + (0.150000006f * (fRec51[1] + fRec51[3])))));
			fRec65[0] = (fSlow4 + (0.999000013f * fRec65[1]));
			float fTemp55 = (fRec65[0] + -0.109999999f);
			float fTemp56 = (fConst2 * (fTemp55 * fTemp1));
			float fTemp57 = (fTemp56 + -1.49999499f);
			int iTemp58 = int(fTemp57);
			int iTemp59 = int(min(fConst1, float(max(0, iTemp58))));
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
			int iTemp70 = int(min(fConst1, float(max(0, (iTemp58 + 2)))));
			float fTemp71 = (0.0f - fTemp65);
			float fTemp72 = (0.0f - (0.5f * fTemp67));
			int iTemp73 = int(min(fConst1, float(max(0, (iTemp58 + 1)))));
			float fTemp74 = (0.0f - fTemp63);
			float fTemp75 = (0.0f - (0.5f * fTemp65));
			float fTemp76 = (0.0f - (0.333333343f * fTemp67));
			float fTemp77 = (fTemp61 * fTemp63);
			int iTemp78 = int(min(fConst1, float(max(0, (iTemp58 + 3)))));
			float fTemp79 = (0.0f - fTemp67);
			float fTemp80 = (fTemp77 * fTemp65);
			int iTemp81 = int(min(fConst1, float(max(0, (iTemp58 + 4)))));
			fRec61[0] = (((((fRec38[((IOTA - (iTemp59 + 1)) & 2047)] * fTemp62) * fTemp64) * fTemp66) * fTemp68) + (fTemp69 * ((((0.5f * (((fTemp61 * fRec38[((IOTA - (iTemp70 + 1)) & 2047)]) * fTemp71) * fTemp72)) + (((fRec38[((IOTA - (iTemp73 + 1)) & 2047)] * fTemp74) * fTemp75) * fTemp76)) + (0.166666672f * ((fTemp77 * fRec38[((IOTA - (iTemp78 + 1)) & 2047)]) * fTemp79))) + (0.0416666679f * (fTemp80 * fRec38[((IOTA - (iTemp81 + 1)) & 2047)])))));
			fRec66[0] = ((0.600000024f * fRec61[1]) + (0.400000006f * fRec66[1]));
			float fRec62 = fRec66[0];
			iVec3[0] = iSlow6;
			int iTemp82 = ((iSlow6 - iVec3[1]) > 0);
			fRec68[0] = fRec36[1];
			fRec69[(IOTA & 2047)] = (0.0f - (0.997843683f * ((0.699999988f * fRec68[2]) + (0.150000006f * (fRec68[1] + fRec68[3])))));
			int iRec70 = 0;
			float fTemp83 = (fConst2 * (fTemp55 * fRec30[0]));
			float fTemp84 = (fTemp83 + -1.49999499f);
			int iTemp85 = int(fTemp84);
			int iTemp86 = int(min(fConst1, float(max(0, iTemp85))));
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
			int iTemp97 = int(min(fConst1, float(max(0, (iTemp85 + 2)))));
			float fTemp98 = (0.0f - fTemp92);
			float fTemp99 = (0.0f - (0.5f * fTemp94));
			int iTemp100 = int(min(fConst1, float(max(0, (iTemp85 + 1)))));
			float fTemp101 = (0.0f - fTemp90);
			float fTemp102 = (0.0f - (0.5f * fTemp92));
			float fTemp103 = (0.0f - (0.333333343f * fTemp94));
			float fTemp104 = (fTemp88 * fTemp90);
			int iTemp105 = int(min(fConst1, float(max(0, (iTemp85 + 3)))));
			float fTemp106 = (0.0f - fTemp94);
			float fTemp107 = (fTemp104 * fTemp92);
			int iTemp108 = int(min(fConst1, float(max(0, (iTemp85 + 4)))));
			fVec4[0] = (((((fRec69[((IOTA - (iTemp86 + 2)) & 2047)] * fTemp89) * fTemp91) * fTemp93) * fTemp95) + (fTemp96 * ((((0.5f * (((fTemp88 * fRec69[((IOTA - (iTemp97 + 2)) & 2047)]) * fTemp98) * fTemp99)) + (((fRec69[((IOTA - (iTemp100 + 2)) & 2047)] * fTemp101) * fTemp102) * fTemp103)) + (0.166666672f * ((fTemp104 * fRec69[((IOTA - (iTemp105 + 2)) & 2047)]) * fTemp106))) + (0.0416666679f * (fTemp107 * fRec69[((IOTA - (iTemp108 + 2)) & 2047)])))));
			fVec5[0] = (float(iTemp82) + fVec4[1]);
			fRec67[(IOTA & 2047)] = ((0.400000006f * fRec67[((IOTA - 1) & 2047)]) + (0.600000024f * fVec5[1]));
			float fRec63 = (((((fTemp62 * fTemp64) * fTemp66) * fTemp68) * fRec67[((IOTA - iTemp59) & 2047)]) + (fTemp69 * ((0.0416666679f * (fTemp80 * fRec67[((IOTA - iTemp81) & 2047)])) + (((((fTemp74 * fTemp75) * fTemp76) * fRec67[((IOTA - iTemp73) & 2047)]) + (0.5f * (((fTemp61 * fTemp71) * fTemp72) * fRec67[((IOTA - iTemp70) & 2047)]))) + (0.166666672f * ((fTemp77 * fTemp79) * fRec67[((IOTA - iTemp78) & 2047)]))))));
			int iRec64 = iRec70;
			fRec57[0] = fRec62;
			float fRec58 = (float(iTemp82) + fRec57[1]);
			float fRec59 = fRec63;
			int iRec60 = iRec64;
			fRec53[(IOTA & 2047)] = fRec58;
			float fRec54 = (((((fTemp89 * fTemp91) * fTemp93) * fTemp95) * fRec53[((IOTA - (iTemp86 + 1)) & 2047)]) + (fTemp96 * (((0.166666672f * ((fTemp104 * fTemp106) * fRec53[((IOTA - (iTemp105 + 1)) & 2047)])) + ((((fTemp101 * fTemp102) * fTemp103) * fRec53[((IOTA - (iTemp100 + 1)) & 2047)]) + (0.5f * (((fTemp88 * fTemp98) * fTemp99) * fRec53[((IOTA - (iTemp97 + 1)) & 2047)])))) + (0.0416666679f * (fTemp107 * fRec53[((IOTA - (iTemp108 + 1)) & 2047)])))));
			fRec55[0] = fRec59;
			int iRec56 = iRec60;
			fRec51[0] = fRec55[1];
			int iRec52 = iRec56;
			float fRec48 = fRec51[1];
			float fRec49 = (fRec51[1] + float(iRec52));
			iRec42[0] = iRec47;
			float fRec43 = fRec50;
			float fRec44 = fRec48;
			float fRec45 = fRec49;
			fRec38[(IOTA & 2047)] = fRec43;
			float fRec39 = fRec54;
			float fRec40 = fRec44;
			float fRec41 = fRec45;
			fRec36[0] = fRec39;
			float fRec37 = fRec41;
			iRec81[0] = 0;
			int iRec82 = iRec81[1];
			float fRec85 = (float(iRec77[1]) - (0.997843683f * ((0.699999988f * fRec86[2]) + (0.150000006f * (fRec86[1] + fRec86[3])))));
			fRec100[0] = (fSlow7 + (0.999000013f * fRec100[1]));
			float fTemp109 = (fRec100[0] + -0.109999999f);
			float fTemp110 = (fConst2 * (fTemp1 * fTemp109));
			float fTemp111 = (fTemp110 + -1.49999499f);
			int iTemp112 = int(fTemp111);
			int iTemp113 = int(min(fConst1, float(max(0, iTemp112))));
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
			int iTemp124 = int(min(fConst1, float(max(0, (iTemp112 + 2)))));
			float fTemp125 = (0.0f - fTemp119);
			float fTemp126 = (0.0f - (0.5f * fTemp121));
			int iTemp127 = int(min(fConst1, float(max(0, (iTemp112 + 1)))));
			float fTemp128 = (0.0f - fTemp117);
			float fTemp129 = (0.0f - (0.5f * fTemp119));
			float fTemp130 = (0.0f - (0.333333343f * fTemp121));
			float fTemp131 = (fTemp115 * fTemp117);
			int iTemp132 = int(min(fConst1, float(max(0, (iTemp112 + 3)))));
			float fTemp133 = (0.0f - fTemp121);
			float fTemp134 = (fTemp131 * fTemp119);
			int iTemp135 = int(min(fConst1, float(max(0, (iTemp112 + 4)))));
			fRec96[0] = (((((fRec73[((IOTA - (iTemp113 + 1)) & 2047)] * fTemp116) * fTemp118) * fTemp120) * fTemp122) + (fTemp123 * ((((0.5f * (((fTemp115 * fRec73[((IOTA - (iTemp124 + 1)) & 2047)]) * fTemp125) * fTemp126)) + (((fRec73[((IOTA - (iTemp127 + 1)) & 2047)] * fTemp128) * fTemp129) * fTemp130)) + (0.166666672f * ((fTemp131 * fRec73[((IOTA - (iTemp132 + 1)) & 2047)]) * fTemp133))) + (0.0416666679f * (fTemp134 * fRec73[((IOTA - (iTemp135 + 1)) & 2047)])))));
			fRec101[0] = ((0.400000006f * fRec101[1]) + (0.600000024f * fRec96[1]));
			float fRec97 = fRec101[0];
			fRec103[0] = fRec71[1];
			fRec104[(IOTA & 2047)] = (0.0f - (0.997843683f * ((0.699999988f * fRec103[2]) + (0.150000006f * (fRec103[1] + fRec103[3])))));
			int iRec105 = 0;
			float fTemp136 = (fConst2 * (fRec30[0] * fTemp109));
			float fTemp137 = (fTemp136 + -1.49999499f);
			int iTemp138 = int(fTemp137);
			int iTemp139 = int(min(fConst1, float(max(0, iTemp138))));
			float fTemp140 = floorf(fTemp137);
			float fTemp141 = (fTemp136 + (-1.0f - fTemp140));
			float fTemp142 = (0.0f - fTemp141);
			float fTemp143 = (fTemp136 + (-2.0f - fTemp140));
			float fTemp144 = (0.0f - (0.5f * fTemp143));
			float fTemp145 = (fTemp136 + (-3.0f - fTemp140));
			float fTemp146 = (0.0f - (0.333333343f * fTemp145));
			float fTemp147 = (fTemp136 + (-4.0f - fTemp140));
			float fTemp148 = (0.0f - (0.25f * fTemp147));
			float fTemp149 = (fTemp136 - fTemp140);
			int iTemp150 = int(min(fConst1, float(max(0, (iTemp138 + 2)))));
			float fTemp151 = (0.0f - fTemp145);
			float fTemp152 = (0.0f - (0.5f * fTemp147));
			int iTemp153 = int(min(fConst1, float(max(0, (iTemp138 + 1)))));
			float fTemp154 = (0.0f - fTemp143);
			float fTemp155 = (0.0f - (0.5f * fTemp145));
			float fTemp156 = (0.0f - (0.333333343f * fTemp147));
			float fTemp157 = (fTemp141 * fTemp143);
			int iTemp158 = int(min(fConst1, float(max(0, (iTemp138 + 3)))));
			float fTemp159 = (0.0f - fTemp147);
			float fTemp160 = (fTemp157 * fTemp145);
			int iTemp161 = int(min(fConst1, float(max(0, (iTemp138 + 4)))));
			fVec6[0] = (((((fRec104[((IOTA - (iTemp139 + 2)) & 2047)] * fTemp142) * fTemp144) * fTemp146) * fTemp148) + (fTemp149 * ((((0.5f * (((fTemp141 * fRec104[((IOTA - (iTemp150 + 2)) & 2047)]) * fTemp151) * fTemp152)) + (((fRec104[((IOTA - (iTemp153 + 2)) & 2047)] * fTemp154) * fTemp155) * fTemp156)) + (0.166666672f * ((fTemp157 * fRec104[((IOTA - (iTemp158 + 2)) & 2047)]) * fTemp159))) + (0.0416666679f * (fTemp160 * fRec104[((IOTA - (iTemp161 + 2)) & 2047)])))));
			iVec7[0] = iSlow9;
			int iTemp162 = ((iSlow9 - iVec7[1]) > 0);
			fVec8[0] = (fVec6[1] + float(iTemp162));
			fRec102[(IOTA & 2047)] = ((0.400000006f * fRec102[((IOTA - 1) & 2047)]) + (0.600000024f * fVec8[1]));
			float fRec98 = (((((fTemp116 * fTemp118) * fTemp120) * fTemp122) * fRec102[((IOTA - iTemp113) & 2047)]) + (fTemp123 * ((0.0416666679f * (fTemp134 * fRec102[((IOTA - iTemp135) & 2047)])) + (((((fTemp128 * fTemp129) * fTemp130) * fRec102[((IOTA - iTemp127) & 2047)]) + (0.5f * (((fTemp115 * fTemp125) * fTemp126) * fRec102[((IOTA - iTemp124) & 2047)]))) + (0.166666672f * ((fTemp131 * fTemp133) * fRec102[((IOTA - iTemp132) & 2047)]))))));
			int iRec99 = iRec105;
			fRec92[0] = fRec97;
			float fRec93 = (float(iTemp162) + fRec92[1]);
			float fRec94 = fRec98;
			int iRec95 = iRec99;
			fRec88[(IOTA & 2047)] = fRec93;
			float fRec89 = (((((fTemp142 * fTemp144) * fTemp146) * fTemp148) * fRec88[((IOTA - (iTemp139 + 1)) & 2047)]) + (fTemp149 * (((0.166666672f * ((fTemp157 * fTemp159) * fRec88[((IOTA - (iTemp158 + 1)) & 2047)])) + ((((fTemp154 * fTemp155) * fTemp156) * fRec88[((IOTA - (iTemp153 + 1)) & 2047)]) + (0.5f * (((fTemp141 * fTemp151) * fTemp152) * fRec88[((IOTA - (iTemp150 + 1)) & 2047)])))) + (0.0416666679f * (fTemp160 * fRec88[((IOTA - (iTemp161 + 1)) & 2047)])))));
			fRec90[0] = fRec94;
			int iRec91 = iRec95;
			fRec86[0] = fRec90[1];
			int iRec87 = iRec91;
			float fRec83 = fRec86[1];
			float fRec84 = (float(iRec87) + fRec86[1]);
			iRec77[0] = iRec82;
			float fRec78 = fRec85;
			float fRec79 = fRec83;
			float fRec80 = fRec84;
			fRec73[(IOTA & 2047)] = fRec78;
			float fRec74 = fRec89;
			float fRec75 = fRec79;
			float fRec76 = fRec80;
			fRec71[0] = fRec74;
			float fRec72 = fRec76;
			iRec116[0] = 0;
			int iRec117 = iRec116[1];
			float fRec120 = (float(iRec112[1]) - (0.997843683f * ((0.699999988f * fRec121[2]) + (0.150000006f * (fRec121[1] + fRec121[3])))));
			fRec135[0] = (fSlow10 + (0.999000013f * fRec135[1]));
			float fTemp163 = (fRec135[0] + -0.109999999f);
			float fTemp164 = (fConst2 * (fTemp1 * fTemp163));
			float fTemp165 = (fTemp164 + -1.49999499f);
			int iTemp166 = int(fTemp165);
			int iTemp167 = int(min(fConst1, float(max(0, iTemp166))));
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
			int iTemp178 = int(min(fConst1, float(max(0, (iTemp166 + 2)))));
			float fTemp179 = (0.0f - fTemp173);
			float fTemp180 = (0.0f - (0.5f * fTemp175));
			int iTemp181 = int(min(fConst1, float(max(0, (iTemp166 + 1)))));
			float fTemp182 = (0.0f - fTemp171);
			float fTemp183 = (0.0f - (0.5f * fTemp173));
			float fTemp184 = (0.0f - (0.333333343f * fTemp175));
			float fTemp185 = (fTemp169 * fTemp171);
			int iTemp186 = int(min(fConst1, float(max(0, (iTemp166 + 3)))));
			float fTemp187 = (0.0f - fTemp175);
			float fTemp188 = (fTemp185 * fTemp173);
			int iTemp189 = int(min(fConst1, float(max(0, (iTemp166 + 4)))));
			fRec131[0] = (((((fRec108[((IOTA - (iTemp167 + 1)) & 2047)] * fTemp170) * fTemp172) * fTemp174) * fTemp176) + (fTemp177 * ((((0.5f * (((fTemp169 * fRec108[((IOTA - (iTemp178 + 1)) & 2047)]) * fTemp179) * fTemp180)) + (((fRec108[((IOTA - (iTemp181 + 1)) & 2047)] * fTemp182) * fTemp183) * fTemp184)) + (0.166666672f * ((fTemp185 * fRec108[((IOTA - (iTemp186 + 1)) & 2047)]) * fTemp187))) + (0.0416666679f * (fTemp188 * fRec108[((IOTA - (iTemp189 + 1)) & 2047)])))));
			fRec136[0] = ((0.600000024f * fRec131[1]) + (0.400000006f * fRec136[1]));
			float fRec132 = fRec136[0];
			iVec9[0] = iSlow12;
			int iTemp190 = ((iSlow12 - iVec9[1]) > 0);
			fRec138[0] = fRec106[1];
			fRec139[(IOTA & 2047)] = (0.0f - (0.997843683f * ((0.699999988f * fRec138[2]) + (0.150000006f * (fRec138[1] + fRec138[3])))));
			int iRec140 = 0;
			float fTemp191 = (fConst2 * (fRec30[0] * fTemp163));
			float fTemp192 = (fTemp191 + -1.49999499f);
			int iTemp193 = int(fTemp192);
			int iTemp194 = int(min(fConst1, float(max(0, iTemp193))));
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
			int iTemp205 = int(min(fConst1, float(max(0, (iTemp193 + 2)))));
			float fTemp206 = (0.0f - fTemp200);
			float fTemp207 = (0.0f - (0.5f * fTemp202));
			int iTemp208 = int(min(fConst1, float(max(0, (iTemp193 + 1)))));
			float fTemp209 = (0.0f - fTemp198);
			float fTemp210 = (0.0f - (0.5f * fTemp200));
			float fTemp211 = (0.0f - (0.333333343f * fTemp202));
			float fTemp212 = (fTemp196 * fTemp198);
			int iTemp213 = int(min(fConst1, float(max(0, (iTemp193 + 3)))));
			float fTemp214 = (0.0f - fTemp202);
			float fTemp215 = (fTemp212 * fTemp200);
			int iTemp216 = int(min(fConst1, float(max(0, (iTemp193 + 4)))));
			fVec10[0] = (((((fRec139[((IOTA - (iTemp194 + 2)) & 2047)] * fTemp197) * fTemp199) * fTemp201) * fTemp203) + (fTemp204 * ((((0.5f * (((fTemp196 * fRec139[((IOTA - (iTemp205 + 2)) & 2047)]) * fTemp206) * fTemp207)) + (((fRec139[((IOTA - (iTemp208 + 2)) & 2047)] * fTemp209) * fTemp210) * fTemp211)) + (0.166666672f * ((fTemp212 * fRec139[((IOTA - (iTemp213 + 2)) & 2047)]) * fTemp214))) + (0.0416666679f * (fTemp215 * fRec139[((IOTA - (iTemp216 + 2)) & 2047)])))));
			fVec11[0] = (float(iTemp190) + fVec10[1]);
			fRec137[(IOTA & 2047)] = ((0.400000006f * fRec137[((IOTA - 1) & 2047)]) + (0.600000024f * fVec11[1]));
			float fRec133 = (((((fTemp170 * fTemp172) * fTemp174) * fTemp176) * fRec137[((IOTA - iTemp167) & 2047)]) + (fTemp177 * ((0.0416666679f * (fTemp188 * fRec137[((IOTA - iTemp189) & 2047)])) + (((((fTemp182 * fTemp183) * fTemp184) * fRec137[((IOTA - iTemp181) & 2047)]) + (0.5f * (((fTemp169 * fTemp179) * fTemp180) * fRec137[((IOTA - iTemp178) & 2047)]))) + (0.166666672f * ((fTemp185 * fTemp187) * fRec137[((IOTA - iTemp186) & 2047)]))))));
			int iRec134 = iRec140;
			fRec127[0] = fRec132;
			float fRec128 = (float(iTemp190) + fRec127[1]);
			float fRec129 = fRec133;
			int iRec130 = iRec134;
			fRec123[(IOTA & 2047)] = fRec128;
			float fRec124 = (((((fTemp197 * fTemp199) * fTemp201) * fTemp203) * fRec123[((IOTA - (iTemp194 + 1)) & 2047)]) + (fTemp204 * (((0.166666672f * ((fTemp212 * fTemp214) * fRec123[((IOTA - (iTemp213 + 1)) & 2047)])) + ((((fTemp209 * fTemp210) * fTemp211) * fRec123[((IOTA - (iTemp208 + 1)) & 2047)]) + (0.5f * (((fTemp196 * fTemp206) * fTemp207) * fRec123[((IOTA - (iTemp205 + 1)) & 2047)])))) + (0.0416666679f * (fTemp215 * fRec123[((IOTA - (iTemp216 + 1)) & 2047)])))));
			fRec125[0] = fRec129;
			int iRec126 = iRec130;
			fRec121[0] = fRec125[1];
			int iRec122 = iRec126;
			float fRec118 = fRec121[1];
			float fRec119 = (float(iRec122) + fRec121[1]);
			iRec112[0] = iRec117;
			float fRec113 = fRec120;
			float fRec114 = fRec118;
			float fRec115 = fRec119;
			fRec108[(IOTA & 2047)] = fRec113;
			float fRec109 = fRec124;
			float fRec110 = fRec114;
			float fRec111 = fRec115;
			fRec106[0] = fRec109;
			float fRec107 = fRec111;
			iRec151[0] = 0;
			int iRec152 = iRec151[1];
			float fRec155 = (float(iRec147[1]) - (0.997843683f * ((0.699999988f * fRec156[2]) + (0.150000006f * (fRec156[1] + fRec156[3])))));
			fRec170[0] = (fSlow13 + (0.999000013f * fRec170[1]));
			float fTemp217 = (fRec170[0] + -0.109999999f);
			float fTemp218 = (fConst2 * (fTemp217 * fTemp1));
			float fTemp219 = (fTemp218 + -1.49999499f);
			int iTemp220 = int(fTemp219);
			int iTemp221 = int(min(fConst1, float(max(0, iTemp220))));
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
			int iTemp232 = int(min(fConst1, float(max(0, (iTemp220 + 2)))));
			float fTemp233 = (0.0f - fTemp227);
			float fTemp234 = (0.0f - (0.5f * fTemp229));
			int iTemp235 = int(min(fConst1, float(max(0, (iTemp220 + 1)))));
			float fTemp236 = (0.0f - fTemp225);
			float fTemp237 = (0.0f - (0.5f * fTemp227));
			float fTemp238 = (0.0f - (0.333333343f * fTemp229));
			float fTemp239 = (fTemp223 * fTemp225);
			int iTemp240 = int(min(fConst1, float(max(0, (iTemp220 + 3)))));
			float fTemp241 = (0.0f - fTemp229);
			float fTemp242 = (fTemp239 * fTemp227);
			int iTemp243 = int(min(fConst1, float(max(0, (iTemp220 + 4)))));
			fRec166[0] = (((((fRec143[((IOTA - (iTemp221 + 1)) & 2047)] * fTemp224) * fTemp226) * fTemp228) * fTemp230) + (fTemp231 * ((((0.5f * (((fTemp223 * fRec143[((IOTA - (iTemp232 + 1)) & 2047)]) * fTemp233) * fTemp234)) + (((fRec143[((IOTA - (iTemp235 + 1)) & 2047)] * fTemp236) * fTemp237) * fTemp238)) + (0.166666672f * ((fTemp239 * fRec143[((IOTA - (iTemp240 + 1)) & 2047)]) * fTemp241))) + (0.0416666679f * (fTemp242 * fRec143[((IOTA - (iTemp243 + 1)) & 2047)])))));
			fRec171[0] = ((0.600000024f * fRec166[1]) + (0.400000006f * fRec171[1]));
			float fRec167 = fRec171[0];
			iVec12[0] = iSlow15;
			int iTemp244 = ((iSlow15 - iVec12[1]) > 0);
			fRec173[0] = fRec141[1];
			fRec174[(IOTA & 2047)] = (0.0f - (0.997843683f * ((0.699999988f * fRec173[2]) + (0.150000006f * (fRec173[1] + fRec173[3])))));
			int iRec175 = 0;
			float fTemp245 = (fConst2 * (fTemp217 * fRec30[0]));
			float fTemp246 = (fTemp245 + -1.49999499f);
			int iTemp247 = int(fTemp246);
			int iTemp248 = int(min(fConst1, float(max(0, iTemp247))));
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
			int iTemp259 = int(min(fConst1, float(max(0, (iTemp247 + 2)))));
			float fTemp260 = (0.0f - fTemp254);
			float fTemp261 = (0.0f - (0.5f * fTemp256));
			int iTemp262 = int(min(fConst1, float(max(0, (iTemp247 + 1)))));
			float fTemp263 = (0.0f - fTemp252);
			float fTemp264 = (0.0f - (0.5f * fTemp254));
			float fTemp265 = (0.0f - (0.333333343f * fTemp256));
			float fTemp266 = (fTemp250 * fTemp252);
			int iTemp267 = int(min(fConst1, float(max(0, (iTemp247 + 3)))));
			float fTemp268 = (0.0f - fTemp256);
			float fTemp269 = (fTemp266 * fTemp254);
			int iTemp270 = int(min(fConst1, float(max(0, (iTemp247 + 4)))));
			fVec13[0] = (((((fRec174[((IOTA - (iTemp248 + 2)) & 2047)] * fTemp251) * fTemp253) * fTemp255) * fTemp257) + (fTemp258 * ((((0.5f * (((fTemp250 * fRec174[((IOTA - (iTemp259 + 2)) & 2047)]) * fTemp260) * fTemp261)) + (((fRec174[((IOTA - (iTemp262 + 2)) & 2047)] * fTemp263) * fTemp264) * fTemp265)) + (0.166666672f * ((fTemp266 * fRec174[((IOTA - (iTemp267 + 2)) & 2047)]) * fTemp268))) + (0.0416666679f * (fTemp269 * fRec174[((IOTA - (iTemp270 + 2)) & 2047)])))));
			fVec14[0] = (float(iTemp244) + fVec13[1]);
			fRec172[(IOTA & 2047)] = ((0.400000006f * fRec172[((IOTA - 1) & 2047)]) + (0.600000024f * fVec14[1]));
			float fRec168 = (((((fTemp224 * fTemp226) * fTemp228) * fTemp230) * fRec172[((IOTA - iTemp221) & 2047)]) + (fTemp231 * ((0.0416666679f * (fTemp242 * fRec172[((IOTA - iTemp243) & 2047)])) + (((((fTemp236 * fTemp237) * fTemp238) * fRec172[((IOTA - iTemp235) & 2047)]) + (0.5f * (((fTemp223 * fTemp233) * fTemp234) * fRec172[((IOTA - iTemp232) & 2047)]))) + (0.166666672f * ((fTemp239 * fTemp241) * fRec172[((IOTA - iTemp240) & 2047)]))))));
			int iRec169 = iRec175;
			fRec162[0] = fRec167;
			float fRec163 = (float(iTemp244) + fRec162[1]);
			float fRec164 = fRec168;
			int iRec165 = iRec169;
			fRec158[(IOTA & 2047)] = fRec163;
			float fRec159 = (((((fTemp251 * fTemp253) * fTemp255) * fTemp257) * fRec158[((IOTA - (iTemp248 + 1)) & 2047)]) + (fTemp258 * (((0.166666672f * ((fTemp266 * fTemp268) * fRec158[((IOTA - (iTemp267 + 1)) & 2047)])) + ((((fTemp263 * fTemp264) * fTemp265) * fRec158[((IOTA - (iTemp262 + 1)) & 2047)]) + (0.5f * (((fTemp250 * fTemp260) * fTemp261) * fRec158[((IOTA - (iTemp259 + 1)) & 2047)])))) + (0.0416666679f * (fTemp269 * fRec158[((IOTA - (iTemp270 + 1)) & 2047)])))));
			fRec160[0] = fRec164;
			int iRec161 = iRec165;
			fRec156[0] = fRec160[1];
			int iRec157 = iRec161;
			float fRec153 = fRec156[1];
			float fRec154 = (fRec156[1] + float(iRec157));
			iRec147[0] = iRec152;
			float fRec148 = fRec155;
			float fRec149 = fRec153;
			float fRec150 = fRec154;
			fRec143[(IOTA & 2047)] = fRec148;
			float fRec144 = fRec159;
			float fRec145 = fRec149;
			float fRec146 = fRec150;
			fRec141[0] = fRec144;
			float fRec142 = fRec146;
			iRec186[0] = 0;
			int iRec187 = iRec186[1];
			float fRec190 = (float(iRec182[1]) - (0.997843683f * ((0.699999988f * fRec191[2]) + (0.150000006f * (fRec191[1] + fRec191[3])))));
			fRec205[0] = (fSlow16 + (0.999000013f * fRec205[1]));
			float fTemp271 = (fRec205[0] + -0.109999999f);
			float fTemp272 = (fConst2 * (fTemp271 * fTemp1));
			float fTemp273 = (fTemp272 + -1.49999499f);
			int iTemp274 = int(fTemp273);
			int iTemp275 = int(min(fConst1, float(max(0, iTemp274))));
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
			int iTemp286 = int(min(fConst1, float(max(0, (iTemp274 + 2)))));
			float fTemp287 = (0.0f - fTemp281);
			float fTemp288 = (0.0f - (0.5f * fTemp283));
			int iTemp289 = int(min(fConst1, float(max(0, (iTemp274 + 1)))));
			float fTemp290 = (0.0f - fTemp279);
			float fTemp291 = (0.0f - (0.5f * fTemp281));
			float fTemp292 = (0.0f - (0.333333343f * fTemp283));
			float fTemp293 = (fTemp277 * fTemp279);
			int iTemp294 = int(min(fConst1, float(max(0, (iTemp274 + 3)))));
			float fTemp295 = (0.0f - fTemp283);
			float fTemp296 = (fTemp293 * fTemp281);
			int iTemp297 = int(min(fConst1, float(max(0, (iTemp274 + 4)))));
			fRec201[0] = (((((fRec178[((IOTA - (iTemp275 + 1)) & 2047)] * fTemp278) * fTemp280) * fTemp282) * fTemp284) + (fTemp285 * ((((0.5f * (((fTemp277 * fRec178[((IOTA - (iTemp286 + 1)) & 2047)]) * fTemp287) * fTemp288)) + (((fRec178[((IOTA - (iTemp289 + 1)) & 2047)] * fTemp290) * fTemp291) * fTemp292)) + (0.166666672f * ((fTemp293 * fRec178[((IOTA - (iTemp294 + 1)) & 2047)]) * fTemp295))) + (0.0416666679f * (fTemp296 * fRec178[((IOTA - (iTemp297 + 1)) & 2047)])))));
			fRec206[0] = ((0.600000024f * fRec201[1]) + (0.400000006f * fRec206[1]));
			float fRec202 = fRec206[0];
			iVec15[0] = iSlow18;
			int iTemp298 = ((iSlow18 - iVec15[1]) > 0);
			fRec208[0] = fRec176[1];
			fRec209[(IOTA & 2047)] = (0.0f - (0.997843683f * ((0.699999988f * fRec208[2]) + (0.150000006f * (fRec208[1] + fRec208[3])))));
			int iRec210 = 0;
			float fTemp299 = (fConst2 * (fTemp271 * fRec30[0]));
			float fTemp300 = (fTemp299 + -1.49999499f);
			int iTemp301 = int(fTemp300);
			int iTemp302 = int(min(fConst1, float(max(0, iTemp301))));
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
			int iTemp313 = int(min(fConst1, float(max(0, (iTemp301 + 2)))));
			float fTemp314 = (0.0f - fTemp308);
			float fTemp315 = (0.0f - (0.5f * fTemp310));
			int iTemp316 = int(min(fConst1, float(max(0, (iTemp301 + 1)))));
			float fTemp317 = (0.0f - fTemp306);
			float fTemp318 = (0.0f - (0.5f * fTemp308));
			float fTemp319 = (0.0f - (0.333333343f * fTemp310));
			float fTemp320 = (fTemp304 * fTemp306);
			int iTemp321 = int(min(fConst1, float(max(0, (iTemp301 + 3)))));
			float fTemp322 = (0.0f - fTemp310);
			float fTemp323 = (fTemp320 * fTemp308);
			int iTemp324 = int(min(fConst1, float(max(0, (iTemp301 + 4)))));
			fVec16[0] = (((((fRec209[((IOTA - (iTemp302 + 2)) & 2047)] * fTemp305) * fTemp307) * fTemp309) * fTemp311) + (fTemp312 * ((((0.5f * (((fTemp304 * fRec209[((IOTA - (iTemp313 + 2)) & 2047)]) * fTemp314) * fTemp315)) + (((fRec209[((IOTA - (iTemp316 + 2)) & 2047)] * fTemp317) * fTemp318) * fTemp319)) + (0.166666672f * ((fTemp320 * fRec209[((IOTA - (iTemp321 + 2)) & 2047)]) * fTemp322))) + (0.0416666679f * (fTemp323 * fRec209[((IOTA - (iTemp324 + 2)) & 2047)])))));
			fVec17[0] = (float(iTemp298) + fVec16[1]);
			fRec207[(IOTA & 2047)] = ((0.400000006f * fRec207[((IOTA - 1) & 2047)]) + (0.600000024f * fVec17[1]));
			float fRec203 = (((((fTemp278 * fTemp280) * fTemp282) * fTemp284) * fRec207[((IOTA - iTemp275) & 2047)]) + (fTemp285 * ((0.0416666679f * (fTemp296 * fRec207[((IOTA - iTemp297) & 2047)])) + (((((fTemp290 * fTemp291) * fTemp292) * fRec207[((IOTA - iTemp289) & 2047)]) + (0.5f * (((fTemp277 * fTemp287) * fTemp288) * fRec207[((IOTA - iTemp286) & 2047)]))) + (0.166666672f * ((fTemp293 * fTemp295) * fRec207[((IOTA - iTemp294) & 2047)]))))));
			int iRec204 = iRec210;
			fRec197[0] = fRec202;
			float fRec198 = (float(iTemp298) + fRec197[1]);
			float fRec199 = fRec203;
			int iRec200 = iRec204;
			fRec193[(IOTA & 2047)] = fRec198;
			float fRec194 = (((((fTemp305 * fTemp307) * fTemp309) * fTemp311) * fRec193[((IOTA - (iTemp302 + 1)) & 2047)]) + (fTemp312 * (((0.166666672f * ((fTemp320 * fTemp322) * fRec193[((IOTA - (iTemp321 + 1)) & 2047)])) + ((((fTemp317 * fTemp318) * fTemp319) * fRec193[((IOTA - (iTemp316 + 1)) & 2047)]) + (0.5f * (((fTemp304 * fTemp314) * fTemp315) * fRec193[((IOTA - (iTemp313 + 1)) & 2047)])))) + (0.0416666679f * (fTemp323 * fRec193[((IOTA - (iTemp324 + 1)) & 2047)])))));
			fRec195[0] = fRec199;
			int iRec196 = iRec200;
			fRec191[0] = fRec195[1];
			int iRec192 = iRec196;
			float fRec188 = fRec191[1];
			float fRec189 = (fRec191[1] + float(iRec192));
			iRec182[0] = iRec187;
			float fRec183 = fRec190;
			float fRec184 = fRec188;
			float fRec185 = fRec189;
			fRec178[(IOTA & 2047)] = fRec183;
			float fRec179 = fRec194;
			float fRec180 = fRec184;
			float fRec181 = fRec185;
			fRec176[0] = fRec179;
			float fRec177 = fRec181;
			float fTemp325 = (((((fRec1 + fRec37) + fRec72) + fRec107) + fRec142) + fRec177);
			output0[i] = FAUSTFLOAT(fTemp325);
			output1[i] = FAUSTFLOAT(fTemp325);
			iRec10[1] = iRec10[0];
			fRec29[1] = fRec29[0];
			fRec30[1] = fRec30[0];
			fRec25[1] = fRec25[0];
			fRec31[1] = fRec31[0];
			iVec0[1] = iVec0[0];
			for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				fRec33[j0] = fRec33[(j0 - 1)];
				
			}
			IOTA = (IOTA + 1);
			fVec1[1] = fVec1[0];
			fVec2[1] = fVec2[0];
			fRec21[1] = fRec21[0];
			fRec19[1] = fRec19[0];
			for (int j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				fRec15[j1] = fRec15[(j1 - 1)];
				
			}
			iRec6[1] = iRec6[0];
			fRec0[1] = fRec0[0];
			iRec46[1] = iRec46[0];
			fRec65[1] = fRec65[0];
			fRec61[1] = fRec61[0];
			fRec66[1] = fRec66[0];
			iVec3[1] = iVec3[0];
			for (int j2 = 3; (j2 > 0); j2 = (j2 - 1)) {
				fRec68[j2] = fRec68[(j2 - 1)];
				
			}
			fVec4[1] = fVec4[0];
			fVec5[1] = fVec5[0];
			fRec57[1] = fRec57[0];
			fRec55[1] = fRec55[0];
			for (int j3 = 3; (j3 > 0); j3 = (j3 - 1)) {
				fRec51[j3] = fRec51[(j3 - 1)];
				
			}
			iRec42[1] = iRec42[0];
			fRec36[1] = fRec36[0];
			iRec81[1] = iRec81[0];
			fRec100[1] = fRec100[0];
			fRec96[1] = fRec96[0];
			fRec101[1] = fRec101[0];
			for (int j4 = 3; (j4 > 0); j4 = (j4 - 1)) {
				fRec103[j4] = fRec103[(j4 - 1)];
				
			}
			fVec6[1] = fVec6[0];
			iVec7[1] = iVec7[0];
			fVec8[1] = fVec8[0];
			fRec92[1] = fRec92[0];
			fRec90[1] = fRec90[0];
			for (int j5 = 3; (j5 > 0); j5 = (j5 - 1)) {
				fRec86[j5] = fRec86[(j5 - 1)];
				
			}
			iRec77[1] = iRec77[0];
			fRec71[1] = fRec71[0];
			iRec116[1] = iRec116[0];
			fRec135[1] = fRec135[0];
			fRec131[1] = fRec131[0];
			fRec136[1] = fRec136[0];
			iVec9[1] = iVec9[0];
			for (int j6 = 3; (j6 > 0); j6 = (j6 - 1)) {
				fRec138[j6] = fRec138[(j6 - 1)];
				
			}
			fVec10[1] = fVec10[0];
			fVec11[1] = fVec11[0];
			fRec127[1] = fRec127[0];
			fRec125[1] = fRec125[0];
			for (int j7 = 3; (j7 > 0); j7 = (j7 - 1)) {
				fRec121[j7] = fRec121[(j7 - 1)];
				
			}
			iRec112[1] = iRec112[0];
			fRec106[1] = fRec106[0];
			iRec151[1] = iRec151[0];
			fRec170[1] = fRec170[0];
			fRec166[1] = fRec166[0];
			fRec171[1] = fRec171[0];
			iVec12[1] = iVec12[0];
			for (int j8 = 3; (j8 > 0); j8 = (j8 - 1)) {
				fRec173[j8] = fRec173[(j8 - 1)];
				
			}
			fVec13[1] = fVec13[0];
			fVec14[1] = fVec14[0];
			fRec162[1] = fRec162[0];
			fRec160[1] = fRec160[0];
			for (int j9 = 3; (j9 > 0); j9 = (j9 - 1)) {
				fRec156[j9] = fRec156[(j9 - 1)];
				
			}
			iRec147[1] = iRec147[0];
			fRec141[1] = fRec141[0];
			iRec186[1] = iRec186[0];
			fRec205[1] = fRec205[0];
			fRec201[1] = fRec201[0];
			fRec206[1] = fRec206[0];
			iVec15[1] = iVec15[0];
			for (int j10 = 3; (j10 > 0); j10 = (j10 - 1)) {
				fRec208[j10] = fRec208[(j10 - 1)];
				
			}
			fVec16[1] = fVec16[0];
			fVec17[1] = fVec17[0];
			fRec197[1] = fRec197[0];
			fRec195[1] = fRec195[0];
			for (int j11 = 3; (j11 > 0); j11 = (j11 - 1)) {
				fRec191[j11] = fRec191[(j11 - 1)];
				
			}
			iRec182[1] = iRec182[0];
			fRec176[1] = fRec176[0];
			
		}
		
	}

	
};

#endif
