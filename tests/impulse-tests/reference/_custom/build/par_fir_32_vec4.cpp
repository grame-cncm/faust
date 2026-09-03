/* ------------------------------------------------------------
name: "par_fir_32"
version: "2.76.0"
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
	
	double fYec0[64];
	int fYec0_idx;
	int fYec0_idx_save;
	int fSampleRate;
	
 public:
	mydsp() {
	}
	
	mydsp(const mydsp&) = default;
	
	virtual ~mydsp() = default;
	
	mydsp& operator=(const mydsp&) = default;
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-single -scal -e par_fir_32.dsp -o par_fir_32_exp.dsp");
		m->declare("filename", "par_fir_32.dsp");
		m->declare("filters_lib_fir_author", "Julius O. Smith III");
		m->declare("filters_lib_fir_copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters_lib_fir_license", "MIT-style STK-4.3 license");
		m->declare("filters_lib_lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters_lib_name", "Faust Filters Library");
		m->declare("filters_lib_version", "1.5.0");
		m->declare("library_path0", "/usr/local/share/faust/stdfaust.lib");
		m->declare("library_path1", "/usr/local/share/faust/filters.lib");
		m->declare("name", "par_fir_32");
		m->declare("version", "2.76.0");
	}

	virtual int getNumInputs() {
		return 1;
	}
	virtual int getNumOutputs() {
		return 1;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
	}
	
	virtual void instanceResetUserInterface() {
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 64; l0 = faust_wrap_add(l0, 1)) {
			fYec0[l0] = 0.0;
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
		ui_interface->openVerticalBox("par_fir_32");
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0_ptr = inputs[0];
		FAUSTFLOAT* output0_ptr = outputs[0];
		int vindex = 0;
		/* Main loop */
		for (vindex = 0; vindex <= (faust_wrap_sub(count, 4)); vindex = faust_wrap_add(vindex, 4)) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			int vsize = 4;
			/* Vectorizable loop 0 */
			/* Pre code */
			fYec0_idx = (faust_wrap_add(fYec0_idx, fYec0_idx_save)) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec0[(faust_wrap_add(i, fYec0_idx)) & 63] = static_cast<double>(input0[i]);
			}
			/* Post code */
			fYec0_idx_save = vsize;
			/* Vectorizable loop 1 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(static_cast<double>(input0[i]) + 0.5 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 1)) & 63] + 0.33333334 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 2)) & 63] + 0.25 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 3)) & 63] + 0.2 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 4)) & 63] + 0.16666667 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 5)) & 63] + 0.14285715 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 6)) & 63] + 0.125 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 7)) & 63] + 0.11111111 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 8)) & 63] + 0.1 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 9)) & 63] + 0.09090909 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 10)) & 63] + 0.083333336 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 11)) & 63] + 0.07692308 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 12)) & 63] + 0.071428575 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 13)) & 63] + 0.06666667 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 14)) & 63] + 0.0625 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 15)) & 63] + 0.05882353 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 16)) & 63] + 0.055555556 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 17)) & 63] + 0.05263158 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 18)) & 63] + 0.05 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 19)) & 63] + 0.04761905 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 20)) & 63] + 0.045454547 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 21)) & 63] + 0.04347826 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 22)) & 63] + 0.041666668 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 23)) & 63] + 0.04 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 24)) & 63] + 0.03846154 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 25)) & 63] + 0.037037037 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 26)) & 63] + 0.035714287 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 27)) & 63] + 0.03448276 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 28)) & 63] + 0.033333335 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 29)) & 63] + 0.032258064 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 30)) & 63] + 0.03125 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 31)) & 63]);
			}
		}
		/* Remaining frames */
		if (vindex < count) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			int vsize = faust_wrap_sub(count, vindex);
			/* Vectorizable loop 0 */
			/* Pre code */
			fYec0_idx = (faust_wrap_add(fYec0_idx, fYec0_idx_save)) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec0[(faust_wrap_add(i, fYec0_idx)) & 63] = static_cast<double>(input0[i]);
			}
			/* Post code */
			fYec0_idx_save = vsize;
			/* Vectorizable loop 1 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(static_cast<double>(input0[i]) + 0.5 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 1)) & 63] + 0.33333334 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 2)) & 63] + 0.25 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 3)) & 63] + 0.2 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 4)) & 63] + 0.16666667 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 5)) & 63] + 0.14285715 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 6)) & 63] + 0.125 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 7)) & 63] + 0.11111111 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 8)) & 63] + 0.1 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 9)) & 63] + 0.09090909 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 10)) & 63] + 0.083333336 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 11)) & 63] + 0.07692308 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 12)) & 63] + 0.071428575 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 13)) & 63] + 0.06666667 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 14)) & 63] + 0.0625 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 15)) & 63] + 0.05882353 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 16)) & 63] + 0.055555556 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 17)) & 63] + 0.05263158 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 18)) & 63] + 0.05 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 19)) & 63] + 0.04761905 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 20)) & 63] + 0.045454547 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 21)) & 63] + 0.04347826 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 22)) & 63] + 0.041666668 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 23)) & 63] + 0.04 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 24)) & 63] + 0.03846154 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 25)) & 63] + 0.037037037 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 26)) & 63] + 0.035714287 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 27)) & 63] + 0.03448276 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 28)) & 63] + 0.033333335 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 29)) & 63] + 0.032258064 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 30)) & 63] + 0.03125 * fYec0[(faust_wrap_sub(faust_wrap_add(i, fYec0_idx), 31)) & 63]);
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
