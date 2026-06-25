/* ------------------------------------------------------------
name: "no_bargraph"
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
	
	FAUSTFLOAT fEntry0;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fButton0;
	int fSampleRate;
	
 public:
	mydsp() {
	}
	
	mydsp(const mydsp&) = default;
	
	virtual ~mydsp() = default;
	
	mydsp& operator=(const mydsp&) = default;
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 32");
		m->declare("filename", "no_bargraph.dsp");
		m->declare("name", "no_bargraph");
	}

	virtual int getNumInputs() {
		return 1;
	}
	virtual int getNumOutputs() {
		return 8;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
	}
	
	virtual void instanceResetUserInterface() {
		fEntry0 = static_cast<FAUSTFLOAT>(0.0);
		fHslider0 = static_cast<FAUSTFLOAT>(0.5);
		fVslider0 = static_cast<FAUSTFLOAT>(0.25);
		fCheckbox0 = static_cast<FAUSTFLOAT>(0.0);
		fButton0 = static_cast<FAUSTFLOAT>(0.0);
	}
	
	virtual void instanceClear() {
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
		ui_interface->openVerticalBox("no_bargraph");
		ui_interface->declare(&fHslider0, "0", "");
		ui_interface->addHorizontalSlider("controls/gain_h", &fHslider0, FAUSTFLOAT(0.5), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.01));
		ui_interface->declare(&fVslider0, "1", "");
		ui_interface->addVerticalSlider("controls/gain_v", &fVslider0, FAUSTFLOAT(0.25), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.01));
		ui_interface->declare(&fEntry0, "2", "");
		ui_interface->addNumEntry("controls/bias_n", &fEntry0, FAUSTFLOAT(0.0), FAUSTFLOAT(-1.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.001));
		ui_interface->declare(&fCheckbox0, "3", "");
		ui_interface->addCheckButton("controls/gate_c", &fCheckbox0);
		ui_interface->declare(&fButton0, "4", "");
		ui_interface->addButton("controls/trig_b", &fButton0);
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0_ptr = inputs[0];
		FAUSTFLOAT* output0_ptr = outputs[0];
		FAUSTFLOAT* output1_ptr = outputs[1];
		FAUSTFLOAT* output2_ptr = outputs[2];
		FAUSTFLOAT* output3_ptr = outputs[3];
		FAUSTFLOAT* output4_ptr = outputs[4];
		FAUSTFLOAT* output5_ptr = outputs[5];
		FAUSTFLOAT* output6_ptr = outputs[6];
		FAUSTFLOAT* output7_ptr = outputs[7];
		double fSlow0 = static_cast<double>(fEntry0);
		double fSlow1 = static_cast<double>(fHslider0);
		double fSlow2 = static_cast<double>(fVslider0);
		double fSlow3 = fSlow1 + fSlow2;
		double fSlow4 = static_cast<double>(fCheckbox0);
		double fSlow5 = static_cast<double>(fButton0);
		double fSlow6 = fSlow4 + fSlow5;
		double fSlow7 = fSlow1 * fSlow2;
		double fSlow8 = fSlow4 + 1.0;
		double fSlow9 = fSlow5 + 0.25;
		double fSlow10 = fSlow5 + fSlow3 + fSlow4;
		int vindex = 0;
		/* Main loop */
		for (vindex = 0; vindex <= (count - 32); vindex = vindex + 32) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			FAUSTFLOAT* output1 = &output1_ptr[vindex];
			FAUSTFLOAT* output2 = &output2_ptr[vindex];
			FAUSTFLOAT* output3 = &output3_ptr[vindex];
			FAUSTFLOAT* output4 = &output4_ptr[vindex];
			FAUSTFLOAT* output5 = &output5_ptr[vindex];
			FAUSTFLOAT* output6 = &output6_ptr[vindex];
			FAUSTFLOAT* output7 = &output7_ptr[vindex];
			int vsize = 32;
			/* Vectorizable loop 0 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				output0[i] = static_cast<FAUSTFLOAT>(fSlow0 + fSlow1 * static_cast<double>(input0[i]));
			}
			/* Vectorizable loop 1 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				output1[i] = static_cast<FAUSTFLOAT>(fSlow2 * static_cast<double>(input0[i]) - fSlow0);
			}
			/* Vectorizable loop 2 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				output2[i] = static_cast<FAUSTFLOAT>(fSlow3 * static_cast<double>(input0[i]));
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				output3[i] = static_cast<FAUSTFLOAT>(fSlow6 * static_cast<double>(input0[i]));
			}
			/* Vectorizable loop 4 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				output4[i] = static_cast<FAUSTFLOAT>(fSlow7 * (fSlow0 + static_cast<double>(input0[i])));
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				output5[i] = static_cast<FAUSTFLOAT>(fSlow8 * (static_cast<double>(input0[i]) - fSlow0));
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				output6[i] = static_cast<FAUSTFLOAT>(fSlow9 * static_cast<double>(input0[i]));
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				output7[i] = static_cast<FAUSTFLOAT>(fSlow10 * static_cast<double>(input0[i]));
			}
		}
		/* Remaining frames */
		if (vindex < count) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			FAUSTFLOAT* output1 = &output1_ptr[vindex];
			FAUSTFLOAT* output2 = &output2_ptr[vindex];
			FAUSTFLOAT* output3 = &output3_ptr[vindex];
			FAUSTFLOAT* output4 = &output4_ptr[vindex];
			FAUSTFLOAT* output5 = &output5_ptr[vindex];
			FAUSTFLOAT* output6 = &output6_ptr[vindex];
			FAUSTFLOAT* output7 = &output7_ptr[vindex];
			int vsize = count - vindex;
			/* Vectorizable loop 0 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				output0[i] = static_cast<FAUSTFLOAT>(fSlow0 + fSlow1 * static_cast<double>(input0[i]));
			}
			/* Vectorizable loop 1 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				output1[i] = static_cast<FAUSTFLOAT>(fSlow2 * static_cast<double>(input0[i]) - fSlow0);
			}
			/* Vectorizable loop 2 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				output2[i] = static_cast<FAUSTFLOAT>(fSlow3 * static_cast<double>(input0[i]));
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				output3[i] = static_cast<FAUSTFLOAT>(fSlow6 * static_cast<double>(input0[i]));
			}
			/* Vectorizable loop 4 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				output4[i] = static_cast<FAUSTFLOAT>(fSlow7 * (fSlow0 + static_cast<double>(input0[i])));
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				output5[i] = static_cast<FAUSTFLOAT>(fSlow8 * (static_cast<double>(input0[i]) - fSlow0));
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				output6[i] = static_cast<FAUSTFLOAT>(fSlow9 * static_cast<double>(input0[i]));
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				output7[i] = static_cast<FAUSTFLOAT>(fSlow10 * static_cast<double>(input0[i]));
			}
		}
	}

};

#endif
