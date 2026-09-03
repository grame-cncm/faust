/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2006"
license: "BSD"
name: "karplus32"
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
	
	int iRec1_perm[4];
	FAUSTFLOAT fButton0;
	double fVec0_perm[4];
	FAUSTFLOAT fHslider0;
	double fRec2_perm[4];
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	double fYec0[1024];
	int fYec0_idx;
	int fYec0_idx_save;
	FAUSTFLOAT fHslider3;
	double fRec0_perm[4];
	double fYec1[2048];
	int fYec1_idx;
	int fYec1_idx_save;
	FAUSTFLOAT fHslider4;
	double fRec3_perm[4];
	double fYec2[4096];
	int fYec2_idx;
	int fYec2_idx_save;
	double fRec4_perm[4];
	double fYec3[4096];
	int fYec3_idx;
	int fYec3_idx_save;
	double fRec5_perm[4];
	double fYec4[8192];
	int fYec4_idx;
	int fYec4_idx_save;
	double fRec6_perm[4];
	double fYec5[8192];
	int fYec5_idx;
	int fYec5_idx_save;
	double fRec7_perm[4];
	double fYec6[8192];
	int fYec6_idx;
	int fYec6_idx_save;
	double fRec8_perm[4];
	double fYec7[8192];
	int fYec7_idx;
	int fYec7_idx_save;
	double fRec9_perm[4];
	double fYec8[8192];
	int fYec8_idx;
	int fYec8_idx_save;
	double fRec10_perm[4];
	double fYec9[8192];
	int fYec9_idx;
	int fYec9_idx_save;
	double fRec11_perm[4];
	double fYec10[8192];
	int fYec10_idx;
	int fYec10_idx_save;
	double fRec12_perm[4];
	double fYec11[8192];
	int fYec11_idx;
	int fYec11_idx_save;
	double fRec13_perm[4];
	double fYec12[8192];
	int fYec12_idx;
	int fYec12_idx_save;
	double fRec14_perm[4];
	double fYec13[8192];
	int fYec13_idx;
	int fYec13_idx_save;
	double fRec15_perm[4];
	double fYec14[8192];
	int fYec14_idx;
	int fYec14_idx_save;
	double fRec16_perm[4];
	double fYec15[8192];
	int fYec15_idx;
	int fYec15_idx_save;
	double fRec17_perm[4];
	FAUSTFLOAT fHslider5;
	FAUSTFLOAT fHslider6;
	double fYec16[2048];
	int fYec16_idx;
	int fYec16_idx_save;
	double fRec18_perm[4];
	double fYec17[4096];
	int fYec17_idx;
	int fYec17_idx_save;
	double fRec19_perm[4];
	double fYec18[4096];
	int fYec18_idx;
	int fYec18_idx_save;
	double fRec20_perm[4];
	double fYec19[8192];
	int fYec19_idx;
	int fYec19_idx_save;
	double fRec21_perm[4];
	double fYec20[8192];
	int fYec20_idx;
	int fYec20_idx_save;
	double fRec22_perm[4];
	double fYec21[8192];
	int fYec21_idx;
	int fYec21_idx_save;
	double fRec23_perm[4];
	double fYec22[8192];
	int fYec22_idx;
	int fYec22_idx_save;
	double fRec24_perm[4];
	double fYec23[8192];
	int fYec23_idx;
	int fYec23_idx_save;
	double fRec25_perm[4];
	double fYec24[8192];
	int fYec24_idx;
	int fYec24_idx_save;
	double fRec26_perm[4];
	double fYec25[8192];
	int fYec25_idx;
	int fYec25_idx_save;
	double fRec27_perm[4];
	double fYec26[8192];
	int fYec26_idx;
	int fYec26_idx_save;
	double fRec28_perm[4];
	double fYec27[8192];
	int fYec27_idx;
	int fYec27_idx_save;
	double fRec29_perm[4];
	double fYec28[8192];
	int fYec28_idx;
	int fYec28_idx_save;
	double fRec30_perm[4];
	double fYec29[8192];
	int fYec29_idx;
	int fYec29_idx_save;
	double fRec31_perm[4];
	double fYec30[8192];
	int fYec30_idx;
	int fYec30_idx_save;
	double fRec32_perm[4];
	double fYec31[8192];
	int fYec31_idx;
	int fYec31_idx_save;
	double fRec33_perm[4];
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
		m->declare("filename", "karplus32.dsp");
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
		m->declare("name", "karplus32");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() {
		return 0;
	}
	virtual int getNumOutputs() {
		return 2;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
	}
	
	virtual void instanceResetUserInterface() {
		fButton0 = static_cast<FAUSTFLOAT>(0.0);
		fHslider0 = static_cast<FAUSTFLOAT>(128.0);
		fHslider1 = static_cast<FAUSTFLOAT>(0.0);
		fHslider2 = static_cast<FAUSTFLOAT>(0.5);
		fHslider3 = static_cast<FAUSTFLOAT>(128.0);
		fHslider4 = static_cast<FAUSTFLOAT>(37.9904);
		fHslider5 = static_cast<FAUSTFLOAT>(0.4866);
		fHslider6 = static_cast<FAUSTFLOAT>(14.0);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 4; l0 = faust_wrap_add(l0, 1)) {
			iRec1_perm[l0] = 0;
		}
		for (int l1 = 0; l1 < 4; l1 = faust_wrap_add(l1, 1)) {
			fVec0_perm[l1] = 0.0;
		}
		for (int l2 = 0; l2 < 4; l2 = faust_wrap_add(l2, 1)) {
			fRec2_perm[l2] = 0.0;
		}
		for (int l3 = 0; l3 < 1024; l3 = faust_wrap_add(l3, 1)) {
			fYec0[l3] = 0.0;
		}
		fYec0_idx = 0;
		fYec0_idx_save = 0;
		for (int l4 = 0; l4 < 4; l4 = faust_wrap_add(l4, 1)) {
			fRec0_perm[l4] = 0.0;
		}
		for (int l5 = 0; l5 < 2048; l5 = faust_wrap_add(l5, 1)) {
			fYec1[l5] = 0.0;
		}
		fYec1_idx = 0;
		fYec1_idx_save = 0;
		for (int l6 = 0; l6 < 4; l6 = faust_wrap_add(l6, 1)) {
			fRec3_perm[l6] = 0.0;
		}
		for (int l7 = 0; l7 < 4096; l7 = faust_wrap_add(l7, 1)) {
			fYec2[l7] = 0.0;
		}
		fYec2_idx = 0;
		fYec2_idx_save = 0;
		for (int l8 = 0; l8 < 4; l8 = faust_wrap_add(l8, 1)) {
			fRec4_perm[l8] = 0.0;
		}
		for (int l9 = 0; l9 < 4096; l9 = faust_wrap_add(l9, 1)) {
			fYec3[l9] = 0.0;
		}
		fYec3_idx = 0;
		fYec3_idx_save = 0;
		for (int l10 = 0; l10 < 4; l10 = faust_wrap_add(l10, 1)) {
			fRec5_perm[l10] = 0.0;
		}
		for (int l11 = 0; l11 < 8192; l11 = faust_wrap_add(l11, 1)) {
			fYec4[l11] = 0.0;
		}
		fYec4_idx = 0;
		fYec4_idx_save = 0;
		for (int l12 = 0; l12 < 4; l12 = faust_wrap_add(l12, 1)) {
			fRec6_perm[l12] = 0.0;
		}
		for (int l13 = 0; l13 < 8192; l13 = faust_wrap_add(l13, 1)) {
			fYec5[l13] = 0.0;
		}
		fYec5_idx = 0;
		fYec5_idx_save = 0;
		for (int l14 = 0; l14 < 4; l14 = faust_wrap_add(l14, 1)) {
			fRec7_perm[l14] = 0.0;
		}
		for (int l15 = 0; l15 < 8192; l15 = faust_wrap_add(l15, 1)) {
			fYec6[l15] = 0.0;
		}
		fYec6_idx = 0;
		fYec6_idx_save = 0;
		for (int l16 = 0; l16 < 4; l16 = faust_wrap_add(l16, 1)) {
			fRec8_perm[l16] = 0.0;
		}
		for (int l17 = 0; l17 < 8192; l17 = faust_wrap_add(l17, 1)) {
			fYec7[l17] = 0.0;
		}
		fYec7_idx = 0;
		fYec7_idx_save = 0;
		for (int l18 = 0; l18 < 4; l18 = faust_wrap_add(l18, 1)) {
			fRec9_perm[l18] = 0.0;
		}
		for (int l19 = 0; l19 < 8192; l19 = faust_wrap_add(l19, 1)) {
			fYec8[l19] = 0.0;
		}
		fYec8_idx = 0;
		fYec8_idx_save = 0;
		for (int l20 = 0; l20 < 4; l20 = faust_wrap_add(l20, 1)) {
			fRec10_perm[l20] = 0.0;
		}
		for (int l21 = 0; l21 < 8192; l21 = faust_wrap_add(l21, 1)) {
			fYec9[l21] = 0.0;
		}
		fYec9_idx = 0;
		fYec9_idx_save = 0;
		for (int l22 = 0; l22 < 4; l22 = faust_wrap_add(l22, 1)) {
			fRec11_perm[l22] = 0.0;
		}
		for (int l23 = 0; l23 < 8192; l23 = faust_wrap_add(l23, 1)) {
			fYec10[l23] = 0.0;
		}
		fYec10_idx = 0;
		fYec10_idx_save = 0;
		for (int l24 = 0; l24 < 4; l24 = faust_wrap_add(l24, 1)) {
			fRec12_perm[l24] = 0.0;
		}
		for (int l25 = 0; l25 < 8192; l25 = faust_wrap_add(l25, 1)) {
			fYec11[l25] = 0.0;
		}
		fYec11_idx = 0;
		fYec11_idx_save = 0;
		for (int l26 = 0; l26 < 4; l26 = faust_wrap_add(l26, 1)) {
			fRec13_perm[l26] = 0.0;
		}
		for (int l27 = 0; l27 < 8192; l27 = faust_wrap_add(l27, 1)) {
			fYec12[l27] = 0.0;
		}
		fYec12_idx = 0;
		fYec12_idx_save = 0;
		for (int l28 = 0; l28 < 4; l28 = faust_wrap_add(l28, 1)) {
			fRec14_perm[l28] = 0.0;
		}
		for (int l29 = 0; l29 < 8192; l29 = faust_wrap_add(l29, 1)) {
			fYec13[l29] = 0.0;
		}
		fYec13_idx = 0;
		fYec13_idx_save = 0;
		for (int l30 = 0; l30 < 4; l30 = faust_wrap_add(l30, 1)) {
			fRec15_perm[l30] = 0.0;
		}
		for (int l31 = 0; l31 < 8192; l31 = faust_wrap_add(l31, 1)) {
			fYec14[l31] = 0.0;
		}
		fYec14_idx = 0;
		fYec14_idx_save = 0;
		for (int l32 = 0; l32 < 4; l32 = faust_wrap_add(l32, 1)) {
			fRec16_perm[l32] = 0.0;
		}
		for (int l33 = 0; l33 < 8192; l33 = faust_wrap_add(l33, 1)) {
			fYec15[l33] = 0.0;
		}
		fYec15_idx = 0;
		fYec15_idx_save = 0;
		for (int l34 = 0; l34 < 4; l34 = faust_wrap_add(l34, 1)) {
			fRec17_perm[l34] = 0.0;
		}
		for (int l35 = 0; l35 < 2048; l35 = faust_wrap_add(l35, 1)) {
			fYec16[l35] = 0.0;
		}
		fYec16_idx = 0;
		fYec16_idx_save = 0;
		for (int l36 = 0; l36 < 4; l36 = faust_wrap_add(l36, 1)) {
			fRec18_perm[l36] = 0.0;
		}
		for (int l37 = 0; l37 < 4096; l37 = faust_wrap_add(l37, 1)) {
			fYec17[l37] = 0.0;
		}
		fYec17_idx = 0;
		fYec17_idx_save = 0;
		for (int l38 = 0; l38 < 4; l38 = faust_wrap_add(l38, 1)) {
			fRec19_perm[l38] = 0.0;
		}
		for (int l39 = 0; l39 < 4096; l39 = faust_wrap_add(l39, 1)) {
			fYec18[l39] = 0.0;
		}
		fYec18_idx = 0;
		fYec18_idx_save = 0;
		for (int l40 = 0; l40 < 4; l40 = faust_wrap_add(l40, 1)) {
			fRec20_perm[l40] = 0.0;
		}
		for (int l41 = 0; l41 < 8192; l41 = faust_wrap_add(l41, 1)) {
			fYec19[l41] = 0.0;
		}
		fYec19_idx = 0;
		fYec19_idx_save = 0;
		for (int l42 = 0; l42 < 4; l42 = faust_wrap_add(l42, 1)) {
			fRec21_perm[l42] = 0.0;
		}
		for (int l43 = 0; l43 < 8192; l43 = faust_wrap_add(l43, 1)) {
			fYec20[l43] = 0.0;
		}
		fYec20_idx = 0;
		fYec20_idx_save = 0;
		for (int l44 = 0; l44 < 4; l44 = faust_wrap_add(l44, 1)) {
			fRec22_perm[l44] = 0.0;
		}
		for (int l45 = 0; l45 < 8192; l45 = faust_wrap_add(l45, 1)) {
			fYec21[l45] = 0.0;
		}
		fYec21_idx = 0;
		fYec21_idx_save = 0;
		for (int l46 = 0; l46 < 4; l46 = faust_wrap_add(l46, 1)) {
			fRec23_perm[l46] = 0.0;
		}
		for (int l47 = 0; l47 < 8192; l47 = faust_wrap_add(l47, 1)) {
			fYec22[l47] = 0.0;
		}
		fYec22_idx = 0;
		fYec22_idx_save = 0;
		for (int l48 = 0; l48 < 4; l48 = faust_wrap_add(l48, 1)) {
			fRec24_perm[l48] = 0.0;
		}
		for (int l49 = 0; l49 < 8192; l49 = faust_wrap_add(l49, 1)) {
			fYec23[l49] = 0.0;
		}
		fYec23_idx = 0;
		fYec23_idx_save = 0;
		for (int l50 = 0; l50 < 4; l50 = faust_wrap_add(l50, 1)) {
			fRec25_perm[l50] = 0.0;
		}
		for (int l51 = 0; l51 < 8192; l51 = faust_wrap_add(l51, 1)) {
			fYec24[l51] = 0.0;
		}
		fYec24_idx = 0;
		fYec24_idx_save = 0;
		for (int l52 = 0; l52 < 4; l52 = faust_wrap_add(l52, 1)) {
			fRec26_perm[l52] = 0.0;
		}
		for (int l53 = 0; l53 < 8192; l53 = faust_wrap_add(l53, 1)) {
			fYec25[l53] = 0.0;
		}
		fYec25_idx = 0;
		fYec25_idx_save = 0;
		for (int l54 = 0; l54 < 4; l54 = faust_wrap_add(l54, 1)) {
			fRec27_perm[l54] = 0.0;
		}
		for (int l55 = 0; l55 < 8192; l55 = faust_wrap_add(l55, 1)) {
			fYec26[l55] = 0.0;
		}
		fYec26_idx = 0;
		fYec26_idx_save = 0;
		for (int l56 = 0; l56 < 4; l56 = faust_wrap_add(l56, 1)) {
			fRec28_perm[l56] = 0.0;
		}
		for (int l57 = 0; l57 < 8192; l57 = faust_wrap_add(l57, 1)) {
			fYec27[l57] = 0.0;
		}
		fYec27_idx = 0;
		fYec27_idx_save = 0;
		for (int l58 = 0; l58 < 4; l58 = faust_wrap_add(l58, 1)) {
			fRec29_perm[l58] = 0.0;
		}
		for (int l59 = 0; l59 < 8192; l59 = faust_wrap_add(l59, 1)) {
			fYec28[l59] = 0.0;
		}
		fYec28_idx = 0;
		fYec28_idx_save = 0;
		for (int l60 = 0; l60 < 4; l60 = faust_wrap_add(l60, 1)) {
			fRec30_perm[l60] = 0.0;
		}
		for (int l61 = 0; l61 < 8192; l61 = faust_wrap_add(l61, 1)) {
			fYec29[l61] = 0.0;
		}
		fYec29_idx = 0;
		fYec29_idx_save = 0;
		for (int l62 = 0; l62 < 4; l62 = faust_wrap_add(l62, 1)) {
			fRec31_perm[l62] = 0.0;
		}
		for (int l63 = 0; l63 < 8192; l63 = faust_wrap_add(l63, 1)) {
			fYec30[l63] = 0.0;
		}
		fYec30_idx = 0;
		fYec30_idx_save = 0;
		for (int l64 = 0; l64 < 4; l64 = faust_wrap_add(l64, 1)) {
			fRec32_perm[l64] = 0.0;
		}
		for (int l65 = 0; l65 < 8192; l65 = faust_wrap_add(l65, 1)) {
			fYec31[l65] = 0.0;
		}
		fYec31_idx = 0;
		fYec31_idx_save = 0;
		for (int l66 = 0; l66 < 4; l66 = faust_wrap_add(l66, 1)) {
			fRec33_perm[l66] = 0.0;
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
		ui_interface->openVerticalBox("karplus32");
		ui_interface->openVerticalBox("excitator");
		ui_interface->addHorizontalSlider("excitation (samples)", &fHslider0, FAUSTFLOAT(128.0), FAUSTFLOAT(2.0), FAUSTFLOAT(512.0), FAUSTFLOAT(1.0));
		ui_interface->addButton("play", &fButton0);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("noise generator");
		ui_interface->addHorizontalSlider("level", &fHslider2, FAUSTFLOAT(0.5), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->addHorizontalSlider("output volume", &fHslider5, FAUSTFLOAT(0.4866), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.1));
		ui_interface->openVerticalBox("resonator x32");
		ui_interface->addHorizontalSlider("attenuation", &fHslider1, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.01));
		ui_interface->addHorizontalSlider("detune", &fHslider4, FAUSTFLOAT(37.9904), FAUSTFLOAT(0.0), FAUSTFLOAT(512.0), FAUSTFLOAT(1.0));
		ui_interface->addHorizontalSlider("duration (samples)", &fHslider3, FAUSTFLOAT(128.0), FAUSTFLOAT(2.0), FAUSTFLOAT(512.0), FAUSTFLOAT(1.0));
		ui_interface->addHorizontalSlider("polyphony", &fHslider6, FAUSTFLOAT(14.0), FAUSTFLOAT(0.0), FAUSTFLOAT(32.0), FAUSTFLOAT(1.0));
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* output0_ptr = outputs[0];
		FAUSTFLOAT* output1_ptr = outputs[1];
		int iRec1_tmp[8];
		int* iRec1 = &iRec1_tmp[4];
		double fSlow0 = static_cast<double>(fButton0);
		double fVec0_tmp[8];
		double* fVec0 = &fVec0_tmp[4];
		double fSlow1 = 1.0 / static_cast<double>(fHslider0);
		double fRec2_tmp[8];
		double* fRec2 = &fRec2_tmp[4];
		double fSlow2 = 0.5 * (1.0 - static_cast<double>(fHslider1));
		double fSlow3 = 4.656612875245797e-10 * static_cast<double>(fHslider2);
		double fZec0[4];
		double fSlow4 = static_cast<double>(fHslider3);
		int iSlow5 = static_cast<int>(fSlow4 + -1.5) & 4095;
		double fRec0_tmp[8];
		double* fRec0 = &fRec0_tmp[4];
		double fSlow6 = static_cast<double>(fHslider4);
		int iSlow7 = static_cast<int>(fSlow4 + 2.0 * fSlow6 + -1.5) & 4095;
		double fRec3_tmp[8];
		double* fRec3 = &fRec3_tmp[4];
		int iSlow8 = static_cast<int>(fSlow4 + 4.0 * fSlow6 + -1.5) & 4095;
		double fRec4_tmp[8];
		double* fRec4 = &fRec4_tmp[4];
		int iSlow9 = static_cast<int>(fSlow4 + 6.0 * fSlow6 + -1.5) & 4095;
		double fRec5_tmp[8];
		double* fRec5 = &fRec5_tmp[4];
		int iSlow10 = static_cast<int>(fSlow4 + 8.0 * fSlow6 + -1.5) & 4095;
		double fRec6_tmp[8];
		double* fRec6 = &fRec6_tmp[4];
		int iSlow11 = static_cast<int>(fSlow4 + 1e+01 * fSlow6 + -1.5) & 4095;
		double fRec7_tmp[8];
		double* fRec7 = &fRec7_tmp[4];
		int iSlow12 = static_cast<int>(fSlow4 + 12.0 * fSlow6 + -1.5) & 4095;
		double fRec8_tmp[8];
		double* fRec8 = &fRec8_tmp[4];
		int iSlow13 = static_cast<int>(fSlow4 + 14.0 * fSlow6 + -1.5) & 4095;
		double fRec9_tmp[8];
		double* fRec9 = &fRec9_tmp[4];
		int iSlow14 = static_cast<int>(fSlow4 + 16.0 * fSlow6 + -1.5) & 4095;
		double fRec10_tmp[8];
		double* fRec10 = &fRec10_tmp[4];
		int iSlow15 = static_cast<int>(fSlow4 + 18.0 * fSlow6 + -1.5) & 4095;
		double fRec11_tmp[8];
		double* fRec11 = &fRec11_tmp[4];
		int iSlow16 = static_cast<int>(fSlow4 + 2e+01 * fSlow6 + -1.5) & 4095;
		double fRec12_tmp[8];
		double* fRec12 = &fRec12_tmp[4];
		int iSlow17 = static_cast<int>(fSlow4 + 22.0 * fSlow6 + -1.5) & 4095;
		double fRec13_tmp[8];
		double* fRec13 = &fRec13_tmp[4];
		int iSlow18 = static_cast<int>(fSlow4 + 24.0 * fSlow6 + -1.5) & 4095;
		double fRec14_tmp[8];
		double* fRec14 = &fRec14_tmp[4];
		int iSlow19 = static_cast<int>(fSlow4 + 26.0 * fSlow6 + -1.5) & 4095;
		double fRec15_tmp[8];
		double* fRec15 = &fRec15_tmp[4];
		int iSlow20 = static_cast<int>(fSlow4 + 28.0 * fSlow6 + -1.5) & 4095;
		double fRec16_tmp[8];
		double* fRec16 = &fRec16_tmp[4];
		int iSlow21 = static_cast<int>(fSlow4 + 3e+01 * fSlow6 + -1.5) & 4095;
		double fRec17_tmp[8];
		double* fRec17 = &fRec17_tmp[4];
		double fSlow22 = static_cast<double>(fHslider5);
		double fSlow23 = static_cast<double>(fHslider6);
		double fSlow24 = static_cast<double>(fSlow23 > 0.0);
		double fSlow25 = static_cast<double>(fSlow23 > 2.0);
		double fSlow26 = static_cast<double>(fSlow23 > 4.0);
		double fSlow27 = static_cast<double>(fSlow23 > 6.0);
		double fSlow28 = static_cast<double>(fSlow23 > 8.0);
		double fSlow29 = static_cast<double>(fSlow23 > 1e+01);
		double fSlow30 = static_cast<double>(fSlow23 > 12.0);
		double fSlow31 = static_cast<double>(fSlow23 > 14.0);
		double fSlow32 = static_cast<double>(fSlow23 > 16.0);
		double fSlow33 = static_cast<double>(fSlow23 > 18.0);
		double fSlow34 = static_cast<double>(fSlow23 > 2e+01);
		double fSlow35 = static_cast<double>(fSlow23 > 22.0);
		double fSlow36 = static_cast<double>(fSlow23 > 24.0);
		double fSlow37 = static_cast<double>(fSlow23 > 26.0);
		double fSlow38 = static_cast<double>(fSlow23 > 28.0);
		double fSlow39 = static_cast<double>(fSlow23 > 3e+01);
		int iSlow40 = static_cast<int>(fSlow4 + fSlow6 + -1.5) & 4095;
		double fRec18_tmp[8];
		double* fRec18 = &fRec18_tmp[4];
		int iSlow41 = static_cast<int>(fSlow4 + 3.0 * fSlow6 + -1.5) & 4095;
		double fRec19_tmp[8];
		double* fRec19 = &fRec19_tmp[4];
		int iSlow42 = static_cast<int>(fSlow4 + 5.0 * fSlow6 + -1.5) & 4095;
		double fRec20_tmp[8];
		double* fRec20 = &fRec20_tmp[4];
		int iSlow43 = static_cast<int>(fSlow4 + 7.0 * fSlow6 + -1.5) & 4095;
		double fRec21_tmp[8];
		double* fRec21 = &fRec21_tmp[4];
		int iSlow44 = static_cast<int>(fSlow4 + 9.0 * fSlow6 + -1.5) & 4095;
		double fRec22_tmp[8];
		double* fRec22 = &fRec22_tmp[4];
		int iSlow45 = static_cast<int>(fSlow4 + 11.0 * fSlow6 + -1.5) & 4095;
		double fRec23_tmp[8];
		double* fRec23 = &fRec23_tmp[4];
		int iSlow46 = static_cast<int>(fSlow4 + 13.0 * fSlow6 + -1.5) & 4095;
		double fRec24_tmp[8];
		double* fRec24 = &fRec24_tmp[4];
		int iSlow47 = static_cast<int>(fSlow4 + 15.0 * fSlow6 + -1.5) & 4095;
		double fRec25_tmp[8];
		double* fRec25 = &fRec25_tmp[4];
		int iSlow48 = static_cast<int>(fSlow4 + 17.0 * fSlow6 + -1.5) & 4095;
		double fRec26_tmp[8];
		double* fRec26 = &fRec26_tmp[4];
		int iSlow49 = static_cast<int>(fSlow4 + 19.0 * fSlow6 + -1.5) & 4095;
		double fRec27_tmp[8];
		double* fRec27 = &fRec27_tmp[4];
		int iSlow50 = static_cast<int>(fSlow4 + 21.0 * fSlow6 + -1.5) & 4095;
		double fRec28_tmp[8];
		double* fRec28 = &fRec28_tmp[4];
		int iSlow51 = static_cast<int>(fSlow4 + 23.0 * fSlow6 + -1.5) & 4095;
		double fRec29_tmp[8];
		double* fRec29 = &fRec29_tmp[4];
		int iSlow52 = static_cast<int>(fSlow4 + 25.0 * fSlow6 + -1.5) & 4095;
		double fRec30_tmp[8];
		double* fRec30 = &fRec30_tmp[4];
		int iSlow53 = static_cast<int>(fSlow4 + 27.0 * fSlow6 + -1.5) & 4095;
		double fRec31_tmp[8];
		double* fRec31 = &fRec31_tmp[4];
		int iSlow54 = static_cast<int>(fSlow4 + 29.0 * fSlow6 + -1.5) & 4095;
		double fRec32_tmp[8];
		double* fRec32 = &fRec32_tmp[4];
		int iSlow55 = static_cast<int>(fSlow4 + 31.0 * fSlow6 + -1.5) & 4095;
		double fRec33_tmp[8];
		double* fRec33 = &fRec33_tmp[4];
		double fSlow56 = static_cast<double>(fSlow23 > 1.0);
		double fSlow57 = static_cast<double>(fSlow23 > 3.0);
		double fSlow58 = static_cast<double>(fSlow23 > 5.0);
		double fSlow59 = static_cast<double>(fSlow23 > 7.0);
		double fSlow60 = static_cast<double>(fSlow23 > 9.0);
		double fSlow61 = static_cast<double>(fSlow23 > 11.0);
		double fSlow62 = static_cast<double>(fSlow23 > 13.0);
		double fSlow63 = static_cast<double>(fSlow23 > 15.0);
		double fSlow64 = static_cast<double>(fSlow23 > 17.0);
		double fSlow65 = static_cast<double>(fSlow23 > 19.0);
		double fSlow66 = static_cast<double>(fSlow23 > 21.0);
		double fSlow67 = static_cast<double>(fSlow23 > 23.0);
		double fSlow68 = static_cast<double>(fSlow23 > 25.0);
		double fSlow69 = static_cast<double>(fSlow23 > 27.0);
		double fSlow70 = static_cast<double>(fSlow23 > 29.0);
		double fSlow71 = static_cast<double>(fSlow23 > 31.0);
		int vindex = 0;
		/* Main loop */
		for (vindex = 0; vindex <= (faust_wrap_sub(count, 4)); vindex = faust_wrap_add(vindex, 4)) {
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			FAUSTFLOAT* output1 = &output1_ptr[vindex];
			int vsize = 4;
			/* Recursive loop 0 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				iRec1_tmp[j0] = iRec1_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iRec1[i] = faust_wrap_add(faust_wrap_mul(1103515245, iRec1[faust_wrap_sub(i, 1)]), 12345);
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				iRec1_perm[j1] = iRec1_tmp[faust_wrap_add(vsize, j1)];
			}
			/* Vectorizable loop 1 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fVec0_tmp[j2] = fVec0_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVec0[i] = fSlow0;
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fVec0_perm[j3] = fVec0_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Recursive loop 2 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				fRec2_tmp[j4] = fRec2_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec2[i] = fRec2[faust_wrap_sub(i, 1)] + static_cast<double>((fSlow0 - fVec0[faust_wrap_sub(i, 1)]) > 0.0) - fSlow1 * static_cast<double>(fRec2[faust_wrap_sub(i, 1)] > 0.0);
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fRec2_perm[j5] = fRec2_tmp[faust_wrap_add(vsize, j5)];
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec0[i] = fSlow3 * static_cast<double>(iRec1[i]) * (static_cast<double>(fRec2[i] > 0.0) + 1.52587890625e-05);
			}
			/* Recursive loop 4 */
			/* Pre code */
			fYec0_idx = (faust_wrap_add(fYec0_idx, fYec0_idx_save)) & 1023;
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec0_tmp[j6] = fRec0_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec0[(faust_wrap_add(i, fYec0_idx)) & 1023] = fSlow2 * (fRec0[faust_wrap_sub(i, 1)] + fRec0[faust_wrap_sub(i, 2)]) + fZec0[i];
				fRec0[i] = fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), iSlow5)) & 1023];
			}
			/* Post code */
			fYec0_idx_save = vsize;
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec0_perm[j7] = fRec0_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Recursive loop 5 */
			/* Pre code */
			fYec1_idx = (faust_wrap_add(fYec1_idx, fYec1_idx_save)) & 2047;
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fRec3_tmp[j8] = fRec3_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec1[(faust_wrap_add(i, fYec1_idx)) & 2047] = fZec0[i] + fSlow2 * (fRec3[faust_wrap_sub(i, 1)] + fRec3[faust_wrap_sub(i, 2)]);
				fRec3[i] = fYec1[(faust_wrap_sub(faust_wrap_add(i, fYec1_idx), iSlow7)) & 2047];
			}
			/* Post code */
			fYec1_idx_save = vsize;
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fRec3_perm[j9] = fRec3_tmp[faust_wrap_add(vsize, j9)];
			}
			/* Recursive loop 6 */
			/* Pre code */
			fYec2_idx = (faust_wrap_add(fYec2_idx, fYec2_idx_save)) & 4095;
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				fRec4_tmp[j10] = fRec4_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec2[(faust_wrap_add(i, fYec2_idx)) & 4095] = fZec0[i] + fSlow2 * (fRec4[faust_wrap_sub(i, 1)] + fRec4[faust_wrap_sub(i, 2)]);
				fRec4[i] = fYec2[(faust_wrap_sub(faust_wrap_add(i, fYec2_idx), iSlow8)) & 4095];
			}
			/* Post code */
			fYec2_idx_save = vsize;
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				fRec4_perm[j11] = fRec4_tmp[faust_wrap_add(vsize, j11)];
			}
			/* Recursive loop 7 */
			/* Pre code */
			fYec3_idx = (faust_wrap_add(fYec3_idx, fYec3_idx_save)) & 4095;
			for (int j12 = 0; j12 < 4; j12 = faust_wrap_add(j12, 1)) {
				fRec5_tmp[j12] = fRec5_perm[j12];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec3[(faust_wrap_add(i, fYec3_idx)) & 4095] = fZec0[i] + fSlow2 * (fRec5[faust_wrap_sub(i, 1)] + fRec5[faust_wrap_sub(i, 2)]);
				fRec5[i] = fYec3[(faust_wrap_sub(faust_wrap_add(i, fYec3_idx), iSlow9)) & 4095];
			}
			/* Post code */
			fYec3_idx_save = vsize;
			for (int j13 = 0; j13 < 4; j13 = faust_wrap_add(j13, 1)) {
				fRec5_perm[j13] = fRec5_tmp[faust_wrap_add(vsize, j13)];
			}
			/* Recursive loop 8 */
			/* Pre code */
			fYec4_idx = (faust_wrap_add(fYec4_idx, fYec4_idx_save)) & 8191;
			for (int j14 = 0; j14 < 4; j14 = faust_wrap_add(j14, 1)) {
				fRec6_tmp[j14] = fRec6_perm[j14];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec4[(faust_wrap_add(i, fYec4_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec6[faust_wrap_sub(i, 1)] + fRec6[faust_wrap_sub(i, 2)]);
				fRec6[i] = fYec4[(faust_wrap_sub(faust_wrap_add(i, fYec4_idx), iSlow10)) & 8191];
			}
			/* Post code */
			fYec4_idx_save = vsize;
			for (int j15 = 0; j15 < 4; j15 = faust_wrap_add(j15, 1)) {
				fRec6_perm[j15] = fRec6_tmp[faust_wrap_add(vsize, j15)];
			}
			/* Recursive loop 9 */
			/* Pre code */
			fYec5_idx = (faust_wrap_add(fYec5_idx, fYec5_idx_save)) & 8191;
			for (int j16 = 0; j16 < 4; j16 = faust_wrap_add(j16, 1)) {
				fRec7_tmp[j16] = fRec7_perm[j16];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec5[(faust_wrap_add(i, fYec5_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec7[faust_wrap_sub(i, 1)] + fRec7[faust_wrap_sub(i, 2)]);
				fRec7[i] = fYec5[(faust_wrap_sub(faust_wrap_add(i, fYec5_idx), iSlow11)) & 8191];
			}
			/* Post code */
			fYec5_idx_save = vsize;
			for (int j17 = 0; j17 < 4; j17 = faust_wrap_add(j17, 1)) {
				fRec7_perm[j17] = fRec7_tmp[faust_wrap_add(vsize, j17)];
			}
			/* Recursive loop 10 */
			/* Pre code */
			fYec6_idx = (faust_wrap_add(fYec6_idx, fYec6_idx_save)) & 8191;
			for (int j18 = 0; j18 < 4; j18 = faust_wrap_add(j18, 1)) {
				fRec8_tmp[j18] = fRec8_perm[j18];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec6[(faust_wrap_add(i, fYec6_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec8[faust_wrap_sub(i, 1)] + fRec8[faust_wrap_sub(i, 2)]);
				fRec8[i] = fYec6[(faust_wrap_sub(faust_wrap_add(i, fYec6_idx), iSlow12)) & 8191];
			}
			/* Post code */
			fYec6_idx_save = vsize;
			for (int j19 = 0; j19 < 4; j19 = faust_wrap_add(j19, 1)) {
				fRec8_perm[j19] = fRec8_tmp[faust_wrap_add(vsize, j19)];
			}
			/* Recursive loop 11 */
			/* Pre code */
			fYec7_idx = (faust_wrap_add(fYec7_idx, fYec7_idx_save)) & 8191;
			for (int j20 = 0; j20 < 4; j20 = faust_wrap_add(j20, 1)) {
				fRec9_tmp[j20] = fRec9_perm[j20];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec7[(faust_wrap_add(i, fYec7_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec9[faust_wrap_sub(i, 1)] + fRec9[faust_wrap_sub(i, 2)]);
				fRec9[i] = fYec7[(faust_wrap_sub(faust_wrap_add(i, fYec7_idx), iSlow13)) & 8191];
			}
			/* Post code */
			fYec7_idx_save = vsize;
			for (int j21 = 0; j21 < 4; j21 = faust_wrap_add(j21, 1)) {
				fRec9_perm[j21] = fRec9_tmp[faust_wrap_add(vsize, j21)];
			}
			/* Recursive loop 12 */
			/* Pre code */
			fYec8_idx = (faust_wrap_add(fYec8_idx, fYec8_idx_save)) & 8191;
			for (int j22 = 0; j22 < 4; j22 = faust_wrap_add(j22, 1)) {
				fRec10_tmp[j22] = fRec10_perm[j22];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec8[(faust_wrap_add(i, fYec8_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec10[faust_wrap_sub(i, 1)] + fRec10[faust_wrap_sub(i, 2)]);
				fRec10[i] = fYec8[(faust_wrap_sub(faust_wrap_add(i, fYec8_idx), iSlow14)) & 8191];
			}
			/* Post code */
			fYec8_idx_save = vsize;
			for (int j23 = 0; j23 < 4; j23 = faust_wrap_add(j23, 1)) {
				fRec10_perm[j23] = fRec10_tmp[faust_wrap_add(vsize, j23)];
			}
			/* Recursive loop 13 */
			/* Pre code */
			fYec9_idx = (faust_wrap_add(fYec9_idx, fYec9_idx_save)) & 8191;
			for (int j24 = 0; j24 < 4; j24 = faust_wrap_add(j24, 1)) {
				fRec11_tmp[j24] = fRec11_perm[j24];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec9[(faust_wrap_add(i, fYec9_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec11[faust_wrap_sub(i, 1)] + fRec11[faust_wrap_sub(i, 2)]);
				fRec11[i] = fYec9[(faust_wrap_sub(faust_wrap_add(i, fYec9_idx), iSlow15)) & 8191];
			}
			/* Post code */
			fYec9_idx_save = vsize;
			for (int j25 = 0; j25 < 4; j25 = faust_wrap_add(j25, 1)) {
				fRec11_perm[j25] = fRec11_tmp[faust_wrap_add(vsize, j25)];
			}
			/* Recursive loop 14 */
			/* Pre code */
			fYec10_idx = (faust_wrap_add(fYec10_idx, fYec10_idx_save)) & 8191;
			for (int j26 = 0; j26 < 4; j26 = faust_wrap_add(j26, 1)) {
				fRec12_tmp[j26] = fRec12_perm[j26];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec10[(faust_wrap_add(i, fYec10_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec12[faust_wrap_sub(i, 1)] + fRec12[faust_wrap_sub(i, 2)]);
				fRec12[i] = fYec10[(faust_wrap_sub(faust_wrap_add(i, fYec10_idx), iSlow16)) & 8191];
			}
			/* Post code */
			fYec10_idx_save = vsize;
			for (int j27 = 0; j27 < 4; j27 = faust_wrap_add(j27, 1)) {
				fRec12_perm[j27] = fRec12_tmp[faust_wrap_add(vsize, j27)];
			}
			/* Recursive loop 15 */
			/* Pre code */
			fYec11_idx = (faust_wrap_add(fYec11_idx, fYec11_idx_save)) & 8191;
			for (int j28 = 0; j28 < 4; j28 = faust_wrap_add(j28, 1)) {
				fRec13_tmp[j28] = fRec13_perm[j28];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec11[(faust_wrap_add(i, fYec11_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec13[faust_wrap_sub(i, 1)] + fRec13[faust_wrap_sub(i, 2)]);
				fRec13[i] = fYec11[(faust_wrap_sub(faust_wrap_add(i, fYec11_idx), iSlow17)) & 8191];
			}
			/* Post code */
			fYec11_idx_save = vsize;
			for (int j29 = 0; j29 < 4; j29 = faust_wrap_add(j29, 1)) {
				fRec13_perm[j29] = fRec13_tmp[faust_wrap_add(vsize, j29)];
			}
			/* Recursive loop 16 */
			/* Pre code */
			fYec12_idx = (faust_wrap_add(fYec12_idx, fYec12_idx_save)) & 8191;
			for (int j30 = 0; j30 < 4; j30 = faust_wrap_add(j30, 1)) {
				fRec14_tmp[j30] = fRec14_perm[j30];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec12[(faust_wrap_add(i, fYec12_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec14[faust_wrap_sub(i, 1)] + fRec14[faust_wrap_sub(i, 2)]);
				fRec14[i] = fYec12[(faust_wrap_sub(faust_wrap_add(i, fYec12_idx), iSlow18)) & 8191];
			}
			/* Post code */
			fYec12_idx_save = vsize;
			for (int j31 = 0; j31 < 4; j31 = faust_wrap_add(j31, 1)) {
				fRec14_perm[j31] = fRec14_tmp[faust_wrap_add(vsize, j31)];
			}
			/* Recursive loop 17 */
			/* Pre code */
			fYec13_idx = (faust_wrap_add(fYec13_idx, fYec13_idx_save)) & 8191;
			for (int j32 = 0; j32 < 4; j32 = faust_wrap_add(j32, 1)) {
				fRec15_tmp[j32] = fRec15_perm[j32];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec13[(faust_wrap_add(i, fYec13_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec15[faust_wrap_sub(i, 1)] + fRec15[faust_wrap_sub(i, 2)]);
				fRec15[i] = fYec13[(faust_wrap_sub(faust_wrap_add(i, fYec13_idx), iSlow19)) & 8191];
			}
			/* Post code */
			fYec13_idx_save = vsize;
			for (int j33 = 0; j33 < 4; j33 = faust_wrap_add(j33, 1)) {
				fRec15_perm[j33] = fRec15_tmp[faust_wrap_add(vsize, j33)];
			}
			/* Recursive loop 18 */
			/* Pre code */
			fYec14_idx = (faust_wrap_add(fYec14_idx, fYec14_idx_save)) & 8191;
			for (int j34 = 0; j34 < 4; j34 = faust_wrap_add(j34, 1)) {
				fRec16_tmp[j34] = fRec16_perm[j34];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec14[(faust_wrap_add(i, fYec14_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec16[faust_wrap_sub(i, 1)] + fRec16[faust_wrap_sub(i, 2)]);
				fRec16[i] = fYec14[(faust_wrap_sub(faust_wrap_add(i, fYec14_idx), iSlow20)) & 8191];
			}
			/* Post code */
			fYec14_idx_save = vsize;
			for (int j35 = 0; j35 < 4; j35 = faust_wrap_add(j35, 1)) {
				fRec16_perm[j35] = fRec16_tmp[faust_wrap_add(vsize, j35)];
			}
			/* Recursive loop 19 */
			/* Pre code */
			fYec15_idx = (faust_wrap_add(fYec15_idx, fYec15_idx_save)) & 8191;
			for (int j36 = 0; j36 < 4; j36 = faust_wrap_add(j36, 1)) {
				fRec17_tmp[j36] = fRec17_perm[j36];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec15[(faust_wrap_add(i, fYec15_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec17[faust_wrap_sub(i, 1)] + fRec17[faust_wrap_sub(i, 2)]);
				fRec17[i] = fYec15[(faust_wrap_sub(faust_wrap_add(i, fYec15_idx), iSlow21)) & 8191];
			}
			/* Post code */
			fYec15_idx_save = vsize;
			for (int j37 = 0; j37 < 4; j37 = faust_wrap_add(j37, 1)) {
				fRec17_perm[j37] = fRec17_tmp[faust_wrap_add(vsize, j37)];
			}
			/* Vectorizable loop 20 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fSlow22 * (fSlow24 * fRec0[i] + fSlow25 * fRec3[i] + fSlow26 * fRec4[i] + fSlow27 * fRec5[i] + fSlow28 * fRec6[i] + fSlow29 * fRec7[i] + fSlow30 * fRec8[i] + fSlow31 * fRec9[i] + fSlow32 * fRec10[i] + fSlow33 * fRec11[i] + fSlow34 * fRec12[i] + fSlow35 * fRec13[i] + fSlow36 * fRec14[i] + fSlow37 * fRec15[i] + fSlow38 * fRec16[i] + fSlow39 * fRec17[i]));
			}
			/* Recursive loop 21 */
			/* Pre code */
			fYec16_idx = (faust_wrap_add(fYec16_idx, fYec16_idx_save)) & 2047;
			for (int j38 = 0; j38 < 4; j38 = faust_wrap_add(j38, 1)) {
				fRec18_tmp[j38] = fRec18_perm[j38];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec16[(faust_wrap_add(i, fYec16_idx)) & 2047] = fZec0[i] + fSlow2 * (fRec18[faust_wrap_sub(i, 1)] + fRec18[faust_wrap_sub(i, 2)]);
				fRec18[i] = fYec16[(faust_wrap_sub(faust_wrap_add(i, fYec16_idx), iSlow40)) & 2047];
			}
			/* Post code */
			fYec16_idx_save = vsize;
			for (int j39 = 0; j39 < 4; j39 = faust_wrap_add(j39, 1)) {
				fRec18_perm[j39] = fRec18_tmp[faust_wrap_add(vsize, j39)];
			}
			/* Recursive loop 22 */
			/* Pre code */
			fYec17_idx = (faust_wrap_add(fYec17_idx, fYec17_idx_save)) & 4095;
			for (int j40 = 0; j40 < 4; j40 = faust_wrap_add(j40, 1)) {
				fRec19_tmp[j40] = fRec19_perm[j40];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec17[(faust_wrap_add(i, fYec17_idx)) & 4095] = fZec0[i] + fSlow2 * (fRec19[faust_wrap_sub(i, 1)] + fRec19[faust_wrap_sub(i, 2)]);
				fRec19[i] = fYec17[(faust_wrap_sub(faust_wrap_add(i, fYec17_idx), iSlow41)) & 4095];
			}
			/* Post code */
			fYec17_idx_save = vsize;
			for (int j41 = 0; j41 < 4; j41 = faust_wrap_add(j41, 1)) {
				fRec19_perm[j41] = fRec19_tmp[faust_wrap_add(vsize, j41)];
			}
			/* Recursive loop 23 */
			/* Pre code */
			fYec18_idx = (faust_wrap_add(fYec18_idx, fYec18_idx_save)) & 4095;
			for (int j42 = 0; j42 < 4; j42 = faust_wrap_add(j42, 1)) {
				fRec20_tmp[j42] = fRec20_perm[j42];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec18[(faust_wrap_add(i, fYec18_idx)) & 4095] = fZec0[i] + fSlow2 * (fRec20[faust_wrap_sub(i, 1)] + fRec20[faust_wrap_sub(i, 2)]);
				fRec20[i] = fYec18[(faust_wrap_sub(faust_wrap_add(i, fYec18_idx), iSlow42)) & 4095];
			}
			/* Post code */
			fYec18_idx_save = vsize;
			for (int j43 = 0; j43 < 4; j43 = faust_wrap_add(j43, 1)) {
				fRec20_perm[j43] = fRec20_tmp[faust_wrap_add(vsize, j43)];
			}
			/* Recursive loop 24 */
			/* Pre code */
			fYec19_idx = (faust_wrap_add(fYec19_idx, fYec19_idx_save)) & 8191;
			for (int j44 = 0; j44 < 4; j44 = faust_wrap_add(j44, 1)) {
				fRec21_tmp[j44] = fRec21_perm[j44];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec19[(faust_wrap_add(i, fYec19_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec21[faust_wrap_sub(i, 1)] + fRec21[faust_wrap_sub(i, 2)]);
				fRec21[i] = fYec19[(faust_wrap_sub(faust_wrap_add(i, fYec19_idx), iSlow43)) & 8191];
			}
			/* Post code */
			fYec19_idx_save = vsize;
			for (int j45 = 0; j45 < 4; j45 = faust_wrap_add(j45, 1)) {
				fRec21_perm[j45] = fRec21_tmp[faust_wrap_add(vsize, j45)];
			}
			/* Recursive loop 25 */
			/* Pre code */
			fYec20_idx = (faust_wrap_add(fYec20_idx, fYec20_idx_save)) & 8191;
			for (int j46 = 0; j46 < 4; j46 = faust_wrap_add(j46, 1)) {
				fRec22_tmp[j46] = fRec22_perm[j46];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec20[(faust_wrap_add(i, fYec20_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec22[faust_wrap_sub(i, 1)] + fRec22[faust_wrap_sub(i, 2)]);
				fRec22[i] = fYec20[(faust_wrap_sub(faust_wrap_add(i, fYec20_idx), iSlow44)) & 8191];
			}
			/* Post code */
			fYec20_idx_save = vsize;
			for (int j47 = 0; j47 < 4; j47 = faust_wrap_add(j47, 1)) {
				fRec22_perm[j47] = fRec22_tmp[faust_wrap_add(vsize, j47)];
			}
			/* Recursive loop 26 */
			/* Pre code */
			fYec21_idx = (faust_wrap_add(fYec21_idx, fYec21_idx_save)) & 8191;
			for (int j48 = 0; j48 < 4; j48 = faust_wrap_add(j48, 1)) {
				fRec23_tmp[j48] = fRec23_perm[j48];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec21[(faust_wrap_add(i, fYec21_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec23[faust_wrap_sub(i, 1)] + fRec23[faust_wrap_sub(i, 2)]);
				fRec23[i] = fYec21[(faust_wrap_sub(faust_wrap_add(i, fYec21_idx), iSlow45)) & 8191];
			}
			/* Post code */
			fYec21_idx_save = vsize;
			for (int j49 = 0; j49 < 4; j49 = faust_wrap_add(j49, 1)) {
				fRec23_perm[j49] = fRec23_tmp[faust_wrap_add(vsize, j49)];
			}
			/* Recursive loop 27 */
			/* Pre code */
			fYec22_idx = (faust_wrap_add(fYec22_idx, fYec22_idx_save)) & 8191;
			for (int j50 = 0; j50 < 4; j50 = faust_wrap_add(j50, 1)) {
				fRec24_tmp[j50] = fRec24_perm[j50];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec22[(faust_wrap_add(i, fYec22_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec24[faust_wrap_sub(i, 1)] + fRec24[faust_wrap_sub(i, 2)]);
				fRec24[i] = fYec22[(faust_wrap_sub(faust_wrap_add(i, fYec22_idx), iSlow46)) & 8191];
			}
			/* Post code */
			fYec22_idx_save = vsize;
			for (int j51 = 0; j51 < 4; j51 = faust_wrap_add(j51, 1)) {
				fRec24_perm[j51] = fRec24_tmp[faust_wrap_add(vsize, j51)];
			}
			/* Recursive loop 28 */
			/* Pre code */
			fYec23_idx = (faust_wrap_add(fYec23_idx, fYec23_idx_save)) & 8191;
			for (int j52 = 0; j52 < 4; j52 = faust_wrap_add(j52, 1)) {
				fRec25_tmp[j52] = fRec25_perm[j52];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec23[(faust_wrap_add(i, fYec23_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec25[faust_wrap_sub(i, 1)] + fRec25[faust_wrap_sub(i, 2)]);
				fRec25[i] = fYec23[(faust_wrap_sub(faust_wrap_add(i, fYec23_idx), iSlow47)) & 8191];
			}
			/* Post code */
			fYec23_idx_save = vsize;
			for (int j53 = 0; j53 < 4; j53 = faust_wrap_add(j53, 1)) {
				fRec25_perm[j53] = fRec25_tmp[faust_wrap_add(vsize, j53)];
			}
			/* Recursive loop 29 */
			/* Pre code */
			fYec24_idx = (faust_wrap_add(fYec24_idx, fYec24_idx_save)) & 8191;
			for (int j54 = 0; j54 < 4; j54 = faust_wrap_add(j54, 1)) {
				fRec26_tmp[j54] = fRec26_perm[j54];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec24[(faust_wrap_add(i, fYec24_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec26[faust_wrap_sub(i, 1)] + fRec26[faust_wrap_sub(i, 2)]);
				fRec26[i] = fYec24[(faust_wrap_sub(faust_wrap_add(i, fYec24_idx), iSlow48)) & 8191];
			}
			/* Post code */
			fYec24_idx_save = vsize;
			for (int j55 = 0; j55 < 4; j55 = faust_wrap_add(j55, 1)) {
				fRec26_perm[j55] = fRec26_tmp[faust_wrap_add(vsize, j55)];
			}
			/* Recursive loop 30 */
			/* Pre code */
			fYec25_idx = (faust_wrap_add(fYec25_idx, fYec25_idx_save)) & 8191;
			for (int j56 = 0; j56 < 4; j56 = faust_wrap_add(j56, 1)) {
				fRec27_tmp[j56] = fRec27_perm[j56];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec25[(faust_wrap_add(i, fYec25_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec27[faust_wrap_sub(i, 1)] + fRec27[faust_wrap_sub(i, 2)]);
				fRec27[i] = fYec25[(faust_wrap_sub(faust_wrap_add(i, fYec25_idx), iSlow49)) & 8191];
			}
			/* Post code */
			fYec25_idx_save = vsize;
			for (int j57 = 0; j57 < 4; j57 = faust_wrap_add(j57, 1)) {
				fRec27_perm[j57] = fRec27_tmp[faust_wrap_add(vsize, j57)];
			}
			/* Recursive loop 31 */
			/* Pre code */
			fYec26_idx = (faust_wrap_add(fYec26_idx, fYec26_idx_save)) & 8191;
			for (int j58 = 0; j58 < 4; j58 = faust_wrap_add(j58, 1)) {
				fRec28_tmp[j58] = fRec28_perm[j58];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec26[(faust_wrap_add(i, fYec26_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec28[faust_wrap_sub(i, 1)] + fRec28[faust_wrap_sub(i, 2)]);
				fRec28[i] = fYec26[(faust_wrap_sub(faust_wrap_add(i, fYec26_idx), iSlow50)) & 8191];
			}
			/* Post code */
			fYec26_idx_save = vsize;
			for (int j59 = 0; j59 < 4; j59 = faust_wrap_add(j59, 1)) {
				fRec28_perm[j59] = fRec28_tmp[faust_wrap_add(vsize, j59)];
			}
			/* Recursive loop 32 */
			/* Pre code */
			fYec27_idx = (faust_wrap_add(fYec27_idx, fYec27_idx_save)) & 8191;
			for (int j60 = 0; j60 < 4; j60 = faust_wrap_add(j60, 1)) {
				fRec29_tmp[j60] = fRec29_perm[j60];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec27[(faust_wrap_add(i, fYec27_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec29[faust_wrap_sub(i, 1)] + fRec29[faust_wrap_sub(i, 2)]);
				fRec29[i] = fYec27[(faust_wrap_sub(faust_wrap_add(i, fYec27_idx), iSlow51)) & 8191];
			}
			/* Post code */
			fYec27_idx_save = vsize;
			for (int j61 = 0; j61 < 4; j61 = faust_wrap_add(j61, 1)) {
				fRec29_perm[j61] = fRec29_tmp[faust_wrap_add(vsize, j61)];
			}
			/* Recursive loop 33 */
			/* Pre code */
			fYec28_idx = (faust_wrap_add(fYec28_idx, fYec28_idx_save)) & 8191;
			for (int j62 = 0; j62 < 4; j62 = faust_wrap_add(j62, 1)) {
				fRec30_tmp[j62] = fRec30_perm[j62];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec28[(faust_wrap_add(i, fYec28_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec30[faust_wrap_sub(i, 1)] + fRec30[faust_wrap_sub(i, 2)]);
				fRec30[i] = fYec28[(faust_wrap_sub(faust_wrap_add(i, fYec28_idx), iSlow52)) & 8191];
			}
			/* Post code */
			fYec28_idx_save = vsize;
			for (int j63 = 0; j63 < 4; j63 = faust_wrap_add(j63, 1)) {
				fRec30_perm[j63] = fRec30_tmp[faust_wrap_add(vsize, j63)];
			}
			/* Recursive loop 34 */
			/* Pre code */
			fYec29_idx = (faust_wrap_add(fYec29_idx, fYec29_idx_save)) & 8191;
			for (int j64 = 0; j64 < 4; j64 = faust_wrap_add(j64, 1)) {
				fRec31_tmp[j64] = fRec31_perm[j64];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec29[(faust_wrap_add(i, fYec29_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec31[faust_wrap_sub(i, 1)] + fRec31[faust_wrap_sub(i, 2)]);
				fRec31[i] = fYec29[(faust_wrap_sub(faust_wrap_add(i, fYec29_idx), iSlow53)) & 8191];
			}
			/* Post code */
			fYec29_idx_save = vsize;
			for (int j65 = 0; j65 < 4; j65 = faust_wrap_add(j65, 1)) {
				fRec31_perm[j65] = fRec31_tmp[faust_wrap_add(vsize, j65)];
			}
			/* Recursive loop 35 */
			/* Pre code */
			fYec30_idx = (faust_wrap_add(fYec30_idx, fYec30_idx_save)) & 8191;
			for (int j66 = 0; j66 < 4; j66 = faust_wrap_add(j66, 1)) {
				fRec32_tmp[j66] = fRec32_perm[j66];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec30[(faust_wrap_add(i, fYec30_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec32[faust_wrap_sub(i, 1)] + fRec32[faust_wrap_sub(i, 2)]);
				fRec32[i] = fYec30[(faust_wrap_sub(faust_wrap_add(i, fYec30_idx), iSlow54)) & 8191];
			}
			/* Post code */
			fYec30_idx_save = vsize;
			for (int j67 = 0; j67 < 4; j67 = faust_wrap_add(j67, 1)) {
				fRec32_perm[j67] = fRec32_tmp[faust_wrap_add(vsize, j67)];
			}
			/* Recursive loop 36 */
			/* Pre code */
			fYec31_idx = (faust_wrap_add(fYec31_idx, fYec31_idx_save)) & 8191;
			for (int j68 = 0; j68 < 4; j68 = faust_wrap_add(j68, 1)) {
				fRec33_tmp[j68] = fRec33_perm[j68];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec31[(faust_wrap_add(i, fYec31_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec33[faust_wrap_sub(i, 1)] + fRec33[faust_wrap_sub(i, 2)]);
				fRec33[i] = fYec31[(faust_wrap_sub(faust_wrap_add(i, fYec31_idx), iSlow55)) & 8191];
			}
			/* Post code */
			fYec31_idx_save = vsize;
			for (int j69 = 0; j69 < 4; j69 = faust_wrap_add(j69, 1)) {
				fRec33_perm[j69] = fRec33_tmp[faust_wrap_add(vsize, j69)];
			}
			/* Vectorizable loop 37 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fSlow22 * (fSlow56 * fRec18[i] + fSlow57 * fRec19[i] + fSlow58 * fRec20[i] + fSlow59 * fRec21[i] + fSlow60 * fRec22[i] + fSlow61 * fRec23[i] + fSlow62 * fRec24[i] + fSlow63 * fRec25[i] + fSlow64 * fRec26[i] + fSlow65 * fRec27[i] + fSlow66 * fRec28[i] + fSlow67 * fRec29[i] + fSlow68 * fRec30[i] + fSlow69 * fRec31[i] + fSlow70 * fRec32[i] + fSlow71 * fRec33[i]));
			}
		}
		/* Remaining frames */
		if (vindex < count) {
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			FAUSTFLOAT* output1 = &output1_ptr[vindex];
			int vsize = faust_wrap_sub(count, vindex);
			/* Recursive loop 0 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				iRec1_tmp[j0] = iRec1_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iRec1[i] = faust_wrap_add(faust_wrap_mul(1103515245, iRec1[faust_wrap_sub(i, 1)]), 12345);
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				iRec1_perm[j1] = iRec1_tmp[faust_wrap_add(vsize, j1)];
			}
			/* Vectorizable loop 1 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fVec0_tmp[j2] = fVec0_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVec0[i] = fSlow0;
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fVec0_perm[j3] = fVec0_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Recursive loop 2 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				fRec2_tmp[j4] = fRec2_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec2[i] = fRec2[faust_wrap_sub(i, 1)] + static_cast<double>((fSlow0 - fVec0[faust_wrap_sub(i, 1)]) > 0.0) - fSlow1 * static_cast<double>(fRec2[faust_wrap_sub(i, 1)] > 0.0);
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fRec2_perm[j5] = fRec2_tmp[faust_wrap_add(vsize, j5)];
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec0[i] = fSlow3 * static_cast<double>(iRec1[i]) * (static_cast<double>(fRec2[i] > 0.0) + 1.52587890625e-05);
			}
			/* Recursive loop 4 */
			/* Pre code */
			fYec0_idx = (faust_wrap_add(fYec0_idx, fYec0_idx_save)) & 1023;
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec0_tmp[j6] = fRec0_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec0[(faust_wrap_add(i, fYec0_idx)) & 1023] = fSlow2 * (fRec0[faust_wrap_sub(i, 1)] + fRec0[faust_wrap_sub(i, 2)]) + fZec0[i];
				fRec0[i] = fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), iSlow5)) & 1023];
			}
			/* Post code */
			fYec0_idx_save = vsize;
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec0_perm[j7] = fRec0_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Recursive loop 5 */
			/* Pre code */
			fYec1_idx = (faust_wrap_add(fYec1_idx, fYec1_idx_save)) & 2047;
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fRec3_tmp[j8] = fRec3_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec1[(faust_wrap_add(i, fYec1_idx)) & 2047] = fZec0[i] + fSlow2 * (fRec3[faust_wrap_sub(i, 1)] + fRec3[faust_wrap_sub(i, 2)]);
				fRec3[i] = fYec1[(faust_wrap_sub(faust_wrap_add(i, fYec1_idx), iSlow7)) & 2047];
			}
			/* Post code */
			fYec1_idx_save = vsize;
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fRec3_perm[j9] = fRec3_tmp[faust_wrap_add(vsize, j9)];
			}
			/* Recursive loop 6 */
			/* Pre code */
			fYec2_idx = (faust_wrap_add(fYec2_idx, fYec2_idx_save)) & 4095;
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				fRec4_tmp[j10] = fRec4_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec2[(faust_wrap_add(i, fYec2_idx)) & 4095] = fZec0[i] + fSlow2 * (fRec4[faust_wrap_sub(i, 1)] + fRec4[faust_wrap_sub(i, 2)]);
				fRec4[i] = fYec2[(faust_wrap_sub(faust_wrap_add(i, fYec2_idx), iSlow8)) & 4095];
			}
			/* Post code */
			fYec2_idx_save = vsize;
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				fRec4_perm[j11] = fRec4_tmp[faust_wrap_add(vsize, j11)];
			}
			/* Recursive loop 7 */
			/* Pre code */
			fYec3_idx = (faust_wrap_add(fYec3_idx, fYec3_idx_save)) & 4095;
			for (int j12 = 0; j12 < 4; j12 = faust_wrap_add(j12, 1)) {
				fRec5_tmp[j12] = fRec5_perm[j12];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec3[(faust_wrap_add(i, fYec3_idx)) & 4095] = fZec0[i] + fSlow2 * (fRec5[faust_wrap_sub(i, 1)] + fRec5[faust_wrap_sub(i, 2)]);
				fRec5[i] = fYec3[(faust_wrap_sub(faust_wrap_add(i, fYec3_idx), iSlow9)) & 4095];
			}
			/* Post code */
			fYec3_idx_save = vsize;
			for (int j13 = 0; j13 < 4; j13 = faust_wrap_add(j13, 1)) {
				fRec5_perm[j13] = fRec5_tmp[faust_wrap_add(vsize, j13)];
			}
			/* Recursive loop 8 */
			/* Pre code */
			fYec4_idx = (faust_wrap_add(fYec4_idx, fYec4_idx_save)) & 8191;
			for (int j14 = 0; j14 < 4; j14 = faust_wrap_add(j14, 1)) {
				fRec6_tmp[j14] = fRec6_perm[j14];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec4[(faust_wrap_add(i, fYec4_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec6[faust_wrap_sub(i, 1)] + fRec6[faust_wrap_sub(i, 2)]);
				fRec6[i] = fYec4[(faust_wrap_sub(faust_wrap_add(i, fYec4_idx), iSlow10)) & 8191];
			}
			/* Post code */
			fYec4_idx_save = vsize;
			for (int j15 = 0; j15 < 4; j15 = faust_wrap_add(j15, 1)) {
				fRec6_perm[j15] = fRec6_tmp[faust_wrap_add(vsize, j15)];
			}
			/* Recursive loop 9 */
			/* Pre code */
			fYec5_idx = (faust_wrap_add(fYec5_idx, fYec5_idx_save)) & 8191;
			for (int j16 = 0; j16 < 4; j16 = faust_wrap_add(j16, 1)) {
				fRec7_tmp[j16] = fRec7_perm[j16];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec5[(faust_wrap_add(i, fYec5_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec7[faust_wrap_sub(i, 1)] + fRec7[faust_wrap_sub(i, 2)]);
				fRec7[i] = fYec5[(faust_wrap_sub(faust_wrap_add(i, fYec5_idx), iSlow11)) & 8191];
			}
			/* Post code */
			fYec5_idx_save = vsize;
			for (int j17 = 0; j17 < 4; j17 = faust_wrap_add(j17, 1)) {
				fRec7_perm[j17] = fRec7_tmp[faust_wrap_add(vsize, j17)];
			}
			/* Recursive loop 10 */
			/* Pre code */
			fYec6_idx = (faust_wrap_add(fYec6_idx, fYec6_idx_save)) & 8191;
			for (int j18 = 0; j18 < 4; j18 = faust_wrap_add(j18, 1)) {
				fRec8_tmp[j18] = fRec8_perm[j18];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec6[(faust_wrap_add(i, fYec6_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec8[faust_wrap_sub(i, 1)] + fRec8[faust_wrap_sub(i, 2)]);
				fRec8[i] = fYec6[(faust_wrap_sub(faust_wrap_add(i, fYec6_idx), iSlow12)) & 8191];
			}
			/* Post code */
			fYec6_idx_save = vsize;
			for (int j19 = 0; j19 < 4; j19 = faust_wrap_add(j19, 1)) {
				fRec8_perm[j19] = fRec8_tmp[faust_wrap_add(vsize, j19)];
			}
			/* Recursive loop 11 */
			/* Pre code */
			fYec7_idx = (faust_wrap_add(fYec7_idx, fYec7_idx_save)) & 8191;
			for (int j20 = 0; j20 < 4; j20 = faust_wrap_add(j20, 1)) {
				fRec9_tmp[j20] = fRec9_perm[j20];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec7[(faust_wrap_add(i, fYec7_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec9[faust_wrap_sub(i, 1)] + fRec9[faust_wrap_sub(i, 2)]);
				fRec9[i] = fYec7[(faust_wrap_sub(faust_wrap_add(i, fYec7_idx), iSlow13)) & 8191];
			}
			/* Post code */
			fYec7_idx_save = vsize;
			for (int j21 = 0; j21 < 4; j21 = faust_wrap_add(j21, 1)) {
				fRec9_perm[j21] = fRec9_tmp[faust_wrap_add(vsize, j21)];
			}
			/* Recursive loop 12 */
			/* Pre code */
			fYec8_idx = (faust_wrap_add(fYec8_idx, fYec8_idx_save)) & 8191;
			for (int j22 = 0; j22 < 4; j22 = faust_wrap_add(j22, 1)) {
				fRec10_tmp[j22] = fRec10_perm[j22];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec8[(faust_wrap_add(i, fYec8_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec10[faust_wrap_sub(i, 1)] + fRec10[faust_wrap_sub(i, 2)]);
				fRec10[i] = fYec8[(faust_wrap_sub(faust_wrap_add(i, fYec8_idx), iSlow14)) & 8191];
			}
			/* Post code */
			fYec8_idx_save = vsize;
			for (int j23 = 0; j23 < 4; j23 = faust_wrap_add(j23, 1)) {
				fRec10_perm[j23] = fRec10_tmp[faust_wrap_add(vsize, j23)];
			}
			/* Recursive loop 13 */
			/* Pre code */
			fYec9_idx = (faust_wrap_add(fYec9_idx, fYec9_idx_save)) & 8191;
			for (int j24 = 0; j24 < 4; j24 = faust_wrap_add(j24, 1)) {
				fRec11_tmp[j24] = fRec11_perm[j24];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec9[(faust_wrap_add(i, fYec9_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec11[faust_wrap_sub(i, 1)] + fRec11[faust_wrap_sub(i, 2)]);
				fRec11[i] = fYec9[(faust_wrap_sub(faust_wrap_add(i, fYec9_idx), iSlow15)) & 8191];
			}
			/* Post code */
			fYec9_idx_save = vsize;
			for (int j25 = 0; j25 < 4; j25 = faust_wrap_add(j25, 1)) {
				fRec11_perm[j25] = fRec11_tmp[faust_wrap_add(vsize, j25)];
			}
			/* Recursive loop 14 */
			/* Pre code */
			fYec10_idx = (faust_wrap_add(fYec10_idx, fYec10_idx_save)) & 8191;
			for (int j26 = 0; j26 < 4; j26 = faust_wrap_add(j26, 1)) {
				fRec12_tmp[j26] = fRec12_perm[j26];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec10[(faust_wrap_add(i, fYec10_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec12[faust_wrap_sub(i, 1)] + fRec12[faust_wrap_sub(i, 2)]);
				fRec12[i] = fYec10[(faust_wrap_sub(faust_wrap_add(i, fYec10_idx), iSlow16)) & 8191];
			}
			/* Post code */
			fYec10_idx_save = vsize;
			for (int j27 = 0; j27 < 4; j27 = faust_wrap_add(j27, 1)) {
				fRec12_perm[j27] = fRec12_tmp[faust_wrap_add(vsize, j27)];
			}
			/* Recursive loop 15 */
			/* Pre code */
			fYec11_idx = (faust_wrap_add(fYec11_idx, fYec11_idx_save)) & 8191;
			for (int j28 = 0; j28 < 4; j28 = faust_wrap_add(j28, 1)) {
				fRec13_tmp[j28] = fRec13_perm[j28];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec11[(faust_wrap_add(i, fYec11_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec13[faust_wrap_sub(i, 1)] + fRec13[faust_wrap_sub(i, 2)]);
				fRec13[i] = fYec11[(faust_wrap_sub(faust_wrap_add(i, fYec11_idx), iSlow17)) & 8191];
			}
			/* Post code */
			fYec11_idx_save = vsize;
			for (int j29 = 0; j29 < 4; j29 = faust_wrap_add(j29, 1)) {
				fRec13_perm[j29] = fRec13_tmp[faust_wrap_add(vsize, j29)];
			}
			/* Recursive loop 16 */
			/* Pre code */
			fYec12_idx = (faust_wrap_add(fYec12_idx, fYec12_idx_save)) & 8191;
			for (int j30 = 0; j30 < 4; j30 = faust_wrap_add(j30, 1)) {
				fRec14_tmp[j30] = fRec14_perm[j30];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec12[(faust_wrap_add(i, fYec12_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec14[faust_wrap_sub(i, 1)] + fRec14[faust_wrap_sub(i, 2)]);
				fRec14[i] = fYec12[(faust_wrap_sub(faust_wrap_add(i, fYec12_idx), iSlow18)) & 8191];
			}
			/* Post code */
			fYec12_idx_save = vsize;
			for (int j31 = 0; j31 < 4; j31 = faust_wrap_add(j31, 1)) {
				fRec14_perm[j31] = fRec14_tmp[faust_wrap_add(vsize, j31)];
			}
			/* Recursive loop 17 */
			/* Pre code */
			fYec13_idx = (faust_wrap_add(fYec13_idx, fYec13_idx_save)) & 8191;
			for (int j32 = 0; j32 < 4; j32 = faust_wrap_add(j32, 1)) {
				fRec15_tmp[j32] = fRec15_perm[j32];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec13[(faust_wrap_add(i, fYec13_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec15[faust_wrap_sub(i, 1)] + fRec15[faust_wrap_sub(i, 2)]);
				fRec15[i] = fYec13[(faust_wrap_sub(faust_wrap_add(i, fYec13_idx), iSlow19)) & 8191];
			}
			/* Post code */
			fYec13_idx_save = vsize;
			for (int j33 = 0; j33 < 4; j33 = faust_wrap_add(j33, 1)) {
				fRec15_perm[j33] = fRec15_tmp[faust_wrap_add(vsize, j33)];
			}
			/* Recursive loop 18 */
			/* Pre code */
			fYec14_idx = (faust_wrap_add(fYec14_idx, fYec14_idx_save)) & 8191;
			for (int j34 = 0; j34 < 4; j34 = faust_wrap_add(j34, 1)) {
				fRec16_tmp[j34] = fRec16_perm[j34];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec14[(faust_wrap_add(i, fYec14_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec16[faust_wrap_sub(i, 1)] + fRec16[faust_wrap_sub(i, 2)]);
				fRec16[i] = fYec14[(faust_wrap_sub(faust_wrap_add(i, fYec14_idx), iSlow20)) & 8191];
			}
			/* Post code */
			fYec14_idx_save = vsize;
			for (int j35 = 0; j35 < 4; j35 = faust_wrap_add(j35, 1)) {
				fRec16_perm[j35] = fRec16_tmp[faust_wrap_add(vsize, j35)];
			}
			/* Recursive loop 19 */
			/* Pre code */
			fYec15_idx = (faust_wrap_add(fYec15_idx, fYec15_idx_save)) & 8191;
			for (int j36 = 0; j36 < 4; j36 = faust_wrap_add(j36, 1)) {
				fRec17_tmp[j36] = fRec17_perm[j36];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec15[(faust_wrap_add(i, fYec15_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec17[faust_wrap_sub(i, 1)] + fRec17[faust_wrap_sub(i, 2)]);
				fRec17[i] = fYec15[(faust_wrap_sub(faust_wrap_add(i, fYec15_idx), iSlow21)) & 8191];
			}
			/* Post code */
			fYec15_idx_save = vsize;
			for (int j37 = 0; j37 < 4; j37 = faust_wrap_add(j37, 1)) {
				fRec17_perm[j37] = fRec17_tmp[faust_wrap_add(vsize, j37)];
			}
			/* Vectorizable loop 20 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fSlow22 * (fSlow24 * fRec0[i] + fSlow25 * fRec3[i] + fSlow26 * fRec4[i] + fSlow27 * fRec5[i] + fSlow28 * fRec6[i] + fSlow29 * fRec7[i] + fSlow30 * fRec8[i] + fSlow31 * fRec9[i] + fSlow32 * fRec10[i] + fSlow33 * fRec11[i] + fSlow34 * fRec12[i] + fSlow35 * fRec13[i] + fSlow36 * fRec14[i] + fSlow37 * fRec15[i] + fSlow38 * fRec16[i] + fSlow39 * fRec17[i]));
			}
			/* Recursive loop 21 */
			/* Pre code */
			fYec16_idx = (faust_wrap_add(fYec16_idx, fYec16_idx_save)) & 2047;
			for (int j38 = 0; j38 < 4; j38 = faust_wrap_add(j38, 1)) {
				fRec18_tmp[j38] = fRec18_perm[j38];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec16[(faust_wrap_add(i, fYec16_idx)) & 2047] = fZec0[i] + fSlow2 * (fRec18[faust_wrap_sub(i, 1)] + fRec18[faust_wrap_sub(i, 2)]);
				fRec18[i] = fYec16[(faust_wrap_sub(faust_wrap_add(i, fYec16_idx), iSlow40)) & 2047];
			}
			/* Post code */
			fYec16_idx_save = vsize;
			for (int j39 = 0; j39 < 4; j39 = faust_wrap_add(j39, 1)) {
				fRec18_perm[j39] = fRec18_tmp[faust_wrap_add(vsize, j39)];
			}
			/* Recursive loop 22 */
			/* Pre code */
			fYec17_idx = (faust_wrap_add(fYec17_idx, fYec17_idx_save)) & 4095;
			for (int j40 = 0; j40 < 4; j40 = faust_wrap_add(j40, 1)) {
				fRec19_tmp[j40] = fRec19_perm[j40];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec17[(faust_wrap_add(i, fYec17_idx)) & 4095] = fZec0[i] + fSlow2 * (fRec19[faust_wrap_sub(i, 1)] + fRec19[faust_wrap_sub(i, 2)]);
				fRec19[i] = fYec17[(faust_wrap_sub(faust_wrap_add(i, fYec17_idx), iSlow41)) & 4095];
			}
			/* Post code */
			fYec17_idx_save = vsize;
			for (int j41 = 0; j41 < 4; j41 = faust_wrap_add(j41, 1)) {
				fRec19_perm[j41] = fRec19_tmp[faust_wrap_add(vsize, j41)];
			}
			/* Recursive loop 23 */
			/* Pre code */
			fYec18_idx = (faust_wrap_add(fYec18_idx, fYec18_idx_save)) & 4095;
			for (int j42 = 0; j42 < 4; j42 = faust_wrap_add(j42, 1)) {
				fRec20_tmp[j42] = fRec20_perm[j42];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec18[(faust_wrap_add(i, fYec18_idx)) & 4095] = fZec0[i] + fSlow2 * (fRec20[faust_wrap_sub(i, 1)] + fRec20[faust_wrap_sub(i, 2)]);
				fRec20[i] = fYec18[(faust_wrap_sub(faust_wrap_add(i, fYec18_idx), iSlow42)) & 4095];
			}
			/* Post code */
			fYec18_idx_save = vsize;
			for (int j43 = 0; j43 < 4; j43 = faust_wrap_add(j43, 1)) {
				fRec20_perm[j43] = fRec20_tmp[faust_wrap_add(vsize, j43)];
			}
			/* Recursive loop 24 */
			/* Pre code */
			fYec19_idx = (faust_wrap_add(fYec19_idx, fYec19_idx_save)) & 8191;
			for (int j44 = 0; j44 < 4; j44 = faust_wrap_add(j44, 1)) {
				fRec21_tmp[j44] = fRec21_perm[j44];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec19[(faust_wrap_add(i, fYec19_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec21[faust_wrap_sub(i, 1)] + fRec21[faust_wrap_sub(i, 2)]);
				fRec21[i] = fYec19[(faust_wrap_sub(faust_wrap_add(i, fYec19_idx), iSlow43)) & 8191];
			}
			/* Post code */
			fYec19_idx_save = vsize;
			for (int j45 = 0; j45 < 4; j45 = faust_wrap_add(j45, 1)) {
				fRec21_perm[j45] = fRec21_tmp[faust_wrap_add(vsize, j45)];
			}
			/* Recursive loop 25 */
			/* Pre code */
			fYec20_idx = (faust_wrap_add(fYec20_idx, fYec20_idx_save)) & 8191;
			for (int j46 = 0; j46 < 4; j46 = faust_wrap_add(j46, 1)) {
				fRec22_tmp[j46] = fRec22_perm[j46];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec20[(faust_wrap_add(i, fYec20_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec22[faust_wrap_sub(i, 1)] + fRec22[faust_wrap_sub(i, 2)]);
				fRec22[i] = fYec20[(faust_wrap_sub(faust_wrap_add(i, fYec20_idx), iSlow44)) & 8191];
			}
			/* Post code */
			fYec20_idx_save = vsize;
			for (int j47 = 0; j47 < 4; j47 = faust_wrap_add(j47, 1)) {
				fRec22_perm[j47] = fRec22_tmp[faust_wrap_add(vsize, j47)];
			}
			/* Recursive loop 26 */
			/* Pre code */
			fYec21_idx = (faust_wrap_add(fYec21_idx, fYec21_idx_save)) & 8191;
			for (int j48 = 0; j48 < 4; j48 = faust_wrap_add(j48, 1)) {
				fRec23_tmp[j48] = fRec23_perm[j48];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec21[(faust_wrap_add(i, fYec21_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec23[faust_wrap_sub(i, 1)] + fRec23[faust_wrap_sub(i, 2)]);
				fRec23[i] = fYec21[(faust_wrap_sub(faust_wrap_add(i, fYec21_idx), iSlow45)) & 8191];
			}
			/* Post code */
			fYec21_idx_save = vsize;
			for (int j49 = 0; j49 < 4; j49 = faust_wrap_add(j49, 1)) {
				fRec23_perm[j49] = fRec23_tmp[faust_wrap_add(vsize, j49)];
			}
			/* Recursive loop 27 */
			/* Pre code */
			fYec22_idx = (faust_wrap_add(fYec22_idx, fYec22_idx_save)) & 8191;
			for (int j50 = 0; j50 < 4; j50 = faust_wrap_add(j50, 1)) {
				fRec24_tmp[j50] = fRec24_perm[j50];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec22[(faust_wrap_add(i, fYec22_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec24[faust_wrap_sub(i, 1)] + fRec24[faust_wrap_sub(i, 2)]);
				fRec24[i] = fYec22[(faust_wrap_sub(faust_wrap_add(i, fYec22_idx), iSlow46)) & 8191];
			}
			/* Post code */
			fYec22_idx_save = vsize;
			for (int j51 = 0; j51 < 4; j51 = faust_wrap_add(j51, 1)) {
				fRec24_perm[j51] = fRec24_tmp[faust_wrap_add(vsize, j51)];
			}
			/* Recursive loop 28 */
			/* Pre code */
			fYec23_idx = (faust_wrap_add(fYec23_idx, fYec23_idx_save)) & 8191;
			for (int j52 = 0; j52 < 4; j52 = faust_wrap_add(j52, 1)) {
				fRec25_tmp[j52] = fRec25_perm[j52];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec23[(faust_wrap_add(i, fYec23_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec25[faust_wrap_sub(i, 1)] + fRec25[faust_wrap_sub(i, 2)]);
				fRec25[i] = fYec23[(faust_wrap_sub(faust_wrap_add(i, fYec23_idx), iSlow47)) & 8191];
			}
			/* Post code */
			fYec23_idx_save = vsize;
			for (int j53 = 0; j53 < 4; j53 = faust_wrap_add(j53, 1)) {
				fRec25_perm[j53] = fRec25_tmp[faust_wrap_add(vsize, j53)];
			}
			/* Recursive loop 29 */
			/* Pre code */
			fYec24_idx = (faust_wrap_add(fYec24_idx, fYec24_idx_save)) & 8191;
			for (int j54 = 0; j54 < 4; j54 = faust_wrap_add(j54, 1)) {
				fRec26_tmp[j54] = fRec26_perm[j54];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec24[(faust_wrap_add(i, fYec24_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec26[faust_wrap_sub(i, 1)] + fRec26[faust_wrap_sub(i, 2)]);
				fRec26[i] = fYec24[(faust_wrap_sub(faust_wrap_add(i, fYec24_idx), iSlow48)) & 8191];
			}
			/* Post code */
			fYec24_idx_save = vsize;
			for (int j55 = 0; j55 < 4; j55 = faust_wrap_add(j55, 1)) {
				fRec26_perm[j55] = fRec26_tmp[faust_wrap_add(vsize, j55)];
			}
			/* Recursive loop 30 */
			/* Pre code */
			fYec25_idx = (faust_wrap_add(fYec25_idx, fYec25_idx_save)) & 8191;
			for (int j56 = 0; j56 < 4; j56 = faust_wrap_add(j56, 1)) {
				fRec27_tmp[j56] = fRec27_perm[j56];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec25[(faust_wrap_add(i, fYec25_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec27[faust_wrap_sub(i, 1)] + fRec27[faust_wrap_sub(i, 2)]);
				fRec27[i] = fYec25[(faust_wrap_sub(faust_wrap_add(i, fYec25_idx), iSlow49)) & 8191];
			}
			/* Post code */
			fYec25_idx_save = vsize;
			for (int j57 = 0; j57 < 4; j57 = faust_wrap_add(j57, 1)) {
				fRec27_perm[j57] = fRec27_tmp[faust_wrap_add(vsize, j57)];
			}
			/* Recursive loop 31 */
			/* Pre code */
			fYec26_idx = (faust_wrap_add(fYec26_idx, fYec26_idx_save)) & 8191;
			for (int j58 = 0; j58 < 4; j58 = faust_wrap_add(j58, 1)) {
				fRec28_tmp[j58] = fRec28_perm[j58];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec26[(faust_wrap_add(i, fYec26_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec28[faust_wrap_sub(i, 1)] + fRec28[faust_wrap_sub(i, 2)]);
				fRec28[i] = fYec26[(faust_wrap_sub(faust_wrap_add(i, fYec26_idx), iSlow50)) & 8191];
			}
			/* Post code */
			fYec26_idx_save = vsize;
			for (int j59 = 0; j59 < 4; j59 = faust_wrap_add(j59, 1)) {
				fRec28_perm[j59] = fRec28_tmp[faust_wrap_add(vsize, j59)];
			}
			/* Recursive loop 32 */
			/* Pre code */
			fYec27_idx = (faust_wrap_add(fYec27_idx, fYec27_idx_save)) & 8191;
			for (int j60 = 0; j60 < 4; j60 = faust_wrap_add(j60, 1)) {
				fRec29_tmp[j60] = fRec29_perm[j60];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec27[(faust_wrap_add(i, fYec27_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec29[faust_wrap_sub(i, 1)] + fRec29[faust_wrap_sub(i, 2)]);
				fRec29[i] = fYec27[(faust_wrap_sub(faust_wrap_add(i, fYec27_idx), iSlow51)) & 8191];
			}
			/* Post code */
			fYec27_idx_save = vsize;
			for (int j61 = 0; j61 < 4; j61 = faust_wrap_add(j61, 1)) {
				fRec29_perm[j61] = fRec29_tmp[faust_wrap_add(vsize, j61)];
			}
			/* Recursive loop 33 */
			/* Pre code */
			fYec28_idx = (faust_wrap_add(fYec28_idx, fYec28_idx_save)) & 8191;
			for (int j62 = 0; j62 < 4; j62 = faust_wrap_add(j62, 1)) {
				fRec30_tmp[j62] = fRec30_perm[j62];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec28[(faust_wrap_add(i, fYec28_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec30[faust_wrap_sub(i, 1)] + fRec30[faust_wrap_sub(i, 2)]);
				fRec30[i] = fYec28[(faust_wrap_sub(faust_wrap_add(i, fYec28_idx), iSlow52)) & 8191];
			}
			/* Post code */
			fYec28_idx_save = vsize;
			for (int j63 = 0; j63 < 4; j63 = faust_wrap_add(j63, 1)) {
				fRec30_perm[j63] = fRec30_tmp[faust_wrap_add(vsize, j63)];
			}
			/* Recursive loop 34 */
			/* Pre code */
			fYec29_idx = (faust_wrap_add(fYec29_idx, fYec29_idx_save)) & 8191;
			for (int j64 = 0; j64 < 4; j64 = faust_wrap_add(j64, 1)) {
				fRec31_tmp[j64] = fRec31_perm[j64];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec29[(faust_wrap_add(i, fYec29_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec31[faust_wrap_sub(i, 1)] + fRec31[faust_wrap_sub(i, 2)]);
				fRec31[i] = fYec29[(faust_wrap_sub(faust_wrap_add(i, fYec29_idx), iSlow53)) & 8191];
			}
			/* Post code */
			fYec29_idx_save = vsize;
			for (int j65 = 0; j65 < 4; j65 = faust_wrap_add(j65, 1)) {
				fRec31_perm[j65] = fRec31_tmp[faust_wrap_add(vsize, j65)];
			}
			/* Recursive loop 35 */
			/* Pre code */
			fYec30_idx = (faust_wrap_add(fYec30_idx, fYec30_idx_save)) & 8191;
			for (int j66 = 0; j66 < 4; j66 = faust_wrap_add(j66, 1)) {
				fRec32_tmp[j66] = fRec32_perm[j66];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec30[(faust_wrap_add(i, fYec30_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec32[faust_wrap_sub(i, 1)] + fRec32[faust_wrap_sub(i, 2)]);
				fRec32[i] = fYec30[(faust_wrap_sub(faust_wrap_add(i, fYec30_idx), iSlow54)) & 8191];
			}
			/* Post code */
			fYec30_idx_save = vsize;
			for (int j67 = 0; j67 < 4; j67 = faust_wrap_add(j67, 1)) {
				fRec32_perm[j67] = fRec32_tmp[faust_wrap_add(vsize, j67)];
			}
			/* Recursive loop 36 */
			/* Pre code */
			fYec31_idx = (faust_wrap_add(fYec31_idx, fYec31_idx_save)) & 8191;
			for (int j68 = 0; j68 < 4; j68 = faust_wrap_add(j68, 1)) {
				fRec33_tmp[j68] = fRec33_perm[j68];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec31[(faust_wrap_add(i, fYec31_idx)) & 8191] = fZec0[i] + fSlow2 * (fRec33[faust_wrap_sub(i, 1)] + fRec33[faust_wrap_sub(i, 2)]);
				fRec33[i] = fYec31[(faust_wrap_sub(faust_wrap_add(i, fYec31_idx), iSlow55)) & 8191];
			}
			/* Post code */
			fYec31_idx_save = vsize;
			for (int j69 = 0; j69 < 4; j69 = faust_wrap_add(j69, 1)) {
				fRec33_perm[j69] = fRec33_tmp[faust_wrap_add(vsize, j69)];
			}
			/* Vectorizable loop 37 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fSlow22 * (fSlow56 * fRec18[i] + fSlow57 * fRec19[i] + fSlow58 * fRec20[i] + fSlow59 * fRec21[i] + fSlow60 * fRec22[i] + fSlow61 * fRec23[i] + fSlow62 * fRec24[i] + fSlow63 * fRec25[i] + fSlow64 * fRec26[i] + fSlow65 * fRec27[i] + fSlow66 * fRec28[i] + fSlow67 * fRec29[i] + fSlow68 * fRec30[i] + fSlow69 * fRec31[i] + fSlow70 * fRec32[i] + fSlow71 * fRec33[i]));
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
