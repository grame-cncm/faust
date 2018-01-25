//----------------------------------------------------------
// name: "bowed"
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
	int 	iVec0[2];
	FAUSTFLOAT 	fslider0;
	float 	fRec2[2];
	float 	fTempPerm0;
	float 	fConst0;
	float 	fConst1;
	float 	fConst2;
	float 	fTempPerm1;
	float 	fRec1[2];
	float 	fRec0[2];
	float 	fConst3;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fslider3;
	float 	fRec6[2];
	float 	fRec5[2];
	FAUSTFLOAT 	fslider4;
	float 	fRec9[2];
	float 	fTempPerm2;
	float 	fTempPerm3;
	float 	fTempPerm4;
	float 	fTempPerm5;
	float 	fRec7[2];
	int 	iTempPerm6;
	float 	fRec8[2];
	float 	fRec12[2];
	float 	fTempPerm7;
	float 	fTempPerm8;
	float 	fRec11[2];
	float 	fRec10[2];
	float 	fTempPerm9;
	float 	fTempPerm10;
	float 	fTempPerm11;
	float 	fTempPerm12;
	float 	fRec3[2];
	float 	fRec4[2];
	float 	fRec16[2];
	float 	fRec15[2];
	float 	fTempPerm13;
	float 	fTempPerm14;
	float 	fTempPerm15;
	float 	fRec17[2];
	float 	fRec18[2];
	float 	fTempPerm16;
	float 	fTempPerm17;
	float 	fTempPerm18;
	float 	fRec13[2];
	float 	fRec14[2];
	float 	fRec22[2];
	float 	fRec21[2];
	float 	fTempPerm19;
	float 	fTempPerm20;
	float 	fTempPerm21;
	float 	fRec23[2];
	float 	fRec24[2];
	float 	fTempPerm22;
	float 	fTempPerm23;
	float 	fTempPerm24;
	float 	fRec19[2];
	float 	fRec20[2];
	float 	fRec28[2];
	float 	fRec27[2];
	float 	fTempPerm25;
	float 	fTempPerm26;
	float 	fTempPerm27;
	float 	fRec29[2];
	float 	fRec30[2];
	float 	fTempPerm28;
	float 	fTempPerm29;
	float 	fTempPerm30;
	float 	fRec25[2];
	float 	fRec26[2];
	float 	fTempPerm31;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
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

	virtual int getNumInputs() { return 0; }
	virtual int getNumOutputs() { return 2; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fTempPerm0 = 0;
		fConst0 = min(192000.0f, max(1.0f, (float)fSamplingFreq));
		fConst1 = expf((0 - (1.0f / fConst0)));
		fConst2 = expf((0 - (10.0f / fConst0)));
		fTempPerm1 = 0;
		fConst3 = (6.2831853071795862f / fConst0);
		fTempPerm2 = 0;
		fTempPerm3 = 0;
		fTempPerm4 = 0;
		fTempPerm5 = 0;
		iTempPerm6 = 0;
		fTempPerm7 = 0;
		fTempPerm8 = 0;
		fTempPerm9 = 0;
		fTempPerm10 = 0;
		fTempPerm11 = 0;
		fTempPerm12 = 0;
		fTempPerm13 = 0;
		fTempPerm14 = 0;
		fTempPerm15 = 0;
		fTempPerm16 = 0;
		fTempPerm17 = 0;
		fTempPerm18 = 0;
		fTempPerm19 = 0;
		fTempPerm20 = 0;
		fTempPerm21 = 0;
		fTempPerm22 = 0;
		fTempPerm23 = 0;
		fTempPerm24 = 0;
		fTempPerm25 = 0;
		fTempPerm26 = 0;
		fTempPerm27 = 0;
		fTempPerm28 = 0;
		fTempPerm29 = 0;
		fTempPerm30 = 0;
		fTempPerm31 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.5f;
		fslider1 = 0.0f;
		fslider2 = 400.0f;
		fslider3 = 1.0f;
		fslider4 = 0.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) iVec0[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) fRec9[i] = 0;
		for (int i=0; i<2; i++) fRec7[i] = 0;
		for (int i=0; i<2; i++) fRec8[i] = 0;
		for (int i=0; i<2; i++) fRec12[i] = 0;
		for (int i=0; i<2; i++) fRec11[i] = 0;
		for (int i=0; i<2; i++) fRec10[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2; i++) fRec16[i] = 0;
		for (int i=0; i<2; i++) fRec15[i] = 0;
		for (int i=0; i<2; i++) fRec17[i] = 0;
		for (int i=0; i<2; i++) fRec18[i] = 0;
		for (int i=0; i<2; i++) fRec13[i] = 0;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		for (int i=0; i<2; i++) fRec22[i] = 0;
		for (int i=0; i<2; i++) fRec21[i] = 0;
		for (int i=0; i<2; i++) fRec23[i] = 0;
		for (int i=0; i<2; i++) fRec24[i] = 0;
		for (int i=0; i<2; i++) fRec19[i] = 0;
		for (int i=0; i<2; i++) fRec20[i] = 0;
		for (int i=0; i<2; i++) fRec28[i] = 0;
		for (int i=0; i<2; i++) fRec27[i] = 0;
		for (int i=0; i<2; i++) fRec29[i] = 0;
		for (int i=0; i<2; i++) fRec30[i] = 0;
		for (int i=0; i<2; i++) fRec25[i] = 0;
		for (int i=0; i<2; i++) fRec26[i] = 0;
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
		ui_interface->addHorizontalSlider("bend", &fslider3, 1.0f, 0.0f, 10.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider2, 400.0f, 50.0f, 2000.0f, 0.01f);
		ui_interface->addHorizontalSlider("keyboard", &fslider1, 0.0f, 0.0f, 5.0f, 1.0f);
		ui_interface->addHorizontalSlider("x", &fslider0, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("y", &fslider4, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = (0.0010000000000000009f * float(fslider0));
		int 	iSlow1 = int(float(fslider1));
		int 	iSlow2 = int((iSlow1 == 3));
		float 	fSlow3 = (float(fslider2) * float(fslider3));
		float 	fSlow4 = (0.0010000000000000009f * float(fslider4));
		int 	iSlow5 = int((iSlow1 == 2));
		int 	iSlow6 = int((iSlow1 == 0));
		int 	iSlow7 = int((iSlow1 == 1));
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			iVec0[0] = 1;
			fRec2[0] = (fSlow0 + (0.999f * fRec2[1]));
			fTempPerm0 = fabsf(fabsf((fRec2[0] - fRec2[1])));
			fTempPerm1 = ((int((fRec0[1] > fTempPerm0)))?fConst1:fConst2);
			fRec1[0] = ((fRec1[1] * fTempPerm1) + (fTempPerm0 * (1.0f - fTempPerm1)));
			fRec0[0] = fRec1[0];
			fRec6[0] = ((iSlow2)?fSlow3:fRec6[1]);
			fRec5[0] = ((0.999f * fRec5[1]) + (0.0010000000000000009f * fRec6[0]));
			fRec9[0] = (fSlow4 + (0.999f * fRec9[1]));
			fTempPerm2 = ((0.29999999999999999f * fRec9[0]) + 1);
			fTempPerm3 = (fConst3 * (fRec5[0] * fTempPerm2));
			fTempPerm4 = sinf(fTempPerm3);
			fTempPerm5 = cosf(fTempPerm3);
			fRec7[0] = ((fRec8[1] * fTempPerm4) + (fRec7[1] * fTempPerm5));
			iTempPerm6 = (1 - iVec0[1]);
			fRec8[0] = (((fRec8[1] * fTempPerm5) + (fRec7[1] * (0 - fTempPerm4))) + iTempPerm6);
			fRec12[0] = (fSlow0 + (0.999f * fRec12[1]));
			fTempPerm7 = fabsf(fabsf((fRec12[0] - fRec12[1])));
			fTempPerm8 = ((int((fRec10[1] > fTempPerm7)))?fConst1:fConst2);
			fRec11[0] = ((fRec11[1] * fTempPerm8) + (fTempPerm7 * (1.0f - fTempPerm8)));
			fRec10[0] = fRec11[0];
			fTempPerm9 = min((float)1, (8000 * fRec10[0]));
			fTempPerm10 = (fConst3 * (fRec5[0] + (1000 * (fRec7[0] * fTempPerm9))));
			fTempPerm11 = sinf(fTempPerm10);
			fTempPerm12 = cosf(fTempPerm10);
			fRec3[0] = ((fRec4[1] * fTempPerm11) + (fRec3[1] * fTempPerm12));
			fRec4[0] = (((fRec4[1] * fTempPerm12) + (fRec3[1] * (0 - fTempPerm11))) + iTempPerm6);
			fRec16[0] = ((iSlow5)?fSlow3:fRec16[1]);
			fRec15[0] = ((0.999f * fRec15[1]) + (0.0010000000000000009f * fRec16[0]));
			fTempPerm13 = (fConst3 * (fRec15[0] * fTempPerm2));
			fTempPerm14 = sinf(fTempPerm13);
			fTempPerm15 = cosf(fTempPerm13);
			fRec17[0] = ((fRec18[1] * fTempPerm14) + (fRec17[1] * fTempPerm15));
			fRec18[0] = (((fRec18[1] * fTempPerm15) + (fRec17[1] * (0 - fTempPerm14))) + iTempPerm6);
			fTempPerm16 = (fConst3 * (fRec15[0] + (1000 * (fRec17[0] * fTempPerm9))));
			fTempPerm17 = sinf(fTempPerm16);
			fTempPerm18 = cosf(fTempPerm16);
			fRec13[0] = ((fRec14[1] * fTempPerm17) + (fRec13[1] * fTempPerm18));
			fRec14[0] = (((fRec14[1] * fTempPerm18) + (fRec13[1] * (0 - fTempPerm17))) + iTempPerm6);
			fRec22[0] = ((iSlow6)?fSlow3:fRec22[1]);
			fRec21[0] = ((0.999f * fRec21[1]) + (0.0010000000000000009f * fRec22[0]));
			fTempPerm19 = (fConst3 * (fRec21[0] * fTempPerm2));
			fTempPerm20 = sinf(fTempPerm19);
			fTempPerm21 = cosf(fTempPerm19);
			fRec23[0] = ((fRec24[1] * fTempPerm20) + (fRec23[1] * fTempPerm21));
			fRec24[0] = (((fRec24[1] * fTempPerm21) + (fRec23[1] * (0 - fTempPerm20))) + iTempPerm6);
			fTempPerm22 = (fConst3 * (fRec21[0] + (1000 * (fRec23[0] * fTempPerm9))));
			fTempPerm23 = sinf(fTempPerm22);
			fTempPerm24 = cosf(fTempPerm22);
			fRec19[0] = ((fRec20[1] * fTempPerm23) + (fRec19[1] * fTempPerm24));
			fRec20[0] = (((fRec20[1] * fTempPerm24) + (fRec19[1] * (0 - fTempPerm23))) + iTempPerm6);
			fRec28[0] = ((iSlow7)?fSlow3:fRec28[1]);
			fRec27[0] = ((0.999f * fRec27[1]) + (0.0010000000000000009f * fRec28[0]));
			fTempPerm25 = (fConst3 * (fRec27[0] * fTempPerm2));
			fTempPerm26 = sinf(fTempPerm25);
			fTempPerm27 = cosf(fTempPerm25);
			fRec29[0] = ((fRec30[1] * fTempPerm26) + (fRec29[1] * fTempPerm27));
			fRec30[0] = (((fRec30[1] * fTempPerm27) + (fRec29[1] * (0 - fTempPerm26))) + iTempPerm6);
			fTempPerm28 = (fConst3 * (fRec27[0] + (1000 * (fRec29[0] * fTempPerm9))));
			fTempPerm29 = sinf(fTempPerm28);
			fTempPerm30 = cosf(fTempPerm28);
			fRec25[0] = ((fRec26[1] * fTempPerm29) + (fRec25[1] * fTempPerm30));
			fRec26[0] = (((fRec26[1] * fTempPerm30) + (fRec25[1] * (0 - fTempPerm29))) + iTempPerm6);
			fTempPerm31 = (min((float)1, (8000 * fRec0[0])) * (fRec3[0] + (fRec13[0] + (fRec19[0] + fRec25[0]))));
			output0[i] = (FAUSTFLOAT)fTempPerm31;
			output1[i] = (FAUSTFLOAT)fTempPerm31;
			// post processing
			fRec26[1] = fRec26[0];
			fRec25[1] = fRec25[0];
			fRec30[1] = fRec30[0];
			fRec29[1] = fRec29[0];
			fRec27[1] = fRec27[0];
			fRec28[1] = fRec28[0];
			fRec20[1] = fRec20[0];
			fRec19[1] = fRec19[0];
			fRec24[1] = fRec24[0];
			fRec23[1] = fRec23[0];
			fRec21[1] = fRec21[0];
			fRec22[1] = fRec22[0];
			fRec14[1] = fRec14[0];
			fRec13[1] = fRec13[0];
			fRec18[1] = fRec18[0];
			fRec17[1] = fRec17[0];
			fRec15[1] = fRec15[0];
			fRec16[1] = fRec16[0];
			fRec4[1] = fRec4[0];
			fRec3[1] = fRec3[0];
			fRec10[1] = fRec10[0];
			fRec11[1] = fRec11[0];
			fRec12[1] = fRec12[0];
			fRec8[1] = fRec8[0];
			fRec7[1] = fRec7[0];
			fRec9[1] = fRec9[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			iVec0[1] = iVec0[0];
		}
	}
};


