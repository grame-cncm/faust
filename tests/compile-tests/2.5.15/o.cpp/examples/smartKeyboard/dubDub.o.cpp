//----------------------------------------------------------
// name: "dubDub"
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
	FAUSTFLOAT 	fslider0;
	float 	fRec0[2];
	float 	fConst0;
	float 	fConst1;
	float 	fConst2;
	FAUSTFLOAT 	fbutton0;
	float 	fVec0[2];
	float 	fRec2[2];
	float 	fConst3;
	float 	fConst4;
	FAUSTFLOAT 	fslider1;
	int 	iTempPerm0;
	float 	fRec5[2];
	float 	fTempPerm1;
	float 	fTempPerm2;
	float 	fTempPerm3;
	int 	iTempPerm4;
	float 	fRec3[2];
	float 	fConst5;
	FAUSTFLOAT 	fslider2;
	float 	fConst6;
	FAUSTFLOAT 	fslider3;
	float 	fVec1[2];
	float 	fTempPerm5;
	float 	fRec6[2];
	float 	fTempPerm6;
	float 	fTempPerm7;
	float 	fTempPerm8;
	float 	fRec1[3];
	float 	fTempPerm9;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("envelopes.lib/author", "GRAME");
		m->declare("envelopes.lib/copyright", "GRAME");
		m->declare("envelopes.lib/license", "LGPL with exception");
		m->declare("envelopes.lib/name", "Faust Envelope Library");
		m->declare("envelopes.lib/version", "0.0");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("interface", "SmartKeyboard{  'Number of Keyboards':'1',  'Keyboard 0 - Number of Keys':'1',  'Keyboard 0 - Piano Keyboard':'0',  'Keyboard 0 - Static Mode':'1',  'Keyboard 0 - Send X':'1',  'Keyboard 0 - Send Y':'1' }");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "dubDub");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("synths.lib/name", "Faust Synthesizer Library");
		m->declare("synths.lib/version", "0.0");
	}

	virtual int getNumInputs() { return 0; }
	virtual int getNumOutputs() { return 2; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(192000.0f, max(1.0f, (float)fSamplingFreq));
		fConst1 = expf((0 - (100.0f / fConst0)));
		fConst2 = (1.0f - fConst1);
		fConst3 = float(fConst0);
		fConst4 = (1.0f / fConst3);
		iTempPerm0 = 0;
		fTempPerm1 = 0;
		fTempPerm2 = 0;
		fTempPerm3 = 0;
		iTempPerm4 = 0;
		fConst5 = (3.1415926535897931f / fConst0);
		fConst6 = (1.0f / fConst0);
		fTempPerm5 = 0;
		fTempPerm6 = 0;
		fTempPerm7 = 0;
		fTempPerm8 = 0;
		fTempPerm9 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.5f;
		fbutton0 = 0.0;
		fslider1 = 0.0f;
		fslider2 = 0.0f;
		fslider3 = 9.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fVec0[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<3; i++) fRec1[i] = 0;
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
		ui_interface->openVerticalBox("dubDub");
		ui_interface->declare(&fslider0, "acc", "1 0 -10 0 10");
		ui_interface->addHorizontalSlider("gain", &fslider0, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->addButton("gate", &fbutton0);
		ui_interface->declare(&fslider3, "acc", "0 0 -10 0 10");
		ui_interface->addHorizontalSlider("modFeq", &fslider3, 9.0f, 0.5f, 18.0f, 0.01f);
		ui_interface->addHorizontalSlider("x", &fslider1, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("y", &fslider2, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = (0.0010000000000000009f * faustpower<2>(float(fslider0)));
		float 	fSlow1 = float(fbutton0);
		float 	fSlow2 = (fConst2 * fSlow1);
		float 	fSlow3 = ((420 * float(fslider1)) + 80);
		int 	iSlow4 = (fSlow1 == 0);
		float 	fSlow5 = (1 - float(fslider2));
		float 	fSlow6 = float(fslider3);
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fRec0[0] = (fSlow0 + (0.999f * fRec0[1]));
			fVec0[0] = fSlow1;
			fRec2[0] = (fSlow2 + (fConst1 * fRec2[1]));
			iTempPerm0 = ((fSlow1 == fVec0[1]) | iSlow4);
			fRec5[0] = ((fSlow3 * (1.0f - (0.999f * iTempPerm0))) + (0.999f * (iTempPerm0 * fRec5[1])));
			fTempPerm1 = float(max(9.9999999999999995e-08f, fabsf(fRec5[0])));
			fTempPerm2 = (fRec3[1] + (fConst4 * fTempPerm1));
			fTempPerm3 = (fTempPerm2 + -1);
			iTempPerm4 = int((fTempPerm3 < 0));
			fRec3[0] = ((iTempPerm4)?fTempPerm2:fTempPerm3);
			float 	fRec4 = ((iTempPerm4)?fTempPerm2:(fTempPerm2 + ((1 - (fConst3 / fTempPerm1)) * fTempPerm3)));
			fVec1[0] = fSlow6;
			fTempPerm5 = ((fConst6 * fVec1[1]) + fRec6[1]);
			fRec6[0] = (fTempPerm5 - floorf(fTempPerm5));
			fTempPerm6 = tanf((fConst5 * ((4950 * (1 - (fSlow5 * (1 - fabsf(((2.0f * fRec6[0]) + -1.0f)))))) + 50)));
			fTempPerm7 = (1.0f / fTempPerm6);
			fTempPerm8 = (((fTempPerm7 + 0.125f) / fTempPerm6) + 1);
			fRec1[0] = ((0.5f * (fRec2[0] * ((2 * fRec4) + -1))) - (((fRec1[2] * (((fTempPerm7 + -0.125f) / fTempPerm6) + 1)) + (2 * (fRec1[1] * (1 - (1.0f / faustpower<2>(fTempPerm6)))))) / fTempPerm8));
			fTempPerm9 = ((fRec0[0] * (fRec1[2] + (fRec1[0] + (2.0f * fRec1[1])))) / fTempPerm8);
			output0[i] = (FAUSTFLOAT)fTempPerm9;
			output1[i] = (FAUSTFLOAT)fTempPerm9;
			// post processing
			fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
			fRec6[1] = fRec6[0];
			fVec1[1] = fVec1[0];
			fRec3[1] = fRec3[0];
			fRec5[1] = fRec5[0];
			fRec2[1] = fRec2[0];
			fVec0[1] = fVec0[0];
			fRec0[1] = fRec0[0];
		}
	}
};


