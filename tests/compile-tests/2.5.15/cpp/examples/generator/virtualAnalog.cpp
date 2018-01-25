/* ------------------------------------------------------------
author: "JOS, revised by RM"
name: "VirtualAnalog"
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

float mydsp_faustpower2_f(float value) {
	return (value * value);
	
}
float mydsp_faustpower3_f(float value) {
	return ((value * value) * value);
	
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif
#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class mydsp : public dsp {
	
 private:
	
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT fHslider0;
	int iVec0[4];
	float fRec0[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fEntry0;
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fVslider2;
	float fRec2[2];
	float fVec1[2];
	float fRec1[2];
	float fConst2;
	float fVec2[2];
	float fConst3;
	float fVec3[2];
	float fVec4[2];
	float fConst4;
	float fVec5[2];
	float fVec6[2];
	float fVec7[2];
	FAUSTFLOAT fVslider3;
	float fVec8[2];
	float fRec3[2];
	float fVec9[2];
	float fVec10[2];
	float fVec11[2];
	float fVec12[2];
	float fVec13[2];
	float fVec14[2];
	FAUSTFLOAT fVslider4;
	float fVec15[2];
	float fRec4[2];
	float fVec16[2];
	float fVec17[2];
	float fVec18[2];
	float fVec19[2];
	float fVec20[2];
	float fVec21[2];
	float fConst5;
	FAUSTFLOAT fVslider5;
	float fVec22[2];
	float fRec5[2];
	float fVec23[2];
	int IOTA;
	float fVec24[4096];
	float fConst6;
	float fVec25[2];
	float fRec6[2];
	float fVec26[2];
	float fVec27[4096];
	float fVec28[2];
	float fRec7[2];
	float fVec29[2];
	float fVec30[4096];
	float fConst7;
	FAUSTFLOAT fVslider6;
	float fRec8[2];
	float fRec9[2];
	float fRec10[2];
	FAUSTFLOAT fVslider7;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fVslider8;
	float fRec11[2];
	float fConst8;
	float fVec31[2];
	float fVec32[2];
	float fVec33[4096];
	float fVec34[2];
	float fVec35[2];
	float fVec36[4096];
	float fVec37[2];
	float fVec38[2];
	float fVec39[4096];
	FAUSTFLOAT fVslider9;
	int iRec13[2];
	float fRec12[4];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("author", "JOS, revised by RM");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("description", "Virtual analog oscillator demo application.");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "VirtualAnalog");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("version", "0.0");
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
		fConst1 = (1.0f / fConst0);
		fConst2 = (0.25f * fConst0);
		fConst3 = (0.0416666679f * mydsp_faustpower2_f(fConst0));
		fConst4 = (0.00520833349f * mydsp_faustpower3_f(fConst0));
		fConst5 = (0.0833333358f * fConst0);
		fConst6 = (0.5f * fConst0);
		fConst7 = (1.33333337f / fConst0);
		fConst8 = (0.013888889f * fConst0);
		
	}
	
	virtual void instanceResetUserInterface() {
		fVslider0 = FAUSTFLOAT(0.0f);
		fHslider0 = FAUSTFLOAT(-20.0f);
		fVslider1 = FAUSTFLOAT(1.0f);
		fEntry0 = FAUSTFLOAT(2.0f);
		fHslider1 = FAUSTFLOAT(49.0f);
		fVslider2 = FAUSTFLOAT(0.10000000000000001f);
		fVslider3 = FAUSTFLOAT(-0.10000000000000001f);
		fVslider4 = FAUSTFLOAT(0.10000000000000001f);
		fVslider5 = FAUSTFLOAT(0.0f);
		fVslider6 = FAUSTFLOAT(0.0f);
		fVslider7 = FAUSTFLOAT(0.0f);
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fVslider8 = FAUSTFLOAT(0.5f);
		fVslider9 = FAUSTFLOAT(0.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 4); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec0[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec2[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fVec1[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec1[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fVec2[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fVec3[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fVec4[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fVec5[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fVec6[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fVec7[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fVec8[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec3[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fVec9[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fVec10[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fVec11[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fVec12[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fVec13[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fVec14[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fVec15[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec4[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fVec16[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fVec17[l22] = 0.0f;
			
		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fVec18[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fVec19[l24] = 0.0f;
			
		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fVec20[l25] = 0.0f;
			
		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fVec21[l26] = 0.0f;
			
		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fVec22[l27] = 0.0f;
			
		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fRec5[l28] = 0.0f;
			
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fVec23[l29] = 0.0f;
			
		}
		IOTA = 0;
		for (int l30 = 0; (l30 < 4096); l30 = (l30 + 1)) {
			fVec24[l30] = 0.0f;
			
		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			fVec25[l31] = 0.0f;
			
		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fRec6[l32] = 0.0f;
			
		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fVec26[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 4096); l34 = (l34 + 1)) {
			fVec27[l34] = 0.0f;
			
		}
		for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			fVec28[l35] = 0.0f;
			
		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			fRec7[l36] = 0.0f;
			
		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fVec29[l37] = 0.0f;
			
		}
		for (int l38 = 0; (l38 < 4096); l38 = (l38 + 1)) {
			fVec30[l38] = 0.0f;
			
		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fRec8[l39] = 0.0f;
			
		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			fRec9[l40] = 0.0f;
			
		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fRec10[l41] = 0.0f;
			
		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			fRec11[l42] = 0.0f;
			
		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			fVec31[l43] = 0.0f;
			
		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fVec32[l44] = 0.0f;
			
		}
		for (int l45 = 0; (l45 < 4096); l45 = (l45 + 1)) {
			fVec33[l45] = 0.0f;
			
		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			fVec34[l46] = 0.0f;
			
		}
		for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			fVec35[l47] = 0.0f;
			
		}
		for (int l48 = 0; (l48 < 4096); l48 = (l48 + 1)) {
			fVec36[l48] = 0.0f;
			
		}
		for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			fVec37[l49] = 0.0f;
			
		}
		for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			fVec38[l50] = 0.0f;
			
		}
		for (int l51 = 0; (l51 < 4096); l51 = (l51 + 1)) {
			fVec39[l51] = 0.0f;
			
		}
		for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			iRec13[l52] = 0;
			
		}
		for (int l53 = 0; (l53 < 4); l53 = (l53 + 1)) {
			fRec12[l53] = 0.0f;
			
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
		ui_interface->declare(0, "tooltip", "See Faust's oscillators.lib for documentation and references");
		ui_interface->openVerticalBox("VIRTUAL ANALOG OSCILLATORS");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("Signal Levels");
		ui_interface->declare(&fVslider1, "0", "");
		ui_interface->declare(&fVslider1, "style", "vslider");
		ui_interface->addVerticalSlider("Sawtooth", &fVslider1, 1.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(0, "1", "");
		ui_interface->openVerticalBox("Pulse Train");
		ui_interface->declare(&fCheckbox0, "0", "");
		ui_interface->declare(&fCheckbox0, "tooltip", "When checked, use 3rd-order aliasing suppression (up from 2)  See if you can hear a difference with the freq high and swept");
		ui_interface->addCheckButton("Order 3", &fCheckbox0);
		ui_interface->declare(&fVslider7, "1", "");
		ui_interface->declare(&fVslider7, "style", "vslider");
		ui_interface->addVerticalSlider("0x00", &fVslider7, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fVslider8, "2", "");
		ui_interface->declare(&fVslider8, "style", "knob");
		ui_interface->addVerticalSlider("Duty Cycle", &fVslider8, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
		ui_interface->declare(&fVslider5, "2", "");
		ui_interface->declare(&fVslider5, "style", "vslider");
		ui_interface->addVerticalSlider("Square", &fVslider5, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fVslider6, "3", "");
		ui_interface->declare(&fVslider6, "style", "vslider");
		ui_interface->addVerticalSlider("Triangle", &fVslider6, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fVslider9, "4", "");
		ui_interface->declare(&fVslider9, "style", "vslider");
		ui_interface->declare(&fVslider9, "tooltip", "Pink Noise (or 1/f noise) is   Constant-Q Noise, meaning that it has the same total power in every octave   (uses only amplitude controls)");
		ui_interface->addVerticalSlider("Pink Noise", &fVslider9, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fVslider0, "5", "");
		ui_interface->declare(&fVslider0, "style", "vslider");
		ui_interface->addVerticalSlider("Ext Input", &fVslider0, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("Signal Parameters");
		ui_interface->declare(0, "0", "");
		ui_interface->openVerticalBox("0x00");
		ui_interface->declare(&fHslider0, "1", "");
		ui_interface->declare(&fHslider0, "style", "hslider");
		ui_interface->declare(&fHslider0, "tooltip", "Sawtooth waveform amplitude");
		ui_interface->declare(&fHslider0, "unit", "dB");
		ui_interface->addHorizontalSlider("Mix Amplitude", &fHslider0, -20.0f, -120.0f, 10.0f, 0.100000001f);
		ui_interface->declare(&fHslider1, "2", "");
		ui_interface->declare(&fHslider1, "style", "hslider");
		ui_interface->declare(&fHslider1, "tooltip", "Sawtooth   frequency as a Piano Key (PK) number (A440 = key 49)");
		ui_interface->declare(&fHslider1, "unit", "PK");
		ui_interface->addHorizontalSlider("Frequency", &fHslider1, 49.0f, 1.0f, 88.0f, 0.00999999978f);
		ui_interface->closeBox();
		ui_interface->declare(&fVslider3, "3", "");
		ui_interface->declare(&fVslider3, "style", "knob");
		ui_interface->declare(&fVslider3, "tooltip", "Percentange frequency-shift up or down for second oscillator");
		ui_interface->declare(&fVslider3, "unit", "%%");
		ui_interface->addVerticalSlider("Detuning 1", &fVslider3, -0.100000001f, -10.0f, 10.0f, 0.00999999978f);
		ui_interface->declare(&fVslider4, "4", "");
		ui_interface->declare(&fVslider4, "style", "knob");
		ui_interface->declare(&fVslider4, "tooltip", "Percentange frequency-shift up or down for third detuned oscillator");
		ui_interface->declare(&fVslider4, "unit", "%%");
		ui_interface->addVerticalSlider("Detuning 2", &fVslider4, 0.100000001f, -10.0f, 10.0f, 0.00999999978f);
		ui_interface->declare(&fVslider2, "5", "");
		ui_interface->declare(&fVslider2, "scale", "log");
		ui_interface->declare(&fVslider2, "style", "knob");
		ui_interface->declare(&fVslider2, "tooltip", "Portamento (frequency-glide) time-constant in seconds");
		ui_interface->declare(&fVslider2, "unit", "sec");
		ui_interface->addVerticalSlider("Portamento", &fVslider2, 0.100000001f, 0.00100000005f, 10.0f, 0.00100000005f);
		ui_interface->declare(&fEntry0, "6", "");
		ui_interface->declare(&fEntry0, "tooltip", "Order of sawtooth aliasing  suppression");
		ui_interface->addNumEntry("Saw Order", &fEntry0, 2.0f, 1.0f, 4.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = float(fVslider0);
		float fSlow1 = (0.00100000005f * powf(10.0f, (0.0500000007f * float(fHslider0))));
		float fSlow2 = (0.333333343f * float(fVslider1));
		int iSlow3 = int((float(fEntry0) + -1.0f));
		int iSlow4 = (iSlow3 >= 2);
		int iSlow5 = (iSlow3 >= 1);
		float fSlow6 = expf((0.0f - (fConst1 / float(fVslider2))));
		float fSlow7 = (440.0f * (powf(2.0f, (0.0833333358f * (float(fHslider1) + -49.0f))) * (1.0f - fSlow6)));
		int iSlow8 = (iSlow3 >= 3);
		float fSlow9 = (1.0f - (0.00999999978f * float(fVslider3)));
		float fSlow10 = ((0.00999999978f * float(fVslider4)) + 1.0f);
		float fSlow11 = (fConst5 * float(fVslider5));
		float fSlow12 = (fConst7 * float(fVslider6));
		float fSlow13 = (fConst0 * float(fVslider7));
		float fSlow14 = float(fCheckbox0);
		float fSlow15 = (0.0833333358f * (1.0f - fSlow14));
		float fSlow16 = (0.00999999978f * float(fVslider8));
		float fSlow17 = (fConst8 * fSlow14);
		float fSlow18 = float(fVslider9);
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			fRec0[0] = (fSlow1 + (0.999000013f * fRec0[1]));
			fRec2[0] = (fSlow7 + (fSlow6 * fRec2[1]));
			float fTemp0 = max(20.0f, fabsf(fRec2[0]));
			fVec1[0] = fTemp0;
			float fTemp1 = (fRec1[1] + (fConst1 * fVec1[1]));
			fRec1[0] = (fTemp1 - floorf(fTemp1));
			float fTemp2 = (2.0f * fRec1[0]);
			float fTemp3 = (fTemp2 + -1.0f);
			float fTemp4 = mydsp_faustpower2_f(fTemp3);
			fVec2[0] = fTemp4;
			float fTemp5 = mydsp_faustpower3_f(fTemp3);
			fVec3[0] = (fTemp5 + (1.0f - fTemp2));
			float fTemp6 = ((fTemp5 + (1.0f - (fTemp2 + fVec3[1]))) / fTemp0);
			fVec4[0] = fTemp6;
			float fTemp7 = (fTemp4 * (fTemp4 + -2.0f));
			fVec5[0] = fTemp7;
			float fTemp8 = ((fTemp7 - fVec5[1]) / fTemp0);
			fVec6[0] = fTemp8;
			float fTemp9 = ((fTemp8 - fVec6[1]) / fTemp0);
			fVec7[0] = fTemp9;
			float fTemp10 = (fSlow9 * fRec2[0]);
			float fTemp11 = max(20.0f, fabsf(fTemp10));
			fVec8[0] = fTemp11;
			float fTemp12 = (fRec3[1] + (fConst1 * fVec8[1]));
			fRec3[0] = (fTemp12 - floorf(fTemp12));
			float fTemp13 = (2.0f * fRec3[0]);
			float fTemp14 = (fTemp13 + -1.0f);
			float fTemp15 = mydsp_faustpower2_f(fTemp14);
			fVec9[0] = fTemp15;
			float fTemp16 = mydsp_faustpower3_f(fTemp14);
			fVec10[0] = (fTemp16 + (1.0f - fTemp13));
			float fTemp17 = ((fTemp16 + (1.0f - (fTemp13 + fVec10[1]))) / fTemp11);
			fVec11[0] = fTemp17;
			float fTemp18 = (fTemp15 * (fTemp15 + -2.0f));
			fVec12[0] = fTemp18;
			float fTemp19 = ((fTemp18 - fVec12[1]) / fTemp11);
			fVec13[0] = fTemp19;
			float fTemp20 = ((fTemp19 - fVec13[1]) / fTemp11);
			fVec14[0] = fTemp20;
			float fTemp21 = (fSlow10 * fRec2[0]);
			float fTemp22 = max(20.0f, fabsf(fTemp21));
			fVec15[0] = fTemp22;
			float fTemp23 = (fRec4[1] + (fConst1 * fVec15[1]));
			fRec4[0] = (fTemp23 - floorf(fTemp23));
			float fTemp24 = (2.0f * fRec4[0]);
			float fTemp25 = (fTemp24 + -1.0f);
			float fTemp26 = mydsp_faustpower2_f(fTemp25);
			fVec16[0] = fTemp26;
			float fTemp27 = mydsp_faustpower3_f(fTemp25);
			fVec17[0] = (fTemp27 + (1.0f - fTemp24));
			float fTemp28 = ((fTemp27 + (1.0f - (fTemp24 + fVec17[1]))) / fTemp22);
			fVec18[0] = fTemp28;
			float fTemp29 = (fTemp26 * (fTemp26 + -2.0f));
			fVec19[0] = fTemp29;
			float fTemp30 = ((fTemp29 - fVec19[1]) / fTemp22);
			fVec20[0] = fTemp30;
			float fTemp31 = ((fTemp30 - fVec20[1]) / fTemp22);
			fVec21[0] = fTemp31;
			float fTemp32 = max(fRec2[0], 23.4489498f);
			float fTemp33 = max(20.0f, fabsf(fTemp32));
			fVec22[0] = fTemp33;
			float fTemp34 = (fRec5[1] + (fConst1 * fVec22[1]));
			fRec5[0] = (fTemp34 - floorf(fTemp34));
			float fTemp35 = (2.0f * fRec5[0]);
			float fTemp36 = (fTemp35 + -1.0f);
			float fTemp37 = mydsp_faustpower2_f(fTemp36);
			fVec23[0] = fTemp37;
			float fTemp38 = ((float(iVec0[1]) * (fTemp37 - fVec23[1])) / fTemp33);
			fVec24[(IOTA & 4095)] = fTemp38;
			float fTemp39 = max(0.0f, min(2047.0f, (fConst6 / fTemp32)));
			int iTemp40 = int(fTemp39);
			float fTemp41 = floorf(fTemp39);
			float fTemp42 = ((fTemp38 - (fVec24[((IOTA - iTemp40) & 4095)] * (fTemp41 + (1.0f - fTemp39)))) - ((fTemp39 - fTemp41) * fVec24[((IOTA - (iTemp40 + 1)) & 4095)]));
			float fTemp43 = max(fTemp10, 23.4489498f);
			float fTemp44 = max(20.0f, fabsf(fTemp43));
			fVec25[0] = fTemp44;
			float fTemp45 = (fRec6[1] + (fConst1 * fVec25[1]));
			fRec6[0] = (fTemp45 - floorf(fTemp45));
			float fTemp46 = (2.0f * fRec6[0]);
			float fTemp47 = (fTemp46 + -1.0f);
			float fTemp48 = mydsp_faustpower2_f(fTemp47);
			fVec26[0] = fTemp48;
			float fTemp49 = ((float(iVec0[1]) * (fTemp48 - fVec26[1])) / fTemp44);
			fVec27[(IOTA & 4095)] = fTemp49;
			float fTemp50 = max(0.0f, min(2047.0f, (fConst6 / fTemp43)));
			int iTemp51 = int(fTemp50);
			float fTemp52 = floorf(fTemp50);
			float fTemp53 = ((fTemp49 - (fVec27[((IOTA - iTemp51) & 4095)] * (fTemp52 + (1.0f - fTemp50)))) - ((fTemp50 - fTemp52) * fVec27[((IOTA - (iTemp51 + 1)) & 4095)]));
			float fTemp54 = max(fTemp21, 23.4489498f);
			float fTemp55 = max(20.0f, fabsf(fTemp54));
			fVec28[0] = fTemp55;
			float fTemp56 = (fRec7[1] + (fConst1 * fVec28[1]));
			fRec7[0] = (fTemp56 - floorf(fTemp56));
			float fTemp57 = (2.0f * fRec7[0]);
			float fTemp58 = (fTemp57 + -1.0f);
			float fTemp59 = mydsp_faustpower2_f(fTemp58);
			fVec29[0] = fTemp59;
			float fTemp60 = ((float(iVec0[1]) * (fTemp59 - fVec29[1])) / fTemp55);
			fVec30[(IOTA & 4095)] = fTemp60;
			float fTemp61 = max(0.0f, min(2047.0f, (fConst6 / fTemp54)));
			int iTemp62 = int(fTemp61);
			float fTemp63 = floorf(fTemp61);
			float fTemp64 = ((fTemp60 - (fVec30[((IOTA - iTemp62) & 4095)] * (fTemp63 + (1.0f - fTemp61)))) - ((fTemp61 - fTemp63) * fVec30[((IOTA - (iTemp62 + 1)) & 4095)]));
			fRec8[0] = ((fConst2 * fTemp42) + (0.999000013f * fRec8[1]));
			fRec9[0] = ((fConst2 * fTemp53) + (0.999000013f * fRec9[1]));
			fRec10[0] = ((fConst2 * fTemp64) + (0.999000013f * fRec10[1]));
			fRec11[0] = (fSlow16 + (0.99000001f * fRec11[1]));
			float fTemp65 = max(0.0f, min(2047.0f, (fConst0 * (fRec11[0] / fTemp32))));
			float fTemp66 = floorf(fTemp65);
			float fTemp67 = (fTemp66 + (1.0f - fTemp65));
			int iTemp68 = int(fTemp65);
			float fTemp69 = (fTemp65 - fTemp66);
			int iTemp70 = (iTemp68 + 1);
			float fTemp71 = max(0.0f, min(2047.0f, (fConst0 * (fRec11[0] / fTemp43))));
			float fTemp72 = floorf(fTemp71);
			float fTemp73 = (fTemp72 + (1.0f - fTemp71));
			int iTemp74 = int(fTemp71);
			float fTemp75 = (fTemp71 - fTemp72);
			int iTemp76 = (iTemp74 + 1);
			float fTemp77 = max(0.0f, min(2047.0f, (fConst0 * (fRec11[0] / fTemp54))));
			float fTemp78 = floorf(fTemp77);
			float fTemp79 = (fTemp78 + (1.0f - fTemp77));
			int iTemp80 = int(fTemp77);
			float fTemp81 = (fTemp77 - fTemp78);
			int iTemp82 = (iTemp80 + 1);
			float fTemp83 = mydsp_faustpower3_f(fTemp36);
			fVec31[0] = (fTemp83 + (1.0f - fTemp35));
			float fTemp84 = ((fTemp83 + (1.0f - (fTemp35 + fVec31[1]))) / fTemp33);
			fVec32[0] = fTemp84;
			float fTemp85 = ((float(iVec0[2]) * (fTemp84 - fVec32[1])) / fTemp33);
			fVec33[(IOTA & 4095)] = fTemp85;
			float fTemp86 = mydsp_faustpower3_f(fTemp47);
			fVec34[0] = (fTemp86 + (1.0f - fTemp46));
			float fTemp87 = ((fTemp86 + (1.0f - (fTemp46 + fVec34[1]))) / fTemp44);
			fVec35[0] = fTemp87;
			float fTemp88 = ((float(iVec0[2]) * (fTemp87 - fVec35[1])) / fTemp44);
			fVec36[(IOTA & 4095)] = fTemp88;
			float fTemp89 = mydsp_faustpower3_f(fTemp58);
			fVec37[0] = (fTemp89 + (1.0f - fTemp57));
			float fTemp90 = ((fTemp89 + (1.0f - (fTemp57 + fVec37[1]))) / fTemp55);
			fVec38[0] = fTemp90;
			float fTemp91 = ((float(iVec0[2]) * (fTemp90 - fVec38[1])) / fTemp55);
			fVec39[(IOTA & 4095)] = fTemp91;
			iRec13[0] = ((1103515245 * iRec13[1]) + 12345);
			fRec12[0] = (((0.522189379f * fRec12[3]) + ((4.65661287e-10f * float(iRec13[0])) + (2.49495602f * fRec12[1]))) - (2.0172658f * fRec12[2]));
			output0[i] = FAUSTFLOAT(((fSlow0 * float(input0[i])) + (fRec0[0] * (((((fSlow2 * (((iSlow4?(iSlow8?(fConst4 * ((float(iVec0[3]) * (fTemp9 - fVec7[1])) / fTemp0)):(fConst3 * ((float(iVec0[2]) * (fTemp6 - fVec4[1])) / fTemp0))):(iSlow5?(fConst2 * ((float(iVec0[1]) * (fTemp4 - fVec2[1])) / fTemp0)):fTemp3)) + (iSlow4?(iSlow8?(fConst4 * ((float(iVec0[3]) * (fTemp20 - fVec14[1])) / fTemp11)):(fConst3 * ((float(iVec0[2]) * (fTemp17 - fVec11[1])) / fTemp11))):(iSlow5?(fConst2 * ((float(iVec0[1]) * (fTemp15 - fVec9[1])) / fTemp11)):fTemp14))) + (iSlow4?(iSlow8?(fConst4 * ((float(iVec0[3]) * (fTemp31 - fVec21[1])) / fTemp22)):(fConst3 * ((float(iVec0[2]) * (fTemp28 - fVec18[1])) / fTemp22))):(iSlow5?(fConst2 * ((float(iVec0[1]) * (fTemp26 - fVec16[1])) / fTemp22)):fTemp25)))) + (fSlow11 * ((fTemp42 + fTemp53) + fTemp64))) + (fSlow12 * (fRec2[0] * ((fRec8[0] + (fSlow9 * fRec9[0])) + (fSlow10 * fRec10[0]))))) + (fSlow13 * ((fSlow15 * ((((fTemp38 - (fTemp67 * fVec24[((IOTA - iTemp68) & 4095)])) - (fTemp69 * fVec24[((IOTA - iTemp70) & 4095)])) + ((fTemp49 - (fTemp73 * fVec27[((IOTA - iTemp74) & 4095)])) - (fTemp75 * fVec27[((IOTA - iTemp76) & 4095)]))) + ((fTemp60 - (fTemp79 * fVec30[((IOTA - iTemp80) & 4095)])) - (fTemp81 * fVec30[((IOTA - iTemp82) & 4095)])))) + (fSlow17 * ((((fTemp85 - (fVec33[((IOTA - iTemp68) & 4095)] * fTemp67)) - (fTemp69 * fVec33[((IOTA - iTemp70) & 4095)])) + ((fTemp88 - (fVec36[((IOTA - iTemp74) & 4095)] * fTemp73)) - (fTemp75 * fVec36[((IOTA - iTemp76) & 4095)]))) + ((fTemp91 - (fVec39[((IOTA - iTemp80) & 4095)] * fTemp79)) - (fTemp81 * fVec39[((IOTA - iTemp82) & 4095)]))))))) + (fSlow18 * (((0.0499220341f * fRec12[0]) + (0.0506126992f * fRec12[2])) - ((0.0959935337f * fRec12[1]) + (0.00440878607f * fRec12[3]))))))));
			for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				iVec0[j0] = iVec0[(j0 - 1)];
				
			}
			fRec0[1] = fRec0[0];
			fRec2[1] = fRec2[0];
			fVec1[1] = fVec1[0];
			fRec1[1] = fRec1[0];
			fVec2[1] = fVec2[0];
			fVec3[1] = fVec3[0];
			fVec4[1] = fVec4[0];
			fVec5[1] = fVec5[0];
			fVec6[1] = fVec6[0];
			fVec7[1] = fVec7[0];
			fVec8[1] = fVec8[0];
			fRec3[1] = fRec3[0];
			fVec9[1] = fVec9[0];
			fVec10[1] = fVec10[0];
			fVec11[1] = fVec11[0];
			fVec12[1] = fVec12[0];
			fVec13[1] = fVec13[0];
			fVec14[1] = fVec14[0];
			fVec15[1] = fVec15[0];
			fRec4[1] = fRec4[0];
			fVec16[1] = fVec16[0];
			fVec17[1] = fVec17[0];
			fVec18[1] = fVec18[0];
			fVec19[1] = fVec19[0];
			fVec20[1] = fVec20[0];
			fVec21[1] = fVec21[0];
			fVec22[1] = fVec22[0];
			fRec5[1] = fRec5[0];
			fVec23[1] = fVec23[0];
			IOTA = (IOTA + 1);
			fVec25[1] = fVec25[0];
			fRec6[1] = fRec6[0];
			fVec26[1] = fVec26[0];
			fVec28[1] = fVec28[0];
			fRec7[1] = fRec7[0];
			fVec29[1] = fVec29[0];
			fRec8[1] = fRec8[0];
			fRec9[1] = fRec9[0];
			fRec10[1] = fRec10[0];
			fRec11[1] = fRec11[0];
			fVec31[1] = fVec31[0];
			fVec32[1] = fVec32[0];
			fVec34[1] = fVec34[0];
			fVec35[1] = fVec35[0];
			fVec37[1] = fVec37[0];
			fVec38[1] = fVec38[0];
			iRec13[1] = iRec13[0];
			for (int j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				fRec12[j1] = fRec12[(j1 - 1)];
				
			}
			
		}
		
	}

	
};

#endif
