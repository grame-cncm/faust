//----------------------------------------------------------
// name: "clarinet"
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
	int 	iRec6[2];
	float 	fRec13[2];
	float 	fConst0;
	float 	fConst1;
	float 	fConst2;
	float 	fTempPerm0;
	float 	fRec18[2];
	float 	fRec17[2];
	float 	fTempPerm1;
	float 	fRec14[2];
	float 	fTempPerm2;
	FAUSTFLOAT 	fslider0;
	float 	fRec19[2];
	int 	IOTA;
	float 	fRec15[2048];
	float 	fConst3;
	float 	fConst4;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT 	fslider8;
	int 	iVec0[2];
	int 	iRec21[2];
	FAUSTFLOAT 	fslider9;
	int 	iVec1[2];
	int 	iRec22[2];
	float 	fRec20[2];
	float 	fTempPerm3;
	float 	fTempPerm4;
	int 	iTempPerm5;
	int 	iTempPerm6;
	float 	fTempPerm7;
	float 	fTempPerm8;
	float 	fTempPerm9;
	float 	fTempPerm10;
	float 	fTempPerm11;
	float 	fTempPerm12;
	float 	fTempPerm13;
	float 	fTempPerm14;
	float 	fTempPerm15;
	float 	fTempPerm16;
	int 	iTempPerm17;
	float 	fTempPerm18;
	float 	fTempPerm19;
	int 	iTempPerm20;
	float 	fTempPerm21;
	float 	fTempPerm22;
	float 	fTempPerm23;
	float 	fTempPerm24;
	int 	iTempPerm25;
	float 	fTempPerm26;
	float 	fTempPerm27;
	int 	iTempPerm28;
	float 	fVec2[2];
	float 	fRec11[2];
	float 	fRec2[2048];
	float 	fRec0[2];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "0.0");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("interface", "SmartKeyboard{  'Number of Keyboards':'2',  'Max Keyboard Polyphony':'0',  'Keyboard 0 - Number of Keys':'4',   'Keyboard 1 - Number of Keys':'5',  'Keyboard 0 - Send Freq':'0',   'Keyboard 1 - Send Freq':'0',  'Keyboard 0 - Piano Keyboard':'0',   'Keyboard 1 - Piano Keyboard':'0',  'Keyboard 0 - Send Key Status':'1',  'Keyboard 1 - Send Key Status':'1',  'Keyboard 0 - Key 3 - Label':'O+',  'Keyboard 1 - Key 4 - Label':'O-' }");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "clarinet");
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
	}

	virtual int getNumInputs() { return 1; }
	virtual int getNumOutputs() { return 2; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(192000.0f, max(1.0f, (float)fSamplingFreq));
		fConst1 = expf((0 - (50.0f / fConst0)));
		fConst2 = (1.0f - fConst1);
		fTempPerm0 = 0;
		fTempPerm1 = 0;
		fTempPerm2 = 0;
		fConst3 = (0.0088235294117647058f * fConst0);
		fConst4 = (0.0014705882352941176f * fConst0);
		fTempPerm3 = 0;
		fTempPerm4 = 0;
		iTempPerm5 = 0;
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
		iTempPerm17 = 0;
		fTempPerm18 = 0;
		fTempPerm19 = 0;
		iTempPerm20 = 0;
		fTempPerm21 = 0;
		fTempPerm22 = 0;
		fTempPerm23 = 0;
		fTempPerm24 = 0;
		iTempPerm25 = 0;
		fTempPerm26 = 0;
		fTempPerm27 = 0;
		iTempPerm28 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.0f;
		fslider1 = 0.0f;
		fslider2 = 0.0f;
		fslider3 = 0.0f;
		fslider4 = 0.0f;
		fslider5 = 0.0f;
		fslider6 = 0.0f;
		fslider7 = 0.0f;
		fslider8 = 0.0f;
		fslider9 = 0.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) iRec6[i] = 0;
		for (int i=0; i<2; i++) fRec13[i] = 0;
		for (int i=0; i<2; i++) fRec18[i] = 0;
		for (int i=0; i<2; i++) fRec17[i] = 0;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		for (int i=0; i<2; i++) fRec19[i] = 0;
		IOTA = 0;
		for (int i=0; i<2048; i++) fRec15[i] = 0;
		for (int i=0; i<2; i++) iVec0[i] = 0;
		for (int i=0; i<2; i++) iRec21[i] = 0;
		for (int i=0; i<2; i++) iVec1[i] = 0;
		for (int i=0; i<2; i++) iRec22[i] = 0;
		for (int i=0; i<2; i++) fRec20[i] = 0;
		for (int i=0; i<2; i++) fVec2[i] = 0;
		for (int i=0; i<2; i++) fRec11[i] = 0;
		for (int i=0; i<2048; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
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
		ui_interface->openVerticalBox("clarinet");
		ui_interface->addHorizontalSlider("kb0k0status", &fslider1, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->addHorizontalSlider("kb0k1status", &fslider2, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->addHorizontalSlider("kb0k2status", &fslider3, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->addHorizontalSlider("kb0k3status", &fslider8, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->addHorizontalSlider("kb1k0status", &fslider4, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->addHorizontalSlider("kb1k1status", &fslider5, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->addHorizontalSlider("kb1k2status", &fslider6, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->addHorizontalSlider("kb1k3status", &fslider7, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->addHorizontalSlider("kb1k4status", &fslider9, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->declare(&fslider0, "acc", "1 1 -10 0 10");
		ui_interface->addHorizontalSlider("reedStiffness", &fslider0, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = (0.0010000000000000009f * float(fslider0));
		int 	iSlow1 = int(min((float)1, float(fslider1)));
		int 	iSlow2 = (iSlow1 == 1);
		int 	iSlow3 = int(min((float)1, float(fslider2)));
		int 	iSlow4 = (iSlow3 == 1);
		int 	iSlow5 = (iSlow2 & iSlow4);
		int 	iSlow6 = int(min((float)1, float(fslider3)));
		int 	iSlow7 = (iSlow6 == 0);
		int 	iSlow8 = (iSlow5 & iSlow7);
		int 	iSlow9 = int(min((float)1, float(fslider4)));
		int 	iSlow10 = (iSlow9 == 0);
		int 	iSlow11 = int(min((float)1, float(fslider5)));
		int 	iSlow12 = (iSlow11 == 0);
		int 	iSlow13 = int(min((float)1, float(fslider6)));
		int 	iSlow14 = (iSlow13 == 0);
		int 	iSlow15 = int(min((float)1, float(fslider7)));
		int 	iSlow16 = (iSlow15 == 0);
		float 	fSlow17 = (4.0f * (1.0f - ((((iSlow8 & iSlow10) & iSlow12) & iSlow14) & iSlow16)));
		int 	iSlow18 = (iSlow6 == 1);
		int 	iSlow19 = (iSlow5 & iSlow18);
		int 	iSlow20 = (iSlow9 == 1);
		int 	iSlow21 = (iSlow19 & iSlow20);
		int 	iSlow22 = (iSlow11 == 1);
		int 	iSlow23 = (iSlow21 & iSlow22);
		int 	iSlow24 = (iSlow23 & (iSlow13 == 1));
		int 	iSlow25 = (iSlow15 == 1);
		int 	iSlow26 = (iSlow23 & iSlow14);
		int 	iSlow27 = (iSlow19 & iSlow10);
		int 	iSlow28 = (iSlow1 == 0);
		int 	iSlow29 = (iSlow3 == 0);
		int 	iSlow30 = (iSlow2 & iSlow29);
		int 	iSlow31 = ((13 * (iSlow24 & iSlow25)) + ((11 * (iSlow24 & iSlow16)) + ((10 * (iSlow26 & iSlow25)) + ((9 * (iSlow26 & iSlow16)) + ((8 * (((iSlow21 & iSlow12) & iSlow14) & iSlow16)) + ((7 * (((iSlow27 & iSlow22) & iSlow14) & iSlow16)) + ((6 * (((iSlow27 & iSlow12) & iSlow14) & iSlow16)) + (((((((((iSlow28 & iSlow4) & iSlow7) & iSlow10) & iSlow12) & iSlow14) & iSlow16) + (2 * (((((iSlow30 & iSlow7) & iSlow10) & iSlow12) & iSlow14) & iSlow16))) + (3 * (((((iSlow30 & iSlow18) & iSlow10) & iSlow12) & iSlow14) & iSlow16))) + (5 * ((((iSlow8 & iSlow20) & iSlow12) & iSlow14) & iSlow16))))))))));
		int 	iSlow32 = ((((((iSlow28 & iSlow29) & iSlow7) & iSlow10) & iSlow12) & iSlow14) & iSlow25);
		int 	iSlow33 = int(min((float)1, float(fslider8)));
		int 	iSlow34 = int(min((float)1, float(fslider9)));
		//zone2b
		//zone3
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			iRec6[0] = 0;
			fRec13[0] = (0.5f * (fRec13[1] + fRec11[1]));
			float 	fRec10 = (fRec13[0] + iRec6[1]);
			fTempPerm0 = fabsf((float)input0[i]);
			fRec18[0] = max(fTempPerm0, ((fConst1 * fRec18[1]) + (fConst2 * fTempPerm0)));
			fRec17[0] = ((fConst1 * fRec17[1]) + (fConst2 * fRec18[0]));
			fTempPerm1 = (0.69999999999999996f * fRec17[0]);
			fRec14[0] = (fRec0[1] + fTempPerm1);
			fTempPerm2 = (0 - fRec14[1]);
			fRec19[0] = (fSlow0 + (0.999f * fRec19[1]));
			fRec15[IOTA&2047] = (fTempPerm1 + (fTempPerm2 * max((float)-1, min((float)1, ((fTempPerm2 * ((0.26000000000000001f * fRec19[0]) + -0.44f)) + 0.69999999999999996f)))));
			int 	iRec16 = 0;
			iVec0[0] = iSlow33;
			iRec21[0] = (((iSlow33 - iVec0[1]) > 0) + iRec21[1]);
			iVec1[0] = iSlow34;
			iRec22[0] = (((iSlow34 - iVec1[1]) > 0) + iRec22[1]);
			fRec20[0] = ((0.999f * fRec20[1]) + (0.00077272727272727334f / powf(2.0f,(0.083333333333333329f * (fSlow17 - (iSlow31 + (12 * (iSlow32 - (iRec21[0] - iRec22[0])))))))));
			fTempPerm3 = (fConst4 * ((0.5f * fRec20[0]) + -0.050000000000000003f));
			fTempPerm4 = (fTempPerm3 + -1.499995f);
			iTempPerm5 = int(fTempPerm4);
			iTempPerm6 = int((int(min(fConst3, (float)max(0, (int)iTempPerm5))) + 1));
			fTempPerm7 = floorf(fTempPerm4);
			fTempPerm8 = (fTempPerm3 + (-1 - fTempPerm7));
			fTempPerm9 = (0 - fTempPerm8);
			fTempPerm10 = (fTempPerm3 + (-2 - fTempPerm7));
			fTempPerm11 = (0 - (0.5f * fTempPerm10));
			fTempPerm12 = (fTempPerm3 + (-3 - fTempPerm7));
			fTempPerm13 = (0 - (0.33333333333333331f * fTempPerm12));
			fTempPerm14 = (fTempPerm3 + (-4 - fTempPerm7));
			fTempPerm15 = (0 - (0.25f * fTempPerm14));
			fTempPerm16 = (fTempPerm3 - fTempPerm7);
			iTempPerm17 = int((int(min(fConst3, (float)max(0, (int)(iTempPerm5 + 2)))) + 1));
			fTempPerm18 = (0 - fTempPerm12);
			fTempPerm19 = (0 - (0.5f * fTempPerm14));
			iTempPerm20 = int((int(min(fConst3, (float)max(0, (int)(iTempPerm5 + 1)))) + 1));
			fTempPerm21 = (0 - fTempPerm10);
			fTempPerm22 = (0 - (0.5f * fTempPerm12));
			fTempPerm23 = (0 - (0.33333333333333331f * fTempPerm14));
			fTempPerm24 = (fTempPerm8 * fTempPerm10);
			iTempPerm25 = int((int(min(fConst3, (float)max(0, (int)(iTempPerm5 + 3)))) + 1));
			fTempPerm26 = (0 - fTempPerm14);
			fTempPerm27 = (fTempPerm24 * fTempPerm12);
			iTempPerm28 = int((int(min(fConst3, (float)max(0, (int)(iTempPerm5 + 4)))) + 1));
			fVec2[0] = (((((fRec15[(IOTA-iTempPerm6)&2047] * fTempPerm9) * fTempPerm11) * fTempPerm13) * fTempPerm15) + (fTempPerm16 * ((((0.5f * (((fTempPerm8 * fRec15[(IOTA-iTempPerm17)&2047]) * fTempPerm18) * fTempPerm19)) + (((fRec15[(IOTA-iTempPerm20)&2047] * fTempPerm21) * fTempPerm22) * fTempPerm23)) + (0.16666666666666666f * ((fTempPerm24 * fRec15[(IOTA-iTempPerm25)&2047]) * fTempPerm26))) + (0.041666666666666664f * (fTempPerm27 * fRec15[(IOTA-iTempPerm28)&2047])))));
			fRec11[0] = fVec2[1];
			int 	iRec12 = iRec16;
			float 	fRec7 = fRec10;
			float 	fRec8 = fRec11[0];
			float 	fRec9 = (fRec11[0] + iRec12);
			fRec2[IOTA&2047] = fRec7;
			float 	fRec3 = (((((fTempPerm9 * fTempPerm11) * fTempPerm13) * fTempPerm15) * fRec2[(IOTA-iTempPerm6)&2047]) + (fTempPerm16 * (((0.16666666666666666f * ((fTempPerm24 * fTempPerm26) * fRec2[(IOTA-iTempPerm25)&2047])) + ((((fTempPerm21 * fTempPerm22) * fTempPerm23) * fRec2[(IOTA-iTempPerm20)&2047]) + (0.5f * (((fTempPerm8 * fTempPerm18) * fTempPerm19) * fRec2[(IOTA-iTempPerm17)&2047])))) + (0.041666666666666664f * (fTempPerm27 * fRec2[(IOTA-iTempPerm28)&2047])))));
			float 	fRec4 = fRec8;
			float 	fRec5 = fRec9;
			fRec0[0] = fRec3;
			float 	fRec1 = fRec5;
			output0[i] = (FAUSTFLOAT)fRec1;
			output1[i] = (FAUSTFLOAT)fRec1;
			// post processing
			fRec0[1] = fRec0[0];
			fRec11[1] = fRec11[0];
			fVec2[1] = fVec2[0];
			fRec20[1] = fRec20[0];
			iRec22[1] = iRec22[0];
			iVec1[1] = iVec1[0];
			iRec21[1] = iRec21[0];
			iVec0[1] = iVec0[0];
			IOTA = IOTA+1;
			fRec19[1] = fRec19[0];
			fRec14[1] = fRec14[0];
			fRec17[1] = fRec17[0];
			fRec18[1] = fRec18[0];
			fRec13[1] = fRec13[0];
			iRec6[1] = iRec6[0];
		}
	}
};


