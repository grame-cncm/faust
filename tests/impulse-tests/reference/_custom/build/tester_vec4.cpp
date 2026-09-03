/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2006"
license: "BSD"
name: "tester"
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

class mydspSIG0 {
	
  private:
	
	int iRec4[2];
	int fSampleRate;
	
  public:
	
	int getNumInputsmydspSIG0() {
		return 0;
	}
	int getNumOutputsmydspSIG0() {
		return 1;
	}
	
	void instanceInitmydspSIG0(int sample_rate) {
		fSampleRate = sample_rate;
		for (int l5 = 0; l5 < 2; l5 = faust_wrap_add(l5, 1)) {
			iRec4[l5] = 0;
		}
	}
	
	void fillmydspSIG0(int count, double* table) {
		for (int i1 = 0; i1 < count; i1 = faust_wrap_add(i1, 1)) {
			iRec4[0] = faust_wrap_add(iRec4[1], 1);
			table[i1] = std::sin(9.587379924285257e-05 * static_cast<double>(faust_wrap_add(iRec4[0], -1)));
			iRec4[1] = iRec4[0];
		}
	}

};

static mydspSIG0* newmydspSIG0() { return (mydspSIG0*)new mydspSIG0(); }
static void deletemydspSIG0(mydspSIG0* dsp) { delete dsp; }

static double ftbl0mydspSIG0[65537];

class mydsp : public dsp {
	
 private:
	
	FAUSTFLOAT fHslider0;
	double fRec0_perm[4];
	int fSampleRate;
	double fConst0;
	FAUSTFLOAT fHslider1;
	double fRec1_perm[4];
	int iRec2_perm[4];
	double fYec0_perm[4];
	double fRec3_perm[4];
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fCheckbox1;
	
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
		m->declare("filename", "tester.dsp");
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
		m->declare("name", "tester");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() {
		return 0;
	}
	virtual int getNumOutputs() {
		return 8;
	}
	
	static void classInit(int sample_rate) {
		mydspSIG0* sig0 = newmydspSIG0();
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(65537, ftbl0mydspSIG0);
		deletemydspSIG0(sig0);
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = 1.0 / std::min<double>(1.92e+05, std::max<double>(1.0, static_cast<double>(fSampleRate)));
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(-24.9984);
		fHslider1 = static_cast<FAUSTFLOAT>(1e+03);
		fHslider2 = static_cast<FAUSTFLOAT>(0.0);
		fCheckbox0 = static_cast<FAUSTFLOAT>(0.0);
		fCheckbox1 = static_cast<FAUSTFLOAT>(0.0);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 4; l0 = faust_wrap_add(l0, 1)) {
			fRec0_perm[l0] = 0.0;
		}
		for (int l1 = 0; l1 < 4; l1 = faust_wrap_add(l1, 1)) {
			fRec1_perm[l1] = 0.0;
		}
		for (int l2 = 0; l2 < 4; l2 = faust_wrap_add(l2, 1)) {
			iRec2_perm[l2] = 0;
		}
		for (int l3 = 0; l3 < 4; l3 = faust_wrap_add(l3, 1)) {
			fYec0_perm[l3] = 0.0;
		}
		for (int l4 = 0; l4 < 4; l4 = faust_wrap_add(l4, 1)) {
			fRec3_perm[l4] = 0.0;
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
		ui_interface->openVerticalBox("Audio Tester");
		ui_interface->declare(&fHslider1, "1", "");
		ui_interface->declare(&fHslider1, "unit", "Hz");
		ui_interface->addHorizontalSlider("freq", &fHslider1, FAUSTFLOAT(1e+03), FAUSTFLOAT(1e+01), FAUSTFLOAT(2e+04), FAUSTFLOAT(1.0));
		ui_interface->declare(&fHslider0, "2", "");
		ui_interface->declare(&fHslider0, "unit", "dB");
		ui_interface->addHorizontalSlider("volume", &fHslider0, FAUSTFLOAT(-24.9984), FAUSTFLOAT(-96.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0));
		ui_interface->declare(&fHslider2, "3", "");
		ui_interface->addHorizontalSlider("destination", &fHslider2, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(8.0), FAUSTFLOAT(1.0));
		ui_interface->addCheckButton("pink noise", &fCheckbox1);
		ui_interface->addCheckButton("white noise", &fCheckbox0);
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
		double fSlow0 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * static_cast<double>(fHslider0));
		double fRec0_tmp[8];
		double* fRec0 = &fRec0_tmp[4];
		double fSlow1 = fConst0 * static_cast<double>(fHslider1);
		double fRec1_tmp[8];
		double* fRec1 = &fRec1_tmp[4];
		int iRec2_tmp[8];
		int* iRec2 = &iRec2_tmp[4];
		double fYec0_tmp[8];
		double* fYec0 = &fYec0_tmp[4];
		double fRec3_tmp[8];
		double* fRec3 = &fRec3_tmp[4];
		double fSlow2 = static_cast<double>(fHslider2);
		double fSlow3 = static_cast<double>(fSlow2 == 0.0);
		double fZec0[4];
		int iZec1[4];
		double fZec2[4];
		double fSlow4 = 4.656612875245797e-10 * static_cast<double>(fCheckbox0);
		double fSlow5 = 1e+01 * static_cast<double>(fCheckbox1);
		double fZec3[4];
		double fSlow6 = static_cast<double>(fSlow2 == 1.0);
		double fSlow7 = static_cast<double>(fSlow2 == 2.0);
		double fSlow8 = static_cast<double>(fSlow2 == 3.0);
		double fSlow9 = static_cast<double>(fSlow2 == 4.0);
		double fSlow10 = static_cast<double>(fSlow2 == 5.0);
		double fSlow11 = static_cast<double>(fSlow2 == 6.0);
		double fSlow12 = static_cast<double>(fSlow2 == 7.0);
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
			int vsize = 4;
			/* Recursive loop 0 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				fRec0_tmp[j0] = fRec0_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec0[i] = fSlow0 + 0.999 * fRec0[faust_wrap_sub(i, 1)];
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
				fRec1[i] = fSlow1 + (fRec1[faust_wrap_sub(i, 1)] - std::floor(fSlow1 + fRec1[faust_wrap_sub(i, 1)]));
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fRec1_perm[j3] = fRec1_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Recursive loop 2 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				iRec2_tmp[j4] = iRec2_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iRec2[i] = faust_wrap_add(faust_wrap_mul(1103515245, iRec2[faust_wrap_sub(i, 1)]), 12345);
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				iRec2_perm[j5] = iRec2_tmp[faust_wrap_add(vsize, j5)];
			}
			/* Vectorizable loop 3 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fYec0_tmp[j6] = fYec0_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec0[i] = static_cast<double>(iRec2[i]);
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fYec0_perm[j7] = fYec0_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Recursive loop 4 */
			/* Pre code */
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fRec3_tmp[j8] = fRec3_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec3[i] = 6.9067828423840845e-12 * fYec0[faust_wrap_sub(i, 2)] + 1.80116083982126 * fRec3[faust_wrap_sub(i, 1)] + 2.308528039463576e-11 * fYec0[i] - (0.80257737639225 * fRec3[faust_wrap_sub(i, 2)] + 2.9362651228132963e-11 * fYec0[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fRec3_perm[j9] = fRec3_tmp[faust_wrap_add(vsize, j9)];
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec0[i] = 65536.0 * fRec1[i];
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec1[i] = static_cast<int>(fZec0[i]);
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec2[i] = ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iZec1[i], 65536))];
			}
			/* Vectorizable loop 8 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec3[i] = fRec0[i] * (fZec2[i] + (fZec0[i] - std::floor(fZec0[i])) * (ftbl0mydspSIG0[std::max<int>(0, std::min<int>(faust_wrap_add(iZec1[i], 1), 65536))] - fZec2[i]) + fSlow4 * fYec0[i] + fSlow5 * fRec3[i]);
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fSlow3 * fZec3[i]);
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fSlow6 * fZec3[i]);
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output2[i] = static_cast<FAUSTFLOAT>(fSlow7 * fZec3[i]);
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output3[i] = static_cast<FAUSTFLOAT>(fSlow8 * fZec3[i]);
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output4[i] = static_cast<FAUSTFLOAT>(fSlow9 * fZec3[i]);
			}
			/* Vectorizable loop 14 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output5[i] = static_cast<FAUSTFLOAT>(fSlow10 * fZec3[i]);
			}
			/* Vectorizable loop 15 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output6[i] = static_cast<FAUSTFLOAT>(fSlow11 * fZec3[i]);
			}
			/* Vectorizable loop 16 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output7[i] = static_cast<FAUSTFLOAT>(fSlow12 * fZec3[i]);
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
			int vsize = faust_wrap_sub(count, vindex);
			/* Recursive loop 0 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				fRec0_tmp[j0] = fRec0_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec0[i] = fSlow0 + 0.999 * fRec0[faust_wrap_sub(i, 1)];
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
				fRec1[i] = fSlow1 + (fRec1[faust_wrap_sub(i, 1)] - std::floor(fSlow1 + fRec1[faust_wrap_sub(i, 1)]));
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fRec1_perm[j3] = fRec1_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Recursive loop 2 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				iRec2_tmp[j4] = iRec2_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iRec2[i] = faust_wrap_add(faust_wrap_mul(1103515245, iRec2[faust_wrap_sub(i, 1)]), 12345);
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				iRec2_perm[j5] = iRec2_tmp[faust_wrap_add(vsize, j5)];
			}
			/* Vectorizable loop 3 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fYec0_tmp[j6] = fYec0_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec0[i] = static_cast<double>(iRec2[i]);
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fYec0_perm[j7] = fYec0_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Recursive loop 4 */
			/* Pre code */
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fRec3_tmp[j8] = fRec3_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec3[i] = 6.9067828423840845e-12 * fYec0[faust_wrap_sub(i, 2)] + 1.80116083982126 * fRec3[faust_wrap_sub(i, 1)] + 2.308528039463576e-11 * fYec0[i] - (0.80257737639225 * fRec3[faust_wrap_sub(i, 2)] + 2.9362651228132963e-11 * fYec0[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fRec3_perm[j9] = fRec3_tmp[faust_wrap_add(vsize, j9)];
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec0[i] = 65536.0 * fRec1[i];
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec1[i] = static_cast<int>(fZec0[i]);
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec2[i] = ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iZec1[i], 65536))];
			}
			/* Vectorizable loop 8 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec3[i] = fRec0[i] * (fZec2[i] + (fZec0[i] - std::floor(fZec0[i])) * (ftbl0mydspSIG0[std::max<int>(0, std::min<int>(faust_wrap_add(iZec1[i], 1), 65536))] - fZec2[i]) + fSlow4 * fYec0[i] + fSlow5 * fRec3[i]);
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fSlow3 * fZec3[i]);
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fSlow6 * fZec3[i]);
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output2[i] = static_cast<FAUSTFLOAT>(fSlow7 * fZec3[i]);
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output3[i] = static_cast<FAUSTFLOAT>(fSlow8 * fZec3[i]);
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output4[i] = static_cast<FAUSTFLOAT>(fSlow9 * fZec3[i]);
			}
			/* Vectorizable loop 14 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output5[i] = static_cast<FAUSTFLOAT>(fSlow10 * fZec3[i]);
			}
			/* Vectorizable loop 15 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output6[i] = static_cast<FAUSTFLOAT>(fSlow11 * fZec3[i]);
			}
			/* Vectorizable loop 16 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output7[i] = static_cast<FAUSTFLOAT>(fSlow12 * fZec3[i]);
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
