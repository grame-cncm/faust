/* ------------------------------------------------------------
name: "clarinet"
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


#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif
#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

typedef struct {
	
	int iRec6[2];
	float fRec13[2];
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	float fRec18[2];
	float fRec17[2];
	float fRec14[2];
	FAUSTFLOAT fHslider0;
	float fRec19[2];
	int IOTA;
	float fRec15[2048];
	float fConst3;
	float fConst4;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT fHslider5;
	FAUSTFLOAT fHslider6;
	FAUSTFLOAT fHslider7;
	FAUSTFLOAT fHslider8;
	int iVec0[2];
	int iRec21[2];
	FAUSTFLOAT fHslider9;
	int iVec1[2];
	int iRec22[2];
	float fRec20[2];
	float fVec2[2];
	float fRec11[2];
	float fRec2[2048];
	float fRec0[2];
	
} mydsp;

mydsp* newmydsp() { 
	mydsp* dsp = (mydsp*)malloc(sizeof(mydsp));
	return dsp;
}

void deletemydsp(mydsp* dsp) { 
	free(dsp);
}

void metadatamydsp(MetaGlue* m) { 
	m->declare(m->metaInterface, "analyzers.lib/name", "Faust Analyzer Library");
	m->declare(m->metaInterface, "analyzers.lib/version", "0.0");
	m->declare(m->metaInterface, "basics.lib/name", "Faust Basic Element Library");
	m->declare(m->metaInterface, "basics.lib/version", "0.0");
	m->declare(m->metaInterface, "delays.lib/name", "Faust Delay Library");
	m->declare(m->metaInterface, "delays.lib/version", "0.0");
	m->declare(m->metaInterface, "interface", "SmartKeyboard{  'Number of Keyboards':'2',  'Max Keyboard Polyphony':'0',  'Keyboard 0 - Number of Keys':'4',   'Keyboard 1 - Number of Keys':'5',  'Keyboard 0 - Send Freq':'0',   'Keyboard 1 - Send Freq':'0',  'Keyboard 0 - Piano Keyboard':'0',   'Keyboard 1 - Piano Keyboard':'0',  'Keyboard 0 - Send Key Status':'1',  'Keyboard 1 - Send Key Status':'1',  'Keyboard 0 - Key 3 - Label':'O+',  'Keyboard 1 - Key 4 - Label':'O-' }");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "clarinet");
	m->declare(m->metaInterface, "routes.lib/name", "Faust Signal Routing Library");
	m->declare(m->metaInterface, "routes.lib/version", "0.0");
	m->declare(m->metaInterface, "signals.lib/name", "Faust Signal Routing Library");
	m->declare(m->metaInterface, "signals.lib/version", "0.0");
}

int getSampleRatemydsp(mydsp* dsp) { return dsp->fSamplingFreq; }

int getNumInputsmydsp(mydsp* dsp) {
	return 1;
	
}
int getNumOutputsmydsp(mydsp* dsp) {
	return 2;
	
}
int getInputRatemydsp(mydsp* dsp, int channel) {
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
	dsp->fHslider0 = (FAUSTFLOAT)0.0f;
	dsp->fHslider1 = (FAUSTFLOAT)0.0f;
	dsp->fHslider2 = (FAUSTFLOAT)0.0f;
	dsp->fHslider3 = (FAUSTFLOAT)0.0f;
	dsp->fHslider4 = (FAUSTFLOAT)0.0f;
	dsp->fHslider5 = (FAUSTFLOAT)0.0f;
	dsp->fHslider6 = (FAUSTFLOAT)0.0f;
	dsp->fHslider7 = (FAUSTFLOAT)0.0f;
	dsp->fHslider8 = (FAUSTFLOAT)0.0f;
	dsp->fHslider9 = (FAUSTFLOAT)0.0f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			dsp->iRec6[l0] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			dsp->fRec13[l1] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			dsp->fRec18[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			dsp->fRec17[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			dsp->fRec14[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			dsp->fRec19[l5] = 0.0f;
			
		}
		
	}
	dsp->IOTA = 0;
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 2048); l6 = (l6 + 1)) {
			dsp->fRec15[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			dsp->iVec0[l7] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			dsp->iRec21[l8] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			dsp->iVec1[l9] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			dsp->iRec22[l10] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			dsp->fRec20[l11] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			dsp->fVec2[l12] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l13;
		for (l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			dsp->fRec11[l13] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l14;
		for (l14 = 0; (l14 < 2048); l14 = (l14 + 1)) {
			dsp->fRec2[l14] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l15;
		for (l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			dsp->fRec0[l15] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = expf((0.0f - (50.0f / dsp->fConst0)));
	dsp->fConst2 = (1.0f - dsp->fConst1);
	dsp->fConst3 = (0.00882352982f * dsp->fConst0);
	dsp->fConst4 = (0.00147058826f * dsp->fConst0);
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "clarinet");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb0k0status", &dsp->fHslider1, 0.0f, 0.0f, 1.0f, 1.0f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb0k1status", &dsp->fHslider2, 0.0f, 0.0f, 1.0f, 1.0f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb0k2status", &dsp->fHslider3, 0.0f, 0.0f, 1.0f, 1.0f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb0k3status", &dsp->fHslider8, 0.0f, 0.0f, 1.0f, 1.0f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb1k0status", &dsp->fHslider4, 0.0f, 0.0f, 1.0f, 1.0f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb1k1status", &dsp->fHslider5, 0.0f, 0.0f, 1.0f, 1.0f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb1k2status", &dsp->fHslider6, 0.0f, 0.0f, 1.0f, 1.0f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb1k3status", &dsp->fHslider7, 0.0f, 0.0f, 1.0f, 1.0f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "kb1k4status", &dsp->fHslider9, 0.0f, 0.0f, 1.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "acc", "1 1 -10 0 10");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "reedStiffness", &dsp->fHslider0, 0.0f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* input0 = inputs[0];
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	float fSlow0 = (0.00100000005f * (float)dsp->fHslider0);
	int iSlow1 = (int)min(1.0f, (float)dsp->fHslider1);
	int iSlow2 = (iSlow1 == 1);
	int iSlow3 = (int)min(1.0f, (float)dsp->fHslider2);
	int iSlow4 = (iSlow3 == 1);
	int iSlow5 = (iSlow2 & iSlow4);
	int iSlow6 = (int)min(1.0f, (float)dsp->fHslider3);
	int iSlow7 = (iSlow6 == 0);
	int iSlow8 = (iSlow5 & iSlow7);
	int iSlow9 = (int)min(1.0f, (float)dsp->fHslider4);
	int iSlow10 = (iSlow9 == 0);
	int iSlow11 = (int)min(1.0f, (float)dsp->fHslider5);
	int iSlow12 = (iSlow11 == 0);
	int iSlow13 = (int)min(1.0f, (float)dsp->fHslider6);
	int iSlow14 = (iSlow13 == 0);
	int iSlow15 = (int)min(1.0f, (float)dsp->fHslider7);
	int iSlow16 = (iSlow15 == 0);
	float fSlow17 = (4.0f * (1.0f - (float)((((iSlow8 & iSlow10) & iSlow12) & iSlow14) & iSlow16)));
	int iSlow18 = (iSlow6 == 1);
	int iSlow19 = (iSlow5 & iSlow18);
	int iSlow20 = (iSlow9 == 1);
	int iSlow21 = (iSlow19 & iSlow20);
	int iSlow22 = (iSlow11 == 1);
	int iSlow23 = (iSlow21 & iSlow22);
	int iSlow24 = (iSlow23 & (iSlow13 == 1));
	int iSlow25 = (iSlow15 == 1);
	int iSlow26 = (iSlow23 & iSlow14);
	int iSlow27 = (iSlow19 & iSlow10);
	int iSlow28 = (iSlow1 == 0);
	int iSlow29 = (iSlow3 == 0);
	int iSlow30 = (iSlow2 & iSlow29);
	int iSlow31 = ((13 * (iSlow24 & iSlow25)) + ((11 * (iSlow24 & iSlow16)) + ((10 * (iSlow26 & iSlow25)) + ((9 * (iSlow26 & iSlow16)) + ((8 * (((iSlow21 & iSlow12) & iSlow14) & iSlow16)) + ((7 * (((iSlow27 & iSlow22) & iSlow14) & iSlow16)) + ((6 * (((iSlow27 & iSlow12) & iSlow14) & iSlow16)) + (((((((((iSlow28 & iSlow4) & iSlow7) & iSlow10) & iSlow12) & iSlow14) & iSlow16) + (2 * (((((iSlow30 & iSlow7) & iSlow10) & iSlow12) & iSlow14) & iSlow16))) + (3 * (((((iSlow30 & iSlow18) & iSlow10) & iSlow12) & iSlow14) & iSlow16))) + (5 * ((((iSlow8 & iSlow20) & iSlow12) & iSlow14) & iSlow16))))))))));
	int iSlow32 = ((((((iSlow28 & iSlow29) & iSlow7) & iSlow10) & iSlow12) & iSlow14) & iSlow25);
	int iSlow33 = (int)min(1.0f, (float)dsp->fHslider8);
	int iSlow34 = (int)min(1.0f, (float)dsp->fHslider9);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->iRec6[0] = 0;
			dsp->fRec13[0] = (0.5f * (dsp->fRec13[1] + dsp->fRec11[1]));
			float fRec10 = (dsp->fRec13[0] + (float)dsp->iRec6[1]);
			float fTemp0 = fabsf((float)input0[i]);
			dsp->fRec18[0] = max(fTemp0, ((dsp->fConst1 * dsp->fRec18[1]) + (dsp->fConst2 * fTemp0)));
			dsp->fRec17[0] = ((dsp->fConst1 * dsp->fRec17[1]) + (dsp->fConst2 * dsp->fRec18[0]));
			float fTemp1 = (0.699999988f * dsp->fRec17[0]);
			dsp->fRec14[0] = (dsp->fRec0[1] + fTemp1);
			float fTemp2 = (0.0f - dsp->fRec14[1]);
			dsp->fRec19[0] = (fSlow0 + (0.999000013f * dsp->fRec19[1]));
			dsp->fRec15[(dsp->IOTA & 2047)] = (fTemp1 + (fTemp2 * max(-1.0f, min(1.0f, ((fTemp2 * ((0.25999999f * dsp->fRec19[0]) + -0.439999998f)) + 0.699999988f)))));
			int iRec16 = 0;
			dsp->iVec0[0] = iSlow33;
			dsp->iRec21[0] = (((iSlow33 - dsp->iVec0[1]) > 0) + dsp->iRec21[1]);
			dsp->iVec1[0] = iSlow34;
			dsp->iRec22[0] = (((iSlow34 - dsp->iVec1[1]) > 0) + dsp->iRec22[1]);
			dsp->fRec20[0] = ((0.999000013f * dsp->fRec20[1]) + (0.000772727246f / powf(2.0f, (0.0833333358f * (fSlow17 - (float)(iSlow31 + (12 * (iSlow32 - (dsp->iRec21[0] - dsp->iRec22[0])))))))));
			float fTemp3 = (dsp->fConst4 * ((0.5f * dsp->fRec20[0]) + -0.0500000007f));
			float fTemp4 = (fTemp3 + -1.49999499f);
			int iTemp5 = (int)fTemp4;
			int iTemp6 = ((int)min(dsp->fConst3, (float)max(0, (int)iTemp5)) + 1);
			float fTemp7 = floorf(fTemp4);
			float fTemp8 = (fTemp3 + (-1.0f - fTemp7));
			float fTemp9 = (0.0f - fTemp8);
			float fTemp10 = (fTemp3 + (-2.0f - fTemp7));
			float fTemp11 = (0.0f - (0.5f * fTemp10));
			float fTemp12 = (fTemp3 + (-3.0f - fTemp7));
			float fTemp13 = (0.0f - (0.333333343f * fTemp12));
			float fTemp14 = (fTemp3 + (-4.0f - fTemp7));
			float fTemp15 = (0.0f - (0.25f * fTemp14));
			float fTemp16 = (fTemp3 - fTemp7);
			int iTemp17 = ((int)min(dsp->fConst3, (float)max(0, (int)(iTemp5 + 2))) + 1);
			float fTemp18 = (0.0f - fTemp12);
			float fTemp19 = (0.0f - (0.5f * fTemp14));
			int iTemp20 = ((int)min(dsp->fConst3, (float)max(0, (int)(iTemp5 + 1))) + 1);
			float fTemp21 = (0.0f - fTemp10);
			float fTemp22 = (0.0f - (0.5f * fTemp12));
			float fTemp23 = (0.0f - (0.333333343f * fTemp14));
			float fTemp24 = (fTemp8 * fTemp10);
			int iTemp25 = ((int)min(dsp->fConst3, (float)max(0, (int)(iTemp5 + 3))) + 1);
			float fTemp26 = (0.0f - fTemp14);
			float fTemp27 = (fTemp24 * fTemp12);
			int iTemp28 = ((int)min(dsp->fConst3, (float)max(0, (int)(iTemp5 + 4))) + 1);
			dsp->fVec2[0] = (((((dsp->fRec15[((dsp->IOTA - iTemp6) & 2047)] * fTemp9) * fTemp11) * fTemp13) * fTemp15) + (fTemp16 * ((((0.5f * (((fTemp8 * dsp->fRec15[((dsp->IOTA - iTemp17) & 2047)]) * fTemp18) * fTemp19)) + (((dsp->fRec15[((dsp->IOTA - iTemp20) & 2047)] * fTemp21) * fTemp22) * fTemp23)) + (0.166666672f * ((fTemp24 * dsp->fRec15[((dsp->IOTA - iTemp25) & 2047)]) * fTemp26))) + (0.0416666679f * (fTemp27 * dsp->fRec15[((dsp->IOTA - iTemp28) & 2047)])))));
			dsp->fRec11[0] = dsp->fVec2[1];
			int iRec12 = iRec16;
			float fRec7 = fRec10;
			float fRec8 = dsp->fRec11[0];
			float fRec9 = (dsp->fRec11[0] + (float)iRec12);
			dsp->fRec2[(dsp->IOTA & 2047)] = fRec7;
			float fRec3 = (((((fTemp9 * fTemp11) * fTemp13) * fTemp15) * dsp->fRec2[((dsp->IOTA - iTemp6) & 2047)]) + (fTemp16 * (((0.166666672f * ((fTemp24 * fTemp26) * dsp->fRec2[((dsp->IOTA - iTemp25) & 2047)])) + ((((fTemp21 * fTemp22) * fTemp23) * dsp->fRec2[((dsp->IOTA - iTemp20) & 2047)]) + (0.5f * (((fTemp8 * fTemp18) * fTemp19) * dsp->fRec2[((dsp->IOTA - iTemp17) & 2047)])))) + (0.0416666679f * (fTemp27 * dsp->fRec2[((dsp->IOTA - iTemp28) & 2047)])))));
			float fRec4 = fRec8;
			float fRec5 = fRec9;
			dsp->fRec0[0] = fRec3;
			float fRec1 = fRec5;
			output0[i] = (FAUSTFLOAT)fRec1;
			output1[i] = (FAUSTFLOAT)fRec1;
			dsp->iRec6[1] = dsp->iRec6[0];
			dsp->fRec13[1] = dsp->fRec13[0];
			dsp->fRec18[1] = dsp->fRec18[0];
			dsp->fRec17[1] = dsp->fRec17[0];
			dsp->fRec14[1] = dsp->fRec14[0];
			dsp->fRec19[1] = dsp->fRec19[0];
			dsp->IOTA = (dsp->IOTA + 1);
			dsp->iVec0[1] = dsp->iVec0[0];
			dsp->iRec21[1] = dsp->iRec21[0];
			dsp->iVec1[1] = dsp->iVec1[0];
			dsp->iRec22[1] = dsp->iRec22[0];
			dsp->fRec20[1] = dsp->fRec20[0];
			dsp->fVec2[1] = dsp->fVec2[0];
			dsp->fRec11[1] = dsp->fRec11[0];
			dsp->fRec0[1] = dsp->fRec0[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
