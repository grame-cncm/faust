/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2006"
license: "BSD"
name: "matrix"
version: "1.0"
Code generated with Faust 2.87.10 (https://faust.grame.fr)
Compilation options: -a /Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/archs/impulsearch.cpp -lang cpp -i -fpga-mem-th 4 -ct 1 -es 1 -mcd 4 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs
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

#include <algorithm>
#include <cmath>
#include <cstdint>
#ifndef FAUST_INT_WRAP
#define FAUST_INT_WRAP
inline int faust_wrap_add(int a, int b) { return int((unsigned int)a + (unsigned int)b); }
inline int faust_wrap_sub(int a, int b) { return int((unsigned int)a - (unsigned int)b); }
inline int faust_wrap_mul(int a, int b) { return int((unsigned int)a * (unsigned int)b); }
#endif


#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
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
	int fSampleRate;
	
 public:
	mydsp() {
	}
	
	mydsp(const mydsp&) = default;
	
	virtual ~mydsp() = default;
	
	mydsp& operator=(const mydsp&) = default;
	
	void metadata(Meta* m) { 
		m->declare("author", "Grame");
		m->declare("compile_options", "-a /Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/archs/impulsearch.cpp -lang cpp -i -fpga-mem-th 4 -ct 1 -es 1 -mcd 4 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs");
		m->declare("copyright", "(c)GRAME 2006");
		m->declare("filename", "matrix.dsp");
		m->declare("license", "BSD");
		m->declare("math.lib/author", "GRAME");
		m->declare("math.lib/copyright", "GRAME");
		m->declare("math.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m->declare("math.lib/license", "LGPL with exception");
		m->declare("math.lib/name", "Math Library");
		m->declare("math.lib/version", "1.0");
		m->declare("music.lib/author", "GRAME");
		m->declare("music.lib/copyright", "GRAME");
		m->declare("music.lib/license", "LGPL with exception");
		m->declare("music.lib/name", "Music Library");
		m->declare("music.lib/version", "1.0");
		m->declare("name", "matrix");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() {
		return 8;
	}
	virtual int getNumOutputs() {
		return 8;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
	}
	
	virtual void instanceResetUserInterface() {
		fVslider0 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider1 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider2 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider3 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider4 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider5 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider6 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider7 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider8 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider9 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider10 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider11 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider12 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider13 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider14 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider15 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider16 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider17 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider18 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider19 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider20 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider21 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider22 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider23 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider24 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider25 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider26 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider27 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider28 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider29 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider30 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider31 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider32 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider33 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider34 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider35 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider36 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider37 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider38 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider39 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider40 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider41 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider42 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider43 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider44 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider45 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider46 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider47 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider48 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider49 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider50 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider51 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider52 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider53 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider54 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider55 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider56 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider57 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider58 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider59 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider60 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider61 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider62 = static_cast<FAUSTFLOAT>(-1e+01);
		fVslider63 = static_cast<FAUSTFLOAT>(-1e+01);
	}
	
	virtual void instanceClear() {
	}
	
	virtual void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	
	virtual void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual mydsp* clone() {
		return new mydsp(*this);
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openTabBox("Matrix 8 x 8");
		ui_interface->openHorizontalBox("Output 0");
		ui_interface->addVerticalSlider("Input 0", &fVslider0, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 1", &fVslider1, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 2", &fVslider2, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 3", &fVslider3, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 4", &fVslider4, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 5", &fVslider5, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 6", &fVslider6, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 7", &fVslider7, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Output 1");
		ui_interface->addVerticalSlider("Input 0", &fVslider8, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 1", &fVslider9, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 2", &fVslider10, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 3", &fVslider11, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 4", &fVslider12, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 5", &fVslider13, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 6", &fVslider14, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 7", &fVslider15, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Output 2");
		ui_interface->addVerticalSlider("Input 0", &fVslider16, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 1", &fVslider17, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 2", &fVslider18, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 3", &fVslider19, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 4", &fVslider20, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 5", &fVslider21, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 6", &fVslider22, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 7", &fVslider23, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Output 3");
		ui_interface->addVerticalSlider("Input 0", &fVslider24, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 1", &fVslider25, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 2", &fVslider26, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 3", &fVslider27, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 4", &fVslider28, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 5", &fVslider29, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 6", &fVslider30, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 7", &fVslider31, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Output 4");
		ui_interface->addVerticalSlider("Input 0", &fVslider32, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 1", &fVslider33, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 2", &fVslider34, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 3", &fVslider35, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 4", &fVslider36, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 5", &fVslider37, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 6", &fVslider38, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 7", &fVslider39, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Output 5");
		ui_interface->addVerticalSlider("Input 0", &fVslider40, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 1", &fVslider41, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 2", &fVslider42, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 3", &fVslider43, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 4", &fVslider44, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 5", &fVslider45, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 6", &fVslider46, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 7", &fVslider47, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Output 6");
		ui_interface->addVerticalSlider("Input 0", &fVslider48, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 1", &fVslider49, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 2", &fVslider50, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 3", &fVslider51, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 4", &fVslider52, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 5", &fVslider53, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 6", &fVslider54, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 7", &fVslider55, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Output 7");
		ui_interface->addVerticalSlider("Input 0", &fVslider56, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 1", &fVslider57, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 2", &fVslider58, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 3", &fVslider59, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 4", &fVslider60, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 5", &fVslider61, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 6", &fVslider62, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("Input 7", &fVslider63, FAUSTFLOAT(-1e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(4.0), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0_ptr = inputs[0];
		FAUSTFLOAT* input1_ptr = inputs[1];
		FAUSTFLOAT* input2_ptr = inputs[2];
		FAUSTFLOAT* input3_ptr = inputs[3];
		FAUSTFLOAT* input4_ptr = inputs[4];
		FAUSTFLOAT* input5_ptr = inputs[5];
		FAUSTFLOAT* input6_ptr = inputs[6];
		FAUSTFLOAT* input7_ptr = inputs[7];
		FAUSTFLOAT* output0_ptr = outputs[0];
		FAUSTFLOAT* output1_ptr = outputs[1];
		FAUSTFLOAT* output2_ptr = outputs[2];
		FAUSTFLOAT* output3_ptr = outputs[3];
		FAUSTFLOAT* output4_ptr = outputs[4];
		FAUSTFLOAT* output5_ptr = outputs[5];
		FAUSTFLOAT* output6_ptr = outputs[6];
		FAUSTFLOAT* output7_ptr = outputs[7];
		double fSlow0 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider0));
		double fSlow1 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider1));
		double fSlow2 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider2));
		double fSlow3 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider3));
		double fSlow4 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider4));
		double fSlow5 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider5));
		double fSlow6 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider6));
		double fSlow7 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider7));
		double fSlow8 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider8));
		double fSlow9 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider9));
		double fSlow10 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider10));
		double fSlow11 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider11));
		double fSlow12 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider12));
		double fSlow13 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider13));
		double fSlow14 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider14));
		double fSlow15 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider15));
		double fSlow16 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider16));
		double fSlow17 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider17));
		double fSlow18 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider18));
		double fSlow19 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider19));
		double fSlow20 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider20));
		double fSlow21 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider21));
		double fSlow22 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider22));
		double fSlow23 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider23));
		double fSlow24 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider24));
		double fSlow25 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider25));
		double fSlow26 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider26));
		double fSlow27 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider27));
		double fSlow28 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider28));
		double fSlow29 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider29));
		double fSlow30 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider30));
		double fSlow31 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider31));
		double fSlow32 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider32));
		double fSlow33 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider33));
		double fSlow34 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider34));
		double fSlow35 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider35));
		double fSlow36 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider36));
		double fSlow37 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider37));
		double fSlow38 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider38));
		double fSlow39 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider39));
		double fSlow40 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider40));
		double fSlow41 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider41));
		double fSlow42 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider42));
		double fSlow43 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider43));
		double fSlow44 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider44));
		double fSlow45 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider45));
		double fSlow46 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider46));
		double fSlow47 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider47));
		double fSlow48 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider48));
		double fSlow49 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider49));
		double fSlow50 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider50));
		double fSlow51 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider51));
		double fSlow52 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider52));
		double fSlow53 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider53));
		double fSlow54 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider54));
		double fSlow55 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider55));
		double fSlow56 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider56));
		double fSlow57 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider57));
		double fSlow58 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider58));
		double fSlow59 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider59));
		double fSlow60 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider60));
		double fSlow61 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider61));
		double fSlow62 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider62));
		double fSlow63 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider63));
		int vindex = 0;
		/* Main loop */
		for (vindex = 0; vindex <= (faust_wrap_sub(count, 4)); vindex = faust_wrap_add(vindex, 4)) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* input1 = &input1_ptr[vindex];
			FAUSTFLOAT* input2 = &input2_ptr[vindex];
			FAUSTFLOAT* input3 = &input3_ptr[vindex];
			FAUSTFLOAT* input4 = &input4_ptr[vindex];
			FAUSTFLOAT* input5 = &input5_ptr[vindex];
			FAUSTFLOAT* input6 = &input6_ptr[vindex];
			FAUSTFLOAT* input7 = &input7_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			FAUSTFLOAT* output1 = &output1_ptr[vindex];
			FAUSTFLOAT* output2 = &output2_ptr[vindex];
			FAUSTFLOAT* output3 = &output3_ptr[vindex];
			FAUSTFLOAT* output4 = &output4_ptr[vindex];
			FAUSTFLOAT* output5 = &output5_ptr[vindex];
			FAUSTFLOAT* output6 = &output6_ptr[vindex];
			FAUSTFLOAT* output7 = &output7_ptr[vindex];
			int vsize = 4;
			/* Vectorizable loop 0 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fSlow0 * static_cast<double>(input0[i]) + fSlow1 * static_cast<double>(input1[i]) + fSlow2 * static_cast<double>(input2[i]) + fSlow3 * static_cast<double>(input3[i]) + fSlow4 * static_cast<double>(input4[i]) + fSlow5 * static_cast<double>(input5[i]) + fSlow6 * static_cast<double>(input6[i]) + fSlow7 * static_cast<double>(input7[i]));
			}
			/* Vectorizable loop 1 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fSlow8 * static_cast<double>(input0[i]) + fSlow9 * static_cast<double>(input1[i]) + fSlow10 * static_cast<double>(input2[i]) + fSlow11 * static_cast<double>(input3[i]) + fSlow12 * static_cast<double>(input4[i]) + fSlow13 * static_cast<double>(input5[i]) + fSlow14 * static_cast<double>(input6[i]) + fSlow15 * static_cast<double>(input7[i]));
			}
			/* Vectorizable loop 2 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output2[i] = static_cast<FAUSTFLOAT>(fSlow16 * static_cast<double>(input0[i]) + fSlow17 * static_cast<double>(input1[i]) + fSlow18 * static_cast<double>(input2[i]) + fSlow19 * static_cast<double>(input3[i]) + fSlow20 * static_cast<double>(input4[i]) + fSlow21 * static_cast<double>(input5[i]) + fSlow22 * static_cast<double>(input6[i]) + fSlow23 * static_cast<double>(input7[i]));
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output3[i] = static_cast<FAUSTFLOAT>(fSlow24 * static_cast<double>(input0[i]) + fSlow25 * static_cast<double>(input1[i]) + fSlow26 * static_cast<double>(input2[i]) + fSlow27 * static_cast<double>(input3[i]) + fSlow28 * static_cast<double>(input4[i]) + fSlow29 * static_cast<double>(input5[i]) + fSlow30 * static_cast<double>(input6[i]) + fSlow31 * static_cast<double>(input7[i]));
			}
			/* Vectorizable loop 4 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output4[i] = static_cast<FAUSTFLOAT>(fSlow32 * static_cast<double>(input0[i]) + fSlow33 * static_cast<double>(input1[i]) + fSlow34 * static_cast<double>(input2[i]) + fSlow35 * static_cast<double>(input3[i]) + fSlow36 * static_cast<double>(input4[i]) + fSlow37 * static_cast<double>(input5[i]) + fSlow38 * static_cast<double>(input6[i]) + fSlow39 * static_cast<double>(input7[i]));
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output5[i] = static_cast<FAUSTFLOAT>(fSlow40 * static_cast<double>(input0[i]) + fSlow41 * static_cast<double>(input1[i]) + fSlow42 * static_cast<double>(input2[i]) + fSlow43 * static_cast<double>(input3[i]) + fSlow44 * static_cast<double>(input4[i]) + fSlow45 * static_cast<double>(input5[i]) + fSlow46 * static_cast<double>(input6[i]) + fSlow47 * static_cast<double>(input7[i]));
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output6[i] = static_cast<FAUSTFLOAT>(fSlow48 * static_cast<double>(input0[i]) + fSlow49 * static_cast<double>(input1[i]) + fSlow50 * static_cast<double>(input2[i]) + fSlow51 * static_cast<double>(input3[i]) + fSlow52 * static_cast<double>(input4[i]) + fSlow53 * static_cast<double>(input5[i]) + fSlow54 * static_cast<double>(input6[i]) + fSlow55 * static_cast<double>(input7[i]));
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output7[i] = static_cast<FAUSTFLOAT>(fSlow56 * static_cast<double>(input0[i]) + fSlow57 * static_cast<double>(input1[i]) + fSlow58 * static_cast<double>(input2[i]) + fSlow59 * static_cast<double>(input3[i]) + fSlow60 * static_cast<double>(input4[i]) + fSlow61 * static_cast<double>(input5[i]) + fSlow62 * static_cast<double>(input6[i]) + fSlow63 * static_cast<double>(input7[i]));
			}
		}
		/* Remaining frames */
		if (vindex < count) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* input1 = &input1_ptr[vindex];
			FAUSTFLOAT* input2 = &input2_ptr[vindex];
			FAUSTFLOAT* input3 = &input3_ptr[vindex];
			FAUSTFLOAT* input4 = &input4_ptr[vindex];
			FAUSTFLOAT* input5 = &input5_ptr[vindex];
			FAUSTFLOAT* input6 = &input6_ptr[vindex];
			FAUSTFLOAT* input7 = &input7_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			FAUSTFLOAT* output1 = &output1_ptr[vindex];
			FAUSTFLOAT* output2 = &output2_ptr[vindex];
			FAUSTFLOAT* output3 = &output3_ptr[vindex];
			FAUSTFLOAT* output4 = &output4_ptr[vindex];
			FAUSTFLOAT* output5 = &output5_ptr[vindex];
			FAUSTFLOAT* output6 = &output6_ptr[vindex];
			FAUSTFLOAT* output7 = &output7_ptr[vindex];
			int vsize = faust_wrap_sub(count, vindex);
			/* Vectorizable loop 0 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fSlow0 * static_cast<double>(input0[i]) + fSlow1 * static_cast<double>(input1[i]) + fSlow2 * static_cast<double>(input2[i]) + fSlow3 * static_cast<double>(input3[i]) + fSlow4 * static_cast<double>(input4[i]) + fSlow5 * static_cast<double>(input5[i]) + fSlow6 * static_cast<double>(input6[i]) + fSlow7 * static_cast<double>(input7[i]));
			}
			/* Vectorizable loop 1 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fSlow8 * static_cast<double>(input0[i]) + fSlow9 * static_cast<double>(input1[i]) + fSlow10 * static_cast<double>(input2[i]) + fSlow11 * static_cast<double>(input3[i]) + fSlow12 * static_cast<double>(input4[i]) + fSlow13 * static_cast<double>(input5[i]) + fSlow14 * static_cast<double>(input6[i]) + fSlow15 * static_cast<double>(input7[i]));
			}
			/* Vectorizable loop 2 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output2[i] = static_cast<FAUSTFLOAT>(fSlow16 * static_cast<double>(input0[i]) + fSlow17 * static_cast<double>(input1[i]) + fSlow18 * static_cast<double>(input2[i]) + fSlow19 * static_cast<double>(input3[i]) + fSlow20 * static_cast<double>(input4[i]) + fSlow21 * static_cast<double>(input5[i]) + fSlow22 * static_cast<double>(input6[i]) + fSlow23 * static_cast<double>(input7[i]));
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output3[i] = static_cast<FAUSTFLOAT>(fSlow24 * static_cast<double>(input0[i]) + fSlow25 * static_cast<double>(input1[i]) + fSlow26 * static_cast<double>(input2[i]) + fSlow27 * static_cast<double>(input3[i]) + fSlow28 * static_cast<double>(input4[i]) + fSlow29 * static_cast<double>(input5[i]) + fSlow30 * static_cast<double>(input6[i]) + fSlow31 * static_cast<double>(input7[i]));
			}
			/* Vectorizable loop 4 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output4[i] = static_cast<FAUSTFLOAT>(fSlow32 * static_cast<double>(input0[i]) + fSlow33 * static_cast<double>(input1[i]) + fSlow34 * static_cast<double>(input2[i]) + fSlow35 * static_cast<double>(input3[i]) + fSlow36 * static_cast<double>(input4[i]) + fSlow37 * static_cast<double>(input5[i]) + fSlow38 * static_cast<double>(input6[i]) + fSlow39 * static_cast<double>(input7[i]));
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output5[i] = static_cast<FAUSTFLOAT>(fSlow40 * static_cast<double>(input0[i]) + fSlow41 * static_cast<double>(input1[i]) + fSlow42 * static_cast<double>(input2[i]) + fSlow43 * static_cast<double>(input3[i]) + fSlow44 * static_cast<double>(input4[i]) + fSlow45 * static_cast<double>(input5[i]) + fSlow46 * static_cast<double>(input6[i]) + fSlow47 * static_cast<double>(input7[i]));
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output6[i] = static_cast<FAUSTFLOAT>(fSlow48 * static_cast<double>(input0[i]) + fSlow49 * static_cast<double>(input1[i]) + fSlow50 * static_cast<double>(input2[i]) + fSlow51 * static_cast<double>(input3[i]) + fSlow52 * static_cast<double>(input4[i]) + fSlow53 * static_cast<double>(input5[i]) + fSlow54 * static_cast<double>(input6[i]) + fSlow55 * static_cast<double>(input7[i]));
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output7[i] = static_cast<FAUSTFLOAT>(fSlow56 * static_cast<double>(input0[i]) + fSlow57 * static_cast<double>(input1[i]) + fSlow58 * static_cast<double>(input2[i]) + fSlow59 * static_cast<double>(input3[i]) + fSlow60 * static_cast<double>(input4[i]) + fSlow61 * static_cast<double>(input5[i]) + fSlow62 * static_cast<double>(input6[i]) + fSlow63 * static_cast<double>(input7[i]));
			}
		}
	}

};

int main(int argc, char* argv[])
{
    int linenum = 0;
    int nbsamples = 60000;
    
    // print general informations
    printHeader(new mydsp(), nbsamples);
    
    // linenum is incremented in runDSP and runPolyDSP
    runDSP(new mydsp(), argv[0], linenum, nbsamples/4);
    runDSP(new mydsp(), argv[0], linenum, nbsamples/4, false, true);
    runPolyDSP(new mydsp(), linenum, nbsamples/4, 4);
    runPolyDSP(new mydsp(), linenum, nbsamples/4, 1);
    
    return 0;
}

#endif
