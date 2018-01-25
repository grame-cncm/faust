//----------------------------------------------------------
// author: "Vincent Rateau, GRAME"
// license: "GPL v3"
// name: "midiTester"
// version: "1.0"
//
// Code generated with Faust 2.5.15 (https://faust.grame.fr)
//----------------------------------------------------------

/* link with  */
#include <math.h>

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


#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

class mydsp : public dsp {
  private:
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT 	fbargraph0;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fbargraph1;
	FAUSTFLOAT 	fcheckbox1;
	FAUSTFLOAT 	fbargraph2;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fbargraph3;
	FAUSTFLOAT 	fcheckbox2;
	FAUSTFLOAT 	fbargraph4;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fbargraph5;
	FAUSTFLOAT 	fcheckbox3;
	FAUSTFLOAT 	fbargraph6;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT 	fbargraph7;
	FAUSTFLOAT 	fcheckbox4;
	FAUSTFLOAT 	fcheckbox5;
	FAUSTFLOAT 	fcheckbox6;
	FAUSTFLOAT 	fbargraph8;
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT 	fbargraph9;
	FAUSTFLOAT 	fcheckbox7;
	FAUSTFLOAT 	fbargraph10;
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT 	fbargraph11;
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT 	fbargraph12;
	FAUSTFLOAT 	fcheckbox8;
	FAUSTFLOAT 	fbargraph13;
	int 	iConst0;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("author", "Vincent Rateau, GRAME");
		m->declare("license", "GPL v3");
		m->declare("name", "midiTester");
		m->declare("reference", "www.sonejo.net");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() { return 1; }
	virtual int getNumOutputs() { return 1; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		iConst0 = 0;
	}
	virtual void instanceResetUserInterface() {
		fcheckbox0 = 0.0;
		fslider0 = 0.0f;
		fcheckbox1 = 0.0;
		fslider1 = 60.0f;
		fcheckbox2 = 0.0;
		fslider2 = 60.0f;
		fcheckbox3 = 0.0;
		fslider3 = 60.0f;
		fcheckbox4 = 0.0;
		fcheckbox5 = 0.0;
		fcheckbox6 = 0.0;
		fslider4 = 60.0f;
		fcheckbox7 = 0.0;
		fslider5 = 60.0f;
		fslider6 = 60.0f;
		fcheckbox8 = 0.0;
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
		ui_interface->declare(&fcheckbox8, "midi", "ctrl 100");
		ui_interface->addCheckButton("Ctrl Bool IN (Ctrl 100)", &fcheckbox8);
		ui_interface->declare(&fbargraph13, "midi", "ctrl 101");
		ui_interface->addHorizontalBargraph("Ctrl Bool OUT (Ctrl 101)", &fbargraph13, 0.0f, 1.0f);
		ui_interface->declare(&fslider6, "midi", "ctrl 50");
		ui_interface->addHorizontalSlider("Ctrl Value IN (Ctrl 50)", &fslider6, 60.0f, 0.0f, 127.0f, 1.0f);
		ui_interface->declare(&fbargraph12, "midi", "ctrl 51");
		ui_interface->addHorizontalBargraph("Ctrl Value OUT (Ctrl 51)", &fbargraph12, 0.0f, 127.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("MIDI SYNC (IN)");
		ui_interface->declare(&fcheckbox4, "midi", "start");
		ui_interface->declare(&fcheckbox4, "midi", "stop");
		ui_interface->addCheckButton("MIDI START/STOP", &fcheckbox4);
		ui_interface->declare(&fcheckbox5, "midi", "clock");
		ui_interface->addCheckButton("MIDI clock signal", &fcheckbox5);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("NOTE OFF IN/OUT");
		ui_interface->declare(&fcheckbox6, "midi", "keyoff 100");
		ui_interface->addCheckButton("NoteOff Bool IN (Note 100)", &fcheckbox6);
		ui_interface->declare(&fbargraph8, "midi", "keyoff 101");
		ui_interface->addHorizontalBargraph("NoteOff Bool OUT (Note 101)", &fbargraph8, 0.0f, 1.0f);
		ui_interface->declare(&fslider4, "midi", "keyoff 50");
		ui_interface->addHorizontalSlider("NoteOff Value IN (Note 50)", &fslider4, 60.0f, 0.0f, 127.0f, 1.0f);
		ui_interface->declare(&fbargraph9, "midi", "keyoff 51");
		ui_interface->addHorizontalBargraph("NoteOff Value OUT (Note 51)", &fbargraph9, 0.0f, 127.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("NOTE ON IN/OUT");
		ui_interface->declare(&fcheckbox7, "midi", "keyon 100");
		ui_interface->addCheckButton("NoteOn Bool IN (Note 100)", &fcheckbox7);
		ui_interface->declare(&fbargraph10, "midi", "keyon 101");
		ui_interface->addHorizontalBargraph("NoteOn Bool OUT (Note 101)", &fbargraph10, 0.0f, 1.0f);
		ui_interface->declare(&fslider5, "midi", "keyon 50");
		ui_interface->addHorizontalSlider("NoteOn Value IN (Note 50)", &fslider5, 60.0f, 0.0f, 127.0f, 1.0f);
		ui_interface->declare(&fbargraph11, "midi", "keyon 51");
		ui_interface->addHorizontalBargraph("NoteOn Value OUT (Note 51)", &fbargraph11, 0.0f, 127.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->openVerticalBox("CHANNEL AFTERTOUCH (CHAT) IN/OUT");
		ui_interface->declare(&fcheckbox1, "midi", "chanpress 100");
		ui_interface->addCheckButton("Note CHAT Bool IN (Note 100)", &fcheckbox1);
		ui_interface->declare(&fbargraph2, "midi", "chanpress 101");
		ui_interface->addHorizontalBargraph("Note CHAT Bool OUT (Note 101)", &fbargraph2, 0.0f, 1.0f);
		ui_interface->declare(&fslider1, "midi", "chanpress 50");
		ui_interface->addHorizontalSlider("Note CHAT Value IN (Note 50)", &fslider1, 60.0f, 0.0f, 127.0f, 1.0f);
		ui_interface->declare(&fbargraph3, "midi", "chanpress 51");
		ui_interface->addHorizontalBargraph("Note CHAT Value OUT (Note 51)", &fbargraph3, 0.0f, 127.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("KEY AFTERTOUCH (KAT) IN/OUT");
		ui_interface->declare(&fcheckbox3, "midi", "keypress 100");
		ui_interface->addCheckButton("Note KAT Bool IN (Note 100)", &fcheckbox3);
		ui_interface->declare(&fbargraph6, "midi", "keypress 101");
		ui_interface->addHorizontalBargraph("Note KAT Bool OUT (Note 101)", &fbargraph6, 0.0f, 1.0f);
		ui_interface->declare(&fslider3, "midi", "keypress 50");
		ui_interface->addHorizontalSlider("Note KAT Value IN (Note 50)", &fslider3, 60.0f, 0.0f, 127.0f, 1.0f);
		ui_interface->declare(&fbargraph7, "midi", "keypress 51");
		ui_interface->addHorizontalBargraph("Note KAT Value OUT (Note 51)", &fbargraph7, 0.0f, 127.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("PITCHWHEEL IN/OUT");
		ui_interface->declare(&fcheckbox0, "midi", "pitchwheel");
		ui_interface->addCheckButton("Pitchwheel Bool IN", &fcheckbox0);
		ui_interface->declare(&fbargraph0, "midi", "pitchwheel");
		ui_interface->addHorizontalBargraph("Pitchwheel Bool OUT", &fbargraph0, 0.0f, 1.0f);
		ui_interface->declare(&fslider0, "midi", "pitchwheel");
		ui_interface->addHorizontalSlider("Pitchwheel Value IN", &fslider0, 0.0f, -8192.0f, 8191.0f, 1.0f);
		ui_interface->declare(&fbargraph1, "midi", "pitchwheel");
		ui_interface->addHorizontalBargraph("Pitchwheel Value OUT", &fbargraph1, -8192.0f, 8191.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("PROGRAM CHANGE (PC) IN/OUT");
		ui_interface->declare(&fcheckbox2, "midi", "pgm 100");
		ui_interface->addCheckButton("ProgramChange Bool IN (PC 100)", &fcheckbox2);
		ui_interface->declare(&fbargraph4, "midi", "pgm 101");
		ui_interface->addHorizontalBargraph("ProgramChange Bool OUT (PC 101)", &fbargraph4, 0.0f, 1.0f);
		ui_interface->declare(&fslider2, "midi", "pgm 50");
		ui_interface->addHorizontalSlider("ProgramChange Value IN (PC 50)", &fslider2, 60.0f, 0.0f, 127.0f, 1.0f);
		ui_interface->declare(&fbargraph5, "midi", "pgm 51");
		ui_interface->addHorizontalBargraph("ProgramChange Value OUT (PC 51)", &fbargraph5, 0.0f, 127.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		fbargraph0 = float(fcheckbox0);
		fbargraph1 = float(fslider0);
		fbargraph2 = float(fcheckbox1);
		fbargraph3 = float(fslider1);
		fbargraph4 = float(fcheckbox2);
		fbargraph5 = float(fslider2);
		fbargraph6 = float(fcheckbox3);
		fbargraph7 = float(fslider3);
		fbargraph8 = float(fcheckbox6);
		fbargraph9 = float(fslider4);
		fbargraph10 = float(fcheckbox7);
		fbargraph11 = float(fslider5);
		fbargraph12 = float(fslider6);
		fbargraph13 = float(fcheckbox8);
		//zone2b
		//zone3
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* output0 = output[0];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			output0[i] = (FAUSTFLOAT)iConst0;
		}
	}
};


