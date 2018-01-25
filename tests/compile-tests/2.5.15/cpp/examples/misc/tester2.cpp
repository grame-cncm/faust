/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2014"
license: "BSD"
name: "tester2"
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
	
	int iRec2[2];
	
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
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			iRec2[l2] = 0;
			
		}
		
	}
	
	void fillmydspSIG0(int count, float* output) {
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec2[0] = (iRec2[1] + 1);
			output[i] = sinf((9.58738019e-05f * float((iRec2[0] + -1))));
			iRec2[1] = iRec2[0];
			
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
	float fRec0[2];
	FAUSTFLOAT fHslider1;
	float fRec1[2];
	FAUSTFLOAT fHslider2;
	int fSamplingFreq;
	float fConst0;
	FAUSTFLOAT fHslider3;
	float fRec3[2];
	int iRec5[3];
	float fRec4[3];
	float fRec6[2];
	
 public:
	
	void metadata(Meta* m) { 
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
		sig0->fillmydspSIG0(65537, ftbl0mydspSIG0);
		deletemydspSIG0(sig0);
		
	}
	
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = (1.0f / min(192000.0f, max(1.0f, float(fSamplingFreq))));
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(-96.0f);
		fHslider1 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(0.0f);
		fHslider3 = FAUSTFLOAT(440.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec0[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec1[l1] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec3[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) {
			iRec5[l4] = 0;
			
		}
		for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) {
			fRec4[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec6[l6] = 0.0f;
			
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
		ui_interface->openVerticalBox("Stereo Audio Tester");
		ui_interface->declare(&fHslider3, "1", "");
		ui_interface->declare(&fHslider3, "scale", "log");
		ui_interface->declare(&fHslider3, "unit", "Hz");
		ui_interface->addHorizontalSlider("freq", &fHslider3, 440.0f, 40.0f, 20000.0f, 1.0f);
		ui_interface->declare(&fHslider0, "2", "");
		ui_interface->declare(&fHslider0, "unit", "dB");
		ui_interface->addHorizontalSlider("volume", &fHslider0, -96.0f, -96.0f, 0.0f, 1.0f);
		ui_interface->declare(&fHslider2, "3", "");
		ui_interface->declare(&fHslider2, "style", "menu{'white noise':0;'pink noise':1;'sine':2}");
		ui_interface->addHorizontalSlider("signal", &fHslider2, 0.0f, 0.0f, 2.0f, 1.0f);
		ui_interface->declare(&fHslider1, "4", "");
		ui_interface->declare(&fHslider1, "style", "radio{'none':0;'left':1;'right':2;'both':3}");
		ui_interface->addHorizontalSlider("channel", &fHslider1, 0.0f, 0.0f, 3.0f, 1.0f);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = (0.00100000005f * powf(10.0f, (0.0500000007f * float(fHslider0))));
		int iSlow1 = int(float(fHslider1));
		int iSlow2 = ((iSlow1 & 1) != 0);
		int iSlow3 = int(float(fHslider2));
		int iSlow4 = (iSlow3 == 0);
		int iSlow5 = (iSlow3 == 1);
		float fSlow6 = (fConst0 * float(fHslider3));
		int iSlow7 = ((iSlow1 & 2) != 0);
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec0[0] = (fSlow0 + (0.999000013f * fRec0[1]));
			fRec1[0] = ((fRec1[1] < float(iSlow2))?min((fRec1[1] + 0.000226757373f), float(iSlow2)):max((fRec1[1] + -0.000226757373f), float(iSlow2)));
			fRec3[0] = (fSlow6 + (fRec3[1] - floorf((fSlow6 + fRec3[1]))));
			float fTemp0 = (65536.0f * fRec3[0]);
			int iTemp1 = int(fTemp0);
			iRec5[0] = ((1103515245 * iRec5[1]) + 12345);
			fRec4[0] = (((6.90678287e-12f * float(iRec5[2])) + ((1.80116081f * fRec4[1]) + (2.30852802e-11f * float(iRec5[0])))) - ((0.802577376f * fRec4[2]) + (2.93626512e-11f * float(iRec5[1]))));
			float fTemp2 = (iSlow4?(4.65661287e-10f * float(iRec5[0])):(iSlow5?fRec4[0]:(ftbl0mydspSIG0[iTemp1] + ((fTemp0 - floorf(fTemp0)) * (ftbl0mydspSIG0[(iTemp1 + 1)] - ftbl0mydspSIG0[iTemp1])))));
			output0[i] = FAUSTFLOAT(((fRec0[0] * fRec1[0]) * fTemp2));
			fRec6[0] = ((fRec6[1] < float(iSlow7))?min((fRec6[1] + 0.000226757373f), float(iSlow7)):max((fRec6[1] + -0.000226757373f), float(iSlow7)));
			output1[i] = FAUSTFLOAT(((fRec0[0] * fRec6[0]) * fTemp2));
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			fRec3[1] = fRec3[0];
			iRec5[2] = iRec5[1];
			iRec5[1] = iRec5[0];
			fRec4[2] = fRec4[1];
			fRec4[1] = fRec4[0];
			fRec6[1] = fRec6[0];
			
		}
		
	}

	
};

#endif
