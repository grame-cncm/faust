/* ------------------------------------------------------------
name: "turenas"
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
	float fConst1;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	int iVec0[2];
	float fRec0[2];
	float fRec1[2];
	FAUSTFLOAT fButton0;
	float fVec1[2];
	FAUSTFLOAT fHslider2;
	float fRec3[2];
	float fVec2[2];
	float fRec2[2];
	float fConst2;
	float fConst3;
	float fConst4;
	float fRec4[2];
	float fRec5[2];
	float fVec3[2];
	float fRec6[2];
	float fRec7[2];
	float fRec8[2];
	float fVec4[2];
	float fRec9[2];
	float fRec10[2];
	float fRec11[2];
	float fVec5[2];
	float fRec12[2];
	float fRec13[2];
	float fRec14[2];
	float fVec6[2];
	float fRec15[2];
	float fRec16[2];
	float fRec17[2];
	float fVec7[2];
	float fRec18[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("envelopes.lib/author", "GRAME");
		m->declare("envelopes.lib/copyright", "GRAME");
		m->declare("envelopes.lib/license", "LGPL with exception");
		m->declare("envelopes.lib/name", "Faust Envelope Library");
		m->declare("envelopes.lib/version", "0.0");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("interface", "SmartKeyboard{  'Number of Keyboards':'10',  'Keyboard 0 - Number of Keys':'18',  'Keyboard 1 - Number of Keys':'18',  'Keyboard 2 - Number of Keys':'18',  'Keyboard 3 - Number of Keys':'18',  'Keyboard 4 - Number of Keys':'18',  'Keyboard 5 - Number of Keys':'18',  'Keyboard 6 - Number of Keys':'18',  'Keyboard 7 - Number of Keys':'18',  'Keyboard 8 - Number of Keys':'18',  'Keyboard 9 - Number of Keys':'18',  'Keyboard 0 - Lowest Key':'50',  'Keyboard 1 - Lowest Key':'55',  'Keyboard 2 - Lowest Key':'60',  'Keyboard 3 - Lowest Key':'65',  'Keyboard 4 - Lowest Key':'70',  'Keyboard 5 - Lowest Key':'75',  'Keyboard 6 - Lowest Key':'80',  'Keyboard 7 - Lowest Key':'85',  'Keyboard 8 - Lowest Key':'90',  'Keyboard 9 - Lowest Key':'95',  'Keyboard 0 - Piano Keyboard':'0',  'Keyboard 1 - Piano Keyboard':'0',  'Keyboard 2 - Piano Keyboard':'0',  'Keyboard 3 - Piano Keyboard':'0',  'Keyboard 4 - Piano Keyboard':'0',  'Keyboard 5 - Piano Keyboard':'0',  'Keyboard 6 - Piano Keyboard':'0',  'Keyboard 7 - Piano Keyboard':'0',  'Keyboard 8 - Piano Keyboard':'0',  'Keyboard 9 - Piano Keyboard':'0',  'Keyboard 0 - Send X':'0',  'Keyboard 1 - Send X':'0',  'Keyboard 2 - Send X':'0',  'Keyboard 3 - Send X':'0',  'Keyboard 4 - Send X':'0',  'Keyboard 5 - Send X':'0',  'Keyboard 6 - Send X':'0',  'Keyboard 7 - Send X':'0',  'Keyboard 8 - Send X':'0',  'Keyboard 9 - Send X':'0' }");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "turenas");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("synths.lib/name", "Faust Synthesizer Library");
		m->declare("synths.lib/version", "0.0");
	}

	virtual int getNumInputs() {
		return 0;
		
	}
	virtual int getNumOutputs() {
		return 1;
		
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
		fConst0 = min(192000.0f, max(1.0f, float(fSamplingFreq)));
		fConst1 = (6.28318548f / fConst0);
		fConst2 = (0.00100000005f * fConst0);
		fConst3 = (1.0f / fConst0);
		fConst4 = (1000.0f / fConst0);
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(400.0f);
		fHslider1 = FAUSTFLOAT(0.0f);
		fButton0 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(2.5f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec0[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec1[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fVec1[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec3[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fVec2[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec2[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec4[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec5[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fVec3[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec6[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec7[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec8[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fVec4[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec9[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec10[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec11[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fVec5[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec12[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec13[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec14[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fVec6[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec15[l22] = 0.0f;
			
		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec16[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fRec17[l24] = 0.0f;
			
		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fVec7[l25] = 0.0f;
			
		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fRec18[l26] = 0.0f;
			
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
		ui_interface->openVerticalBox("turenas");
		ui_interface->addHorizontalSlider("freq", &fHslider0, 400.0f, 50.0f, 2000.0f, 0.00999999978f);
		ui_interface->addButton("gate", &fButton0);
		ui_interface->declare(&fHslider2, "acc", "0 0 -10 0 10");
		ui_interface->addHorizontalSlider("res", &fHslider2, 2.5f, 0.00999999978f, 5.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("y", &fHslider1, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = float(fHslider0);
		float fSlow1 = float(fHslider1);
		float fSlow2 = (fConst1 * (fSlow0 * ((0.833333313f * fSlow1) + 1.0f)));
		float fSlow3 = sinf(fSlow2);
		float fSlow4 = cosf(fSlow2);
		float fSlow5 = (0.0f - fSlow3);
		float fSlow6 = float(fButton0);
		float fSlow7 = (0.00100000005f * float(fHslider2));
		float fSlow8 = (fConst1 * (fSlow0 * ((1.66666663f * fSlow1) + 1.0f)));
		float fSlow9 = sinf(fSlow8);
		float fSlow10 = cosf(fSlow8);
		float fSlow11 = (0.0f - fSlow9);
		float fSlow12 = (fConst1 * (fSlow0 * ((2.5f * fSlow1) + 1.0f)));
		float fSlow13 = sinf(fSlow12);
		float fSlow14 = cosf(fSlow12);
		float fSlow15 = (0.0f - fSlow13);
		float fSlow16 = (fConst1 * (fSlow0 * ((3.33333325f * fSlow1) + 1.0f)));
		float fSlow17 = sinf(fSlow16);
		float fSlow18 = cosf(fSlow16);
		float fSlow19 = (0.0f - fSlow17);
		float fSlow20 = (fConst1 * (fSlow0 * ((4.16666651f * fSlow1) + 1.0f)));
		float fSlow21 = sinf(fSlow20);
		float fSlow22 = cosf(fSlow20);
		float fSlow23 = (0.0f - fSlow21);
		float fSlow24 = (fConst1 * (fSlow0 * ((5.0f * fSlow1) + 1.0f)));
		float fSlow25 = sinf(fSlow24);
		float fSlow26 = cosf(fSlow24);
		float fSlow27 = (0.0f - fSlow25);
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			fRec0[0] = ((fSlow3 * fRec1[1]) + (fSlow4 * fRec0[1]));
			int iTemp0 = (1 - iVec0[1]);
			fRec1[0] = (((fSlow4 * fRec1[1]) + (fSlow5 * fRec0[1])) + float(iTemp0));
			fVec1[0] = fSlow6;
			int iTemp1 = (((fSlow6 - fVec1[1]) > 0.0f) > 0);
			fRec3[0] = (fSlow7 + (0.999000013f * fRec3[1]));
			float fTemp2 = (fRec3[0] + 0.00100000005f);
			fVec2[0] = fTemp2;
			float fTemp3 = (fConst0 * fTemp2);
			fRec2[0] = (iTemp1?0.0f:min(fTemp3, (fRec2[1] + (1.0f - (fConst0 * (fVec2[1] - fTemp2))))));
			int iTemp4 = (fRec2[0] < fConst2);
			fRec4[0] = ((fSlow9 * fRec5[1]) + (fSlow10 * fRec4[1]));
			fRec5[0] = (((fSlow10 * fRec5[1]) + (fSlow11 * fRec4[1])) + float(iTemp0));
			float fTemp5 = ((0.866666675f * fRec3[0]) + 0.00100000005f);
			fVec3[0] = fTemp5;
			float fTemp6 = (fConst0 * fTemp5);
			fRec6[0] = (iTemp1?0.0f:min(fTemp6, (fRec6[1] + (1.0f - (fConst0 * (fVec3[1] - fTemp5))))));
			int iTemp7 = (fRec6[0] < fConst2);
			fRec7[0] = ((fSlow13 * fRec8[1]) + (fSlow14 * fRec7[1]));
			fRec8[0] = (((fSlow14 * fRec8[1]) + (fSlow15 * fRec7[1])) + float(iTemp0));
			float fTemp8 = ((0.733333349f * fRec3[0]) + 0.00100000005f);
			fVec4[0] = fTemp8;
			float fTemp9 = (fConst0 * fTemp8);
			fRec9[0] = (iTemp1?0.0f:min(fTemp9, (fRec9[1] + (1.0f - (fConst0 * (fVec4[1] - fTemp8))))));
			int iTemp10 = (fRec9[0] < fConst2);
			fRec10[0] = ((fSlow17 * fRec11[1]) + (fSlow18 * fRec10[1]));
			fRec11[0] = (((fSlow18 * fRec11[1]) + (fSlow19 * fRec10[1])) + float(iTemp0));
			float fTemp11 = ((0.600000024f * fRec3[0]) + 0.00100000005f);
			fVec5[0] = fTemp11;
			float fTemp12 = (fConst0 * fTemp11);
			fRec12[0] = (iTemp1?0.0f:min(fTemp12, (fRec12[1] + (1.0f - (fConst0 * (fVec5[1] - fTemp11))))));
			int iTemp13 = (fRec12[0] < fConst2);
			fRec13[0] = ((fSlow21 * fRec14[1]) + (fSlow22 * fRec13[1]));
			fRec14[0] = (((fSlow22 * fRec14[1]) + (fSlow23 * fRec13[1])) + float(iTemp0));
			float fTemp14 = ((0.466666669f * fRec3[0]) + 0.00100000005f);
			fVec6[0] = fTemp14;
			float fTemp15 = (fConst0 * fTemp14);
			fRec15[0] = (iTemp1?0.0f:min(fTemp15, (fRec15[1] + (1.0f - (fConst0 * (fVec6[1] - fTemp14))))));
			int iTemp16 = (fRec15[0] < fConst2);
			fRec16[0] = ((fSlow25 * fRec17[1]) + (fSlow26 * fRec16[1]));
			fRec17[0] = (((fSlow26 * fRec17[1]) + (fSlow27 * fRec16[1])) + float(iTemp0));
			float fTemp17 = ((0.333333343f * fRec3[0]) + 0.00100000005f);
			fVec7[0] = fTemp17;
			float fTemp18 = (fConst0 * fTemp17);
			fRec18[0] = (iTemp1?0.0f:min(fTemp18, (fRec18[1] + (1.0f - (fConst0 * (fVec7[1] - fTemp17))))));
			int iTemp19 = (fRec18[0] < fConst2);
			output0[i] = FAUSTFLOAT((0.0500000007f * ((((((0.444444448f * (fRec0[0] * (iTemp4?((fRec2[0] < 0.0f)?0.0f:(iTemp4?(fConst4 * fRec2[0]):1.0f)):((fRec2[0] < fTemp3)?((fConst3 * ((0.0f - (fRec2[0] - fConst2)) / (fTemp2 + -0.00100000005f))) + 1.0f):0.0f)))) + (fRec4[0] * (0.0f - (0.111111112f * (iTemp7?((fRec6[0] < 0.0f)?0.0f:(iTemp7?(fConst4 * fRec6[0]):1.0f)):((fRec6[0] < fTemp6)?((fConst3 * ((0.0f - (fRec6[0] - fConst2)) / (fTemp5 + -0.00100000005f))) + 1.0f):0.0f)))))) + (fRec7[0] * (0.0f - (0.666666687f * (iTemp10?((fRec9[0] < 0.0f)?0.0f:(iTemp10?(fConst4 * fRec9[0]):1.0f)):((fRec9[0] < fTemp9)?((fConst3 * ((0.0f - (fRec9[0] - fConst2)) / (fTemp8 + -0.00100000005f))) + 1.0f):0.0f)))))) + (fRec10[0] * (0.0f - (1.22222221f * (iTemp13?((fRec12[0] < 0.0f)?0.0f:(iTemp13?(fConst4 * fRec12[0]):1.0f)):((fRec12[0] < fTemp12)?((fConst3 * ((0.0f - (fRec12[0] - fConst2)) / (fTemp11 + -0.00100000005f))) + 1.0f):0.0f)))))) + (fRec13[0] * (0.0f - (1.77777779f * (iTemp16?((fRec15[0] < 0.0f)?0.0f:(iTemp16?(fConst4 * fRec15[0]):1.0f)):((fRec15[0] < fTemp15)?((fConst3 * ((0.0f - (fRec15[0] - fConst2)) / (fTemp14 + -0.00100000005f))) + 1.0f):0.0f)))))) + (fRec16[0] * (0.0f - (2.33333325f * (iTemp19?((fRec18[0] < 0.0f)?0.0f:(iTemp19?(fConst4 * fRec18[0]):1.0f)):((fRec18[0] < fTemp18)?((fConst3 * ((0.0f - (fRec18[0] - fConst2)) / (fTemp17 + -0.00100000005f))) + 1.0f):0.0f))))))));
			iVec0[1] = iVec0[0];
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			fVec1[1] = fVec1[0];
			fRec3[1] = fRec3[0];
			fVec2[1] = fVec2[0];
			fRec2[1] = fRec2[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fVec3[1] = fVec3[0];
			fRec6[1] = fRec6[0];
			fRec7[1] = fRec7[0];
			fRec8[1] = fRec8[0];
			fVec4[1] = fVec4[0];
			fRec9[1] = fRec9[0];
			fRec10[1] = fRec10[0];
			fRec11[1] = fRec11[0];
			fVec5[1] = fVec5[0];
			fRec12[1] = fRec12[0];
			fRec13[1] = fRec13[0];
			fRec14[1] = fRec14[0];
			fVec6[1] = fVec6[0];
			fRec15[1] = fRec15[0];
			fRec16[1] = fRec16[0];
			fRec17[1] = fRec17[0];
			fVec7[1] = fVec7[0];
			fRec18[1] = fRec18[0];
			
		}
		
	}

	
};

#endif
