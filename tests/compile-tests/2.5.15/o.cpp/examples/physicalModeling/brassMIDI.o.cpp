//----------------------------------------------------------
// copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
// license: "MIT"
// name: "BrassMIDI"
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
	float 	fRec14[2];
	float 	fRec13[2];
	float 	fRec15[2];
	FAUSTFLOAT 	fbutton0;
	FAUSTFLOAT 	fslider2;
	float 	fVec1[2];
	FAUSTFLOAT 	fslider3;
	float 	fConst0;
	float 	fConst1;
	FAUSTFLOAT 	fslider4;
	float 	fRec20[2];
	FAUSTFLOAT 	fslider5;
	float 	fConst2;
	FAUSTFLOAT 	fslider6;
	float 	fRec21[2];
	float 	fRec22[2];
	float 	fTempPerm0;
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT 	fslider8;
	int 	iTempPerm1;
	float 	fRec23[2];
	FAUSTFLOAT 	fslider9;
	float 	fRec24[2];
	float 	fRec19[3];
	float 	fTempPerm2;
	float 	fTempPerm3;
	float 	fTempPerm4;
	float 	fVec2[2];
	float 	fRec18[2];
	int 	IOTA;
	float 	fRec16[2048];
	float 	fConst3;
	float 	fConst4;
	float 	fTempPerm5;
	float 	fTempPerm6;
	int 	iTempPerm7;
	int 	iTempPerm8;
	float 	fTempPerm9;
	float 	fTempPerm10;
	float 	fTempPerm11;
	float 	fTempPerm12;
	float 	fTempPerm13;
	float 	fTempPerm14;
	float 	fTempPerm15;
	float 	fTempPerm16;
	float 	fTempPerm17;
	float 	fTempPerm18;
	int 	iTempPerm19;
	float 	fTempPerm20;
	float 	fTempPerm21;
	int 	iTempPerm22;
	float 	fTempPerm23;
	float 	fTempPerm24;
	float 	fTempPerm25;
	float 	fTempPerm26;
	int 	iTempPerm27;
	float 	fTempPerm28;
	float 	fTempPerm29;
	int 	iTempPerm30;
	float 	fVec3[2];
	float 	fRec11[2];
	float 	fRec2[2048];
	float 	fRec0[2];
	float 	fTempPerm31;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("description", "Simple MIDI-controllable brass instrument physical model with physical parameters.");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("license", "MIT");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "BrassMIDI");
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
		fConst1 = (1000.0f / fConst0);
		fConst2 = (6.2831853071795862f / fConst0);
		fTempPerm0 = 0;
		iTempPerm1 = 0;
		fTempPerm2 = 0;
		fTempPerm3 = 0;
		fTempPerm4 = 0;
		fConst3 = (0.0088235294117647058f * fConst0);
		fConst4 = (0.5f * fConst0);
		fTempPerm5 = 0;
		fTempPerm6 = 0;
		iTempPerm7 = 0;
		iTempPerm8 = 0;
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
		iTempPerm19 = 0;
		fTempPerm20 = 0;
		fTempPerm21 = 0;
		iTempPerm22 = 0;
		fTempPerm23 = 0;
		fTempPerm24 = 0;
		fTempPerm25 = 0;
		fTempPerm26 = 0;
		iTempPerm27 = 0;
		fTempPerm28 = 0;
		fTempPerm29 = 0;
		iTempPerm30 = 0;
		fTempPerm31 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.5f;
		fslider1 = 0.5f;
		fbutton0 = 0.0;
		fslider2 = 0.0f;
		fslider3 = 0.5f;
		fslider4 = 1.0f;
		fslider5 = 0.5f;
		fslider6 = 5.0f;
		fslider7 = 440.0f;
		fslider8 = 1.0f;
		fslider9 = 0.5f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) iRec6[i] = 0;
		for (int i=0; i<2; i++) iVec0[i] = 0;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		for (int i=0; i<2; i++) fRec13[i] = 0;
		for (int i=0; i<2; i++) fRec15[i] = 0;
		for (int i=0; i<2; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fRec20[i] = 0;
		for (int i=0; i<2; i++) fRec21[i] = 0;
		for (int i=0; i<2; i++) fRec22[i] = 0;
		for (int i=0; i<2; i++) fRec23[i] = 0;
		for (int i=0; i<2; i++) fRec24[i] = 0;
		for (int i=0; i<3; i++) fRec19[i] = 0;
		for (int i=0; i<2; i++) fVec2[i] = 0;
		for (int i=0; i<2; i++) fRec18[i] = 0;
		IOTA = 0;
		for (int i=0; i<2048; i++) fRec16[i] = 0;
		for (int i=0; i<2; i++) fVec3[i] = 0;
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
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("midi");
		ui_interface->declare(&fslider7, "0", "");
		ui_interface->declare(&fslider7, "style", "knob");
		ui_interface->addHorizontalSlider("freq", &fslider7, 440.0f, 50.0f, 1000.0f, 0.01f);
		ui_interface->declare(&fslider8, "1", "");
		ui_interface->declare(&fslider8, "hidden", "1");
		ui_interface->declare(&fslider8, "midi", "pitchwheel");
		ui_interface->declare(&fslider8, "style", "knob");
		ui_interface->addHorizontalSlider("bend", &fslider8, 1.0f, 0.0f, 10.0f, 0.01f);
		ui_interface->declare(&fslider3, "2", "");
		ui_interface->declare(&fslider3, "style", "knob");
		ui_interface->addHorizontalSlider("gain", &fslider3, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider4, "3", "");
		ui_interface->declare(&fslider4, "style", "knob");
		ui_interface->addHorizontalSlider("envAttack", &fslider4, 1.0f, 0.0f, 30.0f, 0.01f);
		ui_interface->declare(&fslider2, "4", "");
		ui_interface->declare(&fslider2, "hidden", "1");
		ui_interface->declare(&fslider2, "midi", "ctrl 64");
		ui_interface->declare(&fslider2, "style", "knob");
		ui_interface->addHorizontalSlider("sustain", &fslider2, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("otherParams");
		ui_interface->declare(&fslider9, "0", "");
		ui_interface->declare(&fslider9, "midi", "ctrl 1");
		ui_interface->declare(&fslider9, "style", "knob");
		ui_interface->addHorizontalSlider("lipsTension", &fslider9, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider1, "1", "");
		ui_interface->declare(&fslider1, "style", "knob");
		ui_interface->addHorizontalSlider("mute", &fslider1, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider6, "2", "");
		ui_interface->declare(&fslider6, "style", "knob");
		ui_interface->addHorizontalSlider("vibratoFreq", &fslider6, 5.0f, 1.0f, 10.0f, 0.01f);
		ui_interface->declare(&fslider5, "3", "");
		ui_interface->declare(&fslider5, "style", "knob");
		ui_interface->addHorizontalSlider("vibratoGain", &fslider5, 0.5f, 0.0f, 1.0f, 0.01f);
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
		float 	fSlow1 = (0.0010000000000000009f * float(fslider1));
		float 	fSlow2 = min((float)1, (float(fbutton0) + float(fslider2)));
		float 	fSlow3 = expf((0 - (fConst1 / float(fslider4))));
		float 	fSlow4 = ((fSlow2 * float(fslider3)) * (1.0f - fSlow3));
		float 	fSlow5 = (0.040000000000000001f * float(fslider5));
		float 	fSlow6 = (fConst2 * float(fslider6));
		float 	fSlow7 = sinf(fSlow6);
		float 	fSlow8 = cosf(fSlow6);
		float 	fSlow9 = (0 - fSlow7);
		float 	fSlow10 = float(fslider7);
		float 	fSlow11 = (fConst2 * fSlow10);
		float 	fSlow12 = float(fslider8);
		int 	iSlow13 = (fSlow2 == 0);
		float 	fSlow14 = (0.0010000000000000009f * float(fslider9));
		float 	fSlow15 = (fConst4 / fSlow10);
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			iRec6[0] = 0;
			iVec0[0] = 1;
			fRec14[0] = (fSlow1 + (0.999f * fRec14[1]));
			fRec13[0] = ((fRec14[0] * fRec13[1]) + ((1.0f - fRec14[0]) * fRec11[1]));
			float 	fRec10 = (fRec13[0] + iRec6[1]);
			fRec15[0] = fRec0[1];
			fVec1[0] = fSlow2;
			fRec20[0] = (fSlow4 + (fSlow3 * fRec20[1]));
			fRec21[0] = ((fSlow7 * fRec22[1]) + (fSlow8 * fRec21[1]));
			fRec22[0] = (((fSlow8 * fRec22[1]) + (fSlow9 * fRec21[1])) + (1 - iVec0[1]));
			fTempPerm0 = (fRec20[0] * ((fSlow5 * (fRec20[0] * fRec21[0])) + 1));
			iTempPerm1 = ((fSlow2 == fVec1[1]) | iSlow13);
			fRec23[0] = ((fSlow12 * (1.0f - (0.999f * iTempPerm1))) + (0.999f * (iTempPerm1 * fRec23[1])));
			fRec24[0] = (fSlow14 + (0.999f * fRec24[1]));
			fRec19[0] = ((0.029999999999999999f * ((0.29999999999999999f * fTempPerm0) - (0.84999999999999998f * fRec15[1]))) - ((fRec19[1] * (0 - (1.994f * cosf((fSlow11 * (fRec23[0] * powf(4,((2 * fRec24[0]) + -1)))))))) + (0.99400900000000003f * fRec19[2])));
			fTempPerm2 = max((float)-1, min((float)1, faustpower<2>(fRec19[0])));
			fTempPerm3 = (0.84999999999999998f * (fRec15[1] * (1 - fTempPerm2)));
			fTempPerm4 = (0.29999999999999999f * (fTempPerm0 * fTempPerm2));
			fVec2[0] = (fTempPerm4 + fTempPerm3);
			fRec18[0] = ((fTempPerm3 + ((0.995f * fRec18[1]) + fTempPerm4)) - fVec2[1]);
			fRec16[IOTA&2047] = fRec18[0];
			int 	iRec17 = 0;
			fTempPerm5 = (fSlow15 / fRec23[0]);
			fTempPerm6 = (fTempPerm5 + -1.499995f);
			iTempPerm7 = int(fTempPerm6);
			iTempPerm8 = int((int(min(fConst3, (float)max(0, (int)iTempPerm7))) + 1));
			fTempPerm9 = floorf(fTempPerm6);
			fTempPerm10 = (fTempPerm5 + (-1 - fTempPerm9));
			fTempPerm11 = (0 - fTempPerm10);
			fTempPerm12 = (fTempPerm5 + (-2 - fTempPerm9));
			fTempPerm13 = (0 - (0.5f * fTempPerm12));
			fTempPerm14 = (fTempPerm5 + (-3 - fTempPerm9));
			fTempPerm15 = (0 - (0.33333333333333331f * fTempPerm14));
			fTempPerm16 = (fTempPerm5 + (-4 - fTempPerm9));
			fTempPerm17 = (0 - (0.25f * fTempPerm16));
			fTempPerm18 = (fTempPerm5 - fTempPerm9);
			iTempPerm19 = int((int(min(fConst3, (float)max(0, (int)(iTempPerm7 + 2)))) + 1));
			fTempPerm20 = (0 - fTempPerm14);
			fTempPerm21 = (0 - (0.5f * fTempPerm16));
			iTempPerm22 = int((int(min(fConst3, (float)max(0, (int)(iTempPerm7 + 1)))) + 1));
			fTempPerm23 = (0 - fTempPerm12);
			fTempPerm24 = (0 - (0.5f * fTempPerm14));
			fTempPerm25 = (0 - (0.33333333333333331f * fTempPerm16));
			fTempPerm26 = (fTempPerm10 * fTempPerm12);
			iTempPerm27 = int((int(min(fConst3, (float)max(0, (int)(iTempPerm7 + 3)))) + 1));
			fTempPerm28 = (0 - fTempPerm16);
			fTempPerm29 = (fTempPerm26 * fTempPerm14);
			iTempPerm30 = int((int(min(fConst3, (float)max(0, (int)(iTempPerm7 + 4)))) + 1));
			fVec3[0] = (((((fRec16[(IOTA-iTempPerm8)&2047] * fTempPerm11) * fTempPerm13) * fTempPerm15) * fTempPerm17) + (fTempPerm18 * ((((0.5f * (((fTempPerm10 * fRec16[(IOTA-iTempPerm19)&2047]) * fTempPerm20) * fTempPerm21)) + (((fRec16[(IOTA-iTempPerm22)&2047] * fTempPerm23) * fTempPerm24) * fTempPerm25)) + (0.16666666666666666f * ((fTempPerm26 * fRec16[(IOTA-iTempPerm27)&2047]) * fTempPerm28))) + (0.041666666666666664f * (fTempPerm29 * fRec16[(IOTA-iTempPerm30)&2047])))));
			fRec11[0] = fVec3[1];
			int 	iRec12 = iRec17;
			float 	fRec7 = fRec10;
			float 	fRec8 = fRec11[0];
			float 	fRec9 = (fRec11[0] + iRec12);
			fRec2[IOTA&2047] = fRec7;
			float 	fRec3 = (((((fTempPerm11 * fTempPerm13) * fTempPerm15) * fTempPerm17) * fRec2[(IOTA-iTempPerm8)&2047]) + (fTempPerm18 * (((0.16666666666666666f * ((fTempPerm26 * fTempPerm28) * fRec2[(IOTA-iTempPerm27)&2047])) + ((((fTempPerm23 * fTempPerm24) * fTempPerm25) * fRec2[(IOTA-iTempPerm22)&2047]) + (0.5f * (((fTempPerm10 * fTempPerm20) * fTempPerm21) * fRec2[(IOTA-iTempPerm19)&2047])))) + (0.041666666666666664f * (fTempPerm29 * fRec2[(IOTA-iTempPerm30)&2047])))));
			float 	fRec4 = fRec8;
			float 	fRec5 = fRec9;
			fRec0[0] = fRec3;
			float 	fRec1 = fRec5;
			fTempPerm31 = (fSlow0 * fRec1);
			output0[i] = (FAUSTFLOAT)fTempPerm31;
			output1[i] = (FAUSTFLOAT)fTempPerm31;
			// post processing
			fRec0[1] = fRec0[0];
			fRec11[1] = fRec11[0];
			fVec3[1] = fVec3[0];
			IOTA = IOTA+1;
			fRec18[1] = fRec18[0];
			fVec2[1] = fVec2[0];
			fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
			fRec24[1] = fRec24[0];
			fRec23[1] = fRec23[0];
			fRec22[1] = fRec22[0];
			fRec21[1] = fRec21[0];
			fRec20[1] = fRec20[0];
			fVec1[1] = fVec1[0];
			fRec15[1] = fRec15[0];
			fRec13[1] = fRec13[0];
			fRec14[1] = fRec14[0];
			iVec0[1] = iVec0[0];
			iRec6[1] = iRec6[0];
		}
	}
};


