//----------------------------------------------------------
// author: "Grame"
// copyright: "(c)GRAME 2007"
// license: "BSD"
// name: "quadEcho"
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
	FAUSTFLOAT 	fslider0;
	float 	fConst0;
	FAUSTFLOAT 	fslider1;
	int 	IOTA;
	float 	fRec0[131072];
	float 	fRec1[131072];
	float 	fRec2[131072];
	float 	fRec3[131072];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("author", "Grame");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("copyright", "(c)GRAME 2007");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("license", "BSD");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("misceffects.lib/name", "Faust Math Library");
		m->declare("misceffects.lib/version", "2.0");
		m->declare("name", "quadEcho");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() { return 4; }
	virtual int getNumOutputs() { return 4; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = (0.001f * min(192000.0f, max(1.0f, (float)fSamplingFreq)));
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.0f;
		fslider1 = 0.0f;
	}
	virtual void instanceClear() {
		IOTA = 0;
		for (int i=0; i<131072; i++) fRec0[i] = 0;
		for (int i=0; i<131072; i++) fRec1[i] = 0;
		for (int i=0; i<131072; i++) fRec2[i] = 0;
		for (int i=0; i<131072; i++) fRec3[i] = 0;
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
		ui_interface->openVerticalBox("stereo echo");
		ui_interface->openVerticalBox("echo  1000");
		ui_interface->addHorizontalSlider("feedback", &fslider0, 0.0f, 0.0f, 100.0f, 0.10000000000000001f);
		ui_interface->addHorizontalSlider("millisecond", &fslider1, 0.0f, 0.0f, 1000.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = (0.01f * float(fslider0));
		int 	iSlow1 = int((int(min(65536, max(0, (int((fConst0 * float(fslider1))) + -1)))) + 1));
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
			fRec0[IOTA&131071] = ((float)input0[i] + (fSlow0 * fRec0[(IOTA-iSlow1)&131071]));
			output0[i] = (FAUSTFLOAT)fRec0[(IOTA-0)&131071];
			fRec1[IOTA&131071] = ((float)input1[i] + (fSlow0 * fRec1[(IOTA-iSlow1)&131071]));
			output1[i] = (FAUSTFLOAT)fRec1[(IOTA-0)&131071];
			fRec2[IOTA&131071] = ((float)input2[i] + (fSlow0 * fRec2[(IOTA-iSlow1)&131071]));
			output2[i] = (FAUSTFLOAT)fRec2[(IOTA-0)&131071];
			fRec3[IOTA&131071] = ((float)input3[i] + (fSlow0 * fRec3[(IOTA-iSlow1)&131071]));
			output3[i] = (FAUSTFLOAT)fRec3[(IOTA-0)&131071];
			// post processing
			IOTA = IOTA+1;
		}
	}
};


