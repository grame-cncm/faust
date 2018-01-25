/* ------------------------------------------------------------
name: "spectralTilt"
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
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	float fConst2;
	float fVec0[2];
	float fRec1[2];
	float fVec1[2];
	float fRec0[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("description", "Demonstrate the Spectral Tilt effect on test signals");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "spectralTilt");
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
		fConst0 = min(192000.0f, max(1.0f, float(fSamplingFreq)));
		fConst1 = (3.14159274f / fConst0);
		fConst2 = (1.0f / tanf((0.5f / fConst0)));
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(100.0f);
		fHslider1 = FAUSTFLOAT(5000.0f);
		fHslider2 = FAUSTFLOAT(-0.5f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fVec0[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec1[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fVec1[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec0[l3] = 0.0f;
			
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
		ui_interface->openVerticalBox("spectralTilt");
		ui_interface->declare(&fHslider2, "1", "");
		ui_interface->addHorizontalSlider("Slope of Spectral Tilt across Band", &fHslider2, -0.5f, -1.0f, 1.0f, 0.00100000005f);
		ui_interface->declare(&fHslider0, "2", "");
		ui_interface->declare(&fHslider0, "unit", "Hz");
		ui_interface->addHorizontalSlider("Band Start Frequency", &fHslider0, 100.0f, 20.0f, 10000.0f, 1.0f);
		ui_interface->declare(&fHslider1, "3", "");
		ui_interface->declare(&fHslider1, "unit", "Hz");
		ui_interface->addHorizontalSlider("Band Width", &fHslider1, 5000.0f, 100.0f, 10000.0f, 1.0f);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = float(fHslider0);
		float fSlow1 = powf(((fSlow0 + float(fHslider1)) / fSlow0), 1.0f);
		float fSlow2 = tanf((fConst1 * (fSlow0 * fSlow1)));
		float fSlow3 = float(fHslider2);
		float fSlow4 = tanf((fConst1 * (fSlow0 * powf(fSlow1, (1.0f - fSlow3)))));
		float fSlow5 = (fSlow2 / fSlow4);
		float fSlow6 = tanf((fConst1 * fSlow0));
		float fSlow7 = (6.28318548f * ((fSlow0 * fSlow2) / fSlow6));
		float fSlow8 = (fConst2 + fSlow7);
		float fSlow9 = (0.0f - ((fSlow7 - fConst2) / fSlow8));
		float fSlow10 = (1.0f / fSlow8);
		float fSlow11 = (6.28318548f * ((fSlow0 * fSlow4) / fSlow6));
		float fSlow12 = (fSlow11 - fConst2);
		float fSlow13 = tanf((fConst1 * (fSlow0 * powf(fSlow1, (0.0f - fSlow3)))));
		float fSlow14 = (fSlow6 / fSlow13);
		float fSlow15 = (6.28318548f * fSlow0);
		float fSlow16 = (fConst2 + fSlow15);
		float fSlow17 = (0.0f - ((fSlow15 - fConst2) / fSlow16));
		float fSlow18 = (1.0f / fSlow16);
		float fSlow19 = (6.28318548f * ((fSlow0 * fSlow13) / fSlow6));
		float fSlow20 = (fConst2 + fSlow19);
		float fSlow21 = (fSlow19 - fConst2);
		float fSlow22 = ((fSlow6 * (fConst2 + fSlow11)) / fSlow13);
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input0[i]);
			fVec0[0] = fTemp0;
			fRec1[0] = ((fSlow17 * fRec1[1]) + (fSlow18 * ((fSlow20 * fTemp0) + (fSlow21 * fVec0[1]))));
			fVec1[0] = (fSlow14 * fRec1[0]);
			fRec0[0] = ((fSlow9 * fRec0[1]) + (fSlow10 * ((fSlow12 * fVec1[1]) + (fSlow22 * fRec1[0]))));
			output0[i] = FAUSTFLOAT((fSlow5 * fRec0[0]));
			fVec0[1] = fVec0[0];
			fRec1[1] = fRec1[0];
			fVec1[1] = fVec1[0];
			fRec0[1] = fRec0[0];
			
		}
		
	}

	
};

#endif
