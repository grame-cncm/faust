/* ------------------------------------------------------------
name: "tf_exp"
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
	
	int fSampleRate;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	int iVec0_perm[4];
	double fYec0_perm[4];
	double fRec2_perm[4];
	double fConst5;
	double fConst6;
	double fConst7;
	double fConst8;
	double fConst9;
	double fRec1_perm[4];
	double fConst10;
	double fConst11;
	double fConst12;
	double fConst13;
	double fConst14;
	double fConst15;
	double fConst16;
	double fConst17;
	double fConst18;
	double fRec0_perm[4];
	double fRec6_perm[4];
	double fRec5_perm[4];
	double fConst19;
	double fYec1_perm[4];
	double fRec4_perm[4];
	double fConst20;
	double fConst21;
	double fRec3_perm[4];
	double fConst22;
	double fRec8_perm[4];
	double fRec7_perm[4];
	
 public:
	mydsp() {
	}
	
	mydsp(const mydsp&) = default;
	
	virtual ~mydsp() = default;
	
	mydsp& operator=(const mydsp&) = default;
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-a /Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/archs/impulsearch.cpp -lang cpp -i -fpga-mem-th 4 -ct 1 -es 1 -mcd 4 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs");
		m->declare("filename", "tf_exp.dsp");
		m->declare("name", "tf_exp");
	}

	virtual int getNumInputs() {
		return 0;
	}
	virtual int getNumOutputs() {
		return 1;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, static_cast<double>(fSampleRate)));
		fConst1 = std::tan(3553.141291210056 / fConst0);
		fConst2 = 1.0 / fConst1;
		fConst3 = 1.0 / (fConst2 + 1.0);
		fConst4 = 1.0 - fConst2;
		fConst5 = (fConst2 + 1.0000000000000002) / fConst1 + 1.0;
		fConst6 = 1.0 / fConst5;
		fConst7 = (fConst2 + -1.0000000000000002) / fConst1 + 1.0;
		fConst8 = mydsp_faustpower2_f(fConst1);
		fConst9 = 2.0 * (1.0 - 1.0 / fConst8);
		fConst10 = 1.0 / (fConst8 * fConst5);
		fConst11 = std::tan(1776.570645605028 / fConst0);
		fConst12 = 1.0 / fConst11;
		fConst13 = fConst12 + 1.0;
		fConst14 = 1.0 / (fConst13 / fConst11 + 1.0);
		fConst15 = 1.0 - fConst12;
		fConst16 = 1.0 - fConst15 / fConst11;
		fConst17 = 1.0 / mydsp_faustpower2_f(fConst11);
		fConst18 = 2.0 * (1.0 - fConst17);
		fConst19 = 1.0 / fConst13;
		fConst20 = 1.0 / ((fConst12 + 1.0000000000000002) / fConst11 + 1.0);
		fConst21 = (fConst12 + -1.0000000000000002) / fConst11 + 1.0;
		fConst22 = 1.0 / (fConst11 * fConst5);
	}
	
	virtual void instanceResetUserInterface() {
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 4; l0 = faust_wrap_add(l0, 1)) {
			iVec0_perm[l0] = 0;
		}
		for (int l1 = 0; l1 < 4; l1 = faust_wrap_add(l1, 1)) {
			fYec0_perm[l1] = 0.0;
		}
		for (int l2 = 0; l2 < 4; l2 = faust_wrap_add(l2, 1)) {
			fRec2_perm[l2] = 0.0;
		}
		for (int l3 = 0; l3 < 4; l3 = faust_wrap_add(l3, 1)) {
			fRec1_perm[l3] = 0.0;
		}
		for (int l4 = 0; l4 < 4; l4 = faust_wrap_add(l4, 1)) {
			fRec0_perm[l4] = 0.0;
		}
		for (int l5 = 0; l5 < 4; l5 = faust_wrap_add(l5, 1)) {
			fRec6_perm[l5] = 0.0;
		}
		for (int l6 = 0; l6 < 4; l6 = faust_wrap_add(l6, 1)) {
			fRec5_perm[l6] = 0.0;
		}
		for (int l7 = 0; l7 < 4; l7 = faust_wrap_add(l7, 1)) {
			fYec1_perm[l7] = 0.0;
		}
		for (int l8 = 0; l8 < 4; l8 = faust_wrap_add(l8, 1)) {
			fRec4_perm[l8] = 0.0;
		}
		for (int l9 = 0; l9 < 4; l9 = faust_wrap_add(l9, 1)) {
			fRec3_perm[l9] = 0.0;
		}
		for (int l10 = 0; l10 < 4; l10 = faust_wrap_add(l10, 1)) {
			fRec8_perm[l10] = 0.0;
		}
		for (int l11 = 0; l11 < 4; l11 = faust_wrap_add(l11, 1)) {
			fRec7_perm[l11] = 0.0;
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
		ui_interface->openVerticalBox("tf_exp");
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* output0_ptr = outputs[0];
		int iVec0_tmp[8];
		int* iVec0 = &iVec0_tmp[4];
		double fYec0_tmp[8];
		double* fYec0 = &fYec0_tmp[4];
		double fRec2_tmp[8];
		double* fRec2 = &fRec2_tmp[4];
		double fRec1_tmp[8];
		double* fRec1 = &fRec1_tmp[4];
		double fZec0[4];
		double fRec0_tmp[8];
		double* fRec0 = &fRec0_tmp[4];
		double fRec6_tmp[8];
		double* fRec6 = &fRec6_tmp[4];
		double fRec5_tmp[8];
		double* fRec5 = &fRec5_tmp[4];
		double fYec1_tmp[8];
		double* fYec1 = &fYec1_tmp[4];
		double fRec4_tmp[8];
		double* fRec4 = &fRec4_tmp[4];
		double fRec3_tmp[8];
		double* fRec3 = &fRec3_tmp[4];
		double fRec8_tmp[8];
		double* fRec8 = &fRec8_tmp[4];
		double fRec7_tmp[8];
		double* fRec7 = &fRec7_tmp[4];
		int vindex = 0;
		/* Main loop */
		for (vindex = 0; vindex <= (faust_wrap_sub(count, 4)); vindex = faust_wrap_add(vindex, 4)) {
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			int vsize = 4;
			/* Vectorizable loop 0 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				iVec0_tmp[j0] = iVec0_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iVec0[i] = 1;
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				iVec0_perm[j1] = iVec0_tmp[faust_wrap_add(vsize, j1)];
			}
			/* Vectorizable loop 1 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fYec0_tmp[j2] = fYec0_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec0[i] = static_cast<double>(faust_wrap_sub(1, iVec0[faust_wrap_sub(i, 1)]));
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fYec0_perm[j3] = fYec0_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Recursive loop 2 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				fRec2_tmp[j4] = fRec2_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec2[i] = -(fConst3 * (fConst4 * fRec2[faust_wrap_sub(i, 1)] - fConst2 * (fYec0[i] - fYec0[faust_wrap_sub(i, 1)])));
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fRec2_perm[j5] = fRec2_tmp[faust_wrap_add(vsize, j5)];
			}
			/* Recursive loop 3 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec1_tmp[j6] = fRec1_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec1[i] = fRec2[i] - fConst6 * (fConst7 * fRec1[faust_wrap_sub(i, 2)] + fConst9 * fRec1[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec1_perm[j7] = fRec1_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Recursive loop 4 */
			/* Pre code */
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fRec0_tmp[j8] = fRec0_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec0[i] = fConst18 * fRec0[faust_wrap_sub(i, 1)];
				fRec0[i] = fConst10 * (fRec1[faust_wrap_sub(i, 2)] + (fRec1[i] - 2.0 * fRec1[faust_wrap_sub(i, 1)])) - fConst14 * (fConst16 * fRec0[faust_wrap_sub(i, 2)] + fZec0[i]);
			}
			/* Post code */
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fRec0_perm[j9] = fRec0_tmp[faust_wrap_add(vsize, j9)];
			}
			/* Recursive loop 5 */
			/* Pre code */
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				fRec6_tmp[j10] = fRec6_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec6[i] = -(fConst3 * (fConst4 * fRec6[faust_wrap_sub(i, 1)] - (fYec0[i] + fYec0[faust_wrap_sub(i, 1)])));
			}
			/* Post code */
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				fRec6_perm[j11] = fRec6_tmp[faust_wrap_add(vsize, j11)];
			}
			/* Recursive loop 6 */
			/* Pre code */
			for (int j12 = 0; j12 < 4; j12 = faust_wrap_add(j12, 1)) {
				fRec5_tmp[j12] = fRec5_perm[j12];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec5[i] = fRec6[i] - fConst6 * (fConst7 * fRec5[faust_wrap_sub(i, 2)] + fConst9 * fRec5[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j13 = 0; j13 < 4; j13 = faust_wrap_add(j13, 1)) {
				fRec5_perm[j13] = fRec5_tmp[faust_wrap_add(vsize, j13)];
			}
			/* Vectorizable loop 7 */
			/* Pre code */
			for (int j14 = 0; j14 < 4; j14 = faust_wrap_add(j14, 1)) {
				fYec1_tmp[j14] = fYec1_perm[j14];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec1[i] = fRec5[faust_wrap_sub(i, 2)] + fRec5[i] + 2.0 * fRec5[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j15 = 0; j15 < 4; j15 = faust_wrap_add(j15, 1)) {
				fYec1_perm[j15] = fYec1_tmp[faust_wrap_add(vsize, j15)];
			}
			/* Recursive loop 8 */
			/* Pre code */
			for (int j16 = 0; j16 < 4; j16 = faust_wrap_add(j16, 1)) {
				fRec4_tmp[j16] = fRec4_perm[j16];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec4[i] = -(fConst19 * (fConst15 * fRec4[faust_wrap_sub(i, 1)] - fConst6 * (fYec1[i] + fYec1[faust_wrap_sub(i, 1)])));
			}
			/* Post code */
			for (int j17 = 0; j17 < 4; j17 = faust_wrap_add(j17, 1)) {
				fRec4_perm[j17] = fRec4_tmp[faust_wrap_add(vsize, j17)];
			}
			/* Recursive loop 9 */
			/* Pre code */
			for (int j18 = 0; j18 < 4; j18 = faust_wrap_add(j18, 1)) {
				fRec3_tmp[j18] = fRec3_perm[j18];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec3[i] = fRec4[i] - fConst20 * (fConst21 * fRec3[faust_wrap_sub(i, 2)] + fConst18 * fRec3[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j19 = 0; j19 < 4; j19 = faust_wrap_add(j19, 1)) {
				fRec3_perm[j19] = fRec3_tmp[faust_wrap_add(vsize, j19)];
			}
			/* Recursive loop 10 */
			/* Pre code */
			for (int j20 = 0; j20 < 4; j20 = faust_wrap_add(j20, 1)) {
				fRec8_tmp[j20] = fRec8_perm[j20];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec8[i] = -(fConst19 * (fConst15 * fRec8[faust_wrap_sub(i, 1)] - fConst22 * (fYec1[i] - fYec1[faust_wrap_sub(i, 1)])));
			}
			/* Post code */
			for (int j21 = 0; j21 < 4; j21 = faust_wrap_add(j21, 1)) {
				fRec8_perm[j21] = fRec8_tmp[faust_wrap_add(vsize, j21)];
			}
			/* Recursive loop 11 */
			/* Pre code */
			for (int j22 = 0; j22 < 4; j22 = faust_wrap_add(j22, 1)) {
				fRec7_tmp[j22] = fRec7_perm[j22];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec7[i] = fRec8[i] - fConst20 * (fConst21 * fRec7[faust_wrap_sub(i, 2)] + fConst18 * fRec7[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j23 = 0; j23 < 4; j23 = faust_wrap_add(j23, 1)) {
				fRec7_perm[j23] = fRec7_tmp[faust_wrap_add(vsize, j23)];
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fRec0[faust_wrap_sub(i, 2)] + fConst14 * (fZec0[i] + fConst16 * fRec0[i]) + fConst20 * (fRec3[faust_wrap_sub(i, 2)] + fRec3[i] + 2.0 * fRec3[faust_wrap_sub(i, 1)] + fConst17 * (fRec7[faust_wrap_sub(i, 2)] + (fRec7[i] - 2.0 * fRec7[faust_wrap_sub(i, 1)]))));
			}
		}
		/* Remaining frames */
		if (vindex < count) {
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			int vsize = faust_wrap_sub(count, vindex);
			/* Vectorizable loop 0 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				iVec0_tmp[j0] = iVec0_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iVec0[i] = 1;
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				iVec0_perm[j1] = iVec0_tmp[faust_wrap_add(vsize, j1)];
			}
			/* Vectorizable loop 1 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fYec0_tmp[j2] = fYec0_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec0[i] = static_cast<double>(faust_wrap_sub(1, iVec0[faust_wrap_sub(i, 1)]));
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fYec0_perm[j3] = fYec0_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Recursive loop 2 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				fRec2_tmp[j4] = fRec2_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec2[i] = -(fConst3 * (fConst4 * fRec2[faust_wrap_sub(i, 1)] - fConst2 * (fYec0[i] - fYec0[faust_wrap_sub(i, 1)])));
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fRec2_perm[j5] = fRec2_tmp[faust_wrap_add(vsize, j5)];
			}
			/* Recursive loop 3 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec1_tmp[j6] = fRec1_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec1[i] = fRec2[i] - fConst6 * (fConst7 * fRec1[faust_wrap_sub(i, 2)] + fConst9 * fRec1[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec1_perm[j7] = fRec1_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Recursive loop 4 */
			/* Pre code */
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fRec0_tmp[j8] = fRec0_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec0[i] = fConst18 * fRec0[faust_wrap_sub(i, 1)];
				fRec0[i] = fConst10 * (fRec1[faust_wrap_sub(i, 2)] + (fRec1[i] - 2.0 * fRec1[faust_wrap_sub(i, 1)])) - fConst14 * (fConst16 * fRec0[faust_wrap_sub(i, 2)] + fZec0[i]);
			}
			/* Post code */
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fRec0_perm[j9] = fRec0_tmp[faust_wrap_add(vsize, j9)];
			}
			/* Recursive loop 5 */
			/* Pre code */
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				fRec6_tmp[j10] = fRec6_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec6[i] = -(fConst3 * (fConst4 * fRec6[faust_wrap_sub(i, 1)] - (fYec0[i] + fYec0[faust_wrap_sub(i, 1)])));
			}
			/* Post code */
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				fRec6_perm[j11] = fRec6_tmp[faust_wrap_add(vsize, j11)];
			}
			/* Recursive loop 6 */
			/* Pre code */
			for (int j12 = 0; j12 < 4; j12 = faust_wrap_add(j12, 1)) {
				fRec5_tmp[j12] = fRec5_perm[j12];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec5[i] = fRec6[i] - fConst6 * (fConst7 * fRec5[faust_wrap_sub(i, 2)] + fConst9 * fRec5[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j13 = 0; j13 < 4; j13 = faust_wrap_add(j13, 1)) {
				fRec5_perm[j13] = fRec5_tmp[faust_wrap_add(vsize, j13)];
			}
			/* Vectorizable loop 7 */
			/* Pre code */
			for (int j14 = 0; j14 < 4; j14 = faust_wrap_add(j14, 1)) {
				fYec1_tmp[j14] = fYec1_perm[j14];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec1[i] = fRec5[faust_wrap_sub(i, 2)] + fRec5[i] + 2.0 * fRec5[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j15 = 0; j15 < 4; j15 = faust_wrap_add(j15, 1)) {
				fYec1_perm[j15] = fYec1_tmp[faust_wrap_add(vsize, j15)];
			}
			/* Recursive loop 8 */
			/* Pre code */
			for (int j16 = 0; j16 < 4; j16 = faust_wrap_add(j16, 1)) {
				fRec4_tmp[j16] = fRec4_perm[j16];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec4[i] = -(fConst19 * (fConst15 * fRec4[faust_wrap_sub(i, 1)] - fConst6 * (fYec1[i] + fYec1[faust_wrap_sub(i, 1)])));
			}
			/* Post code */
			for (int j17 = 0; j17 < 4; j17 = faust_wrap_add(j17, 1)) {
				fRec4_perm[j17] = fRec4_tmp[faust_wrap_add(vsize, j17)];
			}
			/* Recursive loop 9 */
			/* Pre code */
			for (int j18 = 0; j18 < 4; j18 = faust_wrap_add(j18, 1)) {
				fRec3_tmp[j18] = fRec3_perm[j18];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec3[i] = fRec4[i] - fConst20 * (fConst21 * fRec3[faust_wrap_sub(i, 2)] + fConst18 * fRec3[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j19 = 0; j19 < 4; j19 = faust_wrap_add(j19, 1)) {
				fRec3_perm[j19] = fRec3_tmp[faust_wrap_add(vsize, j19)];
			}
			/* Recursive loop 10 */
			/* Pre code */
			for (int j20 = 0; j20 < 4; j20 = faust_wrap_add(j20, 1)) {
				fRec8_tmp[j20] = fRec8_perm[j20];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec8[i] = -(fConst19 * (fConst15 * fRec8[faust_wrap_sub(i, 1)] - fConst22 * (fYec1[i] - fYec1[faust_wrap_sub(i, 1)])));
			}
			/* Post code */
			for (int j21 = 0; j21 < 4; j21 = faust_wrap_add(j21, 1)) {
				fRec8_perm[j21] = fRec8_tmp[faust_wrap_add(vsize, j21)];
			}
			/* Recursive loop 11 */
			/* Pre code */
			for (int j22 = 0; j22 < 4; j22 = faust_wrap_add(j22, 1)) {
				fRec7_tmp[j22] = fRec7_perm[j22];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec7[i] = fRec8[i] - fConst20 * (fConst21 * fRec7[faust_wrap_sub(i, 2)] + fConst18 * fRec7[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j23 = 0; j23 < 4; j23 = faust_wrap_add(j23, 1)) {
				fRec7_perm[j23] = fRec7_tmp[faust_wrap_add(vsize, j23)];
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fRec0[faust_wrap_sub(i, 2)] + fConst14 * (fZec0[i] + fConst16 * fRec0[i]) + fConst20 * (fRec3[faust_wrap_sub(i, 2)] + fRec3[i] + 2.0 * fRec3[faust_wrap_sub(i, 1)] + fConst17 * (fRec7[faust_wrap_sub(i, 2)] + (fRec7[i] - 2.0 * fRec7[faust_wrap_sub(i, 1)]))));
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
