/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2006"
license: "BSD"
name: "dbmeter"
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
	double fRec0_perm[4];
	FAUSTFLOAT fVbargraph0;
	int iConst1;
	double fRec1_perm[4];
	FAUSTFLOAT fVbargraph1;
	int iConst2;
	double fRec2_perm[4];
	FAUSTFLOAT fVbargraph2;
	int iConst3;
	double fRec3_perm[4];
	FAUSTFLOAT fVbargraph3;
	int iConst4;
	double fRec4_perm[4];
	FAUSTFLOAT fVbargraph4;
	int iConst5;
	double fRec5_perm[4];
	FAUSTFLOAT fVbargraph5;
	int iConst6;
	double fRec6_perm[4];
	FAUSTFLOAT fVbargraph6;
	int iConst7;
	double fRec7_perm[4];
	FAUSTFLOAT fVbargraph7;
	int iConst8;
	
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
		m->declare("filename", "dbmeter.dsp");
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
		m->declare("name", "dbmeter");
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
		fConst0 = 8e+01 / std::min<double>(1.92e+05, std::max<double>(1.0, static_cast<double>(fSampleRate)));
		iConst1 = 0;
		iConst2 = 0;
		iConst3 = 0;
		iConst4 = 0;
		iConst5 = 0;
		iConst6 = 0;
		iConst7 = 0;
		iConst8 = 0;
	}
	
	virtual void instanceResetUserInterface() {
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 4; l0 = faust_wrap_add(l0, 1)) {
			fRec0_perm[l0] = 0.0;
		}
		for (int l1 = 0; l1 < 4; l1 = faust_wrap_add(l1, 1)) {
			fRec1_perm[l1] = 0.0;
		}
		for (int l2 = 0; l2 < 4; l2 = faust_wrap_add(l2, 1)) {
			fRec2_perm[l2] = 0.0;
		}
		for (int l3 = 0; l3 < 4; l3 = faust_wrap_add(l3, 1)) {
			fRec3_perm[l3] = 0.0;
		}
		for (int l4 = 0; l4 < 4; l4 = faust_wrap_add(l4, 1)) {
			fRec4_perm[l4] = 0.0;
		}
		for (int l5 = 0; l5 < 4; l5 = faust_wrap_add(l5, 1)) {
			fRec5_perm[l5] = 0.0;
		}
		for (int l6 = 0; l6 < 4; l6 = faust_wrap_add(l6, 1)) {
			fRec6_perm[l6] = 0.0;
		}
		for (int l7 = 0; l7 < 4; l7 = faust_wrap_add(l7, 1)) {
			fRec7_perm[l7] = 0.0;
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
		ui_interface->openHorizontalBox("8 channels dB meter");
		ui_interface->openVerticalBox("0");
		ui_interface->declare(&fVbargraph0, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph0", &fVbargraph0, FAUSTFLOAT(-7e+01), FAUSTFLOAT(1e+01));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("1");
		ui_interface->declare(&fVbargraph1, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph1", &fVbargraph1, FAUSTFLOAT(-7e+01), FAUSTFLOAT(1e+01));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("2");
		ui_interface->declare(&fVbargraph2, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph2", &fVbargraph2, FAUSTFLOAT(-7e+01), FAUSTFLOAT(1e+01));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("3");
		ui_interface->declare(&fVbargraph3, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph3", &fVbargraph3, FAUSTFLOAT(-7e+01), FAUSTFLOAT(1e+01));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("4");
		ui_interface->declare(&fVbargraph4, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph4", &fVbargraph4, FAUSTFLOAT(-7e+01), FAUSTFLOAT(1e+01));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("5");
		ui_interface->declare(&fVbargraph5, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph5", &fVbargraph5, FAUSTFLOAT(-7e+01), FAUSTFLOAT(1e+01));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("6");
		ui_interface->declare(&fVbargraph6, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph6", &fVbargraph6, FAUSTFLOAT(-7e+01), FAUSTFLOAT(1e+01));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("7");
		ui_interface->declare(&fVbargraph7, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph7", &fVbargraph7, FAUSTFLOAT(-7e+01), FAUSTFLOAT(1e+01));
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
		double fRec0_tmp[8];
		double* fRec0 = &fRec0_tmp[4];
		double fRec1_tmp[8];
		double* fRec1 = &fRec1_tmp[4];
		double fRec2_tmp[8];
		double* fRec2 = &fRec2_tmp[4];
		double fRec3_tmp[8];
		double* fRec3 = &fRec3_tmp[4];
		double fRec4_tmp[8];
		double* fRec4 = &fRec4_tmp[4];
		double fRec5_tmp[8];
		double* fRec5 = &fRec5_tmp[4];
		double fRec6_tmp[8];
		double* fRec6 = &fRec6_tmp[4];
		double fRec7_tmp[8];
		double* fRec7 = &fRec7_tmp[4];
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
			/* Recursive loop 0 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				fRec0_tmp[j0] = fRec0_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec0[i] = std::max<double>(fRec0[faust_wrap_sub(i, 1)] - fConst0, std::min<double>(1e+01, 2e+01 * std::log10(std::max<double>(0.00031622776601683794, std::fabs(static_cast<double>(input0[i]))))));
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				fRec0_perm[j1] = fRec0_tmp[faust_wrap_add(vsize, j1)];
			}
			/* Vectorizable loop 1 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph0 = static_cast<FAUSTFLOAT>(fRec0[i]);
				output0[i] = static_cast<FAUSTFLOAT>(iConst1);
			}
			/* Recursive loop 2 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fRec1_tmp[j2] = fRec1_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec1[i] = std::max<double>(fRec1[faust_wrap_sub(i, 1)] - fConst0, std::min<double>(1e+01, 2e+01 * std::log10(std::max<double>(0.00031622776601683794, std::fabs(static_cast<double>(input1[i]))))));
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fRec1_perm[j3] = fRec1_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph1 = static_cast<FAUSTFLOAT>(fRec1[i]);
				output1[i] = static_cast<FAUSTFLOAT>(iConst2);
			}
			/* Recursive loop 4 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				fRec2_tmp[j4] = fRec2_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec2[i] = std::max<double>(fRec2[faust_wrap_sub(i, 1)] - fConst0, std::min<double>(1e+01, 2e+01 * std::log10(std::max<double>(0.00031622776601683794, std::fabs(static_cast<double>(input2[i]))))));
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fRec2_perm[j5] = fRec2_tmp[faust_wrap_add(vsize, j5)];
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph2 = static_cast<FAUSTFLOAT>(fRec2[i]);
				output2[i] = static_cast<FAUSTFLOAT>(iConst3);
			}
			/* Recursive loop 6 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec3_tmp[j6] = fRec3_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec3[i] = std::max<double>(fRec3[faust_wrap_sub(i, 1)] - fConst0, std::min<double>(1e+01, 2e+01 * std::log10(std::max<double>(0.00031622776601683794, std::fabs(static_cast<double>(input3[i]))))));
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec3_perm[j7] = fRec3_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph3 = static_cast<FAUSTFLOAT>(fRec3[i]);
				output3[i] = static_cast<FAUSTFLOAT>(iConst4);
			}
			/* Recursive loop 8 */
			/* Pre code */
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fRec4_tmp[j8] = fRec4_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec4[i] = std::max<double>(fRec4[faust_wrap_sub(i, 1)] - fConst0, std::min<double>(1e+01, 2e+01 * std::log10(std::max<double>(0.00031622776601683794, std::fabs(static_cast<double>(input4[i]))))));
			}
			/* Post code */
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fRec4_perm[j9] = fRec4_tmp[faust_wrap_add(vsize, j9)];
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph4 = static_cast<FAUSTFLOAT>(fRec4[i]);
				output4[i] = static_cast<FAUSTFLOAT>(iConst5);
			}
			/* Recursive loop 10 */
			/* Pre code */
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				fRec5_tmp[j10] = fRec5_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec5[i] = std::max<double>(fRec5[faust_wrap_sub(i, 1)] - fConst0, std::min<double>(1e+01, 2e+01 * std::log10(std::max<double>(0.00031622776601683794, std::fabs(static_cast<double>(input5[i]))))));
			}
			/* Post code */
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				fRec5_perm[j11] = fRec5_tmp[faust_wrap_add(vsize, j11)];
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph5 = static_cast<FAUSTFLOAT>(fRec5[i]);
				output5[i] = static_cast<FAUSTFLOAT>(iConst6);
			}
			/* Recursive loop 12 */
			/* Pre code */
			for (int j12 = 0; j12 < 4; j12 = faust_wrap_add(j12, 1)) {
				fRec6_tmp[j12] = fRec6_perm[j12];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec6[i] = std::max<double>(fRec6[faust_wrap_sub(i, 1)] - fConst0, std::min<double>(1e+01, 2e+01 * std::log10(std::max<double>(0.00031622776601683794, std::fabs(static_cast<double>(input6[i]))))));
			}
			/* Post code */
			for (int j13 = 0; j13 < 4; j13 = faust_wrap_add(j13, 1)) {
				fRec6_perm[j13] = fRec6_tmp[faust_wrap_add(vsize, j13)];
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph6 = static_cast<FAUSTFLOAT>(fRec6[i]);
				output6[i] = static_cast<FAUSTFLOAT>(iConst7);
			}
			/* Recursive loop 14 */
			/* Pre code */
			for (int j14 = 0; j14 < 4; j14 = faust_wrap_add(j14, 1)) {
				fRec7_tmp[j14] = fRec7_perm[j14];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec7[i] = std::max<double>(fRec7[faust_wrap_sub(i, 1)] - fConst0, std::min<double>(1e+01, 2e+01 * std::log10(std::max<double>(0.00031622776601683794, std::fabs(static_cast<double>(input7[i]))))));
			}
			/* Post code */
			for (int j15 = 0; j15 < 4; j15 = faust_wrap_add(j15, 1)) {
				fRec7_perm[j15] = fRec7_tmp[faust_wrap_add(vsize, j15)];
			}
			/* Vectorizable loop 15 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph7 = static_cast<FAUSTFLOAT>(fRec7[i]);
				output7[i] = static_cast<FAUSTFLOAT>(iConst8);
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
			/* Recursive loop 0 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				fRec0_tmp[j0] = fRec0_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec0[i] = std::max<double>(fRec0[faust_wrap_sub(i, 1)] - fConst0, std::min<double>(1e+01, 2e+01 * std::log10(std::max<double>(0.00031622776601683794, std::fabs(static_cast<double>(input0[i]))))));
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				fRec0_perm[j1] = fRec0_tmp[faust_wrap_add(vsize, j1)];
			}
			/* Vectorizable loop 1 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph0 = static_cast<FAUSTFLOAT>(fRec0[i]);
				output0[i] = static_cast<FAUSTFLOAT>(iConst1);
			}
			/* Recursive loop 2 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fRec1_tmp[j2] = fRec1_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec1[i] = std::max<double>(fRec1[faust_wrap_sub(i, 1)] - fConst0, std::min<double>(1e+01, 2e+01 * std::log10(std::max<double>(0.00031622776601683794, std::fabs(static_cast<double>(input1[i]))))));
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fRec1_perm[j3] = fRec1_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph1 = static_cast<FAUSTFLOAT>(fRec1[i]);
				output1[i] = static_cast<FAUSTFLOAT>(iConst2);
			}
			/* Recursive loop 4 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				fRec2_tmp[j4] = fRec2_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec2[i] = std::max<double>(fRec2[faust_wrap_sub(i, 1)] - fConst0, std::min<double>(1e+01, 2e+01 * std::log10(std::max<double>(0.00031622776601683794, std::fabs(static_cast<double>(input2[i]))))));
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fRec2_perm[j5] = fRec2_tmp[faust_wrap_add(vsize, j5)];
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph2 = static_cast<FAUSTFLOAT>(fRec2[i]);
				output2[i] = static_cast<FAUSTFLOAT>(iConst3);
			}
			/* Recursive loop 6 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec3_tmp[j6] = fRec3_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec3[i] = std::max<double>(fRec3[faust_wrap_sub(i, 1)] - fConst0, std::min<double>(1e+01, 2e+01 * std::log10(std::max<double>(0.00031622776601683794, std::fabs(static_cast<double>(input3[i]))))));
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec3_perm[j7] = fRec3_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph3 = static_cast<FAUSTFLOAT>(fRec3[i]);
				output3[i] = static_cast<FAUSTFLOAT>(iConst4);
			}
			/* Recursive loop 8 */
			/* Pre code */
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fRec4_tmp[j8] = fRec4_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec4[i] = std::max<double>(fRec4[faust_wrap_sub(i, 1)] - fConst0, std::min<double>(1e+01, 2e+01 * std::log10(std::max<double>(0.00031622776601683794, std::fabs(static_cast<double>(input4[i]))))));
			}
			/* Post code */
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fRec4_perm[j9] = fRec4_tmp[faust_wrap_add(vsize, j9)];
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph4 = static_cast<FAUSTFLOAT>(fRec4[i]);
				output4[i] = static_cast<FAUSTFLOAT>(iConst5);
			}
			/* Recursive loop 10 */
			/* Pre code */
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				fRec5_tmp[j10] = fRec5_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec5[i] = std::max<double>(fRec5[faust_wrap_sub(i, 1)] - fConst0, std::min<double>(1e+01, 2e+01 * std::log10(std::max<double>(0.00031622776601683794, std::fabs(static_cast<double>(input5[i]))))));
			}
			/* Post code */
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				fRec5_perm[j11] = fRec5_tmp[faust_wrap_add(vsize, j11)];
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph5 = static_cast<FAUSTFLOAT>(fRec5[i]);
				output5[i] = static_cast<FAUSTFLOAT>(iConst6);
			}
			/* Recursive loop 12 */
			/* Pre code */
			for (int j12 = 0; j12 < 4; j12 = faust_wrap_add(j12, 1)) {
				fRec6_tmp[j12] = fRec6_perm[j12];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec6[i] = std::max<double>(fRec6[faust_wrap_sub(i, 1)] - fConst0, std::min<double>(1e+01, 2e+01 * std::log10(std::max<double>(0.00031622776601683794, std::fabs(static_cast<double>(input6[i]))))));
			}
			/* Post code */
			for (int j13 = 0; j13 < 4; j13 = faust_wrap_add(j13, 1)) {
				fRec6_perm[j13] = fRec6_tmp[faust_wrap_add(vsize, j13)];
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph6 = static_cast<FAUSTFLOAT>(fRec6[i]);
				output6[i] = static_cast<FAUSTFLOAT>(iConst7);
			}
			/* Recursive loop 14 */
			/* Pre code */
			for (int j14 = 0; j14 < 4; j14 = faust_wrap_add(j14, 1)) {
				fRec7_tmp[j14] = fRec7_perm[j14];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec7[i] = std::max<double>(fRec7[faust_wrap_sub(i, 1)] - fConst0, std::min<double>(1e+01, 2e+01 * std::log10(std::max<double>(0.00031622776601683794, std::fabs(static_cast<double>(input7[i]))))));
			}
			/* Post code */
			for (int j15 = 0; j15 < 4; j15 = faust_wrap_add(j15, 1)) {
				fRec7_perm[j15] = fRec7_tmp[faust_wrap_add(vsize, j15)];
			}
			/* Vectorizable loop 15 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph7 = static_cast<FAUSTFLOAT>(fRec7[i]);
				output7[i] = static_cast<FAUSTFLOAT>(iConst8);
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
