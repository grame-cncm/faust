//----------------------------------------------------------
// name: "harp"
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
	float 	fConst0;
	float 	fVec0[2];
	FAUSTFLOAT 	fslider0;
	float 	fConst1;
	FAUSTFLOAT 	fslider1;
	int 	iRec2[2];
	FAUSTFLOAT 	fbutton0;
	float 	fVec1[2];
	float 	fConst2;
	float 	fRec3[2];
	float 	fConst3;
	int 	iTempPerm0;
	float 	fTempPerm1;
	int 	IOTA;
	float 	fVec2[2048];
	float 	fRec0[2];
	float 	fRec1[2];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("envelopes.lib/author", "GRAME");
		m->declare("envelopes.lib/copyright", "GRAME");
		m->declare("envelopes.lib/license", "LGPL with exception");
		m->declare("envelopes.lib/name", "Faust Envelope Library");
		m->declare("envelopes.lib/version", "0.0");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("interface", "SmartKeyboard{  'Number of Keyboards':'8',  'Keyboard 0 - Number of Keys':'16',  'Keyboard 1 - Number of Keys':'16',  'Keyboard 2 - Number of Keys':'16',  'Keyboard 3 - Number of Keys':'16',  'Keyboard 4 - Number of Keys':'16',  'Keyboard 5 - Number of Keys':'16',  'Keyboard 6 - Number of Keys':'16',  'Keyboard 7 - Number of Keys':'16',  'Keyboard 0 - Lowest Key':'40',  'Keyboard 1 - Lowest Key':'45',  'Keyboard 2 - Lowest Key':'50',  'Keyboard 3 - Lowest Key':'55',  'Keyboard 4 - Lowest Key':'60',  'Keyboard 5 - Lowest Key':'65',  'Keyboard 6 - Lowest Key':'70',  'Keyboard 7 - Lowest Key':'75',  'Keyboard 0 - Piano Keyboard':'0',  'Keyboard 1 - Piano Keyboard':'0',  'Keyboard 2 - Piano Keyboard':'0',  'Keyboard 3 - Piano Keyboard':'0',  'Keyboard 4 - Piano Keyboard':'0',  'Keyboard 5 - Piano Keyboard':'0',  'Keyboard 6 - Piano Keyboard':'0',  'Keyboard 7 - Piano Keyboard':'0' }");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "harp");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
		m->declare("synths.lib/name", "Faust Synthesizer Library");
		m->declare("synths.lib/version", "0.0");
	}

	virtual int getNumInputs() { return 0; }
	virtual int getNumOutputs() { return 1; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(192000.0f, max(1.0f, (float)fSamplingFreq));
		fConst1 = (1000.0f / fConst0);
		fConst2 = (0.002f * fConst0);
		fConst3 = (0.001f * fConst0);
		iTempPerm0 = 0;
		fTempPerm1 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 400.0f;
		fslider1 = 2.0f;
		fbutton0 = 0.0;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fVec0[i] = 0;
		for (int i=0; i<2; i++) iRec2[i] = 0;
		for (int i=0; i<2; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		IOTA = 0;
		for (int i=0; i<2048; i++) fVec2[i] = 0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
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
		ui_interface->openVerticalBox("harp");
		ui_interface->addHorizontalSlider("freq", &fslider0, 400.0f, 50.0f, 2000.0f, 0.01f);
		ui_interface->addButton("gate", &fbutton0);
		ui_interface->declare(&fslider1, "acc", "0 0 -10 0 10");
		ui_interface->addHorizontalSlider("res", &fslider1, 2.0f, 0.10000000000000001f, 4.0f, 0.01f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = float((fConst0 / float(fslider0)));
		float 	fSlow1 = (fSlow0 + -1.0f);
		float 	fSlow2 = floorf(fSlow1);
		float 	fSlow3 = (fSlow2 + (2.0f - fSlow0));
		float 	fSlow4 = expf((0 - (fConst1 / float(fslider1))));
		float 	fSlow5 = float(fbutton0);
		int 	iSlow6 = int(fSlow1);
		int 	iSlow7 = int(min(1025, max(0, iSlow6)));
		float 	fSlow8 = (fSlow0 + (-1.0f - fSlow2));
		int 	iSlow9 = int(min(1025, max(0, (iSlow6 + 1))));
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fVec0[0] = fConst0;
			iRec2[0] = ((1103515245 * iRec2[1]) + 12345);
			fVec1[0] = fSlow5;
			fRec3[0] = ((int((((fSlow5 - fVec1[1]) > 0) > 0)))?0:min(fConst2, ((fRec3[1] + (0.002f * (fConst0 - fVec0[1]))) + 1)));
			iTempPerm0 = int((fRec3[0] < fConst3));
			fTempPerm1 = ((fSlow4 * fRec0[1]) + (4.6566128752457969e-10f * (iRec2[0] * ((iTempPerm0)?((int((fRec3[0] < 0)))?0:((iTempPerm0)?(fConst1 * fRec3[0]):1)):((int((fRec3[0] < fConst2)))?((fConst1 * (0 - (fRec3[0] - fConst3))) + 1):0)))));
			fVec2[IOTA&2047] = fTempPerm1;
			fRec0[0] = ((fSlow3 * fVec2[(IOTA-iSlow7)&2047]) + (fSlow8 * fVec2[(IOTA-iSlow9)&2047]));
			fRec1[0] = fVec2[IOTA&2047];
			output0[i] = (FAUSTFLOAT)fRec1[1];
			// post processing
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
			IOTA = IOTA+1;
			fRec3[1] = fRec3[0];
			fVec1[1] = fVec1[0];
			iRec2[1] = iRec2[0];
			fVec0[1] = fVec0[0];
		}
	}
};


