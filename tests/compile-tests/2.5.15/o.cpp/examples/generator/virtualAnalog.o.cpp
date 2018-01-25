//----------------------------------------------------------
// author: "JOS, revised by RM"
// name: "VirtualAnalog"
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
	FAUSTFLOAT 	fslider1;
	int 	iVec0[4];
	float 	fRec0[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fentry0;
	float 	fConst0;
	float 	fConst1;
	float 	fConst2;
	float 	fConst3;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT 	fslider4;
	float 	fRec2[2];
	float 	fTempPerm0;
	float 	fVec1[2];
	float 	fTempPerm1;
	float 	fRec1[2];
	float 	fTempPerm2;
	float 	fTempPerm3;
	float 	fTempPerm4;
	float 	fVec2[2];
	float 	fTempPerm5;
	float 	fVec3[2];
	float 	fTempPerm6;
	float 	fVec4[2];
	float 	fTempPerm7;
	float 	fVec5[2];
	float 	fConst4;
	float 	fTempPerm8;
	float 	fVec6[2];
	float 	fTempPerm9;
	float 	fVec7[2];
	float 	fConst5;
	FAUSTFLOAT 	fslider5;
	float 	fTempPerm10;
	float 	fTempPerm11;
	float 	fVec8[2];
	float 	fTempPerm12;
	float 	fRec3[2];
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
	FAUSTFLOAT 	fslider6;
	float 	fTempPerm21;
	float 	fTempPerm22;
	float 	fVec15[2];
	float 	fTempPerm23;
	float 	fRec4[2];
	float 	fTempPerm24;
	float 	fTempPerm25;
	float 	fTempPerm26;
	float 	fVec16[2];
	float 	fTempPerm27;
	float 	fVec17[2];
	float 	fTempPerm28;
	float 	fVec18[2];
	float 	fTempPerm29;
	float 	fVec19[2];
	float 	fTempPerm30;
	float 	fVec20[2];
	float 	fTempPerm31;
	float 	fVec21[2];
	float 	fConst6;
	FAUSTFLOAT 	fslider7;
	float 	fTempPerm32;
	float 	fTempPerm33;
	float 	fVec22[2];
	float 	fTempPerm34;
	float 	fRec5[2];
	float 	fTempPerm35;
	float 	fTempPerm36;
	float 	fTempPerm37;
	float 	fVec23[2];
	float 	fTempPerm38;
	int 	IOTA;
	float 	fVec24[4096];
	float 	fConst7;
	float 	fTempPerm39;
	int 	iTempPerm40;
	float 	fTempPerm41;
	float 	fTempPerm42;
	float 	fTempPerm43;
	float 	fTempPerm44;
	float 	fVec25[2];
	float 	fTempPerm45;
	float 	fRec6[2];
	float 	fTempPerm46;
	float 	fTempPerm47;
	float 	fTempPerm48;
	float 	fVec26[2];
	float 	fTempPerm49;
	float 	fVec27[4096];
	float 	fTempPerm50;
	int 	iTempPerm51;
	float 	fTempPerm52;
	float 	fTempPerm53;
	float 	fTempPerm54;
	float 	fTempPerm55;
	float 	fVec28[2];
	float 	fTempPerm56;
	float 	fRec7[2];
	float 	fTempPerm57;
	float 	fTempPerm58;
	float 	fTempPerm59;
	float 	fVec29[2];
	float 	fTempPerm60;
	float 	fVec30[4096];
	float 	fTempPerm61;
	int 	iTempPerm62;
	float 	fTempPerm63;
	float 	fTempPerm64;
	float 	fConst8;
	FAUSTFLOAT 	fslider8;
	float 	fRec8[2];
	float 	fRec9[2];
	float 	fRec10[2];
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT 	fslider10;
	float 	fRec11[2];
	float 	fTempPerm65;
	float 	fTempPerm66;
	float 	fTempPerm67;
	int 	iTempPerm68;
	float 	fTempPerm69;
	int 	iTempPerm70;
	float 	fTempPerm71;
	float 	fTempPerm72;
	float 	fTempPerm73;
	int 	iTempPerm74;
	float 	fTempPerm75;
	int 	iTempPerm76;
	float 	fTempPerm77;
	float 	fTempPerm78;
	float 	fTempPerm79;
	int 	iTempPerm80;
	float 	fTempPerm81;
	int 	iTempPerm82;
	float 	fConst9;
	float 	fTempPerm83;
	float 	fVec31[2];
	float 	fTempPerm84;
	float 	fVec32[2];
	float 	fTempPerm85;
	float 	fVec33[4096];
	float 	fTempPerm86;
	float 	fVec34[2];
	float 	fTempPerm87;
	float 	fVec35[2];
	float 	fTempPerm88;
	float 	fVec36[4096];
	float 	fTempPerm89;
	float 	fVec37[2];
	float 	fTempPerm90;
	float 	fVec38[2];
	float 	fTempPerm91;
	float 	fVec39[4096];
	FAUSTFLOAT 	fslider11;
	int 	iRec13[2];
	float 	fRec12[4];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("author", "JOS, revised by RM");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("description", "Virtual analog oscillator demo application.");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "VirtualAnalog");
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
		fConst0 = min(192000.0f, max(1.0f, (float)fSamplingFreq));
		fConst1 = float(fConst0);
		fConst2 = (0.005208333333333333f * faustpower<3>(fConst1));
		fConst3 = (1.0f / fConst0);
		fTempPerm0 = 0;
		fTempPerm1 = 0;
		fTempPerm2 = 0;
		fTempPerm3 = 0;
		fTempPerm4 = 0;
		fTempPerm5 = 0;
		fTempPerm6 = 0;
		fTempPerm7 = 0;
		fConst4 = (0.041666666666666664f * faustpower<2>(fConst1));
		fTempPerm8 = 0;
		fTempPerm9 = 0;
		fConst5 = (0.25f * fConst1);
		fTempPerm10 = 0;
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
		fTempPerm31 = 0;
		fConst6 = (0.083333333333333329f * fConst1);
		fTempPerm32 = 0;
		fTempPerm33 = 0;
		fTempPerm34 = 0;
		fTempPerm35 = 0;
		fTempPerm36 = 0;
		fTempPerm37 = 0;
		fTempPerm38 = 0;
		fConst7 = (0.5f * fConst1);
		fTempPerm39 = 0;
		iTempPerm40 = 0;
		fTempPerm41 = 0;
		fTempPerm42 = 0;
		fTempPerm43 = 0;
		fTempPerm44 = 0;
		fTempPerm45 = 0;
		fTempPerm46 = 0;
		fTempPerm47 = 0;
		fTempPerm48 = 0;
		fTempPerm49 = 0;
		fTempPerm50 = 0;
		iTempPerm51 = 0;
		fTempPerm52 = 0;
		fTempPerm53 = 0;
		fTempPerm54 = 0;
		fTempPerm55 = 0;
		fTempPerm56 = 0;
		fTempPerm57 = 0;
		fTempPerm58 = 0;
		fTempPerm59 = 0;
		fTempPerm60 = 0;
		fTempPerm61 = 0;
		iTempPerm62 = 0;
		fTempPerm63 = 0;
		fTempPerm64 = 0;
		fConst8 = (1.3333333333333333f / fConst0);
		fTempPerm65 = 0;
		fTempPerm66 = 0;
		fTempPerm67 = 0;
		iTempPerm68 = 0;
		fTempPerm69 = 0;
		iTempPerm70 = 0;
		fTempPerm71 = 0;
		fTempPerm72 = 0;
		fTempPerm73 = 0;
		iTempPerm74 = 0;
		fTempPerm75 = 0;
		iTempPerm76 = 0;
		fTempPerm77 = 0;
		fTempPerm78 = 0;
		fTempPerm79 = 0;
		iTempPerm80 = 0;
		fTempPerm81 = 0;
		iTempPerm82 = 0;
		fConst9 = (0.013888888888888888f * fConst1);
		fTempPerm83 = 0;
		fTempPerm84 = 0;
		fTempPerm85 = 0;
		fTempPerm86 = 0;
		fTempPerm87 = 0;
		fTempPerm88 = 0;
		fTempPerm89 = 0;
		fTempPerm90 = 0;
		fTempPerm91 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.0f;
		fslider1 = -20.0f;
		fslider2 = 1.0f;
		fentry0 = 2.0f;
		fslider3 = 49.0f;
		fslider4 = 0.10000000000000001f;
		fslider5 = -0.10000000000000001f;
		fslider6 = 0.10000000000000001f;
		fslider7 = 0.0f;
		fslider8 = 0.0f;
		fslider9 = 0.0f;
		fcheckbox0 = 0.0;
		fslider10 = 0.5f;
		fslider11 = 0.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<4; i++) iVec0[i] = 0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) fVec2[i] = 0;
		for (int i=0; i<2; i++) fVec3[i] = 0;
		for (int i=0; i<2; i++) fVec4[i] = 0;
		for (int i=0; i<2; i++) fVec5[i] = 0;
		for (int i=0; i<2; i++) fVec6[i] = 0;
		for (int i=0; i<2; i++) fVec7[i] = 0;
		for (int i=0; i<2; i++) fVec8[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fVec9[i] = 0;
		for (int i=0; i<2; i++) fVec10[i] = 0;
		for (int i=0; i<2; i++) fVec11[i] = 0;
		for (int i=0; i<2; i++) fVec12[i] = 0;
		for (int i=0; i<2; i++) fVec13[i] = 0;
		for (int i=0; i<2; i++) fVec14[i] = 0;
		for (int i=0; i<2; i++) fVec15[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2; i++) fVec16[i] = 0;
		for (int i=0; i<2; i++) fVec17[i] = 0;
		for (int i=0; i<2; i++) fVec18[i] = 0;
		for (int i=0; i<2; i++) fVec19[i] = 0;
		for (int i=0; i<2; i++) fVec20[i] = 0;
		for (int i=0; i<2; i++) fVec21[i] = 0;
		for (int i=0; i<2; i++) fVec22[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) fVec23[i] = 0;
		IOTA = 0;
		for (int i=0; i<4096; i++) fVec24[i] = 0;
		for (int i=0; i<2; i++) fVec25[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<2; i++) fVec26[i] = 0;
		for (int i=0; i<4096; i++) fVec27[i] = 0;
		for (int i=0; i<2; i++) fVec28[i] = 0;
		for (int i=0; i<2; i++) fRec7[i] = 0;
		for (int i=0; i<2; i++) fVec29[i] = 0;
		for (int i=0; i<4096; i++) fVec30[i] = 0;
		for (int i=0; i<2; i++) fRec8[i] = 0;
		for (int i=0; i<2; i++) fRec9[i] = 0;
		for (int i=0; i<2; i++) fRec10[i] = 0;
		for (int i=0; i<2; i++) fRec11[i] = 0;
		for (int i=0; i<2; i++) fVec31[i] = 0;
		for (int i=0; i<2; i++) fVec32[i] = 0;
		for (int i=0; i<4096; i++) fVec33[i] = 0;
		for (int i=0; i<2; i++) fVec34[i] = 0;
		for (int i=0; i<2; i++) fVec35[i] = 0;
		for (int i=0; i<4096; i++) fVec36[i] = 0;
		for (int i=0; i<2; i++) fVec37[i] = 0;
		for (int i=0; i<2; i++) fVec38[i] = 0;
		for (int i=0; i<4096; i++) fVec39[i] = 0;
		for (int i=0; i<2; i++) iRec13[i] = 0;
		for (int i=0; i<4; i++) fRec12[i] = 0;
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
		ui_interface->declare(0, "tooltip", "See Faust's oscillators.lib for documentation and references");
		ui_interface->openVerticalBox("VIRTUAL ANALOG OSCILLATORS");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("Signal Levels");
		ui_interface->declare(&fslider2, "0", "");
		ui_interface->declare(&fslider2, "style", "vslider");
		ui_interface->addVerticalSlider("Sawtooth", &fslider2, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(0, "1", "");
		ui_interface->openVerticalBox("Pulse Train");
		ui_interface->declare(&fcheckbox0, "0", "");
		ui_interface->declare(&fcheckbox0, "tooltip", "When checked, use 3rd-order aliasing suppression (up from 2)  See if you can hear a difference with the freq high and swept");
		ui_interface->addCheckButton("Order 3", &fcheckbox0);
		ui_interface->declare(&fslider9, "1", "");
		ui_interface->declare(&fslider9, "style", "vslider");
		ui_interface->addVerticalSlider("0x00", &fslider9, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider10, "2", "");
		ui_interface->declare(&fslider10, "style", "knob");
		ui_interface->addVerticalSlider("Duty Cycle", &fslider10, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->declare(&fslider7, "2", "");
		ui_interface->declare(&fslider7, "style", "vslider");
		ui_interface->addVerticalSlider("Square", &fslider7, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider8, "3", "");
		ui_interface->declare(&fslider8, "style", "vslider");
		ui_interface->addVerticalSlider("Triangle", &fslider8, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider11, "4", "");
		ui_interface->declare(&fslider11, "style", "vslider");
		ui_interface->declare(&fslider11, "tooltip", "Pink Noise (or 1/f noise) is   Constant-Q Noise, meaning that it has the same total power in every octave   (uses only amplitude controls)");
		ui_interface->addVerticalSlider("Pink Noise", &fslider11, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider0, "5", "");
		ui_interface->declare(&fslider0, "style", "vslider");
		ui_interface->addVerticalSlider("Ext Input", &fslider0, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("Signal Parameters");
		ui_interface->declare(0, "0", "");
		ui_interface->openVerticalBox("0x00");
		ui_interface->declare(&fslider1, "1", "");
		ui_interface->declare(&fslider1, "style", "hslider");
		ui_interface->declare(&fslider1, "tooltip", "Sawtooth waveform amplitude");
		ui_interface->declare(&fslider1, "unit", "dB");
		ui_interface->addHorizontalSlider("Mix Amplitude", &fslider1, -20.0f, -120.0f, 10.0f, 0.10000000000000001f);
		ui_interface->declare(&fslider3, "2", "");
		ui_interface->declare(&fslider3, "style", "hslider");
		ui_interface->declare(&fslider3, "tooltip", "Sawtooth   frequency as a Piano Key (PK) number (A440 = key 49)");
		ui_interface->declare(&fslider3, "unit", "PK");
		ui_interface->addHorizontalSlider("Frequency", &fslider3, 49.0f, 1.0f, 88.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->declare(&fslider5, "3", "");
		ui_interface->declare(&fslider5, "style", "knob");
		ui_interface->declare(&fslider5, "tooltip", "Percentange frequency-shift up or down for second oscillator");
		ui_interface->declare(&fslider5, "unit", "%%");
		ui_interface->addVerticalSlider("Detuning 1", &fslider5, -0.10000000000000001f, -10.0f, 10.0f, 0.01f);
		ui_interface->declare(&fslider6, "4", "");
		ui_interface->declare(&fslider6, "style", "knob");
		ui_interface->declare(&fslider6, "tooltip", "Percentange frequency-shift up or down for third detuned oscillator");
		ui_interface->declare(&fslider6, "unit", "%%");
		ui_interface->addVerticalSlider("Detuning 2", &fslider6, 0.10000000000000001f, -10.0f, 10.0f, 0.01f);
		ui_interface->declare(&fslider4, "5", "");
		ui_interface->declare(&fslider4, "scale", "log");
		ui_interface->declare(&fslider4, "style", "knob");
		ui_interface->declare(&fslider4, "tooltip", "Portamento (frequency-glide) time-constant in seconds");
		ui_interface->declare(&fslider4, "unit", "sec");
		ui_interface->addVerticalSlider("Portamento", &fslider4, 0.10000000000000001f, 0.001f, 10.0f, 0.001f);
		ui_interface->declare(&fentry0, "6", "");
		ui_interface->declare(&fentry0, "tooltip", "Order of sawtooth aliasing  suppression");
		ui_interface->addNumEntry("Saw Order", &fentry0, 2.0f, 1.0f, 4.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = float(fslider0);
		float 	fSlow1 = (0.0010000000000000009f * powf(10,(0.050000000000000003f * float(fslider1))));
		float 	fSlow2 = (0.33333333333333331f * float(fslider2));
		int 	iSlow3 = int((float(fentry0) + -1));
		int 	iSlow4 = int((iSlow3 >= 2));
		int 	iSlow5 = int((iSlow3 >= 3));
		float 	fSlow6 = expf((0 - (fConst3 / float(fslider4))));
		float 	fSlow7 = (440.0f * (powf(2.0f,(0.083333333333333329f * (float(fslider3) + -49.0f))) * (1.0f - fSlow6)));
		int 	iSlow8 = int((iSlow3 >= 1));
		float 	fSlow9 = (1 - (0.01f * float(fslider5)));
		float 	fSlow10 = ((0.01f * float(fslider6)) + 1);
		float 	fSlow11 = (fConst6 * float(fslider7));
		float 	fSlow12 = (fConst8 * float(fslider8));
		float 	fSlow13 = (fConst1 * float(fslider9));
		float 	fSlow14 = float(fcheckbox0);
		float 	fSlow15 = (0.083333333333333329f * (1 - fSlow14));
		float 	fSlow16 = (0.010000000000000009f * float(fslider10));
		float 	fSlow17 = (fConst9 * fSlow14);
		float 	fSlow18 = float(fslider11);
		//zone2b
		//zone3
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* output0 = output[0];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			iVec0[0] = 1;
			fRec0[0] = (fSlow1 + (0.999f * fRec0[1]));
			fRec2[0] = (fSlow7 + (fSlow6 * fRec2[1]));
			fTempPerm0 = max(20.0f, fabsf(fRec2[0]));
			fVec1[0] = fTempPerm0;
			fTempPerm1 = (fRec1[1] + (fConst3 * fVec1[1]));
			fRec1[0] = (fTempPerm1 - floorf(fTempPerm1));
			fTempPerm2 = (2 * fRec1[0]);
			fTempPerm3 = (fTempPerm2 + -1);
			fTempPerm4 = faustpower<2>(fTempPerm3);
			fVec2[0] = fTempPerm4;
			fTempPerm5 = (fVec2[0] * (fVec2[0] + -2.0f));
			fVec3[0] = fTempPerm5;
			fTempPerm6 = ((fVec3[0] - fVec3[1]) / fVec1[0]);
			fVec4[0] = fTempPerm6;
			fTempPerm7 = ((fVec4[0] - fVec4[1]) / fVec1[0]);
			fVec5[0] = fTempPerm7;
			fTempPerm8 = faustpower<3>(fTempPerm3);
			fVec6[0] = (fTempPerm8 + (1 - fTempPerm2));
			fTempPerm9 = ((fTempPerm8 + (1 - (fTempPerm2 + fVec6[1]))) / fVec1[0]);
			fVec7[0] = fTempPerm9;
			fTempPerm10 = (fSlow9 * fRec2[0]);
			fTempPerm11 = max(20.0f, fabsf(fTempPerm10));
			fVec8[0] = fTempPerm11;
			fTempPerm12 = (fRec3[1] + (fConst3 * fVec8[1]));
			fRec3[0] = (fTempPerm12 - floorf(fTempPerm12));
			fTempPerm13 = (2 * fRec3[0]);
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
			fTempPerm21 = (fSlow10 * fRec2[0]);
			fTempPerm22 = max(20.0f, fabsf(fTempPerm21));
			fVec15[0] = fTempPerm22;
			fTempPerm23 = (fRec4[1] + (fConst3 * fVec15[1]));
			fRec4[0] = (fTempPerm23 - floorf(fTempPerm23));
			fTempPerm24 = (2 * fRec4[0]);
			fTempPerm25 = (fTempPerm24 + -1);
			fTempPerm26 = faustpower<2>(fTempPerm25);
			fVec16[0] = fTempPerm26;
			fTempPerm27 = (fVec16[0] * (fVec16[0] + -2.0f));
			fVec17[0] = fTempPerm27;
			fTempPerm28 = ((fVec17[0] - fVec17[1]) / fVec15[0]);
			fVec18[0] = fTempPerm28;
			fTempPerm29 = ((fVec18[0] - fVec18[1]) / fVec15[0]);
			fVec19[0] = fTempPerm29;
			fTempPerm30 = faustpower<3>(fTempPerm25);
			fVec20[0] = (fTempPerm30 + (1 - fTempPerm24));
			fTempPerm31 = ((fTempPerm30 + (1 - (fTempPerm24 + fVec20[1]))) / fVec15[0]);
			fVec21[0] = fTempPerm31;
			fTempPerm32 = max(fRec2[0], 23.448949682462139f);
			fTempPerm33 = max(20.0f, fabsf(fTempPerm32));
			fVec22[0] = fTempPerm33;
			fTempPerm34 = (fRec5[1] + (fConst3 * fVec22[1]));
			fRec5[0] = (fTempPerm34 - floorf(fTempPerm34));
			fTempPerm35 = (2 * fRec5[0]);
			fTempPerm36 = (fTempPerm35 + -1);
			fTempPerm37 = faustpower<2>(fTempPerm36);
			fVec23[0] = fTempPerm37;
			fTempPerm38 = ((iVec0[1] * (fVec23[0] - fVec23[1])) / fVec22[0]);
			fVec24[IOTA&4095] = fTempPerm38;
			fTempPerm39 = max((float)0, min((float)2047, (fConst7 / fTempPerm32)));
			iTempPerm40 = int(fTempPerm39);
			fTempPerm41 = floorf(fTempPerm39);
			fTempPerm42 = ((fVec24[IOTA&4095] - (fVec24[(IOTA-iTempPerm40)&4095] * (fTempPerm41 + (1 - fTempPerm39)))) - ((fTempPerm39 - fTempPerm41) * fVec24[(IOTA-int((iTempPerm40 + 1)))&4095]));
			fTempPerm43 = max(fTempPerm10, 23.448949682462139f);
			fTempPerm44 = max(20.0f, fabsf(fTempPerm43));
			fVec25[0] = fTempPerm44;
			fTempPerm45 = (fRec6[1] + (fConst3 * fVec25[1]));
			fRec6[0] = (fTempPerm45 - floorf(fTempPerm45));
			fTempPerm46 = (2 * fRec6[0]);
			fTempPerm47 = (fTempPerm46 + -1);
			fTempPerm48 = faustpower<2>(fTempPerm47);
			fVec26[0] = fTempPerm48;
			fTempPerm49 = ((iVec0[1] * (fVec26[0] - fVec26[1])) / fVec25[0]);
			fVec27[IOTA&4095] = fTempPerm49;
			fTempPerm50 = max((float)0, min((float)2047, (fConst7 / fTempPerm43)));
			iTempPerm51 = int(fTempPerm50);
			fTempPerm52 = floorf(fTempPerm50);
			fTempPerm53 = ((fVec27[IOTA&4095] - (fVec27[(IOTA-iTempPerm51)&4095] * (fTempPerm52 + (1 - fTempPerm50)))) - ((fTempPerm50 - fTempPerm52) * fVec27[(IOTA-int((iTempPerm51 + 1)))&4095]));
			fTempPerm54 = max(fTempPerm21, 23.448949682462139f);
			fTempPerm55 = max(20.0f, fabsf(fTempPerm54));
			fVec28[0] = fTempPerm55;
			fTempPerm56 = (fRec7[1] + (fConst3 * fVec28[1]));
			fRec7[0] = (fTempPerm56 - floorf(fTempPerm56));
			fTempPerm57 = (2 * fRec7[0]);
			fTempPerm58 = (fTempPerm57 + -1);
			fTempPerm59 = faustpower<2>(fTempPerm58);
			fVec29[0] = fTempPerm59;
			fTempPerm60 = ((iVec0[1] * (fVec29[0] - fVec29[1])) / fVec28[0]);
			fVec30[IOTA&4095] = fTempPerm60;
			fTempPerm61 = max((float)0, min((float)2047, (fConst7 / fTempPerm54)));
			iTempPerm62 = int(fTempPerm61);
			fTempPerm63 = floorf(fTempPerm61);
			fTempPerm64 = ((fVec30[IOTA&4095] - (fVec30[(IOTA-iTempPerm62)&4095] * (fTempPerm63 + (1 - fTempPerm61)))) - ((fTempPerm61 - fTempPerm63) * fVec30[(IOTA-int((iTempPerm62 + 1)))&4095]));
			fRec8[0] = ((fConst5 * fTempPerm42) + (0.999f * fRec8[1]));
			fRec9[0] = ((fConst5 * fTempPerm53) + (0.999f * fRec9[1]));
			fRec10[0] = ((fConst5 * fTempPerm64) + (0.999f * fRec10[1]));
			fRec11[0] = (fSlow16 + (0.98999999999999999f * fRec11[1]));
			fTempPerm65 = max((float)0, min((float)2047, (fConst1 * (fRec11[0] / fTempPerm32))));
			fTempPerm66 = floorf(fTempPerm65);
			fTempPerm67 = (fTempPerm66 + (1 - fTempPerm65));
			iTempPerm68 = int(fTempPerm65);
			fTempPerm69 = (fTempPerm65 - fTempPerm66);
			iTempPerm70 = int((iTempPerm68 + 1));
			fTempPerm71 = max((float)0, min((float)2047, (fConst1 * (fRec11[0] / fTempPerm43))));
			fTempPerm72 = floorf(fTempPerm71);
			fTempPerm73 = (fTempPerm72 + (1 - fTempPerm71));
			iTempPerm74 = int(fTempPerm71);
			fTempPerm75 = (fTempPerm71 - fTempPerm72);
			iTempPerm76 = int((iTempPerm74 + 1));
			fTempPerm77 = max((float)0, min((float)2047, (fConst1 * (fRec11[0] / fTempPerm54))));
			fTempPerm78 = floorf(fTempPerm77);
			fTempPerm79 = (fTempPerm78 + (1 - fTempPerm77));
			iTempPerm80 = int(fTempPerm77);
			fTempPerm81 = (fTempPerm77 - fTempPerm78);
			iTempPerm82 = int((iTempPerm80 + 1));
			fTempPerm83 = faustpower<3>(fTempPerm36);
			fVec31[0] = (fTempPerm83 + (1 - fTempPerm35));
			fTempPerm84 = ((fTempPerm83 + (1 - (fTempPerm35 + fVec31[1]))) / fVec22[0]);
			fVec32[0] = fTempPerm84;
			fTempPerm85 = ((iVec0[2] * (fVec32[0] - fVec32[1])) / fVec22[0]);
			fVec33[IOTA&4095] = fTempPerm85;
			fTempPerm86 = faustpower<3>(fTempPerm47);
			fVec34[0] = (fTempPerm86 + (1 - fTempPerm46));
			fTempPerm87 = ((fTempPerm86 + (1 - (fTempPerm46 + fVec34[1]))) / fVec25[0]);
			fVec35[0] = fTempPerm87;
			fTempPerm88 = ((iVec0[2] * (fVec35[0] - fVec35[1])) / fVec25[0]);
			fVec36[IOTA&4095] = fTempPerm88;
			fTempPerm89 = faustpower<3>(fTempPerm58);
			fVec37[0] = (fTempPerm89 + (1 - fTempPerm57));
			fTempPerm90 = ((fTempPerm89 + (1 - (fTempPerm57 + fVec37[1]))) / fVec28[0]);
			fVec38[0] = fTempPerm90;
			fTempPerm91 = ((iVec0[2] * (fVec38[0] - fVec38[1])) / fVec28[0]);
			fVec39[IOTA&4095] = fTempPerm91;
			iRec13[0] = ((1103515245 * iRec13[1]) + 12345);
			fRec12[0] = (((0.52218940000000003f * fRec12[3]) + ((4.6566128752457969e-10f * iRec13[0]) + (2.4949560019999999f * fRec12[1]))) - (2.0172658750000001f * fRec12[2]));
			output0[i] = (FAUSTFLOAT)((fSlow0 * (float)input0[i]) + (fRec0[0] * (((((fSlow2 * ((((iSlow4)?((iSlow5)?(fConst2 * ((iVec0[3] * (fVec5[0] - fVec5[1])) / fVec1[0])):(fConst4 * ((iVec0[2] * (fVec7[0] - fVec7[1])) / fVec1[0]))):((iSlow8)?(fConst5 * ((iVec0[1] * (fVec2[0] - fVec2[1])) / fVec1[0])):fTempPerm3)) + ((iSlow4)?((iSlow5)?(fConst2 * ((iVec0[3] * (fVec12[0] - fVec12[1])) / fVec8[0])):(fConst4 * ((iVec0[2] * (fVec14[0] - fVec14[1])) / fVec8[0]))):((iSlow8)?(fConst5 * ((iVec0[1] * (fVec9[0] - fVec9[1])) / fVec8[0])):fTempPerm14))) + ((iSlow4)?((iSlow5)?(fConst2 * ((iVec0[3] * (fVec19[0] - fVec19[1])) / fVec15[0])):(fConst4 * ((iVec0[2] * (fVec21[0] - fVec21[1])) / fVec15[0]))):((iSlow8)?(fConst5 * ((iVec0[1] * (fVec16[0] - fVec16[1])) / fVec15[0])):fTempPerm25)))) + (fSlow11 * ((fTempPerm42 + fTempPerm53) + fTempPerm64))) + (fSlow12 * (fRec2[0] * ((fRec8[0] + (fSlow9 * fRec9[0])) + (fSlow10 * fRec10[0]))))) + (fSlow13 * ((fSlow15 * ((((fVec24[IOTA&4095] - (fTempPerm67 * fVec24[(IOTA-iTempPerm68)&4095])) - (fTempPerm69 * fVec24[(IOTA-iTempPerm70)&4095])) + ((fVec27[IOTA&4095] - (fTempPerm73 * fVec27[(IOTA-iTempPerm74)&4095])) - (fTempPerm75 * fVec27[(IOTA-iTempPerm76)&4095]))) + ((fVec30[IOTA&4095] - (fTempPerm79 * fVec30[(IOTA-iTempPerm80)&4095])) - (fTempPerm81 * fVec30[(IOTA-iTempPerm82)&4095])))) + (fSlow17 * ((((fVec33[IOTA&4095] - (fVec33[(IOTA-iTempPerm68)&4095] * fTempPerm67)) - (fTempPerm69 * fVec33[(IOTA-iTempPerm70)&4095])) + ((fVec36[IOTA&4095] - (fVec36[(IOTA-iTempPerm74)&4095] * fTempPerm73)) - (fTempPerm75 * fVec36[(IOTA-iTempPerm76)&4095]))) + ((fVec39[IOTA&4095] - (fVec39[(IOTA-iTempPerm80)&4095] * fTempPerm79)) - (fTempPerm81 * fVec39[(IOTA-iTempPerm82)&4095]))))))) + (fSlow18 * (((0.049922034999999997f * fRec12[0]) + (0.050612698999999997f * fRec12[2])) - ((0.095993537000000004f * fRec12[1]) + (0.0044087859999999996f * fRec12[3])))))));
			// post processing
			for (int i=3; i>0; i--) fRec12[i] = fRec12[i-1];
			iRec13[1] = iRec13[0];
			fVec38[1] = fVec38[0];
			fVec37[1] = fVec37[0];
			fVec35[1] = fVec35[0];
			fVec34[1] = fVec34[0];
			fVec32[1] = fVec32[0];
			fVec31[1] = fVec31[0];
			fRec11[1] = fRec11[0];
			fRec10[1] = fRec10[0];
			fRec9[1] = fRec9[0];
			fRec8[1] = fRec8[0];
			fVec29[1] = fVec29[0];
			fRec7[1] = fRec7[0];
			fVec28[1] = fVec28[0];
			fVec26[1] = fVec26[0];
			fRec6[1] = fRec6[0];
			fVec25[1] = fVec25[0];
			IOTA = IOTA+1;
			fVec23[1] = fVec23[0];
			fRec5[1] = fRec5[0];
			fVec22[1] = fVec22[0];
			fVec21[1] = fVec21[0];
			fVec20[1] = fVec20[0];
			fVec19[1] = fVec19[0];
			fVec18[1] = fVec18[0];
			fVec17[1] = fVec17[0];
			fVec16[1] = fVec16[0];
			fRec4[1] = fRec4[0];
			fVec15[1] = fVec15[0];
			fVec14[1] = fVec14[0];
			fVec13[1] = fVec13[0];
			fVec12[1] = fVec12[0];
			fVec11[1] = fVec11[0];
			fVec10[1] = fVec10[0];
			fVec9[1] = fVec9[0];
			fRec3[1] = fRec3[0];
			fVec8[1] = fVec8[0];
			fVec7[1] = fVec7[0];
			fVec6[1] = fVec6[0];
			fVec5[1] = fVec5[0];
			fVec4[1] = fVec4[0];
			fVec3[1] = fVec3[0];
			fVec2[1] = fVec2[0];
			fRec1[1] = fRec1[0];
			fVec1[1] = fVec1[0];
			fRec2[1] = fRec2[0];
			fRec0[1] = fRec0[0];
			for (int i=3; i>0; i--) iVec0[i] = iVec0[i-1];
		}
	}
};


