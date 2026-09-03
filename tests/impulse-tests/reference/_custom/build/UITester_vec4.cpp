/* ------------------------------------------------------------
author: "O. Guillerminet"
copyright: "(c) O. Guillerminet 2012"
license: "BSD"
name: "UI Tester"
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
	
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT fEntry0;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT fVslider5;
	FAUSTFLOAT fVslider6;
	FAUSTFLOAT fButton0;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fVslider7;
	FAUSTFLOAT fVslider8;
	FAUSTFLOAT fVslider9;
	FAUSTFLOAT fEntry1;
	FAUSTFLOAT fVbargraph0;
	FAUSTFLOAT fVslider10;
	FAUSTFLOAT fVslider11;
	FAUSTFLOAT fVslider12;
	FAUSTFLOAT fEntry2;
	FAUSTFLOAT fVbargraph1;
	FAUSTFLOAT fVslider13;
	FAUSTFLOAT fVslider14;
	FAUSTFLOAT fVslider15;
	FAUSTFLOAT fEntry3;
	FAUSTFLOAT fVbargraph2;
	FAUSTFLOAT fHbargraph0;
	FAUSTFLOAT fVslider16;
	FAUSTFLOAT fButton1;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fEntry4;
	FAUSTFLOAT fVbargraph3;
	FAUSTFLOAT fHbargraph1;
	int fSampleRate;
	
 public:
	mydsp() {
	}
	
	mydsp(const mydsp&) = default;
	
	virtual ~mydsp() = default;
	
	mydsp& operator=(const mydsp&) = default;
	
	void metadata(Meta* m) { 
		m->declare("author", "O. Guillerminet");
		m->declare("compile_options", "-a /Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/archs/impulsearch.cpp -lang cpp -i -fpga-mem-th 4 -ct 1 -es 1 -mcd 4 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs");
		m->declare("copyright", "(c) O. Guillerminet 2012");
		m->declare("filename", "UITester.dsp");
		m->declare("license", "BSD");
		m->declare("name", "UI Tester");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() {
		return 6;
	}
	virtual int getNumOutputs() {
		return 34;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
	}
	
	virtual void instanceResetUserInterface() {
		fCheckbox0 = static_cast<FAUSTFLOAT>(0.0);
		fCheckbox1 = static_cast<FAUSTFLOAT>(0.0);
		fEntry0 = static_cast<FAUSTFLOAT>(6e+01);
		fVslider0 = static_cast<FAUSTFLOAT>(6e+01);
		fVslider1 = static_cast<FAUSTFLOAT>(6e+01);
		fVslider2 = static_cast<FAUSTFLOAT>(6e+01);
		fVslider3 = static_cast<FAUSTFLOAT>(6e+01);
		fVslider4 = static_cast<FAUSTFLOAT>(6e+01);
		fVslider5 = static_cast<FAUSTFLOAT>(6e+01);
		fVslider6 = static_cast<FAUSTFLOAT>(6e+01);
		fButton0 = static_cast<FAUSTFLOAT>(0.0);
		fHslider0 = static_cast<FAUSTFLOAT>(6e+01);
		fVslider7 = static_cast<FAUSTFLOAT>(6e+01);
		fVslider8 = static_cast<FAUSTFLOAT>(6e+01);
		fVslider9 = static_cast<FAUSTFLOAT>(6e+01);
		fEntry1 = static_cast<FAUSTFLOAT>(6e+01);
		fVslider10 = static_cast<FAUSTFLOAT>(6e+01);
		fVslider11 = static_cast<FAUSTFLOAT>(6e+01);
		fVslider12 = static_cast<FAUSTFLOAT>(6e+01);
		fEntry2 = static_cast<FAUSTFLOAT>(6e+01);
		fVslider13 = static_cast<FAUSTFLOAT>(6e+01);
		fVslider14 = static_cast<FAUSTFLOAT>(6e+01);
		fVslider15 = static_cast<FAUSTFLOAT>(6e+01);
		fEntry3 = static_cast<FAUSTFLOAT>(6e+01);
		fVslider16 = static_cast<FAUSTFLOAT>(6e+01);
		fButton1 = static_cast<FAUSTFLOAT>(0.0);
		fHslider1 = static_cast<FAUSTFLOAT>(6e+01);
		fEntry4 = static_cast<FAUSTFLOAT>(6e+01);
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
		ui_interface->openTabBox("grp 1");
		ui_interface->openHorizontalBox("hmisc");
		ui_interface->addButton("button", &fButton1);
		ui_interface->addHorizontalBargraph("hbar", &fHbargraph1, FAUSTFLOAT(0.0), FAUSTFLOAT(127.0));
		ui_interface->addHorizontalSlider("hslider", &fHslider1, FAUSTFLOAT(6e+01), FAUSTFLOAT(0.0), FAUSTFLOAT(127.0), FAUSTFLOAT(0.1));
		ui_interface->declare(&fEntry4, "unit", "f");
		ui_interface->addNumEntry("num", &fEntry4, FAUSTFLOAT(6e+01), FAUSTFLOAT(0.0), FAUSTFLOAT(127.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalBargraph("vbar", &fVbargraph3, FAUSTFLOAT(0.0), FAUSTFLOAT(127.0));
		ui_interface->declare(&fVslider16, "unit", "f");
		ui_interface->addVerticalSlider("vslider4", &fVslider16, FAUSTFLOAT(6e+01), FAUSTFLOAT(0.0), FAUSTFLOAT(127.0), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("knobs");
		ui_interface->declare(&fVslider3, "style", "knob");
		ui_interface->addVerticalSlider("knob1", &fVslider3, FAUSTFLOAT(6e+01), FAUSTFLOAT(0.0), FAUSTFLOAT(127.0), FAUSTFLOAT(0.1));
		ui_interface->declare(&fVslider4, "style", "knob");
		ui_interface->addVerticalSlider("knob2", &fVslider4, FAUSTFLOAT(6e+01), FAUSTFLOAT(0.0), FAUSTFLOAT(127.0), FAUSTFLOAT(0.1));
		ui_interface->declare(&fVslider5, "style", "knob");
		ui_interface->addVerticalSlider("knob3", &fVslider5, FAUSTFLOAT(6e+01), FAUSTFLOAT(0.0), FAUSTFLOAT(127.0), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("sliders");
		ui_interface->addVerticalSlider("vslider1", &fVslider0, FAUSTFLOAT(6e+01), FAUSTFLOAT(0.0), FAUSTFLOAT(127.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("vslider2", &fVslider1, FAUSTFLOAT(6e+01), FAUSTFLOAT(0.0), FAUSTFLOAT(127.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalSlider("vslider3", &fVslider2, FAUSTFLOAT(6e+01), FAUSTFLOAT(0.0), FAUSTFLOAT(127.0), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("vbox");
		ui_interface->addCheckButton("check1", &fCheckbox0);
		ui_interface->addCheckButton("check2", &fCheckbox1);
		ui_interface->declare(&fEntry0, "style", "knob");
		ui_interface->addNumEntry("knob0", &fEntry0, FAUSTFLOAT(6e+01), FAUSTFLOAT(0.0), FAUSTFLOAT(127.0), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("vmisc");
		ui_interface->addButton("button", &fButton0);
		ui_interface->addHorizontalBargraph("hbar", &fHbargraph0, FAUSTFLOAT(0.0), FAUSTFLOAT(127.0));
		ui_interface->declare(&fHslider0, "unit", "Hz");
		ui_interface->addHorizontalSlider("hslider", &fHslider0, FAUSTFLOAT(6e+01), FAUSTFLOAT(0.0), FAUSTFLOAT(127.0), FAUSTFLOAT(0.1));
		ui_interface->openHorizontalBox("small box 1");
		ui_interface->declare(&fVslider9, "style", "knob");
		ui_interface->addVerticalSlider("knob4", &fVslider9, FAUSTFLOAT(6e+01), FAUSTFLOAT(0.0), FAUSTFLOAT(127.0), FAUSTFLOAT(0.1));
		ui_interface->declare(&fEntry1, "unit", "f");
		ui_interface->addNumEntry("num1", &fEntry1, FAUSTFLOAT(6e+01), FAUSTFLOAT(0.0), FAUSTFLOAT(127.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalBargraph("vbar1", &fVbargraph0, FAUSTFLOAT(0.0), FAUSTFLOAT(127.0));
		ui_interface->declare(&fVslider7, "unit", "Hz");
		ui_interface->addVerticalSlider("vslider5", &fVslider7, FAUSTFLOAT(6e+01), FAUSTFLOAT(0.0), FAUSTFLOAT(127.0), FAUSTFLOAT(0.1));
		ui_interface->declare(&fVslider8, "unit", "Hz");
		ui_interface->addVerticalSlider("vslider6", &fVslider8, FAUSTFLOAT(6e+01), FAUSTFLOAT(0.0), FAUSTFLOAT(127.0), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("sub box 1");
		ui_interface->openHorizontalBox("small box 2");
		ui_interface->declare(&fVslider12, "style", "knob");
		ui_interface->addVerticalSlider("knob5", &fVslider12, FAUSTFLOAT(6e+01), FAUSTFLOAT(0.0), FAUSTFLOAT(127.0), FAUSTFLOAT(0.1));
		ui_interface->declare(&fEntry2, "unit", "f");
		ui_interface->addNumEntry("num2", &fEntry2, FAUSTFLOAT(6e+01), FAUSTFLOAT(0.0), FAUSTFLOAT(127.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalBargraph("vbar2", &fVbargraph1, FAUSTFLOAT(0.0), FAUSTFLOAT(127.0));
		ui_interface->declare(&fVslider10, "unit", "Hz");
		ui_interface->addVerticalSlider("vslider7", &fVslider10, FAUSTFLOAT(6e+01), FAUSTFLOAT(0.0), FAUSTFLOAT(127.0), FAUSTFLOAT(0.1));
		ui_interface->declare(&fVslider11, "unit", "Hz");
		ui_interface->addVerticalSlider("vslider8", &fVslider11, FAUSTFLOAT(6e+01), FAUSTFLOAT(0.0), FAUSTFLOAT(127.0), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("small box 3");
		ui_interface->declare(&fVslider15, "style", "knob");
		ui_interface->addVerticalSlider("knob6", &fVslider15, FAUSTFLOAT(6e+01), FAUSTFLOAT(0.0), FAUSTFLOAT(127.0), FAUSTFLOAT(0.1));
		ui_interface->declare(&fEntry3, "unit", "f");
		ui_interface->addNumEntry("num3", &fEntry3, FAUSTFLOAT(6e+01), FAUSTFLOAT(0.0), FAUSTFLOAT(127.0), FAUSTFLOAT(0.1));
		ui_interface->addVerticalBargraph("vbar3", &fVbargraph2, FAUSTFLOAT(0.0), FAUSTFLOAT(127.0));
		ui_interface->declare(&fVslider14, "unit", "m");
		ui_interface->addVerticalSlider("vslider10", &fVslider14, FAUSTFLOAT(6e+01), FAUSTFLOAT(0.0), FAUSTFLOAT(127.0), FAUSTFLOAT(0.1));
		ui_interface->declare(&fVslider13, "unit", "Hz");
		ui_interface->addVerticalSlider("vslider9", &fVslider13, FAUSTFLOAT(6e+01), FAUSTFLOAT(0.0), FAUSTFLOAT(127.0), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(&fVslider6, "unit", "Hz");
		ui_interface->addVerticalSlider("vslider4", &fVslider6, FAUSTFLOAT(6e+01), FAUSTFLOAT(0.0), FAUSTFLOAT(127.0), FAUSTFLOAT(0.1));
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
		double fSlow0 = static_cast<double>(fCheckbox0);
		double fSlow1 = static_cast<double>(fCheckbox1);
		double fSlow2 = static_cast<double>(fEntry0);
		double fSlow3 = static_cast<double>(fVslider0);
		double fSlow4 = static_cast<double>(fVslider1);
		double fSlow5 = static_cast<double>(fVslider2);
		double fSlow6 = static_cast<double>(fVslider3);
		double fSlow7 = static_cast<double>(fVslider4);
		double fSlow8 = static_cast<double>(fVslider5);
		double fSlow9 = static_cast<double>(fVslider6);
		double fSlow10 = static_cast<double>(fButton0);
		double fSlow11 = static_cast<double>(fHslider0);
		double fSlow12 = static_cast<double>(fVslider7);
		double fSlow13 = static_cast<double>(fVslider8);
		double fSlow14 = static_cast<double>(fVslider9);
		double fSlow15 = static_cast<double>(fEntry1);
		double fSlow16 = static_cast<double>(fVslider10);
		double fSlow17 = static_cast<double>(fVslider11);
		double fSlow18 = static_cast<double>(fVslider12);
		double fSlow19 = static_cast<double>(fEntry2);
		double fSlow20 = static_cast<double>(fVslider13);
		double fSlow21 = static_cast<double>(fVslider14);
		double fSlow22 = static_cast<double>(fVslider15);
		double fSlow23 = static_cast<double>(fEntry3);
		double fSlow24 = static_cast<double>(fVslider16);
		double fSlow25 = static_cast<double>(fButton1);
		double fSlow26 = static_cast<double>(fHslider1);
		double fSlow27 = static_cast<double>(fEntry4);
		int vindex = 0;
		/* Main loop */
		for (vindex = 0; vindex <= (faust_wrap_sub(count, 4)); vindex = faust_wrap_add(vindex, 4)) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* input1 = &input1_ptr[vindex];
			FAUSTFLOAT* input2 = &input2_ptr[vindex];
			FAUSTFLOAT* input3 = &input3_ptr[vindex];
			FAUSTFLOAT* input4 = &input4_ptr[vindex];
			FAUSTFLOAT* input5 = &input5_ptr[vindex];
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
				output3[i] = static_cast<FAUSTFLOAT>(fSlow3);
			}
			/* Vectorizable loop 4 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output4[i] = static_cast<FAUSTFLOAT>(fSlow4);
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output5[i] = static_cast<FAUSTFLOAT>(fSlow5);
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output6[i] = static_cast<FAUSTFLOAT>(fSlow6);
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output7[i] = static_cast<FAUSTFLOAT>(fSlow7);
			}
			/* Vectorizable loop 8 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output8[i] = static_cast<FAUSTFLOAT>(fSlow8);
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output9[i] = static_cast<FAUSTFLOAT>(fSlow9);
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output10[i] = static_cast<FAUSTFLOAT>(fSlow10);
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output11[i] = static_cast<FAUSTFLOAT>(fSlow11);
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output12[i] = static_cast<FAUSTFLOAT>(fSlow12);
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output13[i] = static_cast<FAUSTFLOAT>(fSlow13);
			}
			/* Vectorizable loop 14 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output14[i] = static_cast<FAUSTFLOAT>(fSlow14);
			}
			/* Vectorizable loop 15 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output15[i] = static_cast<FAUSTFLOAT>(fSlow15);
			}
			/* Vectorizable loop 16 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph0 = static_cast<FAUSTFLOAT>(static_cast<double>(input0[i]));
				output16[i] = static_cast<FAUSTFLOAT>(static_cast<double>(fVbargraph0));
			}
			/* Vectorizable loop 17 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output17[i] = static_cast<FAUSTFLOAT>(fSlow16);
			}
			/* Vectorizable loop 18 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output18[i] = static_cast<FAUSTFLOAT>(fSlow17);
			}
			/* Vectorizable loop 19 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output19[i] = static_cast<FAUSTFLOAT>(fSlow18);
			}
			/* Vectorizable loop 20 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output20[i] = static_cast<FAUSTFLOAT>(fSlow19);
			}
			/* Vectorizable loop 21 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph1 = static_cast<FAUSTFLOAT>(static_cast<double>(input1[i]));
				output21[i] = static_cast<FAUSTFLOAT>(static_cast<double>(fVbargraph1));
			}
			/* Vectorizable loop 22 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output22[i] = static_cast<FAUSTFLOAT>(fSlow20);
			}
			/* Vectorizable loop 23 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output23[i] = static_cast<FAUSTFLOAT>(fSlow21);
			}
			/* Vectorizable loop 24 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output24[i] = static_cast<FAUSTFLOAT>(fSlow22);
			}
			/* Vectorizable loop 25 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output25[i] = static_cast<FAUSTFLOAT>(fSlow23);
			}
			/* Vectorizable loop 26 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph2 = static_cast<FAUSTFLOAT>(static_cast<double>(input2[i]));
				output26[i] = static_cast<FAUSTFLOAT>(static_cast<double>(fVbargraph2));
			}
			/* Vectorizable loop 27 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fHbargraph0 = static_cast<FAUSTFLOAT>(static_cast<double>(input3[i]));
				output27[i] = static_cast<FAUSTFLOAT>(static_cast<double>(fHbargraph0));
			}
			/* Vectorizable loop 28 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output28[i] = static_cast<FAUSTFLOAT>(fSlow24);
			}
			/* Vectorizable loop 29 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output29[i] = static_cast<FAUSTFLOAT>(fSlow25);
			}
			/* Vectorizable loop 30 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output30[i] = static_cast<FAUSTFLOAT>(fSlow26);
			}
			/* Vectorizable loop 31 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output31[i] = static_cast<FAUSTFLOAT>(fSlow27);
			}
			/* Vectorizable loop 32 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph3 = static_cast<FAUSTFLOAT>(static_cast<double>(input4[i]));
				output32[i] = static_cast<FAUSTFLOAT>(static_cast<double>(fVbargraph3));
			}
			/* Vectorizable loop 33 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fHbargraph1 = static_cast<FAUSTFLOAT>(static_cast<double>(input5[i]));
				output33[i] = static_cast<FAUSTFLOAT>(static_cast<double>(fHbargraph1));
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
				output3[i] = static_cast<FAUSTFLOAT>(fSlow3);
			}
			/* Vectorizable loop 4 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output4[i] = static_cast<FAUSTFLOAT>(fSlow4);
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output5[i] = static_cast<FAUSTFLOAT>(fSlow5);
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output6[i] = static_cast<FAUSTFLOAT>(fSlow6);
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output7[i] = static_cast<FAUSTFLOAT>(fSlow7);
			}
			/* Vectorizable loop 8 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output8[i] = static_cast<FAUSTFLOAT>(fSlow8);
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output9[i] = static_cast<FAUSTFLOAT>(fSlow9);
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output10[i] = static_cast<FAUSTFLOAT>(fSlow10);
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output11[i] = static_cast<FAUSTFLOAT>(fSlow11);
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output12[i] = static_cast<FAUSTFLOAT>(fSlow12);
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output13[i] = static_cast<FAUSTFLOAT>(fSlow13);
			}
			/* Vectorizable loop 14 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output14[i] = static_cast<FAUSTFLOAT>(fSlow14);
			}
			/* Vectorizable loop 15 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output15[i] = static_cast<FAUSTFLOAT>(fSlow15);
			}
			/* Vectorizable loop 16 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph0 = static_cast<FAUSTFLOAT>(static_cast<double>(input0[i]));
				output16[i] = static_cast<FAUSTFLOAT>(static_cast<double>(fVbargraph0));
			}
			/* Vectorizable loop 17 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output17[i] = static_cast<FAUSTFLOAT>(fSlow16);
			}
			/* Vectorizable loop 18 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output18[i] = static_cast<FAUSTFLOAT>(fSlow17);
			}
			/* Vectorizable loop 19 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output19[i] = static_cast<FAUSTFLOAT>(fSlow18);
			}
			/* Vectorizable loop 20 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output20[i] = static_cast<FAUSTFLOAT>(fSlow19);
			}
			/* Vectorizable loop 21 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph1 = static_cast<FAUSTFLOAT>(static_cast<double>(input1[i]));
				output21[i] = static_cast<FAUSTFLOAT>(static_cast<double>(fVbargraph1));
			}
			/* Vectorizable loop 22 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output22[i] = static_cast<FAUSTFLOAT>(fSlow20);
			}
			/* Vectorizable loop 23 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output23[i] = static_cast<FAUSTFLOAT>(fSlow21);
			}
			/* Vectorizable loop 24 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output24[i] = static_cast<FAUSTFLOAT>(fSlow22);
			}
			/* Vectorizable loop 25 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output25[i] = static_cast<FAUSTFLOAT>(fSlow23);
			}
			/* Vectorizable loop 26 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph2 = static_cast<FAUSTFLOAT>(static_cast<double>(input2[i]));
				output26[i] = static_cast<FAUSTFLOAT>(static_cast<double>(fVbargraph2));
			}
			/* Vectorizable loop 27 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fHbargraph0 = static_cast<FAUSTFLOAT>(static_cast<double>(input3[i]));
				output27[i] = static_cast<FAUSTFLOAT>(static_cast<double>(fHbargraph0));
			}
			/* Vectorizable loop 28 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output28[i] = static_cast<FAUSTFLOAT>(fSlow24);
			}
			/* Vectorizable loop 29 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output29[i] = static_cast<FAUSTFLOAT>(fSlow25);
			}
			/* Vectorizable loop 30 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output30[i] = static_cast<FAUSTFLOAT>(fSlow26);
			}
			/* Vectorizable loop 31 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output31[i] = static_cast<FAUSTFLOAT>(fSlow27);
			}
			/* Vectorizable loop 32 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph3 = static_cast<FAUSTFLOAT>(static_cast<double>(input4[i]));
				output32[i] = static_cast<FAUSTFLOAT>(static_cast<double>(fVbargraph3));
			}
			/* Vectorizable loop 33 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fHbargraph1 = static_cast<FAUSTFLOAT>(static_cast<double>(input5[i]));
				output33[i] = static_cast<FAUSTFLOAT>(static_cast<double>(fHbargraph1));
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
