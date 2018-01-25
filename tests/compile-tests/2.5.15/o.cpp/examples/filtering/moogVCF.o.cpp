//----------------------------------------------------------
// name: "moogVCF"
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
	FAUSTFLOAT 	fcheckbox0;
	float 	fTempPerm0;
	FAUSTFLOAT 	fslider0;
	float 	fRec0[2];
	FAUSTFLOAT 	fcheckbox1;
	FAUSTFLOAT 	fcheckbox2;
	float 	fTempPerm1;
	FAUSTFLOAT 	fslider1;
	float 	fConst0;
	float 	fConst1;
	FAUSTFLOAT 	fslider2;
	float 	fRec1[2];
	float 	fTempPerm2;
	float 	fTempPerm3;
	float 	fTempPerm4;
	float 	fTempPerm5;
	float 	fTempPerm6;
	float 	fTempPerm7;
	float 	fTempPerm8;
	float 	fTempPerm9;
	float 	fTempPerm10;
	float 	fTempPerm11;
	float 	fTempPerm12;
	float 	fTempPerm13;
	float 	fTempPerm14;
	float 	fRec4[2];
	float 	fRec2[2];
	float 	fTempPerm15;
	float 	fTempPerm16;
	float 	fTempPerm17;
	float 	fTempPerm18;
	float 	fTempPerm19;
	float 	fTempPerm20;
	float 	fTempPerm21;
	float 	fTempPerm22;
	float 	fTempPerm23;
	float 	fTempPerm24;
	float 	fTempPerm25;
	float 	fTempPerm26;
	float 	fTempPerm27;
	float 	fRec7[2];
	float 	fRec5[2];
	float 	fTempPerm28;
	float 	fTempPerm29;
	float 	fTempPerm30;
	float 	fTempPerm31;
	float 	fTempPerm32;
	float 	fTempPerm33;
	float 	fRec9[3];
	float 	fTempPerm34;
	float 	fRec8[3];
	float 	fConst2;
	float 	fRec15[2];
	float 	fTempPerm35;
	float 	fTempPerm36;
	float 	fRec14[2];
	float 	fRec13[2];
	float 	fRec12[2];
	float 	fRec11[2];
	float 	fRec10[2];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("description", "Exercise and compare three Moog VCF implementations");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "moogVCF");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("vaeffects.lib/name", "Faust Virtual Analog Filter Effect Library");
		m->declare("vaeffects.lib/version", "0.0");
	}

	virtual int getNumInputs() { return 1; }
	virtual int getNumOutputs() { return 1; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fTempPerm0 = 0;
		fTempPerm1 = 0;
		fConst0 = min(192000.0f, max(1.0f, (float)fSamplingFreq));
		fConst1 = (3.1415926535897931f / fConst0);
		fTempPerm2 = 0;
		fTempPerm3 = 0;
		fTempPerm4 = 0;
		fTempPerm5 = 0;
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
		fTempPerm16 = 0;
		fTempPerm17 = 0;
		fTempPerm18 = 0;
		fTempPerm19 = 0;
		fTempPerm20 = 0;
		fTempPerm21 = 0;
		fTempPerm22 = 0;
		fTempPerm23 = 0;
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
		fConst2 = (6.2831853071795862f / fConst0);
		fTempPerm35 = 0;
		fTempPerm36 = 0;
	}
	virtual void instanceResetUserInterface() {
		fcheckbox0 = 0.0;
		fslider0 = 5.0f;
		fcheckbox1 = 0.0;
		fcheckbox2 = 0.0;
		fslider1 = 0.90000000000000002f;
		fslider2 = 25.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fRec7[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<3; i++) fRec9[i] = 0;
		for (int i=0; i<3; i++) fRec8[i] = 0;
		for (int i=0; i<2; i++) fRec15[i] = 0;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		for (int i=0; i<2; i++) fRec13[i] = 0;
		for (int i=0; i<2; i++) fRec12[i] = 0;
		for (int i=0; i<2; i++) fRec11[i] = 0;
		for (int i=0; i<2; i++) fRec10[i] = 0;
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
		ui_interface->declare(0, "tooltip", "See Faust's   vaeffects.lib for info and references");
		ui_interface->openHorizontalBox("MOOG VCF (Voltage Controlled Filter)");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fcheckbox0, "0", "");
		ui_interface->declare(&fcheckbox0, "tooltip", "When this is checked, the Moog VCF   has no effect");
		ui_interface->addCheckButton("Bypass", &fcheckbox0);
		ui_interface->declare(&fcheckbox1, "1", "");
		ui_interface->declare(&fcheckbox1, "tooltip", "Select moog_vcf_2b (two-biquad)   implementation, instead of the default moog_vcf (analog style) implementation");
		ui_interface->addCheckButton("Use Biquads", &fcheckbox1);
		ui_interface->declare(&fcheckbox2, "2", "");
		ui_interface->declare(&fcheckbox2, "tooltip", "If using biquads, make   them normalized ladders (moog_vcf_2bn)");
		ui_interface->addCheckButton("Normalized Ladders", &fcheckbox2);
		ui_interface->closeBox();
		ui_interface->declare(&fslider2, "1", "");
		ui_interface->declare(&fslider2, "tooltip", "The VCF resonates   at the corner frequency (specified in PianoKey (PK) units, with A440 = 49 PK).   The VCF response is flat below the corner frequency, and rolls off -24 dB per   octave above.");
		ui_interface->declare(&fslider2, "unit", "PK");
		ui_interface->addHorizontalSlider("Corner Frequency", &fslider2, 25.0f, 1.0f, 88.0f, 0.01f);
		ui_interface->declare(&fslider1, "2", "");
		ui_interface->declare(&fslider1, "style", "knob");
		ui_interface->declare(&fslider1, "tooltip", "Amount of   resonance near VCF corner frequency (specified between 0 and 1)");
		ui_interface->addHorizontalSlider("Corner Resonance", &fslider1, 0.90000000000000002f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider0, "3", "");
		ui_interface->declare(&fslider0, "style", "knob");
		ui_interface->declare(&fslider0, "tooltip", "output level in decibels");
		ui_interface->declare(&fslider0, "unit", "dB");
		ui_interface->addHorizontalSlider("VCF Output Level", &fslider0, 5.0f, -60.0f, 20.0f, 0.10000000000000001f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		int 	iSlow0 = int(float(fcheckbox0));
		float 	fSlow1 = (0.0010000000000000009f * powf(10,(0.050000000000000003f * float(fslider0))));
		int 	iSlow2 = int(float(fcheckbox1));
		int 	iSlow3 = int(float(fcheckbox2));
		float 	fSlow4 = float(fslider1);
		float 	fSlow5 = (1.9999800000000003f * fSlow4);
		float 	fSlow6 = faustpower<2>((1.4141994202374715f * fSlow4));
		float 	fSlow7 = (fSlow5 + fSlow6);
		float 	fSlow8 = (fSlow5 + 2);
		float 	fSlow9 = (0.44000000000000039f * powf(2.0f,(0.083333333333333329f * (float(fslider2) + -49.0f))));
		float 	fSlow10 = (2 - fSlow5);
		float 	fSlow11 = min(1.4141994202374715f, (1.4142135623730951f * fSlow4));
		float 	fSlow12 = (fSlow11 * (fSlow11 + 1.4142135623730951f));
		float 	fSlow13 = (1.4142135623730951f * fSlow11);
		float 	fSlow14 = (fSlow13 + 2);
		float 	fSlow15 = (fSlow11 * (fSlow11 + -1.4142135623730951f));
		float 	fSlow16 = (2 - fSlow13);
		float 	fSlow17 = (0 - (4.0f * max((float)0, min(faustpower<4>(fSlow4), 0.99999899999999997f))));
		//zone2b
		//zone3
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* output0 = output[0];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fTempPerm0 = (float)input0[i];
			fRec0[0] = (fSlow1 + (0.999f * fRec0[1]));
			fTempPerm1 = ((iSlow0)?0:fTempPerm0);
			fRec1[0] = (fSlow9 + (0.999f * fRec1[1]));
			fTempPerm2 = tanf((fConst1 * max(fRec1[0], (float)20)));
			fTempPerm3 = (1.0f / fTempPerm2);
			fTempPerm4 = (fSlow7 + (((fSlow8 + fTempPerm3) / fTempPerm2) + 1));
			fTempPerm5 = ((fSlow7 + (1 - ((fSlow8 - fTempPerm3) / fTempPerm2))) / fTempPerm4);
			fTempPerm6 = max(-0.99990000000000001f, min(0.99990000000000001f, fTempPerm5));
			fTempPerm7 = (1 - faustpower<2>(fTempPerm6));
			fTempPerm8 = sqrtf(max((float)0, fTempPerm7));
			fTempPerm9 = ((fRec2[1] * (0 - fTempPerm6)) + (fTempPerm1 * fTempPerm8));
			fTempPerm10 = (1 - (1.0f / faustpower<2>(fTempPerm2)));
			fTempPerm11 = (fSlow7 + fTempPerm10);
			fTempPerm12 = max(-0.99990000000000001f, min(0.99990000000000001f, (2 * (fTempPerm11 / (fTempPerm4 * (fTempPerm5 + 1))))));
			fTempPerm13 = (1 - faustpower<2>(fTempPerm12));
			fTempPerm14 = sqrtf(max((float)0, fTempPerm13));
			fRec4[0] = ((fRec4[1] * (0 - fTempPerm12)) + (fTempPerm9 * fTempPerm14));
			fRec2[0] = ((fTempPerm9 * fTempPerm12) + (fRec4[1] * fTempPerm14));
			float 	fRec3 = fRec4[0];
			fTempPerm15 = (1.0f - (fTempPerm11 / fTempPerm4));
			fTempPerm16 = sqrtf(fTempPerm7);
			fTempPerm17 = ((((fTempPerm1 * fTempPerm6) + (fRec2[1] * fTempPerm8)) + (2.0f * ((fRec2[0] * fTempPerm15) / fTempPerm16))) + ((fRec3 * ((1.0f - fTempPerm5) - (2.0f * (fTempPerm12 * fTempPerm15)))) / (fTempPerm16 * sqrtf(fTempPerm13))));
			fTempPerm18 = (fSlow6 + ((((fSlow10 + fTempPerm3) / fTempPerm2) + 1) - fSlow5));
			fTempPerm19 = ((fSlow6 + ((((fTempPerm3 - fSlow10) / fTempPerm2) + 1) - fSlow5)) / fTempPerm18);
			fTempPerm20 = max(-0.99990000000000001f, min(0.99990000000000001f, fTempPerm19));
			fTempPerm21 = (1 - faustpower<2>(fTempPerm20));
			fTempPerm22 = sqrtf(max((float)0, fTempPerm21));
			fTempPerm23 = ((fRec5[1] * (0 - fTempPerm20)) + ((fTempPerm17 * fTempPerm22) / fTempPerm4));
			fTempPerm24 = (fSlow6 + (fTempPerm10 - fSlow5));
			fTempPerm25 = max(-0.99990000000000001f, min(0.99990000000000001f, (2 * (fTempPerm24 / (fTempPerm18 * (fTempPerm19 + 1))))));
			fTempPerm26 = (1 - faustpower<2>(fTempPerm25));
			fTempPerm27 = sqrtf(max((float)0, fTempPerm26));
			fRec7[0] = ((fRec7[1] * (0 - fTempPerm25)) + (fTempPerm23 * fTempPerm27));
			fRec5[0] = ((fTempPerm23 * fTempPerm25) + (fRec7[1] * fTempPerm27));
			float 	fRec6 = fRec7[0];
			fTempPerm28 = (1.0f - (fTempPerm24 / fTempPerm18));
			fTempPerm29 = sqrtf(fTempPerm21);
			fTempPerm30 = tanf((fConst1 * max((float)20, min((float)10000, fRec1[0]))));
			fTempPerm31 = (1.0f / fTempPerm30);
			fTempPerm32 = (1 - (1.0f / faustpower<2>(fTempPerm30)));
			fTempPerm33 = (fSlow12 + (((fSlow14 + fTempPerm31) / fTempPerm30) + 1));
			fRec9[0] = (fTempPerm1 - (((fRec9[2] * (fSlow12 + (((fTempPerm31 - fSlow14) / fTempPerm30) + 1))) + (2 * (fRec9[1] * (fSlow12 + fTempPerm32)))) / fTempPerm33));
			fTempPerm34 = (fSlow15 + (((fSlow16 + fTempPerm31) / fTempPerm30) + 1));
			fRec8[0] = (((fRec9[2] + (fRec9[0] + (2.0f * fRec9[1]))) / fTempPerm33) - (((fRec8[2] * (fSlow15 + (((fTempPerm31 - fSlow16) / fTempPerm30) + 1))) + (2 * ((fSlow15 + fTempPerm32) * fRec8[1]))) / fTempPerm34));
			fRec15[0] = (fSlow9 + (0.999f * fRec15[1]));
			fTempPerm35 = (fConst2 * fRec15[0]);
			fTempPerm36 = (1.0f - fTempPerm35);
			fRec14[0] = ((fSlow17 * fRec10[1]) + (fTempPerm1 + (fTempPerm36 * fRec14[1])));
			fRec13[0] = (fRec14[0] + (fTempPerm36 * fRec13[1]));
			fRec12[0] = (fRec13[0] + (fTempPerm36 * fRec12[1]));
			fRec11[0] = (fRec12[0] + (fRec11[1] * fTempPerm36));
			fRec10[0] = (fRec11[0] * powf(fTempPerm35,4.0f));
			output0[i] = (FAUSTFLOAT)((iSlow0)?fTempPerm0:(fRec0[0] * ((iSlow2)?((iSlow3)?((((((fTempPerm17 * fTempPerm20) / fTempPerm4) + (fRec5[1] * fTempPerm22)) + (2.0f * ((fRec5[0] * fTempPerm28) / fTempPerm29))) + ((fRec6 * ((1.0f - fTempPerm19) - (2.0f * (fTempPerm25 * fTempPerm28)))) / (fTempPerm29 * sqrtf(fTempPerm26)))) / fTempPerm18):((fRec8[2] + (fRec8[0] + (2.0f * fRec8[1]))) / fTempPerm34)):fRec10[0])));
			// post processing
			fRec10[1] = fRec10[0];
			fRec11[1] = fRec11[0];
			fRec12[1] = fRec12[0];
			fRec13[1] = fRec13[0];
			fRec14[1] = fRec14[0];
			fRec15[1] = fRec15[0];
			fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
			fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
			fRec5[1] = fRec5[0];
			fRec7[1] = fRec7[0];
			fRec2[1] = fRec2[0];
			fRec4[1] = fRec4[0];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
		}
	}
};


