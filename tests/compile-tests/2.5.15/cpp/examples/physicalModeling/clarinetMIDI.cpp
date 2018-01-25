/* ------------------------------------------------------------
copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
license: "MIT"
name: "ClarinetMIDI"
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
	int iRec6[2];
	FAUSTFLOAT fHslider1;
	int iVec0[2];
	float fRec13[2];
	FAUSTFLOAT fHslider2;
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider3;
	float fRec17[2];
	float fRec18[2];
	FAUSTFLOAT fButton0;
	FAUSTFLOAT fHslider4;
	float fVec1[2];
	FAUSTFLOAT fHslider5;
	float fConst2;
	FAUSTFLOAT fHslider6;
	float fRec19[2];
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	int iRec21[2];
	float fConst7;
	float fConst8;
	float fConst9;
	float fRec20[3];
	float fRec14[2];
	FAUSTFLOAT fHslider7;
	int IOTA;
	float fRec15[2048];
	float fConst10;
	float fConst11;
	FAUSTFLOAT fHslider8;
	FAUSTFLOAT fHslider9;
	float fRec22[2];
	float fVec2[2];
	float fRec11[2];
	float fRec2[2048];
	float fRec0[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("description", "Simple MIDI-controllable clarinet physical model with physical parameters.");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("license", "MIT");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "ClarinetMIDI");
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
		fHslider2 = FAUSTFLOAT(0.25f);
		fHslider3 = FAUSTFLOAT(5.0f);
		fButton0 = FAUSTFLOAT(0.0f);
		fHslider4 = FAUSTFLOAT(0.0f);
		fHslider5 = FAUSTFLOAT(0.59999999999999998f);
		fHslider6 = FAUSTFLOAT(1.0f);
		fHslider7 = FAUSTFLOAT(0.5f);
		fHslider8 = FAUSTFLOAT(440.0f);
		fHslider9 = FAUSTFLOAT(1.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iRec6[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			iVec0[l1] = 0;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec13[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec17[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec18[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fVec1[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec19[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			iRec21[l7] = 0;
			
		}
		for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
			fRec20[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec14[l9] = 0.0f;
			
		}
		IOTA = 0;
		for (int l10 = 0; (l10 < 2048); l10 = (l10 + 1)) {
			fRec15[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec22[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fVec2[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec11[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2048); l14 = (l14 + 1)) {
			fRec2[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec0[l15] = 0.0f;
			
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
		ui_interface->openVerticalBox("clarinet");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("midi");
		ui_interface->declare(&fHslider8, "0", "");
		ui_interface->declare(&fHslider8, "style", "knob");
		ui_interface->addHorizontalSlider("freq", &fHslider8, 440.0f, 50.0f, 1000.0f, 0.00999999978f);
		ui_interface->declare(&fHslider9, "1", "");
		ui_interface->declare(&fHslider9, "hidden", "1");
		ui_interface->declare(&fHslider9, "midi", "pitchwheel");
		ui_interface->declare(&fHslider9, "style", "knob");
		ui_interface->addHorizontalSlider("bend", &fHslider9, 1.0f, 0.0f, 10.0f, 0.00999999978f);
		ui_interface->declare(&fHslider5, "2", "");
		ui_interface->declare(&fHslider5, "style", "knob");
		ui_interface->addHorizontalSlider("gain", &fHslider5, 0.600000024f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fHslider6, "3", "");
		ui_interface->declare(&fHslider6, "style", "knob");
		ui_interface->addHorizontalSlider("envAttack", &fHslider6, 1.0f, 0.0f, 30.0f, 0.00999999978f);
		ui_interface->declare(&fHslider4, "4", "");
		ui_interface->declare(&fHslider4, "hidden", "1");
		ui_interface->declare(&fHslider4, "midi", "ctrl 64");
		ui_interface->declare(&fHslider4, "style", "knob");
		ui_interface->addHorizontalSlider("sustain", &fHslider4, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("otherParams");
		ui_interface->declare(&fHslider7, "0", "");
		ui_interface->declare(&fHslider7, "midi", "ctrl 1");
		ui_interface->declare(&fHslider7, "style", "knob");
		ui_interface->addHorizontalSlider("reedStiffness", &fHslider7, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fHslider1, "1", "");
		ui_interface->declare(&fHslider1, "midi", "ctrl 3");
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->addHorizontalSlider("bellOpening", &fHslider1, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fHslider3, "2", "");
		ui_interface->declare(&fHslider3, "style", "knob");
		ui_interface->addHorizontalSlider("vibratoFreq", &fHslider3, 5.0f, 1.0f, 10.0f, 0.00999999978f);
		ui_interface->declare(&fHslider2, "3", "");
		ui_interface->declare(&fHslider2, "style", "knob");
		ui_interface->addHorizontalSlider("vibratoGain", &fHslider2, 0.25f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fHslider0, "4", "");
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
		float fSlow1 = float(fHslider1);
		float fSlow2 = (1.0f - fSlow1);
		float fSlow3 = (0.00999999978f * float(fHslider2));
		float fSlow4 = (fConst1 * float(fHslider3));
		float fSlow5 = sinf(fSlow4);
		float fSlow6 = cosf(fSlow4);
		float fSlow7 = (0.0f - fSlow5);
		float fSlow8 = min(1.0f, (float(fButton0) + float(fHslider4)));
		float fSlow9 = expf((0.0f - (fConst2 / float(fHslider6))));
		float fSlow10 = ((fSlow8 * float(fHslider5)) * (1.0f - fSlow9));
		float fSlow11 = ((0.25999999f * float(fHslider7)) + -0.439999998f);
		float fSlow12 = (170.0f / float(fHslider8));
		int iSlow13 = (fSlow8 == 0.0f);
		float fSlow14 = float(fHslider9);
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec6[0] = 0;
			iVec0[0] = 1;
			fRec13[0] = ((fSlow1 * fRec13[1]) + (fSlow2 * fRec11[1]));
			float fRec10 = (fRec13[0] + float(iRec6[1]));
			fRec17[0] = ((fSlow5 * fRec18[1]) + (fSlow6 * fRec17[1]));
			fRec18[0] = (((fSlow6 * fRec18[1]) + (fSlow7 * fRec17[1])) + float((1 - iVec0[1])));
			float fTemp0 = (fSlow3 * fRec17[0]);
			fVec1[0] = fSlow8;
			fRec19[0] = (fSlow10 + (fSlow9 * fRec19[1]));
			iRec21[0] = ((1103515245 * iRec21[1]) + 12345);
			fRec20[0] = ((4.65661287e-10f * float(iRec21[0])) - (fConst7 * ((fConst8 * fRec20[1]) + (fConst9 * fRec20[2]))));
			float fTemp1 = (fRec19[0] * ((fConst6 * (fRec20[2] + (fRec20[0] + (2.0f * fRec20[1])))) + 1.0f));
			fRec14[0] = ((fRec0[1] + fTemp0) + fTemp1);
			float fTemp2 = (0.0f - fRec14[1]);
			fRec15[(IOTA & 2047)] = ((fTemp0 + fTemp1) + (fTemp2 * max(-1.0f, min(1.0f, ((fSlow11 * fTemp2) + 0.699999988f)))));
			int iRec16 = 0;
			int iTemp3 = ((fSlow8 == fVec1[1]) | iSlow13);
			fRec22[0] = ((0.999000013f * (fRec22[1] * float(iTemp3))) + (fSlow14 * (1.0f - (0.999000013f * float(iTemp3)))));
			float fTemp4 = (fConst11 * ((fSlow12 / (fRec22[0] * ((fSlow3 * (fRec19[0] * fRec17[0])) + 1.0f))) + -0.0500000007f));
			float fTemp5 = (fTemp4 + -1.49999499f);
			int iTemp6 = int(fTemp5);
			int iTemp7 = (int(min(fConst10, float(max(0, int(iTemp6))))) + 1);
			float fTemp8 = floorf(fTemp5);
			float fTemp9 = (fTemp4 + (-1.0f - fTemp8));
			float fTemp10 = (0.0f - fTemp9);
			float fTemp11 = (fTemp4 + (-2.0f - fTemp8));
			float fTemp12 = (0.0f - (0.5f * fTemp11));
			float fTemp13 = (fTemp4 + (-3.0f - fTemp8));
			float fTemp14 = (0.0f - (0.333333343f * fTemp13));
			float fTemp15 = (fTemp4 + (-4.0f - fTemp8));
			float fTemp16 = (0.0f - (0.25f * fTemp15));
			float fTemp17 = (fTemp4 - fTemp8);
			int iTemp18 = (int(min(fConst10, float(max(0, int((iTemp6 + 2)))))) + 1);
			float fTemp19 = (0.0f - fTemp13);
			float fTemp20 = (0.0f - (0.5f * fTemp15));
			int iTemp21 = (int(min(fConst10, float(max(0, int((iTemp6 + 1)))))) + 1);
			float fTemp22 = (0.0f - fTemp11);
			float fTemp23 = (0.0f - (0.5f * fTemp13));
			float fTemp24 = (0.0f - (0.333333343f * fTemp15));
			float fTemp25 = (fTemp9 * fTemp11);
			int iTemp26 = (int(min(fConst10, float(max(0, int((iTemp6 + 3)))))) + 1);
			float fTemp27 = (0.0f - fTemp15);
			float fTemp28 = (fTemp25 * fTemp13);
			int iTemp29 = (int(min(fConst10, float(max(0, int((iTemp6 + 4)))))) + 1);
			fVec2[0] = (((((fRec15[((IOTA - iTemp7) & 2047)] * fTemp10) * fTemp12) * fTemp14) * fTemp16) + (fTemp17 * ((((0.5f * (((fTemp9 * fRec15[((IOTA - iTemp18) & 2047)]) * fTemp19) * fTemp20)) + (((fRec15[((IOTA - iTemp21) & 2047)] * fTemp22) * fTemp23) * fTemp24)) + (0.166666672f * ((fTemp25 * fRec15[((IOTA - iTemp26) & 2047)]) * fTemp27))) + (0.0416666679f * (fTemp28 * fRec15[((IOTA - iTemp29) & 2047)])))));
			fRec11[0] = fVec2[1];
			int iRec12 = iRec16;
			float fRec7 = fRec10;
			float fRec8 = fRec11[0];
			float fRec9 = (fRec11[0] + float(iRec12));
			fRec2[(IOTA & 2047)] = fRec7;
			float fRec3 = (((((fTemp10 * fTemp12) * fTemp14) * fTemp16) * fRec2[((IOTA - iTemp7) & 2047)]) + (fTemp17 * (((0.166666672f * ((fTemp25 * fTemp27) * fRec2[((IOTA - iTemp26) & 2047)])) + ((((fTemp22 * fTemp23) * fTemp24) * fRec2[((IOTA - iTemp21) & 2047)]) + (0.5f * (((fTemp9 * fTemp19) * fTemp20) * fRec2[((IOTA - iTemp18) & 2047)])))) + (0.0416666679f * (fTemp28 * fRec2[((IOTA - iTemp29) & 2047)])))));
			float fRec4 = fRec8;
			float fRec5 = fRec9;
			fRec0[0] = fRec3;
			float fRec1 = fRec5;
			float fTemp30 = (fSlow0 * fRec1);
			output0[i] = FAUSTFLOAT(fTemp30);
			output1[i] = FAUSTFLOAT(fTemp30);
			iRec6[1] = iRec6[0];
			iVec0[1] = iVec0[0];
			fRec13[1] = fRec13[0];
			fRec17[1] = fRec17[0];
			fRec18[1] = fRec18[0];
			fVec1[1] = fVec1[0];
			fRec19[1] = fRec19[0];
			iRec21[1] = iRec21[0];
			fRec20[2] = fRec20[1];
			fRec20[1] = fRec20[0];
			fRec14[1] = fRec14[0];
			IOTA = (IOTA + 1);
			fRec22[1] = fRec22[0];
			fVec2[1] = fVec2[0];
			fRec11[1] = fRec11[0];
			fRec0[1] = fRec0[0];
			
		}
		
	}

	
};

#endif
