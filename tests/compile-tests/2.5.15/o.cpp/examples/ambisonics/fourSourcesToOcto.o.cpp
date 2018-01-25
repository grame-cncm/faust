//----------------------------------------------------------
// author: "CICM"
// copyright: "(c)CICM 2013"
// license: "BSD"
// name: "fourSourcesToOcto"
// version: "1.0"
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
	float 	fTempPerm0;
	float 	fConst0;
	float 	fConst1;
	FAUSTFLOAT 	fslider0;
	float 	fRec0[2];
	int 	iTempPerm1;
	int 	iTempPerm2;
	float 	fTempPerm3;
	float 	fTempPerm4;
	float 	fTempPerm5;
	float 	fTempPerm6;
	float 	fTempPerm7;
	FAUSTFLOAT 	fslider1;
	float 	fRec1[2];
	int 	iTempPerm8;
	int 	iTempPerm9;
	float 	fTempPerm10;
	float 	fTempPerm11;
	float 	fTempPerm12;
	float 	fTempPerm13;
	float 	fTempPerm14;
	FAUSTFLOAT 	fslider2;
	float 	fRec2[2];
	int 	iTempPerm15;
	int 	iTempPerm16;
	float 	fTempPerm17;
	float 	fTempPerm18;
	float 	fTempPerm19;
	float 	fTempPerm20;
	float 	fTempPerm21;
	FAUSTFLOAT 	fslider3;
	float 	fRec3[2];
	int 	iTempPerm22;
	int 	iTempPerm23;
	float 	fTempPerm24;
	float 	fTempPerm25;
	float 	fTempPerm26;
	float 	fTempPerm27;
	float 	fTempPerm28;
	float 	fTempPerm29;
	float 	fTempPerm30;
	FAUSTFLOAT 	fslider4;
	float 	fRec4[2];
	float 	fTempPerm31;
	float 	fTempPerm32;
	FAUSTFLOAT 	fslider5;
	float 	fRec5[2];
	float 	fTempPerm33;
	float 	fTempPerm34;
	FAUSTFLOAT 	fslider6;
	float 	fRec6[2];
	float 	fTempPerm35;
	float 	fTempPerm36;
	FAUSTFLOAT 	fslider7;
	float 	fRec7[2];
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
	float 	fTempPerm66;
	float 	fTempPerm67;
	float 	fTempPerm68;
	float 	fTempPerm69;
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
	float 	fTempPerm82;
	float 	fTempPerm83;
	float 	fTempPerm84;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("author", "CICM");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("copyright", "(c)CICM 2013");
		m->declare("hoa.lib/author", "Pierre Guillot");
		m->declare("hoa.lib/copyright", "2012-2013 Guillot, Paris, Colafrancesco, CICM labex art H2H, U. Paris 8");
		m->declare("hoa.lib/name", "High Order Ambisonics library");
		m->declare("license", "BSD");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "fourSourcesToOcto");
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() { return 4; }
	virtual int getNumOutputs() { return 8; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fTempPerm0 = 0;
		fConst0 = expf((0 - (50.0f / min(192000.0f, max(1.0f, (float)fSamplingFreq)))));
		fConst1 = (1.0f - fConst0);
		iTempPerm1 = 0;
		iTempPerm2 = 0;
		fTempPerm3 = 0;
		fTempPerm4 = 0;
		fTempPerm5 = 0;
		fTempPerm6 = 0;
		fTempPerm7 = 0;
		iTempPerm8 = 0;
		iTempPerm9 = 0;
		fTempPerm10 = 0;
		fTempPerm11 = 0;
		fTempPerm12 = 0;
		fTempPerm13 = 0;
		fTempPerm14 = 0;
		iTempPerm15 = 0;
		iTempPerm16 = 0;
		fTempPerm17 = 0;
		fTempPerm18 = 0;
		fTempPerm19 = 0;
		fTempPerm20 = 0;
		fTempPerm21 = 0;
		iTempPerm22 = 0;
		iTempPerm23 = 0;
		fTempPerm24 = 0;
		fTempPerm25 = 0;
		fTempPerm26 = 0;
		fTempPerm27 = 0;
		fTempPerm28 = 0;
		fTempPerm29 = 0;
		fTempPerm30 = 0;
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
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 1.0f;
		fslider1 = 1.0f;
		fslider2 = 1.0f;
		fslider3 = 1.0f;
		fslider4 = 0.0f;
		fslider5 = 0.0f;
		fslider6 = 0.0f;
		fslider7 = 0.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<2; i++) fRec7[i] = 0;
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
		ui_interface->openVerticalBox("fourSourcesToOcto");
		ui_interface->addHorizontalSlider("Angle1", &fslider4, 0.0f, -6.2831853071795862f, 6.2831853071795862f, 0.001f);
		ui_interface->addHorizontalSlider("Angle2", &fslider5, 0.0f, -6.2831853071795862f, 6.2831853071795862f, 0.001f);
		ui_interface->addHorizontalSlider("Angle3", &fslider6, 0.0f, -6.2831853071795862f, 6.2831853071795862f, 0.001f);
		ui_interface->addHorizontalSlider("Angle4", &fslider7, 0.0f, -6.2831853071795862f, 6.2831853071795862f, 0.001f);
		ui_interface->addHorizontalSlider("Radius1", &fslider0, 1.0f, 0.0f, 5.0f, 0.001f);
		ui_interface->addHorizontalSlider("Radius2", &fslider1, 1.0f, 0.0f, 5.0f, 0.001f);
		ui_interface->addHorizontalSlider("Radius3", &fslider2, 1.0f, 0.0f, 5.0f, 0.001f);
		ui_interface->addHorizontalSlider("Radius4", &fslider3, 1.0f, 0.0f, 5.0f, 0.001f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = (fConst1 * float(fslider0));
		float 	fSlow1 = (fConst1 * float(fslider1));
		float 	fSlow2 = (fConst1 * float(fslider2));
		float 	fSlow3 = (fConst1 * float(fslider3));
		float 	fSlow4 = (fConst1 * float(fslider4));
		float 	fSlow5 = (fConst1 * float(fslider5));
		float 	fSlow6 = (fConst1 * float(fslider6));
		float 	fSlow7 = (fConst1 * float(fslider7));
		//zone2b
		//zone3
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* input1 = input[1];
		FAUSTFLOAT* input2 = input[2];
		FAUSTFLOAT* input3 = input[3];
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		FAUSTFLOAT* output2 = output[2];
		FAUSTFLOAT* output3 = output[3];
		FAUSTFLOAT* output4 = output[4];
		FAUSTFLOAT* output5 = output[5];
		FAUSTFLOAT* output6 = output[6];
		FAUSTFLOAT* output7 = output[7];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fTempPerm0 = (float)input0[i];
			fRec0[0] = (fSlow0 + (fConst0 * fRec0[1]));
			iTempPerm1 = (fRec0[0] > 1);
			iTempPerm2 = (fRec0[0] < 1);
			fTempPerm3 = (iTempPerm1 + (fRec0[0] * iTempPerm2));
			fTempPerm4 = ((1.3862943611198906f * (1 - fTempPerm3)) + 1);
			fTempPerm5 = (fTempPerm0 * fTempPerm4);
			fTempPerm6 = (iTempPerm2 + (faustpower<2>(fRec0[0]) * iTempPerm1));
			fTempPerm7 = (float)input1[i];
			fRec1[0] = (fSlow1 + (fConst0 * fRec1[1]));
			iTempPerm8 = (fRec1[0] > 1);
			iTempPerm9 = (fRec1[0] < 1);
			fTempPerm10 = (iTempPerm8 + (fRec1[0] * iTempPerm9));
			fTempPerm11 = ((1.3862943611198906f * (1 - fTempPerm10)) + 1);
			fTempPerm12 = (fTempPerm7 * fTempPerm11);
			fTempPerm13 = (iTempPerm9 + (faustpower<2>(fRec1[0]) * iTempPerm8));
			fTempPerm14 = (float)input2[i];
			fRec2[0] = (fSlow2 + (fConst0 * fRec2[1]));
			iTempPerm15 = (fRec2[0] > 1);
			iTempPerm16 = (fRec2[0] < 1);
			fTempPerm17 = (iTempPerm15 + (fRec2[0] * iTempPerm16));
			fTempPerm18 = ((1.3862943611198906f * (1 - fTempPerm17)) + 1);
			fTempPerm19 = (fTempPerm14 * fTempPerm18);
			fTempPerm20 = (iTempPerm16 + (faustpower<2>(fRec2[0]) * iTempPerm15));
			fTempPerm21 = (float)input3[i];
			fRec3[0] = (fSlow3 + (fConst0 * fRec3[1]));
			iTempPerm22 = (fRec3[0] > 1);
			iTempPerm23 = (fRec3[0] < 1);
			fTempPerm24 = (iTempPerm22 + (fRec3[0] * iTempPerm23));
			fTempPerm25 = ((1.3862943611198906f * (1 - fTempPerm24)) + 1);
			fTempPerm26 = (fTempPerm21 * fTempPerm25);
			fTempPerm27 = (iTempPerm23 + (faustpower<2>(fRec3[0]) * iTempPerm22));
			fTempPerm28 = (0.14285714285714285f * ((((fTempPerm5 / fTempPerm6) + (fTempPerm12 / fTempPerm13)) + (fTempPerm19 / fTempPerm20)) + (fTempPerm26 / fTempPerm27)));
			fTempPerm29 = (2.0f * fTempPerm3);
			fTempPerm30 = ((2.0f * ((fTempPerm3 * (fTempPerm29 > 0)) * (fTempPerm29 <= 1))) + (fTempPerm29 > 1));
			fRec4[0] = (fSlow4 + (fConst0 * fRec4[1]));
			fTempPerm31 = (2.0f * fTempPerm10);
			fTempPerm32 = ((2.0f * ((fTempPerm10 * (fTempPerm31 > 0)) * (fTempPerm31 <= 1))) + (fTempPerm31 > 1));
			fRec5[0] = (fSlow5 + (fConst0 * fRec5[1]));
			fTempPerm33 = (2.0f * fTempPerm17);
			fTempPerm34 = ((2.0f * ((fTempPerm17 * (fTempPerm33 > 0)) * (fTempPerm33 <= 1))) + (fTempPerm33 > 1));
			fRec6[0] = (fSlow6 + (fConst0 * fRec6[1]));
			fTempPerm35 = (2.0f * fTempPerm24);
			fTempPerm36 = ((2.0f * ((fTempPerm24 * (fTempPerm35 > 0)) * (fTempPerm35 <= 1))) + (fTempPerm35 > 1));
			fRec7[0] = (fSlow7 + (fConst0 * fRec7[1]));
			fTempPerm37 = ((((((fTempPerm5 * fTempPerm30) * cosf(fRec4[0])) / fTempPerm6) + (((fTempPerm12 * fTempPerm32) * cosf(fRec5[0])) / fTempPerm13)) + (((fTempPerm19 * fTempPerm34) * cosf(fRec6[0])) / fTempPerm20)) + (((fTempPerm26 * fTempPerm36) * cosf(fRec7[0])) / fTempPerm27));
			fTempPerm38 = (0.21428571428571427f * fTempPerm37);
			fTempPerm39 = (2 * fRec4[0]);
			fTempPerm40 = (1.3862943611198906f * fTempPerm3);
			fTempPerm41 = (fTempPerm40 + -0.69314718055994529f);
			fTempPerm42 = (2.4663034623764308f * fTempPerm41);
			fTempPerm43 = ((2.4663034623764308f * ((fTempPerm41 * (fTempPerm42 > 0)) * (fTempPerm42 <= 1))) + (fTempPerm42 > 1));
			fTempPerm44 = (2 * fRec5[0]);
			fTempPerm45 = (1.3862943611198906f * fTempPerm10);
			fTempPerm46 = (fTempPerm45 + -0.69314718055994529f);
			fTempPerm47 = (2.4663034623764308f * fTempPerm46);
			fTempPerm48 = ((2.4663034623764308f * ((fTempPerm46 * (fTempPerm47 > 0)) * (fTempPerm47 <= 1))) + (fTempPerm47 > 1));
			fTempPerm49 = (2 * fRec6[0]);
			fTempPerm50 = (1.3862943611198906f * fTempPerm17);
			fTempPerm51 = (fTempPerm50 + -0.69314718055994529f);
			fTempPerm52 = (2.4663034623764308f * fTempPerm51);
			fTempPerm53 = ((2.4663034623764308f * ((fTempPerm51 * (fTempPerm52 > 0)) * (fTempPerm52 <= 1))) + (fTempPerm52 > 1));
			fTempPerm54 = (2 * fRec7[0]);
			fTempPerm55 = (1.3862943611198906f * fTempPerm24);
			fTempPerm56 = (fTempPerm55 + -0.69314718055994529f);
			fTempPerm57 = (2.4663034623764308f * fTempPerm56);
			fTempPerm58 = ((2.4663034623764308f * ((fTempPerm56 * (fTempPerm57 > 0)) * (fTempPerm57 <= 1))) + (fTempPerm57 > 1));
			fTempPerm59 = (0.085714285714285701f * (((((((cosf(fTempPerm39) * fTempPerm0) * fTempPerm4) * fTempPerm43) / fTempPerm6) + ((((cosf(fTempPerm44) * fTempPerm7) * fTempPerm11) * fTempPerm48) / fTempPerm13)) + ((((cosf(fTempPerm49) * fTempPerm14) * fTempPerm18) * fTempPerm53) / fTempPerm20)) + ((((cosf(fTempPerm54) * fTempPerm21) * fTempPerm25) * fTempPerm58) / fTempPerm27)));
			fTempPerm60 = (3 * fRec4[0]);
			fTempPerm61 = (fTempPerm40 + -1.0986122886681098f);
			fTempPerm62 = (3.4760594967822085f * fTempPerm61);
			fTempPerm63 = ((3.4760594967822085f * ((fTempPerm61 * (fTempPerm62 > 0)) * (fTempPerm62 <= 1))) + (fTempPerm62 > 1));
			fTempPerm64 = (3 * fRec5[0]);
			fTempPerm65 = (fTempPerm45 + -1.0986122886681098f);
			fTempPerm66 = (3.4760594967822085f * fTempPerm65);
			fTempPerm67 = ((3.4760594967822085f * ((fTempPerm65 * (fTempPerm66 > 0)) * (fTempPerm66 <= 1))) + (fTempPerm66 > 1));
			fTempPerm68 = (3 * fRec6[0]);
			fTempPerm69 = (fTempPerm50 + -1.0986122886681098f);
			fTempPerm70 = (3.4760594967822085f * fTempPerm69);
			fTempPerm71 = ((3.4760594967822085f * ((fTempPerm69 * (fTempPerm70 > 0)) * (fTempPerm70 <= 1))) + (fTempPerm70 > 1));
			fTempPerm72 = (3 * fRec7[0]);
			fTempPerm73 = (fTempPerm55 + -1.0986122886681098f);
			fTempPerm74 = (3.4760594967822085f * fTempPerm73);
			fTempPerm75 = ((3.4760594967822085f * ((fTempPerm73 * (fTempPerm74 > 0)) * (fTempPerm74 <= 1))) + (fTempPerm74 > 1));
			fTempPerm76 = (((((((cosf(fTempPerm60) * fTempPerm0) * fTempPerm4) * fTempPerm63) / fTempPerm6) + ((((cosf(fTempPerm64) * fTempPerm7) * fTempPerm11) * fTempPerm67) / fTempPerm13)) + ((((cosf(fTempPerm68) * fTempPerm14) * fTempPerm18) * fTempPerm71) / fTempPerm20)) + ((((cosf(fTempPerm72) * fTempPerm21) * fTempPerm25) * fTempPerm75) / fTempPerm27));
			fTempPerm77 = (0.014285714285714285f * fTempPerm76);
			output0[i] = (FAUSTFLOAT)(((fTempPerm28 + fTempPerm38) + fTempPerm59) + fTempPerm77);
			fTempPerm78 = ((((((fTempPerm5 * sinf(fRec4[0])) * fTempPerm30) / fTempPerm6) + (((fTempPerm12 * sinf(fRec5[0])) * fTempPerm32) / fTempPerm13)) + (((fTempPerm19 * sinf(fRec6[0])) * fTempPerm34) / fTempPerm20)) + (((fTempPerm26 * sinf(fRec7[0])) * fTempPerm36) / fTempPerm27));
			fTempPerm79 = (0.15152288168283157f * fTempPerm78);
			fTempPerm80 = (0.085714285714285701f * (((((((sinf(fTempPerm39) * fTempPerm0) * fTempPerm4) * fTempPerm43) / fTempPerm6) + ((((sinf(fTempPerm44) * fTempPerm7) * fTempPerm11) * fTempPerm48) / fTempPerm13)) + ((((sinf(fTempPerm49) * fTempPerm14) * fTempPerm18) * fTempPerm53) / fTempPerm20)) + ((((sinf(fTempPerm54) * fTempPerm21) * fTempPerm25) * fTempPerm58) / fTempPerm27)));
			fTempPerm81 = (((((((sinf(fTempPerm60) * fTempPerm0) * fTempPerm4) * fTempPerm63) / fTempPerm6) + ((((sinf(fTempPerm64) * fTempPerm7) * fTempPerm11) * fTempPerm67) / fTempPerm13)) + ((((sinf(fTempPerm68) * fTempPerm14) * fTempPerm18) * fTempPerm71) / fTempPerm20)) + ((((sinf(fTempPerm72) * fTempPerm21) * fTempPerm25) * fTempPerm75) / fTempPerm27));
			output1[i] = (FAUSTFLOAT)(((((fTempPerm28 + fTempPerm79) + (0.15152288168283162f * fTempPerm37)) + fTempPerm80) + (0.010101525445522109f * fTempPerm81)) - (0.010101525445522105f * fTempPerm76));
			fTempPerm82 = (0.21428571428571427f * fTempPerm78);
			fTempPerm83 = (0.014285714285714285f * fTempPerm81);
			output2[i] = (FAUSTFLOAT)((fTempPerm28 + fTempPerm82) - (fTempPerm59 + fTempPerm83));
			fTempPerm84 = (0.15152288168283157f * fTempPerm37);
			output3[i] = (FAUSTFLOAT)((((fTempPerm28 + (0.15152288168283162f * fTempPerm78)) + (0.010101525445522105f * fTempPerm81)) + (0.010101525445522109f * fTempPerm76)) - (fTempPerm80 + fTempPerm84));
			output4[i] = (FAUSTFLOAT)((fTempPerm28 + fTempPerm59) - (fTempPerm38 + fTempPerm77));
			output5[i] = (FAUSTFLOAT)(((fTempPerm28 + fTempPerm80) + (0.010101525445522095f * fTempPerm76)) - ((fTempPerm79 + (0.15152288168283165f * fTempPerm37)) + (0.010101525445522119f * fTempPerm81)));
			output6[i] = (FAUSTFLOAT)((fTempPerm28 + fTempPerm83) - (fTempPerm59 + fTempPerm82));
			output7[i] = (FAUSTFLOAT)((fTempPerm28 + fTempPerm84) - (((fTempPerm80 + (0.15152288168283165f * fTempPerm78)) + (0.010101525445522114f * fTempPerm81)) + (0.0101015254455221f * fTempPerm76)));
			// post processing
			fRec7[1] = fRec7[0];
			fRec6[1] = fRec6[0];
			fRec5[1] = fRec5[0];
			fRec4[1] = fRec4[0];
			fRec3[1] = fRec3[0];
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
		}
	}
};


