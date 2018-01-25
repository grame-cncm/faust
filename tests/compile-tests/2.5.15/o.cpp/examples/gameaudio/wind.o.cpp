//----------------------------------------------------------
// name: "wind"
//
// Code generated with Faust 2.5.15 (https://faust.grame.fr)
//----------------------------------------------------------

/* link with  */
#include <math.h>
#ifndef FAUSTPOWER
#define FAUSTPOWER
#include <cmath>
template <int N> inline int faustpower(int x)              { return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline int faustpower<0>(int x)            { return 1; }
template <> 	 inline int faustpower<1>(int x)            { return x; }
template <> 	 inline int faustpower<2>(int x)            { return x*x; }
template <int N> inline float faustpower(float x)            { return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline float faustpower<0>(float x)          { return 1; }
template <> 	 inline float faustpower<1>(float x)          { return x; }
template <> 	 inline float faustpower<2>(float x)          { return x*x; }
#endif

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


#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

class mydsp : public dsp {
  private:
	FAUSTFLOAT 	fslider0;
	float 	fRec0[2];
	int 	iTempPerm0;
	int 	iRec1[2];
	float 	fTempPerm1;
	float 	fRec3[2];
	float 	fTempPerm2;
	float 	fTempPerm3;
	float 	fTempPerm4;
	float 	fTempPerm5;
	float 	fConst0;
	float 	fTempPerm6;
	float 	fTempPerm7;
	float 	fTempPerm8;
	float 	fTempPerm9;
	float 	fTempPerm10;
	float 	fTempPerm11;
	float 	fTempPerm12;
	float 	fTempPerm13;
	float 	fTempPerm14;
	float 	fTempPerm15;
	float 	fTempPerm16;
	float 	fTempPerm17;
	float 	fTempPerm18;
	float 	fTempPerm19;
	float 	fTempPerm20;
	float 	fRec6[2];
	float 	fRec4[2];
	float 	fTempPerm21;
	float 	fTempPerm22;
	float 	fTempPerm23;
	float 	fTempPerm24;
	float 	fTempPerm25;
	float 	fTempPerm26;
	float 	fTempPerm27;
	float 	fTempPerm28;
	float 	fTempPerm29;
	float 	fTempPerm30;
	float 	fTempPerm31;
	float 	fTempPerm32;
	float 	fTempPerm33;
	float 	fTempPerm34;
	float 	fTempPerm35;
	float 	fTempPerm36;
	float 	fTempPerm37;
	float 	fTempPerm38;
	float 	fTempPerm39;
	float 	fRec9[2];
	float 	fRec7[2];
	float 	fTempPerm40;
	float 	fTempPerm41;
	float 	fTempPerm42;
	float 	fTempPerm43;
	float 	fTempPerm44;
	float 	fTempPerm45;
	float 	fRec12[2];
	float 	fRec10[2];
	float 	fTempPerm46;
	float 	fTempPerm47;
	float 	fRec15[2];
	float 	fRec13[2];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "wind");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("vaeffects.lib/name", "Faust Virtual Analog Filter Effect Library");
		m->declare("vaeffects.lib/version", "0.0");
	}

	virtual int getNumInputs() { return 0; }
	virtual int getNumOutputs() { return 2; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		iTempPerm0 = 0;
		fTempPerm1 = 0;
		fTempPerm2 = 0;
		fTempPerm3 = 0;
		fTempPerm4 = 0;
		fTempPerm5 = 0;
		fConst0 = (3.1415926535897931f / min(192000.0f, max(1.0f, (float)fSamplingFreq)));
		fTempPerm6 = 0;
		fTempPerm7 = 0;
		fTempPerm8 = 0;
		fTempPerm9 = 0;
		fTempPerm10 = 0;
		fTempPerm11 = 0;
		fTempPerm12 = 0;
		fTempPerm13 = 0;
		fTempPerm14 = 0;
		fTempPerm15 = 0;
		fTempPerm16 = 0;
		fTempPerm17 = 0;
		fTempPerm18 = 0;
		fTempPerm19 = 0;
		fTempPerm20 = 0;
		fTempPerm21 = 0;
		fTempPerm22 = 0;
		fTempPerm23 = 0;
		fTempPerm24 = 0;
		fTempPerm25 = 0;
		fTempPerm26 = 0;
		fTempPerm27 = 0;
		fTempPerm28 = 0;
		fTempPerm29 = 0;
		fTempPerm30 = 0;
		fTempPerm31 = 0;
		fTempPerm32 = 0;
		fTempPerm33 = 0;
		fTempPerm34 = 0;
		fTempPerm35 = 0;
		fTempPerm36 = 0;
		fTempPerm37 = 0;
		fTempPerm38 = 0;
		fTempPerm39 = 0;
		fTempPerm40 = 0;
		fTempPerm41 = 0;
		fTempPerm42 = 0;
		fTempPerm43 = 0;
		fTempPerm44 = 0;
		fTempPerm45 = 0;
		fTempPerm46 = 0;
		fTempPerm47 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.66000000000000003f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) iRec1[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2; i++) fRec9[i] = 0;
		for (int i=0; i<2; i++) fRec7[i] = 0;
		for (int i=0; i<2; i++) fRec12[i] = 0;
		for (int i=0; i<2; i++) fRec10[i] = 0;
		for (int i=0; i<2; i++) fRec15[i] = 0;
		for (int i=0; i<2; i++) fRec13[i] = 0;
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
		ui_interface->openVerticalBox("wind");
		ui_interface->addHorizontalSlider("force", &fslider0, 0.66000000000000003f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = (0.0030000000000000027f * float(fslider0));
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fRec0[0] = (fSlow0 + (0.997f * fRec0[1]));
			iTempPerm0 = (1103515245 * (iRec1[1] + 12345));
			iRec1[0] = (1103515245 * (iTempPerm0 + 12345));
			int 	iRec2 = iTempPerm0;
			fTempPerm1 = float((4.6566128752457969e-10f * iRec1[0]));
			fRec3[0] = (fSlow0 + (0.997f * fRec3[1]));
			fTempPerm2 = faustpower<2>((1.4141994202374715f * fRec3[0]));
			fTempPerm3 = (1.9999800000000003f * fRec3[0]);
			fTempPerm4 = (fTempPerm2 + fTempPerm3);
			fTempPerm5 = (fTempPerm3 + 2);
			fTempPerm6 = tanf((fConst0 * max((440.0f * powf(2.0f,(0.083333333333333329f * ((87 * fRec3[0]) + -48.0f)))), (float)20)));
			fTempPerm7 = (1.0f / fTempPerm6);
			fTempPerm8 = ((fTempPerm4 + ((fTempPerm5 + fTempPerm7) / fTempPerm6)) + 1);
			fTempPerm9 = ((fTempPerm4 + (1 - ((fTempPerm5 - fTempPerm7) / fTempPerm6))) / fTempPerm8);
			fTempPerm10 = max(-0.99990000000000001f, min(0.99990000000000001f, fTempPerm9));
			fTempPerm11 = (0 - fTempPerm10);
			fTempPerm12 = (1 - faustpower<2>(fTempPerm10));
			fTempPerm13 = sqrtf(max((float)0, fTempPerm12));
			fTempPerm14 = ((fRec4[1] * fTempPerm11) + (fTempPerm1 * fTempPerm13));
			fTempPerm15 = (1.0f / faustpower<2>(fTempPerm6));
			fTempPerm16 = (fTempPerm4 + (1 - fTempPerm15));
			fTempPerm17 = max(-0.99990000000000001f, min(0.99990000000000001f, (2 * (fTempPerm16 / (fTempPerm8 * (fTempPerm9 + 1))))));
			fTempPerm18 = (0 - fTempPerm17);
			fTempPerm19 = (1 - faustpower<2>(fTempPerm17));
			fTempPerm20 = sqrtf(max((float)0, fTempPerm19));
			fRec6[0] = ((fRec6[1] * fTempPerm18) + (fTempPerm14 * fTempPerm20));
			fRec4[0] = ((fTempPerm14 * fTempPerm17) + (fRec6[1] * fTempPerm20));
			float 	fRec5 = fRec6[0];
			fTempPerm21 = (1.0f - (fTempPerm16 / fTempPerm8));
			fTempPerm22 = sqrtf(fTempPerm12);
			fTempPerm23 = ((1.0f - fTempPerm9) - (2.0f * (fTempPerm17 * fTempPerm21)));
			fTempPerm24 = (fTempPerm22 * sqrtf(fTempPerm19));
			fTempPerm25 = ((((fTempPerm1 * fTempPerm10) + (fRec4[1] * fTempPerm13)) + (2.0f * ((fRec4[0] * fTempPerm21) / fTempPerm22))) + ((fRec5 * fTempPerm23) / fTempPerm24));
			fTempPerm26 = (2 - fTempPerm3);
			fTempPerm27 = (1 - fTempPerm3);
			fTempPerm28 = ((fTempPerm2 + ((fTempPerm7 + fTempPerm26) / fTempPerm6)) + fTempPerm27);
			fTempPerm29 = (((fTempPerm2 + ((fTempPerm7 - fTempPerm26) / fTempPerm6)) + fTempPerm27) / fTempPerm28);
			fTempPerm30 = max(-0.99990000000000001f, min(0.99990000000000001f, fTempPerm29));
			fTempPerm31 = (0 - fTempPerm30);
			fTempPerm32 = (1 - faustpower<2>(fTempPerm30));
			fTempPerm33 = sqrtf(max((float)0, fTempPerm32));
			fTempPerm34 = ((fRec7[1] * fTempPerm31) + ((fTempPerm25 * fTempPerm33) / fTempPerm8));
			fTempPerm35 = (fTempPerm2 + (1 - (fTempPerm3 + fTempPerm15)));
			fTempPerm36 = max(-0.99990000000000001f, min(0.99990000000000001f, (2 * (fTempPerm35 / (fTempPerm28 * (fTempPerm29 + 1))))));
			fTempPerm37 = (0 - fTempPerm36);
			fTempPerm38 = (1 - faustpower<2>(fTempPerm36));
			fTempPerm39 = sqrtf(max((float)0, fTempPerm38));
			fRec9[0] = ((fRec9[1] * fTempPerm37) + (fTempPerm34 * fTempPerm39));
			fRec7[0] = ((fTempPerm34 * fTempPerm36) + (fRec9[1] * fTempPerm39));
			float 	fRec8 = fRec9[0];
			fTempPerm40 = (1.0f - (fTempPerm35 / fTempPerm28));
			fTempPerm41 = sqrtf(fTempPerm32);
			fTempPerm42 = ((1.0f - fTempPerm29) - (2.0f * (fTempPerm36 * fTempPerm40)));
			fTempPerm43 = (fTempPerm41 * sqrtf(fTempPerm38));
			output0[i] = (FAUSTFLOAT)((fRec0[0] * (((((fTempPerm25 * fTempPerm30) / fTempPerm8) + (fRec7[1] * fTempPerm33)) + (2.0f * ((fRec7[0] * fTempPerm40) / fTempPerm41))) + ((fRec8 * fTempPerm42) / fTempPerm43))) / fTempPerm28);
			fTempPerm44 = float((4.6566128752457969e-10f * iRec2));
			fTempPerm45 = ((fTempPerm11 * fRec10[1]) + (fTempPerm13 * fTempPerm44));
			fRec12[0] = ((fTempPerm18 * fRec12[1]) + (fTempPerm20 * fTempPerm45));
			fRec10[0] = ((fTempPerm17 * fTempPerm45) + (fTempPerm20 * fRec12[1]));
			float 	fRec11 = fRec12[0];
			fTempPerm46 = ((((fTempPerm10 * fTempPerm44) + (fTempPerm13 * fRec10[1])) + (2.0f * ((fRec10[0] * fTempPerm21) / fTempPerm22))) + ((fRec11 * fTempPerm23) / fTempPerm24));
			fTempPerm47 = ((fTempPerm31 * fRec13[1]) + ((fTempPerm33 * fTempPerm46) / fTempPerm8));
			fRec15[0] = ((fTempPerm37 * fRec15[1]) + (fTempPerm39 * fTempPerm47));
			fRec13[0] = ((fTempPerm36 * fTempPerm47) + (fTempPerm39 * fRec15[1]));
			float 	fRec14 = fRec15[0];
			output1[i] = (FAUSTFLOAT)((fRec0[0] * (((((fTempPerm30 * fTempPerm46) / fTempPerm8) + (fTempPerm33 * fRec13[1])) + (2.0f * ((fRec13[0] * fTempPerm40) / fTempPerm41))) + ((fRec14 * fTempPerm42) / fTempPerm43))) / fTempPerm28);
			// post processing
			fRec13[1] = fRec13[0];
			fRec15[1] = fRec15[0];
			fRec10[1] = fRec10[0];
			fRec12[1] = fRec12[0];
			fRec7[1] = fRec7[0];
			fRec9[1] = fRec9[0];
			fRec4[1] = fRec4[0];
			fRec6[1] = fRec6[0];
			fRec3[1] = fRec3[0];
			iRec1[1] = iRec1[0];
			fRec0[1] = fRec0[0];
		}
	}
};


