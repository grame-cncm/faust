/* ------------------------------------------------------------
name: "delays"
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
	
	double fYec0[1024];
	int fYec0_idx;
	int fYec0_idx_save;
	FAUSTFLOAT fEntry0;
	double fRec0_perm[4];
	double fYec1[2048];
	int fYec1_idx;
	int fYec1_idx_save;
	FAUSTFLOAT fEntry1;
	double fRec1_perm[4];
	double fYec2[4096];
	int fYec2_idx;
	int fYec2_idx_save;
	FAUSTFLOAT fEntry2;
	double fRec2_perm[4];
	int fSampleRate;
	
 public:
	mydsp() {
	}
	
	mydsp(const mydsp&) = default;
	
	virtual ~mydsp() = default;
	
	mydsp& operator=(const mydsp&) = default;
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-a /Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/archs/impulsearch.cpp -lang cpp -i -fpga-mem-th 4 -ct 1 -es 1 -mcd 4 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs");
		m->declare("filename", "delays.dsp");
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
		m->declare("name", "delays");
	}

	virtual int getNumInputs() {
		return 3;
	}
	virtual int getNumOutputs() {
		return 3;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
	}
	
	virtual void instanceResetUserInterface() {
		fEntry0 = static_cast<FAUSTFLOAT>(2e+02);
		fEntry1 = static_cast<FAUSTFLOAT>(2e+02);
		fEntry2 = static_cast<FAUSTFLOAT>(4e+02);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 1024; l0 = faust_wrap_add(l0, 1)) {
			fYec0[l0] = 0.0;
		}
		fYec0_idx = 0;
		fYec0_idx_save = 0;
		for (int l1 = 0; l1 < 4; l1 = faust_wrap_add(l1, 1)) {
			fRec0_perm[l1] = 0.0;
		}
		for (int l2 = 0; l2 < 2048; l2 = faust_wrap_add(l2, 1)) {
			fYec1[l2] = 0.0;
		}
		fYec1_idx = 0;
		fYec1_idx_save = 0;
		for (int l3 = 0; l3 < 4; l3 = faust_wrap_add(l3, 1)) {
			fRec1_perm[l3] = 0.0;
		}
		for (int l4 = 0; l4 < 4096; l4 = faust_wrap_add(l4, 1)) {
			fYec2[l4] = 0.0;
		}
		fYec2_idx = 0;
		fYec2_idx_save = 0;
		for (int l5 = 0; l5 < 4; l5 = faust_wrap_add(l5, 1)) {
			fRec2_perm[l5] = 0.0;
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
		ui_interface->openVerticalBox("delays");
		ui_interface->addNumEntry("d1", &fEntry0, FAUSTFLOAT(2e+02), FAUSTFLOAT(0.0), FAUSTFLOAT(1e+03), FAUSTFLOAT(1.0));
		ui_interface->addNumEntry("d2", &fEntry1, FAUSTFLOAT(2e+02), FAUSTFLOAT(0.0), FAUSTFLOAT(2e+03), FAUSTFLOAT(1.0));
		ui_interface->addNumEntry("d3", &fEntry2, FAUSTFLOAT(4e+02), FAUSTFLOAT(2e+02), FAUSTFLOAT(3e+03), FAUSTFLOAT(1.0));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0_ptr = inputs[0];
		FAUSTFLOAT* input1_ptr = inputs[1];
		FAUSTFLOAT* input2_ptr = inputs[2];
		FAUSTFLOAT* output0_ptr = outputs[0];
		FAUSTFLOAT* output1_ptr = outputs[1];
		FAUSTFLOAT* output2_ptr = outputs[2];
		int iSlow0 = static_cast<int>(static_cast<double>(fEntry0));
		double fRec0_tmp[8];
		double* fRec0 = &fRec0_tmp[4];
		int iSlow1 = static_cast<int>(static_cast<double>(fEntry1));
		double fRec1_tmp[8];
		double* fRec1 = &fRec1_tmp[4];
		int iSlow2 = static_cast<int>(static_cast<double>(fEntry2));
		double fRec2_tmp[8];
		double* fRec2 = &fRec2_tmp[4];
		int vindex = 0;
		/* Main loop */
		for (vindex = 0; vindex <= (faust_wrap_sub(count, 4)); vindex = faust_wrap_add(vindex, 4)) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* input1 = &input1_ptr[vindex];
			FAUSTFLOAT* input2 = &input2_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			FAUSTFLOAT* output1 = &output1_ptr[vindex];
			FAUSTFLOAT* output2 = &output2_ptr[vindex];
			int vsize = 4;
			/* Vectorizable loop 0 */
			/* Pre code */
			fYec0_idx = (faust_wrap_add(fYec0_idx, fYec0_idx_save)) & 1023;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec0[(faust_wrap_add(i, fYec0_idx)) & 1023] = static_cast<double>(input0[i]);
			}
			/* Post code */
			fYec0_idx_save = vsize;
			/* Recursive loop 1 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				fRec0_tmp[j0] = fRec0_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec0[i] = 0.999 * fRec0[faust_wrap_sub(i, 1)] + 0.0010000000000000009 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), iSlow0)) & 1023];
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				fRec0_perm[j1] = fRec0_tmp[faust_wrap_add(vsize, j1)];
			}
			/* Vectorizable loop 2 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fRec0[i]);
			}
			/* Vectorizable loop 3 */
			/* Pre code */
			fYec1_idx = (faust_wrap_add(fYec1_idx, fYec1_idx_save)) & 2047;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec1[(faust_wrap_add(i, fYec1_idx)) & 2047] = static_cast<double>(input1[i]);
			}
			/* Post code */
			fYec1_idx_save = vsize;
			/* Recursive loop 4 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fRec1_tmp[j2] = fRec1_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec1[i] = 0.999 * fRec1[faust_wrap_sub(i, 1)] + 0.0010000000000000009 * fYec1[(faust_wrap_sub(faust_wrap_add(i, fYec1_idx), iSlow1)) & 2047];
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fRec1_perm[j3] = fRec1_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fRec1[i]);
			}
			/* Vectorizable loop 6 */
			/* Pre code */
			fYec2_idx = (faust_wrap_add(fYec2_idx, fYec2_idx_save)) & 4095;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec2[(faust_wrap_add(i, fYec2_idx)) & 4095] = static_cast<double>(input2[i]);
			}
			/* Post code */
			fYec2_idx_save = vsize;
			/* Recursive loop 7 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				fRec2_tmp[j4] = fRec2_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec2[i] = 0.999 * fRec2[faust_wrap_sub(i, 1)] + 0.0010000000000000009 * fYec2[(faust_wrap_sub(faust_wrap_add(i, fYec2_idx), iSlow2)) & 4095];
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fRec2_perm[j5] = fRec2_tmp[faust_wrap_add(vsize, j5)];
			}
			/* Vectorizable loop 8 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output2[i] = static_cast<FAUSTFLOAT>(fRec2[i]);
			}
		}
		/* Remaining frames */
		if (vindex < count) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* input1 = &input1_ptr[vindex];
			FAUSTFLOAT* input2 = &input2_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			FAUSTFLOAT* output1 = &output1_ptr[vindex];
			FAUSTFLOAT* output2 = &output2_ptr[vindex];
			int vsize = faust_wrap_sub(count, vindex);
			/* Vectorizable loop 0 */
			/* Pre code */
			fYec0_idx = (faust_wrap_add(fYec0_idx, fYec0_idx_save)) & 1023;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec0[(faust_wrap_add(i, fYec0_idx)) & 1023] = static_cast<double>(input0[i]);
			}
			/* Post code */
			fYec0_idx_save = vsize;
			/* Recursive loop 1 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				fRec0_tmp[j0] = fRec0_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec0[i] = 0.999 * fRec0[faust_wrap_sub(i, 1)] + 0.0010000000000000009 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), iSlow0)) & 1023];
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				fRec0_perm[j1] = fRec0_tmp[faust_wrap_add(vsize, j1)];
			}
			/* Vectorizable loop 2 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fRec0[i]);
			}
			/* Vectorizable loop 3 */
			/* Pre code */
			fYec1_idx = (faust_wrap_add(fYec1_idx, fYec1_idx_save)) & 2047;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec1[(faust_wrap_add(i, fYec1_idx)) & 2047] = static_cast<double>(input1[i]);
			}
			/* Post code */
			fYec1_idx_save = vsize;
			/* Recursive loop 4 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fRec1_tmp[j2] = fRec1_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec1[i] = 0.999 * fRec1[faust_wrap_sub(i, 1)] + 0.0010000000000000009 * fYec1[(faust_wrap_sub(faust_wrap_add(i, fYec1_idx), iSlow1)) & 2047];
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fRec1_perm[j3] = fRec1_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fRec1[i]);
			}
			/* Vectorizable loop 6 */
			/* Pre code */
			fYec2_idx = (faust_wrap_add(fYec2_idx, fYec2_idx_save)) & 4095;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec2[(faust_wrap_add(i, fYec2_idx)) & 4095] = static_cast<double>(input2[i]);
			}
			/* Post code */
			fYec2_idx_save = vsize;
			/* Recursive loop 7 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				fRec2_tmp[j4] = fRec2_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec2[i] = 0.999 * fRec2[faust_wrap_sub(i, 1)] + 0.0010000000000000009 * fYec2[(faust_wrap_sub(faust_wrap_add(i, fYec2_idx), iSlow2)) & 4095];
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fRec2_perm[j5] = fRec2_tmp[faust_wrap_add(vsize, j5)];
			}
			/* Vectorizable loop 8 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output2[i] = static_cast<FAUSTFLOAT>(fRec2[i]);
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
