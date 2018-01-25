/* ------------------------------------------------------------
name: "elecGuitar"
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
	
	FAUSTFLOAT fButton0;
	FAUSTFLOAT fHslider0;
	float fVec0[2];
	float fRec13[2];
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	float fRec30[2];
	float fRec26[2];
	float fRec31[2];
	float fRec33[4];
	int IOTA;
	float fRec34[2048];
	float fConst3;
	float fVec1[2];
	FAUSTFLOAT fHslider3;
	int iRec37[2];
	float fConst4;
	float fRec36[3];
	float fConst5;
	float fVec2[2];
	float fRec38[2];
	float fConst6;
	float fConst7;
	float fVec3[3];
	float fRec32[512];
	float fRec22[2];
	float fRec18[2];
	float fRec14[2048];
	float fRec16[2];
	float fRec11[4];
	float fRec6[2];
	float fRec2[512];
	float fRec0[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("envelopes.lib/author", "GRAME");
		m->declare("envelopes.lib/copyright", "GRAME");
		m->declare("envelopes.lib/license", "LGPL with exception");
		m->declare("envelopes.lib/name", "Faust Envelope Library");
		m->declare("envelopes.lib/version", "0.0");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("interface", "SmartKeyboard{  'Number of Keyboards':'6',  'Max Keyboard Polyphony':'1',  'Keyboard 0 - Number of Keys':'13',  'Keyboard 1 - Number of Keys':'13',  'Keyboard 2 - Number of Keys':'13',  'Keyboard 3 - Number of Keys':'13',  'Keyboard 4 - Number of Keys':'13',  'Keyboard 5 - Number of Keys':'13',  'Keyboard 0 - Lowest Key':'72',  'Keyboard 1 - Lowest Key':'67',  'Keyboard 2 - Lowest Key':'62',  'Keyboard 3 - Lowest Key':'57',  'Keyboard 4 - Lowest Key':'52',  'Keyboard 5 - Lowest Key':'47',  'Rounding Mode':'2' }");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "elecGuitar");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
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
		fConst2 = (0.000294117635f * fConst0);
		fConst3 = (0.00117647054f * fConst0);
		fConst4 = (15.707963f / fConst0);
		fConst5 = (0.00400000019f * fConst0);
		fConst6 = (0.00200000009f * fConst0);
		fConst7 = (500.0f / fConst0);
		
	}
	
	virtual void instanceResetUserInterface() {
		fButton0 = FAUSTFLOAT(0.0f);
		fHslider0 = FAUSTFLOAT(0.0f);
		fHslider1 = FAUSTFLOAT(300.0f);
		fHslider2 = FAUSTFLOAT(1.0f);
		fHslider3 = FAUSTFLOAT(1.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fVec0[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec13[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec30[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec26[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec31[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 4); l5 = (l5 + 1)) {
			fRec33[l5] = 0.0f;
			
		}
		IOTA = 0;
		for (int l6 = 0; (l6 < 2048); l6 = (l6 + 1)) {
			fRec34[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fVec1[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			iRec37[l8] = 0;
			
		}
		for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) {
			fRec36[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fVec2[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec38[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 3); l12 = (l12 + 1)) {
			fVec3[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 512); l13 = (l13 + 1)) {
			fRec32[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec22[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec18[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 2048); l16 = (l16 + 1)) {
			fRec14[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec16[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 4); l18 = (l18 + 1)) {
			fRec11[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec6[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 512); l20 = (l20 + 1)) {
			fRec2[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec0[l21] = 0.0f;
			
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
		ui_interface->openVerticalBox("elecGuitar");
		ui_interface->declare(&fHslider2, "midi", "pitchwheel");
		ui_interface->addHorizontalSlider("bend", &fHslider2, 1.0f, 0.0f, 10.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("freq", &fHslider1, 300.0f, 50.0f, 2000.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("gain", &fHslider3, 1.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addButton("gate", &fButton0);
		ui_interface->declare(&fHslider0, "midi", "ctrl 64");
		ui_interface->addHorizontalSlider("sustain", &fHslider0, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = min(1.0f, (float(fButton0) + float(fHslider0)));
		int iSlow1 = (fSlow0 == 0.0f);
		float fSlow2 = float(fHslider1);
		float fSlow3 = float(fHslider2);
		float fSlow4 = float(fHslider3);
		for (int i = 0; (i < count); i = (i + 1)) {
			float fRec10 = (0.0f - (0.997305274f * ((0.899999976f * fRec11[2]) + (0.0500000007f * (fRec11[1] + fRec11[3])))));
			fVec0[0] = fSlow0;
			int iTemp0 = ((fSlow0 == fVec0[1]) | iSlow1);
			float fTemp1 = (1.0f - (0.999000013f * float(iTemp0)));
			fRec13[0] = ((fSlow0 * fTemp1) + (0.999000013f * (float(iTemp0) * fRec13[1])));
			fRec30[0] = ((fSlow3 * fTemp1) + (0.999000013f * (float(iTemp0) * fRec30[1])));
			float fTemp2 = max(60.0f, (fSlow2 * fRec30[0]));
			float fTemp3 = ((340.0f / fTemp2) + -0.109999999f);
			float fTemp4 = (fConst2 * fTemp3);
			float fTemp5 = (fTemp4 + -1.49999499f);
			int iTemp6 = int(fTemp5);
			int iTemp7 = int(min(fConst1, float(max(0, int(iTemp6)))));
			float fTemp8 = floorf(fTemp5);
			float fTemp9 = (fTemp4 + (-1.0f - fTemp8));
			float fTemp10 = (0.0f - fTemp9);
			float fTemp11 = (fTemp4 + (-2.0f - fTemp8));
			float fTemp12 = (0.0f - (0.5f * fTemp11));
			float fTemp13 = (fTemp4 + (-3.0f - fTemp8));
			float fTemp14 = (0.0f - (0.333333343f * fTemp13));
			float fTemp15 = (fTemp4 + (-4.0f - fTemp8));
			float fTemp16 = (0.0f - (0.25f * fTemp15));
			float fTemp17 = (fTemp4 - fTemp8);
			int iTemp18 = int(min(fConst1, float(max(0, int((iTemp6 + 2))))));
			float fTemp19 = (0.0f - fTemp13);
			float fTemp20 = (0.0f - (0.5f * fTemp15));
			int iTemp21 = int(min(fConst1, float(max(0, int((iTemp6 + 1))))));
			float fTemp22 = (0.0f - fTemp11);
			float fTemp23 = (0.0f - (0.5f * fTemp13));
			float fTemp24 = (0.0f - (0.333333343f * fTemp15));
			float fTemp25 = (fTemp9 * fTemp11);
			int iTemp26 = int(min(fConst1, float(max(0, int((iTemp6 + 3))))));
			float fTemp27 = (0.0f - fTemp15);
			float fTemp28 = (fTemp25 * fTemp13);
			int iTemp29 = int(min(fConst1, float(max(0, int((iTemp6 + 4))))));
			fRec26[0] = (((((fRec2[((IOTA - (iTemp7 + 1)) & 511)] * fTemp10) * fTemp12) * fTemp14) * fTemp16) + (fTemp17 * ((((0.5f * (((fTemp9 * fRec2[((IOTA - (iTemp18 + 1)) & 511)]) * fTemp19) * fTemp20)) + (((fRec2[((IOTA - (iTemp21 + 1)) & 511)] * fTemp22) * fTemp23) * fTemp24)) + (0.166666672f * ((fTemp25 * fRec2[((IOTA - (iTemp26 + 1)) & 511)]) * fTemp27))) + (0.0416666679f * (fTemp28 * fRec2[((IOTA - (iTemp29 + 1)) & 511)])))));
			fRec31[0] = ((0.0500000007f * fRec31[1]) + (0.949999988f * fRec26[1]));
			float fRec27 = fRec31[0];
			fRec33[0] = fRec0[1];
			fRec34[(IOTA & 2047)] = (0.0f - (0.997305274f * ((0.899999976f * fRec33[2]) + (0.0500000007f * (fRec33[1] + fRec33[3])))));
			int iRec35 = 0;
			float fTemp30 = (fConst3 * fTemp3);
			float fTemp31 = (fTemp30 + -1.49999499f);
			int iTemp32 = int(fTemp31);
			int iTemp33 = int(min(fConst1, float(max(0, int(iTemp32)))));
			float fTemp34 = floorf(fTemp31);
			float fTemp35 = (fTemp30 + (-1.0f - fTemp34));
			float fTemp36 = (0.0f - fTemp35);
			float fTemp37 = (fTemp30 + (-2.0f - fTemp34));
			float fTemp38 = (0.0f - (0.5f * fTemp37));
			float fTemp39 = (fTemp30 + (-3.0f - fTemp34));
			float fTemp40 = (0.0f - (0.333333343f * fTemp39));
			float fTemp41 = (fTemp30 + (-4.0f - fTemp34));
			float fTemp42 = (0.0f - (0.25f * fTemp41));
			float fTemp43 = (fTemp30 - fTemp34);
			int iTemp44 = int(min(fConst1, float(max(0, int((iTemp32 + 2))))));
			float fTemp45 = (0.0f - fTemp39);
			float fTemp46 = (0.0f - (0.5f * fTemp41));
			int iTemp47 = int(min(fConst1, float(max(0, int((iTemp32 + 1))))));
			float fTemp48 = (0.0f - fTemp37);
			float fTemp49 = (0.0f - (0.5f * fTemp39));
			float fTemp50 = (0.0f - (0.333333343f * fTemp41));
			float fTemp51 = (fTemp35 * fTemp37);
			int iTemp52 = int(min(fConst1, float(max(0, int((iTemp32 + 3))))));
			float fTemp53 = (0.0f - fTemp41);
			float fTemp54 = (fTemp51 * fTemp39);
			int iTemp55 = int(min(fConst1, float(max(0, int((iTemp32 + 4))))));
			fVec1[0] = (((((fRec34[((IOTA - (iTemp33 + 2)) & 2047)] * fTemp36) * fTemp38) * fTemp40) * fTemp42) + (fTemp43 * ((((0.5f * (((fTemp35 * fRec34[((IOTA - (iTemp44 + 2)) & 2047)]) * fTemp45) * fTemp46)) + (((fRec34[((IOTA - (iTemp47 + 2)) & 2047)] * fTemp48) * fTemp49) * fTemp50)) + (0.166666672f * ((fTemp51 * fRec34[((IOTA - (iTemp52 + 2)) & 2047)]) * fTemp53))) + (0.0416666679f * (fTemp54 * fRec34[((IOTA - (iTemp55 + 2)) & 2047)])))));
			iRec37[0] = ((1103515245 * iRec37[1]) + 12345);
			float fTemp56 = tanf((fConst4 * fTemp2));
			float fTemp57 = (1.0f / fTemp56);
			float fTemp58 = (((fTemp57 + 1.41421354f) / fTemp56) + 1.0f);
			fRec36[0] = ((4.65661287e-10f * float(iRec37[0])) - (((fRec36[2] * (((fTemp57 + -1.41421354f) / fTemp56) + 1.0f)) + (2.0f * (fRec36[1] * (1.0f - (1.0f / mydsp_faustpower2_f(fTemp56)))))) / fTemp58));
			float fTemp59 = mydsp_faustpower2_f((1.0f - (0.000500000024f * fTemp2)));
			fVec2[0] = fTemp59;
			float fTemp60 = (fConst5 * fTemp59);
			fRec38[0] = ((((fSlow0 - fVec0[1]) > 0.0f) > 0)?0.0f:min(fTemp60, ((fRec38[1] + (fConst5 * (fTemp59 - fVec2[1]))) + 1.0f)));
			float fTemp61 = (fConst6 * fTemp59);
			int iTemp62 = (fRec38[0] < fTemp61);
			float fTemp63 = (fSlow4 * (((fRec36[2] + (fRec36[0] + (2.0f * fRec36[1]))) * (iTemp62?((fRec38[0] < 0.0f)?0.0f:(iTemp62?(fConst7 * (fRec38[0] / fTemp59)):1.0f)):((fRec38[0] < fTemp60)?((fConst7 * ((0.0f - (fRec38[0] - fTemp61)) / fTemp59)) + 1.0f):0.0f))) / fTemp58));
			float fTemp64 = (fVec1[1] + fTemp63);
			fVec3[0] = fTemp64;
			fRec32[(IOTA & 511)] = ((0.0500000007f * fRec32[((IOTA - 1) & 511)]) + (0.949999988f * fVec3[2]));
			float fRec28 = (((((fTemp10 * fTemp12) * fTemp14) * fTemp16) * fRec32[((IOTA - iTemp7) & 511)]) + (fTemp17 * ((0.0416666679f * (fTemp28 * fRec32[((IOTA - iTemp29) & 511)])) + (((((fTemp22 * fTemp23) * fTemp24) * fRec32[((IOTA - iTemp21) & 511)]) + (0.5f * (((fTemp9 * fTemp19) * fTemp20) * fRec32[((IOTA - iTemp18) & 511)]))) + (0.166666672f * ((fTemp25 * fTemp27) * fRec32[((IOTA - iTemp26) & 511)]))))));
			float fRec29 = (fRec22[1] + (float(iRec35) + fVec3[1]));
			fRec22[0] = fRec27;
			float fRec23 = fRec22[1];
			float fRec24 = fRec28;
			float fRec25 = fRec29;
			fRec18[0] = fRec23;
			float fRec19 = (fTemp63 + fRec18[1]);
			float fRec20 = fRec24;
			float fRec21 = fRec25;
			fRec14[(IOTA & 2047)] = fRec19;
			float fRec15 = (((((fTemp36 * fTemp38) * fTemp40) * fTemp42) * fRec14[((IOTA - (iTemp33 + 1)) & 2047)]) + (fTemp43 * (((0.166666672f * ((fTemp51 * fTemp53) * fRec14[((IOTA - (iTemp52 + 1)) & 2047)])) + ((((fTemp48 * fTemp49) * fTemp50) * fRec14[((IOTA - (iTemp47 + 1)) & 2047)]) + (0.5f * (((fTemp35 * fTemp45) * fTemp46) * fRec14[((IOTA - (iTemp44 + 1)) & 2047)])))) + (0.0416666679f * (fTemp54 * fRec14[((IOTA - (iTemp55 + 1)) & 2047)])))));
			fRec16[0] = fRec20;
			float fRec17 = fRec21;
			fRec11[0] = (fRec13[0] * fRec16[1]);
			float fRec12 = fRec17;
			fRec6[0] = fRec10;
			float fRec7 = (fRec13[0] * fRec6[1]);
			float fRec8 = fRec11[0];
			float fRec9 = fRec12;
			fRec2[(IOTA & 511)] = fRec7;
			float fRec3 = fRec15;
			float fRec4 = fRec8;
			float fRec5 = fRec9;
			fRec0[0] = fRec3;
			float fRec1 = fRec5;
			output0[i] = FAUSTFLOAT(fRec1);
			output1[i] = FAUSTFLOAT(fRec1);
			fVec0[1] = fVec0[0];
			fRec13[1] = fRec13[0];
			fRec30[1] = fRec30[0];
			fRec26[1] = fRec26[0];
			fRec31[1] = fRec31[0];
			for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				fRec33[j0] = fRec33[(j0 - 1)];
				
			}
			IOTA = (IOTA + 1);
			fVec1[1] = fVec1[0];
			iRec37[1] = iRec37[0];
			fRec36[2] = fRec36[1];
			fRec36[1] = fRec36[0];
			fVec2[1] = fVec2[0];
			fRec38[1] = fRec38[0];
			fVec3[2] = fVec3[1];
			fVec3[1] = fVec3[0];
			fRec22[1] = fRec22[0];
			fRec18[1] = fRec18[0];
			fRec16[1] = fRec16[0];
			for (int j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				fRec11[j1] = fRec11[(j1 - 1)];
				
			}
			fRec6[1] = fRec6[0];
			fRec0[1] = fRec0[0];
			
		}
		
	}

	
};

#endif
