/* ------------------------------------------------------------
author: "CICM"
copyright: "(c)CICM 2013"
license: "BSD"
name: "fourSourcesToOcto"
version: "1.0"
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
	FAUSTFLOAT fHslider0;
	float fRec0[2];
	FAUSTFLOAT fHslider1;
	float fRec1[2];
	FAUSTFLOAT fHslider2;
	float fRec2[2];
	FAUSTFLOAT fHslider3;
	float fRec3[2];
	FAUSTFLOAT fHslider4;
	float fRec4[2];
	FAUSTFLOAT fHslider5;
	float fRec5[2];
	FAUSTFLOAT fHslider6;
	float fRec6[2];
	FAUSTFLOAT fHslider7;
	float fRec7[2];
	
 public:
	
	void metadata(Meta* m) { 
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
		m->declare("name", "fourSourcesToOcto");
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() {
		return 4;
		
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
		fConst0 = expf((0.0f - (50.0f / min(192000.0f, max(1.0f, float(fSamplingFreq))))));
		fConst1 = (1.0f - fConst0);
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(1.0f);
		fHslider1 = FAUSTFLOAT(1.0f);
		fHslider2 = FAUSTFLOAT(1.0f);
		fHslider3 = FAUSTFLOAT(1.0f);
		fHslider4 = FAUSTFLOAT(0.0f);
		fHslider5 = FAUSTFLOAT(0.0f);
		fHslider6 = FAUSTFLOAT(0.0f);
		fHslider7 = FAUSTFLOAT(0.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec0[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec1[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec2[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec3[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec4[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec5[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec6[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec7[l7] = 0.0f;
			
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
		ui_interface->openVerticalBox("fourSourcesToOcto");
		ui_interface->addHorizontalSlider("Angle1", &fHslider4, 0.0f, -6.28318548f, 6.28318548f, 0.00100000005f);
		ui_interface->addHorizontalSlider("Angle2", &fHslider5, 0.0f, -6.28318548f, 6.28318548f, 0.00100000005f);
		ui_interface->addHorizontalSlider("Angle3", &fHslider6, 0.0f, -6.28318548f, 6.28318548f, 0.00100000005f);
		ui_interface->addHorizontalSlider("Angle4", &fHslider7, 0.0f, -6.28318548f, 6.28318548f, 0.00100000005f);
		ui_interface->addHorizontalSlider("Radius1", &fHslider0, 1.0f, 0.0f, 5.0f, 0.00100000005f);
		ui_interface->addHorizontalSlider("Radius2", &fHslider1, 1.0f, 0.0f, 5.0f, 0.00100000005f);
		ui_interface->addHorizontalSlider("Radius3", &fHslider2, 1.0f, 0.0f, 5.0f, 0.00100000005f);
		ui_interface->addHorizontalSlider("Radius4", &fHslider3, 1.0f, 0.0f, 5.0f, 0.00100000005f);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* input2 = inputs[2];
		FAUSTFLOAT* input3 = inputs[3];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		FAUSTFLOAT* output2 = outputs[2];
		FAUSTFLOAT* output3 = outputs[3];
		FAUSTFLOAT* output4 = outputs[4];
		FAUSTFLOAT* output5 = outputs[5];
		FAUSTFLOAT* output6 = outputs[6];
		FAUSTFLOAT* output7 = outputs[7];
		float fSlow0 = (fConst1 * float(fHslider0));
		float fSlow1 = (fConst1 * float(fHslider1));
		float fSlow2 = (fConst1 * float(fHslider2));
		float fSlow3 = (fConst1 * float(fHslider3));
		float fSlow4 = (fConst1 * float(fHslider4));
		float fSlow5 = (fConst1 * float(fHslider5));
		float fSlow6 = (fConst1 * float(fHslider6));
		float fSlow7 = (fConst1 * float(fHslider7));
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input0[i]);
			fRec0[0] = (fSlow0 + (fConst0 * fRec0[1]));
			int iTemp1 = (fRec0[0] > 1.0f);
			int iTemp2 = (fRec0[0] < 1.0f);
			float fTemp3 = (float(iTemp1) + (fRec0[0] * float(iTemp2)));
			float fTemp4 = ((1.38629436f * (1.0f - fTemp3)) + 1.0f);
			float fTemp5 = (fTemp0 * fTemp4);
			float fTemp6 = (float(iTemp2) + (mydsp_faustpower2_f(fRec0[0]) * float(iTemp1)));
			float fTemp7 = float(input1[i]);
			fRec1[0] = (fSlow1 + (fConst0 * fRec1[1]));
			int iTemp8 = (fRec1[0] > 1.0f);
			int iTemp9 = (fRec1[0] < 1.0f);
			float fTemp10 = (float(iTemp8) + (fRec1[0] * float(iTemp9)));
			float fTemp11 = ((1.38629436f * (1.0f - fTemp10)) + 1.0f);
			float fTemp12 = (fTemp7 * fTemp11);
			float fTemp13 = (float(iTemp9) + (mydsp_faustpower2_f(fRec1[0]) * float(iTemp8)));
			float fTemp14 = float(input2[i]);
			fRec2[0] = (fSlow2 + (fConst0 * fRec2[1]));
			int iTemp15 = (fRec2[0] > 1.0f);
			int iTemp16 = (fRec2[0] < 1.0f);
			float fTemp17 = (float(iTemp15) + (fRec2[0] * float(iTemp16)));
			float fTemp18 = ((1.38629436f * (1.0f - fTemp17)) + 1.0f);
			float fTemp19 = (fTemp14 * fTemp18);
			float fTemp20 = (float(iTemp16) + (mydsp_faustpower2_f(fRec2[0]) * float(iTemp15)));
			float fTemp21 = float(input3[i]);
			fRec3[0] = (fSlow3 + (fConst0 * fRec3[1]));
			int iTemp22 = (fRec3[0] > 1.0f);
			int iTemp23 = (fRec3[0] < 1.0f);
			float fTemp24 = (float(iTemp22) + (fRec3[0] * float(iTemp23)));
			float fTemp25 = ((1.38629436f * (1.0f - fTemp24)) + 1.0f);
			float fTemp26 = (fTemp21 * fTemp25);
			float fTemp27 = (float(iTemp23) + (mydsp_faustpower2_f(fRec3[0]) * float(iTemp22)));
			float fTemp28 = (0.142857149f * ((((fTemp5 / fTemp6) + (fTemp12 / fTemp13)) + (fTemp19 / fTemp20)) + (fTemp26 / fTemp27)));
			float fTemp29 = (2.0f * fTemp3);
			float fTemp30 = ((2.0f * ((fTemp3 * float((fTemp29 > 0.0f))) * float((fTemp29 <= 1.0f)))) + float((fTemp29 > 1.0f)));
			fRec4[0] = (fSlow4 + (fConst0 * fRec4[1]));
			float fTemp31 = (2.0f * fTemp10);
			float fTemp32 = ((2.0f * ((fTemp10 * float((fTemp31 > 0.0f))) * float((fTemp31 <= 1.0f)))) + float((fTemp31 > 1.0f)));
			fRec5[0] = (fSlow5 + (fConst0 * fRec5[1]));
			float fTemp33 = (2.0f * fTemp17);
			float fTemp34 = ((2.0f * ((fTemp17 * float((fTemp33 > 0.0f))) * float((fTemp33 <= 1.0f)))) + float((fTemp33 > 1.0f)));
			fRec6[0] = (fSlow6 + (fConst0 * fRec6[1]));
			float fTemp35 = (2.0f * fTemp24);
			float fTemp36 = ((2.0f * ((fTemp24 * float((fTemp35 > 0.0f))) * float((fTemp35 <= 1.0f)))) + float((fTemp35 > 1.0f)));
			fRec7[0] = (fSlow7 + (fConst0 * fRec7[1]));
			float fTemp37 = ((((((fTemp5 * fTemp30) * cosf(fRec4[0])) / fTemp6) + (((fTemp12 * fTemp32) * cosf(fRec5[0])) / fTemp13)) + (((fTemp19 * fTemp34) * cosf(fRec6[0])) / fTemp20)) + (((fTemp26 * fTemp36) * cosf(fRec7[0])) / fTemp27));
			float fTemp38 = (0.214285716f * fTemp37);
			float fTemp39 = (2.0f * fRec4[0]);
			float fTemp40 = (1.38629436f * fTemp3);
			float fTemp41 = (fTemp40 + -0.693147182f);
			float fTemp42 = (2.46630335f * fTemp41);
			float fTemp43 = ((2.46630335f * ((fTemp41 * float((fTemp42 > 0.0f))) * float((fTemp42 <= 1.0f)))) + float((fTemp42 > 1.0f)));
			float fTemp44 = (2.0f * fRec5[0]);
			float fTemp45 = (1.38629436f * fTemp10);
			float fTemp46 = (fTemp45 + -0.693147182f);
			float fTemp47 = (2.46630335f * fTemp46);
			float fTemp48 = ((2.46630335f * ((fTemp46 * float((fTemp47 > 0.0f))) * float((fTemp47 <= 1.0f)))) + float((fTemp47 > 1.0f)));
			float fTemp49 = (2.0f * fRec6[0]);
			float fTemp50 = (1.38629436f * fTemp17);
			float fTemp51 = (fTemp50 + -0.693147182f);
			float fTemp52 = (2.46630335f * fTemp51);
			float fTemp53 = ((2.46630335f * ((fTemp51 * float((fTemp52 > 0.0f))) * float((fTemp52 <= 1.0f)))) + float((fTemp52 > 1.0f)));
			float fTemp54 = (2.0f * fRec7[0]);
			float fTemp55 = (1.38629436f * fTemp24);
			float fTemp56 = (fTemp55 + -0.693147182f);
			float fTemp57 = (2.46630335f * fTemp56);
			float fTemp58 = ((2.46630335f * ((fTemp56 * float((fTemp57 > 0.0f))) * float((fTemp57 <= 1.0f)))) + float((fTemp57 > 1.0f)));
			float fTemp59 = (0.0857142881f * (((((((fTemp0 * cosf(fTemp39)) * fTemp4) * fTemp43) / fTemp6) + ((((fTemp7 * cosf(fTemp44)) * fTemp11) * fTemp48) / fTemp13)) + ((((fTemp14 * cosf(fTemp49)) * fTemp18) * fTemp53) / fTemp20)) + ((((fTemp21 * cosf(fTemp54)) * fTemp25) * fTemp58) / fTemp27)));
			float fTemp60 = (3.0f * fRec4[0]);
			float fTemp61 = (fTemp40 + -1.09861231f);
			float fTemp62 = (3.47605944f * fTemp61);
			float fTemp63 = ((3.47605944f * ((fTemp61 * float((fTemp62 > 0.0f))) * float((fTemp62 <= 1.0f)))) + float((fTemp62 > 1.0f)));
			float fTemp64 = (3.0f * fRec5[0]);
			float fTemp65 = (fTemp45 + -1.09861231f);
			float fTemp66 = (3.47605944f * fTemp65);
			float fTemp67 = ((3.47605944f * ((fTemp65 * float((fTemp66 > 0.0f))) * float((fTemp66 <= 1.0f)))) + float((fTemp66 > 1.0f)));
			float fTemp68 = (3.0f * fRec6[0]);
			float fTemp69 = (fTemp50 + -1.09861231f);
			float fTemp70 = (3.47605944f * fTemp69);
			float fTemp71 = ((3.47605944f * ((fTemp69 * float((fTemp70 > 0.0f))) * float((fTemp70 <= 1.0f)))) + float((fTemp70 > 1.0f)));
			float fTemp72 = (3.0f * fRec7[0]);
			float fTemp73 = (fTemp55 + -1.09861231f);
			float fTemp74 = (3.47605944f * fTemp73);
			float fTemp75 = ((3.47605944f * ((fTemp73 * float((fTemp74 > 0.0f))) * float((fTemp74 <= 1.0f)))) + float((fTemp74 > 1.0f)));
			float fTemp76 = (((((((fTemp0 * cosf(fTemp60)) * fTemp4) * fTemp63) / fTemp6) + ((((fTemp7 * cosf(fTemp64)) * fTemp11) * fTemp67) / fTemp13)) + ((((fTemp14 * cosf(fTemp68)) * fTemp18) * fTemp71) / fTemp20)) + ((((fTemp21 * cosf(fTemp72)) * fTemp25) * fTemp75) / fTemp27));
			float fTemp77 = (0.0142857144f * fTemp76);
			output0[i] = FAUSTFLOAT((((fTemp28 + fTemp38) + fTemp59) + fTemp77));
			float fTemp78 = ((((((fTemp5 * sinf(fRec4[0])) * fTemp30) / fTemp6) + (((fTemp12 * sinf(fRec5[0])) * fTemp32) / fTemp13)) + (((fTemp19 * sinf(fRec6[0])) * fTemp34) / fTemp20)) + (((fTemp26 * sinf(fRec7[0])) * fTemp36) / fTemp27));
			float fTemp79 = (0.151522875f * fTemp78);
			float fTemp80 = (0.0857142881f * (((((((fTemp0 * sinf(fTemp39)) * fTemp4) * fTemp43) / fTemp6) + ((((fTemp7 * sinf(fTemp44)) * fTemp11) * fTemp48) / fTemp13)) + ((((fTemp14 * sinf(fTemp49)) * fTemp18) * fTemp53) / fTemp20)) + ((((fTemp21 * sinf(fTemp54)) * fTemp25) * fTemp58) / fTemp27)));
			float fTemp81 = (((((((fTemp0 * sinf(fTemp60)) * fTemp4) * fTemp63) / fTemp6) + ((((fTemp7 * sinf(fTemp64)) * fTemp11) * fTemp67) / fTemp13)) + ((((fTemp14 * sinf(fTemp68)) * fTemp18) * fTemp71) / fTemp20)) + ((((fTemp21 * sinf(fTemp72)) * fTemp25) * fTemp75) / fTemp27));
			output1[i] = FAUSTFLOAT((((((fTemp28 + fTemp79) + (0.151522875f * fTemp37)) + fTemp80) + (0.0101015251f * fTemp81)) - (0.0101015251f * fTemp76)));
			float fTemp82 = (0.214285716f * fTemp78);
			float fTemp83 = (0.0142857144f * fTemp81);
			output2[i] = FAUSTFLOAT(((fTemp28 + fTemp82) - (fTemp59 + fTemp83)));
			float fTemp84 = (0.151522875f * fTemp37);
			output3[i] = FAUSTFLOAT(((((fTemp28 + (0.151522875f * fTemp78)) + (0.0101015251f * fTemp81)) + (0.0101015251f * fTemp76)) - (fTemp80 + fTemp84)));
			output4[i] = FAUSTFLOAT(((fTemp28 + fTemp59) - (fTemp38 + fTemp77)));
			output5[i] = FAUSTFLOAT((((fTemp28 + fTemp80) + (0.0101015251f * fTemp76)) - ((fTemp79 + (0.151522875f * fTemp37)) + (0.0101015251f * fTemp81))));
			output6[i] = FAUSTFLOAT(((fTemp28 + fTemp83) - (fTemp59 + fTemp82)));
			output7[i] = FAUSTFLOAT(((fTemp28 + fTemp84) - (((fTemp80 + (0.151522875f * fTemp78)) + (0.0101015251f * fTemp81)) + (0.0101015251f * fTemp76))));
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec7[1] = fRec7[0];
			
		}
		
	}

	
};

#endif
