/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2006"
license: "BSD"
name: "mixer"
version: "1.0"
Code generated with Faust 2.87.10 (https://faust.grame.fr)
Compilation options: -a /Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/archs/impulsearch.cpp -lang cpp -i -fpga-mem-th 4 -ct 1 -es 1 -mcd 4 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT double
#endif

#include "controlTools.h"

//----------------------------------------------------------------------------
//FAUST generated code
//----------------------------------------------------------------------------


#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>
#ifndef FAUST_INT_WRAP
#define FAUST_INT_WRAP
inline int faust_wrap_add(int a, int b) { return int((unsigned int)a + (unsigned int)b); }
inline int faust_wrap_sub(int a, int b) { return int((unsigned int)a - (unsigned int)b); }
inline int faust_wrap_mul(int a, int b) { return int((unsigned int)a * (unsigned int)b); }
#endif


#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif


class mydsp : public dsp {
	
 private:
	
	FAUSTFLOAT fVslider0;
	double fRec0_perm[4];
	FAUSTFLOAT fVslider1;
	double fRec1_perm[4];
	int fSampleRate;
	double fConst0;
	FAUSTFLOAT fCheckbox0;
	double fRec2_perm[4];
	FAUSTFLOAT fVslider2;
	double fRec3_perm[4];
	FAUSTFLOAT fCheckbox1;
	double fRec4_perm[4];
	FAUSTFLOAT fVslider3;
	double fRec5_perm[4];
	FAUSTFLOAT fCheckbox2;
	double fRec6_perm[4];
	FAUSTFLOAT fVslider4;
	double fRec7_perm[4];
	FAUSTFLOAT fCheckbox3;
	double fRec8_perm[4];
	FAUSTFLOAT fVslider5;
	double fRec9_perm[4];
	FAUSTFLOAT fCheckbox4;
	double fRec10_perm[4];
	FAUSTFLOAT fVslider6;
	double fRec11_perm[4];
	FAUSTFLOAT fCheckbox5;
	double fRec12_perm[4];
	FAUSTFLOAT fVslider7;
	double fRec13_perm[4];
	FAUSTFLOAT fCheckbox6;
	double fRec14_perm[4];
	FAUSTFLOAT fVslider8;
	double fRec15_perm[4];
	FAUSTFLOAT fCheckbox7;
	double fRec16_perm[4];
	FAUSTFLOAT fEntry0;
	FAUSTFLOAT fVbargraph0;
	FAUSTFLOAT fEntry1;
	FAUSTFLOAT fVbargraph1;
	FAUSTFLOAT fEntry2;
	FAUSTFLOAT fVbargraph2;
	FAUSTFLOAT fEntry3;
	FAUSTFLOAT fVbargraph3;
	FAUSTFLOAT fEntry4;
	FAUSTFLOAT fVbargraph4;
	FAUSTFLOAT fEntry5;
	FAUSTFLOAT fVbargraph5;
	FAUSTFLOAT fEntry6;
	FAUSTFLOAT fVbargraph6;
	FAUSTFLOAT fEntry7;
	FAUSTFLOAT fVbargraph7;
	double fRec17_perm[4];
	FAUSTFLOAT fVbargraph8;
	double fRec18_perm[4];
	FAUSTFLOAT fVbargraph9;
	
 public:
	mydsp() {
	}
	
	mydsp(const mydsp&) = default;
	
	virtual ~mydsp() = default;
	
	mydsp& operator=(const mydsp&) = default;
	
	void metadata(Meta* m) { 
		m->declare("author", "Grame");
		m->declare("compile_options", "-a /Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/archs/impulsearch.cpp -lang cpp -i -fpga-mem-th 4 -ct 1 -es 1 -mcd 4 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs");
		m->declare("copyright", "(c)GRAME 2006");
		m->declare("filename", "mixer.dsp");
		m->declare("license", "BSD");
		m->declare("math.lib/author", "GRAME");
		m->declare("math.lib/copyright", "GRAME");
		m->declare("math.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m->declare("math.lib/license", "LGPL with exception");
		m->declare("math.lib/name", "Math Library");
		m->declare("math.lib/version", "1.0");
		m->declare("music.lib/author", "GRAME");
		m->declare("music.lib/copyright", "GRAME");
		m->declare("music.lib/license", "LGPL with exception");
		m->declare("music.lib/name", "Music Library");
		m->declare("music.lib/version", "1.0");
		m->declare("name", "mixer");
		m->declare("panpot.dsp/author", "Grame");
		m->declare("panpot.dsp/copyright", "(c)GRAME 2006");
		m->declare("panpot.dsp/license", "BSD");
		m->declare("panpot.dsp/name", "panpot");
		m->declare("panpot.dsp/version", "1.0");
		m->declare("version", "1.0");
		m->declare("volume.dsp/author", "Grame");
		m->declare("volume.dsp/copyright", "(c)GRAME 2006");
		m->declare("volume.dsp/license", "BSD");
		m->declare("volume.dsp/name", "volume");
		m->declare("volume.dsp/version", "1.0");
		m->declare("vumeter.dsp/author", "Grame");
		m->declare("vumeter.dsp/copyright", "(c)GRAME 2006");
		m->declare("vumeter.dsp/license", "BSD");
		m->declare("vumeter.dsp/name", "vumeter");
		m->declare("vumeter.dsp/version", "1.0");
	}

	virtual int getNumInputs() {
		return 8;
	}
	virtual int getNumOutputs() {
		return 2;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = 1.0 / std::min<double>(1.92e+05, std::max<double>(1.0, static_cast<double>(fSampleRate)));
	}
	
	virtual void instanceResetUserInterface() {
		fVslider0 = static_cast<FAUSTFLOAT>(0.0);
		fVslider1 = static_cast<FAUSTFLOAT>(0.0);
		fCheckbox0 = static_cast<FAUSTFLOAT>(0.0);
		fVslider2 = static_cast<FAUSTFLOAT>(0.0);
		fCheckbox1 = static_cast<FAUSTFLOAT>(0.0);
		fVslider3 = static_cast<FAUSTFLOAT>(0.0);
		fCheckbox2 = static_cast<FAUSTFLOAT>(0.0);
		fVslider4 = static_cast<FAUSTFLOAT>(0.0);
		fCheckbox3 = static_cast<FAUSTFLOAT>(0.0);
		fVslider5 = static_cast<FAUSTFLOAT>(0.0);
		fCheckbox4 = static_cast<FAUSTFLOAT>(0.0);
		fVslider6 = static_cast<FAUSTFLOAT>(0.0);
		fCheckbox5 = static_cast<FAUSTFLOAT>(0.0);
		fVslider7 = static_cast<FAUSTFLOAT>(0.0);
		fCheckbox6 = static_cast<FAUSTFLOAT>(0.0);
		fVslider8 = static_cast<FAUSTFLOAT>(0.0);
		fCheckbox7 = static_cast<FAUSTFLOAT>(0.0);
		fEntry0 = static_cast<FAUSTFLOAT>(0.0);
		fEntry1 = static_cast<FAUSTFLOAT>(0.0);
		fEntry2 = static_cast<FAUSTFLOAT>(0.0);
		fEntry3 = static_cast<FAUSTFLOAT>(0.0);
		fEntry4 = static_cast<FAUSTFLOAT>(0.0);
		fEntry5 = static_cast<FAUSTFLOAT>(0.0);
		fEntry6 = static_cast<FAUSTFLOAT>(0.0);
		fEntry7 = static_cast<FAUSTFLOAT>(0.0);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 4; l0 = faust_wrap_add(l0, 1)) {
			fRec0_perm[l0] = 0.0;
		}
		for (int l1 = 0; l1 < 4; l1 = faust_wrap_add(l1, 1)) {
			fRec1_perm[l1] = 0.0;
		}
		for (int l2 = 0; l2 < 4; l2 = faust_wrap_add(l2, 1)) {
			fRec2_perm[l2] = 0.0;
		}
		for (int l3 = 0; l3 < 4; l3 = faust_wrap_add(l3, 1)) {
			fRec3_perm[l3] = 0.0;
		}
		for (int l4 = 0; l4 < 4; l4 = faust_wrap_add(l4, 1)) {
			fRec4_perm[l4] = 0.0;
		}
		for (int l5 = 0; l5 < 4; l5 = faust_wrap_add(l5, 1)) {
			fRec5_perm[l5] = 0.0;
		}
		for (int l6 = 0; l6 < 4; l6 = faust_wrap_add(l6, 1)) {
			fRec6_perm[l6] = 0.0;
		}
		for (int l7 = 0; l7 < 4; l7 = faust_wrap_add(l7, 1)) {
			fRec7_perm[l7] = 0.0;
		}
		for (int l8 = 0; l8 < 4; l8 = faust_wrap_add(l8, 1)) {
			fRec8_perm[l8] = 0.0;
		}
		for (int l9 = 0; l9 < 4; l9 = faust_wrap_add(l9, 1)) {
			fRec9_perm[l9] = 0.0;
		}
		for (int l10 = 0; l10 < 4; l10 = faust_wrap_add(l10, 1)) {
			fRec10_perm[l10] = 0.0;
		}
		for (int l11 = 0; l11 < 4; l11 = faust_wrap_add(l11, 1)) {
			fRec11_perm[l11] = 0.0;
		}
		for (int l12 = 0; l12 < 4; l12 = faust_wrap_add(l12, 1)) {
			fRec12_perm[l12] = 0.0;
		}
		for (int l13 = 0; l13 < 4; l13 = faust_wrap_add(l13, 1)) {
			fRec13_perm[l13] = 0.0;
		}
		for (int l14 = 0; l14 < 4; l14 = faust_wrap_add(l14, 1)) {
			fRec14_perm[l14] = 0.0;
		}
		for (int l15 = 0; l15 < 4; l15 = faust_wrap_add(l15, 1)) {
			fRec15_perm[l15] = 0.0;
		}
		for (int l16 = 0; l16 < 4; l16 = faust_wrap_add(l16, 1)) {
			fRec16_perm[l16] = 0.0;
		}
		for (int l17 = 0; l17 < 4; l17 = faust_wrap_add(l17, 1)) {
			fRec17_perm[l17] = 0.0;
		}
		for (int l18 = 0; l18 < 4; l18 = faust_wrap_add(l18, 1)) {
			fRec18_perm[l18] = 0.0;
		}
	}
	
	virtual void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	
	virtual void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual mydsp* clone() {
		return new mydsp(*this);
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openHorizontalBox("mixer");
		ui_interface->openVerticalBox("Ch 0");
		ui_interface->declare(&fEntry0, "1", "");
		ui_interface->declare(&fEntry0, "style", "knob");
		ui_interface->addNumEntry("pan", &fEntry0, FAUSTFLOAT(0.0), FAUSTFLOAT(-9e+01), FAUSTFLOAT(9e+01), FAUSTFLOAT(1.0));
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fVslider1, "1", "");
		ui_interface->addVerticalSlider("0x00", &fVslider1, FAUSTFLOAT(0.0), FAUSTFLOAT(-7e+01), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->declare(&fVbargraph0, "2", "");
		ui_interface->declare(&fVbargraph0, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph0", &fVbargraph0, FAUSTFLOAT(-7e+01), FAUSTFLOAT(5.0));
		ui_interface->closeBox();
		ui_interface->addCheckButton("mute", &fCheckbox0);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Ch 1");
		ui_interface->declare(&fEntry1, "1", "");
		ui_interface->declare(&fEntry1, "style", "knob");
		ui_interface->addNumEntry("pan", &fEntry1, FAUSTFLOAT(0.0), FAUSTFLOAT(-9e+01), FAUSTFLOAT(9e+01), FAUSTFLOAT(1.0));
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fVslider2, "1", "");
		ui_interface->addVerticalSlider("0x00", &fVslider2, FAUSTFLOAT(0.0), FAUSTFLOAT(-7e+01), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->declare(&fVbargraph1, "2", "");
		ui_interface->declare(&fVbargraph1, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph1", &fVbargraph1, FAUSTFLOAT(-7e+01), FAUSTFLOAT(5.0));
		ui_interface->closeBox();
		ui_interface->addCheckButton("mute", &fCheckbox1);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Ch 2");
		ui_interface->declare(&fEntry2, "1", "");
		ui_interface->declare(&fEntry2, "style", "knob");
		ui_interface->addNumEntry("pan", &fEntry2, FAUSTFLOAT(0.0), FAUSTFLOAT(-9e+01), FAUSTFLOAT(9e+01), FAUSTFLOAT(1.0));
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fVslider3, "1", "");
		ui_interface->addVerticalSlider("0x00", &fVslider3, FAUSTFLOAT(0.0), FAUSTFLOAT(-7e+01), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->declare(&fVbargraph2, "2", "");
		ui_interface->declare(&fVbargraph2, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph2", &fVbargraph2, FAUSTFLOAT(-7e+01), FAUSTFLOAT(5.0));
		ui_interface->closeBox();
		ui_interface->addCheckButton("mute", &fCheckbox2);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Ch 3");
		ui_interface->declare(&fEntry3, "1", "");
		ui_interface->declare(&fEntry3, "style", "knob");
		ui_interface->addNumEntry("pan", &fEntry3, FAUSTFLOAT(0.0), FAUSTFLOAT(-9e+01), FAUSTFLOAT(9e+01), FAUSTFLOAT(1.0));
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fVslider4, "1", "");
		ui_interface->addVerticalSlider("0x00", &fVslider4, FAUSTFLOAT(0.0), FAUSTFLOAT(-7e+01), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->declare(&fVbargraph3, "2", "");
		ui_interface->declare(&fVbargraph3, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph3", &fVbargraph3, FAUSTFLOAT(-7e+01), FAUSTFLOAT(5.0));
		ui_interface->closeBox();
		ui_interface->addCheckButton("mute", &fCheckbox3);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Ch 4");
		ui_interface->declare(&fEntry4, "1", "");
		ui_interface->declare(&fEntry4, "style", "knob");
		ui_interface->addNumEntry("pan", &fEntry4, FAUSTFLOAT(0.0), FAUSTFLOAT(-9e+01), FAUSTFLOAT(9e+01), FAUSTFLOAT(1.0));
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fVslider5, "1", "");
		ui_interface->addVerticalSlider("0x00", &fVslider5, FAUSTFLOAT(0.0), FAUSTFLOAT(-7e+01), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->declare(&fVbargraph4, "2", "");
		ui_interface->declare(&fVbargraph4, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph4", &fVbargraph4, FAUSTFLOAT(-7e+01), FAUSTFLOAT(5.0));
		ui_interface->closeBox();
		ui_interface->addCheckButton("mute", &fCheckbox4);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Ch 5");
		ui_interface->declare(&fEntry5, "1", "");
		ui_interface->declare(&fEntry5, "style", "knob");
		ui_interface->addNumEntry("pan", &fEntry5, FAUSTFLOAT(0.0), FAUSTFLOAT(-9e+01), FAUSTFLOAT(9e+01), FAUSTFLOAT(1.0));
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fVslider6, "1", "");
		ui_interface->addVerticalSlider("0x00", &fVslider6, FAUSTFLOAT(0.0), FAUSTFLOAT(-7e+01), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->declare(&fVbargraph5, "2", "");
		ui_interface->declare(&fVbargraph5, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph5", &fVbargraph5, FAUSTFLOAT(-7e+01), FAUSTFLOAT(5.0));
		ui_interface->closeBox();
		ui_interface->addCheckButton("mute", &fCheckbox5);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Ch 6");
		ui_interface->declare(&fEntry6, "1", "");
		ui_interface->declare(&fEntry6, "style", "knob");
		ui_interface->addNumEntry("pan", &fEntry6, FAUSTFLOAT(0.0), FAUSTFLOAT(-9e+01), FAUSTFLOAT(9e+01), FAUSTFLOAT(1.0));
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fVslider7, "1", "");
		ui_interface->addVerticalSlider("0x00", &fVslider7, FAUSTFLOAT(0.0), FAUSTFLOAT(-7e+01), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->declare(&fVbargraph6, "2", "");
		ui_interface->declare(&fVbargraph6, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph6", &fVbargraph6, FAUSTFLOAT(-7e+01), FAUSTFLOAT(5.0));
		ui_interface->closeBox();
		ui_interface->addCheckButton("mute", &fCheckbox6);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Ch 7");
		ui_interface->declare(&fEntry7, "1", "");
		ui_interface->declare(&fEntry7, "style", "knob");
		ui_interface->addNumEntry("pan", &fEntry7, FAUSTFLOAT(0.0), FAUSTFLOAT(-9e+01), FAUSTFLOAT(9e+01), FAUSTFLOAT(1.0));
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fVslider8, "1", "");
		ui_interface->addVerticalSlider("0x00", &fVslider8, FAUSTFLOAT(0.0), FAUSTFLOAT(-7e+01), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->declare(&fVbargraph7, "2", "");
		ui_interface->declare(&fVbargraph7, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph7", &fVbargraph7, FAUSTFLOAT(-7e+01), FAUSTFLOAT(5.0));
		ui_interface->closeBox();
		ui_interface->addCheckButton("mute", &fCheckbox7);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("stereo out");
		ui_interface->openVerticalBox("L");
		ui_interface->declare(&fVbargraph8, "2", "");
		ui_interface->declare(&fVbargraph8, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph8", &fVbargraph8, FAUSTFLOAT(-7e+01), FAUSTFLOAT(5.0));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("R");
		ui_interface->declare(&fVbargraph9, "2", "");
		ui_interface->declare(&fVbargraph9, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph9", &fVbargraph9, FAUSTFLOAT(-7e+01), FAUSTFLOAT(5.0));
		ui_interface->closeBox();
		ui_interface->declare(&fVslider0, "1", "");
		ui_interface->addVerticalSlider("0x00", &fVslider0, FAUSTFLOAT(0.0), FAUSTFLOAT(-7e+01), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0_ptr = inputs[0];
		FAUSTFLOAT* input1_ptr = inputs[1];
		FAUSTFLOAT* input2_ptr = inputs[2];
		FAUSTFLOAT* input3_ptr = inputs[3];
		FAUSTFLOAT* input4_ptr = inputs[4];
		FAUSTFLOAT* input5_ptr = inputs[5];
		FAUSTFLOAT* input6_ptr = inputs[6];
		FAUSTFLOAT* input7_ptr = inputs[7];
		FAUSTFLOAT* output0_ptr = outputs[0];
		FAUSTFLOAT* output1_ptr = outputs[1];
		double fSlow0 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * static_cast<double>(fVslider0));
		double fRec0_tmp[8];
		double* fRec0 = &fRec0_tmp[4];
		double fSlow1 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * static_cast<double>(fVslider1));
		double fRec1_tmp[8];
		double* fRec1 = &fRec1_tmp[4];
		double fSlow2 = 1.0 - static_cast<double>(fCheckbox0);
		double fZec0[4];
		double fRec2_tmp[8];
		double* fRec2 = &fRec2_tmp[4];
		double fSlow3 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * static_cast<double>(fVslider2));
		double fRec3_tmp[8];
		double* fRec3 = &fRec3_tmp[4];
		double fSlow4 = 1.0 - static_cast<double>(fCheckbox1);
		double fZec1[4];
		double fRec4_tmp[8];
		double* fRec4 = &fRec4_tmp[4];
		double fSlow5 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * static_cast<double>(fVslider3));
		double fRec5_tmp[8];
		double* fRec5 = &fRec5_tmp[4];
		double fSlow6 = 1.0 - static_cast<double>(fCheckbox2);
		double fZec2[4];
		double fRec6_tmp[8];
		double* fRec6 = &fRec6_tmp[4];
		double fSlow7 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * static_cast<double>(fVslider4));
		double fRec7_tmp[8];
		double* fRec7 = &fRec7_tmp[4];
		double fSlow8 = 1.0 - static_cast<double>(fCheckbox3);
		double fZec3[4];
		double fRec8_tmp[8];
		double* fRec8 = &fRec8_tmp[4];
		double fSlow9 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * static_cast<double>(fVslider5));
		double fRec9_tmp[8];
		double* fRec9 = &fRec9_tmp[4];
		double fSlow10 = 1.0 - static_cast<double>(fCheckbox4);
		double fZec4[4];
		double fRec10_tmp[8];
		double* fRec10 = &fRec10_tmp[4];
		double fSlow11 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * static_cast<double>(fVslider6));
		double fRec11_tmp[8];
		double* fRec11 = &fRec11_tmp[4];
		double fSlow12 = 1.0 - static_cast<double>(fCheckbox5);
		double fZec5[4];
		double fRec12_tmp[8];
		double* fRec12 = &fRec12_tmp[4];
		double fSlow13 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * static_cast<double>(fVslider7));
		double fRec13_tmp[8];
		double* fRec13 = &fRec13_tmp[4];
		double fSlow14 = 1.0 - static_cast<double>(fCheckbox6);
		double fZec6[4];
		double fRec14_tmp[8];
		double* fRec14 = &fRec14_tmp[4];
		double fSlow15 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * static_cast<double>(fVslider8));
		double fRec15_tmp[8];
		double* fRec15 = &fRec15_tmp[4];
		double fSlow16 = 1.0 - static_cast<double>(fCheckbox7);
		double fZec7[4];
		double fRec16_tmp[8];
		double* fRec16 = &fRec16_tmp[4];
		double fSlow17 = 0.005555555555555556 * (static_cast<double>(fEntry0) + -9e+01);
		double fSlow18 = std::sqrt(-fSlow17);
		double fZec8[4];
		double fSlow19 = 0.005555555555555556 * (static_cast<double>(fEntry1) + -9e+01);
		double fSlow20 = std::sqrt(-fSlow19);
		double fZec9[4];
		double fSlow21 = 0.005555555555555556 * (static_cast<double>(fEntry2) + -9e+01);
		double fSlow22 = std::sqrt(-fSlow21);
		double fZec10[4];
		double fSlow23 = 0.005555555555555556 * (static_cast<double>(fEntry3) + -9e+01);
		double fSlow24 = std::sqrt(-fSlow23);
		double fZec11[4];
		double fSlow25 = 0.005555555555555556 * (static_cast<double>(fEntry4) + -9e+01);
		double fSlow26 = std::sqrt(-fSlow25);
		double fZec12[4];
		double fSlow27 = 0.005555555555555556 * (static_cast<double>(fEntry5) + -9e+01);
		double fSlow28 = std::sqrt(-fSlow27);
		double fZec13[4];
		double fSlow29 = 0.005555555555555556 * (static_cast<double>(fEntry6) + -9e+01);
		double fSlow30 = std::sqrt(-fSlow29);
		double fZec14[4];
		double fSlow31 = 0.005555555555555556 * (static_cast<double>(fEntry7) + -9e+01);
		double fSlow32 = std::sqrt(-fSlow31);
		double fZec15[4];
		double fZec16[4];
		double fRec17_tmp[8];
		double* fRec17 = &fRec17_tmp[4];
		double fSlow33 = std::sqrt(fSlow17 + 1.0);
		double fSlow34 = std::sqrt(fSlow19 + 1.0);
		double fSlow35 = std::sqrt(fSlow21 + 1.0);
		double fSlow36 = std::sqrt(fSlow23 + 1.0);
		double fSlow37 = std::sqrt(fSlow25 + 1.0);
		double fSlow38 = std::sqrt(fSlow27 + 1.0);
		double fSlow39 = std::sqrt(fSlow29 + 1.0);
		double fSlow40 = std::sqrt(fSlow31 + 1.0);
		double fZec17[4];
		double fRec18_tmp[8];
		double* fRec18 = &fRec18_tmp[4];
		int vindex = 0;
		/* Main loop */
		for (vindex = 0; vindex <= (faust_wrap_sub(count, 4)); vindex = faust_wrap_add(vindex, 4)) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* input1 = &input1_ptr[vindex];
			FAUSTFLOAT* input2 = &input2_ptr[vindex];
			FAUSTFLOAT* input3 = &input3_ptr[vindex];
			FAUSTFLOAT* input4 = &input4_ptr[vindex];
			FAUSTFLOAT* input5 = &input5_ptr[vindex];
			FAUSTFLOAT* input6 = &input6_ptr[vindex];
			FAUSTFLOAT* input7 = &input7_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			FAUSTFLOAT* output1 = &output1_ptr[vindex];
			int vsize = 4;
			/* Recursive loop 0 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				fRec0_tmp[j0] = fRec0_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec0[i] = fSlow0 + 0.999 * fRec0[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				fRec0_perm[j1] = fRec0_tmp[faust_wrap_add(vsize, j1)];
			}
			/* Recursive loop 1 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fRec1_tmp[j2] = fRec1_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec1[i] = fSlow1 + 0.999 * fRec1[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fRec1_perm[j3] = fRec1_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Vectorizable loop 2 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec0[i] = fSlow2 * static_cast<double>(input0[i]) * fRec1[i];
			}
			/* Recursive loop 3 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				fRec2_tmp[j4] = fRec2_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec2[i] = std::max<double>(fRec2[faust_wrap_sub(i, 1)] - fConst0, std::fabs(fZec0[i]));
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fRec2_perm[j5] = fRec2_tmp[faust_wrap_add(vsize, j5)];
			}
			/* Recursive loop 4 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec3_tmp[j6] = fRec3_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec3[i] = fSlow3 + 0.999 * fRec3[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec3_perm[j7] = fRec3_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec1[i] = fSlow4 * static_cast<double>(input1[i]) * fRec3[i];
			}
			/* Recursive loop 6 */
			/* Pre code */
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fRec4_tmp[j8] = fRec4_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec4[i] = std::max<double>(fRec4[faust_wrap_sub(i, 1)] - fConst0, std::fabs(fZec1[i]));
			}
			/* Post code */
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fRec4_perm[j9] = fRec4_tmp[faust_wrap_add(vsize, j9)];
			}
			/* Recursive loop 7 */
			/* Pre code */
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				fRec5_tmp[j10] = fRec5_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec5[i] = fSlow5 + 0.999 * fRec5[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				fRec5_perm[j11] = fRec5_tmp[faust_wrap_add(vsize, j11)];
			}
			/* Vectorizable loop 8 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec2[i] = fSlow6 * static_cast<double>(input2[i]) * fRec5[i];
			}
			/* Recursive loop 9 */
			/* Pre code */
			for (int j12 = 0; j12 < 4; j12 = faust_wrap_add(j12, 1)) {
				fRec6_tmp[j12] = fRec6_perm[j12];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec6[i] = std::max<double>(fRec6[faust_wrap_sub(i, 1)] - fConst0, std::fabs(fZec2[i]));
			}
			/* Post code */
			for (int j13 = 0; j13 < 4; j13 = faust_wrap_add(j13, 1)) {
				fRec6_perm[j13] = fRec6_tmp[faust_wrap_add(vsize, j13)];
			}
			/* Recursive loop 10 */
			/* Pre code */
			for (int j14 = 0; j14 < 4; j14 = faust_wrap_add(j14, 1)) {
				fRec7_tmp[j14] = fRec7_perm[j14];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec7[i] = fSlow7 + 0.999 * fRec7[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j15 = 0; j15 < 4; j15 = faust_wrap_add(j15, 1)) {
				fRec7_perm[j15] = fRec7_tmp[faust_wrap_add(vsize, j15)];
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec3[i] = fSlow8 * static_cast<double>(input3[i]) * fRec7[i];
			}
			/* Recursive loop 12 */
			/* Pre code */
			for (int j16 = 0; j16 < 4; j16 = faust_wrap_add(j16, 1)) {
				fRec8_tmp[j16] = fRec8_perm[j16];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec8[i] = std::max<double>(fRec8[faust_wrap_sub(i, 1)] - fConst0, std::fabs(fZec3[i]));
			}
			/* Post code */
			for (int j17 = 0; j17 < 4; j17 = faust_wrap_add(j17, 1)) {
				fRec8_perm[j17] = fRec8_tmp[faust_wrap_add(vsize, j17)];
			}
			/* Recursive loop 13 */
			/* Pre code */
			for (int j18 = 0; j18 < 4; j18 = faust_wrap_add(j18, 1)) {
				fRec9_tmp[j18] = fRec9_perm[j18];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec9[i] = fSlow9 + 0.999 * fRec9[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j19 = 0; j19 < 4; j19 = faust_wrap_add(j19, 1)) {
				fRec9_perm[j19] = fRec9_tmp[faust_wrap_add(vsize, j19)];
			}
			/* Vectorizable loop 14 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec4[i] = fSlow10 * static_cast<double>(input4[i]) * fRec9[i];
			}
			/* Recursive loop 15 */
			/* Pre code */
			for (int j20 = 0; j20 < 4; j20 = faust_wrap_add(j20, 1)) {
				fRec10_tmp[j20] = fRec10_perm[j20];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec10[i] = std::max<double>(fRec10[faust_wrap_sub(i, 1)] - fConst0, std::fabs(fZec4[i]));
			}
			/* Post code */
			for (int j21 = 0; j21 < 4; j21 = faust_wrap_add(j21, 1)) {
				fRec10_perm[j21] = fRec10_tmp[faust_wrap_add(vsize, j21)];
			}
			/* Recursive loop 16 */
			/* Pre code */
			for (int j22 = 0; j22 < 4; j22 = faust_wrap_add(j22, 1)) {
				fRec11_tmp[j22] = fRec11_perm[j22];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec11[i] = fSlow11 + 0.999 * fRec11[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j23 = 0; j23 < 4; j23 = faust_wrap_add(j23, 1)) {
				fRec11_perm[j23] = fRec11_tmp[faust_wrap_add(vsize, j23)];
			}
			/* Vectorizable loop 17 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec5[i] = fSlow12 * static_cast<double>(input5[i]) * fRec11[i];
			}
			/* Recursive loop 18 */
			/* Pre code */
			for (int j24 = 0; j24 < 4; j24 = faust_wrap_add(j24, 1)) {
				fRec12_tmp[j24] = fRec12_perm[j24];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec12[i] = std::max<double>(fRec12[faust_wrap_sub(i, 1)] - fConst0, std::fabs(fZec5[i]));
			}
			/* Post code */
			for (int j25 = 0; j25 < 4; j25 = faust_wrap_add(j25, 1)) {
				fRec12_perm[j25] = fRec12_tmp[faust_wrap_add(vsize, j25)];
			}
			/* Recursive loop 19 */
			/* Pre code */
			for (int j26 = 0; j26 < 4; j26 = faust_wrap_add(j26, 1)) {
				fRec13_tmp[j26] = fRec13_perm[j26];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec13[i] = fSlow13 + 0.999 * fRec13[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j27 = 0; j27 < 4; j27 = faust_wrap_add(j27, 1)) {
				fRec13_perm[j27] = fRec13_tmp[faust_wrap_add(vsize, j27)];
			}
			/* Vectorizable loop 20 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec6[i] = fSlow14 * static_cast<double>(input6[i]) * fRec13[i];
			}
			/* Recursive loop 21 */
			/* Pre code */
			for (int j28 = 0; j28 < 4; j28 = faust_wrap_add(j28, 1)) {
				fRec14_tmp[j28] = fRec14_perm[j28];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec14[i] = std::max<double>(fRec14[faust_wrap_sub(i, 1)] - fConst0, std::fabs(fZec6[i]));
			}
			/* Post code */
			for (int j29 = 0; j29 < 4; j29 = faust_wrap_add(j29, 1)) {
				fRec14_perm[j29] = fRec14_tmp[faust_wrap_add(vsize, j29)];
			}
			/* Recursive loop 22 */
			/* Pre code */
			for (int j30 = 0; j30 < 4; j30 = faust_wrap_add(j30, 1)) {
				fRec15_tmp[j30] = fRec15_perm[j30];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec15[i] = fSlow15 + 0.999 * fRec15[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j31 = 0; j31 < 4; j31 = faust_wrap_add(j31, 1)) {
				fRec15_perm[j31] = fRec15_tmp[faust_wrap_add(vsize, j31)];
			}
			/* Vectorizable loop 23 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec7[i] = fSlow16 * static_cast<double>(input7[i]) * fRec15[i];
			}
			/* Recursive loop 24 */
			/* Pre code */
			for (int j32 = 0; j32 < 4; j32 = faust_wrap_add(j32, 1)) {
				fRec16_tmp[j32] = fRec16_perm[j32];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec16[i] = std::max<double>(fRec16[faust_wrap_sub(i, 1)] - fConst0, std::fabs(fZec7[i]));
			}
			/* Post code */
			for (int j33 = 0; j33 < 4; j33 = faust_wrap_add(j33, 1)) {
				fRec16_perm[j33] = fRec16_tmp[faust_wrap_add(vsize, j33)];
			}
			/* Vectorizable loop 25 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph0 = static_cast<FAUSTFLOAT>(2e+01 * std::log10(std::max<double>(0.00031622776601683794, fRec2[i])));
				fZec8[i] = fZec0[i];
			}
			/* Vectorizable loop 26 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph1 = static_cast<FAUSTFLOAT>(2e+01 * std::log10(std::max<double>(0.00031622776601683794, fRec4[i])));
				fZec9[i] = fZec1[i];
			}
			/* Vectorizable loop 27 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph2 = static_cast<FAUSTFLOAT>(2e+01 * std::log10(std::max<double>(0.00031622776601683794, fRec6[i])));
				fZec10[i] = fZec2[i];
			}
			/* Vectorizable loop 28 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph3 = static_cast<FAUSTFLOAT>(2e+01 * std::log10(std::max<double>(0.00031622776601683794, fRec8[i])));
				fZec11[i] = fZec3[i];
			}
			/* Vectorizable loop 29 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph4 = static_cast<FAUSTFLOAT>(2e+01 * std::log10(std::max<double>(0.00031622776601683794, fRec10[i])));
				fZec12[i] = fZec4[i];
			}
			/* Vectorizable loop 30 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph5 = static_cast<FAUSTFLOAT>(2e+01 * std::log10(std::max<double>(0.00031622776601683794, fRec12[i])));
				fZec13[i] = fZec5[i];
			}
			/* Vectorizable loop 31 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph6 = static_cast<FAUSTFLOAT>(2e+01 * std::log10(std::max<double>(0.00031622776601683794, fRec14[i])));
				fZec14[i] = fZec6[i];
			}
			/* Vectorizable loop 32 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph7 = static_cast<FAUSTFLOAT>(2e+01 * std::log10(std::max<double>(0.00031622776601683794, fRec16[i])));
				fZec15[i] = fZec7[i];
			}
			/* Vectorizable loop 33 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec16[i] = fRec0[i] * (fSlow18 * fZec8[i] + fSlow20 * fZec9[i] + fSlow22 * fZec10[i] + fSlow24 * fZec11[i] + fSlow26 * fZec12[i] + fSlow28 * fZec13[i] + fSlow30 * fZec14[i] + fSlow32 * fZec15[i]);
			}
			/* Recursive loop 34 */
			/* Pre code */
			for (int j34 = 0; j34 < 4; j34 = faust_wrap_add(j34, 1)) {
				fRec17_tmp[j34] = fRec17_perm[j34];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec17[i] = std::max<double>(fRec17[faust_wrap_sub(i, 1)] - fConst0, std::fabs(fZec16[i]));
			}
			/* Post code */
			for (int j35 = 0; j35 < 4; j35 = faust_wrap_add(j35, 1)) {
				fRec17_perm[j35] = fRec17_tmp[faust_wrap_add(vsize, j35)];
			}
			/* Vectorizable loop 35 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph8 = static_cast<FAUSTFLOAT>(2e+01 * std::log10(std::max<double>(0.00031622776601683794, fRec17[i])));
				output0[i] = static_cast<FAUSTFLOAT>(fZec16[i]);
			}
			/* Vectorizable loop 36 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec17[i] = fRec0[i] * (fSlow33 * fZec8[i] + fSlow34 * fZec9[i] + fSlow35 * fZec10[i] + fSlow36 * fZec11[i] + fSlow37 * fZec12[i] + fSlow38 * fZec13[i] + fSlow39 * fZec14[i] + fSlow40 * fZec15[i]);
			}
			/* Recursive loop 37 */
			/* Pre code */
			for (int j36 = 0; j36 < 4; j36 = faust_wrap_add(j36, 1)) {
				fRec18_tmp[j36] = fRec18_perm[j36];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec18[i] = std::max<double>(fRec18[faust_wrap_sub(i, 1)] - fConst0, std::fabs(fZec17[i]));
			}
			/* Post code */
			for (int j37 = 0; j37 < 4; j37 = faust_wrap_add(j37, 1)) {
				fRec18_perm[j37] = fRec18_tmp[faust_wrap_add(vsize, j37)];
			}
			/* Vectorizable loop 38 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph9 = static_cast<FAUSTFLOAT>(2e+01 * std::log10(std::max<double>(0.00031622776601683794, fRec18[i])));
				output1[i] = static_cast<FAUSTFLOAT>(fZec17[i]);
			}
		}
		/* Remaining frames */
		if (vindex < count) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* input1 = &input1_ptr[vindex];
			FAUSTFLOAT* input2 = &input2_ptr[vindex];
			FAUSTFLOAT* input3 = &input3_ptr[vindex];
			FAUSTFLOAT* input4 = &input4_ptr[vindex];
			FAUSTFLOAT* input5 = &input5_ptr[vindex];
			FAUSTFLOAT* input6 = &input6_ptr[vindex];
			FAUSTFLOAT* input7 = &input7_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			FAUSTFLOAT* output1 = &output1_ptr[vindex];
			int vsize = faust_wrap_sub(count, vindex);
			/* Recursive loop 0 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				fRec0_tmp[j0] = fRec0_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec0[i] = fSlow0 + 0.999 * fRec0[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				fRec0_perm[j1] = fRec0_tmp[faust_wrap_add(vsize, j1)];
			}
			/* Recursive loop 1 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fRec1_tmp[j2] = fRec1_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec1[i] = fSlow1 + 0.999 * fRec1[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fRec1_perm[j3] = fRec1_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Vectorizable loop 2 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec0[i] = fSlow2 * static_cast<double>(input0[i]) * fRec1[i];
			}
			/* Recursive loop 3 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				fRec2_tmp[j4] = fRec2_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec2[i] = std::max<double>(fRec2[faust_wrap_sub(i, 1)] - fConst0, std::fabs(fZec0[i]));
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fRec2_perm[j5] = fRec2_tmp[faust_wrap_add(vsize, j5)];
			}
			/* Recursive loop 4 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec3_tmp[j6] = fRec3_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec3[i] = fSlow3 + 0.999 * fRec3[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec3_perm[j7] = fRec3_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec1[i] = fSlow4 * static_cast<double>(input1[i]) * fRec3[i];
			}
			/* Recursive loop 6 */
			/* Pre code */
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fRec4_tmp[j8] = fRec4_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec4[i] = std::max<double>(fRec4[faust_wrap_sub(i, 1)] - fConst0, std::fabs(fZec1[i]));
			}
			/* Post code */
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fRec4_perm[j9] = fRec4_tmp[faust_wrap_add(vsize, j9)];
			}
			/* Recursive loop 7 */
			/* Pre code */
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				fRec5_tmp[j10] = fRec5_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec5[i] = fSlow5 + 0.999 * fRec5[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				fRec5_perm[j11] = fRec5_tmp[faust_wrap_add(vsize, j11)];
			}
			/* Vectorizable loop 8 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec2[i] = fSlow6 * static_cast<double>(input2[i]) * fRec5[i];
			}
			/* Recursive loop 9 */
			/* Pre code */
			for (int j12 = 0; j12 < 4; j12 = faust_wrap_add(j12, 1)) {
				fRec6_tmp[j12] = fRec6_perm[j12];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec6[i] = std::max<double>(fRec6[faust_wrap_sub(i, 1)] - fConst0, std::fabs(fZec2[i]));
			}
			/* Post code */
			for (int j13 = 0; j13 < 4; j13 = faust_wrap_add(j13, 1)) {
				fRec6_perm[j13] = fRec6_tmp[faust_wrap_add(vsize, j13)];
			}
			/* Recursive loop 10 */
			/* Pre code */
			for (int j14 = 0; j14 < 4; j14 = faust_wrap_add(j14, 1)) {
				fRec7_tmp[j14] = fRec7_perm[j14];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec7[i] = fSlow7 + 0.999 * fRec7[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j15 = 0; j15 < 4; j15 = faust_wrap_add(j15, 1)) {
				fRec7_perm[j15] = fRec7_tmp[faust_wrap_add(vsize, j15)];
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec3[i] = fSlow8 * static_cast<double>(input3[i]) * fRec7[i];
			}
			/* Recursive loop 12 */
			/* Pre code */
			for (int j16 = 0; j16 < 4; j16 = faust_wrap_add(j16, 1)) {
				fRec8_tmp[j16] = fRec8_perm[j16];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec8[i] = std::max<double>(fRec8[faust_wrap_sub(i, 1)] - fConst0, std::fabs(fZec3[i]));
			}
			/* Post code */
			for (int j17 = 0; j17 < 4; j17 = faust_wrap_add(j17, 1)) {
				fRec8_perm[j17] = fRec8_tmp[faust_wrap_add(vsize, j17)];
			}
			/* Recursive loop 13 */
			/* Pre code */
			for (int j18 = 0; j18 < 4; j18 = faust_wrap_add(j18, 1)) {
				fRec9_tmp[j18] = fRec9_perm[j18];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec9[i] = fSlow9 + 0.999 * fRec9[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j19 = 0; j19 < 4; j19 = faust_wrap_add(j19, 1)) {
				fRec9_perm[j19] = fRec9_tmp[faust_wrap_add(vsize, j19)];
			}
			/* Vectorizable loop 14 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec4[i] = fSlow10 * static_cast<double>(input4[i]) * fRec9[i];
			}
			/* Recursive loop 15 */
			/* Pre code */
			for (int j20 = 0; j20 < 4; j20 = faust_wrap_add(j20, 1)) {
				fRec10_tmp[j20] = fRec10_perm[j20];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec10[i] = std::max<double>(fRec10[faust_wrap_sub(i, 1)] - fConst0, std::fabs(fZec4[i]));
			}
			/* Post code */
			for (int j21 = 0; j21 < 4; j21 = faust_wrap_add(j21, 1)) {
				fRec10_perm[j21] = fRec10_tmp[faust_wrap_add(vsize, j21)];
			}
			/* Recursive loop 16 */
			/* Pre code */
			for (int j22 = 0; j22 < 4; j22 = faust_wrap_add(j22, 1)) {
				fRec11_tmp[j22] = fRec11_perm[j22];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec11[i] = fSlow11 + 0.999 * fRec11[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j23 = 0; j23 < 4; j23 = faust_wrap_add(j23, 1)) {
				fRec11_perm[j23] = fRec11_tmp[faust_wrap_add(vsize, j23)];
			}
			/* Vectorizable loop 17 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec5[i] = fSlow12 * static_cast<double>(input5[i]) * fRec11[i];
			}
			/* Recursive loop 18 */
			/* Pre code */
			for (int j24 = 0; j24 < 4; j24 = faust_wrap_add(j24, 1)) {
				fRec12_tmp[j24] = fRec12_perm[j24];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec12[i] = std::max<double>(fRec12[faust_wrap_sub(i, 1)] - fConst0, std::fabs(fZec5[i]));
			}
			/* Post code */
			for (int j25 = 0; j25 < 4; j25 = faust_wrap_add(j25, 1)) {
				fRec12_perm[j25] = fRec12_tmp[faust_wrap_add(vsize, j25)];
			}
			/* Recursive loop 19 */
			/* Pre code */
			for (int j26 = 0; j26 < 4; j26 = faust_wrap_add(j26, 1)) {
				fRec13_tmp[j26] = fRec13_perm[j26];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec13[i] = fSlow13 + 0.999 * fRec13[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j27 = 0; j27 < 4; j27 = faust_wrap_add(j27, 1)) {
				fRec13_perm[j27] = fRec13_tmp[faust_wrap_add(vsize, j27)];
			}
			/* Vectorizable loop 20 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec6[i] = fSlow14 * static_cast<double>(input6[i]) * fRec13[i];
			}
			/* Recursive loop 21 */
			/* Pre code */
			for (int j28 = 0; j28 < 4; j28 = faust_wrap_add(j28, 1)) {
				fRec14_tmp[j28] = fRec14_perm[j28];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec14[i] = std::max<double>(fRec14[faust_wrap_sub(i, 1)] - fConst0, std::fabs(fZec6[i]));
			}
			/* Post code */
			for (int j29 = 0; j29 < 4; j29 = faust_wrap_add(j29, 1)) {
				fRec14_perm[j29] = fRec14_tmp[faust_wrap_add(vsize, j29)];
			}
			/* Recursive loop 22 */
			/* Pre code */
			for (int j30 = 0; j30 < 4; j30 = faust_wrap_add(j30, 1)) {
				fRec15_tmp[j30] = fRec15_perm[j30];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec15[i] = fSlow15 + 0.999 * fRec15[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j31 = 0; j31 < 4; j31 = faust_wrap_add(j31, 1)) {
				fRec15_perm[j31] = fRec15_tmp[faust_wrap_add(vsize, j31)];
			}
			/* Vectorizable loop 23 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec7[i] = fSlow16 * static_cast<double>(input7[i]) * fRec15[i];
			}
			/* Recursive loop 24 */
			/* Pre code */
			for (int j32 = 0; j32 < 4; j32 = faust_wrap_add(j32, 1)) {
				fRec16_tmp[j32] = fRec16_perm[j32];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec16[i] = std::max<double>(fRec16[faust_wrap_sub(i, 1)] - fConst0, std::fabs(fZec7[i]));
			}
			/* Post code */
			for (int j33 = 0; j33 < 4; j33 = faust_wrap_add(j33, 1)) {
				fRec16_perm[j33] = fRec16_tmp[faust_wrap_add(vsize, j33)];
			}
			/* Vectorizable loop 25 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph0 = static_cast<FAUSTFLOAT>(2e+01 * std::log10(std::max<double>(0.00031622776601683794, fRec2[i])));
				fZec8[i] = fZec0[i];
			}
			/* Vectorizable loop 26 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph1 = static_cast<FAUSTFLOAT>(2e+01 * std::log10(std::max<double>(0.00031622776601683794, fRec4[i])));
				fZec9[i] = fZec1[i];
			}
			/* Vectorizable loop 27 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph2 = static_cast<FAUSTFLOAT>(2e+01 * std::log10(std::max<double>(0.00031622776601683794, fRec6[i])));
				fZec10[i] = fZec2[i];
			}
			/* Vectorizable loop 28 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph3 = static_cast<FAUSTFLOAT>(2e+01 * std::log10(std::max<double>(0.00031622776601683794, fRec8[i])));
				fZec11[i] = fZec3[i];
			}
			/* Vectorizable loop 29 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph4 = static_cast<FAUSTFLOAT>(2e+01 * std::log10(std::max<double>(0.00031622776601683794, fRec10[i])));
				fZec12[i] = fZec4[i];
			}
			/* Vectorizable loop 30 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph5 = static_cast<FAUSTFLOAT>(2e+01 * std::log10(std::max<double>(0.00031622776601683794, fRec12[i])));
				fZec13[i] = fZec5[i];
			}
			/* Vectorizable loop 31 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph6 = static_cast<FAUSTFLOAT>(2e+01 * std::log10(std::max<double>(0.00031622776601683794, fRec14[i])));
				fZec14[i] = fZec6[i];
			}
			/* Vectorizable loop 32 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph7 = static_cast<FAUSTFLOAT>(2e+01 * std::log10(std::max<double>(0.00031622776601683794, fRec16[i])));
				fZec15[i] = fZec7[i];
			}
			/* Vectorizable loop 33 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec16[i] = fRec0[i] * (fSlow18 * fZec8[i] + fSlow20 * fZec9[i] + fSlow22 * fZec10[i] + fSlow24 * fZec11[i] + fSlow26 * fZec12[i] + fSlow28 * fZec13[i] + fSlow30 * fZec14[i] + fSlow32 * fZec15[i]);
			}
			/* Recursive loop 34 */
			/* Pre code */
			for (int j34 = 0; j34 < 4; j34 = faust_wrap_add(j34, 1)) {
				fRec17_tmp[j34] = fRec17_perm[j34];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec17[i] = std::max<double>(fRec17[faust_wrap_sub(i, 1)] - fConst0, std::fabs(fZec16[i]));
			}
			/* Post code */
			for (int j35 = 0; j35 < 4; j35 = faust_wrap_add(j35, 1)) {
				fRec17_perm[j35] = fRec17_tmp[faust_wrap_add(vsize, j35)];
			}
			/* Vectorizable loop 35 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph8 = static_cast<FAUSTFLOAT>(2e+01 * std::log10(std::max<double>(0.00031622776601683794, fRec17[i])));
				output0[i] = static_cast<FAUSTFLOAT>(fZec16[i]);
			}
			/* Vectorizable loop 36 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec17[i] = fRec0[i] * (fSlow33 * fZec8[i] + fSlow34 * fZec9[i] + fSlow35 * fZec10[i] + fSlow36 * fZec11[i] + fSlow37 * fZec12[i] + fSlow38 * fZec13[i] + fSlow39 * fZec14[i] + fSlow40 * fZec15[i]);
			}
			/* Recursive loop 37 */
			/* Pre code */
			for (int j36 = 0; j36 < 4; j36 = faust_wrap_add(j36, 1)) {
				fRec18_tmp[j36] = fRec18_perm[j36];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec18[i] = std::max<double>(fRec18[faust_wrap_sub(i, 1)] - fConst0, std::fabs(fZec17[i]));
			}
			/* Post code */
			for (int j37 = 0; j37 < 4; j37 = faust_wrap_add(j37, 1)) {
				fRec18_perm[j37] = fRec18_tmp[faust_wrap_add(vsize, j37)];
			}
			/* Vectorizable loop 38 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph9 = static_cast<FAUSTFLOAT>(2e+01 * std::log10(std::max<double>(0.00031622776601683794, fRec18[i])));
				output1[i] = static_cast<FAUSTFLOAT>(fZec17[i]);
			}
		}
	}

};

int main(int argc, char* argv[])
{
    int linenum = 0;
    int nbsamples = 60000;
    
    // print general informations
    printHeader(new mydsp(), nbsamples);
    
    // linenum is incremented in runDSP and runPolyDSP
    runDSP(new mydsp(), argv[0], linenum, nbsamples/4);
    runDSP(new mydsp(), argv[0], linenum, nbsamples/4, false, true);
    runPolyDSP(new mydsp(), linenum, nbsamples/4, 4);
    runPolyDSP(new mydsp(), linenum, nbsamples/4, 1);
    
    return 0;
}

#endif
