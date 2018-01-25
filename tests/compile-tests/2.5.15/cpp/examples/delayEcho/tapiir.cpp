/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2006"
license: "BSD"
name: "tapiir"
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
	int IOTA;
	float fVec0[1048576];
	int fSamplingFreq;
	float fConst0;
	FAUSTFLOAT fVslider11;
	float fRec0[2];
	FAUSTFLOAT fVslider12;
	FAUSTFLOAT fVslider13;
	FAUSTFLOAT fVslider14;
	FAUSTFLOAT fVslider15;
	FAUSTFLOAT fVslider16;
	FAUSTFLOAT fVslider17;
	FAUSTFLOAT fVslider18;
	FAUSTFLOAT fVslider19;
	FAUSTFLOAT fVslider20;
	float fVec1[1048576];
	FAUSTFLOAT fVslider21;
	float fRec1[2];
	FAUSTFLOAT fVslider22;
	FAUSTFLOAT fVslider23;
	FAUSTFLOAT fVslider24;
	FAUSTFLOAT fVslider25;
	FAUSTFLOAT fVslider26;
	FAUSTFLOAT fVslider27;
	FAUSTFLOAT fVslider28;
	FAUSTFLOAT fVslider29;
	FAUSTFLOAT fVslider30;
	float fVec2[1048576];
	FAUSTFLOAT fVslider31;
	float fRec2[2];
	FAUSTFLOAT fVslider32;
	FAUSTFLOAT fVslider33;
	FAUSTFLOAT fVslider34;
	FAUSTFLOAT fVslider35;
	FAUSTFLOAT fVslider36;
	FAUSTFLOAT fVslider37;
	FAUSTFLOAT fVslider38;
	FAUSTFLOAT fVslider39;
	FAUSTFLOAT fVslider40;
	float fVec3[1048576];
	FAUSTFLOAT fVslider41;
	float fRec3[2];
	FAUSTFLOAT fVslider42;
	FAUSTFLOAT fVslider43;
	FAUSTFLOAT fVslider44;
	FAUSTFLOAT fVslider45;
	FAUSTFLOAT fVslider46;
	FAUSTFLOAT fVslider47;
	FAUSTFLOAT fVslider48;
	FAUSTFLOAT fVslider49;
	FAUSTFLOAT fVslider50;
	float fVec4[1048576];
	FAUSTFLOAT fVslider51;
	float fRec4[2];
	FAUSTFLOAT fVslider52;
	FAUSTFLOAT fVslider53;
	FAUSTFLOAT fVslider54;
	FAUSTFLOAT fVslider55;
	FAUSTFLOAT fVslider56;
	FAUSTFLOAT fVslider57;
	FAUSTFLOAT fVslider58;
	FAUSTFLOAT fVslider59;
	FAUSTFLOAT fVslider60;
	float fVec5[1048576];
	FAUSTFLOAT fVslider61;
	float fRec5[2];
	FAUSTFLOAT fVslider62;
	FAUSTFLOAT fVslider63;
	FAUSTFLOAT fVslider64;
	FAUSTFLOAT fVslider65;
	FAUSTFLOAT fVslider66;
	FAUSTFLOAT fVslider67;
	FAUSTFLOAT fVslider68;
	FAUSTFLOAT fVslider69;
	FAUSTFLOAT fVslider70;
	FAUSTFLOAT fVslider71;
	FAUSTFLOAT fVslider72;
	FAUSTFLOAT fVslider73;
	FAUSTFLOAT fVslider74;
	FAUSTFLOAT fVslider75;
	FAUSTFLOAT fVslider76;
	FAUSTFLOAT fVslider77;
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("author", "Grame");
		m->declare("copyright", "(c)GRAME 2006");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("license", "BSD");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "tapiir");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() {
		return 2;
		
	}
	virtual int getNumOutputs() {
		return 2;
		
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
		
	}
	
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(192000.0f, max(1.0f, float(fSamplingFreq)));
		
	}
	
	virtual void instanceResetUserInterface() {
		fVslider0 = FAUSTFLOAT(1.0f);
		fVslider1 = FAUSTFLOAT(0.0f);
		fVslider2 = FAUSTFLOAT(1.0f);
		fVslider3 = FAUSTFLOAT(0.0f);
		fVslider4 = FAUSTFLOAT(0.0f);
		fVslider5 = FAUSTFLOAT(0.0f);
		fVslider6 = FAUSTFLOAT(0.0f);
		fVslider7 = FAUSTFLOAT(0.0f);
		fVslider8 = FAUSTFLOAT(0.0f);
		fVslider9 = FAUSTFLOAT(1.0f);
		fVslider10 = FAUSTFLOAT(1.0f);
		fVslider11 = FAUSTFLOAT(0.0f);
		fVslider12 = FAUSTFLOAT(1.0f);
		fVslider13 = FAUSTFLOAT(0.0f);
		fVslider14 = FAUSTFLOAT(0.0f);
		fVslider15 = FAUSTFLOAT(0.0f);
		fVslider16 = FAUSTFLOAT(0.0f);
		fVslider17 = FAUSTFLOAT(0.0f);
		fVslider18 = FAUSTFLOAT(0.0f);
		fVslider19 = FAUSTFLOAT(1.0f);
		fVslider20 = FAUSTFLOAT(1.0f);
		fVslider21 = FAUSTFLOAT(0.0f);
		fVslider22 = FAUSTFLOAT(1.0f);
		fVslider23 = FAUSTFLOAT(0.0f);
		fVslider24 = FAUSTFLOAT(0.0f);
		fVslider25 = FAUSTFLOAT(0.0f);
		fVslider26 = FAUSTFLOAT(0.0f);
		fVslider27 = FAUSTFLOAT(0.0f);
		fVslider28 = FAUSTFLOAT(0.0f);
		fVslider29 = FAUSTFLOAT(1.0f);
		fVslider30 = FAUSTFLOAT(1.0f);
		fVslider31 = FAUSTFLOAT(0.0f);
		fVslider32 = FAUSTFLOAT(1.0f);
		fVslider33 = FAUSTFLOAT(0.0f);
		fVslider34 = FAUSTFLOAT(0.0f);
		fVslider35 = FAUSTFLOAT(0.0f);
		fVslider36 = FAUSTFLOAT(0.0f);
		fVslider37 = FAUSTFLOAT(0.0f);
		fVslider38 = FAUSTFLOAT(0.0f);
		fVslider39 = FAUSTFLOAT(1.0f);
		fVslider40 = FAUSTFLOAT(1.0f);
		fVslider41 = FAUSTFLOAT(0.0f);
		fVslider42 = FAUSTFLOAT(1.0f);
		fVslider43 = FAUSTFLOAT(0.0f);
		fVslider44 = FAUSTFLOAT(0.0f);
		fVslider45 = FAUSTFLOAT(0.0f);
		fVslider46 = FAUSTFLOAT(0.0f);
		fVslider47 = FAUSTFLOAT(0.0f);
		fVslider48 = FAUSTFLOAT(0.0f);
		fVslider49 = FAUSTFLOAT(1.0f);
		fVslider50 = FAUSTFLOAT(1.0f);
		fVslider51 = FAUSTFLOAT(0.0f);
		fVslider52 = FAUSTFLOAT(1.0f);
		fVslider53 = FAUSTFLOAT(0.0f);
		fVslider54 = FAUSTFLOAT(0.0f);
		fVslider55 = FAUSTFLOAT(0.0f);
		fVslider56 = FAUSTFLOAT(0.0f);
		fVslider57 = FAUSTFLOAT(0.0f);
		fVslider58 = FAUSTFLOAT(0.0f);
		fVslider59 = FAUSTFLOAT(1.0f);
		fVslider60 = FAUSTFLOAT(1.0f);
		fVslider61 = FAUSTFLOAT(0.0f);
		fVslider62 = FAUSTFLOAT(0.0f);
		fVslider63 = FAUSTFLOAT(0.0f);
		fVslider64 = FAUSTFLOAT(0.0f);
		fVslider65 = FAUSTFLOAT(0.0f);
		fVslider66 = FAUSTFLOAT(0.0f);
		fVslider67 = FAUSTFLOAT(1.0f);
		fVslider68 = FAUSTFLOAT(1.0f);
		fVslider69 = FAUSTFLOAT(1.0f);
		fVslider70 = FAUSTFLOAT(0.0f);
		fVslider71 = FAUSTFLOAT(0.0f);
		fVslider72 = FAUSTFLOAT(0.0f);
		fVslider73 = FAUSTFLOAT(0.0f);
		fVslider74 = FAUSTFLOAT(0.0f);
		fVslider75 = FAUSTFLOAT(0.0f);
		fVslider76 = FAUSTFLOAT(1.0f);
		fVslider77 = FAUSTFLOAT(1.0f);
		
	}
	
	virtual void instanceClear() {
		IOTA = 0;
		for (int l0 = 0; (l0 < 1048576); l0 = (l0 + 1)) {
			fVec0[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec0[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 1048576); l2 = (l2 + 1)) {
			fVec1[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec1[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 1048576); l4 = (l4 + 1)) {
			fVec2[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec2[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 1048576); l6 = (l6 + 1)) {
			fVec3[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec3[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 1048576); l8 = (l8 + 1)) {
			fVec4[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec4[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 1048576); l10 = (l10 + 1)) {
			fVec5[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec5[l11] = 0.0f;
			
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
		ui_interface->openVerticalBox("Tapiir");
		ui_interface->openTabBox("0x00");
		ui_interface->openHorizontalBox("Tap 0");
		ui_interface->addVerticalSlider("delay (sec)", &fVslider11, 0.0f, 0.0f, 5.0f, 0.00999999978f);
		ui_interface->addVerticalSlider("gain", &fVslider2, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("input 0", &fVslider9, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("input 1", &fVslider10, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 0", &fVslider3, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 1", &fVslider4, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 2", &fVslider5, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 3", &fVslider6, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 4", &fVslider7, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 5", &fVslider8, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Tap 1");
		ui_interface->addVerticalSlider("delay (sec)", &fVslider21, 0.0f, 0.0f, 5.0f, 0.00999999978f);
		ui_interface->addVerticalSlider("gain", &fVslider12, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("input 0", &fVslider19, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("input 1", &fVslider20, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 0", &fVslider13, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 1", &fVslider14, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 2", &fVslider15, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 3", &fVslider16, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 4", &fVslider17, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 5", &fVslider18, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Tap 2");
		ui_interface->addVerticalSlider("delay (sec)", &fVslider31, 0.0f, 0.0f, 5.0f, 0.00999999978f);
		ui_interface->addVerticalSlider("gain", &fVslider22, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("input 0", &fVslider29, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("input 1", &fVslider30, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 0", &fVslider23, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 1", &fVslider24, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 2", &fVslider25, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 3", &fVslider26, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 4", &fVslider27, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 5", &fVslider28, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Tap 3");
		ui_interface->addVerticalSlider("delay (sec)", &fVslider41, 0.0f, 0.0f, 5.0f, 0.00999999978f);
		ui_interface->addVerticalSlider("gain", &fVslider32, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("input 0", &fVslider39, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("input 1", &fVslider40, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 0", &fVslider33, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 1", &fVslider34, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 2", &fVslider35, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 3", &fVslider36, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 4", &fVslider37, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 5", &fVslider38, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Tap 4");
		ui_interface->addVerticalSlider("delay (sec)", &fVslider51, 0.0f, 0.0f, 5.0f, 0.00999999978f);
		ui_interface->addVerticalSlider("gain", &fVslider42, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("input 0", &fVslider49, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("input 1", &fVslider50, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 0", &fVslider43, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 1", &fVslider44, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 2", &fVslider45, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 3", &fVslider46, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 4", &fVslider47, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 5", &fVslider48, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Tap 5");
		ui_interface->addVerticalSlider("delay (sec)", &fVslider61, 0.0f, 0.0f, 5.0f, 0.00999999978f);
		ui_interface->addVerticalSlider("gain", &fVslider52, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("input 0", &fVslider59, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("input 1", &fVslider60, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 0", &fVslider53, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 1", &fVslider54, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 2", &fVslider55, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 3", &fVslider56, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 4", &fVslider57, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 5", &fVslider58, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("outputs");
		ui_interface->openHorizontalBox("output 0");
		ui_interface->addVerticalSlider("gain", &fVslider0, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("input 0", &fVslider67, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("input 1", &fVslider68, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 0", &fVslider1, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 1", &fVslider62, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 2", &fVslider63, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 3", &fVslider64, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 4", &fVslider65, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 5", &fVslider66, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("output 1");
		ui_interface->addVerticalSlider("gain", &fVslider69, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("input 0", &fVslider76, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("input 1", &fVslider77, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 0", &fVslider70, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 1", &fVslider71, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 2", &fVslider72, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 3", &fVslider73, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 4", &fVslider74, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->addVerticalSlider("tap 5", &fVslider75, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = float(fVslider0);
		float fSlow1 = float(fVslider1);
		float fSlow2 = float(fVslider2);
		float fSlow3 = float(fVslider3);
		float fSlow4 = float(fVslider4);
		float fSlow5 = float(fVslider5);
		float fSlow6 = float(fVslider6);
		float fSlow7 = float(fVslider7);
		float fSlow8 = float(fVslider8);
		float fSlow9 = float(fVslider9);
		float fSlow10 = float(fVslider10);
		int iSlow11 = int(min(524288.0f, max(0.0f, (fConst0 * float(fVslider11)))));
		float fSlow12 = float(fVslider12);
		float fSlow13 = float(fVslider13);
		float fSlow14 = float(fVslider14);
		float fSlow15 = float(fVslider15);
		float fSlow16 = float(fVslider16);
		float fSlow17 = float(fVslider17);
		float fSlow18 = float(fVslider18);
		float fSlow19 = float(fVslider19);
		float fSlow20 = float(fVslider20);
		int iSlow21 = int(min(524288.0f, max(0.0f, (fConst0 * float(fVslider21)))));
		float fSlow22 = float(fVslider22);
		float fSlow23 = float(fVslider23);
		float fSlow24 = float(fVslider24);
		float fSlow25 = float(fVslider25);
		float fSlow26 = float(fVslider26);
		float fSlow27 = float(fVslider27);
		float fSlow28 = float(fVslider28);
		float fSlow29 = float(fVslider29);
		float fSlow30 = float(fVslider30);
		int iSlow31 = int(min(524288.0f, max(0.0f, (fConst0 * float(fVslider31)))));
		float fSlow32 = float(fVslider32);
		float fSlow33 = float(fVslider33);
		float fSlow34 = float(fVslider34);
		float fSlow35 = float(fVslider35);
		float fSlow36 = float(fVslider36);
		float fSlow37 = float(fVslider37);
		float fSlow38 = float(fVslider38);
		float fSlow39 = float(fVslider39);
		float fSlow40 = float(fVslider40);
		int iSlow41 = int(min(524288.0f, max(0.0f, (fConst0 * float(fVslider41)))));
		float fSlow42 = float(fVslider42);
		float fSlow43 = float(fVslider43);
		float fSlow44 = float(fVslider44);
		float fSlow45 = float(fVslider45);
		float fSlow46 = float(fVslider46);
		float fSlow47 = float(fVslider47);
		float fSlow48 = float(fVslider48);
		float fSlow49 = float(fVslider49);
		float fSlow50 = float(fVslider50);
		int iSlow51 = int(min(524288.0f, max(0.0f, (fConst0 * float(fVslider51)))));
		float fSlow52 = float(fVslider52);
		float fSlow53 = float(fVslider53);
		float fSlow54 = float(fVslider54);
		float fSlow55 = float(fVslider55);
		float fSlow56 = float(fVslider56);
		float fSlow57 = float(fVslider57);
		float fSlow58 = float(fVslider58);
		float fSlow59 = float(fVslider59);
		float fSlow60 = float(fVslider60);
		int iSlow61 = int(min(524288.0f, max(0.0f, (fConst0 * float(fVslider61)))));
		float fSlow62 = float(fVslider62);
		float fSlow63 = float(fVslider63);
		float fSlow64 = float(fVslider64);
		float fSlow65 = float(fVslider65);
		float fSlow66 = float(fVslider66);
		float fSlow67 = float(fVslider67);
		float fSlow68 = float(fVslider68);
		float fSlow69 = float(fVslider69);
		float fSlow70 = float(fVslider70);
		float fSlow71 = float(fVslider71);
		float fSlow72 = float(fVslider72);
		float fSlow73 = float(fVslider73);
		float fSlow74 = float(fVslider74);
		float fSlow75 = float(fVslider75);
		float fSlow76 = float(fVslider76);
		float fSlow77 = float(fVslider77);
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input0[i]);
			float fTemp1 = float(input1[i]);
			fVec0[(IOTA & 1048575)] = (fSlow2 * ((((((((fSlow3 * fRec0[1]) + (fSlow4 * fRec1[1])) + (fSlow5 * fRec2[1])) + (fSlow6 * fRec3[1])) + (fSlow7 * fRec4[1])) + (fSlow8 * fRec5[1])) + (fSlow9 * fTemp0)) + (fSlow10 * fTemp1)));
			fRec0[0] = fVec0[((IOTA - iSlow11) & 1048575)];
			fVec1[(IOTA & 1048575)] = (fSlow12 * ((((((((fSlow13 * fRec0[1]) + (fSlow14 * fRec1[1])) + (fSlow15 * fRec2[1])) + (fSlow16 * fRec3[1])) + (fSlow17 * fRec4[1])) + (fSlow18 * fRec5[1])) + (fSlow19 * fTemp0)) + (fSlow20 * fTemp1)));
			fRec1[0] = fVec1[((IOTA - iSlow21) & 1048575)];
			fVec2[(IOTA & 1048575)] = (fSlow22 * ((((((((fSlow23 * fRec0[1]) + (fSlow24 * fRec1[1])) + (fSlow25 * fRec2[1])) + (fSlow26 * fRec3[1])) + (fSlow27 * fRec4[1])) + (fSlow28 * fRec5[1])) + (fSlow29 * fTemp0)) + (fSlow30 * fTemp1)));
			fRec2[0] = fVec2[((IOTA - iSlow31) & 1048575)];
			fVec3[(IOTA & 1048575)] = (fSlow32 * ((((((((fSlow33 * fRec0[1]) + (fSlow34 * fRec1[1])) + (fSlow35 * fRec2[1])) + (fSlow36 * fRec3[1])) + (fSlow37 * fRec4[1])) + (fSlow38 * fRec5[1])) + (fSlow39 * fTemp0)) + (fSlow40 * fTemp1)));
			fRec3[0] = fVec3[((IOTA - iSlow41) & 1048575)];
			fVec4[(IOTA & 1048575)] = (fSlow42 * ((((((((fSlow43 * fRec0[1]) + (fSlow44 * fRec1[1])) + (fSlow45 * fRec2[1])) + (fSlow46 * fRec3[1])) + (fSlow47 * fRec4[1])) + (fSlow48 * fRec5[1])) + (fSlow49 * fTemp0)) + (fSlow50 * fTemp1)));
			fRec4[0] = fVec4[((IOTA - iSlow51) & 1048575)];
			fVec5[(IOTA & 1048575)] = (fSlow52 * ((((((((fSlow53 * fRec0[1]) + (fSlow54 * fRec1[1])) + (fSlow55 * fRec2[1])) + (fSlow56 * fRec3[1])) + (fSlow57 * fRec4[1])) + (fSlow58 * fRec5[1])) + (fSlow59 * fTemp0)) + (fSlow60 * fTemp1)));
			fRec5[0] = fVec5[((IOTA - iSlow61) & 1048575)];
			output0[i] = FAUSTFLOAT((fSlow0 * ((((((((fSlow1 * fRec0[0]) + (fSlow62 * fRec1[0])) + (fSlow63 * fRec2[0])) + (fSlow64 * fRec3[0])) + (fSlow65 * fRec4[0])) + (fSlow66 * fRec5[0])) + (fSlow67 * fTemp0)) + (fSlow68 * fTemp1))));
			output1[i] = FAUSTFLOAT((fSlow69 * ((((((((fSlow70 * fRec0[0]) + (fSlow71 * fRec1[0])) + (fSlow72 * fRec2[0])) + (fSlow73 * fRec3[0])) + (fSlow74 * fRec4[0])) + (fSlow75 * fRec5[0])) + (fSlow76 * fTemp0)) + (fSlow77 * fTemp1))));
			IOTA = (IOTA + 1);
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			
		}
		
	}

	
};

#endif
