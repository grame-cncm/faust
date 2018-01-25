//----------------------------------------------------------
// name: "felix2"
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
	int 	IOTA;
	float 	fVec0[512];
	float 	fTempPerm0;
	float 	fTempPerm1;
	float 	fVec1[512];
	float 	fTempPerm2;
	float 	fVec2[512];
	float 	fTempPerm3;
	float 	fVec3[512];
	float 	fTempPerm4;
	float 	fVec4[512];
	float 	fTempPerm5;
	float 	fVec5[512];
	float 	fRec0[2];
	FAUSTFLOAT 	fbargraph0;
	float 	fTempPerm6;
	float 	fRec1[2];
	FAUSTFLOAT 	fbargraph1;
	float 	fTempPerm7;
	float 	fTempPerm8;
	float 	fTempPerm9;
	float 	fRec2[2];
	FAUSTFLOAT 	fbargraph2;
	float 	fTempPerm10;
	float 	fTempPerm11;
	float 	fRec3[2];
	FAUSTFLOAT 	fbargraph3;
	float 	fTempPerm12;
	float 	fTempPerm13;
	float 	fRec4[2];
	FAUSTFLOAT 	fbargraph4;
	float 	fTempPerm14;
	float 	fTempPerm15;
	float 	fTempPerm16;
	float 	fTempPerm17;
	float 	fRec5[2];
	FAUSTFLOAT 	fbargraph5;
	float 	fRec6[2];
	FAUSTFLOAT 	fbargraph6;
	float 	fRec7[2];
	FAUSTFLOAT 	fbargraph7;
	float 	fRec8[2];
	FAUSTFLOAT 	fbargraph8;
	float 	fTempPerm18;
	float 	fRec9[2];
	FAUSTFLOAT 	fbargraph9;
	float 	fRec10[2];
	FAUSTFLOAT 	fbargraph10;
	float 	fTempPerm19;
	float 	fTempPerm20;
	float 	fRec11[2];
	FAUSTFLOAT 	fbargraph11;
	float 	fRec12[2];
	FAUSTFLOAT 	fbargraph12;
	float 	fRec13[2];
	FAUSTFLOAT 	fbargraph13;
	float 	fRec14[2];
	FAUSTFLOAT 	fbargraph14;
	float 	fRec15[2];
	FAUSTFLOAT 	fbargraph15;
	float 	fTempPerm21;
	float 	fTempPerm22;
	float 	fRec16[2];
	FAUSTFLOAT 	fbargraph16;
	float 	fRec17[2];
	FAUSTFLOAT 	fbargraph17;
	float 	fTempPerm23;
	float 	fRec18[2];
	FAUSTFLOAT 	fbargraph18;
	float 	fTempPerm24;
	float 	fRec19[2];
	FAUSTFLOAT 	fbargraph19;
	float 	fTempPerm25;
	float 	fRec20[2];
	FAUSTFLOAT 	fbargraph20;
	float 	fRec21[2];
	FAUSTFLOAT 	fbargraph21;
	float 	fTempPerm26;
	float 	fRec22[2];
	FAUSTFLOAT 	fbargraph22;
	float 	fRec23[2];
	FAUSTFLOAT 	fbargraph23;
	float 	fTempPerm27;
	float 	fRec24[2];
	FAUSTFLOAT 	fbargraph24;
	float 	fTempPerm28;
	float 	fTempPerm29;
	float 	fRec25[2];
	FAUSTFLOAT 	fbargraph25;
	float 	fTempPerm30;
	float 	fTempPerm31;
	float 	fRec26[2];
	FAUSTFLOAT 	fbargraph26;
	float 	fRec27[2];
	FAUSTFLOAT 	fbargraph27;
	float 	fTempPerm32;
	float 	fRec28[2];
	FAUSTFLOAT 	fbargraph28;
	float 	fRec29[2];
	FAUSTFLOAT 	fbargraph29;
	float 	fRec30[2];
	FAUSTFLOAT 	fbargraph30;
	float 	fRec31[2];
	FAUSTFLOAT 	fbargraph31;
	float 	fRec32[2];
	FAUSTFLOAT 	fbargraph32;
	float 	fRec33[2];
	FAUSTFLOAT 	fbargraph33;
	float 	fRec34[2];
	FAUSTFLOAT 	fbargraph34;
	float 	fRec35[2];
	FAUSTFLOAT 	fbargraph35;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("math.lib/author", "GRAME");
		m->declare("math.lib/copyright", "GRAME");
		m->declare("math.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m->declare("math.lib/license", "LGPL with exception");
		m->declare("math.lib/name", "Math Library");
		m->declare("math.lib/version", "1.0");
		m->declare("music.lib/author", "GRAME");
		m->declare("music.lib/copyright", "GRAME");
		m->declare("music.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m->declare("music.lib/license", "LGPL with exception");
		m->declare("music.lib/name", "Music Library");
		m->declare("music.lib/version", "1.0");
		m->declare("name", "felix2");
	}

	virtual int getNumInputs() { return 6; }
	virtual int getNumOutputs() { return 36; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = (96.0f / min(192000.0f, max(1.0f, (float)fSamplingFreq)));
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
		fTempPerm26 = 0;
		fTempPerm27 = 0;
		fTempPerm28 = 0;
		fTempPerm29 = 0;
		fTempPerm30 = 0;
		fTempPerm31 = 0;
		fTempPerm32 = 0;
	}
	virtual void instanceResetUserInterface() {
	}
	virtual void instanceClear() {
		IOTA = 0;
		for (int i=0; i<512; i++) fVec0[i] = 0;
		for (int i=0; i<512; i++) fVec1[i] = 0;
		for (int i=0; i<512; i++) fVec2[i] = 0;
		for (int i=0; i<512; i++) fVec3[i] = 0;
		for (int i=0; i<512; i++) fVec4[i] = 0;
		for (int i=0; i<512; i++) fVec5[i] = 0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<2; i++) fRec7[i] = 0;
		for (int i=0; i<2; i++) fRec8[i] = 0;
		for (int i=0; i<2; i++) fRec9[i] = 0;
		for (int i=0; i<2; i++) fRec10[i] = 0;
		for (int i=0; i<2; i++) fRec11[i] = 0;
		for (int i=0; i<2; i++) fRec12[i] = 0;
		for (int i=0; i<2; i++) fRec13[i] = 0;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		for (int i=0; i<2; i++) fRec15[i] = 0;
		for (int i=0; i<2; i++) fRec16[i] = 0;
		for (int i=0; i<2; i++) fRec17[i] = 0;
		for (int i=0; i<2; i++) fRec18[i] = 0;
		for (int i=0; i<2; i++) fRec19[i] = 0;
		for (int i=0; i<2; i++) fRec20[i] = 0;
		for (int i=0; i<2; i++) fRec21[i] = 0;
		for (int i=0; i<2; i++) fRec22[i] = 0;
		for (int i=0; i<2; i++) fRec23[i] = 0;
		for (int i=0; i<2; i++) fRec24[i] = 0;
		for (int i=0; i<2; i++) fRec25[i] = 0;
		for (int i=0; i<2; i++) fRec26[i] = 0;
		for (int i=0; i<2; i++) fRec27[i] = 0;
		for (int i=0; i<2; i++) fRec28[i] = 0;
		for (int i=0; i<2; i++) fRec29[i] = 0;
		for (int i=0; i<2; i++) fRec30[i] = 0;
		for (int i=0; i<2; i++) fRec31[i] = 0;
		for (int i=0; i<2; i++) fRec32[i] = 0;
		for (int i=0; i<2; i++) fRec33[i] = 0;
		for (int i=0; i<2; i++) fRec34[i] = 0;
		for (int i=0; i<2; i++) fRec35[i] = 0;
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
		ui_interface->openVerticalBox("felix2");
		ui_interface->openHorizontalBox("ctrl   0");
		ui_interface->addVerticalBargraph("ctrl  0", &fbargraph0, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl  1", &fbargraph1, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl  2", &fbargraph2, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl  3", &fbargraph3, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl  4", &fbargraph4, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl  5", &fbargraph5, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("ctrl   1");
		ui_interface->addVerticalBargraph("ctrl 10", &fbargraph6, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 11", &fbargraph7, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 12", &fbargraph8, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 13", &fbargraph9, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 14", &fbargraph10, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 15", &fbargraph11, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("ctrl   2");
		ui_interface->addVerticalBargraph("ctrl 20", &fbargraph12, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 21", &fbargraph13, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 22", &fbargraph14, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 23", &fbargraph15, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 24", &fbargraph16, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 25", &fbargraph17, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("ctrl   3");
		ui_interface->addVerticalBargraph("ctrl 30", &fbargraph18, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 31", &fbargraph19, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 32", &fbargraph20, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 33", &fbargraph21, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 34", &fbargraph22, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 35", &fbargraph23, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("ctrl   4");
		ui_interface->addVerticalBargraph("ctrl 40", &fbargraph24, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 41", &fbargraph25, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 42", &fbargraph26, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 43", &fbargraph27, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 44", &fbargraph28, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 45", &fbargraph29, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("ctrl   5");
		ui_interface->addVerticalBargraph("ctrl 50", &fbargraph30, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 51", &fbargraph31, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 52", &fbargraph32, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 53", &fbargraph33, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 54", &fbargraph34, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 55", &fbargraph35, 0.0f, 1.0f);
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
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		FAUSTFLOAT* output2 = output[2];
		FAUSTFLOAT* output3 = output[3];
		FAUSTFLOAT* output4 = output[4];
		FAUSTFLOAT* output5 = output[5];
		FAUSTFLOAT* output6 = output[6];
		FAUSTFLOAT* output7 = output[7];
		FAUSTFLOAT* output8 = output[8];
		FAUSTFLOAT* output9 = output[9];
		FAUSTFLOAT* output10 = output[10];
		FAUSTFLOAT* output11 = output[11];
		FAUSTFLOAT* output12 = output[12];
		FAUSTFLOAT* output13 = output[13];
		FAUSTFLOAT* output14 = output[14];
		FAUSTFLOAT* output15 = output[15];
		FAUSTFLOAT* output16 = output[16];
		FAUSTFLOAT* output17 = output[17];
		FAUSTFLOAT* output18 = output[18];
		FAUSTFLOAT* output19 = output[19];
		FAUSTFLOAT* output20 = output[20];
		FAUSTFLOAT* output21 = output[21];
		FAUSTFLOAT* output22 = output[22];
		FAUSTFLOAT* output23 = output[23];
		FAUSTFLOAT* output24 = output[24];
		FAUSTFLOAT* output25 = output[25];
		FAUSTFLOAT* output26 = output[26];
		FAUSTFLOAT* output27 = output[27];
		FAUSTFLOAT* output28 = output[28];
		FAUSTFLOAT* output29 = output[29];
		FAUSTFLOAT* output30 = output[30];
		FAUSTFLOAT* output31 = output[31];
		FAUSTFLOAT* output32 = output[32];
		FAUSTFLOAT* output33 = output[33];
		FAUSTFLOAT* output34 = output[34];
		FAUSTFLOAT* output35 = output[35];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fVec0[IOTA&511] = (float)input0[i];
			fTempPerm0 = fVec0[(IOTA-256)&511];
			fTempPerm1 = (float)input1[i];
			fVec1[IOTA&511] = fTempPerm1;
			fTempPerm2 = (float)input2[i];
			fVec2[IOTA&511] = fTempPerm2;
			fTempPerm3 = (float)input3[i];
			fVec3[IOTA&511] = fTempPerm3;
			fTempPerm4 = (float)input4[i];
			fVec4[IOTA&511] = fTempPerm4;
			fTempPerm5 = (float)input5[i];
			fVec5[IOTA&511] = fTempPerm5;
			fRec0[0] = max((fRec0[1] - fConst0), fabsf((((((fTempPerm0 + fVec1[(IOTA-244)&511]) + fVec2[(IOTA-233)&511]) + fVec3[(IOTA-221)&511]) + fVec4[(IOTA-209)&511]) + fVec5[(IOTA-197)&511])));
			fbargraph0 = fRec0[0];
			output0[i] = (FAUSTFLOAT)fbargraph0;
			fTempPerm6 = (fTempPerm0 + fVec1[(IOTA-246)&511]);
			fRec1[0] = max((fRec1[1] - fConst0), fabsf(((((fTempPerm6 + fVec2[(IOTA-236)&511]) + fVec3[(IOTA-225)&511]) + fVec4[(IOTA-215)&511]) + fVec5[(IOTA-204)&511])));
			fbargraph1 = fRec1[0];
			output1[i] = (FAUSTFLOAT)fbargraph1;
			fTempPerm7 = fVec2[(IOTA-239)&511];
			fTempPerm8 = fVec3[(IOTA-230)&511];
			fTempPerm9 = fVec5[(IOTA-211)&511];
			fRec2[0] = max((fRec2[1] - fConst0), fabsf((((((fTempPerm0 + fVec1[(IOTA-247)&511]) + fTempPerm7) + fTempPerm8) + fVec4[(IOTA-220)&511]) + fTempPerm9)));
			fbargraph2 = fRec2[0];
			output2[i] = (FAUSTFLOAT)fbargraph2;
			fTempPerm10 = (fTempPerm0 + fVec1[(IOTA-249)&511]);
			fTempPerm11 = (fTempPerm10 + fVec2[(IOTA-241)&511]);
			fRec3[0] = max((fRec3[1] - fConst0), fabsf((((fTempPerm11 + fVec3[(IOTA-233)&511]) + fVec4[(IOTA-225)&511]) + fVec5[(IOTA-217)&511])));
			fbargraph3 = fRec3[0];
			output3[i] = (FAUSTFLOAT)fbargraph3;
			fTempPerm12 = (fTempPerm0 + fVec1[(IOTA-250)&511]);
			fTempPerm13 = fVec2[(IOTA-243)&511];
			fRec4[0] = max((fRec4[1] - fConst0), fabsf(((((fTempPerm12 + fTempPerm13) + fVec3[(IOTA-236)&511]) + fVec4[(IOTA-229)&511]) + fVec5[(IOTA-222)&511])));
			fbargraph4 = fRec4[0];
			output4[i] = (FAUSTFLOAT)fbargraph4;
			fTempPerm14 = fVec2[(IOTA-245)&511];
			fTempPerm15 = fVec3[(IOTA-239)&511];
			fTempPerm16 = fVec4[(IOTA-232)&511];
			fTempPerm17 = fVec5[(IOTA-225)&511];
			fRec5[0] = max((fRec5[1] - fConst0), fabsf(((((fTempPerm12 + fTempPerm14) + fTempPerm15) + fTempPerm16) + fTempPerm17)));
			fbargraph5 = fRec5[0];
			output5[i] = (FAUSTFLOAT)fbargraph5;
			fRec6[0] = max((fRec6[1] - fConst0), fabsf(((((fTempPerm6 + fVec2[(IOTA-235)&511]) + fVec3[(IOTA-224)&511]) + fVec4[(IOTA-213)&511]) + fVec5[(IOTA-201)&511])));
			fbargraph6 = fRec6[0];
			output6[i] = (FAUSTFLOAT)fbargraph6;
			fRec7[0] = max((fRec7[1] - fConst0), fabsf((fVec4[(IOTA-221)&511] + (fVec1[(IOTA-248)&511] + (fTempPerm9 + (fTempPerm8 + (fTempPerm0 + fTempPerm7)))))));
			fbargraph7 = fRec7[0];
			output7[i] = (FAUSTFLOAT)fbargraph7;
			fRec8[0] = max((fRec8[1] - fConst0), fabsf(((((fTempPerm10 + fTempPerm13) + fVec3[(IOTA-235)&511]) + fVec4[(IOTA-227)&511]) + fVec5[(IOTA-219)&511])));
			fbargraph8 = fRec8[0];
			output8[i] = (FAUSTFLOAT)fbargraph8;
			fTempPerm18 = fVec1[(IOTA-251)&511];
			fRec9[0] = max((fRec9[1] - fConst0), fabsf((fTempPerm18 + (fTempPerm17 + (fTempPerm16 + (fTempPerm15 + (fTempPerm0 + fTempPerm14)))))));
			fbargraph9 = fRec9[0];
			output9[i] = (FAUSTFLOAT)fbargraph9;
			fRec10[0] = max((fRec10[1] - fConst0), fabsf((((((fTempPerm0 + fTempPerm18) + fVec2[(IOTA-247)&511]) + fVec3[(IOTA-241)&511]) + fVec4[(IOTA-236)&511]) + fVec5[(IOTA-230)&511])));
			fbargraph10 = fRec10[0];
			output10[i] = (FAUSTFLOAT)fbargraph10;
			fTempPerm19 = ((fTempPerm0 + fVec1[(IOTA-252)&511]) + fVec2[(IOTA-248)&511]);
			fTempPerm20 = fVec4[(IOTA-238)&511];
			fRec11[0] = max((fRec11[1] - fConst0), fabsf((((fTempPerm19 + fVec3[(IOTA-243)&511]) + fTempPerm20) + fVec5[(IOTA-233)&511])));
			fbargraph11 = fRec11[0];
			output11[i] = (FAUSTFLOAT)fbargraph11;
			fRec12[0] = max((fRec12[1] - fConst0), fabsf((((fTempPerm11 + fVec3[(IOTA-232)&511]) + fVec4[(IOTA-223)&511]) + fVec5[(IOTA-212)&511])));
			fbargraph12 = fRec12[0];
			output12[i] = (FAUSTFLOAT)fbargraph12;
			fRec13[0] = max((fRec13[1] - fConst0), fabsf((fVec5[(IOTA-224)&511] + (fVec3[(IOTA-240)&511] + (fVec2[(IOTA-246)&511] + (fTempPerm18 + (fTempPerm0 + fTempPerm16)))))));
			fbargraph13 = fRec13[0];
			output13[i] = (FAUSTFLOAT)fbargraph13;
			fRec14[0] = max((fRec14[1] - fConst0), fabsf((fVec5[(IOTA-231)&511] + (fVec3[(IOTA-244)&511] + (fTempPerm19 + fTempPerm20)))));
			fbargraph14 = fRec14[0];
			output14[i] = (FAUSTFLOAT)fbargraph14;
			fRec15[0] = max((fRec15[1] - fConst0), fabsf((((((fTempPerm0 + fVec1[(IOTA-253)&511]) + fVec2[(IOTA-250)&511]) + fVec3[(IOTA-246)&511]) + fVec4[(IOTA-241)&511]) + fVec5[(IOTA-236)&511])));
			fbargraph15 = fRec15[0];
			output15[i] = (FAUSTFLOAT)fbargraph15;
			fTempPerm21 = (fTempPerm0 + fVec1[(IOTA-254)&511]);
			fTempPerm22 = fVec5[(IOTA-239)&511];
			fRec16[0] = max((fRec16[1] - fConst0), fabsf(((((fTempPerm21 + fVec2[(IOTA-251)&511]) + fVec3[(IOTA-248)&511]) + fVec4[(IOTA-244)&511]) + fTempPerm22)));
			fbargraph16 = fRec16[0];
			output16[i] = (FAUSTFLOAT)fbargraph16;
			fRec17[0] = max((fRec17[1] - fConst0), fabsf(((((fTempPerm21 + fVec2[(IOTA-252)&511]) + fVec3[(IOTA-249)&511]) + fVec4[(IOTA-245)&511]) + fVec5[(IOTA-242)&511])));
			fbargraph17 = fRec17[0];
			output17[i] = (FAUSTFLOAT)fbargraph17;
			fTempPerm23 = fVec2[(IOTA-256)&511];
			fRec18[0] = max((fRec18[1] - fConst0), fabsf((fVec4[(IOTA-246)&511] + (fVec3[(IOTA-252)&511] + (fTempPerm23 + (fVec1[(IOTA-257)&511] + (fTempPerm0 + fTempPerm22)))))));
			fbargraph18 = fRec18[0];
			output18[i] = (FAUSTFLOAT)fbargraph18;
			fTempPerm24 = (fVec1[(IOTA-256)&511] + (fTempPerm0 + fTempPerm23));
			fRec19[0] = max((fRec19[1] - fConst0), fabsf((fVec5[(IOTA-245)&511] + (fVec4[(IOTA-250)&511] + (fVec3[(IOTA-253)&511] + fTempPerm24)))));
			fbargraph19 = fRec19[0];
			output19[i] = (FAUSTFLOAT)fbargraph19;
			fTempPerm25 = (fTempPerm24 + fVec3[(IOTA-254)&511]);
			fRec20[0] = max((fRec20[1] - fConst0), fabsf(((fTempPerm25 + fVec4[(IOTA-251)&511]) + fVec5[(IOTA-247)&511])));
			fbargraph20 = fRec20[0];
			output20[i] = (FAUSTFLOAT)fbargraph20;
			fRec21[0] = max((fRec21[1] - fConst0), fabsf(((fTempPerm25 + fVec4[(IOTA-252)&511]) + fVec5[(IOTA-249)&511])));
			fbargraph21 = fRec21[0];
			output21[i] = (FAUSTFLOAT)fbargraph21;
			fTempPerm26 = fVec4[(IOTA-253)&511];
			fRec22[0] = max((fRec22[1] - fConst0), fabsf(((fTempPerm25 + fTempPerm26) + fVec5[(IOTA-250)&511])));
			fbargraph22 = fRec22[0];
			output22[i] = (FAUSTFLOAT)fbargraph22;
			fRec23[0] = max((fRec23[1] - fConst0), fabsf((fVec5[(IOTA-251)&511] + (fVec3[(IOTA-255)&511] + (fTempPerm24 + fTempPerm26)))));
			fbargraph23 = fRec23[0];
			output23[i] = (FAUSTFLOAT)fbargraph23;
			fTempPerm27 = fVec5[(IOTA-276)&511];
			fRec24[0] = max((fRec24[1] - fConst0), fabsf((((((fTempPerm0 + fVec1[(IOTA-263)&511]) + fVec2[(IOTA-270)&511]) + fVec3[(IOTA-274)&511]) + fVec4[(IOTA-276)&511]) + fTempPerm27)));
			fbargraph24 = fRec24[0];
			output24[i] = (FAUSTFLOAT)fbargraph24;
			fTempPerm28 = fVec1[(IOTA-261)&511];
			fTempPerm29 = fVec3[(IOTA-268)&511];
			fRec25[0] = max((fRec25[1] - fConst0), fabsf((((((fTempPerm0 + fTempPerm28) + fVec2[(IOTA-265)&511]) + fTempPerm29) + fVec4[(IOTA-269)&511]) + fVec5[(IOTA-269)&511])));
			fbargraph25 = fRec25[0];
			output25[i] = (FAUSTFLOAT)fbargraph25;
			fTempPerm30 = fVec1[(IOTA-260)&511];
			fTempPerm31 = ((fTempPerm0 + fTempPerm30) + fVec2[(IOTA-263)&511]);
			fRec26[0] = max((fRec26[1] - fConst0), fabsf((((fTempPerm31 + fVec3[(IOTA-265)&511]) + fVec4[(IOTA-265)&511]) + fVec5[(IOTA-265)&511])));
			fbargraph26 = fRec26[0];
			output26[i] = (FAUSTFLOAT)fbargraph26;
			fRec27[0] = max((fRec27[1] - fConst0), fabsf((((((fTempPerm0 + fVec1[(IOTA-259)&511]) + fVec2[(IOTA-261)&511]) + fVec3[(IOTA-263)&511]) + fVec4[(IOTA-263)&511]) + fVec5[(IOTA-263)&511])));
			fbargraph27 = fRec27[0];
			output27[i] = (FAUSTFLOAT)fbargraph27;
			fTempPerm32 = (fTempPerm0 + fVec1[(IOTA-258)&511]);
			fRec28[0] = max((fRec28[1] - fConst0), fabsf(((((fTempPerm32 + fVec2[(IOTA-260)&511]) + fVec3[(IOTA-261)&511]) + fVec4[(IOTA-262)&511]) + fVec5[(IOTA-262)&511])));
			fbargraph28 = fRec28[0];
			output28[i] = (FAUSTFLOAT)fbargraph28;
			fRec29[0] = max((fRec29[1] - fConst0), fabsf(((((fTempPerm32 + fVec2[(IOTA-259)&511]) + fVec3[(IOTA-260)&511]) + fVec4[(IOTA-261)&511]) + fVec5[(IOTA-261)&511])));
			fbargraph29 = fRec29[0];
			output29[i] = (FAUSTFLOAT)fbargraph29;
			fRec30[0] = max((fRec30[1] - fConst0), fabsf((((((fTempPerm0 + fVec1[(IOTA-266)&511]) + fVec2[(IOTA-276)&511]) + fVec3[(IOTA-285)&511]) + fVec4[(IOTA-293)&511]) + fVec5[(IOTA-300)&511])));
			fbargraph30 = fRec30[0];
			output30[i] = (FAUSTFLOAT)fbargraph30;
			fRec31[0] = max((fRec31[1] - fConst0), fabsf((((((fTempPerm0 + fVec1[(IOTA-264)&511]) + fVec2[(IOTA-272)&511]) + fVec3[(IOTA-278)&511]) + fVec4[(IOTA-284)&511]) + fVec5[(IOTA-289)&511])));
			fbargraph31 = fRec31[0];
			output31[i] = (FAUSTFLOAT)fbargraph31;
			fRec32[0] = max((fRec32[1] - fConst0), fabsf((((((fTempPerm0 + fVec1[(IOTA-262)&511]) + fVec2[(IOTA-268)&511]) + fVec3[(IOTA-273)&511]) + fVec4[(IOTA-278)&511]) + fVec5[(IOTA-281)&511])));
			fbargraph32 = fRec32[0];
			output32[i] = (FAUSTFLOAT)fbargraph32;
			fRec33[0] = max((fRec33[1] - fConst0), fabsf((fVec4[(IOTA-274)&511] + (fVec3[(IOTA-270)&511] + (fVec2[(IOTA-266)&511] + (fTempPerm28 + (fTempPerm0 + fTempPerm27)))))));
			fbargraph33 = fRec33[0];
			output33[i] = (FAUSTFLOAT)fbargraph33;
			fRec34[0] = max((fRec34[1] - fConst0), fabsf((((fVec2[(IOTA-264)&511] + (fTempPerm30 + (fTempPerm0 + fTempPerm29))) + fVec4[(IOTA-271)&511]) + fVec5[(IOTA-273)&511])));
			fbargraph34 = fRec34[0];
			output34[i] = (FAUSTFLOAT)fbargraph34;
			fRec35[0] = max((fRec35[1] - fConst0), fabsf((((fTempPerm31 + fVec3[(IOTA-266)&511]) + fVec4[(IOTA-268)&511]) + fVec5[(IOTA-270)&511])));
			fbargraph35 = fRec35[0];
			output35[i] = (FAUSTFLOAT)fbargraph35;
			// post processing
			fRec35[1] = fRec35[0];
			fRec34[1] = fRec34[0];
			fRec33[1] = fRec33[0];
			fRec32[1] = fRec32[0];
			fRec31[1] = fRec31[0];
			fRec30[1] = fRec30[0];
			fRec29[1] = fRec29[0];
			fRec28[1] = fRec28[0];
			fRec27[1] = fRec27[0];
			fRec26[1] = fRec26[0];
			fRec25[1] = fRec25[0];
			fRec24[1] = fRec24[0];
			fRec23[1] = fRec23[0];
			fRec22[1] = fRec22[0];
			fRec21[1] = fRec21[0];
			fRec20[1] = fRec20[0];
			fRec19[1] = fRec19[0];
			fRec18[1] = fRec18[0];
			fRec17[1] = fRec17[0];
			fRec16[1] = fRec16[0];
			fRec15[1] = fRec15[0];
			fRec14[1] = fRec14[0];
			fRec13[1] = fRec13[0];
			fRec12[1] = fRec12[0];
			fRec11[1] = fRec11[0];
			fRec10[1] = fRec10[0];
			fRec9[1] = fRec9[0];
			fRec8[1] = fRec8[0];
			fRec7[1] = fRec7[0];
			fRec6[1] = fRec6[0];
			fRec5[1] = fRec5[0];
			fRec4[1] = fRec4[0];
			fRec3[1] = fRec3[0];
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
			IOTA = IOTA+1;
		}
	}
};


