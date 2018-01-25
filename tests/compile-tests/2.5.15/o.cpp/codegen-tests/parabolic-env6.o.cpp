//----------------------------------------------------------
// name: "parabolic-env6"
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
	int 	iRec0[4];
	int 	iTempPerm0;
	int 	iVec0[2];
	int 	iTempPerm1;
	float 	fRec3[2];
	float 	fRec2[2];
	float 	fRec1[2];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("math.lib/author", "GRAME");
		m->declare("math.lib/copyright", "GRAME");
		m->declare("math.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m->declare("math.lib/license", "LGPL with exception");
		m->declare("math.lib/name", "Math Library");
		m->declare("math.lib/version", "1.0");
		m->declare("music.lib/author", "GRAME");
		m->declare("music.lib/copyright", "GRAME");
		m->declare("music.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m->declare("music.lib/license", "LGPL with exception");
		m->declare("music.lib/name", "Music Library");
		m->declare("music.lib/version", "1.0");
		m->declare("name", "parabolic-env6");
	}

	virtual int getNumInputs() { return 0; }
	virtual int getNumOutputs() { return 3; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		iTempPerm0 = 0;
		iTempPerm1 = 0;
	}
	virtual void instanceResetUserInterface() {
	}
	virtual void instanceClear() {
		for (int i=0; i<4; i++) iRec0[i] = 0;
		for (int i=0; i<2; i++) iVec0[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
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
		ui_interface->openVerticalBox("parabolic-env6");
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		FAUSTFLOAT* output2 = output[2];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			iRec0[0] = (iRec0[1] + 1);
			output0[i] = (FAUSTFLOAT)iRec0[1];
			iTempPerm0 = ((iRec0[1] % 7) == 3);
			iVec0[0] = iTempPerm0;
			output1[i] = (FAUSTFLOAT)iVec0[0];
			iTempPerm1 = (((fRec1[1] > 0) | iVec0[0]) | iVec0[1]);
			fRec3[0] = ((fRec3[1] + -0.080000000000000016f) * iTempPerm1);
			fRec2[0] = (iTempPerm1 * ((fRec2[1] + fRec3[1]) + 0.35999999999999999f));
			fRec1[0] = max((float)0, fRec2[1]);
			output2[i] = (FAUSTFLOAT)(fRec1[0] * iRec0[3]);
			// post processing
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			iVec0[1] = iVec0[0];
			for (int i=3; i>0; i--) iRec0[i] = iRec0[i-1];
		}
	}
};


