//----------------------------------------------------------
// name: "highShelf"
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
	float 	fConst0;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
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
		m->declare("name", "highShelf");
	}

	virtual int getNumInputs() { return 1; }
	virtual int getNumOutputs() { return 1; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = (6.2831853071795862f / min(192000.0f, max(1.0f, (float)fSamplingFreq)));
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.0f;
		fslider1 = 1000.0f;
		fslider2 = 1.0f;
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
		ui_interface->openVerticalBox("highShelf");
		ui_interface->addHorizontalSlider("Freq", &fslider1, 1000.0f, 100.0f, 10000.0f, 1.0f);
		ui_interface->declare(&fslider0, "unit", "dB");
		ui_interface->addHorizontalSlider("Gain", &fslider0, 0.0f, -10.0f, 10.0f, 0.10000000000000001f);
		ui_interface->addHorizontalSlider("Q", &fslider2, 1.0f, 0.01f, 100.0f, 0.01f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = powf(10,(0.025000000000000001f * float(fslider0)));
		float 	fSlow1 = (fConst0 * max((float)0, float(fslider1)));
		float 	fSlow2 = ((sqrtf(fSlow0) * sinf(fSlow1)) / max(0.001f, float(fslider2)));
		float 	fSlow3 = cosf(fSlow1);
		float 	fSlow4 = ((fSlow0 + -1) * fSlow3);
		float 	fSlow5 = (1.0f / ((fSlow0 + fSlow2) + (1 - fSlow4)));
		float 	fSlow6 = (fSlow0 + fSlow4);
		float 	fSlow7 = (fSlow0 * ((fSlow2 + fSlow6) + 1));
		float 	fSlow8 = (fSlow0 + (1 - (fSlow4 + fSlow2)));
		float 	fSlow9 = ((fSlow0 + 1) * fSlow3);
		float 	fSlow10 = (2 * (fSlow0 + (-1 - fSlow9)));
		float 	fSlow11 = ((0 - (2 * fSlow0)) * ((fSlow0 + fSlow9) + -1));
		float 	fSlow12 = (fSlow0 * (fSlow6 + (1 - fSlow2)));
		//zone2b
		//zone3
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* output0 = output[0];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fRec0[0] = ((float)input0[i] - (fSlow5 * ((fSlow8 * fRec0[2]) + (fSlow10 * fRec0[1]))));
			output0[i] = (FAUSTFLOAT)(fSlow5 * (((fSlow7 * fRec0[0]) + (fSlow11 * fRec0[1])) + (fSlow12 * fRec0[2])));
			// post processing
			fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		}
	}
};


