/* ------------------------------------------------------------
author: "CICM"
copyright: "(c)CICM 2013"
license: "BSD"
name: "oneSourceToStereo"
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
		m->declare("name", "oneSourceToStereo");
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() {
		return 1;
		
	}
	virtual int getNumOutputs() {
		return 2;
		
	}
	virtual int getInputRate(int channel) {
		int rate;
		switch (channel) {
			case 0: {
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
		fHslider1 = FAUSTFLOAT(0.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec0[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec1[l1] = 0.0f;
			
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
		ui_interface->openVerticalBox("oneSourceToStereo");
		ui_interface->addHorizontalSlider("Angle", &fHslider1, 0.0f, -6.28318548f, 6.28318548f, 0.00100000005f);
		ui_interface->addHorizontalSlider("Radius", &fHslider0, 1.0f, 0.0f, 5.0f, 0.00100000005f);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = (fConst1 * float(fHslider0));
		float fSlow1 = (fConst1 * float(fHslider1));
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec0[0] = (fSlow0 + (fConst0 * fRec0[1]));
			int iTemp0 = (fRec0[0] > 1.0f);
			int iTemp1 = (fRec0[0] < 1.0f);
			float fTemp2 = (float(iTemp0) + (fRec0[0] * float(iTemp1)));
			float fTemp3 = (float(input0[i]) * ((2.07944155f * (1.0f - fTemp2)) + 1.0f));
			float fTemp4 = (3.0f * fTemp2);
			float fTemp5 = ((3.0f * ((fTemp2 * float((fTemp4 > 0.0f))) * float((fTemp4 <= 1.0f)))) + float((fTemp4 > 1.0f)));
			fRec1[0] = (fSlow1 + (fConst0 * fRec1[1]));
			float fTemp6 = (fTemp5 * cosf(fRec1[0]));
			float fTemp7 = (2.0f * fRec1[0]);
			float fTemp8 = (2.07944155f * fTemp2);
			float fTemp9 = (fTemp8 + -0.693147182f);
			float fTemp10 = (2.46630335f * fTemp9);
			float fTemp11 = ((2.46630335f * ((fTemp9 * float((fTemp10 > 0.0f))) * float((fTemp10 <= 1.0f)))) + float((fTemp10 > 1.0f)));
			float fTemp12 = (cosf(fTemp7) * fTemp11);
			float fTemp13 = (0.0777777806f * fTemp12);
			float fTemp14 = (3.0f * fRec1[0]);
			float fTemp15 = (fTemp8 + -1.09861231f);
			float fTemp16 = (3.47605944f * fTemp15);
			float fTemp17 = ((3.47605944f * ((fTemp15 * float((fTemp16 > 0.0f))) * float((fTemp16 <= 1.0f)))) + float((fTemp16 > 1.0f)));
			float fTemp18 = (cosf(fTemp14) * fTemp17);
			float fTemp19 = (4.0f * fRec1[0]);
			float fTemp20 = (fTemp8 + -1.38629436f);
			float fTemp21 = (4.48142004f * fTemp20);
			float fTemp22 = ((4.48142004f * ((fTemp20 * float((fTemp21 > 0.0f))) * float((fTemp21 <= 1.0f)))) + float((fTemp21 > 1.0f)));
			float fTemp23 = (0.0141414143f * (cosf(fTemp19) * fTemp22));
			float fTemp24 = (5.0f * fRec1[0]);
			float fTemp25 = (fTemp8 + -1.60943794f);
			float fTemp26 = (5.48481512f * fTemp25);
			float fTemp27 = ((5.48481512f * ((fTemp25 * float((fTemp26 > 0.0f))) * float((fTemp26 <= 1.0f)))) + float((fTemp26 > 1.0f)));
			float fTemp28 = (cosf(fTemp24) * fTemp27);
			float fTemp29 = (6.0f * fRec1[0]);
			float fTemp30 = (fTemp8 + -1.79175949f);
			float fTemp31 = (6.48715925f * fTemp30);
			float fTemp32 = ((6.48715925f * ((fTemp30 * float((fTemp31 > 0.0f))) * float((fTemp31 <= 1.0f)))) + float((fTemp31 > 1.0f)));
			float fTemp33 = (cosf(fTemp29) * fTemp32);
			float fTemp34 = (0.00175299495f * fTemp33);
			float fTemp35 = (7.0f * fRec1[0]);
			float fTemp36 = (fTemp8 + -1.9459101f);
			float fTemp37 = (7.48887587f * fTemp36);
			float fTemp38 = ((7.48887587f * ((fTemp36 * float((fTemp37 > 0.0f))) * float((fTemp37 <= 1.0f)))) + float((fTemp37 > 1.0f)));
			float fTemp39 = (cosf(fTemp35) * fTemp38);
			float fTemp40 = (0.707106769f * ((((((((0.116666667f * fTemp6) + 0.0666666701f) + fTemp13) + (0.0388888903f * fTemp18)) + fTemp23) + (0.00353535358f * fTemp28)) + fTemp34) + (0.00264818221f * fTemp39)));
			float fTemp41 = (0.0141414143f * (sinf(fTemp19) * fTemp22));
			float fTemp42 = (sinf(fRec1[0]) * fTemp5);
			float fTemp43 = (0.107785948f * fTemp6);
			float fTemp44 = (sinf(fTemp7) * fTemp11);
			float fTemp45 = (0.0549971946f * fTemp44);
			float fTemp46 = (0.0549971946f * fTemp12);
			float fTemp47 = (sinf(fTemp14) * fTemp17);
			float fTemp48 = (sinf(fTemp24) * fTemp27);
			float fTemp49 = (sinf(fTemp29) * fTemp32);
			float fTemp50 = (0.00123955461f * fTemp49);
			float fTemp51 = (0.00123955461f * fTemp33);
			float fTemp52 = (sinf(fTemp35) * fTemp38);
			float fTemp53 = (((((((fTemp41 + (((((((0.044646401f * fTemp42) + 0.0666666701f) + fTemp43) + fTemp45) + fTemp46) + (0.035928648f * fTemp47)) + (0.0148821333f * fTemp18))) + (0.0032662407f * fTemp48)) - (0.00135292124f * fTemp28)) + fTemp50) - fTemp51) + (0.0010134154f * fTemp52)) - (0.00244660117f * fTemp39));
			float fTemp54 = (0.0824957937f * fTemp42);
			float fTemp55 = (0.0777777806f * fTemp44);
			float fTemp56 = (0.00175299495f * fTemp49);
			float fTemp57 = ((0.107785948f * fTemp42) + 0.0666666701f);
			float fTemp58 = (0.0549971946f * fTemp12);
			float fTemp59 = (0.116666667f * fTemp42);
			float fTemp60 = (0.0388888903f * fTemp47);
			float fTemp61 = (0.00353535358f * fTemp48);
			float fTemp62 = (0.00264818221f * fTemp52);
			float fTemp63 = (0.0824957937f * fTemp6);
			float fTemp64 = (0.035928648f * fTemp47);
			float fTemp65 = (0.0032662407f * fTemp48);
			float fTemp66 = (((((((((0.0148821333f * fTemp18) + (((((0.0666666701f - (0.044646401f * fTemp42)) + (0.107785948f * fTemp6)) - (0.0549971946f * fTemp44)) + (0.0549971946f * fTemp12)) - (0.035928648f * fTemp47))) - fTemp41) - fTemp65) - (0.00135292124f * fTemp28)) - (0.00123955461f * fTemp49)) - (0.00123955461f * fTemp33)) - (0.0010134154f * fTemp52)) - (0.00244660117f * fTemp39));
			float fTemp67 = (float(iTemp1) + (mydsp_faustpower2_f(fRec0[0]) * float(iTemp0)));
			output0[i] = FAUSTFLOAT(((fTemp3 * ((((((((fTemp40 + (0.980785251f * fTemp53)) + (0.987688363f * ((0.00187254755f * fTemp39) + ((((((((((fTemp54 + 0.0666666701f) + (0.0824957937f * fTemp6)) + fTemp55) + (0.0274985973f * fTemp47)) - (0.0274985973f * fTemp18)) - fTemp23) - (0.00249987235f * fTemp48)) - (0.00249987235f * fTemp28)) - fTemp56) - (0.00187254755f * fTemp52))))) + (0.923879504f * (((fTemp51 + (fTemp50 + ((((((((fTemp57 + (0.044646401f * fTemp6)) + (0.0549971946f * fTemp44)) - fTemp58) - (0.0148821333f * fTemp47)) - (0.035928648f * fTemp18)) - fTemp41) - (0.00135292124f * fTemp48)) + (0.0032662407f * fTemp28)))) + (0.00244660117f * fTemp52)) - (0.0010134154f * fTemp39)))) + (0.809017003f * ((((fTemp23 + (((fTemp59 + 0.0666666701f) - fTemp13) - fTemp60)) + fTemp61) - fTemp34) - fTemp62))) + (0.649448037f * (((((((fTemp41 + (((((fTemp57 - (0.044646401f * fTemp6)) - fTemp45) - (0.0549971946f * fTemp12)) - (0.0148821333f * fTemp47)) + (0.035928648f * fTemp18))) - (0.00135292124f * fTemp48)) - (0.0032662407f * fTemp28)) - (0.00123955461f * fTemp49)) + (0.00123955461f * fTemp33)) + (0.00244660117f * fTemp52)) + (0.0010134154f * fTemp39)))) + (0.453990489f * (((fTemp56 + ((((((0.0274985973f * fTemp47) + ((((0.0824957937f * fTemp42) + 0.0666666701f) - fTemp63) - fTemp55)) + (0.0274985973f * fTemp18)) - fTemp23) - (0.00249987235f * fTemp48)) + (0.00249987235f * fTemp28))) - (0.00187254755f * fTemp52)) - (0.00187254755f * fTemp39)))) + (0.233445361f * ((((((((((fTemp58 + ((((0.044646401f * fTemp42) + 0.0666666701f) - fTemp43) - (0.0549971946f * fTemp44))) + fTemp64) - (0.0148821333f * fTemp18)) - fTemp41) + fTemp65) + (0.00135292124f * fTemp28)) - (0.00123955461f * fTemp49)) - (0.00123955461f * fTemp33)) + (0.0010134154f * fTemp52)) + (0.00244660117f * fTemp39)))) + (0.195090324f * fTemp66))) / fTemp67));
			float fTemp68 = (0.00249987235f * fTemp48);
			float fTemp69 = (0.0032662407f * fTemp28);
			output1[i] = FAUSTFLOAT(((fTemp3 * ((((((((fTemp40 + (0.195090324f * fTemp53)) + (0.233445361f * (((((((fTemp41 + (((fTemp46 + (fTemp45 + ((0.0666666701f - (0.044646401f * fTemp42)) - fTemp43))) - fTemp64) - (0.0148821333f * fTemp18))) - (0.0032662407f * fTemp48)) + (0.00135292124f * fTemp28)) + (0.00123955461f * fTemp49)) - (0.00123955461f * fTemp33)) - (0.0010134154f * fTemp52)) + (0.00244660117f * fTemp39)))) + (0.453990489f * (((((((((fTemp55 + ((0.0666666701f - fTemp54) - (0.0824957937f * fTemp6))) - (0.0274985973f * fTemp47)) + (0.0274985973f * fTemp18)) - fTemp23) + fTemp68) + (0.00249987235f * fTemp28)) - fTemp56) + (0.00187254755f * fTemp52)) - (0.00187254755f * fTemp39)))) + (0.649448037f * ((((((((((((0.0549971946f * fTemp44) + ((0.0666666701f - (0.107785948f * fTemp42)) - (0.044646401f * fTemp6))) - (0.0549971946f * fTemp12)) + (0.0148821333f * fTemp47)) + (0.035928648f * fTemp18)) - fTemp41) + (0.00135292124f * fTemp48)) - fTemp69) + (0.00123955461f * fTemp49)) + (0.00123955461f * fTemp33)) - (0.00244660117f * fTemp52)) + (0.0010134154f * fTemp39)))) + (0.809017003f * (fTemp62 + (((fTemp23 + (fTemp60 + ((0.0666666701f - fTemp59) - fTemp13))) - fTemp61) - fTemp34)))) + (0.923879504f * (((((fTemp69 + ((fTemp41 + ((((((0.0666666701f - (0.107785948f * fTemp42)) + (0.044646401f * fTemp6)) - (0.0549971946f * fTemp44)) - (0.0549971946f * fTemp12)) + (0.0148821333f * fTemp47)) - (0.035928648f * fTemp18))) + (0.00135292124f * fTemp48))) - (0.00123955461f * fTemp49)) + (0.00123955461f * fTemp33)) - (0.00244660117f * fTemp52)) - (0.0010134154f * fTemp39)))) + (0.987688363f * (((fTemp56 + ((fTemp68 + (((((fTemp63 + (0.0666666701f - (0.0824957937f * fTemp42))) - fTemp55) - (0.0274985973f * fTemp47)) - (0.0274985973f * fTemp18)) - fTemp23)) - (0.00249987235f * fTemp28))) + (0.00187254755f * fTemp52)) + (0.00187254755f * fTemp39)))) + (0.980785251f * fTemp66))) / fTemp67));
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			
		}
		
	}

	
};

#endif
