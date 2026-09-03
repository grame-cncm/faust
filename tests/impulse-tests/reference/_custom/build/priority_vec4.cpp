/* ------------------------------------------------------------
name: "priority"
version: "2.44.4"
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
	
	int iVec1[2];
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
		for (int l8 = 0; l8 < 2; l8 = faust_wrap_add(l8, 1)) {
			iVec1[l8] = 0;
		}
		for (int l9 = 0; l9 < 2; l9 = faust_wrap_add(l9, 1)) {
			iRec5[l9] = 0;
		}
	}
	
	void fillmydspSIG0(int count, double* table) {
		for (int i1 = 0; i1 < count; i1 = faust_wrap_add(i1, 1)) {
			iVec1[0] = 1;
			iRec5[0] = (faust_wrap_add(iVec1[1], iRec5[1])) % 65536;
			table[i1] = std::sin(9.587379924285257e-05 * static_cast<double>(iRec5[0]));
			iVec1[1] = iVec1[0];
			iRec5[1] = iRec5[0];
		}
	}

};

static mydspSIG0* newmydspSIG0() { return (mydspSIG0*)new mydspSIG0(); }
static void deletemydspSIG0(mydspSIG0* dsp) { delete dsp; }

static double ftbl0mydspSIG0[65536];

class mydsp : public dsp {
	
 private:
	
	int iVec0_perm[4];
	int fSampleRate;
	double fConst0;
	int iConst1;
	int iRec2_perm[4];
	int iYec0_perm[4];
	int iRec1_perm[4];
	int iConst2;
	int iRec4_perm[4];
	int iYec1_perm[4];
	int iRec3_perm[4];
	double fConst3;
	double fRec0_perm[4];
	
 public:
	mydsp() {
	}
	
	mydsp(const mydsp&) = default;
	
	virtual ~mydsp() = default;
	
	mydsp& operator=(const mydsp&) = default;
	
	void metadata(Meta* m) { 
		m->declare("basics_lib_counter_author", "Stephane Letz");
		m->declare("basics_lib_name", "Faust Basic Element Library");
		m->declare("basics_lib_version", "0.8");
		m->declare("compile_options", "-single -scal -e dsp/priority.dsp -o priority_exp.dsp");
		m->declare("filename", "priority.dsp");
		m->declare("library_path0", "/usr/local/share/faust/stdfaust.lib");
		m->declare("library_path1", "/usr/local/share/faust/basics.lib");
		m->declare("library_path2", "/usr/local/share/faust/maths.lib");
		m->declare("library_path3", "/usr/local/share/faust/platform.lib");
		m->declare("library_path4", "/usr/local/share/faust/oscillators.lib");
		m->declare("maths_lib_author", "GRAME");
		m->declare("maths_lib_copyright", "GRAME");
		m->declare("maths_lib_license", "LGPL with exception");
		m->declare("maths_lib_name", "Faust Math Library");
		m->declare("maths_lib_version", "2.5");
		m->declare("name", "priority");
		m->declare("oscillators_lib_name", "Faust Oscillator Library");
		m->declare("oscillators_lib_version", "0.3");
		m->declare("platform_lib_name", "Generic Platform Library");
		m->declare("platform_lib_version", "0.2");
		m->declare("version", "2.44.4");
	}

	virtual int getNumInputs() {
		return 0;
	}
	virtual int getNumOutputs() {
		return 1;
	}
	
	static void classInit(int sample_rate) {
		mydspSIG0* sig0 = newmydspSIG0();
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(65536, ftbl0mydspSIG0);
		deletemydspSIG0(sig0);
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, static_cast<double>(fSampleRate)));
		iConst1 = static_cast<int>(0.5 * fConst0);
		iConst2 = static_cast<int>(fConst0);
		fConst3 = 1.0 / fConst0;
	}
	
	virtual void instanceResetUserInterface() {
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 4; l0 = faust_wrap_add(l0, 1)) {
			iVec0_perm[l0] = 0;
		}
		for (int l1 = 0; l1 < 4; l1 = faust_wrap_add(l1, 1)) {
			iRec2_perm[l1] = 0;
		}
		for (int l2 = 0; l2 < 4; l2 = faust_wrap_add(l2, 1)) {
			iYec0_perm[l2] = 0;
		}
		for (int l3 = 0; l3 < 4; l3 = faust_wrap_add(l3, 1)) {
			iRec1_perm[l3] = 0;
		}
		for (int l4 = 0; l4 < 4; l4 = faust_wrap_add(l4, 1)) {
			iRec4_perm[l4] = 0;
		}
		for (int l5 = 0; l5 < 4; l5 = faust_wrap_add(l5, 1)) {
			iYec1_perm[l5] = 0;
		}
		for (int l6 = 0; l6 < 4; l6 = faust_wrap_add(l6, 1)) {
			iRec3_perm[l6] = 0;
		}
		for (int l7 = 0; l7 < 4; l7 = faust_wrap_add(l7, 1)) {
			fRec0_perm[l7] = 0.0;
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
		ui_interface->openVerticalBox("priority");
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* output0_ptr = outputs[0];
		int iVec0_tmp[8];
		int* iVec0 = &iVec0_tmp[4];
		int iRec2_tmp[8];
		int* iRec2 = &iRec2_tmp[4];
		int iYec0_tmp[8];
		int* iYec0 = &iYec0_tmp[4];
		int iRec1_tmp[8];
		int* iRec1 = &iRec1_tmp[4];
		int iRec4_tmp[8];
		int* iRec4 = &iRec4_tmp[4];
		int iYec1_tmp[8];
		int* iYec1 = &iYec1_tmp[4];
		int iRec3_tmp[8];
		int* iRec3 = &iRec3_tmp[4];
		double fZec0[4];
		double fRec0_tmp[8];
		double* fRec0 = &fRec0_tmp[4];
		int vindex = 0;
		/* Main loop */
		for (vindex = 0; vindex <= (faust_wrap_sub(count, 4)); vindex = faust_wrap_add(vindex, 4)) {
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			int vsize = 4;
			/* Vectorizable loop 0 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				iVec0_tmp[j0] = iVec0_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iVec0[i] = 1;
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				iVec0_perm[j1] = iVec0_tmp[faust_wrap_add(vsize, j1)];
			}
			/* Recursive loop 1 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				iRec2_tmp[j2] = iRec2_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iRec2[i] = (faust_wrap_add(iVec0[faust_wrap_sub(i, 1)], iRec2[faust_wrap_sub(i, 1)])) % iConst1;
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				iRec2_perm[j3] = iRec2_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Vectorizable loop 2 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				iYec0_tmp[j4] = iYec0_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iYec0[i] = iRec2[i] <= iRec2[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				iYec0_perm[j5] = iYec0_tmp[faust_wrap_add(vsize, j5)];
			}
			/* Recursive loop 3 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				iRec1_tmp[j6] = iRec1_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iRec1[i] = faust_wrap_add(iRec1[faust_wrap_sub(i, 1)], iYec0[i] > iYec0[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				iRec1_perm[j7] = iRec1_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Recursive loop 4 */
			/* Pre code */
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				iRec4_tmp[j8] = iRec4_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iRec4[i] = (faust_wrap_add(iVec0[faust_wrap_sub(i, 1)], iRec4[faust_wrap_sub(i, 1)])) % iConst2;
			}
			/* Post code */
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				iRec4_perm[j9] = iRec4_tmp[faust_wrap_add(vsize, j9)];
			}
			/* Vectorizable loop 5 */
			/* Pre code */
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				iYec1_tmp[j10] = iYec1_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iYec1[i] = iRec4[i] <= iRec4[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				iYec1_perm[j11] = iYec1_tmp[faust_wrap_add(vsize, j11)];
			}
			/* Recursive loop 6 */
			/* Pre code */
			for (int j12 = 0; j12 < 4; j12 = faust_wrap_add(j12, 1)) {
				iRec3_tmp[j12] = iRec3_perm[j12];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iRec3[i] = faust_wrap_add(iRec3[faust_wrap_sub(i, 1)], iYec1[i] > iYec1[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j13 = 0; j13 < 4; j13 = faust_wrap_add(j13, 1)) {
				iRec3_perm[j13] = iRec3_tmp[faust_wrap_add(vsize, j13)];
			}
			/* Recursive loop 7 */
			/* Pre code */
			for (int j14 = 0; j14 < 4; j14 = faust_wrap_add(j14, 1)) {
				fRec0_tmp[j14] = fRec0_perm[j14];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec0[i] = fRec0[faust_wrap_sub(i, 1)] + fConst3 * static_cast<double>(faust_wrap_mul(200, faust_wrap_add(faust_wrap_add(iRec1[i] % 2, faust_wrap_mul(2, iRec3[i] % 2)), 1)));
				fRec0[i] = fZec0[i] - std::floor(fZec0[i]);
			}
			/* Post code */
			for (int j15 = 0; j15 < 4; j15 = faust_wrap_add(j15, 1)) {
				fRec0_perm[j15] = fRec0_tmp[faust_wrap_add(vsize, j15)];
			}
			/* Vectorizable loop 8 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(ftbl0mydspSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0 * fRec0[i]), 65535))]);
			}
		}
		/* Remaining frames */
		if (vindex < count) {
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			int vsize = faust_wrap_sub(count, vindex);
			/* Vectorizable loop 0 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				iVec0_tmp[j0] = iVec0_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iVec0[i] = 1;
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				iVec0_perm[j1] = iVec0_tmp[faust_wrap_add(vsize, j1)];
			}
			/* Recursive loop 1 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				iRec2_tmp[j2] = iRec2_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iRec2[i] = (faust_wrap_add(iVec0[faust_wrap_sub(i, 1)], iRec2[faust_wrap_sub(i, 1)])) % iConst1;
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				iRec2_perm[j3] = iRec2_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Vectorizable loop 2 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				iYec0_tmp[j4] = iYec0_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iYec0[i] = iRec2[i] <= iRec2[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				iYec0_perm[j5] = iYec0_tmp[faust_wrap_add(vsize, j5)];
			}
			/* Recursive loop 3 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				iRec1_tmp[j6] = iRec1_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iRec1[i] = faust_wrap_add(iRec1[faust_wrap_sub(i, 1)], iYec0[i] > iYec0[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				iRec1_perm[j7] = iRec1_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Recursive loop 4 */
			/* Pre code */
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				iRec4_tmp[j8] = iRec4_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iRec4[i] = (faust_wrap_add(iVec0[faust_wrap_sub(i, 1)], iRec4[faust_wrap_sub(i, 1)])) % iConst2;
			}
			/* Post code */
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				iRec4_perm[j9] = iRec4_tmp[faust_wrap_add(vsize, j9)];
			}
			/* Vectorizable loop 5 */
			/* Pre code */
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				iYec1_tmp[j10] = iYec1_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iYec1[i] = iRec4[i] <= iRec4[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				iYec1_perm[j11] = iYec1_tmp[faust_wrap_add(vsize, j11)];
			}
			/* Recursive loop 6 */
			/* Pre code */
			for (int j12 = 0; j12 < 4; j12 = faust_wrap_add(j12, 1)) {
				iRec3_tmp[j12] = iRec3_perm[j12];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iRec3[i] = faust_wrap_add(iRec3[faust_wrap_sub(i, 1)], iYec1[i] > iYec1[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j13 = 0; j13 < 4; j13 = faust_wrap_add(j13, 1)) {
				iRec3_perm[j13] = iRec3_tmp[faust_wrap_add(vsize, j13)];
			}
			/* Recursive loop 7 */
			/* Pre code */
			for (int j14 = 0; j14 < 4; j14 = faust_wrap_add(j14, 1)) {
				fRec0_tmp[j14] = fRec0_perm[j14];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec0[i] = fRec0[faust_wrap_sub(i, 1)] + fConst3 * static_cast<double>(faust_wrap_mul(200, faust_wrap_add(faust_wrap_add(iRec1[i] % 2, faust_wrap_mul(2, iRec3[i] % 2)), 1)));
				fRec0[i] = fZec0[i] - std::floor(fZec0[i]);
			}
			/* Post code */
			for (int j15 = 0; j15 < 4; j15 = faust_wrap_add(j15, 1)) {
				fRec0_perm[j15] = fRec0_tmp[faust_wrap_add(vsize, j15)];
			}
			/* Vectorizable loop 8 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(ftbl0mydspSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0 * fRec0[i]), 65535))]);
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
