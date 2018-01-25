

function mydsp() {
	
	this.fCheckbox0;
	this.fHbargraph0;
	this.fHslider0;
	this.fHbargraph1;
	this.fCheckbox1;
	this.fHbargraph2;
	this.fHslider1;
	this.fHbargraph3;
	this.fCheckbox2;
	this.fHbargraph4;
	this.fHslider2;
	this.fHbargraph5;
	this.fCheckbox3;
	this.fHbargraph6;
	this.fHslider3;
	this.fHbargraph7;
	this.fCheckbox4;
	this.fCheckbox5;
	this.fCheckbox6;
	this.fHbargraph8;
	this.fHslider4;
	this.fHbargraph9;
	this.fCheckbox7;
	this.fHbargraph10;
	this.fHslider5;
	this.fHbargraph11;
	this.fHslider6;
	this.fHbargraph12;
	this.fCheckbox8;
	this.fHbargraph13;
	this.iConst0;
	this.fSamplingFreq;
	
	this.metadata = function(m) { 
		m.declare("author", "Vincent Rateau, GRAME");
		m.declare("license", "GPL v3");
		m.declare("name", "midiTester");
		m.declare("reference", "www.sonejo.net");
		m.declare("version", "1.0");
	}

	this.getNumInputs = function() {
		return 1;
		
	}
	this.getNumOutputs = function() {
		return 1;
		
	}
	this.getInputRate = function(channel) {
		var rate;
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
	this.getOutputRate = function(channel) {
		var rate;
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
	
	this.classInit = function(samplingFreq) {
		
	}
	
	this.instanceConstants = function(samplingFreq) {
		this.fSamplingFreq = samplingFreq;
		this.iConst0 = 0;
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fCheckbox0 = 0;
		this.fHslider0 = 0;
		this.fCheckbox1 = 0;
		this.fHslider1 = 60;
		this.fCheckbox2 = 0;
		this.fHslider2 = 60;
		this.fCheckbox3 = 0;
		this.fHslider3 = 60;
		this.fCheckbox4 = 0;
		this.fCheckbox5 = 0;
		this.fCheckbox6 = 0;
		this.fHslider4 = 60;
		this.fCheckbox7 = 0;
		this.fHslider5 = 60;
		this.fHslider6 = 60;
		this.fCheckbox8 = 0;
		
	}
	
	this.instanceClear = function() {
		
	}
	
	this.init = function(samplingFreq) {
		this.classInit(samplingFreq);
		this.instanceInit(samplingFreq);
	}
	
	this.instanceInit = function(samplingFreq) {
		this.instanceConstants(samplingFreq);
		this.instanceResetUserInterface();
		this.instanceClear();
	}
	
	this.buildUserInterface = function(ui_interface) {
		ui_interface.openVerticalBox("FAUST MIDI TESTER");
		ui_interface.declare("0", "1", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.openVerticalBox("CTRL IN/OUT");
		ui_interface.declare("fCheckbox8", "midi", "ctrl 100");
		ui_interface.addCheckButton("Ctrl Bool IN (Ctrl 100)", function handler(obj) { function setval(val) { obj.fCheckbox8 = val; } return setval; }(this));
		ui_interface.declare("fHbargraph13", "midi", "ctrl 101");
		ui_interface.addHorizontalBargraph("Ctrl Bool OUT (Ctrl 101)", function handler(obj) { function setval(val) { obj.fHbargraph13 = val; } return setval; }(this), 0, 1);
		ui_interface.declare("fHslider6", "midi", "ctrl 50");
		ui_interface.addHorizontalSlider("Ctrl Value IN (Ctrl 50)", function handler(obj) { function setval(val) { obj.fHslider6 = val; } return setval; }(this), 60, 0, 127, 1);
		ui_interface.declare("fHbargraph12", "midi", "ctrl 51");
		ui_interface.addHorizontalBargraph("Ctrl Value OUT (Ctrl 51)", function handler(obj) { function setval(val) { obj.fHbargraph12 = val; } return setval; }(this), 0, 127);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("MIDI SYNC (IN)");
		ui_interface.declare("fCheckbox4", "midi", "start");
		ui_interface.declare("fCheckbox4", "midi", "stop");
		ui_interface.addCheckButton("MIDI START/STOP", function handler(obj) { function setval(val) { obj.fCheckbox4 = val; } return setval; }(this));
		ui_interface.declare("fCheckbox5", "midi", "clock");
		ui_interface.addCheckButton("MIDI clock signal", function handler(obj) { function setval(val) { obj.fCheckbox5 = val; } return setval; }(this));
		ui_interface.closeBox();
		ui_interface.openVerticalBox("NOTE OFF IN/OUT");
		ui_interface.declare("fCheckbox6", "midi", "keyoff 100");
		ui_interface.addCheckButton("NoteOff Bool IN (Note 100)", function handler(obj) { function setval(val) { obj.fCheckbox6 = val; } return setval; }(this));
		ui_interface.declare("fHbargraph8", "midi", "keyoff 101");
		ui_interface.addHorizontalBargraph("NoteOff Bool OUT (Note 101)", function handler(obj) { function setval(val) { obj.fHbargraph8 = val; } return setval; }(this), 0, 1);
		ui_interface.declare("fHslider4", "midi", "keyoff 50");
		ui_interface.addHorizontalSlider("NoteOff Value IN (Note 50)", function handler(obj) { function setval(val) { obj.fHslider4 = val; } return setval; }(this), 60, 0, 127, 1);
		ui_interface.declare("fHbargraph9", "midi", "keyoff 51");
		ui_interface.addHorizontalBargraph("NoteOff Value OUT (Note 51)", function handler(obj) { function setval(val) { obj.fHbargraph9 = val; } return setval; }(this), 0, 127);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("NOTE ON IN/OUT");
		ui_interface.declare("fCheckbox7", "midi", "keyon 100");
		ui_interface.addCheckButton("NoteOn Bool IN (Note 100)", function handler(obj) { function setval(val) { obj.fCheckbox7 = val; } return setval; }(this));
		ui_interface.declare("fHbargraph10", "midi", "keyon 101");
		ui_interface.addHorizontalBargraph("NoteOn Bool OUT (Note 101)", function handler(obj) { function setval(val) { obj.fHbargraph10 = val; } return setval; }(this), 0, 1);
		ui_interface.declare("fHslider5", "midi", "keyon 50");
		ui_interface.addHorizontalSlider("NoteOn Value IN (Note 50)", function handler(obj) { function setval(val) { obj.fHslider5 = val; } return setval; }(this), 60, 0, 127, 1);
		ui_interface.declare("fHbargraph11", "midi", "keyon 51");
		ui_interface.addHorizontalBargraph("NoteOn Value OUT (Note 51)", function handler(obj) { function setval(val) { obj.fHbargraph11 = val; } return setval; }(this), 0, 127);
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.declare("0", "2", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.openVerticalBox("CHANNEL AFTERTOUCH (CHAT) IN/OUT");
		ui_interface.declare("fCheckbox1", "midi", "chanpress 100");
		ui_interface.addCheckButton("Note CHAT Bool IN (Note 100)", function handler(obj) { function setval(val) { obj.fCheckbox1 = val; } return setval; }(this));
		ui_interface.declare("fHbargraph2", "midi", "chanpress 101");
		ui_interface.addHorizontalBargraph("Note CHAT Bool OUT (Note 101)", function handler(obj) { function setval(val) { obj.fHbargraph2 = val; } return setval; }(this), 0, 1);
		ui_interface.declare("fHslider1", "midi", "chanpress 50");
		ui_interface.addHorizontalSlider("Note CHAT Value IN (Note 50)", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 60, 0, 127, 1);
		ui_interface.declare("fHbargraph3", "midi", "chanpress 51");
		ui_interface.addHorizontalBargraph("Note CHAT Value OUT (Note 51)", function handler(obj) { function setval(val) { obj.fHbargraph3 = val; } return setval; }(this), 0, 127);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("KEY AFTERTOUCH (KAT) IN/OUT");
		ui_interface.declare("fCheckbox3", "midi", "keypress 100");
		ui_interface.addCheckButton("Note KAT Bool IN (Note 100)", function handler(obj) { function setval(val) { obj.fCheckbox3 = val; } return setval; }(this));
		ui_interface.declare("fHbargraph6", "midi", "keypress 101");
		ui_interface.addHorizontalBargraph("Note KAT Bool OUT (Note 101)", function handler(obj) { function setval(val) { obj.fHbargraph6 = val; } return setval; }(this), 0, 1);
		ui_interface.declare("fHslider3", "midi", "keypress 50");
		ui_interface.addHorizontalSlider("Note KAT Value IN (Note 50)", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 60, 0, 127, 1);
		ui_interface.declare("fHbargraph7", "midi", "keypress 51");
		ui_interface.addHorizontalBargraph("Note KAT Value OUT (Note 51)", function handler(obj) { function setval(val) { obj.fHbargraph7 = val; } return setval; }(this), 0, 127);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("PITCHWHEEL IN/OUT");
		ui_interface.declare("fCheckbox0", "midi", "pitchwheel");
		ui_interface.addCheckButton("Pitchwheel Bool IN", function handler(obj) { function setval(val) { obj.fCheckbox0 = val; } return setval; }(this));
		ui_interface.declare("fHbargraph0", "midi", "pitchwheel");
		ui_interface.addHorizontalBargraph("Pitchwheel Bool OUT", function handler(obj) { function setval(val) { obj.fHbargraph0 = val; } return setval; }(this), 0, 1);
		ui_interface.declare("fHslider0", "midi", "pitchwheel");
		ui_interface.addHorizontalSlider("Pitchwheel Value IN", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0, -8192, 8191, 1);
		ui_interface.declare("fHbargraph1", "midi", "pitchwheel");
		ui_interface.addHorizontalBargraph("Pitchwheel Value OUT", function handler(obj) { function setval(val) { obj.fHbargraph1 = val; } return setval; }(this), -8192, 8191);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("PROGRAM CHANGE (PC) IN/OUT");
		ui_interface.declare("fCheckbox2", "midi", "pgm 100");
		ui_interface.addCheckButton("ProgramChange Bool IN (PC 100)", function handler(obj) { function setval(val) { obj.fCheckbox2 = val; } return setval; }(this));
		ui_interface.declare("fHbargraph4", "midi", "pgm 101");
		ui_interface.addHorizontalBargraph("ProgramChange Bool OUT (PC 101)", function handler(obj) { function setval(val) { obj.fHbargraph4 = val; } return setval; }(this), 0, 1);
		ui_interface.declare("fHslider2", "midi", "pgm 50");
		ui_interface.addHorizontalSlider("ProgramChange Value IN (PC 50)", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 60, 0, 127, 1);
		ui_interface.declare("fHbargraph5", "midi", "pgm 51");
		ui_interface.addHorizontalBargraph("ProgramChange Value OUT (PC 51)", function handler(obj) { function setval(val) { obj.fHbargraph5 = val; } return setval; }(this), 0, 127);
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var output0 = outputs[0];
		this.fHbargraph0 = this.fCheckbox0;
		this.fHbargraph1 = this.fHslider0;
		this.fHbargraph2 = this.fCheckbox1;
		this.fHbargraph3 = this.fHslider1;
		this.fHbargraph4 = this.fCheckbox2;
		this.fHbargraph5 = this.fHslider2;
		this.fHbargraph6 = this.fCheckbox3;
		this.fHbargraph7 = this.fHslider3;
		this.fHbargraph8 = this.fCheckbox6;
		this.fHbargraph9 = this.fHslider4;
		this.fHbargraph10 = this.fCheckbox7;
		this.fHbargraph11 = this.fHslider5;
		this.fHbargraph12 = this.fHslider6;
		this.fHbargraph13 = this.fCheckbox8;
		for (var i = 0; (i < count); i = (i + 1)) {
			output0[i] = this.iConst0;
			
		}
		
	}
	
}

