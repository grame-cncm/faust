//----------------------------------------------------------
// author: "JOS, revised by RM"
// name: "noiseGate"
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
	float 	fConst0;
	float 	fConst1;
	float 	fConst2;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fslider1;
	float 	fTempPerm1;
	float 	fTempPerm2;
	float 	fTempPerm3;
	float 	fTempPerm4;
	float 	fRec3[2];
	FAUSTFLOAT 	fslider2;
	int 	iTempPerm5;
	int 	iVec0[2];
	FAUSTFLOAT 	fslider3;
	int 	iRec4[2];
	float 	fTempPerm6;
	float 	fTempPerm7;
	float 	fRec1[2];
	float 	fRec0[2];
	FAUSTFLOAT 	fbargraph0;
	float 	fTempPerm8;
	float 	fRec8[2];
	int 	iTempPerm9;
	int 	iVec1[2];
	int 	iRec9[2];
	float 	fTempPerm10;
	float 	fTempPerm11;
	float 	fRec6[2];
	float 	fRec5[2];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "0.0");
		m->declare("author", "JOS, revised by RM");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("description", "Gate demo application.");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("misceffects.lib/name", "Faust Math Library");
		m->declare("misceffects.lib/version", "2.0");
		m->declare("name", "noiseGate");
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
		fConst1 = (1.0f / fConst0);
		fConst2 = (1.0f / float(fConst0));
		fTempPerm1 = 0;
		fTempPerm2 = 0;
		fTempPerm3 = 0;
		fTempPerm4 = 0;
		iTempPerm5 = 0;
		fTempPerm6 = 0;
		fTempPerm7 = 0;
		fTempPerm8 = 0;
		iTempPerm9 = 0;
		fTempPerm10 = 0;
		fTempPerm11 = 0;
	}
	virtual void instanceResetUserInterface() {
		fcheckbox0 = 0.0;
		fslider0 = 10.0f;
		fslider1 = 100.0f;
		fslider2 = -30.0f;
		fslider3 = 200.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) iVec0[i] = 0;
		for (int i=0; i<2; i++) iRec4[i] = 0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fRec8[i] = 0;
		for (int i=0; i<2; i++) iVec1[i] = 0;
		for (int i=0; i<2; i++) iRec9[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
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
		ui_interface->declare(0, "tooltip", "Reference:   http://en.wikipedia.org/wiki/Noise_gate");
		ui_interface->openVerticalBox("GATE");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fcheckbox0, "0", "");
		ui_interface->declare(&fcheckbox0, "tooltip", "When this is checked,   the gate has no effect");
		ui_interface->addCheckButton("Bypass", &fcheckbox0);
		ui_interface->declare(&fbargraph0, "1", "");
		ui_interface->declare(&fbargraph0, "tooltip", "Current gain of the  gate in dB");
		ui_interface->declare(&fbargraph0, "unit", "dB");
		ui_interface->addHorizontalBargraph("Gate Gain", &fbargraph0, -50.0f, 10.0f);
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fslider2, "1", "");
		ui_interface->declare(&fslider2, "style", "knob");
		ui_interface->declare(&fslider2, "tooltip", "When   the signal level falls below the Threshold (expressed in dB), the signal is   muted");
		ui_interface->declare(&fslider2, "unit", "dB");
		ui_interface->addHorizontalSlider("Threshold", &fslider2, -30.0f, -120.0f, 0.0f, 0.10000000000000001f);
		ui_interface->declare(&fslider0, "2", "");
		ui_interface->declare(&fslider0, "scale", "log");
		ui_interface->declare(&fslider0, "style", "knob");
		ui_interface->declare(&fslider0, "tooltip", "Time constant in MICROseconds (1/e smoothing time) for the gate  gain to go (exponentially) from 0 (muted) to 1 (unmuted)");
		ui_interface->declare(&fslider0, "unit", "us");
		ui_interface->addHorizontalSlider("Attack", &fslider0, 10.0f, 10.0f, 10000.0f, 1.0f);
		ui_interface->declare(&fslider3, "3", "");
		ui_interface->declare(&fslider3, "scale", "log");
		ui_interface->declare(&fslider3, "style", "knob");
		ui_interface->declare(&fslider3, "tooltip", "Time in ms to keep the gate open (no muting) after the signal  level falls below the Threshold");
		ui_interface->declare(&fslider3, "unit", "ms");
		ui_interface->addHorizontalSlider("Hold", &fslider3, 200.0f, 1.0f, 1000.0f, 1.0f);
		ui_interface->declare(&fslider1, "4", "");
		ui_interface->declare(&fslider1, "scale", "log");
		ui_interface->declare(&fslider1, "style", "knob");
		ui_interface->declare(&fslider1, "tooltip", "Time constant in ms (1/e smoothing time) for the gain to go  (exponentially) from 1 (unmuted) to 0 (muted)");
		ui_interface->declare(&fslider1, "unit", "ms");
		ui_interface->addHorizontalSlider("Release", &fslider1, 100.0f, 1.0f, 1000.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		int 	iSlow0 = int(float(fcheckbox0));
		float 	fSlow1 = max(fConst2, (9.9999999999999995e-07f * float(fslider0)));
		float 	fSlow2 = max(fConst2, (0.001f * float(fslider1)));
		float 	fSlow3 = expf((0 - (fConst1 / min(fSlow1, fSlow2))));
		float 	fSlow4 = (1.0f - fSlow3);
		float 	fSlow5 = powf(10,(0.050000000000000003f * float(fslider2)));
		int 	iSlow6 = int((fConst0 * max(fConst2, (0.001f * float(fslider3)))));
		float 	fSlow7 = expf((0 - (fConst1 / fSlow2)));
		float 	fSlow8 = expf((0 - (fConst1 / fSlow1)));
		//zone2b
		//zone3
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* input1 = input[1];
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fTempPerm0 = (float)input0[i];
			fTempPerm1 = ((iSlow0)?0:fTempPerm0);
			fTempPerm2 = (float)input1[i];
			fTempPerm3 = ((iSlow0)?0:fTempPerm2);
			fTempPerm4 = fabsf(fTempPerm3);
			fRec3[0] = ((fSlow3 * fRec3[1]) + (fSlow4 * fabsf((fabsf(fTempPerm1) + fTempPerm4))));
			float 	fRec2 = fRec3[0];
			iTempPerm5 = (fRec2 > fSlow5);
			iVec0[0] = iTempPerm5;
			iRec4[0] = max((int)(iSlow6 * (iVec0[0] < iVec0[1])), (int)(iRec4[1] + -1));
			fTempPerm6 = fabsf(max(float(iVec0[0]), (float)(iRec4[0] > 0)));
			fTempPerm7 = ((int((fRec0[1] > fTempPerm6)))?fSlow7:fSlow8);
			fRec1[0] = ((fRec1[1] * fTempPerm7) + (fTempPerm6 * (1.0f - fTempPerm7)));
			fRec0[0] = fRec1[0];
			fbargraph0 = (20 * log10f(fRec0[0]));
			fTempPerm8 = fTempPerm1;
			fRec8[0] = ((fSlow3 * fRec8[1]) + (fSlow4 * fabsf((fabsf(fTempPerm8) + fTempPerm4))));
			float 	fRec7 = fRec8[0];
			iTempPerm9 = (fRec7 > fSlow5);
			iVec1[0] = iTempPerm9;
			iRec9[0] = max((int)(iSlow6 * (iVec1[0] < iVec1[1])), (int)(iRec9[1] + -1));
			fTempPerm10 = fabsf(max(float(iVec1[0]), (float)(iRec9[0] > 0)));
			fTempPerm11 = ((int((fRec5[1] > fTempPerm10)))?fSlow7:fSlow8);
			fRec6[0] = ((fRec6[1] * fTempPerm11) + (fTempPerm10 * (1.0f - fTempPerm11)));
			fRec5[0] = fRec6[0];
			output0[i] = (FAUSTFLOAT)((iSlow0)?fTempPerm0:(fTempPerm8 * fRec5[0]));
			output1[i] = (FAUSTFLOAT)((iSlow0)?fTempPerm2:(fRec5[0] * fTempPerm3));
			// post processing
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			iRec9[1] = iRec9[0];
			iVec1[1] = iVec1[0];
			fRec8[1] = fRec8[0];
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			iRec4[1] = iRec4[0];
			iVec0[1] = iVec0[0];
			fRec3[1] = fRec3[0];
		}
	}
};


