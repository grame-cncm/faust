
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.mydsp_faustpower2_f = function(value) {
	return (value * value);
	
}
this.mydsp_faustpower3_f = function(value) {
	return ((value * value) * value);
	
}
this.mydsp_faustpower4_f = function(value) {
	return (((value * value) * value) * value);
	
}

function mydsp() {
	
	this.fCheckbox0;
	this.fHslider0;
	this.iVec0 = new Int32Array(2);
	this.fCheckbox1;
	this.fHslider1;
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fHslider2;
	this.fHslider3;
	this.fHslider4;
	this.fConst2;
	this.fHslider5;
	this.fHslider6;
	this.fHslider7;
	this.fRec5 = new Float32Array(2);
	this.fRec6 = new Float32Array(2);
	this.fRec4 = new Float32Array(3);
	this.fRec3 = new Float32Array(3);
	this.fRec2 = new Float32Array(3);
	this.fRec1 = new Float32Array(3);
	this.fRec0 = new Float32Array(2);
	this.fCheckbox2;
	this.fRec11 = new Float32Array(3);
	this.fRec10 = new Float32Array(3);
	this.fRec9 = new Float32Array(3);
	this.fRec8 = new Float32Array(3);
	this.fRec7 = new Float32Array(2);
	
	this.metadata = function(m) { 
		m.declare("author", "JOS, revised by RM");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("description", "Phaser demo application.");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "phaser");
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
		this.fConst1 = (1 / this.fConst0);
		this.fConst2 = (6.28319 / this.fConst0);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fCheckbox0 = 0;
		this.fHslider0 = 0;
		this.fCheckbox1 = 0;
		this.fHslider1 = 1;
		this.fHslider2 = 1000;
		this.fHslider3 = 0;
		this.fHslider4 = 1.5;
		this.fHslider5 = 100;
		this.fHslider6 = 800;
		this.fHslider7 = 0.5;
		this.fCheckbox2 = 0;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.iVec0[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec5[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec6[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 3); l3 = (l3 + 1)) {
			this.fRec4[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 3); l4 = (l4 + 1)) {
			this.fRec3[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 3); l5 = (l5 + 1)) {
			this.fRec2[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 3); l6 = (l6 + 1)) {
			this.fRec1[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			this.fRec0[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
			this.fRec11[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 3); l9 = (l9 + 1)) {
			this.fRec10[l9] = 0;
			
		}
		for (var l10 = 0; (l10 < 3); l10 = (l10 + 1)) {
			this.fRec9[l10] = 0;
			
		}
		for (var l11 = 0; (l11 < 3); l11 = (l11 + 1)) {
			this.fRec8[l11] = 0;
			
		}
		for (var l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			this.fRec7[l12] = 0;
			
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
		ui_interface.declare("0", "tooltip", "Reference:   https://ccrma.stanford.edu/~jos/pasp/Flanging.html");
		ui_interface.openVerticalBox("PHASER2");
		ui_interface.declare("0", "0", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fCheckbox0", "0", "");
		ui_interface.declare("fCheckbox0", "tooltip", "When this is checked, the phaser   has no effect");
		ui_interface.addCheckButton("Bypass", function handler(obj) { function setval(val) { obj.fCheckbox0 = val; } return setval; }(this));
		ui_interface.declare("fCheckbox2", "1", "");
		ui_interface.addCheckButton("Invert Internal Phaser Sum", function handler(obj) { function setval(val) { obj.fCheckbox2 = val; } return setval; }(this));
		ui_interface.declare("fCheckbox1", "2", "");
		ui_interface.addCheckButton("Vibrato Mode", function handler(obj) { function setval(val) { obj.fCheckbox1 = val; } return setval; }(this));
		ui_interface.closeBox();
		ui_interface.declare("0", "1", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fHslider7", "1", "");
		ui_interface.declare("fHslider7", "style", "knob");
		ui_interface.declare("fHslider7", "unit", "Hz");
		ui_interface.addHorizontalSlider("Speed", function handler(obj) { function setval(val) { obj.fHslider7 = val; } return setval; }(this), 0.5, 0, 10, 0.001);
		ui_interface.declare("fHslider1", "2", "");
		ui_interface.declare("fHslider1", "style", "knob");
		ui_interface.addHorizontalSlider("Notch Depth (Intensity)", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 1, 0, 1, 0.001);
		ui_interface.declare("fHslider3", "3", "");
		ui_interface.declare("fHslider3", "style", "knob");
		ui_interface.addHorizontalSlider("Feedback Gain", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 0, -0.999, 0.999, 0.001);
		ui_interface.closeBox();
		ui_interface.declare("0", "2", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fHslider2", "1", "");
		ui_interface.declare("fHslider2", "scale", "log");
		ui_interface.declare("fHslider2", "style", "knob");
		ui_interface.declare("fHslider2", "unit", "Hz");
		ui_interface.addHorizontalSlider("Notch width", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 1000, 10, 5000, 1);
		ui_interface.declare("fHslider5", "2", "");
		ui_interface.declare("fHslider5", "scale", "log");
		ui_interface.declare("fHslider5", "style", "knob");
		ui_interface.declare("fHslider5", "unit", "Hz");
		ui_interface.addHorizontalSlider("Min Notch1 Freq", function handler(obj) { function setval(val) { obj.fHslider5 = val; } return setval; }(this), 100, 20, 5000, 1);
		ui_interface.declare("fHslider6", "3", "");
		ui_interface.declare("fHslider6", "scale", "log");
		ui_interface.declare("fHslider6", "style", "knob");
		ui_interface.declare("fHslider6", "unit", "Hz");
		ui_interface.addHorizontalSlider("Max Notch1 Freq", function handler(obj) { function setval(val) { obj.fHslider6 = val; } return setval; }(this), 800, 20, 10000, 1);
		ui_interface.declare("fHslider4", "4", "");
		ui_interface.declare("fHslider4", "style", "knob");
		ui_interface.addHorizontalSlider("Notch Freq Ratio: NotchFreq(n+1)/NotchFreq(n)", function handler(obj) { function setval(val) { obj.fHslider4 = val; } return setval; }(this), 1.5, 1.1, 4, 0.001);
		ui_interface.closeBox();
		ui_interface.declare("0", "3", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fHslider0", "unit", "dB");
		ui_interface.addHorizontalSlider("Phaser Output Level", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0, -60, 10, 0.1);
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
		var fSlow2 = (0.5 * (this.fCheckbox1?2:this.fHslider1));
		var fSlow3 = (1 - fSlow2);
		var fSlow4 = Math.exp((this.fConst1 * (0 - (3.14159 * this.fHslider2))));
		var fSlow5 = mydsp_faustpower2_f(fSlow4);
		var fSlow6 = this.fHslider3;
		var fSlow7 = (0 - (2 * fSlow4));
		var fSlow8 = this.fHslider4;
		var fSlow9 = this.fHslider5;
		var fSlow10 = (this.fConst2 * fSlow9);
		var fSlow11 = (0.5 * (0 - (this.fConst2 * (fSlow9 - max_f(fSlow9, this.fHslider6)))));
		var fSlow12 = (this.fConst2 * this.fHslider7);
		var fSlow13 = Math.sin(fSlow12);
		var fSlow14 = Math.cos(fSlow12);
		var fSlow15 = (0 - fSlow13);
		var fSlow16 = mydsp_faustpower2_f(fSlow8);
		var fSlow17 = mydsp_faustpower3_f(fSlow8);
		var fSlow18 = mydsp_faustpower4_f(fSlow8);
		var fSlow19 = (this.fCheckbox2?(0 - fSlow2):fSlow2);
		for (var i = 0; (i < count); i = (i + 1)) {
			var fTemp0 = input0[i];
			var fTemp1 = (iSlow0?0:fTemp0);
			this.iVec0[0] = 1;
			this.fRec5[0] = ((fSlow13 * this.fRec6[1]) + (fSlow14 * this.fRec5[1]));
			this.fRec6[0] = (((fSlow14 * this.fRec6[1]) + (fSlow15 * this.fRec5[1])) + (1 - this.iVec0[1]));
			var fTemp2 = (fSlow10 + (fSlow11 * (1 - this.fRec5[0])));
			var fTemp3 = (this.fRec4[1] * Math.cos((fSlow8 * fTemp2)));
			this.fRec4[0] = (((fSlow1 * fTemp1) + (fSlow6 * this.fRec0[1])) - ((fSlow7 * fTemp3) + (fSlow5 * this.fRec4[2])));
			var fTemp4 = (this.fRec3[1] * Math.cos((fSlow16 * fTemp2)));
			this.fRec3[0] = ((this.fRec4[2] + (fSlow7 * (fTemp3 - fTemp4))) + (fSlow5 * (this.fRec4[0] - this.fRec3[2])));
			var fTemp5 = (this.fRec2[1] * Math.cos((fSlow17 * fTemp2)));
			this.fRec2[0] = ((this.fRec3[2] + (fSlow7 * (fTemp4 - fTemp5))) + (fSlow5 * (this.fRec3[0] - this.fRec2[2])));
			var fTemp6 = (this.fRec1[1] * Math.cos((fSlow18 * fTemp2)));
			this.fRec1[0] = ((this.fRec2[2] + (fSlow7 * (fTemp5 - fTemp6))) + (fSlow5 * (this.fRec2[0] - this.fRec1[2])));
			this.fRec0[0] = ((fSlow5 * this.fRec1[0]) + ((fSlow7 * fTemp6) + this.fRec1[2]));
			output0[i] = (iSlow0?fTemp0:((fSlow1 * (fTemp1 * fSlow3)) + (this.fRec0[0] * fSlow19)));
			var fTemp7 = input1[i];
			var fTemp8 = (iSlow0?0:fTemp7);
			var fTemp9 = (fSlow10 + (fSlow11 * (1 - this.fRec6[0])));
			var fTemp10 = (this.fRec11[1] * Math.cos((fSlow8 * fTemp9)));
			this.fRec11[0] = (((fSlow1 * fTemp8) + (fSlow6 * this.fRec7[1])) - ((fSlow7 * fTemp10) + (fSlow5 * this.fRec11[2])));
			var fTemp11 = (this.fRec10[1] * Math.cos((fSlow16 * fTemp9)));
			this.fRec10[0] = ((this.fRec11[2] + (fSlow7 * (fTemp10 - fTemp11))) + (fSlow5 * (this.fRec11[0] - this.fRec10[2])));
			var fTemp12 = (this.fRec9[1] * Math.cos((fSlow17 * fTemp9)));
			this.fRec9[0] = ((this.fRec10[2] + (fSlow7 * (fTemp11 - fTemp12))) + (fSlow5 * (this.fRec10[0] - this.fRec9[2])));
			var fTemp13 = (this.fRec8[1] * Math.cos((fSlow18 * fTemp9)));
			this.fRec8[0] = ((this.fRec9[2] + (fSlow7 * (fTemp12 - fTemp13))) + (fSlow5 * (this.fRec9[0] - this.fRec8[2])));
			this.fRec7[0] = ((fSlow5 * this.fRec8[0]) + ((fSlow7 * fTemp13) + this.fRec8[2]));
			output1[i] = (iSlow0?fTemp7:((fSlow1 * (fTemp8 * fSlow3)) + (this.fRec7[0] * fSlow19)));
			this.iVec0[1] = this.iVec0[0];
			this.fRec5[1] = this.fRec5[0];
			this.fRec6[1] = this.fRec6[0];
			this.fRec4[2] = this.fRec4[1];
			this.fRec4[1] = this.fRec4[0];
			this.fRec3[2] = this.fRec3[1];
			this.fRec3[1] = this.fRec3[0];
			this.fRec2[2] = this.fRec2[1];
			this.fRec2[1] = this.fRec2[0];
			this.fRec1[2] = this.fRec1[1];
			this.fRec1[1] = this.fRec1[0];
			this.fRec0[1] = this.fRec0[0];
			this.fRec11[2] = this.fRec11[1];
			this.fRec11[1] = this.fRec11[0];
			this.fRec10[2] = this.fRec10[1];
			this.fRec10[1] = this.fRec10[0];
			this.fRec9[2] = this.fRec9[1];
			this.fRec9[1] = this.fRec9[0];
			this.fRec8[2] = this.fRec8[1];
			this.fRec8[1] = this.fRec8[0];
			this.fRec7[1] = this.fRec7[0];
			
		}
		
	}
	
}

