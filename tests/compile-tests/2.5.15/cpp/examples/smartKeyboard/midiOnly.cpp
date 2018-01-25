/* ------------------------------------------------------------
name: "midiOnly"
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
	
	int iVec0[2];
	int fSamplingFreq;
	float fConst0;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fButton0;
	FAUSTFLOAT fHslider2;
	float fVec1[2];
	float fRec2[2];
	FAUSTFLOAT fHslider3;
	float fRec5[2];
	float fRec3[2];
	float fRec4[2];
	FAUSTFLOAT fHslider4;
	float fRec6[2];
	FAUSTFLOAT fHslider5;
	float fRec7[2];
	float fRec0[2];
	float fRec1[2];
	float fRec8[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("interface", "SmartKeyboard{  'Number of Keyboards':'1',  'Keyboard 0 - Number of Keys':'2',  'Keyboard 0 - Send Freq':'0',  'Keyboard 0 - Piano Keyboard':'0',  'Keyboard 0 - Static Mode':'1',  'Keyboard 0 - Send Key X':'1',  'Keyboard 0 - Key 0 - Label':'Mod Index',  'Keyboard 0 - Key 1 - Label':'Mod Freq' }");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "midiOnly");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("synths.lib/name", "Faust Synthesizer Library");
		m->declare("synths.lib/version", "0.0");
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
		fConst0 = (6.28318548f / min(192000.0f, max(1.0f, float(fSamplingFreq))));
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(300.0f);
		fHslider1 = FAUSTFLOAT(1.0f);
		fButton0 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(0.0f);
		fHslider3 = FAUSTFLOAT(0.5f);
		fHslider4 = FAUSTFLOAT(0.5f);
		fHslider5 = FAUSTFLOAT(1.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fVec1[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec2[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec5[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec3[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec4[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec6[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec7[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec0[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec1[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec8[l10] = 0.0f;
			
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
		ui_interface->openVerticalBox("midiOnly");
		ui_interface->declare(&fHslider1, "midi", "pitchwheel");
		ui_interface->addHorizontalSlider("bend", &fHslider1, 1.0f, 0.0f, 10.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("freq", &fHslider0, 300.0f, 50.0f, 2000.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("gain", &fHslider5, 1.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addButton("gate", &fButton0);
		ui_interface->declare(&fHslider4, "midi", "ctrl 1");
		ui_interface->addHorizontalSlider("kb0k0x", &fHslider4, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fHslider3, "midi", "ctrl 1");
		ui_interface->addHorizontalSlider("kb0k1x", &fHslider3, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fHslider2, "midi", "ctrl 64");
		ui_interface->addHorizontalSlider("sustain", &fHslider2, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = float(fHslider0);
		float fSlow1 = float(fHslider1);
		float fSlow2 = min(1.0f, (float(fButton0) + float(fHslider2)));
		int iSlow3 = (fSlow2 == 0.0f);
		float fSlow4 = (fConst0 * fSlow0);
		float fSlow5 = (0.00100000005f * float(fHslider3));
		float fSlow6 = (0.00100000005f * float(fHslider4));
		float fSlow7 = (0.00100000005f * (fSlow2 * float(fHslider5)));
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			fVec1[0] = fSlow2;
			int iTemp0 = ((fSlow2 == fVec1[1]) | iSlow3);
			fRec2[0] = ((fSlow1 * (1.0f - (0.999000013f * float(iTemp0)))) + (0.999000013f * (float(iTemp0) * fRec2[1])));
			fRec5[0] = (fSlow5 + (0.999000013f * fRec5[1]));
			float fTemp1 = (fSlow4 * (fRec2[0] * (fRec5[0] + 1.0f)));
			float fTemp2 = sinf(fTemp1);
			float fTemp3 = cosf(fTemp1);
			fRec3[0] = ((fRec4[1] * fTemp2) + (fRec3[1] * fTemp3));
			int iTemp4 = (1 - iVec0[1]);
			fRec4[0] = (((fRec4[1] * fTemp3) + (fRec3[1] * (0.0f - fTemp2))) + float(iTemp4));
			fRec6[0] = (fSlow6 + (0.999000013f * fRec6[1]));
			fRec7[0] = (fSlow7 + (0.999000013f * fRec7[1]));
			float fTemp5 = (fConst0 * ((fSlow0 * fRec2[0]) + (1000.0f * ((fRec3[0] * fRec6[0]) * fRec7[0]))));
			float fTemp6 = sinf(fTemp5);
			float fTemp7 = cosf(fTemp5);
			fRec0[0] = ((fRec1[1] * fTemp6) + (fRec0[1] * fTemp7));
			fRec1[0] = (((fRec1[1] * fTemp7) + (fRec0[1] * (0.0f - fTemp6))) + float(iTemp4));
			fRec8[0] = (fSlow7 + (0.999000013f * fRec8[1]));
			float fTemp8 = (fRec0[0] * fRec8[0]);
			output0[i] = FAUSTFLOAT(fTemp8);
			output1[i] = FAUSTFLOAT(fTemp8);
			iVec0[1] = iVec0[0];
			fVec1[1] = fVec1[0];
			fRec2[1] = fRec2[0];
			fRec5[1] = fRec5[0];
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec6[1] = fRec6[0];
			fRec7[1] = fRec7[0];
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			fRec8[1] = fRec8[0];
			
		}
		
	}

	
};

#endif
