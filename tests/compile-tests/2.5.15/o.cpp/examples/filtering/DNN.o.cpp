//----------------------------------------------------------
// author: "JOS"
// license: "STK-4.3"
// name: "DNN"
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
	float 	fTempPerm0;
	float 	fTempPerm1;
	float 	fTempPerm2;
	float 	fTempPerm3;
	float 	fTempPerm4;
	float 	fTempPerm5;
	float 	fTempPerm6;
	float 	fTempPerm7;
	float 	fTempPerm8;
	float 	fTempPerm9;
	float 	fTempPerm10;
	float 	fTempPerm11;
	float 	fTempPerm12;
	float 	fTempPerm13;
	float 	fTempPerm14;
	float 	fTempPerm15;
	float 	fTempPerm16;
	float 	fTempPerm17;
	float 	fTempPerm18;
	float 	fTempPerm19;
	float 	fTempPerm20;
	float 	fTempPerm21;
	float 	fTempPerm22;
	float 	fTempPerm23;
	float 	fTempPerm24;
	float 	fTempPerm25;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("author", "JOS");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("license", "STK-4.3");
		m->declare("name", "DNN");
	}

	virtual int getNumInputs() { return 8; }
	virtual int getNumOutputs() { return 8; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fTempPerm0 = 0;
		fTempPerm1 = 0;
		fTempPerm2 = 0;
		fTempPerm3 = 0;
		fTempPerm4 = 0;
		fTempPerm5 = 0;
		fTempPerm6 = 0;
		fTempPerm7 = 0;
		fTempPerm8 = 0;
		fTempPerm9 = 0;
		fTempPerm10 = 0;
		fTempPerm11 = 0;
		fTempPerm12 = 0;
		fTempPerm13 = 0;
		fTempPerm14 = 0;
		fTempPerm15 = 0;
		fTempPerm16 = 0;
		fTempPerm17 = 0;
		fTempPerm18 = 0;
		fTempPerm19 = 0;
		fTempPerm20 = 0;
		fTempPerm21 = 0;
		fTempPerm22 = 0;
		fTempPerm23 = 0;
		fTempPerm24 = 0;
		fTempPerm25 = 0;
	}
	virtual void instanceResetUserInterface() {
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
		ui_interface->openVerticalBox("DNN");
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
			fTempPerm0 = (float)input7[i];
			fTempPerm1 = (float)input6[i];
			fTempPerm2 = (float)input5[i];
			fTempPerm3 = (float)input4[i];
			fTempPerm4 = (float)input2[i];
			fTempPerm5 = (float)input1[i];
			fTempPerm6 = (float)input3[i];
			fTempPerm7 = ((30 * fTempPerm0) + ((60 * fTempPerm1) + ((10 * fTempPerm2) + ((40 * fTempPerm3) + (((20 * fTempPerm4) + (50 * fTempPerm5)) + (70 * fTempPerm6))))));
			fTempPerm8 = ((fTempPerm7 > 0) * fTempPerm7);
			fTempPerm9 = (float)input0[i];
			fTempPerm10 = ((43 * fTempPerm0) + (((23 * fTempPerm2) + ((53 * fTempPerm3) + ((3 * fTempPerm6) + ((33 * fTempPerm4) + ((13 * fTempPerm9) + (63 * fTempPerm5)))))) + (73 * fTempPerm1)));
			fTempPerm11 = ((fTempPerm10 > 0) * fTempPerm10);
			fTempPerm12 = ((61 * fTempPerm0) + ((11 * fTempPerm1) + ((41 * fTempPerm2) + (((21 * fTempPerm6) + ((fTempPerm5 + (31 * fTempPerm9)) + (51 * fTempPerm4))) + (71 * fTempPerm3)))));
			fTempPerm13 = ((fTempPerm12 > 0) * fTempPerm12);
			fTempPerm14 = (((24 * fTempPerm1) + ((54 * fTempPerm2) + ((4 * fTempPerm3) + ((34 * fTempPerm6) + (((14 * fTempPerm5) + (44 * fTempPerm9)) + (64 * fTempPerm4)))))) + (74 * fTempPerm0));
			fTempPerm15 = (fTempPerm14 * (fTempPerm14 > 0));
			fTempPerm16 = ((12 * fTempPerm0) + ((42 * fTempPerm1) + (((22 * fTempPerm3) + ((52 * fTempPerm6) + ((2 * fTempPerm4) + ((32 * fTempPerm5) + (62 * fTempPerm9))))) + (72 * fTempPerm2))));
			fTempPerm17 = ((fTempPerm16 > 0) * fTempPerm16);
			fTempPerm18 = (((((100 * fTempPerm8) + (110 * fTempPerm11)) + (120 * fTempPerm13)) + (130 * fTempPerm15)) + (140 * fTempPerm17));
			output0[i] = (FAUSTFLOAT)(fTempPerm18 * (fTempPerm18 > 0));
			fTempPerm19 = ((121 * fTempPerm17) + ((111 * fTempPerm15) + ((101 * fTempPerm13) + ((131 * fTempPerm8) + (141 * fTempPerm11)))));
			output1[i] = (FAUSTFLOAT)((fTempPerm19 > 0) * fTempPerm19);
			fTempPerm20 = ((102 * fTempPerm17) + ((((112 * fTempPerm8) + (122 * fTempPerm11)) + (132 * fTempPerm13)) + (142 * fTempPerm15)));
			output2[i] = (FAUSTFLOAT)((fTempPerm20 > 0) * fTempPerm20);
			fTempPerm21 = ((133 * fTempPerm17) + ((123 * fTempPerm15) + ((113 * fTempPerm13) + ((103 * fTempPerm11) + (143 * fTempPerm8)))));
			output3[i] = (FAUSTFLOAT)((fTempPerm21 > 0) * fTempPerm21);
			fTempPerm22 = ((114 * fTempPerm17) + ((104 * fTempPerm15) + (((124 * fTempPerm8) + (134 * fTempPerm11)) + (144 * fTempPerm13))));
			output4[i] = (FAUSTFLOAT)((fTempPerm22 > 0) * fTempPerm22);
			fTempPerm23 = (((((105 * fTempPerm8) + (115 * fTempPerm11)) + (125 * fTempPerm13)) + (135 * fTempPerm15)) + (145 * fTempPerm17));
			output5[i] = (FAUSTFLOAT)(fTempPerm23 * (fTempPerm23 > 0));
			fTempPerm24 = ((126 * fTempPerm17) + ((116 * fTempPerm15) + ((106 * fTempPerm13) + ((136 * fTempPerm8) + (146 * fTempPerm11)))));
			output6[i] = (FAUSTFLOAT)((fTempPerm24 > 0) * fTempPerm24);
			fTempPerm25 = ((107 * fTempPerm17) + ((((117 * fTempPerm8) + (127 * fTempPerm11)) + (137 * fTempPerm13)) + (147 * fTempPerm15)));
			output7[i] = (FAUSTFLOAT)((fTempPerm25 > 0) * fTempPerm25);
		}
	}
};


