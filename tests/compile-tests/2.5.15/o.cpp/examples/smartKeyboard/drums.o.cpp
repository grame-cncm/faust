//----------------------------------------------------------
// name: "drums"
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
	float 	fVec0[2];
	float 	fConst1;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fslider1;
	int 	iRec3[2];
	float 	fRec2[3];
	float 	fRec1[3];
	FAUSTFLOAT 	fbutton0;
	float 	fVec1[2];
	float 	fConst2;
	float 	fRec4[2];
	float 	fConst3;
	int 	iTempPerm0;
	float 	fConst4;
	float 	fTempPerm1;
	float 	fConst5;
	float 	fConst6;
	float 	fConst7;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fslider3;
	float 	fConst8;
	float 	fRec0[3];
	float 	fConst9;
	float 	fConst10;
	float 	fConst11;
	float 	fConst12;
	float 	fRec5[3];
	float 	fConst13;
	float 	fConst14;
	float 	fConst15;
	float 	fRec6[3];
	float 	fConst16;
	float 	fConst17;
	float 	fConst18;
	float 	fRec7[3];
	float 	fConst19;
	float 	fConst20;
	float 	fConst21;
	float 	fRec8[3];
	float 	fConst22;
	float 	fConst23;
	float 	fConst24;
	float 	fRec9[3];
	float 	fConst25;
	float 	fConst26;
	float 	fConst27;
	float 	fRec10[3];
	float 	fConst28;
	float 	fConst29;
	float 	fConst30;
	float 	fRec11[3];
	float 	fConst31;
	float 	fConst32;
	float 	fConst33;
	float 	fRec12[3];
	float 	fConst34;
	float 	fConst35;
	float 	fConst36;
	float 	fRec13[3];
	float 	fConst37;
	float 	fConst38;
	float 	fConst39;
	float 	fRec14[3];
	float 	fConst40;
	float 	fConst41;
	float 	fConst42;
	float 	fRec15[3];
	float 	fConst43;
	float 	fConst44;
	float 	fConst45;
	float 	fRec16[3];
	float 	fConst46;
	float 	fConst47;
	float 	fConst48;
	float 	fRec17[3];
	float 	fConst49;
	float 	fConst50;
	float 	fConst51;
	float 	fRec18[3];
	float 	fConst52;
	float 	fConst53;
	float 	fConst54;
	float 	fRec19[3];
	float 	fConst55;
	float 	fConst56;
	float 	fConst57;
	float 	fRec20[3];
	float 	fConst58;
	float 	fConst59;
	float 	fConst60;
	float 	fRec21[3];
	float 	fConst61;
	float 	fConst62;
	float 	fConst63;
	float 	fRec22[3];
	float 	fConst64;
	float 	fConst65;
	float 	fConst66;
	float 	fRec23[3];
	float 	fTempPerm2;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("envelopes.lib/author", "GRAME");
		m->declare("envelopes.lib/copyright", "GRAME");
		m->declare("envelopes.lib/license", "LGPL with exception");
		m->declare("envelopes.lib/name", "Faust Envelope Library");
		m->declare("envelopes.lib/version", "0.0");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("interface", "SmartKeyboard{  'Number of Keyboards':'2',  'Keyboard 0 - Number of Keys':'2',  'Keyboard 1 - Number of Keys':'1',  'Keyboard 0 - Static Mode':'1',  'Keyboard 1 - Static Mode':'1',  'Keyboard 0 - Send X':'1',  'Keyboard 0 - Send Y':'1',  'Keyboard 1 - Send X':'1',  'Keyboard 1 - Send Y':'1',  'Keyboard 0 - Piano Keyboard':'0',  'Keyboard 1 - Piano Keyboard':'0',  'Keyboard 0 - Key 0 - Label':'High',  'Keyboard 0 - Key 1 - Label':'Mid',  'Keyboard 1 - Key 0 - Label':'Low' }");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "drums");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
	}

	virtual int getNumInputs() { return 0; }
	virtual int getNumOutputs() { return 2; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(192000.0f, max(1.0f, (float)fSamplingFreq));
		fConst1 = (3.1415926535897931f / fConst0);
		fConst2 = (0.002f * fConst0);
		fConst3 = (0.001f * fConst0);
		iTempPerm0 = 0;
		fConst4 = (1000.0f / fConst0);
		fTempPerm1 = 0;
		fConst5 = powf(0.001f,(1.0f / float((0.59999999999999998f * fConst0))));
		fConst6 = (0 - (2 * fConst5));
		fConst7 = (376.99111843077515f / fConst0);
		fConst8 = faustpower<2>(fConst5);
		fConst9 = powf(0.001f,(1.0f / float((0.56999999999999995f * fConst0))));
		fConst10 = (0 - (2 * fConst9));
		fConst11 = (6.2831853071795862f / fConst0);
		fConst12 = faustpower<2>(fConst9);
		fConst13 = powf(0.001f,(1.0f / float((0.54000000000000004f * fConst0))));
		fConst14 = (0 - (2 * fConst13));
		fConst15 = faustpower<2>(fConst13);
		fConst16 = powf(0.001f,(1.0f / float((0.51000000000000001f * fConst0))));
		fConst17 = (0 - (2 * fConst16));
		fConst18 = faustpower<2>(fConst16);
		fConst19 = powf(0.001f,(1.0f / float((0.47999999999999998f * fConst0))));
		fConst20 = (0 - (2 * fConst19));
		fConst21 = faustpower<2>(fConst19);
		fConst22 = powf(0.001f,(1.0f / float((0.44999999999999996f * fConst0))));
		fConst23 = (0 - (2 * fConst22));
		fConst24 = faustpower<2>(fConst22);
		fConst25 = powf(0.001f,(1.0f / float((0.41999999999999998f * fConst0))));
		fConst26 = (0 - (2 * fConst25));
		fConst27 = faustpower<2>(fConst25);
		fConst28 = powf(0.001f,(1.0f / float((0.39000000000000001f * fConst0))));
		fConst29 = (0 - (2 * fConst28));
		fConst30 = faustpower<2>(fConst28);
		fConst31 = powf(0.001f,(1.0f / float((0.35999999999999999f * fConst0))));
		fConst32 = (0 - (2 * fConst31));
		fConst33 = faustpower<2>(fConst31);
		fConst34 = powf(0.001f,(1.0f / float((0.32999999999999996f * fConst0))));
		fConst35 = (0 - (2 * fConst34));
		fConst36 = faustpower<2>(fConst34);
		fConst37 = powf(0.001f,(1.0f / float((0.29999999999999999f * fConst0))));
		fConst38 = (0 - (2 * fConst37));
		fConst39 = faustpower<2>(fConst37);
		fConst40 = powf(0.001f,(1.0f / float((0.27000000000000002f * fConst0))));
		fConst41 = (0 - (2 * fConst40));
		fConst42 = faustpower<2>(fConst40);
		fConst43 = powf(0.001f,(1.0f / float((0.23999999999999999f * fConst0))));
		fConst44 = (0 - (2 * fConst43));
		fConst45 = faustpower<2>(fConst43);
		fConst46 = powf(0.001f,(1.0f / float((0.20999999999999999f * fConst0))));
		fConst47 = (0 - (2 * fConst46));
		fConst48 = faustpower<2>(fConst46);
		fConst49 = powf(0.001f,(1.0f / float((0.17999999999999999f * fConst0))));
		fConst50 = (0 - (2 * fConst49));
		fConst51 = faustpower<2>(fConst49);
		fConst52 = powf(0.001f,(1.0f / float((0.14999999999999999f * fConst0))));
		fConst53 = (0 - (2 * fConst52));
		fConst54 = faustpower<2>(fConst52);
		fConst55 = powf(0.001f,(1.0f / float((0.12f * fConst0))));
		fConst56 = (0 - (2 * fConst55));
		fConst57 = faustpower<2>(fConst55);
		fConst58 = powf(0.001f,(1.0f / float((0.089999999999999997f * fConst0))));
		fConst59 = (0 - (2 * fConst58));
		fConst60 = faustpower<2>(fConst58);
		fConst61 = powf(0.001f,(1.0f / float((0.059999999999999998f * fConst0))));
		fConst62 = (0 - (2 * fConst61));
		fConst63 = faustpower<2>(fConst61);
		fConst64 = powf(0.001f,(1.0f / float((0.029999999999999999f * fConst0))));
		fConst65 = (0 - (2 * fConst64));
		fConst66 = faustpower<2>(fConst64);
		fTempPerm2 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 1.0f;
		fslider1 = 1.0f;
		fbutton0 = 0.0;
		fslider2 = 0.0f;
		fslider3 = 0.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fVec0[i] = 0;
		for (int i=0; i<2; i++) iRec3[i] = 0;
		for (int i=0; i<3; i++) fRec2[i] = 0;
		for (int i=0; i<3; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<3; i++) fRec0[i] = 0;
		for (int i=0; i<3; i++) fRec5[i] = 0;
		for (int i=0; i<3; i++) fRec6[i] = 0;
		for (int i=0; i<3; i++) fRec7[i] = 0;
		for (int i=0; i<3; i++) fRec8[i] = 0;
		for (int i=0; i<3; i++) fRec9[i] = 0;
		for (int i=0; i<3; i++) fRec10[i] = 0;
		for (int i=0; i<3; i++) fRec11[i] = 0;
		for (int i=0; i<3; i++) fRec12[i] = 0;
		for (int i=0; i<3; i++) fRec13[i] = 0;
		for (int i=0; i<3; i++) fRec14[i] = 0;
		for (int i=0; i<3; i++) fRec15[i] = 0;
		for (int i=0; i<3; i++) fRec16[i] = 0;
		for (int i=0; i<3; i++) fRec17[i] = 0;
		for (int i=0; i<3; i++) fRec18[i] = 0;
		for (int i=0; i<3; i++) fRec19[i] = 0;
		for (int i=0; i<3; i++) fRec20[i] = 0;
		for (int i=0; i<3; i++) fRec21[i] = 0;
		for (int i=0; i<3; i++) fRec22[i] = 0;
		for (int i=0; i<3; i++) fRec23[i] = 0;
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
		ui_interface->openVerticalBox("drums");
		ui_interface->addButton("gate", &fbutton0);
		ui_interface->addHorizontalSlider("key", &fslider3, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->addHorizontalSlider("keyboard", &fslider2, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->addHorizontalSlider("x", &fslider0, 1.0f, 0.0f, 1.0f, 0.001f);
		ui_interface->addHorizontalSlider("y", &fslider1, 1.0f, 0.0f, 1.0f, 0.001f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = min(fabsf(((2 * float(fslider0)) + -1)), fabsf(((2 * float(fslider1)) + -1)));
		float 	fSlow1 = tanf((fConst1 * ((15000 * fSlow0) + 500)));
		float 	fSlow2 = (1.0f / fSlow1);
		float 	fSlow3 = (((fSlow2 + 1.4142135623730949f) / fSlow1) + 1);
		float 	fSlow4 = (2.0f / fSlow3);
		float 	fSlow5 = tanf((fConst1 * ((500 * fSlow0) + 40)));
		float 	fSlow6 = (1.0f / fSlow5);
		float 	fSlow7 = (1.0f / (((fSlow6 + 1.4142135623730949f) / fSlow5) + 1));
		float 	fSlow8 = (1.0f / faustpower<2>(fSlow5));
		float 	fSlow9 = (((fSlow6 + -1.4142135623730949f) / fSlow5) + 1);
		float 	fSlow10 = (2 * (1 - fSlow8));
		float 	fSlow11 = (2 * (0 - fSlow8));
		float 	fSlow12 = (1.0f / fSlow3);
		float 	fSlow13 = (2 * (1 - (1.0f / faustpower<2>(fSlow1))));
		float 	fSlow14 = (((fSlow2 + -1.4142135623730949f) / fSlow1) + 1);
		float 	fSlow15 = float(fbutton0);
		int 	iSlow16 = ((2 * (1 - int(float(fslider2)))) + (1 - int(float(fslider3))));
		float 	fSlow17 = (fConst6 * cosf((fConst7 * iSlow16)));
		int 	iSlow18 = (60 * iSlow16);
		float 	fSlow19 = (fConst10 * cosf((fConst11 * (iSlow18 + 200))));
		float 	fSlow20 = (fConst14 * cosf((fConst11 * (iSlow18 + 400))));
		float 	fSlow21 = (fConst17 * cosf((fConst11 * (iSlow18 + 600))));
		float 	fSlow22 = (fConst20 * cosf((fConst11 * (iSlow18 + 800))));
		float 	fSlow23 = (fConst23 * cosf((fConst11 * (iSlow18 + 1000))));
		float 	fSlow24 = (fConst26 * cosf((fConst11 * (iSlow18 + 1200))));
		float 	fSlow25 = (fConst29 * cosf((fConst11 * (iSlow18 + 1400))));
		float 	fSlow26 = (fConst32 * cosf((fConst11 * (iSlow18 + 1600))));
		float 	fSlow27 = (fConst35 * cosf((fConst11 * (iSlow18 + 1800))));
		float 	fSlow28 = (fConst38 * cosf((fConst11 * (iSlow18 + 2000))));
		float 	fSlow29 = (fConst41 * cosf((fConst11 * (iSlow18 + 2200))));
		float 	fSlow30 = (fConst44 * cosf((fConst11 * (iSlow18 + 2400))));
		float 	fSlow31 = (fConst47 * cosf((fConst11 * (iSlow18 + 2600))));
		float 	fSlow32 = (fConst50 * cosf((fConst11 * (iSlow18 + 2800))));
		float 	fSlow33 = (fConst53 * cosf((fConst11 * (iSlow18 + 3000))));
		float 	fSlow34 = (fConst56 * cosf((fConst11 * (iSlow18 + 3200))));
		float 	fSlow35 = (fConst59 * cosf((fConst11 * (iSlow18 + 3400))));
		float 	fSlow36 = (fConst62 * cosf((fConst11 * (iSlow18 + 3600))));
		float 	fSlow37 = (fConst65 * cosf((fConst11 * (iSlow18 + 3800))));
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fVec0[0] = fConst0;
			iRec3[0] = ((1103515245 * iRec3[1]) + 12345);
			fRec2[0] = ((4.6566128752457969e-10f * iRec3[0]) - (fSlow7 * ((fSlow9 * fRec2[2]) + (fSlow10 * fRec2[1]))));
			fRec1[0] = ((fSlow7 * (((fSlow8 * fRec2[0]) + (fSlow11 * fRec2[1])) + (fSlow8 * fRec2[2]))) - (fSlow12 * ((fSlow13 * fRec1[1]) + (fSlow14 * fRec1[2]))));
			fVec1[0] = fSlow15;
			fRec4[0] = ((int((((fSlow15 - fVec1[1]) > 0) > 0)))?0:min(fConst2, ((fRec4[1] + (0.002f * (fConst0 - fVec0[1]))) + 1)));
			iTempPerm0 = int((fRec4[0] < fConst3));
			fTempPerm1 = (fSlow4 * ((fRec1[2] + (fRec1[0] + (2.0f * fRec1[1]))) * ((iTempPerm0)?((int((fRec4[0] < 0)))?0:((iTempPerm0)?(fConst4 * fRec4[0]):1)):((int((fRec4[0] < fConst2)))?((fConst4 * (0 - (fRec4[0] - fConst3))) + 1):0))));
			fRec0[0] = (fTempPerm1 - ((fSlow17 * fRec0[1]) + (fConst8 * fRec0[2])));
			fRec5[0] = (fTempPerm1 - ((fSlow19 * fRec5[1]) + (fConst12 * fRec5[2])));
			fRec6[0] = (fTempPerm1 - ((fSlow20 * fRec6[1]) + (fConst15 * fRec6[2])));
			fRec7[0] = (fTempPerm1 - ((fSlow21 * fRec7[1]) + (fConst18 * fRec7[2])));
			fRec8[0] = (fTempPerm1 - ((fSlow22 * fRec8[1]) + (fConst21 * fRec8[2])));
			fRec9[0] = (fTempPerm1 - ((fSlow23 * fRec9[1]) + (fConst24 * fRec9[2])));
			fRec10[0] = (fTempPerm1 - ((fSlow24 * fRec10[1]) + (fConst27 * fRec10[2])));
			fRec11[0] = (fTempPerm1 - ((fSlow25 * fRec11[1]) + (fConst30 * fRec11[2])));
			fRec12[0] = (fTempPerm1 - ((fSlow26 * fRec12[1]) + (fConst33 * fRec12[2])));
			fRec13[0] = (fTempPerm1 - ((fSlow27 * fRec13[1]) + (fConst36 * fRec13[2])));
			fRec14[0] = (fTempPerm1 - ((fSlow28 * fRec14[1]) + (fConst39 * fRec14[2])));
			fRec15[0] = (fTempPerm1 - ((fSlow29 * fRec15[1]) + (fConst42 * fRec15[2])));
			fRec16[0] = (fTempPerm1 - ((fSlow30 * fRec16[1]) + (fConst45 * fRec16[2])));
			fRec17[0] = (fTempPerm1 - ((fSlow31 * fRec17[1]) + (fConst48 * fRec17[2])));
			fRec18[0] = (fTempPerm1 - ((fSlow32 * fRec18[1]) + (fConst51 * fRec18[2])));
			fRec19[0] = (fTempPerm1 - ((fSlow33 * fRec19[1]) + (fConst54 * fRec19[2])));
			fRec20[0] = (fTempPerm1 - ((fSlow34 * fRec20[1]) + (fConst57 * fRec20[2])));
			fRec21[0] = (fTempPerm1 - ((fSlow35 * fRec21[1]) + (fConst60 * fRec21[2])));
			fRec22[0] = (fTempPerm1 - ((fSlow36 * fRec22[1]) + (fConst63 * fRec22[2])));
			fRec23[0] = (fTempPerm1 - ((fSlow37 * fRec23[1]) + (fConst66 * fRec23[2])));
			fTempPerm2 = (0.050000000000000003f * ((((((((((((((((((((fRec0[0] + (0.25f * (fRec5[0] - fRec5[2]))) + (0.1111111111111111f * (fRec6[0] - fRec6[2]))) + (0.0625f * (fRec7[0] - fRec7[2]))) + (0.040000000000000008f * (fRec8[0] - fRec8[2]))) + (0.027777777777777776f * (fRec9[0] - fRec9[2]))) + (0.020408163265306121f * (fRec10[0] - fRec10[2]))) + (0.015625f * (fRec11[0] - fRec11[2]))) + (0.012345679012345678f * (fRec12[0] - fRec12[2]))) + (0.010000000000000002f * (fRec13[0] - fRec13[2]))) + (0.0082644628099173556f * (fRec14[0] - fRec14[2]))) + (0.0069444444444444441f * (fRec15[0] - fRec15[2]))) + (0.0059171597633136102f * (fRec16[0] - fRec16[2]))) + (0.0051020408163265302f * (fRec17[0] - fRec17[2]))) + (0.0044444444444444444f * (fRec18[0] - fRec18[2]))) + (0.00390625f * (fRec19[0] - fRec19[2]))) + (0.0034602076124567475f * (fRec20[0] - fRec20[2]))) + (0.0030864197530864196f * (fRec21[0] - fRec21[2]))) + (0.0027700831024930744f * (fRec22[0] - fRec22[2]))) + (0.0025000000000000005f * (fRec23[0] - fRec23[2]))) - fRec0[2]));
			output0[i] = (FAUSTFLOAT)fTempPerm2;
			output1[i] = (FAUSTFLOAT)fTempPerm2;
			// post processing
			fRec23[2] = fRec23[1]; fRec23[1] = fRec23[0];
			fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
			fRec21[2] = fRec21[1]; fRec21[1] = fRec21[0];
			fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
			fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
			fRec18[2] = fRec18[1]; fRec18[1] = fRec18[0];
			fRec17[2] = fRec17[1]; fRec17[1] = fRec17[0];
			fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
			fRec15[2] = fRec15[1]; fRec15[1] = fRec15[0];
			fRec14[2] = fRec14[1]; fRec14[1] = fRec14[0];
			fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
			fRec12[2] = fRec12[1]; fRec12[1] = fRec12[0];
			fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
			fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
			fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
			fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
			fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
			fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
			fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
			fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
			fRec4[1] = fRec4[0];
			fVec1[1] = fVec1[0];
			fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
			fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
			iRec3[1] = iRec3[0];
			fVec0[1] = fVec0[0];
		}
	}
};


