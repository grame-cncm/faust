/* ------------------------------------------------------------
name: "trumpet"
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
	
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider0;
	float fRec2[2];
	FAUSTFLOAT fButton0;
	FAUSTFLOAT fHslider1;
	float fVec0[2];
	FAUSTFLOAT fHslider2;
	float fRec3[2];
	float fConst2;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT fHslider4;
	float fRec6[2];
	float fRec4[2];
	float fVec1[2];
	float fRec1[2];
	float fRec0[3];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("interface", "SmartKeyboard{  'Number of Keyboards':'5',  'Max Keyboard Polyphony':'1',  'Mono Mode':'1',  'Keyboard 0 - Number of Keys':'13',  'Keyboard 1 - Number of Keys':'13',  'Keyboard 2 - Number of Keys':'13',  'Keyboard 3 - Number of Keys':'13',  'Keyboard 4 - Number of Keys':'13',  'Keyboard 0 - Lowest Key':'77',  'Keyboard 1 - Lowest Key':'72',  'Keyboard 2 - Lowest Key':'67',  'Keyboard 3 - Lowest Key':'62',  'Keyboard 4 - Lowest Key':'57',  'Rounding Mode':'2',  'Keyboard 0 - Send Y':'1',  'Keyboard 1 - Send Y':'1',  'Keyboard 2 - Send Y':'1',  'Keyboard 3 - Send Y':'1',  'Keyboard 4 - Send Y':'1', }");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "trumpet");
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
		fConst2 = (1.0f / fConst0);
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(1.0f);
		fButton0 = FAUSTFLOAT(0.0f);
		fHslider1 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(1.0f);
		fHslider3 = FAUSTFLOAT(300.0f);
		fHslider4 = FAUSTFLOAT(1.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec2[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fVec0[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec3[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec6[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec4[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fVec1[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec1[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			fRec0[l7] = 0.0f;
			
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
		ui_interface->openVerticalBox("trumpet");
		ui_interface->declare(&fHslider4, "midi", "pitchwheel");
		ui_interface->addHorizontalSlider("bend", &fHslider4, 1.0f, 0.0f, 10.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("freq", &fHslider3, 300.0f, 50.0f, 2000.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("gain", &fHslider2, 1.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addButton("gate", &fButton0);
		ui_interface->declare(&fHslider1, "midi", "ctrl 64");
		ui_interface->addHorizontalSlider("sustain", &fHslider1, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->declare(&fHslider0, "midi", "ctrl 1");
		ui_interface->addHorizontalSlider("y", &fHslider0, 1.0f, 0.0f, 1.0f, 0.00100000005f);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = (0.00100000005f * float(fHslider0));
		float fSlow1 = min(1.0f, (float(fButton0) + float(fHslider1)));
		float fSlow2 = (0.00100000005f * (fSlow1 * float(fHslider2)));
		float fSlow3 = float(fHslider3);
		float fSlow4 = float(fHslider4);
		int iSlow5 = (fSlow1 == 0.0f);
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec2[0] = (fSlow0 + (0.999000013f * fRec2[1]));
			float fTemp0 = tanf((fConst1 * ((4000.0f * fRec2[0]) + 50.0f)));
			float fTemp1 = (1.0f / fTemp0);
			float fTemp2 = (fTemp1 + 1.0f);
			fVec0[0] = fSlow1;
			fRec3[0] = (fSlow2 + (0.999000013f * fRec3[1]));
			int iTemp3 = ((fSlow1 == fVec0[1]) | iSlow5);
			fRec6[0] = ((fSlow4 * (1.0f - (0.999000013f * float(iTemp3)))) + (0.999000013f * (float(iTemp3) * fRec6[1])));
			float fTemp4 = max(1.00000001e-07f, fabsf((fSlow3 * fRec6[0])));
			float fTemp5 = (fRec4[1] + (fConst2 * fTemp4));
			float fTemp6 = (fTemp5 + -1.0f);
			int iTemp7 = (fTemp6 < 0.0f);
			fRec4[0] = (iTemp7?fTemp5:fTemp6);
			float fRec5 = (iTemp7?fTemp5:(fTemp5 + ((1.0f - (fConst0 / fTemp4)) * fTemp6)));
			float fTemp8 = (fRec3[0] * ((2.0f * fRec5) + -1.0f));
			fVec1[0] = fTemp8;
			fRec1[0] = ((fRec1[1] * (0.0f - ((1.0f - fTemp1) / fTemp2))) + ((fTemp8 + fVec1[1]) / fTemp2));
			float fTemp9 = (((fTemp1 + 1.0f) / fTemp0) + 1.0f);
			fRec0[0] = (fRec1[0] - (((fRec0[2] * (((fTemp1 + -1.0f) / fTemp0) + 1.0f)) + (2.0f * (fRec0[1] * (1.0f - (1.0f / mydsp_faustpower2_f(fTemp0)))))) / fTemp9));
			float fTemp10 = ((fRec0[2] + (fRec0[0] + (2.0f * fRec0[1]))) / fTemp9);
			output0[i] = FAUSTFLOAT(fTemp10);
			output1[i] = FAUSTFLOAT(fTemp10);
			fRec2[1] = fRec2[0];
			fVec0[1] = fVec0[0];
			fRec3[1] = fRec3[0];
			fRec6[1] = fRec6[0];
			fRec4[1] = fRec4[0];
			fVec1[1] = fVec1[0];
			fRec1[1] = fRec1[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			
		}
		
	}

	
};

#endif
