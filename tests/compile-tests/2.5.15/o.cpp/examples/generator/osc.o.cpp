//----------------------------------------------------------
// author: "Grame"
// copyright: "(c)GRAME 2009"
// license: "BSD"
// name: "osc"
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
	float 	fConst0;
	FAUSTFLOAT 	fslider0;
	int 	iVec0[2];
	float 	fRec0[2];
	float 	fRec1[2];
	FAUSTFLOAT 	fslider1;
	float 	fRec2[2];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("author", "Grame");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("copyright", "(c)GRAME 2009");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("license", "BSD");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "osc");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() { return 0; }
	virtual int getNumOutputs() { return 1; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = (6.2831853071795862f / min(192000.0f, max(1.0f, (float)fSamplingFreq)));
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 1000.0f;
		fslider1 = 0.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) iVec0[i] = 0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
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
		ui_interface->openVerticalBox("Oscillator");
		ui_interface->declare(&fslider0, "unit", "Hz");
		ui_interface->addHorizontalSlider("freq", &fslider0, 1000.0f, 20.0f, 24000.0f, 1.0f);
		ui_interface->declare(&fslider1, "unit", "dB");
		ui_interface->addHorizontalSlider("volume", &fslider1, 0.0f, -96.0f, 0.0f, 0.10000000000000001f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = (fConst0 * float(fslider0));
		float 	fSlow1 = sinf(fSlow0);
		float 	fSlow2 = cosf(fSlow0);
		float 	fSlow3 = (0 - fSlow1);
		float 	fSlow4 = (0.0010000000000000009f * powf(10,(0.050000000000000003f * float(fslider1))));
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			iVec0[0] = 1;
			fRec0[0] = ((fSlow1 * fRec1[1]) + (fSlow2 * fRec0[1]));
			fRec1[0] = (((fSlow2 * fRec1[1]) + (fSlow3 * fRec0[1])) + (1 - iVec0[1]));
			fRec2[0] = (fSlow4 + (0.999f * fRec2[1]));
			output0[i] = (FAUSTFLOAT)(fRec0[0] * fRec2[0]);
			// post processing
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
			iVec0[1] = iVec0[0];
		}
	}
};


