//----------------------------------------------------------
// copyright: "(c) 2017: Yann Orlarey, GRAME"
// license: "MIT"
// name: "bubble"
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
	int 	iVec0[2];
	float 	fRec9[2];
	FAUSTFLOAT 	fslider2;
	float 	fConst3;
	FAUSTFLOAT 	fslider3;
	float 	fConst4;
	FAUSTFLOAT 	fbutton0;
	float 	fVec1[2];
	int 	iRec12[2];
	float 	fTempPerm0;
	float 	fTempPerm1;
	float 	fTempPerm2;
	float 	fRec10[2];
	float 	fRec11[2];
	float 	fConst5;
	float 	fRec13[2];
	float 	fTempPerm3;
	float 	fTempPerm4;
	int 	IOTA;
	float 	fVec2[8192];
	int 	iConst6;
	float 	fRec8[2];
	float 	fRec15[2];
	float 	fVec3[8192];
	int 	iConst7;
	float 	fRec14[2];
	float 	fRec17[2];
	float 	fVec4[8192];
	int 	iConst8;
	float 	fRec16[2];
	float 	fRec19[2];
	float 	fVec5[8192];
	int 	iConst9;
	float 	fRec18[2];
	float 	fRec21[2];
	float 	fVec6[8192];
	int 	iConst10;
	float 	fRec20[2];
	float 	fRec23[2];
	float 	fVec7[8192];
	int 	iConst11;
	float 	fRec22[2];
	float 	fRec25[2];
	float 	fVec8[8192];
	int 	iConst12;
	float 	fRec24[2];
	float 	fRec27[2];
	float 	fVec9[8192];
	int 	iConst13;
	float 	fRec26[2];
	float 	fTempPerm5;
	float 	fVec10[2048];
	int 	iConst14;
	int 	iConst15;
	float 	fRec6[2];
	float 	fTempPerm6;
	float 	fVec11[2048];
	int 	iConst16;
	int 	iConst17;
	float 	fRec4[2];
	float 	fTempPerm7;
	float 	fVec12[2048];
	int 	iConst18;
	int 	iConst19;
	float 	fRec2[2];
	float 	fTempPerm8;
	float 	fVec13[1024];
	int 	iConst20;
	int 	iConst21;
	float 	fRec0[2];
	float 	fTempPerm9;
	float 	fRec37[2];
	float 	fVec14[8192];
	float 	fConst22;
	FAUSTFLOAT 	fslider4;
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
	float 	fRec49[2];
	float 	fVec20[8192];
	float 	fRec48[2];
	float 	fRec51[2];
	float 	fVec21[8192];
	float 	fRec50[2];
	float 	fTempPerm10;
	float 	fVec22[2048];
	float 	fRec34[2];
	float 	fTempPerm11;
	float 	fVec23[2048];
	float 	fRec32[2];
	float 	fTempPerm12;
	float 	fVec24[2048];
	float 	fRec30[2];
	float 	fTempPerm13;
	float 	fVec25[2048];
	float 	fRec28[2];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("copyright", "(c) 2017: Yann Orlarey, GRAME");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("description", "Production of a water drop bubble sound.");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("license", "MIT");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "bubble");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("reverbs.lib/name", "Faust Reverb Library");
		m->declare("reverbs.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
	}

	virtual int getNumInputs() { return 0; }
	virtual int getNumOutputs() { return 2; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(192000.0f, max(1.0f, (float)fSamplingFreq));
		fConst1 = (12348.000000000002f / fConst0);
		fConst2 = (17640.0f / fConst0);
		fConst3 = (6.2831853071795862f / fConst0);
		fConst4 = (0.074999999999999997f / fConst0);
		fTempPerm0 = 0;
		fTempPerm1 = 0;
		fTempPerm2 = 0;
		fConst5 = (1.0f / fConst0);
		fTempPerm3 = 0;
		fTempPerm4 = 0;
		iConst6 = int((0.025306122448979593f * fConst0));
		iConst7 = int((0.026938775510204082f * fConst0));
		iConst8 = int((0.028956916099773241f * fConst0));
		iConst9 = int((0.03074829931972789f * fConst0));
		iConst10 = int((0.032244897959183672f * fConst0));
		iConst11 = int((0.03380952380952381f * fConst0));
		iConst12 = int((0.035306122448979592f * fConst0));
		iConst13 = int((0.036666666666666667f * fConst0));
		fTempPerm5 = 0;
		iConst14 = int((0.012607709750566893f * fConst0));
		iConst15 = int(min(1024, max(0, (iConst14 + -1))));
		fTempPerm6 = 0;
		iConst16 = int((0.01f * fConst0));
		iConst17 = int(min(1024, max(0, (iConst16 + -1))));
		fTempPerm7 = 0;
		iConst18 = int((0.007732426303854875f * fConst0));
		iConst19 = int(min(1024, max(0, (iConst18 + -1))));
		fTempPerm8 = 0;
		iConst20 = int((0.0051020408163265302f * fConst0));
		iConst21 = int(min(1024, max(0, (iConst20 + -1))));
		fTempPerm9 = 0;
		fConst22 = (0.0010430839002267573f * fConst0);
		fTempPerm10 = 0;
		fTempPerm11 = 0;
		fTempPerm12 = 0;
		fTempPerm13 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.5f;
		fslider1 = 0.5f;
		fslider2 = 0.33329999999999999f;
		fslider3 = 600.0f;
		fbutton0 = 0.0;
		fslider4 = 0.5f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) iVec0[i] = 0;
		for (int i=0; i<2; i++) fRec9[i] = 0;
		for (int i=0; i<2; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) iRec12[i] = 0;
		for (int i=0; i<2; i++) fRec10[i] = 0;
		for (int i=0; i<2; i++) fRec11[i] = 0;
		for (int i=0; i<2; i++) fRec13[i] = 0;
		IOTA = 0;
		for (int i=0; i<8192; i++) fVec2[i] = 0;
		for (int i=0; i<2; i++) fRec8[i] = 0;
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
		for (int i=0; i<2; i++) fRec25[i] = 0;
		for (int i=0; i<8192; i++) fVec8[i] = 0;
		for (int i=0; i<2; i++) fRec24[i] = 0;
		for (int i=0; i<2; i++) fRec27[i] = 0;
		for (int i=0; i<8192; i++) fVec9[i] = 0;
		for (int i=0; i<2; i++) fRec26[i] = 0;
		for (int i=0; i<2048; i++) fVec10[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<2048; i++) fVec11[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2048; i++) fVec12[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<1024; i++) fVec13[i] = 0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
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
		for (int i=0; i<2; i++) fRec49[i] = 0;
		for (int i=0; i<8192; i++) fVec20[i] = 0;
		for (int i=0; i<2; i++) fRec48[i] = 0;
		for (int i=0; i<2; i++) fRec51[i] = 0;
		for (int i=0; i<8192; i++) fVec21[i] = 0;
		for (int i=0; i<2; i++) fRec50[i] = 0;
		for (int i=0; i<2048; i++) fVec22[i] = 0;
		for (int i=0; i<2; i++) fRec34[i] = 0;
		for (int i=0; i<2048; i++) fVec23[i] = 0;
		for (int i=0; i<2; i++) fRec32[i] = 0;
		for (int i=0; i<2048; i++) fVec24[i] = 0;
		for (int i=0; i<2; i++) fRec30[i] = 0;
		for (int i=0; i<2048; i++) fVec25[i] = 0;
		for (int i=0; i<2; i++) fRec28[i] = 0;
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
		ui_interface->openVerticalBox("bubble");
		ui_interface->openHorizontalBox("Freeverb");
		ui_interface->declare(0, "0", "");
		ui_interface->openVerticalBox("0x00");
		ui_interface->declare(&fslider1, "0", "");
		ui_interface->declare(&fslider1, "style", "knob");
		ui_interface->declare(&fslider1, "tooltip", "Somehow control the   density of the reverb.");
		ui_interface->addVerticalSlider("Damp", &fslider1, 0.5f, 0.0f, 1.0f, 0.025000000000000001f);
		ui_interface->declare(&fslider0, "1", "");
		ui_interface->declare(&fslider0, "style", "knob");
		ui_interface->declare(&fslider0, "tooltip", "The room size   between 0 and 1 with 1 for the largest room.");
		ui_interface->addVerticalSlider("RoomSize", &fslider0, 0.5f, 0.0f, 1.0f, 0.025000000000000001f);
		ui_interface->declare(&fslider4, "2", "");
		ui_interface->declare(&fslider4, "style", "knob");
		ui_interface->declare(&fslider4, "tooltip", "Spatial   spread between 0 and 1 with 1 for maximum spread.");
		ui_interface->addVerticalSlider("Stereo Spread", &fslider4, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->declare(&fslider2, "1", "");
		ui_interface->declare(&fslider2, "tooltip", "The amount of reverb applied to the signal   between 0 and 1 with 1 for the maximum amount of reverb.");
		ui_interface->addVerticalSlider("Wet", &fslider2, 0.33329999999999999f, 0.0f, 1.0f, 0.025000000000000001f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("bubble");
		ui_interface->addHorizontalSlider("freq", &fslider3, 600.0f, 150.0f, 2000.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->addButton("drop", &fbutton0);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = ((fConst1 * float(fslider0)) + 0.69999999999999996f);
		float 	fSlow1 = (fConst2 * float(fslider1));
		float 	fSlow2 = (1 - fSlow1);
		float 	fSlow3 = float(fslider2);
		float 	fSlow4 = (0.20000000000000001f * fSlow3);
		float 	fSlow5 = float(fslider3);
		float 	fSlow6 = (fConst3 * fSlow5);
		float 	fSlow7 = ((0.042999999999999997f * fSlow5) + (0.0014f * powf(fSlow5,1.5f)));
		float 	fSlow8 = (fConst4 * fSlow7);
		float 	fSlow9 = float(fbutton0);
		float 	fSlow10 = (fConst5 * (0 - fSlow7));
		float 	fSlow11 = (1 - fSlow3);
		int 	iSlow12 = int((fConst22 * float(fslider4)));
		int 	iSlow13 = int((iConst6 + iSlow12));
		int 	iSlow14 = int((iConst7 + iSlow12));
		int 	iSlow15 = int((iConst8 + iSlow12));
		int 	iSlow16 = int((iConst9 + iSlow12));
		int 	iSlow17 = int((iConst10 + iSlow12));
		int 	iSlow18 = int((iConst11 + iSlow12));
		int 	iSlow19 = int((iConst12 + iSlow12));
		int 	iSlow20 = int((iConst13 + iSlow12));
		int 	iSlow21 = (iSlow12 + -1);
		int 	iSlow22 = int(min(1024, max(0, (iConst14 + iSlow21))));
		int 	iSlow23 = int(min(1024, max(0, (iConst16 + iSlow21))));
		int 	iSlow24 = int(min(1024, max(0, (iConst18 + iSlow21))));
		int 	iSlow25 = int(min(1024, max(0, (iConst20 + iSlow21))));
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			iVec0[0] = 1;
			fRec9[0] = ((fSlow1 * fRec9[1]) + (fSlow2 * fRec8[1]));
			fVec1[0] = fSlow9;
			iRec12[0] = (((int((fSlow9 > fVec1[1])))?0:iRec12[1]) + 1);
			fTempPerm0 = (fSlow6 * ((fSlow8 * iRec12[0]) + 1));
			fTempPerm1 = sinf(fTempPerm0);
			fTempPerm2 = cosf(fTempPerm0);
			fRec10[0] = ((fRec11[1] * fTempPerm1) + (fRec10[1] * fTempPerm2));
			fRec11[0] = (((fRec11[1] * fTempPerm2) + (fRec10[1] * (0 - fTempPerm1))) + (1 - iVec0[1]));
			fRec13[0] = ((0.98999999999999999f * fRec13[1]) + (0.010000000000000009f * expf((fSlow10 * iRec12[0]))));
			fTempPerm3 = (fRec10[0] * fRec13[0]);
			fTempPerm4 = (fSlow4 * fTempPerm3);
			fVec2[IOTA&8191] = ((fSlow0 * fRec9[0]) + fTempPerm4);
			fRec8[0] = fVec2[(IOTA-iConst6)&8191];
			fRec15[0] = ((fSlow1 * fRec15[1]) + (fSlow2 * fRec14[1]));
			fVec3[IOTA&8191] = (fTempPerm4 + (fSlow0 * fRec15[0]));
			fRec14[0] = fVec3[(IOTA-iConst7)&8191];
			fRec17[0] = ((fSlow1 * fRec17[1]) + (fSlow2 * fRec16[1]));
			fVec4[IOTA&8191] = (fTempPerm4 + (fSlow0 * fRec17[0]));
			fRec16[0] = fVec4[(IOTA-iConst8)&8191];
			fRec19[0] = ((fSlow1 * fRec19[1]) + (fSlow2 * fRec18[1]));
			fVec5[IOTA&8191] = (fTempPerm4 + (fSlow0 * fRec19[0]));
			fRec18[0] = fVec5[(IOTA-iConst9)&8191];
			fRec21[0] = ((fSlow1 * fRec21[1]) + (fSlow2 * fRec20[1]));
			fVec6[IOTA&8191] = (fTempPerm4 + (fSlow0 * fRec21[0]));
			fRec20[0] = fVec6[(IOTA-iConst10)&8191];
			fRec23[0] = ((fSlow1 * fRec23[1]) + (fSlow2 * fRec22[1]));
			fVec7[IOTA&8191] = (fTempPerm4 + (fSlow0 * fRec23[0]));
			fRec22[0] = fVec7[(IOTA-iConst11)&8191];
			fRec25[0] = ((fSlow1 * fRec25[1]) + (fSlow2 * fRec24[1]));
			fVec8[IOTA&8191] = (fTempPerm4 + (fSlow0 * fRec25[0]));
			fRec24[0] = fVec8[(IOTA-iConst12)&8191];
			fRec27[0] = ((fSlow1 * fRec27[1]) + (fSlow2 * fRec26[1]));
			fVec9[IOTA&8191] = (fTempPerm4 + (fSlow0 * fRec27[0]));
			fRec26[0] = fVec9[(IOTA-iConst13)&8191];
			fTempPerm5 = ((((((((fRec8[0] + fRec14[0]) + fRec16[0]) + fRec18[0]) + fRec20[0]) + fRec22[0]) + fRec24[0]) + fRec26[0]) + (0.5f * fRec6[1]));
			fVec10[IOTA&2047] = fTempPerm5;
			fRec6[0] = fVec10[(IOTA-iConst15)&2047];
			float 	fRec7 = (0 - (0.5f * fVec10[IOTA&2047]));
			fTempPerm6 = (fRec6[1] + (fRec7 + (0.5f * fRec4[1])));
			fVec11[IOTA&2047] = fTempPerm6;
			fRec4[0] = fVec11[(IOTA-iConst17)&2047];
			float 	fRec5 = (0 - (0.5f * fVec11[IOTA&2047]));
			fTempPerm7 = (fRec4[1] + (fRec5 + (0.5f * fRec2[1])));
			fVec12[IOTA&2047] = fTempPerm7;
			fRec2[0] = fVec12[(IOTA-iConst19)&2047];
			float 	fRec3 = (0 - (0.5f * fVec12[IOTA&2047]));
			fTempPerm8 = (fRec2[1] + (fRec3 + (0.5f * fRec0[1])));
			fVec13[IOTA&1023] = fTempPerm8;
			fRec0[0] = fVec13[(IOTA-iConst21)&1023];
			float 	fRec1 = (0 - (0.5f * fVec13[IOTA&1023]));
			fTempPerm9 = (fSlow11 * fTempPerm3);
			output0[i] = (FAUSTFLOAT)((fRec1 + fRec0[1]) + fTempPerm9);
			fRec37[0] = ((fSlow1 * fRec37[1]) + (fSlow2 * fRec36[1]));
			fVec14[IOTA&8191] = (fTempPerm4 + (fSlow0 * fRec37[0]));
			fRec36[0] = fVec14[(IOTA-iSlow13)&8191];
			fRec39[0] = ((fSlow1 * fRec39[1]) + (fSlow2 * fRec38[1]));
			fVec15[IOTA&8191] = (fTempPerm4 + (fSlow0 * fRec39[0]));
			fRec38[0] = fVec15[(IOTA-iSlow14)&8191];
			fRec41[0] = ((fSlow1 * fRec41[1]) + (fSlow2 * fRec40[1]));
			fVec16[IOTA&8191] = (fTempPerm4 + (fSlow0 * fRec41[0]));
			fRec40[0] = fVec16[(IOTA-iSlow15)&8191];
			fRec43[0] = ((fSlow1 * fRec43[1]) + (fSlow2 * fRec42[1]));
			fVec17[IOTA&8191] = (fTempPerm4 + (fSlow0 * fRec43[0]));
			fRec42[0] = fVec17[(IOTA-iSlow16)&8191];
			fRec45[0] = ((fSlow1 * fRec45[1]) + (fSlow2 * fRec44[1]));
			fVec18[IOTA&8191] = (fTempPerm4 + (fSlow0 * fRec45[0]));
			fRec44[0] = fVec18[(IOTA-iSlow17)&8191];
			fRec47[0] = ((fSlow1 * fRec47[1]) + (fSlow2 * fRec46[1]));
			fVec19[IOTA&8191] = (fTempPerm4 + (fSlow0 * fRec47[0]));
			fRec46[0] = fVec19[(IOTA-iSlow18)&8191];
			fRec49[0] = ((fSlow1 * fRec49[1]) + (fSlow2 * fRec48[1]));
			fVec20[IOTA&8191] = (fTempPerm4 + (fSlow0 * fRec49[0]));
			fRec48[0] = fVec20[(IOTA-iSlow19)&8191];
			fRec51[0] = ((fSlow1 * fRec51[1]) + (fSlow2 * fRec50[1]));
			fVec21[IOTA&8191] = (fTempPerm4 + (fSlow0 * fRec51[0]));
			fRec50[0] = fVec21[(IOTA-iSlow20)&8191];
			fTempPerm10 = ((((((((fRec36[0] + fRec38[0]) + fRec40[0]) + fRec42[0]) + fRec44[0]) + fRec46[0]) + fRec48[0]) + fRec50[0]) + (0.5f * fRec34[1]));
			fVec22[IOTA&2047] = fTempPerm10;
			fRec34[0] = fVec22[(IOTA-iSlow22)&2047];
			float 	fRec35 = (0 - (0.5f * fVec22[IOTA&2047]));
			fTempPerm11 = (fRec34[1] + (fRec35 + (0.5f * fRec32[1])));
			fVec23[IOTA&2047] = fTempPerm11;
			fRec32[0] = fVec23[(IOTA-iSlow23)&2047];
			float 	fRec33 = (0 - (0.5f * fVec23[IOTA&2047]));
			fTempPerm12 = (fRec32[1] + (fRec33 + (0.5f * fRec30[1])));
			fVec24[IOTA&2047] = fTempPerm12;
			fRec30[0] = fVec24[(IOTA-iSlow24)&2047];
			float 	fRec31 = (0 - (0.5f * fVec24[IOTA&2047]));
			fTempPerm13 = (fRec30[1] + (fRec31 + (0.5f * fRec28[1])));
			fVec25[IOTA&2047] = fTempPerm13;
			fRec28[0] = fVec25[(IOTA-iSlow25)&2047];
			float 	fRec29 = (0 - (0.5f * fVec25[IOTA&2047]));
			output1[i] = (FAUSTFLOAT)(fRec28[1] + (fRec29 + fTempPerm9));
			// post processing
			fRec28[1] = fRec28[0];
			fRec30[1] = fRec30[0];
			fRec32[1] = fRec32[0];
			fRec34[1] = fRec34[0];
			fRec50[1] = fRec50[0];
			fRec51[1] = fRec51[0];
			fRec48[1] = fRec48[0];
			fRec49[1] = fRec49[0];
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
			fRec0[1] = fRec0[0];
			fRec2[1] = fRec2[0];
			fRec4[1] = fRec4[0];
			fRec6[1] = fRec6[0];
			fRec26[1] = fRec26[0];
			fRec27[1] = fRec27[0];
			fRec24[1] = fRec24[0];
			fRec25[1] = fRec25[0];
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
			fRec8[1] = fRec8[0];
			IOTA = IOTA+1;
			fRec13[1] = fRec13[0];
			fRec11[1] = fRec11[0];
			fRec10[1] = fRec10[0];
			iRec12[1] = iRec12[0];
			fVec1[1] = fVec1[0];
			fRec9[1] = fRec9[0];
			iVec0[1] = iVec0[0];
		}
	}
};


