//----------------------------------------------------------
// copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
// license: "MIT"
// name: "Vocal BandPass MIDI"
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
	int 	iVec0[2];
	FAUSTFLOAT 	fbutton0;
	FAUSTFLOAT 	fslider1;
	float 	fVec1[2];
	FAUSTFLOAT 	fslider2;
	float 	fConst0;
	float 	fConst1;
	FAUSTFLOAT 	fslider3;
	float 	fRec1[2];
	FAUSTFLOAT 	fslider4;
	float 	fRec2[2];
	float 	fConst2;
	float 	fConst3;
	FAUSTFLOAT 	fslider5;
	int 	iTempPerm0;
	FAUSTFLOAT 	fslider6;
	float 	fRec5[2];
	FAUSTFLOAT 	fslider7;
	float 	fConst4;
	FAUSTFLOAT 	fslider8;
	float 	fRec6[2];
	int 	iTempPerm1;
	float 	fRec7[2];
	float 	fTempPerm2;
	float 	fTempPerm3;
	float 	fTempPerm4;
	int 	iTempPerm5;
	float 	fRec3[2];
	int 	iRec8[2];
	float 	fTempPerm6;
	float 	fConst5;
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT 	fslider10;
	float 	fRec9[2];
	float 	fTempPerm7;
	int 	iTempPerm8;
	int 	iTempPerm9;
	int 	iTempPerm10;
	int 	iTempPerm11;
	int 	iTempPerm12;
	int 	iTempPerm13;
	int 	iTempPerm14;
	int 	iTempPerm15;
	int 	iTempPerm16;
	int 	iTempPerm17;
	int 	iTempPerm18;
	int 	iTempPerm19;
	int 	iTempPerm20;
	int 	iTempPerm21;
	int 	iTempPerm22;
	int 	iTempPerm23;
	int 	iTempPerm24;
	int 	iTempPerm25;
	int 	iTempPerm26;
	int 	iTempPerm27;
	int 	iTempPerm28;
	int 	iTempPerm29;
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
	float 	fTempPerm42;
	float 	fTempPerm43;
	float 	fTempPerm44;
	float 	fTempPerm45;
	float 	fTempPerm46;
	float 	fTempPerm47;
	float 	fTempPerm48;
	float 	fTempPerm49;
	float 	fTempPerm50;
	float 	fTempPerm51;
	float 	fTempPerm52;
	float 	fTempPerm53;
	float 	fTempPerm54;
	float 	fTempPerm55;
	int 	iTempPerm56;
	float 	fTempPerm57;
	float 	fTempPerm58;
	float 	fRec10[2];
	float 	fRec11[2];
	float 	fTempPerm59;
	float 	fTempPerm60;
	float 	fTempPerm61;
	float 	fTempPerm62;
	float 	fTempPerm63;
	float 	fTempPerm64;
	float 	fTempPerm65;
	float 	fTempPerm66;
	float 	fTempPerm67;
	float 	fTempPerm68;
	float 	fTempPerm69;
	float 	fTempPerm70;
	float 	fTempPerm71;
	float 	fTempPerm72;
	float 	fRec0[3];
	float 	fTempPerm73;
	float 	fTempPerm74;
	float 	fTempPerm75;
	float 	fTempPerm76;
	float 	fTempPerm77;
	float 	fTempPerm78;
	float 	fTempPerm79;
	float 	fTempPerm80;
	float 	fTempPerm81;
	float 	fTempPerm82;
	float 	fTempPerm83;
	float 	fTempPerm84;
	float 	fTempPerm85;
	float 	fTempPerm86;
	float 	fRec12[3];
	float 	fTempPerm87;
	float 	fTempPerm88;
	float 	fTempPerm89;
	float 	fTempPerm90;
	float 	fTempPerm91;
	float 	fTempPerm92;
	float 	fTempPerm93;
	float 	fTempPerm94;
	float 	fTempPerm95;
	float 	fTempPerm96;
	float 	fTempPerm97;
	float 	fTempPerm98;
	float 	fTempPerm99;
	float 	fTempPerm100;
	float 	fRec13[3];
	float 	fTempPerm101;
	float 	fTempPerm102;
	float 	fTempPerm103;
	float 	fTempPerm104;
	float 	fTempPerm105;
	float 	fTempPerm106;
	float 	fTempPerm107;
	float 	fTempPerm108;
	float 	fTempPerm109;
	float 	fRec14[3];
	float 	fTempPerm110;
	float 	fTempPerm111;
	float 	fTempPerm112;
	float 	fTempPerm113;
	float 	fTempPerm114;
	float 	fTempPerm115;
	float 	fTempPerm116;
	float 	fTempPerm117;
	float 	fRec15[3];
	float 	fTempPerm118;
	float 	fTempPerm119;
	float 	fTempPerm120;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
		m->declare("description", "Simple MIDI-controllable source-filter vocal synthesizer.");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("license", "MIT");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "Vocal BandPass MIDI");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
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
		fConst2 = float(fConst0);
		fConst3 = (1.0f / fConst2);
		iTempPerm0 = 0;
		fConst4 = (6.2831853071795862f / fConst0);
		iTempPerm1 = 0;
		fTempPerm2 = 0;
		fTempPerm3 = 0;
		fTempPerm4 = 0;
		iTempPerm5 = 0;
		fTempPerm6 = 0;
		fConst5 = (3.1415926535897931f / fConst0);
		fTempPerm7 = 0;
		iTempPerm8 = 0;
		iTempPerm9 = 0;
		iTempPerm10 = 0;
		iTempPerm11 = 0;
		iTempPerm12 = 0;
		iTempPerm13 = 0;
		iTempPerm14 = 0;
		iTempPerm15 = 0;
		iTempPerm16 = 0;
		iTempPerm17 = 0;
		iTempPerm18 = 0;
		iTempPerm19 = 0;
		iTempPerm20 = 0;
		iTempPerm21 = 0;
		iTempPerm22 = 0;
		iTempPerm23 = 0;
		iTempPerm24 = 0;
		iTempPerm25 = 0;
		iTempPerm26 = 0;
		iTempPerm27 = 0;
		iTempPerm28 = 0;
		iTempPerm29 = 0;
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
		fTempPerm42 = 0;
		fTempPerm43 = 0;
		fTempPerm44 = 0;
		fTempPerm45 = 0;
		fTempPerm46 = 0;
		fTempPerm47 = 0;
		fTempPerm48 = 0;
		fTempPerm49 = 0;
		fTempPerm50 = 0;
		fTempPerm51 = 0;
		fTempPerm52 = 0;
		fTempPerm53 = 0;
		fTempPerm54 = 0;
		fTempPerm55 = 0;
		iTempPerm56 = 0;
		fTempPerm57 = 0;
		fTempPerm58 = 0;
		fTempPerm59 = 0;
		fTempPerm60 = 0;
		fTempPerm61 = 0;
		fTempPerm62 = 0;
		fTempPerm63 = 0;
		fTempPerm64 = 0;
		fTempPerm65 = 0;
		fTempPerm66 = 0;
		fTempPerm67 = 0;
		fTempPerm68 = 0;
		fTempPerm69 = 0;
		fTempPerm70 = 0;
		fTempPerm71 = 0;
		fTempPerm72 = 0;
		fTempPerm73 = 0;
		fTempPerm74 = 0;
		fTempPerm75 = 0;
		fTempPerm76 = 0;
		fTempPerm77 = 0;
		fTempPerm78 = 0;
		fTempPerm79 = 0;
		fTempPerm80 = 0;
		fTempPerm81 = 0;
		fTempPerm82 = 0;
		fTempPerm83 = 0;
		fTempPerm84 = 0;
		fTempPerm85 = 0;
		fTempPerm86 = 0;
		fTempPerm87 = 0;
		fTempPerm88 = 0;
		fTempPerm89 = 0;
		fTempPerm90 = 0;
		fTempPerm91 = 0;
		fTempPerm92 = 0;
		fTempPerm93 = 0;
		fTempPerm94 = 0;
		fTempPerm95 = 0;
		fTempPerm96 = 0;
		fTempPerm97 = 0;
		fTempPerm98 = 0;
		fTempPerm99 = 0;
		fTempPerm100 = 0;
		fTempPerm101 = 0;
		fTempPerm102 = 0;
		fTempPerm103 = 0;
		fTempPerm104 = 0;
		fTempPerm105 = 0;
		fTempPerm106 = 0;
		fTempPerm107 = 0;
		fTempPerm108 = 0;
		fTempPerm109 = 0;
		fTempPerm110 = 0;
		fTempPerm111 = 0;
		fTempPerm112 = 0;
		fTempPerm113 = 0;
		fTempPerm114 = 0;
		fTempPerm115 = 0;
		fTempPerm116 = 0;
		fTempPerm117 = 0;
		fTempPerm118 = 0;
		fTempPerm119 = 0;
		fTempPerm120 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.5f;
		fbutton0 = 0.0;
		fslider1 = 0.0f;
		fslider2 = 0.90000000000000002f;
		fslider3 = 10.0f;
		fslider4 = 0.0f;
		fslider5 = 440.0f;
		fslider6 = 1.0f;
		fslider7 = 0.5f;
		fslider8 = 6.0f;
		fslider9 = 0.0f;
		fslider10 = 0.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) iVec0[i] = 0;
		for (int i=0; i<2; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<2; i++) fRec7[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) iRec8[i] = 0;
		for (int i=0; i<2; i++) fRec9[i] = 0;
		for (int i=0; i<2; i++) fRec10[i] = 0;
		for (int i=0; i<2; i++) fRec11[i] = 0;
		for (int i=0; i<3; i++) fRec0[i] = 0;
		for (int i=0; i<3; i++) fRec12[i] = 0;
		for (int i=0; i<3; i++) fRec13[i] = 0;
		for (int i=0; i<3; i++) fRec14[i] = 0;
		for (int i=0; i<3; i++) fRec15[i] = 0;
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
		ui_interface->openVerticalBox("vocal");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("midi");
		ui_interface->declare(&fslider5, "0", "");
		ui_interface->declare(&fslider5, "style", "knob");
		ui_interface->addHorizontalSlider("freq", &fslider5, 440.0f, 50.0f, 1000.0f, 0.01f);
		ui_interface->declare(&fslider6, "1", "");
		ui_interface->declare(&fslider6, "hidden", "1");
		ui_interface->declare(&fslider6, "midi", "pitchwheel");
		ui_interface->declare(&fslider6, "style", "knob");
		ui_interface->addHorizontalSlider("bend", &fslider6, 1.0f, 0.0f, 10.0f, 0.01f);
		ui_interface->declare(&fslider2, "2", "");
		ui_interface->declare(&fslider2, "style", "knob");
		ui_interface->addHorizontalSlider("gain", &fslider2, 0.90000000000000002f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider3, "3", "");
		ui_interface->declare(&fslider3, "style", "knob");
		ui_interface->addHorizontalSlider("envAttack", &fslider3, 10.0f, 0.0f, 30.0f, 0.01f);
		ui_interface->declare(&fslider1, "4", "");
		ui_interface->declare(&fslider1, "hidden", "1");
		ui_interface->declare(&fslider1, "midi", "ctrl 64");
		ui_interface->declare(&fslider1, "style", "knob");
		ui_interface->addHorizontalSlider("sustain", &fslider1, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("otherParams");
		ui_interface->declare(&fslider9, "0", "");
		ui_interface->declare(&fslider9, "style", "knob");
		ui_interface->addHorizontalSlider("voiceType", &fslider9, 0.0f, 0.0f, 4.0f, 1.0f);
		ui_interface->declare(&fslider10, "1", "");
		ui_interface->declare(&fslider10, "midi", "ctrl 1");
		ui_interface->declare(&fslider10, "style", "knob");
		ui_interface->addHorizontalSlider("vowel", &fslider10, 0.0f, 0.0f, 4.0f, 0.01f);
		ui_interface->declare(&fslider4, "2", "");
		ui_interface->declare(&fslider4, "style", "knob");
		ui_interface->addHorizontalSlider("fricative", &fslider4, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider8, "3", "");
		ui_interface->declare(&fslider8, "style", "knob");
		ui_interface->addHorizontalSlider("vibratoFreq", &fslider8, 6.0f, 1.0f, 10.0f, 0.01f);
		ui_interface->declare(&fslider7, "4", "");
		ui_interface->declare(&fslider7, "style", "knob");
		ui_interface->addHorizontalSlider("vibratoGain", &fslider7, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider0, "5", "");
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
		float 	fSlow1 = min((float)1, (float(fbutton0) + float(fslider1)));
		float 	fSlow2 = expf((0 - (fConst1 / float(fslider3))));
		float 	fSlow3 = ((fSlow1 * float(fslider2)) * (1.0f - fSlow2));
		float 	fSlow4 = (0.0010000000000000009f * float(fslider4));
		float 	fSlow5 = float(fslider5);
		int 	iSlow6 = (fSlow1 == 0);
		float 	fSlow7 = float(fslider6);
		float 	fSlow8 = (0.10000000000000001f * float(fslider7));
		float 	fSlow9 = (fConst4 * float(fslider8));
		float 	fSlow10 = sinf(fSlow9);
		float 	fSlow11 = cosf(fSlow9);
		float 	fSlow12 = (0 - fSlow10);
		float 	fSlow13 = float(fslider9);
		float 	fSlow14 = (5 * fSlow13);
		float 	fSlow15 = (0.0010000000000000009f * float(fslider10));
		float 	fSlow16 = (5 * (1 - fSlow13));
		int 	iSlow17 = int((((int((fSlow13 == 0)))?1:((int((fSlow13 == 3)))?1:0)) == 0));
		int 	iSlow18 = int((fSlow13 != 2));
		float 	fSlow19 = (2 * fSlow5);
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			iVec0[0] = 1;
			fVec1[0] = fSlow1;
			fRec1[0] = (fSlow3 + (fSlow2 * fRec1[1]));
			fRec2[0] = (fSlow4 + (0.999f * fRec2[1]));
			iTempPerm0 = ((fSlow1 == fVec1[1]) | iSlow6);
			fRec5[0] = ((0.999f * (fRec5[1] * iTempPerm0)) + (fSlow7 * (1.0f - (0.999f * iTempPerm0))));
			fRec6[0] = ((fSlow10 * fRec7[1]) + (fSlow11 * fRec6[1]));
			iTempPerm1 = (1 - iVec0[1]);
			fRec7[0] = (((fSlow11 * fRec7[1]) + (fSlow12 * fRec6[1])) + iTempPerm1);
			fTempPerm2 = float(max(9.9999999999999995e-08f, fabsf((fSlow5 * (fRec5[0] * ((fSlow8 * fRec6[0]) + 1))))));
			fTempPerm3 = (fRec3[1] + (fConst3 * fTempPerm2));
			fTempPerm4 = (fTempPerm3 + -1);
			iTempPerm5 = int((fTempPerm4 < 0));
			fRec3[0] = ((iTempPerm5)?fTempPerm3:fTempPerm4);
			float 	fRec4 = ((iTempPerm5)?fTempPerm3:(fTempPerm3 + (fTempPerm4 * (1 - (fConst2 / fTempPerm2)))));
			iRec8[0] = ((1103515245 * iRec8[1]) + 12345);
			fTempPerm6 = (fRec1[0] * (((1 - fRec2[0]) * ((2 * fRec4) + -1)) + (4.6566128752457969e-10f * (fRec2[0] * iRec8[0]))));
			fRec9[0] = (fSlow15 + (0.999f * fRec9[1]));
			fTempPerm7 = (fSlow14 + fRec9[0]);
			iTempPerm8 = int((fTempPerm7 < 23));
			iTempPerm9 = int((fTempPerm7 < 22));
			iTempPerm10 = int((fTempPerm7 < 21));
			iTempPerm11 = int((fTempPerm7 < 20));
			iTempPerm12 = int((fTempPerm7 < 19));
			iTempPerm13 = int((fTempPerm7 < 18));
			iTempPerm14 = int((fTempPerm7 < 17));
			iTempPerm15 = int((fTempPerm7 < 16));
			iTempPerm16 = int((fTempPerm7 < 15));
			iTempPerm17 = int((fTempPerm7 < 14));
			iTempPerm18 = int((fTempPerm7 < 13));
			iTempPerm19 = int((fTempPerm7 < 12));
			iTempPerm20 = int((fTempPerm7 < 11));
			iTempPerm21 = int((fTempPerm7 < 10));
			iTempPerm22 = int((fTempPerm7 < 9));
			iTempPerm23 = int((fTempPerm7 < 8));
			iTempPerm24 = int((fTempPerm7 < 7));
			iTempPerm25 = int((fTempPerm7 < 6));
			iTempPerm26 = int((fTempPerm7 < 5));
			iTempPerm27 = int((fTempPerm7 < 4));
			iTempPerm28 = int((fTempPerm7 < 3));
			iTempPerm29 = int((fTempPerm7 < 2));
			iTempPerm30 = int((fTempPerm7 < 1));
			iTempPerm31 = int((fTempPerm7 < 0));
			fTempPerm32 = (fSlow14 + (fRec9[0] + -1));
			fTempPerm33 = (fSlow14 + (fRec9[0] + -2));
			fTempPerm34 = (fSlow14 + (fRec9[0] + -3));
			fTempPerm35 = (fSlow14 + (fRec9[0] + -4));
			fTempPerm36 = (fRec9[0] - fSlow16);
			fTempPerm37 = (fSlow14 + (fRec9[0] + -6));
			fTempPerm38 = (fSlow14 + (fRec9[0] + -7));
			fTempPerm39 = (fSlow14 + (fRec9[0] + -8));
			fTempPerm40 = (50 * fTempPerm39);
			fTempPerm41 = (fSlow14 + (fRec9[0] + -9));
			fTempPerm42 = (fSlow14 + (fRec9[0] + -10));
			fTempPerm43 = (fSlow14 + (fRec9[0] + -11));
			fTempPerm44 = (fSlow14 + (fRec9[0] + -12));
			fTempPerm45 = (fSlow14 + (fRec9[0] + -13));
			fTempPerm46 = (fSlow14 + (fRec9[0] + -14));
			fTempPerm47 = (fSlow14 + (fRec9[0] + -15));
			fTempPerm48 = (fSlow14 + (fRec9[0] + -16));
			fTempPerm49 = (80 * fTempPerm48);
			fTempPerm50 = (fSlow14 + (fRec9[0] + -17));
			fTempPerm51 = (fSlow14 + (fRec9[0] + -18));
			fTempPerm52 = (fSlow14 + (fRec9[0] + -19));
			fTempPerm53 = (fSlow14 + (fRec9[0] + -20));
			fTempPerm54 = (fSlow14 + (fRec9[0] + -21));
			fTempPerm55 = (fSlow14 + (fRec9[0] + -22));
			iTempPerm56 = int((fTempPerm7 < 24));
			fTempPerm57 = (fSlow14 + (fRec9[0] + -23));
			fTempPerm58 = ((iTempPerm8)?((iTempPerm9)?((iTempPerm10)?((iTempPerm11)?((iTempPerm12)?((iTempPerm13)?((iTempPerm14)?((iTempPerm15)?((iTempPerm16)?((iTempPerm17)?((iTempPerm18)?((iTempPerm19)?((iTempPerm20)?((iTempPerm21)?((iTempPerm22)?((iTempPerm23)?((iTempPerm24)?((iTempPerm25)?((iTempPerm26)?((iTempPerm27)?((iTempPerm28)?((iTempPerm29)?((iTempPerm30)?((iTempPerm31)?800:((iTempPerm30)?(800 - (400 * fTempPerm7)):400)):((iTempPerm29)?(400 - (50 * fTempPerm32)):350)):((iTempPerm28)?((100 * fTempPerm33) + 350):450)):((iTempPerm27)?(450 - (125 * fTempPerm34)):325)):((iTempPerm26)?((275 * fTempPerm35) + 325):600)):((iTempPerm25)?(600 - (200 * fTempPerm36)):400)):((iTempPerm24)?(400 - (150 * fTempPerm37)):250)):((iTempPerm23)?((150 * fTempPerm38) + 250):400)):((iTempPerm22)?(400 - fTempPerm40):350)):((iTempPerm21)?((310 * fTempPerm41) + 350):660)):((iTempPerm20)?(660 - (220 * fTempPerm42)):440)):((iTempPerm19)?(440 - (170 * fTempPerm43)):270)):((iTempPerm18)?((160 * fTempPerm44) + 270):430)):((iTempPerm17)?(430 - (60 * fTempPerm45)):370)):((iTempPerm16)?((430 * fTempPerm46) + 370):800)):((iTempPerm15)?(800 - (450 * fTempPerm47)):350)):((iTempPerm14)?(350 - fTempPerm49):270)):((iTempPerm13)?((180 * fTempPerm50) + 270):450)):((iTempPerm12)?(450 - (125 * fTempPerm51)):325)):((iTempPerm11)?(325 * (fTempPerm52 + 1)):650)):((iTempPerm10)?(650 - (250 * fTempPerm53)):400)):((iTempPerm9)?(400 - (110 * fTempPerm54)):290)):((iTempPerm8)?((110 * fTempPerm55) + 290):400)):((iTempPerm56)?(400 - (50 * fTempPerm57)):350));
			fRec10[0] = ((fSlow10 * fRec11[1]) + (fSlow11 * fRec10[1]));
			fRec11[0] = (((fSlow11 * fRec11[1]) + (fSlow12 * fRec10[1])) + iTempPerm1);
			fTempPerm59 = (fRec5[0] * ((fSlow8 * fRec10[0]) + 1));
			fTempPerm60 = (fSlow5 * fTempPerm59);
			fTempPerm61 = ((int((fTempPerm58 <= fTempPerm60)))?fTempPerm60:fTempPerm58);
			fTempPerm62 = tanf((fConst5 * fTempPerm61));
			fTempPerm63 = (1.0f / fTempPerm62);
			fTempPerm64 = (20 * fTempPerm7);
			fTempPerm65 = (20 * fTempPerm33);
			fTempPerm66 = (20 * fTempPerm34);
			fTempPerm67 = (10 * fTempPerm35);
			fTempPerm68 = (10 * fTempPerm42);
			fTempPerm69 = (20 * fTempPerm47);
			fTempPerm70 = (20 * fTempPerm53);
			fTempPerm71 = (((iTempPerm8)?((iTempPerm9)?((iTempPerm10)?((iTempPerm11)?((iTempPerm12)?((iTempPerm13)?((iTempPerm14)?((iTempPerm15)?((iTempPerm16)?((iTempPerm17)?((iTempPerm18)?((iTempPerm19)?((iTempPerm20)?((iTempPerm21)?((iTempPerm22)?((iTempPerm23)?((iTempPerm24)?((iTempPerm25)?((iTempPerm26)?((iTempPerm27)?((iTempPerm28)?((iTempPerm29)?((iTempPerm30)?((iTempPerm31)?80:((iTempPerm30)?(80 - fTempPerm64):60)):((iTempPerm29)?(60 - (10 * fTempPerm32)):50)):((iTempPerm28)?(fTempPerm65 + 50):70)):((iTempPerm27)?(70 - fTempPerm66):50)):((iTempPerm26)?(fTempPerm67 + 50):60)):((iTempPerm25)?(60 - (20 * fTempPerm36)):40)):((iTempPerm24)?((20 * fTempPerm37) + 40):60)):((iTempPerm23)?(60 - (20 * fTempPerm38)):40)):40):((iTempPerm21)?(40 * (fTempPerm41 + 1)):80)):((iTempPerm20)?(80 - fTempPerm68):70)):((iTempPerm19)?(70 - (30 * fTempPerm43)):40)):40):40):((iTempPerm16)?(40 * (fTempPerm46 + 1)):80)):((iTempPerm15)?(80 - fTempPerm69):60)):60):((iTempPerm13)?(60 - (20 * fTempPerm50)):40)):((iTempPerm12)?((10 * fTempPerm51) + 40):50)):50):((iTempPerm10)?(fTempPerm70 + 50):70)):((iTempPerm9)?(70 - (30 * fTempPerm54)):40)):((iTempPerm8)?((30 * fTempPerm55) + 40):70)):((iTempPerm56)?(70 - (30 * fTempPerm57)):40)) / fTempPerm61);
			fTempPerm72 = (((fTempPerm63 + fTempPerm71) / fTempPerm62) + 1);
			fRec0[0] = (fTempPerm6 - (((fRec0[2] * (((fTempPerm63 - fTempPerm71) / fTempPerm62) + 1)) + (2 * (fRec0[1] * (1 - (1.0f / faustpower<2>(fTempPerm62)))))) / fTempPerm72));
			fTempPerm73 = ((0.003666666666666667f * (400 - fTempPerm60)) + 3);
			fTempPerm74 = ((0.00084000000000000003f * (1000 - fTempPerm60)) + 0.80000000000000004f);
			fTempPerm75 = ((iSlow17)?fTempPerm73:fTempPerm74);
			fTempPerm76 = ((iTempPerm8)?((iTempPerm9)?((iTempPerm10)?((iTempPerm11)?((iTempPerm12)?((iTempPerm13)?((iTempPerm14)?((iTempPerm15)?((iTempPerm16)?((iTempPerm17)?((iTempPerm18)?((iTempPerm19)?((iTempPerm20)?((iTempPerm21)?((iTempPerm22)?((iTempPerm23)?((iTempPerm24)?((iTempPerm25)?((iTempPerm26)?((iTempPerm27)?((iTempPerm28)?((iTempPerm29)?((iTempPerm30)?((iTempPerm31)?1150:((iTempPerm30)?((450 * fTempPerm7) + 1150):1600)):((iTempPerm29)?((100 * fTempPerm32) + 1600):1700)):((iTempPerm28)?(1700 - (900 * fTempPerm33)):800)):((iTempPerm27)?(800 - (100 * fTempPerm34)):700)):((iTempPerm26)?((340 * fTempPerm35) + 700):1040)):((iTempPerm25)?((580 * fTempPerm36) + 1040):1620)):((iTempPerm24)?((130 * fTempPerm37) + 1620):1750)):((iTempPerm23)?(1750 - (1000 * fTempPerm38)):750)):((iTempPerm22)?(750 - (150 * fTempPerm39)):600)):((iTempPerm21)?((520 * fTempPerm41) + 600):1120)):((iTempPerm20)?((680 * fTempPerm42) + 1120):1800)):((iTempPerm19)?((50 * fTempPerm43) + 1800):1850)):((iTempPerm18)?(1850 - (1030 * fTempPerm44)):820)):((iTempPerm17)?(820 - (190 * fTempPerm45)):630)):((iTempPerm16)?((520 * fTempPerm46) + 630):1150)):((iTempPerm15)?((850 * fTempPerm47) + 1150):2000)):((iTempPerm14)?((140 * fTempPerm48) + 2000):2140)):((iTempPerm13)?(2140 - (1340 * fTempPerm50)):800)):((iTempPerm12)?(800 - (100 * fTempPerm51)):700)):((iTempPerm11)?((380 * fTempPerm52) + 700):1080)):((iTempPerm10)?((620 * fTempPerm53) + 1080):1700)):((iTempPerm9)?((170 * fTempPerm54) + 1700):1870)):((iTempPerm8)?(1870 - (1070 * fTempPerm55)):800)):((iTempPerm56)?(800 - (200 * fTempPerm57)):600));
			fTempPerm77 = ((fSlow19 * fTempPerm59) + 30);
			fTempPerm78 = ((iSlow18)?((int(((fTempPerm76 >= 1300) & (fTempPerm60 >= 200))))?(fTempPerm76 - (0.00095238095238095238f * ((fTempPerm60 + -200) * (fTempPerm76 + -1300)))):((int((fTempPerm76 <= fTempPerm77)))?fTempPerm77:fTempPerm76)):fTempPerm76);
			fTempPerm79 = tanf((fConst5 * fTempPerm78));
			fTempPerm80 = (1.0f / fTempPerm79);
			fTempPerm81 = (10 * fTempPerm36);
			fTempPerm82 = (10 * fTempPerm41);
			fTempPerm83 = (10 * fTempPerm53);
			fTempPerm84 = (10 * fTempPerm55);
			fTempPerm85 = (((iTempPerm8)?((iTempPerm9)?((iTempPerm10)?((iTempPerm11)?((iTempPerm12)?((iTempPerm13)?((iTempPerm14)?((iTempPerm15)?((iTempPerm16)?((iTempPerm17)?((iTempPerm18)?((iTempPerm19)?((iTempPerm20)?((iTempPerm21)?((iTempPerm22)?((iTempPerm23)?((iTempPerm24)?((iTempPerm25)?((iTempPerm26)?((iTempPerm27)?((iTempPerm28)?((iTempPerm29)?((iTempPerm30)?((iTempPerm31)?90:((iTempPerm30)?(90 - (10 * fTempPerm7)):80)):((iTempPerm29)?((20 * fTempPerm32) + 80):100)):((iTempPerm28)?(100 - fTempPerm65):80)):((iTempPerm27)?(80 - fTempPerm66):60)):((iTempPerm26)?(fTempPerm67 + 60):70)):((iTempPerm25)?(fTempPerm81 + 70):80)):((iTempPerm24)?((10 * fTempPerm37) + 80):90)):((iTempPerm23)?(90 - (10 * fTempPerm38)):80)):80):((iTempPerm21)?(fTempPerm82 + 80):90)):((iTempPerm20)?(90 - fTempPerm68):80)):((iTempPerm19)?((10 * fTempPerm43) + 80):90)):((iTempPerm18)?(90 - (10 * fTempPerm44)):80)):((iTempPerm17)?(80 - (20 * fTempPerm45)):60)):((iTempPerm16)?((30 * fTempPerm46) + 60):90)):((iTempPerm15)?((10 * fTempPerm47) + 90):100)):((iTempPerm14)?(100 - (10 * fTempPerm48)):90)):((iTempPerm13)?(90 - (10 * fTempPerm50)):80)):((iTempPerm12)?(80 - (20 * fTempPerm51)):60)):((iTempPerm11)?((30 * fTempPerm52) + 60):90)):((iTempPerm10)?(90 - fTempPerm83):80)):((iTempPerm9)?((10 * fTempPerm54) + 80):90)):((iTempPerm8)?(90 - fTempPerm84):80)):((iTempPerm56)?(80 - (20 * fTempPerm57)):60)) / fTempPerm78);
			fTempPerm86 = (((fTempPerm80 + fTempPerm85) / fTempPerm79) + 1);
			fRec12[0] = (fTempPerm6 - (((fRec12[2] * (((fTempPerm80 - fTempPerm85) / fTempPerm79) + 1)) + (2 * (fRec12[1] * (1 - (1.0f / faustpower<2>(fTempPerm79)))))) / fTempPerm86));
			fTempPerm87 = ((iTempPerm8)?((iTempPerm9)?((iTempPerm10)?((iTempPerm11)?((iTempPerm12)?((iTempPerm13)?((iTempPerm14)?((iTempPerm15)?((iTempPerm16)?((iTempPerm17)?((iTempPerm18)?((iTempPerm19)?((iTempPerm20)?((iTempPerm21)?((iTempPerm22)?((iTempPerm23)?((iTempPerm24)?((iTempPerm25)?((iTempPerm26)?((iTempPerm27)?((iTempPerm28)?((iTempPerm29)?((iTempPerm30)?((iTempPerm31)?0.63095699999999999f:((iTempPerm30)?(0.63095699999999999f - (0.56786099999999995f * fTempPerm7)):0.063095999999999999f)):((iTempPerm29)?((0.036904000000000006f * fTempPerm32) + 0.063095999999999999f):0.10000000000000001f)):((iTempPerm28)?((0.25481299999999996f * fTempPerm33) + 0.10000000000000001f):0.35481299999999999f)):((iTempPerm27)?(0.35481299999999999f - (0.10362399999999999f * fTempPerm34)):0.251189f)):((iTempPerm26)?((0.19549500000000003f * fTempPerm35) + 0.251189f):0.44668400000000003f)):((iTempPerm25)?(0.44668400000000003f - (0.19549500000000003f * fTempPerm36)):0.251189f)):((iTempPerm24)?(0.251189f - (0.21956599999999998f * fTempPerm37)):0.031622999999999998f)):((iTempPerm23)?((0.25021499999999997f * fTempPerm38) + 0.031622999999999998f):0.28183799999999998f)):((iTempPerm22)?(0.28183799999999998f - (0.18183799999999997f * fTempPerm39)):0.10000000000000001f)):((iTempPerm21)?((0.40118700000000007f * fTempPerm41) + 0.10000000000000001f):0.50118700000000005f)):((iTempPerm20)?(0.50118700000000005f - (0.30166100000000007f * fTempPerm42)):0.19952600000000001f)):((iTempPerm19)?(0.19952600000000001f - (0.13643f * fTempPerm43)):0.063095999999999999f)):((iTempPerm18)?((0.25313200000000002f * fTempPerm44) + 0.063095999999999999f):0.31622800000000001f)):((iTempPerm17)?(0.31622800000000001f - (0.216228f * fTempPerm45)):0.10000000000000001f)):((iTempPerm16)?((0.40118700000000007f * fTempPerm46) + 0.10000000000000001f):0.50118700000000005f)):((iTempPerm15)?(0.50118700000000005f - (0.40118700000000007f * fTempPerm47)):0.10000000000000001f)):((iTempPerm14)?((0.15118899999999999f * fTempPerm48) + 0.10000000000000001f):0.251189f)):((iTempPerm13)?((0.030648999999999982f * fTempPerm50) + 0.251189f):0.28183799999999998f)):((iTempPerm12)?(0.28183799999999998f - (0.12334899999999999f * fTempPerm51)):0.15848899999999999f)):((iTempPerm11)?((0.34269800000000006f * fTempPerm52) + 0.15848899999999999f):0.50118700000000005f)):((iTempPerm10)?(0.50118700000000005f - (0.30166100000000007f * fTempPerm53)):0.19952600000000001f)):((iTempPerm9)?(0.19952600000000001f - (0.021697999999999995f * fTempPerm54)):0.17782800000000001f)):((iTempPerm8)?((0.1384f * fTempPerm55) + 0.17782800000000001f):0.31622800000000001f)):((iTempPerm56)?(0.31622800000000001f - (0.216228f * fTempPerm57)):0.10000000000000001f));
			fTempPerm88 = ((iSlow17)?(fTempPerm73 * fTempPerm87):(fTempPerm74 * fTempPerm87));
			fTempPerm89 = (50 * fTempPerm42);
			fTempPerm90 = (50 * fTempPerm52);
			fTempPerm91 = (100 * fTempPerm57);
			fTempPerm92 = ((iTempPerm8)?((iTempPerm9)?((iTempPerm10)?((iTempPerm11)?((iTempPerm12)?((iTempPerm13)?((iTempPerm14)?((iTempPerm15)?((iTempPerm16)?((iTempPerm17)?((iTempPerm18)?((iTempPerm19)?((iTempPerm20)?((iTempPerm21)?((iTempPerm22)?((iTempPerm23)?((iTempPerm24)?((iTempPerm25)?((iTempPerm26)?((iTempPerm27)?((iTempPerm28)?((iTempPerm29)?((iTempPerm30)?((iTempPerm31)?2800:((iTempPerm30)?(2800 - (100 * fTempPerm7)):2700)):2700):((iTempPerm28)?((130 * fTempPerm33) + 2700):2830)):((iTempPerm27)?(2830 - (300 * fTempPerm34)):2530)):((iTempPerm26)?(2530 - (280 * fTempPerm35)):2250)):((iTempPerm25)?((150 * fTempPerm36) + 2250):2400)):((iTempPerm24)?((200 * fTempPerm37) + 2400):2600)):((iTempPerm23)?(2600 - (200 * fTempPerm38)):2400)):2400):((iTempPerm21)?((350 * fTempPerm41) + 2400):2750)):((iTempPerm20)?(2750 - fTempPerm89):2700)):((iTempPerm19)?((200 * fTempPerm43) + 2700):2900)):((iTempPerm18)?(2900 - (200 * fTempPerm44)):2700)):((iTempPerm17)?((50 * fTempPerm45) + 2700):2750)):((iTempPerm16)?((150 * fTempPerm46) + 2750):2900)):((iTempPerm15)?(2900 - (100 * fTempPerm47)):2800)):((iTempPerm14)?((150 * fTempPerm48) + 2800):2950)):((iTempPerm13)?(2950 - (120 * fTempPerm50)):2830)):((iTempPerm12)?(2830 - (130 * fTempPerm51)):2700)):((iTempPerm11)?(2700 - fTempPerm90):2650)):((iTempPerm10)?(2650 - (50 * fTempPerm53)):2600)):((iTempPerm9)?((200 * fTempPerm54) + 2600):2800)):((iTempPerm8)?(2800 - (200 * fTempPerm55)):2600)):((iTempPerm56)?(fTempPerm91 + 2600):2700));
			fTempPerm93 = tanf((fConst5 * fTempPerm92));
			fTempPerm94 = (1.0f / fTempPerm93);
			fTempPerm95 = (60 * fTempPerm35);
			fTempPerm96 = (20 * fTempPerm41);
			fTempPerm97 = (20 * fTempPerm42);
			fTempPerm98 = (20 * fTempPerm46);
			fTempPerm99 = (((iTempPerm8)?((iTempPerm9)?((iTempPerm10)?((iTempPerm11)?((iTempPerm12)?((iTempPerm13)?((iTempPerm14)?((iTempPerm15)?((iTempPerm16)?((iTempPerm17)?((iTempPerm18)?((iTempPerm19)?((iTempPerm20)?((iTempPerm21)?((iTempPerm22)?((iTempPerm23)?((iTempPerm24)?((iTempPerm25)?((iTempPerm26)?((iTempPerm27)?((iTempPerm28)?((iTempPerm29)?120:((iTempPerm28)?(120 - fTempPerm65):100)):((iTempPerm27)?((70 * fTempPerm34) + 100):170)):((iTempPerm26)?(170 - fTempPerm95):110)):((iTempPerm25)?(110 - fTempPerm81):100)):100):100):100):((iTempPerm21)?(fTempPerm96 + 100):120)):((iTempPerm20)?(120 - fTempPerm97):100)):100):100):100):((iTempPerm16)?(fTempPerm98 + 100):120)):120):((iTempPerm14)?(120 - (20 * fTempPerm48)):100)):100):((iTempPerm12)?((70 * fTempPerm51) + 100):170)):((iTempPerm11)?(170 - fTempPerm90):120)):((iTempPerm10)?(120 - fTempPerm70):100)):100):100):100) / fTempPerm92);
			fTempPerm100 = (((fTempPerm94 + fTempPerm99) / fTempPerm93) + 1);
			fRec13[0] = (fTempPerm6 - (((fRec13[2] * (((fTempPerm94 - fTempPerm99) / fTempPerm93) + 1)) + (2 * (fRec13[1] * (1 - (1.0f / faustpower<2>(fTempPerm93)))))) / fTempPerm100));
			fTempPerm101 = ((iTempPerm13)?((0.029314000000000007f * fTempPerm50) + 0.050118999999999997f):0.079433000000000004f);
			fTempPerm102 = ((iTempPerm8)?((iTempPerm9)?((iTempPerm10)?((iTempPerm11)?((iTempPerm12)?((iTempPerm13)?((iTempPerm14)?((iTempPerm15)?((iTempPerm16)?((iTempPerm17)?((iTempPerm18)?((iTempPerm19)?((iTempPerm20)?((iTempPerm21)?((iTempPerm22)?((iTempPerm23)?((iTempPerm24)?((iTempPerm25)?((iTempPerm26)?((iTempPerm27)?((iTempPerm28)?((iTempPerm29)?((iTempPerm30)?((iTempPerm31)?0.10000000000000001f:((iTempPerm30)?(0.10000000000000001f - (0.068377000000000007f * fTempPerm7)):0.031622999999999998f)):0.031622999999999998f):((iTempPerm28)?((0.12686599999999998f * fTempPerm33) + 0.031622999999999998f):0.15848899999999999f)):((iTempPerm27)?(0.15848899999999999f - (0.12686599999999998f * fTempPerm34)):0.031622999999999998f)):((iTempPerm26)?((0.32318999999999998f * fTempPerm35) + 0.031622999999999998f):0.35481299999999999f)):0.35481299999999999f):((iTempPerm24)?(0.35481299999999999f - (0.196324f * fTempPerm37)):0.15848899999999999f)):((iTempPerm23)?(0.15848899999999999f - (0.069363999999999995f * fTempPerm38)):0.089124999999999996f)):((iTempPerm22)?(0.089124999999999996f - (0.064005999999999993f * fTempPerm39)):0.025118999999999999f)):((iTempPerm21)?((0.045675999999999994f * fTempPerm41) + 0.025118999999999999f):0.070794999999999997f)):((iTempPerm20)?((0.055098000000000008f * fTempPerm42) + 0.070794999999999997f):0.125893f)):((iTempPerm19)?(0.125893f - (0.062797000000000006f * fTempPerm43)):0.063095999999999999f)):((iTempPerm18)?(0.063095999999999999f - (0.012977000000000002f * fTempPerm44)):0.050118999999999997f)):((iTempPerm17)?((0.020676f * fTempPerm45) + 0.050118999999999997f):0.070794999999999997f)):((iTempPerm16)?(0.070794999999999997f - (0.045675999999999994f * fTempPerm46)):0.025118999999999999f)):((iTempPerm15)?((0.15270900000000001f * fTempPerm47) + 0.025118999999999999f):0.17782800000000001f)):((iTempPerm14)?(0.17782800000000001f - (0.12770900000000002f * fTempPerm48)):0.050118999999999997f)):fTempPerm101):((iTempPerm12)?(0.079433000000000004f - (0.061650000000000003f * fTempPerm51)):0.017783f)):((iTempPerm11)?((0.42890100000000003f * fTempPerm52) + 0.017783f):0.44668400000000003f)):((iTempPerm10)?(0.44668400000000003f - (0.19549500000000003f * fTempPerm53)):0.251189f)):((iTempPerm9)?(0.251189f - (0.12529599999999999f * fTempPerm54)):0.125893f)):((iTempPerm8)?((0.12529599999999999f * fTempPerm55) + 0.125893f):0.251189f)):((iTempPerm56)?(0.251189f - (0.109935f * fTempPerm57)):0.14125399999999999f));
			fTempPerm103 = ((iSlow17)?(fTempPerm73 * fTempPerm102):(fTempPerm74 * fTempPerm102));
			fTempPerm104 = (350 * fTempPerm36);
			fTempPerm105 = ((iTempPerm8)?((iTempPerm9)?((iTempPerm10)?((iTempPerm11)?((iTempPerm12)?((iTempPerm13)?((iTempPerm14)?((iTempPerm15)?((iTempPerm16)?((iTempPerm17)?((iTempPerm18)?((iTempPerm19)?((iTempPerm20)?((iTempPerm21)?((iTempPerm22)?((iTempPerm23)?((iTempPerm24)?((iTempPerm25)?((iTempPerm26)?((iTempPerm27)?((iTempPerm28)?((iTempPerm29)?((iTempPerm30)?((iTempPerm31)?3500:((iTempPerm30)?(3500 - (200 * fTempPerm7)):3300)):((iTempPerm29)?((400 * fTempPerm32) + 3300):3700)):((iTempPerm28)?(3700 - (200 * fTempPerm33)):3500)):3500):((iTempPerm26)?(3500 - (1050 * fTempPerm35)):2450)):((iTempPerm25)?(fTempPerm104 + 2450):2800)):((iTempPerm24)?((250 * fTempPerm37) + 2800):3050)):((iTempPerm23)?(3050 - (450 * fTempPerm38)):2600)):((iTempPerm22)?((75 * fTempPerm39) + 2600):2675)):((iTempPerm21)?((325 * fTempPerm41) + 2675):3000)):3000):((iTempPerm19)?((350 * fTempPerm43) + 3000):3350)):((iTempPerm18)?(3350 - (350 * fTempPerm44)):3000)):3000):((iTempPerm16)?((900 * fTempPerm46) + 3000):3900)):((iTempPerm15)?(3900 - (300 * fTempPerm47)):3600)):((iTempPerm14)?((300 * fTempPerm48) + 3600):3900)):((iTempPerm13)?(3900 - (100 * fTempPerm50)):3800)):3800):((iTempPerm11)?(3800 - (900 * fTempPerm52)):2900)):((iTempPerm10)?((300 * fTempPerm53) + 2900):3200)):((iTempPerm9)?((50 * fTempPerm54) + 3200):3250)):((iTempPerm8)?(3250 - (450 * fTempPerm55)):2800)):((iTempPerm56)?(fTempPerm91 + 2800):2900));
			fTempPerm106 = tanf((fConst5 * fTempPerm105));
			fTempPerm107 = (1.0f / fTempPerm106);
			fTempPerm108 = (((iTempPerm8)?((iTempPerm9)?((iTempPerm10)?((iTempPerm11)?((iTempPerm12)?((iTempPerm13)?((iTempPerm14)?((iTempPerm15)?((iTempPerm16)?((iTempPerm17)?((iTempPerm18)?((iTempPerm19)?((iTempPerm20)?((iTempPerm21)?((iTempPerm22)?((iTempPerm23)?((iTempPerm24)?((iTempPerm25)?((iTempPerm26)?((iTempPerm27)?((iTempPerm28)?((iTempPerm29)?((iTempPerm30)?((iTempPerm31)?130:((iTempPerm30)?(fTempPerm64 + 130):150)):150):((iTempPerm28)?(150 - fTempPerm65):130)):((iTempPerm27)?((50 * fTempPerm34) + 130):180)):((iTempPerm26)?(180 - fTempPerm95):120)):120):120):120):120):((iTempPerm21)?(fTempPerm82 + 120):130)):((iTempPerm20)?(130 - fTempPerm68):120)):120):120):120):((iTempPerm16)?((10 * fTempPerm46) + 120):130)):((iTempPerm15)?(fTempPerm69 + 130):150)):((iTempPerm14)?(150 - (30 * fTempPerm48)):120)):120):((iTempPerm12)?((60 * fTempPerm51) + 120):180)):((iTempPerm11)?(180 - fTempPerm90):130)):((iTempPerm10)?(130 - fTempPerm83):120)):120):((iTempPerm8)?(fTempPerm84 + 120):130)):((iTempPerm56)?(130 - (10 * fTempPerm57)):120)) / fTempPerm105);
			fTempPerm109 = (((fTempPerm107 + fTempPerm108) / fTempPerm106) + 1);
			fRec14[0] = (fTempPerm6 - (((fRec14[2] * (((fTempPerm107 - fTempPerm108) / fTempPerm106) + 1)) + (2 * (fRec14[1] * (1 - (1.0f / faustpower<2>(fTempPerm106)))))) / fTempPerm109));
			fTempPerm110 = ((iTempPerm19)?(0.10000000000000001f - (0.084151000000000004f * fTempPerm43)):0.015848999999999999f);
			fTempPerm111 = ((iTempPerm8)?((iTempPerm9)?((iTempPerm10)?((iTempPerm11)?((iTempPerm12)?((iTempPerm13)?((iTempPerm14)?((iTempPerm15)?((iTempPerm16)?((iTempPerm17)?((iTempPerm18)?((iTempPerm19)?((iTempPerm20)?((iTempPerm21)?((iTempPerm22)?((iTempPerm23)?((iTempPerm24)?((iTempPerm25)?((iTempPerm26)?((iTempPerm27)?((iTempPerm28)?((iTempPerm29)?((iTempPerm30)?((iTempPerm31)?0.015848999999999999f:((iTempPerm30)?((0.0019340000000000017f * fTempPerm7) + 0.015848999999999999f):0.017783f)):((iTempPerm29)?(0.017783f - (0.0019340000000000017f * fTempPerm32)):0.015848999999999999f)):((iTempPerm28)?((0.023962000000000001f * fTempPerm33) + 0.015848999999999999f):0.039810999999999999f)):((iTempPerm27)?(0.039810999999999999f - (0.029810999999999997f * fTempPerm34)):0.01f)):((iTempPerm26)?((0.34481299999999998f * fTempPerm35) + 0.01f):0.35481299999999999f)):((iTempPerm25)?(0.35481299999999999f - (0.10362399999999999f * fTempPerm36)):0.251189f)):((iTempPerm24)?(0.251189f - (0.17175599999999999f * fTempPerm37)):0.079433000000000004f)):((iTempPerm23)?((0.020567000000000002f * fTempPerm38) + 0.079433000000000004f):0.10000000000000001f)):((iTempPerm22)?(0.10000000000000001f - (0.060189000000000006f * fTempPerm39)):0.039810999999999999f)):((iTempPerm21)?((0.023285f * fTempPerm41) + 0.039810999999999999f):0.063095999999999999f)):((iTempPerm20)?((0.036904000000000006f * fTempPerm42) + 0.063095999999999999f):0.10000000000000001f)):fTempPerm110):((iTempPerm18)?((0.063584000000000002f * fTempPerm44) + 0.015848999999999999f):0.079433000000000004f)):((iTempPerm17)?(0.079433000000000004f - (0.047810000000000005f * fTempPerm45)):0.031622999999999998f)):((iTempPerm16)?((0.068377000000000007f * fTempPerm46) + 0.031622999999999998f):0.10000000000000001f)):((iTempPerm15)?(0.10000000000000001f - (0.090000000000000011f * fTempPerm47)):0.01f)):((iTempPerm14)?((0.040118999999999995f * fTempPerm48) + 0.01f):0.050118999999999997f)):fTempPerm101):((iTempPerm12)?(0.079433000000000004f - (0.069433000000000009f * fTempPerm51)):0.01f)):((iTempPerm11)?((0.38810699999999998f * fTempPerm52) + 0.01f):0.39810699999999999f)):((iTempPerm10)?(0.39810699999999999f - (0.19858099999999998f * fTempPerm53)):0.19952600000000001f)):((iTempPerm9)?(0.19952600000000001f - (0.099526000000000003f * fTempPerm54)):0.10000000000000001f)):((iTempPerm8)?((0.15118899999999999f * fTempPerm55) + 0.10000000000000001f):0.251189f)):((iTempPerm56)?(0.251189f - (0.051662999999999987f * fTempPerm57)):0.19952600000000001f));
			fTempPerm112 = ((iSlow17)?(fTempPerm73 * fTempPerm111):(fTempPerm74 * fTempPerm111));
			fTempPerm113 = ((iTempPerm8)?((iTempPerm9)?((iTempPerm10)?((iTempPerm11)?((iTempPerm12)?((iTempPerm13)?((iTempPerm14)?((iTempPerm15)?((iTempPerm16)?((iTempPerm17)?((iTempPerm18)?((iTempPerm19)?((iTempPerm20)?((iTempPerm21)?((iTempPerm22)?((iTempPerm23)?((iTempPerm24)?((iTempPerm25)?((iTempPerm26)?((iTempPerm27)?4950:((iTempPerm26)?(4950 - (2200 * fTempPerm35)):2750)):((iTempPerm25)?(fTempPerm104 + 2750):3100)):((iTempPerm24)?((240 * fTempPerm37) + 3100):3340)):((iTempPerm23)?(3340 - (440 * fTempPerm38)):2900)):((iTempPerm22)?(fTempPerm40 + 2900):2950)):((iTempPerm21)?((400 * fTempPerm41) + 2950):3350)):((iTempPerm20)?(3350 - fTempPerm89):3300)):((iTempPerm19)?((290 * fTempPerm43) + 3300):3590)):((iTempPerm18)?(3590 - (290 * fTempPerm44)):3300)):((iTempPerm17)?((100 * fTempPerm45) + 3300):3400)):((iTempPerm16)?((1550 * fTempPerm46) + 3400):4950)):4950):4950):4950):4950):((iTempPerm11)?(4950 - (1700 * fTempPerm52)):3250)):((iTempPerm10)?((330 * fTempPerm53) + 3250):3580)):((iTempPerm9)?(3580 - (40 * fTempPerm54)):3540)):((iTempPerm8)?(3540 - (540 * fTempPerm55)):3000)):((iTempPerm56)?((300 * fTempPerm57) + 3000):3300));
			fTempPerm114 = tanf((fConst5 * fTempPerm113));
			fTempPerm115 = (1.0f / fTempPerm114);
			fTempPerm116 = (((iTempPerm8)?((iTempPerm9)?((iTempPerm10)?((iTempPerm11)?((iTempPerm12)?((iTempPerm13)?((iTempPerm14)?((iTempPerm15)?((iTempPerm16)?((iTempPerm17)?((iTempPerm18)?((iTempPerm19)?((iTempPerm20)?((iTempPerm21)?((iTempPerm22)?((iTempPerm23)?((iTempPerm24)?((iTempPerm25)?((iTempPerm26)?((iTempPerm27)?((iTempPerm28)?((iTempPerm29)?((iTempPerm30)?((iTempPerm31)?140:((iTempPerm30)?((60 * fTempPerm7) + 140):200)):200):((iTempPerm28)?(200 - (65 * fTempPerm33)):135)):((iTempPerm27)?((65 * fTempPerm34) + 135):200)):((iTempPerm26)?(200 - (70 * fTempPerm35)):130)):((iTempPerm25)?(130 - fTempPerm81):120)):120):120):120):((iTempPerm21)?(fTempPerm96 + 120):140)):((iTempPerm20)?(140 - fTempPerm97):120)):120):120):120):((iTempPerm16)?(fTempPerm98 + 120):140)):((iTempPerm15)?((60 * fTempPerm47) + 140):200)):((iTempPerm14)?(200 - fTempPerm49):120)):120):((iTempPerm12)?((80 * fTempPerm51) + 120):200)):((iTempPerm11)?(200 - (60 * fTempPerm52)):140)):((iTempPerm10)?(140 - fTempPerm70):120)):120):((iTempPerm8)?((15 * fTempPerm55) + 120):135)):((iTempPerm56)?(135 - (15 * fTempPerm57)):120)) / fTempPerm113);
			fTempPerm117 = (((fTempPerm115 + fTempPerm116) / fTempPerm114) + 1);
			fRec15[0] = (fTempPerm6 - (((fRec15[2] * (((fTempPerm115 - fTempPerm116) / fTempPerm114) + 1)) + (2 * (fRec15[1] * (1 - (1.0f / faustpower<2>(fTempPerm114)))))) / fTempPerm117));
			fTempPerm118 = ((iTempPerm8)?((iTempPerm9)?((iTempPerm10)?((iTempPerm11)?((iTempPerm12)?((iTempPerm13)?((iTempPerm14)?((iTempPerm15)?((iTempPerm16)?((iTempPerm17)?((iTempPerm18)?((iTempPerm19)?((iTempPerm20)?((iTempPerm21)?((iTempPerm22)?((iTempPerm23)?((iTempPerm24)?((iTempPerm25)?((iTempPerm26)?((iTempPerm27)?((iTempPerm28)?((iTempPerm29)?0.001f:((iTempPerm28)?((0.00077800000000000005f * fTempPerm33) + 0.001f):0.0017780000000000001f)):((iTempPerm27)?(0.0017780000000000001f - (0.001147f * fTempPerm34)):0.00063100000000000005f)):((iTempPerm26)?((0.099368999999999999f * fTempPerm35) + 0.00063100000000000005f):0.10000000000000001f)):((iTempPerm25)?((0.025892999999999999f * fTempPerm36) + 0.10000000000000001f):0.125893f)):((iTempPerm24)?(0.125893f - (0.086082000000000006f * fTempPerm37)):0.039810999999999999f)):((iTempPerm23)?(0.039810999999999999f - (0.029810999999999997f * fTempPerm38)):0.01f)):((iTempPerm22)?((0.0058489999999999983f * fTempPerm39) + 0.01f):0.015848999999999999f)):((iTempPerm21)?(0.015848999999999999f - (0.003259999999999999f * fTempPerm41)):0.012588999999999999f)):((iTempPerm20)?((0.087411000000000003f * fTempPerm42) + 0.012588999999999999f):0.10000000000000001f)):fTempPerm110):((iTempPerm18)?((0.004104f * fTempPerm44) + 0.015848999999999999f):0.019952999999999999f)):0.019952999999999999f):((iTempPerm16)?(0.019952999999999999f - (0.016791f * fTempPerm46)):0.0031619999999999999f)):((iTempPerm15)?(0.0031619999999999999f - (0.0015769999999999998f * fTempPerm47)):0.001585f)):((iTempPerm14)?((0.004725f * fTempPerm48) + 0.001585f):0.0063099999999999996f)):((iTempPerm13)?(0.0063099999999999996f - (0.0031479999999999998f * fTempPerm50)):0.0031619999999999999f)):((iTempPerm12)?(0.0031619999999999999f - (0.0021619999999999999f * fTempPerm51)):0.001f)):((iTempPerm11)?((0.078433000000000003f * fTempPerm52) + 0.001f):0.079433000000000004f)):((iTempPerm10)?((0.020567000000000002f * fTempPerm53) + 0.079433000000000004f):0.10000000000000001f)):((iTempPerm9)?(0.10000000000000001f - (0.068377000000000007f * fTempPerm54)):0.031622999999999998f)):((iTempPerm8)?((0.018495999999999999f * fTempPerm55) + 0.031622999999999998f):0.050118999999999997f)):0.050118999999999997f);
			fTempPerm119 = ((iSlow17)?(fTempPerm73 * fTempPerm118):(fTempPerm74 * fTempPerm118));
			fTempPerm120 = (fSlow0 * (((((((fRec0[2] * (0 - (fTempPerm75 / fTempPerm62))) + ((fRec0[0] * fTempPerm75) / fTempPerm62)) / fTempPerm72) + (((fRec12[2] * (0 - (fTempPerm88 / fTempPerm79))) + ((fRec12[0] * fTempPerm88) / fTempPerm79)) / fTempPerm86)) + (((fRec13[2] * (0 - (fTempPerm103 / fTempPerm93))) + ((fRec13[0] * fTempPerm103) / fTempPerm93)) / fTempPerm100)) + (((fRec14[2] * (0 - (fTempPerm112 / fTempPerm106))) + ((fRec14[0] * fTempPerm112) / fTempPerm106)) / fTempPerm109)) + (((fRec15[2] * (0 - (fTempPerm119 / fTempPerm114))) + ((fRec15[0] * fTempPerm119) / fTempPerm114)) / fTempPerm117)));
			output0[i] = (FAUSTFLOAT)fTempPerm120;
			output1[i] = (FAUSTFLOAT)fTempPerm120;
			// post processing
			fRec15[2] = fRec15[1]; fRec15[1] = fRec15[0];
			fRec14[2] = fRec14[1]; fRec14[1] = fRec14[0];
			fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
			fRec12[2] = fRec12[1]; fRec12[1] = fRec12[0];
			fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
			fRec11[1] = fRec11[0];
			fRec10[1] = fRec10[0];
			fRec9[1] = fRec9[0];
			iRec8[1] = iRec8[0];
			fRec3[1] = fRec3[0];
			fRec7[1] = fRec7[0];
			fRec6[1] = fRec6[0];
			fRec5[1] = fRec5[0];
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
			fVec1[1] = fVec1[0];
			iVec0[1] = iVec0[0];
		}
	}
};


