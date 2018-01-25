//----------------------------------------------------------
// name: "cryBaby"
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
	FAUSTFLOAT 	fcheckbox0;
	float 	fTempPerm0;
	FAUSTFLOAT 	fslider0;
	float 	fRec1[2];
	float 	fConst0;
	float 	fConst1;
	float 	fConst2;
	float 	fRec2[2];
	float 	fRec3[2];
	float 	fRec0[3];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("description", "Application demonstrating the CryBaby wah pedal emulation");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "cryBaby");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("vaeffects.lib/name", "Faust Virtual Analog Filter Effect Library");
		m->declare("vaeffects.lib/version", "0.0");
	}

	virtual int getNumInputs() { return 1; }
	virtual int getNumOutputs() { return 1; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fTempPerm0 = 0;
		fConst0 = min(192000.0f, max(1.0f, (float)fSamplingFreq));
		fConst1 = (1413.7166941154069f / fConst0);
		fConst2 = (2827.4333882308138f / fConst0);
	}
	virtual void instanceResetUserInterface() {
		fcheckbox0 = 0.0;
		fslider0 = 0.80000000000000004f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
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
		ui_interface->declare(0, "tooltip", "Reference:   https://ccrma.stanford.edu/~jos/pasp/vegf.html");
		ui_interface->openHorizontalBox("CRYBABY");
		ui_interface->declare(&fcheckbox0, "0", "");
		ui_interface->declare(&fcheckbox0, "tooltip", "When this is checked, the wah   pedal has no effect");
		ui_interface->addCheckButton("Bypass", &fcheckbox0);
		ui_interface->declare(&fslider0, "1", "");
		ui_interface->declare(&fslider0, "tooltip", "wah pedal angle between   0 (rocked back) and 1 (rocked forward)");
		ui_interface->addHorizontalSlider("Wah parameter", &fslider0, 0.80000000000000004f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		int 	iSlow0 = int(float(fcheckbox0));
		float 	fSlow1 = float(fslider0);
		float 	fSlow2 = (0.0001000000000000001f * powf(4.0f,fSlow1));
		float 	fSlow3 = powf(2.0f,(2.2999999999999998f * fSlow1));
		float 	fSlow4 = (1 - (fConst1 * (fSlow3 / powf(2.0f,((2.0f * (1.0f - fSlow1)) + 1.0f)))));
		float 	fSlow5 = (0.0010000000000000009f * (0 - (2.0f * (fSlow4 * cosf((fConst2 * fSlow3))))));
		float 	fSlow6 = (0.0010000000000000009f * faustpower<2>(fSlow4));
		//zone2b
		//zone3
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* output0 = output[0];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fTempPerm0 = (float)input0[i];
			fRec1[0] = (fSlow2 + (0.999f * fRec1[1]));
			fRec2[0] = (fSlow5 + (0.999f * fRec2[1]));
			fRec3[0] = (fSlow6 + (0.999f * fRec3[1]));
			fRec0[0] = ((((iSlow0)?0:fTempPerm0) * fRec1[0]) - ((fRec2[0] * fRec0[1]) + (fRec3[0] * fRec0[2])));
			output0[i] = (FAUSTFLOAT)((iSlow0)?fTempPerm0:(fRec0[0] - fRec0[1]));
			// post processing
			fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
			fRec3[1] = fRec3[0];
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
		}
	}
};


