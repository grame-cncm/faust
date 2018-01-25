//----------------------------------------------------------
// copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
// license: "MIT"
// name: "ClarinetMIDI"
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
	FAUSTFLOAT 	fbutton0;
	FAUSTFLOAT 	fslider4;
	float 	fVec1[2];
	FAUSTFLOAT 	fslider5;
	float 	fConst2;
	FAUSTFLOAT 	fslider6;
	float 	fRec19[2];
	float 	fConst3;
	float 	fConst4;
	float 	fConst5;
	float 	fConst6;
	int 	iRec21[2];
	float 	fConst7;
	float 	fConst8;
	float 	fConst9;
	float 	fRec20[3];
	float 	fTempPerm1;
	float 	fRec14[2];
	float 	fTempPerm2;
	FAUSTFLOAT 	fslider7;
	int 	IOTA;
	float 	fRec15[2048];
	float 	fConst10;
	float 	fConst11;
	FAUSTFLOAT 	fslider8;
	FAUSTFLOAT 	fslider9;
	int 	iTempPerm3;
	float 	fRec22[2];
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
	float 	fVec2[2];
	float 	fRec11[2];
	float 	fRec2[2048];
	float 	fRec0[2];
	float 	fTempPerm30;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("description", "Simple MIDI-controllable clarinet physical model with physical parameters.");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("license", "MIT");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "ClarinetMIDI");
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
		fConst2 = (1000.0f / fConst0);
		fConst3 = tanf((6283.1853071795858f / fConst0));
		fConst4 = (1.0f / fConst3);
		fConst5 = (((fConst4 + 1.4142135623730949f) / fConst3) + 1);
		fConst6 = (0.050000000000000003f / fConst5);
		fConst7 = (1.0f / fConst5);
		fConst8 = (2 * (1 - (1.0f / faustpower<2>(fConst3))));
		fConst9 = (((fConst4 + -1.4142135623730949f) / fConst3) + 1);
		fTempPerm1 = 0;
		fTempPerm2 = 0;
		fConst10 = (0.0088235294117647058f * fConst0);
		fConst11 = (0.0014705882352941176f * fConst0);
		iTempPerm3 = 0;
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
		fTempPerm30 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.5f;
		fslider1 = 0.5f;
		fslider2 = 0.25f;
		fslider3 = 5.0f;
		fbutton0 = 0.0;
		fslider4 = 0.0f;
		fslider5 = 0.59999999999999998f;
		fslider6 = 1.0f;
		fslider7 = 0.5f;
		fslider8 = 440.0f;
		fslider9 = 1.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) iRec6[i] = 0;
		for (int i=0; i<2; i++) iVec0[i] = 0;
		for (int i=0; i<2; i++) fRec13[i] = 0;
		for (int i=0; i<2; i++) fRec17[i] = 0;
		for (int i=0; i<2; i++) fRec18[i] = 0;
		for (int i=0; i<2; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fRec19[i] = 0;
		for (int i=0; i<2; i++) iRec21[i] = 0;
		for (int i=0; i<3; i++) fRec20[i] = 0;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		IOTA = 0;
		for (int i=0; i<2048; i++) fRec15[i] = 0;
		for (int i=0; i<2; i++) fRec22[i] = 0;
		for (int i=0; i<2; i++) fVec2[i] = 0;
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
		ui_interface->openVerticalBox("clarinet");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("midi");
		ui_interface->declare(&fslider8, "0", "");
		ui_interface->declare(&fslider8, "style", "knob");
		ui_interface->addHorizontalSlider("freq", &fslider8, 440.0f, 50.0f, 1000.0f, 0.01f);
		ui_interface->declare(&fslider9, "1", "");
		ui_interface->declare(&fslider9, "hidden", "1");
		ui_interface->declare(&fslider9, "midi", "pitchwheel");
		ui_interface->declare(&fslider9, "style", "knob");
		ui_interface->addHorizontalSlider("bend", &fslider9, 1.0f, 0.0f, 10.0f, 0.01f);
		ui_interface->declare(&fslider5, "2", "");
		ui_interface->declare(&fslider5, "style", "knob");
		ui_interface->addHorizontalSlider("gain", &fslider5, 0.59999999999999998f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider6, "3", "");
		ui_interface->declare(&fslider6, "style", "knob");
		ui_interface->addHorizontalSlider("envAttack", &fslider6, 1.0f, 0.0f, 30.0f, 0.01f);
		ui_interface->declare(&fslider4, "4", "");
		ui_interface->declare(&fslider4, "hidden", "1");
		ui_interface->declare(&fslider4, "midi", "ctrl 64");
		ui_interface->declare(&fslider4, "style", "knob");
		ui_interface->addHorizontalSlider("sustain", &fslider4, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("otherParams");
		ui_interface->declare(&fslider7, "0", "");
		ui_interface->declare(&fslider7, "midi", "ctrl 1");
		ui_interface->declare(&fslider7, "style", "knob");
		ui_interface->addHorizontalSlider("reedStiffness", &fslider7, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider1, "1", "");
		ui_interface->declare(&fslider1, "midi", "ctrl 3");
		ui_interface->declare(&fslider1, "style", "knob");
		ui_interface->addHorizontalSlider("bellOpening", &fslider1, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider3, "2", "");
		ui_interface->declare(&fslider3, "style", "knob");
		ui_interface->addHorizontalSlider("vibratoFreq", &fslider3, 5.0f, 1.0f, 10.0f, 0.01f);
		ui_interface->declare(&fslider2, "3", "");
		ui_interface->declare(&fslider2, "style", "knob");
		ui_interface->addHorizontalSlider("vibratoGain", &fslider2, 0.25f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider0, "4", "");
		ui_interface->declare(&fslider0, "style", "knob");
		ui_interface->addHorizontalSlider("outGain", &fslider0, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->declare(&fbutton0, "2", "");
		ui_interface->addButton("gate", &fbutton0);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = float(fslider0);
		float 	fSlow1 = float(fslider1);
		float 	fSlow2 = (1.0f - fSlow1);
		float 	fSlow3 = (0.01f * float(fslider2));
		float 	fSlow4 = (fConst1 * float(fslider3));
		float 	fSlow5 = sinf(fSlow4);
		float 	fSlow6 = cosf(fSlow4);
		float 	fSlow7 = (0 - fSlow5);
		float 	fSlow8 = min((float)1, (float(fbutton0) + float(fslider4)));
		float 	fSlow9 = expf((0 - (fConst2 / float(fslider6))));
		float 	fSlow10 = ((fSlow8 * float(fslider5)) * (1.0f - fSlow9));
		float 	fSlow11 = ((0.26000000000000001f * float(fslider7)) + -0.44f);
		float 	fSlow12 = (float(170) / float(fslider8));
		float 	fSlow13 = float(fslider9);
		int 	iSlow14 = (fSlow8 == 0);
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
			fVec1[0] = fSlow8;
			fRec19[0] = (fSlow10 + (fSlow9 * fRec19[1]));
			iRec21[0] = ((1103515245 * iRec21[1]) + 12345);
			fRec20[0] = ((4.6566128752457969e-10f * iRec21[0]) - (fConst7 * ((fConst8 * fRec20[1]) + (fConst9 * fRec20[2]))));
			fTempPerm1 = (fRec19[0] * ((fConst6 * (fRec20[2] + (fRec20[0] + (2.0f * fRec20[1])))) + 1));
			fRec14[0] = ((fRec0[1] + fTempPerm0) + fTempPerm1);
			fTempPerm2 = (0 - fRec14[1]);
			fRec15[IOTA&2047] = ((fTempPerm0 + fTempPerm1) + (fTempPerm2 * max((float)-1, min((float)1, ((fSlow11 * fTempPerm2) + 0.69999999999999996f)))));
			int 	iRec16 = 0;
			iTempPerm3 = ((fSlow8 == fVec1[1]) | iSlow14);
			fRec22[0] = ((fSlow13 * (1.0f - (0.999f * iTempPerm3))) + (0.999f * (iTempPerm3 * fRec22[1])));
			fTempPerm4 = (fConst11 * ((fSlow12 / (fRec22[0] * ((fSlow3 * (fRec19[0] * fRec17[0])) + 1))) + -0.050000000000000003f));
			fTempPerm5 = (fTempPerm4 + -1.499995f);
			iTempPerm6 = int(fTempPerm5);
			iTempPerm7 = int((int(min(fConst10, (float)max(0, (int)iTempPerm6))) + 1));
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
			iTempPerm18 = int((int(min(fConst10, (float)max(0, (int)(iTempPerm6 + 2)))) + 1));
			fTempPerm19 = (0 - fTempPerm13);
			fTempPerm20 = (0 - (0.5f * fTempPerm15));
			iTempPerm21 = int((int(min(fConst10, (float)max(0, (int)(iTempPerm6 + 1)))) + 1));
			fTempPerm22 = (0 - fTempPerm11);
			fTempPerm23 = (0 - (0.5f * fTempPerm13));
			fTempPerm24 = (0 - (0.33333333333333331f * fTempPerm15));
			fTempPerm25 = (fTempPerm9 * fTempPerm11);
			iTempPerm26 = int((int(min(fConst10, (float)max(0, (int)(iTempPerm6 + 3)))) + 1));
			fTempPerm27 = (0 - fTempPerm15);
			fTempPerm28 = (fTempPerm25 * fTempPerm13);
			iTempPerm29 = int((int(min(fConst10, (float)max(0, (int)(iTempPerm6 + 4)))) + 1));
			fVec2[0] = (((((fRec15[(IOTA-iTempPerm7)&2047] * fTempPerm10) * fTempPerm12) * fTempPerm14) * fTempPerm16) + (fTempPerm17 * ((((0.5f * (((fTempPerm9 * fRec15[(IOTA-iTempPerm18)&2047]) * fTempPerm19) * fTempPerm20)) + (((fRec15[(IOTA-iTempPerm21)&2047] * fTempPerm22) * fTempPerm23) * fTempPerm24)) + (0.16666666666666666f * ((fTempPerm25 * fRec15[(IOTA-iTempPerm26)&2047]) * fTempPerm27))) + (0.041666666666666664f * (fTempPerm28 * fRec15[(IOTA-iTempPerm29)&2047])))));
			fRec11[0] = fVec2[1];
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
			fTempPerm30 = (fSlow0 * fRec1);
			output0[i] = (FAUSTFLOAT)fTempPerm30;
			output1[i] = (FAUSTFLOAT)fTempPerm30;
			// post processing
			fRec0[1] = fRec0[0];
			fRec11[1] = fRec11[0];
			fVec2[1] = fVec2[0];
			fRec22[1] = fRec22[0];
			IOTA = IOTA+1;
			fRec14[1] = fRec14[0];
			fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
			iRec21[1] = iRec21[0];
			fRec19[1] = fRec19[0];
			fVec1[1] = fVec1[0];
			fRec18[1] = fRec18[0];
			fRec17[1] = fRec17[0];
			fRec13[1] = fRec13[0];
			iVec0[1] = iVec0[0];
			iRec6[1] = iRec6[0];
		}
	}
};


