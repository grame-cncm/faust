/* ------------------------------------------------------------
name: "dubDub"
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
	float fRec0[2];
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fButton0;
	float fVec0[2];
	float fRec2[2];
	float fConst3;
	FAUSTFLOAT fHslider1;
	float fRec5[2];
	float fRec3[2];
	float fConst4;
	FAUSTFLOAT fHslider2;
	float fConst5;
	FAUSTFLOAT fHslider3;
	float fVec1[2];
	float fRec6[2];
	float fRec1[3];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("envelopes.lib/author", "GRAME");
		m->declare("envelopes.lib/copyright", "GRAME");
		m->declare("envelopes.lib/license", "LGPL with exception");
		m->declare("envelopes.lib/name", "Faust Envelope Library");
		m->declare("envelopes.lib/version", "0.0");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("interface", "SmartKeyboard{  'Number of Keyboards':'1',  'Keyboard 0 - Number of Keys':'1',  'Keyboard 0 - Piano Keyboard':'0',  'Keyboard 0 - Static Mode':'1',  'Keyboard 0 - Send X':'1',  'Keyboard 0 - Send Y':'1' }");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "dubDub");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("synths.lib/name", "Faust Synthesizer Library");
		m->declare("synths.lib/version", "0.0");
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
		fConst1 = expf((0.0f - (100.0f / fConst0)));
		fConst2 = (1.0f - fConst1);
		fConst3 = (1.0f / fConst0);
		fConst4 = (3.14159274f / fConst0);
		fConst5 = (1.0f / fConst0);
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.5f);
		fButton0 = FAUSTFLOAT(0.0f);
		fHslider1 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(0.0f);
		fHslider3 = FAUSTFLOAT(9.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec0[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fVec0[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec2[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec5[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec3[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fVec1[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec6[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			fRec1[l7] = 0.0f;
			
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
		ui_interface->openVerticalBox("dubDub");
		ui_interface->declare(&fHslider0, "acc", "1 0 -10 0 10");
		ui_interface->addHorizontalSlider("gain", &fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addButton("gate", &fButton0);
		ui_interface->declare(&fHslider3, "acc", "0 0 -10 0 10");
		ui_interface->addHorizontalSlider("modFeq", &fHslider3, 9.0f, 0.5f, 18.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("x", &fHslider1, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("y", &fHslider2, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = (0.00100000005f * mydsp_faustpower2_f(float(fHslider0)));
		float fSlow1 = float(fButton0);
		float fSlow2 = (fConst2 * fSlow1);
		float fSlow3 = ((420.0f * float(fHslider1)) + 80.0f);
		int iSlow4 = (fSlow1 == 0.0f);
		float fSlow5 = (1.0f - float(fHslider2));
		float fSlow6 = float(fHslider3);
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec0[0] = (fSlow0 + (0.999000013f * fRec0[1]));
			fVec0[0] = fSlow1;
			fRec2[0] = (fSlow2 + (fConst1 * fRec2[1]));
			int iTemp0 = ((fSlow1 == fVec0[1]) | iSlow4);
			fRec5[0] = ((fSlow3 * (1.0f - (0.999000013f * float(iTemp0)))) + (0.999000013f * (float(iTemp0) * fRec5[1])));
			float fTemp1 = max(1.00000001e-07f, fabsf(fRec5[0]));
			float fTemp2 = (fRec3[1] + (fConst3 * fTemp1));
			float fTemp3 = (fTemp2 + -1.0f);
			int iTemp4 = (fTemp3 < 0.0f);
			fRec3[0] = (iTemp4?fTemp2:fTemp3);
			float fRec4 = (iTemp4?fTemp2:(fTemp2 + ((1.0f - (fConst0 / fTemp1)) * fTemp3)));
			fVec1[0] = fSlow6;
			float fTemp5 = ((fConst5 * fVec1[1]) + fRec6[1]);
			fRec6[0] = (fTemp5 - floorf(fTemp5));
			float fTemp6 = tanf((fConst4 * ((4950.0f * (1.0f - (fSlow5 * (1.0f - fabsf(((2.0f * fRec6[0]) + -1.0f)))))) + 50.0f)));
			float fTemp7 = (1.0f / fTemp6);
			float fTemp8 = (((fTemp7 + 0.125f) / fTemp6) + 1.0f);
			fRec1[0] = ((0.5f * (fRec2[0] * ((2.0f * fRec4) + -1.0f))) - (((fRec1[2] * (((fTemp7 + -0.125f) / fTemp6) + 1.0f)) + (2.0f * (fRec1[1] * (1.0f - (1.0f / mydsp_faustpower2_f(fTemp6)))))) / fTemp8));
			float fTemp9 = ((fRec0[0] * (fRec1[2] + (fRec1[0] + (2.0f * fRec1[1])))) / fTemp8);
			output0[i] = FAUSTFLOAT(fTemp9);
			output1[i] = FAUSTFLOAT(fTemp9);
			fRec0[1] = fRec0[0];
			fVec0[1] = fVec0[0];
			fRec2[1] = fRec2[0];
			fRec5[1] = fRec5[0];
			fRec3[1] = fRec3[0];
			fVec1[1] = fVec1[0];
			fRec6[1] = fRec6[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			
		}
		
	}

	
};

#endif
