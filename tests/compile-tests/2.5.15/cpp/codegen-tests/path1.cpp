/* ------------------------------------------------------------
name: "path1"
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
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT fHslider5;
	FAUSTFLOAT fHslider6;
	FAUSTFLOAT fHslider7;
	int fSamplingFreq;
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("name", "path1");
	}

	virtual int getNumInputs() {
		return 4;
		
	}
	virtual int getNumOutputs() {
		return 4;
		
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
			case 2: {
				rate = 1;
				break;
			}
			case 3: {
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
			case 2: {
				rate = 1;
				break;
			}
			case 3: {
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
		fHslider0 = FAUSTFLOAT(0.0f);
		fHslider1 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(0.0f);
		fHslider3 = FAUSTFLOAT(0.0f);
		fHslider4 = FAUSTFLOAT(0.0f);
		fHslider5 = FAUSTFLOAT(0.0f);
		fHslider6 = FAUSTFLOAT(0.0f);
		fHslider7 = FAUSTFLOAT(0.0f);
		
	}
	
	virtual void instanceClear() {
		
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
		ui_interface->openTabBox("toto");
		ui_interface->openVerticalBox("foo 0");
		ui_interface->addHorizontalSlider("slid1", &fHslider0, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addHorizontalSlider("slid2", &fHslider1, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("foo 1");
		ui_interface->addHorizontalSlider("slid1", &fHslider2, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addHorizontalSlider("slid2", &fHslider3, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("foo 2");
		ui_interface->addHorizontalSlider("slid1", &fHslider4, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addHorizontalSlider("slid2", &fHslider5, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("foo 3");
		ui_interface->addHorizontalSlider("slid1", &fHslider6, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addHorizontalSlider("slid2", &fHslider7, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* input2 = inputs[2];
		FAUSTFLOAT* input3 = inputs[3];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		FAUSTFLOAT* output2 = outputs[2];
		FAUSTFLOAT* output3 = outputs[3];
		float fSlow0 = (float(fHslider0) * float(fHslider1));
		float fSlow1 = (float(fHslider2) * float(fHslider3));
		float fSlow2 = (float(fHslider4) * float(fHslider5));
		float fSlow3 = (float(fHslider6) * float(fHslider7));
		for (int i = 0; (i < count); i = (i + 1)) {
			output0[i] = FAUSTFLOAT((fSlow0 * float(input0[i])));
			output1[i] = FAUSTFLOAT((fSlow1 * float(input1[i])));
			output2[i] = FAUSTFLOAT((fSlow2 * float(input2[i])));
			output3[i] = FAUSTFLOAT((fSlow3 * float(input3[i])));
			
		}
		
	}

	
};

#endif
