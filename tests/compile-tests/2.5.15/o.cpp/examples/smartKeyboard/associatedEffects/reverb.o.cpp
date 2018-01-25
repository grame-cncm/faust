//----------------------------------------------------------
// name: "reverb"
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
	float 	fRec0[2];
	float 	fTempPerm0;
	int 	IOTA;
	float 	fVec0[16384];
	FAUSTFLOAT 	fslider1;
	float 	fRec1[2];
	float 	fTempPerm1;
	float 	fTempPerm2;
	float 	fConst0;
	float 	fConst1;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT 	fslider5;
	float 	fConst2;
	float 	fConst3;
	FAUSTFLOAT 	fslider6;
	float 	fConst4;
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT 	fslider8;
	float 	fConst5;
	FAUSTFLOAT 	fslider9;
	float 	fRec15[2];
	float 	fRec14[2];
	float 	fVec1[32768];
	float 	fConst6;
	int 	iConst7;
	float 	fTempPerm3;
	float 	fVec2[16384];
	float 	fConst8;
	FAUSTFLOAT 	fslider10;
	float 	fTempPerm4;
	float 	fTempPerm5;
	float 	fVec3[2048];
	int 	iConst9;
	float 	fRec12[2];
	float 	fConst10;
	float 	fConst11;
	float 	fRec19[2];
	float 	fRec18[2];
	float 	fVec4[32768];
	float 	fConst12;
	int 	iConst13;
	float 	fTempPerm6;
	float 	fVec5[4096];
	int 	iConst14;
	float 	fRec16[2];
	float 	fConst15;
	float 	fConst16;
	float 	fRec23[2];
	float 	fRec22[2];
	float 	fVec6[16384];
	float 	fConst17;
	int 	iConst18;
	float 	fTempPerm7;
	float 	fVec7[4096];
	int 	iConst19;
	float 	fRec20[2];
	float 	fConst20;
	float 	fConst21;
	float 	fRec27[2];
	float 	fRec26[2];
	float 	fVec8[32768];
	float 	fConst22;
	int 	iConst23;
	float 	fTempPerm8;
	float 	fVec9[4096];
	int 	iConst24;
	float 	fRec24[2];
	float 	fConst25;
	float 	fConst26;
	float 	fRec31[2];
	float 	fRec30[2];
	float 	fVec10[16384];
	float 	fConst27;
	int 	iConst28;
	float 	fTempPerm9;
	float 	fTempPerm10;
	float 	fVec11[2048];
	int 	iConst29;
	float 	fRec28[2];
	float 	fConst30;
	float 	fConst31;
	float 	fRec35[2];
	float 	fRec34[2];
	float 	fVec12[16384];
	float 	fConst32;
	int 	iConst33;
	float 	fTempPerm11;
	float 	fVec13[4096];
	int 	iConst34;
	float 	fRec32[2];
	float 	fConst35;
	float 	fConst36;
	float 	fRec39[2];
	float 	fRec38[2];
	float 	fVec14[16384];
	float 	fConst37;
	int 	iConst38;
	float 	fTempPerm12;
	float 	fVec15[4096];
	int 	iConst39;
	float 	fRec36[2];
	float 	fConst40;
	float 	fConst41;
	float 	fRec43[2];
	float 	fRec42[2];
	float 	fVec16[16384];
	float 	fConst42;
	int 	iConst43;
	float 	fTempPerm13;
	float 	fVec17[2048];
	int 	iConst44;
	float 	fRec40[2];
	float 	fTempPerm14;
	float 	fTempPerm15;
	float 	fRec4[3];
	float 	fRec5[3];
	float 	fTempPerm16;
	float 	fRec6[3];
	float 	fRec7[3];
	float 	fTempPerm17;
	float 	fTempPerm18;
	float 	fRec8[3];
	float 	fRec9[3];
	float 	fTempPerm19;
	float 	fTempPerm20;
	float 	fRec10[3];
	float 	fRec11[3];
	float 	fTempPerm21;
	float 	fTempPerm22;
	float 	fRec3[3];
	float 	fTempPerm23;
	float 	fTempPerm24;
	float 	fTempPerm25;
	float 	fRec2[3];
	float 	fTempPerm26;
	float 	fTempPerm27;
	float 	fTempPerm28;
	float 	fRec45[3];
	float 	fTempPerm29;
	float 	fTempPerm30;
	float 	fTempPerm31;
	float 	fRec44[3];
	float 	fTempPerm32;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "reverb");
		m->declare("reverbs.lib/name", "Faust Reverb Library");
		m->declare("reverbs.lib/version", "0.0");
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
	}

	virtual int getNumInputs() { return 2; }
	virtual int getNumOutputs() { return 2; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fTempPerm0 = 0;
		fTempPerm1 = 0;
		fTempPerm2 = 0;
		fConst0 = min(192000.0f, max(1.0f, (float)fSamplingFreq));
		fConst1 = (6.2831853071795862f / fConst0);
		fConst2 = floorf(((0.21999099999999999f * fConst0) + 0.5f));
		fConst3 = ((0 - (6.9077552789821377f * fConst2)) / fConst0);
		fConst4 = (6.2831853071795862f / float(fConst0));
		fConst5 = (3.1415926535897931f / fConst0);
		fConst6 = floorf(((0.019123000000000001f * fConst0) + 0.5f));
		iConst7 = int(min((float)16384, max((float)0, (fConst2 - fConst6))));
		fTempPerm3 = 0;
		fConst8 = (0.001f * fConst0);
		fTempPerm4 = 0;
		fTempPerm5 = 0;
		iConst9 = int(min((float)1024, max((float)0, (fConst6 + -1))));
		fConst10 = floorf(((0.25689099999999998f * fConst0) + 0.5f));
		fConst11 = ((0 - (6.9077552789821377f * fConst10)) / fConst0);
		fConst12 = floorf(((0.027333f * fConst0) + 0.5f));
		iConst13 = int(min((float)16384, max((float)0, (fConst10 - fConst12))));
		fTempPerm6 = 0;
		iConst14 = int(min((float)2048, max((float)0, (fConst12 + -1))));
		fConst15 = floorf(((0.192303f * fConst0) + 0.5f));
		fConst16 = ((0 - (6.9077552789821377f * fConst15)) / fConst0);
		fConst17 = floorf(((0.029291000000000001f * fConst0) + 0.5f));
		iConst18 = int(min((float)8192, max((float)0, (fConst15 - fConst17))));
		fTempPerm7 = 0;
		iConst19 = int(min((float)2048, max((float)0, (fConst17 + -1))));
		fConst20 = floorf(((0.21038899999999999f * fConst0) + 0.5f));
		fConst21 = ((0 - (6.9077552789821377f * fConst20)) / fConst0);
		fConst22 = floorf(((0.024421000000000002f * fConst0) + 0.5f));
		iConst23 = int(min((float)16384, max((float)0, (fConst20 - fConst22))));
		fTempPerm8 = 0;
		iConst24 = int(min((float)2048, max((float)0, (fConst22 + -1))));
		fConst25 = floorf(((0.125f * fConst0) + 0.5f));
		fConst26 = ((0 - (6.9077552789821377f * fConst25)) / fConst0);
		fConst27 = floorf(((0.013457999999999999f * fConst0) + 0.5f));
		iConst28 = int(min((float)8192, max((float)0, (fConst25 - fConst27))));
		fTempPerm9 = 0;
		fTempPerm10 = 0;
		iConst29 = int(min((float)1024, max((float)0, (fConst27 + -1))));
		fConst30 = floorf(((0.12783700000000001f * fConst0) + 0.5f));
		fConst31 = ((0 - (6.9077552789821377f * fConst30)) / fConst0);
		fConst32 = floorf(((0.031604f * fConst0) + 0.5f));
		iConst33 = int(min((float)8192, max((float)0, (fConst30 - fConst32))));
		fTempPerm11 = 0;
		iConst34 = int(min((float)2048, max((float)0, (fConst32 + -1))));
		fConst35 = floorf(((0.17471300000000001f * fConst0) + 0.5f));
		fConst36 = ((0 - (6.9077552789821377f * fConst35)) / fConst0);
		fConst37 = floorf(((0.022904000000000001f * fConst0) + 0.5f));
		iConst38 = int(min((float)8192, max((float)0, (fConst35 - fConst37))));
		fTempPerm12 = 0;
		iConst39 = int(min((float)2048, max((float)0, (fConst37 + -1))));
		fConst40 = floorf(((0.15312899999999999f * fConst0) + 0.5f));
		fConst41 = ((0 - (6.9077552789821377f * fConst40)) / fConst0);
		fConst42 = floorf(((0.020346f * fConst0) + 0.5f));
		iConst43 = int(min((float)8192, max((float)0, (fConst40 - fConst42))));
		fTempPerm13 = 0;
		iConst44 = int(min((float)1024, max((float)0, (fConst42 + -1))));
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
		fTempPerm32 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = -20.0f;
		fslider1 = 0.0f;
		fslider2 = 1500.0f;
		fslider3 = 0.0f;
		fslider4 = 315.0f;
		fslider5 = 0.0f;
		fslider6 = 2.0f;
		fslider7 = 6000.0f;
		fslider8 = 3.0f;
		fslider9 = 200.0f;
		fslider10 = 60.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fRec0[i] = 0;
		IOTA = 0;
		for (int i=0; i<16384; i++) fVec0[i] = 0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) fRec15[i] = 0;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		for (int i=0; i<32768; i++) fVec1[i] = 0;
		for (int i=0; i<16384; i++) fVec2[i] = 0;
		for (int i=0; i<2048; i++) fVec3[i] = 0;
		for (int i=0; i<2; i++) fRec12[i] = 0;
		for (int i=0; i<2; i++) fRec19[i] = 0;
		for (int i=0; i<2; i++) fRec18[i] = 0;
		for (int i=0; i<32768; i++) fVec4[i] = 0;
		for (int i=0; i<4096; i++) fVec5[i] = 0;
		for (int i=0; i<2; i++) fRec16[i] = 0;
		for (int i=0; i<2; i++) fRec23[i] = 0;
		for (int i=0; i<2; i++) fRec22[i] = 0;
		for (int i=0; i<16384; i++) fVec6[i] = 0;
		for (int i=0; i<4096; i++) fVec7[i] = 0;
		for (int i=0; i<2; i++) fRec20[i] = 0;
		for (int i=0; i<2; i++) fRec27[i] = 0;
		for (int i=0; i<2; i++) fRec26[i] = 0;
		for (int i=0; i<32768; i++) fVec8[i] = 0;
		for (int i=0; i<4096; i++) fVec9[i] = 0;
		for (int i=0; i<2; i++) fRec24[i] = 0;
		for (int i=0; i<2; i++) fRec31[i] = 0;
		for (int i=0; i<2; i++) fRec30[i] = 0;
		for (int i=0; i<16384; i++) fVec10[i] = 0;
		for (int i=0; i<2048; i++) fVec11[i] = 0;
		for (int i=0; i<2; i++) fRec28[i] = 0;
		for (int i=0; i<2; i++) fRec35[i] = 0;
		for (int i=0; i<2; i++) fRec34[i] = 0;
		for (int i=0; i<16384; i++) fVec12[i] = 0;
		for (int i=0; i<4096; i++) fVec13[i] = 0;
		for (int i=0; i<2; i++) fRec32[i] = 0;
		for (int i=0; i<2; i++) fRec39[i] = 0;
		for (int i=0; i<2; i++) fRec38[i] = 0;
		for (int i=0; i<16384; i++) fVec14[i] = 0;
		for (int i=0; i<4096; i++) fVec15[i] = 0;
		for (int i=0; i<2; i++) fRec36[i] = 0;
		for (int i=0; i<2; i++) fRec43[i] = 0;
		for (int i=0; i<2; i++) fRec42[i] = 0;
		for (int i=0; i<16384; i++) fVec16[i] = 0;
		for (int i=0; i<2048; i++) fVec17[i] = 0;
		for (int i=0; i<2; i++) fRec40[i] = 0;
		for (int i=0; i<3; i++) fRec4[i] = 0;
		for (int i=0; i<3; i++) fRec5[i] = 0;
		for (int i=0; i<3; i++) fRec6[i] = 0;
		for (int i=0; i<3; i++) fRec7[i] = 0;
		for (int i=0; i<3; i++) fRec8[i] = 0;
		for (int i=0; i<3; i++) fRec9[i] = 0;
		for (int i=0; i<3; i++) fRec10[i] = 0;
		for (int i=0; i<3; i++) fRec11[i] = 0;
		for (int i=0; i<3; i++) fRec3[i] = 0;
		for (int i=0; i<3; i++) fRec2[i] = 0;
		for (int i=0; i<3; i++) fRec45[i] = 0;
		for (int i=0; i<3; i++) fRec44[i] = 0;
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
		ui_interface->declare(0, "tooltip", "~ ZITA REV1 FEEDBACK DELAY NETWORK (FDN) & SCHROEDER  ALLPASS-COMB REVERBERATOR (8x8). See Faust's reverbs.lib for documentation and  references");
		ui_interface->openHorizontalBox("Zita_Rev1");
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("Input");
		ui_interface->declare(&fslider10, "1", "");
		ui_interface->declare(&fslider10, "style", "knob");
		ui_interface->declare(&fslider10, "tooltip", "Delay in ms   before reverberation begins");
		ui_interface->declare(&fslider10, "unit", "ms");
		ui_interface->addVerticalSlider("In Delay", &fslider10, 60.0f, 20.0f, 100.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("Decay Times in Bands (see tooltips)");
		ui_interface->declare(&fslider9, "1", "");
		ui_interface->declare(&fslider9, "scale", "log");
		ui_interface->declare(&fslider9, "style", "knob");
		ui_interface->declare(&fslider9, "tooltip", "Crossover frequency (Hz) separating low and middle frequencies");
		ui_interface->declare(&fslider9, "unit", "Hz");
		ui_interface->addVerticalSlider("LF X", &fslider9, 200.0f, 50.0f, 1000.0f, 1.0f);
		ui_interface->declare(&fslider8, "2", "");
		ui_interface->declare(&fslider8, "scale", "log");
		ui_interface->declare(&fslider8, "style", "knob");
		ui_interface->declare(&fslider8, "tooltip", "T60 = time (in seconds) to decay 60dB in low-frequency band");
		ui_interface->declare(&fslider8, "unit", "s");
		ui_interface->addVerticalSlider("Low RT60", &fslider8, 3.0f, 1.0f, 8.0f, 0.10000000000000001f);
		ui_interface->declare(&fslider6, "3", "");
		ui_interface->declare(&fslider6, "scale", "log");
		ui_interface->declare(&fslider6, "style", "knob");
		ui_interface->declare(&fslider6, "tooltip", "T60 = time (in seconds) to decay 60dB in middle band");
		ui_interface->declare(&fslider6, "unit", "s");
		ui_interface->addVerticalSlider("Mid RT60", &fslider6, 2.0f, 1.0f, 8.0f, 0.10000000000000001f);
		ui_interface->declare(&fslider7, "4", "");
		ui_interface->declare(&fslider7, "scale", "log");
		ui_interface->declare(&fslider7, "style", "knob");
		ui_interface->declare(&fslider7, "tooltip", "Frequency (Hz) at which the high-frequency T60 is half the middle-band's T60");
		ui_interface->declare(&fslider7, "unit", "Hz");
		ui_interface->addVerticalSlider("HF Damping", &fslider7, 6000.0f, 1500.0f, 23520.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->declare(0, "3", "");
		ui_interface->openHorizontalBox("RM Peaking Equalizer 1");
		ui_interface->declare(&fslider4, "1", "");
		ui_interface->declare(&fslider4, "scale", "log");
		ui_interface->declare(&fslider4, "style", "knob");
		ui_interface->declare(&fslider4, "tooltip", "Center-frequency of second-order Regalia-Mitra peaking equalizer section 1");
		ui_interface->declare(&fslider4, "unit", "Hz");
		ui_interface->addVerticalSlider("Eq1 Freq", &fslider4, 315.0f, 40.0f, 2500.0f, 1.0f);
		ui_interface->declare(&fslider5, "2", "");
		ui_interface->declare(&fslider5, "style", "knob");
		ui_interface->declare(&fslider5, "tooltip", "Peak level   in dB of second-order Regalia-Mitra peaking equalizer section 1");
		ui_interface->declare(&fslider5, "unit", "dB");
		ui_interface->addVerticalSlider("Eq1 Level", &fslider5, 0.0f, -15.0f, 15.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->declare(0, "4", "");
		ui_interface->openHorizontalBox("RM Peaking Equalizer 2");
		ui_interface->declare(&fslider2, "1", "");
		ui_interface->declare(&fslider2, "scale", "log");
		ui_interface->declare(&fslider2, "style", "knob");
		ui_interface->declare(&fslider2, "tooltip", "Center-frequency of second-order Regalia-Mitra peaking equalizer section 2");
		ui_interface->declare(&fslider2, "unit", "Hz");
		ui_interface->addVerticalSlider("Eq2 Freq", &fslider2, 1500.0f, 160.0f, 10000.0f, 1.0f);
		ui_interface->declare(&fslider3, "2", "");
		ui_interface->declare(&fslider3, "style", "knob");
		ui_interface->declare(&fslider3, "tooltip", "Peak level   in dB of second-order Regalia-Mitra peaking equalizer section 2");
		ui_interface->declare(&fslider3, "unit", "dB");
		ui_interface->addVerticalSlider("Eq2 Level", &fslider3, 0.0f, -15.0f, 15.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->declare(0, "5", "");
		ui_interface->openHorizontalBox("Output");
		ui_interface->declare(&fslider1, "1", "");
		ui_interface->declare(&fslider1, "style", "knob");
		ui_interface->declare(&fslider1, "tooltip", "-1 = dry, 1 = wet");
		ui_interface->addVerticalSlider("Dry/Wet Mix", &fslider1, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider0, "2", "");
		ui_interface->declare(&fslider0, "style", "knob");
		ui_interface->declare(&fslider0, "tooltip", "Output scale   factor");
		ui_interface->declare(&fslider0, "unit", "dB");
		ui_interface->addVerticalSlider("Level", &fslider0, -20.0f, -70.0f, 40.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = (0.0010000000000000009f * powf(10,(0.050000000000000003f * float(fslider0))));
		float 	fSlow1 = (0.0010000000000000009f * float(fslider1));
		float 	fSlow2 = float(fslider2);
		float 	fSlow3 = powf(10,(0.050000000000000003f * float(fslider3)));
		float 	fSlow4 = (fConst1 * (fSlow2 / sqrtf(max((float)0, fSlow3))));
		float 	fSlow5 = ((1.0f - fSlow4) / (fSlow4 + 1.0f));
		float 	fSlow6 = float(fslider4);
		float 	fSlow7 = powf(10,(0.050000000000000003f * float(fslider5)));
		float 	fSlow8 = (fConst1 * (fSlow6 / sqrtf(max((float)0, fSlow7))));
		float 	fSlow9 = ((1.0f - fSlow8) / (fSlow8 + 1.0f));
		float 	fSlow10 = float(fslider6);
		float 	fSlow11 = expf((fConst3 / fSlow10));
		float 	fSlow12 = faustpower<2>(fSlow11);
		float 	fSlow13 = cosf((fConst4 * float(fslider7)));
		float 	fSlow14 = (1.0f - (fSlow12 * fSlow13));
		float 	fSlow15 = (1.0f - fSlow12);
		float 	fSlow16 = (fSlow14 / fSlow15);
		float 	fSlow17 = sqrtf(max((float)0, ((faustpower<2>(fSlow14) / faustpower<2>(fSlow15)) + -1.0f)));
		float 	fSlow18 = (fSlow16 - fSlow17);
		float 	fSlow19 = (fSlow11 * (fSlow17 + (1.0f - fSlow16)));
		float 	fSlow20 = float(fslider8);
		float 	fSlow21 = ((expf((fConst3 / fSlow20)) / fSlow11) + -1);
		float 	fSlow22 = (1.0f / tanf((fConst5 * float(fslider9))));
		float 	fSlow23 = (fSlow22 + 1);
		float 	fSlow24 = (0 - ((1 - fSlow22) / fSlow23));
		float 	fSlow25 = (1.0f / fSlow23);
		int 	iSlow26 = int(min((float)8192, max((float)0, (fConst8 * float(fslider10)))));
		float 	fSlow27 = expf((fConst11 / fSlow10));
		float 	fSlow28 = faustpower<2>(fSlow27);
		float 	fSlow29 = (1.0f - (fSlow13 * fSlow28));
		float 	fSlow30 = (1.0f - fSlow28);
		float 	fSlow31 = (fSlow29 / fSlow30);
		float 	fSlow32 = sqrtf(max((float)0, ((faustpower<2>(fSlow29) / faustpower<2>(fSlow30)) + -1.0f)));
		float 	fSlow33 = (fSlow31 - fSlow32);
		float 	fSlow34 = (fSlow27 * (fSlow32 + (1.0f - fSlow31)));
		float 	fSlow35 = ((expf((fConst11 / fSlow20)) / fSlow27) + -1);
		float 	fSlow36 = expf((fConst16 / fSlow10));
		float 	fSlow37 = faustpower<2>(fSlow36);
		float 	fSlow38 = (1.0f - (fSlow13 * fSlow37));
		float 	fSlow39 = (1.0f - fSlow37);
		float 	fSlow40 = (fSlow38 / fSlow39);
		float 	fSlow41 = sqrtf(max((float)0, ((faustpower<2>(fSlow38) / faustpower<2>(fSlow39)) + -1.0f)));
		float 	fSlow42 = (fSlow40 - fSlow41);
		float 	fSlow43 = (fSlow36 * (fSlow41 + (1.0f - fSlow40)));
		float 	fSlow44 = ((expf((fConst16 / fSlow20)) / fSlow36) + -1);
		float 	fSlow45 = expf((fConst21 / fSlow10));
		float 	fSlow46 = faustpower<2>(fSlow45);
		float 	fSlow47 = (1.0f - (fSlow13 * fSlow46));
		float 	fSlow48 = (1.0f - fSlow46);
		float 	fSlow49 = (fSlow47 / fSlow48);
		float 	fSlow50 = sqrtf(max((float)0, ((faustpower<2>(fSlow47) / faustpower<2>(fSlow48)) + -1.0f)));
		float 	fSlow51 = (fSlow49 - fSlow50);
		float 	fSlow52 = (fSlow45 * (fSlow50 + (1.0f - fSlow49)));
		float 	fSlow53 = ((expf((fConst21 / fSlow20)) / fSlow45) + -1);
		float 	fSlow54 = expf((fConst26 / fSlow10));
		float 	fSlow55 = faustpower<2>(fSlow54);
		float 	fSlow56 = (1.0f - (fSlow13 * fSlow55));
		float 	fSlow57 = (1.0f - fSlow55);
		float 	fSlow58 = (fSlow56 / fSlow57);
		float 	fSlow59 = sqrtf(max((float)0, ((faustpower<2>(fSlow56) / faustpower<2>(fSlow57)) + -1.0f)));
		float 	fSlow60 = (fSlow58 - fSlow59);
		float 	fSlow61 = (fSlow54 * (fSlow59 + (1.0f - fSlow58)));
		float 	fSlow62 = ((expf((fConst26 / fSlow20)) / fSlow54) + -1);
		float 	fSlow63 = expf((fConst31 / fSlow10));
		float 	fSlow64 = faustpower<2>(fSlow63);
		float 	fSlow65 = (1.0f - (fSlow13 * fSlow64));
		float 	fSlow66 = (1.0f - fSlow64);
		float 	fSlow67 = (fSlow65 / fSlow66);
		float 	fSlow68 = sqrtf(max((float)0, ((faustpower<2>(fSlow65) / faustpower<2>(fSlow66)) + -1.0f)));
		float 	fSlow69 = (fSlow67 - fSlow68);
		float 	fSlow70 = (fSlow63 * (fSlow68 + (1.0f - fSlow67)));
		float 	fSlow71 = ((expf((fConst31 / fSlow20)) / fSlow63) + -1);
		float 	fSlow72 = expf((fConst36 / fSlow10));
		float 	fSlow73 = faustpower<2>(fSlow72);
		float 	fSlow74 = (1.0f - (fSlow13 * fSlow73));
		float 	fSlow75 = (1.0f - fSlow73);
		float 	fSlow76 = (fSlow74 / fSlow75);
		float 	fSlow77 = sqrtf(max((float)0, ((faustpower<2>(fSlow74) / faustpower<2>(fSlow75)) + -1.0f)));
		float 	fSlow78 = (fSlow76 - fSlow77);
		float 	fSlow79 = (fSlow72 * (fSlow77 + (1.0f - fSlow76)));
		float 	fSlow80 = ((expf((fConst36 / fSlow20)) / fSlow72) + -1);
		float 	fSlow81 = expf((fConst41 / fSlow10));
		float 	fSlow82 = faustpower<2>(fSlow81);
		float 	fSlow83 = (1.0f - (fSlow13 * fSlow82));
		float 	fSlow84 = (1.0f - fSlow82);
		float 	fSlow85 = (fSlow83 / fSlow84);
		float 	fSlow86 = sqrtf(max((float)0, ((faustpower<2>(fSlow83) / faustpower<2>(fSlow84)) + -1.0f)));
		float 	fSlow87 = (fSlow85 - fSlow86);
		float 	fSlow88 = (fSlow81 * (fSlow86 + (1.0f - fSlow85)));
		float 	fSlow89 = ((expf((fConst41 / fSlow20)) / fSlow81) + -1);
		float 	fSlow90 = ((0 - cosf((fConst1 * fSlow6))) * (fSlow9 + 1));
		float 	fSlow91 = ((0 - cosf((fConst1 * fSlow2))) * (fSlow5 + 1));
		//zone2b
		//zone3
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* input1 = input[1];
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fRec0[0] = (fSlow0 + (0.999f * fRec0[1]));
			fTempPerm0 = (float)input0[i];
			fVec0[IOTA&16383] = fTempPerm0;
			fRec1[0] = (fSlow1 + (0.999f * fRec1[1]));
			fTempPerm1 = (fRec1[0] + 1.0f);
			fTempPerm2 = (1.0f - (0.5f * fTempPerm1));
			fRec15[0] = ((fSlow24 * fRec15[1]) + (fSlow25 * (fRec11[1] + fRec11[2])));
			fRec14[0] = ((fSlow18 * fRec14[1]) + (fSlow19 * (fRec11[1] + (fSlow21 * fRec15[0]))));
			fVec1[IOTA&32767] = ((0.35355339059327373f * fRec14[0]) + 9.9999999999999995e-21f);
			fTempPerm3 = (float)input1[i];
			fVec2[IOTA&16383] = fTempPerm3;
			fTempPerm4 = (0.29999999999999999f * fVec2[(IOTA-iSlow26)&16383]);
			fTempPerm5 = (((0.59999999999999998f * fRec12[1]) + fVec1[(IOTA-iConst7)&32767]) - fTempPerm4);
			fVec3[IOTA&2047] = fTempPerm5;
			fRec12[0] = fVec3[(IOTA-iConst9)&2047];
			float 	fRec13 = (0 - (0.59999999999999998f * fVec3[IOTA&2047]));
			fRec19[0] = ((fSlow24 * fRec19[1]) + (fSlow25 * (fRec7[1] + fRec7[2])));
			fRec18[0] = ((fSlow33 * fRec18[1]) + (fSlow34 * (fRec7[1] + (fSlow35 * fRec19[0]))));
			fVec4[IOTA&32767] = ((0.35355339059327373f * fRec18[0]) + 9.9999999999999995e-21f);
			fTempPerm6 = (((0.59999999999999998f * fRec16[1]) + fVec4[(IOTA-iConst13)&32767]) - fTempPerm4);
			fVec5[IOTA&4095] = fTempPerm6;
			fRec16[0] = fVec5[(IOTA-iConst14)&4095];
			float 	fRec17 = (0 - (0.59999999999999998f * fVec5[IOTA&4095]));
			fRec23[0] = ((fSlow24 * fRec23[1]) + (fSlow25 * (fRec9[1] + fRec9[2])));
			fRec22[0] = ((fSlow42 * fRec22[1]) + (fSlow43 * (fRec9[1] + (fSlow44 * fRec23[0]))));
			fVec6[IOTA&16383] = ((0.35355339059327373f * fRec22[0]) + 9.9999999999999995e-21f);
			fTempPerm7 = (fVec6[(IOTA-iConst18)&16383] + (fTempPerm4 + (0.59999999999999998f * fRec20[1])));
			fVec7[IOTA&4095] = fTempPerm7;
			fRec20[0] = fVec7[(IOTA-iConst19)&4095];
			float 	fRec21 = (0 - (0.59999999999999998f * fVec7[IOTA&4095]));
			fRec27[0] = ((fSlow24 * fRec27[1]) + (fSlow25 * (fRec5[1] + fRec5[2])));
			fRec26[0] = ((fSlow51 * fRec26[1]) + (fSlow52 * (fRec5[1] + (fSlow53 * fRec27[0]))));
			fVec8[IOTA&32767] = ((0.35355339059327373f * fRec26[0]) + 9.9999999999999995e-21f);
			fTempPerm8 = (fTempPerm4 + ((0.59999999999999998f * fRec24[1]) + fVec8[(IOTA-iConst23)&32767]));
			fVec9[IOTA&4095] = fTempPerm8;
			fRec24[0] = fVec9[(IOTA-iConst24)&4095];
			float 	fRec25 = (0 - (0.59999999999999998f * fVec9[IOTA&4095]));
			fRec31[0] = ((fSlow24 * fRec31[1]) + (fSlow25 * (fRec10[1] + fRec10[2])));
			fRec30[0] = ((fSlow60 * fRec30[1]) + (fSlow61 * (fRec10[1] + (fSlow62 * fRec31[0]))));
			fVec10[IOTA&16383] = ((0.35355339059327373f * fRec30[0]) + 9.9999999999999995e-21f);
			fTempPerm9 = (0.29999999999999999f * fVec0[(IOTA-iSlow26)&16383]);
			fTempPerm10 = (fVec10[(IOTA-iConst28)&16383] - (fTempPerm9 + (0.59999999999999998f * fRec28[1])));
			fVec11[IOTA&2047] = fTempPerm10;
			fRec28[0] = fVec11[(IOTA-iConst29)&2047];
			float 	fRec29 = (0.59999999999999998f * fVec11[IOTA&2047]);
			fRec35[0] = ((fSlow24 * fRec35[1]) + (fSlow25 * (fRec6[1] + fRec6[2])));
			fRec34[0] = ((fSlow69 * fRec34[1]) + (fSlow70 * (fRec6[1] + (fSlow71 * fRec35[0]))));
			fVec12[IOTA&16383] = ((0.35355339059327373f * fRec34[0]) + 9.9999999999999995e-21f);
			fTempPerm11 = (fVec12[(IOTA-iConst33)&16383] - (fTempPerm9 + (0.59999999999999998f * fRec32[1])));
			fVec13[IOTA&4095] = fTempPerm11;
			fRec32[0] = fVec13[(IOTA-iConst34)&4095];
			float 	fRec33 = (0.59999999999999998f * fVec13[IOTA&4095]);
			fRec39[0] = ((fSlow24 * fRec39[1]) + (fSlow25 * (fRec8[1] + fRec8[2])));
			fRec38[0] = ((fSlow78 * fRec38[1]) + (fSlow79 * (fRec8[1] + (fSlow80 * fRec39[0]))));
			fVec14[IOTA&16383] = ((0.35355339059327373f * fRec38[0]) + 9.9999999999999995e-21f);
			fTempPerm12 = ((fTempPerm9 + fVec14[(IOTA-iConst38)&16383]) - (0.59999999999999998f * fRec36[1]));
			fVec15[IOTA&4095] = fTempPerm12;
			fRec36[0] = fVec15[(IOTA-iConst39)&4095];
			float 	fRec37 = (0.59999999999999998f * fVec15[IOTA&4095]);
			fRec43[0] = ((fSlow24 * fRec43[1]) + (fSlow25 * (fRec4[1] + fRec4[2])));
			fRec42[0] = ((fSlow87 * fRec42[1]) + (fSlow88 * (fRec4[1] + (fSlow89 * fRec43[0]))));
			fVec16[IOTA&16383] = ((0.35355339059327373f * fRec42[0]) + 9.9999999999999995e-21f);
			fTempPerm13 = ((fVec16[(IOTA-iConst43)&16383] + fTempPerm9) - (0.59999999999999998f * fRec40[1]));
			fVec17[IOTA&2047] = fTempPerm13;
			fRec40[0] = fVec17[(IOTA-iConst44)&2047];
			float 	fRec41 = (0.59999999999999998f * fVec17[IOTA&2047]);
			fTempPerm14 = (fRec41 + fRec37);
			fTempPerm15 = (fRec29 + (fRec33 + fTempPerm14));
			fRec4[0] = (fRec12[1] + (fRec16[1] + (fRec20[1] + (fRec24[1] + (fRec28[1] + (fRec32[1] + (fRec36[1] + (fRec40[1] + (fRec13 + (fRec17 + (fRec21 + (fRec25 + fTempPerm15))))))))))));
			fRec5[0] = ((fRec28[1] + (fRec32[1] + (fRec36[1] + (fRec40[1] + fTempPerm15)))) - (fRec12[1] + (fRec16[1] + (fRec20[1] + (fRec24[1] + (fRec13 + (fRec17 + (fRec25 + fRec21))))))));
			fTempPerm16 = (fRec33 + fRec29);
			fRec6[0] = ((fRec20[1] + (fRec24[1] + (fRec36[1] + (fRec40[1] + (fRec21 + (fRec25 + fTempPerm14)))))) - (fRec12[1] + (fRec16[1] + (fRec28[1] + (fRec32[1] + (fRec13 + (fRec17 + fTempPerm16)))))));
			fRec7[0] = ((fRec12[1] + (fRec16[1] + (fRec36[1] + (fRec40[1] + (fRec13 + (fRec17 + fTempPerm14)))))) - (fRec20[1] + (fRec24[1] + (fRec28[1] + (fRec32[1] + (fRec21 + (fRec25 + fTempPerm16)))))));
			fTempPerm17 = (fRec41 + fRec33);
			fTempPerm18 = (fRec37 + fRec29);
			fRec8[0] = ((fRec16[1] + (fRec24[1] + (fRec32[1] + (fRec40[1] + (fRec17 + (fRec25 + fTempPerm17)))))) - (fRec12[1] + (fRec20[1] + (fRec28[1] + (fRec36[1] + (fRec13 + (fRec21 + fTempPerm18)))))));
			fRec9[0] = ((fRec12[1] + (fRec20[1] + (fRec32[1] + (fRec40[1] + (fRec13 + (fRec21 + fTempPerm17)))))) - (fRec16[1] + (fRec24[1] + (fRec28[1] + (fRec36[1] + (fRec17 + (fRec25 + fTempPerm18)))))));
			fTempPerm19 = (fRec41 + fRec29);
			fTempPerm20 = (fRec37 + fRec33);
			fRec10[0] = ((fRec12[1] + (fRec24[1] + (fRec28[1] + (fRec40[1] + (fRec13 + (fRec25 + fTempPerm19)))))) - (fRec16[1] + (fRec20[1] + (fRec32[1] + (fRec36[1] + (fRec17 + (fRec21 + fTempPerm20)))))));
			fRec11[0] = ((fRec16[1] + (fRec20[1] + (fRec28[1] + (fRec40[1] + (fRec17 + (fRec21 + fTempPerm19)))))) - (fRec12[1] + (fRec24[1] + (fRec32[1] + (fRec36[1] + (fRec13 + (fRec25 + fTempPerm20)))))));
			fTempPerm21 = (0.37f * (fRec5[0] + fRec6[0]));
			fTempPerm22 = (fSlow90 * fRec3[1]);
			fRec3[0] = (fTempPerm21 - (fTempPerm22 + (fSlow9 * fRec3[2])));
			fTempPerm23 = (fSlow9 * fRec3[0]);
			fTempPerm24 = (0.5f * ((fTempPerm23 + (fRec3[2] + (fTempPerm21 + fTempPerm22))) + (fSlow7 * ((fTempPerm23 + (fTempPerm22 + fRec3[2])) - fTempPerm21))));
			fTempPerm25 = (fSlow91 * fRec2[1]);
			fRec2[0] = (fTempPerm24 - (fTempPerm25 + (fSlow5 * fRec2[2])));
			fTempPerm26 = (fSlow5 * fRec2[0]);
			output0[i] = (FAUSTFLOAT)(0.5f * (fRec0[0] * ((fVec0[IOTA&16383] * fTempPerm1) + (fTempPerm2 * ((fTempPerm26 + (fRec2[2] + (fTempPerm24 + fTempPerm25))) + (fSlow3 * ((fTempPerm26 + (fTempPerm25 + fRec2[2])) - fTempPerm24)))))));
			fTempPerm27 = (0.37f * (fRec5[0] - fRec6[0]));
			fTempPerm28 = (fSlow90 * fRec45[1]);
			fRec45[0] = (fTempPerm27 - (fTempPerm28 + (fSlow9 * fRec45[2])));
			fTempPerm29 = (fSlow9 * fRec45[0]);
			fTempPerm30 = (0.5f * ((fTempPerm29 + (fRec45[2] + (fTempPerm27 + fTempPerm28))) + (fSlow7 * ((fTempPerm29 + (fTempPerm28 + fRec45[2])) - fTempPerm27))));
			fTempPerm31 = (fSlow91 * fRec44[1]);
			fRec44[0] = (fTempPerm30 - (fTempPerm31 + (fSlow5 * fRec44[2])));
			fTempPerm32 = (fSlow5 * fRec44[0]);
			output1[i] = (FAUSTFLOAT)(0.5f * (fRec0[0] * ((fVec2[IOTA&16383] * fTempPerm1) + (fTempPerm2 * ((fTempPerm32 + (fRec44[2] + (fTempPerm30 + fTempPerm31))) + (fSlow3 * ((fTempPerm32 + (fTempPerm31 + fRec44[2])) - fTempPerm30)))))));
			// post processing
			fRec44[2] = fRec44[1]; fRec44[1] = fRec44[0];
			fRec45[2] = fRec45[1]; fRec45[1] = fRec45[0];
			fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
			fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
			fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
			fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
			fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
			fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
			fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
			fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
			fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
			fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
			fRec40[1] = fRec40[0];
			fRec42[1] = fRec42[0];
			fRec43[1] = fRec43[0];
			fRec36[1] = fRec36[0];
			fRec38[1] = fRec38[0];
			fRec39[1] = fRec39[0];
			fRec32[1] = fRec32[0];
			fRec34[1] = fRec34[0];
			fRec35[1] = fRec35[0];
			fRec28[1] = fRec28[0];
			fRec30[1] = fRec30[0];
			fRec31[1] = fRec31[0];
			fRec24[1] = fRec24[0];
			fRec26[1] = fRec26[0];
			fRec27[1] = fRec27[0];
			fRec20[1] = fRec20[0];
			fRec22[1] = fRec22[0];
			fRec23[1] = fRec23[0];
			fRec16[1] = fRec16[0];
			fRec18[1] = fRec18[0];
			fRec19[1] = fRec19[0];
			fRec12[1] = fRec12[0];
			fRec14[1] = fRec14[0];
			fRec15[1] = fRec15[0];
			fRec1[1] = fRec1[0];
			IOTA = IOTA+1;
			fRec0[1] = fRec0[0];
		}
	}
};


