/* ------------------------------------------------------------
name: "bowed"
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
	
	int iVec0[2];
	FAUSTFLOAT fHslider0;
	float fRec2[2];
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	float fRec1[2];
	float fRec0[2];
	float fConst3;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	float fRec6[2];
	float fRec5[2];
	FAUSTFLOAT fHslider4;
	float fRec9[2];
	float fRec7[2];
	float fRec8[2];
	float fRec12[2];
	float fRec11[2];
	float fRec10[2];
	float fRec3[2];
	float fRec4[2];
	float fRec16[2];
	float fRec15[2];
	float fRec17[2];
	float fRec18[2];
	float fRec13[2];
	float fRec14[2];
	float fRec22[2];
	float fRec21[2];
	float fRec23[2];
	float fRec24[2];
	float fRec19[2];
	float fRec20[2];
	float fRec28[2];
	float fRec27[2];
	float fRec29[2];
	float fRec30[2];
	float fRec25[2];
	float fRec26[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "0.0");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("interface", "SmartKeyboard{  'Number of Keyboards':'5',  'Max Keyboard Polyphony':'0',  'Rounding Mode':'1',  'Keyboard 0 - Number of Keys':'19',  'Keyboard 1 - Number of Keys':'19',  'Keyboard 2 - Number of Keys':'19',  'Keyboard 3 - Number of Keys':'19',  'Keyboard 4 - Number of Keys':'1',  'Keyboard 4 - Send Freq':'0',  'Keyboard 0 - Send X':'0',  'Keyboard 1 - Send X':'0',  'Keyboard 2 - Send X':'0',  'Keyboard 3 - Send X':'0',  'Keyboard 0 - Send Y':'0',  'Keyboard 1 - Send Y':'0',  'Keyboard 2 - Send Y':'0',  'Keyboard 3 - Send Y':'0',  'Keyboard 0 - Lowest Key':'55',  'Keyboard 1 - Lowest Key':'62',  'Keyboard 2 - Lowest Key':'69',  'Keyboard 3 - Lowest Key':'76',  'Keyboard 4 - Piano Keyboard':'0',  'Keyboard 4 - Key 0 - Label':'Bow' }");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "bowed");
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
		fConst0 = min(192000.0f, max(1.0f, float(fSamplingFreq)));
		fConst1 = expf((0.0f - (10.0f / fConst0)));
		fConst2 = expf((0.0f - (1.0f / fConst0)));
		fConst3 = (6.28318548f / fConst0);
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.5f);
		fHslider1 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(400.0f);
		fHslider3 = FAUSTFLOAT(1.0f);
		fHslider4 = FAUSTFLOAT(0.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec2[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec1[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec0[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec6[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec5[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec9[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec7[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec8[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec12[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec11[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec10[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec3[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec4[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec16[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec15[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec17[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec18[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec13[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec14[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec22[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec21[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec23[l22] = 0.0f;
			
		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec24[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fRec19[l24] = 0.0f;
			
		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fRec20[l25] = 0.0f;
			
		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fRec28[l26] = 0.0f;
			
		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fRec27[l27] = 0.0f;
			
		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fRec29[l28] = 0.0f;
			
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec30[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fRec25[l30] = 0.0f;
			
		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			fRec26[l31] = 0.0f;
			
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
		ui_interface->openVerticalBox("bowed");
		ui_interface->addHorizontalSlider("bend", &fHslider3, 1.0f, 0.0f, 10.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("freq", &fHslider2, 400.0f, 50.0f, 2000.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("keyboard", &fHslider1, 0.0f, 0.0f, 5.0f, 1.0f);
		ui_interface->addHorizontalSlider("x", &fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("y", &fHslider4, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = (0.00100000005f * float(fHslider0));
		int iSlow1 = int(float(fHslider1));
		int iSlow2 = (iSlow1 == 3);
		float fSlow3 = (float(fHslider2) * float(fHslider3));
		float fSlow4 = (0.00100000005f * float(fHslider4));
		int iSlow5 = (iSlow1 == 2);
		int iSlow6 = (iSlow1 == 0);
		int iSlow7 = (iSlow1 == 1);
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			fRec2[0] = (fSlow0 + (0.999000013f * fRec2[1]));
			float fTemp0 = fabsf(fabsf((fRec2[0] - fRec2[1])));
			float fTemp1 = ((fRec0[1] > fTemp0)?fConst2:fConst1);
			fRec1[0] = ((fRec1[1] * fTemp1) + (fTemp0 * (1.0f - fTemp1)));
			fRec0[0] = fRec1[0];
			fRec6[0] = (iSlow2?fSlow3:fRec6[1]);
			fRec5[0] = ((0.999000013f * fRec5[1]) + (0.00100000005f * fRec6[0]));
			fRec9[0] = (fSlow4 + (0.999000013f * fRec9[1]));
			float fTemp2 = ((0.300000012f * fRec9[0]) + 1.0f);
			float fTemp3 = (fConst3 * (fRec5[0] * fTemp2));
			float fTemp4 = sinf(fTemp3);
			float fTemp5 = cosf(fTemp3);
			fRec7[0] = ((fRec8[1] * fTemp4) + (fRec7[1] * fTemp5));
			int iTemp6 = (1 - iVec0[1]);
			fRec8[0] = (((fRec8[1] * fTemp5) + (fRec7[1] * (0.0f - fTemp4))) + float(iTemp6));
			fRec12[0] = (fSlow0 + (0.999000013f * fRec12[1]));
			float fTemp7 = fabsf(fabsf((fRec12[0] - fRec12[1])));
			float fTemp8 = ((fRec10[1] > fTemp7)?fConst2:fConst1);
			fRec11[0] = ((fRec11[1] * fTemp8) + (fTemp7 * (1.0f - fTemp8)));
			fRec10[0] = fRec11[0];
			float fTemp9 = min(1.0f, (8000.0f * fRec10[0]));
			float fTemp10 = (fConst3 * (fRec5[0] + (1000.0f * (fRec7[0] * fTemp9))));
			float fTemp11 = sinf(fTemp10);
			float fTemp12 = cosf(fTemp10);
			fRec3[0] = ((fRec4[1] * fTemp11) + (fRec3[1] * fTemp12));
			fRec4[0] = (((fRec4[1] * fTemp12) + (fRec3[1] * (0.0f - fTemp11))) + float(iTemp6));
			fRec16[0] = (iSlow5?fSlow3:fRec16[1]);
			fRec15[0] = ((0.999000013f * fRec15[1]) + (0.00100000005f * fRec16[0]));
			float fTemp13 = (fConst3 * (fRec15[0] * fTemp2));
			float fTemp14 = sinf(fTemp13);
			float fTemp15 = cosf(fTemp13);
			fRec17[0] = ((fRec18[1] * fTemp14) + (fRec17[1] * fTemp15));
			fRec18[0] = (((fRec18[1] * fTemp15) + (fRec17[1] * (0.0f - fTemp14))) + float(iTemp6));
			float fTemp16 = (fConst3 * (fRec15[0] + (1000.0f * (fRec17[0] * fTemp9))));
			float fTemp17 = sinf(fTemp16);
			float fTemp18 = cosf(fTemp16);
			fRec13[0] = ((fRec14[1] * fTemp17) + (fRec13[1] * fTemp18));
			fRec14[0] = (((fRec14[1] * fTemp18) + (fRec13[1] * (0.0f - fTemp17))) + float(iTemp6));
			fRec22[0] = (iSlow6?fSlow3:fRec22[1]);
			fRec21[0] = ((0.999000013f * fRec21[1]) + (0.00100000005f * fRec22[0]));
			float fTemp19 = (fConst3 * (fRec21[0] * fTemp2));
			float fTemp20 = sinf(fTemp19);
			float fTemp21 = cosf(fTemp19);
			fRec23[0] = ((fRec24[1] * fTemp20) + (fRec23[1] * fTemp21));
			fRec24[0] = (((fRec24[1] * fTemp21) + (fRec23[1] * (0.0f - fTemp20))) + float(iTemp6));
			float fTemp22 = (fConst3 * (fRec21[0] + (1000.0f * (fRec23[0] * fTemp9))));
			float fTemp23 = sinf(fTemp22);
			float fTemp24 = cosf(fTemp22);
			fRec19[0] = ((fRec20[1] * fTemp23) + (fRec19[1] * fTemp24));
			fRec20[0] = (((fRec20[1] * fTemp24) + (fRec19[1] * (0.0f - fTemp23))) + float(iTemp6));
			fRec28[0] = (iSlow7?fSlow3:fRec28[1]);
			fRec27[0] = ((0.999000013f * fRec27[1]) + (0.00100000005f * fRec28[0]));
			float fTemp25 = (fConst3 * (fRec27[0] * fTemp2));
			float fTemp26 = sinf(fTemp25);
			float fTemp27 = cosf(fTemp25);
			fRec29[0] = ((fRec30[1] * fTemp26) + (fRec29[1] * fTemp27));
			fRec30[0] = (((fRec30[1] * fTemp27) + (fRec29[1] * (0.0f - fTemp26))) + float(iTemp6));
			float fTemp28 = (fConst3 * (fRec27[0] + (1000.0f * (fRec29[0] * fTemp9))));
			float fTemp29 = sinf(fTemp28);
			float fTemp30 = cosf(fTemp28);
			fRec25[0] = ((fRec26[1] * fTemp29) + (fRec25[1] * fTemp30));
			fRec26[0] = (((fRec26[1] * fTemp30) + (fRec25[1] * (0.0f - fTemp29))) + float(iTemp6));
			float fTemp31 = (min(1.0f, (8000.0f * fRec0[0])) * (fRec3[0] + (fRec13[0] + (fRec19[0] + fRec25[0]))));
			output0[i] = FAUSTFLOAT(fTemp31);
			output1[i] = FAUSTFLOAT(fTemp31);
			iVec0[1] = iVec0[0];
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
			fRec6[1] = fRec6[0];
			fRec5[1] = fRec5[0];
			fRec9[1] = fRec9[0];
			fRec7[1] = fRec7[0];
			fRec8[1] = fRec8[0];
			fRec12[1] = fRec12[0];
			fRec11[1] = fRec11[0];
			fRec10[1] = fRec10[0];
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec16[1] = fRec16[0];
			fRec15[1] = fRec15[0];
			fRec17[1] = fRec17[0];
			fRec18[1] = fRec18[0];
			fRec13[1] = fRec13[0];
			fRec14[1] = fRec14[0];
			fRec22[1] = fRec22[0];
			fRec21[1] = fRec21[0];
			fRec23[1] = fRec23[0];
			fRec24[1] = fRec24[0];
			fRec19[1] = fRec19[0];
			fRec20[1] = fRec20[0];
			fRec28[1] = fRec28[0];
			fRec27[1] = fRec27[0];
			fRec29[1] = fRec29[0];
			fRec30[1] = fRec30[0];
			fRec25[1] = fRec25[0];
			fRec26[1] = fRec26[0];
			
		}
		
	}

	
};

#endif
