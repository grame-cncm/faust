//----------------------------------------------------------
// copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
// license: "MIT"
// name: "DjembeMIDI"
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
	FAUSTFLOAT 	fslider1;
	float 	fConst0;
	float 	fConst1;
	FAUSTFLOAT 	fslider2;
	int 	iRec3[2];
	float 	fRec2[3];
	float 	fRec1[3];
	FAUSTFLOAT 	fbutton0;
	float 	fVec0[2];
	float 	fConst2;
	FAUSTFLOAT 	fslider3;
	float 	fVec1[2];
	float 	fRec4[2];
	float 	fConst3;
	int 	iTempPerm0;
	float 	fConst4;
	float 	fTempPerm1;
	float 	fConst5;
	float 	fConst6;
	float 	fConst7;
	FAUSTFLOAT 	fslider4;
	float 	fConst8;
	float 	fRec0[3];
	float 	fConst9;
	float 	fConst10;
	float 	fConst11;
	float 	fRec5[3];
	float 	fConst12;
	float 	fConst13;
	float 	fConst14;
	float 	fRec6[3];
	float 	fConst15;
	float 	fConst16;
	float 	fConst17;
	float 	fRec7[3];
	float 	fConst18;
	float 	fConst19;
	float 	fConst20;
	float 	fRec8[3];
	float 	fConst21;
	float 	fConst22;
	float 	fConst23;
	float 	fRec9[3];
	float 	fConst24;
	float 	fConst25;
	float 	fConst26;
	float 	fRec10[3];
	float 	fConst27;
	float 	fConst28;
	float 	fConst29;
	float 	fRec11[3];
	float 	fConst30;
	float 	fConst31;
	float 	fConst32;
	float 	fRec12[3];
	float 	fConst33;
	float 	fConst34;
	float 	fConst35;
	float 	fRec13[3];
	float 	fConst36;
	float 	fConst37;
	float 	fConst38;
	float 	fRec14[3];
	float 	fConst39;
	float 	fConst40;
	float 	fConst41;
	float 	fRec15[3];
	float 	fConst42;
	float 	fConst43;
	float 	fConst44;
	float 	fRec16[3];
	float 	fConst45;
	float 	fConst46;
	float 	fConst47;
	float 	fRec17[3];
	float 	fConst48;
	float 	fConst49;
	float 	fConst50;
	float 	fRec18[3];
	float 	fConst51;
	float 	fConst52;
	float 	fConst53;
	float 	fRec19[3];
	float 	fConst54;
	float 	fConst55;
	float 	fConst56;
	float 	fRec20[3];
	float 	fConst57;
	float 	fConst58;
	float 	fConst59;
	float 	fRec21[3];
	float 	fConst60;
	float 	fConst61;
	float 	fConst62;
	float 	fRec22[3];
	float 	fConst63;
	float 	fConst64;
	float 	fConst65;
	float 	fRec23[3];
	float 	fTempPerm2;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
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

	virtual int getNumInputs() { return 0; }
	virtual int getNumOutputs() { return 2; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(192000.0f, max(1.0f, (float)fSamplingFreq));
		fConst1 = (3.1415926535897931f / fConst0);
		fConst2 = (0.0040000000000000001f * fConst0);
		fConst3 = (0.002f * fConst0);
		iTempPerm0 = 0;
		fConst4 = (500.0f / fConst0);
		fTempPerm1 = 0;
		fConst5 = powf(0.001f,(1.0f / float((0.59999999999999998f * fConst0))));
		fConst6 = (0 - (2 * fConst5));
		fConst7 = (6.2831853071795862f / fConst0);
		fConst8 = faustpower<2>(fConst5);
		fConst9 = powf(0.001f,(1.0f / float((0.56999999999999995f * fConst0))));
		fConst10 = (0 - (2 * fConst9));
		fConst11 = faustpower<2>(fConst9);
		fConst12 = powf(0.001f,(1.0f / float((0.54000000000000004f * fConst0))));
		fConst13 = (0 - (2 * fConst12));
		fConst14 = faustpower<2>(fConst12);
		fConst15 = powf(0.001f,(1.0f / float((0.51000000000000001f * fConst0))));
		fConst16 = (0 - (2 * fConst15));
		fConst17 = faustpower<2>(fConst15);
		fConst18 = powf(0.001f,(1.0f / float((0.47999999999999998f * fConst0))));
		fConst19 = (0 - (2 * fConst18));
		fConst20 = faustpower<2>(fConst18);
		fConst21 = powf(0.001f,(1.0f / float((0.44999999999999996f * fConst0))));
		fConst22 = (0 - (2 * fConst21));
		fConst23 = faustpower<2>(fConst21);
		fConst24 = powf(0.001f,(1.0f / float((0.41999999999999998f * fConst0))));
		fConst25 = (0 - (2 * fConst24));
		fConst26 = faustpower<2>(fConst24);
		fConst27 = powf(0.001f,(1.0f / float((0.39000000000000001f * fConst0))));
		fConst28 = (0 - (2 * fConst27));
		fConst29 = faustpower<2>(fConst27);
		fConst30 = powf(0.001f,(1.0f / float((0.35999999999999999f * fConst0))));
		fConst31 = (0 - (2 * fConst30));
		fConst32 = faustpower<2>(fConst30);
		fConst33 = powf(0.001f,(1.0f / float((0.32999999999999996f * fConst0))));
		fConst34 = (0 - (2 * fConst33));
		fConst35 = faustpower<2>(fConst33);
		fConst36 = powf(0.001f,(1.0f / float((0.29999999999999999f * fConst0))));
		fConst37 = (0 - (2 * fConst36));
		fConst38 = faustpower<2>(fConst36);
		fConst39 = powf(0.001f,(1.0f / float((0.27000000000000002f * fConst0))));
		fConst40 = (0 - (2 * fConst39));
		fConst41 = faustpower<2>(fConst39);
		fConst42 = powf(0.001f,(1.0f / float((0.23999999999999999f * fConst0))));
		fConst43 = (0 - (2 * fConst42));
		fConst44 = faustpower<2>(fConst42);
		fConst45 = powf(0.001f,(1.0f / float((0.20999999999999999f * fConst0))));
		fConst46 = (0 - (2 * fConst45));
		fConst47 = faustpower<2>(fConst45);
		fConst48 = powf(0.001f,(1.0f / float((0.17999999999999999f * fConst0))));
		fConst49 = (0 - (2 * fConst48));
		fConst50 = faustpower<2>(fConst48);
		fConst51 = powf(0.001f,(1.0f / float((0.14999999999999999f * fConst0))));
		fConst52 = (0 - (2 * fConst51));
		fConst53 = faustpower<2>(fConst51);
		fConst54 = powf(0.001f,(1.0f / float((0.12f * fConst0))));
		fConst55 = (0 - (2 * fConst54));
		fConst56 = faustpower<2>(fConst54);
		fConst57 = powf(0.001f,(1.0f / float((0.089999999999999997f * fConst0))));
		fConst58 = (0 - (2 * fConst57));
		fConst59 = faustpower<2>(fConst57);
		fConst60 = powf(0.001f,(1.0f / float((0.059999999999999998f * fConst0))));
		fConst61 = (0 - (2 * fConst60));
		fConst62 = faustpower<2>(fConst60);
		fConst63 = powf(0.001f,(1.0f / float((0.029999999999999999f * fConst0))));
		fConst64 = (0 - (2 * fConst63));
		fConst65 = faustpower<2>(fConst63);
		fTempPerm2 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 1.0f;
		fslider1 = 1.0f;
		fslider2 = 0.5f;
		fbutton0 = 0.0;
		fslider3 = 0.5f;
		fslider4 = 60.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) iRec3[i] = 0;
		for (int i=0; i<3; i++) fRec2[i] = 0;
		for (int i=0; i<3; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) fVec0[i] = 0;
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
		ui_interface->openVerticalBox("djembe");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("midi");
		ui_interface->declare(&fslider4, "0", "");
		ui_interface->declare(&fslider4, "style", "knob");
		ui_interface->addHorizontalSlider("freq", &fslider4, 60.0f, 50.0f, 100.0f, 0.01f);
		ui_interface->declare(&fslider1, "2", "");
		ui_interface->declare(&fslider1, "style", "knob");
		ui_interface->addHorizontalSlider("gain", &fslider1, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("otherParams");
		ui_interface->declare(&fslider2, "0", "");
		ui_interface->declare(&fslider2, "midi", "ctrl 1");
		ui_interface->declare(&fslider2, "style", "knob");
		ui_interface->addHorizontalSlider("strikePosition", &fslider2, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider3, "1", "");
		ui_interface->declare(&fslider3, "style", "knob");
		ui_interface->addHorizontalSlider("strikeSharpness", &fslider3, 0.5f, 0.01f, 5.0f, 0.01f);
		ui_interface->declare(&fslider0, "2", "");
		ui_interface->declare(&fslider0, "style", "knob");
		ui_interface->addHorizontalSlider("outGain", &fslider0, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->declare(&fbutton0, "3", "");
		ui_interface->addButton("gate", &fbutton0);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = (0.050000000000000003f * float(fslider0));
		float 	fSlow1 = float(fslider2);
		float 	fSlow2 = tanf((fConst1 * ((15000 * fSlow1) + 500)));
		float 	fSlow3 = (1.0f / fSlow2);
		float 	fSlow4 = (((fSlow3 + 1.4142135623730949f) / fSlow2) + 1);
		float 	fSlow5 = (float(fslider1) / fSlow4);
		float 	fSlow6 = tanf((fConst1 * ((500 * fSlow1) + 40)));
		float 	fSlow7 = (1.0f / fSlow6);
		float 	fSlow8 = (1.0f / (((fSlow7 + 1.4142135623730949f) / fSlow6) + 1));
		float 	fSlow9 = (1.0f / faustpower<2>(fSlow6));
		float 	fSlow10 = (((fSlow7 + -1.4142135623730949f) / fSlow6) + 1);
		float 	fSlow11 = (2 * (1 - fSlow9));
		float 	fSlow12 = (2 * (0 - fSlow9));
		float 	fSlow13 = (1.0f / fSlow4);
		float 	fSlow14 = (2 * (1 - (1.0f / faustpower<2>(fSlow2))));
		float 	fSlow15 = (((fSlow3 + -1.4142135623730949f) / fSlow2) + 1);
		float 	fSlow16 = float(fbutton0);
		float 	fSlow17 = float(fslider3);
		float 	fSlow18 = (fConst2 * fSlow17);
		float 	fSlow19 = (fConst3 * fSlow17);
		float 	fSlow20 = (fConst4 / fSlow17);
		float 	fSlow21 = float(fslider4);
		float 	fSlow22 = (fConst6 * cosf((fConst7 * fSlow21)));
		float 	fSlow23 = (fConst10 * cosf((fConst7 * (fSlow21 + 200))));
		float 	fSlow24 = (fConst13 * cosf((fConst7 * (fSlow21 + 400))));
		float 	fSlow25 = (fConst16 * cosf((fConst7 * (fSlow21 + 600))));
		float 	fSlow26 = (fConst19 * cosf((fConst7 * (fSlow21 + 800))));
		float 	fSlow27 = (fConst22 * cosf((fConst7 * (fSlow21 + 1000))));
		float 	fSlow28 = (fConst25 * cosf((fConst7 * (fSlow21 + 1200))));
		float 	fSlow29 = (fConst28 * cosf((fConst7 * (fSlow21 + 1400))));
		float 	fSlow30 = (fConst31 * cosf((fConst7 * (fSlow21 + 1600))));
		float 	fSlow31 = (fConst34 * cosf((fConst7 * (fSlow21 + 1800))));
		float 	fSlow32 = (fConst37 * cosf((fConst7 * (fSlow21 + 2000))));
		float 	fSlow33 = (fConst40 * cosf((fConst7 * (fSlow21 + 2200))));
		float 	fSlow34 = (fConst43 * cosf((fConst7 * (fSlow21 + 2400))));
		float 	fSlow35 = (fConst46 * cosf((fConst7 * (fSlow21 + 2600))));
		float 	fSlow36 = (fConst49 * cosf((fConst7 * (fSlow21 + 2800))));
		float 	fSlow37 = (fConst52 * cosf((fConst7 * (fSlow21 + 3000))));
		float 	fSlow38 = (fConst55 * cosf((fConst7 * (fSlow21 + 3200))));
		float 	fSlow39 = (fConst58 * cosf((fConst7 * (fSlow21 + 3400))));
		float 	fSlow40 = (fConst61 * cosf((fConst7 * (fSlow21 + 3600))));
		float 	fSlow41 = (fConst64 * cosf((fConst7 * (fSlow21 + 3800))));
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			iRec3[0] = ((1103515245 * iRec3[1]) + 12345);
			fRec2[0] = ((4.6566128752457969e-10f * iRec3[0]) - (fSlow8 * ((fSlow10 * fRec2[2]) + (fSlow11 * fRec2[1]))));
			fRec1[0] = ((fSlow8 * (((fSlow9 * fRec2[0]) + (fSlow12 * fRec2[1])) + (fSlow9 * fRec2[2]))) - (fSlow13 * ((fSlow14 * fRec1[1]) + (fSlow15 * fRec1[2]))));
			fVec0[0] = fSlow16;
			fVec1[0] = fSlow17;
			fRec4[0] = ((int((((fSlow16 - fVec0[1]) > 0) > 0)))?0:min(fSlow18, ((fRec4[1] + (fConst2 * (fSlow17 - fVec1[1]))) + 1)));
			iTempPerm0 = int((fRec4[0] < fSlow19));
			fTempPerm1 = (fSlow5 * ((fRec1[2] + (fRec1[0] + (2.0f * fRec1[1]))) * ((iTempPerm0)?((int((fRec4[0] < 0)))?0:((iTempPerm0)?(fSlow20 * fRec4[0]):1)):((int((fRec4[0] < fSlow18)))?((fSlow20 * (0 - (fRec4[0] - fSlow19))) + 1):0))));
			fRec0[0] = (fTempPerm1 - ((fSlow22 * fRec0[1]) + (fConst8 * fRec0[2])));
			fRec5[0] = (fTempPerm1 - ((fSlow23 * fRec5[1]) + (fConst11 * fRec5[2])));
			fRec6[0] = (fTempPerm1 - ((fSlow24 * fRec6[1]) + (fConst14 * fRec6[2])));
			fRec7[0] = (fTempPerm1 - ((fSlow25 * fRec7[1]) + (fConst17 * fRec7[2])));
			fRec8[0] = (fTempPerm1 - ((fSlow26 * fRec8[1]) + (fConst20 * fRec8[2])));
			fRec9[0] = (fTempPerm1 - ((fSlow27 * fRec9[1]) + (fConst23 * fRec9[2])));
			fRec10[0] = (fTempPerm1 - ((fSlow28 * fRec10[1]) + (fConst26 * fRec10[2])));
			fRec11[0] = (fTempPerm1 - ((fSlow29 * fRec11[1]) + (fConst29 * fRec11[2])));
			fRec12[0] = (fTempPerm1 - ((fSlow30 * fRec12[1]) + (fConst32 * fRec12[2])));
			fRec13[0] = (fTempPerm1 - ((fSlow31 * fRec13[1]) + (fConst35 * fRec13[2])));
			fRec14[0] = (fTempPerm1 - ((fSlow32 * fRec14[1]) + (fConst38 * fRec14[2])));
			fRec15[0] = (fTempPerm1 - ((fSlow33 * fRec15[1]) + (fConst41 * fRec15[2])));
			fRec16[0] = (fTempPerm1 - ((fSlow34 * fRec16[1]) + (fConst44 * fRec16[2])));
			fRec17[0] = (fTempPerm1 - ((fSlow35 * fRec17[1]) + (fConst47 * fRec17[2])));
			fRec18[0] = (fTempPerm1 - ((fSlow36 * fRec18[1]) + (fConst50 * fRec18[2])));
			fRec19[0] = (fTempPerm1 - ((fSlow37 * fRec19[1]) + (fConst53 * fRec19[2])));
			fRec20[0] = (fTempPerm1 - ((fSlow38 * fRec20[1]) + (fConst56 * fRec20[2])));
			fRec21[0] = (fTempPerm1 - ((fSlow39 * fRec21[1]) + (fConst59 * fRec21[2])));
			fRec22[0] = (fTempPerm1 - ((fSlow40 * fRec22[1]) + (fConst62 * fRec22[2])));
			fRec23[0] = (fTempPerm1 - ((fSlow41 * fRec23[1]) + (fConst65 * fRec23[2])));
			fTempPerm2 = (fSlow0 * ((((((((((((((((((((fRec0[0] + (0.25f * (fRec5[0] - fRec5[2]))) + (0.1111111111111111f * (fRec6[0] - fRec6[2]))) + (0.0625f * (fRec7[0] - fRec7[2]))) + (0.040000000000000008f * (fRec8[0] - fRec8[2]))) + (0.027777777777777776f * (fRec9[0] - fRec9[2]))) + (0.020408163265306121f * (fRec10[0] - fRec10[2]))) + (0.015625f * (fRec11[0] - fRec11[2]))) + (0.012345679012345678f * (fRec12[0] - fRec12[2]))) + (0.010000000000000002f * (fRec13[0] - fRec13[2]))) + (0.0082644628099173556f * (fRec14[0] - fRec14[2]))) + (0.0069444444444444441f * (fRec15[0] - fRec15[2]))) + (0.0059171597633136102f * (fRec16[0] - fRec16[2]))) + (0.0051020408163265302f * (fRec17[0] - fRec17[2]))) + (0.0044444444444444444f * (fRec18[0] - fRec18[2]))) + (0.00390625f * (fRec19[0] - fRec19[2]))) + (0.0034602076124567475f * (fRec20[0] - fRec20[2]))) + (0.0030864197530864196f * (fRec21[0] - fRec21[2]))) + (0.0027700831024930744f * (fRec22[0] - fRec22[2]))) + (0.0025000000000000005f * (fRec23[0] - fRec23[2]))) - fRec0[2]));
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
			fVec0[1] = fVec0[0];
			fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
			fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
			iRec3[1] = iRec3[0];
		}
	}
};


