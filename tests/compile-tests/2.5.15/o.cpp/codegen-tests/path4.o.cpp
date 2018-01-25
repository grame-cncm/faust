//----------------------------------------------------------
// name: "path4"
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
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("name", "path4");
	}

	virtual int getNumInputs() { return 0; }
	virtual int getNumOutputs() { return 1; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.0f;
		fslider1 = 0.0f;
		fslider2 = 0.0f;
	}
	virtual void instanceClear() {
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
		ui_interface->openVerticalBox("foo");
		ui_interface->openHorizontalBox("faa");
		ui_interface->addHorizontalSlider("slid2", &fslider1, 0.0f, 0.0f, 1.0f, 0.10000000000000001f);
		ui_interface->addHorizontalSlider("slid3", &fslider2, 0.0f, 0.0f, 1.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->addHorizontalSlider("slid1", &fslider0, 0.0f, 0.0f, 1.0f, 0.10000000000000001f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = ((float(fslider0) + float(fslider1)) + float(fslider2));
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			output0[i] = (FAUSTFLOAT)fSlow0;
		}
	}
};


