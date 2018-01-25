/* ------------------------------------------------------------
copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
license: "MIT"
name: "DjembeMIDI"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: cpp, -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__


// algorithm is required for min and max
#include <algorithm>
#include "gui/UI.h"

using namespace std;

// the struct below are not defined in UI.h
struct dsp {
};

struct Meta {
	void declare(const char*, const char*) {}
};
#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <cmath>
#include <math.h>

float mydsp_faustpower2_f(float value) {
	return (value * value);
	
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif
#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class mydsp : public dsp {
	
 private:
	
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider2;
	int iRec3[2];
	float fRec2[3];
	float fRec1[3];
	FAUSTFLOAT fButton0;
	float fVec0[2];
	float fConst2;
	FAUSTFLOAT fHslider3;
	float fVec1[2];
	float fRec4[2];
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	float fConst7;
	FAUSTFLOAT fHslider4;
	float fConst8;
	float fRec0[3];
	float fConst9;
	float fConst10;
	float fConst11;
	float fRec5[3];
	float fConst12;
	float fConst13;
	float fConst14;
	float fRec6[3];
	float fConst15;
	float fConst16;
	float fConst17;
	float fRec7[3];
	float fConst18;
	float fConst19;
	float fConst20;
	float fRec8[3];
	float fConst21;
	float fConst22;
	float fConst23;
	float fRec9[3];
	float fConst24;
	float fConst25;
	float fConst26;
	float fRec10[3];
	float fConst27;
	float fConst28;
	float fConst29;
	float fRec11[3];
	float fConst30;
	float fConst31;
	float fConst32;
	float fRec12[3];
	float fConst33;
	float fConst34;
	float fConst35;
	float fRec13[3];
	float fConst36;
	float fConst37;
	float fConst38;
	float fRec14[3];
	float fConst39;
	float fConst40;
	float fConst41;
	float fRec15[3];
	float fConst42;
	float fConst43;
	float fConst44;
	float fRec16[3];
	float fConst45;
	float fConst46;
	float fConst47;
	float fRec17[3];
	float fConst48;
	float fConst49;
	float fConst50;
	float fRec18[3];
	float fConst51;
	float fConst52;
	float fConst53;
	float fRec19[3];
	float fConst54;
	float fConst55;
	float fConst56;
	float fRec20[3];
	float fConst57;
	float fConst58;
	float fConst59;
	float fRec21[3];
	float fConst60;
	float fConst61;
	float fConst62;
	float fRec22[3];
	float fConst63;
	float fConst64;
	float fConst65;
	float fRec23[3];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
		m->declare("description", "Simple MIDI-controllable djembe physical model.");
		m->declare("envelopes.lib/author", "GRAME");
		m->declare("envelopes.lib/copyright", "GRAME");
		m->declare("envelopes.lib/license", "LGPL with exception");
		m->declare("envelopes.lib/name", "Faust Envelope Library");
		m->declare("envelopes.lib/version", "0.0");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("license", "MIT");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "DjembeMIDI");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
	}

	virtual int getNumInputs() {
		return 0;
		
	}
	virtual int getNumOutputs() {
		return 2;
		
	}
	virtual int getInputRate(int channel) {
		int rate;
		switch (channel) {
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	virtual int getOutputRate(int channel) {
		int rate;
		switch (channel) {
			case 0: {
				rate = 1;
				break;
			}
			case 1: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	
	static void classInit(int samplingFreq) {
		
	}
	
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(192000.0f, max(1.0f, float(fSamplingFreq)));
		fConst1 = (3.14159274f / fConst0);
		fConst2 = (0.00400000019f * fConst0);
		fConst3 = (0.00200000009f * fConst0);
		fConst4 = (500.0f / fConst0);
		fConst5 = powf(0.00100000005f, (1.0f / (0.600000024f * fConst0)));
		fConst6 = (0.0f - (2.0f * fConst5));
		fConst7 = (6.28318548f / fConst0);
		fConst8 = mydsp_faustpower2_f(fConst5);
		fConst9 = powf(0.00100000005f, (1.0f / (0.569999993f * fConst0)));
		fConst10 = (0.0f - (2.0f * fConst9));
		fConst11 = mydsp_faustpower2_f(fConst9);
		fConst12 = powf(0.00100000005f, (1.0f / (0.540000021f * fConst0)));
		fConst13 = (0.0f - (2.0f * fConst12));
		fConst14 = mydsp_faustpower2_f(fConst12);
		fConst15 = powf(0.00100000005f, (1.0f / (0.50999999f * fConst0)));
		fConst16 = (0.0f - (2.0f * fConst15));
		fConst17 = mydsp_faustpower2_f(fConst15);
		fConst18 = powf(0.00100000005f, (1.0f / (0.479999989f * fConst0)));
		fConst19 = (0.0f - (2.0f * fConst18));
		fConst20 = mydsp_faustpower2_f(fConst18);
		fConst21 = powf(0.00100000005f, (1.0f / (0.449999988f * fConst0)));
		fConst22 = (0.0f - (2.0f * fConst21));
		fConst23 = mydsp_faustpower2_f(fConst21);
		fConst24 = powf(0.00100000005f, (1.0f / (0.419999987f * fConst0)));
		fConst25 = (0.0f - (2.0f * fConst24));
		fConst26 = mydsp_faustpower2_f(fConst24);
		fConst27 = powf(0.00100000005f, (1.0f / (0.389999986f * fConst0)));
		fConst28 = (0.0f - (2.0f * fConst27));
		fConst29 = mydsp_faustpower2_f(fConst27);
		fConst30 = powf(0.00100000005f, (1.0f / (0.360000014f * fConst0)));
		fConst31 = (0.0f - (2.0f * fConst30));
		fConst32 = mydsp_faustpower2_f(fConst30);
		fConst33 = powf(0.00100000005f, (1.0f / (0.330000013f * fConst0)));
		fConst34 = (0.0f - (2.0f * fConst33));
		fConst35 = mydsp_faustpower2_f(fConst33);
		fConst36 = powf(0.00100000005f, (1.0f / (0.300000012f * fConst0)));
		fConst37 = (0.0f - (2.0f * fConst36));
		fConst38 = mydsp_faustpower2_f(fConst36);
		fConst39 = powf(0.00100000005f, (1.0f / (0.270000011f * fConst0)));
		fConst40 = (0.0f - (2.0f * fConst39));
		fConst41 = mydsp_faustpower2_f(fConst39);
		fConst42 = powf(0.00100000005f, (1.0f / (0.239999995f * fConst0)));
		fConst43 = (0.0f - (2.0f * fConst42));
		fConst44 = mydsp_faustpower2_f(fConst42);
		fConst45 = powf(0.00100000005f, (1.0f / (0.209999993f * fConst0)));
		fConst46 = (0.0f - (2.0f * fConst45));
		fConst47 = mydsp_faustpower2_f(fConst45);
		fConst48 = powf(0.00100000005f, (1.0f / (0.180000007f * fConst0)));
		fConst49 = (0.0f - (2.0f * fConst48));
		fConst50 = mydsp_faustpower2_f(fConst48);
		fConst51 = powf(0.00100000005f, (1.0f / (0.150000006f * fConst0)));
		fConst52 = (0.0f - (2.0f * fConst51));
		fConst53 = mydsp_faustpower2_f(fConst51);
		fConst54 = powf(0.00100000005f, (1.0f / (0.119999997f * fConst0)));
		fConst55 = (0.0f - (2.0f * fConst54));
		fConst56 = mydsp_faustpower2_f(fConst54);
		fConst57 = powf(0.00100000005f, (1.0f / (0.0900000036f * fConst0)));
		fConst58 = (0.0f - (2.0f * fConst57));
		fConst59 = mydsp_faustpower2_f(fConst57);
		fConst60 = powf(0.00100000005f, (1.0f / (0.0599999987f * fConst0)));
		fConst61 = (0.0f - (2.0f * fConst60));
		fConst62 = mydsp_faustpower2_f(fConst60);
		fConst63 = powf(0.00100000005f, (1.0f / (0.0299999993f * fConst0)));
		fConst64 = (0.0f - (2.0f * fConst63));
		fConst65 = mydsp_faustpower2_f(fConst63);
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(1.0f);
		fHslider1 = FAUSTFLOAT(1.0f);
		fHslider2 = FAUSTFLOAT(0.5f);
		fButton0 = FAUSTFLOAT(0.0f);
		fHslider3 = FAUSTFLOAT(0.5f);
		fHslider4 = FAUSTFLOAT(60.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iRec3[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 3); l1 = (l1 + 1)) {
			fRec2[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) {
			fRec1[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fVec0[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fVec1[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec4[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) {
			fRec0[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			fRec5[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
			fRec6[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) {
			fRec7[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 3); l10 = (l10 + 1)) {
			fRec8[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 3); l11 = (l11 + 1)) {
			fRec9[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 3); l12 = (l12 + 1)) {
			fRec10[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 3); l13 = (l13 + 1)) {
			fRec11[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 3); l14 = (l14 + 1)) {
			fRec12[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 3); l15 = (l15 + 1)) {
			fRec13[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 3); l16 = (l16 + 1)) {
			fRec14[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 3); l17 = (l17 + 1)) {
			fRec15[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 3); l18 = (l18 + 1)) {
			fRec16[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 3); l19 = (l19 + 1)) {
			fRec17[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 3); l20 = (l20 + 1)) {
			fRec18[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 3); l21 = (l21 + 1)) {
			fRec19[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 3); l22 = (l22 + 1)) {
			fRec20[l22] = 0.0f;
			
		}
		for (int l23 = 0; (l23 < 3); l23 = (l23 + 1)) {
			fRec21[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 3); l24 = (l24 + 1)) {
			fRec22[l24] = 0.0f;
			
		}
		for (int l25 = 0; (l25 < 3); l25 = (l25 + 1)) {
			fRec23[l25] = 0.0f;
			
		}
		
	}
	
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void instanceInit(int samplingFreq) {
		instanceConstants(samplingFreq);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual mydsp* clone() {
		return new mydsp();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;
		
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("djembe");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("midi");
		ui_interface->declare(&fHslider4, "0", "");
		ui_interface->declare(&fHslider4, "style", "knob");
		ui_interface->addHorizontalSlider("freq", &fHslider4, 60.0f, 50.0f, 100.0f, 0.00999999978f);
		ui_interface->declare(&fHslider1, "2", "");
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->addHorizontalSlider("gain", &fHslider1, 1.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("otherParams");
		ui_interface->declare(&fHslider2, "0", "");
		ui_interface->declare(&fHslider2, "midi", "ctrl 1");
		ui_interface->declare(&fHslider2, "style", "knob");
		ui_interface->addHorizontalSlider("strikePosition", &fHslider2, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fHslider3, "1", "");
		ui_interface->declare(&fHslider3, "style", "knob");
		ui_interface->addHorizontalSlider("strikeSharpness", &fHslider3, 0.5f, 0.00999999978f, 5.0f, 0.00999999978f);
		ui_interface->declare(&fHslider0, "2", "");
		ui_interface->declare(&fHslider0, "style", "knob");
		ui_interface->addHorizontalSlider("outGain", &fHslider0, 1.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
		ui_interface->declare(&fButton0, "3", "");
		ui_interface->addButton("gate", &fButton0);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = (0.0500000007f * float(fHslider0));
		float fSlow1 = float(fHslider2);
		float fSlow2 = tanf((fConst1 * ((15000.0f * fSlow1) + 500.0f)));
		float fSlow3 = (1.0f / fSlow2);
		float fSlow4 = (((fSlow3 + 1.41421354f) / fSlow2) + 1.0f);
		float fSlow5 = (float(fHslider1) / fSlow4);
		float fSlow6 = tanf((fConst1 * ((500.0f * fSlow1) + 40.0f)));
		float fSlow7 = (1.0f / fSlow6);
		float fSlow8 = (1.0f / (((fSlow7 + 1.41421354f) / fSlow6) + 1.0f));
		float fSlow9 = (1.0f / mydsp_faustpower2_f(fSlow6));
		float fSlow10 = (((fSlow7 + -1.41421354f) / fSlow6) + 1.0f);
		float fSlow11 = (2.0f * (1.0f - fSlow9));
		float fSlow12 = (2.0f * (0.0f - fSlow9));
		float fSlow13 = (1.0f / fSlow4);
		float fSlow14 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fSlow2))));
		float fSlow15 = (((fSlow3 + -1.41421354f) / fSlow2) + 1.0f);
		float fSlow16 = float(fButton0);
		float fSlow17 = float(fHslider3);
		float fSlow18 = (fConst2 * fSlow17);
		float fSlow19 = (fConst3 * fSlow17);
		float fSlow20 = (fConst4 / fSlow17);
		float fSlow21 = float(fHslider4);
		float fSlow22 = (fConst6 * cosf((fConst7 * fSlow21)));
		float fSlow23 = (fConst10 * cosf((fConst7 * (fSlow21 + 200.0f))));
		float fSlow24 = (fConst13 * cosf((fConst7 * (fSlow21 + 400.0f))));
		float fSlow25 = (fConst16 * cosf((fConst7 * (fSlow21 + 600.0f))));
		float fSlow26 = (fConst19 * cosf((fConst7 * (fSlow21 + 800.0f))));
		float fSlow27 = (fConst22 * cosf((fConst7 * (fSlow21 + 1000.0f))));
		float fSlow28 = (fConst25 * cosf((fConst7 * (fSlow21 + 1200.0f))));
		float fSlow29 = (fConst28 * cosf((fConst7 * (fSlow21 + 1400.0f))));
		float fSlow30 = (fConst31 * cosf((fConst7 * (fSlow21 + 1600.0f))));
		float fSlow31 = (fConst34 * cosf((fConst7 * (fSlow21 + 1800.0f))));
		float fSlow32 = (fConst37 * cosf((fConst7 * (fSlow21 + 2000.0f))));
		float fSlow33 = (fConst40 * cosf((fConst7 * (fSlow21 + 2200.0f))));
		float fSlow34 = (fConst43 * cosf((fConst7 * (fSlow21 + 2400.0f))));
		float fSlow35 = (fConst46 * cosf((fConst7 * (fSlow21 + 2600.0f))));
		float fSlow36 = (fConst49 * cosf((fConst7 * (fSlow21 + 2800.0f))));
		float fSlow37 = (fConst52 * cosf((fConst7 * (fSlow21 + 3000.0f))));
		float fSlow38 = (fConst55 * cosf((fConst7 * (fSlow21 + 3200.0f))));
		float fSlow39 = (fConst58 * cosf((fConst7 * (fSlow21 + 3400.0f))));
		float fSlow40 = (fConst61 * cosf((fConst7 * (fSlow21 + 3600.0f))));
		float fSlow41 = (fConst64 * cosf((fConst7 * (fSlow21 + 3800.0f))));
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec3[0] = ((1103515245 * iRec3[1]) + 12345);
			fRec2[0] = ((4.65661287e-10f * float(iRec3[0])) - (fSlow8 * ((fSlow10 * fRec2[2]) + (fSlow11 * fRec2[1]))));
			fRec1[0] = ((fSlow8 * (((fSlow9 * fRec2[0]) + (fSlow12 * fRec2[1])) + (fSlow9 * fRec2[2]))) - (fSlow13 * ((fSlow14 * fRec1[1]) + (fSlow15 * fRec1[2]))));
			fVec0[0] = fSlow16;
			fVec1[0] = fSlow17;
			fRec4[0] = ((((fSlow16 - fVec0[1]) > 0.0f) > 0)?0.0f:min(fSlow18, ((fRec4[1] + (fConst2 * (fSlow17 - fVec1[1]))) + 1.0f)));
			int iTemp0 = (fRec4[0] < fSlow19);
			float fTemp1 = (fSlow5 * ((fRec1[2] + (fRec1[0] + (2.0f * fRec1[1]))) * (iTemp0?((fRec4[0] < 0.0f)?0.0f:(iTemp0?(fSlow20 * fRec4[0]):1.0f)):((fRec4[0] < fSlow18)?((fSlow20 * (0.0f - (fRec4[0] - fSlow19))) + 1.0f):0.0f))));
			fRec0[0] = (fTemp1 - ((fSlow22 * fRec0[1]) + (fConst8 * fRec0[2])));
			fRec5[0] = (fTemp1 - ((fSlow23 * fRec5[1]) + (fConst11 * fRec5[2])));
			fRec6[0] = (fTemp1 - ((fSlow24 * fRec6[1]) + (fConst14 * fRec6[2])));
			fRec7[0] = (fTemp1 - ((fSlow25 * fRec7[1]) + (fConst17 * fRec7[2])));
			fRec8[0] = (fTemp1 - ((fSlow26 * fRec8[1]) + (fConst20 * fRec8[2])));
			fRec9[0] = (fTemp1 - ((fSlow27 * fRec9[1]) + (fConst23 * fRec9[2])));
			fRec10[0] = (fTemp1 - ((fSlow28 * fRec10[1]) + (fConst26 * fRec10[2])));
			fRec11[0] = (fTemp1 - ((fSlow29 * fRec11[1]) + (fConst29 * fRec11[2])));
			fRec12[0] = (fTemp1 - ((fSlow30 * fRec12[1]) + (fConst32 * fRec12[2])));
			fRec13[0] = (fTemp1 - ((fSlow31 * fRec13[1]) + (fConst35 * fRec13[2])));
			fRec14[0] = (fTemp1 - ((fSlow32 * fRec14[1]) + (fConst38 * fRec14[2])));
			fRec15[0] = (fTemp1 - ((fSlow33 * fRec15[1]) + (fConst41 * fRec15[2])));
			fRec16[0] = (fTemp1 - ((fSlow34 * fRec16[1]) + (fConst44 * fRec16[2])));
			fRec17[0] = (fTemp1 - ((fSlow35 * fRec17[1]) + (fConst47 * fRec17[2])));
			fRec18[0] = (fTemp1 - ((fSlow36 * fRec18[1]) + (fConst50 * fRec18[2])));
			fRec19[0] = (fTemp1 - ((fSlow37 * fRec19[1]) + (fConst53 * fRec19[2])));
			fRec20[0] = (fTemp1 - ((fSlow38 * fRec20[1]) + (fConst56 * fRec20[2])));
			fRec21[0] = (fTemp1 - ((fSlow39 * fRec21[1]) + (fConst59 * fRec21[2])));
			fRec22[0] = (fTemp1 - ((fSlow40 * fRec22[1]) + (fConst62 * fRec22[2])));
			fRec23[0] = (fTemp1 - ((fSlow41 * fRec23[1]) + (fConst65 * fRec23[2])));
			float fTemp2 = (fSlow0 * ((((((((((((((((((((fRec0[0] + (0.25f * (fRec5[0] - fRec5[2]))) + (0.111111112f * (fRec6[0] - fRec6[2]))) + (0.0625f * (fRec7[0] - fRec7[2]))) + (0.0399999991f * (fRec8[0] - fRec8[2]))) + (0.027777778f * (fRec9[0] - fRec9[2]))) + (0.0204081628f * (fRec10[0] - fRec10[2]))) + (0.015625f * (fRec11[0] - fRec11[2]))) + (0.0123456791f * (fRec12[0] - fRec12[2]))) + (0.00999999978f * (fRec13[0] - fRec13[2]))) + (0.00826446246f * (fRec14[0] - fRec14[2]))) + (0.0069444445f * (fRec15[0] - fRec15[2]))) + (0.00591715984f * (fRec16[0] - fRec16[2]))) + (0.00510204071f * (fRec17[0] - fRec17[2]))) + (0.00444444455f * (fRec18[0] - fRec18[2]))) + (0.00390625f * (fRec19[0] - fRec19[2]))) + (0.00346020772f * (fRec20[0] - fRec20[2]))) + (0.00308641978f * (fRec21[0] - fRec21[2]))) + (0.00277008303f * (fRec22[0] - fRec22[2]))) + (0.00249999994f * (fRec23[0] - fRec23[2]))) - fRec0[2]));
			output0[i] = FAUSTFLOAT(fTemp2);
			output1[i] = FAUSTFLOAT(fTemp2);
			iRec3[1] = iRec3[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fVec0[1] = fVec0[0];
			fVec1[1] = fVec1[0];
			fRec4[1] = fRec4[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			fRec5[2] = fRec5[1];
			fRec5[1] = fRec5[0];
			fRec6[2] = fRec6[1];
			fRec6[1] = fRec6[0];
			fRec7[2] = fRec7[1];
			fRec7[1] = fRec7[0];
			fRec8[2] = fRec8[1];
			fRec8[1] = fRec8[0];
			fRec9[2] = fRec9[1];
			fRec9[1] = fRec9[0];
			fRec10[2] = fRec10[1];
			fRec10[1] = fRec10[0];
			fRec11[2] = fRec11[1];
			fRec11[1] = fRec11[0];
			fRec12[2] = fRec12[1];
			fRec12[1] = fRec12[0];
			fRec13[2] = fRec13[1];
			fRec13[1] = fRec13[0];
			fRec14[2] = fRec14[1];
			fRec14[1] = fRec14[0];
			fRec15[2] = fRec15[1];
			fRec15[1] = fRec15[0];
			fRec16[2] = fRec16[1];
			fRec16[1] = fRec16[0];
			fRec17[2] = fRec17[1];
			fRec17[1] = fRec17[0];
			fRec18[2] = fRec18[1];
			fRec18[1] = fRec18[0];
			fRec19[2] = fRec19[1];
			fRec19[1] = fRec19[0];
			fRec20[2] = fRec20[1];
			fRec20[1] = fRec20[0];
			fRec21[2] = fRec21[1];
			fRec21[1] = fRec21[0];
			fRec22[2] = fRec22[1];
			fRec22[1] = fRec22[0];
			fRec23[2] = fRec23[1];
			fRec23[1] = fRec23[0];
			
		}
		
	}

	
};

#endif
