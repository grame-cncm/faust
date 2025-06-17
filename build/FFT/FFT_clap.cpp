/* ------------------------------------------------------------
author: "JOS"
license: "STK-4.3"
name: "FFT"
Code generated with Faust 2.81.0 (https://faust.grame.fr)
Compilation options: -a /Users/cucu/Documents/GitHub/faust/architecture/clap/clap-arch.cpp -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

//dummy clap architecture file
//this file will translate faust's mydsp c++ class into the clap plugin interface
//it should include plugin lifecycle, audio block processing calls, parameter registration and ui integration using buildUserInterface () and CLAP API
//core of the plugin backend

//includes for faust dsp and ui
#include <faust/dsp/dsp.h>
#include <faust/gui/MapUI.h>
#include <faust/gui/meta.h>

//include for cpp logging
#include <iostream>

//includes for the clap helpers glue
#include <clap/helpers/plugin.hh>
#include <clap/helpers/host-proxy.hh>
#include <clap/events.h>

//guarded MapUI subclass to prevent accidental param writes
struct GuardedUI : public MapUI {
    bool allowWrite = false;
    void setParamValue(const std::string& path, FAUSTFLOAT val) {
        if (!allowWrite) {
            std::abort(); //catch unintended writes early
        }
        MapUI::setParamValue(path, val);
    }

    void setParamValue(int index, FAUSTFLOAT val) {
        std::string addr = getParamAddress(index);

        if (!allowWrite) {
            return;
        }
        MapUI::setParamValue(addr, val);
    }

    void guardedSetByIndex(int index, FAUSTFLOAT val) {
        std::string addr = getParamAddress(index);

        if (!allowWrite) {
            return;
        }
        MapUI::setParamValue(addr, val);
    }
};


struct GuardedScope {
    GuardedUI& ui;
    const char* tag;

    GuardedScope(GuardedUI& ui, const char* src = "unknown") : ui(ui), tag(src) {
        ui.allowWrite = true;
    }

    ~GuardedScope() {
        ui.allowWrite = false;
    }
};

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

static float mydsp_faustpower2_f(float value) {
	return value * value;
}

class mydsp : public dsp {
	
 private:
	
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	int fSampleRate;
	float fConst0;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT fHbargraph0;
	int iVec0[2];
	float fRec1[2];
	float fRec2[2];
	int iRec3[2];
	int IOTA0;
	float fVec1[32];
	float fRec0[2];
	FAUSTFLOAT fVbargraph0;
	float fRec4[2];
	FAUSTFLOAT fVbargraph1;
	float fRec5[2];
	FAUSTFLOAT fVbargraph2;
	float fRec6[2];
	FAUSTFLOAT fVbargraph3;
	float fRec7[2];
	FAUSTFLOAT fVbargraph4;
	float fRec8[2];
	FAUSTFLOAT fVbargraph5;
	float fRec9[2];
	FAUSTFLOAT fVbargraph6;
	float fRec10[2];
	FAUSTFLOAT fVbargraph7;
	float fRec11[2];
	FAUSTFLOAT fVbargraph8;
	float fRec12[2];
	FAUSTFLOAT fVbargraph9;
	float fRec13[2];
	FAUSTFLOAT fVbargraph10;
	float fRec14[2];
	FAUSTFLOAT fVbargraph11;
	float fRec15[2];
	FAUSTFLOAT fVbargraph12;
	float fRec16[2];
	FAUSTFLOAT fVbargraph13;
	float fRec17[2];
	FAUSTFLOAT fVbargraph14;
	float fRec18[2];
	FAUSTFLOAT fVbargraph15;
	float fRec19[2];
	FAUSTFLOAT fVbargraph16;
	
 public:
	mydsp() {
	}
	
	void metadata(Meta* m) { 
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "1.2.0");
		m->declare("author", "JOS");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.21.0");
		m->declare("compile_options", "-a /Users/cucu/Documents/GitHub/faust/architecture/clap/clap-arch.cpp -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("demos.lib/fft_spectral_level_demo:author", "Julius O. Smith III");
		m->declare("demos.lib/fft_spectral_level_demo:licence", "MIT");
		m->declare("demos.lib/name", "Faust Demos Library");
		m->declare("demos.lib/version", "1.2.0");
		m->declare("filename", "FFT.dsp");
		m->declare("filters.lib/lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/nlf2:author", "Julius O. Smith III");
		m->declare("filters.lib/nlf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/nlf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "1.7.1");
		m->declare("license", "STK-4.3");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.8.1");
		m->declare("name", "FFT");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "1.6.0");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "1.6.0");
	}

	virtual int getNumInputs() {
		return 0;
	}
	virtual int getNumOutputs() {
		return 2;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = 1.0f / std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(5e+01f);
		fHslider1 = FAUSTFLOAT(1e+02f);
		fHslider2 = FAUSTFLOAT(0.1f);
		fHslider3 = FAUSTFLOAT(8.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec1[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec2[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			iRec3[l3] = 0;
		}
		IOTA0 = 0;
		for (int l4 = 0; l4 < 32; l4 = l4 + 1) {
			fVec1[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec0[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec4[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec5[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec6[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fRec7[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 2; l10 = l10 + 1) {
			fRec8[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 2; l11 = l11 + 1) {
			fRec9[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 2; l12 = l12 + 1) {
			fRec10[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 2; l13 = l13 + 1) {
			fRec11[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 2; l14 = l14 + 1) {
			fRec12[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 2; l15 = l15 + 1) {
			fRec13[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 2; l16 = l16 + 1) {
			fRec14[l16] = 0.0f;
		}
		for (int l17 = 0; l17 < 2; l17 = l17 + 1) {
			fRec15[l17] = 0.0f;
		}
		for (int l18 = 0; l18 < 2; l18 = l18 + 1) {
			fRec16[l18] = 0.0f;
		}
		for (int l19 = 0; l19 < 2; l19 = l19 + 1) {
			fRec17[l19] = 0.0f;
		}
		for (int l20 = 0; l20 < 2; l20 = l20 + 1) {
			fRec18[l20] = 0.0f;
		}
		for (int l21 = 0; l21 < 2; l21 = l21 + 1) {
			fRec19[l21] = 0.0f;
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
		return new mydsp();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("FFT");
		ui_interface->declare(0, "0", "");
		ui_interface->declare(0, "tooltip", "fft_spectral_level in Faust's analyzers.lib");
		ui_interface->openHorizontalBox("FFT SPECTRUM ANALYZER, 32 bands");
		ui_interface->declare(&fVbargraph0, "0", "");
		ui_interface->declare(&fVbargraph0, "tooltip", "FFT Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph0, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph0", &fVbargraph0, FAUSTFLOAT(-5e+01f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fVbargraph1, "1", "");
		ui_interface->declare(&fVbargraph1, "tooltip", "FFT Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph1, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph1", &fVbargraph1, FAUSTFLOAT(-5e+01f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fVbargraph2, "2", "");
		ui_interface->declare(&fVbargraph2, "tooltip", "FFT Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph2, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph2", &fVbargraph2, FAUSTFLOAT(-5e+01f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fVbargraph3, "3", "");
		ui_interface->declare(&fVbargraph3, "tooltip", "FFT Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph3, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph3", &fVbargraph3, FAUSTFLOAT(-5e+01f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fVbargraph4, "4", "");
		ui_interface->declare(&fVbargraph4, "tooltip", "FFT Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph4, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph4", &fVbargraph4, FAUSTFLOAT(-5e+01f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fVbargraph5, "5", "");
		ui_interface->declare(&fVbargraph5, "tooltip", "FFT Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph5, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph5", &fVbargraph5, FAUSTFLOAT(-5e+01f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fVbargraph6, "6", "");
		ui_interface->declare(&fVbargraph6, "tooltip", "FFT Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph6, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph6", &fVbargraph6, FAUSTFLOAT(-5e+01f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fVbargraph7, "7", "");
		ui_interface->declare(&fVbargraph7, "tooltip", "FFT Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph7, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph7", &fVbargraph7, FAUSTFLOAT(-5e+01f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fVbargraph8, "8", "");
		ui_interface->declare(&fVbargraph8, "tooltip", "FFT Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph8, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph8", &fVbargraph8, FAUSTFLOAT(-5e+01f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fVbargraph9, "9", "");
		ui_interface->declare(&fVbargraph9, "tooltip", "FFT Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph9, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph9", &fVbargraph9, FAUSTFLOAT(-5e+01f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fVbargraph10, "10", "");
		ui_interface->declare(&fVbargraph10, "tooltip", "FFT Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph10, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph10", &fVbargraph10, FAUSTFLOAT(-5e+01f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fVbargraph11, "11", "");
		ui_interface->declare(&fVbargraph11, "tooltip", "FFT Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph11, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph11", &fVbargraph11, FAUSTFLOAT(-5e+01f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fVbargraph12, "12", "");
		ui_interface->declare(&fVbargraph12, "tooltip", "FFT Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph12, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph12", &fVbargraph12, FAUSTFLOAT(-5e+01f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fVbargraph13, "13", "");
		ui_interface->declare(&fVbargraph13, "tooltip", "FFT Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph13, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph13", &fVbargraph13, FAUSTFLOAT(-5e+01f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fVbargraph14, "14", "");
		ui_interface->declare(&fVbargraph14, "tooltip", "FFT Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph14, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph14", &fVbargraph14, FAUSTFLOAT(-5e+01f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fVbargraph15, "15", "");
		ui_interface->declare(&fVbargraph15, "tooltip", "FFT Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph15, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph15", &fVbargraph15, FAUSTFLOAT(-5e+01f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fVbargraph16, "16", "");
		ui_interface->declare(&fVbargraph16, "tooltip", "FFT Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph16, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph16", &fVbargraph16, FAUSTFLOAT(-5e+01f), FAUSTFLOAT(1e+01f));
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("FFT SPECTRUM ANALYZER CONTROLS");
		ui_interface->declare(&fHslider1, "0", "");
		ui_interface->declare(&fHslider1, "scale", "log");
		ui_interface->declare(&fHslider1, "tooltip", "band-level averaging time in milliseconds");
		ui_interface->declare(&fHslider1, "unit", "ms");
		ui_interface->addHorizontalSlider("Level Averaging Time", &fHslider1, FAUSTFLOAT(1e+02f), FAUSTFLOAT(1.0f), FAUSTFLOAT(1e+04f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider0, "1", "");
		ui_interface->declare(&fHslider0, "tooltip", "Level offset in decibels");
		ui_interface->declare(&fHslider0, "unit", "dB");
		ui_interface->addHorizontalSlider("Level dB Offset", &fHslider0, FAUSTFLOAT(5e+01f), FAUSTFLOAT(-5e+01f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->declare(&fHslider3, "2", "");
		ui_interface->addHorizontalSlider("FFT Bin Number", &fHslider3, FAUSTFLOAT(8.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(16.0f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHbargraph0, "3", "");
		ui_interface->addHorizontalBargraph("Measured FFT Bin Number", &fHbargraph0, FAUSTFLOAT(0.0f), FAUSTFLOAT(16.0f));
		ui_interface->declare(&fHslider2, "4", "");
		ui_interface->addHorizontalSlider("Amplitude", &fHslider2, FAUSTFLOAT(0.1f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = float(fHslider0);
		float fSlow1 = 0.001f * float(fHslider1);
		int iSlow2 = std::fabs(fSlow1) < 1.1920929e-07f;
		float fSlow3 = ((iSlow2) ? 0.0f : std::exp(-(fConst0 / ((iSlow2) ? 1.0f : fSlow1))));
		float fSlow4 = 1.0f - fSlow3;
		float fSlow5 = float(fHslider2);
		int iSlow6 = int(float(fHslider3));
		fHbargraph0 = FAUSTFLOAT(float(iSlow6));
		int iSlow7 = iSlow6;
		int iSlow8 = iSlow7 == 0;
		int iSlow9 = iSlow7 == 16;
		float fSlow10 = 0.19634955f * float(iSlow7);
		float fSlow11 = std::sin(fSlow10);
		float fSlow12 = std::cos(fSlow10);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			iVec0[0] = 1;
			fRec1[0] = fSlow11 * fRec2[1] + fSlow12 * fRec1[1];
			fRec2[0] = float(1 - iVec0[1]) + fSlow12 * fRec2[1] - fSlow11 * fRec1[1];
			iRec3[0] = 1 - (iVec0[1] + iRec3[1]);
			float fTemp0 = fSlow5 * ((iSlow8) ? 1.0f : ((iSlow9) ? float(iRec3[0]) : 2.0f * fRec2[0]));
			fVec1[IOTA0 & 31] = fTemp0;
			float fTemp1 = fVec1[(IOTA0 - 31) & 31];
			float fTemp2 = fVec1[(IOTA0 - 15) & 31];
			float fTemp3 = fVec1[(IOTA0 - 23) & 31];
			float fTemp4 = fVec1[(IOTA0 - 7) & 31];
			float fTemp5 = fVec1[(IOTA0 - 27) & 31];
			float fTemp6 = fVec1[(IOTA0 - 11) & 31];
			float fTemp7 = fVec1[(IOTA0 - 19) & 31];
			float fTemp8 = fVec1[(IOTA0 - 3) & 31];
			float fTemp9 = fVec1[(IOTA0 - 29) & 31];
			float fTemp10 = fVec1[(IOTA0 - 13) & 31];
			float fTemp11 = fVec1[(IOTA0 - 21) & 31];
			float fTemp12 = fVec1[(IOTA0 - 5) & 31];
			float fTemp13 = fVec1[(IOTA0 - 25) & 31];
			float fTemp14 = fVec1[(IOTA0 - 9) & 31];
			float fTemp15 = fVec1[(IOTA0 - 17) & 31];
			float fTemp16 = fVec1[(IOTA0 - 1) & 31];
			float fTemp17 = fVec1[(IOTA0 - 30) & 31];
			float fTemp18 = fVec1[(IOTA0 - 14) & 31];
			float fTemp19 = fVec1[(IOTA0 - 22) & 31];
			float fTemp20 = fVec1[(IOTA0 - 6) & 31];
			float fTemp21 = fVec1[(IOTA0 - 26) & 31];
			float fTemp22 = fVec1[(IOTA0 - 10) & 31];
			float fTemp23 = fVec1[(IOTA0 - 18) & 31];
			float fTemp24 = fVec1[(IOTA0 - 2) & 31];
			float fTemp25 = fVec1[(IOTA0 - 28) & 31];
			float fTemp26 = fVec1[(IOTA0 - 12) & 31];
			float fTemp27 = fVec1[(IOTA0 - 20) & 31];
			float fTemp28 = fVec1[(IOTA0 - 4) & 31];
			float fTemp29 = fVec1[(IOTA0 - 24) & 31];
			float fTemp30 = fVec1[(IOTA0 - 8) & 31];
			float fTemp31 = fVec1[(IOTA0 - 16) & 31];
			float fTemp32 = fTemp0 + fTemp31;
			float fTemp33 = fTemp29 + fTemp30 + fTemp32;
			float fTemp34 = fTemp25 + fTemp26 + fTemp27 + fTemp28 + fTemp33;
			float fTemp35 = fTemp17 + fTemp18 + fTemp19 + fTemp20 + fTemp21 + fTemp22 + fTemp23 + fTemp24 + fTemp34;
			fRec0[0] = 1e+01f * fSlow4 * std::log10(std::max<float>(1.1920929e-07f, mydsp_faustpower2_f(std::fabs(fTemp1 + fTemp2 + fTemp3 + fTemp4 + fTemp5 + fTemp6 + fTemp7 + fTemp8 + fTemp9 + fTemp10 + fTemp11 + fTemp12 + fTemp13 + fTemp14 + fTemp15 + fTemp16 + fTemp35)))) + fSlow3 * fRec0[1];
			fVbargraph0 = FAUSTFLOAT(fSlow0 + fRec0[0]);
			float fTemp36 = fTemp28 - fTemp27;
			float fTemp37 = fTemp0 + 0.70710677f * fTemp36;
			float fTemp38 = fTemp20 - fTemp19;
			float fTemp39 = fTemp24 + 0.70710677f * fTemp38;
			float fTemp40 = fTemp18 - fTemp17;
			float fTemp41 = fTemp23 + 0.70710677f * fTemp40;
			float fTemp42 = fTemp39 - fTemp41;
			float fTemp43 = fTemp12 - fTemp11;
			float fTemp44 = fTemp16 + 0.70710677f * fTemp43;
			float fTemp45 = fTemp4 - fTemp3;
			float fTemp46 = fTemp8 + 0.70710677f * fTemp45;
			float fTemp47 = fTemp2 - fTemp1;
			float fTemp48 = fTemp7 + 0.70710677f * fTemp47;
			float fTemp49 = fTemp46 - fTemp48;
			float fTemp50 = fTemp44 + 0.9238795f * fTemp49;
			float fTemp51 = fTemp10 - fTemp9;
			float fTemp52 = fTemp15 + 0.70710677f * fTemp51;
			float fTemp53 = fTemp3 - fTemp4;
			float fTemp54 = 0.70710677f * fTemp53;
			float fTemp55 = fTemp1 - fTemp2;
			float fTemp56 = 0.70710677f * fTemp55;
			float fTemp57 = fTemp54 + fTemp5 + fTemp56;
			float fTemp58 = fTemp6 - fTemp57;
			float fTemp59 = fTemp52 + 0.38268343f * fTemp58;
			float fTemp60 = fTemp26 - fTemp25;
			float fTemp61 = fTemp31 + 0.70710677f * fTemp60;
			float fTemp62 = fTemp19 - fTemp20;
			float fTemp63 = 0.70710677f * fTemp62;
			float fTemp64 = fTemp17 - fTemp18;
			float fTemp65 = 0.70710677f * fTemp64;
			float fTemp66 = fTemp63 + fTemp21 + fTemp65;
			float fTemp67 = fTemp22 - fTemp66;
			float fTemp68 = fTemp48 - fTemp46;
			float fTemp69 = fTemp11 - fTemp12;
			float fTemp70 = 0.70710677f * fTemp69;
			float fTemp71 = fTemp9 - fTemp10;
			float fTemp72 = 0.70710677f * fTemp71;
			float fTemp73 = fTemp13 + fTemp72;
			float fTemp74 = fTemp57 - fTemp6;
			float fTemp75 = 0.38268343f * fTemp68 + fTemp70 + fTemp73 + 0.9238795f * fTemp74;
			float fTemp76 = fTemp41 - fTemp39;
			float fTemp77 = fTemp27 - fTemp28;
			float fTemp78 = 0.70710677f * fTemp77;
			float fTemp79 = fTemp25 - fTemp26;
			float fTemp80 = 0.70710677f * fTemp79;
			float fTemp81 = fTemp29 + fTemp80;
			float fTemp82 = fTemp66 - fTemp22;
			fRec4[0] = 1e+01f * fSlow4 * std::log10(std::max<float>(1.1920929e-07f, mydsp_faustpower2_f(std::fabs(fTemp37 + 0.9238795f * fTemp42 + 0.98078525f * (fTemp50 - fTemp59) - (fTemp61 + 0.38268343f * fTemp67 + 0.19509032f * (fTemp14 - fTemp75)))) + mydsp_faustpower2_f(std::fabs(0.19509032f * (fTemp59 - fTemp50) + 0.38268343f * fTemp76 + fTemp78 + fTemp81 + 0.9238795f * fTemp82 + 0.98078525f * (fTemp75 - fTemp14) - fTemp30)))) + fSlow3 * fRec4[1];
			fVbargraph1 = FAUSTFLOAT(fSlow0 + fRec4[0]);
			float fTemp83 = fTemp24 + fTemp23;
			float fTemp84 = fTemp22 + fTemp21;
			float fTemp85 = fTemp83 - fTemp84;
			float fTemp86 = fTemp16 + fTemp15;
			float fTemp87 = fTemp8 + fTemp7;
			float fTemp88 = fTemp6 + fTemp5;
			float fTemp89 = fTemp87 - fTemp88;
			float fTemp90 = fTemp86 + 0.70710677f * fTemp89;
			float fTemp91 = fTemp14 + fTemp13;
			float fTemp92 = fTemp4 + fTemp3;
			float fTemp93 = fTemp2 + fTemp1;
			float fTemp94 = fTemp92 - fTemp93;
			float fTemp95 = fTemp91 + 0.70710677f * fTemp94;
			float fTemp96 = fTemp30 + fTemp29;
			float fTemp97 = fTemp20 + fTemp19;
			float fTemp98 = fTemp18 + fTemp17;
			float fTemp99 = fTemp97 - fTemp98;
			float fTemp100 = fTemp12 + fTemp11;
			float fTemp101 = fTemp88 - fTemp87;
			float fTemp102 = 0.70710677f * fTemp101;
			float fTemp103 = fTemp10 + fTemp9;
			float fTemp104 = fTemp93 - fTemp92;
			float fTemp105 = 0.70710677f * fTemp104;
			float fTemp106 = fTemp102 + fTemp103 + fTemp105;
			float fTemp107 = fTemp84 - fTemp83;
			float fTemp108 = 0.70710677f * fTemp107;
			float fTemp109 = fTemp26 + fTemp25;
			float fTemp110 = fTemp98 - fTemp97;
			float fTemp111 = 0.70710677f * fTemp110;
			float fTemp112 = fTemp28 + fTemp27;
			fRec5[0] = 1e+01f * fSlow4 * std::log10(std::max<float>(1.1920929e-07f, mydsp_faustpower2_f(std::fabs(fTemp32 + 0.70710677f * fTemp85 + 0.9238795f * (fTemp90 - fTemp95) - (fTemp96 + 0.70710677f * fTemp99 + 0.38268343f * (fTemp100 - fTemp106)))) + mydsp_faustpower2_f(std::fabs(0.38268343f * (fTemp95 - fTemp90) + fTemp108 + fTemp109 + fTemp111 + 0.9238795f * (fTemp106 - fTemp100) - fTemp112)))) + fSlow3 * fRec5[1];
			fVbargraph2 = FAUSTFLOAT(fSlow0 + fRec5[0]);
			float fTemp113 = fTemp0 + fTemp78;
			float fTemp114 = fTemp24 + fTemp63;
			float fTemp115 = fTemp23 + fTemp65;
			float fTemp116 = fTemp114 - fTemp115;
			float fTemp117 = fTemp16 + fTemp70;
			float fTemp118 = fTemp8 + fTemp54;
			float fTemp119 = fTemp7 + fTemp56;
			float fTemp120 = fTemp118 - fTemp119;
			float fTemp121 = fTemp117 + 0.38268343f * fTemp120;
			float fTemp122 = fTemp15 + fTemp72;
			float fTemp123 = 0.70710677f * fTemp55;
			float fTemp124 = 0.70710677f * fTemp53 + fTemp6 + fTemp123;
			float fTemp125 = fTemp5 - fTemp124;
			float fTemp126 = fTemp122 + 0.9238795f * fTemp125;
			float fTemp127 = fTemp31 + fTemp80;
			float fTemp128 = 0.70710677f * fTemp64;
			float fTemp129 = 0.70710677f * fTemp62 + fTemp22 + fTemp128;
			float fTemp130 = fTemp21 - fTemp129;
			float fTemp131 = fTemp119 - fTemp118;
			float fTemp132 = 0.70710677f * fTemp71;
			float fTemp133 = 0.70710677f * fTemp69 + fTemp14 + fTemp132;
			float fTemp134 = fTemp124 - fTemp5;
			float fTemp135 = 0.9238795f * fTemp131 + fTemp133 + 0.38268343f * fTemp134;
			float fTemp136 = fTemp115 - fTemp114;
			float fTemp137 = 0.70710677f * fTemp79;
			float fTemp138 = 0.70710677f * fTemp77 + fTemp30 + fTemp137;
			float fTemp139 = fTemp129 - fTemp21;
			fRec6[0] = 1e+01f * fSlow4 * std::log10(std::max<float>(1.1920929e-07f, mydsp_faustpower2_f(std::fabs(fTemp113 + 0.38268343f * fTemp116 + 0.8314696f * (fTemp121 - fTemp126) - (fTemp127 + 0.9238795f * fTemp130 + 0.55557024f * (fTemp13 - fTemp135)))) + mydsp_faustpower2_f(std::fabs(0.55557024f * (fTemp126 - fTemp121) + 0.9238795f * fTemp136 + fTemp138 + 0.38268343f * fTemp139 + 0.8314696f * (fTemp135 - fTemp13) - fTemp29)))) + fSlow3 * fRec6[1];
			fVbargraph3 = FAUSTFLOAT(fSlow0 + fRec6[0]);
			float fTemp140 = fTemp13 + fTemp14 + fTemp86;
			float fTemp141 = fTemp9 + fTemp10 + fTemp100;
			float fTemp142 = fTemp25 + fTemp26 + fTemp112;
			float fTemp143 = fTemp5 + fTemp6 + fTemp87;
			float fTemp144 = fTemp1 + fTemp2 + fTemp92;
			float fTemp145 = fTemp141 - fTemp140;
			float fTemp146 = 0.70710677f * fTemp145;
			float fTemp147 = fTemp17 + fTemp18 + fTemp97;
			float fTemp148 = fTemp144 - fTemp143;
			float fTemp149 = 0.70710677f * fTemp148;
			float fTemp150 = fTemp21 + fTemp22 + fTemp83;
			fRec7[0] = 1e+01f * fSlow4 * std::log10(std::max<float>(1.1920929e-07f, mydsp_faustpower2_f(std::fabs(fTemp33 + 0.70710677f * (fTemp140 - fTemp141) - (fTemp142 + 0.70710677f * (fTemp143 - fTemp144)))) + mydsp_faustpower2_f(std::fabs(fTemp146 + fTemp147 + fTemp149 - fTemp150)))) + fSlow3 * fRec7[1];
			fVbargraph4 = FAUSTFLOAT(fSlow0 + fRec7[0]);
			float fTemp151 = fTemp0 + 0.70710677f * fTemp77;
			float fTemp152 = fTemp23 + fTemp128;
			float fTemp153 = fTemp24 + 0.70710677f * fTemp62;
			float fTemp154 = fTemp152 - fTemp153;
			float fTemp155 = fTemp16 + 0.70710677f * fTemp69;
			float fTemp156 = fTemp7 + fTemp123;
			float fTemp157 = fTemp8 + 0.70710677f * fTemp53;
			float fTemp158 = fTemp156 - fTemp157;
			float fTemp159 = fTemp155 + 0.38268343f * fTemp158;
			float fTemp160 = fTemp15 + fTemp132;
			float fTemp161 = 0.70710677f * fTemp47;
			float fTemp162 = fTemp161 + fTemp5 + 0.70710677f * fTemp45;
			float fTemp163 = fTemp6 - fTemp162;
			float fTemp164 = fTemp160 + 0.9238795f * fTemp163;
			float fTemp165 = fTemp31 + fTemp137;
			float fTemp166 = 0.70710677f * fTemp40;
			float fTemp167 = fTemp166 + fTemp21 + 0.70710677f * fTemp38;
			float fTemp168 = fTemp22 - fTemp167;
			float fTemp169 = 0.70710677f * fTemp51;
			float fTemp170 = fTemp169 + fTemp13 + 0.70710677f * fTemp43;
			float fTemp171 = 0.38268343f * fTemp163 + fTemp170 + 0.9238795f * fTemp158;
			float fTemp172 = 0.70710677f * fTemp60;
			float fTemp173 = fTemp172 + fTemp29 + 0.70710677f * fTemp36;
			fRec8[0] = 1e+01f * fSlow4 * std::log10(std::max<float>(1.1920929e-07f, mydsp_faustpower2_f(std::fabs(fTemp151 + 0.38268343f * fTemp154 + 0.55557024f * (fTemp159 - fTemp164) - (fTemp165 + 0.9238795f * fTemp168 + 0.8314696f * (fTemp14 - fTemp171)))) + mydsp_faustpower2_f(std::fabs(0.8314696f * (fTemp164 - fTemp159) + 0.38268343f * fTemp168 + fTemp173 + 0.9238795f * fTemp154 + 0.55557024f * (fTemp171 - fTemp14) - fTemp30)))) + fSlow3 * fRec8[1];
			fVbargraph5 = FAUSTFLOAT(fSlow0 + fRec8[0]);
			float fTemp174 = fTemp86 + fTemp102;
			float fTemp175 = fTemp91 + fTemp105;
			float fTemp176 = 0.70710677f * fTemp104;
			float fTemp177 = 0.70710677f * fTemp101 + fTemp100 + fTemp176;
			float fTemp178 = 0.70710677f * fTemp110;
			fRec9[0] = 1e+01f * fSlow4 * std::log10(std::max<float>(1.1920929e-07f, mydsp_faustpower2_f(std::fabs(fTemp32 + fTemp108 + 0.38268343f * (fTemp174 - fTemp175) - (fTemp96 + fTemp111 + 0.9238795f * (fTemp103 - fTemp177)))) + mydsp_faustpower2_f(std::fabs(0.9238795f * (fTemp175 - fTemp174) + 0.70710677f * fTemp107 + fTemp112 + fTemp178 + 0.38268343f * (fTemp177 - fTemp103) - fTemp109)))) + fSlow3 * fRec9[1];
			fVbargraph6 = FAUSTFLOAT(fSlow0 + fRec9[0]);
			float fTemp179 = fTemp0 + 0.70710677f * fTemp36;
			float fTemp180 = fTemp23 + fTemp166;
			float fTemp181 = fTemp24 + 0.70710677f * fTemp38;
			float fTemp182 = fTemp180 - fTemp181;
			float fTemp183 = fTemp16 + 0.70710677f * fTemp43;
			float fTemp184 = fTemp7 + fTemp161;
			float fTemp185 = fTemp8 + 0.70710677f * fTemp45;
			float fTemp186 = fTemp184 - fTemp185;
			float fTemp187 = fTemp183 + 0.9238795f * fTemp186;
			float fTemp188 = fTemp15 + fTemp169;
			float fTemp189 = 0.70710677f * fTemp47 + fTemp6 + 0.70710677f * fTemp45;
			float fTemp190 = fTemp5 - fTemp189;
			float fTemp191 = fTemp188 + 0.38268343f * fTemp190;
			float fTemp192 = fTemp31 + fTemp172;
			float fTemp193 = 0.70710677f * fTemp40 + fTemp22 + 0.70710677f * fTemp38;
			float fTemp194 = fTemp21 - fTemp193;
			float fTemp195 = 0.70710677f * fTemp51 + fTemp14 + 0.70710677f * fTemp43;
			float fTemp196 = 0.9238795f * fTemp190 + fTemp195 + 0.38268343f * fTemp186;
			float fTemp197 = 0.70710677f * fTemp60 + fTemp30 + 0.70710677f * fTemp36;
			fRec10[0] = 1e+01f * fSlow4 * std::log10(std::max<float>(1.1920929e-07f, mydsp_faustpower2_f(std::fabs(fTemp179 + 0.9238795f * fTemp182 + 0.19509032f * (fTemp187 - fTemp191) - (fTemp192 + 0.38268343f * fTemp194 + 0.98078525f * (fTemp13 - fTemp196)))) + mydsp_faustpower2_f(std::fabs(0.98078525f * (fTemp191 - fTemp187) + 0.9238795f * fTemp194 + fTemp197 + 0.38268343f * fTemp182 + 0.19509032f * (fTemp196 - fTemp13) - fTemp29)))) + fSlow3 * fRec10[1];
			fVbargraph7 = FAUSTFLOAT(fSlow0 + fRec10[0]);
			float fTemp198 = fTemp9 + fTemp10 + fTemp11 + fTemp12 + fTemp140;
			fRec11[0] = 1e+01f * fSlow4 * std::log10(std::max<float>(1.1920929e-07f, mydsp_faustpower2_f(std::fabs(fTemp34 - (fTemp17 + fTemp18 + fTemp19 + fTemp20 + fTemp150))) + mydsp_faustpower2_f(std::fabs(fTemp1 + fTemp2 + fTemp3 + fTemp4 + fTemp143 - fTemp198)))) + fSlow3 * fRec11[1];
			fVbargraph8 = FAUSTFLOAT(fSlow0 + fRec11[0]);
			float fTemp199 = fTemp52 + 0.38268343f * fTemp74 - (fTemp44 + 0.9238795f * fTemp68);
			float fTemp200 = fTemp14 - (fTemp70 + 0.9238795f * fTemp58 + fTemp73 + 0.38268343f * fTemp49);
			fRec12[0] = 1e+01f * fSlow4 * std::log10(std::max<float>(1.1920929e-07f, mydsp_faustpower2_f(std::fabs(fTemp37 + 0.9238795f * fTemp76 + 0.19509032f * fTemp199 - (fTemp61 + 0.38268343f * fTemp82 + 0.98078525f * fTemp200))) + mydsp_faustpower2_f(std::fabs(0.19509032f * fTemp200 + fTemp78 + 0.9238795f * fTemp67 + fTemp81 + 0.38268343f * fTemp42 + 0.98078525f * fTemp199 - fTemp30)))) + fSlow3 * fRec12[1];
			fVbargraph9 = FAUSTFLOAT(fSlow0 + fRec12[0]);
			float fTemp201 = fTemp91 + fTemp176 - (fTemp86 + 0.70710677f * fTemp101);
			float fTemp202 = 0.70710677f * fTemp94;
			float fTemp203 = fTemp100 - (fTemp202 + fTemp103 + 0.70710677f * fTemp89);
			float fTemp204 = 0.70710677f * fTemp99;
			fRec13[0] = 1e+01f * fSlow4 * std::log10(std::max<float>(1.1920929e-07f, mydsp_faustpower2_f(std::fabs(fTemp32 + 0.70710677f * fTemp107 + 0.38268343f * fTemp201 - (fTemp96 + fTemp178 + 0.9238795f * fTemp203))) + mydsp_faustpower2_f(std::fabs(0.38268343f * fTemp203 + fTemp204 + fTemp109 + 0.70710677f * fTemp85 + 0.9238795f * fTemp201 - fTemp112)))) + fSlow3 * fRec13[1];
			fVbargraph10 = FAUSTFLOAT(fSlow0 + fRec13[0]);
			float fTemp205 = fTemp122 + 0.9238795f * fTemp134 - (fTemp117 + 0.38268343f * fTemp131);
			float fTemp206 = fTemp13 - (0.38268343f * fTemp125 + fTemp133 + 0.9238795f * fTemp120);
			fRec14[0] = 1e+01f * fSlow4 * std::log10(std::max<float>(1.1920929e-07f, mydsp_faustpower2_f(std::fabs(fTemp113 + 0.38268343f * fTemp136 + 0.55557024f * fTemp205 - (fTemp127 + 0.9238795f * fTemp139 + 0.8314696f * fTemp206))) + mydsp_faustpower2_f(std::fabs(0.55557024f * fTemp206 + 0.38268343f * fTemp130 + fTemp138 + 0.9238795f * fTemp116 + 0.8314696f * fTemp205 - fTemp29)))) + fSlow3 * fRec14[1];
			fVbargraph11 = FAUSTFLOAT(fSlow0 + fRec14[0]);
			fRec15[0] = 1e+01f * fSlow4 * std::log10(std::max<float>(1.1920929e-07f, mydsp_faustpower2_f(std::fabs(fTemp33 + fTemp146 - (fTemp142 + fTemp149))) + mydsp_faustpower2_f(std::fabs(0.70710677f * fTemp145 + fTemp150 + 0.70710677f * fTemp148 - fTemp147)))) + fSlow3 * fRec15[1];
			fVbargraph12 = FAUSTFLOAT(fSlow0 + fRec15[0]);
			float fTemp207 = fTemp153 - fTemp152;
			float fTemp208 = fTemp162 - fTemp6;
			float fTemp209 = fTemp157 - fTemp156;
			float fTemp210 = fTemp160 + 0.9238795f * fTemp208 - (fTemp155 + 0.38268343f * fTemp209);
			float fTemp211 = fTemp167 - fTemp22;
			float fTemp212 = fTemp14 - (0.38268343f * fTemp208 + fTemp170 + 0.9238795f * fTemp209);
			fRec16[0] = 1e+01f * fSlow4 * std::log10(std::max<float>(1.1920929e-07f, mydsp_faustpower2_f(std::fabs(fTemp151 + 0.38268343f * fTemp207 + 0.8314696f * fTemp210 - (fTemp165 + 0.9238795f * fTemp211 + 0.55557024f * fTemp212))) + mydsp_faustpower2_f(std::fabs(0.8314696f * fTemp212 + 0.38268343f * fTemp211 + fTemp173 + 0.9238795f * fTemp207 + 0.55557024f * fTemp210 - fTemp30)))) + fSlow3 * fRec16[1];
			fVbargraph13 = FAUSTFLOAT(fSlow0 + fRec16[0]);
			float fTemp213 = fTemp91 + fTemp202 - (fTemp86 + 0.70710677f * fTemp89);
			float fTemp214 = fTemp103 - (0.70710677f * fTemp94 + fTemp100 + 0.70710677f * fTemp89);
			fRec17[0] = 1e+01f * fSlow4 * std::log10(std::max<float>(1.1920929e-07f, mydsp_faustpower2_f(std::fabs(fTemp32 + 0.70710677f * fTemp85 + 0.9238795f * fTemp213 - (fTemp96 + fTemp204 + 0.38268343f * fTemp214))) + mydsp_faustpower2_f(std::fabs(0.9238795f * fTemp214 + 0.70710677f * fTemp99 + fTemp112 + 0.70710677f * fTemp85 + 0.38268343f * fTemp213 - fTemp109)))) + fSlow3 * fRec17[1];
			fVbargraph14 = FAUSTFLOAT(fSlow0 + fRec17[0]);
			float fTemp215 = fTemp181 - fTemp180;
			float fTemp216 = fTemp189 - fTemp5;
			float fTemp217 = fTemp185 - fTemp184;
			float fTemp218 = fTemp188 + 0.38268343f * fTemp216 - (fTemp183 + 0.9238795f * fTemp217);
			float fTemp219 = fTemp193 - fTemp21;
			float fTemp220 = fTemp13 - (0.9238795f * fTemp216 + fTemp195 + 0.38268343f * fTemp217);
			fRec18[0] = 1e+01f * fSlow4 * std::log10(std::max<float>(1.1920929e-07f, mydsp_faustpower2_f(std::fabs(fTemp179 + 0.9238795f * fTemp215 + 0.98078525f * fTemp218 - (fTemp192 + 0.38268343f * fTemp219 + 0.19509032f * fTemp220))) + mydsp_faustpower2_f(std::fabs(0.98078525f * fTemp220 + 0.9238795f * fTemp219 + fTemp197 + 0.38268343f * fTemp215 + 0.19509032f * fTemp218 - fTemp29)))) + fSlow3 * fRec18[1];
			fVbargraph15 = FAUSTFLOAT(fSlow0 + fRec18[0]);
			fRec19[0] = 1e+01f * fSlow4 * std::log10(std::max<float>(1.1920929e-07f, mydsp_faustpower2_f(std::fabs(fTemp35 - (fTemp1 + fTemp2 + fTemp3 + fTemp4 + fTemp5 + fTemp6 + fTemp7 + fTemp8 + fTemp198))))) + fSlow3 * fRec19[1];
			fVbargraph16 = FAUSTFLOAT(fSlow0 + fRec19[0]);
			float fTemp221 = fTemp0;
			output0[i0] = FAUSTFLOAT(fTemp221);
			output1[i0] = FAUSTFLOAT(fTemp221);
			iVec0[1] = iVec0[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			iRec3[1] = iRec3[0];
			IOTA0 = IOTA0 + 1;
			fRec0[1] = fRec0[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec7[1] = fRec7[0];
			fRec8[1] = fRec8[0];
			fRec9[1] = fRec9[0];
			fRec10[1] = fRec10[0];
			fRec11[1] = fRec11[0];
			fRec12[1] = fRec12[0];
			fRec13[1] = fRec13[0];
			fRec14[1] = fRec14[0];
			fRec15[1] = fRec15[0];
			fRec16[1] = fRec16[0];
			fRec17[1] = fRec17[0];
			fRec18[1] = fRec18[0];
			fRec19[1] = fRec19[0];
		}
	}

};

using Base = clap::helpers::Plugin<
    clap::helpers::MisbehaviourHandler::Terminate,
    clap::helpers::CheckingLevel::Minimal>;

static const clap_plugin_descriptor_t gain_desc = {
    .clap_version = CLAP_VERSION_INIT,
    .id = "org.faust.gain",
    .name = "Faust Gain",
    .vendor = "faust",
    .url = "https://faust.grame.fr",
    .manual_url = "",
    .support_url = "",
    .version = "1.0.0",
    .description = "Simple gain plugin generated from Faust",
    .features = (const char*[]) { CLAP_PLUGIN_FEATURE_AUDIO_EFFECT, nullptr }
};

class GainPlugin final : public Base {
public:
    int fNumInputs = 0;
    int fNumOutputs = 0;
    mydsp fDSP;
    GuardedUI fUI;
    std::vector<std::string> fParamAddresses;
    std::vector<float> fExpectedValues;
    bool fHasFlushed = false;

    GainPlugin(const clap_plugin_descriptor_t* desc, const clap_host_t* host)
    : Base(desc, host) {}

    bool init() noexcept override {
        fDSP.buildUserInterface(&fUI);
        fParamAddresses.clear();
        for (int i = 0; i < fUI.getParamsCount(); ++i) {
            auto shortname = fUI.getParamShortname(i);
            fParamAddresses.push_back(shortname);
            float actual = fUI.getParamValue(shortname);
            fExpectedValues.push_back(actual);
        }
        return true;
    }

    bool startProcessing() noexcept override {
        return Base::startProcessing(); //set status to processing
    }

    void stopProcessing() noexcept override {
        Base::stopProcessing(); //resets status to activated
    }

    bool activate(double sampleRate, uint32_t, uint32_t) noexcept override {
        fDSP.init(sampleRate);
        fNumInputs = fDSP.getNumInputs();
        fNumOutputs = fDSP.getNumOutputs();
        std::cerr << "[activate] Sample rate: " << sampleRate << std::endl;
        std::cerr << "[activate] Input channels: " << fNumInputs << ", Output channels: " << fNumOutputs << std::endl;
        return true;
    }


    bool applyParamEventIfValid(const clap_event_header_t* hdr) {
        if (hdr->space_id != CLAP_CORE_EVENT_SPACE_ID) {
            return false;
        }

        if (hdr->type != CLAP_EVENT_PARAM_VALUE) return false;

        const auto* evParam = reinterpret_cast<const clap_event_param_value_t*>(hdr);
        if (evParam->param_id >= fParamAddresses.size()) return false;

        GuardedScope guard(fUI, "applyParamEventIfValid");
        fUI.setParamValue(fParamAddresses[evParam->param_id], evParam->value);
        fExpectedValues[evParam->param_id] = evParam->value;

        return true;
    }



    clap_process_status process(const clap_process_t* process) noexcept override {
        if (!process || process->audio_inputs_count < 1 || process->audio_outputs_count < 1)
            return CLAP_PROCESS_ERROR;

        const auto& inBuffer  = process->audio_inputs[0];
        const auto& outBuffer = process->audio_outputs[0];

        //skip processing gracefully if no audio channels are connected
        if (inBuffer.channel_count == 0 || outBuffer.channel_count == 0)
            return CLAP_PROCESS_CONTINUE;

        if (inBuffer.channel_count < fNumInputs ||
            outBuffer.channel_count < fNumOutputs) {
            std::cerr << "[error] Channel count mismatch: in="
                      << inBuffer.channel_count << ", expected="
                      << fNumInputs << " / out=" << outBuffer.channel_count
                      << ", expected=" << fNumOutputs << "\n";
            return CLAP_PROCESS_ERROR;
            }

        //apply param events
        if (auto events = process->in_events) {
            for (uint32_t i = 0, N = events->size(events); i < N; ++i) {
                applyParamEventIfValid(events->get(events, i));
            }
        }

        //prepare pointers
        FAUSTFLOAT* inputs[fNumInputs];
        FAUSTFLOAT* outputs[fNumOutputs];
        for (int i = 0; i < fNumInputs; ++i)
            inputs[i] = inBuffer.data32[i];
        for (int i = 0; i < fNumOutputs; ++i)
            outputs[i] = outBuffer.data32[i];

        //process audio
        GuardedScope guard(fUI, "full-buffer");
        fDSP.compute(process->frames_count, inputs, outputs);

        return CLAP_PROCESS_CONTINUE;
    }


    bool implementsParams() const noexcept override { return true; }
    uint32_t paramsCount() const noexcept override { return static_cast<uint32_t>(fParamAddresses.size()); }

    bool implementsAudioPorts() const noexcept override { return true; }
    uint32_t audioPortsCount(bool isInput) const noexcept override {
        return 1; //still 1 port, but could change if faust generates multiple ports
    }
    bool audioPortsInfo(uint32_t index, bool isInput, clap_audio_port_info_t* info) const noexcept override {
        if (index != 0) return false;
        std::memset(info, 0, sizeof(*info));
        info->id = index;
        snprintf(info->name, sizeof(info->name), "%s", isInput ? "Input" : "Output");
        info->channel_count = isInput ? fNumInputs : fNumOutputs;
        info->flags = CLAP_AUDIO_PORT_IS_MAIN;
        info->port_type = nullptr;
        return true;
    }

    bool paramsInfo(uint32_t index, clap_param_info_t* info) const noexcept override {
        if (index >= fParamAddresses.size()) return false;
        std::memset(info, 0, sizeof(*info));
        info->id = index;
        const char* addr = fParamAddresses[index].c_str();
        if (addr[0] == '/') addr += 1;
        snprintf(info->name, sizeof(info->name), "%s", addr);
        info->min_value = 0.f;
        info->max_value = 1.f;
        info->default_value = 0.5f;
        info->flags = CLAP_PARAM_IS_AUTOMATABLE;
        return true;
    }

    bool paramsValue(clap_id id, double* value) noexcept override {
        if (id >= fExpectedValues.size()) return false;
        *value = fExpectedValues[id];
        return true;
    }

    bool paramsTextToValue(clap_id, const char*, double*) noexcept override { return false; }
    bool paramsValueToText(clap_id, double, char*, uint32_t) noexcept override { return false; }

    void paramsFlush(const clap_input_events_t* in, const clap_output_events_t*) noexcept override {
        if (!in) return;
        fHasFlushed = true;

        for (uint32_t i = 0; i < in->size(in); ++i) {
            const clap_event_header_t* hdr = in->get(in, i);
            if (!applyParamEventIfValid(hdr)) {
            }
        }
    }
    using Base::clapPlugin;
    static const clap_plugin_t* create(const clap_host_t* host) {
        return (new GainPlugin(&gain_desc, host))->clapPlugin();
    }
};
static uint32_t plugin_count(const clap_plugin_factory_t*) { return 1; }
static const clap_plugin_descriptor_t* plugin_desc(const clap_plugin_factory_t*, uint32_t index) {
    return (index == 0) ? &gain_desc : nullptr;
}
static const clap_plugin_t* plugin_create(const clap_plugin_factory_t*, const clap_host_t* host, const char* plugin_id) {
    if (std::strcmp(plugin_id, gain_desc.id) == 0) {
        return GainPlugin::create(host);
    }
    return nullptr;
}
static const clap_plugin_factory_t gain_factory = {
    .get_plugin_count = plugin_count,
    .get_plugin_descriptor = plugin_desc,
    .create_plugin = plugin_create
};
static bool entry_init(const char* path) { return true; }
static void entry_deinit() {}

extern "C" {
CLAP_EXPORT const void* clap_get_factory(const char* factory_id) {
    if (std::strcmp(factory_id, CLAP_PLUGIN_FACTORY_ID) == 0)
        return &gain_factory;
    return nullptr;
}
CLAP_EXPORT const clap_plugin_entry_t clap_entry = {
    CLAP_VERSION_INIT,
    entry_init,
    entry_deinit,
    clap_get_factory
};
}

#endif
