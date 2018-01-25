
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.max_i = function(dummy0, dummy1);
this.min_i = function(dummy0, dummy1);

function mydsp() {
	
	this.fSamplingFreq;
	this.fConst0;
	this.fVec0 = new Float32Array(2);
	this.fHslider0;
	this.fConst1;
	this.fHslider1;
	this.iRec2 = new Int32Array(2);
	this.fButton0;
	this.fVec1 = new Float32Array(2);
	this.fConst2;
	this.fRec3 = new Float32Array(2);
	this.fConst3;
	this.IOTA;
	this.fVec2 = new Float32Array(2048);
	this.fRec0 = new Float32Array(2);
	this.fRec1 = new Float32Array(2);
	
	this.metadata = function(m) { 
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("envelopes.lib/author", "GRAME");
		m.declare("envelopes.lib/copyright", "GRAME");
		m.declare("envelopes.lib/license", "LGPL with exception");
		m.declare("envelopes.lib/name", "Faust Envelope Library");
		m.declare("envelopes.lib/version", "0.0");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("interface", "SmartKeyboard{  'Number of Keyboards':'8',  'Keyboard 0 - Number of Keys':'16',  'Keyboard 1 - Number of Keys':'16',  'Keyboard 2 - Number of Keys':'16',  'Keyboard 3 - Number of Keys':'16',  'Keyboard 4 - Number of Keys':'16',  'Keyboard 5 - Number of Keys':'16',  'Keyboard 6 - Number of Keys':'16',  'Keyboard 7 - Number of Keys':'16',  'Keyboard 0 - Lowest Key':'40',  'Keyboard 1 - Lowest Key':'45',  'Keyboard 2 - Lowest Key':'50',  'Keyboard 3 - Lowest Key':'55',  'Keyboard 4 - Lowest Key':'60',  'Keyboard 5 - Lowest Key':'65',  'Keyboard 6 - Lowest Key':'70',  'Keyboard 7 - Lowest Key':'75',  'Keyboard 0 - Piano Keyboard':'0',  'Keyboard 1 - Piano Keyboard':'0',  'Keyboard 2 - Piano Keyboard':'0',  'Keyboard 3 - Piano Keyboard':'0',  'Keyboard 4 - Piano Keyboard':'0',  'Keyboard 5 - Piano Keyboard':'0',  'Keyboard 6 - Piano Keyboard':'0',  'Keyboard 7 - Piano Keyboard':'0' }");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "harp");
		m.declare("noises.lib/name", "Faust Noise Generator Library");
		m.declare("noises.lib/version", "0.0");
		m.declare("synths.lib/name", "Faust Synthesizer Library");
		m.declare("synths.lib/version", "0.0");
	}

	this.getNumInputs = function() {
		return 0;
		
	}
	this.getNumOutputs = function() {
		return 1;
		
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
		this.fConst1 = (1000 / this.fConst0);
		this.fConst2 = (0.002 * this.fConst0);
		this.fConst3 = (0.001 * this.fConst0);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 400;
		this.fHslider1 = 2;
		this.fButton0 = 0;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.fVec0[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.iRec2[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fVec1[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec3[l3] = 0;
			
		}
		this.IOTA = 0;
		for (var l4 = 0; (l4 < 2048); l4 = (l4 + 1)) {
			this.fVec2[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fRec0[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			this.fRec1[l6] = 0;
			
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
		ui_interface.openVerticalBox("harp");
		ui_interface.addHorizontalSlider("freq", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 400, 50, 2000, 0.01);
		ui_interface.addButton("gate", function handler(obj) { function setval(val) { obj.fButton0 = val; } return setval; }(this));
		ui_interface.declare("fHslider1", "acc", "0 0 -10 0 10");
		ui_interface.addHorizontalSlider("res", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 2, 0.1, 4, 0.01);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var output0 = outputs[0];
		var fSlow0 = (this.fConst0 / this.fHslider0);
		var fSlow1 = (fSlow0 + -1);
		var fSlow2 = Math.floor(fSlow1);
		var fSlow3 = (fSlow2 + (2 - fSlow0));
		var fSlow4 = Math.exp((0 - (this.fConst1 / this.fHslider1)));
		var fSlow5 = this.fButton0;
		var iSlow6 = fSlow1;
		var iSlow7 = min_i(1025, max_i(0, iSlow6));
		var fSlow8 = (fSlow0 + (-1 - fSlow2));
		var iSlow9 = min_i(1025, max_i(0, (iSlow6 + 1)));
		for (var i = 0; (i < count); i = (i + 1)) {
			this.fVec0[0] = this.fConst0;
			this.iRec2[0] = ((1103515245 * this.iRec2[1]) + 12345);
			this.fVec1[0] = fSlow5;
			this.fRec3[0] = ((((fSlow5 - this.fVec1[1]) > 0) > 0)?0:min_f(this.fConst2, ((this.fRec3[1] + (0.002 * (this.fConst0 - this.fVec0[1]))) + 1)));
			var iTemp0 = (this.fRec3[0] < this.fConst3);
			var fTemp1 = ((fSlow4 * this.fRec0[1]) + (4.65661e-10 * (this.iRec2[0] * (iTemp0?((this.fRec3[0] < 0)?0:(iTemp0?(this.fConst1 * this.fRec3[0]):1)):((this.fRec3[0] < this.fConst2)?((this.fConst1 * (0 - (this.fRec3[0] - this.fConst3))) + 1):0)))));
			this.fVec2[(this.IOTA & 2047)] = fTemp1;
			this.fRec0[0] = ((fSlow3 * this.fVec2[((this.IOTA - iSlow7) & 2047)]) + (fSlow8 * this.fVec2[((this.IOTA - iSlow9) & 2047)]));
			this.fRec1[0] = fTemp1;
			output0[i] = this.fRec1[1];
			this.fVec0[1] = this.fVec0[0];
			this.iRec2[1] = this.iRec2[0];
			this.fVec1[1] = this.fVec1[0];
			this.fRec3[1] = this.fRec3[0];
			this.IOTA = (this.IOTA + 1);
			this.fRec0[1] = this.fRec0[0];
			this.fRec1[1] = this.fRec1[0];
			
		}
		
	}
	
}

