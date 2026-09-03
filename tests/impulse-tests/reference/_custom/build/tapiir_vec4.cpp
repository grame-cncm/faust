/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2006"
license: "BSD"
name: "tapiir"
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
#include <math.h>
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
	double fYec0[1048576];
	int fYec0_idx;
	int fYec0_idx_save;
	int fSampleRate;
	double fConst0;
	FAUSTFLOAT fVslider9;
	double fRec0_perm[4];
	FAUSTFLOAT fVslider10;
	FAUSTFLOAT fVslider11;
	FAUSTFLOAT fVslider12;
	FAUSTFLOAT fVslider13;
	FAUSTFLOAT fVslider14;
	FAUSTFLOAT fVslider15;
	FAUSTFLOAT fVslider16;
	FAUSTFLOAT fVslider17;
	FAUSTFLOAT fVslider18;
	double fYec1[1048576];
	int fYec1_idx;
	int fYec1_idx_save;
	FAUSTFLOAT fVslider19;
	double fRec1_perm[4];
	FAUSTFLOAT fVslider20;
	FAUSTFLOAT fVslider21;
	FAUSTFLOAT fVslider22;
	FAUSTFLOAT fVslider23;
	FAUSTFLOAT fVslider24;
	FAUSTFLOAT fVslider25;
	FAUSTFLOAT fVslider26;
	FAUSTFLOAT fVslider27;
	FAUSTFLOAT fVslider28;
	double fYec2[1048576];
	int fYec2_idx;
	int fYec2_idx_save;
	FAUSTFLOAT fVslider29;
	double fRec2_perm[4];
	FAUSTFLOAT fVslider30;
	FAUSTFLOAT fVslider31;
	FAUSTFLOAT fVslider32;
	FAUSTFLOAT fVslider33;
	FAUSTFLOAT fVslider34;
	FAUSTFLOAT fVslider35;
	FAUSTFLOAT fVslider36;
	FAUSTFLOAT fVslider37;
	FAUSTFLOAT fVslider38;
	double fYec3[1048576];
	int fYec3_idx;
	int fYec3_idx_save;
	FAUSTFLOAT fVslider39;
	double fRec3_perm[4];
	FAUSTFLOAT fVslider40;
	FAUSTFLOAT fVslider41;
	FAUSTFLOAT fVslider42;
	FAUSTFLOAT fVslider43;
	FAUSTFLOAT fVslider44;
	FAUSTFLOAT fVslider45;
	FAUSTFLOAT fVslider46;
	FAUSTFLOAT fVslider47;
	FAUSTFLOAT fVslider48;
	double fYec4[1048576];
	int fYec4_idx;
	int fYec4_idx_save;
	FAUSTFLOAT fVslider49;
	double fRec4_perm[4];
	FAUSTFLOAT fVslider50;
	FAUSTFLOAT fVslider51;
	FAUSTFLOAT fVslider52;
	FAUSTFLOAT fVslider53;
	FAUSTFLOAT fVslider54;
	FAUSTFLOAT fVslider55;
	FAUSTFLOAT fVslider56;
	FAUSTFLOAT fVslider57;
	FAUSTFLOAT fVslider58;
	double fYec5[1048576];
	int fYec5_idx;
	int fYec5_idx_save;
	FAUSTFLOAT fVslider59;
	double fRec5_perm[4];
	FAUSTFLOAT fVslider60;
	FAUSTFLOAT fVslider61;
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
	mydsp() {
	}
	
	mydsp(const mydsp&) = default;
	
	virtual ~mydsp() = default;
	
	mydsp& operator=(const mydsp&) = default;
	
	void metadata(Meta* m) { 
		m->declare("author", "Grame");
		m->declare("compile_options", "-a /Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/archs/impulsearch.cpp -lang cpp -i -fpga-mem-th 4 -ct 1 -es 1 -mcd 4 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs");
		m->declare("copyright", "(c)GRAME 2006");
		m->declare("filename", "tapiir.dsp");
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
		m->declare("name", "tapiir");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() {
		return 2;
	}
	virtual int getNumOutputs() {
		return 2;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, static_cast<double>(fSampleRate)));
	}
	
	virtual void instanceResetUserInterface() {
		fVslider0 = static_cast<FAUSTFLOAT>(1.0);
		fVslider1 = static_cast<FAUSTFLOAT>(0.0);
		fVslider2 = static_cast<FAUSTFLOAT>(0.0);
		fVslider3 = static_cast<FAUSTFLOAT>(0.0);
		fVslider4 = static_cast<FAUSTFLOAT>(0.0);
		fVslider5 = static_cast<FAUSTFLOAT>(0.0);
		fVslider6 = static_cast<FAUSTFLOAT>(0.0);
		fVslider7 = static_cast<FAUSTFLOAT>(1.0);
		fVslider8 = static_cast<FAUSTFLOAT>(1.0);
		fVslider9 = static_cast<FAUSTFLOAT>(0.0);
		fVslider10 = static_cast<FAUSTFLOAT>(1.0);
		fVslider11 = static_cast<FAUSTFLOAT>(0.0);
		fVslider12 = static_cast<FAUSTFLOAT>(0.0);
		fVslider13 = static_cast<FAUSTFLOAT>(0.0);
		fVslider14 = static_cast<FAUSTFLOAT>(0.0);
		fVslider15 = static_cast<FAUSTFLOAT>(0.0);
		fVslider16 = static_cast<FAUSTFLOAT>(0.0);
		fVslider17 = static_cast<FAUSTFLOAT>(1.0);
		fVslider18 = static_cast<FAUSTFLOAT>(1.0);
		fVslider19 = static_cast<FAUSTFLOAT>(0.0);
		fVslider20 = static_cast<FAUSTFLOAT>(1.0);
		fVslider21 = static_cast<FAUSTFLOAT>(0.0);
		fVslider22 = static_cast<FAUSTFLOAT>(0.0);
		fVslider23 = static_cast<FAUSTFLOAT>(0.0);
		fVslider24 = static_cast<FAUSTFLOAT>(0.0);
		fVslider25 = static_cast<FAUSTFLOAT>(0.0);
		fVslider26 = static_cast<FAUSTFLOAT>(0.0);
		fVslider27 = static_cast<FAUSTFLOAT>(1.0);
		fVslider28 = static_cast<FAUSTFLOAT>(1.0);
		fVslider29 = static_cast<FAUSTFLOAT>(0.0);
		fVslider30 = static_cast<FAUSTFLOAT>(1.0);
		fVslider31 = static_cast<FAUSTFLOAT>(0.0);
		fVslider32 = static_cast<FAUSTFLOAT>(0.0);
		fVslider33 = static_cast<FAUSTFLOAT>(0.0);
		fVslider34 = static_cast<FAUSTFLOAT>(0.0);
		fVslider35 = static_cast<FAUSTFLOAT>(0.0);
		fVslider36 = static_cast<FAUSTFLOAT>(0.0);
		fVslider37 = static_cast<FAUSTFLOAT>(1.0);
		fVslider38 = static_cast<FAUSTFLOAT>(1.0);
		fVslider39 = static_cast<FAUSTFLOAT>(0.0);
		fVslider40 = static_cast<FAUSTFLOAT>(1.0);
		fVslider41 = static_cast<FAUSTFLOAT>(0.0);
		fVslider42 = static_cast<FAUSTFLOAT>(0.0);
		fVslider43 = static_cast<FAUSTFLOAT>(0.0);
		fVslider44 = static_cast<FAUSTFLOAT>(0.0);
		fVslider45 = static_cast<FAUSTFLOAT>(0.0);
		fVslider46 = static_cast<FAUSTFLOAT>(0.0);
		fVslider47 = static_cast<FAUSTFLOAT>(1.0);
		fVslider48 = static_cast<FAUSTFLOAT>(1.0);
		fVslider49 = static_cast<FAUSTFLOAT>(0.0);
		fVslider50 = static_cast<FAUSTFLOAT>(1.0);
		fVslider51 = static_cast<FAUSTFLOAT>(0.0);
		fVslider52 = static_cast<FAUSTFLOAT>(0.0);
		fVslider53 = static_cast<FAUSTFLOAT>(0.0);
		fVslider54 = static_cast<FAUSTFLOAT>(0.0);
		fVslider55 = static_cast<FAUSTFLOAT>(0.0);
		fVslider56 = static_cast<FAUSTFLOAT>(0.0);
		fVslider57 = static_cast<FAUSTFLOAT>(1.0);
		fVslider58 = static_cast<FAUSTFLOAT>(1.0);
		fVslider59 = static_cast<FAUSTFLOAT>(0.0);
		fVslider60 = static_cast<FAUSTFLOAT>(1.0);
		fVslider61 = static_cast<FAUSTFLOAT>(0.0);
		fVslider62 = static_cast<FAUSTFLOAT>(0.0);
		fVslider63 = static_cast<FAUSTFLOAT>(0.0);
		fVslider64 = static_cast<FAUSTFLOAT>(0.0);
		fVslider65 = static_cast<FAUSTFLOAT>(0.0);
		fVslider66 = static_cast<FAUSTFLOAT>(0.0);
		fVslider67 = static_cast<FAUSTFLOAT>(1.0);
		fVslider68 = static_cast<FAUSTFLOAT>(1.0);
		fVslider69 = static_cast<FAUSTFLOAT>(1.0);
		fVslider70 = static_cast<FAUSTFLOAT>(0.0);
		fVslider71 = static_cast<FAUSTFLOAT>(0.0);
		fVslider72 = static_cast<FAUSTFLOAT>(0.0);
		fVslider73 = static_cast<FAUSTFLOAT>(0.0);
		fVslider74 = static_cast<FAUSTFLOAT>(0.0);
		fVslider75 = static_cast<FAUSTFLOAT>(0.0);
		fVslider76 = static_cast<FAUSTFLOAT>(1.0);
		fVslider77 = static_cast<FAUSTFLOAT>(1.0);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 1048576; l0 = faust_wrap_add(l0, 1)) {
			fYec0[l0] = 0.0;
		}
		fYec0_idx = 0;
		fYec0_idx_save = 0;
		for (int l1 = 0; l1 < 4; l1 = faust_wrap_add(l1, 1)) {
			fRec0_perm[l1] = 0.0;
		}
		for (int l2 = 0; l2 < 1048576; l2 = faust_wrap_add(l2, 1)) {
			fYec1[l2] = 0.0;
		}
		fYec1_idx = 0;
		fYec1_idx_save = 0;
		for (int l3 = 0; l3 < 4; l3 = faust_wrap_add(l3, 1)) {
			fRec1_perm[l3] = 0.0;
		}
		for (int l4 = 0; l4 < 1048576; l4 = faust_wrap_add(l4, 1)) {
			fYec2[l4] = 0.0;
		}
		fYec2_idx = 0;
		fYec2_idx_save = 0;
		for (int l5 = 0; l5 < 4; l5 = faust_wrap_add(l5, 1)) {
			fRec2_perm[l5] = 0.0;
		}
		for (int l6 = 0; l6 < 1048576; l6 = faust_wrap_add(l6, 1)) {
			fYec3[l6] = 0.0;
		}
		fYec3_idx = 0;
		fYec3_idx_save = 0;
		for (int l7 = 0; l7 < 4; l7 = faust_wrap_add(l7, 1)) {
			fRec3_perm[l7] = 0.0;
		}
		for (int l8 = 0; l8 < 1048576; l8 = faust_wrap_add(l8, 1)) {
			fYec4[l8] = 0.0;
		}
		fYec4_idx = 0;
		fYec4_idx_save = 0;
		for (int l9 = 0; l9 < 4; l9 = faust_wrap_add(l9, 1)) {
			fRec4_perm[l9] = 0.0;
		}
		for (int l10 = 0; l10 < 1048576; l10 = faust_wrap_add(l10, 1)) {
			fYec5[l10] = 0.0;
		}
		fYec5_idx = 0;
		fYec5_idx_save = 0;
		for (int l11 = 0; l11 < 4; l11 = faust_wrap_add(l11, 1)) {
			fRec5_perm[l11] = 0.0;
		}
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
		ui_interface->openVerticalBox("Tapiir");
		ui_interface->openTabBox("0x00");
		ui_interface->openHorizontalBox("Tap 0");
		ui_interface->addVerticalSlider("delay (sec)", &fVslider9, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(5.0), FAUSTFLOAT(0.01));
		ui_interface->addVerticalSlider("gain", &fVslider0, FAUSTFLOAT(1.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("input 0", &fVslider7, FAUSTFLOAT(1.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("input 1", &fVslider8, FAUSTFLOAT(1.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 0", &fVslider1, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 1", &fVslider2, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 2", &fVslider3, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 3", &fVslider4, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 4", &fVslider5, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 5", &fVslider6, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Tap 1");
		ui_interface->addVerticalSlider("delay (sec)", &fVslider19, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(5.0), FAUSTFLOAT(0.01));
		ui_interface->addVerticalSlider("gain", &fVslider10, FAUSTFLOAT(1.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("input 0", &fVslider17, FAUSTFLOAT(1.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("input 1", &fVslider18, FAUSTFLOAT(1.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 0", &fVslider11, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 1", &fVslider12, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 2", &fVslider13, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 3", &fVslider14, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 4", &fVslider15, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 5", &fVslider16, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Tap 2");
		ui_interface->addVerticalSlider("delay (sec)", &fVslider29, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(5.0), FAUSTFLOAT(0.01));
		ui_interface->addVerticalSlider("gain", &fVslider20, FAUSTFLOAT(1.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("input 0", &fVslider27, FAUSTFLOAT(1.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("input 1", &fVslider28, FAUSTFLOAT(1.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 0", &fVslider21, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 1", &fVslider22, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 2", &fVslider23, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 3", &fVslider24, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 4", &fVslider25, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 5", &fVslider26, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Tap 3");
		ui_interface->addVerticalSlider("delay (sec)", &fVslider39, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(5.0), FAUSTFLOAT(0.01));
		ui_interface->addVerticalSlider("gain", &fVslider30, FAUSTFLOAT(1.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("input 0", &fVslider37, FAUSTFLOAT(1.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("input 1", &fVslider38, FAUSTFLOAT(1.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 0", &fVslider31, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 1", &fVslider32, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 2", &fVslider33, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 3", &fVslider34, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 4", &fVslider35, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 5", &fVslider36, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Tap 4");
		ui_interface->addVerticalSlider("delay (sec)", &fVslider49, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(5.0), FAUSTFLOAT(0.01));
		ui_interface->addVerticalSlider("gain", &fVslider40, FAUSTFLOAT(1.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("input 0", &fVslider47, FAUSTFLOAT(1.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("input 1", &fVslider48, FAUSTFLOAT(1.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 0", &fVslider41, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 1", &fVslider42, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 2", &fVslider43, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 3", &fVslider44, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 4", &fVslider45, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 5", &fVslider46, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Tap 5");
		ui_interface->addVerticalSlider("delay (sec)", &fVslider59, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(5.0), FAUSTFLOAT(0.01));
		ui_interface->addVerticalSlider("gain", &fVslider50, FAUSTFLOAT(1.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("input 0", &fVslider57, FAUSTFLOAT(1.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("input 1", &fVslider58, FAUSTFLOAT(1.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 0", &fVslider51, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 1", &fVslider52, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 2", &fVslider53, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 3", &fVslider54, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 4", &fVslider55, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 5", &fVslider56, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("outputs");
		ui_interface->openHorizontalBox("output 0");
		ui_interface->addVerticalSlider("gain", &fVslider60, FAUSTFLOAT(1.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("input 0", &fVslider67, FAUSTFLOAT(1.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("input 1", &fVslider68, FAUSTFLOAT(1.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 0", &fVslider61, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 1", &fVslider62, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 2", &fVslider63, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 3", &fVslider64, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 4", &fVslider65, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 5", &fVslider66, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("output 1");
		ui_interface->addVerticalSlider("gain", &fVslider69, FAUSTFLOAT(1.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("input 0", &fVslider76, FAUSTFLOAT(1.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("input 1", &fVslider77, FAUSTFLOAT(1.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 0", &fVslider70, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 1", &fVslider71, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 2", &fVslider72, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 3", &fVslider73, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 4", &fVslider74, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("tap 5", &fVslider75, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0_ptr = inputs[0];
		FAUSTFLOAT* input1_ptr = inputs[1];
		FAUSTFLOAT* output0_ptr = outputs[0];
		FAUSTFLOAT* output1_ptr = outputs[1];
		double fSlow0 = static_cast<double>(fVslider0);
		double fSlow1 = static_cast<double>(fVslider1);
		double fSlow2 = static_cast<double>(fVslider2);
		double fSlow3 = static_cast<double>(fVslider3);
		double fSlow4 = static_cast<double>(fVslider4);
		double fSlow5 = static_cast<double>(fVslider5);
		double fSlow6 = static_cast<double>(fVslider6);
		double fSlow7 = static_cast<double>(fVslider7);
		double fSlow8 = static_cast<double>(fVslider8);
		int iSlow9 = static_cast<int>(fConst0 * static_cast<double>(fVslider9)) & 524287;
		double fRec0_tmp[8];
		double* fRec0 = &fRec0_tmp[4];
		double fSlow10 = static_cast<double>(fVslider10);
		double fSlow11 = static_cast<double>(fVslider11);
		double fSlow12 = static_cast<double>(fVslider12);
		double fSlow13 = static_cast<double>(fVslider13);
		double fSlow14 = static_cast<double>(fVslider14);
		double fSlow15 = static_cast<double>(fVslider15);
		double fSlow16 = static_cast<double>(fVslider16);
		double fSlow17 = static_cast<double>(fVslider17);
		double fSlow18 = static_cast<double>(fVslider18);
		int iSlow19 = static_cast<int>(fConst0 * static_cast<double>(fVslider19)) & 524287;
		double fRec1_tmp[8];
		double* fRec1 = &fRec1_tmp[4];
		double fSlow20 = static_cast<double>(fVslider20);
		double fSlow21 = static_cast<double>(fVslider21);
		double fSlow22 = static_cast<double>(fVslider22);
		double fSlow23 = static_cast<double>(fVslider23);
		double fSlow24 = static_cast<double>(fVslider24);
		double fSlow25 = static_cast<double>(fVslider25);
		double fSlow26 = static_cast<double>(fVslider26);
		double fSlow27 = static_cast<double>(fVslider27);
		double fSlow28 = static_cast<double>(fVslider28);
		int iSlow29 = static_cast<int>(fConst0 * static_cast<double>(fVslider29)) & 524287;
		double fRec2_tmp[8];
		double* fRec2 = &fRec2_tmp[4];
		double fSlow30 = static_cast<double>(fVslider30);
		double fSlow31 = static_cast<double>(fVslider31);
		double fSlow32 = static_cast<double>(fVslider32);
		double fSlow33 = static_cast<double>(fVslider33);
		double fSlow34 = static_cast<double>(fVslider34);
		double fSlow35 = static_cast<double>(fVslider35);
		double fSlow36 = static_cast<double>(fVslider36);
		double fSlow37 = static_cast<double>(fVslider37);
		double fSlow38 = static_cast<double>(fVslider38);
		int iSlow39 = static_cast<int>(fConst0 * static_cast<double>(fVslider39)) & 524287;
		double fRec3_tmp[8];
		double* fRec3 = &fRec3_tmp[4];
		double fSlow40 = static_cast<double>(fVslider40);
		double fSlow41 = static_cast<double>(fVslider41);
		double fSlow42 = static_cast<double>(fVslider42);
		double fSlow43 = static_cast<double>(fVslider43);
		double fSlow44 = static_cast<double>(fVslider44);
		double fSlow45 = static_cast<double>(fVslider45);
		double fSlow46 = static_cast<double>(fVslider46);
		double fSlow47 = static_cast<double>(fVslider47);
		double fSlow48 = static_cast<double>(fVslider48);
		int iSlow49 = static_cast<int>(fConst0 * static_cast<double>(fVslider49)) & 524287;
		double fRec4_tmp[8];
		double* fRec4 = &fRec4_tmp[4];
		double fSlow50 = static_cast<double>(fVslider50);
		double fSlow51 = static_cast<double>(fVslider51);
		double fSlow52 = static_cast<double>(fVslider52);
		double fSlow53 = static_cast<double>(fVslider53);
		double fSlow54 = static_cast<double>(fVslider54);
		double fSlow55 = static_cast<double>(fVslider55);
		double fSlow56 = static_cast<double>(fVslider56);
		double fSlow57 = static_cast<double>(fVslider57);
		double fSlow58 = static_cast<double>(fVslider58);
		int iSlow59 = static_cast<int>(fConst0 * static_cast<double>(fVslider59)) & 524287;
		double fRec5_tmp[8];
		double* fRec5 = &fRec5_tmp[4];
		double fSlow60 = static_cast<double>(fVslider60);
		double fSlow61 = static_cast<double>(fVslider61);
		double fSlow62 = static_cast<double>(fVslider62);
		double fSlow63 = static_cast<double>(fVslider63);
		double fSlow64 = static_cast<double>(fVslider64);
		double fSlow65 = static_cast<double>(fVslider65);
		double fSlow66 = static_cast<double>(fVslider66);
		double fSlow67 = static_cast<double>(fVslider67);
		double fSlow68 = static_cast<double>(fVslider68);
		double fSlow69 = static_cast<double>(fVslider69);
		double fSlow70 = static_cast<double>(fVslider70);
		double fSlow71 = static_cast<double>(fVslider71);
		double fSlow72 = static_cast<double>(fVslider72);
		double fSlow73 = static_cast<double>(fVslider73);
		double fSlow74 = static_cast<double>(fVslider74);
		double fSlow75 = static_cast<double>(fVslider75);
		double fSlow76 = static_cast<double>(fVslider76);
		double fSlow77 = static_cast<double>(fVslider77);
		int vindex = 0;
		/* Main loop */
		for (vindex = 0; vindex <= (faust_wrap_sub(count, 4)); vindex = faust_wrap_add(vindex, 4)) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* input1 = &input1_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			FAUSTFLOAT* output1 = &output1_ptr[vindex];
			int vsize = 4;
			/* Recursive loop 0 */
			/* Pre code */
			fYec0_idx = (faust_wrap_add(fYec0_idx, fYec0_idx_save)) & 1048575;
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				fRec0_tmp[j0] = fRec0_perm[j0];
			}
			fYec1_idx = (faust_wrap_add(fYec1_idx, fYec1_idx_save)) & 1048575;
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fRec1_tmp[j2] = fRec1_perm[j2];
			}
			fYec2_idx = (faust_wrap_add(fYec2_idx, fYec2_idx_save)) & 1048575;
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				fRec2_tmp[j4] = fRec2_perm[j4];
			}
			fYec3_idx = (faust_wrap_add(fYec3_idx, fYec3_idx_save)) & 1048575;
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec3_tmp[j6] = fRec3_perm[j6];
			}
			fYec4_idx = (faust_wrap_add(fYec4_idx, fYec4_idx_save)) & 1048575;
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fRec4_tmp[j8] = fRec4_perm[j8];
			}
			fYec5_idx = (faust_wrap_add(fYec5_idx, fYec5_idx_save)) & 1048575;
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				fRec5_tmp[j10] = fRec5_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec0[(faust_wrap_add(i, fYec0_idx)) & 1048575] = fSlow0 * (fSlow1 * fRec0[faust_wrap_sub(i, 1)] + fSlow2 * fRec1[faust_wrap_sub(i, 1)] + fSlow3 * fRec2[faust_wrap_sub(i, 1)] + fSlow4 * fRec3[faust_wrap_sub(i, 1)] + fSlow5 * fRec4[faust_wrap_sub(i, 1)] + fSlow6 * fRec5[faust_wrap_sub(i, 1)] + fSlow7 * static_cast<double>(input0[i]) + fSlow8 * static_cast<double>(input1[i]));
				fRec0[i] = fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), iSlow9)) & 1048575];
				fYec1[(faust_wrap_add(i, fYec1_idx)) & 1048575] = fSlow10 * (fSlow11 * fRec0[faust_wrap_sub(i, 1)] + fSlow12 * fRec1[faust_wrap_sub(i, 1)] + fSlow13 * fRec2[faust_wrap_sub(i, 1)] + fSlow14 * fRec3[faust_wrap_sub(i, 1)] + fSlow15 * fRec4[faust_wrap_sub(i, 1)] + fSlow16 * fRec5[faust_wrap_sub(i, 1)] + fSlow17 * static_cast<double>(input0[i]) + fSlow18 * static_cast<double>(input1[i]));
				fRec1[i] = fYec1[(faust_wrap_sub(faust_wrap_add(i, fYec1_idx), iSlow19)) & 1048575];
				fYec2[(faust_wrap_add(i, fYec2_idx)) & 1048575] = fSlow20 * (fSlow21 * fRec0[faust_wrap_sub(i, 1)] + fSlow22 * fRec1[faust_wrap_sub(i, 1)] + fSlow23 * fRec2[faust_wrap_sub(i, 1)] + fSlow24 * fRec3[faust_wrap_sub(i, 1)] + fSlow25 * fRec4[faust_wrap_sub(i, 1)] + fSlow26 * fRec5[faust_wrap_sub(i, 1)] + fSlow27 * static_cast<double>(input0[i]) + fSlow28 * static_cast<double>(input1[i]));
				fRec2[i] = fYec2[(faust_wrap_sub(faust_wrap_add(i, fYec2_idx), iSlow29)) & 1048575];
				fYec3[(faust_wrap_add(i, fYec3_idx)) & 1048575] = fSlow30 * (fSlow31 * fRec0[faust_wrap_sub(i, 1)] + fSlow32 * fRec1[faust_wrap_sub(i, 1)] + fSlow33 * fRec2[faust_wrap_sub(i, 1)] + fSlow34 * fRec3[faust_wrap_sub(i, 1)] + fSlow35 * fRec4[faust_wrap_sub(i, 1)] + fSlow36 * fRec5[faust_wrap_sub(i, 1)] + fSlow37 * static_cast<double>(input0[i]) + fSlow38 * static_cast<double>(input1[i]));
				fRec3[i] = fYec3[(faust_wrap_sub(faust_wrap_add(i, fYec3_idx), iSlow39)) & 1048575];
				fYec4[(faust_wrap_add(i, fYec4_idx)) & 1048575] = fSlow40 * (fSlow41 * fRec0[faust_wrap_sub(i, 1)] + fSlow42 * fRec1[faust_wrap_sub(i, 1)] + fSlow43 * fRec2[faust_wrap_sub(i, 1)] + fSlow44 * fRec3[faust_wrap_sub(i, 1)] + fSlow45 * fRec4[faust_wrap_sub(i, 1)] + fSlow46 * fRec5[faust_wrap_sub(i, 1)] + fSlow47 * static_cast<double>(input0[i]) + fSlow48 * static_cast<double>(input1[i]));
				fRec4[i] = fYec4[(faust_wrap_sub(faust_wrap_add(i, fYec4_idx), iSlow49)) & 1048575];
				fYec5[(faust_wrap_add(i, fYec5_idx)) & 1048575] = fSlow50 * (fSlow51 * fRec0[faust_wrap_sub(i, 1)] + fSlow52 * fRec1[faust_wrap_sub(i, 1)] + fSlow53 * fRec2[faust_wrap_sub(i, 1)] + fSlow54 * fRec3[faust_wrap_sub(i, 1)] + fSlow55 * fRec4[faust_wrap_sub(i, 1)] + fSlow56 * fRec5[faust_wrap_sub(i, 1)] + fSlow57 * static_cast<double>(input0[i]) + fSlow58 * static_cast<double>(input1[i]));
				fRec5[i] = fYec5[(faust_wrap_sub(faust_wrap_add(i, fYec5_idx), iSlow59)) & 1048575];
			}
			/* Post code */
			fYec5_idx_save = vsize;
			fYec4_idx_save = vsize;
			fYec3_idx_save = vsize;
			fYec2_idx_save = vsize;
			fYec1_idx_save = vsize;
			fYec0_idx_save = vsize;
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				fRec0_perm[j1] = fRec0_tmp[faust_wrap_add(vsize, j1)];
			}
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fRec1_perm[j3] = fRec1_tmp[faust_wrap_add(vsize, j3)];
			}
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fRec2_perm[j5] = fRec2_tmp[faust_wrap_add(vsize, j5)];
			}
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec3_perm[j7] = fRec3_tmp[faust_wrap_add(vsize, j7)];
			}
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fRec4_perm[j9] = fRec4_tmp[faust_wrap_add(vsize, j9)];
			}
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				fRec5_perm[j11] = fRec5_tmp[faust_wrap_add(vsize, j11)];
			}
			/* Vectorizable loop 1 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fSlow60 * (fSlow61 * fRec0[i] + fSlow62 * fRec1[i] + fSlow63 * fRec2[i] + fSlow64 * fRec3[i] + fSlow65 * fRec4[i] + fSlow66 * fRec5[i] + fSlow67 * static_cast<double>(input0[i]) + fSlow68 * static_cast<double>(input1[i])));
			}
			/* Vectorizable loop 2 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fSlow69 * (fSlow70 * fRec0[i] + fSlow71 * fRec1[i] + fSlow72 * fRec2[i] + fSlow73 * fRec3[i] + fSlow74 * fRec4[i] + fSlow75 * fRec5[i] + fSlow76 * static_cast<double>(input0[i]) + fSlow77 * static_cast<double>(input1[i])));
			}
		}
		/* Remaining frames */
		if (vindex < count) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* input1 = &input1_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			FAUSTFLOAT* output1 = &output1_ptr[vindex];
			int vsize = faust_wrap_sub(count, vindex);
			/* Recursive loop 0 */
			/* Pre code */
			fYec0_idx = (faust_wrap_add(fYec0_idx, fYec0_idx_save)) & 1048575;
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				fRec0_tmp[j0] = fRec0_perm[j0];
			}
			fYec1_idx = (faust_wrap_add(fYec1_idx, fYec1_idx_save)) & 1048575;
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fRec1_tmp[j2] = fRec1_perm[j2];
			}
			fYec2_idx = (faust_wrap_add(fYec2_idx, fYec2_idx_save)) & 1048575;
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				fRec2_tmp[j4] = fRec2_perm[j4];
			}
			fYec3_idx = (faust_wrap_add(fYec3_idx, fYec3_idx_save)) & 1048575;
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec3_tmp[j6] = fRec3_perm[j6];
			}
			fYec4_idx = (faust_wrap_add(fYec4_idx, fYec4_idx_save)) & 1048575;
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fRec4_tmp[j8] = fRec4_perm[j8];
			}
			fYec5_idx = (faust_wrap_add(fYec5_idx, fYec5_idx_save)) & 1048575;
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				fRec5_tmp[j10] = fRec5_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec0[(faust_wrap_add(i, fYec0_idx)) & 1048575] = fSlow0 * (fSlow1 * fRec0[faust_wrap_sub(i, 1)] + fSlow2 * fRec1[faust_wrap_sub(i, 1)] + fSlow3 * fRec2[faust_wrap_sub(i, 1)] + fSlow4 * fRec3[faust_wrap_sub(i, 1)] + fSlow5 * fRec4[faust_wrap_sub(i, 1)] + fSlow6 * fRec5[faust_wrap_sub(i, 1)] + fSlow7 * static_cast<double>(input0[i]) + fSlow8 * static_cast<double>(input1[i]));
				fRec0[i] = fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), iSlow9)) & 1048575];
				fYec1[(faust_wrap_add(i, fYec1_idx)) & 1048575] = fSlow10 * (fSlow11 * fRec0[faust_wrap_sub(i, 1)] + fSlow12 * fRec1[faust_wrap_sub(i, 1)] + fSlow13 * fRec2[faust_wrap_sub(i, 1)] + fSlow14 * fRec3[faust_wrap_sub(i, 1)] + fSlow15 * fRec4[faust_wrap_sub(i, 1)] + fSlow16 * fRec5[faust_wrap_sub(i, 1)] + fSlow17 * static_cast<double>(input0[i]) + fSlow18 * static_cast<double>(input1[i]));
				fRec1[i] = fYec1[(faust_wrap_sub(faust_wrap_add(i, fYec1_idx), iSlow19)) & 1048575];
				fYec2[(faust_wrap_add(i, fYec2_idx)) & 1048575] = fSlow20 * (fSlow21 * fRec0[faust_wrap_sub(i, 1)] + fSlow22 * fRec1[faust_wrap_sub(i, 1)] + fSlow23 * fRec2[faust_wrap_sub(i, 1)] + fSlow24 * fRec3[faust_wrap_sub(i, 1)] + fSlow25 * fRec4[faust_wrap_sub(i, 1)] + fSlow26 * fRec5[faust_wrap_sub(i, 1)] + fSlow27 * static_cast<double>(input0[i]) + fSlow28 * static_cast<double>(input1[i]));
				fRec2[i] = fYec2[(faust_wrap_sub(faust_wrap_add(i, fYec2_idx), iSlow29)) & 1048575];
				fYec3[(faust_wrap_add(i, fYec3_idx)) & 1048575] = fSlow30 * (fSlow31 * fRec0[faust_wrap_sub(i, 1)] + fSlow32 * fRec1[faust_wrap_sub(i, 1)] + fSlow33 * fRec2[faust_wrap_sub(i, 1)] + fSlow34 * fRec3[faust_wrap_sub(i, 1)] + fSlow35 * fRec4[faust_wrap_sub(i, 1)] + fSlow36 * fRec5[faust_wrap_sub(i, 1)] + fSlow37 * static_cast<double>(input0[i]) + fSlow38 * static_cast<double>(input1[i]));
				fRec3[i] = fYec3[(faust_wrap_sub(faust_wrap_add(i, fYec3_idx), iSlow39)) & 1048575];
				fYec4[(faust_wrap_add(i, fYec4_idx)) & 1048575] = fSlow40 * (fSlow41 * fRec0[faust_wrap_sub(i, 1)] + fSlow42 * fRec1[faust_wrap_sub(i, 1)] + fSlow43 * fRec2[faust_wrap_sub(i, 1)] + fSlow44 * fRec3[faust_wrap_sub(i, 1)] + fSlow45 * fRec4[faust_wrap_sub(i, 1)] + fSlow46 * fRec5[faust_wrap_sub(i, 1)] + fSlow47 * static_cast<double>(input0[i]) + fSlow48 * static_cast<double>(input1[i]));
				fRec4[i] = fYec4[(faust_wrap_sub(faust_wrap_add(i, fYec4_idx), iSlow49)) & 1048575];
				fYec5[(faust_wrap_add(i, fYec5_idx)) & 1048575] = fSlow50 * (fSlow51 * fRec0[faust_wrap_sub(i, 1)] + fSlow52 * fRec1[faust_wrap_sub(i, 1)] + fSlow53 * fRec2[faust_wrap_sub(i, 1)] + fSlow54 * fRec3[faust_wrap_sub(i, 1)] + fSlow55 * fRec4[faust_wrap_sub(i, 1)] + fSlow56 * fRec5[faust_wrap_sub(i, 1)] + fSlow57 * static_cast<double>(input0[i]) + fSlow58 * static_cast<double>(input1[i]));
				fRec5[i] = fYec5[(faust_wrap_sub(faust_wrap_add(i, fYec5_idx), iSlow59)) & 1048575];
			}
			/* Post code */
			fYec5_idx_save = vsize;
			fYec4_idx_save = vsize;
			fYec3_idx_save = vsize;
			fYec2_idx_save = vsize;
			fYec1_idx_save = vsize;
			fYec0_idx_save = vsize;
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				fRec0_perm[j1] = fRec0_tmp[faust_wrap_add(vsize, j1)];
			}
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fRec1_perm[j3] = fRec1_tmp[faust_wrap_add(vsize, j3)];
			}
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fRec2_perm[j5] = fRec2_tmp[faust_wrap_add(vsize, j5)];
			}
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec3_perm[j7] = fRec3_tmp[faust_wrap_add(vsize, j7)];
			}
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fRec4_perm[j9] = fRec4_tmp[faust_wrap_add(vsize, j9)];
			}
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				fRec5_perm[j11] = fRec5_tmp[faust_wrap_add(vsize, j11)];
			}
			/* Vectorizable loop 1 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fSlow60 * (fSlow61 * fRec0[i] + fSlow62 * fRec1[i] + fSlow63 * fRec2[i] + fSlow64 * fRec3[i] + fSlow65 * fRec4[i] + fSlow66 * fRec5[i] + fSlow67 * static_cast<double>(input0[i]) + fSlow68 * static_cast<double>(input1[i])));
			}
			/* Vectorizable loop 2 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fSlow69 * (fSlow70 * fRec0[i] + fSlow71 * fRec1[i] + fSlow72 * fRec2[i] + fSlow73 * fRec3[i] + fSlow74 * fRec4[i] + fSlow75 * fRec5[i] + fSlow76 * static_cast<double>(input0[i]) + fSlow77 * static_cast<double>(input1[i])));
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
