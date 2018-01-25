//----------------------------------------------------------
// name: "midiOnly"
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
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fbutton0;
	FAUSTFLOAT 	fslider2;
	float 	fVec1[2];
	int 	iTempPerm0;
	float 	fRec2[2];
	FAUSTFLOAT 	fslider3;
	float 	fRec5[2];
	float 	fTempPerm1;
	float 	fTempPerm2;
	float 	fTempPerm3;
	float 	fRec3[2];
	int 	iTempPerm4;
	float 	fRec4[2];
	FAUSTFLOAT 	fslider4;
	float 	fRec6[2];
	FAUSTFLOAT 	fslider5;
	float 	fRec7[2];
	float 	fTempPerm5;
	float 	fTempPerm6;
	float 	fTempPerm7;
	float 	fRec0[2];
	float 	fRec1[2];
	float 	fRec8[2];
	float 	fTempPerm8;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("interface", "SmartKeyboard{  'Number of Keyboards':'1',  'Keyboard 0 - Number of Keys':'2',  'Keyboard 0 - Send Freq':'0',  'Keyboard 0 - Piano Keyboard':'0',  'Keyboard 0 - Static Mode':'1',  'Keyboard 0 - Send Key X':'1',  'Keyboard 0 - Key 0 - Label':'Mod Index',  'Keyboard 0 - Key 1 - Label':'Mod Freq' }");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "midiOnly");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("synths.lib/name", "Faust Synthesizer Library");
		m->declare("synths.lib/version", "0.0");
	}

	virtual int getNumInputs() { return 0; }
	virtual int getNumOutputs() { return 2; }
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
		fTempPerm8 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 300.0f;
		fslider1 = 1.0f;
		fbutton0 = 0.0;
		fslider2 = 0.0f;
		fslider3 = 0.5f;
		fslider4 = 0.5f;
		fslider5 = 1.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) iVec0[i] = 0;
		for (int i=0; i<2; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<2; i++) fRec7[i] = 0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) fRec8[i] = 0;
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
		ui_interface->openVerticalBox("midiOnly");
		ui_interface->declare(&fslider1, "midi", "pitchwheel");
		ui_interface->addHorizontalSlider("bend", &fslider1, 1.0f, 0.0f, 10.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider0, 300.0f, 50.0f, 2000.0f, 0.01f);
		ui_interface->addHorizontalSlider("gain", &fslider5, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addButton("gate", &fbutton0);
		ui_interface->declare(&fslider4, "midi", "ctrl 1");
		ui_interface->addHorizontalSlider("kb0k0x", &fslider4, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider3, "midi", "ctrl 1");
		ui_interface->addHorizontalSlider("kb0k1x", &fslider3, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider2, "midi", "ctrl 64");
		ui_interface->addHorizontalSlider("sustain", &fslider2, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = float(fslider0);
		float 	fSlow1 = float(fslider1);
		float 	fSlow2 = min((float)1, (float(fbutton0) + float(fslider2)));
		int 	iSlow3 = (fSlow2 == 0);
		float 	fSlow4 = (fConst0 * fSlow0);
		float 	fSlow5 = (0.0010000000000000009f * float(fslider3));
		float 	fSlow6 = (0.0010000000000000009f * float(fslider4));
		float 	fSlow7 = (0.0010000000000000009f * (fSlow2 * float(fslider5)));
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			iVec0[0] = 1;
			fVec1[0] = fSlow2;
			iTempPerm0 = ((fSlow2 == fVec1[1]) | iSlow3);
			fRec2[0] = ((fSlow1 * (1.0f - (0.999f * iTempPerm0))) + (0.999f * (iTempPerm0 * fRec2[1])));
			fRec5[0] = (fSlow5 + (0.999f * fRec5[1]));
			fTempPerm1 = (fSlow4 * (fRec2[0] * (fRec5[0] + 1)));
			fTempPerm2 = sinf(fTempPerm1);
			fTempPerm3 = cosf(fTempPerm1);
			fRec3[0] = ((fRec4[1] * fTempPerm2) + (fRec3[1] * fTempPerm3));
			iTempPerm4 = (1 - iVec0[1]);
			fRec4[0] = (((fRec4[1] * fTempPerm3) + (fRec3[1] * (0 - fTempPerm2))) + iTempPerm4);
			fRec6[0] = (fSlow6 + (0.999f * fRec6[1]));
			fRec7[0] = (fSlow7 + (0.999f * fRec7[1]));
			fTempPerm5 = (fConst0 * ((fSlow0 * fRec2[0]) + (1000 * ((fRec3[0] * fRec6[0]) * fRec7[0]))));
			fTempPerm6 = sinf(fTempPerm5);
			fTempPerm7 = cosf(fTempPerm5);
			fRec0[0] = ((fRec1[1] * fTempPerm6) + (fRec0[1] * fTempPerm7));
			fRec1[0] = (((fRec1[1] * fTempPerm7) + (fRec0[1] * (0 - fTempPerm6))) + iTempPerm4);
			fRec8[0] = (fSlow7 + (0.999f * fRec8[1]));
			fTempPerm8 = (fRec0[0] * fRec8[0]);
			output0[i] = (FAUSTFLOAT)fTempPerm8;
			output1[i] = (FAUSTFLOAT)fTempPerm8;
			// post processing
			fRec8[1] = fRec8[0];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
			fRec7[1] = fRec7[0];
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


