//----------------------------------------------------------
// name: "spectralTilt"
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
	float 	fConst1;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	float 	fConst2;
	float 	fTempPerm0;
	float 	fVec0[2];
	float 	fRec1[2];
	float 	fVec1[2];
	float 	fRec0[2];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("description", "Demonstrate the Spectral Tilt effect on test signals");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "spectralTilt");
	}

	virtual int getNumInputs() { return 1; }
	virtual int getNumOutputs() { return 1; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(192000.0f, max(1.0f, (float)fSamplingFreq));
		fConst1 = (3.1415926535897931f / fConst0);
		fConst2 = (1.0f / tanf((0.5f / fConst0)));
		fTempPerm0 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 100.0f;
		fslider1 = 5000.0f;
		fslider2 = -0.5f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fVec0[i] = 0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) fVec1[i] = 0;
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
		ui_interface->openVerticalBox("spectralTilt");
		ui_interface->declare(&fslider2, "1", "");
		ui_interface->addHorizontalSlider("Slope of Spectral Tilt across Band", &fslider2, -0.5f, -1.0f, 1.0f, 0.001f);
		ui_interface->declare(&fslider0, "2", "");
		ui_interface->declare(&fslider0, "unit", "Hz");
		ui_interface->addHorizontalSlider("Band Start Frequency", &fslider0, 100.0f, 20.0f, 10000.0f, 1.0f);
		ui_interface->declare(&fslider1, "3", "");
		ui_interface->declare(&fslider1, "unit", "Hz");
		ui_interface->addHorizontalSlider("Band Width", &fslider1, 5000.0f, 100.0f, 10000.0f, 1.0f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = float(fslider0);
		float 	fSlow1 = powf(((fSlow0 + float(fslider1)) / fSlow0),1.0f);
		float 	fSlow2 = tanf((fConst1 * (fSlow0 * fSlow1)));
		float 	fSlow3 = float(fslider2);
		float 	fSlow4 = tanf((fConst1 * (fSlow0 * powf(fSlow1,(1 - fSlow3)))));
		float 	fSlow5 = (fSlow2 / fSlow4);
		float 	fSlow6 = tanf((fConst1 * fSlow0));
		float 	fSlow7 = (6.2831853071795862f * ((fSlow0 * fSlow2) / fSlow6));
		float 	fSlow8 = (fConst2 + fSlow7);
		float 	fSlow9 = (0 - ((fSlow7 - fConst2) / fSlow8));
		float 	fSlow10 = (1.0f / fSlow8);
		float 	fSlow11 = (6.2831853071795862f * ((fSlow0 * fSlow4) / fSlow6));
		float 	fSlow12 = (fSlow11 - fConst2);
		float 	fSlow13 = tanf((fConst1 * (fSlow0 * powf(fSlow1,(0 - fSlow3)))));
		float 	fSlow14 = (fSlow6 / fSlow13);
		float 	fSlow15 = (6.2831853071795862f * fSlow0);
		float 	fSlow16 = (fConst2 + fSlow15);
		float 	fSlow17 = (0 - ((fSlow15 - fConst2) / fSlow16));
		float 	fSlow18 = (1.0f / fSlow16);
		float 	fSlow19 = (6.2831853071795862f * ((fSlow0 * fSlow13) / fSlow6));
		float 	fSlow20 = (fConst2 + fSlow19);
		float 	fSlow21 = (fSlow19 - fConst2);
		float 	fSlow22 = ((fSlow6 * (fConst2 + fSlow11)) / fSlow13);
		//zone2b
		//zone3
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* output0 = output[0];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fTempPerm0 = (float)input0[i];
			fVec0[0] = fTempPerm0;
			fRec1[0] = ((fSlow17 * fRec1[1]) + (fSlow18 * ((fSlow20 * fVec0[0]) + (fSlow21 * fVec0[1]))));
			fVec1[0] = (fSlow14 * fRec1[0]);
			fRec0[0] = ((fSlow9 * fRec0[1]) + (fSlow10 * ((fSlow12 * fVec1[1]) + (fSlow22 * fRec1[0]))));
			output0[i] = (FAUSTFLOAT)(fSlow5 * fRec0[0]);
			// post processing
			fRec0[1] = fRec0[0];
			fVec1[1] = fVec1[0];
			fRec1[1] = fRec1[0];
			fVec0[1] = fVec0[0];
		}
	}
};


