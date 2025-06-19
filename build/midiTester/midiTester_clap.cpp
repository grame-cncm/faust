/* ------------------------------------------------------------
author: "Vincent Rateau, GRAME"
license: "GPL v3"
name: "midiTester"
version: "1.0"
Code generated with Faust 2.81.0 (https://faust.grame.fr)
Compilation options: -a /Users/cucu/Documents/GitHub/faust/architecture/clap/clap-arch.cpp -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

//dummy clap architecture file
//this file will translate faust's mydsp c++ class into the clap plugin interface
//it should include plugin lifecycle, audio block processing calls, parameter registration and ui integration using buildUserInterface () and CLAP API
//core of the plugin backend

//includes for faust dsp and ui
#include <faust/dsp/dsp.h>
#include <faust/dsp/poly-dsp.h>
#include <faust/gui/MapUI.h>
#include <faust/gui/meta.h>
#include <faust/midi/midi.h> //faust midi types
#include <faust/gui/UI.h>
#include <faust/gui/GUI.h>
//include for cpp logging
#include <iostream>

//includes for the clap helpers glue
#include <clap/helpers/plugin.hh>
#include <clap/helpers/host-proxy.hh>
#include <clap/events.h>
#include <clap/ext/note-ports.h> //clap note port api

//guarded MapUI subclass to prevent accidental param writes
struct GuardedUI : public MapUI {
    bool allowWrite = false;

    struct ParamMeta {
        FAUSTFLOAT init;
        FAUSTFLOAT min;
        FAUSTFLOAT max;
    };
    std::vector<ParamMeta> paramRanges;

    void setParamValue(const std::string& path, FAUSTFLOAT val) {
        if (!allowWrite) std::abort();
        MapUI::setParamValue(path, val);
    }

    void setParamValue(int index, FAUSTFLOAT val) {
        if (!allowWrite) return;
        std::string addr = getParamAddress(index);
        MapUI::setParamValue(addr, val);
    }

    void guardedSetByIndex(int index, FAUSTFLOAT val) {
        if (!allowWrite) return;
        std::string addr = getParamAddress(index);
        MapUI::setParamValue(addr, val);
    }

    void addVerticalSlider(const char* label, FAUSTFLOAT* zone,
                           FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step) override {
        MapUI::addVerticalSlider(label, zone, init, fmin, fmax, step);
        paramRanges.push_back({init, fmin, fmax});
    }

    void addHorizontalSlider(const char* label, FAUSTFLOAT* zone,
                             FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step) override {
        MapUI::addHorizontalSlider(label, zone, init, fmin, fmax, step);
        paramRanges.push_back({init, fmin, fmax});
    }

    void addNumEntry(const char* label, FAUSTFLOAT* zone,
                     FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step) override {
        MapUI::addNumEntry(label, zone, init, fmin, fmax, step);
        paramRanges.push_back({init, fmin, fmax});
    }

    FAUSTFLOAT getParamMin(int index) const {
        if (index < 0 || index >= int(paramRanges.size())) return 0.f;
        return paramRanges[index].min;
    }

    FAUSTFLOAT getParamMax(int index) const {
        if (index < 0 || index >= int(paramRanges.size())) return 1.f;
        return paramRanges[index].max;
    }

    FAUSTFLOAT getParamInit(int index) const {
        if (index < 0 || index >= int(paramRanges.size())) return 0.5f;
        return paramRanges[index].init;
    }
};


struct GuardedScope {
    GuardedUI& ui;
    const char* tag;

    GuardedScope(GuardedUI& ui, const char* src = "unknown") : ui(ui), tag(src) {
        ui.allowWrite = true;
    }

    ~GuardedScope() {
        ui.allowWrite = false;
    }
};

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif


class mydsp : public dsp {
	
 private:
	
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
	FAUSTFLOAT fHbargraph8;
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT fHbargraph9;
	FAUSTFLOAT fCheckbox5;
	FAUSTFLOAT fHbargraph10;
	FAUSTFLOAT fHslider5;
	FAUSTFLOAT fHbargraph11;
	FAUSTFLOAT fCheckbox6;
	FAUSTFLOAT fHbargraph12;
	FAUSTFLOAT fHslider6;
	FAUSTFLOAT fHbargraph13;
	FAUSTFLOAT fCheckbox7;
	FAUSTFLOAT fHbargraph14;
	FAUSTFLOAT fHslider7;
	FAUSTFLOAT fHbargraph15;
	FAUSTFLOAT fCheckbox8;
	FAUSTFLOAT fCheckbox9;
	FAUSTFLOAT fCheckbox10;
	FAUSTFLOAT fHbargraph16;
	FAUSTFLOAT fHslider8;
	FAUSTFLOAT fHbargraph17;
	FAUSTFLOAT fCheckbox11;
	FAUSTFLOAT fHbargraph18;
	FAUSTFLOAT fHslider9;
	FAUSTFLOAT fHbargraph19;
	FAUSTFLOAT fCheckbox12;
	FAUSTFLOAT fHbargraph20;
	FAUSTFLOAT fHslider10;
	FAUSTFLOAT fHbargraph21;
	FAUSTFLOAT fCheckbox13;
	FAUSTFLOAT fHbargraph22;
	FAUSTFLOAT fHslider11;
	FAUSTFLOAT fHbargraph23;
	FAUSTFLOAT fCheckbox14;
	FAUSTFLOAT fHbargraph24;
	FAUSTFLOAT fHslider12;
	FAUSTFLOAT fHbargraph25;
	FAUSTFLOAT fHslider13;
	FAUSTFLOAT fHbargraph26;
	FAUSTFLOAT fHslider14;
	FAUSTFLOAT fHbargraph27;
	FAUSTFLOAT fCheckbox15;
	FAUSTFLOAT fHbargraph28;
	float fConst0;
	int fSampleRate;
	
 public:
	mydsp() {
	}
	
	void metadata(Meta* m) { 
		m->declare("author", "Vincent Rateau, GRAME");
		m->declare("compile_options", "-a /Users/cucu/Documents/GitHub/faust/architecture/clap/clap-arch.cpp -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("filename", "midiTester.dsp");
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
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = 0.0f;
	}
	
	virtual void instanceResetUserInterface() {
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fHslider0 = FAUSTFLOAT(0.0f);
		fCheckbox1 = FAUSTFLOAT(0.0f);
		fHslider1 = FAUSTFLOAT(0.0f);
		fCheckbox2 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(6e+01f);
		fCheckbox3 = FAUSTFLOAT(0.0f);
		fHslider3 = FAUSTFLOAT(6e+01f);
		fCheckbox4 = FAUSTFLOAT(0.0f);
		fHslider4 = FAUSTFLOAT(6e+01f);
		fCheckbox5 = FAUSTFLOAT(0.0f);
		fHslider5 = FAUSTFLOAT(6e+01f);
		fCheckbox6 = FAUSTFLOAT(0.0f);
		fHslider6 = FAUSTFLOAT(6e+01f);
		fCheckbox7 = FAUSTFLOAT(0.0f);
		fHslider7 = FAUSTFLOAT(6e+01f);
		fCheckbox8 = FAUSTFLOAT(0.0f);
		fCheckbox9 = FAUSTFLOAT(0.0f);
		fCheckbox10 = FAUSTFLOAT(0.0f);
		fHslider8 = FAUSTFLOAT(6e+01f);
		fCheckbox11 = FAUSTFLOAT(0.0f);
		fHslider9 = FAUSTFLOAT(6e+01f);
		fCheckbox12 = FAUSTFLOAT(0.0f);
		fHslider10 = FAUSTFLOAT(6e+01f);
		fCheckbox13 = FAUSTFLOAT(0.0f);
		fHslider11 = FAUSTFLOAT(6e+01f);
		fCheckbox14 = FAUSTFLOAT(0.0f);
		fHslider12 = FAUSTFLOAT(6e+01f);
		fHslider13 = FAUSTFLOAT(6e+01f);
		fHslider14 = FAUSTFLOAT(6e+01f);
		fCheckbox15 = FAUSTFLOAT(0.0f);
	}
	
	virtual void instanceClear() {
	}
	
	virtual void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	
	virtual void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual mydsp* clone() {
		return new mydsp();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("FAUST MIDI TESTER");
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->openVerticalBox("CTRL CHAN IN/OUT");
		ui_interface->declare(&fHslider13, "midi", "ctrl 50 2");
		ui_interface->addHorizontalSlider("Ctrl Value IN (Ctrl 50 Channel 2)", &fHslider13, FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHbargraph26, "midi", "ctrl 74 3");
		ui_interface->addHorizontalBargraph("Ctrl Value OUT (Ctrl 74) Channel OUT(Chan 3)", &fHbargraph26, FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("CTRL IN/OUT");
		ui_interface->declare(&fCheckbox15, "midi", "ctrl 100");
		ui_interface->addCheckButton("Ctrl Bool IN (Ctrl 100)", &fCheckbox15);
		ui_interface->declare(&fHbargraph28, "midi", "ctrl 101");
		ui_interface->addHorizontalBargraph("Ctrl Bool OUT (Ctrl 101)", &fHbargraph28, FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider14, "midi", "ctrl 50");
		ui_interface->addHorizontalSlider("Ctrl Value IN (Ctrl 50)", &fHslider14, FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHbargraph27, "midi", "ctrl 51");
		ui_interface->addHorizontalBargraph("Ctrl Value OUT (Ctrl 51)", &fHbargraph27, FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("KEY PRESS CHAN IN/OUT");
		ui_interface->declare(&fHbargraph17, "midi", "keypress 51 3");
		ui_interface->addHorizontalBargraph("Note Value OUT (Note 51 Channel 3)", &fHbargraph17, FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f));
		ui_interface->declare(&fCheckbox10, "midi", "keypress 50 2");
		ui_interface->addCheckButton("Pressure Bool IN (Note 50 Channel 2)", &fCheckbox10);
		ui_interface->declare(&fHbargraph16, "midi", "keypress 101 3");
		ui_interface->addHorizontalBargraph("Pressure Bool OUT (Note 101 Channel 3)", &fHbargraph16, FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider8, "midi", "keypress 50 2");
		ui_interface->addHorizontalSlider("Pressure Value IN (Note 50 Channel 2)", &fHslider8, FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("MIDI SYNC (IN)");
		ui_interface->declare(&fCheckbox8, "midi", "start");
		ui_interface->declare(&fCheckbox8, "midi", "stop");
		ui_interface->addCheckButton("MIDI START/STOP", &fCheckbox8);
		ui_interface->declare(&fCheckbox9, "midi", "clock");
		ui_interface->addCheckButton("MIDI clock signal", &fCheckbox9);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("NOTE OFF CHAN IN/OUT");
		ui_interface->declare(&fCheckbox11, "midi", "keyoff 50 2");
		ui_interface->addCheckButton("NoteOff Bool IN (Note 50 Channel 2)", &fCheckbox11);
		ui_interface->declare(&fHbargraph18, "midi", "keyoff 101 3");
		ui_interface->addHorizontalBargraph("NoteOff Bool OUT (Note 101 Channel 3)", &fHbargraph18, FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider9, "midi", "keyoff 50 2");
		ui_interface->addHorizontalSlider("NoteOff Value IN (Note 50 Channel 2)", &fHslider9, FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHbargraph19, "midi", "keyoff 51 3");
		ui_interface->addHorizontalBargraph("NoteOff Value OUT (Note 51 Channel 3)", &fHbargraph19, FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("NOTE OFF IN/OUT");
		ui_interface->declare(&fCheckbox12, "midi", "keyoff 100");
		ui_interface->addCheckButton("NoteOff Bool IN (Note 100)", &fCheckbox12);
		ui_interface->declare(&fHbargraph20, "midi", "keyoff 101");
		ui_interface->addHorizontalBargraph("NoteOff Bool OUT (Note 101)", &fHbargraph20, FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider10, "midi", "keyoff 50");
		ui_interface->addHorizontalSlider("NoteOff Value IN (Note 50)", &fHslider10, FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHbargraph21, "midi", "keyoff 51");
		ui_interface->addHorizontalBargraph("NoteOff Value OUT (Note 51)", &fHbargraph21, FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("NOTE ON CHAN IN/OUT");
		ui_interface->declare(&fCheckbox13, "midi", "keyon 50 2");
		ui_interface->addCheckButton("NoteOn Chan Bool IN (Note 50 Channel 2)", &fCheckbox13);
		ui_interface->declare(&fHbargraph22, "midi", "keyon 101 3");
		ui_interface->addHorizontalBargraph("NoteOn Chan Bool OUT (Note 101 Channel 3)", &fHbargraph22, FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider11, "midi", "keyon 50 2");
		ui_interface->addHorizontalSlider("NoteOn Value IN (Note 50 Channel 2)", &fHslider11, FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHbargraph23, "midi", "keyon 51 3");
		ui_interface->addHorizontalBargraph("NoteOn Value OUT (Note 51 Chan 3)", &fHbargraph23, FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("NOTE ON IN/OUT");
		ui_interface->declare(&fCheckbox14, "midi", "keyon 100");
		ui_interface->addCheckButton("NoteOn Bool IN (Note 100)", &fCheckbox14);
		ui_interface->declare(&fHbargraph24, "midi", "keyon 101");
		ui_interface->addHorizontalBargraph("NoteOn Bool OUT (Note 101)", &fHbargraph24, FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider12, "midi", "keyon 50");
		ui_interface->addHorizontalSlider("NoteOn Value IN (Note 50)", &fHslider12, FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHbargraph25, "midi", "keyon 51");
		ui_interface->addHorizontalBargraph("NoteOn Value OUT (Note 51)", &fHbargraph25, FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f));
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->openVerticalBox("CHANNEL AFTERTOUCH (CHAT) IN/OUT");
		ui_interface->declare(&fCheckbox3, "midi", "chanpress 100");
		ui_interface->addCheckButton("Note CHAT Bool IN (Note 100)", &fCheckbox3);
		ui_interface->declare(&fHbargraph6, "midi", "chanpress 101");
		ui_interface->addHorizontalBargraph("Note CHAT Bool OUT (Note 101)", &fHbargraph6, FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider3, "midi", "chanpress 50");
		ui_interface->addHorizontalSlider("Note CHAT Value IN (Note 50)", &fHslider3, FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHbargraph7, "midi", "chanpress 51");
		ui_interface->addHorizontalBargraph("Note CHAT Value OUT (Note 51)", &fHbargraph7, FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("CHANNEL AFTERTOUCH CHAN (CHAT) IN/OUT");
		ui_interface->declare(&fCheckbox2, "midi", "chanpress 100 2");
		ui_interface->addCheckButton("Note CHAT Bool IN (Note 100) (Chan 2)", &fCheckbox2);
		ui_interface->declare(&fHbargraph4, "midi", "chanpress 101 3");
		ui_interface->addHorizontalBargraph("Note CHAT Bool OUT (Note 101) (Chan 3)", &fHbargraph4, FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider2, "midi", "chanpress 50 2");
		ui_interface->addHorizontalSlider("Note CHAT Chan Value IN (Note 50) (Chan 2)", &fHslider2, FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHbargraph5, "midi", "chanpress 51 3");
		ui_interface->addHorizontalBargraph("Note CHAT Value OUT (Note 51) (Chan 3)", &fHbargraph5, FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("KEY AFTERTOUCH (KAT) IN/OUT");
		ui_interface->declare(&fCheckbox7, "midi", "keypress 100");
		ui_interface->addCheckButton("Note KAT Bool IN (Note 100)", &fCheckbox7);
		ui_interface->declare(&fHbargraph14, "midi", "keypress 101");
		ui_interface->addHorizontalBargraph("Note KAT Bool OUT (Note 101)", &fHbargraph14, FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider7, "midi", "keypress 50");
		ui_interface->addHorizontalSlider("Note KAT Value IN (Note 50)", &fHslider7, FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHbargraph15, "midi", "keypress 51");
		ui_interface->addHorizontalBargraph("Note KAT Value OUT (Note 51)", &fHbargraph15, FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("KEY AFTERTOUCH CHAN (KAT) IN/OUT");
		ui_interface->declare(&fCheckbox6, "midi", "keypress 100 2");
		ui_interface->addCheckButton("Note KAT Bool IN (Note 100) (Chan 2)", &fCheckbox6);
		ui_interface->declare(&fHbargraph12, "midi", "keypress 101 3");
		ui_interface->addHorizontalBargraph("Note KAT Bool OUT (Note 101) (Chan 3)", &fHbargraph12, FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider6, "midi", "keypress 50 2");
		ui_interface->addHorizontalSlider("Note KAT Value IN (Note 50) (Chan 2)", &fHslider6, FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHbargraph13, "midi", "keypress 51 3");
		ui_interface->addHorizontalBargraph("Note KAT Value OUT (Note 51) (Chan 3)", &fHbargraph13, FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("PITCHWHEEL CHAN IN/OUT");
		ui_interface->declare(&fCheckbox0, "midi", "pitchwheel 2");
		ui_interface->addCheckButton("Pitchwheel Bool IN (Chan 2)", &fCheckbox0);
		ui_interface->declare(&fHbargraph0, "midi", "pitchwheel 15");
		ui_interface->addHorizontalBargraph("Pitchwheel Bool OUT (Chan 15)", &fHbargraph0, FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider0, "midi", "pitchwheel 2");
		ui_interface->addHorizontalSlider("Pitchwheel Value IN (Chan 2)", &fHslider0, FAUSTFLOAT(0.0f), FAUSTFLOAT(-8192.0f), FAUSTFLOAT(8191.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHbargraph1, "midi", "pitchwheel 15");
		ui_interface->addHorizontalBargraph("Pitchwheel Value OUT (Chan 15)", &fHbargraph1, FAUSTFLOAT(-8192.0f), FAUSTFLOAT(8191.0f));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("PITCHWHEEL IN/OUT");
		ui_interface->declare(&fCheckbox1, "midi", "pitchwheel");
		ui_interface->addCheckButton("Pitchwheel Bool IN", &fCheckbox1);
		ui_interface->declare(&fHbargraph2, "midi", "pitchwheel");
		ui_interface->addHorizontalBargraph("Pitchwheel Bool OUT", &fHbargraph2, FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider1, "midi", "pitchwheel");
		ui_interface->addHorizontalSlider("Pitchwheel Value IN", &fHslider1, FAUSTFLOAT(0.0f), FAUSTFLOAT(-8192.0f), FAUSTFLOAT(8191.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHbargraph3, "midi", "pitchwheel");
		ui_interface->addHorizontalBargraph("Pitchwheel Value OUT", &fHbargraph3, FAUSTFLOAT(-8192.0f), FAUSTFLOAT(8191.0f));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("PROGRAM CHANGE (PC) IN/OUT");
		ui_interface->declare(&fCheckbox5, "midi", "pgm 1");
		ui_interface->addCheckButton("ProgramChange Bool IN (PC 1)", &fCheckbox5);
		ui_interface->declare(&fHbargraph10, "midi", "pgm 2");
		ui_interface->addHorizontalBargraph("ProgramChange Bool OUT (PC 2)", &fHbargraph10, FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider5, "midi", "pgm 1");
		ui_interface->addHorizontalSlider("ProgramChange Value IN (PC 1)", &fHslider5, FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHbargraph11, "midi", "pgm 2");
		ui_interface->addHorizontalBargraph("ProgramChange Value OUT (PC 2)", &fHbargraph11, FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("PROGRAM CHANGE CHAN (PC) IN/OUT");
		ui_interface->declare(&fCheckbox4, "midi", "pgm 1 2");
		ui_interface->addCheckButton("ProgramChange Bool IN (PC 1) (CHAN 2)", &fCheckbox4);
		ui_interface->declare(&fHbargraph8, "midi", "pgm 2 3");
		ui_interface->addHorizontalBargraph("ProgramChange Bool OUT (PC 2) (CHAN 3)", &fHbargraph8, FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider4, "midi", "pgm 1 2");
		ui_interface->addHorizontalSlider("ProgramChange Value IN (PC 1) (CHAN 2)", &fHslider4, FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHbargraph9, "midi", "pgm 2 3");
		ui_interface->addHorizontalBargraph("ProgramChange Value OUT (PC 2) (CHAN 3)", &fHbargraph9, FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f));
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		fHbargraph0 = FAUSTFLOAT(float(fCheckbox0));
		fHbargraph1 = FAUSTFLOAT(float(fHslider0));
		fHbargraph2 = FAUSTFLOAT(float(fCheckbox1));
		fHbargraph3 = FAUSTFLOAT(float(fHslider1));
		fHbargraph4 = FAUSTFLOAT(float(fCheckbox2));
		fHbargraph5 = FAUSTFLOAT(float(fHslider2));
		fHbargraph6 = FAUSTFLOAT(float(fCheckbox3));
		fHbargraph7 = FAUSTFLOAT(float(fHslider3));
		fHbargraph8 = FAUSTFLOAT(float(fCheckbox4));
		fHbargraph9 = FAUSTFLOAT(float(fHslider4));
		fHbargraph10 = FAUSTFLOAT(float(fCheckbox5));
		fHbargraph11 = FAUSTFLOAT(float(fHslider5));
		fHbargraph12 = FAUSTFLOAT(float(fCheckbox6));
		fHbargraph13 = FAUSTFLOAT(float(fHslider6));
		fHbargraph14 = FAUSTFLOAT(float(fCheckbox7));
		fHbargraph15 = FAUSTFLOAT(float(fHslider7));
		fHbargraph16 = FAUSTFLOAT(float(fCheckbox10));
		fHbargraph17 = FAUSTFLOAT(float(fHslider8));
		fHbargraph18 = FAUSTFLOAT(float(fCheckbox11));
		fHbargraph19 = FAUSTFLOAT(float(fHslider9));
		fHbargraph20 = FAUSTFLOAT(float(fCheckbox12));
		fHbargraph21 = FAUSTFLOAT(float(fHslider10));
		fHbargraph22 = FAUSTFLOAT(float(fCheckbox13));
		fHbargraph23 = FAUSTFLOAT(float(fHslider11));
		fHbargraph24 = FAUSTFLOAT(float(fCheckbox14));
		fHbargraph25 = FAUSTFLOAT(float(fHslider12));
		fHbargraph26 = FAUSTFLOAT(float(fHslider13));
		fHbargraph27 = FAUSTFLOAT(float(fHslider14));
		fHbargraph28 = FAUSTFLOAT(float(fCheckbox15));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			output0[i0] = FAUSTFLOAT(fConst0);
		}
	}

};

class GainPlugin;

using Base = clap::helpers::Plugin<
    clap::helpers::MisbehaviourHandler::Terminate,
    clap::helpers::CheckingLevel::Minimal>;


static const char* gain_features[] = { CLAP_PLUGIN_FEATURE_AUDIO_EFFECT, nullptr };

static const clap_plugin_descriptor_t gain_desc = {
    .clap_version = CLAP_VERSION_INIT,
    .id = "org.faust.gain",
    .name = "Faust Gain",
    .vendor = "faust",
    .url = "https://faust.grame.fr",
    .manual_url = "",
    .support_url = "",
    .version = "1.0.0",
    .description = "Simple gain plugin generated from Faust",
    .features = gain_features
};

class GainPlugin final : public Base {
public:
    int fNumInputs = 2; //defautl to stereo??
    int fNumOutputs = 2;
    mydsp* fBaseDSP = nullptr; //original Faust DSP
    mydsp_poly* fDSP = nullptr; //midi-aware wrapper


    GuardedUI fUI;
    std::vector<std::string> fParamAddresses;
    std::vector<float> fExpectedValues;
    std::vector<int> fParamIndices;
    bool fHasFlushed = false;
    bool fIsProcessing = false;

    GainPlugin(const clap_plugin_descriptor_t* desc, const clap_host_t* host)
        : Base(desc, host) {}

    bool init() noexcept override {
        fBaseDSP = new mydsp();
        fDSP = new mydsp_poly(fBaseDSP, 16, true, true);
        fDSP->buildUserInterface(&fUI);

        fParamAddresses.clear();
        fExpectedValues.clear();
        fParamIndices.clear();

        for (int i = 0; i < fUI.getParamsCount(); ++i) {
            std::string shortname = fUI.getParamShortname(i);
            if (shortname.empty()) continue;
            fParamAddresses.emplace_back(shortname);
            fExpectedValues.push_back(fUI.getParamValue(shortname));
            fParamIndices.push_back(i); //i is index in MapUI
        }

        return true;
    }


    bool startProcessing() noexcept override {
        std::cerr << "[startProcessing] called\n";
        fIsProcessing = true;
        return true;
    }

    void stopProcessing() noexcept override {
        std::cerr << "[stopProcessing] called\n";
        fIsProcessing = false;
    }


    bool activate(double sampleRate, uint32_t, uint32_t) noexcept override {
        fDSP->init(sampleRate);
        fNumInputs = fDSP->getNumInputs();
        fNumOutputs = fDSP->getNumOutputs();
        std::cerr << "[activate] Sample rate: " << sampleRate << "\n";
        std::cerr << "[activate] Inputs: " << fNumInputs << ", Outputs: " << fNumOutputs << "\n";
        return true;
    }

    bool applyParamEventIfValid(const clap_event_header_t* hdr) {
        if (!hdr || hdr->space_id != CLAP_CORE_EVENT_SPACE_ID || hdr->type != CLAP_EVENT_PARAM_VALUE)
            return false;

        const auto* ev = reinterpret_cast<const clap_event_param_value_t*>(hdr);
        if (!ev || ev->param_id >= fParamAddresses.size() || ev->param_id >= fExpectedValues.size())
            return false;
        if (fParamAddresses[ev->param_id].empty())
            return false;

        GuardedScope guard(fUI, "applyParamEvent");
        fUI.setParamValue(fParamAddresses[ev->param_id], ev->value);
        fExpectedValues[ev->param_id] = ev->value;
        return true;
    }

    void handleNoteEvent(const clap_event_header_t* hdr) {
        if (!hdr || hdr->space_id != CLAP_CORE_EVENT_SPACE_ID) return;

        switch (hdr->type) {
            case CLAP_EVENT_NOTE_ON: {
                auto* ev = reinterpret_cast<const clap_event_note_t*>(hdr);
                fDSP->keyOn(ev->channel, ev->key, ev->velocity);
                break;
            }
            case CLAP_EVENT_NOTE_OFF: {
                auto* ev = reinterpret_cast<const clap_event_note_t*>(hdr);
                fDSP->keyOff(ev->channel, ev->key, ev->velocity);
                break;
            }
            case CLAP_EVENT_MIDI: {
                auto* ev = reinterpret_cast<const clap_event_midi_t*>(hdr);
                uint8_t status = ev->data[0] & 0xF0;
                uint8_t channel = ev->data[0] & 0x0F;
                uint8_t data1 = ev->data[1];
                uint8_t data2 = ev->data[2];

                switch (status) {
                    case 0x90: fDSP->keyOn(channel, data1, data2); break;
                    case 0x80: fDSP->keyOff(channel, data1, data2); break;
                    case 0xB0: fDSP->ctrlChange(channel, data1, data2); break;
                    case 0xE0: fDSP->pitchWheel(channel, (data2 << 7) | data1); break;
                }
                break;
            }
            default:
                break;
        }
    }


    const void* get_extension(const char* id) noexcept {
        if (std::strcmp(id, CLAP_EXT_NOTE_PORTS) == 0) return (const clap_plugin_note_ports_t*)this;
        if (std::strcmp(id, CLAP_EXT_STATE) == 0) return (const clap_plugin_state_t*)this;
        if (std::strcmp(id, CLAP_EXT_PARAMS) == 0) return (const clap_plugin_params_t*)this;
        return nullptr;
    }

    clap_process_status process(const clap_process_t* process) noexcept override {
        std::cerr << "[process] Entered process()\n";
        if (!fIsProcessing) {
            std::cerr << "[process] fIsProcessing is false\n";
            return CLAP_PROCESS_SLEEP;
        }
        if (!process || process->audio_inputs_count < 1 || process->audio_outputs_count < 1)
            return CLAP_PROCESS_ERROR;
        const auto& inBuffer = process->audio_inputs[0];
        const auto& outBuffer = process->audio_outputs[0];

        std::cerr << "[process] Channel count: input = " << inBuffer.channel_count
              << ", output = " << outBuffer.channel_count << "\n";


        if (inBuffer.channel_count < fNumInputs || outBuffer.channel_count < fNumOutputs)
            return CLAP_PROCESS_ERROR;

        if (inBuffer.channel_count == 0 || outBuffer.channel_count == 0)
            return CLAP_PROCESS_CONTINUE;

        if (process->in_events) {
            for (uint32_t i = 0, N = process->in_events->size(process->in_events); i < N; ++i) {
                const clap_event_header_t* hdr = process->in_events->get(process->in_events, i);
                applyParamEventIfValid(hdr);
                handleNoteEvent(hdr);
            }
        }

        FAUSTFLOAT* inputs[fNumInputs];
        FAUSTFLOAT* outputs[fNumOutputs];
        for (int i = 0; i < fNumInputs; ++i)
            inputs[i] = inBuffer.data32[i];
        for (int i = 0; i < fNumOutputs; ++i)
            outputs[i] = outBuffer.data32[i];

        GuardedScope guard(fUI, "compute");
        fDSP->compute(process->frames_count, inputs, outputs);
        std::cerr << "[process] DSP compute finished\n";
        return CLAP_PROCESS_CONTINUE;
    }

    bool implementsNotePorts() const noexcept override { return true; }
    uint32_t notePortsCount(bool isInput) const noexcept override { return isInput ? 1 : 0; }

    bool notePortsInfo(uint32_t index, bool isInput, clap_note_port_info_t* info) const noexcept override {
        if (!isInput || index != 0 || !info) return false;
        std::memset(info, 0, sizeof(*info));
        info->id = index;
        std::snprintf(info->name, sizeof(info->name), "MIDI In");
        info->supported_dialects = CLAP_NOTE_DIALECT_CLAP | CLAP_NOTE_DIALECT_MIDI;
        info->preferred_dialect = CLAP_NOTE_DIALECT_CLAP;
        return true;
    }

    bool implementsState() const noexcept override { return true; }

    bool stateSave(const clap_ostream_t* stream) noexcept override {
        if (!stream || !stream->write) return false;
        uint32_t paramCount = fExpectedValues.size();
        if (!stream->write(stream, &paramCount, sizeof(paramCount))) return false;
        for (float v : fExpectedValues)
            if (!stream->write(stream, &v, sizeof(v))) return false;
        return true;
    }

    bool stateLoad(const clap_istream_t* stream) noexcept override {
        if (!stream || !stream->read) return false;
        uint32_t paramCount = 0;
        if (!stream->read(stream, &paramCount, sizeof(paramCount))) return false;
        if (paramCount > fExpectedValues.size())
            return false;
        if (paramCount != fExpectedValues.size())
            return false;
        for (uint32_t i = 0; i < paramCount; ++i) {
            float v;
            if (!stream->read(stream, &v, sizeof(v))) return false;
            GuardedScope guard(fUI, "stateLoad");
            fUI.setParamValue(fParamAddresses[i], v);
            fExpectedValues[i] = v;
        }

        if (_host.canUseParams()) {
            _host.paramsRescan(CLAP_PARAM_RESCAN_VALUES | CLAP_PARAM_RESCAN_ALL);
            _host.paramsRequestFlush();
        }

        return true;
    }

    bool implementsParams() const noexcept override { return true; }
    uint32_t paramsCount() const noexcept override { return static_cast<uint32_t>(fParamAddresses.size()); }

    bool paramsInfo(uint32_t index, clap_param_info_t* info) const noexcept override {
        if (index >= fParamAddresses.size()) return false;
        std::memset(info, 0, sizeof(*info));
        info->id = index;
        const char* name = fParamAddresses[index].c_str();
        if (name[0] == '/') ++name;
        std::snprintf(info->name, sizeof(info->name), "%s", name);

        FAUSTFLOAT min = fUI.getParamMin(index);
        FAUSTFLOAT max = fUI.getParamMax(index);
        FAUSTFLOAT init = fUI.getParamInit(index);

        info->min_value = min;
        info->max_value = max;
        info->default_value = init;
        info->flags = CLAP_PARAM_IS_AUTOMATABLE;
        return true;
    }

    bool paramsValue(clap_id id, double* value) noexcept override {
        if (!value || id >= fExpectedValues.size())
            return false;
        *value = fExpectedValues[id];
        return true;
    }

    bool paramsTextToValue(clap_id id, const char* text, double* outValue) noexcept override {
        if (!text || !outValue || id >= fExpectedValues.size())
            return false;
        try {
            *outValue = std::stod(text);
            return true;
        } catch (...) {
            return false;
        }
    }

    bool paramsValueToText(clap_id id, double value, char* outBuffer, uint32_t bufferSize) noexcept override {
        if (!outBuffer || bufferSize == 0 || id >= fExpectedValues.size())
            return false;
        std::snprintf(outBuffer, bufferSize, "%.3f", value);
        return true;
    }

    void paramsFlush(const clap_input_events_t* in, const clap_output_events_t*) noexcept override {
        if (!in) return;
        fHasFlushed = true;
        for (uint32_t i = 0; i < in->size(in); ++i) {
            const clap_event_header_t* hdr = in->get(in, i);
            if (!hdr) continue;
            applyParamEventIfValid(hdr);
            handleNoteEvent(hdr);
        }
    }

    bool implementsAudioPorts() const noexcept override { return true; }
    uint32_t audioPortsCount(bool isInput) const noexcept override { return 1; }

    bool audioPortsInfo(uint32_t index, bool isInput, clap_audio_port_info_t* info) const noexcept override {
        if (index != 0 || !info) return false;
        std::memset(info, 0, sizeof(*info));
        info->id = index;
        std::snprintf(info->name, sizeof(info->name), "%s", isInput ? "Input" : "Output");
        info->channel_count = isInput ? std::max(1, fNumInputs) : std::max(1, fNumOutputs);
        info->flags = CLAP_AUDIO_PORT_IS_MAIN;
        return true;
    }

    using Base::clapPlugin;
    static const clap_plugin_t* create(const clap_host_t* host) {
        return (new GainPlugin(&gain_desc, host))->clapPlugin();
    }
};

// Factory glue
static uint32_t plugin_count(const clap_plugin_factory_t*) { return 1; }
static const clap_plugin_descriptor_t* plugin_desc(const clap_plugin_factory_t*, uint32_t index) {
    return (index == 0) ? &gain_desc : nullptr;
}
static const clap_plugin_t* plugin_create(const clap_plugin_factory_t*, const clap_host_t* host, const char* plugin_id) {
    if (std::strcmp(plugin_id, gain_desc.id) == 0)
        return GainPlugin::create(host);
    return nullptr;
}
static const clap_plugin_factory_t gain_factory = {
    .get_plugin_count = plugin_count,
    .get_plugin_descriptor = plugin_desc,
    .create_plugin = plugin_create
};
static bool entry_init(const char* path) { return true; }
static void entry_deinit() {}

extern "C" {
CLAP_EXPORT const void* clap_get_factory(const char* factory_id) {
    if (std::strcmp(factory_id, CLAP_PLUGIN_FACTORY_ID) == 0)
        return &gain_factory;
    return nullptr;
}
CLAP_EXPORT const clap_plugin_entry_t clap_entry = {
    CLAP_VERSION_INIT,
    entry_init,
    entry_deinit,
    clap_get_factory
};
}

#endif
