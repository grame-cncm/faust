/* ------------------------------------------------------------
author: "Grame"
name: "Harpe"
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

static double mydsp_faustpower2_f(double value) {
	return value * value;
}

class mydsp : public dsp {
	
 private:
	
	int iRec1_perm[4];
	FAUSTFLOAT fHslider0;
	double fRec3_perm[4];
	int iYec0_perm[4];
	double fRec2_perm[4];
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	double fYec1[128];
	int fYec1_idx;
	int fYec1_idx_save;
	double fRec0_perm[4];
	int iYec2_perm[4];
	double fRec5_perm[4];
	double fYec3[128];
	int fYec3_idx;
	int fYec3_idx_save;
	double fRec4_perm[4];
	int iYec4_perm[4];
	double fRec7_perm[4];
	double fYec5[128];
	int fYec5_idx;
	int fYec5_idx_save;
	double fRec6_perm[4];
	int iYec6_perm[4];
	double fRec9_perm[4];
	double fYec7[128];
	int fYec7_idx;
	int fYec7_idx_save;
	double fRec8_perm[4];
	int iYec8_perm[4];
	double fRec11_perm[4];
	double fYec9[64];
	int fYec9_idx;
	int fYec9_idx_save;
	double fRec10_perm[4];
	int iYec10_perm[4];
	double fRec13_perm[4];
	double fYec11[64];
	int fYec11_idx;
	int fYec11_idx_save;
	double fRec12_perm[4];
	int iYec12_perm[4];
	double fRec15_perm[4];
	double fYec13[64];
	int fYec13_idx;
	int fYec13_idx_save;
	double fRec14_perm[4];
	int iYec14_perm[4];
	double fRec17_perm[4];
	double fYec15[64];
	int fYec15_idx;
	int fYec15_idx_save;
	double fRec16_perm[4];
	int iYec16_perm[4];
	double fRec19_perm[4];
	double fYec17[64];
	int fYec17_idx;
	int fYec17_idx_save;
	double fRec18_perm[4];
	int iYec18_perm[4];
	double fRec21_perm[4];
	double fYec19[32];
	int fYec19_idx;
	int fYec19_idx_save;
	double fRec20_perm[4];
	int iYec20_perm[4];
	double fRec23_perm[4];
	double fYec21[32];
	int fYec21_idx;
	int fYec21_idx_save;
	double fRec22_perm[4];
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
		m->declare("filename", "harpe.dsp");
		m->declare("name", "Harpe");
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
		fHslider0 = static_cast<FAUSTFLOAT>(0.43);
		fHslider1 = static_cast<FAUSTFLOAT>(0.0);
		fHslider2 = static_cast<FAUSTFLOAT>(0.5);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 4; l0 = faust_wrap_add(l0, 1)) {
			iRec1_perm[l0] = 0;
		}
		for (int l1 = 0; l1 < 4; l1 = faust_wrap_add(l1, 1)) {
			fRec3_perm[l1] = 0.0;
		}
		for (int l2 = 0; l2 < 4; l2 = faust_wrap_add(l2, 1)) {
			iYec0_perm[l2] = 0;
		}
		for (int l3 = 0; l3 < 4; l3 = faust_wrap_add(l3, 1)) {
			fRec2_perm[l3] = 0.0;
		}
		for (int l4 = 0; l4 < 128; l4 = faust_wrap_add(l4, 1)) {
			fYec1[l4] = 0.0;
		}
		fYec1_idx = 0;
		fYec1_idx_save = 0;
		for (int l5 = 0; l5 < 4; l5 = faust_wrap_add(l5, 1)) {
			fRec0_perm[l5] = 0.0;
		}
		for (int l6 = 0; l6 < 4; l6 = faust_wrap_add(l6, 1)) {
			iYec2_perm[l6] = 0;
		}
		for (int l7 = 0; l7 < 4; l7 = faust_wrap_add(l7, 1)) {
			fRec5_perm[l7] = 0.0;
		}
		for (int l8 = 0; l8 < 128; l8 = faust_wrap_add(l8, 1)) {
			fYec3[l8] = 0.0;
		}
		fYec3_idx = 0;
		fYec3_idx_save = 0;
		for (int l9 = 0; l9 < 4; l9 = faust_wrap_add(l9, 1)) {
			fRec4_perm[l9] = 0.0;
		}
		for (int l10 = 0; l10 < 4; l10 = faust_wrap_add(l10, 1)) {
			iYec4_perm[l10] = 0;
		}
		for (int l11 = 0; l11 < 4; l11 = faust_wrap_add(l11, 1)) {
			fRec7_perm[l11] = 0.0;
		}
		for (int l12 = 0; l12 < 128; l12 = faust_wrap_add(l12, 1)) {
			fYec5[l12] = 0.0;
		}
		fYec5_idx = 0;
		fYec5_idx_save = 0;
		for (int l13 = 0; l13 < 4; l13 = faust_wrap_add(l13, 1)) {
			fRec6_perm[l13] = 0.0;
		}
		for (int l14 = 0; l14 < 4; l14 = faust_wrap_add(l14, 1)) {
			iYec6_perm[l14] = 0;
		}
		for (int l15 = 0; l15 < 4; l15 = faust_wrap_add(l15, 1)) {
			fRec9_perm[l15] = 0.0;
		}
		for (int l16 = 0; l16 < 128; l16 = faust_wrap_add(l16, 1)) {
			fYec7[l16] = 0.0;
		}
		fYec7_idx = 0;
		fYec7_idx_save = 0;
		for (int l17 = 0; l17 < 4; l17 = faust_wrap_add(l17, 1)) {
			fRec8_perm[l17] = 0.0;
		}
		for (int l18 = 0; l18 < 4; l18 = faust_wrap_add(l18, 1)) {
			iYec8_perm[l18] = 0;
		}
		for (int l19 = 0; l19 < 4; l19 = faust_wrap_add(l19, 1)) {
			fRec11_perm[l19] = 0.0;
		}
		for (int l20 = 0; l20 < 64; l20 = faust_wrap_add(l20, 1)) {
			fYec9[l20] = 0.0;
		}
		fYec9_idx = 0;
		fYec9_idx_save = 0;
		for (int l21 = 0; l21 < 4; l21 = faust_wrap_add(l21, 1)) {
			fRec10_perm[l21] = 0.0;
		}
		for (int l22 = 0; l22 < 4; l22 = faust_wrap_add(l22, 1)) {
			iYec10_perm[l22] = 0;
		}
		for (int l23 = 0; l23 < 4; l23 = faust_wrap_add(l23, 1)) {
			fRec13_perm[l23] = 0.0;
		}
		for (int l24 = 0; l24 < 64; l24 = faust_wrap_add(l24, 1)) {
			fYec11[l24] = 0.0;
		}
		fYec11_idx = 0;
		fYec11_idx_save = 0;
		for (int l25 = 0; l25 < 4; l25 = faust_wrap_add(l25, 1)) {
			fRec12_perm[l25] = 0.0;
		}
		for (int l26 = 0; l26 < 4; l26 = faust_wrap_add(l26, 1)) {
			iYec12_perm[l26] = 0;
		}
		for (int l27 = 0; l27 < 4; l27 = faust_wrap_add(l27, 1)) {
			fRec15_perm[l27] = 0.0;
		}
		for (int l28 = 0; l28 < 64; l28 = faust_wrap_add(l28, 1)) {
			fYec13[l28] = 0.0;
		}
		fYec13_idx = 0;
		fYec13_idx_save = 0;
		for (int l29 = 0; l29 < 4; l29 = faust_wrap_add(l29, 1)) {
			fRec14_perm[l29] = 0.0;
		}
		for (int l30 = 0; l30 < 4; l30 = faust_wrap_add(l30, 1)) {
			iYec14_perm[l30] = 0;
		}
		for (int l31 = 0; l31 < 4; l31 = faust_wrap_add(l31, 1)) {
			fRec17_perm[l31] = 0.0;
		}
		for (int l32 = 0; l32 < 64; l32 = faust_wrap_add(l32, 1)) {
			fYec15[l32] = 0.0;
		}
		fYec15_idx = 0;
		fYec15_idx_save = 0;
		for (int l33 = 0; l33 < 4; l33 = faust_wrap_add(l33, 1)) {
			fRec16_perm[l33] = 0.0;
		}
		for (int l34 = 0; l34 < 4; l34 = faust_wrap_add(l34, 1)) {
			iYec16_perm[l34] = 0;
		}
		for (int l35 = 0; l35 < 4; l35 = faust_wrap_add(l35, 1)) {
			fRec19_perm[l35] = 0.0;
		}
		for (int l36 = 0; l36 < 64; l36 = faust_wrap_add(l36, 1)) {
			fYec17[l36] = 0.0;
		}
		fYec17_idx = 0;
		fYec17_idx_save = 0;
		for (int l37 = 0; l37 < 4; l37 = faust_wrap_add(l37, 1)) {
			fRec18_perm[l37] = 0.0;
		}
		for (int l38 = 0; l38 < 4; l38 = faust_wrap_add(l38, 1)) {
			iYec18_perm[l38] = 0;
		}
		for (int l39 = 0; l39 < 4; l39 = faust_wrap_add(l39, 1)) {
			fRec21_perm[l39] = 0.0;
		}
		for (int l40 = 0; l40 < 32; l40 = faust_wrap_add(l40, 1)) {
			fYec19[l40] = 0.0;
		}
		fYec19_idx = 0;
		fYec19_idx_save = 0;
		for (int l41 = 0; l41 < 4; l41 = faust_wrap_add(l41, 1)) {
			fRec20_perm[l41] = 0.0;
		}
		for (int l42 = 0; l42 < 4; l42 = faust_wrap_add(l42, 1)) {
			iYec20_perm[l42] = 0;
		}
		for (int l43 = 0; l43 < 4; l43 = faust_wrap_add(l43, 1)) {
			fRec23_perm[l43] = 0.0;
		}
		for (int l44 = 0; l44 < 32; l44 = faust_wrap_add(l44, 1)) {
			fYec21[l44] = 0.0;
		}
		fYec21_idx = 0;
		fYec21_idx_save = 0;
		for (int l45 = 0; l45 < 4; l45 = faust_wrap_add(l45, 1)) {
			fRec22_perm[l45] = 0.0;
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
		ui_interface->openVerticalBox("Harpe");
		ui_interface->declare(&fHslider1, "osc", "/1/fader3");
		ui_interface->addHorizontalSlider("attenuation", &fHslider1, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(0.01), FAUSTFLOAT(0.001));
		ui_interface->declare(&fHslider0, "osc", "/accxyz/1 -10 10");
		ui_interface->addHorizontalSlider("hand", &fHslider0, FAUSTFLOAT(0.43), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.01));
		ui_interface->declare(&fHslider2, "osc", "/accxyz/0 -10 10");
		ui_interface->declare(&fHslider2, "unit", "f");
		ui_interface->addHorizontalSlider("level", &fHslider2, FAUSTFLOAT(0.5), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.01));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* output0_ptr = outputs[0];
		FAUSTFLOAT* output1_ptr = outputs[1];
		int iRec1_tmp[8];
		int* iRec1 = &iRec1_tmp[4];
		double fSlow0 = 0.09999999999999998 * static_cast<double>(fHslider0);
		double fRec3_tmp[8];
		double* fRec3 = &fRec3_tmp[4];
		double fZec0[4];
		double fZec1[4];
		int iYec0_tmp[8];
		int* iYec0 = &iYec0_tmp[4];
		double fRec2_tmp[8];
		double* fRec2 = &fRec2_tmp[4];
		double fSlow1 = 0.5 * (1.0 - static_cast<double>(fHslider1));
		double fSlow2 = 4.656612875245797e-10 * mydsp_faustpower2_f(static_cast<double>(fHslider2));
		double fZec2[4];
		double fRec0_tmp[8];
		double* fRec0 = &fRec0_tmp[4];
		int iYec2_tmp[8];
		int* iYec2 = &iYec2_tmp[4];
		double fRec5_tmp[8];
		double* fRec5 = &fRec5_tmp[4];
		double fRec4_tmp[8];
		double* fRec4 = &fRec4_tmp[4];
		int iYec4_tmp[8];
		int* iYec4 = &iYec4_tmp[4];
		double fRec7_tmp[8];
		double* fRec7 = &fRec7_tmp[4];
		double fRec6_tmp[8];
		double* fRec6 = &fRec6_tmp[4];
		int iYec6_tmp[8];
		int* iYec6 = &iYec6_tmp[4];
		double fRec9_tmp[8];
		double* fRec9 = &fRec9_tmp[4];
		double fRec8_tmp[8];
		double* fRec8 = &fRec8_tmp[4];
		int iYec8_tmp[8];
		int* iYec8 = &iYec8_tmp[4];
		double fRec11_tmp[8];
		double* fRec11 = &fRec11_tmp[4];
		double fRec10_tmp[8];
		double* fRec10 = &fRec10_tmp[4];
		int iYec10_tmp[8];
		int* iYec10 = &iYec10_tmp[4];
		double fRec13_tmp[8];
		double* fRec13 = &fRec13_tmp[4];
		double fRec12_tmp[8];
		double* fRec12 = &fRec12_tmp[4];
		int iYec12_tmp[8];
		int* iYec12 = &iYec12_tmp[4];
		double fRec15_tmp[8];
		double* fRec15 = &fRec15_tmp[4];
		double fRec14_tmp[8];
		double* fRec14 = &fRec14_tmp[4];
		int iYec14_tmp[8];
		int* iYec14 = &iYec14_tmp[4];
		double fRec17_tmp[8];
		double* fRec17 = &fRec17_tmp[4];
		double fRec16_tmp[8];
		double* fRec16 = &fRec16_tmp[4];
		int iYec16_tmp[8];
		int* iYec16 = &iYec16_tmp[4];
		double fRec19_tmp[8];
		double* fRec19 = &fRec19_tmp[4];
		double fRec18_tmp[8];
		double* fRec18 = &fRec18_tmp[4];
		int iYec18_tmp[8];
		int* iYec18 = &iYec18_tmp[4];
		double fRec21_tmp[8];
		double* fRec21 = &fRec21_tmp[4];
		double fRec20_tmp[8];
		double* fRec20 = &fRec20_tmp[4];
		int iYec20_tmp[8];
		int* iYec20 = &iYec20_tmp[4];
		double fRec23_tmp[8];
		double* fRec23 = &fRec23_tmp[4];
		double fRec22_tmp[8];
		double* fRec22 = &fRec22_tmp[4];
		double fZec3[4];
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
			/* Recursive loop 1 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fRec3_tmp[j2] = fRec3_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec3[i] = fSlow0 + 0.9 * fRec3[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fRec3_perm[j3] = fRec3_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Vectorizable loop 2 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec0[i] = std::min<double>(fRec3[i], fRec3[faust_wrap_sub(i, 1)]);
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec1[i] = std::max<double>(fRec3[i], fRec3[faust_wrap_sub(i, 1)]);
			}
			/* Vectorizable loop 4 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				iYec0_tmp[j4] = iYec0_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iYec0[i] = (fZec0[i] < 0.045454545454545456) & (0.045454545454545456 < fZec1[i]);
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				iYec0_perm[j5] = iYec0_tmp[faust_wrap_add(vsize, j5)];
			}
			/* Recursive loop 5 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec2_tmp[j6] = fRec2_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec2[i] = fRec2[faust_wrap_sub(i, 1)] + static_cast<double>(static_cast<double>(faust_wrap_sub(iYec0[i], iYec0[faust_wrap_sub(i, 1)])) > 0.0) - 0.009977324263038548 * static_cast<double>(fRec2[faust_wrap_sub(i, 1)] > 0.0);
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec2_perm[j7] = fRec2_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec2[i] = static_cast<double>(iRec1[i]);
			}
			/* Recursive loop 7 */
			/* Pre code */
			fYec1_idx = (faust_wrap_add(fYec1_idx, fYec1_idx_save)) & 127;
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fRec0_tmp[j8] = fRec0_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec1[(faust_wrap_add(i, fYec1_idx)) & 127] = fSlow1 * (fRec0[faust_wrap_sub(i, 1)] + fRec0[faust_wrap_sub(i, 2)]) + fSlow2 * fZec2[i] * static_cast<double>(fRec2[i] > 0.0);
				fRec0[i] = fYec1[(faust_wrap_sub(faust_wrap_add(i, fYec1_idx), 99)) & 127];
			}
			/* Post code */
			fYec1_idx_save = vsize;
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fRec0_perm[j9] = fRec0_tmp[faust_wrap_add(vsize, j9)];
			}
			/* Vectorizable loop 8 */
			/* Pre code */
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				iYec2_tmp[j10] = iYec2_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iYec2[i] = (fZec0[i] < 0.13636363636363635) & (0.13636363636363635 < fZec1[i]);
			}
			/* Post code */
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				iYec2_perm[j11] = iYec2_tmp[faust_wrap_add(vsize, j11)];
			}
			/* Recursive loop 9 */
			/* Pre code */
			for (int j12 = 0; j12 < 4; j12 = faust_wrap_add(j12, 1)) {
				fRec5_tmp[j12] = fRec5_perm[j12];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec5[i] = fRec5[faust_wrap_sub(i, 1)] + static_cast<double>(static_cast<double>(faust_wrap_sub(iYec2[i], iYec2[faust_wrap_sub(i, 1)])) > 0.0) - 0.011460935968224386 * static_cast<double>(fRec5[faust_wrap_sub(i, 1)] > 0.0);
			}
			/* Post code */
			for (int j13 = 0; j13 < 4; j13 = faust_wrap_add(j13, 1)) {
				fRec5_perm[j13] = fRec5_tmp[faust_wrap_add(vsize, j13)];
			}
			/* Recursive loop 10 */
			/* Pre code */
			fYec3_idx = (faust_wrap_add(fYec3_idx, fYec3_idx_save)) & 127;
			for (int j14 = 0; j14 < 4; j14 = faust_wrap_add(j14, 1)) {
				fRec4_tmp[j14] = fRec4_perm[j14];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec3[(faust_wrap_add(i, fYec3_idx)) & 127] = fSlow1 * (fRec4[faust_wrap_sub(i, 1)] + fRec4[faust_wrap_sub(i, 2)]) + fSlow2 * fZec2[i] * static_cast<double>(fRec5[i] > 0.0);
				fRec4[i] = fYec3[(faust_wrap_sub(faust_wrap_add(i, fYec3_idx), 86)) & 127];
			}
			/* Post code */
			fYec3_idx_save = vsize;
			for (int j15 = 0; j15 < 4; j15 = faust_wrap_add(j15, 1)) {
				fRec4_perm[j15] = fRec4_tmp[faust_wrap_add(vsize, j15)];
			}
			/* Vectorizable loop 11 */
			/* Pre code */
			for (int j16 = 0; j16 < 4; j16 = faust_wrap_add(j16, 1)) {
				iYec4_tmp[j16] = iYec4_perm[j16];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iYec4[i] = (fZec0[i] < 0.22727272727272727) & (0.22727272727272727 < fZec1[i]);
			}
			/* Post code */
			for (int j17 = 0; j17 < 4; j17 = faust_wrap_add(j17, 1)) {
				iYec4_perm[j17] = iYec4_tmp[faust_wrap_add(vsize, j17)];
			}
			/* Recursive loop 12 */
			/* Pre code */
			for (int j18 = 0; j18 < 4; j18 = faust_wrap_add(j18, 1)) {
				fRec7_tmp[j18] = fRec7_perm[j18];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec7[i] = fRec7[faust_wrap_sub(i, 1)] + static_cast<double>(static_cast<double>(faust_wrap_sub(iYec4[i], iYec4[faust_wrap_sub(i, 1)])) > 0.0) - 0.013165158293425702 * static_cast<double>(fRec7[faust_wrap_sub(i, 1)] > 0.0);
			}
			/* Post code */
			for (int j19 = 0; j19 < 4; j19 = faust_wrap_add(j19, 1)) {
				fRec7_perm[j19] = fRec7_tmp[faust_wrap_add(vsize, j19)];
			}
			/* Recursive loop 13 */
			/* Pre code */
			fYec5_idx = (faust_wrap_add(fYec5_idx, fYec5_idx_save)) & 127;
			for (int j20 = 0; j20 < 4; j20 = faust_wrap_add(j20, 1)) {
				fRec6_tmp[j20] = fRec6_perm[j20];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec5[(faust_wrap_add(i, fYec5_idx)) & 127] = fSlow1 * (fRec6[faust_wrap_sub(i, 1)] + fRec6[faust_wrap_sub(i, 2)]) + fSlow2 * fZec2[i] * static_cast<double>(fRec7[i] > 0.0);
				fRec6[i] = fYec5[(faust_wrap_sub(faust_wrap_add(i, fYec5_idx), 74)) & 127];
			}
			/* Post code */
			fYec5_idx_save = vsize;
			for (int j21 = 0; j21 < 4; j21 = faust_wrap_add(j21, 1)) {
				fRec6_perm[j21] = fRec6_tmp[faust_wrap_add(vsize, j21)];
			}
			/* Vectorizable loop 14 */
			/* Pre code */
			for (int j22 = 0; j22 < 4; j22 = faust_wrap_add(j22, 1)) {
				iYec6_tmp[j22] = iYec6_perm[j22];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iYec6[i] = (fZec0[i] < 0.3181818181818182) & (0.3181818181818182 < fZec1[i]);
			}
			/* Post code */
			for (int j23 = 0; j23 < 4; j23 = faust_wrap_add(j23, 1)) {
				iYec6_perm[j23] = iYec6_tmp[faust_wrap_add(vsize, j23)];
			}
			/* Recursive loop 15 */
			/* Pre code */
			for (int j24 = 0; j24 < 4; j24 = faust_wrap_add(j24, 1)) {
				fRec9_tmp[j24] = fRec9_perm[j24];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec9[i] = fRec9[faust_wrap_sub(i, 1)] + static_cast<double>(static_cast<double>(faust_wrap_sub(iYec6[i], iYec6[faust_wrap_sub(i, 1)])) > 0.0) - 0.015122795674933676 * static_cast<double>(fRec9[faust_wrap_sub(i, 1)] > 0.0);
			}
			/* Post code */
			for (int j25 = 0; j25 < 4; j25 = faust_wrap_add(j25, 1)) {
				fRec9_perm[j25] = fRec9_tmp[faust_wrap_add(vsize, j25)];
			}
			/* Recursive loop 16 */
			/* Pre code */
			fYec7_idx = (faust_wrap_add(fYec7_idx, fYec7_idx_save)) & 127;
			for (int j26 = 0; j26 < 4; j26 = faust_wrap_add(j26, 1)) {
				fRec8_tmp[j26] = fRec8_perm[j26];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec7[(faust_wrap_add(i, fYec7_idx)) & 127] = fSlow1 * (fRec8[faust_wrap_sub(i, 1)] + fRec8[faust_wrap_sub(i, 2)]) + fSlow2 * fZec2[i] * static_cast<double>(fRec9[i] > 0.0);
				fRec8[i] = fYec7[(faust_wrap_sub(faust_wrap_add(i, fYec7_idx), 65)) & 127];
			}
			/* Post code */
			fYec7_idx_save = vsize;
			for (int j27 = 0; j27 < 4; j27 = faust_wrap_add(j27, 1)) {
				fRec8_perm[j27] = fRec8_tmp[faust_wrap_add(vsize, j27)];
			}
			/* Vectorizable loop 17 */
			/* Pre code */
			for (int j28 = 0; j28 < 4; j28 = faust_wrap_add(j28, 1)) {
				iYec8_tmp[j28] = iYec8_perm[j28];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iYec8[i] = (fZec0[i] < 0.4090909090909091) & (0.4090909090909091 < fZec1[i]);
			}
			/* Post code */
			for (int j29 = 0; j29 < 4; j29 = faust_wrap_add(j29, 1)) {
				iYec8_perm[j29] = iYec8_tmp[faust_wrap_add(vsize, j29)];
			}
			/* Recursive loop 18 */
			/* Pre code */
			for (int j30 = 0; j30 < 4; j30 = faust_wrap_add(j30, 1)) {
				fRec11_tmp[j30] = fRec11_perm[j30];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec11[i] = fRec11[faust_wrap_sub(i, 1)] + static_cast<double>(static_cast<double>(faust_wrap_sub(iYec8[i], iYec8[faust_wrap_sub(i, 1)])) > 0.0) - 0.01737153051475259 * static_cast<double>(fRec11[faust_wrap_sub(i, 1)] > 0.0);
			}
			/* Post code */
			for (int j31 = 0; j31 < 4; j31 = faust_wrap_add(j31, 1)) {
				fRec11_perm[j31] = fRec11_tmp[faust_wrap_add(vsize, j31)];
			}
			/* Recursive loop 19 */
			/* Pre code */
			fYec9_idx = (faust_wrap_add(fYec9_idx, fYec9_idx_save)) & 63;
			for (int j32 = 0; j32 < 4; j32 = faust_wrap_add(j32, 1)) {
				fRec10_tmp[j32] = fRec10_perm[j32];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec9[(faust_wrap_add(i, fYec9_idx)) & 63] = fSlow1 * (fRec10[faust_wrap_sub(i, 1)] + fRec10[faust_wrap_sub(i, 2)]) + fSlow2 * fZec2[i] * static_cast<double>(fRec11[i] > 0.0);
				fRec10[i] = fYec9[(faust_wrap_sub(faust_wrap_add(i, fYec9_idx), 56)) & 63];
			}
			/* Post code */
			fYec9_idx_save = vsize;
			for (int j33 = 0; j33 < 4; j33 = faust_wrap_add(j33, 1)) {
				fRec10_perm[j33] = fRec10_tmp[faust_wrap_add(vsize, j33)];
			}
			/* Vectorizable loop 20 */
			/* Pre code */
			for (int j34 = 0; j34 < 4; j34 = faust_wrap_add(j34, 1)) {
				iYec10_tmp[j34] = iYec10_perm[j34];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iYec10[i] = (fZec0[i] < 0.5) & (0.5 < fZec1[i]);
			}
			/* Post code */
			for (int j35 = 0; j35 < 4; j35 = faust_wrap_add(j35, 1)) {
				iYec10_perm[j35] = iYec10_tmp[faust_wrap_add(vsize, j35)];
			}
			/* Recursive loop 21 */
			/* Pre code */
			for (int j36 = 0; j36 < 4; j36 = faust_wrap_add(j36, 1)) {
				fRec13_tmp[j36] = fRec13_perm[j36];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec13[i] = fRec13[faust_wrap_sub(i, 1)] + static_cast<double>(static_cast<double>(faust_wrap_sub(iYec10[i], iYec10[faust_wrap_sub(i, 1)])) > 0.0) - 0.019954648526077097 * static_cast<double>(fRec13[faust_wrap_sub(i, 1)] > 0.0);
			}
			/* Post code */
			for (int j37 = 0; j37 < 4; j37 = faust_wrap_add(j37, 1)) {
				fRec13_perm[j37] = fRec13_tmp[faust_wrap_add(vsize, j37)];
			}
			/* Recursive loop 22 */
			/* Pre code */
			fYec11_idx = (faust_wrap_add(fYec11_idx, fYec11_idx_save)) & 63;
			for (int j38 = 0; j38 < 4; j38 = faust_wrap_add(j38, 1)) {
				fRec12_tmp[j38] = fRec12_perm[j38];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec11[(faust_wrap_add(i, fYec11_idx)) & 63] = fSlow1 * (fRec12[faust_wrap_sub(i, 1)] + fRec12[faust_wrap_sub(i, 2)]) + fSlow2 * fZec2[i] * static_cast<double>(fRec13[i] > 0.0);
				fRec12[i] = fYec11[(faust_wrap_sub(faust_wrap_add(i, fYec11_idx), 49)) & 63];
			}
			/* Post code */
			fYec11_idx_save = vsize;
			for (int j39 = 0; j39 < 4; j39 = faust_wrap_add(j39, 1)) {
				fRec12_perm[j39] = fRec12_tmp[faust_wrap_add(vsize, j39)];
			}
			/* Vectorizable loop 23 */
			/* Pre code */
			for (int j40 = 0; j40 < 4; j40 = faust_wrap_add(j40, 1)) {
				iYec12_tmp[j40] = iYec12_perm[j40];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iYec12[i] = (fZec0[i] < 0.5909090909090909) & (0.5909090909090909 < fZec1[i]);
			}
			/* Post code */
			for (int j41 = 0; j41 < 4; j41 = faust_wrap_add(j41, 1)) {
				iYec12_perm[j41] = iYec12_tmp[faust_wrap_add(vsize, j41)];
			}
			/* Recursive loop 24 */
			/* Pre code */
			for (int j42 = 0; j42 < 4; j42 = faust_wrap_add(j42, 1)) {
				fRec15_tmp[j42] = fRec15_perm[j42];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec15[i] = fRec15[faust_wrap_sub(i, 1)] + static_cast<double>(static_cast<double>(faust_wrap_sub(iYec12[i], iYec12[faust_wrap_sub(i, 1)])) > 0.0) - 0.02292187193644877 * static_cast<double>(fRec15[faust_wrap_sub(i, 1)] > 0.0);
			}
			/* Post code */
			for (int j43 = 0; j43 < 4; j43 = faust_wrap_add(j43, 1)) {
				fRec15_perm[j43] = fRec15_tmp[faust_wrap_add(vsize, j43)];
			}
			/* Recursive loop 25 */
			/* Pre code */
			fYec13_idx = (faust_wrap_add(fYec13_idx, fYec13_idx_save)) & 63;
			for (int j44 = 0; j44 < 4; j44 = faust_wrap_add(j44, 1)) {
				fRec14_tmp[j44] = fRec14_perm[j44];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec13[(faust_wrap_add(i, fYec13_idx)) & 63] = fSlow1 * (fRec14[faust_wrap_sub(i, 1)] + fRec14[faust_wrap_sub(i, 2)]) + fSlow2 * fZec2[i] * static_cast<double>(fRec15[i] > 0.0);
				fRec14[i] = fYec13[(faust_wrap_sub(faust_wrap_add(i, fYec13_idx), 42)) & 63];
			}
			/* Post code */
			fYec13_idx_save = vsize;
			for (int j45 = 0; j45 < 4; j45 = faust_wrap_add(j45, 1)) {
				fRec14_perm[j45] = fRec14_tmp[faust_wrap_add(vsize, j45)];
			}
			/* Vectorizable loop 26 */
			/* Pre code */
			for (int j46 = 0; j46 < 4; j46 = faust_wrap_add(j46, 1)) {
				iYec14_tmp[j46] = iYec14_perm[j46];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iYec14[i] = (fZec0[i] < 0.6818181818181818) & (0.6818181818181818 < fZec1[i]);
			}
			/* Post code */
			for (int j47 = 0; j47 < 4; j47 = faust_wrap_add(j47, 1)) {
				iYec14_perm[j47] = iYec14_tmp[faust_wrap_add(vsize, j47)];
			}
			/* Recursive loop 27 */
			/* Pre code */
			for (int j48 = 0; j48 < 4; j48 = faust_wrap_add(j48, 1)) {
				fRec17_tmp[j48] = fRec17_perm[j48];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec17[i] = fRec17[faust_wrap_sub(i, 1)] + static_cast<double>(static_cast<double>(faust_wrap_sub(iYec14[i], iYec14[faust_wrap_sub(i, 1)])) > 0.0) - 0.026330316586851404 * static_cast<double>(fRec17[faust_wrap_sub(i, 1)] > 0.0);
			}
			/* Post code */
			for (int j49 = 0; j49 < 4; j49 = faust_wrap_add(j49, 1)) {
				fRec17_perm[j49] = fRec17_tmp[faust_wrap_add(vsize, j49)];
			}
			/* Recursive loop 28 */
			/* Pre code */
			fYec15_idx = (faust_wrap_add(fYec15_idx, fYec15_idx_save)) & 63;
			for (int j50 = 0; j50 < 4; j50 = faust_wrap_add(j50, 1)) {
				fRec16_tmp[j50] = fRec16_perm[j50];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec15[(faust_wrap_add(i, fYec15_idx)) & 63] = fSlow1 * (fRec16[faust_wrap_sub(i, 1)] + fRec16[faust_wrap_sub(i, 2)]) + fSlow2 * fZec2[i] * static_cast<double>(fRec17[i] > 0.0);
				fRec16[i] = fYec15[(faust_wrap_sub(faust_wrap_add(i, fYec15_idx), 36)) & 63];
			}
			/* Post code */
			fYec15_idx_save = vsize;
			for (int j51 = 0; j51 < 4; j51 = faust_wrap_add(j51, 1)) {
				fRec16_perm[j51] = fRec16_tmp[faust_wrap_add(vsize, j51)];
			}
			/* Vectorizable loop 29 */
			/* Pre code */
			for (int j52 = 0; j52 < 4; j52 = faust_wrap_add(j52, 1)) {
				iYec16_tmp[j52] = iYec16_perm[j52];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iYec16[i] = (fZec0[i] < 0.7727272727272727) & (0.7727272727272727 < fZec1[i]);
			}
			/* Post code */
			for (int j53 = 0; j53 < 4; j53 = faust_wrap_add(j53, 1)) {
				iYec16_perm[j53] = iYec16_tmp[faust_wrap_add(vsize, j53)];
			}
			/* Recursive loop 30 */
			/* Pre code */
			for (int j54 = 0; j54 < 4; j54 = faust_wrap_add(j54, 1)) {
				fRec19_tmp[j54] = fRec19_perm[j54];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec19[i] = fRec19[faust_wrap_sub(i, 1)] + static_cast<double>(static_cast<double>(faust_wrap_sub(iYec16[i], iYec16[faust_wrap_sub(i, 1)])) > 0.0) - 0.03024559134986736 * static_cast<double>(fRec19[faust_wrap_sub(i, 1)] > 0.0);
			}
			/* Post code */
			for (int j55 = 0; j55 < 4; j55 = faust_wrap_add(j55, 1)) {
				fRec19_perm[j55] = fRec19_tmp[faust_wrap_add(vsize, j55)];
			}
			/* Recursive loop 31 */
			/* Pre code */
			fYec17_idx = (faust_wrap_add(fYec17_idx, fYec17_idx_save)) & 63;
			for (int j56 = 0; j56 < 4; j56 = faust_wrap_add(j56, 1)) {
				fRec18_tmp[j56] = fRec18_perm[j56];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec17[(faust_wrap_add(i, fYec17_idx)) & 63] = fSlow1 * (fRec18[faust_wrap_sub(i, 1)] + fRec18[faust_wrap_sub(i, 2)]) + fSlow2 * fZec2[i] * static_cast<double>(fRec19[i] > 0.0);
				fRec18[i] = fYec17[(faust_wrap_sub(faust_wrap_add(i, fYec17_idx), 32)) & 63];
			}
			/* Post code */
			fYec17_idx_save = vsize;
			for (int j57 = 0; j57 < 4; j57 = faust_wrap_add(j57, 1)) {
				fRec18_perm[j57] = fRec18_tmp[faust_wrap_add(vsize, j57)];
			}
			/* Vectorizable loop 32 */
			/* Pre code */
			for (int j58 = 0; j58 < 4; j58 = faust_wrap_add(j58, 1)) {
				iYec18_tmp[j58] = iYec18_perm[j58];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iYec18[i] = (fZec0[i] < 0.8636363636363636) & (0.8636363636363636 < fZec1[i]);
			}
			/* Post code */
			for (int j59 = 0; j59 < 4; j59 = faust_wrap_add(j59, 1)) {
				iYec18_perm[j59] = iYec18_tmp[faust_wrap_add(vsize, j59)];
			}
			/* Recursive loop 33 */
			/* Pre code */
			for (int j60 = 0; j60 < 4; j60 = faust_wrap_add(j60, 1)) {
				fRec21_tmp[j60] = fRec21_perm[j60];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec21[i] = fRec21[faust_wrap_sub(i, 1)] + static_cast<double>(static_cast<double>(faust_wrap_sub(iYec18[i], iYec18[faust_wrap_sub(i, 1)])) > 0.0) - 0.03474306102950518 * static_cast<double>(fRec21[faust_wrap_sub(i, 1)] > 0.0);
			}
			/* Post code */
			for (int j61 = 0; j61 < 4; j61 = faust_wrap_add(j61, 1)) {
				fRec21_perm[j61] = fRec21_tmp[faust_wrap_add(vsize, j61)];
			}
			/* Recursive loop 34 */
			/* Pre code */
			fYec19_idx = (faust_wrap_add(fYec19_idx, fYec19_idx_save)) & 31;
			for (int j62 = 0; j62 < 4; j62 = faust_wrap_add(j62, 1)) {
				fRec20_tmp[j62] = fRec20_perm[j62];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec19[(faust_wrap_add(i, fYec19_idx)) & 31] = fSlow1 * (fRec20[faust_wrap_sub(i, 1)] + fRec20[faust_wrap_sub(i, 2)]) + fSlow2 * fZec2[i] * static_cast<double>(fRec21[i] > 0.0);
				fRec20[i] = fYec19[(faust_wrap_sub(faust_wrap_add(i, fYec19_idx), 27)) & 31];
			}
			/* Post code */
			fYec19_idx_save = vsize;
			for (int j63 = 0; j63 < 4; j63 = faust_wrap_add(j63, 1)) {
				fRec20_perm[j63] = fRec20_tmp[faust_wrap_add(vsize, j63)];
			}
			/* Vectorizable loop 35 */
			/* Pre code */
			for (int j64 = 0; j64 < 4; j64 = faust_wrap_add(j64, 1)) {
				iYec20_tmp[j64] = iYec20_perm[j64];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iYec20[i] = (fZec0[i] < 0.9545454545454546) & (0.9545454545454546 < fZec1[i]);
			}
			/* Post code */
			for (int j65 = 0; j65 < 4; j65 = faust_wrap_add(j65, 1)) {
				iYec20_perm[j65] = iYec20_tmp[faust_wrap_add(vsize, j65)];
			}
			/* Recursive loop 36 */
			/* Pre code */
			for (int j66 = 0; j66 < 4; j66 = faust_wrap_add(j66, 1)) {
				fRec23_tmp[j66] = fRec23_perm[j66];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec23[i] = fRec23[faust_wrap_sub(i, 1)] + static_cast<double>(static_cast<double>(faust_wrap_sub(iYec20[i], iYec20[faust_wrap_sub(i, 1)])) > 0.0) - 0.039909297052154194 * static_cast<double>(fRec23[faust_wrap_sub(i, 1)] > 0.0);
			}
			/* Post code */
			for (int j67 = 0; j67 < 4; j67 = faust_wrap_add(j67, 1)) {
				fRec23_perm[j67] = fRec23_tmp[faust_wrap_add(vsize, j67)];
			}
			/* Recursive loop 37 */
			/* Pre code */
			fYec21_idx = (faust_wrap_add(fYec21_idx, fYec21_idx_save)) & 31;
			for (int j68 = 0; j68 < 4; j68 = faust_wrap_add(j68, 1)) {
				fRec22_tmp[j68] = fRec22_perm[j68];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec21[(faust_wrap_add(i, fYec21_idx)) & 31] = fSlow1 * (fRec22[faust_wrap_sub(i, 1)] + fRec22[faust_wrap_sub(i, 2)]) + fSlow2 * fZec2[i] * static_cast<double>(fRec23[i] > 0.0);
				fRec22[i] = fYec21[(faust_wrap_sub(faust_wrap_add(i, fYec21_idx), 24)) & 31];
			}
			/* Post code */
			fYec21_idx_save = vsize;
			for (int j69 = 0; j69 < 4; j69 = faust_wrap_add(j69, 1)) {
				fRec22_perm[j69] = fRec22_tmp[faust_wrap_add(vsize, j69)];
			}
			/* Vectorizable loop 38 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec3[i] = 0.7071067811865476 * fRec12[i];
			}
			/* Vectorizable loop 39 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(0.9770084209183945 * fRec0[i] + 0.9293203772845852 * fRec4[i] + 0.8790490729915326 * fRec6[i] + 0.8257228238447705 * fRec8[i] + 0.7687061147858073 * fRec10[i] + fZec3[i] + 0.6396021490668313 * fRec14[i] + 0.5640760748177662 * fRec16[i] + 0.4767312946227962 * fRec18[i] + 0.3692744729379982 * fRec20[i] + 0.21320071635561033 * fRec22[i]);
			}
			/* Vectorizable loop 40 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fZec3[i] + 0.21320071635561044 * fRec0[i] + 0.3692744729379982 * fRec4[i] + 0.4767312946227962 * fRec6[i] + 0.5640760748177662 * fRec8[i] + 0.6396021490668313 * fRec10[i] + 0.7687061147858074 * fRec14[i] + 0.8257228238447705 * fRec16[i] + 0.8790490729915326 * fRec18[i] + 0.9293203772845852 * fRec20[i] + 0.9770084209183945 * fRec22[i]);
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
			/* Recursive loop 1 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fRec3_tmp[j2] = fRec3_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec3[i] = fSlow0 + 0.9 * fRec3[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fRec3_perm[j3] = fRec3_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Vectorizable loop 2 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec0[i] = std::min<double>(fRec3[i], fRec3[faust_wrap_sub(i, 1)]);
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec1[i] = std::max<double>(fRec3[i], fRec3[faust_wrap_sub(i, 1)]);
			}
			/* Vectorizable loop 4 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				iYec0_tmp[j4] = iYec0_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iYec0[i] = (fZec0[i] < 0.045454545454545456) & (0.045454545454545456 < fZec1[i]);
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				iYec0_perm[j5] = iYec0_tmp[faust_wrap_add(vsize, j5)];
			}
			/* Recursive loop 5 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec2_tmp[j6] = fRec2_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec2[i] = fRec2[faust_wrap_sub(i, 1)] + static_cast<double>(static_cast<double>(faust_wrap_sub(iYec0[i], iYec0[faust_wrap_sub(i, 1)])) > 0.0) - 0.009977324263038548 * static_cast<double>(fRec2[faust_wrap_sub(i, 1)] > 0.0);
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec2_perm[j7] = fRec2_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec2[i] = static_cast<double>(iRec1[i]);
			}
			/* Recursive loop 7 */
			/* Pre code */
			fYec1_idx = (faust_wrap_add(fYec1_idx, fYec1_idx_save)) & 127;
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fRec0_tmp[j8] = fRec0_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec1[(faust_wrap_add(i, fYec1_idx)) & 127] = fSlow1 * (fRec0[faust_wrap_sub(i, 1)] + fRec0[faust_wrap_sub(i, 2)]) + fSlow2 * fZec2[i] * static_cast<double>(fRec2[i] > 0.0);
				fRec0[i] = fYec1[(faust_wrap_sub(faust_wrap_add(i, fYec1_idx), 99)) & 127];
			}
			/* Post code */
			fYec1_idx_save = vsize;
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fRec0_perm[j9] = fRec0_tmp[faust_wrap_add(vsize, j9)];
			}
			/* Vectorizable loop 8 */
			/* Pre code */
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				iYec2_tmp[j10] = iYec2_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iYec2[i] = (fZec0[i] < 0.13636363636363635) & (0.13636363636363635 < fZec1[i]);
			}
			/* Post code */
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				iYec2_perm[j11] = iYec2_tmp[faust_wrap_add(vsize, j11)];
			}
			/* Recursive loop 9 */
			/* Pre code */
			for (int j12 = 0; j12 < 4; j12 = faust_wrap_add(j12, 1)) {
				fRec5_tmp[j12] = fRec5_perm[j12];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec5[i] = fRec5[faust_wrap_sub(i, 1)] + static_cast<double>(static_cast<double>(faust_wrap_sub(iYec2[i], iYec2[faust_wrap_sub(i, 1)])) > 0.0) - 0.011460935968224386 * static_cast<double>(fRec5[faust_wrap_sub(i, 1)] > 0.0);
			}
			/* Post code */
			for (int j13 = 0; j13 < 4; j13 = faust_wrap_add(j13, 1)) {
				fRec5_perm[j13] = fRec5_tmp[faust_wrap_add(vsize, j13)];
			}
			/* Recursive loop 10 */
			/* Pre code */
			fYec3_idx = (faust_wrap_add(fYec3_idx, fYec3_idx_save)) & 127;
			for (int j14 = 0; j14 < 4; j14 = faust_wrap_add(j14, 1)) {
				fRec4_tmp[j14] = fRec4_perm[j14];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec3[(faust_wrap_add(i, fYec3_idx)) & 127] = fSlow1 * (fRec4[faust_wrap_sub(i, 1)] + fRec4[faust_wrap_sub(i, 2)]) + fSlow2 * fZec2[i] * static_cast<double>(fRec5[i] > 0.0);
				fRec4[i] = fYec3[(faust_wrap_sub(faust_wrap_add(i, fYec3_idx), 86)) & 127];
			}
			/* Post code */
			fYec3_idx_save = vsize;
			for (int j15 = 0; j15 < 4; j15 = faust_wrap_add(j15, 1)) {
				fRec4_perm[j15] = fRec4_tmp[faust_wrap_add(vsize, j15)];
			}
			/* Vectorizable loop 11 */
			/* Pre code */
			for (int j16 = 0; j16 < 4; j16 = faust_wrap_add(j16, 1)) {
				iYec4_tmp[j16] = iYec4_perm[j16];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iYec4[i] = (fZec0[i] < 0.22727272727272727) & (0.22727272727272727 < fZec1[i]);
			}
			/* Post code */
			for (int j17 = 0; j17 < 4; j17 = faust_wrap_add(j17, 1)) {
				iYec4_perm[j17] = iYec4_tmp[faust_wrap_add(vsize, j17)];
			}
			/* Recursive loop 12 */
			/* Pre code */
			for (int j18 = 0; j18 < 4; j18 = faust_wrap_add(j18, 1)) {
				fRec7_tmp[j18] = fRec7_perm[j18];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec7[i] = fRec7[faust_wrap_sub(i, 1)] + static_cast<double>(static_cast<double>(faust_wrap_sub(iYec4[i], iYec4[faust_wrap_sub(i, 1)])) > 0.0) - 0.013165158293425702 * static_cast<double>(fRec7[faust_wrap_sub(i, 1)] > 0.0);
			}
			/* Post code */
			for (int j19 = 0; j19 < 4; j19 = faust_wrap_add(j19, 1)) {
				fRec7_perm[j19] = fRec7_tmp[faust_wrap_add(vsize, j19)];
			}
			/* Recursive loop 13 */
			/* Pre code */
			fYec5_idx = (faust_wrap_add(fYec5_idx, fYec5_idx_save)) & 127;
			for (int j20 = 0; j20 < 4; j20 = faust_wrap_add(j20, 1)) {
				fRec6_tmp[j20] = fRec6_perm[j20];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec5[(faust_wrap_add(i, fYec5_idx)) & 127] = fSlow1 * (fRec6[faust_wrap_sub(i, 1)] + fRec6[faust_wrap_sub(i, 2)]) + fSlow2 * fZec2[i] * static_cast<double>(fRec7[i] > 0.0);
				fRec6[i] = fYec5[(faust_wrap_sub(faust_wrap_add(i, fYec5_idx), 74)) & 127];
			}
			/* Post code */
			fYec5_idx_save = vsize;
			for (int j21 = 0; j21 < 4; j21 = faust_wrap_add(j21, 1)) {
				fRec6_perm[j21] = fRec6_tmp[faust_wrap_add(vsize, j21)];
			}
			/* Vectorizable loop 14 */
			/* Pre code */
			for (int j22 = 0; j22 < 4; j22 = faust_wrap_add(j22, 1)) {
				iYec6_tmp[j22] = iYec6_perm[j22];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iYec6[i] = (fZec0[i] < 0.3181818181818182) & (0.3181818181818182 < fZec1[i]);
			}
			/* Post code */
			for (int j23 = 0; j23 < 4; j23 = faust_wrap_add(j23, 1)) {
				iYec6_perm[j23] = iYec6_tmp[faust_wrap_add(vsize, j23)];
			}
			/* Recursive loop 15 */
			/* Pre code */
			for (int j24 = 0; j24 < 4; j24 = faust_wrap_add(j24, 1)) {
				fRec9_tmp[j24] = fRec9_perm[j24];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec9[i] = fRec9[faust_wrap_sub(i, 1)] + static_cast<double>(static_cast<double>(faust_wrap_sub(iYec6[i], iYec6[faust_wrap_sub(i, 1)])) > 0.0) - 0.015122795674933676 * static_cast<double>(fRec9[faust_wrap_sub(i, 1)] > 0.0);
			}
			/* Post code */
			for (int j25 = 0; j25 < 4; j25 = faust_wrap_add(j25, 1)) {
				fRec9_perm[j25] = fRec9_tmp[faust_wrap_add(vsize, j25)];
			}
			/* Recursive loop 16 */
			/* Pre code */
			fYec7_idx = (faust_wrap_add(fYec7_idx, fYec7_idx_save)) & 127;
			for (int j26 = 0; j26 < 4; j26 = faust_wrap_add(j26, 1)) {
				fRec8_tmp[j26] = fRec8_perm[j26];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec7[(faust_wrap_add(i, fYec7_idx)) & 127] = fSlow1 * (fRec8[faust_wrap_sub(i, 1)] + fRec8[faust_wrap_sub(i, 2)]) + fSlow2 * fZec2[i] * static_cast<double>(fRec9[i] > 0.0);
				fRec8[i] = fYec7[(faust_wrap_sub(faust_wrap_add(i, fYec7_idx), 65)) & 127];
			}
			/* Post code */
			fYec7_idx_save = vsize;
			for (int j27 = 0; j27 < 4; j27 = faust_wrap_add(j27, 1)) {
				fRec8_perm[j27] = fRec8_tmp[faust_wrap_add(vsize, j27)];
			}
			/* Vectorizable loop 17 */
			/* Pre code */
			for (int j28 = 0; j28 < 4; j28 = faust_wrap_add(j28, 1)) {
				iYec8_tmp[j28] = iYec8_perm[j28];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iYec8[i] = (fZec0[i] < 0.4090909090909091) & (0.4090909090909091 < fZec1[i]);
			}
			/* Post code */
			for (int j29 = 0; j29 < 4; j29 = faust_wrap_add(j29, 1)) {
				iYec8_perm[j29] = iYec8_tmp[faust_wrap_add(vsize, j29)];
			}
			/* Recursive loop 18 */
			/* Pre code */
			for (int j30 = 0; j30 < 4; j30 = faust_wrap_add(j30, 1)) {
				fRec11_tmp[j30] = fRec11_perm[j30];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec11[i] = fRec11[faust_wrap_sub(i, 1)] + static_cast<double>(static_cast<double>(faust_wrap_sub(iYec8[i], iYec8[faust_wrap_sub(i, 1)])) > 0.0) - 0.01737153051475259 * static_cast<double>(fRec11[faust_wrap_sub(i, 1)] > 0.0);
			}
			/* Post code */
			for (int j31 = 0; j31 < 4; j31 = faust_wrap_add(j31, 1)) {
				fRec11_perm[j31] = fRec11_tmp[faust_wrap_add(vsize, j31)];
			}
			/* Recursive loop 19 */
			/* Pre code */
			fYec9_idx = (faust_wrap_add(fYec9_idx, fYec9_idx_save)) & 63;
			for (int j32 = 0; j32 < 4; j32 = faust_wrap_add(j32, 1)) {
				fRec10_tmp[j32] = fRec10_perm[j32];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec9[(faust_wrap_add(i, fYec9_idx)) & 63] = fSlow1 * (fRec10[faust_wrap_sub(i, 1)] + fRec10[faust_wrap_sub(i, 2)]) + fSlow2 * fZec2[i] * static_cast<double>(fRec11[i] > 0.0);
				fRec10[i] = fYec9[(faust_wrap_sub(faust_wrap_add(i, fYec9_idx), 56)) & 63];
			}
			/* Post code */
			fYec9_idx_save = vsize;
			for (int j33 = 0; j33 < 4; j33 = faust_wrap_add(j33, 1)) {
				fRec10_perm[j33] = fRec10_tmp[faust_wrap_add(vsize, j33)];
			}
			/* Vectorizable loop 20 */
			/* Pre code */
			for (int j34 = 0; j34 < 4; j34 = faust_wrap_add(j34, 1)) {
				iYec10_tmp[j34] = iYec10_perm[j34];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iYec10[i] = (fZec0[i] < 0.5) & (0.5 < fZec1[i]);
			}
			/* Post code */
			for (int j35 = 0; j35 < 4; j35 = faust_wrap_add(j35, 1)) {
				iYec10_perm[j35] = iYec10_tmp[faust_wrap_add(vsize, j35)];
			}
			/* Recursive loop 21 */
			/* Pre code */
			for (int j36 = 0; j36 < 4; j36 = faust_wrap_add(j36, 1)) {
				fRec13_tmp[j36] = fRec13_perm[j36];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec13[i] = fRec13[faust_wrap_sub(i, 1)] + static_cast<double>(static_cast<double>(faust_wrap_sub(iYec10[i], iYec10[faust_wrap_sub(i, 1)])) > 0.0) - 0.019954648526077097 * static_cast<double>(fRec13[faust_wrap_sub(i, 1)] > 0.0);
			}
			/* Post code */
			for (int j37 = 0; j37 < 4; j37 = faust_wrap_add(j37, 1)) {
				fRec13_perm[j37] = fRec13_tmp[faust_wrap_add(vsize, j37)];
			}
			/* Recursive loop 22 */
			/* Pre code */
			fYec11_idx = (faust_wrap_add(fYec11_idx, fYec11_idx_save)) & 63;
			for (int j38 = 0; j38 < 4; j38 = faust_wrap_add(j38, 1)) {
				fRec12_tmp[j38] = fRec12_perm[j38];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec11[(faust_wrap_add(i, fYec11_idx)) & 63] = fSlow1 * (fRec12[faust_wrap_sub(i, 1)] + fRec12[faust_wrap_sub(i, 2)]) + fSlow2 * fZec2[i] * static_cast<double>(fRec13[i] > 0.0);
				fRec12[i] = fYec11[(faust_wrap_sub(faust_wrap_add(i, fYec11_idx), 49)) & 63];
			}
			/* Post code */
			fYec11_idx_save = vsize;
			for (int j39 = 0; j39 < 4; j39 = faust_wrap_add(j39, 1)) {
				fRec12_perm[j39] = fRec12_tmp[faust_wrap_add(vsize, j39)];
			}
			/* Vectorizable loop 23 */
			/* Pre code */
			for (int j40 = 0; j40 < 4; j40 = faust_wrap_add(j40, 1)) {
				iYec12_tmp[j40] = iYec12_perm[j40];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iYec12[i] = (fZec0[i] < 0.5909090909090909) & (0.5909090909090909 < fZec1[i]);
			}
			/* Post code */
			for (int j41 = 0; j41 < 4; j41 = faust_wrap_add(j41, 1)) {
				iYec12_perm[j41] = iYec12_tmp[faust_wrap_add(vsize, j41)];
			}
			/* Recursive loop 24 */
			/* Pre code */
			for (int j42 = 0; j42 < 4; j42 = faust_wrap_add(j42, 1)) {
				fRec15_tmp[j42] = fRec15_perm[j42];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec15[i] = fRec15[faust_wrap_sub(i, 1)] + static_cast<double>(static_cast<double>(faust_wrap_sub(iYec12[i], iYec12[faust_wrap_sub(i, 1)])) > 0.0) - 0.02292187193644877 * static_cast<double>(fRec15[faust_wrap_sub(i, 1)] > 0.0);
			}
			/* Post code */
			for (int j43 = 0; j43 < 4; j43 = faust_wrap_add(j43, 1)) {
				fRec15_perm[j43] = fRec15_tmp[faust_wrap_add(vsize, j43)];
			}
			/* Recursive loop 25 */
			/* Pre code */
			fYec13_idx = (faust_wrap_add(fYec13_idx, fYec13_idx_save)) & 63;
			for (int j44 = 0; j44 < 4; j44 = faust_wrap_add(j44, 1)) {
				fRec14_tmp[j44] = fRec14_perm[j44];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec13[(faust_wrap_add(i, fYec13_idx)) & 63] = fSlow1 * (fRec14[faust_wrap_sub(i, 1)] + fRec14[faust_wrap_sub(i, 2)]) + fSlow2 * fZec2[i] * static_cast<double>(fRec15[i] > 0.0);
				fRec14[i] = fYec13[(faust_wrap_sub(faust_wrap_add(i, fYec13_idx), 42)) & 63];
			}
			/* Post code */
			fYec13_idx_save = vsize;
			for (int j45 = 0; j45 < 4; j45 = faust_wrap_add(j45, 1)) {
				fRec14_perm[j45] = fRec14_tmp[faust_wrap_add(vsize, j45)];
			}
			/* Vectorizable loop 26 */
			/* Pre code */
			for (int j46 = 0; j46 < 4; j46 = faust_wrap_add(j46, 1)) {
				iYec14_tmp[j46] = iYec14_perm[j46];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iYec14[i] = (fZec0[i] < 0.6818181818181818) & (0.6818181818181818 < fZec1[i]);
			}
			/* Post code */
			for (int j47 = 0; j47 < 4; j47 = faust_wrap_add(j47, 1)) {
				iYec14_perm[j47] = iYec14_tmp[faust_wrap_add(vsize, j47)];
			}
			/* Recursive loop 27 */
			/* Pre code */
			for (int j48 = 0; j48 < 4; j48 = faust_wrap_add(j48, 1)) {
				fRec17_tmp[j48] = fRec17_perm[j48];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec17[i] = fRec17[faust_wrap_sub(i, 1)] + static_cast<double>(static_cast<double>(faust_wrap_sub(iYec14[i], iYec14[faust_wrap_sub(i, 1)])) > 0.0) - 0.026330316586851404 * static_cast<double>(fRec17[faust_wrap_sub(i, 1)] > 0.0);
			}
			/* Post code */
			for (int j49 = 0; j49 < 4; j49 = faust_wrap_add(j49, 1)) {
				fRec17_perm[j49] = fRec17_tmp[faust_wrap_add(vsize, j49)];
			}
			/* Recursive loop 28 */
			/* Pre code */
			fYec15_idx = (faust_wrap_add(fYec15_idx, fYec15_idx_save)) & 63;
			for (int j50 = 0; j50 < 4; j50 = faust_wrap_add(j50, 1)) {
				fRec16_tmp[j50] = fRec16_perm[j50];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec15[(faust_wrap_add(i, fYec15_idx)) & 63] = fSlow1 * (fRec16[faust_wrap_sub(i, 1)] + fRec16[faust_wrap_sub(i, 2)]) + fSlow2 * fZec2[i] * static_cast<double>(fRec17[i] > 0.0);
				fRec16[i] = fYec15[(faust_wrap_sub(faust_wrap_add(i, fYec15_idx), 36)) & 63];
			}
			/* Post code */
			fYec15_idx_save = vsize;
			for (int j51 = 0; j51 < 4; j51 = faust_wrap_add(j51, 1)) {
				fRec16_perm[j51] = fRec16_tmp[faust_wrap_add(vsize, j51)];
			}
			/* Vectorizable loop 29 */
			/* Pre code */
			for (int j52 = 0; j52 < 4; j52 = faust_wrap_add(j52, 1)) {
				iYec16_tmp[j52] = iYec16_perm[j52];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iYec16[i] = (fZec0[i] < 0.7727272727272727) & (0.7727272727272727 < fZec1[i]);
			}
			/* Post code */
			for (int j53 = 0; j53 < 4; j53 = faust_wrap_add(j53, 1)) {
				iYec16_perm[j53] = iYec16_tmp[faust_wrap_add(vsize, j53)];
			}
			/* Recursive loop 30 */
			/* Pre code */
			for (int j54 = 0; j54 < 4; j54 = faust_wrap_add(j54, 1)) {
				fRec19_tmp[j54] = fRec19_perm[j54];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec19[i] = fRec19[faust_wrap_sub(i, 1)] + static_cast<double>(static_cast<double>(faust_wrap_sub(iYec16[i], iYec16[faust_wrap_sub(i, 1)])) > 0.0) - 0.03024559134986736 * static_cast<double>(fRec19[faust_wrap_sub(i, 1)] > 0.0);
			}
			/* Post code */
			for (int j55 = 0; j55 < 4; j55 = faust_wrap_add(j55, 1)) {
				fRec19_perm[j55] = fRec19_tmp[faust_wrap_add(vsize, j55)];
			}
			/* Recursive loop 31 */
			/* Pre code */
			fYec17_idx = (faust_wrap_add(fYec17_idx, fYec17_idx_save)) & 63;
			for (int j56 = 0; j56 < 4; j56 = faust_wrap_add(j56, 1)) {
				fRec18_tmp[j56] = fRec18_perm[j56];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec17[(faust_wrap_add(i, fYec17_idx)) & 63] = fSlow1 * (fRec18[faust_wrap_sub(i, 1)] + fRec18[faust_wrap_sub(i, 2)]) + fSlow2 * fZec2[i] * static_cast<double>(fRec19[i] > 0.0);
				fRec18[i] = fYec17[(faust_wrap_sub(faust_wrap_add(i, fYec17_idx), 32)) & 63];
			}
			/* Post code */
			fYec17_idx_save = vsize;
			for (int j57 = 0; j57 < 4; j57 = faust_wrap_add(j57, 1)) {
				fRec18_perm[j57] = fRec18_tmp[faust_wrap_add(vsize, j57)];
			}
			/* Vectorizable loop 32 */
			/* Pre code */
			for (int j58 = 0; j58 < 4; j58 = faust_wrap_add(j58, 1)) {
				iYec18_tmp[j58] = iYec18_perm[j58];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iYec18[i] = (fZec0[i] < 0.8636363636363636) & (0.8636363636363636 < fZec1[i]);
			}
			/* Post code */
			for (int j59 = 0; j59 < 4; j59 = faust_wrap_add(j59, 1)) {
				iYec18_perm[j59] = iYec18_tmp[faust_wrap_add(vsize, j59)];
			}
			/* Recursive loop 33 */
			/* Pre code */
			for (int j60 = 0; j60 < 4; j60 = faust_wrap_add(j60, 1)) {
				fRec21_tmp[j60] = fRec21_perm[j60];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec21[i] = fRec21[faust_wrap_sub(i, 1)] + static_cast<double>(static_cast<double>(faust_wrap_sub(iYec18[i], iYec18[faust_wrap_sub(i, 1)])) > 0.0) - 0.03474306102950518 * static_cast<double>(fRec21[faust_wrap_sub(i, 1)] > 0.0);
			}
			/* Post code */
			for (int j61 = 0; j61 < 4; j61 = faust_wrap_add(j61, 1)) {
				fRec21_perm[j61] = fRec21_tmp[faust_wrap_add(vsize, j61)];
			}
			/* Recursive loop 34 */
			/* Pre code */
			fYec19_idx = (faust_wrap_add(fYec19_idx, fYec19_idx_save)) & 31;
			for (int j62 = 0; j62 < 4; j62 = faust_wrap_add(j62, 1)) {
				fRec20_tmp[j62] = fRec20_perm[j62];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec19[(faust_wrap_add(i, fYec19_idx)) & 31] = fSlow1 * (fRec20[faust_wrap_sub(i, 1)] + fRec20[faust_wrap_sub(i, 2)]) + fSlow2 * fZec2[i] * static_cast<double>(fRec21[i] > 0.0);
				fRec20[i] = fYec19[(faust_wrap_sub(faust_wrap_add(i, fYec19_idx), 27)) & 31];
			}
			/* Post code */
			fYec19_idx_save = vsize;
			for (int j63 = 0; j63 < 4; j63 = faust_wrap_add(j63, 1)) {
				fRec20_perm[j63] = fRec20_tmp[faust_wrap_add(vsize, j63)];
			}
			/* Vectorizable loop 35 */
			/* Pre code */
			for (int j64 = 0; j64 < 4; j64 = faust_wrap_add(j64, 1)) {
				iYec20_tmp[j64] = iYec20_perm[j64];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iYec20[i] = (fZec0[i] < 0.9545454545454546) & (0.9545454545454546 < fZec1[i]);
			}
			/* Post code */
			for (int j65 = 0; j65 < 4; j65 = faust_wrap_add(j65, 1)) {
				iYec20_perm[j65] = iYec20_tmp[faust_wrap_add(vsize, j65)];
			}
			/* Recursive loop 36 */
			/* Pre code */
			for (int j66 = 0; j66 < 4; j66 = faust_wrap_add(j66, 1)) {
				fRec23_tmp[j66] = fRec23_perm[j66];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec23[i] = fRec23[faust_wrap_sub(i, 1)] + static_cast<double>(static_cast<double>(faust_wrap_sub(iYec20[i], iYec20[faust_wrap_sub(i, 1)])) > 0.0) - 0.039909297052154194 * static_cast<double>(fRec23[faust_wrap_sub(i, 1)] > 0.0);
			}
			/* Post code */
			for (int j67 = 0; j67 < 4; j67 = faust_wrap_add(j67, 1)) {
				fRec23_perm[j67] = fRec23_tmp[faust_wrap_add(vsize, j67)];
			}
			/* Recursive loop 37 */
			/* Pre code */
			fYec21_idx = (faust_wrap_add(fYec21_idx, fYec21_idx_save)) & 31;
			for (int j68 = 0; j68 < 4; j68 = faust_wrap_add(j68, 1)) {
				fRec22_tmp[j68] = fRec22_perm[j68];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec21[(faust_wrap_add(i, fYec21_idx)) & 31] = fSlow1 * (fRec22[faust_wrap_sub(i, 1)] + fRec22[faust_wrap_sub(i, 2)]) + fSlow2 * fZec2[i] * static_cast<double>(fRec23[i] > 0.0);
				fRec22[i] = fYec21[(faust_wrap_sub(faust_wrap_add(i, fYec21_idx), 24)) & 31];
			}
			/* Post code */
			fYec21_idx_save = vsize;
			for (int j69 = 0; j69 < 4; j69 = faust_wrap_add(j69, 1)) {
				fRec22_perm[j69] = fRec22_tmp[faust_wrap_add(vsize, j69)];
			}
			/* Vectorizable loop 38 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec3[i] = 0.7071067811865476 * fRec12[i];
			}
			/* Vectorizable loop 39 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(0.9770084209183945 * fRec0[i] + 0.9293203772845852 * fRec4[i] + 0.8790490729915326 * fRec6[i] + 0.8257228238447705 * fRec8[i] + 0.7687061147858073 * fRec10[i] + fZec3[i] + 0.6396021490668313 * fRec14[i] + 0.5640760748177662 * fRec16[i] + 0.4767312946227962 * fRec18[i] + 0.3692744729379982 * fRec20[i] + 0.21320071635561033 * fRec22[i]);
			}
			/* Vectorizable loop 40 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fZec3[i] + 0.21320071635561044 * fRec0[i] + 0.3692744729379982 * fRec4[i] + 0.4767312946227962 * fRec6[i] + 0.5640760748177662 * fRec8[i] + 0.6396021490668313 * fRec10[i] + 0.7687061147858074 * fRec14[i] + 0.8257228238447705 * fRec16[i] + 0.8790490729915326 * fRec18[i] + 0.9293203772845852 * fRec20[i] + 0.9770084209183945 * fRec22[i]);
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
