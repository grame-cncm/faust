//----------------------------------------------------------
// copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
// license: "MIT"
// name: "Violin"
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
	int 	iRec10[2];
	float 	fConst0;
	float 	fConst1;
	float 	fConst2;
	float 	fConst3;
	float 	fConst4;
	float 	fConst5;
	FAUSTFLOAT 	fslider1;
	float 	fRec26[2];
	FAUSTFLOAT 	fslider2;
	float 	fRec27[2];
	float 	fTempPerm0;
	float 	fTempPerm1;
	float 	fTempPerm2;
	int 	iTempPerm3;
	int 	iTempPerm4;
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
	int 	iTempPerm15;
	float 	fTempPerm16;
	float 	fTempPerm17;
	int 	iTempPerm18;
	float 	fTempPerm19;
	float 	fTempPerm20;
	float 	fTempPerm21;
	float 	fTempPerm22;
	int 	iTempPerm23;
	float 	fTempPerm24;
	float 	fTempPerm25;
	int 	iTempPerm26;
	float 	fRec22[2];
	FAUSTFLOAT 	fslider3;
	float 	fRec28[2];
	float 	fRec29[4];
	int 	IOTA;
	float 	fRec30[2048];
	float 	fTempPerm27;
	float 	fTempPerm28;
	int 	iTempPerm29;
	int 	iTempPerm30;
	float 	fTempPerm31;
	float 	fTempPerm32;
	float 	fTempPerm33;
	float 	fTempPerm34;
	float 	fTempPerm35;
	float 	fTempPerm36;
	float 	fTempPerm37;
	float 	fTempPerm38;
	float 	fTempPerm39;
	float 	fTempPerm40;
	int 	iTempPerm41;
	float 	fTempPerm42;
	float 	fTempPerm43;
	int 	iTempPerm44;
	float 	fTempPerm45;
	float 	fTempPerm46;
	float 	fTempPerm47;
	float 	fTempPerm48;
	int 	iTempPerm49;
	float 	fTempPerm50;
	float 	fTempPerm51;
	int 	iTempPerm52;
	float 	fVec0[2];
	float 	fTempPerm53;
	FAUSTFLOAT 	fslider4;
	float 	fRec32[2];
	float 	fTempPerm54;
	float 	fTempPerm55;
	float 	fVec1[2048];
	float 	fRec18[2048];
	float 	fRec20[2];
	float 	fRec16[4];
	float 	fConst6;
	float 	fConst7;
	float 	fRec14[3];
	float 	fConst8;
	float 	fTempPerm56;
	int 	iRec6[2];
	float 	fRec2[2048];
	float 	fRec0[2];
	float 	fTempPerm57;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("description", "Simple violin physical model controlled with continuous parameters.");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("license", "MIT");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "Violin");
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
		fConst1 = tanf((1570.7963267948965f / fConst0));
		fConst2 = (1.0f / fConst1);
		fConst3 = (1.0f / (((fConst2 + 0.5f) / fConst1) + 1));
		fConst4 = (0.0088235294117647058f * fConst0);
		fConst5 = (0.0014705882352941176f * fConst0);
		fTempPerm0 = 0;
		fTempPerm1 = 0;
		fTempPerm2 = 0;
		iTempPerm3 = 0;
		iTempPerm4 = 0;
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
		iTempPerm15 = 0;
		fTempPerm16 = 0;
		fTempPerm17 = 0;
		iTempPerm18 = 0;
		fTempPerm19 = 0;
		fTempPerm20 = 0;
		fTempPerm21 = 0;
		fTempPerm22 = 0;
		iTempPerm23 = 0;
		fTempPerm24 = 0;
		fTempPerm25 = 0;
		iTempPerm26 = 0;
		fTempPerm27 = 0;
		fTempPerm28 = 0;
		iTempPerm29 = 0;
		iTempPerm30 = 0;
		fTempPerm31 = 0;
		fTempPerm32 = 0;
		fTempPerm33 = 0;
		fTempPerm34 = 0;
		fTempPerm35 = 0;
		fTempPerm36 = 0;
		fTempPerm37 = 0;
		fTempPerm38 = 0;
		fTempPerm39 = 0;
		fTempPerm40 = 0;
		iTempPerm41 = 0;
		fTempPerm42 = 0;
		fTempPerm43 = 0;
		iTempPerm44 = 0;
		fTempPerm45 = 0;
		fTempPerm46 = 0;
		fTempPerm47 = 0;
		fTempPerm48 = 0;
		iTempPerm49 = 0;
		fTempPerm50 = 0;
		fTempPerm51 = 0;
		iTempPerm52 = 0;
		fTempPerm53 = 0;
		fTempPerm54 = 0;
		fTempPerm55 = 0;
		fConst6 = (((fConst2 + -0.5f) / fConst1) + 1);
		fConst7 = (2 * (1 - (1.0f / faustpower<2>(fConst1))));
		fConst8 = (0 - fConst2);
		fTempPerm56 = 0;
		fTempPerm57 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.5f;
		fslider1 = 0.69999999999999996f;
		fslider2 = 0.75f;
		fslider3 = 0.0f;
		fslider4 = 0.5f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) iRec10[i] = 0;
		for (int i=0; i<2; i++) fRec26[i] = 0;
		for (int i=0; i<2; i++) fRec27[i] = 0;
		for (int i=0; i<2; i++) fRec22[i] = 0;
		for (int i=0; i<2; i++) fRec28[i] = 0;
		for (int i=0; i<4; i++) fRec29[i] = 0;
		IOTA = 0;
		for (int i=0; i<2048; i++) fRec30[i] = 0;
		for (int i=0; i<2; i++) fVec0[i] = 0;
		for (int i=0; i<2; i++) fRec32[i] = 0;
		for (int i=0; i<2048; i++) fVec1[i] = 0;
		for (int i=0; i<2048; i++) fRec18[i] = 0;
		for (int i=0; i<2; i++) fRec20[i] = 0;
		for (int i=0; i<4; i++) fRec16[i] = 0;
		for (int i=0; i<3; i++) fRec14[i] = 0;
		for (int i=0; i<2; i++) iRec6[i] = 0;
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
		ui_interface->openVerticalBox("violin");
		ui_interface->declare(0, "0", "");
		ui_interface->openVerticalBox("string");
		ui_interface->declare(&fslider2, "0", "");
		ui_interface->addHorizontalSlider("length", &fslider2, 0.75f, 0.0f, 2.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openVerticalBox("bow");
		ui_interface->declare(&fslider3, "0", "");
		ui_interface->addHorizontalSlider("velocity", &fslider3, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider4, "1", "");
		ui_interface->addHorizontalSlider("pressure", &fslider4, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider1, "2", "");
		ui_interface->addHorizontalSlider("position", &fslider1, 0.69999999999999996f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->addHorizontalSlider("outGain", &fslider0, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = float(fslider0);
		float 	fSlow1 = (0.0010000000000000009f * float(fslider1));
		float 	fSlow2 = (0.0010000000000000009f * float(fslider2));
		float 	fSlow3 = (0.0010000000000000009f * float(fslider3));
		float 	fSlow4 = (0.0010000000000000009f * float(fslider4));
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			iRec10[0] = 0;
			int 	iRec11 = iRec10[1];
			float 	fRec15 = (iRec6[1] - (0.98926467176774091f * ((0.59999999999999998f * fRec16[2]) + (0.20000000000000001f * (fRec16[1] + fRec16[3])))));
			fRec26[0] = (fSlow1 + (0.999f * fRec26[1]));
			fRec27[0] = (fSlow2 + (0.999f * fRec27[1]));
			fTempPerm0 = (fRec27[0] + -0.080000000000000002f);
			fTempPerm1 = (fConst5 * ((1 - fRec26[0]) * fTempPerm0));
			fTempPerm2 = (fTempPerm1 + -1.499995f);
			iTempPerm3 = int(fTempPerm2);
			iTempPerm4 = int(min(fConst4, (float)max(0, iTempPerm3)));
			fTempPerm5 = floorf(fTempPerm2);
			fTempPerm6 = (fTempPerm1 + (-1 - fTempPerm5));
			fTempPerm7 = (0 - fTempPerm6);
			fTempPerm8 = (fTempPerm1 + (-2 - fTempPerm5));
			fTempPerm9 = (0 - (0.5f * fTempPerm8));
			fTempPerm10 = (fTempPerm1 + (-3 - fTempPerm5));
			fTempPerm11 = (0 - (0.33333333333333331f * fTempPerm10));
			fTempPerm12 = (fTempPerm1 + (-4 - fTempPerm5));
			fTempPerm13 = (0 - (0.25f * fTempPerm12));
			fTempPerm14 = (fTempPerm1 - fTempPerm5);
			iTempPerm15 = int(min(fConst4, (float)max(0, (iTempPerm3 + 2))));
			fTempPerm16 = (0 - fTempPerm10);
			fTempPerm17 = (0 - (0.5f * fTempPerm12));
			iTempPerm18 = int(min(fConst4, (float)max(0, (iTempPerm3 + 1))));
			fTempPerm19 = (0 - fTempPerm8);
			fTempPerm20 = (0 - (0.5f * fTempPerm10));
			fTempPerm21 = (0 - (0.33333333333333331f * fTempPerm12));
			fTempPerm22 = (fTempPerm6 * fTempPerm8);
			iTempPerm23 = int(min(fConst4, (float)max(0, (iTempPerm3 + 3))));
			fTempPerm24 = (0 - fTempPerm12);
			fTempPerm25 = (fTempPerm22 * fTempPerm10);
			iTempPerm26 = int(min(fConst4, (float)max(0, (iTempPerm3 + 4))));
			fRec22[0] = (((((fRec2[(IOTA-int((iTempPerm4 + 1)))&2047] * fTempPerm7) * fTempPerm9) * fTempPerm11) * fTempPerm13) + (fTempPerm14 * ((((0.5f * (((fTempPerm6 * fRec2[(IOTA-int((iTempPerm15 + 1)))&2047]) * fTempPerm16) * fTempPerm17)) + (((fRec2[(IOTA-int((iTempPerm18 + 1)))&2047] * fTempPerm19) * fTempPerm20) * fTempPerm21)) + (0.16666666666666666f * ((fTempPerm22 * fRec2[(IOTA-int((iTempPerm23 + 1)))&2047]) * fTempPerm24))) + (0.041666666666666664f * (fTempPerm25 * fRec2[(IOTA-int((iTempPerm26 + 1)))&2047])))));
			fRec28[0] = (fSlow3 + (0.999f * fRec28[1]));
			fRec29[0] = fRec0[1];
			fRec30[IOTA&2047] = (0 - (0.99880145575930335f * ((0.80000000000000004f * fRec29[2]) + (0.10000000000000001f * (fRec29[1] + fRec29[3])))));
			int 	iRec31 = 0;
			fTempPerm27 = (fConst5 * (fRec26[0] * fTempPerm0));
			fTempPerm28 = (fTempPerm27 + -1.499995f);
			iTempPerm29 = int(fTempPerm28);
			iTempPerm30 = int(min(fConst4, (float)max(0, iTempPerm29)));
			fTempPerm31 = floorf(fTempPerm28);
			fTempPerm32 = (fTempPerm27 + (-1 - fTempPerm31));
			fTempPerm33 = (0 - fTempPerm32);
			fTempPerm34 = (fTempPerm27 + (-2 - fTempPerm31));
			fTempPerm35 = (0 - (0.5f * fTempPerm34));
			fTempPerm36 = (fTempPerm27 + (-3 - fTempPerm31));
			fTempPerm37 = (0 - (0.33333333333333331f * fTempPerm36));
			fTempPerm38 = (fTempPerm27 + (-4 - fTempPerm31));
			fTempPerm39 = (0 - (0.25f * fTempPerm38));
			fTempPerm40 = (fTempPerm27 - fTempPerm31);
			iTempPerm41 = int(min(fConst4, (float)max(0, (iTempPerm29 + 2))));
			fTempPerm42 = (0 - fTempPerm36);
			fTempPerm43 = (0 - (0.5f * fTempPerm38));
			iTempPerm44 = int(min(fConst4, (float)max(0, (iTempPerm29 + 1))));
			fTempPerm45 = (0 - fTempPerm34);
			fTempPerm46 = (0 - (0.5f * fTempPerm36));
			fTempPerm47 = (0 - (0.33333333333333331f * fTempPerm38));
			fTempPerm48 = (fTempPerm32 * fTempPerm34);
			iTempPerm49 = int(min(fConst4, (float)max(0, (iTempPerm29 + 3))));
			fTempPerm50 = (0 - fTempPerm38);
			fTempPerm51 = (fTempPerm48 * fTempPerm36);
			iTempPerm52 = int(min(fConst4, (float)max(0, (iTempPerm29 + 4))));
			fVec0[0] = (((((fRec30[(IOTA-int((iTempPerm30 + 2)))&2047] * fTempPerm33) * fTempPerm35) * fTempPerm37) * fTempPerm39) + (fTempPerm40 * ((((0.5f * (((fTempPerm32 * fRec30[(IOTA-int((iTempPerm41 + 2)))&2047]) * fTempPerm42) * fTempPerm43)) + (((fRec30[(IOTA-int((iTempPerm44 + 2)))&2047] * fTempPerm45) * fTempPerm46) * fTempPerm47)) + (0.16666666666666666f * ((fTempPerm48 * fRec30[(IOTA-int((iTempPerm49 + 2)))&2047]) * fTempPerm50))) + (0.041666666666666664f * (fTempPerm51 * fRec30[(IOTA-int((iTempPerm52 + 2)))&2047])))));
			fTempPerm53 = (fRec28[0] - (fRec22[1] + fVec0[1]));
			fRec32[0] = (fSlow4 + (0.999f * fRec32[1]));
			fTempPerm54 = (fTempPerm53 * min((float)1, (1.0f / faustpower<4>((fabsf(((5 - (4 * fRec32[0])) * fTempPerm53)) + 0.75f)))));
			float 	fRec23 = (fRec22[1] + fTempPerm54);
			fTempPerm55 = (fVec0[1] + fTempPerm54);
			fVec1[IOTA&2047] = fTempPerm55;
			float 	fRec24 = (((((fTempPerm7 * fTempPerm9) * fTempPerm11) * fTempPerm13) * fVec1[(IOTA-iTempPerm4)&2047]) + (fTempPerm14 * ((0.041666666666666664f * (fTempPerm25 * fVec1[(IOTA-iTempPerm26)&2047])) + (((((fTempPerm19 * fTempPerm20) * fTempPerm21) * fVec1[(IOTA-iTempPerm18)&2047]) + (0.5f * (((fTempPerm6 * fTempPerm16) * fTempPerm17) * fVec1[(IOTA-iTempPerm15)&2047]))) + (0.16666666666666666f * ((fTempPerm22 * fTempPerm24) * fVec1[(IOTA-iTempPerm23)&2047]))))));
			int 	iRec25 = iRec31;
			fRec18[IOTA&2047] = fRec23;
			float 	fRec19 = (((((fTempPerm33 * fTempPerm35) * fTempPerm37) * fTempPerm39) * fRec18[(IOTA-int((iTempPerm30 + 1)))&2047]) + (fTempPerm40 * (((0.16666666666666666f * ((fTempPerm48 * fTempPerm50) * fRec18[(IOTA-int((iTempPerm49 + 1)))&2047])) + ((((fTempPerm45 * fTempPerm46) * fTempPerm47) * fRec18[(IOTA-int((iTempPerm44 + 1)))&2047]) + (0.5f * (((fTempPerm32 * fTempPerm42) * fTempPerm43) * fRec18[(IOTA-int((iTempPerm41 + 1)))&2047])))) + (0.041666666666666664f * (fTempPerm51 * fRec18[(IOTA-int((iTempPerm52 + 1)))&2047])))));
			fRec20[0] = fRec24;
			int 	iRec21 = iRec25;
			fRec16[0] = fRec20[1];
			int 	iRec17 = iRec21;
			fRec14[0] = (fRec16[1] - (fConst3 * ((fConst6 * fRec14[2]) + (fConst7 * fRec14[1]))));
			fTempPerm56 = (fConst3 * ((fConst2 * fRec14[0]) + (fConst8 * fRec14[2])));
			float 	fRec12 = fTempPerm56;
			float 	fRec13 = (iRec17 + fTempPerm56);
			iRec6[0] = iRec11;
			float 	fRec7 = fRec15;
			float 	fRec8 = fRec12;
			float 	fRec9 = fRec13;
			fRec2[IOTA&2047] = fRec7;
			float 	fRec3 = fRec19;
			float 	fRec4 = fRec8;
			float 	fRec5 = fRec9;
			fRec0[0] = fRec3;
			float 	fRec1 = fRec5;
			fTempPerm57 = (fSlow0 * fRec1);
			output0[i] = (FAUSTFLOAT)fTempPerm57;
			output1[i] = (FAUSTFLOAT)fTempPerm57;
			// post processing
			fRec0[1] = fRec0[0];
			iRec6[1] = iRec6[0];
			fRec14[2] = fRec14[1]; fRec14[1] = fRec14[0];
			for (int i=3; i>0; i--) fRec16[i] = fRec16[i-1];
			fRec20[1] = fRec20[0];
			fRec32[1] = fRec32[0];
			fVec0[1] = fVec0[0];
			IOTA = IOTA+1;
			for (int i=3; i>0; i--) fRec29[i] = fRec29[i-1];
			fRec28[1] = fRec28[0];
			fRec22[1] = fRec22[0];
			fRec27[1] = fRec27[0];
			fRec26[1] = fRec26[0];
			iRec10[1] = iRec10[0];
		}
	}
};


