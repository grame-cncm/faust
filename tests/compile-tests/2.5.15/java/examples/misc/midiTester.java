/* ------------------------------------------------------------
author: "Vincent Rateau, GRAME"
license: "GPL v3"
name: "midiTester"
version: "1.0"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	
	float fCheckbox0;
	float fHbargraph0;
	float fHslider0;
	float fHbargraph1;
	float fCheckbox1;
	float fHbargraph2;
	float fHslider1;
	float fHbargraph3;
	float fCheckbox2;
	float fHbargraph4;
	float fHslider2;
	float fHbargraph5;
	float fCheckbox3;
	float fHbargraph6;
	float fHslider3;
	float fHbargraph7;
	float fCheckbox4;
	float fCheckbox5;
	float fCheckbox6;
	float fHbargraph8;
	float fHslider4;
	float fHbargraph9;
	float fCheckbox7;
	float fHbargraph10;
	float fHslider5;
	float fHbargraph11;
	float fHslider6;
	float fHbargraph12;
	float fCheckbox8;
	float fHbargraph13;
	int iConst0;
	int fSamplingFreq;
	
	public void metadata(Meta m) { 
		m.declare("author", "Vincent Rateau, GRAME");
		m.declare("license", "GPL v3");
		m.declare("name", "midiTester");
		m.declare("reference", "www.sonejo.net");
		m.declare("version", "1.0");
	}

	int getNumInputs() {
		return 1;
		
	}
	int getNumOutputs() {
		return 1;
		
	}
	int getInputRate(int channel) {
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
	int getOutputRate(int channel) {
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
	
	public void classInit(int samplingFreq) {
		
	}
	
	public void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		iConst0 = 0;
		
	}
	
	public void instanceResetUserInterface() {
		fCheckbox0 = (float)0.0f;
		fHslider0 = (float)0.0f;
		fCheckbox1 = (float)0.0f;
		fHslider1 = (float)60.0f;
		fCheckbox2 = (float)0.0f;
		fHslider2 = (float)60.0f;
		fCheckbox3 = (float)0.0f;
		fHslider3 = (float)60.0f;
		fCheckbox4 = (float)0.0f;
		fCheckbox5 = (float)0.0f;
		fCheckbox6 = (float)0.0f;
		fHslider4 = (float)60.0f;
		fCheckbox7 = (float)0.0f;
		fHslider5 = (float)60.0f;
		fHslider6 = (float)60.0f;
		fCheckbox8 = (float)0.0f;
		
	}
	
	public void instanceClear() {
		
	}
	
	public void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	
	public void instanceInit(int samplingFreq) {
		instanceConstants(samplingFreq);
		instanceResetUserInterface();
		instanceClear();
	}
	
	public void buildUserInterface(UI ui_interface) {
		ui_interface.openVerticalBox("FAUST MIDI TESTER");
		ui_interface.declare("0", "1", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.openVerticalBox("CTRL IN/OUT");
		ui_interface.declare("fCheckbox8", "midi", "ctrl 100");
		ui_interface.addCheckButton("Ctrl Bool IN (Ctrl 100)", new FaustVarAccess() {
				public String getId() { return "fCheckbox8"; }
				public void set(float val) { fCheckbox8 = val; }
				public float get() { return (float)fCheckbox8; }
			}
			);
		ui_interface.declare("fHbargraph13", "midi", "ctrl 101");
		ui_interface.addHorizontalBargraph("Ctrl Bool OUT (Ctrl 101)", new FaustVarAccess() {
				public String getId() { return "fHbargraph13"; }
				public void set(float val) { fHbargraph13 = val; }
				public float get() { return (float)fHbargraph13; }
			}
			, 0.0f, 1.0f);
		ui_interface.declare("fHslider6", "midi", "ctrl 50");
		ui_interface.addHorizontalSlider("Ctrl Value IN (Ctrl 50)", new FaustVarAccess() {
				public String getId() { return "fHslider6"; }
				public void set(float val) { fHslider6 = val; }
				public float get() { return (float)fHslider6; }
			}
			, 60.0f, 0.0f, 127.0f, 1.0f);
		ui_interface.declare("fHbargraph12", "midi", "ctrl 51");
		ui_interface.addHorizontalBargraph("Ctrl Value OUT (Ctrl 51)", new FaustVarAccess() {
				public String getId() { return "fHbargraph12"; }
				public void set(float val) { fHbargraph12 = val; }
				public float get() { return (float)fHbargraph12; }
			}
			, 0.0f, 127.0f);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("MIDI SYNC (IN)");
		ui_interface.declare("fCheckbox4", "midi", "start");
		ui_interface.declare("fCheckbox4", "midi", "stop");
		ui_interface.addCheckButton("MIDI START/STOP", new FaustVarAccess() {
				public String getId() { return "fCheckbox4"; }
				public void set(float val) { fCheckbox4 = val; }
				public float get() { return (float)fCheckbox4; }
			}
			);
		ui_interface.declare("fCheckbox5", "midi", "clock");
		ui_interface.addCheckButton("MIDI clock signal", new FaustVarAccess() {
				public String getId() { return "fCheckbox5"; }
				public void set(float val) { fCheckbox5 = val; }
				public float get() { return (float)fCheckbox5; }
			}
			);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("NOTE OFF IN/OUT");
		ui_interface.declare("fCheckbox6", "midi", "keyoff 100");
		ui_interface.addCheckButton("NoteOff Bool IN (Note 100)", new FaustVarAccess() {
				public String getId() { return "fCheckbox6"; }
				public void set(float val) { fCheckbox6 = val; }
				public float get() { return (float)fCheckbox6; }
			}
			);
		ui_interface.declare("fHbargraph8", "midi", "keyoff 101");
		ui_interface.addHorizontalBargraph("NoteOff Bool OUT (Note 101)", new FaustVarAccess() {
				public String getId() { return "fHbargraph8"; }
				public void set(float val) { fHbargraph8 = val; }
				public float get() { return (float)fHbargraph8; }
			}
			, 0.0f, 1.0f);
		ui_interface.declare("fHslider4", "midi", "keyoff 50");
		ui_interface.addHorizontalSlider("NoteOff Value IN (Note 50)", new FaustVarAccess() {
				public String getId() { return "fHslider4"; }
				public void set(float val) { fHslider4 = val; }
				public float get() { return (float)fHslider4; }
			}
			, 60.0f, 0.0f, 127.0f, 1.0f);
		ui_interface.declare("fHbargraph9", "midi", "keyoff 51");
		ui_interface.addHorizontalBargraph("NoteOff Value OUT (Note 51)", new FaustVarAccess() {
				public String getId() { return "fHbargraph9"; }
				public void set(float val) { fHbargraph9 = val; }
				public float get() { return (float)fHbargraph9; }
			}
			, 0.0f, 127.0f);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("NOTE ON IN/OUT");
		ui_interface.declare("fCheckbox7", "midi", "keyon 100");
		ui_interface.addCheckButton("NoteOn Bool IN (Note 100)", new FaustVarAccess() {
				public String getId() { return "fCheckbox7"; }
				public void set(float val) { fCheckbox7 = val; }
				public float get() { return (float)fCheckbox7; }
			}
			);
		ui_interface.declare("fHbargraph10", "midi", "keyon 101");
		ui_interface.addHorizontalBargraph("NoteOn Bool OUT (Note 101)", new FaustVarAccess() {
				public String getId() { return "fHbargraph10"; }
				public void set(float val) { fHbargraph10 = val; }
				public float get() { return (float)fHbargraph10; }
			}
			, 0.0f, 1.0f);
		ui_interface.declare("fHslider5", "midi", "keyon 50");
		ui_interface.addHorizontalSlider("NoteOn Value IN (Note 50)", new FaustVarAccess() {
				public String getId() { return "fHslider5"; }
				public void set(float val) { fHslider5 = val; }
				public float get() { return (float)fHslider5; }
			}
			, 60.0f, 0.0f, 127.0f, 1.0f);
		ui_interface.declare("fHbargraph11", "midi", "keyon 51");
		ui_interface.addHorizontalBargraph("NoteOn Value OUT (Note 51)", new FaustVarAccess() {
				public String getId() { return "fHbargraph11"; }
				public void set(float val) { fHbargraph11 = val; }
				public float get() { return (float)fHbargraph11; }
			}
			, 0.0f, 127.0f);
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.declare("0", "2", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.openVerticalBox("CHANNEL AFTERTOUCH (CHAT) IN/OUT");
		ui_interface.declare("fCheckbox1", "midi", "chanpress 100");
		ui_interface.addCheckButton("Note CHAT Bool IN (Note 100)", new FaustVarAccess() {
				public String getId() { return "fCheckbox1"; }
				public void set(float val) { fCheckbox1 = val; }
				public float get() { return (float)fCheckbox1; }
			}
			);
		ui_interface.declare("fHbargraph2", "midi", "chanpress 101");
		ui_interface.addHorizontalBargraph("Note CHAT Bool OUT (Note 101)", new FaustVarAccess() {
				public String getId() { return "fHbargraph2"; }
				public void set(float val) { fHbargraph2 = val; }
				public float get() { return (float)fHbargraph2; }
			}
			, 0.0f, 1.0f);
		ui_interface.declare("fHslider1", "midi", "chanpress 50");
		ui_interface.addHorizontalSlider("Note CHAT Value IN (Note 50)", new FaustVarAccess() {
				public String getId() { return "fHslider1"; }
				public void set(float val) { fHslider1 = val; }
				public float get() { return (float)fHslider1; }
			}
			, 60.0f, 0.0f, 127.0f, 1.0f);
		ui_interface.declare("fHbargraph3", "midi", "chanpress 51");
		ui_interface.addHorizontalBargraph("Note CHAT Value OUT (Note 51)", new FaustVarAccess() {
				public String getId() { return "fHbargraph3"; }
				public void set(float val) { fHbargraph3 = val; }
				public float get() { return (float)fHbargraph3; }
			}
			, 0.0f, 127.0f);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("KEY AFTERTOUCH (KAT) IN/OUT");
		ui_interface.declare("fCheckbox3", "midi", "keypress 100");
		ui_interface.addCheckButton("Note KAT Bool IN (Note 100)", new FaustVarAccess() {
				public String getId() { return "fCheckbox3"; }
				public void set(float val) { fCheckbox3 = val; }
				public float get() { return (float)fCheckbox3; }
			}
			);
		ui_interface.declare("fHbargraph6", "midi", "keypress 101");
		ui_interface.addHorizontalBargraph("Note KAT Bool OUT (Note 101)", new FaustVarAccess() {
				public String getId() { return "fHbargraph6"; }
				public void set(float val) { fHbargraph6 = val; }
				public float get() { return (float)fHbargraph6; }
			}
			, 0.0f, 1.0f);
		ui_interface.declare("fHslider3", "midi", "keypress 50");
		ui_interface.addHorizontalSlider("Note KAT Value IN (Note 50)", new FaustVarAccess() {
				public String getId() { return "fHslider3"; }
				public void set(float val) { fHslider3 = val; }
				public float get() { return (float)fHslider3; }
			}
			, 60.0f, 0.0f, 127.0f, 1.0f);
		ui_interface.declare("fHbargraph7", "midi", "keypress 51");
		ui_interface.addHorizontalBargraph("Note KAT Value OUT (Note 51)", new FaustVarAccess() {
				public String getId() { return "fHbargraph7"; }
				public void set(float val) { fHbargraph7 = val; }
				public float get() { return (float)fHbargraph7; }
			}
			, 0.0f, 127.0f);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("PITCHWHEEL IN/OUT");
		ui_interface.declare("fCheckbox0", "midi", "pitchwheel");
		ui_interface.addCheckButton("Pitchwheel Bool IN", new FaustVarAccess() {
				public String getId() { return "fCheckbox0"; }
				public void set(float val) { fCheckbox0 = val; }
				public float get() { return (float)fCheckbox0; }
			}
			);
		ui_interface.declare("fHbargraph0", "midi", "pitchwheel");
		ui_interface.addHorizontalBargraph("Pitchwheel Bool OUT", new FaustVarAccess() {
				public String getId() { return "fHbargraph0"; }
				public void set(float val) { fHbargraph0 = val; }
				public float get() { return (float)fHbargraph0; }
			}
			, 0.0f, 1.0f);
		ui_interface.declare("fHslider0", "midi", "pitchwheel");
		ui_interface.addHorizontalSlider("Pitchwheel Value IN", new FaustVarAccess() {
				public String getId() { return "fHslider0"; }
				public void set(float val) { fHslider0 = val; }
				public float get() { return (float)fHslider0; }
			}
			, 0.0f, -8192.0f, 8191.0f, 1.0f);
		ui_interface.declare("fHbargraph1", "midi", "pitchwheel");
		ui_interface.addHorizontalBargraph("Pitchwheel Value OUT", new FaustVarAccess() {
				public String getId() { return "fHbargraph1"; }
				public void set(float val) { fHbargraph1 = val; }
				public float get() { return (float)fHbargraph1; }
			}
			, -8192.0f, 8191.0f);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("PROGRAM CHANGE (PC) IN/OUT");
		ui_interface.declare("fCheckbox2", "midi", "pgm 100");
		ui_interface.addCheckButton("ProgramChange Bool IN (PC 100)", new FaustVarAccess() {
				public String getId() { return "fCheckbox2"; }
				public void set(float val) { fCheckbox2 = val; }
				public float get() { return (float)fCheckbox2; }
			}
			);
		ui_interface.declare("fHbargraph4", "midi", "pgm 101");
		ui_interface.addHorizontalBargraph("ProgramChange Bool OUT (PC 101)", new FaustVarAccess() {
				public String getId() { return "fHbargraph4"; }
				public void set(float val) { fHbargraph4 = val; }
				public float get() { return (float)fHbargraph4; }
			}
			, 0.0f, 1.0f);
		ui_interface.declare("fHslider2", "midi", "pgm 50");
		ui_interface.addHorizontalSlider("ProgramChange Value IN (PC 50)", new FaustVarAccess() {
				public String getId() { return "fHslider2"; }
				public void set(float val) { fHslider2 = val; }
				public float get() { return (float)fHslider2; }
			}
			, 60.0f, 0.0f, 127.0f, 1.0f);
		ui_interface.declare("fHbargraph5", "midi", "pgm 51");
		ui_interface.addHorizontalBargraph("ProgramChange Value OUT (PC 51)", new FaustVarAccess() {
				public String getId() { return "fHbargraph5"; }
				public void set(float val) { fHbargraph5 = val; }
				public float get() { return (float)fHbargraph5; }
			}
			, 0.0f, 127.0f);
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] input0 = inputs[0];
		float[] output0 = outputs[0];
		fHbargraph0 = fCheckbox0;
		fHbargraph1 = fHslider0;
		fHbargraph2 = fCheckbox1;
		fHbargraph3 = fHslider1;
		fHbargraph4 = fCheckbox2;
		fHbargraph5 = fHslider2;
		fHbargraph6 = fCheckbox3;
		fHbargraph7 = fHslider3;
		fHbargraph8 = fCheckbox6;
		fHbargraph9 = fHslider4;
		fHbargraph10 = fCheckbox7;
		fHbargraph11 = fHslider5;
		fHbargraph12 = fHslider6;
		fHbargraph13 = fCheckbox8;
		for (int i = 0; (i < count); i = (i + 1)) {
			output0[i] = (float)iConst0;
			
		}
		
	}
	
};

