/* ------------------------------------------------------------
author: "CICM"
copyright: "(c)CICM 2013"
license: "BSD"
name: "fourSourcesToOcto"
version: "1.0"
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
	
} mydsp;

mydsp* newmydsp() { 
	mydsp* dsp = (mydsp*)malloc(sizeof(mydsp));
	return dsp;
}

void deletemydsp(mydsp* dsp) { 
	free(dsp);
}

void metadatamydsp(MetaGlue* m) { 
	m->declare(m->metaInterface, "author", "CICM");
	m->declare(m->metaInterface, "basics.lib/name", "Faust Basic Element Library");
	m->declare(m->metaInterface, "basics.lib/version", "0.0");
	m->declare(m->metaInterface, "copyright", "(c)CICM 2013");
	m->declare(m->metaInterface, "hoa.lib/author", "Pierre Guillot");
	m->declare(m->metaInterface, "hoa.lib/copyright", "2012-2013 Guillot, Paris, Colafrancesco, CICM labex art H2H, U. Paris 8");
	m->declare(m->metaInterface, "hoa.lib/name", "High Order Ambisonics library");
	m->declare(m->metaInterface, "license", "BSD");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "fourSourcesToOcto");
	m->declare(m->metaInterface, "routes.lib/name", "Faust Signal Routing Library");
	m->declare(m->metaInterface, "routes.lib/version", "0.0");
	m->declare(m->metaInterface, "signals.lib/name", "Faust Signal Routing Library");
	m->declare(m->metaInterface, "signals.lib/version", "0.0");
	m->declare(m->metaInterface, "version", "1.0");
}

int getSampleRatemydsp(mydsp* dsp) { return dsp->fSamplingFreq; }

int getNumInputsmydsp(mydsp* dsp) {
	return 4;
	
}
int getNumOutputsmydsp(mydsp* dsp) {
	return 8;
	
}
int getInputRatemydsp(mydsp* dsp, int channel) {
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

void classInitmydsp(int samplingFreq) {
	
}

void instanceResetUserInterfacemydsp(mydsp* dsp) {
	dsp->fHslider0 = (FAUSTFLOAT)1.0f;
	dsp->fHslider1 = (FAUSTFLOAT)1.0f;
	dsp->fHslider2 = (FAUSTFLOAT)1.0f;
	dsp->fHslider3 = (FAUSTFLOAT)1.0f;
	dsp->fHslider4 = (FAUSTFLOAT)0.0f;
	dsp->fHslider5 = (FAUSTFLOAT)0.0f;
	dsp->fHslider6 = (FAUSTFLOAT)0.0f;
	dsp->fHslider7 = (FAUSTFLOAT)0.0f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			dsp->fRec0[l0] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			dsp->fRec1[l1] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			dsp->fRec2[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			dsp->fRec3[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			dsp->fRec4[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			dsp->fRec5[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			dsp->fRec6[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			dsp->fRec7[l7] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = expf((0.0f - (50.0f / min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq)))));
	dsp->fConst1 = (1.0f - dsp->fConst0);
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "fourSourcesToOcto");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Angle1", &dsp->fHslider4, 0.0f, -6.28318548f, 6.28318548f, 0.00100000005f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Angle2", &dsp->fHslider5, 0.0f, -6.28318548f, 6.28318548f, 0.00100000005f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Angle3", &dsp->fHslider6, 0.0f, -6.28318548f, 6.28318548f, 0.00100000005f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Angle4", &dsp->fHslider7, 0.0f, -6.28318548f, 6.28318548f, 0.00100000005f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Radius1", &dsp->fHslider0, 1.0f, 0.0f, 5.0f, 0.00100000005f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Radius2", &dsp->fHslider1, 1.0f, 0.0f, 5.0f, 0.00100000005f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Radius3", &dsp->fHslider2, 1.0f, 0.0f, 5.0f, 0.00100000005f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Radius4", &dsp->fHslider3, 1.0f, 0.0f, 5.0f, 0.00100000005f);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
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
	float fSlow0 = (dsp->fConst1 * (float)dsp->fHslider0);
	float fSlow1 = (dsp->fConst1 * (float)dsp->fHslider1);
	float fSlow2 = (dsp->fConst1 * (float)dsp->fHslider2);
	float fSlow3 = (dsp->fConst1 * (float)dsp->fHslider3);
	float fSlow4 = (dsp->fConst1 * (float)dsp->fHslider4);
	float fSlow5 = (dsp->fConst1 * (float)dsp->fHslider5);
	float fSlow6 = (dsp->fConst1 * (float)dsp->fHslider6);
	float fSlow7 = (dsp->fConst1 * (float)dsp->fHslider7);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = (float)input0[i];
			dsp->fRec0[0] = (fSlow0 + (dsp->fConst0 * dsp->fRec0[1]));
			int iTemp1 = (dsp->fRec0[0] > 1.0f);
			int iTemp2 = (dsp->fRec0[0] < 1.0f);
			float fTemp3 = ((float)iTemp1 + (dsp->fRec0[0] * (float)iTemp2));
			float fTemp4 = ((1.38629436f * (1.0f - fTemp3)) + 1.0f);
			float fTemp5 = (fTemp0 * fTemp4);
			float fTemp6 = ((float)iTemp2 + (mydsp_faustpower2_f(dsp->fRec0[0]) * (float)iTemp1));
			float fTemp7 = (float)input1[i];
			dsp->fRec1[0] = (fSlow1 + (dsp->fConst0 * dsp->fRec1[1]));
			int iTemp8 = (dsp->fRec1[0] > 1.0f);
			int iTemp9 = (dsp->fRec1[0] < 1.0f);
			float fTemp10 = ((float)iTemp8 + (dsp->fRec1[0] * (float)iTemp9));
			float fTemp11 = ((1.38629436f * (1.0f - fTemp10)) + 1.0f);
			float fTemp12 = (fTemp7 * fTemp11);
			float fTemp13 = ((float)iTemp9 + (mydsp_faustpower2_f(dsp->fRec1[0]) * (float)iTemp8));
			float fTemp14 = (float)input2[i];
			dsp->fRec2[0] = (fSlow2 + (dsp->fConst0 * dsp->fRec2[1]));
			int iTemp15 = (dsp->fRec2[0] > 1.0f);
			int iTemp16 = (dsp->fRec2[0] < 1.0f);
			float fTemp17 = ((float)iTemp15 + (dsp->fRec2[0] * (float)iTemp16));
			float fTemp18 = ((1.38629436f * (1.0f - fTemp17)) + 1.0f);
			float fTemp19 = (fTemp14 * fTemp18);
			float fTemp20 = ((float)iTemp16 + (mydsp_faustpower2_f(dsp->fRec2[0]) * (float)iTemp15));
			float fTemp21 = (float)input3[i];
			dsp->fRec3[0] = (fSlow3 + (dsp->fConst0 * dsp->fRec3[1]));
			int iTemp22 = (dsp->fRec3[0] > 1.0f);
			int iTemp23 = (dsp->fRec3[0] < 1.0f);
			float fTemp24 = ((float)iTemp22 + (dsp->fRec3[0] * (float)iTemp23));
			float fTemp25 = ((1.38629436f * (1.0f - fTemp24)) + 1.0f);
			float fTemp26 = (fTemp21 * fTemp25);
			float fTemp27 = ((float)iTemp23 + (mydsp_faustpower2_f(dsp->fRec3[0]) * (float)iTemp22));
			float fTemp28 = (0.142857149f * ((((fTemp5 / fTemp6) + (fTemp12 / fTemp13)) + (fTemp19 / fTemp20)) + (fTemp26 / fTemp27)));
			float fTemp29 = (2.0f * fTemp3);
			float fTemp30 = ((2.0f * ((fTemp3 * (float)(fTemp29 > 0.0f)) * (float)(fTemp29 <= 1.0f))) + (float)(fTemp29 > 1.0f));
			dsp->fRec4[0] = (fSlow4 + (dsp->fConst0 * dsp->fRec4[1]));
			float fTemp31 = (2.0f * fTemp10);
			float fTemp32 = ((2.0f * ((fTemp10 * (float)(fTemp31 > 0.0f)) * (float)(fTemp31 <= 1.0f))) + (float)(fTemp31 > 1.0f));
			dsp->fRec5[0] = (fSlow5 + (dsp->fConst0 * dsp->fRec5[1]));
			float fTemp33 = (2.0f * fTemp17);
			float fTemp34 = ((2.0f * ((fTemp17 * (float)(fTemp33 > 0.0f)) * (float)(fTemp33 <= 1.0f))) + (float)(fTemp33 > 1.0f));
			dsp->fRec6[0] = (fSlow6 + (dsp->fConst0 * dsp->fRec6[1]));
			float fTemp35 = (2.0f * fTemp24);
			float fTemp36 = ((2.0f * ((fTemp24 * (float)(fTemp35 > 0.0f)) * (float)(fTemp35 <= 1.0f))) + (float)(fTemp35 > 1.0f));
			dsp->fRec7[0] = (fSlow7 + (dsp->fConst0 * dsp->fRec7[1]));
			float fTemp37 = ((((((fTemp5 * fTemp30) * cosf(dsp->fRec4[0])) / fTemp6) + (((fTemp12 * fTemp32) * cosf(dsp->fRec5[0])) / fTemp13)) + (((fTemp19 * fTemp34) * cosf(dsp->fRec6[0])) / fTemp20)) + (((fTemp26 * fTemp36) * cosf(dsp->fRec7[0])) / fTemp27));
			float fTemp38 = (0.214285716f * fTemp37);
			float fTemp39 = (2.0f * dsp->fRec4[0]);
			float fTemp40 = (1.38629436f * fTemp3);
			float fTemp41 = (fTemp40 + -0.693147182f);
			float fTemp42 = (2.46630335f * fTemp41);
			float fTemp43 = ((2.46630335f * ((fTemp41 * (float)(fTemp42 > 0.0f)) * (float)(fTemp42 <= 1.0f))) + (float)(fTemp42 > 1.0f));
			float fTemp44 = (2.0f * dsp->fRec5[0]);
			float fTemp45 = (1.38629436f * fTemp10);
			float fTemp46 = (fTemp45 + -0.693147182f);
			float fTemp47 = (2.46630335f * fTemp46);
			float fTemp48 = ((2.46630335f * ((fTemp46 * (float)(fTemp47 > 0.0f)) * (float)(fTemp47 <= 1.0f))) + (float)(fTemp47 > 1.0f));
			float fTemp49 = (2.0f * dsp->fRec6[0]);
			float fTemp50 = (1.38629436f * fTemp17);
			float fTemp51 = (fTemp50 + -0.693147182f);
			float fTemp52 = (2.46630335f * fTemp51);
			float fTemp53 = ((2.46630335f * ((fTemp51 * (float)(fTemp52 > 0.0f)) * (float)(fTemp52 <= 1.0f))) + (float)(fTemp52 > 1.0f));
			float fTemp54 = (2.0f * dsp->fRec7[0]);
			float fTemp55 = (1.38629436f * fTemp24);
			float fTemp56 = (fTemp55 + -0.693147182f);
			float fTemp57 = (2.46630335f * fTemp56);
			float fTemp58 = ((2.46630335f * ((fTemp56 * (float)(fTemp57 > 0.0f)) * (float)(fTemp57 <= 1.0f))) + (float)(fTemp57 > 1.0f));
			float fTemp59 = (0.0857142881f * (((((((fTemp0 * cosf(fTemp39)) * fTemp4) * fTemp43) / fTemp6) + ((((fTemp7 * cosf(fTemp44)) * fTemp11) * fTemp48) / fTemp13)) + ((((fTemp14 * cosf(fTemp49)) * fTemp18) * fTemp53) / fTemp20)) + ((((fTemp21 * cosf(fTemp54)) * fTemp25) * fTemp58) / fTemp27)));
			float fTemp60 = (3.0f * dsp->fRec4[0]);
			float fTemp61 = (fTemp40 + -1.09861231f);
			float fTemp62 = (3.47605944f * fTemp61);
			float fTemp63 = ((3.47605944f * ((fTemp61 * (float)(fTemp62 > 0.0f)) * (float)(fTemp62 <= 1.0f))) + (float)(fTemp62 > 1.0f));
			float fTemp64 = (3.0f * dsp->fRec5[0]);
			float fTemp65 = (fTemp45 + -1.09861231f);
			float fTemp66 = (3.47605944f * fTemp65);
			float fTemp67 = ((3.47605944f * ((fTemp65 * (float)(fTemp66 > 0.0f)) * (float)(fTemp66 <= 1.0f))) + (float)(fTemp66 > 1.0f));
			float fTemp68 = (3.0f * dsp->fRec6[0]);
			float fTemp69 = (fTemp50 + -1.09861231f);
			float fTemp70 = (3.47605944f * fTemp69);
			float fTemp71 = ((3.47605944f * ((fTemp69 * (float)(fTemp70 > 0.0f)) * (float)(fTemp70 <= 1.0f))) + (float)(fTemp70 > 1.0f));
			float fTemp72 = (3.0f * dsp->fRec7[0]);
			float fTemp73 = (fTemp55 + -1.09861231f);
			float fTemp74 = (3.47605944f * fTemp73);
			float fTemp75 = ((3.47605944f * ((fTemp73 * (float)(fTemp74 > 0.0f)) * (float)(fTemp74 <= 1.0f))) + (float)(fTemp74 > 1.0f));
			float fTemp76 = (((((((fTemp0 * cosf(fTemp60)) * fTemp4) * fTemp63) / fTemp6) + ((((fTemp7 * cosf(fTemp64)) * fTemp11) * fTemp67) / fTemp13)) + ((((fTemp14 * cosf(fTemp68)) * fTemp18) * fTemp71) / fTemp20)) + ((((fTemp21 * cosf(fTemp72)) * fTemp25) * fTemp75) / fTemp27));
			float fTemp77 = (0.0142857144f * fTemp76);
			output0[i] = (FAUSTFLOAT)(((fTemp28 + fTemp38) + fTemp59) + fTemp77);
			float fTemp78 = ((((((fTemp5 * sinf(dsp->fRec4[0])) * fTemp30) / fTemp6) + (((fTemp12 * sinf(dsp->fRec5[0])) * fTemp32) / fTemp13)) + (((fTemp19 * sinf(dsp->fRec6[0])) * fTemp34) / fTemp20)) + (((fTemp26 * sinf(dsp->fRec7[0])) * fTemp36) / fTemp27));
			float fTemp79 = (0.151522875f * fTemp78);
			float fTemp80 = (0.0857142881f * (((((((fTemp0 * sinf(fTemp39)) * fTemp4) * fTemp43) / fTemp6) + ((((fTemp7 * sinf(fTemp44)) * fTemp11) * fTemp48) / fTemp13)) + ((((fTemp14 * sinf(fTemp49)) * fTemp18) * fTemp53) / fTemp20)) + ((((fTemp21 * sinf(fTemp54)) * fTemp25) * fTemp58) / fTemp27)));
			float fTemp81 = (((((((fTemp0 * sinf(fTemp60)) * fTemp4) * fTemp63) / fTemp6) + ((((fTemp7 * sinf(fTemp64)) * fTemp11) * fTemp67) / fTemp13)) + ((((fTemp14 * sinf(fTemp68)) * fTemp18) * fTemp71) / fTemp20)) + ((((fTemp21 * sinf(fTemp72)) * fTemp25) * fTemp75) / fTemp27));
			output1[i] = (FAUSTFLOAT)(((((fTemp28 + fTemp79) + (0.151522875f * fTemp37)) + fTemp80) + (0.0101015251f * fTemp81)) - (0.0101015251f * fTemp76));
			float fTemp82 = (0.214285716f * fTemp78);
			float fTemp83 = (0.0142857144f * fTemp81);
			output2[i] = (FAUSTFLOAT)((fTemp28 + fTemp82) - (fTemp59 + fTemp83));
			float fTemp84 = (0.151522875f * fTemp37);
			output3[i] = (FAUSTFLOAT)((((fTemp28 + (0.151522875f * fTemp78)) + (0.0101015251f * fTemp81)) + (0.0101015251f * fTemp76)) - (fTemp80 + fTemp84));
			output4[i] = (FAUSTFLOAT)((fTemp28 + fTemp59) - (fTemp38 + fTemp77));
			output5[i] = (FAUSTFLOAT)(((fTemp28 + fTemp80) + (0.0101015251f * fTemp76)) - ((fTemp79 + (0.151522875f * fTemp37)) + (0.0101015251f * fTemp81)));
			output6[i] = (FAUSTFLOAT)((fTemp28 + fTemp83) - (fTemp59 + fTemp82));
			output7[i] = (FAUSTFLOAT)((fTemp28 + fTemp84) - (((fTemp80 + (0.151522875f * fTemp78)) + (0.0101015251f * fTemp81)) + (0.0101015251f * fTemp76)));
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec3[1] = dsp->fRec3[0];
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fRec5[1] = dsp->fRec5[0];
			dsp->fRec6[1] = dsp->fRec6[0];
			dsp->fRec7[1] = dsp->fRec7[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
