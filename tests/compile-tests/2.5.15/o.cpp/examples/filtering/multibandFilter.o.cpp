//----------------------------------------------------------
// author: "Grame"
// copyright: "(c)GRAME 2006"
// license: "BSD"
// name: "multibandFilter"
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
	FAUSTFLOAT 	fentry2;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fentry3;
	FAUSTFLOAT 	fentry4;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fentry5;
	FAUSTFLOAT 	fentry6;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT 	fentry7;
	FAUSTFLOAT 	fentry8;
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT 	fentry9;
	FAUSTFLOAT 	fentry10;
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT 	fentry11;
	FAUSTFLOAT 	fentry12;
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT 	fentry13;
	FAUSTFLOAT 	fentry14;
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT 	fentry15;
	FAUSTFLOAT 	fentry16;
	FAUSTFLOAT 	fslider8;
	FAUSTFLOAT 	fentry17;
	FAUSTFLOAT 	fentry18;
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT 	fentry19;
	float 	fTempPerm0;
	float 	fRec9[3];
	float 	fTempPerm1;
	float 	fRec8[3];
	float 	fTempPerm2;
	float 	fRec7[3];
	float 	fTempPerm3;
	float 	fRec6[3];
	float 	fTempPerm4;
	float 	fRec5[3];
	float 	fTempPerm5;
	float 	fRec4[3];
	float 	fTempPerm6;
	float 	fRec3[3];
	float 	fTempPerm7;
	float 	fRec2[3];
	float 	fTempPerm8;
	float 	fRec1[3];
	float 	fTempPerm9;
	float 	fRec0[3];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("author", "Grame");
		m->declare("bandfilter.dsp/author", "Grame");
		m->declare("bandfilter.dsp/copyright", "(c)GRAME 2006");
		m->declare("bandfilter.dsp/license", "BSD");
		m->declare("bandfilter.dsp/name", "bandFilter");
		m->declare("bandfilter.dsp/version", "1.0");
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
		m->declare("name", "multibandFilter");
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
		fTempPerm1 = 0;
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
		fentry0 = 10000.0f;
		fslider0 = 0.0f;
		fentry1 = 50.0f;
		fentry2 = 9000.0f;
		fslider1 = 0.0f;
		fentry3 = 50.0f;
		fentry4 = 8000.0f;
		fslider2 = 0.0f;
		fentry5 = 50.0f;
		fentry6 = 7000.0f;
		fslider3 = 0.0f;
		fentry7 = 50.0f;
		fentry8 = 6000.0f;
		fslider4 = 0.0f;
		fentry9 = 50.0f;
		fentry10 = 5000.0f;
		fslider5 = 0.0f;
		fentry11 = 50.0f;
		fentry12 = 4000.0f;
		fslider6 = 0.0f;
		fentry13 = 50.0f;
		fentry14 = 3000.0f;
		fslider7 = 0.0f;
		fentry15 = 50.0f;
		fentry16 = 2000.0f;
		fslider8 = 0.0f;
		fentry17 = 50.0f;
		fentry18 = 1000.0f;
		fslider9 = 0.0f;
		fentry19 = 50.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<3; i++) fRec9[i] = 0;
		for (int i=0; i<3; i++) fRec8[i] = 0;
		for (int i=0; i<3; i++) fRec7[i] = 0;
		for (int i=0; i<3; i++) fRec6[i] = 0;
		for (int i=0; i<3; i++) fRec5[i] = 0;
		for (int i=0; i<3; i++) fRec4[i] = 0;
		for (int i=0; i<3; i++) fRec3[i] = 0;
		for (int i=0; i<3; i++) fRec2[i] = 0;
		for (int i=0; i<3; i++) fRec1[i] = 0;
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
		ui_interface->openHorizontalBox("Multi Band Filter");
		ui_interface->openVerticalBox("peak 0");
		ui_interface->declare(&fentry19, "style", "knob");
		ui_interface->addNumEntry("Q factor", &fentry19, 50.0f, 0.10000000000000001f, 100.0f, 0.10000000000000001f);
		ui_interface->declare(&fentry18, "style", "knob");
		ui_interface->declare(&fentry18, "unit", "Hz");
		ui_interface->addNumEntry("freq", &fentry18, 1000.0f, 20.0f, 20000.0f, 1.0f);
		ui_interface->declare(&fslider9, "unit", "dB");
		ui_interface->addVerticalSlider("gain", &fslider9, 0.0f, -50.0f, 50.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("peak 1");
		ui_interface->declare(&fentry17, "style", "knob");
		ui_interface->addNumEntry("Q factor", &fentry17, 50.0f, 0.10000000000000001f, 100.0f, 0.10000000000000001f);
		ui_interface->declare(&fentry16, "style", "knob");
		ui_interface->declare(&fentry16, "unit", "Hz");
		ui_interface->addNumEntry("freq", &fentry16, 2000.0f, 20.0f, 20000.0f, 1.0f);
		ui_interface->declare(&fslider8, "unit", "dB");
		ui_interface->addVerticalSlider("gain", &fslider8, 0.0f, -50.0f, 50.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("peak 2");
		ui_interface->declare(&fentry15, "style", "knob");
		ui_interface->addNumEntry("Q factor", &fentry15, 50.0f, 0.10000000000000001f, 100.0f, 0.10000000000000001f);
		ui_interface->declare(&fentry14, "style", "knob");
		ui_interface->declare(&fentry14, "unit", "Hz");
		ui_interface->addNumEntry("freq", &fentry14, 3000.0f, 20.0f, 20000.0f, 1.0f);
		ui_interface->declare(&fslider7, "unit", "dB");
		ui_interface->addVerticalSlider("gain", &fslider7, 0.0f, -50.0f, 50.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("peak 3");
		ui_interface->declare(&fentry13, "style", "knob");
		ui_interface->addNumEntry("Q factor", &fentry13, 50.0f, 0.10000000000000001f, 100.0f, 0.10000000000000001f);
		ui_interface->declare(&fentry12, "style", "knob");
		ui_interface->declare(&fentry12, "unit", "Hz");
		ui_interface->addNumEntry("freq", &fentry12, 4000.0f, 20.0f, 20000.0f, 1.0f);
		ui_interface->declare(&fslider6, "unit", "dB");
		ui_interface->addVerticalSlider("gain", &fslider6, 0.0f, -50.0f, 50.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("peak 4");
		ui_interface->declare(&fentry11, "style", "knob");
		ui_interface->addNumEntry("Q factor", &fentry11, 50.0f, 0.10000000000000001f, 100.0f, 0.10000000000000001f);
		ui_interface->declare(&fentry10, "style", "knob");
		ui_interface->declare(&fentry10, "unit", "Hz");
		ui_interface->addNumEntry("freq", &fentry10, 5000.0f, 20.0f, 20000.0f, 1.0f);
		ui_interface->declare(&fslider5, "unit", "dB");
		ui_interface->addVerticalSlider("gain", &fslider5, 0.0f, -50.0f, 50.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("peak 5");
		ui_interface->declare(&fentry9, "style", "knob");
		ui_interface->addNumEntry("Q factor", &fentry9, 50.0f, 0.10000000000000001f, 100.0f, 0.10000000000000001f);
		ui_interface->declare(&fentry8, "style", "knob");
		ui_interface->declare(&fentry8, "unit", "Hz");
		ui_interface->addNumEntry("freq", &fentry8, 6000.0f, 20.0f, 20000.0f, 1.0f);
		ui_interface->declare(&fslider4, "unit", "dB");
		ui_interface->addVerticalSlider("gain", &fslider4, 0.0f, -50.0f, 50.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("peak 6");
		ui_interface->declare(&fentry7, "style", "knob");
		ui_interface->addNumEntry("Q factor", &fentry7, 50.0f, 0.10000000000000001f, 100.0f, 0.10000000000000001f);
		ui_interface->declare(&fentry6, "style", "knob");
		ui_interface->declare(&fentry6, "unit", "Hz");
		ui_interface->addNumEntry("freq", &fentry6, 7000.0f, 20.0f, 20000.0f, 1.0f);
		ui_interface->declare(&fslider3, "unit", "dB");
		ui_interface->addVerticalSlider("gain", &fslider3, 0.0f, -50.0f, 50.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("peak 7");
		ui_interface->declare(&fentry5, "style", "knob");
		ui_interface->addNumEntry("Q factor", &fentry5, 50.0f, 0.10000000000000001f, 100.0f, 0.10000000000000001f);
		ui_interface->declare(&fentry4, "style", "knob");
		ui_interface->declare(&fentry4, "unit", "Hz");
		ui_interface->addNumEntry("freq", &fentry4, 8000.0f, 20.0f, 20000.0f, 1.0f);
		ui_interface->declare(&fslider2, "unit", "dB");
		ui_interface->addVerticalSlider("gain", &fslider2, 0.0f, -50.0f, 50.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("peak 8");
		ui_interface->declare(&fentry3, "style", "knob");
		ui_interface->addNumEntry("Q factor", &fentry3, 50.0f, 0.10000000000000001f, 100.0f, 0.10000000000000001f);
		ui_interface->declare(&fentry2, "style", "knob");
		ui_interface->declare(&fentry2, "unit", "Hz");
		ui_interface->addNumEntry("freq", &fentry2, 9000.0f, 20.0f, 20000.0f, 1.0f);
		ui_interface->declare(&fslider1, "unit", "dB");
		ui_interface->addVerticalSlider("gain", &fslider1, 0.0f, -50.0f, 50.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("peak 9");
		ui_interface->declare(&fentry1, "style", "knob");
		ui_interface->addNumEntry("Q factor", &fentry1, 50.0f, 0.10000000000000001f, 100.0f, 0.10000000000000001f);
		ui_interface->declare(&fentry0, "style", "knob");
		ui_interface->declare(&fentry0, "unit", "Hz");
		ui_interface->addNumEntry("freq", &fentry0, 10000.0f, 20.0f, 20000.0f, 1.0f);
		ui_interface->declare(&fslider0, "unit", "dB");
		ui_interface->addVerticalSlider("gain", &fslider0, 0.0f, -50.0f, 50.0f, 0.10000000000000001f);
		ui_interface->closeBox();
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
		float 	fSlow5 = tanf((fConst0 * float(fentry2)));
		float 	fSlow6 = float(fentry3);
		float 	fSlow7 = (powf(10,(0.050000000000000003f * (0 - float(fslider1)))) / fSlow6);
		float 	fSlow8 = (1.0f / ((fSlow5 * (fSlow5 + fSlow7)) + 1));
		float 	fSlow9 = (2 * (faustpower<2>(fSlow5) + -1));
		float 	fSlow10 = tanf((fConst0 * float(fentry4)));
		float 	fSlow11 = float(fentry5);
		float 	fSlow12 = (powf(10,(0.050000000000000003f * (0 - float(fslider2)))) / fSlow11);
		float 	fSlow13 = (1.0f / ((fSlow10 * (fSlow10 + fSlow12)) + 1));
		float 	fSlow14 = (2 * (faustpower<2>(fSlow10) + -1));
		float 	fSlow15 = tanf((fConst0 * float(fentry6)));
		float 	fSlow16 = float(fentry7);
		float 	fSlow17 = (powf(10,(0.050000000000000003f * (0 - float(fslider3)))) / fSlow16);
		float 	fSlow18 = (1.0f / ((fSlow15 * (fSlow15 + fSlow17)) + 1));
		float 	fSlow19 = (2 * (faustpower<2>(fSlow15) + -1));
		float 	fSlow20 = tanf((fConst0 * float(fentry8)));
		float 	fSlow21 = float(fentry9);
		float 	fSlow22 = (powf(10,(0.050000000000000003f * (0 - float(fslider4)))) / fSlow21);
		float 	fSlow23 = (1.0f / ((fSlow20 * (fSlow20 + fSlow22)) + 1));
		float 	fSlow24 = (2 * (faustpower<2>(fSlow20) + -1));
		float 	fSlow25 = tanf((fConst0 * float(fentry10)));
		float 	fSlow26 = float(fentry11);
		float 	fSlow27 = (powf(10,(0.050000000000000003f * (0 - float(fslider5)))) / fSlow26);
		float 	fSlow28 = (1.0f / ((fSlow25 * (fSlow25 + fSlow27)) + 1));
		float 	fSlow29 = (2 * (faustpower<2>(fSlow25) + -1));
		float 	fSlow30 = tanf((fConst0 * float(fentry12)));
		float 	fSlow31 = float(fentry13);
		float 	fSlow32 = (powf(10,(0.050000000000000003f * (0 - float(fslider6)))) / fSlow31);
		float 	fSlow33 = (1.0f / ((fSlow30 * (fSlow30 + fSlow32)) + 1));
		float 	fSlow34 = (2 * (faustpower<2>(fSlow30) + -1));
		float 	fSlow35 = tanf((fConst0 * float(fentry14)));
		float 	fSlow36 = float(fentry15);
		float 	fSlow37 = (powf(10,(0.050000000000000003f * (0 - float(fslider7)))) / fSlow36);
		float 	fSlow38 = (1.0f / ((fSlow35 * (fSlow35 + fSlow37)) + 1));
		float 	fSlow39 = (2 * (faustpower<2>(fSlow35) + -1));
		float 	fSlow40 = tanf((fConst0 * float(fentry16)));
		float 	fSlow41 = float(fentry17);
		float 	fSlow42 = (powf(10,(0.050000000000000003f * (0 - float(fslider8)))) / fSlow41);
		float 	fSlow43 = (1.0f / ((fSlow40 * (fSlow40 + fSlow42)) + 1));
		float 	fSlow44 = (2 * (faustpower<2>(fSlow40) + -1));
		float 	fSlow45 = tanf((fConst0 * float(fentry18)));
		float 	fSlow46 = float(fentry19);
		float 	fSlow47 = (powf(10,(0.050000000000000003f * (0 - float(fslider9)))) / fSlow46);
		float 	fSlow48 = (1.0f / ((fSlow45 * (fSlow45 + fSlow47)) + 1));
		float 	fSlow49 = (2 * (faustpower<2>(fSlow45) + -1));
		float 	fSlow50 = ((fSlow45 * (fSlow45 - fSlow47)) + 1);
		float 	fSlow51 = (1.0f / fSlow46);
		float 	fSlow52 = ((fSlow45 * (fSlow45 + fSlow51)) + 1);
		float 	fSlow53 = (1 - (fSlow45 * (fSlow51 - fSlow45)));
		float 	fSlow54 = ((fSlow40 * (fSlow40 - fSlow42)) + 1);
		float 	fSlow55 = (1.0f / fSlow41);
		float 	fSlow56 = ((fSlow40 * (fSlow40 + fSlow55)) + 1);
		float 	fSlow57 = (1 - (fSlow40 * (fSlow55 - fSlow40)));
		float 	fSlow58 = ((fSlow35 * (fSlow35 - fSlow37)) + 1);
		float 	fSlow59 = (1.0f / fSlow36);
		float 	fSlow60 = ((fSlow35 * (fSlow35 + fSlow59)) + 1);
		float 	fSlow61 = (1 - (fSlow35 * (fSlow59 - fSlow35)));
		float 	fSlow62 = ((fSlow30 * (fSlow30 - fSlow32)) + 1);
		float 	fSlow63 = (1.0f / fSlow31);
		float 	fSlow64 = ((fSlow30 * (fSlow30 + fSlow63)) + 1);
		float 	fSlow65 = (1 - (fSlow30 * (fSlow63 - fSlow30)));
		float 	fSlow66 = ((fSlow25 * (fSlow25 - fSlow27)) + 1);
		float 	fSlow67 = (1.0f / fSlow26);
		float 	fSlow68 = ((fSlow25 * (fSlow25 + fSlow67)) + 1);
		float 	fSlow69 = (1 - (fSlow25 * (fSlow67 - fSlow25)));
		float 	fSlow70 = ((fSlow20 * (fSlow20 - fSlow22)) + 1);
		float 	fSlow71 = (1.0f / fSlow21);
		float 	fSlow72 = ((fSlow20 * (fSlow20 + fSlow71)) + 1);
		float 	fSlow73 = (1 - (fSlow20 * (fSlow71 - fSlow20)));
		float 	fSlow74 = ((fSlow15 * (fSlow15 - fSlow17)) + 1);
		float 	fSlow75 = (1.0f / fSlow16);
		float 	fSlow76 = ((fSlow15 * (fSlow15 + fSlow75)) + 1);
		float 	fSlow77 = (1 - (fSlow15 * (fSlow75 - fSlow15)));
		float 	fSlow78 = ((fSlow10 * (fSlow10 - fSlow12)) + 1);
		float 	fSlow79 = (1.0f / fSlow11);
		float 	fSlow80 = ((fSlow10 * (fSlow10 + fSlow79)) + 1);
		float 	fSlow81 = (1 - (fSlow10 * (fSlow79 - fSlow10)));
		float 	fSlow82 = ((fSlow5 * (fSlow5 - fSlow7)) + 1);
		float 	fSlow83 = (1.0f / fSlow6);
		float 	fSlow84 = ((fSlow5 * (fSlow5 + fSlow83)) + 1);
		float 	fSlow85 = (1 - (fSlow5 * (fSlow83 - fSlow5)));
		float 	fSlow86 = ((fSlow0 * (fSlow0 - fSlow2)) + 1);
		float 	fSlow87 = (1.0f / fSlow1);
		float 	fSlow88 = ((fSlow0 * (fSlow0 + fSlow87)) + 1);
		float 	fSlow89 = (1 - (fSlow0 * (fSlow87 - fSlow0)));
		//zone2b
		//zone3
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* output0 = output[0];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fTempPerm0 = (fSlow49 * fRec9[1]);
			fRec9[0] = ((float)input0[i] - (fSlow48 * ((fSlow50 * fRec9[2]) + fTempPerm0)));
			fTempPerm1 = (fSlow44 * fRec8[1]);
			fRec8[0] = ((fSlow48 * ((fTempPerm0 + (fSlow52 * fRec9[0])) + (fSlow53 * fRec9[2]))) - (fSlow43 * ((fSlow54 * fRec8[2]) + fTempPerm1)));
			fTempPerm2 = (fSlow39 * fRec7[1]);
			fRec7[0] = ((fSlow43 * ((fTempPerm1 + (fSlow56 * fRec8[0])) + (fSlow57 * fRec8[2]))) - (fSlow38 * ((fSlow58 * fRec7[2]) + fTempPerm2)));
			fTempPerm3 = (fSlow34 * fRec6[1]);
			fRec6[0] = ((fSlow38 * ((fTempPerm2 + (fSlow60 * fRec7[0])) + (fSlow61 * fRec7[2]))) - (fSlow33 * ((fSlow62 * fRec6[2]) + fTempPerm3)));
			fTempPerm4 = (fSlow29 * fRec5[1]);
			fRec5[0] = ((fSlow33 * ((fTempPerm3 + (fSlow64 * fRec6[0])) + (fSlow65 * fRec6[2]))) - (fSlow28 * ((fSlow66 * fRec5[2]) + fTempPerm4)));
			fTempPerm5 = (fSlow24 * fRec4[1]);
			fRec4[0] = ((fSlow28 * ((fTempPerm4 + (fSlow68 * fRec5[0])) + (fSlow69 * fRec5[2]))) - (fSlow23 * ((fSlow70 * fRec4[2]) + fTempPerm5)));
			fTempPerm6 = (fSlow19 * fRec3[1]);
			fRec3[0] = ((fSlow23 * ((fTempPerm5 + (fSlow72 * fRec4[0])) + (fSlow73 * fRec4[2]))) - (fSlow18 * ((fSlow74 * fRec3[2]) + fTempPerm6)));
			fTempPerm7 = (fSlow14 * fRec2[1]);
			fRec2[0] = ((fSlow18 * ((fTempPerm6 + (fSlow76 * fRec3[0])) + (fSlow77 * fRec3[2]))) - (fSlow13 * ((fSlow78 * fRec2[2]) + fTempPerm7)));
			fTempPerm8 = (fSlow9 * fRec1[1]);
			fRec1[0] = ((fSlow13 * ((fTempPerm7 + (fSlow80 * fRec2[0])) + (fSlow81 * fRec2[2]))) - (fSlow8 * ((fSlow82 * fRec1[2]) + fTempPerm8)));
			fTempPerm9 = (fSlow4 * fRec0[1]);
			fRec0[0] = ((fSlow8 * ((fTempPerm8 + (fSlow84 * fRec1[0])) + (fSlow85 * fRec1[2]))) - (fSlow3 * ((fSlow86 * fRec0[2]) + fTempPerm9)));
			output0[i] = (FAUSTFLOAT)(fSlow3 * ((fTempPerm9 + (fSlow88 * fRec0[0])) + (fSlow89 * fRec0[2])));
			// post processing
			fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
			fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
			fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
			fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
			fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
			fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
			fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
			fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
			fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
			fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		}
	}
};


