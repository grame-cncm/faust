//----------------------------------------------------------
// author: "JOS, revised by RM"
// name: "distortion"
// version: "0.0"
//
// Code generated with Faust 2.5.15 (https://faust.grame.fr)
//----------------------------------------------------------

/* link with  */
#include <math.h>
#ifndef FAUSTPOWER
#define FAUSTPOWER
#include <cmath>
template <int N> inline int faustpower(int x)              { return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline int faustpower<0>(int x)            { return 1; }
template <> 	 inline int faustpower<1>(int x)            { return x; }
template <> 	 inline int faustpower<2>(int x)            { return x*x; }
template <int N> inline float faustpower(float x)            { return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline float faustpower<0>(float x)          { return 1; }
template <> 	 inline float faustpower<1>(float x)          { return x; }
template <> 	 inline float faustpower<2>(float x)          { return x*x; }
#endif

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
	float 	fRec1[2];
	FAUSTFLOAT 	fslider1;
	float 	fRec2[2];
	float 	fTempPerm1;
	float 	fTempPerm2;
	float 	fVec0[2];
	float 	fRec0[2];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("author", "JOS, revised by RM");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("description", "Distortion demo application.");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("misceffects.lib/name", "Faust Math Library");
		m->declare("misceffects.lib/version", "2.0");
		m->declare("name", "distortion");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("version", "0.0");
	}

	virtual int getNumInputs() { return 1; }
	virtual int getNumOutputs() { return 1; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fTempPerm0 = 0;
		fTempPerm1 = 0;
		fTempPerm2 = 0;
	}
	virtual void instanceResetUserInterface() {
		fcheckbox0 = 0.0;
		fslider0 = 0.0f;
		fslider1 = 0.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fVec0[i] = 0;
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
		ui_interface->declare(0, "tooltip", "Reference:   https://ccrma.stanford.edu/~jos/pasp/Cubic_Soft_Clipper.html");
		ui_interface->openVerticalBox("CUBIC NONLINEARITY cubicnl");
		ui_interface->declare(&fcheckbox0, "0", "");
		ui_interface->declare(&fcheckbox0, "tooltip", "When this is checked, the   nonlinearity has no effect");
		ui_interface->addCheckButton("Bypass", &fcheckbox0);
		ui_interface->declare(&fslider1, "1", "");
		ui_interface->declare(&fslider1, "tooltip", "Amount of distortion");
		ui_interface->addHorizontalSlider("Drive", &fslider1, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider0, "2", "");
		ui_interface->declare(&fslider0, "tooltip", "Brings in even harmonics");
		ui_interface->addHorizontalSlider("Offset", &fslider0, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		int 	iSlow0 = int(float(fcheckbox0));
		float 	fSlow1 = (0.0010000000000000009f * float(fslider0));
		float 	fSlow2 = (0.0010000000000000009f * float(fslider1));
		//zone2b
		//zone3
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* output0 = output[0];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fTempPerm0 = (float)input0[i];
			fRec1[0] = (fSlow1 + (0.999f * fRec1[1]));
			fRec2[0] = (fSlow2 + (0.999f * fRec2[1]));
			fTempPerm1 = max((float)-1, min((float)1, (fRec1[0] + (powf(10.0f,(2 * fRec2[0])) * ((iSlow0)?0:fTempPerm0)))));
			fTempPerm2 = (fTempPerm1 * (1 - (0.33333333333333331f * faustpower<2>(fTempPerm1))));
			fVec0[0] = fTempPerm2;
			fRec0[0] = (((0.995f * fRec0[1]) + fVec0[0]) - fVec0[1]);
			output0[i] = (FAUSTFLOAT)((iSlow0)?fTempPerm0:fRec0[0]);
			// post processing
			fRec0[1] = fRec0[0];
			fVec0[1] = fVec0[0];
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
		}
	}
};


