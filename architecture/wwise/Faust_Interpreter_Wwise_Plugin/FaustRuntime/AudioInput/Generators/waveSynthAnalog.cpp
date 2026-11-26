/* ------------------------------------------------------------
name: "untitled"
Code generated with Faust 2.79.4 (https://faust.grame.fr)
Compilation options: -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __WaveSynthAnalog_H__
#define  __WaveSynthAnalog_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <faust/dsp/dsp.h>
#include <faust/gui/MapUI.h>
#include <faust/gui/meta.h>
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS WaveSynthAnalog
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

class WaveSynthAnalogSIG0 {
	
  private:
	
	int iRec3[2];
	
  public:
	
	int getNumInputsWaveSynthAnalogSIG0() {
		return 0;
	}
	int getNumOutputsWaveSynthAnalogSIG0() {
		return 1;
	}
	
	void instanceInitWaveSynthAnalogSIG0(int sample_rate) {
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			iRec3[l4] = 0;
		}
	}
	
	void fillWaveSynthAnalogSIG0(int count, float* table) {
		for (int i1 = 0; i1 < count; i1 = i1 + 1) {
			iRec3[0] = iRec3[1] + 1;
			table[i1] = std::fabs(std::fmod(0.00390625f * float(iRec3[1]) + 1.0f, 4.0f) + -2.0f) + -1.0f;
			iRec3[1] = iRec3[0];
		}
	}

};

static WaveSynthAnalogSIG0* newWaveSynthAnalogSIG0() { return (WaveSynthAnalogSIG0*)new WaveSynthAnalogSIG0(); }
static void deleteWaveSynthAnalogSIG0(WaveSynthAnalogSIG0* dsp) { delete dsp; }

class WaveSynthAnalogSIG1 {
	
  private:
	
	int iRec5[2];
	
  public:
	
	int getNumInputsWaveSynthAnalogSIG1() {
		return 0;
	}
	int getNumOutputsWaveSynthAnalogSIG1() {
		return 1;
	}
	
	void instanceInitWaveSynthAnalogSIG1(int sample_rate) {
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			iRec5[l6] = 0;
		}
	}
	
	void fillWaveSynthAnalogSIG1(int count, float* table) {
		for (int i2 = 0; i2 < count; i2 = i2 + 1) {
			iRec5[0] = iRec5[1] + 1;
			table[i2] = std::fabs(std::fmod(0.005859375f * float(iRec5[1]) + 1.0f, 4.0f) + -2.0f) + -1.0f;
			iRec5[1] = iRec5[0];
		}
	}

};

static WaveSynthAnalogSIG1* newWaveSynthAnalogSIG1() { return (WaveSynthAnalogSIG1*)new WaveSynthAnalogSIG1(); }
static void deleteWaveSynthAnalogSIG1(WaveSynthAnalogSIG1* dsp) { delete dsp; }

class WaveSynthAnalogSIG2 {
	
  private:
	
	int iRec6[2];
	
  public:
	
	int getNumInputsWaveSynthAnalogSIG2() {
		return 0;
	}
	int getNumOutputsWaveSynthAnalogSIG2() {
		return 1;
	}
	
	void instanceInitWaveSynthAnalogSIG2(int sample_rate) {
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			iRec6[l7] = 0;
		}
	}
	
	void fillWaveSynthAnalogSIG2(int count, float* table) {
		for (int i3 = 0; i3 < count; i3 = i3 + 1) {
			iRec6[0] = iRec6[1] + 1;
			table[i3] = std::fabs(std::fmod(0.0078125f * float(iRec6[1]) + 1.0f, 4.0f) + -2.0f) + -1.0f;
			iRec6[1] = iRec6[0];
		}
	}

};

static WaveSynthAnalogSIG2* newWaveSynthAnalogSIG2() { return (WaveSynthAnalogSIG2*)new WaveSynthAnalogSIG2(); }
static void deleteWaveSynthAnalogSIG2(WaveSynthAnalogSIG2* dsp) { delete dsp; }

class WaveSynthAnalogSIG3 {
	
  private:
	
	int iRec7[2];
	
  public:
	
	int getNumInputsWaveSynthAnalogSIG3() {
		return 0;
	}
	int getNumOutputsWaveSynthAnalogSIG3() {
		return 1;
	}
	
	void instanceInitWaveSynthAnalogSIG3(int sample_rate) {
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			iRec7[l8] = 0;
		}
	}
	
	void fillWaveSynthAnalogSIG3(int count, float* table) {
		for (int i4 = 0; i4 < count; i4 = i4 + 1) {
			iRec7[0] = iRec7[1] + 1;
			table[i4] = std::fabs(std::fmod(0.015625f * float(iRec7[1]) + 1.0f, 4.0f) + -2.0f) + -1.0f;
			iRec7[1] = iRec7[0];
		}
	}

};

static WaveSynthAnalogSIG3* newWaveSynthAnalogSIG3() { return (WaveSynthAnalogSIG3*)new WaveSynthAnalogSIG3(); }
static void deleteWaveSynthAnalogSIG3(WaveSynthAnalogSIG3* dsp) { delete dsp; }

static float ftbl0WaveSynthAnalogSIG0[1024];
static float ftbl1WaveSynthAnalogSIG1[1024];
static float ftbl2WaveSynthAnalogSIG2[1024];
static float ftbl3WaveSynthAnalogSIG3[1024];

class WaveSynthAnalog : public dsp {
	
 private:
	
	int iVec0[2];
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fHslider0;
	float fRec1[2];
	float fConst3;
	float fRec0[2];
	FAUSTFLOAT fHslider1;
	float fRec2[2];
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT fEntry0;
	float fRec4[2];
	FAUSTFLOAT fHslider4;
	int iRec9[2];
	FAUSTFLOAT fHslider5;
	FAUSTFLOAT fHslider6;
	float fRec8[2];
	FAUSTFLOAT fEntry1;
	
 public:
	WaveSynthAnalog() {
	}
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.21.0");
		m->declare("compile_options", "-lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("envelopes.lib/adsre:author", "Julius O. Smith III");
		m->declare("envelopes.lib/adsre:licence", "STK-4.3");
		m->declare("envelopes.lib/author", "GRAME");
		m->declare("envelopes.lib/copyright", "GRAME");
		m->declare("envelopes.lib/license", "LGPL with exception");
		m->declare("envelopes.lib/name", "Faust Envelope Library");
		m->declare("envelopes.lib/version", "1.3.0");
		m->declare("filename", "untitled.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.8.1");
		m->declare("name", "untitled");
		m->declare("oscillators.lib/lf_sawpos:author", "Bart Brouns, revised by Stéphane Letz");
		m->declare("oscillators.lib/lf_sawpos:licence", "STK-4.3");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/saw1:author", "Bart Brouns");
		m->declare("oscillators.lib/saw1:licence", "STK-4.3");
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
		return 1;
	}
	
	static void classInit(int sample_rate) {
		WaveSynthAnalogSIG0* sig0 = newWaveSynthAnalogSIG0();
		sig0->instanceInitWaveSynthAnalogSIG0(sample_rate);
		sig0->fillWaveSynthAnalogSIG0(1024, ftbl0WaveSynthAnalogSIG0);
		WaveSynthAnalogSIG1* sig1 = newWaveSynthAnalogSIG1();
		sig1->instanceInitWaveSynthAnalogSIG1(sample_rate);
		sig1->fillWaveSynthAnalogSIG1(1024, ftbl1WaveSynthAnalogSIG1);
		WaveSynthAnalogSIG2* sig2 = newWaveSynthAnalogSIG2();
		sig2->instanceInitWaveSynthAnalogSIG2(sample_rate);
		sig2->fillWaveSynthAnalogSIG2(1024, ftbl2WaveSynthAnalogSIG2);
		WaveSynthAnalogSIG3* sig3 = newWaveSynthAnalogSIG3();
		sig3->instanceInitWaveSynthAnalogSIG3(sample_rate);
		sig3->fillWaveSynthAnalogSIG3(1024, ftbl3WaveSynthAnalogSIG3);
		deleteWaveSynthAnalogSIG0(sig0);
		deleteWaveSynthAnalogSIG1(sig1);
		deleteWaveSynthAnalogSIG2(sig2);
		deleteWaveSynthAnalogSIG3(sig3);
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = 44.1f / fConst0;
		fConst2 = 1.0f - fConst1;
		fConst3 = 1.0f / fConst0;
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.1f);
		fHslider1 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(0.0f);
		fHslider3 = FAUSTFLOAT(0.0f);
		fEntry0 = FAUSTFLOAT(4.4e+02f);
		fHslider4 = FAUSTFLOAT(0.01f);
		fHslider5 = FAUSTFLOAT(0.6f);
		fHslider6 = FAUSTFLOAT(0.2f);
		fEntry1 = FAUSTFLOAT(0.5f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec1[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec0[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec2[l3] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec4[l5] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			iRec9[l9] = 0;
		}
		for (int l10 = 0; l10 < 2; l10 = l10 + 1) {
			fRec8[l10] = 0.0f;
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
	
	virtual WaveSynthAnalog* clone() {
		return new WaveSynthAnalog();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("untitled");
		ui_interface->declare(&fHslider4, "midi", "ctrl 73");
		ui_interface->addHorizontalSlider("A", &fHslider4, FAUSTFLOAT(0.01f), FAUSTFLOAT(0.01f), FAUSTFLOAT(4.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider5, "midi", "ctrl 76");
		ui_interface->addHorizontalSlider("D", &fHslider5, FAUSTFLOAT(0.6f), FAUSTFLOAT(0.01f), FAUSTFLOAT(8.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider6, "midi", "ctrl 77");
		ui_interface->addHorizontalSlider("S", &fHslider6, FAUSTFLOAT(0.2f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider3, "midi", "pitchwheel");
		ui_interface->addHorizontalSlider("bend", &fHslider3, FAUSTFLOAT(0.0f), FAUSTFLOAT(-2.0f), FAUSTFLOAT(2.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fEntry0, "unit", "Hz");
		ui_interface->addNumEntry("freq", &fEntry0, FAUSTFLOAT(4.4e+02f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(2e+04f), FAUSTFLOAT(1.0f));
		ui_interface->addNumEntry("gain", &fEntry1, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider1, "BELA", "ANALOG_2");
		ui_interface->addHorizontalSlider("lfoDepth", &fHslider1, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider0, "BELA", "ANALOG_1");
		ui_interface->addHorizontalSlider("lfoFreq", &fHslider0, FAUSTFLOAT(0.1f), FAUSTFLOAT(0.01f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider2, "BELA", "ANALOG_0");
		ui_interface->addHorizontalSlider("waveTravel", &fHslider2, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = fConst1 * float(fHslider0);
		float fSlow1 = fConst1 * float(fHslider1);
		float fSlow2 = float(fHslider2);
		float fSlow3 = fConst3 * float(fEntry0) * std::pow(2.0f, 0.083333336f * float(fHslider3));
		float fSlow4 = float(fHslider4);
		int iSlow5 = int(fConst0 * fSlow4);
		float fSlow6 = float(fHslider5);
		float fSlow7 = float(fHslider6);
		float fSlow8 = float(fEntry1);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			iVec0[0] = 1;
			int iTemp0 = 1 - iVec0[1];
			fRec1[0] = fSlow0 + fConst2 * fRec1[1];
			float fTemp1 = ((iTemp0) ? 0.0f : fRec0[1] + fConst3 * fRec1[0]);
			fRec0[0] = fTemp1 - std::floor(fTemp1);
			fRec2[0] = fSlow1 + fConst2 * fRec2[1];
			float fTemp2 = std::max<float>(0.0f, std::min<float>(1.0f, fSlow2 + fRec2[0] * (1.0f - std::fabs(2.0f * fRec0[0] + -1.0f))));
			float fTemp3 = ((iTemp0) ? 0.0f : fSlow3 + fRec4[1]);
			fRec4[0] = fTemp3 - std::floor(fTemp3);
			int iTemp4 = std::max<int>(0, std::min<int>(int(1024.0f * fRec4[0]), 1023));
			iRec9[0] = iRec9[1] + 1;
			int iTemp5 = (iRec9[0] < iSlow5) | (iTemp0 * (iTemp0 > 0));
			float fTemp6 = 0.1447178f * ((iTemp5) ? fSlow4 : fSlow6);
			int iTemp7 = std::fabs(fTemp6) < 1.1920929e-07f;
			float fTemp8 = ((iTemp7) ? 0.0f : std::exp(-(fConst3 / ((iTemp7) ? 1.0f : fTemp6))));
			fRec8[0] = (1.0f - fTemp8) * ((iTemp5) ? 1.0f : fSlow7) + fTemp8 * fRec8[1];
			output0[i0] = FAUSTFLOAT(fSlow8 * fRec8[0] * (ftbl3WaveSynthAnalogSIG3[iTemp4] * std::max<float>(0.0f, std::cos(4.712385f * fTemp2)) + ftbl2WaveSynthAnalogSIG2[iTemp4] * std::max<float>(0.0f, std::cos(4.712385f * (fTemp2 + -0.33333334f))) + ftbl1WaveSynthAnalogSIG1[iTemp4] * std::max<float>(0.0f, std::cos(4.712385f * (fTemp2 + -0.6666667f))) + ftbl0WaveSynthAnalogSIG0[iTemp4] * std::max<float>(0.0f, std::cos(4.712385f * (fTemp2 + -1.0f)))));
			iVec0[1] = iVec0[0];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
			fRec2[1] = fRec2[0];
			fRec4[1] = fRec4[0];
			iRec9[1] = iRec9[0];
			fRec8[1] = fRec8[0];
		}
	}

};

#endif
