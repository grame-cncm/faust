//----------------------------------------------------------
// author: "Grame"
// copyright: "(c)GRAME 2006"
// license: "BSD"
// name: "vumeter"
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
	float 	fTempPerm0;
	float 	fRec0[2];
	FAUSTFLOAT 	fbargraph0;
	float 	fTempPerm1;
	float 	fRec1[2];
	FAUSTFLOAT 	fbargraph1;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("author", "Grame");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("copyright", "(c)GRAME 2006");
		m->declare("license", "BSD");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "vumeter");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() { return 2; }
	virtual int getNumOutputs() { return 2; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = (1.0f / min(192000.0f, max(1.0f, (float)fSamplingFreq)));
		fTempPerm0 = 0;
		fTempPerm1 = 0;
	}
	virtual void instanceResetUserInterface() {
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
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
		ui_interface->openVerticalBox("vumeter");
		ui_interface->declare(&fbargraph0, "2", "");
		ui_interface->declare(&fbargraph0, "unit", "dB");
		ui_interface->addHorizontalBargraph("0x7fb46943a810", &fbargraph0, -70.0f, 5.0f);
		ui_interface->declare(&fbargraph1, "2", "");
		ui_interface->declare(&fbargraph1, "unit", "dB");
		ui_interface->addHorizontalBargraph("0x7fb46943c010", &fbargraph1, -70.0f, 5.0f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		//zone2b
		//zone3
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* input1 = input[1];
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fTempPerm0 = (float)input0[i];
			fRec0[0] = max((fRec0[1] - fConst0), fabsf(fTempPerm0));
			fbargraph0 = (20 * log10f(max(0.00031622776601683794f, fRec0[0])));
			output0[i] = (FAUSTFLOAT)fTempPerm0;
			fTempPerm1 = (float)input1[i];
			fRec1[0] = max((fRec1[1] - fConst0), fabsf(fTempPerm1));
			fbargraph1 = (20 * log10f(max(0.00031622776601683794f, fRec1[0])));
			output1[i] = (FAUSTFLOAT)fTempPerm1;
			// post processing
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
		}
	}
};


