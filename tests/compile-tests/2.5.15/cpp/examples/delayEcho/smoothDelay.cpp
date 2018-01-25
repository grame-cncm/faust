/* ------------------------------------------------------------
author: "Yann Orlarey"
copyright: "Grame"
license: "STK-4.3"
name: "smoothDelay"
version: "1.0"
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
	
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider0;
	float fConst2;
	FAUSTFLOAT fHslider1;
	float fRec1[2];
	float fRec2[2];
	float fRec3[2];
	float fRec4[2];
	FAUSTFLOAT fHslider2;
	int IOTA;
	float fVec0[1048576];
	float fRec0[2];
	float fVec1[1048576];
	float fRec5[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("author", "Yann Orlarey");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("copyright", "Grame");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("license", "STK-4.3");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "smoothDelay");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("version", "1.0");
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
		fConst0 = min(192000.0f, max(1.0f, float(fSamplingFreq)));
		fConst1 = (0.00100000005f * fConst0);
		fConst2 = (1000.0f / fConst0);
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.0f);
		fHslider1 = FAUSTFLOAT(10.0f);
		fHslider2 = FAUSTFLOAT(0.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec1[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec2[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec3[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec4[l3] = 0.0f;
			
		}
		IOTA = 0;
		for (int l4 = 0; (l4 < 1048576); l4 = (l4 + 1)) {
			fVec0[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec0[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 1048576); l6 = (l6 + 1)) {
			fVec1[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec5[l7] = 0.0f;
			
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
		ui_interface->openVerticalBox("smoothDelay");
		ui_interface->declare(&fHslider0, "style", "knob");
		ui_interface->declare(&fHslider0, "unit", "ms");
		ui_interface->addHorizontalSlider("delay", &fHslider0, 0.0f, 0.0f, 5000.0f, 0.100000001f);
		ui_interface->declare(&fHslider2, "style", "knob");
		ui_interface->addHorizontalSlider("feedback", &fHslider2, 0.0f, 0.0f, 100.0f, 0.100000001f);
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->declare(&fHslider1, "unit", "ms");
		ui_interface->addHorizontalSlider("interpolation", &fHslider1, 10.0f, 1.0f, 100.0f, 0.100000001f);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = (fConst1 * float(fHslider0));
		float fSlow1 = (fConst2 / float(fHslider1));
		float fSlow2 = (0.0f - fSlow1);
		float fSlow3 = (0.00999999978f * float(fHslider2));
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = ((fRec1[1] != 0.0f)?(((fRec2[1] > 0.0f) & (fRec2[1] < 1.0f))?fRec1[1]:0.0f):(((fRec2[1] == 0.0f) & (fSlow0 != fRec3[1]))?fSlow1:(((fRec2[1] == 1.0f) & (fSlow0 != fRec4[1]))?fSlow2:0.0f)));
			fRec1[0] = fTemp0;
			fRec2[0] = max(0.0f, min(1.0f, (fRec2[1] + fTemp0)));
			fRec3[0] = (((fRec2[1] >= 1.0f) & (fRec4[1] != fSlow0))?fSlow0:fRec3[1]);
			fRec4[0] = (((fRec2[1] <= 0.0f) & (fRec3[1] != fSlow0))?fSlow0:fRec4[1]);
			float fTemp1 = (1.0f - fRec2[0]);
			float fTemp2 = (float(input0[i]) + (fSlow3 * fRec0[1]));
			fVec0[(IOTA & 1048575)] = fTemp2;
			int iTemp3 = int(min(524288.0f, max(0.0f, fRec3[0])));
			int iTemp4 = int(min(524288.0f, max(0.0f, fRec4[0])));
			fRec0[0] = ((fTemp1 * fVec0[((IOTA - iTemp3) & 1048575)]) + (fRec2[0] * fVec0[((IOTA - iTemp4) & 1048575)]));
			output0[i] = FAUSTFLOAT(fRec0[0]);
			float fTemp5 = (float(input1[i]) + (fSlow3 * fRec5[1]));
			fVec1[(IOTA & 1048575)] = fTemp5;
			fRec5[0] = ((fTemp1 * fVec1[((IOTA - iTemp3) & 1048575)]) + (fRec2[0] * fVec1[((IOTA - iTemp4) & 1048575)]));
			output1[i] = FAUSTFLOAT(fRec5[0]);
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			IOTA = (IOTA + 1);
			fRec0[1] = fRec0[0];
			fRec5[1] = fRec5[0];
			
		}
		
	}

	
};

#endif
