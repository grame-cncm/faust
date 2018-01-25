/* ------------------------------------------------------------
name: "moogVCF"
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

float mydsp_faustpower4_f(float value) {
	return (((value * value) * value) * value);
	
}
float mydsp_faustpower2_f(float value) {
	return (value * value);
	
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
	
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fHslider0;
	float fRec0[2];
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT fHslider1;
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider2;
	float fRec6[2];
	float fRec5[2];
	float fRec4[2];
	float fRec3[2];
	float fRec2[2];
	float fRec1[2];
	FAUSTFLOAT fCheckbox2;
	float fConst2;
	float fRec9[2];
	float fRec8[3];
	float fRec7[3];
	float fRec12[2];
	float fRec10[2];
	float fRec15[2];
	float fRec13[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("description", "Exercise and compare three Moog VCF implementations");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "moogVCF");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("vaeffects.lib/name", "Faust Virtual Analog Filter Effect Library");
		m->declare("vaeffects.lib/version", "0.0");
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
		fConst1 = (6.28318548f / fConst0);
		fConst2 = (3.14159274f / fConst0);
		
	}
	
	virtual void instanceResetUserInterface() {
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fHslider0 = FAUSTFLOAT(5.0f);
		fCheckbox1 = FAUSTFLOAT(0.0f);
		fHslider1 = FAUSTFLOAT(0.90000000000000002f);
		fHslider2 = FAUSTFLOAT(25.0f);
		fCheckbox2 = FAUSTFLOAT(0.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec0[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec6[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec5[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec4[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec3[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec2[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec1[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec9[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
			fRec8[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) {
			fRec7[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec12[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec10[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec15[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec13[l13] = 0.0f;
			
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
		ui_interface->declare(0, "tooltip", "See Faust's   vaeffects.lib for info and references");
		ui_interface->openHorizontalBox("MOOG VCF (Voltage Controlled Filter)");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fCheckbox0, "0", "");
		ui_interface->declare(&fCheckbox0, "tooltip", "When this is checked, the Moog VCF   has no effect");
		ui_interface->addCheckButton("Bypass", &fCheckbox0);
		ui_interface->declare(&fCheckbox1, "1", "");
		ui_interface->declare(&fCheckbox1, "tooltip", "Select moog_vcf_2b (two-biquad)   implementation, instead of the default moog_vcf (analog style) implementation");
		ui_interface->addCheckButton("Use Biquads", &fCheckbox1);
		ui_interface->declare(&fCheckbox2, "2", "");
		ui_interface->declare(&fCheckbox2, "tooltip", "If using biquads, make   them normalized ladders (moog_vcf_2bn)");
		ui_interface->addCheckButton("Normalized Ladders", &fCheckbox2);
		ui_interface->closeBox();
		ui_interface->declare(&fHslider2, "1", "");
		ui_interface->declare(&fHslider2, "tooltip", "The VCF resonates   at the corner frequency (specified in PianoKey (PK) units, with A440 = 49 PK).   The VCF response is flat below the corner frequency, and rolls off -24 dB per   octave above.");
		ui_interface->declare(&fHslider2, "unit", "PK");
		ui_interface->addHorizontalSlider("Corner Frequency", &fHslider2, 25.0f, 1.0f, 88.0f, 0.00999999978f);
		ui_interface->declare(&fHslider1, "2", "");
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->declare(&fHslider1, "tooltip", "Amount of   resonance near VCF corner frequency (specified between 0 and 1)");
		ui_interface->addHorizontalSlider("Corner Resonance", &fHslider1, 0.899999976f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fHslider0, "3", "");
		ui_interface->declare(&fHslider0, "style", "knob");
		ui_interface->declare(&fHslider0, "tooltip", "output level in decibels");
		ui_interface->declare(&fHslider0, "unit", "dB");
		ui_interface->addHorizontalSlider("VCF Output Level", &fHslider0, 5.0f, -60.0f, 20.0f, 0.100000001f);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		int iSlow0 = int(float(fCheckbox0));
		float fSlow1 = (0.00100000005f * powf(10.0f, (0.0500000007f * float(fHslider0))));
		int iSlow2 = int(float(fCheckbox1));
		float fSlow3 = float(fHslider1);
		float fSlow4 = (0.0f - (4.0f * max(0.0f, min(mydsp_faustpower4_f(fSlow3), 0.999998987f))));
		float fSlow5 = (0.439999998f * powf(2.0f, (0.0833333358f * (float(fHslider2) + -49.0f))));
		int iSlow6 = int(float(fCheckbox2));
		float fSlow7 = min(1.41419947f, (1.41421354f * fSlow3));
		float fSlow8 = (fSlow7 * (fSlow7 + 1.41421354f));
		float fSlow9 = (1.41421354f * fSlow7);
		float fSlow10 = (fSlow9 + 2.0f);
		float fSlow11 = (fSlow7 * (fSlow7 + -1.41421354f));
		float fSlow12 = (2.0f - fSlow9);
		float fSlow13 = (1.99997997f * fSlow3);
		float fSlow14 = mydsp_faustpower2_f((1.41419947f * fSlow3));
		float fSlow15 = (fSlow13 + fSlow14);
		float fSlow16 = (fSlow13 + 2.0f);
		float fSlow17 = (2.0f - fSlow13);
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec0[0] = (fSlow1 + (0.999000013f * fRec0[1]));
			float fTemp0 = float(input0[i]);
			float fTemp1 = (iSlow0?0.0f:fTemp0);
			fRec6[0] = (fSlow5 + (0.999000013f * fRec6[1]));
			float fTemp2 = (fConst1 * fRec6[0]);
			float fTemp3 = (1.0f - fTemp2);
			fRec5[0] = ((fSlow4 * fRec1[1]) + (fTemp1 + (fTemp3 * fRec5[1])));
			fRec4[0] = (fRec5[0] + (fTemp3 * fRec4[1]));
			fRec3[0] = (fRec4[0] + (fTemp3 * fRec3[1]));
			fRec2[0] = (fRec3[0] + (fRec2[1] * fTemp3));
			fRec1[0] = (fRec2[0] * powf(fTemp2, 4.0f));
			fRec9[0] = (fSlow5 + (0.999000013f * fRec9[1]));
			float fTemp4 = tanf((fConst2 * max(20.0f, min(10000.0f, fRec9[0]))));
			float fTemp5 = (1.0f / fTemp4);
			float fTemp6 = (1.0f - (1.0f / mydsp_faustpower2_f(fTemp4)));
			float fTemp7 = (fSlow8 + (((fSlow10 + fTemp5) / fTemp4) + 1.0f));
			fRec8[0] = (fTemp1 - (((fRec8[2] * (fSlow8 + (((fTemp5 - fSlow10) / fTemp4) + 1.0f))) + (2.0f * (fRec8[1] * (fSlow8 + fTemp6)))) / fTemp7));
			float fTemp8 = (fSlow11 + (((fSlow12 + fTemp5) / fTemp4) + 1.0f));
			fRec7[0] = (((fRec8[2] + (fRec8[0] + (2.0f * fRec8[1]))) / fTemp7) - (((fRec7[2] * (fSlow11 + (((fTemp5 - fSlow12) / fTemp4) + 1.0f))) + (2.0f * ((fSlow11 + fTemp6) * fRec7[1]))) / fTemp8));
			float fTemp9 = tanf((fConst2 * max(fRec9[0], 20.0f)));
			float fTemp10 = (1.0f / fTemp9);
			float fTemp11 = (fSlow15 + (((fSlow16 + fTemp10) / fTemp9) + 1.0f));
			float fTemp12 = ((fSlow15 + (1.0f - ((fSlow16 - fTemp10) / fTemp9))) / fTemp11);
			float fTemp13 = max(-0.999899983f, min(0.999899983f, fTemp12));
			float fTemp14 = (1.0f - mydsp_faustpower2_f(fTemp13));
			float fTemp15 = sqrtf(max(0.0f, fTemp14));
			float fTemp16 = ((fRec10[1] * (0.0f - fTemp13)) + (fTemp1 * fTemp15));
			float fTemp17 = (1.0f - (1.0f / mydsp_faustpower2_f(fTemp9)));
			float fTemp18 = (fSlow15 + fTemp17);
			float fTemp19 = max(-0.999899983f, min(0.999899983f, (2.0f * (fTemp18 / (fTemp11 * (fTemp12 + 1.0f))))));
			float fTemp20 = (1.0f - mydsp_faustpower2_f(fTemp19));
			float fTemp21 = sqrtf(max(0.0f, fTemp20));
			fRec12[0] = ((fRec12[1] * (0.0f - fTemp19)) + (fTemp16 * fTemp21));
			fRec10[0] = ((fTemp16 * fTemp19) + (fRec12[1] * fTemp21));
			float fRec11 = fRec12[0];
			float fTemp22 = (1.0f - (fTemp18 / fTemp11));
			float fTemp23 = sqrtf(fTemp14);
			float fTemp24 = ((((fTemp1 * fTemp13) + (fRec10[1] * fTemp15)) + (2.0f * ((fRec10[0] * fTemp22) / fTemp23))) + ((fRec11 * ((1.0f - fTemp12) - (2.0f * (fTemp19 * fTemp22)))) / (fTemp23 * sqrtf(fTemp20))));
			float fTemp25 = (fSlow14 + ((((fSlow17 + fTemp10) / fTemp9) + 1.0f) - fSlow13));
			float fTemp26 = ((fSlow14 + ((((fTemp10 - fSlow17) / fTemp9) + 1.0f) - fSlow13)) / fTemp25);
			float fTemp27 = max(-0.999899983f, min(0.999899983f, fTemp26));
			float fTemp28 = (1.0f - mydsp_faustpower2_f(fTemp27));
			float fTemp29 = sqrtf(max(0.0f, fTemp28));
			float fTemp30 = ((fRec13[1] * (0.0f - fTemp27)) + ((fTemp24 * fTemp29) / fTemp11));
			float fTemp31 = (fSlow14 + (fTemp17 - fSlow13));
			float fTemp32 = max(-0.999899983f, min(0.999899983f, (2.0f * (fTemp31 / (fTemp25 * (fTemp26 + 1.0f))))));
			float fTemp33 = (1.0f - mydsp_faustpower2_f(fTemp32));
			float fTemp34 = sqrtf(max(0.0f, fTemp33));
			fRec15[0] = ((fRec15[1] * (0.0f - fTemp32)) + (fTemp30 * fTemp34));
			fRec13[0] = ((fTemp30 * fTemp32) + (fRec15[1] * fTemp34));
			float fRec14 = fRec15[0];
			float fTemp35 = (1.0f - (fTemp31 / fTemp25));
			float fTemp36 = sqrtf(fTemp28);
			output0[i] = FAUSTFLOAT((iSlow0?fTemp0:(fRec0[0] * (iSlow2?(iSlow6?((((((fTemp24 * fTemp27) / fTemp11) + (fRec13[1] * fTemp29)) + (2.0f * ((fRec13[0] * fTemp35) / fTemp36))) + ((fRec14 * ((1.0f - fTemp26) - (2.0f * (fTemp32 * fTemp35)))) / (fTemp36 * sqrtf(fTemp33)))) / fTemp25):((fRec7[2] + (fRec7[0] + (2.0f * fRec7[1]))) / fTemp8)):fRec1[0]))));
			fRec0[1] = fRec0[0];
			fRec6[1] = fRec6[0];
			fRec5[1] = fRec5[0];
			fRec4[1] = fRec4[0];
			fRec3[1] = fRec3[0];
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
			fRec9[1] = fRec9[0];
			fRec8[2] = fRec8[1];
			fRec8[1] = fRec8[0];
			fRec7[2] = fRec7[1];
			fRec7[1] = fRec7[0];
			fRec12[1] = fRec12[0];
			fRec10[1] = fRec10[0];
			fRec15[1] = fRec15[0];
			fRec13[1] = fRec13[0];
			
		}
		
	}

	
};

#endif
