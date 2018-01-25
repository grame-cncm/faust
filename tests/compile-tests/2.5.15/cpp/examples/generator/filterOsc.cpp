/* ------------------------------------------------------------
author: "JOS, revised by RM"
name: "filterOSC"
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
	
	FAUSTFLOAT fHslider0;
	int iVec0[2];
	float fRec0[2];
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider1;
	float fConst2;
	FAUSTFLOAT fHslider2;
	float fRec3[2];
	float fRec1[2];
	float fRec2[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("author", "JOS, revised by RM");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("description", "Simple application demoing filter based oscillators.");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "filterOSC");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("version", "0.0");
	}

	virtual int getNumInputs() {
		return 0;
		
	}
	virtual int getNumOutputs() {
		return 1;
		
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
		fConst2 = (1.0f / fConst0);
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(-20.0f);
		fHslider1 = FAUSTFLOAT(49.0f);
		fHslider2 = FAUSTFLOAT(0.10000000000000001f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec0[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec3[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec1[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec2[l4] = 0.0f;
			
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
		ui_interface->declare(0, "0", "");
		ui_interface->declare(0, "tooltip", "Sine oscillator based   on 2D vector rotation");
		ui_interface->openVerticalBox("SINE WAVE OSCILLATOR oscrs");
		ui_interface->declare(&fHslider0, "1", "");
		ui_interface->declare(&fHslider0, "tooltip", "Sawtooth waveform   amplitude");
		ui_interface->declare(&fHslider0, "unit", "dB");
		ui_interface->addHorizontalSlider("Amplitude", &fHslider0, -20.0f, -120.0f, 10.0f, 0.100000001f);
		ui_interface->declare(&fHslider1, "2", "");
		ui_interface->declare(&fHslider1, "tooltip", "Sine wave frequency as a Piano Key (PK) number (A440 = 49 PK)");
		ui_interface->declare(&fHslider1, "unit", "PK");
		ui_interface->addHorizontalSlider("Frequency", &fHslider1, 49.0f, 1.0f, 88.0f, 0.00999999978f);
		ui_interface->declare(&fHslider2, "3", "");
		ui_interface->declare(&fHslider2, "scale", "log");
		ui_interface->declare(&fHslider2, "tooltip", "Portamento (frequency-glide) time-constant in seconds");
		ui_interface->declare(&fHslider2, "unit", "sec");
		ui_interface->addHorizontalSlider("Portamento", &fHslider2, 0.100000001f, 0.00100000005f, 10.0f, 0.00100000005f);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = (0.00100000005f * powf(10.0f, (0.0500000007f * float(fHslider0))));
		float fSlow1 = expf((0.0f - (fConst2 / float(fHslider2))));
		float fSlow2 = (440.0f * (powf(2.0f, (0.0833333358f * (float(fHslider1) + -49.0f))) * (1.0f - fSlow1)));
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			fRec0[0] = (fSlow0 + (0.999000013f * fRec0[1]));
			fRec3[0] = (fSlow2 + (fSlow1 * fRec3[1]));
			float fTemp0 = (fConst1 * fRec3[0]);
			float fTemp1 = sinf(fTemp0);
			float fTemp2 = cosf(fTemp0);
			fRec1[0] = ((fRec2[1] * fTemp1) + (fRec1[1] * fTemp2));
			fRec2[0] = (((fRec2[1] * fTemp2) + (fRec1[1] * (0.0f - fTemp1))) + float((1 - iVec0[1])));
			output0[i] = FAUSTFLOAT((fRec0[0] * fRec1[0]));
			iVec0[1] = iVec0[0];
			fRec0[1] = fRec0[0];
			fRec3[1] = fRec3[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			
		}
		
	}

	
};

#endif
