//----------------------------------------------------------
// copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
// license: "MIT"
// name: "ViolinMidi"
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
	int 	iVec0[2];
	float 	fConst0;
	float 	fConst1;
	float 	fConst2;
	float 	fConst3;
	float 	fConst4;
	float 	fConst5;
	FAUSTFLOAT 	fslider1;
	float 	fRec26[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT 	fbutton0;
	FAUSTFLOAT 	fslider4;
	float 	fVec1[2];
	int 	iTempPerm0;
	float 	fRec27[2];
	FAUSTFLOAT 	fslider5;
	float 	fConst6;
	FAUSTFLOAT 	fslider6;
	float 	fRec28[2];
	float 	fRec29[2];
	FAUSTFLOAT 	fslider7;
	float 	fConst7;
	FAUSTFLOAT 	fslider8;
	float 	fRec30[2];
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
	float 	fRec22[2];
	float 	fRec31[4];
	int 	IOTA;
	float 	fRec32[2048];
	float 	fTempPerm28;
	float 	fTempPerm29;
	int 	iTempPerm30;
	int 	iTempPerm31;
	float 	fTempPerm32;
	float 	fTempPerm33;
	float 	fTempPerm34;
	float 	fTempPerm35;
	float 	fTempPerm36;
	float 	fTempPerm37;
	float 	fTempPerm38;
	float 	fTempPerm39;
	float 	fTempPerm40;
	float 	fTempPerm41;
	int 	iTempPerm42;
	float 	fTempPerm43;
	float 	fTempPerm44;
	int 	iTempPerm45;
	float 	fTempPerm46;
	float 	fTempPerm47;
	float 	fTempPerm48;
	float 	fTempPerm49;
	int 	iTempPerm50;
	float 	fTempPerm51;
	float 	fTempPerm52;
	int 	iTempPerm53;
	float 	fVec2[2];
	float 	fTempPerm54;
	FAUSTFLOAT 	fslider9;
	float 	fRec34[2];
	float 	fTempPerm55;
	float 	fTempPerm56;
	float 	fVec3[2048];
	float 	fRec18[2048];
	float 	fRec20[2];
	float 	fRec16[4];
	float 	fConst8;
	float 	fConst9;
	float 	fRec14[3];
	float 	fConst10;
	float 	fTempPerm57;
	int 	iRec6[2];
	float 	fRec2[2048];
	float 	fRec0[2];
	float 	fTempPerm58;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("description", "Simple MIDI-controllable violin physical model.");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("license", "MIT");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "ViolinMidi");
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
		fConst1 = tanf((1570.7963267948965f / fConst0));
		fConst2 = (1.0f / fConst1);
		fConst3 = (1.0f / (((fConst2 + 0.5f) / fConst1) + 1));
		fConst4 = (0.0088235294117647058f * fConst0);
		fConst5 = (0.0014705882352941176f * fConst0);
		iTempPerm0 = 0;
		fConst6 = (6.2831853071795862f / fConst0);
		fConst7 = (1000.0f / fConst0);
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
		iTempPerm30 = 0;
		iTempPerm31 = 0;
		fTempPerm32 = 0;
		fTempPerm33 = 0;
		fTempPerm34 = 0;
		fTempPerm35 = 0;
		fTempPerm36 = 0;
		fTempPerm37 = 0;
		fTempPerm38 = 0;
		fTempPerm39 = 0;
		fTempPerm40 = 0;
		fTempPerm41 = 0;
		iTempPerm42 = 0;
		fTempPerm43 = 0;
		fTempPerm44 = 0;
		iTempPerm45 = 0;
		fTempPerm46 = 0;
		fTempPerm47 = 0;
		fTempPerm48 = 0;
		fTempPerm49 = 0;
		iTempPerm50 = 0;
		fTempPerm51 = 0;
		fTempPerm52 = 0;
		iTempPerm53 = 0;
		fTempPerm54 = 0;
		fTempPerm55 = 0;
		fTempPerm56 = 0;
		fConst8 = (((fConst2 + -0.5f) / fConst1) + 1);
		fConst9 = (2 * (1 - (1.0f / faustpower<2>(fConst1))));
		fConst10 = (0 - fConst2);
		fTempPerm57 = 0;
		fTempPerm58 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.5f;
		fslider1 = 0.69999999999999996f;
		fslider2 = 440.0f;
		fslider3 = 1.0f;
		fbutton0 = 0.0;
		fslider4 = 0.0f;
		fslider5 = 0.5f;
		fslider6 = 6.0f;
		fslider7 = 0.59999999999999998f;
		fslider8 = 1.0f;
		fslider9 = 0.5f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) iRec10[i] = 0;
		for (int i=0; i<2; i++) iVec0[i] = 0;
		for (int i=0; i<2; i++) fRec26[i] = 0;
		for (int i=0; i<2; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fRec27[i] = 0;
		for (int i=0; i<2; i++) fRec28[i] = 0;
		for (int i=0; i<2; i++) fRec29[i] = 0;
		for (int i=0; i<2; i++) fRec30[i] = 0;
		for (int i=0; i<2; i++) fRec22[i] = 0;
		for (int i=0; i<4; i++) fRec31[i] = 0;
		IOTA = 0;
		for (int i=0; i<2048; i++) fRec32[i] = 0;
		for (int i=0; i<2; i++) fVec2[i] = 0;
		for (int i=0; i<2; i++) fRec34[i] = 0;
		for (int i=0; i<2048; i++) fVec3[i] = 0;
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
		ui_interface->openHorizontalBox("midi");
		ui_interface->declare(&fslider2, "0", "");
		ui_interface->declare(&fslider2, "style", "knob");
		ui_interface->addHorizontalSlider("freq", &fslider2, 440.0f, 50.0f, 1000.0f, 0.01f);
		ui_interface->declare(&fslider3, "1", "");
		ui_interface->declare(&fslider3, "hidden", "1");
		ui_interface->declare(&fslider3, "midi", "pitchwheel");
		ui_interface->declare(&fslider3, "style", "knob");
		ui_interface->addHorizontalSlider("bend", &fslider3, 1.0f, 0.0f, 10.0f, 0.01f);
		ui_interface->declare(&fslider7, "2", "");
		ui_interface->declare(&fslider7, "style", "knob");
		ui_interface->addHorizontalSlider("gain", &fslider7, 0.59999999999999998f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider8, "3", "");
		ui_interface->declare(&fslider8, "style", "knob");
		ui_interface->addHorizontalSlider("envAttack", &fslider8, 1.0f, 0.0f, 30.0f, 0.01f);
		ui_interface->declare(&fslider4, "4", "");
		ui_interface->declare(&fslider4, "hidden", "1");
		ui_interface->declare(&fslider4, "midi", "ctrl 64");
		ui_interface->declare(&fslider4, "style", "knob");
		ui_interface->addHorizontalSlider("sustain", &fslider4, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("bow");
		ui_interface->declare(&fslider9, "0", "");
		ui_interface->declare(&fslider9, "midi", "ctrl 1");
		ui_interface->declare(&fslider9, "style", "knob");
		ui_interface->addHorizontalSlider("pressure", &fslider9, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider1, "1", "");
		ui_interface->declare(&fslider1, "style", "knob");
		ui_interface->addHorizontalSlider("position", &fslider1, 0.69999999999999996f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("otherParams");
		ui_interface->declare(&fslider6, "0", "");
		ui_interface->declare(&fslider6, "style", "knob");
		ui_interface->addHorizontalSlider("vibratoFrequency", &fslider6, 6.0f, 1.0f, 10.0f, 0.01f);
		ui_interface->declare(&fslider5, "1", "");
		ui_interface->declare(&fslider5, "style", "knob");
		ui_interface->addHorizontalSlider("vibratoGain", &fslider5, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider0, "2", "");
		ui_interface->declare(&fslider0, "style", "knob");
		ui_interface->addHorizontalSlider("outGain", &fslider0, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->declare(&fbutton0, "3", "");
		ui_interface->addButton("gate", &fbutton0);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = float(fslider0);
		float 	fSlow1 = (0.0010000000000000009f * float(fslider1));
		float 	fSlow2 = (float(340) / float(fslider2));
		float 	fSlow3 = float(fslider3);
		float 	fSlow4 = min((float)1, (float(fbutton0) + float(fslider4)));
		int 	iSlow5 = (fSlow4 == 0);
		float 	fSlow6 = (0.01f * float(fslider5));
		float 	fSlow7 = (fConst6 * float(fslider6));
		float 	fSlow8 = sinf(fSlow7);
		float 	fSlow9 = cosf(fSlow7);
		float 	fSlow10 = (0 - fSlow8);
		float 	fSlow11 = expf((0 - (fConst7 / float(fslider8))));
		float 	fSlow12 = ((fSlow4 * float(fslider7)) * (1.0f - fSlow11));
		float 	fSlow13 = (0.0010000000000000009f * float(fslider9));
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			iRec10[0] = 0;
			iVec0[0] = 1;
			int 	iRec11 = iRec10[1];
			float 	fRec15 = (iRec6[1] - (0.98926467176774091f * ((0.59999999999999998f * fRec16[2]) + (0.20000000000000001f * (fRec16[1] + fRec16[3])))));
			fRec26[0] = (fSlow1 + (0.999f * fRec26[1]));
			fVec1[0] = fSlow4;
			iTempPerm0 = ((fSlow4 == fVec1[1]) | iSlow5);
			fRec27[0] = ((fSlow3 * (1.0f - (0.999f * iTempPerm0))) + (0.999f * (iTempPerm0 * fRec27[1])));
			fRec28[0] = ((fSlow8 * fRec29[1]) + (fSlow9 * fRec28[1]));
			fRec29[0] = (((fSlow9 * fRec29[1]) + (fSlow10 * fRec28[1])) + (1 - iVec0[1]));
			fRec30[0] = (fSlow12 + (fSlow11 * fRec30[1]));
			fTempPerm1 = ((fSlow2 / (fRec27[0] * ((fSlow6 * (fRec28[0] * fRec30[0])) + 1))) + -0.080000000000000002f);
			fTempPerm2 = (fConst5 * ((1 - fRec26[0]) * fTempPerm1));
			fTempPerm3 = (fTempPerm2 + -1.499995f);
			iTempPerm4 = int(fTempPerm3);
			iTempPerm5 = int(min(fConst4, (float)max(0, (int)iTempPerm4)));
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
			iTempPerm16 = int(min(fConst4, (float)max(0, (int)(iTempPerm4 + 2))));
			fTempPerm17 = (0 - fTempPerm11);
			fTempPerm18 = (0 - (0.5f * fTempPerm13));
			iTempPerm19 = int(min(fConst4, (float)max(0, (int)(iTempPerm4 + 1))));
			fTempPerm20 = (0 - fTempPerm9);
			fTempPerm21 = (0 - (0.5f * fTempPerm11));
			fTempPerm22 = (0 - (0.33333333333333331f * fTempPerm13));
			fTempPerm23 = (fTempPerm7 * fTempPerm9);
			iTempPerm24 = int(min(fConst4, (float)max(0, (int)(iTempPerm4 + 3))));
			fTempPerm25 = (0 - fTempPerm13);
			fTempPerm26 = (fTempPerm23 * fTempPerm11);
			iTempPerm27 = int(min(fConst4, (float)max(0, (int)(iTempPerm4 + 4))));
			fRec22[0] = (((((fRec2[(IOTA-int((iTempPerm5 + 1)))&2047] * fTempPerm8) * fTempPerm10) * fTempPerm12) * fTempPerm14) + (fTempPerm15 * ((((0.5f * (((fTempPerm7 * fRec2[(IOTA-int((iTempPerm16 + 1)))&2047]) * fTempPerm17) * fTempPerm18)) + (((fRec2[(IOTA-int((iTempPerm19 + 1)))&2047] * fTempPerm20) * fTempPerm21) * fTempPerm22)) + (0.16666666666666666f * ((fTempPerm23 * fRec2[(IOTA-int((iTempPerm24 + 1)))&2047]) * fTempPerm25))) + (0.041666666666666664f * (fTempPerm26 * fRec2[(IOTA-int((iTempPerm27 + 1)))&2047])))));
			fRec31[0] = fRec0[1];
			fRec32[IOTA&2047] = (0 - (0.99880145575930335f * ((0.80000000000000004f * fRec31[2]) + (0.10000000000000001f * (fRec31[1] + fRec31[3])))));
			int 	iRec33 = 0;
			fTempPerm28 = (fConst5 * (fRec26[0] * fTempPerm1));
			fTempPerm29 = (fTempPerm28 + -1.499995f);
			iTempPerm30 = int(fTempPerm29);
			iTempPerm31 = int(min(fConst4, (float)max(0, (int)iTempPerm30)));
			fTempPerm32 = floorf(fTempPerm29);
			fTempPerm33 = (fTempPerm28 + (-1 - fTempPerm32));
			fTempPerm34 = (0 - fTempPerm33);
			fTempPerm35 = (fTempPerm28 + (-2 - fTempPerm32));
			fTempPerm36 = (0 - (0.5f * fTempPerm35));
			fTempPerm37 = (fTempPerm28 + (-3 - fTempPerm32));
			fTempPerm38 = (0 - (0.33333333333333331f * fTempPerm37));
			fTempPerm39 = (fTempPerm28 + (-4 - fTempPerm32));
			fTempPerm40 = (0 - (0.25f * fTempPerm39));
			fTempPerm41 = (fTempPerm28 - fTempPerm32);
			iTempPerm42 = int(min(fConst4, (float)max(0, (int)(iTempPerm30 + 2))));
			fTempPerm43 = (0 - fTempPerm37);
			fTempPerm44 = (0 - (0.5f * fTempPerm39));
			iTempPerm45 = int(min(fConst4, (float)max(0, (int)(iTempPerm30 + 1))));
			fTempPerm46 = (0 - fTempPerm35);
			fTempPerm47 = (0 - (0.5f * fTempPerm37));
			fTempPerm48 = (0 - (0.33333333333333331f * fTempPerm39));
			fTempPerm49 = (fTempPerm33 * fTempPerm35);
			iTempPerm50 = int(min(fConst4, (float)max(0, (int)(iTempPerm30 + 3))));
			fTempPerm51 = (0 - fTempPerm39);
			fTempPerm52 = (fTempPerm49 * fTempPerm37);
			iTempPerm53 = int(min(fConst4, (float)max(0, (int)(iTempPerm30 + 4))));
			fVec2[0] = (((((fRec32[(IOTA-int((iTempPerm31 + 2)))&2047] * fTempPerm34) * fTempPerm36) * fTempPerm38) * fTempPerm40) + (fTempPerm41 * ((((0.5f * (((fTempPerm33 * fRec32[(IOTA-int((iTempPerm42 + 2)))&2047]) * fTempPerm43) * fTempPerm44)) + (((fRec32[(IOTA-int((iTempPerm45 + 2)))&2047] * fTempPerm46) * fTempPerm47) * fTempPerm48)) + (0.16666666666666666f * ((fTempPerm49 * fRec32[(IOTA-int((iTempPerm50 + 2)))&2047]) * fTempPerm51))) + (0.041666666666666664f * (fTempPerm52 * fRec32[(IOTA-int((iTempPerm53 + 2)))&2047])))));
			fTempPerm54 = (fRec30[0] - (fRec22[1] + fVec2[1]));
			fRec34[0] = (fSlow13 + (0.999f * fRec34[1]));
			fTempPerm55 = (fTempPerm54 * min((float)1, (1.0f / faustpower<4>((fabsf(((5 - (4 * fRec34[0])) * fTempPerm54)) + 0.75f)))));
			float 	fRec23 = (fRec22[1] + fTempPerm55);
			fTempPerm56 = (fVec2[1] + fTempPerm55);
			fVec3[IOTA&2047] = fTempPerm56;
			float 	fRec24 = (((((fTempPerm8 * fTempPerm10) * fTempPerm12) * fTempPerm14) * fVec3[(IOTA-iTempPerm5)&2047]) + (fTempPerm15 * ((0.041666666666666664f * (fTempPerm26 * fVec3[(IOTA-iTempPerm27)&2047])) + (((((fTempPerm20 * fTempPerm21) * fTempPerm22) * fVec3[(IOTA-iTempPerm19)&2047]) + (0.5f * (((fTempPerm7 * fTempPerm17) * fTempPerm18) * fVec3[(IOTA-iTempPerm16)&2047]))) + (0.16666666666666666f * ((fTempPerm23 * fTempPerm25) * fVec3[(IOTA-iTempPerm24)&2047]))))));
			int 	iRec25 = iRec33;
			fRec18[IOTA&2047] = fRec23;
			float 	fRec19 = (((((fTempPerm34 * fTempPerm36) * fTempPerm38) * fTempPerm40) * fRec18[(IOTA-int((iTempPerm31 + 1)))&2047]) + (fTempPerm41 * (((0.16666666666666666f * ((fTempPerm49 * fTempPerm51) * fRec18[(IOTA-int((iTempPerm50 + 1)))&2047])) + ((((fTempPerm46 * fTempPerm47) * fTempPerm48) * fRec18[(IOTA-int((iTempPerm45 + 1)))&2047]) + (0.5f * (((fTempPerm33 * fTempPerm43) * fTempPerm44) * fRec18[(IOTA-int((iTempPerm42 + 1)))&2047])))) + (0.041666666666666664f * (fTempPerm52 * fRec18[(IOTA-int((iTempPerm53 + 1)))&2047])))));
			fRec20[0] = fRec24;
			int 	iRec21 = iRec25;
			fRec16[0] = fRec20[1];
			int 	iRec17 = iRec21;
			fRec14[0] = (fRec16[1] - (fConst3 * ((fConst8 * fRec14[2]) + (fConst9 * fRec14[1]))));
			fTempPerm57 = (fConst3 * ((fConst2 * fRec14[0]) + (fConst10 * fRec14[2])));
			float 	fRec12 = fTempPerm57;
			float 	fRec13 = (iRec17 + fTempPerm57);
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
			fTempPerm58 = (fSlow0 * fRec1);
			output0[i] = (FAUSTFLOAT)fTempPerm58;
			output1[i] = (FAUSTFLOAT)fTempPerm58;
			// post processing
			fRec0[1] = fRec0[0];
			iRec6[1] = iRec6[0];
			fRec14[2] = fRec14[1]; fRec14[1] = fRec14[0];
			for (int i=3; i>0; i--) fRec16[i] = fRec16[i-1];
			fRec20[1] = fRec20[0];
			fRec34[1] = fRec34[0];
			fVec2[1] = fVec2[0];
			IOTA = IOTA+1;
			for (int i=3; i>0; i--) fRec31[i] = fRec31[i-1];
			fRec22[1] = fRec22[0];
			fRec30[1] = fRec30[0];
			fRec29[1] = fRec29[0];
			fRec28[1] = fRec28[0];
			fRec27[1] = fRec27[0];
			fVec1[1] = fVec1[0];
			fRec26[1] = fRec26[0];
			iVec0[1] = iVec0[0];
			iRec10[1] = iRec10[0];
		}
	}
};


