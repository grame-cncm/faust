//----------------------------------------------------------
// name: "turenas"
//
// Code generated with Faust 2.5.15 (https://faust.grame.fr)
//----------------------------------------------------------

/* link with  */
#include <math.h>

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


#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

class mydsp : public dsp {
  private:
	float 	fConst0;
	float 	fConst1;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fslider1;
	int 	iVec0[2];
	float 	fRec0[2];
	int 	iTempPerm0;
	float 	fRec1[2];
	FAUSTFLOAT 	fbutton0;
	float 	fVec1[2];
	int 	iTempPerm1;
	FAUSTFLOAT 	fslider2;
	float 	fRec3[2];
	float 	fTempPerm2;
	float 	fVec2[2];
	float 	fTempPerm3;
	float 	fRec2[2];
	float 	fConst2;
	int 	iTempPerm4;
	float 	fConst3;
	float 	fConst4;
	float 	fRec4[2];
	float 	fRec5[2];
	float 	fTempPerm5;
	float 	fVec3[2];
	float 	fTempPerm6;
	float 	fRec6[2];
	int 	iTempPerm7;
	float 	fRec7[2];
	float 	fRec8[2];
	float 	fTempPerm8;
	float 	fVec4[2];
	float 	fTempPerm9;
	float 	fRec9[2];
	int 	iTempPerm10;
	float 	fRec10[2];
	float 	fRec11[2];
	float 	fTempPerm11;
	float 	fVec5[2];
	float 	fTempPerm12;
	float 	fRec12[2];
	int 	iTempPerm13;
	float 	fRec13[2];
	float 	fRec14[2];
	float 	fTempPerm14;
	float 	fVec6[2];
	float 	fTempPerm15;
	float 	fRec15[2];
	int 	iTempPerm16;
	float 	fRec16[2];
	float 	fRec17[2];
	float 	fTempPerm17;
	float 	fVec7[2];
	float 	fTempPerm18;
	float 	fRec18[2];
	int 	iTempPerm19;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
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

	virtual int getNumInputs() { return 0; }
	virtual int getNumOutputs() { return 1; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(192000.0f, max(1.0f, (float)fSamplingFreq));
		fConst1 = (6.2831853071795862f / fConst0);
		iTempPerm0 = 0;
		iTempPerm1 = 0;
		fTempPerm2 = 0;
		fTempPerm3 = 0;
		fConst2 = (0.001f * fConst0);
		iTempPerm4 = 0;
		fConst3 = (1000.0f / fConst0);
		fConst4 = (1.0f / fConst0);
		fTempPerm5 = 0;
		fTempPerm6 = 0;
		iTempPerm7 = 0;
		fTempPerm8 = 0;
		fTempPerm9 = 0;
		iTempPerm10 = 0;
		fTempPerm11 = 0;
		fTempPerm12 = 0;
		iTempPerm13 = 0;
		fTempPerm14 = 0;
		fTempPerm15 = 0;
		iTempPerm16 = 0;
		fTempPerm17 = 0;
		fTempPerm18 = 0;
		iTempPerm19 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 400.0f;
		fslider1 = 0.0f;
		fbutton0 = 0.0;
		fslider2 = 2.5f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) iVec0[i] = 0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fVec2[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) fVec3[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<2; i++) fRec7[i] = 0;
		for (int i=0; i<2; i++) fRec8[i] = 0;
		for (int i=0; i<2; i++) fVec4[i] = 0;
		for (int i=0; i<2; i++) fRec9[i] = 0;
		for (int i=0; i<2; i++) fRec10[i] = 0;
		for (int i=0; i<2; i++) fRec11[i] = 0;
		for (int i=0; i<2; i++) fVec5[i] = 0;
		for (int i=0; i<2; i++) fRec12[i] = 0;
		for (int i=0; i<2; i++) fRec13[i] = 0;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		for (int i=0; i<2; i++) fVec6[i] = 0;
		for (int i=0; i<2; i++) fRec15[i] = 0;
		for (int i=0; i<2; i++) fRec16[i] = 0;
		for (int i=0; i<2; i++) fRec17[i] = 0;
		for (int i=0; i<2; i++) fVec7[i] = 0;
		for (int i=0; i<2; i++) fRec18[i] = 0;
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
		ui_interface->addHorizontalSlider("freq", &fslider0, 400.0f, 50.0f, 2000.0f, 0.01f);
		ui_interface->addButton("gate", &fbutton0);
		ui_interface->declare(&fslider2, "acc", "0 0 -10 0 10");
		ui_interface->addHorizontalSlider("res", &fslider2, 2.5f, 0.01f, 5.0f, 0.01f);
		ui_interface->addHorizontalSlider("y", &fslider1, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = float(fslider0);
		float 	fSlow1 = float(fslider1);
		float 	fSlow2 = (fConst1 * (fSlow0 * ((0.83333333333333326f * fSlow1) + 1)));
		float 	fSlow3 = sinf(fSlow2);
		float 	fSlow4 = cosf(fSlow2);
		float 	fSlow5 = (0 - fSlow3);
		float 	fSlow6 = float(fbutton0);
		float 	fSlow7 = (0.0010000000000000009f * float(fslider2));
		float 	fSlow8 = (fConst1 * (fSlow0 * ((1.6666666666666665f * fSlow1) + 1)));
		float 	fSlow9 = sinf(fSlow8);
		float 	fSlow10 = cosf(fSlow8);
		float 	fSlow11 = (0 - fSlow9);
		float 	fSlow12 = (fConst1 * (fSlow0 * ((2.5f * fSlow1) + 1)));
		float 	fSlow13 = sinf(fSlow12);
		float 	fSlow14 = cosf(fSlow12);
		float 	fSlow15 = (0 - fSlow13);
		float 	fSlow16 = (fConst1 * (fSlow0 * ((3.333333333333333f * fSlow1) + 1)));
		float 	fSlow17 = sinf(fSlow16);
		float 	fSlow18 = cosf(fSlow16);
		float 	fSlow19 = (0 - fSlow17);
		float 	fSlow20 = (fConst1 * (fSlow0 * ((4.166666666666667f * fSlow1) + 1)));
		float 	fSlow21 = sinf(fSlow20);
		float 	fSlow22 = cosf(fSlow20);
		float 	fSlow23 = (0 - fSlow21);
		float 	fSlow24 = (fConst1 * (fSlow0 * ((5 * fSlow1) + 1)));
		float 	fSlow25 = sinf(fSlow24);
		float 	fSlow26 = cosf(fSlow24);
		float 	fSlow27 = (0 - fSlow25);
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			iVec0[0] = 1;
			fRec0[0] = ((fSlow3 * fRec1[1]) + (fSlow4 * fRec0[1]));
			iTempPerm0 = (1 - iVec0[1]);
			fRec1[0] = (((fSlow4 * fRec1[1]) + (fSlow5 * fRec0[1])) + iTempPerm0);
			fVec1[0] = fSlow6;
			iTempPerm1 = int((((fSlow6 - fVec1[1]) > 0) > 0));
			fRec3[0] = (fSlow7 + (0.999f * fRec3[1]));
			fTempPerm2 = (fRec3[0] + 0.001f);
			fVec2[0] = fTempPerm2;
			fTempPerm3 = (fConst0 * fVec2[0]);
			fRec2[0] = ((iTempPerm1)?0:min(fTempPerm3, (fRec2[1] + (1 - (fConst0 * (fVec2[1] - fVec2[0]))))));
			iTempPerm4 = int((fRec2[0] < fConst2));
			fRec4[0] = ((fSlow9 * fRec5[1]) + (fSlow10 * fRec4[1]));
			fRec5[0] = (((fSlow10 * fRec5[1]) + (fSlow11 * fRec4[1])) + iTempPerm0);
			fTempPerm5 = ((0.8666666666666667f * fRec3[0]) + 0.001f);
			fVec3[0] = fTempPerm5;
			fTempPerm6 = (fConst0 * fVec3[0]);
			fRec6[0] = ((iTempPerm1)?0:min(fTempPerm6, (fRec6[1] + (1 - (fConst0 * (fVec3[1] - fVec3[0]))))));
			iTempPerm7 = int((fRec6[0] < fConst2));
			fRec7[0] = ((fSlow13 * fRec8[1]) + (fSlow14 * fRec7[1]));
			fRec8[0] = (((fSlow14 * fRec8[1]) + (fSlow15 * fRec7[1])) + iTempPerm0);
			fTempPerm8 = ((0.73333333333333339f * fRec3[0]) + 0.001f);
			fVec4[0] = fTempPerm8;
			fTempPerm9 = (fConst0 * fVec4[0]);
			fRec9[0] = ((iTempPerm1)?0:min(fTempPerm9, (fRec9[1] + (1 - (fConst0 * (fVec4[1] - fVec4[0]))))));
			iTempPerm10 = int((fRec9[0] < fConst2));
			fRec10[0] = ((fSlow17 * fRec11[1]) + (fSlow18 * fRec10[1]));
			fRec11[0] = (((fSlow18 * fRec11[1]) + (fSlow19 * fRec10[1])) + iTempPerm0);
			fTempPerm11 = ((0.59999999999999998f * fRec3[0]) + 0.001f);
			fVec5[0] = fTempPerm11;
			fTempPerm12 = (fConst0 * fVec5[0]);
			fRec12[0] = ((iTempPerm1)?0:min(fTempPerm12, (fRec12[1] + (1 - (fConst0 * (fVec5[1] - fVec5[0]))))));
			iTempPerm13 = int((fRec12[0] < fConst2));
			fRec13[0] = ((fSlow21 * fRec14[1]) + (fSlow22 * fRec13[1]));
			fRec14[0] = (((fSlow22 * fRec14[1]) + (fSlow23 * fRec13[1])) + iTempPerm0);
			fTempPerm14 = ((0.46666666666666667f * fRec3[0]) + 0.001f);
			fVec6[0] = fTempPerm14;
			fTempPerm15 = (fConst0 * fVec6[0]);
			fRec15[0] = ((iTempPerm1)?0:min(fTempPerm15, (fRec15[1] + (1 - (fConst0 * (fVec6[1] - fVec6[0]))))));
			iTempPerm16 = int((fRec15[0] < fConst2));
			fRec16[0] = ((fSlow25 * fRec17[1]) + (fSlow26 * fRec16[1]));
			fRec17[0] = (((fSlow26 * fRec17[1]) + (fSlow27 * fRec16[1])) + iTempPerm0);
			fTempPerm17 = ((0.33333333333333326f * fRec3[0]) + 0.001f);
			fVec7[0] = fTempPerm17;
			fTempPerm18 = (fConst0 * fVec7[0]);
			fRec18[0] = ((iTempPerm1)?0:min(fTempPerm18, (fRec18[1] + (1 - (fConst0 * (fVec7[1] - fVec7[0]))))));
			iTempPerm19 = int((fRec18[0] < fConst2));
			output0[i] = (FAUSTFLOAT)(0.050000000000000003f * ((((((0.44444444444444442f * (fRec0[0] * ((iTempPerm4)?((int((fRec2[0] < 0)))?0:((iTempPerm4)?(fConst3 * fRec2[0]):1)):((int((fRec2[0] < fTempPerm3)))?((fConst4 * ((0 - (fRec2[0] - fConst2)) / (fVec2[0] + -0.001f))) + 1):0)))) + (fRec4[0] * (0 - (0.11111111111111116f * ((iTempPerm7)?((int((fRec6[0] < 0)))?0:((iTempPerm7)?(fConst3 * fRec6[0]):1)):((int((fRec6[0] < fTempPerm6)))?((fConst4 * ((0 - (fRec6[0] - fConst2)) / (fVec3[0] + -0.001f))) + 1):0)))))) + (fRec7[0] * (0 - (0.66666666666666674f * ((iTempPerm10)?((int((fRec9[0] < 0)))?0:((iTempPerm10)?(fConst3 * fRec9[0]):1)):((int((fRec9[0] < fTempPerm9)))?((fConst4 * ((0 - (fRec9[0] - fConst2)) / (fVec4[0] + -0.001f))) + 1):0)))))) + (fRec10[0] * (0 - (1.2222222222222223f * ((iTempPerm13)?((int((fRec12[0] < 0)))?0:((iTempPerm13)?(fConst3 * fRec12[0]):1)):((int((fRec12[0] < fTempPerm12)))?((fConst4 * ((0 - (fRec12[0] - fConst2)) / (fVec5[0] + -0.001f))) + 1):0)))))) + (fRec13[0] * (0 - (1.7777777777777781f * ((iTempPerm16)?((int((fRec15[0] < 0)))?0:((iTempPerm16)?(fConst3 * fRec15[0]):1)):((int((fRec15[0] < fTempPerm15)))?((fConst4 * ((0 - (fRec15[0] - fConst2)) / (fVec6[0] + -0.001f))) + 1):0)))))) + (fRec16[0] * (0 - (2.3333333333333335f * ((iTempPerm19)?((int((fRec18[0] < 0)))?0:((iTempPerm19)?(fConst3 * fRec18[0]):1)):((int((fRec18[0] < fTempPerm18)))?((fConst4 * ((0 - (fRec18[0] - fConst2)) / (fVec7[0] + -0.001f))) + 1):0)))))));
			// post processing
			fRec18[1] = fRec18[0];
			fVec7[1] = fVec7[0];
			fRec17[1] = fRec17[0];
			fRec16[1] = fRec16[0];
			fRec15[1] = fRec15[0];
			fVec6[1] = fVec6[0];
			fRec14[1] = fRec14[0];
			fRec13[1] = fRec13[0];
			fRec12[1] = fRec12[0];
			fVec5[1] = fVec5[0];
			fRec11[1] = fRec11[0];
			fRec10[1] = fRec10[0];
			fRec9[1] = fRec9[0];
			fVec4[1] = fVec4[0];
			fRec8[1] = fRec8[0];
			fRec7[1] = fRec7[0];
			fRec6[1] = fRec6[0];
			fVec3[1] = fVec3[0];
			fRec5[1] = fRec5[0];
			fRec4[1] = fRec4[0];
			fRec2[1] = fRec2[0];
			fVec2[1] = fVec2[0];
			fRec3[1] = fRec3[0];
			fVec1[1] = fVec1[0];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
			iVec0[1] = iVec0[0];
		}
	}
};


