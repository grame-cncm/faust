/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2006"
license: "BSD"
name: "mixer"
version: "1.0"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: cpp, -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__


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

#include <cmath>
#include <math.h>


#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif
#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class mydsp : public dsp {
	
 private:
	
	int fSamplingFreq;
	float fConst0;
	FAUSTFLOAT fVslider0;
	float fRec1[2];
	FAUSTFLOAT fEntry0;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fVslider1;
	float fRec3[2];
	float fRec2[2];
	FAUSTFLOAT fVbargraph0;
	FAUSTFLOAT fEntry1;
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT fVslider2;
	float fRec5[2];
	float fRec4[2];
	FAUSTFLOAT fVbargraph1;
	FAUSTFLOAT fEntry2;
	FAUSTFLOAT fCheckbox2;
	FAUSTFLOAT fVslider3;
	float fRec7[2];
	float fRec6[2];
	FAUSTFLOAT fVbargraph2;
	FAUSTFLOAT fEntry3;
	FAUSTFLOAT fCheckbox3;
	FAUSTFLOAT fVslider4;
	float fRec9[2];
	float fRec8[2];
	FAUSTFLOAT fVbargraph3;
	FAUSTFLOAT fEntry4;
	FAUSTFLOAT fCheckbox4;
	FAUSTFLOAT fVslider5;
	float fRec11[2];
	float fRec10[2];
	FAUSTFLOAT fVbargraph4;
	FAUSTFLOAT fEntry5;
	FAUSTFLOAT fCheckbox5;
	FAUSTFLOAT fVslider6;
	float fRec13[2];
	float fRec12[2];
	FAUSTFLOAT fVbargraph5;
	FAUSTFLOAT fEntry6;
	FAUSTFLOAT fCheckbox6;
	FAUSTFLOAT fVslider7;
	float fRec15[2];
	float fRec14[2];
	FAUSTFLOAT fVbargraph6;
	FAUSTFLOAT fEntry7;
	FAUSTFLOAT fCheckbox7;
	FAUSTFLOAT fVslider8;
	float fRec17[2];
	float fRec16[2];
	FAUSTFLOAT fVbargraph7;
	float fRec0[2];
	FAUSTFLOAT fVbargraph8;
	float fRec18[2];
	FAUSTFLOAT fVbargraph9;
	
 public:
	
	void metadata(Meta* m) { 
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

	virtual int getNumInputs() {
		return 8;
		
	}
	virtual int getNumOutputs() {
		return 2;
		
	}
	virtual int getInputRate(int channel) {
		int rate;
		switch (channel) {
			case 0: {
				rate = 1;
				break;
			}
			case 1: {
				rate = 1;
				break;
			}
			case 2: {
				rate = 1;
				break;
			}
			case 3: {
				rate = 1;
				break;
			}
			case 4: {
				rate = 1;
				break;
			}
			case 5: {
				rate = 1;
				break;
			}
			case 6: {
				rate = 1;
				break;
			}
			case 7: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	virtual int getOutputRate(int channel) {
		int rate;
		switch (channel) {
			case 0: {
				rate = 1;
				break;
			}
			case 1: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	
	static void classInit(int samplingFreq) {
		
	}
	
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = (1.0f / min(192000.0f, max(1.0f, float(fSamplingFreq))));
		
	}
	
	virtual void instanceResetUserInterface() {
		fVslider0 = FAUSTFLOAT(0.0f);
		fEntry0 = FAUSTFLOAT(0.0f);
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fVslider1 = FAUSTFLOAT(0.0f);
		fEntry1 = FAUSTFLOAT(0.0f);
		fCheckbox1 = FAUSTFLOAT(0.0f);
		fVslider2 = FAUSTFLOAT(0.0f);
		fEntry2 = FAUSTFLOAT(0.0f);
		fCheckbox2 = FAUSTFLOAT(0.0f);
		fVslider3 = FAUSTFLOAT(0.0f);
		fEntry3 = FAUSTFLOAT(0.0f);
		fCheckbox3 = FAUSTFLOAT(0.0f);
		fVslider4 = FAUSTFLOAT(0.0f);
		fEntry4 = FAUSTFLOAT(0.0f);
		fCheckbox4 = FAUSTFLOAT(0.0f);
		fVslider5 = FAUSTFLOAT(0.0f);
		fEntry5 = FAUSTFLOAT(0.0f);
		fCheckbox5 = FAUSTFLOAT(0.0f);
		fVslider6 = FAUSTFLOAT(0.0f);
		fEntry6 = FAUSTFLOAT(0.0f);
		fCheckbox6 = FAUSTFLOAT(0.0f);
		fVslider7 = FAUSTFLOAT(0.0f);
		fEntry7 = FAUSTFLOAT(0.0f);
		fCheckbox7 = FAUSTFLOAT(0.0f);
		fVslider8 = FAUSTFLOAT(0.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec1[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec3[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec2[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec5[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec4[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec7[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec6[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec9[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec8[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec11[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec10[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec13[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec12[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec15[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec14[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec17[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec16[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec0[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec18[l18] = 0.0f;
			
		}
		
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
		ui_interface->declare(&fEntry0, "1", "");
		ui_interface->declare(&fEntry0, "style", "knob");
		ui_interface->addNumEntry("pan", &fEntry0, 0.0f, -90.0f, 90.0f, 1.0f);
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fVslider1, "1", "");
		ui_interface->addVerticalSlider("0x00", &fVslider1, 0.0f, -70.0f, 4.0f, 0.100000001f);
		ui_interface->declare(&fVbargraph0, "2", "");
		ui_interface->declare(&fVbargraph0, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fc0a0439bf0", &fVbargraph0, -70.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->addCheckButton("mute", &fCheckbox0);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Ch 1");
		ui_interface->declare(&fEntry1, "1", "");
		ui_interface->declare(&fEntry1, "style", "knob");
		ui_interface->addNumEntry("pan", &fEntry1, 0.0f, -90.0f, 90.0f, 1.0f);
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fVslider2, "1", "");
		ui_interface->addVerticalSlider("0x00", &fVslider2, 0.0f, -70.0f, 4.0f, 0.100000001f);
		ui_interface->declare(&fVbargraph1, "2", "");
		ui_interface->declare(&fVbargraph1, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fc0a0443cf0", &fVbargraph1, -70.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->addCheckButton("mute", &fCheckbox1);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Ch 2");
		ui_interface->declare(&fEntry2, "1", "");
		ui_interface->declare(&fEntry2, "style", "knob");
		ui_interface->addNumEntry("pan", &fEntry2, 0.0f, -90.0f, 90.0f, 1.0f);
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fVslider3, "1", "");
		ui_interface->addVerticalSlider("0x00", &fVslider3, 0.0f, -70.0f, 4.0f, 0.100000001f);
		ui_interface->declare(&fVbargraph2, "2", "");
		ui_interface->declare(&fVbargraph2, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fc0a044e230", &fVbargraph2, -70.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->addCheckButton("mute", &fCheckbox2);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Ch 3");
		ui_interface->declare(&fEntry3, "1", "");
		ui_interface->declare(&fEntry3, "style", "knob");
		ui_interface->addNumEntry("pan", &fEntry3, 0.0f, -90.0f, 90.0f, 1.0f);
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fVslider4, "1", "");
		ui_interface->addVerticalSlider("0x00", &fVslider4, 0.0f, -70.0f, 4.0f, 0.100000001f);
		ui_interface->declare(&fVbargraph3, "2", "");
		ui_interface->declare(&fVbargraph3, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fc0a0458a30", &fVbargraph3, -70.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->addCheckButton("mute", &fCheckbox3);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Ch 4");
		ui_interface->declare(&fEntry4, "1", "");
		ui_interface->declare(&fEntry4, "style", "knob");
		ui_interface->addNumEntry("pan", &fEntry4, 0.0f, -90.0f, 90.0f, 1.0f);
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fVslider5, "1", "");
		ui_interface->addVerticalSlider("0x00", &fVslider5, 0.0f, -70.0f, 4.0f, 0.100000001f);
		ui_interface->declare(&fVbargraph4, "2", "");
		ui_interface->declare(&fVbargraph4, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fc0a04634f0", &fVbargraph4, -70.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->addCheckButton("mute", &fCheckbox4);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Ch 5");
		ui_interface->declare(&fEntry5, "1", "");
		ui_interface->declare(&fEntry5, "style", "knob");
		ui_interface->addNumEntry("pan", &fEntry5, 0.0f, -90.0f, 90.0f, 1.0f);
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fVslider6, "1", "");
		ui_interface->addVerticalSlider("0x00", &fVslider6, 0.0f, -70.0f, 4.0f, 0.100000001f);
		ui_interface->declare(&fVbargraph5, "2", "");
		ui_interface->declare(&fVbargraph5, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fc0a046e270", &fVbargraph5, -70.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->addCheckButton("mute", &fCheckbox5);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Ch 6");
		ui_interface->declare(&fEntry6, "1", "");
		ui_interface->declare(&fEntry6, "style", "knob");
		ui_interface->addNumEntry("pan", &fEntry6, 0.0f, -90.0f, 90.0f, 1.0f);
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fVslider7, "1", "");
		ui_interface->addVerticalSlider("0x00", &fVslider7, 0.0f, -70.0f, 4.0f, 0.100000001f);
		ui_interface->declare(&fVbargraph6, "2", "");
		ui_interface->declare(&fVbargraph6, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fc0a04792b0", &fVbargraph6, -70.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->addCheckButton("mute", &fCheckbox6);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Ch 7");
		ui_interface->declare(&fEntry7, "1", "");
		ui_interface->declare(&fEntry7, "style", "knob");
		ui_interface->addNumEntry("pan", &fEntry7, 0.0f, -90.0f, 90.0f, 1.0f);
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fVslider8, "1", "");
		ui_interface->addVerticalSlider("0x00", &fVslider8, 0.0f, -70.0f, 4.0f, 0.100000001f);
		ui_interface->declare(&fVbargraph7, "2", "");
		ui_interface->declare(&fVbargraph7, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fc0a04845b0", &fVbargraph7, -70.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->addCheckButton("mute", &fCheckbox7);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("stereo out");
		ui_interface->openVerticalBox("L");
		ui_interface->declare(&fVbargraph8, "2", "");
		ui_interface->declare(&fVbargraph8, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fc0a04884a0", &fVbargraph8, -70.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("R");
		ui_interface->declare(&fVbargraph9, "2", "");
		ui_interface->declare(&fVbargraph9, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fc0a0491a40", &fVbargraph9, -70.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->declare(&fVslider0, "1", "");
		ui_interface->addVerticalSlider("0x00", &fVslider0, 0.0f, -70.0f, 4.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* input2 = inputs[2];
		FAUSTFLOAT* input3 = inputs[3];
		FAUSTFLOAT* input4 = inputs[4];
		FAUSTFLOAT* input5 = inputs[5];
		FAUSTFLOAT* input6 = inputs[6];
		FAUSTFLOAT* input7 = inputs[7];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = (0.00100000005f * powf(10.0f, (0.0500000007f * float(fVslider0))));
		float fSlow1 = (0.00555555569f * (float(fEntry0) + -90.0f));
		float fSlow2 = sqrtf((0.0f - fSlow1));
		float fSlow3 = (1.0f - float(fCheckbox0));
		float fSlow4 = (0.00100000005f * powf(10.0f, (0.0500000007f * float(fVslider1))));
		float fSlow5 = (0.00555555569f * (float(fEntry1) + -90.0f));
		float fSlow6 = sqrtf((0.0f - fSlow5));
		float fSlow7 = (1.0f - float(fCheckbox1));
		float fSlow8 = (0.00100000005f * powf(10.0f, (0.0500000007f * float(fVslider2))));
		float fSlow9 = (0.00555555569f * (float(fEntry2) + -90.0f));
		float fSlow10 = sqrtf((0.0f - fSlow9));
		float fSlow11 = (1.0f - float(fCheckbox2));
		float fSlow12 = (0.00100000005f * powf(10.0f, (0.0500000007f * float(fVslider3))));
		float fSlow13 = (0.00555555569f * (float(fEntry3) + -90.0f));
		float fSlow14 = sqrtf((0.0f - fSlow13));
		float fSlow15 = (1.0f - float(fCheckbox3));
		float fSlow16 = (0.00100000005f * powf(10.0f, (0.0500000007f * float(fVslider4))));
		float fSlow17 = (0.00555555569f * (float(fEntry4) + -90.0f));
		float fSlow18 = sqrtf((0.0f - fSlow17));
		float fSlow19 = (1.0f - float(fCheckbox4));
		float fSlow20 = (0.00100000005f * powf(10.0f, (0.0500000007f * float(fVslider5))));
		float fSlow21 = (0.00555555569f * (float(fEntry5) + -90.0f));
		float fSlow22 = sqrtf((0.0f - fSlow21));
		float fSlow23 = (1.0f - float(fCheckbox5));
		float fSlow24 = (0.00100000005f * powf(10.0f, (0.0500000007f * float(fVslider6))));
		float fSlow25 = (0.00555555569f * (float(fEntry6) + -90.0f));
		float fSlow26 = sqrtf((0.0f - fSlow25));
		float fSlow27 = (1.0f - float(fCheckbox6));
		float fSlow28 = (0.00100000005f * powf(10.0f, (0.0500000007f * float(fVslider7))));
		float fSlow29 = (0.00555555569f * (float(fEntry7) + -90.0f));
		float fSlow30 = sqrtf((0.0f - fSlow29));
		float fSlow31 = (1.0f - float(fCheckbox7));
		float fSlow32 = (0.00100000005f * powf(10.0f, (0.0500000007f * float(fVslider8))));
		float fSlow33 = sqrtf((fSlow1 + 1.0f));
		float fSlow34 = sqrtf((fSlow5 + 1.0f));
		float fSlow35 = sqrtf((fSlow9 + 1.0f));
		float fSlow36 = sqrtf((fSlow13 + 1.0f));
		float fSlow37 = sqrtf((fSlow17 + 1.0f));
		float fSlow38 = sqrtf((fSlow21 + 1.0f));
		float fSlow39 = sqrtf((fSlow25 + 1.0f));
		float fSlow40 = sqrtf((fSlow29 + 1.0f));
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec1[0] = (fSlow0 + (0.999000013f * fRec1[1]));
			fRec3[0] = (fSlow4 + (0.999000013f * fRec3[1]));
			float fTemp0 = (fSlow3 * (float(input0[i]) * fRec3[0]));
			fRec2[0] = max((fRec2[1] - fConst0), fabsf(fTemp0));
			fVbargraph0 = FAUSTFLOAT((20.0f * log10f(max(0.000316227757f, fRec2[0]))));
			fRec5[0] = (fSlow8 + (0.999000013f * fRec5[1]));
			float fTemp1 = (fSlow7 * (float(input1[i]) * fRec5[0]));
			fRec4[0] = max((fRec4[1] - fConst0), fabsf(fTemp1));
			fVbargraph1 = FAUSTFLOAT((20.0f * log10f(max(0.000316227757f, fRec4[0]))));
			fRec7[0] = (fSlow12 + (0.999000013f * fRec7[1]));
			float fTemp2 = (fSlow11 * (float(input2[i]) * fRec7[0]));
			fRec6[0] = max((fRec6[1] - fConst0), fabsf(fTemp2));
			fVbargraph2 = FAUSTFLOAT((20.0f * log10f(max(0.000316227757f, fRec6[0]))));
			fRec9[0] = (fSlow16 + (0.999000013f * fRec9[1]));
			float fTemp3 = (fSlow15 * (float(input3[i]) * fRec9[0]));
			fRec8[0] = max((fRec8[1] - fConst0), fabsf(fTemp3));
			fVbargraph3 = FAUSTFLOAT((20.0f * log10f(max(0.000316227757f, fRec8[0]))));
			fRec11[0] = (fSlow20 + (0.999000013f * fRec11[1]));
			float fTemp4 = (fSlow19 * (float(input4[i]) * fRec11[0]));
			fRec10[0] = max((fRec10[1] - fConst0), fabsf(fTemp4));
			fVbargraph4 = FAUSTFLOAT((20.0f * log10f(max(0.000316227757f, fRec10[0]))));
			fRec13[0] = (fSlow24 + (0.999000013f * fRec13[1]));
			float fTemp5 = (fSlow23 * (float(input5[i]) * fRec13[0]));
			fRec12[0] = max((fRec12[1] - fConst0), fabsf(fTemp5));
			fVbargraph5 = FAUSTFLOAT((20.0f * log10f(max(0.000316227757f, fRec12[0]))));
			fRec15[0] = (fSlow28 + (0.999000013f * fRec15[1]));
			float fTemp6 = (fSlow27 * (float(input6[i]) * fRec15[0]));
			fRec14[0] = max((fRec14[1] - fConst0), fabsf(fTemp6));
			fVbargraph6 = FAUSTFLOAT((20.0f * log10f(max(0.000316227757f, fRec14[0]))));
			fRec17[0] = (fSlow32 + (0.999000013f * fRec17[1]));
			float fTemp7 = (fSlow31 * (float(input7[i]) * fRec17[0]));
			fRec16[0] = max((fRec16[1] - fConst0), fabsf(fTemp7));
			fVbargraph7 = FAUSTFLOAT((20.0f * log10f(max(0.000316227757f, fRec16[0]))));
			float fTemp8 = (fRec1[0] * ((((((((fSlow2 * fTemp0) + (fSlow6 * fTemp1)) + (fSlow10 * fTemp2)) + (fSlow14 * fTemp3)) + (fSlow18 * fTemp4)) + (fSlow22 * fTemp5)) + (fSlow26 * fTemp6)) + (fSlow30 * fTemp7)));
			fRec0[0] = max((fRec0[1] - fConst0), fabsf(fTemp8));
			fVbargraph8 = FAUSTFLOAT((20.0f * log10f(max(0.000316227757f, fRec0[0]))));
			output0[i] = FAUSTFLOAT(fTemp8);
			float fTemp9 = (fRec1[0] * ((((((((fSlow33 * fTemp0) + (fSlow34 * fTemp1)) + (fSlow35 * fTemp2)) + (fSlow36 * fTemp3)) + (fSlow37 * fTemp4)) + (fSlow38 * fTemp5)) + (fSlow39 * fTemp6)) + (fSlow40 * fTemp7)));
			fRec18[0] = max((fRec18[1] - fConst0), fabsf(fTemp9));
			fVbargraph9 = FAUSTFLOAT((20.0f * log10f(max(0.000316227757f, fRec18[0]))));
			output1[i] = FAUSTFLOAT(fTemp9);
			fRec1[1] = fRec1[0];
			fRec3[1] = fRec3[0];
			fRec2[1] = fRec2[0];
			fRec5[1] = fRec5[0];
			fRec4[1] = fRec4[0];
			fRec7[1] = fRec7[0];
			fRec6[1] = fRec6[0];
			fRec9[1] = fRec9[0];
			fRec8[1] = fRec8[0];
			fRec11[1] = fRec11[0];
			fRec10[1] = fRec10[0];
			fRec13[1] = fRec13[0];
			fRec12[1] = fRec12[0];
			fRec15[1] = fRec15[0];
			fRec14[1] = fRec14[0];
			fRec17[1] = fRec17[0];
			fRec16[1] = fRec16[0];
			fRec0[1] = fRec0[0];
			fRec18[1] = fRec18[0];
			
		}
		
	}

	
};

#endif
