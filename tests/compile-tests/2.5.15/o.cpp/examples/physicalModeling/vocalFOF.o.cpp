//----------------------------------------------------------
// copyright: "(c)Mike Olsen, CCRMA (Stanford University)"
// license: "MIT"
// name: "Vocal FOF"
//
// Code generated with Faust 2.5.15 (https://faust.grame.fr)
//----------------------------------------------------------

/* link with  */
#include <math.h>

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
	class SIG0 {
	  private:
		int fSamplingFreq;
		int 	iRec9[2];
		float 	fTempPerm73;
	  public:
		int getNumInputs() { return 0; }
		int getNumOutputs() { return 1; }
		void init(int samplingFreq) {
			fSamplingFreq = samplingFreq;
			fTempPerm73 = 0;
			for (int i=0; i<2; i++) iRec9[i] = 0;
		}
		void fill (int count, float output[]) {
			for (int i=0; i<count; i++) {
				iRec9[0] = (iRec9[1] + 1);
				fTempPerm73 = sinf((9.5873799242852573e-05f * float((iRec9[0] + -1))));
				output[i] = fTempPerm73;
				// post processing
				iRec9[1] = iRec9[0];
			}
		}
	};


	FAUSTFLOAT 	fslider0;
	int 	iVec0[2];
	float 	fConst0;
	float 	fConst1;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	float 	fConst2;
	FAUSTFLOAT 	fslider3;
	float 	fRec2[2];
	int 	iTempPerm0;
	float 	fRec3[2];
	float 	fTempPerm1;
	float 	fTempPerm2;
	float 	fVec1[2];
	float 	fTempPerm3;
	float 	fRec1[2];
	int 	iTempPerm4;
	int 	iVec2[2];
	float 	fConst3;
	float 	fConst4;
	float 	fConst5;
	FAUSTFLOAT 	fslider4;
	float 	fRec5[2];
	FAUSTFLOAT 	fslider5;
	float 	fTempPerm5;
	int 	iTempPerm6;
	int 	iTempPerm7;
	int 	iTempPerm8;
	int 	iTempPerm9;
	int 	iTempPerm10;
	int 	iTempPerm11;
	int 	iTempPerm12;
	int 	iTempPerm13;
	float 	fTempPerm14;
	float 	fRec6[2];
	float 	fRec7[2];
	float 	fTempPerm15;
	float 	fTempPerm16;
	float 	fTempPerm17;
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
	int 	iTempPerm32;
	int 	iTempPerm33;
	int 	iTempPerm34;
	int 	iTempPerm35;
	int 	iTempPerm36;
	int 	iTempPerm37;
	int 	iTempPerm38;
	int 	iTempPerm39;
	int 	iTempPerm40;
	int 	iTempPerm41;
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
	float 	fTempPerm56;
	float 	fTempPerm57;
	float 	fTempPerm58;
	float 	fTempPerm59;
	float 	fTempPerm60;
	float 	fTempPerm61;
	float 	fTempPerm62;
	float 	fTempPerm63;
	float 	fTempPerm64;
	float 	fTempPerm65;
	int 	iTempPerm66;
	float 	fTempPerm67;
	float 	fTempPerm68;
	float 	fRec4[2];
	float 	fTempPerm69;
	float 	fRec8[2];
	float 	fTempPerm70;
	float 	fRec0[3];
	float 	fTempPerm71;
	float 	fTempPerm72;
	static float 	ftbl0[65536];
	int 	iTempPerm74;
	float 	fConst6;
	float 	fRec11[2];
	float 	fTempPerm75;
	int 	iTempPerm76;
	int 	iTempPerm77;
	int 	iTempPerm78;
	int 	iTempPerm79;
	int 	iTempPerm80;
	int 	iTempPerm81;
	int 	iTempPerm82;
	int 	iTempPerm83;
	int 	iTempPerm84;
	int 	iTempPerm85;
	int 	iTempPerm86;
	int 	iTempPerm87;
	int 	iTempPerm88;
	int 	iTempPerm89;
	int 	iTempPerm90;
	int 	iTempPerm91;
	int 	iTempPerm92;
	int 	iTempPerm93;
	int 	iTempPerm94;
	int 	iTempPerm95;
	int 	iTempPerm96;
	int 	iTempPerm97;
	int 	iTempPerm98;
	int 	iTempPerm99;
	float 	fTempPerm100;
	float 	fTempPerm101;
	float 	fTempPerm102;
	float 	fTempPerm103;
	float 	fTempPerm104;
	float 	fTempPerm105;
	float 	fTempPerm106;
	float 	fTempPerm107;
	float 	fTempPerm108;
	float 	fTempPerm109;
	float 	fTempPerm110;
	float 	fTempPerm111;
	float 	fTempPerm112;
	float 	fTempPerm113;
	float 	fTempPerm114;
	float 	fTempPerm115;
	float 	fTempPerm116;
	float 	fTempPerm117;
	float 	fTempPerm118;
	float 	fTempPerm119;
	float 	fTempPerm120;
	float 	fTempPerm121;
	float 	fTempPerm122;
	int 	iTempPerm123;
	float 	fTempPerm124;
	float 	fTempPerm125;
	float 	fTempPerm126;
	float 	fRec10[2];
	float 	fTempPerm127;
	float 	fTempPerm128;
	float 	fTempPerm129;
	float 	fTempPerm130;
	float 	fTempPerm131;
	float 	fTempPerm132;
	float 	fTempPerm133;
	float 	fTempPerm134;
	float 	fTempPerm135;
	float 	fRec13[2];
	float 	fTempPerm136;
	float 	fRec14[2];
	float 	fTempPerm137;
	float 	fRec12[3];
	float 	fTempPerm138;
	float 	fTempPerm139;
	float 	fTempPerm140;
	float 	fTempPerm141;
	float 	fTempPerm142;
	float 	fRec15[2];
	float 	fTempPerm143;
	float 	fTempPerm144;
	float 	fTempPerm145;
	float 	fTempPerm146;
	float 	fTempPerm147;
	float 	fTempPerm148;
	float 	fRec17[2];
	float 	fTempPerm149;
	float 	fRec18[2];
	float 	fTempPerm150;
	float 	fRec16[3];
	float 	fTempPerm151;
	float 	fTempPerm152;
	float 	fTempPerm153;
	float 	fTempPerm154;
	float 	fTempPerm155;
	float 	fRec19[2];
	float 	fTempPerm156;
	float 	fRec21[2];
	float 	fTempPerm157;
	float 	fRec22[2];
	float 	fTempPerm158;
	float 	fRec20[3];
	float 	fTempPerm159;
	float 	fTempPerm160;
	float 	fTempPerm161;
	float 	fTempPerm162;
	float 	fRec23[2];
	float 	fTempPerm163;
	float 	fRec25[2];
	float 	fTempPerm164;
	float 	fRec26[2];
	float 	fTempPerm165;
	float 	fRec24[3];
	float 	fTempPerm166;
	float 	fTempPerm167;
	float 	fRec27[2];
	float 	fTempPerm168;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("copyright", "(c)Mike Olsen, CCRMA (Stanford University)");
		m->declare("description", "FOF vocal synthesizer.");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("license", "MIT");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "Vocal FOF");
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
		SIG0 sig0;
		sig0.init(samplingFreq);
		sig0.fill(65536,ftbl0);
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(192000.0f, max(1.0f, (float)fSamplingFreq));
		fConst1 = (1.0f / fConst0);
		fConst2 = (6.2831853071795862f / fConst0);
		iTempPerm0 = 0;
		fTempPerm1 = 0;
		fTempPerm2 = 0;
		fTempPerm3 = 0;
		iTempPerm4 = 0;
		fConst3 = (3.1415926535897931f / fConst0);
		fConst4 = expf((0 - (1000.0f / fConst0)));
		fConst5 = (1.0f - fConst4);
		fTempPerm5 = 0;
		iTempPerm6 = 0;
		iTempPerm7 = 0;
		iTempPerm8 = 0;
		iTempPerm9 = 0;
		iTempPerm10 = 0;
		iTempPerm11 = 0;
		iTempPerm12 = 0;
		iTempPerm13 = 0;
		fTempPerm14 = 0;
		fTempPerm15 = 0;
		fTempPerm16 = 0;
		fTempPerm17 = 0;
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
		iTempPerm32 = 0;
		iTempPerm33 = 0;
		iTempPerm34 = 0;
		iTempPerm35 = 0;
		iTempPerm36 = 0;
		iTempPerm37 = 0;
		iTempPerm38 = 0;
		iTempPerm39 = 0;
		iTempPerm40 = 0;
		iTempPerm41 = 0;
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
		fTempPerm56 = 0;
		fTempPerm57 = 0;
		fTempPerm58 = 0;
		fTempPerm59 = 0;
		fTempPerm60 = 0;
		fTempPerm61 = 0;
		fTempPerm62 = 0;
		fTempPerm63 = 0;
		fTempPerm64 = 0;
		fTempPerm65 = 0;
		iTempPerm66 = 0;
		fTempPerm67 = 0;
		fTempPerm68 = 0;
		fTempPerm69 = 0;
		fTempPerm70 = 0;
		fTempPerm71 = 0;
		fTempPerm72 = 0;
		iTempPerm74 = 0;
		fConst6 = (1.0f / float(fConst0));
		fTempPerm75 = 0;
		iTempPerm76 = 0;
		iTempPerm77 = 0;
		iTempPerm78 = 0;
		iTempPerm79 = 0;
		iTempPerm80 = 0;
		iTempPerm81 = 0;
		iTempPerm82 = 0;
		iTempPerm83 = 0;
		iTempPerm84 = 0;
		iTempPerm85 = 0;
		iTempPerm86 = 0;
		iTempPerm87 = 0;
		iTempPerm88 = 0;
		iTempPerm89 = 0;
		iTempPerm90 = 0;
		iTempPerm91 = 0;
		iTempPerm92 = 0;
		iTempPerm93 = 0;
		iTempPerm94 = 0;
		iTempPerm95 = 0;
		iTempPerm96 = 0;
		iTempPerm97 = 0;
		iTempPerm98 = 0;
		iTempPerm99 = 0;
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
		fTempPerm121 = 0;
		fTempPerm122 = 0;
		iTempPerm123 = 0;
		fTempPerm124 = 0;
		fTempPerm125 = 0;
		fTempPerm126 = 0;
		fTempPerm127 = 0;
		fTempPerm128 = 0;
		fTempPerm129 = 0;
		fTempPerm130 = 0;
		fTempPerm131 = 0;
		fTempPerm132 = 0;
		fTempPerm133 = 0;
		fTempPerm134 = 0;
		fTempPerm135 = 0;
		fTempPerm136 = 0;
		fTempPerm137 = 0;
		fTempPerm138 = 0;
		fTempPerm139 = 0;
		fTempPerm140 = 0;
		fTempPerm141 = 0;
		fTempPerm142 = 0;
		fTempPerm143 = 0;
		fTempPerm144 = 0;
		fTempPerm145 = 0;
		fTempPerm146 = 0;
		fTempPerm147 = 0;
		fTempPerm148 = 0;
		fTempPerm149 = 0;
		fTempPerm150 = 0;
		fTempPerm151 = 0;
		fTempPerm152 = 0;
		fTempPerm153 = 0;
		fTempPerm154 = 0;
		fTempPerm155 = 0;
		fTempPerm156 = 0;
		fTempPerm157 = 0;
		fTempPerm158 = 0;
		fTempPerm159 = 0;
		fTempPerm160 = 0;
		fTempPerm161 = 0;
		fTempPerm162 = 0;
		fTempPerm163 = 0;
		fTempPerm164 = 0;
		fTempPerm165 = 0;
		fTempPerm166 = 0;
		fTempPerm167 = 0;
		fTempPerm168 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.90000000000000002f;
		fslider1 = 440.0f;
		fslider2 = 0.5f;
		fslider3 = 6.0f;
		fslider4 = 0.0f;
		fslider5 = 0.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) iVec0[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) iVec2[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<2; i++) fRec7[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2; i++) fRec8[i] = 0;
		for (int i=0; i<3; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fRec11[i] = 0;
		for (int i=0; i<2; i++) fRec10[i] = 0;
		for (int i=0; i<2; i++) fRec13[i] = 0;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		for (int i=0; i<3; i++) fRec12[i] = 0;
		for (int i=0; i<2; i++) fRec15[i] = 0;
		for (int i=0; i<2; i++) fRec17[i] = 0;
		for (int i=0; i<2; i++) fRec18[i] = 0;
		for (int i=0; i<3; i++) fRec16[i] = 0;
		for (int i=0; i<2; i++) fRec19[i] = 0;
		for (int i=0; i<2; i++) fRec21[i] = 0;
		for (int i=0; i<2; i++) fRec22[i] = 0;
		for (int i=0; i<3; i++) fRec20[i] = 0;
		for (int i=0; i<2; i++) fRec23[i] = 0;
		for (int i=0; i<2; i++) fRec25[i] = 0;
		for (int i=0; i<2; i++) fRec26[i] = 0;
		for (int i=0; i<3; i++) fRec24[i] = 0;
		for (int i=0; i<2; i++) fRec27[i] = 0;
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
		ui_interface->declare(&fslider1, "0", "");
		ui_interface->addHorizontalSlider("freq", &fslider1, 440.0f, 50.0f, 1000.0f, 0.01f);
		ui_interface->declare(&fslider0, "1", "");
		ui_interface->addHorizontalSlider("gain", &fslider0, 0.90000000000000002f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider5, "2", "");
		ui_interface->addHorizontalSlider("voiceType", &fslider5, 0.0f, 0.0f, 4.0f, 1.0f);
		ui_interface->declare(&fslider4, "3", "");
		ui_interface->addHorizontalSlider("vowel", &fslider4, 0.0f, 0.0f, 4.0f, 0.01f);
		ui_interface->declare(&fslider3, "5", "");
		ui_interface->addHorizontalSlider("vibratoFreq", &fslider3, 6.0f, 1.0f, 10.0f, 0.01f);
		ui_interface->declare(&fslider2, "6", "");
		ui_interface->addHorizontalSlider("vibratoGain", &fslider2, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = (25.0f * float(fslider0));
		float 	fSlow1 = float(fslider1);
		float 	fSlow2 = (0.10000000000000001f * float(fslider2));
		float 	fSlow3 = (fConst2 * float(fslider3));
		float 	fSlow4 = sinf(fSlow3);
		float 	fSlow5 = cosf(fSlow3);
		float 	fSlow6 = (0 - fSlow4);
		float 	fSlow7 = (0.0010000000000000009f * float(fslider4));
		float 	fSlow8 = float(fslider5);
		int 	iSlow9 = ((int((fSlow8 == 0)))?1:((int((fSlow8 == 3)))?1:0));
		int 	iSlow10 = (5 * iSlow9);
		int 	iSlow11 = int((iSlow9 >= 1));
		float 	fSlow12 = ((iSlow11)?174.61000000000001f:82.409999999999997f);
		float 	fSlow13 = ((iSlow11)?1046.5f:523.25f);
		float 	fSlow14 = (fSlow13 - fSlow12);
		float 	fSlow15 = (5 * fSlow8);
		float 	fSlow16 = (5 * (1 - fSlow8));
		int 	iSlow17 = int((iSlow9 == 0));
		int 	iSlow18 = int((fSlow8 != 2));
		float 	fSlow19 = (2 * fSlow1);
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			iVec0[0] = 1;
			fRec2[0] = ((fSlow4 * fRec3[1]) + (fSlow5 * fRec2[1]));
			iTempPerm0 = (1 - iVec0[1]);
			fRec3[0] = (((fSlow5 * fRec3[1]) + (fSlow6 * fRec2[1])) + iTempPerm0);
			fTempPerm1 = ((fSlow2 * fRec2[0]) + 1);
			fTempPerm2 = (fSlow1 * fTempPerm1);
			fVec1[0] = fTempPerm2;
			fTempPerm3 = (fRec1[1] + (fConst1 * fVec1[1]));
			fRec1[0] = (fTempPerm3 - floorf(fTempPerm3));
			iTempPerm4 = ((fRec1[0] - fRec1[1]) < 0);
			iVec2[0] = iTempPerm4;
			fRec5[0] = (fSlow7 + (0.999f * fRec5[1]));
			fTempPerm5 = (fRec5[0] + iSlow10);
			iTempPerm6 = int((fTempPerm5 >= 5));
			iTempPerm7 = int((fTempPerm5 >= 8));
			iTempPerm8 = int((fTempPerm5 >= 7));
			iTempPerm9 = int((fTempPerm5 >= 6));
			iTempPerm10 = int((fTempPerm5 >= 3));
			iTempPerm11 = int((fTempPerm5 >= 4));
			iTempPerm12 = int((fTempPerm5 >= 2));
			iTempPerm13 = int((fTempPerm5 >= 1));
			fTempPerm14 = ((iTempPerm6)?((iTempPerm7)?2.0f:((iTempPerm8)?3.0f:((iTempPerm9)?3.0f:2.0f))):((iTempPerm10)?((iTempPerm11)?1.5f:1.0f):((iTempPerm12)?1.25f:((iTempPerm13)?1.25f:1.0f))));
			fRec6[0] = ((fSlow4 * fRec7[1]) + (fSlow5 * fRec6[1]));
			fRec7[0] = (((fSlow5 * fRec7[1]) + (fSlow6 * fRec6[1])) + iTempPerm0);
			fTempPerm15 = (fSlow1 * ((fSlow2 * fRec6[0]) + 1));
			fTempPerm16 = (fTempPerm14 + ((((iTempPerm6)?((iTempPerm7)?12.0f:((iTempPerm8)?12.0f:((iTempPerm9)?12.0f:15.0f))):((iTempPerm10)?((iTempPerm11)?4.0f:10.0f):((iTempPerm12)?2.5f:((iTempPerm13)?2.5f:10.0f)))) - fTempPerm14) * ((int((fTempPerm15 <= fSlow12)))?0.0f:((int((fTempPerm15 >= fSlow13)))?1.0f:((fTempPerm15 - fSlow12) / fSlow14)))));
			fTempPerm17 = (fSlow15 + fRec5[0]);
			iTempPerm18 = int((fTempPerm17 < 23));
			iTempPerm19 = int((fTempPerm17 < 22));
			iTempPerm20 = int((fTempPerm17 < 21));
			iTempPerm21 = int((fTempPerm17 < 20));
			iTempPerm22 = int((fTempPerm17 < 19));
			iTempPerm23 = int((fTempPerm17 < 18));
			iTempPerm24 = int((fTempPerm17 < 17));
			iTempPerm25 = int((fTempPerm17 < 16));
			iTempPerm26 = int((fTempPerm17 < 15));
			iTempPerm27 = int((fTempPerm17 < 14));
			iTempPerm28 = int((fTempPerm17 < 13));
			iTempPerm29 = int((fTempPerm17 < 12));
			iTempPerm30 = int((fTempPerm17 < 11));
			iTempPerm31 = int((fTempPerm17 < 10));
			iTempPerm32 = int((fTempPerm17 < 9));
			iTempPerm33 = int((fTempPerm17 < 8));
			iTempPerm34 = int((fTempPerm17 < 7));
			iTempPerm35 = int((fTempPerm17 < 6));
			iTempPerm36 = int((fTempPerm17 < 5));
			iTempPerm37 = int((fTempPerm17 < 4));
			iTempPerm38 = int((fTempPerm17 < 3));
			iTempPerm39 = int((fTempPerm17 < 2));
			iTempPerm40 = int((fTempPerm17 < 1));
			iTempPerm41 = int((fTempPerm17 < 0));
			fTempPerm42 = (20 * fTempPerm17);
			fTempPerm43 = (fSlow15 + (fRec5[0] + -1));
			fTempPerm44 = (fSlow15 + (fRec5[0] + -2));
			fTempPerm45 = (20 * fTempPerm44);
			fTempPerm46 = (fSlow15 + (fRec5[0] + -3));
			fTempPerm47 = (20 * fTempPerm46);
			fTempPerm48 = (fSlow15 + (fRec5[0] + -4));
			fTempPerm49 = (10 * fTempPerm48);
			fTempPerm50 = (fRec5[0] - fSlow16);
			fTempPerm51 = (fSlow15 + (fRec5[0] + -6));
			fTempPerm52 = (fSlow15 + (fRec5[0] + -7));
			fTempPerm53 = (fSlow15 + (fRec5[0] + -9));
			fTempPerm54 = (fSlow15 + (fRec5[0] + -10));
			fTempPerm55 = (10 * fTempPerm54);
			fTempPerm56 = (fSlow15 + (fRec5[0] + -11));
			fTempPerm57 = (fSlow15 + (fRec5[0] + -14));
			fTempPerm58 = (fSlow15 + (fRec5[0] + -15));
			fTempPerm59 = (20 * fTempPerm58);
			fTempPerm60 = (fSlow15 + (fRec5[0] + -17));
			fTempPerm61 = (fSlow15 + (fRec5[0] + -18));
			fTempPerm62 = (fSlow15 + (fRec5[0] + -20));
			fTempPerm63 = (20 * fTempPerm62);
			fTempPerm64 = (fSlow15 + (fRec5[0] + -21));
			fTempPerm65 = (fSlow15 + (fRec5[0] + -22));
			iTempPerm66 = int((fTempPerm17 < 24));
			fTempPerm67 = (fSlow15 + (fRec5[0] + -23));
			fTempPerm68 = ((iTempPerm18)?((iTempPerm19)?((iTempPerm20)?((iTempPerm21)?((iTempPerm22)?((iTempPerm23)?((iTempPerm24)?((iTempPerm25)?((iTempPerm26)?((iTempPerm27)?((iTempPerm28)?((iTempPerm29)?((iTempPerm30)?((iTempPerm31)?((iTempPerm32)?((iTempPerm33)?((iTempPerm34)?((iTempPerm35)?((iTempPerm36)?((iTempPerm37)?((iTempPerm38)?((iTempPerm39)?((iTempPerm40)?((iTempPerm41)?80:((iTempPerm40)?(80 - fTempPerm42):60)):((iTempPerm39)?(60 - (10 * fTempPerm43)):50)):((iTempPerm38)?(fTempPerm45 + 50):70)):((iTempPerm37)?(70 - fTempPerm47):50)):((iTempPerm36)?(fTempPerm49 + 50):60)):((iTempPerm35)?(60 - (20 * fTempPerm50)):40)):((iTempPerm34)?((20 * fTempPerm51) + 40):60)):((iTempPerm33)?(60 - (20 * fTempPerm52)):40)):40):((iTempPerm31)?(40 * (fTempPerm53 + 1)):80)):((iTempPerm30)?(80 - fTempPerm55):70)):((iTempPerm29)?(70 - (30 * fTempPerm56)):40)):40):40):((iTempPerm26)?(40 * (fTempPerm57 + 1)):80)):((iTempPerm25)?(80 - fTempPerm59):60)):60):((iTempPerm23)?(60 - (20 * fTempPerm60)):40)):((iTempPerm22)?((10 * fTempPerm61) + 40):50)):50):((iTempPerm20)?(fTempPerm63 + 50):70)):((iTempPerm19)?(70 - (30 * fTempPerm64)):40)):((iTempPerm18)?((30 * fTempPerm65) + 40):70)):((iTempPerm66)?(70 - (30 * fTempPerm67)):40));
			fRec4[0] = ((fConst4 * fRec4[1]) + (fConst5 * (fTempPerm16 * fTempPerm68)));
			fTempPerm69 = expf((fConst3 * (0 - fRec4[0])));
			fRec8[0] = ((fConst4 * fRec8[1]) + (fConst5 * fTempPerm68));
			fTempPerm70 = expf((fConst3 * (0 - fRec8[0])));
			fRec0[0] = (iVec2[1] - ((fRec0[1] * (0 - (fTempPerm69 + fTempPerm70))) + ((fTempPerm69 * fTempPerm70) * fRec0[2])));
			fTempPerm71 = ((0.003666666666666667f * (400 - fTempPerm15)) + 3);
			fTempPerm72 = ((0.00084000000000000003f * (1000 - fTempPerm15)) + 0.80000000000000004f);
			iTempPerm74 = (1 - (iVec2[0] > 0));
			fRec11[0] = (fSlow7 + (0.999f * fRec11[1]));
			fTempPerm75 = (fSlow15 + fRec11[0]);
			iTempPerm76 = int((fTempPerm75 < 23));
			iTempPerm77 = int((fTempPerm75 < 22));
			iTempPerm78 = int((fTempPerm75 < 21));
			iTempPerm79 = int((fTempPerm75 < 20));
			iTempPerm80 = int((fTempPerm75 < 19));
			iTempPerm81 = int((fTempPerm75 < 18));
			iTempPerm82 = int((fTempPerm75 < 17));
			iTempPerm83 = int((fTempPerm75 < 16));
			iTempPerm84 = int((fTempPerm75 < 15));
			iTempPerm85 = int((fTempPerm75 < 14));
			iTempPerm86 = int((fTempPerm75 < 13));
			iTempPerm87 = int((fTempPerm75 < 12));
			iTempPerm88 = int((fTempPerm75 < 11));
			iTempPerm89 = int((fTempPerm75 < 10));
			iTempPerm90 = int((fTempPerm75 < 9));
			iTempPerm91 = int((fTempPerm75 < 8));
			iTempPerm92 = int((fTempPerm75 < 7));
			iTempPerm93 = int((fTempPerm75 < 6));
			iTempPerm94 = int((fTempPerm75 < 5));
			iTempPerm95 = int((fTempPerm75 < 4));
			iTempPerm96 = int((fTempPerm75 < 3));
			iTempPerm97 = int((fTempPerm75 < 2));
			iTempPerm98 = int((fTempPerm75 < 1));
			iTempPerm99 = int((fTempPerm75 < 0));
			fTempPerm100 = (fSlow15 + (fRec11[0] + -1));
			fTempPerm101 = (fSlow15 + (fRec11[0] + -2));
			fTempPerm102 = (fSlow15 + (fRec11[0] + -3));
			fTempPerm103 = (fSlow15 + (fRec11[0] + -4));
			fTempPerm104 = (fRec11[0] - fSlow16);
			fTempPerm105 = (fSlow15 + (fRec11[0] + -6));
			fTempPerm106 = (fSlow15 + (fRec11[0] + -7));
			fTempPerm107 = (fSlow15 + (fRec11[0] + -8));
			fTempPerm108 = (50 * fTempPerm107);
			fTempPerm109 = (fSlow15 + (fRec11[0] + -9));
			fTempPerm110 = (fSlow15 + (fRec11[0] + -10));
			fTempPerm111 = (fSlow15 + (fRec11[0] + -11));
			fTempPerm112 = (fSlow15 + (fRec11[0] + -12));
			fTempPerm113 = (fSlow15 + (fRec11[0] + -13));
			fTempPerm114 = (fSlow15 + (fRec11[0] + -14));
			fTempPerm115 = (fSlow15 + (fRec11[0] + -15));
			fTempPerm116 = (fSlow15 + (fRec11[0] + -16));
			fTempPerm117 = (fSlow15 + (fRec11[0] + -17));
			fTempPerm118 = (fSlow15 + (fRec11[0] + -18));
			fTempPerm119 = (fSlow15 + (fRec11[0] + -19));
			fTempPerm120 = (fSlow15 + (fRec11[0] + -20));
			fTempPerm121 = (fSlow15 + (fRec11[0] + -21));
			fTempPerm122 = (fSlow15 + (fRec11[0] + -22));
			iTempPerm123 = int((fTempPerm75 < 24));
			fTempPerm124 = (fSlow15 + (fRec11[0] + -23));
			fTempPerm125 = ((iTempPerm76)?((iTempPerm77)?((iTempPerm78)?((iTempPerm79)?((iTempPerm80)?((iTempPerm81)?((iTempPerm82)?((iTempPerm83)?((iTempPerm84)?((iTempPerm85)?((iTempPerm86)?((iTempPerm87)?((iTempPerm88)?((iTempPerm89)?((iTempPerm90)?((iTempPerm91)?((iTempPerm92)?((iTempPerm93)?((iTempPerm94)?((iTempPerm95)?((iTempPerm96)?((iTempPerm97)?((iTempPerm98)?((iTempPerm99)?800:((iTempPerm98)?(800 - (400 * fTempPerm75)):400)):((iTempPerm97)?(400 - (50 * fTempPerm100)):350)):((iTempPerm96)?((100 * fTempPerm101) + 350):450)):((iTempPerm95)?(450 - (125 * fTempPerm102)):325)):((iTempPerm94)?((275 * fTempPerm103) + 325):600)):((iTempPerm93)?(600 - (200 * fTempPerm104)):400)):((iTempPerm92)?(400 - (150 * fTempPerm105)):250)):((iTempPerm91)?((150 * fTempPerm106) + 250):400)):((iTempPerm90)?(400 - fTempPerm108):350)):((iTempPerm89)?((310 * fTempPerm109) + 350):660)):((iTempPerm88)?(660 - (220 * fTempPerm110)):440)):((iTempPerm87)?(440 - (170 * fTempPerm111)):270)):((iTempPerm86)?((160 * fTempPerm112) + 270):430)):((iTempPerm85)?(430 - (60 * fTempPerm113)):370)):((iTempPerm84)?((430 * fTempPerm114) + 370):800)):((iTempPerm83)?(800 - (450 * fTempPerm115)):350)):((iTempPerm82)?(350 - (80 * fTempPerm116)):270)):((iTempPerm81)?((180 * fTempPerm117) + 270):450)):((iTempPerm80)?(450 - (125 * fTempPerm118)):325)):((iTempPerm79)?(325 * (fTempPerm119 + 1)):650)):((iTempPerm78)?(650 - (250 * fTempPerm120)):400)):((iTempPerm77)?(400 - (110 * fTempPerm121)):290)):((iTempPerm76)?((110 * fTempPerm122) + 290):400)):((iTempPerm123)?(400 - (50 * fTempPerm124)):350));
			fTempPerm126 = ((fRec10[1] * iTempPerm74) + (fConst6 * ((int((fTempPerm125 <= fVec1[0])))?fVec1[0]:fTempPerm125)));
			fRec10[0] = (fTempPerm126 - floorf(fTempPerm126));
			fTempPerm127 = (10 * fTempPerm50);
			fTempPerm128 = (10 * fTempPerm53);
			fTempPerm129 = (fSlow15 + (fRec5[0] + -12));
			fTempPerm130 = (fSlow15 + (fRec5[0] + -13));
			fTempPerm131 = (fSlow15 + (fRec5[0] + -16));
			fTempPerm132 = (fSlow15 + (fRec5[0] + -19));
			fTempPerm133 = (10 * fTempPerm62);
			fTempPerm134 = (10 * fTempPerm65);
			fTempPerm135 = ((iTempPerm18)?((iTempPerm19)?((iTempPerm20)?((iTempPerm21)?((iTempPerm22)?((iTempPerm23)?((iTempPerm24)?((iTempPerm25)?((iTempPerm26)?((iTempPerm27)?((iTempPerm28)?((iTempPerm29)?((iTempPerm30)?((iTempPerm31)?((iTempPerm32)?((iTempPerm33)?((iTempPerm34)?((iTempPerm35)?((iTempPerm36)?((iTempPerm37)?((iTempPerm38)?((iTempPerm39)?((iTempPerm40)?((iTempPerm41)?90:((iTempPerm40)?(90 - (10 * fTempPerm17)):80)):((iTempPerm39)?((20 * fTempPerm43) + 80):100)):((iTempPerm38)?(100 - fTempPerm45):80)):((iTempPerm37)?(80 - fTempPerm47):60)):((iTempPerm36)?(fTempPerm49 + 60):70)):((iTempPerm35)?(fTempPerm127 + 70):80)):((iTempPerm34)?((10 * fTempPerm51) + 80):90)):((iTempPerm33)?(90 - (10 * fTempPerm52)):80)):80):((iTempPerm31)?(fTempPerm128 + 80):90)):((iTempPerm30)?(90 - fTempPerm55):80)):((iTempPerm29)?((10 * fTempPerm56) + 80):90)):((iTempPerm28)?(90 - (10 * fTempPerm129)):80)):((iTempPerm27)?(80 - (20 * fTempPerm130)):60)):((iTempPerm26)?((30 * fTempPerm57) + 60):90)):((iTempPerm25)?((10 * fTempPerm58) + 90):100)):((iTempPerm24)?(100 - (10 * fTempPerm131)):90)):((iTempPerm23)?(90 - (10 * fTempPerm60)):80)):((iTempPerm22)?(80 - (20 * fTempPerm61)):60)):((iTempPerm21)?((30 * fTempPerm132) + 60):90)):((iTempPerm20)?(90 - fTempPerm133):80)):((iTempPerm19)?((10 * fTempPerm64) + 80):90)):((iTempPerm18)?(90 - fTempPerm134):80)):((iTempPerm66)?(80 - (20 * fTempPerm67)):60));
			fRec13[0] = ((fConst4 * fRec13[1]) + (fConst5 * (fTempPerm16 * fTempPerm135)));
			fTempPerm136 = expf((fConst3 * (0 - fRec13[0])));
			fRec14[0] = ((fConst4 * fRec14[1]) + (fConst5 * fTempPerm135));
			fTempPerm137 = expf((fConst3 * (0 - fRec14[0])));
			fRec12[0] = (iVec2[1] - ((fRec12[1] * (0 - (fTempPerm136 + fTempPerm137))) + ((fTempPerm136 * fTempPerm137) * fRec12[2])));
			fTempPerm138 = (fSlow15 + (fRec5[0] + -8));
			fTempPerm139 = ((iTempPerm18)?((iTempPerm19)?((iTempPerm20)?((iTempPerm21)?((iTempPerm22)?((iTempPerm23)?((iTempPerm24)?((iTempPerm25)?((iTempPerm26)?((iTempPerm27)?((iTempPerm28)?((iTempPerm29)?((iTempPerm30)?((iTempPerm31)?((iTempPerm32)?((iTempPerm33)?((iTempPerm34)?((iTempPerm35)?((iTempPerm36)?((iTempPerm37)?((iTempPerm38)?((iTempPerm39)?((iTempPerm40)?((iTempPerm41)?0.63095699999999999f:((iTempPerm40)?(0.63095699999999999f - (0.56786099999999995f * fTempPerm17)):0.063095999999999999f)):((iTempPerm39)?((0.036904000000000006f * fTempPerm43) + 0.063095999999999999f):0.10000000000000001f)):((iTempPerm38)?((0.25481299999999996f * fTempPerm44) + 0.10000000000000001f):0.35481299999999999f)):((iTempPerm37)?(0.35481299999999999f - (0.10362399999999999f * fTempPerm46)):0.251189f)):((iTempPerm36)?((0.19549500000000003f * fTempPerm48) + 0.251189f):0.44668400000000003f)):((iTempPerm35)?(0.44668400000000003f - (0.19549500000000003f * fTempPerm50)):0.251189f)):((iTempPerm34)?(0.251189f - (0.21956599999999998f * fTempPerm51)):0.031622999999999998f)):((iTempPerm33)?((0.25021499999999997f * fTempPerm52) + 0.031622999999999998f):0.28183799999999998f)):((iTempPerm32)?(0.28183799999999998f - (0.18183799999999997f * fTempPerm138)):0.10000000000000001f)):((iTempPerm31)?((0.40118700000000007f * fTempPerm53) + 0.10000000000000001f):0.50118700000000005f)):((iTempPerm30)?(0.50118700000000005f - (0.30166100000000007f * fTempPerm54)):0.19952600000000001f)):((iTempPerm29)?(0.19952600000000001f - (0.13643f * fTempPerm56)):0.063095999999999999f)):((iTempPerm28)?((0.25313200000000002f * fTempPerm129) + 0.063095999999999999f):0.31622800000000001f)):((iTempPerm27)?(0.31622800000000001f - (0.216228f * fTempPerm130)):0.10000000000000001f)):((iTempPerm26)?((0.40118700000000007f * fTempPerm57) + 0.10000000000000001f):0.50118700000000005f)):((iTempPerm25)?(0.50118700000000005f - (0.40118700000000007f * fTempPerm58)):0.10000000000000001f)):((iTempPerm24)?((0.15118899999999999f * fTempPerm131) + 0.10000000000000001f):0.251189f)):((iTempPerm23)?((0.030648999999999982f * fTempPerm60) + 0.251189f):0.28183799999999998f)):((iTempPerm22)?(0.28183799999999998f - (0.12334899999999999f * fTempPerm61)):0.15848899999999999f)):((iTempPerm21)?((0.34269800000000006f * fTempPerm132) + 0.15848899999999999f):0.50118700000000005f)):((iTempPerm20)?(0.50118700000000005f - (0.30166100000000007f * fTempPerm62)):0.19952600000000001f)):((iTempPerm19)?(0.19952600000000001f - (0.021697999999999995f * fTempPerm64)):0.17782800000000001f)):((iTempPerm18)?((0.1384f * fTempPerm65) + 0.17782800000000001f):0.31622800000000001f)):((iTempPerm66)?(0.31622800000000001f - (0.216228f * fTempPerm67)):0.10000000000000001f));
			fTempPerm140 = ((iTempPerm76)?((iTempPerm77)?((iTempPerm78)?((iTempPerm79)?((iTempPerm80)?((iTempPerm81)?((iTempPerm82)?((iTempPerm83)?((iTempPerm84)?((iTempPerm85)?((iTempPerm86)?((iTempPerm87)?((iTempPerm88)?((iTempPerm89)?((iTempPerm90)?((iTempPerm91)?((iTempPerm92)?((iTempPerm93)?((iTempPerm94)?((iTempPerm95)?((iTempPerm96)?((iTempPerm97)?((iTempPerm98)?((iTempPerm99)?1150:((iTempPerm98)?((450 * fTempPerm75) + 1150):1600)):((iTempPerm97)?((100 * fTempPerm100) + 1600):1700)):((iTempPerm96)?(1700 - (900 * fTempPerm101)):800)):((iTempPerm95)?(800 - (100 * fTempPerm102)):700)):((iTempPerm94)?((340 * fTempPerm103) + 700):1040)):((iTempPerm93)?((580 * fTempPerm104) + 1040):1620)):((iTempPerm92)?((130 * fTempPerm105) + 1620):1750)):((iTempPerm91)?(1750 - (1000 * fTempPerm106)):750)):((iTempPerm90)?(750 - (150 * fTempPerm107)):600)):((iTempPerm89)?((520 * fTempPerm109) + 600):1120)):((iTempPerm88)?((680 * fTempPerm110) + 1120):1800)):((iTempPerm87)?((50 * fTempPerm111) + 1800):1850)):((iTempPerm86)?(1850 - (1030 * fTempPerm112)):820)):((iTempPerm85)?(820 - (190 * fTempPerm113)):630)):((iTempPerm84)?((520 * fTempPerm114) + 630):1150)):((iTempPerm83)?((850 * fTempPerm115) + 1150):2000)):((iTempPerm82)?((140 * fTempPerm116) + 2000):2140)):((iTempPerm81)?(2140 - (1340 * fTempPerm117)):800)):((iTempPerm80)?(800 - (100 * fTempPerm118)):700)):((iTempPerm79)?((380 * fTempPerm119) + 700):1080)):((iTempPerm78)?((620 * fTempPerm120) + 1080):1700)):((iTempPerm77)?((170 * fTempPerm121) + 1700):1870)):((iTempPerm76)?(1870 - (1070 * fTempPerm122)):800)):((iTempPerm123)?(800 - (200 * fTempPerm124)):600));
			fTempPerm141 = ((fSlow19 * fTempPerm1) + 30);
			fTempPerm142 = ((iTempPerm74 * fRec15[1]) + (fConst6 * ((iSlow18)?((int(((fTempPerm140 >= 1300) & (fVec1[0] >= 200))))?(fTempPerm140 - (0.00095238095238095238f * ((fVec1[0] + -200) * (fTempPerm140 + -1300)))):((int((fTempPerm140 <= fTempPerm141)))?fTempPerm141:fTempPerm140)):fTempPerm140)));
			fRec15[0] = (fTempPerm142 - floorf(fTempPerm142));
			fTempPerm143 = (60 * fTempPerm48);
			fTempPerm144 = (20 * fTempPerm53);
			fTempPerm145 = (20 * fTempPerm54);
			fTempPerm146 = (20 * fTempPerm57);
			fTempPerm147 = (50 * fTempPerm132);
			fTempPerm148 = ((iTempPerm18)?((iTempPerm19)?((iTempPerm20)?((iTempPerm21)?((iTempPerm22)?((iTempPerm23)?((iTempPerm24)?((iTempPerm25)?((iTempPerm26)?((iTempPerm27)?((iTempPerm28)?((iTempPerm29)?((iTempPerm30)?((iTempPerm31)?((iTempPerm32)?((iTempPerm33)?((iTempPerm34)?((iTempPerm35)?((iTempPerm36)?((iTempPerm37)?((iTempPerm38)?((iTempPerm39)?120:((iTempPerm38)?(120 - fTempPerm45):100)):((iTempPerm37)?((70 * fTempPerm46) + 100):170)):((iTempPerm36)?(170 - fTempPerm143):110)):((iTempPerm35)?(110 - fTempPerm127):100)):100):100):100):((iTempPerm31)?(fTempPerm144 + 100):120)):((iTempPerm30)?(120 - fTempPerm145):100)):100):100):100):((iTempPerm26)?(fTempPerm146 + 100):120)):120):((iTempPerm24)?(120 - (20 * fTempPerm131)):100)):100):((iTempPerm22)?((70 * fTempPerm61) + 100):170)):((iTempPerm21)?(170 - fTempPerm147):120)):((iTempPerm20)?(120 - fTempPerm63):100)):100):100):100);
			fRec17[0] = ((fConst4 * fRec17[1]) + (fConst5 * (fTempPerm16 * fTempPerm148)));
			fTempPerm149 = expf((fConst3 * (0 - fRec17[0])));
			fRec18[0] = ((fConst4 * fRec18[1]) + (fConst5 * fTempPerm148));
			fTempPerm150 = expf((fConst3 * (0 - fRec18[0])));
			fRec16[0] = (iVec2[1] - ((fRec16[1] * (0 - (fTempPerm149 + fTempPerm150))) + ((fTempPerm149 * fTempPerm150) * fRec16[2])));
			fTempPerm151 = ((iTempPerm23)?((0.029314000000000007f * fTempPerm60) + 0.050118999999999997f):0.079433000000000004f);
			fTempPerm152 = ((iTempPerm18)?((iTempPerm19)?((iTempPerm20)?((iTempPerm21)?((iTempPerm22)?((iTempPerm23)?((iTempPerm24)?((iTempPerm25)?((iTempPerm26)?((iTempPerm27)?((iTempPerm28)?((iTempPerm29)?((iTempPerm30)?((iTempPerm31)?((iTempPerm32)?((iTempPerm33)?((iTempPerm34)?((iTempPerm35)?((iTempPerm36)?((iTempPerm37)?((iTempPerm38)?((iTempPerm39)?((iTempPerm40)?((iTempPerm41)?0.10000000000000001f:((iTempPerm40)?(0.10000000000000001f - (0.068377000000000007f * fTempPerm17)):0.031622999999999998f)):0.031622999999999998f):((iTempPerm38)?((0.12686599999999998f * fTempPerm44) + 0.031622999999999998f):0.15848899999999999f)):((iTempPerm37)?(0.15848899999999999f - (0.12686599999999998f * fTempPerm46)):0.031622999999999998f)):((iTempPerm36)?((0.32318999999999998f * fTempPerm48) + 0.031622999999999998f):0.35481299999999999f)):0.35481299999999999f):((iTempPerm34)?(0.35481299999999999f - (0.196324f * fTempPerm51)):0.15848899999999999f)):((iTempPerm33)?(0.15848899999999999f - (0.069363999999999995f * fTempPerm52)):0.089124999999999996f)):((iTempPerm32)?(0.089124999999999996f - (0.064005999999999993f * fTempPerm138)):0.025118999999999999f)):((iTempPerm31)?((0.045675999999999994f * fTempPerm53) + 0.025118999999999999f):0.070794999999999997f)):((iTempPerm30)?((0.055098000000000008f * fTempPerm54) + 0.070794999999999997f):0.125893f)):((iTempPerm29)?(0.125893f - (0.062797000000000006f * fTempPerm56)):0.063095999999999999f)):((iTempPerm28)?(0.063095999999999999f - (0.012977000000000002f * fTempPerm129)):0.050118999999999997f)):((iTempPerm27)?((0.020676f * fTempPerm130) + 0.050118999999999997f):0.070794999999999997f)):((iTempPerm26)?(0.070794999999999997f - (0.045675999999999994f * fTempPerm57)):0.025118999999999999f)):((iTempPerm25)?((0.15270900000000001f * fTempPerm58) + 0.025118999999999999f):0.17782800000000001f)):((iTempPerm24)?(0.17782800000000001f - (0.12770900000000002f * fTempPerm131)):0.050118999999999997f)):fTempPerm151):((iTempPerm22)?(0.079433000000000004f - (0.061650000000000003f * fTempPerm61)):0.017783f)):((iTempPerm21)?((0.42890100000000003f * fTempPerm132) + 0.017783f):0.44668400000000003f)):((iTempPerm20)?(0.44668400000000003f - (0.19549500000000003f * fTempPerm62)):0.251189f)):((iTempPerm19)?(0.251189f - (0.12529599999999999f * fTempPerm64)):0.125893f)):((iTempPerm18)?((0.12529599999999999f * fTempPerm65) + 0.125893f):0.251189f)):((iTempPerm66)?(0.251189f - (0.109935f * fTempPerm67)):0.14125399999999999f));
			fTempPerm153 = (50 * fTempPerm110);
			fTempPerm154 = (100 * fTempPerm124);
			fTempPerm155 = ((iTempPerm74 * fRec19[1]) + (fConst6 * ((iTempPerm76)?((iTempPerm77)?((iTempPerm78)?((iTempPerm79)?((iTempPerm80)?((iTempPerm81)?((iTempPerm82)?((iTempPerm83)?((iTempPerm84)?((iTempPerm85)?((iTempPerm86)?((iTempPerm87)?((iTempPerm88)?((iTempPerm89)?((iTempPerm90)?((iTempPerm91)?((iTempPerm92)?((iTempPerm93)?((iTempPerm94)?((iTempPerm95)?((iTempPerm96)?((iTempPerm97)?((iTempPerm98)?((iTempPerm99)?2800:((iTempPerm98)?(2800 - (100 * fTempPerm75)):2700)):2700):((iTempPerm96)?((130 * fTempPerm101) + 2700):2830)):((iTempPerm95)?(2830 - (300 * fTempPerm102)):2530)):((iTempPerm94)?(2530 - (280 * fTempPerm103)):2250)):((iTempPerm93)?((150 * fTempPerm104) + 2250):2400)):((iTempPerm92)?((200 * fTempPerm105) + 2400):2600)):((iTempPerm91)?(2600 - (200 * fTempPerm106)):2400)):2400):((iTempPerm89)?((350 * fTempPerm109) + 2400):2750)):((iTempPerm88)?(2750 - fTempPerm153):2700)):((iTempPerm87)?((200 * fTempPerm111) + 2700):2900)):((iTempPerm86)?(2900 - (200 * fTempPerm112)):2700)):((iTempPerm85)?((50 * fTempPerm113) + 2700):2750)):((iTempPerm84)?((150 * fTempPerm114) + 2750):2900)):((iTempPerm83)?(2900 - (100 * fTempPerm115)):2800)):((iTempPerm82)?((150 * fTempPerm116) + 2800):2950)):((iTempPerm81)?(2950 - (120 * fTempPerm117)):2830)):((iTempPerm80)?(2830 - (130 * fTempPerm118)):2700)):((iTempPerm79)?(2700 - (50 * fTempPerm119)):2650)):((iTempPerm78)?(2650 - (50 * fTempPerm120)):2600)):((iTempPerm77)?((200 * fTempPerm121) + 2600):2800)):((iTempPerm76)?(2800 - (200 * fTempPerm122)):2600)):((iTempPerm123)?(fTempPerm154 + 2600):2700))));
			fRec19[0] = (fTempPerm155 - floorf(fTempPerm155));
			fTempPerm156 = ((iTempPerm18)?((iTempPerm19)?((iTempPerm20)?((iTempPerm21)?((iTempPerm22)?((iTempPerm23)?((iTempPerm24)?((iTempPerm25)?((iTempPerm26)?((iTempPerm27)?((iTempPerm28)?((iTempPerm29)?((iTempPerm30)?((iTempPerm31)?((iTempPerm32)?((iTempPerm33)?((iTempPerm34)?((iTempPerm35)?((iTempPerm36)?((iTempPerm37)?((iTempPerm38)?((iTempPerm39)?((iTempPerm40)?((iTempPerm41)?130:((iTempPerm40)?(fTempPerm42 + 130):150)):150):((iTempPerm38)?(150 - fTempPerm45):130)):((iTempPerm37)?((50 * fTempPerm46) + 130):180)):((iTempPerm36)?(180 - fTempPerm143):120)):120):120):120):120):((iTempPerm31)?(fTempPerm128 + 120):130)):((iTempPerm30)?(130 - fTempPerm55):120)):120):120):120):((iTempPerm26)?((10 * fTempPerm57) + 120):130)):((iTempPerm25)?(fTempPerm59 + 130):150)):((iTempPerm24)?(150 - (30 * fTempPerm131)):120)):120):((iTempPerm22)?((60 * fTempPerm61) + 120):180)):((iTempPerm21)?(180 - fTempPerm147):130)):((iTempPerm20)?(130 - fTempPerm133):120)):120):((iTempPerm18)?(fTempPerm134 + 120):130)):((iTempPerm66)?(130 - (10 * fTempPerm67)):120));
			fRec21[0] = ((fConst4 * fRec21[1]) + (fConst5 * (fTempPerm16 * fTempPerm156)));
			fTempPerm157 = expf((fConst3 * (0 - fRec21[0])));
			fRec22[0] = ((fConst4 * fRec22[1]) + (fConst5 * fTempPerm156));
			fTempPerm158 = expf((fConst3 * (0 - fRec22[0])));
			fRec20[0] = (iVec2[1] - ((fRec20[1] * (0 - (fTempPerm157 + fTempPerm158))) + ((fTempPerm157 * fTempPerm158) * fRec20[2])));
			fTempPerm159 = ((iTempPerm29)?(0.10000000000000001f - (0.084151000000000004f * fTempPerm56)):0.015848999999999999f);
			fTempPerm160 = ((iTempPerm18)?((iTempPerm19)?((iTempPerm20)?((iTempPerm21)?((iTempPerm22)?((iTempPerm23)?((iTempPerm24)?((iTempPerm25)?((iTempPerm26)?((iTempPerm27)?((iTempPerm28)?((iTempPerm29)?((iTempPerm30)?((iTempPerm31)?((iTempPerm32)?((iTempPerm33)?((iTempPerm34)?((iTempPerm35)?((iTempPerm36)?((iTempPerm37)?((iTempPerm38)?((iTempPerm39)?((iTempPerm40)?((iTempPerm41)?0.015848999999999999f:((iTempPerm40)?((0.0019340000000000017f * fTempPerm17) + 0.015848999999999999f):0.017783f)):((iTempPerm39)?(0.017783f - (0.0019340000000000017f * fTempPerm43)):0.015848999999999999f)):((iTempPerm38)?((0.023962000000000001f * fTempPerm44) + 0.015848999999999999f):0.039810999999999999f)):((iTempPerm37)?(0.039810999999999999f - (0.029810999999999997f * fTempPerm46)):0.01f)):((iTempPerm36)?((0.34481299999999998f * fTempPerm48) + 0.01f):0.35481299999999999f)):((iTempPerm35)?(0.35481299999999999f - (0.10362399999999999f * fTempPerm50)):0.251189f)):((iTempPerm34)?(0.251189f - (0.17175599999999999f * fTempPerm51)):0.079433000000000004f)):((iTempPerm33)?((0.020567000000000002f * fTempPerm52) + 0.079433000000000004f):0.10000000000000001f)):((iTempPerm32)?(0.10000000000000001f - (0.060189000000000006f * fTempPerm138)):0.039810999999999999f)):((iTempPerm31)?((0.023285f * fTempPerm53) + 0.039810999999999999f):0.063095999999999999f)):((iTempPerm30)?((0.036904000000000006f * fTempPerm54) + 0.063095999999999999f):0.10000000000000001f)):fTempPerm159):((iTempPerm28)?((0.063584000000000002f * fTempPerm129) + 0.015848999999999999f):0.079433000000000004f)):((iTempPerm27)?(0.079433000000000004f - (0.047810000000000005f * fTempPerm130)):0.031622999999999998f)):((iTempPerm26)?((0.068377000000000007f * fTempPerm57) + 0.031622999999999998f):0.10000000000000001f)):((iTempPerm25)?(0.10000000000000001f - (0.090000000000000011f * fTempPerm58)):0.01f)):((iTempPerm24)?((0.040118999999999995f * fTempPerm131) + 0.01f):0.050118999999999997f)):fTempPerm151):((iTempPerm22)?(0.079433000000000004f - (0.069433000000000009f * fTempPerm61)):0.01f)):((iTempPerm21)?((0.38810699999999998f * fTempPerm132) + 0.01f):0.39810699999999999f)):((iTempPerm20)?(0.39810699999999999f - (0.19858099999999998f * fTempPerm62)):0.19952600000000001f)):((iTempPerm19)?(0.19952600000000001f - (0.099526000000000003f * fTempPerm64)):0.10000000000000001f)):((iTempPerm18)?((0.15118899999999999f * fTempPerm65) + 0.10000000000000001f):0.251189f)):((iTempPerm66)?(0.251189f - (0.051662999999999987f * fTempPerm67)):0.19952600000000001f));
			fTempPerm161 = (350 * fTempPerm104);
			fTempPerm162 = ((iTempPerm74 * fRec23[1]) + (fConst6 * ((iTempPerm76)?((iTempPerm77)?((iTempPerm78)?((iTempPerm79)?((iTempPerm80)?((iTempPerm81)?((iTempPerm82)?((iTempPerm83)?((iTempPerm84)?((iTempPerm85)?((iTempPerm86)?((iTempPerm87)?((iTempPerm88)?((iTempPerm89)?((iTempPerm90)?((iTempPerm91)?((iTempPerm92)?((iTempPerm93)?((iTempPerm94)?((iTempPerm95)?((iTempPerm96)?((iTempPerm97)?((iTempPerm98)?((iTempPerm99)?3500:((iTempPerm98)?(3500 - (200 * fTempPerm75)):3300)):((iTempPerm97)?((400 * fTempPerm100) + 3300):3700)):((iTempPerm96)?(3700 - (200 * fTempPerm101)):3500)):3500):((iTempPerm94)?(3500 - (1050 * fTempPerm103)):2450)):((iTempPerm93)?(fTempPerm161 + 2450):2800)):((iTempPerm92)?((250 * fTempPerm105) + 2800):3050)):((iTempPerm91)?(3050 - (450 * fTempPerm106)):2600)):((iTempPerm90)?((75 * fTempPerm107) + 2600):2675)):((iTempPerm89)?((325 * fTempPerm109) + 2675):3000)):3000):((iTempPerm87)?((350 * fTempPerm111) + 3000):3350)):((iTempPerm86)?(3350 - (350 * fTempPerm112)):3000)):3000):((iTempPerm84)?((900 * fTempPerm114) + 3000):3900)):((iTempPerm83)?(3900 - (300 * fTempPerm115)):3600)):((iTempPerm82)?((300 * fTempPerm116) + 3600):3900)):((iTempPerm81)?(3900 - (100 * fTempPerm117)):3800)):3800):((iTempPerm79)?(3800 - (900 * fTempPerm119)):2900)):((iTempPerm78)?((300 * fTempPerm120) + 2900):3200)):((iTempPerm77)?((50 * fTempPerm121) + 3200):3250)):((iTempPerm76)?(3250 - (450 * fTempPerm122)):2800)):((iTempPerm123)?(fTempPerm154 + 2800):2900))));
			fRec23[0] = (fTempPerm162 - floorf(fTempPerm162));
			fTempPerm163 = ((iTempPerm18)?((iTempPerm19)?((iTempPerm20)?((iTempPerm21)?((iTempPerm22)?((iTempPerm23)?((iTempPerm24)?((iTempPerm25)?((iTempPerm26)?((iTempPerm27)?((iTempPerm28)?((iTempPerm29)?((iTempPerm30)?((iTempPerm31)?((iTempPerm32)?((iTempPerm33)?((iTempPerm34)?((iTempPerm35)?((iTempPerm36)?((iTempPerm37)?((iTempPerm38)?((iTempPerm39)?((iTempPerm40)?((iTempPerm41)?140:((iTempPerm40)?((60 * fTempPerm17) + 140):200)):200):((iTempPerm38)?(200 - (65 * fTempPerm44)):135)):((iTempPerm37)?((65 * fTempPerm46) + 135):200)):((iTempPerm36)?(200 - (70 * fTempPerm48)):130)):((iTempPerm35)?(130 - fTempPerm127):120)):120):120):120):((iTempPerm31)?(fTempPerm144 + 120):140)):((iTempPerm30)?(140 - fTempPerm145):120)):120):120):120):((iTempPerm26)?(fTempPerm146 + 120):140)):((iTempPerm25)?((60 * fTempPerm58) + 140):200)):((iTempPerm24)?(200 - (80 * fTempPerm131)):120)):120):((iTempPerm22)?((80 * fTempPerm61) + 120):200)):((iTempPerm21)?(200 - (60 * fTempPerm132)):140)):((iTempPerm20)?(140 - fTempPerm63):120)):120):((iTempPerm18)?((15 * fTempPerm65) + 120):135)):((iTempPerm66)?(135 - (15 * fTempPerm67)):120));
			fRec25[0] = ((fConst4 * fRec25[1]) + (fConst5 * (fTempPerm16 * fTempPerm163)));
			fTempPerm164 = expf((fConst3 * (0 - fRec25[0])));
			fRec26[0] = ((fConst4 * fRec26[1]) + (fConst5 * fTempPerm163));
			fTempPerm165 = expf((fConst3 * (0 - fRec26[0])));
			fRec24[0] = (iVec2[1] - ((fRec24[1] * (0 - (fTempPerm164 + fTempPerm165))) + ((fTempPerm164 * fTempPerm165) * fRec24[2])));
			fTempPerm166 = ((iTempPerm18)?((iTempPerm19)?((iTempPerm20)?((iTempPerm21)?((iTempPerm22)?((iTempPerm23)?((iTempPerm24)?((iTempPerm25)?((iTempPerm26)?((iTempPerm27)?((iTempPerm28)?((iTempPerm29)?((iTempPerm30)?((iTempPerm31)?((iTempPerm32)?((iTempPerm33)?((iTempPerm34)?((iTempPerm35)?((iTempPerm36)?((iTempPerm37)?((iTempPerm38)?((iTempPerm39)?0.001f:((iTempPerm38)?((0.00077800000000000005f * fTempPerm44) + 0.001f):0.0017780000000000001f)):((iTempPerm37)?(0.0017780000000000001f - (0.001147f * fTempPerm46)):0.00063100000000000005f)):((iTempPerm36)?((0.099368999999999999f * fTempPerm48) + 0.00063100000000000005f):0.10000000000000001f)):((iTempPerm35)?((0.025892999999999999f * fTempPerm50) + 0.10000000000000001f):0.125893f)):((iTempPerm34)?(0.125893f - (0.086082000000000006f * fTempPerm51)):0.039810999999999999f)):((iTempPerm33)?(0.039810999999999999f - (0.029810999999999997f * fTempPerm52)):0.01f)):((iTempPerm32)?((0.0058489999999999983f * fTempPerm138) + 0.01f):0.015848999999999999f)):((iTempPerm31)?(0.015848999999999999f - (0.003259999999999999f * fTempPerm53)):0.012588999999999999f)):((iTempPerm30)?((0.087411000000000003f * fTempPerm54) + 0.012588999999999999f):0.10000000000000001f)):fTempPerm159):((iTempPerm28)?((0.004104f * fTempPerm129) + 0.015848999999999999f):0.019952999999999999f)):0.019952999999999999f):((iTempPerm26)?(0.019952999999999999f - (0.016791f * fTempPerm57)):0.0031619999999999999f)):((iTempPerm25)?(0.0031619999999999999f - (0.0015769999999999998f * fTempPerm58)):0.001585f)):((iTempPerm24)?((0.004725f * fTempPerm131) + 0.001585f):0.0063099999999999996f)):((iTempPerm23)?(0.0063099999999999996f - (0.0031479999999999998f * fTempPerm60)):0.0031619999999999999f)):((iTempPerm22)?(0.0031619999999999999f - (0.0021619999999999999f * fTempPerm61)):0.001f)):((iTempPerm21)?((0.078433000000000003f * fTempPerm132) + 0.001f):0.079433000000000004f)):((iTempPerm20)?((0.020567000000000002f * fTempPerm62) + 0.079433000000000004f):0.10000000000000001f)):((iTempPerm19)?(0.10000000000000001f - (0.068377000000000007f * fTempPerm64)):0.031622999999999998f)):((iTempPerm18)?((0.018495999999999999f * fTempPerm65) + 0.031622999999999998f):0.050118999999999997f)):0.050118999999999997f);
			fTempPerm167 = ((iTempPerm74 * fRec27[1]) + (fConst6 * ((iTempPerm76)?((iTempPerm77)?((iTempPerm78)?((iTempPerm79)?((iTempPerm80)?((iTempPerm81)?((iTempPerm82)?((iTempPerm83)?((iTempPerm84)?((iTempPerm85)?((iTempPerm86)?((iTempPerm87)?((iTempPerm88)?((iTempPerm89)?((iTempPerm90)?((iTempPerm91)?((iTempPerm92)?((iTempPerm93)?((iTempPerm94)?((iTempPerm95)?4950:((iTempPerm94)?(4950 - (2200 * fTempPerm103)):2750)):((iTempPerm93)?(fTempPerm161 + 2750):3100)):((iTempPerm92)?((240 * fTempPerm105) + 3100):3340)):((iTempPerm91)?(3340 - (440 * fTempPerm106)):2900)):((iTempPerm90)?(fTempPerm108 + 2900):2950)):((iTempPerm89)?((400 * fTempPerm109) + 2950):3350)):((iTempPerm88)?(3350 - fTempPerm153):3300)):((iTempPerm87)?((290 * fTempPerm111) + 3300):3590)):((iTempPerm86)?(3590 - (290 * fTempPerm112)):3300)):((iTempPerm85)?((100 * fTempPerm113) + 3300):3400)):((iTempPerm84)?((1550 * fTempPerm114) + 3400):4950)):4950):4950):4950):4950):((iTempPerm79)?(4950 - (1700 * fTempPerm119)):3250)):((iTempPerm78)?((330 * fTempPerm120) + 3250):3580)):((iTempPerm77)?(3580 - (40 * fTempPerm121)):3540)):((iTempPerm76)?(3540 - (540 * fTempPerm122)):3000)):((iTempPerm123)?((300 * fTempPerm124) + 3000):3300))));
			fRec27[0] = (fTempPerm167 - floorf(fTempPerm167));
			fTempPerm168 = (fSlow0 * (((((((fRec0[0] * ((iSlow17)?fTempPerm71:fTempPerm72)) * (1 - (fTempPerm70 + (fTempPerm69 * (1 - fTempPerm70))))) * ftbl0[int((65536 * fRec10[0]))]) + (((fRec12[0] * ((iSlow17)?(fTempPerm71 * fTempPerm139):(fTempPerm72 * fTempPerm139))) * (1 - (fTempPerm137 + (fTempPerm136 * (1 - fTempPerm137))))) * ftbl0[int((65536 * fRec15[0]))])) + (((fRec16[0] * ((iSlow17)?(fTempPerm71 * fTempPerm152):(fTempPerm72 * fTempPerm152))) * (1 - (fTempPerm150 + (fTempPerm149 * (1 - fTempPerm150))))) * ftbl0[int((65536 * fRec19[0]))])) + (((fRec20[0] * ((iSlow17)?(fTempPerm71 * fTempPerm160):(fTempPerm72 * fTempPerm160))) * (1 - (fTempPerm158 + (fTempPerm157 * (1 - fTempPerm158))))) * ftbl0[int((65536 * fRec23[0]))])) + (((fRec24[0] * ((iSlow17)?(fTempPerm71 * fTempPerm166):(fTempPerm72 * fTempPerm166))) * (1 - (fTempPerm165 + (fTempPerm164 * (1 - fTempPerm165))))) * ftbl0[int((65536 * fRec27[0]))])));
			output0[i] = (FAUSTFLOAT)fTempPerm168;
			output1[i] = (FAUSTFLOAT)fTempPerm168;
			// post processing
			fRec27[1] = fRec27[0];
			fRec24[2] = fRec24[1]; fRec24[1] = fRec24[0];
			fRec26[1] = fRec26[0];
			fRec25[1] = fRec25[0];
			fRec23[1] = fRec23[0];
			fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
			fRec22[1] = fRec22[0];
			fRec21[1] = fRec21[0];
			fRec19[1] = fRec19[0];
			fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
			fRec18[1] = fRec18[0];
			fRec17[1] = fRec17[0];
			fRec15[1] = fRec15[0];
			fRec12[2] = fRec12[1]; fRec12[1] = fRec12[0];
			fRec14[1] = fRec14[0];
			fRec13[1] = fRec13[0];
			fRec10[1] = fRec10[0];
			fRec11[1] = fRec11[0];
			fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
			fRec8[1] = fRec8[0];
			fRec4[1] = fRec4[0];
			fRec7[1] = fRec7[0];
			fRec6[1] = fRec6[0];
			fRec5[1] = fRec5[0];
			iVec2[1] = iVec2[0];
			fRec1[1] = fRec1[0];
			fVec1[1] = fVec1[0];
			fRec3[1] = fRec3[0];
			fRec2[1] = fRec2[0];
			iVec0[1] = iVec0[0];
		}
	}
};


float 	mydsp::ftbl0[65536];
