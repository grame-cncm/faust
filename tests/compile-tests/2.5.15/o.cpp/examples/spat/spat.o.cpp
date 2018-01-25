//----------------------------------------------------------
// author: "Grame"
// copyright: "(c)GRAME 2006"
// license: "BSD"
// name: "spat"
// version: "1.0"
//
// Code generated with Faust 2.5.15 (https://faust.grame.fr)
//----------------------------------------------------------

/* link with  */
#include <math.h>

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
	float 	fTempPerm0;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fslider1;
	float 	fRec0[2];
	float 	fRec1[2];
	float 	fRec2[2];
	float 	fRec3[2];
	float 	fRec4[2];
	float 	fRec5[2];
	float 	fRec6[2];
	float 	fRec7[2];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("author", "Grame");
		m->declare("copyright", "(c)GRAME 2006");
		m->declare("license", "BSD");
		m->declare("name", "spat");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("spats.lib/name", "Faust Spatialization Library");
		m->declare("spats.lib/version", "0.0");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() { return 1; }
	virtual int getNumOutputs() { return 8; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fTempPerm0 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.5f;
		fslider1 = 0.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<2; i++) fRec7[i] = 0;
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
		ui_interface->openVerticalBox("Spatializer 1x8");
		ui_interface->addHorizontalSlider("angle", &fslider1, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("distance", &fslider0, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = float(fslider0);
		float 	fSlow1 = (fSlow0 + 1.0f);
		float 	fSlow2 = float(fslider1);
		float 	fSlow3 = (4.9999999999994493e-05f * (fSlow1 * sqrtf(max(0.0f, (1.0f - (8 * (fSlow0 * fabsf((fmodf((fSlow2 + 1.5f),1.0f) + -0.5f)))))))));
		float 	fSlow4 = (4.9999999999994493e-05f * (fSlow1 * sqrtf(max(0.0f, (1.0f - (8 * (fSlow0 * fabsf((fmodf((fSlow2 + 1.375f),1.0f) + -0.5f)))))))));
		float 	fSlow5 = (4.9999999999994493e-05f * (fSlow1 * sqrtf(max(0.0f, (1.0f - (8 * (fSlow0 * fabsf((fmodf((fSlow2 + 1.25f),1.0f) + -0.5f)))))))));
		float 	fSlow6 = (4.9999999999994493e-05f * (fSlow1 * sqrtf(max(0.0f, (1.0f - (8 * (fSlow0 * fabsf((fmodf((fSlow2 + 1.125f),1.0f) + -0.5f)))))))));
		float 	fSlow7 = (4.9999999999994493e-05f * (fSlow1 * sqrtf(max(0.0f, (1.0f - (8 * (fSlow0 * fabsf((fmodf((fSlow2 + 1.0f),1.0f) + -0.5f)))))))));
		float 	fSlow8 = (4.9999999999994493e-05f * (fSlow1 * sqrtf(max(0.0f, (1.0f - (8 * (fSlow0 * fabsf((fmodf((fSlow2 + 0.875f),1.0f) + -0.5f)))))))));
		float 	fSlow9 = (4.9999999999994493e-05f * (fSlow1 * sqrtf(max(0.0f, (1.0f - (8 * (fSlow0 * fabsf((fmodf((fSlow2 + 0.75f),1.0f) + -0.5f)))))))));
		float 	fSlow10 = (4.9999999999994493e-05f * (fSlow1 * sqrtf(max(0.0f, (1.0f - (8 * (fSlow0 * fabsf((fmodf((fSlow2 + 0.625f),1.0f) + -0.5f)))))))));
		//zone2b
		//zone3
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		FAUSTFLOAT* output2 = output[2];
		FAUSTFLOAT* output3 = output[3];
		FAUSTFLOAT* output4 = output[4];
		FAUSTFLOAT* output5 = output[5];
		FAUSTFLOAT* output6 = output[6];
		FAUSTFLOAT* output7 = output[7];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fTempPerm0 = (float)input0[i];
			fRec0[0] = (fSlow3 + (0.99990000000000001f * fRec0[1]));
			output0[i] = (FAUSTFLOAT)(fTempPerm0 * fRec0[0]);
			fRec1[0] = (fSlow4 + (0.99990000000000001f * fRec1[1]));
			output1[i] = (FAUSTFLOAT)(fTempPerm0 * fRec1[0]);
			fRec2[0] = (fSlow5 + (0.99990000000000001f * fRec2[1]));
			output2[i] = (FAUSTFLOAT)(fTempPerm0 * fRec2[0]);
			fRec3[0] = (fSlow6 + (0.99990000000000001f * fRec3[1]));
			output3[i] = (FAUSTFLOAT)(fTempPerm0 * fRec3[0]);
			fRec4[0] = (fSlow7 + (0.99990000000000001f * fRec4[1]));
			output4[i] = (FAUSTFLOAT)(fTempPerm0 * fRec4[0]);
			fRec5[0] = (fSlow8 + (0.99990000000000001f * fRec5[1]));
			output5[i] = (FAUSTFLOAT)(fTempPerm0 * fRec5[0]);
			fRec6[0] = (fSlow9 + (0.99990000000000001f * fRec6[1]));
			output6[i] = (FAUSTFLOAT)(fTempPerm0 * fRec6[0]);
			fRec7[0] = (fSlow10 + (0.99990000000000001f * fRec7[1]));
			output7[i] = (FAUSTFLOAT)(fTempPerm0 * fRec7[0]);
			// post processing
			fRec7[1] = fRec7[0];
			fRec6[1] = fRec6[0];
			fRec5[1] = fRec5[0];
			fRec4[1] = fRec4[0];
			fRec3[1] = fRec3[0];
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
		}
	}
};


