//----------------------------------------------------------
// name: "path2"
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
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT 	fslider4;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("name", "path2");
	}

	virtual int getNumInputs() { return 4; }
	virtual int getNumOutputs() { return 4; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.0f;
		fslider1 = 0.0f;
		fslider2 = 0.0f;
		fslider3 = 0.0f;
		fslider4 = 0.0f;
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
		ui_interface->openTabBox("toto");
		ui_interface->addHorizontalSlider("common", &fslider1, 0.0f, 0.0f, 1.0f, 0.10000000000000001f);
		ui_interface->openVerticalBox("foo 0");
		ui_interface->addHorizontalSlider("slid", &fslider0, 0.0f, 0.0f, 1.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("foo 1");
		ui_interface->addHorizontalSlider("slid", &fslider2, 0.0f, 0.0f, 1.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("foo 2");
		ui_interface->addHorizontalSlider("slid", &fslider3, 0.0f, 0.0f, 1.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("foo 3");
		ui_interface->addHorizontalSlider("slid", &fslider4, 0.0f, 0.0f, 1.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = float(fslider1);
		float 	fSlow1 = (float(fslider0) * fSlow0);
		float 	fSlow2 = (fSlow0 * float(fslider2));
		float 	fSlow3 = (fSlow0 * float(fslider3));
		float 	fSlow4 = (fSlow0 * float(fslider4));
		//zone2b
		//zone3
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* input1 = input[1];
		FAUSTFLOAT* input2 = input[2];
		FAUSTFLOAT* input3 = input[3];
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		FAUSTFLOAT* output2 = output[2];
		FAUSTFLOAT* output3 = output[3];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			output0[i] = (FAUSTFLOAT)(fSlow1 * (float)input0[i]);
			output1[i] = (FAUSTFLOAT)(fSlow2 * (float)input1[i]);
			output2[i] = (FAUSTFLOAT)(fSlow3 * (float)input2[i]);
			output3[i] = (FAUSTFLOAT)(fSlow4 * (float)input3[i]);
		}
	}
};


