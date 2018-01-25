//----------------------------------------------------------
// author: "Grame"
// copyright: "(c)GRAME 2006"
// license: "BSD"
// name: "pitchShifter"
// version: "1.0"
//
// Code generated with Faust 2.5.15 (https://faust.grame.fr)
//----------------------------------------------------------

/* link with  */
#include <math.h>

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
	float 	fTempPerm0;
	int 	IOTA;
	float 	fVec0[131072];
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fslider1;
	float 	fRec0[2];
	int 	iTempPerm1;
	float 	fTempPerm2;
	float 	fTempPerm3;
	FAUSTFLOAT 	fslider2;
	float 	fTempPerm4;
	float 	fTempPerm5;
	int 	iTempPerm6;
	float 	fTempPerm7;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("author", "Grame");
		m->declare("copyright", "(c)GRAME 2006");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("license", "BSD");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("misceffects.lib/name", "Faust Math Library");
		m->declare("misceffects.lib/version", "2.0");
		m->declare("name", "pitchShifter");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() { return 1; }
	virtual int getNumOutputs() { return 1; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fTempPerm0 = 0;
		iTempPerm1 = 0;
		fTempPerm2 = 0;
		fTempPerm3 = 0;
		fTempPerm4 = 0;
		fTempPerm5 = 0;
		iTempPerm6 = 0;
		fTempPerm7 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 1000.0f;
		fslider1 = 0.0f;
		fslider2 = 10.0f;
	}
	virtual void instanceClear() {
		IOTA = 0;
		for (int i=0; i<131072; i++) fVec0[i] = 0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
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
		ui_interface->openVerticalBox("Pitch Shifter");
		ui_interface->addHorizontalSlider("shift (semitones)", &fslider1, 0.0f, -12.0f, 12.0f, 0.10000000000000001f);
		ui_interface->addHorizontalSlider("window (samples)", &fslider0, 1000.0f, 50.0f, 10000.0f, 1.0f);
		ui_interface->addHorizontalSlider("xfade (samples)", &fslider2, 10.0f, 1.0f, 10000.0f, 1.0f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = float(fslider0);
		float 	fSlow1 = powf(2,(0.083333333333333329f * float(fslider1)));
		float 	fSlow2 = (1.0f / float(fslider2));
		//zone2b
		//zone3
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* output0 = output[0];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fTempPerm0 = (float)input0[i];
			fVec0[IOTA&131071] = fTempPerm0;
			fRec0[0] = fmodf((fSlow0 + ((fRec0[1] + 1) - fSlow1)),fSlow0);
			iTempPerm1 = int(fRec0[0]);
			fTempPerm2 = floorf(fRec0[0]);
			fTempPerm3 = (1 - fRec0[0]);
			fTempPerm4 = min((fSlow2 * fRec0[0]), (float)1);
			fTempPerm5 = (fSlow0 + fRec0[0]);
			iTempPerm6 = int(fTempPerm5);
			fTempPerm7 = floorf(fTempPerm5);
			output0[i] = (FAUSTFLOAT)((((fVec0[(IOTA-int(min(65537, max(0, iTempPerm1))))&131071] * (fTempPerm2 + fTempPerm3)) + ((fRec0[0] - fTempPerm2) * fVec0[(IOTA-int(min(65537, max(0, (iTempPerm1 + 1)))))&131071])) * fTempPerm4) + (((fVec0[(IOTA-int(min(65537, max(0, iTempPerm6))))&131071] * ((fTempPerm7 + fTempPerm3) - fSlow0)) + ((fSlow0 + (fRec0[0] - fTempPerm7)) * fVec0[(IOTA-int(min(65537, max(0, (iTempPerm6 + 1)))))&131071])) * (1 - fTempPerm4)));
			// post processing
			fRec0[1] = fRec0[0];
			IOTA = IOTA+1;
		}
	}
};


