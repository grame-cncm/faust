/* ------------------------------------------------------------
author: "JOS, revised by RM"
name: "compressor"
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
	
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fHslider0;
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	float fRec2[2];
	float fRec1[2];
	FAUSTFLOAT fHslider4;
	float fRec0[2];
	float fRec5[2];
	float fRec4[2];
	float fRec3[2];
	FAUSTFLOAT fHbargraph0;
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "0.0");
		m->declare("author", "JOS, revised by RM");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("compressors.lib/name", "Faust Compressor Effect Library");
		m->declare("compressors.lib/version", "0.0");
		m->declare("description", "Compressor demo application");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "compressor");
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
		fConst1 = (2.0f / fConst0);
		fConst2 = (1.0f / fConst0);
		
	}
	
	virtual void instanceResetUserInterface() {
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fHslider0 = FAUSTFLOAT(40.0f);
		fHslider1 = FAUSTFLOAT(50.0f);
		fHslider2 = FAUSTFLOAT(5.0f);
		fHslider3 = FAUSTFLOAT(500.0f);
		fHslider4 = FAUSTFLOAT(-30.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec2[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec1[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec0[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec5[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec4[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec3[l5] = 0.0f;
			
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
		ui_interface->declare(0, "tooltip", "Reference:   http://en.wikipedia.org/wiki/Dynamic_range_compression");
		ui_interface->openVerticalBox("COMPRESSOR");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fCheckbox0, "0", "");
		ui_interface->declare(&fCheckbox0, "tooltip", "When this is checked, the compressor   has no effect");
		ui_interface->addCheckButton("Bypass", &fCheckbox0);
		ui_interface->declare(&fHbargraph0, "1", "");
		ui_interface->declare(&fHbargraph0, "tooltip", "Current gain of  the compressor in dB");
		ui_interface->declare(&fHbargraph0, "unit", "dB");
		ui_interface->addHorizontalBargraph("Compressor Gain", &fHbargraph0, -50.0f, 10.0f);
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(0, "3", "");
		ui_interface->openHorizontalBox("Compression Control");
		ui_interface->declare(&fHslider2, "0", "");
		ui_interface->declare(&fHslider2, "style", "knob");
		ui_interface->declare(&fHslider2, "tooltip", "A compression Ratio of N means that for each N dB increase in input  signal level above Threshold, the output level goes up 1 dB");
		ui_interface->addHorizontalSlider("Ratio", &fHslider2, 5.0f, 1.0f, 20.0f, 0.100000001f);
		ui_interface->declare(&fHslider4, "1", "");
		ui_interface->declare(&fHslider4, "style", "knob");
		ui_interface->declare(&fHslider4, "tooltip", "When the signal level exceeds the Threshold (in dB), its level  is compressed according to the Ratio");
		ui_interface->declare(&fHslider4, "unit", "dB");
		ui_interface->addHorizontalSlider("Threshold", &fHslider4, -30.0f, -100.0f, 10.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->declare(0, "4", "");
		ui_interface->openHorizontalBox("Compression Response");
		ui_interface->declare(&fHslider1, "1", "");
		ui_interface->declare(&fHslider1, "scale", "log");
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->declare(&fHslider1, "unit", "ms");
		ui_interface->addHorizontalSlider("Attack     tooltip: Time constant in ms (1/e smoothing time) for the compression gain  to approach (exponentially) a new lower target level (the compression  `kicking in')]", &fHslider1, 50.0f, 1.0f, 1000.0f, 0.100000001f);
		ui_interface->declare(&fHslider3, "2", "");
		ui_interface->declare(&fHslider3, "scale", "log");
		ui_interface->declare(&fHslider3, "style", "knob");
		ui_interface->declare(&fHslider3, "tooltip", "Time constant in ms (1/e smoothing time) for the compression gain  to approach (exponentially) a new higher target level (the compression  'releasing')");
		ui_interface->declare(&fHslider3, "unit", "ms");
		ui_interface->addHorizontalSlider("Release", &fHslider3, 500.0f, 1.0f, 1000.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(&fHslider0, "5", "");
		ui_interface->declare(&fHslider0, "tooltip", "The compressed-signal output level is increased by this amount  (in dB) to make up for the level lost due to compression");
		ui_interface->declare(&fHslider0, "unit", "dB");
		ui_interface->addHorizontalSlider("Makeup Gain", &fHslider0, 40.0f, -96.0f, 96.0f, 0.100000001f);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		int iSlow0 = int(float(fCheckbox0));
		float fSlow1 = powf(10.0f, (0.0500000007f * float(fHslider0)));
		float fSlow2 = max(fConst2, (0.00100000005f * float(fHslider1)));
		float fSlow3 = expf((0.0f - (fConst1 / fSlow2)));
		float fSlow4 = (((1.0f / float(fHslider2)) + -1.0f) * (1.0f - fSlow3));
		float fSlow5 = expf((0.0f - (fConst2 / fSlow2)));
		float fSlow6 = expf((0.0f - (fConst2 / max(fConst2, (0.00100000005f * float(fHslider3))))));
		float fSlow7 = float(fHslider4);
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input0[i]);
			float fTemp1 = (iSlow0?0.0f:fTemp0);
			float fTemp2 = float(input1[i]);
			float fTemp3 = (iSlow0?0.0f:fTemp2);
			float fTemp4 = fabsf((fabsf(fTemp1) + fabsf(fTemp3)));
			float fTemp5 = ((fRec1[1] > fTemp4)?fSlow6:fSlow5);
			fRec2[0] = ((fRec2[1] * fTemp5) + (fTemp4 * (1.0f - fTemp5)));
			fRec1[0] = fRec2[0];
			fRec0[0] = ((fSlow3 * fRec0[1]) + (fSlow4 * max(((20.0f * log10f(fRec1[0])) - fSlow7), 0.0f)));
			float fTemp6 = powf(10.0f, (0.0500000007f * fRec0[0]));
			float fTemp7 = (fTemp1 * fTemp6);
			output0[i] = FAUSTFLOAT((iSlow0?fTemp0:(fSlow1 * fTemp7)));
			float fTemp8 = (fTemp3 * fTemp6);
			float fTemp9 = fabsf((fabsf(fTemp7) + fabsf(fTemp8)));
			float fTemp10 = ((fRec4[1] > fTemp9)?fSlow6:fSlow5);
			fRec5[0] = ((fRec5[1] * fTemp10) + (fTemp9 * (1.0f - fTemp10)));
			fRec4[0] = fRec5[0];
			fRec3[0] = ((fSlow3 * fRec3[1]) + (fSlow4 * max(((20.0f * log10f(fRec4[0])) - fSlow7), 0.0f)));
			fHbargraph0 = FAUSTFLOAT((20.0f * log10f(powf(10.0f, (0.0500000007f * fRec3[0])))));
			output1[i] = FAUSTFLOAT((iSlow0?fTemp2:(fSlow1 * fTemp8)));
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
			fRec5[1] = fRec5[0];
			fRec4[1] = fRec4[0];
			fRec3[1] = fRec3[0];
			
		}
		
	}

	
};

#endif
