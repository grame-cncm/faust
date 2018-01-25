/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2006"
license: "BSD"
name: "mixer"
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
	FAUSTFLOAT fVslider0;
	float fRec1[2];
	FAUSTFLOAT fEntry0;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fVslider1;
	float fRec3[2];
	float fRec2[2];
	FAUSTFLOAT fVbargraph0;
	FAUSTFLOAT fEntry1;
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT fVslider2;
	float fRec5[2];
	float fRec4[2];
	FAUSTFLOAT fVbargraph1;
	FAUSTFLOAT fEntry2;
	FAUSTFLOAT fCheckbox2;
	FAUSTFLOAT fVslider3;
	float fRec7[2];
	float fRec6[2];
	FAUSTFLOAT fVbargraph2;
	FAUSTFLOAT fEntry3;
	FAUSTFLOAT fCheckbox3;
	FAUSTFLOAT fVslider4;
	float fRec9[2];
	float fRec8[2];
	FAUSTFLOAT fVbargraph3;
	FAUSTFLOAT fEntry4;
	FAUSTFLOAT fCheckbox4;
	FAUSTFLOAT fVslider5;
	float fRec11[2];
	float fRec10[2];
	FAUSTFLOAT fVbargraph4;
	FAUSTFLOAT fEntry5;
	FAUSTFLOAT fCheckbox5;
	FAUSTFLOAT fVslider6;
	float fRec13[2];
	float fRec12[2];
	FAUSTFLOAT fVbargraph5;
	FAUSTFLOAT fEntry6;
	FAUSTFLOAT fCheckbox6;
	FAUSTFLOAT fVslider7;
	float fRec15[2];
	float fRec14[2];
	FAUSTFLOAT fVbargraph6;
	FAUSTFLOAT fEntry7;
	FAUSTFLOAT fCheckbox7;
	FAUSTFLOAT fVslider8;
	float fRec17[2];
	float fRec16[2];
	FAUSTFLOAT fVbargraph7;
	float fRec0[2];
	FAUSTFLOAT fVbargraph8;
	float fRec18[2];
	FAUSTFLOAT fVbargraph9;
	
} mydsp;

mydsp* newmydsp() { 
	mydsp* dsp = (mydsp*)malloc(sizeof(mydsp));
	return dsp;
}

void deletemydsp(mydsp* dsp) { 
	free(dsp);
}

void metadatamydsp(MetaGlue* m) { 
	m->declare(m->metaInterface, "../analysis/vumeter.dsp/author", "Grame");
	m->declare(m->metaInterface, "../analysis/vumeter.dsp/copyright", "(c)GRAME 2006");
	m->declare(m->metaInterface, "../analysis/vumeter.dsp/license", "BSD");
	m->declare(m->metaInterface, "../analysis/vumeter.dsp/name", "vumeter");
	m->declare(m->metaInterface, "../analysis/vumeter.dsp/version", "1.0");
	m->declare(m->metaInterface, "../dynamic/volume.dsp/author", "Grame");
	m->declare(m->metaInterface, "../dynamic/volume.dsp/copyright", "(c)GRAME 2006");
	m->declare(m->metaInterface, "../dynamic/volume.dsp/license", "BSD");
	m->declare(m->metaInterface, "../dynamic/volume.dsp/name", "volume");
	m->declare(m->metaInterface, "../dynamic/volume.dsp/version", "1.0");
	m->declare(m->metaInterface, "../spat/panpot.dsp/author", "Grame");
	m->declare(m->metaInterface, "../spat/panpot.dsp/copyright", "(c)GRAME 2006");
	m->declare(m->metaInterface, "../spat/panpot.dsp/license", "BSD");
	m->declare(m->metaInterface, "../spat/panpot.dsp/name", "panpot");
	m->declare(m->metaInterface, "../spat/panpot.dsp/version", "1.0");
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
	m->declare(m->metaInterface, "name", "mixer");
	m->declare(m->metaInterface, "signals.lib/name", "Faust Signal Routing Library");
	m->declare(m->metaInterface, "signals.lib/version", "0.0");
	m->declare(m->metaInterface, "version", "1.0");
}

int getSampleRatemydsp(mydsp* dsp) { return dsp->fSamplingFreq; }

int getNumInputsmydsp(mydsp* dsp) {
	return 8;
	
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
	dsp->fVslider0 = (FAUSTFLOAT)0.0f;
	dsp->fEntry0 = (FAUSTFLOAT)0.0f;
	dsp->fCheckbox0 = (FAUSTFLOAT)0.0f;
	dsp->fVslider1 = (FAUSTFLOAT)0.0f;
	dsp->fEntry1 = (FAUSTFLOAT)0.0f;
	dsp->fCheckbox1 = (FAUSTFLOAT)0.0f;
	dsp->fVslider2 = (FAUSTFLOAT)0.0f;
	dsp->fEntry2 = (FAUSTFLOAT)0.0f;
	dsp->fCheckbox2 = (FAUSTFLOAT)0.0f;
	dsp->fVslider3 = (FAUSTFLOAT)0.0f;
	dsp->fEntry3 = (FAUSTFLOAT)0.0f;
	dsp->fCheckbox3 = (FAUSTFLOAT)0.0f;
	dsp->fVslider4 = (FAUSTFLOAT)0.0f;
	dsp->fEntry4 = (FAUSTFLOAT)0.0f;
	dsp->fCheckbox4 = (FAUSTFLOAT)0.0f;
	dsp->fVslider5 = (FAUSTFLOAT)0.0f;
	dsp->fEntry5 = (FAUSTFLOAT)0.0f;
	dsp->fCheckbox5 = (FAUSTFLOAT)0.0f;
	dsp->fVslider6 = (FAUSTFLOAT)0.0f;
	dsp->fEntry6 = (FAUSTFLOAT)0.0f;
	dsp->fCheckbox6 = (FAUSTFLOAT)0.0f;
	dsp->fVslider7 = (FAUSTFLOAT)0.0f;
	dsp->fEntry7 = (FAUSTFLOAT)0.0f;
	dsp->fCheckbox7 = (FAUSTFLOAT)0.0f;
	dsp->fVslider8 = (FAUSTFLOAT)0.0f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			dsp->fRec1[l0] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			dsp->fRec3[l1] = 0.0f;
			
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
			dsp->fRec5[l3] = 0.0f;
			
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
			dsp->fRec7[l5] = 0.0f;
			
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
			dsp->fRec9[l7] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			dsp->fRec8[l8] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			dsp->fRec11[l9] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			dsp->fRec10[l10] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			dsp->fRec13[l11] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			dsp->fRec12[l12] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l13;
		for (l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			dsp->fRec15[l13] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l14;
		for (l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			dsp->fRec14[l14] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l15;
		for (l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			dsp->fRec17[l15] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l16;
		for (l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			dsp->fRec16[l16] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l17;
		for (l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			dsp->fRec0[l17] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l18;
		for (l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			dsp->fRec18[l18] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = (1.0f / min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq)));
	
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
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "mixer");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "Ch 0");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry0, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry0, "style", "knob");
	ui_interface->addNumEntry(ui_interface->uiInterface, "pan", &dsp->fEntry0, 0.0f, -90.0f, 90.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, 0, "2", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider1, "1", "");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "0x00", &dsp->fVslider1, 0.0f, -70.0f, 4.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph0, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph0, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fbcf57e32b0", &dsp->fVbargraph0, -70.0f, 5.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->addCheckButton(ui_interface->uiInterface, "mute", &dsp->fCheckbox0);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "Ch 1");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry1, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry1, "style", "knob");
	ui_interface->addNumEntry(ui_interface->uiInterface, "pan", &dsp->fEntry1, 0.0f, -90.0f, 90.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, 0, "2", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider2, "1", "");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "0x00", &dsp->fVslider2, 0.0f, -70.0f, 4.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph1, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph1, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fbcf57ed3b0", &dsp->fVbargraph1, -70.0f, 5.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->addCheckButton(ui_interface->uiInterface, "mute", &dsp->fCheckbox1);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "Ch 2");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry2, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry2, "style", "knob");
	ui_interface->addNumEntry(ui_interface->uiInterface, "pan", &dsp->fEntry2, 0.0f, -90.0f, 90.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, 0, "2", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider3, "1", "");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "0x00", &dsp->fVslider3, 0.0f, -70.0f, 4.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph2, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph2, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fbcf57f78f0", &dsp->fVbargraph2, -70.0f, 5.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->addCheckButton(ui_interface->uiInterface, "mute", &dsp->fCheckbox2);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "Ch 3");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry3, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry3, "style", "knob");
	ui_interface->addNumEntry(ui_interface->uiInterface, "pan", &dsp->fEntry3, 0.0f, -90.0f, 90.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, 0, "2", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider4, "1", "");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "0x00", &dsp->fVslider4, 0.0f, -70.0f, 4.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph3, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph3, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fbcf6806070", &dsp->fVbargraph3, -70.0f, 5.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->addCheckButton(ui_interface->uiInterface, "mute", &dsp->fCheckbox3);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "Ch 4");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry4, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry4, "style", "knob");
	ui_interface->addNumEntry(ui_interface->uiInterface, "pan", &dsp->fEntry4, 0.0f, -90.0f, 90.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, 0, "2", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider5, "1", "");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "0x00", &dsp->fVslider5, 0.0f, -70.0f, 4.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph4, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph4, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fbcf6810b30", &dsp->fVbargraph4, -70.0f, 5.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->addCheckButton(ui_interface->uiInterface, "mute", &dsp->fCheckbox4);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "Ch 5");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry5, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry5, "style", "knob");
	ui_interface->addNumEntry(ui_interface->uiInterface, "pan", &dsp->fEntry5, 0.0f, -90.0f, 90.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, 0, "2", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider6, "1", "");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "0x00", &dsp->fVslider6, 0.0f, -70.0f, 4.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph5, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph5, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fbcf681b8b0", &dsp->fVbargraph5, -70.0f, 5.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->addCheckButton(ui_interface->uiInterface, "mute", &dsp->fCheckbox5);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "Ch 6");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry6, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry6, "style", "knob");
	ui_interface->addNumEntry(ui_interface->uiInterface, "pan", &dsp->fEntry6, 0.0f, -90.0f, 90.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, 0, "2", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider7, "1", "");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "0x00", &dsp->fVslider7, 0.0f, -70.0f, 4.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph6, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph6, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fbcf68268f0", &dsp->fVbargraph6, -70.0f, 5.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->addCheckButton(ui_interface->uiInterface, "mute", &dsp->fCheckbox6);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "Ch 7");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry7, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry7, "style", "knob");
	ui_interface->addNumEntry(ui_interface->uiInterface, "pan", &dsp->fEntry7, 0.0f, -90.0f, 90.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, 0, "2", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider8, "1", "");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "0x00", &dsp->fVslider8, 0.0f, -70.0f, 4.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph7, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph7, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fbcf6831bf0", &dsp->fVbargraph7, -70.0f, 5.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->addCheckButton(ui_interface->uiInterface, "mute", &dsp->fCheckbox7);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "stereo out");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "L");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph8, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph8, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fbcf6835ae0", &dsp->fVbargraph8, -70.0f, 5.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "R");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph9, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph9, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fbcf683f080", &dsp->fVbargraph9, -70.0f, 5.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider0, "1", "");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "0x00", &dsp->fVslider0, 0.0f, -70.0f, 4.0f, 0.100000001f);
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
	float fSlow0 = (0.00100000005f * powf(10.0f, (0.0500000007f * (float)dsp->fVslider0)));
	float fSlow1 = (0.00555555569f * ((float)dsp->fEntry0 + -90.0f));
	float fSlow2 = sqrtf((0.0f - fSlow1));
	float fSlow3 = (1.0f - (float)dsp->fCheckbox0);
	float fSlow4 = (0.00100000005f * powf(10.0f, (0.0500000007f * (float)dsp->fVslider1)));
	float fSlow5 = (0.00555555569f * ((float)dsp->fEntry1 + -90.0f));
	float fSlow6 = sqrtf((0.0f - fSlow5));
	float fSlow7 = (1.0f - (float)dsp->fCheckbox1);
	float fSlow8 = (0.00100000005f * powf(10.0f, (0.0500000007f * (float)dsp->fVslider2)));
	float fSlow9 = (0.00555555569f * ((float)dsp->fEntry2 + -90.0f));
	float fSlow10 = sqrtf((0.0f - fSlow9));
	float fSlow11 = (1.0f - (float)dsp->fCheckbox2);
	float fSlow12 = (0.00100000005f * powf(10.0f, (0.0500000007f * (float)dsp->fVslider3)));
	float fSlow13 = (0.00555555569f * ((float)dsp->fEntry3 + -90.0f));
	float fSlow14 = sqrtf((0.0f - fSlow13));
	float fSlow15 = (1.0f - (float)dsp->fCheckbox3);
	float fSlow16 = (0.00100000005f * powf(10.0f, (0.0500000007f * (float)dsp->fVslider4)));
	float fSlow17 = (0.00555555569f * ((float)dsp->fEntry4 + -90.0f));
	float fSlow18 = sqrtf((0.0f - fSlow17));
	float fSlow19 = (1.0f - (float)dsp->fCheckbox4);
	float fSlow20 = (0.00100000005f * powf(10.0f, (0.0500000007f * (float)dsp->fVslider5)));
	float fSlow21 = (0.00555555569f * ((float)dsp->fEntry5 + -90.0f));
	float fSlow22 = sqrtf((0.0f - fSlow21));
	float fSlow23 = (1.0f - (float)dsp->fCheckbox5);
	float fSlow24 = (0.00100000005f * powf(10.0f, (0.0500000007f * (float)dsp->fVslider6)));
	float fSlow25 = (0.00555555569f * ((float)dsp->fEntry6 + -90.0f));
	float fSlow26 = sqrtf((0.0f - fSlow25));
	float fSlow27 = (1.0f - (float)dsp->fCheckbox6);
	float fSlow28 = (0.00100000005f * powf(10.0f, (0.0500000007f * (float)dsp->fVslider7)));
	float fSlow29 = (0.00555555569f * ((float)dsp->fEntry7 + -90.0f));
	float fSlow30 = sqrtf((0.0f - fSlow29));
	float fSlow31 = (1.0f - (float)dsp->fCheckbox7);
	float fSlow32 = (0.00100000005f * powf(10.0f, (0.0500000007f * (float)dsp->fVslider8)));
	float fSlow33 = sqrtf((fSlow1 + 1.0f));
	float fSlow34 = sqrtf((fSlow5 + 1.0f));
	float fSlow35 = sqrtf((fSlow9 + 1.0f));
	float fSlow36 = sqrtf((fSlow13 + 1.0f));
	float fSlow37 = sqrtf((fSlow17 + 1.0f));
	float fSlow38 = sqrtf((fSlow21 + 1.0f));
	float fSlow39 = sqrtf((fSlow25 + 1.0f));
	float fSlow40 = sqrtf((fSlow29 + 1.0f));
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->fRec1[0] = (fSlow0 + (0.999000013f * dsp->fRec1[1]));
			dsp->fRec3[0] = (fSlow4 + (0.999000013f * dsp->fRec3[1]));
			float fTemp0 = (fSlow3 * ((float)input0[i] * dsp->fRec3[0]));
			dsp->fRec2[0] = max((dsp->fRec2[1] - dsp->fConst0), fabsf(fTemp0));
			dsp->fVbargraph0 = (FAUSTFLOAT)(20.0f * log10f(max(0.000316227757f, dsp->fRec2[0])));
			dsp->fRec5[0] = (fSlow8 + (0.999000013f * dsp->fRec5[1]));
			float fTemp1 = (fSlow7 * ((float)input1[i] * dsp->fRec5[0]));
			dsp->fRec4[0] = max((dsp->fRec4[1] - dsp->fConst0), fabsf(fTemp1));
			dsp->fVbargraph1 = (FAUSTFLOAT)(20.0f * log10f(max(0.000316227757f, dsp->fRec4[0])));
			dsp->fRec7[0] = (fSlow12 + (0.999000013f * dsp->fRec7[1]));
			float fTemp2 = (fSlow11 * ((float)input2[i] * dsp->fRec7[0]));
			dsp->fRec6[0] = max((dsp->fRec6[1] - dsp->fConst0), fabsf(fTemp2));
			dsp->fVbargraph2 = (FAUSTFLOAT)(20.0f * log10f(max(0.000316227757f, dsp->fRec6[0])));
			dsp->fRec9[0] = (fSlow16 + (0.999000013f * dsp->fRec9[1]));
			float fTemp3 = (fSlow15 * ((float)input3[i] * dsp->fRec9[0]));
			dsp->fRec8[0] = max((dsp->fRec8[1] - dsp->fConst0), fabsf(fTemp3));
			dsp->fVbargraph3 = (FAUSTFLOAT)(20.0f * log10f(max(0.000316227757f, dsp->fRec8[0])));
			dsp->fRec11[0] = (fSlow20 + (0.999000013f * dsp->fRec11[1]));
			float fTemp4 = (fSlow19 * ((float)input4[i] * dsp->fRec11[0]));
			dsp->fRec10[0] = max((dsp->fRec10[1] - dsp->fConst0), fabsf(fTemp4));
			dsp->fVbargraph4 = (FAUSTFLOAT)(20.0f * log10f(max(0.000316227757f, dsp->fRec10[0])));
			dsp->fRec13[0] = (fSlow24 + (0.999000013f * dsp->fRec13[1]));
			float fTemp5 = (fSlow23 * ((float)input5[i] * dsp->fRec13[0]));
			dsp->fRec12[0] = max((dsp->fRec12[1] - dsp->fConst0), fabsf(fTemp5));
			dsp->fVbargraph5 = (FAUSTFLOAT)(20.0f * log10f(max(0.000316227757f, dsp->fRec12[0])));
			dsp->fRec15[0] = (fSlow28 + (0.999000013f * dsp->fRec15[1]));
			float fTemp6 = (fSlow27 * ((float)input6[i] * dsp->fRec15[0]));
			dsp->fRec14[0] = max((dsp->fRec14[1] - dsp->fConst0), fabsf(fTemp6));
			dsp->fVbargraph6 = (FAUSTFLOAT)(20.0f * log10f(max(0.000316227757f, dsp->fRec14[0])));
			dsp->fRec17[0] = (fSlow32 + (0.999000013f * dsp->fRec17[1]));
			float fTemp7 = (fSlow31 * ((float)input7[i] * dsp->fRec17[0]));
			dsp->fRec16[0] = max((dsp->fRec16[1] - dsp->fConst0), fabsf(fTemp7));
			dsp->fVbargraph7 = (FAUSTFLOAT)(20.0f * log10f(max(0.000316227757f, dsp->fRec16[0])));
			float fTemp8 = (dsp->fRec1[0] * ((((((((fSlow2 * fTemp0) + (fSlow6 * fTemp1)) + (fSlow10 * fTemp2)) + (fSlow14 * fTemp3)) + (fSlow18 * fTemp4)) + (fSlow22 * fTemp5)) + (fSlow26 * fTemp6)) + (fSlow30 * fTemp7)));
			dsp->fRec0[0] = max((dsp->fRec0[1] - dsp->fConst0), fabsf(fTemp8));
			dsp->fVbargraph8 = (FAUSTFLOAT)(20.0f * log10f(max(0.000316227757f, dsp->fRec0[0])));
			output0[i] = (FAUSTFLOAT)fTemp8;
			float fTemp9 = (dsp->fRec1[0] * ((((((((fSlow33 * fTemp0) + (fSlow34 * fTemp1)) + (fSlow35 * fTemp2)) + (fSlow36 * fTemp3)) + (fSlow37 * fTemp4)) + (fSlow38 * fTemp5)) + (fSlow39 * fTemp6)) + (fSlow40 * fTemp7)));
			dsp->fRec18[0] = max((dsp->fRec18[1] - dsp->fConst0), fabsf(fTemp9));
			dsp->fVbargraph9 = (FAUSTFLOAT)(20.0f * log10f(max(0.000316227757f, dsp->fRec18[0])));
			output1[i] = (FAUSTFLOAT)fTemp9;
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fRec3[1] = dsp->fRec3[0];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec5[1] = dsp->fRec5[0];
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fRec7[1] = dsp->fRec7[0];
			dsp->fRec6[1] = dsp->fRec6[0];
			dsp->fRec9[1] = dsp->fRec9[0];
			dsp->fRec8[1] = dsp->fRec8[0];
			dsp->fRec11[1] = dsp->fRec11[0];
			dsp->fRec10[1] = dsp->fRec10[0];
			dsp->fRec13[1] = dsp->fRec13[0];
			dsp->fRec12[1] = dsp->fRec12[0];
			dsp->fRec15[1] = dsp->fRec15[0];
			dsp->fRec14[1] = dsp->fRec14[0];
			dsp->fRec17[1] = dsp->fRec17[0];
			dsp->fRec16[1] = dsp->fRec16[0];
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec18[1] = dsp->fRec18[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
