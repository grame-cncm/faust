/* ------------------------------------------------------------
name: "math_simp"
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
	
	double fYec0[16];
	int fYec0_idx;
	int fYec0_idx_save;
	int fSampleRate;
	double fConst0;
	
 public:
	mydsp() {
	}
	
	mydsp(const mydsp&) = default;
	
	virtual ~mydsp() = default;
	
	mydsp& operator=(const mydsp&) = default;
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-a /Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/archs/impulsearch.cpp -lang cpp -i -fpga-mem-th 4 -ct 1 -es 1 -mcd 4 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs");
		m->declare("filename", "math_simp.dsp");
		m->declare("name", "math_simp");
	}

	virtual int getNumInputs() {
		return 3;
	}
	virtual int getNumOutputs() {
		return 32;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, static_cast<double>(fSampleRate)));
	}
	
	virtual void instanceResetUserInterface() {
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 16; l0 = faust_wrap_add(l0, 1)) {
			fYec0[l0] = 0.0;
		}
		fYec0_idx = 0;
		fYec0_idx_save = 0;
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
		ui_interface->openVerticalBox("math_simp");
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0_ptr = inputs[0];
		FAUSTFLOAT* input1_ptr = inputs[1];
		FAUSTFLOAT* input2_ptr = inputs[2];
		FAUSTFLOAT* output0_ptr = outputs[0];
		FAUSTFLOAT* output1_ptr = outputs[1];
		FAUSTFLOAT* output2_ptr = outputs[2];
		FAUSTFLOAT* output3_ptr = outputs[3];
		FAUSTFLOAT* output4_ptr = outputs[4];
		FAUSTFLOAT* output5_ptr = outputs[5];
		FAUSTFLOAT* output6_ptr = outputs[6];
		FAUSTFLOAT* output7_ptr = outputs[7];
		FAUSTFLOAT* output8_ptr = outputs[8];
		FAUSTFLOAT* output9_ptr = outputs[9];
		FAUSTFLOAT* output10_ptr = outputs[10];
		FAUSTFLOAT* output11_ptr = outputs[11];
		FAUSTFLOAT* output12_ptr = outputs[12];
		FAUSTFLOAT* output13_ptr = outputs[13];
		FAUSTFLOAT* output14_ptr = outputs[14];
		FAUSTFLOAT* output15_ptr = outputs[15];
		FAUSTFLOAT* output16_ptr = outputs[16];
		FAUSTFLOAT* output17_ptr = outputs[17];
		FAUSTFLOAT* output18_ptr = outputs[18];
		FAUSTFLOAT* output19_ptr = outputs[19];
		FAUSTFLOAT* output20_ptr = outputs[20];
		FAUSTFLOAT* output21_ptr = outputs[21];
		FAUSTFLOAT* output22_ptr = outputs[22];
		FAUSTFLOAT* output23_ptr = outputs[23];
		FAUSTFLOAT* output24_ptr = outputs[24];
		FAUSTFLOAT* output25_ptr = outputs[25];
		FAUSTFLOAT* output26_ptr = outputs[26];
		FAUSTFLOAT* output27_ptr = outputs[27];
		FAUSTFLOAT* output28_ptr = outputs[28];
		FAUSTFLOAT* output29_ptr = outputs[29];
		FAUSTFLOAT* output30_ptr = outputs[30];
		FAUSTFLOAT* output31_ptr = outputs[31];
		double fZec0[4];
		double fZec1[4];
		double fZec2[4];
		double fZec3[4];
		double fZec4[4];
		int vindex = 0;
		/* Main loop */
		for (vindex = 0; vindex <= (faust_wrap_sub(count, 4)); vindex = faust_wrap_add(vindex, 4)) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* input1 = &input1_ptr[vindex];
			FAUSTFLOAT* input2 = &input2_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			FAUSTFLOAT* output1 = &output1_ptr[vindex];
			FAUSTFLOAT* output2 = &output2_ptr[vindex];
			FAUSTFLOAT* output3 = &output3_ptr[vindex];
			FAUSTFLOAT* output4 = &output4_ptr[vindex];
			FAUSTFLOAT* output5 = &output5_ptr[vindex];
			FAUSTFLOAT* output6 = &output6_ptr[vindex];
			FAUSTFLOAT* output7 = &output7_ptr[vindex];
			FAUSTFLOAT* output8 = &output8_ptr[vindex];
			FAUSTFLOAT* output9 = &output9_ptr[vindex];
			FAUSTFLOAT* output10 = &output10_ptr[vindex];
			FAUSTFLOAT* output11 = &output11_ptr[vindex];
			FAUSTFLOAT* output12 = &output12_ptr[vindex];
			FAUSTFLOAT* output13 = &output13_ptr[vindex];
			FAUSTFLOAT* output14 = &output14_ptr[vindex];
			FAUSTFLOAT* output15 = &output15_ptr[vindex];
			FAUSTFLOAT* output16 = &output16_ptr[vindex];
			FAUSTFLOAT* output17 = &output17_ptr[vindex];
			FAUSTFLOAT* output18 = &output18_ptr[vindex];
			FAUSTFLOAT* output19 = &output19_ptr[vindex];
			FAUSTFLOAT* output20 = &output20_ptr[vindex];
			FAUSTFLOAT* output21 = &output21_ptr[vindex];
			FAUSTFLOAT* output22 = &output22_ptr[vindex];
			FAUSTFLOAT* output23 = &output23_ptr[vindex];
			FAUSTFLOAT* output24 = &output24_ptr[vindex];
			FAUSTFLOAT* output25 = &output25_ptr[vindex];
			FAUSTFLOAT* output26 = &output26_ptr[vindex];
			FAUSTFLOAT* output27 = &output27_ptr[vindex];
			FAUSTFLOAT* output28 = &output28_ptr[vindex];
			FAUSTFLOAT* output29 = &output29_ptr[vindex];
			FAUSTFLOAT* output30 = &output30_ptr[vindex];
			FAUSTFLOAT* output31 = &output31_ptr[vindex];
			int vsize = 4;
			/* Vectorizable loop 0 */
			/* Pre code */
			fYec0_idx = (faust_wrap_add(fYec0_idx, fYec0_idx_save)) & 15;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec0[(faust_wrap_add(i, fYec0_idx)) & 15] = static_cast<double>(input0[i]);
			}
			/* Post code */
			fYec0_idx_save = vsize;
			/* Vectorizable loop 1 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(-(static_cast<double>(input0[i])));
			}
			/* Vectorizable loop 2 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(-(static_cast<double>(input0[i])));
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output2[i] = static_cast<FAUSTFLOAT>(-(static_cast<double>(input0[i])));
			}
			/* Vectorizable loop 4 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output3[i] = static_cast<FAUSTFLOAT>(static_cast<double>(input0[i]));
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec0[i] = static_cast<double>(input0[i]) - static_cast<double>(input1[i]);
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output4[i] = static_cast<FAUSTFLOAT>(fZec0[i]);
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec1[i] = static_cast<double>(input1[i]) - static_cast<double>(input0[i]);
			}
			/* Vectorizable loop 8 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output5[i] = static_cast<FAUSTFLOAT>(fZec1[i]);
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output6[i] = static_cast<FAUSTFLOAT>(fZec0[i]);
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec2[i] = static_cast<double>(input0[i]) - (static_cast<double>(input1[i]) + static_cast<double>(input2[i]));
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output7[i] = static_cast<FAUSTFLOAT>(fZec2[i]);
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output8[i] = static_cast<FAUSTFLOAT>(fZec2[i]);
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output9[i] = static_cast<FAUSTFLOAT>(3.0 * fZec1[i]);
			}
			/* Vectorizable loop 14 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output10[i] = static_cast<FAUSTFLOAT>(static_cast<double>(input1[i]) + 3.0 * fZec0[i] - static_cast<double>(input0[i]));
			}
			/* Vectorizable loop 15 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output11[i] = static_cast<FAUSTFLOAT>(4.0 * std::fabs(fZec1[i]));
			}
			/* Vectorizable loop 16 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output12[i] = static_cast<FAUSTFLOAT>(-fConst0);
			}
			/* Vectorizable loop 17 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec3[i] = fConst0 * static_cast<double>(input0[i]);
			}
			/* Vectorizable loop 18 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output13[i] = static_cast<FAUSTFLOAT>(-(fZec3[i]));
			}
			/* Vectorizable loop 19 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output14[i] = static_cast<FAUSTFLOAT>(-(-(static_cast<double>(input0[i]))));
			}
			/* Vectorizable loop 20 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output15[i] = static_cast<FAUSTFLOAT>(-(static_cast<double>(input0[i])));
			}
			/* Vectorizable loop 21 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output16[i] = static_cast<FAUSTFLOAT>(-fConst0);
			}
			/* Vectorizable loop 22 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output17[i] = static_cast<FAUSTFLOAT>(-(fZec3[i]));
			}
			/* Vectorizable loop 23 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output18[i] = static_cast<FAUSTFLOAT>(fZec3[i]);
			}
			/* Vectorizable loop 24 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output19[i] = static_cast<FAUSTFLOAT>(-fConst0);
			}
			/* Vectorizable loop 25 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output20[i] = static_cast<FAUSTFLOAT>(-(fZec3[i]));
			}
			/* Vectorizable loop 26 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output21[i] = static_cast<FAUSTFLOAT>(fConst0);
			}
			/* Vectorizable loop 27 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output22[i] = static_cast<FAUSTFLOAT>(-(static_cast<double>(input0[i]) + static_cast<double>(input1[i])));
			}
			/* Vectorizable loop 28 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output23[i] = static_cast<FAUSTFLOAT>(-(static_cast<double>(input0[i]) + static_cast<double>(input1[i])));
			}
			/* Vectorizable loop 29 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output24[i] = static_cast<FAUSTFLOAT>(-(fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 10)) & 15]));
			}
			/* Vectorizable loop 30 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output25[i] = static_cast<FAUSTFLOAT>(-(fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 10)) & 15]));
			}
			/* Vectorizable loop 31 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec4[i] = 3.0 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 1)) & 15];
			}
			/* Vectorizable loop 32 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output26[i] = static_cast<FAUSTFLOAT>(fZec4[i]);
			}
			/* Vectorizable loop 33 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output27[i] = static_cast<FAUSTFLOAT>(3.0 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 2)) & 15]);
			}
			/* Vectorizable loop 34 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output28[i] = static_cast<FAUSTFLOAT>(fZec4[i]);
			}
			/* Vectorizable loop 35 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output29[i] = static_cast<FAUSTFLOAT>(4.0 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 2)) & 15]);
			}
			/* Vectorizable loop 36 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output30[i] = static_cast<FAUSTFLOAT>(-(fConst0 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 1)) & 15]));
			}
			/* Vectorizable loop 37 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output31[i] = static_cast<FAUSTFLOAT>(-(fConst0 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 2)) & 15]));
			}
		}
		/* Remaining frames */
		if (vindex < count) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* input1 = &input1_ptr[vindex];
			FAUSTFLOAT* input2 = &input2_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			FAUSTFLOAT* output1 = &output1_ptr[vindex];
			FAUSTFLOAT* output2 = &output2_ptr[vindex];
			FAUSTFLOAT* output3 = &output3_ptr[vindex];
			FAUSTFLOAT* output4 = &output4_ptr[vindex];
			FAUSTFLOAT* output5 = &output5_ptr[vindex];
			FAUSTFLOAT* output6 = &output6_ptr[vindex];
			FAUSTFLOAT* output7 = &output7_ptr[vindex];
			FAUSTFLOAT* output8 = &output8_ptr[vindex];
			FAUSTFLOAT* output9 = &output9_ptr[vindex];
			FAUSTFLOAT* output10 = &output10_ptr[vindex];
			FAUSTFLOAT* output11 = &output11_ptr[vindex];
			FAUSTFLOAT* output12 = &output12_ptr[vindex];
			FAUSTFLOAT* output13 = &output13_ptr[vindex];
			FAUSTFLOAT* output14 = &output14_ptr[vindex];
			FAUSTFLOAT* output15 = &output15_ptr[vindex];
			FAUSTFLOAT* output16 = &output16_ptr[vindex];
			FAUSTFLOAT* output17 = &output17_ptr[vindex];
			FAUSTFLOAT* output18 = &output18_ptr[vindex];
			FAUSTFLOAT* output19 = &output19_ptr[vindex];
			FAUSTFLOAT* output20 = &output20_ptr[vindex];
			FAUSTFLOAT* output21 = &output21_ptr[vindex];
			FAUSTFLOAT* output22 = &output22_ptr[vindex];
			FAUSTFLOAT* output23 = &output23_ptr[vindex];
			FAUSTFLOAT* output24 = &output24_ptr[vindex];
			FAUSTFLOAT* output25 = &output25_ptr[vindex];
			FAUSTFLOAT* output26 = &output26_ptr[vindex];
			FAUSTFLOAT* output27 = &output27_ptr[vindex];
			FAUSTFLOAT* output28 = &output28_ptr[vindex];
			FAUSTFLOAT* output29 = &output29_ptr[vindex];
			FAUSTFLOAT* output30 = &output30_ptr[vindex];
			FAUSTFLOAT* output31 = &output31_ptr[vindex];
			int vsize = faust_wrap_sub(count, vindex);
			/* Vectorizable loop 0 */
			/* Pre code */
			fYec0_idx = (faust_wrap_add(fYec0_idx, fYec0_idx_save)) & 15;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec0[(faust_wrap_add(i, fYec0_idx)) & 15] = static_cast<double>(input0[i]);
			}
			/* Post code */
			fYec0_idx_save = vsize;
			/* Vectorizable loop 1 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(-(static_cast<double>(input0[i])));
			}
			/* Vectorizable loop 2 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(-(static_cast<double>(input0[i])));
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output2[i] = static_cast<FAUSTFLOAT>(-(static_cast<double>(input0[i])));
			}
			/* Vectorizable loop 4 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output3[i] = static_cast<FAUSTFLOAT>(static_cast<double>(input0[i]));
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec0[i] = static_cast<double>(input0[i]) - static_cast<double>(input1[i]);
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output4[i] = static_cast<FAUSTFLOAT>(fZec0[i]);
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec1[i] = static_cast<double>(input1[i]) - static_cast<double>(input0[i]);
			}
			/* Vectorizable loop 8 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output5[i] = static_cast<FAUSTFLOAT>(fZec1[i]);
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output6[i] = static_cast<FAUSTFLOAT>(fZec0[i]);
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec2[i] = static_cast<double>(input0[i]) - (static_cast<double>(input1[i]) + static_cast<double>(input2[i]));
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output7[i] = static_cast<FAUSTFLOAT>(fZec2[i]);
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output8[i] = static_cast<FAUSTFLOAT>(fZec2[i]);
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output9[i] = static_cast<FAUSTFLOAT>(3.0 * fZec1[i]);
			}
			/* Vectorizable loop 14 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output10[i] = static_cast<FAUSTFLOAT>(static_cast<double>(input1[i]) + 3.0 * fZec0[i] - static_cast<double>(input0[i]));
			}
			/* Vectorizable loop 15 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output11[i] = static_cast<FAUSTFLOAT>(4.0 * std::fabs(fZec1[i]));
			}
			/* Vectorizable loop 16 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output12[i] = static_cast<FAUSTFLOAT>(-fConst0);
			}
			/* Vectorizable loop 17 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec3[i] = fConst0 * static_cast<double>(input0[i]);
			}
			/* Vectorizable loop 18 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output13[i] = static_cast<FAUSTFLOAT>(-(fZec3[i]));
			}
			/* Vectorizable loop 19 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output14[i] = static_cast<FAUSTFLOAT>(-(-(static_cast<double>(input0[i]))));
			}
			/* Vectorizable loop 20 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output15[i] = static_cast<FAUSTFLOAT>(-(static_cast<double>(input0[i])));
			}
			/* Vectorizable loop 21 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output16[i] = static_cast<FAUSTFLOAT>(-fConst0);
			}
			/* Vectorizable loop 22 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output17[i] = static_cast<FAUSTFLOAT>(-(fZec3[i]));
			}
			/* Vectorizable loop 23 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output18[i] = static_cast<FAUSTFLOAT>(fZec3[i]);
			}
			/* Vectorizable loop 24 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output19[i] = static_cast<FAUSTFLOAT>(-fConst0);
			}
			/* Vectorizable loop 25 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output20[i] = static_cast<FAUSTFLOAT>(-(fZec3[i]));
			}
			/* Vectorizable loop 26 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output21[i] = static_cast<FAUSTFLOAT>(fConst0);
			}
			/* Vectorizable loop 27 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output22[i] = static_cast<FAUSTFLOAT>(-(static_cast<double>(input0[i]) + static_cast<double>(input1[i])));
			}
			/* Vectorizable loop 28 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output23[i] = static_cast<FAUSTFLOAT>(-(static_cast<double>(input0[i]) + static_cast<double>(input1[i])));
			}
			/* Vectorizable loop 29 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output24[i] = static_cast<FAUSTFLOAT>(-(fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 10)) & 15]));
			}
			/* Vectorizable loop 30 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output25[i] = static_cast<FAUSTFLOAT>(-(fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 10)) & 15]));
			}
			/* Vectorizable loop 31 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec4[i] = 3.0 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 1)) & 15];
			}
			/* Vectorizable loop 32 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output26[i] = static_cast<FAUSTFLOAT>(fZec4[i]);
			}
			/* Vectorizable loop 33 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output27[i] = static_cast<FAUSTFLOAT>(3.0 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 2)) & 15]);
			}
			/* Vectorizable loop 34 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output28[i] = static_cast<FAUSTFLOAT>(fZec4[i]);
			}
			/* Vectorizable loop 35 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output29[i] = static_cast<FAUSTFLOAT>(4.0 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 2)) & 15]);
			}
			/* Vectorizable loop 36 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output30[i] = static_cast<FAUSTFLOAT>(-(fConst0 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 1)) & 15]));
			}
			/* Vectorizable loop 37 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output31[i] = static_cast<FAUSTFLOAT>(-(fConst0 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 2)) & 15]));
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
