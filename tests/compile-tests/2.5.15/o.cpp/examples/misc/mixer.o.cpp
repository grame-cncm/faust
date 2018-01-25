//----------------------------------------------------------
// author: "Grame"
// copyright: "(c)GRAME 2006"
// license: "BSD"
// name: "mixer"
// version: "1.0"
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
	float 	fConst0;
	FAUSTFLOAT 	fslider0;
	float 	fRec1[2];
	FAUSTFLOAT 	fentry0;
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT 	fslider1;
	float 	fRec3[2];
	float 	fTempPerm0;
	float 	fRec2[2];
	FAUSTFLOAT 	fbargraph0;
	float 	fTempPerm1;
	FAUSTFLOAT 	fentry1;
	FAUSTFLOAT 	fcheckbox1;
	FAUSTFLOAT 	fslider2;
	float 	fRec5[2];
	float 	fTempPerm2;
	float 	fRec4[2];
	FAUSTFLOAT 	fbargraph1;
	float 	fTempPerm3;
	FAUSTFLOAT 	fentry2;
	FAUSTFLOAT 	fcheckbox2;
	FAUSTFLOAT 	fslider3;
	float 	fRec7[2];
	float 	fTempPerm4;
	float 	fRec6[2];
	FAUSTFLOAT 	fbargraph2;
	float 	fTempPerm5;
	FAUSTFLOAT 	fentry3;
	FAUSTFLOAT 	fcheckbox3;
	FAUSTFLOAT 	fslider4;
	float 	fRec9[2];
	float 	fTempPerm6;
	float 	fRec8[2];
	FAUSTFLOAT 	fbargraph3;
	float 	fTempPerm7;
	FAUSTFLOAT 	fentry4;
	FAUSTFLOAT 	fcheckbox4;
	FAUSTFLOAT 	fslider5;
	float 	fRec11[2];
	float 	fTempPerm8;
	float 	fRec10[2];
	FAUSTFLOAT 	fbargraph4;
	float 	fTempPerm9;
	FAUSTFLOAT 	fentry5;
	FAUSTFLOAT 	fcheckbox5;
	FAUSTFLOAT 	fslider6;
	float 	fRec13[2];
	float 	fTempPerm10;
	float 	fRec12[2];
	FAUSTFLOAT 	fbargraph5;
	float 	fTempPerm11;
	FAUSTFLOAT 	fentry6;
	FAUSTFLOAT 	fcheckbox6;
	FAUSTFLOAT 	fslider7;
	float 	fRec15[2];
	float 	fTempPerm12;
	float 	fRec14[2];
	FAUSTFLOAT 	fbargraph6;
	float 	fTempPerm13;
	FAUSTFLOAT 	fentry7;
	FAUSTFLOAT 	fcheckbox7;
	FAUSTFLOAT 	fslider8;
	float 	fRec17[2];
	float 	fTempPerm14;
	float 	fRec16[2];
	FAUSTFLOAT 	fbargraph7;
	float 	fTempPerm15;
	float 	fTempPerm16;
	float 	fRec0[2];
	FAUSTFLOAT 	fbargraph8;
	float 	fTempPerm17;
	float 	fRec18[2];
	FAUSTFLOAT 	fbargraph9;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("../analysis/vumeter.dsp/author", "Grame");
		m->declare("../analysis/vumeter.dsp/copyright", "(c)GRAME 2006");
		m->declare("../analysis/vumeter.dsp/license", "BSD");
		m->declare("../analysis/vumeter.dsp/name", "vumeter");
		m->declare("../analysis/vumeter.dsp/version", "1.0");
		m->declare("../dynamic/volume.dsp/author", "Grame");
		m->declare("../dynamic/volume.dsp/copyright", "(c)GRAME 2006");
		m->declare("../dynamic/volume.dsp/license", "BSD");
		m->declare("../dynamic/volume.dsp/name", "volume");
		m->declare("../dynamic/volume.dsp/version", "1.0");
		m->declare("../spat/panpot.dsp/author", "Grame");
		m->declare("../spat/panpot.dsp/copyright", "(c)GRAME 2006");
		m->declare("../spat/panpot.dsp/license", "BSD");
		m->declare("../spat/panpot.dsp/name", "panpot");
		m->declare("../spat/panpot.dsp/version", "1.0");
		m->declare("author", "Grame");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("copyright", "(c)GRAME 2006");
		m->declare("license", "BSD");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "mixer");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() { return 8; }
	virtual int getNumOutputs() { return 2; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = (1.0f / min(192000.0f, max(1.0f, (float)fSamplingFreq)));
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
		fTempPerm10 = 0;
		fTempPerm11 = 0;
		fTempPerm12 = 0;
		fTempPerm13 = 0;
		fTempPerm14 = 0;
		fTempPerm15 = 0;
		fTempPerm16 = 0;
		fTempPerm17 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.0f;
		fentry0 = 0.0f;
		fcheckbox0 = 0.0;
		fslider1 = 0.0f;
		fentry1 = 0.0f;
		fcheckbox1 = 0.0;
		fslider2 = 0.0f;
		fentry2 = 0.0f;
		fcheckbox2 = 0.0;
		fslider3 = 0.0f;
		fentry3 = 0.0f;
		fcheckbox3 = 0.0;
		fslider4 = 0.0f;
		fentry4 = 0.0f;
		fcheckbox4 = 0.0;
		fslider5 = 0.0f;
		fentry5 = 0.0f;
		fcheckbox5 = 0.0;
		fslider6 = 0.0f;
		fentry6 = 0.0f;
		fcheckbox6 = 0.0;
		fslider7 = 0.0f;
		fentry7 = 0.0f;
		fcheckbox7 = 0.0;
		fslider8 = 0.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2; i++) fRec7[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<2; i++) fRec9[i] = 0;
		for (int i=0; i<2; i++) fRec8[i] = 0;
		for (int i=0; i<2; i++) fRec11[i] = 0;
		for (int i=0; i<2; i++) fRec10[i] = 0;
		for (int i=0; i<2; i++) fRec13[i] = 0;
		for (int i=0; i<2; i++) fRec12[i] = 0;
		for (int i=0; i<2; i++) fRec15[i] = 0;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		for (int i=0; i<2; i++) fRec17[i] = 0;
		for (int i=0; i<2; i++) fRec16[i] = 0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fRec18[i] = 0;
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
		ui_interface->openHorizontalBox("mixer");
		ui_interface->openVerticalBox("Ch 0");
		ui_interface->declare(&fentry0, "1", "");
		ui_interface->declare(&fentry0, "style", "knob");
		ui_interface->addNumEntry("pan", &fentry0, 0.0f, -90.0f, 90.0f, 1.0f);
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fslider1, "1", "");
		ui_interface->addVerticalSlider("0x00", &fslider1, 0.0f, -70.0f, 4.0f, 0.10000000000000001f);
		ui_interface->declare(&fbargraph0, "2", "");
		ui_interface->declare(&fbargraph0, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fb1a16ddfe0", &fbargraph0, -70.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->addCheckButton("mute", &fcheckbox0);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Ch 1");
		ui_interface->declare(&fentry1, "1", "");
		ui_interface->declare(&fentry1, "style", "knob");
		ui_interface->addNumEntry("pan", &fentry1, 0.0f, -90.0f, 90.0f, 1.0f);
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fslider2, "1", "");
		ui_interface->addVerticalSlider("0x00", &fslider2, 0.0f, -70.0f, 4.0f, 0.10000000000000001f);
		ui_interface->declare(&fbargraph1, "2", "");
		ui_interface->declare(&fbargraph1, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fb1a16e3e40", &fbargraph1, -70.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->addCheckButton("mute", &fcheckbox1);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Ch 2");
		ui_interface->declare(&fentry2, "1", "");
		ui_interface->declare(&fentry2, "style", "knob");
		ui_interface->addNumEntry("pan", &fentry2, 0.0f, -90.0f, 90.0f, 1.0f);
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fslider3, "1", "");
		ui_interface->addVerticalSlider("0x00", &fslider3, 0.0f, -70.0f, 4.0f, 0.10000000000000001f);
		ui_interface->declare(&fbargraph2, "2", "");
		ui_interface->declare(&fbargraph2, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fb1a16ea110", &fbargraph2, -70.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->addCheckButton("mute", &fcheckbox2);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Ch 3");
		ui_interface->declare(&fentry3, "1", "");
		ui_interface->declare(&fentry3, "style", "knob");
		ui_interface->addNumEntry("pan", &fentry3, 0.0f, -90.0f, 90.0f, 1.0f);
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fslider4, "1", "");
		ui_interface->addVerticalSlider("0x00", &fslider4, 0.0f, -70.0f, 4.0f, 0.10000000000000001f);
		ui_interface->declare(&fbargraph3, "2", "");
		ui_interface->declare(&fbargraph3, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fb1a16f06b0", &fbargraph3, -70.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->addCheckButton("mute", &fcheckbox3);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Ch 4");
		ui_interface->declare(&fentry4, "1", "");
		ui_interface->declare(&fentry4, "style", "knob");
		ui_interface->addNumEntry("pan", &fentry4, 0.0f, -90.0f, 90.0f, 1.0f);
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fslider5, "1", "");
		ui_interface->addVerticalSlider("0x00", &fslider5, 0.0f, -70.0f, 4.0f, 0.10000000000000001f);
		ui_interface->declare(&fbargraph4, "2", "");
		ui_interface->declare(&fbargraph4, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fb1a16f6f60", &fbargraph4, -70.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->addCheckButton("mute", &fcheckbox4);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Ch 5");
		ui_interface->declare(&fentry5, "1", "");
		ui_interface->declare(&fentry5, "style", "knob");
		ui_interface->addNumEntry("pan", &fentry5, 0.0f, -90.0f, 90.0f, 1.0f);
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fslider6, "1", "");
		ui_interface->addVerticalSlider("0x00", &fslider6, 0.0f, -70.0f, 4.0f, 0.10000000000000001f);
		ui_interface->declare(&fbargraph5, "2", "");
		ui_interface->declare(&fbargraph5, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fb1a1701a50", &fbargraph5, -70.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->addCheckButton("mute", &fcheckbox5);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Ch 6");
		ui_interface->declare(&fentry6, "1", "");
		ui_interface->declare(&fentry6, "style", "knob");
		ui_interface->addNumEntry("pan", &fentry6, 0.0f, -90.0f, 90.0f, 1.0f);
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fslider7, "1", "");
		ui_interface->addVerticalSlider("0x00", &fslider7, 0.0f, -70.0f, 4.0f, 0.10000000000000001f);
		ui_interface->declare(&fbargraph6, "2", "");
		ui_interface->declare(&fbargraph6, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fb1a17088a0", &fbargraph6, -70.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->addCheckButton("mute", &fcheckbox6);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Ch 7");
		ui_interface->declare(&fentry7, "1", "");
		ui_interface->declare(&fentry7, "style", "knob");
		ui_interface->addNumEntry("pan", &fentry7, 0.0f, -90.0f, 90.0f, 1.0f);
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fslider8, "1", "");
		ui_interface->addVerticalSlider("0x00", &fslider8, 0.0f, -70.0f, 4.0f, 0.10000000000000001f);
		ui_interface->declare(&fbargraph7, "2", "");
		ui_interface->declare(&fbargraph7, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fb1a170f9e0", &fbargraph7, -70.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->addCheckButton("mute", &fcheckbox7);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("stereo out");
		ui_interface->openVerticalBox("L");
		ui_interface->declare(&fbargraph8, "2", "");
		ui_interface->declare(&fbargraph8, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fb1a1711e20", &fbargraph8, -70.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("R");
		ui_interface->declare(&fbargraph9, "2", "");
		ui_interface->declare(&fbargraph9, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fb1a1717380", &fbargraph9, -70.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->declare(&fslider0, "1", "");
		ui_interface->addVerticalSlider("0x00", &fslider0, 0.0f, -70.0f, 4.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = (0.0010000000000000009f * powf(10,(0.050000000000000003f * float(fslider0))));
		float 	fSlow1 = (0.0055555555555555558f * (float(fentry0) + -90.0f));
		float 	fSlow2 = sqrtf((0 - fSlow1));
		float 	fSlow3 = (1 - float(fcheckbox0));
		float 	fSlow4 = (0.0010000000000000009f * powf(10,(0.050000000000000003f * float(fslider1))));
		float 	fSlow5 = (0.0055555555555555558f * (float(fentry1) + -90.0f));
		float 	fSlow6 = sqrtf((0 - fSlow5));
		float 	fSlow7 = (1 - float(fcheckbox1));
		float 	fSlow8 = (0.0010000000000000009f * powf(10,(0.050000000000000003f * float(fslider2))));
		float 	fSlow9 = (0.0055555555555555558f * (float(fentry2) + -90.0f));
		float 	fSlow10 = sqrtf((0 - fSlow9));
		float 	fSlow11 = (1 - float(fcheckbox2));
		float 	fSlow12 = (0.0010000000000000009f * powf(10,(0.050000000000000003f * float(fslider3))));
		float 	fSlow13 = (0.0055555555555555558f * (float(fentry3) + -90.0f));
		float 	fSlow14 = sqrtf((0 - fSlow13));
		float 	fSlow15 = (1 - float(fcheckbox3));
		float 	fSlow16 = (0.0010000000000000009f * powf(10,(0.050000000000000003f * float(fslider4))));
		float 	fSlow17 = (0.0055555555555555558f * (float(fentry4) + -90.0f));
		float 	fSlow18 = sqrtf((0 - fSlow17));
		float 	fSlow19 = (1 - float(fcheckbox4));
		float 	fSlow20 = (0.0010000000000000009f * powf(10,(0.050000000000000003f * float(fslider5))));
		float 	fSlow21 = (0.0055555555555555558f * (float(fentry5) + -90.0f));
		float 	fSlow22 = sqrtf((0 - fSlow21));
		float 	fSlow23 = (1 - float(fcheckbox5));
		float 	fSlow24 = (0.0010000000000000009f * powf(10,(0.050000000000000003f * float(fslider6))));
		float 	fSlow25 = (0.0055555555555555558f * (float(fentry6) + -90.0f));
		float 	fSlow26 = sqrtf((0 - fSlow25));
		float 	fSlow27 = (1 - float(fcheckbox6));
		float 	fSlow28 = (0.0010000000000000009f * powf(10,(0.050000000000000003f * float(fslider7))));
		float 	fSlow29 = (0.0055555555555555558f * (float(fentry7) + -90.0f));
		float 	fSlow30 = sqrtf((0 - fSlow29));
		float 	fSlow31 = (1 - float(fcheckbox7));
		float 	fSlow32 = (0.0010000000000000009f * powf(10,(0.050000000000000003f * float(fslider8))));
		float 	fSlow33 = sqrtf((fSlow1 + 1));
		float 	fSlow34 = sqrtf((fSlow5 + 1));
		float 	fSlow35 = sqrtf((fSlow9 + 1));
		float 	fSlow36 = sqrtf((fSlow13 + 1));
		float 	fSlow37 = sqrtf((fSlow17 + 1));
		float 	fSlow38 = sqrtf((fSlow21 + 1));
		float 	fSlow39 = sqrtf((fSlow25 + 1));
		float 	fSlow40 = sqrtf((fSlow29 + 1));
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
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fRec1[0] = (fSlow0 + (0.999f * fRec1[1]));
			fRec3[0] = (fSlow4 + (0.999f * fRec3[1]));
			fTempPerm0 = (fSlow3 * ((float)input0[i] * fRec3[0]));
			fRec2[0] = max((fRec2[1] - fConst0), fabsf(fTempPerm0));
			fbargraph0 = (20 * log10f(max(0.00031622776601683794f, fRec2[0])));
			fTempPerm1 = fTempPerm0;
			fRec5[0] = (fSlow8 + (0.999f * fRec5[1]));
			fTempPerm2 = (fSlow7 * ((float)input1[i] * fRec5[0]));
			fRec4[0] = max((fRec4[1] - fConst0), fabsf(fTempPerm2));
			fbargraph1 = (20 * log10f(max(0.00031622776601683794f, fRec4[0])));
			fTempPerm3 = fTempPerm2;
			fRec7[0] = (fSlow12 + (0.999f * fRec7[1]));
			fTempPerm4 = (fSlow11 * ((float)input2[i] * fRec7[0]));
			fRec6[0] = max((fRec6[1] - fConst0), fabsf(fTempPerm4));
			fbargraph2 = (20 * log10f(max(0.00031622776601683794f, fRec6[0])));
			fTempPerm5 = fTempPerm4;
			fRec9[0] = (fSlow16 + (0.999f * fRec9[1]));
			fTempPerm6 = (fSlow15 * ((float)input3[i] * fRec9[0]));
			fRec8[0] = max((fRec8[1] - fConst0), fabsf(fTempPerm6));
			fbargraph3 = (20 * log10f(max(0.00031622776601683794f, fRec8[0])));
			fTempPerm7 = fTempPerm6;
			fRec11[0] = (fSlow20 + (0.999f * fRec11[1]));
			fTempPerm8 = (fSlow19 * ((float)input4[i] * fRec11[0]));
			fRec10[0] = max((fRec10[1] - fConst0), fabsf(fTempPerm8));
			fbargraph4 = (20 * log10f(max(0.00031622776601683794f, fRec10[0])));
			fTempPerm9 = fTempPerm8;
			fRec13[0] = (fSlow24 + (0.999f * fRec13[1]));
			fTempPerm10 = (fSlow23 * ((float)input5[i] * fRec13[0]));
			fRec12[0] = max((fRec12[1] - fConst0), fabsf(fTempPerm10));
			fbargraph5 = (20 * log10f(max(0.00031622776601683794f, fRec12[0])));
			fTempPerm11 = fTempPerm10;
			fRec15[0] = (fSlow28 + (0.999f * fRec15[1]));
			fTempPerm12 = (fSlow27 * ((float)input6[i] * fRec15[0]));
			fRec14[0] = max((fRec14[1] - fConst0), fabsf(fTempPerm12));
			fbargraph6 = (20 * log10f(max(0.00031622776601683794f, fRec14[0])));
			fTempPerm13 = fTempPerm12;
			fRec17[0] = (fSlow32 + (0.999f * fRec17[1]));
			fTempPerm14 = (fSlow31 * ((float)input7[i] * fRec17[0]));
			fRec16[0] = max((fRec16[1] - fConst0), fabsf(fTempPerm14));
			fbargraph7 = (20 * log10f(max(0.00031622776601683794f, fRec16[0])));
			fTempPerm15 = fTempPerm14;
			fTempPerm16 = (fRec1[0] * ((((((((fSlow2 * fTempPerm1) + (fSlow6 * fTempPerm3)) + (fSlow10 * fTempPerm5)) + (fSlow14 * fTempPerm7)) + (fSlow18 * fTempPerm9)) + (fSlow22 * fTempPerm11)) + (fSlow26 * fTempPerm13)) + (fSlow30 * fTempPerm15)));
			fRec0[0] = max((fRec0[1] - fConst0), fabsf(fTempPerm16));
			fbargraph8 = (20 * log10f(max(0.00031622776601683794f, fRec0[0])));
			output0[i] = (FAUSTFLOAT)fTempPerm16;
			fTempPerm17 = (fRec1[0] * ((((((((fSlow33 * fTempPerm1) + (fSlow34 * fTempPerm3)) + (fSlow35 * fTempPerm5)) + (fSlow36 * fTempPerm7)) + (fSlow37 * fTempPerm9)) + (fSlow38 * fTempPerm11)) + (fSlow39 * fTempPerm13)) + (fSlow40 * fTempPerm15)));
			fRec18[0] = max((fRec18[1] - fConst0), fabsf(fTempPerm17));
			fbargraph9 = (20 * log10f(max(0.00031622776601683794f, fRec18[0])));
			output1[i] = (FAUSTFLOAT)fTempPerm17;
			// post processing
			fRec18[1] = fRec18[0];
			fRec0[1] = fRec0[0];
			fRec16[1] = fRec16[0];
			fRec17[1] = fRec17[0];
			fRec14[1] = fRec14[0];
			fRec15[1] = fRec15[0];
			fRec12[1] = fRec12[0];
			fRec13[1] = fRec13[0];
			fRec10[1] = fRec10[0];
			fRec11[1] = fRec11[0];
			fRec8[1] = fRec8[0];
			fRec9[1] = fRec9[0];
			fRec6[1] = fRec6[0];
			fRec7[1] = fRec7[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec1[1] = fRec1[0];
		}
	}
};


