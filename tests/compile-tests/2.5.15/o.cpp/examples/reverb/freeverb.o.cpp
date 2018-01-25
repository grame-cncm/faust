//----------------------------------------------------------
// author: "RM"
// name: "freeverb"
// version: "0.0"
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
	float 	fTempPerm0;
	float 	fTempPerm1;
	float 	fTempPerm2;
	float 	fConst0;
	float 	fConst1;
	FAUSTFLOAT 	fslider1;
	float 	fConst2;
	FAUSTFLOAT 	fslider2;
	float 	fRec9[2];
	int 	IOTA;
	float 	fVec0[8192];
	int 	iConst3;
	float 	fRec8[2];
	float 	fRec11[2];
	float 	fVec1[8192];
	int 	iConst4;
	float 	fRec10[2];
	float 	fRec13[2];
	float 	fVec2[8192];
	int 	iConst5;
	float 	fRec12[2];
	float 	fRec15[2];
	float 	fVec3[8192];
	int 	iConst6;
	float 	fRec14[2];
	float 	fRec17[2];
	float 	fVec4[8192];
	int 	iConst7;
	float 	fRec16[2];
	float 	fRec19[2];
	float 	fVec5[8192];
	int 	iConst8;
	float 	fRec18[2];
	float 	fRec21[2];
	float 	fVec6[8192];
	int 	iConst9;
	float 	fRec20[2];
	float 	fRec23[2];
	float 	fVec7[8192];
	int 	iConst10;
	float 	fRec22[2];
	float 	fTempPerm3;
	float 	fVec8[2048];
	int 	iConst11;
	int 	iConst12;
	float 	fRec6[2];
	float 	fTempPerm4;
	float 	fVec9[2048];
	int 	iConst13;
	int 	iConst14;
	float 	fRec4[2];
	float 	fTempPerm5;
	float 	fVec10[2048];
	int 	iConst15;
	int 	iConst16;
	float 	fRec2[2];
	float 	fTempPerm6;
	float 	fVec11[1024];
	int 	iConst17;
	int 	iConst18;
	float 	fRec0[2];
	float 	fRec33[2];
	float 	fVec12[8192];
	float 	fConst19;
	FAUSTFLOAT 	fslider3;
	float 	fRec32[2];
	float 	fRec35[2];
	float 	fVec13[8192];
	float 	fRec34[2];
	float 	fRec37[2];
	float 	fVec14[8192];
	float 	fRec36[2];
	float 	fRec39[2];
	float 	fVec15[8192];
	float 	fRec38[2];
	float 	fRec41[2];
	float 	fVec16[8192];
	float 	fRec40[2];
	float 	fRec43[2];
	float 	fVec17[8192];
	float 	fRec42[2];
	float 	fRec45[2];
	float 	fVec18[8192];
	float 	fRec44[2];
	float 	fRec47[2];
	float 	fVec19[8192];
	float 	fRec46[2];
	float 	fTempPerm7;
	float 	fVec20[2048];
	float 	fRec30[2];
	float 	fTempPerm8;
	float 	fVec21[2048];
	float 	fRec28[2];
	float 	fTempPerm9;
	float 	fVec22[2048];
	float 	fRec26[2];
	float 	fTempPerm10;
	float 	fVec23[2048];
	float 	fRec24[2];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("author", "RM");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("description", "Freeverb demo application.");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "freeverb");
		m->declare("reverbs.lib/name", "Faust Reverb Library");
		m->declare("reverbs.lib/version", "0.0");
		m->declare("version", "0.0");
	}

	virtual int getNumInputs() { return 2; }
	virtual int getNumOutputs() { return 2; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fTempPerm0 = 0;
		fTempPerm1 = 0;
		fTempPerm2 = 0;
		fConst0 = min(192000.0f, max(1.0f, (float)fSamplingFreq));
		fConst1 = (12348.000000000002f / fConst0);
		fConst2 = (17640.0f / fConst0);
		iConst3 = int((0.036666666666666667f * fConst0));
		iConst4 = int((0.035306122448979592f * fConst0));
		iConst5 = int((0.032244897959183672f * fConst0));
		iConst6 = int((0.03380952380952381f * fConst0));
		iConst7 = int((0.025306122448979593f * fConst0));
		iConst8 = int((0.026938775510204082f * fConst0));
		iConst9 = int((0.028956916099773241f * fConst0));
		iConst10 = int((0.03074829931972789f * fConst0));
		fTempPerm3 = 0;
		iConst11 = int((0.012607709750566893f * fConst0));
		iConst12 = int(min(1024, max(0, (iConst11 + -1))));
		fTempPerm4 = 0;
		iConst13 = int((0.01f * fConst0));
		iConst14 = int(min(1024, max(0, (iConst13 + -1))));
		fTempPerm5 = 0;
		iConst15 = int((0.007732426303854875f * fConst0));
		iConst16 = int(min(1024, max(0, (iConst15 + -1))));
		fTempPerm6 = 0;
		iConst17 = int((0.0051020408163265302f * fConst0));
		iConst18 = int(min(1024, max(0, (iConst17 + -1))));
		fConst19 = (0.0010430839002267573f * fConst0);
		fTempPerm7 = 0;
		fTempPerm8 = 0;
		fTempPerm9 = 0;
		fTempPerm10 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.33329999999999999f;
		fslider1 = 0.5f;
		fslider2 = 0.5f;
		fslider3 = 0.5f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fRec9[i] = 0;
		IOTA = 0;
		for (int i=0; i<8192; i++) fVec0[i] = 0;
		for (int i=0; i<2; i++) fRec8[i] = 0;
		for (int i=0; i<2; i++) fRec11[i] = 0;
		for (int i=0; i<8192; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fRec10[i] = 0;
		for (int i=0; i<2; i++) fRec13[i] = 0;
		for (int i=0; i<8192; i++) fVec2[i] = 0;
		for (int i=0; i<2; i++) fRec12[i] = 0;
		for (int i=0; i<2; i++) fRec15[i] = 0;
		for (int i=0; i<8192; i++) fVec3[i] = 0;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		for (int i=0; i<2; i++) fRec17[i] = 0;
		for (int i=0; i<8192; i++) fVec4[i] = 0;
		for (int i=0; i<2; i++) fRec16[i] = 0;
		for (int i=0; i<2; i++) fRec19[i] = 0;
		for (int i=0; i<8192; i++) fVec5[i] = 0;
		for (int i=0; i<2; i++) fRec18[i] = 0;
		for (int i=0; i<2; i++) fRec21[i] = 0;
		for (int i=0; i<8192; i++) fVec6[i] = 0;
		for (int i=0; i<2; i++) fRec20[i] = 0;
		for (int i=0; i<2; i++) fRec23[i] = 0;
		for (int i=0; i<8192; i++) fVec7[i] = 0;
		for (int i=0; i<2; i++) fRec22[i] = 0;
		for (int i=0; i<2048; i++) fVec8[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<2048; i++) fVec9[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2048; i++) fVec10[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<1024; i++) fVec11[i] = 0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fRec33[i] = 0;
		for (int i=0; i<8192; i++) fVec12[i] = 0;
		for (int i=0; i<2; i++) fRec32[i] = 0;
		for (int i=0; i<2; i++) fRec35[i] = 0;
		for (int i=0; i<8192; i++) fVec13[i] = 0;
		for (int i=0; i<2; i++) fRec34[i] = 0;
		for (int i=0; i<2; i++) fRec37[i] = 0;
		for (int i=0; i<8192; i++) fVec14[i] = 0;
		for (int i=0; i<2; i++) fRec36[i] = 0;
		for (int i=0; i<2; i++) fRec39[i] = 0;
		for (int i=0; i<8192; i++) fVec15[i] = 0;
		for (int i=0; i<2; i++) fRec38[i] = 0;
		for (int i=0; i<2; i++) fRec41[i] = 0;
		for (int i=0; i<8192; i++) fVec16[i] = 0;
		for (int i=0; i<2; i++) fRec40[i] = 0;
		for (int i=0; i<2; i++) fRec43[i] = 0;
		for (int i=0; i<8192; i++) fVec17[i] = 0;
		for (int i=0; i<2; i++) fRec42[i] = 0;
		for (int i=0; i<2; i++) fRec45[i] = 0;
		for (int i=0; i<8192; i++) fVec18[i] = 0;
		for (int i=0; i<2; i++) fRec44[i] = 0;
		for (int i=0; i<2; i++) fRec47[i] = 0;
		for (int i=0; i<8192; i++) fVec19[i] = 0;
		for (int i=0; i<2; i++) fRec46[i] = 0;
		for (int i=0; i<2048; i++) fVec20[i] = 0;
		for (int i=0; i<2; i++) fRec30[i] = 0;
		for (int i=0; i<2048; i++) fVec21[i] = 0;
		for (int i=0; i<2; i++) fRec28[i] = 0;
		for (int i=0; i<2048; i++) fVec22[i] = 0;
		for (int i=0; i<2; i++) fRec26[i] = 0;
		for (int i=0; i<2048; i++) fVec23[i] = 0;
		for (int i=0; i<2; i++) fRec24[i] = 0;
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
		ui_interface->openHorizontalBox("Freeverb");
		ui_interface->declare(0, "0", "");
		ui_interface->openVerticalBox("0x00");
		ui_interface->declare(&fslider2, "0", "");
		ui_interface->declare(&fslider2, "style", "knob");
		ui_interface->declare(&fslider2, "tooltip", "Somehow control the   density of the reverb.");
		ui_interface->addVerticalSlider("Damp", &fslider2, 0.5f, 0.0f, 1.0f, 0.025000000000000001f);
		ui_interface->declare(&fslider1, "1", "");
		ui_interface->declare(&fslider1, "style", "knob");
		ui_interface->declare(&fslider1, "tooltip", "The room size   between 0 and 1 with 1 for the largest room.");
		ui_interface->addVerticalSlider("RoomSize", &fslider1, 0.5f, 0.0f, 1.0f, 0.025000000000000001f);
		ui_interface->declare(&fslider3, "2", "");
		ui_interface->declare(&fslider3, "style", "knob");
		ui_interface->declare(&fslider3, "tooltip", "Spatial   spread between 0 and 1 with 1 for maximum spread.");
		ui_interface->addVerticalSlider("Stereo Spread", &fslider3, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->declare(&fslider0, "1", "");
		ui_interface->declare(&fslider0, "tooltip", "The amount of reverb applied to the signal   between 0 and 1 with 1 for the maximum amount of reverb.");
		ui_interface->addVerticalSlider("Wet", &fslider0, 0.33329999999999999f, 0.0f, 1.0f, 0.025000000000000001f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = float(fslider0);
		float 	fSlow1 = (0.10000000000000001f * fSlow0);
		float 	fSlow2 = ((fConst1 * float(fslider1)) + 0.69999999999999996f);
		float 	fSlow3 = (fConst2 * float(fslider2));
		float 	fSlow4 = (1 - fSlow3);
		float 	fSlow5 = (1 - fSlow0);
		int 	iSlow6 = int((fConst19 * float(fslider3)));
		int 	iSlow7 = int((iConst7 + iSlow6));
		int 	iSlow8 = int((iConst8 + iSlow6));
		int 	iSlow9 = int((iConst9 + iSlow6));
		int 	iSlow10 = int((iConst10 + iSlow6));
		int 	iSlow11 = int((iConst5 + iSlow6));
		int 	iSlow12 = int((iConst6 + iSlow6));
		int 	iSlow13 = int((iConst4 + iSlow6));
		int 	iSlow14 = int((iConst3 + iSlow6));
		int 	iSlow15 = (iSlow6 + -1);
		int 	iSlow16 = int(min(1024, max(0, (iConst11 + iSlow15))));
		int 	iSlow17 = int(min(1024, max(0, (iConst13 + iSlow15))));
		int 	iSlow18 = int(min(1024, max(0, (iConst15 + iSlow15))));
		int 	iSlow19 = int(min(1024, max(0, (iConst17 + iSlow15))));
		//zone2b
		//zone3
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* input1 = input[1];
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fTempPerm0 = (float)input0[i];
			fTempPerm1 = (float)input1[i];
			fTempPerm2 = (fSlow1 * (fTempPerm0 + fTempPerm1));
			fRec9[0] = ((fSlow3 * fRec9[1]) + (fSlow4 * fRec8[1]));
			fVec0[IOTA&8191] = (fTempPerm2 + (fSlow2 * fRec9[0]));
			fRec8[0] = fVec0[(IOTA-iConst3)&8191];
			fRec11[0] = ((fSlow3 * fRec11[1]) + (fSlow4 * fRec10[1]));
			fVec1[IOTA&8191] = (fTempPerm2 + (fSlow2 * fRec11[0]));
			fRec10[0] = fVec1[(IOTA-iConst4)&8191];
			fRec13[0] = ((fSlow3 * fRec13[1]) + (fSlow4 * fRec12[1]));
			fVec2[IOTA&8191] = (fTempPerm2 + (fSlow2 * fRec13[0]));
			fRec12[0] = fVec2[(IOTA-iConst5)&8191];
			fRec15[0] = ((fSlow3 * fRec15[1]) + (fSlow4 * fRec14[1]));
			fVec3[IOTA&8191] = (fTempPerm2 + (fSlow2 * fRec15[0]));
			fRec14[0] = fVec3[(IOTA-iConst6)&8191];
			fRec17[0] = ((fSlow3 * fRec17[1]) + (fSlow4 * fRec16[1]));
			fVec4[IOTA&8191] = ((fSlow2 * fRec17[0]) + fTempPerm2);
			fRec16[0] = fVec4[(IOTA-iConst7)&8191];
			fRec19[0] = ((fSlow3 * fRec19[1]) + (fSlow4 * fRec18[1]));
			fVec5[IOTA&8191] = (fTempPerm2 + (fSlow2 * fRec19[0]));
			fRec18[0] = fVec5[(IOTA-iConst8)&8191];
			fRec21[0] = ((fSlow3 * fRec21[1]) + (fSlow4 * fRec20[1]));
			fVec6[IOTA&8191] = (fTempPerm2 + (fSlow2 * fRec21[0]));
			fRec20[0] = fVec6[(IOTA-iConst9)&8191];
			fRec23[0] = ((fSlow3 * fRec23[1]) + (fSlow4 * fRec22[1]));
			fVec7[IOTA&8191] = (fTempPerm2 + (fSlow2 * fRec23[0]));
			fRec22[0] = fVec7[(IOTA-iConst10)&8191];
			fTempPerm3 = ((((((0.5f * fRec6[1]) + (fRec8[0] + (fRec10[0] + (fRec12[0] + fRec14[0])))) + fRec16[0]) + fRec18[0]) + fRec20[0]) + fRec22[0]);
			fVec8[IOTA&2047] = fTempPerm3;
			fRec6[0] = fVec8[(IOTA-iConst12)&2047];
			float 	fRec7 = (0 - (0.5f * fVec8[IOTA&2047]));
			fTempPerm4 = (fRec6[1] + (fRec7 + (0.5f * fRec4[1])));
			fVec9[IOTA&2047] = fTempPerm4;
			fRec4[0] = fVec9[(IOTA-iConst14)&2047];
			float 	fRec5 = (0 - (0.5f * fVec9[IOTA&2047]));
			fTempPerm5 = (fRec4[1] + (fRec5 + (0.5f * fRec2[1])));
			fVec10[IOTA&2047] = fTempPerm5;
			fRec2[0] = fVec10[(IOTA-iConst16)&2047];
			float 	fRec3 = (0 - (0.5f * fVec10[IOTA&2047]));
			fTempPerm6 = (fRec2[1] + (fRec3 + (0.5f * fRec0[1])));
			fVec11[IOTA&1023] = fTempPerm6;
			fRec0[0] = fVec11[(IOTA-iConst18)&1023];
			float 	fRec1 = (0 - (0.5f * fVec11[IOTA&1023]));
			output0[i] = (FAUSTFLOAT)((fRec1 + fRec0[1]) + (fSlow5 * fTempPerm0));
			fRec33[0] = ((fSlow3 * fRec33[1]) + (fSlow4 * fRec32[1]));
			fVec12[IOTA&8191] = (fTempPerm2 + (fSlow2 * fRec33[0]));
			fRec32[0] = fVec12[(IOTA-iSlow7)&8191];
			fRec35[0] = ((fSlow3 * fRec35[1]) + (fSlow4 * fRec34[1]));
			fVec13[IOTA&8191] = (fTempPerm2 + (fSlow2 * fRec35[0]));
			fRec34[0] = fVec13[(IOTA-iSlow8)&8191];
			fRec37[0] = ((fSlow3 * fRec37[1]) + (fSlow4 * fRec36[1]));
			fVec14[IOTA&8191] = (fTempPerm2 + (fSlow2 * fRec37[0]));
			fRec36[0] = fVec14[(IOTA-iSlow9)&8191];
			fRec39[0] = ((fSlow3 * fRec39[1]) + (fSlow4 * fRec38[1]));
			fVec15[IOTA&8191] = (fTempPerm2 + (fSlow2 * fRec39[0]));
			fRec38[0] = fVec15[(IOTA-iSlow10)&8191];
			fRec41[0] = ((fSlow3 * fRec41[1]) + (fSlow4 * fRec40[1]));
			fVec16[IOTA&8191] = (fTempPerm2 + (fSlow2 * fRec41[0]));
			fRec40[0] = fVec16[(IOTA-iSlow11)&8191];
			fRec43[0] = ((fSlow3 * fRec43[1]) + (fSlow4 * fRec42[1]));
			fVec17[IOTA&8191] = (fTempPerm2 + (fSlow2 * fRec43[0]));
			fRec42[0] = fVec17[(IOTA-iSlow12)&8191];
			fRec45[0] = ((fSlow3 * fRec45[1]) + (fSlow4 * fRec44[1]));
			fVec18[IOTA&8191] = (fTempPerm2 + (fSlow2 * fRec45[0]));
			fRec44[0] = fVec18[(IOTA-iSlow13)&8191];
			fRec47[0] = ((fSlow3 * fRec47[1]) + (fSlow4 * fRec46[1]));
			fVec19[IOTA&8191] = (fTempPerm2 + (fSlow2 * fRec47[0]));
			fRec46[0] = fVec19[(IOTA-iSlow14)&8191];
			fTempPerm7 = ((((((((fRec32[0] + fRec34[0]) + fRec36[0]) + fRec38[0]) + fRec40[0]) + fRec42[0]) + fRec44[0]) + fRec46[0]) + (0.5f * fRec30[1]));
			fVec20[IOTA&2047] = fTempPerm7;
			fRec30[0] = fVec20[(IOTA-iSlow16)&2047];
			float 	fRec31 = (0 - (0.5f * fVec20[IOTA&2047]));
			fTempPerm8 = (fRec30[1] + (fRec31 + (0.5f * fRec28[1])));
			fVec21[IOTA&2047] = fTempPerm8;
			fRec28[0] = fVec21[(IOTA-iSlow17)&2047];
			float 	fRec29 = (0 - (0.5f * fVec21[IOTA&2047]));
			fTempPerm9 = (fRec28[1] + (fRec29 + (0.5f * fRec26[1])));
			fVec22[IOTA&2047] = fTempPerm9;
			fRec26[0] = fVec22[(IOTA-iSlow18)&2047];
			float 	fRec27 = (0 - (0.5f * fVec22[IOTA&2047]));
			fTempPerm10 = (fRec26[1] + (fRec27 + (0.5f * fRec24[1])));
			fVec23[IOTA&2047] = fTempPerm10;
			fRec24[0] = fVec23[(IOTA-iSlow19)&2047];
			float 	fRec25 = (0 - (0.5f * fVec23[IOTA&2047]));
			output1[i] = (FAUSTFLOAT)((fSlow5 * fTempPerm1) + (fRec25 + fRec24[1]));
			// post processing
			fRec24[1] = fRec24[0];
			fRec26[1] = fRec26[0];
			fRec28[1] = fRec28[0];
			fRec30[1] = fRec30[0];
			fRec46[1] = fRec46[0];
			fRec47[1] = fRec47[0];
			fRec44[1] = fRec44[0];
			fRec45[1] = fRec45[0];
			fRec42[1] = fRec42[0];
			fRec43[1] = fRec43[0];
			fRec40[1] = fRec40[0];
			fRec41[1] = fRec41[0];
			fRec38[1] = fRec38[0];
			fRec39[1] = fRec39[0];
			fRec36[1] = fRec36[0];
			fRec37[1] = fRec37[0];
			fRec34[1] = fRec34[0];
			fRec35[1] = fRec35[0];
			fRec32[1] = fRec32[0];
			fRec33[1] = fRec33[0];
			fRec0[1] = fRec0[0];
			fRec2[1] = fRec2[0];
			fRec4[1] = fRec4[0];
			fRec6[1] = fRec6[0];
			fRec22[1] = fRec22[0];
			fRec23[1] = fRec23[0];
			fRec20[1] = fRec20[0];
			fRec21[1] = fRec21[0];
			fRec18[1] = fRec18[0];
			fRec19[1] = fRec19[0];
			fRec16[1] = fRec16[0];
			fRec17[1] = fRec17[0];
			fRec14[1] = fRec14[0];
			fRec15[1] = fRec15[0];
			fRec12[1] = fRec12[0];
			fRec13[1] = fRec13[0];
			fRec10[1] = fRec10[0];
			fRec11[1] = fRec11[0];
			fRec8[1] = fRec8[0];
			IOTA = IOTA+1;
			fRec9[1] = fRec9[0];
		}
	}
};


