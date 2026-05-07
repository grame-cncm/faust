/* ------------------------------------------------------------
name: "hello_sine"
Code generated with Faust 2.85.5 (https://faust.grame.fr)
Compilation options: -a ./arch/cpp/bench.cpp -lang cpp -fpga-mem-th 4 -ct 1 -cn HelloSine -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __HelloSine_H__
#define  __HelloSine_H__

#include "faust/dsp/dsp.h"
#include "faust/gui/UI.h"
#include "faust/gui/meta.h"

#include "bench.h"

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS HelloSine
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


class HelloSine : public dsp {
	
 private:
	
	int fSampleRate;
	float fConst0;
	FAUSTFLOAT fHslider0;
	float fRec0[2];
	
 public:
	HelloSine() {
	}
	
	HelloSine(const HelloSine&) = default;
	
	virtual ~HelloSine() = default;
	
	HelloSine& operator=(const HelloSine&) = default;
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-a ./arch/cpp/bench.cpp -lang cpp -fpga-mem-th 4 -ct 1 -cn HelloSine -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("filename", "hello_sine.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.9.0");
		m->declare("name", "hello_sine");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
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
		fConst0 = 1.0f / std::min<float>(1.92e+05f, std::max<float>(1.0f, static_cast<float>(fSampleRate)));
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(4.4e+02f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec0[l0] = 0.0f;
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
	
	virtual HelloSine* clone() {
		return new HelloSine(*this);
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("hello_sine");
		ui_interface->addHorizontalSlider("freq", &fHslider0, FAUSTFLOAT(4.4e+02f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(2e+03f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = fConst0 * static_cast<float>(fHslider0);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec0[0] = fSlow0 + (fRec0[1] - static_cast<float>(static_cast<int>(fSlow0 + fRec0[1])));
			output0[i0] = static_cast<FAUSTFLOAT>(std::sin(6.2831855f * fRec0[0]));
			fRec0[1] = fRec0[0];
		}
	}

};

int main() {
    auto dsp = new HelloSine();
    dsp->init(SAMP_RATE);
    
    s32 n_ins = dsp->getNumInputs();
    s32 n_outs = dsp->getNumOutputs();
    auto [base, err] = make_buffers(n_ins, n_outs);
    if (err) {
        printf("Critical allocation error: %d\n", err);
        exit(err);
    }

    Real** inputs = (Real**)base;
    Real** outputs = inputs + n_ins;

#if FILL_INPUTS
    fill_inputs(inputs, dsp->getNumInputs());
#endif

    warmup(*dsp, inputs, outputs);
    FaustReport report = measure(*dsp, inputs, outputs);
    report.checksum = checksum_outputs(outputs, n_outs);
    print_report(report); // the output will be redirected via script

#if WRITE_CSV
    write_csv(report);
#endif

    free_buffers(inputs);
    return 0;
}

#endif
