/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2006"
license: "BSD"
name: "tapiir"
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
	int IOTA;
	float fVec0[1048576];
	int fSamplingFreq;
	float fConst0;
	FAUSTFLOAT fVslider11;
	float fRec0[2];
	FAUSTFLOAT fVslider12;
	FAUSTFLOAT fVslider13;
	FAUSTFLOAT fVslider14;
	FAUSTFLOAT fVslider15;
	FAUSTFLOAT fVslider16;
	FAUSTFLOAT fVslider17;
	FAUSTFLOAT fVslider18;
	FAUSTFLOAT fVslider19;
	FAUSTFLOAT fVslider20;
	float fVec1[1048576];
	FAUSTFLOAT fVslider21;
	float fRec1[2];
	FAUSTFLOAT fVslider22;
	FAUSTFLOAT fVslider23;
	FAUSTFLOAT fVslider24;
	FAUSTFLOAT fVslider25;
	FAUSTFLOAT fVslider26;
	FAUSTFLOAT fVslider27;
	FAUSTFLOAT fVslider28;
	FAUSTFLOAT fVslider29;
	FAUSTFLOAT fVslider30;
	float fVec2[1048576];
	FAUSTFLOAT fVslider31;
	float fRec2[2];
	FAUSTFLOAT fVslider32;
	FAUSTFLOAT fVslider33;
	FAUSTFLOAT fVslider34;
	FAUSTFLOAT fVslider35;
	FAUSTFLOAT fVslider36;
	FAUSTFLOAT fVslider37;
	FAUSTFLOAT fVslider38;
	FAUSTFLOAT fVslider39;
	FAUSTFLOAT fVslider40;
	float fVec3[1048576];
	FAUSTFLOAT fVslider41;
	float fRec3[2];
	FAUSTFLOAT fVslider42;
	FAUSTFLOAT fVslider43;
	FAUSTFLOAT fVslider44;
	FAUSTFLOAT fVslider45;
	FAUSTFLOAT fVslider46;
	FAUSTFLOAT fVslider47;
	FAUSTFLOAT fVslider48;
	FAUSTFLOAT fVslider49;
	FAUSTFLOAT fVslider50;
	float fVec4[1048576];
	FAUSTFLOAT fVslider51;
	float fRec4[2];
	FAUSTFLOAT fVslider52;
	FAUSTFLOAT fVslider53;
	FAUSTFLOAT fVslider54;
	FAUSTFLOAT fVslider55;
	FAUSTFLOAT fVslider56;
	FAUSTFLOAT fVslider57;
	FAUSTFLOAT fVslider58;
	FAUSTFLOAT fVslider59;
	FAUSTFLOAT fVslider60;
	float fVec5[1048576];
	FAUSTFLOAT fVslider61;
	float fRec5[2];
	FAUSTFLOAT fVslider62;
	FAUSTFLOAT fVslider63;
	FAUSTFLOAT fVslider64;
	FAUSTFLOAT fVslider65;
	FAUSTFLOAT fVslider66;
	FAUSTFLOAT fVslider67;
	FAUSTFLOAT fVslider68;
	FAUSTFLOAT fVslider69;
	FAUSTFLOAT fVslider70;
	FAUSTFLOAT fVslider71;
	FAUSTFLOAT fVslider72;
	FAUSTFLOAT fVslider73;
	FAUSTFLOAT fVslider74;
	FAUSTFLOAT fVslider75;
	FAUSTFLOAT fVslider76;
	FAUSTFLOAT fVslider77;
	
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
	m->declare(m->metaInterface, "copyright", "(c)GRAME 2006");
	m->declare(m->metaInterface, "delays.lib/name", "Faust Delay Library");
	m->declare(m->metaInterface, "delays.lib/version", "0.0");
	m->declare(m->metaInterface, "license", "BSD");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "tapiir");
	m->declare(m->metaInterface, "signals.lib/name", "Faust Signal Routing Library");
	m->declare(m->metaInterface, "signals.lib/version", "0.0");
	m->declare(m->metaInterface, "version", "1.0");
}

int getSampleRatemydsp(mydsp* dsp) { return dsp->fSamplingFreq; }

int getNumInputsmydsp(mydsp* dsp) {
	return 2;
	
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
	dsp->fVslider0 = (FAUSTFLOAT)1.0f;
	dsp->fVslider1 = (FAUSTFLOAT)0.0f;
	dsp->fVslider2 = (FAUSTFLOAT)1.0f;
	dsp->fVslider3 = (FAUSTFLOAT)0.0f;
	dsp->fVslider4 = (FAUSTFLOAT)0.0f;
	dsp->fVslider5 = (FAUSTFLOAT)0.0f;
	dsp->fVslider6 = (FAUSTFLOAT)0.0f;
	dsp->fVslider7 = (FAUSTFLOAT)0.0f;
	dsp->fVslider8 = (FAUSTFLOAT)0.0f;
	dsp->fVslider9 = (FAUSTFLOAT)1.0f;
	dsp->fVslider10 = (FAUSTFLOAT)1.0f;
	dsp->fVslider11 = (FAUSTFLOAT)0.0f;
	dsp->fVslider12 = (FAUSTFLOAT)1.0f;
	dsp->fVslider13 = (FAUSTFLOAT)0.0f;
	dsp->fVslider14 = (FAUSTFLOAT)0.0f;
	dsp->fVslider15 = (FAUSTFLOAT)0.0f;
	dsp->fVslider16 = (FAUSTFLOAT)0.0f;
	dsp->fVslider17 = (FAUSTFLOAT)0.0f;
	dsp->fVslider18 = (FAUSTFLOAT)0.0f;
	dsp->fVslider19 = (FAUSTFLOAT)1.0f;
	dsp->fVslider20 = (FAUSTFLOAT)1.0f;
	dsp->fVslider21 = (FAUSTFLOAT)0.0f;
	dsp->fVslider22 = (FAUSTFLOAT)1.0f;
	dsp->fVslider23 = (FAUSTFLOAT)0.0f;
	dsp->fVslider24 = (FAUSTFLOAT)0.0f;
	dsp->fVslider25 = (FAUSTFLOAT)0.0f;
	dsp->fVslider26 = (FAUSTFLOAT)0.0f;
	dsp->fVslider27 = (FAUSTFLOAT)0.0f;
	dsp->fVslider28 = (FAUSTFLOAT)0.0f;
	dsp->fVslider29 = (FAUSTFLOAT)1.0f;
	dsp->fVslider30 = (FAUSTFLOAT)1.0f;
	dsp->fVslider31 = (FAUSTFLOAT)0.0f;
	dsp->fVslider32 = (FAUSTFLOAT)1.0f;
	dsp->fVslider33 = (FAUSTFLOAT)0.0f;
	dsp->fVslider34 = (FAUSTFLOAT)0.0f;
	dsp->fVslider35 = (FAUSTFLOAT)0.0f;
	dsp->fVslider36 = (FAUSTFLOAT)0.0f;
	dsp->fVslider37 = (FAUSTFLOAT)0.0f;
	dsp->fVslider38 = (FAUSTFLOAT)0.0f;
	dsp->fVslider39 = (FAUSTFLOAT)1.0f;
	dsp->fVslider40 = (FAUSTFLOAT)1.0f;
	dsp->fVslider41 = (FAUSTFLOAT)0.0f;
	dsp->fVslider42 = (FAUSTFLOAT)1.0f;
	dsp->fVslider43 = (FAUSTFLOAT)0.0f;
	dsp->fVslider44 = (FAUSTFLOAT)0.0f;
	dsp->fVslider45 = (FAUSTFLOAT)0.0f;
	dsp->fVslider46 = (FAUSTFLOAT)0.0f;
	dsp->fVslider47 = (FAUSTFLOAT)0.0f;
	dsp->fVslider48 = (FAUSTFLOAT)0.0f;
	dsp->fVslider49 = (FAUSTFLOAT)1.0f;
	dsp->fVslider50 = (FAUSTFLOAT)1.0f;
	dsp->fVslider51 = (FAUSTFLOAT)0.0f;
	dsp->fVslider52 = (FAUSTFLOAT)1.0f;
	dsp->fVslider53 = (FAUSTFLOAT)0.0f;
	dsp->fVslider54 = (FAUSTFLOAT)0.0f;
	dsp->fVslider55 = (FAUSTFLOAT)0.0f;
	dsp->fVslider56 = (FAUSTFLOAT)0.0f;
	dsp->fVslider57 = (FAUSTFLOAT)0.0f;
	dsp->fVslider58 = (FAUSTFLOAT)0.0f;
	dsp->fVslider59 = (FAUSTFLOAT)1.0f;
	dsp->fVslider60 = (FAUSTFLOAT)1.0f;
	dsp->fVslider61 = (FAUSTFLOAT)0.0f;
	dsp->fVslider62 = (FAUSTFLOAT)0.0f;
	dsp->fVslider63 = (FAUSTFLOAT)0.0f;
	dsp->fVslider64 = (FAUSTFLOAT)0.0f;
	dsp->fVslider65 = (FAUSTFLOAT)0.0f;
	dsp->fVslider66 = (FAUSTFLOAT)0.0f;
	dsp->fVslider67 = (FAUSTFLOAT)1.0f;
	dsp->fVslider68 = (FAUSTFLOAT)1.0f;
	dsp->fVslider69 = (FAUSTFLOAT)1.0f;
	dsp->fVslider70 = (FAUSTFLOAT)0.0f;
	dsp->fVslider71 = (FAUSTFLOAT)0.0f;
	dsp->fVslider72 = (FAUSTFLOAT)0.0f;
	dsp->fVslider73 = (FAUSTFLOAT)0.0f;
	dsp->fVslider74 = (FAUSTFLOAT)0.0f;
	dsp->fVslider75 = (FAUSTFLOAT)0.0f;
	dsp->fVslider76 = (FAUSTFLOAT)1.0f;
	dsp->fVslider77 = (FAUSTFLOAT)1.0f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	dsp->IOTA = 0;
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 1048576); l0 = (l0 + 1)) {
			dsp->fVec0[l0] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			dsp->fRec0[l1] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 1048576); l2 = (l2 + 1)) {
			dsp->fVec1[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			dsp->fRec1[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 1048576); l4 = (l4 + 1)) {
			dsp->fVec2[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			dsp->fRec2[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 1048576); l6 = (l6 + 1)) {
			dsp->fVec3[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			dsp->fRec3[l7] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 1048576); l8 = (l8 + 1)) {
			dsp->fVec4[l8] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			dsp->fRec4[l9] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 1048576); l10 = (l10 + 1)) {
			dsp->fVec5[l10] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			dsp->fRec5[l11] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "Tapiir");
	ui_interface->openTabBox(ui_interface->uiInterface, "0x00");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "Tap 0");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "delay (sec)", &dsp->fVslider11, 0.0f, 0.0f, 5.0f, 0.00999999978f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "gain", &dsp->fVslider2, 1.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "input 0", &dsp->fVslider9, 1.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "input 1", &dsp->fVslider10, 1.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 0", &dsp->fVslider3, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 1", &dsp->fVslider4, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 2", &dsp->fVslider5, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 3", &dsp->fVslider6, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 4", &dsp->fVslider7, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 5", &dsp->fVslider8, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "Tap 1");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "delay (sec)", &dsp->fVslider21, 0.0f, 0.0f, 5.0f, 0.00999999978f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "gain", &dsp->fVslider12, 1.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "input 0", &dsp->fVslider19, 1.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "input 1", &dsp->fVslider20, 1.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 0", &dsp->fVslider13, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 1", &dsp->fVslider14, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 2", &dsp->fVslider15, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 3", &dsp->fVslider16, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 4", &dsp->fVslider17, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 5", &dsp->fVslider18, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "Tap 2");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "delay (sec)", &dsp->fVslider31, 0.0f, 0.0f, 5.0f, 0.00999999978f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "gain", &dsp->fVslider22, 1.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "input 0", &dsp->fVslider29, 1.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "input 1", &dsp->fVslider30, 1.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 0", &dsp->fVslider23, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 1", &dsp->fVslider24, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 2", &dsp->fVslider25, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 3", &dsp->fVslider26, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 4", &dsp->fVslider27, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 5", &dsp->fVslider28, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "Tap 3");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "delay (sec)", &dsp->fVslider41, 0.0f, 0.0f, 5.0f, 0.00999999978f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "gain", &dsp->fVslider32, 1.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "input 0", &dsp->fVslider39, 1.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "input 1", &dsp->fVslider40, 1.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 0", &dsp->fVslider33, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 1", &dsp->fVslider34, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 2", &dsp->fVslider35, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 3", &dsp->fVslider36, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 4", &dsp->fVslider37, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 5", &dsp->fVslider38, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "Tap 4");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "delay (sec)", &dsp->fVslider51, 0.0f, 0.0f, 5.0f, 0.00999999978f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "gain", &dsp->fVslider42, 1.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "input 0", &dsp->fVslider49, 1.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "input 1", &dsp->fVslider50, 1.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 0", &dsp->fVslider43, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 1", &dsp->fVslider44, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 2", &dsp->fVslider45, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 3", &dsp->fVslider46, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 4", &dsp->fVslider47, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 5", &dsp->fVslider48, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "Tap 5");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "delay (sec)", &dsp->fVslider61, 0.0f, 0.0f, 5.0f, 0.00999999978f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "gain", &dsp->fVslider52, 1.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "input 0", &dsp->fVslider59, 1.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "input 1", &dsp->fVslider60, 1.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 0", &dsp->fVslider53, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 1", &dsp->fVslider54, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 2", &dsp->fVslider55, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 3", &dsp->fVslider56, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 4", &dsp->fVslider57, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 5", &dsp->fVslider58, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "outputs");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "output 0");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "gain", &dsp->fVslider0, 1.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "input 0", &dsp->fVslider67, 1.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "input 1", &dsp->fVslider68, 1.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 0", &dsp->fVslider1, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 1", &dsp->fVslider62, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 2", &dsp->fVslider63, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 3", &dsp->fVslider64, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 4", &dsp->fVslider65, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 5", &dsp->fVslider66, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "output 1");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "gain", &dsp->fVslider69, 1.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "input 0", &dsp->fVslider76, 1.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "input 1", &dsp->fVslider77, 1.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 0", &dsp->fVslider70, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 1", &dsp->fVslider71, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 2", &dsp->fVslider72, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 3", &dsp->fVslider73, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 4", &dsp->fVslider74, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "tap 5", &dsp->fVslider75, 0.0f, 0.0f, 1.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* input0 = inputs[0];
	FAUSTFLOAT* input1 = inputs[1];
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	float fSlow0 = (float)dsp->fVslider0;
	float fSlow1 = (float)dsp->fVslider1;
	float fSlow2 = (float)dsp->fVslider2;
	float fSlow3 = (float)dsp->fVslider3;
	float fSlow4 = (float)dsp->fVslider4;
	float fSlow5 = (float)dsp->fVslider5;
	float fSlow6 = (float)dsp->fVslider6;
	float fSlow7 = (float)dsp->fVslider7;
	float fSlow8 = (float)dsp->fVslider8;
	float fSlow9 = (float)dsp->fVslider9;
	float fSlow10 = (float)dsp->fVslider10;
	int iSlow11 = (int)min(524288.0f, max(0.0f, (dsp->fConst0 * (float)dsp->fVslider11)));
	float fSlow12 = (float)dsp->fVslider12;
	float fSlow13 = (float)dsp->fVslider13;
	float fSlow14 = (float)dsp->fVslider14;
	float fSlow15 = (float)dsp->fVslider15;
	float fSlow16 = (float)dsp->fVslider16;
	float fSlow17 = (float)dsp->fVslider17;
	float fSlow18 = (float)dsp->fVslider18;
	float fSlow19 = (float)dsp->fVslider19;
	float fSlow20 = (float)dsp->fVslider20;
	int iSlow21 = (int)min(524288.0f, max(0.0f, (dsp->fConst0 * (float)dsp->fVslider21)));
	float fSlow22 = (float)dsp->fVslider22;
	float fSlow23 = (float)dsp->fVslider23;
	float fSlow24 = (float)dsp->fVslider24;
	float fSlow25 = (float)dsp->fVslider25;
	float fSlow26 = (float)dsp->fVslider26;
	float fSlow27 = (float)dsp->fVslider27;
	float fSlow28 = (float)dsp->fVslider28;
	float fSlow29 = (float)dsp->fVslider29;
	float fSlow30 = (float)dsp->fVslider30;
	int iSlow31 = (int)min(524288.0f, max(0.0f, (dsp->fConst0 * (float)dsp->fVslider31)));
	float fSlow32 = (float)dsp->fVslider32;
	float fSlow33 = (float)dsp->fVslider33;
	float fSlow34 = (float)dsp->fVslider34;
	float fSlow35 = (float)dsp->fVslider35;
	float fSlow36 = (float)dsp->fVslider36;
	float fSlow37 = (float)dsp->fVslider37;
	float fSlow38 = (float)dsp->fVslider38;
	float fSlow39 = (float)dsp->fVslider39;
	float fSlow40 = (float)dsp->fVslider40;
	int iSlow41 = (int)min(524288.0f, max(0.0f, (dsp->fConst0 * (float)dsp->fVslider41)));
	float fSlow42 = (float)dsp->fVslider42;
	float fSlow43 = (float)dsp->fVslider43;
	float fSlow44 = (float)dsp->fVslider44;
	float fSlow45 = (float)dsp->fVslider45;
	float fSlow46 = (float)dsp->fVslider46;
	float fSlow47 = (float)dsp->fVslider47;
	float fSlow48 = (float)dsp->fVslider48;
	float fSlow49 = (float)dsp->fVslider49;
	float fSlow50 = (float)dsp->fVslider50;
	int iSlow51 = (int)min(524288.0f, max(0.0f, (dsp->fConst0 * (float)dsp->fVslider51)));
	float fSlow52 = (float)dsp->fVslider52;
	float fSlow53 = (float)dsp->fVslider53;
	float fSlow54 = (float)dsp->fVslider54;
	float fSlow55 = (float)dsp->fVslider55;
	float fSlow56 = (float)dsp->fVslider56;
	float fSlow57 = (float)dsp->fVslider57;
	float fSlow58 = (float)dsp->fVslider58;
	float fSlow59 = (float)dsp->fVslider59;
	float fSlow60 = (float)dsp->fVslider60;
	int iSlow61 = (int)min(524288.0f, max(0.0f, (dsp->fConst0 * (float)dsp->fVslider61)));
	float fSlow62 = (float)dsp->fVslider62;
	float fSlow63 = (float)dsp->fVslider63;
	float fSlow64 = (float)dsp->fVslider64;
	float fSlow65 = (float)dsp->fVslider65;
	float fSlow66 = (float)dsp->fVslider66;
	float fSlow67 = (float)dsp->fVslider67;
	float fSlow68 = (float)dsp->fVslider68;
	float fSlow69 = (float)dsp->fVslider69;
	float fSlow70 = (float)dsp->fVslider70;
	float fSlow71 = (float)dsp->fVslider71;
	float fSlow72 = (float)dsp->fVslider72;
	float fSlow73 = (float)dsp->fVslider73;
	float fSlow74 = (float)dsp->fVslider74;
	float fSlow75 = (float)dsp->fVslider75;
	float fSlow76 = (float)dsp->fVslider76;
	float fSlow77 = (float)dsp->fVslider77;
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = (float)input0[i];
			float fTemp1 = (float)input1[i];
			dsp->fVec0[(dsp->IOTA & 1048575)] = (fSlow2 * ((((((((fSlow3 * dsp->fRec0[1]) + (fSlow4 * dsp->fRec1[1])) + (fSlow5 * dsp->fRec2[1])) + (fSlow6 * dsp->fRec3[1])) + (fSlow7 * dsp->fRec4[1])) + (fSlow8 * dsp->fRec5[1])) + (fSlow9 * fTemp0)) + (fSlow10 * fTemp1)));
			dsp->fRec0[0] = dsp->fVec0[((dsp->IOTA - iSlow11) & 1048575)];
			dsp->fVec1[(dsp->IOTA & 1048575)] = (fSlow12 * ((((((((fSlow13 * dsp->fRec0[1]) + (fSlow14 * dsp->fRec1[1])) + (fSlow15 * dsp->fRec2[1])) + (fSlow16 * dsp->fRec3[1])) + (fSlow17 * dsp->fRec4[1])) + (fSlow18 * dsp->fRec5[1])) + (fSlow19 * fTemp0)) + (fSlow20 * fTemp1)));
			dsp->fRec1[0] = dsp->fVec1[((dsp->IOTA - iSlow21) & 1048575)];
			dsp->fVec2[(dsp->IOTA & 1048575)] = (fSlow22 * ((((((((fSlow23 * dsp->fRec0[1]) + (fSlow24 * dsp->fRec1[1])) + (fSlow25 * dsp->fRec2[1])) + (fSlow26 * dsp->fRec3[1])) + (fSlow27 * dsp->fRec4[1])) + (fSlow28 * dsp->fRec5[1])) + (fSlow29 * fTemp0)) + (fSlow30 * fTemp1)));
			dsp->fRec2[0] = dsp->fVec2[((dsp->IOTA - iSlow31) & 1048575)];
			dsp->fVec3[(dsp->IOTA & 1048575)] = (fSlow32 * ((((((((fSlow33 * dsp->fRec0[1]) + (fSlow34 * dsp->fRec1[1])) + (fSlow35 * dsp->fRec2[1])) + (fSlow36 * dsp->fRec3[1])) + (fSlow37 * dsp->fRec4[1])) + (fSlow38 * dsp->fRec5[1])) + (fSlow39 * fTemp0)) + (fSlow40 * fTemp1)));
			dsp->fRec3[0] = dsp->fVec3[((dsp->IOTA - iSlow41) & 1048575)];
			dsp->fVec4[(dsp->IOTA & 1048575)] = (fSlow42 * ((((((((fSlow43 * dsp->fRec0[1]) + (fSlow44 * dsp->fRec1[1])) + (fSlow45 * dsp->fRec2[1])) + (fSlow46 * dsp->fRec3[1])) + (fSlow47 * dsp->fRec4[1])) + (fSlow48 * dsp->fRec5[1])) + (fSlow49 * fTemp0)) + (fSlow50 * fTemp1)));
			dsp->fRec4[0] = dsp->fVec4[((dsp->IOTA - iSlow51) & 1048575)];
			dsp->fVec5[(dsp->IOTA & 1048575)] = (fSlow52 * ((((((((fSlow53 * dsp->fRec0[1]) + (fSlow54 * dsp->fRec1[1])) + (fSlow55 * dsp->fRec2[1])) + (fSlow56 * dsp->fRec3[1])) + (fSlow57 * dsp->fRec4[1])) + (fSlow58 * dsp->fRec5[1])) + (fSlow59 * fTemp0)) + (fSlow60 * fTemp1)));
			dsp->fRec5[0] = dsp->fVec5[((dsp->IOTA - iSlow61) & 1048575)];
			output0[i] = (FAUSTFLOAT)(fSlow0 * ((((((((fSlow1 * dsp->fRec0[0]) + (fSlow62 * dsp->fRec1[0])) + (fSlow63 * dsp->fRec2[0])) + (fSlow64 * dsp->fRec3[0])) + (fSlow65 * dsp->fRec4[0])) + (fSlow66 * dsp->fRec5[0])) + (fSlow67 * fTemp0)) + (fSlow68 * fTemp1)));
			output1[i] = (FAUSTFLOAT)(fSlow69 * ((((((((fSlow70 * dsp->fRec0[0]) + (fSlow71 * dsp->fRec1[0])) + (fSlow72 * dsp->fRec2[0])) + (fSlow73 * dsp->fRec3[0])) + (fSlow74 * dsp->fRec4[0])) + (fSlow75 * dsp->fRec5[0])) + (fSlow76 * fTemp0)) + (fSlow77 * fTemp1)));
			dsp->IOTA = (dsp->IOTA + 1);
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec3[1] = dsp->fRec3[0];
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fRec5[1] = dsp->fRec5[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
