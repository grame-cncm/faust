/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2006"
license: "BSD"
name: "dbmeter"
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
	float fRec0[2];
	FAUSTFLOAT fVbargraph0;
	int iConst1;
	float fRec1[2];
	FAUSTFLOAT fVbargraph1;
	int iConst2;
	float fRec2[2];
	FAUSTFLOAT fVbargraph2;
	int iConst3;
	float fRec3[2];
	FAUSTFLOAT fVbargraph3;
	int iConst4;
	float fRec4[2];
	FAUSTFLOAT fVbargraph4;
	int iConst5;
	float fRec5[2];
	FAUSTFLOAT fVbargraph5;
	int iConst6;
	float fRec6[2];
	FAUSTFLOAT fVbargraph6;
	int iConst7;
	float fRec7[2];
	FAUSTFLOAT fVbargraph7;
	int iConst8;
	
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
		m->declare("name", "dbmeter");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() {
		return 8;
		
	}
	virtual int getNumOutputs() {
		return 8;
		
	}
	virtual int getInputRate(int channel) {
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
		
	}
	
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = (80.0f / min(192000.0f, max(1.0f, float(fSamplingFreq))));
		iConst1 = 0;
		iConst2 = 0;
		iConst3 = 0;
		iConst4 = 0;
		iConst5 = 0;
		iConst6 = 0;
		iConst7 = 0;
		iConst8 = 0;
		
	}
	
	virtual void instanceResetUserInterface() {
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec0[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec1[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec2[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec3[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec4[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec5[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec6[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec7[l7] = 0.0f;
			
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
		ui_interface->openHorizontalBox("8 channels dB meter");
		ui_interface->openVerticalBox("0");
		ui_interface->declare(&fVbargraph0, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fce0e65cbb0", &fVbargraph0, -70.0f, 10.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("1");
		ui_interface->declare(&fVbargraph1, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fce0e661290", &fVbargraph1, -70.0f, 10.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("2");
		ui_interface->declare(&fVbargraph2, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fce0e665970", &fVbargraph2, -70.0f, 10.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("3");
		ui_interface->declare(&fVbargraph3, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fce0e66a100", &fVbargraph3, -70.0f, 10.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("4");
		ui_interface->declare(&fVbargraph4, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fce0e66e940", &fVbargraph4, -70.0f, 10.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("5");
		ui_interface->declare(&fVbargraph5, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fce0e673230", &fVbargraph5, -70.0f, 10.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("6");
		ui_interface->declare(&fVbargraph6, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fce0e677bd0", &fVbargraph6, -70.0f, 10.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("7");
		ui_interface->declare(&fVbargraph7, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fce0e67c620", &fVbargraph7, -70.0f, 10.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* input2 = inputs[2];
		FAUSTFLOAT* input3 = inputs[3];
		FAUSTFLOAT* input4 = inputs[4];
		FAUSTFLOAT* input5 = inputs[5];
		FAUSTFLOAT* input6 = inputs[6];
		FAUSTFLOAT* input7 = inputs[7];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		FAUSTFLOAT* output2 = outputs[2];
		FAUSTFLOAT* output3 = outputs[3];
		FAUSTFLOAT* output4 = outputs[4];
		FAUSTFLOAT* output5 = outputs[5];
		FAUSTFLOAT* output6 = outputs[6];
		FAUSTFLOAT* output7 = outputs[7];
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input0[i]);
			fRec0[0] = max((fRec0[1] - fConst0), min(10.0f, (20.0f * log10f(max(0.000316227757f, fabsf(fTemp0))))));
			fVbargraph0 = FAUSTFLOAT(fRec0[0]);
			output0[i] = FAUSTFLOAT(iConst1);
			float fTemp1 = float(input1[i]);
			fRec1[0] = max((fRec1[1] - fConst0), min(10.0f, (20.0f * log10f(max(0.000316227757f, fabsf(fTemp1))))));
			fVbargraph1 = FAUSTFLOAT(fRec1[0]);
			output1[i] = FAUSTFLOAT(iConst2);
			float fTemp2 = float(input2[i]);
			fRec2[0] = max((fRec2[1] - fConst0), min(10.0f, (20.0f * log10f(max(0.000316227757f, fabsf(fTemp2))))));
			fVbargraph2 = FAUSTFLOAT(fRec2[0]);
			output2[i] = FAUSTFLOAT(iConst3);
			float fTemp3 = float(input3[i]);
			fRec3[0] = max((fRec3[1] - fConst0), min(10.0f, (20.0f * log10f(max(0.000316227757f, fabsf(fTemp3))))));
			fVbargraph3 = FAUSTFLOAT(fRec3[0]);
			output3[i] = FAUSTFLOAT(iConst4);
			float fTemp4 = float(input4[i]);
			fRec4[0] = max((fRec4[1] - fConst0), min(10.0f, (20.0f * log10f(max(0.000316227757f, fabsf(fTemp4))))));
			fVbargraph4 = FAUSTFLOAT(fRec4[0]);
			output4[i] = FAUSTFLOAT(iConst5);
			float fTemp5 = float(input5[i]);
			fRec5[0] = max((fRec5[1] - fConst0), min(10.0f, (20.0f * log10f(max(0.000316227757f, fabsf(fTemp5))))));
			fVbargraph5 = FAUSTFLOAT(fRec5[0]);
			output5[i] = FAUSTFLOAT(iConst6);
			float fTemp6 = float(input6[i]);
			fRec6[0] = max((fRec6[1] - fConst0), min(10.0f, (20.0f * log10f(max(0.000316227757f, fabsf(fTemp6))))));
			fVbargraph6 = FAUSTFLOAT(fRec6[0]);
			output6[i] = FAUSTFLOAT(iConst7);
			float fTemp7 = float(input7[i]);
			fRec7[0] = max((fRec7[1] - fConst0), min(10.0f, (20.0f * log10f(max(0.000316227757f, fabsf(fTemp7))))));
			fVbargraph7 = FAUSTFLOAT(fRec7[0]);
			output7[i] = FAUSTFLOAT(iConst8);
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec7[1] = fRec7[0];
			
		}
		
	}

	
};

#endif
