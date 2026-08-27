/* ------------------------------------------------------------
name: "untitled"
Code generated with Faust 2.79.4 (https://faust.grame.fr)
Compilation options: -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __Windchimes_H__
#define  __Windchimes_H__

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
#define FAUSTCLASS Windchimes
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


class Windchimes : public dsp {
	
 private:
	
	int iVec0[2];
	int iVec1[2];
	int iRec7[2];
	float fRec6[2];
	float fRec5[2];
	int fSampleRate;
	float fConst0;
	float fConst1;
	int iRec8[2];
	float fVec2[2];
	int iRec4[2];
	float fRec3[2];
	float fConst2;
	float fRec10[3];
	FAUSTFLOAT fHbargraph0;
	FAUSTFLOAT fHbargraph1;
	float fRec9[2];
	float fRec11[2];
	float fRec12[2];
	float fRec13[2];
	float fRec14[2];
	float fRec15[2];
	float fRec16[2];
	float fRec2[3];
	int iVec3[2];
	int iRec1[2];
	float fConst3;
	float fRec17[2];
	float fRec0[3];
	int iVec4[2];
	int iRec19[2];
	float fRec20[2];
	float fRec18[3];
	int iVec5[2];
	int iRec22[2];
	float fRec23[2];
	float fRec21[3];
	int iVec6[2];
	int iRec25[2];
	float fRec26[2];
	float fRec24[3];
	int iVec7[2];
	int iRec28[2];
	float fRec29[2];
	float fRec27[3];
	float fRec30[3];
	float fRec31[3];
	float fRec32[3];
	float fRec33[3];
	float fRec34[3];
	float fRec35[3];
	float fRec36[3];
	float fRec37[3];
	float fRec38[3];
	float fRec39[3];
	float fRec40[3];
	float fRec41[3];
	float fRec42[3];
	float fRec43[3];
	float fRec44[3];
	float fRec45[3];
	float fRec46[3];
	float fRec47[3];
	float fRec48[3];
	float fRec49[3];
	
 public:
	Windchimes() {
	}
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/sAndH:author", "Romain Michon");
		m->declare("basics.lib/selectoutn:author", "Vince");
		m->declare("basics.lib/version", "1.21.0");
		m->declare("compile_options", "-lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("envelopes.lib/ar:author", "Yann Orlarey, Stéphane Letz");
		m->declare("envelopes.lib/author", "GRAME");
		m->declare("envelopes.lib/copyright", "GRAME");
		m->declare("envelopes.lib/license", "LGPL with exception");
		m->declare("envelopes.lib/name", "Faust Envelope Library");
		m->declare("envelopes.lib/version", "1.3.0");
		m->declare("filename", "untitled.dsp");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
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
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "1.2.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "1.6.0");
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
		fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = 0.001f * fConst0;
		fConst2 = 2.0f / fConst0;
		fConst3 = 1.0f / std::max<float>(1.0f, 0.02f * fConst0);
	}
	
	virtual void instanceResetUserInterface() {
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			iVec1[l1] = 0;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			iRec7[l2] = 0;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec6[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec5[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			iRec8[l5] = 0;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fVec2[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			iRec4[l7] = 0;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec3[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 3; l9 = l9 + 1) {
			fRec10[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 2; l10 = l10 + 1) {
			fRec9[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 2; l11 = l11 + 1) {
			fRec11[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 2; l12 = l12 + 1) {
			fRec12[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 2; l13 = l13 + 1) {
			fRec13[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 2; l14 = l14 + 1) {
			fRec14[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 2; l15 = l15 + 1) {
			fRec15[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 2; l16 = l16 + 1) {
			fRec16[l16] = 0.0f;
		}
		for (int l17 = 0; l17 < 3; l17 = l17 + 1) {
			fRec2[l17] = 0.0f;
		}
		for (int l18 = 0; l18 < 2; l18 = l18 + 1) {
			iVec3[l18] = 0;
		}
		for (int l19 = 0; l19 < 2; l19 = l19 + 1) {
			iRec1[l19] = 0;
		}
		for (int l20 = 0; l20 < 2; l20 = l20 + 1) {
			fRec17[l20] = 0.0f;
		}
		for (int l21 = 0; l21 < 3; l21 = l21 + 1) {
			fRec0[l21] = 0.0f;
		}
		for (int l22 = 0; l22 < 2; l22 = l22 + 1) {
			iVec4[l22] = 0;
		}
		for (int l23 = 0; l23 < 2; l23 = l23 + 1) {
			iRec19[l23] = 0;
		}
		for (int l24 = 0; l24 < 2; l24 = l24 + 1) {
			fRec20[l24] = 0.0f;
		}
		for (int l25 = 0; l25 < 3; l25 = l25 + 1) {
			fRec18[l25] = 0.0f;
		}
		for (int l26 = 0; l26 < 2; l26 = l26 + 1) {
			iVec5[l26] = 0;
		}
		for (int l27 = 0; l27 < 2; l27 = l27 + 1) {
			iRec22[l27] = 0;
		}
		for (int l28 = 0; l28 < 2; l28 = l28 + 1) {
			fRec23[l28] = 0.0f;
		}
		for (int l29 = 0; l29 < 3; l29 = l29 + 1) {
			fRec21[l29] = 0.0f;
		}
		for (int l30 = 0; l30 < 2; l30 = l30 + 1) {
			iVec6[l30] = 0;
		}
		for (int l31 = 0; l31 < 2; l31 = l31 + 1) {
			iRec25[l31] = 0;
		}
		for (int l32 = 0; l32 < 2; l32 = l32 + 1) {
			fRec26[l32] = 0.0f;
		}
		for (int l33 = 0; l33 < 3; l33 = l33 + 1) {
			fRec24[l33] = 0.0f;
		}
		for (int l34 = 0; l34 < 2; l34 = l34 + 1) {
			iVec7[l34] = 0;
		}
		for (int l35 = 0; l35 < 2; l35 = l35 + 1) {
			iRec28[l35] = 0;
		}
		for (int l36 = 0; l36 < 2; l36 = l36 + 1) {
			fRec29[l36] = 0.0f;
		}
		for (int l37 = 0; l37 < 3; l37 = l37 + 1) {
			fRec27[l37] = 0.0f;
		}
		for (int l38 = 0; l38 < 3; l38 = l38 + 1) {
			fRec30[l38] = 0.0f;
		}
		for (int l39 = 0; l39 < 3; l39 = l39 + 1) {
			fRec31[l39] = 0.0f;
		}
		for (int l40 = 0; l40 < 3; l40 = l40 + 1) {
			fRec32[l40] = 0.0f;
		}
		for (int l41 = 0; l41 < 3; l41 = l41 + 1) {
			fRec33[l41] = 0.0f;
		}
		for (int l42 = 0; l42 < 3; l42 = l42 + 1) {
			fRec34[l42] = 0.0f;
		}
		for (int l43 = 0; l43 < 3; l43 = l43 + 1) {
			fRec35[l43] = 0.0f;
		}
		for (int l44 = 0; l44 < 3; l44 = l44 + 1) {
			fRec36[l44] = 0.0f;
		}
		for (int l45 = 0; l45 < 3; l45 = l45 + 1) {
			fRec37[l45] = 0.0f;
		}
		for (int l46 = 0; l46 < 3; l46 = l46 + 1) {
			fRec38[l46] = 0.0f;
		}
		for (int l47 = 0; l47 < 3; l47 = l47 + 1) {
			fRec39[l47] = 0.0f;
		}
		for (int l48 = 0; l48 < 3; l48 = l48 + 1) {
			fRec40[l48] = 0.0f;
		}
		for (int l49 = 0; l49 < 3; l49 = l49 + 1) {
			fRec41[l49] = 0.0f;
		}
		for (int l50 = 0; l50 < 3; l50 = l50 + 1) {
			fRec42[l50] = 0.0f;
		}
		for (int l51 = 0; l51 < 3; l51 = l51 + 1) {
			fRec43[l51] = 0.0f;
		}
		for (int l52 = 0; l52 < 3; l52 = l52 + 1) {
			fRec44[l52] = 0.0f;
		}
		for (int l53 = 0; l53 < 3; l53 = l53 + 1) {
			fRec45[l53] = 0.0f;
		}
		for (int l54 = 0; l54 < 3; l54 = l54 + 1) {
			fRec46[l54] = 0.0f;
		}
		for (int l55 = 0; l55 < 3; l55 = l55 + 1) {
			fRec47[l55] = 0.0f;
		}
		for (int l56 = 0; l56 < 3; l56 = l56 + 1) {
			fRec48[l56] = 0.0f;
		}
		for (int l57 = 0; l57 < 3; l57 = l57 + 1) {
			fRec49[l57] = 0.0f;
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
	
	virtual Windchimes* clone() {
		return new Windchimes();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("wind chimes");
		ui_interface->addHorizontalBargraph("energy", &fHbargraph0, FAUSTFLOAT(0.0f), FAUSTFLOAT(1.5f));
		ui_interface->addHorizontalBargraph("hit probability", &fHbargraph1, FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			iVec0[0] = 1;
			int iTemp0 = iRec4[1] + (1 - iVec0[1]);
			iVec1[0] = iTemp0;
			iRec7[0] = 1103515245 * iRec7[1] + 12345;
			float fTemp1 = float(iRec7[0]);
			float fTemp2 = 4.656613e-10f * fTemp1;
			fRec6[0] = ((iTemp0) ? 1e+01f * (fTemp2 + 1.0f) + 3e+01f : fRec6[1]);
			fRec5[0] = ((iTemp0) ? fRec6[0] : fRec5[1]);
			float fTemp3 = std::max<float>(1.0f, fConst1 * fRec5[0]);
			iRec8[0] = (iRec8[1] + (iRec8[1] > 0)) * (iTemp0 <= iVec1[1]) + (iTemp0 > iVec1[1]);
			float fTemp4 = float(iRec8[0]);
			float fTemp5 = std::max<float>(0.0f, std::min<float>(fTemp4 / fTemp3, fTemp3 + (1.0f - fTemp4)));
			fVec2[0] = fTemp5;
			iRec4[0] = (fVec2[1] != 0.0f) & (fTemp5 == 0.0f);
			fRec3[0] = ((iRec4[0]) ? fRec2[2] : fRec3[1]);
			fRec10[0] = 0.99997f * (fConst2 + fRec10[2]);
			fHbargraph0 = FAUSTFLOAT(fRec10[0]);
			float fTemp6 = fHbargraph0;
			fHbargraph1 = FAUSTFLOAT(1.0f / (99.0f * std::exp(-(2.0f * fTemp6)) + 1.0f));
			fRec9[0] = ((iRec4[0]) ? fHbargraph1 : fRec9[1]);
			float fTemp7 = std::fabs(fTemp2);
			fRec11[0] = ((iRec4[0] * (fRec3[0] == 0.0f)) ? fTemp7 : fRec11[1]);
			float fTemp8 = 0.5f * fRec9[0];
			fRec12[0] = ((iRec4[0] * (fRec3[0] == 1.0f)) ? fTemp7 : fRec12[1]);
			fRec13[0] = ((iRec4[0] * (fRec3[0] == 2.0f)) ? fTemp7 : fRec13[1]);
			fRec14[0] = ((iRec4[0] * (fRec3[0] == 3.0f)) ? fTemp7 : fRec14[1]);
			fRec15[0] = ((iRec4[0] * (fRec3[0] == 4.0f)) ? fTemp7 : fRec15[1]);
			fRec16[0] = ((iRec4[0] * (fRec3[0] == 5.0f)) ? fTemp7 : fRec16[1]);
			fRec2[0] = ((fRec3[0] >= 3.0f) ? float(((fRec3[0] >= 5.0f) ? ((fRec16[0] <= fTemp8) ? 1 : ((fRec16[0] <= fRec9[0]) ? 4 : 0)) : ((fRec3[0] >= 4.0f) ? ((fRec15[0] <= fTemp8) ? 5 : ((fRec15[0] <= fRec9[0]) ? 3 : 0)) : ((fRec14[0] <= fTemp8) ? 4 : ((fRec14[0] <= fRec9[0]) ? 2 : 0))))) : ((fRec3[0] >= 2.0f) ? float(((fRec13[0] <= fTemp8) ? 3 : ((fRec13[0] <= fRec9[0]) ? 1 : 0))) : ((fRec3[0] >= 1.0f) ? float(((fRec12[0] <= fTemp8) ? 2 : ((fRec12[0] <= fRec9[0]) ? 5 : 0))) : ((fRec11[0] <= fRec9[0]) ? std::round(4.0f * (fRec11[0] / fRec9[0])) + 1.0f : 0.0f))));
			int iTemp9 = fRec2[0] != fRec2[1];
			int iTemp10 = (fRec2[0] == 5.0f) * iTemp9;
			iVec3[0] = iTemp10;
			iRec1[0] = (iRec1[1] + (iRec1[1] > 0)) * (iTemp10 <= iVec3[1]) + (iTemp10 > iVec3[1]);
			float fTemp11 = float(iRec1[0]);
			fRec17[0] = ((iTemp10) ? fTemp6 : fRec17[1]);
			float fTemp12 = 4.656613e-10f * std::sqrt(fRec17[0] + 0.1f) * fTemp1 * std::pow(0.97f, 1e+03f * (1.0f - std::max<float>(0.0f, std::min<float>(fTemp11, fConst3 * (1.0f - fTemp11) + 1.0f))));
			fRec0[0] = fTemp12 + 1.9976895f * fRec0[1] - 0.99998564f * fRec0[2];
			int iTemp13 = (fRec2[0] == 4.0f) * iTemp9;
			iVec4[0] = iTemp13;
			iRec19[0] = (iRec19[1] + (iRec19[1] > 0)) * (iTemp13 <= iVec4[1]) + (iTemp13 > iVec4[1]);
			float fTemp14 = float(iRec19[0]);
			fRec20[0] = ((iTemp13) ? fTemp6 : fRec20[1]);
			float fTemp15 = 4.656613e-10f * std::sqrt(fRec20[0] + 0.1f) * fTemp1 * std::pow(0.97f, 1e+03f * (1.0f - std::max<float>(0.0f, std::min<float>(fTemp14, fConst3 * (1.0f - fTemp14) + 1.0f))));
			fRec18[0] = fTemp15 + 1.9981018f * fRec18[1] - 0.99998564f * fRec18[2];
			int iTemp16 = (fRec2[0] == 3.0f) * iTemp9;
			iVec5[0] = iTemp16;
			iRec22[0] = (iRec22[1] + (iRec22[1] > 0)) * (iTemp16 <= iVec5[1]) + (iTemp16 > iVec5[1]);
			float fTemp17 = float(iRec22[0]);
			fRec23[0] = ((iTemp16) ? fTemp6 : fRec23[1]);
			float fTemp18 = 4.656613e-10f * std::sqrt(fRec23[0] + 0.1f) * fTemp1 * std::pow(0.97f, 1e+03f * (1.0f - std::max<float>(0.0f, std::min<float>(fTemp17, fConst3 * (1.0f - fTemp17) + 1.0f))));
			fRec21[0] = fTemp18 + 1.9985057f * fRec21[1] - 0.99998564f * fRec21[2];
			int iTemp19 = (fRec2[0] == 2.0f) * iTemp9;
			iVec6[0] = iTemp19;
			iRec25[0] = (iRec25[1] + (iRec25[1] > 0)) * (iTemp19 <= iVec6[1]) + (iTemp19 > iVec6[1]);
			float fTemp20 = float(iRec25[0]);
			fRec26[0] = ((iTemp19) ? fTemp6 : fRec26[1]);
			float fTemp21 = 4.656613e-10f * std::sqrt(fRec26[0] + 0.1f) * fTemp1 * std::pow(0.97f, 1e+03f * (1.0f - std::max<float>(0.0f, std::min<float>(fTemp20, fConst3 * (1.0f - fTemp20) + 1.0f))));
			fRec24[0] = fTemp21 + 1.9989505f * fRec24[1] - 0.99998564f * fRec24[2];
			int iTemp22 = (fRec2[0] == 1.0f) * iTemp9;
			iVec7[0] = iTemp22;
			iRec28[0] = (iRec28[1] + (iRec28[1] > 0)) * (iTemp22 <= iVec7[1]) + (iTemp22 > iVec7[1]);
			float fTemp23 = float(iRec28[0]);
			fRec29[0] = ((iTemp22) ? fTemp6 : fRec29[1]);
			float fTemp24 = 4.656613e-10f * std::sqrt(fRec29[0] + 0.1f) * fTemp1 * std::pow(0.97f, 1e+03f * (1.0f - std::max<float>(0.0f, std::min<float>(fTemp23, fConst3 * (1.0f - fTemp23) + 1.0f))));
			fRec27[0] = fTemp24 + 1.8915979f * fRec27[1] - 0.9988494f * fRec27[2];
			fRec30[0] = fTemp24 + 1.9462262f * fRec30[1] - 0.9994245f * fRec30[2];
			fRec31[0] = fTemp24 + 1.9784355f * fRec31[1] - 0.9997122f * fRec31[2];
			fRec32[0] = fTemp24 + 1.9939524f * fRec32[1] - 0.99991775f * fRec32[2];
			fRec33[0] = fTemp24 + 1.9991579f * fRec33[1] - 0.99998564f * fRec33[2];
			fRec34[0] = fTemp21 + 1.992513f * fRec34[1] - 0.99991775f * fRec34[2];
			fRec35[0] = fTemp21 + 1.9734613f * fRec35[1] - 0.9997122f * fRec35[2];
			fRec36[0] = fTemp21 + 1.9342905f * fRec36[1] - 0.9994245f * fRec36[2];
			fRec37[0] = fTemp21 + 1.8685968f * fRec37[1] - 0.9988494f * fRec37[2];
			fRec38[0] = fTemp18 + 1.9894383f * fRec38[1] - 0.99991775f * fRec38[2];
			fRec39[0] = fTemp18 + 1.963045f * fRec39[1] - 0.9997122f * fRec39[2];
			fRec40[0] = fTemp18 + 1.9085721f * fRec40[1] - 0.9994245f * fRec40[2];
			fRec41[0] = fTemp18 + 1.8175561f * fRec41[1] - 0.9988494f * fRec41[2];
			fRec42[0] = fTemp15 + 1.9867989f * fRec42[1] - 0.99991775f * fRec42[2];
			fRec43[0] = fTemp15 + 1.9541994f * fRec43[1] - 0.9997122f * fRec43[2];
			fRec44[0] = fTemp15 + 1.8867846f * fRec44[1] - 0.9994245f * fRec44[2];
			fRec45[0] = fTemp15 + 1.7745043f * fRec45[1] - 0.9988494f * fRec45[2];
			fRec46[0] = fTemp12 + 1.9839008f * fRec46[1] - 0.99991775f * fRec46[2];
			fRec47[0] = fTemp12 + 1.9448138f * fRec47[1] - 0.9997122f * fRec47[2];
			fRec48[0] = fTemp12 + 1.8637005f * fRec48[1] - 0.9994245f * fRec48[2];
			fRec49[0] = fTemp12 + 1.729075f * fRec49[1] - 0.9988494f * fRec49[2];
			float fTemp25 = 0.25f * (0.027578233f * (fRec49[0] - fRec49[2]) + 0.00984774f * (fRec48[0] - fRec48[2]) + 0.46534723f * (fRec47[0] - fRec47[2]) + 0.046706475f * (fRec46[0] - fRec46[2]) + 0.025301978f * (fRec45[0] - fRec45[2]) + 0.008998045f * (fRec44[0] - fRec44[2]) + 0.42420912f * (fRec43[0] - fRec43[2]) + 0.04228563f * (fRec42[0] - fRec42[2]) + 0.02287444f * (fRec41[0] - fRec41[2]) + 0.008103716f * (fRec40[0] - fRec40[2]) + 0.3811863f * (fRec39[0] - fRec39[2]) + 0.03780568f * (fRec38[0] - fRec38[2]) + 0.0195181f * (fRec37[0] - fRec37[2]) + 0.006884051f * (fRec36[0] - fRec36[2]) + 0.3229546f * (fRec35[0] - fRec35[2]) + 0.03179165f * (fRec34[0] - fRec34[2]) + 0.004528017f * (fRec33[0] - fRec33[2]) + 0.028540056f * (fRec32[0] - fRec32[2]) + 0.29093292f * (fRec31[0] - fRec31[2]) + 0.0062308447f * (fRec30[0] - fRec30[2]) + 0.017763702f * (fRec27[0] - fRec27[2]) + 0.005063458f * (fRec24[0] - fRec24[2]) + 0.0060538645f * (fRec21[0] - fRec21[2]) + 0.0068299635f * (fRec18[0] - fRec18[2]) + 0.007540041f * (fRec0[0] - fRec0[2]));
			output0[i0] = FAUSTFLOAT(fTemp25);
			output1[i0] = FAUSTFLOAT(fTemp25);
			iVec0[1] = iVec0[0];
			iVec1[1] = iVec1[0];
			iRec7[1] = iRec7[0];
			fRec6[1] = fRec6[0];
			fRec5[1] = fRec5[0];
			iRec8[1] = iRec8[0];
			fVec2[1] = fVec2[0];
			iRec4[1] = iRec4[0];
			fRec3[1] = fRec3[0];
			fRec10[2] = fRec10[1];
			fRec10[1] = fRec10[0];
			fRec9[1] = fRec9[0];
			fRec11[1] = fRec11[0];
			fRec12[1] = fRec12[0];
			fRec13[1] = fRec13[0];
			fRec14[1] = fRec14[0];
			fRec15[1] = fRec15[0];
			fRec16[1] = fRec16[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			iVec3[1] = iVec3[0];
			iRec1[1] = iRec1[0];
			fRec17[1] = fRec17[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			iVec4[1] = iVec4[0];
			iRec19[1] = iRec19[0];
			fRec20[1] = fRec20[0];
			fRec18[2] = fRec18[1];
			fRec18[1] = fRec18[0];
			iVec5[1] = iVec5[0];
			iRec22[1] = iRec22[0];
			fRec23[1] = fRec23[0];
			fRec21[2] = fRec21[1];
			fRec21[1] = fRec21[0];
			iVec6[1] = iVec6[0];
			iRec25[1] = iRec25[0];
			fRec26[1] = fRec26[0];
			fRec24[2] = fRec24[1];
			fRec24[1] = fRec24[0];
			iVec7[1] = iVec7[0];
			iRec28[1] = iRec28[0];
			fRec29[1] = fRec29[0];
			fRec27[2] = fRec27[1];
			fRec27[1] = fRec27[0];
			fRec30[2] = fRec30[1];
			fRec30[1] = fRec30[0];
			fRec31[2] = fRec31[1];
			fRec31[1] = fRec31[0];
			fRec32[2] = fRec32[1];
			fRec32[1] = fRec32[0];
			fRec33[2] = fRec33[1];
			fRec33[1] = fRec33[0];
			fRec34[2] = fRec34[1];
			fRec34[1] = fRec34[0];
			fRec35[2] = fRec35[1];
			fRec35[1] = fRec35[0];
			fRec36[2] = fRec36[1];
			fRec36[1] = fRec36[0];
			fRec37[2] = fRec37[1];
			fRec37[1] = fRec37[0];
			fRec38[2] = fRec38[1];
			fRec38[1] = fRec38[0];
			fRec39[2] = fRec39[1];
			fRec39[1] = fRec39[0];
			fRec40[2] = fRec40[1];
			fRec40[1] = fRec40[0];
			fRec41[2] = fRec41[1];
			fRec41[1] = fRec41[0];
			fRec42[2] = fRec42[1];
			fRec42[1] = fRec42[0];
			fRec43[2] = fRec43[1];
			fRec43[1] = fRec43[0];
			fRec44[2] = fRec44[1];
			fRec44[1] = fRec44[0];
			fRec45[2] = fRec45[1];
			fRec45[1] = fRec45[0];
			fRec46[2] = fRec46[1];
			fRec46[1] = fRec46[0];
			fRec47[2] = fRec47[1];
			fRec47[1] = fRec47[0];
			fRec48[2] = fRec48[1];
			fRec48[1] = fRec48[0];
			fRec49[2] = fRec49[1];
			fRec49[1] = fRec49[0];
		}
	}

};

#endif
