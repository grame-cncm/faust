/* ------------------------------------------------------------
name: "harmonicExciter"
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
	
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fCheckbox0;
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	float fConst3;
	FAUSTFLOAT fHslider4;
	float fRec3[3];
	FAUSTFLOAT fHslider5;
	float fRec6[2];
	float fRec5[2];
	FAUSTFLOAT fHslider6;
	float fRec4[2];
	float fRec2[2];
	float fRec1[2];
	float fRec0[2];
	FAUSTFLOAT fHbargraph0;
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "0.0");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("compressors.lib/name", "Faust Compressor Effect Library");
		m->declare("compressors.lib/version", "0.0");
		m->declare("description", "Psychoacoustic harmonic exciter, with GUI");
		m->declare("exciter_author", "Priyanka Shekar (pshekar@ccrma.stanford.edu), revised by RM");
		m->declare("exciter_copyright", "Copyright (c) 2013 Priyanka Shekar");
		m->declare("exciter_license", "MIT License (MIT)");
		m->declare("exciter_name", "harmonicExciter");
		m->declare("exciter_version", "1.0");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "harmonicExciter");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
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
		fConst1 = (2.0f / fConst0);
		fConst2 = (1.0f / fConst0);
		fConst3 = (3.14159274f / fConst0);
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.5f);
		fHslider1 = FAUSTFLOAT(20.0f);
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(50.0f);
		fHslider3 = FAUSTFLOAT(5.0f);
		fHslider4 = FAUSTFLOAT(5000.0f);
		fHslider5 = FAUSTFLOAT(500.0f);
		fHslider6 = FAUSTFLOAT(-30.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) {
			fRec3[l0] = 0.0f;
			
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
			fRec2[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec1[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec0[l6] = 0.0f;
			
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
		ui_interface->openVerticalBox("harmonicExciter");
		ui_interface->declare(0, "tooltip", "Reference:    http://en.wikipedia.org/wiki/Dynamic_range_compression");
		ui_interface->openVerticalBox("COMPRESSOR");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fCheckbox0, "0", "");
		ui_interface->declare(&fCheckbox0, "tooltip", "When this is checked,   the compressor has no effect");
		ui_interface->addCheckButton("Bypass", &fCheckbox0);
		ui_interface->declare(&fHbargraph0, "1", "");
		ui_interface->declare(&fHbargraph0, "tooltip", "Current gain   of the compressor in dB");
		ui_interface->declare(&fHbargraph0, "unit", "dB");
		ui_interface->addHorizontalBargraph("Compressor Gain", &fHbargraph0, -50.0f, 10.0f);
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(0, "3", "");
		ui_interface->openHorizontalBox("Compression Control");
		ui_interface->declare(&fHslider3, "0", "");
		ui_interface->declare(&fHslider3, "style", "knob");
		ui_interface->declare(&fHslider3, "tooltip", "A compression Ratio  of N means that for each N dB increase in input signal level above Threshold, the  output level goes up 1 dB");
		ui_interface->addHorizontalSlider("Ratio", &fHslider3, 5.0f, 1.0f, 20.0f, 0.100000001f);
		ui_interface->declare(&fHslider6, "1", "");
		ui_interface->declare(&fHslider6, "style", "knob");
		ui_interface->declare(&fHslider6, "tooltip", "When the signal level exceeds the Threshold (in dB), its level is compressed  according to the Ratio");
		ui_interface->declare(&fHslider6, "unit", "dB");
		ui_interface->addHorizontalSlider("Threshold", &fHslider6, -30.0f, -100.0f, 10.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->declare(0, "4", "");
		ui_interface->openHorizontalBox("Compression Response");
		ui_interface->declare(&fHslider2, "1", "");
		ui_interface->declare(&fHslider2, "style", "knob");
		ui_interface->declare(&fHslider2, "tooltip", "Time constant in ms (1/e smoothing time) for the compression gain to approach  (exponentially) a new lower target level (the compression `kicking in')");
		ui_interface->declare(&fHslider2, "unit", "ms");
		ui_interface->addHorizontalSlider("Attack", &fHslider2, 50.0f, 0.0f, 500.0f, 0.100000001f);
		ui_interface->declare(&fHslider5, "2", "");
		ui_interface->declare(&fHslider5, "style", "knob");
		ui_interface->declare(&fHslider5, "tooltip", "Time constant in ms (1/e smoothing time) for the compression gain to approach  (exponentially) a new higher target level (the compression 'releasing')");
		ui_interface->declare(&fHslider5, "unit", "ms");
		ui_interface->addHorizontalSlider("Release", &fHslider5, 500.0f, 0.0f, 1000.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(0, "tooltip", "Reference: Patent US4150253 A");
		ui_interface->openHorizontalBox("EXCITER");
		ui_interface->declare(&fHslider4, "0", "");
		ui_interface->declare(&fHslider4, "scale", "log");
		ui_interface->declare(&fHslider4, "style", "knob");
		ui_interface->declare(&fHslider4, "tooltip", "Cutoff frequency for highpassed components to be excited");
		ui_interface->declare(&fHslider4, "unit", "Hz");
		ui_interface->addHorizontalSlider("Cutoff Frequency", &fHslider4, 5000.0f, 1000.0f, 10000.0f, 100.0f);
		ui_interface->declare(&fHslider1, "1", "");
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->declare(&fHslider1, "tooltip", "Percentage of harmonics generated");
		ui_interface->declare(&fHslider1, "unit", "percent");
		ui_interface->addHorizontalSlider("Harmonics", &fHslider1, 20.0f, 0.0f, 200.0f, 1.0f);
		ui_interface->declare(&fHslider0, "2", "");
		ui_interface->declare(&fHslider0, "style", "knob");
		ui_interface->declare(&fHslider0, "tooltip", "Dry/Wet mix of original signal   to excited signal");
		ui_interface->addHorizontalSlider("Mix", &fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = float(fHslider0);
		float fSlow1 = float(fHslider1);
		float fSlow2 = (100.0f * (fSlow0 / fSlow1));
		float fSlow3 = (0.00999999978f * fSlow1);
		int iSlow4 = int(float(fCheckbox0));
		float fSlow5 = max(fConst2, (0.00100000005f * float(fHslider2)));
		float fSlow6 = expf((0.0f - (fConst1 / fSlow5)));
		float fSlow7 = (((1.0f / float(fHslider3)) + -1.0f) * (1.0f - fSlow6));
		float fSlow8 = tanf((fConst3 * float(fHslider4)));
		float fSlow9 = (1.0f / fSlow8);
		float fSlow10 = (1.0f / (((fSlow9 + 1.41421354f) / fSlow8) + 1.0f));
		float fSlow11 = (1.0f / mydsp_faustpower2_f(fSlow8));
		float fSlow12 = (((fSlow9 + -1.41421354f) / fSlow8) + 1.0f);
		float fSlow13 = (2.0f * (1.0f - fSlow11));
		float fSlow14 = (2.0f * (0.0f - fSlow11));
		float fSlow15 = expf((0.0f - (fConst2 / fSlow5)));
		float fSlow16 = expf((0.0f - (fConst2 / max(fConst2, (0.00100000005f * float(fHslider5))))));
		float fSlow17 = float(fHslider6);
		float fSlow18 = (1.0f - fSlow0);
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input0[i]);
			fRec3[0] = (fTemp0 - (fSlow10 * ((fSlow12 * fRec3[2]) + (fSlow13 * fRec3[1]))));
			float fTemp1 = (fSlow10 * (((fSlow11 * fRec3[0]) + (fSlow14 * fRec3[1])) + (fSlow11 * fRec3[2])));
			float fTemp2 = (iSlow4?0.0f:fTemp1);
			float fTemp3 = fabsf(fTemp2);
			float fTemp4 = ((fRec5[1] > fTemp3)?fSlow16:fSlow15);
			fRec6[0] = ((fRec6[1] * fTemp4) + (fTemp3 * (1.0f - fTemp4)));
			fRec5[0] = fRec6[0];
			fRec4[0] = ((fSlow6 * fRec4[1]) + (fSlow7 * max(((20.0f * log10f(fRec5[0])) - fSlow17), 0.0f)));
			float fTemp5 = (fTemp2 * powf(10.0f, (0.0500000007f * fRec4[0])));
			float fTemp6 = fabsf(fabsf(fTemp5));
			float fTemp7 = ((fRec1[1] > fTemp6)?fSlow16:fSlow15);
			fRec2[0] = ((fRec2[1] * fTemp7) + (fTemp6 * (1.0f - fTemp7)));
			fRec1[0] = fRec2[0];
			fRec0[0] = ((fSlow6 * fRec0[1]) + (fSlow7 * max(((20.0f * log10f(fRec1[0])) - fSlow17), 0.0f)));
			fHbargraph0 = FAUSTFLOAT((20.0f * log10f(powf(10.0f, (0.0500000007f * fRec0[0])))));
			float fTemp8 = (iSlow4?fTemp1:fTemp5);
			float fTemp9 = (fSlow3 * fTemp8);
			output0[i] = FAUSTFLOAT(((fSlow2 * (((fSlow3 * (fTemp8 * float((fTemp9 < 0.0f)))) + (float(((fTemp9 >= 0.0f) * (fTemp9 <= 1.0f))) * (fTemp9 - (0.333333343f * mydsp_faustpower3_f(fTemp9))))) + (0.666666687f * float((fTemp9 > 1.0f))))) + (fSlow18 * fTemp0)));
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fRec6[1] = fRec6[0];
			fRec5[1] = fRec5[0];
			fRec4[1] = fRec4[0];
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
			
		}
		
	}

	
};

#endif
