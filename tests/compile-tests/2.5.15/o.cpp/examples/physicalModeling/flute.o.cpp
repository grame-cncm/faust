//----------------------------------------------------------
// copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
// license: "MIT"
// name: "Flute"
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
	int 	iRec15[2];
	int 	iVec0[2];
	float 	fRec22[2];
	FAUSTFLOAT 	fslider1;
	float 	fConst0;
	float 	fConst1;
	FAUSTFLOAT 	fslider2;
	float 	fRec23[2];
	float 	fRec24[2];
	FAUSTFLOAT 	fslider3;
	float 	fRec25[2];
	FAUSTFLOAT 	fslider4;
	float 	fConst2;
	FAUSTFLOAT 	fslider5;
	int 	iRec27[2];
	float 	fRec26[3];
	float 	fRec28[2];
	int 	IOTA;
	float 	fRec29[2048];
	float 	fConst3;
	float 	fConst4;
	FAUSTFLOAT 	fslider6;
	float 	fRec31[2];
	float 	fTempPerm0;
	FAUSTFLOAT 	fslider7;
	float 	fRec32[2];
	float 	fTempPerm1;
	float 	fTempPerm2;
	float 	fTempPerm3;
	int 	iTempPerm4;
	int 	iTempPerm5;
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
	int 	iTempPerm16;
	float 	fTempPerm17;
	float 	fTempPerm18;
	int 	iTempPerm19;
	float 	fTempPerm20;
	float 	fTempPerm21;
	float 	fTempPerm22;
	float 	fTempPerm23;
	int 	iTempPerm24;
	float 	fTempPerm25;
	float 	fTempPerm26;
	int 	iTempPerm27;
	float 	fVec1[2];
	float 	fTempPerm28;
	float 	fTempPerm29;
	float 	fVec2[2048];
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
	float 	fVec3[2];
	float 	fRec20[2];
	float 	fRec11[2048];
	float 	fRec7[2];
	float 	fRec3[2048];
	float 	fRec1[2];
	float 	fRec2[2];
	float 	fRec0[2];
	float 	fTempPerm56;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("description", "Simple flute physical model with physical parameters.");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("license", "MIT");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "Flute");
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
		fConst1 = (6.2831853071795862f / fConst0);
		fConst2 = (3.1415926535897931f / fConst0);
		fConst3 = (0.0088235294117647058f * fConst0);
		fConst4 = (0.0014705882352941176f * fConst0);
		fTempPerm0 = 0;
		fTempPerm1 = 0;
		fTempPerm2 = 0;
		fTempPerm3 = 0;
		iTempPerm4 = 0;
		iTempPerm5 = 0;
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
		iTempPerm16 = 0;
		fTempPerm17 = 0;
		fTempPerm18 = 0;
		iTempPerm19 = 0;
		fTempPerm20 = 0;
		fTempPerm21 = 0;
		fTempPerm22 = 0;
		fTempPerm23 = 0;
		iTempPerm24 = 0;
		fTempPerm25 = 0;
		fTempPerm26 = 0;
		iTempPerm27 = 0;
		fTempPerm28 = 0;
		fTempPerm29 = 0;
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
		fTempPerm56 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.5f;
		fslider1 = 0.25f;
		fslider2 = 5.0f;
		fslider3 = 0.0f;
		fslider4 = 0.10000000000000001f;
		fslider5 = 2000.0f;
		fslider6 = 0.80000000000000004f;
		fslider7 = 0.5f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) iRec15[i] = 0;
		for (int i=0; i<2; i++) iVec0[i] = 0;
		for (int i=0; i<2; i++) fRec22[i] = 0;
		for (int i=0; i<2; i++) fRec23[i] = 0;
		for (int i=0; i<2; i++) fRec24[i] = 0;
		for (int i=0; i<2; i++) fRec25[i] = 0;
		for (int i=0; i<2; i++) iRec27[i] = 0;
		for (int i=0; i<3; i++) fRec26[i] = 0;
		for (int i=0; i<2; i++) fRec28[i] = 0;
		IOTA = 0;
		for (int i=0; i<2048; i++) fRec29[i] = 0;
		for (int i=0; i<2; i++) fRec31[i] = 0;
		for (int i=0; i<2; i++) fRec32[i] = 0;
		for (int i=0; i<2; i++) fVec1[i] = 0;
		for (int i=0; i<2048; i++) fVec2[i] = 0;
		for (int i=0; i<2; i++) fVec3[i] = 0;
		for (int i=0; i<2; i++) fRec20[i] = 0;
		for (int i=0; i<2048; i++) fRec11[i] = 0;
		for (int i=0; i<2; i++) fRec7[i] = 0;
		for (int i=0; i<2048; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
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
		ui_interface->openHorizontalBox("flute");
		ui_interface->openVerticalBox("blower");
		ui_interface->declare(&fslider3, "0", "");
		ui_interface->addHorizontalSlider("pressure", &fslider3, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider4, "1", "");
		ui_interface->addHorizontalSlider("breathGain", &fslider4, 0.10000000000000001f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider5, "2", "");
		ui_interface->addHorizontalSlider("breathCutoff", &fslider5, 2000.0f, 20.0f, 20000.0f, 0.10000000000000001f);
		ui_interface->declare(&fslider2, "3", "");
		ui_interface->addHorizontalSlider("vibratoFreq", &fslider2, 5.0f, 0.10000000000000001f, 10.0f, 0.10000000000000001f);
		ui_interface->declare(&fslider1, "4", "");
		ui_interface->addHorizontalSlider("vibratoGain", &fslider1, 0.25f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("fluteModel");
		ui_interface->declare(&fslider6, "0", "");
		ui_interface->addHorizontalSlider("tubeLength", &fslider6, 0.80000000000000004f, 0.01f, 3.0f, 0.01f);
		ui_interface->declare(&fslider7, "1", "");
		ui_interface->addHorizontalSlider("mouthPosition", &fslider7, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider0, "2", "");
		ui_interface->addHorizontalSlider("outGain", &fslider0, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = float(fslider0);
		float 	fSlow1 = (0.029999999999999999f * float(fslider1));
		float 	fSlow2 = (fConst1 * float(fslider2));
		float 	fSlow3 = sinf(fSlow2);
		float 	fSlow4 = cosf(fSlow2);
		float 	fSlow5 = (0 - fSlow3);
		float 	fSlow6 = (0.0010000000000000009f * float(fslider3));
		float 	fSlow7 = tanf((fConst2 * float(fslider5)));
		float 	fSlow8 = (1.0f / fSlow7);
		float 	fSlow9 = (((fSlow8 + 1.4142135623730949f) / fSlow7) + 1);
		float 	fSlow10 = (0.050000000000000003f * (float(fslider4) / fSlow9));
		float 	fSlow11 = (1.0f / fSlow9);
		float 	fSlow12 = (((fSlow8 + -1.4142135623730949f) / fSlow7) + 1);
		float 	fSlow13 = (2 * (1 - (1.0f / faustpower<2>(fSlow7))));
		float 	fSlow14 = (0.0010000000000000009f * float(fslider6));
		float 	fSlow15 = (0.0010000000000000009f * float(fslider7));
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			iRec15[0] = 0;
			iVec0[0] = 1;
			fRec22[0] = ((0.69999999999999996f * fRec22[1]) + (0.28500000000000003f * fRec20[1]));
			float 	fRec19 = (fRec22[0] + iRec15[1]);
			fRec23[0] = ((fSlow3 * fRec24[1]) + (fSlow4 * fRec23[1]));
			fRec24[0] = (((fSlow4 * fRec24[1]) + (fSlow5 * fRec23[1])) + (1 - iVec0[1]));
			fRec25[0] = (fSlow6 + (0.999f * fRec25[1]));
			iRec27[0] = ((1103515245 * iRec27[1]) + 12345);
			fRec26[0] = ((4.6566128752457969e-10f * iRec27[0]) - (fSlow11 * ((fSlow12 * fRec26[2]) + (fSlow13 * fRec26[1]))));
			fRec28[0] = fRec1[1];
			fRec29[IOTA&2047] = (0.94999999999999996f * fRec28[1]);
			int 	iRec30 = 0;
			fRec31[0] = (fSlow14 + (0.999f * fRec31[1]));
			fTempPerm0 = (fRec31[0] + 0.27000000000000002f);
			fRec32[0] = (fSlow15 + (0.999f * fRec32[1]));
			fTempPerm1 = (0.40000000000000002f * (fRec32[0] + -0.5f));
			fTempPerm2 = (fConst4 * (fTempPerm0 * (fTempPerm1 + 0.27000000000000002f)));
			fTempPerm3 = (fTempPerm2 + -1.499995f);
			iTempPerm4 = int(fTempPerm3);
			iTempPerm5 = int((int(min(fConst3, (float)max(0, iTempPerm4))) + 1));
			fTempPerm6 = floorf(fTempPerm3);
			fTempPerm7 = (fTempPerm2 + (-1 - fTempPerm6));
			fTempPerm8 = (0 - fTempPerm7);
			fTempPerm9 = (fTempPerm2 + (-2 - fTempPerm6));
			fTempPerm10 = (0 - (0.5f * fTempPerm9));
			fTempPerm11 = (fTempPerm2 + (-3 - fTempPerm6));
			fTempPerm12 = (0 - (0.33333333333333331f * fTempPerm11));
			fTempPerm13 = (fTempPerm2 + (-4 - fTempPerm6));
			fTempPerm14 = (0 - (0.25f * fTempPerm13));
			fTempPerm15 = (fTempPerm2 - fTempPerm6);
			iTempPerm16 = int((int(min(fConst3, (float)max(0, (iTempPerm4 + 2)))) + 1));
			fTempPerm17 = (0 - fTempPerm11);
			fTempPerm18 = (0 - (0.5f * fTempPerm13));
			iTempPerm19 = int((int(min(fConst3, (float)max(0, (iTempPerm4 + 1)))) + 1));
			fTempPerm20 = (0 - fTempPerm9);
			fTempPerm21 = (0 - (0.5f * fTempPerm11));
			fTempPerm22 = (0 - (0.33333333333333331f * fTempPerm13));
			fTempPerm23 = (fTempPerm7 * fTempPerm9);
			iTempPerm24 = int((int(min(fConst3, (float)max(0, (iTempPerm4 + 3)))) + 1));
			fTempPerm25 = (0 - fTempPerm13);
			fTempPerm26 = (fTempPerm23 * fTempPerm11);
			iTempPerm27 = int((int(min(fConst3, (float)max(0, (iTempPerm4 + 4)))) + 1));
			fVec1[0] = (((((fRec29[(IOTA-iTempPerm5)&2047] * fTempPerm8) * fTempPerm10) * fTempPerm12) * fTempPerm14) + (fTempPerm15 * ((((0.5f * (((fTempPerm7 * fRec29[(IOTA-iTempPerm16)&2047]) * fTempPerm17) * fTempPerm18)) + (((fRec29[(IOTA-iTempPerm19)&2047] * fTempPerm20) * fTempPerm21) * fTempPerm22)) + (0.16666666666666666f * ((fTempPerm23 * fRec29[(IOTA-iTempPerm24)&2047]) * fTempPerm25))) + (0.041666666666666664f * (fTempPerm26 * fRec29[(IOTA-iTempPerm27)&2047])))));
			fTempPerm28 = (((fSlow1 * fRec23[0]) + (fRec25[0] * ((fSlow10 * (fRec26[2] + (fRec26[0] + (2.0f * fRec26[1])))) + 1))) - (0.5f * fVec1[1]));
			fTempPerm29 = ((0.5f * fRec7[1]) + max((float)-1, min((float)1, (fTempPerm28 * (faustpower<2>(fTempPerm28) + -1)))));
			fVec2[IOTA&2047] = fTempPerm29;
			fTempPerm30 = (fConst4 * (fTempPerm0 * (0.72999999999999998f - fTempPerm1)));
			fTempPerm31 = (fTempPerm30 + -1.499995f);
			iTempPerm32 = int(fTempPerm31);
			iTempPerm33 = int((int(min(fConst3, (float)max(0, iTempPerm32))) + 1));
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
			iTempPerm44 = int((int(min(fConst3, (float)max(0, (iTempPerm32 + 2)))) + 1));
			fTempPerm45 = (0 - fTempPerm39);
			fTempPerm46 = (0 - (0.5f * fTempPerm41));
			iTempPerm47 = int((int(min(fConst3, (float)max(0, (iTempPerm32 + 1)))) + 1));
			fTempPerm48 = (0 - fTempPerm37);
			fTempPerm49 = (0 - (0.5f * fTempPerm39));
			fTempPerm50 = (0 - (0.33333333333333331f * fTempPerm41));
			fTempPerm51 = (fTempPerm35 * fTempPerm37);
			iTempPerm52 = int((int(min(fConst3, (float)max(0, (iTempPerm32 + 3)))) + 1));
			fTempPerm53 = (0 - fTempPerm41);
			fTempPerm54 = (fTempPerm51 * fTempPerm39);
			iTempPerm55 = int((int(min(fConst3, (float)max(0, (iTempPerm32 + 4)))) + 1));
			fVec3[0] = (((((fVec2[(IOTA-iTempPerm33)&2047] * fTempPerm36) * fTempPerm38) * fTempPerm40) * fTempPerm42) + (fTempPerm43 * ((((0.5f * (((fTempPerm35 * fVec2[(IOTA-iTempPerm44)&2047]) * fTempPerm45) * fTempPerm46)) + (((fVec2[(IOTA-iTempPerm47)&2047] * fTempPerm48) * fTempPerm49) * fTempPerm50)) + (0.16666666666666666f * ((fTempPerm51 * fVec2[(IOTA-iTempPerm52)&2047]) * fTempPerm53))) + (0.041666666666666664f * (fTempPerm54 * fVec2[(IOTA-iTempPerm55)&2047])))));
			fRec20[0] = fVec3[1];
			int 	iRec21 = iRec30;
			float 	fRec16 = fRec19;
			float 	fRec17 = fRec20[0];
			float 	fRec18 = (fRec20[0] + iRec21);
			fRec11[IOTA&2047] = fRec16;
			float 	fRec12 = (((((fTempPerm36 * fTempPerm38) * fTempPerm40) * fTempPerm42) * fRec11[(IOTA-iTempPerm33)&2047]) + (fTempPerm43 * (((0.16666666666666666f * ((fTempPerm51 * fTempPerm53) * fRec11[(IOTA-iTempPerm52)&2047])) + ((((fTempPerm48 * fTempPerm49) * fTempPerm50) * fRec11[(IOTA-iTempPerm47)&2047]) + (0.5f * (((fTempPerm35 * fTempPerm45) * fTempPerm46) * fRec11[(IOTA-iTempPerm44)&2047])))) + (0.041666666666666664f * (fTempPerm54 * fRec11[(IOTA-iTempPerm55)&2047])))));
			float 	fRec13 = fRec17;
			float 	fRec14 = fRec18;
			fRec7[0] = fRec12;
			float 	fRec8 = fRec7[1];
			float 	fRec9 = fRec13;
			float 	fRec10 = fRec14;
			fRec3[IOTA&2047] = fRec8;
			float 	fRec4 = (((((fTempPerm8 * fTempPerm10) * fTempPerm12) * fTempPerm14) * fRec3[(IOTA-iTempPerm5)&2047]) + (fTempPerm15 * (((0.16666666666666666f * ((fTempPerm23 * fTempPerm25) * fRec3[(IOTA-iTempPerm24)&2047])) + ((((fTempPerm20 * fTempPerm21) * fTempPerm22) * fRec3[(IOTA-iTempPerm19)&2047]) + (0.5f * (((fTempPerm7 * fTempPerm17) * fTempPerm18) * fRec3[(IOTA-iTempPerm16)&2047])))) + (0.041666666666666664f * (fTempPerm26 * fRec3[(IOTA-iTempPerm27)&2047])))));
			float 	fRec5 = fRec9;
			float 	fRec6 = fRec10;
			fRec1[0] = fRec4;
			fRec2[0] = fRec6;
			fRec0[0] = ((fRec2[0] + (0.995f * fRec0[1])) - fRec2[1]);
			fTempPerm56 = (fSlow0 * fRec0[0]);
			output0[i] = (FAUSTFLOAT)fTempPerm56;
			output1[i] = (FAUSTFLOAT)fTempPerm56;
			// post processing
			fRec0[1] = fRec0[0];
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
			fRec7[1] = fRec7[0];
			fRec20[1] = fRec20[0];
			fVec3[1] = fVec3[0];
			fVec1[1] = fVec1[0];
			fRec32[1] = fRec32[0];
			fRec31[1] = fRec31[0];
			IOTA = IOTA+1;
			fRec28[1] = fRec28[0];
			fRec26[2] = fRec26[1]; fRec26[1] = fRec26[0];
			iRec27[1] = iRec27[0];
			fRec25[1] = fRec25[0];
			fRec24[1] = fRec24[0];
			fRec23[1] = fRec23[0];
			fRec22[1] = fRec22[0];
			iVec0[1] = iVec0[0];
			iRec15[1] = iRec15[0];
		}
	}
};


