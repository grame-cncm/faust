
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.mydsp_faustpower2_f = function(value) {
	return (value * value);
	
}

function mydsp() {
	
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fConst2;
	this.fButton0;
	this.fVec0 = new Float32Array(2);
	this.fRec1 = new Float32Array(2);
	this.fConst3;
	this.fHslider0;
	this.fRec4 = new Float32Array(2);
	this.fRec2 = new Float32Array(2);
	this.fConst4;
	this.fHslider1;
	this.fRec5 = new Float32Array(2);
	this.fHslider2;
	this.fRec6 = new Float32Array(2);
	this.fRec0 = new Float32Array(3);
	
	this.metadata = function(m) { 
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("envelopes.lib/author", "GRAME");
		m.declare("envelopes.lib/copyright", "GRAME");
		m.declare("envelopes.lib/license", "LGPL with exception");
		m.declare("envelopes.lib/name", "Faust Envelope Library");
		m.declare("envelopes.lib/version", "0.0");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("interface", "SmartKeyboard{  'Number of Keyboards':'1',  'Keyboard 0 - Number of Keys':'1',  'Keyboard 0 - Piano Keyboard':'0',  'Keyboard 0 - Static Mode':'1',  'Keyboard 0 - Send X':'1',  'Keyboard 0 - Send Y':'1' }");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "frog");
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
		this.fConst0 = min_f(192000, max_f(1, this.fSamplingFreq));
		this.fConst1 = Math.exp((0 - (100 / this.fConst0)));
		this.fConst2 = (1 - this.fConst1);
		this.fConst3 = (1 / this.fConst0);
		this.fConst4 = (3.14159 / this.fConst0);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fButton0 = 0;
		this.fHslider0 = 0;
		this.fHslider1 = 2500;
		this.fHslider2 = 0;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.fVec0[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec1[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec4[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec2[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec5[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fRec6[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 3); l6 = (l6 + 1)) {
			this.fRec0[l6] = 0;
			
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
		ui_interface.openVerticalBox("frog");
		ui_interface.declare("fHslider1", "acc", "0 0 -10 0 10");
		ui_interface.addHorizontalSlider("cutoff", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 2500, 50, 5000, 0.01);
		ui_interface.addButton("gate", function handler(obj) { function setval(val) { obj.fButton0 = val; } return setval; }(this));
		ui_interface.addHorizontalSlider("x", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0, 0, 1, 0.01);
		ui_interface.addHorizontalSlider("y", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 0, 0, 1, 0.01);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = this.fButton0;
		var fSlow1 = (this.fConst2 * fSlow0);
		var fSlow2 = ((99 * this.fHslider0) + 1);
		var iSlow3 = (fSlow0 == 0);
		var fSlow4 = (0.001 * this.fHslider1);
		var fSlow5 = (0.001 * ((39 * (1 - this.fHslider2)) + 1));
		for (var i = 0; (i < count); i = (i + 1)) {
			this.fVec0[0] = fSlow0;
			this.fRec1[0] = (fSlow1 + (this.fConst1 * this.fRec1[1]));
			var iTemp0 = ((fSlow0 == this.fVec0[1]) | iSlow3);
			this.fRec4[0] = ((fSlow2 * (1 - (0.999 * iTemp0))) + (0.999 * (iTemp0 * this.fRec4[1])));
			var fTemp1 = max_f(1e-07, Math.abs(this.fRec4[0]));
			var fTemp2 = (this.fRec2[1] + (this.fConst3 * fTemp1));
			var fTemp3 = (fTemp2 + -1);
			var iTemp4 = (fTemp3 < 0);
			this.fRec2[0] = (iTemp4?fTemp2:fTemp3);
			var fRec3 = (iTemp4?fTemp2:(fTemp2 + ((1 - (this.fConst0 / fTemp1)) * fTemp3)));
			this.fRec5[0] = (fSlow4 + (0.999 * this.fRec5[1]));
			var fTemp5 = Math.tan((this.fConst4 * this.fRec5[0]));
			var fTemp6 = (1 / fTemp5);
			this.fRec6[0] = (fSlow5 + (0.999 * this.fRec6[1]));
			var fTemp7 = (1 / this.fRec6[0]);
			var fTemp8 = (((fTemp6 + fTemp7) / fTemp5) + 1);
			this.fRec0[0] = ((0.5 * (this.fRec1[0] * ((2 * fRec3) + -1))) - (((this.fRec0[2] * (((fTemp6 - fTemp7) / fTemp5) + 1)) + (2 * (this.fRec0[1] * (1 - (1 / mydsp_faustpower2_f(fTemp5)))))) / fTemp8));
			var fTemp9 = ((this.fRec0[2] + (this.fRec0[0] + (2 * this.fRec0[1]))) / fTemp8);
			output0[i] = fTemp9;
			output1[i] = fTemp9;
			this.fVec0[1] = this.fVec0[0];
			this.fRec1[1] = this.fRec1[0];
			this.fRec4[1] = this.fRec4[0];
			this.fRec2[1] = this.fRec2[0];
			this.fRec5[1] = this.fRec5[0];
			this.fRec6[1] = this.fRec6[0];
			this.fRec0[2] = this.fRec0[1];
			this.fRec0[1] = this.fRec0[0];
			
		}
		
	}
	
}

