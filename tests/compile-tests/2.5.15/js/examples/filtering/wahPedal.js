
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);

function mydsp() {
	
	this.fCheckbox0;
	this.fSamplingFreq;
	this.fConst0;
	this.fHslider0;
	this.fRec5 = new Float32Array(2);
	this.fRec4 = new Float32Array(2);
	this.fRec3 = new Float32Array(2);
	this.fRec2 = new Float32Array(2);
	this.fRec1 = new Float32Array(2);
	this.fRec0 = new Float32Array(2);
	
	this.metadata = function(m) { 
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("description", "Demonstrate the Fourth-Order Wah pedal (similar to the Moog VCF)");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "wahPedal");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
		m.declare("vaeffects.lib/name", "Faust Virtual Analog Filter Effect Library");
		m.declare("vaeffects.lib/version", "0.0");
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
		this.fConst0 = (6.28319 / min_f(192000, max_f(1, this.fSamplingFreq)));
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fCheckbox0 = 0;
		this.fHslider0 = 200;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.fRec5[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec4[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec3[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec2[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec1[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fRec0[l5] = 0;
			
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
		ui_interface.declare("0", "tooltip", "Fourth-order wah effect made using moog_vcf");
		ui_interface.openHorizontalBox("WAH4");
		ui_interface.declare("fCheckbox0", "0", "");
		ui_interface.declare("fCheckbox0", "tooltip", "When this is checked, the wah pedal has   no effect");
		ui_interface.addCheckButton("Bypass", function handler(obj) { function setval(val) { obj.fCheckbox0 = val; } return setval; }(this));
		ui_interface.declare("fHslider0", "1", "");
		ui_interface.declare("fHslider0", "scale", "log");
		ui_interface.declare("fHslider0", "tooltip", "wah resonance   frequency in Hz");
		ui_interface.addHorizontalSlider("Resonance Frequency", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 200, 100, 2000, 1);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var output0 = outputs[0];
		var iSlow0 = this.fCheckbox0;
		var fSlow1 = (0.001 * this.fHslider0);
		for (var i = 0; (i < count); i = (i + 1)) {
			var fTemp0 = input0[i];
			this.fRec5[0] = (fSlow1 + (0.999 * this.fRec5[1]));
			var fTemp1 = (this.fConst0 * this.fRec5[0]);
			var fTemp2 = (1 - fTemp1);
			this.fRec4[0] = (((iSlow0?0:fTemp0) + (fTemp2 * this.fRec4[1])) - (3.2 * this.fRec0[1]));
			this.fRec3[0] = (this.fRec4[0] + (fTemp2 * this.fRec3[1]));
			this.fRec2[0] = (this.fRec3[0] + (fTemp2 * this.fRec2[1]));
			this.fRec1[0] = (this.fRec2[0] + (this.fRec1[1] * fTemp2));
			this.fRec0[0] = (this.fRec1[0] * Math.pow(fTemp1, 4));
			output0[i] = (iSlow0?fTemp0:(4 * this.fRec0[0]));
			this.fRec5[1] = this.fRec5[0];
			this.fRec4[1] = this.fRec4[0];
			this.fRec3[1] = this.fRec3[0];
			this.fRec2[1] = this.fRec2[0];
			this.fRec1[1] = this.fRec1[0];
			this.fRec0[1] = this.fRec0[0];
			
		}
		
	}
	
}

