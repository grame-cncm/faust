/* ------------------------------------------------------------
author: "JOS, revised by RM"
name: "sawtoothLab"
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
	int iVec0[4];
	float fRec0[2];
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT fEntry0;
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fVslider1;
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
	FAUSTFLOAT fCheckbox2;
	int iRec5[2];
	float fRec6[4];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("author", "JOS, revised by RM");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("description", "An application demonstrating the different sawtooth oscillators of Faust.");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "sawtoothLab");
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
		
	}
	
	virtual void instanceResetUserInterface() {
		fVslider0 = FAUSTFLOAT(-20.0f);
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fCheckbox1 = FAUSTFLOAT(0.0f);
		fEntry0 = FAUSTFLOAT(2.0f);
		fVslider1 = FAUSTFLOAT(49.0f);
		fVslider2 = FAUSTFLOAT(0.10000000000000001f);
		fVslider3 = FAUSTFLOAT(-0.10000000000000001f);
		fVslider4 = FAUSTFLOAT(0.10000000000000001f);
		fCheckbox2 = FAUSTFLOAT(0.0f);
		
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
			iRec5[l27] = 0;
			
		}
		for (int l28 = 0; (l28 < 4); l28 = (l28 + 1)) {
			fRec6[l28] = 0.0f;
			
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
		ui_interface->declare(0, "tooltip", "See Faust's oscillators.lib   for documentation and references");
		ui_interface->openVerticalBox("SAWTOOTH OSCILLATOR");
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fVslider0, "1", "");
		ui_interface->declare(&fVslider0, "style", "knob");
		ui_interface->declare(&fVslider0, "tooltip", "Sawtooth   waveform amplitude");
		ui_interface->declare(&fVslider0, "unit", "dB");
		ui_interface->addVerticalSlider("Amplitude", &fVslider0, -20.0f, -120.0f, 10.0f, 0.100000001f);
		ui_interface->declare(&fVslider1, "2", "");
		ui_interface->declare(&fVslider1, "style", "knob");
		ui_interface->declare(&fVslider1, "tooltip", "Sawtooth   frequency as a Piano Key (PK) number (A440 = key 49)");
		ui_interface->declare(&fVslider1, "unit", "PK");
		ui_interface->addVerticalSlider("Frequency", &fVslider1, 49.0f, 1.0f, 88.0f, 0.00999999978f);
		ui_interface->declare(&fVslider3, "3", "");
		ui_interface->declare(&fVslider3, "style", "knob");
		ui_interface->declare(&fVslider3, "tooltip", "Percentange frequency-shift  up or down for second oscillator");
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
		ui_interface->declare(&fEntry0, "tooltip", "Order of sawtootn aliasing   suppression");
		ui_interface->addNumEntry("Saw Order", &fEntry0, 2.0f, 1.0f, 4.0f, 1.0f);
		ui_interface->declare(0, "7", "");
		ui_interface->openVerticalBox("Alternate Signals");
		ui_interface->declare(&fCheckbox1, "0", "");
		ui_interface->addCheckButton("Noise (White or Pink - uses only Amplitude control on   the left)", &fCheckbox1);
		ui_interface->declare(&fCheckbox2, "1", "");
		ui_interface->declare(&fCheckbox2, "tooltip", "Pink Noise (or 1/f noise) is Constant-Q Noise, meaning that it has the   same total power in every octave");
		ui_interface->addCheckButton("Pink instead of White Noise (also called 1/f Noise)", &fCheckbox2);
		ui_interface->declare(&fCheckbox0, "2", "");
		ui_interface->addCheckButton("External Signal Input (overrides Sawtooth/Noise   selection above)", &fCheckbox0);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = (0.00100000005f * powf(10.0f, (0.0500000007f * float(fVslider0))));
		int iSlow1 = int(float(fCheckbox0));
		int iSlow2 = int(float(fCheckbox1));
		int iSlow3 = int((float(fEntry0) + -1.0f));
		int iSlow4 = (iSlow3 >= 2);
		int iSlow5 = (iSlow3 >= 1);
		float fSlow6 = expf((0.0f - (fConst1 / float(fVslider2))));
		float fSlow7 = (440.0f * (powf(2.0f, (0.0833333358f * (float(fVslider1) + -49.0f))) * (1.0f - fSlow6)));
		int iSlow8 = (iSlow3 >= 3);
		float fSlow9 = ((0.00999999978f * float(fVslider3)) + 1.0f);
		float fSlow10 = ((0.00999999978f * float(fVslider4)) + 1.0f);
		int iSlow11 = int(float(fCheckbox2));
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			fRec0[0] = (fSlow0 + (0.999000013f * fRec0[1]));
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
			float fTemp10 = max(20.0f, fabsf((fSlow9 * fRec2[0])));
			fVec8[0] = fTemp10;
			float fTemp11 = (fRec3[1] + (fConst1 * fVec8[1]));
			fRec3[0] = (fTemp11 - floorf(fTemp11));
			float fTemp12 = (2.0f * fRec3[0]);
			float fTemp13 = (fTemp12 + -1.0f);
			float fTemp14 = mydsp_faustpower2_f(fTemp13);
			fVec9[0] = fTemp14;
			float fTemp15 = mydsp_faustpower3_f(fTemp13);
			fVec10[0] = (fTemp15 + (1.0f - fTemp12));
			float fTemp16 = ((fTemp15 + (1.0f - (fTemp12 + fVec10[1]))) / fTemp10);
			fVec11[0] = fTemp16;
			float fTemp17 = (fTemp14 * (fTemp14 + -2.0f));
			fVec12[0] = fTemp17;
			float fTemp18 = ((fTemp17 - fVec12[1]) / fTemp10);
			fVec13[0] = fTemp18;
			float fTemp19 = ((fTemp18 - fVec13[1]) / fTemp10);
			fVec14[0] = fTemp19;
			float fTemp20 = max(20.0f, fabsf((fSlow10 * fRec2[0])));
			fVec15[0] = fTemp20;
			float fTemp21 = (fRec4[1] + (fConst1 * fVec15[1]));
			fRec4[0] = (fTemp21 - floorf(fTemp21));
			float fTemp22 = (2.0f * fRec4[0]);
			float fTemp23 = (fTemp22 + -1.0f);
			float fTemp24 = mydsp_faustpower2_f(fTemp23);
			fVec16[0] = fTemp24;
			float fTemp25 = mydsp_faustpower3_f(fTemp23);
			fVec17[0] = (fTemp25 + (1.0f - fTemp22));
			float fTemp26 = ((fTemp25 + (1.0f - (fTemp22 + fVec17[1]))) / fTemp20);
			fVec18[0] = fTemp26;
			float fTemp27 = (fTemp24 * (fTemp24 + -2.0f));
			fVec19[0] = fTemp27;
			float fTemp28 = ((fTemp27 - fVec19[1]) / fTemp20);
			fVec20[0] = fTemp28;
			float fTemp29 = ((fTemp28 - fVec20[1]) / fTemp20);
			fVec21[0] = fTemp29;
			iRec5[0] = ((1103515245 * iRec5[1]) + 12345);
			float fTemp30 = (4.65661287e-10f * float(iRec5[0]));
			fRec6[0] = (((0.522189379f * fRec6[3]) + (fTemp30 + (2.49495602f * fRec6[1]))) - (2.0172658f * fRec6[2]));
			output0[i] = FAUSTFLOAT((fRec0[0] * (iSlow1?float(input0[i]):(iSlow2?(iSlow11?(((0.0499220341f * fRec6[0]) + (0.0506126992f * fRec6[2])) - ((0.0959935337f * fRec6[1]) + (0.00440878607f * fRec6[3]))):fTemp30):(0.333333343f * (fRec0[0] * (((iSlow4?(iSlow8?(fConst4 * ((float(iVec0[3]) * (fTemp9 - fVec7[1])) / fTemp0)):(fConst3 * ((float(iVec0[2]) * (fTemp6 - fVec4[1])) / fTemp0))):(iSlow5?(fConst2 * ((float(iVec0[1]) * (fTemp4 - fVec2[1])) / fTemp0)):fTemp3)) + (iSlow4?(iSlow8?(fConst4 * ((float(iVec0[3]) * (fTemp19 - fVec14[1])) / fTemp10)):(fConst3 * ((float(iVec0[2]) * (fTemp16 - fVec11[1])) / fTemp10))):(iSlow5?(fConst2 * ((float(iVec0[1]) * (fTemp14 - fVec9[1])) / fTemp10)):fTemp13))) + (iSlow4?(iSlow8?(fConst4 * ((float(iVec0[3]) * (fTemp29 - fVec21[1])) / fTemp20)):(fConst3 * ((float(iVec0[2]) * (fTemp26 - fVec18[1])) / fTemp20))):(iSlow5?(fConst2 * ((float(iVec0[1]) * (fTemp24 - fVec16[1])) / fTemp20)):fTemp23)))))))));
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
			iRec5[1] = iRec5[0];
			for (int j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				fRec6[j1] = fRec6[(j1 - 1)];
				
			}
			
		}
		
	}

	
};

#endif
