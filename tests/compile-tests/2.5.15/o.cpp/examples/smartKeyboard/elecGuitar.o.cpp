//----------------------------------------------------------
// name: "elecGuitar"
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
	FAUSTFLOAT 	fbutton0;
	FAUSTFLOAT 	fslider0;
	float 	fVec0[2];
	int 	iTempPerm0;
	float 	fTempPerm1;
	float 	fRec13[2];
	float 	fConst0;
	float 	fConst1;
	float 	fConst2;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	float 	fRec30[2];
	float 	fTempPerm2;
	float 	fTempPerm3;
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
	float 	fRec26[2];
	float 	fRec31[2];
	float 	fRec33[4];
	int 	IOTA;
	float 	fRec34[2048];
	float 	fConst3;
	float 	fTempPerm30;
	float 	fTempPerm31;
	int 	iTempPerm32;
	int 	iTempPerm33;
	float 	fTempPerm34;
	float 	fTempPerm35;
	float 	fTempPerm36;
	float 	fTempPerm37;
	float 	fTempPerm38;
	float 	fTempPerm39;
	float 	fTempPerm40;
	float 	fTempPerm41;
	float 	fTempPerm42;
	float 	fTempPerm43;
	int 	iTempPerm44;
	float 	fTempPerm45;
	float 	fTempPerm46;
	int 	iTempPerm47;
	float 	fTempPerm48;
	float 	fTempPerm49;
	float 	fTempPerm50;
	float 	fTempPerm51;
	int 	iTempPerm52;
	float 	fTempPerm53;
	float 	fTempPerm54;
	int 	iTempPerm55;
	float 	fVec1[2];
	FAUSTFLOAT 	fslider3;
	int 	iRec37[2];
	float 	fConst4;
	float 	fTempPerm56;
	float 	fTempPerm57;
	float 	fTempPerm58;
	float 	fRec36[3];
	float 	fConst5;
	float 	fTempPerm59;
	float 	fVec2[2];
	float 	fTempPerm60;
	float 	fRec38[2];
	float 	fConst6;
	float 	fTempPerm61;
	int 	iTempPerm62;
	float 	fConst7;
	float 	fTempPerm63;
	float 	fTempPerm64;
	float 	fVec3[3];
	float 	fRec32[512];
	float 	fRec22[2];
	float 	fRec18[2];
	float 	fRec14[2048];
	float 	fRec16[2];
	float 	fRec11[4];
	float 	fRec6[2];
	float 	fRec2[512];
	float 	fRec0[2];
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
		m->declare("interface", "SmartKeyboard{  'Number of Keyboards':'6',  'Max Keyboard Polyphony':'1',  'Keyboard 0 - Number of Keys':'13',  'Keyboard 1 - Number of Keys':'13',  'Keyboard 2 - Number of Keys':'13',  'Keyboard 3 - Number of Keys':'13',  'Keyboard 4 - Number of Keys':'13',  'Keyboard 5 - Number of Keys':'13',  'Keyboard 0 - Lowest Key':'72',  'Keyboard 1 - Lowest Key':'67',  'Keyboard 2 - Lowest Key':'62',  'Keyboard 3 - Lowest Key':'57',  'Keyboard 4 - Lowest Key':'52',  'Keyboard 5 - Lowest Key':'47',  'Rounding Mode':'2' }");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "elecGuitar");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
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
		iTempPerm0 = 0;
		fTempPerm1 = 0;
		fConst0 = min(192000.0f, max(1.0f, (float)fSamplingFreq));
		fConst1 = (0.0088235294117647058f * fConst0);
		fConst2 = (0.00029411764705882345f * fConst0);
		fTempPerm2 = 0;
		fTempPerm3 = 0;
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
		fConst3 = (0.0011764705882352942f * fConst0);
		fTempPerm30 = 0;
		fTempPerm31 = 0;
		iTempPerm32 = 0;
		iTempPerm33 = 0;
		fTempPerm34 = 0;
		fTempPerm35 = 0;
		fTempPerm36 = 0;
		fTempPerm37 = 0;
		fTempPerm38 = 0;
		fTempPerm39 = 0;
		fTempPerm40 = 0;
		fTempPerm41 = 0;
		fTempPerm42 = 0;
		fTempPerm43 = 0;
		iTempPerm44 = 0;
		fTempPerm45 = 0;
		fTempPerm46 = 0;
		iTempPerm47 = 0;
		fTempPerm48 = 0;
		fTempPerm49 = 0;
		fTempPerm50 = 0;
		fTempPerm51 = 0;
		iTempPerm52 = 0;
		fTempPerm53 = 0;
		fTempPerm54 = 0;
		iTempPerm55 = 0;
		fConst4 = (15.707963267948966f / fConst0);
		fTempPerm56 = 0;
		fTempPerm57 = 0;
		fTempPerm58 = 0;
		fConst5 = (0.0040000000000000001f * fConst0);
		fTempPerm59 = 0;
		fTempPerm60 = 0;
		fConst6 = (0.002f * fConst0);
		fTempPerm61 = 0;
		iTempPerm62 = 0;
		fConst7 = (500.0f / fConst0);
		fTempPerm63 = 0;
		fTempPerm64 = 0;
	}
	virtual void instanceResetUserInterface() {
		fbutton0 = 0.0;
		fslider0 = 0.0f;
		fslider1 = 300.0f;
		fslider2 = 1.0f;
		fslider3 = 1.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fVec0[i] = 0;
		for (int i=0; i<2; i++) fRec13[i] = 0;
		for (int i=0; i<2; i++) fRec30[i] = 0;
		for (int i=0; i<2; i++) fRec26[i] = 0;
		for (int i=0; i<2; i++) fRec31[i] = 0;
		for (int i=0; i<4; i++) fRec33[i] = 0;
		IOTA = 0;
		for (int i=0; i<2048; i++) fRec34[i] = 0;
		for (int i=0; i<2; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) iRec37[i] = 0;
		for (int i=0; i<3; i++) fRec36[i] = 0;
		for (int i=0; i<2; i++) fVec2[i] = 0;
		for (int i=0; i<2; i++) fRec38[i] = 0;
		for (int i=0; i<3; i++) fVec3[i] = 0;
		for (int i=0; i<512; i++) fRec32[i] = 0;
		for (int i=0; i<2; i++) fRec22[i] = 0;
		for (int i=0; i<2; i++) fRec18[i] = 0;
		for (int i=0; i<2048; i++) fRec14[i] = 0;
		for (int i=0; i<2; i++) fRec16[i] = 0;
		for (int i=0; i<4; i++) fRec11[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<512; i++) fRec2[i] = 0;
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
		ui_interface->openVerticalBox("elecGuitar");
		ui_interface->declare(&fslider2, "midi", "pitchwheel");
		ui_interface->addHorizontalSlider("bend", &fslider2, 1.0f, 0.0f, 10.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider1, 300.0f, 50.0f, 2000.0f, 0.01f);
		ui_interface->addHorizontalSlider("gain", &fslider3, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addButton("gate", &fbutton0);
		ui_interface->declare(&fslider0, "midi", "ctrl 64");
		ui_interface->addHorizontalSlider("sustain", &fslider0, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = min((float)1, (float(fbutton0) + float(fslider0)));
		int 	iSlow1 = (fSlow0 == 0);
		float 	fSlow2 = float(fslider1);
		float 	fSlow3 = float(fslider2);
		float 	fSlow4 = float(fslider3);
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			float 	fRec10 = (0 - (0.99730529534641577f * ((0.90000000000000002f * fRec11[2]) + (0.049999999999999989f * (fRec11[1] + fRec11[3])))));
			fVec0[0] = fSlow0;
			iTempPerm0 = ((fSlow0 == fVec0[1]) | iSlow1);
			fTempPerm1 = (1.0f - (0.999f * iTempPerm0));
			fRec13[0] = ((fSlow0 * fTempPerm1) + (0.999f * (iTempPerm0 * fRec13[1])));
			fRec30[0] = ((fSlow3 * fTempPerm1) + (0.999f * (iTempPerm0 * fRec30[1])));
			fTempPerm2 = max((float)60, (fSlow2 * fRec30[0]));
			fTempPerm3 = ((float(340) / fTempPerm2) + -0.11f);
			fTempPerm4 = (fConst2 * fTempPerm3);
			fTempPerm5 = (fTempPerm4 + -1.499995f);
			iTempPerm6 = int(fTempPerm5);
			iTempPerm7 = int(min(fConst1, (float)max(0, (int)iTempPerm6)));
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
			iTempPerm18 = int(min(fConst1, (float)max(0, (int)(iTempPerm6 + 2))));
			fTempPerm19 = (0 - fTempPerm13);
			fTempPerm20 = (0 - (0.5f * fTempPerm15));
			iTempPerm21 = int(min(fConst1, (float)max(0, (int)(iTempPerm6 + 1))));
			fTempPerm22 = (0 - fTempPerm11);
			fTempPerm23 = (0 - (0.5f * fTempPerm13));
			fTempPerm24 = (0 - (0.33333333333333331f * fTempPerm15));
			fTempPerm25 = (fTempPerm9 * fTempPerm11);
			iTempPerm26 = int(min(fConst1, (float)max(0, (int)(iTempPerm6 + 3))));
			fTempPerm27 = (0 - fTempPerm15);
			fTempPerm28 = (fTempPerm25 * fTempPerm13);
			iTempPerm29 = int(min(fConst1, (float)max(0, (int)(iTempPerm6 + 4))));
			fRec26[0] = (((((fRec2[(IOTA-int((iTempPerm7 + 1)))&511] * fTempPerm10) * fTempPerm12) * fTempPerm14) * fTempPerm16) + (fTempPerm17 * ((((0.5f * (((fTempPerm9 * fRec2[(IOTA-int((iTempPerm18 + 1)))&511]) * fTempPerm19) * fTempPerm20)) + (((fRec2[(IOTA-int((iTempPerm21 + 1)))&511] * fTempPerm22) * fTempPerm23) * fTempPerm24)) + (0.16666666666666666f * ((fTempPerm25 * fRec2[(IOTA-int((iTempPerm26 + 1)))&511]) * fTempPerm27))) + (0.041666666666666664f * (fTempPerm28 * fRec2[(IOTA-int((iTempPerm29 + 1)))&511])))));
			fRec31[0] = ((0.050000000000000003f * fRec31[1]) + (0.94999999999999996f * fRec26[1]));
			float 	fRec27 = fRec31[0];
			fRec33[0] = fRec0[1];
			fRec34[IOTA&2047] = (0 - (0.99730529534641577f * ((0.90000000000000002f * fRec33[2]) + (0.049999999999999989f * (fRec33[1] + fRec33[3])))));
			int 	iRec35 = 0;
			fTempPerm30 = (fConst3 * fTempPerm3);
			fTempPerm31 = (fTempPerm30 + -1.499995f);
			iTempPerm32 = int(fTempPerm31);
			iTempPerm33 = int(min(fConst1, (float)max(0, (int)iTempPerm32)));
			fTempPerm34 = floorf(fTempPerm31);
			fTempPerm35 = (fTempPerm30 + (-1 - fTempPerm34));
			fTempPerm36 = (0 - fTempPerm35);
			fTempPerm37 = (fTempPerm30 + (-2 - fTempPerm34));
			fTempPerm38 = (0 - (0.5f * fTempPerm37));
			fTempPerm39 = (fTempPerm30 + (-3 - fTempPerm34));
			fTempPerm40 = (0 - (0.33333333333333331f * fTempPerm39));
			fTempPerm41 = (fTempPerm30 + (-4 - fTempPerm34));
			fTempPerm42 = (0 - (0.25f * fTempPerm41));
			fTempPerm43 = (fTempPerm30 - fTempPerm34);
			iTempPerm44 = int(min(fConst1, (float)max(0, (int)(iTempPerm32 + 2))));
			fTempPerm45 = (0 - fTempPerm39);
			fTempPerm46 = (0 - (0.5f * fTempPerm41));
			iTempPerm47 = int(min(fConst1, (float)max(0, (int)(iTempPerm32 + 1))));
			fTempPerm48 = (0 - fTempPerm37);
			fTempPerm49 = (0 - (0.5f * fTempPerm39));
			fTempPerm50 = (0 - (0.33333333333333331f * fTempPerm41));
			fTempPerm51 = (fTempPerm35 * fTempPerm37);
			iTempPerm52 = int(min(fConst1, (float)max(0, (int)(iTempPerm32 + 3))));
			fTempPerm53 = (0 - fTempPerm41);
			fTempPerm54 = (fTempPerm51 * fTempPerm39);
			iTempPerm55 = int(min(fConst1, (float)max(0, (int)(iTempPerm32 + 4))));
			fVec1[0] = (((((fRec34[(IOTA-int((iTempPerm33 + 2)))&2047] * fTempPerm36) * fTempPerm38) * fTempPerm40) * fTempPerm42) + (fTempPerm43 * ((((0.5f * (((fTempPerm35 * fRec34[(IOTA-int((iTempPerm44 + 2)))&2047]) * fTempPerm45) * fTempPerm46)) + (((fRec34[(IOTA-int((iTempPerm47 + 2)))&2047] * fTempPerm48) * fTempPerm49) * fTempPerm50)) + (0.16666666666666666f * ((fTempPerm51 * fRec34[(IOTA-int((iTempPerm52 + 2)))&2047]) * fTempPerm53))) + (0.041666666666666664f * (fTempPerm54 * fRec34[(IOTA-int((iTempPerm55 + 2)))&2047])))));
			iRec37[0] = ((1103515245 * iRec37[1]) + 12345);
			fTempPerm56 = tanf((fConst4 * fTempPerm2));
			fTempPerm57 = (1.0f / fTempPerm56);
			fTempPerm58 = (((fTempPerm57 + 1.4142135623730949f) / fTempPerm56) + 1);
			fRec36[0] = ((4.6566128752457969e-10f * iRec37[0]) - (((fRec36[2] * (((fTempPerm57 + -1.4142135623730949f) / fTempPerm56) + 1)) + (2 * (fRec36[1] * (1 - (1.0f / faustpower<2>(fTempPerm56)))))) / fTempPerm58));
			fTempPerm59 = faustpower<2>((1 - (0.00050000000000000001f * fTempPerm2)));
			fVec2[0] = fTempPerm59;
			fTempPerm60 = (fConst5 * fVec2[0]);
			fRec38[0] = ((int((((fSlow0 - fVec0[1]) > 0) > 0)))?0:min(fTempPerm60, ((fRec38[1] + (fConst5 * (fVec2[0] - fVec2[1]))) + 1)));
			fTempPerm61 = (fConst6 * fVec2[0]);
			iTempPerm62 = int((fRec38[0] < fTempPerm61));
			fTempPerm63 = (fSlow4 * (((fRec36[2] + (fRec36[0] + (2.0f * fRec36[1]))) * ((iTempPerm62)?((int((fRec38[0] < 0)))?0:((iTempPerm62)?(fConst7 * (fRec38[0] / fVec2[0])):1)):((int((fRec38[0] < fTempPerm60)))?((fConst7 * ((0 - (fRec38[0] - fTempPerm61)) / fVec2[0])) + 1):0))) / fTempPerm58));
			fTempPerm64 = (fVec1[1] + fTempPerm63);
			fVec3[0] = fTempPerm64;
			fRec32[IOTA&511] = ((0.050000000000000003f * fRec32[(IOTA-1)&511]) + (0.94999999999999996f * fVec3[2]));
			float 	fRec28 = (((((fTempPerm10 * fTempPerm12) * fTempPerm14) * fTempPerm16) * fRec32[(IOTA-iTempPerm7)&511]) + (fTempPerm17 * ((0.041666666666666664f * (fTempPerm28 * fRec32[(IOTA-iTempPerm29)&511])) + (((((fTempPerm22 * fTempPerm23) * fTempPerm24) * fRec32[(IOTA-iTempPerm21)&511]) + (0.5f * (((fTempPerm9 * fTempPerm19) * fTempPerm20) * fRec32[(IOTA-iTempPerm18)&511]))) + (0.16666666666666666f * ((fTempPerm25 * fTempPerm27) * fRec32[(IOTA-iTempPerm26)&511]))))));
			float 	fRec29 = (fRec22[1] + (iRec35 + fVec3[1]));
			fRec22[0] = fRec27;
			float 	fRec23 = fRec22[1];
			float 	fRec24 = fRec28;
			float 	fRec25 = fRec29;
			fRec18[0] = fRec23;
			float 	fRec19 = (fTempPerm63 + fRec18[1]);
			float 	fRec20 = fRec24;
			float 	fRec21 = fRec25;
			fRec14[IOTA&2047] = fRec19;
			float 	fRec15 = (((((fTempPerm36 * fTempPerm38) * fTempPerm40) * fTempPerm42) * fRec14[(IOTA-int((iTempPerm33 + 1)))&2047]) + (fTempPerm43 * (((0.16666666666666666f * ((fTempPerm51 * fTempPerm53) * fRec14[(IOTA-int((iTempPerm52 + 1)))&2047])) + ((((fTempPerm48 * fTempPerm49) * fTempPerm50) * fRec14[(IOTA-int((iTempPerm47 + 1)))&2047]) + (0.5f * (((fTempPerm35 * fTempPerm45) * fTempPerm46) * fRec14[(IOTA-int((iTempPerm44 + 1)))&2047])))) + (0.041666666666666664f * (fTempPerm54 * fRec14[(IOTA-int((iTempPerm55 + 1)))&2047])))));
			fRec16[0] = fRec20;
			float 	fRec17 = fRec21;
			fRec11[0] = (fRec13[0] * fRec16[1]);
			float 	fRec12 = fRec17;
			fRec6[0] = fRec10;
			float 	fRec7 = (fRec13[0] * fRec6[1]);
			float 	fRec8 = fRec11[0];
			float 	fRec9 = fRec12;
			fRec2[IOTA&511] = fRec7;
			float 	fRec3 = fRec15;
			float 	fRec4 = fRec8;
			float 	fRec5 = fRec9;
			fRec0[0] = fRec3;
			float 	fRec1 = fRec5;
			output0[i] = (FAUSTFLOAT)fRec1;
			output1[i] = (FAUSTFLOAT)fRec1;
			// post processing
			fRec0[1] = fRec0[0];
			fRec6[1] = fRec6[0];
			for (int i=3; i>0; i--) fRec11[i] = fRec11[i-1];
			fRec16[1] = fRec16[0];
			fRec18[1] = fRec18[0];
			fRec22[1] = fRec22[0];
			fVec3[2] = fVec3[1]; fVec3[1] = fVec3[0];
			fRec38[1] = fRec38[0];
			fVec2[1] = fVec2[0];
			fRec36[2] = fRec36[1]; fRec36[1] = fRec36[0];
			iRec37[1] = iRec37[0];
			fVec1[1] = fVec1[0];
			IOTA = IOTA+1;
			for (int i=3; i>0; i--) fRec33[i] = fRec33[i-1];
			fRec31[1] = fRec31[0];
			fRec26[1] = fRec26[0];
			fRec30[1] = fRec30[0];
			fRec13[1] = fRec13[0];
			fVec0[1] = fVec0[0];
		}
	}
};


