/* ------------------------------------------------------------
name: "untitled"
Code generated with Faust 2.79.4 (https://faust.grame.fr)
Compilation options: -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __FMSynthAnalog_H__
#define  __FMSynthAnalog_H__

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
#define FAUSTCLASS FMSynthAnalog
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

class FMSynthAnalogSIG0 {
	
  private:
	
	int iVec0[2];
	int iRec0[2];
	
  public:
	
	int getNumInputsFMSynthAnalogSIG0() {
		return 0;
	}
	int getNumOutputsFMSynthAnalogSIG0() {
		return 1;
	}
	
	void instanceInitFMSynthAnalogSIG0(int sample_rate) {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			iRec0[l1] = 0;
		}
	}
	
	void fillFMSynthAnalogSIG0(int count, float* table) {
		for (int i1 = 0; i1 < count; i1 = i1 + 1) {
			iVec0[0] = 1;
			iRec0[0] = (iVec0[1] + iRec0[1]) % 65536;
			table[i1] = std::sin(9.58738e-05f * float(iRec0[0]));
			iVec0[1] = iVec0[0];
			iRec0[1] = iRec0[0];
		}
	}

};

static FMSynthAnalogSIG0* newFMSynthAnalogSIG0() { return (FMSynthAnalogSIG0*)new FMSynthAnalogSIG0(); }
static void deleteFMSynthAnalogSIG0(FMSynthAnalogSIG0* dsp) { delete dsp; }

static float ftbl0FMSynthAnalogSIG0[65537];

class FMSynthAnalog : public dsp {
	
 private:
	
	int iVec1[2];
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fHslider0;
	float fRec4[2];
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fEntry0;
	FAUSTFLOAT fHslider2;
	float fRec5[2];
	float fConst3;
	float fRec3[2];
	float fRec2[2];
	FAUSTFLOAT fHslider3;
	int iRec7[2];
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT fHslider5;
	float fRec6[2];
	FAUSTFLOAT fEntry1;
	float fRec1[2];
	
 public:
	FMSynthAnalog() {
	}
	
	void metadata(Meta* m) { 
		m->declare("aanl.lib/name", "Faust Antialiased Nonlinearities");
		m->declare("aanl.lib/version", "1.4.1");
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "1.2.0");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.21.0");
		m->declare("compile_options", "-lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("compressors.lib/name", "Faust Compressor Effect Library");
		m->declare("compressors.lib/version", "1.6.0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "1.1.0");
		m->declare("demos.lib/name", "Faust Demos Library");
		m->declare("demos.lib/version", "1.2.0");
		m->declare("dx7.lib/version", "1.1.0");
		m->declare("envelopes.lib/adsre:author", "Julius O. Smith III");
		m->declare("envelopes.lib/adsre:licence", "STK-4.3");
		m->declare("envelopes.lib/author", "GRAME");
		m->declare("envelopes.lib/copyright", "GRAME");
		m->declare("envelopes.lib/license", "LGPL with exception");
		m->declare("envelopes.lib/name", "Faust Envelope Library");
		m->declare("envelopes.lib/version", "1.3.0");
		m->declare("fds.lib/author", "Romain Michon");
		m->declare("fds.lib/name", "Faust Finite Difference Schemes Library");
		m->declare("fds.lib/version", "1.1.0");
		m->declare("filename", "untitled.dsp");
		m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "1.7.1");
		m->declare("hoa.lib/author", "Pierre Guillot");
		m->declare("hoa.lib/copyright", "2012-2013 Guillot, Paris, Colafrancesco, CICM labex art H2H, U. Paris 8, 2019 Wargreen, 2022 Bonardi, Goutmann");
		m->declare("hoa.lib/name", "High Order Ambisonics library");
		m->declare("hoa.lib/version", "1.4.0");
		m->declare("interpolators.lib/name", "Faust Interpolator Library");
		m->declare("interpolators.lib/version", "1.4.0");
		m->declare("linearalgebra.lib/name", "Faust Linear Algebra Library");
		m->declare("linearalgebra.lib/version", "0.1.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.8.1");
		m->declare("mi.lib/author", "Romain Michon");
		m->declare("mi.lib/copyright", "2018-2020 GRAME / GIPSA-Lab");
		m->declare("mi.lib/name", "Faust mass-interaction physical modelling library");
		m->declare("mi.lib/version", "1.1.0");
		m->declare("misceffects.lib/name", "Misc Effects Library");
		m->declare("misceffects.lib/version", "2.5.1");
		m->declare("name", "untitled");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "1.4.1");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "1.6.0");
		m->declare("phaflangers.lib/name", "Faust Phaser and Flanger Library");
		m->declare("phaflangers.lib/version", "1.1.0");
		m->declare("physmodels.lib/name", "Faust Physical Models Library");
		m->declare("physmodels.lib/version", "1.2.0");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("quantizers.lib/name", "Faust Frequency Quantization Library");
		m->declare("quantizers.lib/version", "1.1.1");
		m->declare("reducemaps.lib/author", "Yann Orlarey");
		m->declare("reducemaps.lib/copyright", "Grame and Yann Orlarey");
		m->declare("reducemaps.lib/license", "LGPL with exception");
		m->declare("reducemaps.lib/name", "Reduce Library");
		m->declare("reducemaps.lib/version", "1.2.0");
		m->declare("reverbs.lib/name", "Faust Reverb Library");
		m->declare("reverbs.lib/version", "1.4.0");
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "1.2.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "1.6.0");
		m->declare("soundfiles.lib/name", "Faust Soundfile Library");
		m->declare("soundfiles.lib/version", "1.7.0");
		m->declare("spats.lib/name", "Faust Spatialization Library");
		m->declare("spats.lib/version", "1.2.0");
		m->declare("synths.lib/name", "Faust Synthesizer Library");
		m->declare("synths.lib/version", "1.1.0");
		m->declare("vaeffects.lib/name", "Faust Virtual Analog Filter Effect Library");
		m->declare("vaeffects.lib/version", "1.3.0");
		m->declare("wdmodels.lib/name", "Faust Wave Digital Model Library");
		m->declare("wdmodels.lib/version", "1.2.1");
		m->declare("webaudio.lib/author", "GRAME");
		m->declare("webaudio.lib/copyright", "GRAME");
		m->declare("webaudio.lib/license", "LGPL with exception");
		m->declare("webaudio.lib/name", "Faust WebAudio Filters Library");
		m->declare("webaudio.lib/version", "1.1.0");
	}

	virtual int getNumInputs() {
		return 0;
	}
	virtual int getNumOutputs() {
		return 1;
	}
	
	static void classInit(int sample_rate) {
		FMSynthAnalogSIG0* sig0 = newFMSynthAnalogSIG0();
		sig0->instanceInitFMSynthAnalogSIG0(sample_rate);
		sig0->fillFMSynthAnalogSIG0(65537, ftbl0FMSynthAnalogSIG0);
		deleteFMSynthAnalogSIG0(sig0);
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = 44.1f / fConst0;
		fConst2 = 1.0f - fConst1;
		fConst3 = 1.0f / fConst0;
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(2.0f);
		fHslider1 = FAUSTFLOAT(0.0f);
		fEntry0 = FAUSTFLOAT(4.4e+02f);
		fHslider2 = FAUSTFLOAT(0.0f);
		fHslider3 = FAUSTFLOAT(0.01f);
		fHslider4 = FAUSTFLOAT(0.6f);
		fHslider5 = FAUSTFLOAT(0.2f);
		fEntry1 = FAUSTFLOAT(1.0f);
	}
	
	virtual void instanceClear() {
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			iVec1[l2] = 0;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec4[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec5[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec3[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec2[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			iRec7[l7] = 0;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec6[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fRec1[l9] = 0.0f;
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
	
	virtual FMSynthAnalog* clone() {
		return new FMSynthAnalog();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("untitled");
		ui_interface->declare(&fHslider3, "BELA", "ANALOG_1");
		ui_interface->addHorizontalSlider("A", &fHslider3, FAUSTFLOAT(0.01f), FAUSTFLOAT(0.01f), FAUSTFLOAT(4.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider4, "BELA", "ANALOG_2");
		ui_interface->addHorizontalSlider("DR", &fHslider4, FAUSTFLOAT(0.6f), FAUSTFLOAT(0.01f), FAUSTFLOAT(8.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider5, "BELA", "ANALOG_3");
		ui_interface->addHorizontalSlider("S", &fHslider5, FAUSTFLOAT(0.2f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider1, "midi", "pitchwheel");
		ui_interface->addHorizontalSlider("bend", &fHslider1, FAUSTFLOAT(0.0f), FAUSTFLOAT(-2.0f), FAUSTFLOAT(2.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider2, "midi", "ctrl 1");
		ui_interface->addHorizontalSlider("feedb", &fHslider2, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fEntry0, "unit", "Hz");
		ui_interface->addNumEntry("freq", &fEntry0, FAUSTFLOAT(4.4e+02f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(2e+04f), FAUSTFLOAT(1.0f));
		ui_interface->addNumEntry("gain", &fEntry1, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider0, "BELA", "ANALOG_0");
		ui_interface->addHorizontalSlider("ratio", &fHslider0, FAUSTFLOAT(2.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = fConst1 * float(fHslider0);
		float fSlow1 = float(fEntry0) * std::pow(2.0f, 0.083333336f * float(fHslider1));
		float fSlow2 = fConst1 * float(fHslider2);
		float fSlow3 = fSlow1 + -1.0f;
		float fSlow4 = float(fHslider3);
		int iSlow5 = int(fConst0 * fSlow4);
		float fSlow6 = float(fHslider4);
		float fSlow7 = float(fHslider5);
		float fSlow8 = 1e+03f * float(fEntry1);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			iVec1[0] = 1;
			int iTemp0 = 1 - iVec1[1];
			fRec4[0] = fSlow0 + fConst2 * fRec4[1];
			fRec5[0] = fSlow2 + fConst2 * fRec5[1];
			float fTemp1 = ((iTemp0) ? 0.0f : fRec3[1] + fConst3 * (fSlow3 * fRec5[0] * fRec2[1] + fSlow1 * fRec4[0]));
			fRec3[0] = fTemp1 - std::floor(fTemp1);
			float fTemp2 = 65536.0f * fRec3[0];
			int iTemp3 = int(fTemp2);
			float fTemp4 = ftbl0FMSynthAnalogSIG0[std::max<int>(0, std::min<int>(iTemp3, 65536))];
			fRec2[0] = fTemp4 + (fTemp2 - std::floor(fTemp2)) * (ftbl0FMSynthAnalogSIG0[std::max<int>(0, std::min<int>(iTemp3 + 1, 65536))] - fTemp4);
			iRec7[0] = iRec7[1] + 1;
			int iTemp5 = (iRec7[0] < iSlow5) | (iTemp0 * (iTemp0 > 0));
			float fTemp6 = 0.1447178f * ((iTemp5) ? fSlow4 : fSlow6);
			int iTemp7 = std::fabs(fTemp6) < 1.1920929e-07f;
			float fTemp8 = ((iTemp7) ? 0.0f : std::exp(-(fConst3 / ((iTemp7) ? 1.0f : fTemp6))));
			fRec6[0] = (1.0f - fTemp8) * ((iTemp5) ? 1.0f : fSlow7) + fTemp8 * fRec6[1];
			float fTemp9 = ((iTemp0) ? 0.0f : fRec1[1] + fConst3 * (fSlow1 + fSlow8 * fRec6[0] * fRec2[0]));
			fRec1[0] = fTemp9 - std::floor(fTemp9);
			float fTemp10 = 65536.0f * fRec1[0];
			int iTemp11 = int(fTemp10);
			float fTemp12 = ftbl0FMSynthAnalogSIG0[std::max<int>(0, std::min<int>(iTemp11, 65536))];
			output0[i0] = FAUSTFLOAT(fRec6[0] * (fTemp12 + (fTemp10 - std::floor(fTemp10)) * (ftbl0FMSynthAnalogSIG0[std::max<int>(0, std::min<int>(iTemp11 + 1, 65536))] - fTemp12)));
			iVec1[1] = iVec1[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec3[1] = fRec3[0];
			fRec2[1] = fRec2[0];
			iRec7[1] = iRec7[0];
			fRec6[1] = fRec6[0];
			fRec1[1] = fRec1[0];
		}
	}

};

#endif
