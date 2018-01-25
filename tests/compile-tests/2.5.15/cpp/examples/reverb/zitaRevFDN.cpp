/* ------------------------------------------------------------
author: "JOS, Revised by RM"
name: "zitaRevFDN"
version: "0.0"
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
	
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fVslider0;
	float fConst3;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fVslider2;
	float fConst4;
	FAUSTFLOAT fVslider3;
	float fRec11[2];
	float fRec10[2];
	int IOTA;
	float fVec0[32768];
	float fConst5;
	int iConst6;
	float fVec1[2048];
	int iConst7;
	float fRec8[2];
	float fConst8;
	float fConst9;
	float fRec15[2];
	float fRec14[2];
	float fVec2[32768];
	float fConst10;
	int iConst11;
	float fVec3[4096];
	int iConst12;
	float fRec12[2];
	float fConst13;
	float fConst14;
	float fRec19[2];
	float fRec18[2];
	float fVec4[16384];
	float fConst15;
	int iConst16;
	float fVec5[4096];
	int iConst17;
	float fRec16[2];
	float fConst18;
	float fConst19;
	float fRec23[2];
	float fRec22[2];
	float fVec6[32768];
	float fConst20;
	int iConst21;
	float fVec7[4096];
	int iConst22;
	float fRec20[2];
	float fConst23;
	float fConst24;
	float fRec27[2];
	float fRec26[2];
	float fVec8[16384];
	float fConst25;
	int iConst26;
	float fVec9[2048];
	int iConst27;
	float fRec24[2];
	float fConst28;
	float fConst29;
	float fRec31[2];
	float fRec30[2];
	float fVec10[16384];
	float fConst30;
	int iConst31;
	float fVec11[4096];
	int iConst32;
	float fRec28[2];
	float fConst33;
	float fConst34;
	float fRec35[2];
	float fRec34[2];
	float fVec12[16384];
	float fConst35;
	int iConst36;
	float fVec13[4096];
	int iConst37;
	float fRec32[2];
	float fConst38;
	float fConst39;
	float fRec39[2];
	float fRec38[2];
	float fVec14[16384];
	float fConst40;
	int iConst41;
	float fVec15[2048];
	int iConst42;
	float fRec36[2];
	float fRec0[3];
	float fRec1[3];
	float fRec2[3];
	float fRec3[3];
	float fRec4[3];
	float fRec5[3];
	float fRec6[3];
	float fRec7[3];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("author", "JOS, Revised by RM");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("description", "Reverb demo application based on `zita_rev_fdn`.");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "zitaRevFDN");
		m->declare("reverbs.lib/name", "Faust Reverb Library");
		m->declare("reverbs.lib/version", "0.0");
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("version", "0.0");
	}

	virtual int getNumInputs() {
		return 8;
		
	}
	virtual int getNumOutputs() {
		return 8;
		
	}
	virtual int getInputRate(int channel) {
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
			case 2: {
				rate = 1;
				break;
			}
			case 3: {
				rate = 1;
				break;
			}
			case 4: {
				rate = 1;
				break;
			}
			case 5: {
				rate = 1;
				break;
			}
			case 6: {
				rate = 1;
				break;
			}
			case 7: {
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
			case 2: {
				rate = 1;
				break;
			}
			case 3: {
				rate = 1;
				break;
			}
			case 4: {
				rate = 1;
				break;
			}
			case 5: {
				rate = 1;
				break;
			}
			case 6: {
				rate = 1;
				break;
			}
			case 7: {
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
		fConst1 = floorf(((0.219990999f * fConst0) + 0.5f));
		fConst2 = ((0.0f - (6.90775537f * fConst1)) / fConst0);
		fConst3 = (6.28318548f / fConst0);
		fConst4 = (3.14159274f / fConst0);
		fConst5 = floorf(((0.0191229992f * fConst0) + 0.5f));
		iConst6 = int(min(16384.0f, max(0.0f, (fConst1 - fConst5))));
		iConst7 = int(min(1024.0f, max(0.0f, (fConst5 + -1.0f))));
		fConst8 = floorf(((0.256891012f * fConst0) + 0.5f));
		fConst9 = ((0.0f - (6.90775537f * fConst8)) / fConst0);
		fConst10 = floorf(((0.0273330007f * fConst0) + 0.5f));
		iConst11 = int(min(16384.0f, max(0.0f, (fConst8 - fConst10))));
		iConst12 = int(min(2048.0f, max(0.0f, (fConst10 + -1.0f))));
		fConst13 = floorf(((0.192303002f * fConst0) + 0.5f));
		fConst14 = ((0.0f - (6.90775537f * fConst13)) / fConst0);
		fConst15 = floorf(((0.0292910002f * fConst0) + 0.5f));
		iConst16 = int(min(8192.0f, max(0.0f, (fConst13 - fConst15))));
		iConst17 = int(min(2048.0f, max(0.0f, (fConst15 + -1.0f))));
		fConst18 = floorf(((0.210389003f * fConst0) + 0.5f));
		fConst19 = ((0.0f - (6.90775537f * fConst18)) / fConst0);
		fConst20 = floorf(((0.0244210009f * fConst0) + 0.5f));
		iConst21 = int(min(16384.0f, max(0.0f, (fConst18 - fConst20))));
		iConst22 = int(min(2048.0f, max(0.0f, (fConst20 + -1.0f))));
		fConst23 = floorf(((0.125f * fConst0) + 0.5f));
		fConst24 = ((0.0f - (6.90775537f * fConst23)) / fConst0);
		fConst25 = floorf(((0.0134579996f * fConst0) + 0.5f));
		iConst26 = int(min(8192.0f, max(0.0f, (fConst23 - fConst25))));
		iConst27 = int(min(1024.0f, max(0.0f, (fConst25 + -1.0f))));
		fConst28 = floorf(((0.127837002f * fConst0) + 0.5f));
		fConst29 = ((0.0f - (6.90775537f * fConst28)) / fConst0);
		fConst30 = floorf(((0.0316039994f * fConst0) + 0.5f));
		iConst31 = int(min(8192.0f, max(0.0f, (fConst28 - fConst30))));
		iConst32 = int(min(2048.0f, max(0.0f, (fConst30 + -1.0f))));
		fConst33 = floorf(((0.174713001f * fConst0) + 0.5f));
		fConst34 = ((0.0f - (6.90775537f * fConst33)) / fConst0);
		fConst35 = floorf(((0.0229039993f * fConst0) + 0.5f));
		iConst36 = int(min(8192.0f, max(0.0f, (fConst33 - fConst35))));
		iConst37 = int(min(2048.0f, max(0.0f, (fConst35 + -1.0f))));
		fConst38 = floorf(((0.153128996f * fConst0) + 0.5f));
		fConst39 = ((0.0f - (6.90775537f * fConst38)) / fConst0);
		fConst40 = floorf(((0.0203460008f * fConst0) + 0.5f));
		iConst41 = int(min(8192.0f, max(0.0f, (fConst38 - fConst40))));
		iConst42 = int(min(1024.0f, max(0.0f, (fConst40 + -1.0f))));
		
	}
	
	virtual void instanceResetUserInterface() {
		fVslider0 = FAUSTFLOAT(2.0f);
		fVslider1 = FAUSTFLOAT(6000.0f);
		fVslider2 = FAUSTFLOAT(3.0f);
		fVslider3 = FAUSTFLOAT(200.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec11[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec10[l1] = 0.0f;
			
		}
		IOTA = 0;
		for (int l2 = 0; (l2 < 32768); l2 = (l2 + 1)) {
			fVec0[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2048); l3 = (l3 + 1)) {
			fVec1[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec8[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec15[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec14[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 32768); l7 = (l7 + 1)) {
			fVec2[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 4096); l8 = (l8 + 1)) {
			fVec3[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec12[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec19[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec18[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 16384); l12 = (l12 + 1)) {
			fVec4[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 4096); l13 = (l13 + 1)) {
			fVec5[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec16[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec23[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec22[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 32768); l17 = (l17 + 1)) {
			fVec6[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 4096); l18 = (l18 + 1)) {
			fVec7[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec20[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec27[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec26[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 16384); l22 = (l22 + 1)) {
			fVec8[l22] = 0.0f;
			
		}
		for (int l23 = 0; (l23 < 2048); l23 = (l23 + 1)) {
			fVec9[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fRec24[l24] = 0.0f;
			
		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fRec31[l25] = 0.0f;
			
		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fRec30[l26] = 0.0f;
			
		}
		for (int l27 = 0; (l27 < 16384); l27 = (l27 + 1)) {
			fVec10[l27] = 0.0f;
			
		}
		for (int l28 = 0; (l28 < 4096); l28 = (l28 + 1)) {
			fVec11[l28] = 0.0f;
			
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec28[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fRec35[l30] = 0.0f;
			
		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			fRec34[l31] = 0.0f;
			
		}
		for (int l32 = 0; (l32 < 16384); l32 = (l32 + 1)) {
			fVec12[l32] = 0.0f;
			
		}
		for (int l33 = 0; (l33 < 4096); l33 = (l33 + 1)) {
			fVec13[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fRec32[l34] = 0.0f;
			
		}
		for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			fRec39[l35] = 0.0f;
			
		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			fRec38[l36] = 0.0f;
			
		}
		for (int l37 = 0; (l37 < 16384); l37 = (l37 + 1)) {
			fVec14[l37] = 0.0f;
			
		}
		for (int l38 = 0; (l38 < 2048); l38 = (l38 + 1)) {
			fVec15[l38] = 0.0f;
			
		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fRec36[l39] = 0.0f;
			
		}
		for (int l40 = 0; (l40 < 3); l40 = (l40 + 1)) {
			fRec0[l40] = 0.0f;
			
		}
		for (int l41 = 0; (l41 < 3); l41 = (l41 + 1)) {
			fRec1[l41] = 0.0f;
			
		}
		for (int l42 = 0; (l42 < 3); l42 = (l42 + 1)) {
			fRec2[l42] = 0.0f;
			
		}
		for (int l43 = 0; (l43 < 3); l43 = (l43 + 1)) {
			fRec3[l43] = 0.0f;
			
		}
		for (int l44 = 0; (l44 < 3); l44 = (l44 + 1)) {
			fRec4[l44] = 0.0f;
			
		}
		for (int l45 = 0; (l45 < 3); l45 = (l45 + 1)) {
			fRec5[l45] = 0.0f;
			
		}
		for (int l46 = 0; (l46 < 3); l46 = (l46 + 1)) {
			fRec6[l46] = 0.0f;
			
		}
		for (int l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			fRec7[l47] = 0.0f;
			
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
		ui_interface->declare(0, "tooltip", "~ Zita_Rev's internal   8x8 Feedback Delay Network (FDN) & Schroeder allpass-comb reverberator.  See   Faust's reverbs.lib for documentation and references");
		ui_interface->openHorizontalBox("Zita_Rev Internal FDN Reverb");
		ui_interface->declare(&fVslider2, "1", "");
		ui_interface->declare(&fVslider2, "style", "knob");
		ui_interface->declare(&fVslider2, "tooltip", "T60 = time (in seconds) to decay 60dB in low-frequency band");
		ui_interface->declare(&fVslider2, "unit", "s");
		ui_interface->addVerticalSlider("Low RT60", &fVslider2, 3.0f, 1.0f, 8.0f, 0.100000001f);
		ui_interface->declare(&fVslider3, "2", "");
		ui_interface->declare(&fVslider3, "scale", "log");
		ui_interface->declare(&fVslider3, "style", "knob");
		ui_interface->declare(&fVslider3, "tooltip", "Crossover frequency (Hz) separating low and middle frequencies");
		ui_interface->declare(&fVslider3, "unit", "Hz");
		ui_interface->addVerticalSlider("LF X", &fVslider3, 200.0f, 50.0f, 1000.0f, 1.0f);
		ui_interface->declare(&fVslider0, "3", "");
		ui_interface->declare(&fVslider0, "scale", "log");
		ui_interface->declare(&fVslider0, "style", "knob");
		ui_interface->declare(&fVslider0, "tooltip", "T60 = time (in seconds) to decay 60dB in middle band");
		ui_interface->declare(&fVslider0, "unit", "s");
		ui_interface->addVerticalSlider("Mid RT60", &fVslider0, 2.0f, 1.0f, 8.0f, 0.100000001f);
		ui_interface->declare(&fVslider1, "4", "");
		ui_interface->declare(&fVslider1, "scale", "log");
		ui_interface->declare(&fVslider1, "style", "knob");
		ui_interface->declare(&fVslider1, "tooltip", "Frequency (Hz) at which the high-frequency T60 is half the middle-band's T60");
		ui_interface->declare(&fVslider1, "unit", "Hz");
		ui_interface->addVerticalSlider("HF Damping", &fVslider1, 6000.0f, 1500.0f, 23520.0f, 1.0f);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* input2 = inputs[2];
		FAUSTFLOAT* input3 = inputs[3];
		FAUSTFLOAT* input4 = inputs[4];
		FAUSTFLOAT* input5 = inputs[5];
		FAUSTFLOAT* input6 = inputs[6];
		FAUSTFLOAT* input7 = inputs[7];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		FAUSTFLOAT* output2 = outputs[2];
		FAUSTFLOAT* output3 = outputs[3];
		FAUSTFLOAT* output4 = outputs[4];
		FAUSTFLOAT* output5 = outputs[5];
		FAUSTFLOAT* output6 = outputs[6];
		FAUSTFLOAT* output7 = outputs[7];
		float fSlow0 = float(fVslider0);
		float fSlow1 = expf((fConst2 / fSlow0));
		float fSlow2 = mydsp_faustpower2_f(fSlow1);
		float fSlow3 = cosf((fConst3 * float(fVslider1)));
		float fSlow4 = (1.0f - (fSlow2 * fSlow3));
		float fSlow5 = (1.0f - fSlow2);
		float fSlow6 = (fSlow4 / fSlow5);
		float fSlow7 = sqrtf(max(0.0f, ((mydsp_faustpower2_f(fSlow4) / mydsp_faustpower2_f(fSlow5)) + -1.0f)));
		float fSlow8 = (fSlow6 - fSlow7);
		float fSlow9 = (fSlow1 * (fSlow7 + (1.0f - fSlow6)));
		float fSlow10 = float(fVslider2);
		float fSlow11 = ((expf((fConst2 / fSlow10)) / fSlow1) + -1.0f);
		float fSlow12 = (1.0f / tanf((fConst4 * float(fVslider3))));
		float fSlow13 = (fSlow12 + 1.0f);
		float fSlow14 = (0.0f - ((1.0f - fSlow12) / fSlow13));
		float fSlow15 = (1.0f / fSlow13);
		float fSlow16 = expf((fConst9 / fSlow0));
		float fSlow17 = mydsp_faustpower2_f(fSlow16);
		float fSlow18 = (1.0f - (fSlow3 * fSlow17));
		float fSlow19 = (1.0f - fSlow17);
		float fSlow20 = (fSlow18 / fSlow19);
		float fSlow21 = sqrtf(max(0.0f, ((mydsp_faustpower2_f(fSlow18) / mydsp_faustpower2_f(fSlow19)) + -1.0f)));
		float fSlow22 = (fSlow20 - fSlow21);
		float fSlow23 = (fSlow16 * (fSlow21 + (1.0f - fSlow20)));
		float fSlow24 = ((expf((fConst9 / fSlow10)) / fSlow16) + -1.0f);
		float fSlow25 = expf((fConst14 / fSlow0));
		float fSlow26 = mydsp_faustpower2_f(fSlow25);
		float fSlow27 = (1.0f - (fSlow3 * fSlow26));
		float fSlow28 = (1.0f - fSlow26);
		float fSlow29 = (fSlow27 / fSlow28);
		float fSlow30 = sqrtf(max(0.0f, ((mydsp_faustpower2_f(fSlow27) / mydsp_faustpower2_f(fSlow28)) + -1.0f)));
		float fSlow31 = (fSlow29 - fSlow30);
		float fSlow32 = (fSlow25 * (fSlow30 + (1.0f - fSlow29)));
		float fSlow33 = ((expf((fConst14 / fSlow10)) / fSlow25) + -1.0f);
		float fSlow34 = expf((fConst19 / fSlow0));
		float fSlow35 = mydsp_faustpower2_f(fSlow34);
		float fSlow36 = (1.0f - (fSlow3 * fSlow35));
		float fSlow37 = (1.0f - fSlow35);
		float fSlow38 = (fSlow36 / fSlow37);
		float fSlow39 = sqrtf(max(0.0f, ((mydsp_faustpower2_f(fSlow36) / mydsp_faustpower2_f(fSlow37)) + -1.0f)));
		float fSlow40 = (fSlow38 - fSlow39);
		float fSlow41 = (fSlow34 * (fSlow39 + (1.0f - fSlow38)));
		float fSlow42 = ((expf((fConst19 / fSlow10)) / fSlow34) + -1.0f);
		float fSlow43 = expf((fConst24 / fSlow0));
		float fSlow44 = mydsp_faustpower2_f(fSlow43);
		float fSlow45 = (1.0f - (fSlow3 * fSlow44));
		float fSlow46 = (1.0f - fSlow44);
		float fSlow47 = (fSlow45 / fSlow46);
		float fSlow48 = sqrtf(max(0.0f, ((mydsp_faustpower2_f(fSlow45) / mydsp_faustpower2_f(fSlow46)) + -1.0f)));
		float fSlow49 = (fSlow47 - fSlow48);
		float fSlow50 = (fSlow43 * (fSlow48 + (1.0f - fSlow47)));
		float fSlow51 = ((expf((fConst24 / fSlow10)) / fSlow43) + -1.0f);
		float fSlow52 = expf((fConst29 / fSlow0));
		float fSlow53 = mydsp_faustpower2_f(fSlow52);
		float fSlow54 = (1.0f - (fSlow3 * fSlow53));
		float fSlow55 = (1.0f - fSlow53);
		float fSlow56 = (fSlow54 / fSlow55);
		float fSlow57 = sqrtf(max(0.0f, ((mydsp_faustpower2_f(fSlow54) / mydsp_faustpower2_f(fSlow55)) + -1.0f)));
		float fSlow58 = (fSlow56 - fSlow57);
		float fSlow59 = (fSlow52 * (fSlow57 + (1.0f - fSlow56)));
		float fSlow60 = ((expf((fConst29 / fSlow10)) / fSlow52) + -1.0f);
		float fSlow61 = expf((fConst34 / fSlow0));
		float fSlow62 = mydsp_faustpower2_f(fSlow61);
		float fSlow63 = (1.0f - (fSlow3 * fSlow62));
		float fSlow64 = (1.0f - fSlow62);
		float fSlow65 = (fSlow63 / fSlow64);
		float fSlow66 = sqrtf(max(0.0f, ((mydsp_faustpower2_f(fSlow63) / mydsp_faustpower2_f(fSlow64)) + -1.0f)));
		float fSlow67 = (fSlow65 - fSlow66);
		float fSlow68 = (fSlow61 * (fSlow66 + (1.0f - fSlow65)));
		float fSlow69 = ((expf((fConst34 / fSlow10)) / fSlow61) + -1.0f);
		float fSlow70 = expf((fConst39 / fSlow0));
		float fSlow71 = mydsp_faustpower2_f(fSlow70);
		float fSlow72 = (1.0f - (fSlow3 * fSlow71));
		float fSlow73 = (1.0f - fSlow71);
		float fSlow74 = (fSlow72 / fSlow73);
		float fSlow75 = sqrtf(max(0.0f, ((mydsp_faustpower2_f(fSlow72) / mydsp_faustpower2_f(fSlow73)) + -1.0f)));
		float fSlow76 = (fSlow74 - fSlow75);
		float fSlow77 = (fSlow70 * (fSlow75 + (1.0f - fSlow74)));
		float fSlow78 = ((expf((fConst39 / fSlow10)) / fSlow70) + -1.0f);
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec11[0] = ((fSlow14 * fRec11[1]) + (fSlow15 * (fRec7[1] + fRec7[2])));
			fRec10[0] = ((fSlow8 * fRec10[1]) + (fSlow9 * (fRec7[1] + (fSlow11 * fRec11[0]))));
			fVec0[(IOTA & 32767)] = ((0.353553385f * fRec10[0]) + 9.99999968e-21f);
			float fTemp0 = (fVec0[((IOTA - iConst6) & 32767)] + (float(input7[i]) + (0.600000024f * fRec8[1])));
			fVec1[(IOTA & 2047)] = fTemp0;
			fRec8[0] = fVec1[((IOTA - iConst7) & 2047)];
			float fRec9 = (0.0f - (0.600000024f * fTemp0));
			fRec15[0] = ((fSlow14 * fRec15[1]) + (fSlow15 * (fRec3[1] + fRec3[2])));
			fRec14[0] = ((fSlow22 * fRec14[1]) + (fSlow23 * (fRec3[1] + (fSlow24 * fRec15[0]))));
			fVec2[(IOTA & 32767)] = ((0.353553385f * fRec14[0]) + 9.99999968e-21f);
			float fTemp1 = (fVec2[((IOTA - iConst11) & 32767)] + (float(input3[i]) + (0.600000024f * fRec12[1])));
			fVec3[(IOTA & 4095)] = fTemp1;
			fRec12[0] = fVec3[((IOTA - iConst12) & 4095)];
			float fRec13 = (0.0f - (0.600000024f * fTemp1));
			fRec19[0] = ((fSlow14 * fRec19[1]) + (fSlow15 * (fRec5[1] + fRec5[2])));
			fRec18[0] = ((fSlow31 * fRec18[1]) + (fSlow32 * (fRec5[1] + (fSlow33 * fRec19[0]))));
			fVec4[(IOTA & 16383)] = ((0.353553385f * fRec18[0]) + 9.99999968e-21f);
			float fTemp2 = (fVec4[((IOTA - iConst16) & 16383)] + (float(input5[i]) + (0.600000024f * fRec16[1])));
			fVec5[(IOTA & 4095)] = fTemp2;
			fRec16[0] = fVec5[((IOTA - iConst17) & 4095)];
			float fRec17 = (0.0f - (0.600000024f * fTemp2));
			fRec23[0] = ((fSlow14 * fRec23[1]) + (fSlow15 * (fRec1[1] + fRec1[2])));
			fRec22[0] = ((fSlow40 * fRec22[1]) + (fSlow41 * (fRec1[1] + (fSlow42 * fRec23[0]))));
			fVec6[(IOTA & 32767)] = ((0.353553385f * fRec22[0]) + 9.99999968e-21f);
			float fTemp3 = (fVec6[((IOTA - iConst21) & 32767)] + (float(input1[i]) + (0.600000024f * fRec20[1])));
			fVec7[(IOTA & 4095)] = fTemp3;
			fRec20[0] = fVec7[((IOTA - iConst22) & 4095)];
			float fRec21 = (0.0f - (0.600000024f * fTemp3));
			fRec27[0] = ((fSlow14 * fRec27[1]) + (fSlow15 * (fRec6[1] + fRec6[2])));
			fRec26[0] = ((fSlow49 * fRec26[1]) + (fSlow50 * (fRec6[1] + (fSlow51 * fRec27[0]))));
			fVec8[(IOTA & 16383)] = ((0.353553385f * fRec26[0]) + 9.99999968e-21f);
			float fTemp4 = ((float(input6[i]) + fVec8[((IOTA - iConst26) & 16383)]) - (0.600000024f * fRec24[1]));
			fVec9[(IOTA & 2047)] = fTemp4;
			fRec24[0] = fVec9[((IOTA - iConst27) & 2047)];
			float fRec25 = (0.600000024f * fTemp4);
			fRec31[0] = ((fSlow14 * fRec31[1]) + (fSlow15 * (fRec2[1] + fRec2[2])));
			fRec30[0] = ((fSlow58 * fRec30[1]) + (fSlow59 * (fRec2[1] + (fSlow60 * fRec31[0]))));
			fVec10[(IOTA & 16383)] = ((0.353553385f * fRec30[0]) + 9.99999968e-21f);
			float fTemp5 = ((float(input2[i]) + fVec10[((IOTA - iConst31) & 16383)]) - (0.600000024f * fRec28[1]));
			fVec11[(IOTA & 4095)] = fTemp5;
			fRec28[0] = fVec11[((IOTA - iConst32) & 4095)];
			float fRec29 = (0.600000024f * fTemp5);
			fRec35[0] = ((fSlow14 * fRec35[1]) + (fSlow15 * (fRec4[1] + fRec4[2])));
			fRec34[0] = ((fSlow67 * fRec34[1]) + (fSlow68 * (fRec4[1] + (fSlow69 * fRec35[0]))));
			fVec12[(IOTA & 16383)] = ((0.353553385f * fRec34[0]) + 9.99999968e-21f);
			float fTemp6 = ((float(input4[i]) + fVec12[((IOTA - iConst36) & 16383)]) - (0.600000024f * fRec32[1]));
			fVec13[(IOTA & 4095)] = fTemp6;
			fRec32[0] = fVec13[((IOTA - iConst37) & 4095)];
			float fRec33 = (0.600000024f * fTemp6);
			fRec39[0] = ((fSlow14 * fRec39[1]) + (fSlow15 * (fRec0[1] + fRec0[2])));
			fRec38[0] = ((fSlow76 * fRec38[1]) + (fSlow77 * (fRec0[1] + (fSlow78 * fRec39[0]))));
			fVec14[(IOTA & 16383)] = ((0.353553385f * fRec38[0]) + 9.99999968e-21f);
			float fTemp7 = ((float(input0[i]) + fVec14[((IOTA - iConst41) & 16383)]) - (0.600000024f * fRec36[1]));
			fVec15[(IOTA & 2047)] = fTemp7;
			fRec36[0] = fVec15[((IOTA - iConst42) & 2047)];
			float fRec37 = (0.600000024f * fTemp7);
			float fTemp8 = (fRec37 + fRec33);
			float fTemp9 = (fRec25 + (fRec29 + fTemp8));
			fRec0[0] = (fRec8[1] + (fRec12[1] + (fRec16[1] + (fRec20[1] + (fRec24[1] + (fRec28[1] + (fRec32[1] + (fRec36[1] + (fRec9 + (fRec13 + (fRec17 + (fRec21 + fTemp9))))))))))));
			fRec1[0] = ((fRec24[1] + (fRec28[1] + (fRec32[1] + (fRec36[1] + fTemp9)))) - (fRec8[1] + (fRec12[1] + (fRec16[1] + (fRec20[1] + (fRec9 + (fRec13 + (fRec21 + fRec17))))))));
			float fTemp10 = (fRec29 + fRec25);
			fRec2[0] = ((fRec16[1] + (fRec20[1] + (fRec32[1] + (fRec36[1] + (fRec17 + (fRec21 + fTemp8)))))) - (fRec8[1] + (fRec12[1] + (fRec24[1] + (fRec28[1] + (fRec9 + (fRec13 + fTemp10)))))));
			fRec3[0] = ((fRec8[1] + (fRec12[1] + (fRec32[1] + (fRec36[1] + (fRec9 + (fRec13 + fTemp8)))))) - (fRec16[1] + (fRec20[1] + (fRec24[1] + (fRec28[1] + (fRec17 + (fRec21 + fTemp10)))))));
			float fTemp11 = (fRec37 + fRec29);
			float fTemp12 = (fRec33 + fRec25);
			fRec4[0] = ((fRec12[1] + (fRec20[1] + (fRec28[1] + (fRec36[1] + (fRec13 + (fRec21 + fTemp11)))))) - (fRec8[1] + (fRec16[1] + (fRec24[1] + (fRec32[1] + (fRec9 + (fRec17 + fTemp12)))))));
			fRec5[0] = ((fRec8[1] + (fRec16[1] + (fRec28[1] + (fRec36[1] + (fRec9 + (fRec17 + fTemp11)))))) - (fRec12[1] + (fRec20[1] + (fRec24[1] + (fRec32[1] + (fRec13 + (fRec21 + fTemp12)))))));
			float fTemp13 = (fRec37 + fRec25);
			float fTemp14 = (fRec33 + fRec29);
			fRec6[0] = ((fRec8[1] + (fRec20[1] + (fRec24[1] + (fRec36[1] + (fRec9 + (fRec21 + fTemp13)))))) - (fRec12[1] + (fRec16[1] + (fRec28[1] + (fRec32[1] + (fRec13 + (fRec17 + fTemp14)))))));
			fRec7[0] = ((fRec12[1] + (fRec16[1] + (fRec24[1] + (fRec36[1] + (fRec13 + (fRec17 + fTemp13)))))) - (fRec8[1] + (fRec20[1] + (fRec28[1] + (fRec32[1] + (fRec9 + (fRec21 + fTemp14)))))));
			output0[i] = FAUSTFLOAT(fRec0[0]);
			output1[i] = FAUSTFLOAT(fRec1[0]);
			output2[i] = FAUSTFLOAT(fRec2[0]);
			output3[i] = FAUSTFLOAT(fRec3[0]);
			output4[i] = FAUSTFLOAT(fRec4[0]);
			output5[i] = FAUSTFLOAT(fRec5[0]);
			output6[i] = FAUSTFLOAT(fRec6[0]);
			output7[i] = FAUSTFLOAT(fRec7[0]);
			fRec11[1] = fRec11[0];
			fRec10[1] = fRec10[0];
			IOTA = (IOTA + 1);
			fRec8[1] = fRec8[0];
			fRec15[1] = fRec15[0];
			fRec14[1] = fRec14[0];
			fRec12[1] = fRec12[0];
			fRec19[1] = fRec19[0];
			fRec18[1] = fRec18[0];
			fRec16[1] = fRec16[0];
			fRec23[1] = fRec23[0];
			fRec22[1] = fRec22[0];
			fRec20[1] = fRec20[0];
			fRec27[1] = fRec27[0];
			fRec26[1] = fRec26[0];
			fRec24[1] = fRec24[0];
			fRec31[1] = fRec31[0];
			fRec30[1] = fRec30[0];
			fRec28[1] = fRec28[0];
			fRec35[1] = fRec35[0];
			fRec34[1] = fRec34[0];
			fRec32[1] = fRec32[0];
			fRec39[1] = fRec39[0];
			fRec38[1] = fRec38[0];
			fRec36[1] = fRec36[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fRec4[2] = fRec4[1];
			fRec4[1] = fRec4[0];
			fRec5[2] = fRec5[1];
			fRec5[1] = fRec5[0];
			fRec6[2] = fRec6[1];
			fRec6[1] = fRec6[0];
			fRec7[2] = fRec7[1];
			fRec7[1] = fRec7[0];
			
		}
		
	}

	
};

#endif
