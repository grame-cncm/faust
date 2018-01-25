/* ------------------------------------------------------------
copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
license: "MIT"
name: "FluteMIDI"
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
	int iRec15[2];
	int iVec0[2];
	float fRec22[2];
	FAUSTFLOAT fHslider1;
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider2;
	float fRec23[2];
	float fRec24[2];
	FAUSTFLOAT fButton0;
	FAUSTFLOAT fHslider3;
	float fVec1[2];
	FAUSTFLOAT fHslider4;
	float fConst2;
	FAUSTFLOAT fHslider5;
	float fRec25[2];
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	int iRec27[2];
	float fConst7;
	float fConst8;
	float fConst9;
	float fRec26[3];
	float fRec28[2];
	int IOTA;
	float fRec29[2048];
	float fConst10;
	float fConst11;
	FAUSTFLOAT fHslider6;
	FAUSTFLOAT fHslider7;
	float fRec31[2];
	FAUSTFLOAT fHslider8;
	float fRec32[2];
	float fVec2[2];
	float fVec3[2048];
	float fVec4[2];
	float fRec20[2];
	float fRec11[2048];
	float fRec7[2];
	float fRec3[2048];
	float fRec1[2];
	float fRec2[2];
	float fRec0[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("description", "Simple MIDI-controllable flute physical model with physical parameters.");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("license", "MIT");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "FluteMIDI");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
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
		fConst0 = min(192000.0f, max(1.0f, float(fSamplingFreq)));
		fConst1 = (6.28318548f / fConst0);
		fConst2 = (1000.0f / fConst0);
		fConst3 = tanf((6283.18555f / fConst0));
		fConst4 = (1.0f / fConst3);
		fConst5 = (((fConst4 + 1.41421354f) / fConst3) + 1.0f);
		fConst6 = (0.0500000007f / fConst5);
		fConst7 = (1.0f / fConst5);
		fConst8 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst3))));
		fConst9 = (((fConst4 + -1.41421354f) / fConst3) + 1.0f);
		fConst10 = (0.00882352982f * fConst0);
		fConst11 = (0.00147058826f * fConst0);
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.5f);
		fHslider1 = FAUSTFLOAT(0.5f);
		fHslider2 = FAUSTFLOAT(5.0f);
		fButton0 = FAUSTFLOAT(0.0f);
		fHslider3 = FAUSTFLOAT(0.0f);
		fHslider4 = FAUSTFLOAT(0.90000000000000002f);
		fHslider5 = FAUSTFLOAT(1.0f);
		fHslider6 = FAUSTFLOAT(440.0f);
		fHslider7 = FAUSTFLOAT(1.0f);
		fHslider8 = FAUSTFLOAT(0.5f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iRec15[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			iVec0[l1] = 0;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec22[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec23[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec24[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fVec1[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec25[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			iRec27[l7] = 0;
			
		}
		for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
			fRec26[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec28[l9] = 0.0f;
			
		}
		IOTA = 0;
		for (int l10 = 0; (l10 < 2048); l10 = (l10 + 1)) {
			fRec29[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec31[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec32[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fVec2[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2048); l14 = (l14 + 1)) {
			fVec3[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fVec4[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec20[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 2048); l17 = (l17 + 1)) {
			fRec11[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec7[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 2048); l19 = (l19 + 1)) {
			fRec3[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec1[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec2[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec0[l22] = 0.0f;
			
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
		ui_interface->openVerticalBox("flute");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("midi");
		ui_interface->declare(&fHslider6, "0", "");
		ui_interface->declare(&fHslider6, "style", "knob");
		ui_interface->addHorizontalSlider("freq", &fHslider6, 440.0f, 50.0f, 1000.0f, 0.00999999978f);
		ui_interface->declare(&fHslider7, "1", "");
		ui_interface->declare(&fHslider7, "hidden", "1");
		ui_interface->declare(&fHslider7, "midi", "pitchwheel");
		ui_interface->declare(&fHslider7, "style", "knob");
		ui_interface->addHorizontalSlider("bend", &fHslider7, 1.0f, 0.0f, 10.0f, 0.00999999978f);
		ui_interface->declare(&fHslider4, "2", "");
		ui_interface->declare(&fHslider4, "style", "knob");
		ui_interface->addHorizontalSlider("gain", &fHslider4, 0.899999976f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fHslider5, "3", "");
		ui_interface->declare(&fHslider5, "style", "knob");
		ui_interface->addHorizontalSlider("envAttack", &fHslider5, 1.0f, 0.0f, 30.0f, 0.00999999978f);
		ui_interface->declare(&fHslider3, "4", "");
		ui_interface->declare(&fHslider3, "hidden", "1");
		ui_interface->declare(&fHslider3, "midi", "ctrl 64");
		ui_interface->declare(&fHslider3, "style", "knob");
		ui_interface->addHorizontalSlider("sustain", &fHslider3, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("otherParams");
		ui_interface->declare(&fHslider8, "0", "");
		ui_interface->declare(&fHslider8, "midi", "ctrl 1");
		ui_interface->declare(&fHslider8, "style", "knob");
		ui_interface->addHorizontalSlider("mouthPosition", &fHslider8, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fHslider2, "1", "");
		ui_interface->declare(&fHslider2, "style", "knob");
		ui_interface->addHorizontalSlider("vibratoFreq", &fHslider2, 5.0f, 1.0f, 10.0f, 0.00999999978f);
		ui_interface->declare(&fHslider1, "2", "");
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->addHorizontalSlider("vibratoGain", &fHslider1, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fHslider0, "3", "");
		ui_interface->declare(&fHslider0, "style", "knob");
		ui_interface->addHorizontalSlider("outGain", &fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
		ui_interface->declare(&fButton0, "2", "");
		ui_interface->addButton("gate", &fButton0);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = float(fHslider0);
		float fSlow1 = (0.0399999991f * float(fHslider1));
		float fSlow2 = (fConst1 * float(fHslider2));
		float fSlow3 = sinf(fSlow2);
		float fSlow4 = cosf(fSlow2);
		float fSlow5 = (0.0f - fSlow3);
		float fSlow6 = min(1.0f, (float(fButton0) + float(fHslider3)));
		float fSlow7 = expf((0.0f - (fConst2 / float(fHslider5))));
		float fSlow8 = ((fSlow6 * float(fHslider4)) * (1.0f - fSlow7));
		float fSlow9 = (340.0f / float(fHslider6));
		float fSlow10 = float(fHslider7);
		int iSlow11 = (fSlow6 == 0.0f);
		float fSlow12 = (0.00100000005f * float(fHslider8));
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec15[0] = 0;
			iVec0[0] = 1;
			fRec22[0] = ((0.699999988f * fRec22[1]) + (0.284999996f * fRec20[1]));
			float fRec19 = (fRec22[0] + float(iRec15[1]));
			fRec23[0] = ((fSlow3 * fRec24[1]) + (fSlow4 * fRec23[1]));
			fRec24[0] = (((fSlow4 * fRec24[1]) + (fSlow5 * fRec23[1])) + float((1 - iVec0[1])));
			fVec1[0] = fSlow6;
			fRec25[0] = (fSlow8 + (fSlow7 * fRec25[1]));
			iRec27[0] = ((1103515245 * iRec27[1]) + 12345);
			fRec26[0] = ((4.65661287e-10f * float(iRec27[0])) - (fConst7 * ((fConst8 * fRec26[1]) + (fConst9 * fRec26[2]))));
			fRec28[0] = fRec1[1];
			fRec29[(IOTA & 2047)] = (0.949999988f * fRec28[1]);
			int iRec30 = 0;
			int iTemp0 = ((fSlow6 == fVec1[1]) | iSlow11);
			fRec31[0] = ((fSlow10 * (1.0f - (0.999000013f * float(iTemp0)))) + (0.999000013f * (float(iTemp0) * fRec31[1])));
			float fTemp1 = ((fSlow9 / fRec31[0]) + 0.270000011f);
			fRec32[0] = (fSlow12 + (0.999000013f * fRec32[1]));
			float fTemp2 = (0.400000006f * (fRec32[0] + -0.5f));
			float fTemp3 = (fConst11 * (fTemp1 * (fTemp2 + 0.270000011f)));
			float fTemp4 = (fTemp3 + -1.49999499f);
			int iTemp5 = int(fTemp4);
			int iTemp6 = (int(min(fConst10, float(max(0, int(iTemp5))))) + 1);
			float fTemp7 = floorf(fTemp4);
			float fTemp8 = (fTemp3 + (-1.0f - fTemp7));
			float fTemp9 = (0.0f - fTemp8);
			float fTemp10 = (fTemp3 + (-2.0f - fTemp7));
			float fTemp11 = (0.0f - (0.5f * fTemp10));
			float fTemp12 = (fTemp3 + (-3.0f - fTemp7));
			float fTemp13 = (0.0f - (0.333333343f * fTemp12));
			float fTemp14 = (fTemp3 + (-4.0f - fTemp7));
			float fTemp15 = (0.0f - (0.25f * fTemp14));
			float fTemp16 = (fTemp3 - fTemp7);
			int iTemp17 = (int(min(fConst10, float(max(0, int((iTemp5 + 2)))))) + 1);
			float fTemp18 = (0.0f - fTemp12);
			float fTemp19 = (0.0f - (0.5f * fTemp14));
			int iTemp20 = (int(min(fConst10, float(max(0, int((iTemp5 + 1)))))) + 1);
			float fTemp21 = (0.0f - fTemp10);
			float fTemp22 = (0.0f - (0.5f * fTemp12));
			float fTemp23 = (0.0f - (0.333333343f * fTemp14));
			float fTemp24 = (fTemp8 * fTemp10);
			int iTemp25 = (int(min(fConst10, float(max(0, int((iTemp5 + 3)))))) + 1);
			float fTemp26 = (0.0f - fTemp14);
			float fTemp27 = (fTemp24 * fTemp12);
			int iTemp28 = (int(min(fConst10, float(max(0, int((iTemp5 + 4)))))) + 1);
			fVec2[0] = (((((fRec29[((IOTA - iTemp6) & 2047)] * fTemp9) * fTemp11) * fTemp13) * fTemp15) + (fTemp16 * ((((0.5f * (((fTemp8 * fRec29[((IOTA - iTemp17) & 2047)]) * fTemp18) * fTemp19)) + (((fRec29[((IOTA - iTemp20) & 2047)] * fTemp21) * fTemp22) * fTemp23)) + (0.166666672f * ((fTemp24 * fRec29[((IOTA - iTemp25) & 2047)]) * fTemp26))) + (0.0416666679f * (fTemp27 * fRec29[((IOTA - iTemp28) & 2047)])))));
			float fTemp29 = (((fSlow1 * fRec23[0]) + (fRec25[0] * ((fConst6 * (fRec26[2] + (fRec26[0] + (2.0f * fRec26[1])))) + 1.0f))) - (0.5f * fVec2[1]));
			float fTemp30 = ((0.5f * fRec7[1]) + max(-1.0f, min(1.0f, (fTemp29 * (mydsp_faustpower2_f(fTemp29) + -1.0f)))));
			fVec3[(IOTA & 2047)] = fTemp30;
			float fTemp31 = (fConst11 * (fTemp1 * (0.730000019f - fTemp2)));
			float fTemp32 = (fTemp31 + -1.49999499f);
			int iTemp33 = int(fTemp32);
			int iTemp34 = (int(min(fConst10, float(max(0, int(iTemp33))))) + 1);
			float fTemp35 = floorf(fTemp32);
			float fTemp36 = (fTemp31 + (-1.0f - fTemp35));
			float fTemp37 = (0.0f - fTemp36);
			float fTemp38 = (fTemp31 + (-2.0f - fTemp35));
			float fTemp39 = (0.0f - (0.5f * fTemp38));
			float fTemp40 = (fTemp31 + (-3.0f - fTemp35));
			float fTemp41 = (0.0f - (0.333333343f * fTemp40));
			float fTemp42 = (fTemp31 + (-4.0f - fTemp35));
			float fTemp43 = (0.0f - (0.25f * fTemp42));
			float fTemp44 = (fTemp31 - fTemp35);
			int iTemp45 = (int(min(fConst10, float(max(0, int((iTemp33 + 2)))))) + 1);
			float fTemp46 = (0.0f - fTemp40);
			float fTemp47 = (0.0f - (0.5f * fTemp42));
			int iTemp48 = (int(min(fConst10, float(max(0, int((iTemp33 + 1)))))) + 1);
			float fTemp49 = (0.0f - fTemp38);
			float fTemp50 = (0.0f - (0.5f * fTemp40));
			float fTemp51 = (0.0f - (0.333333343f * fTemp42));
			float fTemp52 = (fTemp36 * fTemp38);
			int iTemp53 = (int(min(fConst10, float(max(0, int((iTemp33 + 3)))))) + 1);
			float fTemp54 = (0.0f - fTemp42);
			float fTemp55 = (fTemp52 * fTemp40);
			int iTemp56 = (int(min(fConst10, float(max(0, int((iTemp33 + 4)))))) + 1);
			fVec4[0] = (((((fVec3[((IOTA - iTemp34) & 2047)] * fTemp37) * fTemp39) * fTemp41) * fTemp43) + (fTemp44 * ((((0.5f * (((fTemp36 * fVec3[((IOTA - iTemp45) & 2047)]) * fTemp46) * fTemp47)) + (((fVec3[((IOTA - iTemp48) & 2047)] * fTemp49) * fTemp50) * fTemp51)) + (0.166666672f * ((fTemp52 * fVec3[((IOTA - iTemp53) & 2047)]) * fTemp54))) + (0.0416666679f * (fTemp55 * fVec3[((IOTA - iTemp56) & 2047)])))));
			fRec20[0] = fVec4[1];
			int iRec21 = iRec30;
			float fRec16 = fRec19;
			float fRec17 = fRec20[0];
			float fRec18 = (fRec20[0] + float(iRec21));
			fRec11[(IOTA & 2047)] = fRec16;
			float fRec12 = (((((fTemp37 * fTemp39) * fTemp41) * fTemp43) * fRec11[((IOTA - iTemp34) & 2047)]) + (fTemp44 * (((0.166666672f * ((fTemp52 * fTemp54) * fRec11[((IOTA - iTemp53) & 2047)])) + ((((fTemp49 * fTemp50) * fTemp51) * fRec11[((IOTA - iTemp48) & 2047)]) + (0.5f * (((fTemp36 * fTemp46) * fTemp47) * fRec11[((IOTA - iTemp45) & 2047)])))) + (0.0416666679f * (fTemp55 * fRec11[((IOTA - iTemp56) & 2047)])))));
			float fRec13 = fRec17;
			float fRec14 = fRec18;
			fRec7[0] = fRec12;
			float fRec8 = fRec7[1];
			float fRec9 = fRec13;
			float fRec10 = fRec14;
			fRec3[(IOTA & 2047)] = fRec8;
			float fRec4 = (((((fTemp9 * fTemp11) * fTemp13) * fTemp15) * fRec3[((IOTA - iTemp6) & 2047)]) + (fTemp16 * (((0.166666672f * ((fTemp24 * fTemp26) * fRec3[((IOTA - iTemp25) & 2047)])) + ((((fTemp21 * fTemp22) * fTemp23) * fRec3[((IOTA - iTemp20) & 2047)]) + (0.5f * (((fTemp8 * fTemp18) * fTemp19) * fRec3[((IOTA - iTemp17) & 2047)])))) + (0.0416666679f * (fTemp27 * fRec3[((IOTA - iTemp28) & 2047)])))));
			float fRec5 = fRec9;
			float fRec6 = fRec10;
			fRec1[0] = fRec4;
			fRec2[0] = fRec6;
			fRec0[0] = ((fRec2[0] + (0.995000005f * fRec0[1])) - fRec2[1]);
			float fTemp57 = (fSlow0 * fRec0[0]);
			output0[i] = FAUSTFLOAT(fTemp57);
			output1[i] = FAUSTFLOAT(fTemp57);
			iRec15[1] = iRec15[0];
			iVec0[1] = iVec0[0];
			fRec22[1] = fRec22[0];
			fRec23[1] = fRec23[0];
			fRec24[1] = fRec24[0];
			fVec1[1] = fVec1[0];
			fRec25[1] = fRec25[0];
			iRec27[1] = iRec27[0];
			fRec26[2] = fRec26[1];
			fRec26[1] = fRec26[0];
			fRec28[1] = fRec28[0];
			IOTA = (IOTA + 1);
			fRec31[1] = fRec31[0];
			fRec32[1] = fRec32[0];
			fVec2[1] = fVec2[0];
			fVec4[1] = fVec4[0];
			fRec20[1] = fRec20[0];
			fRec7[1] = fRec7[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec0[1] = fRec0[0];
			
		}
		
	}

	
};

#endif
