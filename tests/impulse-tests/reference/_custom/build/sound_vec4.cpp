/* ------------------------------------------------------------
name: "sound"
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
	
	Soundfile* fSoundfile0;
	int iRec0_perm[4];
	int fSampleRate;
	
	void allocate() {
		fSoundfile0 = 0;
	}
	
 public:
	mydsp() {
		allocate();
	}
	
	mydsp(const mydsp&) = default;
	
	virtual ~mydsp() = default;
	
	mydsp& operator=(const mydsp&) = default;
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-a /Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/archs/impulsearch.cpp -lang cpp -i -fpga-mem-th 4 -ct 1 -es 1 -mcd 4 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs");
		m->declare("filename", "sound.dsp");
		m->declare("name", "sound");
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
	}
	
	virtual void instanceResetUserInterface() {
		if (reinterpret_cast<uintptr_t>(fSoundfile0) == 0) {
			fSoundfile0 = defaultsound;
		}
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 4; l0 = faust_wrap_add(l0, 1)) {
			iRec0_perm[l0] = 0;
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
		ui_interface->openVerticalBox("sound");
		ui_interface->addSoundfile("son", "{'sound1';'sound2'}", &fSoundfile0);
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* output0_ptr = outputs[0];
		FAUSTFLOAT* output1_ptr = outputs[1];
		FAUSTFLOAT* output2_ptr = outputs[2];
		FAUSTFLOAT* output3_ptr = outputs[3];
		int iRec0_tmp[8];
		int* iRec0 = &iRec0_tmp[4];
		Soundfile* fSoundfile0ca = fSoundfile0;
		int* fSoundfile0ca_le0 = fSoundfile0ca->fLength;
		int iSlow0 = faust_wrap_add(fSoundfile0ca_le0[0], -1);
		int iZec0[4];
		int* fSoundfile0ca_of0 = fSoundfile0ca->fOffset;
		double** fSoundfile0ca_bu0 = static_cast<double**>(fSoundfile0ca->fBuffers);
		double* fSoundfile0ca_bu_ch0 = fSoundfile0ca_bu0[0];
		int* fSoundfile0ca_of1 = fSoundfile0ca->fOffset;
		double** fSoundfile0ca_bu1 = static_cast<double**>(fSoundfile0ca->fBuffers);
		double* fSoundfile0ca_bu_ch1 = fSoundfile0ca_bu1[1];
		int* fSoundfile0ca_of2 = fSoundfile0ca->fOffset;
		double** fSoundfile0ca_bu2 = static_cast<double**>(fSoundfile0ca->fBuffers);
		double* fSoundfile0ca_bu_ch2 = fSoundfile0ca_bu2[2];
		int* fSoundfile0ca_of3 = fSoundfile0ca->fOffset;
		double** fSoundfile0ca_bu3 = static_cast<double**>(fSoundfile0ca->fBuffers);
		double* fSoundfile0ca_bu_ch3 = fSoundfile0ca_bu3[3];
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
				iZec0[i] = std::max<int>(0, std::min<int>(iRec0[i], iSlow0));
			}
			/* Vectorizable loop 2 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fSoundfile0ca_bu_ch0[faust_wrap_add(fSoundfile0ca_of0[0], iZec0[i])]);
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fSoundfile0ca_bu_ch1[faust_wrap_add(fSoundfile0ca_of1[0], iZec0[i])]);
			}
			/* Vectorizable loop 4 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output2[i] = static_cast<FAUSTFLOAT>(fSoundfile0ca_bu_ch2[faust_wrap_add(fSoundfile0ca_of2[0], iZec0[i])]);
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output3[i] = static_cast<FAUSTFLOAT>(fSoundfile0ca_bu_ch3[faust_wrap_add(fSoundfile0ca_of3[0], iZec0[i])]);
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
				iZec0[i] = std::max<int>(0, std::min<int>(iRec0[i], iSlow0));
			}
			/* Vectorizable loop 2 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fSoundfile0ca_bu_ch0[faust_wrap_add(fSoundfile0ca_of0[0], iZec0[i])]);
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fSoundfile0ca_bu_ch1[faust_wrap_add(fSoundfile0ca_of1[0], iZec0[i])]);
			}
			/* Vectorizable loop 4 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output2[i] = static_cast<FAUSTFLOAT>(fSoundfile0ca_bu_ch2[faust_wrap_add(fSoundfile0ca_of2[0], iZec0[i])]);
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output3[i] = static_cast<FAUSTFLOAT>(fSoundfile0ca_bu_ch3[faust_wrap_add(fSoundfile0ca_of3[0], iZec0[i])]);
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
