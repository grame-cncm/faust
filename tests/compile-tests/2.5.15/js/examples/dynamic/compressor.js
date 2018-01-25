
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);

function mydsp() {
	
	this.fCheckbox0;
	this.fHslider0;
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fConst2;
	this.fHslider1;
	this.fHslider2;
	this.fHslider3;
	this.fRec2 = new Float32Array(2);
	this.fRec1 = new Float32Array(2);
	this.fHslider4;
	this.fRec0 = new Float32Array(2);
	this.fRec5 = new Float32Array(2);
	this.fRec4 = new Float32Array(2);
	this.fRec3 = new Float32Array(2);
	this.fHbargraph0;
	
	this.metadata = function(m) { 
		m.declare("analyzers.lib/name", "Faust Analyzer Library");
		m.declare("analyzers.lib/version", "0.0");
		m.declare("author", "JOS, revised by RM");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("compressors.lib/name", "Faust Compressor Effect Library");
		m.declare("compressors.lib/version", "0.0");
		m.declare("description", "Compressor demo application");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "compressor");
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
		this.fConst1 = (2 / this.fConst0);
		this.fConst2 = (1 / this.fConst0);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fCheckbox0 = 0;
		this.fHslider0 = 40;
		this.fHslider1 = 50;
		this.fHslider2 = 5;
		this.fHslider3 = 500;
		this.fHslider4 = -30;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.fRec2[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec1[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec0[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec5[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec4[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fRec3[l5] = 0;
			
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
		ui_interface.declare("0", "tooltip", "Reference:   http://en.wikipedia.org/wiki/Dynamic_range_compression");
		ui_interface.openVerticalBox("COMPRESSOR");
		ui_interface.declare("0", "0", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fCheckbox0", "0", "");
		ui_interface.declare("fCheckbox0", "tooltip", "When this is checked, the compressor   has no effect");
		ui_interface.addCheckButton("Bypass", function handler(obj) { function setval(val) { obj.fCheckbox0 = val; } return setval; }(this));
		ui_interface.declare("fHbargraph0", "1", "");
		ui_interface.declare("fHbargraph0", "tooltip", "Current gain of  the compressor in dB");
		ui_interface.declare("fHbargraph0", "unit", "dB");
		ui_interface.addHorizontalBargraph("Compressor Gain", function handler(obj) { function setval(val) { obj.fHbargraph0 = val; } return setval; }(this), -50, 10);
		ui_interface.closeBox();
		ui_interface.declare("0", "1", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("0", "3", "");
		ui_interface.openHorizontalBox("Compression Control");
		ui_interface.declare("fHslider2", "0", "");
		ui_interface.declare("fHslider2", "style", "knob");
		ui_interface.declare("fHslider2", "tooltip", "A compression Ratio of N means that for each N dB increase in input  signal level above Threshold, the output level goes up 1 dB");
		ui_interface.addHorizontalSlider("Ratio", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 5, 1, 20, 0.1);
		ui_interface.declare("fHslider4", "1", "");
		ui_interface.declare("fHslider4", "style", "knob");
		ui_interface.declare("fHslider4", "tooltip", "When the signal level exceeds the Threshold (in dB), its level  is compressed according to the Ratio");
		ui_interface.declare("fHslider4", "unit", "dB");
		ui_interface.addHorizontalSlider("Threshold", function handler(obj) { function setval(val) { obj.fHslider4 = val; } return setval; }(this), -30, -100, 10, 0.1);
		ui_interface.closeBox();
		ui_interface.declare("0", "4", "");
		ui_interface.openHorizontalBox("Compression Response");
		ui_interface.declare("fHslider1", "1", "");
		ui_interface.declare("fHslider1", "scale", "log");
		ui_interface.declare("fHslider1", "style", "knob");
		ui_interface.declare("fHslider1", "unit", "ms");
		ui_interface.addHorizontalSlider("Attack     tooltip: Time constant in ms (1/e smoothing time) for the compression gain  to approach (exponentially) a new lower target level (the compression  `kicking in')]", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 50, 1, 1000, 0.1);
		ui_interface.declare("fHslider3", "2", "");
		ui_interface.declare("fHslider3", "scale", "log");
		ui_interface.declare("fHslider3", "style", "knob");
		ui_interface.declare("fHslider3", "tooltip", "Time constant in ms (1/e smoothing time) for the compression gain  to approach (exponentially) a new higher target level (the compression  'releasing')");
		ui_interface.declare("fHslider3", "unit", "ms");
		ui_interface.addHorizontalSlider("Release", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 500, 1, 1000, 0.1);
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.declare("fHslider0", "5", "");
		ui_interface.declare("fHslider0", "tooltip", "The compressed-signal output level is increased by this amount  (in dB) to make up for the level lost due to compression");
		ui_interface.declare("fHslider0", "unit", "dB");
		ui_interface.addHorizontalSlider("Makeup Gain", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 40, -96, 96, 0.1);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var input1 = inputs[1];
		var output0 = outputs[0];
		var output1 = outputs[1];
		var iSlow0 = this.fCheckbox0;
		var fSlow1 = Math.pow(10, (0.05 * this.fHslider0));
		var fSlow2 = max_f(this.fConst2, (0.001 * this.fHslider1));
		var fSlow3 = Math.exp((0 - (this.fConst1 / fSlow2)));
		var fSlow4 = (((1 / this.fHslider2) + -1) * (1 - fSlow3));
		var fSlow5 = Math.exp((0 - (this.fConst2 / fSlow2)));
		var fSlow6 = Math.exp((0 - (this.fConst2 / max_f(this.fConst2, (0.001 * this.fHslider3)))));
		var fSlow7 = this.fHslider4;
		for (var i = 0; (i < count); i = (i + 1)) {
			var fTemp0 = input0[i];
			var fTemp1 = (iSlow0?0:fTemp0);
			var fTemp2 = input1[i];
			var fTemp3 = (iSlow0?0:fTemp2);
			var fTemp4 = Math.abs((Math.abs(fTemp1) + Math.abs(fTemp3)));
			var fTemp5 = ((this.fRec1[1] > fTemp4)?fSlow6:fSlow5);
			this.fRec2[0] = ((this.fRec2[1] * fTemp5) + (fTemp4 * (1 - fTemp5)));
			this.fRec1[0] = this.fRec2[0];
			this.fRec0[0] = ((fSlow3 * this.fRec0[1]) + (fSlow4 * max_f(((20 * function log10(a) { return Math.log(a)/Math.log(10); }(this.fRec1[0])) - fSlow7), 0)));
			var fTemp6 = Math.pow(10, (0.05 * this.fRec0[0]));
			var fTemp7 = (fTemp1 * fTemp6);
			output0[i] = (iSlow0?fTemp0:(fSlow1 * fTemp7));
			var fTemp8 = (fTemp3 * fTemp6);
			var fTemp9 = Math.abs((Math.abs(fTemp7) + Math.abs(fTemp8)));
			var fTemp10 = ((this.fRec4[1] > fTemp9)?fSlow6:fSlow5);
			this.fRec5[0] = ((this.fRec5[1] * fTemp10) + (fTemp9 * (1 - fTemp10)));
			this.fRec4[0] = this.fRec5[0];
			this.fRec3[0] = ((fSlow3 * this.fRec3[1]) + (fSlow4 * max_f(((20 * function log10(a) { return Math.log(a)/Math.log(10); }(this.fRec4[0])) - fSlow7), 0)));
			this.fHbargraph0 = (20 * function log10(a) { return Math.log(a)/Math.log(10); }(Math.pow(10, (0.05 * this.fRec3[0]))));
			output1[i] = (iSlow0?fTemp2:(fSlow1 * fTemp8));
			this.fRec2[1] = this.fRec2[0];
			this.fRec1[1] = this.fRec1[0];
			this.fRec0[1] = this.fRec0[0];
			this.fRec5[1] = this.fRec5[0];
			this.fRec4[1] = this.fRec4[0];
			this.fRec3[1] = this.fRec3[0];
			
		}
		
	}
	
}

