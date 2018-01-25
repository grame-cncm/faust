//----------------------------------------------------------
// author: "Grame"
// copyright: "(c)GRAME 2014"
// license: "BSD"
// name: "tester2"
// version: "1.0"
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
	class SIG0 {
	  private:
		int fSamplingFreq;
		int 	iRec4[2];
		float 	fTempPerm0;
	  public:
		int getNumInputs() { return 0; }
		int getNumOutputs() { return 1; }
		void init(int samplingFreq) {
			fSamplingFreq = samplingFreq;
			fTempPerm0 = 0;
			for (int i=0; i<2; i++) iRec4[i] = 0;
		}
		void fill (int count, float output[]) {
			for (int i=0; i<count; i++) {
				iRec4[0] = (iRec4[1] + 1);
				fTempPerm0 = sinf((9.5873799242852573e-05f * float((iRec4[0] + -1))));
				output[i] = fTempPerm0;
				// post processing
				iRec4[1] = iRec4[0];
			}
		}
	};


	FAUSTFLOAT 	fslider0;
	float 	fRec0[2];
	FAUSTFLOAT 	fslider1;
	float 	fRec1[2];
	FAUSTFLOAT 	fslider2;
	int 	iRec2[3];
	float 	fRec3[3];
	static float 	ftbl0[65537];
	float 	fConst0;
	FAUSTFLOAT 	fslider3;
	float 	fRec5[2];
	float 	fTempPerm1;
	int 	iTempPerm2;
	float 	fTempPerm3;
	float 	fTempPerm4;
	float 	fRec6[2];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("author", "Grame");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("copyright", "(c)GRAME 2014");
		m->declare("license", "BSD");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "tester2");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() { return 0; }
	virtual int getNumOutputs() { return 2; }
	static void classInit(int samplingFreq) {
		SIG0 sig0;
		sig0.init(samplingFreq);
		sig0.fill(65537,ftbl0);
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = (1.0f / float(min(192000.0f, max(1.0f, (float)fSamplingFreq))));
		fTempPerm1 = 0;
		iTempPerm2 = 0;
		fTempPerm3 = 0;
		fTempPerm4 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = -96.0f;
		fslider1 = 0.0f;
		fslider2 = 0.0f;
		fslider3 = 440.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<3; i++) iRec2[i] = 0;
		for (int i=0; i<3; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
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
		ui_interface->openVerticalBox("Stereo Audio Tester");
		ui_interface->declare(&fslider3, "1", "");
		ui_interface->declare(&fslider3, "scale", "log");
		ui_interface->declare(&fslider3, "unit", "Hz");
		ui_interface->addHorizontalSlider("freq", &fslider3, 440.0f, 40.0f, 20000.0f, 1.0f);
		ui_interface->declare(&fslider0, "2", "");
		ui_interface->declare(&fslider0, "unit", "dB");
		ui_interface->addHorizontalSlider("volume", &fslider0, -96.0f, -96.0f, 0.0f, 1.0f);
		ui_interface->declare(&fslider2, "3", "");
		ui_interface->declare(&fslider2, "style", "menu{'white noise':0;'pink noise':1;'sine':2}");
		ui_interface->addHorizontalSlider("signal", &fslider2, 0.0f, 0.0f, 2.0f, 1.0f);
		ui_interface->declare(&fslider1, "4", "");
		ui_interface->declare(&fslider1, "style", "radio{'none':0;'left':1;'right':2;'both':3}");
		ui_interface->addHorizontalSlider("channel", &fslider1, 0.0f, 0.0f, 3.0f, 1.0f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = (0.0010000000000000009f * powf(10,(0.050000000000000003f * float(fslider0))));
		int 	iSlow1 = int(float(fslider1));
		int 	iSlow2 = ((iSlow1 & 1) != 0);
		int 	iSlow3 = int(float(fslider2));
		int 	iSlow4 = int((iSlow3 == 0));
		int 	iSlow5 = int((iSlow3 == 1));
		float 	fSlow6 = (fConst0 * float(fslider3));
		int 	iSlow7 = ((iSlow1 & 2) != 0);
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fRec0[0] = (fSlow0 + (0.999f * fRec0[1]));
			fRec1[0] = ((int((fRec1[1] < iSlow2)))?min((fRec1[1] + 0.00022675736961451248f), (float)iSlow2):max((fRec1[1] + -0.00022675736961451248f), (float)iSlow2));
			iRec2[0] = ((1103515245 * iRec2[1]) + 12345);
			fRec3[0] = (((6.9067828423840845e-12f * iRec2[2]) + ((1.80116083982126f * fRec3[1]) + (2.308528039463576e-11f * iRec2[0]))) - ((0.80257737639225002f * fRec3[2]) + (2.9362651228132963e-11f * iRec2[1])));
			fRec5[0] = (fSlow6 + (fRec5[1] - floorf((fSlow6 + fRec5[1]))));
			fTempPerm1 = (65536.0f * fRec5[0]);
			iTempPerm2 = int(fTempPerm1);
			fTempPerm3 = ftbl0[iTempPerm2];
			fTempPerm4 = ((iSlow4)?(4.6566128752457969e-10f * iRec2[0]):((iSlow5)?fRec3[0]:(fTempPerm3 + ((fTempPerm1 - floorf(fTempPerm1)) * (ftbl0[(iTempPerm2 + 1)] - fTempPerm3)))));
			output0[i] = (FAUSTFLOAT)((fRec0[0] * fRec1[0]) * fTempPerm4);
			fRec6[0] = ((int((fRec6[1] < iSlow7)))?min((fRec6[1] + 0.00022675736961451248f), (float)iSlow7):max((fRec6[1] + -0.00022675736961451248f), (float)iSlow7));
			output1[i] = (FAUSTFLOAT)((fRec0[0] * fRec6[0]) * fTempPerm4);
			// post processing
			fRec6[1] = fRec6[0];
			fRec5[1] = fRec5[0];
			fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
			iRec2[2] = iRec2[1]; iRec2[1] = iRec2[0];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
		}
	}
};


float 	mydsp::ftbl0[65537];
