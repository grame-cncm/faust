
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.mydsp_faustpower2_f = function(value) {
	return (value * value);
	
}

function mydsp() {
	
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fHslider0;
	this.fRec2 = new Float32Array(2);
	this.fButton0;
	this.fHslider1;
	this.fVec0 = new Float32Array(2);
	this.fHslider2;
	this.fRec3 = new Float32Array(2);
	this.fConst2;
	this.fHslider3;
	this.fHslider4;
	this.fRec6 = new Float32Array(2);
	this.fRec4 = new Float32Array(2);
	this.fVec1 = new Float32Array(2);
	this.fRec1 = new Float32Array(2);
	this.fRec0 = new Float32Array(3);
	
	this.metadata = function(m) { 
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("interface", "SmartKeyboard{  'Number of Keyboards':'5',  'Max Keyboard Polyphony':'1',  'Mono Mode':'1',  'Keyboard 0 - Number of Keys':'13',  'Keyboard 1 - Number of Keys':'13',  'Keyboard 2 - Number of Keys':'13',  'Keyboard 3 - Number of Keys':'13',  'Keyboard 4 - Number of Keys':'13',  'Keyboard 0 - Lowest Key':'77',  'Keyboard 1 - Lowest Key':'72',  'Keyboard 2 - Lowest Key':'67',  'Keyboard 3 - Lowest Key':'62',  'Keyboard 4 - Lowest Key':'57',  'Rounding Mode':'2',  'Keyboard 0 - Send Y':'1',  'Keyboard 1 - Send Y':'1',  'Keyboard 2 - Send Y':'1',  'Keyboard 3 - Send Y':'1',  'Keyboard 4 - Send Y':'1', }");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "trumpet");
		m.declare("oscillators.lib/name", "Faust Oscillator Library");
		m.declare("oscillators.lib/version", "0.0");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
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
		this.fConst0 = min_f(192000, max_f(1, this.fSamplingFreq));
		this.fConst1 = (3.14159 / this.fConst0);
		this.fConst2 = (1 / this.fConst0);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 1;
		this.fButton0 = 0;
		this.fHslider1 = 0;
		this.fHslider2 = 1;
		this.fHslider3 = 300;
		this.fHslider4 = 1;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.fRec2[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fVec0[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec3[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec6[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec4[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fVec1[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			this.fRec1[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			this.fRec0[l7] = 0;
			
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
		ui_interface.openVerticalBox("trumpet");
		ui_interface.declare("fHslider4", "midi", "pitchwheel");
		ui_interface.addHorizontalSlider("bend", function handler(obj) { function setval(val) { obj.fHslider4 = val; } return setval; }(this), 1, 0, 10, 0.01);
		ui_interface.addHorizontalSlider("freq", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 300, 50, 2000, 0.01);
		ui_interface.addHorizontalSlider("gain", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 1, 0, 1, 0.01);
		ui_interface.addButton("gate", function handler(obj) { function setval(val) { obj.fButton0 = val; } return setval; }(this));
		ui_interface.declare("fHslider1", "midi", "ctrl 64");
		ui_interface.addHorizontalSlider("sustain", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 0, 0, 1, 1);
		ui_interface.declare("fHslider0", "midi", "ctrl 1");
		ui_interface.addHorizontalSlider("y", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 1, 0, 1, 0.001);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = (0.001 * this.fHslider0);
		var fSlow1 = min_f(1, (this.fButton0 + this.fHslider1));
		var fSlow2 = (0.001 * (fSlow1 * this.fHslider2));
		var fSlow3 = this.fHslider3;
		var fSlow4 = this.fHslider4;
		var iSlow5 = (fSlow1 == 0);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.fRec2[0] = (fSlow0 + (0.999 * this.fRec2[1]));
			var fTemp0 = Math.tan((this.fConst1 * ((4000 * this.fRec2[0]) + 50)));
			var fTemp1 = (1 / fTemp0);
			var fTemp2 = (fTemp1 + 1);
			this.fVec0[0] = fSlow1;
			this.fRec3[0] = (fSlow2 + (0.999 * this.fRec3[1]));
			var iTemp3 = ((fSlow1 == this.fVec0[1]) | iSlow5);
			this.fRec6[0] = ((fSlow4 * (1 - (0.999 * iTemp3))) + (0.999 * (iTemp3 * this.fRec6[1])));
			var fTemp4 = max_f(1e-07, Math.abs((fSlow3 * this.fRec6[0])));
			var fTemp5 = (this.fRec4[1] + (this.fConst2 * fTemp4));
			var fTemp6 = (fTemp5 + -1);
			var iTemp7 = (fTemp6 < 0);
			this.fRec4[0] = (iTemp7?fTemp5:fTemp6);
			var fRec5 = (iTemp7?fTemp5:(fTemp5 + ((1 - (this.fConst0 / fTemp4)) * fTemp6)));
			var fTemp8 = (this.fRec3[0] * ((2 * fRec5) + -1));
			this.fVec1[0] = fTemp8;
			this.fRec1[0] = ((this.fRec1[1] * (0 - ((1 - fTemp1) / fTemp2))) + ((fTemp8 + this.fVec1[1]) / fTemp2));
			var fTemp9 = (((fTemp1 + 1) / fTemp0) + 1);
			this.fRec0[0] = (this.fRec1[0] - (((this.fRec0[2] * (((fTemp1 + -1) / fTemp0) + 1)) + (2 * (this.fRec0[1] * (1 - (1 / mydsp_faustpower2_f(fTemp0)))))) / fTemp9));
			var fTemp10 = ((this.fRec0[2] + (this.fRec0[0] + (2 * this.fRec0[1]))) / fTemp9);
			output0[i] = fTemp10;
			output1[i] = fTemp10;
			this.fRec2[1] = this.fRec2[0];
			this.fVec0[1] = this.fVec0[0];
			this.fRec3[1] = this.fRec3[0];
			this.fRec6[1] = this.fRec6[0];
			this.fRec4[1] = this.fRec4[0];
			this.fVec1[1] = this.fVec1[0];
			this.fRec1[1] = this.fRec1[0];
			this.fRec0[2] = this.fRec0[1];
			this.fRec0[1] = this.fRec0[0];
			
		}
		
	}
	
}

