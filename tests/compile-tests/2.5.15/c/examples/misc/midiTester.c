/* ------------------------------------------------------------
author: "Vincent Rateau, GRAME"
license: "GPL v3"
name: "midiTester"
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
	FAUSTFLOAT fHbargraph0;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHbargraph1;
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT fHbargraph2;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHbargraph3;
	FAUSTFLOAT fCheckbox2;
	FAUSTFLOAT fHbargraph4;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHbargraph5;
	FAUSTFLOAT fCheckbox3;
	FAUSTFLOAT fHbargraph6;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT fHbargraph7;
	FAUSTFLOAT fCheckbox4;
	FAUSTFLOAT fCheckbox5;
	FAUSTFLOAT fCheckbox6;
	FAUSTFLOAT fHbargraph8;
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT fHbargraph9;
	FAUSTFLOAT fCheckbox7;
	FAUSTFLOAT fHbargraph10;
	FAUSTFLOAT fHslider5;
	FAUSTFLOAT fHbargraph11;
	FAUSTFLOAT fHslider6;
	FAUSTFLOAT fHbargraph12;
	FAUSTFLOAT fCheckbox8;
	FAUSTFLOAT fHbargraph13;
	int iConst0;
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
	m->declare(m->metaInterface, "author", "Vincent Rateau, GRAME");
	m->declare(m->metaInterface, "license", "GPL v3");
	m->declare(m->metaInterface, "name", "midiTester");
	m->declare(m->metaInterface, "reference", "www.sonejo.net");
	m->declare(m->metaInterface, "version", "1.0");
}

int getSampleRatemydsp(mydsp* dsp) { return dsp->fSamplingFreq; }

int getNumInputsmydsp(mydsp* dsp) {
	return 1;
	
}
int getNumOutputsmydsp(mydsp* dsp) {
	return 1;
	
}
int getInputRatemydsp(mydsp* dsp, int channel) {
	int rate;
	switch (channel) {
		case 0: {
			rate = 0;
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
	dsp->fHslider0 = (FAUSTFLOAT)0.0f;
	dsp->fCheckbox1 = (FAUSTFLOAT)0.0f;
	dsp->fHslider1 = (FAUSTFLOAT)60.0f;
	dsp->fCheckbox2 = (FAUSTFLOAT)0.0f;
	dsp->fHslider2 = (FAUSTFLOAT)60.0f;
	dsp->fCheckbox3 = (FAUSTFLOAT)0.0f;
	dsp->fHslider3 = (FAUSTFLOAT)60.0f;
	dsp->fCheckbox4 = (FAUSTFLOAT)0.0f;
	dsp->fCheckbox5 = (FAUSTFLOAT)0.0f;
	dsp->fCheckbox6 = (FAUSTFLOAT)0.0f;
	dsp->fHslider4 = (FAUSTFLOAT)60.0f;
	dsp->fCheckbox7 = (FAUSTFLOAT)0.0f;
	dsp->fHslider5 = (FAUSTFLOAT)60.0f;
	dsp->fHslider6 = (FAUSTFLOAT)60.0f;
	dsp->fCheckbox8 = (FAUSTFLOAT)0.0f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->iConst0 = 0;
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "FAUST MIDI TESTER");
	ui_interface->declare(ui_interface->uiInterface, 0, "1", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "0x00");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "CTRL IN/OUT");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox8, "midi", "ctrl 100");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Ctrl Bool IN (Ctrl 100)", &dsp->fCheckbox8);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHbargraph13, "midi", "ctrl 101");
	ui_interface->addHorizontalBargraph(ui_interface->uiInterface, "Ctrl Bool OUT (Ctrl 101)", &dsp->fHbargraph13, 0.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider6, "midi", "ctrl 50");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Ctrl Value IN (Ctrl 50)", &dsp->fHslider6, 60.0f, 0.0f, 127.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHbargraph12, "midi", "ctrl 51");
	ui_interface->addHorizontalBargraph(ui_interface->uiInterface, "Ctrl Value OUT (Ctrl 51)", &dsp->fHbargraph12, 0.0f, 127.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "MIDI SYNC (IN)");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox4, "midi", "start");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox4, "midi", "stop");
	ui_interface->addCheckButton(ui_interface->uiInterface, "MIDI START/STOP", &dsp->fCheckbox4);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox5, "midi", "clock");
	ui_interface->addCheckButton(ui_interface->uiInterface, "MIDI clock signal", &dsp->fCheckbox5);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "NOTE OFF IN/OUT");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox6, "midi", "keyoff 100");
	ui_interface->addCheckButton(ui_interface->uiInterface, "NoteOff Bool IN (Note 100)", &dsp->fCheckbox6);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHbargraph8, "midi", "keyoff 101");
	ui_interface->addHorizontalBargraph(ui_interface->uiInterface, "NoteOff Bool OUT (Note 101)", &dsp->fHbargraph8, 0.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "midi", "keyoff 50");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "NoteOff Value IN (Note 50)", &dsp->fHslider4, 60.0f, 0.0f, 127.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHbargraph9, "midi", "keyoff 51");
	ui_interface->addHorizontalBargraph(ui_interface->uiInterface, "NoteOff Value OUT (Note 51)", &dsp->fHbargraph9, 0.0f, 127.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "NOTE ON IN/OUT");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox7, "midi", "keyon 100");
	ui_interface->addCheckButton(ui_interface->uiInterface, "NoteOn Bool IN (Note 100)", &dsp->fCheckbox7);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHbargraph10, "midi", "keyon 101");
	ui_interface->addHorizontalBargraph(ui_interface->uiInterface, "NoteOn Bool OUT (Note 101)", &dsp->fHbargraph10, 0.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "midi", "keyon 50");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "NoteOn Value IN (Note 50)", &dsp->fHslider5, 60.0f, 0.0f, 127.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHbargraph11, "midi", "keyon 51");
	ui_interface->addHorizontalBargraph(ui_interface->uiInterface, "NoteOn Value OUT (Note 51)", &dsp->fHbargraph11, 0.0f, 127.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "2", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "0x00");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "CHANNEL AFTERTOUCH (CHAT) IN/OUT");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox1, "midi", "chanpress 100");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Note CHAT Bool IN (Note 100)", &dsp->fCheckbox1);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHbargraph2, "midi", "chanpress 101");
	ui_interface->addHorizontalBargraph(ui_interface->uiInterface, "Note CHAT Bool OUT (Note 101)", &dsp->fHbargraph2, 0.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "midi", "chanpress 50");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Note CHAT Value IN (Note 50)", &dsp->fHslider1, 60.0f, 0.0f, 127.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHbargraph3, "midi", "chanpress 51");
	ui_interface->addHorizontalBargraph(ui_interface->uiInterface, "Note CHAT Value OUT (Note 51)", &dsp->fHbargraph3, 0.0f, 127.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "KEY AFTERTOUCH (KAT) IN/OUT");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox3, "midi", "keypress 100");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Note KAT Bool IN (Note 100)", &dsp->fCheckbox3);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHbargraph6, "midi", "keypress 101");
	ui_interface->addHorizontalBargraph(ui_interface->uiInterface, "Note KAT Bool OUT (Note 101)", &dsp->fHbargraph6, 0.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "midi", "keypress 50");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Note KAT Value IN (Note 50)", &dsp->fHslider3, 60.0f, 0.0f, 127.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHbargraph7, "midi", "keypress 51");
	ui_interface->addHorizontalBargraph(ui_interface->uiInterface, "Note KAT Value OUT (Note 51)", &dsp->fHbargraph7, 0.0f, 127.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "PITCHWHEEL IN/OUT");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox0, "midi", "pitchwheel");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Pitchwheel Bool IN", &dsp->fCheckbox0);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHbargraph0, "midi", "pitchwheel");
	ui_interface->addHorizontalBargraph(ui_interface->uiInterface, "Pitchwheel Bool OUT", &dsp->fHbargraph0, 0.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "midi", "pitchwheel");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Pitchwheel Value IN", &dsp->fHslider0, 0.0f, -8192.0f, 8191.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHbargraph1, "midi", "pitchwheel");
	ui_interface->addHorizontalBargraph(ui_interface->uiInterface, "Pitchwheel Value OUT", &dsp->fHbargraph1, -8192.0f, 8191.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->openVerticalBox(ui_interface->uiInterface, "PROGRAM CHANGE (PC) IN/OUT");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox2, "midi", "pgm 100");
	ui_interface->addCheckButton(ui_interface->uiInterface, "ProgramChange Bool IN (PC 100)", &dsp->fCheckbox2);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHbargraph4, "midi", "pgm 101");
	ui_interface->addHorizontalBargraph(ui_interface->uiInterface, "ProgramChange Bool OUT (PC 101)", &dsp->fHbargraph4, 0.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "midi", "pgm 50");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "ProgramChange Value IN (PC 50)", &dsp->fHslider2, 60.0f, 0.0f, 127.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHbargraph5, "midi", "pgm 51");
	ui_interface->addHorizontalBargraph(ui_interface->uiInterface, "ProgramChange Value OUT (PC 51)", &dsp->fHbargraph5, 0.0f, 127.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* input0 = inputs[0];
	FAUSTFLOAT* output0 = outputs[0];
	dsp->fHbargraph0 = (FAUSTFLOAT)(float)dsp->fCheckbox0;
	dsp->fHbargraph1 = (FAUSTFLOAT)(float)dsp->fHslider0;
	dsp->fHbargraph2 = (FAUSTFLOAT)(float)dsp->fCheckbox1;
	dsp->fHbargraph3 = (FAUSTFLOAT)(float)dsp->fHslider1;
	dsp->fHbargraph4 = (FAUSTFLOAT)(float)dsp->fCheckbox2;
	dsp->fHbargraph5 = (FAUSTFLOAT)(float)dsp->fHslider2;
	dsp->fHbargraph6 = (FAUSTFLOAT)(float)dsp->fCheckbox3;
	dsp->fHbargraph7 = (FAUSTFLOAT)(float)dsp->fHslider3;
	dsp->fHbargraph8 = (FAUSTFLOAT)(float)dsp->fCheckbox6;
	dsp->fHbargraph9 = (FAUSTFLOAT)(float)dsp->fHslider4;
	dsp->fHbargraph10 = (FAUSTFLOAT)(float)dsp->fCheckbox7;
	dsp->fHbargraph11 = (FAUSTFLOAT)(float)dsp->fHslider5;
	dsp->fHbargraph12 = (FAUSTFLOAT)(float)dsp->fHslider6;
	dsp->fHbargraph13 = (FAUSTFLOAT)(float)dsp->fCheckbox8;
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			output0[i] = (FAUSTFLOAT)dsp->iConst0;
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
