/* ------------------------------------------------------------
name: "echo_bug"
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
	
	double fRec1[2048];
	int fRec1_idx;
	int fRec1_idx_save;
	FAUSTFLOAT fHslider0;
	int fSampleRate;
	
 public:
	mydsp() {
	}
	
	mydsp(const mydsp&) = default;
	
	virtual ~mydsp() = default;
	
	mydsp& operator=(const mydsp&) = default;
	
	void metadata(Meta* m) { 
		m->declare("analyzers_lib_name", "Faust Analyzer Library");
		m->declare("analyzers_lib_version", "0.0");
		m->declare("basics_lib_name", "Faust Basic Element Library");
		m->declare("basics_lib_version", "0.0");
		m->declare("compilation_options", "-single -scal -e echo_bug.dsp -o echo_bug.dsp");
		m->declare("compile_options", "-a /Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/archs/impulsearch.cpp -lang cpp -i -fpga-mem-th 4 -ct 1 -es 1 -mcd 4 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs");
		m->declare("compressors_lib_name", "Faust Compressor Effect Library");
		m->declare("compressors_lib_version", "0.0");
		m->declare("delays_lib_name", "Faust Delay Library");
		m->declare("delays_lib_version", "0.1");
		m->declare("envelopes_lib_author", "GRAME");
		m->declare("envelopes_lib_copyright", "GRAME");
		m->declare("envelopes_lib_license", "LGPL with exception");
		m->declare("envelopes_lib_name", "Faust Envelope Library");
		m->declare("envelopes_lib_version", "0.0");
		m->declare("filename", "echo_bug.dsp");
		m->declare("filters_lib_name", "Faust Filters Library");
		m->declare("filters_lib_version", "0.0");
		m->declare("hoa_lib_author", "Pierre Guillot");
		m->declare("hoa_lib_copyright", "2012-2013 Guillot, Paris, Colafrancesco, CICM labex art H2H, U. Paris 8");
		m->declare("hoa_lib_name", "High Order Ambisonics library");
		m->declare("library_path", "/usr/local/share/faust/sf.lib");
		m->declare("maths_lib_author", "GRAME");
		m->declare("maths_lib_copyright", "GRAME");
		m->declare("maths_lib_license", "LGPL with exception");
		m->declare("maths_lib_name", "Faust Math Library");
		m->declare("maths_lib_version", "2.1");
		m->declare("misceffects_lib_name", "Faust Math Library");
		m->declare("misceffects_lib_version", "2.0");
		m->declare("name", "echo_bug");
		m->declare("noises_lib_name", "Faust Noise Generator Library");
		m->declare("noises_lib_version", "0.0");
		m->declare("oscillators_lib_name", "Faust Oscillator Library");
		m->declare("oscillators_lib_version", "0.0");
		m->declare("phaflangers_lib_name", "Faust Phaser and Flanger Library");
		m->declare("phaflangers_lib_version", "0.0");
		m->declare("reverbs_lib_name", "Faust Reverb Library");
		m->declare("reverbs_lib_version", "0.0");
		m->declare("routes_lib_name", "Faust Signal Routing Library");
		m->declare("routes_lib_version", "0.1");
		m->declare("signals_lib_name", "Faust Signal Routing Library");
		m->declare("signals_lib_version", "0.0");
		m->declare("soundfiles_lib_name", "Faust Soundfile Library");
		m->declare("soundfiles_lib_version", "0.4");
		m->declare("spats_lib_name", "Faust Spatialization Library");
		m->declare("spats_lib_version", "0.0");
		m->declare("synths_lib_name", "Faust Synthesizer Library");
		m->declare("synths_lib_version", "0.0");
		m->declare("vaeffects_lib_name", "Faust Virtual Analog Filter Effect Library");
		m->declare("vaeffects_lib_version", "0.0");
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
		fHslider0 = static_cast<FAUSTFLOAT>(0.0);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2048; l0 = faust_wrap_add(l0, 1)) {
			fRec1[l0] = 0.0;
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
		ui_interface->openVerticalBox("echo_bug");
		ui_interface->declare(&fHslider0, "0", "");
		ui_interface->addHorizontalSlider("EchoWarp", &fHslider0, FAUSTFLOAT(0.0), FAUSTFLOAT(-1.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.001));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0_ptr = inputs[0];
		FAUSTFLOAT* output0_ptr = outputs[0];
		double fRec3[4];
		double fRec2[4];
		int iZec0[4];
		double fZec1[4];
		double fRec0[4];
		int vindex = 0;
		/* Main loop */
		for (vindex = 0; vindex <= (faust_wrap_sub(count, 4)); vindex = faust_wrap_add(vindex, 4)) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			int vsize = 4;
			/* Recursive loop 0 */
			/* Pre code */
			fRec1_idx = (faust_wrap_add(fRec1_idx, fRec1_idx_save)) & 2047;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec1[(faust_wrap_add(i, fRec1_idx)) & 2047] = 0.995 * fRec1[(faust_wrap_sub(faust_wrap_add(i, fRec1_idx), 1)) & 2047] + 0.0050000000000000044 * static_cast<double>(input0[i]);
			}
			/* Post code */
			fRec1_idx_save = vsize;
			/* Recursive loop 1 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec3[i] = static_cast<double>(fHslider0);
			}
			/* Recursive loop 2 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec2[i] = 1e+02 * (fRec3[i] + 1.0);
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec0[i] = static_cast<int>(fRec2[i]);
			}
			/* Vectorizable loop 4 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec1[i] = std::floor(fRec2[i]);
			}
			/* Recursive loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec0[i] = fRec1[(faust_wrap_sub(faust_wrap_add(i, fRec1_idx), std::min<int>(1025, std::max<int>(0, iZec0[i])))) & 2047] * (fZec1[i] + (1.0 - fRec2[i])) + (fRec2[i] - fZec1[i]) * fRec1[(faust_wrap_sub(faust_wrap_add(i, fRec1_idx), std::min<int>(1025, std::max<int>(0, faust_wrap_add(iZec0[i], 1))))) & 2047];
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(static_cast<double>(input0[i]) + fRec0[i]);
			}
		}
		/* Remaining frames */
		if (vindex < count) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			int vsize = faust_wrap_sub(count, vindex);
			/* Recursive loop 0 */
			/* Pre code */
			fRec1_idx = (faust_wrap_add(fRec1_idx, fRec1_idx_save)) & 2047;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec1[(faust_wrap_add(i, fRec1_idx)) & 2047] = 0.995 * fRec1[(faust_wrap_sub(faust_wrap_add(i, fRec1_idx), 1)) & 2047] + 0.0050000000000000044 * static_cast<double>(input0[i]);
			}
			/* Post code */
			fRec1_idx_save = vsize;
			/* Recursive loop 1 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec3[i] = static_cast<double>(fHslider0);
			}
			/* Recursive loop 2 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec2[i] = 1e+02 * (fRec3[i] + 1.0);
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec0[i] = static_cast<int>(fRec2[i]);
			}
			/* Vectorizable loop 4 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec1[i] = std::floor(fRec2[i]);
			}
			/* Recursive loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec0[i] = fRec1[(faust_wrap_sub(faust_wrap_add(i, fRec1_idx), std::min<int>(1025, std::max<int>(0, iZec0[i])))) & 2047] * (fZec1[i] + (1.0 - fRec2[i])) + (fRec2[i] - fZec1[i]) * fRec1[(faust_wrap_sub(faust_wrap_add(i, fRec1_idx), std::min<int>(1025, std::max<int>(0, faust_wrap_add(iZec0[i], 1))))) & 2047];
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(static_cast<double>(input0[i]) + fRec0[i]);
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
