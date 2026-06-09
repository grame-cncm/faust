/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2006"
license: "BSD"
name: "multibandfilter"
version: "1.0"
Code generated with Faust 2.85.5 (https://faust.grame.fr)
Compilation options: -a /Users/manuelfarzini/personal/dev/repo/faust/architecture/_bench/arch/cpp/bench.cpp -lang cpp -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 32
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
	double fRec9_perm[4];
	FAUSTFLOAT fEntry2;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fEntry3;
	double fRec8_perm[4];
	FAUSTFLOAT fEntry4;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT fEntry5;
	double fRec7_perm[4];
	FAUSTFLOAT fEntry6;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT fEntry7;
	double fRec6_perm[4];
	FAUSTFLOAT fEntry8;
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT fEntry9;
	double fRec5_perm[4];
	FAUSTFLOAT fEntry10;
	FAUSTFLOAT fVslider5;
	FAUSTFLOAT fEntry11;
	double fRec4_perm[4];
	FAUSTFLOAT fEntry12;
	FAUSTFLOAT fVslider6;
	FAUSTFLOAT fEntry13;
	double fRec3_perm[4];
	FAUSTFLOAT fEntry14;
	FAUSTFLOAT fVslider7;
	FAUSTFLOAT fEntry15;
	double fRec2_perm[4];
	FAUSTFLOAT fEntry16;
	FAUSTFLOAT fVslider8;
	FAUSTFLOAT fEntry17;
	double fRec1_perm[4];
	FAUSTFLOAT fEntry18;
	FAUSTFLOAT fVslider9;
	FAUSTFLOAT fEntry19;
	double fRec0_perm[4];
	
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
		m->declare("compile_options", "-a /Users/manuelfarzini/personal/dev/repo/faust/architecture/_bench/arch/cpp/bench.cpp -lang cpp -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 32");
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
		fEntry0 = static_cast<FAUSTFLOAT>(1e+03);
		fVslider0 = static_cast<FAUSTFLOAT>(0.0);
		fEntry1 = static_cast<FAUSTFLOAT>(5e+01);
		fEntry2 = static_cast<FAUSTFLOAT>(2e+03);
		fVslider1 = static_cast<FAUSTFLOAT>(0.0);
		fEntry3 = static_cast<FAUSTFLOAT>(5e+01);
		fEntry4 = static_cast<FAUSTFLOAT>(3e+03);
		fVslider2 = static_cast<FAUSTFLOAT>(0.0);
		fEntry5 = static_cast<FAUSTFLOAT>(5e+01);
		fEntry6 = static_cast<FAUSTFLOAT>(4e+03);
		fVslider3 = static_cast<FAUSTFLOAT>(0.0);
		fEntry7 = static_cast<FAUSTFLOAT>(5e+01);
		fEntry8 = static_cast<FAUSTFLOAT>(5e+03);
		fVslider4 = static_cast<FAUSTFLOAT>(0.0);
		fEntry9 = static_cast<FAUSTFLOAT>(5e+01);
		fEntry10 = static_cast<FAUSTFLOAT>(6e+03);
		fVslider5 = static_cast<FAUSTFLOAT>(0.0);
		fEntry11 = static_cast<FAUSTFLOAT>(5e+01);
		fEntry12 = static_cast<FAUSTFLOAT>(7e+03);
		fVslider6 = static_cast<FAUSTFLOAT>(0.0);
		fEntry13 = static_cast<FAUSTFLOAT>(5e+01);
		fEntry14 = static_cast<FAUSTFLOAT>(8e+03);
		fVslider7 = static_cast<FAUSTFLOAT>(0.0);
		fEntry15 = static_cast<FAUSTFLOAT>(5e+01);
		fEntry16 = static_cast<FAUSTFLOAT>(9e+03);
		fVslider8 = static_cast<FAUSTFLOAT>(0.0);
		fEntry17 = static_cast<FAUSTFLOAT>(5e+01);
		fEntry18 = static_cast<FAUSTFLOAT>(1e+04);
		fVslider9 = static_cast<FAUSTFLOAT>(0.0);
		fEntry19 = static_cast<FAUSTFLOAT>(5e+01);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 4; l0 = l0 + 1) {
			fRec9_perm[l0] = 0.0;
		}
		for (int l1 = 0; l1 < 4; l1 = l1 + 1) {
			fRec8_perm[l1] = 0.0;
		}
		for (int l2 = 0; l2 < 4; l2 = l2 + 1) {
			fRec7_perm[l2] = 0.0;
		}
		for (int l3 = 0; l3 < 4; l3 = l3 + 1) {
			fRec6_perm[l3] = 0.0;
		}
		for (int l4 = 0; l4 < 4; l4 = l4 + 1) {
			fRec5_perm[l4] = 0.0;
		}
		for (int l5 = 0; l5 < 4; l5 = l5 + 1) {
			fRec4_perm[l5] = 0.0;
		}
		for (int l6 = 0; l6 < 4; l6 = l6 + 1) {
			fRec3_perm[l6] = 0.0;
		}
		for (int l7 = 0; l7 < 4; l7 = l7 + 1) {
			fRec2_perm[l7] = 0.0;
		}
		for (int l8 = 0; l8 < 4; l8 = l8 + 1) {
			fRec1_perm[l8] = 0.0;
		}
		for (int l9 = 0; l9 < 4; l9 = l9 + 1) {
			fRec0_perm[l9] = 0.0;
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
		ui_interface->declare(&fEntry1, "style", "knob");
		ui_interface->addNumEntry("Q factor", &fEntry1, FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1), FAUSTFLOAT(1e+02), FAUSTFLOAT(0.1));
		ui_interface->declare(&fEntry0, "style", "knob");
		ui_interface->declare(&fEntry0, "unit", "Hz");
		ui_interface->addNumEntry("freq", &fEntry0, FAUSTFLOAT(1e+03), FAUSTFLOAT(2e+01), FAUSTFLOAT(2e+04), FAUSTFLOAT(1.0));
		ui_interface->declare(&fVslider0, "unit", "dB");
		ui_interface->addVerticalSlider("gain", &fVslider0, FAUSTFLOAT(0.0), FAUSTFLOAT(-5e+01), FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("peak 1");
		ui_interface->declare(&fEntry3, "style", "knob");
		ui_interface->addNumEntry("Q factor", &fEntry3, FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1), FAUSTFLOAT(1e+02), FAUSTFLOAT(0.1));
		ui_interface->declare(&fEntry2, "style", "knob");
		ui_interface->declare(&fEntry2, "unit", "Hz");
		ui_interface->addNumEntry("freq", &fEntry2, FAUSTFLOAT(2e+03), FAUSTFLOAT(2e+01), FAUSTFLOAT(2e+04), FAUSTFLOAT(1.0));
		ui_interface->declare(&fVslider1, "unit", "dB");
		ui_interface->addVerticalSlider("gain", &fVslider1, FAUSTFLOAT(0.0), FAUSTFLOAT(-5e+01), FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("peak 2");
		ui_interface->declare(&fEntry5, "style", "knob");
		ui_interface->addNumEntry("Q factor", &fEntry5, FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1), FAUSTFLOAT(1e+02), FAUSTFLOAT(0.1));
		ui_interface->declare(&fEntry4, "style", "knob");
		ui_interface->declare(&fEntry4, "unit", "Hz");
		ui_interface->addNumEntry("freq", &fEntry4, FAUSTFLOAT(3e+03), FAUSTFLOAT(2e+01), FAUSTFLOAT(2e+04), FAUSTFLOAT(1.0));
		ui_interface->declare(&fVslider2, "unit", "dB");
		ui_interface->addVerticalSlider("gain", &fVslider2, FAUSTFLOAT(0.0), FAUSTFLOAT(-5e+01), FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("peak 3");
		ui_interface->declare(&fEntry7, "style", "knob");
		ui_interface->addNumEntry("Q factor", &fEntry7, FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1), FAUSTFLOAT(1e+02), FAUSTFLOAT(0.1));
		ui_interface->declare(&fEntry6, "style", "knob");
		ui_interface->declare(&fEntry6, "unit", "Hz");
		ui_interface->addNumEntry("freq", &fEntry6, FAUSTFLOAT(4e+03), FAUSTFLOAT(2e+01), FAUSTFLOAT(2e+04), FAUSTFLOAT(1.0));
		ui_interface->declare(&fVslider3, "unit", "dB");
		ui_interface->addVerticalSlider("gain", &fVslider3, FAUSTFLOAT(0.0), FAUSTFLOAT(-5e+01), FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("peak 4");
		ui_interface->declare(&fEntry9, "style", "knob");
		ui_interface->addNumEntry("Q factor", &fEntry9, FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1), FAUSTFLOAT(1e+02), FAUSTFLOAT(0.1));
		ui_interface->declare(&fEntry8, "style", "knob");
		ui_interface->declare(&fEntry8, "unit", "Hz");
		ui_interface->addNumEntry("freq", &fEntry8, FAUSTFLOAT(5e+03), FAUSTFLOAT(2e+01), FAUSTFLOAT(2e+04), FAUSTFLOAT(1.0));
		ui_interface->declare(&fVslider4, "unit", "dB");
		ui_interface->addVerticalSlider("gain", &fVslider4, FAUSTFLOAT(0.0), FAUSTFLOAT(-5e+01), FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("peak 5");
		ui_interface->declare(&fEntry11, "style", "knob");
		ui_interface->addNumEntry("Q factor", &fEntry11, FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1), FAUSTFLOAT(1e+02), FAUSTFLOAT(0.1));
		ui_interface->declare(&fEntry10, "style", "knob");
		ui_interface->declare(&fEntry10, "unit", "Hz");
		ui_interface->addNumEntry("freq", &fEntry10, FAUSTFLOAT(6e+03), FAUSTFLOAT(2e+01), FAUSTFLOAT(2e+04), FAUSTFLOAT(1.0));
		ui_interface->declare(&fVslider5, "unit", "dB");
		ui_interface->addVerticalSlider("gain", &fVslider5, FAUSTFLOAT(0.0), FAUSTFLOAT(-5e+01), FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("peak 6");
		ui_interface->declare(&fEntry13, "style", "knob");
		ui_interface->addNumEntry("Q factor", &fEntry13, FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1), FAUSTFLOAT(1e+02), FAUSTFLOAT(0.1));
		ui_interface->declare(&fEntry12, "style", "knob");
		ui_interface->declare(&fEntry12, "unit", "Hz");
		ui_interface->addNumEntry("freq", &fEntry12, FAUSTFLOAT(7e+03), FAUSTFLOAT(2e+01), FAUSTFLOAT(2e+04), FAUSTFLOAT(1.0));
		ui_interface->declare(&fVslider6, "unit", "dB");
		ui_interface->addVerticalSlider("gain", &fVslider6, FAUSTFLOAT(0.0), FAUSTFLOAT(-5e+01), FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("peak 7");
		ui_interface->declare(&fEntry15, "style", "knob");
		ui_interface->addNumEntry("Q factor", &fEntry15, FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1), FAUSTFLOAT(1e+02), FAUSTFLOAT(0.1));
		ui_interface->declare(&fEntry14, "style", "knob");
		ui_interface->declare(&fEntry14, "unit", "Hz");
		ui_interface->addNumEntry("freq", &fEntry14, FAUSTFLOAT(8e+03), FAUSTFLOAT(2e+01), FAUSTFLOAT(2e+04), FAUSTFLOAT(1.0));
		ui_interface->declare(&fVslider7, "unit", "dB");
		ui_interface->addVerticalSlider("gain", &fVslider7, FAUSTFLOAT(0.0), FAUSTFLOAT(-5e+01), FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("peak 8");
		ui_interface->declare(&fEntry17, "style", "knob");
		ui_interface->addNumEntry("Q factor", &fEntry17, FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1), FAUSTFLOAT(1e+02), FAUSTFLOAT(0.1));
		ui_interface->declare(&fEntry16, "style", "knob");
		ui_interface->declare(&fEntry16, "unit", "Hz");
		ui_interface->addNumEntry("freq", &fEntry16, FAUSTFLOAT(9e+03), FAUSTFLOAT(2e+01), FAUSTFLOAT(2e+04), FAUSTFLOAT(1.0));
		ui_interface->declare(&fVslider8, "unit", "dB");
		ui_interface->addVerticalSlider("gain", &fVslider8, FAUSTFLOAT(0.0), FAUSTFLOAT(-5e+01), FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("peak 9");
		ui_interface->declare(&fEntry19, "style", "knob");
		ui_interface->addNumEntry("Q factor", &fEntry19, FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1), FAUSTFLOAT(1e+02), FAUSTFLOAT(0.1));
		ui_interface->declare(&fEntry18, "style", "knob");
		ui_interface->declare(&fEntry18, "unit", "Hz");
		ui_interface->addNumEntry("freq", &fEntry18, FAUSTFLOAT(1e+04), FAUSTFLOAT(2e+01), FAUSTFLOAT(2e+04), FAUSTFLOAT(1.0));
		ui_interface->declare(&fVslider9, "unit", "dB");
		ui_interface->addVerticalSlider("gain", &fVslider9, FAUSTFLOAT(0.0), FAUSTFLOAT(-5e+01), FAUSTFLOAT(5e+01), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0_ptr = inputs[0];
		FAUSTFLOAT* output0_ptr = outputs[0];
		double fSlow0 = std::tan(fConst0 * static_cast<double>(fEntry0));
		double fSlow1 = static_cast<double>(fEntry1);
		double fSlow2 = std::pow(1e+01, -(0.05 * static_cast<double>(fVslider0))) / fSlow1;
		double fSlow3 = 1.0 / (fSlow0 * (fSlow0 + fSlow2) + 1.0);
		double fSlow4 = fSlow0 * (fSlow0 - fSlow2) + 1.0;
		double fSlow5 = 2.0 * (mydsp_faustpower2_f(fSlow0) + -1.0);
		double fZec0[32];
		double fRec9_tmp[36];
		double* fRec9 = &fRec9_tmp[4];
		double fSlow6 = 1.0 / fSlow1;
		double fSlow7 = fSlow0 * (fSlow0 + fSlow6) + 1.0;
		double fSlow8 = 1.0 - fSlow0 * (fSlow6 - fSlow0);
		double fSlow9 = std::tan(fConst0 * static_cast<double>(fEntry2));
		double fSlow10 = static_cast<double>(fEntry3);
		double fSlow11 = std::pow(1e+01, -(0.05 * static_cast<double>(fVslider1))) / fSlow10;
		double fSlow12 = 1.0 / (fSlow9 * (fSlow9 + fSlow11) + 1.0);
		double fSlow13 = fSlow9 * (fSlow9 - fSlow11) + 1.0;
		double fSlow14 = 2.0 * (mydsp_faustpower2_f(fSlow9) + -1.0);
		double fZec1[32];
		double fRec8_tmp[36];
		double* fRec8 = &fRec8_tmp[4];
		double fSlow15 = 1.0 / fSlow10;
		double fSlow16 = fSlow9 * (fSlow9 + fSlow15) + 1.0;
		double fSlow17 = 1.0 - fSlow9 * (fSlow15 - fSlow9);
		double fSlow18 = std::tan(fConst0 * static_cast<double>(fEntry4));
		double fSlow19 = static_cast<double>(fEntry5);
		double fSlow20 = std::pow(1e+01, -(0.05 * static_cast<double>(fVslider2))) / fSlow19;
		double fSlow21 = 1.0 / (fSlow18 * (fSlow18 + fSlow20) + 1.0);
		double fSlow22 = fSlow18 * (fSlow18 - fSlow20) + 1.0;
		double fSlow23 = 2.0 * (mydsp_faustpower2_f(fSlow18) + -1.0);
		double fZec2[32];
		double fRec7_tmp[36];
		double* fRec7 = &fRec7_tmp[4];
		double fSlow24 = 1.0 / fSlow19;
		double fSlow25 = fSlow18 * (fSlow18 + fSlow24) + 1.0;
		double fSlow26 = 1.0 - fSlow18 * (fSlow24 - fSlow18);
		double fSlow27 = std::tan(fConst0 * static_cast<double>(fEntry6));
		double fSlow28 = static_cast<double>(fEntry7);
		double fSlow29 = std::pow(1e+01, -(0.05 * static_cast<double>(fVslider3))) / fSlow28;
		double fSlow30 = 1.0 / (fSlow27 * (fSlow27 + fSlow29) + 1.0);
		double fSlow31 = fSlow27 * (fSlow27 - fSlow29) + 1.0;
		double fSlow32 = 2.0 * (mydsp_faustpower2_f(fSlow27) + -1.0);
		double fZec3[32];
		double fRec6_tmp[36];
		double* fRec6 = &fRec6_tmp[4];
		double fSlow33 = 1.0 / fSlow28;
		double fSlow34 = fSlow27 * (fSlow27 + fSlow33) + 1.0;
		double fSlow35 = 1.0 - fSlow27 * (fSlow33 - fSlow27);
		double fSlow36 = std::tan(fConst0 * static_cast<double>(fEntry8));
		double fSlow37 = static_cast<double>(fEntry9);
		double fSlow38 = std::pow(1e+01, -(0.05 * static_cast<double>(fVslider4))) / fSlow37;
		double fSlow39 = 1.0 / (fSlow36 * (fSlow36 + fSlow38) + 1.0);
		double fSlow40 = fSlow36 * (fSlow36 - fSlow38) + 1.0;
		double fSlow41 = 2.0 * (mydsp_faustpower2_f(fSlow36) + -1.0);
		double fZec4[32];
		double fRec5_tmp[36];
		double* fRec5 = &fRec5_tmp[4];
		double fSlow42 = 1.0 / fSlow37;
		double fSlow43 = fSlow36 * (fSlow36 + fSlow42) + 1.0;
		double fSlow44 = 1.0 - fSlow36 * (fSlow42 - fSlow36);
		double fSlow45 = std::tan(fConst0 * static_cast<double>(fEntry10));
		double fSlow46 = static_cast<double>(fEntry11);
		double fSlow47 = std::pow(1e+01, -(0.05 * static_cast<double>(fVslider5))) / fSlow46;
		double fSlow48 = 1.0 / (fSlow45 * (fSlow45 + fSlow47) + 1.0);
		double fSlow49 = fSlow45 * (fSlow45 - fSlow47) + 1.0;
		double fSlow50 = 2.0 * (mydsp_faustpower2_f(fSlow45) + -1.0);
		double fZec5[32];
		double fRec4_tmp[36];
		double* fRec4 = &fRec4_tmp[4];
		double fSlow51 = 1.0 / fSlow46;
		double fSlow52 = fSlow45 * (fSlow45 + fSlow51) + 1.0;
		double fSlow53 = 1.0 - fSlow45 * (fSlow51 - fSlow45);
		double fSlow54 = std::tan(fConst0 * static_cast<double>(fEntry12));
		double fSlow55 = static_cast<double>(fEntry13);
		double fSlow56 = std::pow(1e+01, -(0.05 * static_cast<double>(fVslider6))) / fSlow55;
		double fSlow57 = 1.0 / (fSlow54 * (fSlow54 + fSlow56) + 1.0);
		double fSlow58 = fSlow54 * (fSlow54 - fSlow56) + 1.0;
		double fSlow59 = 2.0 * (mydsp_faustpower2_f(fSlow54) + -1.0);
		double fZec6[32];
		double fRec3_tmp[36];
		double* fRec3 = &fRec3_tmp[4];
		double fSlow60 = 1.0 / fSlow55;
		double fSlow61 = fSlow54 * (fSlow54 + fSlow60) + 1.0;
		double fSlow62 = 1.0 - fSlow54 * (fSlow60 - fSlow54);
		double fSlow63 = std::tan(fConst0 * static_cast<double>(fEntry14));
		double fSlow64 = static_cast<double>(fEntry15);
		double fSlow65 = std::pow(1e+01, -(0.05 * static_cast<double>(fVslider7))) / fSlow64;
		double fSlow66 = 1.0 / (fSlow63 * (fSlow63 + fSlow65) + 1.0);
		double fSlow67 = fSlow63 * (fSlow63 - fSlow65) + 1.0;
		double fSlow68 = 2.0 * (mydsp_faustpower2_f(fSlow63) + -1.0);
		double fZec7[32];
		double fRec2_tmp[36];
		double* fRec2 = &fRec2_tmp[4];
		double fSlow69 = 1.0 / fSlow64;
		double fSlow70 = fSlow63 * (fSlow63 + fSlow69) + 1.0;
		double fSlow71 = 1.0 - fSlow63 * (fSlow69 - fSlow63);
		double fSlow72 = std::tan(fConst0 * static_cast<double>(fEntry16));
		double fSlow73 = static_cast<double>(fEntry17);
		double fSlow74 = std::pow(1e+01, -(0.05 * static_cast<double>(fVslider8))) / fSlow73;
		double fSlow75 = 1.0 / (fSlow72 * (fSlow72 + fSlow74) + 1.0);
		double fSlow76 = fSlow72 * (fSlow72 - fSlow74) + 1.0;
		double fSlow77 = 2.0 * (mydsp_faustpower2_f(fSlow72) + -1.0);
		double fZec8[32];
		double fRec1_tmp[36];
		double* fRec1 = &fRec1_tmp[4];
		double fSlow78 = 1.0 / fSlow73;
		double fSlow79 = fSlow72 * (fSlow72 + fSlow78) + 1.0;
		double fSlow80 = 1.0 - fSlow72 * (fSlow78 - fSlow72);
		double fSlow81 = std::tan(fConst0 * static_cast<double>(fEntry18));
		double fSlow82 = static_cast<double>(fEntry19);
		double fSlow83 = std::pow(1e+01, -(0.05 * static_cast<double>(fVslider9))) / fSlow82;
		double fSlow84 = 1.0 / (fSlow81 * (fSlow81 + fSlow83) + 1.0);
		double fSlow85 = fSlow81 * (fSlow81 - fSlow83) + 1.0;
		double fSlow86 = 2.0 * (mydsp_faustpower2_f(fSlow81) + -1.0);
		double fZec9[32];
		double fRec0_tmp[36];
		double* fRec0 = &fRec0_tmp[4];
		double fSlow87 = 1.0 / fSlow82;
		double fSlow88 = fSlow81 * (fSlow81 + fSlow87) + 1.0;
		double fSlow89 = 1.0 - fSlow81 * (fSlow87 - fSlow81);
		int vindex = 0;
		/* Main loop */
		for (vindex = 0; vindex <= (count - 32); vindex = vindex + 32) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			int vsize = 32;
			/* Recursive loop 0 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = j0 + 1) {
				fRec9_tmp[j0] = fRec9_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec0[i] = fSlow5 * fRec9[i - 1];
				fRec9[i] = static_cast<double>(input0[i]) - fSlow3 * (fSlow4 * fRec9[i - 2] + fZec0[i]);
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = j1 + 1) {
				fRec9_perm[j1] = fRec9_tmp[vsize + j1];
			}
			/* Recursive loop 1 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = j2 + 1) {
				fRec8_tmp[j2] = fRec8_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec1[i] = fSlow14 * fRec8[i - 1];
				fRec8[i] = fSlow3 * (fZec0[i] + fSlow7 * fRec9[i] + fSlow8 * fRec9[i - 2]) - fSlow12 * (fSlow13 * fRec8[i - 2] + fZec1[i]);
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = j3 + 1) {
				fRec8_perm[j3] = fRec8_tmp[vsize + j3];
			}
			/* Recursive loop 2 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = j4 + 1) {
				fRec7_tmp[j4] = fRec7_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec2[i] = fSlow23 * fRec7[i - 1];
				fRec7[i] = fSlow12 * (fZec1[i] + fSlow16 * fRec8[i] + fSlow17 * fRec8[i - 2]) - fSlow21 * (fSlow22 * fRec7[i - 2] + fZec2[i]);
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = j5 + 1) {
				fRec7_perm[j5] = fRec7_tmp[vsize + j5];
			}
			/* Recursive loop 3 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = j6 + 1) {
				fRec6_tmp[j6] = fRec6_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec3[i] = fSlow32 * fRec6[i - 1];
				fRec6[i] = fSlow21 * (fZec2[i] + fSlow25 * fRec7[i] + fSlow26 * fRec7[i - 2]) - fSlow30 * (fSlow31 * fRec6[i - 2] + fZec3[i]);
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = j7 + 1) {
				fRec6_perm[j7] = fRec6_tmp[vsize + j7];
			}
			/* Recursive loop 4 */
			/* Pre code */
			for (int j8 = 0; j8 < 4; j8 = j8 + 1) {
				fRec5_tmp[j8] = fRec5_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec4[i] = fSlow41 * fRec5[i - 1];
				fRec5[i] = fSlow30 * (fZec3[i] + fSlow34 * fRec6[i] + fSlow35 * fRec6[i - 2]) - fSlow39 * (fSlow40 * fRec5[i - 2] + fZec4[i]);
			}
			/* Post code */
			for (int j9 = 0; j9 < 4; j9 = j9 + 1) {
				fRec5_perm[j9] = fRec5_tmp[vsize + j9];
			}
			/* Recursive loop 5 */
			/* Pre code */
			for (int j10 = 0; j10 < 4; j10 = j10 + 1) {
				fRec4_tmp[j10] = fRec4_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec5[i] = fSlow50 * fRec4[i - 1];
				fRec4[i] = fSlow39 * (fZec4[i] + fSlow43 * fRec5[i] + fSlow44 * fRec5[i - 2]) - fSlow48 * (fSlow49 * fRec4[i - 2] + fZec5[i]);
			}
			/* Post code */
			for (int j11 = 0; j11 < 4; j11 = j11 + 1) {
				fRec4_perm[j11] = fRec4_tmp[vsize + j11];
			}
			/* Recursive loop 6 */
			/* Pre code */
			for (int j12 = 0; j12 < 4; j12 = j12 + 1) {
				fRec3_tmp[j12] = fRec3_perm[j12];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec6[i] = fSlow59 * fRec3[i - 1];
				fRec3[i] = fSlow48 * (fZec5[i] + fSlow52 * fRec4[i] + fSlow53 * fRec4[i - 2]) - fSlow57 * (fSlow58 * fRec3[i - 2] + fZec6[i]);
			}
			/* Post code */
			for (int j13 = 0; j13 < 4; j13 = j13 + 1) {
				fRec3_perm[j13] = fRec3_tmp[vsize + j13];
			}
			/* Recursive loop 7 */
			/* Pre code */
			for (int j14 = 0; j14 < 4; j14 = j14 + 1) {
				fRec2_tmp[j14] = fRec2_perm[j14];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec7[i] = fSlow68 * fRec2[i - 1];
				fRec2[i] = fSlow57 * (fZec6[i] + fSlow61 * fRec3[i] + fSlow62 * fRec3[i - 2]) - fSlow66 * (fSlow67 * fRec2[i - 2] + fZec7[i]);
			}
			/* Post code */
			for (int j15 = 0; j15 < 4; j15 = j15 + 1) {
				fRec2_perm[j15] = fRec2_tmp[vsize + j15];
			}
			/* Recursive loop 8 */
			/* Pre code */
			for (int j16 = 0; j16 < 4; j16 = j16 + 1) {
				fRec1_tmp[j16] = fRec1_perm[j16];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec8[i] = fSlow77 * fRec1[i - 1];
				fRec1[i] = fSlow66 * (fZec7[i] + fSlow70 * fRec2[i] + fSlow71 * fRec2[i - 2]) - fSlow75 * (fSlow76 * fRec1[i - 2] + fZec8[i]);
			}
			/* Post code */
			for (int j17 = 0; j17 < 4; j17 = j17 + 1) {
				fRec1_perm[j17] = fRec1_tmp[vsize + j17];
			}
			/* Recursive loop 9 */
			/* Pre code */
			for (int j18 = 0; j18 < 4; j18 = j18 + 1) {
				fRec0_tmp[j18] = fRec0_perm[j18];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec9[i] = fSlow86 * fRec0[i - 1];
				fRec0[i] = fSlow75 * (fZec8[i] + fSlow79 * fRec1[i] + fSlow80 * fRec1[i - 2]) - fSlow84 * (fSlow85 * fRec0[i - 2] + fZec9[i]);
			}
			/* Post code */
			for (int j19 = 0; j19 < 4; j19 = j19 + 1) {
				fRec0_perm[j19] = fRec0_tmp[vsize + j19];
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				output0[i] = static_cast<FAUSTFLOAT>(fSlow84 * (fZec9[i] + fSlow88 * fRec0[i] + fSlow89 * fRec0[i - 2]));
			}
		}
		/* Remaining frames */
		if (vindex < count) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			int vsize = count - vindex;
			/* Recursive loop 0 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = j0 + 1) {
				fRec9_tmp[j0] = fRec9_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec0[i] = fSlow5 * fRec9[i - 1];
				fRec9[i] = static_cast<double>(input0[i]) - fSlow3 * (fSlow4 * fRec9[i - 2] + fZec0[i]);
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = j1 + 1) {
				fRec9_perm[j1] = fRec9_tmp[vsize + j1];
			}
			/* Recursive loop 1 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = j2 + 1) {
				fRec8_tmp[j2] = fRec8_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec1[i] = fSlow14 * fRec8[i - 1];
				fRec8[i] = fSlow3 * (fZec0[i] + fSlow7 * fRec9[i] + fSlow8 * fRec9[i - 2]) - fSlow12 * (fSlow13 * fRec8[i - 2] + fZec1[i]);
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = j3 + 1) {
				fRec8_perm[j3] = fRec8_tmp[vsize + j3];
			}
			/* Recursive loop 2 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = j4 + 1) {
				fRec7_tmp[j4] = fRec7_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec2[i] = fSlow23 * fRec7[i - 1];
				fRec7[i] = fSlow12 * (fZec1[i] + fSlow16 * fRec8[i] + fSlow17 * fRec8[i - 2]) - fSlow21 * (fSlow22 * fRec7[i - 2] + fZec2[i]);
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = j5 + 1) {
				fRec7_perm[j5] = fRec7_tmp[vsize + j5];
			}
			/* Recursive loop 3 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = j6 + 1) {
				fRec6_tmp[j6] = fRec6_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec3[i] = fSlow32 * fRec6[i - 1];
				fRec6[i] = fSlow21 * (fZec2[i] + fSlow25 * fRec7[i] + fSlow26 * fRec7[i - 2]) - fSlow30 * (fSlow31 * fRec6[i - 2] + fZec3[i]);
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = j7 + 1) {
				fRec6_perm[j7] = fRec6_tmp[vsize + j7];
			}
			/* Recursive loop 4 */
			/* Pre code */
			for (int j8 = 0; j8 < 4; j8 = j8 + 1) {
				fRec5_tmp[j8] = fRec5_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec4[i] = fSlow41 * fRec5[i - 1];
				fRec5[i] = fSlow30 * (fZec3[i] + fSlow34 * fRec6[i] + fSlow35 * fRec6[i - 2]) - fSlow39 * (fSlow40 * fRec5[i - 2] + fZec4[i]);
			}
			/* Post code */
			for (int j9 = 0; j9 < 4; j9 = j9 + 1) {
				fRec5_perm[j9] = fRec5_tmp[vsize + j9];
			}
			/* Recursive loop 5 */
			/* Pre code */
			for (int j10 = 0; j10 < 4; j10 = j10 + 1) {
				fRec4_tmp[j10] = fRec4_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec5[i] = fSlow50 * fRec4[i - 1];
				fRec4[i] = fSlow39 * (fZec4[i] + fSlow43 * fRec5[i] + fSlow44 * fRec5[i - 2]) - fSlow48 * (fSlow49 * fRec4[i - 2] + fZec5[i]);
			}
			/* Post code */
			for (int j11 = 0; j11 < 4; j11 = j11 + 1) {
				fRec4_perm[j11] = fRec4_tmp[vsize + j11];
			}
			/* Recursive loop 6 */
			/* Pre code */
			for (int j12 = 0; j12 < 4; j12 = j12 + 1) {
				fRec3_tmp[j12] = fRec3_perm[j12];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec6[i] = fSlow59 * fRec3[i - 1];
				fRec3[i] = fSlow48 * (fZec5[i] + fSlow52 * fRec4[i] + fSlow53 * fRec4[i - 2]) - fSlow57 * (fSlow58 * fRec3[i - 2] + fZec6[i]);
			}
			/* Post code */
			for (int j13 = 0; j13 < 4; j13 = j13 + 1) {
				fRec3_perm[j13] = fRec3_tmp[vsize + j13];
			}
			/* Recursive loop 7 */
			/* Pre code */
			for (int j14 = 0; j14 < 4; j14 = j14 + 1) {
				fRec2_tmp[j14] = fRec2_perm[j14];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec7[i] = fSlow68 * fRec2[i - 1];
				fRec2[i] = fSlow57 * (fZec6[i] + fSlow61 * fRec3[i] + fSlow62 * fRec3[i - 2]) - fSlow66 * (fSlow67 * fRec2[i - 2] + fZec7[i]);
			}
			/* Post code */
			for (int j15 = 0; j15 < 4; j15 = j15 + 1) {
				fRec2_perm[j15] = fRec2_tmp[vsize + j15];
			}
			/* Recursive loop 8 */
			/* Pre code */
			for (int j16 = 0; j16 < 4; j16 = j16 + 1) {
				fRec1_tmp[j16] = fRec1_perm[j16];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec8[i] = fSlow77 * fRec1[i - 1];
				fRec1[i] = fSlow66 * (fZec7[i] + fSlow70 * fRec2[i] + fSlow71 * fRec2[i - 2]) - fSlow75 * (fSlow76 * fRec1[i - 2] + fZec8[i]);
			}
			/* Post code */
			for (int j17 = 0; j17 < 4; j17 = j17 + 1) {
				fRec1_perm[j17] = fRec1_tmp[vsize + j17];
			}
			/* Recursive loop 9 */
			/* Pre code */
			for (int j18 = 0; j18 < 4; j18 = j18 + 1) {
				fRec0_tmp[j18] = fRec0_perm[j18];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec9[i] = fSlow86 * fRec0[i - 1];
				fRec0[i] = fSlow75 * (fZec8[i] + fSlow79 * fRec1[i] + fSlow80 * fRec1[i - 2]) - fSlow84 * (fSlow85 * fRec0[i - 2] + fZec9[i]);
			}
			/* Post code */
			for (int j19 = 0; j19 < 4; j19 = j19 + 1) {
				fRec0_perm[j19] = fRec0_tmp[vsize + j19];
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				output0[i] = static_cast<FAUSTFLOAT>(fSlow84 * (fZec9[i] + fSlow88 * fRec0[i] + fSlow89 * fRec0[i - 2]));
			}
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
