//----------------------------------------------------------
// author: "JOS, Revised by RM"
// name: "zitaRevFDN"
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
	float 	fConst0;
	float 	fConst1;
	float 	fConst2;
	FAUSTFLOAT 	fslider0;
	float 	fConst3;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	float 	fConst4;
	FAUSTFLOAT 	fslider3;
	float 	fRec11[2];
	float 	fRec10[2];
	int 	IOTA;
	float 	fVec0[32768];
	float 	fConst5;
	int 	iConst6;
	float 	fTempPerm0;
	float 	fVec1[2048];
	int 	iConst7;
	float 	fRec8[2];
	float 	fConst8;
	float 	fConst9;
	float 	fRec15[2];
	float 	fRec14[2];
	float 	fVec2[32768];
	float 	fConst10;
	int 	iConst11;
	float 	fTempPerm1;
	float 	fVec3[4096];
	int 	iConst12;
	float 	fRec12[2];
	float 	fConst13;
	float 	fConst14;
	float 	fRec19[2];
	float 	fRec18[2];
	float 	fVec4[16384];
	float 	fConst15;
	int 	iConst16;
	float 	fTempPerm2;
	float 	fVec5[4096];
	int 	iConst17;
	float 	fRec16[2];
	float 	fConst18;
	float 	fConst19;
	float 	fRec23[2];
	float 	fRec22[2];
	float 	fVec6[32768];
	float 	fConst20;
	int 	iConst21;
	float 	fTempPerm3;
	float 	fVec7[4096];
	int 	iConst22;
	float 	fRec20[2];
	float 	fConst23;
	float 	fConst24;
	float 	fRec27[2];
	float 	fRec26[2];
	float 	fVec8[16384];
	float 	fConst25;
	int 	iConst26;
	float 	fTempPerm4;
	float 	fVec9[2048];
	int 	iConst27;
	float 	fRec24[2];
	float 	fConst28;
	float 	fConst29;
	float 	fRec31[2];
	float 	fRec30[2];
	float 	fVec10[16384];
	float 	fConst30;
	int 	iConst31;
	float 	fTempPerm5;
	float 	fVec11[4096];
	int 	iConst32;
	float 	fRec28[2];
	float 	fConst33;
	float 	fConst34;
	float 	fRec35[2];
	float 	fRec34[2];
	float 	fVec12[16384];
	float 	fConst35;
	int 	iConst36;
	float 	fTempPerm6;
	float 	fVec13[4096];
	int 	iConst37;
	float 	fRec32[2];
	float 	fConst38;
	float 	fConst39;
	float 	fRec39[2];
	float 	fRec38[2];
	float 	fVec14[16384];
	float 	fConst40;
	int 	iConst41;
	float 	fTempPerm7;
	float 	fVec15[2048];
	int 	iConst42;
	float 	fRec36[2];
	float 	fTempPerm8;
	float 	fTempPerm9;
	float 	fRec0[3];
	float 	fRec1[3];
	float 	fTempPerm10;
	float 	fRec2[3];
	float 	fRec3[3];
	float 	fTempPerm11;
	float 	fTempPerm12;
	float 	fRec4[3];
	float 	fRec5[3];
	float 	fTempPerm13;
	float 	fTempPerm14;
	float 	fRec6[3];
	float 	fRec7[3];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("author", "JOS, Revised by RM");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("description", "Reverb demo application based on `zita_rev_fdn`.");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "zitaRevFDN");
		m->declare("reverbs.lib/name", "Faust Reverb Library");
		m->declare("reverbs.lib/version", "0.0");
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("version", "0.0");
	}

	virtual int getNumInputs() { return 8; }
	virtual int getNumOutputs() { return 8; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(192000.0f, max(1.0f, (float)fSamplingFreq));
		fConst1 = floorf(((0.21999099999999999f * fConst0) + 0.5f));
		fConst2 = ((0 - (6.9077552789821377f * fConst1)) / fConst0);
		fConst3 = (6.2831853071795862f / float(fConst0));
		fConst4 = (3.1415926535897931f / fConst0);
		fConst5 = floorf(((0.019123000000000001f * fConst0) + 0.5f));
		iConst6 = int(min((float)16384, max((float)0, (fConst1 - fConst5))));
		fTempPerm0 = 0;
		iConst7 = int(min((float)1024, max((float)0, (fConst5 + -1))));
		fConst8 = floorf(((0.25689099999999998f * fConst0) + 0.5f));
		fConst9 = ((0 - (6.9077552789821377f * fConst8)) / fConst0);
		fConst10 = floorf(((0.027333f * fConst0) + 0.5f));
		iConst11 = int(min((float)16384, max((float)0, (fConst8 - fConst10))));
		fTempPerm1 = 0;
		iConst12 = int(min((float)2048, max((float)0, (fConst10 + -1))));
		fConst13 = floorf(((0.192303f * fConst0) + 0.5f));
		fConst14 = ((0 - (6.9077552789821377f * fConst13)) / fConst0);
		fConst15 = floorf(((0.029291000000000001f * fConst0) + 0.5f));
		iConst16 = int(min((float)8192, max((float)0, (fConst13 - fConst15))));
		fTempPerm2 = 0;
		iConst17 = int(min((float)2048, max((float)0, (fConst15 + -1))));
		fConst18 = floorf(((0.21038899999999999f * fConst0) + 0.5f));
		fConst19 = ((0 - (6.9077552789821377f * fConst18)) / fConst0);
		fConst20 = floorf(((0.024421000000000002f * fConst0) + 0.5f));
		iConst21 = int(min((float)16384, max((float)0, (fConst18 - fConst20))));
		fTempPerm3 = 0;
		iConst22 = int(min((float)2048, max((float)0, (fConst20 + -1))));
		fConst23 = floorf(((0.125f * fConst0) + 0.5f));
		fConst24 = ((0 - (6.9077552789821377f * fConst23)) / fConst0);
		fConst25 = floorf(((0.013457999999999999f * fConst0) + 0.5f));
		iConst26 = int(min((float)8192, max((float)0, (fConst23 - fConst25))));
		fTempPerm4 = 0;
		iConst27 = int(min((float)1024, max((float)0, (fConst25 + -1))));
		fConst28 = floorf(((0.12783700000000001f * fConst0) + 0.5f));
		fConst29 = ((0 - (6.9077552789821377f * fConst28)) / fConst0);
		fConst30 = floorf(((0.031604f * fConst0) + 0.5f));
		iConst31 = int(min((float)8192, max((float)0, (fConst28 - fConst30))));
		fTempPerm5 = 0;
		iConst32 = int(min((float)2048, max((float)0, (fConst30 + -1))));
		fConst33 = floorf(((0.17471300000000001f * fConst0) + 0.5f));
		fConst34 = ((0 - (6.9077552789821377f * fConst33)) / fConst0);
		fConst35 = floorf(((0.022904000000000001f * fConst0) + 0.5f));
		iConst36 = int(min((float)8192, max((float)0, (fConst33 - fConst35))));
		fTempPerm6 = 0;
		iConst37 = int(min((float)2048, max((float)0, (fConst35 + -1))));
		fConst38 = floorf(((0.15312899999999999f * fConst0) + 0.5f));
		fConst39 = ((0 - (6.9077552789821377f * fConst38)) / fConst0);
		fConst40 = floorf(((0.020346f * fConst0) + 0.5f));
		iConst41 = int(min((float)8192, max((float)0, (fConst38 - fConst40))));
		fTempPerm7 = 0;
		iConst42 = int(min((float)1024, max((float)0, (fConst40 + -1))));
		fTempPerm8 = 0;
		fTempPerm9 = 0;
		fTempPerm10 = 0;
		fTempPerm11 = 0;
		fTempPerm12 = 0;
		fTempPerm13 = 0;
		fTempPerm14 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 2.0f;
		fslider1 = 6000.0f;
		fslider2 = 3.0f;
		fslider3 = 200.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fRec11[i] = 0;
		for (int i=0; i<2; i++) fRec10[i] = 0;
		IOTA = 0;
		for (int i=0; i<32768; i++) fVec0[i] = 0;
		for (int i=0; i<2048; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fRec8[i] = 0;
		for (int i=0; i<2; i++) fRec15[i] = 0;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		for (int i=0; i<32768; i++) fVec2[i] = 0;
		for (int i=0; i<4096; i++) fVec3[i] = 0;
		for (int i=0; i<2; i++) fRec12[i] = 0;
		for (int i=0; i<2; i++) fRec19[i] = 0;
		for (int i=0; i<2; i++) fRec18[i] = 0;
		for (int i=0; i<16384; i++) fVec4[i] = 0;
		for (int i=0; i<4096; i++) fVec5[i] = 0;
		for (int i=0; i<2; i++) fRec16[i] = 0;
		for (int i=0; i<2; i++) fRec23[i] = 0;
		for (int i=0; i<2; i++) fRec22[i] = 0;
		for (int i=0; i<32768; i++) fVec6[i] = 0;
		for (int i=0; i<4096; i++) fVec7[i] = 0;
		for (int i=0; i<2; i++) fRec20[i] = 0;
		for (int i=0; i<2; i++) fRec27[i] = 0;
		for (int i=0; i<2; i++) fRec26[i] = 0;
		for (int i=0; i<16384; i++) fVec8[i] = 0;
		for (int i=0; i<2048; i++) fVec9[i] = 0;
		for (int i=0; i<2; i++) fRec24[i] = 0;
		for (int i=0; i<2; i++) fRec31[i] = 0;
		for (int i=0; i<2; i++) fRec30[i] = 0;
		for (int i=0; i<16384; i++) fVec10[i] = 0;
		for (int i=0; i<4096; i++) fVec11[i] = 0;
		for (int i=0; i<2; i++) fRec28[i] = 0;
		for (int i=0; i<2; i++) fRec35[i] = 0;
		for (int i=0; i<2; i++) fRec34[i] = 0;
		for (int i=0; i<16384; i++) fVec12[i] = 0;
		for (int i=0; i<4096; i++) fVec13[i] = 0;
		for (int i=0; i<2; i++) fRec32[i] = 0;
		for (int i=0; i<2; i++) fRec39[i] = 0;
		for (int i=0; i<2; i++) fRec38[i] = 0;
		for (int i=0; i<16384; i++) fVec14[i] = 0;
		for (int i=0; i<2048; i++) fVec15[i] = 0;
		for (int i=0; i<2; i++) fRec36[i] = 0;
		for (int i=0; i<3; i++) fRec0[i] = 0;
		for (int i=0; i<3; i++) fRec1[i] = 0;
		for (int i=0; i<3; i++) fRec2[i] = 0;
		for (int i=0; i<3; i++) fRec3[i] = 0;
		for (int i=0; i<3; i++) fRec4[i] = 0;
		for (int i=0; i<3; i++) fRec5[i] = 0;
		for (int i=0; i<3; i++) fRec6[i] = 0;
		for (int i=0; i<3; i++) fRec7[i] = 0;
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
		ui_interface->declare(0, "tooltip", "~ Zita_Rev's internal   8x8 Feedback Delay Network (FDN) & Schroeder allpass-comb reverberator.  See   Faust's reverbs.lib for documentation and references");
		ui_interface->openHorizontalBox("Zita_Rev Internal FDN Reverb");
		ui_interface->declare(&fslider2, "1", "");
		ui_interface->declare(&fslider2, "style", "knob");
		ui_interface->declare(&fslider2, "tooltip", "T60 = time (in seconds) to decay 60dB in low-frequency band");
		ui_interface->declare(&fslider2, "unit", "s");
		ui_interface->addVerticalSlider("Low RT60", &fslider2, 3.0f, 1.0f, 8.0f, 0.10000000000000001f);
		ui_interface->declare(&fslider3, "2", "");
		ui_interface->declare(&fslider3, "scale", "log");
		ui_interface->declare(&fslider3, "style", "knob");
		ui_interface->declare(&fslider3, "tooltip", "Crossover frequency (Hz) separating low and middle frequencies");
		ui_interface->declare(&fslider3, "unit", "Hz");
		ui_interface->addVerticalSlider("LF X", &fslider3, 200.0f, 50.0f, 1000.0f, 1.0f);
		ui_interface->declare(&fslider0, "3", "");
		ui_interface->declare(&fslider0, "scale", "log");
		ui_interface->declare(&fslider0, "style", "knob");
		ui_interface->declare(&fslider0, "tooltip", "T60 = time (in seconds) to decay 60dB in middle band");
		ui_interface->declare(&fslider0, "unit", "s");
		ui_interface->addVerticalSlider("Mid RT60", &fslider0, 2.0f, 1.0f, 8.0f, 0.10000000000000001f);
		ui_interface->declare(&fslider1, "4", "");
		ui_interface->declare(&fslider1, "scale", "log");
		ui_interface->declare(&fslider1, "style", "knob");
		ui_interface->declare(&fslider1, "tooltip", "Frequency (Hz) at which the high-frequency T60 is half the middle-band's T60");
		ui_interface->declare(&fslider1, "unit", "Hz");
		ui_interface->addVerticalSlider("HF Damping", &fslider1, 6000.0f, 1500.0f, 23520.0f, 1.0f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = float(fslider0);
		float 	fSlow1 = expf((fConst2 / fSlow0));
		float 	fSlow2 = faustpower<2>(fSlow1);
		float 	fSlow3 = cosf((fConst3 * float(fslider1)));
		float 	fSlow4 = (1.0f - (fSlow2 * fSlow3));
		float 	fSlow5 = (1.0f - fSlow2);
		float 	fSlow6 = (fSlow4 / fSlow5);
		float 	fSlow7 = sqrtf(max((float)0, ((faustpower<2>(fSlow4) / faustpower<2>(fSlow5)) + -1.0f)));
		float 	fSlow8 = (fSlow6 - fSlow7);
		float 	fSlow9 = (fSlow1 * (fSlow7 + (1.0f - fSlow6)));
		float 	fSlow10 = float(fslider2);
		float 	fSlow11 = ((expf((fConst2 / fSlow10)) / fSlow1) + -1);
		float 	fSlow12 = (1.0f / tanf((fConst4 * float(fslider3))));
		float 	fSlow13 = (fSlow12 + 1);
		float 	fSlow14 = (0 - ((1 - fSlow12) / fSlow13));
		float 	fSlow15 = (1.0f / fSlow13);
		float 	fSlow16 = expf((fConst9 / fSlow0));
		float 	fSlow17 = faustpower<2>(fSlow16);
		float 	fSlow18 = (1.0f - (fSlow3 * fSlow17));
		float 	fSlow19 = (1.0f - fSlow17);
		float 	fSlow20 = (fSlow18 / fSlow19);
		float 	fSlow21 = sqrtf(max((float)0, ((faustpower<2>(fSlow18) / faustpower<2>(fSlow19)) + -1.0f)));
		float 	fSlow22 = (fSlow20 - fSlow21);
		float 	fSlow23 = (fSlow16 * (fSlow21 + (1.0f - fSlow20)));
		float 	fSlow24 = ((expf((fConst9 / fSlow10)) / fSlow16) + -1);
		float 	fSlow25 = expf((fConst14 / fSlow0));
		float 	fSlow26 = faustpower<2>(fSlow25);
		float 	fSlow27 = (1.0f - (fSlow3 * fSlow26));
		float 	fSlow28 = (1.0f - fSlow26);
		float 	fSlow29 = (fSlow27 / fSlow28);
		float 	fSlow30 = sqrtf(max((float)0, ((faustpower<2>(fSlow27) / faustpower<2>(fSlow28)) + -1.0f)));
		float 	fSlow31 = (fSlow29 - fSlow30);
		float 	fSlow32 = (fSlow25 * (fSlow30 + (1.0f - fSlow29)));
		float 	fSlow33 = ((expf((fConst14 / fSlow10)) / fSlow25) + -1);
		float 	fSlow34 = expf((fConst19 / fSlow0));
		float 	fSlow35 = faustpower<2>(fSlow34);
		float 	fSlow36 = (1.0f - (fSlow3 * fSlow35));
		float 	fSlow37 = (1.0f - fSlow35);
		float 	fSlow38 = (fSlow36 / fSlow37);
		float 	fSlow39 = sqrtf(max((float)0, ((faustpower<2>(fSlow36) / faustpower<2>(fSlow37)) + -1.0f)));
		float 	fSlow40 = (fSlow38 - fSlow39);
		float 	fSlow41 = (fSlow34 * (fSlow39 + (1.0f - fSlow38)));
		float 	fSlow42 = ((expf((fConst19 / fSlow10)) / fSlow34) + -1);
		float 	fSlow43 = expf((fConst24 / fSlow0));
		float 	fSlow44 = faustpower<2>(fSlow43);
		float 	fSlow45 = (1.0f - (fSlow3 * fSlow44));
		float 	fSlow46 = (1.0f - fSlow44);
		float 	fSlow47 = (fSlow45 / fSlow46);
		float 	fSlow48 = sqrtf(max((float)0, ((faustpower<2>(fSlow45) / faustpower<2>(fSlow46)) + -1.0f)));
		float 	fSlow49 = (fSlow47 - fSlow48);
		float 	fSlow50 = (fSlow43 * (fSlow48 + (1.0f - fSlow47)));
		float 	fSlow51 = ((expf((fConst24 / fSlow10)) / fSlow43) + -1);
		float 	fSlow52 = expf((fConst29 / fSlow0));
		float 	fSlow53 = faustpower<2>(fSlow52);
		float 	fSlow54 = (1.0f - (fSlow3 * fSlow53));
		float 	fSlow55 = (1.0f - fSlow53);
		float 	fSlow56 = (fSlow54 / fSlow55);
		float 	fSlow57 = sqrtf(max((float)0, ((faustpower<2>(fSlow54) / faustpower<2>(fSlow55)) + -1.0f)));
		float 	fSlow58 = (fSlow56 - fSlow57);
		float 	fSlow59 = (fSlow52 * (fSlow57 + (1.0f - fSlow56)));
		float 	fSlow60 = ((expf((fConst29 / fSlow10)) / fSlow52) + -1);
		float 	fSlow61 = expf((fConst34 / fSlow0));
		float 	fSlow62 = faustpower<2>(fSlow61);
		float 	fSlow63 = (1.0f - (fSlow3 * fSlow62));
		float 	fSlow64 = (1.0f - fSlow62);
		float 	fSlow65 = (fSlow63 / fSlow64);
		float 	fSlow66 = sqrtf(max((float)0, ((faustpower<2>(fSlow63) / faustpower<2>(fSlow64)) + -1.0f)));
		float 	fSlow67 = (fSlow65 - fSlow66);
		float 	fSlow68 = (fSlow61 * (fSlow66 + (1.0f - fSlow65)));
		float 	fSlow69 = ((expf((fConst34 / fSlow10)) / fSlow61) + -1);
		float 	fSlow70 = expf((fConst39 / fSlow0));
		float 	fSlow71 = faustpower<2>(fSlow70);
		float 	fSlow72 = (1.0f - (fSlow3 * fSlow71));
		float 	fSlow73 = (1.0f - fSlow71);
		float 	fSlow74 = (fSlow72 / fSlow73);
		float 	fSlow75 = sqrtf(max((float)0, ((faustpower<2>(fSlow72) / faustpower<2>(fSlow73)) + -1.0f)));
		float 	fSlow76 = (fSlow74 - fSlow75);
		float 	fSlow77 = (fSlow70 * (fSlow75 + (1.0f - fSlow74)));
		float 	fSlow78 = ((expf((fConst39 / fSlow10)) / fSlow70) + -1);
		//zone2b
		//zone3
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* input1 = input[1];
		FAUSTFLOAT* input2 = input[2];
		FAUSTFLOAT* input3 = input[3];
		FAUSTFLOAT* input4 = input[4];
		FAUSTFLOAT* input5 = input[5];
		FAUSTFLOAT* input6 = input[6];
		FAUSTFLOAT* input7 = input[7];
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		FAUSTFLOAT* output2 = output[2];
		FAUSTFLOAT* output3 = output[3];
		FAUSTFLOAT* output4 = output[4];
		FAUSTFLOAT* output5 = output[5];
		FAUSTFLOAT* output6 = output[6];
		FAUSTFLOAT* output7 = output[7];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fRec11[0] = ((fSlow14 * fRec11[1]) + (fSlow15 * (fRec7[1] + fRec7[2])));
			fRec10[0] = ((fSlow8 * fRec10[1]) + (fSlow9 * (fRec7[1] + (fSlow11 * fRec11[0]))));
			fVec0[IOTA&32767] = ((0.35355339059327373f * fRec10[0]) + 9.9999999999999995e-21f);
			fTempPerm0 = (fVec0[(IOTA-iConst6)&32767] + ((float)input7[i] + (0.59999999999999998f * fRec8[1])));
			fVec1[IOTA&2047] = fTempPerm0;
			fRec8[0] = fVec1[(IOTA-iConst7)&2047];
			float 	fRec9 = (0 - (0.59999999999999998f * fVec1[IOTA&2047]));
			fRec15[0] = ((fSlow14 * fRec15[1]) + (fSlow15 * (fRec3[1] + fRec3[2])));
			fRec14[0] = ((fSlow22 * fRec14[1]) + (fSlow23 * (fRec3[1] + (fSlow24 * fRec15[0]))));
			fVec2[IOTA&32767] = ((0.35355339059327373f * fRec14[0]) + 9.9999999999999995e-21f);
			fTempPerm1 = (fVec2[(IOTA-iConst11)&32767] + ((float)input3[i] + (0.59999999999999998f * fRec12[1])));
			fVec3[IOTA&4095] = fTempPerm1;
			fRec12[0] = fVec3[(IOTA-iConst12)&4095];
			float 	fRec13 = (0 - (0.59999999999999998f * fVec3[IOTA&4095]));
			fRec19[0] = ((fSlow14 * fRec19[1]) + (fSlow15 * (fRec5[1] + fRec5[2])));
			fRec18[0] = ((fSlow31 * fRec18[1]) + (fSlow32 * (fRec5[1] + (fSlow33 * fRec19[0]))));
			fVec4[IOTA&16383] = ((0.35355339059327373f * fRec18[0]) + 9.9999999999999995e-21f);
			fTempPerm2 = (fVec4[(IOTA-iConst16)&16383] + ((float)input5[i] + (0.59999999999999998f * fRec16[1])));
			fVec5[IOTA&4095] = fTempPerm2;
			fRec16[0] = fVec5[(IOTA-iConst17)&4095];
			float 	fRec17 = (0 - (0.59999999999999998f * fVec5[IOTA&4095]));
			fRec23[0] = ((fSlow14 * fRec23[1]) + (fSlow15 * (fRec1[1] + fRec1[2])));
			fRec22[0] = ((fSlow40 * fRec22[1]) + (fSlow41 * (fRec1[1] + (fSlow42 * fRec23[0]))));
			fVec6[IOTA&32767] = ((0.35355339059327373f * fRec22[0]) + 9.9999999999999995e-21f);
			fTempPerm3 = (fVec6[(IOTA-iConst21)&32767] + ((float)input1[i] + (0.59999999999999998f * fRec20[1])));
			fVec7[IOTA&4095] = fTempPerm3;
			fRec20[0] = fVec7[(IOTA-iConst22)&4095];
			float 	fRec21 = (0 - (0.59999999999999998f * fVec7[IOTA&4095]));
			fRec27[0] = ((fSlow14 * fRec27[1]) + (fSlow15 * (fRec6[1] + fRec6[2])));
			fRec26[0] = ((fSlow49 * fRec26[1]) + (fSlow50 * (fRec6[1] + (fSlow51 * fRec27[0]))));
			fVec8[IOTA&16383] = ((0.35355339059327373f * fRec26[0]) + 9.9999999999999995e-21f);
			fTempPerm4 = (((float)input6[i] + fVec8[(IOTA-iConst26)&16383]) - (0.59999999999999998f * fRec24[1]));
			fVec9[IOTA&2047] = fTempPerm4;
			fRec24[0] = fVec9[(IOTA-iConst27)&2047];
			float 	fRec25 = (0.59999999999999998f * fVec9[IOTA&2047]);
			fRec31[0] = ((fSlow14 * fRec31[1]) + (fSlow15 * (fRec2[1] + fRec2[2])));
			fRec30[0] = ((fSlow58 * fRec30[1]) + (fSlow59 * (fRec2[1] + (fSlow60 * fRec31[0]))));
			fVec10[IOTA&16383] = ((0.35355339059327373f * fRec30[0]) + 9.9999999999999995e-21f);
			fTempPerm5 = (((float)input2[i] + fVec10[(IOTA-iConst31)&16383]) - (0.59999999999999998f * fRec28[1]));
			fVec11[IOTA&4095] = fTempPerm5;
			fRec28[0] = fVec11[(IOTA-iConst32)&4095];
			float 	fRec29 = (0.59999999999999998f * fVec11[IOTA&4095]);
			fRec35[0] = ((fSlow14 * fRec35[1]) + (fSlow15 * (fRec4[1] + fRec4[2])));
			fRec34[0] = ((fSlow67 * fRec34[1]) + (fSlow68 * (fRec4[1] + (fSlow69 * fRec35[0]))));
			fVec12[IOTA&16383] = ((0.35355339059327373f * fRec34[0]) + 9.9999999999999995e-21f);
			fTempPerm6 = (((float)input4[i] + fVec12[(IOTA-iConst36)&16383]) - (0.59999999999999998f * fRec32[1]));
			fVec13[IOTA&4095] = fTempPerm6;
			fRec32[0] = fVec13[(IOTA-iConst37)&4095];
			float 	fRec33 = (0.59999999999999998f * fVec13[IOTA&4095]);
			fRec39[0] = ((fSlow14 * fRec39[1]) + (fSlow15 * (fRec0[1] + fRec0[2])));
			fRec38[0] = ((fSlow76 * fRec38[1]) + (fSlow77 * (fRec0[1] + (fSlow78 * fRec39[0]))));
			fVec14[IOTA&16383] = ((0.35355339059327373f * fRec38[0]) + 9.9999999999999995e-21f);
			fTempPerm7 = (((float)input0[i] + fVec14[(IOTA-iConst41)&16383]) - (0.59999999999999998f * fRec36[1]));
			fVec15[IOTA&2047] = fTempPerm7;
			fRec36[0] = fVec15[(IOTA-iConst42)&2047];
			float 	fRec37 = (0.59999999999999998f * fVec15[IOTA&2047]);
			fTempPerm8 = (fRec37 + fRec33);
			fTempPerm9 = (fRec25 + (fRec29 + fTempPerm8));
			fRec0[0] = (fRec8[1] + (fRec12[1] + (fRec16[1] + (fRec20[1] + (fRec24[1] + (fRec28[1] + (fRec32[1] + (fRec36[1] + (fRec9 + (fRec13 + (fRec17 + (fRec21 + fTempPerm9))))))))))));
			fRec1[0] = ((fRec24[1] + (fRec28[1] + (fRec32[1] + (fRec36[1] + fTempPerm9)))) - (fRec8[1] + (fRec12[1] + (fRec16[1] + (fRec20[1] + (fRec9 + (fRec13 + (fRec21 + fRec17))))))));
			fTempPerm10 = (fRec29 + fRec25);
			fRec2[0] = ((fRec16[1] + (fRec20[1] + (fRec32[1] + (fRec36[1] + (fRec17 + (fRec21 + fTempPerm8)))))) - (fRec8[1] + (fRec12[1] + (fRec24[1] + (fRec28[1] + (fRec9 + (fRec13 + fTempPerm10)))))));
			fRec3[0] = ((fRec8[1] + (fRec12[1] + (fRec32[1] + (fRec36[1] + (fRec9 + (fRec13 + fTempPerm8)))))) - (fRec16[1] + (fRec20[1] + (fRec24[1] + (fRec28[1] + (fRec17 + (fRec21 + fTempPerm10)))))));
			fTempPerm11 = (fRec37 + fRec29);
			fTempPerm12 = (fRec33 + fRec25);
			fRec4[0] = ((fRec12[1] + (fRec20[1] + (fRec28[1] + (fRec36[1] + (fRec13 + (fRec21 + fTempPerm11)))))) - (fRec8[1] + (fRec16[1] + (fRec24[1] + (fRec32[1] + (fRec9 + (fRec17 + fTempPerm12)))))));
			fRec5[0] = ((fRec8[1] + (fRec16[1] + (fRec28[1] + (fRec36[1] + (fRec9 + (fRec17 + fTempPerm11)))))) - (fRec12[1] + (fRec20[1] + (fRec24[1] + (fRec32[1] + (fRec13 + (fRec21 + fTempPerm12)))))));
			fTempPerm13 = (fRec37 + fRec25);
			fTempPerm14 = (fRec33 + fRec29);
			fRec6[0] = ((fRec8[1] + (fRec20[1] + (fRec24[1] + (fRec36[1] + (fRec9 + (fRec21 + fTempPerm13)))))) - (fRec12[1] + (fRec16[1] + (fRec28[1] + (fRec32[1] + (fRec13 + (fRec17 + fTempPerm14)))))));
			fRec7[0] = ((fRec12[1] + (fRec16[1] + (fRec24[1] + (fRec36[1] + (fRec13 + (fRec17 + fTempPerm13)))))) - (fRec8[1] + (fRec20[1] + (fRec28[1] + (fRec32[1] + (fRec9 + (fRec21 + fTempPerm14)))))));
			output0[i] = (FAUSTFLOAT)fRec0[0];
			output1[i] = (FAUSTFLOAT)fRec1[0];
			output2[i] = (FAUSTFLOAT)fRec2[0];
			output3[i] = (FAUSTFLOAT)fRec3[0];
			output4[i] = (FAUSTFLOAT)fRec4[0];
			output5[i] = (FAUSTFLOAT)fRec5[0];
			output6[i] = (FAUSTFLOAT)fRec6[0];
			output7[i] = (FAUSTFLOAT)fRec7[0];
			// post processing
			fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
			fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
			fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
			fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
			fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
			fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
			fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
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
			fRec8[1] = fRec8[0];
			IOTA = IOTA+1;
			fRec10[1] = fRec10[0];
			fRec11[1] = fRec11[0];
		}
	}
};


