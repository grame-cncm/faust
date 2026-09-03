/* ------------------------------------------------------------
name: "norm1"
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
static double mydsp_faustpower3_f(double value) {
	return value * value * value;
}
static double mydsp_faustpower5_f(double value) {
	return value * value * value * value * value;
}

class mydsp : public dsp {
	
 private:
	
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT fHslider5;
	FAUSTFLOAT fHslider6;
	FAUSTFLOAT fHslider7;
	FAUSTFLOAT fHslider8;
	FAUSTFLOAT fHslider9;
	FAUSTFLOAT fHslider10;
	FAUSTFLOAT fHslider11;
	FAUSTFLOAT fHslider12;
	FAUSTFLOAT fHslider13;
	FAUSTFLOAT fHslider14;
	FAUSTFLOAT fHslider15;
	FAUSTFLOAT fHslider16;
	FAUSTFLOAT fHslider17;
	FAUSTFLOAT fHslider18;
	FAUSTFLOAT fHslider19;
	FAUSTFLOAT fHslider20;
	FAUSTFLOAT fHslider21;
	FAUSTFLOAT fHslider22;
	FAUSTFLOAT fHslider23;
	FAUSTFLOAT fHslider24;
	FAUSTFLOAT fHslider25;
	FAUSTFLOAT fHslider26;
	FAUSTFLOAT fHslider27;
	FAUSTFLOAT fHslider28;
	FAUSTFLOAT fHslider29;
	FAUSTFLOAT fHslider30;
	FAUSTFLOAT fHslider31;
	FAUSTFLOAT fHslider32;
	FAUSTFLOAT fHslider33;
	FAUSTFLOAT fHslider34;
	FAUSTFLOAT fHslider35;
	FAUSTFLOAT fHslider36;
	FAUSTFLOAT fHslider37;
	FAUSTFLOAT fHslider38;
	FAUSTFLOAT fHslider39;
	FAUSTFLOAT fHslider40;
	FAUSTFLOAT fHslider41;
	FAUSTFLOAT fHslider42;
	FAUSTFLOAT fHslider43;
	FAUSTFLOAT fHslider44;
	FAUSTFLOAT fHslider45;
	FAUSTFLOAT fHslider46;
	FAUSTFLOAT fHslider47;
	FAUSTFLOAT fHslider48;
	FAUSTFLOAT fHslider49;
	FAUSTFLOAT fHslider50;
	FAUSTFLOAT fHslider51;
	FAUSTFLOAT fHslider52;
	int fSampleRate;
	
 public:
	mydsp() {
	}
	
	mydsp(const mydsp&) = default;
	
	virtual ~mydsp() = default;
	
	mydsp& operator=(const mydsp&) = default;
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-a /Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/archs/impulsearch.cpp -lang cpp -i -fpga-mem-th 4 -ct 1 -es 1 -mcd 4 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs");
		m->declare("filename", "norm1.dsp");
		m->declare("name", "norm1");
	}

	virtual int getNumInputs() {
		return 0;
	}
	virtual int getNumOutputs() {
		return 35;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(0.0);
		fHslider1 = static_cast<FAUSTFLOAT>(0.0);
		fHslider2 = static_cast<FAUSTFLOAT>(0.0);
		fHslider3 = static_cast<FAUSTFLOAT>(0.0);
		fHslider4 = static_cast<FAUSTFLOAT>(0.0);
		fHslider5 = static_cast<FAUSTFLOAT>(0.0);
		fHslider6 = static_cast<FAUSTFLOAT>(0.0);
		fHslider7 = static_cast<FAUSTFLOAT>(0.0);
		fHslider8 = static_cast<FAUSTFLOAT>(0.0);
		fHslider9 = static_cast<FAUSTFLOAT>(0.0);
		fHslider10 = static_cast<FAUSTFLOAT>(0.0);
		fHslider11 = static_cast<FAUSTFLOAT>(0.0);
		fHslider12 = static_cast<FAUSTFLOAT>(0.0);
		fHslider13 = static_cast<FAUSTFLOAT>(0.0);
		fHslider14 = static_cast<FAUSTFLOAT>(0.0);
		fHslider15 = static_cast<FAUSTFLOAT>(0.0);
		fHslider16 = static_cast<FAUSTFLOAT>(0.0);
		fHslider17 = static_cast<FAUSTFLOAT>(0.0);
		fHslider18 = static_cast<FAUSTFLOAT>(0.0);
		fHslider19 = static_cast<FAUSTFLOAT>(0.0);
		fHslider20 = static_cast<FAUSTFLOAT>(0.0);
		fHslider21 = static_cast<FAUSTFLOAT>(0.0);
		fHslider22 = static_cast<FAUSTFLOAT>(0.0);
		fHslider23 = static_cast<FAUSTFLOAT>(0.0);
		fHslider24 = static_cast<FAUSTFLOAT>(0.0);
		fHslider25 = static_cast<FAUSTFLOAT>(0.0);
		fHslider26 = static_cast<FAUSTFLOAT>(0.0);
		fHslider27 = static_cast<FAUSTFLOAT>(0.0);
		fHslider28 = static_cast<FAUSTFLOAT>(0.0);
		fHslider29 = static_cast<FAUSTFLOAT>(0.0);
		fHslider30 = static_cast<FAUSTFLOAT>(0.0);
		fHslider31 = static_cast<FAUSTFLOAT>(0.0);
		fHslider32 = static_cast<FAUSTFLOAT>(0.0);
		fHslider33 = static_cast<FAUSTFLOAT>(0.0);
		fHslider34 = static_cast<FAUSTFLOAT>(0.0);
		fHslider35 = static_cast<FAUSTFLOAT>(0.0);
		fHslider36 = static_cast<FAUSTFLOAT>(0.0);
		fHslider37 = static_cast<FAUSTFLOAT>(0.0);
		fHslider38 = static_cast<FAUSTFLOAT>(0.0);
		fHslider39 = static_cast<FAUSTFLOAT>(1.0);
		fHslider40 = static_cast<FAUSTFLOAT>(1.0);
		fHslider41 = static_cast<FAUSTFLOAT>(0.0);
		fHslider42 = static_cast<FAUSTFLOAT>(0.0);
		fHslider43 = static_cast<FAUSTFLOAT>(0.0);
		fHslider44 = static_cast<FAUSTFLOAT>(0.0);
		fHslider45 = static_cast<FAUSTFLOAT>(0.0);
		fHslider46 = static_cast<FAUSTFLOAT>(0.0);
		fHslider47 = static_cast<FAUSTFLOAT>(0.0);
		fHslider48 = static_cast<FAUSTFLOAT>(0.0);
		fHslider49 = static_cast<FAUSTFLOAT>(0.0);
		fHslider50 = static_cast<FAUSTFLOAT>(0.0);
		fHslider51 = static_cast<FAUSTFLOAT>(0.0);
		fHslider52 = static_cast<FAUSTFLOAT>(0.0);
	}
	
	virtual void instanceClear() {
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
		ui_interface->openVerticalBox("norm1");
		ui_interface->addHorizontalSlider("1.1_x", &fHslider0, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("1.2_x", &fHslider2, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("1.2_y", &fHslider1, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("1.3_x", &fHslider3, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("1.4_x", &fHslider4, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("1.5_y", &fHslider5, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("1.6_x", &fHslider6, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("2.1_x", &fHslider7, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("2.1_y", &fHslider8, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("2.2_x", &fHslider9, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("2.2_y", &fHslider10, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("2.3_x", &fHslider11, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("2.3_y", &fHslider12, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("2.3_z", &fHslider13, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("2.4_x", &fHslider15, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("2.4_y", &fHslider16, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("2.4_z", &fHslider14, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("2.5_x", &fHslider18, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("2.5_y", &fHslider17, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("3.1_x", &fHslider19, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("3.2_x", &fHslider20, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("3.3_x", &fHslider21, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("3.6_z", &fHslider22, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("3.7_y", &fHslider23, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("4.1_x", &fHslider24, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("4.1_y", &fHslider25, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("4.2_x", &fHslider26, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("4.2_y", &fHslider28, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("4.2_z", &fHslider27, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("4.3_x", &fHslider29, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("4.3_y", &fHslider30, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("4.3_z", &fHslider31, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("4.4_y", &fHslider32, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("4.5_x", &fHslider33, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("4.5_y", &fHslider34, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("5.1_x", &fHslider35, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("5.2_x", &fHslider36, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("5.3_x", &fHslider37, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("5.3_y", &fHslider38, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("5.4_x", &fHslider39, FAUSTFLOAT(1.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("5.5_x", &fHslider40, FAUSTFLOAT(1.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("6.1_x", &fHslider41, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("6.1_y", &fHslider42, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("6.1_z", &fHslider43, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("6.2_x", &fHslider44, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("6.2_y", &fHslider45, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("6.3_x", &fHslider46, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("6.3_y", &fHslider47, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("6.4_x", &fHslider48, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("6.5_a", &fHslider51, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("6.5_b", &fHslider52, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("6.5_x", &fHslider49, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("6.5_y", &fHslider50, FAUSTFLOAT(0.0), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
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
		double fSlow0 = 2.0 * static_cast<double>(fHslider0);
		double fSlow1 = static_cast<double>(fHslider1) + 2.0 * static_cast<double>(fHslider2);
		double fSlow2 = 3.0 * static_cast<double>(fHslider3);
		double fSlow3 = static_cast<double>(fHslider5);
		double fSlow4 = 3.7 * static_cast<double>(fHslider6);
		double fSlow5 = static_cast<double>(fHslider7) + static_cast<double>(fHslider8);
		double fSlow6 = static_cast<double>(fHslider9) * static_cast<double>(fHslider10);
		double fSlow7 = static_cast<double>(fHslider11) + static_cast<double>(fHslider12) + static_cast<double>(fHslider13);
		double fSlow8 = static_cast<double>(fHslider14) + static_cast<double>(fHslider15) + static_cast<double>(fHslider16);
		double fSlow9 = 2.0 * (static_cast<double>(fHslider17) + static_cast<double>(fHslider18));
		double fSlow10 = static_cast<double>(fHslider19);
		double fSlow11 = static_cast<double>(fHslider20);
		double fSlow12 = static_cast<double>(fHslider21);
		double fSlow13 = static_cast<double>(fHslider22);
		double fSlow14 = static_cast<double>(fHslider23);
		double fSlow15 = 2.0 * (static_cast<double>(fHslider24) + static_cast<double>(fHslider25));
		double fSlow16 = static_cast<double>(fHslider26) + static_cast<double>(fHslider27) - static_cast<double>(fHslider28);
		double fSlow17 = mydsp_faustpower2_f(static_cast<double>(fHslider29)) * static_cast<double>(fHslider30) * static_cast<double>(fHslider31);
		double fSlow18 = static_cast<double>(fHslider32);
		double fSlow19 = 0.5 * (static_cast<double>(fHslider33) + static_cast<double>(fHslider34));
		double fSlow20 = mydsp_faustpower2_f(static_cast<double>(fHslider35));
		double fSlow21 = mydsp_faustpower2_f(static_cast<double>(fHslider36));
		double fSlow22 = mydsp_faustpower2_f(static_cast<double>(fHslider37)) * mydsp_faustpower3_f(static_cast<double>(fHslider38));
		double fSlow23 = static_cast<double>(fHslider39);
		double fSlow24 = mydsp_faustpower5_f(fSlow23) / mydsp_faustpower3_f(fSlow23);
		double fSlow25 = mydsp_faustpower2_f(static_cast<double>(fHslider40));
		double fSlow26 = fSlow25 / fSlow25;
		double fSlow27 = static_cast<double>(fHslider41) * (static_cast<double>(fHslider42) + static_cast<double>(fHslider43));
		double fSlow28 = 4.0 * static_cast<double>(fHslider44) + 2.0 * static_cast<double>(fHslider45);
		double fSlow29 = static_cast<double>(fHslider46);
		double fSlow30 = static_cast<double>(fHslider47);
		double fSlow31 = fSlow29 * fSlow30 * (fSlow29 + fSlow30);
		double fSlow32 = static_cast<double>(fHslider48);
		double fSlow33 = fSlow32 * (3.0 * fSlow32 + -6.0);
		double fSlow34 = (static_cast<double>(fHslider49) + static_cast<double>(fHslider50)) * (static_cast<double>(fHslider51) + static_cast<double>(fHslider52));
		int vindex = 0;
		/* Main loop */
		for (vindex = 0; vindex <= (faust_wrap_sub(count, 4)); vindex = faust_wrap_add(vindex, 4)) {
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
			int vsize = 4;
			/* Vectorizable loop 0 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fSlow0);
			}
			/* Vectorizable loop 1 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fSlow1);
			}
			/* Vectorizable loop 2 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output2[i] = static_cast<FAUSTFLOAT>(fSlow2);
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output3[i] = static_cast<FAUSTFLOAT>(-(3.0 * static_cast<double>(fHslider4)));
			}
			/* Vectorizable loop 4 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output4[i] = static_cast<FAUSTFLOAT>(fSlow3);
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output5[i] = static_cast<FAUSTFLOAT>(fSlow4);
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output6[i] = static_cast<FAUSTFLOAT>(fSlow5);
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output7[i] = static_cast<FAUSTFLOAT>(fSlow5);
			}
			/* Vectorizable loop 8 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output8[i] = static_cast<FAUSTFLOAT>(fSlow6);
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output9[i] = static_cast<FAUSTFLOAT>(fSlow6);
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output10[i] = static_cast<FAUSTFLOAT>(fSlow7);
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output11[i] = static_cast<FAUSTFLOAT>(fSlow8);
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output12[i] = static_cast<FAUSTFLOAT>(fSlow9);
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output13[i] = static_cast<FAUSTFLOAT>(fSlow10);
			}
			/* Vectorizable loop 14 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output14[i] = static_cast<FAUSTFLOAT>(fSlow11);
			}
			/* Vectorizable loop 15 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output15[i] = static_cast<FAUSTFLOAT>(fSlow12);
			}
			/* Vectorizable loop 16 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output16[i] = static_cast<FAUSTFLOAT>(0.0);
			}
			/* Vectorizable loop 17 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output17[i] = static_cast<FAUSTFLOAT>(0);
			}
			/* Vectorizable loop 18 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output18[i] = static_cast<FAUSTFLOAT>(fSlow13);
			}
			/* Vectorizable loop 19 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output19[i] = static_cast<FAUSTFLOAT>(fSlow14);
			}
			/* Vectorizable loop 20 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output20[i] = static_cast<FAUSTFLOAT>(fSlow15);
			}
			/* Vectorizable loop 21 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output21[i] = static_cast<FAUSTFLOAT>(fSlow16);
			}
			/* Vectorizable loop 22 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output22[i] = static_cast<FAUSTFLOAT>(fSlow17);
			}
			/* Vectorizable loop 23 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output23[i] = static_cast<FAUSTFLOAT>(fSlow18);
			}
			/* Vectorizable loop 24 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output24[i] = static_cast<FAUSTFLOAT>(fSlow19);
			}
			/* Vectorizable loop 25 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output25[i] = static_cast<FAUSTFLOAT>(fSlow20);
			}
			/* Vectorizable loop 26 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output26[i] = static_cast<FAUSTFLOAT>(fSlow21);
			}
			/* Vectorizable loop 27 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output27[i] = static_cast<FAUSTFLOAT>(fSlow22);
			}
			/* Vectorizable loop 28 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output28[i] = static_cast<FAUSTFLOAT>(fSlow24);
			}
			/* Vectorizable loop 29 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output29[i] = static_cast<FAUSTFLOAT>(fSlow26);
			}
			/* Vectorizable loop 30 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output30[i] = static_cast<FAUSTFLOAT>(fSlow27);
			}
			/* Vectorizable loop 31 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output31[i] = static_cast<FAUSTFLOAT>(fSlow28);
			}
			/* Vectorizable loop 32 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output32[i] = static_cast<FAUSTFLOAT>(fSlow31);
			}
			/* Vectorizable loop 33 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output33[i] = static_cast<FAUSTFLOAT>(fSlow33);
			}
			/* Vectorizable loop 34 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output34[i] = static_cast<FAUSTFLOAT>(fSlow34);
			}
		}
		/* Remaining frames */
		if (vindex < count) {
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
			int vsize = faust_wrap_sub(count, vindex);
			/* Vectorizable loop 0 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fSlow0);
			}
			/* Vectorizable loop 1 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fSlow1);
			}
			/* Vectorizable loop 2 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output2[i] = static_cast<FAUSTFLOAT>(fSlow2);
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output3[i] = static_cast<FAUSTFLOAT>(-(3.0 * static_cast<double>(fHslider4)));
			}
			/* Vectorizable loop 4 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output4[i] = static_cast<FAUSTFLOAT>(fSlow3);
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output5[i] = static_cast<FAUSTFLOAT>(fSlow4);
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output6[i] = static_cast<FAUSTFLOAT>(fSlow5);
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output7[i] = static_cast<FAUSTFLOAT>(fSlow5);
			}
			/* Vectorizable loop 8 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output8[i] = static_cast<FAUSTFLOAT>(fSlow6);
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output9[i] = static_cast<FAUSTFLOAT>(fSlow6);
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output10[i] = static_cast<FAUSTFLOAT>(fSlow7);
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output11[i] = static_cast<FAUSTFLOAT>(fSlow8);
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output12[i] = static_cast<FAUSTFLOAT>(fSlow9);
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output13[i] = static_cast<FAUSTFLOAT>(fSlow10);
			}
			/* Vectorizable loop 14 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output14[i] = static_cast<FAUSTFLOAT>(fSlow11);
			}
			/* Vectorizable loop 15 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output15[i] = static_cast<FAUSTFLOAT>(fSlow12);
			}
			/* Vectorizable loop 16 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output16[i] = static_cast<FAUSTFLOAT>(0.0);
			}
			/* Vectorizable loop 17 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output17[i] = static_cast<FAUSTFLOAT>(0);
			}
			/* Vectorizable loop 18 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output18[i] = static_cast<FAUSTFLOAT>(fSlow13);
			}
			/* Vectorizable loop 19 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output19[i] = static_cast<FAUSTFLOAT>(fSlow14);
			}
			/* Vectorizable loop 20 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output20[i] = static_cast<FAUSTFLOAT>(fSlow15);
			}
			/* Vectorizable loop 21 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output21[i] = static_cast<FAUSTFLOAT>(fSlow16);
			}
			/* Vectorizable loop 22 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output22[i] = static_cast<FAUSTFLOAT>(fSlow17);
			}
			/* Vectorizable loop 23 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output23[i] = static_cast<FAUSTFLOAT>(fSlow18);
			}
			/* Vectorizable loop 24 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output24[i] = static_cast<FAUSTFLOAT>(fSlow19);
			}
			/* Vectorizable loop 25 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output25[i] = static_cast<FAUSTFLOAT>(fSlow20);
			}
			/* Vectorizable loop 26 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output26[i] = static_cast<FAUSTFLOAT>(fSlow21);
			}
			/* Vectorizable loop 27 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output27[i] = static_cast<FAUSTFLOAT>(fSlow22);
			}
			/* Vectorizable loop 28 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output28[i] = static_cast<FAUSTFLOAT>(fSlow24);
			}
			/* Vectorizable loop 29 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output29[i] = static_cast<FAUSTFLOAT>(fSlow26);
			}
			/* Vectorizable loop 30 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output30[i] = static_cast<FAUSTFLOAT>(fSlow27);
			}
			/* Vectorizable loop 31 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output31[i] = static_cast<FAUSTFLOAT>(fSlow28);
			}
			/* Vectorizable loop 32 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output32[i] = static_cast<FAUSTFLOAT>(fSlow31);
			}
			/* Vectorizable loop 33 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output33[i] = static_cast<FAUSTFLOAT>(fSlow33);
			}
			/* Vectorizable loop 34 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output34[i] = static_cast<FAUSTFLOAT>(fSlow34);
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
