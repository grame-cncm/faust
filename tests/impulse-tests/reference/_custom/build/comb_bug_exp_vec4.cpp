/* ------------------------------------------------------------
name: "comb_bug"
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
	
	int iRec2_perm[4];
	FAUSTFLOAT fButton0;
	double fVec0_perm[4];
	int iRec3_perm[4];
	double fRec4_perm[4];
	int iRec5_perm[4];
	int fSampleRate;
	double fConst0;
	double fConst1;
	double fConst2;
	FAUSTFLOAT fHslider0;
	double fRec6_perm[4];
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT fHslider4;
	double fConst3;
	double fConst4;
	double fYec0[2048];
	int fYec0_idx;
	int fYec0_idx_save;
	double fConst5;
	double fConst6;
	double fRec0_perm[4];
	FAUSTFLOAT fHslider5;
	double fRec7_perm[4];
	double fYec1_perm[4];
	
 public:
	mydsp() {
	}
	
	mydsp(const mydsp&) = default;
	
	virtual ~mydsp() = default;
	
	mydsp& operator=(const mydsp&) = default;
	
	void metadata(Meta* m) { 
		m->declare("basics_lib_name", "Faust Basic Element Library");
		m->declare("basics_lib_version", "0.1");
		m->declare("compilation_options", "-single -scal -e comb_bug.dsp -o comb_bug_exp.dsp");
		m->declare("compile_options", "-a /Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/archs/impulsearch.cpp -lang cpp -i -fpga-mem-th 4 -ct 1 -es 1 -mcd 4 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs");
		m->declare("delays_lib_name", "Faust Delay Library");
		m->declare("delays_lib_version", "0.1");
		m->declare("envelopes_lib_adsr_author", "Yann Orlarey");
		m->declare("envelopes_lib_ar_author", "Yann Orlarey, Stéphane Letz");
		m->declare("envelopes_lib_author", "GRAME");
		m->declare("envelopes_lib_copyright", "GRAME");
		m->declare("envelopes_lib_license", "LGPL with exception");
		m->declare("envelopes_lib_name", "Faust Envelope Library");
		m->declare("envelopes_lib_version", "0.0");
		m->declare("filename", "comb_bug.dsp");
		m->declare("filters_lib_fb_fcomb_author", "Julius O. Smith III");
		m->declare("filters_lib_fb_fcomb_copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters_lib_fb_fcomb_license", "MIT-style STK-4.3 license");
		m->declare("filters_lib_lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters_lib_name", "Faust Filters Library");
		m->declare("library_path", "/usr/local/share/faust/stdfaust.lib");
		m->declare("maths_lib_author", "GRAME");
		m->declare("maths_lib_copyright", "GRAME");
		m->declare("maths_lib_license", "LGPL with exception");
		m->declare("maths_lib_name", "Faust Math Library");
		m->declare("maths_lib_version", "2.1");
		m->declare("name", "comb_bug");
		m->declare("noises_lib_name", "Faust Noise Generator Library");
		m->declare("noises_lib_version", "0.0");
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
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, static_cast<double>(fSampleRate)));
		fConst1 = std::exp(-(1e+03 / fConst0));
		fConst2 = 1.0 - fConst1;
		fConst3 = 1.0 / std::max<double>(1.0, 0.1 * fConst0);
		fConst4 = 1.0 / std::max<double>(1.0, 0.01 * fConst0);
		fConst5 = 0.9993265 * fConst0;
		fConst6 = 1.0006735 * fConst0;
	}
	
	virtual void instanceResetUserInterface() {
		fButton0 = static_cast<FAUSTFLOAT>(0.0);
		fHslider0 = static_cast<FAUSTFLOAT>(2e+02);
		fHslider1 = static_cast<FAUSTFLOAT>(0.999);
		fHslider2 = static_cast<FAUSTFLOAT>(127.0);
		fHslider3 = static_cast<FAUSTFLOAT>(0.95);
		fHslider4 = static_cast<FAUSTFLOAT>(0.95);
		fHslider5 = static_cast<FAUSTFLOAT>(0.8);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 4; l0 = faust_wrap_add(l0, 1)) {
			iRec2_perm[l0] = 0;
		}
		for (int l1 = 0; l1 < 4; l1 = faust_wrap_add(l1, 1)) {
			fVec0_perm[l1] = 0.0;
		}
		for (int l2 = 0; l2 < 4; l2 = faust_wrap_add(l2, 1)) {
			iRec3_perm[l2] = 0;
		}
		for (int l3 = 0; l3 < 4; l3 = faust_wrap_add(l3, 1)) {
			fRec4_perm[l3] = 0.0;
		}
		for (int l4 = 0; l4 < 4; l4 = faust_wrap_add(l4, 1)) {
			iRec5_perm[l4] = 0;
		}
		for (int l5 = 0; l5 < 4; l5 = faust_wrap_add(l5, 1)) {
			fRec6_perm[l5] = 0.0;
		}
		for (int l6 = 0; l6 < 2048; l6 = faust_wrap_add(l6, 1)) {
			fYec0[l6] = 0.0;
		}
		fYec0_idx = 0;
		fYec0_idx_save = 0;
		for (int l7 = 0; l7 < 4; l7 = faust_wrap_add(l7, 1)) {
			fRec0_perm[l7] = 0.0;
		}
		for (int l8 = 0; l8 < 4; l8 = faust_wrap_add(l8, 1)) {
			fRec7_perm[l8] = 0.0;
		}
		for (int l9 = 0; l9 < 4; l9 = faust_wrap_add(l9, 1)) {
			fYec1_perm[l9] = 0.0;
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
		ui_interface->openVerticalBox("comb_bug");
		ui_interface->addHorizontalSlider("comb_res", &fHslider1, FAUSTFLOAT(0.999), FAUSTFLOAT(-0.999), FAUSTFLOAT(0.999), FAUSTFLOAT(0.01));
		ui_interface->addHorizontalSlider("env_a", &fHslider3, FAUSTFLOAT(0.95), FAUSTFLOAT(0.001), FAUSTFLOAT(1.0), FAUSTFLOAT(0.01));
		ui_interface->addHorizontalSlider("env_r", &fHslider4, FAUSTFLOAT(0.95), FAUSTFLOAT(0.001), FAUSTFLOAT(1.0), FAUSTFLOAT(0.01));
		ui_interface->addHorizontalSlider("freq", &fHslider0, FAUSTFLOAT(2e+02), FAUSTFLOAT(2e+02), FAUSTFLOAT(8e+02), FAUSTFLOAT(1.0));
		ui_interface->addHorizontalSlider("gain", &fHslider5, FAUSTFLOAT(0.8), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.01));
		ui_interface->addButton("gate", &fButton0);
		ui_interface->addHorizontalSlider("vitesse", &fHslider2, FAUSTFLOAT(127.0), FAUSTFLOAT(0.0), FAUSTFLOAT(127.0), FAUSTFLOAT(1.0));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* output0_ptr = outputs[0];
		FAUSTFLOAT* output1_ptr = outputs[1];
		int iRec2_tmp[8];
		int* iRec2 = &iRec2_tmp[4];
		double fSlow0 = static_cast<double>(fButton0);
		double fVec0_tmp[8];
		double* fVec0 = &fVec0_tmp[4];
		int iRec3_tmp[8];
		int* iRec3 = &iRec3_tmp[4];
		double fRec4_tmp[8];
		double* fRec4 = &fRec4_tmp[4];
		int iSlow1 = fSlow0 == 0.0;
		int iRec5_tmp[8];
		int* iRec5 = &iRec5_tmp[4];
		double fSlow2 = fConst2 * static_cast<double>(fHslider0);
		double fRec6_tmp[8];
		double* fRec6 = &fRec6_tmp[4];
		double fSlow3 = static_cast<double>(fHslider1);
		double fSlow4 = 3.666624311217163e-12 * static_cast<double>(fHslider2);
		double fSlow5 = std::max<double>(1.0, fConst0 * static_cast<double>(fHslider3));
		double fSlow6 = 1.0 / fSlow5;
		double fZec0[4];
		double fSlow7 = 1.0 / std::max<double>(1.0, fConst0 * static_cast<double>(fHslider4));
		double fZec1[4];
		double fZec2[4];
		double fZec3[4];
		double fZec4[4];
		int iZec5[4];
		double fZec6[4];
		double fRec0_tmp[8];
		double* fRec0 = &fRec0_tmp[4];
		double fRec1[4];
		double fSlow8 = 0.0010000000000000009 * static_cast<double>(fHslider5);
		double fRec7_tmp[8];
		double* fRec7 = &fRec7_tmp[4];
		double fYec1_tmp[8];
		double* fYec1 = &fYec1_tmp[4];
		double fZec7[4];
		int vindex = 0;
		/* Main loop */
		for (vindex = 0; vindex <= (faust_wrap_sub(count, 4)); vindex = faust_wrap_add(vindex, 4)) {
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			FAUSTFLOAT* output1 = &output1_ptr[vindex];
			int vsize = 4;
			/* Vectorizable loop 0 */
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
			/* Recursive loop 1 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				iRec3_tmp[j4] = iRec3_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iRec3[i] = faust_wrap_add(faust_wrap_mul(faust_wrap_add(iRec3[faust_wrap_sub(i, 1)], iRec3[faust_wrap_sub(i, 1)] > 0), fSlow0 <= fVec0[faust_wrap_sub(i, 1)]), fSlow0 > fVec0[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				iRec3_perm[j5] = iRec3_tmp[faust_wrap_add(vsize, j5)];
			}
			/* Recursive loop 2 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				iRec2_tmp[j0] = iRec2_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iRec2[i] = faust_wrap_add(faust_wrap_mul(1103515245, iRec2[faust_wrap_sub(i, 1)]), 12345);
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				iRec2_perm[j1] = iRec2_tmp[faust_wrap_add(vsize, j1)];
			}
			/* Recursive loop 3 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec4_tmp[j6] = fRec4_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec4[i] = fSlow0 + fRec4[faust_wrap_sub(i, 1)] * static_cast<double>(fVec0[faust_wrap_sub(i, 1)] >= fSlow0);
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec4_perm[j7] = fRec4_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Recursive loop 4 */
			/* Pre code */
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				iRec5_tmp[j8] = iRec5_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iRec5[i] = faust_wrap_mul(iSlow1, faust_wrap_add(iRec5[faust_wrap_sub(i, 1)], 1));
			}
			/* Post code */
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				iRec5_perm[j9] = iRec5_tmp[faust_wrap_add(vsize, j9)];
			}
			/* Recursive loop 5 */
			/* Pre code */
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				fRec6_tmp[j10] = fRec6_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec6[i] = fSlow2 + fConst1 * fRec6[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				fRec6_perm[j11] = fRec6_tmp[faust_wrap_add(vsize, j11)];
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec0[i] = static_cast<double>(iRec3[i]);
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec1[i] = fConst0 / fRec6[i];
			}
			/* Vectorizable loop 8 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec2[i] = fZec1[i] - std::floor(fZec1[i]);
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec3[i] = ((fZec2[i] <= 0.06) ? fConst6 / fRec6[i] : ((fZec2[i] >= 0.95) ? fConst5 / fRec6[i] : fZec1[i]));
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec4[i] = fZec3[i] + -1.0;
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec5[i] = static_cast<int>(fZec4[i]);
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec6[i] = std::floor(fZec4[i]);
			}
			/* Recursive loop 13 */
			/* Pre code */
			fYec0_idx = (faust_wrap_add(fYec0_idx, fYec0_idx_save)) & 2047;
			for (int j12 = 0; j12 < 4; j12 = faust_wrap_add(j12, 1)) {
				fRec0_tmp[j12] = fRec0_perm[j12];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec0[(faust_wrap_add(i, fYec0_idx)) & 2047] = fSlow3 * fRec0[faust_wrap_sub(i, 1)] + fSlow4 * static_cast<double>(iRec2[i]) * std::max<double>(0.0, std::min<double>(fSlow6 * fZec0[i], fSlow7 * (fSlow5 - fZec0[i]) + 1.0)) * std::max<double>(0.0, std::min<double>(fConst3 * fRec4[i], 1.0) - fConst4 * static_cast<double>(iRec5[i]));
				fRec0[i] = fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), std::min<int>(1025, std::max<int>(0, iZec5[i])))) & 2047] * (fZec6[i] + (2.0 - fZec3[i])) + (fZec3[i] + (-1.0 - fZec6[i])) * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), std::min<int>(1025, std::max<int>(0, faust_wrap_add(iZec5[i], 1))))) & 2047];
				fRec1[i] = fYec0[(faust_wrap_add(i, fYec0_idx)) & 2047];
			}
			/* Post code */
			fYec0_idx_save = vsize;
			for (int j13 = 0; j13 < 4; j13 = faust_wrap_add(j13, 1)) {
				fRec0_perm[j13] = fRec0_tmp[faust_wrap_add(vsize, j13)];
			}
			/* Recursive loop 14 */
			/* Pre code */
			for (int j14 = 0; j14 < 4; j14 = faust_wrap_add(j14, 1)) {
				fRec7_tmp[j14] = fRec7_perm[j14];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec7[i] = fSlow8 + 0.999 * fRec7[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j15 = 0; j15 < 4; j15 = faust_wrap_add(j15, 1)) {
				fRec7_perm[j15] = fRec7_tmp[faust_wrap_add(vsize, j15)];
			}
			/* Vectorizable loop 15 */
			/* Pre code */
			for (int j16 = 0; j16 < 4; j16 = faust_wrap_add(j16, 1)) {
				fYec1_tmp[j16] = fYec1_perm[j16];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec1[i] = fRec1[i] * fRec7[i];
			}
			/* Post code */
			for (int j17 = 0; j17 < 4; j17 = faust_wrap_add(j17, 1)) {
				fYec1_perm[j17] = fYec1_tmp[faust_wrap_add(vsize, j17)];
			}
			/* Vectorizable loop 16 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec7[i] = 0.3 * fYec1[faust_wrap_sub(i, 1)];
			}
			/* Vectorizable loop 17 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fZec7[i]);
			}
			/* Vectorizable loop 18 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fZec7[i]);
			}
		}
		/* Remaining frames */
		if (vindex < count) {
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			FAUSTFLOAT* output1 = &output1_ptr[vindex];
			int vsize = faust_wrap_sub(count, vindex);
			/* Vectorizable loop 0 */
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
			/* Recursive loop 1 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				iRec3_tmp[j4] = iRec3_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iRec3[i] = faust_wrap_add(faust_wrap_mul(faust_wrap_add(iRec3[faust_wrap_sub(i, 1)], iRec3[faust_wrap_sub(i, 1)] > 0), fSlow0 <= fVec0[faust_wrap_sub(i, 1)]), fSlow0 > fVec0[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				iRec3_perm[j5] = iRec3_tmp[faust_wrap_add(vsize, j5)];
			}
			/* Recursive loop 2 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				iRec2_tmp[j0] = iRec2_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iRec2[i] = faust_wrap_add(faust_wrap_mul(1103515245, iRec2[faust_wrap_sub(i, 1)]), 12345);
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				iRec2_perm[j1] = iRec2_tmp[faust_wrap_add(vsize, j1)];
			}
			/* Recursive loop 3 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec4_tmp[j6] = fRec4_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec4[i] = fSlow0 + fRec4[faust_wrap_sub(i, 1)] * static_cast<double>(fVec0[faust_wrap_sub(i, 1)] >= fSlow0);
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec4_perm[j7] = fRec4_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Recursive loop 4 */
			/* Pre code */
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				iRec5_tmp[j8] = iRec5_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iRec5[i] = faust_wrap_mul(iSlow1, faust_wrap_add(iRec5[faust_wrap_sub(i, 1)], 1));
			}
			/* Post code */
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				iRec5_perm[j9] = iRec5_tmp[faust_wrap_add(vsize, j9)];
			}
			/* Recursive loop 5 */
			/* Pre code */
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				fRec6_tmp[j10] = fRec6_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec6[i] = fSlow2 + fConst1 * fRec6[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				fRec6_perm[j11] = fRec6_tmp[faust_wrap_add(vsize, j11)];
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec0[i] = static_cast<double>(iRec3[i]);
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec1[i] = fConst0 / fRec6[i];
			}
			/* Vectorizable loop 8 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec2[i] = fZec1[i] - std::floor(fZec1[i]);
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec3[i] = ((fZec2[i] <= 0.06) ? fConst6 / fRec6[i] : ((fZec2[i] >= 0.95) ? fConst5 / fRec6[i] : fZec1[i]));
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec4[i] = fZec3[i] + -1.0;
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec5[i] = static_cast<int>(fZec4[i]);
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec6[i] = std::floor(fZec4[i]);
			}
			/* Recursive loop 13 */
			/* Pre code */
			fYec0_idx = (faust_wrap_add(fYec0_idx, fYec0_idx_save)) & 2047;
			for (int j12 = 0; j12 < 4; j12 = faust_wrap_add(j12, 1)) {
				fRec0_tmp[j12] = fRec0_perm[j12];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec0[(faust_wrap_add(i, fYec0_idx)) & 2047] = fSlow3 * fRec0[faust_wrap_sub(i, 1)] + fSlow4 * static_cast<double>(iRec2[i]) * std::max<double>(0.0, std::min<double>(fSlow6 * fZec0[i], fSlow7 * (fSlow5 - fZec0[i]) + 1.0)) * std::max<double>(0.0, std::min<double>(fConst3 * fRec4[i], 1.0) - fConst4 * static_cast<double>(iRec5[i]));
				fRec0[i] = fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), std::min<int>(1025, std::max<int>(0, iZec5[i])))) & 2047] * (fZec6[i] + (2.0 - fZec3[i])) + (fZec3[i] + (-1.0 - fZec6[i])) * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), std::min<int>(1025, std::max<int>(0, faust_wrap_add(iZec5[i], 1))))) & 2047];
				fRec1[i] = fYec0[(faust_wrap_add(i, fYec0_idx)) & 2047];
			}
			/* Post code */
			fYec0_idx_save = vsize;
			for (int j13 = 0; j13 < 4; j13 = faust_wrap_add(j13, 1)) {
				fRec0_perm[j13] = fRec0_tmp[faust_wrap_add(vsize, j13)];
			}
			/* Recursive loop 14 */
			/* Pre code */
			for (int j14 = 0; j14 < 4; j14 = faust_wrap_add(j14, 1)) {
				fRec7_tmp[j14] = fRec7_perm[j14];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec7[i] = fSlow8 + 0.999 * fRec7[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j15 = 0; j15 < 4; j15 = faust_wrap_add(j15, 1)) {
				fRec7_perm[j15] = fRec7_tmp[faust_wrap_add(vsize, j15)];
			}
			/* Vectorizable loop 15 */
			/* Pre code */
			for (int j16 = 0; j16 < 4; j16 = faust_wrap_add(j16, 1)) {
				fYec1_tmp[j16] = fYec1_perm[j16];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec1[i] = fRec1[i] * fRec7[i];
			}
			/* Post code */
			for (int j17 = 0; j17 < 4; j17 = faust_wrap_add(j17, 1)) {
				fYec1_perm[j17] = fYec1_tmp[faust_wrap_add(vsize, j17)];
			}
			/* Vectorizable loop 16 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec7[i] = 0.3 * fYec1[faust_wrap_sub(i, 1)];
			}
			/* Vectorizable loop 17 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fZec7[i]);
			}
			/* Vectorizable loop 18 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fZec7[i]);
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
