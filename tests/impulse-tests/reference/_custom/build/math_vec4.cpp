/* ------------------------------------------------------------
name: "math"
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

/* link with : "" */
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

static double mydsp_faustpower3_f(double value) {
	return value * value * value;
}
static int mydsp_faustpower3_i(int value) {
	return value * value * value;
}

class mydsp : public dsp {
	
 private:
	
	double fVec0_perm[4];
	int iVec1_perm[4];
	int fSampleRate;
	
 public:
	mydsp() {
	}
	
	mydsp(const mydsp&) = default;
	
	virtual ~mydsp() = default;
	
	mydsp& operator=(const mydsp&) = default;
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-a /Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/archs/impulsearch.cpp -lang cpp -i -fpga-mem-th 4 -ct 1 -es 1 -mcd 4 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs");
		m->declare("filename", "math.dsp");
		m->declare("math.lib/author", "GRAME");
		m->declare("math.lib/copyright", "GRAME");
		m->declare("math.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m->declare("math.lib/license", "LGPL with exception");
		m->declare("math.lib/name", "Math Library");
		m->declare("math.lib/version", "1.0");
		m->declare("name", "math");
	}

	virtual int getNumInputs() {
		return 104;
	}
	virtual int getNumOutputs() {
		return 76;
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
			fVec0_perm[l0] = 0.0;
		}
		for (int l1 = 0; l1 < 4; l1 = faust_wrap_add(l1, 1)) {
			iVec1_perm[l1] = 0;
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
		ui_interface->openVerticalBox("math");
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
		FAUSTFLOAT* output32_ptr = outputs[32];
		FAUSTFLOAT* output33_ptr = outputs[33];
		FAUSTFLOAT* output34_ptr = outputs[34];
		FAUSTFLOAT* output35_ptr = outputs[35];
		FAUSTFLOAT* output36_ptr = outputs[36];
		FAUSTFLOAT* output37_ptr = outputs[37];
		FAUSTFLOAT* output38_ptr = outputs[38];
		FAUSTFLOAT* output39_ptr = outputs[39];
		FAUSTFLOAT* output40_ptr = outputs[40];
		FAUSTFLOAT* output41_ptr = outputs[41];
		FAUSTFLOAT* output42_ptr = outputs[42];
		FAUSTFLOAT* output43_ptr = outputs[43];
		FAUSTFLOAT* output44_ptr = outputs[44];
		FAUSTFLOAT* output45_ptr = outputs[45];
		FAUSTFLOAT* output46_ptr = outputs[46];
		FAUSTFLOAT* output47_ptr = outputs[47];
		FAUSTFLOAT* output48_ptr = outputs[48];
		FAUSTFLOAT* output49_ptr = outputs[49];
		FAUSTFLOAT* output50_ptr = outputs[50];
		FAUSTFLOAT* output51_ptr = outputs[51];
		FAUSTFLOAT* output52_ptr = outputs[52];
		FAUSTFLOAT* output53_ptr = outputs[53];
		FAUSTFLOAT* output54_ptr = outputs[54];
		FAUSTFLOAT* output55_ptr = outputs[55];
		FAUSTFLOAT* output56_ptr = outputs[56];
		FAUSTFLOAT* output57_ptr = outputs[57];
		FAUSTFLOAT* output58_ptr = outputs[58];
		FAUSTFLOAT* output59_ptr = outputs[59];
		FAUSTFLOAT* output60_ptr = outputs[60];
		FAUSTFLOAT* output61_ptr = outputs[61];
		FAUSTFLOAT* output62_ptr = outputs[62];
		FAUSTFLOAT* output63_ptr = outputs[63];
		FAUSTFLOAT* output64_ptr = outputs[64];
		FAUSTFLOAT* output65_ptr = outputs[65];
		FAUSTFLOAT* output66_ptr = outputs[66];
		FAUSTFLOAT* output67_ptr = outputs[67];
		FAUSTFLOAT* output68_ptr = outputs[68];
		FAUSTFLOAT* output69_ptr = outputs[69];
		FAUSTFLOAT* output70_ptr = outputs[70];
		FAUSTFLOAT* output71_ptr = outputs[71];
		FAUSTFLOAT* output72_ptr = outputs[72];
		FAUSTFLOAT* output73_ptr = outputs[73];
		FAUSTFLOAT* output74_ptr = outputs[74];
		FAUSTFLOAT* output75_ptr = outputs[75];
		double fVec0_tmp[8];
		double* fVec0 = &fVec0_tmp[4];
		int iVec1_tmp[8];
		int* iVec1 = &iVec1_tmp[4];
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
			FAUSTFLOAT* output32 = &output32_ptr[vindex];
			FAUSTFLOAT* output33 = &output33_ptr[vindex];
			FAUSTFLOAT* output34 = &output34_ptr[vindex];
			FAUSTFLOAT* output35 = &output35_ptr[vindex];
			FAUSTFLOAT* output36 = &output36_ptr[vindex];
			FAUSTFLOAT* output37 = &output37_ptr[vindex];
			FAUSTFLOAT* output38 = &output38_ptr[vindex];
			FAUSTFLOAT* output39 = &output39_ptr[vindex];
			FAUSTFLOAT* output40 = &output40_ptr[vindex];
			FAUSTFLOAT* output41 = &output41_ptr[vindex];
			FAUSTFLOAT* output42 = &output42_ptr[vindex];
			FAUSTFLOAT* output43 = &output43_ptr[vindex];
			FAUSTFLOAT* output44 = &output44_ptr[vindex];
			FAUSTFLOAT* output45 = &output45_ptr[vindex];
			FAUSTFLOAT* output46 = &output46_ptr[vindex];
			FAUSTFLOAT* output47 = &output47_ptr[vindex];
			FAUSTFLOAT* output48 = &output48_ptr[vindex];
			FAUSTFLOAT* output49 = &output49_ptr[vindex];
			FAUSTFLOAT* output50 = &output50_ptr[vindex];
			FAUSTFLOAT* output51 = &output51_ptr[vindex];
			FAUSTFLOAT* output52 = &output52_ptr[vindex];
			FAUSTFLOAT* output53 = &output53_ptr[vindex];
			FAUSTFLOAT* output54 = &output54_ptr[vindex];
			FAUSTFLOAT* output55 = &output55_ptr[vindex];
			FAUSTFLOAT* output56 = &output56_ptr[vindex];
			FAUSTFLOAT* output57 = &output57_ptr[vindex];
			FAUSTFLOAT* output58 = &output58_ptr[vindex];
			FAUSTFLOAT* output59 = &output59_ptr[vindex];
			FAUSTFLOAT* output60 = &output60_ptr[vindex];
			FAUSTFLOAT* output61 = &output61_ptr[vindex];
			FAUSTFLOAT* output62 = &output62_ptr[vindex];
			FAUSTFLOAT* output63 = &output63_ptr[vindex];
			FAUSTFLOAT* output64 = &output64_ptr[vindex];
			FAUSTFLOAT* output65 = &output65_ptr[vindex];
			FAUSTFLOAT* output66 = &output66_ptr[vindex];
			FAUSTFLOAT* output67 = &output67_ptr[vindex];
			FAUSTFLOAT* output68 = &output68_ptr[vindex];
			FAUSTFLOAT* output69 = &output69_ptr[vindex];
			FAUSTFLOAT* output70 = &output70_ptr[vindex];
			FAUSTFLOAT* output71 = &output71_ptr[vindex];
			FAUSTFLOAT* output72 = &output72_ptr[vindex];
			FAUSTFLOAT* output73 = &output73_ptr[vindex];
			FAUSTFLOAT* output74 = &output74_ptr[vindex];
			FAUSTFLOAT* output75 = &output75_ptr[vindex];
			int vsize = 4;
			/* Vectorizable loop 0 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				fVec0_tmp[j0] = fVec0_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVec0[i] = 2.0;
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				fVec0_perm[j1] = fVec0_tmp[faust_wrap_add(vsize, j1)];
			}
			/* Vectorizable loop 1 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(std::pow(fVec0[faust_wrap_sub(i, 1)], 3e+01));
			}
			/* Vectorizable loop 2 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				iVec1_tmp[j2] = iVec1_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iVec1[i] = 2;
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				iVec1_perm[j3] = iVec1_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(static_cast<int>(std::pow(static_cast<double>(iVec1[faust_wrap_sub(i, 1)]), static_cast<double>(30))));
			}
			/* Vectorizable loop 4 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output2[i] = static_cast<FAUSTFLOAT>(1073741824.0);
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output3[i] = static_cast<FAUSTFLOAT>(1073741824);
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output4[i] = static_cast<FAUSTFLOAT>(std::isnan(static_cast<double>(input0[i])));
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output5[i] = static_cast<FAUSTFLOAT>(std::isinf(static_cast<double>(input1[i])));
			}
			/* Vectorizable loop 8 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output6[i] = static_cast<FAUSTFLOAT>(copysign(static_cast<double>(input2[i]), static_cast<double>(input3[i])));
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output7[i] = static_cast<FAUSTFLOAT>(static_cast<int>(static_cast<double>(input4[i])) >> static_cast<int>(static_cast<double>(input5[i])));
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output8[i] = static_cast<FAUSTFLOAT>(static_cast<int>(static_cast<double>(input6[i])) << static_cast<int>(static_cast<double>(input7[i])));
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output9[i] = static_cast<FAUSTFLOAT>(static_cast<int>(10.5 * static_cast<double>(input8[i])) % 3);
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output10[i] = static_cast<FAUSTFLOAT>(std::fmod(10.5 * static_cast<double>(input9[i]), 3.0));
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output11[i] = static_cast<FAUSTFLOAT>(static_cast<int>(static_cast<double>(input10[i])) & static_cast<int>(static_cast<double>(input11[i])));
			}
			/* Vectorizable loop 14 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output12[i] = static_cast<FAUSTFLOAT>(static_cast<int>(3.5 * static_cast<double>(input12[i])) & static_cast<int>(2.4 * static_cast<double>(input13[i])));
			}
			/* Vectorizable loop 15 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output13[i] = static_cast<FAUSTFLOAT>(static_cast<int>(3.5 * static_cast<double>(input14[i])) & static_cast<int>(2.4 * static_cast<double>(input15[i])));
			}
			/* Vectorizable loop 16 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output14[i] = static_cast<FAUSTFLOAT>(2.4 * static_cast<double>(static_cast<int>(3.5 * static_cast<double>(input16[i])) & static_cast<int>(static_cast<double>(input17[i]))));
			}
			/* Vectorizable loop 17 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output15[i] = static_cast<FAUSTFLOAT>(static_cast<int>(3.5 * static_cast<double>(input18[i])) | static_cast<int>(2.4 * static_cast<double>(input19[i])));
			}
			/* Vectorizable loop 18 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output16[i] = static_cast<FAUSTFLOAT>(static_cast<int>(3.5 * static_cast<double>(input20[i])) | static_cast<int>(2.4 * static_cast<double>(input21[i])));
			}
			/* Vectorizable loop 19 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output17[i] = static_cast<FAUSTFLOAT>(static_cast<int>(3.5 * static_cast<double>(input22[i])) ^ static_cast<int>(2.4 * static_cast<double>(input23[i])));
			}
			/* Vectorizable loop 20 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output18[i] = static_cast<FAUSTFLOAT>(static_cast<int>(3.5 * static_cast<double>(input24[i])) ^ static_cast<int>(2.4 * static_cast<double>(input25[i])));
			}
			/* Vectorizable loop 21 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output19[i] = static_cast<FAUSTFLOAT>(static_cast<int>(std::pow(static_cast<double>(static_cast<int>(3.5 * static_cast<double>(input26[i]))), static_cast<double>(static_cast<int>(2.4 * static_cast<double>(input27[i]))))));
			}
			/* Vectorizable loop 22 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output20[i] = static_cast<FAUSTFLOAT>(2.4 * static_cast<double>(input28[i]) * std::pow(3.5, static_cast<double>(input29[i])));
			}
			/* Vectorizable loop 23 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output21[i] = static_cast<FAUSTFLOAT>(static_cast<int>(3.5 * static_cast<double>(input30[i])) > static_cast<int>(2.4 * static_cast<double>(input31[i])));
			}
			/* Vectorizable loop 24 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output22[i] = static_cast<FAUSTFLOAT>((3.5 * static_cast<double>(input32[i])) > static_cast<double>(static_cast<int>(2.4 * static_cast<double>(input33[i]))));
			}
			/* Vectorizable loop 25 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output23[i] = static_cast<FAUSTFLOAT>((3.5 * static_cast<double>(input34[i])) > (2.4 * static_cast<double>(input35[i])));
			}
			/* Vectorizable loop 26 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output24[i] = static_cast<FAUSTFLOAT>(static_cast<int>(3.5 * static_cast<double>(input36[i])) >= static_cast<int>(2.4 * static_cast<double>(input37[i])));
			}
			/* Vectorizable loop 27 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output25[i] = static_cast<FAUSTFLOAT>((3.5 * static_cast<double>(input38[i])) >= (2.4 * static_cast<double>(input39[i])));
			}
			/* Vectorizable loop 28 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output26[i] = static_cast<FAUSTFLOAT>(static_cast<int>(3.5 * static_cast<double>(input40[i])) < static_cast<int>(2.4 * static_cast<double>(input41[i])));
			}
			/* Vectorizable loop 29 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output27[i] = static_cast<FAUSTFLOAT>((3.5 * static_cast<double>(input42[i])) < (2.4 * static_cast<double>(input43[i])));
			}
			/* Vectorizable loop 30 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output28[i] = static_cast<FAUSTFLOAT>(static_cast<int>(3.5 * static_cast<double>(input44[i])) <= static_cast<int>(2.4 * static_cast<double>(input45[i])));
			}
			/* Vectorizable loop 31 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output29[i] = static_cast<FAUSTFLOAT>((3.5 * static_cast<double>(input46[i])) <= (2.4 * static_cast<double>(input47[i])));
			}
			/* Vectorizable loop 32 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output30[i] = static_cast<FAUSTFLOAT>(static_cast<int>(3.5 * static_cast<double>(input48[i])) == static_cast<int>(2.4 * static_cast<double>(input49[i])));
			}
			/* Vectorizable loop 33 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output31[i] = static_cast<FAUSTFLOAT>((3.5 * static_cast<double>(input50[i])) == (2.4 * static_cast<double>(input51[i])));
			}
			/* Vectorizable loop 34 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output32[i] = static_cast<FAUSTFLOAT>(static_cast<int>(3.5 * static_cast<double>(input52[i])) != static_cast<int>(2.4 * static_cast<double>(input53[i])));
			}
			/* Vectorizable loop 35 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output33[i] = static_cast<FAUSTFLOAT>((3.5 * static_cast<double>(input54[i])) != (2.4 * static_cast<double>(input55[i])));
			}
			/* Vectorizable loop 36 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output34[i] = static_cast<FAUSTFLOAT>(std::abs(static_cast<int>(4.4 * static_cast<double>(input56[i]))));
			}
			/* Vectorizable loop 37 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output35[i] = static_cast<FAUSTFLOAT>(std::abs(static_cast<int>(-(4.4 * static_cast<double>(input57[i])))));
			}
			/* Vectorizable loop 38 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output36[i] = static_cast<FAUSTFLOAT>(std::fabs(4.4 * static_cast<double>(input58[i])));
			}
			/* Vectorizable loop 39 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output37[i] = static_cast<FAUSTFLOAT>(std::fabs(-(4.4 * static_cast<double>(input59[i]))));
			}
			/* Vectorizable loop 40 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output38[i] = static_cast<FAUSTFLOAT>(std::acos(0.5 * static_cast<double>(input60[i])));
			}
			/* Vectorizable loop 41 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output39[i] = static_cast<FAUSTFLOAT>(std::acos(static_cast<double>(static_cast<int>(0.5 * static_cast<double>(input61[i])))));
			}
			/* Vectorizable loop 42 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output40[i] = static_cast<FAUSTFLOAT>(std::asin(0.5 * static_cast<double>(input62[i])));
			}
			/* Vectorizable loop 43 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output41[i] = static_cast<FAUSTFLOAT>(std::atan(0.5 * static_cast<double>(input63[i])));
			}
			/* Vectorizable loop 44 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output42[i] = static_cast<FAUSTFLOAT>(std::atan2(0.5 * static_cast<double>(input64[i]), 4.0));
			}
			/* Vectorizable loop 45 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output43[i] = static_cast<FAUSTFLOAT>(std::atan2(static_cast<double>(static_cast<int>(0.5 * static_cast<double>(input65[i]))), 4.0));
			}
			/* Vectorizable loop 46 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output44[i] = static_cast<FAUSTFLOAT>(std::atan2(static_cast<double>(static_cast<int>(0.5 * static_cast<double>(input66[i]))), 4.0));
			}
			/* Vectorizable loop 47 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output45[i] = static_cast<FAUSTFLOAT>(std::ceil(1.3 * static_cast<double>(input67[i])));
			}
			/* Vectorizable loop 48 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output46[i] = static_cast<FAUSTFLOAT>(std::cos(0.3 * static_cast<double>(input68[i])));
			}
			/* Vectorizable loop 49 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output47[i] = static_cast<FAUSTFLOAT>(std::exp(0.5 * static_cast<double>(input69[i])));
			}
			/* Vectorizable loop 50 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output48[i] = static_cast<FAUSTFLOAT>(std::floor(6.5 * static_cast<double>(input70[i])));
			}
			/* Vectorizable loop 51 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output49[i] = static_cast<FAUSTFLOAT>(std::fmod(9.2 * static_cast<double>(input71[i]), 2.0));
			}
			/* Vectorizable loop 52 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output50[i] = static_cast<FAUSTFLOAT>(std::log(0.5 * (static_cast<double>(input72[i]) + 1.0)));
			}
			/* Vectorizable loop 53 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output51[i] = static_cast<FAUSTFLOAT>(std::log10(0.5 * (static_cast<double>(input73[i]) + 1.0)));
			}
			/* Vectorizable loop 54 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output52[i] = static_cast<FAUSTFLOAT>(std::max<double>(0.5 * static_cast<double>(input74[i]), 0.4 * static_cast<double>(input75[i])));
			}
			/* Vectorizable loop 55 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output53[i] = static_cast<FAUSTFLOAT>(std::min<double>(0.5 * static_cast<double>(input76[i]), 0.4 * static_cast<double>(input77[i])));
			}
			/* Vectorizable loop 56 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output54[i] = static_cast<FAUSTFLOAT>(std::max<double>(0.5 * static_cast<double>(input78[i]), static_cast<double>(static_cast<int>(0.4 * static_cast<double>(input79[i])))));
			}
			/* Vectorizable loop 57 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output55[i] = static_cast<FAUSTFLOAT>(std::min<double>(0.5 * static_cast<double>(input80[i]), static_cast<double>(static_cast<int>(0.4 * static_cast<double>(input81[i])))));
			}
			/* Vectorizable loop 58 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output56[i] = static_cast<FAUSTFLOAT>(std::max<int>(static_cast<int>(3.5 * static_cast<double>(input82[i])), static_cast<int>(2.4 * static_cast<double>(input83[i]))));
			}
			/* Vectorizable loop 59 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output57[i] = static_cast<FAUSTFLOAT>(std::min<int>(static_cast<int>(3.5 * static_cast<double>(input84[i])), static_cast<int>(2.4 * static_cast<double>(input85[i]))));
			}
			/* Vectorizable loop 60 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output58[i] = static_cast<FAUSTFLOAT>(std::pow(0.5 * static_cast<double>(input86[i]), 0.3));
			}
			/* Vectorizable loop 61 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output59[i] = static_cast<FAUSTFLOAT>(std::pow(static_cast<double>(static_cast<int>(0.5 * static_cast<double>(input87[i]))), 0.3));
			}
			/* Vectorizable loop 62 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output60[i] = static_cast<FAUSTFLOAT>(mydsp_faustpower3_f(0.5 * static_cast<double>(input88[i])));
			}
			/* Vectorizable loop 63 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output61[i] = static_cast<FAUSTFLOAT>(mydsp_faustpower3_i(static_cast<int>(0.5 * static_cast<double>(input89[i]))));
			}
			/* Vectorizable loop 64 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output62[i] = static_cast<FAUSTFLOAT>(mydsp_faustpower3_i(static_cast<int>(0.5 * static_cast<double>(input90[i]))));
			}
			/* Vectorizable loop 65 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output63[i] = static_cast<FAUSTFLOAT>(std::pow(1e+01, 3.0 * static_cast<double>(input91[i])));
			}
			/* Vectorizable loop 66 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output64[i] = static_cast<FAUSTFLOAT>(std::remainder(9.2 * static_cast<double>(input92[i]), 2.0));
			}
			/* Vectorizable loop 67 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output65[i] = static_cast<FAUSTFLOAT>(std::rint(1.5 * static_cast<double>(input93[i])));
			}
			/* Vectorizable loop 68 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output66[i] = static_cast<FAUSTFLOAT>(std::round(1.5 * static_cast<double>(input94[i])));
			}
			/* Vectorizable loop 69 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output67[i] = static_cast<FAUSTFLOAT>(std::sin(0.3 * static_cast<double>(input95[i])));
			}
			/* Vectorizable loop 70 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output68[i] = static_cast<FAUSTFLOAT>(std::sqrt(0.3 * static_cast<double>(input96[i])));
			}
			/* Vectorizable loop 71 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output69[i] = static_cast<FAUSTFLOAT>(std::tan(0.3 * static_cast<double>(input97[i])));
			}
			/* Vectorizable loop 72 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output70[i] = static_cast<FAUSTFLOAT>(acosh(0.3 * static_cast<double>(input98[i]) + 1e+01));
			}
			/* Vectorizable loop 73 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output71[i] = static_cast<FAUSTFLOAT>(asinh(0.3 * static_cast<double>(input99[i]) + 1e+01));
			}
			/* Vectorizable loop 74 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output72[i] = static_cast<FAUSTFLOAT>(atanh(0.3 * static_cast<double>(input100[i]) + 0.5));
			}
			/* Vectorizable loop 75 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output73[i] = static_cast<FAUSTFLOAT>(cosh(0.3 * static_cast<double>(input101[i]) + 1e+01));
			}
			/* Vectorizable loop 76 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output74[i] = static_cast<FAUSTFLOAT>(sinh(0.3 * static_cast<double>(input102[i]) + 1e+01));
			}
			/* Vectorizable loop 77 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output75[i] = static_cast<FAUSTFLOAT>(tanh(0.3 * static_cast<double>(input103[i]) + 1e+01));
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
			FAUSTFLOAT* output32 = &output32_ptr[vindex];
			FAUSTFLOAT* output33 = &output33_ptr[vindex];
			FAUSTFLOAT* output34 = &output34_ptr[vindex];
			FAUSTFLOAT* output35 = &output35_ptr[vindex];
			FAUSTFLOAT* output36 = &output36_ptr[vindex];
			FAUSTFLOAT* output37 = &output37_ptr[vindex];
			FAUSTFLOAT* output38 = &output38_ptr[vindex];
			FAUSTFLOAT* output39 = &output39_ptr[vindex];
			FAUSTFLOAT* output40 = &output40_ptr[vindex];
			FAUSTFLOAT* output41 = &output41_ptr[vindex];
			FAUSTFLOAT* output42 = &output42_ptr[vindex];
			FAUSTFLOAT* output43 = &output43_ptr[vindex];
			FAUSTFLOAT* output44 = &output44_ptr[vindex];
			FAUSTFLOAT* output45 = &output45_ptr[vindex];
			FAUSTFLOAT* output46 = &output46_ptr[vindex];
			FAUSTFLOAT* output47 = &output47_ptr[vindex];
			FAUSTFLOAT* output48 = &output48_ptr[vindex];
			FAUSTFLOAT* output49 = &output49_ptr[vindex];
			FAUSTFLOAT* output50 = &output50_ptr[vindex];
			FAUSTFLOAT* output51 = &output51_ptr[vindex];
			FAUSTFLOAT* output52 = &output52_ptr[vindex];
			FAUSTFLOAT* output53 = &output53_ptr[vindex];
			FAUSTFLOAT* output54 = &output54_ptr[vindex];
			FAUSTFLOAT* output55 = &output55_ptr[vindex];
			FAUSTFLOAT* output56 = &output56_ptr[vindex];
			FAUSTFLOAT* output57 = &output57_ptr[vindex];
			FAUSTFLOAT* output58 = &output58_ptr[vindex];
			FAUSTFLOAT* output59 = &output59_ptr[vindex];
			FAUSTFLOAT* output60 = &output60_ptr[vindex];
			FAUSTFLOAT* output61 = &output61_ptr[vindex];
			FAUSTFLOAT* output62 = &output62_ptr[vindex];
			FAUSTFLOAT* output63 = &output63_ptr[vindex];
			FAUSTFLOAT* output64 = &output64_ptr[vindex];
			FAUSTFLOAT* output65 = &output65_ptr[vindex];
			FAUSTFLOAT* output66 = &output66_ptr[vindex];
			FAUSTFLOAT* output67 = &output67_ptr[vindex];
			FAUSTFLOAT* output68 = &output68_ptr[vindex];
			FAUSTFLOAT* output69 = &output69_ptr[vindex];
			FAUSTFLOAT* output70 = &output70_ptr[vindex];
			FAUSTFLOAT* output71 = &output71_ptr[vindex];
			FAUSTFLOAT* output72 = &output72_ptr[vindex];
			FAUSTFLOAT* output73 = &output73_ptr[vindex];
			FAUSTFLOAT* output74 = &output74_ptr[vindex];
			FAUSTFLOAT* output75 = &output75_ptr[vindex];
			int vsize = faust_wrap_sub(count, vindex);
			/* Vectorizable loop 0 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				fVec0_tmp[j0] = fVec0_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVec0[i] = 2.0;
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				fVec0_perm[j1] = fVec0_tmp[faust_wrap_add(vsize, j1)];
			}
			/* Vectorizable loop 1 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(std::pow(fVec0[faust_wrap_sub(i, 1)], 3e+01));
			}
			/* Vectorizable loop 2 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				iVec1_tmp[j2] = iVec1_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iVec1[i] = 2;
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				iVec1_perm[j3] = iVec1_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(static_cast<int>(std::pow(static_cast<double>(iVec1[faust_wrap_sub(i, 1)]), static_cast<double>(30))));
			}
			/* Vectorizable loop 4 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output2[i] = static_cast<FAUSTFLOAT>(1073741824.0);
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output3[i] = static_cast<FAUSTFLOAT>(1073741824);
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output4[i] = static_cast<FAUSTFLOAT>(std::isnan(static_cast<double>(input0[i])));
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output5[i] = static_cast<FAUSTFLOAT>(std::isinf(static_cast<double>(input1[i])));
			}
			/* Vectorizable loop 8 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output6[i] = static_cast<FAUSTFLOAT>(copysign(static_cast<double>(input2[i]), static_cast<double>(input3[i])));
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output7[i] = static_cast<FAUSTFLOAT>(static_cast<int>(static_cast<double>(input4[i])) >> static_cast<int>(static_cast<double>(input5[i])));
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output8[i] = static_cast<FAUSTFLOAT>(static_cast<int>(static_cast<double>(input6[i])) << static_cast<int>(static_cast<double>(input7[i])));
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output9[i] = static_cast<FAUSTFLOAT>(static_cast<int>(10.5 * static_cast<double>(input8[i])) % 3);
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output10[i] = static_cast<FAUSTFLOAT>(std::fmod(10.5 * static_cast<double>(input9[i]), 3.0));
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output11[i] = static_cast<FAUSTFLOAT>(static_cast<int>(static_cast<double>(input10[i])) & static_cast<int>(static_cast<double>(input11[i])));
			}
			/* Vectorizable loop 14 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output12[i] = static_cast<FAUSTFLOAT>(static_cast<int>(3.5 * static_cast<double>(input12[i])) & static_cast<int>(2.4 * static_cast<double>(input13[i])));
			}
			/* Vectorizable loop 15 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output13[i] = static_cast<FAUSTFLOAT>(static_cast<int>(3.5 * static_cast<double>(input14[i])) & static_cast<int>(2.4 * static_cast<double>(input15[i])));
			}
			/* Vectorizable loop 16 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output14[i] = static_cast<FAUSTFLOAT>(2.4 * static_cast<double>(static_cast<int>(3.5 * static_cast<double>(input16[i])) & static_cast<int>(static_cast<double>(input17[i]))));
			}
			/* Vectorizable loop 17 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output15[i] = static_cast<FAUSTFLOAT>(static_cast<int>(3.5 * static_cast<double>(input18[i])) | static_cast<int>(2.4 * static_cast<double>(input19[i])));
			}
			/* Vectorizable loop 18 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output16[i] = static_cast<FAUSTFLOAT>(static_cast<int>(3.5 * static_cast<double>(input20[i])) | static_cast<int>(2.4 * static_cast<double>(input21[i])));
			}
			/* Vectorizable loop 19 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output17[i] = static_cast<FAUSTFLOAT>(static_cast<int>(3.5 * static_cast<double>(input22[i])) ^ static_cast<int>(2.4 * static_cast<double>(input23[i])));
			}
			/* Vectorizable loop 20 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output18[i] = static_cast<FAUSTFLOAT>(static_cast<int>(3.5 * static_cast<double>(input24[i])) ^ static_cast<int>(2.4 * static_cast<double>(input25[i])));
			}
			/* Vectorizable loop 21 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output19[i] = static_cast<FAUSTFLOAT>(static_cast<int>(std::pow(static_cast<double>(static_cast<int>(3.5 * static_cast<double>(input26[i]))), static_cast<double>(static_cast<int>(2.4 * static_cast<double>(input27[i]))))));
			}
			/* Vectorizable loop 22 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output20[i] = static_cast<FAUSTFLOAT>(2.4 * static_cast<double>(input28[i]) * std::pow(3.5, static_cast<double>(input29[i])));
			}
			/* Vectorizable loop 23 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output21[i] = static_cast<FAUSTFLOAT>(static_cast<int>(3.5 * static_cast<double>(input30[i])) > static_cast<int>(2.4 * static_cast<double>(input31[i])));
			}
			/* Vectorizable loop 24 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output22[i] = static_cast<FAUSTFLOAT>((3.5 * static_cast<double>(input32[i])) > static_cast<double>(static_cast<int>(2.4 * static_cast<double>(input33[i]))));
			}
			/* Vectorizable loop 25 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output23[i] = static_cast<FAUSTFLOAT>((3.5 * static_cast<double>(input34[i])) > (2.4 * static_cast<double>(input35[i])));
			}
			/* Vectorizable loop 26 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output24[i] = static_cast<FAUSTFLOAT>(static_cast<int>(3.5 * static_cast<double>(input36[i])) >= static_cast<int>(2.4 * static_cast<double>(input37[i])));
			}
			/* Vectorizable loop 27 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output25[i] = static_cast<FAUSTFLOAT>((3.5 * static_cast<double>(input38[i])) >= (2.4 * static_cast<double>(input39[i])));
			}
			/* Vectorizable loop 28 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output26[i] = static_cast<FAUSTFLOAT>(static_cast<int>(3.5 * static_cast<double>(input40[i])) < static_cast<int>(2.4 * static_cast<double>(input41[i])));
			}
			/* Vectorizable loop 29 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output27[i] = static_cast<FAUSTFLOAT>((3.5 * static_cast<double>(input42[i])) < (2.4 * static_cast<double>(input43[i])));
			}
			/* Vectorizable loop 30 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output28[i] = static_cast<FAUSTFLOAT>(static_cast<int>(3.5 * static_cast<double>(input44[i])) <= static_cast<int>(2.4 * static_cast<double>(input45[i])));
			}
			/* Vectorizable loop 31 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output29[i] = static_cast<FAUSTFLOAT>((3.5 * static_cast<double>(input46[i])) <= (2.4 * static_cast<double>(input47[i])));
			}
			/* Vectorizable loop 32 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output30[i] = static_cast<FAUSTFLOAT>(static_cast<int>(3.5 * static_cast<double>(input48[i])) == static_cast<int>(2.4 * static_cast<double>(input49[i])));
			}
			/* Vectorizable loop 33 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output31[i] = static_cast<FAUSTFLOAT>((3.5 * static_cast<double>(input50[i])) == (2.4 * static_cast<double>(input51[i])));
			}
			/* Vectorizable loop 34 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output32[i] = static_cast<FAUSTFLOAT>(static_cast<int>(3.5 * static_cast<double>(input52[i])) != static_cast<int>(2.4 * static_cast<double>(input53[i])));
			}
			/* Vectorizable loop 35 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output33[i] = static_cast<FAUSTFLOAT>((3.5 * static_cast<double>(input54[i])) != (2.4 * static_cast<double>(input55[i])));
			}
			/* Vectorizable loop 36 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output34[i] = static_cast<FAUSTFLOAT>(std::abs(static_cast<int>(4.4 * static_cast<double>(input56[i]))));
			}
			/* Vectorizable loop 37 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output35[i] = static_cast<FAUSTFLOAT>(std::abs(static_cast<int>(-(4.4 * static_cast<double>(input57[i])))));
			}
			/* Vectorizable loop 38 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output36[i] = static_cast<FAUSTFLOAT>(std::fabs(4.4 * static_cast<double>(input58[i])));
			}
			/* Vectorizable loop 39 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output37[i] = static_cast<FAUSTFLOAT>(std::fabs(-(4.4 * static_cast<double>(input59[i]))));
			}
			/* Vectorizable loop 40 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output38[i] = static_cast<FAUSTFLOAT>(std::acos(0.5 * static_cast<double>(input60[i])));
			}
			/* Vectorizable loop 41 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output39[i] = static_cast<FAUSTFLOAT>(std::acos(static_cast<double>(static_cast<int>(0.5 * static_cast<double>(input61[i])))));
			}
			/* Vectorizable loop 42 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output40[i] = static_cast<FAUSTFLOAT>(std::asin(0.5 * static_cast<double>(input62[i])));
			}
			/* Vectorizable loop 43 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output41[i] = static_cast<FAUSTFLOAT>(std::atan(0.5 * static_cast<double>(input63[i])));
			}
			/* Vectorizable loop 44 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output42[i] = static_cast<FAUSTFLOAT>(std::atan2(0.5 * static_cast<double>(input64[i]), 4.0));
			}
			/* Vectorizable loop 45 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output43[i] = static_cast<FAUSTFLOAT>(std::atan2(static_cast<double>(static_cast<int>(0.5 * static_cast<double>(input65[i]))), 4.0));
			}
			/* Vectorizable loop 46 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output44[i] = static_cast<FAUSTFLOAT>(std::atan2(static_cast<double>(static_cast<int>(0.5 * static_cast<double>(input66[i]))), 4.0));
			}
			/* Vectorizable loop 47 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output45[i] = static_cast<FAUSTFLOAT>(std::ceil(1.3 * static_cast<double>(input67[i])));
			}
			/* Vectorizable loop 48 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output46[i] = static_cast<FAUSTFLOAT>(std::cos(0.3 * static_cast<double>(input68[i])));
			}
			/* Vectorizable loop 49 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output47[i] = static_cast<FAUSTFLOAT>(std::exp(0.5 * static_cast<double>(input69[i])));
			}
			/* Vectorizable loop 50 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output48[i] = static_cast<FAUSTFLOAT>(std::floor(6.5 * static_cast<double>(input70[i])));
			}
			/* Vectorizable loop 51 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output49[i] = static_cast<FAUSTFLOAT>(std::fmod(9.2 * static_cast<double>(input71[i]), 2.0));
			}
			/* Vectorizable loop 52 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output50[i] = static_cast<FAUSTFLOAT>(std::log(0.5 * (static_cast<double>(input72[i]) + 1.0)));
			}
			/* Vectorizable loop 53 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output51[i] = static_cast<FAUSTFLOAT>(std::log10(0.5 * (static_cast<double>(input73[i]) + 1.0)));
			}
			/* Vectorizable loop 54 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output52[i] = static_cast<FAUSTFLOAT>(std::max<double>(0.5 * static_cast<double>(input74[i]), 0.4 * static_cast<double>(input75[i])));
			}
			/* Vectorizable loop 55 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output53[i] = static_cast<FAUSTFLOAT>(std::min<double>(0.5 * static_cast<double>(input76[i]), 0.4 * static_cast<double>(input77[i])));
			}
			/* Vectorizable loop 56 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output54[i] = static_cast<FAUSTFLOAT>(std::max<double>(0.5 * static_cast<double>(input78[i]), static_cast<double>(static_cast<int>(0.4 * static_cast<double>(input79[i])))));
			}
			/* Vectorizable loop 57 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output55[i] = static_cast<FAUSTFLOAT>(std::min<double>(0.5 * static_cast<double>(input80[i]), static_cast<double>(static_cast<int>(0.4 * static_cast<double>(input81[i])))));
			}
			/* Vectorizable loop 58 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output56[i] = static_cast<FAUSTFLOAT>(std::max<int>(static_cast<int>(3.5 * static_cast<double>(input82[i])), static_cast<int>(2.4 * static_cast<double>(input83[i]))));
			}
			/* Vectorizable loop 59 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output57[i] = static_cast<FAUSTFLOAT>(std::min<int>(static_cast<int>(3.5 * static_cast<double>(input84[i])), static_cast<int>(2.4 * static_cast<double>(input85[i]))));
			}
			/* Vectorizable loop 60 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output58[i] = static_cast<FAUSTFLOAT>(std::pow(0.5 * static_cast<double>(input86[i]), 0.3));
			}
			/* Vectorizable loop 61 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output59[i] = static_cast<FAUSTFLOAT>(std::pow(static_cast<double>(static_cast<int>(0.5 * static_cast<double>(input87[i]))), 0.3));
			}
			/* Vectorizable loop 62 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output60[i] = static_cast<FAUSTFLOAT>(mydsp_faustpower3_f(0.5 * static_cast<double>(input88[i])));
			}
			/* Vectorizable loop 63 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output61[i] = static_cast<FAUSTFLOAT>(mydsp_faustpower3_i(static_cast<int>(0.5 * static_cast<double>(input89[i]))));
			}
			/* Vectorizable loop 64 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output62[i] = static_cast<FAUSTFLOAT>(mydsp_faustpower3_i(static_cast<int>(0.5 * static_cast<double>(input90[i]))));
			}
			/* Vectorizable loop 65 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output63[i] = static_cast<FAUSTFLOAT>(std::pow(1e+01, 3.0 * static_cast<double>(input91[i])));
			}
			/* Vectorizable loop 66 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output64[i] = static_cast<FAUSTFLOAT>(std::remainder(9.2 * static_cast<double>(input92[i]), 2.0));
			}
			/* Vectorizable loop 67 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output65[i] = static_cast<FAUSTFLOAT>(std::rint(1.5 * static_cast<double>(input93[i])));
			}
			/* Vectorizable loop 68 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output66[i] = static_cast<FAUSTFLOAT>(std::round(1.5 * static_cast<double>(input94[i])));
			}
			/* Vectorizable loop 69 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output67[i] = static_cast<FAUSTFLOAT>(std::sin(0.3 * static_cast<double>(input95[i])));
			}
			/* Vectorizable loop 70 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output68[i] = static_cast<FAUSTFLOAT>(std::sqrt(0.3 * static_cast<double>(input96[i])));
			}
			/* Vectorizable loop 71 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output69[i] = static_cast<FAUSTFLOAT>(std::tan(0.3 * static_cast<double>(input97[i])));
			}
			/* Vectorizable loop 72 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output70[i] = static_cast<FAUSTFLOAT>(acosh(0.3 * static_cast<double>(input98[i]) + 1e+01));
			}
			/* Vectorizable loop 73 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output71[i] = static_cast<FAUSTFLOAT>(asinh(0.3 * static_cast<double>(input99[i]) + 1e+01));
			}
			/* Vectorizable loop 74 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output72[i] = static_cast<FAUSTFLOAT>(atanh(0.3 * static_cast<double>(input100[i]) + 0.5));
			}
			/* Vectorizable loop 75 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output73[i] = static_cast<FAUSTFLOAT>(cosh(0.3 * static_cast<double>(input101[i]) + 1e+01));
			}
			/* Vectorizable loop 76 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output74[i] = static_cast<FAUSTFLOAT>(sinh(0.3 * static_cast<double>(input102[i]) + 1e+01));
			}
			/* Vectorizable loop 77 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output75[i] = static_cast<FAUSTFLOAT>(tanh(0.3 * static_cast<double>(input103[i]) + 1e+01));
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
