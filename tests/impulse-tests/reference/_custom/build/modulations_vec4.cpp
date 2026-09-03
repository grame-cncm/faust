/* ------------------------------------------------------------
author: "ER"
name: "modulations"
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

class mydspSIG0 {
	
  private:
	
	int iRec28[2];
	int fSampleRate;
	
  public:
	
	int getNumInputsmydspSIG0() {
		return 0;
	}
	int getNumOutputsmydspSIG0() {
		return 1;
	}
	
	void instanceInitmydspSIG0(int sample_rate) {
		fSampleRate = sample_rate;
		for (int l11 = 0; l11 < 2; l11 = faust_wrap_add(l11, 1)) {
			iRec28[l11] = 0;
		}
	}
	
	void fillmydspSIG0(int count, double* table) {
		for (int i1 = 0; i1 < count; i1 = faust_wrap_add(i1, 1)) {
			iRec28[0] = faust_wrap_add(iRec28[1], 1);
			table[i1] = std::sin(9.587379924285257e-05 * static_cast<double>(faust_wrap_add(iRec28[0], -1)));
			iRec28[1] = iRec28[0];
		}
	}

};

static mydspSIG0* newmydspSIG0() { return (mydspSIG0*)new mydspSIG0(); }
static void deletemydspSIG0(mydspSIG0* dsp) { delete dsp; }

static double mydsp_faustpower2_f(double value) {
	return value * value;
}
static double ftbl0mydspSIG0[65536];
static double ftbl1mydspSIG0[65537];

class mydsp : public dsp {
	
 private:
	
	FAUSTFLOAT fHslider0;
	double fRec0_perm[4];
	int fSampleRate;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fRec12_perm[4];
	double fConst4;
	double fConst5;
	double fConst6;
	double fConst7;
	FAUSTFLOAT fHslider1;
	double fConst8;
	double fRec11_perm[4];
	double fRec15_perm[4];
	FAUSTFLOAT fHslider2;
	double fRec17_perm[4];
	double fConst9;
	double fRec16_perm[4];
	FAUSTFLOAT fHslider3;
	double fConst10;
	double fRec18_perm[4];
	double fConst11;
	double fRec20_perm[4];
	double fConst12;
	double fRec19_perm[4];
	FAUSTFLOAT fHslider4;
	double fRec22_perm[4];
	double fRec21_perm[4];
	double fConst13;
	double fRec27_perm[4];
	double fRec26_perm[4];
	double fRec25_perm[4];
	double fRec24_perm[4];
	double fRec23_perm[4];
	double fRec14_perm[4];
	FAUSTFLOAT fHslider5;
	double fRec29_perm[4];
	double fRec31_perm[4];
	double fRec30_perm[4];
	double fRec37_perm[4];
	double fRec36_perm[4];
	double fRec35_perm[4];
	double fRec34_perm[4];
	double fRec33_perm[4];
	double fRec32_perm[4];
	FAUSTFLOAT fHslider6;
	double fRec38_perm[4];
	double fRec40_perm[4];
	double fRec39_perm[4];
	double fYec0_perm[4];
	double fRec46_perm[4];
	double fRec45_perm[4];
	double fRec44_perm[4];
	double fRec43_perm[4];
	double fRec42_perm[4];
	double fRec41_perm[4];
	FAUSTFLOAT fHslider7;
	double fRec47_perm[4];
	double fRec49_perm[4];
	double fRec48_perm[4];
	double fRec55_perm[4];
	double fRec54_perm[4];
	double fRec53_perm[4];
	double fRec52_perm[4];
	double fRec51_perm[4];
	double fRec50_perm[4];
	double fConst14;
	double fConst15;
	double fConst16;
	double fYec1_perm[4];
	double fRec13_perm[4];
	FAUSTFLOAT fHslider8;
	double fRec56_perm[4];
	FAUSTFLOAT fHslider9;
	double fRec57_perm[4];
	double fYec2[32768];
	int fYec2_idx;
	int fYec2_idx_save;
	double fConst17;
	int iConst18;
	double fYec3[4096];
	int fYec3_idx;
	int fYec3_idx_save;
	int iConst19;
	double fYec4[2048];
	int fYec4_idx;
	int fYec4_idx_save;
	int iConst20;
	double fRec9_perm[4];
	double fRec61_perm[4];
	double fConst21;
	double fConst22;
	double fConst23;
	double fConst24;
	double fRec60_perm[4];
	double fYec5[32768];
	int fYec5_idx;
	int fYec5_idx_save;
	double fConst25;
	int iConst26;
	double fYec6[4096];
	int fYec6_idx;
	int fYec6_idx_save;
	int iConst27;
	double fRec58_perm[4];
	double fRec65_perm[4];
	double fConst28;
	double fConst29;
	double fConst30;
	double fConst31;
	double fRec64_perm[4];
	double fYec7[16384];
	int fYec7_idx;
	int fYec7_idx_save;
	double fConst32;
	int iConst33;
	double fYec8[4096];
	int fYec8_idx;
	int fYec8_idx_save;
	int iConst34;
	double fRec62_perm[4];
	double fRec69_perm[4];
	double fConst35;
	double fConst36;
	double fConst37;
	double fConst38;
	double fRec68_perm[4];
	double fYec9[32768];
	int fYec9_idx;
	int fYec9_idx_save;
	double fConst39;
	int iConst40;
	double fYec10[4096];
	int fYec10_idx;
	int fYec10_idx_save;
	int iConst41;
	double fRec66_perm[4];
	double fRec73_perm[4];
	double fConst42;
	double fConst43;
	double fConst44;
	double fConst45;
	double fRec72_perm[4];
	double fYec11[16384];
	int fYec11_idx;
	int fYec11_idx_save;
	double fConst46;
	int iConst47;
	double fYec12[2048];
	int fYec12_idx;
	int fYec12_idx_save;
	int iConst48;
	double fRec70_perm[4];
	double fRec77_perm[4];
	double fConst49;
	double fConst50;
	double fConst51;
	double fConst52;
	double fRec76_perm[4];
	double fYec13[16384];
	int fYec13_idx;
	int fYec13_idx_save;
	double fConst53;
	int iConst54;
	double fYec14[4096];
	int fYec14_idx;
	int fYec14_idx_save;
	int iConst55;
	double fRec74_perm[4];
	double fRec81_perm[4];
	double fConst56;
	double fConst57;
	double fConst58;
	double fConst59;
	double fRec80_perm[4];
	double fYec15[16384];
	int fYec15_idx;
	int fYec15_idx_save;
	double fConst60;
	int iConst61;
	double fYec16[4096];
	int fYec16_idx;
	int fYec16_idx_save;
	int iConst62;
	double fRec78_perm[4];
	double fRec85_perm[4];
	double fConst63;
	double fConst64;
	double fConst65;
	double fConst66;
	double fRec84_perm[4];
	double fYec17[16384];
	int fYec17_idx;
	int fYec17_idx_save;
	double fConst67;
	int iConst68;
	double fYec18[2048];
	int fYec18_idx;
	int fYec18_idx_save;
	int iConst69;
	double fRec82_perm[4];
	double fRec1_perm[4];
	double fRec2_perm[4];
	double fRec3_perm[4];
	double fRec4_perm[4];
	double fRec5_perm[4];
	double fRec6_perm[4];
	double fRec7_perm[4];
	double fRec8_perm[4];
	
 public:
	mydsp() {
	}
	
	mydsp(const mydsp&) = default;
	
	virtual ~mydsp() = default;
	
	mydsp& operator=(const mydsp&) = default;
	
	void metadata(Meta* m) { 
		m->declare("author", "ER");
		m->declare("basics_lib_name", "Faust Basic Element Library");
		m->declare("basics_lib_version", "0.0");
		m->declare("compilation_options", "-single -scal -e modulations.dsp -o modulations_exp.dsp");
		m->declare("compile_options", "-a /Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/archs/impulsearch.cpp -lang cpp -i -fpga-mem-th 4 -ct 1 -es 1 -mcd 4 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs");
		m->declare("delays_lib_name", "Faust Delay Library");
		m->declare("delays_lib_version", "0.1");
		m->declare("envelopes_lib_author", "GRAME");
		m->declare("envelopes_lib_copyright", "GRAME");
		m->declare("envelopes_lib_license", "LGPL with exception");
		m->declare("envelopes_lib_name", "Faust Envelope Library");
		m->declare("envelopes_lib_version", "0.0");
		m->declare("filename", "modulations.dsp");
		m->declare("filters_lib_name", "Faust Filters Library");
		m->declare("filters_lib_version", "0.0");
		m->declare("instruments_lib_author", "Romain Michon (rmichon@ccrma.stanford.edu)");
		m->declare("instruments_lib_copyright", "Romain Michon");
		m->declare("instruments_lib_licence", "STK-4.3");
		m->declare("instruments_lib_name", "Faust-STK Tools Library");
		m->declare("instruments_lib_version", "1.0");
		m->declare("library_path", "/usr/local/share/faust/stdfaust.lib");
		m->declare("maths_lib_author", "GRAME");
		m->declare("maths_lib_copyright", "GRAME");
		m->declare("maths_lib_license", "LGPL with exception");
		m->declare("maths_lib_name", "Faust Math Library");
		m->declare("maths_lib_version", "2.1");
		m->declare("name", "modulations");
		m->declare("oscillators_lib_name", "Faust Oscillator Library");
		m->declare("oscillators_lib_version", "0.0");
		m->declare("reverbs_lib_name", "Faust Reverb Library");
		m->declare("reverbs_lib_version", "0.0");
		m->declare("routes_lib_name", "Faust Signal Routing Library");
		m->declare("routes_lib_version", "0.0");
		m->declare("signals_lib_name", "Faust Signal Routing Library");
		m->declare("signals_lib_version", "0.0");
	}

	virtual int getNumInputs() {
		return 0;
	}
	virtual int getNumOutputs() {
		return 2;
	}
	
	static void classInit(int sample_rate) {
		mydspSIG0* sig0 = newmydspSIG0();
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(65536, ftbl0mydspSIG0);
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(65537, ftbl1mydspSIG0);
		deletemydspSIG0(sig0);
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, static_cast<double>(fSampleRate)));
		fConst1 = 1.0 / std::tan(628.3185307179587 / fConst0);
		fConst2 = 1.0 / (fConst1 + 1.0);
		fConst3 = 1.0 - fConst1;
		fConst4 = std::cos(37699.11184307752 / fConst0);
		fConst5 = std::floor(0.219991 * fConst0 + 0.5);
		fConst6 = fConst5 / fConst0;
		fConst7 = 3.453877639491069 * fConst6;
		fConst8 = 2.302585092994046 * fConst6;
		fConst9 = 1.0 / fConst0;
		fConst10 = 2.0 * fConst0;
		fConst11 = 3.0 * fConst0;
		fConst12 = 0.3333333333333333 / fConst0;
		fConst13 = 0.5 / fConst0;
		fConst14 = 1.0 / std::tan(6283.185307179586 / fConst0);
		fConst15 = 1.0 / (fConst14 + 1.0);
		fConst16 = 1.0 - fConst14;
		fConst17 = std::floor(0.019123 * fConst0 + 0.5);
		iConst18 = static_cast<int>(std::min<double>(16384.0, std::max<double>(0.0, fConst5 - fConst17)));
		iConst19 = static_cast<int>(std::min<double>(8192.0, std::max<double>(0.0, 0.02 * fConst0)));
		iConst20 = static_cast<int>(std::min<double>(1024.0, std::max<double>(0.0, fConst17 + -1.0)));
		fConst21 = std::floor(0.256891 * fConst0 + 0.5);
		fConst22 = fConst21 / fConst0;
		fConst23 = 3.453877639491069 * fConst22;
		fConst24 = 2.302585092994046 * fConst22;
		fConst25 = std::floor(0.027333 * fConst0 + 0.5);
		iConst26 = static_cast<int>(std::min<double>(16384.0, std::max<double>(0.0, fConst21 - fConst25)));
		iConst27 = static_cast<int>(std::min<double>(2048.0, std::max<double>(0.0, fConst25 + -1.0)));
		fConst28 = std::floor(0.192303 * fConst0 + 0.5);
		fConst29 = fConst28 / fConst0;
		fConst30 = 3.453877639491069 * fConst29;
		fConst31 = 2.302585092994046 * fConst29;
		fConst32 = std::floor(0.029291 * fConst0 + 0.5);
		iConst33 = static_cast<int>(std::min<double>(8192.0, std::max<double>(0.0, fConst28 - fConst32)));
		iConst34 = static_cast<int>(std::min<double>(2048.0, std::max<double>(0.0, fConst32 + -1.0)));
		fConst35 = std::floor(0.210389 * fConst0 + 0.5);
		fConst36 = fConst35 / fConst0;
		fConst37 = 3.453877639491069 * fConst36;
		fConst38 = 2.302585092994046 * fConst36;
		fConst39 = std::floor(0.024421 * fConst0 + 0.5);
		iConst40 = static_cast<int>(std::min<double>(16384.0, std::max<double>(0.0, fConst35 - fConst39)));
		iConst41 = static_cast<int>(std::min<double>(2048.0, std::max<double>(0.0, fConst39 + -1.0)));
		fConst42 = std::floor(0.125 * fConst0 + 0.5);
		fConst43 = fConst42 / fConst0;
		fConst44 = 3.453877639491069 * fConst43;
		fConst45 = 2.302585092994046 * fConst43;
		fConst46 = std::floor(0.013458 * fConst0 + 0.5);
		iConst47 = static_cast<int>(std::min<double>(8192.0, std::max<double>(0.0, fConst42 - fConst46)));
		iConst48 = static_cast<int>(std::min<double>(1024.0, std::max<double>(0.0, fConst46 + -1.0)));
		fConst49 = std::floor(0.127837 * fConst0 + 0.5);
		fConst50 = fConst49 / fConst0;
		fConst51 = 3.453877639491069 * fConst50;
		fConst52 = 2.302585092994046 * fConst50;
		fConst53 = std::floor(0.031604 * fConst0 + 0.5);
		iConst54 = static_cast<int>(std::min<double>(8192.0, std::max<double>(0.0, fConst49 - fConst53)));
		iConst55 = static_cast<int>(std::min<double>(2048.0, std::max<double>(0.0, fConst53 + -1.0)));
		fConst56 = std::floor(0.174713 * fConst0 + 0.5);
		fConst57 = fConst56 / fConst0;
		fConst58 = 3.453877639491069 * fConst57;
		fConst59 = 2.302585092994046 * fConst57;
		fConst60 = std::floor(0.022904 * fConst0 + 0.5);
		iConst61 = static_cast<int>(std::min<double>(8192.0, std::max<double>(0.0, fConst56 - fConst60)));
		iConst62 = static_cast<int>(std::min<double>(2048.0, std::max<double>(0.0, fConst60 + -1.0)));
		fConst63 = std::floor(0.153129 * fConst0 + 0.5);
		fConst64 = fConst63 / fConst0;
		fConst65 = 3.453877639491069 * fConst64;
		fConst66 = 2.302585092994046 * fConst64;
		fConst67 = std::floor(0.020346 * fConst0 + 0.5);
		iConst68 = static_cast<int>(std::min<double>(8192.0, std::max<double>(0.0, fConst63 - fConst67)));
		iConst69 = static_cast<int>(std::min<double>(1024.0, std::max<double>(0.0, fConst67 + -1.0)));
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(1.0);
		fHslider1 = static_cast<FAUSTFLOAT>(0.5);
		fHslider2 = static_cast<FAUSTFLOAT>(1.2e+03);
		fHslider3 = static_cast<FAUSTFLOAT>(0.0);
		fHslider4 = static_cast<FAUSTFLOAT>(3.3e+02);
		fHslider5 = static_cast<FAUSTFLOAT>(0.0);
		fHslider6 = static_cast<FAUSTFLOAT>(0.0);
		fHslider7 = static_cast<FAUSTFLOAT>(0.0);
		fHslider8 = static_cast<FAUSTFLOAT>(0.5);
		fHslider9 = static_cast<FAUSTFLOAT>(0.25);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 4; l0 = faust_wrap_add(l0, 1)) {
			fRec0_perm[l0] = 0.0;
		}
		for (int l1 = 0; l1 < 4; l1 = faust_wrap_add(l1, 1)) {
			fRec12_perm[l1] = 0.0;
		}
		for (int l2 = 0; l2 < 4; l2 = faust_wrap_add(l2, 1)) {
			fRec11_perm[l2] = 0.0;
		}
		for (int l3 = 0; l3 < 4; l3 = faust_wrap_add(l3, 1)) {
			fRec15_perm[l3] = 0.0;
		}
		for (int l4 = 0; l4 < 4; l4 = faust_wrap_add(l4, 1)) {
			fRec17_perm[l4] = 0.0;
		}
		for (int l5 = 0; l5 < 4; l5 = faust_wrap_add(l5, 1)) {
			fRec16_perm[l5] = 0.0;
		}
		for (int l6 = 0; l6 < 4; l6 = faust_wrap_add(l6, 1)) {
			fRec18_perm[l6] = 0.0;
		}
		for (int l7 = 0; l7 < 4; l7 = faust_wrap_add(l7, 1)) {
			fRec20_perm[l7] = 0.0;
		}
		for (int l8 = 0; l8 < 4; l8 = faust_wrap_add(l8, 1)) {
			fRec19_perm[l8] = 0.0;
		}
		for (int l9 = 0; l9 < 4; l9 = faust_wrap_add(l9, 1)) {
			fRec22_perm[l9] = 0.0;
		}
		for (int l10 = 0; l10 < 4; l10 = faust_wrap_add(l10, 1)) {
			fRec21_perm[l10] = 0.0;
		}
		for (int l12 = 0; l12 < 4; l12 = faust_wrap_add(l12, 1)) {
			fRec27_perm[l12] = 0.0;
		}
		for (int l13 = 0; l13 < 4; l13 = faust_wrap_add(l13, 1)) {
			fRec26_perm[l13] = 0.0;
		}
		for (int l14 = 0; l14 < 4; l14 = faust_wrap_add(l14, 1)) {
			fRec25_perm[l14] = 0.0;
		}
		for (int l15 = 0; l15 < 4; l15 = faust_wrap_add(l15, 1)) {
			fRec24_perm[l15] = 0.0;
		}
		for (int l16 = 0; l16 < 4; l16 = faust_wrap_add(l16, 1)) {
			fRec23_perm[l16] = 0.0;
		}
		for (int l17 = 0; l17 < 4; l17 = faust_wrap_add(l17, 1)) {
			fRec14_perm[l17] = 0.0;
		}
		for (int l18 = 0; l18 < 4; l18 = faust_wrap_add(l18, 1)) {
			fRec29_perm[l18] = 0.0;
		}
		for (int l19 = 0; l19 < 4; l19 = faust_wrap_add(l19, 1)) {
			fRec31_perm[l19] = 0.0;
		}
		for (int l20 = 0; l20 < 4; l20 = faust_wrap_add(l20, 1)) {
			fRec30_perm[l20] = 0.0;
		}
		for (int l21 = 0; l21 < 4; l21 = faust_wrap_add(l21, 1)) {
			fRec37_perm[l21] = 0.0;
		}
		for (int l22 = 0; l22 < 4; l22 = faust_wrap_add(l22, 1)) {
			fRec36_perm[l22] = 0.0;
		}
		for (int l23 = 0; l23 < 4; l23 = faust_wrap_add(l23, 1)) {
			fRec35_perm[l23] = 0.0;
		}
		for (int l24 = 0; l24 < 4; l24 = faust_wrap_add(l24, 1)) {
			fRec34_perm[l24] = 0.0;
		}
		for (int l25 = 0; l25 < 4; l25 = faust_wrap_add(l25, 1)) {
			fRec33_perm[l25] = 0.0;
		}
		for (int l26 = 0; l26 < 4; l26 = faust_wrap_add(l26, 1)) {
			fRec32_perm[l26] = 0.0;
		}
		for (int l27 = 0; l27 < 4; l27 = faust_wrap_add(l27, 1)) {
			fRec38_perm[l27] = 0.0;
		}
		for (int l28 = 0; l28 < 4; l28 = faust_wrap_add(l28, 1)) {
			fRec40_perm[l28] = 0.0;
		}
		for (int l29 = 0; l29 < 4; l29 = faust_wrap_add(l29, 1)) {
			fRec39_perm[l29] = 0.0;
		}
		for (int l30 = 0; l30 < 4; l30 = faust_wrap_add(l30, 1)) {
			fYec0_perm[l30] = 0.0;
		}
		for (int l31 = 0; l31 < 4; l31 = faust_wrap_add(l31, 1)) {
			fRec46_perm[l31] = 0.0;
		}
		for (int l32 = 0; l32 < 4; l32 = faust_wrap_add(l32, 1)) {
			fRec45_perm[l32] = 0.0;
		}
		for (int l33 = 0; l33 < 4; l33 = faust_wrap_add(l33, 1)) {
			fRec44_perm[l33] = 0.0;
		}
		for (int l34 = 0; l34 < 4; l34 = faust_wrap_add(l34, 1)) {
			fRec43_perm[l34] = 0.0;
		}
		for (int l35 = 0; l35 < 4; l35 = faust_wrap_add(l35, 1)) {
			fRec42_perm[l35] = 0.0;
		}
		for (int l36 = 0; l36 < 4; l36 = faust_wrap_add(l36, 1)) {
			fRec41_perm[l36] = 0.0;
		}
		for (int l37 = 0; l37 < 4; l37 = faust_wrap_add(l37, 1)) {
			fRec47_perm[l37] = 0.0;
		}
		for (int l38 = 0; l38 < 4; l38 = faust_wrap_add(l38, 1)) {
			fRec49_perm[l38] = 0.0;
		}
		for (int l39 = 0; l39 < 4; l39 = faust_wrap_add(l39, 1)) {
			fRec48_perm[l39] = 0.0;
		}
		for (int l40 = 0; l40 < 4; l40 = faust_wrap_add(l40, 1)) {
			fRec55_perm[l40] = 0.0;
		}
		for (int l41 = 0; l41 < 4; l41 = faust_wrap_add(l41, 1)) {
			fRec54_perm[l41] = 0.0;
		}
		for (int l42 = 0; l42 < 4; l42 = faust_wrap_add(l42, 1)) {
			fRec53_perm[l42] = 0.0;
		}
		for (int l43 = 0; l43 < 4; l43 = faust_wrap_add(l43, 1)) {
			fRec52_perm[l43] = 0.0;
		}
		for (int l44 = 0; l44 < 4; l44 = faust_wrap_add(l44, 1)) {
			fRec51_perm[l44] = 0.0;
		}
		for (int l45 = 0; l45 < 4; l45 = faust_wrap_add(l45, 1)) {
			fRec50_perm[l45] = 0.0;
		}
		for (int l46 = 0; l46 < 4; l46 = faust_wrap_add(l46, 1)) {
			fYec1_perm[l46] = 0.0;
		}
		for (int l47 = 0; l47 < 4; l47 = faust_wrap_add(l47, 1)) {
			fRec13_perm[l47] = 0.0;
		}
		for (int l48 = 0; l48 < 4; l48 = faust_wrap_add(l48, 1)) {
			fRec56_perm[l48] = 0.0;
		}
		for (int l49 = 0; l49 < 4; l49 = faust_wrap_add(l49, 1)) {
			fRec57_perm[l49] = 0.0;
		}
		for (int l50 = 0; l50 < 32768; l50 = faust_wrap_add(l50, 1)) {
			fYec2[l50] = 0.0;
		}
		fYec2_idx = 0;
		fYec2_idx_save = 0;
		for (int l51 = 0; l51 < 4096; l51 = faust_wrap_add(l51, 1)) {
			fYec3[l51] = 0.0;
		}
		fYec3_idx = 0;
		fYec3_idx_save = 0;
		for (int l52 = 0; l52 < 2048; l52 = faust_wrap_add(l52, 1)) {
			fYec4[l52] = 0.0;
		}
		fYec4_idx = 0;
		fYec4_idx_save = 0;
		for (int l53 = 0; l53 < 4; l53 = faust_wrap_add(l53, 1)) {
			fRec9_perm[l53] = 0.0;
		}
		for (int l54 = 0; l54 < 4; l54 = faust_wrap_add(l54, 1)) {
			fRec61_perm[l54] = 0.0;
		}
		for (int l55 = 0; l55 < 4; l55 = faust_wrap_add(l55, 1)) {
			fRec60_perm[l55] = 0.0;
		}
		for (int l56 = 0; l56 < 32768; l56 = faust_wrap_add(l56, 1)) {
			fYec5[l56] = 0.0;
		}
		fYec5_idx = 0;
		fYec5_idx_save = 0;
		for (int l57 = 0; l57 < 4096; l57 = faust_wrap_add(l57, 1)) {
			fYec6[l57] = 0.0;
		}
		fYec6_idx = 0;
		fYec6_idx_save = 0;
		for (int l58 = 0; l58 < 4; l58 = faust_wrap_add(l58, 1)) {
			fRec58_perm[l58] = 0.0;
		}
		for (int l59 = 0; l59 < 4; l59 = faust_wrap_add(l59, 1)) {
			fRec65_perm[l59] = 0.0;
		}
		for (int l60 = 0; l60 < 4; l60 = faust_wrap_add(l60, 1)) {
			fRec64_perm[l60] = 0.0;
		}
		for (int l61 = 0; l61 < 16384; l61 = faust_wrap_add(l61, 1)) {
			fYec7[l61] = 0.0;
		}
		fYec7_idx = 0;
		fYec7_idx_save = 0;
		for (int l62 = 0; l62 < 4096; l62 = faust_wrap_add(l62, 1)) {
			fYec8[l62] = 0.0;
		}
		fYec8_idx = 0;
		fYec8_idx_save = 0;
		for (int l63 = 0; l63 < 4; l63 = faust_wrap_add(l63, 1)) {
			fRec62_perm[l63] = 0.0;
		}
		for (int l64 = 0; l64 < 4; l64 = faust_wrap_add(l64, 1)) {
			fRec69_perm[l64] = 0.0;
		}
		for (int l65 = 0; l65 < 4; l65 = faust_wrap_add(l65, 1)) {
			fRec68_perm[l65] = 0.0;
		}
		for (int l66 = 0; l66 < 32768; l66 = faust_wrap_add(l66, 1)) {
			fYec9[l66] = 0.0;
		}
		fYec9_idx = 0;
		fYec9_idx_save = 0;
		for (int l67 = 0; l67 < 4096; l67 = faust_wrap_add(l67, 1)) {
			fYec10[l67] = 0.0;
		}
		fYec10_idx = 0;
		fYec10_idx_save = 0;
		for (int l68 = 0; l68 < 4; l68 = faust_wrap_add(l68, 1)) {
			fRec66_perm[l68] = 0.0;
		}
		for (int l69 = 0; l69 < 4; l69 = faust_wrap_add(l69, 1)) {
			fRec73_perm[l69] = 0.0;
		}
		for (int l70 = 0; l70 < 4; l70 = faust_wrap_add(l70, 1)) {
			fRec72_perm[l70] = 0.0;
		}
		for (int l71 = 0; l71 < 16384; l71 = faust_wrap_add(l71, 1)) {
			fYec11[l71] = 0.0;
		}
		fYec11_idx = 0;
		fYec11_idx_save = 0;
		for (int l72 = 0; l72 < 2048; l72 = faust_wrap_add(l72, 1)) {
			fYec12[l72] = 0.0;
		}
		fYec12_idx = 0;
		fYec12_idx_save = 0;
		for (int l73 = 0; l73 < 4; l73 = faust_wrap_add(l73, 1)) {
			fRec70_perm[l73] = 0.0;
		}
		for (int l74 = 0; l74 < 4; l74 = faust_wrap_add(l74, 1)) {
			fRec77_perm[l74] = 0.0;
		}
		for (int l75 = 0; l75 < 4; l75 = faust_wrap_add(l75, 1)) {
			fRec76_perm[l75] = 0.0;
		}
		for (int l76 = 0; l76 < 16384; l76 = faust_wrap_add(l76, 1)) {
			fYec13[l76] = 0.0;
		}
		fYec13_idx = 0;
		fYec13_idx_save = 0;
		for (int l77 = 0; l77 < 4096; l77 = faust_wrap_add(l77, 1)) {
			fYec14[l77] = 0.0;
		}
		fYec14_idx = 0;
		fYec14_idx_save = 0;
		for (int l78 = 0; l78 < 4; l78 = faust_wrap_add(l78, 1)) {
			fRec74_perm[l78] = 0.0;
		}
		for (int l79 = 0; l79 < 4; l79 = faust_wrap_add(l79, 1)) {
			fRec81_perm[l79] = 0.0;
		}
		for (int l80 = 0; l80 < 4; l80 = faust_wrap_add(l80, 1)) {
			fRec80_perm[l80] = 0.0;
		}
		for (int l81 = 0; l81 < 16384; l81 = faust_wrap_add(l81, 1)) {
			fYec15[l81] = 0.0;
		}
		fYec15_idx = 0;
		fYec15_idx_save = 0;
		for (int l82 = 0; l82 < 4096; l82 = faust_wrap_add(l82, 1)) {
			fYec16[l82] = 0.0;
		}
		fYec16_idx = 0;
		fYec16_idx_save = 0;
		for (int l83 = 0; l83 < 4; l83 = faust_wrap_add(l83, 1)) {
			fRec78_perm[l83] = 0.0;
		}
		for (int l84 = 0; l84 < 4; l84 = faust_wrap_add(l84, 1)) {
			fRec85_perm[l84] = 0.0;
		}
		for (int l85 = 0; l85 < 4; l85 = faust_wrap_add(l85, 1)) {
			fRec84_perm[l85] = 0.0;
		}
		for (int l86 = 0; l86 < 16384; l86 = faust_wrap_add(l86, 1)) {
			fYec17[l86] = 0.0;
		}
		fYec17_idx = 0;
		fYec17_idx_save = 0;
		for (int l87 = 0; l87 < 2048; l87 = faust_wrap_add(l87, 1)) {
			fYec18[l87] = 0.0;
		}
		fYec18_idx = 0;
		fYec18_idx_save = 0;
		for (int l88 = 0; l88 < 4; l88 = faust_wrap_add(l88, 1)) {
			fRec82_perm[l88] = 0.0;
		}
		for (int l89 = 0; l89 < 4; l89 = faust_wrap_add(l89, 1)) {
			fRec1_perm[l89] = 0.0;
		}
		for (int l90 = 0; l90 < 4; l90 = faust_wrap_add(l90, 1)) {
			fRec2_perm[l90] = 0.0;
		}
		for (int l91 = 0; l91 < 4; l91 = faust_wrap_add(l91, 1)) {
			fRec3_perm[l91] = 0.0;
		}
		for (int l92 = 0; l92 < 4; l92 = faust_wrap_add(l92, 1)) {
			fRec4_perm[l92] = 0.0;
		}
		for (int l93 = 0; l93 < 4; l93 = faust_wrap_add(l93, 1)) {
			fRec5_perm[l93] = 0.0;
		}
		for (int l94 = 0; l94 < 4; l94 = faust_wrap_add(l94, 1)) {
			fRec6_perm[l94] = 0.0;
		}
		for (int l95 = 0; l95 < 4; l95 = faust_wrap_add(l95, 1)) {
			fRec7_perm[l95] = 0.0;
		}
		for (int l96 = 0; l96 < 4; l96 = faust_wrap_add(l96, 1)) {
			fRec8_perm[l96] = 0.0;
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
		ui_interface->openVerticalBox("Modulations");
		ui_interface->openHorizontalBox("Instrument");
		ui_interface->declare(&fHslider4, "acc", "1 1 -10 0 15");
		ui_interface->declare(&fHslider4, "unit", "Hz");
		ui_interface->addHorizontalSlider("Frequency", &fHslider4, FAUSTFLOAT(3.3e+02), FAUSTFLOAT(1e+02), FAUSTFLOAT(1.2e+03), FAUSTFLOAT(0.1));
		ui_interface->declare(&fHslider0, "acc", "1 1 -10 0 10");
		ui_interface->declare(&fHslider0, "style", "knob");
		ui_interface->addHorizontalSlider("General Volume", &fHslider0, FAUSTFLOAT(1.0), FAUSTFLOAT(0.75), FAUSTFLOAT(4.0), FAUSTFLOAT(0.01));
		ui_interface->declare(&fHslider8, "acc", "1 0 -10 0 10");
		ui_interface->declare(&fHslider8, "style", "knob");
		ui_interface->addHorizontalSlider("Oscillator Volume", &fHslider8, FAUSTFLOAT(0.5), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.01));
		ui_interface->declare(&fHslider2, "acc", "0 0 -10 0 10");
		ui_interface->declare(&fHslider2, "style", "knob");
		ui_interface->declare(&fHslider2, "unit", "Hz");
		ui_interface->addHorizontalSlider("Modulating Frequency", &fHslider2, FAUSTFLOAT(1.2e+03), FAUSTFLOAT(9e+02), FAUSTFLOAT(1.7e+03), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Modulations");
		ui_interface->declare(&fHslider5, "acc", "0 0 -30 0 10");
		ui_interface->declare(&fHslider5, "tooltip", "noteOn = 1, noteOff = 0");
		ui_interface->addHorizontalSlider("Play Modulation 0 (ASR Envelope)", &fHslider5, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(1.0));
		ui_interface->declare(&fHslider6, "acc", "0 0 -30 0 5");
		ui_interface->declare(&fHslider6, "tooltip", "noteOn = 1, noteOff = 0");
		ui_interface->addHorizontalSlider("Play Modulation 1 (ASR Envelope)", &fHslider6, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(1.0));
		ui_interface->declare(&fHslider7, "acc", "2 1 -30 0 10");
		ui_interface->declare(&fHslider7, "tooltip", "noteOn = 1, noteOff = 0");
		ui_interface->addHorizontalSlider("Play Modulation 2 (ASR Envelope)", &fHslider7, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(1.0));
		ui_interface->declare(&fHslider3, "acc", "1 0 -10 0 10");
		ui_interface->declare(&fHslider3, "tooltip", "noteOn = 1, noteOff = 0");
		ui_interface->addHorizontalSlider("Play Modulation 3 (ASR Envelope)", &fHslider3, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(1.0));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Reverb");
		ui_interface->declare(&fHslider1, "acc", "1 1 -10 0 10");
		ui_interface->addHorizontalSlider("Reverberation Room Size(InstrReverb)", &fHslider1, FAUSTFLOAT(0.5), FAUSTFLOAT(0.05), FAUSTFLOAT(2.0), FAUSTFLOAT(0.01));
		ui_interface->declare(&fHslider9, "acc", "1 1 -10 0 10");
		ui_interface->addHorizontalSlider("Reverberation Volume(InstrReverb)", &fHslider9, FAUSTFLOAT(0.25), FAUSTFLOAT(0.05), FAUSTFLOAT(1.0), FAUSTFLOAT(0.01));
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* output0_ptr = outputs[0];
		FAUSTFLOAT* output1_ptr = outputs[1];
		double fSlow0 = 0.0010000000000000009 * static_cast<double>(fHslider0);
		double fRec0_tmp[8];
		double* fRec0 = &fRec0_tmp[4];
		double fRec12_tmp[8];
		double* fRec12 = &fRec12_tmp[4];
		double fSlow1 = std::max<double>(0.05, std::min<double>(2.0, static_cast<double>(fHslider1)));
		double fSlow2 = std::exp(-(fConst7 / fSlow1));
		double fSlow3 = mydsp_faustpower2_f(fSlow2);
		double fSlow4 = 1.0 - fConst4 * fSlow3;
		double fSlow5 = 1.0 - fSlow3;
		double fSlow6 = fSlow4 / fSlow5;
		double fSlow7 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow4) / mydsp_faustpower2_f(fSlow5) + -1.0));
		double fSlow8 = fSlow6 - fSlow7;
		double fSlow9 = fSlow2 * (fSlow7 + (1.0 - fSlow6));
		double fSlow10 = std::exp(-(fConst8 / fSlow1)) / fSlow2 + -1.0;
		double fRec11_tmp[8];
		double* fRec11 = &fRec11_tmp[4];
		double fRec15_tmp[8];
		double* fRec15 = &fRec15_tmp[4];
		double fSlow11 = 0.0010000000000000009 * static_cast<double>(fHslider2);
		double fRec17_tmp[8];
		double* fRec17 = &fRec17_tmp[4];
		double fZec0[4];
		double fRec16_tmp[8];
		double* fRec16 = &fRec16_tmp[4];
		double fSlow12 = static_cast<double>(fHslider3);
		int iSlow13 = fSlow12 > 0.0;
		int iSlow14 = iSlow13 > 0;
		double fRec18_tmp[8];
		double* fRec18 = &fRec18_tmp[4];
		int iSlow15 = (fSlow12 == 0.0) > 0;
		double fRec20_tmp[8];
		double* fRec20 = &fRec20_tmp[4];
		double fSlow16 = static_cast<double>(iSlow13);
		double fSlow17 = fConst12 * fSlow12;
		double fRec19_tmp[8];
		double* fRec19 = &fRec19_tmp[4];
		double fSlow18 = 0.0010000000000000009 * static_cast<double>(fHslider4);
		double fRec22_tmp[8];
		double* fRec22 = &fRec22_tmp[4];
		double fZec1[4];
		double fRec21_tmp[8];
		double* fRec21 = &fRec21_tmp[4];
		double fZec2[4];
		double fZec3[4];
		double fZec4[4];
		int iZec5[4];
		double fZec6[4];
		double fZec7[4];
		double fZec8[4];
		double fZec9[4];
		double fZec10[4];
		double fZec11[4];
		double fZec12[4];
		double fZec13[4];
		double fRec27_tmp[8];
		double* fRec27 = &fRec27_tmp[4];
		double fRec26_tmp[8];
		double* fRec26 = &fRec26_tmp[4];
		double fRec25_tmp[8];
		double* fRec25 = &fRec25_tmp[4];
		double fRec24_tmp[8];
		double* fRec24 = &fRec24_tmp[4];
		double fRec23_tmp[8];
		double* fRec23 = &fRec23_tmp[4];
		double fRec14_tmp[8];
		double* fRec14 = &fRec14_tmp[4];
		double fSlow19 = static_cast<double>(fHslider5);
		int iSlow20 = fSlow19 > 0.0;
		int iSlow21 = iSlow20 > 0;
		double fRec29_tmp[8];
		double* fRec29 = &fRec29_tmp[4];
		int iSlow22 = (fSlow19 == 0.0) > 0;
		double fRec31_tmp[8];
		double* fRec31 = &fRec31_tmp[4];
		double fSlow23 = static_cast<double>(iSlow20);
		double fSlow24 = fConst12 * fSlow19;
		double fRec30_tmp[8];
		double* fRec30 = &fRec30_tmp[4];
		double fZec14[4];
		double fZec15[4];
		double fZec16[4];
		double fZec17[4];
		double fZec18[4];
		double fZec19[4];
		double fZec20[4];
		double fZec21[4];
		double fRec37_tmp[8];
		double* fRec37 = &fRec37_tmp[4];
		double fRec36_tmp[8];
		double* fRec36 = &fRec36_tmp[4];
		double fRec35_tmp[8];
		double* fRec35 = &fRec35_tmp[4];
		double fRec34_tmp[8];
		double* fRec34 = &fRec34_tmp[4];
		double fRec33_tmp[8];
		double* fRec33 = &fRec33_tmp[4];
		double fRec32_tmp[8];
		double* fRec32 = &fRec32_tmp[4];
		double fSlow25 = static_cast<double>(fHslider6);
		int iSlow26 = fSlow25 > 0.0;
		int iSlow27 = iSlow26 > 0;
		double fRec38_tmp[8];
		double* fRec38 = &fRec38_tmp[4];
		int iSlow28 = (fSlow25 == 0.0) > 0;
		double fRec40_tmp[8];
		double* fRec40 = &fRec40_tmp[4];
		double fSlow29 = static_cast<double>(iSlow26);
		double fSlow30 = fConst12 * fSlow25;
		double fRec39_tmp[8];
		double* fRec39 = &fRec39_tmp[4];
		double fZec22[4];
		double fYec0_tmp[8];
		double* fYec0 = &fYec0_tmp[4];
		double fZec23[4];
		double fZec24[4];
		double fZec25[4];
		double fZec26[4];
		double fZec27[4];
		double fZec28[4];
		double fZec29[4];
		double fZec30[4];
		double fRec46_tmp[8];
		double* fRec46 = &fRec46_tmp[4];
		double fRec45_tmp[8];
		double* fRec45 = &fRec45_tmp[4];
		double fRec44_tmp[8];
		double* fRec44 = &fRec44_tmp[4];
		double fRec43_tmp[8];
		double* fRec43 = &fRec43_tmp[4];
		double fRec42_tmp[8];
		double* fRec42 = &fRec42_tmp[4];
		double fRec41_tmp[8];
		double* fRec41 = &fRec41_tmp[4];
		double fSlow31 = static_cast<double>(fHslider7);
		int iSlow32 = fSlow31 > 0.0;
		int iSlow33 = iSlow32 > 0;
		double fRec47_tmp[8];
		double* fRec47 = &fRec47_tmp[4];
		int iSlow34 = (fSlow31 == 0.0) > 0;
		double fRec49_tmp[8];
		double* fRec49 = &fRec49_tmp[4];
		double fSlow35 = static_cast<double>(iSlow32);
		double fSlow36 = fConst12 * fSlow31;
		double fRec48_tmp[8];
		double* fRec48 = &fRec48_tmp[4];
		double fZec31[4];
		double fZec32[4];
		double fZec33[4];
		double fZec34[4];
		double fZec35[4];
		double fZec36[4];
		double fZec37[4];
		double fZec38[4];
		double fZec39[4];
		double fRec55_tmp[8];
		double* fRec55 = &fRec55_tmp[4];
		double fRec54_tmp[8];
		double* fRec54 = &fRec54_tmp[4];
		double fRec53_tmp[8];
		double* fRec53 = &fRec53_tmp[4];
		double fRec52_tmp[8];
		double* fRec52 = &fRec52_tmp[4];
		double fRec51_tmp[8];
		double* fRec51 = &fRec51_tmp[4];
		double fRec50_tmp[8];
		double* fRec50 = &fRec50_tmp[4];
		double fYec1_tmp[8];
		double* fYec1 = &fYec1_tmp[4];
		double fRec13_tmp[8];
		double* fRec13 = &fRec13_tmp[4];
		double fSlow37 = 0.0010000000000000009 * mydsp_faustpower2_f(static_cast<double>(fHslider8));
		double fRec56_tmp[8];
		double* fRec56 = &fRec56_tmp[4];
		double fSlow38 = 0.0010000000000000009 * static_cast<double>(fHslider9);
		double fRec57_tmp[8];
		double* fRec57 = &fRec57_tmp[4];
		double fZec40[4];
		double fZec41[4];
		double fZec42[4];
		double fZec43[4];
		double fRec9_tmp[8];
		double* fRec9 = &fRec9_tmp[4];
		double fRec10[4];
		double fRec61_tmp[8];
		double* fRec61 = &fRec61_tmp[4];
		double fSlow39 = std::exp(-(fConst23 / fSlow1));
		double fSlow40 = mydsp_faustpower2_f(fSlow39);
		double fSlow41 = 1.0 - fConst4 * fSlow40;
		double fSlow42 = 1.0 - fSlow40;
		double fSlow43 = fSlow41 / fSlow42;
		double fSlow44 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow41) / mydsp_faustpower2_f(fSlow42) + -1.0));
		double fSlow45 = fSlow43 - fSlow44;
		double fSlow46 = fSlow39 * (fSlow44 + (1.0 - fSlow43));
		double fSlow47 = std::exp(-(fConst24 / fSlow1)) / fSlow39 + -1.0;
		double fRec60_tmp[8];
		double* fRec60 = &fRec60_tmp[4];
		double fZec44[4];
		double fRec58_tmp[8];
		double* fRec58 = &fRec58_tmp[4];
		double fRec59[4];
		double fRec65_tmp[8];
		double* fRec65 = &fRec65_tmp[4];
		double fSlow48 = std::exp(-(fConst30 / fSlow1));
		double fSlow49 = mydsp_faustpower2_f(fSlow48);
		double fSlow50 = 1.0 - fConst4 * fSlow49;
		double fSlow51 = 1.0 - fSlow49;
		double fSlow52 = fSlow50 / fSlow51;
		double fSlow53 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow50) / mydsp_faustpower2_f(fSlow51) + -1.0));
		double fSlow54 = fSlow52 - fSlow53;
		double fSlow55 = fSlow48 * (fSlow53 + (1.0 - fSlow52));
		double fSlow56 = std::exp(-(fConst31 / fSlow1)) / fSlow48 + -1.0;
		double fRec64_tmp[8];
		double* fRec64 = &fRec64_tmp[4];
		double fRec62_tmp[8];
		double* fRec62 = &fRec62_tmp[4];
		double fRec63[4];
		double fRec69_tmp[8];
		double* fRec69 = &fRec69_tmp[4];
		double fSlow57 = std::exp(-(fConst37 / fSlow1));
		double fSlow58 = mydsp_faustpower2_f(fSlow57);
		double fSlow59 = 1.0 - fConst4 * fSlow58;
		double fSlow60 = 1.0 - fSlow58;
		double fSlow61 = fSlow59 / fSlow60;
		double fSlow62 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow59) / mydsp_faustpower2_f(fSlow60) + -1.0));
		double fSlow63 = fSlow61 - fSlow62;
		double fSlow64 = fSlow57 * (fSlow62 + (1.0 - fSlow61));
		double fSlow65 = std::exp(-(fConst38 / fSlow1)) / fSlow57 + -1.0;
		double fRec68_tmp[8];
		double* fRec68 = &fRec68_tmp[4];
		double fRec66_tmp[8];
		double* fRec66 = &fRec66_tmp[4];
		double fRec67[4];
		double fRec73_tmp[8];
		double* fRec73 = &fRec73_tmp[4];
		double fSlow66 = std::exp(-(fConst44 / fSlow1));
		double fSlow67 = mydsp_faustpower2_f(fSlow66);
		double fSlow68 = 1.0 - fConst4 * fSlow67;
		double fSlow69 = 1.0 - fSlow67;
		double fSlow70 = fSlow68 / fSlow69;
		double fSlow71 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow68) / mydsp_faustpower2_f(fSlow69) + -1.0));
		double fSlow72 = fSlow70 - fSlow71;
		double fSlow73 = fSlow66 * (fSlow71 + (1.0 - fSlow70));
		double fSlow74 = std::exp(-(fConst45 / fSlow1)) / fSlow66 + -1.0;
		double fRec72_tmp[8];
		double* fRec72 = &fRec72_tmp[4];
		double fRec70_tmp[8];
		double* fRec70 = &fRec70_tmp[4];
		double fRec71[4];
		double fRec77_tmp[8];
		double* fRec77 = &fRec77_tmp[4];
		double fSlow75 = std::exp(-(fConst51 / fSlow1));
		double fSlow76 = mydsp_faustpower2_f(fSlow75);
		double fSlow77 = 1.0 - fConst4 * fSlow76;
		double fSlow78 = 1.0 - fSlow76;
		double fSlow79 = fSlow77 / fSlow78;
		double fSlow80 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow77) / mydsp_faustpower2_f(fSlow78) + -1.0));
		double fSlow81 = fSlow79 - fSlow80;
		double fSlow82 = fSlow75 * (fSlow80 + (1.0 - fSlow79));
		double fSlow83 = std::exp(-(fConst52 / fSlow1)) / fSlow75 + -1.0;
		double fRec76_tmp[8];
		double* fRec76 = &fRec76_tmp[4];
		double fRec74_tmp[8];
		double* fRec74 = &fRec74_tmp[4];
		double fRec75[4];
		double fRec81_tmp[8];
		double* fRec81 = &fRec81_tmp[4];
		double fSlow84 = std::exp(-(fConst58 / fSlow1));
		double fSlow85 = mydsp_faustpower2_f(fSlow84);
		double fSlow86 = 1.0 - fConst4 * fSlow85;
		double fSlow87 = 1.0 - fSlow85;
		double fSlow88 = fSlow86 / fSlow87;
		double fSlow89 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow86) / mydsp_faustpower2_f(fSlow87) + -1.0));
		double fSlow90 = fSlow88 - fSlow89;
		double fSlow91 = fSlow84 * (fSlow89 + (1.0 - fSlow88));
		double fSlow92 = std::exp(-(fConst59 / fSlow1)) / fSlow84 + -1.0;
		double fRec80_tmp[8];
		double* fRec80 = &fRec80_tmp[4];
		double fRec78_tmp[8];
		double* fRec78 = &fRec78_tmp[4];
		double fRec79[4];
		double fRec85_tmp[8];
		double* fRec85 = &fRec85_tmp[4];
		double fSlow93 = std::exp(-(fConst65 / fSlow1));
		double fSlow94 = mydsp_faustpower2_f(fSlow93);
		double fSlow95 = 1.0 - fConst4 * fSlow94;
		double fSlow96 = 1.0 - fSlow94;
		double fSlow97 = fSlow95 / fSlow96;
		double fSlow98 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow95) / mydsp_faustpower2_f(fSlow96) + -1.0));
		double fSlow99 = fSlow97 - fSlow98;
		double fSlow100 = fSlow93 * (fSlow98 + (1.0 - fSlow97));
		double fSlow101 = std::exp(-(fConst66 / fSlow1)) / fSlow93 + -1.0;
		double fRec84_tmp[8];
		double* fRec84 = &fRec84_tmp[4];
		double fRec82_tmp[8];
		double* fRec82 = &fRec82_tmp[4];
		double fRec83[4];
		double fZec45[4];
		double fZec46[4];
		double fRec1_tmp[8];
		double* fRec1 = &fRec1_tmp[4];
		double fRec2_tmp[8];
		double* fRec2 = &fRec2_tmp[4];
		double fZec47[4];
		double fRec3_tmp[8];
		double* fRec3 = &fRec3_tmp[4];
		double fRec4_tmp[8];
		double* fRec4 = &fRec4_tmp[4];
		double fZec48[4];
		double fZec49[4];
		double fRec5_tmp[8];
		double* fRec5 = &fRec5_tmp[4];
		double fRec6_tmp[8];
		double* fRec6 = &fRec6_tmp[4];
		double fZec50[4];
		double fZec51[4];
		double fRec7_tmp[8];
		double* fRec7 = &fRec7_tmp[4];
		double fRec8_tmp[8];
		double* fRec8 = &fRec8_tmp[4];
		double fZec52[4];
		double fZec53[4];
		int vindex = 0;
		/* Main loop */
		for (vindex = 0; vindex <= (faust_wrap_sub(count, 4)); vindex = faust_wrap_add(vindex, 4)) {
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
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec15_tmp[j6] = fRec15_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec15[i] = 0.999 * fRec15[faust_wrap_sub(i, 1)] + 0.0008000000000000008;
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec15_perm[j7] = fRec15_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Recursive loop 2 */
			/* Pre code */
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fRec17_tmp[j8] = fRec17_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec17[i] = fSlow11 + 0.999 * fRec17[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fRec17_perm[j9] = fRec17_tmp[faust_wrap_add(vsize, j9)];
			}
			/* Recursive loop 3 */
			/* Pre code */
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				fRec16_tmp[j10] = fRec16_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec0[i] = fRec16[faust_wrap_sub(i, 1)] + fConst9 * fRec17[i];
				fRec16[i] = fZec0[i] - std::floor(fZec0[i]);
			}
			/* Post code */
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				fRec16_perm[j11] = fRec16_tmp[faust_wrap_add(vsize, j11)];
			}
			/* Recursive loop 4 */
			/* Pre code */
			for (int j12 = 0; j12 < 4; j12 = faust_wrap_add(j12, 1)) {
				fRec18_tmp[j12] = fRec18_perm[j12];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec18[i] = ((iSlow14) ? 0.0 : std::min<double>(fConst10, fRec18[faust_wrap_sub(i, 1)] + 1.0));
			}
			/* Post code */
			for (int j13 = 0; j13 < 4; j13 = faust_wrap_add(j13, 1)) {
				fRec18_perm[j13] = fRec18_tmp[faust_wrap_add(vsize, j13)];
			}
			/* Recursive loop 5 */
			/* Pre code */
			for (int j14 = 0; j14 < 4; j14 = faust_wrap_add(j14, 1)) {
				fRec20_tmp[j14] = fRec20_perm[j14];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec20[i] = ((iSlow15) ? 0.0 : std::min<double>(fConst11, fRec20[faust_wrap_sub(i, 1)] + 1.0));
			}
			/* Post code */
			for (int j15 = 0; j15 < 4; j15 = faust_wrap_add(j15, 1)) {
				fRec20_perm[j15] = fRec20_tmp[faust_wrap_add(vsize, j15)];
			}
			/* Recursive loop 6 */
			/* Pre code */
			for (int j16 = 0; j16 < 4; j16 = faust_wrap_add(j16, 1)) {
				fRec19_tmp[j16] = fRec19_perm[j16];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec19[i] = ((iSlow13) ? fSlow16 * ((fRec20[i] < 0.0) ? 0.0 : ((fRec20[i] < fConst11) ? fSlow17 * fRec20[i] : fSlow12)) : fRec19[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j17 = 0; j17 < 4; j17 = faust_wrap_add(j17, 1)) {
				fRec19_perm[j17] = fRec19_tmp[faust_wrap_add(vsize, j17)];
			}
			/* Recursive loop 7 */
			/* Pre code */
			for (int j18 = 0; j18 < 4; j18 = faust_wrap_add(j18, 1)) {
				fRec22_tmp[j18] = fRec22_perm[j18];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec22[i] = fSlow18 + 0.999 * fRec22[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j19 = 0; j19 < 4; j19 = faust_wrap_add(j19, 1)) {
				fRec22_perm[j19] = fRec22_tmp[faust_wrap_add(vsize, j19)];
			}
			/* Recursive loop 8 */
			/* Pre code */
			for (int j20 = 0; j20 < 4; j20 = faust_wrap_add(j20, 1)) {
				fRec21_tmp[j20] = fRec21_perm[j20];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec1[i] = fRec21[faust_wrap_sub(i, 1)] + fConst9 * fRec22[i];
				fRec21[i] = fZec1[i] - std::floor(fZec1[i]);
			}
			/* Post code */
			for (int j21 = 0; j21 < 4; j21 = faust_wrap_add(j21, 1)) {
				fRec21_perm[j21] = fRec21_tmp[faust_wrap_add(vsize, j21)];
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec2[i] = 3.141592653589793 * fRec15[i] * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0 * fRec16[i]), 65535))] * ((fRec18[i] < 0.0) ? fRec19[i] : ((fRec18[i] < fConst10) ? fRec19[i] * (1.0 - fConst13 * fRec18[i]) : 0.0));
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec3[i] = std::cos(fZec2[i]);
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec4[i] = 65536.0 * fRec21[i];
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec5[i] = static_cast<int>(fZec4[i]);
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec6[i] = ftbl1mydspSIG0[std::max<int>(0, std::min<int>(iZec5[i], 65536))];
			}
			/* Vectorizable loop 14 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec7[i] = fZec6[i] + (fZec4[i] - std::floor(fZec4[i])) * (ftbl1mydspSIG0[std::max<int>(0, std::min<int>(faust_wrap_add(iZec5[i], 1), 65536))] - fZec6[i]);
			}
			/* Vectorizable loop 15 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec8[i] = std::sin(fZec2[i]);
			}
			/* Recursive loop 16 */
			/* Pre code */
			for (int j22 = 0; j22 < 4; j22 = faust_wrap_add(j22, 1)) {
				fRec27_tmp[j22] = fRec27_perm[j22];
			}
			for (int j24 = 0; j24 < 4; j24 = faust_wrap_add(j24, 1)) {
				fRec26_tmp[j24] = fRec26_perm[j24];
			}
			for (int j26 = 0; j26 < 4; j26 = faust_wrap_add(j26, 1)) {
				fRec25_tmp[j26] = fRec25_perm[j26];
			}
			for (int j28 = 0; j28 < 4; j28 = faust_wrap_add(j28, 1)) {
				fRec24_tmp[j28] = fRec24_perm[j28];
			}
			for (int j30 = 0; j30 < 4; j30 = faust_wrap_add(j30, 1)) {
				fRec23_tmp[j30] = fRec23_perm[j30];
			}
			for (int j32 = 0; j32 < 4; j32 = faust_wrap_add(j32, 1)) {
				fRec14_tmp[j32] = fRec14_perm[j32];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec9[i] = fZec7[i] * fZec3[i] - fZec8[i] * fRec14[faust_wrap_sub(i, 1)];
				fZec10[i] = fZec3[i] * fZec9[i] - fZec8[i] * fRec23[faust_wrap_sub(i, 1)];
				fZec11[i] = fZec3[i] * fZec10[i] - fZec8[i] * fRec24[faust_wrap_sub(i, 1)];
				fZec12[i] = fZec3[i] * fZec11[i] - fZec8[i] * fRec25[faust_wrap_sub(i, 1)];
				fZec13[i] = fZec3[i] * fZec12[i] - fZec8[i] * fRec26[faust_wrap_sub(i, 1)];
				fRec27[i] = fZec3[i] * fZec13[i] - fZec8[i] * fRec27[faust_wrap_sub(i, 1)];
				fRec26[i] = fZec8[i] * fZec13[i] + fZec3[i] * fRec27[faust_wrap_sub(i, 1)];
				fRec25[i] = fZec8[i] * fZec12[i] + fZec3[i] * fRec26[faust_wrap_sub(i, 1)];
				fRec24[i] = fZec8[i] * fZec11[i] + fZec3[i] * fRec25[faust_wrap_sub(i, 1)];
				fRec23[i] = fZec8[i] * fZec10[i] + fZec3[i] * fRec24[faust_wrap_sub(i, 1)];
				fRec14[i] = fZec8[i] * fZec9[i] + fZec3[i] * fRec23[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j23 = 0; j23 < 4; j23 = faust_wrap_add(j23, 1)) {
				fRec27_perm[j23] = fRec27_tmp[faust_wrap_add(vsize, j23)];
			}
			for (int j25 = 0; j25 < 4; j25 = faust_wrap_add(j25, 1)) {
				fRec26_perm[j25] = fRec26_tmp[faust_wrap_add(vsize, j25)];
			}
			for (int j27 = 0; j27 < 4; j27 = faust_wrap_add(j27, 1)) {
				fRec25_perm[j27] = fRec25_tmp[faust_wrap_add(vsize, j27)];
			}
			for (int j29 = 0; j29 < 4; j29 = faust_wrap_add(j29, 1)) {
				fRec24_perm[j29] = fRec24_tmp[faust_wrap_add(vsize, j29)];
			}
			for (int j31 = 0; j31 < 4; j31 = faust_wrap_add(j31, 1)) {
				fRec23_perm[j31] = fRec23_tmp[faust_wrap_add(vsize, j31)];
			}
			for (int j33 = 0; j33 < 4; j33 = faust_wrap_add(j33, 1)) {
				fRec14_perm[j33] = fRec14_tmp[faust_wrap_add(vsize, j33)];
			}
			/* Recursive loop 17 */
			/* Pre code */
			for (int j34 = 0; j34 < 4; j34 = faust_wrap_add(j34, 1)) {
				fRec29_tmp[j34] = fRec29_perm[j34];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec29[i] = ((iSlow21) ? 0.0 : std::min<double>(fConst10, fRec29[faust_wrap_sub(i, 1)] + 1.0));
			}
			/* Post code */
			for (int j35 = 0; j35 < 4; j35 = faust_wrap_add(j35, 1)) {
				fRec29_perm[j35] = fRec29_tmp[faust_wrap_add(vsize, j35)];
			}
			/* Recursive loop 18 */
			/* Pre code */
			for (int j36 = 0; j36 < 4; j36 = faust_wrap_add(j36, 1)) {
				fRec31_tmp[j36] = fRec31_perm[j36];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec31[i] = ((iSlow22) ? 0.0 : std::min<double>(fConst11, fRec31[faust_wrap_sub(i, 1)] + 1.0));
			}
			/* Post code */
			for (int j37 = 0; j37 < 4; j37 = faust_wrap_add(j37, 1)) {
				fRec31_perm[j37] = fRec31_tmp[faust_wrap_add(vsize, j37)];
			}
			/* Recursive loop 19 */
			/* Pre code */
			for (int j38 = 0; j38 < 4; j38 = faust_wrap_add(j38, 1)) {
				fRec30_tmp[j38] = fRec30_perm[j38];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec30[i] = ((iSlow20) ? fSlow23 * ((fRec31[i] < 0.0) ? 0.0 : ((fRec31[i] < fConst11) ? fSlow24 * fRec31[i] : fSlow19)) : fRec30[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j39 = 0; j39 < 4; j39 = faust_wrap_add(j39, 1)) {
				fRec30_perm[j39] = fRec30_tmp[faust_wrap_add(vsize, j39)];
			}
			/* Vectorizable loop 20 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec14[i] = 3.141592653589793 * fRec15[i] * fZec7[i] * ((fRec29[i] < 0.0) ? fRec30[i] : ((fRec29[i] < fConst10) ? fRec30[i] * (1.0 - fConst13 * fRec29[i]) : 0.0));
			}
			/* Vectorizable loop 21 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec15[i] = std::cos(fZec14[i]);
			}
			/* Vectorizable loop 22 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec16[i] = std::sin(fZec14[i]);
			}
			/* Recursive loop 23 */
			/* Pre code */
			for (int j40 = 0; j40 < 4; j40 = faust_wrap_add(j40, 1)) {
				fRec37_tmp[j40] = fRec37_perm[j40];
			}
			for (int j42 = 0; j42 < 4; j42 = faust_wrap_add(j42, 1)) {
				fRec36_tmp[j42] = fRec36_perm[j42];
			}
			for (int j44 = 0; j44 < 4; j44 = faust_wrap_add(j44, 1)) {
				fRec35_tmp[j44] = fRec35_perm[j44];
			}
			for (int j46 = 0; j46 < 4; j46 = faust_wrap_add(j46, 1)) {
				fRec34_tmp[j46] = fRec34_perm[j46];
			}
			for (int j48 = 0; j48 < 4; j48 = faust_wrap_add(j48, 1)) {
				fRec33_tmp[j48] = fRec33_perm[j48];
			}
			for (int j50 = 0; j50 < 4; j50 = faust_wrap_add(j50, 1)) {
				fRec32_tmp[j50] = fRec32_perm[j50];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec17[i] = fZec7[i] * fZec15[i] - fZec16[i] * fRec32[faust_wrap_sub(i, 1)];
				fZec18[i] = fZec15[i] * fZec17[i] - fZec16[i] * fRec33[faust_wrap_sub(i, 1)];
				fZec19[i] = fZec15[i] * fZec18[i] - fZec16[i] * fRec34[faust_wrap_sub(i, 1)];
				fZec20[i] = fZec15[i] * fZec19[i] - fZec16[i] * fRec35[faust_wrap_sub(i, 1)];
				fZec21[i] = fZec15[i] * fZec20[i] - fZec16[i] * fRec36[faust_wrap_sub(i, 1)];
				fRec37[i] = fZec15[i] * fZec21[i] - fZec16[i] * fRec37[faust_wrap_sub(i, 1)];
				fRec36[i] = fZec16[i] * fZec21[i] + fZec15[i] * fRec37[faust_wrap_sub(i, 1)];
				fRec35[i] = fZec16[i] * fZec20[i] + fZec15[i] * fRec36[faust_wrap_sub(i, 1)];
				fRec34[i] = fZec16[i] * fZec19[i] + fZec15[i] * fRec35[faust_wrap_sub(i, 1)];
				fRec33[i] = fZec16[i] * fZec18[i] + fZec15[i] * fRec34[faust_wrap_sub(i, 1)];
				fRec32[i] = fZec16[i] * fZec17[i] + fZec15[i] * fRec33[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j41 = 0; j41 < 4; j41 = faust_wrap_add(j41, 1)) {
				fRec37_perm[j41] = fRec37_tmp[faust_wrap_add(vsize, j41)];
			}
			for (int j43 = 0; j43 < 4; j43 = faust_wrap_add(j43, 1)) {
				fRec36_perm[j43] = fRec36_tmp[faust_wrap_add(vsize, j43)];
			}
			for (int j45 = 0; j45 < 4; j45 = faust_wrap_add(j45, 1)) {
				fRec35_perm[j45] = fRec35_tmp[faust_wrap_add(vsize, j45)];
			}
			for (int j47 = 0; j47 < 4; j47 = faust_wrap_add(j47, 1)) {
				fRec34_perm[j47] = fRec34_tmp[faust_wrap_add(vsize, j47)];
			}
			for (int j49 = 0; j49 < 4; j49 = faust_wrap_add(j49, 1)) {
				fRec33_perm[j49] = fRec33_tmp[faust_wrap_add(vsize, j49)];
			}
			for (int j51 = 0; j51 < 4; j51 = faust_wrap_add(j51, 1)) {
				fRec32_perm[j51] = fRec32_tmp[faust_wrap_add(vsize, j51)];
			}
			/* Recursive loop 24 */
			/* Pre code */
			for (int j52 = 0; j52 < 4; j52 = faust_wrap_add(j52, 1)) {
				fRec38_tmp[j52] = fRec38_perm[j52];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec38[i] = ((iSlow27) ? 0.0 : std::min<double>(fConst10, fRec38[faust_wrap_sub(i, 1)] + 1.0));
			}
			/* Post code */
			for (int j53 = 0; j53 < 4; j53 = faust_wrap_add(j53, 1)) {
				fRec38_perm[j53] = fRec38_tmp[faust_wrap_add(vsize, j53)];
			}
			/* Recursive loop 25 */
			/* Pre code */
			for (int j54 = 0; j54 < 4; j54 = faust_wrap_add(j54, 1)) {
				fRec40_tmp[j54] = fRec40_perm[j54];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec40[i] = ((iSlow28) ? 0.0 : std::min<double>(fConst11, fRec40[faust_wrap_sub(i, 1)] + 1.0));
			}
			/* Post code */
			for (int j55 = 0; j55 < 4; j55 = faust_wrap_add(j55, 1)) {
				fRec40_perm[j55] = fRec40_tmp[faust_wrap_add(vsize, j55)];
			}
			/* Recursive loop 26 */
			/* Pre code */
			for (int j56 = 0; j56 < 4; j56 = faust_wrap_add(j56, 1)) {
				fRec39_tmp[j56] = fRec39_perm[j56];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec39[i] = ((iSlow26) ? fSlow29 * ((fRec40[i] < 0.0) ? 0.0 : ((fRec40[i] < fConst11) ? fSlow30 * fRec40[i] : fSlow25)) : fRec39[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j57 = 0; j57 < 4; j57 = faust_wrap_add(j57, 1)) {
				fRec39_perm[j57] = fRec39_tmp[faust_wrap_add(vsize, j57)];
			}
			/* Vectorizable loop 27 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec22[i] = 1.0 - fRec15[i];
			}
			/* Vectorizable loop 28 */
			/* Pre code */
			for (int j58 = 0; j58 < 4; j58 = faust_wrap_add(j58, 1)) {
				fYec0_tmp[j58] = fYec0_perm[j58];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec0[i] = fRec15[i] * (fZec7[i] * fZec16[i] + fRec32[faust_wrap_sub(i, 1)] * fZec15[i]) + fZec22[i] * fZec7[i];
			}
			/* Post code */
			for (int j59 = 0; j59 < 4; j59 = faust_wrap_add(j59, 1)) {
				fYec0_perm[j59] = fYec0_tmp[faust_wrap_add(vsize, j59)];
			}
			/* Vectorizable loop 29 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec23[i] = 1.5707963267948966 * fRec15[i] * ((fRec38[i] < 0.0) ? fRec39[i] : ((fRec38[i] < fConst10) ? fRec39[i] * (1.0 - fConst13 * fRec38[i]) : 0.0)) * (fYec0[i] + fYec0[faust_wrap_sub(i, 1)]);
			}
			/* Vectorizable loop 30 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec24[i] = std::cos(fZec23[i]);
			}
			/* Vectorizable loop 31 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec25[i] = std::sin(fZec23[i]);
			}
			/* Recursive loop 32 */
			/* Pre code */
			for (int j60 = 0; j60 < 4; j60 = faust_wrap_add(j60, 1)) {
				fRec46_tmp[j60] = fRec46_perm[j60];
			}
			for (int j62 = 0; j62 < 4; j62 = faust_wrap_add(j62, 1)) {
				fRec45_tmp[j62] = fRec45_perm[j62];
			}
			for (int j64 = 0; j64 < 4; j64 = faust_wrap_add(j64, 1)) {
				fRec44_tmp[j64] = fRec44_perm[j64];
			}
			for (int j66 = 0; j66 < 4; j66 = faust_wrap_add(j66, 1)) {
				fRec43_tmp[j66] = fRec43_perm[j66];
			}
			for (int j68 = 0; j68 < 4; j68 = faust_wrap_add(j68, 1)) {
				fRec42_tmp[j68] = fRec42_perm[j68];
			}
			for (int j70 = 0; j70 < 4; j70 = faust_wrap_add(j70, 1)) {
				fRec41_tmp[j70] = fRec41_perm[j70];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec26[i] = fYec0[i] * fZec24[i] - fZec25[i] * fRec41[faust_wrap_sub(i, 1)];
				fZec27[i] = fZec24[i] * fZec26[i] - fZec25[i] * fRec42[faust_wrap_sub(i, 1)];
				fZec28[i] = fZec24[i] * fZec27[i] - fZec25[i] * fRec43[faust_wrap_sub(i, 1)];
				fZec29[i] = fZec24[i] * fZec28[i] - fZec25[i] * fRec44[faust_wrap_sub(i, 1)];
				fZec30[i] = fZec24[i] * fZec29[i] - fZec25[i] * fRec45[faust_wrap_sub(i, 1)];
				fRec46[i] = fZec24[i] * fZec30[i] - fZec25[i] * fRec46[faust_wrap_sub(i, 1)];
				fRec45[i] = fZec25[i] * fZec30[i] + fZec24[i] * fRec46[faust_wrap_sub(i, 1)];
				fRec44[i] = fZec25[i] * fZec29[i] + fZec24[i] * fRec45[faust_wrap_sub(i, 1)];
				fRec43[i] = fZec25[i] * fZec28[i] + fZec24[i] * fRec44[faust_wrap_sub(i, 1)];
				fRec42[i] = fZec25[i] * fZec27[i] + fZec24[i] * fRec43[faust_wrap_sub(i, 1)];
				fRec41[i] = fZec25[i] * fZec26[i] + fZec24[i] * fRec42[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j61 = 0; j61 < 4; j61 = faust_wrap_add(j61, 1)) {
				fRec46_perm[j61] = fRec46_tmp[faust_wrap_add(vsize, j61)];
			}
			for (int j63 = 0; j63 < 4; j63 = faust_wrap_add(j63, 1)) {
				fRec45_perm[j63] = fRec45_tmp[faust_wrap_add(vsize, j63)];
			}
			for (int j65 = 0; j65 < 4; j65 = faust_wrap_add(j65, 1)) {
				fRec44_perm[j65] = fRec44_tmp[faust_wrap_add(vsize, j65)];
			}
			for (int j67 = 0; j67 < 4; j67 = faust_wrap_add(j67, 1)) {
				fRec43_perm[j67] = fRec43_tmp[faust_wrap_add(vsize, j67)];
			}
			for (int j69 = 0; j69 < 4; j69 = faust_wrap_add(j69, 1)) {
				fRec42_perm[j69] = fRec42_tmp[faust_wrap_add(vsize, j69)];
			}
			for (int j71 = 0; j71 < 4; j71 = faust_wrap_add(j71, 1)) {
				fRec41_perm[j71] = fRec41_tmp[faust_wrap_add(vsize, j71)];
			}
			/* Recursive loop 33 */
			/* Pre code */
			for (int j72 = 0; j72 < 4; j72 = faust_wrap_add(j72, 1)) {
				fRec47_tmp[j72] = fRec47_perm[j72];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec47[i] = ((iSlow33) ? 0.0 : std::min<double>(fConst10, fRec47[faust_wrap_sub(i, 1)] + 1.0));
			}
			/* Post code */
			for (int j73 = 0; j73 < 4; j73 = faust_wrap_add(j73, 1)) {
				fRec47_perm[j73] = fRec47_tmp[faust_wrap_add(vsize, j73)];
			}
			/* Recursive loop 34 */
			/* Pre code */
			for (int j74 = 0; j74 < 4; j74 = faust_wrap_add(j74, 1)) {
				fRec49_tmp[j74] = fRec49_perm[j74];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec49[i] = ((iSlow34) ? 0.0 : std::min<double>(fConst11, fRec49[faust_wrap_sub(i, 1)] + 1.0));
			}
			/* Post code */
			for (int j75 = 0; j75 < 4; j75 = faust_wrap_add(j75, 1)) {
				fRec49_perm[j75] = fRec49_tmp[faust_wrap_add(vsize, j75)];
			}
			/* Recursive loop 35 */
			/* Pre code */
			for (int j76 = 0; j76 < 4; j76 = faust_wrap_add(j76, 1)) {
				fRec48_tmp[j76] = fRec48_perm[j76];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec48[i] = ((iSlow32) ? fSlow35 * ((fRec49[i] < 0.0) ? 0.0 : ((fRec49[i] < fConst11) ? fSlow36 * fRec49[i] : fSlow31)) : fRec48[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j77 = 0; j77 < 4; j77 = faust_wrap_add(j77, 1)) {
				fRec48_perm[j77] = fRec48_tmp[faust_wrap_add(vsize, j77)];
			}
			/* Vectorizable loop 36 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec31[i] = fRec15[i] * (fYec0[i] * fZec25[i] + fRec41[faust_wrap_sub(i, 1)] * fZec24[i]) + fZec22[i] * fYec0[i];
			}
			/* Vectorizable loop 37 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec32[i] = 3.141592653589793 * fRec15[i] * mydsp_faustpower2_f(fZec31[i]) * ((fRec47[i] < 0.0) ? fRec48[i] : ((fRec47[i] < fConst10) ? fRec48[i] * (1.0 - fConst13 * fRec47[i]) : 0.0));
			}
			/* Vectorizable loop 38 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec33[i] = std::cos(fZec32[i]);
			}
			/* Vectorizable loop 39 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec34[i] = std::sin(fZec32[i]);
			}
			/* Recursive loop 40 */
			/* Pre code */
			for (int j78 = 0; j78 < 4; j78 = faust_wrap_add(j78, 1)) {
				fRec55_tmp[j78] = fRec55_perm[j78];
			}
			for (int j80 = 0; j80 < 4; j80 = faust_wrap_add(j80, 1)) {
				fRec54_tmp[j80] = fRec54_perm[j80];
			}
			for (int j82 = 0; j82 < 4; j82 = faust_wrap_add(j82, 1)) {
				fRec53_tmp[j82] = fRec53_perm[j82];
			}
			for (int j84 = 0; j84 < 4; j84 = faust_wrap_add(j84, 1)) {
				fRec52_tmp[j84] = fRec52_perm[j84];
			}
			for (int j86 = 0; j86 < 4; j86 = faust_wrap_add(j86, 1)) {
				fRec51_tmp[j86] = fRec51_perm[j86];
			}
			for (int j88 = 0; j88 < 4; j88 = faust_wrap_add(j88, 1)) {
				fRec50_tmp[j88] = fRec50_perm[j88];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec35[i] = fZec31[i] * fZec33[i] - fZec34[i] * fRec50[faust_wrap_sub(i, 1)];
				fZec36[i] = fZec33[i] * fZec35[i] - fZec34[i] * fRec51[faust_wrap_sub(i, 1)];
				fZec37[i] = fZec33[i] * fZec36[i] - fZec34[i] * fRec52[faust_wrap_sub(i, 1)];
				fZec38[i] = fZec33[i] * fZec37[i] - fZec34[i] * fRec53[faust_wrap_sub(i, 1)];
				fZec39[i] = fZec33[i] * fZec38[i] - fZec34[i] * fRec54[faust_wrap_sub(i, 1)];
				fRec55[i] = fZec33[i] * fZec39[i] - fZec34[i] * fRec55[faust_wrap_sub(i, 1)];
				fRec54[i] = fZec34[i] * fZec39[i] + fZec33[i] * fRec55[faust_wrap_sub(i, 1)];
				fRec53[i] = fZec34[i] * fZec38[i] + fZec33[i] * fRec54[faust_wrap_sub(i, 1)];
				fRec52[i] = fZec34[i] * fZec37[i] + fZec33[i] * fRec53[faust_wrap_sub(i, 1)];
				fRec51[i] = fZec34[i] * fZec36[i] + fZec33[i] * fRec52[faust_wrap_sub(i, 1)];
				fRec50[i] = fZec34[i] * fZec35[i] + fZec33[i] * fRec51[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j79 = 0; j79 < 4; j79 = faust_wrap_add(j79, 1)) {
				fRec55_perm[j79] = fRec55_tmp[faust_wrap_add(vsize, j79)];
			}
			for (int j81 = 0; j81 < 4; j81 = faust_wrap_add(j81, 1)) {
				fRec54_perm[j81] = fRec54_tmp[faust_wrap_add(vsize, j81)];
			}
			for (int j83 = 0; j83 < 4; j83 = faust_wrap_add(j83, 1)) {
				fRec53_perm[j83] = fRec53_tmp[faust_wrap_add(vsize, j83)];
			}
			for (int j85 = 0; j85 < 4; j85 = faust_wrap_add(j85, 1)) {
				fRec52_perm[j85] = fRec52_tmp[faust_wrap_add(vsize, j85)];
			}
			for (int j87 = 0; j87 < 4; j87 = faust_wrap_add(j87, 1)) {
				fRec51_perm[j87] = fRec51_tmp[faust_wrap_add(vsize, j87)];
			}
			for (int j89 = 0; j89 < 4; j89 = faust_wrap_add(j89, 1)) {
				fRec50_perm[j89] = fRec50_tmp[faust_wrap_add(vsize, j89)];
			}
			/* Vectorizable loop 41 */
			/* Pre code */
			for (int j90 = 0; j90 < 4; j90 = faust_wrap_add(j90, 1)) {
				fYec1_tmp[j90] = fYec1_perm[j90];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec1[i] = fRec14[faust_wrap_sub(i, 1)] * fZec3[i] + fRec15[i] * (fZec31[i] * fZec34[i] + fRec50[faust_wrap_sub(i, 1)] * fZec33[i]) + fZec22[i] * fZec31[i] + fZec7[i] * fZec8[i];
			}
			/* Post code */
			for (int j91 = 0; j91 < 4; j91 = faust_wrap_add(j91, 1)) {
				fYec1_perm[j91] = fYec1_tmp[faust_wrap_add(vsize, j91)];
			}
			/* Recursive loop 42 */
			/* Pre code */
			for (int j92 = 0; j92 < 4; j92 = faust_wrap_add(j92, 1)) {
				fRec13_tmp[j92] = fRec13_perm[j92];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec13[i] = -(fConst15 * (fConst16 * fRec13[faust_wrap_sub(i, 1)] - (fYec1[i] + fYec1[faust_wrap_sub(i, 1)])));
			}
			/* Post code */
			for (int j93 = 0; j93 < 4; j93 = faust_wrap_add(j93, 1)) {
				fRec13_perm[j93] = fRec13_tmp[faust_wrap_add(vsize, j93)];
			}
			/* Recursive loop 43 */
			/* Pre code */
			for (int j94 = 0; j94 < 4; j94 = faust_wrap_add(j94, 1)) {
				fRec56_tmp[j94] = fRec56_perm[j94];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec56[i] = fSlow37 + 0.999 * fRec56[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j95 = 0; j95 < 4; j95 = faust_wrap_add(j95, 1)) {
				fRec56_perm[j95] = fRec56_tmp[faust_wrap_add(vsize, j95)];
			}
			/* Recursive loop 44 */
			/* Pre code */
			for (int j96 = 0; j96 < 4; j96 = faust_wrap_add(j96, 1)) {
				fRec57_tmp[j96] = fRec57_perm[j96];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec57[i] = fSlow38 + 0.999 * fRec57[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j97 = 0; j97 < 4; j97 = faust_wrap_add(j97, 1)) {
				fRec57_perm[j97] = fRec57_tmp[faust_wrap_add(vsize, j97)];
			}
			/* Vectorizable loop 45 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec41[i] = fRec13[i] * fRec56[i];
			}
			/* Vectorizable loop 46 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec42[i] = std::max<double>(0.05, std::min<double>(1.0, fRec57[i]));
			}
			/* Vectorizable loop 47 */
			/* Pre code */
			fYec3_idx = (faust_wrap_add(fYec3_idx, fYec3_idx_save)) & 4095;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec3[(faust_wrap_add(i, fYec3_idx)) & 4095] = fZec41[i] * fZec42[i];
			}
			/* Post code */
			fYec3_idx_save = vsize;
			/* Vectorizable loop 48 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec43[i] = 0.18 * fYec3[(faust_wrap_sub(faust_wrap_add(i, fYec3_idx), iConst19)) & 4095];
			}
			/* Recursive loop 49 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fRec12_tmp[j2] = fRec12_perm[j2];
			}
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				fRec11_tmp[j4] = fRec11_perm[j4];
			}
			fYec2_idx = (faust_wrap_add(fYec2_idx, fYec2_idx_save)) & 32767;
			fYec4_idx = (faust_wrap_add(fYec4_idx, fYec4_idx_save)) & 2047;
			for (int j98 = 0; j98 < 4; j98 = faust_wrap_add(j98, 1)) {
				fRec9_tmp[j98] = fRec9_perm[j98];
			}
			for (int j100 = 0; j100 < 4; j100 = faust_wrap_add(j100, 1)) {
				fRec61_tmp[j100] = fRec61_perm[j100];
			}
			for (int j102 = 0; j102 < 4; j102 = faust_wrap_add(j102, 1)) {
				fRec60_tmp[j102] = fRec60_perm[j102];
			}
			fYec5_idx = (faust_wrap_add(fYec5_idx, fYec5_idx_save)) & 32767;
			fYec6_idx = (faust_wrap_add(fYec6_idx, fYec6_idx_save)) & 4095;
			for (int j104 = 0; j104 < 4; j104 = faust_wrap_add(j104, 1)) {
				fRec58_tmp[j104] = fRec58_perm[j104];
			}
			for (int j106 = 0; j106 < 4; j106 = faust_wrap_add(j106, 1)) {
				fRec65_tmp[j106] = fRec65_perm[j106];
			}
			for (int j108 = 0; j108 < 4; j108 = faust_wrap_add(j108, 1)) {
				fRec64_tmp[j108] = fRec64_perm[j108];
			}
			fYec7_idx = (faust_wrap_add(fYec7_idx, fYec7_idx_save)) & 16383;
			fYec8_idx = (faust_wrap_add(fYec8_idx, fYec8_idx_save)) & 4095;
			for (int j110 = 0; j110 < 4; j110 = faust_wrap_add(j110, 1)) {
				fRec62_tmp[j110] = fRec62_perm[j110];
			}
			for (int j112 = 0; j112 < 4; j112 = faust_wrap_add(j112, 1)) {
				fRec69_tmp[j112] = fRec69_perm[j112];
			}
			for (int j114 = 0; j114 < 4; j114 = faust_wrap_add(j114, 1)) {
				fRec68_tmp[j114] = fRec68_perm[j114];
			}
			fYec9_idx = (faust_wrap_add(fYec9_idx, fYec9_idx_save)) & 32767;
			fYec10_idx = (faust_wrap_add(fYec10_idx, fYec10_idx_save)) & 4095;
			for (int j116 = 0; j116 < 4; j116 = faust_wrap_add(j116, 1)) {
				fRec66_tmp[j116] = fRec66_perm[j116];
			}
			for (int j118 = 0; j118 < 4; j118 = faust_wrap_add(j118, 1)) {
				fRec73_tmp[j118] = fRec73_perm[j118];
			}
			for (int j120 = 0; j120 < 4; j120 = faust_wrap_add(j120, 1)) {
				fRec72_tmp[j120] = fRec72_perm[j120];
			}
			fYec11_idx = (faust_wrap_add(fYec11_idx, fYec11_idx_save)) & 16383;
			fYec12_idx = (faust_wrap_add(fYec12_idx, fYec12_idx_save)) & 2047;
			for (int j122 = 0; j122 < 4; j122 = faust_wrap_add(j122, 1)) {
				fRec70_tmp[j122] = fRec70_perm[j122];
			}
			for (int j124 = 0; j124 < 4; j124 = faust_wrap_add(j124, 1)) {
				fRec77_tmp[j124] = fRec77_perm[j124];
			}
			for (int j126 = 0; j126 < 4; j126 = faust_wrap_add(j126, 1)) {
				fRec76_tmp[j126] = fRec76_perm[j126];
			}
			fYec13_idx = (faust_wrap_add(fYec13_idx, fYec13_idx_save)) & 16383;
			fYec14_idx = (faust_wrap_add(fYec14_idx, fYec14_idx_save)) & 4095;
			for (int j128 = 0; j128 < 4; j128 = faust_wrap_add(j128, 1)) {
				fRec74_tmp[j128] = fRec74_perm[j128];
			}
			for (int j130 = 0; j130 < 4; j130 = faust_wrap_add(j130, 1)) {
				fRec81_tmp[j130] = fRec81_perm[j130];
			}
			for (int j132 = 0; j132 < 4; j132 = faust_wrap_add(j132, 1)) {
				fRec80_tmp[j132] = fRec80_perm[j132];
			}
			fYec15_idx = (faust_wrap_add(fYec15_idx, fYec15_idx_save)) & 16383;
			fYec16_idx = (faust_wrap_add(fYec16_idx, fYec16_idx_save)) & 4095;
			for (int j134 = 0; j134 < 4; j134 = faust_wrap_add(j134, 1)) {
				fRec78_tmp[j134] = fRec78_perm[j134];
			}
			for (int j136 = 0; j136 < 4; j136 = faust_wrap_add(j136, 1)) {
				fRec85_tmp[j136] = fRec85_perm[j136];
			}
			for (int j138 = 0; j138 < 4; j138 = faust_wrap_add(j138, 1)) {
				fRec84_tmp[j138] = fRec84_perm[j138];
			}
			fYec17_idx = (faust_wrap_add(fYec17_idx, fYec17_idx_save)) & 16383;
			fYec18_idx = (faust_wrap_add(fYec18_idx, fYec18_idx_save)) & 2047;
			for (int j140 = 0; j140 < 4; j140 = faust_wrap_add(j140, 1)) {
				fRec82_tmp[j140] = fRec82_perm[j140];
			}
			for (int j142 = 0; j142 < 4; j142 = faust_wrap_add(j142, 1)) {
				fRec1_tmp[j142] = fRec1_perm[j142];
			}
			for (int j144 = 0; j144 < 4; j144 = faust_wrap_add(j144, 1)) {
				fRec2_tmp[j144] = fRec2_perm[j144];
			}
			for (int j146 = 0; j146 < 4; j146 = faust_wrap_add(j146, 1)) {
				fRec3_tmp[j146] = fRec3_perm[j146];
			}
			for (int j148 = 0; j148 < 4; j148 = faust_wrap_add(j148, 1)) {
				fRec4_tmp[j148] = fRec4_perm[j148];
			}
			for (int j150 = 0; j150 < 4; j150 = faust_wrap_add(j150, 1)) {
				fRec5_tmp[j150] = fRec5_perm[j150];
			}
			for (int j152 = 0; j152 < 4; j152 = faust_wrap_add(j152, 1)) {
				fRec6_tmp[j152] = fRec6_perm[j152];
			}
			for (int j154 = 0; j154 < 4; j154 = faust_wrap_add(j154, 1)) {
				fRec7_tmp[j154] = fRec7_perm[j154];
			}
			for (int j156 = 0; j156 < 4; j156 = faust_wrap_add(j156, 1)) {
				fRec8_tmp[j156] = fRec8_perm[j156];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec12[i] = -(fConst2 * (fConst3 * fRec12[faust_wrap_sub(i, 1)] - (fRec8[faust_wrap_sub(i, 1)] + fRec8[faust_wrap_sub(i, 2)])));
				fRec11[i] = fSlow8 * fRec11[faust_wrap_sub(i, 1)] + fSlow9 * (fRec8[faust_wrap_sub(i, 1)] + fSlow10 * fRec12[i]);
				fYec2[(faust_wrap_add(i, fYec2_idx)) & 32767] = 0.35355339059327373 * fRec11[i] + 1e-20;
				fZec40[i] = 0.6 * fRec9[faust_wrap_sub(i, 1)] + fYec2[(faust_wrap_sub(faust_wrap_add(i, fYec2_idx), iConst18)) & 32767];
				fYec4[(faust_wrap_add(i, fYec4_idx)) & 2047] = fZec40[i] - fZec43[i];
				fRec9[i] = fYec4[(faust_wrap_sub(faust_wrap_add(i, fYec4_idx), iConst20)) & 2047];
				fRec10[i] = 0.6 * (fZec43[i] - fZec40[i]);
				fRec61[i] = -(fConst2 * (fConst3 * fRec61[faust_wrap_sub(i, 1)] - (fRec4[faust_wrap_sub(i, 1)] + fRec4[faust_wrap_sub(i, 2)])));
				fRec60[i] = fSlow45 * fRec60[faust_wrap_sub(i, 1)] + fSlow46 * (fRec4[faust_wrap_sub(i, 1)] + fSlow47 * fRec61[i]);
				fYec5[(faust_wrap_add(i, fYec5_idx)) & 32767] = 0.35355339059327373 * fRec60[i] + 1e-20;
				fZec44[i] = 0.6 * fRec58[faust_wrap_sub(i, 1)] + fYec5[(faust_wrap_sub(faust_wrap_add(i, fYec5_idx), iConst26)) & 32767];
				fYec6[(faust_wrap_add(i, fYec6_idx)) & 4095] = fZec44[i] - fZec43[i];
				fRec58[i] = fYec6[(faust_wrap_sub(faust_wrap_add(i, fYec6_idx), iConst27)) & 4095];
				fRec59[i] = 0.6 * (fZec43[i] - fZec44[i]);
				fRec65[i] = -(fConst2 * (fConst3 * fRec65[faust_wrap_sub(i, 1)] - (fRec6[faust_wrap_sub(i, 1)] + fRec6[faust_wrap_sub(i, 2)])));
				fRec64[i] = fSlow54 * fRec64[faust_wrap_sub(i, 1)] + fSlow55 * (fRec6[faust_wrap_sub(i, 1)] + fSlow56 * fRec65[i]);
				fYec7[(faust_wrap_add(i, fYec7_idx)) & 16383] = 0.35355339059327373 * fRec64[i] + 1e-20;
				fYec8[(faust_wrap_add(i, fYec8_idx)) & 4095] = fYec7[(faust_wrap_sub(faust_wrap_add(i, fYec7_idx), iConst33)) & 16383] + fZec43[i] + 0.6 * fRec62[faust_wrap_sub(i, 1)];
				fRec62[i] = fYec8[(faust_wrap_sub(faust_wrap_add(i, fYec8_idx), iConst34)) & 4095];
				fRec63[i] = -(0.6 * fYec8[(faust_wrap_add(i, fYec8_idx)) & 4095]);
				fRec69[i] = -(fConst2 * (fConst3 * fRec69[faust_wrap_sub(i, 1)] - (fRec2[faust_wrap_sub(i, 1)] + fRec2[faust_wrap_sub(i, 2)])));
				fRec68[i] = fSlow63 * fRec68[faust_wrap_sub(i, 1)] + fSlow64 * (fRec2[faust_wrap_sub(i, 1)] + fSlow65 * fRec69[i]);
				fYec9[(faust_wrap_add(i, fYec9_idx)) & 32767] = 0.35355339059327373 * fRec68[i] + 1e-20;
				fYec10[(faust_wrap_add(i, fYec10_idx)) & 4095] = fYec9[(faust_wrap_sub(faust_wrap_add(i, fYec9_idx), iConst40)) & 32767] + fZec43[i] + 0.6 * fRec66[faust_wrap_sub(i, 1)];
				fRec66[i] = fYec10[(faust_wrap_sub(faust_wrap_add(i, fYec10_idx), iConst41)) & 4095];
				fRec67[i] = -(0.6 * fYec10[(faust_wrap_add(i, fYec10_idx)) & 4095]);
				fRec73[i] = -(fConst2 * (fConst3 * fRec73[faust_wrap_sub(i, 1)] - (fRec7[faust_wrap_sub(i, 1)] + fRec7[faust_wrap_sub(i, 2)])));
				fRec72[i] = fSlow72 * fRec72[faust_wrap_sub(i, 1)] + fSlow73 * (fRec7[faust_wrap_sub(i, 1)] + fSlow74 * fRec73[i]);
				fYec11[(faust_wrap_add(i, fYec11_idx)) & 16383] = 0.35355339059327373 * fRec72[i] + 1e-20;
				fYec12[(faust_wrap_add(i, fYec12_idx)) & 2047] = fYec11[(faust_wrap_sub(faust_wrap_add(i, fYec11_idx), iConst47)) & 16383] - (fZec43[i] + 0.6 * fRec70[faust_wrap_sub(i, 1)]);
				fRec70[i] = fYec12[(faust_wrap_sub(faust_wrap_add(i, fYec12_idx), iConst48)) & 2047];
				fRec71[i] = 0.6 * fYec12[(faust_wrap_add(i, fYec12_idx)) & 2047];
				fRec77[i] = -(fConst2 * (fConst3 * fRec77[faust_wrap_sub(i, 1)] - (fRec3[faust_wrap_sub(i, 1)] + fRec3[faust_wrap_sub(i, 2)])));
				fRec76[i] = fSlow81 * fRec76[faust_wrap_sub(i, 1)] + fSlow82 * (fRec3[faust_wrap_sub(i, 1)] + fSlow83 * fRec77[i]);
				fYec13[(faust_wrap_add(i, fYec13_idx)) & 16383] = 0.35355339059327373 * fRec76[i] + 1e-20;
				fYec14[(faust_wrap_add(i, fYec14_idx)) & 4095] = fYec13[(faust_wrap_sub(faust_wrap_add(i, fYec13_idx), iConst54)) & 16383] - (fZec43[i] + 0.6 * fRec74[faust_wrap_sub(i, 1)]);
				fRec74[i] = fYec14[(faust_wrap_sub(faust_wrap_add(i, fYec14_idx), iConst55)) & 4095];
				fRec75[i] = 0.6 * fYec14[(faust_wrap_add(i, fYec14_idx)) & 4095];
				fRec81[i] = -(fConst2 * (fConst3 * fRec81[faust_wrap_sub(i, 1)] - (fRec5[faust_wrap_sub(i, 1)] + fRec5[faust_wrap_sub(i, 2)])));
				fRec80[i] = fSlow90 * fRec80[faust_wrap_sub(i, 1)] + fSlow91 * (fRec5[faust_wrap_sub(i, 1)] + fSlow92 * fRec81[i]);
				fYec15[(faust_wrap_add(i, fYec15_idx)) & 16383] = 0.35355339059327373 * fRec80[i] + 1e-20;
				fYec16[(faust_wrap_add(i, fYec16_idx)) & 4095] = fZec43[i] + fYec15[(faust_wrap_sub(faust_wrap_add(i, fYec15_idx), iConst61)) & 16383] - 0.6 * fRec78[faust_wrap_sub(i, 1)];
				fRec78[i] = fYec16[(faust_wrap_sub(faust_wrap_add(i, fYec16_idx), iConst62)) & 4095];
				fRec79[i] = 0.6 * fYec16[(faust_wrap_add(i, fYec16_idx)) & 4095];
				fRec85[i] = -(fConst2 * (fConst3 * fRec85[faust_wrap_sub(i, 1)] - (fRec1[faust_wrap_sub(i, 1)] + fRec1[faust_wrap_sub(i, 2)])));
				fRec84[i] = fSlow99 * fRec84[faust_wrap_sub(i, 1)] + fSlow100 * (fRec1[faust_wrap_sub(i, 1)] + fSlow101 * fRec85[i]);
				fYec17[(faust_wrap_add(i, fYec17_idx)) & 16383] = 0.35355339059327373 * fRec84[i] + 1e-20;
				fYec18[(faust_wrap_add(i, fYec18_idx)) & 2047] = fYec17[(faust_wrap_sub(faust_wrap_add(i, fYec17_idx), iConst68)) & 16383] + fZec43[i] - 0.6 * fRec82[faust_wrap_sub(i, 1)];
				fRec82[i] = fYec18[(faust_wrap_sub(faust_wrap_add(i, fYec18_idx), iConst69)) & 2047];
				fRec83[i] = 0.6 * fYec18[(faust_wrap_add(i, fYec18_idx)) & 2047];
				fZec45[i] = fRec83[i] + fRec79[i];
				fZec46[i] = fRec71[i] + fRec75[i] + fZec45[i];
				fRec1[i] = fRec9[faust_wrap_sub(i, 1)] + fRec58[faust_wrap_sub(i, 1)] + fRec62[faust_wrap_sub(i, 1)] + fRec66[faust_wrap_sub(i, 1)] + fRec70[faust_wrap_sub(i, 1)] + fRec74[faust_wrap_sub(i, 1)] + fRec78[faust_wrap_sub(i, 1)] + fRec82[faust_wrap_sub(i, 1)] + fRec10[i] + fRec59[i] + fRec63[i] + fRec67[i] + fZec46[i];
				fRec2[i] = fRec70[faust_wrap_sub(i, 1)] + fRec74[faust_wrap_sub(i, 1)] + fRec78[faust_wrap_sub(i, 1)] + fRec82[faust_wrap_sub(i, 1)] + fZec46[i] - (fRec9[faust_wrap_sub(i, 1)] + fRec58[faust_wrap_sub(i, 1)] + fRec62[faust_wrap_sub(i, 1)] + fRec66[faust_wrap_sub(i, 1)] + fRec10[i] + fRec59[i] + fRec67[i] + fRec63[i]);
				fZec47[i] = fRec75[i] + fRec71[i];
				fRec3[i] = fRec62[faust_wrap_sub(i, 1)] + fRec66[faust_wrap_sub(i, 1)] + fRec78[faust_wrap_sub(i, 1)] + fRec82[faust_wrap_sub(i, 1)] + fRec63[i] + fRec67[i] + fZec45[i] - (fRec9[faust_wrap_sub(i, 1)] + fRec58[faust_wrap_sub(i, 1)] + fRec70[faust_wrap_sub(i, 1)] + fRec74[faust_wrap_sub(i, 1)] + fRec10[i] + fRec59[i] + fZec47[i]);
				fRec4[i] = fRec9[faust_wrap_sub(i, 1)] + fRec58[faust_wrap_sub(i, 1)] + fRec78[faust_wrap_sub(i, 1)] + fRec82[faust_wrap_sub(i, 1)] + fRec10[i] + fRec59[i] + fZec45[i] - (fRec62[faust_wrap_sub(i, 1)] + fRec66[faust_wrap_sub(i, 1)] + fRec70[faust_wrap_sub(i, 1)] + fRec74[faust_wrap_sub(i, 1)] + fRec63[i] + fRec67[i] + fZec47[i]);
				fZec48[i] = fRec83[i] + fRec75[i];
				fZec49[i] = fRec79[i] + fRec71[i];
				fRec5[i] = fRec58[faust_wrap_sub(i, 1)] + fRec66[faust_wrap_sub(i, 1)] + fRec74[faust_wrap_sub(i, 1)] + fRec82[faust_wrap_sub(i, 1)] + fRec59[i] + fRec67[i] + fZec48[i] - (fRec9[faust_wrap_sub(i, 1)] + fRec62[faust_wrap_sub(i, 1)] + fRec70[faust_wrap_sub(i, 1)] + fRec78[faust_wrap_sub(i, 1)] + fRec10[i] + fRec63[i] + fZec49[i]);
				fRec6[i] = fRec9[faust_wrap_sub(i, 1)] + fRec62[faust_wrap_sub(i, 1)] + fRec74[faust_wrap_sub(i, 1)] + fRec82[faust_wrap_sub(i, 1)] + fRec10[i] + fRec63[i] + fZec48[i] - (fRec58[faust_wrap_sub(i, 1)] + fRec66[faust_wrap_sub(i, 1)] + fRec70[faust_wrap_sub(i, 1)] + fRec78[faust_wrap_sub(i, 1)] + fRec59[i] + fRec67[i] + fZec49[i]);
				fZec50[i] = fRec83[i] + fRec71[i];
				fZec51[i] = fRec79[i] + fRec75[i];
				fRec7[i] = fRec9[faust_wrap_sub(i, 1)] + fRec66[faust_wrap_sub(i, 1)] + fRec70[faust_wrap_sub(i, 1)] + fRec82[faust_wrap_sub(i, 1)] + fRec10[i] + fRec67[i] + fZec50[i] - (fRec58[faust_wrap_sub(i, 1)] + fRec62[faust_wrap_sub(i, 1)] + fRec74[faust_wrap_sub(i, 1)] + fRec78[faust_wrap_sub(i, 1)] + fRec59[i] + fRec63[i] + fZec51[i]);
				fRec8[i] = fRec58[faust_wrap_sub(i, 1)] + fRec62[faust_wrap_sub(i, 1)] + fRec70[faust_wrap_sub(i, 1)] + fRec82[faust_wrap_sub(i, 1)] + fRec59[i] + fRec63[i] + fZec50[i] - (fRec9[faust_wrap_sub(i, 1)] + fRec66[faust_wrap_sub(i, 1)] + fRec74[faust_wrap_sub(i, 1)] + fRec78[faust_wrap_sub(i, 1)] + fRec10[i] + fRec67[i] + fZec51[i]);
			}
			/* Post code */
			fYec17_idx_save = vsize;
			fYec18_idx_save = vsize;
			for (int j137 = 0; j137 < 4; j137 = faust_wrap_add(j137, 1)) {
				fRec85_perm[j137] = fRec85_tmp[faust_wrap_add(vsize, j137)];
			}
			for (int j139 = 0; j139 < 4; j139 = faust_wrap_add(j139, 1)) {
				fRec84_perm[j139] = fRec84_tmp[faust_wrap_add(vsize, j139)];
			}
			for (int j141 = 0; j141 < 4; j141 = faust_wrap_add(j141, 1)) {
				fRec82_perm[j141] = fRec82_tmp[faust_wrap_add(vsize, j141)];
			}
			fYec15_idx_save = vsize;
			fYec16_idx_save = vsize;
			for (int j131 = 0; j131 < 4; j131 = faust_wrap_add(j131, 1)) {
				fRec81_perm[j131] = fRec81_tmp[faust_wrap_add(vsize, j131)];
			}
			for (int j133 = 0; j133 < 4; j133 = faust_wrap_add(j133, 1)) {
				fRec80_perm[j133] = fRec80_tmp[faust_wrap_add(vsize, j133)];
			}
			for (int j135 = 0; j135 < 4; j135 = faust_wrap_add(j135, 1)) {
				fRec78_perm[j135] = fRec78_tmp[faust_wrap_add(vsize, j135)];
			}
			fYec13_idx_save = vsize;
			fYec14_idx_save = vsize;
			for (int j125 = 0; j125 < 4; j125 = faust_wrap_add(j125, 1)) {
				fRec77_perm[j125] = fRec77_tmp[faust_wrap_add(vsize, j125)];
			}
			for (int j127 = 0; j127 < 4; j127 = faust_wrap_add(j127, 1)) {
				fRec76_perm[j127] = fRec76_tmp[faust_wrap_add(vsize, j127)];
			}
			for (int j129 = 0; j129 < 4; j129 = faust_wrap_add(j129, 1)) {
				fRec74_perm[j129] = fRec74_tmp[faust_wrap_add(vsize, j129)];
			}
			fYec11_idx_save = vsize;
			fYec12_idx_save = vsize;
			for (int j119 = 0; j119 < 4; j119 = faust_wrap_add(j119, 1)) {
				fRec73_perm[j119] = fRec73_tmp[faust_wrap_add(vsize, j119)];
			}
			for (int j121 = 0; j121 < 4; j121 = faust_wrap_add(j121, 1)) {
				fRec72_perm[j121] = fRec72_tmp[faust_wrap_add(vsize, j121)];
			}
			for (int j123 = 0; j123 < 4; j123 = faust_wrap_add(j123, 1)) {
				fRec70_perm[j123] = fRec70_tmp[faust_wrap_add(vsize, j123)];
			}
			fYec9_idx_save = vsize;
			fYec10_idx_save = vsize;
			for (int j113 = 0; j113 < 4; j113 = faust_wrap_add(j113, 1)) {
				fRec69_perm[j113] = fRec69_tmp[faust_wrap_add(vsize, j113)];
			}
			for (int j115 = 0; j115 < 4; j115 = faust_wrap_add(j115, 1)) {
				fRec68_perm[j115] = fRec68_tmp[faust_wrap_add(vsize, j115)];
			}
			for (int j117 = 0; j117 < 4; j117 = faust_wrap_add(j117, 1)) {
				fRec66_perm[j117] = fRec66_tmp[faust_wrap_add(vsize, j117)];
			}
			fYec7_idx_save = vsize;
			fYec8_idx_save = vsize;
			for (int j107 = 0; j107 < 4; j107 = faust_wrap_add(j107, 1)) {
				fRec65_perm[j107] = fRec65_tmp[faust_wrap_add(vsize, j107)];
			}
			for (int j109 = 0; j109 < 4; j109 = faust_wrap_add(j109, 1)) {
				fRec64_perm[j109] = fRec64_tmp[faust_wrap_add(vsize, j109)];
			}
			for (int j111 = 0; j111 < 4; j111 = faust_wrap_add(j111, 1)) {
				fRec62_perm[j111] = fRec62_tmp[faust_wrap_add(vsize, j111)];
			}
			fYec5_idx_save = vsize;
			fYec6_idx_save = vsize;
			for (int j101 = 0; j101 < 4; j101 = faust_wrap_add(j101, 1)) {
				fRec61_perm[j101] = fRec61_tmp[faust_wrap_add(vsize, j101)];
			}
			for (int j103 = 0; j103 < 4; j103 = faust_wrap_add(j103, 1)) {
				fRec60_perm[j103] = fRec60_tmp[faust_wrap_add(vsize, j103)];
			}
			for (int j105 = 0; j105 < 4; j105 = faust_wrap_add(j105, 1)) {
				fRec58_perm[j105] = fRec58_tmp[faust_wrap_add(vsize, j105)];
			}
			fYec2_idx_save = vsize;
			fYec4_idx_save = vsize;
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fRec12_perm[j3] = fRec12_tmp[faust_wrap_add(vsize, j3)];
			}
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fRec11_perm[j5] = fRec11_tmp[faust_wrap_add(vsize, j5)];
			}
			for (int j99 = 0; j99 < 4; j99 = faust_wrap_add(j99, 1)) {
				fRec9_perm[j99] = fRec9_tmp[faust_wrap_add(vsize, j99)];
			}
			for (int j143 = 0; j143 < 4; j143 = faust_wrap_add(j143, 1)) {
				fRec1_perm[j143] = fRec1_tmp[faust_wrap_add(vsize, j143)];
			}
			for (int j145 = 0; j145 < 4; j145 = faust_wrap_add(j145, 1)) {
				fRec2_perm[j145] = fRec2_tmp[faust_wrap_add(vsize, j145)];
			}
			for (int j147 = 0; j147 < 4; j147 = faust_wrap_add(j147, 1)) {
				fRec3_perm[j147] = fRec3_tmp[faust_wrap_add(vsize, j147)];
			}
			for (int j149 = 0; j149 < 4; j149 = faust_wrap_add(j149, 1)) {
				fRec4_perm[j149] = fRec4_tmp[faust_wrap_add(vsize, j149)];
			}
			for (int j151 = 0; j151 < 4; j151 = faust_wrap_add(j151, 1)) {
				fRec5_perm[j151] = fRec5_tmp[faust_wrap_add(vsize, j151)];
			}
			for (int j153 = 0; j153 < 4; j153 = faust_wrap_add(j153, 1)) {
				fRec6_perm[j153] = fRec6_tmp[faust_wrap_add(vsize, j153)];
			}
			for (int j155 = 0; j155 < 4; j155 = faust_wrap_add(j155, 1)) {
				fRec7_perm[j155] = fRec7_tmp[faust_wrap_add(vsize, j155)];
			}
			for (int j157 = 0; j157 < 4; j157 = faust_wrap_add(j157, 1)) {
				fRec8_perm[j157] = fRec8_tmp[faust_wrap_add(vsize, j157)];
			}
			/* Vectorizable loop 50 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec52[i] = std::max<double>(0.75, std::min<double>(4.0, fRec0[i]));
			}
			/* Vectorizable loop 51 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec53[i] = 0.6 * fZec41[i] * (1.0 - fZec42[i]);
			}
			/* Vectorizable loop 52 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fZec52[i] * (0.37 * (fRec2[i] + fRec3[i]) + fZec53[i]));
			}
			/* Vectorizable loop 53 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fZec52[i] * (fZec53[i] + 0.37 * (fRec2[i] - fRec3[i])));
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
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec15_tmp[j6] = fRec15_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec15[i] = 0.999 * fRec15[faust_wrap_sub(i, 1)] + 0.0008000000000000008;
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec15_perm[j7] = fRec15_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Recursive loop 2 */
			/* Pre code */
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fRec17_tmp[j8] = fRec17_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec17[i] = fSlow11 + 0.999 * fRec17[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fRec17_perm[j9] = fRec17_tmp[faust_wrap_add(vsize, j9)];
			}
			/* Recursive loop 3 */
			/* Pre code */
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				fRec16_tmp[j10] = fRec16_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec0[i] = fRec16[faust_wrap_sub(i, 1)] + fConst9 * fRec17[i];
				fRec16[i] = fZec0[i] - std::floor(fZec0[i]);
			}
			/* Post code */
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				fRec16_perm[j11] = fRec16_tmp[faust_wrap_add(vsize, j11)];
			}
			/* Recursive loop 4 */
			/* Pre code */
			for (int j12 = 0; j12 < 4; j12 = faust_wrap_add(j12, 1)) {
				fRec18_tmp[j12] = fRec18_perm[j12];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec18[i] = ((iSlow14) ? 0.0 : std::min<double>(fConst10, fRec18[faust_wrap_sub(i, 1)] + 1.0));
			}
			/* Post code */
			for (int j13 = 0; j13 < 4; j13 = faust_wrap_add(j13, 1)) {
				fRec18_perm[j13] = fRec18_tmp[faust_wrap_add(vsize, j13)];
			}
			/* Recursive loop 5 */
			/* Pre code */
			for (int j14 = 0; j14 < 4; j14 = faust_wrap_add(j14, 1)) {
				fRec20_tmp[j14] = fRec20_perm[j14];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec20[i] = ((iSlow15) ? 0.0 : std::min<double>(fConst11, fRec20[faust_wrap_sub(i, 1)] + 1.0));
			}
			/* Post code */
			for (int j15 = 0; j15 < 4; j15 = faust_wrap_add(j15, 1)) {
				fRec20_perm[j15] = fRec20_tmp[faust_wrap_add(vsize, j15)];
			}
			/* Recursive loop 6 */
			/* Pre code */
			for (int j16 = 0; j16 < 4; j16 = faust_wrap_add(j16, 1)) {
				fRec19_tmp[j16] = fRec19_perm[j16];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec19[i] = ((iSlow13) ? fSlow16 * ((fRec20[i] < 0.0) ? 0.0 : ((fRec20[i] < fConst11) ? fSlow17 * fRec20[i] : fSlow12)) : fRec19[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j17 = 0; j17 < 4; j17 = faust_wrap_add(j17, 1)) {
				fRec19_perm[j17] = fRec19_tmp[faust_wrap_add(vsize, j17)];
			}
			/* Recursive loop 7 */
			/* Pre code */
			for (int j18 = 0; j18 < 4; j18 = faust_wrap_add(j18, 1)) {
				fRec22_tmp[j18] = fRec22_perm[j18];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec22[i] = fSlow18 + 0.999 * fRec22[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j19 = 0; j19 < 4; j19 = faust_wrap_add(j19, 1)) {
				fRec22_perm[j19] = fRec22_tmp[faust_wrap_add(vsize, j19)];
			}
			/* Recursive loop 8 */
			/* Pre code */
			for (int j20 = 0; j20 < 4; j20 = faust_wrap_add(j20, 1)) {
				fRec21_tmp[j20] = fRec21_perm[j20];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec1[i] = fRec21[faust_wrap_sub(i, 1)] + fConst9 * fRec22[i];
				fRec21[i] = fZec1[i] - std::floor(fZec1[i]);
			}
			/* Post code */
			for (int j21 = 0; j21 < 4; j21 = faust_wrap_add(j21, 1)) {
				fRec21_perm[j21] = fRec21_tmp[faust_wrap_add(vsize, j21)];
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec2[i] = 3.141592653589793 * fRec15[i] * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0 * fRec16[i]), 65535))] * ((fRec18[i] < 0.0) ? fRec19[i] : ((fRec18[i] < fConst10) ? fRec19[i] * (1.0 - fConst13 * fRec18[i]) : 0.0));
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec3[i] = std::cos(fZec2[i]);
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec4[i] = 65536.0 * fRec21[i];
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec5[i] = static_cast<int>(fZec4[i]);
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec6[i] = ftbl1mydspSIG0[std::max<int>(0, std::min<int>(iZec5[i], 65536))];
			}
			/* Vectorizable loop 14 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec7[i] = fZec6[i] + (fZec4[i] - std::floor(fZec4[i])) * (ftbl1mydspSIG0[std::max<int>(0, std::min<int>(faust_wrap_add(iZec5[i], 1), 65536))] - fZec6[i]);
			}
			/* Vectorizable loop 15 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec8[i] = std::sin(fZec2[i]);
			}
			/* Recursive loop 16 */
			/* Pre code */
			for (int j22 = 0; j22 < 4; j22 = faust_wrap_add(j22, 1)) {
				fRec27_tmp[j22] = fRec27_perm[j22];
			}
			for (int j24 = 0; j24 < 4; j24 = faust_wrap_add(j24, 1)) {
				fRec26_tmp[j24] = fRec26_perm[j24];
			}
			for (int j26 = 0; j26 < 4; j26 = faust_wrap_add(j26, 1)) {
				fRec25_tmp[j26] = fRec25_perm[j26];
			}
			for (int j28 = 0; j28 < 4; j28 = faust_wrap_add(j28, 1)) {
				fRec24_tmp[j28] = fRec24_perm[j28];
			}
			for (int j30 = 0; j30 < 4; j30 = faust_wrap_add(j30, 1)) {
				fRec23_tmp[j30] = fRec23_perm[j30];
			}
			for (int j32 = 0; j32 < 4; j32 = faust_wrap_add(j32, 1)) {
				fRec14_tmp[j32] = fRec14_perm[j32];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec9[i] = fZec7[i] * fZec3[i] - fZec8[i] * fRec14[faust_wrap_sub(i, 1)];
				fZec10[i] = fZec3[i] * fZec9[i] - fZec8[i] * fRec23[faust_wrap_sub(i, 1)];
				fZec11[i] = fZec3[i] * fZec10[i] - fZec8[i] * fRec24[faust_wrap_sub(i, 1)];
				fZec12[i] = fZec3[i] * fZec11[i] - fZec8[i] * fRec25[faust_wrap_sub(i, 1)];
				fZec13[i] = fZec3[i] * fZec12[i] - fZec8[i] * fRec26[faust_wrap_sub(i, 1)];
				fRec27[i] = fZec3[i] * fZec13[i] - fZec8[i] * fRec27[faust_wrap_sub(i, 1)];
				fRec26[i] = fZec8[i] * fZec13[i] + fZec3[i] * fRec27[faust_wrap_sub(i, 1)];
				fRec25[i] = fZec8[i] * fZec12[i] + fZec3[i] * fRec26[faust_wrap_sub(i, 1)];
				fRec24[i] = fZec8[i] * fZec11[i] + fZec3[i] * fRec25[faust_wrap_sub(i, 1)];
				fRec23[i] = fZec8[i] * fZec10[i] + fZec3[i] * fRec24[faust_wrap_sub(i, 1)];
				fRec14[i] = fZec8[i] * fZec9[i] + fZec3[i] * fRec23[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j23 = 0; j23 < 4; j23 = faust_wrap_add(j23, 1)) {
				fRec27_perm[j23] = fRec27_tmp[faust_wrap_add(vsize, j23)];
			}
			for (int j25 = 0; j25 < 4; j25 = faust_wrap_add(j25, 1)) {
				fRec26_perm[j25] = fRec26_tmp[faust_wrap_add(vsize, j25)];
			}
			for (int j27 = 0; j27 < 4; j27 = faust_wrap_add(j27, 1)) {
				fRec25_perm[j27] = fRec25_tmp[faust_wrap_add(vsize, j27)];
			}
			for (int j29 = 0; j29 < 4; j29 = faust_wrap_add(j29, 1)) {
				fRec24_perm[j29] = fRec24_tmp[faust_wrap_add(vsize, j29)];
			}
			for (int j31 = 0; j31 < 4; j31 = faust_wrap_add(j31, 1)) {
				fRec23_perm[j31] = fRec23_tmp[faust_wrap_add(vsize, j31)];
			}
			for (int j33 = 0; j33 < 4; j33 = faust_wrap_add(j33, 1)) {
				fRec14_perm[j33] = fRec14_tmp[faust_wrap_add(vsize, j33)];
			}
			/* Recursive loop 17 */
			/* Pre code */
			for (int j34 = 0; j34 < 4; j34 = faust_wrap_add(j34, 1)) {
				fRec29_tmp[j34] = fRec29_perm[j34];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec29[i] = ((iSlow21) ? 0.0 : std::min<double>(fConst10, fRec29[faust_wrap_sub(i, 1)] + 1.0));
			}
			/* Post code */
			for (int j35 = 0; j35 < 4; j35 = faust_wrap_add(j35, 1)) {
				fRec29_perm[j35] = fRec29_tmp[faust_wrap_add(vsize, j35)];
			}
			/* Recursive loop 18 */
			/* Pre code */
			for (int j36 = 0; j36 < 4; j36 = faust_wrap_add(j36, 1)) {
				fRec31_tmp[j36] = fRec31_perm[j36];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec31[i] = ((iSlow22) ? 0.0 : std::min<double>(fConst11, fRec31[faust_wrap_sub(i, 1)] + 1.0));
			}
			/* Post code */
			for (int j37 = 0; j37 < 4; j37 = faust_wrap_add(j37, 1)) {
				fRec31_perm[j37] = fRec31_tmp[faust_wrap_add(vsize, j37)];
			}
			/* Recursive loop 19 */
			/* Pre code */
			for (int j38 = 0; j38 < 4; j38 = faust_wrap_add(j38, 1)) {
				fRec30_tmp[j38] = fRec30_perm[j38];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec30[i] = ((iSlow20) ? fSlow23 * ((fRec31[i] < 0.0) ? 0.0 : ((fRec31[i] < fConst11) ? fSlow24 * fRec31[i] : fSlow19)) : fRec30[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j39 = 0; j39 < 4; j39 = faust_wrap_add(j39, 1)) {
				fRec30_perm[j39] = fRec30_tmp[faust_wrap_add(vsize, j39)];
			}
			/* Vectorizable loop 20 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec14[i] = 3.141592653589793 * fRec15[i] * fZec7[i] * ((fRec29[i] < 0.0) ? fRec30[i] : ((fRec29[i] < fConst10) ? fRec30[i] * (1.0 - fConst13 * fRec29[i]) : 0.0));
			}
			/* Vectorizable loop 21 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec15[i] = std::cos(fZec14[i]);
			}
			/* Vectorizable loop 22 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec16[i] = std::sin(fZec14[i]);
			}
			/* Recursive loop 23 */
			/* Pre code */
			for (int j40 = 0; j40 < 4; j40 = faust_wrap_add(j40, 1)) {
				fRec37_tmp[j40] = fRec37_perm[j40];
			}
			for (int j42 = 0; j42 < 4; j42 = faust_wrap_add(j42, 1)) {
				fRec36_tmp[j42] = fRec36_perm[j42];
			}
			for (int j44 = 0; j44 < 4; j44 = faust_wrap_add(j44, 1)) {
				fRec35_tmp[j44] = fRec35_perm[j44];
			}
			for (int j46 = 0; j46 < 4; j46 = faust_wrap_add(j46, 1)) {
				fRec34_tmp[j46] = fRec34_perm[j46];
			}
			for (int j48 = 0; j48 < 4; j48 = faust_wrap_add(j48, 1)) {
				fRec33_tmp[j48] = fRec33_perm[j48];
			}
			for (int j50 = 0; j50 < 4; j50 = faust_wrap_add(j50, 1)) {
				fRec32_tmp[j50] = fRec32_perm[j50];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec17[i] = fZec7[i] * fZec15[i] - fZec16[i] * fRec32[faust_wrap_sub(i, 1)];
				fZec18[i] = fZec15[i] * fZec17[i] - fZec16[i] * fRec33[faust_wrap_sub(i, 1)];
				fZec19[i] = fZec15[i] * fZec18[i] - fZec16[i] * fRec34[faust_wrap_sub(i, 1)];
				fZec20[i] = fZec15[i] * fZec19[i] - fZec16[i] * fRec35[faust_wrap_sub(i, 1)];
				fZec21[i] = fZec15[i] * fZec20[i] - fZec16[i] * fRec36[faust_wrap_sub(i, 1)];
				fRec37[i] = fZec15[i] * fZec21[i] - fZec16[i] * fRec37[faust_wrap_sub(i, 1)];
				fRec36[i] = fZec16[i] * fZec21[i] + fZec15[i] * fRec37[faust_wrap_sub(i, 1)];
				fRec35[i] = fZec16[i] * fZec20[i] + fZec15[i] * fRec36[faust_wrap_sub(i, 1)];
				fRec34[i] = fZec16[i] * fZec19[i] + fZec15[i] * fRec35[faust_wrap_sub(i, 1)];
				fRec33[i] = fZec16[i] * fZec18[i] + fZec15[i] * fRec34[faust_wrap_sub(i, 1)];
				fRec32[i] = fZec16[i] * fZec17[i] + fZec15[i] * fRec33[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j41 = 0; j41 < 4; j41 = faust_wrap_add(j41, 1)) {
				fRec37_perm[j41] = fRec37_tmp[faust_wrap_add(vsize, j41)];
			}
			for (int j43 = 0; j43 < 4; j43 = faust_wrap_add(j43, 1)) {
				fRec36_perm[j43] = fRec36_tmp[faust_wrap_add(vsize, j43)];
			}
			for (int j45 = 0; j45 < 4; j45 = faust_wrap_add(j45, 1)) {
				fRec35_perm[j45] = fRec35_tmp[faust_wrap_add(vsize, j45)];
			}
			for (int j47 = 0; j47 < 4; j47 = faust_wrap_add(j47, 1)) {
				fRec34_perm[j47] = fRec34_tmp[faust_wrap_add(vsize, j47)];
			}
			for (int j49 = 0; j49 < 4; j49 = faust_wrap_add(j49, 1)) {
				fRec33_perm[j49] = fRec33_tmp[faust_wrap_add(vsize, j49)];
			}
			for (int j51 = 0; j51 < 4; j51 = faust_wrap_add(j51, 1)) {
				fRec32_perm[j51] = fRec32_tmp[faust_wrap_add(vsize, j51)];
			}
			/* Recursive loop 24 */
			/* Pre code */
			for (int j52 = 0; j52 < 4; j52 = faust_wrap_add(j52, 1)) {
				fRec38_tmp[j52] = fRec38_perm[j52];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec38[i] = ((iSlow27) ? 0.0 : std::min<double>(fConst10, fRec38[faust_wrap_sub(i, 1)] + 1.0));
			}
			/* Post code */
			for (int j53 = 0; j53 < 4; j53 = faust_wrap_add(j53, 1)) {
				fRec38_perm[j53] = fRec38_tmp[faust_wrap_add(vsize, j53)];
			}
			/* Recursive loop 25 */
			/* Pre code */
			for (int j54 = 0; j54 < 4; j54 = faust_wrap_add(j54, 1)) {
				fRec40_tmp[j54] = fRec40_perm[j54];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec40[i] = ((iSlow28) ? 0.0 : std::min<double>(fConst11, fRec40[faust_wrap_sub(i, 1)] + 1.0));
			}
			/* Post code */
			for (int j55 = 0; j55 < 4; j55 = faust_wrap_add(j55, 1)) {
				fRec40_perm[j55] = fRec40_tmp[faust_wrap_add(vsize, j55)];
			}
			/* Recursive loop 26 */
			/* Pre code */
			for (int j56 = 0; j56 < 4; j56 = faust_wrap_add(j56, 1)) {
				fRec39_tmp[j56] = fRec39_perm[j56];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec39[i] = ((iSlow26) ? fSlow29 * ((fRec40[i] < 0.0) ? 0.0 : ((fRec40[i] < fConst11) ? fSlow30 * fRec40[i] : fSlow25)) : fRec39[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j57 = 0; j57 < 4; j57 = faust_wrap_add(j57, 1)) {
				fRec39_perm[j57] = fRec39_tmp[faust_wrap_add(vsize, j57)];
			}
			/* Vectorizable loop 27 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec22[i] = 1.0 - fRec15[i];
			}
			/* Vectorizable loop 28 */
			/* Pre code */
			for (int j58 = 0; j58 < 4; j58 = faust_wrap_add(j58, 1)) {
				fYec0_tmp[j58] = fYec0_perm[j58];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec0[i] = fRec15[i] * (fZec7[i] * fZec16[i] + fRec32[faust_wrap_sub(i, 1)] * fZec15[i]) + fZec22[i] * fZec7[i];
			}
			/* Post code */
			for (int j59 = 0; j59 < 4; j59 = faust_wrap_add(j59, 1)) {
				fYec0_perm[j59] = fYec0_tmp[faust_wrap_add(vsize, j59)];
			}
			/* Vectorizable loop 29 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec23[i] = 1.5707963267948966 * fRec15[i] * ((fRec38[i] < 0.0) ? fRec39[i] : ((fRec38[i] < fConst10) ? fRec39[i] * (1.0 - fConst13 * fRec38[i]) : 0.0)) * (fYec0[i] + fYec0[faust_wrap_sub(i, 1)]);
			}
			/* Vectorizable loop 30 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec24[i] = std::cos(fZec23[i]);
			}
			/* Vectorizable loop 31 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec25[i] = std::sin(fZec23[i]);
			}
			/* Recursive loop 32 */
			/* Pre code */
			for (int j60 = 0; j60 < 4; j60 = faust_wrap_add(j60, 1)) {
				fRec46_tmp[j60] = fRec46_perm[j60];
			}
			for (int j62 = 0; j62 < 4; j62 = faust_wrap_add(j62, 1)) {
				fRec45_tmp[j62] = fRec45_perm[j62];
			}
			for (int j64 = 0; j64 < 4; j64 = faust_wrap_add(j64, 1)) {
				fRec44_tmp[j64] = fRec44_perm[j64];
			}
			for (int j66 = 0; j66 < 4; j66 = faust_wrap_add(j66, 1)) {
				fRec43_tmp[j66] = fRec43_perm[j66];
			}
			for (int j68 = 0; j68 < 4; j68 = faust_wrap_add(j68, 1)) {
				fRec42_tmp[j68] = fRec42_perm[j68];
			}
			for (int j70 = 0; j70 < 4; j70 = faust_wrap_add(j70, 1)) {
				fRec41_tmp[j70] = fRec41_perm[j70];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec26[i] = fYec0[i] * fZec24[i] - fZec25[i] * fRec41[faust_wrap_sub(i, 1)];
				fZec27[i] = fZec24[i] * fZec26[i] - fZec25[i] * fRec42[faust_wrap_sub(i, 1)];
				fZec28[i] = fZec24[i] * fZec27[i] - fZec25[i] * fRec43[faust_wrap_sub(i, 1)];
				fZec29[i] = fZec24[i] * fZec28[i] - fZec25[i] * fRec44[faust_wrap_sub(i, 1)];
				fZec30[i] = fZec24[i] * fZec29[i] - fZec25[i] * fRec45[faust_wrap_sub(i, 1)];
				fRec46[i] = fZec24[i] * fZec30[i] - fZec25[i] * fRec46[faust_wrap_sub(i, 1)];
				fRec45[i] = fZec25[i] * fZec30[i] + fZec24[i] * fRec46[faust_wrap_sub(i, 1)];
				fRec44[i] = fZec25[i] * fZec29[i] + fZec24[i] * fRec45[faust_wrap_sub(i, 1)];
				fRec43[i] = fZec25[i] * fZec28[i] + fZec24[i] * fRec44[faust_wrap_sub(i, 1)];
				fRec42[i] = fZec25[i] * fZec27[i] + fZec24[i] * fRec43[faust_wrap_sub(i, 1)];
				fRec41[i] = fZec25[i] * fZec26[i] + fZec24[i] * fRec42[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j61 = 0; j61 < 4; j61 = faust_wrap_add(j61, 1)) {
				fRec46_perm[j61] = fRec46_tmp[faust_wrap_add(vsize, j61)];
			}
			for (int j63 = 0; j63 < 4; j63 = faust_wrap_add(j63, 1)) {
				fRec45_perm[j63] = fRec45_tmp[faust_wrap_add(vsize, j63)];
			}
			for (int j65 = 0; j65 < 4; j65 = faust_wrap_add(j65, 1)) {
				fRec44_perm[j65] = fRec44_tmp[faust_wrap_add(vsize, j65)];
			}
			for (int j67 = 0; j67 < 4; j67 = faust_wrap_add(j67, 1)) {
				fRec43_perm[j67] = fRec43_tmp[faust_wrap_add(vsize, j67)];
			}
			for (int j69 = 0; j69 < 4; j69 = faust_wrap_add(j69, 1)) {
				fRec42_perm[j69] = fRec42_tmp[faust_wrap_add(vsize, j69)];
			}
			for (int j71 = 0; j71 < 4; j71 = faust_wrap_add(j71, 1)) {
				fRec41_perm[j71] = fRec41_tmp[faust_wrap_add(vsize, j71)];
			}
			/* Recursive loop 33 */
			/* Pre code */
			for (int j72 = 0; j72 < 4; j72 = faust_wrap_add(j72, 1)) {
				fRec47_tmp[j72] = fRec47_perm[j72];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec47[i] = ((iSlow33) ? 0.0 : std::min<double>(fConst10, fRec47[faust_wrap_sub(i, 1)] + 1.0));
			}
			/* Post code */
			for (int j73 = 0; j73 < 4; j73 = faust_wrap_add(j73, 1)) {
				fRec47_perm[j73] = fRec47_tmp[faust_wrap_add(vsize, j73)];
			}
			/* Recursive loop 34 */
			/* Pre code */
			for (int j74 = 0; j74 < 4; j74 = faust_wrap_add(j74, 1)) {
				fRec49_tmp[j74] = fRec49_perm[j74];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec49[i] = ((iSlow34) ? 0.0 : std::min<double>(fConst11, fRec49[faust_wrap_sub(i, 1)] + 1.0));
			}
			/* Post code */
			for (int j75 = 0; j75 < 4; j75 = faust_wrap_add(j75, 1)) {
				fRec49_perm[j75] = fRec49_tmp[faust_wrap_add(vsize, j75)];
			}
			/* Recursive loop 35 */
			/* Pre code */
			for (int j76 = 0; j76 < 4; j76 = faust_wrap_add(j76, 1)) {
				fRec48_tmp[j76] = fRec48_perm[j76];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec48[i] = ((iSlow32) ? fSlow35 * ((fRec49[i] < 0.0) ? 0.0 : ((fRec49[i] < fConst11) ? fSlow36 * fRec49[i] : fSlow31)) : fRec48[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j77 = 0; j77 < 4; j77 = faust_wrap_add(j77, 1)) {
				fRec48_perm[j77] = fRec48_tmp[faust_wrap_add(vsize, j77)];
			}
			/* Vectorizable loop 36 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec31[i] = fRec15[i] * (fYec0[i] * fZec25[i] + fRec41[faust_wrap_sub(i, 1)] * fZec24[i]) + fZec22[i] * fYec0[i];
			}
			/* Vectorizable loop 37 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec32[i] = 3.141592653589793 * fRec15[i] * mydsp_faustpower2_f(fZec31[i]) * ((fRec47[i] < 0.0) ? fRec48[i] : ((fRec47[i] < fConst10) ? fRec48[i] * (1.0 - fConst13 * fRec47[i]) : 0.0));
			}
			/* Vectorizable loop 38 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec33[i] = std::cos(fZec32[i]);
			}
			/* Vectorizable loop 39 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec34[i] = std::sin(fZec32[i]);
			}
			/* Recursive loop 40 */
			/* Pre code */
			for (int j78 = 0; j78 < 4; j78 = faust_wrap_add(j78, 1)) {
				fRec55_tmp[j78] = fRec55_perm[j78];
			}
			for (int j80 = 0; j80 < 4; j80 = faust_wrap_add(j80, 1)) {
				fRec54_tmp[j80] = fRec54_perm[j80];
			}
			for (int j82 = 0; j82 < 4; j82 = faust_wrap_add(j82, 1)) {
				fRec53_tmp[j82] = fRec53_perm[j82];
			}
			for (int j84 = 0; j84 < 4; j84 = faust_wrap_add(j84, 1)) {
				fRec52_tmp[j84] = fRec52_perm[j84];
			}
			for (int j86 = 0; j86 < 4; j86 = faust_wrap_add(j86, 1)) {
				fRec51_tmp[j86] = fRec51_perm[j86];
			}
			for (int j88 = 0; j88 < 4; j88 = faust_wrap_add(j88, 1)) {
				fRec50_tmp[j88] = fRec50_perm[j88];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec35[i] = fZec31[i] * fZec33[i] - fZec34[i] * fRec50[faust_wrap_sub(i, 1)];
				fZec36[i] = fZec33[i] * fZec35[i] - fZec34[i] * fRec51[faust_wrap_sub(i, 1)];
				fZec37[i] = fZec33[i] * fZec36[i] - fZec34[i] * fRec52[faust_wrap_sub(i, 1)];
				fZec38[i] = fZec33[i] * fZec37[i] - fZec34[i] * fRec53[faust_wrap_sub(i, 1)];
				fZec39[i] = fZec33[i] * fZec38[i] - fZec34[i] * fRec54[faust_wrap_sub(i, 1)];
				fRec55[i] = fZec33[i] * fZec39[i] - fZec34[i] * fRec55[faust_wrap_sub(i, 1)];
				fRec54[i] = fZec34[i] * fZec39[i] + fZec33[i] * fRec55[faust_wrap_sub(i, 1)];
				fRec53[i] = fZec34[i] * fZec38[i] + fZec33[i] * fRec54[faust_wrap_sub(i, 1)];
				fRec52[i] = fZec34[i] * fZec37[i] + fZec33[i] * fRec53[faust_wrap_sub(i, 1)];
				fRec51[i] = fZec34[i] * fZec36[i] + fZec33[i] * fRec52[faust_wrap_sub(i, 1)];
				fRec50[i] = fZec34[i] * fZec35[i] + fZec33[i] * fRec51[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j79 = 0; j79 < 4; j79 = faust_wrap_add(j79, 1)) {
				fRec55_perm[j79] = fRec55_tmp[faust_wrap_add(vsize, j79)];
			}
			for (int j81 = 0; j81 < 4; j81 = faust_wrap_add(j81, 1)) {
				fRec54_perm[j81] = fRec54_tmp[faust_wrap_add(vsize, j81)];
			}
			for (int j83 = 0; j83 < 4; j83 = faust_wrap_add(j83, 1)) {
				fRec53_perm[j83] = fRec53_tmp[faust_wrap_add(vsize, j83)];
			}
			for (int j85 = 0; j85 < 4; j85 = faust_wrap_add(j85, 1)) {
				fRec52_perm[j85] = fRec52_tmp[faust_wrap_add(vsize, j85)];
			}
			for (int j87 = 0; j87 < 4; j87 = faust_wrap_add(j87, 1)) {
				fRec51_perm[j87] = fRec51_tmp[faust_wrap_add(vsize, j87)];
			}
			for (int j89 = 0; j89 < 4; j89 = faust_wrap_add(j89, 1)) {
				fRec50_perm[j89] = fRec50_tmp[faust_wrap_add(vsize, j89)];
			}
			/* Vectorizable loop 41 */
			/* Pre code */
			for (int j90 = 0; j90 < 4; j90 = faust_wrap_add(j90, 1)) {
				fYec1_tmp[j90] = fYec1_perm[j90];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec1[i] = fRec14[faust_wrap_sub(i, 1)] * fZec3[i] + fRec15[i] * (fZec31[i] * fZec34[i] + fRec50[faust_wrap_sub(i, 1)] * fZec33[i]) + fZec22[i] * fZec31[i] + fZec7[i] * fZec8[i];
			}
			/* Post code */
			for (int j91 = 0; j91 < 4; j91 = faust_wrap_add(j91, 1)) {
				fYec1_perm[j91] = fYec1_tmp[faust_wrap_add(vsize, j91)];
			}
			/* Recursive loop 42 */
			/* Pre code */
			for (int j92 = 0; j92 < 4; j92 = faust_wrap_add(j92, 1)) {
				fRec13_tmp[j92] = fRec13_perm[j92];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec13[i] = -(fConst15 * (fConst16 * fRec13[faust_wrap_sub(i, 1)] - (fYec1[i] + fYec1[faust_wrap_sub(i, 1)])));
			}
			/* Post code */
			for (int j93 = 0; j93 < 4; j93 = faust_wrap_add(j93, 1)) {
				fRec13_perm[j93] = fRec13_tmp[faust_wrap_add(vsize, j93)];
			}
			/* Recursive loop 43 */
			/* Pre code */
			for (int j94 = 0; j94 < 4; j94 = faust_wrap_add(j94, 1)) {
				fRec56_tmp[j94] = fRec56_perm[j94];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec56[i] = fSlow37 + 0.999 * fRec56[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j95 = 0; j95 < 4; j95 = faust_wrap_add(j95, 1)) {
				fRec56_perm[j95] = fRec56_tmp[faust_wrap_add(vsize, j95)];
			}
			/* Recursive loop 44 */
			/* Pre code */
			for (int j96 = 0; j96 < 4; j96 = faust_wrap_add(j96, 1)) {
				fRec57_tmp[j96] = fRec57_perm[j96];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec57[i] = fSlow38 + 0.999 * fRec57[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j97 = 0; j97 < 4; j97 = faust_wrap_add(j97, 1)) {
				fRec57_perm[j97] = fRec57_tmp[faust_wrap_add(vsize, j97)];
			}
			/* Vectorizable loop 45 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec41[i] = fRec13[i] * fRec56[i];
			}
			/* Vectorizable loop 46 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec42[i] = std::max<double>(0.05, std::min<double>(1.0, fRec57[i]));
			}
			/* Vectorizable loop 47 */
			/* Pre code */
			fYec3_idx = (faust_wrap_add(fYec3_idx, fYec3_idx_save)) & 4095;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec3[(faust_wrap_add(i, fYec3_idx)) & 4095] = fZec41[i] * fZec42[i];
			}
			/* Post code */
			fYec3_idx_save = vsize;
			/* Vectorizable loop 48 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec43[i] = 0.18 * fYec3[(faust_wrap_sub(faust_wrap_add(i, fYec3_idx), iConst19)) & 4095];
			}
			/* Recursive loop 49 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fRec12_tmp[j2] = fRec12_perm[j2];
			}
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				fRec11_tmp[j4] = fRec11_perm[j4];
			}
			fYec2_idx = (faust_wrap_add(fYec2_idx, fYec2_idx_save)) & 32767;
			fYec4_idx = (faust_wrap_add(fYec4_idx, fYec4_idx_save)) & 2047;
			for (int j98 = 0; j98 < 4; j98 = faust_wrap_add(j98, 1)) {
				fRec9_tmp[j98] = fRec9_perm[j98];
			}
			for (int j100 = 0; j100 < 4; j100 = faust_wrap_add(j100, 1)) {
				fRec61_tmp[j100] = fRec61_perm[j100];
			}
			for (int j102 = 0; j102 < 4; j102 = faust_wrap_add(j102, 1)) {
				fRec60_tmp[j102] = fRec60_perm[j102];
			}
			fYec5_idx = (faust_wrap_add(fYec5_idx, fYec5_idx_save)) & 32767;
			fYec6_idx = (faust_wrap_add(fYec6_idx, fYec6_idx_save)) & 4095;
			for (int j104 = 0; j104 < 4; j104 = faust_wrap_add(j104, 1)) {
				fRec58_tmp[j104] = fRec58_perm[j104];
			}
			for (int j106 = 0; j106 < 4; j106 = faust_wrap_add(j106, 1)) {
				fRec65_tmp[j106] = fRec65_perm[j106];
			}
			for (int j108 = 0; j108 < 4; j108 = faust_wrap_add(j108, 1)) {
				fRec64_tmp[j108] = fRec64_perm[j108];
			}
			fYec7_idx = (faust_wrap_add(fYec7_idx, fYec7_idx_save)) & 16383;
			fYec8_idx = (faust_wrap_add(fYec8_idx, fYec8_idx_save)) & 4095;
			for (int j110 = 0; j110 < 4; j110 = faust_wrap_add(j110, 1)) {
				fRec62_tmp[j110] = fRec62_perm[j110];
			}
			for (int j112 = 0; j112 < 4; j112 = faust_wrap_add(j112, 1)) {
				fRec69_tmp[j112] = fRec69_perm[j112];
			}
			for (int j114 = 0; j114 < 4; j114 = faust_wrap_add(j114, 1)) {
				fRec68_tmp[j114] = fRec68_perm[j114];
			}
			fYec9_idx = (faust_wrap_add(fYec9_idx, fYec9_idx_save)) & 32767;
			fYec10_idx = (faust_wrap_add(fYec10_idx, fYec10_idx_save)) & 4095;
			for (int j116 = 0; j116 < 4; j116 = faust_wrap_add(j116, 1)) {
				fRec66_tmp[j116] = fRec66_perm[j116];
			}
			for (int j118 = 0; j118 < 4; j118 = faust_wrap_add(j118, 1)) {
				fRec73_tmp[j118] = fRec73_perm[j118];
			}
			for (int j120 = 0; j120 < 4; j120 = faust_wrap_add(j120, 1)) {
				fRec72_tmp[j120] = fRec72_perm[j120];
			}
			fYec11_idx = (faust_wrap_add(fYec11_idx, fYec11_idx_save)) & 16383;
			fYec12_idx = (faust_wrap_add(fYec12_idx, fYec12_idx_save)) & 2047;
			for (int j122 = 0; j122 < 4; j122 = faust_wrap_add(j122, 1)) {
				fRec70_tmp[j122] = fRec70_perm[j122];
			}
			for (int j124 = 0; j124 < 4; j124 = faust_wrap_add(j124, 1)) {
				fRec77_tmp[j124] = fRec77_perm[j124];
			}
			for (int j126 = 0; j126 < 4; j126 = faust_wrap_add(j126, 1)) {
				fRec76_tmp[j126] = fRec76_perm[j126];
			}
			fYec13_idx = (faust_wrap_add(fYec13_idx, fYec13_idx_save)) & 16383;
			fYec14_idx = (faust_wrap_add(fYec14_idx, fYec14_idx_save)) & 4095;
			for (int j128 = 0; j128 < 4; j128 = faust_wrap_add(j128, 1)) {
				fRec74_tmp[j128] = fRec74_perm[j128];
			}
			for (int j130 = 0; j130 < 4; j130 = faust_wrap_add(j130, 1)) {
				fRec81_tmp[j130] = fRec81_perm[j130];
			}
			for (int j132 = 0; j132 < 4; j132 = faust_wrap_add(j132, 1)) {
				fRec80_tmp[j132] = fRec80_perm[j132];
			}
			fYec15_idx = (faust_wrap_add(fYec15_idx, fYec15_idx_save)) & 16383;
			fYec16_idx = (faust_wrap_add(fYec16_idx, fYec16_idx_save)) & 4095;
			for (int j134 = 0; j134 < 4; j134 = faust_wrap_add(j134, 1)) {
				fRec78_tmp[j134] = fRec78_perm[j134];
			}
			for (int j136 = 0; j136 < 4; j136 = faust_wrap_add(j136, 1)) {
				fRec85_tmp[j136] = fRec85_perm[j136];
			}
			for (int j138 = 0; j138 < 4; j138 = faust_wrap_add(j138, 1)) {
				fRec84_tmp[j138] = fRec84_perm[j138];
			}
			fYec17_idx = (faust_wrap_add(fYec17_idx, fYec17_idx_save)) & 16383;
			fYec18_idx = (faust_wrap_add(fYec18_idx, fYec18_idx_save)) & 2047;
			for (int j140 = 0; j140 < 4; j140 = faust_wrap_add(j140, 1)) {
				fRec82_tmp[j140] = fRec82_perm[j140];
			}
			for (int j142 = 0; j142 < 4; j142 = faust_wrap_add(j142, 1)) {
				fRec1_tmp[j142] = fRec1_perm[j142];
			}
			for (int j144 = 0; j144 < 4; j144 = faust_wrap_add(j144, 1)) {
				fRec2_tmp[j144] = fRec2_perm[j144];
			}
			for (int j146 = 0; j146 < 4; j146 = faust_wrap_add(j146, 1)) {
				fRec3_tmp[j146] = fRec3_perm[j146];
			}
			for (int j148 = 0; j148 < 4; j148 = faust_wrap_add(j148, 1)) {
				fRec4_tmp[j148] = fRec4_perm[j148];
			}
			for (int j150 = 0; j150 < 4; j150 = faust_wrap_add(j150, 1)) {
				fRec5_tmp[j150] = fRec5_perm[j150];
			}
			for (int j152 = 0; j152 < 4; j152 = faust_wrap_add(j152, 1)) {
				fRec6_tmp[j152] = fRec6_perm[j152];
			}
			for (int j154 = 0; j154 < 4; j154 = faust_wrap_add(j154, 1)) {
				fRec7_tmp[j154] = fRec7_perm[j154];
			}
			for (int j156 = 0; j156 < 4; j156 = faust_wrap_add(j156, 1)) {
				fRec8_tmp[j156] = fRec8_perm[j156];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec12[i] = -(fConst2 * (fConst3 * fRec12[faust_wrap_sub(i, 1)] - (fRec8[faust_wrap_sub(i, 1)] + fRec8[faust_wrap_sub(i, 2)])));
				fRec11[i] = fSlow8 * fRec11[faust_wrap_sub(i, 1)] + fSlow9 * (fRec8[faust_wrap_sub(i, 1)] + fSlow10 * fRec12[i]);
				fYec2[(faust_wrap_add(i, fYec2_idx)) & 32767] = 0.35355339059327373 * fRec11[i] + 1e-20;
				fZec40[i] = 0.6 * fRec9[faust_wrap_sub(i, 1)] + fYec2[(faust_wrap_sub(faust_wrap_add(i, fYec2_idx), iConst18)) & 32767];
				fYec4[(faust_wrap_add(i, fYec4_idx)) & 2047] = fZec40[i] - fZec43[i];
				fRec9[i] = fYec4[(faust_wrap_sub(faust_wrap_add(i, fYec4_idx), iConst20)) & 2047];
				fRec10[i] = 0.6 * (fZec43[i] - fZec40[i]);
				fRec61[i] = -(fConst2 * (fConst3 * fRec61[faust_wrap_sub(i, 1)] - (fRec4[faust_wrap_sub(i, 1)] + fRec4[faust_wrap_sub(i, 2)])));
				fRec60[i] = fSlow45 * fRec60[faust_wrap_sub(i, 1)] + fSlow46 * (fRec4[faust_wrap_sub(i, 1)] + fSlow47 * fRec61[i]);
				fYec5[(faust_wrap_add(i, fYec5_idx)) & 32767] = 0.35355339059327373 * fRec60[i] + 1e-20;
				fZec44[i] = 0.6 * fRec58[faust_wrap_sub(i, 1)] + fYec5[(faust_wrap_sub(faust_wrap_add(i, fYec5_idx), iConst26)) & 32767];
				fYec6[(faust_wrap_add(i, fYec6_idx)) & 4095] = fZec44[i] - fZec43[i];
				fRec58[i] = fYec6[(faust_wrap_sub(faust_wrap_add(i, fYec6_idx), iConst27)) & 4095];
				fRec59[i] = 0.6 * (fZec43[i] - fZec44[i]);
				fRec65[i] = -(fConst2 * (fConst3 * fRec65[faust_wrap_sub(i, 1)] - (fRec6[faust_wrap_sub(i, 1)] + fRec6[faust_wrap_sub(i, 2)])));
				fRec64[i] = fSlow54 * fRec64[faust_wrap_sub(i, 1)] + fSlow55 * (fRec6[faust_wrap_sub(i, 1)] + fSlow56 * fRec65[i]);
				fYec7[(faust_wrap_add(i, fYec7_idx)) & 16383] = 0.35355339059327373 * fRec64[i] + 1e-20;
				fYec8[(faust_wrap_add(i, fYec8_idx)) & 4095] = fYec7[(faust_wrap_sub(faust_wrap_add(i, fYec7_idx), iConst33)) & 16383] + fZec43[i] + 0.6 * fRec62[faust_wrap_sub(i, 1)];
				fRec62[i] = fYec8[(faust_wrap_sub(faust_wrap_add(i, fYec8_idx), iConst34)) & 4095];
				fRec63[i] = -(0.6 * fYec8[(faust_wrap_add(i, fYec8_idx)) & 4095]);
				fRec69[i] = -(fConst2 * (fConst3 * fRec69[faust_wrap_sub(i, 1)] - (fRec2[faust_wrap_sub(i, 1)] + fRec2[faust_wrap_sub(i, 2)])));
				fRec68[i] = fSlow63 * fRec68[faust_wrap_sub(i, 1)] + fSlow64 * (fRec2[faust_wrap_sub(i, 1)] + fSlow65 * fRec69[i]);
				fYec9[(faust_wrap_add(i, fYec9_idx)) & 32767] = 0.35355339059327373 * fRec68[i] + 1e-20;
				fYec10[(faust_wrap_add(i, fYec10_idx)) & 4095] = fYec9[(faust_wrap_sub(faust_wrap_add(i, fYec9_idx), iConst40)) & 32767] + fZec43[i] + 0.6 * fRec66[faust_wrap_sub(i, 1)];
				fRec66[i] = fYec10[(faust_wrap_sub(faust_wrap_add(i, fYec10_idx), iConst41)) & 4095];
				fRec67[i] = -(0.6 * fYec10[(faust_wrap_add(i, fYec10_idx)) & 4095]);
				fRec73[i] = -(fConst2 * (fConst3 * fRec73[faust_wrap_sub(i, 1)] - (fRec7[faust_wrap_sub(i, 1)] + fRec7[faust_wrap_sub(i, 2)])));
				fRec72[i] = fSlow72 * fRec72[faust_wrap_sub(i, 1)] + fSlow73 * (fRec7[faust_wrap_sub(i, 1)] + fSlow74 * fRec73[i]);
				fYec11[(faust_wrap_add(i, fYec11_idx)) & 16383] = 0.35355339059327373 * fRec72[i] + 1e-20;
				fYec12[(faust_wrap_add(i, fYec12_idx)) & 2047] = fYec11[(faust_wrap_sub(faust_wrap_add(i, fYec11_idx), iConst47)) & 16383] - (fZec43[i] + 0.6 * fRec70[faust_wrap_sub(i, 1)]);
				fRec70[i] = fYec12[(faust_wrap_sub(faust_wrap_add(i, fYec12_idx), iConst48)) & 2047];
				fRec71[i] = 0.6 * fYec12[(faust_wrap_add(i, fYec12_idx)) & 2047];
				fRec77[i] = -(fConst2 * (fConst3 * fRec77[faust_wrap_sub(i, 1)] - (fRec3[faust_wrap_sub(i, 1)] + fRec3[faust_wrap_sub(i, 2)])));
				fRec76[i] = fSlow81 * fRec76[faust_wrap_sub(i, 1)] + fSlow82 * (fRec3[faust_wrap_sub(i, 1)] + fSlow83 * fRec77[i]);
				fYec13[(faust_wrap_add(i, fYec13_idx)) & 16383] = 0.35355339059327373 * fRec76[i] + 1e-20;
				fYec14[(faust_wrap_add(i, fYec14_idx)) & 4095] = fYec13[(faust_wrap_sub(faust_wrap_add(i, fYec13_idx), iConst54)) & 16383] - (fZec43[i] + 0.6 * fRec74[faust_wrap_sub(i, 1)]);
				fRec74[i] = fYec14[(faust_wrap_sub(faust_wrap_add(i, fYec14_idx), iConst55)) & 4095];
				fRec75[i] = 0.6 * fYec14[(faust_wrap_add(i, fYec14_idx)) & 4095];
				fRec81[i] = -(fConst2 * (fConst3 * fRec81[faust_wrap_sub(i, 1)] - (fRec5[faust_wrap_sub(i, 1)] + fRec5[faust_wrap_sub(i, 2)])));
				fRec80[i] = fSlow90 * fRec80[faust_wrap_sub(i, 1)] + fSlow91 * (fRec5[faust_wrap_sub(i, 1)] + fSlow92 * fRec81[i]);
				fYec15[(faust_wrap_add(i, fYec15_idx)) & 16383] = 0.35355339059327373 * fRec80[i] + 1e-20;
				fYec16[(faust_wrap_add(i, fYec16_idx)) & 4095] = fZec43[i] + fYec15[(faust_wrap_sub(faust_wrap_add(i, fYec15_idx), iConst61)) & 16383] - 0.6 * fRec78[faust_wrap_sub(i, 1)];
				fRec78[i] = fYec16[(faust_wrap_sub(faust_wrap_add(i, fYec16_idx), iConst62)) & 4095];
				fRec79[i] = 0.6 * fYec16[(faust_wrap_add(i, fYec16_idx)) & 4095];
				fRec85[i] = -(fConst2 * (fConst3 * fRec85[faust_wrap_sub(i, 1)] - (fRec1[faust_wrap_sub(i, 1)] + fRec1[faust_wrap_sub(i, 2)])));
				fRec84[i] = fSlow99 * fRec84[faust_wrap_sub(i, 1)] + fSlow100 * (fRec1[faust_wrap_sub(i, 1)] + fSlow101 * fRec85[i]);
				fYec17[(faust_wrap_add(i, fYec17_idx)) & 16383] = 0.35355339059327373 * fRec84[i] + 1e-20;
				fYec18[(faust_wrap_add(i, fYec18_idx)) & 2047] = fYec17[(faust_wrap_sub(faust_wrap_add(i, fYec17_idx), iConst68)) & 16383] + fZec43[i] - 0.6 * fRec82[faust_wrap_sub(i, 1)];
				fRec82[i] = fYec18[(faust_wrap_sub(faust_wrap_add(i, fYec18_idx), iConst69)) & 2047];
				fRec83[i] = 0.6 * fYec18[(faust_wrap_add(i, fYec18_idx)) & 2047];
				fZec45[i] = fRec83[i] + fRec79[i];
				fZec46[i] = fRec71[i] + fRec75[i] + fZec45[i];
				fRec1[i] = fRec9[faust_wrap_sub(i, 1)] + fRec58[faust_wrap_sub(i, 1)] + fRec62[faust_wrap_sub(i, 1)] + fRec66[faust_wrap_sub(i, 1)] + fRec70[faust_wrap_sub(i, 1)] + fRec74[faust_wrap_sub(i, 1)] + fRec78[faust_wrap_sub(i, 1)] + fRec82[faust_wrap_sub(i, 1)] + fRec10[i] + fRec59[i] + fRec63[i] + fRec67[i] + fZec46[i];
				fRec2[i] = fRec70[faust_wrap_sub(i, 1)] + fRec74[faust_wrap_sub(i, 1)] + fRec78[faust_wrap_sub(i, 1)] + fRec82[faust_wrap_sub(i, 1)] + fZec46[i] - (fRec9[faust_wrap_sub(i, 1)] + fRec58[faust_wrap_sub(i, 1)] + fRec62[faust_wrap_sub(i, 1)] + fRec66[faust_wrap_sub(i, 1)] + fRec10[i] + fRec59[i] + fRec67[i] + fRec63[i]);
				fZec47[i] = fRec75[i] + fRec71[i];
				fRec3[i] = fRec62[faust_wrap_sub(i, 1)] + fRec66[faust_wrap_sub(i, 1)] + fRec78[faust_wrap_sub(i, 1)] + fRec82[faust_wrap_sub(i, 1)] + fRec63[i] + fRec67[i] + fZec45[i] - (fRec9[faust_wrap_sub(i, 1)] + fRec58[faust_wrap_sub(i, 1)] + fRec70[faust_wrap_sub(i, 1)] + fRec74[faust_wrap_sub(i, 1)] + fRec10[i] + fRec59[i] + fZec47[i]);
				fRec4[i] = fRec9[faust_wrap_sub(i, 1)] + fRec58[faust_wrap_sub(i, 1)] + fRec78[faust_wrap_sub(i, 1)] + fRec82[faust_wrap_sub(i, 1)] + fRec10[i] + fRec59[i] + fZec45[i] - (fRec62[faust_wrap_sub(i, 1)] + fRec66[faust_wrap_sub(i, 1)] + fRec70[faust_wrap_sub(i, 1)] + fRec74[faust_wrap_sub(i, 1)] + fRec63[i] + fRec67[i] + fZec47[i]);
				fZec48[i] = fRec83[i] + fRec75[i];
				fZec49[i] = fRec79[i] + fRec71[i];
				fRec5[i] = fRec58[faust_wrap_sub(i, 1)] + fRec66[faust_wrap_sub(i, 1)] + fRec74[faust_wrap_sub(i, 1)] + fRec82[faust_wrap_sub(i, 1)] + fRec59[i] + fRec67[i] + fZec48[i] - (fRec9[faust_wrap_sub(i, 1)] + fRec62[faust_wrap_sub(i, 1)] + fRec70[faust_wrap_sub(i, 1)] + fRec78[faust_wrap_sub(i, 1)] + fRec10[i] + fRec63[i] + fZec49[i]);
				fRec6[i] = fRec9[faust_wrap_sub(i, 1)] + fRec62[faust_wrap_sub(i, 1)] + fRec74[faust_wrap_sub(i, 1)] + fRec82[faust_wrap_sub(i, 1)] + fRec10[i] + fRec63[i] + fZec48[i] - (fRec58[faust_wrap_sub(i, 1)] + fRec66[faust_wrap_sub(i, 1)] + fRec70[faust_wrap_sub(i, 1)] + fRec78[faust_wrap_sub(i, 1)] + fRec59[i] + fRec67[i] + fZec49[i]);
				fZec50[i] = fRec83[i] + fRec71[i];
				fZec51[i] = fRec79[i] + fRec75[i];
				fRec7[i] = fRec9[faust_wrap_sub(i, 1)] + fRec66[faust_wrap_sub(i, 1)] + fRec70[faust_wrap_sub(i, 1)] + fRec82[faust_wrap_sub(i, 1)] + fRec10[i] + fRec67[i] + fZec50[i] - (fRec58[faust_wrap_sub(i, 1)] + fRec62[faust_wrap_sub(i, 1)] + fRec74[faust_wrap_sub(i, 1)] + fRec78[faust_wrap_sub(i, 1)] + fRec59[i] + fRec63[i] + fZec51[i]);
				fRec8[i] = fRec58[faust_wrap_sub(i, 1)] + fRec62[faust_wrap_sub(i, 1)] + fRec70[faust_wrap_sub(i, 1)] + fRec82[faust_wrap_sub(i, 1)] + fRec59[i] + fRec63[i] + fZec50[i] - (fRec9[faust_wrap_sub(i, 1)] + fRec66[faust_wrap_sub(i, 1)] + fRec74[faust_wrap_sub(i, 1)] + fRec78[faust_wrap_sub(i, 1)] + fRec10[i] + fRec67[i] + fZec51[i]);
			}
			/* Post code */
			fYec17_idx_save = vsize;
			fYec18_idx_save = vsize;
			for (int j137 = 0; j137 < 4; j137 = faust_wrap_add(j137, 1)) {
				fRec85_perm[j137] = fRec85_tmp[faust_wrap_add(vsize, j137)];
			}
			for (int j139 = 0; j139 < 4; j139 = faust_wrap_add(j139, 1)) {
				fRec84_perm[j139] = fRec84_tmp[faust_wrap_add(vsize, j139)];
			}
			for (int j141 = 0; j141 < 4; j141 = faust_wrap_add(j141, 1)) {
				fRec82_perm[j141] = fRec82_tmp[faust_wrap_add(vsize, j141)];
			}
			fYec15_idx_save = vsize;
			fYec16_idx_save = vsize;
			for (int j131 = 0; j131 < 4; j131 = faust_wrap_add(j131, 1)) {
				fRec81_perm[j131] = fRec81_tmp[faust_wrap_add(vsize, j131)];
			}
			for (int j133 = 0; j133 < 4; j133 = faust_wrap_add(j133, 1)) {
				fRec80_perm[j133] = fRec80_tmp[faust_wrap_add(vsize, j133)];
			}
			for (int j135 = 0; j135 < 4; j135 = faust_wrap_add(j135, 1)) {
				fRec78_perm[j135] = fRec78_tmp[faust_wrap_add(vsize, j135)];
			}
			fYec13_idx_save = vsize;
			fYec14_idx_save = vsize;
			for (int j125 = 0; j125 < 4; j125 = faust_wrap_add(j125, 1)) {
				fRec77_perm[j125] = fRec77_tmp[faust_wrap_add(vsize, j125)];
			}
			for (int j127 = 0; j127 < 4; j127 = faust_wrap_add(j127, 1)) {
				fRec76_perm[j127] = fRec76_tmp[faust_wrap_add(vsize, j127)];
			}
			for (int j129 = 0; j129 < 4; j129 = faust_wrap_add(j129, 1)) {
				fRec74_perm[j129] = fRec74_tmp[faust_wrap_add(vsize, j129)];
			}
			fYec11_idx_save = vsize;
			fYec12_idx_save = vsize;
			for (int j119 = 0; j119 < 4; j119 = faust_wrap_add(j119, 1)) {
				fRec73_perm[j119] = fRec73_tmp[faust_wrap_add(vsize, j119)];
			}
			for (int j121 = 0; j121 < 4; j121 = faust_wrap_add(j121, 1)) {
				fRec72_perm[j121] = fRec72_tmp[faust_wrap_add(vsize, j121)];
			}
			for (int j123 = 0; j123 < 4; j123 = faust_wrap_add(j123, 1)) {
				fRec70_perm[j123] = fRec70_tmp[faust_wrap_add(vsize, j123)];
			}
			fYec9_idx_save = vsize;
			fYec10_idx_save = vsize;
			for (int j113 = 0; j113 < 4; j113 = faust_wrap_add(j113, 1)) {
				fRec69_perm[j113] = fRec69_tmp[faust_wrap_add(vsize, j113)];
			}
			for (int j115 = 0; j115 < 4; j115 = faust_wrap_add(j115, 1)) {
				fRec68_perm[j115] = fRec68_tmp[faust_wrap_add(vsize, j115)];
			}
			for (int j117 = 0; j117 < 4; j117 = faust_wrap_add(j117, 1)) {
				fRec66_perm[j117] = fRec66_tmp[faust_wrap_add(vsize, j117)];
			}
			fYec7_idx_save = vsize;
			fYec8_idx_save = vsize;
			for (int j107 = 0; j107 < 4; j107 = faust_wrap_add(j107, 1)) {
				fRec65_perm[j107] = fRec65_tmp[faust_wrap_add(vsize, j107)];
			}
			for (int j109 = 0; j109 < 4; j109 = faust_wrap_add(j109, 1)) {
				fRec64_perm[j109] = fRec64_tmp[faust_wrap_add(vsize, j109)];
			}
			for (int j111 = 0; j111 < 4; j111 = faust_wrap_add(j111, 1)) {
				fRec62_perm[j111] = fRec62_tmp[faust_wrap_add(vsize, j111)];
			}
			fYec5_idx_save = vsize;
			fYec6_idx_save = vsize;
			for (int j101 = 0; j101 < 4; j101 = faust_wrap_add(j101, 1)) {
				fRec61_perm[j101] = fRec61_tmp[faust_wrap_add(vsize, j101)];
			}
			for (int j103 = 0; j103 < 4; j103 = faust_wrap_add(j103, 1)) {
				fRec60_perm[j103] = fRec60_tmp[faust_wrap_add(vsize, j103)];
			}
			for (int j105 = 0; j105 < 4; j105 = faust_wrap_add(j105, 1)) {
				fRec58_perm[j105] = fRec58_tmp[faust_wrap_add(vsize, j105)];
			}
			fYec2_idx_save = vsize;
			fYec4_idx_save = vsize;
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fRec12_perm[j3] = fRec12_tmp[faust_wrap_add(vsize, j3)];
			}
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fRec11_perm[j5] = fRec11_tmp[faust_wrap_add(vsize, j5)];
			}
			for (int j99 = 0; j99 < 4; j99 = faust_wrap_add(j99, 1)) {
				fRec9_perm[j99] = fRec9_tmp[faust_wrap_add(vsize, j99)];
			}
			for (int j143 = 0; j143 < 4; j143 = faust_wrap_add(j143, 1)) {
				fRec1_perm[j143] = fRec1_tmp[faust_wrap_add(vsize, j143)];
			}
			for (int j145 = 0; j145 < 4; j145 = faust_wrap_add(j145, 1)) {
				fRec2_perm[j145] = fRec2_tmp[faust_wrap_add(vsize, j145)];
			}
			for (int j147 = 0; j147 < 4; j147 = faust_wrap_add(j147, 1)) {
				fRec3_perm[j147] = fRec3_tmp[faust_wrap_add(vsize, j147)];
			}
			for (int j149 = 0; j149 < 4; j149 = faust_wrap_add(j149, 1)) {
				fRec4_perm[j149] = fRec4_tmp[faust_wrap_add(vsize, j149)];
			}
			for (int j151 = 0; j151 < 4; j151 = faust_wrap_add(j151, 1)) {
				fRec5_perm[j151] = fRec5_tmp[faust_wrap_add(vsize, j151)];
			}
			for (int j153 = 0; j153 < 4; j153 = faust_wrap_add(j153, 1)) {
				fRec6_perm[j153] = fRec6_tmp[faust_wrap_add(vsize, j153)];
			}
			for (int j155 = 0; j155 < 4; j155 = faust_wrap_add(j155, 1)) {
				fRec7_perm[j155] = fRec7_tmp[faust_wrap_add(vsize, j155)];
			}
			for (int j157 = 0; j157 < 4; j157 = faust_wrap_add(j157, 1)) {
				fRec8_perm[j157] = fRec8_tmp[faust_wrap_add(vsize, j157)];
			}
			/* Vectorizable loop 50 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec52[i] = std::max<double>(0.75, std::min<double>(4.0, fRec0[i]));
			}
			/* Vectorizable loop 51 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec53[i] = 0.6 * fZec41[i] * (1.0 - fZec42[i]);
			}
			/* Vectorizable loop 52 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fZec52[i] * (0.37 * (fRec2[i] + fRec3[i]) + fZec53[i]));
			}
			/* Vectorizable loop 53 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fZec52[i] * (fZec53[i] + 0.37 * (fRec2[i] - fRec3[i])));
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
