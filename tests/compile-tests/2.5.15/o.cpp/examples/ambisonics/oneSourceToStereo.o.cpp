//----------------------------------------------------------
// author: "CICM"
// copyright: "(c)CICM 2013"
// license: "BSD"
// name: "oneSourceToStereo"
// version: "1.0"
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
	float 	fConst0;
	float 	fConst1;
	FAUSTFLOAT 	fslider0;
	float 	fRec0[2];
	int 	iTempPerm0;
	int 	iTempPerm1;
	float 	fTempPerm2;
	float 	fTempPerm3;
	float 	fTempPerm4;
	float 	fTempPerm5;
	FAUSTFLOAT 	fslider1;
	float 	fRec1[2];
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
	float 	fTempPerm40;
	float 	fTempPerm41;
	float 	fTempPerm42;
	float 	fTempPerm43;
	float 	fTempPerm44;
	float 	fTempPerm45;
	float 	fTempPerm46;
	float 	fTempPerm47;
	float 	fTempPerm48;
	float 	fTempPerm49;
	float 	fTempPerm50;
	float 	fTempPerm51;
	float 	fTempPerm52;
	float 	fTempPerm53;
	float 	fTempPerm54;
	float 	fTempPerm55;
	float 	fTempPerm56;
	float 	fTempPerm57;
	float 	fTempPerm58;
	float 	fTempPerm59;
	float 	fTempPerm60;
	float 	fTempPerm61;
	float 	fTempPerm62;
	float 	fTempPerm63;
	float 	fTempPerm64;
	float 	fTempPerm65;
	float 	fTempPerm66;
	float 	fTempPerm67;
	float 	fTempPerm68;
	float 	fTempPerm69;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("author", "CICM");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("copyright", "(c)CICM 2013");
		m->declare("hoa.lib/author", "Pierre Guillot");
		m->declare("hoa.lib/copyright", "2012-2013 Guillot, Paris, Colafrancesco, CICM labex art H2H, U. Paris 8");
		m->declare("hoa.lib/name", "High Order Ambisonics library");
		m->declare("license", "BSD");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "oneSourceToStereo");
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() { return 1; }
	virtual int getNumOutputs() { return 2; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = expf((0 - (50.0f / min(192000.0f, max(1.0f, (float)fSamplingFreq)))));
		fConst1 = (1.0f - fConst0);
		iTempPerm0 = 0;
		iTempPerm1 = 0;
		fTempPerm2 = 0;
		fTempPerm3 = 0;
		fTempPerm4 = 0;
		fTempPerm5 = 0;
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
		fTempPerm48 = 0;
		fTempPerm49 = 0;
		fTempPerm50 = 0;
		fTempPerm51 = 0;
		fTempPerm52 = 0;
		fTempPerm53 = 0;
		fTempPerm54 = 0;
		fTempPerm55 = 0;
		fTempPerm56 = 0;
		fTempPerm57 = 0;
		fTempPerm58 = 0;
		fTempPerm59 = 0;
		fTempPerm60 = 0;
		fTempPerm61 = 0;
		fTempPerm62 = 0;
		fTempPerm63 = 0;
		fTempPerm64 = 0;
		fTempPerm65 = 0;
		fTempPerm66 = 0;
		fTempPerm67 = 0;
		fTempPerm68 = 0;
		fTempPerm69 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 1.0f;
		fslider1 = 0.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
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
		ui_interface->openVerticalBox("oneSourceToStereo");
		ui_interface->addHorizontalSlider("Angle", &fslider1, 0.0f, -6.2831853071795862f, 6.2831853071795862f, 0.001f);
		ui_interface->addHorizontalSlider("Radius", &fslider0, 1.0f, 0.0f, 5.0f, 0.001f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = (fConst1 * float(fslider0));
		float 	fSlow1 = (fConst1 * float(fslider1));
		//zone2b
		//zone3
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fRec0[0] = (fSlow0 + (fConst0 * fRec0[1]));
			iTempPerm0 = (fRec0[0] > 1);
			iTempPerm1 = (fRec0[0] < 1);
			fTempPerm2 = (iTempPerm0 + (fRec0[0] * iTempPerm1));
			fTempPerm3 = ((float)input0[i] * ((2.0794415416798357f * (1 - fTempPerm2)) + 1));
			fTempPerm4 = (3.0f * fTempPerm2);
			fTempPerm5 = ((3.0f * ((fTempPerm2 * (fTempPerm4 > 0)) * (fTempPerm4 <= 1))) + (fTempPerm4 > 1));
			fRec1[0] = (fSlow1 + (fConst0 * fRec1[1]));
			fTempPerm6 = (fTempPerm5 * cosf(fRec1[0]));
			fTempPerm7 = (2 * fRec1[0]);
			fTempPerm8 = (2.0794415416798357f * fTempPerm2);
			fTempPerm9 = (fTempPerm8 + -0.69314718055994529f);
			fTempPerm10 = (2.4663034623764308f * fTempPerm9);
			fTempPerm11 = ((2.4663034623764308f * ((fTempPerm9 * (fTempPerm10 > 0)) * (fTempPerm10 <= 1))) + (fTempPerm10 > 1));
			fTempPerm12 = (cosf(fTempPerm7) * fTempPerm11);
			fTempPerm13 = (0.077777777777777779f * fTempPerm12);
			fTempPerm14 = (3 * fRec1[0]);
			fTempPerm15 = (fTempPerm8 + -1.0986122886681098f);
			fTempPerm16 = (3.4760594967822085f * fTempPerm15);
			fTempPerm17 = ((3.4760594967822085f * ((fTempPerm15 * (fTempPerm16 > 0)) * (fTempPerm16 <= 1))) + (fTempPerm16 > 1));
			fTempPerm18 = (cosf(fTempPerm14) * fTempPerm17);
			fTempPerm19 = (4 * fRec1[0]);
			fTempPerm20 = (fTempPerm8 + -1.3862943611198906f);
			fTempPerm21 = (4.481420117724551f * fTempPerm20);
			fTempPerm22 = ((4.481420117724551f * ((fTempPerm20 * (fTempPerm21 > 0)) * (fTempPerm21 <= 1))) + (fTempPerm21 > 1));
			fTempPerm23 = (0.014141414141414142f * (cosf(fTempPerm19) * fTempPerm22));
			fTempPerm24 = (5 * fRec1[0]);
			fTempPerm25 = (fTempPerm8 + -1.6094379124341003f);
			fTempPerm26 = (5.4848149477470756f * fTempPerm25);
			fTempPerm27 = ((5.4848149477470756f * ((fTempPerm25 * (fTempPerm26 > 0)) * (fTempPerm26 <= 1))) + (fTempPerm26 > 1));
			fTempPerm28 = (cosf(fTempPerm24) * fTempPerm27);
			fTempPerm29 = (6 * fRec1[0]);
			fTempPerm30 = (fTempPerm8 + -1.791759469228055f);
			fTempPerm31 = (6.487159194630884f * fTempPerm30);
			fTempPerm32 = ((6.487159194630884f * ((fTempPerm30 * (fTempPerm31 > 0)) * (fTempPerm31 <= 1))) + (fTempPerm31 > 1));
			fTempPerm33 = (cosf(fTempPerm29) * fTempPerm32);
			fTempPerm34 = (0.0017529949315523716f * fTempPerm33);
			fTempPerm35 = (7 * fRec1[0]);
			fTempPerm36 = (fTempPerm8 + -1.9459101490553132f);
			fTempPerm37 = (7.4888756894186237f * fTempPerm36);
			fTempPerm38 = ((7.4888756894186237f * ((fTempPerm36 * (fTempPerm37 > 0)) * (fTempPerm37 <= 1))) + (fTempPerm37 > 1));
			fTempPerm39 = (cosf(fTempPerm35) * fTempPerm38);
			fTempPerm40 = (0.70710678118654746f * ((((((((0.11666666666666667f * fTempPerm6) + 0.066666666666666666f) + fTempPerm13) + (0.03888888888888889f * fTempPerm18)) + fTempPerm23) + (0.0035353535353535356f * fTempPerm28)) + fTempPerm34) + (0.0026481821020520905f * fTempPerm39)));
			fTempPerm41 = (0.014141414141414142f * (sinf(fTempPerm19) * fTempPerm22));
			fTempPerm42 = (sinf(fRec1[0]) * fTempPerm5);
			fTempPerm43 = (0.10778594545965012f * fTempPerm6);
			fTempPerm44 = (sinf(fTempPerm7) * fTempPerm11);
			fTempPerm45 = (0.054997194092287024f * fTempPerm44);
			fTempPerm46 = (0.054997194092287031f * fTempPerm12);
			fTempPerm47 = (sinf(fTempPerm14) * fTempPerm17);
			fTempPerm48 = (sinf(fTempPerm24) * fTempPerm27);
			fTempPerm49 = (sinf(fTempPerm29) * fTempPerm32);
			fTempPerm50 = (0.0012395546034863296f * fTempPerm49);
			fTempPerm51 = (0.0012395546034863296f * fTempPerm33);
			fTempPerm52 = (sinf(fTempPerm35) * fTempPerm38);
			fTempPerm53 = (((((((fTempPerm41 + (((((((0.044646400442593805f * fTempPerm42) + 0.066666666666666666f) + fTempPerm43) + fTempPerm45) + fTempPerm46) + (0.035928648486550044f * fTempPerm47)) + (0.014882133480864604f * fTempPerm18))) + (0.0032662407715045492f * fTempPerm48)) - (0.0013529212255331455f * fTempPerm28)) + fTempPerm50) - fTempPerm51) + (0.0010134154163410926f * fTempPerm52)) - (0.0024466012424486424f * fTempPerm39));
			fTempPerm54 = (0.08249579113843053f * fTempPerm42);
			fTempPerm55 = (0.077777777777777779f * fTempPerm44);
			fTempPerm56 = (0.0017529949315523716f * fTempPerm49);
			fTempPerm57 = ((0.10778594545965012f * fTempPerm42) + 0.066666666666666666f);
			fTempPerm58 = (0.054997194092287024f * fTempPerm12);
			fTempPerm59 = (0.11666666666666667f * fTempPerm42);
			fTempPerm60 = (0.03888888888888889f * fTempPerm47);
			fTempPerm61 = (0.0035353535353535356f * fTempPerm48);
			fTempPerm62 = (0.0026481821020520905f * fTempPerm52);
			fTempPerm63 = (0.08249579113843053f * fTempPerm6);
			fTempPerm64 = (0.035928648486550037f * fTempPerm47);
			fTempPerm65 = (0.0032662407715045483f * fTempPerm48);
			fTempPerm66 = (((((((((0.014882133480864486f * fTempPerm18) + (((((0.066666666666666666f - (0.044646400442593881f * fTempPerm42)) + (0.10778594545965009f * fTempPerm6)) - (0.054997194092287101f * fTempPerm44)) + (0.054997194092286969f * fTempPerm12)) - (0.035928648486550092f * fTempPerm47))) - fTempPerm41) - fTempPerm65) - (0.0013529212255331477f * fTempPerm28)) - (0.0012395546034863218f * fTempPerm49)) - (0.0012395546034863376f * fTempPerm33)) - (0.0010134154163410803f * fTempPerm52)) - (0.0024466012424486472f * fTempPerm39));
			fTempPerm67 = (iTempPerm1 + (faustpower<2>(fRec0[0]) * iTempPerm0));
			output0[i] = (FAUSTFLOAT)((fTempPerm3 * ((((((((fTempPerm40 + (0.98078528040323043f * fTempPerm53)) + (0.98768834059513766f * ((0.0018725475221778789f * fTempPerm39) + ((((((((((fTempPerm54 + 0.066666666666666666f) + (0.082495791138430544f * fTempPerm6)) + fTempPerm55) + (0.027498597046143516f * fTempPerm47)) - (0.027498597046143512f * fTempPerm18)) - fTempPerm23) - (0.0024998724587403194f * fTempPerm48)) - (0.0024998724587403202f * fTempPerm28)) - fTempPerm56) - (0.0018725475221778797f * fTempPerm52))))) + (0.92387953251128674f * (((fTempPerm51 + (fTempPerm50 + ((((((((fTempPerm57 + (0.044646400442593812f * fTempPerm6)) + (0.054997194092287031f * fTempPerm44)) - fTempPerm58) - (0.014882133480864599f * fTempPerm47)) - (0.035928648486550044f * fTempPerm18)) - fTempPerm41) - (0.0013529212255331479f * fTempPerm48)) + (0.0032662407715045483f * fTempPerm28)))) + (0.002446601242448642f * fTempPerm52)) - (0.0010134154163410935f * fTempPerm39)))) + (0.80901699437494745f * ((((fTempPerm23 + (((fTempPerm59 + 0.066666666666666666f) - fTempPerm13) - fTempPerm60)) + fTempPerm61) - fTempPerm34) - fTempPerm62))) + (0.64944804833018377f * (((((((fTempPerm41 + (((((fTempPerm57 - (0.044646400442593798f * fTempPerm6)) - fTempPerm45) - (0.054997194092287052f * fTempPerm12)) - (0.014882133480864626f * fTempPerm47)) + (0.035928648486550037f * fTempPerm18))) - (0.0013529212255331468f * fTempPerm48)) - (0.0032662407715045487f * fTempPerm28)) - (0.0012395546034863311f * fTempPerm49)) + (0.0012395546034863283f * fTempPerm33)) + (0.0024466012424486415f * fTempPerm52)) + (0.0010134154163410937f * fTempPerm39)))) + (0.45399049973954686f * (((fTempPerm56 + ((((((0.027498597046143512f * fTempPerm47) + ((((0.082495791138430544f * fTempPerm42) + 0.066666666666666666f) - fTempPerm63) - fTempPerm55)) + (0.027498597046143516f * fTempPerm18)) - fTempPerm23) - (0.0024998724587403224f * fTempPerm48)) + (0.0024998724587403168f * fTempPerm28))) - (0.0018725475221778806f * fTempPerm52)) - (0.0018725475221778778f * fTempPerm39)))) + (0.2334453638559055f * ((((((((((fTempPerm58 + ((((0.044646400442593812f * fTempPerm42) + 0.066666666666666666f) - fTempPerm43) - (0.054997194092287052f * fTempPerm44))) + fTempPerm64) - (0.014882133480864616f * fTempPerm18)) - fTempPerm41) + fTempPerm65) + (0.0013529212255331473f * fTempPerm28)) - (0.0012395546034863307f * fTempPerm49)) - (0.0012395546034863288f * fTempPerm33)) + (0.0010134154163410891f * fTempPerm52)) + (0.0024466012424486437f * fTempPerm39)))) + (0.19509032201612825f * fTempPerm66))) / fTempPerm67);
			fTempPerm68 = (0.002499872458740322f * fTempPerm48);
			fTempPerm69 = (0.0032662407715045457f * fTempPerm28);
			output1[i] = (FAUSTFLOAT)((fTempPerm3 * ((((((((fTempPerm40 + (0.19509032201612825f * fTempPerm53)) + (0.23344536385590539f * (((((((fTempPerm41 + (((fTempPerm46 + (fTempPerm45 + ((0.066666666666666666f - (0.044646400442593791f * fTempPerm42)) - fTempPerm43))) - fTempPerm64) - (0.014882133480864625f * fTempPerm18))) - (0.0032662407715045487f * fTempPerm48)) + (0.0013529212255331466f * fTempPerm28)) + (0.0012395546034863309f * fTempPerm49)) - (0.0012395546034863285f * fTempPerm33)) - (0.0010134154163410898f * fTempPerm52)) + (0.0024466012424486433f * fTempPerm39)))) + (0.45399049973954675f * (((((((((fTempPerm55 + ((0.066666666666666666f - fTempPerm54) - (0.082495791138430571f * fTempPerm6))) - (0.02749859704614355f * fTempPerm47)) + (0.027498597046143484f * fTempPerm18)) - fTempPerm23) + fTempPerm68) + (0.0024998724587403176f * fTempPerm28)) - fTempPerm56) + (0.001872547522177881f * fTempPerm52)) - (0.0018725475221778771f * fTempPerm39)))) + (0.64944804833018366f * ((((((((((((0.054997194092287087f * fTempPerm44) + ((0.066666666666666666f - (0.10778594545965009f * fTempPerm42)) - (0.044646400442593874f * fTempPerm6))) - (0.054997194092286976f * fTempPerm12)) + (0.014882133480864554f * fTempPerm47)) + (0.035928648486550065f * fTempPerm18)) - fTempPerm41) + (0.0013529212255331531f * fTempPerm48)) - fTempPerm69) + (0.0012395546034863264f * fTempPerm49)) + (0.0012395546034863331f * fTempPerm33)) - (0.0024466012424486459f * fTempPerm52)) + (0.0010134154163410844f * fTempPerm39)))) + (0.80901699437494734f * (fTempPerm62 + (((fTempPerm23 + (fTempPerm60 + ((0.066666666666666666f - fTempPerm59) - fTempPerm13))) - fTempPerm61) - fTempPerm34)))) + (0.92387953251128674f * (((((fTempPerm69 + ((fTempPerm41 + ((((((0.066666666666666666f - (0.1077859454596501f * fTempPerm42)) + (0.044646400442593832f * fTempPerm6)) - (0.054997194092287073f * fTempPerm44)) - (0.05499719409228699f * fTempPerm12)) + (0.014882133480864559f * fTempPerm47)) - (0.035928648486550058f * fTempPerm18))) + (0.0013529212255331529f * fTempPerm48))) - (0.0012395546034863266f * fTempPerm49)) + (0.0012395546034863327f * fTempPerm33)) - (0.0024466012424486489f * fTempPerm52)) - (0.0010134154163410766f * fTempPerm39)))) + (0.98768834059513777f * (((fTempPerm56 + ((fTempPerm68 + (((((fTempPerm63 + (0.066666666666666666f - (0.082495791138430571f * fTempPerm42))) - fTempPerm55) - (0.027498597046143537f * fTempPerm47)) - (0.027498597046143495f * fTempPerm18)) - fTempPerm23)) - (0.0024998724587403172f * fTempPerm28))) + (0.0018725475221778741f * fTempPerm52)) + (0.0018725475221778843f * fTempPerm39)))) + (0.98078528040323043f * fTempPerm66))) / fTempPerm67);
			// post processing
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
		}
	}
};


