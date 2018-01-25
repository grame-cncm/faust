/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2006"
license: "BSD"
name: "matrix"
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
	
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT fVslider5;
	FAUSTFLOAT fVslider6;
	FAUSTFLOAT fVslider7;
	FAUSTFLOAT fVslider8;
	FAUSTFLOAT fVslider9;
	FAUSTFLOAT fVslider10;
	FAUSTFLOAT fVslider11;
	FAUSTFLOAT fVslider12;
	FAUSTFLOAT fVslider13;
	FAUSTFLOAT fVslider14;
	FAUSTFLOAT fVslider15;
	FAUSTFLOAT fVslider16;
	FAUSTFLOAT fVslider17;
	FAUSTFLOAT fVslider18;
	FAUSTFLOAT fVslider19;
	FAUSTFLOAT fVslider20;
	FAUSTFLOAT fVslider21;
	FAUSTFLOAT fVslider22;
	FAUSTFLOAT fVslider23;
	FAUSTFLOAT fVslider24;
	FAUSTFLOAT fVslider25;
	FAUSTFLOAT fVslider26;
	FAUSTFLOAT fVslider27;
	FAUSTFLOAT fVslider28;
	FAUSTFLOAT fVslider29;
	FAUSTFLOAT fVslider30;
	FAUSTFLOAT fVslider31;
	FAUSTFLOAT fVslider32;
	FAUSTFLOAT fVslider33;
	FAUSTFLOAT fVslider34;
	FAUSTFLOAT fVslider35;
	FAUSTFLOAT fVslider36;
	FAUSTFLOAT fVslider37;
	FAUSTFLOAT fVslider38;
	FAUSTFLOAT fVslider39;
	FAUSTFLOAT fVslider40;
	FAUSTFLOAT fVslider41;
	FAUSTFLOAT fVslider42;
	FAUSTFLOAT fVslider43;
	FAUSTFLOAT fVslider44;
	FAUSTFLOAT fVslider45;
	FAUSTFLOAT fVslider46;
	FAUSTFLOAT fVslider47;
	FAUSTFLOAT fVslider48;
	FAUSTFLOAT fVslider49;
	FAUSTFLOAT fVslider50;
	FAUSTFLOAT fVslider51;
	FAUSTFLOAT fVslider52;
	FAUSTFLOAT fVslider53;
	FAUSTFLOAT fVslider54;
	FAUSTFLOAT fVslider55;
	FAUSTFLOAT fVslider56;
	FAUSTFLOAT fVslider57;
	FAUSTFLOAT fVslider58;
	FAUSTFLOAT fVslider59;
	FAUSTFLOAT fVslider60;
	FAUSTFLOAT fVslider61;
	FAUSTFLOAT fVslider62;
	FAUSTFLOAT fVslider63;
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
	m->declare(m->metaInterface, "author", "Grame");
	m->declare(m->metaInterface, "basics.lib/name", "Faust Basic Element Library");
	m->declare(m->metaInterface, "basics.lib/version", "0.0");
	m->declare(m->metaInterface, "copyright", "(c)GRAME 2006");
	m->declare(m->metaInterface, "license", "BSD");
	m->declare(m->metaInterface, "name", "matrix");
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
	dsp->fVslider0 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider1 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider2 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider3 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider4 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider5 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider6 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider7 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider8 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider9 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider10 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider11 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider12 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider13 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider14 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider15 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider16 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider17 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider18 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider19 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider20 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider21 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider22 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider23 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider24 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider25 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider26 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider27 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider28 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider29 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider30 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider31 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider32 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider33 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider34 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider35 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider36 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider37 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider38 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider39 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider40 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider41 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider42 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider43 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider44 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider45 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider46 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider47 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider48 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider49 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider50 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider51 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider52 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider53 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider54 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider55 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider56 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider57 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider58 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider59 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider60 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider61 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider62 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider63 = (FAUSTFLOAT)-10.0f;
	
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
	ui_interface->openTabBox(ui_interface->uiInterface, "Matrix 8 x 8");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "Output 0");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 0", &dsp->fVslider0, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 1", &dsp->fVslider1, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 2", &dsp->fVslider2, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 3", &dsp->fVslider3, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 4", &dsp->fVslider4, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 5", &dsp->fVslider5, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 6", &dsp->fVslider6, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 7", &dsp->fVslider7, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "Output 1");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 0", &dsp->fVslider8, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 1", &dsp->fVslider9, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 2", &dsp->fVslider10, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 3", &dsp->fVslider11, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 4", &dsp->fVslider12, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 5", &dsp->fVslider13, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 6", &dsp->fVslider14, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 7", &dsp->fVslider15, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "Output 2");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 0", &dsp->fVslider16, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 1", &dsp->fVslider17, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 2", &dsp->fVslider18, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 3", &dsp->fVslider19, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 4", &dsp->fVslider20, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 5", &dsp->fVslider21, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 6", &dsp->fVslider22, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 7", &dsp->fVslider23, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "Output 3");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 0", &dsp->fVslider24, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 1", &dsp->fVslider25, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 2", &dsp->fVslider26, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 3", &dsp->fVslider27, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 4", &dsp->fVslider28, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 5", &dsp->fVslider29, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 6", &dsp->fVslider30, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 7", &dsp->fVslider31, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "Output 4");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 0", &dsp->fVslider32, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 1", &dsp->fVslider33, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 2", &dsp->fVslider34, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 3", &dsp->fVslider35, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 4", &dsp->fVslider36, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 5", &dsp->fVslider37, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 6", &dsp->fVslider38, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 7", &dsp->fVslider39, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "Output 5");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 0", &dsp->fVslider40, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 1", &dsp->fVslider41, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 2", &dsp->fVslider42, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 3", &dsp->fVslider43, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 4", &dsp->fVslider44, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 5", &dsp->fVslider45, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 6", &dsp->fVslider46, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 7", &dsp->fVslider47, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "Output 6");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 0", &dsp->fVslider48, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 1", &dsp->fVslider49, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 2", &dsp->fVslider50, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 3", &dsp->fVslider51, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 4", &dsp->fVslider52, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 5", &dsp->fVslider53, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 6", &dsp->fVslider54, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 7", &dsp->fVslider55, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "Output 7");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 0", &dsp->fVslider56, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 1", &dsp->fVslider57, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 2", &dsp->fVslider58, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 3", &dsp->fVslider59, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 4", &dsp->fVslider60, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 5", &dsp->fVslider61, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 6", &dsp->fVslider62, -10.0f, -96.0f, 4.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Input 7", &dsp->fVslider63, -10.0f, -96.0f, 4.0f, 0.100000001f);
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
	float fSlow0 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider0));
	float fSlow1 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider1));
	float fSlow2 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider2));
	float fSlow3 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider3));
	float fSlow4 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider4));
	float fSlow5 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider5));
	float fSlow6 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider6));
	float fSlow7 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider7));
	float fSlow8 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider8));
	float fSlow9 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider9));
	float fSlow10 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider10));
	float fSlow11 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider11));
	float fSlow12 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider12));
	float fSlow13 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider13));
	float fSlow14 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider14));
	float fSlow15 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider15));
	float fSlow16 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider16));
	float fSlow17 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider17));
	float fSlow18 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider18));
	float fSlow19 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider19));
	float fSlow20 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider20));
	float fSlow21 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider21));
	float fSlow22 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider22));
	float fSlow23 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider23));
	float fSlow24 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider24));
	float fSlow25 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider25));
	float fSlow26 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider26));
	float fSlow27 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider27));
	float fSlow28 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider28));
	float fSlow29 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider29));
	float fSlow30 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider30));
	float fSlow31 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider31));
	float fSlow32 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider32));
	float fSlow33 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider33));
	float fSlow34 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider34));
	float fSlow35 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider35));
	float fSlow36 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider36));
	float fSlow37 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider37));
	float fSlow38 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider38));
	float fSlow39 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider39));
	float fSlow40 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider40));
	float fSlow41 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider41));
	float fSlow42 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider42));
	float fSlow43 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider43));
	float fSlow44 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider44));
	float fSlow45 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider45));
	float fSlow46 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider46));
	float fSlow47 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider47));
	float fSlow48 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider48));
	float fSlow49 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider49));
	float fSlow50 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider50));
	float fSlow51 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider51));
	float fSlow52 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider52));
	float fSlow53 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider53));
	float fSlow54 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider54));
	float fSlow55 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider55));
	float fSlow56 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider56));
	float fSlow57 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider57));
	float fSlow58 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider58));
	float fSlow59 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider59));
	float fSlow60 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider60));
	float fSlow61 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider61));
	float fSlow62 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider62));
	float fSlow63 = powf(10.0f, (0.0500000007f * (float)dsp->fVslider63));
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = (float)input0[i];
			float fTemp1 = (float)input1[i];
			float fTemp2 = (float)input2[i];
			float fTemp3 = (float)input3[i];
			float fTemp4 = (float)input4[i];
			float fTemp5 = (float)input5[i];
			float fTemp6 = (float)input6[i];
			float fTemp7 = (float)input7[i];
			output0[i] = (FAUSTFLOAT)((((((((fSlow0 * fTemp0) + (fSlow1 * fTemp1)) + (fSlow2 * fTemp2)) + (fSlow3 * fTemp3)) + (fSlow4 * fTemp4)) + (fSlow5 * fTemp5)) + (fSlow6 * fTemp6)) + (fSlow7 * fTemp7));
			output1[i] = (FAUSTFLOAT)((((((((fSlow8 * fTemp0) + (fSlow9 * fTemp1)) + (fSlow10 * fTemp2)) + (fSlow11 * fTemp3)) + (fSlow12 * fTemp4)) + (fSlow13 * fTemp5)) + (fSlow14 * fTemp6)) + (fSlow15 * fTemp7));
			output2[i] = (FAUSTFLOAT)((((((((fSlow16 * fTemp0) + (fSlow17 * fTemp1)) + (fSlow18 * fTemp2)) + (fSlow19 * fTemp3)) + (fSlow20 * fTemp4)) + (fSlow21 * fTemp5)) + (fSlow22 * fTemp6)) + (fSlow23 * fTemp7));
			output3[i] = (FAUSTFLOAT)((((((((fSlow24 * fTemp0) + (fSlow25 * fTemp1)) + (fSlow26 * fTemp2)) + (fSlow27 * fTemp3)) + (fSlow28 * fTemp4)) + (fSlow29 * fTemp5)) + (fSlow30 * fTemp6)) + (fSlow31 * fTemp7));
			output4[i] = (FAUSTFLOAT)((((((((fSlow32 * fTemp0) + (fSlow33 * fTemp1)) + (fSlow34 * fTemp2)) + (fSlow35 * fTemp3)) + (fSlow36 * fTemp4)) + (fSlow37 * fTemp5)) + (fSlow38 * fTemp6)) + (fSlow39 * fTemp7));
			output5[i] = (FAUSTFLOAT)((((((((fSlow40 * fTemp0) + (fSlow41 * fTemp1)) + (fSlow42 * fTemp2)) + (fSlow43 * fTemp3)) + (fSlow44 * fTemp4)) + (fSlow45 * fTemp5)) + (fSlow46 * fTemp6)) + (fSlow47 * fTemp7));
			output6[i] = (FAUSTFLOAT)((((((((fSlow48 * fTemp0) + (fSlow49 * fTemp1)) + (fSlow50 * fTemp2)) + (fSlow51 * fTemp3)) + (fSlow52 * fTemp4)) + (fSlow53 * fTemp5)) + (fSlow54 * fTemp6)) + (fSlow55 * fTemp7));
			output7[i] = (FAUSTFLOAT)((((((((fSlow56 * fTemp0) + (fSlow57 * fTemp1)) + (fSlow58 * fTemp2)) + (fSlow59 * fTemp3)) + (fSlow60 * fTemp4)) + (fSlow61 * fTemp5)) + (fSlow62 * fTemp6)) + (fSlow63 * fTemp7));
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
