/* ------------------------------------------------------------
author: "O. Guillerminet"
copyright: "(c) O. Guillerminet 2012"
license: "BSD"
name: "UITester"
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


#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif
#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class mydsp : public dsp {
	
 private:
	
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT fEntry0;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT fVslider5;
	FAUSTFLOAT fVslider6;
	FAUSTFLOAT fButton0;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fVslider7;
	FAUSTFLOAT fVslider8;
	FAUSTFLOAT fVslider9;
	FAUSTFLOAT fEntry1;
	FAUSTFLOAT fVbargraph0;
	FAUSTFLOAT fVslider10;
	FAUSTFLOAT fVslider11;
	FAUSTFLOAT fVslider12;
	FAUSTFLOAT fEntry2;
	FAUSTFLOAT fVbargraph1;
	FAUSTFLOAT fVslider13;
	FAUSTFLOAT fVslider14;
	FAUSTFLOAT fVslider15;
	FAUSTFLOAT fEntry3;
	FAUSTFLOAT fVbargraph2;
	FAUSTFLOAT fHbargraph0;
	FAUSTFLOAT fVslider16;
	FAUSTFLOAT fButton1;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fEntry4;
	FAUSTFLOAT fVbargraph3;
	FAUSTFLOAT fHbargraph1;
	int fSamplingFreq;
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("author", "O. Guillerminet");
		m->declare("copyright", "(c) O. Guillerminet 2012");
		m->declare("license", "BSD");
		m->declare("name", "UITester");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() {
		return 6;
		
	}
	virtual int getNumOutputs() {
		return 34;
		
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
			case 8: {
				rate = 1;
				break;
			}
			case 9: {
				rate = 1;
				break;
			}
			case 10: {
				rate = 1;
				break;
			}
			case 11: {
				rate = 1;
				break;
			}
			case 12: {
				rate = 1;
				break;
			}
			case 13: {
				rate = 1;
				break;
			}
			case 14: {
				rate = 1;
				break;
			}
			case 15: {
				rate = 1;
				break;
			}
			case 16: {
				rate = 1;
				break;
			}
			case 17: {
				rate = 1;
				break;
			}
			case 18: {
				rate = 1;
				break;
			}
			case 19: {
				rate = 1;
				break;
			}
			case 20: {
				rate = 1;
				break;
			}
			case 21: {
				rate = 1;
				break;
			}
			case 22: {
				rate = 1;
				break;
			}
			case 23: {
				rate = 1;
				break;
			}
			case 24: {
				rate = 1;
				break;
			}
			case 25: {
				rate = 1;
				break;
			}
			case 26: {
				rate = 1;
				break;
			}
			case 27: {
				rate = 1;
				break;
			}
			case 28: {
				rate = 1;
				break;
			}
			case 29: {
				rate = 1;
				break;
			}
			case 30: {
				rate = 1;
				break;
			}
			case 31: {
				rate = 1;
				break;
			}
			case 32: {
				rate = 1;
				break;
			}
			case 33: {
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
		
	}
	
	virtual void instanceResetUserInterface() {
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fCheckbox1 = FAUSTFLOAT(0.0f);
		fEntry0 = FAUSTFLOAT(60.0f);
		fVslider0 = FAUSTFLOAT(60.0f);
		fVslider1 = FAUSTFLOAT(60.0f);
		fVslider2 = FAUSTFLOAT(60.0f);
		fVslider3 = FAUSTFLOAT(60.0f);
		fVslider4 = FAUSTFLOAT(60.0f);
		fVslider5 = FAUSTFLOAT(60.0f);
		fVslider6 = FAUSTFLOAT(60.0f);
		fButton0 = FAUSTFLOAT(0.0f);
		fHslider0 = FAUSTFLOAT(60.0f);
		fVslider7 = FAUSTFLOAT(60.0f);
		fVslider8 = FAUSTFLOAT(60.0f);
		fVslider9 = FAUSTFLOAT(60.0f);
		fEntry1 = FAUSTFLOAT(60.0f);
		fVslider10 = FAUSTFLOAT(60.0f);
		fVslider11 = FAUSTFLOAT(60.0f);
		fVslider12 = FAUSTFLOAT(60.0f);
		fEntry2 = FAUSTFLOAT(60.0f);
		fVslider13 = FAUSTFLOAT(60.0f);
		fVslider14 = FAUSTFLOAT(60.0f);
		fVslider15 = FAUSTFLOAT(60.0f);
		fEntry3 = FAUSTFLOAT(60.0f);
		fVslider16 = FAUSTFLOAT(60.0f);
		fButton1 = FAUSTFLOAT(0.0f);
		fHslider1 = FAUSTFLOAT(60.0f);
		fEntry4 = FAUSTFLOAT(60.0f);
		
	}
	
	virtual void instanceClear() {
		
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
		ui_interface->openTabBox("grp 1");
		ui_interface->openHorizontalBox("hmisc");
		ui_interface->addButton("button", &fButton1);
		ui_interface->addHorizontalBargraph("hbar", &fHbargraph1, 0.0f, 127.0f);
		ui_interface->addHorizontalSlider("hslider", &fHslider1, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface->declare(&fEntry4, "unit", "f");
		ui_interface->addNumEntry("num", &fEntry4, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface->addVerticalBargraph("vbar", &fVbargraph3, 0.0f, 127.0f);
		ui_interface->declare(&fVslider16, "unit", "f");
		ui_interface->addVerticalSlider("vslider4", &fVslider16, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("knobs");
		ui_interface->declare(&fVslider3, "style", "knob");
		ui_interface->addVerticalSlider("knob1", &fVslider3, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface->declare(&fVslider4, "style", "knob");
		ui_interface->addVerticalSlider("knob2", &fVslider4, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface->declare(&fVslider5, "style", "knob");
		ui_interface->addVerticalSlider("knob3", &fVslider5, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("sliders");
		ui_interface->addVerticalSlider("vslider1", &fVslider0, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface->addVerticalSlider("vslider2", &fVslider1, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface->addVerticalSlider("vslider3", &fVslider2, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("vbox");
		ui_interface->addCheckButton("check1", &fCheckbox0);
		ui_interface->addCheckButton("check2", &fCheckbox1);
		ui_interface->declare(&fEntry0, "style", "knob");
		ui_interface->addNumEntry("knob0", &fEntry0, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("vmisc");
		ui_interface->addButton("button", &fButton0);
		ui_interface->addHorizontalBargraph("hbar", &fHbargraph0, 0.0f, 127.0f);
		ui_interface->declare(&fHslider0, "unit", "Hz");
		ui_interface->addHorizontalSlider("hslider", &fHslider0, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface->openHorizontalBox("small box 1");
		ui_interface->declare(&fVslider9, "style", "knob");
		ui_interface->addVerticalSlider("knob4", &fVslider9, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface->declare(&fEntry1, "unit", "f");
		ui_interface->addNumEntry("num1", &fEntry1, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface->addVerticalBargraph("vbar1", &fVbargraph0, 0.0f, 127.0f);
		ui_interface->declare(&fVslider7, "unit", "Hz");
		ui_interface->addVerticalSlider("vslider5", &fVslider7, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface->declare(&fVslider8, "unit", "Hz");
		ui_interface->addVerticalSlider("vslider6", &fVslider8, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("sub box 1");
		ui_interface->openHorizontalBox("small box 2");
		ui_interface->declare(&fVslider12, "style", "knob");
		ui_interface->addVerticalSlider("knob5", &fVslider12, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface->declare(&fEntry2, "unit", "f");
		ui_interface->addNumEntry("num2", &fEntry2, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface->addVerticalBargraph("vbar2", &fVbargraph1, 0.0f, 127.0f);
		ui_interface->declare(&fVslider10, "unit", "Hz");
		ui_interface->addVerticalSlider("vslider7", &fVslider10, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface->declare(&fVslider11, "unit", "Hz");
		ui_interface->addVerticalSlider("vslider8", &fVslider11, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("small box 3");
		ui_interface->declare(&fVslider15, "style", "knob");
		ui_interface->addVerticalSlider("knob6", &fVslider15, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface->declare(&fEntry3, "unit", "f");
		ui_interface->addNumEntry("num3", &fEntry3, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface->addVerticalBargraph("vbar3", &fVbargraph2, 0.0f, 127.0f);
		ui_interface->declare(&fVslider14, "unit", "m");
		ui_interface->addVerticalSlider("vslider10", &fVslider14, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface->declare(&fVslider13, "unit", "Hz");
		ui_interface->addVerticalSlider("vslider9", &fVslider13, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(&fVslider6, "unit", "Hz");
		ui_interface->addVerticalSlider("vslider4", &fVslider6, 60.0f, 0.0f, 127.0f, 0.100000001f);
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
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		FAUSTFLOAT* output2 = outputs[2];
		FAUSTFLOAT* output3 = outputs[3];
		FAUSTFLOAT* output4 = outputs[4];
		FAUSTFLOAT* output5 = outputs[5];
		FAUSTFLOAT* output6 = outputs[6];
		FAUSTFLOAT* output7 = outputs[7];
		FAUSTFLOAT* output8 = outputs[8];
		FAUSTFLOAT* output9 = outputs[9];
		FAUSTFLOAT* output10 = outputs[10];
		FAUSTFLOAT* output11 = outputs[11];
		FAUSTFLOAT* output12 = outputs[12];
		FAUSTFLOAT* output13 = outputs[13];
		FAUSTFLOAT* output14 = outputs[14];
		FAUSTFLOAT* output15 = outputs[15];
		FAUSTFLOAT* output16 = outputs[16];
		FAUSTFLOAT* output17 = outputs[17];
		FAUSTFLOAT* output18 = outputs[18];
		FAUSTFLOAT* output19 = outputs[19];
		FAUSTFLOAT* output20 = outputs[20];
		FAUSTFLOAT* output21 = outputs[21];
		FAUSTFLOAT* output22 = outputs[22];
		FAUSTFLOAT* output23 = outputs[23];
		FAUSTFLOAT* output24 = outputs[24];
		FAUSTFLOAT* output25 = outputs[25];
		FAUSTFLOAT* output26 = outputs[26];
		FAUSTFLOAT* output27 = outputs[27];
		FAUSTFLOAT* output28 = outputs[28];
		FAUSTFLOAT* output29 = outputs[29];
		FAUSTFLOAT* output30 = outputs[30];
		FAUSTFLOAT* output31 = outputs[31];
		FAUSTFLOAT* output32 = outputs[32];
		FAUSTFLOAT* output33 = outputs[33];
		float fSlow0 = float(fCheckbox0);
		float fSlow1 = float(fCheckbox1);
		float fSlow2 = float(fEntry0);
		float fSlow3 = float(fVslider0);
		float fSlow4 = float(fVslider1);
		float fSlow5 = float(fVslider2);
		float fSlow6 = float(fVslider3);
		float fSlow7 = float(fVslider4);
		float fSlow8 = float(fVslider5);
		float fSlow9 = float(fVslider6);
		float fSlow10 = float(fButton0);
		float fSlow11 = float(fHslider0);
		float fSlow12 = float(fVslider7);
		float fSlow13 = float(fVslider8);
		float fSlow14 = float(fVslider9);
		float fSlow15 = float(fEntry1);
		float fSlow16 = float(fVslider10);
		float fSlow17 = float(fVslider11);
		float fSlow18 = float(fVslider12);
		float fSlow19 = float(fEntry2);
		float fSlow20 = float(fVslider13);
		float fSlow21 = float(fVslider14);
		float fSlow22 = float(fVslider15);
		float fSlow23 = float(fEntry3);
		float fSlow24 = float(fVslider16);
		float fSlow25 = float(fButton1);
		float fSlow26 = float(fHslider1);
		float fSlow27 = float(fEntry4);
		for (int i = 0; (i < count); i = (i + 1)) {
			output0[i] = FAUSTFLOAT(fSlow0);
			output1[i] = FAUSTFLOAT(fSlow1);
			output2[i] = FAUSTFLOAT(fSlow2);
			output3[i] = FAUSTFLOAT(fSlow3);
			output4[i] = FAUSTFLOAT(fSlow4);
			output5[i] = FAUSTFLOAT(fSlow5);
			output6[i] = FAUSTFLOAT(fSlow6);
			output7[i] = FAUSTFLOAT(fSlow7);
			output8[i] = FAUSTFLOAT(fSlow8);
			output9[i] = FAUSTFLOAT(fSlow9);
			output10[i] = FAUSTFLOAT(fSlow10);
			output11[i] = FAUSTFLOAT(fSlow11);
			output12[i] = FAUSTFLOAT(fSlow12);
			output13[i] = FAUSTFLOAT(fSlow13);
			output14[i] = FAUSTFLOAT(fSlow14);
			output15[i] = FAUSTFLOAT(fSlow15);
			fVbargraph0 = FAUSTFLOAT(float(input0[i]));
			output16[i] = FAUSTFLOAT(fVbargraph0);
			output17[i] = FAUSTFLOAT(fSlow16);
			output18[i] = FAUSTFLOAT(fSlow17);
			output19[i] = FAUSTFLOAT(fSlow18);
			output20[i] = FAUSTFLOAT(fSlow19);
			fVbargraph1 = FAUSTFLOAT(float(input1[i]));
			output21[i] = FAUSTFLOAT(fVbargraph1);
			output22[i] = FAUSTFLOAT(fSlow20);
			output23[i] = FAUSTFLOAT(fSlow21);
			output24[i] = FAUSTFLOAT(fSlow22);
			output25[i] = FAUSTFLOAT(fSlow23);
			fVbargraph2 = FAUSTFLOAT(float(input2[i]));
			output26[i] = FAUSTFLOAT(fVbargraph2);
			fHbargraph0 = FAUSTFLOAT(float(input3[i]));
			output27[i] = FAUSTFLOAT(fHbargraph0);
			output28[i] = FAUSTFLOAT(fSlow24);
			output29[i] = FAUSTFLOAT(fSlow25);
			output30[i] = FAUSTFLOAT(fSlow26);
			output31[i] = FAUSTFLOAT(fSlow27);
			fVbargraph3 = FAUSTFLOAT(float(input4[i]));
			output32[i] = FAUSTFLOAT(fVbargraph3);
			fHbargraph1 = FAUSTFLOAT(float(input5[i]));
			output33[i] = FAUSTFLOAT(fHbargraph1);
			
		}
		
	}

	
};

#endif
