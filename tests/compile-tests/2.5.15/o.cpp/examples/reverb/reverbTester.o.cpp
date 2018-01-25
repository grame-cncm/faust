//----------------------------------------------------------
// author: "RM"
// name: "reverbTester"
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
	FAUSTFLOAT 	fbutton0;
	float 	fVec0[2];
	int 	iTempPerm0;
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT 	fbutton1;
	float 	fVec1[2];
	FAUSTFLOAT 	fcheckbox1;
	int 	iRec1[2];
	float 	fRec0[4];
	float 	fTempPerm1;
	FAUSTFLOAT 	fbutton2;
	float 	fVec2[2];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("author", "RM");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("description", "Handy test inputs for reverberator demos below.");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "reverbTester");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
		m->declare("version", "0.0");
	}

	virtual int getNumInputs() { return 5; }
	virtual int getNumOutputs() { return 2; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		iTempPerm0 = 0;
		fTempPerm1 = 0;
	}
	virtual void instanceResetUserInterface() {
		fbutton0 = 0.0;
		fcheckbox0 = 0.0;
		fbutton1 = 0.0;
		fcheckbox1 = 0.0;
		fbutton2 = 0.0;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fVec0[i] = 0;
		for (int i=0; i<2; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) iRec1[i] = 0;
		for (int i=0; i<4; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fVec2[i] = 0;
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
		ui_interface->openVerticalBox("reverbTester");
		ui_interface->declare(0, "1", "");
		ui_interface->openVerticalBox("Input Config");
		ui_interface->declare(&fcheckbox0, "1", "");
		ui_interface->declare(&fcheckbox0, "tooltip", "When this is checked, the stereo external audio inputs are   disabled (good for hearing the impulse response or pink-noise response alone)");
		ui_interface->addCheckButton("Mute Ext Inputs", &fcheckbox0);
		ui_interface->declare(&fcheckbox1, "2", "");
		ui_interface->declare(&fcheckbox1, "tooltip", "Pink Noise (or 1/f noise) is Constant-Q Noise (useful for adjusting   the EQ sections)");
		ui_interface->addCheckButton("Pink Noise", &fcheckbox1);
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("Impulse Selection");
		ui_interface->declare(&fbutton1, "1", "");
		ui_interface->declare(&fbutton1, "tooltip", "Send impulse into LEFT channel");
		ui_interface->addButton("Left", &fbutton1);
		ui_interface->declare(&fbutton0, "2", "");
		ui_interface->declare(&fbutton0, "tooltip", "Send impulse into LEFT and RIGHT channels");
		ui_interface->addButton("Center", &fbutton0);
		ui_interface->declare(&fbutton2, "3", "");
		ui_interface->declare(&fbutton2, "tooltip", "Send impulse into RIGHT channel");
		ui_interface->addButton("Right", &fbutton2);
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = float(fbutton0);
		float 	fSlow1 = (1 - float(fcheckbox0));
		float 	fSlow2 = float(fbutton1);
		float 	fSlow3 = (0.10000000000000001f * float(fcheckbox1));
		float 	fSlow4 = float(fbutton2);
		//zone2b
		//zone3
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* input1 = input[1];
		FAUSTFLOAT* input2 = input[2];
		FAUSTFLOAT* input3 = input[3];
		FAUSTFLOAT* input4 = input[4];
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fVec0[0] = fSlow0;
			iTempPerm0 = ((fSlow0 - fVec0[1]) > 0);
			fVec1[0] = fSlow2;
			iRec1[0] = ((1103515245 * iRec1[1]) + 12345);
			fRec0[0] = (((0.52218940000000003f * fRec0[3]) + ((4.6566128752457969e-10f * iRec1[0]) + (2.4949560019999999f * fRec0[1]))) - (2.0172658750000001f * fRec0[2]));
			fTempPerm1 = (fSlow3 * (((0.049922034999999997f * fRec0[0]) + (0.050612698999999997f * fRec0[2])) - ((0.095993537000000004f * fRec0[1]) + (0.0044087859999999996f * fRec0[3]))));
			output0[i] = (FAUSTFLOAT)((iTempPerm0 + ((fSlow1 * (float)input3[i]) + ((fSlow2 - fVec1[1]) > 0))) + fTempPerm1);
			fVec2[0] = fSlow4;
			output1[i] = (FAUSTFLOAT)(((fSlow4 - fVec2[1]) > 0) + ((fSlow1 * (float)input4[i]) + (iTempPerm0 + fTempPerm1)));
			// post processing
			fVec2[1] = fVec2[0];
			for (int i=3; i>0; i--) fRec0[i] = fRec0[i-1];
			iRec1[1] = iRec1[0];
			fVec1[1] = fVec1[0];
			fVec0[1] = fVec0[0];
		}
	}
};


