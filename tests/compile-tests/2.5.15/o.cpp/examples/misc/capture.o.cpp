//----------------------------------------------------------
// author: "Grame"
// copyright: "(c)GRAME 2006"
// license: "BSD"
// name: "capture"
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
	FAUSTFLOAT 	fbutton0;
	int 	IOTA;
	float 	fVec0[1048576];
	int 	iVec1[2];
	int 	iRec1[2];
	float 	fRec0[2];
	FAUSTFLOAT 	fslider0;
	float 	fRec2[2];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("author", "Grame");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("copyright", "(c)GRAME 2006");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("license", "BSD");
		m->declare("name", "capture");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() { return 1; }
	virtual int getNumOutputs() { return 1; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
	}
	virtual void instanceResetUserInterface() {
		fbutton0 = 0.0;
		fslider0 = 0.0f;
	}
	virtual void instanceClear() {
		IOTA = 0;
		for (int i=0; i<1048576; i++) fVec0[i] = 0;
		for (int i=0; i<2; i++) iVec1[i] = 0;
		for (int i=0; i<2; i++) iRec1[i] = 0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
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
		ui_interface->openVerticalBox("Audio Capture");
		ui_interface->addButton("Capture", &fbutton0);
		ui_interface->addHorizontalSlider("level (db)", &fslider0, 0.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = float(fbutton0);
		float 	fSlow1 = (1.0f - fSlow0);
		int 	iSlow2 = int(fSlow0);
		float 	fSlow3 = (0.0010000000000000009f * powf(10,(0.050000000000000003f * float(fslider0))));
		//zone2b
		//zone3
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* output0 = output[0];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fVec0[IOTA&1048575] = ((fSlow1 * fRec0[1]) + (fSlow0 * (float)input0[i]));
			iVec1[0] = iSlow2;
			iRec1[0] = ((iSlow2 + iRec1[1]) * ((iSlow2 - iVec1[1]) <= 0));
			fRec0[0] = fVec0[(IOTA-int(min(524288, (int)max(0, (int)(iRec1[0] + -1)))))&1048575];
			fRec2[0] = (fSlow3 + (0.999f * fRec2[1]));
			output0[i] = (FAUSTFLOAT)(fRec0[0] * fRec2[0]);
			// post processing
			fRec2[1] = fRec2[0];
			fRec0[1] = fRec0[0];
			iRec1[1] = iRec1[0];
			iVec1[1] = iVec1[0];
			IOTA = IOTA+1;
		}
	}
};


