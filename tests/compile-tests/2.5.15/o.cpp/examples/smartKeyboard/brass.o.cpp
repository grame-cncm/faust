//----------------------------------------------------------
// name: "brass"
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
	int 	iRec6[2];
	float 	fRec13[2];
	float 	fRec14[2];
	FAUSTFLOAT 	fslider0;
	float 	fRec19[2];
	float 	fConst0;
	float 	fConst1;
	float 	fConst2;
	float 	fConst3;
	float 	fConst4;
	int 	iRec21[2];
	float 	fConst5;
	float 	fConst6;
	float 	fConst7;
	float 	fRec20[3];
	float 	fTempPerm0;
	float 	fConst8;
	FAUSTFLOAT 	fslider1;
	float 	fRec22[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT 	fslider4;
	float 	fRec23[2];
	float 	fRec18[3];
	float 	fTempPerm1;
	float 	fTempPerm2;
	float 	fTempPerm3;
	float 	fVec0[2];
	float 	fRec17[2];
	int 	IOTA;
	float 	fRec15[2048];
	float 	fConst9;
	float 	fConst10;
	float 	fTempPerm4;
	float 	fTempPerm5;
	int 	iTempPerm6;
	int 	iTempPerm7;
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
	int 	iTempPerm18;
	float 	fTempPerm19;
	float 	fTempPerm20;
	int 	iTempPerm21;
	float 	fTempPerm22;
	float 	fTempPerm23;
	float 	fTempPerm24;
	float 	fTempPerm25;
	int 	iTempPerm26;
	float 	fTempPerm27;
	float 	fTempPerm28;
	int 	iTempPerm29;
	float 	fVec1[2];
	float 	fRec11[2];
	float 	fRec2[2048];
	float 	fRec0[2];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("interface", "SmartKeyboard{  'Number of Keyboards':'2',  'Max Keyboard Polyphony':'0',  'Keyboard 0 - Number of Keys':'1',   'Keyboard 1 - Number of Keys':'3',  'Keyboard 0 - Send Freq':'0',   'Keyboard 1 - Send Freq':'0',  'Keyboard 0 - Piano Keyboard':'0',   'Keyboard 1 - Piano Keyboard':'0',  'Keyboard 0 - Send Key X':'1',  'Keyboard 1 - Send Key Status':'1',  'Keyboard 0 - Static Mode':'1',  'Keyboard 0 - Key 0 - Label':'Lips Tension',  'Keyboard 1 - Key 0 - Label':'P1',  'Keyboard 1 - Key 1 - Label':'P2',  'Keyboard 1 - Key 2 - Label':'P3' }");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "brass");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "0.0");
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
		fConst1 = tanf((6283.1853071795858f / fConst0));
		fConst2 = (1.0f / fConst1);
		fConst3 = (((fConst2 + 1.4142135623730949f) / fConst1) + 1);
		fConst4 = (0.0050000000000000001f / fConst3);
		fConst5 = (1.0f / fConst3);
		fConst6 = (2 * (1 - (1.0f / faustpower<2>(fConst1))));
		fConst7 = (((fConst2 + -1.4142135623730949f) / fConst1) + 1);
		fTempPerm0 = 0;
		fConst8 = (2136.2830044410593f / fConst0);
		fTempPerm1 = 0;
		fTempPerm2 = 0;
		fTempPerm3 = 0;
		fConst9 = (0.0088235294117647058f * fConst0);
		fConst10 = (0.0014705882352941176f * fConst0);
		fTempPerm4 = 0;
		fTempPerm5 = 0;
		iTempPerm6 = 0;
		iTempPerm7 = 0;
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
		iTempPerm18 = 0;
		fTempPerm19 = 0;
		fTempPerm20 = 0;
		iTempPerm21 = 0;
		fTempPerm22 = 0;
		fTempPerm23 = 0;
		fTempPerm24 = 0;
		fTempPerm25 = 0;
		iTempPerm26 = 0;
		fTempPerm27 = 0;
		fTempPerm28 = 0;
		iTempPerm29 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.0f;
		fslider1 = 0.0f;
		fslider2 = 0.0f;
		fslider3 = 0.0f;
		fslider4 = 0.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) iRec6[i] = 0;
		for (int i=0; i<2; i++) fRec13[i] = 0;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		for (int i=0; i<2; i++) fRec19[i] = 0;
		for (int i=0; i<2; i++) iRec21[i] = 0;
		for (int i=0; i<3; i++) fRec20[i] = 0;
		for (int i=0; i<2; i++) fRec22[i] = 0;
		for (int i=0; i<2; i++) fRec23[i] = 0;
		for (int i=0; i<3; i++) fRec18[i] = 0;
		for (int i=0; i<2; i++) fVec0[i] = 0;
		for (int i=0; i<2; i++) fRec17[i] = 0;
		IOTA = 0;
		for (int i=0; i<2048; i++) fRec15[i] = 0;
		for (int i=0; i<2; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fRec11[i] = 0;
		for (int i=0; i<2048; i++) fRec2[i] = 0;
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
		ui_interface->openVerticalBox("brass");
		ui_interface->addHorizontalSlider("kb0k0x", &fslider1, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->addHorizontalSlider("kb1k0status", &fslider2, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->addHorizontalSlider("kb1k1status", &fslider3, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->addHorizontalSlider("kb1k2status", &fslider4, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->declare(&fslider0, "acc", "1 1 -10 0 10");
		ui_interface->addHorizontalSlider("pressure", &fslider0, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = (0.0010000000000000009f * float(fslider0));
		float 	fSlow1 = (0.0010000000000000009f * float(fslider1));
		int 	iSlow2 = int(min((float)1, float(fslider2)));
		int 	iSlow3 = int(min((float)1, float(fslider3)));
		int 	iSlow4 = (iSlow3 == 1);
		int 	iSlow5 = ((iSlow2 == 0) & iSlow4);
		int 	iSlow6 = int(min((float)1, float(fslider4)));
		int 	iSlow7 = (iSlow6 == 0);
		int 	iSlow8 = (iSlow2 == 1);
		int 	iSlow9 = (iSlow8 & (iSlow3 == 0));
		int 	iSlow10 = (iSlow8 & iSlow4);
		int 	iSlow11 = (iSlow6 == 1);
		float 	fSlow12 = (0.00077272727272727334f / powf(2.0f,(0.083333333333333329f * (-21.0f - ((((((iSlow5 & iSlow7) + (2 * (iSlow9 & iSlow7))) + (3 * (iSlow10 & iSlow7))) + (4 * (iSlow5 & iSlow11))) + (5 * (iSlow9 & iSlow11))) + (6 * (iSlow10 & iSlow11)))))));
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			iRec6[0] = 0;
			fRec13[0] = (0.5f * (fRec13[1] + fRec11[1]));
			float 	fRec10 = (fRec13[0] + iRec6[1]);
			fRec14[0] = fRec0[1];
			fRec19[0] = (fSlow0 + (0.999f * fRec19[1]));
			iRec21[0] = ((1103515245 * iRec21[1]) + 12345);
			fRec20[0] = ((4.6566128752457969e-10f * iRec21[0]) - (fConst5 * ((fConst6 * fRec20[1]) + (fConst7 * fRec20[2]))));
			fTempPerm0 = (fRec19[0] * ((fConst4 * (fRec20[2] + (fRec20[0] + (2.0f * fRec20[1])))) + 1));
			fRec22[0] = (fSlow1 + (0.999f * fRec22[1]));
			fRec23[0] = (fSlow12 + (0.999f * fRec23[1]));
			fRec18[0] = ((0.029999999999999999f * ((0.29999999999999999f * fTempPerm0) - (0.84999999999999998f * fRec14[1]))) - ((fRec18[1] * (0 - (1.994f * cosf((fConst8 * (powf(4,((2 * fRec22[0]) + -1)) / fRec23[0])))))) + (0.99400900000000003f * fRec18[2])));
			fTempPerm1 = max((float)-1, min((float)1, faustpower<2>(fRec18[0])));
			fTempPerm2 = (0.84999999999999998f * (fRec14[1] * (1 - fTempPerm1)));
			fTempPerm3 = (0.29999999999999999f * (fTempPerm0 * fTempPerm1));
			fVec0[0] = (fTempPerm3 + fTempPerm2);
			fRec17[0] = ((fTempPerm2 + ((0.995f * fRec17[1]) + fTempPerm3)) - fVec0[1]);
			fRec15[IOTA&2047] = fRec17[0];
			int 	iRec16 = 0;
			fTempPerm4 = (fConst10 * fRec23[0]);
			fTempPerm5 = (fTempPerm4 + -1.499995f);
			iTempPerm6 = int(fTempPerm5);
			iTempPerm7 = int((int(min(fConst9, (float)max(0, (int)iTempPerm6))) + 1));
			fTempPerm8 = floorf(fTempPerm5);
			fTempPerm9 = (fTempPerm4 + (-1 - fTempPerm8));
			fTempPerm10 = (0 - fTempPerm9);
			fTempPerm11 = (fTempPerm4 + (-2 - fTempPerm8));
			fTempPerm12 = (0 - (0.5f * fTempPerm11));
			fTempPerm13 = (fTempPerm4 + (-3 - fTempPerm8));
			fTempPerm14 = (0 - (0.33333333333333331f * fTempPerm13));
			fTempPerm15 = (fTempPerm4 + (-4 - fTempPerm8));
			fTempPerm16 = (0 - (0.25f * fTempPerm15));
			fTempPerm17 = (fTempPerm4 - fTempPerm8);
			iTempPerm18 = int((int(min(fConst9, (float)max(0, (int)(iTempPerm6 + 2)))) + 1));
			fTempPerm19 = (0 - fTempPerm13);
			fTempPerm20 = (0 - (0.5f * fTempPerm15));
			iTempPerm21 = int((int(min(fConst9, (float)max(0, (int)(iTempPerm6 + 1)))) + 1));
			fTempPerm22 = (0 - fTempPerm11);
			fTempPerm23 = (0 - (0.5f * fTempPerm13));
			fTempPerm24 = (0 - (0.33333333333333331f * fTempPerm15));
			fTempPerm25 = (fTempPerm9 * fTempPerm11);
			iTempPerm26 = int((int(min(fConst9, (float)max(0, (int)(iTempPerm6 + 3)))) + 1));
			fTempPerm27 = (0 - fTempPerm15);
			fTempPerm28 = (fTempPerm25 * fTempPerm13);
			iTempPerm29 = int((int(min(fConst9, (float)max(0, (int)(iTempPerm6 + 4)))) + 1));
			fVec1[0] = (((((fRec15[(IOTA-iTempPerm7)&2047] * fTempPerm10) * fTempPerm12) * fTempPerm14) * fTempPerm16) + (fTempPerm17 * ((((0.5f * (((fTempPerm9 * fRec15[(IOTA-iTempPerm18)&2047]) * fTempPerm19) * fTempPerm20)) + (((fRec15[(IOTA-iTempPerm21)&2047] * fTempPerm22) * fTempPerm23) * fTempPerm24)) + (0.16666666666666666f * ((fTempPerm25 * fRec15[(IOTA-iTempPerm26)&2047]) * fTempPerm27))) + (0.041666666666666664f * (fTempPerm28 * fRec15[(IOTA-iTempPerm29)&2047])))));
			fRec11[0] = fVec1[1];
			int 	iRec12 = iRec16;
			float 	fRec7 = fRec10;
			float 	fRec8 = fRec11[0];
			float 	fRec9 = (fRec11[0] + iRec12);
			fRec2[IOTA&2047] = fRec7;
			float 	fRec3 = (((((fTempPerm10 * fTempPerm12) * fTempPerm14) * fTempPerm16) * fRec2[(IOTA-iTempPerm7)&2047]) + (fTempPerm17 * (((0.16666666666666666f * ((fTempPerm25 * fTempPerm27) * fRec2[(IOTA-iTempPerm26)&2047])) + ((((fTempPerm22 * fTempPerm23) * fTempPerm24) * fRec2[(IOTA-iTempPerm21)&2047]) + (0.5f * (((fTempPerm9 * fTempPerm19) * fTempPerm20) * fRec2[(IOTA-iTempPerm18)&2047])))) + (0.041666666666666664f * (fTempPerm28 * fRec2[(IOTA-iTempPerm29)&2047])))));
			float 	fRec4 = fRec8;
			float 	fRec5 = fRec9;
			fRec0[0] = fRec3;
			float 	fRec1 = fRec5;
			output0[i] = (FAUSTFLOAT)fRec1;
			output1[i] = (FAUSTFLOAT)fRec1;
			// post processing
			fRec0[1] = fRec0[0];
			fRec11[1] = fRec11[0];
			fVec1[1] = fVec1[0];
			IOTA = IOTA+1;
			fRec17[1] = fRec17[0];
			fVec0[1] = fVec0[0];
			fRec18[2] = fRec18[1]; fRec18[1] = fRec18[0];
			fRec23[1] = fRec23[0];
			fRec22[1] = fRec22[0];
			fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
			iRec21[1] = iRec21[0];
			fRec19[1] = fRec19[0];
			fRec14[1] = fRec14[0];
			fRec13[1] = fRec13[0];
			iRec6[1] = iRec6[0];
		}
	}
};


