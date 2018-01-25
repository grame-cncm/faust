/* ------------------------------------------------------------
author: "JOS"
license: "STK-4.3"
name: "FFT"
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

float mydsp_faustpower2_f(float value) {
	return (value * value);
	
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif
#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class mydsp : public dsp {
	
 private:
	
	FAUSTFLOAT fHslider0;
	int fSamplingFreq;
	float fConst0;
	FAUSTFLOAT fHslider1;
	int iVec0[2];
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT fHbargraph0;
	float fRec1[2];
	float fRec2[2];
	int iRec3[2];
	int IOTA;
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
	
	void metadata(Meta* m) { 
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "0.0");
		m->declare("author", "JOS");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("license", "STK-4.3");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "FFT");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
	}

	virtual int getNumInputs() {
		return 0;
		
	}
	virtual int getNumOutputs() {
		return 2;
		
	}
	virtual int getInputRate(int channel) {
		int rate;
		switch (channel) {
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
		fConst0 = (1000.0f / min(192000.0f, max(1.0f, float(fSamplingFreq))));
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(50.0f);
		fHslider1 = FAUSTFLOAT(100.0f);
		fHslider2 = FAUSTFLOAT(0.10000000000000001f);
		fHslider3 = FAUSTFLOAT(8.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec1[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec2[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			iRec3[l3] = 0;
			
		}
		IOTA = 0;
		for (int l4 = 0; (l4 < 32); l4 = (l4 + 1)) {
			fVec1[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec0[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec4[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec5[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec6[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec7[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec8[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec9[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec10[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec11[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec12[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec13[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec14[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec15[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec16[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec17[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec18[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec19[l21] = 0.0f;
			
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
		ui_interface->openVerticalBox("FFT");
		ui_interface->declare(0, "0", "");
		ui_interface->declare(0, "tooltip", "fft_spectral_level in Faust's analyzers.lib");
		ui_interface->openHorizontalBox("FFT SPECTRUM ANALYZER, 32 bands");
		ui_interface->declare(&fVbargraph0, "0", "");
		ui_interface->declare(&fVbargraph0, "tooltip", "FFT Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph0, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ff9ab30c480", &fVbargraph0, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph1, "1", "");
		ui_interface->declare(&fVbargraph1, "tooltip", "FFT Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph1, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ff9ab31cc70", &fVbargraph1, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph2, "2", "");
		ui_interface->declare(&fVbargraph2, "tooltip", "FFT Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph2, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ff9ab328820", &fVbargraph2, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph3, "3", "");
		ui_interface->declare(&fVbargraph3, "tooltip", "FFT Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph3, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ff9ab3341d0", &fVbargraph3, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph4, "4", "");
		ui_interface->declare(&fVbargraph4, "tooltip", "FFT Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph4, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ff9ab33c170", &fVbargraph4, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph5, "5", "");
		ui_interface->declare(&fVbargraph5, "tooltip", "FFT Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph5, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ff9ab347df0", &fVbargraph5, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph6, "6", "");
		ui_interface->declare(&fVbargraph6, "tooltip", "FFT Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph6, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ff9ab34eee0", &fVbargraph6, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph7, "7", "");
		ui_interface->declare(&fVbargraph7, "tooltip", "FFT Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph7, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ff9ab359af0", &fVbargraph7, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph8, "8", "");
		ui_interface->declare(&fVbargraph8, "tooltip", "FFT Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph8, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ff9ab35fa70", &fVbargraph8, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph9, "9", "");
		ui_interface->declare(&fVbargraph9, "tooltip", "FFT Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph9, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ff9ab366c90", &fVbargraph9, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph10, "10", "");
		ui_interface->declare(&fVbargraph10, "tooltip", "FFT Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph10, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ff9ab36e040", &fVbargraph10, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph11, "11", "");
		ui_interface->declare(&fVbargraph11, "tooltip", "FFT Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph11, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ff9ab375ca0", &fVbargraph11, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph12, "12", "");
		ui_interface->declare(&fVbargraph12, "tooltip", "FFT Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph12, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ff9ab37b230", &fVbargraph12, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph13, "13", "");
		ui_interface->declare(&fVbargraph13, "tooltip", "FFT Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph13, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ff9ab382e80", &fVbargraph13, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph14, "14", "");
		ui_interface->declare(&fVbargraph14, "tooltip", "FFT Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph14, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ff9ab389e30", &fVbargraph14, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph15, "15", "");
		ui_interface->declare(&fVbargraph15, "tooltip", "FFT Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph15, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ff9ab391a70", &fVbargraph15, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph16, "16", "");
		ui_interface->declare(&fVbargraph16, "tooltip", "FFT Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph16, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ff9ab396910", &fVbargraph16, -50.0f, 10.0f);
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("FFT SPECTRUM ANALYZER CONTROLS");
		ui_interface->declare(&fHslider1, "0", "");
		ui_interface->declare(&fHslider1, "scale", "log");
		ui_interface->declare(&fHslider1, "tooltip", "band-level averaging time in milliseconds");
		ui_interface->declare(&fHslider1, "unit", "ms");
		ui_interface->addHorizontalSlider("Level Averaging Time", &fHslider1, 100.0f, 1.0f, 10000.0f, 1.0f);
		ui_interface->declare(&fHslider0, "1", "");
		ui_interface->declare(&fHslider0, "tooltip", "Level offset in decibels");
		ui_interface->declare(&fHslider0, "unit", "dB");
		ui_interface->addHorizontalSlider("Level dB Offset", &fHslider0, 50.0f, -50.0f, 100.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->declare(&fHslider3, "2", "");
		ui_interface->addHorizontalSlider("FFT Bin Number", &fHslider3, 8.0f, 0.0f, 16.0f, 0.00100000005f);
		ui_interface->declare(&fHbargraph0, "3", "");
		ui_interface->addHorizontalBargraph("Measured FFT Bin Number", &fHbargraph0, 0.0f, 16.0f);
		ui_interface->declare(&fHslider2, "4", "");
		ui_interface->addHorizontalSlider("Amplitude", &fHslider2, 0.100000001f, 0.0f, 1.0f, 0.00100000005f);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = float(fHslider0);
		float fSlow1 = expf((0.0f - (fConst0 / float(fHslider1))));
		float fSlow2 = (10.0f * (1.0f - fSlow1));
		float fSlow3 = float(fHslider2);
		int iSlow4 = int(float(fHslider3));
		fHbargraph0 = FAUSTFLOAT(iSlow4);
		int iSlow5 = (iSlow4 == 0);
		int iSlow6 = (iSlow4 == 16);
		float fSlow7 = (0.196349546f * float(iSlow4));
		float fSlow8 = sinf(fSlow7);
		float fSlow9 = cosf(fSlow7);
		float fSlow10 = (0.0f - fSlow8);
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			fRec1[0] = ((fSlow8 * fRec2[1]) + (fSlow9 * fRec1[1]));
			fRec2[0] = (((fSlow9 * fRec2[1]) + (fSlow10 * fRec1[1])) + float((1 - iVec0[1])));
			iRec3[0] = (1 - (iVec0[1] + iRec3[1]));
			float fTemp0 = (fSlow3 * (iSlow5?1.0f:(iSlow6?float(iRec3[0]):(2.0f * fRec2[0]))));
			fVec1[(IOTA & 31)] = fTemp0;
			float fTemp1 = (fTemp0 + fVec1[((IOTA - 16) & 31)]);
			float fTemp2 = (fVec1[((IOTA - 24) & 31)] + (fTemp1 + fVec1[((IOTA - 8) & 31)]));
			float fTemp3 = (fVec1[((IOTA - 28) & 31)] + (fVec1[((IOTA - 12) & 31)] + (fVec1[((IOTA - 20) & 31)] + (fVec1[((IOTA - 4) & 31)] + fTemp2))));
			float fTemp4 = (fVec1[((IOTA - 30) & 31)] + (fVec1[((IOTA - 14) & 31)] + (fVec1[((IOTA - 22) & 31)] + (fVec1[((IOTA - 6) & 31)] + (fVec1[((IOTA - 26) & 31)] + (fVec1[((IOTA - 10) & 31)] + (fVec1[((IOTA - 18) & 31)] + (fVec1[((IOTA - 2) & 31)] + fTemp3))))))));
			fRec0[0] = ((fSlow1 * fRec0[1]) + (fSlow2 * log10f(max(1.00000001e-07f, mydsp_faustpower2_f(fabsf((fVec1[((IOTA - 31) & 31)] + (fVec1[((IOTA - 15) & 31)] + (fVec1[((IOTA - 23) & 31)] + (fVec1[((IOTA - 7) & 31)] + (fVec1[((IOTA - 27) & 31)] + (fVec1[((IOTA - 11) & 31)] + (fVec1[((IOTA - 19) & 31)] + (fVec1[((IOTA - 3) & 31)] + (fVec1[((IOTA - 29) & 31)] + (fVec1[((IOTA - 13) & 31)] + (fVec1[((IOTA - 21) & 31)] + (fVec1[((IOTA - 5) & 31)] + (fVec1[((IOTA - 25) & 31)] + (fVec1[((IOTA - 9) & 31)] + (fVec1[((IOTA - 17) & 31)] + (fVec1[((IOTA - 1) & 31)] + fTemp4))))))))))))))))))))));
			fVbargraph0 = FAUSTFLOAT((fSlow0 + fRec0[0]));
			float fTemp5 = (fVec1[((IOTA - 15) & 31)] - fVec1[((IOTA - 31) & 31)]);
			float fTemp6 = (0.0f - fTemp5);
			float fTemp7 = (fVec1[((IOTA - 7) & 31)] - fVec1[((IOTA - 23) & 31)]);
			float fTemp8 = (0.707106769f * fTemp7);
			float fTemp9 = ((fVec1[((IOTA - 27) & 31)] + (0.707106769f * fTemp6)) - (fVec1[((IOTA - 11) & 31)] + fTemp8));
			float fTemp10 = (0.923879504f * fTemp9);
			float fTemp11 = (fVec1[((IOTA - 13) & 31)] - fVec1[((IOTA - 29) & 31)]);
			float fTemp12 = (0.0f - fTemp11);
			float fTemp13 = (fVec1[((IOTA - 25) & 31)] + (0.707106769f * fTemp12));
			float fTemp14 = (fVec1[((IOTA - 5) & 31)] - fVec1[((IOTA - 21) & 31)]);
			float fTemp15 = (0.707106769f * fTemp14);
			float fTemp16 = (fVec1[((IOTA - 9) & 31)] + fTemp15);
			float fTemp17 = (0.707106769f * fTemp6);
			float fTemp18 = (0.707106769f * fTemp7);
			float fTemp19 = ((fTemp17 + (fVec1[((IOTA - 3) & 31)] + fTemp18)) - fVec1[((IOTA - 19) & 31)]);
			float fTemp20 = ((fTemp10 + fTemp13) - (fTemp16 + (0.382683426f * fTemp19)));
			float fTemp21 = (fVec1[((IOTA - 14) & 31)] - fVec1[((IOTA - 30) & 31)]);
			float fTemp22 = (0.0f - fTemp21);
			float fTemp23 = (fVec1[((IOTA - 6) & 31)] - fVec1[((IOTA - 22) & 31)]);
			float fTemp24 = (0.707106769f * fTemp23);
			float fTemp25 = ((fVec1[((IOTA - 26) & 31)] + (0.707106769f * fTemp22)) - (fVec1[((IOTA - 10) & 31)] + fTemp24));
			float fTemp26 = (fVec1[((IOTA - 12) & 31)] - fVec1[((IOTA - 28) & 31)]);
			float fTemp27 = (0.0f - fTemp26);
			float fTemp28 = (0.707106769f * fTemp27);
			float fTemp29 = (fVec1[((IOTA - 4) & 31)] - fVec1[((IOTA - 20) & 31)]);
			float fTemp30 = (0.707106769f * fTemp29);
			float fTemp31 = (fTemp28 + (fTemp0 + fTemp30));
			float fTemp32 = (0.707106769f * fTemp22);
			float fTemp33 = (0.707106769f * fTemp23);
			float fTemp34 = ((fTemp32 + (fVec1[((IOTA - 2) & 31)] + fTemp33)) - fVec1[((IOTA - 18) & 31)]);
			float fTemp35 = (0.923879504f * fTemp34);
			float fTemp36 = (0.707106769f * fTemp12);
			float fTemp37 = (0.707106769f * fTemp14);
			float fTemp38 = (fTemp36 + (fVec1[((IOTA - 1) & 31)] + fTemp37));
			float fTemp39 = (0.923879504f * fTemp19);
			float fTemp40 = (((0.382683426f * fTemp9) + (fTemp38 + fTemp39)) - fVec1[((IOTA - 17) & 31)]);
			float fTemp41 = (0.923879504f * fTemp25);
			float fTemp42 = (fVec1[((IOTA - 24) & 31)] + (0.707106769f * fTemp27));
			float fTemp43 = (0.707106769f * fTemp29);
			float fTemp44 = (fVec1[((IOTA - 8) & 31)] + fTemp43);
			fRec4[0] = ((fSlow1 * fRec4[1]) + (fSlow2 * log10f(max(1.00000001e-07f, (mydsp_faustpower2_f(fabsf((((0.195090324f * fTemp20) + (((0.382683426f * fTemp25) + (fTemp31 + fTemp35)) + (0.980785251f * fTemp40))) - fVec1[((IOTA - 16) & 31)]))) + mydsp_faustpower2_f(fabsf((((0.980785251f * fTemp20) + (fTemp41 + fTemp42)) - ((fTemp44 + (0.382683426f * fTemp34)) + (0.195090324f * fTemp40))))))))));
			fVbargraph1 = FAUSTFLOAT((fSlow0 + fRec4[0]));
			float fTemp45 = (fVec1[((IOTA - 13) & 31)] + fVec1[((IOTA - 29) & 31)]);
			float fTemp46 = (fVec1[((IOTA - 7) & 31)] + fVec1[((IOTA - 23) & 31)]);
			float fTemp47 = (fTemp46 - (fVec1[((IOTA - 15) & 31)] + fVec1[((IOTA - 31) & 31)]));
			float fTemp48 = (0.0f - fTemp47);
			float fTemp49 = (fVec1[((IOTA - 5) & 31)] + fVec1[((IOTA - 21) & 31)]);
			float fTemp50 = (fVec1[((IOTA - 3) & 31)] + fVec1[((IOTA - 19) & 31)]);
			float fTemp51 = (fTemp50 - (fVec1[((IOTA - 11) & 31)] + fVec1[((IOTA - 27) & 31)]));
			float fTemp52 = (0.707106769f * fTemp51);
			float fTemp53 = ((fTemp45 + (0.707106769f * fTemp48)) - (fTemp49 + fTemp52));
			float fTemp54 = (fVec1[((IOTA - 6) & 31)] + fVec1[((IOTA - 22) & 31)]);
			float fTemp55 = (fTemp54 - (fVec1[((IOTA - 14) & 31)] + fVec1[((IOTA - 30) & 31)]));
			float fTemp56 = (0.0f - fTemp55);
			float fTemp57 = (0.707106769f * fTemp56);
			float fTemp58 = (fVec1[((IOTA - 2) & 31)] + fVec1[((IOTA - 18) & 31)]);
			float fTemp59 = (fTemp58 - (fVec1[((IOTA - 10) & 31)] + fVec1[((IOTA - 26) & 31)]));
			float fTemp60 = (0.707106769f * fTemp59);
			float fTemp61 = (0.707106769f * fTemp48);
			float fTemp62 = (fVec1[((IOTA - 1) & 31)] + fVec1[((IOTA - 17) & 31)]);
			float fTemp63 = (0.707106769f * fTemp51);
			float fTemp64 = (fVec1[((IOTA - 9) & 31)] + fVec1[((IOTA - 25) & 31)]);
			float fTemp65 = ((fTemp61 + (fTemp62 + fTemp63)) - fTemp64);
			float fTemp66 = (fVec1[((IOTA - 8) & 31)] + fVec1[((IOTA - 24) & 31)]);
			float fTemp67 = (fVec1[((IOTA - 12) & 31)] + fVec1[((IOTA - 28) & 31)]);
			float fTemp68 = (fVec1[((IOTA - 4) & 31)] + fVec1[((IOTA - 20) & 31)]);
			float fTemp69 = (0.707106769f * fTemp59);
			fRec5[0] = ((fSlow1 * fRec5[1]) + (fSlow2 * log10f(max(1.00000001e-07f, (mydsp_faustpower2_f(fabsf((((0.382683426f * fTemp53) + ((fTemp57 + (fTemp1 + fTemp60)) + (0.923879504f * fTemp65))) - fTemp66))) + mydsp_faustpower2_f(fabsf((((0.923879504f * fTemp53) + (fTemp67 + (0.707106769f * fTemp56))) - ((0.382683426f * fTemp65) + (fTemp68 + fTemp69))))))))));
			fVbargraph2 = FAUSTFLOAT((fSlow0 + fRec5[0]));
			float fTemp70 = (0.707106769f * fTemp5);
			float fTemp71 = (fVec1[((IOTA - 11) & 31)] - (fTemp70 + (fVec1[((IOTA - 27) & 31)] + fTemp18)));
			float fTemp72 = (0.707106769f * fTemp11);
			float fTemp73 = (fTemp72 + (fVec1[((IOTA - 25) & 31)] + fTemp37));
			float fTemp74 = ((fVec1[((IOTA - 3) & 31)] + (0.707106769f * fTemp5)) - (fVec1[((IOTA - 19) & 31)] + fTemp8));
			float fTemp75 = ((fVec1[((IOTA - 9) & 31)] + (0.382683426f * fTemp71)) - (fTemp73 + (0.923879504f * fTemp74)));
			float fTemp76 = (0.707106769f * fTemp21);
			float fTemp77 = (fVec1[((IOTA - 10) & 31)] - (fTemp76 + (fVec1[((IOTA - 26) & 31)] + fTemp33)));
			float fTemp78 = (fTemp0 + (0.707106769f * fTemp26));
			float fTemp79 = ((fVec1[((IOTA - 2) & 31)] + (0.707106769f * fTemp21)) - (fVec1[((IOTA - 18) & 31)] + fTemp24));
			float fTemp80 = (fVec1[((IOTA - 1) & 31)] + (0.707106769f * fTemp11));
			float fTemp81 = (fVec1[((IOTA - 17) & 31)] + fTemp15);
			float fTemp82 = (((0.923879504f * fTemp71) + (fTemp80 + (0.382683426f * fTemp74))) - fTemp81);
			float fTemp83 = (fVec1[((IOTA - 16) & 31)] + fTemp43);
			float fTemp84 = (0.707106769f * fTemp26);
			float fTemp85 = (fTemp84 + (fVec1[((IOTA - 24) & 31)] + fTemp30));
			fRec6[0] = ((fSlow1 * fRec6[1]) + (fSlow2 * log10f(max(1.00000001e-07f, (mydsp_faustpower2_f(fabsf((((0.555570245f * fTemp75) + (((0.923879504f * fTemp77) + (fTemp78 + (0.382683426f * fTemp79))) + (0.831469595f * fTemp82))) - fTemp83))) + mydsp_faustpower2_f(fabsf((((0.831469595f * fTemp75) + (fVec1[((IOTA - 8) & 31)] + (0.382683426f * fTemp77))) - ((fTemp85 + (0.923879504f * fTemp79)) + (0.555570245f * fTemp82))))))))));
			fVbargraph3 = FAUSTFLOAT((fSlow0 + fRec6[0]));
			float fTemp86 = (fVec1[((IOTA - 27) & 31)] + (fTemp50 + fVec1[((IOTA - 11) & 31)]));
			float fTemp87 = (fTemp86 - (fVec1[((IOTA - 31) & 31)] + (fTemp46 + fVec1[((IOTA - 15) & 31)])));
			float fTemp88 = (0.0f - fTemp87);
			float fTemp89 = (fVec1[((IOTA - 25) & 31)] + (fTemp62 + fVec1[((IOTA - 9) & 31)]));
			float fTemp90 = (fTemp89 - (fVec1[((IOTA - 29) & 31)] + (fTemp49 + fVec1[((IOTA - 13) & 31)])));
			float fTemp91 = (0.707106769f * fTemp90);
			float fTemp92 = (fVec1[((IOTA - 28) & 31)] + (fTemp68 + fVec1[((IOTA - 12) & 31)]));
			float fTemp93 = (fVec1[((IOTA - 30) & 31)] + (fTemp54 + fVec1[((IOTA - 14) & 31)]));
			float fTemp94 = (fVec1[((IOTA - 26) & 31)] + (fTemp58 + fVec1[((IOTA - 10) & 31)]));
			float fTemp95 = (0.707106769f * fTemp90);
			fRec7[0] = ((fSlow1 * fRec7[1]) + (fSlow2 * log10f(max(1.00000001e-07f, (mydsp_faustpower2_f(fabsf((((0.707106769f * fTemp88) + (fTemp2 + fTemp91)) - fTemp92))) + mydsp_faustpower2_f(fabsf(((fTemp93 + (0.707106769f * fTemp88)) - (fTemp94 + fTemp95)))))))));
			fVbargraph4 = FAUSTFLOAT((fSlow0 + fRec7[0]));
			float fTemp96 = (fVec1[((IOTA - 25) & 31)] + fTemp15);
			float fTemp97 = ((fVec1[((IOTA - 27) & 31)] + fTemp8) - (fVec1[((IOTA - 11) & 31)] + (0.707106769f * fTemp6)));
			float fTemp98 = (fVec1[((IOTA - 9) & 31)] + (0.707106769f * fTemp12));
			float fTemp99 = (0.707106769f * fTemp7);
			float fTemp100 = (fVec1[((IOTA - 3) & 31)] - (fTemp17 + (fVec1[((IOTA - 19) & 31)] + fTemp99)));
			float fTemp101 = (fTemp96 - ((0.382683426f * fTemp97) + (fTemp98 + (0.923879504f * fTemp100))));
			float fTemp102 = ((fVec1[((IOTA - 26) & 31)] + fTemp24) - (fVec1[((IOTA - 10) & 31)] + (0.707106769f * fTemp22)));
			float fTemp103 = (0.707106769f * fTemp14);
			float fTemp104 = (fTemp36 + (fVec1[((IOTA - 17) & 31)] + fTemp103));
			float fTemp105 = ((fVec1[((IOTA - 1) & 31)] + (0.923879504f * fTemp97)) - (fTemp104 + (0.382683426f * fTemp100)));
			float fTemp106 = (0.707106769f * fTemp29);
			float fTemp107 = (fTemp28 + (fVec1[((IOTA - 16) & 31)] + fTemp106));
			float fTemp108 = (0.707106769f * fTemp23);
			float fTemp109 = (fVec1[((IOTA - 2) & 31)] - (fTemp32 + (fVec1[((IOTA - 18) & 31)] + fTemp108)));
			float fTemp110 = (fVec1[((IOTA - 24) & 31)] + fTemp43);
			float fTemp111 = (fVec1[((IOTA - 8) & 31)] + (0.707106769f * fTemp27));
			fRec8[0] = ((fSlow1 * fRec8[1]) + (fSlow2 * log10f(max(1.00000001e-07f, (mydsp_faustpower2_f(fabsf((((0.831469595f * fTemp101) + ((fTemp0 + (0.923879504f * fTemp102)) + (0.555570245f * fTemp105))) - (fTemp107 + (0.382683426f * fTemp109))))) + mydsp_faustpower2_f(fabsf(((fTemp110 + (0.555570245f * fTemp101)) - ((0.831469595f * fTemp105) + ((0.382683426f * fTemp102) + (fTemp111 + (0.923879504f * fTemp109))))))))))));
			fVbargraph5 = FAUSTFLOAT((fSlow0 + fRec8[0]));
			float fTemp112 = (0.707106769f * fTemp47);
			float fTemp113 = (fTemp49 - (fTemp112 + (fTemp45 + fTemp63)));
			float fTemp114 = ((fTemp62 + (0.707106769f * fTemp47)) - (fTemp64 + fTemp52));
			float fTemp115 = (0.707106769f * fTemp55);
			fRec9[0] = ((fSlow1 * fRec9[1]) + (fSlow2 * log10f(max(1.00000001e-07f, (mydsp_faustpower2_f(fabsf((((0.923879504f * fTemp113) + ((fTemp1 + (0.707106769f * fTemp55)) + (0.382683426f * fTemp114))) - (fTemp66 + fTemp69)))) + mydsp_faustpower2_f(fabsf(((fTemp68 + (0.382683426f * fTemp113)) - ((0.923879504f * fTemp114) + (fTemp115 + (fTemp67 + fTemp60)))))))))));
			fVbargraph6 = FAUSTFLOAT((fSlow0 + fRec9[0]));
			float fTemp116 = (fTemp72 + (fVec1[((IOTA - 9) & 31)] + fTemp103));
			float fTemp117 = ((fTemp70 + (fVec1[((IOTA - 11) & 31)] + fTemp99)) - fVec1[((IOTA - 27) & 31)]);
			float fTemp118 = ((fVec1[((IOTA - 3) & 31)] + fTemp8) - (fVec1[((IOTA - 19) & 31)] + (0.707106769f * fTemp5)));
			float fTemp119 = (fTemp116 - ((0.923879504f * fTemp117) + (fVec1[((IOTA - 25) & 31)] + (0.382683426f * fTemp118))));
			float fTemp120 = (fTemp0 + fTemp43);
			float fTemp121 = ((fTemp76 + (fVec1[((IOTA - 10) & 31)] + fTemp108)) - fVec1[((IOTA - 26) & 31)]);
			float fTemp122 = (fVec1[((IOTA - 1) & 31)] + fTemp15);
			float fTemp123 = (fVec1[((IOTA - 17) & 31)] + (0.707106769f * fTemp11));
			float fTemp124 = ((fTemp122 + (0.382683426f * fTemp117)) - (fTemp123 + (0.923879504f * fTemp118)));
			float fTemp125 = (fVec1[((IOTA - 16) & 31)] + (0.707106769f * fTemp26));
			float fTemp126 = ((fVec1[((IOTA - 2) & 31)] + fTemp24) - (fVec1[((IOTA - 18) & 31)] + (0.707106769f * fTemp21)));
			float fTemp127 = (fTemp84 + (fVec1[((IOTA - 8) & 31)] + fTemp106));
			fRec10[0] = ((fSlow1 * fRec10[1]) + (fSlow2 * log10f(max(1.00000001e-07f, (mydsp_faustpower2_f(fabsf((((0.980785251f * fTemp119) + ((fTemp120 + (0.382683426f * fTemp121)) + (0.195090324f * fTemp124))) - (fTemp125 + (0.923879504f * fTemp126))))) + mydsp_faustpower2_f(fabsf(((fTemp127 + (0.195090324f * fTemp119)) - ((0.980785251f * fTemp124) + ((0.923879504f * fTemp121) + (fVec1[((IOTA - 24) & 31)] + (0.382683426f * fTemp126))))))))))));
			fVbargraph7 = FAUSTFLOAT((fSlow0 + fRec10[0]));
			float fTemp128 = (fVec1[((IOTA - 29) & 31)] + (fVec1[((IOTA - 13) & 31)] + (fVec1[((IOTA - 21) & 31)] + (fVec1[((IOTA - 5) & 31)] + fTemp89))));
			fRec11[0] = ((fSlow1 * fRec11[1]) + (fSlow2 * log10f(max(1.00000001e-07f, (mydsp_faustpower2_f(fabsf((fTemp3 - (fVec1[((IOTA - 30) & 31)] + (fVec1[((IOTA - 14) & 31)] + (fVec1[((IOTA - 22) & 31)] + (fVec1[((IOTA - 6) & 31)] + fTemp94))))))) + mydsp_faustpower2_f(fabsf((0.0f - (fTemp128 - (fVec1[((IOTA - 31) & 31)] + (fVec1[((IOTA - 15) & 31)] + (fVec1[((IOTA - 23) & 31)] + (fVec1[((IOTA - 7) & 31)] + fTemp86)))))))))))));
			fVbargraph8 = FAUSTFLOAT((fSlow0 + fRec11[0]));
			float fTemp129 = ((fTemp13 + (0.382683426f * fTemp19)) - (fTemp10 + fTemp16));
			float fTemp130 = (fTemp38 - ((0.382683426f * fTemp9) + (fVec1[((IOTA - 17) & 31)] + fTemp39)));
			fRec12[0] = ((fSlow1 * fRec12[1]) + (fSlow2 * log10f(max(1.00000001e-07f, (mydsp_faustpower2_f(fabsf(((fTemp31 + (0.980785251f * fTemp129)) - (((0.382683426f * fTemp25) + (fVec1[((IOTA - 16) & 31)] + fTemp35)) + (0.195090324f * fTemp130))))) + mydsp_faustpower2_f(fabsf(((fTemp42 + (0.382683426f * fTemp34)) - ((0.195090324f * fTemp129) + ((fTemp41 + fTemp44) + (0.980785251f * fTemp130)))))))))));
			fVbargraph9 = FAUSTFLOAT((fSlow0 + fRec12[0]));
			float fTemp131 = ((fTemp45 + fTemp52) - (fTemp49 + (0.707106769f * fTemp48)));
			float fTemp132 = (0.707106769f * fTemp59);
			float fTemp133 = (0.707106769f * fTemp51);
			float fTemp134 = (fTemp62 - (fTemp61 + (fTemp64 + fTemp133)));
			fRec13[0] = ((fSlow1 * fRec13[1]) + (fSlow2 * log10f(max(1.00000001e-07f, (mydsp_faustpower2_f(fabsf(((fTemp1 + (0.923879504f * fTemp131)) - ((fTemp57 + (fTemp66 + fTemp132)) + (0.382683426f * fTemp134))))) + mydsp_faustpower2_f(fabsf(((fTemp67 + fTemp69) - ((0.382683426f * fTemp131) + ((fTemp68 + (0.707106769f * fTemp56)) + (0.923879504f * fTemp134)))))))))));
			fVbargraph10 = FAUSTFLOAT((fSlow0 + fRec13[0]));
			float fTemp135 = ((fVec1[((IOTA - 9) & 31)] + (0.923879504f * fTemp74)) - (fTemp73 + (0.382683426f * fTemp71)));
			float fTemp136 = (fTemp80 - ((0.923879504f * fTemp71) + (fTemp81 + (0.382683426f * fTemp74))));
			fRec14[0] = ((fSlow1 * fRec14[1]) + (fSlow2 * log10f(max(1.00000001e-07f, (mydsp_faustpower2_f(fabsf(((fTemp78 + (0.831469595f * fTemp135)) - (((0.923879504f * fTemp77) + (fTemp83 + (0.382683426f * fTemp79))) + (0.555570245f * fTemp136))))) + mydsp_faustpower2_f(fabsf(((fVec1[((IOTA - 8) & 31)] + (0.923879504f * fTemp79)) - ((0.555570245f * fTemp135) + ((fTemp85 + (0.382683426f * fTemp77)) + (0.831469595f * fTemp136)))))))))));
			fVbargraph11 = FAUSTFLOAT((fSlow0 + fRec14[0]));
			fRec15[0] = ((fSlow1 * fRec15[1]) + (fSlow2 * log10f(max(1.00000001e-07f, (mydsp_faustpower2_f(fabsf(((fTemp2 + (0.707106769f * fTemp87)) - (fTemp92 + fTemp95)))) + mydsp_faustpower2_f(fabsf((fTemp94 - ((0.707106769f * fTemp87) + (fTemp93 + fTemp91))))))))));
			fVbargraph12 = FAUSTFLOAT((fSlow0 + fRec15[0]));
			float fTemp137 = (((0.382683426f * fTemp97) + (fTemp96 + (0.923879504f * fTemp100))) - fTemp98);
			float fTemp138 = ((fVec1[((IOTA - 1) & 31)] + (0.382683426f * fTemp100)) - (fTemp104 + (0.923879504f * fTemp97)));
			fRec16[0] = ((fSlow1 * fRec16[1]) + (fSlow2 * log10f(max(1.00000001e-07f, (mydsp_faustpower2_f(fabsf((((fTemp0 + (0.382683426f * fTemp109)) + (0.555570245f * fTemp137)) - ((fTemp107 + (0.923879504f * fTemp102)) + (0.831469595f * fTemp138))))) + mydsp_faustpower2_f(fabsf((((0.382683426f * fTemp102) + (fTemp110 + (0.923879504f * fTemp109))) - ((0.831469595f * fTemp137) + (fTemp111 + (0.555570245f * fTemp138)))))))))));
			fVbargraph13 = FAUSTFLOAT((fSlow0 + fRec16[0]));
			float fTemp139 = ((fTemp112 + (fTemp49 + fTemp133)) - fTemp45);
			float fTemp140 = ((fTemp62 + fTemp52) - (fTemp64 + (0.707106769f * fTemp47)));
			fRec17[0] = ((fSlow1 * fRec17[1]) + (fSlow2 * log10f(max(1.00000001e-07f, (mydsp_faustpower2_f(fabsf((((fTemp1 + fTemp69) + (0.382683426f * fTemp139)) - ((fTemp66 + (0.707106769f * fTemp55)) + (0.923879504f * fTemp140))))) + mydsp_faustpower2_f(fabsf(((fTemp115 + (fTemp68 + fTemp132)) - ((0.923879504f * fTemp139) + (fTemp67 + (0.382683426f * fTemp140)))))))))));
			fVbargraph14 = FAUSTFLOAT((fSlow0 + fRec17[0]));
			float fTemp141 = (((0.923879504f * fTemp117) + (fTemp116 + (0.382683426f * fTemp118))) - fVec1[((IOTA - 25) & 31)]);
			float fTemp142 = ((fTemp122 + (0.923879504f * fTemp118)) - (fTemp123 + (0.382683426f * fTemp117)));
			fRec18[0] = ((fSlow1 * fRec18[1]) + (fSlow2 * log10f(max(1.00000001e-07f, (mydsp_faustpower2_f(fabsf((((fTemp120 + (0.923879504f * fTemp126)) + (0.195090324f * fTemp141)) - ((fTemp125 + (0.382683426f * fTemp121)) + (0.980785251f * fTemp142))))) + mydsp_faustpower2_f(fabsf((((0.923879504f * fTemp121) + (fTemp127 + (0.382683426f * fTemp126))) - ((0.980785251f * fTemp141) + (fVec1[((IOTA - 24) & 31)] + (0.195090324f * fTemp142)))))))))));
			fVbargraph15 = FAUSTFLOAT((fSlow0 + fRec18[0]));
			fRec19[0] = ((fSlow1 * fRec19[1]) + (fSlow2 * log10f(max(1.00000001e-07f, mydsp_faustpower2_f(fabsf((fTemp4 - (fVec1[((IOTA - 31) & 31)] + (fVec1[((IOTA - 15) & 31)] + (fVec1[((IOTA - 23) & 31)] + (fVec1[((IOTA - 7) & 31)] + (fVec1[((IOTA - 27) & 31)] + (fVec1[((IOTA - 11) & 31)] + (fVec1[((IOTA - 19) & 31)] + (fVec1[((IOTA - 3) & 31)] + fTemp128)))))))))))))));
			fVbargraph16 = FAUSTFLOAT((fSlow0 + fRec19[0]));
			output0[i] = FAUSTFLOAT(fTemp0);
			output1[i] = FAUSTFLOAT(fTemp0);
			iVec0[1] = iVec0[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			iRec3[1] = iRec3[0];
			IOTA = (IOTA + 1);
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

#endif
