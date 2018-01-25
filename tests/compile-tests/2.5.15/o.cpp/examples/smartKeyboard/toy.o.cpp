//----------------------------------------------------------
// name: "toy"
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
	float 	fRec1[2];
	float 	fConst0;
	FAUSTFLOAT 	fslider1;
	float 	fRec2[2];
	float 	fConst1;
	FAUSTFLOAT 	fslider2;
	float 	fRec5[2];
	float 	fVec0[2];
	float 	fTempPerm0;
	float 	fRec4[2];
	float 	fConst2;
	FAUSTFLOAT 	fslider3;
	float 	fRec6[2];
	float 	fTempPerm1;
	float 	fTempPerm2;
	FAUSTFLOAT 	fslider4;
	float 	fRec7[2];
	float 	fTempPerm3;
	float 	fTempPerm4;
	float 	fRec3[3];
	int 	IOTA;
	float 	fRec0[131072];
	FAUSTFLOAT 	fslider5;
	float 	fRec8[2];
	float 	fTempPerm5;
	float 	fTempPerm6;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("interface", "SmartKeyboard{  'Number of Keyboards':'1',  'Max Keyboard Polyphony':'0',  'Keyboard 0 - Number of Keys':'1',  'Keyboard 0 - Send Freq':'0',  'Keyboard 0 - Static Mode':'1',  'Keyboard 0 - Piano Keyboard':'0',  'Keyboard 0 - Send Numbered X':'1',  'Keyboard 0 - Send Numbered Y':'1' }");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("misceffects.lib/name", "Faust Math Library");
		m->declare("misceffects.lib/version", "2.0");
		m->declare("name", "toy");
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
		fConst1 = (1.0f / fConst0);
		fTempPerm0 = 0;
		fConst2 = (3.1415926535897931f / fConst0);
		fTempPerm1 = 0;
		fTempPerm2 = 0;
		fTempPerm3 = 0;
		fTempPerm4 = 0;
		fTempPerm5 = 0;
		fTempPerm6 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.5f;
		fslider1 = 0.5f;
		fslider2 = 0.5f;
		fslider3 = 0.5f;
		fslider4 = 30.0f;
		fslider5 = 0.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) fVec0[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<2; i++) fRec7[i] = 0;
		for (int i=0; i<3; i++) fRec3[i] = 0;
		IOTA = 0;
		for (int i=0; i<131072; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fRec8[i] = 0;
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
		ui_interface->openVerticalBox("toy");
		ui_interface->declare(&fslider1, "acc", "0 0 -10 0 10");
		ui_interface->addHorizontalSlider("del", &fslider1, 0.5f, 0.01f, 1.0f, 0.01f);
		ui_interface->declare(&fslider0, "acc", "1 0 -10 0 10");
		ui_interface->addHorizontalSlider("fb", &fslider0, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider4, "acc", "0 0 -10 0 10");
		ui_interface->addHorizontalSlider("q", &fslider4, 30.0f, 10.0f, 50.0f, 0.01f);
		ui_interface->addHorizontalSlider("x0", &fslider2, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("y0", &fslider3, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("y1", &fslider5, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = (0.0010000000000000009f * float(fslider0));
		float 	fSlow1 = (0.0010000000000000009f * float(fslider1));
		float 	fSlow2 = (0.0010000000000000009f * float(fslider2));
		float 	fSlow3 = (0.0010000000000000009f * float(fslider3));
		float 	fSlow4 = (0.0010000000000000009f * float(fslider4));
		float 	fSlow5 = (0.0010000000000000009f * float(fslider5));
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fRec1[0] = (fSlow0 + (0.999f * fRec1[1]));
			fRec2[0] = (fSlow1 + (0.999f * fRec2[1]));
			fRec5[0] = (fSlow2 + (0.999f * fRec5[1]));
			fVec0[0] = ((20 * fRec5[0]) + 2);
			fTempPerm0 = (fRec4[1] + (fConst1 * fVec0[1]));
			fRec4[0] = (fTempPerm0 - floorf(fTempPerm0));
			fRec6[0] = (fSlow3 + (0.999f * fRec6[1]));
			fTempPerm1 = tanf((fConst2 * ((3000 * fRec6[0]) + 300)));
			fTempPerm2 = (1.0f / fTempPerm1);
			fRec7[0] = (fSlow4 + (0.999f * fRec7[1]));
			fTempPerm3 = (1.0f / fRec7[0]);
			fTempPerm4 = (((fTempPerm2 + fTempPerm3) / fTempPerm1) + 1);
			fRec3[0] = (((fRec4[0] - fRec4[1]) < 0) - (((fRec3[2] * (((fTempPerm2 - fTempPerm3) / fTempPerm1) + 1)) + (2 * (fRec3[1] * (1 - (1.0f / faustpower<2>(fTempPerm1)))))) / fTempPerm4));
			fRec0[IOTA&131071] = ((fRec1[0] * fRec0[(IOTA-int((int(min((float)65536, max((float)0, (fConst0 * fRec2[0])))) + 1)))&131071]) + ((fRec3[2] + (fRec3[0] + (2.0f * fRec3[1]))) / fTempPerm4));
			fRec8[0] = (fSlow5 + (0.999f * fRec8[1]));
			fTempPerm5 = max((float)-1, min((float)1, (fRec0[(IOTA-0)&131071] * powf(10.0f,(2 * fRec8[0])))));
			fTempPerm6 = (0.94999999999999996f * (fTempPerm5 * (1 - (0.33333333333333331f * faustpower<2>(fTempPerm5)))));
			output0[i] = (FAUSTFLOAT)fTempPerm6;
			output1[i] = (FAUSTFLOAT)fTempPerm6;
			// post processing
			fRec8[1] = fRec8[0];
			IOTA = IOTA+1;
			fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
			fRec7[1] = fRec7[0];
			fRec6[1] = fRec6[0];
			fRec4[1] = fRec4[0];
			fVec0[1] = fVec0[0];
			fRec5[1] = fRec5[0];
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
		}
	}
};


