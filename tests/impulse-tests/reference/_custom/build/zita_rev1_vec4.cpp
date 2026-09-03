/* ------------------------------------------------------------
name: "zita_rev1"
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

static double mydsp_faustpower2_f(double value) {
	return value * value;
}

class mydsp : public dsp {
	
 private:
	
	FAUSTFLOAT fVslider0;
	double fRec0_perm[4];
	FAUSTFLOAT fVslider1;
	double fRec1_perm[4];
	int fSampleRate;
	double fConst0;
	double fConst1;
	FAUSTFLOAT fVslider2;
	double fRec15_perm[4];
	double fConst2;
	FAUSTFLOAT fVslider3;
	double fConst3;
	double fConst4;
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT fVslider5;
	double fRec14_perm[4];
	double fYec0[32768];
	int fYec0_idx;
	int fYec0_idx_save;
	double fConst5;
	int iConst6;
	double fYec1[16384];
	int fYec1_idx;
	int fYec1_idx_save;
	double fConst7;
	FAUSTFLOAT fVslider6;
	double fYec2[2048];
	int fYec2_idx;
	int fYec2_idx_save;
	int iConst8;
	double fRec12_perm[4];
	double fRec19_perm[4];
	double fConst9;
	double fConst10;
	double fRec18_perm[4];
	double fYec3[32768];
	int fYec3_idx;
	int fYec3_idx_save;
	double fConst11;
	int iConst12;
	double fYec4[4096];
	int fYec4_idx;
	int fYec4_idx_save;
	int iConst13;
	double fRec16_perm[4];
	double fRec23_perm[4];
	double fConst14;
	double fConst15;
	double fRec22_perm[4];
	double fYec5[16384];
	int fYec5_idx;
	int fYec5_idx_save;
	double fConst16;
	int iConst17;
	double fYec6[4096];
	int fYec6_idx;
	int fYec6_idx_save;
	int iConst18;
	double fRec20_perm[4];
	double fRec27_perm[4];
	double fConst19;
	double fConst20;
	double fRec26_perm[4];
	double fYec7[32768];
	int fYec7_idx;
	int fYec7_idx_save;
	double fConst21;
	int iConst22;
	double fYec8[4096];
	int fYec8_idx;
	int fYec8_idx_save;
	int iConst23;
	double fRec24_perm[4];
	double fRec31_perm[4];
	double fConst24;
	double fConst25;
	double fRec30_perm[4];
	double fYec9[16384];
	int fYec9_idx;
	int fYec9_idx_save;
	double fConst26;
	int iConst27;
	double fYec10[16384];
	int fYec10_idx;
	int fYec10_idx_save;
	double fYec11[2048];
	int fYec11_idx;
	int fYec11_idx_save;
	int iConst28;
	double fRec28_perm[4];
	double fRec35_perm[4];
	double fConst29;
	double fConst30;
	double fRec34_perm[4];
	double fYec12[16384];
	int fYec12_idx;
	int fYec12_idx_save;
	double fConst31;
	int iConst32;
	double fYec13[4096];
	int fYec13_idx;
	int fYec13_idx_save;
	int iConst33;
	double fRec32_perm[4];
	double fRec39_perm[4];
	double fConst34;
	double fConst35;
	double fRec38_perm[4];
	double fYec14[16384];
	int fYec14_idx;
	int fYec14_idx_save;
	double fConst36;
	int iConst37;
	double fYec15[4096];
	int fYec15_idx;
	int fYec15_idx_save;
	int iConst38;
	double fRec36_perm[4];
	double fRec43_perm[4];
	double fConst39;
	double fConst40;
	double fRec42_perm[4];
	double fYec16[16384];
	int fYec16_idx;
	int fYec16_idx_save;
	double fConst41;
	int iConst42;
	double fYec17[2048];
	int fYec17_idx;
	int fYec17_idx_save;
	int iConst43;
	double fRec40_perm[4];
	double fRec4_perm[4];
	double fRec5_perm[4];
	double fRec6_perm[4];
	double fRec7_perm[4];
	double fRec8_perm[4];
	double fRec9_perm[4];
	double fRec10_perm[4];
	double fRec11_perm[4];
	FAUSTFLOAT fVslider7;
	FAUSTFLOAT fVslider8;
	double fRec3_perm[4];
	FAUSTFLOAT fVslider9;
	FAUSTFLOAT fVslider10;
	double fRec2_perm[4];
	double fRec45_perm[4];
	double fRec44_perm[4];
	
 public:
	mydsp() {
	}
	
	mydsp(const mydsp&) = default;
	
	virtual ~mydsp() = default;
	
	mydsp& operator=(const mydsp&) = default;
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-a /Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/archs/impulsearch.cpp -lang cpp -i -fpga-mem-th 4 -ct 1 -es 1 -mcd 4 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs");
		m->declare("effect.lib/name", "Faust Audio Effect Library");
		m->declare("effect.lib/zita_distrib2:author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("effect.lib/zita_distrib2:copyright", "Julius O. Smith III");
		m->declare("effect.lib/zita_distrib2:license", "STK-4.3");
		m->declare("effect.lib/zita_in_delay:author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("effect.lib/zita_in_delay:copyright", "Julius O. Smith III");
		m->declare("effect.lib/zita_in_delay:license", "STK-4.3");
		m->declare("effect.lib/zita_rev1_stereo:author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("effect.lib/zita_rev1_stereo:copyright", "Julius O. Smith III");
		m->declare("effect.lib/zita_rev1_stereo:license", "STK-4.3");
		m->declare("effect.lib/zita_rev_fdn:author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("effect.lib/zita_rev_fdn:copyright", "Julius O. Smith III");
		m->declare("effect.lib/zita_rev_fdn:license", "STK-4.3");
		m->declare("filename", "zita_rev1.dsp");
		m->declare("filter.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("filter.lib/copyright", "Julius O. Smith III");
		m->declare("filter.lib/license", "STK-4.3");
		m->declare("filter.lib/name", "Faust Filter Library");
		m->declare("filter.lib/reference", "https://ccrma.stanford.edu/~jos/filters/");
		m->declare("filter.lib/version", "1.29");
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
		m->declare("name", "zita_rev1");
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
		fConst1 = 3.141592653589793 / fConst0;
		fConst2 = 6.283185307179586 / fConst0;
		fConst3 = std::floor(0.219991 * fConst0 + 0.5);
		fConst4 = 6.907755278982138 * (fConst3 / fConst0);
		fConst5 = std::floor(0.019123 * fConst0 + 0.5);
		iConst6 = static_cast<int>(fConst3 - fConst5) & 16383;
		fConst7 = 0.001 * fConst0;
		iConst8 = static_cast<int>(fConst5 + -1.0) & 1023;
		fConst9 = std::floor(0.256891 * fConst0 + 0.5);
		fConst10 = 6.907755278982138 * (fConst9 / fConst0);
		fConst11 = std::floor(0.027333 * fConst0 + 0.5);
		iConst12 = static_cast<int>(fConst9 - fConst11) & 16383;
		iConst13 = static_cast<int>(fConst11 + -1.0) & 2047;
		fConst14 = std::floor(0.192303 * fConst0 + 0.5);
		fConst15 = 6.907755278982138 * (fConst14 / fConst0);
		fConst16 = std::floor(0.029291 * fConst0 + 0.5);
		iConst17 = static_cast<int>(fConst14 - fConst16) & 8191;
		iConst18 = static_cast<int>(fConst16 + -1.0) & 2047;
		fConst19 = std::floor(0.210389 * fConst0 + 0.5);
		fConst20 = 6.907755278982138 * (fConst19 / fConst0);
		fConst21 = std::floor(0.024421 * fConst0 + 0.5);
		iConst22 = static_cast<int>(fConst19 - fConst21) & 16383;
		iConst23 = static_cast<int>(fConst21 + -1.0) & 2047;
		fConst24 = std::floor(0.125 * fConst0 + 0.5);
		fConst25 = 6.907755278982138 * (fConst24 / fConst0);
		fConst26 = std::floor(0.013458 * fConst0 + 0.5);
		iConst27 = static_cast<int>(fConst24 - fConst26) & 8191;
		iConst28 = static_cast<int>(fConst26 + -1.0) & 1023;
		fConst29 = std::floor(0.127837 * fConst0 + 0.5);
		fConst30 = 6.907755278982138 * (fConst29 / fConst0);
		fConst31 = std::floor(0.031604 * fConst0 + 0.5);
		iConst32 = static_cast<int>(fConst29 - fConst31) & 8191;
		iConst33 = static_cast<int>(fConst31 + -1.0) & 2047;
		fConst34 = std::floor(0.174713 * fConst0 + 0.5);
		fConst35 = 6.907755278982138 * (fConst34 / fConst0);
		fConst36 = std::floor(0.022904 * fConst0 + 0.5);
		iConst37 = static_cast<int>(fConst34 - fConst36) & 8191;
		iConst38 = static_cast<int>(fConst36 + -1.0) & 2047;
		fConst39 = std::floor(0.153129 * fConst0 + 0.5);
		fConst40 = 6.907755278982138 * (fConst39 / fConst0);
		fConst41 = std::floor(0.020346 * fConst0 + 0.5);
		iConst42 = static_cast<int>(fConst39 - fConst41) & 8191;
		iConst43 = static_cast<int>(fConst41 + -1.0) & 1023;
	}
	
	virtual void instanceResetUserInterface() {
		fVslider0 = static_cast<FAUSTFLOAT>(16.79);
		fVslider1 = static_cast<FAUSTFLOAT>(0.4492);
		fVslider2 = static_cast<FAUSTFLOAT>(2e+02);
		fVslider3 = static_cast<FAUSTFLOAT>(6e+03);
		fVslider4 = static_cast<FAUSTFLOAT>(2.0);
		fVslider5 = static_cast<FAUSTFLOAT>(3.0);
		fVslider6 = static_cast<FAUSTFLOAT>(6e+01);
		fVslider7 = static_cast<FAUSTFLOAT>(315.0);
		fVslider8 = static_cast<FAUSTFLOAT>(0.0);
		fVslider9 = static_cast<FAUSTFLOAT>(1.5e+03);
		fVslider10 = static_cast<FAUSTFLOAT>(0.0);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 4; l0 = faust_wrap_add(l0, 1)) {
			fRec0_perm[l0] = 0.0;
		}
		for (int l1 = 0; l1 < 4; l1 = faust_wrap_add(l1, 1)) {
			fRec1_perm[l1] = 0.0;
		}
		for (int l2 = 0; l2 < 4; l2 = faust_wrap_add(l2, 1)) {
			fRec15_perm[l2] = 0.0;
		}
		for (int l3 = 0; l3 < 4; l3 = faust_wrap_add(l3, 1)) {
			fRec14_perm[l3] = 0.0;
		}
		for (int l4 = 0; l4 < 32768; l4 = faust_wrap_add(l4, 1)) {
			fYec0[l4] = 0.0;
		}
		fYec0_idx = 0;
		fYec0_idx_save = 0;
		for (int l5 = 0; l5 < 16384; l5 = faust_wrap_add(l5, 1)) {
			fYec1[l5] = 0.0;
		}
		fYec1_idx = 0;
		fYec1_idx_save = 0;
		for (int l6 = 0; l6 < 2048; l6 = faust_wrap_add(l6, 1)) {
			fYec2[l6] = 0.0;
		}
		fYec2_idx = 0;
		fYec2_idx_save = 0;
		for (int l7 = 0; l7 < 4; l7 = faust_wrap_add(l7, 1)) {
			fRec12_perm[l7] = 0.0;
		}
		for (int l8 = 0; l8 < 4; l8 = faust_wrap_add(l8, 1)) {
			fRec19_perm[l8] = 0.0;
		}
		for (int l9 = 0; l9 < 4; l9 = faust_wrap_add(l9, 1)) {
			fRec18_perm[l9] = 0.0;
		}
		for (int l10 = 0; l10 < 32768; l10 = faust_wrap_add(l10, 1)) {
			fYec3[l10] = 0.0;
		}
		fYec3_idx = 0;
		fYec3_idx_save = 0;
		for (int l11 = 0; l11 < 4096; l11 = faust_wrap_add(l11, 1)) {
			fYec4[l11] = 0.0;
		}
		fYec4_idx = 0;
		fYec4_idx_save = 0;
		for (int l12 = 0; l12 < 4; l12 = faust_wrap_add(l12, 1)) {
			fRec16_perm[l12] = 0.0;
		}
		for (int l13 = 0; l13 < 4; l13 = faust_wrap_add(l13, 1)) {
			fRec23_perm[l13] = 0.0;
		}
		for (int l14 = 0; l14 < 4; l14 = faust_wrap_add(l14, 1)) {
			fRec22_perm[l14] = 0.0;
		}
		for (int l15 = 0; l15 < 16384; l15 = faust_wrap_add(l15, 1)) {
			fYec5[l15] = 0.0;
		}
		fYec5_idx = 0;
		fYec5_idx_save = 0;
		for (int l16 = 0; l16 < 4096; l16 = faust_wrap_add(l16, 1)) {
			fYec6[l16] = 0.0;
		}
		fYec6_idx = 0;
		fYec6_idx_save = 0;
		for (int l17 = 0; l17 < 4; l17 = faust_wrap_add(l17, 1)) {
			fRec20_perm[l17] = 0.0;
		}
		for (int l18 = 0; l18 < 4; l18 = faust_wrap_add(l18, 1)) {
			fRec27_perm[l18] = 0.0;
		}
		for (int l19 = 0; l19 < 4; l19 = faust_wrap_add(l19, 1)) {
			fRec26_perm[l19] = 0.0;
		}
		for (int l20 = 0; l20 < 32768; l20 = faust_wrap_add(l20, 1)) {
			fYec7[l20] = 0.0;
		}
		fYec7_idx = 0;
		fYec7_idx_save = 0;
		for (int l21 = 0; l21 < 4096; l21 = faust_wrap_add(l21, 1)) {
			fYec8[l21] = 0.0;
		}
		fYec8_idx = 0;
		fYec8_idx_save = 0;
		for (int l22 = 0; l22 < 4; l22 = faust_wrap_add(l22, 1)) {
			fRec24_perm[l22] = 0.0;
		}
		for (int l23 = 0; l23 < 4; l23 = faust_wrap_add(l23, 1)) {
			fRec31_perm[l23] = 0.0;
		}
		for (int l24 = 0; l24 < 4; l24 = faust_wrap_add(l24, 1)) {
			fRec30_perm[l24] = 0.0;
		}
		for (int l25 = 0; l25 < 16384; l25 = faust_wrap_add(l25, 1)) {
			fYec9[l25] = 0.0;
		}
		fYec9_idx = 0;
		fYec9_idx_save = 0;
		for (int l26 = 0; l26 < 16384; l26 = faust_wrap_add(l26, 1)) {
			fYec10[l26] = 0.0;
		}
		fYec10_idx = 0;
		fYec10_idx_save = 0;
		for (int l27 = 0; l27 < 2048; l27 = faust_wrap_add(l27, 1)) {
			fYec11[l27] = 0.0;
		}
		fYec11_idx = 0;
		fYec11_idx_save = 0;
		for (int l28 = 0; l28 < 4; l28 = faust_wrap_add(l28, 1)) {
			fRec28_perm[l28] = 0.0;
		}
		for (int l29 = 0; l29 < 4; l29 = faust_wrap_add(l29, 1)) {
			fRec35_perm[l29] = 0.0;
		}
		for (int l30 = 0; l30 < 4; l30 = faust_wrap_add(l30, 1)) {
			fRec34_perm[l30] = 0.0;
		}
		for (int l31 = 0; l31 < 16384; l31 = faust_wrap_add(l31, 1)) {
			fYec12[l31] = 0.0;
		}
		fYec12_idx = 0;
		fYec12_idx_save = 0;
		for (int l32 = 0; l32 < 4096; l32 = faust_wrap_add(l32, 1)) {
			fYec13[l32] = 0.0;
		}
		fYec13_idx = 0;
		fYec13_idx_save = 0;
		for (int l33 = 0; l33 < 4; l33 = faust_wrap_add(l33, 1)) {
			fRec32_perm[l33] = 0.0;
		}
		for (int l34 = 0; l34 < 4; l34 = faust_wrap_add(l34, 1)) {
			fRec39_perm[l34] = 0.0;
		}
		for (int l35 = 0; l35 < 4; l35 = faust_wrap_add(l35, 1)) {
			fRec38_perm[l35] = 0.0;
		}
		for (int l36 = 0; l36 < 16384; l36 = faust_wrap_add(l36, 1)) {
			fYec14[l36] = 0.0;
		}
		fYec14_idx = 0;
		fYec14_idx_save = 0;
		for (int l37 = 0; l37 < 4096; l37 = faust_wrap_add(l37, 1)) {
			fYec15[l37] = 0.0;
		}
		fYec15_idx = 0;
		fYec15_idx_save = 0;
		for (int l38 = 0; l38 < 4; l38 = faust_wrap_add(l38, 1)) {
			fRec36_perm[l38] = 0.0;
		}
		for (int l39 = 0; l39 < 4; l39 = faust_wrap_add(l39, 1)) {
			fRec43_perm[l39] = 0.0;
		}
		for (int l40 = 0; l40 < 4; l40 = faust_wrap_add(l40, 1)) {
			fRec42_perm[l40] = 0.0;
		}
		for (int l41 = 0; l41 < 16384; l41 = faust_wrap_add(l41, 1)) {
			fYec16[l41] = 0.0;
		}
		fYec16_idx = 0;
		fYec16_idx_save = 0;
		for (int l42 = 0; l42 < 2048; l42 = faust_wrap_add(l42, 1)) {
			fYec17[l42] = 0.0;
		}
		fYec17_idx = 0;
		fYec17_idx_save = 0;
		for (int l43 = 0; l43 < 4; l43 = faust_wrap_add(l43, 1)) {
			fRec40_perm[l43] = 0.0;
		}
		for (int l44 = 0; l44 < 4; l44 = faust_wrap_add(l44, 1)) {
			fRec4_perm[l44] = 0.0;
		}
		for (int l45 = 0; l45 < 4; l45 = faust_wrap_add(l45, 1)) {
			fRec5_perm[l45] = 0.0;
		}
		for (int l46 = 0; l46 < 4; l46 = faust_wrap_add(l46, 1)) {
			fRec6_perm[l46] = 0.0;
		}
		for (int l47 = 0; l47 < 4; l47 = faust_wrap_add(l47, 1)) {
			fRec7_perm[l47] = 0.0;
		}
		for (int l48 = 0; l48 < 4; l48 = faust_wrap_add(l48, 1)) {
			fRec8_perm[l48] = 0.0;
		}
		for (int l49 = 0; l49 < 4; l49 = faust_wrap_add(l49, 1)) {
			fRec9_perm[l49] = 0.0;
		}
		for (int l50 = 0; l50 < 4; l50 = faust_wrap_add(l50, 1)) {
			fRec10_perm[l50] = 0.0;
		}
		for (int l51 = 0; l51 < 4; l51 = faust_wrap_add(l51, 1)) {
			fRec11_perm[l51] = 0.0;
		}
		for (int l52 = 0; l52 < 4; l52 = faust_wrap_add(l52, 1)) {
			fRec3_perm[l52] = 0.0;
		}
		for (int l53 = 0; l53 < 4; l53 = faust_wrap_add(l53, 1)) {
			fRec2_perm[l53] = 0.0;
		}
		for (int l54 = 0; l54 < 4; l54 = faust_wrap_add(l54, 1)) {
			fRec45_perm[l54] = 0.0;
		}
		for (int l55 = 0; l55 < 4; l55 = faust_wrap_add(l55, 1)) {
			fRec44_perm[l55] = 0.0;
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
		ui_interface->declare(0, "0", "");
		ui_interface->declare(0, "tooltip", "~ ZITA REV1 FEEDBACK DELAY NETWORK (FDN) & SCHROEDER ALLPASS-COMB REVERBERATOR (8x8). See Faust's effect.lib for documentation and references");
		ui_interface->openHorizontalBox("Zita_Rev1");
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("Input");
		ui_interface->declare(&fVslider6, "1", "");
		ui_interface->declare(&fVslider6, "style", "knob");
		ui_interface->declare(&fVslider6, "tooltip", "Delay in ms before reverberation begins");
		ui_interface->declare(&fVslider6, "unit", "ms");
		ui_interface->addVerticalSlider("In Delay", &fVslider6, FAUSTFLOAT(6e+01), FAUSTFLOAT(2e+01), FAUSTFLOAT(1e+02), FAUSTFLOAT(1.0));
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("Decay Times in Bands (see tooltips)");
		ui_interface->declare(&fVslider2, "1", "");
		ui_interface->declare(&fVslider2, "scale", "log");
		ui_interface->declare(&fVslider2, "style", "knob");
		ui_interface->declare(&fVslider2, "tooltip", "Crossover frequency (Hz) separating low and middle frequencies");
		ui_interface->declare(&fVslider2, "unit", "Hz");
		ui_interface->addVerticalSlider("LF X", &fVslider2, FAUSTFLOAT(2e+02), FAUSTFLOAT(5e+01), FAUSTFLOAT(1e+03), FAUSTFLOAT(1.0));
		ui_interface->declare(&fVslider5, "2", "");
		ui_interface->declare(&fVslider5, "scale", "log");
		ui_interface->declare(&fVslider5, "style", "knob");
		ui_interface->declare(&fVslider5, "tooltip", "T60 = time (in seconds) to decay 60dB in low-frequency band");
		ui_interface->declare(&fVslider5, "unit", "s");
		ui_interface->addVerticalSlider("Low RT60", &fVslider5, FAUSTFLOAT(3.0), FAUSTFLOAT(1.0), FAUSTFLOAT(8.0), FAUSTFLOAT(0.1));
		ui_interface->declare(&fVslider4, "3", "");
		ui_interface->declare(&fVslider4, "scale", "log");
		ui_interface->declare(&fVslider4, "style", "knob");
		ui_interface->declare(&fVslider4, "tooltip", "T60 = time (in seconds) to decay 60dB in middle band");
		ui_interface->declare(&fVslider4, "unit", "s");
		ui_interface->addVerticalSlider("Mid RT60", &fVslider4, FAUSTFLOAT(2.0), FAUSTFLOAT(1.0), FAUSTFLOAT(8.0), FAUSTFLOAT(0.1));
		ui_interface->declare(&fVslider3, "4", "");
		ui_interface->declare(&fVslider3, "scale", "log");
		ui_interface->declare(&fVslider3, "style", "knob");
		ui_interface->declare(&fVslider3, "tooltip", "Frequency (Hz) at which the high-frequency T60 is half the middle-band's T60");
		ui_interface->declare(&fVslider3, "unit", "Hz");
		ui_interface->addVerticalSlider("HF Damping", &fVslider3, FAUSTFLOAT(6e+03), FAUSTFLOAT(1.5e+03), FAUSTFLOAT(2.352e+04), FAUSTFLOAT(1.0));
		ui_interface->closeBox();
		ui_interface->declare(0, "3", "");
		ui_interface->openHorizontalBox("RM Peaking Equalizer 1");
		ui_interface->declare(&fVslider7, "1", "");
		ui_interface->declare(&fVslider7, "scale", "log");
		ui_interface->declare(&fVslider7, "style", "knob");
		ui_interface->declare(&fVslider7, "tooltip", "Center-frequency of second-order Regalia-Mitra peaking equalizer section 1");
		ui_interface->declare(&fVslider7, "unit", "Hz");
		ui_interface->addVerticalSlider("Eq1 Freq", &fVslider7, FAUSTFLOAT(315.0), FAUSTFLOAT(4e+01), FAUSTFLOAT(2.5e+03), FAUSTFLOAT(1.0));
		ui_interface->declare(&fVslider8, "2", "");
		ui_interface->declare(&fVslider8, "style", "knob");
		ui_interface->declare(&fVslider8, "tooltip", "Peak level in dB of second-order Regalia-Mitra peaking equalizer section 1");
		ui_interface->declare(&fVslider8, "unit", "dB");
		ui_interface->addVerticalSlider("Eq1 Level", &fVslider8, FAUSTFLOAT(0.0), FAUSTFLOAT(-15.0), FAUSTFLOAT(15.0), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->declare(0, "4", "");
		ui_interface->openHorizontalBox("RM Peaking Equalizer 2");
		ui_interface->declare(&fVslider9, "1", "");
		ui_interface->declare(&fVslider9, "scale", "log");
		ui_interface->declare(&fVslider9, "style", "knob");
		ui_interface->declare(&fVslider9, "tooltip", "Center-frequency of second-order Regalia-Mitra peaking equalizer section 2");
		ui_interface->declare(&fVslider9, "unit", "Hz");
		ui_interface->addVerticalSlider("Eq2 Freq", &fVslider9, FAUSTFLOAT(1.5e+03), FAUSTFLOAT(1.6e+02), FAUSTFLOAT(1e+04), FAUSTFLOAT(1.0));
		ui_interface->declare(&fVslider10, "2", "");
		ui_interface->declare(&fVslider10, "style", "knob");
		ui_interface->declare(&fVslider10, "tooltip", "Peak level in dB of second-order Regalia-Mitra peaking equalizer section 2");
		ui_interface->declare(&fVslider10, "unit", "dB");
		ui_interface->addVerticalSlider("Eq2 Level", &fVslider10, FAUSTFLOAT(0.0), FAUSTFLOAT(-15.0), FAUSTFLOAT(15.0), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->declare(0, "5", "");
		ui_interface->openHorizontalBox("Output");
		ui_interface->declare(&fVslider1, "1", "");
		ui_interface->declare(&fVslider1, "style", "knob");
		ui_interface->declare(&fVslider1, "tooltip", "-1 = dry, 1 = wet");
		ui_interface->addVerticalSlider("Dry/Wet Mix", &fVslider1, FAUSTFLOAT(0.4492), FAUSTFLOAT(-1.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.01));
		ui_interface->declare(&fVslider0, "2", "");
		ui_interface->declare(&fVslider0, "style", "knob");
		ui_interface->declare(&fVslider0, "tooltip", "Output scale factor");
		ui_interface->declare(&fVslider0, "unit", "dB");
		ui_interface->addVerticalSlider("Level", &fVslider0, FAUSTFLOAT(16.79), FAUSTFLOAT(-7e+01), FAUSTFLOAT(4e+01), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0_ptr = inputs[0];
		FAUSTFLOAT* input1_ptr = inputs[1];
		FAUSTFLOAT* output0_ptr = outputs[0];
		FAUSTFLOAT* output1_ptr = outputs[1];
		double fSlow0 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * static_cast<double>(fVslider0));
		double fRec0_tmp[8];
		double* fRec0 = &fRec0_tmp[4];
		double fSlow1 = 0.0010000000000000009 * static_cast<double>(fVslider1);
		double fRec1_tmp[8];
		double* fRec1 = &fRec1_tmp[4];
		double fSlow2 = 1.0 / std::tan(fConst1 * static_cast<double>(fVslider2));
		double fSlow3 = 1.0 / (fSlow2 + 1.0);
		double fSlow4 = 1.0 - fSlow2;
		double fRec15_tmp[8];
		double* fRec15 = &fRec15_tmp[4];
		double fSlow5 = std::cos(fConst2 * static_cast<double>(fVslider3));
		double fSlow6 = static_cast<double>(fVslider4);
		double fSlow7 = std::exp(-(fConst4 / fSlow6));
		double fSlow8 = mydsp_faustpower2_f(fSlow7);
		double fSlow9 = 1.0 - fSlow5 * fSlow8;
		double fSlow10 = 1.0 - fSlow8;
		double fSlow11 = fSlow9 / fSlow10;
		double fSlow12 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow9) / mydsp_faustpower2_f(fSlow10) + -1.0));
		double fSlow13 = fSlow11 - fSlow12;
		double fSlow14 = fSlow7 * (fSlow12 + (1.0 - fSlow11));
		double fSlow15 = static_cast<double>(fVslider5);
		double fSlow16 = std::exp(-(fConst4 / fSlow15)) / fSlow7 + -1.0;
		double fRec14_tmp[8];
		double* fRec14 = &fRec14_tmp[4];
		double fZec0[4];
		int iSlow17 = static_cast<int>(fConst7 * static_cast<double>(fVslider6)) & 8191;
		double fZec1[4];
		double fRec12_tmp[8];
		double* fRec12 = &fRec12_tmp[4];
		double fRec13[4];
		double fRec19_tmp[8];
		double* fRec19 = &fRec19_tmp[4];
		double fSlow18 = std::exp(-(fConst10 / fSlow6));
		double fSlow19 = mydsp_faustpower2_f(fSlow18);
		double fSlow20 = 1.0 - fSlow5 * fSlow19;
		double fSlow21 = 1.0 - fSlow19;
		double fSlow22 = fSlow20 / fSlow21;
		double fSlow23 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow20) / mydsp_faustpower2_f(fSlow21) + -1.0));
		double fSlow24 = fSlow22 - fSlow23;
		double fSlow25 = fSlow18 * (fSlow23 + (1.0 - fSlow22));
		double fSlow26 = std::exp(-(fConst10 / fSlow15)) / fSlow18 + -1.0;
		double fRec18_tmp[8];
		double* fRec18 = &fRec18_tmp[4];
		double fZec2[4];
		double fRec16_tmp[8];
		double* fRec16 = &fRec16_tmp[4];
		double fRec17[4];
		double fRec23_tmp[8];
		double* fRec23 = &fRec23_tmp[4];
		double fSlow27 = std::exp(-(fConst15 / fSlow6));
		double fSlow28 = mydsp_faustpower2_f(fSlow27);
		double fSlow29 = 1.0 - fSlow5 * fSlow28;
		double fSlow30 = 1.0 - fSlow28;
		double fSlow31 = fSlow29 / fSlow30;
		double fSlow32 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow29) / mydsp_faustpower2_f(fSlow30) + -1.0));
		double fSlow33 = fSlow31 - fSlow32;
		double fSlow34 = fSlow27 * (fSlow32 + (1.0 - fSlow31));
		double fSlow35 = std::exp(-(fConst15 / fSlow15)) / fSlow27 + -1.0;
		double fRec22_tmp[8];
		double* fRec22 = &fRec22_tmp[4];
		double fRec20_tmp[8];
		double* fRec20 = &fRec20_tmp[4];
		double fRec21[4];
		double fRec27_tmp[8];
		double* fRec27 = &fRec27_tmp[4];
		double fSlow36 = std::exp(-(fConst20 / fSlow6));
		double fSlow37 = mydsp_faustpower2_f(fSlow36);
		double fSlow38 = 1.0 - fSlow5 * fSlow37;
		double fSlow39 = 1.0 - fSlow37;
		double fSlow40 = fSlow38 / fSlow39;
		double fSlow41 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow38) / mydsp_faustpower2_f(fSlow39) + -1.0));
		double fSlow42 = fSlow40 - fSlow41;
		double fSlow43 = fSlow36 * (fSlow41 + (1.0 - fSlow40));
		double fSlow44 = std::exp(-(fConst20 / fSlow15)) / fSlow36 + -1.0;
		double fRec26_tmp[8];
		double* fRec26 = &fRec26_tmp[4];
		double fRec24_tmp[8];
		double* fRec24 = &fRec24_tmp[4];
		double fRec25[4];
		double fRec31_tmp[8];
		double* fRec31 = &fRec31_tmp[4];
		double fSlow45 = std::exp(-(fConst25 / fSlow6));
		double fSlow46 = mydsp_faustpower2_f(fSlow45);
		double fSlow47 = 1.0 - fSlow5 * fSlow46;
		double fSlow48 = 1.0 - fSlow46;
		double fSlow49 = fSlow47 / fSlow48;
		double fSlow50 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow47) / mydsp_faustpower2_f(fSlow48) + -1.0));
		double fSlow51 = fSlow49 - fSlow50;
		double fSlow52 = fSlow45 * (fSlow50 + (1.0 - fSlow49));
		double fSlow53 = std::exp(-(fConst25 / fSlow15)) / fSlow45 + -1.0;
		double fRec30_tmp[8];
		double* fRec30 = &fRec30_tmp[4];
		double fZec3[4];
		double fRec28_tmp[8];
		double* fRec28 = &fRec28_tmp[4];
		double fRec29[4];
		double fRec35_tmp[8];
		double* fRec35 = &fRec35_tmp[4];
		double fSlow54 = std::exp(-(fConst30 / fSlow6));
		double fSlow55 = mydsp_faustpower2_f(fSlow54);
		double fSlow56 = 1.0 - fSlow5 * fSlow55;
		double fSlow57 = 1.0 - fSlow55;
		double fSlow58 = fSlow56 / fSlow57;
		double fSlow59 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow56) / mydsp_faustpower2_f(fSlow57) + -1.0));
		double fSlow60 = fSlow58 - fSlow59;
		double fSlow61 = fSlow54 * (fSlow59 + (1.0 - fSlow58));
		double fSlow62 = std::exp(-(fConst30 / fSlow15)) / fSlow54 + -1.0;
		double fRec34_tmp[8];
		double* fRec34 = &fRec34_tmp[4];
		double fRec32_tmp[8];
		double* fRec32 = &fRec32_tmp[4];
		double fRec33[4];
		double fRec39_tmp[8];
		double* fRec39 = &fRec39_tmp[4];
		double fSlow63 = std::exp(-(fConst35 / fSlow6));
		double fSlow64 = mydsp_faustpower2_f(fSlow63);
		double fSlow65 = 1.0 - fSlow5 * fSlow64;
		double fSlow66 = 1.0 - fSlow64;
		double fSlow67 = fSlow65 / fSlow66;
		double fSlow68 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow65) / mydsp_faustpower2_f(fSlow66) + -1.0));
		double fSlow69 = fSlow67 - fSlow68;
		double fSlow70 = fSlow63 * (fSlow68 + (1.0 - fSlow67));
		double fSlow71 = std::exp(-(fConst35 / fSlow15)) / fSlow63 + -1.0;
		double fRec38_tmp[8];
		double* fRec38 = &fRec38_tmp[4];
		double fRec36_tmp[8];
		double* fRec36 = &fRec36_tmp[4];
		double fRec37[4];
		double fRec43_tmp[8];
		double* fRec43 = &fRec43_tmp[4];
		double fSlow72 = std::exp(-(fConst40 / fSlow6));
		double fSlow73 = mydsp_faustpower2_f(fSlow72);
		double fSlow74 = 1.0 - fSlow73 * fSlow5;
		double fSlow75 = 1.0 - fSlow73;
		double fSlow76 = fSlow74 / fSlow75;
		double fSlow77 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow74) / mydsp_faustpower2_f(fSlow75) + -1.0));
		double fSlow78 = fSlow76 - fSlow77;
		double fSlow79 = fSlow72 * (fSlow77 + (1.0 - fSlow76));
		double fSlow80 = std::exp(-(fConst40 / fSlow15)) / fSlow72 + -1.0;
		double fRec42_tmp[8];
		double* fRec42 = &fRec42_tmp[4];
		double fRec40_tmp[8];
		double* fRec40 = &fRec40_tmp[4];
		double fRec41[4];
		double fZec4[4];
		double fZec5[4];
		double fRec4_tmp[8];
		double* fRec4 = &fRec4_tmp[4];
		double fRec5_tmp[8];
		double* fRec5 = &fRec5_tmp[4];
		double fZec6[4];
		double fRec6_tmp[8];
		double* fRec6 = &fRec6_tmp[4];
		double fRec7_tmp[8];
		double* fRec7 = &fRec7_tmp[4];
		double fZec7[4];
		double fZec8[4];
		double fRec8_tmp[8];
		double* fRec8 = &fRec8_tmp[4];
		double fRec9_tmp[8];
		double* fRec9 = &fRec9_tmp[4];
		double fZec9[4];
		double fZec10[4];
		double fRec10_tmp[8];
		double* fRec10 = &fRec10_tmp[4];
		double fRec11_tmp[8];
		double* fRec11 = &fRec11_tmp[4];
		double fZec11[4];
		double fSlow81 = static_cast<double>(fVslider7);
		double fSlow82 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider8));
		double fSlow83 = fConst2 * (fSlow81 / std::sqrt(std::max<double>(0.0, fSlow82)));
		double fSlow84 = (1.0 - fSlow83) / (fSlow83 + 1.0);
		double fSlow85 = std::cos(fConst2 * fSlow81) * (fSlow84 + 1.0);
		double fZec12[4];
		double fZec13[4];
		double fRec3_tmp[8];
		double* fRec3 = &fRec3_tmp[4];
		double fZec14[4];
		double fZec15[4];
		double fSlow86 = static_cast<double>(fVslider9);
		double fSlow87 = std::pow(1e+01, 0.05 * static_cast<double>(fVslider10));
		double fSlow88 = fConst2 * (fSlow86 / std::sqrt(std::max<double>(0.0, fSlow87)));
		double fSlow89 = (1.0 - fSlow88) / (fSlow88 + 1.0);
		double fSlow90 = std::cos(fConst2 * fSlow86) * (fSlow89 + 1.0);
		double fZec16[4];
		double fZec17[4];
		double fRec2_tmp[8];
		double* fRec2 = &fRec2_tmp[4];
		double fZec18[4];
		double fZec19[4];
		double fZec20[4];
		double fZec21[4];
		double fZec22[4];
		double fZec23[4];
		double fRec45_tmp[8];
		double* fRec45 = &fRec45_tmp[4];
		double fZec24[4];
		double fZec25[4];
		double fZec26[4];
		double fZec27[4];
		double fRec44_tmp[8];
		double* fRec44 = &fRec44_tmp[4];
		double fZec28[4];
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
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				fRec0_tmp[j0] = fRec0_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec0[i] = fSlow0 + 0.999 * fRec0[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				fRec0_perm[j1] = fRec0_tmp[faust_wrap_add(vsize, j1)];
			}
			/* Recursive loop 1 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fRec1_tmp[j2] = fRec1_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec1[i] = fSlow1 + 0.999 * fRec1[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fRec1_perm[j3] = fRec1_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Vectorizable loop 2 */
			/* Pre code */
			fYec1_idx = (faust_wrap_add(fYec1_idx, fYec1_idx_save)) & 16383;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec1[(faust_wrap_add(i, fYec1_idx)) & 16383] = static_cast<double>(input1[i]);
			}
			/* Post code */
			fYec1_idx_save = vsize;
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec1[i] = 0.3 * fYec1[(faust_wrap_sub(faust_wrap_add(i, fYec1_idx), iSlow17)) & 16383];
			}
			/* Vectorizable loop 4 */
			/* Pre code */
			fYec10_idx = (faust_wrap_add(fYec10_idx, fYec10_idx_save)) & 16383;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec10[(faust_wrap_add(i, fYec10_idx)) & 16383] = static_cast<double>(input0[i]);
			}
			/* Post code */
			fYec10_idx_save = vsize;
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec3[i] = 0.3 * fYec10[(faust_wrap_sub(faust_wrap_add(i, fYec10_idx), iSlow17)) & 16383];
			}
			/* Recursive loop 6 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				fRec15_tmp[j4] = fRec15_perm[j4];
			}
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec14_tmp[j6] = fRec14_perm[j6];
			}
			fYec0_idx = (faust_wrap_add(fYec0_idx, fYec0_idx_save)) & 32767;
			fYec2_idx = (faust_wrap_add(fYec2_idx, fYec2_idx_save)) & 2047;
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fRec12_tmp[j8] = fRec12_perm[j8];
			}
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				fRec19_tmp[j10] = fRec19_perm[j10];
			}
			for (int j12 = 0; j12 < 4; j12 = faust_wrap_add(j12, 1)) {
				fRec18_tmp[j12] = fRec18_perm[j12];
			}
			fYec3_idx = (faust_wrap_add(fYec3_idx, fYec3_idx_save)) & 32767;
			fYec4_idx = (faust_wrap_add(fYec4_idx, fYec4_idx_save)) & 4095;
			for (int j14 = 0; j14 < 4; j14 = faust_wrap_add(j14, 1)) {
				fRec16_tmp[j14] = fRec16_perm[j14];
			}
			for (int j16 = 0; j16 < 4; j16 = faust_wrap_add(j16, 1)) {
				fRec23_tmp[j16] = fRec23_perm[j16];
			}
			for (int j18 = 0; j18 < 4; j18 = faust_wrap_add(j18, 1)) {
				fRec22_tmp[j18] = fRec22_perm[j18];
			}
			fYec5_idx = (faust_wrap_add(fYec5_idx, fYec5_idx_save)) & 16383;
			fYec6_idx = (faust_wrap_add(fYec6_idx, fYec6_idx_save)) & 4095;
			for (int j20 = 0; j20 < 4; j20 = faust_wrap_add(j20, 1)) {
				fRec20_tmp[j20] = fRec20_perm[j20];
			}
			for (int j22 = 0; j22 < 4; j22 = faust_wrap_add(j22, 1)) {
				fRec27_tmp[j22] = fRec27_perm[j22];
			}
			for (int j24 = 0; j24 < 4; j24 = faust_wrap_add(j24, 1)) {
				fRec26_tmp[j24] = fRec26_perm[j24];
			}
			fYec7_idx = (faust_wrap_add(fYec7_idx, fYec7_idx_save)) & 32767;
			fYec8_idx = (faust_wrap_add(fYec8_idx, fYec8_idx_save)) & 4095;
			for (int j26 = 0; j26 < 4; j26 = faust_wrap_add(j26, 1)) {
				fRec24_tmp[j26] = fRec24_perm[j26];
			}
			for (int j28 = 0; j28 < 4; j28 = faust_wrap_add(j28, 1)) {
				fRec31_tmp[j28] = fRec31_perm[j28];
			}
			for (int j30 = 0; j30 < 4; j30 = faust_wrap_add(j30, 1)) {
				fRec30_tmp[j30] = fRec30_perm[j30];
			}
			fYec9_idx = (faust_wrap_add(fYec9_idx, fYec9_idx_save)) & 16383;
			fYec11_idx = (faust_wrap_add(fYec11_idx, fYec11_idx_save)) & 2047;
			for (int j32 = 0; j32 < 4; j32 = faust_wrap_add(j32, 1)) {
				fRec28_tmp[j32] = fRec28_perm[j32];
			}
			for (int j34 = 0; j34 < 4; j34 = faust_wrap_add(j34, 1)) {
				fRec35_tmp[j34] = fRec35_perm[j34];
			}
			for (int j36 = 0; j36 < 4; j36 = faust_wrap_add(j36, 1)) {
				fRec34_tmp[j36] = fRec34_perm[j36];
			}
			fYec12_idx = (faust_wrap_add(fYec12_idx, fYec12_idx_save)) & 16383;
			fYec13_idx = (faust_wrap_add(fYec13_idx, fYec13_idx_save)) & 4095;
			for (int j38 = 0; j38 < 4; j38 = faust_wrap_add(j38, 1)) {
				fRec32_tmp[j38] = fRec32_perm[j38];
			}
			for (int j40 = 0; j40 < 4; j40 = faust_wrap_add(j40, 1)) {
				fRec39_tmp[j40] = fRec39_perm[j40];
			}
			for (int j42 = 0; j42 < 4; j42 = faust_wrap_add(j42, 1)) {
				fRec38_tmp[j42] = fRec38_perm[j42];
			}
			fYec14_idx = (faust_wrap_add(fYec14_idx, fYec14_idx_save)) & 16383;
			fYec15_idx = (faust_wrap_add(fYec15_idx, fYec15_idx_save)) & 4095;
			for (int j44 = 0; j44 < 4; j44 = faust_wrap_add(j44, 1)) {
				fRec36_tmp[j44] = fRec36_perm[j44];
			}
			for (int j46 = 0; j46 < 4; j46 = faust_wrap_add(j46, 1)) {
				fRec43_tmp[j46] = fRec43_perm[j46];
			}
			for (int j48 = 0; j48 < 4; j48 = faust_wrap_add(j48, 1)) {
				fRec42_tmp[j48] = fRec42_perm[j48];
			}
			fYec16_idx = (faust_wrap_add(fYec16_idx, fYec16_idx_save)) & 16383;
			fYec17_idx = (faust_wrap_add(fYec17_idx, fYec17_idx_save)) & 2047;
			for (int j50 = 0; j50 < 4; j50 = faust_wrap_add(j50, 1)) {
				fRec40_tmp[j50] = fRec40_perm[j50];
			}
			for (int j52 = 0; j52 < 4; j52 = faust_wrap_add(j52, 1)) {
				fRec4_tmp[j52] = fRec4_perm[j52];
			}
			for (int j54 = 0; j54 < 4; j54 = faust_wrap_add(j54, 1)) {
				fRec5_tmp[j54] = fRec5_perm[j54];
			}
			for (int j56 = 0; j56 < 4; j56 = faust_wrap_add(j56, 1)) {
				fRec6_tmp[j56] = fRec6_perm[j56];
			}
			for (int j58 = 0; j58 < 4; j58 = faust_wrap_add(j58, 1)) {
				fRec7_tmp[j58] = fRec7_perm[j58];
			}
			for (int j60 = 0; j60 < 4; j60 = faust_wrap_add(j60, 1)) {
				fRec8_tmp[j60] = fRec8_perm[j60];
			}
			for (int j62 = 0; j62 < 4; j62 = faust_wrap_add(j62, 1)) {
				fRec9_tmp[j62] = fRec9_perm[j62];
			}
			for (int j64 = 0; j64 < 4; j64 = faust_wrap_add(j64, 1)) {
				fRec10_tmp[j64] = fRec10_perm[j64];
			}
			for (int j66 = 0; j66 < 4; j66 = faust_wrap_add(j66, 1)) {
				fRec11_tmp[j66] = fRec11_perm[j66];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec15[i] = -(fSlow3 * (fSlow4 * fRec15[faust_wrap_sub(i, 1)] - (fRec11[faust_wrap_sub(i, 1)] + fRec11[faust_wrap_sub(i, 2)])));
				fRec14[i] = fSlow13 * fRec14[faust_wrap_sub(i, 1)] + fSlow14 * (fRec11[faust_wrap_sub(i, 1)] + fSlow16 * fRec15[i]);
				fYec0[(faust_wrap_add(i, fYec0_idx)) & 32767] = 0.35355339059327373 * fRec14[i] + 1e-20;
				fZec0[i] = 0.6 * fRec12[faust_wrap_sub(i, 1)] + fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), iConst6)) & 32767];
				fYec2[(faust_wrap_add(i, fYec2_idx)) & 2047] = fZec0[i] - fZec1[i];
				fRec12[i] = fYec2[(faust_wrap_sub(faust_wrap_add(i, fYec2_idx), iConst8)) & 2047];
				fRec13[i] = 0.6 * (fZec1[i] - fZec0[i]);
				fRec19[i] = -(fSlow3 * (fSlow4 * fRec19[faust_wrap_sub(i, 1)] - (fRec7[faust_wrap_sub(i, 1)] + fRec7[faust_wrap_sub(i, 2)])));
				fRec18[i] = fSlow24 * fRec18[faust_wrap_sub(i, 1)] + fSlow25 * (fRec7[faust_wrap_sub(i, 1)] + fSlow26 * fRec19[i]);
				fYec3[(faust_wrap_add(i, fYec3_idx)) & 32767] = 0.35355339059327373 * fRec18[i] + 1e-20;
				fZec2[i] = 0.6 * fRec16[faust_wrap_sub(i, 1)] + fYec3[(faust_wrap_sub(faust_wrap_add(i, fYec3_idx), iConst12)) & 32767];
				fYec4[(faust_wrap_add(i, fYec4_idx)) & 4095] = fZec2[i] - fZec1[i];
				fRec16[i] = fYec4[(faust_wrap_sub(faust_wrap_add(i, fYec4_idx), iConst13)) & 4095];
				fRec17[i] = 0.6 * (fZec1[i] - fZec2[i]);
				fRec23[i] = -(fSlow3 * (fSlow4 * fRec23[faust_wrap_sub(i, 1)] - (fRec9[faust_wrap_sub(i, 1)] + fRec9[faust_wrap_sub(i, 2)])));
				fRec22[i] = fSlow33 * fRec22[faust_wrap_sub(i, 1)] + fSlow34 * (fRec9[faust_wrap_sub(i, 1)] + fSlow35 * fRec23[i]);
				fYec5[(faust_wrap_add(i, fYec5_idx)) & 16383] = 0.35355339059327373 * fRec22[i] + 1e-20;
				fYec6[(faust_wrap_add(i, fYec6_idx)) & 4095] = fYec5[(faust_wrap_sub(faust_wrap_add(i, fYec5_idx), iConst17)) & 16383] + fZec1[i] + 0.6 * fRec20[faust_wrap_sub(i, 1)];
				fRec20[i] = fYec6[(faust_wrap_sub(faust_wrap_add(i, fYec6_idx), iConst18)) & 4095];
				fRec21[i] = -(0.6 * fYec6[(faust_wrap_add(i, fYec6_idx)) & 4095]);
				fRec27[i] = -(fSlow3 * (fSlow4 * fRec27[faust_wrap_sub(i, 1)] - (fRec5[faust_wrap_sub(i, 1)] + fRec5[faust_wrap_sub(i, 2)])));
				fRec26[i] = fSlow42 * fRec26[faust_wrap_sub(i, 1)] + fSlow43 * (fRec5[faust_wrap_sub(i, 1)] + fSlow44 * fRec27[i]);
				fYec7[(faust_wrap_add(i, fYec7_idx)) & 32767] = 0.35355339059327373 * fRec26[i] + 1e-20;
				fYec8[(faust_wrap_add(i, fYec8_idx)) & 4095] = fZec1[i] + 0.6 * fRec24[faust_wrap_sub(i, 1)] + fYec7[(faust_wrap_sub(faust_wrap_add(i, fYec7_idx), iConst22)) & 32767];
				fRec24[i] = fYec8[(faust_wrap_sub(faust_wrap_add(i, fYec8_idx), iConst23)) & 4095];
				fRec25[i] = -(0.6 * fYec8[(faust_wrap_add(i, fYec8_idx)) & 4095]);
				fRec31[i] = -(fSlow3 * (fSlow4 * fRec31[faust_wrap_sub(i, 1)] - (fRec10[faust_wrap_sub(i, 1)] + fRec10[faust_wrap_sub(i, 2)])));
				fRec30[i] = fSlow51 * fRec30[faust_wrap_sub(i, 1)] + fSlow52 * (fRec10[faust_wrap_sub(i, 1)] + fSlow53 * fRec31[i]);
				fYec9[(faust_wrap_add(i, fYec9_idx)) & 16383] = 0.35355339059327373 * fRec30[i] + 1e-20;
				fYec11[(faust_wrap_add(i, fYec11_idx)) & 2047] = fYec9[(faust_wrap_sub(faust_wrap_add(i, fYec9_idx), iConst27)) & 16383] - (fZec3[i] + 0.6 * fRec28[faust_wrap_sub(i, 1)]);
				fRec28[i] = fYec11[(faust_wrap_sub(faust_wrap_add(i, fYec11_idx), iConst28)) & 2047];
				fRec29[i] = 0.6 * fYec11[(faust_wrap_add(i, fYec11_idx)) & 2047];
				fRec35[i] = -(fSlow3 * (fSlow4 * fRec35[faust_wrap_sub(i, 1)] - (fRec6[faust_wrap_sub(i, 1)] + fRec6[faust_wrap_sub(i, 2)])));
				fRec34[i] = fSlow60 * fRec34[faust_wrap_sub(i, 1)] + fSlow61 * (fRec6[faust_wrap_sub(i, 1)] + fSlow62 * fRec35[i]);
				fYec12[(faust_wrap_add(i, fYec12_idx)) & 16383] = 0.35355339059327373 * fRec34[i] + 1e-20;
				fYec13[(faust_wrap_add(i, fYec13_idx)) & 4095] = fYec12[(faust_wrap_sub(faust_wrap_add(i, fYec12_idx), iConst32)) & 16383] - (fZec3[i] + 0.6 * fRec32[faust_wrap_sub(i, 1)]);
				fRec32[i] = fYec13[(faust_wrap_sub(faust_wrap_add(i, fYec13_idx), iConst33)) & 4095];
				fRec33[i] = 0.6 * fYec13[(faust_wrap_add(i, fYec13_idx)) & 4095];
				fRec39[i] = -(fSlow3 * (fSlow4 * fRec39[faust_wrap_sub(i, 1)] - (fRec8[faust_wrap_sub(i, 1)] + fRec8[faust_wrap_sub(i, 2)])));
				fRec38[i] = fSlow69 * fRec38[faust_wrap_sub(i, 1)] + fSlow70 * (fRec8[faust_wrap_sub(i, 1)] + fSlow71 * fRec39[i]);
				fYec14[(faust_wrap_add(i, fYec14_idx)) & 16383] = 0.35355339059327373 * fRec38[i] + 1e-20;
				fYec15[(faust_wrap_add(i, fYec15_idx)) & 4095] = fZec3[i] + fYec14[(faust_wrap_sub(faust_wrap_add(i, fYec14_idx), iConst37)) & 16383] - 0.6 * fRec36[faust_wrap_sub(i, 1)];
				fRec36[i] = fYec15[(faust_wrap_sub(faust_wrap_add(i, fYec15_idx), iConst38)) & 4095];
				fRec37[i] = 0.6 * fYec15[(faust_wrap_add(i, fYec15_idx)) & 4095];
				fRec43[i] = -(fSlow3 * (fSlow4 * fRec43[faust_wrap_sub(i, 1)] - (fRec4[faust_wrap_sub(i, 1)] + fRec4[faust_wrap_sub(i, 2)])));
				fRec42[i] = fSlow78 * fRec42[faust_wrap_sub(i, 1)] + fSlow79 * (fRec4[faust_wrap_sub(i, 1)] + fSlow80 * fRec43[i]);
				fYec16[(faust_wrap_add(i, fYec16_idx)) & 16383] = 0.35355339059327373 * fRec42[i] + 1e-20;
				fYec17[(faust_wrap_add(i, fYec17_idx)) & 2047] = fYec16[(faust_wrap_sub(faust_wrap_add(i, fYec16_idx), iConst42)) & 16383] + fZec3[i] - 0.6 * fRec40[faust_wrap_sub(i, 1)];
				fRec40[i] = fYec17[(faust_wrap_sub(faust_wrap_add(i, fYec17_idx), iConst43)) & 2047];
				fRec41[i] = 0.6 * fYec17[(faust_wrap_add(i, fYec17_idx)) & 2047];
				fZec4[i] = fRec41[i] + fRec37[i];
				fZec5[i] = fRec29[i] + fRec33[i] + fZec4[i];
				fRec4[i] = fRec12[faust_wrap_sub(i, 1)] + fRec16[faust_wrap_sub(i, 1)] + fRec20[faust_wrap_sub(i, 1)] + fRec24[faust_wrap_sub(i, 1)] + fRec28[faust_wrap_sub(i, 1)] + fRec32[faust_wrap_sub(i, 1)] + fRec36[faust_wrap_sub(i, 1)] + fRec40[faust_wrap_sub(i, 1)] + fRec13[i] + fRec17[i] + fRec21[i] + fRec25[i] + fZec5[i];
				fRec5[i] = fRec28[faust_wrap_sub(i, 1)] + fRec32[faust_wrap_sub(i, 1)] + fRec36[faust_wrap_sub(i, 1)] + fRec40[faust_wrap_sub(i, 1)] + fZec5[i] - (fRec12[faust_wrap_sub(i, 1)] + fRec16[faust_wrap_sub(i, 1)] + fRec20[faust_wrap_sub(i, 1)] + fRec24[faust_wrap_sub(i, 1)] + fRec13[i] + fRec17[i] + fRec25[i] + fRec21[i]);
				fZec6[i] = fRec33[i] + fRec29[i];
				fRec6[i] = fRec20[faust_wrap_sub(i, 1)] + fRec24[faust_wrap_sub(i, 1)] + fRec36[faust_wrap_sub(i, 1)] + fRec40[faust_wrap_sub(i, 1)] + fRec21[i] + fRec25[i] + fZec4[i] - (fRec12[faust_wrap_sub(i, 1)] + fRec16[faust_wrap_sub(i, 1)] + fRec28[faust_wrap_sub(i, 1)] + fRec32[faust_wrap_sub(i, 1)] + fRec13[i] + fRec17[i] + fZec6[i]);
				fRec7[i] = fRec12[faust_wrap_sub(i, 1)] + fRec16[faust_wrap_sub(i, 1)] + fRec36[faust_wrap_sub(i, 1)] + fRec40[faust_wrap_sub(i, 1)] + fRec13[i] + fRec17[i] + fZec4[i] - (fRec20[faust_wrap_sub(i, 1)] + fRec24[faust_wrap_sub(i, 1)] + fRec28[faust_wrap_sub(i, 1)] + fRec32[faust_wrap_sub(i, 1)] + fRec21[i] + fRec25[i] + fZec6[i]);
				fZec7[i] = fRec41[i] + fRec33[i];
				fZec8[i] = fRec37[i] + fRec29[i];
				fRec8[i] = fRec16[faust_wrap_sub(i, 1)] + fRec24[faust_wrap_sub(i, 1)] + fRec32[faust_wrap_sub(i, 1)] + fRec40[faust_wrap_sub(i, 1)] + fRec17[i] + fRec25[i] + fZec7[i] - (fRec12[faust_wrap_sub(i, 1)] + fRec20[faust_wrap_sub(i, 1)] + fRec28[faust_wrap_sub(i, 1)] + fRec36[faust_wrap_sub(i, 1)] + fRec13[i] + fRec21[i] + fZec8[i]);
				fRec9[i] = fRec12[faust_wrap_sub(i, 1)] + fRec20[faust_wrap_sub(i, 1)] + fRec32[faust_wrap_sub(i, 1)] + fRec40[faust_wrap_sub(i, 1)] + fRec13[i] + fRec21[i] + fZec7[i] - (fRec16[faust_wrap_sub(i, 1)] + fRec24[faust_wrap_sub(i, 1)] + fRec28[faust_wrap_sub(i, 1)] + fRec36[faust_wrap_sub(i, 1)] + fRec17[i] + fRec25[i] + fZec8[i]);
				fZec9[i] = fRec41[i] + fRec29[i];
				fZec10[i] = fRec37[i] + fRec33[i];
				fRec10[i] = fRec12[faust_wrap_sub(i, 1)] + fRec24[faust_wrap_sub(i, 1)] + fRec28[faust_wrap_sub(i, 1)] + fRec40[faust_wrap_sub(i, 1)] + fRec13[i] + fRec25[i] + fZec9[i] - (fRec16[faust_wrap_sub(i, 1)] + fRec20[faust_wrap_sub(i, 1)] + fRec32[faust_wrap_sub(i, 1)] + fRec36[faust_wrap_sub(i, 1)] + fRec17[i] + fRec21[i] + fZec10[i]);
				fRec11[i] = fRec16[faust_wrap_sub(i, 1)] + fRec20[faust_wrap_sub(i, 1)] + fRec28[faust_wrap_sub(i, 1)] + fRec40[faust_wrap_sub(i, 1)] + fRec17[i] + fRec21[i] + fZec9[i] - (fRec12[faust_wrap_sub(i, 1)] + fRec24[faust_wrap_sub(i, 1)] + fRec32[faust_wrap_sub(i, 1)] + fRec36[faust_wrap_sub(i, 1)] + fRec13[i] + fRec25[i] + fZec10[i]);
			}
			/* Post code */
			fYec16_idx_save = vsize;
			fYec17_idx_save = vsize;
			for (int j47 = 0; j47 < 4; j47 = faust_wrap_add(j47, 1)) {
				fRec43_perm[j47] = fRec43_tmp[faust_wrap_add(vsize, j47)];
			}
			for (int j49 = 0; j49 < 4; j49 = faust_wrap_add(j49, 1)) {
				fRec42_perm[j49] = fRec42_tmp[faust_wrap_add(vsize, j49)];
			}
			for (int j51 = 0; j51 < 4; j51 = faust_wrap_add(j51, 1)) {
				fRec40_perm[j51] = fRec40_tmp[faust_wrap_add(vsize, j51)];
			}
			fYec14_idx_save = vsize;
			fYec15_idx_save = vsize;
			for (int j41 = 0; j41 < 4; j41 = faust_wrap_add(j41, 1)) {
				fRec39_perm[j41] = fRec39_tmp[faust_wrap_add(vsize, j41)];
			}
			for (int j43 = 0; j43 < 4; j43 = faust_wrap_add(j43, 1)) {
				fRec38_perm[j43] = fRec38_tmp[faust_wrap_add(vsize, j43)];
			}
			for (int j45 = 0; j45 < 4; j45 = faust_wrap_add(j45, 1)) {
				fRec36_perm[j45] = fRec36_tmp[faust_wrap_add(vsize, j45)];
			}
			fYec12_idx_save = vsize;
			fYec13_idx_save = vsize;
			for (int j35 = 0; j35 < 4; j35 = faust_wrap_add(j35, 1)) {
				fRec35_perm[j35] = fRec35_tmp[faust_wrap_add(vsize, j35)];
			}
			for (int j37 = 0; j37 < 4; j37 = faust_wrap_add(j37, 1)) {
				fRec34_perm[j37] = fRec34_tmp[faust_wrap_add(vsize, j37)];
			}
			for (int j39 = 0; j39 < 4; j39 = faust_wrap_add(j39, 1)) {
				fRec32_perm[j39] = fRec32_tmp[faust_wrap_add(vsize, j39)];
			}
			fYec9_idx_save = vsize;
			fYec11_idx_save = vsize;
			for (int j29 = 0; j29 < 4; j29 = faust_wrap_add(j29, 1)) {
				fRec31_perm[j29] = fRec31_tmp[faust_wrap_add(vsize, j29)];
			}
			for (int j31 = 0; j31 < 4; j31 = faust_wrap_add(j31, 1)) {
				fRec30_perm[j31] = fRec30_tmp[faust_wrap_add(vsize, j31)];
			}
			for (int j33 = 0; j33 < 4; j33 = faust_wrap_add(j33, 1)) {
				fRec28_perm[j33] = fRec28_tmp[faust_wrap_add(vsize, j33)];
			}
			fYec7_idx_save = vsize;
			fYec8_idx_save = vsize;
			for (int j23 = 0; j23 < 4; j23 = faust_wrap_add(j23, 1)) {
				fRec27_perm[j23] = fRec27_tmp[faust_wrap_add(vsize, j23)];
			}
			for (int j25 = 0; j25 < 4; j25 = faust_wrap_add(j25, 1)) {
				fRec26_perm[j25] = fRec26_tmp[faust_wrap_add(vsize, j25)];
			}
			for (int j27 = 0; j27 < 4; j27 = faust_wrap_add(j27, 1)) {
				fRec24_perm[j27] = fRec24_tmp[faust_wrap_add(vsize, j27)];
			}
			fYec5_idx_save = vsize;
			fYec6_idx_save = vsize;
			for (int j17 = 0; j17 < 4; j17 = faust_wrap_add(j17, 1)) {
				fRec23_perm[j17] = fRec23_tmp[faust_wrap_add(vsize, j17)];
			}
			for (int j19 = 0; j19 < 4; j19 = faust_wrap_add(j19, 1)) {
				fRec22_perm[j19] = fRec22_tmp[faust_wrap_add(vsize, j19)];
			}
			for (int j21 = 0; j21 < 4; j21 = faust_wrap_add(j21, 1)) {
				fRec20_perm[j21] = fRec20_tmp[faust_wrap_add(vsize, j21)];
			}
			fYec3_idx_save = vsize;
			fYec4_idx_save = vsize;
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				fRec19_perm[j11] = fRec19_tmp[faust_wrap_add(vsize, j11)];
			}
			for (int j13 = 0; j13 < 4; j13 = faust_wrap_add(j13, 1)) {
				fRec18_perm[j13] = fRec18_tmp[faust_wrap_add(vsize, j13)];
			}
			for (int j15 = 0; j15 < 4; j15 = faust_wrap_add(j15, 1)) {
				fRec16_perm[j15] = fRec16_tmp[faust_wrap_add(vsize, j15)];
			}
			fYec0_idx_save = vsize;
			fYec2_idx_save = vsize;
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fRec15_perm[j5] = fRec15_tmp[faust_wrap_add(vsize, j5)];
			}
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec14_perm[j7] = fRec14_tmp[faust_wrap_add(vsize, j7)];
			}
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fRec12_perm[j9] = fRec12_tmp[faust_wrap_add(vsize, j9)];
			}
			for (int j53 = 0; j53 < 4; j53 = faust_wrap_add(j53, 1)) {
				fRec4_perm[j53] = fRec4_tmp[faust_wrap_add(vsize, j53)];
			}
			for (int j55 = 0; j55 < 4; j55 = faust_wrap_add(j55, 1)) {
				fRec5_perm[j55] = fRec5_tmp[faust_wrap_add(vsize, j55)];
			}
			for (int j57 = 0; j57 < 4; j57 = faust_wrap_add(j57, 1)) {
				fRec6_perm[j57] = fRec6_tmp[faust_wrap_add(vsize, j57)];
			}
			for (int j59 = 0; j59 < 4; j59 = faust_wrap_add(j59, 1)) {
				fRec7_perm[j59] = fRec7_tmp[faust_wrap_add(vsize, j59)];
			}
			for (int j61 = 0; j61 < 4; j61 = faust_wrap_add(j61, 1)) {
				fRec8_perm[j61] = fRec8_tmp[faust_wrap_add(vsize, j61)];
			}
			for (int j63 = 0; j63 < 4; j63 = faust_wrap_add(j63, 1)) {
				fRec9_perm[j63] = fRec9_tmp[faust_wrap_add(vsize, j63)];
			}
			for (int j65 = 0; j65 < 4; j65 = faust_wrap_add(j65, 1)) {
				fRec10_perm[j65] = fRec10_tmp[faust_wrap_add(vsize, j65)];
			}
			for (int j67 = 0; j67 < 4; j67 = faust_wrap_add(j67, 1)) {
				fRec11_perm[j67] = fRec11_tmp[faust_wrap_add(vsize, j67)];
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec11[i] = 0.37 * (fRec5[i] + fRec6[i]);
			}
			/* Recursive loop 8 */
			/* Pre code */
			for (int j68 = 0; j68 < 4; j68 = faust_wrap_add(j68, 1)) {
				fRec3_tmp[j68] = fRec3_perm[j68];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec12[i] = fSlow85 * fRec3[faust_wrap_sub(i, 1)];
				fZec13[i] = fZec11[i] + fZec12[i];
				fRec3[i] = fZec13[i] - fSlow84 * fRec3[faust_wrap_sub(i, 2)];
			}
			/* Post code */
			for (int j69 = 0; j69 < 4; j69 = faust_wrap_add(j69, 1)) {
				fRec3_perm[j69] = fRec3_tmp[faust_wrap_add(vsize, j69)];
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec14[i] = fSlow84 * fRec3[i];
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec15[i] = 0.5 * (fZec14[i] + fZec11[i] + fRec3[faust_wrap_sub(i, 2)] - fZec12[i] + fSlow82 * (fRec3[faust_wrap_sub(i, 2)] + fZec14[i] - fZec13[i]));
			}
			/* Recursive loop 11 */
			/* Pre code */
			for (int j70 = 0; j70 < 4; j70 = faust_wrap_add(j70, 1)) {
				fRec2_tmp[j70] = fRec2_perm[j70];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec16[i] = fSlow90 * fRec2[faust_wrap_sub(i, 1)];
				fZec17[i] = fZec15[i] + fZec16[i];
				fRec2[i] = fZec17[i] - fSlow89 * fRec2[faust_wrap_sub(i, 2)];
			}
			/* Post code */
			for (int j71 = 0; j71 < 4; j71 = faust_wrap_add(j71, 1)) {
				fRec2_perm[j71] = fRec2_tmp[faust_wrap_add(vsize, j71)];
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec18[i] = fRec1[i] + 1.0;
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec19[i] = fSlow89 * fRec2[i];
			}
			/* Vectorizable loop 14 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec20[i] = 1.0 - 0.5 * fZec18[i];
			}
			/* Vectorizable loop 15 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fRec0[i] * (0.25 * fZec18[i] * (fZec19[i] + fZec15[i] + fRec2[faust_wrap_sub(i, 2)] - fZec16[i] + fSlow87 * (fRec2[faust_wrap_sub(i, 2)] + fZec19[i] - fZec17[i])) + static_cast<double>(input0[i]) * fZec20[i]));
			}
			/* Vectorizable loop 16 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec21[i] = 0.37 * (fRec5[i] - fRec6[i]);
			}
			/* Recursive loop 17 */
			/* Pre code */
			for (int j72 = 0; j72 < 4; j72 = faust_wrap_add(j72, 1)) {
				fRec45_tmp[j72] = fRec45_perm[j72];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec22[i] = fSlow85 * fRec45[faust_wrap_sub(i, 1)];
				fZec23[i] = fZec21[i] + fZec22[i];
				fRec45[i] = fZec23[i] - fSlow84 * fRec45[faust_wrap_sub(i, 2)];
			}
			/* Post code */
			for (int j73 = 0; j73 < 4; j73 = faust_wrap_add(j73, 1)) {
				fRec45_perm[j73] = fRec45_tmp[faust_wrap_add(vsize, j73)];
			}
			/* Vectorizable loop 18 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec24[i] = fSlow84 * fRec45[i];
			}
			/* Vectorizable loop 19 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec25[i] = 0.5 * (fZec24[i] + fZec21[i] + fRec45[faust_wrap_sub(i, 2)] - fZec22[i] + fSlow82 * (fRec45[faust_wrap_sub(i, 2)] + fZec24[i] - fZec23[i]));
			}
			/* Recursive loop 20 */
			/* Pre code */
			for (int j74 = 0; j74 < 4; j74 = faust_wrap_add(j74, 1)) {
				fRec44_tmp[j74] = fRec44_perm[j74];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec26[i] = fSlow90 * fRec44[faust_wrap_sub(i, 1)];
				fZec27[i] = fZec25[i] + fZec26[i];
				fRec44[i] = fZec27[i] - fSlow89 * fRec44[faust_wrap_sub(i, 2)];
			}
			/* Post code */
			for (int j75 = 0; j75 < 4; j75 = faust_wrap_add(j75, 1)) {
				fRec44_perm[j75] = fRec44_tmp[faust_wrap_add(vsize, j75)];
			}
			/* Vectorizable loop 21 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec28[i] = fSlow89 * fRec44[i];
			}
			/* Vectorizable loop 22 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fRec0[i] * (0.25 * fZec18[i] * (fZec28[i] + fZec25[i] + fRec44[faust_wrap_sub(i, 2)] - fZec26[i] + fSlow87 * (fRec44[faust_wrap_sub(i, 2)] + fZec28[i] - fZec27[i])) + static_cast<double>(input1[i]) * fZec20[i]));
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
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				fRec0_tmp[j0] = fRec0_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec0[i] = fSlow0 + 0.999 * fRec0[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				fRec0_perm[j1] = fRec0_tmp[faust_wrap_add(vsize, j1)];
			}
			/* Recursive loop 1 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fRec1_tmp[j2] = fRec1_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec1[i] = fSlow1 + 0.999 * fRec1[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fRec1_perm[j3] = fRec1_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Vectorizable loop 2 */
			/* Pre code */
			fYec1_idx = (faust_wrap_add(fYec1_idx, fYec1_idx_save)) & 16383;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec1[(faust_wrap_add(i, fYec1_idx)) & 16383] = static_cast<double>(input1[i]);
			}
			/* Post code */
			fYec1_idx_save = vsize;
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec1[i] = 0.3 * fYec1[(faust_wrap_sub(faust_wrap_add(i, fYec1_idx), iSlow17)) & 16383];
			}
			/* Vectorizable loop 4 */
			/* Pre code */
			fYec10_idx = (faust_wrap_add(fYec10_idx, fYec10_idx_save)) & 16383;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec10[(faust_wrap_add(i, fYec10_idx)) & 16383] = static_cast<double>(input0[i]);
			}
			/* Post code */
			fYec10_idx_save = vsize;
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec3[i] = 0.3 * fYec10[(faust_wrap_sub(faust_wrap_add(i, fYec10_idx), iSlow17)) & 16383];
			}
			/* Recursive loop 6 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				fRec15_tmp[j4] = fRec15_perm[j4];
			}
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec14_tmp[j6] = fRec14_perm[j6];
			}
			fYec0_idx = (faust_wrap_add(fYec0_idx, fYec0_idx_save)) & 32767;
			fYec2_idx = (faust_wrap_add(fYec2_idx, fYec2_idx_save)) & 2047;
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fRec12_tmp[j8] = fRec12_perm[j8];
			}
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				fRec19_tmp[j10] = fRec19_perm[j10];
			}
			for (int j12 = 0; j12 < 4; j12 = faust_wrap_add(j12, 1)) {
				fRec18_tmp[j12] = fRec18_perm[j12];
			}
			fYec3_idx = (faust_wrap_add(fYec3_idx, fYec3_idx_save)) & 32767;
			fYec4_idx = (faust_wrap_add(fYec4_idx, fYec4_idx_save)) & 4095;
			for (int j14 = 0; j14 < 4; j14 = faust_wrap_add(j14, 1)) {
				fRec16_tmp[j14] = fRec16_perm[j14];
			}
			for (int j16 = 0; j16 < 4; j16 = faust_wrap_add(j16, 1)) {
				fRec23_tmp[j16] = fRec23_perm[j16];
			}
			for (int j18 = 0; j18 < 4; j18 = faust_wrap_add(j18, 1)) {
				fRec22_tmp[j18] = fRec22_perm[j18];
			}
			fYec5_idx = (faust_wrap_add(fYec5_idx, fYec5_idx_save)) & 16383;
			fYec6_idx = (faust_wrap_add(fYec6_idx, fYec6_idx_save)) & 4095;
			for (int j20 = 0; j20 < 4; j20 = faust_wrap_add(j20, 1)) {
				fRec20_tmp[j20] = fRec20_perm[j20];
			}
			for (int j22 = 0; j22 < 4; j22 = faust_wrap_add(j22, 1)) {
				fRec27_tmp[j22] = fRec27_perm[j22];
			}
			for (int j24 = 0; j24 < 4; j24 = faust_wrap_add(j24, 1)) {
				fRec26_tmp[j24] = fRec26_perm[j24];
			}
			fYec7_idx = (faust_wrap_add(fYec7_idx, fYec7_idx_save)) & 32767;
			fYec8_idx = (faust_wrap_add(fYec8_idx, fYec8_idx_save)) & 4095;
			for (int j26 = 0; j26 < 4; j26 = faust_wrap_add(j26, 1)) {
				fRec24_tmp[j26] = fRec24_perm[j26];
			}
			for (int j28 = 0; j28 < 4; j28 = faust_wrap_add(j28, 1)) {
				fRec31_tmp[j28] = fRec31_perm[j28];
			}
			for (int j30 = 0; j30 < 4; j30 = faust_wrap_add(j30, 1)) {
				fRec30_tmp[j30] = fRec30_perm[j30];
			}
			fYec9_idx = (faust_wrap_add(fYec9_idx, fYec9_idx_save)) & 16383;
			fYec11_idx = (faust_wrap_add(fYec11_idx, fYec11_idx_save)) & 2047;
			for (int j32 = 0; j32 < 4; j32 = faust_wrap_add(j32, 1)) {
				fRec28_tmp[j32] = fRec28_perm[j32];
			}
			for (int j34 = 0; j34 < 4; j34 = faust_wrap_add(j34, 1)) {
				fRec35_tmp[j34] = fRec35_perm[j34];
			}
			for (int j36 = 0; j36 < 4; j36 = faust_wrap_add(j36, 1)) {
				fRec34_tmp[j36] = fRec34_perm[j36];
			}
			fYec12_idx = (faust_wrap_add(fYec12_idx, fYec12_idx_save)) & 16383;
			fYec13_idx = (faust_wrap_add(fYec13_idx, fYec13_idx_save)) & 4095;
			for (int j38 = 0; j38 < 4; j38 = faust_wrap_add(j38, 1)) {
				fRec32_tmp[j38] = fRec32_perm[j38];
			}
			for (int j40 = 0; j40 < 4; j40 = faust_wrap_add(j40, 1)) {
				fRec39_tmp[j40] = fRec39_perm[j40];
			}
			for (int j42 = 0; j42 < 4; j42 = faust_wrap_add(j42, 1)) {
				fRec38_tmp[j42] = fRec38_perm[j42];
			}
			fYec14_idx = (faust_wrap_add(fYec14_idx, fYec14_idx_save)) & 16383;
			fYec15_idx = (faust_wrap_add(fYec15_idx, fYec15_idx_save)) & 4095;
			for (int j44 = 0; j44 < 4; j44 = faust_wrap_add(j44, 1)) {
				fRec36_tmp[j44] = fRec36_perm[j44];
			}
			for (int j46 = 0; j46 < 4; j46 = faust_wrap_add(j46, 1)) {
				fRec43_tmp[j46] = fRec43_perm[j46];
			}
			for (int j48 = 0; j48 < 4; j48 = faust_wrap_add(j48, 1)) {
				fRec42_tmp[j48] = fRec42_perm[j48];
			}
			fYec16_idx = (faust_wrap_add(fYec16_idx, fYec16_idx_save)) & 16383;
			fYec17_idx = (faust_wrap_add(fYec17_idx, fYec17_idx_save)) & 2047;
			for (int j50 = 0; j50 < 4; j50 = faust_wrap_add(j50, 1)) {
				fRec40_tmp[j50] = fRec40_perm[j50];
			}
			for (int j52 = 0; j52 < 4; j52 = faust_wrap_add(j52, 1)) {
				fRec4_tmp[j52] = fRec4_perm[j52];
			}
			for (int j54 = 0; j54 < 4; j54 = faust_wrap_add(j54, 1)) {
				fRec5_tmp[j54] = fRec5_perm[j54];
			}
			for (int j56 = 0; j56 < 4; j56 = faust_wrap_add(j56, 1)) {
				fRec6_tmp[j56] = fRec6_perm[j56];
			}
			for (int j58 = 0; j58 < 4; j58 = faust_wrap_add(j58, 1)) {
				fRec7_tmp[j58] = fRec7_perm[j58];
			}
			for (int j60 = 0; j60 < 4; j60 = faust_wrap_add(j60, 1)) {
				fRec8_tmp[j60] = fRec8_perm[j60];
			}
			for (int j62 = 0; j62 < 4; j62 = faust_wrap_add(j62, 1)) {
				fRec9_tmp[j62] = fRec9_perm[j62];
			}
			for (int j64 = 0; j64 < 4; j64 = faust_wrap_add(j64, 1)) {
				fRec10_tmp[j64] = fRec10_perm[j64];
			}
			for (int j66 = 0; j66 < 4; j66 = faust_wrap_add(j66, 1)) {
				fRec11_tmp[j66] = fRec11_perm[j66];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec15[i] = -(fSlow3 * (fSlow4 * fRec15[faust_wrap_sub(i, 1)] - (fRec11[faust_wrap_sub(i, 1)] + fRec11[faust_wrap_sub(i, 2)])));
				fRec14[i] = fSlow13 * fRec14[faust_wrap_sub(i, 1)] + fSlow14 * (fRec11[faust_wrap_sub(i, 1)] + fSlow16 * fRec15[i]);
				fYec0[(faust_wrap_add(i, fYec0_idx)) & 32767] = 0.35355339059327373 * fRec14[i] + 1e-20;
				fZec0[i] = 0.6 * fRec12[faust_wrap_sub(i, 1)] + fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), iConst6)) & 32767];
				fYec2[(faust_wrap_add(i, fYec2_idx)) & 2047] = fZec0[i] - fZec1[i];
				fRec12[i] = fYec2[(faust_wrap_sub(faust_wrap_add(i, fYec2_idx), iConst8)) & 2047];
				fRec13[i] = 0.6 * (fZec1[i] - fZec0[i]);
				fRec19[i] = -(fSlow3 * (fSlow4 * fRec19[faust_wrap_sub(i, 1)] - (fRec7[faust_wrap_sub(i, 1)] + fRec7[faust_wrap_sub(i, 2)])));
				fRec18[i] = fSlow24 * fRec18[faust_wrap_sub(i, 1)] + fSlow25 * (fRec7[faust_wrap_sub(i, 1)] + fSlow26 * fRec19[i]);
				fYec3[(faust_wrap_add(i, fYec3_idx)) & 32767] = 0.35355339059327373 * fRec18[i] + 1e-20;
				fZec2[i] = 0.6 * fRec16[faust_wrap_sub(i, 1)] + fYec3[(faust_wrap_sub(faust_wrap_add(i, fYec3_idx), iConst12)) & 32767];
				fYec4[(faust_wrap_add(i, fYec4_idx)) & 4095] = fZec2[i] - fZec1[i];
				fRec16[i] = fYec4[(faust_wrap_sub(faust_wrap_add(i, fYec4_idx), iConst13)) & 4095];
				fRec17[i] = 0.6 * (fZec1[i] - fZec2[i]);
				fRec23[i] = -(fSlow3 * (fSlow4 * fRec23[faust_wrap_sub(i, 1)] - (fRec9[faust_wrap_sub(i, 1)] + fRec9[faust_wrap_sub(i, 2)])));
				fRec22[i] = fSlow33 * fRec22[faust_wrap_sub(i, 1)] + fSlow34 * (fRec9[faust_wrap_sub(i, 1)] + fSlow35 * fRec23[i]);
				fYec5[(faust_wrap_add(i, fYec5_idx)) & 16383] = 0.35355339059327373 * fRec22[i] + 1e-20;
				fYec6[(faust_wrap_add(i, fYec6_idx)) & 4095] = fYec5[(faust_wrap_sub(faust_wrap_add(i, fYec5_idx), iConst17)) & 16383] + fZec1[i] + 0.6 * fRec20[faust_wrap_sub(i, 1)];
				fRec20[i] = fYec6[(faust_wrap_sub(faust_wrap_add(i, fYec6_idx), iConst18)) & 4095];
				fRec21[i] = -(0.6 * fYec6[(faust_wrap_add(i, fYec6_idx)) & 4095]);
				fRec27[i] = -(fSlow3 * (fSlow4 * fRec27[faust_wrap_sub(i, 1)] - (fRec5[faust_wrap_sub(i, 1)] + fRec5[faust_wrap_sub(i, 2)])));
				fRec26[i] = fSlow42 * fRec26[faust_wrap_sub(i, 1)] + fSlow43 * (fRec5[faust_wrap_sub(i, 1)] + fSlow44 * fRec27[i]);
				fYec7[(faust_wrap_add(i, fYec7_idx)) & 32767] = 0.35355339059327373 * fRec26[i] + 1e-20;
				fYec8[(faust_wrap_add(i, fYec8_idx)) & 4095] = fZec1[i] + 0.6 * fRec24[faust_wrap_sub(i, 1)] + fYec7[(faust_wrap_sub(faust_wrap_add(i, fYec7_idx), iConst22)) & 32767];
				fRec24[i] = fYec8[(faust_wrap_sub(faust_wrap_add(i, fYec8_idx), iConst23)) & 4095];
				fRec25[i] = -(0.6 * fYec8[(faust_wrap_add(i, fYec8_idx)) & 4095]);
				fRec31[i] = -(fSlow3 * (fSlow4 * fRec31[faust_wrap_sub(i, 1)] - (fRec10[faust_wrap_sub(i, 1)] + fRec10[faust_wrap_sub(i, 2)])));
				fRec30[i] = fSlow51 * fRec30[faust_wrap_sub(i, 1)] + fSlow52 * (fRec10[faust_wrap_sub(i, 1)] + fSlow53 * fRec31[i]);
				fYec9[(faust_wrap_add(i, fYec9_idx)) & 16383] = 0.35355339059327373 * fRec30[i] + 1e-20;
				fYec11[(faust_wrap_add(i, fYec11_idx)) & 2047] = fYec9[(faust_wrap_sub(faust_wrap_add(i, fYec9_idx), iConst27)) & 16383] - (fZec3[i] + 0.6 * fRec28[faust_wrap_sub(i, 1)]);
				fRec28[i] = fYec11[(faust_wrap_sub(faust_wrap_add(i, fYec11_idx), iConst28)) & 2047];
				fRec29[i] = 0.6 * fYec11[(faust_wrap_add(i, fYec11_idx)) & 2047];
				fRec35[i] = -(fSlow3 * (fSlow4 * fRec35[faust_wrap_sub(i, 1)] - (fRec6[faust_wrap_sub(i, 1)] + fRec6[faust_wrap_sub(i, 2)])));
				fRec34[i] = fSlow60 * fRec34[faust_wrap_sub(i, 1)] + fSlow61 * (fRec6[faust_wrap_sub(i, 1)] + fSlow62 * fRec35[i]);
				fYec12[(faust_wrap_add(i, fYec12_idx)) & 16383] = 0.35355339059327373 * fRec34[i] + 1e-20;
				fYec13[(faust_wrap_add(i, fYec13_idx)) & 4095] = fYec12[(faust_wrap_sub(faust_wrap_add(i, fYec12_idx), iConst32)) & 16383] - (fZec3[i] + 0.6 * fRec32[faust_wrap_sub(i, 1)]);
				fRec32[i] = fYec13[(faust_wrap_sub(faust_wrap_add(i, fYec13_idx), iConst33)) & 4095];
				fRec33[i] = 0.6 * fYec13[(faust_wrap_add(i, fYec13_idx)) & 4095];
				fRec39[i] = -(fSlow3 * (fSlow4 * fRec39[faust_wrap_sub(i, 1)] - (fRec8[faust_wrap_sub(i, 1)] + fRec8[faust_wrap_sub(i, 2)])));
				fRec38[i] = fSlow69 * fRec38[faust_wrap_sub(i, 1)] + fSlow70 * (fRec8[faust_wrap_sub(i, 1)] + fSlow71 * fRec39[i]);
				fYec14[(faust_wrap_add(i, fYec14_idx)) & 16383] = 0.35355339059327373 * fRec38[i] + 1e-20;
				fYec15[(faust_wrap_add(i, fYec15_idx)) & 4095] = fZec3[i] + fYec14[(faust_wrap_sub(faust_wrap_add(i, fYec14_idx), iConst37)) & 16383] - 0.6 * fRec36[faust_wrap_sub(i, 1)];
				fRec36[i] = fYec15[(faust_wrap_sub(faust_wrap_add(i, fYec15_idx), iConst38)) & 4095];
				fRec37[i] = 0.6 * fYec15[(faust_wrap_add(i, fYec15_idx)) & 4095];
				fRec43[i] = -(fSlow3 * (fSlow4 * fRec43[faust_wrap_sub(i, 1)] - (fRec4[faust_wrap_sub(i, 1)] + fRec4[faust_wrap_sub(i, 2)])));
				fRec42[i] = fSlow78 * fRec42[faust_wrap_sub(i, 1)] + fSlow79 * (fRec4[faust_wrap_sub(i, 1)] + fSlow80 * fRec43[i]);
				fYec16[(faust_wrap_add(i, fYec16_idx)) & 16383] = 0.35355339059327373 * fRec42[i] + 1e-20;
				fYec17[(faust_wrap_add(i, fYec17_idx)) & 2047] = fYec16[(faust_wrap_sub(faust_wrap_add(i, fYec16_idx), iConst42)) & 16383] + fZec3[i] - 0.6 * fRec40[faust_wrap_sub(i, 1)];
				fRec40[i] = fYec17[(faust_wrap_sub(faust_wrap_add(i, fYec17_idx), iConst43)) & 2047];
				fRec41[i] = 0.6 * fYec17[(faust_wrap_add(i, fYec17_idx)) & 2047];
				fZec4[i] = fRec41[i] + fRec37[i];
				fZec5[i] = fRec29[i] + fRec33[i] + fZec4[i];
				fRec4[i] = fRec12[faust_wrap_sub(i, 1)] + fRec16[faust_wrap_sub(i, 1)] + fRec20[faust_wrap_sub(i, 1)] + fRec24[faust_wrap_sub(i, 1)] + fRec28[faust_wrap_sub(i, 1)] + fRec32[faust_wrap_sub(i, 1)] + fRec36[faust_wrap_sub(i, 1)] + fRec40[faust_wrap_sub(i, 1)] + fRec13[i] + fRec17[i] + fRec21[i] + fRec25[i] + fZec5[i];
				fRec5[i] = fRec28[faust_wrap_sub(i, 1)] + fRec32[faust_wrap_sub(i, 1)] + fRec36[faust_wrap_sub(i, 1)] + fRec40[faust_wrap_sub(i, 1)] + fZec5[i] - (fRec12[faust_wrap_sub(i, 1)] + fRec16[faust_wrap_sub(i, 1)] + fRec20[faust_wrap_sub(i, 1)] + fRec24[faust_wrap_sub(i, 1)] + fRec13[i] + fRec17[i] + fRec25[i] + fRec21[i]);
				fZec6[i] = fRec33[i] + fRec29[i];
				fRec6[i] = fRec20[faust_wrap_sub(i, 1)] + fRec24[faust_wrap_sub(i, 1)] + fRec36[faust_wrap_sub(i, 1)] + fRec40[faust_wrap_sub(i, 1)] + fRec21[i] + fRec25[i] + fZec4[i] - (fRec12[faust_wrap_sub(i, 1)] + fRec16[faust_wrap_sub(i, 1)] + fRec28[faust_wrap_sub(i, 1)] + fRec32[faust_wrap_sub(i, 1)] + fRec13[i] + fRec17[i] + fZec6[i]);
				fRec7[i] = fRec12[faust_wrap_sub(i, 1)] + fRec16[faust_wrap_sub(i, 1)] + fRec36[faust_wrap_sub(i, 1)] + fRec40[faust_wrap_sub(i, 1)] + fRec13[i] + fRec17[i] + fZec4[i] - (fRec20[faust_wrap_sub(i, 1)] + fRec24[faust_wrap_sub(i, 1)] + fRec28[faust_wrap_sub(i, 1)] + fRec32[faust_wrap_sub(i, 1)] + fRec21[i] + fRec25[i] + fZec6[i]);
				fZec7[i] = fRec41[i] + fRec33[i];
				fZec8[i] = fRec37[i] + fRec29[i];
				fRec8[i] = fRec16[faust_wrap_sub(i, 1)] + fRec24[faust_wrap_sub(i, 1)] + fRec32[faust_wrap_sub(i, 1)] + fRec40[faust_wrap_sub(i, 1)] + fRec17[i] + fRec25[i] + fZec7[i] - (fRec12[faust_wrap_sub(i, 1)] + fRec20[faust_wrap_sub(i, 1)] + fRec28[faust_wrap_sub(i, 1)] + fRec36[faust_wrap_sub(i, 1)] + fRec13[i] + fRec21[i] + fZec8[i]);
				fRec9[i] = fRec12[faust_wrap_sub(i, 1)] + fRec20[faust_wrap_sub(i, 1)] + fRec32[faust_wrap_sub(i, 1)] + fRec40[faust_wrap_sub(i, 1)] + fRec13[i] + fRec21[i] + fZec7[i] - (fRec16[faust_wrap_sub(i, 1)] + fRec24[faust_wrap_sub(i, 1)] + fRec28[faust_wrap_sub(i, 1)] + fRec36[faust_wrap_sub(i, 1)] + fRec17[i] + fRec25[i] + fZec8[i]);
				fZec9[i] = fRec41[i] + fRec29[i];
				fZec10[i] = fRec37[i] + fRec33[i];
				fRec10[i] = fRec12[faust_wrap_sub(i, 1)] + fRec24[faust_wrap_sub(i, 1)] + fRec28[faust_wrap_sub(i, 1)] + fRec40[faust_wrap_sub(i, 1)] + fRec13[i] + fRec25[i] + fZec9[i] - (fRec16[faust_wrap_sub(i, 1)] + fRec20[faust_wrap_sub(i, 1)] + fRec32[faust_wrap_sub(i, 1)] + fRec36[faust_wrap_sub(i, 1)] + fRec17[i] + fRec21[i] + fZec10[i]);
				fRec11[i] = fRec16[faust_wrap_sub(i, 1)] + fRec20[faust_wrap_sub(i, 1)] + fRec28[faust_wrap_sub(i, 1)] + fRec40[faust_wrap_sub(i, 1)] + fRec17[i] + fRec21[i] + fZec9[i] - (fRec12[faust_wrap_sub(i, 1)] + fRec24[faust_wrap_sub(i, 1)] + fRec32[faust_wrap_sub(i, 1)] + fRec36[faust_wrap_sub(i, 1)] + fRec13[i] + fRec25[i] + fZec10[i]);
			}
			/* Post code */
			fYec16_idx_save = vsize;
			fYec17_idx_save = vsize;
			for (int j47 = 0; j47 < 4; j47 = faust_wrap_add(j47, 1)) {
				fRec43_perm[j47] = fRec43_tmp[faust_wrap_add(vsize, j47)];
			}
			for (int j49 = 0; j49 < 4; j49 = faust_wrap_add(j49, 1)) {
				fRec42_perm[j49] = fRec42_tmp[faust_wrap_add(vsize, j49)];
			}
			for (int j51 = 0; j51 < 4; j51 = faust_wrap_add(j51, 1)) {
				fRec40_perm[j51] = fRec40_tmp[faust_wrap_add(vsize, j51)];
			}
			fYec14_idx_save = vsize;
			fYec15_idx_save = vsize;
			for (int j41 = 0; j41 < 4; j41 = faust_wrap_add(j41, 1)) {
				fRec39_perm[j41] = fRec39_tmp[faust_wrap_add(vsize, j41)];
			}
			for (int j43 = 0; j43 < 4; j43 = faust_wrap_add(j43, 1)) {
				fRec38_perm[j43] = fRec38_tmp[faust_wrap_add(vsize, j43)];
			}
			for (int j45 = 0; j45 < 4; j45 = faust_wrap_add(j45, 1)) {
				fRec36_perm[j45] = fRec36_tmp[faust_wrap_add(vsize, j45)];
			}
			fYec12_idx_save = vsize;
			fYec13_idx_save = vsize;
			for (int j35 = 0; j35 < 4; j35 = faust_wrap_add(j35, 1)) {
				fRec35_perm[j35] = fRec35_tmp[faust_wrap_add(vsize, j35)];
			}
			for (int j37 = 0; j37 < 4; j37 = faust_wrap_add(j37, 1)) {
				fRec34_perm[j37] = fRec34_tmp[faust_wrap_add(vsize, j37)];
			}
			for (int j39 = 0; j39 < 4; j39 = faust_wrap_add(j39, 1)) {
				fRec32_perm[j39] = fRec32_tmp[faust_wrap_add(vsize, j39)];
			}
			fYec9_idx_save = vsize;
			fYec11_idx_save = vsize;
			for (int j29 = 0; j29 < 4; j29 = faust_wrap_add(j29, 1)) {
				fRec31_perm[j29] = fRec31_tmp[faust_wrap_add(vsize, j29)];
			}
			for (int j31 = 0; j31 < 4; j31 = faust_wrap_add(j31, 1)) {
				fRec30_perm[j31] = fRec30_tmp[faust_wrap_add(vsize, j31)];
			}
			for (int j33 = 0; j33 < 4; j33 = faust_wrap_add(j33, 1)) {
				fRec28_perm[j33] = fRec28_tmp[faust_wrap_add(vsize, j33)];
			}
			fYec7_idx_save = vsize;
			fYec8_idx_save = vsize;
			for (int j23 = 0; j23 < 4; j23 = faust_wrap_add(j23, 1)) {
				fRec27_perm[j23] = fRec27_tmp[faust_wrap_add(vsize, j23)];
			}
			for (int j25 = 0; j25 < 4; j25 = faust_wrap_add(j25, 1)) {
				fRec26_perm[j25] = fRec26_tmp[faust_wrap_add(vsize, j25)];
			}
			for (int j27 = 0; j27 < 4; j27 = faust_wrap_add(j27, 1)) {
				fRec24_perm[j27] = fRec24_tmp[faust_wrap_add(vsize, j27)];
			}
			fYec5_idx_save = vsize;
			fYec6_idx_save = vsize;
			for (int j17 = 0; j17 < 4; j17 = faust_wrap_add(j17, 1)) {
				fRec23_perm[j17] = fRec23_tmp[faust_wrap_add(vsize, j17)];
			}
			for (int j19 = 0; j19 < 4; j19 = faust_wrap_add(j19, 1)) {
				fRec22_perm[j19] = fRec22_tmp[faust_wrap_add(vsize, j19)];
			}
			for (int j21 = 0; j21 < 4; j21 = faust_wrap_add(j21, 1)) {
				fRec20_perm[j21] = fRec20_tmp[faust_wrap_add(vsize, j21)];
			}
			fYec3_idx_save = vsize;
			fYec4_idx_save = vsize;
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				fRec19_perm[j11] = fRec19_tmp[faust_wrap_add(vsize, j11)];
			}
			for (int j13 = 0; j13 < 4; j13 = faust_wrap_add(j13, 1)) {
				fRec18_perm[j13] = fRec18_tmp[faust_wrap_add(vsize, j13)];
			}
			for (int j15 = 0; j15 < 4; j15 = faust_wrap_add(j15, 1)) {
				fRec16_perm[j15] = fRec16_tmp[faust_wrap_add(vsize, j15)];
			}
			fYec0_idx_save = vsize;
			fYec2_idx_save = vsize;
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fRec15_perm[j5] = fRec15_tmp[faust_wrap_add(vsize, j5)];
			}
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec14_perm[j7] = fRec14_tmp[faust_wrap_add(vsize, j7)];
			}
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fRec12_perm[j9] = fRec12_tmp[faust_wrap_add(vsize, j9)];
			}
			for (int j53 = 0; j53 < 4; j53 = faust_wrap_add(j53, 1)) {
				fRec4_perm[j53] = fRec4_tmp[faust_wrap_add(vsize, j53)];
			}
			for (int j55 = 0; j55 < 4; j55 = faust_wrap_add(j55, 1)) {
				fRec5_perm[j55] = fRec5_tmp[faust_wrap_add(vsize, j55)];
			}
			for (int j57 = 0; j57 < 4; j57 = faust_wrap_add(j57, 1)) {
				fRec6_perm[j57] = fRec6_tmp[faust_wrap_add(vsize, j57)];
			}
			for (int j59 = 0; j59 < 4; j59 = faust_wrap_add(j59, 1)) {
				fRec7_perm[j59] = fRec7_tmp[faust_wrap_add(vsize, j59)];
			}
			for (int j61 = 0; j61 < 4; j61 = faust_wrap_add(j61, 1)) {
				fRec8_perm[j61] = fRec8_tmp[faust_wrap_add(vsize, j61)];
			}
			for (int j63 = 0; j63 < 4; j63 = faust_wrap_add(j63, 1)) {
				fRec9_perm[j63] = fRec9_tmp[faust_wrap_add(vsize, j63)];
			}
			for (int j65 = 0; j65 < 4; j65 = faust_wrap_add(j65, 1)) {
				fRec10_perm[j65] = fRec10_tmp[faust_wrap_add(vsize, j65)];
			}
			for (int j67 = 0; j67 < 4; j67 = faust_wrap_add(j67, 1)) {
				fRec11_perm[j67] = fRec11_tmp[faust_wrap_add(vsize, j67)];
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec11[i] = 0.37 * (fRec5[i] + fRec6[i]);
			}
			/* Recursive loop 8 */
			/* Pre code */
			for (int j68 = 0; j68 < 4; j68 = faust_wrap_add(j68, 1)) {
				fRec3_tmp[j68] = fRec3_perm[j68];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec12[i] = fSlow85 * fRec3[faust_wrap_sub(i, 1)];
				fZec13[i] = fZec11[i] + fZec12[i];
				fRec3[i] = fZec13[i] - fSlow84 * fRec3[faust_wrap_sub(i, 2)];
			}
			/* Post code */
			for (int j69 = 0; j69 < 4; j69 = faust_wrap_add(j69, 1)) {
				fRec3_perm[j69] = fRec3_tmp[faust_wrap_add(vsize, j69)];
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec14[i] = fSlow84 * fRec3[i];
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec15[i] = 0.5 * (fZec14[i] + fZec11[i] + fRec3[faust_wrap_sub(i, 2)] - fZec12[i] + fSlow82 * (fRec3[faust_wrap_sub(i, 2)] + fZec14[i] - fZec13[i]));
			}
			/* Recursive loop 11 */
			/* Pre code */
			for (int j70 = 0; j70 < 4; j70 = faust_wrap_add(j70, 1)) {
				fRec2_tmp[j70] = fRec2_perm[j70];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec16[i] = fSlow90 * fRec2[faust_wrap_sub(i, 1)];
				fZec17[i] = fZec15[i] + fZec16[i];
				fRec2[i] = fZec17[i] - fSlow89 * fRec2[faust_wrap_sub(i, 2)];
			}
			/* Post code */
			for (int j71 = 0; j71 < 4; j71 = faust_wrap_add(j71, 1)) {
				fRec2_perm[j71] = fRec2_tmp[faust_wrap_add(vsize, j71)];
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec18[i] = fRec1[i] + 1.0;
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec19[i] = fSlow89 * fRec2[i];
			}
			/* Vectorizable loop 14 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec20[i] = 1.0 - 0.5 * fZec18[i];
			}
			/* Vectorizable loop 15 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fRec0[i] * (0.25 * fZec18[i] * (fZec19[i] + fZec15[i] + fRec2[faust_wrap_sub(i, 2)] - fZec16[i] + fSlow87 * (fRec2[faust_wrap_sub(i, 2)] + fZec19[i] - fZec17[i])) + static_cast<double>(input0[i]) * fZec20[i]));
			}
			/* Vectorizable loop 16 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec21[i] = 0.37 * (fRec5[i] - fRec6[i]);
			}
			/* Recursive loop 17 */
			/* Pre code */
			for (int j72 = 0; j72 < 4; j72 = faust_wrap_add(j72, 1)) {
				fRec45_tmp[j72] = fRec45_perm[j72];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec22[i] = fSlow85 * fRec45[faust_wrap_sub(i, 1)];
				fZec23[i] = fZec21[i] + fZec22[i];
				fRec45[i] = fZec23[i] - fSlow84 * fRec45[faust_wrap_sub(i, 2)];
			}
			/* Post code */
			for (int j73 = 0; j73 < 4; j73 = faust_wrap_add(j73, 1)) {
				fRec45_perm[j73] = fRec45_tmp[faust_wrap_add(vsize, j73)];
			}
			/* Vectorizable loop 18 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec24[i] = fSlow84 * fRec45[i];
			}
			/* Vectorizable loop 19 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec25[i] = 0.5 * (fZec24[i] + fZec21[i] + fRec45[faust_wrap_sub(i, 2)] - fZec22[i] + fSlow82 * (fRec45[faust_wrap_sub(i, 2)] + fZec24[i] - fZec23[i]));
			}
			/* Recursive loop 20 */
			/* Pre code */
			for (int j74 = 0; j74 < 4; j74 = faust_wrap_add(j74, 1)) {
				fRec44_tmp[j74] = fRec44_perm[j74];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec26[i] = fSlow90 * fRec44[faust_wrap_sub(i, 1)];
				fZec27[i] = fZec25[i] + fZec26[i];
				fRec44[i] = fZec27[i] - fSlow89 * fRec44[faust_wrap_sub(i, 2)];
			}
			/* Post code */
			for (int j75 = 0; j75 < 4; j75 = faust_wrap_add(j75, 1)) {
				fRec44_perm[j75] = fRec44_tmp[faust_wrap_add(vsize, j75)];
			}
			/* Vectorizable loop 21 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec28[i] = fSlow89 * fRec44[i];
			}
			/* Vectorizable loop 22 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fRec0[i] * (0.25 * fZec18[i] * (fZec28[i] + fZec25[i] + fRec44[faust_wrap_sub(i, 2)] - fZec26[i] + fSlow87 * (fRec44[faust_wrap_sub(i, 2)] + fZec28[i] - fZec27[i])) + static_cast<double>(input1[i]) * fZec20[i]));
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
