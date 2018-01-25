/* ------------------------------------------------------------
name: "rain"
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
	
	FAUSTFLOAT fHslider0;
	int iRec0[2];
	float fVec0[2];
	FAUSTFLOAT fHslider1;
	float fVec1[2];
	int fSamplingFreq;
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("name", "rain");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
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
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.5f);
		fHslider1 = FAUSTFLOAT(300.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iRec0[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fVec0[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fVec1[l2] = 0.0f;
			
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
		ui_interface->openVerticalBox("rain");
		ui_interface->addHorizontalSlider("density", &fHslider1, 300.0f, 0.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("volume", &fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = float(fHslider0);
		float fSlow1 = (0.00100000005f * float(fHslider1));
		for (int i = 0; (i < count); i = (i + 1)) {
			int iTemp0 = (1103515245 * (iRec0[1] + 12345));
			iRec0[0] = (1103515245 * (iTemp0 + 12345));
			int iRec1 = iTemp0;
			float fTemp1 = (4.65661287e-10f * float(iRec0[0]));
			fVec0[0] = fTemp1;
			output0[i] = FAUSTFLOAT((fSlow0 * (fVec0[1] * float((fabsf(fTemp1) < fSlow1)))));
			float fTemp2 = (4.65661287e-10f * float(iRec1));
			fVec1[0] = fTemp2;
			output1[i] = FAUSTFLOAT((fSlow0 * (fVec1[1] * float((fabsf(fTemp2) < fSlow1)))));
			iRec0[1] = iRec0[0];
			fVec0[1] = fVec0[0];
			fVec1[1] = fVec1[0];
			
		}
		
	}

	
};

#endif
