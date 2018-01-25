/* ------------------------------------------------------------
name: "drums"
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
	
	int fSamplingFreq;
	float fConst0;
	float fVec0[2];
	float fConst1;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	int iRec3[2];
	float fRec2[3];
	float fRec1[3];
	FAUSTFLOAT fButton0;
	float fVec1[2];
	float fConst2;
	float fRec4[2];
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	float fConst7;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	float fConst8;
	float fRec0[3];
	float fConst9;
	float fConst10;
	float fConst11;
	float fConst12;
	float fRec5[3];
	float fConst13;
	float fConst14;
	float fConst15;
	float fRec6[3];
	float fConst16;
	float fConst17;
	float fConst18;
	float fRec7[3];
	float fConst19;
	float fConst20;
	float fConst21;
	float fRec8[3];
	float fConst22;
	float fConst23;
	float fConst24;
	float fRec9[3];
	float fConst25;
	float fConst26;
	float fConst27;
	float fRec10[3];
	float fConst28;
	float fConst29;
	float fConst30;
	float fRec11[3];
	float fConst31;
	float fConst32;
	float fConst33;
	float fRec12[3];
	float fConst34;
	float fConst35;
	float fConst36;
	float fRec13[3];
	float fConst37;
	float fConst38;
	float fConst39;
	float fRec14[3];
	float fConst40;
	float fConst41;
	float fConst42;
	float fRec15[3];
	float fConst43;
	float fConst44;
	float fConst45;
	float fRec16[3];
	float fConst46;
	float fConst47;
	float fConst48;
	float fRec17[3];
	float fConst49;
	float fConst50;
	float fConst51;
	float fRec18[3];
	float fConst52;
	float fConst53;
	float fConst54;
	float fRec19[3];
	float fConst55;
	float fConst56;
	float fConst57;
	float fRec20[3];
	float fConst58;
	float fConst59;
	float fConst60;
	float fRec21[3];
	float fConst61;
	float fConst62;
	float fConst63;
	float fRec22[3];
	float fConst64;
	float fConst65;
	float fConst66;
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
	m->declare(m->metaInterface, "envelopes.lib/author", "GRAME");
	m->declare(m->metaInterface, "envelopes.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "envelopes.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "envelopes.lib/name", "Faust Envelope Library");
	m->declare(m->metaInterface, "envelopes.lib/version", "0.0");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "interface", "SmartKeyboard{  'Number of Keyboards':'2',  'Keyboard 0 - Number of Keys':'2',  'Keyboard 1 - Number of Keys':'1',  'Keyboard 0 - Static Mode':'1',  'Keyboard 1 - Static Mode':'1',  'Keyboard 0 - Send X':'1',  'Keyboard 0 - Send Y':'1',  'Keyboard 1 - Send X':'1',  'Keyboard 1 - Send Y':'1',  'Keyboard 0 - Piano Keyboard':'0',  'Keyboard 1 - Piano Keyboard':'0',  'Keyboard 0 - Key 0 - Label':'High',  'Keyboard 0 - Key 1 - Label':'Mid',  'Keyboard 1 - Key 0 - Label':'Low' }");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "drums");
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
	dsp->fButton0 = (FAUSTFLOAT)0.0f;
	dsp->fHslider2 = (FAUSTFLOAT)0.0f;
	dsp->fHslider3 = (FAUSTFLOAT)0.0f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			dsp->fVec0[l0] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			dsp->iRec3[l1] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 3); l2 = (l2 + 1)) {
			dsp->fRec2[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 3); l3 = (l3 + 1)) {
			dsp->fRec1[l3] = 0.0f;
			
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
	dsp->fConst2 = (0.00200000009f * dsp->fConst0);
	dsp->fConst3 = (0.00100000005f * dsp->fConst0);
	dsp->fConst4 = (1000.0f / dsp->fConst0);
	dsp->fConst5 = powf(0.00100000005f, (1.0f / (0.600000024f * dsp->fConst0)));
	dsp->fConst6 = (0.0f - (2.0f * dsp->fConst5));
	dsp->fConst7 = (376.991119f / dsp->fConst0);
	dsp->fConst8 = mydsp_faustpower2_f(dsp->fConst5);
	dsp->fConst9 = powf(0.00100000005f, (1.0f / (0.569999993f * dsp->fConst0)));
	dsp->fConst10 = (0.0f - (2.0f * dsp->fConst9));
	dsp->fConst11 = (6.28318548f / dsp->fConst0);
	dsp->fConst12 = mydsp_faustpower2_f(dsp->fConst9);
	dsp->fConst13 = powf(0.00100000005f, (1.0f / (0.540000021f * dsp->fConst0)));
	dsp->fConst14 = (0.0f - (2.0f * dsp->fConst13));
	dsp->fConst15 = mydsp_faustpower2_f(dsp->fConst13);
	dsp->fConst16 = powf(0.00100000005f, (1.0f / (0.50999999f * dsp->fConst0)));
	dsp->fConst17 = (0.0f - (2.0f * dsp->fConst16));
	dsp->fConst18 = mydsp_faustpower2_f(dsp->fConst16);
	dsp->fConst19 = powf(0.00100000005f, (1.0f / (0.479999989f * dsp->fConst0)));
	dsp->fConst20 = (0.0f - (2.0f * dsp->fConst19));
	dsp->fConst21 = mydsp_faustpower2_f(dsp->fConst19);
	dsp->fConst22 = powf(0.00100000005f, (1.0f / (0.449999988f * dsp->fConst0)));
	dsp->fConst23 = (0.0f - (2.0f * dsp->fConst22));
	dsp->fConst24 = mydsp_faustpower2_f(dsp->fConst22);
	dsp->fConst25 = powf(0.00100000005f, (1.0f / (0.419999987f * dsp->fConst0)));
	dsp->fConst26 = (0.0f - (2.0f * dsp->fConst25));
	dsp->fConst27 = mydsp_faustpower2_f(dsp->fConst25);
	dsp->fConst28 = powf(0.00100000005f, (1.0f / (0.389999986f * dsp->fConst0)));
	dsp->fConst29 = (0.0f - (2.0f * dsp->fConst28));
	dsp->fConst30 = mydsp_faustpower2_f(dsp->fConst28);
	dsp->fConst31 = powf(0.00100000005f, (1.0f / (0.360000014f * dsp->fConst0)));
	dsp->fConst32 = (0.0f - (2.0f * dsp->fConst31));
	dsp->fConst33 = mydsp_faustpower2_f(dsp->fConst31);
	dsp->fConst34 = powf(0.00100000005f, (1.0f / (0.330000013f * dsp->fConst0)));
	dsp->fConst35 = (0.0f - (2.0f * dsp->fConst34));
	dsp->fConst36 = mydsp_faustpower2_f(dsp->fConst34);
	dsp->fConst37 = powf(0.00100000005f, (1.0f / (0.300000012f * dsp->fConst0)));
	dsp->fConst38 = (0.0f - (2.0f * dsp->fConst37));
	dsp->fConst39 = mydsp_faustpower2_f(dsp->fConst37);
	dsp->fConst40 = powf(0.00100000005f, (1.0f / (0.270000011f * dsp->fConst0)));
	dsp->fConst41 = (0.0f - (2.0f * dsp->fConst40));
	dsp->fConst42 = mydsp_faustpower2_f(dsp->fConst40);
	dsp->fConst43 = powf(0.00100000005f, (1.0f / (0.239999995f * dsp->fConst0)));
	dsp->fConst44 = (0.0f - (2.0f * dsp->fConst43));
	dsp->fConst45 = mydsp_faustpower2_f(dsp->fConst43);
	dsp->fConst46 = powf(0.00100000005f, (1.0f / (0.209999993f * dsp->fConst0)));
	dsp->fConst47 = (0.0f - (2.0f * dsp->fConst46));
	dsp->fConst48 = mydsp_faustpower2_f(dsp->fConst46);
	dsp->fConst49 = powf(0.00100000005f, (1.0f / (0.180000007f * dsp->fConst0)));
	dsp->fConst50 = (0.0f - (2.0f * dsp->fConst49));
	dsp->fConst51 = mydsp_faustpower2_f(dsp->fConst49);
	dsp->fConst52 = powf(0.00100000005f, (1.0f / (0.150000006f * dsp->fConst0)));
	dsp->fConst53 = (0.0f - (2.0f * dsp->fConst52));
	dsp->fConst54 = mydsp_faustpower2_f(dsp->fConst52);
	dsp->fConst55 = powf(0.00100000005f, (1.0f / (0.119999997f * dsp->fConst0)));
	dsp->fConst56 = (0.0f - (2.0f * dsp->fConst55));
	dsp->fConst57 = mydsp_faustpower2_f(dsp->fConst55);
	dsp->fConst58 = powf(0.00100000005f, (1.0f / (0.0900000036f * dsp->fConst0)));
	dsp->fConst59 = (0.0f - (2.0f * dsp->fConst58));
	dsp->fConst60 = mydsp_faustpower2_f(dsp->fConst58);
	dsp->fConst61 = powf(0.00100000005f, (1.0f / (0.0599999987f * dsp->fConst0)));
	dsp->fConst62 = (0.0f - (2.0f * dsp->fConst61));
	dsp->fConst63 = mydsp_faustpower2_f(dsp->fConst61);
	dsp->fConst64 = powf(0.00100000005f, (1.0f / (0.0299999993f * dsp->fConst0)));
	dsp->fConst65 = (0.0f - (2.0f * dsp->fConst64));
	dsp->fConst66 = mydsp_faustpower2_f(dsp->fConst64);
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "drums");
	ui_interface->addButton(ui_interface->uiInterface, "gate", &dsp->fButton0);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "key", &dsp->fHslider3, 0.0f, 0.0f, 1.0f, 1.0f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "keyboard", &dsp->fHslider2, 0.0f, 0.0f, 1.0f, 1.0f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "x", &dsp->fHslider0, 1.0f, 0.0f, 1.0f, 0.00100000005f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "y", &dsp->fHslider1, 1.0f, 0.0f, 1.0f, 0.00100000005f);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	float fSlow0 = min(fabsf(((2.0f * (float)dsp->fHslider0) + -1.0f)), fabsf(((2.0f * (float)dsp->fHslider1) + -1.0f)));
	float fSlow1 = tanf((dsp->fConst1 * ((15000.0f * fSlow0) + 500.0f)));
	float fSlow2 = (1.0f / fSlow1);
	float fSlow3 = (((fSlow2 + 1.41421354f) / fSlow1) + 1.0f);
	float fSlow4 = (2.0f / fSlow3);
	float fSlow5 = tanf((dsp->fConst1 * ((500.0f * fSlow0) + 40.0f)));
	float fSlow6 = (1.0f / fSlow5);
	float fSlow7 = (1.0f / (((fSlow6 + 1.41421354f) / fSlow5) + 1.0f));
	float fSlow8 = (1.0f / mydsp_faustpower2_f(fSlow5));
	float fSlow9 = (((fSlow6 + -1.41421354f) / fSlow5) + 1.0f);
	float fSlow10 = (2.0f * (1.0f - fSlow8));
	float fSlow11 = (2.0f * (0.0f - fSlow8));
	float fSlow12 = (1.0f / fSlow3);
	float fSlow13 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fSlow1))));
	float fSlow14 = (((fSlow2 + -1.41421354f) / fSlow1) + 1.0f);
	float fSlow15 = (float)dsp->fButton0;
	int iSlow16 = ((2 * (1 - (int)(float)dsp->fHslider2)) + (1 - (int)(float)dsp->fHslider3));
	float fSlow17 = (dsp->fConst6 * cosf((dsp->fConst7 * (float)iSlow16)));
	int iSlow18 = (60 * iSlow16);
	float fSlow19 = (dsp->fConst10 * cosf((dsp->fConst11 * (float)(iSlow18 + 200))));
	float fSlow20 = (dsp->fConst14 * cosf((dsp->fConst11 * (float)(iSlow18 + 400))));
	float fSlow21 = (dsp->fConst17 * cosf((dsp->fConst11 * (float)(iSlow18 + 600))));
	float fSlow22 = (dsp->fConst20 * cosf((dsp->fConst11 * (float)(iSlow18 + 800))));
	float fSlow23 = (dsp->fConst23 * cosf((dsp->fConst11 * (float)(iSlow18 + 1000))));
	float fSlow24 = (dsp->fConst26 * cosf((dsp->fConst11 * (float)(iSlow18 + 1200))));
	float fSlow25 = (dsp->fConst29 * cosf((dsp->fConst11 * (float)(iSlow18 + 1400))));
	float fSlow26 = (dsp->fConst32 * cosf((dsp->fConst11 * (float)(iSlow18 + 1600))));
	float fSlow27 = (dsp->fConst35 * cosf((dsp->fConst11 * (float)(iSlow18 + 1800))));
	float fSlow28 = (dsp->fConst38 * cosf((dsp->fConst11 * (float)(iSlow18 + 2000))));
	float fSlow29 = (dsp->fConst41 * cosf((dsp->fConst11 * (float)(iSlow18 + 2200))));
	float fSlow30 = (dsp->fConst44 * cosf((dsp->fConst11 * (float)(iSlow18 + 2400))));
	float fSlow31 = (dsp->fConst47 * cosf((dsp->fConst11 * (float)(iSlow18 + 2600))));
	float fSlow32 = (dsp->fConst50 * cosf((dsp->fConst11 * (float)(iSlow18 + 2800))));
	float fSlow33 = (dsp->fConst53 * cosf((dsp->fConst11 * (float)(iSlow18 + 3000))));
	float fSlow34 = (dsp->fConst56 * cosf((dsp->fConst11 * (float)(iSlow18 + 3200))));
	float fSlow35 = (dsp->fConst59 * cosf((dsp->fConst11 * (float)(iSlow18 + 3400))));
	float fSlow36 = (dsp->fConst62 * cosf((dsp->fConst11 * (float)(iSlow18 + 3600))));
	float fSlow37 = (dsp->fConst65 * cosf((dsp->fConst11 * (float)(iSlow18 + 3800))));
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->fVec0[0] = dsp->fConst0;
			dsp->iRec3[0] = ((1103515245 * dsp->iRec3[1]) + 12345);
			dsp->fRec2[0] = ((4.65661287e-10f * (float)dsp->iRec3[0]) - (fSlow7 * ((fSlow9 * dsp->fRec2[2]) + (fSlow10 * dsp->fRec2[1]))));
			dsp->fRec1[0] = ((fSlow7 * (((fSlow8 * dsp->fRec2[0]) + (fSlow11 * dsp->fRec2[1])) + (fSlow8 * dsp->fRec2[2]))) - (fSlow12 * ((fSlow13 * dsp->fRec1[1]) + (fSlow14 * dsp->fRec1[2]))));
			dsp->fVec1[0] = fSlow15;
			dsp->fRec4[0] = ((((fSlow15 - dsp->fVec1[1]) > 0.0f) > 0)?0.0f:min(dsp->fConst2, ((dsp->fRec4[1] + (0.00200000009f * (dsp->fConst0 - dsp->fVec0[1]))) + 1.0f)));
			int iTemp0 = (dsp->fRec4[0] < dsp->fConst3);
			float fTemp1 = (fSlow4 * ((dsp->fRec1[2] + (dsp->fRec1[0] + (2.0f * dsp->fRec1[1]))) * (iTemp0?((dsp->fRec4[0] < 0.0f)?0.0f:(iTemp0?(dsp->fConst4 * dsp->fRec4[0]):1.0f)):((dsp->fRec4[0] < dsp->fConst2)?((dsp->fConst4 * (0.0f - (dsp->fRec4[0] - dsp->fConst3))) + 1.0f):0.0f))));
			dsp->fRec0[0] = (fTemp1 - ((fSlow17 * dsp->fRec0[1]) + (dsp->fConst8 * dsp->fRec0[2])));
			dsp->fRec5[0] = (fTemp1 - ((fSlow19 * dsp->fRec5[1]) + (dsp->fConst12 * dsp->fRec5[2])));
			dsp->fRec6[0] = (fTemp1 - ((fSlow20 * dsp->fRec6[1]) + (dsp->fConst15 * dsp->fRec6[2])));
			dsp->fRec7[0] = (fTemp1 - ((fSlow21 * dsp->fRec7[1]) + (dsp->fConst18 * dsp->fRec7[2])));
			dsp->fRec8[0] = (fTemp1 - ((fSlow22 * dsp->fRec8[1]) + (dsp->fConst21 * dsp->fRec8[2])));
			dsp->fRec9[0] = (fTemp1 - ((fSlow23 * dsp->fRec9[1]) + (dsp->fConst24 * dsp->fRec9[2])));
			dsp->fRec10[0] = (fTemp1 - ((fSlow24 * dsp->fRec10[1]) + (dsp->fConst27 * dsp->fRec10[2])));
			dsp->fRec11[0] = (fTemp1 - ((fSlow25 * dsp->fRec11[1]) + (dsp->fConst30 * dsp->fRec11[2])));
			dsp->fRec12[0] = (fTemp1 - ((fSlow26 * dsp->fRec12[1]) + (dsp->fConst33 * dsp->fRec12[2])));
			dsp->fRec13[0] = (fTemp1 - ((fSlow27 * dsp->fRec13[1]) + (dsp->fConst36 * dsp->fRec13[2])));
			dsp->fRec14[0] = (fTemp1 - ((fSlow28 * dsp->fRec14[1]) + (dsp->fConst39 * dsp->fRec14[2])));
			dsp->fRec15[0] = (fTemp1 - ((fSlow29 * dsp->fRec15[1]) + (dsp->fConst42 * dsp->fRec15[2])));
			dsp->fRec16[0] = (fTemp1 - ((fSlow30 * dsp->fRec16[1]) + (dsp->fConst45 * dsp->fRec16[2])));
			dsp->fRec17[0] = (fTemp1 - ((fSlow31 * dsp->fRec17[1]) + (dsp->fConst48 * dsp->fRec17[2])));
			dsp->fRec18[0] = (fTemp1 - ((fSlow32 * dsp->fRec18[1]) + (dsp->fConst51 * dsp->fRec18[2])));
			dsp->fRec19[0] = (fTemp1 - ((fSlow33 * dsp->fRec19[1]) + (dsp->fConst54 * dsp->fRec19[2])));
			dsp->fRec20[0] = (fTemp1 - ((fSlow34 * dsp->fRec20[1]) + (dsp->fConst57 * dsp->fRec20[2])));
			dsp->fRec21[0] = (fTemp1 - ((fSlow35 * dsp->fRec21[1]) + (dsp->fConst60 * dsp->fRec21[2])));
			dsp->fRec22[0] = (fTemp1 - ((fSlow36 * dsp->fRec22[1]) + (dsp->fConst63 * dsp->fRec22[2])));
			dsp->fRec23[0] = (fTemp1 - ((fSlow37 * dsp->fRec23[1]) + (dsp->fConst66 * dsp->fRec23[2])));
			float fTemp2 = (0.0500000007f * ((((((((((((((((((((dsp->fRec0[0] + (0.25f * (dsp->fRec5[0] - dsp->fRec5[2]))) + (0.111111112f * (dsp->fRec6[0] - dsp->fRec6[2]))) + (0.0625f * (dsp->fRec7[0] - dsp->fRec7[2]))) + (0.0399999991f * (dsp->fRec8[0] - dsp->fRec8[2]))) + (0.027777778f * (dsp->fRec9[0] - dsp->fRec9[2]))) + (0.0204081628f * (dsp->fRec10[0] - dsp->fRec10[2]))) + (0.015625f * (dsp->fRec11[0] - dsp->fRec11[2]))) + (0.0123456791f * (dsp->fRec12[0] - dsp->fRec12[2]))) + (0.00999999978f * (dsp->fRec13[0] - dsp->fRec13[2]))) + (0.00826446246f * (dsp->fRec14[0] - dsp->fRec14[2]))) + (0.0069444445f * (dsp->fRec15[0] - dsp->fRec15[2]))) + (0.00591715984f * (dsp->fRec16[0] - dsp->fRec16[2]))) + (0.00510204071f * (dsp->fRec17[0] - dsp->fRec17[2]))) + (0.00444444455f * (dsp->fRec18[0] - dsp->fRec18[2]))) + (0.00390625f * (dsp->fRec19[0] - dsp->fRec19[2]))) + (0.00346020772f * (dsp->fRec20[0] - dsp->fRec20[2]))) + (0.00308641978f * (dsp->fRec21[0] - dsp->fRec21[2]))) + (0.00277008303f * (dsp->fRec22[0] - dsp->fRec22[2]))) + (0.00249999994f * (dsp->fRec23[0] - dsp->fRec23[2]))) - dsp->fRec0[2]));
			output0[i] = (FAUSTFLOAT)fTemp2;
			output1[i] = (FAUSTFLOAT)fTemp2;
			dsp->fVec0[1] = dsp->fVec0[0];
			dsp->iRec3[1] = dsp->iRec3[0];
			dsp->fRec2[2] = dsp->fRec2[1];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec1[2] = dsp->fRec1[1];
			dsp->fRec1[1] = dsp->fRec1[0];
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
