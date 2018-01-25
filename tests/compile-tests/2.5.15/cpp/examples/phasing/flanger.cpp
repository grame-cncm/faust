/* ------------------------------------------------------------
author: "JOS, revised by RM"
name: "flanger"
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
	
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fHslider0;
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider1;
	int iVec0[2];
	float fRec0[2];
	float fRec1[2];
	FAUSTFLOAT fHbargraph0;
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	int IOTA;
	float fVec1[4096];
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT fHslider5;
	float fRec2[2];
	float fVec2[4096];
	float fRec3[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("author", "JOS, revised by RM");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("description", "Flanger effect application.");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "flanger");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("phaflangers.lib/name", "Faust Phaser and Flanger Library");
		m->declare("phaflangers.lib/version", "0.0");
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("version", "0.0");
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
		fConst1 = (6.28318548f / fConst0);
		
	}
	
	virtual void instanceResetUserInterface() {
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fHslider0 = FAUSTFLOAT(0.0f);
		fHslider1 = FAUSTFLOAT(0.5f);
		fCheckbox1 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(1.0f);
		fHslider3 = FAUSTFLOAT(0.0f);
		fHslider4 = FAUSTFLOAT(1.0f);
		fHslider5 = FAUSTFLOAT(10.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec0[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec1[l2] = 0.0f;
			
		}
		IOTA = 0;
		for (int l3 = 0; (l3 < 4096); l3 = (l3 + 1)) {
			fVec1[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec2[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 4096); l5 = (l5 + 1)) {
			fVec2[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec3[l6] = 0.0f;
			
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
		ui_interface->declare(0, "tooltip", "Reference: https://ccrma.stanford.edu/~jos/pasp/Flanging.html");
		ui_interface->openVerticalBox("FLANGER");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fCheckbox0, "0", "");
		ui_interface->declare(&fCheckbox0, "tooltip", "When this is checked, the flanger   has no effect");
		ui_interface->addCheckButton("Bypass", &fCheckbox0);
		ui_interface->declare(&fCheckbox1, "1", "");
		ui_interface->addCheckButton("Invert Flange Sum", &fCheckbox1);
		ui_interface->declare(&fHbargraph0, "2", "");
		ui_interface->declare(&fHbargraph0, "style", "led");
		ui_interface->declare(&fHbargraph0, "tooltip", "Display sum of flange delays");
		ui_interface->addHorizontalBargraph("Flange LFO", &fHbargraph0, -1.5f, 1.5f);
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fHslider1, "1", "");
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->declare(&fHslider1, "unit", "Hz");
		ui_interface->addHorizontalSlider("Speed", &fHslider1, 0.5f, 0.0f, 10.0f, 0.00999999978f);
		ui_interface->declare(&fHslider2, "2", "");
		ui_interface->declare(&fHslider2, "style", "knob");
		ui_interface->addHorizontalSlider("Depth", &fHslider2, 1.0f, 0.0f, 1.0f, 0.00100000005f);
		ui_interface->declare(&fHslider3, "3", "");
		ui_interface->declare(&fHslider3, "style", "knob");
		ui_interface->addHorizontalSlider("Feedback", &fHslider3, 0.0f, -0.999000013f, 0.999000013f, 0.00100000005f);
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("Delay Controls");
		ui_interface->declare(&fHslider5, "1", "");
		ui_interface->declare(&fHslider5, "style", "knob");
		ui_interface->declare(&fHslider5, "unit", "ms");
		ui_interface->addHorizontalSlider("Flange Delay", &fHslider5, 10.0f, 0.0f, 20.0f, 0.00100000005f);
		ui_interface->declare(&fHslider4, "2", "");
		ui_interface->declare(&fHslider4, "style", "knob");
		ui_interface->declare(&fHslider4, "unit", "ms");
		ui_interface->addHorizontalSlider("Delay Offset", &fHslider4, 1.0f, 0.0f, 20.0f, 0.00100000005f);
		ui_interface->closeBox();
		ui_interface->declare(0, "3", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fHslider0, "unit", "dB");
		ui_interface->addHorizontalSlider("Flanger Output Level", &fHslider0, 0.0f, -60.0f, 10.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		int iSlow0 = int(float(fCheckbox0));
		float fSlow1 = powf(10.0f, (0.0500000007f * float(fHslider0)));
		float fSlow2 = (fConst1 * float(fHslider1));
		float fSlow3 = sinf(fSlow2);
		float fSlow4 = cosf(fSlow2);
		float fSlow5 = (0.0f - fSlow3);
		float fSlow6 = float(fHslider2);
		float fSlow7 = (int(float(fCheckbox1))?(0.0f - fSlow6):fSlow6);
		float fSlow8 = float(fHslider3);
		float fSlow9 = (0.00100000005f * float(fHslider4));
		float fSlow10 = (0.000500000024f * float(fHslider5));
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			fRec0[0] = ((fSlow3 * fRec1[1]) + (fSlow4 * fRec0[1]));
			fRec1[0] = (((fSlow4 * fRec1[1]) + (fSlow5 * fRec0[1])) + float((1 - iVec0[1])));
			fHbargraph0 = FAUSTFLOAT((fRec1[0] + fRec0[0]));
			float fTemp0 = float(input0[i]);
			float fTemp1 = (fSlow1 * (iSlow0?0.0f:fTemp0));
			float fTemp2 = ((fSlow8 * fRec2[1]) - fTemp1);
			fVec1[(IOTA & 4095)] = fTemp2;
			float fTemp3 = (fConst0 * (fSlow9 + (fSlow10 * (fRec0[0] + 1.0f))));
			int iTemp4 = int(fTemp3);
			float fTemp5 = floorf(fTemp3);
			fRec2[0] = ((fVec1[((IOTA - min(2049, max(0, iTemp4))) & 4095)] * (fTemp5 + (1.0f - fTemp3))) + ((fTemp3 - fTemp5) * fVec1[((IOTA - min(2049, max(0, (iTemp4 + 1)))) & 4095)]));
			output0[i] = FAUSTFLOAT((iSlow0?fTemp0:(0.5f * (fTemp1 + (fSlow7 * fRec2[0])))));
			float fTemp6 = float(input1[i]);
			float fTemp7 = (fSlow1 * (iSlow0?0.0f:fTemp6));
			float fTemp8 = ((fSlow8 * fRec3[1]) - fTemp7);
			fVec2[(IOTA & 4095)] = fTemp8;
			float fTemp9 = (fConst0 * (fSlow9 + (fSlow10 * (fRec1[0] + 1.0f))));
			int iTemp10 = int(fTemp9);
			float fTemp11 = floorf(fTemp9);
			fRec3[0] = ((fVec2[((IOTA - min(2049, max(0, iTemp10))) & 4095)] * (fTemp11 + (1.0f - fTemp9))) + ((fTemp9 - fTemp11) * fVec2[((IOTA - min(2049, max(0, (iTemp10 + 1)))) & 4095)]));
			output1[i] = FAUSTFLOAT((iSlow0?fTemp6:(0.5f * (fTemp7 + (fSlow7 * fRec3[0])))));
			iVec0[1] = iVec0[0];
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			IOTA = (IOTA + 1);
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			
		}
		
	}

	
};

#endif
