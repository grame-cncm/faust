
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.max_i = function(dummy0, dummy1);
this.min_i = function(dummy0, dummy1);

function mydsp() {
	
	this.fCheckbox0;
	this.fHslider0;
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fHslider1;
	this.iVec0 = new Int32Array(2);
	this.fRec0 = new Float32Array(2);
	this.fRec1 = new Float32Array(2);
	this.fHbargraph0;
	this.fCheckbox1;
	this.fHslider2;
	this.fHslider3;
	this.IOTA;
	this.fVec1 = new Float32Array(4096);
	this.fHslider4;
	this.fHslider5;
	this.fRec2 = new Float32Array(2);
	this.fVec2 = new Float32Array(4096);
	this.fRec3 = new Float32Array(2);
	
	this.metadata = function(m) { 
		m.declare("author", "JOS, revised by RM");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("description", "Flanger effect application.");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "flanger");
		m.declare("oscillators.lib/name", "Faust Oscillator Library");
		m.declare("oscillators.lib/version", "0.0");
		m.declare("phaflangers.lib/name", "Faust Phaser and Flanger Library");
		m.declare("phaflangers.lib/version", "0.0");
		m.declare("routes.lib/name", "Faust Signal Routing Library");
		m.declare("routes.lib/version", "0.0");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
		m.declare("version", "0.0");
	}

	this.getNumInputs = function() {
		return 2;
		
	}
	this.getNumOutputs = function() {
		return 2;
		
	}
	this.getInputRate = function(channel) {
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
		this.fConst1 = (6.28319 / this.fConst0);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fCheckbox0 = 0;
		this.fHslider0 = 0;
		this.fHslider1 = 0.5;
		this.fCheckbox1 = 0;
		this.fHslider2 = 1;
		this.fHslider3 = 0;
		this.fHslider4 = 1;
		this.fHslider5 = 10;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.iVec0[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec0[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec1[l2] = 0;
			
		}
		this.IOTA = 0;
		for (var l3 = 0; (l3 < 4096); l3 = (l3 + 1)) {
			this.fVec1[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec2[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 4096); l5 = (l5 + 1)) {
			this.fVec2[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			this.fRec3[l6] = 0;
			
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
		ui_interface.declare("0", "tooltip", "Reference: https://ccrma.stanford.edu/~jos/pasp/Flanging.html");
		ui_interface.openVerticalBox("FLANGER");
		ui_interface.declare("0", "0", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fCheckbox0", "0", "");
		ui_interface.declare("fCheckbox0", "tooltip", "When this is checked, the flanger   has no effect");
		ui_interface.addCheckButton("Bypass", function handler(obj) { function setval(val) { obj.fCheckbox0 = val; } return setval; }(this));
		ui_interface.declare("fCheckbox1", "1", "");
		ui_interface.addCheckButton("Invert Flange Sum", function handler(obj) { function setval(val) { obj.fCheckbox1 = val; } return setval; }(this));
		ui_interface.declare("fHbargraph0", "2", "");
		ui_interface.declare("fHbargraph0", "style", "led");
		ui_interface.declare("fHbargraph0", "tooltip", "Display sum of flange delays");
		ui_interface.addHorizontalBargraph("Flange LFO", function handler(obj) { function setval(val) { obj.fHbargraph0 = val; } return setval; }(this), -1.5, 1.5);
		ui_interface.closeBox();
		ui_interface.declare("0", "1", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fHslider1", "1", "");
		ui_interface.declare("fHslider1", "style", "knob");
		ui_interface.declare("fHslider1", "unit", "Hz");
		ui_interface.addHorizontalSlider("Speed", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 0.5, 0, 10, 0.01);
		ui_interface.declare("fHslider2", "2", "");
		ui_interface.declare("fHslider2", "style", "knob");
		ui_interface.addHorizontalSlider("Depth", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 1, 0, 1, 0.001);
		ui_interface.declare("fHslider3", "3", "");
		ui_interface.declare("fHslider3", "style", "knob");
		ui_interface.addHorizontalSlider("Feedback", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 0, -0.999, 0.999, 0.001);
		ui_interface.closeBox();
		ui_interface.declare("0", "2", "");
		ui_interface.openHorizontalBox("Delay Controls");
		ui_interface.declare("fHslider5", "1", "");
		ui_interface.declare("fHslider5", "style", "knob");
		ui_interface.declare("fHslider5", "unit", "ms");
		ui_interface.addHorizontalSlider("Flange Delay", function handler(obj) { function setval(val) { obj.fHslider5 = val; } return setval; }(this), 10, 0, 20, 0.001);
		ui_interface.declare("fHslider4", "2", "");
		ui_interface.declare("fHslider4", "style", "knob");
		ui_interface.declare("fHslider4", "unit", "ms");
		ui_interface.addHorizontalSlider("Delay Offset", function handler(obj) { function setval(val) { obj.fHslider4 = val; } return setval; }(this), 1, 0, 20, 0.001);
		ui_interface.closeBox();
		ui_interface.declare("0", "3", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fHslider0", "unit", "dB");
		ui_interface.addHorizontalSlider("Flanger Output Level", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0, -60, 10, 0.1);
		ui_interface.closeBox();
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var input1 = inputs[1];
		var output0 = outputs[0];
		var output1 = outputs[1];
		var iSlow0 = this.fCheckbox0;
		var fSlow1 = Math.pow(10, (0.05 * this.fHslider0));
		var fSlow2 = (this.fConst1 * this.fHslider1);
		var fSlow3 = Math.sin(fSlow2);
		var fSlow4 = Math.cos(fSlow2);
		var fSlow5 = (0 - fSlow3);
		var fSlow6 = this.fHslider2;
		var fSlow7 = (this.fCheckbox1?(0 - fSlow6):fSlow6);
		var fSlow8 = this.fHslider3;
		var fSlow9 = (0.001 * this.fHslider4);
		var fSlow10 = (0.0005 * this.fHslider5);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iVec0[0] = 1;
			this.fRec0[0] = ((fSlow3 * this.fRec1[1]) + (fSlow4 * this.fRec0[1]));
			this.fRec1[0] = (((fSlow4 * this.fRec1[1]) + (fSlow5 * this.fRec0[1])) + (1 - this.iVec0[1]));
			this.fHbargraph0 = (this.fRec1[0] + this.fRec0[0]);
			var fTemp0 = input0[i];
			var fTemp1 = (fSlow1 * (iSlow0?0:fTemp0));
			var fTemp2 = ((fSlow8 * this.fRec2[1]) - fTemp1);
			this.fVec1[(this.IOTA & 4095)] = fTemp2;
			var fTemp3 = (this.fConst0 * (fSlow9 + (fSlow10 * (this.fRec0[0] + 1))));
			var iTemp4 = fTemp3;
			var fTemp5 = Math.floor(fTemp3);
			this.fRec2[0] = ((this.fVec1[((this.IOTA - min_i(2049, max_i(0, iTemp4))) & 4095)] * (fTemp5 + (1 - fTemp3))) + ((fTemp3 - fTemp5) * this.fVec1[((this.IOTA - min_i(2049, max_i(0, (iTemp4 + 1)))) & 4095)]));
			output0[i] = (iSlow0?fTemp0:(0.5 * (fTemp1 + (fSlow7 * this.fRec2[0]))));
			var fTemp6 = input1[i];
			var fTemp7 = (fSlow1 * (iSlow0?0:fTemp6));
			var fTemp8 = ((fSlow8 * this.fRec3[1]) - fTemp7);
			this.fVec2[(this.IOTA & 4095)] = fTemp8;
			var fTemp9 = (this.fConst0 * (fSlow9 + (fSlow10 * (this.fRec1[0] + 1))));
			var iTemp10 = fTemp9;
			var fTemp11 = Math.floor(fTemp9);
			this.fRec3[0] = ((this.fVec2[((this.IOTA - min_i(2049, max_i(0, iTemp10))) & 4095)] * (fTemp11 + (1 - fTemp9))) + ((fTemp9 - fTemp11) * this.fVec2[((this.IOTA - min_i(2049, max_i(0, (iTemp10 + 1)))) & 4095)]));
			output1[i] = (iSlow0?fTemp6:(0.5 * (fTemp7 + (fSlow7 * this.fRec3[0]))));
			this.iVec0[1] = this.iVec0[0];
			this.fRec0[1] = this.fRec0[0];
			this.fRec1[1] = this.fRec1[0];
			this.IOTA = (this.IOTA + 1);
			this.fRec2[1] = this.fRec2[0];
			this.fRec3[1] = this.fRec3[0];
			
		}
		
	}
	
}

