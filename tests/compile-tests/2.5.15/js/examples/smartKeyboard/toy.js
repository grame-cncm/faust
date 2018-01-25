
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.mydsp_faustpower2_f = function(value) {
	return (value * value);
	
}

function mydsp() {
	
	this.fHslider0;
	this.fRec1 = new Float32Array(2);
	this.fSamplingFreq;
	this.fConst0;
	this.fHslider1;
	this.fRec2 = new Float32Array(2);
	this.fConst1;
	this.fHslider2;
	this.fRec5 = new Float32Array(2);
	this.fVec0 = new Float32Array(2);
	this.fRec4 = new Float32Array(2);
	this.fConst2;
	this.fHslider3;
	this.fRec6 = new Float32Array(2);
	this.fHslider4;
	this.fRec7 = new Float32Array(2);
	this.fRec3 = new Float32Array(3);
	this.IOTA;
	this.fRec0 = new Float32Array(131072);
	this.fHslider5;
	this.fRec8 = new Float32Array(2);
	
	this.metadata = function(m) { 
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("interface", "SmartKeyboard{  'Number of Keyboards':'1',  'Max Keyboard Polyphony':'0',  'Keyboard 0 - Number of Keys':'1',  'Keyboard 0 - Send Freq':'0',  'Keyboard 0 - Static Mode':'1',  'Keyboard 0 - Piano Keyboard':'0',  'Keyboard 0 - Send Numbered X':'1',  'Keyboard 0 - Send Numbered Y':'1' }");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("misceffects.lib/name", "Faust Math Library");
		m.declare("misceffects.lib/version", "2.0");
		m.declare("name", "toy");
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
		this.fConst1 = (1 / this.fConst0);
		this.fConst2 = (3.14159 / this.fConst0);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 0.5;
		this.fHslider1 = 0.5;
		this.fHslider2 = 0.5;
		this.fHslider3 = 0.5;
		this.fHslider4 = 30;
		this.fHslider5 = 0;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.fRec1[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec2[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec5[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fVec0[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec4[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fRec6[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			this.fRec7[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			this.fRec3[l7] = 0;
			
		}
		this.IOTA = 0;
		for (var l8 = 0; (l8 < 131072); l8 = (l8 + 1)) {
			this.fRec0[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			this.fRec8[l9] = 0;
			
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
		ui_interface.openVerticalBox("toy");
		ui_interface.declare("fHslider1", "acc", "0 0 -10 0 10");
		ui_interface.addHorizontalSlider("del", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 0.5, 0.01, 1, 0.01);
		ui_interface.declare("fHslider0", "acc", "1 0 -10 0 10");
		ui_interface.addHorizontalSlider("fb", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.declare("fHslider4", "acc", "0 0 -10 0 10");
		ui_interface.addHorizontalSlider("q", function handler(obj) { function setval(val) { obj.fHslider4 = val; } return setval; }(this), 30, 10, 50, 0.01);
		ui_interface.addHorizontalSlider("x0", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.addHorizontalSlider("y0", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.addHorizontalSlider("y1", function handler(obj) { function setval(val) { obj.fHslider5 = val; } return setval; }(this), 0, 0, 1, 0.01);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = (0.001 * this.fHslider0);
		var fSlow1 = (0.001 * this.fHslider1);
		var fSlow2 = (0.001 * this.fHslider2);
		var fSlow3 = (0.001 * this.fHslider3);
		var fSlow4 = (0.001 * this.fHslider4);
		var fSlow5 = (0.001 * this.fHslider5);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.fRec1[0] = (fSlow0 + (0.999 * this.fRec1[1]));
			this.fRec2[0] = (fSlow1 + (0.999 * this.fRec2[1]));
			this.fRec5[0] = (fSlow2 + (0.999 * this.fRec5[1]));
			this.fVec0[0] = ((20 * this.fRec5[0]) + 2);
			var fTemp0 = (this.fRec4[1] + (this.fConst1 * this.fVec0[1]));
			this.fRec4[0] = (fTemp0 - Math.floor(fTemp0));
			this.fRec6[0] = (fSlow3 + (0.999 * this.fRec6[1]));
			var fTemp1 = Math.tan((this.fConst2 * ((3000 * this.fRec6[0]) + 300)));
			var fTemp2 = (1 / fTemp1);
			this.fRec7[0] = (fSlow4 + (0.999 * this.fRec7[1]));
			var fTemp3 = (1 / this.fRec7[0]);
			var fTemp4 = (((fTemp2 + fTemp3) / fTemp1) + 1);
			this.fRec3[0] = (((this.fRec4[0] - this.fRec4[1]) < 0) - (((this.fRec3[2] * (((fTemp2 - fTemp3) / fTemp1) + 1)) + (2 * (this.fRec3[1] * (1 - (1 / mydsp_faustpower2_f(fTemp1)))))) / fTemp4));
			this.fRec0[(this.IOTA & 131071)] = ((this.fRec1[0] * this.fRec0[((this.IOTA - (min_f(65536, max_f(0, (this.fConst0 * this.fRec2[0]))) + 1)) & 131071)]) + ((this.fRec3[2] + (this.fRec3[0] + (2 * this.fRec3[1]))) / fTemp4));
			this.fRec8[0] = (fSlow5 + (0.999 * this.fRec8[1]));
			var fTemp5 = max_f(-1, min_f(1, (this.fRec0[((this.IOTA - 0) & 131071)] * Math.pow(10, (2 * this.fRec8[0])))));
			var fTemp6 = (0.95 * (fTemp5 * (1 - (0.333333 * mydsp_faustpower2_f(fTemp5)))));
			output0[i] = fTemp6;
			output1[i] = fTemp6;
			this.fRec1[1] = this.fRec1[0];
			this.fRec2[1] = this.fRec2[0];
			this.fRec5[1] = this.fRec5[0];
			this.fVec0[1] = this.fVec0[0];
			this.fRec4[1] = this.fRec4[0];
			this.fRec6[1] = this.fRec6[0];
			this.fRec7[1] = this.fRec7[0];
			this.fRec3[2] = this.fRec3[1];
			this.fRec3[1] = this.fRec3[0];
			this.IOTA = (this.IOTA + 1);
			this.fRec8[1] = this.fRec8[0];
			
		}
		
	}
	
}

