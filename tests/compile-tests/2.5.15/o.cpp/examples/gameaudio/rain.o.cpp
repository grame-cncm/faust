//----------------------------------------------------------
// name: "rain"
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
	FAUSTFLOAT 	fslider0;
	int 	iTempPerm0;
	int 	iRec0[2];
	float 	fTempPerm1;
	float 	fVec0[2];
	FAUSTFLOAT 	fslider1;
	float 	fTempPerm2;
	float 	fVec1[2];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("name", "rain");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
	}

	virtual int getNumInputs() { return 0; }
	virtual int getNumOutputs() { return 2; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		iTempPerm0 = 0;
		fTempPerm1 = 0;
		fTempPerm2 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.5f;
		fslider1 = 300.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) iRec0[i] = 0;
		for (int i=0; i<2; i++) fVec0[i] = 0;
		for (int i=0; i<2; i++) fVec1[i] = 0;
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
		ui_interface->openVerticalBox("rain");
		ui_interface->addHorizontalSlider("density", &fslider1, 300.0f, 0.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("volume", &fslider0, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = float(fslider0);
		float 	fSlow1 = (0.001f * float(fslider1));
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			iTempPerm0 = (1103515245 * (iRec0[1] + 12345));
			iRec0[0] = (1103515245 * (iTempPerm0 + 12345));
			int 	iRec1 = iTempPerm0;
			fTempPerm1 = float((4.6566128752457969e-10f * iRec0[0]));
			fVec0[0] = fTempPerm1;
			output0[i] = (FAUSTFLOAT)(fSlow0 * (fVec0[1] * (fabsf(fVec0[0]) < fSlow1)));
			fTempPerm2 = float((4.6566128752457969e-10f * iRec1));
			fVec1[0] = fTempPerm2;
			output1[i] = (FAUSTFLOAT)(fSlow0 * (fVec1[1] * (fabsf(fVec1[0]) < fSlow1)));
			// post processing
			fVec1[1] = fVec1[0];
			fVec0[1] = fVec0[0];
			iRec0[1] = iRec0[0];
		}
	}
};


