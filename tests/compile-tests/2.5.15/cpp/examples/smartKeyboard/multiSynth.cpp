/* ------------------------------------------------------------
name: "multiSynth"
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
	
	int iVec0[2];
	FAUSTFLOAT fButton0;
	FAUSTFLOAT fHslider0;
	float fVec1[2];
	FAUSTFLOAT fHslider1;
	float fRec0[2];
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider2;
	float fRec3[2];
	FAUSTFLOAT fHslider3;
	float fConst2;
	float fConst3;
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT fHslider5;
	float fRec5[2];
	float fVec2[2];
	float fRec4[2];
	float fVec3[2];
	int IOTA;
	float fVec4[4096];
	float fConst4;
	float fConst5;
	float fRec6[2];
	float fConst6;
	float fRec7[2];
	float fRec8[2];
	float fConst7;
	float fRec9[2];
	float fVec5[2];
	float fRec2[2];
	float fRec1[3];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("interface", "SmartKeyboard{  'Number of Keyboards':'4',  'Rounding Mode':'2',  'Inter-Keyboard Slide':'0',  'Keyboard 0 - Number of Keys':'13',  'Keyboard 1 - Number of Keys':'13',  'Keyboard 2 - Number of Keys':'13',  'Keyboard 3 - Number of Keys':'13',  'Keyboard 0 - Lowest Key':'60',  'Keyboard 1 - Lowest Key':'60',  'Keyboard 2 - Lowest Key':'60',  'Keyboard 3 - Lowest Key':'60',  'Keyboard 0 - Send Y':'1',  'Keyboard 1 - Send Y':'1',  'Keyboard 2 - Send Y':'1',  'Keyboard 3 - Send Y':'1' }");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "multiSynth");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
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
		fConst1 = (3.14159274f / fConst0);
		fConst2 = (0.25f * fConst0);
		fConst3 = (1.0f / fConst0);
		fConst4 = (0.5f * fConst0);
		fConst5 = (4.0f / fConst0);
		fConst6 = (6.28318548f / fConst0);
		fConst7 = (1.0f / fConst0);
		
	}
	
	virtual void instanceResetUserInterface() {
		fButton0 = FAUSTFLOAT(0.0f);
		fHslider0 = FAUSTFLOAT(0.0f);
		fHslider1 = FAUSTFLOAT(1.0f);
		fHslider2 = FAUSTFLOAT(1.0f);
		fHslider3 = FAUSTFLOAT(0.0f);
		fHslider4 = FAUSTFLOAT(300.0f);
		fHslider5 = FAUSTFLOAT(1.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fVec1[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec0[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec3[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec5[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fVec2[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec4[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fVec3[l7] = 0.0f;
			
		}
		IOTA = 0;
		for (int l8 = 0; (l8 < 4096); l8 = (l8 + 1)) {
			fVec4[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec6[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec7[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec8[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec9[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fVec5[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec2[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 3); l15 = (l15 + 1)) {
			fRec1[l15] = 0.0f;
			
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
		ui_interface->openVerticalBox("multiSynth");
		ui_interface->declare(&fHslider5, "midi", "pitchwheel");
		ui_interface->addHorizontalSlider("bend", &fHslider5, 1.0f, 0.0f, 10.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("freq", &fHslider4, 300.0f, 50.0f, 2000.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("gain", &fHslider1, 1.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addButton("gate", &fButton0);
		ui_interface->addHorizontalSlider("keyboard", &fHslider3, 0.0f, 0.0f, 3.0f, 1.0f);
		ui_interface->declare(&fHslider0, "midi", "ctrl 64");
		ui_interface->addHorizontalSlider("sustain", &fHslider0, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->declare(&fHslider2, "midi", "ctrl 1");
		ui_interface->addHorizontalSlider("y", &fHslider2, 1.0f, 0.0f, 1.0f, 0.00100000005f);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = min(1.0f, (float(fButton0) + float(fHslider0)));
		float fSlow1 = (0.00100000005f * (fSlow0 * float(fHslider1)));
		float fSlow2 = (0.00100000005f * float(fHslider2));
		int iSlow3 = int(float(fHslider3));
		int iSlow4 = (iSlow3 == 2);
		float fSlow5 = float(fHslider4);
		float fSlow6 = float(fHslider5);
		int iSlow7 = (fSlow0 == 0.0f);
		int iSlow8 = (iSlow3 == 1);
		float fSlow9 = (fConst5 * fSlow5);
		int iSlow10 = (iSlow3 == 3);
		float fSlow11 = (fConst6 * fSlow5);
		int iSlow12 = (iSlow3 == 0);
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			fVec1[0] = fSlow0;
			fRec0[0] = (fSlow1 + (0.999000013f * fRec0[1]));
			fRec3[0] = (fSlow2 + (0.999000013f * fRec3[1]));
			float fTemp0 = tanf((fConst1 * ((4000.0f * fRec3[0]) + 50.0f)));
			float fTemp1 = (1.0f / fTemp0);
			float fTemp2 = (fTemp1 + 1.0f);
			int iTemp3 = ((fSlow0 == fVec1[1]) | iSlow7);
			fRec5[0] = ((fSlow6 * (1.0f - (0.999000013f * float(iTemp3)))) + (0.999000013f * (float(iTemp3) * fRec5[1])));
			float fTemp4 = (fSlow5 * fRec5[0]);
			float fTemp5 = max(fTemp4, 23.4489498f);
			float fTemp6 = max(20.0f, fabsf(fTemp5));
			fVec2[0] = fTemp6;
			float fTemp7 = (fRec4[1] + (fConst3 * fVec2[1]));
			fRec4[0] = (fTemp7 - floorf(fTemp7));
			float fTemp8 = mydsp_faustpower2_f(((2.0f * fRec4[0]) + -1.0f));
			fVec3[0] = fTemp8;
			float fTemp9 = ((float(iVec0[1]) * (fTemp8 - fVec3[1])) / fTemp6);
			fVec4[(IOTA & 4095)] = fTemp9;
			float fTemp10 = max(0.0f, min(2047.0f, (fConst4 / fTemp5)));
			int iTemp11 = int(fTemp10);
			float fTemp12 = floorf(fTemp10);
			float fTemp13 = (fConst2 * ((fTemp9 - (fVec4[((IOTA - iTemp11) & 4095)] * (fTemp12 + (1.0f - fTemp10)))) - ((fTemp10 - fTemp12) * fVec4[((IOTA - (iTemp11 + 1)) & 4095)])));
			fRec6[0] = ((0.999000013f * fRec6[1]) + fTemp13);
			float fTemp14 = (fSlow11 * fRec5[0]);
			float fTemp15 = sinf(fTemp14);
			float fTemp16 = cosf(fTemp14);
			fRec7[0] = ((fRec8[1] * fTemp15) + (fRec7[1] * fTemp16));
			fRec8[0] = (((fRec8[1] * fTemp16) + (fRec7[1] * (0.0f - fTemp15))) + float((1 - iVec0[1])));
			float fTemp17 = max(1.00000001e-07f, fabsf(fTemp4));
			float fTemp18 = (fRec9[1] + (fConst7 * fTemp17));
			float fTemp19 = (fTemp18 + -1.0f);
			int iTemp20 = (fTemp19 < 0.0f);
			fRec9[0] = (iTemp20?fTemp18:fTemp19);
			float fRec10 = (iTemp20?fTemp18:(fTemp18 + ((1.0f - (fConst0 / fTemp17)) * fTemp19)));
			float fTemp21 = ((iSlow4?fTemp13:0.0f) + ((iSlow8?(fSlow9 * (fRec5[0] * fRec6[0])):0.0f) + ((iSlow10?fRec7[0]:0.0f) + (iSlow12?((2.0f * fRec10) + -1.0f):0.0f))));
			fVec5[0] = fTemp21;
			fRec2[0] = ((fRec2[1] * (0.0f - ((1.0f - fTemp1) / fTemp2))) + ((fTemp21 + fVec5[1]) / fTemp2));
			float fTemp22 = (((fTemp1 + 1.0f) / fTemp0) + 1.0f);
			fRec1[0] = (fRec2[0] - (((fRec1[2] * (((fTemp1 + -1.0f) / fTemp0) + 1.0f)) + (2.0f * (fRec1[1] * (1.0f - (1.0f / mydsp_faustpower2_f(fTemp0)))))) / fTemp22));
			float fTemp23 = ((fRec0[0] * (fRec1[2] + (fRec1[0] + (2.0f * fRec1[1])))) / fTemp22);
			output0[i] = FAUSTFLOAT(fTemp23);
			output1[i] = FAUSTFLOAT(fTemp23);
			iVec0[1] = iVec0[0];
			fVec1[1] = fVec1[0];
			fRec0[1] = fRec0[0];
			fRec3[1] = fRec3[0];
			fRec5[1] = fRec5[0];
			fVec2[1] = fVec2[0];
			fRec4[1] = fRec4[0];
			fVec3[1] = fVec3[0];
			IOTA = (IOTA + 1);
			fRec6[1] = fRec6[0];
			fRec7[1] = fRec7[0];
			fRec8[1] = fRec8[0];
			fRec9[1] = fRec9[0];
			fVec5[1] = fVec5[0];
			fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			
		}
		
	}

	
};

#endif
