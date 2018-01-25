/* ------------------------------------------------------------
author: "Vincent Rateau, GRAME"
license: "GPL v3"
name: "midiTester"
version: "1.0"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: cpp, -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__


// algorithm is required for min and max
#include <algorithm>
#include "gui/UI.h"

using namespace std;

// the struct below are not defined in UI.h
struct dsp {
};

struct Meta {
	void declare(const char*, const char*) {}
};
#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <cmath>


#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif
#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class mydsp : public dsp {
	
 private:
	
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHbargraph0;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fHbargraph1;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHbargraph2;
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT fCheckbox2;
	FAUSTFLOAT fCheckbox3;
	FAUSTFLOAT fHbargraph3;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHbargraph4;
	FAUSTFLOAT fCheckbox4;
	FAUSTFLOAT fHbargraph5;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT fHbargraph6;
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT fHbargraph7;
	FAUSTFLOAT fCheckbox5;
	FAUSTFLOAT fHbargraph8;
	FAUSTFLOAT fCheckbox6;
	FAUSTFLOAT fHbargraph9;
	FAUSTFLOAT fHslider5;
	FAUSTFLOAT fHbargraph10;
	FAUSTFLOAT fCheckbox7;
	FAUSTFLOAT fHbargraph11;
	FAUSTFLOAT fHslider6;
	FAUSTFLOAT fHbargraph12;
	FAUSTFLOAT fCheckbox8;
	FAUSTFLOAT fHbargraph13;
	int iConst0;
	int fSamplingFreq;
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("author", "Vincent Rateau, GRAME");
		m->declare("license", "GPL v3");
		m->declare("name", "midiTester");
		m->declare("reference", "www.sonejo.net");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() {
		return 1;
		
	}
	virtual int getNumOutputs() {
		return 1;
		
	}
	virtual int getInputRate(int channel) {
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
	virtual int getOutputRate(int channel) {
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
	
	static void classInit(int samplingFreq) {
		
	}
	
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		iConst0 = 0;
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(60.0f);
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fHslider1 = FAUSTFLOAT(60.0f);
		fCheckbox1 = FAUSTFLOAT(0.0f);
		fCheckbox2 = FAUSTFLOAT(0.0f);
		fCheckbox3 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(60.0f);
		fCheckbox4 = FAUSTFLOAT(0.0f);
		fHslider3 = FAUSTFLOAT(60.0f);
		fHslider4 = FAUSTFLOAT(60.0f);
		fCheckbox5 = FAUSTFLOAT(0.0f);
		fCheckbox6 = FAUSTFLOAT(0.0f);
		fHslider5 = FAUSTFLOAT(60.0f);
		fCheckbox7 = FAUSTFLOAT(0.0f);
		fHslider6 = FAUSTFLOAT(0.0f);
		fCheckbox8 = FAUSTFLOAT(0.0f);
		
	}
	
	virtual void instanceClear() {
		
	}
	
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void instanceInit(int samplingFreq) {
		instanceConstants(samplingFreq);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual mydsp* clone() {
		return new mydsp();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;
		
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("FAUST MIDI TESTER");
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->openVerticalBox("CTRL IN/OUT");
		ui_interface->declare(&fCheckbox5, "midi", "ctrl 100");
		ui_interface->addCheckButton("Ctrl Bool IN (Ctrl 100)", &fCheckbox5);
		ui_interface->declare(&fHbargraph8, "midi", "ctrl 101");
		ui_interface->addHorizontalBargraph("Ctrl Bool OUT (Ctrl 101)", &fHbargraph8, 0.0f, 1.0f);
		ui_interface->declare(&fHslider4, "midi", "ctrl 50");
		ui_interface->addHorizontalSlider("Ctrl Value IN (Ctrl 50)", &fHslider4, 60.0f, 0.0f, 127.0f, 1.0f);
		ui_interface->declare(&fHbargraph7, "midi", "ctrl 51");
		ui_interface->addHorizontalBargraph("Ctrl Value OUT (Ctrl 51)", &fHbargraph7, 0.0f, 127.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("MIDI SYNC (IN)");
		ui_interface->declare(&fCheckbox1, "midi", "start");
		ui_interface->declare(&fCheckbox1, "midi", "stop");
		ui_interface->addCheckButton("MIDI START/STOP", &fCheckbox1);
		ui_interface->declare(&fCheckbox2, "midi", "clock");
		ui_interface->addCheckButton("MIDI clock signal", &fCheckbox2);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("NOTE OFF IN/OUT");
		ui_interface->declare(&fCheckbox3, "midi", "keyoff 100");
		ui_interface->addCheckButton("NoteOff Bool IN (Note 100)", &fCheckbox3);
		ui_interface->declare(&fHbargraph3, "midi", "keyoff 101");
		ui_interface->addHorizontalBargraph("NoteOff Bool OUT (Note 101)", &fHbargraph3, 0.0f, 1.0f);
		ui_interface->declare(&fHslider2, "midi", "keyoff 50");
		ui_interface->addHorizontalSlider("NoteOff Value IN (Note 50)", &fHslider2, 60.0f, 0.0f, 127.0f, 1.0f);
		ui_interface->declare(&fHbargraph4, "midi", "keyoff 51");
		ui_interface->addHorizontalBargraph("NoteOff Value OUT (Note 51)", &fHbargraph4, 0.0f, 127.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("NOTE ON IN/OUT");
		ui_interface->declare(&fCheckbox4, "midi", "keyon 100");
		ui_interface->addCheckButton("NoteOn Bool IN (Note 100)", &fCheckbox4);
		ui_interface->declare(&fHbargraph5, "midi", "keyon 101");
		ui_interface->addHorizontalBargraph("NoteOn Bool OUT (Note 101)", &fHbargraph5, 0.0f, 1.0f);
		ui_interface->declare(&fHslider3, "midi", "keyon 50");
		ui_interface->addHorizontalSlider("NoteOn Value IN (Note 50)", &fHslider3, 60.0f, 0.0f, 127.0f, 1.0f);
		ui_interface->declare(&fHbargraph6, "midi", "keyon 51");
		ui_interface->addHorizontalBargraph("NoteOn Value OUT (Note 51)", &fHbargraph6, 0.0f, 127.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->openVerticalBox("CHANNEL AFTERTOUCH (CHAT) IN/OUT");
		ui_interface->declare(&fCheckbox7, "midi", "chanpress 100");
		ui_interface->addCheckButton("Note CHAT Bool IN (Note 100)", &fCheckbox7);
		ui_interface->declare(&fHbargraph11, "midi", "chanpress 101");
		ui_interface->addHorizontalBargraph("Note CHAT Bool OUT (Note 101)", &fHbargraph11, 0.0f, 1.0f);
		ui_interface->declare(&fHslider5, "midi", "chanpress 50");
		ui_interface->addHorizontalSlider("Note CHAT Value IN (Note 50)", &fHslider5, 60.0f, 0.0f, 127.0f, 1.0f);
		ui_interface->declare(&fHbargraph10, "midi", "chanpress 51");
		ui_interface->addHorizontalBargraph("Note CHAT Value OUT (Note 51)", &fHbargraph10, 0.0f, 127.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("KEY AFTERTOUCH (KAT) IN/OUT");
		ui_interface->declare(&fCheckbox0, "midi", "keypress 100");
		ui_interface->addCheckButton("Note KAT Bool IN (Note 100)", &fCheckbox0);
		ui_interface->declare(&fHbargraph1, "midi", "keypress 101");
		ui_interface->addHorizontalBargraph("Note KAT Bool OUT (Note 101)", &fHbargraph1, 0.0f, 1.0f);
		ui_interface->declare(&fHslider1, "midi", "keypress 50");
		ui_interface->addHorizontalSlider("Note KAT Value IN (Note 50)", &fHslider1, 60.0f, 0.0f, 127.0f, 1.0f);
		ui_interface->declare(&fHbargraph2, "midi", "keypress 51");
		ui_interface->addHorizontalBargraph("Note KAT Value OUT (Note 51)", &fHbargraph2, 0.0f, 127.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("PITCHWHEEL IN/OUT");
		ui_interface->declare(&fCheckbox8, "midi", "pitchwheel");
		ui_interface->addCheckButton("Pitchwheel Bool IN", &fCheckbox8);
		ui_interface->declare(&fHbargraph13, "midi", "pitchwheel");
		ui_interface->addHorizontalBargraph("Pitchwheel Bool OUT", &fHbargraph13, 0.0f, 1.0f);
		ui_interface->declare(&fHslider6, "midi", "pitchwheel");
		ui_interface->addHorizontalSlider("Pitchwheel Value IN", &fHslider6, 0.0f, -8192.0f, 8191.0f, 1.0f);
		ui_interface->declare(&fHbargraph12, "midi", "pitchwheel");
		ui_interface->addHorizontalBargraph("Pitchwheel Value OUT", &fHbargraph12, -8192.0f, 8191.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("PROGRAM CHANGE (PC) IN/OUT");
		ui_interface->declare(&fCheckbox6, "midi", "pgm 100");
		ui_interface->addCheckButton("ProgramChange Bool IN (PC 100)", &fCheckbox6);
		ui_interface->declare(&fHbargraph9, "midi", "pgm 101");
		ui_interface->addHorizontalBargraph("ProgramChange Bool OUT (PC 101)", &fHbargraph9, 0.0f, 1.0f);
		ui_interface->declare(&fHslider0, "midi", "pgm 50");
		ui_interface->addHorizontalSlider("ProgramChange Value IN (PC 50)", &fHslider0, 60.0f, 0.0f, 127.0f, 1.0f);
		ui_interface->declare(&fHbargraph0, "midi", "pgm 51");
		ui_interface->addHorizontalBargraph("ProgramChange Value OUT (PC 51)", &fHbargraph0, 0.0f, 127.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		fHbargraph0 = FAUSTFLOAT(float(fHslider0));
		fHbargraph1 = FAUSTFLOAT(float(fCheckbox0));
		fHbargraph2 = FAUSTFLOAT(float(fHslider1));
		fHbargraph3 = FAUSTFLOAT(float(fCheckbox3));
		fHbargraph4 = FAUSTFLOAT(float(fHslider2));
		fHbargraph5 = FAUSTFLOAT(float(fCheckbox4));
		fHbargraph6 = FAUSTFLOAT(float(fHslider3));
		fHbargraph7 = FAUSTFLOAT(float(fHslider4));
		fHbargraph8 = FAUSTFLOAT(float(fCheckbox5));
		fHbargraph9 = FAUSTFLOAT(float(fCheckbox6));
		fHbargraph10 = FAUSTFLOAT(float(fHslider5));
		fHbargraph11 = FAUSTFLOAT(float(fCheckbox7));
		fHbargraph12 = FAUSTFLOAT(float(fHslider6));
		fHbargraph13 = FAUSTFLOAT(float(fCheckbox8));
		for (int i = 0; (i < count); i = (i + 1)) {
			output0[i] = FAUSTFLOAT(iConst0);
			
		}
		
	}

	
};

#endif
