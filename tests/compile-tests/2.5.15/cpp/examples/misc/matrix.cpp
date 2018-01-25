/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2006"
license: "BSD"
name: "matrix"
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
	
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT fVslider5;
	FAUSTFLOAT fVslider6;
	FAUSTFLOAT fVslider7;
	FAUSTFLOAT fVslider8;
	FAUSTFLOAT fVslider9;
	FAUSTFLOAT fVslider10;
	FAUSTFLOAT fVslider11;
	FAUSTFLOAT fVslider12;
	FAUSTFLOAT fVslider13;
	FAUSTFLOAT fVslider14;
	FAUSTFLOAT fVslider15;
	FAUSTFLOAT fVslider16;
	FAUSTFLOAT fVslider17;
	FAUSTFLOAT fVslider18;
	FAUSTFLOAT fVslider19;
	FAUSTFLOAT fVslider20;
	FAUSTFLOAT fVslider21;
	FAUSTFLOAT fVslider22;
	FAUSTFLOAT fVslider23;
	FAUSTFLOAT fVslider24;
	FAUSTFLOAT fVslider25;
	FAUSTFLOAT fVslider26;
	FAUSTFLOAT fVslider27;
	FAUSTFLOAT fVslider28;
	FAUSTFLOAT fVslider29;
	FAUSTFLOAT fVslider30;
	FAUSTFLOAT fVslider31;
	FAUSTFLOAT fVslider32;
	FAUSTFLOAT fVslider33;
	FAUSTFLOAT fVslider34;
	FAUSTFLOAT fVslider35;
	FAUSTFLOAT fVslider36;
	FAUSTFLOAT fVslider37;
	FAUSTFLOAT fVslider38;
	FAUSTFLOAT fVslider39;
	FAUSTFLOAT fVslider40;
	FAUSTFLOAT fVslider41;
	FAUSTFLOAT fVslider42;
	FAUSTFLOAT fVslider43;
	FAUSTFLOAT fVslider44;
	FAUSTFLOAT fVslider45;
	FAUSTFLOAT fVslider46;
	FAUSTFLOAT fVslider47;
	FAUSTFLOAT fVslider48;
	FAUSTFLOAT fVslider49;
	FAUSTFLOAT fVslider50;
	FAUSTFLOAT fVslider51;
	FAUSTFLOAT fVslider52;
	FAUSTFLOAT fVslider53;
	FAUSTFLOAT fVslider54;
	FAUSTFLOAT fVslider55;
	FAUSTFLOAT fVslider56;
	FAUSTFLOAT fVslider57;
	FAUSTFLOAT fVslider58;
	FAUSTFLOAT fVslider59;
	FAUSTFLOAT fVslider60;
	FAUSTFLOAT fVslider61;
	FAUSTFLOAT fVslider62;
	FAUSTFLOAT fVslider63;
	int fSamplingFreq;
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("author", "Grame");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("copyright", "(c)GRAME 2006");
		m->declare("license", "BSD");
		m->declare("name", "matrix");
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
		
	}
	
	virtual void instanceResetUserInterface() {
		fVslider0 = FAUSTFLOAT(-10.0f);
		fVslider1 = FAUSTFLOAT(-10.0f);
		fVslider2 = FAUSTFLOAT(-10.0f);
		fVslider3 = FAUSTFLOAT(-10.0f);
		fVslider4 = FAUSTFLOAT(-10.0f);
		fVslider5 = FAUSTFLOAT(-10.0f);
		fVslider6 = FAUSTFLOAT(-10.0f);
		fVslider7 = FAUSTFLOAT(-10.0f);
		fVslider8 = FAUSTFLOAT(-10.0f);
		fVslider9 = FAUSTFLOAT(-10.0f);
		fVslider10 = FAUSTFLOAT(-10.0f);
		fVslider11 = FAUSTFLOAT(-10.0f);
		fVslider12 = FAUSTFLOAT(-10.0f);
		fVslider13 = FAUSTFLOAT(-10.0f);
		fVslider14 = FAUSTFLOAT(-10.0f);
		fVslider15 = FAUSTFLOAT(-10.0f);
		fVslider16 = FAUSTFLOAT(-10.0f);
		fVslider17 = FAUSTFLOAT(-10.0f);
		fVslider18 = FAUSTFLOAT(-10.0f);
		fVslider19 = FAUSTFLOAT(-10.0f);
		fVslider20 = FAUSTFLOAT(-10.0f);
		fVslider21 = FAUSTFLOAT(-10.0f);
		fVslider22 = FAUSTFLOAT(-10.0f);
		fVslider23 = FAUSTFLOAT(-10.0f);
		fVslider24 = FAUSTFLOAT(-10.0f);
		fVslider25 = FAUSTFLOAT(-10.0f);
		fVslider26 = FAUSTFLOAT(-10.0f);
		fVslider27 = FAUSTFLOAT(-10.0f);
		fVslider28 = FAUSTFLOAT(-10.0f);
		fVslider29 = FAUSTFLOAT(-10.0f);
		fVslider30 = FAUSTFLOAT(-10.0f);
		fVslider31 = FAUSTFLOAT(-10.0f);
		fVslider32 = FAUSTFLOAT(-10.0f);
		fVslider33 = FAUSTFLOAT(-10.0f);
		fVslider34 = FAUSTFLOAT(-10.0f);
		fVslider35 = FAUSTFLOAT(-10.0f);
		fVslider36 = FAUSTFLOAT(-10.0f);
		fVslider37 = FAUSTFLOAT(-10.0f);
		fVslider38 = FAUSTFLOAT(-10.0f);
		fVslider39 = FAUSTFLOAT(-10.0f);
		fVslider40 = FAUSTFLOAT(-10.0f);
		fVslider41 = FAUSTFLOAT(-10.0f);
		fVslider42 = FAUSTFLOAT(-10.0f);
		fVslider43 = FAUSTFLOAT(-10.0f);
		fVslider44 = FAUSTFLOAT(-10.0f);
		fVslider45 = FAUSTFLOAT(-10.0f);
		fVslider46 = FAUSTFLOAT(-10.0f);
		fVslider47 = FAUSTFLOAT(-10.0f);
		fVslider48 = FAUSTFLOAT(-10.0f);
		fVslider49 = FAUSTFLOAT(-10.0f);
		fVslider50 = FAUSTFLOAT(-10.0f);
		fVslider51 = FAUSTFLOAT(-10.0f);
		fVslider52 = FAUSTFLOAT(-10.0f);
		fVslider53 = FAUSTFLOAT(-10.0f);
		fVslider54 = FAUSTFLOAT(-10.0f);
		fVslider55 = FAUSTFLOAT(-10.0f);
		fVslider56 = FAUSTFLOAT(-10.0f);
		fVslider57 = FAUSTFLOAT(-10.0f);
		fVslider58 = FAUSTFLOAT(-10.0f);
		fVslider59 = FAUSTFLOAT(-10.0f);
		fVslider60 = FAUSTFLOAT(-10.0f);
		fVslider61 = FAUSTFLOAT(-10.0f);
		fVslider62 = FAUSTFLOAT(-10.0f);
		fVslider63 = FAUSTFLOAT(-10.0f);
		
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
		ui_interface->openTabBox("Matrix 8 x 8");
		ui_interface->openHorizontalBox("Output 0");
		ui_interface->addVerticalSlider("Input 0", &fVslider0, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 1", &fVslider1, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 2", &fVslider2, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 3", &fVslider3, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 4", &fVslider4, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 5", &fVslider5, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 6", &fVslider6, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 7", &fVslider7, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Output 1");
		ui_interface->addVerticalSlider("Input 0", &fVslider8, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 1", &fVslider9, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 2", &fVslider10, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 3", &fVslider11, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 4", &fVslider12, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 5", &fVslider13, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 6", &fVslider14, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 7", &fVslider15, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Output 2");
		ui_interface->addVerticalSlider("Input 0", &fVslider16, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 1", &fVslider17, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 2", &fVslider18, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 3", &fVslider19, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 4", &fVslider20, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 5", &fVslider21, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 6", &fVslider22, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 7", &fVslider23, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Output 3");
		ui_interface->addVerticalSlider("Input 0", &fVslider24, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 1", &fVslider25, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 2", &fVslider26, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 3", &fVslider27, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 4", &fVslider28, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 5", &fVslider29, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 6", &fVslider30, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 7", &fVslider31, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Output 4");
		ui_interface->addVerticalSlider("Input 0", &fVslider32, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 1", &fVslider33, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 2", &fVslider34, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 3", &fVslider35, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 4", &fVslider36, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 5", &fVslider37, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 6", &fVslider38, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 7", &fVslider39, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Output 5");
		ui_interface->addVerticalSlider("Input 0", &fVslider40, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 1", &fVslider41, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 2", &fVslider42, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 3", &fVslider43, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 4", &fVslider44, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 5", &fVslider45, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 6", &fVslider46, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 7", &fVslider47, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Output 6");
		ui_interface->addVerticalSlider("Input 0", &fVslider48, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 1", &fVslider49, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 2", &fVslider50, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 3", &fVslider51, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 4", &fVslider52, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 5", &fVslider53, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 6", &fVslider54, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 7", &fVslider55, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Output 7");
		ui_interface->addVerticalSlider("Input 0", &fVslider56, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 1", &fVslider57, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 2", &fVslider58, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 3", &fVslider59, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 4", &fVslider60, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 5", &fVslider61, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 6", &fVslider62, -10.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface->addVerticalSlider("Input 7", &fVslider63, -10.0f, -96.0f, 4.0f, 0.100000001f);
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
		float fSlow0 = powf(10.0f, (0.0500000007f * float(fVslider0)));
		float fSlow1 = powf(10.0f, (0.0500000007f * float(fVslider1)));
		float fSlow2 = powf(10.0f, (0.0500000007f * float(fVslider2)));
		float fSlow3 = powf(10.0f, (0.0500000007f * float(fVslider3)));
		float fSlow4 = powf(10.0f, (0.0500000007f * float(fVslider4)));
		float fSlow5 = powf(10.0f, (0.0500000007f * float(fVslider5)));
		float fSlow6 = powf(10.0f, (0.0500000007f * float(fVslider6)));
		float fSlow7 = powf(10.0f, (0.0500000007f * float(fVslider7)));
		float fSlow8 = powf(10.0f, (0.0500000007f * float(fVslider8)));
		float fSlow9 = powf(10.0f, (0.0500000007f * float(fVslider9)));
		float fSlow10 = powf(10.0f, (0.0500000007f * float(fVslider10)));
		float fSlow11 = powf(10.0f, (0.0500000007f * float(fVslider11)));
		float fSlow12 = powf(10.0f, (0.0500000007f * float(fVslider12)));
		float fSlow13 = powf(10.0f, (0.0500000007f * float(fVslider13)));
		float fSlow14 = powf(10.0f, (0.0500000007f * float(fVslider14)));
		float fSlow15 = powf(10.0f, (0.0500000007f * float(fVslider15)));
		float fSlow16 = powf(10.0f, (0.0500000007f * float(fVslider16)));
		float fSlow17 = powf(10.0f, (0.0500000007f * float(fVslider17)));
		float fSlow18 = powf(10.0f, (0.0500000007f * float(fVslider18)));
		float fSlow19 = powf(10.0f, (0.0500000007f * float(fVslider19)));
		float fSlow20 = powf(10.0f, (0.0500000007f * float(fVslider20)));
		float fSlow21 = powf(10.0f, (0.0500000007f * float(fVslider21)));
		float fSlow22 = powf(10.0f, (0.0500000007f * float(fVslider22)));
		float fSlow23 = powf(10.0f, (0.0500000007f * float(fVslider23)));
		float fSlow24 = powf(10.0f, (0.0500000007f * float(fVslider24)));
		float fSlow25 = powf(10.0f, (0.0500000007f * float(fVslider25)));
		float fSlow26 = powf(10.0f, (0.0500000007f * float(fVslider26)));
		float fSlow27 = powf(10.0f, (0.0500000007f * float(fVslider27)));
		float fSlow28 = powf(10.0f, (0.0500000007f * float(fVslider28)));
		float fSlow29 = powf(10.0f, (0.0500000007f * float(fVslider29)));
		float fSlow30 = powf(10.0f, (0.0500000007f * float(fVslider30)));
		float fSlow31 = powf(10.0f, (0.0500000007f * float(fVslider31)));
		float fSlow32 = powf(10.0f, (0.0500000007f * float(fVslider32)));
		float fSlow33 = powf(10.0f, (0.0500000007f * float(fVslider33)));
		float fSlow34 = powf(10.0f, (0.0500000007f * float(fVslider34)));
		float fSlow35 = powf(10.0f, (0.0500000007f * float(fVslider35)));
		float fSlow36 = powf(10.0f, (0.0500000007f * float(fVslider36)));
		float fSlow37 = powf(10.0f, (0.0500000007f * float(fVslider37)));
		float fSlow38 = powf(10.0f, (0.0500000007f * float(fVslider38)));
		float fSlow39 = powf(10.0f, (0.0500000007f * float(fVslider39)));
		float fSlow40 = powf(10.0f, (0.0500000007f * float(fVslider40)));
		float fSlow41 = powf(10.0f, (0.0500000007f * float(fVslider41)));
		float fSlow42 = powf(10.0f, (0.0500000007f * float(fVslider42)));
		float fSlow43 = powf(10.0f, (0.0500000007f * float(fVslider43)));
		float fSlow44 = powf(10.0f, (0.0500000007f * float(fVslider44)));
		float fSlow45 = powf(10.0f, (0.0500000007f * float(fVslider45)));
		float fSlow46 = powf(10.0f, (0.0500000007f * float(fVslider46)));
		float fSlow47 = powf(10.0f, (0.0500000007f * float(fVslider47)));
		float fSlow48 = powf(10.0f, (0.0500000007f * float(fVslider48)));
		float fSlow49 = powf(10.0f, (0.0500000007f * float(fVslider49)));
		float fSlow50 = powf(10.0f, (0.0500000007f * float(fVslider50)));
		float fSlow51 = powf(10.0f, (0.0500000007f * float(fVslider51)));
		float fSlow52 = powf(10.0f, (0.0500000007f * float(fVslider52)));
		float fSlow53 = powf(10.0f, (0.0500000007f * float(fVslider53)));
		float fSlow54 = powf(10.0f, (0.0500000007f * float(fVslider54)));
		float fSlow55 = powf(10.0f, (0.0500000007f * float(fVslider55)));
		float fSlow56 = powf(10.0f, (0.0500000007f * float(fVslider56)));
		float fSlow57 = powf(10.0f, (0.0500000007f * float(fVslider57)));
		float fSlow58 = powf(10.0f, (0.0500000007f * float(fVslider58)));
		float fSlow59 = powf(10.0f, (0.0500000007f * float(fVslider59)));
		float fSlow60 = powf(10.0f, (0.0500000007f * float(fVslider60)));
		float fSlow61 = powf(10.0f, (0.0500000007f * float(fVslider61)));
		float fSlow62 = powf(10.0f, (0.0500000007f * float(fVslider62)));
		float fSlow63 = powf(10.0f, (0.0500000007f * float(fVslider63)));
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input0[i]);
			float fTemp1 = float(input1[i]);
			float fTemp2 = float(input2[i]);
			float fTemp3 = float(input3[i]);
			float fTemp4 = float(input4[i]);
			float fTemp5 = float(input5[i]);
			float fTemp6 = float(input6[i]);
			float fTemp7 = float(input7[i]);
			output0[i] = FAUSTFLOAT(((((((((fSlow0 * fTemp0) + (fSlow1 * fTemp1)) + (fSlow2 * fTemp2)) + (fSlow3 * fTemp3)) + (fSlow4 * fTemp4)) + (fSlow5 * fTemp5)) + (fSlow6 * fTemp6)) + (fSlow7 * fTemp7)));
			output1[i] = FAUSTFLOAT(((((((((fSlow8 * fTemp0) + (fSlow9 * fTemp1)) + (fSlow10 * fTemp2)) + (fSlow11 * fTemp3)) + (fSlow12 * fTemp4)) + (fSlow13 * fTemp5)) + (fSlow14 * fTemp6)) + (fSlow15 * fTemp7)));
			output2[i] = FAUSTFLOAT(((((((((fSlow16 * fTemp0) + (fSlow17 * fTemp1)) + (fSlow18 * fTemp2)) + (fSlow19 * fTemp3)) + (fSlow20 * fTemp4)) + (fSlow21 * fTemp5)) + (fSlow22 * fTemp6)) + (fSlow23 * fTemp7)));
			output3[i] = FAUSTFLOAT(((((((((fSlow24 * fTemp0) + (fSlow25 * fTemp1)) + (fSlow26 * fTemp2)) + (fSlow27 * fTemp3)) + (fSlow28 * fTemp4)) + (fSlow29 * fTemp5)) + (fSlow30 * fTemp6)) + (fSlow31 * fTemp7)));
			output4[i] = FAUSTFLOAT(((((((((fSlow32 * fTemp0) + (fSlow33 * fTemp1)) + (fSlow34 * fTemp2)) + (fSlow35 * fTemp3)) + (fSlow36 * fTemp4)) + (fSlow37 * fTemp5)) + (fSlow38 * fTemp6)) + (fSlow39 * fTemp7)));
			output5[i] = FAUSTFLOAT(((((((((fSlow40 * fTemp0) + (fSlow41 * fTemp1)) + (fSlow42 * fTemp2)) + (fSlow43 * fTemp3)) + (fSlow44 * fTemp4)) + (fSlow45 * fTemp5)) + (fSlow46 * fTemp6)) + (fSlow47 * fTemp7)));
			output6[i] = FAUSTFLOAT(((((((((fSlow48 * fTemp0) + (fSlow49 * fTemp1)) + (fSlow50 * fTemp2)) + (fSlow51 * fTemp3)) + (fSlow52 * fTemp4)) + (fSlow53 * fTemp5)) + (fSlow54 * fTemp6)) + (fSlow55 * fTemp7)));
			output7[i] = FAUSTFLOAT(((((((((fSlow56 * fTemp0) + (fSlow57 * fTemp1)) + (fSlow58 * fTemp2)) + (fSlow59 * fTemp3)) + (fSlow60 * fTemp4)) + (fSlow61 * fTemp5)) + (fSlow62 * fTemp6)) + (fSlow63 * fTemp7)));
			
		}
		
	}

	
};

#endif
