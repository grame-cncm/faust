//----------------------------------------------------------
// name: "test16"
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
	int 	iRec0[2];
	float 	fRec1[2];
	float 	fRec2[2];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("name", "test16");
	}

	virtual int getNumInputs() { return 0; }
	virtual int getNumOutputs() { return 3; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
	}
	virtual void instanceResetUserInterface() {
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) iRec0[i] = 0;
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
		ui_interface->openVerticalBox("test16");
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		FAUSTFLOAT* output2 = output[2];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			iRec0[0] = (iRec0[1] + 1);
			output0[i] = (FAUSTFLOAT)iRec0[1];
			fRec1[0] = (fRec1[1] + -0.22400000000000003f);
			output1[i] = (FAUSTFLOAT)(fRec1[1] + 1.008f);
			fRec2[0] = ((fRec1[1] + fRec2[1]) + 1.008f);
			output2[i] = (FAUSTFLOAT)max(0.0f, fRec2[1]);
			// post processing
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
			iRec0[1] = iRec0[0];
		}
	}
};


