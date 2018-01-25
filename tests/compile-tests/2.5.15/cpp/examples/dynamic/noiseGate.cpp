/* ------------------------------------------------------------
author: "JOS, revised by RM"
name: "noiseGate"
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
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	float fRec3[2];
	FAUSTFLOAT fHslider2;
	int iVec0[2];
	FAUSTFLOAT fHslider3;
	int iRec4[2];
	float fRec1[2];
	float fRec0[2];
	FAUSTFLOAT fHbargraph0;
	float fRec8[2];
	int iVec1[2];
	int iRec9[2];
	float fRec6[2];
	float fRec5[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "0.0");
		m->declare("author", "JOS, revised by RM");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("description", "Gate demo application.");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("misceffects.lib/name", "Faust Math Library");
		m->declare("misceffects.lib/version", "2.0");
		m->declare("name", "noiseGate");
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
		fConst1 = (1.0f / fConst0);
		fConst2 = (1.0f / fConst0);
		
	}
	
	virtual void instanceResetUserInterface() {
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fHslider0 = FAUSTFLOAT(10.0f);
		fHslider1 = FAUSTFLOAT(100.0f);
		fHslider2 = FAUSTFLOAT(-30.0f);
		fHslider3 = FAUSTFLOAT(200.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec3[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			iVec0[l1] = 0;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			iRec4[l2] = 0;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec1[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec0[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec8[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			iVec1[l6] = 0;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			iRec9[l7] = 0;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec6[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec5[l9] = 0.0f;
			
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
		ui_interface->declare(0, "tooltip", "Reference:   http://en.wikipedia.org/wiki/Noise_gate");
		ui_interface->openVerticalBox("GATE");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fCheckbox0, "0", "");
		ui_interface->declare(&fCheckbox0, "tooltip", "When this is checked,   the gate has no effect");
		ui_interface->addCheckButton("Bypass", &fCheckbox0);
		ui_interface->declare(&fHbargraph0, "1", "");
		ui_interface->declare(&fHbargraph0, "tooltip", "Current gain of the  gate in dB");
		ui_interface->declare(&fHbargraph0, "unit", "dB");
		ui_interface->addHorizontalBargraph("Gate Gain", &fHbargraph0, -50.0f, 10.0f);
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fHslider2, "1", "");
		ui_interface->declare(&fHslider2, "style", "knob");
		ui_interface->declare(&fHslider2, "tooltip", "When   the signal level falls below the Threshold (expressed in dB), the signal is   muted");
		ui_interface->declare(&fHslider2, "unit", "dB");
		ui_interface->addHorizontalSlider("Threshold", &fHslider2, -30.0f, -120.0f, 0.0f, 0.100000001f);
		ui_interface->declare(&fHslider0, "2", "");
		ui_interface->declare(&fHslider0, "scale", "log");
		ui_interface->declare(&fHslider0, "style", "knob");
		ui_interface->declare(&fHslider0, "tooltip", "Time constant in MICROseconds (1/e smoothing time) for the gate  gain to go (exponentially) from 0 (muted) to 1 (unmuted)");
		ui_interface->declare(&fHslider0, "unit", "us");
		ui_interface->addHorizontalSlider("Attack", &fHslider0, 10.0f, 10.0f, 10000.0f, 1.0f);
		ui_interface->declare(&fHslider3, "3", "");
		ui_interface->declare(&fHslider3, "scale", "log");
		ui_interface->declare(&fHslider3, "style", "knob");
		ui_interface->declare(&fHslider3, "tooltip", "Time in ms to keep the gate open (no muting) after the signal  level falls below the Threshold");
		ui_interface->declare(&fHslider3, "unit", "ms");
		ui_interface->addHorizontalSlider("Hold", &fHslider3, 200.0f, 1.0f, 1000.0f, 1.0f);
		ui_interface->declare(&fHslider1, "4", "");
		ui_interface->declare(&fHslider1, "scale", "log");
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->declare(&fHslider1, "tooltip", "Time constant in ms (1/e smoothing time) for the gain to go  (exponentially) from 1 (unmuted) to 0 (muted)");
		ui_interface->declare(&fHslider1, "unit", "ms");
		ui_interface->addHorizontalSlider("Release", &fHslider1, 100.0f, 1.0f, 1000.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		int iSlow0 = int(float(fCheckbox0));
		float fSlow1 = max(fConst2, (9.99999997e-07f * float(fHslider0)));
		float fSlow2 = max(fConst2, (0.00100000005f * float(fHslider1)));
		float fSlow3 = expf((0.0f - (fConst1 / min(fSlow1, fSlow2))));
		float fSlow4 = (1.0f - fSlow3);
		float fSlow5 = powf(10.0f, (0.0500000007f * float(fHslider2)));
		int iSlow6 = int((fConst0 * max(fConst2, (0.00100000005f * float(fHslider3)))));
		float fSlow7 = expf((0.0f - (fConst1 / fSlow1)));
		float fSlow8 = expf((0.0f - (fConst1 / fSlow2)));
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input0[i]);
			float fTemp1 = (iSlow0?0.0f:fTemp0);
			float fTemp2 = float(input1[i]);
			float fTemp3 = (iSlow0?0.0f:fTemp2);
			float fTemp4 = fabsf(fTemp3);
			fRec3[0] = ((fSlow3 * fRec3[1]) + (fSlow4 * fabsf((fabsf(fTemp1) + fTemp4))));
			float fRec2 = fRec3[0];
			int iTemp5 = (fRec2 > fSlow5);
			iVec0[0] = iTemp5;
			iRec4[0] = max(int((iSlow6 * (iTemp5 < iVec0[1]))), int((iRec4[1] + -1)));
			float fTemp6 = fabsf(max(float(iTemp5), float((iRec4[0] > 0))));
			float fTemp7 = ((fRec0[1] > fTemp6)?fSlow8:fSlow7);
			fRec1[0] = ((fRec1[1] * fTemp7) + (fTemp6 * (1.0f - fTemp7)));
			fRec0[0] = fRec1[0];
			fHbargraph0 = FAUSTFLOAT((20.0f * log10f(fRec0[0])));
			fRec8[0] = ((fSlow3 * fRec8[1]) + (fSlow4 * fabsf((fTemp4 + fabsf(fTemp1)))));
			float fRec7 = fRec8[0];
			int iTemp8 = (fRec7 > fSlow5);
			iVec1[0] = iTemp8;
			iRec9[0] = max(int((iSlow6 * (iTemp8 < iVec1[1]))), int((iRec9[1] + -1)));
			float fTemp9 = fabsf(max(float(iTemp8), float((iRec9[0] > 0))));
			float fTemp10 = ((fRec5[1] > fTemp9)?fSlow8:fSlow7);
			fRec6[0] = ((fRec6[1] * fTemp10) + (fTemp9 * (1.0f - fTemp10)));
			fRec5[0] = fRec6[0];
			output0[i] = FAUSTFLOAT((iSlow0?fTemp0:(fTemp1 * fRec5[0])));
			output1[i] = FAUSTFLOAT((iSlow0?fTemp2:(fTemp3 * fRec5[0])));
			fRec3[1] = fRec3[0];
			iVec0[1] = iVec0[0];
			iRec4[1] = iRec4[0];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
			fRec8[1] = fRec8[0];
			iVec1[1] = iVec1[0];
			iRec9[1] = iRec9[0];
			fRec6[1] = fRec6[0];
			fRec5[1] = fRec5[0];
			
		}
		
	}

	
};

#endif
