//----------------------------------------------------------
// name: "trumpet"
//
// Code generated with Faust 2.5.15 (https://faust.grame.fr)
//----------------------------------------------------------

/* link with  */
#include <math.h>
#ifndef FAUSTPOWER
#define FAUSTPOWER
#include <cmath>
template <int N> inline int faustpower(int x)              { return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline int faustpower<0>(int x)            { return 1; }
template <> 	 inline int faustpower<1>(int x)            { return x; }
template <> 	 inline int faustpower<2>(int x)            { return x*x; }
template <int N> inline float faustpower(float x)            { return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline float faustpower<0>(float x)          { return 1; }
template <> 	 inline float faustpower<1>(float x)          { return x; }
template <> 	 inline float faustpower<2>(float x)          { return x*x; }
#endif

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


#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

class mydsp : public dsp {
  private:
	float 	fConst0;
	float 	fConst1;
	FAUSTFLOAT 	fslider0;
	float 	fRec2[2];
	float 	fTempPerm0;
	float 	fTempPerm1;
	float 	fTempPerm2;
	FAUSTFLOAT 	fbutton0;
	FAUSTFLOAT 	fslider1;
	float 	fVec0[2];
	FAUSTFLOAT 	fslider2;
	float 	fRec3[2];
	float 	fConst2;
	float 	fConst3;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT 	fslider4;
	int 	iTempPerm3;
	float 	fRec6[2];
	float 	fTempPerm4;
	float 	fTempPerm5;
	float 	fTempPerm6;
	int 	iTempPerm7;
	float 	fRec4[2];
	float 	fTempPerm8;
	float 	fVec1[2];
	float 	fRec1[2];
	float 	fTempPerm9;
	float 	fRec0[3];
	float 	fTempPerm10;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("interface", "SmartKeyboard{  'Number of Keyboards':'5',  'Max Keyboard Polyphony':'1',  'Mono Mode':'1',  'Keyboard 0 - Number of Keys':'13',  'Keyboard 1 - Number of Keys':'13',  'Keyboard 2 - Number of Keys':'13',  'Keyboard 3 - Number of Keys':'13',  'Keyboard 4 - Number of Keys':'13',  'Keyboard 0 - Lowest Key':'77',  'Keyboard 1 - Lowest Key':'72',  'Keyboard 2 - Lowest Key':'67',  'Keyboard 3 - Lowest Key':'62',  'Keyboard 4 - Lowest Key':'57',  'Rounding Mode':'2',  'Keyboard 0 - Send Y':'1',  'Keyboard 1 - Send Y':'1',  'Keyboard 2 - Send Y':'1',  'Keyboard 3 - Send Y':'1',  'Keyboard 4 - Send Y':'1', }");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "trumpet");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
	}

	virtual int getNumInputs() { return 0; }
	virtual int getNumOutputs() { return 2; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(192000.0f, max(1.0f, (float)fSamplingFreq));
		fConst1 = (3.1415926535897931f / fConst0);
		fTempPerm0 = 0;
		fTempPerm1 = 0;
		fTempPerm2 = 0;
		fConst2 = float(fConst0);
		fConst3 = (1.0f / fConst2);
		iTempPerm3 = 0;
		fTempPerm4 = 0;
		fTempPerm5 = 0;
		fTempPerm6 = 0;
		iTempPerm7 = 0;
		fTempPerm8 = 0;
		fTempPerm9 = 0;
		fTempPerm10 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 1.0f;
		fbutton0 = 0.0;
		fslider1 = 0.0f;
		fslider2 = 1.0f;
		fslider3 = 300.0f;
		fslider4 = 1.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fVec0[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<3; i++) fRec0[i] = 0;
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
		ui_interface->openVerticalBox("trumpet");
		ui_interface->declare(&fslider4, "midi", "pitchwheel");
		ui_interface->addHorizontalSlider("bend", &fslider4, 1.0f, 0.0f, 10.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider3, 300.0f, 50.0f, 2000.0f, 0.01f);
		ui_interface->addHorizontalSlider("gain", &fslider2, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addButton("gate", &fbutton0);
		ui_interface->declare(&fslider1, "midi", "ctrl 64");
		ui_interface->addHorizontalSlider("sustain", &fslider1, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->declare(&fslider0, "midi", "ctrl 1");
		ui_interface->addHorizontalSlider("y", &fslider0, 1.0f, 0.0f, 1.0f, 0.001f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = (0.0010000000000000009f * float(fslider0));
		float 	fSlow1 = min((float)1, (float(fbutton0) + float(fslider1)));
		float 	fSlow2 = (0.0010000000000000009f * (fSlow1 * float(fslider2)));
		float 	fSlow3 = float(fslider3);
		float 	fSlow4 = float(fslider4);
		int 	iSlow5 = (fSlow1 == 0);
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fRec2[0] = (fSlow0 + (0.999f * fRec2[1]));
			fTempPerm0 = tanf((fConst1 * ((4000 * fRec2[0]) + 50)));
			fTempPerm1 = (1.0f / fTempPerm0);
			fTempPerm2 = (fTempPerm1 + 1);
			fVec0[0] = fSlow1;
			fRec3[0] = (fSlow2 + (0.999f * fRec3[1]));
			iTempPerm3 = ((fSlow1 == fVec0[1]) | iSlow5);
			fRec6[0] = ((fSlow4 * (1.0f - (0.999f * iTempPerm3))) + (0.999f * (iTempPerm3 * fRec6[1])));
			fTempPerm4 = float(max(9.9999999999999995e-08f, fabsf((fSlow3 * fRec6[0]))));
			fTempPerm5 = (fRec4[1] + (fConst3 * fTempPerm4));
			fTempPerm6 = (fTempPerm5 + -1);
			iTempPerm7 = int((fTempPerm6 < 0));
			fRec4[0] = ((iTempPerm7)?fTempPerm5:fTempPerm6);
			float 	fRec5 = ((iTempPerm7)?fTempPerm5:(fTempPerm5 + ((1 - (fConst2 / fTempPerm4)) * fTempPerm6)));
			fTempPerm8 = (fRec3[0] * ((2 * fRec5) + -1));
			fVec1[0] = fTempPerm8;
			fRec1[0] = ((fRec1[1] * (0 - ((1 - fTempPerm1) / fTempPerm2))) + ((fVec1[0] + fVec1[1]) / fTempPerm2));
			fTempPerm9 = (((fTempPerm1 + 1.0000000000000002f) / fTempPerm0) + 1);
			fRec0[0] = (fRec1[0] - (((fRec0[2] * (((fTempPerm1 + -1.0000000000000002f) / fTempPerm0) + 1)) + (2 * (fRec0[1] * (1 - (1.0f / faustpower<2>(fTempPerm0)))))) / fTempPerm9));
			fTempPerm10 = ((fRec0[2] + (fRec0[0] + (2.0f * fRec0[1]))) / fTempPerm9);
			output0[i] = (FAUSTFLOAT)fTempPerm10;
			output1[i] = (FAUSTFLOAT)fTempPerm10;
			// post processing
			fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			fVec1[1] = fVec1[0];
			fRec4[1] = fRec4[0];
			fRec6[1] = fRec6[0];
			fRec3[1] = fRec3[0];
			fVec0[1] = fVec0[0];
			fRec2[1] = fRec2[0];
		}
	}
};


