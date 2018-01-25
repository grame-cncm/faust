//----------------------------------------------------------
// name: "parametricEqualizer"
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
	float 	fConst1;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fslider1;
	float 	fTempPerm0;
	float 	fVec0[2];
	float 	fRec4[2];
	float 	fRec3[3];
	FAUSTFLOAT 	fslider2;
	float 	fRec6[2];
	float 	fRec5[3];
	float 	fConst2;
	FAUSTFLOAT 	fslider3;
	float 	fRec7[2];
	float 	fTempPerm1;
	float 	fTempPerm2;
	float 	fTempPerm3;
	FAUSTFLOAT 	fslider4;
	float 	fConst3;
	float 	fConst4;
	FAUSTFLOAT 	fslider5;
	float 	fConst5;
	float 	fTempPerm4;
	float 	fTempPerm5;
	float 	fTempPerm6;
	float 	fTempPerm7;
	float 	fTempPerm8;
	float 	fTempPerm9;
	float 	fRec2[3];
	float 	fTempPerm10;
	float 	fTempPerm11;
	float 	fVec1[2];
	float 	fRec1[2];
	float 	fRec0[3];
	FAUSTFLOAT 	fslider6;
	float 	fRec9[2];
	float 	fRec8[3];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "0.0");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("description", "Exercise and compare Parametric Equalizer sections on test signals");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "parametricEqualizer");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
	}

	virtual int getNumInputs() { return 1; }
	virtual int getNumOutputs() { return 1; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(192000.0f, max(1.0f, (float)fSamplingFreq));
		fConst1 = (3.1415926535897931f / fConst0);
		fTempPerm0 = 0;
		fConst2 = (1382.3007675795091f / fConst0);
		fTempPerm1 = 0;
		fTempPerm2 = 0;
		fTempPerm3 = 0;
		fConst3 = float((1.0f / fConst0));
		fConst4 = (1382.3007675795091f * fConst3);
		fConst5 = (2764.6015351590181f * fConst3);
		fTempPerm4 = 0;
		fTempPerm5 = 0;
		fTempPerm6 = 0;
		fTempPerm7 = 0;
		fTempPerm8 = 0;
		fTempPerm9 = 0;
		fTempPerm10 = 0;
		fTempPerm11 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 8000.0f;
		fslider1 = 200.0f;
		fslider2 = 0.0f;
		fslider3 = 49.0f;
		fslider4 = 0.0f;
		fslider5 = 40.0f;
		fslider6 = 0.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fVec0[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<3; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<3; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) fRec7[i] = 0;
		for (int i=0; i<3; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<3; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fRec9[i] = 0;
		for (int i=0; i<3; i++) fRec8[i] = 0;
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
		ui_interface->declare(0, "0", "");
		ui_interface->declare(0, "tooltip", "See Faust's filters.lib   for info and pointers");
		ui_interface->openHorizontalBox("PARAMETRIC EQ SECTIONS");
		ui_interface->declare(0, "1", "");
		ui_interface->openVerticalBox("Low Shelf");
		ui_interface->declare(&fslider2, "0", "");
		ui_interface->declare(&fslider2, "style", "knob");
		ui_interface->declare(&fslider2, "tooltip", "Amount of low-frequency boost or cut in decibels");
		ui_interface->declare(&fslider2, "unit", "dB");
		ui_interface->addHorizontalSlider("Low Boost|Cut", &fslider2, 0.0f, -40.0f, 40.0f, 0.10000000000000001f);
		ui_interface->declare(&fslider1, "1", "");
		ui_interface->declare(&fslider1, "scale", "log");
		ui_interface->declare(&fslider1, "style", "knob");
		ui_interface->declare(&fslider1, "tooltip", "Transition-frequency from boost (cut) to unity gain");
		ui_interface->declare(&fslider1, "unit", "Hz");
		ui_interface->addHorizontalSlider("Transition Frequency", &fslider1, 200.0f, 1.0f, 5000.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->declare(0, "tooltip", "Parametric Equalizer   sections from filters.lib");
		ui_interface->openVerticalBox("Peaking Equalizer");
		ui_interface->declare(&fslider4, "0", "");
		ui_interface->declare(&fslider4, "style", "knob");
		ui_interface->declare(&fslider4, "tooltip", "Amount of   local boost or cut in decibels");
		ui_interface->declare(&fslider4, "unit", "dB");
		ui_interface->addHorizontalSlider("Peak Boost|Cut", &fslider4, 0.0f, -40.0f, 40.0f, 0.10000000000000001f);
		ui_interface->declare(&fslider3, "1", "");
		ui_interface->declare(&fslider3, "style", "knob");
		ui_interface->declare(&fslider3, "tooltip", "Peak   Frequency in Piano Key (PK) units (A440 = 49PK)");
		ui_interface->declare(&fslider3, "unit", "PK");
		ui_interface->addHorizontalSlider("Peak Frequency", &fslider3, 49.0f, 1.0f, 100.0f, 1.0f);
		ui_interface->declare(&fslider5, "2", "");
		ui_interface->declare(&fslider5, "scale", "log");
		ui_interface->declare(&fslider5, "style", "knob");
		ui_interface->declare(&fslider5, "tooltip", "Quality factor   (Q) of the peak = center-frequency/bandwidth");
		ui_interface->addHorizontalSlider("Peak Q", &fslider5, 40.0f, 1.0f, 1000.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->declare(0, "3", "");
		ui_interface->declare(0, "tooltip", "A high shelf provides a boost   or cut above some frequency");
		ui_interface->openVerticalBox("High Shelf");
		ui_interface->declare(&fslider6, "0", "");
		ui_interface->declare(&fslider6, "style", "knob");
		ui_interface->declare(&fslider6, "tooltip", "Amount of   high-frequency boost or cut in decibels");
		ui_interface->declare(&fslider6, "unit", "dB");
		ui_interface->addHorizontalSlider("High Boost|Cut", &fslider6, 0.0f, -40.0f, 40.0f, 0.10000000000000001f);
		ui_interface->declare(&fslider0, "1", "");
		ui_interface->declare(&fslider0, "scale", "log");
		ui_interface->declare(&fslider0, "style", "knob");
		ui_interface->declare(&fslider0, "tooltip", "Transition-frequency from boost (cut) to unity gain");
		ui_interface->declare(&fslider0, "unit", "Hz");
		ui_interface->addHorizontalSlider("Transition Frequency", &fslider0, 8000.0f, 20.0f, 10000.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = tanf((fConst1 * float(fslider0)));
		float 	fSlow1 = (1.0f / fSlow0);
		float 	fSlow2 = (1.0f / (((fSlow1 + 1.0000000000000002f) / fSlow0) + 1));
		float 	fSlow3 = (fSlow1 + 1);
		float 	fSlow4 = (0 - ((1 - fSlow1) / fSlow3));
		float 	fSlow5 = (1.0f / fSlow3);
		float 	fSlow6 = tanf((fConst1 * float(fslider1)));
		float 	fSlow7 = (1.0f / fSlow6);
		float 	fSlow8 = (1.0f / (((fSlow7 + 1.0000000000000002f) / fSlow6) + 1));
		float 	fSlow9 = (1.0f / faustpower<2>(fSlow6));
		float 	fSlow10 = (fSlow7 + 1);
		float 	fSlow11 = (0 - ((1 - fSlow7) / fSlow10));
		float 	fSlow12 = (1.0f / fSlow10);
		float 	fSlow13 = (0 - fSlow7);
		float 	fSlow14 = (2 * (1 - fSlow9));
		float 	fSlow15 = (((fSlow7 + -1.0000000000000002f) / fSlow6) + 1);
		float 	fSlow16 = (2 * (0 - fSlow9));
		float 	fSlow17 = powf(10,(0.050000000000000003f * float(fslider2)));
		float 	fSlow18 = (0.0010000000000000009f * float(fslider3));
		float 	fSlow19 = float(fslider4);
		int 	iSlow20 = int((fSlow19 > 0));
		float 	fSlow21 = float(fslider5);
		float 	fSlow22 = (fConst4 / fSlow21);
		float 	fSlow23 = (fConst4 * (powf(10,(0.050000000000000003f * fabsf(fSlow19))) / fSlow21));
		float 	fSlow24 = (1.0f / faustpower<2>(fSlow0));
		float 	fSlow25 = (2 * (1 - fSlow24));
		float 	fSlow26 = (((fSlow1 + -1.0000000000000002f) / fSlow0) + 1);
		float 	fSlow27 = powf(10,(0.050000000000000003f * float(fslider6)));
		float 	fSlow28 = (0 - fSlow1);
		float 	fSlow29 = (2 * (0 - fSlow24));
		//zone2b
		//zone3
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* output0 = output[0];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fTempPerm0 = (float)input0[i];
			fVec0[0] = fTempPerm0;
			fRec4[0] = ((fSlow11 * fRec4[1]) + (fSlow12 * ((fSlow7 * fVec0[0]) + (fSlow13 * fVec0[1]))));
			fRec3[0] = (fRec4[0] - (fSlow8 * ((fSlow14 * fRec3[1]) + (fSlow15 * fRec3[2]))));
			fRec6[0] = ((fSlow11 * fRec6[1]) + (fSlow12 * (fVec0[0] + fVec0[1])));
			fRec5[0] = (fRec6[0] - (fSlow8 * ((fSlow14 * fRec5[1]) + (fSlow15 * fRec5[2]))));
			fRec7[0] = (fSlow18 + (0.999f * fRec7[1]));
			fTempPerm1 = powf(2.0f,(0.083333333333333329f * (fRec7[0] + -49.0f)));
			fTempPerm2 = tanf((fConst2 * fTempPerm1));
			fTempPerm3 = (1.0f / fTempPerm2);
			fTempPerm4 = (fTempPerm1 / sinf((fConst5 * fTempPerm1)));
			fTempPerm5 = (fSlow22 * fTempPerm4);
			fTempPerm6 = (fSlow23 * fTempPerm4);
			fTempPerm7 = ((iSlow20)?fTempPerm5:fTempPerm6);
			fTempPerm8 = (2 * (fRec2[1] * (1 - (1.0f / faustpower<2>(fTempPerm2)))));
			fTempPerm9 = (((fTempPerm3 + fTempPerm7) / fTempPerm2) + 1);
			fRec2[0] = ((fSlow8 * ((((fSlow9 * fRec3[0]) + (fSlow16 * fRec3[1])) + (fSlow9 * fRec3[2])) + (fSlow17 * (fRec5[2] + (fRec5[0] + (2.0f * fRec5[1])))))) - (((fRec2[2] * (((fTempPerm3 - fTempPerm7) / fTempPerm2) + 1)) + fTempPerm8) / fTempPerm9));
			fTempPerm10 = ((iSlow20)?fTempPerm6:fTempPerm5);
			fTempPerm11 = (((fTempPerm8 + (fRec2[0] * (((fTempPerm3 + fTempPerm10) / fTempPerm2) + 1))) + (fRec2[2] * (((fTempPerm3 - fTempPerm10) / fTempPerm2) + 1))) / fTempPerm9);
			fVec1[0] = fTempPerm11;
			fRec1[0] = ((fSlow4 * fRec1[1]) + (fSlow5 * (fVec1[1] + fVec1[0])));
			fRec0[0] = (fRec1[0] - (fSlow2 * ((fSlow25 * fRec0[1]) + (fSlow26 * fRec0[2]))));
			fRec9[0] = ((fSlow4 * fRec9[1]) + (fSlow5 * ((fSlow28 * fVec1[1]) + (fSlow1 * fVec1[0]))));
			fRec8[0] = (fRec9[0] - (fSlow2 * ((fSlow25 * fRec8[1]) + (fSlow26 * fRec8[2]))));
			output0[i] = (FAUSTFLOAT)(fSlow2 * ((fRec0[2] + (fRec0[0] + (2.0f * fRec0[1]))) + (fSlow27 * (((fSlow24 * fRec8[0]) + (fSlow29 * fRec8[1])) + (fSlow24 * fRec8[2])))));
			// post processing
			fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
			fRec9[1] = fRec9[0];
			fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			fVec1[1] = fVec1[0];
			fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
			fRec7[1] = fRec7[0];
			fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fVec0[1] = fVec0[0];
		}
	}
};


