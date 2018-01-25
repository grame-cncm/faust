//----------------------------------------------------------
// name: "peakingEQ"
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
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	float 	fTempPerm0;
	float 	fRec0[3];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("maxmsp.lib/author", "GRAME");
		m->declare("maxmsp.lib/copyright", "GRAME");
		m->declare("maxmsp.lib/license", "LGPL");
		m->declare("maxmsp.lib/name", "MaxMSP compatibility Library");
		m->declare("maxmsp.lib/version", "1.1");
		m->declare("name", "peakingEQ");
	}

	virtual int getNumInputs() { return 1; }
	virtual int getNumOutputs() { return 1; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = (6.2831853071795862f / min(192000.0f, max(1.0f, (float)fSamplingFreq)));
		fTempPerm0 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 1000.0f;
		fslider1 = 1.0f;
		fslider2 = 0.0f;
	}
	virtual void instanceClear() {
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
		ui_interface->openVerticalBox("peakingEQ");
		ui_interface->addHorizontalSlider("Freq", &fslider0, 1000.0f, 100.0f, 10000.0f, 1.0f);
		ui_interface->declare(&fslider2, "unit", "dB");
		ui_interface->addHorizontalSlider("Gain", &fslider2, 0.0f, -10.0f, 10.0f, 0.10000000000000001f);
		ui_interface->addHorizontalSlider("Q", &fslider1, 1.0f, 0.01f, 100.0f, 0.01f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = (fConst0 * max((float)0, float(fslider0)));
		float 	fSlow1 = sinf(fSlow0);
		float 	fSlow2 = max(0.001f, float(fslider1));
		float 	fSlow3 = powf(10,(0.025000000000000001f * float(fslider2)));
		float 	fSlow4 = (0.5f * (fSlow1 / (fSlow2 * fSlow3)));
		float 	fSlow5 = (1.0f / (fSlow4 + 1));
		float 	fSlow6 = (0 - (2 * cosf(fSlow0)));
		float 	fSlow7 = (1 - fSlow4);
		float 	fSlow8 = (0.5f * ((fSlow1 * fSlow3) / fSlow2));
		float 	fSlow9 = (fSlow8 + 1);
		float 	fSlow10 = (1 - fSlow8);
		//zone2b
		//zone3
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* output0 = output[0];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fTempPerm0 = (fSlow6 * fRec0[1]);
			fRec0[0] = ((float)input0[i] - (fSlow5 * (fTempPerm0 + (fSlow7 * fRec0[2]))));
			output0[i] = (FAUSTFLOAT)(fSlow5 * ((fTempPerm0 + (fSlow9 * fRec0[0])) + (fSlow10 * fRec0[2])));
			// post processing
			fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		}
	}
};


