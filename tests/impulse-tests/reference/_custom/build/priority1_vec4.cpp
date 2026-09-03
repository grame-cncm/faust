/* ------------------------------------------------------------
name: "priority1"
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
	
	double fRec0_perm[4];
	double fRec1_perm[4];
	double fRec2_perm[4];
	double fRec3_perm[4];
	double fRec4_perm[4];
	double fRec5_perm[4];
	double fRec6_perm[4];
	double fRec7_perm[4];
	double fRec8_perm[4];
	double fRec9_perm[4];
	double fRec10_perm[4];
	double fRec11_perm[4];
	double fRec12_perm[4];
	double fRec13_perm[4];
	double fRec14_perm[4];
	double fRec15_perm[4];
	double fRec16_perm[4];
	double fRec17_perm[4];
	double fRec18_perm[4];
	double fRec19_perm[4];
	double fRec20_perm[4];
	double fRec21_perm[4];
	double fRec22_perm[4];
	double fRec23_perm[4];
	double fRec24_perm[4];
	double fRec25_perm[4];
	double fRec26_perm[4];
	double fRec27_perm[4];
	double fRec28_perm[4];
	double fRec29_perm[4];
	double fRec30_perm[4];
	double fRec31_perm[4];
	double fRec32_perm[4];
	double fRec33_perm[4];
	double fRec34_perm[4];
	double fRec35_perm[4];
	double fRec36_perm[4];
	double fRec37_perm[4];
	double fRec38_perm[4];
	double fRec39_perm[4];
	double fRec40_perm[4];
	double fRec41_perm[4];
	double fRec42_perm[4];
	int fSampleRate;
	
 public:
	mydsp() {
	}
	
	mydsp(const mydsp&) = default;
	
	virtual ~mydsp() = default;
	
	mydsp& operator=(const mydsp&) = default;
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-a /Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/archs/impulsearch.cpp -lang cpp -i -fpga-mem-th 4 -ct 1 -es 1 -mcd 4 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs");
		m->declare("filename", "priority1.dsp");
		m->declare("name", "priority1");
	}

	virtual int getNumInputs() {
		return 110;
	}
	virtual int getNumOutputs() {
		return 31;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
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
		for (int l8 = 0; l8 < 4; l8 = faust_wrap_add(l8, 1)) {
			fRec8_perm[l8] = 0.0;
		}
		for (int l9 = 0; l9 < 4; l9 = faust_wrap_add(l9, 1)) {
			fRec9_perm[l9] = 0.0;
		}
		for (int l10 = 0; l10 < 4; l10 = faust_wrap_add(l10, 1)) {
			fRec10_perm[l10] = 0.0;
		}
		for (int l11 = 0; l11 < 4; l11 = faust_wrap_add(l11, 1)) {
			fRec11_perm[l11] = 0.0;
		}
		for (int l12 = 0; l12 < 4; l12 = faust_wrap_add(l12, 1)) {
			fRec12_perm[l12] = 0.0;
		}
		for (int l13 = 0; l13 < 4; l13 = faust_wrap_add(l13, 1)) {
			fRec13_perm[l13] = 0.0;
		}
		for (int l14 = 0; l14 < 4; l14 = faust_wrap_add(l14, 1)) {
			fRec14_perm[l14] = 0.0;
		}
		for (int l15 = 0; l15 < 4; l15 = faust_wrap_add(l15, 1)) {
			fRec15_perm[l15] = 0.0;
		}
		for (int l16 = 0; l16 < 4; l16 = faust_wrap_add(l16, 1)) {
			fRec16_perm[l16] = 0.0;
		}
		for (int l17 = 0; l17 < 4; l17 = faust_wrap_add(l17, 1)) {
			fRec17_perm[l17] = 0.0;
		}
		for (int l18 = 0; l18 < 4; l18 = faust_wrap_add(l18, 1)) {
			fRec18_perm[l18] = 0.0;
		}
		for (int l19 = 0; l19 < 4; l19 = faust_wrap_add(l19, 1)) {
			fRec19_perm[l19] = 0.0;
		}
		for (int l20 = 0; l20 < 4; l20 = faust_wrap_add(l20, 1)) {
			fRec20_perm[l20] = 0.0;
		}
		for (int l21 = 0; l21 < 4; l21 = faust_wrap_add(l21, 1)) {
			fRec21_perm[l21] = 0.0;
		}
		for (int l22 = 0; l22 < 4; l22 = faust_wrap_add(l22, 1)) {
			fRec22_perm[l22] = 0.0;
		}
		for (int l23 = 0; l23 < 4; l23 = faust_wrap_add(l23, 1)) {
			fRec23_perm[l23] = 0.0;
		}
		for (int l24 = 0; l24 < 4; l24 = faust_wrap_add(l24, 1)) {
			fRec24_perm[l24] = 0.0;
		}
		for (int l25 = 0; l25 < 4; l25 = faust_wrap_add(l25, 1)) {
			fRec25_perm[l25] = 0.0;
		}
		for (int l26 = 0; l26 < 4; l26 = faust_wrap_add(l26, 1)) {
			fRec26_perm[l26] = 0.0;
		}
		for (int l27 = 0; l27 < 4; l27 = faust_wrap_add(l27, 1)) {
			fRec27_perm[l27] = 0.0;
		}
		for (int l28 = 0; l28 < 4; l28 = faust_wrap_add(l28, 1)) {
			fRec28_perm[l28] = 0.0;
		}
		for (int l29 = 0; l29 < 4; l29 = faust_wrap_add(l29, 1)) {
			fRec29_perm[l29] = 0.0;
		}
		for (int l30 = 0; l30 < 4; l30 = faust_wrap_add(l30, 1)) {
			fRec30_perm[l30] = 0.0;
		}
		for (int l31 = 0; l31 < 4; l31 = faust_wrap_add(l31, 1)) {
			fRec31_perm[l31] = 0.0;
		}
		for (int l32 = 0; l32 < 4; l32 = faust_wrap_add(l32, 1)) {
			fRec32_perm[l32] = 0.0;
		}
		for (int l33 = 0; l33 < 4; l33 = faust_wrap_add(l33, 1)) {
			fRec33_perm[l33] = 0.0;
		}
		for (int l34 = 0; l34 < 4; l34 = faust_wrap_add(l34, 1)) {
			fRec34_perm[l34] = 0.0;
		}
		for (int l35 = 0; l35 < 4; l35 = faust_wrap_add(l35, 1)) {
			fRec35_perm[l35] = 0.0;
		}
		for (int l36 = 0; l36 < 4; l36 = faust_wrap_add(l36, 1)) {
			fRec36_perm[l36] = 0.0;
		}
		for (int l37 = 0; l37 < 4; l37 = faust_wrap_add(l37, 1)) {
			fRec37_perm[l37] = 0.0;
		}
		for (int l38 = 0; l38 < 4; l38 = faust_wrap_add(l38, 1)) {
			fRec38_perm[l38] = 0.0;
		}
		for (int l39 = 0; l39 < 4; l39 = faust_wrap_add(l39, 1)) {
			fRec39_perm[l39] = 0.0;
		}
		for (int l40 = 0; l40 < 4; l40 = faust_wrap_add(l40, 1)) {
			fRec40_perm[l40] = 0.0;
		}
		for (int l41 = 0; l41 < 4; l41 = faust_wrap_add(l41, 1)) {
			fRec41_perm[l41] = 0.0;
		}
		for (int l42 = 0; l42 < 4; l42 = faust_wrap_add(l42, 1)) {
			fRec42_perm[l42] = 0.0;
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
		ui_interface->openVerticalBox("priority1");
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
		FAUSTFLOAT* input11_ptr = inputs[11];
		FAUSTFLOAT* input12_ptr = inputs[12];
		FAUSTFLOAT* input13_ptr = inputs[13];
		FAUSTFLOAT* input14_ptr = inputs[14];
		FAUSTFLOAT* input15_ptr = inputs[15];
		FAUSTFLOAT* input16_ptr = inputs[16];
		FAUSTFLOAT* input17_ptr = inputs[17];
		FAUSTFLOAT* input18_ptr = inputs[18];
		FAUSTFLOAT* input19_ptr = inputs[19];
		FAUSTFLOAT* input20_ptr = inputs[20];
		FAUSTFLOAT* input21_ptr = inputs[21];
		FAUSTFLOAT* input22_ptr = inputs[22];
		FAUSTFLOAT* input23_ptr = inputs[23];
		FAUSTFLOAT* input24_ptr = inputs[24];
		FAUSTFLOAT* input25_ptr = inputs[25];
		FAUSTFLOAT* input26_ptr = inputs[26];
		FAUSTFLOAT* input27_ptr = inputs[27];
		FAUSTFLOAT* input28_ptr = inputs[28];
		FAUSTFLOAT* input29_ptr = inputs[29];
		FAUSTFLOAT* input30_ptr = inputs[30];
		FAUSTFLOAT* input31_ptr = inputs[31];
		FAUSTFLOAT* input32_ptr = inputs[32];
		FAUSTFLOAT* input33_ptr = inputs[33];
		FAUSTFLOAT* input34_ptr = inputs[34];
		FAUSTFLOAT* input35_ptr = inputs[35];
		FAUSTFLOAT* input36_ptr = inputs[36];
		FAUSTFLOAT* input37_ptr = inputs[37];
		FAUSTFLOAT* input38_ptr = inputs[38];
		FAUSTFLOAT* input39_ptr = inputs[39];
		FAUSTFLOAT* input40_ptr = inputs[40];
		FAUSTFLOAT* input41_ptr = inputs[41];
		FAUSTFLOAT* input42_ptr = inputs[42];
		FAUSTFLOAT* input43_ptr = inputs[43];
		FAUSTFLOAT* input44_ptr = inputs[44];
		FAUSTFLOAT* input45_ptr = inputs[45];
		FAUSTFLOAT* input46_ptr = inputs[46];
		FAUSTFLOAT* input47_ptr = inputs[47];
		FAUSTFLOAT* input48_ptr = inputs[48];
		FAUSTFLOAT* input49_ptr = inputs[49];
		FAUSTFLOAT* input50_ptr = inputs[50];
		FAUSTFLOAT* input51_ptr = inputs[51];
		FAUSTFLOAT* input52_ptr = inputs[52];
		FAUSTFLOAT* input53_ptr = inputs[53];
		FAUSTFLOAT* input54_ptr = inputs[54];
		FAUSTFLOAT* input55_ptr = inputs[55];
		FAUSTFLOAT* input56_ptr = inputs[56];
		FAUSTFLOAT* input57_ptr = inputs[57];
		FAUSTFLOAT* input58_ptr = inputs[58];
		FAUSTFLOAT* input59_ptr = inputs[59];
		FAUSTFLOAT* input60_ptr = inputs[60];
		FAUSTFLOAT* input61_ptr = inputs[61];
		FAUSTFLOAT* input62_ptr = inputs[62];
		FAUSTFLOAT* input63_ptr = inputs[63];
		FAUSTFLOAT* input64_ptr = inputs[64];
		FAUSTFLOAT* input65_ptr = inputs[65];
		FAUSTFLOAT* input66_ptr = inputs[66];
		FAUSTFLOAT* input67_ptr = inputs[67];
		FAUSTFLOAT* input68_ptr = inputs[68];
		FAUSTFLOAT* input69_ptr = inputs[69];
		FAUSTFLOAT* input70_ptr = inputs[70];
		FAUSTFLOAT* input71_ptr = inputs[71];
		FAUSTFLOAT* input72_ptr = inputs[72];
		FAUSTFLOAT* input73_ptr = inputs[73];
		FAUSTFLOAT* input74_ptr = inputs[74];
		FAUSTFLOAT* input75_ptr = inputs[75];
		FAUSTFLOAT* input76_ptr = inputs[76];
		FAUSTFLOAT* input77_ptr = inputs[77];
		FAUSTFLOAT* input78_ptr = inputs[78];
		FAUSTFLOAT* input79_ptr = inputs[79];
		FAUSTFLOAT* input80_ptr = inputs[80];
		FAUSTFLOAT* input81_ptr = inputs[81];
		FAUSTFLOAT* input82_ptr = inputs[82];
		FAUSTFLOAT* input83_ptr = inputs[83];
		FAUSTFLOAT* input84_ptr = inputs[84];
		FAUSTFLOAT* input85_ptr = inputs[85];
		FAUSTFLOAT* input86_ptr = inputs[86];
		FAUSTFLOAT* input87_ptr = inputs[87];
		FAUSTFLOAT* input88_ptr = inputs[88];
		FAUSTFLOAT* input89_ptr = inputs[89];
		FAUSTFLOAT* input90_ptr = inputs[90];
		FAUSTFLOAT* input91_ptr = inputs[91];
		FAUSTFLOAT* input92_ptr = inputs[92];
		FAUSTFLOAT* input93_ptr = inputs[93];
		FAUSTFLOAT* input94_ptr = inputs[94];
		FAUSTFLOAT* input95_ptr = inputs[95];
		FAUSTFLOAT* input96_ptr = inputs[96];
		FAUSTFLOAT* input97_ptr = inputs[97];
		FAUSTFLOAT* input98_ptr = inputs[98];
		FAUSTFLOAT* input99_ptr = inputs[99];
		FAUSTFLOAT* input100_ptr = inputs[100];
		FAUSTFLOAT* input101_ptr = inputs[101];
		FAUSTFLOAT* input102_ptr = inputs[102];
		FAUSTFLOAT* input103_ptr = inputs[103];
		FAUSTFLOAT* input104_ptr = inputs[104];
		FAUSTFLOAT* input105_ptr = inputs[105];
		FAUSTFLOAT* input106_ptr = inputs[106];
		FAUSTFLOAT* input107_ptr = inputs[107];
		FAUSTFLOAT* input108_ptr = inputs[108];
		FAUSTFLOAT* input109_ptr = inputs[109];
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
		double fRec8_tmp[8];
		double* fRec8 = &fRec8_tmp[4];
		double fRec9_tmp[8];
		double* fRec9 = &fRec9_tmp[4];
		double fRec10_tmp[8];
		double* fRec10 = &fRec10_tmp[4];
		double fRec11_tmp[8];
		double* fRec11 = &fRec11_tmp[4];
		double fRec12_tmp[8];
		double* fRec12 = &fRec12_tmp[4];
		double fRec13_tmp[8];
		double* fRec13 = &fRec13_tmp[4];
		double fRec14_tmp[8];
		double* fRec14 = &fRec14_tmp[4];
		double fRec15_tmp[8];
		double* fRec15 = &fRec15_tmp[4];
		double fRec16_tmp[8];
		double* fRec16 = &fRec16_tmp[4];
		double fRec17_tmp[8];
		double* fRec17 = &fRec17_tmp[4];
		double fRec18_tmp[8];
		double* fRec18 = &fRec18_tmp[4];
		double fRec19_tmp[8];
		double* fRec19 = &fRec19_tmp[4];
		double fRec20_tmp[8];
		double* fRec20 = &fRec20_tmp[4];
		double fRec21_tmp[8];
		double* fRec21 = &fRec21_tmp[4];
		double fRec22_tmp[8];
		double* fRec22 = &fRec22_tmp[4];
		double fRec23_tmp[8];
		double* fRec23 = &fRec23_tmp[4];
		double fRec24_tmp[8];
		double* fRec24 = &fRec24_tmp[4];
		double fRec25_tmp[8];
		double* fRec25 = &fRec25_tmp[4];
		double fRec26_tmp[8];
		double* fRec26 = &fRec26_tmp[4];
		double fRec27_tmp[8];
		double* fRec27 = &fRec27_tmp[4];
		double fRec28_tmp[8];
		double* fRec28 = &fRec28_tmp[4];
		double fRec29_tmp[8];
		double* fRec29 = &fRec29_tmp[4];
		double fRec30_tmp[8];
		double* fRec30 = &fRec30_tmp[4];
		double fRec31_tmp[8];
		double* fRec31 = &fRec31_tmp[4];
		double fRec32_tmp[8];
		double* fRec32 = &fRec32_tmp[4];
		double fRec33_tmp[8];
		double* fRec33 = &fRec33_tmp[4];
		double fRec34_tmp[8];
		double* fRec34 = &fRec34_tmp[4];
		double fRec35_tmp[8];
		double* fRec35 = &fRec35_tmp[4];
		double fRec36_tmp[8];
		double* fRec36 = &fRec36_tmp[4];
		double fRec37_tmp[8];
		double* fRec37 = &fRec37_tmp[4];
		double fRec38_tmp[8];
		double* fRec38 = &fRec38_tmp[4];
		double fRec39_tmp[8];
		double* fRec39 = &fRec39_tmp[4];
		double fRec40_tmp[8];
		double* fRec40 = &fRec40_tmp[4];
		double fRec41_tmp[8];
		double* fRec41 = &fRec41_tmp[4];
		double fRec42_tmp[8];
		double* fRec42 = &fRec42_tmp[4];
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
			FAUSTFLOAT* input11 = &input11_ptr[vindex];
			FAUSTFLOAT* input12 = &input12_ptr[vindex];
			FAUSTFLOAT* input13 = &input13_ptr[vindex];
			FAUSTFLOAT* input14 = &input14_ptr[vindex];
			FAUSTFLOAT* input15 = &input15_ptr[vindex];
			FAUSTFLOAT* input16 = &input16_ptr[vindex];
			FAUSTFLOAT* input17 = &input17_ptr[vindex];
			FAUSTFLOAT* input18 = &input18_ptr[vindex];
			FAUSTFLOAT* input19 = &input19_ptr[vindex];
			FAUSTFLOAT* input20 = &input20_ptr[vindex];
			FAUSTFLOAT* input21 = &input21_ptr[vindex];
			FAUSTFLOAT* input22 = &input22_ptr[vindex];
			FAUSTFLOAT* input23 = &input23_ptr[vindex];
			FAUSTFLOAT* input24 = &input24_ptr[vindex];
			FAUSTFLOAT* input25 = &input25_ptr[vindex];
			FAUSTFLOAT* input26 = &input26_ptr[vindex];
			FAUSTFLOAT* input27 = &input27_ptr[vindex];
			FAUSTFLOAT* input28 = &input28_ptr[vindex];
			FAUSTFLOAT* input29 = &input29_ptr[vindex];
			FAUSTFLOAT* input30 = &input30_ptr[vindex];
			FAUSTFLOAT* input31 = &input31_ptr[vindex];
			FAUSTFLOAT* input32 = &input32_ptr[vindex];
			FAUSTFLOAT* input33 = &input33_ptr[vindex];
			FAUSTFLOAT* input34 = &input34_ptr[vindex];
			FAUSTFLOAT* input35 = &input35_ptr[vindex];
			FAUSTFLOAT* input36 = &input36_ptr[vindex];
			FAUSTFLOAT* input37 = &input37_ptr[vindex];
			FAUSTFLOAT* input38 = &input38_ptr[vindex];
			FAUSTFLOAT* input39 = &input39_ptr[vindex];
			FAUSTFLOAT* input40 = &input40_ptr[vindex];
			FAUSTFLOAT* input41 = &input41_ptr[vindex];
			FAUSTFLOAT* input42 = &input42_ptr[vindex];
			FAUSTFLOAT* input43 = &input43_ptr[vindex];
			FAUSTFLOAT* input44 = &input44_ptr[vindex];
			FAUSTFLOAT* input45 = &input45_ptr[vindex];
			FAUSTFLOAT* input46 = &input46_ptr[vindex];
			FAUSTFLOAT* input47 = &input47_ptr[vindex];
			FAUSTFLOAT* input48 = &input48_ptr[vindex];
			FAUSTFLOAT* input49 = &input49_ptr[vindex];
			FAUSTFLOAT* input50 = &input50_ptr[vindex];
			FAUSTFLOAT* input51 = &input51_ptr[vindex];
			FAUSTFLOAT* input52 = &input52_ptr[vindex];
			FAUSTFLOAT* input53 = &input53_ptr[vindex];
			FAUSTFLOAT* input54 = &input54_ptr[vindex];
			FAUSTFLOAT* input55 = &input55_ptr[vindex];
			FAUSTFLOAT* input56 = &input56_ptr[vindex];
			FAUSTFLOAT* input57 = &input57_ptr[vindex];
			FAUSTFLOAT* input58 = &input58_ptr[vindex];
			FAUSTFLOAT* input59 = &input59_ptr[vindex];
			FAUSTFLOAT* input60 = &input60_ptr[vindex];
			FAUSTFLOAT* input61 = &input61_ptr[vindex];
			FAUSTFLOAT* input62 = &input62_ptr[vindex];
			FAUSTFLOAT* input63 = &input63_ptr[vindex];
			FAUSTFLOAT* input64 = &input64_ptr[vindex];
			FAUSTFLOAT* input65 = &input65_ptr[vindex];
			FAUSTFLOAT* input66 = &input66_ptr[vindex];
			FAUSTFLOAT* input67 = &input67_ptr[vindex];
			FAUSTFLOAT* input68 = &input68_ptr[vindex];
			FAUSTFLOAT* input69 = &input69_ptr[vindex];
			FAUSTFLOAT* input70 = &input70_ptr[vindex];
			FAUSTFLOAT* input71 = &input71_ptr[vindex];
			FAUSTFLOAT* input72 = &input72_ptr[vindex];
			FAUSTFLOAT* input73 = &input73_ptr[vindex];
			FAUSTFLOAT* input74 = &input74_ptr[vindex];
			FAUSTFLOAT* input75 = &input75_ptr[vindex];
			FAUSTFLOAT* input76 = &input76_ptr[vindex];
			FAUSTFLOAT* input77 = &input77_ptr[vindex];
			FAUSTFLOAT* input78 = &input78_ptr[vindex];
			FAUSTFLOAT* input79 = &input79_ptr[vindex];
			FAUSTFLOAT* input80 = &input80_ptr[vindex];
			FAUSTFLOAT* input81 = &input81_ptr[vindex];
			FAUSTFLOAT* input82 = &input82_ptr[vindex];
			FAUSTFLOAT* input83 = &input83_ptr[vindex];
			FAUSTFLOAT* input84 = &input84_ptr[vindex];
			FAUSTFLOAT* input85 = &input85_ptr[vindex];
			FAUSTFLOAT* input86 = &input86_ptr[vindex];
			FAUSTFLOAT* input87 = &input87_ptr[vindex];
			FAUSTFLOAT* input88 = &input88_ptr[vindex];
			FAUSTFLOAT* input89 = &input89_ptr[vindex];
			FAUSTFLOAT* input90 = &input90_ptr[vindex];
			FAUSTFLOAT* input91 = &input91_ptr[vindex];
			FAUSTFLOAT* input92 = &input92_ptr[vindex];
			FAUSTFLOAT* input93 = &input93_ptr[vindex];
			FAUSTFLOAT* input94 = &input94_ptr[vindex];
			FAUSTFLOAT* input95 = &input95_ptr[vindex];
			FAUSTFLOAT* input96 = &input96_ptr[vindex];
			FAUSTFLOAT* input97 = &input97_ptr[vindex];
			FAUSTFLOAT* input98 = &input98_ptr[vindex];
			FAUSTFLOAT* input99 = &input99_ptr[vindex];
			FAUSTFLOAT* input100 = &input100_ptr[vindex];
			FAUSTFLOAT* input101 = &input101_ptr[vindex];
			FAUSTFLOAT* input102 = &input102_ptr[vindex];
			FAUSTFLOAT* input103 = &input103_ptr[vindex];
			FAUSTFLOAT* input104 = &input104_ptr[vindex];
			FAUSTFLOAT* input105 = &input105_ptr[vindex];
			FAUSTFLOAT* input106 = &input106_ptr[vindex];
			FAUSTFLOAT* input107 = &input107_ptr[vindex];
			FAUSTFLOAT* input108 = &input108_ptr[vindex];
			FAUSTFLOAT* input109 = &input109_ptr[vindex];
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
			int vsize = 4;
			/* Recursive loop 0 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				fRec0_tmp[j0] = fRec0_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec0[i] = 1.0499999999999998 * static_cast<double>(input0[i]) + 0.9 * fRec0[faust_wrap_sub(i, 1)];
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
				fRec1[i] = 1.0499999999999998 * static_cast<double>(input1[i]) + 0.9 * fRec1[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fRec1_perm[j3] = fRec1_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Recursive loop 2 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				fRec2_tmp[j4] = fRec2_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec2[i] = 1.0499999999999998 * static_cast<double>(input2[i]) + 0.9 * fRec2[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fRec2_perm[j5] = fRec2_tmp[faust_wrap_add(vsize, j5)];
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fRec0[i] * fRec1[i] * fRec2[i]);
			}
			/* Recursive loop 4 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec3_tmp[j6] = fRec3_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec3[i] = 1.0499999999999998 * static_cast<double>(input3[i]) + 0.9 * fRec3[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec3_perm[j7] = fRec3_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Recursive loop 5 */
			/* Pre code */
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fRec4_tmp[j8] = fRec4_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec4[i] = 1.0499999999999998 * static_cast<double>(input4[i]) + 0.9 * fRec4[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fRec4_perm[j9] = fRec4_tmp[faust_wrap_add(vsize, j9)];
			}
			/* Recursive loop 6 */
			/* Pre code */
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				fRec5_tmp[j10] = fRec5_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec5[i] = 1.0499999999999998 * static_cast<double>(input5[i]) + 0.9 * fRec5[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				fRec5_perm[j11] = fRec5_tmp[faust_wrap_add(vsize, j11)];
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fRec3[i] * fRec4[i] * fRec5[i]);
			}
			/* Recursive loop 8 */
			/* Pre code */
			for (int j12 = 0; j12 < 4; j12 = faust_wrap_add(j12, 1)) {
				fRec6_tmp[j12] = fRec6_perm[j12];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec6[i] = 1.0499999999999998 * static_cast<double>(input6[i]) + 0.9 * fRec6[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j13 = 0; j13 < 4; j13 = faust_wrap_add(j13, 1)) {
				fRec6_perm[j13] = fRec6_tmp[faust_wrap_add(vsize, j13)];
			}
			/* Recursive loop 9 */
			/* Pre code */
			for (int j14 = 0; j14 < 4; j14 = faust_wrap_add(j14, 1)) {
				fRec7_tmp[j14] = fRec7_perm[j14];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec7[i] = 1.0499999999999998 * static_cast<double>(input7[i]) + 0.9 * fRec7[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j15 = 0; j15 < 4; j15 = faust_wrap_add(j15, 1)) {
				fRec7_perm[j15] = fRec7_tmp[faust_wrap_add(vsize, j15)];
			}
			/* Recursive loop 10 */
			/* Pre code */
			for (int j16 = 0; j16 < 4; j16 = faust_wrap_add(j16, 1)) {
				fRec8_tmp[j16] = fRec8_perm[j16];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec8[i] = 1.0499999999999998 * static_cast<double>(input8[i]) + 0.9 * fRec8[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j17 = 0; j17 < 4; j17 = faust_wrap_add(j17, 1)) {
				fRec8_perm[j17] = fRec8_tmp[faust_wrap_add(vsize, j17)];
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output2[i] = static_cast<FAUSTFLOAT>(fRec6[i] * fRec7[i] * fRec8[i]);
			}
			/* Recursive loop 12 */
			/* Pre code */
			for (int j18 = 0; j18 < 4; j18 = faust_wrap_add(j18, 1)) {
				fRec9_tmp[j18] = fRec9_perm[j18];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec9[i] = 1.0499999999999998 * static_cast<double>(input9[i]) + 0.9 * fRec9[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j19 = 0; j19 < 4; j19 = faust_wrap_add(j19, 1)) {
				fRec9_perm[j19] = fRec9_tmp[faust_wrap_add(vsize, j19)];
			}
			/* Recursive loop 13 */
			/* Pre code */
			for (int j20 = 0; j20 < 4; j20 = faust_wrap_add(j20, 1)) {
				fRec10_tmp[j20] = fRec10_perm[j20];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec10[i] = 1.0499999999999998 * static_cast<double>(input10[i]) + 0.9 * fRec10[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j21 = 0; j21 < 4; j21 = faust_wrap_add(j21, 1)) {
				fRec10_perm[j21] = fRec10_tmp[faust_wrap_add(vsize, j21)];
			}
			/* Recursive loop 14 */
			/* Pre code */
			for (int j22 = 0; j22 < 4; j22 = faust_wrap_add(j22, 1)) {
				fRec11_tmp[j22] = fRec11_perm[j22];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec11[i] = 1.0499999999999998 * static_cast<double>(input11[i]) + 0.9 * fRec11[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j23 = 0; j23 < 4; j23 = faust_wrap_add(j23, 1)) {
				fRec11_perm[j23] = fRec11_tmp[faust_wrap_add(vsize, j23)];
			}
			/* Vectorizable loop 15 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output3[i] = static_cast<FAUSTFLOAT>(fRec9[i] * fRec10[i] + fRec11[i]);
			}
			/* Recursive loop 16 */
			/* Pre code */
			for (int j24 = 0; j24 < 4; j24 = faust_wrap_add(j24, 1)) {
				fRec12_tmp[j24] = fRec12_perm[j24];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec12[i] = 1.0499999999999998 * static_cast<double>(input12[i]) + 0.9 * fRec12[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j25 = 0; j25 < 4; j25 = faust_wrap_add(j25, 1)) {
				fRec12_perm[j25] = fRec12_tmp[faust_wrap_add(vsize, j25)];
			}
			/* Recursive loop 17 */
			/* Pre code */
			for (int j26 = 0; j26 < 4; j26 = faust_wrap_add(j26, 1)) {
				fRec13_tmp[j26] = fRec13_perm[j26];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec13[i] = 1.0499999999999998 * static_cast<double>(input13[i]) + 0.9 * fRec13[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j27 = 0; j27 < 4; j27 = faust_wrap_add(j27, 1)) {
				fRec13_perm[j27] = fRec13_tmp[faust_wrap_add(vsize, j27)];
			}
			/* Recursive loop 18 */
			/* Pre code */
			for (int j28 = 0; j28 < 4; j28 = faust_wrap_add(j28, 1)) {
				fRec14_tmp[j28] = fRec14_perm[j28];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec14[i] = 1.0499999999999998 * static_cast<double>(input14[i]) + 0.9 * fRec14[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j29 = 0; j29 < 4; j29 = faust_wrap_add(j29, 1)) {
				fRec14_perm[j29] = fRec14_tmp[faust_wrap_add(vsize, j29)];
			}
			/* Vectorizable loop 19 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output4[i] = static_cast<FAUSTFLOAT>(fRec12[i] * fRec13[i] + fRec14[i]);
			}
			/* Recursive loop 20 */
			/* Pre code */
			for (int j30 = 0; j30 < 4; j30 = faust_wrap_add(j30, 1)) {
				fRec15_tmp[j30] = fRec15_perm[j30];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec15[i] = 1.0499999999999998 * static_cast<double>(input15[i]) + 0.9 * fRec15[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j31 = 0; j31 < 4; j31 = faust_wrap_add(j31, 1)) {
				fRec15_perm[j31] = fRec15_tmp[faust_wrap_add(vsize, j31)];
			}
			/* Recursive loop 21 */
			/* Pre code */
			for (int j32 = 0; j32 < 4; j32 = faust_wrap_add(j32, 1)) {
				fRec16_tmp[j32] = fRec16_perm[j32];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec16[i] = 1.0499999999999998 * static_cast<double>(input16[i]) + 0.9 * fRec16[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j33 = 0; j33 < 4; j33 = faust_wrap_add(j33, 1)) {
				fRec16_perm[j33] = fRec16_tmp[faust_wrap_add(vsize, j33)];
			}
			/* Recursive loop 22 */
			/* Pre code */
			for (int j34 = 0; j34 < 4; j34 = faust_wrap_add(j34, 1)) {
				fRec17_tmp[j34] = fRec17_perm[j34];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec17[i] = 1.0499999999999998 * static_cast<double>(input17[i]) + 0.9 * fRec17[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j35 = 0; j35 < 4; j35 = faust_wrap_add(j35, 1)) {
				fRec17_perm[j35] = fRec17_tmp[faust_wrap_add(vsize, j35)];
			}
			/* Vectorizable loop 23 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output5[i] = static_cast<FAUSTFLOAT>(fRec15[i] * (fRec16[i] + fRec17[i]));
			}
			/* Recursive loop 24 */
			/* Pre code */
			for (int j36 = 0; j36 < 4; j36 = faust_wrap_add(j36, 1)) {
				fRec18_tmp[j36] = fRec18_perm[j36];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec18[i] = 0.09999999999999998 * static_cast<double>(faust_wrap_mul(static_cast<int>(3.5 * static_cast<double>(input18[i])), static_cast<int>(3.5 * static_cast<double>(input19[i]))) % (faust_wrap_add(static_cast<int>(static_cast<double>(input20[i])), 3))) + 0.9 * fRec18[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j37 = 0; j37 < 4; j37 = faust_wrap_add(j37, 1)) {
				fRec18_perm[j37] = fRec18_tmp[faust_wrap_add(vsize, j37)];
			}
			/* Vectorizable loop 25 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output6[i] = static_cast<FAUSTFLOAT>(fRec18[i]);
			}
			/* Recursive loop 26 */
			/* Pre code */
			for (int j38 = 0; j38 < 4; j38 = faust_wrap_add(j38, 1)) {
				fRec19_tmp[j38] = fRec19_perm[j38];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec19[i] = 0.09999999999999998 * static_cast<double>(faust_wrap_mul(static_cast<int>(3.5 * static_cast<double>(input21[i])), static_cast<int>(3.5 * static_cast<double>(input22[i]))) % (faust_wrap_add(static_cast<int>(static_cast<double>(input23[i])), 3))) + 0.9 * fRec19[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j39 = 0; j39 < 4; j39 = faust_wrap_add(j39, 1)) {
				fRec19_perm[j39] = fRec19_tmp[faust_wrap_add(vsize, j39)];
			}
			/* Vectorizable loop 27 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output7[i] = static_cast<FAUSTFLOAT>(fRec19[i]);
			}
			/* Recursive loop 28 */
			/* Pre code */
			for (int j40 = 0; j40 < 4; j40 = faust_wrap_add(j40, 1)) {
				fRec20_tmp[j40] = fRec20_perm[j40];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec20[i] = 0.09999999999999998 * static_cast<double>(faust_wrap_mul(static_cast<int>(3.5 * static_cast<double>(input24[i])), static_cast<int>(3.5 * static_cast<double>(input25[i])) % (faust_wrap_add(static_cast<int>(static_cast<double>(input26[i])), 3)))) + 0.9 * fRec20[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j41 = 0; j41 < 4; j41 = faust_wrap_add(j41, 1)) {
				fRec20_perm[j41] = fRec20_tmp[faust_wrap_add(vsize, j41)];
			}
			/* Vectorizable loop 29 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output8[i] = static_cast<FAUSTFLOAT>(fRec20[i]);
			}
			/* Recursive loop 30 */
			/* Pre code */
			for (int j42 = 0; j42 < 4; j42 = faust_wrap_add(j42, 1)) {
				fRec21_tmp[j42] = fRec21_perm[j42];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec21[i] = 0.09999999999999998 * static_cast<double>((static_cast<int>(3.5 * static_cast<double>(input27[i])) << static_cast<int>(3.5 * static_cast<double>(input28[i]))) >> (faust_wrap_add(static_cast<int>(static_cast<double>(input29[i])), 3))) + 0.9 * fRec21[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j43 = 0; j43 < 4; j43 = faust_wrap_add(j43, 1)) {
				fRec21_perm[j43] = fRec21_tmp[faust_wrap_add(vsize, j43)];
			}
			/* Vectorizable loop 31 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output9[i] = static_cast<FAUSTFLOAT>(fRec21[i]);
			}
			/* Recursive loop 32 */
			/* Pre code */
			for (int j44 = 0; j44 < 4; j44 = faust_wrap_add(j44, 1)) {
				fRec22_tmp[j44] = fRec22_perm[j44];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec22[i] = 0.09999999999999998 * static_cast<double>((static_cast<int>(3.5 * static_cast<double>(input30[i])) << static_cast<int>(3.5 * static_cast<double>(input31[i]))) >> (faust_wrap_add(static_cast<int>(static_cast<double>(input32[i])), 3))) + 0.9 * fRec22[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j45 = 0; j45 < 4; j45 = faust_wrap_add(j45, 1)) {
				fRec22_perm[j45] = fRec22_tmp[faust_wrap_add(vsize, j45)];
			}
			/* Vectorizable loop 33 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output10[i] = static_cast<FAUSTFLOAT>(fRec22[i]);
			}
			/* Recursive loop 34 */
			/* Pre code */
			for (int j46 = 0; j46 < 4; j46 = faust_wrap_add(j46, 1)) {
				fRec23_tmp[j46] = fRec23_perm[j46];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec23[i] = 0.09999999999999998 * static_cast<double>(static_cast<int>(3.5 * static_cast<double>(input33[i])) << (static_cast<int>(3.5 * static_cast<double>(input34[i])) >> (faust_wrap_add(static_cast<int>(static_cast<double>(input35[i])), 3)))) + 0.9 * fRec23[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j47 = 0; j47 < 4; j47 = faust_wrap_add(j47, 1)) {
				fRec23_perm[j47] = fRec23_tmp[faust_wrap_add(vsize, j47)];
			}
			/* Vectorizable loop 35 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output11[i] = static_cast<FAUSTFLOAT>(fRec23[i]);
			}
			/* Recursive loop 36 */
			/* Pre code */
			for (int j48 = 0; j48 < 4; j48 = faust_wrap_add(j48, 1)) {
				fRec24_tmp[j48] = fRec24_perm[j48];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec24[i] = 0.09999999999999998 * static_cast<double>((static_cast<int>(3.5 * static_cast<double>(input36[i])) << static_cast<int>(3.5 * static_cast<double>(input37[i]))) <= (faust_wrap_add(static_cast<int>(static_cast<double>(input38[i])), 3))) + 0.9 * fRec24[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j49 = 0; j49 < 4; j49 = faust_wrap_add(j49, 1)) {
				fRec24_perm[j49] = fRec24_tmp[faust_wrap_add(vsize, j49)];
			}
			/* Vectorizable loop 37 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output12[i] = static_cast<FAUSTFLOAT>(fRec24[i]);
			}
			/* Recursive loop 38 */
			/* Pre code */
			for (int j50 = 0; j50 < 4; j50 = faust_wrap_add(j50, 1)) {
				fRec25_tmp[j50] = fRec25_perm[j50];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec25[i] = 0.09999999999999998 * static_cast<double>((static_cast<int>(3.5 * static_cast<double>(input39[i])) << static_cast<int>(3.5 * static_cast<double>(input40[i]))) <= (faust_wrap_add(static_cast<int>(static_cast<double>(input41[i])), 3))) + 0.9 * fRec25[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j51 = 0; j51 < 4; j51 = faust_wrap_add(j51, 1)) {
				fRec25_perm[j51] = fRec25_tmp[faust_wrap_add(vsize, j51)];
			}
			/* Vectorizable loop 39 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output13[i] = static_cast<FAUSTFLOAT>(fRec25[i]);
			}
			/* Recursive loop 40 */
			/* Pre code */
			for (int j52 = 0; j52 < 4; j52 = faust_wrap_add(j52, 1)) {
				fRec26_tmp[j52] = fRec26_perm[j52];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec26[i] = 0.09999999999999998 * static_cast<double>(static_cast<int>(3.5 * static_cast<double>(input42[i])) << (static_cast<int>(3.5 * static_cast<double>(input43[i])) <= (faust_wrap_add(static_cast<int>(static_cast<double>(input44[i])), 3)))) + 0.9 * fRec26[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j53 = 0; j53 < 4; j53 = faust_wrap_add(j53, 1)) {
				fRec26_perm[j53] = fRec26_tmp[faust_wrap_add(vsize, j53)];
			}
			/* Vectorizable loop 41 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output14[i] = static_cast<FAUSTFLOAT>(fRec26[i]);
			}
			/* Recursive loop 42 */
			/* Pre code */
			for (int j54 = 0; j54 < 4; j54 = faust_wrap_add(j54, 1)) {
				fRec27_tmp[j54] = fRec27_perm[j54];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec27[i] = 0.09999999999999998 * static_cast<double>((static_cast<int>(3.5 * static_cast<double>(input45[i])) < static_cast<int>(3.5 * static_cast<double>(input46[i]))) <= (faust_wrap_add(static_cast<int>(static_cast<double>(input47[i])), 3))) + 0.9 * fRec27[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j55 = 0; j55 < 4; j55 = faust_wrap_add(j55, 1)) {
				fRec27_perm[j55] = fRec27_tmp[faust_wrap_add(vsize, j55)];
			}
			/* Vectorizable loop 43 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output15[i] = static_cast<FAUSTFLOAT>(fRec27[i]);
			}
			/* Recursive loop 44 */
			/* Pre code */
			for (int j56 = 0; j56 < 4; j56 = faust_wrap_add(j56, 1)) {
				fRec28_tmp[j56] = fRec28_perm[j56];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec28[i] = 0.09999999999999998 * static_cast<double>((static_cast<int>(3.5 * static_cast<double>(input48[i])) < static_cast<int>(3.5 * static_cast<double>(input49[i]))) <= (faust_wrap_add(static_cast<int>(static_cast<double>(input50[i])), 3))) + 0.9 * fRec28[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j57 = 0; j57 < 4; j57 = faust_wrap_add(j57, 1)) {
				fRec28_perm[j57] = fRec28_tmp[faust_wrap_add(vsize, j57)];
			}
			/* Vectorizable loop 45 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output16[i] = static_cast<FAUSTFLOAT>(fRec28[i]);
			}
			/* Recursive loop 46 */
			/* Pre code */
			for (int j58 = 0; j58 < 4; j58 = faust_wrap_add(j58, 1)) {
				fRec29_tmp[j58] = fRec29_perm[j58];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec29[i] = 0.09999999999999998 * static_cast<double>(static_cast<int>(3.5 * static_cast<double>(input51[i])) < (static_cast<int>(3.5 * static_cast<double>(input52[i])) <= (faust_wrap_add(static_cast<int>(static_cast<double>(input53[i])), 3)))) + 0.9 * fRec29[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j59 = 0; j59 < 4; j59 = faust_wrap_add(j59, 1)) {
				fRec29_perm[j59] = fRec29_tmp[faust_wrap_add(vsize, j59)];
			}
			/* Vectorizable loop 47 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output17[i] = static_cast<FAUSTFLOAT>(fRec29[i]);
			}
			/* Recursive loop 48 */
			/* Pre code */
			for (int j60 = 0; j60 < 4; j60 = faust_wrap_add(j60, 1)) {
				fRec30_tmp[j60] = fRec30_perm[j60];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec30[i] = 0.09999999999999998 * static_cast<double>((static_cast<int>(3.5 * static_cast<double>(input54[i])) == static_cast<int>(3.5 * static_cast<double>(input55[i]))) != (faust_wrap_add(static_cast<int>(static_cast<double>(input56[i])), 3))) + 0.9 * fRec30[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j61 = 0; j61 < 4; j61 = faust_wrap_add(j61, 1)) {
				fRec30_perm[j61] = fRec30_tmp[faust_wrap_add(vsize, j61)];
			}
			/* Vectorizable loop 49 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output18[i] = static_cast<FAUSTFLOAT>(fRec30[i]);
			}
			/* Recursive loop 50 */
			/* Pre code */
			for (int j62 = 0; j62 < 4; j62 = faust_wrap_add(j62, 1)) {
				fRec31_tmp[j62] = fRec31_perm[j62];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec31[i] = 0.09999999999999998 * static_cast<double>((static_cast<int>(3.5 * static_cast<double>(input57[i])) == static_cast<int>(3.5 * static_cast<double>(input58[i]))) != (faust_wrap_add(static_cast<int>(static_cast<double>(input59[i])), 3))) + 0.9 * fRec31[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j63 = 0; j63 < 4; j63 = faust_wrap_add(j63, 1)) {
				fRec31_perm[j63] = fRec31_tmp[faust_wrap_add(vsize, j63)];
			}
			/* Vectorizable loop 51 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output19[i] = static_cast<FAUSTFLOAT>(fRec31[i]);
			}
			/* Recursive loop 52 */
			/* Pre code */
			for (int j64 = 0; j64 < 4; j64 = faust_wrap_add(j64, 1)) {
				fRec32_tmp[j64] = fRec32_perm[j64];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec32[i] = 0.09999999999999998 * static_cast<double>(static_cast<int>(3.5 * static_cast<double>(input60[i])) == (static_cast<int>(3.5 * static_cast<double>(input61[i])) != (faust_wrap_add(static_cast<int>(static_cast<double>(input62[i])), 3)))) + 0.9 * fRec32[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j65 = 0; j65 < 4; j65 = faust_wrap_add(j65, 1)) {
				fRec32_perm[j65] = fRec32_tmp[faust_wrap_add(vsize, j65)];
			}
			/* Vectorizable loop 53 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output20[i] = static_cast<FAUSTFLOAT>(fRec32[i]);
			}
			/* Recursive loop 54 */
			/* Pre code */
			for (int j66 = 0; j66 < 4; j66 = faust_wrap_add(j66, 1)) {
				fRec33_tmp[j66] = fRec33_perm[j66];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec33[i] = 0.09999999999999998 * static_cast<double>((static_cast<int>(3.5 * static_cast<double>(input63[i])) & static_cast<int>(3.5 * static_cast<double>(input64[i]))) | (faust_wrap_add(static_cast<int>(static_cast<double>(input65[i])), 3))) + 0.9 * fRec33[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j67 = 0; j67 < 4; j67 = faust_wrap_add(j67, 1)) {
				fRec33_perm[j67] = fRec33_tmp[faust_wrap_add(vsize, j67)];
			}
			/* Vectorizable loop 55 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output21[i] = static_cast<FAUSTFLOAT>(fRec33[i]);
			}
			/* Recursive loop 56 */
			/* Pre code */
			for (int j68 = 0; j68 < 4; j68 = faust_wrap_add(j68, 1)) {
				fRec34_tmp[j68] = fRec34_perm[j68];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec34[i] = 0.09999999999999998 * static_cast<double>((static_cast<int>(3.5 * static_cast<double>(input66[i])) & static_cast<int>(3.5 * static_cast<double>(input67[i]))) ^ faust_wrap_add(static_cast<int>(static_cast<double>(input68[i])), 3)) + 0.9 * fRec34[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j69 = 0; j69 < 4; j69 = faust_wrap_add(j69, 1)) {
				fRec34_perm[j69] = fRec34_tmp[faust_wrap_add(vsize, j69)];
			}
			/* Vectorizable loop 57 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output22[i] = static_cast<FAUSTFLOAT>(fRec34[i]);
			}
			/* Recursive loop 58 */
			/* Pre code */
			for (int j70 = 0; j70 < 4; j70 = faust_wrap_add(j70, 1)) {
				fRec35_tmp[j70] = fRec35_perm[j70];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec35[i] = 0.09999999999999998 * static_cast<double>((static_cast<int>(3.5 * static_cast<double>(input69[i])) & static_cast<int>(3.5 * static_cast<double>(input70[i]))) | (faust_wrap_add(static_cast<int>(static_cast<double>(input71[i])), 3))) + 0.9 * fRec35[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j71 = 0; j71 < 4; j71 = faust_wrap_add(j71, 1)) {
				fRec35_perm[j71] = fRec35_tmp[faust_wrap_add(vsize, j71)];
			}
			/* Vectorizable loop 59 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output23[i] = static_cast<FAUSTFLOAT>(fRec35[i]);
			}
			/* Recursive loop 60 */
			/* Pre code */
			for (int j72 = 0; j72 < 4; j72 = faust_wrap_add(j72, 1)) {
				fRec36_tmp[j72] = fRec36_perm[j72];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec36[i] = 0.09999999999999998 * static_cast<double>((static_cast<int>(3.5 * static_cast<double>(input72[i])) & static_cast<int>(3.5 * static_cast<double>(input73[i]))) ^ faust_wrap_add(static_cast<int>(static_cast<double>(input74[i])), 3)) + 0.9 * fRec36[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j73 = 0; j73 < 4; j73 = faust_wrap_add(j73, 1)) {
				fRec36_perm[j73] = fRec36_tmp[faust_wrap_add(vsize, j73)];
			}
			/* Vectorizable loop 61 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output24[i] = static_cast<FAUSTFLOAT>(fRec36[i]);
			}
			/* Recursive loop 62 */
			/* Pre code */
			for (int j74 = 0; j74 < 4; j74 = faust_wrap_add(j74, 1)) {
				fRec37_tmp[j74] = fRec37_perm[j74];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec37[i] = 0.09999999999999998 * static_cast<double>(static_cast<int>(3.5 * static_cast<double>(input75[i])) & (static_cast<int>(3.5 * static_cast<double>(input76[i])) | (faust_wrap_add(static_cast<int>(static_cast<double>(input77[i])), 3)))) + 0.9 * fRec37[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j75 = 0; j75 < 4; j75 = faust_wrap_add(j75, 1)) {
				fRec37_perm[j75] = fRec37_tmp[faust_wrap_add(vsize, j75)];
			}
			/* Vectorizable loop 63 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output25[i] = static_cast<FAUSTFLOAT>(fRec37[i]);
			}
			/* Recursive loop 64 */
			/* Pre code */
			for (int j76 = 0; j76 < 4; j76 = faust_wrap_add(j76, 1)) {
				fRec38_tmp[j76] = fRec38_perm[j76];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec38[i] = 0.09999999999999998 * static_cast<double>(static_cast<int>(3.5 * static_cast<double>(input78[i])) & (static_cast<int>(3.5 * static_cast<double>(input79[i])) ^ faust_wrap_add(static_cast<int>(static_cast<double>(input80[i])), 3))) + 0.9 * fRec38[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j77 = 0; j77 < 4; j77 = faust_wrap_add(j77, 1)) {
				fRec38_perm[j77] = fRec38_tmp[faust_wrap_add(vsize, j77)];
			}
			/* Vectorizable loop 65 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output26[i] = static_cast<FAUSTFLOAT>(fRec38[i]);
			}
			/* Recursive loop 66 */
			/* Pre code */
			for (int j78 = 0; j78 < 4; j78 = faust_wrap_add(j78, 1)) {
				fRec39_tmp[j78] = fRec39_perm[j78];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec39[i] = 0.09999999999999998 * static_cast<double>((faust_wrap_add(faust_wrap_add(static_cast<int>(static_cast<double>(input82[i])), static_cast<int>(3.5 * static_cast<double>(input81[i]))), faust_wrap_sub(3, static_cast<int>(3.5 * static_cast<double>(input83[i]))))) | (faust_wrap_add(static_cast<int>(static_cast<double>(input84[i])), 3))) + 0.9 * fRec39[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j79 = 0; j79 < 4; j79 = faust_wrap_add(j79, 1)) {
				fRec39_perm[j79] = fRec39_tmp[faust_wrap_add(vsize, j79)];
			}
			/* Vectorizable loop 67 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output27[i] = static_cast<FAUSTFLOAT>(fRec39[i]);
			}
			/* Recursive loop 68 */
			/* Pre code */
			for (int j80 = 0; j80 < 4; j80 = faust_wrap_add(j80, 1)) {
				fRec40_tmp[j80] = fRec40_perm[j80];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec40[i] = 0.09999999999999998 * static_cast<double>((((static_cast<int>(std::fmod(static_cast<double>(faust_wrap_mul(faust_wrap_add(static_cast<int>(static_cast<double>(input86[i])), 3), static_cast<int>(3.5 * static_cast<double>(input85[i])))) / static_cast<double>(faust_wrap_add(static_cast<int>(3.5 * static_cast<double>(input87[i])), 1)), static_cast<double>(faust_wrap_add(static_cast<int>(static_cast<double>(input88[i])), 3)))) & static_cast<int>(3.5 * static_cast<double>(input89[i]))) ^ faust_wrap_add(static_cast<int>(static_cast<double>(input90[i])), 3)) << static_cast<int>(3.5 * static_cast<double>(input91[i]))) >> (faust_wrap_add(static_cast<int>(static_cast<double>(input92[i])), 3))) + 0.9 * fRec40[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j81 = 0; j81 < 4; j81 = faust_wrap_add(j81, 1)) {
				fRec40_perm[j81] = fRec40_tmp[faust_wrap_add(vsize, j81)];
			}
			/* Vectorizable loop 69 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output28[i] = static_cast<FAUSTFLOAT>(fRec40[i]);
			}
			/* Recursive loop 70 */
			/* Pre code */
			for (int j82 = 0; j82 < 4; j82 = faust_wrap_add(j82, 1)) {
				fRec41_tmp[j82] = fRec41_perm[j82];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec41[i] = 0.09999999999999998 * static_cast<double>((static_cast<int>(3.5 * static_cast<double>(input93[i])) <= (faust_wrap_add(static_cast<int>(static_cast<double>(input94[i])), 3))) >= ((faust_wrap_add(faust_wrap_add(static_cast<int>(static_cast<double>(input96[i])), static_cast<int>(3.5 * static_cast<double>(input95[i]))), faust_wrap_sub(3, static_cast<int>(3.5 * static_cast<double>(input97[i]))))) | (faust_wrap_add(static_cast<int>(static_cast<double>(input98[i])), 3)))) + 0.9 * fRec41[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j83 = 0; j83 < 4; j83 = faust_wrap_add(j83, 1)) {
				fRec41_perm[j83] = fRec41_tmp[faust_wrap_add(vsize, j83)];
			}
			/* Vectorizable loop 71 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output29[i] = static_cast<FAUSTFLOAT>(fRec41[i]);
			}
			/* Recursive loop 72 */
			/* Pre code */
			for (int j84 = 0; j84 < 4; j84 = faust_wrap_add(j84, 1)) {
				fRec42_tmp[j84] = fRec42_perm[j84];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec42[i] = 0.09999999999999998 * static_cast<double>((faust_wrap_sub(faust_wrap_add(static_cast<int>(static_cast<double>(input99[i])), static_cast<int>(3.5 * static_cast<double>(input100[i]))), static_cast<int>(static_cast<double>(input101[i])))) | ((((static_cast<int>(std::fmod(static_cast<double>(faust_wrap_mul(faust_wrap_add(static_cast<int>(static_cast<double>(input103[i])), 3), static_cast<int>(3.5 * static_cast<double>(input102[i])))) / static_cast<double>(faust_wrap_add(static_cast<int>(3.5 * static_cast<double>(input104[i])), 1)), static_cast<double>(faust_wrap_add(static_cast<int>(static_cast<double>(input105[i])), 3)))) & static_cast<int>(3.5 * static_cast<double>(input106[i]))) ^ faust_wrap_add(static_cast<int>(static_cast<double>(input107[i])), 3)) << static_cast<int>(3.5 * static_cast<double>(input108[i]))) >> (faust_wrap_add(static_cast<int>(static_cast<double>(input109[i])), 3)))) + 0.9 * fRec42[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j85 = 0; j85 < 4; j85 = faust_wrap_add(j85, 1)) {
				fRec42_perm[j85] = fRec42_tmp[faust_wrap_add(vsize, j85)];
			}
			/* Vectorizable loop 73 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output30[i] = static_cast<FAUSTFLOAT>(fRec42[i]);
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
			FAUSTFLOAT* input11 = &input11_ptr[vindex];
			FAUSTFLOAT* input12 = &input12_ptr[vindex];
			FAUSTFLOAT* input13 = &input13_ptr[vindex];
			FAUSTFLOAT* input14 = &input14_ptr[vindex];
			FAUSTFLOAT* input15 = &input15_ptr[vindex];
			FAUSTFLOAT* input16 = &input16_ptr[vindex];
			FAUSTFLOAT* input17 = &input17_ptr[vindex];
			FAUSTFLOAT* input18 = &input18_ptr[vindex];
			FAUSTFLOAT* input19 = &input19_ptr[vindex];
			FAUSTFLOAT* input20 = &input20_ptr[vindex];
			FAUSTFLOAT* input21 = &input21_ptr[vindex];
			FAUSTFLOAT* input22 = &input22_ptr[vindex];
			FAUSTFLOAT* input23 = &input23_ptr[vindex];
			FAUSTFLOAT* input24 = &input24_ptr[vindex];
			FAUSTFLOAT* input25 = &input25_ptr[vindex];
			FAUSTFLOAT* input26 = &input26_ptr[vindex];
			FAUSTFLOAT* input27 = &input27_ptr[vindex];
			FAUSTFLOAT* input28 = &input28_ptr[vindex];
			FAUSTFLOAT* input29 = &input29_ptr[vindex];
			FAUSTFLOAT* input30 = &input30_ptr[vindex];
			FAUSTFLOAT* input31 = &input31_ptr[vindex];
			FAUSTFLOAT* input32 = &input32_ptr[vindex];
			FAUSTFLOAT* input33 = &input33_ptr[vindex];
			FAUSTFLOAT* input34 = &input34_ptr[vindex];
			FAUSTFLOAT* input35 = &input35_ptr[vindex];
			FAUSTFLOAT* input36 = &input36_ptr[vindex];
			FAUSTFLOAT* input37 = &input37_ptr[vindex];
			FAUSTFLOAT* input38 = &input38_ptr[vindex];
			FAUSTFLOAT* input39 = &input39_ptr[vindex];
			FAUSTFLOAT* input40 = &input40_ptr[vindex];
			FAUSTFLOAT* input41 = &input41_ptr[vindex];
			FAUSTFLOAT* input42 = &input42_ptr[vindex];
			FAUSTFLOAT* input43 = &input43_ptr[vindex];
			FAUSTFLOAT* input44 = &input44_ptr[vindex];
			FAUSTFLOAT* input45 = &input45_ptr[vindex];
			FAUSTFLOAT* input46 = &input46_ptr[vindex];
			FAUSTFLOAT* input47 = &input47_ptr[vindex];
			FAUSTFLOAT* input48 = &input48_ptr[vindex];
			FAUSTFLOAT* input49 = &input49_ptr[vindex];
			FAUSTFLOAT* input50 = &input50_ptr[vindex];
			FAUSTFLOAT* input51 = &input51_ptr[vindex];
			FAUSTFLOAT* input52 = &input52_ptr[vindex];
			FAUSTFLOAT* input53 = &input53_ptr[vindex];
			FAUSTFLOAT* input54 = &input54_ptr[vindex];
			FAUSTFLOAT* input55 = &input55_ptr[vindex];
			FAUSTFLOAT* input56 = &input56_ptr[vindex];
			FAUSTFLOAT* input57 = &input57_ptr[vindex];
			FAUSTFLOAT* input58 = &input58_ptr[vindex];
			FAUSTFLOAT* input59 = &input59_ptr[vindex];
			FAUSTFLOAT* input60 = &input60_ptr[vindex];
			FAUSTFLOAT* input61 = &input61_ptr[vindex];
			FAUSTFLOAT* input62 = &input62_ptr[vindex];
			FAUSTFLOAT* input63 = &input63_ptr[vindex];
			FAUSTFLOAT* input64 = &input64_ptr[vindex];
			FAUSTFLOAT* input65 = &input65_ptr[vindex];
			FAUSTFLOAT* input66 = &input66_ptr[vindex];
			FAUSTFLOAT* input67 = &input67_ptr[vindex];
			FAUSTFLOAT* input68 = &input68_ptr[vindex];
			FAUSTFLOAT* input69 = &input69_ptr[vindex];
			FAUSTFLOAT* input70 = &input70_ptr[vindex];
			FAUSTFLOAT* input71 = &input71_ptr[vindex];
			FAUSTFLOAT* input72 = &input72_ptr[vindex];
			FAUSTFLOAT* input73 = &input73_ptr[vindex];
			FAUSTFLOAT* input74 = &input74_ptr[vindex];
			FAUSTFLOAT* input75 = &input75_ptr[vindex];
			FAUSTFLOAT* input76 = &input76_ptr[vindex];
			FAUSTFLOAT* input77 = &input77_ptr[vindex];
			FAUSTFLOAT* input78 = &input78_ptr[vindex];
			FAUSTFLOAT* input79 = &input79_ptr[vindex];
			FAUSTFLOAT* input80 = &input80_ptr[vindex];
			FAUSTFLOAT* input81 = &input81_ptr[vindex];
			FAUSTFLOAT* input82 = &input82_ptr[vindex];
			FAUSTFLOAT* input83 = &input83_ptr[vindex];
			FAUSTFLOAT* input84 = &input84_ptr[vindex];
			FAUSTFLOAT* input85 = &input85_ptr[vindex];
			FAUSTFLOAT* input86 = &input86_ptr[vindex];
			FAUSTFLOAT* input87 = &input87_ptr[vindex];
			FAUSTFLOAT* input88 = &input88_ptr[vindex];
			FAUSTFLOAT* input89 = &input89_ptr[vindex];
			FAUSTFLOAT* input90 = &input90_ptr[vindex];
			FAUSTFLOAT* input91 = &input91_ptr[vindex];
			FAUSTFLOAT* input92 = &input92_ptr[vindex];
			FAUSTFLOAT* input93 = &input93_ptr[vindex];
			FAUSTFLOAT* input94 = &input94_ptr[vindex];
			FAUSTFLOAT* input95 = &input95_ptr[vindex];
			FAUSTFLOAT* input96 = &input96_ptr[vindex];
			FAUSTFLOAT* input97 = &input97_ptr[vindex];
			FAUSTFLOAT* input98 = &input98_ptr[vindex];
			FAUSTFLOAT* input99 = &input99_ptr[vindex];
			FAUSTFLOAT* input100 = &input100_ptr[vindex];
			FAUSTFLOAT* input101 = &input101_ptr[vindex];
			FAUSTFLOAT* input102 = &input102_ptr[vindex];
			FAUSTFLOAT* input103 = &input103_ptr[vindex];
			FAUSTFLOAT* input104 = &input104_ptr[vindex];
			FAUSTFLOAT* input105 = &input105_ptr[vindex];
			FAUSTFLOAT* input106 = &input106_ptr[vindex];
			FAUSTFLOAT* input107 = &input107_ptr[vindex];
			FAUSTFLOAT* input108 = &input108_ptr[vindex];
			FAUSTFLOAT* input109 = &input109_ptr[vindex];
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
			int vsize = faust_wrap_sub(count, vindex);
			/* Recursive loop 0 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				fRec0_tmp[j0] = fRec0_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec0[i] = 1.0499999999999998 * static_cast<double>(input0[i]) + 0.9 * fRec0[faust_wrap_sub(i, 1)];
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
				fRec1[i] = 1.0499999999999998 * static_cast<double>(input1[i]) + 0.9 * fRec1[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fRec1_perm[j3] = fRec1_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Recursive loop 2 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				fRec2_tmp[j4] = fRec2_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec2[i] = 1.0499999999999998 * static_cast<double>(input2[i]) + 0.9 * fRec2[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fRec2_perm[j5] = fRec2_tmp[faust_wrap_add(vsize, j5)];
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fRec0[i] * fRec1[i] * fRec2[i]);
			}
			/* Recursive loop 4 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec3_tmp[j6] = fRec3_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec3[i] = 1.0499999999999998 * static_cast<double>(input3[i]) + 0.9 * fRec3[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec3_perm[j7] = fRec3_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Recursive loop 5 */
			/* Pre code */
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fRec4_tmp[j8] = fRec4_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec4[i] = 1.0499999999999998 * static_cast<double>(input4[i]) + 0.9 * fRec4[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fRec4_perm[j9] = fRec4_tmp[faust_wrap_add(vsize, j9)];
			}
			/* Recursive loop 6 */
			/* Pre code */
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				fRec5_tmp[j10] = fRec5_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec5[i] = 1.0499999999999998 * static_cast<double>(input5[i]) + 0.9 * fRec5[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				fRec5_perm[j11] = fRec5_tmp[faust_wrap_add(vsize, j11)];
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fRec3[i] * fRec4[i] * fRec5[i]);
			}
			/* Recursive loop 8 */
			/* Pre code */
			for (int j12 = 0; j12 < 4; j12 = faust_wrap_add(j12, 1)) {
				fRec6_tmp[j12] = fRec6_perm[j12];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec6[i] = 1.0499999999999998 * static_cast<double>(input6[i]) + 0.9 * fRec6[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j13 = 0; j13 < 4; j13 = faust_wrap_add(j13, 1)) {
				fRec6_perm[j13] = fRec6_tmp[faust_wrap_add(vsize, j13)];
			}
			/* Recursive loop 9 */
			/* Pre code */
			for (int j14 = 0; j14 < 4; j14 = faust_wrap_add(j14, 1)) {
				fRec7_tmp[j14] = fRec7_perm[j14];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec7[i] = 1.0499999999999998 * static_cast<double>(input7[i]) + 0.9 * fRec7[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j15 = 0; j15 < 4; j15 = faust_wrap_add(j15, 1)) {
				fRec7_perm[j15] = fRec7_tmp[faust_wrap_add(vsize, j15)];
			}
			/* Recursive loop 10 */
			/* Pre code */
			for (int j16 = 0; j16 < 4; j16 = faust_wrap_add(j16, 1)) {
				fRec8_tmp[j16] = fRec8_perm[j16];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec8[i] = 1.0499999999999998 * static_cast<double>(input8[i]) + 0.9 * fRec8[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j17 = 0; j17 < 4; j17 = faust_wrap_add(j17, 1)) {
				fRec8_perm[j17] = fRec8_tmp[faust_wrap_add(vsize, j17)];
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output2[i] = static_cast<FAUSTFLOAT>(fRec6[i] * fRec7[i] * fRec8[i]);
			}
			/* Recursive loop 12 */
			/* Pre code */
			for (int j18 = 0; j18 < 4; j18 = faust_wrap_add(j18, 1)) {
				fRec9_tmp[j18] = fRec9_perm[j18];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec9[i] = 1.0499999999999998 * static_cast<double>(input9[i]) + 0.9 * fRec9[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j19 = 0; j19 < 4; j19 = faust_wrap_add(j19, 1)) {
				fRec9_perm[j19] = fRec9_tmp[faust_wrap_add(vsize, j19)];
			}
			/* Recursive loop 13 */
			/* Pre code */
			for (int j20 = 0; j20 < 4; j20 = faust_wrap_add(j20, 1)) {
				fRec10_tmp[j20] = fRec10_perm[j20];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec10[i] = 1.0499999999999998 * static_cast<double>(input10[i]) + 0.9 * fRec10[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j21 = 0; j21 < 4; j21 = faust_wrap_add(j21, 1)) {
				fRec10_perm[j21] = fRec10_tmp[faust_wrap_add(vsize, j21)];
			}
			/* Recursive loop 14 */
			/* Pre code */
			for (int j22 = 0; j22 < 4; j22 = faust_wrap_add(j22, 1)) {
				fRec11_tmp[j22] = fRec11_perm[j22];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec11[i] = 1.0499999999999998 * static_cast<double>(input11[i]) + 0.9 * fRec11[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j23 = 0; j23 < 4; j23 = faust_wrap_add(j23, 1)) {
				fRec11_perm[j23] = fRec11_tmp[faust_wrap_add(vsize, j23)];
			}
			/* Vectorizable loop 15 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output3[i] = static_cast<FAUSTFLOAT>(fRec9[i] * fRec10[i] + fRec11[i]);
			}
			/* Recursive loop 16 */
			/* Pre code */
			for (int j24 = 0; j24 < 4; j24 = faust_wrap_add(j24, 1)) {
				fRec12_tmp[j24] = fRec12_perm[j24];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec12[i] = 1.0499999999999998 * static_cast<double>(input12[i]) + 0.9 * fRec12[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j25 = 0; j25 < 4; j25 = faust_wrap_add(j25, 1)) {
				fRec12_perm[j25] = fRec12_tmp[faust_wrap_add(vsize, j25)];
			}
			/* Recursive loop 17 */
			/* Pre code */
			for (int j26 = 0; j26 < 4; j26 = faust_wrap_add(j26, 1)) {
				fRec13_tmp[j26] = fRec13_perm[j26];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec13[i] = 1.0499999999999998 * static_cast<double>(input13[i]) + 0.9 * fRec13[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j27 = 0; j27 < 4; j27 = faust_wrap_add(j27, 1)) {
				fRec13_perm[j27] = fRec13_tmp[faust_wrap_add(vsize, j27)];
			}
			/* Recursive loop 18 */
			/* Pre code */
			for (int j28 = 0; j28 < 4; j28 = faust_wrap_add(j28, 1)) {
				fRec14_tmp[j28] = fRec14_perm[j28];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec14[i] = 1.0499999999999998 * static_cast<double>(input14[i]) + 0.9 * fRec14[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j29 = 0; j29 < 4; j29 = faust_wrap_add(j29, 1)) {
				fRec14_perm[j29] = fRec14_tmp[faust_wrap_add(vsize, j29)];
			}
			/* Vectorizable loop 19 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output4[i] = static_cast<FAUSTFLOAT>(fRec12[i] * fRec13[i] + fRec14[i]);
			}
			/* Recursive loop 20 */
			/* Pre code */
			for (int j30 = 0; j30 < 4; j30 = faust_wrap_add(j30, 1)) {
				fRec15_tmp[j30] = fRec15_perm[j30];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec15[i] = 1.0499999999999998 * static_cast<double>(input15[i]) + 0.9 * fRec15[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j31 = 0; j31 < 4; j31 = faust_wrap_add(j31, 1)) {
				fRec15_perm[j31] = fRec15_tmp[faust_wrap_add(vsize, j31)];
			}
			/* Recursive loop 21 */
			/* Pre code */
			for (int j32 = 0; j32 < 4; j32 = faust_wrap_add(j32, 1)) {
				fRec16_tmp[j32] = fRec16_perm[j32];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec16[i] = 1.0499999999999998 * static_cast<double>(input16[i]) + 0.9 * fRec16[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j33 = 0; j33 < 4; j33 = faust_wrap_add(j33, 1)) {
				fRec16_perm[j33] = fRec16_tmp[faust_wrap_add(vsize, j33)];
			}
			/* Recursive loop 22 */
			/* Pre code */
			for (int j34 = 0; j34 < 4; j34 = faust_wrap_add(j34, 1)) {
				fRec17_tmp[j34] = fRec17_perm[j34];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec17[i] = 1.0499999999999998 * static_cast<double>(input17[i]) + 0.9 * fRec17[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j35 = 0; j35 < 4; j35 = faust_wrap_add(j35, 1)) {
				fRec17_perm[j35] = fRec17_tmp[faust_wrap_add(vsize, j35)];
			}
			/* Vectorizable loop 23 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output5[i] = static_cast<FAUSTFLOAT>(fRec15[i] * (fRec16[i] + fRec17[i]));
			}
			/* Recursive loop 24 */
			/* Pre code */
			for (int j36 = 0; j36 < 4; j36 = faust_wrap_add(j36, 1)) {
				fRec18_tmp[j36] = fRec18_perm[j36];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec18[i] = 0.09999999999999998 * static_cast<double>(faust_wrap_mul(static_cast<int>(3.5 * static_cast<double>(input18[i])), static_cast<int>(3.5 * static_cast<double>(input19[i]))) % (faust_wrap_add(static_cast<int>(static_cast<double>(input20[i])), 3))) + 0.9 * fRec18[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j37 = 0; j37 < 4; j37 = faust_wrap_add(j37, 1)) {
				fRec18_perm[j37] = fRec18_tmp[faust_wrap_add(vsize, j37)];
			}
			/* Vectorizable loop 25 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output6[i] = static_cast<FAUSTFLOAT>(fRec18[i]);
			}
			/* Recursive loop 26 */
			/* Pre code */
			for (int j38 = 0; j38 < 4; j38 = faust_wrap_add(j38, 1)) {
				fRec19_tmp[j38] = fRec19_perm[j38];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec19[i] = 0.09999999999999998 * static_cast<double>(faust_wrap_mul(static_cast<int>(3.5 * static_cast<double>(input21[i])), static_cast<int>(3.5 * static_cast<double>(input22[i]))) % (faust_wrap_add(static_cast<int>(static_cast<double>(input23[i])), 3))) + 0.9 * fRec19[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j39 = 0; j39 < 4; j39 = faust_wrap_add(j39, 1)) {
				fRec19_perm[j39] = fRec19_tmp[faust_wrap_add(vsize, j39)];
			}
			/* Vectorizable loop 27 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output7[i] = static_cast<FAUSTFLOAT>(fRec19[i]);
			}
			/* Recursive loop 28 */
			/* Pre code */
			for (int j40 = 0; j40 < 4; j40 = faust_wrap_add(j40, 1)) {
				fRec20_tmp[j40] = fRec20_perm[j40];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec20[i] = 0.09999999999999998 * static_cast<double>(faust_wrap_mul(static_cast<int>(3.5 * static_cast<double>(input24[i])), static_cast<int>(3.5 * static_cast<double>(input25[i])) % (faust_wrap_add(static_cast<int>(static_cast<double>(input26[i])), 3)))) + 0.9 * fRec20[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j41 = 0; j41 < 4; j41 = faust_wrap_add(j41, 1)) {
				fRec20_perm[j41] = fRec20_tmp[faust_wrap_add(vsize, j41)];
			}
			/* Vectorizable loop 29 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output8[i] = static_cast<FAUSTFLOAT>(fRec20[i]);
			}
			/* Recursive loop 30 */
			/* Pre code */
			for (int j42 = 0; j42 < 4; j42 = faust_wrap_add(j42, 1)) {
				fRec21_tmp[j42] = fRec21_perm[j42];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec21[i] = 0.09999999999999998 * static_cast<double>((static_cast<int>(3.5 * static_cast<double>(input27[i])) << static_cast<int>(3.5 * static_cast<double>(input28[i]))) >> (faust_wrap_add(static_cast<int>(static_cast<double>(input29[i])), 3))) + 0.9 * fRec21[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j43 = 0; j43 < 4; j43 = faust_wrap_add(j43, 1)) {
				fRec21_perm[j43] = fRec21_tmp[faust_wrap_add(vsize, j43)];
			}
			/* Vectorizable loop 31 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output9[i] = static_cast<FAUSTFLOAT>(fRec21[i]);
			}
			/* Recursive loop 32 */
			/* Pre code */
			for (int j44 = 0; j44 < 4; j44 = faust_wrap_add(j44, 1)) {
				fRec22_tmp[j44] = fRec22_perm[j44];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec22[i] = 0.09999999999999998 * static_cast<double>((static_cast<int>(3.5 * static_cast<double>(input30[i])) << static_cast<int>(3.5 * static_cast<double>(input31[i]))) >> (faust_wrap_add(static_cast<int>(static_cast<double>(input32[i])), 3))) + 0.9 * fRec22[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j45 = 0; j45 < 4; j45 = faust_wrap_add(j45, 1)) {
				fRec22_perm[j45] = fRec22_tmp[faust_wrap_add(vsize, j45)];
			}
			/* Vectorizable loop 33 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output10[i] = static_cast<FAUSTFLOAT>(fRec22[i]);
			}
			/* Recursive loop 34 */
			/* Pre code */
			for (int j46 = 0; j46 < 4; j46 = faust_wrap_add(j46, 1)) {
				fRec23_tmp[j46] = fRec23_perm[j46];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec23[i] = 0.09999999999999998 * static_cast<double>(static_cast<int>(3.5 * static_cast<double>(input33[i])) << (static_cast<int>(3.5 * static_cast<double>(input34[i])) >> (faust_wrap_add(static_cast<int>(static_cast<double>(input35[i])), 3)))) + 0.9 * fRec23[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j47 = 0; j47 < 4; j47 = faust_wrap_add(j47, 1)) {
				fRec23_perm[j47] = fRec23_tmp[faust_wrap_add(vsize, j47)];
			}
			/* Vectorizable loop 35 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output11[i] = static_cast<FAUSTFLOAT>(fRec23[i]);
			}
			/* Recursive loop 36 */
			/* Pre code */
			for (int j48 = 0; j48 < 4; j48 = faust_wrap_add(j48, 1)) {
				fRec24_tmp[j48] = fRec24_perm[j48];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec24[i] = 0.09999999999999998 * static_cast<double>((static_cast<int>(3.5 * static_cast<double>(input36[i])) << static_cast<int>(3.5 * static_cast<double>(input37[i]))) <= (faust_wrap_add(static_cast<int>(static_cast<double>(input38[i])), 3))) + 0.9 * fRec24[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j49 = 0; j49 < 4; j49 = faust_wrap_add(j49, 1)) {
				fRec24_perm[j49] = fRec24_tmp[faust_wrap_add(vsize, j49)];
			}
			/* Vectorizable loop 37 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output12[i] = static_cast<FAUSTFLOAT>(fRec24[i]);
			}
			/* Recursive loop 38 */
			/* Pre code */
			for (int j50 = 0; j50 < 4; j50 = faust_wrap_add(j50, 1)) {
				fRec25_tmp[j50] = fRec25_perm[j50];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec25[i] = 0.09999999999999998 * static_cast<double>((static_cast<int>(3.5 * static_cast<double>(input39[i])) << static_cast<int>(3.5 * static_cast<double>(input40[i]))) <= (faust_wrap_add(static_cast<int>(static_cast<double>(input41[i])), 3))) + 0.9 * fRec25[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j51 = 0; j51 < 4; j51 = faust_wrap_add(j51, 1)) {
				fRec25_perm[j51] = fRec25_tmp[faust_wrap_add(vsize, j51)];
			}
			/* Vectorizable loop 39 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output13[i] = static_cast<FAUSTFLOAT>(fRec25[i]);
			}
			/* Recursive loop 40 */
			/* Pre code */
			for (int j52 = 0; j52 < 4; j52 = faust_wrap_add(j52, 1)) {
				fRec26_tmp[j52] = fRec26_perm[j52];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec26[i] = 0.09999999999999998 * static_cast<double>(static_cast<int>(3.5 * static_cast<double>(input42[i])) << (static_cast<int>(3.5 * static_cast<double>(input43[i])) <= (faust_wrap_add(static_cast<int>(static_cast<double>(input44[i])), 3)))) + 0.9 * fRec26[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j53 = 0; j53 < 4; j53 = faust_wrap_add(j53, 1)) {
				fRec26_perm[j53] = fRec26_tmp[faust_wrap_add(vsize, j53)];
			}
			/* Vectorizable loop 41 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output14[i] = static_cast<FAUSTFLOAT>(fRec26[i]);
			}
			/* Recursive loop 42 */
			/* Pre code */
			for (int j54 = 0; j54 < 4; j54 = faust_wrap_add(j54, 1)) {
				fRec27_tmp[j54] = fRec27_perm[j54];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec27[i] = 0.09999999999999998 * static_cast<double>((static_cast<int>(3.5 * static_cast<double>(input45[i])) < static_cast<int>(3.5 * static_cast<double>(input46[i]))) <= (faust_wrap_add(static_cast<int>(static_cast<double>(input47[i])), 3))) + 0.9 * fRec27[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j55 = 0; j55 < 4; j55 = faust_wrap_add(j55, 1)) {
				fRec27_perm[j55] = fRec27_tmp[faust_wrap_add(vsize, j55)];
			}
			/* Vectorizable loop 43 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output15[i] = static_cast<FAUSTFLOAT>(fRec27[i]);
			}
			/* Recursive loop 44 */
			/* Pre code */
			for (int j56 = 0; j56 < 4; j56 = faust_wrap_add(j56, 1)) {
				fRec28_tmp[j56] = fRec28_perm[j56];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec28[i] = 0.09999999999999998 * static_cast<double>((static_cast<int>(3.5 * static_cast<double>(input48[i])) < static_cast<int>(3.5 * static_cast<double>(input49[i]))) <= (faust_wrap_add(static_cast<int>(static_cast<double>(input50[i])), 3))) + 0.9 * fRec28[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j57 = 0; j57 < 4; j57 = faust_wrap_add(j57, 1)) {
				fRec28_perm[j57] = fRec28_tmp[faust_wrap_add(vsize, j57)];
			}
			/* Vectorizable loop 45 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output16[i] = static_cast<FAUSTFLOAT>(fRec28[i]);
			}
			/* Recursive loop 46 */
			/* Pre code */
			for (int j58 = 0; j58 < 4; j58 = faust_wrap_add(j58, 1)) {
				fRec29_tmp[j58] = fRec29_perm[j58];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec29[i] = 0.09999999999999998 * static_cast<double>(static_cast<int>(3.5 * static_cast<double>(input51[i])) < (static_cast<int>(3.5 * static_cast<double>(input52[i])) <= (faust_wrap_add(static_cast<int>(static_cast<double>(input53[i])), 3)))) + 0.9 * fRec29[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j59 = 0; j59 < 4; j59 = faust_wrap_add(j59, 1)) {
				fRec29_perm[j59] = fRec29_tmp[faust_wrap_add(vsize, j59)];
			}
			/* Vectorizable loop 47 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output17[i] = static_cast<FAUSTFLOAT>(fRec29[i]);
			}
			/* Recursive loop 48 */
			/* Pre code */
			for (int j60 = 0; j60 < 4; j60 = faust_wrap_add(j60, 1)) {
				fRec30_tmp[j60] = fRec30_perm[j60];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec30[i] = 0.09999999999999998 * static_cast<double>((static_cast<int>(3.5 * static_cast<double>(input54[i])) == static_cast<int>(3.5 * static_cast<double>(input55[i]))) != (faust_wrap_add(static_cast<int>(static_cast<double>(input56[i])), 3))) + 0.9 * fRec30[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j61 = 0; j61 < 4; j61 = faust_wrap_add(j61, 1)) {
				fRec30_perm[j61] = fRec30_tmp[faust_wrap_add(vsize, j61)];
			}
			/* Vectorizable loop 49 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output18[i] = static_cast<FAUSTFLOAT>(fRec30[i]);
			}
			/* Recursive loop 50 */
			/* Pre code */
			for (int j62 = 0; j62 < 4; j62 = faust_wrap_add(j62, 1)) {
				fRec31_tmp[j62] = fRec31_perm[j62];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec31[i] = 0.09999999999999998 * static_cast<double>((static_cast<int>(3.5 * static_cast<double>(input57[i])) == static_cast<int>(3.5 * static_cast<double>(input58[i]))) != (faust_wrap_add(static_cast<int>(static_cast<double>(input59[i])), 3))) + 0.9 * fRec31[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j63 = 0; j63 < 4; j63 = faust_wrap_add(j63, 1)) {
				fRec31_perm[j63] = fRec31_tmp[faust_wrap_add(vsize, j63)];
			}
			/* Vectorizable loop 51 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output19[i] = static_cast<FAUSTFLOAT>(fRec31[i]);
			}
			/* Recursive loop 52 */
			/* Pre code */
			for (int j64 = 0; j64 < 4; j64 = faust_wrap_add(j64, 1)) {
				fRec32_tmp[j64] = fRec32_perm[j64];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec32[i] = 0.09999999999999998 * static_cast<double>(static_cast<int>(3.5 * static_cast<double>(input60[i])) == (static_cast<int>(3.5 * static_cast<double>(input61[i])) != (faust_wrap_add(static_cast<int>(static_cast<double>(input62[i])), 3)))) + 0.9 * fRec32[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j65 = 0; j65 < 4; j65 = faust_wrap_add(j65, 1)) {
				fRec32_perm[j65] = fRec32_tmp[faust_wrap_add(vsize, j65)];
			}
			/* Vectorizable loop 53 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output20[i] = static_cast<FAUSTFLOAT>(fRec32[i]);
			}
			/* Recursive loop 54 */
			/* Pre code */
			for (int j66 = 0; j66 < 4; j66 = faust_wrap_add(j66, 1)) {
				fRec33_tmp[j66] = fRec33_perm[j66];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec33[i] = 0.09999999999999998 * static_cast<double>((static_cast<int>(3.5 * static_cast<double>(input63[i])) & static_cast<int>(3.5 * static_cast<double>(input64[i]))) | (faust_wrap_add(static_cast<int>(static_cast<double>(input65[i])), 3))) + 0.9 * fRec33[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j67 = 0; j67 < 4; j67 = faust_wrap_add(j67, 1)) {
				fRec33_perm[j67] = fRec33_tmp[faust_wrap_add(vsize, j67)];
			}
			/* Vectorizable loop 55 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output21[i] = static_cast<FAUSTFLOAT>(fRec33[i]);
			}
			/* Recursive loop 56 */
			/* Pre code */
			for (int j68 = 0; j68 < 4; j68 = faust_wrap_add(j68, 1)) {
				fRec34_tmp[j68] = fRec34_perm[j68];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec34[i] = 0.09999999999999998 * static_cast<double>((static_cast<int>(3.5 * static_cast<double>(input66[i])) & static_cast<int>(3.5 * static_cast<double>(input67[i]))) ^ faust_wrap_add(static_cast<int>(static_cast<double>(input68[i])), 3)) + 0.9 * fRec34[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j69 = 0; j69 < 4; j69 = faust_wrap_add(j69, 1)) {
				fRec34_perm[j69] = fRec34_tmp[faust_wrap_add(vsize, j69)];
			}
			/* Vectorizable loop 57 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output22[i] = static_cast<FAUSTFLOAT>(fRec34[i]);
			}
			/* Recursive loop 58 */
			/* Pre code */
			for (int j70 = 0; j70 < 4; j70 = faust_wrap_add(j70, 1)) {
				fRec35_tmp[j70] = fRec35_perm[j70];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec35[i] = 0.09999999999999998 * static_cast<double>((static_cast<int>(3.5 * static_cast<double>(input69[i])) & static_cast<int>(3.5 * static_cast<double>(input70[i]))) | (faust_wrap_add(static_cast<int>(static_cast<double>(input71[i])), 3))) + 0.9 * fRec35[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j71 = 0; j71 < 4; j71 = faust_wrap_add(j71, 1)) {
				fRec35_perm[j71] = fRec35_tmp[faust_wrap_add(vsize, j71)];
			}
			/* Vectorizable loop 59 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output23[i] = static_cast<FAUSTFLOAT>(fRec35[i]);
			}
			/* Recursive loop 60 */
			/* Pre code */
			for (int j72 = 0; j72 < 4; j72 = faust_wrap_add(j72, 1)) {
				fRec36_tmp[j72] = fRec36_perm[j72];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec36[i] = 0.09999999999999998 * static_cast<double>((static_cast<int>(3.5 * static_cast<double>(input72[i])) & static_cast<int>(3.5 * static_cast<double>(input73[i]))) ^ faust_wrap_add(static_cast<int>(static_cast<double>(input74[i])), 3)) + 0.9 * fRec36[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j73 = 0; j73 < 4; j73 = faust_wrap_add(j73, 1)) {
				fRec36_perm[j73] = fRec36_tmp[faust_wrap_add(vsize, j73)];
			}
			/* Vectorizable loop 61 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output24[i] = static_cast<FAUSTFLOAT>(fRec36[i]);
			}
			/* Recursive loop 62 */
			/* Pre code */
			for (int j74 = 0; j74 < 4; j74 = faust_wrap_add(j74, 1)) {
				fRec37_tmp[j74] = fRec37_perm[j74];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec37[i] = 0.09999999999999998 * static_cast<double>(static_cast<int>(3.5 * static_cast<double>(input75[i])) & (static_cast<int>(3.5 * static_cast<double>(input76[i])) | (faust_wrap_add(static_cast<int>(static_cast<double>(input77[i])), 3)))) + 0.9 * fRec37[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j75 = 0; j75 < 4; j75 = faust_wrap_add(j75, 1)) {
				fRec37_perm[j75] = fRec37_tmp[faust_wrap_add(vsize, j75)];
			}
			/* Vectorizable loop 63 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output25[i] = static_cast<FAUSTFLOAT>(fRec37[i]);
			}
			/* Recursive loop 64 */
			/* Pre code */
			for (int j76 = 0; j76 < 4; j76 = faust_wrap_add(j76, 1)) {
				fRec38_tmp[j76] = fRec38_perm[j76];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec38[i] = 0.09999999999999998 * static_cast<double>(static_cast<int>(3.5 * static_cast<double>(input78[i])) & (static_cast<int>(3.5 * static_cast<double>(input79[i])) ^ faust_wrap_add(static_cast<int>(static_cast<double>(input80[i])), 3))) + 0.9 * fRec38[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j77 = 0; j77 < 4; j77 = faust_wrap_add(j77, 1)) {
				fRec38_perm[j77] = fRec38_tmp[faust_wrap_add(vsize, j77)];
			}
			/* Vectorizable loop 65 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output26[i] = static_cast<FAUSTFLOAT>(fRec38[i]);
			}
			/* Recursive loop 66 */
			/* Pre code */
			for (int j78 = 0; j78 < 4; j78 = faust_wrap_add(j78, 1)) {
				fRec39_tmp[j78] = fRec39_perm[j78];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec39[i] = 0.09999999999999998 * static_cast<double>((faust_wrap_add(faust_wrap_add(static_cast<int>(static_cast<double>(input82[i])), static_cast<int>(3.5 * static_cast<double>(input81[i]))), faust_wrap_sub(3, static_cast<int>(3.5 * static_cast<double>(input83[i]))))) | (faust_wrap_add(static_cast<int>(static_cast<double>(input84[i])), 3))) + 0.9 * fRec39[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j79 = 0; j79 < 4; j79 = faust_wrap_add(j79, 1)) {
				fRec39_perm[j79] = fRec39_tmp[faust_wrap_add(vsize, j79)];
			}
			/* Vectorizable loop 67 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output27[i] = static_cast<FAUSTFLOAT>(fRec39[i]);
			}
			/* Recursive loop 68 */
			/* Pre code */
			for (int j80 = 0; j80 < 4; j80 = faust_wrap_add(j80, 1)) {
				fRec40_tmp[j80] = fRec40_perm[j80];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec40[i] = 0.09999999999999998 * static_cast<double>((((static_cast<int>(std::fmod(static_cast<double>(faust_wrap_mul(faust_wrap_add(static_cast<int>(static_cast<double>(input86[i])), 3), static_cast<int>(3.5 * static_cast<double>(input85[i])))) / static_cast<double>(faust_wrap_add(static_cast<int>(3.5 * static_cast<double>(input87[i])), 1)), static_cast<double>(faust_wrap_add(static_cast<int>(static_cast<double>(input88[i])), 3)))) & static_cast<int>(3.5 * static_cast<double>(input89[i]))) ^ faust_wrap_add(static_cast<int>(static_cast<double>(input90[i])), 3)) << static_cast<int>(3.5 * static_cast<double>(input91[i]))) >> (faust_wrap_add(static_cast<int>(static_cast<double>(input92[i])), 3))) + 0.9 * fRec40[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j81 = 0; j81 < 4; j81 = faust_wrap_add(j81, 1)) {
				fRec40_perm[j81] = fRec40_tmp[faust_wrap_add(vsize, j81)];
			}
			/* Vectorizable loop 69 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output28[i] = static_cast<FAUSTFLOAT>(fRec40[i]);
			}
			/* Recursive loop 70 */
			/* Pre code */
			for (int j82 = 0; j82 < 4; j82 = faust_wrap_add(j82, 1)) {
				fRec41_tmp[j82] = fRec41_perm[j82];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec41[i] = 0.09999999999999998 * static_cast<double>((static_cast<int>(3.5 * static_cast<double>(input93[i])) <= (faust_wrap_add(static_cast<int>(static_cast<double>(input94[i])), 3))) >= ((faust_wrap_add(faust_wrap_add(static_cast<int>(static_cast<double>(input96[i])), static_cast<int>(3.5 * static_cast<double>(input95[i]))), faust_wrap_sub(3, static_cast<int>(3.5 * static_cast<double>(input97[i]))))) | (faust_wrap_add(static_cast<int>(static_cast<double>(input98[i])), 3)))) + 0.9 * fRec41[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j83 = 0; j83 < 4; j83 = faust_wrap_add(j83, 1)) {
				fRec41_perm[j83] = fRec41_tmp[faust_wrap_add(vsize, j83)];
			}
			/* Vectorizable loop 71 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output29[i] = static_cast<FAUSTFLOAT>(fRec41[i]);
			}
			/* Recursive loop 72 */
			/* Pre code */
			for (int j84 = 0; j84 < 4; j84 = faust_wrap_add(j84, 1)) {
				fRec42_tmp[j84] = fRec42_perm[j84];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec42[i] = 0.09999999999999998 * static_cast<double>((faust_wrap_sub(faust_wrap_add(static_cast<int>(static_cast<double>(input99[i])), static_cast<int>(3.5 * static_cast<double>(input100[i]))), static_cast<int>(static_cast<double>(input101[i])))) | ((((static_cast<int>(std::fmod(static_cast<double>(faust_wrap_mul(faust_wrap_add(static_cast<int>(static_cast<double>(input103[i])), 3), static_cast<int>(3.5 * static_cast<double>(input102[i])))) / static_cast<double>(faust_wrap_add(static_cast<int>(3.5 * static_cast<double>(input104[i])), 1)), static_cast<double>(faust_wrap_add(static_cast<int>(static_cast<double>(input105[i])), 3)))) & static_cast<int>(3.5 * static_cast<double>(input106[i]))) ^ faust_wrap_add(static_cast<int>(static_cast<double>(input107[i])), 3)) << static_cast<int>(3.5 * static_cast<double>(input108[i]))) >> (faust_wrap_add(static_cast<int>(static_cast<double>(input109[i])), 3)))) + 0.9 * fRec42[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j85 = 0; j85 < 4; j85 = faust_wrap_add(j85, 1)) {
				fRec42_perm[j85] = fRec42_tmp[faust_wrap_add(vsize, j85)];
			}
			/* Vectorizable loop 73 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output30[i] = static_cast<FAUSTFLOAT>(fRec42[i]);
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
