/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2006"
license: "BSD"
name: "tester"
version: "1.0"
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
	
	int iRec1[2];
	
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
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			iRec1[l1] = 0;
			
		}
		
	}
	
	void fillmydspSIG0(int count, float* output) {
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec1[0] = (iRec1[1] + 1);
			output[i] = sinf((9.58738019e-05f * float((iRec1[0] + -1))));
			iRec1[1] = iRec1[0];
			
		}
		
	}
};

mydspSIG0* newmydspSIG0() { return (mydspSIG0*)new mydspSIG0(); }
void deletemydspSIG0(mydspSIG0* dsp) { delete dsp; }

static float ftbl0mydspSIG0[65537];

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
	FAUSTFLOAT fHslider1;
	float fRec0[2];
	FAUSTFLOAT fCheckbox0;
	int fSamplingFreq;
	float fConst0;
	FAUSTFLOAT fHslider2;
	float fRec2[2];
	FAUSTFLOAT fCheckbox1;
	int iRec3[3];
	FAUSTFLOAT fCheckbox2;
	float fRec4[3];
	
 public:
	
	void metadata(Meta* m) { 
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

	virtual int getNumInputs() {
		return 0;
		
	}
	virtual int getNumOutputs() {
		return 8;
		
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
			case 2: {
				rate = 1;
				break;
			}
			case 3: {
				rate = 1;
				break;
			}
			case 4: {
				rate = 1;
				break;
			}
			case 5: {
				rate = 1;
				break;
			}
			case 6: {
				rate = 1;
				break;
			}
			case 7: {
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
		sig0->fillmydspSIG0(65537, ftbl0mydspSIG0);
		deletemydspSIG0(sig0);
		
	}
	
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = (1.0f / min(192000.0f, max(1.0f, float(fSamplingFreq))));
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.0f);
		fHslider1 = FAUSTFLOAT(-96.0f);
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(1000.0f);
		fCheckbox1 = FAUSTFLOAT(0.0f);
		fCheckbox2 = FAUSTFLOAT(0.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec0[l0] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec2[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 3); l3 = (l3 + 1)) {
			iRec3[l3] = 0;
			
		}
		for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) {
			fRec4[l4] = 0.0f;
			
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
		ui_interface->openVerticalBox("Audio Tester");
		ui_interface->declare(&fHslider2, "1", "");
		ui_interface->declare(&fHslider2, "unit", "Hz");
		ui_interface->addHorizontalSlider("freq", &fHslider2, 1000.0f, 10.0f, 20000.0f, 1.0f);
		ui_interface->declare(&fHslider1, "2", "");
		ui_interface->declare(&fHslider1, "unit", "dB");
		ui_interface->addHorizontalSlider("volume", &fHslider1, -96.0f, -96.0f, 0.0f, 1.0f);
		ui_interface->declare(&fHslider0, "3", "");
		ui_interface->addHorizontalSlider("destination", &fHslider0, 0.0f, 0.0f, 8.0f, 1.0f);
		ui_interface->addCheckButton("pink noise", &fCheckbox2);
		ui_interface->addCheckButton("sine wave", &fCheckbox0);
		ui_interface->addCheckButton("white noise", &fCheckbox1);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		FAUSTFLOAT* output2 = outputs[2];
		FAUSTFLOAT* output3 = outputs[3];
		FAUSTFLOAT* output4 = outputs[4];
		FAUSTFLOAT* output5 = outputs[5];
		FAUSTFLOAT* output6 = outputs[6];
		FAUSTFLOAT* output7 = outputs[7];
		float fSlow0 = float(fHslider0);
		int iSlow1 = (fSlow0 == 0.0f);
		float fSlow2 = (0.00100000005f * powf(10.0f, (0.0500000007f * float(fHslider1))));
		float fSlow3 = float(fCheckbox0);
		float fSlow4 = (fConst0 * float(fHslider2));
		float fSlow5 = (4.65661287e-10f * float(fCheckbox1));
		float fSlow6 = (10.0f * float(fCheckbox2));
		int iSlow7 = (fSlow0 == 1.0f);
		int iSlow8 = (fSlow0 == 2.0f);
		int iSlow9 = (fSlow0 == 3.0f);
		int iSlow10 = (fSlow0 == 4.0f);
		int iSlow11 = (fSlow0 == 5.0f);
		int iSlow12 = (fSlow0 == 6.0f);
		int iSlow13 = (fSlow0 == 7.0f);
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec0[0] = (fSlow2 + (0.999000013f * fRec0[1]));
			fRec2[0] = (fSlow4 + (fRec2[1] - floorf((fSlow4 + fRec2[1]))));
			float fTemp0 = (65536.0f * fRec2[0]);
			int iTemp1 = int(fTemp0);
			iRec3[0] = ((1103515245 * iRec3[1]) + 12345);
			fRec4[0] = (((6.90678287e-12f * float(iRec3[2])) + ((1.80116081f * fRec4[1]) + (2.30852802e-11f * float(iRec3[0])))) - ((0.802577376f * fRec4[2]) + (2.93626512e-11f * float(iRec3[1]))));
			float fTemp2 = (fRec0[0] * (((fSlow3 * (ftbl0mydspSIG0[iTemp1] + ((fTemp0 - floorf(fTemp0)) * (ftbl0mydspSIG0[(iTemp1 + 1)] - ftbl0mydspSIG0[iTemp1])))) + (fSlow5 * float(iRec3[0]))) + (fSlow6 * fRec4[0])));
			output0[i] = FAUSTFLOAT((float(iSlow1) * fTemp2));
			output1[i] = FAUSTFLOAT((float(iSlow7) * fTemp2));
			output2[i] = FAUSTFLOAT((float(iSlow8) * fTemp2));
			output3[i] = FAUSTFLOAT((float(iSlow9) * fTemp2));
			output4[i] = FAUSTFLOAT((float(iSlow10) * fTemp2));
			output5[i] = FAUSTFLOAT((float(iSlow11) * fTemp2));
			output6[i] = FAUSTFLOAT((float(iSlow12) * fTemp2));
			output7[i] = FAUSTFLOAT((float(iSlow13) * fTemp2));
			fRec0[1] = fRec0[0];
			fRec2[1] = fRec2[0];
			iRec3[2] = iRec3[1];
			iRec3[1] = iRec3[0];
			fRec4[2] = fRec4[1];
			fRec4[1] = fRec4[0];
			
		}
		
	}

	
};

#endif
