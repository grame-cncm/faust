/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2006"
license: "BSD"
name: "spat"
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
	
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	float fRec0[2];
	float fRec1[2];
	float fRec2[2];
	float fRec3[2];
	float fRec4[2];
	float fRec5[2];
	float fRec6[2];
	float fRec7[2];
	int fSamplingFreq;
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("author", "Grame");
		m->declare("copyright", "(c)GRAME 2006");
		m->declare("license", "BSD");
		m->declare("name", "spat");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("spats.lib/name", "Faust Spatialization Library");
		m->declare("spats.lib/version", "0.0");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() {
		return 1;
		
	}
	virtual int getNumOutputs() {
		return 8;
		
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
			case 4: {
				rate = 1;
				break;
			}
			case 5: {
				rate = 1;
				break;
			}
			case 6: {
				rate = 1;
				break;
			}
			case 7: {
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
		fHslider1 = FAUSTFLOAT(0.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec0[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec1[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec2[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec3[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec4[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec5[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec6[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec7[l7] = 0.0f;
			
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
		ui_interface->openVerticalBox("Spatializer 1x8");
		ui_interface->addHorizontalSlider("angle", &fHslider1, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("distance", &fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		FAUSTFLOAT* output2 = outputs[2];
		FAUSTFLOAT* output3 = outputs[3];
		FAUSTFLOAT* output4 = outputs[4];
		FAUSTFLOAT* output5 = outputs[5];
		FAUSTFLOAT* output6 = outputs[6];
		FAUSTFLOAT* output7 = outputs[7];
		float fSlow0 = float(fHslider0);
		float fSlow1 = (fSlow0 + 1.0f);
		float fSlow2 = float(fHslider1);
		float fSlow3 = (4.99999987e-05f * (fSlow1 * sqrtf(max(0.0f, (1.0f - (8.0f * (fSlow0 * fabsf((fmodf((fSlow2 + 1.5f), 1.0f) + -0.5f)))))))));
		float fSlow4 = (4.99999987e-05f * (fSlow1 * sqrtf(max(0.0f, (1.0f - (8.0f * (fSlow0 * fabsf((fmodf((fSlow2 + 1.375f), 1.0f) + -0.5f)))))))));
		float fSlow5 = (4.99999987e-05f * (fSlow1 * sqrtf(max(0.0f, (1.0f - (8.0f * (fSlow0 * fabsf((fmodf((fSlow2 + 1.25f), 1.0f) + -0.5f)))))))));
		float fSlow6 = (4.99999987e-05f * (fSlow1 * sqrtf(max(0.0f, (1.0f - (8.0f * (fSlow0 * fabsf((fmodf((fSlow2 + 1.125f), 1.0f) + -0.5f)))))))));
		float fSlow7 = (4.99999987e-05f * (fSlow1 * sqrtf(max(0.0f, (1.0f - (8.0f * (fSlow0 * fabsf((fmodf((fSlow2 + 1.0f), 1.0f) + -0.5f)))))))));
		float fSlow8 = (4.99999987e-05f * (fSlow1 * sqrtf(max(0.0f, (1.0f - (8.0f * (fSlow0 * fabsf((fmodf((fSlow2 + 0.875f), 1.0f) + -0.5f)))))))));
		float fSlow9 = (4.99999987e-05f * (fSlow1 * sqrtf(max(0.0f, (1.0f - (8.0f * (fSlow0 * fabsf((fmodf((fSlow2 + 0.75f), 1.0f) + -0.5f)))))))));
		float fSlow10 = (4.99999987e-05f * (fSlow1 * sqrtf(max(0.0f, (1.0f - (8.0f * (fSlow0 * fabsf((fmodf((fSlow2 + 0.625f), 1.0f) + -0.5f)))))))));
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input0[i]);
			fRec0[0] = (fSlow3 + (0.999899983f * fRec0[1]));
			output0[i] = FAUSTFLOAT((fTemp0 * fRec0[0]));
			fRec1[0] = (fSlow4 + (0.999899983f * fRec1[1]));
			output1[i] = FAUSTFLOAT((fTemp0 * fRec1[0]));
			fRec2[0] = (fSlow5 + (0.999899983f * fRec2[1]));
			output2[i] = FAUSTFLOAT((fTemp0 * fRec2[0]));
			fRec3[0] = (fSlow6 + (0.999899983f * fRec3[1]));
			output3[i] = FAUSTFLOAT((fTemp0 * fRec3[0]));
			fRec4[0] = (fSlow7 + (0.999899983f * fRec4[1]));
			output4[i] = FAUSTFLOAT((fTemp0 * fRec4[0]));
			fRec5[0] = (fSlow8 + (0.999899983f * fRec5[1]));
			output5[i] = FAUSTFLOAT((fTemp0 * fRec5[0]));
			fRec6[0] = (fSlow9 + (0.999899983f * fRec6[1]));
			output6[i] = FAUSTFLOAT((fTemp0 * fRec6[0]));
			fRec7[0] = (fSlow10 + (0.999899983f * fRec7[1]));
			output7[i] = FAUSTFLOAT((fTemp0 * fRec7[0]));
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec7[1] = fRec7[0];
			
		}
		
	}

	
};

#endif
