/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2006"
license: "BSD"
name: "multibandfilter"
version: "1.0"
Code generated with Faust 2.85.5 (https://faust.grame.fr)
Compilation options: -a /Users/manuelfarzini/personal/dev/repo/faust/architecture/_bench/arch/cpp/bench.cpp -lang cpp -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

// architecture/bench/arch/cpp/bench.cpp

#include "faust/dsp/dsp.h"
#include "faust/gui/UI.h"
#include "faust/gui/meta.h"

#include "bench.h"

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

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

static double mydsp_faustpower2_f(double value) {
	return value * value;
}

class mydsp : public dsp {
	
 private:
	
	int fSampleRate;
	double fConst0;
	FAUSTFLOAT fEntry0;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT fEntry1;
	FAUSTFLOAT fEntry2;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fEntry3;
	FAUSTFLOAT fEntry4;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT fEntry5;
	FAUSTFLOAT fEntry6;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT fEntry7;
	FAUSTFLOAT fEntry8;
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT fEntry9;
	FAUSTFLOAT fEntry10;
	FAUSTFLOAT fVslider5;
	FAUSTFLOAT fEntry11;
	FAUSTFLOAT fEntry12;
	FAUSTFLOAT fVslider6;
	FAUSTFLOAT fEntry13;
	FAUSTFLOAT fEntry14;
	FAUSTFLOAT fVslider7;
	FAUSTFLOAT fEntry15;
	FAUSTFLOAT fEntry16;
	FAUSTFLOAT fVslider8;
	FAUSTFLOAT fEntry17;
	FAUSTFLOAT fEntry18;
	FAUSTFLOAT fVslider9;
	FAUSTFLOAT fEntry19;
	double fRec9[3];
	double fRec8[3];
	double fRec7[3];
	double fRec6[3];
	double fRec5[3];
	double fRec4[3];
	double fRec3[3];
	double fRec2[3];
	double fRec1[3];
	double fRec0[3];
	
 public:
	mydsp() {
	}
	
	mydsp(const mydsp&) = default;
	
	virtual ~mydsp() = default;
	
	mydsp& operator=(const mydsp&) = default;
	
	void metadata(Meta* m) { 
		m->declare("author", "Grame");
		m->declare("bandfilter.dsp/author", "Grame");
		m->declare("bandfilter.dsp/copyright", "(c)GRAME 2006");
		m->declare("bandfilter.dsp/license", "BSD");
		m->declare("bandfilter.dsp/name", "bandfilter");
		m->declare("bandfilter.dsp/version", "1.0");
		m->declare("compile_options", "-a /Users/manuelfarzini/personal/dev/repo/faust/architecture/_bench/arch/cpp/bench.cpp -lang cpp -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0");
		m->declare("copyright", "(c)GRAME 2006");
		m->declare("filename", "multibandfilter.dsp");
		m->declare("license", "BSD");
		m->declare("math.lib/author", "GRAME");
		m->declare("math.lib/copyright", "GRAME");
		m->declare("math.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m->declare("math.lib/license", "LGPL with exception");
		m->declare("math.lib/name", "Math Library");
		m->declare("math.lib/version", "1.0");
		m->declare("music.lib/author", "GRAME");
		m->declare("music.lib/copyright", "GRAME");
		m->declare("music.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m->declare("music.lib/license", "LGPL with exception");
		m->declare("music.lib/name", "Music Library");
		m->declare("music.lib/version", "1.0");
		m->declare("name", "multibandfilter");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() {
		return 1;
	}
	virtual int getNumOutputs() {
		return 1;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = 3.141592653589793 / std::min<double>(1.92e+05, std::max<double>(1.0, static_cast<double>(fSampleRate)));
	}
	
	virtual void instanceResetUserInterface() {
		fEntry0 = static_cast<FAUSTFLOAT>(1e+04);
		fVslider0 = static_cast<FAUSTFLOAT>(0.0);
		fEntry1 = static_cast<FAUSTFLOAT>(5e+01);
		fEntry2 = static_cast<FAUSTFLOAT>(9e+03);
		fVslider1 = static_cast<FAUSTFLOAT>(0.0);
		fEntry3 = static_cast<FAUSTFLOAT>(5e+01);
		fEntry4 = static_cast<FAUSTFLOAT>(8e+03);
		fVslider2 = static_cast<FAUSTFLOAT>(0.0);
		fEntry5 = static_cast<FAUSTFLOAT>(5e+01);
		fEntry6 = static_cast<FAUSTFLOAT>(7e+03);
		fVslider3 = static_cast<FAUSTFLOAT>(0.0);
		fEntry7 = static_cast<FAUSTFLOAT>(5e+01);
		fEntry8 = static_cast<FAUSTFLOAT>(6e+03);
		fVslider4 = static_cast<FAUSTFLOAT>(0.0);
		fEntry9 = static_cast<FAUSTFLOAT>(5e+01);
		fEntry10 = static_cast<FAUSTFLOAT>(5e+03);
		fVslider5 = static_cast<FAUSTFLOAT>(0.0);
		fEntry11 = static_cast<FAUSTFLOAT>(5e+01);
		fEntry12 = static_cast<FAUSTFLOAT>(4e+03);
		fVslider6 = static_cast<FAUSTFLOAT>(0.0);
		fEntry13 = static_cast<FAUSTFLOAT>(5e+01);
		fEntry14 = static_cast<FAUSTFLOAT>(3e+03);
		fVslider7 = static_cast<FAUSTFLOAT>(0.0);
		fEntry15 = static_cast<FAUSTFLOAT>(5e+01);
		fEntry16 = static_cast<FAUSTFLOAT>(2e+03);
		fVslider8 = static_cast<FAUSTFLOAT>(0.0);
		fEntry17 = static_cast<FAUSTFLOAT>(5e+01);
		fEntry18 = static_cast<FAUSTFLOAT>(1e+03);
		fVslider9 = static_cast<FAUSTFLOAT>(0.0);
		fEntry19 = static_cast<FAUSTFLOAT>(5e+01);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 3; l0 = l0 + 1) {
			fRec9[l0] = 0.0;
		}
		for (int l1 = 0; l1 < 3; l1 = l1 + 1) {
			fRec8[l1] = 0.0;
		}
		for (int l2 = 0; l2 < 3; l2 = l2 + 1) {
			fRec7[l2] = 0.0;
		}
		for (int l3 = 0; l3 < 3; l3 = l3 + 1) {
			fRec6[l3] = 0.0;
		}
		for (int l4 = 0; l4 < 3; l4 = l4 + 1) {
			fRec5[l4] = 0.0;
		}
		for (int l5 = 0; l5 < 3; l5 = l5 + 1) {
			fRec4[l5] = 0.0;
		}
		for (int l6 = 0; l6 < 3; l6 = l6 + 1) {
			fRec3[l6] = 0.0;
		}
		for (int l7 = 0; l7 < 3; l7 = l7 + 1) {
			fRec2[l7] = 0.0;
		}
		for (int l8 = 0; l8 < 3; l8 = l8 + 1) {
			fRec1[l8] = 0.0;
		}
		for (int l9 = 0; l9 < 3; l9 = l9 + 1) {
			fRec0[l9] = 0.0;
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
		ui_interface->openHorizontalBox("Multi Band Filter");
		ui_interface->openVerticalBox("peak 0");
		ui_interface->declare(&fEntry19, "style", "knob");
		ui_interface->addNumEntry("Q factor", &fEntry19, FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1), FAUSTFLOAT(1e+02), FAUSTFLOAT(0.1));
		ui_interface->declare(&fEntry18, "style", "knob");
		ui_interface->declare(&fEntry18, "unit", "Hz");
		ui_interface->addNumEntry("freq", &fEntry18, FAUSTFLOAT(1e+03), FAUSTFLOAT(2e+01), FAUSTFLOAT(2e+04), FAUSTFLOAT(1.0));
		ui_interface->declare(&fVslider9, "unit", "dB");
		ui_interface->addVerticalSlider("gain", &fVslider9, FAUSTFLOAT(0.0), FAUSTFLOAT(-5e+01), FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("peak 1");
		ui_interface->declare(&fEntry17, "style", "knob");
		ui_interface->addNumEntry("Q factor", &fEntry17, FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1), FAUSTFLOAT(1e+02), FAUSTFLOAT(0.1));
		ui_interface->declare(&fEntry16, "style", "knob");
		ui_interface->declare(&fEntry16, "unit", "Hz");
		ui_interface->addNumEntry("freq", &fEntry16, FAUSTFLOAT(2e+03), FAUSTFLOAT(2e+01), FAUSTFLOAT(2e+04), FAUSTFLOAT(1.0));
		ui_interface->declare(&fVslider8, "unit", "dB");
		ui_interface->addVerticalSlider("gain", &fVslider8, FAUSTFLOAT(0.0), FAUSTFLOAT(-5e+01), FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("peak 2");
		ui_interface->declare(&fEntry15, "style", "knob");
		ui_interface->addNumEntry("Q factor", &fEntry15, FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1), FAUSTFLOAT(1e+02), FAUSTFLOAT(0.1));
		ui_interface->declare(&fEntry14, "style", "knob");
		ui_interface->declare(&fEntry14, "unit", "Hz");
		ui_interface->addNumEntry("freq", &fEntry14, FAUSTFLOAT(3e+03), FAUSTFLOAT(2e+01), FAUSTFLOAT(2e+04), FAUSTFLOAT(1.0));
		ui_interface->declare(&fVslider7, "unit", "dB");
		ui_interface->addVerticalSlider("gain", &fVslider7, FAUSTFLOAT(0.0), FAUSTFLOAT(-5e+01), FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("peak 3");
		ui_interface->declare(&fEntry13, "style", "knob");
		ui_interface->addNumEntry("Q factor", &fEntry13, FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1), FAUSTFLOAT(1e+02), FAUSTFLOAT(0.1));
		ui_interface->declare(&fEntry12, "style", "knob");
		ui_interface->declare(&fEntry12, "unit", "Hz");
		ui_interface->addNumEntry("freq", &fEntry12, FAUSTFLOAT(4e+03), FAUSTFLOAT(2e+01), FAUSTFLOAT(2e+04), FAUSTFLOAT(1.0));
		ui_interface->declare(&fVslider6, "unit", "dB");
		ui_interface->addVerticalSlider("gain", &fVslider6, FAUSTFLOAT(0.0), FAUSTFLOAT(-5e+01), FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("peak 4");
		ui_interface->declare(&fEntry11, "style", "knob");
		ui_interface->addNumEntry("Q factor", &fEntry11, FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1), FAUSTFLOAT(1e+02), FAUSTFLOAT(0.1));
		ui_interface->declare(&fEntry10, "style", "knob");
		ui_interface->declare(&fEntry10, "unit", "Hz");
		ui_interface->addNumEntry("freq", &fEntry10, FAUSTFLOAT(5e+03), FAUSTFLOAT(2e+01), FAUSTFLOAT(2e+04), FAUSTFLOAT(1.0));
		ui_interface->declare(&fVslider5, "unit", "dB");
		ui_interface->addVerticalSlider("gain", &fVslider5, FAUSTFLOAT(0.0), FAUSTFLOAT(-5e+01), FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("peak 5");
		ui_interface->declare(&fEntry9, "style", "knob");
		ui_interface->addNumEntry("Q factor", &fEntry9, FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1), FAUSTFLOAT(1e+02), FAUSTFLOAT(0.1));
		ui_interface->declare(&fEntry8, "style", "knob");
		ui_interface->declare(&fEntry8, "unit", "Hz");
		ui_interface->addNumEntry("freq", &fEntry8, FAUSTFLOAT(6e+03), FAUSTFLOAT(2e+01), FAUSTFLOAT(2e+04), FAUSTFLOAT(1.0));
		ui_interface->declare(&fVslider4, "unit", "dB");
		ui_interface->addVerticalSlider("gain", &fVslider4, FAUSTFLOAT(0.0), FAUSTFLOAT(-5e+01), FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("peak 6");
		ui_interface->declare(&fEntry7, "style", "knob");
		ui_interface->addNumEntry("Q factor", &fEntry7, FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1), FAUSTFLOAT(1e+02), FAUSTFLOAT(0.1));
		ui_interface->declare(&fEntry6, "style", "knob");
		ui_interface->declare(&fEntry6, "unit", "Hz");
		ui_interface->addNumEntry("freq", &fEntry6, FAUSTFLOAT(7e+03), FAUSTFLOAT(2e+01), FAUSTFLOAT(2e+04), FAUSTFLOAT(1.0));
		ui_interface->declare(&fVslider3, "unit", "dB");
		ui_interface->addVerticalSlider("gain", &fVslider3, FAUSTFLOAT(0.0), FAUSTFLOAT(-5e+01), FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("peak 7");
		ui_interface->declare(&fEntry5, "style", "knob");
		ui_interface->addNumEntry("Q factor", &fEntry5, FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1), FAUSTFLOAT(1e+02), FAUSTFLOAT(0.1));
		ui_interface->declare(&fEntry4, "style", "knob");
		ui_interface->declare(&fEntry4, "unit", "Hz");
		ui_interface->addNumEntry("freq", &fEntry4, FAUSTFLOAT(8e+03), FAUSTFLOAT(2e+01), FAUSTFLOAT(2e+04), FAUSTFLOAT(1.0));
		ui_interface->declare(&fVslider2, "unit", "dB");
		ui_interface->addVerticalSlider("gain", &fVslider2, FAUSTFLOAT(0.0), FAUSTFLOAT(-5e+01), FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("peak 8");
		ui_interface->declare(&fEntry3, "style", "knob");
		ui_interface->addNumEntry("Q factor", &fEntry3, FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1), FAUSTFLOAT(1e+02), FAUSTFLOAT(0.1));
		ui_interface->declare(&fEntry2, "style", "knob");
		ui_interface->declare(&fEntry2, "unit", "Hz");
		ui_interface->addNumEntry("freq", &fEntry2, FAUSTFLOAT(9e+03), FAUSTFLOAT(2e+01), FAUSTFLOAT(2e+04), FAUSTFLOAT(1.0));
		ui_interface->declare(&fVslider1, "unit", "dB");
		ui_interface->addVerticalSlider("gain", &fVslider1, FAUSTFLOAT(0.0), FAUSTFLOAT(-5e+01), FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("peak 9");
		ui_interface->declare(&fEntry1, "style", "knob");
		ui_interface->addNumEntry("Q factor", &fEntry1, FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1), FAUSTFLOAT(1e+02), FAUSTFLOAT(0.1));
		ui_interface->declare(&fEntry0, "style", "knob");
		ui_interface->declare(&fEntry0, "unit", "Hz");
		ui_interface->addNumEntry("freq", &fEntry0, FAUSTFLOAT(1e+04), FAUSTFLOAT(2e+01), FAUSTFLOAT(2e+04), FAUSTFLOAT(1.0));
		ui_interface->declare(&fVslider0, "unit", "dB");
		ui_interface->addVerticalSlider("gain", &fVslider0, FAUSTFLOAT(0.0), FAUSTFLOAT(-5e+01), FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		double fSlow0 = std::tan(fConst0 * static_cast<double>(fEntry0));
		double fSlow1 = static_cast<double>(fEntry1);
		double fSlow2 = std::pow(1e+01, -(0.05 * static_cast<double>(fVslider0))) / fSlow1;
		double fSlow3 = 1.0 / (fSlow0 * (fSlow0 + fSlow2) + 1.0);
		double fSlow4 = 2.0 * (mydsp_faustpower2_f(fSlow0) + -1.0);
		double fSlow5 = std::tan(fConst0 * static_cast<double>(fEntry2));
		double fSlow6 = static_cast<double>(fEntry3);
		double fSlow7 = std::pow(1e+01, -(0.05 * static_cast<double>(fVslider1))) / fSlow6;
		double fSlow8 = 1.0 / (fSlow5 * (fSlow5 + fSlow7) + 1.0);
		double fSlow9 = 2.0 * (mydsp_faustpower2_f(fSlow5) + -1.0);
		double fSlow10 = std::tan(fConst0 * static_cast<double>(fEntry4));
		double fSlow11 = static_cast<double>(fEntry5);
		double fSlow12 = std::pow(1e+01, -(0.05 * static_cast<double>(fVslider2))) / fSlow11;
		double fSlow13 = 1.0 / (fSlow10 * (fSlow10 + fSlow12) + 1.0);
		double fSlow14 = 2.0 * (mydsp_faustpower2_f(fSlow10) + -1.0);
		double fSlow15 = std::tan(fConst0 * static_cast<double>(fEntry6));
		double fSlow16 = static_cast<double>(fEntry7);
		double fSlow17 = std::pow(1e+01, -(0.05 * static_cast<double>(fVslider3))) / fSlow16;
		double fSlow18 = 1.0 / (fSlow15 * (fSlow15 + fSlow17) + 1.0);
		double fSlow19 = 2.0 * (mydsp_faustpower2_f(fSlow15) + -1.0);
		double fSlow20 = std::tan(fConst0 * static_cast<double>(fEntry8));
		double fSlow21 = static_cast<double>(fEntry9);
		double fSlow22 = std::pow(1e+01, -(0.05 * static_cast<double>(fVslider4))) / fSlow21;
		double fSlow23 = 1.0 / (fSlow20 * (fSlow20 + fSlow22) + 1.0);
		double fSlow24 = 2.0 * (mydsp_faustpower2_f(fSlow20) + -1.0);
		double fSlow25 = std::tan(fConst0 * static_cast<double>(fEntry10));
		double fSlow26 = static_cast<double>(fEntry11);
		double fSlow27 = std::pow(1e+01, -(0.05 * static_cast<double>(fVslider5))) / fSlow26;
		double fSlow28 = 1.0 / (fSlow25 * (fSlow25 + fSlow27) + 1.0);
		double fSlow29 = 2.0 * (mydsp_faustpower2_f(fSlow25) + -1.0);
		double fSlow30 = std::tan(fConst0 * static_cast<double>(fEntry12));
		double fSlow31 = static_cast<double>(fEntry13);
		double fSlow32 = std::pow(1e+01, -(0.05 * static_cast<double>(fVslider6))) / fSlow31;
		double fSlow33 = 1.0 / (fSlow30 * (fSlow30 + fSlow32) + 1.0);
		double fSlow34 = 2.0 * (mydsp_faustpower2_f(fSlow30) + -1.0);
		double fSlow35 = std::tan(fConst0 * static_cast<double>(fEntry14));
		double fSlow36 = static_cast<double>(fEntry15);
		double fSlow37 = std::pow(1e+01, -(0.05 * static_cast<double>(fVslider7))) / fSlow36;
		double fSlow38 = 1.0 / (fSlow35 * (fSlow35 + fSlow37) + 1.0);
		double fSlow39 = 2.0 * (mydsp_faustpower2_f(fSlow35) + -1.0);
		double fSlow40 = std::tan(fConst0 * static_cast<double>(fEntry16));
		double fSlow41 = static_cast<double>(fEntry17);
		double fSlow42 = std::pow(1e+01, -(0.05 * static_cast<double>(fVslider8))) / fSlow41;
		double fSlow43 = 1.0 / (fSlow40 * (fSlow40 + fSlow42) + 1.0);
		double fSlow44 = 2.0 * (mydsp_faustpower2_f(fSlow40) + -1.0);
		double fSlow45 = std::tan(fConst0 * static_cast<double>(fEntry18));
		double fSlow46 = static_cast<double>(fEntry19);
		double fSlow47 = std::pow(1e+01, -(0.05 * static_cast<double>(fVslider9))) / fSlow46;
		double fSlow48 = 1.0 / (fSlow45 * (fSlow45 + fSlow47) + 1.0);
		double fSlow49 = 2.0 * (mydsp_faustpower2_f(fSlow45) + -1.0);
		double fSlow50 = fSlow45 * (fSlow45 - fSlow47) + 1.0;
		double fSlow51 = 1.0 / fSlow46;
		double fSlow52 = fSlow45 * (fSlow45 + fSlow51) + 1.0;
		double fSlow53 = 1.0 - fSlow45 * (fSlow51 - fSlow45);
		double fSlow54 = fSlow40 * (fSlow40 - fSlow42) + 1.0;
		double fSlow55 = 1.0 / fSlow41;
		double fSlow56 = fSlow40 * (fSlow40 + fSlow55) + 1.0;
		double fSlow57 = 1.0 - fSlow40 * (fSlow55 - fSlow40);
		double fSlow58 = fSlow35 * (fSlow35 - fSlow37) + 1.0;
		double fSlow59 = 1.0 / fSlow36;
		double fSlow60 = fSlow35 * (fSlow35 + fSlow59) + 1.0;
		double fSlow61 = 1.0 - fSlow35 * (fSlow59 - fSlow35);
		double fSlow62 = fSlow30 * (fSlow30 - fSlow32) + 1.0;
		double fSlow63 = 1.0 / fSlow31;
		double fSlow64 = fSlow30 * (fSlow30 + fSlow63) + 1.0;
		double fSlow65 = 1.0 - fSlow30 * (fSlow63 - fSlow30);
		double fSlow66 = fSlow25 * (fSlow25 - fSlow27) + 1.0;
		double fSlow67 = 1.0 / fSlow26;
		double fSlow68 = fSlow25 * (fSlow25 + fSlow67) + 1.0;
		double fSlow69 = 1.0 - fSlow25 * (fSlow67 - fSlow25);
		double fSlow70 = fSlow20 * (fSlow20 - fSlow22) + 1.0;
		double fSlow71 = 1.0 / fSlow21;
		double fSlow72 = fSlow20 * (fSlow20 + fSlow71) + 1.0;
		double fSlow73 = 1.0 - fSlow20 * (fSlow71 - fSlow20);
		double fSlow74 = fSlow15 * (fSlow15 - fSlow17) + 1.0;
		double fSlow75 = 1.0 / fSlow16;
		double fSlow76 = fSlow15 * (fSlow15 + fSlow75) + 1.0;
		double fSlow77 = 1.0 - fSlow15 * (fSlow75 - fSlow15);
		double fSlow78 = fSlow10 * (fSlow10 - fSlow12) + 1.0;
		double fSlow79 = 1.0 / fSlow11;
		double fSlow80 = fSlow10 * (fSlow10 + fSlow79) + 1.0;
		double fSlow81 = 1.0 - fSlow10 * (fSlow79 - fSlow10);
		double fSlow82 = fSlow5 * (fSlow5 - fSlow7) + 1.0;
		double fSlow83 = 1.0 / fSlow6;
		double fSlow84 = fSlow5 * (fSlow5 + fSlow83) + 1.0;
		double fSlow85 = 1.0 - fSlow5 * (fSlow83 - fSlow5);
		double fSlow86 = fSlow0 * (fSlow0 - fSlow2) + 1.0;
		double fSlow87 = 1.0 / fSlow1;
		double fSlow88 = fSlow0 * (fSlow0 + fSlow87) + 1.0;
		double fSlow89 = 1.0 - fSlow0 * (fSlow87 - fSlow0);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			double fTemp0 = fSlow49 * fRec9[1];
			fRec9[0] = static_cast<double>(input0[i0]) - fSlow48 * (fSlow50 * fRec9[2] + fTemp0);
			double fTemp1 = fSlow44 * fRec8[1];
			fRec8[0] = fSlow48 * (fTemp0 + fSlow52 * fRec9[0] + fSlow53 * fRec9[2]) - fSlow43 * (fSlow54 * fRec8[2] + fTemp1);
			double fTemp2 = fSlow39 * fRec7[1];
			fRec7[0] = fSlow43 * (fTemp1 + fSlow56 * fRec8[0] + fSlow57 * fRec8[2]) - fSlow38 * (fSlow58 * fRec7[2] + fTemp2);
			double fTemp3 = fSlow34 * fRec6[1];
			fRec6[0] = fSlow38 * (fTemp2 + fSlow60 * fRec7[0] + fSlow61 * fRec7[2]) - fSlow33 * (fSlow62 * fRec6[2] + fTemp3);
			double fTemp4 = fSlow29 * fRec5[1];
			fRec5[0] = fSlow33 * (fTemp3 + fSlow64 * fRec6[0] + fSlow65 * fRec6[2]) - fSlow28 * (fSlow66 * fRec5[2] + fTemp4);
			double fTemp5 = fSlow24 * fRec4[1];
			fRec4[0] = fSlow28 * (fTemp4 + fSlow68 * fRec5[0] + fSlow69 * fRec5[2]) - fSlow23 * (fSlow70 * fRec4[2] + fTemp5);
			double fTemp6 = fSlow19 * fRec3[1];
			fRec3[0] = fSlow23 * (fTemp5 + fSlow72 * fRec4[0] + fSlow73 * fRec4[2]) - fSlow18 * (fSlow74 * fRec3[2] + fTemp6);
			double fTemp7 = fSlow14 * fRec2[1];
			fRec2[0] = fSlow18 * (fTemp6 + fSlow76 * fRec3[0] + fSlow77 * fRec3[2]) - fSlow13 * (fSlow78 * fRec2[2] + fTemp7);
			double fTemp8 = fSlow9 * fRec1[1];
			fRec1[0] = fSlow13 * (fTemp7 + fSlow80 * fRec2[0] + fSlow81 * fRec2[2]) - fSlow8 * (fSlow82 * fRec1[2] + fTemp8);
			double fTemp9 = fSlow4 * fRec0[1];
			fRec0[0] = fSlow8 * (fTemp8 + fSlow84 * fRec1[0] + fSlow85 * fRec1[2]) - fSlow3 * (fSlow86 * fRec0[2] + fTemp9);
			output0[i0] = static_cast<FAUSTFLOAT>(fSlow3 * (fTemp9 + fSlow88 * fRec0[0] + fSlow89 * fRec0[2]));
			fRec9[2] = fRec9[1];
			fRec9[1] = fRec9[0];
			fRec8[2] = fRec8[1];
			fRec8[1] = fRec8[0];
			fRec7[2] = fRec7[1];
			fRec7[1] = fRec7[0];
			fRec6[2] = fRec6[1];
			fRec6[1] = fRec6[0];
			fRec5[2] = fRec5[1];
			fRec5[1] = fRec5[0];
			fRec4[2] = fRec4[1];
			fRec4[1] = fRec4[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
		}
	}

};

int main() {
    auto dsp = new mydsp();
    dsp->init(SAMP_RATE);
    
    s32 n_ins = dsp->getNumInputs();
    s32 n_outs = dsp->getNumOutputs();
    auto [base, err] = make_buffers(n_ins, n_outs);
    if (err) {
        printf("Critical allocation error: %d\n", err);
        exit(err);
    }

    Real** inputs = (Real**)base;
    Real** outputs = inputs + n_ins;

#if FILL_INPUTS
    fill_inputs(inputs, dsp->getNumInputs());
#endif

    warmup(*dsp, inputs, outputs);
    FaustReport report = measure(*dsp, inputs, outputs);
    report.checksum = checksum_outputs(outputs, n_outs);
    print_report(report); // the output will be redirected via script

#if WRITE_CSV
    write_csv(report);
#endif

    free_buffers(inputs);
    return 0;
}

#endif
