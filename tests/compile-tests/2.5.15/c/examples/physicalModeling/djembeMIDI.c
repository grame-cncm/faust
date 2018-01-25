/* ------------------------------------------------------------
copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
license: "MIT"
name: "DjembeMIDI"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: c, -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__


typedef struct Soundfile Soundfile;

#include "gui/CInterface.h"

#ifndef max
// define min and max (the result doesn't matter)
#define max(a,b) (a)
#define min(a,b) (b)
#endif

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 


#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
#include <stdlib.h>

static float mydsp_faustpower2_f(float value) {
	return (value * value);
	
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif
#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

typedef struct {
	
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider2;
	int iRec3[2];
	float fRec2[3];
	float fRec1[3];
	FAUSTFLOAT fButton0;
	float fVec0[2];
	float fConst2;
	FAUSTFLOAT fHslider3;
	float fVec1[2];
	float fRec4[2];
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	float fConst7;
	FAUSTFLOAT fHslider4;
	float fConst8;
	float fRec0[3];
	float fConst9;
	float fConst10;
	float fConst11;
	float fRec5[3];
	float fConst12;
	float fConst13;
	float fConst14;
	float fRec6[3];
	float fConst15;
	float fConst16;
	float fConst17;
	float fRec7[3];
	float fConst18;
	float fConst19;
	float fConst20;
	float fRec8[3];
	float fConst21;
	float fConst22;
	float fConst23;
	float fRec9[3];
	float fConst24;
	float fConst25;
	float fConst26;
	float fRec10[3];
	float fConst27;
	float fConst28;
	float fConst29;
	float fRec11[3];
	float fConst30;
	float fConst31;
	float fConst32;
	float fRec12[3];
	float fConst33;
	float fConst34;
	float fConst35;
	float fRec13[3];
	float fConst36;
	float fConst37;
	float fConst38;
	float fRec14[3];
	float fConst39;
	float fConst40;
	float fConst41;
	float fRec15[3];
	float fConst42;
	float fConst43;
	float fConst44;
	float fRec16[3];
	float fConst45;
	float fConst46;
	float fConst47;
	float fRec17[3];
	float fConst48;
	float fConst49;
	float fConst50;
	float fRec18[3];
	float fConst51;
	float fConst52;
	float fConst53;
	float fRec19[3];
	float fConst54;
	float fConst55;
	float fConst56;
	float fRec20[3];
	float fConst57;
	float fConst58;
	float fConst59;
	float fRec21[3];
	float fConst60;
	float fConst61;
	float fConst62;
	float fRec22[3];
	float fConst63;
	float fConst64;
	float fConst65;
	float fRec23[3];
	
} mydsp;

mydsp* newmydsp() { 
	mydsp* dsp = (mydsp*)malloc(sizeof(mydsp));
	return dsp;
}

void deletemydsp(mydsp* dsp) { 
	free(dsp);
}

void metadatamydsp(MetaGlue* m) { 
	m->declare(m->metaInterface, "basics.lib/name", "Faust Basic Element Library");
	m->declare(m->metaInterface, "basics.lib/version", "0.0");
	m->declare(m->metaInterface, "copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
	m->declare(m->metaInterface, "description", "Simple MIDI-controllable djembe physical model.");
	m->declare(m->metaInterface, "envelopes.lib/author", "GRAME");
	m->declare(m->metaInterface, "envelopes.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "envelopes.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "envelopes.lib/name", "Faust Envelope Library");
	m->declare(m->metaInterface, "envelopes.lib/version", "0.0");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "license", "MIT");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "DjembeMIDI");
	m->declare(m->metaInterface, "noises.lib/name", "Faust Noise Generator Library");
	m->declare(m->metaInterface, "noises.lib/version", "0.0");
}

int getSampleRatemydsp(mydsp* dsp) { return dsp->fSamplingFreq; }

int getNumInputsmydsp(mydsp* dsp) {
	return 0;
	
}
int getNumOutputsmydsp(mydsp* dsp) {
	return 2;
	
}
int getInputRatemydsp(mydsp* dsp, int channel) {
	int rate;
	switch (channel) {
		default: {
			rate = -1;
			break;
		}
		
	}
	return rate;
	
}
int getOutputRatemydsp(mydsp* dsp, int channel) {
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

void classInitmydsp(int samplingFreq) {
	
}

void instanceResetUserInterfacemydsp(mydsp* dsp) {
	dsp->fHslider0 = (FAUSTFLOAT)1.0f;
	dsp->fHslider1 = (FAUSTFLOAT)1.0f;
	dsp->fHslider2 = (FAUSTFLOAT)0.5f;
	dsp->fButton0 = (FAUSTFLOAT)0.0f;
	dsp->fHslider3 = (FAUSTFLOAT)0.5f;
	dsp->fHslider4 = (FAUSTFLOAT)60.0f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			dsp->iRec3[l0] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 3); l1 = (l1 + 1)) {
			dsp->fRec2[l1] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 3); l2 = (l2 + 1)) {
			dsp->fRec1[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			dsp->fVec0[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			dsp->fVec1[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			dsp->fRec4[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 3); l6 = (l6 + 1)) {
			dsp->fRec0[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			dsp->fRec5[l7] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
			dsp->fRec6[l8] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 3); l9 = (l9 + 1)) {
			dsp->fRec7[l9] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 3); l10 = (l10 + 1)) {
			dsp->fRec8[l10] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 3); l11 = (l11 + 1)) {
			dsp->fRec9[l11] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 3); l12 = (l12 + 1)) {
			dsp->fRec10[l12] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l13;
		for (l13 = 0; (l13 < 3); l13 = (l13 + 1)) {
			dsp->fRec11[l13] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l14;
		for (l14 = 0; (l14 < 3); l14 = (l14 + 1)) {
			dsp->fRec12[l14] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l15;
		for (l15 = 0; (l15 < 3); l15 = (l15 + 1)) {
			dsp->fRec13[l15] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l16;
		for (l16 = 0; (l16 < 3); l16 = (l16 + 1)) {
			dsp->fRec14[l16] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l17;
		for (l17 = 0; (l17 < 3); l17 = (l17 + 1)) {
			dsp->fRec15[l17] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l18;
		for (l18 = 0; (l18 < 3); l18 = (l18 + 1)) {
			dsp->fRec16[l18] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l19;
		for (l19 = 0; (l19 < 3); l19 = (l19 + 1)) {
			dsp->fRec17[l19] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l20;
		for (l20 = 0; (l20 < 3); l20 = (l20 + 1)) {
			dsp->fRec18[l20] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l21;
		for (l21 = 0; (l21 < 3); l21 = (l21 + 1)) {
			dsp->fRec19[l21] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l22;
		for (l22 = 0; (l22 < 3); l22 = (l22 + 1)) {
			dsp->fRec20[l22] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l23;
		for (l23 = 0; (l23 < 3); l23 = (l23 + 1)) {
			dsp->fRec21[l23] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l24;
		for (l24 = 0; (l24 < 3); l24 = (l24 + 1)) {
			dsp->fRec22[l24] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l25;
		for (l25 = 0; (l25 < 3); l25 = (l25 + 1)) {
			dsp->fRec23[l25] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = (3.14159274f / dsp->fConst0);
	dsp->fConst2 = (0.00400000019f * dsp->fConst0);
	dsp->fConst3 = (0.00200000009f * dsp->fConst0);
	dsp->fConst4 = (500.0f / dsp->fConst0);
	dsp->fConst5 = powf(0.00100000005f, (1.0f / (0.600000024f * dsp->fConst0)));
	dsp->fConst6 = (0.0f - (2.0f * dsp->fConst5));
	dsp->fConst7 = (6.28318548f / dsp->fConst0);
	dsp->fConst8 = mydsp_faustpower2_f(dsp->fConst5);
	dsp->fConst9 = powf(0.00100000005f, (1.0f / (0.569999993f * dsp->fConst0)));
	dsp->fConst10 = (0.0f - (2.0f * dsp->fConst9));
	dsp->fConst11 = mydsp_faustpower2_f(dsp->fConst9);
	dsp->fConst12 = powf(0.00100000005f, (1.0f / (0.540000021f * dsp->fConst0)));
	dsp->fConst13 = (0.0f - (2.0f * dsp->fConst12));
	dsp->fConst14 = mydsp_faustpower2_f(dsp->fConst12);
	dsp->fConst15 = powf(0.00100000005f, (1.0f / (0.50999999f * dsp->fConst0)));
	dsp->fConst16 = (0.0f - (2.0f * dsp->fConst15));
	dsp->fConst17 = mydsp_faustpower2_f(dsp->fConst15);
	dsp->fConst18 = powf(0.00100000005f, (1.0f / (0.479999989f * dsp->fConst0)));
	dsp->fConst19 = (0.0f - (2.0f * dsp->fConst18));
	dsp->fConst20 = mydsp_faustpower2_f(dsp->fConst18);
	dsp->fConst21 = powf(0.00100000005f, (1.0f / (0.449999988f * dsp->fConst0)));
	dsp->fConst22 = (0.0f - (2.0f * dsp->fConst21));
	dsp->fConst23 = mydsp_faustpower2_f(dsp->fConst21);
	dsp->fConst24 = powf(0.00100000005f, (1.0f / (0.419999987f * dsp->fConst0)));
	dsp->fConst25 = (0.0f - (2.0f * dsp->fConst24));
	dsp->fConst26 = mydsp_faustpower2_f(dsp->fConst24);
	dsp->fConst27 = powf(0.00100000005f, (1.0f / (0.389999986f * dsp->fConst0)));
	dsp->fConst28 = (0.0f - (2.0f * dsp->fConst27));
	dsp->fConst29 = mydsp_faustpower2_f(dsp->fConst27);
	dsp->fConst30 = powf(0.00100000005f, (1.0f / (0.360000014f * dsp->fConst0)));
	dsp->fConst31 = (0.0f - (2.0f * dsp->fConst30));
	dsp->fConst32 = mydsp_faustpower2_f(dsp->fConst30);
	dsp->fConst33 = powf(0.00100000005f, (1.0f / (0.330000013f * dsp->fConst0)));
	dsp->fConst34 = (0.0f - (2.0f * dsp->fConst33));
	dsp->fConst35 = mydsp_faustpower2_f(dsp->fConst33);
	dsp->fConst36 = powf(0.00100000005f, (1.0f / (0.300000012f * dsp->fConst0)));
	dsp->fConst37 = (0.0f - (2.0f * dsp->fConst36));
	dsp->fConst38 = mydsp_faustpower2_f(dsp->fConst36);
	dsp->fConst39 = powf(0.00100000005f, (1.0f / (0.270000011f * dsp->fConst0)));
	dsp->fConst40 = (0.0f - (2.0f * dsp->fConst39));
	dsp->fConst41 = mydsp_faustpower2_f(dsp->fConst39);
	dsp->fConst42 = powf(0.00100000005f, (1.0f / (0.239999995f * dsp->fConst0)));
	dsp->fConst43 = (0.0f - (2.0f * dsp->fConst42));
	dsp->fConst44 = mydsp_faustpower2_f(dsp->fConst42);
	dsp->fConst45 = powf(0.00100000005f, (1.0f / (0.209999993f * dsp->fConst0)));
	dsp->fConst46 = (0.0f - (2.0f * dsp->fConst45));
	dsp->fConst47 = mydsp_faustpower2_f(dsp->fConst45);
	dsp->fConst48 = powf(0.00100000005f, (1.0f / (0.180000007f * dsp->fConst0)));
	dsp->fConst49 = (0.0f - (2.0f * dsp->fConst48));
	dsp->fConst50 = mydsp_faustpower2_f(dsp->fConst48);
	dsp->fConst51 = powf(0.00100000005f, (1.0f / (0.150000006f * dsp->fConst0)));
	dsp->fConst52 = (0.0f - (2.0f * dsp->fConst51));
	dsp->fConst53 = mydsp_faustpower2_f(dsp->fConst51);
	dsp->fConst54 = powf(0.00100000005f, (1.0f / (0.119999997f * dsp->fConst0)));
	dsp->fConst55 = (0.0f - (2.0f * dsp->fConst54));
	dsp->fConst56 = mydsp_faustpower2_f(dsp->fConst54);
	dsp->fConst57 = powf(0.00100000005f, (1.0f / (0.0900000036f * dsp->fConst0)));
	dsp->fConst58 = (0.0f - (2.0f * dsp->fConst57));
	dsp->fConst59 = mydsp_faustpower2_f(dsp->fConst57);
	dsp->fConst60 = powf(0.00100000005f, (1.0f / (0.0599999987f * dsp->fConst0)));
	dsp->fConst61 = (0.0f - (2.0f * dsp->fConst60));
	dsp->fConst62 = mydsp_faustpower2_f(dsp->fConst60);
	dsp->fConst63 = powf(0.00100000005f, (1.0f / (0.0299999993f * dsp->fConst0)));
	dsp->fConst64 = (0.0f - (2.0f * dsp->fConst63));
	dsp->fConst65 = mydsp_faustpower2_f(dsp->fConst63);
	
}

void instanceInitmydsp(mydsp* dsp, int samplingFreq) {
	instanceConstantsmydsp(dsp, samplingFreq);
	instanceResetUserInterfacemydsp(dsp);
	instanceClearmydsp(dsp);
}

void initmydsp(mydsp* dsp, int samplingFreq) {
	classInitmydsp(samplingFreq);
	instanceInitmydsp(dsp, samplingFreq);
}

void buildUserInterfacemydsp(mydsp* dsp, UIGlue* ui_interface) {
	ui_interface->openVerticalBox(ui_interface->uiInterface, "djembe");
	ui_interface->declare(ui_interface->uiInterface, 0, "0", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "midi");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "freq", &dsp->fHslider4, 60.0f, 50.0f, 100.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "gain", &dsp->fHslider1, 1.0f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "1", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "otherParams");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "midi", "ctrl 1");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "strikePosition", &dsp->fHslider2, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "strikeSharpness", &dsp->fHslider3, 0.5f, 0.00999999978f, 5.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "outGain", &dsp->fHslider0, 1.0f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fButton0, "3", "");
	ui_interface->addButton(ui_interface->uiInterface, "gate", &dsp->fButton0);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	float fSlow0 = (0.0500000007f * (float)dsp->fHslider0);
	float fSlow1 = (float)dsp->fHslider2;
	float fSlow2 = tanf((dsp->fConst1 * ((15000.0f * fSlow1) + 500.0f)));
	float fSlow3 = (1.0f / fSlow2);
	float fSlow4 = (((fSlow3 + 1.41421354f) / fSlow2) + 1.0f);
	float fSlow5 = ((float)dsp->fHslider1 / fSlow4);
	float fSlow6 = tanf((dsp->fConst1 * ((500.0f * fSlow1) + 40.0f)));
	float fSlow7 = (1.0f / fSlow6);
	float fSlow8 = (1.0f / (((fSlow7 + 1.41421354f) / fSlow6) + 1.0f));
	float fSlow9 = (1.0f / mydsp_faustpower2_f(fSlow6));
	float fSlow10 = (((fSlow7 + -1.41421354f) / fSlow6) + 1.0f);
	float fSlow11 = (2.0f * (1.0f - fSlow9));
	float fSlow12 = (2.0f * (0.0f - fSlow9));
	float fSlow13 = (1.0f / fSlow4);
	float fSlow14 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fSlow2))));
	float fSlow15 = (((fSlow3 + -1.41421354f) / fSlow2) + 1.0f);
	float fSlow16 = (float)dsp->fButton0;
	float fSlow17 = (float)dsp->fHslider3;
	float fSlow18 = (dsp->fConst2 * fSlow17);
	float fSlow19 = (dsp->fConst3 * fSlow17);
	float fSlow20 = (dsp->fConst4 / fSlow17);
	float fSlow21 = (float)dsp->fHslider4;
	float fSlow22 = (dsp->fConst6 * cosf((dsp->fConst7 * fSlow21)));
	float fSlow23 = (dsp->fConst10 * cosf((dsp->fConst7 * (fSlow21 + 200.0f))));
	float fSlow24 = (dsp->fConst13 * cosf((dsp->fConst7 * (fSlow21 + 400.0f))));
	float fSlow25 = (dsp->fConst16 * cosf((dsp->fConst7 * (fSlow21 + 600.0f))));
	float fSlow26 = (dsp->fConst19 * cosf((dsp->fConst7 * (fSlow21 + 800.0f))));
	float fSlow27 = (dsp->fConst22 * cosf((dsp->fConst7 * (fSlow21 + 1000.0f))));
	float fSlow28 = (dsp->fConst25 * cosf((dsp->fConst7 * (fSlow21 + 1200.0f))));
	float fSlow29 = (dsp->fConst28 * cosf((dsp->fConst7 * (fSlow21 + 1400.0f))));
	float fSlow30 = (dsp->fConst31 * cosf((dsp->fConst7 * (fSlow21 + 1600.0f))));
	float fSlow31 = (dsp->fConst34 * cosf((dsp->fConst7 * (fSlow21 + 1800.0f))));
	float fSlow32 = (dsp->fConst37 * cosf((dsp->fConst7 * (fSlow21 + 2000.0f))));
	float fSlow33 = (dsp->fConst40 * cosf((dsp->fConst7 * (fSlow21 + 2200.0f))));
	float fSlow34 = (dsp->fConst43 * cosf((dsp->fConst7 * (fSlow21 + 2400.0f))));
	float fSlow35 = (dsp->fConst46 * cosf((dsp->fConst7 * (fSlow21 + 2600.0f))));
	float fSlow36 = (dsp->fConst49 * cosf((dsp->fConst7 * (fSlow21 + 2800.0f))));
	float fSlow37 = (dsp->fConst52 * cosf((dsp->fConst7 * (fSlow21 + 3000.0f))));
	float fSlow38 = (dsp->fConst55 * cosf((dsp->fConst7 * (fSlow21 + 3200.0f))));
	float fSlow39 = (dsp->fConst58 * cosf((dsp->fConst7 * (fSlow21 + 3400.0f))));
	float fSlow40 = (dsp->fConst61 * cosf((dsp->fConst7 * (fSlow21 + 3600.0f))));
	float fSlow41 = (dsp->fConst64 * cosf((dsp->fConst7 * (fSlow21 + 3800.0f))));
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->iRec3[0] = ((1103515245 * dsp->iRec3[1]) + 12345);
			dsp->fRec2[0] = ((4.65661287e-10f * (float)dsp->iRec3[0]) - (fSlow8 * ((fSlow10 * dsp->fRec2[2]) + (fSlow11 * dsp->fRec2[1]))));
			dsp->fRec1[0] = ((fSlow8 * (((fSlow9 * dsp->fRec2[0]) + (fSlow12 * dsp->fRec2[1])) + (fSlow9 * dsp->fRec2[2]))) - (fSlow13 * ((fSlow14 * dsp->fRec1[1]) + (fSlow15 * dsp->fRec1[2]))));
			dsp->fVec0[0] = fSlow16;
			dsp->fVec1[0] = fSlow17;
			dsp->fRec4[0] = ((((fSlow16 - dsp->fVec0[1]) > 0.0f) > 0)?0.0f:min(fSlow18, ((dsp->fRec4[1] + (dsp->fConst2 * (fSlow17 - dsp->fVec1[1]))) + 1.0f)));
			int iTemp0 = (dsp->fRec4[0] < fSlow19);
			float fTemp1 = (fSlow5 * ((dsp->fRec1[2] + (dsp->fRec1[0] + (2.0f * dsp->fRec1[1]))) * (iTemp0?((dsp->fRec4[0] < 0.0f)?0.0f:(iTemp0?(fSlow20 * dsp->fRec4[0]):1.0f)):((dsp->fRec4[0] < fSlow18)?((fSlow20 * (0.0f - (dsp->fRec4[0] - fSlow19))) + 1.0f):0.0f))));
			dsp->fRec0[0] = (fTemp1 - ((fSlow22 * dsp->fRec0[1]) + (dsp->fConst8 * dsp->fRec0[2])));
			dsp->fRec5[0] = (fTemp1 - ((fSlow23 * dsp->fRec5[1]) + (dsp->fConst11 * dsp->fRec5[2])));
			dsp->fRec6[0] = (fTemp1 - ((fSlow24 * dsp->fRec6[1]) + (dsp->fConst14 * dsp->fRec6[2])));
			dsp->fRec7[0] = (fTemp1 - ((fSlow25 * dsp->fRec7[1]) + (dsp->fConst17 * dsp->fRec7[2])));
			dsp->fRec8[0] = (fTemp1 - ((fSlow26 * dsp->fRec8[1]) + (dsp->fConst20 * dsp->fRec8[2])));
			dsp->fRec9[0] = (fTemp1 - ((fSlow27 * dsp->fRec9[1]) + (dsp->fConst23 * dsp->fRec9[2])));
			dsp->fRec10[0] = (fTemp1 - ((fSlow28 * dsp->fRec10[1]) + (dsp->fConst26 * dsp->fRec10[2])));
			dsp->fRec11[0] = (fTemp1 - ((fSlow29 * dsp->fRec11[1]) + (dsp->fConst29 * dsp->fRec11[2])));
			dsp->fRec12[0] = (fTemp1 - ((fSlow30 * dsp->fRec12[1]) + (dsp->fConst32 * dsp->fRec12[2])));
			dsp->fRec13[0] = (fTemp1 - ((fSlow31 * dsp->fRec13[1]) + (dsp->fConst35 * dsp->fRec13[2])));
			dsp->fRec14[0] = (fTemp1 - ((fSlow32 * dsp->fRec14[1]) + (dsp->fConst38 * dsp->fRec14[2])));
			dsp->fRec15[0] = (fTemp1 - ((fSlow33 * dsp->fRec15[1]) + (dsp->fConst41 * dsp->fRec15[2])));
			dsp->fRec16[0] = (fTemp1 - ((fSlow34 * dsp->fRec16[1]) + (dsp->fConst44 * dsp->fRec16[2])));
			dsp->fRec17[0] = (fTemp1 - ((fSlow35 * dsp->fRec17[1]) + (dsp->fConst47 * dsp->fRec17[2])));
			dsp->fRec18[0] = (fTemp1 - ((fSlow36 * dsp->fRec18[1]) + (dsp->fConst50 * dsp->fRec18[2])));
			dsp->fRec19[0] = (fTemp1 - ((fSlow37 * dsp->fRec19[1]) + (dsp->fConst53 * dsp->fRec19[2])));
			dsp->fRec20[0] = (fTemp1 - ((fSlow38 * dsp->fRec20[1]) + (dsp->fConst56 * dsp->fRec20[2])));
			dsp->fRec21[0] = (fTemp1 - ((fSlow39 * dsp->fRec21[1]) + (dsp->fConst59 * dsp->fRec21[2])));
			dsp->fRec22[0] = (fTemp1 - ((fSlow40 * dsp->fRec22[1]) + (dsp->fConst62 * dsp->fRec22[2])));
			dsp->fRec23[0] = (fTemp1 - ((fSlow41 * dsp->fRec23[1]) + (dsp->fConst65 * dsp->fRec23[2])));
			float fTemp2 = (fSlow0 * ((((((((((((((((((((dsp->fRec0[0] + (0.25f * (dsp->fRec5[0] - dsp->fRec5[2]))) + (0.111111112f * (dsp->fRec6[0] - dsp->fRec6[2]))) + (0.0625f * (dsp->fRec7[0] - dsp->fRec7[2]))) + (0.0399999991f * (dsp->fRec8[0] - dsp->fRec8[2]))) + (0.027777778f * (dsp->fRec9[0] - dsp->fRec9[2]))) + (0.0204081628f * (dsp->fRec10[0] - dsp->fRec10[2]))) + (0.015625f * (dsp->fRec11[0] - dsp->fRec11[2]))) + (0.0123456791f * (dsp->fRec12[0] - dsp->fRec12[2]))) + (0.00999999978f * (dsp->fRec13[0] - dsp->fRec13[2]))) + (0.00826446246f * (dsp->fRec14[0] - dsp->fRec14[2]))) + (0.0069444445f * (dsp->fRec15[0] - dsp->fRec15[2]))) + (0.00591715984f * (dsp->fRec16[0] - dsp->fRec16[2]))) + (0.00510204071f * (dsp->fRec17[0] - dsp->fRec17[2]))) + (0.00444444455f * (dsp->fRec18[0] - dsp->fRec18[2]))) + (0.00390625f * (dsp->fRec19[0] - dsp->fRec19[2]))) + (0.00346020772f * (dsp->fRec20[0] - dsp->fRec20[2]))) + (0.00308641978f * (dsp->fRec21[0] - dsp->fRec21[2]))) + (0.00277008303f * (dsp->fRec22[0] - dsp->fRec22[2]))) + (0.00249999994f * (dsp->fRec23[0] - dsp->fRec23[2]))) - dsp->fRec0[2]));
			output0[i] = (FAUSTFLOAT)fTemp2;
			output1[i] = (FAUSTFLOAT)fTemp2;
			dsp->iRec3[1] = dsp->iRec3[0];
			dsp->fRec2[2] = dsp->fRec2[1];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec1[2] = dsp->fRec1[1];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fVec0[1] = dsp->fVec0[0];
			dsp->fVec1[1] = dsp->fVec1[0];
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fRec0[2] = dsp->fRec0[1];
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec5[2] = dsp->fRec5[1];
			dsp->fRec5[1] = dsp->fRec5[0];
			dsp->fRec6[2] = dsp->fRec6[1];
			dsp->fRec6[1] = dsp->fRec6[0];
			dsp->fRec7[2] = dsp->fRec7[1];
			dsp->fRec7[1] = dsp->fRec7[0];
			dsp->fRec8[2] = dsp->fRec8[1];
			dsp->fRec8[1] = dsp->fRec8[0];
			dsp->fRec9[2] = dsp->fRec9[1];
			dsp->fRec9[1] = dsp->fRec9[0];
			dsp->fRec10[2] = dsp->fRec10[1];
			dsp->fRec10[1] = dsp->fRec10[0];
			dsp->fRec11[2] = dsp->fRec11[1];
			dsp->fRec11[1] = dsp->fRec11[0];
			dsp->fRec12[2] = dsp->fRec12[1];
			dsp->fRec12[1] = dsp->fRec12[0];
			dsp->fRec13[2] = dsp->fRec13[1];
			dsp->fRec13[1] = dsp->fRec13[0];
			dsp->fRec14[2] = dsp->fRec14[1];
			dsp->fRec14[1] = dsp->fRec14[0];
			dsp->fRec15[2] = dsp->fRec15[1];
			dsp->fRec15[1] = dsp->fRec15[0];
			dsp->fRec16[2] = dsp->fRec16[1];
			dsp->fRec16[1] = dsp->fRec16[0];
			dsp->fRec17[2] = dsp->fRec17[1];
			dsp->fRec17[1] = dsp->fRec17[0];
			dsp->fRec18[2] = dsp->fRec18[1];
			dsp->fRec18[1] = dsp->fRec18[0];
			dsp->fRec19[2] = dsp->fRec19[1];
			dsp->fRec19[1] = dsp->fRec19[0];
			dsp->fRec20[2] = dsp->fRec20[1];
			dsp->fRec20[1] = dsp->fRec20[0];
			dsp->fRec21[2] = dsp->fRec21[1];
			dsp->fRec21[1] = dsp->fRec21[0];
			dsp->fRec22[2] = dsp->fRec22[1];
			dsp->fRec22[1] = dsp->fRec22[0];
			dsp->fRec23[2] = dsp->fRec23[1];
			dsp->fRec23[1] = dsp->fRec23[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
