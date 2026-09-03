/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2007"
license: "BSD"
name: "stereoecho"
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


class mydsp : public dsp {
	
 private:
	
	FAUSTFLOAT fHslider0;
	int fSampleRate;
	double fConst0;
	FAUSTFLOAT fHslider1;
	double fRec0[131072];
	int fRec0_idx;
	int fRec0_idx_save;
	double fRec1[131072];
	int fRec1_idx;
	int fRec1_idx_save;
	
 public:
	mydsp() {
	}
	
	mydsp(const mydsp&) = default;
	
	virtual ~mydsp() = default;
	
	mydsp& operator=(const mydsp&) = default;
	
	void metadata(Meta* m) { 
		m->declare("author", "Grame");
		m->declare("compile_options", "-a /Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/archs/impulsearch.cpp -lang cpp -i -fpga-mem-th 4 -ct 1 -es 1 -mcd 4 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs");
		m->declare("copyright", "(c)GRAME 2007");
		m->declare("filename", "stereoecho.dsp");
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
		m->declare("name", "stereoecho");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() {
		return 2;
	}
	virtual int getNumOutputs() {
		return 2;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = 0.001 * std::min<double>(1.92e+05, std::max<double>(1.0, static_cast<double>(fSampleRate)));
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(90.9);
		fHslider1 = static_cast<FAUSTFLOAT>(16.3);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 131072; l0 = faust_wrap_add(l0, 1)) {
			fRec0[l0] = 0.0;
		}
		fRec0_idx = 0;
		fRec0_idx_save = 0;
		for (int l1 = 0; l1 < 131072; l1 = faust_wrap_add(l1, 1)) {
			fRec1[l1] = 0.0;
		}
		fRec1_idx = 0;
		fRec1_idx_save = 0;
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
		ui_interface->openVerticalBox("stereo echo");
		ui_interface->openVerticalBox("echo 1000");
		ui_interface->addHorizontalSlider("feedback", &fHslider0, FAUSTFLOAT(90.9), FAUSTFLOAT(0.0), FAUSTFLOAT(1e+02), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("millisecond", &fHslider1, FAUSTFLOAT(16.3), FAUSTFLOAT(0.0), FAUSTFLOAT(1e+03), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0_ptr = inputs[0];
		FAUSTFLOAT* input1_ptr = inputs[1];
		FAUSTFLOAT* output0_ptr = outputs[0];
		FAUSTFLOAT* output1_ptr = outputs[1];
		double fSlow0 = 0.01 * static_cast<double>(fHslider0);
		int iSlow1 = faust_wrap_add((faust_wrap_add(static_cast<int>(fConst0 * static_cast<double>(fHslider1)), -1)) & 65535, 1);
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
			fRec0_idx = (faust_wrap_add(fRec0_idx, fRec0_idx_save)) & 131071;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec0[(faust_wrap_add(i, fRec0_idx)) & 131071] = static_cast<double>(input0[i]) + fSlow0 * fRec0[(faust_wrap_sub(faust_wrap_add(i, fRec0_idx), iSlow1)) & 131071];
			}
			/* Post code */
			fRec0_idx_save = vsize;
			/* Vectorizable loop 1 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fRec0[(faust_wrap_add(i, fRec0_idx)) & 131071]);
			}
			/* Recursive loop 2 */
			/* Pre code */
			fRec1_idx = (faust_wrap_add(fRec1_idx, fRec1_idx_save)) & 131071;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec1[(faust_wrap_add(i, fRec1_idx)) & 131071] = static_cast<double>(input1[i]) + fSlow0 * fRec1[(faust_wrap_sub(faust_wrap_add(i, fRec1_idx), iSlow1)) & 131071];
			}
			/* Post code */
			fRec1_idx_save = vsize;
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fRec1[(faust_wrap_add(i, fRec1_idx)) & 131071]);
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
			fRec0_idx = (faust_wrap_add(fRec0_idx, fRec0_idx_save)) & 131071;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec0[(faust_wrap_add(i, fRec0_idx)) & 131071] = static_cast<double>(input0[i]) + fSlow0 * fRec0[(faust_wrap_sub(faust_wrap_add(i, fRec0_idx), iSlow1)) & 131071];
			}
			/* Post code */
			fRec0_idx_save = vsize;
			/* Vectorizable loop 1 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fRec0[(faust_wrap_add(i, fRec0_idx)) & 131071]);
			}
			/* Recursive loop 2 */
			/* Pre code */
			fRec1_idx = (faust_wrap_add(fRec1_idx, fRec1_idx_save)) & 131071;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec1[(faust_wrap_add(i, fRec1_idx)) & 131071] = static_cast<double>(input1[i]) + fSlow0 * fRec1[(faust_wrap_sub(faust_wrap_add(i, fRec1_idx), iSlow1)) & 131071];
			}
			/* Post code */
			fRec1_idx_save = vsize;
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fRec1[(faust_wrap_add(i, fRec1_idx)) & 131071]);
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
