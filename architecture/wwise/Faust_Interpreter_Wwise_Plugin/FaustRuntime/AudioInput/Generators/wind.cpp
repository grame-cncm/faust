/* ------------------------------------------------------------
name: "untitled", "wind"
Code generated with Faust 2.79.4 (https://faust.grame.fr)
Compilation options: -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __Wind_H__
#define  __Wind_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <faust/dsp/dsp.h>
#include <faust/gui/MapUI.h>
#include <faust/gui/meta.h>
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS Wind
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

static float Wind_faustpower2_f(float value) {
	return value * value;
}

class Wind : public dsp {
	
 private:
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	float fConst7;
	float fConst8;
	float fConst9;
	float fConst10;
	float fConst11;
	float fConst12;
	int iRec6[2];
	float fConst13;
	float fConst14;
	float fConst15;
	float fConst16;
	float fConst17;
	float fRec5[2];
	float fRec3[2];
	float fConst18;
	float fConst19;
	float fConst20;
	float fConst21;
	float fConst22;
	float fConst23;
	float fConst24;
	float fConst25;
	float fConst26;
	float fConst27;
	float fRec2[2];
	float fRec0[2];
	float fConst28;
	float fConst29;
	float fConst30;
	float fConst31;
	float fConst32;
	float fConst33;
	float fRec13[2];
	float fRec11[2];
	float fRec10[2];
	float fRec8[2];
	
 public:
	Wind() {
	}
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.21.0");
		m->declare("compile_options", "-lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("filename", "untitled.dsp");
		m->declare("filters.lib/allpassnnlt:author", "Julius O. Smith III");
		m->declare("filters.lib/allpassnnlt:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/allpassnnlt:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/tf2np:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2np:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2np:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "1.7.1");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.8.1");
		m->declare("name", "untitled");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "1.4.1");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("vaeffects.lib/moog_vcf_2bn:author", "Julius O. Smith III");
		m->declare("vaeffects.lib/moog_vcf_2bn:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("vaeffects.lib/moog_vcf_2bn:license", "MIT-style STK-4.3 license");
		m->declare("vaeffects.lib/name", "Faust Virtual Analog Filter Effect Library");
		m->declare("vaeffects.lib/version", "1.3.0");
	}

	virtual int getNumInputs() {
		return 0;
	}
	virtual int getNumOutputs() {
		return 2;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::tan(2912.1235f / std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate))));
		fConst1 = 1.0f / fConst0;
		fConst2 = (fConst1 + 0.600014f) / fConst0 + 0.5799944f;
		fConst3 = ((fConst1 + -0.600014f) / fConst0 + 0.5799944f) / fConst2;
		fConst4 = 1.0f / Wind_faustpower2_f(fConst0);
		fConst5 = 0.5799944f - fConst4;
		fConst6 = std::max<float>(-0.9999999f, std::min<float>(0.9999999f, 2.0f * (fConst5 / (fConst2 * (fConst3 + 1.0f)))));
		fConst7 = std::max<float>(-0.9999999f, std::min<float>(0.9999999f, fConst3));
		fConst8 = (fConst1 + 3.399986f) / fConst0 + 3.3799665f;
		fConst9 = ((fConst1 + -3.399986f) / fConst0 + 3.3799665f) / fConst8;
		fConst10 = 3.3799665f - fConst4;
		fConst11 = std::max<float>(-0.9999999f, std::min<float>(0.9999999f, 2.0f * (fConst10 / (fConst8 * (fConst9 + 1.0f)))));
		fConst12 = std::max<float>(-0.9999999f, std::min<float>(0.9999999f, fConst9));
		fConst13 = 1.0f - Wind_faustpower2_f(fConst12);
		fConst14 = std::sqrt(std::max<float>(0.0f, fConst13));
		fConst15 = 4.656613e-10f * fConst14;
		fConst16 = 1.0f - Wind_faustpower2_f(fConst11);
		fConst17 = std::sqrt(std::max<float>(0.0f, fConst16));
		fConst18 = std::sqrt(fConst13);
		fConst19 = 1.0f - fConst10 / fConst8;
		fConst20 = (1.0f - fConst9 - 2.0f * fConst11 * fConst19) / (fConst18 * std::sqrt(fConst16));
		fConst21 = 2.0f * (fConst19 / fConst18);
		fConst22 = 4.656613e-10f * fConst12;
		fConst23 = 1.0f - Wind_faustpower2_f(fConst7);
		fConst24 = std::sqrt(std::max<float>(0.0f, fConst23));
		fConst25 = fConst24 / fConst8;
		fConst26 = 1.0f - Wind_faustpower2_f(fConst6);
		fConst27 = std::sqrt(std::max<float>(0.0f, fConst26));
		fConst28 = std::sqrt(fConst23);
		fConst29 = 1.0f - fConst5 / fConst2;
		fConst30 = (1.0f - fConst3 - 2.0f * fConst6 * fConst29) / (fConst28 * std::sqrt(fConst26));
		fConst31 = 2.0f * (fConst29 / fConst28);
		fConst32 = fConst7 / fConst8;
		fConst33 = 0.7f / fConst2;
	}
	
	virtual void instanceResetUserInterface() {
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iRec6[l0] = 0;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec5[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec3[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec2[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec0[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec13[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec11[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec10[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec8[l8] = 0.0f;
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
	
	virtual Wind* clone() {
		return new Wind();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("untitled");
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			int iTemp0 = 1103515245 * (iRec6[1] + 12345);
			iRec6[0] = 1103515245 * (iTemp0 + 12345);
			int iRec7 = iTemp0;
			float fTemp1 = float(iRec6[0]);
			float fTemp2 = fConst15 * fTemp1 - fConst12 * fRec3[1];
			fRec5[0] = fConst17 * fTemp2 - fConst11 * fRec5[1];
			fRec3[0] = fConst11 * fTemp2 + fConst17 * fRec5[1];
			float fRec4 = fRec5[0];
			float fTemp3 = fConst22 * fTemp1 + fConst14 * fRec3[1] + fConst21 * fRec3[0] + fConst20 * fRec4;
			float fTemp4 = fConst25 * fTemp3 - fConst7 * fRec0[1];
			fRec2[0] = fConst27 * fTemp4 - fConst6 * fRec2[1];
			fRec0[0] = fConst6 * fTemp4 + fConst27 * fRec2[1];
			float fRec1 = fRec2[0];
			output0[i0] = FAUSTFLOAT(fConst33 * (fConst32 * fTemp3 + fConst24 * fRec0[1] + fConst31 * fRec0[0] + fConst30 * fRec1));
			float fTemp5 = float(iRec7);
			float fTemp6 = fConst15 * fTemp5 - fConst12 * fRec11[1];
			fRec13[0] = fConst17 * fTemp6 - fConst11 * fRec13[1];
			fRec11[0] = fConst11 * fTemp6 + fConst17 * fRec13[1];
			float fRec12 = fRec13[0];
			float fTemp7 = fConst22 * fTemp5 + fConst14 * fRec11[1] + fConst21 * fRec11[0] + fConst20 * fRec12;
			float fTemp8 = fConst25 * fTemp7 - fConst7 * fRec8[1];
			fRec10[0] = fConst27 * fTemp8 - fConst6 * fRec10[1];
			fRec8[0] = fConst6 * fTemp8 + fConst27 * fRec10[1];
			float fRec9 = fRec10[0];
			output1[i0] = FAUSTFLOAT(fConst33 * (fConst32 * fTemp7 + fConst24 * fRec8[1] + fConst31 * fRec8[0] + fConst30 * fRec9));
			iRec6[1] = iRec6[0];
			fRec5[1] = fRec5[0];
			fRec3[1] = fRec3[0];
			fRec2[1] = fRec2[0];
			fRec0[1] = fRec0[0];
			fRec13[1] = fRec13[0];
			fRec11[1] = fRec11[0];
			fRec10[1] = fRec10[0];
			fRec8[1] = fRec8[0];
		}
	}

};

#endif
