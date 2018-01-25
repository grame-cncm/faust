/* ------------------------------------------------------------
name: "brass"
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
	
	int iRec6[2];
	float fRec13[2];
	float fRec14[2];
	FAUSTFLOAT fHslider0;
	float fRec19[2];
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	float fConst3;
	float fConst4;
	int iRec21[2];
	float fConst5;
	float fConst6;
	float fConst7;
	float fRec20[3];
	float fConst8;
	FAUSTFLOAT fHslider1;
	float fRec22[2];
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT fHslider4;
	float fRec23[2];
	float fRec18[3];
	float fVec0[2];
	float fRec17[2];
	int IOTA;
	float fRec15[2048];
	float fConst9;
	float fConst10;
	float fVec1[2];
	float fRec11[2];
	float fRec2[2048];
	float fRec0[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("interface", "SmartKeyboard{  'Number of Keyboards':'2',  'Max Keyboard Polyphony':'0',  'Keyboard 0 - Number of Keys':'1',   'Keyboard 1 - Number of Keys':'3',  'Keyboard 0 - Send Freq':'0',   'Keyboard 1 - Send Freq':'0',  'Keyboard 0 - Piano Keyboard':'0',   'Keyboard 1 - Piano Keyboard':'0',  'Keyboard 0 - Send Key X':'1',  'Keyboard 1 - Send Key Status':'1',  'Keyboard 0 - Static Mode':'1',  'Keyboard 0 - Key 0 - Label':'Lips Tension',  'Keyboard 1 - Key 0 - Label':'P1',  'Keyboard 1 - Key 1 - Label':'P2',  'Keyboard 1 - Key 2 - Label':'P3' }");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "brass");
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
		fConst1 = tanf((6283.18555f / fConst0));
		fConst2 = (1.0f / fConst1);
		fConst3 = (((fConst2 + 1.41421354f) / fConst1) + 1.0f);
		fConst4 = (0.00499999989f / fConst3);
		fConst5 = (1.0f / fConst3);
		fConst6 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst1))));
		fConst7 = (((fConst2 + -1.41421354f) / fConst1) + 1.0f);
		fConst8 = (2136.28296f / fConst0);
		fConst9 = (0.00882352982f * fConst0);
		fConst10 = (0.00147058826f * fConst0);
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.0f);
		fHslider1 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(0.0f);
		fHslider3 = FAUSTFLOAT(0.0f);
		fHslider4 = FAUSTFLOAT(0.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iRec6[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec13[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec14[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec19[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			iRec21[l4] = 0;
			
		}
		for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) {
			fRec20[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec22[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec23[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
			fRec18[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fVec0[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec17[l10] = 0.0f;
			
		}
		IOTA = 0;
		for (int l11 = 0; (l11 < 2048); l11 = (l11 + 1)) {
			fRec15[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fVec1[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec11[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2048); l14 = (l14 + 1)) {
			fRec2[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec0[l15] = 0.0f;
			
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
		ui_interface->openVerticalBox("brass");
		ui_interface->addHorizontalSlider("kb0k0x", &fHslider1, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->addHorizontalSlider("kb1k0status", &fHslider2, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->addHorizontalSlider("kb1k1status", &fHslider3, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->addHorizontalSlider("kb1k2status", &fHslider4, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->declare(&fHslider0, "acc", "1 1 -10 0 10");
		ui_interface->addHorizontalSlider("pressure", &fHslider0, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = (0.00100000005f * float(fHslider0));
		float fSlow1 = (0.00100000005f * float(fHslider1));
		int iSlow2 = int(min(1.0f, float(fHslider2)));
		int iSlow3 = int(min(1.0f, float(fHslider3)));
		int iSlow4 = (iSlow3 == 1);
		int iSlow5 = ((iSlow2 == 0) & iSlow4);
		int iSlow6 = int(min(1.0f, float(fHslider4)));
		int iSlow7 = (iSlow6 == 0);
		int iSlow8 = (iSlow2 == 1);
		int iSlow9 = (iSlow8 & (iSlow3 == 0));
		int iSlow10 = (iSlow8 & iSlow4);
		int iSlow11 = (iSlow6 == 1);
		float fSlow12 = (0.000772727246f / powf(2.0f, (0.0833333358f * (-21.0f - float(((((((iSlow5 & iSlow7) + (2 * (iSlow9 & iSlow7))) + (3 * (iSlow10 & iSlow7))) + (4 * (iSlow5 & iSlow11))) + (5 * (iSlow9 & iSlow11))) + (6 * (iSlow10 & iSlow11))))))));
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec6[0] = 0;
			fRec13[0] = (0.5f * (fRec13[1] + fRec11[1]));
			float fRec10 = (fRec13[0] + float(iRec6[1]));
			fRec14[0] = fRec0[1];
			fRec19[0] = (fSlow0 + (0.999000013f * fRec19[1]));
			iRec21[0] = ((1103515245 * iRec21[1]) + 12345);
			fRec20[0] = ((4.65661287e-10f * float(iRec21[0])) - (fConst5 * ((fConst6 * fRec20[1]) + (fConst7 * fRec20[2]))));
			float fTemp0 = (fRec19[0] * ((fConst4 * (fRec20[2] + (fRec20[0] + (2.0f * fRec20[1])))) + 1.0f));
			fRec22[0] = (fSlow1 + (0.999000013f * fRec22[1]));
			fRec23[0] = (fSlow12 + (0.999000013f * fRec23[1]));
			fRec18[0] = ((0.0299999993f * ((0.300000012f * fTemp0) - (0.850000024f * fRec14[1]))) - ((fRec18[1] * (0.0f - (1.99399996f * cosf((fConst8 * (powf(4.0f, ((2.0f * fRec22[0]) + -1.0f)) / fRec23[0])))))) + (0.994009018f * fRec18[2])));
			float fTemp1 = max(-1.0f, min(1.0f, mydsp_faustpower2_f(fRec18[0])));
			float fTemp2 = (0.850000024f * (fRec14[1] * (1.0f - fTemp1)));
			float fTemp3 = (0.300000012f * (fTemp0 * fTemp1));
			fVec0[0] = (fTemp3 + fTemp2);
			fRec17[0] = ((fTemp2 + ((0.995000005f * fRec17[1]) + fTemp3)) - fVec0[1]);
			fRec15[(IOTA & 2047)] = fRec17[0];
			int iRec16 = 0;
			float fTemp4 = (fConst10 * fRec23[0]);
			float fTemp5 = (fTemp4 + -1.49999499f);
			int iTemp6 = int(fTemp5);
			int iTemp7 = (int(min(fConst9, float(max(0, int(iTemp6))))) + 1);
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
			int iTemp18 = (int(min(fConst9, float(max(0, int((iTemp6 + 2)))))) + 1);
			float fTemp19 = (0.0f - fTemp13);
			float fTemp20 = (0.0f - (0.5f * fTemp15));
			int iTemp21 = (int(min(fConst9, float(max(0, int((iTemp6 + 1)))))) + 1);
			float fTemp22 = (0.0f - fTemp11);
			float fTemp23 = (0.0f - (0.5f * fTemp13));
			float fTemp24 = (0.0f - (0.333333343f * fTemp15));
			float fTemp25 = (fTemp9 * fTemp11);
			int iTemp26 = (int(min(fConst9, float(max(0, int((iTemp6 + 3)))))) + 1);
			float fTemp27 = (0.0f - fTemp15);
			float fTemp28 = (fTemp25 * fTemp13);
			int iTemp29 = (int(min(fConst9, float(max(0, int((iTemp6 + 4)))))) + 1);
			fVec1[0] = (((((fRec15[((IOTA - iTemp7) & 2047)] * fTemp10) * fTemp12) * fTemp14) * fTemp16) + (fTemp17 * ((((0.5f * (((fTemp9 * fRec15[((IOTA - iTemp18) & 2047)]) * fTemp19) * fTemp20)) + (((fRec15[((IOTA - iTemp21) & 2047)] * fTemp22) * fTemp23) * fTemp24)) + (0.166666672f * ((fTemp25 * fRec15[((IOTA - iTemp26) & 2047)]) * fTemp27))) + (0.0416666679f * (fTemp28 * fRec15[((IOTA - iTemp29) & 2047)])))));
			fRec11[0] = fVec1[1];
			int iRec12 = iRec16;
			float fRec7 = fRec10;
			float fRec8 = fRec11[0];
			float fRec9 = (fRec11[0] + float(iRec12));
			fRec2[(IOTA & 2047)] = fRec7;
			float fRec3 = (((((fTemp10 * fTemp12) * fTemp14) * fTemp16) * fRec2[((IOTA - iTemp7) & 2047)]) + (fTemp17 * (((0.166666672f * ((fTemp25 * fTemp27) * fRec2[((IOTA - iTemp26) & 2047)])) + ((((fTemp22 * fTemp23) * fTemp24) * fRec2[((IOTA - iTemp21) & 2047)]) + (0.5f * (((fTemp9 * fTemp19) * fTemp20) * fRec2[((IOTA - iTemp18) & 2047)])))) + (0.0416666679f * (fTemp28 * fRec2[((IOTA - iTemp29) & 2047)])))));
			float fRec4 = fRec8;
			float fRec5 = fRec9;
			fRec0[0] = fRec3;
			float fRec1 = fRec5;
			output0[i] = FAUSTFLOAT(fRec1);
			output1[i] = FAUSTFLOAT(fRec1);
			iRec6[1] = iRec6[0];
			fRec13[1] = fRec13[0];
			fRec14[1] = fRec14[0];
			fRec19[1] = fRec19[0];
			iRec21[1] = iRec21[0];
			fRec20[2] = fRec20[1];
			fRec20[1] = fRec20[0];
			fRec22[1] = fRec22[0];
			fRec23[1] = fRec23[0];
			fRec18[2] = fRec18[1];
			fRec18[1] = fRec18[0];
			fVec0[1] = fVec0[0];
			fRec17[1] = fRec17[0];
			IOTA = (IOTA + 1);
			fVec1[1] = fVec1[0];
			fRec11[1] = fRec11[0];
			fRec0[1] = fRec0[0];
			
		}
		
	}

	
};

#endif
