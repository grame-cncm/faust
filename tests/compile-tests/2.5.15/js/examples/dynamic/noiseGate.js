
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.max_i = function(dummy0, dummy1);

function mydsp() {
	
	this.fCheckbox0;
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fConst2;
	this.fHslider0;
	this.fHslider1;
	this.fRec3 = new Float32Array(2);
	this.fHslider2;
	this.iVec0 = new Int32Array(2);
	this.fHslider3;
	this.iRec4 = new Int32Array(2);
	this.fRec1 = new Float32Array(2);
	this.fRec0 = new Float32Array(2);
	this.fHbargraph0;
	this.fRec8 = new Float32Array(2);
	this.iVec1 = new Int32Array(2);
	this.iRec9 = new Int32Array(2);
	this.fRec6 = new Float32Array(2);
	this.fRec5 = new Float32Array(2);
	
	this.metadata = function(m) { 
		m.declare("analyzers.lib/name", "Faust Analyzer Library");
		m.declare("analyzers.lib/version", "0.0");
		m.declare("author", "JOS, revised by RM");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("description", "Gate demo application.");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("misceffects.lib/name", "Faust Math Library");
		m.declare("misceffects.lib/version", "2.0");
		m.declare("name", "noiseGate");
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
		this.fConst1 = (1 / this.fConst0);
		this.fConst2 = (1 / this.fConst0);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fCheckbox0 = 0;
		this.fHslider0 = 10;
		this.fHslider1 = 100;
		this.fHslider2 = -30;
		this.fHslider3 = 200;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.fRec3[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.iVec0[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.iRec4[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec1[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec0[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fRec8[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			this.iVec1[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			this.iRec9[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			this.fRec6[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			this.fRec5[l9] = 0;
			
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
		ui_interface.declare("0", "tooltip", "Reference:   http://en.wikipedia.org/wiki/Noise_gate");
		ui_interface.openVerticalBox("GATE");
		ui_interface.declare("0", "0", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fCheckbox0", "0", "");
		ui_interface.declare("fCheckbox0", "tooltip", "When this is checked,   the gate has no effect");
		ui_interface.addCheckButton("Bypass", function handler(obj) { function setval(val) { obj.fCheckbox0 = val; } return setval; }(this));
		ui_interface.declare("fHbargraph0", "1", "");
		ui_interface.declare("fHbargraph0", "tooltip", "Current gain of the  gate in dB");
		ui_interface.declare("fHbargraph0", "unit", "dB");
		ui_interface.addHorizontalBargraph("Gate Gain", function handler(obj) { function setval(val) { obj.fHbargraph0 = val; } return setval; }(this), -50, 10);
		ui_interface.closeBox();
		ui_interface.declare("0", "1", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fHslider2", "1", "");
		ui_interface.declare("fHslider2", "style", "knob");
		ui_interface.declare("fHslider2", "tooltip", "When   the signal level falls below the Threshold (expressed in dB), the signal is   muted");
		ui_interface.declare("fHslider2", "unit", "dB");
		ui_interface.addHorizontalSlider("Threshold", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), -30, -120, 0, 0.1);
		ui_interface.declare("fHslider0", "2", "");
		ui_interface.declare("fHslider0", "scale", "log");
		ui_interface.declare("fHslider0", "style", "knob");
		ui_interface.declare("fHslider0", "tooltip", "Time constant in MICROseconds (1/e smoothing time) for the gate  gain to go (exponentially) from 0 (muted) to 1 (unmuted)");
		ui_interface.declare("fHslider0", "unit", "us");
		ui_interface.addHorizontalSlider("Attack", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 10, 10, 10000, 1);
		ui_interface.declare("fHslider3", "3", "");
		ui_interface.declare("fHslider3", "scale", "log");
		ui_interface.declare("fHslider3", "style", "knob");
		ui_interface.declare("fHslider3", "tooltip", "Time in ms to keep the gate open (no muting) after the signal  level falls below the Threshold");
		ui_interface.declare("fHslider3", "unit", "ms");
		ui_interface.addHorizontalSlider("Hold", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 200, 1, 1000, 1);
		ui_interface.declare("fHslider1", "4", "");
		ui_interface.declare("fHslider1", "scale", "log");
		ui_interface.declare("fHslider1", "style", "knob");
		ui_interface.declare("fHslider1", "tooltip", "Time constant in ms (1/e smoothing time) for the gain to go  (exponentially) from 1 (unmuted) to 0 (muted)");
		ui_interface.declare("fHslider1", "unit", "ms");
		ui_interface.addHorizontalSlider("Release", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 100, 1, 1000, 1);
		ui_interface.closeBox();
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var input1 = inputs[1];
		var output0 = outputs[0];
		var output1 = outputs[1];
		var iSlow0 = this.fCheckbox0;
		var fSlow1 = max_f(this.fConst2, (1e-06 * this.fHslider0));
		var fSlow2 = max_f(this.fConst2, (0.001 * this.fHslider1));
		var fSlow3 = Math.exp((0 - (this.fConst1 / min_f(fSlow1, fSlow2))));
		var fSlow4 = (1 - fSlow3);
		var fSlow5 = Math.pow(10, (0.05 * this.fHslider2));
		var iSlow6 = (this.fConst0 * max_f(this.fConst2, (0.001 * this.fHslider3)));
		var fSlow7 = Math.exp((0 - (this.fConst1 / fSlow1)));
		var fSlow8 = Math.exp((0 - (this.fConst1 / fSlow2)));
		for (var i = 0; (i < count); i = (i + 1)) {
			var fTemp0 = input0[i];
			var fTemp1 = (iSlow0?0:fTemp0);
			var fTemp2 = input1[i];
			var fTemp3 = (iSlow0?0:fTemp2);
			var fTemp4 = Math.abs(fTemp3);
			this.fRec3[0] = ((fSlow3 * this.fRec3[1]) + (fSlow4 * Math.abs((Math.abs(fTemp1) + fTemp4))));
			var fRec2 = this.fRec3[0];
			var iTemp5 = (fRec2 > fSlow5);
			this.iVec0[0] = iTemp5;
			this.iRec4[0] = max_i((iSlow6 * (iTemp5 < this.iVec0[1])), (this.iRec4[1] + -1));
			var fTemp6 = Math.abs(max_f(iTemp5, (this.iRec4[0] > 0)));
			var fTemp7 = ((this.fRec0[1] > fTemp6)?fSlow8:fSlow7);
			this.fRec1[0] = ((this.fRec1[1] * fTemp7) + (fTemp6 * (1 - fTemp7)));
			this.fRec0[0] = this.fRec1[0];
			this.fHbargraph0 = (20 * function log10(a) { return Math.log(a)/Math.log(10); }(this.fRec0[0]));
			this.fRec8[0] = ((fSlow3 * this.fRec8[1]) + (fSlow4 * Math.abs((fTemp4 + Math.abs(fTemp1)))));
			var fRec7 = this.fRec8[0];
			var iTemp8 = (fRec7 > fSlow5);
			this.iVec1[0] = iTemp8;
			this.iRec9[0] = max_i((iSlow6 * (iTemp8 < this.iVec1[1])), (this.iRec9[1] + -1));
			var fTemp9 = Math.abs(max_f(iTemp8, (this.iRec9[0] > 0)));
			var fTemp10 = ((this.fRec5[1] > fTemp9)?fSlow8:fSlow7);
			this.fRec6[0] = ((this.fRec6[1] * fTemp10) + (fTemp9 * (1 - fTemp10)));
			this.fRec5[0] = this.fRec6[0];
			output0[i] = (iSlow0?fTemp0:(fTemp1 * this.fRec5[0]));
			output1[i] = (iSlow0?fTemp2:(fTemp3 * this.fRec5[0]));
			this.fRec3[1] = this.fRec3[0];
			this.iVec0[1] = this.iVec0[0];
			this.iRec4[1] = this.iRec4[0];
			this.fRec1[1] = this.fRec1[0];
			this.fRec0[1] = this.fRec0[0];
			this.fRec8[1] = this.fRec8[0];
			this.iVec1[1] = this.iVec1[0];
			this.iRec9[1] = this.iRec9[0];
			this.fRec6[1] = this.fRec6[0];
			this.fRec5[1] = this.fRec5[0];
			
		}
		
	}
	
}

