//----------------------------------------------------------
// copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
// license: "MIT"
// name: "ElecGuitarMidi"
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
	float 	fConst0;
	float 	fConst1;
	float 	fConst2;
	FAUSTFLOAT 	fslider1;
	float 	fRec29[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT 	fbutton0;
	FAUSTFLOAT 	fslider4;
	float 	fVec0[2];
	int 	iTempPerm0;
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
	float 	fRec25[2];
	float 	fRec31[2];
	float 	fRec33[4];
	int 	IOTA;
	float 	fRec34[2048];
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
	float 	fVec1[2];
	FAUSTFLOAT 	fslider5;
	int 	iRec37[2];
	float 	fConst3;
	float 	fTempPerm54;
	float 	fTempPerm55;
	float 	fTempPerm56;
	float 	fRec36[3];
	float 	fConst4;
	float 	fTempPerm57;
	float 	fVec2[2];
	float 	fTempPerm58;
	float 	fRec38[2];
	float 	fConst5;
	float 	fTempPerm59;
	int 	iTempPerm60;
	float 	fConst6;
	float 	fTempPerm61;
	float 	fTempPerm62;
	float 	fVec3[3];
	float 	fRec32[2048];
	float 	fRec21[2];
	float 	fRec17[2];
	float 	fRec13[2048];
	float 	fRec15[2];
	float 	fRec11[4];
	float 	fRec6[2];
	float 	fRec2[2048];
	float 	fRec0[2];
	float 	fTempPerm63;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("description", "Simple electric guitar model without effect chain.");
		m->declare("envelopes.lib/author", "GRAME");
		m->declare("envelopes.lib/copyright", "GRAME");
		m->declare("envelopes.lib/license", "LGPL with exception");
		m->declare("envelopes.lib/name", "Faust Envelope Library");
		m->declare("envelopes.lib/version", "0.0");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("license", "MIT");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "ElecGuitarMidi");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
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
		fConst1 = (0.0088235294117647058f * fConst0);
		fConst2 = (0.0014705882352941176f * fConst0);
		iTempPerm0 = 0;
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
		fConst3 = (15.707963267948966f / fConst0);
		fTempPerm54 = 0;
		fTempPerm55 = 0;
		fTempPerm56 = 0;
		fConst4 = (0.0040000000000000001f * fConst0);
		fTempPerm57 = 0;
		fTempPerm58 = 0;
		fConst5 = (0.002f * fConst0);
		fTempPerm59 = 0;
		iTempPerm60 = 0;
		fConst6 = (500.0f / fConst0);
		fTempPerm61 = 0;
		fTempPerm62 = 0;
		fTempPerm63 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.5f;
		fslider1 = 0.80000000000000004f;
		fslider2 = 440.0f;
		fslider3 = 1.0f;
		fbutton0 = 0.0;
		fslider4 = 0.0f;
		fslider5 = 0.80000000000000004f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fRec29[i] = 0;
		for (int i=0; i<2; i++) fVec0[i] = 0;
		for (int i=0; i<2; i++) fRec30[i] = 0;
		for (int i=0; i<2; i++) fRec25[i] = 0;
		for (int i=0; i<2; i++) fRec31[i] = 0;
		for (int i=0; i<4; i++) fRec33[i] = 0;
		IOTA = 0;
		for (int i=0; i<2048; i++) fRec34[i] = 0;
		for (int i=0; i<2; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) iRec37[i] = 0;
		for (int i=0; i<3; i++) fRec36[i] = 0;
		for (int i=0; i<2; i++) fVec2[i] = 0;
		for (int i=0; i<2; i++) fRec38[i] = 0;
		for (int i=0; i<3; i++) fVec3[i] = 0;
		for (int i=0; i<2048; i++) fRec32[i] = 0;
		for (int i=0; i<2; i++) fRec21[i] = 0;
		for (int i=0; i<2; i++) fRec17[i] = 0;
		for (int i=0; i<2048; i++) fRec13[i] = 0;
		for (int i=0; i<2; i++) fRec15[i] = 0;
		for (int i=0; i<4; i++) fRec11[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
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
		ui_interface->openVerticalBox("elecGuitar");
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
		ui_interface->declare(&fslider5, "2", "");
		ui_interface->declare(&fslider5, "style", "knob");
		ui_interface->addHorizontalSlider("gain", &fslider5, 0.80000000000000004f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider4, "3", "");
		ui_interface->declare(&fslider4, "hidden", "1");
		ui_interface->declare(&fslider4, "midi", "ctrl 64");
		ui_interface->declare(&fslider4, "style", "knob");
		ui_interface->addHorizontalSlider("sustain", &fslider4, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->declare(&fslider1, "1", "");
		ui_interface->declare(&fslider1, "midi", "ctrl 1");
		ui_interface->addHorizontalSlider("pluckPosition", &fslider1, 0.80000000000000004f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider0, "2", "");
		ui_interface->addHorizontalSlider("outGain", &fslider0, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fbutton0, "3", "");
		ui_interface->addButton("gate", &fbutton0);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = float(fslider0);
		float 	fSlow1 = (0.0010000000000000009f * float(fslider1));
		float 	fSlow2 = float(fslider2);
		float 	fSlow3 = (float(340) / fSlow2);
		float 	fSlow4 = float(fslider3);
		float 	fSlow5 = min((float)1, (float(fbutton0) + float(fslider4)));
		int 	iSlow6 = (fSlow5 == 0);
		float 	fSlow7 = float(fslider5);
		float 	fSlow8 = (fConst3 * fSlow2);
		float 	fSlow9 = (0.00050000000000000001f * fSlow2);
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			float 	fRec10 = (0 - (0.99730529534641577f * ((0.90000000000000002f * fRec11[2]) + (0.049999999999999989f * (fRec11[1] + fRec11[3])))));
			fRec29[0] = (fSlow1 + (0.999f * fRec29[1]));
			fVec0[0] = fSlow5;
			iTempPerm0 = ((fSlow5 == fVec0[1]) | iSlow6);
			fRec30[0] = ((fSlow4 * (1.0f - (0.999f * iTempPerm0))) + (0.999f * (iTempPerm0 * fRec30[1])));
			fTempPerm1 = ((fSlow3 / fRec30[0]) + -0.11f);
			fTempPerm2 = (fConst2 * ((1 - fRec29[0]) * fTempPerm1));
			fTempPerm3 = (fTempPerm2 + -1.499995f);
			iTempPerm4 = int(fTempPerm3);
			iTempPerm5 = int(min(fConst1, (float)max(0, (int)iTempPerm4)));
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
			iTempPerm16 = int(min(fConst1, (float)max(0, (int)(iTempPerm4 + 2))));
			fTempPerm17 = (0 - fTempPerm11);
			fTempPerm18 = (0 - (0.5f * fTempPerm13));
			iTempPerm19 = int(min(fConst1, (float)max(0, (int)(iTempPerm4 + 1))));
			fTempPerm20 = (0 - fTempPerm9);
			fTempPerm21 = (0 - (0.5f * fTempPerm11));
			fTempPerm22 = (0 - (0.33333333333333331f * fTempPerm13));
			fTempPerm23 = (fTempPerm7 * fTempPerm9);
			iTempPerm24 = int(min(fConst1, (float)max(0, (int)(iTempPerm4 + 3))));
			fTempPerm25 = (0 - fTempPerm13);
			fTempPerm26 = (fTempPerm23 * fTempPerm11);
			iTempPerm27 = int(min(fConst1, (float)max(0, (int)(iTempPerm4 + 4))));
			fRec25[0] = (((((fRec2[(IOTA-int((iTempPerm5 + 1)))&2047] * fTempPerm8) * fTempPerm10) * fTempPerm12) * fTempPerm14) + (fTempPerm15 * ((((0.5f * (((fTempPerm7 * fRec2[(IOTA-int((iTempPerm16 + 1)))&2047]) * fTempPerm17) * fTempPerm18)) + (((fRec2[(IOTA-int((iTempPerm19 + 1)))&2047] * fTempPerm20) * fTempPerm21) * fTempPerm22)) + (0.16666666666666666f * ((fTempPerm23 * fRec2[(IOTA-int((iTempPerm24 + 1)))&2047]) * fTempPerm25))) + (0.041666666666666664f * (fTempPerm26 * fRec2[(IOTA-int((iTempPerm27 + 1)))&2047])))));
			fRec31[0] = ((0.050000000000000003f * fRec31[1]) + (0.94999999999999996f * fRec25[1]));
			float 	fRec26 = fRec31[0];
			fRec33[0] = fRec0[1];
			fRec34[IOTA&2047] = (0 - (0.99730529534641577f * ((0.90000000000000002f * fRec33[2]) + (0.049999999999999989f * (fRec33[1] + fRec33[3])))));
			int 	iRec35 = 0;
			fTempPerm28 = (fConst2 * (fRec29[0] * fTempPerm1));
			fTempPerm29 = (fTempPerm28 + -1.499995f);
			iTempPerm30 = int(fTempPerm29);
			iTempPerm31 = int(min(fConst1, (float)max(0, (int)iTempPerm30)));
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
			iTempPerm42 = int(min(fConst1, (float)max(0, (int)(iTempPerm30 + 2))));
			fTempPerm43 = (0 - fTempPerm37);
			fTempPerm44 = (0 - (0.5f * fTempPerm39));
			iTempPerm45 = int(min(fConst1, (float)max(0, (int)(iTempPerm30 + 1))));
			fTempPerm46 = (0 - fTempPerm35);
			fTempPerm47 = (0 - (0.5f * fTempPerm37));
			fTempPerm48 = (0 - (0.33333333333333331f * fTempPerm39));
			fTempPerm49 = (fTempPerm33 * fTempPerm35);
			iTempPerm50 = int(min(fConst1, (float)max(0, (int)(iTempPerm30 + 3))));
			fTempPerm51 = (0 - fTempPerm39);
			fTempPerm52 = (fTempPerm49 * fTempPerm37);
			iTempPerm53 = int(min(fConst1, (float)max(0, (int)(iTempPerm30 + 4))));
			fVec1[0] = (((((fRec34[(IOTA-int((iTempPerm31 + 2)))&2047] * fTempPerm34) * fTempPerm36) * fTempPerm38) * fTempPerm40) + (fTempPerm41 * ((((0.5f * (((fTempPerm33 * fRec34[(IOTA-int((iTempPerm42 + 2)))&2047]) * fTempPerm43) * fTempPerm44)) + (((fRec34[(IOTA-int((iTempPerm45 + 2)))&2047] * fTempPerm46) * fTempPerm47) * fTempPerm48)) + (0.16666666666666666f * ((fTempPerm49 * fRec34[(IOTA-int((iTempPerm50 + 2)))&2047]) * fTempPerm51))) + (0.041666666666666664f * (fTempPerm52 * fRec34[(IOTA-int((iTempPerm53 + 2)))&2047])))));
			iRec37[0] = ((1103515245 * iRec37[1]) + 12345);
			fTempPerm54 = tanf((fSlow8 * fRec30[0]));
			fTempPerm55 = (1.0f / fTempPerm54);
			fTempPerm56 = (((fTempPerm55 + 1.4142135623730949f) / fTempPerm54) + 1);
			fRec36[0] = ((4.6566128752457969e-10f * iRec37[0]) - (((fRec36[2] * (((fTempPerm55 + -1.4142135623730949f) / fTempPerm54) + 1)) + (2 * (fRec36[1] * (1 - (1.0f / faustpower<2>(fTempPerm54)))))) / fTempPerm56));
			fTempPerm57 = faustpower<2>((1 - (fSlow9 * fRec30[0])));
			fVec2[0] = fTempPerm57;
			fTempPerm58 = (fConst4 * fVec2[0]);
			fRec38[0] = ((int((((fSlow5 - fVec0[1]) > 0) > 0)))?0:min(fTempPerm58, ((fRec38[1] + (fConst4 * (fVec2[0] - fVec2[1]))) + 1)));
			fTempPerm59 = (fConst5 * fVec2[0]);
			iTempPerm60 = int((fRec38[0] < fTempPerm59));
			fTempPerm61 = (fSlow7 * (((fRec36[2] + (fRec36[0] + (2.0f * fRec36[1]))) * ((iTempPerm60)?((int((fRec38[0] < 0)))?0:((iTempPerm60)?(fConst6 * (fRec38[0] / fVec2[0])):1)):((int((fRec38[0] < fTempPerm58)))?((fConst6 * ((0 - (fRec38[0] - fTempPerm59)) / fVec2[0])) + 1):0))) / fTempPerm56));
			fTempPerm62 = (fVec1[1] + fTempPerm61);
			fVec3[0] = fTempPerm62;
			fRec32[IOTA&2047] = ((0.050000000000000003f * fRec32[(IOTA-1)&2047]) + (0.94999999999999996f * fVec3[2]));
			float 	fRec27 = (((((fTempPerm8 * fTempPerm10) * fTempPerm12) * fTempPerm14) * fRec32[(IOTA-iTempPerm5)&2047]) + (fTempPerm15 * ((0.041666666666666664f * (fTempPerm26 * fRec32[(IOTA-iTempPerm27)&2047])) + (((((fTempPerm20 * fTempPerm21) * fTempPerm22) * fRec32[(IOTA-iTempPerm19)&2047]) + (0.5f * (((fTempPerm7 * fTempPerm17) * fTempPerm18) * fRec32[(IOTA-iTempPerm16)&2047]))) + (0.16666666666666666f * ((fTempPerm23 * fTempPerm25) * fRec32[(IOTA-iTempPerm24)&2047]))))));
			float 	fRec28 = (fRec21[1] + (iRec35 + fVec3[1]));
			fRec21[0] = fRec26;
			float 	fRec22 = fRec21[1];
			float 	fRec23 = fRec27;
			float 	fRec24 = fRec28;
			fRec17[0] = fRec22;
			float 	fRec18 = (fTempPerm61 + fRec17[1]);
			float 	fRec19 = fRec23;
			float 	fRec20 = fRec24;
			fRec13[IOTA&2047] = fRec18;
			float 	fRec14 = (((((fTempPerm34 * fTempPerm36) * fTempPerm38) * fTempPerm40) * fRec13[(IOTA-int((iTempPerm31 + 1)))&2047]) + (fTempPerm41 * (((0.16666666666666666f * ((fTempPerm49 * fTempPerm51) * fRec13[(IOTA-int((iTempPerm50 + 1)))&2047])) + ((((fTempPerm46 * fTempPerm47) * fTempPerm48) * fRec13[(IOTA-int((iTempPerm45 + 1)))&2047]) + (0.5f * (((fTempPerm33 * fTempPerm43) * fTempPerm44) * fRec13[(IOTA-int((iTempPerm42 + 1)))&2047])))) + (0.041666666666666664f * (fTempPerm52 * fRec13[(IOTA-int((iTempPerm53 + 1)))&2047])))));
			fRec15[0] = fRec19;
			float 	fRec16 = fRec20;
			fRec11[0] = fRec15[1];
			float 	fRec12 = fRec16;
			fRec6[0] = fRec10;
			float 	fRec7 = fRec6[1];
			float 	fRec8 = fRec11[0];
			float 	fRec9 = fRec12;
			fRec2[IOTA&2047] = fRec7;
			float 	fRec3 = fRec14;
			float 	fRec4 = fRec8;
			float 	fRec5 = fRec9;
			fRec0[0] = fRec3;
			float 	fRec1 = fRec5;
			fTempPerm63 = (fSlow0 * fRec1);
			output0[i] = (FAUSTFLOAT)fTempPerm63;
			output1[i] = (FAUSTFLOAT)fTempPerm63;
			// post processing
			fRec0[1] = fRec0[0];
			fRec6[1] = fRec6[0];
			for (int i=3; i>0; i--) fRec11[i] = fRec11[i-1];
			fRec15[1] = fRec15[0];
			fRec17[1] = fRec17[0];
			fRec21[1] = fRec21[0];
			fVec3[2] = fVec3[1]; fVec3[1] = fVec3[0];
			fRec38[1] = fRec38[0];
			fVec2[1] = fVec2[0];
			fRec36[2] = fRec36[1]; fRec36[1] = fRec36[0];
			iRec37[1] = iRec37[0];
			fVec1[1] = fVec1[0];
			IOTA = IOTA+1;
			for (int i=3; i>0; i--) fRec33[i] = fRec33[i-1];
			fRec31[1] = fRec31[0];
			fRec25[1] = fRec25[0];
			fRec30[1] = fRec30[0];
			fVec0[1] = fVec0[0];
			fRec29[1] = fRec29[0];
		}
	}
};


