//----------------------------------------------------------
// copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
// license: "MIT"
// name: "Clarinet"
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
	int 	iRec6[2];
	FAUSTFLOAT 	fslider1;
	int 	iVec0[2];
	float 	fRec13[2];
	FAUSTFLOAT 	fslider2;
	float 	fConst0;
	float 	fConst1;
	FAUSTFLOAT 	fslider3;
	float 	fRec17[2];
	float 	fRec18[2];
	float 	fTempPerm0;
	FAUSTFLOAT 	fslider4;
	float 	fRec19[2];
	FAUSTFLOAT 	fslider5;
	float 	fConst2;
	FAUSTFLOAT 	fslider6;
	int 	iRec21[2];
	float 	fRec20[3];
	float 	fTempPerm1;
	float 	fRec14[2];
	float 	fTempPerm2;
	FAUSTFLOAT 	fslider7;
	int 	IOTA;
	float 	fRec15[2048];
	float 	fConst3;
	float 	fConst4;
	FAUSTFLOAT 	fslider8;
	float 	fRec22[2];
	float 	fTempPerm3;
	float 	fTempPerm4;
	int 	iTempPerm5;
	int 	iTempPerm6;
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
	int 	iTempPerm17;
	float 	fTempPerm18;
	float 	fTempPerm19;
	int 	iTempPerm20;
	float 	fTempPerm21;
	float 	fTempPerm22;
	float 	fTempPerm23;
	float 	fTempPerm24;
	int 	iTempPerm25;
	float 	fTempPerm26;
	float 	fTempPerm27;
	int 	iTempPerm28;
	float 	fVec1[2];
	float 	fRec11[2];
	float 	fRec2[2048];
	float 	fRec0[2];
	float 	fTempPerm29;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("description", "Simple clarinet physical model with physical parameters.");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("license", "MIT");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "Clarinet");
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
		fTempPerm0 = 0;
		fConst2 = (3.1415926535897931f / fConst0);
		fTempPerm1 = 0;
		fTempPerm2 = 0;
		fConst3 = (0.0088235294117647058f * fConst0);
		fConst4 = (0.0014705882352941176f * fConst0);
		fTempPerm3 = 0;
		fTempPerm4 = 0;
		iTempPerm5 = 0;
		iTempPerm6 = 0;
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
		iTempPerm17 = 0;
		fTempPerm18 = 0;
		fTempPerm19 = 0;
		iTempPerm20 = 0;
		fTempPerm21 = 0;
		fTempPerm22 = 0;
		fTempPerm23 = 0;
		fTempPerm24 = 0;
		iTempPerm25 = 0;
		fTempPerm26 = 0;
		fTempPerm27 = 0;
		iTempPerm28 = 0;
		fTempPerm29 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.5f;
		fslider1 = 0.5f;
		fslider2 = 0.25f;
		fslider3 = 5.0f;
		fslider4 = 0.0f;
		fslider5 = 0.10000000000000001f;
		fslider6 = 2000.0f;
		fslider7 = 0.5f;
		fslider8 = 0.80000000000000004f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) iRec6[i] = 0;
		for (int i=0; i<2; i++) iVec0[i] = 0;
		for (int i=0; i<2; i++) fRec13[i] = 0;
		for (int i=0; i<2; i++) fRec17[i] = 0;
		for (int i=0; i<2; i++) fRec18[i] = 0;
		for (int i=0; i<2; i++) fRec19[i] = 0;
		for (int i=0; i<2; i++) iRec21[i] = 0;
		for (int i=0; i<3; i++) fRec20[i] = 0;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		IOTA = 0;
		for (int i=0; i<2048; i++) fRec15[i] = 0;
		for (int i=0; i<2; i++) fRec22[i] = 0;
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
		ui_interface->openHorizontalBox("clarinet");
		ui_interface->openVerticalBox("blower");
		ui_interface->declare(&fslider4, "0", "");
		ui_interface->addHorizontalSlider("pressure", &fslider4, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider5, "1", "");
		ui_interface->addHorizontalSlider("breathGain", &fslider5, 0.10000000000000001f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider6, "2", "");
		ui_interface->addHorizontalSlider("breathCutoff", &fslider6, 2000.0f, 20.0f, 20000.0f, 0.10000000000000001f);
		ui_interface->declare(&fslider3, "3", "");
		ui_interface->addHorizontalSlider("vibratoFreq", &fslider3, 5.0f, 0.10000000000000001f, 10.0f, 0.10000000000000001f);
		ui_interface->declare(&fslider2, "4", "");
		ui_interface->addHorizontalSlider("vibratoGain", &fslider2, 0.25f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("clarinetModel");
		ui_interface->declare(&fslider8, "0", "");
		ui_interface->addHorizontalSlider("tubeLength", &fslider8, 0.80000000000000004f, 0.01f, 3.0f, 0.01f);
		ui_interface->declare(&fslider7, "1", "");
		ui_interface->addHorizontalSlider("reedStiffness", &fslider7, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider1, "2", "");
		ui_interface->addHorizontalSlider("bellOpening", &fslider1, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider0, "3", "");
		ui_interface->addHorizontalSlider("outGain", &fslider0, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = float(fslider0);
		float 	fSlow1 = float(fslider1);
		float 	fSlow2 = (1.0f - fSlow1);
		float 	fSlow3 = (0.029999999999999999f * float(fslider2));
		float 	fSlow4 = (fConst1 * float(fslider3));
		float 	fSlow5 = sinf(fSlow4);
		float 	fSlow6 = cosf(fSlow4);
		float 	fSlow7 = (0 - fSlow5);
		float 	fSlow8 = (0.0010000000000000009f * float(fslider4));
		float 	fSlow9 = tanf((fConst2 * float(fslider6)));
		float 	fSlow10 = (1.0f / fSlow9);
		float 	fSlow11 = (((fSlow10 + 1.4142135623730949f) / fSlow9) + 1);
		float 	fSlow12 = (0.050000000000000003f * (float(fslider5) / fSlow11));
		float 	fSlow13 = (1.0f / fSlow11);
		float 	fSlow14 = (((fSlow10 + -1.4142135623730949f) / fSlow9) + 1);
		float 	fSlow15 = (2 * (1 - (1.0f / faustpower<2>(fSlow9))));
		float 	fSlow16 = ((0.26000000000000001f * float(fslider7)) + -0.44f);
		float 	fSlow17 = (0.0010000000000000009f * float(fslider8));
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			iRec6[0] = 0;
			iVec0[0] = 1;
			fRec13[0] = ((fSlow1 * fRec13[1]) + (fSlow2 * fRec11[1]));
			float 	fRec10 = (fRec13[0] + iRec6[1]);
			fRec17[0] = ((fSlow5 * fRec18[1]) + (fSlow6 * fRec17[1]));
			fRec18[0] = (((fSlow6 * fRec18[1]) + (fSlow7 * fRec17[1])) + (1 - iVec0[1]));
			fTempPerm0 = (fSlow3 * fRec17[0]);
			fRec19[0] = (fSlow8 + (0.999f * fRec19[1]));
			iRec21[0] = ((1103515245 * iRec21[1]) + 12345);
			fRec20[0] = ((4.6566128752457969e-10f * iRec21[0]) - (fSlow13 * ((fSlow14 * fRec20[2]) + (fSlow15 * fRec20[1]))));
			fTempPerm1 = (fRec19[0] * ((fSlow12 * (fRec20[2] + (fRec20[0] + (2.0f * fRec20[1])))) + 1));
			fRec14[0] = ((fRec0[1] + fTempPerm0) + fTempPerm1);
			fTempPerm2 = (0 - fRec14[1]);
			fRec15[IOTA&2047] = ((fTempPerm0 + fTempPerm1) + (fTempPerm2 * max((float)-1, min((float)1, ((fSlow16 * fTempPerm2) + 0.69999999999999996f)))));
			int 	iRec16 = 0;
			fRec22[0] = (fSlow17 + (0.999f * fRec22[1]));
			fTempPerm3 = (fConst4 * ((0.5f * fRec22[0]) + -0.050000000000000003f));
			fTempPerm4 = (fTempPerm3 + -1.499995f);
			iTempPerm5 = int(fTempPerm4);
			iTempPerm6 = int((int(min(fConst3, (float)max(0, iTempPerm5))) + 1));
			fTempPerm7 = floorf(fTempPerm4);
			fTempPerm8 = (fTempPerm3 + (-1 - fTempPerm7));
			fTempPerm9 = (0 - fTempPerm8);
			fTempPerm10 = (fTempPerm3 + (-2 - fTempPerm7));
			fTempPerm11 = (0 - (0.5f * fTempPerm10));
			fTempPerm12 = (fTempPerm3 + (-3 - fTempPerm7));
			fTempPerm13 = (0 - (0.33333333333333331f * fTempPerm12));
			fTempPerm14 = (fTempPerm3 + (-4 - fTempPerm7));
			fTempPerm15 = (0 - (0.25f * fTempPerm14));
			fTempPerm16 = (fTempPerm3 - fTempPerm7);
			iTempPerm17 = int((int(min(fConst3, (float)max(0, (iTempPerm5 + 2)))) + 1));
			fTempPerm18 = (0 - fTempPerm12);
			fTempPerm19 = (0 - (0.5f * fTempPerm14));
			iTempPerm20 = int((int(min(fConst3, (float)max(0, (iTempPerm5 + 1)))) + 1));
			fTempPerm21 = (0 - fTempPerm10);
			fTempPerm22 = (0 - (0.5f * fTempPerm12));
			fTempPerm23 = (0 - (0.33333333333333331f * fTempPerm14));
			fTempPerm24 = (fTempPerm8 * fTempPerm10);
			iTempPerm25 = int((int(min(fConst3, (float)max(0, (iTempPerm5 + 3)))) + 1));
			fTempPerm26 = (0 - fTempPerm14);
			fTempPerm27 = (fTempPerm24 * fTempPerm12);
			iTempPerm28 = int((int(min(fConst3, (float)max(0, (iTempPerm5 + 4)))) + 1));
			fVec1[0] = (((((fRec15[(IOTA-iTempPerm6)&2047] * fTempPerm9) * fTempPerm11) * fTempPerm13) * fTempPerm15) + (fTempPerm16 * ((((0.5f * (((fTempPerm8 * fRec15[(IOTA-iTempPerm17)&2047]) * fTempPerm18) * fTempPerm19)) + (((fRec15[(IOTA-iTempPerm20)&2047] * fTempPerm21) * fTempPerm22) * fTempPerm23)) + (0.16666666666666666f * ((fTempPerm24 * fRec15[(IOTA-iTempPerm25)&2047]) * fTempPerm26))) + (0.041666666666666664f * (fTempPerm27 * fRec15[(IOTA-iTempPerm28)&2047])))));
			fRec11[0] = fVec1[1];
			int 	iRec12 = iRec16;
			float 	fRec7 = fRec10;
			float 	fRec8 = fRec11[0];
			float 	fRec9 = (fRec11[0] + iRec12);
			fRec2[IOTA&2047] = fRec7;
			float 	fRec3 = (((((fTempPerm9 * fTempPerm11) * fTempPerm13) * fTempPerm15) * fRec2[(IOTA-iTempPerm6)&2047]) + (fTempPerm16 * (((0.16666666666666666f * ((fTempPerm24 * fTempPerm26) * fRec2[(IOTA-iTempPerm25)&2047])) + ((((fTempPerm21 * fTempPerm22) * fTempPerm23) * fRec2[(IOTA-iTempPerm20)&2047]) + (0.5f * (((fTempPerm8 * fTempPerm18) * fTempPerm19) * fRec2[(IOTA-iTempPerm17)&2047])))) + (0.041666666666666664f * (fTempPerm27 * fRec2[(IOTA-iTempPerm28)&2047])))));
			float 	fRec4 = fRec8;
			float 	fRec5 = fRec9;
			fRec0[0] = fRec3;
			float 	fRec1 = fRec5;
			fTempPerm29 = (fSlow0 * fRec1);
			output0[i] = (FAUSTFLOAT)fTempPerm29;
			output1[i] = (FAUSTFLOAT)fTempPerm29;
			// post processing
			fRec0[1] = fRec0[0];
			fRec11[1] = fRec11[0];
			fVec1[1] = fVec1[0];
			fRec22[1] = fRec22[0];
			IOTA = IOTA+1;
			fRec14[1] = fRec14[0];
			fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
			iRec21[1] = iRec21[0];
			fRec19[1] = fRec19[0];
			fRec18[1] = fRec18[0];
			fRec17[1] = fRec17[0];
			fRec13[1] = fRec13[0];
			iVec0[1] = iVec0[0];
			iRec6[1] = iRec6[0];
		}
	}
};


