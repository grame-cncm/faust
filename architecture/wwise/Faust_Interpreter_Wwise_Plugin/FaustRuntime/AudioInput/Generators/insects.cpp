/* ------------------------------------------------------------
name: "untitled"
Code generated with Faust 2.79.4 (https://faust.grame.fr)
Compilation options: -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __Insects_H__
#define  __Insects_H__

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
#define FAUSTCLASS Insects
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

class InsectsSIG0 {
	
  private:
	
	int iVec1[2];
	int iRec10[2];
	
  public:
	
	int getNumInputsInsectsSIG0() {
		return 0;
	}
	int getNumOutputsInsectsSIG0() {
		return 1;
	}
	
	void instanceInitInsectsSIG0(int sample_rate) {
		for (int l11 = 0; l11 < 2; l11 = l11 + 1) {
			iVec1[l11] = 0;
		}
		for (int l12 = 0; l12 < 2; l12 = l12 + 1) {
			iRec10[l12] = 0;
		}
	}
	
	void fillInsectsSIG0(int count, float* table) {
		for (int i1 = 0; i1 < count; i1 = i1 + 1) {
			iVec1[0] = 1;
			iRec10[0] = (iVec1[1] + iRec10[1]) % 65536;
			table[i1] = std::sin(9.58738e-05f * float(iRec10[0]));
			iVec1[1] = iVec1[0];
			iRec10[1] = iRec10[0];
		}
	}

};

static InsectsSIG0* newInsectsSIG0() { return (InsectsSIG0*)new InsectsSIG0(); }
static void deleteInsectsSIG0(InsectsSIG0* dsp) { delete dsp; }

static float Insects_faustpower2_f(float value) {
	return value * value;
}
static float ftbl0InsectsSIG0[65536];

class Insects : public dsp {
	
 private:
	
	int iVec0[2];
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	float fRec1[2];
	float fConst7;
	float fRec2[2];
	float fConst8;
	float fRec3[2];
	float fConst9;
	float fRec4[2];
	float fRec0[3];
	float fConst10;
	float fRec6[2];
	float fConst11;
	float fRec7[2];
	float fConst12;
	float fRec8[2];
	float fConst13;
	float fRec9[2];
	float fRec5[3];
	float fConst14;
	float fRec11[2];
	float fConst15;
	float fConst16;
	float fConst17;
	float fConst18;
	float fConst19;
	int iRec13[2];
	float fVec2[2];
	float fRec12[3];
	float fConst20;
	float fConst21;
	float fConst22;
	float fConst23;
	float fConst24;
	float fConst25;
	float fRec18[2];
	float fVec3[2];
	float fRec17[2];
	float fRec16[2];
	float fConst26;
	float fRec15[2];
	float fRec14[3];
	float fConst27;
	float fConst28;
	float fConst29;
	float fConst30;
	float fConst31;
	float fConst32;
	float fConst33;
	float fConst34;
	float fConst35;
	float fConst36;
	int iConst37;
	int iRec22[2];
	float fConst38;
	float fRec25[2];
	float fVec4[2];
	float fRec24[2];
	float fConst39;
	float fRec23[2];
	int iVec5[2];
	int iRec21[2];
	float fConst40;
	int iRec26[2];
	float fConst41;
	float fRec27[3];
	float fRec20[3];
	float fRec29[3];
	float fRec28[3];
	float fRec31[3];
	float fRec30[3];
	float fRec19[3];
	int iRec34[2];
	float fRec33[2];
	float fRec48[2];
	float fRec32[2];
	int iConst42;
	int iRec52[2];
	float fConst43;
	float fRec55[2];
	float fVec6[2];
	float fRec54[2];
	float fConst44;
	float fRec53[2];
	int iVec7[2];
	int iRec51[2];
	float fConst45;
	int iRec56[2];
	float fRec57[3];
	float fRec50[3];
	float fRec59[3];
	float fRec58[3];
	float fRec61[3];
	float fRec60[3];
	float fRec49[3];
	float fRec63[2];
	float fRec64[2];
	float fRec62[2];
	float fConst46;
	int iConst47;
	int iRec68[2];
	float fConst48;
	float fRec71[2];
	float fVec8[2];
	float fRec70[2];
	float fRec69[2];
	int iVec9[2];
	int iRec67[2];
	float fConst49;
	int iRec72[2];
	float fRec73[3];
	float fRec66[3];
	float fRec75[3];
	float fRec74[3];
	float fRec77[3];
	float fRec76[3];
	float fRec65[3];
	float fRec79[2];
	float fRec80[2];
	float fRec78[2];
	float fConst50;
	float fRec81[2];
	float fConst51;
	float fRec82[2];
	int iConst52;
	int iRec84[2];
	float fConst53;
	float fRec87[2];
	float fVec10[2];
	float fRec86[2];
	float fConst54;
	float fRec85[2];
	float fConst55;
	float fRec88[2];
	float fRec83[2];
	float fConst56;
	float fRec89[2];
	float fRec91[2];
	float fRec92[2];
	float fRec90[2];
	float fConst57;
	float fRec93[2];
	float fConst58;
	float fRec94[2];
	float fConst59;
	float fRec98[2];
	float fVec11[2];
	float fRec97[2];
	float fConst60;
	float fRec96[2];
	float fRec95[2];
	float fRec99[2];
	float fRec101[2];
	float fRec102[2];
	float fRec100[2];
	float fConst61;
	float fRec103[2];
	float fConst62;
	float fRec104[2];
	float fConst63;
	float fRec108[2];
	float fVec12[2];
	float fRec107[2];
	float fConst64;
	float fRec106[2];
	float fRec105[2];
	float fRec109[2];
	float fRec111[2];
	float fRec112[2];
	float fRec110[2];
	float fConst65;
	float fRec113[2];
	float fConst66;
	float fRec114[2];
	int iConst67;
	int iRec116[2];
	float fConst68;
	float fRec119[2];
	float fVec13[2];
	float fRec118[2];
	float fConst69;
	float fRec117[2];
	float fRec115[2];
	float fRec120[2];
	float fRec122[2];
	float fRec123[2];
	float fRec121[2];
	float fConst70;
	float fConst71;
	float fConst72;
	float fRec130[2];
	float fRec131[2];
	float fRec129[2];
	float fConst73;
	float fConst74;
	float fConst75;
	float fRec128[2];
	float fRec127[2];
	float fRec126[2];
	float fRec125[2];
	float fRec124[2];
	float fRec132[2];
	float fRec133[2];
	float fRec134[2];
	float fRec135[2];
	float fRec136[2];
	float fRec137[2];
	float fRec138[2];
	
 public:
	Insects() {
	}
	
	void metadata(Meta* m) { 
		m->declare("aanl.lib/name", "Faust Antialiased Nonlinearities");
		m->declare("aanl.lib/version", "1.4.1");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/sAndH:author", "Romain Michon");
		m->declare("basics.lib/version", "1.21.0");
		m->declare("compile_options", "-lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("envelopes.lib/asr:author", "Yann Orlarey, Stéphane Letz");
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
		m->declare("filters.lib/lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass0_highpass1:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/nlf2:author", "Julius O. Smith III");
		m->declare("filters.lib/nlf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/nlf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/resonbp:author", "Julius O. Smith III");
		m->declare("filters.lib/resonbp:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/resonbp:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/resonhp:author", "Julius O. Smith III");
		m->declare("filters.lib/resonhp:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/resonhp:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/resonlp:author", "Julius O. Smith III");
		m->declare("filters.lib/resonlp:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/resonlp:license", "MIT-style STK-4.3 license");
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
		m->declare("oscillators.lib/lf_sawpos:author", "Bart Brouns, revised by Stéphane Letz");
		m->declare("oscillators.lib/lf_sawpos:licence", "STK-4.3");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "1.6.0");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "1.2.0");
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
		InsectsSIG0* sig0 = newInsectsSIG0();
		sig0->instanceInitInsectsSIG0(sample_rate);
		sig0->fillInsectsSIG0(65536, ftbl0InsectsSIG0);
		deleteInsectsSIG0(sig0);
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = std::tan(62.831852f / fConst0);
		fConst2 = 2.0f * (1.0f - 1.0f / Insects_faustpower2_f(fConst1));
		fConst3 = 1.0f / fConst1;
		fConst4 = 1.0f - (1.0f - fConst3) / fConst1;
		fConst5 = 1.0f / ((fConst3 + 1.0f) / fConst1 + 1.0f);
		fConst6 = 15.5f / fConst0;
		fConst7 = 20.4f / fConst0;
		fConst8 = 4.279f / fConst0;
		fConst9 = 2134.0f / fConst0;
		fConst10 = 2.0f / fConst0;
		fConst11 = 2e+01f / fConst0;
		fConst12 = 4.0f / fConst0;
		fConst13 = 2012.0f / fConst0;
		fConst14 = 0.01f / fConst0;
		fConst15 = std::tan(2513.2742f / fConst0);
		fConst16 = 2.0f * (1.0f - 1.0f / Insects_faustpower2_f(fConst15));
		fConst17 = 1.0f / fConst15;
		fConst18 = 1.0f - (1.0f - fConst17) / fConst15;
		fConst19 = 1.0f / ((fConst17 + 1.0f) / fConst15 + 1.0f);
		fConst20 = std::tan(2670.3538f / fConst0);
		fConst21 = 2.0f * (1.0f - 1.0f / Insects_faustpower2_f(fConst20));
		fConst22 = 1.0f / fConst20;
		fConst23 = (fConst22 + -0.06666667f) / fConst20 + 1.0f;
		fConst24 = 1.0f / ((fConst22 + 0.06666667f) / fConst20 + 1.0f);
		fConst25 = 2.5e+02f / fConst0;
		fConst26 = 1.0f / fConst0;
		fConst27 = std::tan(31.415926f / fConst0);
		fConst28 = 2.0f * (1.0f - 1.0f / Insects_faustpower2_f(fConst27));
		fConst29 = 1.0f / fConst27;
		fConst30 = 1.0f - (1.0f - fConst29) / fConst27;
		fConst31 = 1.0f / ((fConst29 + 1.0f) / fConst27 + 1.0f);
		fConst32 = std::tan(4398.2295f / fConst0);
		fConst33 = 2.0f * (1.0f - 1.0f / Insects_faustpower2_f(fConst32));
		fConst34 = 1.0f / fConst32;
		fConst35 = 1.0f - (1.0f - fConst34) / fConst32;
		fConst36 = 1.0f / ((fConst34 + 1.0f) / fConst32 + 1.0f);
		iConst37 = int(0.15f * fConst0);
		fConst38 = 0.087f / fConst0;
		fConst39 = 0.75f * fConst0;
		fConst40 = 1.0f / std::max<float>(1.0f, 0.2f * fConst0);
		fConst41 = 3.1415927f / fConst0;
		iConst42 = int(0.3f * fConst0);
		fConst43 = 0.09f / fConst0;
		fConst44 = 0.6f * fConst0;
		fConst45 = 1.0f / std::max<float>(1.0f, 0.4f * fConst0);
		fConst46 = 0.25f * fConst0;
		iConst47 = int(fConst46);
		fConst48 = 0.093f / fConst0;
		fConst49 = 1.0f / std::max<float>(1.0f, fConst46);
		fConst50 = 1842.0f / fConst0;
		fConst51 = 6134.0f / fConst0;
		iConst52 = int(0.32f * fConst0);
		fConst53 = 0.0921f / fConst0;
		fConst54 = 1.28f * fConst0;
		fConst55 = 0.8f / fConst0;
		fConst56 = 1.25f * fConst0;
		fConst57 = 15342.0f / fConst0;
		fConst58 = 8134.0f / fConst0;
		fConst59 = 0.05f / fConst0;
		fConst60 = 1.5f * fConst0;
		fConst61 = 8342.0f / fConst0;
		fConst62 = 3134.0f / fConst0;
		fConst63 = 0.15f / fConst0;
		fConst64 = 0.9f * fConst0;
		fConst65 = 12342.0f / fConst0;
		fConst66 = 5134.0f / fConst0;
		iConst67 = int(0.5f * fConst0);
		fConst68 = 0.1f / fConst0;
		fConst69 = 2.5f * fConst0;
		fConst70 = 3141.5928f / fConst0;
		fConst71 = std::cos(fConst70);
		fConst72 = std::sin(fConst70);
		fConst73 = 1.0f / std::tan(1570.7964f / fConst0);
		fConst74 = 1.0f - fConst73;
		fConst75 = 1.0f / (fConst73 + 1.0f);
	}
	
	virtual void instanceResetUserInterface() {
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec1[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec2[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec3[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec4[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 3; l5 = l5 + 1) {
			fRec0[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec6[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec7[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec8[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fRec9[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 3; l10 = l10 + 1) {
			fRec5[l10] = 0.0f;
		}
		for (int l13 = 0; l13 < 2; l13 = l13 + 1) {
			fRec11[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 2; l14 = l14 + 1) {
			iRec13[l14] = 0;
		}
		for (int l15 = 0; l15 < 2; l15 = l15 + 1) {
			fVec2[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 3; l16 = l16 + 1) {
			fRec12[l16] = 0.0f;
		}
		for (int l17 = 0; l17 < 2; l17 = l17 + 1) {
			fRec18[l17] = 0.0f;
		}
		for (int l18 = 0; l18 < 2; l18 = l18 + 1) {
			fVec3[l18] = 0.0f;
		}
		for (int l19 = 0; l19 < 2; l19 = l19 + 1) {
			fRec17[l19] = 0.0f;
		}
		for (int l20 = 0; l20 < 2; l20 = l20 + 1) {
			fRec16[l20] = 0.0f;
		}
		for (int l21 = 0; l21 < 2; l21 = l21 + 1) {
			fRec15[l21] = 0.0f;
		}
		for (int l22 = 0; l22 < 3; l22 = l22 + 1) {
			fRec14[l22] = 0.0f;
		}
		for (int l23 = 0; l23 < 2; l23 = l23 + 1) {
			iRec22[l23] = 0;
		}
		for (int l24 = 0; l24 < 2; l24 = l24 + 1) {
			fRec25[l24] = 0.0f;
		}
		for (int l25 = 0; l25 < 2; l25 = l25 + 1) {
			fVec4[l25] = 0.0f;
		}
		for (int l26 = 0; l26 < 2; l26 = l26 + 1) {
			fRec24[l26] = 0.0f;
		}
		for (int l27 = 0; l27 < 2; l27 = l27 + 1) {
			fRec23[l27] = 0.0f;
		}
		for (int l28 = 0; l28 < 2; l28 = l28 + 1) {
			iVec5[l28] = 0;
		}
		for (int l29 = 0; l29 < 2; l29 = l29 + 1) {
			iRec21[l29] = 0;
		}
		for (int l30 = 0; l30 < 2; l30 = l30 + 1) {
			iRec26[l30] = 0;
		}
		for (int l31 = 0; l31 < 3; l31 = l31 + 1) {
			fRec27[l31] = 0.0f;
		}
		for (int l32 = 0; l32 < 3; l32 = l32 + 1) {
			fRec20[l32] = 0.0f;
		}
		for (int l33 = 0; l33 < 3; l33 = l33 + 1) {
			fRec29[l33] = 0.0f;
		}
		for (int l34 = 0; l34 < 3; l34 = l34 + 1) {
			fRec28[l34] = 0.0f;
		}
		for (int l35 = 0; l35 < 3; l35 = l35 + 1) {
			fRec31[l35] = 0.0f;
		}
		for (int l36 = 0; l36 < 3; l36 = l36 + 1) {
			fRec30[l36] = 0.0f;
		}
		for (int l37 = 0; l37 < 3; l37 = l37 + 1) {
			fRec19[l37] = 0.0f;
		}
		for (int l38 = 0; l38 < 2; l38 = l38 + 1) {
			iRec34[l38] = 0;
		}
		for (int l39 = 0; l39 < 2; l39 = l39 + 1) {
			fRec33[l39] = 0.0f;
		}
		for (int l40 = 0; l40 < 2; l40 = l40 + 1) {
			fRec48[l40] = 0.0f;
		}
		for (int l41 = 0; l41 < 2; l41 = l41 + 1) {
			fRec32[l41] = 0.0f;
		}
		for (int l42 = 0; l42 < 2; l42 = l42 + 1) {
			iRec52[l42] = 0;
		}
		for (int l43 = 0; l43 < 2; l43 = l43 + 1) {
			fRec55[l43] = 0.0f;
		}
		for (int l44 = 0; l44 < 2; l44 = l44 + 1) {
			fVec6[l44] = 0.0f;
		}
		for (int l45 = 0; l45 < 2; l45 = l45 + 1) {
			fRec54[l45] = 0.0f;
		}
		for (int l46 = 0; l46 < 2; l46 = l46 + 1) {
			fRec53[l46] = 0.0f;
		}
		for (int l47 = 0; l47 < 2; l47 = l47 + 1) {
			iVec7[l47] = 0;
		}
		for (int l48 = 0; l48 < 2; l48 = l48 + 1) {
			iRec51[l48] = 0;
		}
		for (int l49 = 0; l49 < 2; l49 = l49 + 1) {
			iRec56[l49] = 0;
		}
		for (int l50 = 0; l50 < 3; l50 = l50 + 1) {
			fRec57[l50] = 0.0f;
		}
		for (int l51 = 0; l51 < 3; l51 = l51 + 1) {
			fRec50[l51] = 0.0f;
		}
		for (int l52 = 0; l52 < 3; l52 = l52 + 1) {
			fRec59[l52] = 0.0f;
		}
		for (int l53 = 0; l53 < 3; l53 = l53 + 1) {
			fRec58[l53] = 0.0f;
		}
		for (int l54 = 0; l54 < 3; l54 = l54 + 1) {
			fRec61[l54] = 0.0f;
		}
		for (int l55 = 0; l55 < 3; l55 = l55 + 1) {
			fRec60[l55] = 0.0f;
		}
		for (int l56 = 0; l56 < 3; l56 = l56 + 1) {
			fRec49[l56] = 0.0f;
		}
		for (int l57 = 0; l57 < 2; l57 = l57 + 1) {
			fRec63[l57] = 0.0f;
		}
		for (int l58 = 0; l58 < 2; l58 = l58 + 1) {
			fRec64[l58] = 0.0f;
		}
		for (int l59 = 0; l59 < 2; l59 = l59 + 1) {
			fRec62[l59] = 0.0f;
		}
		for (int l60 = 0; l60 < 2; l60 = l60 + 1) {
			iRec68[l60] = 0;
		}
		for (int l61 = 0; l61 < 2; l61 = l61 + 1) {
			fRec71[l61] = 0.0f;
		}
		for (int l62 = 0; l62 < 2; l62 = l62 + 1) {
			fVec8[l62] = 0.0f;
		}
		for (int l63 = 0; l63 < 2; l63 = l63 + 1) {
			fRec70[l63] = 0.0f;
		}
		for (int l64 = 0; l64 < 2; l64 = l64 + 1) {
			fRec69[l64] = 0.0f;
		}
		for (int l65 = 0; l65 < 2; l65 = l65 + 1) {
			iVec9[l65] = 0;
		}
		for (int l66 = 0; l66 < 2; l66 = l66 + 1) {
			iRec67[l66] = 0;
		}
		for (int l67 = 0; l67 < 2; l67 = l67 + 1) {
			iRec72[l67] = 0;
		}
		for (int l68 = 0; l68 < 3; l68 = l68 + 1) {
			fRec73[l68] = 0.0f;
		}
		for (int l69 = 0; l69 < 3; l69 = l69 + 1) {
			fRec66[l69] = 0.0f;
		}
		for (int l70 = 0; l70 < 3; l70 = l70 + 1) {
			fRec75[l70] = 0.0f;
		}
		for (int l71 = 0; l71 < 3; l71 = l71 + 1) {
			fRec74[l71] = 0.0f;
		}
		for (int l72 = 0; l72 < 3; l72 = l72 + 1) {
			fRec77[l72] = 0.0f;
		}
		for (int l73 = 0; l73 < 3; l73 = l73 + 1) {
			fRec76[l73] = 0.0f;
		}
		for (int l74 = 0; l74 < 3; l74 = l74 + 1) {
			fRec65[l74] = 0.0f;
		}
		for (int l75 = 0; l75 < 2; l75 = l75 + 1) {
			fRec79[l75] = 0.0f;
		}
		for (int l76 = 0; l76 < 2; l76 = l76 + 1) {
			fRec80[l76] = 0.0f;
		}
		for (int l77 = 0; l77 < 2; l77 = l77 + 1) {
			fRec78[l77] = 0.0f;
		}
		for (int l78 = 0; l78 < 2; l78 = l78 + 1) {
			fRec81[l78] = 0.0f;
		}
		for (int l79 = 0; l79 < 2; l79 = l79 + 1) {
			fRec82[l79] = 0.0f;
		}
		for (int l80 = 0; l80 < 2; l80 = l80 + 1) {
			iRec84[l80] = 0;
		}
		for (int l81 = 0; l81 < 2; l81 = l81 + 1) {
			fRec87[l81] = 0.0f;
		}
		for (int l82 = 0; l82 < 2; l82 = l82 + 1) {
			fVec10[l82] = 0.0f;
		}
		for (int l83 = 0; l83 < 2; l83 = l83 + 1) {
			fRec86[l83] = 0.0f;
		}
		for (int l84 = 0; l84 < 2; l84 = l84 + 1) {
			fRec85[l84] = 0.0f;
		}
		for (int l85 = 0; l85 < 2; l85 = l85 + 1) {
			fRec88[l85] = 0.0f;
		}
		for (int l86 = 0; l86 < 2; l86 = l86 + 1) {
			fRec83[l86] = 0.0f;
		}
		for (int l87 = 0; l87 < 2; l87 = l87 + 1) {
			fRec89[l87] = 0.0f;
		}
		for (int l88 = 0; l88 < 2; l88 = l88 + 1) {
			fRec91[l88] = 0.0f;
		}
		for (int l89 = 0; l89 < 2; l89 = l89 + 1) {
			fRec92[l89] = 0.0f;
		}
		for (int l90 = 0; l90 < 2; l90 = l90 + 1) {
			fRec90[l90] = 0.0f;
		}
		for (int l91 = 0; l91 < 2; l91 = l91 + 1) {
			fRec93[l91] = 0.0f;
		}
		for (int l92 = 0; l92 < 2; l92 = l92 + 1) {
			fRec94[l92] = 0.0f;
		}
		for (int l93 = 0; l93 < 2; l93 = l93 + 1) {
			fRec98[l93] = 0.0f;
		}
		for (int l94 = 0; l94 < 2; l94 = l94 + 1) {
			fVec11[l94] = 0.0f;
		}
		for (int l95 = 0; l95 < 2; l95 = l95 + 1) {
			fRec97[l95] = 0.0f;
		}
		for (int l96 = 0; l96 < 2; l96 = l96 + 1) {
			fRec96[l96] = 0.0f;
		}
		for (int l97 = 0; l97 < 2; l97 = l97 + 1) {
			fRec95[l97] = 0.0f;
		}
		for (int l98 = 0; l98 < 2; l98 = l98 + 1) {
			fRec99[l98] = 0.0f;
		}
		for (int l99 = 0; l99 < 2; l99 = l99 + 1) {
			fRec101[l99] = 0.0f;
		}
		for (int l100 = 0; l100 < 2; l100 = l100 + 1) {
			fRec102[l100] = 0.0f;
		}
		for (int l101 = 0; l101 < 2; l101 = l101 + 1) {
			fRec100[l101] = 0.0f;
		}
		for (int l102 = 0; l102 < 2; l102 = l102 + 1) {
			fRec103[l102] = 0.0f;
		}
		for (int l103 = 0; l103 < 2; l103 = l103 + 1) {
			fRec104[l103] = 0.0f;
		}
		for (int l104 = 0; l104 < 2; l104 = l104 + 1) {
			fRec108[l104] = 0.0f;
		}
		for (int l105 = 0; l105 < 2; l105 = l105 + 1) {
			fVec12[l105] = 0.0f;
		}
		for (int l106 = 0; l106 < 2; l106 = l106 + 1) {
			fRec107[l106] = 0.0f;
		}
		for (int l107 = 0; l107 < 2; l107 = l107 + 1) {
			fRec106[l107] = 0.0f;
		}
		for (int l108 = 0; l108 < 2; l108 = l108 + 1) {
			fRec105[l108] = 0.0f;
		}
		for (int l109 = 0; l109 < 2; l109 = l109 + 1) {
			fRec109[l109] = 0.0f;
		}
		for (int l110 = 0; l110 < 2; l110 = l110 + 1) {
			fRec111[l110] = 0.0f;
		}
		for (int l111 = 0; l111 < 2; l111 = l111 + 1) {
			fRec112[l111] = 0.0f;
		}
		for (int l112 = 0; l112 < 2; l112 = l112 + 1) {
			fRec110[l112] = 0.0f;
		}
		for (int l113 = 0; l113 < 2; l113 = l113 + 1) {
			fRec113[l113] = 0.0f;
		}
		for (int l114 = 0; l114 < 2; l114 = l114 + 1) {
			fRec114[l114] = 0.0f;
		}
		for (int l115 = 0; l115 < 2; l115 = l115 + 1) {
			iRec116[l115] = 0;
		}
		for (int l116 = 0; l116 < 2; l116 = l116 + 1) {
			fRec119[l116] = 0.0f;
		}
		for (int l117 = 0; l117 < 2; l117 = l117 + 1) {
			fVec13[l117] = 0.0f;
		}
		for (int l118 = 0; l118 < 2; l118 = l118 + 1) {
			fRec118[l118] = 0.0f;
		}
		for (int l119 = 0; l119 < 2; l119 = l119 + 1) {
			fRec117[l119] = 0.0f;
		}
		for (int l120 = 0; l120 < 2; l120 = l120 + 1) {
			fRec115[l120] = 0.0f;
		}
		for (int l121 = 0; l121 < 2; l121 = l121 + 1) {
			fRec120[l121] = 0.0f;
		}
		for (int l122 = 0; l122 < 2; l122 = l122 + 1) {
			fRec122[l122] = 0.0f;
		}
		for (int l123 = 0; l123 < 2; l123 = l123 + 1) {
			fRec123[l123] = 0.0f;
		}
		for (int l124 = 0; l124 < 2; l124 = l124 + 1) {
			fRec121[l124] = 0.0f;
		}
		for (int l125 = 0; l125 < 2; l125 = l125 + 1) {
			fRec130[l125] = 0.0f;
		}
		for (int l126 = 0; l126 < 2; l126 = l126 + 1) {
			fRec131[l126] = 0.0f;
		}
		for (int l127 = 0; l127 < 2; l127 = l127 + 1) {
			fRec129[l127] = 0.0f;
		}
		for (int l128 = 0; l128 < 2; l128 = l128 + 1) {
			fRec128[l128] = 0.0f;
		}
		for (int l129 = 0; l129 < 2; l129 = l129 + 1) {
			fRec127[l129] = 0.0f;
		}
		for (int l130 = 0; l130 < 2; l130 = l130 + 1) {
			fRec126[l130] = 0.0f;
		}
		for (int l131 = 0; l131 < 2; l131 = l131 + 1) {
			fRec125[l131] = 0.0f;
		}
		for (int l132 = 0; l132 < 2; l132 = l132 + 1) {
			fRec124[l132] = 0.0f;
		}
		for (int l133 = 0; l133 < 2; l133 = l133 + 1) {
			fRec132[l133] = 0.0f;
		}
		for (int l134 = 0; l134 < 2; l134 = l134 + 1) {
			fRec133[l134] = 0.0f;
		}
		for (int l135 = 0; l135 < 2; l135 = l135 + 1) {
			fRec134[l135] = 0.0f;
		}
		for (int l136 = 0; l136 < 2; l136 = l136 + 1) {
			fRec135[l136] = 0.0f;
		}
		for (int l137 = 0; l137 < 2; l137 = l137 + 1) {
			fRec136[l137] = 0.0f;
		}
		for (int l138 = 0; l138 < 2; l138 = l138 + 1) {
			fRec137[l138] = 0.0f;
		}
		for (int l139 = 0; l139 < 2; l139 = l139 + 1) {
			fRec138[l139] = 0.0f;
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
	
	virtual Insects* clone() {
		return new Insects();
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
			int iTemp0 = 1 - iVec0[1];
			float fTemp1 = ((iTemp0) ? 0.0f : fConst6 + fRec1[1]);
			fRec1[0] = fTemp1 - std::floor(fTemp1);
			float fTemp2 = ((iTemp0) ? 0.0f : fConst7 + fRec2[1]);
			fRec2[0] = fTemp2 - std::floor(fTemp2);
			float fTemp3 = ((iTemp0) ? 0.0f : fConst8 + fRec3[1]);
			fRec3[0] = fTemp3 - std::floor(fTemp3);
			float fTemp4 = ((iTemp0) ? 0.0f : fConst9 + fRec4[1]);
			fRec4[0] = fTemp4 - std::floor(fTemp4);
			float fTemp5 = std::cos(6.2831855f * fRec4[0]) * std::cos(6.2831855f * fRec3[0]) * std::cos(6.2831855f * fRec2[0]) * std::cos(6.2831855f * fRec1[0]);
			fRec0[0] = fTemp5 - fConst5 * (fConst4 * fRec0[2] + fConst2 * fRec0[1]);
			float fTemp6 = ((iTemp0) ? 0.0f : fConst10 + fRec6[1]);
			fRec6[0] = fTemp6 - std::floor(fTemp6);
			float fTemp7 = ((iTemp0) ? 0.0f : fConst11 + fRec7[1]);
			fRec7[0] = fTemp7 - std::floor(fTemp7);
			float fTemp8 = ((iTemp0) ? 0.0f : fConst12 + fRec8[1]);
			fRec8[0] = fTemp8 - std::floor(fTemp8);
			float fTemp9 = ((iTemp0) ? 0.0f : fConst13 + fRec9[1]);
			fRec9[0] = fTemp9 - std::floor(fTemp9);
			float fTemp10 = std::cos(6.2831855f * fRec9[0]) * std::cos(6.2831855f * fRec8[0]) * std::cos(6.2831855f * fRec7[0]) * std::cos(6.2831855f * fRec6[0]);
			fRec5[0] = fTemp10 - fConst5 * (fConst4 * fRec5[2] + fConst2 * fRec5[1]);
			float fTemp11 = ((iTemp0) ? 0.0f : fConst14 + fRec11[1]);
			fRec11[0] = fTemp11 - std::floor(fTemp11);
			iRec13[0] = 1103515245 * iRec13[1] + 12345;
			float fTemp12 = float(iRec13[0]);
			fVec2[0] = fTemp12;
			float fTemp13 = 4.656613e-10f * fTemp12;
			fRec12[0] = fTemp13 - fConst19 * (fConst18 * fRec12[2] + fConst16 * fRec12[1]);
			float fTemp14 = ((iTemp0) ? 0.0f : fConst25 + fRec18[1]);
			fRec18[0] = fTemp14 - std::floor(fTemp14);
			float fTemp15 = fRec18[0] - fRec18[1];
			fVec3[0] = fTemp15;
			int iTemp16 = (fVec3[1] <= 0.0f) & (fTemp15 > 0.0f);
			fRec17[0] = fRec17[1] * float(1 - iTemp16) + 4.656613e-10f * fTemp12 * float(iTemp16);
			float fTemp17 = 0.5f * (fRec17[0] + 1.0f);
			fRec16[0] = ((std::fabs(4.656613e-10f * fVec2[1] * float((fRec18[0] >= fTemp17) * (fRec18[1] < fTemp17))) > 0.0f) ? std::fabs(fTemp13) : fRec16[1]);
			float fTemp18 = ((iTemp0) ? 0.0f : fRec15[1] + fConst26 * (1.2e+03f * fRec16[0] + 4e+02f));
			fRec15[0] = fTemp18 - std::floor(fTemp18);
			float fTemp19 = ftbl0InsectsSIG0[std::max<int>(0, std::min<int>(int(65536.0f * fRec15[0]), 65535))];
			fRec14[0] = fTemp19 - fConst24 * (fConst23 * fRec14[2] + fConst21 * fRec14[1]);
			float fTemp20 = 0.4f * (0.008f * (fTemp19 - fConst24 * (fRec14[2] + fRec14[0] + 2.0f * fRec14[1])) + fConst19 * (0.08f * fRec12[0] + 0.16f * fRec12[1] + 0.08f * fRec12[2]) + 0.025f * ftbl0InsectsSIG0[std::max<int>(0, std::min<int>(int(65536.0f * fRec11[0]), 65535))] * (fTemp10 - fConst5 * (fRec5[2] + fRec5[0] + 2.0f * fRec5[1]) + (fTemp5 - fConst5 * (fRec0[2] + fRec0[0] + 2.0f * fRec0[1]))));
			iRec22[0] = (iVec0[1] + iRec22[1]) % iConst37;
			float fTemp21 = ((iTemp0) ? 0.0f : fConst38 + fRec25[1]);
			fRec25[0] = fTemp21 - std::floor(fTemp21);
			float fTemp22 = fRec25[0] - fRec25[1];
			fVec4[0] = fTemp22;
			int iTemp23 = (fVec4[1] <= 0.0f) & (fTemp22 > 0.0f);
			fRec24[0] = fRec24[1] * float(1 - iTemp23) + 4.656613e-10f * fTemp12 * float(iTemp23);
			float fTemp24 = 0.5f * (fRec24[0] + 1.0f);
			int iTemp25 = std::fabs(4.656613e-10f * fVec2[1] * float((fRec25[0] >= fTemp24) * (fRec25[1] < fTemp24))) > 0.0f;
			fRec23[0] = ((iTemp25 > 0) ? fConst39 : std::max<float>(0.0f, fRec23[1] + -1.0f));
			int iTemp26 = (fRec23[0] > 0.0f) * (iRec22[0] <= iRec22[1]);
			iVec5[0] = iTemp26;
			iRec21[0] = (iRec21[1] + 1) * (iTemp26 == 0);
			iRec26[0] = iTemp26 + iRec26[1] * (iVec5[1] >= iTemp26);
			float fTemp27 = std::max<float>(0.0f, std::min<float>(float(iRec26[0]), 1.0f) - fConst40 * float(iRec21[0]));
			float fTemp28 = 1.0f - fTemp27;
			float fTemp29 = std::min<float>(0.5f, fTemp28) - std::max<float>(0.9f, fTemp28);
			float fTemp30 = std::tan(fConst41 * (7.2e+02f * fTemp29 + 2.4e+03f));
			float fTemp31 = 1.0f / fTemp30;
			float fTemp32 = (fTemp31 + 0.33333334f) / fTemp30 + 1.0f;
			float fTemp33 = 18.0f * Insects_faustpower2_f(std::min<float>(0.5f, fTemp27) - std::max<float>(0.5f, fTemp27));
			float fTemp34 = 1.0f / (14884.0f * Insects_faustpower2_f(fTemp33 + (-1.0f - float(int(fTemp33 + -1.0f)))) + 1.0f);
			fRec27[0] = fTemp34 - (fRec27[2] * ((fTemp31 + -0.33333334f) / fTemp30 + 1.0f) + 2.0f * fRec27[1] * (1.0f - 1.0f / Insects_faustpower2_f(fTemp30))) / fTemp32;
			fRec20[0] = (fRec27[0] - fRec27[2]) / (fTemp30 * fTemp32) - fConst36 * (fConst35 * fRec20[2] + fConst33 * fRec20[1]);
			float fTemp35 = std::tan(fConst41 * (1.2e+02f * fTemp29 + 8e+02f));
			float fTemp36 = 1.0f / fTemp35;
			float fTemp37 = (fTemp36 + 0.2f) / fTemp35 + 1.0f;
			fRec29[0] = fTemp34 - (fRec29[2] * ((fTemp36 + -0.2f) / fTemp35 + 1.0f) + 2.0f * fRec29[1] * (1.0f - 1.0f / Insects_faustpower2_f(fTemp35))) / fTemp37;
			fRec28[0] = (fRec29[0] - fRec29[2]) / (fTemp35 * fTemp37) - fConst36 * (fConst35 * fRec28[2] + fConst33 * fRec28[1]);
			float fTemp38 = std::tan(fConst41 * (2.7e+02f * fTemp29 + 1.6e+03f));
			float fTemp39 = 1.0f / fTemp38;
			float fTemp40 = (fTemp39 + 0.25f) / fTemp38 + 1.0f;
			fRec31[0] = fTemp34 - (fRec31[2] * ((fTemp39 + -0.25f) / fTemp38 + 1.0f) + 2.0f * fRec31[1] * (1.0f - 1.0f / Insects_faustpower2_f(fTemp38))) / fTemp40;
			fRec30[0] = (fRec31[0] - fRec31[2]) / (fTemp38 * fTemp40) - fConst36 * (fConst35 * fRec30[2] + fConst33 * fRec30[1]);
			float fTemp41 = fConst36 * (fRec30[2] + fRec30[0] + 2.0f * fRec30[1] + 0.45f * (fRec28[2] + fRec28[0] + 2.0f * fRec28[1]) + 0.45f * (fRec20[2] + fRec20[0] + 2.0f * fRec20[1]));
			fRec19[0] = fTemp41 - fConst31 * (fConst30 * fRec19[2] + fConst28 * fRec19[1]);
			float fTemp42 = fTemp41 - fConst31 * (fRec19[2] + fRec19[0] + 2.0f * fRec19[1]);
			int iTemp43 = 1103515245 * (iRec34[1] + 12345);
			int iTemp44 = 1103515245 * (iTemp43 + 12345);
			int iTemp45 = 1103515245 * (iTemp44 + 12345);
			int iTemp46 = 1103515245 * (iTemp45 + 12345);
			int iTemp47 = 1103515245 * (iTemp46 + 12345);
			int iTemp48 = 1103515245 * (iTemp47 + 12345);
			int iTemp49 = 1103515245 * (iTemp48 + 12345);
			int iTemp50 = 1103515245 * (iTemp49 + 12345);
			int iTemp51 = 1103515245 * (iTemp50 + 12345);
			int iTemp52 = 1103515245 * (iTemp51 + 12345);
			int iTemp53 = 1103515245 * (iTemp52 + 12345);
			int iTemp54 = 1103515245 * (iTemp53 + 12345);
			int iTemp55 = 1103515245 * (iTemp54 + 12345);
			iRec34[0] = 1103515245 * (iTemp55 + 12345);
			int iRec35 = iTemp55;
			int iRec36 = iTemp54;
			int iRec37 = iTemp53;
			int iRec38 = iTemp52;
			int iRec39 = iTemp51;
			int iRec40 = iTemp50;
			int iRec41 = iTemp49;
			int iRec42 = iTemp48;
			int iRec43 = iTemp47;
			int iRec44 = iTemp46;
			int iRec45 = iTemp45;
			int iRec46 = iTemp44;
			int iRec47 = iTemp43;
			fRec33[0] = ((iTemp25) ? std::fabs(4.656613e-10f * float(iRec40)) : fRec33[1]);
			fRec48[0] = ((iTemp25) ? std::fabs(4.656613e-10f * float(iRec47)) : fRec48[1]);
			float fTemp56 = fRec48[0] + 1.0f;
			fRec32[0] = 5e-05f * fTemp56 * std::sqrt(std::max<float>(0.0f, 1.0f - 2.0f * fRec48[0] * std::fabs(std::fmod(fRec33[0] + 1.5f, 1.0f) + -0.5f))) + 0.9999f * fRec32[1];
			iRec52[0] = (iVec0[1] + iRec52[1]) % iConst42;
			int iTemp57 = iRec52[0] <= iRec52[1];
			float fTemp58 = ((iTemp0) ? 0.0f : fConst43 + fRec55[1]);
			fRec55[0] = fTemp58 - std::floor(fTemp58);
			float fTemp59 = fRec55[0] - fRec55[1];
			fVec6[0] = fTemp59;
			int iTemp60 = (fVec6[1] <= 0.0f) & (fTemp59 > 0.0f);
			fRec54[0] = fRec54[1] * float(1 - iTemp60) + 4.656613e-10f * fTemp12 * float(iTemp60);
			float fTemp61 = 0.5f * (fRec54[0] + 1.0f);
			int iTemp62 = std::fabs(4.656613e-10f * fVec2[1] * float((fRec55[0] >= fTemp61) * (fRec55[1] < fTemp61))) > 0.0f;
			fRec53[0] = ((iTemp62 > 0) ? fConst44 : std::max<float>(0.0f, fRec53[1] + -1.0f));
			int iTemp63 = (fRec53[0] > 0.0f) * iTemp57;
			iVec7[0] = iTemp63;
			iRec51[0] = (iRec51[1] + 1) * (iTemp63 == 0);
			iRec56[0] = iTemp63 + iRec56[1] * (iVec7[1] >= iTemp63);
			float fTemp64 = std::max<float>(0.0f, std::min<float>(float(iRec56[0]), 1.0f) - fConst45 * float(iRec51[0]));
			float fTemp65 = 1.0f - fTemp64;
			float fTemp66 = std::min<float>(0.5f, fTemp65) - std::max<float>(0.9f, fTemp65);
			float fTemp67 = std::tan(fConst41 * (7.2e+02f * fTemp66 + 1.8e+03f));
			float fTemp68 = 1.0f / fTemp67;
			float fTemp69 = (fTemp68 + 0.33333334f) / fTemp67 + 1.0f;
			float fTemp70 = 18.0f * Insects_faustpower2_f(std::min<float>(0.5f, fTemp64) - std::max<float>(0.5f, fTemp64));
			float fTemp71 = 1.0f / (14884.0f * Insects_faustpower2_f(fTemp70 + (-1.0f - float(int(fTemp70 + -1.0f)))) + 1.0f);
			fRec57[0] = fTemp71 - (fRec57[2] * ((fTemp68 + -0.33333334f) / fTemp67 + 1.0f) + 2.0f * fRec57[1] * (1.0f - 1.0f / Insects_faustpower2_f(fTemp67))) / fTemp69;
			fRec50[0] = (fRec57[0] - fRec57[2]) / (fTemp67 * fTemp69) - fConst36 * (fConst35 * fRec50[2] + fConst33 * fRec50[1]);
			float fTemp72 = std::tan(fConst41 * (1.2e+02f * fTemp66 + 6e+02f));
			float fTemp73 = 1.0f / fTemp72;
			float fTemp74 = (fTemp73 + 0.2f) / fTemp72 + 1.0f;
			fRec59[0] = fTemp71 - (fRec59[2] * ((fTemp73 + -0.2f) / fTemp72 + 1.0f) + 2.0f * fRec59[1] * (1.0f - 1.0f / Insects_faustpower2_f(fTemp72))) / fTemp74;
			fRec58[0] = (fRec59[0] - fRec59[2]) / (fTemp72 * fTemp74) - fConst36 * (fConst35 * fRec58[2] + fConst33 * fRec58[1]);
			float fTemp75 = std::tan(fConst41 * (2.7e+02f * fTemp66 + 1.2e+03f));
			float fTemp76 = 1.0f / fTemp75;
			float fTemp77 = (fTemp76 + 0.25f) / fTemp75 + 1.0f;
			fRec61[0] = fTemp71 - (fRec61[2] * ((fTemp76 + -0.25f) / fTemp75 + 1.0f) + 2.0f * fRec61[1] * (1.0f - 1.0f / Insects_faustpower2_f(fTemp75))) / fTemp77;
			fRec60[0] = (fRec61[0] - fRec61[2]) / (fTemp75 * fTemp77) - fConst36 * (fConst35 * fRec60[2] + fConst33 * fRec60[1]);
			float fTemp78 = fConst36 * (fRec60[2] + fRec60[0] + 2.0f * fRec60[1] + 0.45f * (fRec58[2] + fRec58[0] + 2.0f * fRec58[1]) + 0.45f * (fRec50[2] + fRec50[0] + 2.0f * fRec50[1]));
			fRec49[0] = fTemp78 - fConst31 * (fConst30 * fRec49[2] + fConst28 * fRec49[1]);
			float fTemp79 = fTemp78 - fConst31 * (fRec49[2] + fRec49[0] + 2.0f * fRec49[1]);
			fRec63[0] = ((iTemp62) ? std::fabs(4.656613e-10f * float(iRec39)) : fRec63[1]);
			fRec64[0] = ((iTemp62) ? std::fabs(4.656613e-10f * float(iRec46)) : fRec64[1]);
			float fTemp80 = fRec64[0] + 1.0f;
			fRec62[0] = 5e-05f * fTemp80 * std::sqrt(std::max<float>(0.0f, 1.0f - 2.0f * fRec64[0] * std::fabs(std::fmod(fRec63[0] + 1.5f, 1.0f) + -0.5f))) + 0.9999f * fRec62[1];
			iRec68[0] = (iVec0[1] + iRec68[1]) % iConst47;
			int iTemp81 = iRec68[0] <= iRec68[1];
			float fTemp82 = ((iTemp0) ? 0.0f : fConst48 + fRec71[1]);
			fRec71[0] = fTemp82 - std::floor(fTemp82);
			float fTemp83 = fRec71[0] - fRec71[1];
			fVec8[0] = fTemp83;
			int iTemp84 = (fVec8[1] <= 0.0f) & (fTemp83 > 0.0f);
			fRec70[0] = fRec70[1] * float(1 - iTemp84) + 4.656613e-10f * fTemp12 * float(iTemp84);
			float fTemp85 = 0.5f * (fRec70[0] + 1.0f);
			int iTemp86 = std::fabs(4.656613e-10f * fVec2[1] * float((fRec71[0] >= fTemp85) * (fRec71[1] < fTemp85))) > 0.0f;
			fRec69[0] = ((iTemp86 > 0) ? fConst39 : std::max<float>(0.0f, fRec69[1] + -1.0f));
			int iTemp87 = (fRec69[0] > 0.0f) * iTemp81;
			iVec9[0] = iTemp87;
			iRec67[0] = (iRec67[1] + 1) * (iTemp87 == 0);
			iRec72[0] = iTemp87 + iRec72[1] * (iVec9[1] >= iTemp87);
			float fTemp88 = std::max<float>(0.0f, std::min<float>(float(iRec72[0]), 1.0f) - fConst49 * float(iRec67[0]));
			float fTemp89 = 1.0f - fTemp88;
			float fTemp90 = std::min<float>(0.5f, fTemp89) - std::max<float>(0.9f, fTemp89);
			float fTemp91 = std::tan(fConst41 * (7.2e+02f * fTemp90 + 2.7e+03f));
			float fTemp92 = 1.0f / fTemp91;
			float fTemp93 = (fTemp92 + 0.33333334f) / fTemp91 + 1.0f;
			float fTemp94 = 18.0f * Insects_faustpower2_f(std::min<float>(0.5f, fTemp88) - std::max<float>(0.5f, fTemp88));
			float fTemp95 = 1.0f / (14884.0f * Insects_faustpower2_f(fTemp94 + (-1.0f - float(int(fTemp94 + -1.0f)))) + 1.0f);
			fRec73[0] = fTemp95 - (fRec73[2] * ((fTemp92 + -0.33333334f) / fTemp91 + 1.0f) + 2.0f * fRec73[1] * (1.0f - 1.0f / Insects_faustpower2_f(fTemp91))) / fTemp93;
			fRec66[0] = (fRec73[0] - fRec73[2]) / (fTemp91 * fTemp93) - fConst36 * (fConst35 * fRec66[2] + fConst33 * fRec66[1]);
			float fTemp96 = std::tan(fConst41 * (1.2e+02f * fTemp90 + 9e+02f));
			float fTemp97 = 1.0f / fTemp96;
			float fTemp98 = (fTemp97 + 0.2f) / fTemp96 + 1.0f;
			fRec75[0] = fTemp95 - (fRec75[2] * ((fTemp97 + -0.2f) / fTemp96 + 1.0f) + 2.0f * fRec75[1] * (1.0f - 1.0f / Insects_faustpower2_f(fTemp96))) / fTemp98;
			fRec74[0] = (fRec75[0] - fRec75[2]) / (fTemp96 * fTemp98) - fConst36 * (fConst35 * fRec74[2] + fConst33 * fRec74[1]);
			float fTemp99 = std::tan(fConst41 * (2.7e+02f * fTemp90 + 1.8e+03f));
			float fTemp100 = 1.0f / fTemp99;
			float fTemp101 = (fTemp100 + 0.25f) / fTemp99 + 1.0f;
			fRec77[0] = fTemp95 - (fRec77[2] * ((fTemp100 + -0.25f) / fTemp99 + 1.0f) + 2.0f * fRec77[1] * (1.0f - 1.0f / Insects_faustpower2_f(fTemp99))) / fTemp101;
			fRec76[0] = (fRec77[0] - fRec77[2]) / (fTemp99 * fTemp101) - fConst36 * (fConst35 * fRec76[2] + fConst33 * fRec76[1]);
			float fTemp102 = fConst36 * (fRec76[2] + fRec76[0] + 2.0f * fRec76[1] + 0.45f * (fRec74[2] + fRec74[0] + 2.0f * fRec74[1]) + 0.45f * (fRec66[2] + fRec66[0] + 2.0f * fRec66[1]));
			fRec65[0] = fTemp102 - fConst31 * (fConst30 * fRec65[2] + fConst28 * fRec65[1]);
			float fTemp103 = fTemp102 - fConst31 * (fRec65[2] + fRec65[0] + 2.0f * fRec65[1]);
			fRec79[0] = ((iTemp86) ? std::fabs(4.656613e-10f * float(iRec38)) : fRec79[1]);
			fRec80[0] = ((iTemp86) ? std::fabs(4.656613e-10f * float(iRec45)) : fRec80[1]);
			float fTemp104 = fRec80[0] + 1.0f;
			fRec78[0] = 5e-05f * fTemp104 * std::sqrt(std::max<float>(0.0f, 1.0f - 2.0f * fRec80[0] * std::fabs(std::fmod(fRec79[0] + 1.5f, 1.0f) + -0.5f))) + 0.9999f * fRec78[1];
			float fTemp105 = ((iTemp0) ? 0.0f : fConst50 + fRec81[1]);
			fRec81[0] = fTemp105 - std::floor(fTemp105);
			float fTemp106 = ((iTemp0) ? 0.0f : fConst51 + fRec82[1]);
			fRec82[0] = fTemp106 - std::floor(fTemp106);
			float fTemp107 = ftbl0InsectsSIG0[std::max<int>(0, std::min<int>(int(65536.0f * fRec82[0]), 65535))] + ftbl0InsectsSIG0[std::max<int>(0, std::min<int>(int(65536.0f * fRec81[0]), 65535))];
			iRec84[0] = (iVec0[1] + iRec84[1]) % iConst52;
			float fTemp108 = ((iTemp0) ? 0.0f : fConst53 + fRec87[1]);
			fRec87[0] = fTemp108 - std::floor(fTemp108);
			float fTemp109 = fRec87[0] - fRec87[1];
			fVec10[0] = fTemp109;
			int iTemp110 = (fVec10[1] <= 0.0f) & (fTemp109 > 0.0f);
			fRec86[0] = fRec86[1] * float(1 - iTemp110) + 4.656613e-10f * fTemp12 * float(iTemp110);
			float fTemp111 = 0.5f * (fRec86[0] + 1.0f);
			int iTemp112 = std::fabs(4.656613e-10f * fVec2[1] * float((fRec87[0] >= fTemp111) * (fRec87[1] < fTemp111))) > 0.0f;
			fRec85[0] = ((iTemp112 > 0) ? fConst54 : std::max<float>(0.0f, fRec85[1] + -1.0f));
			int iTemp113 = (fRec85[0] > 0.0f) * (iRec84[0] <= iRec84[1]);
			float fTemp114 = ((iTemp0) ? 0.0f : fConst55 + fRec88[1]);
			fRec88[0] = fTemp114 - std::floor(fTemp114);
			fRec83[0] = ((iTemp113) ? fRec88[0] : fRec83[1]);
			float fTemp115 = 44.0f * (fRec88[0] + (1.0f - (fRec83[0] + float(int(fRec88[0] + (1.0f - fRec83[0]))))));
			float fTemp116 = std::max<float>(1.0f, std::min<float>(4.0f, fTemp115));
			float fTemp117 = std::max<float>(0.0f, std::min<float>(1.0f, fTemp115));
			float fTemp118 = std::max<float>(0.0f, std::min<float>(1.0f, std::sin(6.2831855f * (fTemp117 + fTemp116 - (float(int(fTemp117)) + float(int(fTemp116)))))));
			fRec89[0] = ((iTemp113 > 0) ? fConst56 : std::max<float>(0.0f, fRec89[1] + -1.0f));
			float fTemp119 = float(fRec89[0] > 0.0f);
			fRec91[0] = ((iTemp112) ? std::fabs(4.656613e-10f * float(iRec37)) : fRec91[1]);
			fRec92[0] = ((iTemp112) ? std::fabs(4.656613e-10f * float(iRec44)) : fRec92[1]);
			float fTemp120 = fRec92[0] + 1.0f;
			fRec90[0] = 5e-05f * fTemp120 * std::sqrt(std::max<float>(0.0f, 1.0f - 2.0f * fRec92[0] * std::fabs(std::fmod(fRec91[0] + 1.5f, 1.0f) + -0.5f))) + 0.9999f * fRec90[1];
			float fTemp121 = ((iTemp0) ? 0.0f : fConst57 + fRec93[1]);
			fRec93[0] = fTemp121 - std::floor(fTemp121);
			float fTemp122 = ((iTemp0) ? 0.0f : fConst58 + fRec94[1]);
			fRec94[0] = fTemp122 - std::floor(fTemp122);
			float fTemp123 = ftbl0InsectsSIG0[std::max<int>(0, std::min<int>(int(65536.0f * fRec94[0]), 65535))] + ftbl0InsectsSIG0[std::max<int>(0, std::min<int>(int(65536.0f * fRec93[0]), 65535))];
			float fTemp124 = ((iTemp0) ? 0.0f : fConst59 + fRec98[1]);
			fRec98[0] = fTemp124 - std::floor(fTemp124);
			float fTemp125 = fRec98[0] - fRec98[1];
			fVec11[0] = fTemp125;
			int iTemp126 = (fVec11[1] <= 0.0f) & (fTemp125 > 0.0f);
			fRec97[0] = fRec97[1] * float(1 - iTemp126) + 4.656613e-10f * fTemp12 * float(iTemp126);
			float fTemp127 = 0.5f * (fRec97[0] + 1.0f);
			int iTemp128 = std::fabs(4.656613e-10f * fVec2[1] * float((fRec98[0] >= fTemp127) * (fRec98[1] < fTemp127))) > 0.0f;
			fRec96[0] = ((iTemp128 > 0) ? fConst60 : std::max<float>(0.0f, fRec96[1] + -1.0f));
			int iTemp129 = (fRec96[0] > 0.0f) * iTemp81;
			fRec95[0] = ((iTemp129) ? fRec88[0] : fRec95[1]);
			float fTemp130 = 44.0f * (fRec88[0] + (1.0f - (fRec95[0] + float(int(fRec88[0] + (1.0f - fRec95[0]))))));
			float fTemp131 = std::max<float>(1.0f, std::min<float>(4.0f, fTemp130));
			float fTemp132 = std::max<float>(0.0f, std::min<float>(1.0f, fTemp130));
			float fTemp133 = std::max<float>(0.0f, std::min<float>(1.0f, std::sin(6.2831855f * (fTemp132 + fTemp131 - (float(int(fTemp132)) + float(int(fTemp131)))))));
			fRec99[0] = ((iTemp129 > 0) ? fConst56 : std::max<float>(0.0f, fRec99[1] + -1.0f));
			float fTemp134 = float(fRec99[0] > 0.0f);
			fRec101[0] = ((iTemp128) ? std::fabs(4.656613e-10f * float(iRec36)) : fRec101[1]);
			fRec102[0] = ((iTemp128) ? std::fabs(4.656613e-10f * float(iRec43)) : fRec102[1]);
			float fTemp135 = fRec102[0] + 1.0f;
			fRec100[0] = 5e-05f * fTemp135 * std::sqrt(std::max<float>(0.0f, 1.0f - 2.0f * fRec102[0] * std::fabs(std::fmod(fRec101[0] + 1.5f, 1.0f) + -0.5f))) + 0.9999f * fRec100[1];
			float fTemp136 = ((iTemp0) ? 0.0f : fConst61 + fRec103[1]);
			fRec103[0] = fTemp136 - std::floor(fTemp136);
			float fTemp137 = ((iTemp0) ? 0.0f : fConst62 + fRec104[1]);
			fRec104[0] = fTemp137 - std::floor(fTemp137);
			float fTemp138 = ftbl0InsectsSIG0[std::max<int>(0, std::min<int>(int(65536.0f * fRec104[0]), 65535))] + ftbl0InsectsSIG0[std::max<int>(0, std::min<int>(int(65536.0f * fRec103[0]), 65535))];
			float fTemp139 = ((iTemp0) ? 0.0f : fConst63 + fRec108[1]);
			fRec108[0] = fTemp139 - std::floor(fTemp139);
			float fTemp140 = fRec108[0] - fRec108[1];
			fVec12[0] = fTemp140;
			int iTemp141 = (fVec12[1] <= 0.0f) & (fTemp140 > 0.0f);
			fRec107[0] = fRec107[1] * float(1 - iTemp141) + 4.656613e-10f * fTemp12 * float(iTemp141);
			float fTemp142 = 0.5f * (fRec107[0] + 1.0f);
			int iTemp143 = std::fabs(4.656613e-10f * fVec2[1] * float((fRec108[0] >= fTemp142) * (fRec108[1] < fTemp142))) > 0.0f;
			fRec106[0] = ((iTemp143 > 0) ? fConst64 : std::max<float>(0.0f, fRec106[1] + -1.0f));
			int iTemp144 = (fRec106[0] > 0.0f) * iTemp57;
			fRec105[0] = ((iTemp144) ? fRec88[0] : fRec105[1]);
			float fTemp145 = 44.0f * (fRec88[0] + (1.0f - (fRec105[0] + float(int(fRec88[0] + (1.0f - fRec105[0]))))));
			float fTemp146 = std::max<float>(1.0f, std::min<float>(4.0f, fTemp145));
			float fTemp147 = std::max<float>(0.0f, std::min<float>(1.0f, fTemp145));
			float fTemp148 = std::max<float>(0.0f, std::min<float>(1.0f, std::sin(6.2831855f * (fTemp147 + fTemp146 - (float(int(fTemp147)) + float(int(fTemp146)))))));
			fRec109[0] = ((iTemp144 > 0) ? fConst56 : std::max<float>(0.0f, fRec109[1] + -1.0f));
			float fTemp149 = float(fRec109[0] > 0.0f);
			fRec111[0] = ((iTemp143) ? std::fabs(4.656613e-10f * float(iRec35)) : fRec111[1]);
			fRec112[0] = ((iTemp143) ? std::fabs(4.656613e-10f * float(iRec42)) : fRec112[1]);
			float fTemp150 = fRec112[0] + 1.0f;
			fRec110[0] = 5e-05f * fTemp150 * std::sqrt(std::max<float>(0.0f, 1.0f - 2.0f * fRec112[0] * std::fabs(std::fmod(fRec111[0] + 1.5f, 1.0f) + -0.5f))) + 0.9999f * fRec110[1];
			float fTemp151 = ((iTemp0) ? 0.0f : fConst65 + fRec113[1]);
			fRec113[0] = fTemp151 - std::floor(fTemp151);
			float fTemp152 = ((iTemp0) ? 0.0f : fConst66 + fRec114[1]);
			fRec114[0] = fTemp152 - std::floor(fTemp152);
			float fTemp153 = ftbl0InsectsSIG0[std::max<int>(0, std::min<int>(int(65536.0f * fRec114[0]), 65535))] + ftbl0InsectsSIG0[std::max<int>(0, std::min<int>(int(65536.0f * fRec113[0]), 65535))];
			iRec116[0] = (iVec0[1] + iRec116[1]) % iConst67;
			float fTemp154 = ((iTemp0) ? 0.0f : fConst68 + fRec119[1]);
			fRec119[0] = fTemp154 - std::floor(fTemp154);
			float fTemp155 = fRec119[0] - fRec119[1];
			fVec13[0] = fTemp155;
			int iTemp156 = (fVec13[1] <= 0.0f) & (fTemp155 > 0.0f);
			fRec118[0] = fRec118[1] * float(1 - iTemp156) + 4.656613e-10f * fTemp12 * float(iTemp156);
			float fTemp157 = 0.5f * (fRec118[0] + 1.0f);
			int iTemp158 = std::fabs(4.656613e-10f * fVec2[1] * float((fRec119[0] >= fTemp157) * (fRec119[1] < fTemp157))) > 0.0f;
			fRec117[0] = ((iTemp158 > 0) ? fConst69 : std::max<float>(0.0f, fRec117[1] + -1.0f));
			int iTemp159 = (fRec117[0] > 0.0f) * (iRec116[0] <= iRec116[1]);
			fRec115[0] = ((iTemp159) ? fRec88[0] : fRec115[1]);
			float fTemp160 = 44.0f * (fRec88[0] + (1.0f - (fRec115[0] + float(int(fRec88[0] + (1.0f - fRec115[0]))))));
			float fTemp161 = std::max<float>(1.0f, std::min<float>(4.0f, fTemp160));
			float fTemp162 = std::max<float>(0.0f, std::min<float>(1.0f, fTemp160));
			float fTemp163 = std::max<float>(0.0f, std::min<float>(1.0f, std::sin(6.2831855f * (fTemp162 + fTemp161 - (float(int(fTemp162)) + float(int(fTemp161)))))));
			fRec120[0] = ((iTemp159 > 0) ? fConst56 : std::max<float>(0.0f, fRec120[1] + -1.0f));
			float fTemp164 = float(fRec120[0] > 0.0f);
			fRec122[0] = ((iTemp158) ? std::fabs(4.656613e-10f * float(iRec34[0])) : fRec122[1]);
			fRec123[0] = ((iTemp158) ? std::fabs(4.656613e-10f * float(iRec41)) : fRec123[1]);
			float fTemp165 = fRec123[0] + 1.0f;
			fRec121[0] = 5e-05f * fTemp165 * std::sqrt(std::max<float>(0.0f, 1.0f - 2.0f * fRec123[0] * std::fabs(std::fmod(fRec122[0] + 1.5f, 1.0f) + -0.5f))) + 0.9999f * fRec121[1];
			fRec130[0] = fConst72 * fRec131[1] + fConst71 * fRec130[1];
			fRec131[0] = float(iTemp0) + fConst71 * fRec131[1] - fConst72 * fRec130[1];
			int iTemp166 = (fRec130[1] <= 0.0f) & (fRec130[0] > 0.0f);
			fRec129[0] = fRec129[1] * float(1 - iTemp166) + 4.656613e-10f * fTemp12 * float(iTemp166);
			fRec128[0] = -(fConst75 * (fConst74 * fRec128[1] - (fRec129[0] + fRec129[1])));
			fRec127[0] = -(fConst75 * (fConst74 * fRec127[1] - (fRec128[0] + fRec128[1])));
			fRec126[0] = -(fConst75 * (fConst74 * fRec126[1] - (fRec127[0] + fRec127[1])));
			fRec125[0] = -(fConst75 * (fConst74 * fRec125[1] - (fRec126[0] + fRec126[1])));
			fRec124[0] = -(fConst75 * (fConst74 * fRec124[1] - (fRec125[0] + fRec125[1])));
			output0[i0] = FAUSTFLOAT(0.3f * fRec124[0] * (fRec121[0] * fTemp164 * fTemp163 * fTemp153 + fRec110[0] * fTemp149 * fTemp148 * fTemp138 + fRec100[0] * fTemp134 * fTemp133 * fTemp123 + fRec90[0] * fTemp119 * fTemp118 * fTemp107) + 0.5f * (fRec78[0] * fTemp103 + fRec62[0] * fTemp79 + fRec32[0] * fTemp42) + fTemp20);
			fRec132[0] = 5e-05f * fTemp120 * std::sqrt(std::max<float>(0.0f, 1.0f - 2.0f * fRec92[0] * std::fabs(std::fmod(fRec91[0] + 1.0f, 1.0f) + -0.5f))) + 0.9999f * fRec132[1];
			fRec133[0] = 5e-05f * fTemp135 * std::sqrt(std::max<float>(0.0f, 1.0f - 2.0f * fRec102[0] * std::fabs(std::fmod(fRec101[0] + 1.0f, 1.0f) + -0.5f))) + 0.9999f * fRec133[1];
			fRec134[0] = 5e-05f * fTemp150 * std::sqrt(std::max<float>(0.0f, 1.0f - 2.0f * fRec112[0] * std::fabs(std::fmod(fRec111[0] + 1.0f, 1.0f) + -0.5f))) + 0.9999f * fRec134[1];
			fRec135[0] = 5e-05f * fTemp165 * std::sqrt(std::max<float>(0.0f, 1.0f - 2.0f * fRec123[0] * std::fabs(std::fmod(fRec122[0] + 1.0f, 1.0f) + -0.5f))) + 0.9999f * fRec135[1];
			fRec136[0] = 5e-05f * fTemp56 * std::sqrt(std::max<float>(0.0f, 1.0f - 2.0f * fRec48[0] * std::fabs(std::fmod(fRec33[0] + 1.0f, 1.0f) + -0.5f))) + 0.9999f * fRec136[1];
			fRec137[0] = 5e-05f * fTemp80 * std::sqrt(std::max<float>(0.0f, 1.0f - 2.0f * fRec64[0] * std::fabs(std::fmod(fRec63[0] + 1.0f, 1.0f) + -0.5f))) + 0.9999f * fRec137[1];
			fRec138[0] = 5e-05f * fTemp104 * std::sqrt(std::max<float>(0.0f, 1.0f - 2.0f * fRec80[0] * std::fabs(std::fmod(fRec79[0] + 1.0f, 1.0f) + -0.5f))) + 0.9999f * fRec138[1];
			output1[i0] = FAUSTFLOAT(0.5f * (fRec138[0] * fTemp103 + fRec137[0] * fTemp79 + fRec136[0] * fTemp42) + fTemp20 + 0.3f * fRec124[0] * (fRec135[0] * fTemp164 * fTemp163 * fTemp153 + fRec134[0] * fTemp149 * fTemp148 * fTemp138 + fRec133[0] * fTemp134 * fTemp133 * fTemp123 + fRec132[0] * fTemp119 * fTemp118 * fTemp107));
			iVec0[1] = iVec0[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			fRec6[1] = fRec6[0];
			fRec7[1] = fRec7[0];
			fRec8[1] = fRec8[0];
			fRec9[1] = fRec9[0];
			fRec5[2] = fRec5[1];
			fRec5[1] = fRec5[0];
			fRec11[1] = fRec11[0];
			iRec13[1] = iRec13[0];
			fVec2[1] = fVec2[0];
			fRec12[2] = fRec12[1];
			fRec12[1] = fRec12[0];
			fRec18[1] = fRec18[0];
			fVec3[1] = fVec3[0];
			fRec17[1] = fRec17[0];
			fRec16[1] = fRec16[0];
			fRec15[1] = fRec15[0];
			fRec14[2] = fRec14[1];
			fRec14[1] = fRec14[0];
			iRec22[1] = iRec22[0];
			fRec25[1] = fRec25[0];
			fVec4[1] = fVec4[0];
			fRec24[1] = fRec24[0];
			fRec23[1] = fRec23[0];
			iVec5[1] = iVec5[0];
			iRec21[1] = iRec21[0];
			iRec26[1] = iRec26[0];
			fRec27[2] = fRec27[1];
			fRec27[1] = fRec27[0];
			fRec20[2] = fRec20[1];
			fRec20[1] = fRec20[0];
			fRec29[2] = fRec29[1];
			fRec29[1] = fRec29[0];
			fRec28[2] = fRec28[1];
			fRec28[1] = fRec28[0];
			fRec31[2] = fRec31[1];
			fRec31[1] = fRec31[0];
			fRec30[2] = fRec30[1];
			fRec30[1] = fRec30[0];
			fRec19[2] = fRec19[1];
			fRec19[1] = fRec19[0];
			iRec34[1] = iRec34[0];
			fRec33[1] = fRec33[0];
			fRec48[1] = fRec48[0];
			fRec32[1] = fRec32[0];
			iRec52[1] = iRec52[0];
			fRec55[1] = fRec55[0];
			fVec6[1] = fVec6[0];
			fRec54[1] = fRec54[0];
			fRec53[1] = fRec53[0];
			iVec7[1] = iVec7[0];
			iRec51[1] = iRec51[0];
			iRec56[1] = iRec56[0];
			fRec57[2] = fRec57[1];
			fRec57[1] = fRec57[0];
			fRec50[2] = fRec50[1];
			fRec50[1] = fRec50[0];
			fRec59[2] = fRec59[1];
			fRec59[1] = fRec59[0];
			fRec58[2] = fRec58[1];
			fRec58[1] = fRec58[0];
			fRec61[2] = fRec61[1];
			fRec61[1] = fRec61[0];
			fRec60[2] = fRec60[1];
			fRec60[1] = fRec60[0];
			fRec49[2] = fRec49[1];
			fRec49[1] = fRec49[0];
			fRec63[1] = fRec63[0];
			fRec64[1] = fRec64[0];
			fRec62[1] = fRec62[0];
			iRec68[1] = iRec68[0];
			fRec71[1] = fRec71[0];
			fVec8[1] = fVec8[0];
			fRec70[1] = fRec70[0];
			fRec69[1] = fRec69[0];
			iVec9[1] = iVec9[0];
			iRec67[1] = iRec67[0];
			iRec72[1] = iRec72[0];
			fRec73[2] = fRec73[1];
			fRec73[1] = fRec73[0];
			fRec66[2] = fRec66[1];
			fRec66[1] = fRec66[0];
			fRec75[2] = fRec75[1];
			fRec75[1] = fRec75[0];
			fRec74[2] = fRec74[1];
			fRec74[1] = fRec74[0];
			fRec77[2] = fRec77[1];
			fRec77[1] = fRec77[0];
			fRec76[2] = fRec76[1];
			fRec76[1] = fRec76[0];
			fRec65[2] = fRec65[1];
			fRec65[1] = fRec65[0];
			fRec79[1] = fRec79[0];
			fRec80[1] = fRec80[0];
			fRec78[1] = fRec78[0];
			fRec81[1] = fRec81[0];
			fRec82[1] = fRec82[0];
			iRec84[1] = iRec84[0];
			fRec87[1] = fRec87[0];
			fVec10[1] = fVec10[0];
			fRec86[1] = fRec86[0];
			fRec85[1] = fRec85[0];
			fRec88[1] = fRec88[0];
			fRec83[1] = fRec83[0];
			fRec89[1] = fRec89[0];
			fRec91[1] = fRec91[0];
			fRec92[1] = fRec92[0];
			fRec90[1] = fRec90[0];
			fRec93[1] = fRec93[0];
			fRec94[1] = fRec94[0];
			fRec98[1] = fRec98[0];
			fVec11[1] = fVec11[0];
			fRec97[1] = fRec97[0];
			fRec96[1] = fRec96[0];
			fRec95[1] = fRec95[0];
			fRec99[1] = fRec99[0];
			fRec101[1] = fRec101[0];
			fRec102[1] = fRec102[0];
			fRec100[1] = fRec100[0];
			fRec103[1] = fRec103[0];
			fRec104[1] = fRec104[0];
			fRec108[1] = fRec108[0];
			fVec12[1] = fVec12[0];
			fRec107[1] = fRec107[0];
			fRec106[1] = fRec106[0];
			fRec105[1] = fRec105[0];
			fRec109[1] = fRec109[0];
			fRec111[1] = fRec111[0];
			fRec112[1] = fRec112[0];
			fRec110[1] = fRec110[0];
			fRec113[1] = fRec113[0];
			fRec114[1] = fRec114[0];
			iRec116[1] = iRec116[0];
			fRec119[1] = fRec119[0];
			fVec13[1] = fVec13[0];
			fRec118[1] = fRec118[0];
			fRec117[1] = fRec117[0];
			fRec115[1] = fRec115[0];
			fRec120[1] = fRec120[0];
			fRec122[1] = fRec122[0];
			fRec123[1] = fRec123[0];
			fRec121[1] = fRec121[0];
			fRec130[1] = fRec130[0];
			fRec131[1] = fRec131[0];
			fRec129[1] = fRec129[0];
			fRec128[1] = fRec128[0];
			fRec127[1] = fRec127[0];
			fRec126[1] = fRec126[0];
			fRec125[1] = fRec125[0];
			fRec124[1] = fRec124[0];
			fRec132[1] = fRec132[0];
			fRec133[1] = fRec133[0];
			fRec134[1] = fRec134[0];
			fRec135[1] = fRec135[0];
			fRec136[1] = fRec136[0];
			fRec137[1] = fRec137[0];
			fRec138[1] = fRec138[0];
		}
	}

};

#endif
