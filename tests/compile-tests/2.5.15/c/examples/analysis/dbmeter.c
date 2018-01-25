/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2006"
license: "BSD"
name: "dbmeter"
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
	float fRec0[2];
	FAUSTFLOAT fVbargraph0;
	int iConst1;
	float fRec1[2];
	FAUSTFLOAT fVbargraph1;
	int iConst2;
	float fRec2[2];
	FAUSTFLOAT fVbargraph2;
	int iConst3;
	float fRec3[2];
	FAUSTFLOAT fVbargraph3;
	int iConst4;
	float fRec4[2];
	FAUSTFLOAT fVbargraph4;
	int iConst5;
	float fRec5[2];
	FAUSTFLOAT fVbargraph5;
	int iConst6;
	float fRec6[2];
	FAUSTFLOAT fVbargraph6;
	int iConst7;
	float fRec7[2];
	FAUSTFLOAT fVbargraph7;
	int iConst8;
	
} mydsp;

mydsp* newmydsp() { 
	mydsp* dsp = (mydsp*)malloc(sizeof(mydsp));
	return dsp;
}

void deletemydsp(mydsp* dsp) { 
	free(dsp);
}

void metadatamydsp(MetaGlue* m) { 
	m->declare(m->metaInterface, "author", "Grame");
	m->declare(m->metaInterface, "basics.lib/name", "Faust Basic Element Library");
	m->declare(m->metaInterface, "basics.lib/version", "0.0");
	m->declare(m->metaInterface, "copyright", "(c)GRAME 2006");
	m->declare(m->metaInterface, "license", "BSD");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "dbmeter");
	m->declare(m->metaInterface, "version", "1.0");
}

int getSampleRatemydsp(mydsp* dsp) { return dsp->fSamplingFreq; }

int getNumInputsmydsp(mydsp* dsp) {
	return 8;
	
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
	dsp->fConst0 = (80.0f / min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq)));
	dsp->iConst1 = 0;
	dsp->iConst2 = 0;
	dsp->iConst3 = 0;
	dsp->iConst4 = 0;
	dsp->iConst5 = 0;
	dsp->iConst6 = 0;
	dsp->iConst7 = 0;
	dsp->iConst8 = 0;
	
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
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "8 channels dB meter");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "0");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph0, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fab9b491a10", &dsp->fVbargraph0, -70.0f, 10.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "1");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph1, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fab9b4960f0", &dsp->fVbargraph1, -70.0f, 10.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "2");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph2, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fab9b49a7d0", &dsp->fVbargraph2, -70.0f, 10.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "3");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph3, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fab9b49ef60", &dsp->fVbargraph3, -70.0f, 10.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "4");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph4, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fab9b4a37a0", &dsp->fVbargraph4, -70.0f, 10.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "5");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph5, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fab9b4a8090", &dsp->fVbargraph5, -70.0f, 10.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "6");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph6, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fab9b4aca30", &dsp->fVbargraph6, -70.0f, 10.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "7");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph7, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fab9b4b1480", &dsp->fVbargraph7, -70.0f, 10.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* input0 = inputs[0];
	FAUSTFLOAT* input1 = inputs[1];
	FAUSTFLOAT* input2 = inputs[2];
	FAUSTFLOAT* input3 = inputs[3];
	FAUSTFLOAT* input4 = inputs[4];
	FAUSTFLOAT* input5 = inputs[5];
	FAUSTFLOAT* input6 = inputs[6];
	FAUSTFLOAT* input7 = inputs[7];
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	FAUSTFLOAT* output2 = outputs[2];
	FAUSTFLOAT* output3 = outputs[3];
	FAUSTFLOAT* output4 = outputs[4];
	FAUSTFLOAT* output5 = outputs[5];
	FAUSTFLOAT* output6 = outputs[6];
	FAUSTFLOAT* output7 = outputs[7];
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = (float)input0[i];
			dsp->fRec0[0] = max((dsp->fRec0[1] - dsp->fConst0), min(10.0f, (20.0f * log10f(max(0.000316227757f, fabsf(fTemp0))))));
			dsp->fVbargraph0 = (FAUSTFLOAT)dsp->fRec0[0];
			output0[i] = (FAUSTFLOAT)dsp->iConst1;
			float fTemp1 = (float)input1[i];
			dsp->fRec1[0] = max((dsp->fRec1[1] - dsp->fConst0), min(10.0f, (20.0f * log10f(max(0.000316227757f, fabsf(fTemp1))))));
			dsp->fVbargraph1 = (FAUSTFLOAT)dsp->fRec1[0];
			output1[i] = (FAUSTFLOAT)dsp->iConst2;
			float fTemp2 = (float)input2[i];
			dsp->fRec2[0] = max((dsp->fRec2[1] - dsp->fConst0), min(10.0f, (20.0f * log10f(max(0.000316227757f, fabsf(fTemp2))))));
			dsp->fVbargraph2 = (FAUSTFLOAT)dsp->fRec2[0];
			output2[i] = (FAUSTFLOAT)dsp->iConst3;
			float fTemp3 = (float)input3[i];
			dsp->fRec3[0] = max((dsp->fRec3[1] - dsp->fConst0), min(10.0f, (20.0f * log10f(max(0.000316227757f, fabsf(fTemp3))))));
			dsp->fVbargraph3 = (FAUSTFLOAT)dsp->fRec3[0];
			output3[i] = (FAUSTFLOAT)dsp->iConst4;
			float fTemp4 = (float)input4[i];
			dsp->fRec4[0] = max((dsp->fRec4[1] - dsp->fConst0), min(10.0f, (20.0f * log10f(max(0.000316227757f, fabsf(fTemp4))))));
			dsp->fVbargraph4 = (FAUSTFLOAT)dsp->fRec4[0];
			output4[i] = (FAUSTFLOAT)dsp->iConst5;
			float fTemp5 = (float)input5[i];
			dsp->fRec5[0] = max((dsp->fRec5[1] - dsp->fConst0), min(10.0f, (20.0f * log10f(max(0.000316227757f, fabsf(fTemp5))))));
			dsp->fVbargraph5 = (FAUSTFLOAT)dsp->fRec5[0];
			output5[i] = (FAUSTFLOAT)dsp->iConst6;
			float fTemp6 = (float)input6[i];
			dsp->fRec6[0] = max((dsp->fRec6[1] - dsp->fConst0), min(10.0f, (20.0f * log10f(max(0.000316227757f, fabsf(fTemp6))))));
			dsp->fVbargraph6 = (FAUSTFLOAT)dsp->fRec6[0];
			output6[i] = (FAUSTFLOAT)dsp->iConst7;
			float fTemp7 = (float)input7[i];
			dsp->fRec7[0] = max((dsp->fRec7[1] - dsp->fConst0), min(10.0f, (20.0f * log10f(max(0.000316227757f, fabsf(fTemp7))))));
			dsp->fVbargraph7 = (FAUSTFLOAT)dsp->fRec7[0];
			output7[i] = (FAUSTFLOAT)dsp->iConst8;
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
