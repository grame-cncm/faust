//----------------------------------------------------------
// copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
// license: "MIT"
// name: "FluteMIDI"
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
	FAUSTFLOAT 	fbutton0;
	FAUSTFLOAT 	fslider3;
	float 	fVec1[2];
	FAUSTFLOAT 	fslider4;
	float 	fConst2;
	FAUSTFLOAT 	fslider5;
	float 	fRec25[2];
	float 	fConst3;
	float 	fConst4;
	float 	fConst5;
	float 	fConst6;
	int 	iRec27[2];
	float 	fConst7;
	float 	fConst8;
	float 	fConst9;
	float 	fRec26[3];
	float 	fRec28[2];
	int 	IOTA;
	float 	fRec29[2048];
	float 	fConst10;
	float 	fConst11;
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT 	fslider7;
	int 	iTempPerm0;
	float 	fRec31[2];
	float 	fTempPerm1;
	FAUSTFLOAT 	fslider8;
	float 	fRec32[2];
	float 	fTempPerm2;
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
	float 	fVec2[2];
	float 	fTempPerm29;
	float 	fTempPerm30;
	float 	fVec3[2048];
	float 	fTempPerm31;
	float 	fTempPerm32;
	int 	iTempPerm33;
	int 	iTempPerm34;
	float 	fTempPerm35;
	float 	fTempPerm36;
	float 	fTempPerm37;
	float 	fTempPerm38;
	float 	fTempPerm39;
	float 	fTempPerm40;
	float 	fTempPerm41;
	float 	fTempPerm42;
	float 	fTempPerm43;
	float 	fTempPerm44;
	int 	iTempPerm45;
	float 	fTempPerm46;
	float 	fTempPerm47;
	int 	iTempPerm48;
	float 	fTempPerm49;
	float 	fTempPerm50;
	float 	fTempPerm51;
	float 	fTempPerm52;
	int 	iTempPerm53;
	float 	fTempPerm54;
	float 	fTempPerm55;
	int 	iTempPerm56;
	float 	fVec4[2];
	float 	fRec20[2];
	float 	fRec11[2048];
	float 	fRec7[2];
	float 	fRec3[2048];
	float 	fRec1[2];
	float 	fRec2[2];
	float 	fRec0[2];
	float 	fTempPerm57;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("description", "Simple MIDI-controllable flute physical model with physical parameters.");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("license", "MIT");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "FluteMIDI");
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
		fConst2 = (1000.0f / fConst0);
		fConst3 = tanf((6283.1853071795858f / fConst0));
		fConst4 = (1.0f / fConst3);
		fConst5 = (((fConst4 + 1.4142135623730949f) / fConst3) + 1);
		fConst6 = (0.050000000000000003f / fConst5);
		fConst7 = (1.0f / fConst5);
		fConst8 = (2 * (1 - (1.0f / faustpower<2>(fConst3))));
		fConst9 = (((fConst4 + -1.4142135623730949f) / fConst3) + 1);
		fConst10 = (0.0088235294117647058f * fConst0);
		fConst11 = (0.0014705882352941176f * fConst0);
		iTempPerm0 = 0;
		fTempPerm1 = 0;
		fTempPerm2 = 0;
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
		fTempPerm30 = 0;
		fTempPerm31 = 0;
		fTempPerm32 = 0;
		iTempPerm33 = 0;
		iTempPerm34 = 0;
		fTempPerm35 = 0;
		fTempPerm36 = 0;
		fTempPerm37 = 0;
		fTempPerm38 = 0;
		fTempPerm39 = 0;
		fTempPerm40 = 0;
		fTempPerm41 = 0;
		fTempPerm42 = 0;
		fTempPerm43 = 0;
		fTempPerm44 = 0;
		iTempPerm45 = 0;
		fTempPerm46 = 0;
		fTempPerm47 = 0;
		iTempPerm48 = 0;
		fTempPerm49 = 0;
		fTempPerm50 = 0;
		fTempPerm51 = 0;
		fTempPerm52 = 0;
		iTempPerm53 = 0;
		fTempPerm54 = 0;
		fTempPerm55 = 0;
		iTempPerm56 = 0;
		fTempPerm57 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.5f;
		fslider1 = 0.5f;
		fslider2 = 5.0f;
		fbutton0 = 0.0;
		fslider3 = 0.0f;
		fslider4 = 0.90000000000000002f;
		fslider5 = 1.0f;
		fslider6 = 440.0f;
		fslider7 = 1.0f;
		fslider8 = 0.5f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) iRec15[i] = 0;
		for (int i=0; i<2; i++) iVec0[i] = 0;
		for (int i=0; i<2; i++) fRec22[i] = 0;
		for (int i=0; i<2; i++) fRec23[i] = 0;
		for (int i=0; i<2; i++) fRec24[i] = 0;
		for (int i=0; i<2; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fRec25[i] = 0;
		for (int i=0; i<2; i++) iRec27[i] = 0;
		for (int i=0; i<3; i++) fRec26[i] = 0;
		for (int i=0; i<2; i++) fRec28[i] = 0;
		IOTA = 0;
		for (int i=0; i<2048; i++) fRec29[i] = 0;
		for (int i=0; i<2; i++) fRec31[i] = 0;
		for (int i=0; i<2; i++) fRec32[i] = 0;
		for (int i=0; i<2; i++) fVec2[i] = 0;
		for (int i=0; i<2048; i++) fVec3[i] = 0;
		for (int i=0; i<2; i++) fVec4[i] = 0;
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
		ui_interface->openVerticalBox("flute");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("midi");
		ui_interface->declare(&fslider6, "0", "");
		ui_interface->declare(&fslider6, "style", "knob");
		ui_interface->addHorizontalSlider("freq", &fslider6, 440.0f, 50.0f, 1000.0f, 0.01f);
		ui_interface->declare(&fslider7, "1", "");
		ui_interface->declare(&fslider7, "hidden", "1");
		ui_interface->declare(&fslider7, "midi", "pitchwheel");
		ui_interface->declare(&fslider7, "style", "knob");
		ui_interface->addHorizontalSlider("bend", &fslider7, 1.0f, 0.0f, 10.0f, 0.01f);
		ui_interface->declare(&fslider4, "2", "");
		ui_interface->declare(&fslider4, "style", "knob");
		ui_interface->addHorizontalSlider("gain", &fslider4, 0.90000000000000002f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider5, "3", "");
		ui_interface->declare(&fslider5, "style", "knob");
		ui_interface->addHorizontalSlider("envAttack", &fslider5, 1.0f, 0.0f, 30.0f, 0.01f);
		ui_interface->declare(&fslider3, "4", "");
		ui_interface->declare(&fslider3, "hidden", "1");
		ui_interface->declare(&fslider3, "midi", "ctrl 64");
		ui_interface->declare(&fslider3, "style", "knob");
		ui_interface->addHorizontalSlider("sustain", &fslider3, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("otherParams");
		ui_interface->declare(&fslider8, "0", "");
		ui_interface->declare(&fslider8, "midi", "ctrl 1");
		ui_interface->declare(&fslider8, "style", "knob");
		ui_interface->addHorizontalSlider("mouthPosition", &fslider8, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider2, "1", "");
		ui_interface->declare(&fslider2, "style", "knob");
		ui_interface->addHorizontalSlider("vibratoFreq", &fslider2, 5.0f, 1.0f, 10.0f, 0.01f);
		ui_interface->declare(&fslider1, "2", "");
		ui_interface->declare(&fslider1, "style", "knob");
		ui_interface->addHorizontalSlider("vibratoGain", &fslider1, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider0, "3", "");
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
		float 	fSlow1 = (0.040000000000000001f * float(fslider1));
		float 	fSlow2 = (fConst1 * float(fslider2));
		float 	fSlow3 = sinf(fSlow2);
		float 	fSlow4 = cosf(fSlow2);
		float 	fSlow5 = (0 - fSlow3);
		float 	fSlow6 = min((float)1, (float(fbutton0) + float(fslider3)));
		float 	fSlow7 = expf((0 - (fConst2 / float(fslider5))));
		float 	fSlow8 = ((fSlow6 * float(fslider4)) * (1.0f - fSlow7));
		float 	fSlow9 = (float(340) / float(fslider6));
		float 	fSlow10 = float(fslider7);
		int 	iSlow11 = (fSlow6 == 0);
		float 	fSlow12 = (0.0010000000000000009f * float(fslider8));
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
			fVec1[0] = fSlow6;
			fRec25[0] = (fSlow8 + (fSlow7 * fRec25[1]));
			iRec27[0] = ((1103515245 * iRec27[1]) + 12345);
			fRec26[0] = ((4.6566128752457969e-10f * iRec27[0]) - (fConst7 * ((fConst8 * fRec26[1]) + (fConst9 * fRec26[2]))));
			fRec28[0] = fRec1[1];
			fRec29[IOTA&2047] = (0.94999999999999996f * fRec28[1]);
			int 	iRec30 = 0;
			iTempPerm0 = ((fSlow6 == fVec1[1]) | iSlow11);
			fRec31[0] = ((fSlow10 * (1.0f - (0.999f * iTempPerm0))) + (0.999f * (iTempPerm0 * fRec31[1])));
			fTempPerm1 = ((fSlow9 / fRec31[0]) + 0.27000000000000002f);
			fRec32[0] = (fSlow12 + (0.999f * fRec32[1]));
			fTempPerm2 = (0.40000000000000002f * (fRec32[0] + -0.5f));
			fTempPerm3 = (fConst11 * (fTempPerm1 * (fTempPerm2 + 0.27000000000000002f)));
			fTempPerm4 = (fTempPerm3 + -1.499995f);
			iTempPerm5 = int(fTempPerm4);
			iTempPerm6 = int((int(min(fConst10, (float)max(0, (int)iTempPerm5))) + 1));
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
			iTempPerm17 = int((int(min(fConst10, (float)max(0, (int)(iTempPerm5 + 2)))) + 1));
			fTempPerm18 = (0 - fTempPerm12);
			fTempPerm19 = (0 - (0.5f * fTempPerm14));
			iTempPerm20 = int((int(min(fConst10, (float)max(0, (int)(iTempPerm5 + 1)))) + 1));
			fTempPerm21 = (0 - fTempPerm10);
			fTempPerm22 = (0 - (0.5f * fTempPerm12));
			fTempPerm23 = (0 - (0.33333333333333331f * fTempPerm14));
			fTempPerm24 = (fTempPerm8 * fTempPerm10);
			iTempPerm25 = int((int(min(fConst10, (float)max(0, (int)(iTempPerm5 + 3)))) + 1));
			fTempPerm26 = (0 - fTempPerm14);
			fTempPerm27 = (fTempPerm24 * fTempPerm12);
			iTempPerm28 = int((int(min(fConst10, (float)max(0, (int)(iTempPerm5 + 4)))) + 1));
			fVec2[0] = (((((fRec29[(IOTA-iTempPerm6)&2047] * fTempPerm9) * fTempPerm11) * fTempPerm13) * fTempPerm15) + (fTempPerm16 * ((((0.5f * (((fTempPerm8 * fRec29[(IOTA-iTempPerm17)&2047]) * fTempPerm18) * fTempPerm19)) + (((fRec29[(IOTA-iTempPerm20)&2047] * fTempPerm21) * fTempPerm22) * fTempPerm23)) + (0.16666666666666666f * ((fTempPerm24 * fRec29[(IOTA-iTempPerm25)&2047]) * fTempPerm26))) + (0.041666666666666664f * (fTempPerm27 * fRec29[(IOTA-iTempPerm28)&2047])))));
			fTempPerm29 = (((fSlow1 * fRec23[0]) + (fRec25[0] * ((fConst6 * (fRec26[2] + (fRec26[0] + (2.0f * fRec26[1])))) + 1))) - (0.5f * fVec2[1]));
			fTempPerm30 = ((0.5f * fRec7[1]) + max((float)-1, min((float)1, (fTempPerm29 * (faustpower<2>(fTempPerm29) + -1)))));
			fVec3[IOTA&2047] = fTempPerm30;
			fTempPerm31 = (fConst11 * (fTempPerm1 * (0.72999999999999998f - fTempPerm2)));
			fTempPerm32 = (fTempPerm31 + -1.499995f);
			iTempPerm33 = int(fTempPerm32);
			iTempPerm34 = int((int(min(fConst10, (float)max(0, (int)iTempPerm33))) + 1));
			fTempPerm35 = floorf(fTempPerm32);
			fTempPerm36 = (fTempPerm31 + (-1 - fTempPerm35));
			fTempPerm37 = (0 - fTempPerm36);
			fTempPerm38 = (fTempPerm31 + (-2 - fTempPerm35));
			fTempPerm39 = (0 - (0.5f * fTempPerm38));
			fTempPerm40 = (fTempPerm31 + (-3 - fTempPerm35));
			fTempPerm41 = (0 - (0.33333333333333331f * fTempPerm40));
			fTempPerm42 = (fTempPerm31 + (-4 - fTempPerm35));
			fTempPerm43 = (0 - (0.25f * fTempPerm42));
			fTempPerm44 = (fTempPerm31 - fTempPerm35);
			iTempPerm45 = int((int(min(fConst10, (float)max(0, (int)(iTempPerm33 + 2)))) + 1));
			fTempPerm46 = (0 - fTempPerm40);
			fTempPerm47 = (0 - (0.5f * fTempPerm42));
			iTempPerm48 = int((int(min(fConst10, (float)max(0, (int)(iTempPerm33 + 1)))) + 1));
			fTempPerm49 = (0 - fTempPerm38);
			fTempPerm50 = (0 - (0.5f * fTempPerm40));
			fTempPerm51 = (0 - (0.33333333333333331f * fTempPerm42));
			fTempPerm52 = (fTempPerm36 * fTempPerm38);
			iTempPerm53 = int((int(min(fConst10, (float)max(0, (int)(iTempPerm33 + 3)))) + 1));
			fTempPerm54 = (0 - fTempPerm42);
			fTempPerm55 = (fTempPerm52 * fTempPerm40);
			iTempPerm56 = int((int(min(fConst10, (float)max(0, (int)(iTempPerm33 + 4)))) + 1));
			fVec4[0] = (((((fVec3[(IOTA-iTempPerm34)&2047] * fTempPerm37) * fTempPerm39) * fTempPerm41) * fTempPerm43) + (fTempPerm44 * ((((0.5f * (((fTempPerm36 * fVec3[(IOTA-iTempPerm45)&2047]) * fTempPerm46) * fTempPerm47)) + (((fVec3[(IOTA-iTempPerm48)&2047] * fTempPerm49) * fTempPerm50) * fTempPerm51)) + (0.16666666666666666f * ((fTempPerm52 * fVec3[(IOTA-iTempPerm53)&2047]) * fTempPerm54))) + (0.041666666666666664f * (fTempPerm55 * fVec3[(IOTA-iTempPerm56)&2047])))));
			fRec20[0] = fVec4[1];
			int 	iRec21 = iRec30;
			float 	fRec16 = fRec19;
			float 	fRec17 = fRec20[0];
			float 	fRec18 = (fRec20[0] + iRec21);
			fRec11[IOTA&2047] = fRec16;
			float 	fRec12 = (((((fTempPerm37 * fTempPerm39) * fTempPerm41) * fTempPerm43) * fRec11[(IOTA-iTempPerm34)&2047]) + (fTempPerm44 * (((0.16666666666666666f * ((fTempPerm52 * fTempPerm54) * fRec11[(IOTA-iTempPerm53)&2047])) + ((((fTempPerm49 * fTempPerm50) * fTempPerm51) * fRec11[(IOTA-iTempPerm48)&2047]) + (0.5f * (((fTempPerm36 * fTempPerm46) * fTempPerm47) * fRec11[(IOTA-iTempPerm45)&2047])))) + (0.041666666666666664f * (fTempPerm55 * fRec11[(IOTA-iTempPerm56)&2047])))));
			float 	fRec13 = fRec17;
			float 	fRec14 = fRec18;
			fRec7[0] = fRec12;
			float 	fRec8 = fRec7[1];
			float 	fRec9 = fRec13;
			float 	fRec10 = fRec14;
			fRec3[IOTA&2047] = fRec8;
			float 	fRec4 = (((((fTempPerm9 * fTempPerm11) * fTempPerm13) * fTempPerm15) * fRec3[(IOTA-iTempPerm6)&2047]) + (fTempPerm16 * (((0.16666666666666666f * ((fTempPerm24 * fTempPerm26) * fRec3[(IOTA-iTempPerm25)&2047])) + ((((fTempPerm21 * fTempPerm22) * fTempPerm23) * fRec3[(IOTA-iTempPerm20)&2047]) + (0.5f * (((fTempPerm8 * fTempPerm18) * fTempPerm19) * fRec3[(IOTA-iTempPerm17)&2047])))) + (0.041666666666666664f * (fTempPerm27 * fRec3[(IOTA-iTempPerm28)&2047])))));
			float 	fRec5 = fRec9;
			float 	fRec6 = fRec10;
			fRec1[0] = fRec4;
			fRec2[0] = fRec6;
			fRec0[0] = ((fRec2[0] + (0.995f * fRec0[1])) - fRec2[1]);
			fTempPerm57 = (fSlow0 * fRec0[0]);
			output0[i] = (FAUSTFLOAT)fTempPerm57;
			output1[i] = (FAUSTFLOAT)fTempPerm57;
			// post processing
			fRec0[1] = fRec0[0];
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
			fRec7[1] = fRec7[0];
			fRec20[1] = fRec20[0];
			fVec4[1] = fVec4[0];
			fVec2[1] = fVec2[0];
			fRec32[1] = fRec32[0];
			fRec31[1] = fRec31[0];
			IOTA = IOTA+1;
			fRec28[1] = fRec28[0];
			fRec26[2] = fRec26[1]; fRec26[1] = fRec26[0];
			iRec27[1] = iRec27[0];
			fRec25[1] = fRec25[0];
			fVec1[1] = fVec1[0];
			fRec24[1] = fRec24[0];
			fRec23[1] = fRec23[0];
			fRec22[1] = fRec22[0];
			iVec0[1] = iVec0[0];
			iRec15[1] = iRec15[0];
		}
	}
};


