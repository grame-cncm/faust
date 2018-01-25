//----------------------------------------------------------
// author: "Grame"
// copyright: "(c)GRAME 2006"
// license: "BSD"
// name: "bandFilter"
// version: "1.0"
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
	float 	fConst0;
	FAUSTFLOAT 	fentry0;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fentry1;
	float 	fTempPerm0;
	float 	fRec0[3];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("author", "Grame");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("copyright", "(c)GRAME 2006");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("license", "BSD");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "bandFilter");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() { return 1; }
	virtual int getNumOutputs() { return 1; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = (3.1415926535897931f / min(192000.0f, max(1.0f, (float)fSamplingFreq)));
		fTempPerm0 = 0;
	}
	virtual void instanceResetUserInterface() {
		fentry0 = 1000.0f;
		fslider0 = 0.0f;
		fentry1 = 50.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<3; i++) fRec0[i] = 0;
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
		ui_interface->openVerticalBox("Bandfilter");
		ui_interface->declare(&fentry1, "style", "knob");
		ui_interface->addNumEntry("Q factor", &fentry1, 50.0f, 0.10000000000000001f, 100.0f, 0.10000000000000001f);
		ui_interface->declare(&fentry0, "style", "knob");
		ui_interface->declare(&fentry0, "unit", "Hz");
		ui_interface->addNumEntry("freq", &fentry0, 1000.0f, 20.0f, 20000.0f, 1.0f);
		ui_interface->declare(&fslider0, "unit", "dB");
		ui_interface->addVerticalSlider("gain", &fslider0, 0.0f, -50.0f, 50.0f, 0.10000000000000001f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = tanf((fConst0 * float(fentry0)));
		float 	fSlow1 = float(fentry1);
		float 	fSlow2 = (powf(10,(0.050000000000000003f * (0 - float(fslider0)))) / fSlow1);
		float 	fSlow3 = (1.0f / ((fSlow0 * (fSlow0 + fSlow2)) + 1));
		float 	fSlow4 = (2 * (faustpower<2>(fSlow0) + -1));
		float 	fSlow5 = ((fSlow0 * (fSlow0 - fSlow2)) + 1);
		float 	fSlow6 = (1.0f / fSlow1);
		float 	fSlow7 = ((fSlow0 * (fSlow0 + fSlow6)) + 1);
		float 	fSlow8 = (1 - (fSlow0 * (fSlow6 - fSlow0)));
		//zone2b
		//zone3
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* output0 = output[0];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fTempPerm0 = (fSlow4 * fRec0[1]);
			fRec0[0] = ((float)input0[i] - (fSlow3 * ((fSlow5 * fRec0[2]) + fTempPerm0)));
			output0[i] = (FAUSTFLOAT)(fSlow3 * ((fTempPerm0 + (fSlow7 * fRec0[0])) + (fSlow8 * fRec0[2])));
			// post processing
			fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		}
	}
};


