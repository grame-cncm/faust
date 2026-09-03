/* ------------------------------------------------------------
author: "Oli Larkin (contact@olilarkin.co.uk)"
copyright: "Oliver Larkin"
name: "Thru Zero Flanger"
version: "0.1"
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
	
	int iRec3[2];
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
		for (int l4 = 0; l4 < 2; l4 = faust_wrap_add(l4, 1)) {
			iRec3[l4] = 0;
		}
	}
	
	void fillmydspSIG0(int count, double* table) {
		for (int i1 = 0; i1 < count; i1 = faust_wrap_add(i1, 1)) {
			iRec3[0] = faust_wrap_add(iRec3[1], 1);
			double fTemp0 = static_cast<double>(faust_wrap_add(iRec3[0], -1));
			double fTemp1 = 0.001953125 * fTemp0;
			double fTemp2 = 0.00390625 * fTemp0;
			table[i1] = 2.0 * (static_cast<double>((0.0 <= fTemp1) & (fTemp1 <= 0.5)) * (fTemp2 + -0.5) + static_cast<double>((0.5 < fTemp1) & (fTemp1 <= 1.0)) * (1.5 - fTemp2));
			iRec3[1] = iRec3[0];
		}
	}

};

static mydspSIG0* newmydspSIG0() { return (mydspSIG0*)new mydspSIG0(); }
static void deletemydspSIG0(mydspSIG0* dsp) { delete dsp; }

static double ftbl0mydspSIG0[513];

class mydsp : public dsp {
	
 private:
	
	int fSampleRate;
	double fConst0;
	double fConst1;
	double fConst2;
	FAUSTFLOAT fHslider0;
	double fRec0_perm[4];
	double fConst3;
	FAUSTFLOAT fHslider1;
	double fRec1_perm[4];
	double fConst4;
	FAUSTFLOAT fHslider2;
	double fRec2_perm[4];
	double fYec0[8192];
	int fYec0_idx;
	int fYec0_idx_save;
	double fConst5;
	double fConst6;
	FAUSTFLOAT fHslider3;
	double fRec4_perm[4];
	double fYec1[8192];
	int fYec1_idx;
	int fYec1_idx_save;
	
 public:
	mydsp() {
	}
	
	mydsp(const mydsp&) = default;
	
	virtual ~mydsp() = default;
	
	mydsp& operator=(const mydsp&) = default;
	
	void metadata(Meta* m) { 
		m->declare("author", "Oli Larkin (contact@olilarkin.co.uk)");
		m->declare("compile_options", "-a /Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/archs/impulsearch.cpp -lang cpp -i -fpga-mem-th 4 -ct 1 -es 1 -mcd 4 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs");
		m->declare("copyright", "Oliver Larkin");
		m->declare("description", "Stereo Thru Zero Flanger - warning can ZERO the sound!");
		m->declare("effect.lib/name", "Faust Audio Effect Library");
		m->declare("filename", "thru_zero_flanger.dsp");
		m->declare("filter.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("filter.lib/copyright", "Julius O. Smith III");
		m->declare("filter.lib/license", "STK-4.3");
		m->declare("filter.lib/name", "Faust Filter Library");
		m->declare("filter.lib/reference", "https://ccrma.stanford.edu/~jos/filters/");
		m->declare("filter.lib/version", "1.29");
		m->declare("licence", "GPL");
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
		m->declare("name", "Thru Zero Flanger");
		m->declare("version", "0.1");
	}

	virtual int getNumInputs() {
		return 2;
	}
	virtual int getNumOutputs() {
		return 2;
	}
	
	static void classInit(int sample_rate) {
		mydspSIG0* sig0 = newmydspSIG0();
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(513, ftbl0mydspSIG0);
		deletemydspSIG0(sig0);
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, static_cast<double>(fSampleRate)));
		fConst1 = std::exp(-(2e+02 / fConst0));
		fConst2 = 1.0 - fConst1;
		fConst3 = 0.01 * fConst2;
		fConst4 = 1.0 / fConst0;
		fConst5 = 0.001 * fConst0;
		fConst6 = 0.5 * fConst2;
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(1e+01);
		fHslider1 = static_cast<FAUSTFLOAT>(2e+01);
		fHslider2 = static_cast<FAUSTFLOAT>(0.1);
		fHslider3 = static_cast<FAUSTFLOAT>(0.0);
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
		for (int l3 = 0; l3 < 8192; l3 = faust_wrap_add(l3, 1)) {
			fYec0[l3] = 0.0;
		}
		fYec0_idx = 0;
		fYec0_idx_save = 0;
		for (int l5 = 0; l5 < 4; l5 = faust_wrap_add(l5, 1)) {
			fRec4_perm[l5] = 0.0;
		}
		for (int l6 = 0; l6 < 8192; l6 = faust_wrap_add(l6, 1)) {
			fYec1[l6] = 0.0;
		}
		fYec1_idx = 0;
		fYec1_idx_save = 0;
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
		ui_interface->openVerticalBox("Thru Zero Flanger");
		ui_interface->declare(&fHslider0, "OWL", "PARAMETER_B");
		ui_interface->declare(&fHslider0, "unit", "ms");
		ui_interface->addHorizontalSlider("Delay", &fHslider0, FAUSTFLOAT(1e+01), FAUSTFLOAT(0.5), FAUSTFLOAT(2e+01), FAUSTFLOAT(0.01));
		ui_interface->declare(&fHslider1, "OWL", "PARAMETER_D");
		ui_interface->declare(&fHslider1, "unit", "%");
		ui_interface->addHorizontalSlider("Depth", &fHslider1, FAUSTFLOAT(2e+01), FAUSTFLOAT(3.0), FAUSTFLOAT(1e+02), FAUSTFLOAT(1.0));
		ui_interface->declare(&fHslider3, "OWL", "PARAMETER_C");
		ui_interface->addHorizontalSlider("L-R Offset", &fHslider3, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.001));
		ui_interface->declare(&fHslider2, "OWL", "PARAMETER_A");
		ui_interface->declare(&fHslider2, "unit", "hz");
		ui_interface->addHorizontalSlider("Rate", &fHslider2, FAUSTFLOAT(0.1), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.001));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0_ptr = inputs[0];
		FAUSTFLOAT* input1_ptr = inputs[1];
		FAUSTFLOAT* output0_ptr = outputs[0];
		FAUSTFLOAT* output1_ptr = outputs[1];
		double fSlow0 = fConst2 * static_cast<double>(fHslider0);
		double fRec0_tmp[8];
		double* fRec0 = &fRec0_tmp[4];
		double fSlow1 = fConst3 * static_cast<double>(fHslider1);
		double fRec1_tmp[8];
		double* fRec1 = &fRec1_tmp[4];
		double fSlow2 = fConst4 * static_cast<double>(fHslider2);
		double fRec2_tmp[8];
		double* fRec2 = &fRec2_tmp[4];
		double fZec0[4];
		int iZec1[4];
		int iZec2[4];
		double fZec3[4];
		double fZec4[4];
		double fZec5[4];
		int iZec6[4];
		double fZec7[4];
		int iZec8[4];
		double fZec9[4];
		double fZec10[4];
		int iZec11[4];
		double fZec12[4];
		double fSlow3 = fConst6 * static_cast<double>(fHslider3);
		double fRec4_tmp[8];
		double* fRec4 = &fRec4_tmp[4];
		double fZec13[4];
		int iZec14[4];
		double fZec15[4];
		double fZec16[4];
		int iZec17[4];
		double fZec18[4];
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
				fRec0_tmp[j0] = fRec0_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec0[i] = fSlow0 + fConst1 * fRec0[faust_wrap_sub(i, 1)];
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
				fRec1[i] = fSlow1 + fConst1 * fRec1[faust_wrap_sub(i, 1)];
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
				fRec2[i] = fSlow2 + (fRec2[faust_wrap_sub(i, 1)] - std::floor(fSlow2 + fRec2[faust_wrap_sub(i, 1)]));
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fRec2_perm[j5] = fRec2_tmp[faust_wrap_add(vsize, j5)];
			}
			/* Vectorizable loop 3 */
			/* Pre code */
			fYec0_idx = (faust_wrap_add(fYec0_idx, fYec0_idx_save)) & 8191;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec0[(faust_wrap_add(i, fYec0_idx)) & 8191] = static_cast<double>(input0[i]);
			}
			/* Post code */
			fYec0_idx_save = vsize;
			/* Vectorizable loop 4 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec0[i] = fConst5 * fRec0[i];
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec1[i] = static_cast<int>(fZec0[i]);
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec2[i] = iZec1[i] & 4095;
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec3[i] = static_cast<double>(iZec1[i]);
			}
			/* Vectorizable loop 8 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec4[i] = fZec3[i] + (1.0 - fZec0[i]);
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec5[i] = fZec0[i] - fZec3[i];
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec6[i] = (faust_wrap_add(iZec1[i], 1)) & 4095;
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec7[i] = 512.0 * std::fmod(fRec2[i], 1.0);
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec8[i] = static_cast<int>(fZec7[i]);
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec9[i] = ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iZec8[i], 512))];
			}
			/* Vectorizable loop 14 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec10[i] = fConst5 * fRec0[i] * (fRec1[i] * (fZec9[i] + (fZec7[i] - std::floor(fZec7[i])) * (ftbl0mydspSIG0[std::max<int>(0, std::min<int>(faust_wrap_add(iZec8[i], 1), 512))] - fZec9[i])) + 1.0);
			}
			/* Vectorizable loop 15 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec11[i] = static_cast<int>(fZec10[i]);
			}
			/* Vectorizable loop 16 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec12[i] = static_cast<double>(iZec11[i]);
			}
			/* Vectorizable loop 17 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), iZec2[i])) & 8191] * fZec4[i] + fZec5[i] * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), iZec6[i])) & 8191] - (fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), iZec11[i] & 4095)) & 8191] * (fZec12[i] + (1.0 - fZec10[i])) + (fZec10[i] - fZec12[i]) * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), (faust_wrap_add(iZec11[i], 1)) & 4095)) & 8191]));
			}
			/* Recursive loop 18 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec4_tmp[j6] = fRec4_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec4[i] = fSlow3 + fConst1 * fRec4[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec4_perm[j7] = fRec4_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Vectorizable loop 19 */
			/* Pre code */
			fYec1_idx = (faust_wrap_add(fYec1_idx, fYec1_idx_save)) & 8191;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec1[(faust_wrap_add(i, fYec1_idx)) & 8191] = static_cast<double>(input1[i]);
			}
			/* Post code */
			fYec1_idx_save = vsize;
			/* Vectorizable loop 20 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec13[i] = 512.0 * std::fmod(fRec2[i] + fRec4[i], 1.0);
			}
			/* Vectorizable loop 21 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec14[i] = static_cast<int>(fZec13[i]);
			}
			/* Vectorizable loop 22 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec15[i] = ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iZec14[i], 512))];
			}
			/* Vectorizable loop 23 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec16[i] = fConst5 * fRec0[i] * (fRec1[i] * (fZec15[i] + (fZec13[i] - std::floor(fZec13[i])) * (ftbl0mydspSIG0[std::max<int>(0, std::min<int>(faust_wrap_add(iZec14[i], 1), 512))] - fZec15[i])) + 1.0);
			}
			/* Vectorizable loop 24 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec17[i] = static_cast<int>(fZec16[i]);
			}
			/* Vectorizable loop 25 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec18[i] = static_cast<double>(iZec17[i]);
			}
			/* Vectorizable loop 26 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fZec4[i] * fYec1[(faust_wrap_sub(faust_wrap_add(i, fYec1_idx), iZec2[i])) & 8191] + fZec5[i] * fYec1[(faust_wrap_sub(faust_wrap_add(i, fYec1_idx), iZec6[i])) & 8191] - (fYec1[(faust_wrap_sub(faust_wrap_add(i, fYec1_idx), iZec17[i] & 4095)) & 8191] * (fZec18[i] + (1.0 - fZec16[i])) + (fZec16[i] - fZec18[i]) * fYec1[(faust_wrap_sub(faust_wrap_add(i, fYec1_idx), (faust_wrap_add(iZec17[i], 1)) & 4095)) & 8191]));
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
				fRec0_tmp[j0] = fRec0_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec0[i] = fSlow0 + fConst1 * fRec0[faust_wrap_sub(i, 1)];
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
				fRec1[i] = fSlow1 + fConst1 * fRec1[faust_wrap_sub(i, 1)];
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
				fRec2[i] = fSlow2 + (fRec2[faust_wrap_sub(i, 1)] - std::floor(fSlow2 + fRec2[faust_wrap_sub(i, 1)]));
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fRec2_perm[j5] = fRec2_tmp[faust_wrap_add(vsize, j5)];
			}
			/* Vectorizable loop 3 */
			/* Pre code */
			fYec0_idx = (faust_wrap_add(fYec0_idx, fYec0_idx_save)) & 8191;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec0[(faust_wrap_add(i, fYec0_idx)) & 8191] = static_cast<double>(input0[i]);
			}
			/* Post code */
			fYec0_idx_save = vsize;
			/* Vectorizable loop 4 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec0[i] = fConst5 * fRec0[i];
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec1[i] = static_cast<int>(fZec0[i]);
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec2[i] = iZec1[i] & 4095;
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec3[i] = static_cast<double>(iZec1[i]);
			}
			/* Vectorizable loop 8 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec4[i] = fZec3[i] + (1.0 - fZec0[i]);
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec5[i] = fZec0[i] - fZec3[i];
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec6[i] = (faust_wrap_add(iZec1[i], 1)) & 4095;
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec7[i] = 512.0 * std::fmod(fRec2[i], 1.0);
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec8[i] = static_cast<int>(fZec7[i]);
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec9[i] = ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iZec8[i], 512))];
			}
			/* Vectorizable loop 14 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec10[i] = fConst5 * fRec0[i] * (fRec1[i] * (fZec9[i] + (fZec7[i] - std::floor(fZec7[i])) * (ftbl0mydspSIG0[std::max<int>(0, std::min<int>(faust_wrap_add(iZec8[i], 1), 512))] - fZec9[i])) + 1.0);
			}
			/* Vectorizable loop 15 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec11[i] = static_cast<int>(fZec10[i]);
			}
			/* Vectorizable loop 16 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec12[i] = static_cast<double>(iZec11[i]);
			}
			/* Vectorizable loop 17 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), iZec2[i])) & 8191] * fZec4[i] + fZec5[i] * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), iZec6[i])) & 8191] - (fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), iZec11[i] & 4095)) & 8191] * (fZec12[i] + (1.0 - fZec10[i])) + (fZec10[i] - fZec12[i]) * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), (faust_wrap_add(iZec11[i], 1)) & 4095)) & 8191]));
			}
			/* Recursive loop 18 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec4_tmp[j6] = fRec4_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec4[i] = fSlow3 + fConst1 * fRec4[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec4_perm[j7] = fRec4_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Vectorizable loop 19 */
			/* Pre code */
			fYec1_idx = (faust_wrap_add(fYec1_idx, fYec1_idx_save)) & 8191;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec1[(faust_wrap_add(i, fYec1_idx)) & 8191] = static_cast<double>(input1[i]);
			}
			/* Post code */
			fYec1_idx_save = vsize;
			/* Vectorizable loop 20 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec13[i] = 512.0 * std::fmod(fRec2[i] + fRec4[i], 1.0);
			}
			/* Vectorizable loop 21 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec14[i] = static_cast<int>(fZec13[i]);
			}
			/* Vectorizable loop 22 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec15[i] = ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iZec14[i], 512))];
			}
			/* Vectorizable loop 23 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec16[i] = fConst5 * fRec0[i] * (fRec1[i] * (fZec15[i] + (fZec13[i] - std::floor(fZec13[i])) * (ftbl0mydspSIG0[std::max<int>(0, std::min<int>(faust_wrap_add(iZec14[i], 1), 512))] - fZec15[i])) + 1.0);
			}
			/* Vectorizable loop 24 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec17[i] = static_cast<int>(fZec16[i]);
			}
			/* Vectorizable loop 25 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec18[i] = static_cast<double>(iZec17[i]);
			}
			/* Vectorizable loop 26 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fZec4[i] * fYec1[(faust_wrap_sub(faust_wrap_add(i, fYec1_idx), iZec2[i])) & 8191] + fZec5[i] * fYec1[(faust_wrap_sub(faust_wrap_add(i, fYec1_idx), iZec6[i])) & 8191] - (fYec1[(faust_wrap_sub(faust_wrap_add(i, fYec1_idx), iZec17[i] & 4095)) & 8191] * (fZec18[i] + (1.0 - fZec16[i])) + (fZec16[i] - fZec18[i]) * fYec1[(faust_wrap_sub(faust_wrap_add(i, fYec1_idx), (faust_wrap_add(iZec17[i], 1)) & 4095)) & 8191]));
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
