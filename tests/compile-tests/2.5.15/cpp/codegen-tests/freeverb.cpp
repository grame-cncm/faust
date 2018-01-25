/* ------------------------------------------------------------
name: "freeverb"
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
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("name", "freeverb");
	}

	virtual int getNumInputs() {
		return 2;
		
	}
	virtual int getNumOutputs() {
		return 2;
		
	}
	virtual int getInputRate(int channel) {
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
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.33329999999999999f);
		fHslider1 = FAUSTFLOAT(0.5f);
		fHslider2 = FAUSTFLOAT(0.5f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec9[l0] = 0.0f;
			
		}
		IOTA = 0;
		for (int l1 = 0; (l1 < 2048); l1 = (l1 + 1)) {
			fVec0[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec8[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec11[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2048); l4 = (l4 + 1)) {
			fVec1[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec10[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec13[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2048); l7 = (l7 + 1)) {
			fVec2[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec12[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec15[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2048); l10 = (l10 + 1)) {
			fVec3[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec14[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec17[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 2048); l13 = (l13 + 1)) {
			fVec4[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec16[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec19[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 2048); l16 = (l16 + 1)) {
			fVec5[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec18[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec21[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 2048); l19 = (l19 + 1)) {
			fVec6[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec20[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec23[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 2048); l22 = (l22 + 1)) {
			fVec7[l22] = 0.0f;
			
		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec22[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 1024); l24 = (l24 + 1)) {
			fVec8[l24] = 0.0f;
			
		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fRec6[l25] = 0.0f;
			
		}
		for (int l26 = 0; (l26 < 512); l26 = (l26 + 1)) {
			fVec9[l26] = 0.0f;
			
		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fRec4[l27] = 0.0f;
			
		}
		for (int l28 = 0; (l28 < 512); l28 = (l28 + 1)) {
			fVec10[l28] = 0.0f;
			
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec2[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 256); l30 = (l30 + 1)) {
			fVec11[l30] = 0.0f;
			
		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			fRec0[l31] = 0.0f;
			
		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fRec33[l32] = 0.0f;
			
		}
		for (int l33 = 0; (l33 < 2048); l33 = (l33 + 1)) {
			fVec12[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fRec32[l34] = 0.0f;
			
		}
		for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			fRec35[l35] = 0.0f;
			
		}
		for (int l36 = 0; (l36 < 2048); l36 = (l36 + 1)) {
			fVec13[l36] = 0.0f;
			
		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fRec34[l37] = 0.0f;
			
		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec37[l38] = 0.0f;
			
		}
		for (int l39 = 0; (l39 < 2048); l39 = (l39 + 1)) {
			fVec14[l39] = 0.0f;
			
		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			fRec36[l40] = 0.0f;
			
		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fRec39[l41] = 0.0f;
			
		}
		for (int l42 = 0; (l42 < 2048); l42 = (l42 + 1)) {
			fVec15[l42] = 0.0f;
			
		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			fRec38[l43] = 0.0f;
			
		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fRec41[l44] = 0.0f;
			
		}
		for (int l45 = 0; (l45 < 2048); l45 = (l45 + 1)) {
			fVec16[l45] = 0.0f;
			
		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			fRec40[l46] = 0.0f;
			
		}
		for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			fRec43[l47] = 0.0f;
			
		}
		for (int l48 = 0; (l48 < 2048); l48 = (l48 + 1)) {
			fVec17[l48] = 0.0f;
			
		}
		for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			fRec42[l49] = 0.0f;
			
		}
		for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			fRec45[l50] = 0.0f;
			
		}
		for (int l51 = 0; (l51 < 2048); l51 = (l51 + 1)) {
			fVec18[l51] = 0.0f;
			
		}
		for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			fRec44[l52] = 0.0f;
			
		}
		for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			fRec47[l53] = 0.0f;
			
		}
		for (int l54 = 0; (l54 < 2048); l54 = (l54 + 1)) {
			fVec19[l54] = 0.0f;
			
		}
		for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			fRec46[l55] = 0.0f;
			
		}
		for (int l56 = 0; (l56 < 1024); l56 = (l56 + 1)) {
			fVec20[l56] = 0.0f;
			
		}
		for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			fRec30[l57] = 0.0f;
			
		}
		for (int l58 = 0; (l58 < 512); l58 = (l58 + 1)) {
			fVec21[l58] = 0.0f;
			
		}
		for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			fRec28[l59] = 0.0f;
			
		}
		for (int l60 = 0; (l60 < 512); l60 = (l60 + 1)) {
			fVec22[l60] = 0.0f;
			
		}
		for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			fRec26[l61] = 0.0f;
			
		}
		for (int l62 = 0; (l62 < 256); l62 = (l62 + 1)) {
			fVec23[l62] = 0.0f;
			
		}
		for (int l63 = 0; (l63 < 2); l63 = (l63 + 1)) {
			fRec24[l63] = 0.0f;
			
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
		ui_interface->openVerticalBox("Freeverb");
		ui_interface->addHorizontalSlider("Damp", &fHslider2, 0.5f, 0.0f, 1.0f, 0.0250000004f);
		ui_interface->addHorizontalSlider("RoomSize", &fHslider1, 0.5f, 0.0f, 1.0f, 0.0250000004f);
		ui_interface->addHorizontalSlider("Wet", &fHslider0, 0.333299994f, 0.0f, 1.0f, 0.0250000004f);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = float(fHslider0);
		float fSlow1 = ((0.280000001f * float(fHslider1)) + 0.699999988f);
		float fSlow2 = (0.400000006f * float(fHslider2));
		float fSlow3 = (1.0f - fSlow2);
		float fSlow4 = (1.0f - fSlow0);
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec9[0] = ((fSlow2 * fRec9[1]) + (fSlow3 * fRec8[1]));
			float fTemp0 = float(input0[i]);
			float fTemp1 = float(input1[i]);
			float fTemp2 = (0.0149999997f * (fTemp0 + fTemp1));
			fVec0[(IOTA & 2047)] = ((fSlow1 * fRec9[0]) + fTemp2);
			fRec8[0] = fVec0[((IOTA - 1116) & 2047)];
			fRec11[0] = ((fSlow2 * fRec11[1]) + (fSlow3 * fRec10[1]));
			fVec1[(IOTA & 2047)] = (fTemp2 + (fSlow1 * fRec11[0]));
			fRec10[0] = fVec1[((IOTA - 1188) & 2047)];
			fRec13[0] = ((fSlow2 * fRec13[1]) + (fSlow3 * fRec12[1]));
			fVec2[(IOTA & 2047)] = (fTemp2 + (fSlow1 * fRec13[0]));
			fRec12[0] = fVec2[((IOTA - 1277) & 2047)];
			fRec15[0] = ((fSlow2 * fRec15[1]) + (fSlow3 * fRec14[1]));
			fVec3[(IOTA & 2047)] = (fTemp2 + (fSlow1 * fRec15[0]));
			fRec14[0] = fVec3[((IOTA - 1356) & 2047)];
			fRec17[0] = ((fSlow2 * fRec17[1]) + (fSlow3 * fRec16[1]));
			fVec4[(IOTA & 2047)] = (fTemp2 + (fSlow1 * fRec17[0]));
			fRec16[0] = fVec4[((IOTA - 1422) & 2047)];
			fRec19[0] = ((fSlow2 * fRec19[1]) + (fSlow3 * fRec18[1]));
			fVec5[(IOTA & 2047)] = (fTemp2 + (fSlow1 * fRec19[0]));
			fRec18[0] = fVec5[((IOTA - 1491) & 2047)];
			fRec21[0] = ((fSlow2 * fRec21[1]) + (fSlow3 * fRec20[1]));
			fVec6[(IOTA & 2047)] = (fTemp2 + (fSlow1 * fRec21[0]));
			fRec20[0] = fVec6[((IOTA - 1557) & 2047)];
			fRec23[0] = ((fSlow2 * fRec23[1]) + (fSlow3 * fRec22[1]));
			fVec7[(IOTA & 2047)] = (fTemp2 + (fSlow1 * fRec23[0]));
			fRec22[0] = fVec7[((IOTA - 1617) & 2047)];
			float fTemp3 = (((((((fRec8[0] + fRec10[0]) + fRec12[0]) + fRec14[0]) + fRec16[0]) + fRec18[0]) + fRec20[0]) + fRec22[0]);
			fVec8[(IOTA & 1023)] = (fTemp3 + (0.5f * fRec6[1]));
			fRec6[0] = fVec8[((IOTA - 556) & 1023)];
			float fRec7 = (fRec6[1] - fTemp3);
			fVec9[(IOTA & 511)] = (fRec7 + (0.5f * fRec4[1]));
			fRec4[0] = fVec9[((IOTA - 441) & 511)];
			float fRec5 = (fRec4[1] - fRec7);
			fVec10[(IOTA & 511)] = (fRec5 + (0.5f * fRec2[1]));
			fRec2[0] = fVec10[((IOTA - 341) & 511)];
			float fRec3 = (fRec2[1] - fRec5);
			fVec11[(IOTA & 255)] = (fRec3 + (0.5f * fRec0[1]));
			fRec0[0] = fVec11[((IOTA - 225) & 255)];
			float fRec1 = (fRec0[1] - fRec3);
			output0[i] = FAUSTFLOAT(((fSlow0 * fRec1) + (fSlow4 * fTemp0)));
			fRec33[0] = ((fSlow2 * fRec33[1]) + (fSlow3 * fRec32[1]));
			fVec12[(IOTA & 2047)] = (fTemp2 + (fSlow1 * fRec33[0]));
			fRec32[0] = fVec12[((IOTA - 1139) & 2047)];
			fRec35[0] = ((fSlow2 * fRec35[1]) + (fSlow3 * fRec34[1]));
			fVec13[(IOTA & 2047)] = (fTemp2 + (fSlow1 * fRec35[0]));
			fRec34[0] = fVec13[((IOTA - 1211) & 2047)];
			fRec37[0] = ((fSlow2 * fRec37[1]) + (fSlow3 * fRec36[1]));
			fVec14[(IOTA & 2047)] = (fTemp2 + (fSlow1 * fRec37[0]));
			fRec36[0] = fVec14[((IOTA - 1300) & 2047)];
			fRec39[0] = ((fSlow2 * fRec39[1]) + (fSlow3 * fRec38[1]));
			fVec15[(IOTA & 2047)] = (fTemp2 + (fSlow1 * fRec39[0]));
			fRec38[0] = fVec15[((IOTA - 1379) & 2047)];
			fRec41[0] = ((fSlow2 * fRec41[1]) + (fSlow3 * fRec40[1]));
			fVec16[(IOTA & 2047)] = (fTemp2 + (fSlow1 * fRec41[0]));
			fRec40[0] = fVec16[((IOTA - 1445) & 2047)];
			fRec43[0] = ((fSlow2 * fRec43[1]) + (fSlow3 * fRec42[1]));
			fVec17[(IOTA & 2047)] = (fTemp2 + (fSlow1 * fRec43[0]));
			fRec42[0] = fVec17[((IOTA - 1514) & 2047)];
			fRec45[0] = ((fSlow2 * fRec45[1]) + (fSlow3 * fRec44[1]));
			fVec18[(IOTA & 2047)] = (fTemp2 + (fSlow1 * fRec45[0]));
			fRec44[0] = fVec18[((IOTA - 1580) & 2047)];
			fRec47[0] = ((fSlow2 * fRec47[1]) + (fSlow3 * fRec46[1]));
			fVec19[(IOTA & 2047)] = (fTemp2 + (fSlow1 * fRec47[0]));
			fRec46[0] = fVec19[((IOTA - 1640) & 2047)];
			float fTemp4 = (((((((fRec32[0] + fRec34[0]) + fRec36[0]) + fRec38[0]) + fRec40[0]) + fRec42[0]) + fRec44[0]) + fRec46[0]);
			fVec20[(IOTA & 1023)] = (fTemp4 + (0.5f * fRec30[1]));
			fRec30[0] = fVec20[((IOTA - 579) & 1023)];
			float fRec31 = (fRec30[1] - fTemp4);
			fVec21[(IOTA & 511)] = (fRec31 + (0.5f * fRec28[1]));
			fRec28[0] = fVec21[((IOTA - 464) & 511)];
			float fRec29 = (fRec28[1] - fRec31);
			fVec22[(IOTA & 511)] = (fRec29 + (0.5f * fRec26[1]));
			fRec26[0] = fVec22[((IOTA - 364) & 511)];
			float fRec27 = (fRec26[1] - fRec29);
			fVec23[(IOTA & 255)] = (fRec27 + (0.5f * fRec24[1]));
			fRec24[0] = fVec23[((IOTA - 248) & 255)];
			float fRec25 = (fRec24[1] - fRec27);
			output1[i] = FAUSTFLOAT(((fSlow0 * fRec25) + (fSlow4 * fTemp1)));
			fRec9[1] = fRec9[0];
			IOTA = (IOTA + 1);
			fRec8[1] = fRec8[0];
			fRec11[1] = fRec11[0];
			fRec10[1] = fRec10[0];
			fRec13[1] = fRec13[0];
			fRec12[1] = fRec12[0];
			fRec15[1] = fRec15[0];
			fRec14[1] = fRec14[0];
			fRec17[1] = fRec17[0];
			fRec16[1] = fRec16[0];
			fRec19[1] = fRec19[0];
			fRec18[1] = fRec18[0];
			fRec21[1] = fRec21[0];
			fRec20[1] = fRec20[0];
			fRec23[1] = fRec23[0];
			fRec22[1] = fRec22[0];
			fRec6[1] = fRec6[0];
			fRec4[1] = fRec4[0];
			fRec2[1] = fRec2[0];
			fRec0[1] = fRec0[0];
			fRec33[1] = fRec33[0];
			fRec32[1] = fRec32[0];
			fRec35[1] = fRec35[0];
			fRec34[1] = fRec34[0];
			fRec37[1] = fRec37[0];
			fRec36[1] = fRec36[0];
			fRec39[1] = fRec39[0];
			fRec38[1] = fRec38[0];
			fRec41[1] = fRec41[0];
			fRec40[1] = fRec40[0];
			fRec43[1] = fRec43[0];
			fRec42[1] = fRec42[0];
			fRec45[1] = fRec45[0];
			fRec44[1] = fRec44[0];
			fRec47[1] = fRec47[0];
			fRec46[1] = fRec46[0];
			fRec30[1] = fRec30[0];
			fRec28[1] = fRec28[0];
			fRec26[1] = fRec26[0];
			fRec24[1] = fRec24[0];
			
		}
		
	}

	
};

#endif
