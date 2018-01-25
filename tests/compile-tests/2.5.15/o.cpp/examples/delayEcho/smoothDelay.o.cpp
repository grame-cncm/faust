//----------------------------------------------------------
// author: "Yann Orlarey"
// copyright: "Grame"
// license: "STK-4.3"
// name: "smoothDelay"
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
	float 	fConst1;
	FAUSTFLOAT 	fslider0;
	float 	fConst2;
	FAUSTFLOAT 	fslider1;
	float 	fTempPerm0;
	float 	fRec1[2];
	float 	fRec2[2];
	float 	fRec3[2];
	float 	fRec4[2];
	float 	fTempPerm1;
	FAUSTFLOAT 	fslider2;
	float 	fTempPerm2;
	int 	IOTA;
	float 	fVec0[1048576];
	int 	iTempPerm3;
	int 	iTempPerm4;
	float 	fRec0[2];
	float 	fTempPerm5;
	float 	fVec1[1048576];
	float 	fRec5[2];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("author", "Yann Orlarey");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("copyright", "Grame");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("license", "STK-4.3");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "smoothDelay");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() { return 2; }
	virtual int getNumOutputs() { return 2; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(192000.0f, max(1.0f, (float)fSamplingFreq));
		fConst1 = (0.001f * fConst0);
		fConst2 = (1000.0f / fConst0);
		fTempPerm0 = 0;
		fTempPerm1 = 0;
		fTempPerm2 = 0;
		iTempPerm3 = 0;
		iTempPerm4 = 0;
		fTempPerm5 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.0f;
		fslider1 = 10.0f;
		fslider2 = 0.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		IOTA = 0;
		for (int i=0; i<1048576; i++) fVec0[i] = 0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<1048576; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
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
		ui_interface->openVerticalBox("smoothDelay");
		ui_interface->declare(&fslider0, "style", "knob");
		ui_interface->declare(&fslider0, "unit", "ms");
		ui_interface->addHorizontalSlider("delay", &fslider0, 0.0f, 0.0f, 5000.0f, 0.10000000000000001f);
		ui_interface->declare(&fslider2, "style", "knob");
		ui_interface->addHorizontalSlider("feedback", &fslider2, 0.0f, 0.0f, 100.0f, 0.10000000000000001f);
		ui_interface->declare(&fslider1, "style", "knob");
		ui_interface->declare(&fslider1, "unit", "ms");
		ui_interface->addHorizontalSlider("interpolation", &fslider1, 10.0f, 1.0f, 100.0f, 0.10000000000000001f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = (fConst1 * float(fslider0));
		float 	fSlow1 = (fConst2 / float(fslider1));
		float 	fSlow2 = (0 - fSlow1);
		float 	fSlow3 = (0.01f * float(fslider2));
		//zone2b
		//zone3
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* input1 = input[1];
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fTempPerm0 = ((int((fRec1[1] != 0.0f)))?((int(((fRec2[1] > 0.0f) & (fRec2[1] < 1.0f))))?fRec1[1]:0):((int(((fRec2[1] == 0.0f) & (fSlow0 != fRec3[1]))))?fSlow1:((int(((fRec2[1] == 1.0f) & (fSlow0 != fRec4[1]))))?fSlow2:0)));
			fRec1[0] = fTempPerm0;
			fRec2[0] = max(0.0f, min(1.0f, (fRec2[1] + fTempPerm0)));
			fRec3[0] = ((int(((fRec2[1] >= 1.0f) & (fRec4[1] != fSlow0))))?fSlow0:fRec3[1]);
			fRec4[0] = ((int(((fRec2[1] <= 0.0f) & (fRec3[1] != fSlow0))))?fSlow0:fRec4[1]);
			fTempPerm1 = (1.0f - fRec2[0]);
			fTempPerm2 = ((float)input0[i] + (fSlow3 * fRec0[1]));
			fVec0[IOTA&1048575] = fTempPerm2;
			iTempPerm3 = int(min((float)524288, max((float)0, fRec3[0])));
			iTempPerm4 = int(min((float)524288, max((float)0, fRec4[0])));
			fRec0[0] = ((fTempPerm1 * fVec0[(IOTA-iTempPerm3)&1048575]) + (fRec2[0] * fVec0[(IOTA-iTempPerm4)&1048575]));
			output0[i] = (FAUSTFLOAT)fRec0[0];
			fTempPerm5 = ((float)input1[i] + (fSlow3 * fRec5[1]));
			fVec1[IOTA&1048575] = fTempPerm5;
			fRec5[0] = ((fTempPerm1 * fVec1[(IOTA-iTempPerm3)&1048575]) + (fRec2[0] * fVec1[(IOTA-iTempPerm4)&1048575]));
			output1[i] = (FAUSTFLOAT)fRec5[0];
			// post processing
			fRec5[1] = fRec5[0];
			fRec0[1] = fRec0[0];
			IOTA = IOTA+1;
			fRec4[1] = fRec4[0];
			fRec3[1] = fRec3[0];
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
		}
	}
};


