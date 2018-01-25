/* ------------------------------------------------------------
copyright: "(c)Mike Olsen, CCRMA (Stanford University)"
license: "MIT"
name: "Vocal FOF"
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


class mydspSIG0 {
	
  private:
	
	int iRec9[2];
	
  public:
	
	int getNumInputsmydspSIG0() {
		return 0;
		
	}
	int getNumOutputsmydspSIG0() {
		return 1;
		
	}
	int getInputRatemydspSIG0(int channel) {
		int rate;
		switch (channel) {
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	int getOutputRatemydspSIG0(int channel) {
		int rate;
		switch (channel) {
			case 0: {
				rate = 0;
				break;
			}
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	
	void instanceInitmydspSIG0(int samplingFreq) {
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			iRec9[l12] = 0;
			
		}
		
	}
	
	void fillmydspSIG0(int count, float* output) {
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec9[0] = (iRec9[1] + 1);
			output[i] = sinf((9.58738019e-05f * float((iRec9[0] + -1))));
			iRec9[1] = iRec9[0];
			
		}
		
	}
};

mydspSIG0* newmydspSIG0() { return (mydspSIG0*)new mydspSIG0(); }
void deletemydspSIG0(mydspSIG0* dsp) { delete dsp; }

static float ftbl0mydspSIG0[65536];

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
	int iVec0[2];
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	float fConst2;
	FAUSTFLOAT fHslider3;
	float fRec2[2];
	float fRec3[2];
	float fVec1[2];
	float fRec1[2];
	int iVec2[2];
	float fConst3;
	float fConst4;
	float fConst5;
	FAUSTFLOAT fHslider4;
	float fRec5[2];
	FAUSTFLOAT fHslider5;
	float fRec6[2];
	float fRec7[2];
	float fRec4[2];
	float fRec8[2];
	float fRec0[3];
	float fConst6;
	float fRec11[2];
	float fRec10[2];
	float fRec13[2];
	float fRec14[2];
	float fRec12[3];
	float fRec15[2];
	float fRec17[2];
	float fRec18[2];
	float fRec16[3];
	float fRec19[2];
	float fRec21[2];
	float fRec22[2];
	float fRec20[3];
	float fRec23[2];
	float fRec25[2];
	float fRec26[2];
	float fRec24[3];
	float fRec27[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("copyright", "(c)Mike Olsen, CCRMA (Stanford University)");
		m->declare("description", "FOF vocal synthesizer.");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("license", "MIT");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "Vocal FOF");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
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
		mydspSIG0* sig0 = newmydspSIG0();
		sig0->instanceInitmydspSIG0(samplingFreq);
		sig0->fillmydspSIG0(65536, ftbl0mydspSIG0);
		deletemydspSIG0(sig0);
		
	}
	
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(192000.0f, max(1.0f, float(fSamplingFreq)));
		fConst1 = (1.0f / fConst0);
		fConst2 = (6.28318548f / fConst0);
		fConst3 = (3.14159274f / fConst0);
		fConst4 = expf((0.0f - (1000.0f / fConst0)));
		fConst5 = (1.0f - fConst4);
		fConst6 = (1.0f / fConst0);
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.90000000000000002f);
		fHslider1 = FAUSTFLOAT(440.0f);
		fHslider2 = FAUSTFLOAT(0.5f);
		fHslider3 = FAUSTFLOAT(6.0f);
		fHslider4 = FAUSTFLOAT(0.0f);
		fHslider5 = FAUSTFLOAT(0.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec2[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec3[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fVec1[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec1[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			iVec2[l5] = 0;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec5[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec6[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec7[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec4[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec8[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 3); l11 = (l11 + 1)) {
			fRec0[l11] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec11[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec10[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec13[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec14[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 3); l17 = (l17 + 1)) {
			fRec12[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec15[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec17[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec18[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 3); l21 = (l21 + 1)) {
			fRec16[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec19[l22] = 0.0f;
			
		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec21[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fRec22[l24] = 0.0f;
			
		}
		for (int l25 = 0; (l25 < 3); l25 = (l25 + 1)) {
			fRec20[l25] = 0.0f;
			
		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fRec23[l26] = 0.0f;
			
		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fRec25[l27] = 0.0f;
			
		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fRec26[l28] = 0.0f;
			
		}
		for (int l29 = 0; (l29 < 3); l29 = (l29 + 1)) {
			fRec24[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fRec27[l30] = 0.0f;
			
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
		ui_interface->openVerticalBox("vocal");
		ui_interface->declare(&fHslider1, "0", "");
		ui_interface->addHorizontalSlider("freq", &fHslider1, 440.0f, 50.0f, 1000.0f, 0.00999999978f);
		ui_interface->declare(&fHslider0, "1", "");
		ui_interface->addHorizontalSlider("gain", &fHslider0, 0.899999976f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fHslider5, "2", "");
		ui_interface->addHorizontalSlider("voiceType", &fHslider5, 0.0f, 0.0f, 4.0f, 1.0f);
		ui_interface->declare(&fHslider4, "3", "");
		ui_interface->addHorizontalSlider("vowel", &fHslider4, 0.0f, 0.0f, 4.0f, 0.00999999978f);
		ui_interface->declare(&fHslider3, "5", "");
		ui_interface->addHorizontalSlider("vibratoFreq", &fHslider3, 6.0f, 1.0f, 10.0f, 0.00999999978f);
		ui_interface->declare(&fHslider2, "6", "");
		ui_interface->addHorizontalSlider("vibratoGain", &fHslider2, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = (25.0f * float(fHslider0));
		float fSlow1 = float(fHslider1);
		float fSlow2 = (0.100000001f * float(fHslider2));
		float fSlow3 = (fConst2 * float(fHslider3));
		float fSlow4 = sinf(fSlow3);
		float fSlow5 = cosf(fSlow3);
		float fSlow6 = (0.0f - fSlow4);
		float fSlow7 = (0.00100000005f * float(fHslider4));
		float fSlow8 = float(fHslider5);
		int iSlow9 = ((fSlow8 == 0.0f)?1:((fSlow8 == 3.0f)?1:0));
		int iSlow10 = (5 * iSlow9);
		int iSlow11 = (iSlow9 >= 1);
		float fSlow12 = (iSlow11?174.610001f:82.4100037f);
		float fSlow13 = (iSlow11?1046.5f:523.25f);
		float fSlow14 = (fSlow13 - fSlow12);
		float fSlow15 = (5.0f * fSlow8);
		float fSlow16 = (5.0f * (1.0f - fSlow8));
		int iSlow17 = (iSlow9 == 0);
		int iSlow18 = (fSlow8 != 2.0f);
		float fSlow19 = (2.0f * fSlow1);
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			fRec2[0] = ((fSlow4 * fRec3[1]) + (fSlow5 * fRec2[1]));
			int iTemp0 = (1 - iVec0[1]);
			fRec3[0] = (((fSlow5 * fRec3[1]) + (fSlow6 * fRec2[1])) + float(iTemp0));
			float fTemp1 = ((fSlow2 * fRec2[0]) + 1.0f);
			float fTemp2 = (fSlow1 * fTemp1);
			fVec1[0] = fTemp2;
			float fTemp3 = (fRec1[1] + (fConst1 * fVec1[1]));
			fRec1[0] = (fTemp3 - floorf(fTemp3));
			int iTemp4 = ((fRec1[0] - fRec1[1]) < 0.0f);
			iVec2[0] = iTemp4;
			fRec5[0] = (fSlow7 + (0.999000013f * fRec5[1]));
			float fTemp5 = (fRec5[0] + float(iSlow10));
			int iTemp6 = (fTemp5 >= 5.0f);
			int iTemp7 = (fTemp5 >= 3.0f);
			int iTemp8 = (fTemp5 >= 2.0f);
			int iTemp9 = (fTemp5 >= 1.0f);
			int iTemp10 = (fTemp5 >= 4.0f);
			int iTemp11 = (fTemp5 >= 8.0f);
			int iTemp12 = (fTemp5 >= 7.0f);
			int iTemp13 = (fTemp5 >= 6.0f);
			float fTemp14 = (iTemp6?(iTemp11?2.0f:(iTemp12?3.0f:(iTemp13?3.0f:2.0f))):(iTemp7?(iTemp10?1.5f:1.0f):(iTemp8?1.25f:(iTemp9?1.25f:1.0f))));
			fRec6[0] = ((fSlow4 * fRec7[1]) + (fSlow5 * fRec6[1]));
			fRec7[0] = (((fSlow5 * fRec7[1]) + (fSlow6 * fRec6[1])) + float(iTemp0));
			float fTemp15 = (fSlow1 * ((fSlow2 * fRec6[0]) + 1.0f));
			float fTemp16 = (fTemp14 + (((iTemp6?(iTemp11?12.0f:(iTemp12?12.0f:(iTemp13?12.0f:15.0f))):(iTemp7?(iTemp10?4.0f:10.0f):(iTemp8?2.5f:(iTemp9?2.5f:10.0f)))) - fTemp14) * ((fTemp15 <= fSlow12)?0.0f:((fTemp15 >= fSlow13)?1.0f:((fTemp15 - fSlow12) / fSlow14)))));
			float fTemp17 = (fSlow15 + fRec5[0]);
			int iTemp18 = (fTemp17 < 23.0f);
			int iTemp19 = (fTemp17 < 24.0f);
			float fTemp20 = (fSlow15 + (fRec5[0] + -23.0f));
			int iTemp21 = (fTemp17 < 22.0f);
			float fTemp22 = (fSlow15 + (fRec5[0] + -22.0f));
			int iTemp23 = (fTemp17 < 21.0f);
			float fTemp24 = (fSlow15 + (fRec5[0] + -21.0f));
			int iTemp25 = (fTemp17 < 20.0f);
			float fTemp26 = (fSlow15 + (fRec5[0] + -20.0f));
			float fTemp27 = (20.0f * fTemp26);
			int iTemp28 = (fTemp17 < 19.0f);
			int iTemp29 = (fTemp17 < 18.0f);
			float fTemp30 = (fSlow15 + (fRec5[0] + -18.0f));
			int iTemp31 = (fTemp17 < 17.0f);
			float fTemp32 = (fSlow15 + (fRec5[0] + -17.0f));
			int iTemp33 = (fTemp17 < 16.0f);
			int iTemp34 = (fTemp17 < 15.0f);
			float fTemp35 = (fSlow15 + (fRec5[0] + -15.0f));
			float fTemp36 = (20.0f * fTemp35);
			int iTemp37 = (fTemp17 < 14.0f);
			float fTemp38 = (fSlow15 + (fRec5[0] + -14.0f));
			int iTemp39 = (fTemp17 < 13.0f);
			int iTemp40 = (fTemp17 < 12.0f);
			int iTemp41 = (fTemp17 < 11.0f);
			float fTemp42 = (fSlow15 + (fRec5[0] + -11.0f));
			int iTemp43 = (fTemp17 < 10.0f);
			float fTemp44 = (fSlow15 + (fRec5[0] + -10.0f));
			float fTemp45 = (10.0f * fTemp44);
			int iTemp46 = (fTemp17 < 9.0f);
			float fTemp47 = (fSlow15 + (fRec5[0] + -9.0f));
			int iTemp48 = (fTemp17 < 8.0f);
			int iTemp49 = (fTemp17 < 7.0f);
			float fTemp50 = (fSlow15 + (fRec5[0] + -7.0f));
			int iTemp51 = (fTemp17 < 6.0f);
			float fTemp52 = (fSlow15 + (fRec5[0] + -6.0f));
			int iTemp53 = (fTemp17 < 5.0f);
			float fTemp54 = (fRec5[0] - fSlow16);
			int iTemp55 = (fTemp17 < 4.0f);
			float fTemp56 = (fSlow15 + (fRec5[0] + -4.0f));
			float fTemp57 = (10.0f * fTemp56);
			int iTemp58 = (fTemp17 < 3.0f);
			float fTemp59 = (fSlow15 + (fRec5[0] + -3.0f));
			float fTemp60 = (20.0f * fTemp59);
			int iTemp61 = (fTemp17 < 2.0f);
			float fTemp62 = (fSlow15 + (fRec5[0] + -2.0f));
			float fTemp63 = (20.0f * fTemp62);
			int iTemp64 = (fTemp17 < 1.0f);
			float fTemp65 = (fSlow15 + (fRec5[0] + -1.0f));
			int iTemp66 = (fTemp17 < 0.0f);
			float fTemp67 = (20.0f * fTemp17);
			float fTemp68 = (iTemp18?(iTemp21?(iTemp23?(iTemp25?(iTemp28?(iTemp29?(iTemp31?(iTemp33?(iTemp34?(iTemp37?(iTemp39?(iTemp40?(iTemp41?(iTemp43?(iTemp46?(iTemp48?(iTemp49?(iTemp51?(iTemp53?(iTemp55?(iTemp58?(iTemp61?(iTemp64?(iTemp66?80.0f:(iTemp64?(80.0f - fTemp67):60.0f)):(iTemp61?(60.0f - (10.0f * fTemp65)):50.0f)):(iTemp58?(fTemp63 + 50.0f):70.0f)):(iTemp55?(70.0f - fTemp60):50.0f)):(iTemp53?(fTemp57 + 50.0f):60.0f)):(iTemp51?(60.0f - (20.0f * fTemp54)):40.0f)):(iTemp49?((20.0f * fTemp52) + 40.0f):60.0f)):(iTemp48?(60.0f - (20.0f * fTemp50)):40.0f)):40.0f):(iTemp43?(40.0f * (fTemp47 + 1.0f)):80.0f)):(iTemp41?(80.0f - fTemp45):70.0f)):(iTemp40?(70.0f - (30.0f * fTemp42)):40.0f)):40.0f):40.0f):(iTemp34?(40.0f * (fTemp38 + 1.0f)):80.0f)):(iTemp33?(80.0f - fTemp36):60.0f)):60.0f):(iTemp29?(60.0f - (20.0f * fTemp32)):40.0f)):(iTemp28?((10.0f * fTemp30) + 40.0f):50.0f)):50.0f):(iTemp23?(fTemp27 + 50.0f):70.0f)):(iTemp21?(70.0f - (30.0f * fTemp24)):40.0f)):(iTemp18?((30.0f * fTemp22) + 40.0f):70.0f)):(iTemp19?(70.0f - (30.0f * fTemp20)):40.0f));
			fRec4[0] = ((fConst4 * fRec4[1]) + (fConst5 * (fTemp16 * fTemp68)));
			float fTemp69 = expf((fConst3 * (0.0f - fRec4[0])));
			fRec8[0] = ((fConst4 * fRec8[1]) + (fConst5 * fTemp68));
			float fTemp70 = expf((fConst3 * (0.0f - fRec8[0])));
			fRec0[0] = (float(iVec2[1]) - ((fRec0[1] * (0.0f - (fTemp69 + fTemp70))) + ((fTemp69 * fTemp70) * fRec0[2])));
			float fTemp71 = ((0.000839999993f * (1000.0f - fTemp15)) + 0.800000012f);
			float fTemp72 = ((0.00366666657f * (400.0f - fTemp15)) + 3.0f);
			int iTemp73 = (1 - (iTemp4 > 0));
			fRec11[0] = (fSlow7 + (0.999000013f * fRec11[1]));
			float fTemp74 = (fSlow15 + fRec11[0]);
			int iTemp75 = (fTemp74 < 23.0f);
			int iTemp76 = (fTemp74 < 24.0f);
			float fTemp77 = (fSlow15 + (fRec11[0] + -23.0f));
			int iTemp78 = (fTemp74 < 22.0f);
			float fTemp79 = (fSlow15 + (fRec11[0] + -22.0f));
			int iTemp80 = (fTemp74 < 21.0f);
			float fTemp81 = (fSlow15 + (fRec11[0] + -21.0f));
			int iTemp82 = (fTemp74 < 20.0f);
			float fTemp83 = (fSlow15 + (fRec11[0] + -20.0f));
			int iTemp84 = (fTemp74 < 19.0f);
			float fTemp85 = (fSlow15 + (fRec11[0] + -19.0f));
			int iTemp86 = (fTemp74 < 18.0f);
			float fTemp87 = (fSlow15 + (fRec11[0] + -18.0f));
			int iTemp88 = (fTemp74 < 17.0f);
			float fTemp89 = (fSlow15 + (fRec11[0] + -17.0f));
			int iTemp90 = (fTemp74 < 16.0f);
			float fTemp91 = (fSlow15 + (fRec11[0] + -16.0f));
			int iTemp92 = (fTemp74 < 15.0f);
			float fTemp93 = (fSlow15 + (fRec11[0] + -15.0f));
			int iTemp94 = (fTemp74 < 14.0f);
			float fTemp95 = (fSlow15 + (fRec11[0] + -14.0f));
			int iTemp96 = (fTemp74 < 13.0f);
			float fTemp97 = (fSlow15 + (fRec11[0] + -13.0f));
			int iTemp98 = (fTemp74 < 12.0f);
			float fTemp99 = (fSlow15 + (fRec11[0] + -12.0f));
			int iTemp100 = (fTemp74 < 11.0f);
			float fTemp101 = (fSlow15 + (fRec11[0] + -11.0f));
			int iTemp102 = (fTemp74 < 10.0f);
			float fTemp103 = (fSlow15 + (fRec11[0] + -10.0f));
			int iTemp104 = (fTemp74 < 9.0f);
			float fTemp105 = (fSlow15 + (fRec11[0] + -9.0f));
			int iTemp106 = (fTemp74 < 8.0f);
			float fTemp107 = (fSlow15 + (fRec11[0] + -8.0f));
			float fTemp108 = (50.0f * fTemp107);
			int iTemp109 = (fTemp74 < 7.0f);
			float fTemp110 = (fSlow15 + (fRec11[0] + -7.0f));
			int iTemp111 = (fTemp74 < 6.0f);
			float fTemp112 = (fSlow15 + (fRec11[0] + -6.0f));
			int iTemp113 = (fTemp74 < 5.0f);
			float fTemp114 = (fRec11[0] - fSlow16);
			int iTemp115 = (fTemp74 < 4.0f);
			float fTemp116 = (fSlow15 + (fRec11[0] + -4.0f));
			int iTemp117 = (fTemp74 < 3.0f);
			float fTemp118 = (fSlow15 + (fRec11[0] + -3.0f));
			int iTemp119 = (fTemp74 < 2.0f);
			float fTemp120 = (fSlow15 + (fRec11[0] + -2.0f));
			int iTemp121 = (fTemp74 < 1.0f);
			float fTemp122 = (fSlow15 + (fRec11[0] + -1.0f));
			int iTemp123 = (fTemp74 < 0.0f);
			float fTemp124 = (iTemp75?(iTemp78?(iTemp80?(iTemp82?(iTemp84?(iTemp86?(iTemp88?(iTemp90?(iTemp92?(iTemp94?(iTemp96?(iTemp98?(iTemp100?(iTemp102?(iTemp104?(iTemp106?(iTemp109?(iTemp111?(iTemp113?(iTemp115?(iTemp117?(iTemp119?(iTemp121?(iTemp123?800.0f:(iTemp121?(800.0f - (400.0f * fTemp74)):400.0f)):(iTemp119?(400.0f - (50.0f * fTemp122)):350.0f)):(iTemp117?((100.0f * fTemp120) + 350.0f):450.0f)):(iTemp115?(450.0f - (125.0f * fTemp118)):325.0f)):(iTemp113?((275.0f * fTemp116) + 325.0f):600.0f)):(iTemp111?(600.0f - (200.0f * fTemp114)):400.0f)):(iTemp109?(400.0f - (150.0f * fTemp112)):250.0f)):(iTemp106?((150.0f * fTemp110) + 250.0f):400.0f)):(iTemp104?(400.0f - fTemp108):350.0f)):(iTemp102?((310.0f * fTemp105) + 350.0f):660.0f)):(iTemp100?(660.0f - (220.0f * fTemp103)):440.0f)):(iTemp98?(440.0f - (170.0f * fTemp101)):270.0f)):(iTemp96?((160.0f * fTemp99) + 270.0f):430.0f)):(iTemp94?(430.0f - (60.0f * fTemp97)):370.0f)):(iTemp92?((430.0f * fTemp95) + 370.0f):800.0f)):(iTemp90?(800.0f - (450.0f * fTemp93)):350.0f)):(iTemp88?(350.0f - (80.0f * fTemp91)):270.0f)):(iTemp86?((180.0f * fTemp89) + 270.0f):450.0f)):(iTemp84?(450.0f - (125.0f * fTemp87)):325.0f)):(iTemp82?(325.0f * (fTemp85 + 1.0f)):650.0f)):(iTemp80?(650.0f - (250.0f * fTemp83)):400.0f)):(iTemp78?(400.0f - (110.0f * fTemp81)):290.0f)):(iTemp75?((110.0f * fTemp79) + 290.0f):400.0f)):(iTemp76?(400.0f - (50.0f * fTemp77)):350.0f));
			float fTemp125 = ((fRec10[1] * float(iTemp73)) + (fConst6 * ((fTemp124 <= fTemp2)?fTemp2:fTemp124)));
			fRec10[0] = (fTemp125 - floorf(fTemp125));
			float fTemp126 = (10.0f * fTemp22);
			float fTemp127 = (10.0f * fTemp26);
			float fTemp128 = (fSlow15 + (fRec5[0] + -19.0f));
			float fTemp129 = (fSlow15 + (fRec5[0] + -16.0f));
			float fTemp130 = (fSlow15 + (fRec5[0] + -13.0f));
			float fTemp131 = (fSlow15 + (fRec5[0] + -12.0f));
			float fTemp132 = (10.0f * fTemp47);
			float fTemp133 = (10.0f * fTemp54);
			float fTemp134 = (iTemp18?(iTemp21?(iTemp23?(iTemp25?(iTemp28?(iTemp29?(iTemp31?(iTemp33?(iTemp34?(iTemp37?(iTemp39?(iTemp40?(iTemp41?(iTemp43?(iTemp46?(iTemp48?(iTemp49?(iTemp51?(iTemp53?(iTemp55?(iTemp58?(iTemp61?(iTemp64?(iTemp66?90.0f:(iTemp64?(90.0f - (10.0f * fTemp17)):80.0f)):(iTemp61?((20.0f * fTemp65) + 80.0f):100.0f)):(iTemp58?(100.0f - fTemp63):80.0f)):(iTemp55?(80.0f - fTemp60):60.0f)):(iTemp53?(fTemp57 + 60.0f):70.0f)):(iTemp51?(fTemp133 + 70.0f):80.0f)):(iTemp49?((10.0f * fTemp52) + 80.0f):90.0f)):(iTemp48?(90.0f - (10.0f * fTemp50)):80.0f)):80.0f):(iTemp43?(fTemp132 + 80.0f):90.0f)):(iTemp41?(90.0f - fTemp45):80.0f)):(iTemp40?((10.0f * fTemp42) + 80.0f):90.0f)):(iTemp39?(90.0f - (10.0f * fTemp131)):80.0f)):(iTemp37?(80.0f - (20.0f * fTemp130)):60.0f)):(iTemp34?((30.0f * fTemp38) + 60.0f):90.0f)):(iTemp33?((10.0f * fTemp35) + 90.0f):100.0f)):(iTemp31?(100.0f - (10.0f * fTemp129)):90.0f)):(iTemp29?(90.0f - (10.0f * fTemp32)):80.0f)):(iTemp28?(80.0f - (20.0f * fTemp30)):60.0f)):(iTemp25?((30.0f * fTemp128) + 60.0f):90.0f)):(iTemp23?(90.0f - fTemp127):80.0f)):(iTemp21?((10.0f * fTemp24) + 80.0f):90.0f)):(iTemp18?(90.0f - fTemp126):80.0f)):(iTemp19?(80.0f - (20.0f * fTemp20)):60.0f));
			fRec13[0] = ((fConst4 * fRec13[1]) + (fConst5 * (fTemp16 * fTemp134)));
			float fTemp135 = expf((fConst3 * (0.0f - fRec13[0])));
			fRec14[0] = ((fConst4 * fRec14[1]) + (fConst5 * fTemp134));
			float fTemp136 = expf((fConst3 * (0.0f - fRec14[0])));
			fRec12[0] = (float(iVec2[1]) - ((fRec12[1] * (0.0f - (fTemp135 + fTemp136))) + ((fTemp135 * fTemp136) * fRec12[2])));
			float fTemp137 = (fSlow15 + (fRec5[0] + -8.0f));
			float fTemp138 = (iTemp18?(iTemp21?(iTemp23?(iTemp25?(iTemp28?(iTemp29?(iTemp31?(iTemp33?(iTemp34?(iTemp37?(iTemp39?(iTemp40?(iTemp41?(iTemp43?(iTemp46?(iTemp48?(iTemp49?(iTemp51?(iTemp53?(iTemp55?(iTemp58?(iTemp61?(iTemp64?(iTemp66?0.630957007f:(iTemp64?(0.630957007f - (0.567861021f * fTemp17)):0.0630960017f)):(iTemp61?((0.0369039997f * fTemp65) + 0.0630960017f):0.100000001f)):(iTemp58?((0.254812986f * fTemp62) + 0.100000001f):0.35481301f)):(iTemp55?(0.35481301f - (0.103624001f * fTemp59)):0.251188993f)):(iTemp53?((0.195494995f * fTemp56) + 0.251188993f):0.446684003f)):(iTemp51?(0.446684003f - (0.195494995f * fTemp54)):0.251188993f)):(iTemp49?(0.251188993f - (0.219566002f * fTemp52)):0.0316229984f)):(iTemp48?((0.250214994f * fTemp50) + 0.0316229984f):0.281838f)):(iTemp46?(0.281838f - (0.181838006f * fTemp137)):0.100000001f)):(iTemp43?((0.401187003f * fTemp47) + 0.100000001f):0.501187027f)):(iTemp41?(0.501187027f - (0.301661015f * fTemp44)):0.199525997f)):(iTemp40?(0.199525997f - (0.136429995f * fTemp42)):0.0630960017f)):(iTemp39?((0.253131986f * fTemp131) + 0.0630960017f):0.316228002f)):(iTemp37?(0.316228002f - (0.216227993f * fTemp130)):0.100000001f)):(iTemp34?((0.401187003f * fTemp38) + 0.100000001f):0.501187027f)):(iTemp33?(0.501187027f - (0.401187003f * fTemp35)):0.100000001f)):(iTemp31?((0.151188999f * fTemp129) + 0.100000001f):0.251188993f)):(iTemp29?((0.0306490008f * fTemp32) + 0.251188993f):0.281838f)):(iTemp28?(0.281838f - (0.123349003f * fTemp30)):0.158489004f)):(iTemp25?((0.342698008f * fTemp128) + 0.158489004f):0.501187027f)):(iTemp23?(0.501187027f - (0.301661015f * fTemp26)):0.199525997f)):(iTemp21?(0.199525997f - (0.0216979999f * fTemp24)):0.177827999f)):(iTemp18?((0.138400003f * fTemp22) + 0.177827999f):0.316228002f)):(iTemp19?(0.316228002f - (0.216227993f * fTemp20)):0.100000001f));
			float fTemp139 = (iTemp75?(iTemp78?(iTemp80?(iTemp82?(iTemp84?(iTemp86?(iTemp88?(iTemp90?(iTemp92?(iTemp94?(iTemp96?(iTemp98?(iTemp100?(iTemp102?(iTemp104?(iTemp106?(iTemp109?(iTemp111?(iTemp113?(iTemp115?(iTemp117?(iTemp119?(iTemp121?(iTemp123?1150.0f:(iTemp121?((450.0f * fTemp74) + 1150.0f):1600.0f)):(iTemp119?((100.0f * fTemp122) + 1600.0f):1700.0f)):(iTemp117?(1700.0f - (900.0f * fTemp120)):800.0f)):(iTemp115?(800.0f - (100.0f * fTemp118)):700.0f)):(iTemp113?((340.0f * fTemp116) + 700.0f):1040.0f)):(iTemp111?((580.0f * fTemp114) + 1040.0f):1620.0f)):(iTemp109?((130.0f * fTemp112) + 1620.0f):1750.0f)):(iTemp106?(1750.0f - (1000.0f * fTemp110)):750.0f)):(iTemp104?(750.0f - (150.0f * fTemp107)):600.0f)):(iTemp102?((520.0f * fTemp105) + 600.0f):1120.0f)):(iTemp100?((680.0f * fTemp103) + 1120.0f):1800.0f)):(iTemp98?((50.0f * fTemp101) + 1800.0f):1850.0f)):(iTemp96?(1850.0f - (1030.0f * fTemp99)):820.0f)):(iTemp94?(820.0f - (190.0f * fTemp97)):630.0f)):(iTemp92?((520.0f * fTemp95) + 630.0f):1150.0f)):(iTemp90?((850.0f * fTemp93) + 1150.0f):2000.0f)):(iTemp88?((140.0f * fTemp91) + 2000.0f):2140.0f)):(iTemp86?(2140.0f - (1340.0f * fTemp89)):800.0f)):(iTemp84?(800.0f - (100.0f * fTemp87)):700.0f)):(iTemp82?((380.0f * fTemp85) + 700.0f):1080.0f)):(iTemp80?((620.0f * fTemp83) + 1080.0f):1700.0f)):(iTemp78?((170.0f * fTemp81) + 1700.0f):1870.0f)):(iTemp75?(1870.0f - (1070.0f * fTemp79)):800.0f)):(iTemp76?(800.0f - (200.0f * fTemp77)):600.0f));
			float fTemp140 = ((fSlow19 * fTemp1) + 30.0f);
			float fTemp141 = ((float(iTemp73) * fRec15[1]) + (fConst6 * (iSlow18?(((fTemp139 >= 1300.0f) & (fTemp2 >= 200.0f))?(fTemp139 - (0.000952380942f * ((fTemp2 + -200.0f) * (fTemp139 + -1300.0f)))):((fTemp139 <= fTemp140)?fTemp140:fTemp139)):fTemp139)));
			fRec15[0] = (fTemp141 - floorf(fTemp141));
			float fTemp142 = (50.0f * fTemp128);
			float fTemp143 = (20.0f * fTemp38);
			float fTemp144 = (20.0f * fTemp44);
			float fTemp145 = (20.0f * fTemp47);
			float fTemp146 = (60.0f * fTemp56);
			float fTemp147 = (iTemp18?(iTemp21?(iTemp23?(iTemp25?(iTemp28?(iTemp29?(iTemp31?(iTemp33?(iTemp34?(iTemp37?(iTemp39?(iTemp40?(iTemp41?(iTemp43?(iTemp46?(iTemp48?(iTemp49?(iTemp51?(iTemp53?(iTemp55?(iTemp58?(iTemp61?120.0f:(iTemp58?(120.0f - fTemp63):100.0f)):(iTemp55?((70.0f * fTemp59) + 100.0f):170.0f)):(iTemp53?(170.0f - fTemp146):110.0f)):(iTemp51?(110.0f - fTemp133):100.0f)):100.0f):100.0f):100.0f):(iTemp43?(fTemp145 + 100.0f):120.0f)):(iTemp41?(120.0f - fTemp144):100.0f)):100.0f):100.0f):100.0f):(iTemp34?(fTemp143 + 100.0f):120.0f)):120.0f):(iTemp31?(120.0f - (20.0f * fTemp129)):100.0f)):100.0f):(iTemp28?((70.0f * fTemp30) + 100.0f):170.0f)):(iTemp25?(170.0f - fTemp142):120.0f)):(iTemp23?(120.0f - fTemp27):100.0f)):100.0f):100.0f):100.0f);
			fRec17[0] = ((fConst4 * fRec17[1]) + (fConst5 * (fTemp16 * fTemp147)));
			float fTemp148 = expf((fConst3 * (0.0f - fRec17[0])));
			fRec18[0] = ((fConst4 * fRec18[1]) + (fConst5 * fTemp147));
			float fTemp149 = expf((fConst3 * (0.0f - fRec18[0])));
			fRec16[0] = (float(iVec2[1]) - ((fRec16[1] * (0.0f - (fTemp148 + fTemp149))) + ((fTemp148 * fTemp149) * fRec16[2])));
			float fTemp150 = (iTemp29?((0.0293140002f * fTemp32) + 0.0501190014f):0.0794330016f);
			float fTemp151 = (iTemp18?(iTemp21?(iTemp23?(iTemp25?(iTemp28?(iTemp29?(iTemp31?(iTemp33?(iTemp34?(iTemp37?(iTemp39?(iTemp40?(iTemp41?(iTemp43?(iTemp46?(iTemp48?(iTemp49?(iTemp51?(iTemp53?(iTemp55?(iTemp58?(iTemp61?(iTemp64?(iTemp66?0.100000001f:(iTemp64?(0.100000001f - (0.0683770031f * fTemp17)):0.0316229984f)):0.0316229984f):(iTemp58?((0.126865998f * fTemp62) + 0.0316229984f):0.158489004f)):(iTemp55?(0.158489004f - (0.126865998f * fTemp59)):0.0316229984f)):(iTemp53?((0.323190004f * fTemp56) + 0.0316229984f):0.35481301f)):0.35481301f):(iTemp49?(0.35481301f - (0.196324006f * fTemp52)):0.158489004f)):(iTemp48?(0.158489004f - (0.0693639964f * fTemp50)):0.0891249999f)):(iTemp46?(0.0891249999f - (0.0640060008f * fTemp137)):0.0251189992f)):(iTemp43?((0.0456760004f * fTemp47) + 0.0251189992f):0.0707949996f)):(iTemp41?((0.0550980009f * fTemp44) + 0.0707949996f):0.125892997f)):(iTemp40?(0.125892997f - (0.0627970025f * fTemp42)):0.0630960017f)):(iTemp39?(0.0630960017f - (0.0129770003f * fTemp131)):0.0501190014f)):(iTemp37?((0.020676f * fTemp130) + 0.0501190014f):0.0707949996f)):(iTemp34?(0.0707949996f - (0.0456760004f * fTemp38)):0.0251189992f)):(iTemp33?((0.152709007f * fTemp35) + 0.0251189992f):0.177827999f)):(iTemp31?(0.177827999f - (0.127709001f * fTemp129)):0.0501190014f)):fTemp150):(iTemp28?(0.0794330016f - (0.0616500005f * fTemp30)):0.0177829992f)):(iTemp25?((0.428900987f * fTemp128) + 0.0177829992f):0.446684003f)):(iTemp23?(0.446684003f - (0.195494995f * fTemp26)):0.251188993f)):(iTemp21?(0.251188993f - (0.125295997f * fTemp24)):0.125892997f)):(iTemp18?((0.125295997f * fTemp22) + 0.125892997f):0.251188993f)):(iTemp19?(0.251188993f - (0.109935001f * fTemp20)):0.141253993f));
			float fTemp152 = (100.0f * fTemp77);
			float fTemp153 = (50.0f * fTemp103);
			float fTemp154 = ((float(iTemp73) * fRec19[1]) + (fConst6 * (iTemp75?(iTemp78?(iTemp80?(iTemp82?(iTemp84?(iTemp86?(iTemp88?(iTemp90?(iTemp92?(iTemp94?(iTemp96?(iTemp98?(iTemp100?(iTemp102?(iTemp104?(iTemp106?(iTemp109?(iTemp111?(iTemp113?(iTemp115?(iTemp117?(iTemp119?(iTemp121?(iTemp123?2800.0f:(iTemp121?(2800.0f - (100.0f * fTemp74)):2700.0f)):2700.0f):(iTemp117?((130.0f * fTemp120) + 2700.0f):2830.0f)):(iTemp115?(2830.0f - (300.0f * fTemp118)):2530.0f)):(iTemp113?(2530.0f - (280.0f * fTemp116)):2250.0f)):(iTemp111?((150.0f * fTemp114) + 2250.0f):2400.0f)):(iTemp109?((200.0f * fTemp112) + 2400.0f):2600.0f)):(iTemp106?(2600.0f - (200.0f * fTemp110)):2400.0f)):2400.0f):(iTemp102?((350.0f * fTemp105) + 2400.0f):2750.0f)):(iTemp100?(2750.0f - fTemp153):2700.0f)):(iTemp98?((200.0f * fTemp101) + 2700.0f):2900.0f)):(iTemp96?(2900.0f - (200.0f * fTemp99)):2700.0f)):(iTemp94?((50.0f * fTemp97) + 2700.0f):2750.0f)):(iTemp92?((150.0f * fTemp95) + 2750.0f):2900.0f)):(iTemp90?(2900.0f - (100.0f * fTemp93)):2800.0f)):(iTemp88?((150.0f * fTemp91) + 2800.0f):2950.0f)):(iTemp86?(2950.0f - (120.0f * fTemp89)):2830.0f)):(iTemp84?(2830.0f - (130.0f * fTemp87)):2700.0f)):(iTemp82?(2700.0f - (50.0f * fTemp85)):2650.0f)):(iTemp80?(2650.0f - (50.0f * fTemp83)):2600.0f)):(iTemp78?((200.0f * fTemp81) + 2600.0f):2800.0f)):(iTemp75?(2800.0f - (200.0f * fTemp79)):2600.0f)):(iTemp76?(fTemp152 + 2600.0f):2700.0f))));
			fRec19[0] = (fTemp154 - floorf(fTemp154));
			float fTemp155 = (iTemp18?(iTemp21?(iTemp23?(iTemp25?(iTemp28?(iTemp29?(iTemp31?(iTemp33?(iTemp34?(iTemp37?(iTemp39?(iTemp40?(iTemp41?(iTemp43?(iTemp46?(iTemp48?(iTemp49?(iTemp51?(iTemp53?(iTemp55?(iTemp58?(iTemp61?(iTemp64?(iTemp66?130.0f:(iTemp64?(fTemp67 + 130.0f):150.0f)):150.0f):(iTemp58?(150.0f - fTemp63):130.0f)):(iTemp55?((50.0f * fTemp59) + 130.0f):180.0f)):(iTemp53?(180.0f - fTemp146):120.0f)):120.0f):120.0f):120.0f):120.0f):(iTemp43?(fTemp132 + 120.0f):130.0f)):(iTemp41?(130.0f - fTemp45):120.0f)):120.0f):120.0f):120.0f):(iTemp34?((10.0f * fTemp38) + 120.0f):130.0f)):(iTemp33?(fTemp36 + 130.0f):150.0f)):(iTemp31?(150.0f - (30.0f * fTemp129)):120.0f)):120.0f):(iTemp28?((60.0f * fTemp30) + 120.0f):180.0f)):(iTemp25?(180.0f - fTemp142):130.0f)):(iTemp23?(130.0f - fTemp127):120.0f)):120.0f):(iTemp18?(fTemp126 + 120.0f):130.0f)):(iTemp19?(130.0f - (10.0f * fTemp20)):120.0f));
			fRec21[0] = ((fConst4 * fRec21[1]) + (fConst5 * (fTemp16 * fTemp155)));
			float fTemp156 = expf((fConst3 * (0.0f - fRec21[0])));
			fRec22[0] = ((fConst4 * fRec22[1]) + (fConst5 * fTemp155));
			float fTemp157 = expf((fConst3 * (0.0f - fRec22[0])));
			fRec20[0] = (float(iVec2[1]) - ((fRec20[1] * (0.0f - (fTemp156 + fTemp157))) + ((fTemp156 * fTemp157) * fRec20[2])));
			float fTemp158 = (iTemp40?(0.100000001f - (0.0841509998f * fTemp42)):0.0158489998f);
			float fTemp159 = (iTemp18?(iTemp21?(iTemp23?(iTemp25?(iTemp28?(iTemp29?(iTemp31?(iTemp33?(iTemp34?(iTemp37?(iTemp39?(iTemp40?(iTemp41?(iTemp43?(iTemp46?(iTemp48?(iTemp49?(iTemp51?(iTemp53?(iTemp55?(iTemp58?(iTemp61?(iTemp64?(iTemp66?0.0158489998f:(iTemp64?((0.00193400006f * fTemp17) + 0.0158489998f):0.0177829992f)):(iTemp61?(0.0177829992f - (0.00193400006f * fTemp65)):0.0158489998f)):(iTemp58?((0.0239620004f * fTemp62) + 0.0158489998f):0.0398110002f)):(iTemp55?(0.0398110002f - (0.0298110005f * fTemp59)):0.00999999978f)):(iTemp53?((0.344812989f * fTemp56) + 0.00999999978f):0.35481301f)):(iTemp51?(0.35481301f - (0.103624001f * fTemp54)):0.251188993f)):(iTemp49?(0.251188993f - (0.171755999f * fTemp52)):0.0794330016f)):(iTemp48?((0.0205669999f * fTemp50) + 0.0794330016f):0.100000001f)):(iTemp46?(0.100000001f - (0.0601890013f * fTemp137)):0.0398110002f)):(iTemp43?((0.0232849997f * fTemp47) + 0.0398110002f):0.0630960017f)):(iTemp41?((0.0369039997f * fTemp44) + 0.0630960017f):0.100000001f)):fTemp158):(iTemp39?((0.0635839999f * fTemp131) + 0.0158489998f):0.0794330016f)):(iTemp37?(0.0794330016f - (0.0478099994f * fTemp130)):0.0316229984f)):(iTemp34?((0.0683770031f * fTemp38) + 0.0316229984f):0.100000001f)):(iTemp33?(0.100000001f - (0.0900000036f * fTemp35)):0.00999999978f)):(iTemp31?((0.0401189998f * fTemp129) + 0.00999999978f):0.0501190014f)):fTemp150):(iTemp28?(0.0794330016f - (0.0694330037f * fTemp30)):0.00999999978f)):(iTemp25?((0.388107002f * fTemp128) + 0.00999999978f):0.398106992f)):(iTemp23?(0.398106992f - (0.198580995f * fTemp26)):0.199525997f)):(iTemp21?(0.199525997f - (0.099526003f * fTemp24)):0.100000001f)):(iTemp18?((0.151188999f * fTemp22) + 0.100000001f):0.251188993f)):(iTemp19?(0.251188993f - (0.0516630001f * fTemp20)):0.199525997f));
			float fTemp160 = (350.0f * fTemp114);
			float fTemp161 = ((float(iTemp73) * fRec23[1]) + (fConst6 * (iTemp75?(iTemp78?(iTemp80?(iTemp82?(iTemp84?(iTemp86?(iTemp88?(iTemp90?(iTemp92?(iTemp94?(iTemp96?(iTemp98?(iTemp100?(iTemp102?(iTemp104?(iTemp106?(iTemp109?(iTemp111?(iTemp113?(iTemp115?(iTemp117?(iTemp119?(iTemp121?(iTemp123?3500.0f:(iTemp121?(3500.0f - (200.0f * fTemp74)):3300.0f)):(iTemp119?((400.0f * fTemp122) + 3300.0f):3700.0f)):(iTemp117?(3700.0f - (200.0f * fTemp120)):3500.0f)):3500.0f):(iTemp113?(3500.0f - (1050.0f * fTemp116)):2450.0f)):(iTemp111?(fTemp160 + 2450.0f):2800.0f)):(iTemp109?((250.0f * fTemp112) + 2800.0f):3050.0f)):(iTemp106?(3050.0f - (450.0f * fTemp110)):2600.0f)):(iTemp104?((75.0f * fTemp107) + 2600.0f):2675.0f)):(iTemp102?((325.0f * fTemp105) + 2675.0f):3000.0f)):3000.0f):(iTemp98?((350.0f * fTemp101) + 3000.0f):3350.0f)):(iTemp96?(3350.0f - (350.0f * fTemp99)):3000.0f)):3000.0f):(iTemp92?((900.0f * fTemp95) + 3000.0f):3900.0f)):(iTemp90?(3900.0f - (300.0f * fTemp93)):3600.0f)):(iTemp88?((300.0f * fTemp91) + 3600.0f):3900.0f)):(iTemp86?(3900.0f - (100.0f * fTemp89)):3800.0f)):3800.0f):(iTemp82?(3800.0f - (900.0f * fTemp85)):2900.0f)):(iTemp80?((300.0f * fTemp83) + 2900.0f):3200.0f)):(iTemp78?((50.0f * fTemp81) + 3200.0f):3250.0f)):(iTemp75?(3250.0f - (450.0f * fTemp79)):2800.0f)):(iTemp76?(fTemp152 + 2800.0f):2900.0f))));
			fRec23[0] = (fTemp161 - floorf(fTemp161));
			float fTemp162 = (iTemp18?(iTemp21?(iTemp23?(iTemp25?(iTemp28?(iTemp29?(iTemp31?(iTemp33?(iTemp34?(iTemp37?(iTemp39?(iTemp40?(iTemp41?(iTemp43?(iTemp46?(iTemp48?(iTemp49?(iTemp51?(iTemp53?(iTemp55?(iTemp58?(iTemp61?(iTemp64?(iTemp66?140.0f:(iTemp64?((60.0f * fTemp17) + 140.0f):200.0f)):200.0f):(iTemp58?(200.0f - (65.0f * fTemp62)):135.0f)):(iTemp55?((65.0f * fTemp59) + 135.0f):200.0f)):(iTemp53?(200.0f - (70.0f * fTemp56)):130.0f)):(iTemp51?(130.0f - fTemp133):120.0f)):120.0f):120.0f):120.0f):(iTemp43?(fTemp145 + 120.0f):140.0f)):(iTemp41?(140.0f - fTemp144):120.0f)):120.0f):120.0f):120.0f):(iTemp34?(fTemp143 + 120.0f):140.0f)):(iTemp33?((60.0f * fTemp35) + 140.0f):200.0f)):(iTemp31?(200.0f - (80.0f * fTemp129)):120.0f)):120.0f):(iTemp28?((80.0f * fTemp30) + 120.0f):200.0f)):(iTemp25?(200.0f - (60.0f * fTemp128)):140.0f)):(iTemp23?(140.0f - fTemp27):120.0f)):120.0f):(iTemp18?((15.0f * fTemp22) + 120.0f):135.0f)):(iTemp19?(135.0f - (15.0f * fTemp20)):120.0f));
			fRec25[0] = ((fConst4 * fRec25[1]) + (fConst5 * (fTemp16 * fTemp162)));
			float fTemp163 = expf((fConst3 * (0.0f - fRec25[0])));
			fRec26[0] = ((fConst4 * fRec26[1]) + (fConst5 * fTemp162));
			float fTemp164 = expf((fConst3 * (0.0f - fRec26[0])));
			fRec24[0] = (float(iVec2[1]) - ((fRec24[1] * (0.0f - (fTemp163 + fTemp164))) + ((fTemp163 * fTemp164) * fRec24[2])));
			float fTemp165 = (iTemp18?(iTemp21?(iTemp23?(iTemp25?(iTemp28?(iTemp29?(iTemp31?(iTemp33?(iTemp34?(iTemp37?(iTemp39?(iTemp40?(iTemp41?(iTemp43?(iTemp46?(iTemp48?(iTemp49?(iTemp51?(iTemp53?(iTemp55?(iTemp58?(iTemp61?0.00100000005f:(iTemp58?((0.000777999987f * fTemp62) + 0.00100000005f):0.00177800003f)):(iTemp55?(0.00177800003f - (0.001147f * fTemp59)):0.000630999974f)):(iTemp53?((0.0993689969f * fTemp56) + 0.000630999974f):0.100000001f)):(iTemp51?((0.0258930009f * fTemp54) + 0.100000001f):0.125892997f)):(iTemp49?(0.125892997f - (0.0860819966f * fTemp52)):0.0398110002f)):(iTemp48?(0.0398110002f - (0.0298110005f * fTemp50)):0.00999999978f)):(iTemp46?((0.00584900007f * fTemp137) + 0.00999999978f):0.0158489998f)):(iTemp43?(0.0158489998f - (0.00325999991f * fTemp47)):0.0125890002f)):(iTemp41?((0.0874110013f * fTemp44) + 0.0125890002f):0.100000001f)):fTemp158):(iTemp39?((0.00410400005f * fTemp131) + 0.0158489998f):0.0199529994f)):0.0199529994f):(iTemp34?(0.0199529994f - (0.0167909991f * fTemp38)):0.0031620001f)):(iTemp33?(0.0031620001f - (0.00157700002f * fTemp35)):0.00158499996f)):(iTemp31?((0.00472499989f * fTemp129) + 0.00158499996f):0.00631000008f)):(iTemp29?(0.00631000008f - (0.00314799999f * fTemp32)):0.0031620001f)):(iTemp28?(0.0031620001f - (0.00216199993f * fTemp30)):0.00100000005f)):(iTemp25?((0.0784329996f * fTemp128) + 0.00100000005f):0.0794330016f)):(iTemp23?((0.0205669999f * fTemp26) + 0.0794330016f):0.100000001f)):(iTemp21?(0.100000001f - (0.0683770031f * fTemp24)):0.0316229984f)):(iTemp18?((0.0184959993f * fTemp22) + 0.0316229984f):0.0501190014f)):0.0501190014f);
			float fTemp166 = ((float(iTemp73) * fRec27[1]) + (fConst6 * (iTemp75?(iTemp78?(iTemp80?(iTemp82?(iTemp84?(iTemp86?(iTemp88?(iTemp90?(iTemp92?(iTemp94?(iTemp96?(iTemp98?(iTemp100?(iTemp102?(iTemp104?(iTemp106?(iTemp109?(iTemp111?(iTemp113?(iTemp115?4950.0f:(iTemp113?(4950.0f - (2200.0f * fTemp116)):2750.0f)):(iTemp111?(fTemp160 + 2750.0f):3100.0f)):(iTemp109?((240.0f * fTemp112) + 3100.0f):3340.0f)):(iTemp106?(3340.0f - (440.0f * fTemp110)):2900.0f)):(iTemp104?(fTemp108 + 2900.0f):2950.0f)):(iTemp102?((400.0f * fTemp105) + 2950.0f):3350.0f)):(iTemp100?(3350.0f - fTemp153):3300.0f)):(iTemp98?((290.0f * fTemp101) + 3300.0f):3590.0f)):(iTemp96?(3590.0f - (290.0f * fTemp99)):3300.0f)):(iTemp94?((100.0f * fTemp97) + 3300.0f):3400.0f)):(iTemp92?((1550.0f * fTemp95) + 3400.0f):4950.0f)):4950.0f):4950.0f):4950.0f):4950.0f):(iTemp82?(4950.0f - (1700.0f * fTemp85)):3250.0f)):(iTemp80?((330.0f * fTemp83) + 3250.0f):3580.0f)):(iTemp78?(3580.0f - (40.0f * fTemp81)):3540.0f)):(iTemp75?(3540.0f - (540.0f * fTemp79)):3000.0f)):(iTemp76?((300.0f * fTemp77) + 3000.0f):3300.0f))));
			fRec27[0] = (fTemp166 - floorf(fTemp166));
			float fTemp167 = (fSlow0 * (((((((fRec0[0] * (iSlow17?fTemp72:fTemp71)) * (1.0f - (fTemp70 + (fTemp69 * (1.0f - fTemp70))))) * ftbl0mydspSIG0[int((65536.0f * fRec10[0]))]) + (((fRec12[0] * (iSlow17?(fTemp72 * fTemp138):(fTemp71 * fTemp138))) * (1.0f - (fTemp136 + (fTemp135 * (1.0f - fTemp136))))) * ftbl0mydspSIG0[int((65536.0f * fRec15[0]))])) + (((fRec16[0] * (iSlow17?(fTemp72 * fTemp151):(fTemp71 * fTemp151))) * (1.0f - (fTemp149 + (fTemp148 * (1.0f - fTemp149))))) * ftbl0mydspSIG0[int((65536.0f * fRec19[0]))])) + (((fRec20[0] * (iSlow17?(fTemp72 * fTemp159):(fTemp71 * fTemp159))) * (1.0f - (fTemp157 + (fTemp156 * (1.0f - fTemp157))))) * ftbl0mydspSIG0[int((65536.0f * fRec23[0]))])) + (((fRec24[0] * (iSlow17?(fTemp72 * fTemp165):(fTemp71 * fTemp165))) * (1.0f - (fTemp164 + (fTemp163 * (1.0f - fTemp164))))) * ftbl0mydspSIG0[int((65536.0f * fRec27[0]))])));
			output0[i] = FAUSTFLOAT(fTemp167);
			output1[i] = FAUSTFLOAT(fTemp167);
			iVec0[1] = iVec0[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fVec1[1] = fVec1[0];
			fRec1[1] = fRec1[0];
			iVec2[1] = iVec2[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec7[1] = fRec7[0];
			fRec4[1] = fRec4[0];
			fRec8[1] = fRec8[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			fRec11[1] = fRec11[0];
			fRec10[1] = fRec10[0];
			fRec13[1] = fRec13[0];
			fRec14[1] = fRec14[0];
			fRec12[2] = fRec12[1];
			fRec12[1] = fRec12[0];
			fRec15[1] = fRec15[0];
			fRec17[1] = fRec17[0];
			fRec18[1] = fRec18[0];
			fRec16[2] = fRec16[1];
			fRec16[1] = fRec16[0];
			fRec19[1] = fRec19[0];
			fRec21[1] = fRec21[0];
			fRec22[1] = fRec22[0];
			fRec20[2] = fRec20[1];
			fRec20[1] = fRec20[0];
			fRec23[1] = fRec23[0];
			fRec25[1] = fRec25[0];
			fRec26[1] = fRec26[0];
			fRec24[2] = fRec24[1];
			fRec24[1] = fRec24[0];
			fRec27[1] = fRec27[0];
			
		}
		
	}

	
};

#endif
