/* ------------------------------------------------------------
author: "Grame"
copyright: "(c) GRAME 2006"
license: "BSD"
name: "freeverb"
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
	
	FAUSTFLOAT fHslider0;
	double fRec9_perm[4];
	FAUSTFLOAT fHslider1;
	double fYec0[2048];
	int fYec0_idx;
	int fYec0_idx_save;
	double fRec8_perm[4];
	double fRec11_perm[4];
	double fYec1[2048];
	int fYec1_idx;
	int fYec1_idx_save;
	double fRec10_perm[4];
	double fRec13_perm[4];
	double fYec2[2048];
	int fYec2_idx;
	int fYec2_idx_save;
	double fRec12_perm[4];
	double fRec15_perm[4];
	double fYec3[2048];
	int fYec3_idx;
	int fYec3_idx_save;
	double fRec14_perm[4];
	double fRec17_perm[4];
	double fYec4[2048];
	int fYec4_idx;
	int fYec4_idx_save;
	double fRec16_perm[4];
	double fRec19_perm[4];
	double fYec5[2048];
	int fYec5_idx;
	int fYec5_idx_save;
	double fRec18_perm[4];
	double fRec21_perm[4];
	double fYec6[2048];
	int fYec6_idx;
	int fYec6_idx_save;
	double fRec20_perm[4];
	double fRec23_perm[4];
	double fYec7[2048];
	int fYec7_idx;
	int fYec7_idx_save;
	double fRec22_perm[4];
	double fYec8[1024];
	int fYec8_idx;
	int fYec8_idx_save;
	double fRec6_perm[4];
	double fYec9[512];
	int fYec9_idx;
	int fYec9_idx_save;
	double fRec4_perm[4];
	double fYec10[512];
	int fYec10_idx;
	int fYec10_idx_save;
	double fRec2_perm[4];
	double fYec11[256];
	int fYec11_idx;
	int fYec11_idx_save;
	double fRec0_perm[4];
	FAUSTFLOAT fHslider2;
	double fRec33_perm[4];
	double fYec12[2048];
	int fYec12_idx;
	int fYec12_idx_save;
	double fRec32_perm[4];
	double fRec35_perm[4];
	double fYec13[2048];
	int fYec13_idx;
	int fYec13_idx_save;
	double fRec34_perm[4];
	double fRec37_perm[4];
	double fYec14[2048];
	int fYec14_idx;
	int fYec14_idx_save;
	double fRec36_perm[4];
	double fRec39_perm[4];
	double fYec15[2048];
	int fYec15_idx;
	int fYec15_idx_save;
	double fRec38_perm[4];
	double fRec41_perm[4];
	double fYec16[2048];
	int fYec16_idx;
	int fYec16_idx_save;
	double fRec40_perm[4];
	double fRec43_perm[4];
	double fYec17[2048];
	int fYec17_idx;
	int fYec17_idx_save;
	double fRec42_perm[4];
	double fRec45_perm[4];
	double fYec18[2048];
	int fYec18_idx;
	int fYec18_idx_save;
	double fRec44_perm[4];
	double fRec47_perm[4];
	double fYec19[2048];
	int fYec19_idx;
	int fYec19_idx_save;
	double fRec46_perm[4];
	double fYec20[1024];
	int fYec20_idx;
	int fYec20_idx_save;
	double fRec30_perm[4];
	double fYec21[512];
	int fYec21_idx;
	int fYec21_idx_save;
	double fRec28_perm[4];
	double fYec22[512];
	int fYec22_idx;
	int fYec22_idx_save;
	double fRec26_perm[4];
	double fYec23[256];
	int fYec23_idx;
	int fYec23_idx_save;
	double fRec24_perm[4];
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
		m->declare("copyright", "(c) GRAME 2006");
		m->declare("filename", "freeverb.dsp");
		m->declare("license", "BSD");
		m->declare("name", "freeverb");
		m->declare("reference", "https://ccrma.stanford.edu/~jos/pasp/Freeverb.html");
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
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(1.0);
		fHslider1 = static_cast<FAUSTFLOAT>(1.0);
		fHslider2 = static_cast<FAUSTFLOAT>(0.93);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 4; l0 = faust_wrap_add(l0, 1)) {
			fRec9_perm[l0] = 0.0;
		}
		for (int l1 = 0; l1 < 2048; l1 = faust_wrap_add(l1, 1)) {
			fYec0[l1] = 0.0;
		}
		fYec0_idx = 0;
		fYec0_idx_save = 0;
		for (int l2 = 0; l2 < 4; l2 = faust_wrap_add(l2, 1)) {
			fRec8_perm[l2] = 0.0;
		}
		for (int l3 = 0; l3 < 4; l3 = faust_wrap_add(l3, 1)) {
			fRec11_perm[l3] = 0.0;
		}
		for (int l4 = 0; l4 < 2048; l4 = faust_wrap_add(l4, 1)) {
			fYec1[l4] = 0.0;
		}
		fYec1_idx = 0;
		fYec1_idx_save = 0;
		for (int l5 = 0; l5 < 4; l5 = faust_wrap_add(l5, 1)) {
			fRec10_perm[l5] = 0.0;
		}
		for (int l6 = 0; l6 < 4; l6 = faust_wrap_add(l6, 1)) {
			fRec13_perm[l6] = 0.0;
		}
		for (int l7 = 0; l7 < 2048; l7 = faust_wrap_add(l7, 1)) {
			fYec2[l7] = 0.0;
		}
		fYec2_idx = 0;
		fYec2_idx_save = 0;
		for (int l8 = 0; l8 < 4; l8 = faust_wrap_add(l8, 1)) {
			fRec12_perm[l8] = 0.0;
		}
		for (int l9 = 0; l9 < 4; l9 = faust_wrap_add(l9, 1)) {
			fRec15_perm[l9] = 0.0;
		}
		for (int l10 = 0; l10 < 2048; l10 = faust_wrap_add(l10, 1)) {
			fYec3[l10] = 0.0;
		}
		fYec3_idx = 0;
		fYec3_idx_save = 0;
		for (int l11 = 0; l11 < 4; l11 = faust_wrap_add(l11, 1)) {
			fRec14_perm[l11] = 0.0;
		}
		for (int l12 = 0; l12 < 4; l12 = faust_wrap_add(l12, 1)) {
			fRec17_perm[l12] = 0.0;
		}
		for (int l13 = 0; l13 < 2048; l13 = faust_wrap_add(l13, 1)) {
			fYec4[l13] = 0.0;
		}
		fYec4_idx = 0;
		fYec4_idx_save = 0;
		for (int l14 = 0; l14 < 4; l14 = faust_wrap_add(l14, 1)) {
			fRec16_perm[l14] = 0.0;
		}
		for (int l15 = 0; l15 < 4; l15 = faust_wrap_add(l15, 1)) {
			fRec19_perm[l15] = 0.0;
		}
		for (int l16 = 0; l16 < 2048; l16 = faust_wrap_add(l16, 1)) {
			fYec5[l16] = 0.0;
		}
		fYec5_idx = 0;
		fYec5_idx_save = 0;
		for (int l17 = 0; l17 < 4; l17 = faust_wrap_add(l17, 1)) {
			fRec18_perm[l17] = 0.0;
		}
		for (int l18 = 0; l18 < 4; l18 = faust_wrap_add(l18, 1)) {
			fRec21_perm[l18] = 0.0;
		}
		for (int l19 = 0; l19 < 2048; l19 = faust_wrap_add(l19, 1)) {
			fYec6[l19] = 0.0;
		}
		fYec6_idx = 0;
		fYec6_idx_save = 0;
		for (int l20 = 0; l20 < 4; l20 = faust_wrap_add(l20, 1)) {
			fRec20_perm[l20] = 0.0;
		}
		for (int l21 = 0; l21 < 4; l21 = faust_wrap_add(l21, 1)) {
			fRec23_perm[l21] = 0.0;
		}
		for (int l22 = 0; l22 < 2048; l22 = faust_wrap_add(l22, 1)) {
			fYec7[l22] = 0.0;
		}
		fYec7_idx = 0;
		fYec7_idx_save = 0;
		for (int l23 = 0; l23 < 4; l23 = faust_wrap_add(l23, 1)) {
			fRec22_perm[l23] = 0.0;
		}
		for (int l24 = 0; l24 < 1024; l24 = faust_wrap_add(l24, 1)) {
			fYec8[l24] = 0.0;
		}
		fYec8_idx = 0;
		fYec8_idx_save = 0;
		for (int l25 = 0; l25 < 4; l25 = faust_wrap_add(l25, 1)) {
			fRec6_perm[l25] = 0.0;
		}
		for (int l26 = 0; l26 < 512; l26 = faust_wrap_add(l26, 1)) {
			fYec9[l26] = 0.0;
		}
		fYec9_idx = 0;
		fYec9_idx_save = 0;
		for (int l27 = 0; l27 < 4; l27 = faust_wrap_add(l27, 1)) {
			fRec4_perm[l27] = 0.0;
		}
		for (int l28 = 0; l28 < 512; l28 = faust_wrap_add(l28, 1)) {
			fYec10[l28] = 0.0;
		}
		fYec10_idx = 0;
		fYec10_idx_save = 0;
		for (int l29 = 0; l29 < 4; l29 = faust_wrap_add(l29, 1)) {
			fRec2_perm[l29] = 0.0;
		}
		for (int l30 = 0; l30 < 256; l30 = faust_wrap_add(l30, 1)) {
			fYec11[l30] = 0.0;
		}
		fYec11_idx = 0;
		fYec11_idx_save = 0;
		for (int l31 = 0; l31 < 4; l31 = faust_wrap_add(l31, 1)) {
			fRec0_perm[l31] = 0.0;
		}
		for (int l32 = 0; l32 < 4; l32 = faust_wrap_add(l32, 1)) {
			fRec33_perm[l32] = 0.0;
		}
		for (int l33 = 0; l33 < 2048; l33 = faust_wrap_add(l33, 1)) {
			fYec12[l33] = 0.0;
		}
		fYec12_idx = 0;
		fYec12_idx_save = 0;
		for (int l34 = 0; l34 < 4; l34 = faust_wrap_add(l34, 1)) {
			fRec32_perm[l34] = 0.0;
		}
		for (int l35 = 0; l35 < 4; l35 = faust_wrap_add(l35, 1)) {
			fRec35_perm[l35] = 0.0;
		}
		for (int l36 = 0; l36 < 2048; l36 = faust_wrap_add(l36, 1)) {
			fYec13[l36] = 0.0;
		}
		fYec13_idx = 0;
		fYec13_idx_save = 0;
		for (int l37 = 0; l37 < 4; l37 = faust_wrap_add(l37, 1)) {
			fRec34_perm[l37] = 0.0;
		}
		for (int l38 = 0; l38 < 4; l38 = faust_wrap_add(l38, 1)) {
			fRec37_perm[l38] = 0.0;
		}
		for (int l39 = 0; l39 < 2048; l39 = faust_wrap_add(l39, 1)) {
			fYec14[l39] = 0.0;
		}
		fYec14_idx = 0;
		fYec14_idx_save = 0;
		for (int l40 = 0; l40 < 4; l40 = faust_wrap_add(l40, 1)) {
			fRec36_perm[l40] = 0.0;
		}
		for (int l41 = 0; l41 < 4; l41 = faust_wrap_add(l41, 1)) {
			fRec39_perm[l41] = 0.0;
		}
		for (int l42 = 0; l42 < 2048; l42 = faust_wrap_add(l42, 1)) {
			fYec15[l42] = 0.0;
		}
		fYec15_idx = 0;
		fYec15_idx_save = 0;
		for (int l43 = 0; l43 < 4; l43 = faust_wrap_add(l43, 1)) {
			fRec38_perm[l43] = 0.0;
		}
		for (int l44 = 0; l44 < 4; l44 = faust_wrap_add(l44, 1)) {
			fRec41_perm[l44] = 0.0;
		}
		for (int l45 = 0; l45 < 2048; l45 = faust_wrap_add(l45, 1)) {
			fYec16[l45] = 0.0;
		}
		fYec16_idx = 0;
		fYec16_idx_save = 0;
		for (int l46 = 0; l46 < 4; l46 = faust_wrap_add(l46, 1)) {
			fRec40_perm[l46] = 0.0;
		}
		for (int l47 = 0; l47 < 4; l47 = faust_wrap_add(l47, 1)) {
			fRec43_perm[l47] = 0.0;
		}
		for (int l48 = 0; l48 < 2048; l48 = faust_wrap_add(l48, 1)) {
			fYec17[l48] = 0.0;
		}
		fYec17_idx = 0;
		fYec17_idx_save = 0;
		for (int l49 = 0; l49 < 4; l49 = faust_wrap_add(l49, 1)) {
			fRec42_perm[l49] = 0.0;
		}
		for (int l50 = 0; l50 < 4; l50 = faust_wrap_add(l50, 1)) {
			fRec45_perm[l50] = 0.0;
		}
		for (int l51 = 0; l51 < 2048; l51 = faust_wrap_add(l51, 1)) {
			fYec18[l51] = 0.0;
		}
		fYec18_idx = 0;
		fYec18_idx_save = 0;
		for (int l52 = 0; l52 < 4; l52 = faust_wrap_add(l52, 1)) {
			fRec44_perm[l52] = 0.0;
		}
		for (int l53 = 0; l53 < 4; l53 = faust_wrap_add(l53, 1)) {
			fRec47_perm[l53] = 0.0;
		}
		for (int l54 = 0; l54 < 2048; l54 = faust_wrap_add(l54, 1)) {
			fYec19[l54] = 0.0;
		}
		fYec19_idx = 0;
		fYec19_idx_save = 0;
		for (int l55 = 0; l55 < 4; l55 = faust_wrap_add(l55, 1)) {
			fRec46_perm[l55] = 0.0;
		}
		for (int l56 = 0; l56 < 1024; l56 = faust_wrap_add(l56, 1)) {
			fYec20[l56] = 0.0;
		}
		fYec20_idx = 0;
		fYec20_idx_save = 0;
		for (int l57 = 0; l57 < 4; l57 = faust_wrap_add(l57, 1)) {
			fRec30_perm[l57] = 0.0;
		}
		for (int l58 = 0; l58 < 512; l58 = faust_wrap_add(l58, 1)) {
			fYec21[l58] = 0.0;
		}
		fYec21_idx = 0;
		fYec21_idx_save = 0;
		for (int l59 = 0; l59 < 4; l59 = faust_wrap_add(l59, 1)) {
			fRec28_perm[l59] = 0.0;
		}
		for (int l60 = 0; l60 < 512; l60 = faust_wrap_add(l60, 1)) {
			fYec22[l60] = 0.0;
		}
		fYec22_idx = 0;
		fYec22_idx_save = 0;
		for (int l61 = 0; l61 < 4; l61 = faust_wrap_add(l61, 1)) {
			fRec26_perm[l61] = 0.0;
		}
		for (int l62 = 0; l62 < 256; l62 = faust_wrap_add(l62, 1)) {
			fYec23[l62] = 0.0;
		}
		fYec23_idx = 0;
		fYec23_idx_save = 0;
		for (int l63 = 0; l63 < 4; l63 = faust_wrap_add(l63, 1)) {
			fRec24_perm[l63] = 0.0;
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
		ui_interface->openVerticalBox("Freeverb");
		ui_interface->addHorizontalSlider("Damp", &fHslider0, FAUSTFLOAT(1.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.025));
		ui_interface->addHorizontalSlider("RoomSize", &fHslider1, FAUSTFLOAT(1.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.025));
		ui_interface->addHorizontalSlider("Wet", &fHslider2, FAUSTFLOAT(0.93), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.025));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0_ptr = inputs[0];
		FAUSTFLOAT* input1_ptr = inputs[1];
		FAUSTFLOAT* output0_ptr = outputs[0];
		FAUSTFLOAT* output1_ptr = outputs[1];
		double fSlow0 = 0.4 * static_cast<double>(fHslider0);
		double fSlow1 = 1.0 - fSlow0;
		double fRec9_tmp[8];
		double* fRec9 = &fRec9_tmp[4];
		double fSlow2 = 0.28 * static_cast<double>(fHslider1) + 0.7;
		double fZec0[4];
		double fRec8_tmp[8];
		double* fRec8 = &fRec8_tmp[4];
		double fRec11_tmp[8];
		double* fRec11 = &fRec11_tmp[4];
		double fRec10_tmp[8];
		double* fRec10 = &fRec10_tmp[4];
		double fRec13_tmp[8];
		double* fRec13 = &fRec13_tmp[4];
		double fRec12_tmp[8];
		double* fRec12 = &fRec12_tmp[4];
		double fRec15_tmp[8];
		double* fRec15 = &fRec15_tmp[4];
		double fRec14_tmp[8];
		double* fRec14 = &fRec14_tmp[4];
		double fRec17_tmp[8];
		double* fRec17 = &fRec17_tmp[4];
		double fRec16_tmp[8];
		double* fRec16 = &fRec16_tmp[4];
		double fRec19_tmp[8];
		double* fRec19 = &fRec19_tmp[4];
		double fRec18_tmp[8];
		double* fRec18 = &fRec18_tmp[4];
		double fRec21_tmp[8];
		double* fRec21 = &fRec21_tmp[4];
		double fRec20_tmp[8];
		double* fRec20 = &fRec20_tmp[4];
		double fRec23_tmp[8];
		double* fRec23 = &fRec23_tmp[4];
		double fRec22_tmp[8];
		double* fRec22 = &fRec22_tmp[4];
		double fZec1[4];
		double fRec6_tmp[8];
		double* fRec6 = &fRec6_tmp[4];
		double fRec7[4];
		double fRec4_tmp[8];
		double* fRec4 = &fRec4_tmp[4];
		double fRec5[4];
		double fRec2_tmp[8];
		double* fRec2 = &fRec2_tmp[4];
		double fRec3[4];
		double fRec0_tmp[8];
		double* fRec0 = &fRec0_tmp[4];
		double fRec1[4];
		double fSlow3 = static_cast<double>(fHslider2);
		double fSlow4 = 1.0 - fSlow3;
		double fRec33_tmp[8];
		double* fRec33 = &fRec33_tmp[4];
		double fRec32_tmp[8];
		double* fRec32 = &fRec32_tmp[4];
		double fRec35_tmp[8];
		double* fRec35 = &fRec35_tmp[4];
		double fRec34_tmp[8];
		double* fRec34 = &fRec34_tmp[4];
		double fRec37_tmp[8];
		double* fRec37 = &fRec37_tmp[4];
		double fRec36_tmp[8];
		double* fRec36 = &fRec36_tmp[4];
		double fRec39_tmp[8];
		double* fRec39 = &fRec39_tmp[4];
		double fRec38_tmp[8];
		double* fRec38 = &fRec38_tmp[4];
		double fRec41_tmp[8];
		double* fRec41 = &fRec41_tmp[4];
		double fRec40_tmp[8];
		double* fRec40 = &fRec40_tmp[4];
		double fRec43_tmp[8];
		double* fRec43 = &fRec43_tmp[4];
		double fRec42_tmp[8];
		double* fRec42 = &fRec42_tmp[4];
		double fRec45_tmp[8];
		double* fRec45 = &fRec45_tmp[4];
		double fRec44_tmp[8];
		double* fRec44 = &fRec44_tmp[4];
		double fRec47_tmp[8];
		double* fRec47 = &fRec47_tmp[4];
		double fRec46_tmp[8];
		double* fRec46 = &fRec46_tmp[4];
		double fZec2[4];
		double fRec30_tmp[8];
		double* fRec30 = &fRec30_tmp[4];
		double fRec31[4];
		double fRec28_tmp[8];
		double* fRec28 = &fRec28_tmp[4];
		double fRec29[4];
		double fRec26_tmp[8];
		double* fRec26 = &fRec26_tmp[4];
		double fRec27[4];
		double fRec24_tmp[8];
		double* fRec24 = &fRec24_tmp[4];
		double fRec25[4];
		int vindex = 0;
		/* Main loop */
		for (vindex = 0; vindex <= (faust_wrap_sub(count, 4)); vindex = faust_wrap_add(vindex, 4)) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* input1 = &input1_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			FAUSTFLOAT* output1 = &output1_ptr[vindex];
			int vsize = 4;
			/* Vectorizable loop 0 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec0[i] = 0.015 * (static_cast<double>(input0[i]) + static_cast<double>(input1[i]));
			}
			/* Recursive loop 1 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				fRec9_tmp[j0] = fRec9_perm[j0];
			}
			fYec0_idx = (faust_wrap_add(fYec0_idx, fYec0_idx_save)) & 2047;
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fRec8_tmp[j2] = fRec8_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec9[i] = fSlow0 * fRec9[faust_wrap_sub(i, 1)] + fSlow1 * fRec8[faust_wrap_sub(i, 1)];
				fYec0[(faust_wrap_add(i, fYec0_idx)) & 2047] = fSlow2 * fRec9[i] + fZec0[i];
				fRec8[i] = fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 1116)) & 2047];
			}
			/* Post code */
			fYec0_idx_save = vsize;
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				fRec9_perm[j1] = fRec9_tmp[faust_wrap_add(vsize, j1)];
			}
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fRec8_perm[j3] = fRec8_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Recursive loop 2 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				fRec11_tmp[j4] = fRec11_perm[j4];
			}
			fYec1_idx = (faust_wrap_add(fYec1_idx, fYec1_idx_save)) & 2047;
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec10_tmp[j6] = fRec10_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec11[i] = fSlow0 * fRec11[faust_wrap_sub(i, 1)] + fSlow1 * fRec10[faust_wrap_sub(i, 1)];
				fYec1[(faust_wrap_add(i, fYec1_idx)) & 2047] = fZec0[i] + fSlow2 * fRec11[i];
				fRec10[i] = fYec1[(faust_wrap_sub(faust_wrap_add(i, fYec1_idx), 1188)) & 2047];
			}
			/* Post code */
			fYec1_idx_save = vsize;
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fRec11_perm[j5] = fRec11_tmp[faust_wrap_add(vsize, j5)];
			}
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec10_perm[j7] = fRec10_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Recursive loop 3 */
			/* Pre code */
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fRec13_tmp[j8] = fRec13_perm[j8];
			}
			fYec2_idx = (faust_wrap_add(fYec2_idx, fYec2_idx_save)) & 2047;
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				fRec12_tmp[j10] = fRec12_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec13[i] = fSlow0 * fRec13[faust_wrap_sub(i, 1)] + fSlow1 * fRec12[faust_wrap_sub(i, 1)];
				fYec2[(faust_wrap_add(i, fYec2_idx)) & 2047] = fZec0[i] + fSlow2 * fRec13[i];
				fRec12[i] = fYec2[(faust_wrap_sub(faust_wrap_add(i, fYec2_idx), 1277)) & 2047];
			}
			/* Post code */
			fYec2_idx_save = vsize;
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fRec13_perm[j9] = fRec13_tmp[faust_wrap_add(vsize, j9)];
			}
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				fRec12_perm[j11] = fRec12_tmp[faust_wrap_add(vsize, j11)];
			}
			/* Recursive loop 4 */
			/* Pre code */
			for (int j12 = 0; j12 < 4; j12 = faust_wrap_add(j12, 1)) {
				fRec15_tmp[j12] = fRec15_perm[j12];
			}
			fYec3_idx = (faust_wrap_add(fYec3_idx, fYec3_idx_save)) & 2047;
			for (int j14 = 0; j14 < 4; j14 = faust_wrap_add(j14, 1)) {
				fRec14_tmp[j14] = fRec14_perm[j14];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec15[i] = fSlow0 * fRec15[faust_wrap_sub(i, 1)] + fSlow1 * fRec14[faust_wrap_sub(i, 1)];
				fYec3[(faust_wrap_add(i, fYec3_idx)) & 2047] = fZec0[i] + fSlow2 * fRec15[i];
				fRec14[i] = fYec3[(faust_wrap_sub(faust_wrap_add(i, fYec3_idx), 1356)) & 2047];
			}
			/* Post code */
			fYec3_idx_save = vsize;
			for (int j13 = 0; j13 < 4; j13 = faust_wrap_add(j13, 1)) {
				fRec15_perm[j13] = fRec15_tmp[faust_wrap_add(vsize, j13)];
			}
			for (int j15 = 0; j15 < 4; j15 = faust_wrap_add(j15, 1)) {
				fRec14_perm[j15] = fRec14_tmp[faust_wrap_add(vsize, j15)];
			}
			/* Recursive loop 5 */
			/* Pre code */
			for (int j16 = 0; j16 < 4; j16 = faust_wrap_add(j16, 1)) {
				fRec17_tmp[j16] = fRec17_perm[j16];
			}
			fYec4_idx = (faust_wrap_add(fYec4_idx, fYec4_idx_save)) & 2047;
			for (int j18 = 0; j18 < 4; j18 = faust_wrap_add(j18, 1)) {
				fRec16_tmp[j18] = fRec16_perm[j18];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec17[i] = fSlow0 * fRec17[faust_wrap_sub(i, 1)] + fSlow1 * fRec16[faust_wrap_sub(i, 1)];
				fYec4[(faust_wrap_add(i, fYec4_idx)) & 2047] = fZec0[i] + fSlow2 * fRec17[i];
				fRec16[i] = fYec4[(faust_wrap_sub(faust_wrap_add(i, fYec4_idx), 1422)) & 2047];
			}
			/* Post code */
			fYec4_idx_save = vsize;
			for (int j17 = 0; j17 < 4; j17 = faust_wrap_add(j17, 1)) {
				fRec17_perm[j17] = fRec17_tmp[faust_wrap_add(vsize, j17)];
			}
			for (int j19 = 0; j19 < 4; j19 = faust_wrap_add(j19, 1)) {
				fRec16_perm[j19] = fRec16_tmp[faust_wrap_add(vsize, j19)];
			}
			/* Recursive loop 6 */
			/* Pre code */
			for (int j20 = 0; j20 < 4; j20 = faust_wrap_add(j20, 1)) {
				fRec19_tmp[j20] = fRec19_perm[j20];
			}
			fYec5_idx = (faust_wrap_add(fYec5_idx, fYec5_idx_save)) & 2047;
			for (int j22 = 0; j22 < 4; j22 = faust_wrap_add(j22, 1)) {
				fRec18_tmp[j22] = fRec18_perm[j22];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec19[i] = fSlow0 * fRec19[faust_wrap_sub(i, 1)] + fSlow1 * fRec18[faust_wrap_sub(i, 1)];
				fYec5[(faust_wrap_add(i, fYec5_idx)) & 2047] = fZec0[i] + fSlow2 * fRec19[i];
				fRec18[i] = fYec5[(faust_wrap_sub(faust_wrap_add(i, fYec5_idx), 1491)) & 2047];
			}
			/* Post code */
			fYec5_idx_save = vsize;
			for (int j21 = 0; j21 < 4; j21 = faust_wrap_add(j21, 1)) {
				fRec19_perm[j21] = fRec19_tmp[faust_wrap_add(vsize, j21)];
			}
			for (int j23 = 0; j23 < 4; j23 = faust_wrap_add(j23, 1)) {
				fRec18_perm[j23] = fRec18_tmp[faust_wrap_add(vsize, j23)];
			}
			/* Recursive loop 7 */
			/* Pre code */
			for (int j24 = 0; j24 < 4; j24 = faust_wrap_add(j24, 1)) {
				fRec21_tmp[j24] = fRec21_perm[j24];
			}
			fYec6_idx = (faust_wrap_add(fYec6_idx, fYec6_idx_save)) & 2047;
			for (int j26 = 0; j26 < 4; j26 = faust_wrap_add(j26, 1)) {
				fRec20_tmp[j26] = fRec20_perm[j26];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec21[i] = fSlow0 * fRec21[faust_wrap_sub(i, 1)] + fSlow1 * fRec20[faust_wrap_sub(i, 1)];
				fYec6[(faust_wrap_add(i, fYec6_idx)) & 2047] = fZec0[i] + fSlow2 * fRec21[i];
				fRec20[i] = fYec6[(faust_wrap_sub(faust_wrap_add(i, fYec6_idx), 1557)) & 2047];
			}
			/* Post code */
			fYec6_idx_save = vsize;
			for (int j25 = 0; j25 < 4; j25 = faust_wrap_add(j25, 1)) {
				fRec21_perm[j25] = fRec21_tmp[faust_wrap_add(vsize, j25)];
			}
			for (int j27 = 0; j27 < 4; j27 = faust_wrap_add(j27, 1)) {
				fRec20_perm[j27] = fRec20_tmp[faust_wrap_add(vsize, j27)];
			}
			/* Recursive loop 8 */
			/* Pre code */
			for (int j28 = 0; j28 < 4; j28 = faust_wrap_add(j28, 1)) {
				fRec23_tmp[j28] = fRec23_perm[j28];
			}
			fYec7_idx = (faust_wrap_add(fYec7_idx, fYec7_idx_save)) & 2047;
			for (int j30 = 0; j30 < 4; j30 = faust_wrap_add(j30, 1)) {
				fRec22_tmp[j30] = fRec22_perm[j30];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec23[i] = fSlow0 * fRec23[faust_wrap_sub(i, 1)] + fSlow1 * fRec22[faust_wrap_sub(i, 1)];
				fYec7[(faust_wrap_add(i, fYec7_idx)) & 2047] = fZec0[i] + fSlow2 * fRec23[i];
				fRec22[i] = fYec7[(faust_wrap_sub(faust_wrap_add(i, fYec7_idx), 1617)) & 2047];
			}
			/* Post code */
			fYec7_idx_save = vsize;
			for (int j29 = 0; j29 < 4; j29 = faust_wrap_add(j29, 1)) {
				fRec23_perm[j29] = fRec23_tmp[faust_wrap_add(vsize, j29)];
			}
			for (int j31 = 0; j31 < 4; j31 = faust_wrap_add(j31, 1)) {
				fRec22_perm[j31] = fRec22_tmp[faust_wrap_add(vsize, j31)];
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec1[i] = fRec8[i] + fRec10[i] + fRec12[i] + fRec14[i] + fRec16[i] + fRec18[i] + fRec20[i] + fRec22[i];
			}
			/* Recursive loop 10 */
			/* Pre code */
			fYec8_idx = (faust_wrap_add(fYec8_idx, fYec8_idx_save)) & 1023;
			for (int j32 = 0; j32 < 4; j32 = faust_wrap_add(j32, 1)) {
				fRec6_tmp[j32] = fRec6_perm[j32];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec8[(faust_wrap_add(i, fYec8_idx)) & 1023] = fZec1[i] + 0.5 * fRec6[faust_wrap_sub(i, 1)];
				fRec6[i] = fYec8[(faust_wrap_sub(faust_wrap_add(i, fYec8_idx), 556)) & 1023];
				fRec7[i] = fRec6[faust_wrap_sub(i, 1)] - fZec1[i];
			}
			/* Post code */
			fYec8_idx_save = vsize;
			for (int j33 = 0; j33 < 4; j33 = faust_wrap_add(j33, 1)) {
				fRec6_perm[j33] = fRec6_tmp[faust_wrap_add(vsize, j33)];
			}
			/* Recursive loop 11 */
			/* Pre code */
			fYec9_idx = (faust_wrap_add(fYec9_idx, fYec9_idx_save)) & 511;
			for (int j34 = 0; j34 < 4; j34 = faust_wrap_add(j34, 1)) {
				fRec4_tmp[j34] = fRec4_perm[j34];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec9[(faust_wrap_add(i, fYec9_idx)) & 511] = fRec7[i] + 0.5 * fRec4[faust_wrap_sub(i, 1)];
				fRec4[i] = fYec9[(faust_wrap_sub(faust_wrap_add(i, fYec9_idx), 441)) & 511];
				fRec5[i] = fRec4[faust_wrap_sub(i, 1)] - fRec7[i];
			}
			/* Post code */
			fYec9_idx_save = vsize;
			for (int j35 = 0; j35 < 4; j35 = faust_wrap_add(j35, 1)) {
				fRec4_perm[j35] = fRec4_tmp[faust_wrap_add(vsize, j35)];
			}
			/* Recursive loop 12 */
			/* Pre code */
			fYec10_idx = (faust_wrap_add(fYec10_idx, fYec10_idx_save)) & 511;
			for (int j36 = 0; j36 < 4; j36 = faust_wrap_add(j36, 1)) {
				fRec2_tmp[j36] = fRec2_perm[j36];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec10[(faust_wrap_add(i, fYec10_idx)) & 511] = fRec5[i] + 0.5 * fRec2[faust_wrap_sub(i, 1)];
				fRec2[i] = fYec10[(faust_wrap_sub(faust_wrap_add(i, fYec10_idx), 341)) & 511];
				fRec3[i] = fRec2[faust_wrap_sub(i, 1)] - fRec5[i];
			}
			/* Post code */
			fYec10_idx_save = vsize;
			for (int j37 = 0; j37 < 4; j37 = faust_wrap_add(j37, 1)) {
				fRec2_perm[j37] = fRec2_tmp[faust_wrap_add(vsize, j37)];
			}
			/* Recursive loop 13 */
			/* Pre code */
			fYec11_idx = (faust_wrap_add(fYec11_idx, fYec11_idx_save)) & 255;
			for (int j38 = 0; j38 < 4; j38 = faust_wrap_add(j38, 1)) {
				fRec0_tmp[j38] = fRec0_perm[j38];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec11[(faust_wrap_add(i, fYec11_idx)) & 255] = fRec3[i] + 0.5 * fRec0[faust_wrap_sub(i, 1)];
				fRec0[i] = fYec11[(faust_wrap_sub(faust_wrap_add(i, fYec11_idx), 225)) & 255];
				fRec1[i] = fRec0[faust_wrap_sub(i, 1)] - fRec3[i];
			}
			/* Post code */
			fYec11_idx_save = vsize;
			for (int j39 = 0; j39 < 4; j39 = faust_wrap_add(j39, 1)) {
				fRec0_perm[j39] = fRec0_tmp[faust_wrap_add(vsize, j39)];
			}
			/* Vectorizable loop 14 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fSlow3 * fRec1[i] + fSlow4 * static_cast<double>(input0[i]));
			}
			/* Recursive loop 15 */
			/* Pre code */
			for (int j40 = 0; j40 < 4; j40 = faust_wrap_add(j40, 1)) {
				fRec33_tmp[j40] = fRec33_perm[j40];
			}
			fYec12_idx = (faust_wrap_add(fYec12_idx, fYec12_idx_save)) & 2047;
			for (int j42 = 0; j42 < 4; j42 = faust_wrap_add(j42, 1)) {
				fRec32_tmp[j42] = fRec32_perm[j42];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec33[i] = fSlow0 * fRec33[faust_wrap_sub(i, 1)] + fSlow1 * fRec32[faust_wrap_sub(i, 1)];
				fYec12[(faust_wrap_add(i, fYec12_idx)) & 2047] = fZec0[i] + fSlow2 * fRec33[i];
				fRec32[i] = fYec12[(faust_wrap_sub(faust_wrap_add(i, fYec12_idx), 1139)) & 2047];
			}
			/* Post code */
			fYec12_idx_save = vsize;
			for (int j41 = 0; j41 < 4; j41 = faust_wrap_add(j41, 1)) {
				fRec33_perm[j41] = fRec33_tmp[faust_wrap_add(vsize, j41)];
			}
			for (int j43 = 0; j43 < 4; j43 = faust_wrap_add(j43, 1)) {
				fRec32_perm[j43] = fRec32_tmp[faust_wrap_add(vsize, j43)];
			}
			/* Recursive loop 16 */
			/* Pre code */
			for (int j44 = 0; j44 < 4; j44 = faust_wrap_add(j44, 1)) {
				fRec35_tmp[j44] = fRec35_perm[j44];
			}
			fYec13_idx = (faust_wrap_add(fYec13_idx, fYec13_idx_save)) & 2047;
			for (int j46 = 0; j46 < 4; j46 = faust_wrap_add(j46, 1)) {
				fRec34_tmp[j46] = fRec34_perm[j46];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec35[i] = fSlow0 * fRec35[faust_wrap_sub(i, 1)] + fSlow1 * fRec34[faust_wrap_sub(i, 1)];
				fYec13[(faust_wrap_add(i, fYec13_idx)) & 2047] = fZec0[i] + fSlow2 * fRec35[i];
				fRec34[i] = fYec13[(faust_wrap_sub(faust_wrap_add(i, fYec13_idx), 1211)) & 2047];
			}
			/* Post code */
			fYec13_idx_save = vsize;
			for (int j45 = 0; j45 < 4; j45 = faust_wrap_add(j45, 1)) {
				fRec35_perm[j45] = fRec35_tmp[faust_wrap_add(vsize, j45)];
			}
			for (int j47 = 0; j47 < 4; j47 = faust_wrap_add(j47, 1)) {
				fRec34_perm[j47] = fRec34_tmp[faust_wrap_add(vsize, j47)];
			}
			/* Recursive loop 17 */
			/* Pre code */
			for (int j48 = 0; j48 < 4; j48 = faust_wrap_add(j48, 1)) {
				fRec37_tmp[j48] = fRec37_perm[j48];
			}
			fYec14_idx = (faust_wrap_add(fYec14_idx, fYec14_idx_save)) & 2047;
			for (int j50 = 0; j50 < 4; j50 = faust_wrap_add(j50, 1)) {
				fRec36_tmp[j50] = fRec36_perm[j50];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec37[i] = fSlow0 * fRec37[faust_wrap_sub(i, 1)] + fSlow1 * fRec36[faust_wrap_sub(i, 1)];
				fYec14[(faust_wrap_add(i, fYec14_idx)) & 2047] = fZec0[i] + fSlow2 * fRec37[i];
				fRec36[i] = fYec14[(faust_wrap_sub(faust_wrap_add(i, fYec14_idx), 1300)) & 2047];
			}
			/* Post code */
			fYec14_idx_save = vsize;
			for (int j49 = 0; j49 < 4; j49 = faust_wrap_add(j49, 1)) {
				fRec37_perm[j49] = fRec37_tmp[faust_wrap_add(vsize, j49)];
			}
			for (int j51 = 0; j51 < 4; j51 = faust_wrap_add(j51, 1)) {
				fRec36_perm[j51] = fRec36_tmp[faust_wrap_add(vsize, j51)];
			}
			/* Recursive loop 18 */
			/* Pre code */
			for (int j52 = 0; j52 < 4; j52 = faust_wrap_add(j52, 1)) {
				fRec39_tmp[j52] = fRec39_perm[j52];
			}
			fYec15_idx = (faust_wrap_add(fYec15_idx, fYec15_idx_save)) & 2047;
			for (int j54 = 0; j54 < 4; j54 = faust_wrap_add(j54, 1)) {
				fRec38_tmp[j54] = fRec38_perm[j54];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec39[i] = fSlow0 * fRec39[faust_wrap_sub(i, 1)] + fSlow1 * fRec38[faust_wrap_sub(i, 1)];
				fYec15[(faust_wrap_add(i, fYec15_idx)) & 2047] = fZec0[i] + fSlow2 * fRec39[i];
				fRec38[i] = fYec15[(faust_wrap_sub(faust_wrap_add(i, fYec15_idx), 1379)) & 2047];
			}
			/* Post code */
			fYec15_idx_save = vsize;
			for (int j53 = 0; j53 < 4; j53 = faust_wrap_add(j53, 1)) {
				fRec39_perm[j53] = fRec39_tmp[faust_wrap_add(vsize, j53)];
			}
			for (int j55 = 0; j55 < 4; j55 = faust_wrap_add(j55, 1)) {
				fRec38_perm[j55] = fRec38_tmp[faust_wrap_add(vsize, j55)];
			}
			/* Recursive loop 19 */
			/* Pre code */
			for (int j56 = 0; j56 < 4; j56 = faust_wrap_add(j56, 1)) {
				fRec41_tmp[j56] = fRec41_perm[j56];
			}
			fYec16_idx = (faust_wrap_add(fYec16_idx, fYec16_idx_save)) & 2047;
			for (int j58 = 0; j58 < 4; j58 = faust_wrap_add(j58, 1)) {
				fRec40_tmp[j58] = fRec40_perm[j58];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec41[i] = fSlow0 * fRec41[faust_wrap_sub(i, 1)] + fSlow1 * fRec40[faust_wrap_sub(i, 1)];
				fYec16[(faust_wrap_add(i, fYec16_idx)) & 2047] = fZec0[i] + fSlow2 * fRec41[i];
				fRec40[i] = fYec16[(faust_wrap_sub(faust_wrap_add(i, fYec16_idx), 1445)) & 2047];
			}
			/* Post code */
			fYec16_idx_save = vsize;
			for (int j57 = 0; j57 < 4; j57 = faust_wrap_add(j57, 1)) {
				fRec41_perm[j57] = fRec41_tmp[faust_wrap_add(vsize, j57)];
			}
			for (int j59 = 0; j59 < 4; j59 = faust_wrap_add(j59, 1)) {
				fRec40_perm[j59] = fRec40_tmp[faust_wrap_add(vsize, j59)];
			}
			/* Recursive loop 20 */
			/* Pre code */
			for (int j60 = 0; j60 < 4; j60 = faust_wrap_add(j60, 1)) {
				fRec43_tmp[j60] = fRec43_perm[j60];
			}
			fYec17_idx = (faust_wrap_add(fYec17_idx, fYec17_idx_save)) & 2047;
			for (int j62 = 0; j62 < 4; j62 = faust_wrap_add(j62, 1)) {
				fRec42_tmp[j62] = fRec42_perm[j62];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec43[i] = fSlow0 * fRec43[faust_wrap_sub(i, 1)] + fSlow1 * fRec42[faust_wrap_sub(i, 1)];
				fYec17[(faust_wrap_add(i, fYec17_idx)) & 2047] = fZec0[i] + fSlow2 * fRec43[i];
				fRec42[i] = fYec17[(faust_wrap_sub(faust_wrap_add(i, fYec17_idx), 1514)) & 2047];
			}
			/* Post code */
			fYec17_idx_save = vsize;
			for (int j61 = 0; j61 < 4; j61 = faust_wrap_add(j61, 1)) {
				fRec43_perm[j61] = fRec43_tmp[faust_wrap_add(vsize, j61)];
			}
			for (int j63 = 0; j63 < 4; j63 = faust_wrap_add(j63, 1)) {
				fRec42_perm[j63] = fRec42_tmp[faust_wrap_add(vsize, j63)];
			}
			/* Recursive loop 21 */
			/* Pre code */
			for (int j64 = 0; j64 < 4; j64 = faust_wrap_add(j64, 1)) {
				fRec45_tmp[j64] = fRec45_perm[j64];
			}
			fYec18_idx = (faust_wrap_add(fYec18_idx, fYec18_idx_save)) & 2047;
			for (int j66 = 0; j66 < 4; j66 = faust_wrap_add(j66, 1)) {
				fRec44_tmp[j66] = fRec44_perm[j66];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec45[i] = fSlow0 * fRec45[faust_wrap_sub(i, 1)] + fSlow1 * fRec44[faust_wrap_sub(i, 1)];
				fYec18[(faust_wrap_add(i, fYec18_idx)) & 2047] = fZec0[i] + fSlow2 * fRec45[i];
				fRec44[i] = fYec18[(faust_wrap_sub(faust_wrap_add(i, fYec18_idx), 1580)) & 2047];
			}
			/* Post code */
			fYec18_idx_save = vsize;
			for (int j65 = 0; j65 < 4; j65 = faust_wrap_add(j65, 1)) {
				fRec45_perm[j65] = fRec45_tmp[faust_wrap_add(vsize, j65)];
			}
			for (int j67 = 0; j67 < 4; j67 = faust_wrap_add(j67, 1)) {
				fRec44_perm[j67] = fRec44_tmp[faust_wrap_add(vsize, j67)];
			}
			/* Recursive loop 22 */
			/* Pre code */
			for (int j68 = 0; j68 < 4; j68 = faust_wrap_add(j68, 1)) {
				fRec47_tmp[j68] = fRec47_perm[j68];
			}
			fYec19_idx = (faust_wrap_add(fYec19_idx, fYec19_idx_save)) & 2047;
			for (int j70 = 0; j70 < 4; j70 = faust_wrap_add(j70, 1)) {
				fRec46_tmp[j70] = fRec46_perm[j70];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec47[i] = fSlow0 * fRec47[faust_wrap_sub(i, 1)] + fSlow1 * fRec46[faust_wrap_sub(i, 1)];
				fYec19[(faust_wrap_add(i, fYec19_idx)) & 2047] = fZec0[i] + fSlow2 * fRec47[i];
				fRec46[i] = fYec19[(faust_wrap_sub(faust_wrap_add(i, fYec19_idx), 1640)) & 2047];
			}
			/* Post code */
			fYec19_idx_save = vsize;
			for (int j69 = 0; j69 < 4; j69 = faust_wrap_add(j69, 1)) {
				fRec47_perm[j69] = fRec47_tmp[faust_wrap_add(vsize, j69)];
			}
			for (int j71 = 0; j71 < 4; j71 = faust_wrap_add(j71, 1)) {
				fRec46_perm[j71] = fRec46_tmp[faust_wrap_add(vsize, j71)];
			}
			/* Vectorizable loop 23 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec2[i] = fRec32[i] + fRec34[i] + fRec36[i] + fRec38[i] + fRec40[i] + fRec42[i] + fRec44[i] + fRec46[i];
			}
			/* Recursive loop 24 */
			/* Pre code */
			fYec20_idx = (faust_wrap_add(fYec20_idx, fYec20_idx_save)) & 1023;
			for (int j72 = 0; j72 < 4; j72 = faust_wrap_add(j72, 1)) {
				fRec30_tmp[j72] = fRec30_perm[j72];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec20[(faust_wrap_add(i, fYec20_idx)) & 1023] = fZec2[i] + 0.5 * fRec30[faust_wrap_sub(i, 1)];
				fRec30[i] = fYec20[(faust_wrap_sub(faust_wrap_add(i, fYec20_idx), 579)) & 1023];
				fRec31[i] = fRec30[faust_wrap_sub(i, 1)] - fZec2[i];
			}
			/* Post code */
			fYec20_idx_save = vsize;
			for (int j73 = 0; j73 < 4; j73 = faust_wrap_add(j73, 1)) {
				fRec30_perm[j73] = fRec30_tmp[faust_wrap_add(vsize, j73)];
			}
			/* Recursive loop 25 */
			/* Pre code */
			fYec21_idx = (faust_wrap_add(fYec21_idx, fYec21_idx_save)) & 511;
			for (int j74 = 0; j74 < 4; j74 = faust_wrap_add(j74, 1)) {
				fRec28_tmp[j74] = fRec28_perm[j74];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec21[(faust_wrap_add(i, fYec21_idx)) & 511] = fRec31[i] + 0.5 * fRec28[faust_wrap_sub(i, 1)];
				fRec28[i] = fYec21[(faust_wrap_sub(faust_wrap_add(i, fYec21_idx), 464)) & 511];
				fRec29[i] = fRec28[faust_wrap_sub(i, 1)] - fRec31[i];
			}
			/* Post code */
			fYec21_idx_save = vsize;
			for (int j75 = 0; j75 < 4; j75 = faust_wrap_add(j75, 1)) {
				fRec28_perm[j75] = fRec28_tmp[faust_wrap_add(vsize, j75)];
			}
			/* Recursive loop 26 */
			/* Pre code */
			fYec22_idx = (faust_wrap_add(fYec22_idx, fYec22_idx_save)) & 511;
			for (int j76 = 0; j76 < 4; j76 = faust_wrap_add(j76, 1)) {
				fRec26_tmp[j76] = fRec26_perm[j76];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec22[(faust_wrap_add(i, fYec22_idx)) & 511] = fRec29[i] + 0.5 * fRec26[faust_wrap_sub(i, 1)];
				fRec26[i] = fYec22[(faust_wrap_sub(faust_wrap_add(i, fYec22_idx), 364)) & 511];
				fRec27[i] = fRec26[faust_wrap_sub(i, 1)] - fRec29[i];
			}
			/* Post code */
			fYec22_idx_save = vsize;
			for (int j77 = 0; j77 < 4; j77 = faust_wrap_add(j77, 1)) {
				fRec26_perm[j77] = fRec26_tmp[faust_wrap_add(vsize, j77)];
			}
			/* Recursive loop 27 */
			/* Pre code */
			fYec23_idx = (faust_wrap_add(fYec23_idx, fYec23_idx_save)) & 255;
			for (int j78 = 0; j78 < 4; j78 = faust_wrap_add(j78, 1)) {
				fRec24_tmp[j78] = fRec24_perm[j78];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec23[(faust_wrap_add(i, fYec23_idx)) & 255] = fRec27[i] + 0.5 * fRec24[faust_wrap_sub(i, 1)];
				fRec24[i] = fYec23[(faust_wrap_sub(faust_wrap_add(i, fYec23_idx), 248)) & 255];
				fRec25[i] = fRec24[faust_wrap_sub(i, 1)] - fRec27[i];
			}
			/* Post code */
			fYec23_idx_save = vsize;
			for (int j79 = 0; j79 < 4; j79 = faust_wrap_add(j79, 1)) {
				fRec24_perm[j79] = fRec24_tmp[faust_wrap_add(vsize, j79)];
			}
			/* Vectorizable loop 28 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fSlow3 * fRec25[i] + fSlow4 * static_cast<double>(input1[i]));
			}
		}
		/* Remaining frames */
		if (vindex < count) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* input1 = &input1_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			FAUSTFLOAT* output1 = &output1_ptr[vindex];
			int vsize = faust_wrap_sub(count, vindex);
			/* Vectorizable loop 0 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec0[i] = 0.015 * (static_cast<double>(input0[i]) + static_cast<double>(input1[i]));
			}
			/* Recursive loop 1 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				fRec9_tmp[j0] = fRec9_perm[j0];
			}
			fYec0_idx = (faust_wrap_add(fYec0_idx, fYec0_idx_save)) & 2047;
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fRec8_tmp[j2] = fRec8_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec9[i] = fSlow0 * fRec9[faust_wrap_sub(i, 1)] + fSlow1 * fRec8[faust_wrap_sub(i, 1)];
				fYec0[(faust_wrap_add(i, fYec0_idx)) & 2047] = fSlow2 * fRec9[i] + fZec0[i];
				fRec8[i] = fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 1116)) & 2047];
			}
			/* Post code */
			fYec0_idx_save = vsize;
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				fRec9_perm[j1] = fRec9_tmp[faust_wrap_add(vsize, j1)];
			}
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fRec8_perm[j3] = fRec8_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Recursive loop 2 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				fRec11_tmp[j4] = fRec11_perm[j4];
			}
			fYec1_idx = (faust_wrap_add(fYec1_idx, fYec1_idx_save)) & 2047;
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec10_tmp[j6] = fRec10_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec11[i] = fSlow0 * fRec11[faust_wrap_sub(i, 1)] + fSlow1 * fRec10[faust_wrap_sub(i, 1)];
				fYec1[(faust_wrap_add(i, fYec1_idx)) & 2047] = fZec0[i] + fSlow2 * fRec11[i];
				fRec10[i] = fYec1[(faust_wrap_sub(faust_wrap_add(i, fYec1_idx), 1188)) & 2047];
			}
			/* Post code */
			fYec1_idx_save = vsize;
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fRec11_perm[j5] = fRec11_tmp[faust_wrap_add(vsize, j5)];
			}
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec10_perm[j7] = fRec10_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Recursive loop 3 */
			/* Pre code */
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fRec13_tmp[j8] = fRec13_perm[j8];
			}
			fYec2_idx = (faust_wrap_add(fYec2_idx, fYec2_idx_save)) & 2047;
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				fRec12_tmp[j10] = fRec12_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec13[i] = fSlow0 * fRec13[faust_wrap_sub(i, 1)] + fSlow1 * fRec12[faust_wrap_sub(i, 1)];
				fYec2[(faust_wrap_add(i, fYec2_idx)) & 2047] = fZec0[i] + fSlow2 * fRec13[i];
				fRec12[i] = fYec2[(faust_wrap_sub(faust_wrap_add(i, fYec2_idx), 1277)) & 2047];
			}
			/* Post code */
			fYec2_idx_save = vsize;
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fRec13_perm[j9] = fRec13_tmp[faust_wrap_add(vsize, j9)];
			}
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				fRec12_perm[j11] = fRec12_tmp[faust_wrap_add(vsize, j11)];
			}
			/* Recursive loop 4 */
			/* Pre code */
			for (int j12 = 0; j12 < 4; j12 = faust_wrap_add(j12, 1)) {
				fRec15_tmp[j12] = fRec15_perm[j12];
			}
			fYec3_idx = (faust_wrap_add(fYec3_idx, fYec3_idx_save)) & 2047;
			for (int j14 = 0; j14 < 4; j14 = faust_wrap_add(j14, 1)) {
				fRec14_tmp[j14] = fRec14_perm[j14];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec15[i] = fSlow0 * fRec15[faust_wrap_sub(i, 1)] + fSlow1 * fRec14[faust_wrap_sub(i, 1)];
				fYec3[(faust_wrap_add(i, fYec3_idx)) & 2047] = fZec0[i] + fSlow2 * fRec15[i];
				fRec14[i] = fYec3[(faust_wrap_sub(faust_wrap_add(i, fYec3_idx), 1356)) & 2047];
			}
			/* Post code */
			fYec3_idx_save = vsize;
			for (int j13 = 0; j13 < 4; j13 = faust_wrap_add(j13, 1)) {
				fRec15_perm[j13] = fRec15_tmp[faust_wrap_add(vsize, j13)];
			}
			for (int j15 = 0; j15 < 4; j15 = faust_wrap_add(j15, 1)) {
				fRec14_perm[j15] = fRec14_tmp[faust_wrap_add(vsize, j15)];
			}
			/* Recursive loop 5 */
			/* Pre code */
			for (int j16 = 0; j16 < 4; j16 = faust_wrap_add(j16, 1)) {
				fRec17_tmp[j16] = fRec17_perm[j16];
			}
			fYec4_idx = (faust_wrap_add(fYec4_idx, fYec4_idx_save)) & 2047;
			for (int j18 = 0; j18 < 4; j18 = faust_wrap_add(j18, 1)) {
				fRec16_tmp[j18] = fRec16_perm[j18];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec17[i] = fSlow0 * fRec17[faust_wrap_sub(i, 1)] + fSlow1 * fRec16[faust_wrap_sub(i, 1)];
				fYec4[(faust_wrap_add(i, fYec4_idx)) & 2047] = fZec0[i] + fSlow2 * fRec17[i];
				fRec16[i] = fYec4[(faust_wrap_sub(faust_wrap_add(i, fYec4_idx), 1422)) & 2047];
			}
			/* Post code */
			fYec4_idx_save = vsize;
			for (int j17 = 0; j17 < 4; j17 = faust_wrap_add(j17, 1)) {
				fRec17_perm[j17] = fRec17_tmp[faust_wrap_add(vsize, j17)];
			}
			for (int j19 = 0; j19 < 4; j19 = faust_wrap_add(j19, 1)) {
				fRec16_perm[j19] = fRec16_tmp[faust_wrap_add(vsize, j19)];
			}
			/* Recursive loop 6 */
			/* Pre code */
			for (int j20 = 0; j20 < 4; j20 = faust_wrap_add(j20, 1)) {
				fRec19_tmp[j20] = fRec19_perm[j20];
			}
			fYec5_idx = (faust_wrap_add(fYec5_idx, fYec5_idx_save)) & 2047;
			for (int j22 = 0; j22 < 4; j22 = faust_wrap_add(j22, 1)) {
				fRec18_tmp[j22] = fRec18_perm[j22];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec19[i] = fSlow0 * fRec19[faust_wrap_sub(i, 1)] + fSlow1 * fRec18[faust_wrap_sub(i, 1)];
				fYec5[(faust_wrap_add(i, fYec5_idx)) & 2047] = fZec0[i] + fSlow2 * fRec19[i];
				fRec18[i] = fYec5[(faust_wrap_sub(faust_wrap_add(i, fYec5_idx), 1491)) & 2047];
			}
			/* Post code */
			fYec5_idx_save = vsize;
			for (int j21 = 0; j21 < 4; j21 = faust_wrap_add(j21, 1)) {
				fRec19_perm[j21] = fRec19_tmp[faust_wrap_add(vsize, j21)];
			}
			for (int j23 = 0; j23 < 4; j23 = faust_wrap_add(j23, 1)) {
				fRec18_perm[j23] = fRec18_tmp[faust_wrap_add(vsize, j23)];
			}
			/* Recursive loop 7 */
			/* Pre code */
			for (int j24 = 0; j24 < 4; j24 = faust_wrap_add(j24, 1)) {
				fRec21_tmp[j24] = fRec21_perm[j24];
			}
			fYec6_idx = (faust_wrap_add(fYec6_idx, fYec6_idx_save)) & 2047;
			for (int j26 = 0; j26 < 4; j26 = faust_wrap_add(j26, 1)) {
				fRec20_tmp[j26] = fRec20_perm[j26];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec21[i] = fSlow0 * fRec21[faust_wrap_sub(i, 1)] + fSlow1 * fRec20[faust_wrap_sub(i, 1)];
				fYec6[(faust_wrap_add(i, fYec6_idx)) & 2047] = fZec0[i] + fSlow2 * fRec21[i];
				fRec20[i] = fYec6[(faust_wrap_sub(faust_wrap_add(i, fYec6_idx), 1557)) & 2047];
			}
			/* Post code */
			fYec6_idx_save = vsize;
			for (int j25 = 0; j25 < 4; j25 = faust_wrap_add(j25, 1)) {
				fRec21_perm[j25] = fRec21_tmp[faust_wrap_add(vsize, j25)];
			}
			for (int j27 = 0; j27 < 4; j27 = faust_wrap_add(j27, 1)) {
				fRec20_perm[j27] = fRec20_tmp[faust_wrap_add(vsize, j27)];
			}
			/* Recursive loop 8 */
			/* Pre code */
			for (int j28 = 0; j28 < 4; j28 = faust_wrap_add(j28, 1)) {
				fRec23_tmp[j28] = fRec23_perm[j28];
			}
			fYec7_idx = (faust_wrap_add(fYec7_idx, fYec7_idx_save)) & 2047;
			for (int j30 = 0; j30 < 4; j30 = faust_wrap_add(j30, 1)) {
				fRec22_tmp[j30] = fRec22_perm[j30];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec23[i] = fSlow0 * fRec23[faust_wrap_sub(i, 1)] + fSlow1 * fRec22[faust_wrap_sub(i, 1)];
				fYec7[(faust_wrap_add(i, fYec7_idx)) & 2047] = fZec0[i] + fSlow2 * fRec23[i];
				fRec22[i] = fYec7[(faust_wrap_sub(faust_wrap_add(i, fYec7_idx), 1617)) & 2047];
			}
			/* Post code */
			fYec7_idx_save = vsize;
			for (int j29 = 0; j29 < 4; j29 = faust_wrap_add(j29, 1)) {
				fRec23_perm[j29] = fRec23_tmp[faust_wrap_add(vsize, j29)];
			}
			for (int j31 = 0; j31 < 4; j31 = faust_wrap_add(j31, 1)) {
				fRec22_perm[j31] = fRec22_tmp[faust_wrap_add(vsize, j31)];
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec1[i] = fRec8[i] + fRec10[i] + fRec12[i] + fRec14[i] + fRec16[i] + fRec18[i] + fRec20[i] + fRec22[i];
			}
			/* Recursive loop 10 */
			/* Pre code */
			fYec8_idx = (faust_wrap_add(fYec8_idx, fYec8_idx_save)) & 1023;
			for (int j32 = 0; j32 < 4; j32 = faust_wrap_add(j32, 1)) {
				fRec6_tmp[j32] = fRec6_perm[j32];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec8[(faust_wrap_add(i, fYec8_idx)) & 1023] = fZec1[i] + 0.5 * fRec6[faust_wrap_sub(i, 1)];
				fRec6[i] = fYec8[(faust_wrap_sub(faust_wrap_add(i, fYec8_idx), 556)) & 1023];
				fRec7[i] = fRec6[faust_wrap_sub(i, 1)] - fZec1[i];
			}
			/* Post code */
			fYec8_idx_save = vsize;
			for (int j33 = 0; j33 < 4; j33 = faust_wrap_add(j33, 1)) {
				fRec6_perm[j33] = fRec6_tmp[faust_wrap_add(vsize, j33)];
			}
			/* Recursive loop 11 */
			/* Pre code */
			fYec9_idx = (faust_wrap_add(fYec9_idx, fYec9_idx_save)) & 511;
			for (int j34 = 0; j34 < 4; j34 = faust_wrap_add(j34, 1)) {
				fRec4_tmp[j34] = fRec4_perm[j34];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec9[(faust_wrap_add(i, fYec9_idx)) & 511] = fRec7[i] + 0.5 * fRec4[faust_wrap_sub(i, 1)];
				fRec4[i] = fYec9[(faust_wrap_sub(faust_wrap_add(i, fYec9_idx), 441)) & 511];
				fRec5[i] = fRec4[faust_wrap_sub(i, 1)] - fRec7[i];
			}
			/* Post code */
			fYec9_idx_save = vsize;
			for (int j35 = 0; j35 < 4; j35 = faust_wrap_add(j35, 1)) {
				fRec4_perm[j35] = fRec4_tmp[faust_wrap_add(vsize, j35)];
			}
			/* Recursive loop 12 */
			/* Pre code */
			fYec10_idx = (faust_wrap_add(fYec10_idx, fYec10_idx_save)) & 511;
			for (int j36 = 0; j36 < 4; j36 = faust_wrap_add(j36, 1)) {
				fRec2_tmp[j36] = fRec2_perm[j36];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec10[(faust_wrap_add(i, fYec10_idx)) & 511] = fRec5[i] + 0.5 * fRec2[faust_wrap_sub(i, 1)];
				fRec2[i] = fYec10[(faust_wrap_sub(faust_wrap_add(i, fYec10_idx), 341)) & 511];
				fRec3[i] = fRec2[faust_wrap_sub(i, 1)] - fRec5[i];
			}
			/* Post code */
			fYec10_idx_save = vsize;
			for (int j37 = 0; j37 < 4; j37 = faust_wrap_add(j37, 1)) {
				fRec2_perm[j37] = fRec2_tmp[faust_wrap_add(vsize, j37)];
			}
			/* Recursive loop 13 */
			/* Pre code */
			fYec11_idx = (faust_wrap_add(fYec11_idx, fYec11_idx_save)) & 255;
			for (int j38 = 0; j38 < 4; j38 = faust_wrap_add(j38, 1)) {
				fRec0_tmp[j38] = fRec0_perm[j38];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec11[(faust_wrap_add(i, fYec11_idx)) & 255] = fRec3[i] + 0.5 * fRec0[faust_wrap_sub(i, 1)];
				fRec0[i] = fYec11[(faust_wrap_sub(faust_wrap_add(i, fYec11_idx), 225)) & 255];
				fRec1[i] = fRec0[faust_wrap_sub(i, 1)] - fRec3[i];
			}
			/* Post code */
			fYec11_idx_save = vsize;
			for (int j39 = 0; j39 < 4; j39 = faust_wrap_add(j39, 1)) {
				fRec0_perm[j39] = fRec0_tmp[faust_wrap_add(vsize, j39)];
			}
			/* Vectorizable loop 14 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fSlow3 * fRec1[i] + fSlow4 * static_cast<double>(input0[i]));
			}
			/* Recursive loop 15 */
			/* Pre code */
			for (int j40 = 0; j40 < 4; j40 = faust_wrap_add(j40, 1)) {
				fRec33_tmp[j40] = fRec33_perm[j40];
			}
			fYec12_idx = (faust_wrap_add(fYec12_idx, fYec12_idx_save)) & 2047;
			for (int j42 = 0; j42 < 4; j42 = faust_wrap_add(j42, 1)) {
				fRec32_tmp[j42] = fRec32_perm[j42];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec33[i] = fSlow0 * fRec33[faust_wrap_sub(i, 1)] + fSlow1 * fRec32[faust_wrap_sub(i, 1)];
				fYec12[(faust_wrap_add(i, fYec12_idx)) & 2047] = fZec0[i] + fSlow2 * fRec33[i];
				fRec32[i] = fYec12[(faust_wrap_sub(faust_wrap_add(i, fYec12_idx), 1139)) & 2047];
			}
			/* Post code */
			fYec12_idx_save = vsize;
			for (int j41 = 0; j41 < 4; j41 = faust_wrap_add(j41, 1)) {
				fRec33_perm[j41] = fRec33_tmp[faust_wrap_add(vsize, j41)];
			}
			for (int j43 = 0; j43 < 4; j43 = faust_wrap_add(j43, 1)) {
				fRec32_perm[j43] = fRec32_tmp[faust_wrap_add(vsize, j43)];
			}
			/* Recursive loop 16 */
			/* Pre code */
			for (int j44 = 0; j44 < 4; j44 = faust_wrap_add(j44, 1)) {
				fRec35_tmp[j44] = fRec35_perm[j44];
			}
			fYec13_idx = (faust_wrap_add(fYec13_idx, fYec13_idx_save)) & 2047;
			for (int j46 = 0; j46 < 4; j46 = faust_wrap_add(j46, 1)) {
				fRec34_tmp[j46] = fRec34_perm[j46];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec35[i] = fSlow0 * fRec35[faust_wrap_sub(i, 1)] + fSlow1 * fRec34[faust_wrap_sub(i, 1)];
				fYec13[(faust_wrap_add(i, fYec13_idx)) & 2047] = fZec0[i] + fSlow2 * fRec35[i];
				fRec34[i] = fYec13[(faust_wrap_sub(faust_wrap_add(i, fYec13_idx), 1211)) & 2047];
			}
			/* Post code */
			fYec13_idx_save = vsize;
			for (int j45 = 0; j45 < 4; j45 = faust_wrap_add(j45, 1)) {
				fRec35_perm[j45] = fRec35_tmp[faust_wrap_add(vsize, j45)];
			}
			for (int j47 = 0; j47 < 4; j47 = faust_wrap_add(j47, 1)) {
				fRec34_perm[j47] = fRec34_tmp[faust_wrap_add(vsize, j47)];
			}
			/* Recursive loop 17 */
			/* Pre code */
			for (int j48 = 0; j48 < 4; j48 = faust_wrap_add(j48, 1)) {
				fRec37_tmp[j48] = fRec37_perm[j48];
			}
			fYec14_idx = (faust_wrap_add(fYec14_idx, fYec14_idx_save)) & 2047;
			for (int j50 = 0; j50 < 4; j50 = faust_wrap_add(j50, 1)) {
				fRec36_tmp[j50] = fRec36_perm[j50];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec37[i] = fSlow0 * fRec37[faust_wrap_sub(i, 1)] + fSlow1 * fRec36[faust_wrap_sub(i, 1)];
				fYec14[(faust_wrap_add(i, fYec14_idx)) & 2047] = fZec0[i] + fSlow2 * fRec37[i];
				fRec36[i] = fYec14[(faust_wrap_sub(faust_wrap_add(i, fYec14_idx), 1300)) & 2047];
			}
			/* Post code */
			fYec14_idx_save = vsize;
			for (int j49 = 0; j49 < 4; j49 = faust_wrap_add(j49, 1)) {
				fRec37_perm[j49] = fRec37_tmp[faust_wrap_add(vsize, j49)];
			}
			for (int j51 = 0; j51 < 4; j51 = faust_wrap_add(j51, 1)) {
				fRec36_perm[j51] = fRec36_tmp[faust_wrap_add(vsize, j51)];
			}
			/* Recursive loop 18 */
			/* Pre code */
			for (int j52 = 0; j52 < 4; j52 = faust_wrap_add(j52, 1)) {
				fRec39_tmp[j52] = fRec39_perm[j52];
			}
			fYec15_idx = (faust_wrap_add(fYec15_idx, fYec15_idx_save)) & 2047;
			for (int j54 = 0; j54 < 4; j54 = faust_wrap_add(j54, 1)) {
				fRec38_tmp[j54] = fRec38_perm[j54];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec39[i] = fSlow0 * fRec39[faust_wrap_sub(i, 1)] + fSlow1 * fRec38[faust_wrap_sub(i, 1)];
				fYec15[(faust_wrap_add(i, fYec15_idx)) & 2047] = fZec0[i] + fSlow2 * fRec39[i];
				fRec38[i] = fYec15[(faust_wrap_sub(faust_wrap_add(i, fYec15_idx), 1379)) & 2047];
			}
			/* Post code */
			fYec15_idx_save = vsize;
			for (int j53 = 0; j53 < 4; j53 = faust_wrap_add(j53, 1)) {
				fRec39_perm[j53] = fRec39_tmp[faust_wrap_add(vsize, j53)];
			}
			for (int j55 = 0; j55 < 4; j55 = faust_wrap_add(j55, 1)) {
				fRec38_perm[j55] = fRec38_tmp[faust_wrap_add(vsize, j55)];
			}
			/* Recursive loop 19 */
			/* Pre code */
			for (int j56 = 0; j56 < 4; j56 = faust_wrap_add(j56, 1)) {
				fRec41_tmp[j56] = fRec41_perm[j56];
			}
			fYec16_idx = (faust_wrap_add(fYec16_idx, fYec16_idx_save)) & 2047;
			for (int j58 = 0; j58 < 4; j58 = faust_wrap_add(j58, 1)) {
				fRec40_tmp[j58] = fRec40_perm[j58];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec41[i] = fSlow0 * fRec41[faust_wrap_sub(i, 1)] + fSlow1 * fRec40[faust_wrap_sub(i, 1)];
				fYec16[(faust_wrap_add(i, fYec16_idx)) & 2047] = fZec0[i] + fSlow2 * fRec41[i];
				fRec40[i] = fYec16[(faust_wrap_sub(faust_wrap_add(i, fYec16_idx), 1445)) & 2047];
			}
			/* Post code */
			fYec16_idx_save = vsize;
			for (int j57 = 0; j57 < 4; j57 = faust_wrap_add(j57, 1)) {
				fRec41_perm[j57] = fRec41_tmp[faust_wrap_add(vsize, j57)];
			}
			for (int j59 = 0; j59 < 4; j59 = faust_wrap_add(j59, 1)) {
				fRec40_perm[j59] = fRec40_tmp[faust_wrap_add(vsize, j59)];
			}
			/* Recursive loop 20 */
			/* Pre code */
			for (int j60 = 0; j60 < 4; j60 = faust_wrap_add(j60, 1)) {
				fRec43_tmp[j60] = fRec43_perm[j60];
			}
			fYec17_idx = (faust_wrap_add(fYec17_idx, fYec17_idx_save)) & 2047;
			for (int j62 = 0; j62 < 4; j62 = faust_wrap_add(j62, 1)) {
				fRec42_tmp[j62] = fRec42_perm[j62];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec43[i] = fSlow0 * fRec43[faust_wrap_sub(i, 1)] + fSlow1 * fRec42[faust_wrap_sub(i, 1)];
				fYec17[(faust_wrap_add(i, fYec17_idx)) & 2047] = fZec0[i] + fSlow2 * fRec43[i];
				fRec42[i] = fYec17[(faust_wrap_sub(faust_wrap_add(i, fYec17_idx), 1514)) & 2047];
			}
			/* Post code */
			fYec17_idx_save = vsize;
			for (int j61 = 0; j61 < 4; j61 = faust_wrap_add(j61, 1)) {
				fRec43_perm[j61] = fRec43_tmp[faust_wrap_add(vsize, j61)];
			}
			for (int j63 = 0; j63 < 4; j63 = faust_wrap_add(j63, 1)) {
				fRec42_perm[j63] = fRec42_tmp[faust_wrap_add(vsize, j63)];
			}
			/* Recursive loop 21 */
			/* Pre code */
			for (int j64 = 0; j64 < 4; j64 = faust_wrap_add(j64, 1)) {
				fRec45_tmp[j64] = fRec45_perm[j64];
			}
			fYec18_idx = (faust_wrap_add(fYec18_idx, fYec18_idx_save)) & 2047;
			for (int j66 = 0; j66 < 4; j66 = faust_wrap_add(j66, 1)) {
				fRec44_tmp[j66] = fRec44_perm[j66];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec45[i] = fSlow0 * fRec45[faust_wrap_sub(i, 1)] + fSlow1 * fRec44[faust_wrap_sub(i, 1)];
				fYec18[(faust_wrap_add(i, fYec18_idx)) & 2047] = fZec0[i] + fSlow2 * fRec45[i];
				fRec44[i] = fYec18[(faust_wrap_sub(faust_wrap_add(i, fYec18_idx), 1580)) & 2047];
			}
			/* Post code */
			fYec18_idx_save = vsize;
			for (int j65 = 0; j65 < 4; j65 = faust_wrap_add(j65, 1)) {
				fRec45_perm[j65] = fRec45_tmp[faust_wrap_add(vsize, j65)];
			}
			for (int j67 = 0; j67 < 4; j67 = faust_wrap_add(j67, 1)) {
				fRec44_perm[j67] = fRec44_tmp[faust_wrap_add(vsize, j67)];
			}
			/* Recursive loop 22 */
			/* Pre code */
			for (int j68 = 0; j68 < 4; j68 = faust_wrap_add(j68, 1)) {
				fRec47_tmp[j68] = fRec47_perm[j68];
			}
			fYec19_idx = (faust_wrap_add(fYec19_idx, fYec19_idx_save)) & 2047;
			for (int j70 = 0; j70 < 4; j70 = faust_wrap_add(j70, 1)) {
				fRec46_tmp[j70] = fRec46_perm[j70];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec47[i] = fSlow0 * fRec47[faust_wrap_sub(i, 1)] + fSlow1 * fRec46[faust_wrap_sub(i, 1)];
				fYec19[(faust_wrap_add(i, fYec19_idx)) & 2047] = fZec0[i] + fSlow2 * fRec47[i];
				fRec46[i] = fYec19[(faust_wrap_sub(faust_wrap_add(i, fYec19_idx), 1640)) & 2047];
			}
			/* Post code */
			fYec19_idx_save = vsize;
			for (int j69 = 0; j69 < 4; j69 = faust_wrap_add(j69, 1)) {
				fRec47_perm[j69] = fRec47_tmp[faust_wrap_add(vsize, j69)];
			}
			for (int j71 = 0; j71 < 4; j71 = faust_wrap_add(j71, 1)) {
				fRec46_perm[j71] = fRec46_tmp[faust_wrap_add(vsize, j71)];
			}
			/* Vectorizable loop 23 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec2[i] = fRec32[i] + fRec34[i] + fRec36[i] + fRec38[i] + fRec40[i] + fRec42[i] + fRec44[i] + fRec46[i];
			}
			/* Recursive loop 24 */
			/* Pre code */
			fYec20_idx = (faust_wrap_add(fYec20_idx, fYec20_idx_save)) & 1023;
			for (int j72 = 0; j72 < 4; j72 = faust_wrap_add(j72, 1)) {
				fRec30_tmp[j72] = fRec30_perm[j72];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec20[(faust_wrap_add(i, fYec20_idx)) & 1023] = fZec2[i] + 0.5 * fRec30[faust_wrap_sub(i, 1)];
				fRec30[i] = fYec20[(faust_wrap_sub(faust_wrap_add(i, fYec20_idx), 579)) & 1023];
				fRec31[i] = fRec30[faust_wrap_sub(i, 1)] - fZec2[i];
			}
			/* Post code */
			fYec20_idx_save = vsize;
			for (int j73 = 0; j73 < 4; j73 = faust_wrap_add(j73, 1)) {
				fRec30_perm[j73] = fRec30_tmp[faust_wrap_add(vsize, j73)];
			}
			/* Recursive loop 25 */
			/* Pre code */
			fYec21_idx = (faust_wrap_add(fYec21_idx, fYec21_idx_save)) & 511;
			for (int j74 = 0; j74 < 4; j74 = faust_wrap_add(j74, 1)) {
				fRec28_tmp[j74] = fRec28_perm[j74];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec21[(faust_wrap_add(i, fYec21_idx)) & 511] = fRec31[i] + 0.5 * fRec28[faust_wrap_sub(i, 1)];
				fRec28[i] = fYec21[(faust_wrap_sub(faust_wrap_add(i, fYec21_idx), 464)) & 511];
				fRec29[i] = fRec28[faust_wrap_sub(i, 1)] - fRec31[i];
			}
			/* Post code */
			fYec21_idx_save = vsize;
			for (int j75 = 0; j75 < 4; j75 = faust_wrap_add(j75, 1)) {
				fRec28_perm[j75] = fRec28_tmp[faust_wrap_add(vsize, j75)];
			}
			/* Recursive loop 26 */
			/* Pre code */
			fYec22_idx = (faust_wrap_add(fYec22_idx, fYec22_idx_save)) & 511;
			for (int j76 = 0; j76 < 4; j76 = faust_wrap_add(j76, 1)) {
				fRec26_tmp[j76] = fRec26_perm[j76];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec22[(faust_wrap_add(i, fYec22_idx)) & 511] = fRec29[i] + 0.5 * fRec26[faust_wrap_sub(i, 1)];
				fRec26[i] = fYec22[(faust_wrap_sub(faust_wrap_add(i, fYec22_idx), 364)) & 511];
				fRec27[i] = fRec26[faust_wrap_sub(i, 1)] - fRec29[i];
			}
			/* Post code */
			fYec22_idx_save = vsize;
			for (int j77 = 0; j77 < 4; j77 = faust_wrap_add(j77, 1)) {
				fRec26_perm[j77] = fRec26_tmp[faust_wrap_add(vsize, j77)];
			}
			/* Recursive loop 27 */
			/* Pre code */
			fYec23_idx = (faust_wrap_add(fYec23_idx, fYec23_idx_save)) & 255;
			for (int j78 = 0; j78 < 4; j78 = faust_wrap_add(j78, 1)) {
				fRec24_tmp[j78] = fRec24_perm[j78];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec23[(faust_wrap_add(i, fYec23_idx)) & 255] = fRec27[i] + 0.5 * fRec24[faust_wrap_sub(i, 1)];
				fRec24[i] = fYec23[(faust_wrap_sub(faust_wrap_add(i, fYec23_idx), 248)) & 255];
				fRec25[i] = fRec24[faust_wrap_sub(i, 1)] - fRec27[i];
			}
			/* Post code */
			fYec23_idx_save = vsize;
			for (int j79 = 0; j79 < 4; j79 = faust_wrap_add(j79, 1)) {
				fRec24_perm[j79] = fRec24_tmp[faust_wrap_add(vsize, j79)];
			}
			/* Vectorizable loop 28 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fSlow3 * fRec25[i] + fSlow4 * static_cast<double>(input1[i]));
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
