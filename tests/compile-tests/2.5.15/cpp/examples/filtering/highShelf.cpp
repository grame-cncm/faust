/* ------------------------------------------------------------
name: "highShelf"
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
	
	FAUSTFLOAT fHslider0;
	int fSamplingFreq;
	float fConst0;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	float fRec0[3];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("maxmsp.lib/author", "GRAME");
		m->declare("maxmsp.lib/copyright", "GRAME");
		m->declare("maxmsp.lib/license", "LGPL");
		m->declare("maxmsp.lib/name", "MaxMSP compatibility Library");
		m->declare("maxmsp.lib/version", "1.1");
		m->declare("name", "highShelf");
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
		fConst0 = (6.28318548f / min(192000.0f, max(1.0f, float(fSamplingFreq))));
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.0f);
		fHslider1 = FAUSTFLOAT(1000.0f);
		fHslider2 = FAUSTFLOAT(1.0f);
		
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
		ui_interface->openVerticalBox("highShelf");
		ui_interface->addHorizontalSlider("Freq", &fHslider1, 1000.0f, 100.0f, 10000.0f, 1.0f);
		ui_interface->declare(&fHslider0, "unit", "dB");
		ui_interface->addHorizontalSlider("Gain", &fHslider0, 0.0f, -10.0f, 10.0f, 0.100000001f);
		ui_interface->addHorizontalSlider("Q", &fHslider2, 1.0f, 0.00999999978f, 100.0f, 0.00999999978f);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = powf(10.0f, (0.0250000004f * float(fHslider0)));
		float fSlow1 = (fConst0 * max(0.0f, float(fHslider1)));
		float fSlow2 = ((sqrtf(fSlow0) * sinf(fSlow1)) / max(0.00100000005f, float(fHslider2)));
		float fSlow3 = cosf(fSlow1);
		float fSlow4 = ((fSlow0 + -1.0f) * fSlow3);
		float fSlow5 = (1.0f / ((fSlow0 + fSlow2) + (1.0f - fSlow4)));
		float fSlow6 = (fSlow0 + fSlow4);
		float fSlow7 = (fSlow0 * ((fSlow2 + fSlow6) + 1.0f));
		float fSlow8 = (fSlow0 + (1.0f - (fSlow4 + fSlow2)));
		float fSlow9 = ((fSlow0 + 1.0f) * fSlow3);
		float fSlow10 = (2.0f * (fSlow0 + (-1.0f - fSlow9)));
		float fSlow11 = ((0.0f - (2.0f * fSlow0)) * ((fSlow0 + fSlow9) + -1.0f));
		float fSlow12 = (fSlow0 * (fSlow6 + (1.0f - fSlow2)));
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec0[0] = (float(input0[i]) - (fSlow5 * ((fSlow8 * fRec0[2]) + (fSlow10 * fRec0[1]))));
			output0[i] = FAUSTFLOAT((fSlow5 * (((fSlow7 * fRec0[0]) + (fSlow11 * fRec0[1])) + (fSlow12 * fRec0[2]))));
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			
		}
		
	}

	
};

#endif
