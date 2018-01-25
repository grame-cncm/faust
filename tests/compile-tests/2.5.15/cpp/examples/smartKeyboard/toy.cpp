/* ------------------------------------------------------------
name: "toy"
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
	float fRec1[2];
	int fSamplingFreq;
	float fConst0;
	FAUSTFLOAT fHslider1;
	float fRec2[2];
	float fConst1;
	FAUSTFLOAT fHslider2;
	float fRec5[2];
	float fVec0[2];
	float fRec4[2];
	float fConst2;
	FAUSTFLOAT fHslider3;
	float fRec6[2];
	FAUSTFLOAT fHslider4;
	float fRec7[2];
	float fRec3[3];
	int IOTA;
	float fRec0[131072];
	FAUSTFLOAT fHslider5;
	float fRec8[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("interface", "SmartKeyboard{  'Number of Keyboards':'1',  'Max Keyboard Polyphony':'0',  'Keyboard 0 - Number of Keys':'1',  'Keyboard 0 - Send Freq':'0',  'Keyboard 0 - Static Mode':'1',  'Keyboard 0 - Piano Keyboard':'0',  'Keyboard 0 - Send Numbered X':'1',  'Keyboard 0 - Send Numbered Y':'1' }");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("misceffects.lib/name", "Faust Math Library");
		m->declare("misceffects.lib/version", "2.0");
		m->declare("name", "toy");
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
		fConst1 = (1.0f / fConst0);
		fConst2 = (3.14159274f / fConst0);
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.5f);
		fHslider1 = FAUSTFLOAT(0.5f);
		fHslider2 = FAUSTFLOAT(0.5f);
		fHslider3 = FAUSTFLOAT(0.5f);
		fHslider4 = FAUSTFLOAT(30.0f);
		fHslider5 = FAUSTFLOAT(0.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec1[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec2[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec5[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fVec0[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec4[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec6[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec7[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			fRec3[l7] = 0.0f;
			
		}
		IOTA = 0;
		for (int l8 = 0; (l8 < 131072); l8 = (l8 + 1)) {
			fRec0[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec8[l9] = 0.0f;
			
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
		ui_interface->openVerticalBox("toy");
		ui_interface->declare(&fHslider1, "acc", "0 0 -10 0 10");
		ui_interface->addHorizontalSlider("del", &fHslider1, 0.5f, 0.00999999978f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fHslider0, "acc", "1 0 -10 0 10");
		ui_interface->addHorizontalSlider("fb", &fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fHslider4, "acc", "0 0 -10 0 10");
		ui_interface->addHorizontalSlider("q", &fHslider4, 30.0f, 10.0f, 50.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("x0", &fHslider2, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("y0", &fHslider3, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("y1", &fHslider5, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = (0.00100000005f * float(fHslider0));
		float fSlow1 = (0.00100000005f * float(fHslider1));
		float fSlow2 = (0.00100000005f * float(fHslider2));
		float fSlow3 = (0.00100000005f * float(fHslider3));
		float fSlow4 = (0.00100000005f * float(fHslider4));
		float fSlow5 = (0.00100000005f * float(fHslider5));
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec1[0] = (fSlow0 + (0.999000013f * fRec1[1]));
			fRec2[0] = (fSlow1 + (0.999000013f * fRec2[1]));
			fRec5[0] = (fSlow2 + (0.999000013f * fRec5[1]));
			fVec0[0] = ((20.0f * fRec5[0]) + 2.0f);
			float fTemp0 = (fRec4[1] + (fConst1 * fVec0[1]));
			fRec4[0] = (fTemp0 - floorf(fTemp0));
			fRec6[0] = (fSlow3 + (0.999000013f * fRec6[1]));
			float fTemp1 = tanf((fConst2 * ((3000.0f * fRec6[0]) + 300.0f)));
			float fTemp2 = (1.0f / fTemp1);
			fRec7[0] = (fSlow4 + (0.999000013f * fRec7[1]));
			float fTemp3 = (1.0f / fRec7[0]);
			float fTemp4 = (((fTemp2 + fTemp3) / fTemp1) + 1.0f);
			fRec3[0] = (float(((fRec4[0] - fRec4[1]) < 0.0f)) - (((fRec3[2] * (((fTemp2 - fTemp3) / fTemp1) + 1.0f)) + (2.0f * (fRec3[1] * (1.0f - (1.0f / mydsp_faustpower2_f(fTemp1)))))) / fTemp4));
			fRec0[(IOTA & 131071)] = ((fRec1[0] * fRec0[((IOTA - (int(min(65536.0f, max(0.0f, (fConst0 * fRec2[0])))) + 1)) & 131071)]) + ((fRec3[2] + (fRec3[0] + (2.0f * fRec3[1]))) / fTemp4));
			fRec8[0] = (fSlow5 + (0.999000013f * fRec8[1]));
			float fTemp5 = max(-1.0f, min(1.0f, (fRec0[((IOTA - 0) & 131071)] * powf(10.0f, (2.0f * fRec8[0])))));
			float fTemp6 = (0.949999988f * (fTemp5 * (1.0f - (0.333333343f * mydsp_faustpower2_f(fTemp5)))));
			output0[i] = FAUSTFLOAT(fTemp6);
			output1[i] = FAUSTFLOAT(fTemp6);
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec5[1] = fRec5[0];
			fVec0[1] = fVec0[0];
			fRec4[1] = fRec4[0];
			fRec6[1] = fRec6[0];
			fRec7[1] = fRec7[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			IOTA = (IOTA + 1);
			fRec8[1] = fRec8[0];
			
		}
		
	}

	
};

#endif
