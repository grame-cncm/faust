//----------------------------------------------------------
// author: "JOS, revised by RM"
// name: "flanger"
// version: "0.0"
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
	FAUSTFLOAT 	fcheckbox0;
	float 	fTempPerm0;
	FAUSTFLOAT 	fslider0;
	float 	fConst0;
	float 	fConst1;
	FAUSTFLOAT 	fslider1;
	int 	iVec0[2];
	float 	fRec0[2];
	float 	fRec1[2];
	FAUSTFLOAT 	fbargraph0;
	float 	fTempPerm1;
	FAUSTFLOAT 	fcheckbox1;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fslider3;
	float 	fTempPerm2;
	int 	IOTA;
	float 	fVec1[4096];
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT 	fslider5;
	float 	fTempPerm3;
	int 	iTempPerm4;
	float 	fTempPerm5;
	float 	fRec2[2];
	float 	fTempPerm6;
	float 	fTempPerm7;
	float 	fTempPerm8;
	float 	fVec2[4096];
	float 	fTempPerm9;
	int 	iTempPerm10;
	float 	fTempPerm11;
	float 	fRec3[2];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("author", "JOS, revised by RM");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("description", "Flanger effect application.");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "flanger");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("phaflangers.lib/name", "Faust Phaser and Flanger Library");
		m->declare("phaflangers.lib/version", "0.0");
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("version", "0.0");
	}

	virtual int getNumInputs() { return 2; }
	virtual int getNumOutputs() { return 2; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fTempPerm0 = 0;
		fConst0 = min(192000.0f, max(1.0f, (float)fSamplingFreq));
		fConst1 = (6.2831853071795862f / fConst0);
		fTempPerm1 = 0;
		fTempPerm2 = 0;
		fTempPerm3 = 0;
		iTempPerm4 = 0;
		fTempPerm5 = 0;
		fTempPerm6 = 0;
		fTempPerm7 = 0;
		fTempPerm8 = 0;
		fTempPerm9 = 0;
		iTempPerm10 = 0;
		fTempPerm11 = 0;
	}
	virtual void instanceResetUserInterface() {
		fcheckbox0 = 0.0;
		fslider0 = 0.0f;
		fslider1 = 0.5f;
		fcheckbox1 = 0.0;
		fslider2 = 1.0f;
		fslider3 = 0.0f;
		fslider4 = 1.0f;
		fslider5 = 10.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) iVec0[i] = 0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		IOTA = 0;
		for (int i=0; i<4096; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<4096; i++) fVec2[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
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
		ui_interface->declare(0, "tooltip", "Reference: https://ccrma.stanford.edu/~jos/pasp/Flanging.html");
		ui_interface->openVerticalBox("FLANGER");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fcheckbox0, "0", "");
		ui_interface->declare(&fcheckbox0, "tooltip", "When this is checked, the flanger   has no effect");
		ui_interface->addCheckButton("Bypass", &fcheckbox0);
		ui_interface->declare(&fcheckbox1, "1", "");
		ui_interface->addCheckButton("Invert Flange Sum", &fcheckbox1);
		ui_interface->declare(&fbargraph0, "2", "");
		ui_interface->declare(&fbargraph0, "style", "led");
		ui_interface->declare(&fbargraph0, "tooltip", "Display sum of flange delays");
		ui_interface->addHorizontalBargraph("Flange LFO", &fbargraph0, -1.5f, 1.5f);
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fslider1, "1", "");
		ui_interface->declare(&fslider1, "style", "knob");
		ui_interface->declare(&fslider1, "unit", "Hz");
		ui_interface->addHorizontalSlider("Speed", &fslider1, 0.5f, 0.0f, 10.0f, 0.01f);
		ui_interface->declare(&fslider2, "2", "");
		ui_interface->declare(&fslider2, "style", "knob");
		ui_interface->addHorizontalSlider("Depth", &fslider2, 1.0f, 0.0f, 1.0f, 0.001f);
		ui_interface->declare(&fslider3, "3", "");
		ui_interface->declare(&fslider3, "style", "knob");
		ui_interface->addHorizontalSlider("Feedback", &fslider3, 0.0f, -0.999f, 0.999f, 0.001f);
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("Delay Controls");
		ui_interface->declare(&fslider5, "1", "");
		ui_interface->declare(&fslider5, "style", "knob");
		ui_interface->declare(&fslider5, "unit", "ms");
		ui_interface->addHorizontalSlider("Flange Delay", &fslider5, 10.0f, 0.0f, 20.0f, 0.001f);
		ui_interface->declare(&fslider4, "2", "");
		ui_interface->declare(&fslider4, "style", "knob");
		ui_interface->declare(&fslider4, "unit", "ms");
		ui_interface->addHorizontalSlider("Delay Offset", &fslider4, 1.0f, 0.0f, 20.0f, 0.001f);
		ui_interface->closeBox();
		ui_interface->declare(0, "3", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fslider0, "unit", "dB");
		ui_interface->addHorizontalSlider("Flanger Output Level", &fslider0, 0.0f, -60.0f, 10.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		int 	iSlow0 = int(float(fcheckbox0));
		float 	fSlow1 = powf(10,(0.050000000000000003f * float(fslider0)));
		float 	fSlow2 = (fConst1 * float(fslider1));
		float 	fSlow3 = sinf(fSlow2);
		float 	fSlow4 = cosf(fSlow2);
		float 	fSlow5 = (0 - fSlow3);
		float 	fSlow6 = float(fslider2);
		float 	fSlow7 = ((int(float(fcheckbox1)))?(0 - fSlow6):fSlow6);
		float 	fSlow8 = float(fslider3);
		float 	fSlow9 = (0.001f * float(fslider4));
		float 	fSlow10 = (0.00050000000000000001f * float(fslider5));
		//zone2b
		//zone3
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* input1 = input[1];
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fTempPerm0 = (float)input0[i];
			iVec0[0] = 1;
			fRec0[0] = ((fSlow3 * fRec1[1]) + (fSlow4 * fRec0[1]));
			fRec1[0] = (((fSlow4 * fRec1[1]) + (fSlow5 * fRec0[1])) + (1 - iVec0[1]));
			fbargraph0 = (fRec1[0] + fRec0[0]);
			fTempPerm1 = (fSlow1 * ((iSlow0)?0:fTempPerm0));
			fTempPerm2 = ((fSlow8 * fRec2[1]) - fTempPerm1);
			fVec1[IOTA&4095] = fTempPerm2;
			fTempPerm3 = (fConst0 * (fSlow9 + (fSlow10 * (fRec0[0] + 1))));
			iTempPerm4 = int(fTempPerm3);
			fTempPerm5 = floorf(fTempPerm3);
			fRec2[0] = ((fVec1[(IOTA-int(min(2049, max(0, iTempPerm4))))&4095] * (fTempPerm5 + (1 - fTempPerm3))) + ((fTempPerm3 - fTempPerm5) * fVec1[(IOTA-int(min(2049, max(0, (iTempPerm4 + 1)))))&4095]));
			output0[i] = (FAUSTFLOAT)((iSlow0)?fTempPerm0:(0.5f * (fTempPerm1 + (fSlow7 * fRec2[0]))));
			fTempPerm6 = (float)input1[i];
			fTempPerm7 = (fSlow1 * ((iSlow0)?0:fTempPerm6));
			fTempPerm8 = ((fSlow8 * fRec3[1]) - fTempPerm7);
			fVec2[IOTA&4095] = fTempPerm8;
			fTempPerm9 = (fConst0 * (fSlow9 + (fSlow10 * (fRec1[0] + 1))));
			iTempPerm10 = int(fTempPerm9);
			fTempPerm11 = floorf(fTempPerm9);
			fRec3[0] = ((fVec2[(IOTA-int(min(2049, max(0, iTempPerm10))))&4095] * (fTempPerm11 + (1 - fTempPerm9))) + ((fTempPerm9 - fTempPerm11) * fVec2[(IOTA-int(min(2049, max(0, (iTempPerm10 + 1)))))&4095]));
			output1[i] = (FAUSTFLOAT)((iSlow0)?fTempPerm6:(0.5f * (fTempPerm7 + (fSlow7 * fRec3[0]))));
			// post processing
			fRec3[1] = fRec3[0];
			fRec2[1] = fRec2[0];
			IOTA = IOTA+1;
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
			iVec0[1] = iVec0[0];
		}
	}
};


