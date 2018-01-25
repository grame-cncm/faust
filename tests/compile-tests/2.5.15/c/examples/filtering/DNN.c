/* ------------------------------------------------------------
author: "JOS"
license: "STK-4.3"
name: "DNN"
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
	
} mydsp;

mydsp* newmydsp() { 
	mydsp* dsp = (mydsp*)malloc(sizeof(mydsp));
	return dsp;
}

void deletemydsp(mydsp* dsp) { 
	free(dsp);
}

void metadatamydsp(MetaGlue* m) { 
	m->declare(m->metaInterface, "author", "JOS");
	m->declare(m->metaInterface, "basics.lib/name", "Faust Basic Element Library");
	m->declare(m->metaInterface, "basics.lib/version", "0.0");
	m->declare(m->metaInterface, "license", "STK-4.3");
	m->declare(m->metaInterface, "name", "DNN");
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
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "DNN");
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
			float fTemp0 = (float)input7[i];
			float fTemp1 = (float)input6[i];
			float fTemp2 = (float)input5[i];
			float fTemp3 = (float)input4[i];
			float fTemp4 = (float)input2[i];
			float fTemp5 = (float)input1[i];
			float fTemp6 = (float)input3[i];
			float fTemp7 = ((30.0f * fTemp0) + ((60.0f * fTemp1) + ((10.0f * fTemp2) + ((40.0f * fTemp3) + (((20.0f * fTemp4) + (50.0f * fTemp5)) + (70.0f * fTemp6))))));
			float fTemp8 = ((float)(fTemp7 > 0.0f) * fTemp7);
			float fTemp9 = (float)input0[i];
			float fTemp10 = ((43.0f * fTemp0) + (((23.0f * fTemp2) + ((53.0f * fTemp3) + ((3.0f * fTemp6) + ((33.0f * fTemp4) + ((13.0f * fTemp9) + (63.0f * fTemp5)))))) + (73.0f * fTemp1)));
			float fTemp11 = ((float)(fTemp10 > 0.0f) * fTemp10);
			float fTemp12 = ((61.0f * fTemp0) + ((11.0f * fTemp1) + ((41.0f * fTemp2) + (((21.0f * fTemp6) + ((fTemp5 + (31.0f * fTemp9)) + (51.0f * fTemp4))) + (71.0f * fTemp3)))));
			float fTemp13 = ((float)(fTemp12 > 0.0f) * fTemp12);
			float fTemp14 = (((24.0f * fTemp1) + ((54.0f * fTemp2) + ((4.0f * fTemp3) + ((34.0f * fTemp6) + (((14.0f * fTemp5) + (44.0f * fTemp9)) + (64.0f * fTemp4)))))) + (74.0f * fTemp0));
			float fTemp15 = (fTemp14 * (float)(fTemp14 > 0.0f));
			float fTemp16 = ((12.0f * fTemp0) + ((42.0f * fTemp1) + (((22.0f * fTemp3) + ((52.0f * fTemp6) + ((2.0f * fTemp4) + ((32.0f * fTemp5) + (62.0f * fTemp9))))) + (72.0f * fTemp2))));
			float fTemp17 = ((float)(fTemp16 > 0.0f) * fTemp16);
			float fTemp18 = (((((100.0f * fTemp8) + (110.0f * fTemp11)) + (120.0f * fTemp13)) + (130.0f * fTemp15)) + (140.0f * fTemp17));
			output0[i] = (FAUSTFLOAT)(fTemp18 * (float)(fTemp18 > 0.0f));
			float fTemp19 = ((121.0f * fTemp17) + ((111.0f * fTemp15) + ((101.0f * fTemp13) + ((131.0f * fTemp8) + (141.0f * fTemp11)))));
			output1[i] = (FAUSTFLOAT)((float)(fTemp19 > 0.0f) * fTemp19);
			float fTemp20 = ((102.0f * fTemp17) + ((((112.0f * fTemp8) + (122.0f * fTemp11)) + (132.0f * fTemp13)) + (142.0f * fTemp15)));
			output2[i] = (FAUSTFLOAT)((float)(fTemp20 > 0.0f) * fTemp20);
			float fTemp21 = ((133.0f * fTemp17) + ((123.0f * fTemp15) + ((113.0f * fTemp13) + ((103.0f * fTemp11) + (143.0f * fTemp8)))));
			output3[i] = (FAUSTFLOAT)((float)(fTemp21 > 0.0f) * fTemp21);
			float fTemp22 = ((114.0f * fTemp17) + ((104.0f * fTemp15) + (((124.0f * fTemp8) + (134.0f * fTemp11)) + (144.0f * fTemp13))));
			output4[i] = (FAUSTFLOAT)((float)(fTemp22 > 0.0f) * fTemp22);
			float fTemp23 = (((((105.0f * fTemp8) + (115.0f * fTemp11)) + (125.0f * fTemp13)) + (135.0f * fTemp15)) + (145.0f * fTemp17));
			output5[i] = (FAUSTFLOAT)(fTemp23 * (float)(fTemp23 > 0.0f));
			float fTemp24 = ((126.0f * fTemp17) + ((116.0f * fTemp15) + ((106.0f * fTemp13) + ((136.0f * fTemp8) + (146.0f * fTemp11)))));
			output6[i] = (FAUSTFLOAT)((float)(fTemp24 > 0.0f) * fTemp24);
			float fTemp25 = ((107.0f * fTemp17) + ((((117.0f * fTemp8) + (127.0f * fTemp11)) + (137.0f * fTemp13)) + (147.0f * fTemp15)));
			output7[i] = (FAUSTFLOAT)((float)(fTemp25 > 0.0f) * fTemp25);
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
