//----------------------------------------------------------
// author: "Grame"
// copyright: "(c)GRAME 2006"
// license: "BSD"
// name: "dbmeter"
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
	int 	iConst1;
	float 	fTempPerm1;
	float 	fRec1[2];
	FAUSTFLOAT 	fbargraph1;
	int 	iConst2;
	float 	fTempPerm2;
	float 	fRec2[2];
	FAUSTFLOAT 	fbargraph2;
	int 	iConst3;
	float 	fTempPerm3;
	float 	fRec3[2];
	FAUSTFLOAT 	fbargraph3;
	int 	iConst4;
	float 	fTempPerm4;
	float 	fRec4[2];
	FAUSTFLOAT 	fbargraph4;
	int 	iConst5;
	float 	fTempPerm5;
	float 	fRec5[2];
	FAUSTFLOAT 	fbargraph5;
	int 	iConst6;
	float 	fTempPerm6;
	float 	fRec6[2];
	FAUSTFLOAT 	fbargraph6;
	int 	iConst7;
	float 	fTempPerm7;
	float 	fRec7[2];
	FAUSTFLOAT 	fbargraph7;
	int 	iConst8;
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
		m->declare("name", "dbmeter");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() { return 8; }
	virtual int getNumOutputs() { return 8; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = (80.0f / min(192000.0f, max(1.0f, (float)fSamplingFreq)));
		fTempPerm0 = 0;
		iConst1 = 0;
		fTempPerm1 = 0;
		iConst2 = 0;
		fTempPerm2 = 0;
		iConst3 = 0;
		fTempPerm3 = 0;
		iConst4 = 0;
		fTempPerm4 = 0;
		iConst5 = 0;
		fTempPerm5 = 0;
		iConst6 = 0;
		fTempPerm6 = 0;
		iConst7 = 0;
		fTempPerm7 = 0;
		iConst8 = 0;
	}
	virtual void instanceResetUserInterface() {
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<2; i++) fRec7[i] = 0;
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
		ui_interface->openHorizontalBox("8 channels dB meter");
		ui_interface->openVerticalBox("0");
		ui_interface->declare(&fbargraph0, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fc859e577f0", &fbargraph0, -70.0f, 10.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("1");
		ui_interface->declare(&fbargraph1, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fc859e599c0", &fbargraph1, -70.0f, 10.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("2");
		ui_interface->declare(&fbargraph2, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fc859e5bb80", &fbargraph2, -70.0f, 10.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("3");
		ui_interface->declare(&fbargraph3, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fc859e5de10", &fbargraph3, -70.0f, 10.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("4");
		ui_interface->declare(&fbargraph4, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fc859e60170", &fbargraph4, -70.0f, 10.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("5");
		ui_interface->declare(&fbargraph5, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fc859e62580", &fbargraph5, -70.0f, 10.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("6");
		ui_interface->declare(&fbargraph6, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fc859e64a40", &fbargraph6, -70.0f, 10.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("7");
		ui_interface->declare(&fbargraph7, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fc859e66fb0", &fbargraph7, -70.0f, 10.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		//zone2b
		//zone3
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* input1 = input[1];
		FAUSTFLOAT* input2 = input[2];
		FAUSTFLOAT* input3 = input[3];
		FAUSTFLOAT* input4 = input[4];
		FAUSTFLOAT* input5 = input[5];
		FAUSTFLOAT* input6 = input[6];
		FAUSTFLOAT* input7 = input[7];
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		FAUSTFLOAT* output2 = output[2];
		FAUSTFLOAT* output3 = output[3];
		FAUSTFLOAT* output4 = output[4];
		FAUSTFLOAT* output5 = output[5];
		FAUSTFLOAT* output6 = output[6];
		FAUSTFLOAT* output7 = output[7];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fTempPerm0 = (float)input0[i];
			fRec0[0] = max((fRec0[1] - fConst0), min((float)10, (20 * log10f(max(0.00031622776601683794f, fabsf(fTempPerm0))))));
			fbargraph0 = fRec0[0];
			output0[i] = (FAUSTFLOAT)iConst1;
			fTempPerm1 = (float)input1[i];
			fRec1[0] = max((fRec1[1] - fConst0), min((float)10, (20 * log10f(max(0.00031622776601683794f, fabsf(fTempPerm1))))));
			fbargraph1 = fRec1[0];
			output1[i] = (FAUSTFLOAT)iConst2;
			fTempPerm2 = (float)input2[i];
			fRec2[0] = max((fRec2[1] - fConst0), min((float)10, (20 * log10f(max(0.00031622776601683794f, fabsf(fTempPerm2))))));
			fbargraph2 = fRec2[0];
			output2[i] = (FAUSTFLOAT)iConst3;
			fTempPerm3 = (float)input3[i];
			fRec3[0] = max((fRec3[1] - fConst0), min((float)10, (20 * log10f(max(0.00031622776601683794f, fabsf(fTempPerm3))))));
			fbargraph3 = fRec3[0];
			output3[i] = (FAUSTFLOAT)iConst4;
			fTempPerm4 = (float)input4[i];
			fRec4[0] = max((fRec4[1] - fConst0), min((float)10, (20 * log10f(max(0.00031622776601683794f, fabsf(fTempPerm4))))));
			fbargraph4 = fRec4[0];
			output4[i] = (FAUSTFLOAT)iConst5;
			fTempPerm5 = (float)input5[i];
			fRec5[0] = max((fRec5[1] - fConst0), min((float)10, (20 * log10f(max(0.00031622776601683794f, fabsf(fTempPerm5))))));
			fbargraph5 = fRec5[0];
			output5[i] = (FAUSTFLOAT)iConst6;
			fTempPerm6 = (float)input6[i];
			fRec6[0] = max((fRec6[1] - fConst0), min((float)10, (20 * log10f(max(0.00031622776601683794f, fabsf(fTempPerm6))))));
			fbargraph6 = fRec6[0];
			output6[i] = (FAUSTFLOAT)iConst7;
			fTempPerm7 = (float)input7[i];
			fRec7[0] = max((fRec7[1] - fConst0), min((float)10, (20 * log10f(max(0.00031622776601683794f, fabsf(fTempPerm7))))));
			fbargraph7 = fRec7[0];
			output7[i] = (FAUSTFLOAT)iConst8;
			// post processing
			fRec7[1] = fRec7[0];
			fRec6[1] = fRec6[0];
			fRec5[1] = fRec5[0];
			fRec4[1] = fRec4[0];
			fRec3[1] = fRec3[0];
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
		}
	}
};


