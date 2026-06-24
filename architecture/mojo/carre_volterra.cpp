/* ------------------------------------------------------------
name: "carre_volterra"
Code generated with Faust 2.85.5 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 32
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

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

static double mydsp_faustpower2_f(double value) {
	return value * value;
}
static double mydsp_faustpower3_f(double value) {
	return value * value * value;
}

class mydsp : public dsp {
	
 private:
	
	int fSampleRate;
	double fConst0;
	double fConst1;
	FAUSTFLOAT fHslider0;
	double fRec4_perm[4];
	FAUSTFLOAT fHslider1;
	double fRec5_perm[4];
	double fConst2;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	double fConst3;
	int iVec0_perm[4];
	double fYec0_perm[4];
	double fYec1_perm[4];
	double fConst4;
	double fYec2[4096];
	int fYec2_idx;
	int fYec2_idx_save;
	double fYec3[4096];
	int fYec3_idx;
	int fYec3_idx_save;
	double fRec3_perm[4];
	double fRec2_perm[4];
	double fRec1_perm[4];
	double fRec0_perm[4];
	double fRec9_perm[4];
	double fRec8_perm[4];
	double fRec7_perm[4];
	double fRec6_perm[4];
	FAUSTFLOAT fCheckbox0;
	
 public:
	mydsp() {
	}
	
	mydsp(const mydsp&) = default;
	
	virtual ~mydsp() = default;
	
	mydsp& operator=(const mydsp&) = default;
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 32");
		m->declare("effect.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("effect.lib/copyright", "Julius O. Smith III");
		m->declare("effect.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m->declare("effect.lib/exciter_author", "Priyanka Shekar (pshekar@ccrma.stanford.edu)");
		m->declare("effect.lib/exciter_copyright", "Copyright (c) 2013 Priyanka Shekar");
		m->declare("effect.lib/exciter_license", "MIT License (MIT)");
		m->declare("effect.lib/exciter_name", "Harmonic Exciter");
		m->declare("effect.lib/exciter_version", "1.0");
		m->declare("effect.lib/license", "STK-4.3");
		m->declare("effect.lib/name", "Faust Audio Effect Library");
		m->declare("effect.lib/version", "1.33");
		m->declare("filename", "carre_volterra.dsp");
		m->declare("filter.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("filter.lib/copyright", "Julius O. Smith III");
		m->declare("filter.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
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
		m->declare("music.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m->declare("music.lib/license", "LGPL with exception");
		m->declare("music.lib/name", "Music Library");
		m->declare("music.lib/version", "1.0");
		m->declare("name", "carre_volterra");
		m->declare("oscillator.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("oscillator.lib/copyright", "Julius O. Smith III");
		m->declare("oscillator.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m->declare("oscillator.lib/license", "STK-4.3");
		m->declare("oscillator.lib/name", "Faust Oscillator Library");
		m->declare("oscillator.lib/version", "1.11");
	}

	virtual int getNumInputs() {
		return 0;
	}
	virtual int getNumOutputs() {
		return 1;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, static_cast<double>(fSampleRate)));
		fConst1 = 1.0 / fConst0;
		fConst2 = 6.283185307179586 / fConst0;
		fConst3 = 0.25 * fConst0;
		fConst4 = 0.5 * fConst0;
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(4.4e+02);
		fHslider1 = static_cast<FAUSTFLOAT>(2.0);
		fHslider2 = static_cast<FAUSTFLOAT>(7e+02);
		fHslider3 = static_cast<FAUSTFLOAT>(0.5);
		fCheckbox0 = static_cast<FAUSTFLOAT>(0.0);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 4; l0 = l0 + 1) {
			fRec4_perm[l0] = 0.0;
		}
		for (int l1 = 0; l1 < 4; l1 = l1 + 1) {
			fRec5_perm[l1] = 0.0;
		}
		for (int l2 = 0; l2 < 4; l2 = l2 + 1) {
			iVec0_perm[l2] = 0;
		}
		for (int l3 = 0; l3 < 4; l3 = l3 + 1) {
			fYec0_perm[l3] = 0.0;
		}
		for (int l4 = 0; l4 < 4; l4 = l4 + 1) {
			fYec1_perm[l4] = 0.0;
		}
		for (int l5 = 0; l5 < 4096; l5 = l5 + 1) {
			fYec2[l5] = 0.0;
		}
		fYec2_idx = 0;
		fYec2_idx_save = 0;
		for (int l6 = 0; l6 < 4096; l6 = l6 + 1) {
			fYec3[l6] = 0.0;
		}
		fYec3_idx = 0;
		fYec3_idx_save = 0;
		for (int l7 = 0; l7 < 4; l7 = l7 + 1) {
			fRec3_perm[l7] = 0.0;
		}
		for (int l8 = 0; l8 < 4; l8 = l8 + 1) {
			fRec2_perm[l8] = 0.0;
		}
		for (int l9 = 0; l9 < 4; l9 = l9 + 1) {
			fRec1_perm[l9] = 0.0;
		}
		for (int l10 = 0; l10 < 4; l10 = l10 + 1) {
			fRec0_perm[l10] = 0.0;
		}
		for (int l11 = 0; l11 < 4; l11 = l11 + 1) {
			fRec9_perm[l11] = 0.0;
		}
		for (int l12 = 0; l12 < 4; l12 = l12 + 1) {
			fRec8_perm[l12] = 0.0;
		}
		for (int l13 = 0; l13 < 4; l13 = l13 + 1) {
			fRec7_perm[l13] = 0.0;
		}
		for (int l14 = 0; l14 < 4; l14 = l14 + 1) {
			fRec6_perm[l14] = 0.0;
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
		ui_interface->openVerticalBox("carre_volterra");
		ui_interface->addCheckButton("NL", &fCheckbox0);
		ui_interface->addHorizontalSlider("delta", &fHslider1, FAUSTFLOAT(2.0), FAUSTFLOAT(0.0), FAUSTFLOAT(6.0), FAUSTFLOAT(0.1));
		ui_interface->addHorizontalSlider("freq carre", &fHslider0, FAUSTFLOAT(4.4e+02), FAUSTFLOAT(2e+01), FAUSTFLOAT(8e+03), FAUSTFLOAT(1.0));
		ui_interface->declare(&fHslider2, "unit", "Hz");
		ui_interface->addHorizontalSlider("freq", &fHslider2, FAUSTFLOAT(7e+02), FAUSTFLOAT(1.0), FAUSTFLOAT(2e+04), FAUSTFLOAT(1.0));
		ui_interface->addHorizontalSlider("level", &fHslider3, FAUSTFLOAT(0.5), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.01));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* output0_ptr = outputs[0];
		double fSlow0 = static_cast<double>(fHslider0);
		double fSlow1 = std::max<double>(fSlow0, 23.44894968246214);
		double fSlow2 = std::max<double>(2e+01, std::fabs(fSlow1));
		double fSlow3 = fConst1 * fSlow2;
		double fRec4_tmp[36];
		double* fRec4 = &fRec4_tmp[4];
		double fSlow4 = std::max<double>(fSlow0 + static_cast<double>(fHslider1), 23.44894968246214);
		double fSlow5 = std::max<double>(2e+01, std::fabs(fSlow4));
		double fSlow6 = fConst1 * fSlow5;
		double fRec5_tmp[36];
		double* fRec5 = &fRec5_tmp[4];
		double fSlow7 = static_cast<double>(fHslider2);
		double fSlow8 = fConst2 * fSlow7;
		double fSlow9 = 1.0 / (fSlow8 + 1.0);
		double fSlow10 = static_cast<double>(fHslider3);
		double fSlow11 = fConst2 * fSlow10 * fSlow7;
		int iVec0_tmp[36];
		int* iVec0 = &iVec0_tmp[4];
		double fZec0[32];
		double fSlow12 = 1.0 / fSlow2;
		double fYec0_tmp[36];
		double* fYec0 = &fYec0_tmp[4];
		double fZec1[32];
		double fSlow13 = 1.0 / fSlow5;
		double fYec1_tmp[36];
		double* fYec1 = &fYec1_tmp[4];
		double fZec2[32];
		double fSlow14 = std::max<double>(0.0, std::min<double>(2047.0, fConst4 / fSlow4));
		int iSlow15 = static_cast<int>(fSlow14);
		double fSlow16 = static_cast<double>(iSlow15);
		double fSlow17 = fSlow14 - fSlow16;
		double fSlow18 = fConst3 / fSlow5;
		int iSlow19 = iSlow15 + 1;
		double fSlow20 = std::max<double>(0.0, std::min<double>(2047.0, fConst4 / fSlow1));
		int iSlow21 = static_cast<int>(fSlow20);
		double fSlow22 = static_cast<double>(iSlow21);
		double fSlow23 = fSlow22 + (1.0 - fSlow20);
		double fSlow24 = fConst3 / fSlow2;
		double fSlow25 = fSlow20 - fSlow22;
		int iSlow26 = iSlow21 + 1;
		double fSlow27 = fSlow16 + (1.0 - fSlow14);
		double fZec3[32];
		double fRec3_tmp[36];
		double* fRec3 = &fRec3_tmp[4];
		double fRec2_tmp[36];
		double* fRec2 = &fRec2_tmp[4];
		double fRec1_tmp[36];
		double* fRec1 = &fRec1_tmp[4];
		double fRec0_tmp[36];
		double* fRec0 = &fRec0_tmp[4];
		double fZec4[32];
		double fRec9_tmp[36];
		double* fRec9 = &fRec9_tmp[4];
		double fZec5[32];
		double fRec8_tmp[36];
		double* fRec8 = &fRec8_tmp[4];
		double fZec6[32];
		double fRec7_tmp[36];
		double* fRec7 = &fRec7_tmp[4];
		double fRec6_tmp[36];
		double* fRec6 = &fRec6_tmp[4];
		double fSlow28 = 0.3333333333333333 * static_cast<double>(fCheckbox0);
		int vindex = 0;
		/* Main loop */
		for (vindex = 0; vindex <= (count - 32); vindex = vindex + 32) {
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			int vsize = 32;
			/* Recursive loop 0 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = j0 + 1) {
				fRec4_tmp[j0] = fRec4_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec4[i] = fSlow3 + (fRec4[i - 1] - std::floor(fSlow3 + fRec4[i - 1]));
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = j1 + 1) {
				fRec4_perm[j1] = fRec4_tmp[vsize + j1];
			}
			/* Recursive loop 1 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = j2 + 1) {
				fRec5_tmp[j2] = fRec5_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec5[i] = fSlow6 + (fRec5[i - 1] - std::floor(fSlow6 + fRec5[i - 1]));
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = j3 + 1) {
				fRec5_perm[j3] = fRec5_tmp[vsize + j3];
			}
			/* Vectorizable loop 2 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = j4 + 1) {
				iVec0_tmp[j4] = iVec0_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				iVec0[i] = 1;
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = j5 + 1) {
				iVec0_perm[j5] = iVec0_tmp[vsize + j5];
			}
			/* Vectorizable loop 3 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = j6 + 1) {
				fYec0_tmp[j6] = fYec0_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec0[i] = mydsp_faustpower2_f(2.0 * fRec4[i] + -1.0);
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = j7 + 1) {
				fYec0_perm[j7] = fYec0_tmp[vsize + j7];
			}
			/* Vectorizable loop 4 */
			/* Pre code */
			for (int j8 = 0; j8 < 4; j8 = j8 + 1) {
				fYec1_tmp[j8] = fYec1_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec1[i] = mydsp_faustpower2_f(2.0 * fRec5[i] + -1.0);
			}
			/* Post code */
			for (int j9 = 0; j9 < 4; j9 = j9 + 1) {
				fYec1_perm[j9] = fYec1_tmp[vsize + j9];
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec0[i] = static_cast<double>(iVec0[i - 1]);
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec1[i] = fYec0[i] - fYec0[i - 1];
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec2[i] = fYec1[i] - fYec1[i - 1];
			}
			/* Vectorizable loop 8 */
			/* Pre code */
			fYec2_idx = (fYec2_idx + fYec2_idx_save) & 4095;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec2[(i + fYec2_idx) & 4095] = fSlow18 * fZec0[i] * fZec2[i];
			}
			/* Post code */
			fYec2_idx_save = vsize;
			/* Vectorizable loop 9 */
			/* Pre code */
			fYec3_idx = (fYec3_idx + fYec3_idx_save) & 4095;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec3[(i + fYec3_idx) & 4095] = fSlow24 * fZec0[i] * fZec1[i];
			}
			/* Post code */
			fYec3_idx_save = vsize;
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec3[i] = fConst3 * fZec0[i] * (fSlow12 * fZec1[i] + fSlow13 * fZec2[i]) - (fSlow17 * fYec2[(i + fYec2_idx - iSlow19) & 4095] + fSlow23 * fYec3[(i + fYec3_idx - iSlow21) & 4095] + fSlow25 * fYec3[(i + fYec3_idx - iSlow26) & 4095] + fSlow27 * fYec2[(i + fYec2_idx - iSlow15) & 4095]);
			}
			/* Recursive loop 11 */
			/* Pre code */
			for (int j10 = 0; j10 < 4; j10 = j10 + 1) {
				fRec3_tmp[j10] = fRec3_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec3[i] = fSlow9 * (fRec3[i - 1] + fSlow11 * fZec3[i]);
			}
			/* Post code */
			for (int j11 = 0; j11 < 4; j11 = j11 + 1) {
				fRec3_perm[j11] = fRec3_tmp[vsize + j11];
			}
			/* Recursive loop 12 */
			/* Pre code */
			for (int j12 = 0; j12 < 4; j12 = j12 + 1) {
				fRec2_tmp[j12] = fRec2_perm[j12];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec2[i] = fSlow9 * (fRec2[i - 1] + fSlow8 * fRec3[i]);
			}
			/* Post code */
			for (int j13 = 0; j13 < 4; j13 = j13 + 1) {
				fRec2_perm[j13] = fRec2_tmp[vsize + j13];
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec4[i] = mydsp_faustpower3_f(fRec3[i]);
			}
			/* Recursive loop 14 */
			/* Pre code */
			for (int j14 = 0; j14 < 4; j14 = j14 + 1) {
				fRec1_tmp[j14] = fRec1_perm[j14];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec1[i] = fSlow9 * (fRec1[i - 1] + fSlow8 * fRec2[i]);
			}
			/* Post code */
			for (int j15 = 0; j15 < 4; j15 = j15 + 1) {
				fRec1_perm[j15] = fRec1_tmp[vsize + j15];
			}
			/* Recursive loop 15 */
			/* Pre code */
			for (int j18 = 0; j18 < 4; j18 = j18 + 1) {
				fRec9_tmp[j18] = fRec9_perm[j18];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec9[i] = fSlow9 * (fRec9[i - 1] + fSlow8 * (mydsp_faustpower3_f(fSlow10 * fZec3[i]) - fZec4[i]));
			}
			/* Post code */
			for (int j19 = 0; j19 < 4; j19 = j19 + 1) {
				fRec9_perm[j19] = fRec9_tmp[vsize + j19];
			}
			/* Vectorizable loop 16 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec5[i] = mydsp_faustpower3_f(fRec2[i]);
			}
			/* Recursive loop 17 */
			/* Pre code */
			for (int j20 = 0; j20 < 4; j20 = j20 + 1) {
				fRec8_tmp[j20] = fRec8_perm[j20];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec8[i] = fSlow9 * (fRec8[i - 1] + fSlow8 * (fRec9[i] + fZec4[i] - fZec5[i]));
			}
			/* Post code */
			for (int j21 = 0; j21 < 4; j21 = j21 + 1) {
				fRec8_perm[j21] = fRec8_tmp[vsize + j21];
			}
			/* Vectorizable loop 18 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec6[i] = mydsp_faustpower3_f(fRec1[i]);
			}
			/* Recursive loop 19 */
			/* Pre code */
			for (int j16 = 0; j16 < 4; j16 = j16 + 1) {
				fRec0_tmp[j16] = fRec0_perm[j16];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec0[i] = fSlow9 * (fRec0[i - 1] + fSlow8 * fRec1[i]);
			}
			/* Post code */
			for (int j17 = 0; j17 < 4; j17 = j17 + 1) {
				fRec0_perm[j17] = fRec0_tmp[vsize + j17];
			}
			/* Recursive loop 20 */
			/* Pre code */
			for (int j22 = 0; j22 < 4; j22 = j22 + 1) {
				fRec7_tmp[j22] = fRec7_perm[j22];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec7[i] = fSlow9 * (fRec7[i - 1] + fSlow8 * (fRec8[i] + fZec5[i] - fZec6[i]));
			}
			/* Post code */
			for (int j23 = 0; j23 < 4; j23 = j23 + 1) {
				fRec7_perm[j23] = fRec7_tmp[vsize + j23];
			}
			/* Recursive loop 21 */
			/* Pre code */
			for (int j24 = 0; j24 < 4; j24 = j24 + 1) {
				fRec6_tmp[j24] = fRec6_perm[j24];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec6[i] = fSlow9 * (fRec6[i - 1] + fSlow8 * (fRec7[i] + fZec6[i] - mydsp_faustpower3_f(fRec0[i])));
			}
			/* Post code */
			for (int j25 = 0; j25 < 4; j25 = j25 + 1) {
				fRec6_perm[j25] = fRec6_tmp[vsize + j25];
			}
			/* Vectorizable loop 22 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				output0[i] = static_cast<FAUSTFLOAT>(fRec0[i] - fSlow28 * fRec6[i]);
			}
		}
		/* Remaining frames */
		if (vindex < count) {
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			int vsize = count - vindex;
			/* Recursive loop 0 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = j0 + 1) {
				fRec4_tmp[j0] = fRec4_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec4[i] = fSlow3 + (fRec4[i - 1] - std::floor(fSlow3 + fRec4[i - 1]));
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = j1 + 1) {
				fRec4_perm[j1] = fRec4_tmp[vsize + j1];
			}
			/* Recursive loop 1 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = j2 + 1) {
				fRec5_tmp[j2] = fRec5_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec5[i] = fSlow6 + (fRec5[i - 1] - std::floor(fSlow6 + fRec5[i - 1]));
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = j3 + 1) {
				fRec5_perm[j3] = fRec5_tmp[vsize + j3];
			}
			/* Vectorizable loop 2 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = j4 + 1) {
				iVec0_tmp[j4] = iVec0_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				iVec0[i] = 1;
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = j5 + 1) {
				iVec0_perm[j5] = iVec0_tmp[vsize + j5];
			}
			/* Vectorizable loop 3 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = j6 + 1) {
				fYec0_tmp[j6] = fYec0_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec0[i] = mydsp_faustpower2_f(2.0 * fRec4[i] + -1.0);
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = j7 + 1) {
				fYec0_perm[j7] = fYec0_tmp[vsize + j7];
			}
			/* Vectorizable loop 4 */
			/* Pre code */
			for (int j8 = 0; j8 < 4; j8 = j8 + 1) {
				fYec1_tmp[j8] = fYec1_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec1[i] = mydsp_faustpower2_f(2.0 * fRec5[i] + -1.0);
			}
			/* Post code */
			for (int j9 = 0; j9 < 4; j9 = j9 + 1) {
				fYec1_perm[j9] = fYec1_tmp[vsize + j9];
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec0[i] = static_cast<double>(iVec0[i - 1]);
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec1[i] = fYec0[i] - fYec0[i - 1];
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec2[i] = fYec1[i] - fYec1[i - 1];
			}
			/* Vectorizable loop 8 */
			/* Pre code */
			fYec2_idx = (fYec2_idx + fYec2_idx_save) & 4095;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec2[(i + fYec2_idx) & 4095] = fSlow18 * fZec0[i] * fZec2[i];
			}
			/* Post code */
			fYec2_idx_save = vsize;
			/* Vectorizable loop 9 */
			/* Pre code */
			fYec3_idx = (fYec3_idx + fYec3_idx_save) & 4095;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec3[(i + fYec3_idx) & 4095] = fSlow24 * fZec0[i] * fZec1[i];
			}
			/* Post code */
			fYec3_idx_save = vsize;
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec3[i] = fConst3 * fZec0[i] * (fSlow12 * fZec1[i] + fSlow13 * fZec2[i]) - (fSlow17 * fYec2[(i + fYec2_idx - iSlow19) & 4095] + fSlow23 * fYec3[(i + fYec3_idx - iSlow21) & 4095] + fSlow25 * fYec3[(i + fYec3_idx - iSlow26) & 4095] + fSlow27 * fYec2[(i + fYec2_idx - iSlow15) & 4095]);
			}
			/* Recursive loop 11 */
			/* Pre code */
			for (int j10 = 0; j10 < 4; j10 = j10 + 1) {
				fRec3_tmp[j10] = fRec3_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec3[i] = fSlow9 * (fRec3[i - 1] + fSlow11 * fZec3[i]);
			}
			/* Post code */
			for (int j11 = 0; j11 < 4; j11 = j11 + 1) {
				fRec3_perm[j11] = fRec3_tmp[vsize + j11];
			}
			/* Recursive loop 12 */
			/* Pre code */
			for (int j12 = 0; j12 < 4; j12 = j12 + 1) {
				fRec2_tmp[j12] = fRec2_perm[j12];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec2[i] = fSlow9 * (fRec2[i - 1] + fSlow8 * fRec3[i]);
			}
			/* Post code */
			for (int j13 = 0; j13 < 4; j13 = j13 + 1) {
				fRec2_perm[j13] = fRec2_tmp[vsize + j13];
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec4[i] = mydsp_faustpower3_f(fRec3[i]);
			}
			/* Recursive loop 14 */
			/* Pre code */
			for (int j14 = 0; j14 < 4; j14 = j14 + 1) {
				fRec1_tmp[j14] = fRec1_perm[j14];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec1[i] = fSlow9 * (fRec1[i - 1] + fSlow8 * fRec2[i]);
			}
			/* Post code */
			for (int j15 = 0; j15 < 4; j15 = j15 + 1) {
				fRec1_perm[j15] = fRec1_tmp[vsize + j15];
			}
			/* Recursive loop 15 */
			/* Pre code */
			for (int j18 = 0; j18 < 4; j18 = j18 + 1) {
				fRec9_tmp[j18] = fRec9_perm[j18];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec9[i] = fSlow9 * (fRec9[i - 1] + fSlow8 * (mydsp_faustpower3_f(fSlow10 * fZec3[i]) - fZec4[i]));
			}
			/* Post code */
			for (int j19 = 0; j19 < 4; j19 = j19 + 1) {
				fRec9_perm[j19] = fRec9_tmp[vsize + j19];
			}
			/* Vectorizable loop 16 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec5[i] = mydsp_faustpower3_f(fRec2[i]);
			}
			/* Recursive loop 17 */
			/* Pre code */
			for (int j20 = 0; j20 < 4; j20 = j20 + 1) {
				fRec8_tmp[j20] = fRec8_perm[j20];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec8[i] = fSlow9 * (fRec8[i - 1] + fSlow8 * (fRec9[i] + fZec4[i] - fZec5[i]));
			}
			/* Post code */
			for (int j21 = 0; j21 < 4; j21 = j21 + 1) {
				fRec8_perm[j21] = fRec8_tmp[vsize + j21];
			}
			/* Vectorizable loop 18 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec6[i] = mydsp_faustpower3_f(fRec1[i]);
			}
			/* Recursive loop 19 */
			/* Pre code */
			for (int j16 = 0; j16 < 4; j16 = j16 + 1) {
				fRec0_tmp[j16] = fRec0_perm[j16];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec0[i] = fSlow9 * (fRec0[i - 1] + fSlow8 * fRec1[i]);
			}
			/* Post code */
			for (int j17 = 0; j17 < 4; j17 = j17 + 1) {
				fRec0_perm[j17] = fRec0_tmp[vsize + j17];
			}
			/* Recursive loop 20 */
			/* Pre code */
			for (int j22 = 0; j22 < 4; j22 = j22 + 1) {
				fRec7_tmp[j22] = fRec7_perm[j22];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec7[i] = fSlow9 * (fRec7[i - 1] + fSlow8 * (fRec8[i] + fZec5[i] - fZec6[i]));
			}
			/* Post code */
			for (int j23 = 0; j23 < 4; j23 = j23 + 1) {
				fRec7_perm[j23] = fRec7_tmp[vsize + j23];
			}
			/* Recursive loop 21 */
			/* Pre code */
			for (int j24 = 0; j24 < 4; j24 = j24 + 1) {
				fRec6_tmp[j24] = fRec6_perm[j24];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec6[i] = fSlow9 * (fRec6[i - 1] + fSlow8 * (fRec7[i] + fZec6[i] - mydsp_faustpower3_f(fRec0[i])));
			}
			/* Post code */
			for (int j25 = 0; j25 < 4; j25 = j25 + 1) {
				fRec6_perm[j25] = fRec6_tmp[vsize + j25];
			}
			/* Vectorizable loop 22 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				output0[i] = static_cast<FAUSTFLOAT>(fRec0[i] - fSlow28 * fRec6[i]);
			}
		}
	}

};

#endif
