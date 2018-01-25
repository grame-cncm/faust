/* ------------------------------------------------------------
copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
license: "MIT"
name: "Flute"
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
	int iRec15[2];
	int iVec0[2];
	float fRec22[2];
	FAUSTFLOAT fHslider1;
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider2;
	float fRec23[2];
	float fRec24[2];
	FAUSTFLOAT fHslider3;
	float fRec25[2];
	FAUSTFLOAT fHslider4;
	float fConst2;
	FAUSTFLOAT fHslider5;
	int iRec27[2];
	float fRec26[3];
	float fRec28[2];
	int IOTA;
	float fRec29[2048];
	float fConst3;
	float fConst4;
	FAUSTFLOAT fHslider6;
	float fRec31[2];
	FAUSTFLOAT fHslider7;
	float fRec32[2];
	float fVec1[2];
	float fVec2[2048];
	float fVec3[2];
	float fRec20[2];
	float fRec11[2048];
	float fRec7[2];
	float fRec3[2048];
	float fRec1[2];
	float fRec2[2];
	float fRec0[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("description", "Simple flute physical model with physical parameters.");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("license", "MIT");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "Flute");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
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
		fConst1 = (6.28318548f / fConst0);
		fConst2 = (3.14159274f / fConst0);
		fConst3 = (0.00882352982f * fConst0);
		fConst4 = (0.00147058826f * fConst0);
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.5f);
		fHslider1 = FAUSTFLOAT(0.25f);
		fHslider2 = FAUSTFLOAT(5.0f);
		fHslider3 = FAUSTFLOAT(0.0f);
		fHslider4 = FAUSTFLOAT(0.10000000000000001f);
		fHslider5 = FAUSTFLOAT(2000.0f);
		fHslider6 = FAUSTFLOAT(0.80000000000000004f);
		fHslider7 = FAUSTFLOAT(0.5f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iRec15[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			iVec0[l1] = 0;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec22[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec23[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec24[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec25[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			iRec27[l6] = 0;
			
		}
		for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			fRec26[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec28[l8] = 0.0f;
			
		}
		IOTA = 0;
		for (int l9 = 0; (l9 < 2048); l9 = (l9 + 1)) {
			fRec29[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec31[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec32[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fVec1[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 2048); l13 = (l13 + 1)) {
			fVec2[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fVec3[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec20[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 2048); l16 = (l16 + 1)) {
			fRec11[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec7[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 2048); l18 = (l18 + 1)) {
			fRec3[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec1[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
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
		ui_interface->openHorizontalBox("flute");
		ui_interface->openVerticalBox("blower");
		ui_interface->declare(&fHslider3, "0", "");
		ui_interface->addHorizontalSlider("pressure", &fHslider3, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fHslider4, "1", "");
		ui_interface->addHorizontalSlider("breathGain", &fHslider4, 0.100000001f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fHslider5, "2", "");
		ui_interface->addHorizontalSlider("breathCutoff", &fHslider5, 2000.0f, 20.0f, 20000.0f, 0.100000001f);
		ui_interface->declare(&fHslider2, "3", "");
		ui_interface->addHorizontalSlider("vibratoFreq", &fHslider2, 5.0f, 0.100000001f, 10.0f, 0.100000001f);
		ui_interface->declare(&fHslider1, "4", "");
		ui_interface->addHorizontalSlider("vibratoGain", &fHslider1, 0.25f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("fluteModel");
		ui_interface->declare(&fHslider6, "0", "");
		ui_interface->addHorizontalSlider("tubeLength", &fHslider6, 0.800000012f, 0.00999999978f, 3.0f, 0.00999999978f);
		ui_interface->declare(&fHslider7, "1", "");
		ui_interface->addHorizontalSlider("mouthPosition", &fHslider7, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fHslider0, "2", "");
		ui_interface->addHorizontalSlider("outGain", &fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = float(fHslider0);
		float fSlow1 = (0.0299999993f * float(fHslider1));
		float fSlow2 = (fConst1 * float(fHslider2));
		float fSlow3 = sinf(fSlow2);
		float fSlow4 = cosf(fSlow2);
		float fSlow5 = (0.0f - fSlow3);
		float fSlow6 = (0.00100000005f * float(fHslider3));
		float fSlow7 = tanf((fConst2 * float(fHslider5)));
		float fSlow8 = (1.0f / fSlow7);
		float fSlow9 = (((fSlow8 + 1.41421354f) / fSlow7) + 1.0f);
		float fSlow10 = (0.0500000007f * (float(fHslider4) / fSlow9));
		float fSlow11 = (1.0f / fSlow9);
		float fSlow12 = (((fSlow8 + -1.41421354f) / fSlow7) + 1.0f);
		float fSlow13 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fSlow7))));
		float fSlow14 = (0.00100000005f * float(fHslider6));
		float fSlow15 = (0.00100000005f * float(fHslider7));
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec15[0] = 0;
			iVec0[0] = 1;
			fRec22[0] = ((0.699999988f * fRec22[1]) + (0.284999996f * fRec20[1]));
			float fRec19 = (fRec22[0] + float(iRec15[1]));
			fRec23[0] = ((fSlow3 * fRec24[1]) + (fSlow4 * fRec23[1]));
			fRec24[0] = (((fSlow4 * fRec24[1]) + (fSlow5 * fRec23[1])) + float((1 - iVec0[1])));
			fRec25[0] = (fSlow6 + (0.999000013f * fRec25[1]));
			iRec27[0] = ((1103515245 * iRec27[1]) + 12345);
			fRec26[0] = ((4.65661287e-10f * float(iRec27[0])) - (fSlow11 * ((fSlow12 * fRec26[2]) + (fSlow13 * fRec26[1]))));
			fRec28[0] = fRec1[1];
			fRec29[(IOTA & 2047)] = (0.949999988f * fRec28[1]);
			int iRec30 = 0;
			fRec31[0] = (fSlow14 + (0.999000013f * fRec31[1]));
			float fTemp0 = (fRec31[0] + 0.270000011f);
			fRec32[0] = (fSlow15 + (0.999000013f * fRec32[1]));
			float fTemp1 = (0.400000006f * (fRec32[0] + -0.5f));
			float fTemp2 = (fConst4 * (fTemp0 * (fTemp1 + 0.270000011f)));
			float fTemp3 = (fTemp2 + -1.49999499f);
			int iTemp4 = int(fTemp3);
			int iTemp5 = (int(min(fConst3, float(max(0, iTemp4)))) + 1);
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
			int iTemp16 = (int(min(fConst3, float(max(0, (iTemp4 + 2))))) + 1);
			float fTemp17 = (0.0f - fTemp11);
			float fTemp18 = (0.0f - (0.5f * fTemp13));
			int iTemp19 = (int(min(fConst3, float(max(0, (iTemp4 + 1))))) + 1);
			float fTemp20 = (0.0f - fTemp9);
			float fTemp21 = (0.0f - (0.5f * fTemp11));
			float fTemp22 = (0.0f - (0.333333343f * fTemp13));
			float fTemp23 = (fTemp7 * fTemp9);
			int iTemp24 = (int(min(fConst3, float(max(0, (iTemp4 + 3))))) + 1);
			float fTemp25 = (0.0f - fTemp13);
			float fTemp26 = (fTemp23 * fTemp11);
			int iTemp27 = (int(min(fConst3, float(max(0, (iTemp4 + 4))))) + 1);
			fVec1[0] = (((((fRec29[((IOTA - iTemp5) & 2047)] * fTemp8) * fTemp10) * fTemp12) * fTemp14) + (fTemp15 * ((((0.5f * (((fTemp7 * fRec29[((IOTA - iTemp16) & 2047)]) * fTemp17) * fTemp18)) + (((fRec29[((IOTA - iTemp19) & 2047)] * fTemp20) * fTemp21) * fTemp22)) + (0.166666672f * ((fTemp23 * fRec29[((IOTA - iTemp24) & 2047)]) * fTemp25))) + (0.0416666679f * (fTemp26 * fRec29[((IOTA - iTemp27) & 2047)])))));
			float fTemp28 = (((fSlow1 * fRec23[0]) + (fRec25[0] * ((fSlow10 * (fRec26[2] + (fRec26[0] + (2.0f * fRec26[1])))) + 1.0f))) - (0.5f * fVec1[1]));
			float fTemp29 = ((0.5f * fRec7[1]) + max(-1.0f, min(1.0f, (fTemp28 * (mydsp_faustpower2_f(fTemp28) + -1.0f)))));
			fVec2[(IOTA & 2047)] = fTemp29;
			float fTemp30 = (fConst4 * (fTemp0 * (0.730000019f - fTemp1)));
			float fTemp31 = (fTemp30 + -1.49999499f);
			int iTemp32 = int(fTemp31);
			int iTemp33 = (int(min(fConst3, float(max(0, iTemp32)))) + 1);
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
			int iTemp44 = (int(min(fConst3, float(max(0, (iTemp32 + 2))))) + 1);
			float fTemp45 = (0.0f - fTemp39);
			float fTemp46 = (0.0f - (0.5f * fTemp41));
			int iTemp47 = (int(min(fConst3, float(max(0, (iTemp32 + 1))))) + 1);
			float fTemp48 = (0.0f - fTemp37);
			float fTemp49 = (0.0f - (0.5f * fTemp39));
			float fTemp50 = (0.0f - (0.333333343f * fTemp41));
			float fTemp51 = (fTemp35 * fTemp37);
			int iTemp52 = (int(min(fConst3, float(max(0, (iTemp32 + 3))))) + 1);
			float fTemp53 = (0.0f - fTemp41);
			float fTemp54 = (fTemp51 * fTemp39);
			int iTemp55 = (int(min(fConst3, float(max(0, (iTemp32 + 4))))) + 1);
			fVec3[0] = (((((fVec2[((IOTA - iTemp33) & 2047)] * fTemp36) * fTemp38) * fTemp40) * fTemp42) + (fTemp43 * ((((0.5f * (((fTemp35 * fVec2[((IOTA - iTemp44) & 2047)]) * fTemp45) * fTemp46)) + (((fVec2[((IOTA - iTemp47) & 2047)] * fTemp48) * fTemp49) * fTemp50)) + (0.166666672f * ((fTemp51 * fVec2[((IOTA - iTemp52) & 2047)]) * fTemp53))) + (0.0416666679f * (fTemp54 * fVec2[((IOTA - iTemp55) & 2047)])))));
			fRec20[0] = fVec3[1];
			int iRec21 = iRec30;
			float fRec16 = fRec19;
			float fRec17 = fRec20[0];
			float fRec18 = (fRec20[0] + float(iRec21));
			fRec11[(IOTA & 2047)] = fRec16;
			float fRec12 = (((((fTemp36 * fTemp38) * fTemp40) * fTemp42) * fRec11[((IOTA - iTemp33) & 2047)]) + (fTemp43 * (((0.166666672f * ((fTemp51 * fTemp53) * fRec11[((IOTA - iTemp52) & 2047)])) + ((((fTemp48 * fTemp49) * fTemp50) * fRec11[((IOTA - iTemp47) & 2047)]) + (0.5f * (((fTemp35 * fTemp45) * fTemp46) * fRec11[((IOTA - iTemp44) & 2047)])))) + (0.0416666679f * (fTemp54 * fRec11[((IOTA - iTemp55) & 2047)])))));
			float fRec13 = fRec17;
			float fRec14 = fRec18;
			fRec7[0] = fRec12;
			float fRec8 = fRec7[1];
			float fRec9 = fRec13;
			float fRec10 = fRec14;
			fRec3[(IOTA & 2047)] = fRec8;
			float fRec4 = (((((fTemp8 * fTemp10) * fTemp12) * fTemp14) * fRec3[((IOTA - iTemp5) & 2047)]) + (fTemp15 * (((0.166666672f * ((fTemp23 * fTemp25) * fRec3[((IOTA - iTemp24) & 2047)])) + ((((fTemp20 * fTemp21) * fTemp22) * fRec3[((IOTA - iTemp19) & 2047)]) + (0.5f * (((fTemp7 * fTemp17) * fTemp18) * fRec3[((IOTA - iTemp16) & 2047)])))) + (0.0416666679f * (fTemp26 * fRec3[((IOTA - iTemp27) & 2047)])))));
			float fRec5 = fRec9;
			float fRec6 = fRec10;
			fRec1[0] = fRec4;
			fRec2[0] = fRec6;
			fRec0[0] = ((fRec2[0] + (0.995000005f * fRec0[1])) - fRec2[1]);
			float fTemp56 = (fSlow0 * fRec0[0]);
			output0[i] = FAUSTFLOAT(fTemp56);
			output1[i] = FAUSTFLOAT(fTemp56);
			iRec15[1] = iRec15[0];
			iVec0[1] = iVec0[0];
			fRec22[1] = fRec22[0];
			fRec23[1] = fRec23[0];
			fRec24[1] = fRec24[0];
			fRec25[1] = fRec25[0];
			iRec27[1] = iRec27[0];
			fRec26[2] = fRec26[1];
			fRec26[1] = fRec26[0];
			fRec28[1] = fRec28[0];
			IOTA = (IOTA + 1);
			fRec31[1] = fRec31[0];
			fRec32[1] = fRec32[0];
			fVec1[1] = fVec1[0];
			fVec3[1] = fVec3[0];
			fRec20[1] = fRec20[0];
			fRec7[1] = fRec7[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec0[1] = fRec0[0];
			
		}
		
	}

	
};

#endif
