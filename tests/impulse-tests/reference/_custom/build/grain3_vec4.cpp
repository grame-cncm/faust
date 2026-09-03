/* ------------------------------------------------------------
name: "grain3"
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
	
	int iRec5[2];
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
		for (int l6 = 0; l6 < 2; l6 = faust_wrap_add(l6, 1)) {
			iRec5[l6] = 0;
		}
	}
	
	void fillmydspSIG0(int count, double* table) {
		for (int i1 = 0; i1 < count; i1 = faust_wrap_add(i1, 1)) {
			iRec5[0] = faust_wrap_add(iRec5[1], 1);
			table[i1] = std::sin(9.587379924285257e-05 * static_cast<double>(faust_wrap_add(iRec5[0], -1)));
			iRec5[1] = iRec5[0];
		}
	}

};

static mydspSIG0* newmydspSIG0() { return (mydspSIG0*)new mydspSIG0(); }
static void deletemydspSIG0(mydspSIG0* dsp) { delete dsp; }

class mydspSIG1 {
	
  private:
	
	int iRec6[2];
	int fSampleRate;
	
  public:
	
	int getNumInputsmydspSIG1() {
		return 0;
	}
	int getNumOutputsmydspSIG1() {
		return 1;
	}
	
	void instanceInitmydspSIG1(int sample_rate) {
		fSampleRate = sample_rate;
		for (int l7 = 0; l7 < 2; l7 = faust_wrap_add(l7, 1)) {
			iRec6[l7] = 0;
		}
	}
	
	void fillmydspSIG1(int count, double* table) {
		for (int i2 = 0; i2 < count; i2 = faust_wrap_add(i2, 1)) {
			iRec6[0] = faust_wrap_add(iRec6[1], 1);
			table[i2] = std::cos(9.587379924285257e-05 * static_cast<double>(faust_wrap_add(iRec6[0], -1)));
			iRec6[1] = iRec6[0];
		}
	}

};

static mydspSIG1* newmydspSIG1() { return (mydspSIG1*)new mydspSIG1(); }
static void deletemydspSIG1(mydspSIG1* dsp) { delete dsp; }

static double ftbl0mydspSIG0[65536];
static double ftbl1mydspSIG1[65536];

class mydsp : public dsp {
	
 private:
	
	int fSampleRate;
	double fConst0;
	double fConst1;
	FAUSTFLOAT fHslider0;
	double fRec1_perm[4];
	int iRec2_perm[4];
	FAUSTFLOAT fHslider1;
	int iRec0_perm[4];
	double fConst2;
	FAUSTFLOAT fHslider2;
	double fRec3_perm[4];
	double fRec4_perm[4];
	double fYec0[1048576];
	int fYec0_idx;
	int fYec0_idx_save;
	
 public:
	mydsp() {
	}
	
	mydsp(const mydsp&) = default;
	
	virtual ~mydsp() = default;
	
	mydsp& operator=(const mydsp&) = default;
	
	void metadata(Meta* m) { 
		m->declare("basics_lib_name", "Faust Basic Element Library");
		m->declare("basics_lib_version", "0.1");
		m->declare("compilation_options", "-single -scal -e grain3.dsp -o grain3.dsp");
		m->declare("compile_options", "-a /Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/archs/impulsearch.cpp -lang cpp -i -fpga-mem-th 4 -ct 1 -es 1 -mcd 4 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs");
		m->declare("delays_lib_name", "Faust Delay Library");
		m->declare("delays_lib_version", "0.1");
		m->declare("filename", "grain3.dsp");
		m->declare("library_path", "/usr/local/share/faust/stdfaust.lib");
		m->declare("maths_lib_author", "GRAME");
		m->declare("maths_lib_copyright", "GRAME");
		m->declare("maths_lib_license", "LGPL with exception");
		m->declare("maths_lib_name", "Faust Math Library");
		m->declare("maths_lib_version", "2.3");
		m->declare("name", "grain3");
		m->declare("noises_lib_name", "Faust Noise Generator Library");
		m->declare("noises_lib_version", "0.0");
		m->declare("oscillators_lib_name", "Faust Oscillator Library");
		m->declare("oscillators_lib_version", "0.1");
		m->declare("platform_lib_name", "Generic Platform Library");
		m->declare("platform_lib_version", "0.1");
	}

	virtual int getNumInputs() {
		return 1;
	}
	virtual int getNumOutputs() {
		return 1;
	}
	
	static void classInit(int sample_rate) {
		mydspSIG0* sig0 = newmydspSIG0();
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(65536, ftbl0mydspSIG0);
		mydspSIG1* sig1 = newmydspSIG1();
		sig1->instanceInitmydspSIG1(sample_rate);
		sig1->fillmydspSIG1(65536, ftbl1mydspSIG1);
		deletemydspSIG0(sig0);
		deletemydspSIG1(sig1);
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, static_cast<double>(fSampleRate)));
		fConst1 = 1e+03 / fConst0;
		fConst2 = 0.0005 * fConst0;
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(1e+02);
		fHslider1 = static_cast<FAUSTFLOAT>(0.2);
		fHslider2 = static_cast<FAUSTFLOAT>(1e+03);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 4; l0 = faust_wrap_add(l0, 1)) {
			fRec1_perm[l0] = 0.0;
		}
		for (int l1 = 0; l1 < 4; l1 = faust_wrap_add(l1, 1)) {
			iRec2_perm[l1] = 0;
		}
		for (int l2 = 0; l2 < 4; l2 = faust_wrap_add(l2, 1)) {
			iRec0_perm[l2] = 0;
		}
		for (int l3 = 0; l3 < 4; l3 = faust_wrap_add(l3, 1)) {
			fRec3_perm[l3] = 0.0;
		}
		for (int l4 = 0; l4 < 4; l4 = faust_wrap_add(l4, 1)) {
			fRec4_perm[l4] = 0.0;
		}
		for (int l5 = 0; l5 < 1048576; l5 = faust_wrap_add(l5, 1)) {
			fYec0[l5] = 0.0;
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
		ui_interface->openVerticalBox("grain3");
		ui_interface->addHorizontalSlider("delaymax", &fHslider2, FAUSTFLOAT(1e+03), FAUSTFLOAT(1e+01), FAUSTFLOAT(1e+04), FAUSTFLOAT(1.0));
		ui_interface->declare(&fHslider0, "unit", "msec");
		ui_interface->addHorizontalSlider("grainsize", &fHslider0, FAUSTFLOAT(1e+02), FAUSTFLOAT(1.0), FAUSTFLOAT(1e+03), FAUSTFLOAT(1.0));
		ui_interface->addHorizontalSlider("rarefaction", &fHslider1, FAUSTFLOAT(0.2), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.01));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0_ptr = inputs[0];
		FAUSTFLOAT* output0_ptr = outputs[0];
		double fSlow0 = fConst1 / static_cast<double>(fHslider0);
		double fRec1_tmp[8];
		double* fRec1 = &fRec1_tmp[4];
		int iRec2_tmp[8];
		int* iRec2 = &iRec2_tmp[4];
		int iZec0[4];
		double fZec1[4];
		double fSlow1 = static_cast<double>(fHslider1);
		int iRec0_tmp[8];
		int* iRec0 = &iRec0_tmp[4];
		double fSlow2 = fConst2 * static_cast<double>(fHslider2);
		double fRec3_tmp[8];
		double* fRec3 = &fRec3_tmp[4];
		double fRec4_tmp[8];
		double* fRec4 = &fRec4_tmp[4];
		int iZec2[4];
		double fZec3[4];
		int iZec4[4];
		double fZec5[4];
		int vindex = 0;
		/* Main loop */
		for (vindex = 0; vindex <= (faust_wrap_sub(count, 4)); vindex = faust_wrap_add(vindex, 4)) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			int vsize = 4;
			/* Recursive loop 0 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				fRec1_tmp[j0] = fRec1_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec1[i] = fSlow0 + (fRec1[faust_wrap_sub(i, 1)] - std::floor(fSlow0 + fRec1[faust_wrap_sub(i, 1)]));
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				fRec1_perm[j1] = fRec1_tmp[faust_wrap_add(vsize, j1)];
			}
			/* Recursive loop 1 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				iRec2_tmp[j2] = iRec2_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iRec2[i] = faust_wrap_add(faust_wrap_mul(1103515245, iRec2[faust_wrap_sub(i, 1)]), 12345);
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				iRec2_perm[j3] = iRec2_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Vectorizable loop 2 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec0[i] = (fRec1[i] > 0.0001) * (fRec1[faust_wrap_sub(i, 1)] <= 0.0001);
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec1[i] = 4.656612875245797e-10 * static_cast<double>(iRec2[i]) + 1.0;
			}
			/* Recursive loop 4 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				iRec0_tmp[j4] = iRec0_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iRec0[i] = ((iZec0[i]) ? (0.5 * fZec1[i]) > fSlow1 : iRec0[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				iRec0_perm[j5] = iRec0_tmp[faust_wrap_add(vsize, j5)];
			}
			/* Recursive loop 5 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec3_tmp[j6] = fRec3_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec3[i] = ((iZec0[i]) ? fSlow2 * fZec1[i] : fRec3[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec3_perm[j7] = fRec3_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Recursive loop 6 */
			/* Pre code */
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fRec4_tmp[j8] = fRec4_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec4[i] = fRec4[faust_wrap_sub(i, 1)] - std::floor(fRec4[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fRec4_perm[j9] = fRec4_tmp[faust_wrap_add(vsize, j9)];
			}
			/* Vectorizable loop 7 */
			/* Pre code */
			fYec0_idx = (faust_wrap_add(fYec0_idx, fYec0_idx_save)) & 1048575;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec0[(faust_wrap_add(i, fYec0_idx)) & 1048575] = static_cast<double>(input0[i]);
			}
			/* Post code */
			fYec0_idx_save = vsize;
			/* Vectorizable loop 8 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec2[i] = static_cast<int>(fRec3[i]);
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec3[i] = std::floor(fRec3[i]);
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec4[i] = static_cast<int>(65536.0 * fRec4[i]);
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec5[i] = 3.141592653589793 * fRec1[i];
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(static_cast<double>(iRec0[i]) * (fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), std::min<int>(524289, std::max<int>(0, iZec2[i])))) & 1048575] * (fZec3[i] + (1.0 - fRec3[i])) + (fRec3[i] - fZec3[i]) * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), std::min<int>(524289, std::max<int>(0, faust_wrap_add(iZec2[i], 1))))) & 1048575]) * (ftbl0mydspSIG0[iZec4[i]] * std::cos(fZec5[i]) + ftbl1mydspSIG1[iZec4[i]] * std::sin(fZec5[i])));
			}
		}
		/* Remaining frames */
		if (vindex < count) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			int vsize = faust_wrap_sub(count, vindex);
			/* Recursive loop 0 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				fRec1_tmp[j0] = fRec1_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec1[i] = fSlow0 + (fRec1[faust_wrap_sub(i, 1)] - std::floor(fSlow0 + fRec1[faust_wrap_sub(i, 1)]));
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				fRec1_perm[j1] = fRec1_tmp[faust_wrap_add(vsize, j1)];
			}
			/* Recursive loop 1 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				iRec2_tmp[j2] = iRec2_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iRec2[i] = faust_wrap_add(faust_wrap_mul(1103515245, iRec2[faust_wrap_sub(i, 1)]), 12345);
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				iRec2_perm[j3] = iRec2_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Vectorizable loop 2 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec0[i] = (fRec1[i] > 0.0001) * (fRec1[faust_wrap_sub(i, 1)] <= 0.0001);
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec1[i] = 4.656612875245797e-10 * static_cast<double>(iRec2[i]) + 1.0;
			}
			/* Recursive loop 4 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				iRec0_tmp[j4] = iRec0_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iRec0[i] = ((iZec0[i]) ? (0.5 * fZec1[i]) > fSlow1 : iRec0[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				iRec0_perm[j5] = iRec0_tmp[faust_wrap_add(vsize, j5)];
			}
			/* Recursive loop 5 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec3_tmp[j6] = fRec3_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec3[i] = ((iZec0[i]) ? fSlow2 * fZec1[i] : fRec3[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec3_perm[j7] = fRec3_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Recursive loop 6 */
			/* Pre code */
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fRec4_tmp[j8] = fRec4_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec4[i] = fRec4[faust_wrap_sub(i, 1)] - std::floor(fRec4[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fRec4_perm[j9] = fRec4_tmp[faust_wrap_add(vsize, j9)];
			}
			/* Vectorizable loop 7 */
			/* Pre code */
			fYec0_idx = (faust_wrap_add(fYec0_idx, fYec0_idx_save)) & 1048575;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec0[(faust_wrap_add(i, fYec0_idx)) & 1048575] = static_cast<double>(input0[i]);
			}
			/* Post code */
			fYec0_idx_save = vsize;
			/* Vectorizable loop 8 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec2[i] = static_cast<int>(fRec3[i]);
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec3[i] = std::floor(fRec3[i]);
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec4[i] = static_cast<int>(65536.0 * fRec4[i]);
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec5[i] = 3.141592653589793 * fRec1[i];
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(static_cast<double>(iRec0[i]) * (fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), std::min<int>(524289, std::max<int>(0, iZec2[i])))) & 1048575] * (fZec3[i] + (1.0 - fRec3[i])) + (fRec3[i] - fZec3[i]) * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), std::min<int>(524289, std::max<int>(0, faust_wrap_add(iZec2[i], 1))))) & 1048575]) * (ftbl0mydspSIG0[iZec4[i]] * std::cos(fZec5[i]) + ftbl1mydspSIG1[iZec4[i]] * std::sin(fZec5[i])));
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
