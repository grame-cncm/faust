/* ------------------------------------------------------------
author: "Vincent Rateau, GRAME"
license: "GPL v3"
name: "Faust Midi Tester"
version: "1.0"
Code generated with Faust 2.87.10 (https://faust.grame.fr)
Compilation options: -a /Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/archs/impulsearch.cpp -lang cpp -i -fpga-mem-th 4 -ct 1 -es 1 -mcd 4 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT double
#endif

#include "controlTools.h"

//----------------------------------------------------------------------------
//FAUST generated code
//----------------------------------------------------------------------------


#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#ifndef FAUST_INT_WRAP
#define FAUST_INT_WRAP
inline int faust_wrap_add(int a, int b) { return int((unsigned int)a + (unsigned int)b); }
inline int faust_wrap_sub(int a, int b) { return int((unsigned int)a - (unsigned int)b); }
inline int faust_wrap_mul(int a, int b) { return int((unsigned int)a * (unsigned int)b); }
#endif


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
	double fConst0;
	int fSampleRate;
	
 public:
	mydsp() {
	}
	
	mydsp(const mydsp&) = default;
	
	virtual ~mydsp() = default;
	
	mydsp& operator=(const mydsp&) = default;
	
	void metadata(Meta* m) { 
		m->declare("author", "Vincent Rateau, GRAME");
		m->declare("compile_options", "-a /Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/archs/impulsearch.cpp -lang cpp -i -fpga-mem-th 4 -ct 1 -es 1 -mcd 4 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs");
		m->declare("filename", "midi_tester.dsp");
		m->declare("license", "GPL v3");
		m->declare("name", "Faust Midi Tester");
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
		fConst0 = 0.0;
	}
	
	virtual void instanceResetUserInterface() {
		fCheckbox0 = static_cast<FAUSTFLOAT>(0.0);
		fHslider0 = static_cast<FAUSTFLOAT>(0.0);
		fCheckbox1 = static_cast<FAUSTFLOAT>(0.0);
		fHslider1 = static_cast<FAUSTFLOAT>(6e+01);
		fCheckbox2 = static_cast<FAUSTFLOAT>(0.0);
		fHslider2 = static_cast<FAUSTFLOAT>(6e+01);
		fCheckbox3 = static_cast<FAUSTFLOAT>(0.0);
		fHslider3 = static_cast<FAUSTFLOAT>(6e+01);
		fCheckbox4 = static_cast<FAUSTFLOAT>(0.0);
		fCheckbox5 = static_cast<FAUSTFLOAT>(0.0);
		fCheckbox6 = static_cast<FAUSTFLOAT>(0.0);
		fHslider4 = static_cast<FAUSTFLOAT>(6e+01);
		fCheckbox7 = static_cast<FAUSTFLOAT>(0.0);
		fHslider5 = static_cast<FAUSTFLOAT>(6e+01);
		fHslider6 = static_cast<FAUSTFLOAT>(6e+01);
		fCheckbox8 = static_cast<FAUSTFLOAT>(0.0);
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
		return new mydsp(*this);
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("FAUST MIDI TESTER");
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->openVerticalBox("CTRL IN/OUT");
		ui_interface->declare(&fCheckbox8, "midi", "ctrl 100");
		ui_interface->addCheckButton("Ctrl Bool IN (Ctrl 100)", &fCheckbox8);
		ui_interface->declare(&fHbargraph13, "midi", "ctrl 101");
		ui_interface->addHorizontalBargraph("Ctrl Bool OUT (Ctrl 101)", &fHbargraph13, FAUSTFLOAT(0.0), FAUSTFLOAT(1.0));
		ui_interface->declare(&fHslider6, "midi", "ctrl 50");
		ui_interface->addHorizontalSlider("Ctrl Value IN (Ctrl 50)", &fHslider6, FAUSTFLOAT(6e+01), FAUSTFLOAT(0.0), FAUSTFLOAT(127.0), FAUSTFLOAT(1.0));
		ui_interface->declare(&fHbargraph12, "midi", "ctrl 51");
		ui_interface->addHorizontalBargraph("Ctrl Value OUT (Ctrl 51)", &fHbargraph12, FAUSTFLOAT(0.0), FAUSTFLOAT(127.0));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("MIDI SYNC (IN)");
		ui_interface->declare(&fCheckbox4, "midi", "start");
		ui_interface->declare(&fCheckbox4, "midi", "stop");
		ui_interface->addCheckButton("MIDI START/STOP", &fCheckbox4);
		ui_interface->declare(&fCheckbox5, "midi", "clock");
		ui_interface->addCheckButton("MIDI clock signal", &fCheckbox5);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("NOTE OFF IN/OUT");
		ui_interface->declare(&fCheckbox6, "midi", "keyoff 100");
		ui_interface->addCheckButton("NoteOff Bool IN (Note 100)", &fCheckbox6);
		ui_interface->declare(&fHbargraph8, "midi", "keyoff 101");
		ui_interface->addHorizontalBargraph("NoteOff Bool OUT (Note 101)", &fHbargraph8, FAUSTFLOAT(0.0), FAUSTFLOAT(1.0));
		ui_interface->declare(&fHslider4, "midi", "keyoff 50");
		ui_interface->addHorizontalSlider("NoteOff Value IN (Note 50)", &fHslider4, FAUSTFLOAT(6e+01), FAUSTFLOAT(0.0), FAUSTFLOAT(127.0), FAUSTFLOAT(1.0));
		ui_interface->declare(&fHbargraph9, "midi", "keyoff 51");
		ui_interface->addHorizontalBargraph("NoteOff Value OUT (Note 51)", &fHbargraph9, FAUSTFLOAT(0.0), FAUSTFLOAT(127.0));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("NOTE ON IN/OUT");
		ui_interface->declare(&fCheckbox7, "midi", "keyon 100");
		ui_interface->addCheckButton("NoteOn Bool IN (Note 100)", &fCheckbox7);
		ui_interface->declare(&fHbargraph10, "midi", "keyon 101");
		ui_interface->addHorizontalBargraph("NoteOn Bool OUT (Note 101)", &fHbargraph10, FAUSTFLOAT(0.0), FAUSTFLOAT(1.0));
		ui_interface->declare(&fHslider5, "midi", "keyon 50");
		ui_interface->addHorizontalSlider("NoteOn Value IN (Note 50)", &fHslider5, FAUSTFLOAT(6e+01), FAUSTFLOAT(0.0), FAUSTFLOAT(127.0), FAUSTFLOAT(1.0));
		ui_interface->declare(&fHbargraph11, "midi", "keyon 51");
		ui_interface->addHorizontalBargraph("NoteOn Value OUT (Note 51)", &fHbargraph11, FAUSTFLOAT(0.0), FAUSTFLOAT(127.0));
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->openVerticalBox("CHANNEL AFTERTOUCH (CHAT) IN/OUT");
		ui_interface->declare(&fCheckbox1, "midi", "chanpress 100");
		ui_interface->addCheckButton("Note CHAT Bool IN (Note 100)", &fCheckbox1);
		ui_interface->declare(&fHbargraph2, "midi", "chanpress 101");
		ui_interface->addHorizontalBargraph("Note CHAT Bool OUT (Note 101)", &fHbargraph2, FAUSTFLOAT(0.0), FAUSTFLOAT(1.0));
		ui_interface->declare(&fHslider1, "midi", "chanpress 50");
		ui_interface->addHorizontalSlider("Note CHAT Value IN (Note 50)", &fHslider1, FAUSTFLOAT(6e+01), FAUSTFLOAT(0.0), FAUSTFLOAT(127.0), FAUSTFLOAT(1.0));
		ui_interface->declare(&fHbargraph3, "midi", "chanpress 51");
		ui_interface->addHorizontalBargraph("Note CHAT Value OUT (Note 51)", &fHbargraph3, FAUSTFLOAT(0.0), FAUSTFLOAT(127.0));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("KEY AFTERTOUCH (KAT) IN/OUT");
		ui_interface->declare(&fCheckbox3, "midi", "keypress 100");
		ui_interface->addCheckButton("Note KAT Bool IN (Note 100)", &fCheckbox3);
		ui_interface->declare(&fHbargraph6, "midi", "keypress 101");
		ui_interface->addHorizontalBargraph("Note KAT Bool OUT (Note 101)", &fHbargraph6, FAUSTFLOAT(0.0), FAUSTFLOAT(1.0));
		ui_interface->declare(&fHslider3, "midi", "keypress 50");
		ui_interface->addHorizontalSlider("Note KAT Value IN (Note 50)", &fHslider3, FAUSTFLOAT(6e+01), FAUSTFLOAT(0.0), FAUSTFLOAT(127.0), FAUSTFLOAT(1.0));
		ui_interface->declare(&fHbargraph7, "midi", "keypress 51");
		ui_interface->addHorizontalBargraph("Note KAT Value OUT (Note 51)", &fHbargraph7, FAUSTFLOAT(0.0), FAUSTFLOAT(127.0));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("PITCHWHEEL IN/OUT");
		ui_interface->declare(&fCheckbox0, "midi", "pitchwheel");
		ui_interface->addCheckButton("Pitchwheel Bool IN", &fCheckbox0);
		ui_interface->declare(&fHbargraph0, "midi", "pitchwheel");
		ui_interface->addHorizontalBargraph("Pitchwheel Bool OUT", &fHbargraph0, FAUSTFLOAT(0.0), FAUSTFLOAT(1.0));
		ui_interface->declare(&fHslider0, "midi", "pitchwheel");
		ui_interface->addHorizontalSlider("Pitchwheel Value IN", &fHslider0, FAUSTFLOAT(0.0), FAUSTFLOAT(-8192.0), FAUSTFLOAT(8191.0), FAUSTFLOAT(1.0));
		ui_interface->declare(&fHbargraph1, "midi", "pitchwheel");
		ui_interface->addHorizontalBargraph("Pitchwheel Value OUT", &fHbargraph1, FAUSTFLOAT(-8192.0), FAUSTFLOAT(8191.0));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("PROGRAM CHANGE (PC) IN/OUT");
		ui_interface->declare(&fCheckbox2, "midi", "pgm 100");
		ui_interface->addCheckButton("ProgramChange Bool IN (PC 100)", &fCheckbox2);
		ui_interface->declare(&fHbargraph4, "midi", "pgm 101");
		ui_interface->addHorizontalBargraph("ProgramChange Bool OUT (PC 101)", &fHbargraph4, FAUSTFLOAT(0.0), FAUSTFLOAT(1.0));
		ui_interface->declare(&fHslider2, "midi", "pgm 50");
		ui_interface->addHorizontalSlider("ProgramChange Value IN (PC 50)", &fHslider2, FAUSTFLOAT(6e+01), FAUSTFLOAT(0.0), FAUSTFLOAT(127.0), FAUSTFLOAT(1.0));
		ui_interface->declare(&fHbargraph5, "midi", "pgm 51");
		ui_interface->addHorizontalBargraph("ProgramChange Value OUT (PC 51)", &fHbargraph5, FAUSTFLOAT(0.0), FAUSTFLOAT(127.0));
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0_ptr = inputs[0];
		FAUSTFLOAT* output0_ptr = outputs[0];
		fHbargraph0 = static_cast<FAUSTFLOAT>(static_cast<double>(fCheckbox0));
		fHbargraph1 = static_cast<FAUSTFLOAT>(static_cast<double>(fHslider0));
		fHbargraph2 = static_cast<FAUSTFLOAT>(static_cast<double>(fCheckbox1));
		fHbargraph3 = static_cast<FAUSTFLOAT>(static_cast<double>(fHslider1));
		fHbargraph4 = static_cast<FAUSTFLOAT>(static_cast<double>(fCheckbox2));
		fHbargraph5 = static_cast<FAUSTFLOAT>(static_cast<double>(fHslider2));
		fHbargraph6 = static_cast<FAUSTFLOAT>(static_cast<double>(fCheckbox3));
		fHbargraph7 = static_cast<FAUSTFLOAT>(static_cast<double>(fHslider3));
		fHbargraph8 = static_cast<FAUSTFLOAT>(static_cast<double>(fCheckbox6));
		fHbargraph9 = static_cast<FAUSTFLOAT>(static_cast<double>(fHslider4));
		fHbargraph10 = static_cast<FAUSTFLOAT>(static_cast<double>(fCheckbox7));
		fHbargraph11 = static_cast<FAUSTFLOAT>(static_cast<double>(fHslider5));
		fHbargraph12 = static_cast<FAUSTFLOAT>(static_cast<double>(fHslider6));
		fHbargraph13 = static_cast<FAUSTFLOAT>(static_cast<double>(fCheckbox8));
		int vindex = 0;
		/* Main loop */
		for (vindex = 0; vindex <= (faust_wrap_sub(count, 4)); vindex = faust_wrap_add(vindex, 4)) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			int vsize = 4;
			/* Vectorizable loop 0 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fConst0);
			}
		}
		/* Remaining frames */
		if (vindex < count) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			int vsize = faust_wrap_sub(count, vindex);
			/* Vectorizable loop 0 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fConst0);
			}
		}
	}

};

int main(int argc, char* argv[])
{
    int linenum = 0;
    int nbsamples = 60000;
    
    // print general informations
    printHeader(new mydsp(), nbsamples);
    
    // linenum is incremented in runDSP and runPolyDSP
    runDSP(new mydsp(), argv[0], linenum, nbsamples/4);
    runDSP(new mydsp(), argv[0], linenum, nbsamples/4, false, true);
    runPolyDSP(new mydsp(), linenum, nbsamples/4, 4);
    runPolyDSP(new mydsp(), linenum, nbsamples/4, 1);
    
    return 0;
}

#endif
