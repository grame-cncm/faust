/* ------------------------------------------------------------
author: "JOS, revised by RM"
name: "sawtoothLab"
version: "0.0"
Code generated with Faust 2.81.0 (https://faust.grame.fr)
Compilation options: -a /Users/cucu/Documents/GitHub/faust/architecture/clap/clap-arch.cpp -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

// Created by Cucu on 02/06/2025.

// this file implements a CLAP plugin backend by wrapping Faust's mydsp class.
// it acts as a bridge between Faust-generated DSP code and the CLAP plugin API.

// faust DSP and UI headers
#include <faust/dsp/dsp.h>
#include <faust/dsp/poly-dsp.h>
#include <faust/gui/MapUI.h>
#include <faust/gui/meta.h>
#include <faust/midi/midi.h> // faust midi types
#include <faust/gui/UI.h>
#include <faust/gui/GUI.h>

// cpp logging
#include <iostream>

// CLAP helpers and API headers
#include <clap/helpers/plugin.hh>
#include <clap/helpers/host-proxy.hh>
#include <clap/events.h>
#include <clap/ext/note-ports.h> // CLAP note port extension

// include user Faust-generated class placeholder
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
static float mydsp_faustpower3_f(float value) {
	return value * value * value;
}

class mydsp : public dsp {
	
 private:
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fVslider0;
	float fConst2;
	int iVec0[4];
	float fRec0[2];
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT fEntry0;
	float fConst3;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fVslider2;
	float fRec2[2];
	float fRec1[2];
	float fConst4;
	float fVec1[2];
	float fConst5;
	float fVec2[2];
	float fVec3[2];
	float fConst6;
	float fVec4[2];
	float fVec5[2];
	float fVec6[2];
	FAUSTFLOAT fVslider3;
	float fRec3[2];
	float fVec7[2];
	float fVec8[2];
	float fVec9[2];
	float fVec10[2];
	float fVec11[2];
	float fVec12[2];
	FAUSTFLOAT fVslider4;
	float fRec4[2];
	float fVec13[2];
	float fVec14[2];
	float fVec15[2];
	float fVec16[2];
	float fVec17[2];
	float fVec18[2];
	FAUSTFLOAT fCheckbox2;
	int iRec5[2];
	float fRec6[4];
	
 public:
	mydsp() {
	}
	
	void metadata(Meta* m) { 
		m->declare("author", "JOS, revised by RM");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.21.0");
		m->declare("compile_options", "-a /Users/cucu/Documents/GitHub/faust/architecture/clap/clap-arch.cpp -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("demos.lib/name", "Faust Demos Library");
		m->declare("demos.lib/sawtooth_demo:author", "Julius O. Smith III");
		m->declare("demos.lib/sawtooth_demo:licence", "MIT");
		m->declare("demos.lib/version", "1.2.0");
		m->declare("description", "An application demonstrating the different sawtooth oscillators of Faust.");
		m->declare("filename", "sawtoothLab.dsp");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "1.7.1");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.8.1");
		m->declare("name", "sawtoothLab");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "1.4.1");
		m->declare("oscillators.lib/lf_sawpos:author", "Bart Brouns, revised by Stéphane Letz");
		m->declare("oscillators.lib/lf_sawpos:licence", "STK-4.3");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/sawN:author", "Julius O. Smith III");
		m->declare("oscillators.lib/sawN:license", "STK-4.3");
		m->declare("oscillators.lib/version", "1.6.0");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "1.6.0");
		m->declare("version", "0.0");
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
		fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = 44.1f / fConst0;
		fConst2 = 1.0f - fConst1;
		fConst3 = 1.0f / fConst0;
		fConst4 = 0.25f * fConst0;
		fConst5 = 0.041666668f * mydsp_faustpower2_f(fConst0);
		fConst6 = 0.0052083335f * mydsp_faustpower3_f(fConst0);
	}
	
	virtual void instanceResetUserInterface() {
		fVslider0 = FAUSTFLOAT(-2e+01f);
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fCheckbox1 = FAUSTFLOAT(0.0f);
		fEntry0 = FAUSTFLOAT(2.0f);
		fVslider1 = FAUSTFLOAT(49.0f);
		fVslider2 = FAUSTFLOAT(0.1f);
		fVslider3 = FAUSTFLOAT(-0.1f);
		fVslider4 = FAUSTFLOAT(0.1f);
		fCheckbox2 = FAUSTFLOAT(0.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 4; l0 = l0 + 1) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec0[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec2[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec1[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fVec1[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fVec2[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fVec3[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fVec4[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fVec5[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fVec6[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 2; l10 = l10 + 1) {
			fRec3[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 2; l11 = l11 + 1) {
			fVec7[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 2; l12 = l12 + 1) {
			fVec8[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 2; l13 = l13 + 1) {
			fVec9[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 2; l14 = l14 + 1) {
			fVec10[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 2; l15 = l15 + 1) {
			fVec11[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 2; l16 = l16 + 1) {
			fVec12[l16] = 0.0f;
		}
		for (int l17 = 0; l17 < 2; l17 = l17 + 1) {
			fRec4[l17] = 0.0f;
		}
		for (int l18 = 0; l18 < 2; l18 = l18 + 1) {
			fVec13[l18] = 0.0f;
		}
		for (int l19 = 0; l19 < 2; l19 = l19 + 1) {
			fVec14[l19] = 0.0f;
		}
		for (int l20 = 0; l20 < 2; l20 = l20 + 1) {
			fVec15[l20] = 0.0f;
		}
		for (int l21 = 0; l21 < 2; l21 = l21 + 1) {
			fVec16[l21] = 0.0f;
		}
		for (int l22 = 0; l22 < 2; l22 = l22 + 1) {
			fVec17[l22] = 0.0f;
		}
		for (int l23 = 0; l23 < 2; l23 = l23 + 1) {
			fVec18[l23] = 0.0f;
		}
		for (int l24 = 0; l24 < 2; l24 = l24 + 1) {
			iRec5[l24] = 0;
		}
		for (int l25 = 0; l25 < 4; l25 = l25 + 1) {
			fRec6[l25] = 0.0f;
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
		ui_interface->declare(0, "0", "");
		ui_interface->declare(0, "tooltip", "See Faust's oscillators.lib         for documentation and references");
		ui_interface->openVerticalBox("SAWTOOTH OSCILLATOR");
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fVslider0, "1", "");
		ui_interface->declare(&fVslider0, "style", "knob");
		ui_interface->declare(&fVslider0, "tooltip", "Sawtooth         waveform amplitude");
		ui_interface->declare(&fVslider0, "unit", "dB");
		ui_interface->addVerticalSlider("Amplitude", &fVslider0, FAUSTFLOAT(-2e+01f), FAUSTFLOAT(-1.2e+02f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fVslider1, "2", "");
		ui_interface->declare(&fVslider1, "style", "knob");
		ui_interface->declare(&fVslider1, "tooltip", "Sawtooth         frequency as a Piano Key (PK) number (A440 = key 49)");
		ui_interface->declare(&fVslider1, "unit", "PK");
		ui_interface->addVerticalSlider("Frequency", &fVslider1, FAUSTFLOAT(49.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(88.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fVslider3, "3", "");
		ui_interface->declare(&fVslider3, "style", "knob");
		ui_interface->declare(&fVslider3, "tooltip", "Percentage frequency-shift     up or down for second oscillator");
		ui_interface->declare(&fVslider3, "unit", "%%");
		ui_interface->addVerticalSlider("Detuning 1", &fVslider3, FAUSTFLOAT(-0.1f), FAUSTFLOAT(-1e+01f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fVslider4, "4", "");
		ui_interface->declare(&fVslider4, "style", "knob");
		ui_interface->declare(&fVslider4, "tooltip", "Percentage frequency-shift up or down for third detuned oscillator");
		ui_interface->declare(&fVslider4, "unit", "%%");
		ui_interface->addVerticalSlider("Detuning 2", &fVslider4, FAUSTFLOAT(0.1f), FAUSTFLOAT(-1e+01f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fVslider2, "5", "");
		ui_interface->declare(&fVslider2, "scale", "log");
		ui_interface->declare(&fVslider2, "style", "knob");
		ui_interface->declare(&fVslider2, "tooltip", "Portamento (frequency-glide) time-constant in seconds");
		ui_interface->declare(&fVslider2, "unit", "sec");
		ui_interface->addVerticalSlider("Portamento", &fVslider2, FAUSTFLOAT(0.1f), FAUSTFLOAT(0.001f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fEntry0, "6", "");
		ui_interface->declare(&fEntry0, "tooltip", "Order of sawtootn aliasing         suppression");
		ui_interface->addNumEntry("Saw Order", &fEntry0, FAUSTFLOAT(2.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(4.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(0, "7", "");
		ui_interface->openVerticalBox("Alternate Signals");
		ui_interface->declare(&fCheckbox1, "0", "");
		ui_interface->addCheckButton("Noise (White or Pink - uses only Amplitude control on         the left)", &fCheckbox1);
		ui_interface->declare(&fCheckbox2, "1", "");
		ui_interface->declare(&fCheckbox2, "tooltip", "Pink Noise (or 1/f noise) is Constant-Q Noise, meaning that it has the         same total power in every octave");
		ui_interface->addCheckButton("Pink instead of White Noise (also called 1/f Noise)", &fCheckbox2);
		ui_interface->declare(&fCheckbox0, "2", "");
		ui_interface->addCheckButton("External Signal Input (overrides Sawtooth/Noise         selection above)", &fCheckbox0);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = fConst1 * std::pow(1e+01f, 0.05f * float(fVslider0));
		int iSlow1 = int(float(fCheckbox0));
		int iSlow2 = int(float(fCheckbox1));
		int iSlow3 = int(float(fEntry0) + -1.0f);
		int iSlow4 = iSlow3 >= 2;
		int iSlow5 = iSlow3 >= 1;
		float fSlow6 = float(fVslider2);
		int iSlow7 = std::fabs(fSlow6) < 1.1920929e-07f;
		float fSlow8 = ((iSlow7) ? 0.0f : std::exp(-(fConst3 / ((iSlow7) ? 1.0f : fSlow6))));
		float fSlow9 = 4.4e+02f * std::pow(2.0f, 0.083333336f * (float(fVslider1) + -49.0f)) * (1.0f - fSlow8);
		int iSlow10 = iSlow3 >= 3;
		float fSlow11 = 0.01f * float(fVslider3) + 1.0f;
		float fSlow12 = 0.01f * float(fVslider4) + 1.0f;
		int iSlow13 = int(float(fCheckbox2));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			iVec0[0] = 1;
			fRec0[0] = fSlow0 + fConst2 * fRec0[1];
			int iTemp0 = 1 - iVec0[1];
			fRec2[0] = fSlow9 + fSlow8 * fRec2[1];
			float fTemp1 = std::max<float>(2e+01f, std::fabs(fRec2[0]));
			float fTemp2 = ((iTemp0) ? 0.0f : fRec1[1] + fConst3 * fTemp1);
			fRec1[0] = fTemp2 - std::floor(fTemp2);
			float fTemp3 = 2.0f * fRec1[0];
			float fTemp4 = fTemp3 + -1.0f;
			float fTemp5 = float(iVec0[1]);
			float fTemp6 = mydsp_faustpower2_f(fTemp4);
			fVec1[0] = fTemp6;
			float fTemp7 = float(iVec0[2]);
			float fTemp8 = mydsp_faustpower3_f(fTemp4);
			fVec2[0] = fTemp8 + (1.0f - fTemp3);
			float fTemp9 = (fTemp8 + (1.0f - (fTemp3 + fVec2[1]))) / fTemp1;
			fVec3[0] = fTemp9;
			float fTemp10 = float(iVec0[3]);
			float fTemp11 = fTemp6 * (fTemp6 + -2.0f);
			fVec4[0] = fTemp11;
			float fTemp12 = (fTemp11 - fVec4[1]) / fTemp1;
			fVec5[0] = fTemp12;
			float fTemp13 = (fTemp12 - fVec5[1]) / fTemp1;
			fVec6[0] = fTemp13;
			float fTemp14 = std::max<float>(2e+01f, std::fabs(fSlow11 * fRec2[0]));
			float fTemp15 = ((iTemp0) ? 0.0f : fRec3[1] + fConst3 * fTemp14);
			fRec3[0] = fTemp15 - std::floor(fTemp15);
			float fTemp16 = 2.0f * fRec3[0];
			float fTemp17 = fTemp16 + -1.0f;
			float fTemp18 = mydsp_faustpower2_f(fTemp17);
			fVec7[0] = fTemp18;
			float fTemp19 = mydsp_faustpower3_f(fTemp17);
			fVec8[0] = fTemp19 + (1.0f - fTemp16);
			float fTemp20 = (fTemp19 + (1.0f - (fTemp16 + fVec8[1]))) / fTemp14;
			fVec9[0] = fTemp20;
			float fTemp21 = fTemp18 * (fTemp18 + -2.0f);
			fVec10[0] = fTemp21;
			float fTemp22 = (fTemp21 - fVec10[1]) / fTemp14;
			fVec11[0] = fTemp22;
			float fTemp23 = (fTemp22 - fVec11[1]) / fTemp14;
			fVec12[0] = fTemp23;
			float fTemp24 = std::max<float>(2e+01f, std::fabs(fSlow12 * fRec2[0]));
			float fTemp25 = ((iTemp0) ? 0.0f : fRec4[1] + fConst3 * fTemp24);
			fRec4[0] = fTemp25 - std::floor(fTemp25);
			float fTemp26 = 2.0f * fRec4[0];
			float fTemp27 = fTemp26 + -1.0f;
			float fTemp28 = mydsp_faustpower2_f(fTemp27);
			fVec13[0] = fTemp28;
			float fTemp29 = mydsp_faustpower3_f(fTemp27);
			fVec14[0] = fTemp29 + (1.0f - fTemp26);
			float fTemp30 = (fTemp29 + (1.0f - (fTemp26 + fVec14[1]))) / fTemp24;
			fVec15[0] = fTemp30;
			float fTemp31 = fTemp28 * (fTemp28 + -2.0f);
			fVec16[0] = fTemp31;
			float fTemp32 = (fTemp31 - fVec16[1]) / fTemp24;
			fVec17[0] = fTemp32;
			float fTemp33 = (fTemp32 - fVec17[1]) / fTemp24;
			fVec18[0] = fTemp33;
			iRec5[0] = 1103515245 * iRec5[1] + 12345;
			float fTemp34 = 4.656613e-10f * float(iRec5[0]);
			fRec6[0] = 0.5221894f * fRec6[3] + fTemp34 + 2.494956f * fRec6[1] - 2.0172658f * fRec6[2];
			output0[i0] = FAUSTFLOAT(fRec0[0] * ((iSlow1) ? float(input0[i0]) : ((iSlow2) ? ((iSlow13) ? 0.049922034f * fRec6[0] + 0.0506127f * fRec6[2] - (0.095993534f * fRec6[1] + 0.004408786f * fRec6[3]) : fTemp34) : 0.33333334f * fRec0[0] * (((iSlow4) ? ((iSlow10) ? fConst6 * (fTemp10 * (fTemp13 - fVec6[1]) / fTemp1) : fConst5 * (fTemp7 * (fTemp9 - fVec3[1]) / fTemp1)) : ((iSlow5) ? fConst4 * (fTemp5 * (fTemp6 - fVec1[1]) / fTemp1) : fTemp4)) + ((iSlow4) ? ((iSlow10) ? fConst6 * (fTemp10 * (fTemp23 - fVec12[1]) / fTemp14) : fConst5 * (fTemp7 * (fTemp20 - fVec9[1]) / fTemp14)) : ((iSlow5) ? fConst4 * (fTemp5 * (fTemp18 - fVec7[1]) / fTemp14) : fTemp17)) + ((iSlow4) ? ((iSlow10) ? fConst6 * (fTemp10 * (fTemp33 - fVec18[1]) / fTemp24) : fConst5 * (fTemp7 * (fTemp30 - fVec15[1]) / fTemp24)) : ((iSlow5) ? fConst4 * (fTemp5 * (fTemp28 - fVec13[1]) / fTemp24) : fTemp27))))));
			for (int j0 = 3; j0 > 0; j0 = j0 - 1) {
				iVec0[j0] = iVec0[j0 - 1];
			}
			fRec0[1] = fRec0[0];
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
			fVec1[1] = fVec1[0];
			fVec2[1] = fVec2[0];
			fVec3[1] = fVec3[0];
			fVec4[1] = fVec4[0];
			fVec5[1] = fVec5[0];
			fVec6[1] = fVec6[0];
			fRec3[1] = fRec3[0];
			fVec7[1] = fVec7[0];
			fVec8[1] = fVec8[0];
			fVec9[1] = fVec9[0];
			fVec10[1] = fVec10[0];
			fVec11[1] = fVec11[0];
			fVec12[1] = fVec12[0];
			fRec4[1] = fRec4[0];
			fVec13[1] = fVec13[0];
			fVec14[1] = fVec14[0];
			fVec15[1] = fVec15[0];
			fVec16[1] = fVec16[0];
			fVec17[1] = fVec17[0];
			fVec18[1] = fVec18[0];
			iRec5[1] = iRec5[0];
			for (int j1 = 3; j1 > 0; j1 = j1 - 1) {
				fRec6[j1] = fRec6[j1 - 1];
			}
		}
	}

};

// custom UI class inheriting Faust's MapUI to store parameter metadata
struct CLAPMapUI : public MapUI {
    struct ParamMeta {
        FAUSTFLOAT min;
        FAUSTFLOAT max;
        FAUSTFLOAT init;
    };

    struct ParamData {
        std::string shortname;
        ParamMeta meta;
    };

    std::vector<ParamData> fParams;

    void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override {
        MapUI::addVerticalSlider(label, zone, init, min, max, step);
        std::string shortname = buildPath(label);
        fParams.push_back({shortname, {min, max, init}});
    }

    void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override {
        MapUI::addHorizontalSlider(label, zone, init, min, max, step);
        std::string shortname = buildPath(label);
        fParams.push_back({shortname, {min, max, init}});
    }

    void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override {
        MapUI::addNumEntry(label, zone, init, min, max, step);
        std::string shortname = buildPath(label);
        fParams.push_back({shortname, {min, max, init}});
    }

    void openTabBox(const char* label) override { MapUI::openTabBox(label); }
    void openHorizontalBox(const char* label) override { MapUI::openHorizontalBox(label); }
    void openVerticalBox(const char* label) override { MapUI::openVerticalBox(label); }
    void closeBox() override { MapUI::closeBox(); }

    int getParamsCount() const { return int(fParams.size()); }

    std::string getParamShortname(int index) const {
        if (index < 0 || index >= int(fParams.size())) return "";
        return fParams[index].shortname;
    }

    FAUSTFLOAT getParamMin(int index) const {
        if (index < 0 || index >= int(fParams.size())) return 0.f;
        return fParams[index].meta.min;
    }

    FAUSTFLOAT getParamMax(int index) const {
        if (index < 0 || index >= int(fParams.size())) return 1.f;
        return fParams[index].meta.max;
    }

    FAUSTFLOAT getParamInit(int index) const {
        if (index < 0 || index >= int(fParams.size())) return 0.5f;
        return fParams[index].meta.init;
    }

    FAUSTFLOAT* getParamZone(int index) const {
        if (index < 0 || index >= int(fParams.size())) return nullptr;
        return MapUI::getParamZone(fParams[index].shortname);
    }

    void setParamValue(int index, FAUSTFLOAT val) {
        if (index < 0 || index >= getParamsCount()) return;
        MapUI::setParamValue(fParams[index].shortname, val);
    }

    FAUSTFLOAT getParamValue(int index) const {
        if (index < 0 || index >= getParamsCount()) return 0.f;
        return MapUI::getParamValue(fParams[index].shortname);
    }

    std::string getParamAddress(int index) const {
        if (index < 0 || index >= int(fParams.size())) return "";
        return fParams[index].shortname;
    }
};

// forward declaration for Plugin class
class GainPlugin;

// base class alias for simplified CLAP plugin inheritance
using Base = clap::helpers::Plugin<
    clap::helpers::MisbehaviourHandler::Terminate,
    clap::helpers::CheckingLevel::Minimal>;

// plugin features declaration
static const char* gain_features[] = { CLAP_PLUGIN_FEATURE_AUDIO_EFFECT, nullptr };

// plugin descriptor structure describing metadata to the host
static const clap_plugin_descriptor_t gain_desc = {
    .clap_version = CLAP_VERSION_INIT,
    .id = "org.faust.gain",
    .name = "Faust Gain",
    .vendor = "faust",
    .url = "https://faust.grame.fr",
    .manual_url = "",
    .support_url = "",
    .version = "1.0.0",
    .description = "Plugin generated from Faust",
    .features = gain_features
};

// the main plugin class implementing CLAP plugin behaviour
class GainPlugin final : public Base {
public:
    int fNumInputs = 2; // default to stereo
    int fNumOutputs = 2;
    mydsp* fBaseDSP = nullptr; // original Faust DSP
    mydsp_poly* fDSP = nullptr; // midi-aware wrapper

    CLAPMapUI fUI;
    bool fIsPolyphonic = false; // determines if midi/note handling is enabled
    MidiUI* fMidiUI = nullptr;
    midi_handler* fMidiHandler = nullptr;

    // constructor initialises base class with descriptor and host pointers
    GainPlugin(const clap_plugin_descriptor_t* desc, const clap_host_t* host)
        : Base(desc, host) {}

    bool init() noexcept override {
        fBaseDSP = new mydsp();
        fIsPolyphonic = true;
        if (fIsPolyphonic) {
            // create polyphonic wrapper and build UI linked to CLAPMapUI
            fDSP = new mydsp_poly(fBaseDSP, 16, true, true);
            fDSP->buildUserInterface(&fUI);
            GUI::updateAllGuis();

        } else {
            // create MIDI support and UI for non-polyphonic mode
            fMidiHandler = new midi_handler();
            fMidiUI = new MidiUI(fMidiHandler);
            fBaseDSP->buildUserInterface(fMidiUI); // MIDI support
            fBaseDSP->buildUserInterface(&fUI); // regular UI
            GUI::updateAllGuis();
        }
        return true;
    }

    // activate plugin and initialise DSP with sample rate
    bool activate(double sampleRate, uint32_t, uint32_t) noexcept override {
        if (fIsPolyphonic) {
            fDSP->init(sampleRate);
            fNumInputs = fDSP->getNumInputs();
            fNumOutputs = fDSP->getNumOutputs();
        } else {
            fBaseDSP->init(sampleRate);
            fNumInputs = fBaseDSP->getNumInputs();
            fNumOutputs = fBaseDSP->getNumOutputs();
        }
        return true;
    }

    // apply parameter event if valid and within range
    bool applyParamEventIfValid(const clap_event_header_t* hdr) {
        if (!hdr || hdr->space_id != CLAP_CORE_EVENT_SPACE_ID || hdr->type != CLAP_EVENT_PARAM_VALUE) // defensive check: hdr should not be null, but verify to avoid crashes on malformed events
            return false;

        const auto* ev = reinterpret_cast<const clap_event_param_value_t*>(hdr);
        int paramCount = fUI.getParamsCount();
        if (!ev || ev->param_id < 0 || ev->param_id >= paramCount)
            return false;

        fUI.setParamValue(ev->param_id, ev->value);
        return true;
    }

    // handle MIDI events in polyphonic mode by forwarding to Faust DSP
    void handlePolyMIDIEvent(const clap_event_header_t* hdr){
        switch (hdr->type) {
            case CLAP_EVENT_NOTE_ON: {
                auto* ev = reinterpret_cast<const clap_event_note_t*>(hdr);
                fDSP->keyOn(ev->channel, ev->key, ev->velocity);
                break;
            }
            case CLAP_EVENT_NOTE_OFF: {
                auto* ev = reinterpret_cast<const clap_event_note_t*>(hdr);
                fDSP->keyOff(ev->channel, ev->key, ev->velocity);
                break;
            }
            case CLAP_EVENT_MIDI: {
                auto* ev = reinterpret_cast<const clap_event_midi_t*>(hdr);
                uint8_t status = ev->data[0] & 0xF0;
                uint8_t channel = ev->data[0] & 0x0F;
                uint8_t data1 = ev->data[1];
                uint8_t data2 = ev->data[2];

                switch (status) {
                    case 0x90: fDSP->keyOn(channel, data1, data2); break;
                    case 0x80: fDSP->keyOff(channel, data1, data2); break;
                    case 0xB0: fDSP->ctrlChange(channel, data1, data2); break;
                    case 0xE0: fDSP->pitchWheel(channel, (data2 << 7) | data1); break;
                }
                break;
            }
        }
    }

    // handle MIDI events in non-polyphonic DSP mode
	//assumes fBaseDSP, fMidiHandler, and hdr are valid and hdr->space_id == CLAP_CORE_EVENT_SPACE_ID
    void handleDSPMIDIEvent(const clap_event_header_t* hdr) {
        switch (hdr->type) {
            case CLAP_EVENT_MIDI: {
                auto* ev = reinterpret_cast<const clap_event_midi_t*>(hdr);
                int type = ev->data[0] & 0xF0;
                int channel = ev->data[0] & 0x0F;
                int data1 = ev->data[1];
                int data2 = ev->data[2];
                fMidiHandler->handleData2(0.0, type, channel, data1, data2);

                break;
            }
            default: break;
        }
    }

    // provide CLAP extensions this plugin supports
    const void* get_extension(const char* id) noexcept {
        if (std::strcmp(id, CLAP_EXT_NOTE_PORTS) == 0) return (const clap_plugin_note_ports_t*)this;
        if (std::strcmp(id, CLAP_EXT_STATE) == 0) return (const clap_plugin_state_t*)this;
        if (std::strcmp(id, CLAP_EXT_PARAMS) == 0) return (const clap_plugin_params_t*)this;
        return nullptr;
    }

    // main processing method called by host each audio block
    clap_process_status process(const clap_process_t* process) noexcept override {

        // basic sanity checks on audio IO buffers
        if (process->audio_inputs_count < 1 || process->audio_outputs_count < 1)
            return CLAP_PROCESS_ERROR;
        const auto& inBuffer = process->audio_inputs[0];
        const auto& outBuffer = process->audio_outputs[0];
        if (inBuffer.channel_count < fNumInputs || outBuffer.channel_count < fNumOutputs)
            return CLAP_PROCESS_ERROR;

        if (inBuffer.channel_count == 0 || outBuffer.channel_count == 0)
            return CLAP_PROCESS_CONTINUE;

        // process incoming parameter and MIDI events
        if (process->in_events) {
            for (uint32_t i = 0, N = process->in_events->size(process->in_events); i < N; ++i) {
                const clap_event_header_t* hdr = process->in_events->get(process->in_events, i);
                applyParamEventIfValid(hdr);
                if (fIsPolyphonic) {
                    handlePolyMIDIEvent(hdr);
                } else {
                    handleDSPMIDIEvent(hdr);
                }
            }
        }

        // prepare Faust audio buffers
        FAUSTFLOAT* inputs[fNumInputs];
        FAUSTFLOAT* outputs[fNumOutputs];
        for (int i = 0; i < fNumInputs; ++i)
            inputs[i] = inBuffer.data32[i];
        for (int i = 0; i < fNumOutputs; ++i)
            outputs[i] = outBuffer.data32[i];

        // compute audio block
        if (fIsPolyphonic) {
            fDSP->compute(process->frames_count, inputs, outputs);
        } else {
            fBaseDSP->compute(process->frames_count, inputs, outputs);
        }

        return CLAP_PROCESS_CONTINUE;
    }

    // implement note ports extension, always 1 input port
    bool implementsNotePorts() const noexcept override { return true; }
    uint32_t notePortsCount(bool isInput) const noexcept override { return isInput ? 1 : 0; }

    bool notePortsInfo(uint32_t index, bool isInput, clap_note_port_info_t* info) const noexcept override {
        if (!isInput || index != 0) return false;
        std::memset(info, 0, sizeof(*info));
        info->id = index;
        std::snprintf(info->name, CLAP_NAME_SIZE, "MIDI In");
        info->supported_dialects = CLAP_NOTE_DIALECT_CLAP | CLAP_NOTE_DIALECT_MIDI;
        info->preferred_dialect = CLAP_NOTE_DIALECT_CLAP;
        return true;
    }

    // implement state extension to save and restore parameter values
    bool implementsState() const noexcept override { return true; }

    bool stateSave(const clap_ostream_t* stream) noexcept override {
        if (!stream || !stream->write) return false;
        int paramCount = fUI.getParamsCount();

        // write number of parameters
        if (!stream->write(stream, &paramCount, sizeof(paramCount))) return false;

        // write each parameter value
        for (int i = 0; i < paramCount; ++i) {
            float v = fUI.getParamValue(i);
            if (!stream->write(stream, &v, sizeof(v))) return false;
        }
        return true;
    }

    bool stateLoad(const clap_istream_t* stream) noexcept override {
        if (!stream || !stream->read) return false;
        uint32_t paramCount = 0;

        // read number of parameters
        if (!stream->read(stream, &paramCount, sizeof(paramCount))) return false;

        if (paramCount != (uint32_t)fUI.getParamsCount())
            return false;

        // read each parameter and set value
        for (uint32_t i = 0; i < paramCount; ++i) {
            float v;
            if (!stream->read(stream, &v, sizeof(v))) return false;
            fUI.setParamValue(i, v);
        }

        // notify host to update parameter display and processing
        if (_host.canUseParams()) {
            _host.paramsRescan(CLAP_PARAM_RESCAN_VALUES | CLAP_PARAM_RESCAN_ALL);
            _host.paramsRequestFlush();
        }

        return true;
    }

    // implement parameter extension methods
    bool implementsParams() const noexcept override { return true; }
    uint32_t paramsCount() const noexcept override {
        return static_cast<uint32_t>(fUI.getParamsCount());
    }

    bool paramsInfo(uint32_t index, clap_param_info_t* info) const noexcept override {
    int paramCount = fUI.getParamsCount();
    if (index >= paramCount) return false;

    std::memset(info, 0, sizeof(*info));
    info->id = index;

    std::string paramName = fUI.getParamShortname(index);
    if (paramName.empty() || paramName == "/") {
        paramName = "param" + std::to_string(index);  // fallback safe name
    }
    const char* name = paramName.c_str();
    if (paramName.size() > 1 && name[0] == '/') ++name; // remove leading slash if present

    std::snprintf(info->name, CLAP_NAME_SIZE, "%s", name);

    FAUSTFLOAT min = fUI.getParamMin(index);
    FAUSTFLOAT max = fUI.getParamMax(index);
    FAUSTFLOAT init = fUI.getParamInit(index);

    info->min_value = min;
    info->max_value = max;
    info->default_value = init;
    info->flags = CLAP_PARAM_IS_AUTOMATABLE;

    std::strncpy(info->module, "Main", sizeof(info->module));
    info->module[sizeof(info->module) - 1] = '\0';

    return true;
}


// return parameter value by ID
bool paramsValue(clap_id id, double* value) noexcept override {
    if (!value || id >= (clap_id)fUI.getParamsCount())
        return false;
    *value = fUI.getParamValue(id);
    return true;
}

    // convert text to parameter value (string to double)
    bool paramsTextToValue(clap_id id, const char* text, double* outValue) noexcept override {
        if (!text || !outValue || id >= (clap_id)fUI.getParamsCount())
            return false;
        try {
            *outValue = std::stod(text);
            return true;
        } catch (...) {
            return false;
        }
    }

    // convert parameter value to text representation
    bool paramsValueToText(clap_id id, double value, char* outBuffer, uint32_t bufferSize) noexcept override {
        if (!outBuffer || bufferSize == 0 || id >= (clap_id)fUI.getParamsCount())
            return false;
        std::snprintf(outBuffer, bufferSize, "%.3f", value);
        return true;
    }

    // flush pending parameter and MIDI events in the event queue
    void paramsFlush(const clap_input_events_t* in, const clap_output_events_t*) noexcept override {
        if (!in) return;

        // iterate over all incoming events
        for (uint32_t i = 0; i < in->size(in); ++i) {
            const clap_event_header_t* hdr = in->get(in, i);
            if (!hdr) continue;

            // apply parameter changes if the event is valid
            applyParamEventIfValid(hdr);

            // route MIDI events according to polyphony mode
            if (fIsPolyphonic) {
                handlePolyMIDIEvent(hdr);
            } else {
                handleDSPMIDIEvent(hdr);
            }
        }
    }

    // indicate support for audio ports
    bool implementsAudioPorts() const noexcept override { return true; }

    // report number of audio ports; 1 input and 1 output port by default
    uint32_t audioPortsCount(bool isInput) const noexcept override { return 1; }

    // provide information about audio ports to host
    bool audioPortsInfo(uint32_t index, bool isInput, clap_audio_port_info_t* info) const noexcept override {
        if (index != 0 || !info) return false;
        std::memset(info, 0, sizeof(*info));
        info->id = index;
        std::snprintf(info->name, CLAP_NAME_SIZE, "%s", isInput ? "Input" : "Output");

        // channel count matches current number of DSP inputs or outputs
        info->channel_count = isInput ? std::max(1, fNumInputs) : std::max(1, fNumOutputs);

        // mark port as the main port for in-place processing
        info->flags = CLAP_AUDIO_PORT_IS_MAIN;
        info->in_place_pair = 0;  //port for in-place processing
        return true;
    }

    // expose base class method to retrieve underlying CLAP plugin pointer
    using Base::clapPlugin;
    static const clap_plugin_t* create(const clap_host_t* host) {
        return (new GainPlugin(&gain_desc, host))->clapPlugin();
    }
};

// return total number of plugins provided by this factory
static uint32_t plugin_count(const clap_plugin_factory_t*) { return 1; }

// return plugin descriptor for given index; only one plugin here
static const clap_plugin_descriptor_t* plugin_desc(const clap_plugin_factory_t*, uint32_t index) {
    return (index == 0) ? &gain_desc : nullptr;
}

// factory method to create new plugin instance
static const clap_plugin_t* plugin_create(const clap_plugin_factory_t*, const clap_host_t* host, const char* plugin_id) {
    if (std::strcmp(plugin_id, gain_desc.id) == 0)
        return GainPlugin::create(host);
    return nullptr;
}

// single plugin factory structure describing factory callbacks
static const clap_plugin_factory_t gain_factory = {
    .get_plugin_count = plugin_count,
    .get_plugin_descriptor = plugin_desc,
    .create_plugin = plugin_create
};

// entry point initialisation and deinitialisation
static bool entry_init(const char* path) { return true; }
static void entry_deinit() {}

// C linkage block exporting the CLAP factory to the host
extern "C" {

// retrieve the requested factory by its ID string
CLAP_EXPORT const void* clap_get_factory(const char* factory_id) {
    if (std::strcmp(factory_id, CLAP_PLUGIN_FACTORY_ID) == 0)
        return &gain_factory;
    return nullptr;
}

// define the CLAP plugin entry point structure
CLAP_EXPORT const clap_plugin_entry_t clap_entry = {
    CLAP_VERSION_INIT,
    entry_init,
    entry_deinit,
    clap_get_factory
};
}

#endif
