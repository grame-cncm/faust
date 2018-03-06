/* ------------------------------------------------------------
name: "UITester.dsp-mute"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: cpp, -double -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT double
#endif

#include "controlTools.h"

//----------------------------------------------------------------------------
//FAUST generated code
//----------------------------------------------------------------------------


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
	FAUSTFLOAT fCheckbox2;
	FAUSTFLOAT fCheckbox3;
	FAUSTFLOAT fEntry0;
	FAUSTFLOAT fCheckbox4;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT fCheckbox5;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fCheckbox6;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT fCheckbox7;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT fCheckbox8;
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT fCheckbox9;
	FAUSTFLOAT fVslider5;
	FAUSTFLOAT fCheckbox10;
	FAUSTFLOAT fVslider6;
	FAUSTFLOAT fCheckbox11;
	FAUSTFLOAT fButton0;
	FAUSTFLOAT fCheckbox12;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fCheckbox13;
	FAUSTFLOAT fVslider7;
	FAUSTFLOAT fCheckbox14;
	FAUSTFLOAT fVslider8;
	FAUSTFLOAT fCheckbox15;
	FAUSTFLOAT fVslider9;
	FAUSTFLOAT fCheckbox16;
	FAUSTFLOAT fEntry1;
	FAUSTFLOAT fCheckbox17;
	FAUSTFLOAT fCheckbox18;
	FAUSTFLOAT fVbargraph0;
	FAUSTFLOAT fVslider10;
	FAUSTFLOAT fCheckbox19;
	FAUSTFLOAT fVslider11;
	FAUSTFLOAT fCheckbox20;
	FAUSTFLOAT fVslider12;
	FAUSTFLOAT fCheckbox21;
	FAUSTFLOAT fEntry2;
	FAUSTFLOAT fCheckbox22;
	FAUSTFLOAT fCheckbox23;
	FAUSTFLOAT fVbargraph1;
	FAUSTFLOAT fVslider13;
	FAUSTFLOAT fCheckbox24;
	FAUSTFLOAT fVslider14;
	FAUSTFLOAT fCheckbox25;
	FAUSTFLOAT fVslider15;
	FAUSTFLOAT fCheckbox26;
	FAUSTFLOAT fEntry3;
	FAUSTFLOAT fCheckbox27;
	FAUSTFLOAT fCheckbox28;
	FAUSTFLOAT fVbargraph2;
	FAUSTFLOAT fCheckbox29;
	FAUSTFLOAT fHbargraph0;
	FAUSTFLOAT fVslider16;
	FAUSTFLOAT fCheckbox30;
	FAUSTFLOAT fButton1;
	FAUSTFLOAT fCheckbox31;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fCheckbox32;
	FAUSTFLOAT fEntry4;
	FAUSTFLOAT fCheckbox33;
	FAUSTFLOAT fCheckbox34;
	FAUSTFLOAT fVbargraph3;
	FAUSTFLOAT fCheckbox35;
	FAUSTFLOAT fHbargraph1;
	int fSamplingFreq;
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("UITester.dsp/author", "O. Guillerminet");
		m->declare("UITester.dsp/copyright", "(c) O. Guillerminet 2012");
		m->declare("UITester.dsp/license", "BSD");
		m->declare("UITester.dsp/name", "UI Tester");
		m->declare("UITester.dsp/version", "1.0");
		m->declare("name", "UITester.dsp-mute");
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
		fCheckbox0 = FAUSTFLOAT(0.0);
		fCheckbox1 = FAUSTFLOAT(0.0);
		fCheckbox2 = FAUSTFLOAT(0.0);
		fCheckbox3 = FAUSTFLOAT(0.0);
		fEntry0 = FAUSTFLOAT(60.0);
		fCheckbox4 = FAUSTFLOAT(0.0);
		fVslider0 = FAUSTFLOAT(60.0);
		fCheckbox5 = FAUSTFLOAT(0.0);
		fVslider1 = FAUSTFLOAT(60.0);
		fCheckbox6 = FAUSTFLOAT(0.0);
		fVslider2 = FAUSTFLOAT(60.0);
		fCheckbox7 = FAUSTFLOAT(0.0);
		fVslider3 = FAUSTFLOAT(60.0);
		fCheckbox8 = FAUSTFLOAT(0.0);
		fVslider4 = FAUSTFLOAT(60.0);
		fCheckbox9 = FAUSTFLOAT(0.0);
		fVslider5 = FAUSTFLOAT(60.0);
		fCheckbox10 = FAUSTFLOAT(0.0);
		fVslider6 = FAUSTFLOAT(60.0);
		fCheckbox11 = FAUSTFLOAT(0.0);
		fButton0 = FAUSTFLOAT(0.0);
		fCheckbox12 = FAUSTFLOAT(0.0);
		fHslider0 = FAUSTFLOAT(60.0);
		fCheckbox13 = FAUSTFLOAT(0.0);
		fVslider7 = FAUSTFLOAT(60.0);
		fCheckbox14 = FAUSTFLOAT(0.0);
		fVslider8 = FAUSTFLOAT(60.0);
		fCheckbox15 = FAUSTFLOAT(0.0);
		fVslider9 = FAUSTFLOAT(60.0);
		fCheckbox16 = FAUSTFLOAT(0.0);
		fEntry1 = FAUSTFLOAT(60.0);
		fCheckbox17 = FAUSTFLOAT(0.0);
		fCheckbox18 = FAUSTFLOAT(0.0);
		fVslider10 = FAUSTFLOAT(60.0);
		fCheckbox19 = FAUSTFLOAT(0.0);
		fVslider11 = FAUSTFLOAT(60.0);
		fCheckbox20 = FAUSTFLOAT(0.0);
		fVslider12 = FAUSTFLOAT(60.0);
		fCheckbox21 = FAUSTFLOAT(0.0);
		fEntry2 = FAUSTFLOAT(60.0);
		fCheckbox22 = FAUSTFLOAT(0.0);
		fCheckbox23 = FAUSTFLOAT(0.0);
		fVslider13 = FAUSTFLOAT(60.0);
		fCheckbox24 = FAUSTFLOAT(0.0);
		fVslider14 = FAUSTFLOAT(60.0);
		fCheckbox25 = FAUSTFLOAT(0.0);
		fVslider15 = FAUSTFLOAT(60.0);
		fCheckbox26 = FAUSTFLOAT(0.0);
		fEntry3 = FAUSTFLOAT(60.0);
		fCheckbox27 = FAUSTFLOAT(0.0);
		fCheckbox28 = FAUSTFLOAT(0.0);
		fCheckbox29 = FAUSTFLOAT(0.0);
		fVslider16 = FAUSTFLOAT(60.0);
		fCheckbox30 = FAUSTFLOAT(0.0);
		fButton1 = FAUSTFLOAT(0.0);
		fCheckbox31 = FAUSTFLOAT(0.0);
		fHslider1 = FAUSTFLOAT(60.0);
		fCheckbox32 = FAUSTFLOAT(0.0);
		fEntry4 = FAUSTFLOAT(60.0);
		fCheckbox33 = FAUSTFLOAT(0.0);
		fCheckbox34 = FAUSTFLOAT(0.0);
		fCheckbox35 = FAUSTFLOAT(0.0);
		
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
		ui_interface->openVerticalBox("UITester.dsp-mute");
		ui_interface->addCheckButton("fakedisable  0", &fCheckbox1);
		ui_interface->addCheckButton("fakedisable  1", &fCheckbox3);
		ui_interface->addCheckButton("fakedisable  2", &fCheckbox4);
		ui_interface->addCheckButton("fakedisable  3", &fCheckbox5);
		ui_interface->addCheckButton("fakedisable  4", &fCheckbox6);
		ui_interface->addCheckButton("fakedisable  5", &fCheckbox7);
		ui_interface->addCheckButton("fakedisable  6", &fCheckbox8);
		ui_interface->addCheckButton("fakedisable  7", &fCheckbox9);
		ui_interface->addCheckButton("fakedisable  8", &fCheckbox10);
		ui_interface->addCheckButton("fakedisable  9", &fCheckbox11);
		ui_interface->addCheckButton("fakedisable 10", &fCheckbox12);
		ui_interface->addCheckButton("fakedisable 11", &fCheckbox13);
		ui_interface->addCheckButton("fakedisable 12", &fCheckbox14);
		ui_interface->addCheckButton("fakedisable 13", &fCheckbox15);
		ui_interface->addCheckButton("fakedisable 14", &fCheckbox16);
		ui_interface->addCheckButton("fakedisable 15", &fCheckbox17);
		ui_interface->addCheckButton("fakedisable 16", &fCheckbox18);
		ui_interface->addCheckButton("fakedisable 17", &fCheckbox19);
		ui_interface->addCheckButton("fakedisable 18", &fCheckbox20);
		ui_interface->addCheckButton("fakedisable 19", &fCheckbox21);
		ui_interface->addCheckButton("fakedisable 20", &fCheckbox22);
		ui_interface->addCheckButton("fakedisable 21", &fCheckbox23);
		ui_interface->addCheckButton("fakedisable 22", &fCheckbox24);
		ui_interface->addCheckButton("fakedisable 23", &fCheckbox25);
		ui_interface->addCheckButton("fakedisable 24", &fCheckbox26);
		ui_interface->addCheckButton("fakedisable 25", &fCheckbox27);
		ui_interface->addCheckButton("fakedisable 26", &fCheckbox28);
		ui_interface->addCheckButton("fakedisable 27", &fCheckbox29);
		ui_interface->addCheckButton("fakedisable 28", &fCheckbox30);
		ui_interface->addCheckButton("fakedisable 29", &fCheckbox31);
		ui_interface->addCheckButton("fakedisable 30", &fCheckbox32);
		ui_interface->addCheckButton("fakedisable 31", &fCheckbox33);
		ui_interface->addCheckButton("fakedisable 32", &fCheckbox34);
		ui_interface->addCheckButton("fakedisable 33", &fCheckbox35);
		ui_interface->openTabBox("grp 1");
		ui_interface->openHorizontalBox("hmisc");
		ui_interface->addButton("button", &fButton1);
		ui_interface->addHorizontalBargraph("hbar", &fHbargraph1, 0.0, 127.0);
		ui_interface->addHorizontalSlider("hslider", &fHslider1, 60.0, 0.0, 127.0, 0.10000000000000001);
		ui_interface->declare(&fEntry4, "unit", "f");
		ui_interface->addNumEntry("num", &fEntry4, 60.0, 0.0, 127.0, 0.10000000000000001);
		ui_interface->addVerticalBargraph("vbar", &fVbargraph3, 0.0, 127.0);
		ui_interface->declare(&fVslider16, "unit", "f");
		ui_interface->addVerticalSlider("vslider4", &fVslider16, 60.0, 0.0, 127.0, 0.10000000000000001);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("knobs");
		ui_interface->declare(&fVslider3, "style", "knob");
		ui_interface->addVerticalSlider("knob1", &fVslider3, 60.0, 0.0, 127.0, 0.10000000000000001);
		ui_interface->declare(&fVslider4, "style", "knob");
		ui_interface->addVerticalSlider("knob2", &fVslider4, 60.0, 0.0, 127.0, 0.10000000000000001);
		ui_interface->declare(&fVslider5, "style", "knob");
		ui_interface->addVerticalSlider("knob3", &fVslider5, 60.0, 0.0, 127.0, 0.10000000000000001);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("sliders");
		ui_interface->addVerticalSlider("vslider1", &fVslider0, 60.0, 0.0, 127.0, 0.10000000000000001);
		ui_interface->addVerticalSlider("vslider2", &fVslider1, 60.0, 0.0, 127.0, 0.10000000000000001);
		ui_interface->addVerticalSlider("vslider3", &fVslider2, 60.0, 0.0, 127.0, 0.10000000000000001);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("vbox");
		ui_interface->addCheckButton("check1", &fCheckbox0);
		ui_interface->addCheckButton("check2", &fCheckbox2);
		ui_interface->declare(&fEntry0, "style", "knob");
		ui_interface->addNumEntry("knob0", &fEntry0, 60.0, 0.0, 127.0, 0.10000000000000001);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("vmisc");
		ui_interface->addButton("button", &fButton0);
		ui_interface->addHorizontalBargraph("hbar", &fHbargraph0, 0.0, 127.0);
		ui_interface->declare(&fHslider0, "unit", "Hz");
		ui_interface->addHorizontalSlider("hslider", &fHslider0, 60.0, 0.0, 127.0, 0.10000000000000001);
		ui_interface->openHorizontalBox("small box 1");
		ui_interface->declare(&fVslider9, "style", "knob");
		ui_interface->addVerticalSlider("knob4", &fVslider9, 60.0, 0.0, 127.0, 0.10000000000000001);
		ui_interface->declare(&fEntry1, "unit", "f");
		ui_interface->addNumEntry("num1", &fEntry1, 60.0, 0.0, 127.0, 0.10000000000000001);
		ui_interface->addVerticalBargraph("vbar1", &fVbargraph0, 0.0, 127.0);
		ui_interface->declare(&fVslider7, "unit", "Hz");
		ui_interface->addVerticalSlider("vslider5", &fVslider7, 60.0, 0.0, 127.0, 0.10000000000000001);
		ui_interface->declare(&fVslider8, "unit", "Hz");
		ui_interface->addVerticalSlider("vslider6", &fVslider8, 60.0, 0.0, 127.0, 0.10000000000000001);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("sub box 1");
		ui_interface->openHorizontalBox("small box 2");
		ui_interface->declare(&fVslider12, "style", "knob");
		ui_interface->addVerticalSlider("knob5", &fVslider12, 60.0, 0.0, 127.0, 0.10000000000000001);
		ui_interface->declare(&fEntry2, "unit", "f");
		ui_interface->addNumEntry("num2", &fEntry2, 60.0, 0.0, 127.0, 0.10000000000000001);
		ui_interface->addVerticalBargraph("vbar2", &fVbargraph1, 0.0, 127.0);
		ui_interface->declare(&fVslider10, "unit", "Hz");
		ui_interface->addVerticalSlider("vslider7", &fVslider10, 60.0, 0.0, 127.0, 0.10000000000000001);
		ui_interface->declare(&fVslider11, "unit", "Hz");
		ui_interface->addVerticalSlider("vslider8", &fVslider11, 60.0, 0.0, 127.0, 0.10000000000000001);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("small box 3");
		ui_interface->declare(&fVslider15, "style", "knob");
		ui_interface->addVerticalSlider("knob6", &fVslider15, 60.0, 0.0, 127.0, 0.10000000000000001);
		ui_interface->declare(&fEntry3, "unit", "f");
		ui_interface->addNumEntry("num3", &fEntry3, 60.0, 0.0, 127.0, 0.10000000000000001);
		ui_interface->addVerticalBargraph("vbar3", &fVbargraph2, 0.0, 127.0);
		ui_interface->declare(&fVslider14, "unit", "m");
		ui_interface->addVerticalSlider("vslider10", &fVslider14, 60.0, 0.0, 127.0, 0.10000000000000001);
		ui_interface->declare(&fVslider13, "unit", "Hz");
		ui_interface->addVerticalSlider("vslider9", &fVslider13, 60.0, 0.0, 127.0, 0.10000000000000001);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(&fVslider6, "unit", "Hz");
		ui_interface->addVerticalSlider("vslider4", &fVslider6, 60.0, 0.0, 127.0, 0.10000000000000001);
		ui_interface->closeBox();
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
		double fSlow0 = (double(fCheckbox0) * (1.0 - double(fCheckbox1)));
		double fSlow1 = (double(fCheckbox2) * (1.0 - double(fCheckbox3)));
		double fSlow2 = (double(fEntry0) * (1.0 - double(fCheckbox4)));
		double fSlow3 = (double(fVslider0) * (1.0 - double(fCheckbox5)));
		double fSlow4 = (double(fVslider1) * (1.0 - double(fCheckbox6)));
		double fSlow5 = (double(fVslider2) * (1.0 - double(fCheckbox7)));
		double fSlow6 = (double(fVslider3) * (1.0 - double(fCheckbox8)));
		double fSlow7 = (double(fVslider4) * (1.0 - double(fCheckbox9)));
		double fSlow8 = (double(fVslider5) * (1.0 - double(fCheckbox10)));
		double fSlow9 = (double(fVslider6) * (1.0 - double(fCheckbox11)));
		double fSlow10 = (double(fButton0) * (1.0 - double(fCheckbox12)));
		double fSlow11 = (double(fHslider0) * (1.0 - double(fCheckbox13)));
		double fSlow12 = (double(fVslider7) * (1.0 - double(fCheckbox14)));
		double fSlow13 = (double(fVslider8) * (1.0 - double(fCheckbox15)));
		double fSlow14 = (double(fVslider9) * (1.0 - double(fCheckbox16)));
		double fSlow15 = (double(fEntry1) * (1.0 - double(fCheckbox17)));
		double fSlow16 = (1.0 - double(fCheckbox18));
		double fSlow17 = (double(fVslider10) * (1.0 - double(fCheckbox19)));
		double fSlow18 = (double(fVslider11) * (1.0 - double(fCheckbox20)));
		double fSlow19 = (double(fVslider12) * (1.0 - double(fCheckbox21)));
		double fSlow20 = (double(fEntry2) * (1.0 - double(fCheckbox22)));
		double fSlow21 = (1.0 - double(fCheckbox23));
		double fSlow22 = (double(fVslider13) * (1.0 - double(fCheckbox24)));
		double fSlow23 = (double(fVslider14) * (1.0 - double(fCheckbox25)));
		double fSlow24 = (double(fVslider15) * (1.0 - double(fCheckbox26)));
		double fSlow25 = (double(fEntry3) * (1.0 - double(fCheckbox27)));
		double fSlow26 = (1.0 - double(fCheckbox28));
		double fSlow27 = (1.0 - double(fCheckbox29));
		double fSlow28 = (double(fVslider16) * (1.0 - double(fCheckbox30)));
		double fSlow29 = (double(fButton1) * (1.0 - double(fCheckbox31)));
		double fSlow30 = (double(fHslider1) * (1.0 - double(fCheckbox32)));
		double fSlow31 = (double(fEntry4) * (1.0 - double(fCheckbox33)));
		double fSlow32 = (1.0 - double(fCheckbox34));
		double fSlow33 = (1.0 - double(fCheckbox35));
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
			fVbargraph0 = FAUSTFLOAT(double(input0[i]));
			output16[i] = FAUSTFLOAT((fSlow16 * fVbargraph0));
			output17[i] = FAUSTFLOAT(fSlow17);
			output18[i] = FAUSTFLOAT(fSlow18);
			output19[i] = FAUSTFLOAT(fSlow19);
			output20[i] = FAUSTFLOAT(fSlow20);
			fVbargraph1 = FAUSTFLOAT(double(input1[i]));
			output21[i] = FAUSTFLOAT((fSlow21 * fVbargraph1));
			output22[i] = FAUSTFLOAT(fSlow22);
			output23[i] = FAUSTFLOAT(fSlow23);
			output24[i] = FAUSTFLOAT(fSlow24);
			output25[i] = FAUSTFLOAT(fSlow25);
			fVbargraph2 = FAUSTFLOAT(double(input2[i]));
			output26[i] = FAUSTFLOAT((fSlow26 * fVbargraph2));
			fHbargraph0 = FAUSTFLOAT(double(input3[i]));
			output27[i] = FAUSTFLOAT((fSlow27 * fHbargraph0));
			output28[i] = FAUSTFLOAT(fSlow28);
			output29[i] = FAUSTFLOAT(fSlow29);
			output30[i] = FAUSTFLOAT(fSlow30);
			output31[i] = FAUSTFLOAT(fSlow31);
			fVbargraph3 = FAUSTFLOAT(double(input4[i]));
			output32[i] = FAUSTFLOAT((fSlow32 * fVbargraph3));
			fHbargraph1 = FAUSTFLOAT(double(input5[i]));
			output33[i] = FAUSTFLOAT((fSlow33 * fHbargraph1));
			
		}
		
	}

	
};

mydsp* DSP;

int main(int argc, char* argv[])
{
    char rcfilename[256];
    FUI finterface;
    snprintf(rcfilename, 255, "%src", argv[0]);
    
    bool inpl = isopt(argv, "-inpl");
    
    DSP = new mydsp();
    
    DSP->buildUserInterface(&finterface);
 
    // Get control and then 'initRandom'
    CheckControlUI controlui;
    DSP->buildUserInterface(&controlui);
    controlui.initRandom();
    
    // Init signal processor and the user interface values
    DSP->init(44100);
    
    // Check getSampleRate
    if (DSP->getSampleRate() != 44100) {
        cerr << "ERROR in getSampleRate" << std::endl;
    }
   
    // Check default after 'init'
    if (!controlui.checkDefaults()) {
        cerr << "ERROR in checkDefaults after 'init'" << std::endl;
    }
    
    // Check default after 'instanceResetUserInterface'
    controlui.initRandom();
    DSP->instanceResetUserInterface();
    if (!controlui.checkDefaults()) {
        cerr << "ERROR in checkDefaults after 'instanceResetUserInterface'" << std::endl;
    }
    
    // Check default after 'instanceInit'
    controlui.initRandom();
    DSP->instanceInit(44100);
    if (!controlui.checkDefaults()) {
        cerr << "ERROR in checkDefaults after 'instanceInit'" << std::endl;
    }
    
    // Init again
    DSP->init(44100);
 
    int nins = DSP->getNumInputs();
    int nouts = DSP->getNumOutputs();
    
    channels* ichan = new channels(kFrames, ((inpl) ? std::max(nins, nouts) : nins));
    channels* ochan = (inpl) ? ichan : new channels(kFrames, nouts);

    int nbsamples = 60000;
    int linenum = 0;
    int run = 0;
    
    // recall saved state
    finterface.recallState(rcfilename);
    
    // print general informations
    printf("number_of_inputs  : %3d\n", nins);
    printf("number_of_outputs : %3d\n", nouts);
    printf("number_of_frames  : %6d\n", nbsamples);
    
    // print audio frames
    int i;
    try {
        while (nbsamples > 0) {
            if (run == 0) {
                ichan->impulse();
                finterface.setButtons(true);
            }
            if (run >= 1) {
                ichan->zero();
                finterface.setButtons(false);
            }
            int nFrames = min(kFrames, nbsamples);
            DSP->compute(nFrames, ichan->buffers(), ochan->buffers());
            run++;
            for (int i = 0; i < nFrames; i++) {
                printf("%6d : ", linenum++);
                for (int c = 0; c < nouts; c++) {
                    FAUSTFLOAT f = normalize(ochan->buffers()[c][i]);
                    printf(" %8.6f", f);
                }
                printf("\n");
            }
            nbsamples -= nFrames;
        }
    } catch (...) {
        cerr << "ERROR in " << argv[1] << " line : " << i << std::endl;
    }
    
    testPolyphony(DSP);
    
    return 0;
}

#endif
