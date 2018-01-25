/* ------------------------------------------------------------
author: "O. Guillerminet"
copyright: "(c) O. Guillerminet 2012"
license: "BSD"
name: "UITester"
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
	
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT fEntry0;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT fVslider5;
	FAUSTFLOAT fVslider6;
	FAUSTFLOAT fButton0;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fVslider7;
	FAUSTFLOAT fVslider8;
	FAUSTFLOAT fVslider9;
	FAUSTFLOAT fEntry1;
	FAUSTFLOAT fVbargraph0;
	FAUSTFLOAT fVslider10;
	FAUSTFLOAT fVslider11;
	FAUSTFLOAT fVslider12;
	FAUSTFLOAT fEntry2;
	FAUSTFLOAT fVbargraph1;
	FAUSTFLOAT fVslider13;
	FAUSTFLOAT fVslider14;
	FAUSTFLOAT fVslider15;
	FAUSTFLOAT fEntry3;
	FAUSTFLOAT fVbargraph2;
	FAUSTFLOAT fHbargraph0;
	FAUSTFLOAT fVslider16;
	FAUSTFLOAT fButton1;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fEntry4;
	FAUSTFLOAT fVbargraph3;
	FAUSTFLOAT fHbargraph1;
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
	m->declare(m->metaInterface, "author", "O. Guillerminet");
	m->declare(m->metaInterface, "copyright", "(c) O. Guillerminet 2012");
	m->declare(m->metaInterface, "license", "BSD");
	m->declare(m->metaInterface, "name", "UITester");
	m->declare(m->metaInterface, "version", "1.0");
}

int getSampleRatemydsp(mydsp* dsp) { return dsp->fSamplingFreq; }

int getNumInputsmydsp(mydsp* dsp) {
	return 6;
	
}
int getNumOutputsmydsp(mydsp* dsp) {
	return 34;
	
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
		case 8: {
			rate = 1;
			break;
		}
		case 9: {
			rate = 1;
			break;
		}
		case 10: {
			rate = 1;
			break;
		}
		case 11: {
			rate = 1;
			break;
		}
		case 12: {
			rate = 1;
			break;
		}
		case 13: {
			rate = 1;
			break;
		}
		case 14: {
			rate = 1;
			break;
		}
		case 15: {
			rate = 1;
			break;
		}
		case 16: {
			rate = 1;
			break;
		}
		case 17: {
			rate = 1;
			break;
		}
		case 18: {
			rate = 1;
			break;
		}
		case 19: {
			rate = 1;
			break;
		}
		case 20: {
			rate = 1;
			break;
		}
		case 21: {
			rate = 1;
			break;
		}
		case 22: {
			rate = 1;
			break;
		}
		case 23: {
			rate = 1;
			break;
		}
		case 24: {
			rate = 1;
			break;
		}
		case 25: {
			rate = 1;
			break;
		}
		case 26: {
			rate = 1;
			break;
		}
		case 27: {
			rate = 1;
			break;
		}
		case 28: {
			rate = 1;
			break;
		}
		case 29: {
			rate = 1;
			break;
		}
		case 30: {
			rate = 1;
			break;
		}
		case 31: {
			rate = 1;
			break;
		}
		case 32: {
			rate = 1;
			break;
		}
		case 33: {
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
	dsp->fCheckbox0 = (FAUSTFLOAT)0.0f;
	dsp->fCheckbox1 = (FAUSTFLOAT)0.0f;
	dsp->fEntry0 = (FAUSTFLOAT)60.0f;
	dsp->fVslider0 = (FAUSTFLOAT)60.0f;
	dsp->fVslider1 = (FAUSTFLOAT)60.0f;
	dsp->fVslider2 = (FAUSTFLOAT)60.0f;
	dsp->fVslider3 = (FAUSTFLOAT)60.0f;
	dsp->fVslider4 = (FAUSTFLOAT)60.0f;
	dsp->fVslider5 = (FAUSTFLOAT)60.0f;
	dsp->fVslider6 = (FAUSTFLOAT)60.0f;
	dsp->fButton0 = (FAUSTFLOAT)0.0f;
	dsp->fHslider0 = (FAUSTFLOAT)60.0f;
	dsp->fVslider7 = (FAUSTFLOAT)60.0f;
	dsp->fVslider8 = (FAUSTFLOAT)60.0f;
	dsp->fVslider9 = (FAUSTFLOAT)60.0f;
	dsp->fEntry1 = (FAUSTFLOAT)60.0f;
	dsp->fVslider10 = (FAUSTFLOAT)60.0f;
	dsp->fVslider11 = (FAUSTFLOAT)60.0f;
	dsp->fVslider12 = (FAUSTFLOAT)60.0f;
	dsp->fEntry2 = (FAUSTFLOAT)60.0f;
	dsp->fVslider13 = (FAUSTFLOAT)60.0f;
	dsp->fVslider14 = (FAUSTFLOAT)60.0f;
	dsp->fVslider15 = (FAUSTFLOAT)60.0f;
	dsp->fEntry3 = (FAUSTFLOAT)60.0f;
	dsp->fVslider16 = (FAUSTFLOAT)60.0f;
	dsp->fButton1 = (FAUSTFLOAT)0.0f;
	dsp->fHslider1 = (FAUSTFLOAT)60.0f;
	dsp->fEntry4 = (FAUSTFLOAT)60.0f;
	
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
	ui_interface->openTabBox(ui_interface->uiInterface, "grp 1");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "hmisc");
	ui_interface->addButton(ui_interface->uiInterface, "button", &dsp->fButton1);
	ui_interface->addHorizontalBargraph(ui_interface->uiInterface, "hbar", &dsp->fHbargraph1, 0.0f, 127.0f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "hslider", &dsp->fHslider1, 60.0f, 0.0f, 127.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry4, "unit", "f");
	ui_interface->addNumEntry(ui_interface->uiInterface, "num", &dsp->fEntry4, 60.0f, 0.0f, 127.0f, 0.100000001f);
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "vbar", &dsp->fVbargraph3, 0.0f, 127.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider16, "unit", "f");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "vslider4", &dsp->fVslider16, 60.0f, 0.0f, 127.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "knobs");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider3, "style", "knob");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "knob1", &dsp->fVslider3, 60.0f, 0.0f, 127.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider4, "style", "knob");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "knob2", &dsp->fVslider4, 60.0f, 0.0f, 127.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider5, "style", "knob");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "knob3", &dsp->fVslider5, 60.0f, 0.0f, 127.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "sliders");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "vslider1", &dsp->fVslider0, 60.0f, 0.0f, 127.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "vslider2", &dsp->fVslider1, 60.0f, 0.0f, 127.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "vslider3", &dsp->fVslider2, 60.0f, 0.0f, 127.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "vbox");
	ui_interface->addCheckButton(ui_interface->uiInterface, "check1", &dsp->fCheckbox0);
	ui_interface->addCheckButton(ui_interface->uiInterface, "check2", &dsp->fCheckbox1);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry0, "style", "knob");
	ui_interface->addNumEntry(ui_interface->uiInterface, "knob0", &dsp->fEntry0, 60.0f, 0.0f, 127.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "vmisc");
	ui_interface->addButton(ui_interface->uiInterface, "button", &dsp->fButton0);
	ui_interface->addHorizontalBargraph(ui_interface->uiInterface, "hbar", &dsp->fHbargraph0, 0.0f, 127.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "unit", "Hz");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "hslider", &dsp->fHslider0, 60.0f, 0.0f, 127.0f, 0.100000001f);
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "small box 1");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider9, "style", "knob");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "knob4", &dsp->fVslider9, 60.0f, 0.0f, 127.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry1, "unit", "f");
	ui_interface->addNumEntry(ui_interface->uiInterface, "num1", &dsp->fEntry1, 60.0f, 0.0f, 127.0f, 0.100000001f);
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "vbar1", &dsp->fVbargraph0, 0.0f, 127.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider7, "unit", "Hz");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "vslider5", &dsp->fVslider7, 60.0f, 0.0f, 127.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider8, "unit", "Hz");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "vslider6", &dsp->fVslider8, 60.0f, 0.0f, 127.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "sub box 1");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "small box 2");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider12, "style", "knob");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "knob5", &dsp->fVslider12, 60.0f, 0.0f, 127.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry2, "unit", "f");
	ui_interface->addNumEntry(ui_interface->uiInterface, "num2", &dsp->fEntry2, 60.0f, 0.0f, 127.0f, 0.100000001f);
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "vbar2", &dsp->fVbargraph1, 0.0f, 127.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider10, "unit", "Hz");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "vslider7", &dsp->fVslider10, 60.0f, 0.0f, 127.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider11, "unit", "Hz");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "vslider8", &dsp->fVslider11, 60.0f, 0.0f, 127.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "small box 3");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider15, "style", "knob");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "knob6", &dsp->fVslider15, 60.0f, 0.0f, 127.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry3, "unit", "f");
	ui_interface->addNumEntry(ui_interface->uiInterface, "num3", &dsp->fEntry3, 60.0f, 0.0f, 127.0f, 0.100000001f);
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "vbar3", &dsp->fVbargraph2, 0.0f, 127.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider14, "unit", "m");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "vslider10", &dsp->fVslider14, 60.0f, 0.0f, 127.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider13, "unit", "Hz");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "vslider9", &dsp->fVslider13, 60.0f, 0.0f, 127.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider6, "unit", "Hz");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "vslider4", &dsp->fVslider6, 60.0f, 0.0f, 127.0f, 0.100000001f);
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
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	FAUSTFLOAT* output2 = outputs[2];
	FAUSTFLOAT* output3 = outputs[3];
	FAUSTFLOAT* output4 = outputs[4];
	FAUSTFLOAT* output5 = outputs[5];
	FAUSTFLOAT* output6 = outputs[6];
	FAUSTFLOAT* output7 = outputs[7];
	FAUSTFLOAT* output8 = outputs[8];
	FAUSTFLOAT* output9 = outputs[9];
	FAUSTFLOAT* output10 = outputs[10];
	FAUSTFLOAT* output11 = outputs[11];
	FAUSTFLOAT* output12 = outputs[12];
	FAUSTFLOAT* output13 = outputs[13];
	FAUSTFLOAT* output14 = outputs[14];
	FAUSTFLOAT* output15 = outputs[15];
	FAUSTFLOAT* output16 = outputs[16];
	FAUSTFLOAT* output17 = outputs[17];
	FAUSTFLOAT* output18 = outputs[18];
	FAUSTFLOAT* output19 = outputs[19];
	FAUSTFLOAT* output20 = outputs[20];
	FAUSTFLOAT* output21 = outputs[21];
	FAUSTFLOAT* output22 = outputs[22];
	FAUSTFLOAT* output23 = outputs[23];
	FAUSTFLOAT* output24 = outputs[24];
	FAUSTFLOAT* output25 = outputs[25];
	FAUSTFLOAT* output26 = outputs[26];
	FAUSTFLOAT* output27 = outputs[27];
	FAUSTFLOAT* output28 = outputs[28];
	FAUSTFLOAT* output29 = outputs[29];
	FAUSTFLOAT* output30 = outputs[30];
	FAUSTFLOAT* output31 = outputs[31];
	FAUSTFLOAT* output32 = outputs[32];
	FAUSTFLOAT* output33 = outputs[33];
	float fSlow0 = (float)dsp->fCheckbox0;
	float fSlow1 = (float)dsp->fCheckbox1;
	float fSlow2 = (float)dsp->fEntry0;
	float fSlow3 = (float)dsp->fVslider0;
	float fSlow4 = (float)dsp->fVslider1;
	float fSlow5 = (float)dsp->fVslider2;
	float fSlow6 = (float)dsp->fVslider3;
	float fSlow7 = (float)dsp->fVslider4;
	float fSlow8 = (float)dsp->fVslider5;
	float fSlow9 = (float)dsp->fVslider6;
	float fSlow10 = (float)dsp->fButton0;
	float fSlow11 = (float)dsp->fHslider0;
	float fSlow12 = (float)dsp->fVslider7;
	float fSlow13 = (float)dsp->fVslider8;
	float fSlow14 = (float)dsp->fVslider9;
	float fSlow15 = (float)dsp->fEntry1;
	float fSlow16 = (float)dsp->fVslider10;
	float fSlow17 = (float)dsp->fVslider11;
	float fSlow18 = (float)dsp->fVslider12;
	float fSlow19 = (float)dsp->fEntry2;
	float fSlow20 = (float)dsp->fVslider13;
	float fSlow21 = (float)dsp->fVslider14;
	float fSlow22 = (float)dsp->fVslider15;
	float fSlow23 = (float)dsp->fEntry3;
	float fSlow24 = (float)dsp->fVslider16;
	float fSlow25 = (float)dsp->fButton1;
	float fSlow26 = (float)dsp->fHslider1;
	float fSlow27 = (float)dsp->fEntry4;
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			output0[i] = (FAUSTFLOAT)fSlow0;
			output1[i] = (FAUSTFLOAT)fSlow1;
			output2[i] = (FAUSTFLOAT)fSlow2;
			output3[i] = (FAUSTFLOAT)fSlow3;
			output4[i] = (FAUSTFLOAT)fSlow4;
			output5[i] = (FAUSTFLOAT)fSlow5;
			output6[i] = (FAUSTFLOAT)fSlow6;
			output7[i] = (FAUSTFLOAT)fSlow7;
			output8[i] = (FAUSTFLOAT)fSlow8;
			output9[i] = (FAUSTFLOAT)fSlow9;
			output10[i] = (FAUSTFLOAT)fSlow10;
			output11[i] = (FAUSTFLOAT)fSlow11;
			output12[i] = (FAUSTFLOAT)fSlow12;
			output13[i] = (FAUSTFLOAT)fSlow13;
			output14[i] = (FAUSTFLOAT)fSlow14;
			output15[i] = (FAUSTFLOAT)fSlow15;
			dsp->fVbargraph0 = (FAUSTFLOAT)(float)input0[i];
			output16[i] = (FAUSTFLOAT)dsp->fVbargraph0;
			output17[i] = (FAUSTFLOAT)fSlow16;
			output18[i] = (FAUSTFLOAT)fSlow17;
			output19[i] = (FAUSTFLOAT)fSlow18;
			output20[i] = (FAUSTFLOAT)fSlow19;
			dsp->fVbargraph1 = (FAUSTFLOAT)(float)input1[i];
			output21[i] = (FAUSTFLOAT)dsp->fVbargraph1;
			output22[i] = (FAUSTFLOAT)fSlow20;
			output23[i] = (FAUSTFLOAT)fSlow21;
			output24[i] = (FAUSTFLOAT)fSlow22;
			output25[i] = (FAUSTFLOAT)fSlow23;
			dsp->fVbargraph2 = (FAUSTFLOAT)(float)input2[i];
			output26[i] = (FAUSTFLOAT)dsp->fVbargraph2;
			dsp->fHbargraph0 = (FAUSTFLOAT)(float)input3[i];
			output27[i] = (FAUSTFLOAT)dsp->fHbargraph0;
			output28[i] = (FAUSTFLOAT)fSlow24;
			output29[i] = (FAUSTFLOAT)fSlow25;
			output30[i] = (FAUSTFLOAT)fSlow26;
			output31[i] = (FAUSTFLOAT)fSlow27;
			dsp->fVbargraph3 = (FAUSTFLOAT)(float)input4[i];
			output32[i] = (FAUSTFLOAT)dsp->fVbargraph3;
			dsp->fHbargraph1 = (FAUSTFLOAT)(float)input5[i];
			output33[i] = (FAUSTFLOAT)dsp->fHbargraph1;
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
