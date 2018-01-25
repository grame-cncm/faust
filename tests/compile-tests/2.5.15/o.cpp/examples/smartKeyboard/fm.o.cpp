//----------------------------------------------------------
// name: "fm"
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
	int 	iVec0[2];
	float 	fConst0;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fbutton0;
	float 	fVec1[2];
	int 	iTempPerm0;
	float 	fRec2[2];
	FAUSTFLOAT 	fslider1;
	float 	fRec5[2];
	float 	fTempPerm1;
	float 	fTempPerm2;
	float 	fTempPerm3;
	float 	fRec3[2];
	int 	iTempPerm4;
	float 	fRec4[2];
	FAUSTFLOAT 	fslider2;
	float 	fRec6[2];
	float 	fTempPerm5;
	float 	fTempPerm6;
	float 	fTempPerm7;
	float 	fRec0[2];
	float 	fRec1[2];
	float 	fRec7[2];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("interface", "SmartKeyboard{  'Number of Keyboards':'1',  'Keyboard 0 - Number of Keys':'1',  'Keyboard 0 - Piano Keyboard':'0',  'Keyboard 0 - Static Mode':'1',  'Keyboard 0 - Send X':'1',  'Keyboard 0 - Send Y':'1' }");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "fm");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("synths.lib/name", "Faust Synthesizer Library");
		m->declare("synths.lib/version", "0.0");
	}

	virtual int getNumInputs() { return 0; }
	virtual int getNumOutputs() { return 1; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = (6.2831853071795862f / min(192000.0f, max(1.0f, (float)fSamplingFreq)));
		iTempPerm0 = 0;
		fTempPerm1 = 0;
		fTempPerm2 = 0;
		fTempPerm3 = 0;
		iTempPerm4 = 0;
		fTempPerm5 = 0;
		fTempPerm6 = 0;
		fTempPerm7 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.0f;
		fbutton0 = 0.0;
		fslider1 = 1.0f;
		fslider2 = 0.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) iVec0[i] = 0;
		for (int i=0; i<2; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
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
		ui_interface->openVerticalBox("fm");
		ui_interface->addButton("gate", &fbutton0);
		ui_interface->declare(&fslider1, "acc", "0 0 -10 0 10");
		ui_interface->addHorizontalSlider("res", &fslider1, 1.0f, 0.0f, 2.0f, 0.01f);
		ui_interface->addHorizontalSlider("x", &fslider0, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("y", &fslider2, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = ((420 * float(fslider0)) + 80);
		float 	fSlow1 = float(fbutton0);
		int 	iSlow2 = (fSlow1 == 0);
		float 	fSlow3 = (0.0010000000000000009f * float(fslider1));
		float 	fSlow4 = (1.0000000000000009f * float(fslider2));
		float 	fSlow5 = (0.0010000000000000009f * fSlow1);
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			iVec0[0] = 1;
			fVec1[0] = fSlow1;
			iTempPerm0 = ((fSlow1 == fVec1[1]) | iSlow2);
			fRec2[0] = ((fSlow0 * (1.0f - (0.999f * iTempPerm0))) + (0.999f * (iTempPerm0 * fRec2[1])));
			fRec5[0] = (fSlow3 + (0.999f * fRec5[1]));
			fTempPerm1 = (fConst0 * (fRec2[0] * fRec5[0]));
			fTempPerm2 = sinf(fTempPerm1);
			fTempPerm3 = cosf(fTempPerm1);
			fRec3[0] = ((fRec4[1] * fTempPerm2) + (fRec3[1] * fTempPerm3));
			iTempPerm4 = (1 - iVec0[1]);
			fRec4[0] = (((fRec4[1] * fTempPerm3) + (fRec3[1] * (0 - fTempPerm2))) + iTempPerm4);
			fRec6[0] = (fSlow4 + (0.999f * fRec6[1]));
			fTempPerm5 = (fConst0 * (fRec2[0] + (fRec3[0] * fRec6[0])));
			fTempPerm6 = sinf(fTempPerm5);
			fTempPerm7 = cosf(fTempPerm5);
			fRec0[0] = ((fRec1[1] * fTempPerm6) + (fRec0[1] * fTempPerm7));
			fRec1[0] = (((fRec1[1] * fTempPerm7) + (fRec0[1] * (0 - fTempPerm6))) + iTempPerm4);
			fRec7[0] = (fSlow5 + (0.999f * fRec7[1]));
			output0[i] = (FAUSTFLOAT)(0.5f * (fRec0[0] * fRec7[0]));
			// post processing
			fRec7[1] = fRec7[0];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
			fRec6[1] = fRec6[0];
			fRec4[1] = fRec4[0];
			fRec3[1] = fRec3[0];
			fRec5[1] = fRec5[0];
			fRec2[1] = fRec2[0];
			fVec1[1] = fVec1[0];
			iVec0[1] = iVec0[0];
		}
	}
};


