//----------------------------------------------------------
// author: "JOS, revised by RM"
// name: "filterOSC"
// version: "0.0"
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
	FAUSTFLOAT 	fslider0;
	int 	iVec0[2];
	float 	fRec0[2];
	float 	fConst0;
	float 	fConst1;
	FAUSTFLOAT 	fslider1;
	float 	fConst2;
	FAUSTFLOAT 	fslider2;
	float 	fRec3[2];
	float 	fTempPerm0;
	float 	fTempPerm1;
	float 	fTempPerm2;
	float 	fRec1[2];
	float 	fRec2[2];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("author", "JOS, revised by RM");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("description", "Simple application demoing filter based oscillators.");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "filterOSC");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("version", "0.0");
	}

	virtual int getNumInputs() { return 0; }
	virtual int getNumOutputs() { return 1; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(192000.0f, max(1.0f, (float)fSamplingFreq));
		fConst1 = (6.2831853071795862f / fConst0);
		fConst2 = (1.0f / fConst0);
		fTempPerm0 = 0;
		fTempPerm1 = 0;
		fTempPerm2 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = -20.0f;
		fslider1 = 49.0f;
		fslider2 = 0.10000000000000001f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) iVec0[i] = 0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
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
		ui_interface->declare(0, "0", "");
		ui_interface->declare(0, "tooltip", "Sine oscillator based   on 2D vector rotation");
		ui_interface->openVerticalBox("SINE WAVE OSCILLATOR oscrs");
		ui_interface->declare(&fslider0, "1", "");
		ui_interface->declare(&fslider0, "tooltip", "Sawtooth waveform   amplitude");
		ui_interface->declare(&fslider0, "unit", "dB");
		ui_interface->addHorizontalSlider("Amplitude", &fslider0, -20.0f, -120.0f, 10.0f, 0.10000000000000001f);
		ui_interface->declare(&fslider1, "2", "");
		ui_interface->declare(&fslider1, "tooltip", "Sine wave frequency as a Piano Key (PK) number (A440 = 49 PK)");
		ui_interface->declare(&fslider1, "unit", "PK");
		ui_interface->addHorizontalSlider("Frequency", &fslider1, 49.0f, 1.0f, 88.0f, 0.01f);
		ui_interface->declare(&fslider2, "3", "");
		ui_interface->declare(&fslider2, "scale", "log");
		ui_interface->declare(&fslider2, "tooltip", "Portamento (frequency-glide) time-constant in seconds");
		ui_interface->declare(&fslider2, "unit", "sec");
		ui_interface->addHorizontalSlider("Portamento", &fslider2, 0.10000000000000001f, 0.001f, 10.0f, 0.001f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = (0.0010000000000000009f * powf(10,(0.050000000000000003f * float(fslider0))));
		float 	fSlow1 = expf((0 - (fConst2 / float(fslider2))));
		float 	fSlow2 = (440.0f * (powf(2.0f,(0.083333333333333329f * (float(fslider1) + -49.0f))) * (1.0f - fSlow1)));
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			iVec0[0] = 1;
			fRec0[0] = (fSlow0 + (0.999f * fRec0[1]));
			fRec3[0] = (fSlow2 + (fSlow1 * fRec3[1]));
			fTempPerm0 = (fConst1 * fRec3[0]);
			fTempPerm1 = sinf(fTempPerm0);
			fTempPerm2 = cosf(fTempPerm0);
			fRec1[0] = ((fRec2[1] * fTempPerm1) + (fRec1[1] * fTempPerm2));
			fRec2[0] = (((fRec2[1] * fTempPerm2) + (fRec1[1] * (0 - fTempPerm1))) + (1 - iVec0[1]));
			output0[i] = (FAUSTFLOAT)(fRec0[0] * fRec1[0]);
			// post processing
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
			fRec3[1] = fRec3[0];
			fRec0[1] = fRec0[0];
			iVec0[1] = iVec0[0];
		}
	}
};


