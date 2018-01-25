//----------------------------------------------------------
// name: "crazyGuiro"
//
// Code generated with Faust 2.5.15 (https://faust.grame.fr)
//----------------------------------------------------------

/* link with  */
#include <math.h>
#ifndef FAUSTPOWER
#define FAUSTPOWER
#include <cmath>
template <int N> inline int faustpower(int x)              { return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline int faustpower<0>(int x)            { return 1; }
template <> 	 inline int faustpower<1>(int x)            { return x; }
template <> 	 inline int faustpower<2>(int x)            { return x*x; }
template <int N> inline float faustpower(float x)            { return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline float faustpower<0>(float x)          { return 1; }
template <> 	 inline float faustpower<1>(float x)          { return x; }
template <> 	 inline float faustpower<2>(float x)          { return x*x; }
#endif

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
	float 	fRec9[2];
	FAUSTFLOAT 	fslider1;
	float 	fConst0;
	float 	fVec0[2];
	float 	fConst1;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fslider3;
	int 	iRec11[2];
	FAUSTFLOAT 	fbutton0;
	float 	fVec1[2];
	float 	fConst2;
	float 	fRec12[2];
	float 	fConst3;
	int 	iTempPerm0;
	float 	fConst4;
	float 	fRec10[3];
	float 	fTempPerm1;
	float 	fTempPerm2;
	int 	IOTA;
	float 	fVec2[8192];
	int 	iConst5;
	float 	fRec8[2];
	float 	fRec14[2];
	float 	fVec3[8192];
	int 	iConst6;
	float 	fRec13[2];
	float 	fRec16[2];
	float 	fVec4[8192];
	int 	iConst7;
	float 	fRec15[2];
	float 	fRec18[2];
	float 	fVec5[8192];
	int 	iConst8;
	float 	fRec17[2];
	float 	fRec20[2];
	float 	fVec6[8192];
	int 	iConst9;
	float 	fRec19[2];
	float 	fRec22[2];
	float 	fVec7[8192];
	int 	iConst10;
	float 	fRec21[2];
	float 	fRec24[2];
	float 	fVec8[8192];
	int 	iConst11;
	float 	fRec23[2];
	float 	fRec26[2];
	float 	fVec9[8192];
	int 	iConst12;
	float 	fRec25[2];
	float 	fTempPerm3;
	float 	fVec10[2048];
	int 	iConst13;
	float 	fRec6[2];
	float 	fTempPerm4;
	float 	fVec11[2048];
	int 	iConst14;
	float 	fRec4[2];
	float 	fTempPerm5;
	float 	fVec12[2048];
	int 	iConst15;
	float 	fRec2[2];
	float 	fTempPerm6;
	float 	fVec13[1024];
	int 	iConst16;
	float 	fRec0[2];
	float 	fTempPerm7;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("envelopes.lib/author", "GRAME");
		m->declare("envelopes.lib/copyright", "GRAME");
		m->declare("envelopes.lib/license", "LGPL with exception");
		m->declare("envelopes.lib/name", "Faust Envelope Library");
		m->declare("envelopes.lib/version", "0.0");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("interface", "SmartKeyboard{  'Number of Keyboards':'8',  'Keyboard 0 - Number of Keys':'16',  'Keyboard 1 - Number of Keys':'16',  'Keyboard 2 - Number of Keys':'16',  'Keyboard 3 - Number of Keys':'16',  'Keyboard 4 - Number of Keys':'16',  'Keyboard 5 - Number of Keys':'16',  'Keyboard 6 - Number of Keys':'16',  'Keyboard 7 - Number of Keys':'16',  'Keyboard 0 - Piano Keyboard':'0',  'Keyboard 1 - Piano Keyboard':'0',  'Keyboard 2 - Piano Keyboard':'0',  'Keyboard 3 - Piano Keyboard':'0',  'Keyboard 4 - Piano Keyboard':'0',  'Keyboard 5 - Piano Keyboard':'0',  'Keyboard 6 - Piano Keyboard':'0',  'Keyboard 7 - Piano Keyboard':'0' }");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "crazyGuiro");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
		m->declare("reverbs.lib/name", "Faust Reverb Library");
		m->declare("reverbs.lib/version", "0.0");
		m->declare("synths.lib/name", "Faust Synthesizer Library");
		m->declare("synths.lib/version", "0.0");
	}

	virtual int getNumInputs() { return 0; }
	virtual int getNumOutputs() { return 2; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(192000.0f, max(1.0f, (float)fSamplingFreq));
		fConst1 = (1382.3007675795091f / fConst0);
		fConst2 = (0.002f * fConst0);
		fConst3 = (0.001f * fConst0);
		iTempPerm0 = 0;
		fConst4 = (1000.0f / fConst0);
		fTempPerm1 = 0;
		fTempPerm2 = 0;
		iConst5 = int((0.025306122448979593f * fConst0));
		iConst6 = int((0.026938775510204082f * fConst0));
		iConst7 = int((0.028956916099773241f * fConst0));
		iConst8 = int((0.03074829931972789f * fConst0));
		iConst9 = int((0.032244897959183672f * fConst0));
		iConst10 = int((0.03380952380952381f * fConst0));
		iConst11 = int((0.035306122448979592f * fConst0));
		iConst12 = int((0.036666666666666667f * fConst0));
		fTempPerm3 = 0;
		iConst13 = int(min(1024, max(0, (int((0.012607709750566893f * fConst0)) + -1))));
		fTempPerm4 = 0;
		iConst14 = int(min(1024, max(0, (int((0.01f * fConst0)) + -1))));
		fTempPerm5 = 0;
		iConst15 = int(min(1024, max(0, (int((0.007732426303854875f * fConst0)) + -1))));
		fTempPerm6 = 0;
		iConst16 = int(min(1024, max(0, (int((0.0051020408163265302f * fConst0)) + -1))));
		fTempPerm7 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.5f;
		fslider1 = 0.0f;
		fslider2 = 0.0f;
		fslider3 = 0.0f;
		fbutton0 = 0.0;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fRec9[i] = 0;
		for (int i=0; i<2; i++) fVec0[i] = 0;
		for (int i=0; i<2; i++) iRec11[i] = 0;
		for (int i=0; i<2; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fRec12[i] = 0;
		for (int i=0; i<3; i++) fRec10[i] = 0;
		IOTA = 0;
		for (int i=0; i<8192; i++) fVec2[i] = 0;
		for (int i=0; i<2; i++) fRec8[i] = 0;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		for (int i=0; i<8192; i++) fVec3[i] = 0;
		for (int i=0; i<2; i++) fRec13[i] = 0;
		for (int i=0; i<2; i++) fRec16[i] = 0;
		for (int i=0; i<8192; i++) fVec4[i] = 0;
		for (int i=0; i<2; i++) fRec15[i] = 0;
		for (int i=0; i<2; i++) fRec18[i] = 0;
		for (int i=0; i<8192; i++) fVec5[i] = 0;
		for (int i=0; i<2; i++) fRec17[i] = 0;
		for (int i=0; i<2; i++) fRec20[i] = 0;
		for (int i=0; i<8192; i++) fVec6[i] = 0;
		for (int i=0; i<2; i++) fRec19[i] = 0;
		for (int i=0; i<2; i++) fRec22[i] = 0;
		for (int i=0; i<8192; i++) fVec7[i] = 0;
		for (int i=0; i<2; i++) fRec21[i] = 0;
		for (int i=0; i<2; i++) fRec24[i] = 0;
		for (int i=0; i<8192; i++) fVec8[i] = 0;
		for (int i=0; i<2; i++) fRec23[i] = 0;
		for (int i=0; i<2; i++) fRec26[i] = 0;
		for (int i=0; i<8192; i++) fVec9[i] = 0;
		for (int i=0; i<2; i++) fRec25[i] = 0;
		for (int i=0; i<2048; i++) fVec10[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<2048; i++) fVec11[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2048; i++) fVec12[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<1024; i++) fVec13[i] = 0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
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
		ui_interface->openVerticalBox("crazyGuiro");
		ui_interface->addButton("gate", &fbutton0);
		ui_interface->addHorizontalSlider("key", &fslider2, 0.0f, 0.0f, 2.0f, 1.0f);
		ui_interface->addHorizontalSlider("keyboard", &fslider3, 0.0f, 0.0f, 2.0f, 1.0f);
		ui_interface->declare(&fslider0, "acc", "1 0 -10 0 10");
		ui_interface->addHorizontalSlider("res", &fslider0, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider1, "acc", "0 0 -10 0 10");
		ui_interface->addHorizontalSlider("wet", &fslider1, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = float(fslider0);
		float 	fSlow1 = float(fslider1);
		float 	fSlow2 = tanf((fConst1 * powf(2.0f,(0.083333333333333329f * ((float(fslider2) + (8 * float(fslider3))) + -19.0f)))));
		float 	fSlow3 = (1.0f / fSlow2);
		float 	fSlow4 = (((fSlow3 + 0.125f) / fSlow2) + 1);
		float 	fSlow5 = (fSlow1 / fSlow4);
		float 	fSlow6 = float(fbutton0);
		float 	fSlow7 = (1.0f / fSlow4);
		float 	fSlow8 = (((fSlow3 + -0.125f) / fSlow2) + 1);
		float 	fSlow9 = (2 * (1 - (1.0f / faustpower<2>(fSlow2))));
		float 	fSlow10 = (0 - fSlow3);
		float 	fSlow11 = ((1 - fSlow1) / fSlow4);
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fRec9[0] = (0.5f * (fRec9[1] + fRec8[1]));
			fVec0[0] = fConst0;
			iRec11[0] = ((1103515245 * iRec11[1]) + 12345);
			fVec1[0] = fSlow6;
			fRec12[0] = ((int((((fSlow6 - fVec1[1]) > 0) > 0)))?0:min(fConst2, ((fRec12[1] + (0.002f * (fConst0 - fVec0[1]))) + 1)));
			iTempPerm0 = int((fRec12[0] < fConst3));
			fRec10[0] = ((4.6566128752457969e-10f * (iRec11[0] * ((iTempPerm0)?((int((fRec12[0] < 0)))?0:((iTempPerm0)?(fConst4 * fRec12[0]):1)):((int((fRec12[0] < fConst2)))?((fConst4 * (0 - (fRec12[0] - fConst3))) + 1):0)))) - (fSlow7 * ((fSlow8 * fRec10[2]) + (fSlow9 * fRec10[1]))));
			fTempPerm1 = ((fSlow3 * fRec10[0]) + (fSlow10 * fRec10[2]));
			fTempPerm2 = (fSlow5 * fTempPerm1);
			fVec2[IOTA&8191] = ((fSlow0 * fRec9[0]) + fTempPerm2);
			fRec8[0] = fVec2[(IOTA-iConst5)&8191];
			fRec14[0] = (0.5f * (fRec14[1] + fRec13[1]));
			fVec3[IOTA&8191] = (fTempPerm2 + (fSlow0 * fRec14[0]));
			fRec13[0] = fVec3[(IOTA-iConst6)&8191];
			fRec16[0] = (0.5f * (fRec16[1] + fRec15[1]));
			fVec4[IOTA&8191] = (fTempPerm2 + (fSlow0 * fRec16[0]));
			fRec15[0] = fVec4[(IOTA-iConst7)&8191];
			fRec18[0] = (0.5f * (fRec18[1] + fRec17[1]));
			fVec5[IOTA&8191] = (fTempPerm2 + (fSlow0 * fRec18[0]));
			fRec17[0] = fVec5[(IOTA-iConst8)&8191];
			fRec20[0] = (0.5f * (fRec20[1] + fRec19[1]));
			fVec6[IOTA&8191] = (fTempPerm2 + (fSlow0 * fRec20[0]));
			fRec19[0] = fVec6[(IOTA-iConst9)&8191];
			fRec22[0] = (0.5f * (fRec22[1] + fRec21[1]));
			fVec7[IOTA&8191] = (fTempPerm2 + (fSlow0 * fRec22[0]));
			fRec21[0] = fVec7[(IOTA-iConst10)&8191];
			fRec24[0] = (0.5f * (fRec24[1] + fRec23[1]));
			fVec8[IOTA&8191] = (fTempPerm2 + (fSlow0 * fRec24[0]));
			fRec23[0] = fVec8[(IOTA-iConst11)&8191];
			fRec26[0] = (0.5f * (fRec26[1] + fRec25[1]));
			fVec9[IOTA&8191] = (fTempPerm2 + (fSlow0 * fRec26[0]));
			fRec25[0] = fVec9[(IOTA-iConst12)&8191];
			fTempPerm3 = ((((((((fRec8[0] + fRec13[0]) + fRec15[0]) + fRec17[0]) + fRec19[0]) + fRec21[0]) + fRec23[0]) + fRec25[0]) + (0.5f * fRec6[1]));
			fVec10[IOTA&2047] = fTempPerm3;
			fRec6[0] = fVec10[(IOTA-iConst13)&2047];
			float 	fRec7 = (0 - (0.5f * fVec10[IOTA&2047]));
			fTempPerm4 = (fRec6[1] + (fRec7 + (0.5f * fRec4[1])));
			fVec11[IOTA&2047] = fTempPerm4;
			fRec4[0] = fVec11[(IOTA-iConst14)&2047];
			float 	fRec5 = (0 - (0.5f * fVec11[IOTA&2047]));
			fTempPerm5 = (fRec4[1] + (fRec5 + (0.5f * fRec2[1])));
			fVec12[IOTA&2047] = fTempPerm5;
			fRec2[0] = fVec12[(IOTA-iConst15)&2047];
			float 	fRec3 = (0 - (0.5f * fVec12[IOTA&2047]));
			fTempPerm6 = (fRec2[1] + (fRec3 + (0.5f * fRec0[1])));
			fVec13[IOTA&1023] = fTempPerm6;
			fRec0[0] = fVec13[(IOTA-iConst16)&1023];
			float 	fRec1 = (0 - (0.5f * fVec13[IOTA&1023]));
			fTempPerm7 = (fRec0[1] + (fRec1 + (fSlow11 * fTempPerm1)));
			output0[i] = (FAUSTFLOAT)fTempPerm7;
			output1[i] = (FAUSTFLOAT)fTempPerm7;
			// post processing
			fRec0[1] = fRec0[0];
			fRec2[1] = fRec2[0];
			fRec4[1] = fRec4[0];
			fRec6[1] = fRec6[0];
			fRec25[1] = fRec25[0];
			fRec26[1] = fRec26[0];
			fRec23[1] = fRec23[0];
			fRec24[1] = fRec24[0];
			fRec21[1] = fRec21[0];
			fRec22[1] = fRec22[0];
			fRec19[1] = fRec19[0];
			fRec20[1] = fRec20[0];
			fRec17[1] = fRec17[0];
			fRec18[1] = fRec18[0];
			fRec15[1] = fRec15[0];
			fRec16[1] = fRec16[0];
			fRec13[1] = fRec13[0];
			fRec14[1] = fRec14[0];
			fRec8[1] = fRec8[0];
			IOTA = IOTA+1;
			fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
			fRec12[1] = fRec12[0];
			fVec1[1] = fVec1[0];
			iRec11[1] = iRec11[0];
			fVec0[1] = fVec0[0];
			fRec9[1] = fRec9[0];
		}
	}
};


