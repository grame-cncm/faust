/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2006"
license: "BSD"
name: "bandFilter"
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
	FAUSTFLOAT fEntry0;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT fEntry1;
	float fRec0[3];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("author", "Grame");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("copyright", "(c)GRAME 2006");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("license", "BSD");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "bandFilter");
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
		fConst0 = (3.14159274f / min(192000.0f, max(1.0f, float(fSamplingFreq))));
		
	}
	
	virtual void instanceResetUserInterface() {
		fEntry0 = FAUSTFLOAT(1000.0f);
		fVslider0 = FAUSTFLOAT(0.0f);
		fEntry1 = FAUSTFLOAT(50.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) {
			fRec0[l0] = 0.0f;
			
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
		ui_interface->openVerticalBox("Bandfilter");
		ui_interface->declare(&fEntry1, "style", "knob");
		ui_interface->addNumEntry("Q factor", &fEntry1, 50.0f, 0.100000001f, 100.0f, 0.100000001f);
		ui_interface->declare(&fEntry0, "style", "knob");
		ui_interface->declare(&fEntry0, "unit", "Hz");
		ui_interface->addNumEntry("freq", &fEntry0, 1000.0f, 20.0f, 20000.0f, 1.0f);
		ui_interface->declare(&fVslider0, "unit", "dB");
		ui_interface->addVerticalSlider("gain", &fVslider0, 0.0f, -50.0f, 50.0f, 0.100000001f);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = tanf((fConst0 * float(fEntry0)));
		float fSlow1 = float(fEntry1);
		float fSlow2 = (powf(10.0f, (0.0500000007f * (0.0f - float(fVslider0)))) / fSlow1);
		float fSlow3 = (1.0f / ((fSlow0 * (fSlow0 + fSlow2)) + 1.0f));
		float fSlow4 = (2.0f * (mydsp_faustpower2_f(fSlow0) + -1.0f));
		float fSlow5 = ((fSlow0 * (fSlow0 - fSlow2)) + 1.0f);
		float fSlow6 = (1.0f / fSlow1);
		float fSlow7 = ((fSlow0 * (fSlow0 + fSlow6)) + 1.0f);
		float fSlow8 = (1.0f - (fSlow0 * (fSlow6 - fSlow0)));
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = (fSlow4 * fRec0[1]);
			fRec0[0] = (float(input0[i]) - (fSlow3 * ((fSlow5 * fRec0[2]) + fTemp0)));
			output0[i] = FAUSTFLOAT((fSlow3 * ((fTemp0 + (fSlow7 * fRec0[0])) + (fSlow8 * fRec0[2]))));
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			
		}
		
	}

	
};

#endif
