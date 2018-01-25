//----------------------------------------------------------
// name: "wahPedal"
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
	FAUSTFLOAT 	fslider0;
	float 	fRec5[2];
	float 	fTempPerm1;
	float 	fTempPerm2;
	float 	fRec4[2];
	float 	fRec3[2];
	float 	fRec2[2];
	float 	fRec1[2];
	float 	fRec0[2];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("description", "Demonstrate the Fourth-Order Wah pedal (similar to the Moog VCF)");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "wahPedal");
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
		fConst0 = (6.2831853071795862f / min(192000.0f, max(1.0f, (float)fSamplingFreq)));
		fTempPerm1 = 0;
		fTempPerm2 = 0;
	}
	virtual void instanceResetUserInterface() {
		fcheckbox0 = 0.0;
		fslider0 = 200.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
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
		ui_interface->declare(0, "tooltip", "Fourth-order wah effect made using moog_vcf");
		ui_interface->openHorizontalBox("WAH4");
		ui_interface->declare(&fcheckbox0, "0", "");
		ui_interface->declare(&fcheckbox0, "tooltip", "When this is checked, the wah pedal has   no effect");
		ui_interface->addCheckButton("Bypass", &fcheckbox0);
		ui_interface->declare(&fslider0, "1", "");
		ui_interface->declare(&fslider0, "scale", "log");
		ui_interface->declare(&fslider0, "tooltip", "wah resonance   frequency in Hz");
		ui_interface->addHorizontalSlider("Resonance Frequency", &fslider0, 200.0f, 100.0f, 2000.0f, 1.0f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		int 	iSlow0 = int(float(fcheckbox0));
		float 	fSlow1 = (0.0010000000000000009f * float(fslider0));
		//zone2b
		//zone3
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* output0 = output[0];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fTempPerm0 = (float)input0[i];
			fRec5[0] = (fSlow1 + (0.999f * fRec5[1]));
			fTempPerm1 = (fConst0 * fRec5[0]);
			fTempPerm2 = (1.0f - fTempPerm1);
			fRec4[0] = ((((iSlow0)?0:fTempPerm0) + (fTempPerm2 * fRec4[1])) - (3.2000000000000002f * fRec0[1]));
			fRec3[0] = (fRec4[0] + (fTempPerm2 * fRec3[1]));
			fRec2[0] = (fRec3[0] + (fTempPerm2 * fRec2[1]));
			fRec1[0] = (fRec2[0] + (fRec1[1] * fTempPerm2));
			fRec0[0] = (fRec1[0] * powf(fTempPerm1,4.0f));
			output0[i] = (FAUSTFLOAT)((iSlow0)?fTempPerm0:(4 * fRec0[0]));
			// post processing
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
		}
	}
};


