/* ------------------------------------------------------------
name: "norm3"
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
	double fYec0_perm[4];
	FAUSTFLOAT fHslider1;
	double fYec1_perm[4];
	double fYec2[64];
	int fYec2_idx;
	int fYec2_idx_save;
	double fYec3[128];
	int fYec3_idx;
	int fYec3_idx_save;
	FAUSTFLOAT fHslider2;
	double fYec4[128];
	int fYec4_idx;
	int fYec4_idx_save;
	FAUSTFLOAT fHslider3;
	double fYec5[16];
	int fYec5_idx;
	int fYec5_idx_save;
	double fYec6[128];
	int fYec6_idx;
	int fYec6_idx_save;
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT fHslider5;
	FAUSTFLOAT fHslider6;
	int fSampleRate;
	
 public:
	mydsp() {
	}
	
	mydsp(const mydsp&) = default;
	
	virtual ~mydsp() = default;
	
	mydsp& operator=(const mydsp&) = default;
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-a /Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/archs/impulsearch.cpp -lang cpp -i -fpga-mem-th 4 -ct 1 -es 1 -mcd 4 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs");
		m->declare("filename", "norm3.dsp");
		m->declare("name", "norm3");
	}

	virtual int getNumInputs() {
		return 11;
	}
	virtual int getNumOutputs() {
		return 11;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(2.0);
		fHslider1 = static_cast<FAUSTFLOAT>(2.0);
		fHslider2 = static_cast<FAUSTFLOAT>(1e+01);
		fHslider3 = static_cast<FAUSTFLOAT>(2e+01);
		fHslider4 = static_cast<FAUSTFLOAT>(2e+01);
		fHslider5 = static_cast<FAUSTFLOAT>(0.0);
		fHslider6 = static_cast<FAUSTFLOAT>(0.0);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 4; l0 = faust_wrap_add(l0, 1)) {
			fYec0_perm[l0] = 0.0;
		}
		for (int l1 = 0; l1 < 4; l1 = faust_wrap_add(l1, 1)) {
			fYec1_perm[l1] = 0.0;
		}
		for (int l2 = 0; l2 < 64; l2 = faust_wrap_add(l2, 1)) {
			fYec2[l2] = 0.0;
		}
		fYec2_idx = 0;
		fYec2_idx_save = 0;
		for (int l3 = 0; l3 < 128; l3 = faust_wrap_add(l3, 1)) {
			fYec3[l3] = 0.0;
		}
		fYec3_idx = 0;
		fYec3_idx_save = 0;
		for (int l4 = 0; l4 < 128; l4 = faust_wrap_add(l4, 1)) {
			fYec4[l4] = 0.0;
		}
		fYec4_idx = 0;
		fYec4_idx_save = 0;
		for (int l5 = 0; l5 < 16; l5 = faust_wrap_add(l5, 1)) {
			fYec5[l5] = 0.0;
		}
		fYec5_idx = 0;
		fYec5_idx_save = 0;
		for (int l6 = 0; l6 < 128; l6 = faust_wrap_add(l6, 1)) {
			fYec6[l6] = 0.0;
		}
		fYec6_idx = 0;
		fYec6_idx_save = 0;
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
		ui_interface->openVerticalBox("norm3");
		ui_interface->addHorizontalSlider("1.1_c", &fHslider0, FAUSTFLOAT(2.0), FAUSTFLOAT(1.0), FAUSTFLOAT(1e+01), FAUSTFLOAT(1.0));
		ui_interface->addHorizontalSlider("1.2_c", &fHslider1, FAUSTFLOAT(2.0), FAUSTFLOAT(1.0), FAUSTFLOAT(1e+01), FAUSTFLOAT(1.0));
		ui_interface->addHorizontalSlider("1.4_c1", &fHslider2, FAUSTFLOAT(1e+01), FAUSTFLOAT(1.0), FAUSTFLOAT(1e+02), FAUSTFLOAT(1.0));
		ui_interface->addHorizontalSlider("1.4_c2", &fHslider3, FAUSTFLOAT(2e+01), FAUSTFLOAT(1.0), FAUSTFLOAT(1e+02), FAUSTFLOAT(1.0));
		ui_interface->addHorizontalSlider("1.5_c", &fHslider4, FAUSTFLOAT(2e+01), FAUSTFLOAT(1.0), FAUSTFLOAT(1e+02), FAUSTFLOAT(1.0));
		ui_interface->addHorizontalSlider("3.1_x", &fHslider5, FAUSTFLOAT(0.0), FAUSTFLOAT(-1.0), FAUSTFLOAT(1.0), FAUSTFLOAT(1.0));
		ui_interface->addHorizontalSlider("3.2_y", &fHslider6, FAUSTFLOAT(0.0), FAUSTFLOAT(-1.0), FAUSTFLOAT(1.0), FAUSTFLOAT(1.0));
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
		FAUSTFLOAT* input8_ptr = inputs[8];
		FAUSTFLOAT* input9_ptr = inputs[9];
		FAUSTFLOAT* input10_ptr = inputs[10];
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
		double fSlow0 = static_cast<double>(fHslider0);
		double fYec0_tmp[8];
		double* fYec0 = &fYec0_tmp[4];
		double fSlow1 = 1.0 / static_cast<double>(fHslider1);
		double fYec1_tmp[8];
		double* fYec1 = &fYec1_tmp[4];
		int iSlow2 = static_cast<int>(static_cast<double>(fHslider2));
		int iSlow3 = static_cast<int>(static_cast<double>(fHslider3));
		int iSlow4 = static_cast<int>(static_cast<double>(fHslider4));
		double fSlow5 = static_cast<double>(fHslider5);
		double fSlow6 = static_cast<double>(fHslider6);
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
			FAUSTFLOAT* input8 = &input8_ptr[vindex];
			FAUSTFLOAT* input9 = &input9_ptr[vindex];
			FAUSTFLOAT* input10 = &input10_ptr[vindex];
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
			int vsize = 4;
			/* Vectorizable loop 0 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				fYec0_tmp[j0] = fYec0_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec0[i] = fSlow0 * static_cast<double>(input0[i]);
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				fYec0_perm[j1] = fYec0_tmp[faust_wrap_add(vsize, j1)];
			}
			/* Vectorizable loop 1 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fYec0[faust_wrap_sub(i, 1)]);
			}
			/* Vectorizable loop 2 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fYec1_tmp[j2] = fYec1_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec1[i] = fSlow1 * static_cast<double>(input1[i]);
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fYec1_perm[j3] = fYec1_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fYec1[faust_wrap_sub(i, 1)]);
			}
			/* Vectorizable loop 4 */
			/* Pre code */
			fYec2_idx = (faust_wrap_add(fYec2_idx, fYec2_idx_save)) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec2[(faust_wrap_add(i, fYec2_idx)) & 63] = static_cast<double>(input2[i]);
			}
			/* Post code */
			fYec2_idx_save = vsize;
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output2[i] = static_cast<FAUSTFLOAT>(fYec2[(faust_wrap_sub(faust_wrap_add(i, fYec2_idx), 30)) & 63]);
			}
			/* Vectorizable loop 6 */
			/* Pre code */
			fYec3_idx = (faust_wrap_add(fYec3_idx, fYec3_idx_save)) & 127;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec3[(faust_wrap_add(i, fYec3_idx)) & 127] = static_cast<double>(input3[i]);
			}
			/* Post code */
			fYec3_idx_save = vsize;
			/* Vectorizable loop 7 */
			/* Pre code */
			fYec4_idx = (faust_wrap_add(fYec4_idx, fYec4_idx_save)) & 127;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec4[(faust_wrap_add(i, fYec4_idx)) & 127] = fYec3[(faust_wrap_sub(faust_wrap_add(i, fYec3_idx), iSlow2)) & 127];
			}
			/* Post code */
			fYec4_idx_save = vsize;
			/* Vectorizable loop 8 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output3[i] = static_cast<FAUSTFLOAT>(fYec4[(faust_wrap_sub(faust_wrap_add(i, fYec4_idx), iSlow3)) & 127]);
			}
			/* Vectorizable loop 9 */
			/* Pre code */
			fYec5_idx = (faust_wrap_add(fYec5_idx, fYec5_idx_save)) & 15;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec5[(faust_wrap_add(i, fYec5_idx)) & 15] = static_cast<double>(input4[i]);
			}
			/* Post code */
			fYec5_idx_save = vsize;
			/* Vectorizable loop 10 */
			/* Pre code */
			fYec6_idx = (faust_wrap_add(fYec6_idx, fYec6_idx_save)) & 127;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec6[(faust_wrap_add(i, fYec6_idx)) & 127] = fYec5[(faust_wrap_sub(faust_wrap_add(i, fYec5_idx), static_cast<int>(1e+01 * std::fabs(static_cast<double>(input5[i]))))) & 15];
			}
			/* Post code */
			fYec6_idx_save = vsize;
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output4[i] = static_cast<FAUSTFLOAT>(fYec6[(faust_wrap_sub(faust_wrap_add(i, fYec6_idx), iSlow4)) & 127]);
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output5[i] = static_cast<FAUSTFLOAT>(static_cast<double>(input6[i]));
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output6[i] = static_cast<FAUSTFLOAT>(3);
			}
			/* Vectorizable loop 14 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output7[i] = static_cast<FAUSTFLOAT>(5.0);
			}
			/* Vectorizable loop 15 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output8[i] = static_cast<FAUSTFLOAT>(fSlow5);
			}
			/* Vectorizable loop 16 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output9[i] = static_cast<FAUSTFLOAT>(fSlow6);
			}
			/* Vectorizable loop 17 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output10[i] = static_cast<FAUSTFLOAT>(static_cast<double>(input7[i]));
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
			FAUSTFLOAT* input8 = &input8_ptr[vindex];
			FAUSTFLOAT* input9 = &input9_ptr[vindex];
			FAUSTFLOAT* input10 = &input10_ptr[vindex];
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
			int vsize = faust_wrap_sub(count, vindex);
			/* Vectorizable loop 0 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				fYec0_tmp[j0] = fYec0_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec0[i] = fSlow0 * static_cast<double>(input0[i]);
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				fYec0_perm[j1] = fYec0_tmp[faust_wrap_add(vsize, j1)];
			}
			/* Vectorizable loop 1 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fYec0[faust_wrap_sub(i, 1)]);
			}
			/* Vectorizable loop 2 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fYec1_tmp[j2] = fYec1_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec1[i] = fSlow1 * static_cast<double>(input1[i]);
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fYec1_perm[j3] = fYec1_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fYec1[faust_wrap_sub(i, 1)]);
			}
			/* Vectorizable loop 4 */
			/* Pre code */
			fYec2_idx = (faust_wrap_add(fYec2_idx, fYec2_idx_save)) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec2[(faust_wrap_add(i, fYec2_idx)) & 63] = static_cast<double>(input2[i]);
			}
			/* Post code */
			fYec2_idx_save = vsize;
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output2[i] = static_cast<FAUSTFLOAT>(fYec2[(faust_wrap_sub(faust_wrap_add(i, fYec2_idx), 30)) & 63]);
			}
			/* Vectorizable loop 6 */
			/* Pre code */
			fYec3_idx = (faust_wrap_add(fYec3_idx, fYec3_idx_save)) & 127;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec3[(faust_wrap_add(i, fYec3_idx)) & 127] = static_cast<double>(input3[i]);
			}
			/* Post code */
			fYec3_idx_save = vsize;
			/* Vectorizable loop 7 */
			/* Pre code */
			fYec4_idx = (faust_wrap_add(fYec4_idx, fYec4_idx_save)) & 127;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec4[(faust_wrap_add(i, fYec4_idx)) & 127] = fYec3[(faust_wrap_sub(faust_wrap_add(i, fYec3_idx), iSlow2)) & 127];
			}
			/* Post code */
			fYec4_idx_save = vsize;
			/* Vectorizable loop 8 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output3[i] = static_cast<FAUSTFLOAT>(fYec4[(faust_wrap_sub(faust_wrap_add(i, fYec4_idx), iSlow3)) & 127]);
			}
			/* Vectorizable loop 9 */
			/* Pre code */
			fYec5_idx = (faust_wrap_add(fYec5_idx, fYec5_idx_save)) & 15;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec5[(faust_wrap_add(i, fYec5_idx)) & 15] = static_cast<double>(input4[i]);
			}
			/* Post code */
			fYec5_idx_save = vsize;
			/* Vectorizable loop 10 */
			/* Pre code */
			fYec6_idx = (faust_wrap_add(fYec6_idx, fYec6_idx_save)) & 127;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec6[(faust_wrap_add(i, fYec6_idx)) & 127] = fYec5[(faust_wrap_sub(faust_wrap_add(i, fYec5_idx), static_cast<int>(1e+01 * std::fabs(static_cast<double>(input5[i]))))) & 15];
			}
			/* Post code */
			fYec6_idx_save = vsize;
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output4[i] = static_cast<FAUSTFLOAT>(fYec6[(faust_wrap_sub(faust_wrap_add(i, fYec6_idx), iSlow4)) & 127]);
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output5[i] = static_cast<FAUSTFLOAT>(static_cast<double>(input6[i]));
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output6[i] = static_cast<FAUSTFLOAT>(3);
			}
			/* Vectorizable loop 14 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output7[i] = static_cast<FAUSTFLOAT>(5.0);
			}
			/* Vectorizable loop 15 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output8[i] = static_cast<FAUSTFLOAT>(fSlow5);
			}
			/* Vectorizable loop 16 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output9[i] = static_cast<FAUSTFLOAT>(fSlow6);
			}
			/* Vectorizable loop 17 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output10[i] = static_cast<FAUSTFLOAT>(static_cast<double>(input7[i]));
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
