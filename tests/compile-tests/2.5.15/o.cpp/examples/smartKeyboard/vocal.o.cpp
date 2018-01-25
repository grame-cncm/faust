//----------------------------------------------------------
// name: "vocal"
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
	float 	fConst0;
	float 	fConst1;
	float 	fConst2;
	FAUSTFLOAT 	fslider1;
	float 	fRec3[2];
	FAUSTFLOAT 	fslider2;
	float 	fConst3;
	float 	fConst4;
	float 	fConst5;
	float 	fRec4[2];
	float 	fConst6;
	int 	iTempPerm0;
	float 	fRec5[2];
	float 	fTempPerm1;
	float 	fTempPerm2;
	float 	fTempPerm3;
	int 	iTempPerm4;
	float 	fRec1[2];
	float 	fTempPerm5;
	float 	fConst7;
	FAUSTFLOAT 	fslider3;
	float 	fRec6[2];
	float 	fTempPerm6;
	int 	iTempPerm7;
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
	int 	iTempPerm54;
	float 	fTempPerm55;
	float 	fTempPerm56;
	float 	fRec7[2];
	float 	fRec8[2];
	float 	fRec9[2];
	float 	fTempPerm57;
	float 	fTempPerm58;
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
	float 	fRec0[3];
	float 	fTempPerm70;
	float 	fTempPerm71;
	float 	fTempPerm72;
	float 	fTempPerm73;
	float 	fTempPerm74;
	float 	fTempPerm75;
	float 	fTempPerm76;
	float 	fTempPerm77;
	float 	fTempPerm78;
	float 	fTempPerm79;
	float 	fTempPerm80;
	float 	fTempPerm81;
	float 	fRec10[3];
	float 	fTempPerm82;
	float 	fTempPerm83;
	float 	fTempPerm84;
	float 	fTempPerm85;
	float 	fTempPerm86;
	float 	fTempPerm87;
	float 	fTempPerm88;
	float 	fTempPerm89;
	float 	fTempPerm90;
	float 	fTempPerm91;
	float 	fTempPerm92;
	float 	fTempPerm93;
	float 	fTempPerm94;
	float 	fRec11[3];
	float 	fTempPerm95;
	float 	fTempPerm96;
	float 	fTempPerm97;
	float 	fTempPerm98;
	float 	fTempPerm99;
	float 	fTempPerm100;
	float 	fTempPerm101;
	float 	fTempPerm102;
	float 	fRec12[3];
	float 	fTempPerm103;
	float 	fTempPerm104;
	float 	fTempPerm105;
	float 	fTempPerm106;
	float 	fTempPerm107;
	float 	fTempPerm108;
	float 	fTempPerm109;
	float 	fRec13[3];
	float 	fTempPerm110;
	float 	fTempPerm111;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("interface", "SmartKeyboard{  'Number of Keyboards':'1',  'Max Keyboard Polyphony':'0',  'Keyboard 0 - Number of Keys':'1',  'Keyboard 0 - Send Freq':'0',  'Keyboard 0 - Static Mode':'1',  'Keyboard 0 - Send X':'1',  'Keyboard 0 - Piano Keyboard':'0' }");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "vocal");
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
		fConst1 = float(fConst0);
		fConst2 = (1.0f / fConst1);
		fConst3 = (37.699111843077517f / fConst0);
		fConst4 = sinf(fConst3);
		fConst5 = cosf(fConst3);
		fConst6 = (0 - fConst4);
		iTempPerm0 = 0;
		fTempPerm1 = 0;
		fTempPerm2 = 0;
		fTempPerm3 = 0;
		iTempPerm4 = 0;
		fTempPerm5 = 0;
		fConst7 = (3.1415926535897931f / fConst0);
		fTempPerm6 = 0;
		iTempPerm7 = 0;
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
		iTempPerm54 = 0;
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
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.25f;
		fslider1 = 0.5f;
		fslider2 = 0.050000000000000003f;
		fslider3 = 2.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) iVec0[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<2; i++) fRec7[i] = 0;
		for (int i=0; i<2; i++) fRec8[i] = 0;
		for (int i=0; i<2; i++) fRec9[i] = 0;
		for (int i=0; i<3; i++) fRec0[i] = 0;
		for (int i=0; i<3; i++) fRec10[i] = 0;
		for (int i=0; i<3; i++) fRec11[i] = 0;
		for (int i=0; i<3; i++) fRec12[i] = 0;
		for (int i=0; i<3; i++) fRec13[i] = 0;
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
		ui_interface->addHorizontalSlider("gain", &fslider0, 0.25f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider2, "acc", "1 0 -10 0 10");
		ui_interface->addHorizontalSlider("vibrato", &fslider2, 0.050000000000000003f, 0.0f, 0.10000000000000001f, 0.01f);
		ui_interface->declare(&fslider3, "acc", "0 0 -10 0 10");
		ui_interface->addHorizontalSlider("vowel", &fslider3, 2.0f, 0.0f, 4.0f, 0.01f);
		ui_interface->addHorizontalSlider("x", &fslider1, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = float(fslider0);
		float 	fSlow1 = (0.0010000000000000009f * float(fslider1));
		float 	fSlow2 = float(fslider2);
		float 	fSlow3 = (0.0010000000000000009f * float(fslider3));
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			iVec0[0] = 1;
			fRec3[0] = (fSlow1 + (0.999f * fRec3[1]));
			fRec4[0] = ((fConst4 * fRec5[1]) + (fConst5 * fRec4[1]));
			iTempPerm0 = (1 - iVec0[1]);
			fRec5[0] = (((fConst5 * fRec5[1]) + (fConst6 * fRec4[1])) + iTempPerm0);
			fTempPerm1 = float(max(9.9999999999999995e-08f, fabsf((((200 * fRec3[0]) + 50) * ((fSlow2 * fRec4[0]) + 1)))));
			fTempPerm2 = (fRec1[1] + (fConst2 * fTempPerm1));
			fTempPerm3 = (fTempPerm2 + -1);
			iTempPerm4 = int((fTempPerm3 < 0));
			fRec1[0] = ((iTempPerm4)?fTempPerm2:fTempPerm3);
			float 	fRec2 = ((iTempPerm4)?fTempPerm2:(fTempPerm2 + (fTempPerm3 * (1 - (fConst1 / fTempPerm1)))));
			fTempPerm5 = (fSlow0 * ((2 * fRec2) + -1));
			fRec6[0] = (fSlow3 + (0.999f * fRec6[1]));
			fTempPerm6 = (fRec6[0] + 5);
			iTempPerm7 = int((fTempPerm6 < 23));
			iTempPerm8 = int((fTempPerm6 < 22));
			iTempPerm9 = int((fTempPerm6 < 21));
			iTempPerm10 = int((fTempPerm6 < 20));
			iTempPerm11 = int((fTempPerm6 < 19));
			iTempPerm12 = int((fTempPerm6 < 18));
			iTempPerm13 = int((fTempPerm6 < 17));
			iTempPerm14 = int((fTempPerm6 < 16));
			iTempPerm15 = int((fTempPerm6 < 15));
			iTempPerm16 = int((fTempPerm6 < 14));
			iTempPerm17 = int((fTempPerm6 < 13));
			iTempPerm18 = int((fTempPerm6 < 12));
			iTempPerm19 = int((fTempPerm6 < 11));
			iTempPerm20 = int((fTempPerm6 < 10));
			iTempPerm21 = int((fTempPerm6 < 9));
			iTempPerm22 = int((fTempPerm6 < 8));
			iTempPerm23 = int((fTempPerm6 < 7));
			iTempPerm24 = int((fTempPerm6 < 6));
			iTempPerm25 = int((fTempPerm6 < 5));
			iTempPerm26 = int((fTempPerm6 < 4));
			iTempPerm27 = int((fTempPerm6 < 3));
			iTempPerm28 = int((fTempPerm6 < 2));
			iTempPerm29 = int((fTempPerm6 < 1));
			iTempPerm30 = int((fTempPerm6 < 0));
			fTempPerm31 = (fRec6[0] + 4);
			fTempPerm32 = (fRec6[0] + 3);
			fTempPerm33 = (fRec6[0] + 2);
			fTempPerm34 = (fRec6[0] + 1);
			fTempPerm35 = (fRec6[0] + -1);
			fTempPerm36 = (fRec6[0] + -2);
			fTempPerm37 = (fRec6[0] + -3);
			fTempPerm38 = (50 * fTempPerm37);
			fTempPerm39 = (fRec6[0] + -4);
			fTempPerm40 = (fRec6[0] + -5);
			fTempPerm41 = (fRec6[0] + -6);
			fTempPerm42 = (fRec6[0] + -7);
			fTempPerm43 = (fRec6[0] + -8);
			fTempPerm44 = (fRec6[0] + -9);
			fTempPerm45 = (fRec6[0] + -10);
			fTempPerm46 = (fRec6[0] + -11);
			fTempPerm47 = (80 * fTempPerm46);
			fTempPerm48 = (fRec6[0] + -12);
			fTempPerm49 = (fRec6[0] + -13);
			fTempPerm50 = (fRec6[0] + -14);
			fTempPerm51 = (fRec6[0] + -15);
			fTempPerm52 = (fRec6[0] + -16);
			fTempPerm53 = (fRec6[0] + -17);
			iTempPerm54 = int((fTempPerm6 < 24));
			fTempPerm55 = (fRec6[0] + -18);
			fTempPerm56 = ((iTempPerm7)?((iTempPerm8)?((iTempPerm9)?((iTempPerm10)?((iTempPerm11)?((iTempPerm12)?((iTempPerm13)?((iTempPerm14)?((iTempPerm15)?((iTempPerm16)?((iTempPerm17)?((iTempPerm18)?((iTempPerm19)?((iTempPerm20)?((iTempPerm21)?((iTempPerm22)?((iTempPerm23)?((iTempPerm24)?((iTempPerm25)?((iTempPerm26)?((iTempPerm27)?((iTempPerm28)?((iTempPerm29)?((iTempPerm30)?800:((iTempPerm29)?(800 - (400 * fTempPerm6)):400)):((iTempPerm28)?(400 - (50 * fTempPerm31)):350)):((iTempPerm27)?((100 * fTempPerm32) + 350):450)):((iTempPerm26)?(450 - (125 * fTempPerm33)):325)):((iTempPerm25)?((275 * fTempPerm34) + 325):600)):((iTempPerm24)?(600 - (200 * fRec6[0])):400)):((iTempPerm23)?(400 - (150 * fTempPerm35)):250)):((iTempPerm22)?((150 * fTempPerm36) + 250):400)):((iTempPerm21)?(400 - fTempPerm38):350)):((iTempPerm20)?((310 * fTempPerm39) + 350):660)):((iTempPerm19)?(660 - (220 * fTempPerm40)):440)):((iTempPerm18)?(440 - (170 * fTempPerm41)):270)):((iTempPerm17)?((160 * fTempPerm42) + 270):430)):((iTempPerm16)?(430 - (60 * fTempPerm43)):370)):((iTempPerm15)?((430 * fTempPerm44) + 370):800)):((iTempPerm14)?(800 - (450 * fTempPerm45)):350)):((iTempPerm13)?(350 - fTempPerm47):270)):((iTempPerm12)?((180 * fTempPerm48) + 270):450)):((iTempPerm11)?(450 - (125 * fTempPerm49)):325)):((iTempPerm10)?(325 * (fTempPerm50 + 1)):650)):((iTempPerm9)?(650 - (250 * fTempPerm51)):400)):((iTempPerm8)?(400 - (110 * fTempPerm52)):290)):((iTempPerm7)?((110 * fTempPerm53) + 290):400)):((iTempPerm54)?(400 - (50 * fTempPerm55)):350));
			fRec7[0] = (fSlow1 + (0.999f * fRec7[1]));
			fRec8[0] = ((fConst4 * fRec9[1]) + (fConst5 * fRec8[1]));
			fRec9[0] = (((fConst5 * fRec9[1]) + (fConst6 * fRec8[1])) + iTempPerm0);
			fTempPerm57 = (((200 * fRec7[0]) + 50) * ((fSlow2 * fRec8[0]) + 1));
			fTempPerm58 = ((int((fTempPerm56 <= fTempPerm57)))?fTempPerm57:fTempPerm56);
			fTempPerm59 = tanf((fConst7 * fTempPerm58));
			fTempPerm60 = (1.0f / fTempPerm59);
			fTempPerm61 = (20 * fTempPerm6);
			fTempPerm62 = (20 * fTempPerm32);
			fTempPerm63 = (20 * fTempPerm33);
			fTempPerm64 = (10 * fTempPerm34);
			fTempPerm65 = (10 * fTempPerm40);
			fTempPerm66 = (20 * fTempPerm45);
			fTempPerm67 = (20 * fTempPerm51);
			fTempPerm68 = (((iTempPerm7)?((iTempPerm8)?((iTempPerm9)?((iTempPerm10)?((iTempPerm11)?((iTempPerm12)?((iTempPerm13)?((iTempPerm14)?((iTempPerm15)?((iTempPerm16)?((iTempPerm17)?((iTempPerm18)?((iTempPerm19)?((iTempPerm20)?((iTempPerm21)?((iTempPerm22)?((iTempPerm23)?((iTempPerm24)?((iTempPerm25)?((iTempPerm26)?((iTempPerm27)?((iTempPerm28)?((iTempPerm29)?((iTempPerm30)?80:((iTempPerm29)?(80 - fTempPerm61):60)):((iTempPerm28)?(60 - (10 * fTempPerm31)):50)):((iTempPerm27)?(fTempPerm62 + 50):70)):((iTempPerm26)?(70 - fTempPerm63):50)):((iTempPerm25)?(fTempPerm64 + 50):60)):((iTempPerm24)?(60 - (20 * fRec6[0])):40)):((iTempPerm23)?((20 * fTempPerm35) + 40):60)):((iTempPerm22)?(60 - (20 * fTempPerm36)):40)):40):((iTempPerm20)?(40 * (fTempPerm39 + 1)):80)):((iTempPerm19)?(80 - fTempPerm65):70)):((iTempPerm18)?(70 - (30 * fTempPerm41)):40)):40):40):((iTempPerm15)?(40 * (fTempPerm44 + 1)):80)):((iTempPerm14)?(80 - fTempPerm66):60)):60):((iTempPerm12)?(60 - (20 * fTempPerm48)):40)):((iTempPerm11)?((10 * fTempPerm49) + 40):50)):50):((iTempPerm9)?(fTempPerm67 + 50):70)):((iTempPerm8)?(70 - (30 * fTempPerm52)):40)):((iTempPerm7)?((30 * fTempPerm53) + 40):70)):((iTempPerm54)?(70 - (30 * fTempPerm55)):40)) / fTempPerm58);
			fTempPerm69 = (((fTempPerm60 + fTempPerm68) / fTempPerm59) + 1);
			fRec0[0] = (fTempPerm5 - (((fRec0[2] * (((fTempPerm60 - fTempPerm68) / fTempPerm59) + 1)) + (2 * (fRec0[1] * (1 - (1.0f / faustpower<2>(fTempPerm59)))))) / fTempPerm69));
			fTempPerm70 = ((0.003666666666666667f * (400 - fTempPerm57)) + 3);
			fTempPerm71 = ((iTempPerm7)?((iTempPerm8)?((iTempPerm9)?((iTempPerm10)?((iTempPerm11)?((iTempPerm12)?((iTempPerm13)?((iTempPerm14)?((iTempPerm15)?((iTempPerm16)?((iTempPerm17)?((iTempPerm18)?((iTempPerm19)?((iTempPerm20)?((iTempPerm21)?((iTempPerm22)?((iTempPerm23)?((iTempPerm24)?((iTempPerm25)?((iTempPerm26)?((iTempPerm27)?((iTempPerm28)?((iTempPerm29)?((iTempPerm30)?1150:((iTempPerm29)?((450 * fTempPerm6) + 1150):1600)):((iTempPerm28)?((100 * fTempPerm31) + 1600):1700)):((iTempPerm27)?(1700 - (900 * fTempPerm32)):800)):((iTempPerm26)?(800 - (100 * fTempPerm33)):700)):((iTempPerm25)?((340 * fTempPerm34) + 700):1040)):((iTempPerm24)?((580 * fRec6[0]) + 1040):1620)):((iTempPerm23)?((130 * fTempPerm35) + 1620):1750)):((iTempPerm22)?(1750 - (1000 * fTempPerm36)):750)):((iTempPerm21)?(750 - (150 * fTempPerm37)):600)):((iTempPerm20)?((520 * fTempPerm39) + 600):1120)):((iTempPerm19)?((680 * fTempPerm40) + 1120):1800)):((iTempPerm18)?((50 * fTempPerm41) + 1800):1850)):((iTempPerm17)?(1850 - (1030 * fTempPerm42)):820)):((iTempPerm16)?(820 - (190 * fTempPerm43)):630)):((iTempPerm15)?((520 * fTempPerm44) + 630):1150)):((iTempPerm14)?((850 * fTempPerm45) + 1150):2000)):((iTempPerm13)?((140 * fTempPerm46) + 2000):2140)):((iTempPerm12)?(2140 - (1340 * fTempPerm48)):800)):((iTempPerm11)?(800 - (100 * fTempPerm49)):700)):((iTempPerm10)?((380 * fTempPerm50) + 700):1080)):((iTempPerm9)?((620 * fTempPerm51) + 1080):1700)):((iTempPerm8)?((170 * fTempPerm52) + 1700):1870)):((iTempPerm7)?(1870 - (1070 * fTempPerm53)):800)):((iTempPerm54)?(800 - (200 * fTempPerm55)):600));
			fTempPerm72 = ((2 * fTempPerm57) + 30);
			fTempPerm73 = ((int(((fTempPerm71 >= 1300) & (fTempPerm57 >= 200))))?(fTempPerm71 - (0.00095238095238095238f * ((fTempPerm57 + -200) * (fTempPerm71 + -1300)))):((int((fTempPerm71 <= fTempPerm72)))?fTempPerm72:fTempPerm71));
			fTempPerm74 = tanf((fConst7 * fTempPerm73));
			fTempPerm75 = (1.0f / fTempPerm74);
			fTempPerm76 = (10 * fRec6[0]);
			fTempPerm77 = (10 * fTempPerm39);
			fTempPerm78 = (10 * fTempPerm51);
			fTempPerm79 = (10 * fTempPerm53);
			fTempPerm80 = (((iTempPerm7)?((iTempPerm8)?((iTempPerm9)?((iTempPerm10)?((iTempPerm11)?((iTempPerm12)?((iTempPerm13)?((iTempPerm14)?((iTempPerm15)?((iTempPerm16)?((iTempPerm17)?((iTempPerm18)?((iTempPerm19)?((iTempPerm20)?((iTempPerm21)?((iTempPerm22)?((iTempPerm23)?((iTempPerm24)?((iTempPerm25)?((iTempPerm26)?((iTempPerm27)?((iTempPerm28)?((iTempPerm29)?((iTempPerm30)?90:((iTempPerm29)?(90 - (10 * fTempPerm6)):80)):((iTempPerm28)?((20 * fTempPerm31) + 80):100)):((iTempPerm27)?(100 - fTempPerm62):80)):((iTempPerm26)?(80 - fTempPerm63):60)):((iTempPerm25)?(fTempPerm64 + 60):70)):((iTempPerm24)?(fTempPerm76 + 70):80)):((iTempPerm23)?((10 * fTempPerm35) + 80):90)):((iTempPerm22)?(90 - (10 * fTempPerm36)):80)):80):((iTempPerm20)?(fTempPerm77 + 80):90)):((iTempPerm19)?(90 - fTempPerm65):80)):((iTempPerm18)?((10 * fTempPerm41) + 80):90)):((iTempPerm17)?(90 - (10 * fTempPerm42)):80)):((iTempPerm16)?(80 - (20 * fTempPerm43)):60)):((iTempPerm15)?((30 * fTempPerm44) + 60):90)):((iTempPerm14)?((10 * fTempPerm45) + 90):100)):((iTempPerm13)?(100 - (10 * fTempPerm46)):90)):((iTempPerm12)?(90 - (10 * fTempPerm48)):80)):((iTempPerm11)?(80 - (20 * fTempPerm49)):60)):((iTempPerm10)?((30 * fTempPerm50) + 60):90)):((iTempPerm9)?(90 - fTempPerm78):80)):((iTempPerm8)?((10 * fTempPerm52) + 80):90)):((iTempPerm7)?(90 - fTempPerm79):80)):((iTempPerm54)?(80 - (20 * fTempPerm55)):60)) / fTempPerm73);
			fTempPerm81 = (((fTempPerm75 + fTempPerm80) / fTempPerm74) + 1);
			fRec10[0] = (fTempPerm5 - (((fRec10[2] * (((fTempPerm75 - fTempPerm80) / fTempPerm74) + 1)) + (2 * (fRec10[1] * (1 - (1.0f / faustpower<2>(fTempPerm74)))))) / fTempPerm81));
			fTempPerm82 = ((iTempPerm7)?((iTempPerm8)?((iTempPerm9)?((iTempPerm10)?((iTempPerm11)?((iTempPerm12)?((iTempPerm13)?((iTempPerm14)?((iTempPerm15)?((iTempPerm16)?((iTempPerm17)?((iTempPerm18)?((iTempPerm19)?((iTempPerm20)?((iTempPerm21)?((iTempPerm22)?((iTempPerm23)?((iTempPerm24)?((iTempPerm25)?((iTempPerm26)?((iTempPerm27)?((iTempPerm28)?((iTempPerm29)?((iTempPerm30)?0.63095699999999999f:((iTempPerm29)?(0.63095699999999999f - (0.56786099999999995f * fTempPerm6)):0.063095999999999999f)):((iTempPerm28)?((0.036904000000000006f * fTempPerm31) + 0.063095999999999999f):0.10000000000000001f)):((iTempPerm27)?((0.25481299999999996f * fTempPerm32) + 0.10000000000000001f):0.35481299999999999f)):((iTempPerm26)?(0.35481299999999999f - (0.10362399999999999f * fTempPerm33)):0.251189f)):((iTempPerm25)?((0.19549500000000003f * fTempPerm34) + 0.251189f):0.44668400000000003f)):((iTempPerm24)?(0.44668400000000003f - (0.19549500000000003f * fRec6[0])):0.251189f)):((iTempPerm23)?(0.251189f - (0.21956599999999998f * fTempPerm35)):0.031622999999999998f)):((iTempPerm22)?((0.25021499999999997f * fTempPerm36) + 0.031622999999999998f):0.28183799999999998f)):((iTempPerm21)?(0.28183799999999998f - (0.18183799999999997f * fTempPerm37)):0.10000000000000001f)):((iTempPerm20)?((0.40118700000000007f * fTempPerm39) + 0.10000000000000001f):0.50118700000000005f)):((iTempPerm19)?(0.50118700000000005f - (0.30166100000000007f * fTempPerm40)):0.19952600000000001f)):((iTempPerm18)?(0.19952600000000001f - (0.13643f * fTempPerm41)):0.063095999999999999f)):((iTempPerm17)?((0.25313200000000002f * fTempPerm42) + 0.063095999999999999f):0.31622800000000001f)):((iTempPerm16)?(0.31622800000000001f - (0.216228f * fTempPerm43)):0.10000000000000001f)):((iTempPerm15)?((0.40118700000000007f * fTempPerm44) + 0.10000000000000001f):0.50118700000000005f)):((iTempPerm14)?(0.50118700000000005f - (0.40118700000000007f * fTempPerm45)):0.10000000000000001f)):((iTempPerm13)?((0.15118899999999999f * fTempPerm46) + 0.10000000000000001f):0.251189f)):((iTempPerm12)?((0.030648999999999982f * fTempPerm48) + 0.251189f):0.28183799999999998f)):((iTempPerm11)?(0.28183799999999998f - (0.12334899999999999f * fTempPerm49)):0.15848899999999999f)):((iTempPerm10)?((0.34269800000000006f * fTempPerm50) + 0.15848899999999999f):0.50118700000000005f)):((iTempPerm9)?(0.50118700000000005f - (0.30166100000000007f * fTempPerm51)):0.19952600000000001f)):((iTempPerm8)?(0.19952600000000001f - (0.021697999999999995f * fTempPerm52)):0.17782800000000001f)):((iTempPerm7)?((0.1384f * fTempPerm53) + 0.17782800000000001f):0.31622800000000001f)):((iTempPerm54)?(0.31622800000000001f - (0.216228f * fTempPerm55)):0.10000000000000001f));
			fTempPerm83 = (50 * fTempPerm40);
			fTempPerm84 = (50 * fTempPerm50);
			fTempPerm85 = (100 * fTempPerm55);
			fTempPerm86 = ((iTempPerm7)?((iTempPerm8)?((iTempPerm9)?((iTempPerm10)?((iTempPerm11)?((iTempPerm12)?((iTempPerm13)?((iTempPerm14)?((iTempPerm15)?((iTempPerm16)?((iTempPerm17)?((iTempPerm18)?((iTempPerm19)?((iTempPerm20)?((iTempPerm21)?((iTempPerm22)?((iTempPerm23)?((iTempPerm24)?((iTempPerm25)?((iTempPerm26)?((iTempPerm27)?((iTempPerm28)?((iTempPerm29)?((iTempPerm30)?2800:((iTempPerm29)?(2800 - (100 * fTempPerm6)):2700)):2700):((iTempPerm27)?((130 * fTempPerm32) + 2700):2830)):((iTempPerm26)?(2830 - (300 * fTempPerm33)):2530)):((iTempPerm25)?(2530 - (280 * fTempPerm34)):2250)):((iTempPerm24)?((150 * fRec6[0]) + 2250):2400)):((iTempPerm23)?((200 * fTempPerm35) + 2400):2600)):((iTempPerm22)?(2600 - (200 * fTempPerm36)):2400)):2400):((iTempPerm20)?((350 * fTempPerm39) + 2400):2750)):((iTempPerm19)?(2750 - fTempPerm83):2700)):((iTempPerm18)?((200 * fTempPerm41) + 2700):2900)):((iTempPerm17)?(2900 - (200 * fTempPerm42)):2700)):((iTempPerm16)?((50 * fTempPerm43) + 2700):2750)):((iTempPerm15)?((150 * fTempPerm44) + 2750):2900)):((iTempPerm14)?(2900 - (100 * fTempPerm45)):2800)):((iTempPerm13)?((150 * fTempPerm46) + 2800):2950)):((iTempPerm12)?(2950 - (120 * fTempPerm48)):2830)):((iTempPerm11)?(2830 - (130 * fTempPerm49)):2700)):((iTempPerm10)?(2700 - fTempPerm84):2650)):((iTempPerm9)?(2650 - (50 * fTempPerm51)):2600)):((iTempPerm8)?((200 * fTempPerm52) + 2600):2800)):((iTempPerm7)?(2800 - (200 * fTempPerm53)):2600)):((iTempPerm54)?(fTempPerm85 + 2600):2700));
			fTempPerm87 = tanf((fConst7 * fTempPerm86));
			fTempPerm88 = (1.0f / fTempPerm87);
			fTempPerm89 = (60 * fTempPerm34);
			fTempPerm90 = (20 * fTempPerm39);
			fTempPerm91 = (20 * fTempPerm40);
			fTempPerm92 = (20 * fTempPerm44);
			fTempPerm93 = (((iTempPerm7)?((iTempPerm8)?((iTempPerm9)?((iTempPerm10)?((iTempPerm11)?((iTempPerm12)?((iTempPerm13)?((iTempPerm14)?((iTempPerm15)?((iTempPerm16)?((iTempPerm17)?((iTempPerm18)?((iTempPerm19)?((iTempPerm20)?((iTempPerm21)?((iTempPerm22)?((iTempPerm23)?((iTempPerm24)?((iTempPerm25)?((iTempPerm26)?((iTempPerm27)?((iTempPerm28)?120:((iTempPerm27)?(120 - fTempPerm62):100)):((iTempPerm26)?((70 * fTempPerm33) + 100):170)):((iTempPerm25)?(170 - fTempPerm89):110)):((iTempPerm24)?(110 - fTempPerm76):100)):100):100):100):((iTempPerm20)?(fTempPerm90 + 100):120)):((iTempPerm19)?(120 - fTempPerm91):100)):100):100):100):((iTempPerm15)?(fTempPerm92 + 100):120)):120):((iTempPerm13)?(120 - (20 * fTempPerm46)):100)):100):((iTempPerm11)?((70 * fTempPerm49) + 100):170)):((iTempPerm10)?(170 - fTempPerm84):120)):((iTempPerm9)?(120 - fTempPerm67):100)):100):100):100) / fTempPerm86);
			fTempPerm94 = (((fTempPerm88 + fTempPerm93) / fTempPerm87) + 1);
			fRec11[0] = (fTempPerm5 - (((fRec11[2] * (((fTempPerm88 - fTempPerm93) / fTempPerm87) + 1)) + (2 * (fRec11[1] * (1 - (1.0f / faustpower<2>(fTempPerm87)))))) / fTempPerm94));
			fTempPerm95 = ((iTempPerm12)?((0.029314000000000007f * fTempPerm48) + 0.050118999999999997f):0.079433000000000004f);
			fTempPerm96 = ((iTempPerm7)?((iTempPerm8)?((iTempPerm9)?((iTempPerm10)?((iTempPerm11)?((iTempPerm12)?((iTempPerm13)?((iTempPerm14)?((iTempPerm15)?((iTempPerm16)?((iTempPerm17)?((iTempPerm18)?((iTempPerm19)?((iTempPerm20)?((iTempPerm21)?((iTempPerm22)?((iTempPerm23)?((iTempPerm24)?((iTempPerm25)?((iTempPerm26)?((iTempPerm27)?((iTempPerm28)?((iTempPerm29)?((iTempPerm30)?0.10000000000000001f:((iTempPerm29)?(0.10000000000000001f - (0.068377000000000007f * fTempPerm6)):0.031622999999999998f)):0.031622999999999998f):((iTempPerm27)?((0.12686599999999998f * fTempPerm32) + 0.031622999999999998f):0.15848899999999999f)):((iTempPerm26)?(0.15848899999999999f - (0.12686599999999998f * fTempPerm33)):0.031622999999999998f)):((iTempPerm25)?((0.32318999999999998f * fTempPerm34) + 0.031622999999999998f):0.35481299999999999f)):0.35481299999999999f):((iTempPerm23)?(0.35481299999999999f - (0.196324f * fTempPerm35)):0.15848899999999999f)):((iTempPerm22)?(0.15848899999999999f - (0.069363999999999995f * fTempPerm36)):0.089124999999999996f)):((iTempPerm21)?(0.089124999999999996f - (0.064005999999999993f * fTempPerm37)):0.025118999999999999f)):((iTempPerm20)?((0.045675999999999994f * fTempPerm39) + 0.025118999999999999f):0.070794999999999997f)):((iTempPerm19)?((0.055098000000000008f * fTempPerm40) + 0.070794999999999997f):0.125893f)):((iTempPerm18)?(0.125893f - (0.062797000000000006f * fTempPerm41)):0.063095999999999999f)):((iTempPerm17)?(0.063095999999999999f - (0.012977000000000002f * fTempPerm42)):0.050118999999999997f)):((iTempPerm16)?((0.020676f * fTempPerm43) + 0.050118999999999997f):0.070794999999999997f)):((iTempPerm15)?(0.070794999999999997f - (0.045675999999999994f * fTempPerm44)):0.025118999999999999f)):((iTempPerm14)?((0.15270900000000001f * fTempPerm45) + 0.025118999999999999f):0.17782800000000001f)):((iTempPerm13)?(0.17782800000000001f - (0.12770900000000002f * fTempPerm46)):0.050118999999999997f)):fTempPerm95):((iTempPerm11)?(0.079433000000000004f - (0.061650000000000003f * fTempPerm49)):0.017783f)):((iTempPerm10)?((0.42890100000000003f * fTempPerm50) + 0.017783f):0.44668400000000003f)):((iTempPerm9)?(0.44668400000000003f - (0.19549500000000003f * fTempPerm51)):0.251189f)):((iTempPerm8)?(0.251189f - (0.12529599999999999f * fTempPerm52)):0.125893f)):((iTempPerm7)?((0.12529599999999999f * fTempPerm53) + 0.125893f):0.251189f)):((iTempPerm54)?(0.251189f - (0.109935f * fTempPerm55)):0.14125399999999999f));
			fTempPerm97 = (350 * fRec6[0]);
			fTempPerm98 = ((iTempPerm7)?((iTempPerm8)?((iTempPerm9)?((iTempPerm10)?((iTempPerm11)?((iTempPerm12)?((iTempPerm13)?((iTempPerm14)?((iTempPerm15)?((iTempPerm16)?((iTempPerm17)?((iTempPerm18)?((iTempPerm19)?((iTempPerm20)?((iTempPerm21)?((iTempPerm22)?((iTempPerm23)?((iTempPerm24)?((iTempPerm25)?((iTempPerm26)?((iTempPerm27)?((iTempPerm28)?((iTempPerm29)?((iTempPerm30)?3500:((iTempPerm29)?(3500 - (200 * fTempPerm6)):3300)):((iTempPerm28)?((400 * fTempPerm31) + 3300):3700)):((iTempPerm27)?(3700 - (200 * fTempPerm32)):3500)):3500):((iTempPerm25)?(3500 - (1050 * fTempPerm34)):2450)):((iTempPerm24)?(fTempPerm97 + 2450):2800)):((iTempPerm23)?((250 * fTempPerm35) + 2800):3050)):((iTempPerm22)?(3050 - (450 * fTempPerm36)):2600)):((iTempPerm21)?((75 * fTempPerm37) + 2600):2675)):((iTempPerm20)?((325 * fTempPerm39) + 2675):3000)):3000):((iTempPerm18)?((350 * fTempPerm41) + 3000):3350)):((iTempPerm17)?(3350 - (350 * fTempPerm42)):3000)):3000):((iTempPerm15)?((900 * fTempPerm44) + 3000):3900)):((iTempPerm14)?(3900 - (300 * fTempPerm45)):3600)):((iTempPerm13)?((300 * fTempPerm46) + 3600):3900)):((iTempPerm12)?(3900 - (100 * fTempPerm48)):3800)):3800):((iTempPerm10)?(3800 - (900 * fTempPerm50)):2900)):((iTempPerm9)?((300 * fTempPerm51) + 2900):3200)):((iTempPerm8)?((50 * fTempPerm52) + 3200):3250)):((iTempPerm7)?(3250 - (450 * fTempPerm53)):2800)):((iTempPerm54)?(fTempPerm85 + 2800):2900));
			fTempPerm99 = tanf((fConst7 * fTempPerm98));
			fTempPerm100 = (1.0f / fTempPerm99);
			fTempPerm101 = (((iTempPerm7)?((iTempPerm8)?((iTempPerm9)?((iTempPerm10)?((iTempPerm11)?((iTempPerm12)?((iTempPerm13)?((iTempPerm14)?((iTempPerm15)?((iTempPerm16)?((iTempPerm17)?((iTempPerm18)?((iTempPerm19)?((iTempPerm20)?((iTempPerm21)?((iTempPerm22)?((iTempPerm23)?((iTempPerm24)?((iTempPerm25)?((iTempPerm26)?((iTempPerm27)?((iTempPerm28)?((iTempPerm29)?((iTempPerm30)?130:((iTempPerm29)?(fTempPerm61 + 130):150)):150):((iTempPerm27)?(150 - fTempPerm62):130)):((iTempPerm26)?((50 * fTempPerm33) + 130):180)):((iTempPerm25)?(180 - fTempPerm89):120)):120):120):120):120):((iTempPerm20)?(fTempPerm77 + 120):130)):((iTempPerm19)?(130 - fTempPerm65):120)):120):120):120):((iTempPerm15)?((10 * fTempPerm44) + 120):130)):((iTempPerm14)?(fTempPerm66 + 130):150)):((iTempPerm13)?(150 - (30 * fTempPerm46)):120)):120):((iTempPerm11)?((60 * fTempPerm49) + 120):180)):((iTempPerm10)?(180 - fTempPerm84):130)):((iTempPerm9)?(130 - fTempPerm78):120)):120):((iTempPerm7)?(fTempPerm79 + 120):130)):((iTempPerm54)?(130 - (10 * fTempPerm55)):120)) / fTempPerm98);
			fTempPerm102 = (((fTempPerm100 + fTempPerm101) / fTempPerm99) + 1);
			fRec12[0] = (fTempPerm5 - (((fRec12[2] * (((fTempPerm100 - fTempPerm101) / fTempPerm99) + 1)) + (2 * (fRec12[1] * (1 - (1.0f / faustpower<2>(fTempPerm99)))))) / fTempPerm102));
			fTempPerm103 = ((iTempPerm18)?(0.10000000000000001f - (0.084151000000000004f * fTempPerm41)):0.015848999999999999f);
			fTempPerm104 = ((iTempPerm7)?((iTempPerm8)?((iTempPerm9)?((iTempPerm10)?((iTempPerm11)?((iTempPerm12)?((iTempPerm13)?((iTempPerm14)?((iTempPerm15)?((iTempPerm16)?((iTempPerm17)?((iTempPerm18)?((iTempPerm19)?((iTempPerm20)?((iTempPerm21)?((iTempPerm22)?((iTempPerm23)?((iTempPerm24)?((iTempPerm25)?((iTempPerm26)?((iTempPerm27)?((iTempPerm28)?((iTempPerm29)?((iTempPerm30)?0.015848999999999999f:((iTempPerm29)?((0.0019340000000000017f * fTempPerm6) + 0.015848999999999999f):0.017783f)):((iTempPerm28)?(0.017783f - (0.0019340000000000017f * fTempPerm31)):0.015848999999999999f)):((iTempPerm27)?((0.023962000000000001f * fTempPerm32) + 0.015848999999999999f):0.039810999999999999f)):((iTempPerm26)?(0.039810999999999999f - (0.029810999999999997f * fTempPerm33)):0.01f)):((iTempPerm25)?((0.34481299999999998f * fTempPerm34) + 0.01f):0.35481299999999999f)):((iTempPerm24)?(0.35481299999999999f - (0.10362399999999999f * fRec6[0])):0.251189f)):((iTempPerm23)?(0.251189f - (0.17175599999999999f * fTempPerm35)):0.079433000000000004f)):((iTempPerm22)?((0.020567000000000002f * fTempPerm36) + 0.079433000000000004f):0.10000000000000001f)):((iTempPerm21)?(0.10000000000000001f - (0.060189000000000006f * fTempPerm37)):0.039810999999999999f)):((iTempPerm20)?((0.023285f * fTempPerm39) + 0.039810999999999999f):0.063095999999999999f)):((iTempPerm19)?((0.036904000000000006f * fTempPerm40) + 0.063095999999999999f):0.10000000000000001f)):fTempPerm103):((iTempPerm17)?((0.063584000000000002f * fTempPerm42) + 0.015848999999999999f):0.079433000000000004f)):((iTempPerm16)?(0.079433000000000004f - (0.047810000000000005f * fTempPerm43)):0.031622999999999998f)):((iTempPerm15)?((0.068377000000000007f * fTempPerm44) + 0.031622999999999998f):0.10000000000000001f)):((iTempPerm14)?(0.10000000000000001f - (0.090000000000000011f * fTempPerm45)):0.01f)):((iTempPerm13)?((0.040118999999999995f * fTempPerm46) + 0.01f):0.050118999999999997f)):fTempPerm95):((iTempPerm11)?(0.079433000000000004f - (0.069433000000000009f * fTempPerm49)):0.01f)):((iTempPerm10)?((0.38810699999999998f * fTempPerm50) + 0.01f):0.39810699999999999f)):((iTempPerm9)?(0.39810699999999999f - (0.19858099999999998f * fTempPerm51)):0.19952600000000001f)):((iTempPerm8)?(0.19952600000000001f - (0.099526000000000003f * fTempPerm52)):0.10000000000000001f)):((iTempPerm7)?((0.15118899999999999f * fTempPerm53) + 0.10000000000000001f):0.251189f)):((iTempPerm54)?(0.251189f - (0.051662999999999987f * fTempPerm55)):0.19952600000000001f));
			fTempPerm105 = ((iTempPerm7)?((iTempPerm8)?((iTempPerm9)?((iTempPerm10)?((iTempPerm11)?((iTempPerm12)?((iTempPerm13)?((iTempPerm14)?((iTempPerm15)?((iTempPerm16)?((iTempPerm17)?((iTempPerm18)?((iTempPerm19)?((iTempPerm20)?((iTempPerm21)?((iTempPerm22)?((iTempPerm23)?((iTempPerm24)?((iTempPerm25)?((iTempPerm26)?4950:((iTempPerm25)?(4950 - (2200 * fTempPerm34)):2750)):((iTempPerm24)?(fTempPerm97 + 2750):3100)):((iTempPerm23)?((240 * fTempPerm35) + 3100):3340)):((iTempPerm22)?(3340 - (440 * fTempPerm36)):2900)):((iTempPerm21)?(fTempPerm38 + 2900):2950)):((iTempPerm20)?((400 * fTempPerm39) + 2950):3350)):((iTempPerm19)?(3350 - fTempPerm83):3300)):((iTempPerm18)?((290 * fTempPerm41) + 3300):3590)):((iTempPerm17)?(3590 - (290 * fTempPerm42)):3300)):((iTempPerm16)?((100 * fTempPerm43) + 3300):3400)):((iTempPerm15)?((1550 * fTempPerm44) + 3400):4950)):4950):4950):4950):4950):((iTempPerm10)?(4950 - (1700 * fTempPerm50)):3250)):((iTempPerm9)?((330 * fTempPerm51) + 3250):3580)):((iTempPerm8)?(3580 - (40 * fTempPerm52)):3540)):((iTempPerm7)?(3540 - (540 * fTempPerm53)):3000)):((iTempPerm54)?((300 * fTempPerm55) + 3000):3300));
			fTempPerm106 = tanf((fConst7 * fTempPerm105));
			fTempPerm107 = (1.0f / fTempPerm106);
			fTempPerm108 = (((iTempPerm7)?((iTempPerm8)?((iTempPerm9)?((iTempPerm10)?((iTempPerm11)?((iTempPerm12)?((iTempPerm13)?((iTempPerm14)?((iTempPerm15)?((iTempPerm16)?((iTempPerm17)?((iTempPerm18)?((iTempPerm19)?((iTempPerm20)?((iTempPerm21)?((iTempPerm22)?((iTempPerm23)?((iTempPerm24)?((iTempPerm25)?((iTempPerm26)?((iTempPerm27)?((iTempPerm28)?((iTempPerm29)?((iTempPerm30)?140:((iTempPerm29)?((60 * fTempPerm6) + 140):200)):200):((iTempPerm27)?(200 - (65 * fTempPerm32)):135)):((iTempPerm26)?((65 * fTempPerm33) + 135):200)):((iTempPerm25)?(200 - (70 * fTempPerm34)):130)):((iTempPerm24)?(130 - fTempPerm76):120)):120):120):120):((iTempPerm20)?(fTempPerm90 + 120):140)):((iTempPerm19)?(140 - fTempPerm91):120)):120):120):120):((iTempPerm15)?(fTempPerm92 + 120):140)):((iTempPerm14)?((60 * fTempPerm45) + 140):200)):((iTempPerm13)?(200 - fTempPerm47):120)):120):((iTempPerm11)?((80 * fTempPerm49) + 120):200)):((iTempPerm10)?(200 - (60 * fTempPerm50)):140)):((iTempPerm9)?(140 - fTempPerm67):120)):120):((iTempPerm7)?((15 * fTempPerm53) + 120):135)):((iTempPerm54)?(135 - (15 * fTempPerm55)):120)) / fTempPerm105);
			fTempPerm109 = (((fTempPerm107 + fTempPerm108) / fTempPerm106) + 1);
			fRec13[0] = (fTempPerm5 - (((fRec13[2] * (((fTempPerm107 - fTempPerm108) / fTempPerm106) + 1)) + (2 * (fRec13[1] * (1 - (1.0f / faustpower<2>(fTempPerm106)))))) / fTempPerm109));
			fTempPerm110 = ((iTempPerm7)?((iTempPerm8)?((iTempPerm9)?((iTempPerm10)?((iTempPerm11)?((iTempPerm12)?((iTempPerm13)?((iTempPerm14)?((iTempPerm15)?((iTempPerm16)?((iTempPerm17)?((iTempPerm18)?((iTempPerm19)?((iTempPerm20)?((iTempPerm21)?((iTempPerm22)?((iTempPerm23)?((iTempPerm24)?((iTempPerm25)?((iTempPerm26)?((iTempPerm27)?((iTempPerm28)?0.001f:((iTempPerm27)?((0.00077800000000000005f * fTempPerm32) + 0.001f):0.0017780000000000001f)):((iTempPerm26)?(0.0017780000000000001f - (0.001147f * fTempPerm33)):0.00063100000000000005f)):((iTempPerm25)?((0.099368999999999999f * fTempPerm34) + 0.00063100000000000005f):0.10000000000000001f)):((iTempPerm24)?((0.025892999999999999f * fRec6[0]) + 0.10000000000000001f):0.125893f)):((iTempPerm23)?(0.125893f - (0.086082000000000006f * fTempPerm35)):0.039810999999999999f)):((iTempPerm22)?(0.039810999999999999f - (0.029810999999999997f * fTempPerm36)):0.01f)):((iTempPerm21)?((0.0058489999999999983f * fTempPerm37) + 0.01f):0.015848999999999999f)):((iTempPerm20)?(0.015848999999999999f - (0.003259999999999999f * fTempPerm39)):0.012588999999999999f)):((iTempPerm19)?((0.087411000000000003f * fTempPerm40) + 0.012588999999999999f):0.10000000000000001f)):fTempPerm103):((iTempPerm17)?((0.004104f * fTempPerm42) + 0.015848999999999999f):0.019952999999999999f)):0.019952999999999999f):((iTempPerm15)?(0.019952999999999999f - (0.016791f * fTempPerm44)):0.0031619999999999999f)):((iTempPerm14)?(0.0031619999999999999f - (0.0015769999999999998f * fTempPerm45)):0.001585f)):((iTempPerm13)?((0.004725f * fTempPerm46) + 0.001585f):0.0063099999999999996f)):((iTempPerm12)?(0.0063099999999999996f - (0.0031479999999999998f * fTempPerm48)):0.0031619999999999999f)):((iTempPerm11)?(0.0031619999999999999f - (0.0021619999999999999f * fTempPerm49)):0.001f)):((iTempPerm10)?((0.078433000000000003f * fTempPerm50) + 0.001f):0.079433000000000004f)):((iTempPerm9)?((0.020567000000000002f * fTempPerm51) + 0.079433000000000004f):0.10000000000000001f)):((iTempPerm8)?(0.10000000000000001f - (0.068377000000000007f * fTempPerm52)):0.031622999999999998f)):((iTempPerm7)?((0.018495999999999999f * fTempPerm53) + 0.031622999999999998f):0.050118999999999997f)):0.050118999999999997f);
			fTempPerm111 = (((((((fRec0[2] * (0 - (fTempPerm70 / fTempPerm59))) + ((fRec0[0] * fTempPerm70) / fTempPerm59)) / fTempPerm69) + (((fRec10[2] * (0 - ((fTempPerm70 * fTempPerm82) / fTempPerm74))) + (((fRec10[0] * fTempPerm70) * fTempPerm82) / fTempPerm74)) / fTempPerm81)) + (((fRec11[2] * (0 - ((fTempPerm70 * fTempPerm96) / fTempPerm87))) + (((fRec11[0] * fTempPerm70) * fTempPerm96) / fTempPerm87)) / fTempPerm94)) + (((fRec12[2] * (0 - ((fTempPerm70 * fTempPerm104) / fTempPerm99))) + (((fRec12[0] * fTempPerm70) * fTempPerm104) / fTempPerm99)) / fTempPerm102)) + (((fRec13[2] * (0 - ((fTempPerm70 * fTempPerm110) / fTempPerm106))) + (((fRec13[0] * fTempPerm70) * fTempPerm110) / fTempPerm106)) / fTempPerm109));
			output0[i] = (FAUSTFLOAT)fTempPerm111;
			output1[i] = (FAUSTFLOAT)fTempPerm111;
			// post processing
			fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
			fRec12[2] = fRec12[1]; fRec12[1] = fRec12[0];
			fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
			fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
			fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
			fRec9[1] = fRec9[0];
			fRec8[1] = fRec8[0];
			fRec7[1] = fRec7[0];
			fRec6[1] = fRec6[0];
			fRec1[1] = fRec1[0];
			fRec5[1] = fRec5[0];
			fRec4[1] = fRec4[0];
			fRec3[1] = fRec3[0];
			iVec0[1] = iVec0[0];
		}
	}
};


