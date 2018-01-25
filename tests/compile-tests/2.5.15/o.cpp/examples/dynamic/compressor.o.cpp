//----------------------------------------------------------
// author: "JOS, revised by RM"
// name: "compressor"
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
	float 	fTempPerm1;
	float 	fConst0;
	float 	fConst1;
	float 	fConst2;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	float 	fTempPerm2;
	float 	fTempPerm3;
	float 	fTempPerm4;
	FAUSTFLOAT 	fslider3;
	float 	fTempPerm5;
	float 	fRec2[2];
	float 	fRec1[2];
	FAUSTFLOAT 	fslider4;
	float 	fRec0[2];
	float 	fTempPerm6;
	float 	fTempPerm7;
	float 	fTempPerm8;
	float 	fTempPerm9;
	float 	fTempPerm10;
	float 	fRec5[2];
	float 	fRec4[2];
	float 	fRec3[2];
	FAUSTFLOAT 	fbargraph0;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "0.0");
		m->declare("author", "JOS, revised by RM");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("compressors.lib/name", "Faust Compressor Effect Library");
		m->declare("compressors.lib/version", "0.0");
		m->declare("description", "Compressor demo application");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "compressor");
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
		fTempPerm1 = 0;
		fConst0 = min(192000.0f, max(1.0f, (float)fSamplingFreq));
		fConst1 = (2.0f / fConst0);
		fConst2 = (1.0f / fConst0);
		fTempPerm2 = 0;
		fTempPerm3 = 0;
		fTempPerm4 = 0;
		fTempPerm5 = 0;
		fTempPerm6 = 0;
		fTempPerm7 = 0;
		fTempPerm8 = 0;
		fTempPerm9 = 0;
		fTempPerm10 = 0;
	}
	virtual void instanceResetUserInterface() {
		fcheckbox0 = 0.0;
		fslider0 = 40.0f;
		fslider1 = 50.0f;
		fslider2 = 5.0f;
		fslider3 = 500.0f;
		fslider4 = -30.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
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
		ui_interface->declare(0, "tooltip", "Reference:   http://en.wikipedia.org/wiki/Dynamic_range_compression");
		ui_interface->openVerticalBox("COMPRESSOR");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fcheckbox0, "0", "");
		ui_interface->declare(&fcheckbox0, "tooltip", "When this is checked, the compressor   has no effect");
		ui_interface->addCheckButton("Bypass", &fcheckbox0);
		ui_interface->declare(&fbargraph0, "1", "");
		ui_interface->declare(&fbargraph0, "tooltip", "Current gain of  the compressor in dB");
		ui_interface->declare(&fbargraph0, "unit", "dB");
		ui_interface->addHorizontalBargraph("Compressor Gain", &fbargraph0, -50.0f, 10.0f);
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(0, "3", "");
		ui_interface->openHorizontalBox("Compression Control");
		ui_interface->declare(&fslider2, "0", "");
		ui_interface->declare(&fslider2, "style", "knob");
		ui_interface->declare(&fslider2, "tooltip", "A compression Ratio of N means that for each N dB increase in input  signal level above Threshold, the output level goes up 1 dB");
		ui_interface->addHorizontalSlider("Ratio", &fslider2, 5.0f, 1.0f, 20.0f, 0.10000000000000001f);
		ui_interface->declare(&fslider4, "1", "");
		ui_interface->declare(&fslider4, "style", "knob");
		ui_interface->declare(&fslider4, "tooltip", "When the signal level exceeds the Threshold (in dB), its level  is compressed according to the Ratio");
		ui_interface->declare(&fslider4, "unit", "dB");
		ui_interface->addHorizontalSlider("Threshold", &fslider4, -30.0f, -100.0f, 10.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->declare(0, "4", "");
		ui_interface->openHorizontalBox("Compression Response");
		ui_interface->declare(&fslider1, "1", "");
		ui_interface->declare(&fslider1, "scale", "log");
		ui_interface->declare(&fslider1, "style", "knob");
		ui_interface->declare(&fslider1, "unit", "ms");
		ui_interface->addHorizontalSlider("Attack     tooltip: Time constant in ms (1/e smoothing time) for the compression gain  to approach (exponentially) a new lower target level (the compression  `kicking in')]", &fslider1, 50.0f, 1.0f, 1000.0f, 0.10000000000000001f);
		ui_interface->declare(&fslider3, "2", "");
		ui_interface->declare(&fslider3, "scale", "log");
		ui_interface->declare(&fslider3, "style", "knob");
		ui_interface->declare(&fslider3, "tooltip", "Time constant in ms (1/e smoothing time) for the compression gain  to approach (exponentially) a new higher target level (the compression  'releasing')");
		ui_interface->declare(&fslider3, "unit", "ms");
		ui_interface->addHorizontalSlider("Release", &fslider3, 500.0f, 1.0f, 1000.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(&fslider0, "5", "");
		ui_interface->declare(&fslider0, "tooltip", "The compressed-signal output level is increased by this amount  (in dB) to make up for the level lost due to compression");
		ui_interface->declare(&fslider0, "unit", "dB");
		ui_interface->addHorizontalSlider("Makeup Gain", &fslider0, 40.0f, -96.0f, 96.0f, 0.10000000000000001f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		int 	iSlow0 = int(float(fcheckbox0));
		float 	fSlow1 = powf(10,(0.050000000000000003f * float(fslider0)));
		float 	fSlow2 = max(fConst2, (0.001f * float(fslider1)));
		float 	fSlow3 = expf((0 - (fConst1 / fSlow2)));
		float 	fSlow4 = (((1.0f / float(float(fslider2))) + -1.0f) * (1.0f - fSlow3));
		float 	fSlow5 = expf((0 - (fConst2 / max(fConst2, (0.001f * float(fslider3))))));
		float 	fSlow6 = expf((0 - (fConst2 / fSlow2)));
		float 	fSlow7 = float(fslider4);
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
			fTempPerm4 = fabsf((fabsf(fTempPerm1) + fabsf(fTempPerm3)));
			fTempPerm5 = ((int((fRec1[1] > fTempPerm4)))?fSlow5:fSlow6);
			fRec2[0] = ((fRec2[1] * fTempPerm5) + (fTempPerm4 * (1.0f - fTempPerm5)));
			fRec1[0] = fRec2[0];
			fRec0[0] = ((fSlow3 * fRec0[1]) + (fSlow4 * max(((20 * log10f(fRec1[0])) - fSlow7), 0.0f)));
			fTempPerm6 = powf(10,(0.050000000000000003f * fRec0[0]));
			fTempPerm7 = (fTempPerm1 * fTempPerm6);
			output0[i] = (FAUSTFLOAT)((iSlow0)?fTempPerm0:(fSlow1 * fTempPerm7));
			fTempPerm8 = (fTempPerm3 * fTempPerm6);
			fTempPerm9 = fabsf((fabsf(fTempPerm7) + fabsf(fTempPerm8)));
			fTempPerm10 = ((int((fRec4[1] > fTempPerm9)))?fSlow5:fSlow6);
			fRec5[0] = ((fRec5[1] * fTempPerm10) + (fTempPerm9 * (1.0f - fTempPerm10)));
			fRec4[0] = fRec5[0];
			fRec3[0] = ((fSlow3 * fRec3[1]) + (fSlow4 * max(((20 * log10f(fRec4[0])) - fSlow7), 0.0f)));
			fbargraph0 = (20 * log10f(powf(10,(0.050000000000000003f * fRec3[0]))));
			output1[i] = (FAUSTFLOAT)((iSlow0)?fTempPerm2:(fSlow1 * fTempPerm8));
			// post processing
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
		}
	}
};


