//----------------------------------------------------------
// name: "harmonicExciter"
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
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fcheckbox0;
	float 	fConst0;
	float 	fConst1;
	FAUSTFLOAT 	fslider2;
	float 	fTempPerm0;
	float 	fRec0[3];
	float 	fTempPerm1;
	float 	fConst2;
	float 	fConst3;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT 	fslider4;
	float 	fTempPerm2;
	float 	fTempPerm3;
	FAUSTFLOAT 	fslider5;
	float 	fTempPerm4;
	float 	fRec6[2];
	float 	fRec5[2];
	FAUSTFLOAT 	fslider6;
	float 	fRec4[2];
	float 	fTempPerm5;
	float 	fTempPerm6;
	float 	fTempPerm7;
	float 	fRec3[2];
	float 	fRec2[2];
	float 	fRec1[2];
	FAUSTFLOAT 	fbargraph0;
	float 	fTempPerm8;
	float 	fTempPerm9;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "0.0");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("compressors.lib/name", "Faust Compressor Effect Library");
		m->declare("compressors.lib/version", "0.0");
		m->declare("description", "Psychoacoustic harmonic exciter, with GUI");
		m->declare("exciter_author", "Priyanka Shekar (pshekar@ccrma.stanford.edu), revised by RM");
		m->declare("exciter_copyright", "Copyright (c) 2013 Priyanka Shekar");
		m->declare("exciter_license", "MIT License (MIT)");
		m->declare("exciter_name", "harmonicExciter");
		m->declare("exciter_version", "1.0");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "harmonicExciter");
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
		fTempPerm1 = 0;
		fConst2 = (2.0f / fConst0);
		fConst3 = (1.0f / fConst0);
		fTempPerm2 = 0;
		fTempPerm3 = 0;
		fTempPerm4 = 0;
		fTempPerm5 = 0;
		fTempPerm6 = 0;
		fTempPerm7 = 0;
		fTempPerm8 = 0;
		fTempPerm9 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.5f;
		fslider1 = 20.0f;
		fcheckbox0 = 0.0;
		fslider2 = 5000.0f;
		fslider3 = 50.0f;
		fslider4 = 5.0f;
		fslider5 = 500.0f;
		fslider6 = -30.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<3; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
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
		ui_interface->openVerticalBox("harmonicExciter");
		ui_interface->declare(0, "tooltip", "Reference:    http://en.wikipedia.org/wiki/Dynamic_range_compression");
		ui_interface->openVerticalBox("COMPRESSOR");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fcheckbox0, "0", "");
		ui_interface->declare(&fcheckbox0, "tooltip", "When this is checked,   the compressor has no effect");
		ui_interface->addCheckButton("Bypass", &fcheckbox0);
		ui_interface->declare(&fbargraph0, "1", "");
		ui_interface->declare(&fbargraph0, "tooltip", "Current gain   of the compressor in dB");
		ui_interface->declare(&fbargraph0, "unit", "dB");
		ui_interface->addHorizontalBargraph("Compressor Gain", &fbargraph0, -50.0f, 10.0f);
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(0, "3", "");
		ui_interface->openHorizontalBox("Compression Control");
		ui_interface->declare(&fslider4, "0", "");
		ui_interface->declare(&fslider4, "style", "knob");
		ui_interface->declare(&fslider4, "tooltip", "A compression Ratio  of N means that for each N dB increase in input signal level above Threshold, the  output level goes up 1 dB");
		ui_interface->addHorizontalSlider("Ratio", &fslider4, 5.0f, 1.0f, 20.0f, 0.10000000000000001f);
		ui_interface->declare(&fslider6, "1", "");
		ui_interface->declare(&fslider6, "style", "knob");
		ui_interface->declare(&fslider6, "tooltip", "When the signal level exceeds the Threshold (in dB), its level is compressed  according to the Ratio");
		ui_interface->declare(&fslider6, "unit", "dB");
		ui_interface->addHorizontalSlider("Threshold", &fslider6, -30.0f, -100.0f, 10.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->declare(0, "4", "");
		ui_interface->openHorizontalBox("Compression Response");
		ui_interface->declare(&fslider3, "1", "");
		ui_interface->declare(&fslider3, "style", "knob");
		ui_interface->declare(&fslider3, "tooltip", "Time constant in ms (1/e smoothing time) for the compression gain to approach  (exponentially) a new lower target level (the compression `kicking in')");
		ui_interface->declare(&fslider3, "unit", "ms");
		ui_interface->addHorizontalSlider("Attack", &fslider3, 50.0f, 0.0f, 500.0f, 0.10000000000000001f);
		ui_interface->declare(&fslider5, "2", "");
		ui_interface->declare(&fslider5, "style", "knob");
		ui_interface->declare(&fslider5, "tooltip", "Time constant in ms (1/e smoothing time) for the compression gain to approach  (exponentially) a new higher target level (the compression 'releasing')");
		ui_interface->declare(&fslider5, "unit", "ms");
		ui_interface->addHorizontalSlider("Release", &fslider5, 500.0f, 0.0f, 1000.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(0, "tooltip", "Reference: Patent US4150253 A");
		ui_interface->openHorizontalBox("EXCITER");
		ui_interface->declare(&fslider2, "0", "");
		ui_interface->declare(&fslider2, "scale", "log");
		ui_interface->declare(&fslider2, "style", "knob");
		ui_interface->declare(&fslider2, "tooltip", "Cutoff frequency for highpassed components to be excited");
		ui_interface->declare(&fslider2, "unit", "Hz");
		ui_interface->addHorizontalSlider("Cutoff Frequency", &fslider2, 5000.0f, 1000.0f, 10000.0f, 100.0f);
		ui_interface->declare(&fslider1, "1", "");
		ui_interface->declare(&fslider1, "style", "knob");
		ui_interface->declare(&fslider1, "tooltip", "Percentage of harmonics generated");
		ui_interface->declare(&fslider1, "unit", "percent");
		ui_interface->addHorizontalSlider("Harmonics", &fslider1, 20.0f, 0.0f, 200.0f, 1.0f);
		ui_interface->declare(&fslider0, "2", "");
		ui_interface->declare(&fslider0, "style", "knob");
		ui_interface->declare(&fslider0, "tooltip", "Dry/Wet mix of original signal   to excited signal");
		ui_interface->addHorizontalSlider("Mix", &fslider0, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = float(fslider0);
		float 	fSlow1 = float(fslider1);
		float 	fSlow2 = (100.0f * (fSlow0 / fSlow1));
		float 	fSlow3 = (0.01f * fSlow1);
		int 	iSlow4 = int(float(fcheckbox0));
		float 	fSlow5 = tanf((fConst1 * float(fslider2)));
		float 	fSlow6 = (1.0f / fSlow5);
		float 	fSlow7 = (1.0f / (((fSlow6 + 1.4142135623730949f) / fSlow5) + 1));
		float 	fSlow8 = (1.0f / faustpower<2>(fSlow5));
		float 	fSlow9 = (((fSlow6 + -1.4142135623730949f) / fSlow5) + 1);
		float 	fSlow10 = (2 * (1 - fSlow8));
		float 	fSlow11 = (2 * (0 - fSlow8));
		float 	fSlow12 = max(fConst3, (0.001f * float(fslider3)));
		float 	fSlow13 = expf((0 - (fConst2 / fSlow12)));
		float 	fSlow14 = (((1.0f / float(float(fslider4))) + -1.0f) * (1.0f - fSlow13));
		float 	fSlow15 = expf((0 - (fConst3 / max(fConst3, (0.001f * float(fslider5))))));
		float 	fSlow16 = expf((0 - (fConst3 / fSlow12)));
		float 	fSlow17 = float(fslider6);
		float 	fSlow18 = (1.0f - fSlow0);
		//zone2b
		//zone3
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* output0 = output[0];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fTempPerm0 = (float)input0[i];
			fRec0[0] = (fTempPerm0 - (fSlow7 * ((fSlow9 * fRec0[2]) + (fSlow10 * fRec0[1]))));
			fTempPerm1 = (fSlow7 * (((fSlow8 * fRec0[0]) + (fSlow11 * fRec0[1])) + (fSlow8 * fRec0[2])));
			fTempPerm2 = ((iSlow4)?0:fTempPerm1);
			fTempPerm3 = fabsf(fTempPerm2);
			fTempPerm4 = ((int((fRec5[1] > fTempPerm3)))?fSlow15:fSlow16);
			fRec6[0] = ((fRec6[1] * fTempPerm4) + (fTempPerm3 * (1.0f - fTempPerm4)));
			fRec5[0] = fRec6[0];
			fRec4[0] = ((fSlow13 * fRec4[1]) + (fSlow14 * max(((20 * log10f(fRec5[0])) - fSlow17), 0.0f)));
			fTempPerm5 = (fTempPerm2 * powf(10,(0.050000000000000003f * fRec4[0])));
			fTempPerm6 = fabsf(fabsf(fTempPerm5));
			fTempPerm7 = ((int((fRec2[1] > fTempPerm6)))?fSlow15:fSlow16);
			fRec3[0] = ((fRec3[1] * fTempPerm7) + (fTempPerm6 * (1.0f - fTempPerm7)));
			fRec2[0] = fRec3[0];
			fRec1[0] = ((fSlow13 * fRec1[1]) + (fSlow14 * max(((20 * log10f(fRec2[0])) - fSlow17), 0.0f)));
			fbargraph0 = (20 * log10f(powf(10,(0.050000000000000003f * fRec1[0]))));
			fTempPerm8 = ((iSlow4)?fTempPerm1:fTempPerm5);
			fTempPerm9 = (fSlow3 * fTempPerm8);
			output0[i] = (FAUSTFLOAT)((fSlow2 * (((fSlow3 * (fTempPerm8 * (fTempPerm9 < 0))) + (((fTempPerm9 >= 0) * (fTempPerm9 <= 1)) * (fTempPerm9 - (0.33333333333333331f * faustpower<3>(fTempPerm9))))) + (0.66666666666666663f * (fTempPerm9 > 1)))) + (fSlow18 * fTempPerm0));
			// post processing
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		}
	}
};


