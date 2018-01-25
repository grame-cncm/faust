//----------------------------------------------------------
// author: "Grame"
// copyright: "(c)GRAME 2006"
// license: "BSD"
// name: "tester"
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
		int 	iRec1[2];
		float 	fTempPerm0;
	  public:
		int getNumInputs() { return 0; }
		int getNumOutputs() { return 1; }
		void init(int samplingFreq) {
			fSamplingFreq = samplingFreq;
			fTempPerm0 = 0;
			for (int i=0; i<2; i++) iRec1[i] = 0;
		}
		void fill (int count, float output[]) {
			for (int i=0; i<count; i++) {
				iRec1[0] = (iRec1[1] + 1);
				fTempPerm0 = sinf((9.5873799242852573e-05f * float((iRec1[0] + -1))));
				output[i] = fTempPerm0;
				// post processing
				iRec1[1] = iRec1[0];
			}
		}
	};


	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fslider1;
	float 	fRec0[2];
	FAUSTFLOAT 	fcheckbox0;
	static float 	ftbl0[65537];
	float 	fConst0;
	FAUSTFLOAT 	fslider2;
	float 	fRec2[2];
	float 	fTempPerm1;
	int 	iTempPerm2;
	float 	fTempPerm3;
	FAUSTFLOAT 	fcheckbox1;
	int 	iRec3[3];
	FAUSTFLOAT 	fcheckbox2;
	float 	fRec4[3];
	float 	fTempPerm4;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("author", "Grame");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("copyright", "(c)GRAME 2006");
		m->declare("license", "BSD");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "tester");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() { return 0; }
	virtual int getNumOutputs() { return 8; }
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
		fslider0 = 0.0f;
		fslider1 = -96.0f;
		fcheckbox0 = 0.0;
		fslider2 = 1000.0f;
		fcheckbox1 = 0.0;
		fcheckbox2 = 0.0;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<3; i++) iRec3[i] = 0;
		for (int i=0; i<3; i++) fRec4[i] = 0;
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
		ui_interface->openVerticalBox("Audio Tester");
		ui_interface->declare(&fslider2, "1", "");
		ui_interface->declare(&fslider2, "unit", "Hz");
		ui_interface->addHorizontalSlider("freq", &fslider2, 1000.0f, 10.0f, 20000.0f, 1.0f);
		ui_interface->declare(&fslider1, "2", "");
		ui_interface->declare(&fslider1, "unit", "dB");
		ui_interface->addHorizontalSlider("volume", &fslider1, -96.0f, -96.0f, 0.0f, 1.0f);
		ui_interface->declare(&fslider0, "3", "");
		ui_interface->addHorizontalSlider("destination", &fslider0, 0.0f, 0.0f, 8.0f, 1.0f);
		ui_interface->addCheckButton("pink noise", &fcheckbox2);
		ui_interface->addCheckButton("sine wave", &fcheckbox0);
		ui_interface->addCheckButton("white noise", &fcheckbox1);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = float(fslider0);
		int 	iSlow1 = (fSlow0 == 0);
		float 	fSlow2 = (0.0010000000000000009f * powf(10,(0.050000000000000003f * float(fslider1))));
		float 	fSlow3 = float(fcheckbox0);
		float 	fSlow4 = (fConst0 * float(fslider2));
		float 	fSlow5 = (4.6566128752457969e-10f * float(fcheckbox1));
		float 	fSlow6 = (10.0f * float(fcheckbox2));
		int 	iSlow7 = (fSlow0 == 1);
		int 	iSlow8 = (fSlow0 == 2);
		int 	iSlow9 = (fSlow0 == 3);
		int 	iSlow10 = (fSlow0 == 4);
		int 	iSlow11 = (fSlow0 == 5);
		int 	iSlow12 = (fSlow0 == 6);
		int 	iSlow13 = (fSlow0 == 7);
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		FAUSTFLOAT* output2 = output[2];
		FAUSTFLOAT* output3 = output[3];
		FAUSTFLOAT* output4 = output[4];
		FAUSTFLOAT* output5 = output[5];
		FAUSTFLOAT* output6 = output[6];
		FAUSTFLOAT* output7 = output[7];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fRec0[0] = (fSlow2 + (0.999f * fRec0[1]));
			fRec2[0] = (fSlow4 + (fRec2[1] - floorf((fSlow4 + fRec2[1]))));
			fTempPerm1 = (65536.0f * fRec2[0]);
			iTempPerm2 = int(fTempPerm1);
			fTempPerm3 = ftbl0[iTempPerm2];
			iRec3[0] = ((1103515245 * iRec3[1]) + 12345);
			fRec4[0] = (((6.9067828423840845e-12f * iRec3[2]) + ((1.80116083982126f * fRec4[1]) + (2.308528039463576e-11f * iRec3[0]))) - ((0.80257737639225002f * fRec4[2]) + (2.9362651228132963e-11f * iRec3[1])));
			fTempPerm4 = (fRec0[0] * (((fSlow3 * (fTempPerm3 + ((fTempPerm1 - floorf(fTempPerm1)) * (ftbl0[(iTempPerm2 + 1)] - fTempPerm3)))) + (fSlow5 * iRec3[0])) + (fSlow6 * fRec4[0])));
			output0[i] = (FAUSTFLOAT)(iSlow1 * fTempPerm4);
			output1[i] = (FAUSTFLOAT)(iSlow7 * fTempPerm4);
			output2[i] = (FAUSTFLOAT)(iSlow8 * fTempPerm4);
			output3[i] = (FAUSTFLOAT)(iSlow9 * fTempPerm4);
			output4[i] = (FAUSTFLOAT)(iSlow10 * fTempPerm4);
			output5[i] = (FAUSTFLOAT)(iSlow11 * fTempPerm4);
			output6[i] = (FAUSTFLOAT)(iSlow12 * fTempPerm4);
			output7[i] = (FAUSTFLOAT)(iSlow13 * fTempPerm4);
			// post processing
			fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
			iRec3[2] = iRec3[1]; iRec3[1] = iRec3[0];
			fRec2[1] = fRec2[0];
			fRec0[1] = fRec0[0];
		}
	}
};


float 	mydsp::ftbl0[65537];
