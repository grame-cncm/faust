/* ------------------------------------------------------------
author: "JOS, revised by RM"
name: "phaser"
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
float mydsp_faustpower4_f(float value) {
	return (((value * value) * value) * value);
	
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
	int iVec0[2];
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT fHslider1;
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT fHslider4;
	float fConst2;
	FAUSTFLOAT fHslider5;
	FAUSTFLOAT fHslider6;
	FAUSTFLOAT fHslider7;
	float fRec5[2];
	float fRec6[2];
	float fRec4[3];
	float fRec3[3];
	float fRec2[3];
	float fRec1[3];
	float fRec0[2];
	FAUSTFLOAT fCheckbox2;
	float fRec11[3];
	float fRec10[3];
	float fRec9[3];
	float fRec8[3];
	float fRec7[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("author", "JOS, revised by RM");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("description", "Phaser demo application.");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "phaser");
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
		fConst1 = (1.0f / fConst0);
		fConst2 = (6.28318548f / fConst0);
		
	}
	
	virtual void instanceResetUserInterface() {
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fHslider0 = FAUSTFLOAT(0.0f);
		fCheckbox1 = FAUSTFLOAT(0.0f);
		fHslider1 = FAUSTFLOAT(1.0f);
		fHslider2 = FAUSTFLOAT(1000.0f);
		fHslider3 = FAUSTFLOAT(0.0f);
		fHslider4 = FAUSTFLOAT(1.5f);
		fHslider5 = FAUSTFLOAT(100.0f);
		fHslider6 = FAUSTFLOAT(800.0f);
		fHslider7 = FAUSTFLOAT(0.5f);
		fCheckbox2 = FAUSTFLOAT(0.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec5[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec6[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 3); l3 = (l3 + 1)) {
			fRec4[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) {
			fRec3[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) {
			fRec2[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) {
			fRec1[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec0[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
			fRec11[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) {
			fRec10[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 3); l10 = (l10 + 1)) {
			fRec9[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 3); l11 = (l11 + 1)) {
			fRec8[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec7[l12] = 0.0f;
			
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
		ui_interface->declare(0, "tooltip", "Reference:   https://ccrma.stanford.edu/~jos/pasp/Flanging.html");
		ui_interface->openVerticalBox("PHASER2");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fCheckbox0, "0", "");
		ui_interface->declare(&fCheckbox0, "tooltip", "When this is checked, the phaser   has no effect");
		ui_interface->addCheckButton("Bypass", &fCheckbox0);
		ui_interface->declare(&fCheckbox2, "1", "");
		ui_interface->addCheckButton("Invert Internal Phaser Sum", &fCheckbox2);
		ui_interface->declare(&fCheckbox1, "2", "");
		ui_interface->addCheckButton("Vibrato Mode", &fCheckbox1);
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fHslider7, "1", "");
		ui_interface->declare(&fHslider7, "style", "knob");
		ui_interface->declare(&fHslider7, "unit", "Hz");
		ui_interface->addHorizontalSlider("Speed", &fHslider7, 0.5f, 0.0f, 10.0f, 0.00100000005f);
		ui_interface->declare(&fHslider1, "2", "");
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->addHorizontalSlider("Notch Depth (Intensity)", &fHslider1, 1.0f, 0.0f, 1.0f, 0.00100000005f);
		ui_interface->declare(&fHslider3, "3", "");
		ui_interface->declare(&fHslider3, "style", "knob");
		ui_interface->addHorizontalSlider("Feedback Gain", &fHslider3, 0.0f, -0.999000013f, 0.999000013f, 0.00100000005f);
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fHslider2, "1", "");
		ui_interface->declare(&fHslider2, "scale", "log");
		ui_interface->declare(&fHslider2, "style", "knob");
		ui_interface->declare(&fHslider2, "unit", "Hz");
		ui_interface->addHorizontalSlider("Notch width", &fHslider2, 1000.0f, 10.0f, 5000.0f, 1.0f);
		ui_interface->declare(&fHslider5, "2", "");
		ui_interface->declare(&fHslider5, "scale", "log");
		ui_interface->declare(&fHslider5, "style", "knob");
		ui_interface->declare(&fHslider5, "unit", "Hz");
		ui_interface->addHorizontalSlider("Min Notch1 Freq", &fHslider5, 100.0f, 20.0f, 5000.0f, 1.0f);
		ui_interface->declare(&fHslider6, "3", "");
		ui_interface->declare(&fHslider6, "scale", "log");
		ui_interface->declare(&fHslider6, "style", "knob");
		ui_interface->declare(&fHslider6, "unit", "Hz");
		ui_interface->addHorizontalSlider("Max Notch1 Freq", &fHslider6, 800.0f, 20.0f, 10000.0f, 1.0f);
		ui_interface->declare(&fHslider4, "4", "");
		ui_interface->declare(&fHslider4, "style", "knob");
		ui_interface->addHorizontalSlider("Notch Freq Ratio: NotchFreq(n+1)/NotchFreq(n)", &fHslider4, 1.5f, 1.10000002f, 4.0f, 0.00100000005f);
		ui_interface->closeBox();
		ui_interface->declare(0, "3", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fHslider0, "unit", "dB");
		ui_interface->addHorizontalSlider("Phaser Output Level", &fHslider0, 0.0f, -60.0f, 10.0f, 0.100000001f);
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
		float fSlow2 = (0.5f * (int(float(fCheckbox1))?2.0f:float(fHslider1)));
		float fSlow3 = (1.0f - fSlow2);
		float fSlow4 = expf((fConst1 * (0.0f - (3.14159274f * float(fHslider2)))));
		float fSlow5 = mydsp_faustpower2_f(fSlow4);
		float fSlow6 = float(fHslider3);
		float fSlow7 = (0.0f - (2.0f * fSlow4));
		float fSlow8 = float(fHslider4);
		float fSlow9 = float(fHslider5);
		float fSlow10 = (fConst2 * fSlow9);
		float fSlow11 = (0.5f * (0.0f - (fConst2 * (fSlow9 - max(fSlow9, float(fHslider6))))));
		float fSlow12 = (fConst2 * float(fHslider7));
		float fSlow13 = sinf(fSlow12);
		float fSlow14 = cosf(fSlow12);
		float fSlow15 = (0.0f - fSlow13);
		float fSlow16 = mydsp_faustpower2_f(fSlow8);
		float fSlow17 = mydsp_faustpower3_f(fSlow8);
		float fSlow18 = mydsp_faustpower4_f(fSlow8);
		float fSlow19 = (int(float(fCheckbox2))?(0.0f - fSlow2):fSlow2);
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input0[i]);
			float fTemp1 = (iSlow0?0.0f:fTemp0);
			iVec0[0] = 1;
			fRec5[0] = ((fSlow13 * fRec6[1]) + (fSlow14 * fRec5[1]));
			fRec6[0] = (((fSlow14 * fRec6[1]) + (fSlow15 * fRec5[1])) + float((1 - iVec0[1])));
			float fTemp2 = (fSlow10 + (fSlow11 * (1.0f - fRec5[0])));
			float fTemp3 = (fRec4[1] * cosf((fSlow8 * fTemp2)));
			fRec4[0] = (((fSlow1 * fTemp1) + (fSlow6 * fRec0[1])) - ((fSlow7 * fTemp3) + (fSlow5 * fRec4[2])));
			float fTemp4 = (fRec3[1] * cosf((fSlow16 * fTemp2)));
			fRec3[0] = ((fRec4[2] + (fSlow7 * (fTemp3 - fTemp4))) + (fSlow5 * (fRec4[0] - fRec3[2])));
			float fTemp5 = (fRec2[1] * cosf((fSlow17 * fTemp2)));
			fRec2[0] = ((fRec3[2] + (fSlow7 * (fTemp4 - fTemp5))) + (fSlow5 * (fRec3[0] - fRec2[2])));
			float fTemp6 = (fRec1[1] * cosf((fSlow18 * fTemp2)));
			fRec1[0] = ((fRec2[2] + (fSlow7 * (fTemp5 - fTemp6))) + (fSlow5 * (fRec2[0] - fRec1[2])));
			fRec0[0] = ((fSlow5 * fRec1[0]) + ((fSlow7 * fTemp6) + fRec1[2]));
			output0[i] = FAUSTFLOAT((iSlow0?fTemp0:((fSlow1 * (fTemp1 * fSlow3)) + (fRec0[0] * fSlow19))));
			float fTemp7 = float(input1[i]);
			float fTemp8 = (iSlow0?0.0f:fTemp7);
			float fTemp9 = (fSlow10 + (fSlow11 * (1.0f - fRec6[0])));
			float fTemp10 = (fRec11[1] * cosf((fSlow8 * fTemp9)));
			fRec11[0] = (((fSlow1 * fTemp8) + (fSlow6 * fRec7[1])) - ((fSlow7 * fTemp10) + (fSlow5 * fRec11[2])));
			float fTemp11 = (fRec10[1] * cosf((fSlow16 * fTemp9)));
			fRec10[0] = ((fRec11[2] + (fSlow7 * (fTemp10 - fTemp11))) + (fSlow5 * (fRec11[0] - fRec10[2])));
			float fTemp12 = (fRec9[1] * cosf((fSlow17 * fTemp9)));
			fRec9[0] = ((fRec10[2] + (fSlow7 * (fTemp11 - fTemp12))) + (fSlow5 * (fRec10[0] - fRec9[2])));
			float fTemp13 = (fRec8[1] * cosf((fSlow18 * fTemp9)));
			fRec8[0] = ((fRec9[2] + (fSlow7 * (fTemp12 - fTemp13))) + (fSlow5 * (fRec9[0] - fRec8[2])));
			fRec7[0] = ((fSlow5 * fRec8[0]) + ((fSlow7 * fTemp13) + fRec8[2]));
			output1[i] = FAUSTFLOAT((iSlow0?fTemp7:((fSlow1 * (fTemp8 * fSlow3)) + (fRec7[0] * fSlow19))));
			iVec0[1] = iVec0[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec4[2] = fRec4[1];
			fRec4[1] = fRec4[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
			fRec11[2] = fRec11[1];
			fRec11[1] = fRec11[0];
			fRec10[2] = fRec10[1];
			fRec10[1] = fRec10[0];
			fRec9[2] = fRec9[1];
			fRec9[1] = fRec9[0];
			fRec8[2] = fRec8[1];
			fRec8[1] = fRec8[0];
			fRec7[1] = fRec7[0];
			
		}
		
	}

	
};

#endif
