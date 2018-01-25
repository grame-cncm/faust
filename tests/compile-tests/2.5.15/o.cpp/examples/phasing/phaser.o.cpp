//----------------------------------------------------------
// author: "JOS, revised by RM"
// name: "phaser"
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
	float 	fTempPerm1;
	int 	iVec0[2];
	FAUSTFLOAT 	fcheckbox1;
	FAUSTFLOAT 	fslider1;
	float 	fConst0;
	float 	fConst1;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT 	fslider4;
	float 	fConst2;
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT 	fslider7;
	float 	fRec5[2];
	float 	fRec6[2];
	float 	fTempPerm2;
	float 	fTempPerm3;
	float 	fRec4[3];
	float 	fTempPerm4;
	float 	fRec3[3];
	float 	fTempPerm5;
	float 	fRec2[3];
	float 	fTempPerm6;
	float 	fRec1[3];
	float 	fRec0[2];
	FAUSTFLOAT 	fcheckbox2;
	float 	fTempPerm7;
	float 	fTempPerm8;
	float 	fTempPerm9;
	float 	fTempPerm10;
	float 	fRec11[3];
	float 	fTempPerm11;
	float 	fRec10[3];
	float 	fTempPerm12;
	float 	fRec9[3];
	float 	fTempPerm13;
	float 	fRec8[3];
	float 	fRec7[2];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("author", "JOS, revised by RM");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("description", "Phaser demo application.");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "phaser");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("phaflangers.lib/name", "Faust Phaser and Flanger Library");
		m->declare("phaflangers.lib/version", "0.0");
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("version", "0.0");
	}

	virtual int getNumInputs() { return 2; }
	virtual int getNumOutputs() { return 2; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fTempPerm0 = 0;
		fTempPerm1 = 0;
		fConst0 = min(192000.0f, max(1.0f, (float)fSamplingFreq));
		fConst1 = (1.0f / fConst0);
		fConst2 = (6.2831853071795862f / fConst0);
		fTempPerm2 = 0;
		fTempPerm3 = 0;
		fTempPerm4 = 0;
		fTempPerm5 = 0;
		fTempPerm6 = 0;
		fTempPerm7 = 0;
		fTempPerm8 = 0;
		fTempPerm9 = 0;
		fTempPerm10 = 0;
		fTempPerm11 = 0;
		fTempPerm12 = 0;
		fTempPerm13 = 0;
	}
	virtual void instanceResetUserInterface() {
		fcheckbox0 = 0.0;
		fslider0 = 0.0f;
		fcheckbox1 = 0.0;
		fslider1 = 1.0f;
		fslider2 = 1000.0f;
		fslider3 = 0.0f;
		fslider4 = 1.5f;
		fslider5 = 100.0f;
		fslider6 = 800.0f;
		fslider7 = 0.5f;
		fcheckbox2 = 0.0;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) iVec0[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<3; i++) fRec4[i] = 0;
		for (int i=0; i<3; i++) fRec3[i] = 0;
		for (int i=0; i<3; i++) fRec2[i] = 0;
		for (int i=0; i<3; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<3; i++) fRec11[i] = 0;
		for (int i=0; i<3; i++) fRec10[i] = 0;
		for (int i=0; i<3; i++) fRec9[i] = 0;
		for (int i=0; i<3; i++) fRec8[i] = 0;
		for (int i=0; i<2; i++) fRec7[i] = 0;
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
		ui_interface->declare(0, "tooltip", "Reference:   https://ccrma.stanford.edu/~jos/pasp/Flanging.html");
		ui_interface->openVerticalBox("PHASER2");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fcheckbox0, "0", "");
		ui_interface->declare(&fcheckbox0, "tooltip", "When this is checked, the phaser   has no effect");
		ui_interface->addCheckButton("Bypass", &fcheckbox0);
		ui_interface->declare(&fcheckbox2, "1", "");
		ui_interface->addCheckButton("Invert Internal Phaser Sum", &fcheckbox2);
		ui_interface->declare(&fcheckbox1, "2", "");
		ui_interface->addCheckButton("Vibrato Mode", &fcheckbox1);
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fslider7, "1", "");
		ui_interface->declare(&fslider7, "style", "knob");
		ui_interface->declare(&fslider7, "unit", "Hz");
		ui_interface->addHorizontalSlider("Speed", &fslider7, 0.5f, 0.0f, 10.0f, 0.001f);
		ui_interface->declare(&fslider1, "2", "");
		ui_interface->declare(&fslider1, "style", "knob");
		ui_interface->addHorizontalSlider("Notch Depth (Intensity)", &fslider1, 1.0f, 0.0f, 1.0f, 0.001f);
		ui_interface->declare(&fslider3, "3", "");
		ui_interface->declare(&fslider3, "style", "knob");
		ui_interface->addHorizontalSlider("Feedback Gain", &fslider3, 0.0f, -0.999f, 0.999f, 0.001f);
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fslider2, "1", "");
		ui_interface->declare(&fslider2, "scale", "log");
		ui_interface->declare(&fslider2, "style", "knob");
		ui_interface->declare(&fslider2, "unit", "Hz");
		ui_interface->addHorizontalSlider("Notch width", &fslider2, 1000.0f, 10.0f, 5000.0f, 1.0f);
		ui_interface->declare(&fslider5, "2", "");
		ui_interface->declare(&fslider5, "scale", "log");
		ui_interface->declare(&fslider5, "style", "knob");
		ui_interface->declare(&fslider5, "unit", "Hz");
		ui_interface->addHorizontalSlider("Min Notch1 Freq", &fslider5, 100.0f, 20.0f, 5000.0f, 1.0f);
		ui_interface->declare(&fslider6, "3", "");
		ui_interface->declare(&fslider6, "scale", "log");
		ui_interface->declare(&fslider6, "style", "knob");
		ui_interface->declare(&fslider6, "unit", "Hz");
		ui_interface->addHorizontalSlider("Max Notch1 Freq", &fslider6, 800.0f, 20.0f, 10000.0f, 1.0f);
		ui_interface->declare(&fslider4, "4", "");
		ui_interface->declare(&fslider4, "style", "knob");
		ui_interface->addHorizontalSlider("Notch Freq Ratio: NotchFreq(n+1)/NotchFreq(n)", &fslider4, 1.5f, 1.1000000000000001f, 4.0f, 0.001f);
		ui_interface->closeBox();
		ui_interface->declare(0, "3", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fslider0, "unit", "dB");
		ui_interface->addHorizontalSlider("Phaser Output Level", &fslider0, 0.0f, -60.0f, 10.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		int 	iSlow0 = int(float(fcheckbox0));
		float 	fSlow1 = powf(10,(0.050000000000000003f * float(fslider0)));
		float 	fSlow2 = (0.5f * ((int(float(fcheckbox1)))?2:float(fslider1)));
		float 	fSlow3 = (1 - fSlow2);
		float 	fSlow4 = expf((fConst1 * (0 - (3.1415926535897931f * float(fslider2)))));
		float 	fSlow5 = faustpower<2>(fSlow4);
		float 	fSlow6 = float(fslider3);
		float 	fSlow7 = (0 - (2 * fSlow4));
		float 	fSlow8 = float(fslider4);
		float 	fSlow9 = float(fslider5);
		float 	fSlow10 = (fConst2 * fSlow9);
		float 	fSlow11 = (0.5f * (0 - (fConst2 * (fSlow9 - max(fSlow9, float(fslider6))))));
		float 	fSlow12 = (fConst2 * float(fslider7));
		float 	fSlow13 = sinf(fSlow12);
		float 	fSlow14 = cosf(fSlow12);
		float 	fSlow15 = (0 - fSlow13);
		float 	fSlow16 = faustpower<2>(fSlow8);
		float 	fSlow17 = faustpower<3>(fSlow8);
		float 	fSlow18 = faustpower<4>(fSlow8);
		float 	fSlow19 = ((int(float(fcheckbox2)))?(0 - fSlow2):fSlow2);
		//zone2b
		//zone3
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* input1 = input[1];
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fTempPerm0 = (float)input0[i];
			fTempPerm1 = ((iSlow0)?0:fTempPerm0);
			iVec0[0] = 1;
			fRec5[0] = ((fSlow13 * fRec6[1]) + (fSlow14 * fRec5[1]));
			fRec6[0] = (((fSlow14 * fRec6[1]) + (fSlow15 * fRec5[1])) + (1 - iVec0[1]));
			fTempPerm2 = (fSlow10 + (fSlow11 * (1 - fRec5[0])));
			fTempPerm3 = (fRec4[1] * cosf((fSlow8 * fTempPerm2)));
			fRec4[0] = (((fSlow1 * fTempPerm1) + (fSlow6 * fRec0[1])) - ((fSlow7 * fTempPerm3) + (fSlow5 * fRec4[2])));
			fTempPerm4 = (fRec3[1] * cosf((fSlow16 * fTempPerm2)));
			fRec3[0] = ((fRec4[2] + (fSlow7 * (fTempPerm3 - fTempPerm4))) + (fSlow5 * (fRec4[0] - fRec3[2])));
			fTempPerm5 = (fRec2[1] * cosf((fSlow17 * fTempPerm2)));
			fRec2[0] = ((fSlow5 * (fRec3[0] - fRec2[2])) + (fRec3[2] + (fSlow7 * (fTempPerm4 - fTempPerm5))));
			fTempPerm6 = (fRec1[1] * cosf((fSlow18 * fTempPerm2)));
			fRec1[0] = ((fRec2[2] + (fSlow7 * (fTempPerm5 - fTempPerm6))) + (fSlow5 * (fRec2[0] - fRec1[2])));
			fRec0[0] = ((fSlow5 * fRec1[0]) + ((fSlow7 * fTempPerm6) + fRec1[2]));
			output0[i] = (FAUSTFLOAT)((iSlow0)?fTempPerm0:((fSlow1 * (fTempPerm1 * fSlow3)) + (fRec0[0] * fSlow19)));
			fTempPerm7 = (float)input1[i];
			fTempPerm8 = ((iSlow0)?0:fTempPerm7);
			fTempPerm9 = (fSlow10 + (fSlow11 * (1 - fRec6[0])));
			fTempPerm10 = (fRec11[1] * cosf((fSlow8 * fTempPerm9)));
			fRec11[0] = (((fSlow1 * fTempPerm8) + (fSlow6 * fRec7[1])) - ((fSlow7 * fTempPerm10) + (fSlow5 * fRec11[2])));
			fTempPerm11 = (fRec10[1] * cosf((fSlow16 * fTempPerm9)));
			fRec10[0] = ((fRec11[2] + (fSlow7 * (fTempPerm10 - fTempPerm11))) + (fSlow5 * (fRec11[0] - fRec10[2])));
			fTempPerm12 = (fRec9[1] * cosf((fSlow17 * fTempPerm9)));
			fRec9[0] = ((fRec10[2] + (fSlow7 * (fTempPerm11 - fTempPerm12))) + (fSlow5 * (fRec10[0] - fRec9[2])));
			fTempPerm13 = (fRec8[1] * cosf((fSlow18 * fTempPerm9)));
			fRec8[0] = ((fRec9[2] + (fSlow7 * (fTempPerm12 - fTempPerm13))) + (fSlow5 * (fRec9[0] - fRec8[2])));
			fRec7[0] = ((fSlow5 * fRec8[0]) + ((fSlow7 * fTempPerm13) + fRec8[2]));
			output1[i] = (FAUSTFLOAT)((iSlow0)?fTempPerm7:((fSlow1 * (fTempPerm8 * fSlow3)) + (fRec7[0] * fSlow19)));
			// post processing
			fRec7[1] = fRec7[0];
			fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
			fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
			fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
			fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
			fRec0[1] = fRec0[0];
			fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
			fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
			fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
			fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
			fRec6[1] = fRec6[0];
			fRec5[1] = fRec5[0];
			iVec0[1] = iVec0[0];
		}
	}
};


