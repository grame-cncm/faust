/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2006"
license: "BSD"
name: "pitchShifter"
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


#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif
#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class mydsp : public dsp {
	
 private:
	
	int IOTA;
	float fVec0[131072];
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	float fRec0[2];
	FAUSTFLOAT fHslider2;
	int fSamplingFreq;
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("author", "Grame");
		m->declare("copyright", "(c)GRAME 2006");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("license", "BSD");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("misceffects.lib/name", "Faust Math Library");
		m->declare("misceffects.lib/version", "2.0");
		m->declare("name", "pitchShifter");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() {
		return 1;
		
	}
	virtual int getNumOutputs() {
		return 1;
		
	}
	virtual int getInputRate(int channel) {
		int rate;
		switch (channel) {
			case 0: {
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
		fHslider0 = FAUSTFLOAT(1000.0f);
		fHslider1 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(10.0f);
		
	}
	
	virtual void instanceClear() {
		IOTA = 0;
		for (int l0 = 0; (l0 < 131072); l0 = (l0 + 1)) {
			fVec0[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec0[l1] = 0.0f;
			
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
		ui_interface->openVerticalBox("Pitch Shifter");
		ui_interface->addHorizontalSlider("shift (semitones)", &fHslider1, 0.0f, -12.0f, 12.0f, 0.100000001f);
		ui_interface->addHorizontalSlider("window (samples)", &fHslider0, 1000.0f, 50.0f, 10000.0f, 1.0f);
		ui_interface->addHorizontalSlider("xfade (samples)", &fHslider2, 10.0f, 1.0f, 10000.0f, 1.0f);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = float(fHslider0);
		float fSlow1 = powf(2.0f, (0.0833333358f * float(fHslider1)));
		float fSlow2 = (1.0f / float(fHslider2));
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input0[i]);
			fVec0[(IOTA & 131071)] = fTemp0;
			fRec0[0] = fmodf((fSlow0 + ((fRec0[1] + 1.0f) - fSlow1)), fSlow0);
			int iTemp1 = int(fRec0[0]);
			float fTemp2 = floorf(fRec0[0]);
			float fTemp3 = (1.0f - fRec0[0]);
			float fTemp4 = min((fSlow2 * fRec0[0]), 1.0f);
			float fTemp5 = (fSlow0 + fRec0[0]);
			int iTemp6 = int(fTemp5);
			float fTemp7 = floorf(fTemp5);
			output0[i] = FAUSTFLOAT(((((fVec0[((IOTA - min(65537, max(0, iTemp1))) & 131071)] * (fTemp2 + fTemp3)) + ((fRec0[0] - fTemp2) * fVec0[((IOTA - min(65537, max(0, (iTemp1 + 1)))) & 131071)])) * fTemp4) + (((fVec0[((IOTA - min(65537, max(0, iTemp6))) & 131071)] * ((fTemp7 + fTemp3) - fSlow0)) + ((fSlow0 + (fRec0[0] - fTemp7)) * fVec0[((IOTA - min(65537, max(0, (iTemp6 + 1)))) & 131071)])) * (1.0f - fTemp4))));
			IOTA = (IOTA + 1);
			fRec0[1] = fRec0[0];
			
		}
		
	}

	
};

#endif
