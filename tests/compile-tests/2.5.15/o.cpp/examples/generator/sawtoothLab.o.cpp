//----------------------------------------------------------
// author: "JOS, revised by RM"
// name: "sawtoothLab"
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
	FAUSTFLOAT 	fslider0;
	int 	iVec0[4];
	float 	fRec0[2];
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT 	fcheckbox1;
	FAUSTFLOAT 	fcheckbox2;
	int 	iRec2[2];
	float 	fTempPerm0;
	float 	fRec1[4];
	FAUSTFLOAT 	fentry0;
	float 	fConst0;
	float 	fConst1;
	float 	fConst2;
	float 	fConst3;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	float 	fRec4[2];
	float 	fTempPerm1;
	float 	fVec1[2];
	float 	fTempPerm2;
	float 	fRec3[2];
	float 	fTempPerm3;
	float 	fTempPerm4;
	float 	fTempPerm5;
	float 	fVec2[2];
	float 	fTempPerm6;
	float 	fVec3[2];
	float 	fTempPerm7;
	float 	fVec4[2];
	float 	fTempPerm8;
	float 	fVec5[2];
	float 	fConst4;
	float 	fTempPerm9;
	float 	fVec6[2];
	float 	fTempPerm10;
	float 	fVec7[2];
	float 	fConst5;
	FAUSTFLOAT 	fslider3;
	float 	fTempPerm11;
	float 	fVec8[2];
	float 	fTempPerm12;
	float 	fRec5[2];
	float 	fTempPerm13;
	float 	fTempPerm14;
	float 	fTempPerm15;
	float 	fVec9[2];
	float 	fTempPerm16;
	float 	fVec10[2];
	float 	fTempPerm17;
	float 	fVec11[2];
	float 	fTempPerm18;
	float 	fVec12[2];
	float 	fTempPerm19;
	float 	fVec13[2];
	float 	fTempPerm20;
	float 	fVec14[2];
	FAUSTFLOAT 	fslider4;
	float 	fTempPerm21;
	float 	fVec15[2];
	float 	fTempPerm22;
	float 	fRec6[2];
	float 	fTempPerm23;
	float 	fTempPerm24;
	float 	fTempPerm25;
	float 	fVec16[2];
	float 	fTempPerm26;
	float 	fVec17[2];
	float 	fTempPerm27;
	float 	fVec18[2];
	float 	fTempPerm28;
	float 	fVec19[2];
	float 	fTempPerm29;
	float 	fVec20[2];
	float 	fTempPerm30;
	float 	fVec21[2];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("author", "JOS, revised by RM");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("description", "An application demonstrating the different sawtooth oscillators of Faust.");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "sawtoothLab");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
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
		fConst0 = min(192000.0f, max(1.0f, (float)fSamplingFreq));
		fConst1 = float(fConst0);
		fConst2 = (0.005208333333333333f * faustpower<3>(fConst1));
		fConst3 = (1.0f / fConst0);
		fTempPerm1 = 0;
		fTempPerm2 = 0;
		fTempPerm3 = 0;
		fTempPerm4 = 0;
		fTempPerm5 = 0;
		fTempPerm6 = 0;
		fTempPerm7 = 0;
		fTempPerm8 = 0;
		fConst4 = (0.041666666666666664f * faustpower<2>(fConst1));
		fTempPerm9 = 0;
		fTempPerm10 = 0;
		fConst5 = (0.25f * fConst1);
		fTempPerm11 = 0;
		fTempPerm12 = 0;
		fTempPerm13 = 0;
		fTempPerm14 = 0;
		fTempPerm15 = 0;
		fTempPerm16 = 0;
		fTempPerm17 = 0;
		fTempPerm18 = 0;
		fTempPerm19 = 0;
		fTempPerm20 = 0;
		fTempPerm21 = 0;
		fTempPerm22 = 0;
		fTempPerm23 = 0;
		fTempPerm24 = 0;
		fTempPerm25 = 0;
		fTempPerm26 = 0;
		fTempPerm27 = 0;
		fTempPerm28 = 0;
		fTempPerm29 = 0;
		fTempPerm30 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = -20.0f;
		fcheckbox0 = 0.0;
		fcheckbox1 = 0.0;
		fcheckbox2 = 0.0;
		fentry0 = 2.0f;
		fslider1 = 49.0f;
		fslider2 = 0.10000000000000001f;
		fslider3 = -0.10000000000000001f;
		fslider4 = 0.10000000000000001f;
	}
	virtual void instanceClear() {
		for (int i=0; i<4; i++) iVec0[i] = 0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) iRec2[i] = 0;
		for (int i=0; i<4; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fVec2[i] = 0;
		for (int i=0; i<2; i++) fVec3[i] = 0;
		for (int i=0; i<2; i++) fVec4[i] = 0;
		for (int i=0; i<2; i++) fVec5[i] = 0;
		for (int i=0; i<2; i++) fVec6[i] = 0;
		for (int i=0; i<2; i++) fVec7[i] = 0;
		for (int i=0; i<2; i++) fVec8[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) fVec9[i] = 0;
		for (int i=0; i<2; i++) fVec10[i] = 0;
		for (int i=0; i<2; i++) fVec11[i] = 0;
		for (int i=0; i<2; i++) fVec12[i] = 0;
		for (int i=0; i<2; i++) fVec13[i] = 0;
		for (int i=0; i<2; i++) fVec14[i] = 0;
		for (int i=0; i<2; i++) fVec15[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<2; i++) fVec16[i] = 0;
		for (int i=0; i<2; i++) fVec17[i] = 0;
		for (int i=0; i<2; i++) fVec18[i] = 0;
		for (int i=0; i<2; i++) fVec19[i] = 0;
		for (int i=0; i<2; i++) fVec20[i] = 0;
		for (int i=0; i<2; i++) fVec21[i] = 0;
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
		ui_interface->declare(0, "tooltip", "See Faust's oscillators.lib   for documentation and references");
		ui_interface->openVerticalBox("SAWTOOTH OSCILLATOR");
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fslider0, "1", "");
		ui_interface->declare(&fslider0, "style", "knob");
		ui_interface->declare(&fslider0, "tooltip", "Sawtooth   waveform amplitude");
		ui_interface->declare(&fslider0, "unit", "dB");
		ui_interface->addVerticalSlider("Amplitude", &fslider0, -20.0f, -120.0f, 10.0f, 0.10000000000000001f);
		ui_interface->declare(&fslider1, "2", "");
		ui_interface->declare(&fslider1, "style", "knob");
		ui_interface->declare(&fslider1, "tooltip", "Sawtooth   frequency as a Piano Key (PK) number (A440 = key 49)");
		ui_interface->declare(&fslider1, "unit", "PK");
		ui_interface->addVerticalSlider("Frequency", &fslider1, 49.0f, 1.0f, 88.0f, 0.01f);
		ui_interface->declare(&fslider3, "3", "");
		ui_interface->declare(&fslider3, "style", "knob");
		ui_interface->declare(&fslider3, "tooltip", "Percentange frequency-shift  up or down for second oscillator");
		ui_interface->declare(&fslider3, "unit", "%%");
		ui_interface->addVerticalSlider("Detuning 1", &fslider3, -0.10000000000000001f, -10.0f, 10.0f, 0.01f);
		ui_interface->declare(&fslider4, "4", "");
		ui_interface->declare(&fslider4, "style", "knob");
		ui_interface->declare(&fslider4, "tooltip", "Percentange frequency-shift up or down for third detuned oscillator");
		ui_interface->declare(&fslider4, "unit", "%%");
		ui_interface->addVerticalSlider("Detuning 2", &fslider4, 0.10000000000000001f, -10.0f, 10.0f, 0.01f);
		ui_interface->declare(&fslider2, "5", "");
		ui_interface->declare(&fslider2, "scale", "log");
		ui_interface->declare(&fslider2, "style", "knob");
		ui_interface->declare(&fslider2, "tooltip", "Portamento (frequency-glide) time-constant in seconds");
		ui_interface->declare(&fslider2, "unit", "sec");
		ui_interface->addVerticalSlider("Portamento", &fslider2, 0.10000000000000001f, 0.001f, 10.0f, 0.001f);
		ui_interface->declare(&fentry0, "6", "");
		ui_interface->declare(&fentry0, "tooltip", "Order of sawtootn aliasing   suppression");
		ui_interface->addNumEntry("Saw Order", &fentry0, 2.0f, 1.0f, 4.0f, 1.0f);
		ui_interface->declare(0, "7", "");
		ui_interface->openVerticalBox("Alternate Signals");
		ui_interface->declare(&fcheckbox1, "0", "");
		ui_interface->addCheckButton("Noise (White or Pink - uses only Amplitude control on   the left)", &fcheckbox1);
		ui_interface->declare(&fcheckbox2, "1", "");
		ui_interface->declare(&fcheckbox2, "tooltip", "Pink Noise (or 1/f noise) is Constant-Q Noise, meaning that it has the   same total power in every octave");
		ui_interface->addCheckButton("Pink instead of White Noise (also called 1/f Noise)", &fcheckbox2);
		ui_interface->declare(&fcheckbox0, "2", "");
		ui_interface->addCheckButton("External Signal Input (overrides Sawtooth/Noise   selection above)", &fcheckbox0);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = (0.0010000000000000009f * powf(10,(0.050000000000000003f * float(fslider0))));
		int 	iSlow1 = int(float(fcheckbox0));
		int 	iSlow2 = int(float(fcheckbox1));
		int 	iSlow3 = int(float(fcheckbox2));
		int 	iSlow4 = int((float(fentry0) + -1));
		int 	iSlow5 = int((iSlow4 >= 2));
		int 	iSlow6 = int((iSlow4 >= 3));
		float 	fSlow7 = expf((0 - (fConst3 / float(fslider2))));
		float 	fSlow8 = (440.0f * (powf(2.0f,(0.083333333333333329f * (float(fslider1) + -49.0f))) * (1.0f - fSlow7)));
		int 	iSlow9 = int((iSlow4 >= 1));
		float 	fSlow10 = ((0.01f * float(fslider3)) + 1);
		float 	fSlow11 = ((0.01f * float(fslider4)) + 1);
		//zone2b
		//zone3
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* output0 = output[0];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			iVec0[0] = 1;
			fRec0[0] = (fSlow0 + (0.999f * fRec0[1]));
			iRec2[0] = ((1103515245 * iRec2[1]) + 12345);
			fTempPerm0 = (4.6566128752457969e-10f * iRec2[0]);
			fRec1[0] = (((0.52218940000000003f * fRec1[3]) + (fTempPerm0 + (2.4949560019999999f * fRec1[1]))) - (2.0172658750000001f * fRec1[2]));
			fRec4[0] = (fSlow8 + (fSlow7 * fRec4[1]));
			fTempPerm1 = max(20.0f, fabsf(fRec4[0]));
			fVec1[0] = fTempPerm1;
			fTempPerm2 = (fRec3[1] + (fConst3 * fVec1[1]));
			fRec3[0] = (fTempPerm2 - floorf(fTempPerm2));
			fTempPerm3 = (2 * fRec3[0]);
			fTempPerm4 = (fTempPerm3 + -1);
			fTempPerm5 = faustpower<2>(fTempPerm4);
			fVec2[0] = fTempPerm5;
			fTempPerm6 = (fVec2[0] * (fVec2[0] + -2.0f));
			fVec3[0] = fTempPerm6;
			fTempPerm7 = ((fVec3[0] - fVec3[1]) / fVec1[0]);
			fVec4[0] = fTempPerm7;
			fTempPerm8 = ((fVec4[0] - fVec4[1]) / fVec1[0]);
			fVec5[0] = fTempPerm8;
			fTempPerm9 = faustpower<3>(fTempPerm4);
			fVec6[0] = (fTempPerm9 + (1 - fTempPerm3));
			fTempPerm10 = ((fTempPerm9 + (1 - (fTempPerm3 + fVec6[1]))) / fVec1[0]);
			fVec7[0] = fTempPerm10;
			fTempPerm11 = max(20.0f, fabsf((fSlow10 * fRec4[0])));
			fVec8[0] = fTempPerm11;
			fTempPerm12 = (fRec5[1] + (fConst3 * fVec8[1]));
			fRec5[0] = (fTempPerm12 - floorf(fTempPerm12));
			fTempPerm13 = (2 * fRec5[0]);
			fTempPerm14 = (fTempPerm13 + -1);
			fTempPerm15 = faustpower<2>(fTempPerm14);
			fVec9[0] = fTempPerm15;
			fTempPerm16 = (fVec9[0] * (fVec9[0] + -2.0f));
			fVec10[0] = fTempPerm16;
			fTempPerm17 = ((fVec10[0] - fVec10[1]) / fVec8[0]);
			fVec11[0] = fTempPerm17;
			fTempPerm18 = ((fVec11[0] - fVec11[1]) / fVec8[0]);
			fVec12[0] = fTempPerm18;
			fTempPerm19 = faustpower<3>(fTempPerm14);
			fVec13[0] = (fTempPerm19 + (1 - fTempPerm13));
			fTempPerm20 = ((fTempPerm19 + (1 - (fTempPerm13 + fVec13[1]))) / fVec8[0]);
			fVec14[0] = fTempPerm20;
			fTempPerm21 = max(20.0f, fabsf((fSlow11 * fRec4[0])));
			fVec15[0] = fTempPerm21;
			fTempPerm22 = (fRec6[1] + (fConst3 * fVec15[1]));
			fRec6[0] = (fTempPerm22 - floorf(fTempPerm22));
			fTempPerm23 = (2 * fRec6[0]);
			fTempPerm24 = (fTempPerm23 + -1);
			fTempPerm25 = faustpower<2>(fTempPerm24);
			fVec16[0] = fTempPerm25;
			fTempPerm26 = (fVec16[0] * (fVec16[0] + -2.0f));
			fVec17[0] = fTempPerm26;
			fTempPerm27 = ((fVec17[0] - fVec17[1]) / fVec15[0]);
			fVec18[0] = fTempPerm27;
			fTempPerm28 = ((fVec18[0] - fVec18[1]) / fVec15[0]);
			fVec19[0] = fTempPerm28;
			fTempPerm29 = faustpower<3>(fTempPerm24);
			fVec20[0] = (fTempPerm29 + (1 - fTempPerm23));
			fTempPerm30 = ((fTempPerm29 + (1 - (fTempPerm23 + fVec20[1]))) / fVec15[0]);
			fVec21[0] = fTempPerm30;
			output0[i] = (FAUSTFLOAT)(fRec0[0] * ((iSlow1)?(float)input0[i]:((iSlow2)?((iSlow3)?(((0.049922034999999997f * fRec1[0]) + (0.050612698999999997f * fRec1[2])) - ((0.095993537000000004f * fRec1[1]) + (0.0044087859999999996f * fRec1[3]))):fTempPerm0):(0.33333333333333331f * (fRec0[0] * ((((iSlow5)?((iSlow6)?(fConst2 * ((iVec0[3] * (fVec5[0] - fVec5[1])) / fVec1[0])):(fConst4 * ((iVec0[2] * (fVec7[0] - fVec7[1])) / fVec1[0]))):((iSlow9)?(fConst5 * ((iVec0[1] * (fVec2[0] - fVec2[1])) / fVec1[0])):fTempPerm4)) + ((iSlow5)?((iSlow6)?(fConst2 * ((iVec0[3] * (fVec12[0] - fVec12[1])) / fVec8[0])):(fConst4 * ((iVec0[2] * (fVec14[0] - fVec14[1])) / fVec8[0]))):((iSlow9)?(fConst5 * ((iVec0[1] * (fVec9[0] - fVec9[1])) / fVec8[0])):fTempPerm14))) + ((iSlow5)?((iSlow6)?(fConst2 * ((iVec0[3] * (fVec19[0] - fVec19[1])) / fVec15[0])):(fConst4 * ((iVec0[2] * (fVec21[0] - fVec21[1])) / fVec15[0]))):((iSlow9)?(fConst5 * ((iVec0[1] * (fVec16[0] - fVec16[1])) / fVec15[0])):fTempPerm24))))))));
			// post processing
			fVec21[1] = fVec21[0];
			fVec20[1] = fVec20[0];
			fVec19[1] = fVec19[0];
			fVec18[1] = fVec18[0];
			fVec17[1] = fVec17[0];
			fVec16[1] = fVec16[0];
			fRec6[1] = fRec6[0];
			fVec15[1] = fVec15[0];
			fVec14[1] = fVec14[0];
			fVec13[1] = fVec13[0];
			fVec12[1] = fVec12[0];
			fVec11[1] = fVec11[0];
			fVec10[1] = fVec10[0];
			fVec9[1] = fVec9[0];
			fRec5[1] = fRec5[0];
			fVec8[1] = fVec8[0];
			fVec7[1] = fVec7[0];
			fVec6[1] = fVec6[0];
			fVec5[1] = fVec5[0];
			fVec4[1] = fVec4[0];
			fVec3[1] = fVec3[0];
			fVec2[1] = fVec2[0];
			fRec3[1] = fRec3[0];
			fVec1[1] = fVec1[0];
			fRec4[1] = fRec4[0];
			for (int i=3; i>0; i--) fRec1[i] = fRec1[i-1];
			iRec2[1] = iRec2[0];
			fRec0[1] = fRec0[0];
			for (int i=3; i>0; i--) iVec0[i] = iVec0[i-1];
		}
	}
};


