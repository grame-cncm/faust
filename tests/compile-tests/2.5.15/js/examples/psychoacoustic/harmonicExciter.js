
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.mydsp_faustpower2_f = function(value) {
	return (value * value);
	
}
this.mydsp_faustpower3_f = function(value) {
	return ((value * value) * value);
	
}

function mydsp() {
	
	this.fHslider0;
	this.fHslider1;
	this.fCheckbox0;
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fConst2;
	this.fHslider2;
	this.fHslider3;
	this.fConst3;
	this.fHslider4;
	this.fRec3 = new Float32Array(3);
	this.fHslider5;
	this.fRec6 = new Float32Array(2);
	this.fRec5 = new Float32Array(2);
	this.fHslider6;
	this.fRec4 = new Float32Array(2);
	this.fRec2 = new Float32Array(2);
	this.fRec1 = new Float32Array(2);
	this.fRec0 = new Float32Array(2);
	this.fHbargraph0;
	
	this.metadata = function(m) { 
		m.declare("analyzers.lib/name", "Faust Analyzer Library");
		m.declare("analyzers.lib/version", "0.0");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("compressors.lib/name", "Faust Compressor Effect Library");
		m.declare("compressors.lib/version", "0.0");
		m.declare("description", "Psychoacoustic harmonic exciter, with GUI");
		m.declare("exciter_author", "Priyanka Shekar (pshekar@ccrma.stanford.edu), revised by RM");
		m.declare("exciter_copyright", "Copyright (c) 2013 Priyanka Shekar");
		m.declare("exciter_license", "MIT License (MIT)");
		m.declare("exciter_name", "harmonicExciter");
		m.declare("exciter_version", "1.0");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "harmonicExciter");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
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
		this.fConst0 = min_f(192000, max_f(1, this.fSamplingFreq));
		this.fConst1 = (2 / this.fConst0);
		this.fConst2 = (1 / this.fConst0);
		this.fConst3 = (3.14159 / this.fConst0);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 0.5;
		this.fHslider1 = 20;
		this.fCheckbox0 = 0;
		this.fHslider2 = 50;
		this.fHslider3 = 5;
		this.fHslider4 = 5000;
		this.fHslider5 = 500;
		this.fHslider6 = -30;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 3); l0 = (l0 + 1)) {
			this.fRec3[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec6[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec5[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec4[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec2[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fRec1[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
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
		ui_interface.openVerticalBox("harmonicExciter");
		ui_interface.declare("0", "tooltip", "Reference:    http://en.wikipedia.org/wiki/Dynamic_range_compression");
		ui_interface.openVerticalBox("COMPRESSOR");
		ui_interface.declare("0", "0", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fCheckbox0", "0", "");
		ui_interface.declare("fCheckbox0", "tooltip", "When this is checked,   the compressor has no effect");
		ui_interface.addCheckButton("Bypass", function handler(obj) { function setval(val) { obj.fCheckbox0 = val; } return setval; }(this));
		ui_interface.declare("fHbargraph0", "1", "");
		ui_interface.declare("fHbargraph0", "tooltip", "Current gain   of the compressor in dB");
		ui_interface.declare("fHbargraph0", "unit", "dB");
		ui_interface.addHorizontalBargraph("Compressor Gain", function handler(obj) { function setval(val) { obj.fHbargraph0 = val; } return setval; }(this), -50, 10);
		ui_interface.closeBox();
		ui_interface.declare("0", "1", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("0", "3", "");
		ui_interface.openHorizontalBox("Compression Control");
		ui_interface.declare("fHslider3", "0", "");
		ui_interface.declare("fHslider3", "style", "knob");
		ui_interface.declare("fHslider3", "tooltip", "A compression Ratio  of N means that for each N dB increase in input signal level above Threshold, the  output level goes up 1 dB");
		ui_interface.addHorizontalSlider("Ratio", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 5, 1, 20, 0.1);
		ui_interface.declare("fHslider6", "1", "");
		ui_interface.declare("fHslider6", "style", "knob");
		ui_interface.declare("fHslider6", "tooltip", "When the signal level exceeds the Threshold (in dB), its level is compressed  according to the Ratio");
		ui_interface.declare("fHslider6", "unit", "dB");
		ui_interface.addHorizontalSlider("Threshold", function handler(obj) { function setval(val) { obj.fHslider6 = val; } return setval; }(this), -30, -100, 10, 0.1);
		ui_interface.closeBox();
		ui_interface.declare("0", "4", "");
		ui_interface.openHorizontalBox("Compression Response");
		ui_interface.declare("fHslider2", "1", "");
		ui_interface.declare("fHslider2", "style", "knob");
		ui_interface.declare("fHslider2", "tooltip", "Time constant in ms (1/e smoothing time) for the compression gain to approach  (exponentially) a new lower target level (the compression `kicking in')");
		ui_interface.declare("fHslider2", "unit", "ms");
		ui_interface.addHorizontalSlider("Attack", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 50, 0, 500, 0.1);
		ui_interface.declare("fHslider5", "2", "");
		ui_interface.declare("fHslider5", "style", "knob");
		ui_interface.declare("fHslider5", "tooltip", "Time constant in ms (1/e smoothing time) for the compression gain to approach  (exponentially) a new higher target level (the compression 'releasing')");
		ui_interface.declare("fHslider5", "unit", "ms");
		ui_interface.addHorizontalSlider("Release", function handler(obj) { function setval(val) { obj.fHslider5 = val; } return setval; }(this), 500, 0, 1000, 0.1);
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.declare("0", "tooltip", "Reference: Patent US4150253 A");
		ui_interface.openHorizontalBox("EXCITER");
		ui_interface.declare("fHslider4", "0", "");
		ui_interface.declare("fHslider4", "scale", "log");
		ui_interface.declare("fHslider4", "style", "knob");
		ui_interface.declare("fHslider4", "tooltip", "Cutoff frequency for highpassed components to be excited");
		ui_interface.declare("fHslider4", "unit", "Hz");
		ui_interface.addHorizontalSlider("Cutoff Frequency", function handler(obj) { function setval(val) { obj.fHslider4 = val; } return setval; }(this), 5000, 1000, 10000, 100);
		ui_interface.declare("fHslider1", "1", "");
		ui_interface.declare("fHslider1", "style", "knob");
		ui_interface.declare("fHslider1", "tooltip", "Percentage of harmonics generated");
		ui_interface.declare("fHslider1", "unit", "percent");
		ui_interface.addHorizontalSlider("Harmonics", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 20, 0, 200, 1);
		ui_interface.declare("fHslider0", "2", "");
		ui_interface.declare("fHslider0", "style", "knob");
		ui_interface.declare("fHslider0", "tooltip", "Dry/Wet mix of original signal   to excited signal");
		ui_interface.addHorizontalSlider("Mix", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.closeBox();
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var output0 = outputs[0];
		var fSlow0 = this.fHslider0;
		var fSlow1 = this.fHslider1;
		var fSlow2 = (100 * (fSlow0 / fSlow1));
		var fSlow3 = (0.01 * fSlow1);
		var iSlow4 = this.fCheckbox0;
		var fSlow5 = max_f(this.fConst2, (0.001 * this.fHslider2));
		var fSlow6 = Math.exp((0 - (this.fConst1 / fSlow5)));
		var fSlow7 = (((1 / this.fHslider3) + -1) * (1 - fSlow6));
		var fSlow8 = Math.tan((this.fConst3 * this.fHslider4));
		var fSlow9 = (1 / fSlow8);
		var fSlow10 = (1 / (((fSlow9 + 1.41421) / fSlow8) + 1));
		var fSlow11 = (1 / mydsp_faustpower2_f(fSlow8));
		var fSlow12 = (((fSlow9 + -1.41421) / fSlow8) + 1);
		var fSlow13 = (2 * (1 - fSlow11));
		var fSlow14 = (2 * (0 - fSlow11));
		var fSlow15 = Math.exp((0 - (this.fConst2 / fSlow5)));
		var fSlow16 = Math.exp((0 - (this.fConst2 / max_f(this.fConst2, (0.001 * this.fHslider5)))));
		var fSlow17 = this.fHslider6;
		var fSlow18 = (1 - fSlow0);
		for (var i = 0; (i < count); i = (i + 1)) {
			var fTemp0 = input0[i];
			this.fRec3[0] = (fTemp0 - (fSlow10 * ((fSlow12 * this.fRec3[2]) + (fSlow13 * this.fRec3[1]))));
			var fTemp1 = (fSlow10 * (((fSlow11 * this.fRec3[0]) + (fSlow14 * this.fRec3[1])) + (fSlow11 * this.fRec3[2])));
			var fTemp2 = (iSlow4?0:fTemp1);
			var fTemp3 = Math.abs(fTemp2);
			var fTemp4 = ((this.fRec5[1] > fTemp3)?fSlow16:fSlow15);
			this.fRec6[0] = ((this.fRec6[1] * fTemp4) + (fTemp3 * (1 - fTemp4)));
			this.fRec5[0] = this.fRec6[0];
			this.fRec4[0] = ((fSlow6 * this.fRec4[1]) + (fSlow7 * max_f(((20 * function log10(a) { return Math.log(a)/Math.log(10); }(this.fRec5[0])) - fSlow17), 0)));
			var fTemp5 = (fTemp2 * Math.pow(10, (0.05 * this.fRec4[0])));
			var fTemp6 = Math.abs(Math.abs(fTemp5));
			var fTemp7 = ((this.fRec1[1] > fTemp6)?fSlow16:fSlow15);
			this.fRec2[0] = ((this.fRec2[1] * fTemp7) + (fTemp6 * (1 - fTemp7)));
			this.fRec1[0] = this.fRec2[0];
			this.fRec0[0] = ((fSlow6 * this.fRec0[1]) + (fSlow7 * max_f(((20 * function log10(a) { return Math.log(a)/Math.log(10); }(this.fRec1[0])) - fSlow17), 0)));
			this.fHbargraph0 = (20 * function log10(a) { return Math.log(a)/Math.log(10); }(Math.pow(10, (0.05 * this.fRec0[0]))));
			var fTemp8 = (iSlow4?fTemp1:fTemp5);
			var fTemp9 = (fSlow3 * fTemp8);
			output0[i] = ((fSlow2 * (((fSlow3 * (fTemp8 * (fTemp9 < 0))) + (((fTemp9 >= 0) * (fTemp9 <= 1)) * (fTemp9 - (0.333333 * mydsp_faustpower3_f(fTemp9))))) + (0.666667 * (fTemp9 > 1)))) + (fSlow18 * fTemp0));
			this.fRec3[2] = this.fRec3[1];
			this.fRec3[1] = this.fRec3[0];
			this.fRec6[1] = this.fRec6[0];
			this.fRec5[1] = this.fRec5[0];
			this.fRec4[1] = this.fRec4[0];
			this.fRec2[1] = this.fRec2[0];
			this.fRec1[1] = this.fRec1[0];
			this.fRec0[1] = this.fRec0[0];
			
		}
		
	}
	
}

