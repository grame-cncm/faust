//----------------------------------------------------------
// name: "multiSynth"
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
	int 	iVec0[2];
	FAUSTFLOAT 	fbutton0;
	FAUSTFLOAT 	fslider0;
	float 	fVec1[2];
	FAUSTFLOAT 	fslider1;
	float 	fRec0[2];
	float 	fConst0;
	float 	fConst1;
	FAUSTFLOAT 	fslider2;
	float 	fRec3[2];
	float 	fTempPerm0;
	float 	fTempPerm1;
	float 	fTempPerm2;
	FAUSTFLOAT 	fslider3;
	float 	fConst2;
	float 	fConst3;
	float 	fConst4;
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT 	fslider5;
	int 	iTempPerm3;
	float 	fRec5[2];
	float 	fTempPerm4;
	float 	fTempPerm5;
	float 	fTempPerm6;
	float 	fVec2[2];
	float 	fTempPerm7;
	float 	fRec4[2];
	float 	fTempPerm8;
	float 	fVec3[2];
	float 	fTempPerm9;
	int 	IOTA;
	float 	fVec4[4096];
	float 	fConst5;
	float 	fTempPerm10;
	int 	iTempPerm11;
	float 	fTempPerm12;
	float 	fTempPerm13;
	float 	fConst6;
	float 	fRec6[2];
	float 	fConst7;
	float 	fTempPerm14;
	float 	fTempPerm15;
	float 	fTempPerm16;
	float 	fRec7[2];
	float 	fRec8[2];
	float 	fConst8;
	float 	fTempPerm17;
	float 	fTempPerm18;
	float 	fTempPerm19;
	int 	iTempPerm20;
	float 	fRec9[2];
	float 	fTempPerm21;
	float 	fVec5[2];
	float 	fRec2[2];
	float 	fTempPerm22;
	float 	fRec1[3];
	float 	fTempPerm23;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("interface", "SmartKeyboard{  'Number of Keyboards':'4',  'Rounding Mode':'2',  'Inter-Keyboard Slide':'0',  'Keyboard 0 - Number of Keys':'13',  'Keyboard 1 - Number of Keys':'13',  'Keyboard 2 - Number of Keys':'13',  'Keyboard 3 - Number of Keys':'13',  'Keyboard 0 - Lowest Key':'60',  'Keyboard 1 - Lowest Key':'60',  'Keyboard 2 - Lowest Key':'60',  'Keyboard 3 - Lowest Key':'60',  'Keyboard 0 - Send Y':'1',  'Keyboard 1 - Send Y':'1',  'Keyboard 2 - Send Y':'1',  'Keyboard 3 - Send Y':'1' }");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "multiSynth");
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
		fConst3 = (0.25f * fConst2);
		fConst4 = (1.0f / fConst0);
		iTempPerm3 = 0;
		fTempPerm4 = 0;
		fTempPerm5 = 0;
		fTempPerm6 = 0;
		fTempPerm7 = 0;
		fTempPerm8 = 0;
		fTempPerm9 = 0;
		fConst5 = (0.5f * fConst2);
		fTempPerm10 = 0;
		iTempPerm11 = 0;
		fTempPerm12 = 0;
		fTempPerm13 = 0;
		fConst6 = (4.0f / fConst0);
		fConst7 = (6.2831853071795862f / fConst0);
		fTempPerm14 = 0;
		fTempPerm15 = 0;
		fTempPerm16 = 0;
		fConst8 = (1.0f / fConst2);
		fTempPerm17 = 0;
		fTempPerm18 = 0;
		fTempPerm19 = 0;
		iTempPerm20 = 0;
		fTempPerm21 = 0;
		fTempPerm22 = 0;
		fTempPerm23 = 0;
	}
	virtual void instanceResetUserInterface() {
		fbutton0 = 0.0;
		fslider0 = 0.0f;
		fslider1 = 1.0f;
		fslider2 = 1.0f;
		fslider3 = 0.0f;
		fslider4 = 300.0f;
		fslider5 = 1.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) iVec0[i] = 0;
		for (int i=0; i<2; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) fVec2[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2; i++) fVec3[i] = 0;
		IOTA = 0;
		for (int i=0; i<4096; i++) fVec4[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<2; i++) fRec7[i] = 0;
		for (int i=0; i<2; i++) fRec8[i] = 0;
		for (int i=0; i<2; i++) fRec9[i] = 0;
		for (int i=0; i<2; i++) fVec5[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
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
		ui_interface->openVerticalBox("multiSynth");
		ui_interface->declare(&fslider5, "midi", "pitchwheel");
		ui_interface->addHorizontalSlider("bend", &fslider5, 1.0f, 0.0f, 10.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider4, 300.0f, 50.0f, 2000.0f, 0.01f);
		ui_interface->addHorizontalSlider("gain", &fslider1, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addButton("gate", &fbutton0);
		ui_interface->addHorizontalSlider("keyboard", &fslider3, 0.0f, 0.0f, 3.0f, 1.0f);
		ui_interface->declare(&fslider0, "midi", "ctrl 64");
		ui_interface->addHorizontalSlider("sustain", &fslider0, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->declare(&fslider2, "midi", "ctrl 1");
		ui_interface->addHorizontalSlider("y", &fslider2, 1.0f, 0.0f, 1.0f, 0.001f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = min((float)1, (float(fbutton0) + float(fslider0)));
		float 	fSlow1 = (0.0010000000000000009f * (fSlow0 * float(fslider1)));
		float 	fSlow2 = (0.0010000000000000009f * float(fslider2));
		int 	iSlow3 = int(float(fslider3));
		int 	iSlow4 = int((iSlow3 == 2));
		float 	fSlow5 = float(fslider4);
		float 	fSlow6 = float(fslider5);
		int 	iSlow7 = (fSlow0 == 0);
		int 	iSlow8 = int((iSlow3 == 1));
		float 	fSlow9 = (fConst6 * fSlow5);
		int 	iSlow10 = int((iSlow3 == 3));
		float 	fSlow11 = (fConst7 * fSlow5);
		int 	iSlow12 = int((iSlow3 == 0));
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			iVec0[0] = 1;
			fVec1[0] = fSlow0;
			fRec0[0] = (fSlow1 + (0.999f * fRec0[1]));
			fRec3[0] = (fSlow2 + (0.999f * fRec3[1]));
			fTempPerm0 = tanf((fConst1 * ((4000 * fRec3[0]) + 50)));
			fTempPerm1 = (1.0f / fTempPerm0);
			fTempPerm2 = (fTempPerm1 + 1);
			iTempPerm3 = ((fSlow0 == fVec1[1]) | iSlow7);
			fRec5[0] = ((fSlow6 * (1.0f - (0.999f * iTempPerm3))) + (0.999f * (iTempPerm3 * fRec5[1])));
			fTempPerm4 = (fSlow5 * fRec5[0]);
			fTempPerm5 = max(fTempPerm4, 23.448949682462139f);
			fTempPerm6 = max(20.0f, fabsf(fTempPerm5));
			fVec2[0] = fTempPerm6;
			fTempPerm7 = (fRec4[1] + (fConst4 * fVec2[1]));
			fRec4[0] = (fTempPerm7 - floorf(fTempPerm7));
			fTempPerm8 = faustpower<2>(((2 * fRec4[0]) + -1));
			fVec3[0] = fTempPerm8;
			fTempPerm9 = ((iVec0[1] * (fVec3[0] - fVec3[1])) / fVec2[0]);
			fVec4[IOTA&4095] = fTempPerm9;
			fTempPerm10 = max((float)0, min((float)2047, (fConst5 / fTempPerm5)));
			iTempPerm11 = int(fTempPerm10);
			fTempPerm12 = floorf(fTempPerm10);
			fTempPerm13 = (fConst3 * ((fVec4[IOTA&4095] - (fVec4[(IOTA-iTempPerm11)&4095] * (fTempPerm12 + (1 - fTempPerm10)))) - ((fTempPerm10 - fTempPerm12) * fVec4[(IOTA-int((iTempPerm11 + 1)))&4095])));
			fRec6[0] = ((0.999f * fRec6[1]) + fTempPerm13);
			fTempPerm14 = (fSlow11 * fRec5[0]);
			fTempPerm15 = sinf(fTempPerm14);
			fTempPerm16 = cosf(fTempPerm14);
			fRec7[0] = ((fRec8[1] * fTempPerm15) + (fRec7[1] * fTempPerm16));
			fRec8[0] = (((fRec8[1] * fTempPerm16) + (fRec7[1] * (0 - fTempPerm15))) + (1 - iVec0[1]));
			fTempPerm17 = float(max(9.9999999999999995e-08f, fabsf(fTempPerm4)));
			fTempPerm18 = (fRec9[1] + (fConst8 * fTempPerm17));
			fTempPerm19 = (fTempPerm18 + -1);
			iTempPerm20 = int((fTempPerm19 < 0));
			fRec9[0] = ((iTempPerm20)?fTempPerm18:fTempPerm19);
			float 	fRec10 = ((iTempPerm20)?fTempPerm18:(fTempPerm18 + ((1 - (fConst2 / fTempPerm17)) * fTempPerm19)));
			fTempPerm21 = (((iSlow4)?fTempPerm13:0) + (((iSlow8)?(fSlow9 * (fRec5[0] * fRec6[0])):0) + (((iSlow10)?fRec7[0]:0) + ((iSlow12)?((2 * fRec10) + -1):0))));
			fVec5[0] = fTempPerm21;
			fRec2[0] = ((fRec2[1] * (0 - ((1 - fTempPerm1) / fTempPerm2))) + ((fVec5[0] + fVec5[1]) / fTempPerm2));
			fTempPerm22 = (((fTempPerm1 + 1.0000000000000002f) / fTempPerm0) + 1);
			fRec1[0] = (fRec2[0] - (((fRec1[2] * (((fTempPerm1 + -1.0000000000000002f) / fTempPerm0) + 1)) + (2 * (fRec1[1] * (1 - (1.0f / faustpower<2>(fTempPerm0)))))) / fTempPerm22));
			fTempPerm23 = ((fRec0[0] * (fRec1[2] + (fRec1[0] + (2.0f * fRec1[1])))) / fTempPerm22);
			output0[i] = (FAUSTFLOAT)fTempPerm23;
			output1[i] = (FAUSTFLOAT)fTempPerm23;
			// post processing
			fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fVec5[1] = fVec5[0];
			fRec9[1] = fRec9[0];
			fRec8[1] = fRec8[0];
			fRec7[1] = fRec7[0];
			fRec6[1] = fRec6[0];
			IOTA = IOTA+1;
			fVec3[1] = fVec3[0];
			fRec4[1] = fRec4[0];
			fVec2[1] = fVec2[0];
			fRec5[1] = fRec5[0];
			fRec3[1] = fRec3[0];
			fRec0[1] = fRec0[0];
			fVec1[1] = fVec1[0];
			iVec0[1] = iVec0[0];
		}
	}
};


