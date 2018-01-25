/* ------------------------------------------------------------
copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
license: "MIT"
name: "Vocal BandPass"
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
	int iVec0[2];
	FAUSTFLOAT fHslider1;
	float fRec1[2];
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	float fConst2;
	FAUSTFLOAT fHslider4;
	float fRec4[2];
	float fRec5[2];
	float fRec2[2];
	int iRec6[2];
	float fConst3;
	FAUSTFLOAT fHslider5;
	FAUSTFLOAT fHslider6;
	float fRec7[2];
	float fRec8[2];
	float fRec9[2];
	float fRec0[3];
	float fRec10[3];
	float fRec11[3];
	float fRec12[3];
	float fRec13[3];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
		m->declare("description", "Simple source-filter vocal synthesizer.");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("license", "MIT");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "Vocal BandPass");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
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
		fConst1 = (1.0f / fConst0);
		fConst2 = (6.28318548f / fConst0);
		fConst3 = (3.14159274f / fConst0);
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.90000000000000002f);
		fHslider1 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(440.0f);
		fHslider3 = FAUSTFLOAT(0.5f);
		fHslider4 = FAUSTFLOAT(6.0f);
		fHslider5 = FAUSTFLOAT(0.0f);
		fHslider6 = FAUSTFLOAT(0.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec1[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec4[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec5[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec2[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			iRec6[l5] = 0;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec7[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec8[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec9[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) {
			fRec0[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 3); l10 = (l10 + 1)) {
			fRec10[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 3); l11 = (l11 + 1)) {
			fRec11[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 3); l12 = (l12 + 1)) {
			fRec12[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 3); l13 = (l13 + 1)) {
			fRec13[l13] = 0.0f;
			
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
		ui_interface->openVerticalBox("vocal");
		ui_interface->declare(&fHslider2, "0", "");
		ui_interface->addHorizontalSlider("freq", &fHslider2, 440.0f, 50.0f, 1000.0f, 0.00999999978f);
		ui_interface->declare(&fHslider0, "1", "");
		ui_interface->addHorizontalSlider("gain", &fHslider0, 0.899999976f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fHslider5, "2", "");
		ui_interface->addHorizontalSlider("voiceType", &fHslider5, 0.0f, 0.0f, 4.0f, 1.0f);
		ui_interface->declare(&fHslider6, "3", "");
		ui_interface->addHorizontalSlider("vowel", &fHslider6, 0.0f, 0.0f, 4.0f, 0.00999999978f);
		ui_interface->declare(&fHslider1, "4", "");
		ui_interface->addHorizontalSlider("fricative", &fHslider1, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fHslider4, "5", "");
		ui_interface->addHorizontalSlider("vibratoFreq", &fHslider4, 6.0f, 1.0f, 10.0f, 0.00999999978f);
		ui_interface->declare(&fHslider3, "6", "");
		ui_interface->addHorizontalSlider("vibratoGain", &fHslider3, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = float(fHslider0);
		float fSlow1 = (0.00100000005f * float(fHslider1));
		float fSlow2 = float(fHslider2);
		float fSlow3 = (0.100000001f * float(fHslider3));
		float fSlow4 = (fConst2 * float(fHslider4));
		float fSlow5 = sinf(fSlow4);
		float fSlow6 = cosf(fSlow4);
		float fSlow7 = (0.0f - fSlow5);
		float fSlow8 = float(fHslider5);
		float fSlow9 = (5.0f * fSlow8);
		float fSlow10 = (0.00100000005f * float(fHslider6));
		float fSlow11 = (5.0f * (1.0f - fSlow8));
		int iSlow12 = (((fSlow8 == 0.0f)?1:((fSlow8 == 3.0f)?1:0)) == 0);
		int iSlow13 = (fSlow8 != 2.0f);
		float fSlow14 = (2.0f * fSlow2);
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			fRec1[0] = (fSlow1 + (0.999000013f * fRec1[1]));
			fRec4[0] = ((fSlow5 * fRec5[1]) + (fSlow6 * fRec4[1]));
			int iTemp0 = (1 - iVec0[1]);
			fRec5[0] = (((fSlow6 * fRec5[1]) + (fSlow7 * fRec4[1])) + float(iTemp0));
			float fTemp1 = max(1.00000001e-07f, fabsf((fSlow2 * ((fSlow3 * fRec4[0]) + 1.0f))));
			float fTemp2 = (fRec2[1] + (fConst1 * fTemp1));
			float fTemp3 = (fTemp2 + -1.0f);
			int iTemp4 = (fTemp3 < 0.0f);
			fRec2[0] = (iTemp4?fTemp2:fTemp3);
			float fRec3 = (iTemp4?fTemp2:(fTemp2 + (fTemp3 * (1.0f - (fConst0 / fTemp1)))));
			iRec6[0] = ((1103515245 * iRec6[1]) + 12345);
			float fTemp5 = (fSlow0 * (((1.0f - fRec1[0]) * ((2.0f * fRec3) + -1.0f)) + (4.65661287e-10f * (fRec1[0] * float(iRec6[0])))));
			fRec7[0] = (fSlow10 + (0.999000013f * fRec7[1]));
			float fTemp6 = (fSlow9 + fRec7[0]);
			int iTemp7 = (fTemp6 < 23.0f);
			int iTemp8 = (fTemp6 < 24.0f);
			float fTemp9 = (fSlow9 + (fRec7[0] + -23.0f));
			int iTemp10 = (fTemp6 < 22.0f);
			float fTemp11 = (fSlow9 + (fRec7[0] + -22.0f));
			int iTemp12 = (fTemp6 < 21.0f);
			float fTemp13 = (fSlow9 + (fRec7[0] + -21.0f));
			int iTemp14 = (fTemp6 < 20.0f);
			float fTemp15 = (fSlow9 + (fRec7[0] + -20.0f));
			int iTemp16 = (fTemp6 < 19.0f);
			float fTemp17 = (fSlow9 + (fRec7[0] + -19.0f));
			int iTemp18 = (fTemp6 < 18.0f);
			float fTemp19 = (fSlow9 + (fRec7[0] + -18.0f));
			int iTemp20 = (fTemp6 < 17.0f);
			float fTemp21 = (fSlow9 + (fRec7[0] + -17.0f));
			int iTemp22 = (fTemp6 < 16.0f);
			float fTemp23 = (fSlow9 + (fRec7[0] + -16.0f));
			float fTemp24 = (80.0f * fTemp23);
			int iTemp25 = (fTemp6 < 15.0f);
			float fTemp26 = (fSlow9 + (fRec7[0] + -15.0f));
			int iTemp27 = (fTemp6 < 14.0f);
			float fTemp28 = (fSlow9 + (fRec7[0] + -14.0f));
			int iTemp29 = (fTemp6 < 13.0f);
			float fTemp30 = (fSlow9 + (fRec7[0] + -13.0f));
			int iTemp31 = (fTemp6 < 12.0f);
			float fTemp32 = (fSlow9 + (fRec7[0] + -12.0f));
			int iTemp33 = (fTemp6 < 11.0f);
			float fTemp34 = (fSlow9 + (fRec7[0] + -11.0f));
			int iTemp35 = (fTemp6 < 10.0f);
			float fTemp36 = (fSlow9 + (fRec7[0] + -10.0f));
			int iTemp37 = (fTemp6 < 9.0f);
			float fTemp38 = (fSlow9 + (fRec7[0] + -9.0f));
			int iTemp39 = (fTemp6 < 8.0f);
			float fTemp40 = (fSlow9 + (fRec7[0] + -8.0f));
			float fTemp41 = (50.0f * fTemp40);
			int iTemp42 = (fTemp6 < 7.0f);
			float fTemp43 = (fSlow9 + (fRec7[0] + -7.0f));
			int iTemp44 = (fTemp6 < 6.0f);
			float fTemp45 = (fSlow9 + (fRec7[0] + -6.0f));
			int iTemp46 = (fTemp6 < 5.0f);
			float fTemp47 = (fRec7[0] - fSlow11);
			int iTemp48 = (fTemp6 < 4.0f);
			float fTemp49 = (fSlow9 + (fRec7[0] + -4.0f));
			int iTemp50 = (fTemp6 < 3.0f);
			float fTemp51 = (fSlow9 + (fRec7[0] + -3.0f));
			int iTemp52 = (fTemp6 < 2.0f);
			float fTemp53 = (fSlow9 + (fRec7[0] + -2.0f));
			int iTemp54 = (fTemp6 < 1.0f);
			float fTemp55 = (fSlow9 + (fRec7[0] + -1.0f));
			int iTemp56 = (fTemp6 < 0.0f);
			float fTemp57 = (iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp48?(iTemp50?(iTemp52?(iTemp54?(iTemp56?800.0f:(iTemp54?(800.0f - (400.0f * fTemp6)):400.0f)):(iTemp52?(400.0f - (50.0f * fTemp55)):350.0f)):(iTemp50?((100.0f * fTemp53) + 350.0f):450.0f)):(iTemp48?(450.0f - (125.0f * fTemp51)):325.0f)):(iTemp46?((275.0f * fTemp49) + 325.0f):600.0f)):(iTemp44?(600.0f - (200.0f * fTemp47)):400.0f)):(iTemp42?(400.0f - (150.0f * fTemp45)):250.0f)):(iTemp39?((150.0f * fTemp43) + 250.0f):400.0f)):(iTemp37?(400.0f - fTemp41):350.0f)):(iTemp35?((310.0f * fTemp38) + 350.0f):660.0f)):(iTemp33?(660.0f - (220.0f * fTemp36)):440.0f)):(iTemp31?(440.0f - (170.0f * fTemp34)):270.0f)):(iTemp29?((160.0f * fTemp32) + 270.0f):430.0f)):(iTemp27?(430.0f - (60.0f * fTemp30)):370.0f)):(iTemp25?((430.0f * fTemp28) + 370.0f):800.0f)):(iTemp22?(800.0f - (450.0f * fTemp26)):350.0f)):(iTemp20?(350.0f - fTemp24):270.0f)):(iTemp18?((180.0f * fTemp21) + 270.0f):450.0f)):(iTemp16?(450.0f - (125.0f * fTemp19)):325.0f)):(iTemp14?(325.0f * (fTemp17 + 1.0f)):650.0f)):(iTemp12?(650.0f - (250.0f * fTemp15)):400.0f)):(iTemp10?(400.0f - (110.0f * fTemp13)):290.0f)):(iTemp7?((110.0f * fTemp11) + 290.0f):400.0f)):(iTemp8?(400.0f - (50.0f * fTemp9)):350.0f));
			fRec8[0] = ((fSlow5 * fRec9[1]) + (fSlow6 * fRec8[1]));
			fRec9[0] = (((fSlow6 * fRec9[1]) + (fSlow7 * fRec8[1])) + float(iTemp0));
			float fTemp58 = ((fSlow3 * fRec8[0]) + 1.0f);
			float fTemp59 = (fSlow2 * fTemp58);
			float fTemp60 = ((fTemp57 <= fTemp59)?fTemp59:fTemp57);
			float fTemp61 = tanf((fConst3 * fTemp60));
			float fTemp62 = (1.0f / fTemp61);
			float fTemp63 = (20.0f * fTemp15);
			float fTemp64 = (20.0f * fTemp26);
			float fTemp65 = (10.0f * fTemp36);
			float fTemp66 = (10.0f * fTemp49);
			float fTemp67 = (20.0f * fTemp51);
			float fTemp68 = (20.0f * fTemp53);
			float fTemp69 = (20.0f * fTemp6);
			float fTemp70 = ((iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp48?(iTemp50?(iTemp52?(iTemp54?(iTemp56?80.0f:(iTemp54?(80.0f - fTemp69):60.0f)):(iTemp52?(60.0f - (10.0f * fTemp55)):50.0f)):(iTemp50?(fTemp68 + 50.0f):70.0f)):(iTemp48?(70.0f - fTemp67):50.0f)):(iTemp46?(fTemp66 + 50.0f):60.0f)):(iTemp44?(60.0f - (20.0f * fTemp47)):40.0f)):(iTemp42?((20.0f * fTemp45) + 40.0f):60.0f)):(iTemp39?(60.0f - (20.0f * fTemp43)):40.0f)):40.0f):(iTemp35?(40.0f * (fTemp38 + 1.0f)):80.0f)):(iTemp33?(80.0f - fTemp65):70.0f)):(iTemp31?(70.0f - (30.0f * fTemp34)):40.0f)):40.0f):40.0f):(iTemp25?(40.0f * (fTemp28 + 1.0f)):80.0f)):(iTemp22?(80.0f - fTemp64):60.0f)):60.0f):(iTemp18?(60.0f - (20.0f * fTemp21)):40.0f)):(iTemp16?((10.0f * fTemp19) + 40.0f):50.0f)):50.0f):(iTemp12?(fTemp63 + 50.0f):70.0f)):(iTemp10?(70.0f - (30.0f * fTemp13)):40.0f)):(iTemp7?((30.0f * fTemp11) + 40.0f):70.0f)):(iTemp8?(70.0f - (30.0f * fTemp9)):40.0f)) / fTemp60);
			float fTemp71 = (((fTemp62 + fTemp70) / fTemp61) + 1.0f);
			fRec0[0] = (fTemp5 - (((fRec0[2] * (((fTemp62 - fTemp70) / fTemp61) + 1.0f)) + (2.0f * (fRec0[1] * (1.0f - (1.0f / mydsp_faustpower2_f(fTemp61)))))) / fTemp71));
			float fTemp72 = ((0.000839999993f * (1000.0f - fTemp59)) + 0.800000012f);
			float fTemp73 = ((0.00366666657f * (400.0f - fTemp59)) + 3.0f);
			float fTemp74 = (iSlow12?fTemp73:fTemp72);
			float fTemp75 = (iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp48?(iTemp50?(iTemp52?(iTemp54?(iTemp56?1150.0f:(iTemp54?((450.0f * fTemp6) + 1150.0f):1600.0f)):(iTemp52?((100.0f * fTemp55) + 1600.0f):1700.0f)):(iTemp50?(1700.0f - (900.0f * fTemp53)):800.0f)):(iTemp48?(800.0f - (100.0f * fTemp51)):700.0f)):(iTemp46?((340.0f * fTemp49) + 700.0f):1040.0f)):(iTemp44?((580.0f * fTemp47) + 1040.0f):1620.0f)):(iTemp42?((130.0f * fTemp45) + 1620.0f):1750.0f)):(iTemp39?(1750.0f - (1000.0f * fTemp43)):750.0f)):(iTemp37?(750.0f - (150.0f * fTemp40)):600.0f)):(iTemp35?((520.0f * fTemp38) + 600.0f):1120.0f)):(iTemp33?((680.0f * fTemp36) + 1120.0f):1800.0f)):(iTemp31?((50.0f * fTemp34) + 1800.0f):1850.0f)):(iTemp29?(1850.0f - (1030.0f * fTemp32)):820.0f)):(iTemp27?(820.0f - (190.0f * fTemp30)):630.0f)):(iTemp25?((520.0f * fTemp28) + 630.0f):1150.0f)):(iTemp22?((850.0f * fTemp26) + 1150.0f):2000.0f)):(iTemp20?((140.0f * fTemp23) + 2000.0f):2140.0f)):(iTemp18?(2140.0f - (1340.0f * fTemp21)):800.0f)):(iTemp16?(800.0f - (100.0f * fTemp19)):700.0f)):(iTemp14?((380.0f * fTemp17) + 700.0f):1080.0f)):(iTemp12?((620.0f * fTemp15) + 1080.0f):1700.0f)):(iTemp10?((170.0f * fTemp13) + 1700.0f):1870.0f)):(iTemp7?(1870.0f - (1070.0f * fTemp11)):800.0f)):(iTemp8?(800.0f - (200.0f * fTemp9)):600.0f));
			float fTemp76 = ((fSlow14 * fTemp58) + 30.0f);
			float fTemp77 = (iSlow13?(((fTemp75 >= 1300.0f) & (fTemp59 >= 200.0f))?(fTemp75 - (0.000952380942f * ((fTemp59 + -200.0f) * (fTemp75 + -1300.0f)))):((fTemp75 <= fTemp76)?fTemp76:fTemp75)):fTemp75);
			float fTemp78 = tanf((fConst3 * fTemp77));
			float fTemp79 = (1.0f / fTemp78);
			float fTemp80 = (10.0f * fTemp11);
			float fTemp81 = (10.0f * fTemp15);
			float fTemp82 = (10.0f * fTemp38);
			float fTemp83 = (10.0f * fTemp47);
			float fTemp84 = ((iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp48?(iTemp50?(iTemp52?(iTemp54?(iTemp56?90.0f:(iTemp54?(90.0f - (10.0f * fTemp6)):80.0f)):(iTemp52?((20.0f * fTemp55) + 80.0f):100.0f)):(iTemp50?(100.0f - fTemp68):80.0f)):(iTemp48?(80.0f - fTemp67):60.0f)):(iTemp46?(fTemp66 + 60.0f):70.0f)):(iTemp44?(fTemp83 + 70.0f):80.0f)):(iTemp42?((10.0f * fTemp45) + 80.0f):90.0f)):(iTemp39?(90.0f - (10.0f * fTemp43)):80.0f)):80.0f):(iTemp35?(fTemp82 + 80.0f):90.0f)):(iTemp33?(90.0f - fTemp65):80.0f)):(iTemp31?((10.0f * fTemp34) + 80.0f):90.0f)):(iTemp29?(90.0f - (10.0f * fTemp32)):80.0f)):(iTemp27?(80.0f - (20.0f * fTemp30)):60.0f)):(iTemp25?((30.0f * fTemp28) + 60.0f):90.0f)):(iTemp22?((10.0f * fTemp26) + 90.0f):100.0f)):(iTemp20?(100.0f - (10.0f * fTemp23)):90.0f)):(iTemp18?(90.0f - (10.0f * fTemp21)):80.0f)):(iTemp16?(80.0f - (20.0f * fTemp19)):60.0f)):(iTemp14?((30.0f * fTemp17) + 60.0f):90.0f)):(iTemp12?(90.0f - fTemp81):80.0f)):(iTemp10?((10.0f * fTemp13) + 80.0f):90.0f)):(iTemp7?(90.0f - fTemp80):80.0f)):(iTemp8?(80.0f - (20.0f * fTemp9)):60.0f)) / fTemp77);
			float fTemp85 = (((fTemp79 + fTemp84) / fTemp78) + 1.0f);
			fRec10[0] = (fTemp5 - (((fRec10[2] * (((fTemp79 - fTemp84) / fTemp78) + 1.0f)) + (2.0f * (fRec10[1] * (1.0f - (1.0f / mydsp_faustpower2_f(fTemp78)))))) / fTemp85));
			float fTemp86 = (iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp48?(iTemp50?(iTemp52?(iTemp54?(iTemp56?0.630957007f:(iTemp54?(0.630957007f - (0.567861021f * fTemp6)):0.0630960017f)):(iTemp52?((0.0369039997f * fTemp55) + 0.0630960017f):0.100000001f)):(iTemp50?((0.254812986f * fTemp53) + 0.100000001f):0.35481301f)):(iTemp48?(0.35481301f - (0.103624001f * fTemp51)):0.251188993f)):(iTemp46?((0.195494995f * fTemp49) + 0.251188993f):0.446684003f)):(iTemp44?(0.446684003f - (0.195494995f * fTemp47)):0.251188993f)):(iTemp42?(0.251188993f - (0.219566002f * fTemp45)):0.0316229984f)):(iTemp39?((0.250214994f * fTemp43) + 0.0316229984f):0.281838f)):(iTemp37?(0.281838f - (0.181838006f * fTemp40)):0.100000001f)):(iTemp35?((0.401187003f * fTemp38) + 0.100000001f):0.501187027f)):(iTemp33?(0.501187027f - (0.301661015f * fTemp36)):0.199525997f)):(iTemp31?(0.199525997f - (0.136429995f * fTemp34)):0.0630960017f)):(iTemp29?((0.253131986f * fTemp32) + 0.0630960017f):0.316228002f)):(iTemp27?(0.316228002f - (0.216227993f * fTemp30)):0.100000001f)):(iTemp25?((0.401187003f * fTemp28) + 0.100000001f):0.501187027f)):(iTemp22?(0.501187027f - (0.401187003f * fTemp26)):0.100000001f)):(iTemp20?((0.151188999f * fTemp23) + 0.100000001f):0.251188993f)):(iTemp18?((0.0306490008f * fTemp21) + 0.251188993f):0.281838f)):(iTemp16?(0.281838f - (0.123349003f * fTemp19)):0.158489004f)):(iTemp14?((0.342698008f * fTemp17) + 0.158489004f):0.501187027f)):(iTemp12?(0.501187027f - (0.301661015f * fTemp15)):0.199525997f)):(iTemp10?(0.199525997f - (0.0216979999f * fTemp13)):0.177827999f)):(iTemp7?((0.138400003f * fTemp11) + 0.177827999f):0.316228002f)):(iTemp8?(0.316228002f - (0.216227993f * fTemp9)):0.100000001f));
			float fTemp87 = (iSlow12?(fTemp73 * fTemp86):(fTemp72 * fTemp86));
			float fTemp88 = (100.0f * fTemp9);
			float fTemp89 = (50.0f * fTemp17);
			float fTemp90 = (50.0f * fTemp36);
			float fTemp91 = (iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp48?(iTemp50?(iTemp52?(iTemp54?(iTemp56?2800.0f:(iTemp54?(2800.0f - (100.0f * fTemp6)):2700.0f)):2700.0f):(iTemp50?((130.0f * fTemp53) + 2700.0f):2830.0f)):(iTemp48?(2830.0f - (300.0f * fTemp51)):2530.0f)):(iTemp46?(2530.0f - (280.0f * fTemp49)):2250.0f)):(iTemp44?((150.0f * fTemp47) + 2250.0f):2400.0f)):(iTemp42?((200.0f * fTemp45) + 2400.0f):2600.0f)):(iTemp39?(2600.0f - (200.0f * fTemp43)):2400.0f)):2400.0f):(iTemp35?((350.0f * fTemp38) + 2400.0f):2750.0f)):(iTemp33?(2750.0f - fTemp90):2700.0f)):(iTemp31?((200.0f * fTemp34) + 2700.0f):2900.0f)):(iTemp29?(2900.0f - (200.0f * fTemp32)):2700.0f)):(iTemp27?((50.0f * fTemp30) + 2700.0f):2750.0f)):(iTemp25?((150.0f * fTemp28) + 2750.0f):2900.0f)):(iTemp22?(2900.0f - (100.0f * fTemp26)):2800.0f)):(iTemp20?((150.0f * fTemp23) + 2800.0f):2950.0f)):(iTemp18?(2950.0f - (120.0f * fTemp21)):2830.0f)):(iTemp16?(2830.0f - (130.0f * fTemp19)):2700.0f)):(iTemp14?(2700.0f - fTemp89):2650.0f)):(iTemp12?(2650.0f - (50.0f * fTemp15)):2600.0f)):(iTemp10?((200.0f * fTemp13) + 2600.0f):2800.0f)):(iTemp7?(2800.0f - (200.0f * fTemp11)):2600.0f)):(iTemp8?(fTemp88 + 2600.0f):2700.0f));
			float fTemp92 = tanf((fConst3 * fTemp91));
			float fTemp93 = (1.0f / fTemp92);
			float fTemp94 = (20.0f * fTemp28);
			float fTemp95 = (20.0f * fTemp36);
			float fTemp96 = (20.0f * fTemp38);
			float fTemp97 = (60.0f * fTemp49);
			float fTemp98 = ((iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp48?(iTemp50?(iTemp52?120.0f:(iTemp50?(120.0f - fTemp68):100.0f)):(iTemp48?((70.0f * fTemp51) + 100.0f):170.0f)):(iTemp46?(170.0f - fTemp97):110.0f)):(iTemp44?(110.0f - fTemp83):100.0f)):100.0f):100.0f):100.0f):(iTemp35?(fTemp96 + 100.0f):120.0f)):(iTemp33?(120.0f - fTemp95):100.0f)):100.0f):100.0f):100.0f):(iTemp25?(fTemp94 + 100.0f):120.0f)):120.0f):(iTemp20?(120.0f - (20.0f * fTemp23)):100.0f)):100.0f):(iTemp16?((70.0f * fTemp19) + 100.0f):170.0f)):(iTemp14?(170.0f - fTemp89):120.0f)):(iTemp12?(120.0f - fTemp63):100.0f)):100.0f):100.0f):100.0f) / fTemp91);
			float fTemp99 = (((fTemp93 + fTemp98) / fTemp92) + 1.0f);
			fRec11[0] = (fTemp5 - (((fRec11[2] * (((fTemp93 - fTemp98) / fTemp92) + 1.0f)) + (2.0f * (fRec11[1] * (1.0f - (1.0f / mydsp_faustpower2_f(fTemp92)))))) / fTemp99));
			float fTemp100 = (iTemp18?((0.0293140002f * fTemp21) + 0.0501190014f):0.0794330016f);
			float fTemp101 = (iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp48?(iTemp50?(iTemp52?(iTemp54?(iTemp56?0.100000001f:(iTemp54?(0.100000001f - (0.0683770031f * fTemp6)):0.0316229984f)):0.0316229984f):(iTemp50?((0.126865998f * fTemp53) + 0.0316229984f):0.158489004f)):(iTemp48?(0.158489004f - (0.126865998f * fTemp51)):0.0316229984f)):(iTemp46?((0.323190004f * fTemp49) + 0.0316229984f):0.35481301f)):0.35481301f):(iTemp42?(0.35481301f - (0.196324006f * fTemp45)):0.158489004f)):(iTemp39?(0.158489004f - (0.0693639964f * fTemp43)):0.0891249999f)):(iTemp37?(0.0891249999f - (0.0640060008f * fTemp40)):0.0251189992f)):(iTemp35?((0.0456760004f * fTemp38) + 0.0251189992f):0.0707949996f)):(iTemp33?((0.0550980009f * fTemp36) + 0.0707949996f):0.125892997f)):(iTemp31?(0.125892997f - (0.0627970025f * fTemp34)):0.0630960017f)):(iTemp29?(0.0630960017f - (0.0129770003f * fTemp32)):0.0501190014f)):(iTemp27?((0.020676f * fTemp30) + 0.0501190014f):0.0707949996f)):(iTemp25?(0.0707949996f - (0.0456760004f * fTemp28)):0.0251189992f)):(iTemp22?((0.152709007f * fTemp26) + 0.0251189992f):0.177827999f)):(iTemp20?(0.177827999f - (0.127709001f * fTemp23)):0.0501190014f)):fTemp100):(iTemp16?(0.0794330016f - (0.0616500005f * fTemp19)):0.0177829992f)):(iTemp14?((0.428900987f * fTemp17) + 0.0177829992f):0.446684003f)):(iTemp12?(0.446684003f - (0.195494995f * fTemp15)):0.251188993f)):(iTemp10?(0.251188993f - (0.125295997f * fTemp13)):0.125892997f)):(iTemp7?((0.125295997f * fTemp11) + 0.125892997f):0.251188993f)):(iTemp8?(0.251188993f - (0.109935001f * fTemp9)):0.141253993f));
			float fTemp102 = (iSlow12?(fTemp73 * fTemp101):(fTemp72 * fTemp101));
			float fTemp103 = (350.0f * fTemp47);
			float fTemp104 = (iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp48?(iTemp50?(iTemp52?(iTemp54?(iTemp56?3500.0f:(iTemp54?(3500.0f - (200.0f * fTemp6)):3300.0f)):(iTemp52?((400.0f * fTemp55) + 3300.0f):3700.0f)):(iTemp50?(3700.0f - (200.0f * fTemp53)):3500.0f)):3500.0f):(iTemp46?(3500.0f - (1050.0f * fTemp49)):2450.0f)):(iTemp44?(fTemp103 + 2450.0f):2800.0f)):(iTemp42?((250.0f * fTemp45) + 2800.0f):3050.0f)):(iTemp39?(3050.0f - (450.0f * fTemp43)):2600.0f)):(iTemp37?((75.0f * fTemp40) + 2600.0f):2675.0f)):(iTemp35?((325.0f * fTemp38) + 2675.0f):3000.0f)):3000.0f):(iTemp31?((350.0f * fTemp34) + 3000.0f):3350.0f)):(iTemp29?(3350.0f - (350.0f * fTemp32)):3000.0f)):3000.0f):(iTemp25?((900.0f * fTemp28) + 3000.0f):3900.0f)):(iTemp22?(3900.0f - (300.0f * fTemp26)):3600.0f)):(iTemp20?((300.0f * fTemp23) + 3600.0f):3900.0f)):(iTemp18?(3900.0f - (100.0f * fTemp21)):3800.0f)):3800.0f):(iTemp14?(3800.0f - (900.0f * fTemp17)):2900.0f)):(iTemp12?((300.0f * fTemp15) + 2900.0f):3200.0f)):(iTemp10?((50.0f * fTemp13) + 3200.0f):3250.0f)):(iTemp7?(3250.0f - (450.0f * fTemp11)):2800.0f)):(iTemp8?(fTemp88 + 2800.0f):2900.0f));
			float fTemp105 = tanf((fConst3 * fTemp104));
			float fTemp106 = (1.0f / fTemp105);
			float fTemp107 = ((iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp48?(iTemp50?(iTemp52?(iTemp54?(iTemp56?130.0f:(iTemp54?(fTemp69 + 130.0f):150.0f)):150.0f):(iTemp50?(150.0f - fTemp68):130.0f)):(iTemp48?((50.0f * fTemp51) + 130.0f):180.0f)):(iTemp46?(180.0f - fTemp97):120.0f)):120.0f):120.0f):120.0f):120.0f):(iTemp35?(fTemp82 + 120.0f):130.0f)):(iTemp33?(130.0f - fTemp65):120.0f)):120.0f):120.0f):120.0f):(iTemp25?((10.0f * fTemp28) + 120.0f):130.0f)):(iTemp22?(fTemp64 + 130.0f):150.0f)):(iTemp20?(150.0f - (30.0f * fTemp23)):120.0f)):120.0f):(iTemp16?((60.0f * fTemp19) + 120.0f):180.0f)):(iTemp14?(180.0f - fTemp89):130.0f)):(iTemp12?(130.0f - fTemp81):120.0f)):120.0f):(iTemp7?(fTemp80 + 120.0f):130.0f)):(iTemp8?(130.0f - (10.0f * fTemp9)):120.0f)) / fTemp104);
			float fTemp108 = (((fTemp106 + fTemp107) / fTemp105) + 1.0f);
			fRec12[0] = (fTemp5 - (((fRec12[2] * (((fTemp106 - fTemp107) / fTemp105) + 1.0f)) + (2.0f * (fRec12[1] * (1.0f - (1.0f / mydsp_faustpower2_f(fTemp105)))))) / fTemp108));
			float fTemp109 = (iTemp31?(0.100000001f - (0.0841509998f * fTemp34)):0.0158489998f);
			float fTemp110 = (iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp48?(iTemp50?(iTemp52?(iTemp54?(iTemp56?0.0158489998f:(iTemp54?((0.00193400006f * fTemp6) + 0.0158489998f):0.0177829992f)):(iTemp52?(0.0177829992f - (0.00193400006f * fTemp55)):0.0158489998f)):(iTemp50?((0.0239620004f * fTemp53) + 0.0158489998f):0.0398110002f)):(iTemp48?(0.0398110002f - (0.0298110005f * fTemp51)):0.00999999978f)):(iTemp46?((0.344812989f * fTemp49) + 0.00999999978f):0.35481301f)):(iTemp44?(0.35481301f - (0.103624001f * fTemp47)):0.251188993f)):(iTemp42?(0.251188993f - (0.171755999f * fTemp45)):0.0794330016f)):(iTemp39?((0.0205669999f * fTemp43) + 0.0794330016f):0.100000001f)):(iTemp37?(0.100000001f - (0.0601890013f * fTemp40)):0.0398110002f)):(iTemp35?((0.0232849997f * fTemp38) + 0.0398110002f):0.0630960017f)):(iTemp33?((0.0369039997f * fTemp36) + 0.0630960017f):0.100000001f)):fTemp109):(iTemp29?((0.0635839999f * fTemp32) + 0.0158489998f):0.0794330016f)):(iTemp27?(0.0794330016f - (0.0478099994f * fTemp30)):0.0316229984f)):(iTemp25?((0.0683770031f * fTemp28) + 0.0316229984f):0.100000001f)):(iTemp22?(0.100000001f - (0.0900000036f * fTemp26)):0.00999999978f)):(iTemp20?((0.0401189998f * fTemp23) + 0.00999999978f):0.0501190014f)):fTemp100):(iTemp16?(0.0794330016f - (0.0694330037f * fTemp19)):0.00999999978f)):(iTemp14?((0.388107002f * fTemp17) + 0.00999999978f):0.398106992f)):(iTemp12?(0.398106992f - (0.198580995f * fTemp15)):0.199525997f)):(iTemp10?(0.199525997f - (0.099526003f * fTemp13)):0.100000001f)):(iTemp7?((0.151188999f * fTemp11) + 0.100000001f):0.251188993f)):(iTemp8?(0.251188993f - (0.0516630001f * fTemp9)):0.199525997f));
			float fTemp111 = (iSlow12?(fTemp73 * fTemp110):(fTemp72 * fTemp110));
			float fTemp112 = (iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp48?4950.0f:(iTemp46?(4950.0f - (2200.0f * fTemp49)):2750.0f)):(iTemp44?(fTemp103 + 2750.0f):3100.0f)):(iTemp42?((240.0f * fTemp45) + 3100.0f):3340.0f)):(iTemp39?(3340.0f - (440.0f * fTemp43)):2900.0f)):(iTemp37?(fTemp41 + 2900.0f):2950.0f)):(iTemp35?((400.0f * fTemp38) + 2950.0f):3350.0f)):(iTemp33?(3350.0f - fTemp90):3300.0f)):(iTemp31?((290.0f * fTemp34) + 3300.0f):3590.0f)):(iTemp29?(3590.0f - (290.0f * fTemp32)):3300.0f)):(iTemp27?((100.0f * fTemp30) + 3300.0f):3400.0f)):(iTemp25?((1550.0f * fTemp28) + 3400.0f):4950.0f)):4950.0f):4950.0f):4950.0f):4950.0f):(iTemp14?(4950.0f - (1700.0f * fTemp17)):3250.0f)):(iTemp12?((330.0f * fTemp15) + 3250.0f):3580.0f)):(iTemp10?(3580.0f - (40.0f * fTemp13)):3540.0f)):(iTemp7?(3540.0f - (540.0f * fTemp11)):3000.0f)):(iTemp8?((300.0f * fTemp9) + 3000.0f):3300.0f));
			float fTemp113 = tanf((fConst3 * fTemp112));
			float fTemp114 = (1.0f / fTemp113);
			float fTemp115 = ((iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp48?(iTemp50?(iTemp52?(iTemp54?(iTemp56?140.0f:(iTemp54?((60.0f * fTemp6) + 140.0f):200.0f)):200.0f):(iTemp50?(200.0f - (65.0f * fTemp53)):135.0f)):(iTemp48?((65.0f * fTemp51) + 135.0f):200.0f)):(iTemp46?(200.0f - (70.0f * fTemp49)):130.0f)):(iTemp44?(130.0f - fTemp83):120.0f)):120.0f):120.0f):120.0f):(iTemp35?(fTemp96 + 120.0f):140.0f)):(iTemp33?(140.0f - fTemp95):120.0f)):120.0f):120.0f):120.0f):(iTemp25?(fTemp94 + 120.0f):140.0f)):(iTemp22?((60.0f * fTemp26) + 140.0f):200.0f)):(iTemp20?(200.0f - fTemp24):120.0f)):120.0f):(iTemp16?((80.0f * fTemp19) + 120.0f):200.0f)):(iTemp14?(200.0f - (60.0f * fTemp17)):140.0f)):(iTemp12?(140.0f - fTemp63):120.0f)):120.0f):(iTemp7?((15.0f * fTemp11) + 120.0f):135.0f)):(iTemp8?(135.0f - (15.0f * fTemp9)):120.0f)) / fTemp112);
			float fTemp116 = (((fTemp114 + fTemp115) / fTemp113) + 1.0f);
			fRec13[0] = (fTemp5 - (((fRec13[2] * (((fTemp114 - fTemp115) / fTemp113) + 1.0f)) + (2.0f * (fRec13[1] * (1.0f - (1.0f / mydsp_faustpower2_f(fTemp113)))))) / fTemp116));
			float fTemp117 = (iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp48?(iTemp50?(iTemp52?0.00100000005f:(iTemp50?((0.000777999987f * fTemp53) + 0.00100000005f):0.00177800003f)):(iTemp48?(0.00177800003f - (0.001147f * fTemp51)):0.000630999974f)):(iTemp46?((0.0993689969f * fTemp49) + 0.000630999974f):0.100000001f)):(iTemp44?((0.0258930009f * fTemp47) + 0.100000001f):0.125892997f)):(iTemp42?(0.125892997f - (0.0860819966f * fTemp45)):0.0398110002f)):(iTemp39?(0.0398110002f - (0.0298110005f * fTemp43)):0.00999999978f)):(iTemp37?((0.00584900007f * fTemp40) + 0.00999999978f):0.0158489998f)):(iTemp35?(0.0158489998f - (0.00325999991f * fTemp38)):0.0125890002f)):(iTemp33?((0.0874110013f * fTemp36) + 0.0125890002f):0.100000001f)):fTemp109):(iTemp29?((0.00410400005f * fTemp32) + 0.0158489998f):0.0199529994f)):0.0199529994f):(iTemp25?(0.0199529994f - (0.0167909991f * fTemp28)):0.0031620001f)):(iTemp22?(0.0031620001f - (0.00157700002f * fTemp26)):0.00158499996f)):(iTemp20?((0.00472499989f * fTemp23) + 0.00158499996f):0.00631000008f)):(iTemp18?(0.00631000008f - (0.00314799999f * fTemp21)):0.0031620001f)):(iTemp16?(0.0031620001f - (0.00216199993f * fTemp19)):0.00100000005f)):(iTemp14?((0.0784329996f * fTemp17) + 0.00100000005f):0.0794330016f)):(iTemp12?((0.0205669999f * fTemp15) + 0.0794330016f):0.100000001f)):(iTemp10?(0.100000001f - (0.0683770031f * fTemp13)):0.0316229984f)):(iTemp7?((0.0184959993f * fTemp11) + 0.0316229984f):0.0501190014f)):0.0501190014f);
			float fTemp118 = (iSlow12?(fTemp73 * fTemp117):(fTemp72 * fTemp117));
			float fTemp119 = (((((((fRec0[2] * (0.0f - (fTemp74 / fTemp61))) + ((fRec0[0] * fTemp74) / fTemp61)) / fTemp71) + (((fRec10[2] * (0.0f - (fTemp87 / fTemp78))) + ((fRec10[0] * fTemp87) / fTemp78)) / fTemp85)) + (((fRec11[2] * (0.0f - (fTemp102 / fTemp92))) + ((fRec11[0] * fTemp102) / fTemp92)) / fTemp99)) + (((fRec12[2] * (0.0f - (fTemp111 / fTemp105))) + ((fRec12[0] * fTemp111) / fTemp105)) / fTemp108)) + (((fRec13[2] * (0.0f - (fTemp118 / fTemp113))) + ((fRec13[0] * fTemp118) / fTemp113)) / fTemp116));
			output0[i] = FAUSTFLOAT(fTemp119);
			output1[i] = FAUSTFLOAT(fTemp119);
			iVec0[1] = iVec0[0];
			fRec1[1] = fRec1[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec2[1] = fRec2[0];
			iRec6[1] = iRec6[0];
			fRec7[1] = fRec7[0];
			fRec8[1] = fRec8[0];
			fRec9[1] = fRec9[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			fRec10[2] = fRec10[1];
			fRec10[1] = fRec10[0];
			fRec11[2] = fRec11[1];
			fRec11[1] = fRec11[0];
			fRec12[2] = fRec12[1];
			fRec12[1] = fRec12[0];
			fRec13[2] = fRec13[1];
			fRec13[1] = fRec13[0];
			
		}
		
	}

	
};

#endif
