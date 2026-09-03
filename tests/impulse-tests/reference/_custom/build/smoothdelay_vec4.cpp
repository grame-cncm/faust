/* ------------------------------------------------------------
author: "Yann Orlarey"
copyright: "Grame"
license: "STK-4.3"
name: "SmoothDelay"
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
	
	int fSampleRate;
	double fConst0;
	double fConst1;
	FAUSTFLOAT fHslider0;
	double fConst2;
	FAUSTFLOAT fHslider1;
	double fRec1_perm[4];
	double fRec2_perm[4];
	double fRec3_perm[4];
	double fRec4_perm[4];
	FAUSTFLOAT fHslider2;
	double fYec0[1048576];
	int fYec0_idx;
	int fYec0_idx_save;
	double fRec0_perm[4];
	double fYec1[1048576];
	int fYec1_idx;
	int fYec1_idx_save;
	double fRec5_perm[4];
	
 public:
	mydsp() {
	}
	
	mydsp(const mydsp&) = default;
	
	virtual ~mydsp() = default;
	
	mydsp& operator=(const mydsp&) = default;
	
	void metadata(Meta* m) { 
		m->declare("author", "Yann Orlarey");
		m->declare("compile_options", "-a /Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/archs/impulsearch.cpp -lang cpp -i -fpga-mem-th 4 -ct 1 -es 1 -mcd 4 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs");
		m->declare("copyright", "Grame");
		m->declare("filename", "smoothdelay.dsp");
		m->declare("license", "STK-4.3");
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
		m->declare("name", "SmoothDelay");
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
		fConst1 = 0.001 * fConst0;
		fConst2 = 1e+03 / fConst0;
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(114.5);
		fHslider1 = static_cast<FAUSTFLOAT>(68.0329);
		fHslider2 = static_cast<FAUSTFLOAT>(87.11);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 4; l0 = faust_wrap_add(l0, 1)) {
			fRec1_perm[l0] = 0.0;
		}
		for (int l1 = 0; l1 < 4; l1 = faust_wrap_add(l1, 1)) {
			fRec2_perm[l1] = 0.0;
		}
		for (int l2 = 0; l2 < 4; l2 = faust_wrap_add(l2, 1)) {
			fRec3_perm[l2] = 0.0;
		}
		for (int l3 = 0; l3 < 4; l3 = faust_wrap_add(l3, 1)) {
			fRec4_perm[l3] = 0.0;
		}
		for (int l4 = 0; l4 < 1048576; l4 = faust_wrap_add(l4, 1)) {
			fYec0[l4] = 0.0;
		}
		fYec0_idx = 0;
		fYec0_idx_save = 0;
		for (int l5 = 0; l5 < 4; l5 = faust_wrap_add(l5, 1)) {
			fRec0_perm[l5] = 0.0;
		}
		for (int l6 = 0; l6 < 1048576; l6 = faust_wrap_add(l6, 1)) {
			fYec1[l6] = 0.0;
		}
		fYec1_idx = 0;
		fYec1_idx_save = 0;
		for (int l7 = 0; l7 < 4; l7 = faust_wrap_add(l7, 1)) {
			fRec5_perm[l7] = 0.0;
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
		ui_interface->openVerticalBox("SmoothDelay");
		ui_interface->declare(&fHslider0, "style", "knob");
		ui_interface->declare(&fHslider0, "unit", "ms");
		ui_interface->addHorizontalSlider("delay", &fHslider0, FAUSTFLOAT(114.5), FAUSTFLOAT(0.0), FAUSTFLOAT(5e+03), FAUSTFLOAT(0.1));
		ui_interface->declare(&fHslider2, "style", "knob");
		ui_interface->addHorizontalSlider("feedback", &fHslider2, FAUSTFLOAT(87.11), FAUSTFLOAT(0.0), FAUSTFLOAT(1e+02), FAUSTFLOAT(0.1));
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->declare(&fHslider1, "unit", "ms");
		ui_interface->addHorizontalSlider("interpolation", &fHslider1, FAUSTFLOAT(68.0329), FAUSTFLOAT(1.0), FAUSTFLOAT(1e+02), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0_ptr = inputs[0];
		FAUSTFLOAT* input1_ptr = inputs[1];
		FAUSTFLOAT* output0_ptr = outputs[0];
		FAUSTFLOAT* output1_ptr = outputs[1];
		double fSlow0 = fConst1 * static_cast<double>(fHslider0);
		double fSlow1 = fConst2 / static_cast<double>(fHslider1);
		double fZec0[4];
		double fRec1_tmp[8];
		double* fRec1 = &fRec1_tmp[4];
		double fRec2_tmp[8];
		double* fRec2 = &fRec2_tmp[4];
		double fRec3_tmp[8];
		double* fRec3 = &fRec3_tmp[4];
		double fRec4_tmp[8];
		double* fRec4 = &fRec4_tmp[4];
		double fZec1[4];
		double fSlow2 = 0.01 * static_cast<double>(fHslider2);
		int iZec2[4];
		int iZec3[4];
		double fRec0_tmp[8];
		double* fRec0 = &fRec0_tmp[4];
		double fRec5_tmp[8];
		double* fRec5 = &fRec5_tmp[4];
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
				fRec1_tmp[j0] = fRec1_perm[j0];
			}
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fRec2_tmp[j2] = fRec2_perm[j2];
			}
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				fRec3_tmp[j4] = fRec3_perm[j4];
			}
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec4_tmp[j6] = fRec4_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec0[i] = ((fRec1[faust_wrap_sub(i, 1)] != 0.0) ? (((fRec2[faust_wrap_sub(i, 1)] > 0.0) & (fRec2[faust_wrap_sub(i, 1)] < 1.0)) ? fRec1[faust_wrap_sub(i, 1)] : 0.0) : (((fRec2[faust_wrap_sub(i, 1)] == 0.0) & (fSlow0 != fRec3[faust_wrap_sub(i, 1)])) ? fSlow1 : (((fRec2[faust_wrap_sub(i, 1)] == 1.0) & (fSlow0 != fRec4[faust_wrap_sub(i, 1)])) ? -fSlow1 : 0.0)));
				fRec1[i] = fZec0[i];
				fRec2[i] = std::max<double>(0.0, std::min<double>(1.0, fRec2[faust_wrap_sub(i, 1)] + fZec0[i]));
				fRec3[i] = (((fRec2[faust_wrap_sub(i, 1)] >= 1.0) & (fRec4[faust_wrap_sub(i, 1)] != fSlow0)) ? fSlow0 : fRec3[faust_wrap_sub(i, 1)]);
				fRec4[i] = (((fRec2[faust_wrap_sub(i, 1)] <= 0.0) & (fRec3[faust_wrap_sub(i, 1)] != fSlow0)) ? fSlow0 : fRec4[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				fRec1_perm[j1] = fRec1_tmp[faust_wrap_add(vsize, j1)];
			}
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fRec2_perm[j3] = fRec2_tmp[faust_wrap_add(vsize, j3)];
			}
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fRec3_perm[j5] = fRec3_tmp[faust_wrap_add(vsize, j5)];
			}
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec4_perm[j7] = fRec4_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Vectorizable loop 1 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec1[i] = 1.0 - fRec2[i];
			}
			/* Vectorizable loop 2 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec2[i] = static_cast<int>(fRec3[i]) & 524287;
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec3[i] = static_cast<int>(fRec4[i]) & 524287;
			}
			/* Recursive loop 4 */
			/* Pre code */
			fYec0_idx = (faust_wrap_add(fYec0_idx, fYec0_idx_save)) & 1048575;
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fRec0_tmp[j8] = fRec0_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec0[(faust_wrap_add(i, fYec0_idx)) & 1048575] = static_cast<double>(input0[i]) + fSlow2 * fRec0[faust_wrap_sub(i, 1)];
				fRec0[i] = fZec1[i] * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), iZec2[i])) & 1048575] + fRec2[i] * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), iZec3[i])) & 1048575];
			}
			/* Post code */
			fYec0_idx_save = vsize;
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fRec0_perm[j9] = fRec0_tmp[faust_wrap_add(vsize, j9)];
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fRec0[i]);
			}
			/* Recursive loop 6 */
			/* Pre code */
			fYec1_idx = (faust_wrap_add(fYec1_idx, fYec1_idx_save)) & 1048575;
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				fRec5_tmp[j10] = fRec5_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec1[(faust_wrap_add(i, fYec1_idx)) & 1048575] = static_cast<double>(input1[i]) + fSlow2 * fRec5[faust_wrap_sub(i, 1)];
				fRec5[i] = fZec1[i] * fYec1[(faust_wrap_sub(faust_wrap_add(i, fYec1_idx), iZec2[i])) & 1048575] + fRec2[i] * fYec1[(faust_wrap_sub(faust_wrap_add(i, fYec1_idx), iZec3[i])) & 1048575];
			}
			/* Post code */
			fYec1_idx_save = vsize;
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				fRec5_perm[j11] = fRec5_tmp[faust_wrap_add(vsize, j11)];
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fRec5[i]);
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
				fRec1_tmp[j0] = fRec1_perm[j0];
			}
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fRec2_tmp[j2] = fRec2_perm[j2];
			}
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				fRec3_tmp[j4] = fRec3_perm[j4];
			}
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec4_tmp[j6] = fRec4_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec0[i] = ((fRec1[faust_wrap_sub(i, 1)] != 0.0) ? (((fRec2[faust_wrap_sub(i, 1)] > 0.0) & (fRec2[faust_wrap_sub(i, 1)] < 1.0)) ? fRec1[faust_wrap_sub(i, 1)] : 0.0) : (((fRec2[faust_wrap_sub(i, 1)] == 0.0) & (fSlow0 != fRec3[faust_wrap_sub(i, 1)])) ? fSlow1 : (((fRec2[faust_wrap_sub(i, 1)] == 1.0) & (fSlow0 != fRec4[faust_wrap_sub(i, 1)])) ? -fSlow1 : 0.0)));
				fRec1[i] = fZec0[i];
				fRec2[i] = std::max<double>(0.0, std::min<double>(1.0, fRec2[faust_wrap_sub(i, 1)] + fZec0[i]));
				fRec3[i] = (((fRec2[faust_wrap_sub(i, 1)] >= 1.0) & (fRec4[faust_wrap_sub(i, 1)] != fSlow0)) ? fSlow0 : fRec3[faust_wrap_sub(i, 1)]);
				fRec4[i] = (((fRec2[faust_wrap_sub(i, 1)] <= 0.0) & (fRec3[faust_wrap_sub(i, 1)] != fSlow0)) ? fSlow0 : fRec4[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				fRec1_perm[j1] = fRec1_tmp[faust_wrap_add(vsize, j1)];
			}
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fRec2_perm[j3] = fRec2_tmp[faust_wrap_add(vsize, j3)];
			}
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fRec3_perm[j5] = fRec3_tmp[faust_wrap_add(vsize, j5)];
			}
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec4_perm[j7] = fRec4_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Vectorizable loop 1 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec1[i] = 1.0 - fRec2[i];
			}
			/* Vectorizable loop 2 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec2[i] = static_cast<int>(fRec3[i]) & 524287;
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec3[i] = static_cast<int>(fRec4[i]) & 524287;
			}
			/* Recursive loop 4 */
			/* Pre code */
			fYec0_idx = (faust_wrap_add(fYec0_idx, fYec0_idx_save)) & 1048575;
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fRec0_tmp[j8] = fRec0_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec0[(faust_wrap_add(i, fYec0_idx)) & 1048575] = static_cast<double>(input0[i]) + fSlow2 * fRec0[faust_wrap_sub(i, 1)];
				fRec0[i] = fZec1[i] * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), iZec2[i])) & 1048575] + fRec2[i] * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), iZec3[i])) & 1048575];
			}
			/* Post code */
			fYec0_idx_save = vsize;
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fRec0_perm[j9] = fRec0_tmp[faust_wrap_add(vsize, j9)];
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fRec0[i]);
			}
			/* Recursive loop 6 */
			/* Pre code */
			fYec1_idx = (faust_wrap_add(fYec1_idx, fYec1_idx_save)) & 1048575;
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				fRec5_tmp[j10] = fRec5_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec1[(faust_wrap_add(i, fYec1_idx)) & 1048575] = static_cast<double>(input1[i]) + fSlow2 * fRec5[faust_wrap_sub(i, 1)];
				fRec5[i] = fZec1[i] * fYec1[(faust_wrap_sub(faust_wrap_add(i, fYec1_idx), iZec2[i])) & 1048575] + fRec2[i] * fYec1[(faust_wrap_sub(faust_wrap_add(i, fYec1_idx), iZec3[i])) & 1048575];
			}
			/* Post code */
			fYec1_idx_save = vsize;
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				fRec5_perm[j11] = fRec5_tmp[faust_wrap_add(vsize, j11)];
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fRec5[i]);
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
