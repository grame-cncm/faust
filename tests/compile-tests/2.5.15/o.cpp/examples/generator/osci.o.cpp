//----------------------------------------------------------
// author: "Grame"
// copyright: "(c)GRAME 2009"
// license: "BSD"
// name: "osci"
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
	class SIG0 {
	  private:
		int fSamplingFreq;
		int 	iRec1[2];
		float 	fTempPerm0;
	  public:
		int getNumInputs() { return 0; }
		int getNumOutputs() { return 1; }
		void init(int samplingFreq) {
			fSamplingFreq = samplingFreq;
			fTempPerm0 = 0;
			for (int i=0; i<2; i++) iRec1[i] = 0;
		}
		void fill (int count, float output[]) {
			for (int i=0; i<count; i++) {
				iRec1[0] = (iRec1[1] + 1);
				fTempPerm0 = sinf((9.5873799242852573e-05f * float((iRec1[0] + -1))));
				output[i] = fTempPerm0;
				// post processing
				iRec1[1] = iRec1[0];
			}
		}
	};


	FAUSTFLOAT 	fslider0;
	float 	fRec0[2];
	static float 	ftbl0[65537];
	float 	fConst0;
	FAUSTFLOAT 	fslider1;
	float 	fRec2[2];
	float 	fTempPerm1;
	int 	iTempPerm2;
	float 	fTempPerm3;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("author", "Grame");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("copyright", "(c)GRAME 2009");
		m->declare("license", "BSD");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "osci");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() { return 0; }
	virtual int getNumOutputs() { return 1; }
	static void classInit(int samplingFreq) {
		SIG0 sig0;
		sig0.init(samplingFreq);
		sig0.fill(65537,ftbl0);
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = (1.0f / float(min(192000.0f, max(1.0f, (float)fSamplingFreq))));
		fTempPerm1 = 0;
		iTempPerm2 = 0;
		fTempPerm3 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.0f;
		fslider1 = 1000.0f;
	}
	virtual void instanceClear() {
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
		ui_interface->openVerticalBox("Oscillator");
		ui_interface->declare(&fslider1, "unit", "Hz");
		ui_interface->addHorizontalSlider("freq", &fslider1, 1000.0f, 20.0f, 24000.0f, 1.0f);
		ui_interface->declare(&fslider0, "unit", "dB");
		ui_interface->addHorizontalSlider("volume", &fslider0, 0.0f, -96.0f, 0.0f, 0.10000000000000001f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = (0.0010000000000000009f * powf(10,(0.050000000000000003f * float(fslider0))));
		float 	fSlow1 = (fConst0 * float(fslider1));
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fRec0[0] = (fSlow0 + (0.999f * fRec0[1]));
			fRec2[0] = (fSlow1 + (fRec2[1] - floorf((fSlow1 + fRec2[1]))));
			fTempPerm1 = (65536.0f * fRec2[0]);
			iTempPerm2 = int(fTempPerm1);
			fTempPerm3 = ftbl0[iTempPerm2];
			output0[i] = (FAUSTFLOAT)(fRec0[0] * (fTempPerm3 + ((fTempPerm1 - floorf(fTempPerm1)) * (ftbl0[(iTempPerm2 + 1)] - fTempPerm3))));
			// post processing
			fRec2[1] = fRec2[0];
			fRec0[1] = fRec0[0];
		}
	}
};


float 	mydsp::ftbl0[65537];
