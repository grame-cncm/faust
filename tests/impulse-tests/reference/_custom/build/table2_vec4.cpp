/* ------------------------------------------------------------
name: "table2"
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

class mydspSIG0 {
	
  private:
	
	int iRec1[2];
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
		for (int l1 = 0; l1 < 2; l1 = faust_wrap_add(l1, 1)) {
			iRec1[l1] = 0;
		}
	}
	
	void fillmydspSIG0(int count, int* table) {
		for (int i1 = 0; i1 < count; i1 = faust_wrap_add(i1, 1)) {
			iRec1[0] = faust_wrap_add(iRec1[1], 1);
			table[i1] = iRec1[0];
			iRec1[1] = iRec1[0];
		}
	}

};

static mydspSIG0* newmydspSIG0() { return (mydspSIG0*)new mydspSIG0(); }
static void deletemydspSIG0(mydspSIG0* dsp) { delete dsp; }

class mydspSIG1 {
	
  private:
	
	double fRec3[2];
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
		for (int l3 = 0; l3 < 2; l3 = faust_wrap_add(l3, 1)) {
			fRec3[l3] = 0.0;
		}
	}
	
	void fillmydspSIG1(int count, double* table) {
		for (int i2 = 0; i2 < count; i2 = faust_wrap_add(i2, 1)) {
			fRec3[0] = fRec3[1] + 0.1;
			table[i2] = fRec3[0];
			fRec3[1] = fRec3[0];
		}
	}

};

static mydspSIG1* newmydspSIG1() { return (mydspSIG1*)new mydspSIG1(); }
static void deletemydspSIG1(mydspSIG1* dsp) { delete dsp; }

const static int imydspSIG2Wave0[7] = {1,2,3,7,4,8,1};
class mydspSIG2 {
	
  private:
	
	int imydspSIG2Wave0_idx;
	int fSampleRate;
	
  public:
	
	int getNumInputsmydspSIG2() {
		return 0;
	}
	int getNumOutputsmydspSIG2() {
		return 1;
	}
	
	void instanceInitmydspSIG2(int sample_rate) {
		fSampleRate = sample_rate;
		imydspSIG2Wave0_idx = 0;
	}
	
	void fillmydspSIG2(int count, int* table) {
		for (int i3 = 0; i3 < count; i3 = faust_wrap_add(i3, 1)) {
			table[i3] = imydspSIG2Wave0[imydspSIG2Wave0_idx];
			imydspSIG2Wave0_idx = (faust_wrap_add(1, imydspSIG2Wave0_idx)) % 7;
		}
	}

};

static mydspSIG2* newmydspSIG2() { return (mydspSIG2*)new mydspSIG2(); }
static void deletemydspSIG2(mydspSIG2* dsp) { delete dsp; }

const static double fmydspSIG3Wave0[7] = {1.4,2.1,3.8,7.12,4.9,8.9,1.2};
class mydspSIG3 {
	
  private:
	
	int fmydspSIG3Wave0_idx;
	int fSampleRate;
	
  public:
	
	int getNumInputsmydspSIG3() {
		return 0;
	}
	int getNumOutputsmydspSIG3() {
		return 1;
	}
	
	void instanceInitmydspSIG3(int sample_rate) {
		fSampleRate = sample_rate;
		fmydspSIG3Wave0_idx = 0;
	}
	
	void fillmydspSIG3(int count, double* table) {
		for (int i4 = 0; i4 < count; i4 = faust_wrap_add(i4, 1)) {
			table[i4] = fmydspSIG3Wave0[fmydspSIG3Wave0_idx];
			fmydspSIG3Wave0_idx = (faust_wrap_add(1, fmydspSIG3Wave0_idx)) % 7;
		}
	}

};

static mydspSIG3* newmydspSIG3() { return (mydspSIG3*)new mydspSIG3(); }
static void deletemydspSIG3(mydspSIG3* dsp) { delete dsp; }

const static int imydspWave0[7] = {1,2,3,7,4,8,1};
const static double fmydspWave1[7] = {1.4,2.1,3.8,7.12,4.9,8.9,1.2};

class mydsp : public dsp {
	
 private:
	
	int iRec0_perm[4];
	int itbl0[10];
	double fRec2_perm[4];
	double ftbl1[7];
	int itbl2[10];
	int imydspWave0_idx;
	double ftbl3[7];
	int fmydspWave1_idx;
	int fSampleRate;
	
 public:
	mydsp() {
	}
	
	mydsp(const mydsp&) = default;
	
	virtual ~mydsp() = default;
	
	mydsp& operator=(const mydsp&) = default;
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-a /Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/archs/impulsearch.cpp -lang cpp -i -fpga-mem-th 4 -ct 1 -es 1 -mcd 4 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs");
		m->declare("filename", "table2.dsp");
		m->declare("name", "table2");
	}

	virtual int getNumInputs() {
		return 0;
	}
	virtual int getNumOutputs() {
		return 4;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		mydspSIG0* sig0 = newmydspSIG0();
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(10, itbl0);
		mydspSIG1* sig1 = newmydspSIG1();
		sig1->instanceInitmydspSIG1(sample_rate);
		sig1->fillmydspSIG1(7, ftbl1);
		mydspSIG2* sig2 = newmydspSIG2();
		sig2->instanceInitmydspSIG2(sample_rate);
		sig2->fillmydspSIG2(10, itbl2);
		imydspWave0_idx = 0;
		mydspSIG3* sig3 = newmydspSIG3();
		sig3->instanceInitmydspSIG3(sample_rate);
		sig3->fillmydspSIG3(7, ftbl3);
		fmydspWave1_idx = 0;
		deletemydspSIG0(sig0);
		deletemydspSIG1(sig1);
		deletemydspSIG2(sig2);
		deletemydspSIG3(sig3);
	}
	
	virtual void instanceResetUserInterface() {
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 4; l0 = faust_wrap_add(l0, 1)) {
			iRec0_perm[l0] = 0;
		}
		for (int l2 = 0; l2 < 4; l2 = faust_wrap_add(l2, 1)) {
			fRec2_perm[l2] = 0.0;
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
		ui_interface->openVerticalBox("table2");
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* output0_ptr = outputs[0];
		FAUSTFLOAT* output1_ptr = outputs[1];
		FAUSTFLOAT* output2_ptr = outputs[2];
		FAUSTFLOAT* output3_ptr = outputs[3];
		int iRec0_tmp[8];
		int* iRec0 = &iRec0_tmp[4];
		double fRec2_tmp[8];
		double* fRec2 = &fRec2_tmp[4];
		int iZec0[4];
		double fZec1[4];
		int vindex = 0;
		/* Main loop */
		for (vindex = 0; vindex <= (faust_wrap_sub(count, 4)); vindex = faust_wrap_add(vindex, 4)) {
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			FAUSTFLOAT* output1 = &output1_ptr[vindex];
			FAUSTFLOAT* output2 = &output2_ptr[vindex];
			FAUSTFLOAT* output3 = &output3_ptr[vindex];
			int vsize = 4;
			/* Recursive loop 0 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				iRec0_tmp[j0] = iRec0_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iRec0[i] = faust_wrap_add(iRec0[faust_wrap_sub(i, 1)], 1);
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				iRec0_perm[j1] = iRec0_tmp[faust_wrap_add(vsize, j1)];
			}
			/* Vectorizable loop 1 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				itbl0[(faust_wrap_add(iRec0[i], 1)) % 10] = faust_wrap_mul(2, iRec0[i]);
				output0[i] = static_cast<FAUSTFLOAT>(itbl0[(faust_wrap_add(iRec0[i], 2)) % 10]);
			}
			/* Recursive loop 2 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fRec2_tmp[j2] = fRec2_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec2[i] = fRec2[faust_wrap_sub(i, 1)] + 0.1;
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fRec2_perm[j3] = fRec2_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				ftbl1[static_cast<int>(std::fmod(fRec2[i] + 1.0, 7.0))] = 1.24 * fRec2[i];
				output1[i] = static_cast<FAUSTFLOAT>(ftbl1[static_cast<int>(std::fmod(fRec2[i] + 2.0, 7.0))]);
			}
			/* Vectorizable loop 4 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec0[i] = imydspWave0[(faust_wrap_add(imydspWave0_idx, i)) % 7];
			}
			/* Post code */
			imydspWave0_idx = (faust_wrap_add(imydspWave0_idx, vsize)) % 7;
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				itbl2[(faust_wrap_add(iZec0[i], 1)) % 10] = static_cast<int>(1.24 * static_cast<double>(iZec0[i]));
				output2[i] = static_cast<FAUSTFLOAT>(itbl2[(faust_wrap_add(iZec0[i], 2)) % 10]);
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec1[i] = fmydspWave1[(faust_wrap_add(fmydspWave1_idx, i)) % 7];
			}
			/* Post code */
			fmydspWave1_idx = (faust_wrap_add(fmydspWave1_idx, vsize)) % 7;
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				ftbl3[static_cast<int>(std::fmod(fZec1[i] + 1.0, 7.0))] = 1.24 * fZec1[i];
				output3[i] = static_cast<FAUSTFLOAT>(ftbl3[static_cast<int>(std::fmod(fZec1[i] + 2.0, 7.0))]);
			}
		}
		/* Remaining frames */
		if (vindex < count) {
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			FAUSTFLOAT* output1 = &output1_ptr[vindex];
			FAUSTFLOAT* output2 = &output2_ptr[vindex];
			FAUSTFLOAT* output3 = &output3_ptr[vindex];
			int vsize = faust_wrap_sub(count, vindex);
			/* Recursive loop 0 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				iRec0_tmp[j0] = iRec0_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iRec0[i] = faust_wrap_add(iRec0[faust_wrap_sub(i, 1)], 1);
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				iRec0_perm[j1] = iRec0_tmp[faust_wrap_add(vsize, j1)];
			}
			/* Vectorizable loop 1 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				itbl0[(faust_wrap_add(iRec0[i], 1)) % 10] = faust_wrap_mul(2, iRec0[i]);
				output0[i] = static_cast<FAUSTFLOAT>(itbl0[(faust_wrap_add(iRec0[i], 2)) % 10]);
			}
			/* Recursive loop 2 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fRec2_tmp[j2] = fRec2_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec2[i] = fRec2[faust_wrap_sub(i, 1)] + 0.1;
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fRec2_perm[j3] = fRec2_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				ftbl1[static_cast<int>(std::fmod(fRec2[i] + 1.0, 7.0))] = 1.24 * fRec2[i];
				output1[i] = static_cast<FAUSTFLOAT>(ftbl1[static_cast<int>(std::fmod(fRec2[i] + 2.0, 7.0))]);
			}
			/* Vectorizable loop 4 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec0[i] = imydspWave0[(faust_wrap_add(imydspWave0_idx, i)) % 7];
			}
			/* Post code */
			imydspWave0_idx = (faust_wrap_add(imydspWave0_idx, vsize)) % 7;
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				itbl2[(faust_wrap_add(iZec0[i], 1)) % 10] = static_cast<int>(1.24 * static_cast<double>(iZec0[i]));
				output2[i] = static_cast<FAUSTFLOAT>(itbl2[(faust_wrap_add(iZec0[i], 2)) % 10]);
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec1[i] = fmydspWave1[(faust_wrap_add(fmydspWave1_idx, i)) % 7];
			}
			/* Post code */
			fmydspWave1_idx = (faust_wrap_add(fmydspWave1_idx, vsize)) % 7;
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				ftbl3[static_cast<int>(std::fmod(fZec1[i] + 1.0, 7.0))] = 1.24 * fZec1[i];
				output3[i] = static_cast<FAUSTFLOAT>(ftbl3[static_cast<int>(std::fmod(fZec1[i] + 2.0, 7.0))]);
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
