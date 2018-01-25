//----------------------------------------------------------
// copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
// license: "MIT"
// name: "KarplusStrong"
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
	FAUSTFLOAT 	fslider0;
	float 	fRec11[2];
	float 	fTempPerm0;
	int 	IOTA;
	float 	fRec7[2048];
	float 	fConst0;
	float 	fConst1;
	float 	fConst2;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fbutton0;
	FAUSTFLOAT 	fslider3;
	float 	fVec0[2];
	int 	iTempPerm1;
	float 	fRec12[2];
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
	FAUSTFLOAT 	fslider4;
	float 	fTempPerm28;
	float 	fTempPerm29;
	float 	fVec1[2048];
	float 	fTempPerm30;
	float 	fTempPerm31;
	float 	fRec3[2];
	float 	fRec0[3];
	float 	fRec1[3];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("description", "Simple call of the Karplus-Strong model for the Faust physical modeling library");
		m->declare("license", "MIT");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "KarplusStrong");
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
		fTempPerm0 = 0;
		fConst0 = min(192000.0f, max(1.0f, (float)fSamplingFreq));
		fConst1 = (0.0088235294117647058f * fConst0);
		fConst2 = (0.0014705882352941176f * fConst0);
		iTempPerm1 = 0;
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
		fTempPerm30 = 0;
		fTempPerm31 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.01f;
		fslider1 = 440.0f;
		fslider2 = 1.0f;
		fbutton0 = 0.0;
		fslider3 = 0.0f;
		fslider4 = 0.80000000000000004f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fRec11[i] = 0;
		IOTA = 0;
		for (int i=0; i<2048; i++) fRec7[i] = 0;
		for (int i=0; i<2; i++) fVec0[i] = 0;
		for (int i=0; i<2; i++) fRec12[i] = 0;
		for (int i=0; i<2048; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<3; i++) fRec0[i] = 0;
		for (int i=0; i<3; i++) fRec1[i] = 0;
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
		ui_interface->openVerticalBox("karplus");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("params");
		ui_interface->declare(&fslider1, "0", "");
		ui_interface->declare(&fslider1, "style", "knob");
		ui_interface->addHorizontalSlider("freq", &fslider1, 440.0f, 50.0f, 1000.0f, 0.01f);
		ui_interface->declare(&fslider2, "1", "");
		ui_interface->declare(&fslider2, "hidden", "1");
		ui_interface->declare(&fslider2, "midi", "pitchwheel");
		ui_interface->declare(&fslider2, "style", "knob");
		ui_interface->addHorizontalSlider("bend", &fslider2, 1.0f, 0.0f, 10.0f, 0.01f);
		ui_interface->declare(&fslider0, "1", "");
		ui_interface->declare(&fslider0, "midi", "ctrl 1");
		ui_interface->declare(&fslider0, "style", "knob");
		ui_interface->addHorizontalSlider("damping", &fslider0, 0.01f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider4, "2", "");
		ui_interface->declare(&fslider4, "style", "knob");
		ui_interface->addHorizontalSlider("gain", &fslider4, 0.80000000000000004f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider3, "3", "");
		ui_interface->declare(&fslider3, "hidden", "1");
		ui_interface->declare(&fslider3, "midi", "ctrl 64");
		ui_interface->declare(&fslider3, "style", "knob");
		ui_interface->addHorizontalSlider("sustain", &fslider3, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->declare(&fbutton0, "1", "");
		ui_interface->addButton("gate", &fbutton0);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = (0.0010000000000000009f * float(fslider0));
		float 	fSlow1 = (float(340) / float(fslider1));
		float 	fSlow2 = float(fslider2);
		float 	fSlow3 = min((float)1, (float(fbutton0) + float(fslider3)));
		int 	iSlow4 = (fSlow3 == 0);
		float 	fSlow5 = float(fslider4);
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fRec11[0] = (fSlow0 + (0.999f * fRec11[1]));
			fTempPerm0 = (0.5f * ((fRec1[1] + fRec1[2]) * ((0.20000000000000001f * (1 - fRec11[0])) + 0.80000000000000004f)));
			fRec7[IOTA&2047] = fTempPerm0;
			fVec0[0] = fSlow3;
			iTempPerm1 = ((fSlow3 == fVec0[1]) | iSlow4);
			fRec12[0] = ((fSlow2 * (1.0f - (0.999f * iTempPerm1))) + (0.999f * (iTempPerm1 * fRec12[1])));
			fTempPerm2 = (fConst2 * ((fSlow1 / fRec12[0]) + -0.050000000000000003f));
			fTempPerm3 = (fTempPerm2 + -1.499995f);
			iTempPerm4 = int(fTempPerm3);
			iTempPerm5 = int((int(min(fConst1, (float)max(0, (int)iTempPerm4))) + 1));
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
			iTempPerm16 = int((int(min(fConst1, (float)max(0, (int)(iTempPerm4 + 2)))) + 1));
			fTempPerm17 = (0 - fTempPerm11);
			fTempPerm18 = (0 - (0.5f * fTempPerm13));
			iTempPerm19 = int((int(min(fConst1, (float)max(0, (int)(iTempPerm4 + 1)))) + 1));
			fTempPerm20 = (0 - fTempPerm9);
			fTempPerm21 = (0 - (0.5f * fTempPerm11));
			fTempPerm22 = (0 - (0.33333333333333331f * fTempPerm13));
			fTempPerm23 = (fTempPerm7 * fTempPerm9);
			iTempPerm24 = int((int(min(fConst1, (float)max(0, (int)(iTempPerm4 + 3)))) + 1));
			fTempPerm25 = (0 - fTempPerm13);
			fTempPerm26 = (fTempPerm23 * fTempPerm11);
			iTempPerm27 = int((int(min(fConst1, (float)max(0, (int)(iTempPerm4 + 4)))) + 1));
			float 	fRec8 = (((((fRec7[(IOTA-iTempPerm5)&2047] * fTempPerm8) * fTempPerm10) * fTempPerm12) * fTempPerm14) + (fTempPerm15 * ((((0.5f * (((fTempPerm7 * fRec7[(IOTA-iTempPerm16)&2047]) * fTempPerm17) * fTempPerm18)) + (((fRec7[(IOTA-iTempPerm19)&2047] * fTempPerm20) * fTempPerm21) * fTempPerm22)) + (0.16666666666666666f * ((fTempPerm23 * fRec7[(IOTA-iTempPerm24)&2047]) * fTempPerm25))) + (0.041666666666666664f * (fTempPerm26 * fRec7[(IOTA-iTempPerm27)&2047])))));
			fTempPerm28 = (fSlow5 * ((fSlow3 - fVec0[1]) > 0));
			fTempPerm29 = (fRec0[2] + fTempPerm28);
			fVec1[IOTA&2047] = fTempPerm29;
			fTempPerm30 = ((((fTempPerm8 * fTempPerm10) * fTempPerm12) * fTempPerm14) * fVec1[(IOTA-iTempPerm5)&2047]);
			fTempPerm31 = (fTempPerm15 * (((0.16666666666666666f * ((fTempPerm23 * fTempPerm25) * fVec1[(IOTA-iTempPerm24)&2047])) + ((((fTempPerm20 * fTempPerm21) * fTempPerm22) * fVec1[(IOTA-iTempPerm19)&2047]) + (0.5f * (((fTempPerm7 * fTempPerm17) * fTempPerm18) * fVec1[(IOTA-iTempPerm16)&2047])))) + (0.041666666666666664f * (fTempPerm26 * fVec1[(IOTA-iTempPerm27)&2047]))));
			float 	fRec9 = (fTempPerm30 + fTempPerm31);
			float 	fRec10 = ((fTempPerm0 + fTempPerm30) + fTempPerm31);
			fRec3[0] = fRec8;
			float 	fRec4 = (fTempPerm28 + fRec3[1]);
			float 	fRec5 = fRec9;
			float 	fRec6 = fRec10;
			fRec0[0] = fRec4;
			fRec1[0] = fRec5;
			float 	fRec2 = fRec6;
			output0[i] = (FAUSTFLOAT)fRec2;
			output1[i] = (FAUSTFLOAT)fRec2;
			// post processing
			fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
			fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
			fRec3[1] = fRec3[0];
			fRec12[1] = fRec12[0];
			fVec0[1] = fVec0[0];
			IOTA = IOTA+1;
			fRec11[1] = fRec11[0];
		}
	}
};


