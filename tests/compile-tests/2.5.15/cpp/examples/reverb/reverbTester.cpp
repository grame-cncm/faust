/* ------------------------------------------------------------
author: "RM"
name: "reverbTester"
version: "0.0"
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
	
	FAUSTFLOAT fButton0;
	float fVec0[2];
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fButton1;
	float fVec1[2];
	FAUSTFLOAT fCheckbox1;
	int iRec1[2];
	float fRec0[4];
	FAUSTFLOAT fButton2;
	float fVec2[2];
	int fSamplingFreq;
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("author", "RM");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("description", "Handy test inputs for reverberator demos below.");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "reverbTester");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
		m->declare("version", "0.0");
	}

	virtual int getNumInputs() {
		return 5;
		
	}
	virtual int getNumOutputs() {
		return 2;
		
	}
	virtual int getInputRate(int channel) {
		int rate;
		switch (channel) {
			case 0: {
				rate = 0;
				break;
			}
			case 1: {
				rate = 0;
				break;
			}
			case 2: {
				rate = 0;
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
		fButton0 = FAUSTFLOAT(0.0f);
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fButton1 = FAUSTFLOAT(0.0f);
		fCheckbox1 = FAUSTFLOAT(0.0f);
		fButton2 = FAUSTFLOAT(0.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fVec0[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fVec1[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			iRec1[l2] = 0;
			
		}
		for (int l3 = 0; (l3 < 4); l3 = (l3 + 1)) {
			fRec0[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fVec2[l4] = 0.0f;
			
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
		ui_interface->openVerticalBox("reverbTester");
		ui_interface->declare(0, "1", "");
		ui_interface->openVerticalBox("Input Config");
		ui_interface->declare(&fCheckbox0, "1", "");
		ui_interface->declare(&fCheckbox0, "tooltip", "When this is checked, the stereo external audio inputs are   disabled (good for hearing the impulse response or pink-noise response alone)");
		ui_interface->addCheckButton("Mute Ext Inputs", &fCheckbox0);
		ui_interface->declare(&fCheckbox1, "2", "");
		ui_interface->declare(&fCheckbox1, "tooltip", "Pink Noise (or 1/f noise) is Constant-Q Noise (useful for adjusting   the EQ sections)");
		ui_interface->addCheckButton("Pink Noise", &fCheckbox1);
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("Impulse Selection");
		ui_interface->declare(&fButton1, "1", "");
		ui_interface->declare(&fButton1, "tooltip", "Send impulse into LEFT channel");
		ui_interface->addButton("Left", &fButton1);
		ui_interface->declare(&fButton0, "2", "");
		ui_interface->declare(&fButton0, "tooltip", "Send impulse into LEFT and RIGHT channels");
		ui_interface->addButton("Center", &fButton0);
		ui_interface->declare(&fButton2, "3", "");
		ui_interface->declare(&fButton2, "tooltip", "Send impulse into RIGHT channel");
		ui_interface->addButton("Right", &fButton2);
		ui_interface->closeBox();
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* input2 = inputs[2];
		FAUSTFLOAT* input3 = inputs[3];
		FAUSTFLOAT* input4 = inputs[4];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = float(fButton0);
		float fSlow1 = (1.0f - float(fCheckbox0));
		float fSlow2 = float(fButton1);
		float fSlow3 = (0.100000001f * float(fCheckbox1));
		float fSlow4 = float(fButton2);
		for (int i = 0; (i < count); i = (i + 1)) {
			fVec0[0] = fSlow0;
			int iTemp0 = ((fSlow0 - fVec0[1]) > 0.0f);
			fVec1[0] = fSlow2;
			iRec1[0] = ((1103515245 * iRec1[1]) + 12345);
			fRec0[0] = (((0.522189379f * fRec0[3]) + ((4.65661287e-10f * float(iRec1[0])) + (2.49495602f * fRec0[1]))) - (2.0172658f * fRec0[2]));
			float fTemp1 = (fSlow3 * (((0.0499220341f * fRec0[0]) + (0.0506126992f * fRec0[2])) - ((0.0959935337f * fRec0[1]) + (0.00440878607f * fRec0[3]))));
			output0[i] = FAUSTFLOAT(((float(iTemp0) + ((fSlow1 * float(input3[i])) + float(((fSlow2 - fVec1[1]) > 0.0f)))) + fTemp1));
			fVec2[0] = fSlow4;
			output1[i] = FAUSTFLOAT((float(((fSlow4 - fVec2[1]) > 0.0f)) + ((fSlow1 * float(input4[i])) + (float(iTemp0) + fTemp1))));
			fVec0[1] = fVec0[0];
			fVec1[1] = fVec1[0];
			iRec1[1] = iRec1[0];
			for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				fRec0[j0] = fRec0[(j0 - 1)];
				
			}
			fVec2[1] = fVec2[0];
			
		}
		
	}

	
};

#endif
