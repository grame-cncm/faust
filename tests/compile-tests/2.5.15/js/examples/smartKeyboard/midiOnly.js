
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);

function mydsp() {
	
	this.iVec0 = new Int32Array(2);
	this.fSamplingFreq;
	this.fConst0;
	this.fHslider0;
	this.fHslider1;
	this.fButton0;
	this.fHslider2;
	this.fVec1 = new Float32Array(2);
	this.fRec2 = new Float32Array(2);
	this.fHslider3;
	this.fRec5 = new Float32Array(2);
	this.fRec3 = new Float32Array(2);
	this.fRec4 = new Float32Array(2);
	this.fHslider4;
	this.fRec6 = new Float32Array(2);
	this.fHslider5;
	this.fRec7 = new Float32Array(2);
	this.fRec0 = new Float32Array(2);
	this.fRec1 = new Float32Array(2);
	this.fRec8 = new Float32Array(2);
	
	this.metadata = function(m) { 
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("interface", "SmartKeyboard{  'Number of Keyboards':'1',  'Keyboard 0 - Number of Keys':'2',  'Keyboard 0 - Send Freq':'0',  'Keyboard 0 - Piano Keyboard':'0',  'Keyboard 0 - Static Mode':'1',  'Keyboard 0 - Send Key X':'1',  'Keyboard 0 - Key 0 - Label':'Mod Index',  'Keyboard 0 - Key 1 - Label':'Mod Freq' }");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "midiOnly");
		m.declare("oscillators.lib/name", "Faust Oscillator Library");
		m.declare("oscillators.lib/version", "0.0");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
		m.declare("synths.lib/name", "Faust Synthesizer Library");
		m.declare("synths.lib/version", "0.0");
	}

	this.getNumInputs = function() {
		return 0;
		
	}
	this.getNumOutputs = function() {
		return 2;
		
	}
	this.getInputRate = function(channel) {
		var rate;
		switch (channel) {
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
	
	this.classInit = function(samplingFreq) {
		
	}
	
	this.instanceConstants = function(samplingFreq) {
		this.fSamplingFreq = samplingFreq;
		this.fConst0 = (6.28319 / min_f(192000, max_f(1, this.fSamplingFreq)));
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 300;
		this.fHslider1 = 1;
		this.fButton0 = 0;
		this.fHslider2 = 0;
		this.fHslider3 = 0.5;
		this.fHslider4 = 0.5;
		this.fHslider5 = 1;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.iVec0[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fVec1[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec2[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec5[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec3[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fRec4[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			this.fRec6[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			this.fRec7[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			this.fRec0[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			this.fRec1[l9] = 0;
			
		}
		for (var l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			this.fRec8[l10] = 0;
			
		}
		
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
		ui_interface.openVerticalBox("midiOnly");
		ui_interface.declare("fHslider1", "midi", "pitchwheel");
		ui_interface.addHorizontalSlider("bend", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 1, 0, 10, 0.01);
		ui_interface.addHorizontalSlider("freq", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 300, 50, 2000, 0.01);
		ui_interface.addHorizontalSlider("gain", function handler(obj) { function setval(val) { obj.fHslider5 = val; } return setval; }(this), 1, 0, 1, 0.01);
		ui_interface.addButton("gate", function handler(obj) { function setval(val) { obj.fButton0 = val; } return setval; }(this));
		ui_interface.declare("fHslider4", "midi", "ctrl 1");
		ui_interface.addHorizontalSlider("kb0k0x", function handler(obj) { function setval(val) { obj.fHslider4 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.declare("fHslider3", "midi", "ctrl 1");
		ui_interface.addHorizontalSlider("kb0k1x", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.declare("fHslider2", "midi", "ctrl 64");
		ui_interface.addHorizontalSlider("sustain", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 0, 0, 1, 1);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = this.fHslider0;
		var fSlow1 = this.fHslider1;
		var fSlow2 = min_f(1, (this.fButton0 + this.fHslider2));
		var iSlow3 = (fSlow2 == 0);
		var fSlow4 = (this.fConst0 * fSlow0);
		var fSlow5 = (0.001 * this.fHslider3);
		var fSlow6 = (0.001 * this.fHslider4);
		var fSlow7 = (0.001 * (fSlow2 * this.fHslider5));
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iVec0[0] = 1;
			this.fVec1[0] = fSlow2;
			var iTemp0 = ((fSlow2 == this.fVec1[1]) | iSlow3);
			this.fRec2[0] = ((fSlow1 * (1 - (0.999 * iTemp0))) + (0.999 * (iTemp0 * this.fRec2[1])));
			this.fRec5[0] = (fSlow5 + (0.999 * this.fRec5[1]));
			var fTemp1 = (fSlow4 * (this.fRec2[0] * (this.fRec5[0] + 1)));
			var fTemp2 = Math.sin(fTemp1);
			var fTemp3 = Math.cos(fTemp1);
			this.fRec3[0] = ((this.fRec4[1] * fTemp2) + (this.fRec3[1] * fTemp3));
			var iTemp4 = (1 - this.iVec0[1]);
			this.fRec4[0] = (((this.fRec4[1] * fTemp3) + (this.fRec3[1] * (0 - fTemp2))) + iTemp4);
			this.fRec6[0] = (fSlow6 + (0.999 * this.fRec6[1]));
			this.fRec7[0] = (fSlow7 + (0.999 * this.fRec7[1]));
			var fTemp5 = (this.fConst0 * ((fSlow0 * this.fRec2[0]) + (1000 * ((this.fRec3[0] * this.fRec6[0]) * this.fRec7[0]))));
			var fTemp6 = Math.sin(fTemp5);
			var fTemp7 = Math.cos(fTemp5);
			this.fRec0[0] = ((this.fRec1[1] * fTemp6) + (this.fRec0[1] * fTemp7));
			this.fRec1[0] = (((this.fRec1[1] * fTemp7) + (this.fRec0[1] * (0 - fTemp6))) + iTemp4);
			this.fRec8[0] = (fSlow7 + (0.999 * this.fRec8[1]));
			var fTemp8 = (this.fRec0[0] * this.fRec8[0]);
			output0[i] = fTemp8;
			output1[i] = fTemp8;
			this.iVec0[1] = this.iVec0[0];
			this.fVec1[1] = this.fVec1[0];
			this.fRec2[1] = this.fRec2[0];
			this.fRec5[1] = this.fRec5[0];
			this.fRec3[1] = this.fRec3[0];
			this.fRec4[1] = this.fRec4[0];
			this.fRec6[1] = this.fRec6[0];
			this.fRec7[1] = this.fRec7[0];
			this.fRec0[1] = this.fRec0[0];
			this.fRec1[1] = this.fRec1[0];
			this.fRec8[1] = this.fRec8[0];
			
		}
		
	}
	
}

