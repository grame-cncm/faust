/* ------------------------------------------------------------
name: "untitled"
Code generated with Faust 2.79.4 (https://faust.grame.fr)
Compilation options: -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __ComplexRain_H__
#define  __ComplexRain_H__

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
#define FAUSTCLASS ComplexRain
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

class ComplexRainSIG0 {
	
  private:
	
	int iVec2[2];
	int iRec10[2];
	
  public:
	
	int getNumInputsComplexRainSIG0() {
		return 0;
	}
	int getNumOutputsComplexRainSIG0() {
		return 1;
	}
	
	void instanceInitComplexRainSIG0(int sample_rate) {
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			iVec2[l6] = 0;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			iRec10[l7] = 0;
		}
	}
	
	void fillComplexRainSIG0(int count, float* table) {
		for (int i1 = 0; i1 < count; i1 = i1 + 1) {
			iVec2[0] = 1;
			iRec10[0] = (iVec2[1] + iRec10[1]) % 65536;
			table[i1] = std::sin(9.58738e-05f * float(iRec10[0]));
			iVec2[1] = iVec2[0];
			iRec10[1] = iRec10[0];
		}
	}

};

static ComplexRainSIG0* newComplexRainSIG0() { return (ComplexRainSIG0*)new ComplexRainSIG0(); }
static void deleteComplexRainSIG0(ComplexRainSIG0* dsp) { delete dsp; }

static float ComplexRain_faustpower2_f(float value) {
	return value * value;
}
static float ComplexRain_faustpower4_f(float value) {
	return value * value * value * value;
}
static float ftbl0ComplexRainSIG0[65536];

class ComplexRain : public dsp {
	
 private:
	
	int iVec0[2];
	float fRec0[2];
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
	int iRec3[2];
	float fRec2[3];
	float fConst10;
	float fVec1[2];
	float fConst11;
	float fConst12;
	float fRec1[2];
	float fConst13;
	float fRec11[2];
	float fConst14;
	float fConst15;
	float fConst16;
	float fConst17;
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
	float fConst28;
	int iRec19[2];
	float fRec18[3];
	float fVec3[2];
	float fConst29;
	float fConst30;
	float fRec17[2];
	float fConst31;
	float fRec16[2];
	float fVec4[2];
	float fConst32;
	float fRec15[2];
	float fRec14[2];
	float fConst33;
	float fConst34;
	float fConst35;
	float fRec13[2];
	int IOTA0;
	float fVec5[512];
	int iConst36;
	float fRec12[3];
	float fConst37;
	float fRec7[2];
	float fConst38;
	float fRec29[2];
	float fConst39;
	float fConst40;
	float fConst41;
	float fConst42;
	float fConst43;
	float fConst44;
	float fRec30[3];
	float fConst45;
	float fRec4[2];
	float fConst46;
	float fRec34[2];
	float fConst47;
	float fConst48;
	float fConst49;
	float fConst50;
	float fConst51;
	float fConst52;
	float fVec6[512];
	int iConst53;
	float fRec35[3];
	float fConst54;
	float fRec31[2];
	float fConst55;
	float fRec36[2];
	float fConst56;
	float fConst57;
	float fConst58;
	float fConst59;
	float fConst60;
	float fConst61;
	float fRec37[3];
	float fConst62;
	float fRec5[2];
	float fRec38[2];
	
 public:
	ComplexRain() {
	}
	
	void metadata(Meta* m) { 
		m->declare("aanl.lib/name", "Faust Antialiased Nonlinearities");
		m->declare("aanl.lib/version", "1.4.1");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.21.0");
		m->declare("compile_options", "-lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "1.1.0");
		m->declare("filename", "untitled.dsp");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/highpass:author", "Julius O. Smith III");
		m->declare("filters.lib/highpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/resonbp:author", "Julius O. Smith III");
		m->declare("filters.lib/resonbp:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/resonbp:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf1:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf1s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "1.7.1");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.8.1");
		m->declare("name", "untitled");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "1.4.1");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "1.6.0");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "1.6.0");
		m->declare("spats.lib/name", "Faust Spatialization Library");
		m->declare("spats.lib/spat:author", "Laurent Pottier, revised by Romain Michon");
		m->declare("spats.lib/version", "1.2.0");
	}

	virtual int getNumInputs() {
		return 0;
	}
	virtual int getNumOutputs() {
		return 2;
	}
	
	static void classInit(int sample_rate) {
		ComplexRainSIG0* sig0 = newComplexRainSIG0();
		sig0->instanceInitComplexRainSIG0(sample_rate);
		sig0->fillComplexRainSIG0(65536, ftbl0ComplexRainSIG0);
		deleteComplexRainSIG0(sig0);
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = std::tan(6283.1855f / fConst0);
		fConst2 = 1.0f / fConst1;
		fConst3 = 1.0f - fConst2;
		fConst4 = std::tan(31.415926f / fConst0);
		fConst5 = 2.0f * (1.0f - 1.0f / ComplexRain_faustpower2_f(fConst4));
		fConst6 = 1.0f / fConst4;
		fConst7 = (fConst6 + -76.92308f) / fConst4 + 1.0f;
		fConst8 = (fConst6 + 76.92308f) / fConst4 + 1.0f;
		fConst9 = 1.0f / fConst8;
		fConst10 = 2e+02f / (fConst4 * fConst8);
		fConst11 = 0.1f / fConst1;
		fConst12 = 1.0f / (fConst2 + 1.0f);
		fConst13 = 669.0f / fConst0;
		fConst14 = std::tan(6264.336f / fConst0);
		fConst15 = 2.0f * (1.0f - 1.0f / ComplexRain_faustpower2_f(fConst14));
		fConst16 = 1.0f / fConst14;
		fConst17 = (fConst16 + -0.4347826f) / fConst14 + 1.0f;
		fConst18 = (fConst16 + 0.4347826f) / fConst14 + 1.0f;
		fConst19 = 1.0f / fConst18;
		fConst20 = std::tan(1570.7964f / fConst0);
		fConst21 = 1.0f / fConst20;
		fConst22 = 1.0f - fConst21;
		fConst23 = std::tan(157.07964f / fConst0);
		fConst24 = 2.0f * (1.0f - 1.0f / ComplexRain_faustpower2_f(fConst23));
		fConst25 = 1.0f / fConst23;
		fConst26 = 1.0f - (1.0f - fConst25) / fConst23;
		fConst27 = (fConst25 + 1.0f) / fConst23 + 1.0f;
		fConst28 = 1.0f / fConst27;
		fConst29 = 2.0f / (fConst23 * fConst27);
		fConst30 = 1.0f / (fConst21 + 1.0f);
		fConst31 = 1.0f / fConst0;
		fConst32 = 0.5f / fConst20;
		fConst33 = 1.0f / std::tan(28274.334f / fConst0);
		fConst34 = 1.0f - fConst33;
		fConst35 = 1.0f / (fConst33 + 1.0f);
		iConst36 = int(std::min<float>(3e+02f, std::max<float>(0.0f, 0.0037f * fConst0)));
		fConst37 = 1.0f / (fConst14 * fConst18);
		fConst38 = 254.0f / fConst0;
		fConst39 = std::tan(6305.1763f / fConst0);
		fConst40 = 2.0f * (1.0f - 1.0f / ComplexRain_faustpower2_f(fConst39));
		fConst41 = 1.0f / fConst39;
		fConst42 = (fConst41 + -0.4347826f) / fConst39 + 1.0f;
		fConst43 = (fConst41 + 0.4347826f) / fConst39 + 1.0f;
		fConst44 = 1.0f / fConst43;
		fConst45 = 1.0f / (fConst39 * fConst43);
		fConst46 = 551.0f / fConst0;
		fConst47 = std::tan(6185.796f / fConst0);
		fConst48 = 2.0f * (1.0f - 1.0f / ComplexRain_faustpower2_f(fConst47));
		fConst49 = 1.0f / fConst47;
		fConst50 = (fConst49 + -0.4347826f) / fConst47 + 1.0f;
		fConst51 = (fConst49 + 0.4347826f) / fConst47 + 1.0f;
		fConst52 = 1.0f / fConst51;
		iConst53 = int(std::min<float>(3e+02f, std::max<float>(0.0f, 0.0042f * fConst0)));
		fConst54 = 1.0f / (fConst47 * fConst51);
		fConst55 = 443.0f / fConst0;
		fConst56 = std::tan(6239.203f / fConst0);
		fConst57 = 2.0f * (1.0f - 1.0f / ComplexRain_faustpower2_f(fConst56));
		fConst58 = 1.0f / fConst56;
		fConst59 = (fConst58 + -0.4347826f) / fConst56 + 1.0f;
		fConst60 = (fConst58 + 0.4347826f) / fConst56 + 1.0f;
		fConst61 = 1.0f / fConst60;
		fConst62 = 1.0f / (fConst56 * fConst60);
	}
	
	virtual void instanceResetUserInterface() {
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec0[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			iRec3[l2] = 0;
		}
		for (int l3 = 0; l3 < 3; l3 = l3 + 1) {
			fRec2[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fVec1[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec1[l5] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec11[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			iRec19[l9] = 0;
		}
		for (int l10 = 0; l10 < 3; l10 = l10 + 1) {
			fRec18[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 2; l11 = l11 + 1) {
			fVec3[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 2; l12 = l12 + 1) {
			fRec17[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 2; l13 = l13 + 1) {
			fRec16[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 2; l14 = l14 + 1) {
			fVec4[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 2; l15 = l15 + 1) {
			fRec15[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 2; l16 = l16 + 1) {
			fRec14[l16] = 0.0f;
		}
		for (int l17 = 0; l17 < 2; l17 = l17 + 1) {
			fRec13[l17] = 0.0f;
		}
		IOTA0 = 0;
		for (int l18 = 0; l18 < 512; l18 = l18 + 1) {
			fVec5[l18] = 0.0f;
		}
		for (int l19 = 0; l19 < 3; l19 = l19 + 1) {
			fRec12[l19] = 0.0f;
		}
		for (int l20 = 0; l20 < 2; l20 = l20 + 1) {
			fRec7[l20] = 0.0f;
		}
		for (int l21 = 0; l21 < 2; l21 = l21 + 1) {
			fRec29[l21] = 0.0f;
		}
		for (int l22 = 0; l22 < 3; l22 = l22 + 1) {
			fRec30[l22] = 0.0f;
		}
		for (int l23 = 0; l23 < 2; l23 = l23 + 1) {
			fRec4[l23] = 0.0f;
		}
		for (int l24 = 0; l24 < 2; l24 = l24 + 1) {
			fRec34[l24] = 0.0f;
		}
		for (int l25 = 0; l25 < 512; l25 = l25 + 1) {
			fVec6[l25] = 0.0f;
		}
		for (int l26 = 0; l26 < 3; l26 = l26 + 1) {
			fRec35[l26] = 0.0f;
		}
		for (int l27 = 0; l27 < 2; l27 = l27 + 1) {
			fRec31[l27] = 0.0f;
		}
		for (int l28 = 0; l28 < 2; l28 = l28 + 1) {
			fRec36[l28] = 0.0f;
		}
		for (int l29 = 0; l29 < 3; l29 = l29 + 1) {
			fRec37[l29] = 0.0f;
		}
		for (int l30 = 0; l30 < 2; l30 = l30 + 1) {
			fRec5[l30] = 0.0f;
		}
		for (int l31 = 0; l31 < 2; l31 = l31 + 1) {
			fRec38[l31] = 0.0f;
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
	
	virtual ComplexRain* clone() {
		return new ComplexRain();
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
			iVec0[0] = 1;
			fRec0[0] = 0.9999f * fRec0[1] + 8.944272e-05f;
			iRec3[0] = 1103515245 * iRec3[1] + 12345;
			fRec2[0] = 4.656613e-10f * float(iRec3[0]) - fConst9 * (fConst7 * fRec2[2] + fConst5 * fRec2[1]);
			float fTemp0 = ComplexRain_faustpower4_f(std::max<float>(0.05f, std::max<float>(0.0f, std::min<float>(1.0f, fConst10 * (fRec2[0] - fRec2[2])))) + -0.05f);
			fVec1[0] = fTemp0;
			fRec1[0] = fConst12 * (fConst11 * (fTemp0 - fVec1[1]) - fConst3 * fRec1[1]);
			int iTemp1 = 1 - iVec0[1];
			float fTemp2 = ((iTemp1) ? 0.0f : fConst13 + fRec11[1]);
			fRec11[0] = fTemp2 - std::floor(fTemp2);
			int iTemp3 = 1103515245 * (iRec19[1] + 12345);
			int iTemp4 = 1103515245 * (iTemp3 + 12345);
			int iTemp5 = 1103515245 * (iTemp4 + 12345);
			int iTemp6 = 1103515245 * (iTemp5 + 12345);
			int iTemp7 = 1103515245 * (iTemp6 + 12345);
			int iTemp8 = 1103515245 * (iTemp7 + 12345);
			int iTemp9 = 1103515245 * (iTemp8 + 12345);
			int iTemp10 = 1103515245 * (iTemp9 + 12345);
			int iTemp11 = 1103515245 * (iTemp10 + 12345);
			iRec19[0] = 1103515245 * (iTemp11 + 12345);
			int iRec20 = iTemp11;
			int iRec21 = iTemp10;
			int iRec22 = iTemp9;
			int iRec23 = iTemp8;
			int iRec24 = iTemp7;
			int iRec25 = iTemp6;
			int iRec26 = iTemp5;
			int iRec27 = iTemp4;
			int iRec28 = iTemp3;
			fRec18[0] = 2.550532e-10f * (float(iRec28) + float(iRec27) + float(iRec26) + float(iRec25) + float(iRec24) + float(iRec23) + float(iRec22) + float(iRec21) + float(iRec20) + float(iRec19[0])) - fConst28 * (fConst26 * fRec18[2] + fConst24 * fRec18[1]);
			float fTemp12 = fRec18[0] - fRec18[2];
			fVec3[0] = fTemp12;
			fRec17[0] = fConst30 * (fConst29 * (fTemp12 + fVec3[1]) - fConst22 * fRec17[1]);
			float fTemp13 = ((iTemp1) ? 0.0f : fRec16[1] + fConst31 * (8e+01f * fRec17[0] + 4e+01f));
			fRec16[0] = fTemp13 - std::floor(fTemp13);
			float fTemp14 = std::max<float>(0.35f, 1e+01f * ComplexRain_faustpower2_f(fRec17[0]) * std::cos(6.2831855f * (fRec16[0] + -0.25f))) + -0.35f;
			fVec4[0] = fTemp14;
			fRec15[0] = fConst30 * (fConst32 * (fTemp14 - fVec4[1]) - fConst22 * fRec15[1]);
			fRec14[0] = -(fConst30 * (fConst22 * fRec14[1] - fConst21 * (fRec15[0] - fRec15[1])));
			fRec13[0] = -(fConst35 * (fConst34 * fRec13[1] - fConst33 * (fRec14[0] - fRec14[1])));
			float fTemp15 = 15.0f * fRec13[0];
			fVec5[IOTA0 & 511] = fRec5[1] + fRec7[1] + fTemp15;
			float fTemp16 = 0.61f * fVec5[(IOTA0 - iConst36) & 511];
			fRec12[0] = fTemp16 - fConst19 * (fConst17 * fRec12[2] + fConst15 * fRec12[1]);
			fRec7[0] = fConst37 * (fRec12[0] - fRec12[2]) * ftbl0ComplexRainSIG0[std::max<int>(0, std::min<int>(int(65536.0f * fRec11[0]), 65535))];
			float fTemp17 = ((iTemp1) ? 0.0f : fConst38 + fRec29[1]);
			fRec29[0] = fTemp17 - std::floor(fTemp17);
			fRec30[0] = fTemp16 - fConst44 * (fConst42 * fRec30[2] + fConst40 * fRec30[1]);
			float fRec8 = fConst45 * (fRec30[0] - fRec30[2]) * ftbl0ComplexRainSIG0[std::max<int>(0, std::min<int>(int(65536.0f * fRec29[0]), 65535))];
			float fRec9 = fTemp16;
			fRec4[0] = fRec8;
			float fTemp18 = ((iTemp1) ? 0.0f : fConst46 + fRec34[1]);
			fRec34[0] = fTemp18 - std::floor(fTemp18);
			fVec6[IOTA0 & 511] = fRec4[1] + fTemp15 + fRec31[1];
			float fTemp19 = 0.61f * fVec6[(IOTA0 - iConst53) & 511];
			fRec35[0] = fTemp19 - fConst52 * (fConst50 * fRec35[2] + fConst48 * fRec35[1]);
			fRec31[0] = fConst54 * (fRec35[0] - fRec35[2]) * ftbl0ComplexRainSIG0[std::max<int>(0, std::min<int>(int(65536.0f * fRec34[0]), 65535))];
			float fTemp20 = ((iTemp1) ? 0.0f : fConst55 + fRec36[1]);
			fRec36[0] = fTemp20 - std::floor(fTemp20);
			fRec37[0] = fTemp19 - fConst61 * (fConst59 * fRec37[2] + fConst57 * fRec37[1]);
			float fRec32 = fConst62 * (fRec37[0] - fRec37[2]) * ftbl0ComplexRainSIG0[std::max<int>(0, std::min<int>(int(65536.0f * fRec36[0]), 65535))];
			float fRec33 = fTemp19;
			fRec5[0] = fRec32;
			float fRec6 = fRec9 + fRec33;
			float fTemp21 = fRec6 + fRec1[0];
			output0[i0] = FAUSTFLOAT(fTemp21 * fRec0[0]);
			fRec38[0] = 0.9999f * fRec38[1] + 4.472136e-05f;
			output1[i0] = FAUSTFLOAT(fTemp21 * fRec38[0]);
			iVec0[1] = iVec0[0];
			fRec0[1] = fRec0[0];
			iRec3[1] = iRec3[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fVec1[1] = fVec1[0];
			fRec1[1] = fRec1[0];
			fRec11[1] = fRec11[0];
			iRec19[1] = iRec19[0];
			fRec18[2] = fRec18[1];
			fRec18[1] = fRec18[0];
			fVec3[1] = fVec3[0];
			fRec17[1] = fRec17[0];
			fRec16[1] = fRec16[0];
			fVec4[1] = fVec4[0];
			fRec15[1] = fRec15[0];
			fRec14[1] = fRec14[0];
			fRec13[1] = fRec13[0];
			IOTA0 = IOTA0 + 1;
			fRec12[2] = fRec12[1];
			fRec12[1] = fRec12[0];
			fRec7[1] = fRec7[0];
			fRec29[1] = fRec29[0];
			fRec30[2] = fRec30[1];
			fRec30[1] = fRec30[0];
			fRec4[1] = fRec4[0];
			fRec34[1] = fRec34[0];
			fRec35[2] = fRec35[1];
			fRec35[1] = fRec35[0];
			fRec31[1] = fRec31[0];
			fRec36[1] = fRec36[0];
			fRec37[2] = fRec37[1];
			fRec37[1] = fRec37[0];
			fRec5[1] = fRec5[0];
			fRec38[1] = fRec38[0];
		}
	}

};

#endif
