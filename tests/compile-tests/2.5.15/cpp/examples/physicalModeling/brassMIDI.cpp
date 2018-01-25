/* ------------------------------------------------------------
copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
license: "MIT"
name: "BrassMIDI"
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
	float fRec14[2];
	float fRec13[2];
	float fRec15[2];
	FAUSTFLOAT fButton0;
	FAUSTFLOAT fHslider2;
	float fVec1[2];
	FAUSTFLOAT fHslider3;
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider4;
	float fRec20[2];
	FAUSTFLOAT fHslider5;
	float fConst2;
	FAUSTFLOAT fHslider6;
	float fRec21[2];
	float fRec22[2];
	FAUSTFLOAT fHslider7;
	FAUSTFLOAT fHslider8;
	float fRec23[2];
	FAUSTFLOAT fHslider9;
	float fRec24[2];
	float fRec19[3];
	float fVec2[2];
	float fRec18[2];
	int IOTA;
	float fRec16[2048];
	float fConst3;
	float fConst4;
	float fVec3[2];
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
		m->declare("description", "Simple MIDI-controllable brass instrument physical model with physical parameters.");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("license", "MIT");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "BrassMIDI");
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
		fConst1 = (1000.0f / fConst0);
		fConst2 = (6.28318548f / fConst0);
		fConst3 = (0.00882352982f * fConst0);
		fConst4 = (0.5f * fConst0);
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.5f);
		fHslider1 = FAUSTFLOAT(0.5f);
		fButton0 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(0.0f);
		fHslider3 = FAUSTFLOAT(0.5f);
		fHslider4 = FAUSTFLOAT(1.0f);
		fHslider5 = FAUSTFLOAT(0.5f);
		fHslider6 = FAUSTFLOAT(5.0f);
		fHslider7 = FAUSTFLOAT(440.0f);
		fHslider8 = FAUSTFLOAT(1.0f);
		fHslider9 = FAUSTFLOAT(0.5f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iRec6[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			iVec0[l1] = 0;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec14[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec13[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec15[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fVec1[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec20[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec21[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec22[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec23[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec24[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 3); l11 = (l11 + 1)) {
			fRec19[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fVec2[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec18[l13] = 0.0f;
			
		}
		IOTA = 0;
		for (int l14 = 0; (l14 < 2048); l14 = (l14 + 1)) {
			fRec16[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fVec3[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec11[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 2048); l17 = (l17 + 1)) {
			fRec2[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec0[l18] = 0.0f;
			
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
		ui_interface->openVerticalBox("brass");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("midi");
		ui_interface->declare(&fHslider7, "0", "");
		ui_interface->declare(&fHslider7, "style", "knob");
		ui_interface->addHorizontalSlider("freq", &fHslider7, 440.0f, 50.0f, 1000.0f, 0.00999999978f);
		ui_interface->declare(&fHslider8, "1", "");
		ui_interface->declare(&fHslider8, "hidden", "1");
		ui_interface->declare(&fHslider8, "midi", "pitchwheel");
		ui_interface->declare(&fHslider8, "style", "knob");
		ui_interface->addHorizontalSlider("bend", &fHslider8, 1.0f, 0.0f, 10.0f, 0.00999999978f);
		ui_interface->declare(&fHslider3, "2", "");
		ui_interface->declare(&fHslider3, "style", "knob");
		ui_interface->addHorizontalSlider("gain", &fHslider3, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fHslider4, "3", "");
		ui_interface->declare(&fHslider4, "style", "knob");
		ui_interface->addHorizontalSlider("envAttack", &fHslider4, 1.0f, 0.0f, 30.0f, 0.00999999978f);
		ui_interface->declare(&fHslider2, "4", "");
		ui_interface->declare(&fHslider2, "hidden", "1");
		ui_interface->declare(&fHslider2, "midi", "ctrl 64");
		ui_interface->declare(&fHslider2, "style", "knob");
		ui_interface->addHorizontalSlider("sustain", &fHslider2, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("otherParams");
		ui_interface->declare(&fHslider9, "0", "");
		ui_interface->declare(&fHslider9, "midi", "ctrl 1");
		ui_interface->declare(&fHslider9, "style", "knob");
		ui_interface->addHorizontalSlider("lipsTension", &fHslider9, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fHslider1, "1", "");
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->addHorizontalSlider("mute", &fHslider1, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fHslider6, "2", "");
		ui_interface->declare(&fHslider6, "style", "knob");
		ui_interface->addHorizontalSlider("vibratoFreq", &fHslider6, 5.0f, 1.0f, 10.0f, 0.00999999978f);
		ui_interface->declare(&fHslider5, "3", "");
		ui_interface->declare(&fHslider5, "style", "knob");
		ui_interface->addHorizontalSlider("vibratoGain", &fHslider5, 0.5f, 0.0f, 1.0f, 0.00999999978f);
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
		float fSlow1 = (0.00100000005f * float(fHslider1));
		float fSlow2 = min(1.0f, (float(fButton0) + float(fHslider2)));
		float fSlow3 = expf((0.0f - (fConst1 / float(fHslider4))));
		float fSlow4 = ((fSlow2 * float(fHslider3)) * (1.0f - fSlow3));
		float fSlow5 = (0.0399999991f * float(fHslider5));
		float fSlow6 = (fConst2 * float(fHslider6));
		float fSlow7 = sinf(fSlow6);
		float fSlow8 = cosf(fSlow6);
		float fSlow9 = (0.0f - fSlow7);
		float fSlow10 = float(fHslider7);
		float fSlow11 = (fConst2 * fSlow10);
		float fSlow12 = float(fHslider8);
		int iSlow13 = (fSlow2 == 0.0f);
		float fSlow14 = (0.00100000005f * float(fHslider9));
		float fSlow15 = (fConst4 / fSlow10);
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec6[0] = 0;
			iVec0[0] = 1;
			fRec14[0] = (fSlow1 + (0.999000013f * fRec14[1]));
			fRec13[0] = ((fRec14[0] * fRec13[1]) + ((1.0f - fRec14[0]) * fRec11[1]));
			float fRec10 = (fRec13[0] + float(iRec6[1]));
			fRec15[0] = fRec0[1];
			fVec1[0] = fSlow2;
			fRec20[0] = (fSlow4 + (fSlow3 * fRec20[1]));
			fRec21[0] = ((fSlow7 * fRec22[1]) + (fSlow8 * fRec21[1]));
			fRec22[0] = (((fSlow8 * fRec22[1]) + (fSlow9 * fRec21[1])) + float((1 - iVec0[1])));
			float fTemp0 = (fRec20[0] * ((fSlow5 * (fRec20[0] * fRec21[0])) + 1.0f));
			int iTemp1 = ((fSlow2 == fVec1[1]) | iSlow13);
			fRec23[0] = ((fSlow12 * (1.0f - (0.999000013f * float(iTemp1)))) + (0.999000013f * (float(iTemp1) * fRec23[1])));
			fRec24[0] = (fSlow14 + (0.999000013f * fRec24[1]));
			fRec19[0] = ((0.0299999993f * ((0.300000012f * fTemp0) - (0.850000024f * fRec15[1]))) - ((fRec19[1] * (0.0f - (1.99399996f * cosf((fSlow11 * (fRec23[0] * powf(4.0f, ((2.0f * fRec24[0]) + -1.0f)))))))) + (0.994009018f * fRec19[2])));
			float fTemp2 = max(-1.0f, min(1.0f, mydsp_faustpower2_f(fRec19[0])));
			float fTemp3 = (0.850000024f * (fRec15[1] * (1.0f - fTemp2)));
			float fTemp4 = (0.300000012f * (fTemp0 * fTemp2));
			fVec2[0] = (fTemp4 + fTemp3);
			fRec18[0] = ((fTemp3 + ((0.995000005f * fRec18[1]) + fTemp4)) - fVec2[1]);
			fRec16[(IOTA & 2047)] = fRec18[0];
			int iRec17 = 0;
			float fTemp5 = (fSlow15 / fRec23[0]);
			float fTemp6 = (fTemp5 + -1.49999499f);
			int iTemp7 = int(fTemp6);
			int iTemp8 = (int(min(fConst3, float(max(0, int(iTemp7))))) + 1);
			float fTemp9 = floorf(fTemp6);
			float fTemp10 = (fTemp5 + (-1.0f - fTemp9));
			float fTemp11 = (0.0f - fTemp10);
			float fTemp12 = (fTemp5 + (-2.0f - fTemp9));
			float fTemp13 = (0.0f - (0.5f * fTemp12));
			float fTemp14 = (fTemp5 + (-3.0f - fTemp9));
			float fTemp15 = (0.0f - (0.333333343f * fTemp14));
			float fTemp16 = (fTemp5 + (-4.0f - fTemp9));
			float fTemp17 = (0.0f - (0.25f * fTemp16));
			float fTemp18 = (fTemp5 - fTemp9);
			int iTemp19 = (int(min(fConst3, float(max(0, int((iTemp7 + 2)))))) + 1);
			float fTemp20 = (0.0f - fTemp14);
			float fTemp21 = (0.0f - (0.5f * fTemp16));
			int iTemp22 = (int(min(fConst3, float(max(0, int((iTemp7 + 1)))))) + 1);
			float fTemp23 = (0.0f - fTemp12);
			float fTemp24 = (0.0f - (0.5f * fTemp14));
			float fTemp25 = (0.0f - (0.333333343f * fTemp16));
			float fTemp26 = (fTemp10 * fTemp12);
			int iTemp27 = (int(min(fConst3, float(max(0, int((iTemp7 + 3)))))) + 1);
			float fTemp28 = (0.0f - fTemp16);
			float fTemp29 = (fTemp26 * fTemp14);
			int iTemp30 = (int(min(fConst3, float(max(0, int((iTemp7 + 4)))))) + 1);
			fVec3[0] = (((((fRec16[((IOTA - iTemp8) & 2047)] * fTemp11) * fTemp13) * fTemp15) * fTemp17) + (fTemp18 * ((((0.5f * (((fTemp10 * fRec16[((IOTA - iTemp19) & 2047)]) * fTemp20) * fTemp21)) + (((fRec16[((IOTA - iTemp22) & 2047)] * fTemp23) * fTemp24) * fTemp25)) + (0.166666672f * ((fTemp26 * fRec16[((IOTA - iTemp27) & 2047)]) * fTemp28))) + (0.0416666679f * (fTemp29 * fRec16[((IOTA - iTemp30) & 2047)])))));
			fRec11[0] = fVec3[1];
			int iRec12 = iRec17;
			float fRec7 = fRec10;
			float fRec8 = fRec11[0];
			float fRec9 = (fRec11[0] + float(iRec12));
			fRec2[(IOTA & 2047)] = fRec7;
			float fRec3 = (((((fTemp11 * fTemp13) * fTemp15) * fTemp17) * fRec2[((IOTA - iTemp8) & 2047)]) + (fTemp18 * (((0.166666672f * ((fTemp26 * fTemp28) * fRec2[((IOTA - iTemp27) & 2047)])) + ((((fTemp23 * fTemp24) * fTemp25) * fRec2[((IOTA - iTemp22) & 2047)]) + (0.5f * (((fTemp10 * fTemp20) * fTemp21) * fRec2[((IOTA - iTemp19) & 2047)])))) + (0.0416666679f * (fTemp29 * fRec2[((IOTA - iTemp30) & 2047)])))));
			float fRec4 = fRec8;
			float fRec5 = fRec9;
			fRec0[0] = fRec3;
			float fRec1 = fRec5;
			float fTemp31 = (fSlow0 * fRec1);
			output0[i] = FAUSTFLOAT(fTemp31);
			output1[i] = FAUSTFLOAT(fTemp31);
			iRec6[1] = iRec6[0];
			iVec0[1] = iVec0[0];
			fRec14[1] = fRec14[0];
			fRec13[1] = fRec13[0];
			fRec15[1] = fRec15[0];
			fVec1[1] = fVec1[0];
			fRec20[1] = fRec20[0];
			fRec21[1] = fRec21[0];
			fRec22[1] = fRec22[0];
			fRec23[1] = fRec23[0];
			fRec24[1] = fRec24[0];
			fRec19[2] = fRec19[1];
			fRec19[1] = fRec19[0];
			fVec2[1] = fVec2[0];
			fRec18[1] = fRec18[0];
			IOTA = (IOTA + 1);
			fVec3[1] = fVec3[0];
			fRec11[1] = fRec11[0];
			fRec0[1] = fRec0[0];
			
		}
		
	}

	
};

#endif
