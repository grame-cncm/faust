/* ------------------------------------------------------------
name: "reverb_tester"
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
	
	int iRec1_perm[4];
	double fRec0_perm[4];
	FAUSTFLOAT fButton0;
	double fVec0_perm[4];
	FAUSTFLOAT fButton1;
	double fVec1_perm[4];
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fButton2;
	double fVec2_perm[4];
	int fSampleRate;
	
 public:
	mydsp() {
	}
	
	mydsp(const mydsp&) = default;
	
	virtual ~mydsp() = default;
	
	mydsp& operator=(const mydsp&) = default;
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-a /Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/archs/impulsearch.cpp -lang cpp -i -fpga-mem-th 4 -ct 1 -es 1 -mcd 4 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs");
		m->declare("effect.lib/name", "Faust Audio Effect Library");
		m->declare("filename", "reverb_tester.dsp");
		m->declare("filter.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("filter.lib/copyright", "Julius O. Smith III");
		m->declare("filter.lib/license", "STK-4.3");
		m->declare("filter.lib/name", "Faust Filter Library");
		m->declare("filter.lib/reference", "https://ccrma.stanford.edu/~jos/filters/");
		m->declare("filter.lib/version", "1.29");
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
		m->declare("name", "reverb_tester");
		m->declare("oscillator.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("oscillator.lib/copyright", "Julius O. Smith III");
		m->declare("oscillator.lib/license", "STK-4.3");
		m->declare("oscillator.lib/name", "Faust Oscillator Library");
		m->declare("oscillator.lib/version", "1.11");
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
	}
	
	virtual void instanceResetUserInterface() {
		fButton0 = static_cast<FAUSTFLOAT>(0.0);
		fButton1 = static_cast<FAUSTFLOAT>(0.0);
		fCheckbox0 = static_cast<FAUSTFLOAT>(0.0);
		fButton2 = static_cast<FAUSTFLOAT>(0.0);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 4; l0 = faust_wrap_add(l0, 1)) {
			iRec1_perm[l0] = 0;
		}
		for (int l1 = 0; l1 < 4; l1 = faust_wrap_add(l1, 1)) {
			fRec0_perm[l1] = 0.0;
		}
		for (int l2 = 0; l2 < 4; l2 = faust_wrap_add(l2, 1)) {
			fVec0_perm[l2] = 0.0;
		}
		for (int l3 = 0; l3 < 4; l3 = faust_wrap_add(l3, 1)) {
			fVec1_perm[l3] = 0.0;
		}
		for (int l4 = 0; l4 < 4; l4 = faust_wrap_add(l4, 1)) {
			fVec2_perm[l4] = 0.0;
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
		ui_interface->openHorizontalBox("Stereo Reverb Tester");
		ui_interface->declare(0, "1", "");
		ui_interface->openVerticalBox("Input Config");
		ui_interface->declare(&fCheckbox0, "2", "");
		ui_interface->declare(&fCheckbox0, "tooltip", "Pink Noise (or 1/f noise) is Constant-Q Noise (useful for adjusting the EQ sections)");
		ui_interface->addCheckButton("Pink Noise", &fCheckbox0);
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("Impulse Selection");
		ui_interface->declare(&fButton0, "1", "");
		ui_interface->declare(&fButton0, "tooltip", "Send impulse into LEFT channel");
		ui_interface->addButton("Left", &fButton0);
		ui_interface->declare(&fButton1, "2", "");
		ui_interface->declare(&fButton1, "tooltip", "Send impulse into LEFT and RIGHT channels");
		ui_interface->addButton("Center", &fButton1);
		ui_interface->declare(&fButton2, "3", "");
		ui_interface->declare(&fButton2, "tooltip", "Send impulse into RIGHT channel");
		ui_interface->addButton("Right", &fButton2);
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0_ptr = inputs[0];
		FAUSTFLOAT* input1_ptr = inputs[1];
		FAUSTFLOAT* output0_ptr = outputs[0];
		FAUSTFLOAT* output1_ptr = outputs[1];
		int iRec1_tmp[8];
		int* iRec1 = &iRec1_tmp[4];
		double fRec0_tmp[8];
		double* fRec0 = &fRec0_tmp[4];
		double fSlow0 = static_cast<double>(fButton0);
		double fVec0_tmp[8];
		double* fVec0 = &fVec0_tmp[4];
		double fSlow1 = static_cast<double>(fButton1);
		double fVec1_tmp[8];
		double* fVec1 = &fVec1_tmp[4];
		int iZec0[4];
		double fSlow2 = 0.1 * static_cast<double>(fCheckbox0);
		double fZec1[4];
		double fSlow3 = static_cast<double>(fButton2);
		double fVec2_tmp[8];
		double* fVec2 = &fVec2_tmp[4];
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
				iRec1_tmp[j0] = iRec1_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iRec1[i] = faust_wrap_add(faust_wrap_mul(1103515245, iRec1[faust_wrap_sub(i, 1)]), 12345);
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				iRec1_perm[j1] = iRec1_tmp[faust_wrap_add(vsize, j1)];
			}
			/* Recursive loop 1 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fRec0_tmp[j2] = fRec0_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec0[i] = 0.5221894 * fRec0[faust_wrap_sub(i, 3)] + 4.656612875245797e-10 * static_cast<double>(iRec1[i]) + 2.494956002 * fRec0[faust_wrap_sub(i, 1)] - 2.017265875 * fRec0[faust_wrap_sub(i, 2)];
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fRec0_perm[j3] = fRec0_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Vectorizable loop 2 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				fVec0_tmp[j4] = fVec0_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVec0[i] = fSlow0;
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fVec0_perm[j5] = fVec0_tmp[faust_wrap_add(vsize, j5)];
			}
			/* Vectorizable loop 3 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fVec1_tmp[j6] = fVec1_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVec1[i] = fSlow1;
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fVec1_perm[j7] = fVec1_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Vectorizable loop 4 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec0[i] = (fSlow1 - fVec1[faust_wrap_sub(i, 1)]) > 0.0;
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec1[i] = fSlow2 * (0.049922035 * fRec0[i] + 0.050612699 * fRec0[faust_wrap_sub(i, 2)] - (0.095993537 * fRec0[faust_wrap_sub(i, 1)] + 0.004408786 * fRec0[faust_wrap_sub(i, 3)]));
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(static_cast<double>(((fSlow0 - fVec0[faust_wrap_sub(i, 1)]) > 0.0) + iZec0[i]) + fZec1[i]);
			}
			/* Vectorizable loop 7 */
			/* Pre code */
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fVec2_tmp[j8] = fVec2_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVec2[i] = fSlow3;
			}
			/* Post code */
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fVec2_perm[j9] = fVec2_tmp[faust_wrap_add(vsize, j9)];
			}
			/* Vectorizable loop 8 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fZec1[i] + static_cast<double>(faust_wrap_add(iZec0[i], (fSlow3 - fVec2[faust_wrap_sub(i, 1)]) > 0.0)));
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
				iRec1_tmp[j0] = iRec1_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iRec1[i] = faust_wrap_add(faust_wrap_mul(1103515245, iRec1[faust_wrap_sub(i, 1)]), 12345);
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				iRec1_perm[j1] = iRec1_tmp[faust_wrap_add(vsize, j1)];
			}
			/* Recursive loop 1 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fRec0_tmp[j2] = fRec0_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec0[i] = 0.5221894 * fRec0[faust_wrap_sub(i, 3)] + 4.656612875245797e-10 * static_cast<double>(iRec1[i]) + 2.494956002 * fRec0[faust_wrap_sub(i, 1)] - 2.017265875 * fRec0[faust_wrap_sub(i, 2)];
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fRec0_perm[j3] = fRec0_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Vectorizable loop 2 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				fVec0_tmp[j4] = fVec0_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVec0[i] = fSlow0;
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fVec0_perm[j5] = fVec0_tmp[faust_wrap_add(vsize, j5)];
			}
			/* Vectorizable loop 3 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fVec1_tmp[j6] = fVec1_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVec1[i] = fSlow1;
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fVec1_perm[j7] = fVec1_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Vectorizable loop 4 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec0[i] = (fSlow1 - fVec1[faust_wrap_sub(i, 1)]) > 0.0;
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec1[i] = fSlow2 * (0.049922035 * fRec0[i] + 0.050612699 * fRec0[faust_wrap_sub(i, 2)] - (0.095993537 * fRec0[faust_wrap_sub(i, 1)] + 0.004408786 * fRec0[faust_wrap_sub(i, 3)]));
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(static_cast<double>(((fSlow0 - fVec0[faust_wrap_sub(i, 1)]) > 0.0) + iZec0[i]) + fZec1[i]);
			}
			/* Vectorizable loop 7 */
			/* Pre code */
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fVec2_tmp[j8] = fVec2_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVec2[i] = fSlow3;
			}
			/* Post code */
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fVec2_perm[j9] = fVec2_tmp[faust_wrap_add(vsize, j9)];
			}
			/* Vectorizable loop 8 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fZec1[i] + static_cast<double>(faust_wrap_add(iZec0[i], (fSlow3 - fVec2[faust_wrap_sub(i, 1)]) > 0.0)));
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
