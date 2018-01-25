/* ------------------------------------------------------------
name: "felix2"
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
	int IOTA;
	float fVec0[512];
	float fVec1[512];
	float fVec2[512];
	float fVec3[512];
	float fVec4[512];
	float fVec5[512];
	float fRec0[2];
	FAUSTFLOAT fVbargraph0;
	float fRec1[2];
	FAUSTFLOAT fVbargraph1;
	float fRec2[2];
	FAUSTFLOAT fVbargraph2;
	float fRec3[2];
	FAUSTFLOAT fVbargraph3;
	float fRec4[2];
	FAUSTFLOAT fVbargraph4;
	float fRec5[2];
	FAUSTFLOAT fVbargraph5;
	float fRec6[2];
	FAUSTFLOAT fVbargraph6;
	float fRec7[2];
	FAUSTFLOAT fVbargraph7;
	float fRec8[2];
	FAUSTFLOAT fVbargraph8;
	float fRec9[2];
	FAUSTFLOAT fVbargraph9;
	float fRec10[2];
	FAUSTFLOAT fVbargraph10;
	float fRec11[2];
	FAUSTFLOAT fVbargraph11;
	float fRec12[2];
	FAUSTFLOAT fVbargraph12;
	float fRec13[2];
	FAUSTFLOAT fVbargraph13;
	float fRec14[2];
	FAUSTFLOAT fVbargraph14;
	float fRec15[2];
	FAUSTFLOAT fVbargraph15;
	float fRec16[2];
	FAUSTFLOAT fVbargraph16;
	float fRec17[2];
	FAUSTFLOAT fVbargraph17;
	float fRec18[2];
	FAUSTFLOAT fVbargraph18;
	float fRec19[2];
	FAUSTFLOAT fVbargraph19;
	float fRec20[2];
	FAUSTFLOAT fVbargraph20;
	float fRec21[2];
	FAUSTFLOAT fVbargraph21;
	float fRec22[2];
	FAUSTFLOAT fVbargraph22;
	float fRec23[2];
	FAUSTFLOAT fVbargraph23;
	float fRec24[2];
	FAUSTFLOAT fVbargraph24;
	float fRec25[2];
	FAUSTFLOAT fVbargraph25;
	float fRec26[2];
	FAUSTFLOAT fVbargraph26;
	float fRec27[2];
	FAUSTFLOAT fVbargraph27;
	float fRec28[2];
	FAUSTFLOAT fVbargraph28;
	float fRec29[2];
	FAUSTFLOAT fVbargraph29;
	float fRec30[2];
	FAUSTFLOAT fVbargraph30;
	float fRec31[2];
	FAUSTFLOAT fVbargraph31;
	float fRec32[2];
	FAUSTFLOAT fVbargraph32;
	float fRec33[2];
	FAUSTFLOAT fVbargraph33;
	float fRec34[2];
	FAUSTFLOAT fVbargraph34;
	float fRec35[2];
	FAUSTFLOAT fVbargraph35;
	
 public:
	
	void metadata(Meta* m) { 
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
		m->declare("name", "felix2");
	}

	virtual int getNumInputs() {
		return 6;
		
	}
	virtual int getNumOutputs() {
		return 36;
		
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
			case 8: {
				rate = 1;
				break;
			}
			case 9: {
				rate = 1;
				break;
			}
			case 10: {
				rate = 1;
				break;
			}
			case 11: {
				rate = 1;
				break;
			}
			case 12: {
				rate = 1;
				break;
			}
			case 13: {
				rate = 1;
				break;
			}
			case 14: {
				rate = 1;
				break;
			}
			case 15: {
				rate = 1;
				break;
			}
			case 16: {
				rate = 1;
				break;
			}
			case 17: {
				rate = 1;
				break;
			}
			case 18: {
				rate = 1;
				break;
			}
			case 19: {
				rate = 1;
				break;
			}
			case 20: {
				rate = 1;
				break;
			}
			case 21: {
				rate = 1;
				break;
			}
			case 22: {
				rate = 1;
				break;
			}
			case 23: {
				rate = 1;
				break;
			}
			case 24: {
				rate = 1;
				break;
			}
			case 25: {
				rate = 1;
				break;
			}
			case 26: {
				rate = 1;
				break;
			}
			case 27: {
				rate = 1;
				break;
			}
			case 28: {
				rate = 1;
				break;
			}
			case 29: {
				rate = 1;
				break;
			}
			case 30: {
				rate = 1;
				break;
			}
			case 31: {
				rate = 1;
				break;
			}
			case 32: {
				rate = 1;
				break;
			}
			case 33: {
				rate = 1;
				break;
			}
			case 34: {
				rate = 1;
				break;
			}
			case 35: {
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
		fConst0 = (96.0f / min(192000.0f, max(1.0f, float(fSamplingFreq))));
		
	}
	
	virtual void instanceResetUserInterface() {
		
	}
	
	virtual void instanceClear() {
		IOTA = 0;
		for (int l0 = 0; (l0 < 512); l0 = (l0 + 1)) {
			fVec0[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 512); l1 = (l1 + 1)) {
			fVec1[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 512); l2 = (l2 + 1)) {
			fVec2[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 512); l3 = (l3 + 1)) {
			fVec3[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 512); l4 = (l4 + 1)) {
			fVec4[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 512); l5 = (l5 + 1)) {
			fVec5[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec0[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec1[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec2[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec3[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec4[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec5[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec6[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec7[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec8[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec9[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec10[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec11[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec12[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec13[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec14[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec15[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec16[l22] = 0.0f;
			
		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec17[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fRec18[l24] = 0.0f;
			
		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fRec19[l25] = 0.0f;
			
		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fRec20[l26] = 0.0f;
			
		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fRec21[l27] = 0.0f;
			
		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fRec22[l28] = 0.0f;
			
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec23[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fRec24[l30] = 0.0f;
			
		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			fRec25[l31] = 0.0f;
			
		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fRec26[l32] = 0.0f;
			
		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fRec27[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fRec28[l34] = 0.0f;
			
		}
		for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			fRec29[l35] = 0.0f;
			
		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			fRec30[l36] = 0.0f;
			
		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fRec31[l37] = 0.0f;
			
		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec32[l38] = 0.0f;
			
		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fRec33[l39] = 0.0f;
			
		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			fRec34[l40] = 0.0f;
			
		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fRec35[l41] = 0.0f;
			
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
		ui_interface->openVerticalBox("felix2");
		ui_interface->openHorizontalBox("ctrl   0");
		ui_interface->addVerticalBargraph("ctrl  0", &fVbargraph0, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl  1", &fVbargraph1, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl  2", &fVbargraph2, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl  3", &fVbargraph3, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl  4", &fVbargraph4, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl  5", &fVbargraph5, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("ctrl   1");
		ui_interface->addVerticalBargraph("ctrl 10", &fVbargraph6, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 11", &fVbargraph7, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 12", &fVbargraph8, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 13", &fVbargraph9, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 14", &fVbargraph10, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 15", &fVbargraph11, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("ctrl   2");
		ui_interface->addVerticalBargraph("ctrl 20", &fVbargraph12, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 21", &fVbargraph13, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 22", &fVbargraph14, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 23", &fVbargraph15, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 24", &fVbargraph16, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 25", &fVbargraph17, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("ctrl   3");
		ui_interface->addVerticalBargraph("ctrl 30", &fVbargraph18, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 31", &fVbargraph19, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 32", &fVbargraph20, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 33", &fVbargraph21, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 34", &fVbargraph22, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 35", &fVbargraph23, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("ctrl   4");
		ui_interface->addVerticalBargraph("ctrl 40", &fVbargraph24, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 41", &fVbargraph25, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 42", &fVbargraph26, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 43", &fVbargraph27, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 44", &fVbargraph28, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 45", &fVbargraph29, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("ctrl   5");
		ui_interface->addVerticalBargraph("ctrl 50", &fVbargraph30, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 51", &fVbargraph31, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 52", &fVbargraph32, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 53", &fVbargraph33, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 54", &fVbargraph34, 0.0f, 1.0f);
		ui_interface->addVerticalBargraph("ctrl 55", &fVbargraph35, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* input2 = inputs[2];
		FAUSTFLOAT* input3 = inputs[3];
		FAUSTFLOAT* input4 = inputs[4];
		FAUSTFLOAT* input5 = inputs[5];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		FAUSTFLOAT* output2 = outputs[2];
		FAUSTFLOAT* output3 = outputs[3];
		FAUSTFLOAT* output4 = outputs[4];
		FAUSTFLOAT* output5 = outputs[5];
		FAUSTFLOAT* output6 = outputs[6];
		FAUSTFLOAT* output7 = outputs[7];
		FAUSTFLOAT* output8 = outputs[8];
		FAUSTFLOAT* output9 = outputs[9];
		FAUSTFLOAT* output10 = outputs[10];
		FAUSTFLOAT* output11 = outputs[11];
		FAUSTFLOAT* output12 = outputs[12];
		FAUSTFLOAT* output13 = outputs[13];
		FAUSTFLOAT* output14 = outputs[14];
		FAUSTFLOAT* output15 = outputs[15];
		FAUSTFLOAT* output16 = outputs[16];
		FAUSTFLOAT* output17 = outputs[17];
		FAUSTFLOAT* output18 = outputs[18];
		FAUSTFLOAT* output19 = outputs[19];
		FAUSTFLOAT* output20 = outputs[20];
		FAUSTFLOAT* output21 = outputs[21];
		FAUSTFLOAT* output22 = outputs[22];
		FAUSTFLOAT* output23 = outputs[23];
		FAUSTFLOAT* output24 = outputs[24];
		FAUSTFLOAT* output25 = outputs[25];
		FAUSTFLOAT* output26 = outputs[26];
		FAUSTFLOAT* output27 = outputs[27];
		FAUSTFLOAT* output28 = outputs[28];
		FAUSTFLOAT* output29 = outputs[29];
		FAUSTFLOAT* output30 = outputs[30];
		FAUSTFLOAT* output31 = outputs[31];
		FAUSTFLOAT* output32 = outputs[32];
		FAUSTFLOAT* output33 = outputs[33];
		FAUSTFLOAT* output34 = outputs[34];
		FAUSTFLOAT* output35 = outputs[35];
		for (int i = 0; (i < count); i = (i + 1)) {
			fVec0[(IOTA & 511)] = float(input0[i]);
			float fTemp0 = float(input1[i]);
			fVec1[(IOTA & 511)] = fTemp0;
			float fTemp1 = float(input2[i]);
			fVec2[(IOTA & 511)] = fTemp1;
			float fTemp2 = float(input3[i]);
			fVec3[(IOTA & 511)] = fTemp2;
			float fTemp3 = float(input4[i]);
			fVec4[(IOTA & 511)] = fTemp3;
			float fTemp4 = float(input5[i]);
			fVec5[(IOTA & 511)] = fTemp4;
			fRec0[0] = max((fRec0[1] - fConst0), fabsf((((((fVec0[((IOTA - 256) & 511)] + fVec1[((IOTA - 244) & 511)]) + fVec2[((IOTA - 233) & 511)]) + fVec3[((IOTA - 221) & 511)]) + fVec4[((IOTA - 209) & 511)]) + fVec5[((IOTA - 197) & 511)])));
			fVbargraph0 = FAUSTFLOAT(fRec0[0]);
			output0[i] = FAUSTFLOAT(fVbargraph0);
			float fTemp5 = (fVec0[((IOTA - 256) & 511)] + fVec1[((IOTA - 246) & 511)]);
			fRec1[0] = max((fRec1[1] - fConst0), fabsf(((((fTemp5 + fVec2[((IOTA - 236) & 511)]) + fVec3[((IOTA - 225) & 511)]) + fVec4[((IOTA - 215) & 511)]) + fVec5[((IOTA - 204) & 511)])));
			fVbargraph1 = FAUSTFLOAT(fRec1[0]);
			output1[i] = FAUSTFLOAT(fVbargraph1);
			fRec2[0] = max((fRec2[1] - fConst0), fabsf((((((fVec0[((IOTA - 256) & 511)] + fVec1[((IOTA - 247) & 511)]) + fVec2[((IOTA - 239) & 511)]) + fVec3[((IOTA - 230) & 511)]) + fVec4[((IOTA - 220) & 511)]) + fVec5[((IOTA - 211) & 511)])));
			fVbargraph2 = FAUSTFLOAT(fRec2[0]);
			output2[i] = FAUSTFLOAT(fVbargraph2);
			float fTemp6 = (fVec0[((IOTA - 256) & 511)] + fVec1[((IOTA - 249) & 511)]);
			float fTemp7 = (fTemp6 + fVec2[((IOTA - 241) & 511)]);
			fRec3[0] = max((fRec3[1] - fConst0), fabsf((((fTemp7 + fVec3[((IOTA - 233) & 511)]) + fVec4[((IOTA - 225) & 511)]) + fVec5[((IOTA - 217) & 511)])));
			fVbargraph3 = FAUSTFLOAT(fRec3[0]);
			output3[i] = FAUSTFLOAT(fVbargraph3);
			float fTemp8 = (fVec0[((IOTA - 256) & 511)] + fVec1[((IOTA - 250) & 511)]);
			fRec4[0] = max((fRec4[1] - fConst0), fabsf(((((fTemp8 + fVec2[((IOTA - 243) & 511)]) + fVec3[((IOTA - 236) & 511)]) + fVec4[((IOTA - 229) & 511)]) + fVec5[((IOTA - 222) & 511)])));
			fVbargraph4 = FAUSTFLOAT(fRec4[0]);
			output4[i] = FAUSTFLOAT(fVbargraph4);
			fRec5[0] = max((fRec5[1] - fConst0), fabsf(((((fTemp8 + fVec2[((IOTA - 245) & 511)]) + fVec3[((IOTA - 239) & 511)]) + fVec4[((IOTA - 232) & 511)]) + fVec5[((IOTA - 225) & 511)])));
			fVbargraph5 = FAUSTFLOAT(fRec5[0]);
			output5[i] = FAUSTFLOAT(fVbargraph5);
			fRec6[0] = max((fRec6[1] - fConst0), fabsf(((((fTemp5 + fVec2[((IOTA - 235) & 511)]) + fVec3[((IOTA - 224) & 511)]) + fVec4[((IOTA - 213) & 511)]) + fVec5[((IOTA - 201) & 511)])));
			fVbargraph6 = FAUSTFLOAT(fRec6[0]);
			output6[i] = FAUSTFLOAT(fVbargraph6);
			fRec7[0] = max((fRec7[1] - fConst0), fabsf((fVec4[((IOTA - 221) & 511)] + (fVec1[((IOTA - 248) & 511)] + (fVec5[((IOTA - 211) & 511)] + (fVec3[((IOTA - 230) & 511)] + (fVec0[((IOTA - 256) & 511)] + fVec2[((IOTA - 239) & 511)])))))));
			fVbargraph7 = FAUSTFLOAT(fRec7[0]);
			output7[i] = FAUSTFLOAT(fVbargraph7);
			fRec8[0] = max((fRec8[1] - fConst0), fabsf(((((fTemp6 + fVec2[((IOTA - 243) & 511)]) + fVec3[((IOTA - 235) & 511)]) + fVec4[((IOTA - 227) & 511)]) + fVec5[((IOTA - 219) & 511)])));
			fVbargraph8 = FAUSTFLOAT(fRec8[0]);
			output8[i] = FAUSTFLOAT(fVbargraph8);
			fRec9[0] = max((fRec9[1] - fConst0), fabsf((fVec1[((IOTA - 251) & 511)] + (fVec5[((IOTA - 225) & 511)] + (fVec4[((IOTA - 232) & 511)] + (fVec3[((IOTA - 239) & 511)] + (fVec0[((IOTA - 256) & 511)] + fVec2[((IOTA - 245) & 511)])))))));
			fVbargraph9 = FAUSTFLOAT(fRec9[0]);
			output9[i] = FAUSTFLOAT(fVbargraph9);
			fRec10[0] = max((fRec10[1] - fConst0), fabsf((((((fVec0[((IOTA - 256) & 511)] + fVec1[((IOTA - 251) & 511)]) + fVec2[((IOTA - 247) & 511)]) + fVec3[((IOTA - 241) & 511)]) + fVec4[((IOTA - 236) & 511)]) + fVec5[((IOTA - 230) & 511)])));
			fVbargraph10 = FAUSTFLOAT(fRec10[0]);
			output10[i] = FAUSTFLOAT(fVbargraph10);
			float fTemp9 = ((fVec0[((IOTA - 256) & 511)] + fVec1[((IOTA - 252) & 511)]) + fVec2[((IOTA - 248) & 511)]);
			fRec11[0] = max((fRec11[1] - fConst0), fabsf((((fTemp9 + fVec3[((IOTA - 243) & 511)]) + fVec4[((IOTA - 238) & 511)]) + fVec5[((IOTA - 233) & 511)])));
			fVbargraph11 = FAUSTFLOAT(fRec11[0]);
			output11[i] = FAUSTFLOAT(fVbargraph11);
			fRec12[0] = max((fRec12[1] - fConst0), fabsf((((fTemp7 + fVec3[((IOTA - 232) & 511)]) + fVec4[((IOTA - 223) & 511)]) + fVec5[((IOTA - 212) & 511)])));
			fVbargraph12 = FAUSTFLOAT(fRec12[0]);
			output12[i] = FAUSTFLOAT(fVbargraph12);
			fRec13[0] = max((fRec13[1] - fConst0), fabsf((fVec5[((IOTA - 224) & 511)] + (fVec3[((IOTA - 240) & 511)] + (fVec2[((IOTA - 246) & 511)] + (fVec1[((IOTA - 251) & 511)] + (fVec0[((IOTA - 256) & 511)] + fVec4[((IOTA - 232) & 511)])))))));
			fVbargraph13 = FAUSTFLOAT(fRec13[0]);
			output13[i] = FAUSTFLOAT(fVbargraph13);
			fRec14[0] = max((fRec14[1] - fConst0), fabsf((fVec5[((IOTA - 231) & 511)] + (fVec3[((IOTA - 244) & 511)] + (fTemp9 + fVec4[((IOTA - 238) & 511)])))));
			fVbargraph14 = FAUSTFLOAT(fRec14[0]);
			output14[i] = FAUSTFLOAT(fVbargraph14);
			fRec15[0] = max((fRec15[1] - fConst0), fabsf((((((fVec0[((IOTA - 256) & 511)] + fVec1[((IOTA - 253) & 511)]) + fVec2[((IOTA - 250) & 511)]) + fVec3[((IOTA - 246) & 511)]) + fVec4[((IOTA - 241) & 511)]) + fVec5[((IOTA - 236) & 511)])));
			fVbargraph15 = FAUSTFLOAT(fRec15[0]);
			output15[i] = FAUSTFLOAT(fVbargraph15);
			float fTemp10 = (fVec0[((IOTA - 256) & 511)] + fVec1[((IOTA - 254) & 511)]);
			fRec16[0] = max((fRec16[1] - fConst0), fabsf(((((fTemp10 + fVec2[((IOTA - 251) & 511)]) + fVec3[((IOTA - 248) & 511)]) + fVec4[((IOTA - 244) & 511)]) + fVec5[((IOTA - 239) & 511)])));
			fVbargraph16 = FAUSTFLOAT(fRec16[0]);
			output16[i] = FAUSTFLOAT(fVbargraph16);
			fRec17[0] = max((fRec17[1] - fConst0), fabsf(((((fTemp10 + fVec2[((IOTA - 252) & 511)]) + fVec3[((IOTA - 249) & 511)]) + fVec4[((IOTA - 245) & 511)]) + fVec5[((IOTA - 242) & 511)])));
			fVbargraph17 = FAUSTFLOAT(fRec17[0]);
			output17[i] = FAUSTFLOAT(fVbargraph17);
			fRec18[0] = max((fRec18[1] - fConst0), fabsf((fVec4[((IOTA - 246) & 511)] + (fVec3[((IOTA - 252) & 511)] + (fVec2[((IOTA - 256) & 511)] + (fVec1[((IOTA - 257) & 511)] + (fVec0[((IOTA - 256) & 511)] + fVec5[((IOTA - 239) & 511)])))))));
			fVbargraph18 = FAUSTFLOAT(fRec18[0]);
			output18[i] = FAUSTFLOAT(fVbargraph18);
			float fTemp11 = (fVec1[((IOTA - 256) & 511)] + (fVec0[((IOTA - 256) & 511)] + fVec2[((IOTA - 256) & 511)]));
			fRec19[0] = max((fRec19[1] - fConst0), fabsf((fVec5[((IOTA - 245) & 511)] + (fVec4[((IOTA - 250) & 511)] + (fVec3[((IOTA - 253) & 511)] + fTemp11)))));
			fVbargraph19 = FAUSTFLOAT(fRec19[0]);
			output19[i] = FAUSTFLOAT(fVbargraph19);
			float fTemp12 = (fTemp11 + fVec3[((IOTA - 254) & 511)]);
			fRec20[0] = max((fRec20[1] - fConst0), fabsf(((fTemp12 + fVec4[((IOTA - 251) & 511)]) + fVec5[((IOTA - 247) & 511)])));
			fVbargraph20 = FAUSTFLOAT(fRec20[0]);
			output20[i] = FAUSTFLOAT(fVbargraph20);
			fRec21[0] = max((fRec21[1] - fConst0), fabsf(((fTemp12 + fVec4[((IOTA - 252) & 511)]) + fVec5[((IOTA - 249) & 511)])));
			fVbargraph21 = FAUSTFLOAT(fRec21[0]);
			output21[i] = FAUSTFLOAT(fVbargraph21);
			fRec22[0] = max((fRec22[1] - fConst0), fabsf(((fTemp12 + fVec4[((IOTA - 253) & 511)]) + fVec5[((IOTA - 250) & 511)])));
			fVbargraph22 = FAUSTFLOAT(fRec22[0]);
			output22[i] = FAUSTFLOAT(fVbargraph22);
			fRec23[0] = max((fRec23[1] - fConst0), fabsf((fVec5[((IOTA - 251) & 511)] + (fVec3[((IOTA - 255) & 511)] + (fTemp11 + fVec4[((IOTA - 253) & 511)])))));
			fVbargraph23 = FAUSTFLOAT(fRec23[0]);
			output23[i] = FAUSTFLOAT(fVbargraph23);
			fRec24[0] = max((fRec24[1] - fConst0), fabsf((((((fVec0[((IOTA - 256) & 511)] + fVec1[((IOTA - 263) & 511)]) + fVec2[((IOTA - 270) & 511)]) + fVec3[((IOTA - 274) & 511)]) + fVec4[((IOTA - 276) & 511)]) + fVec5[((IOTA - 276) & 511)])));
			fVbargraph24 = FAUSTFLOAT(fRec24[0]);
			output24[i] = FAUSTFLOAT(fVbargraph24);
			fRec25[0] = max((fRec25[1] - fConst0), fabsf((((((fVec0[((IOTA - 256) & 511)] + fVec1[((IOTA - 261) & 511)]) + fVec2[((IOTA - 265) & 511)]) + fVec3[((IOTA - 268) & 511)]) + fVec4[((IOTA - 269) & 511)]) + fVec5[((IOTA - 269) & 511)])));
			fVbargraph25 = FAUSTFLOAT(fRec25[0]);
			output25[i] = FAUSTFLOAT(fVbargraph25);
			float fTemp13 = ((fVec0[((IOTA - 256) & 511)] + fVec1[((IOTA - 260) & 511)]) + fVec2[((IOTA - 263) & 511)]);
			fRec26[0] = max((fRec26[1] - fConst0), fabsf((((fTemp13 + fVec3[((IOTA - 265) & 511)]) + fVec4[((IOTA - 265) & 511)]) + fVec5[((IOTA - 265) & 511)])));
			fVbargraph26 = FAUSTFLOAT(fRec26[0]);
			output26[i] = FAUSTFLOAT(fVbargraph26);
			fRec27[0] = max((fRec27[1] - fConst0), fabsf((((((fVec0[((IOTA - 256) & 511)] + fVec1[((IOTA - 259) & 511)]) + fVec2[((IOTA - 261) & 511)]) + fVec3[((IOTA - 263) & 511)]) + fVec4[((IOTA - 263) & 511)]) + fVec5[((IOTA - 263) & 511)])));
			fVbargraph27 = FAUSTFLOAT(fRec27[0]);
			output27[i] = FAUSTFLOAT(fVbargraph27);
			float fTemp14 = (fVec0[((IOTA - 256) & 511)] + fVec1[((IOTA - 258) & 511)]);
			fRec28[0] = max((fRec28[1] - fConst0), fabsf(((((fTemp14 + fVec2[((IOTA - 260) & 511)]) + fVec3[((IOTA - 261) & 511)]) + fVec4[((IOTA - 262) & 511)]) + fVec5[((IOTA - 262) & 511)])));
			fVbargraph28 = FAUSTFLOAT(fRec28[0]);
			output28[i] = FAUSTFLOAT(fVbargraph28);
			fRec29[0] = max((fRec29[1] - fConst0), fabsf(((((fTemp14 + fVec2[((IOTA - 259) & 511)]) + fVec3[((IOTA - 260) & 511)]) + fVec4[((IOTA - 261) & 511)]) + fVec5[((IOTA - 261) & 511)])));
			fVbargraph29 = FAUSTFLOAT(fRec29[0]);
			output29[i] = FAUSTFLOAT(fVbargraph29);
			fRec30[0] = max((fRec30[1] - fConst0), fabsf((((((fVec0[((IOTA - 256) & 511)] + fVec1[((IOTA - 266) & 511)]) + fVec2[((IOTA - 276) & 511)]) + fVec3[((IOTA - 285) & 511)]) + fVec4[((IOTA - 293) & 511)]) + fVec5[((IOTA - 300) & 511)])));
			fVbargraph30 = FAUSTFLOAT(fRec30[0]);
			output30[i] = FAUSTFLOAT(fVbargraph30);
			fRec31[0] = max((fRec31[1] - fConst0), fabsf((((((fVec0[((IOTA - 256) & 511)] + fVec1[((IOTA - 264) & 511)]) + fVec2[((IOTA - 272) & 511)]) + fVec3[((IOTA - 278) & 511)]) + fVec4[((IOTA - 284) & 511)]) + fVec5[((IOTA - 289) & 511)])));
			fVbargraph31 = FAUSTFLOAT(fRec31[0]);
			output31[i] = FAUSTFLOAT(fVbargraph31);
			fRec32[0] = max((fRec32[1] - fConst0), fabsf((((((fVec0[((IOTA - 256) & 511)] + fVec1[((IOTA - 262) & 511)]) + fVec2[((IOTA - 268) & 511)]) + fVec3[((IOTA - 273) & 511)]) + fVec4[((IOTA - 278) & 511)]) + fVec5[((IOTA - 281) & 511)])));
			fVbargraph32 = FAUSTFLOAT(fRec32[0]);
			output32[i] = FAUSTFLOAT(fVbargraph32);
			fRec33[0] = max((fRec33[1] - fConst0), fabsf((fVec4[((IOTA - 274) & 511)] + (fVec3[((IOTA - 270) & 511)] + (fVec2[((IOTA - 266) & 511)] + (fVec1[((IOTA - 261) & 511)] + (fVec0[((IOTA - 256) & 511)] + fVec5[((IOTA - 276) & 511)])))))));
			fVbargraph33 = FAUSTFLOAT(fRec33[0]);
			output33[i] = FAUSTFLOAT(fVbargraph33);
			fRec34[0] = max((fRec34[1] - fConst0), fabsf((((fVec2[((IOTA - 264) & 511)] + (fVec1[((IOTA - 260) & 511)] + (fVec0[((IOTA - 256) & 511)] + fVec3[((IOTA - 268) & 511)]))) + fVec4[((IOTA - 271) & 511)]) + fVec5[((IOTA - 273) & 511)])));
			fVbargraph34 = FAUSTFLOAT(fRec34[0]);
			output34[i] = FAUSTFLOAT(fVbargraph34);
			fRec35[0] = max((fRec35[1] - fConst0), fabsf((((fTemp13 + fVec3[((IOTA - 266) & 511)]) + fVec4[((IOTA - 268) & 511)]) + fVec5[((IOTA - 270) & 511)])));
			fVbargraph35 = FAUSTFLOAT(fRec35[0]);
			output35[i] = FAUSTFLOAT(fVbargraph35);
			IOTA = (IOTA + 1);
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec7[1] = fRec7[0];
			fRec8[1] = fRec8[0];
			fRec9[1] = fRec9[0];
			fRec10[1] = fRec10[0];
			fRec11[1] = fRec11[0];
			fRec12[1] = fRec12[0];
			fRec13[1] = fRec13[0];
			fRec14[1] = fRec14[0];
			fRec15[1] = fRec15[0];
			fRec16[1] = fRec16[0];
			fRec17[1] = fRec17[0];
			fRec18[1] = fRec18[0];
			fRec19[1] = fRec19[0];
			fRec20[1] = fRec20[0];
			fRec21[1] = fRec21[0];
			fRec22[1] = fRec22[0];
			fRec23[1] = fRec23[0];
			fRec24[1] = fRec24[0];
			fRec25[1] = fRec25[0];
			fRec26[1] = fRec26[0];
			fRec27[1] = fRec27[0];
			fRec28[1] = fRec28[0];
			fRec29[1] = fRec29[0];
			fRec30[1] = fRec30[0];
			fRec31[1] = fRec31[0];
			fRec32[1] = fRec32[0];
			fRec33[1] = fRec33[0];
			fRec34[1] = fRec34[0];
			fRec35[1] = fRec35[0];
			
		}
		
	}

	
};

#endif
