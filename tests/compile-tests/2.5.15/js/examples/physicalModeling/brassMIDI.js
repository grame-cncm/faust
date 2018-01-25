
this.min_f = function(dummy0, dummy1);
this.max_f = function(dummy0, dummy1);
this.mydsp_faustpower2_f = function(value) {
	return (value * value);
	
}
this.max_i = function(dummy0, dummy1);

function mydsp() {
	
	this.fHslider0;
	this.iRec6 = new Int32Array(2);
	this.fHslider1;
	this.iVec0 = new Int32Array(2);
	this.fRec14 = new Float32Array(2);
	this.fRec13 = new Float32Array(2);
	this.fRec15 = new Float32Array(2);
	this.fButton0;
	this.fHslider2;
	this.fVec1 = new Float32Array(2);
	this.fHslider3;
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fHslider4;
	this.fRec20 = new Float32Array(2);
	this.fHslider5;
	this.fConst2;
	this.fHslider6;
	this.fRec21 = new Float32Array(2);
	this.fRec22 = new Float32Array(2);
	this.fHslider7;
	this.fHslider8;
	this.fRec23 = new Float32Array(2);
	this.fHslider9;
	this.fRec24 = new Float32Array(2);
	this.fRec19 = new Float32Array(3);
	this.fVec2 = new Float32Array(2);
	this.fRec18 = new Float32Array(2);
	this.IOTA;
	this.fRec16 = new Float32Array(2048);
	this.fConst3;
	this.fConst4;
	this.fVec3 = new Float32Array(2);
	this.fRec11 = new Float32Array(2);
	this.fRec2 = new Float32Array(2048);
	this.fRec0 = new Float32Array(2);
	
	this.metadata = function(m) { 
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("description", "Simple MIDI-controllable brass instrument physical model with physical parameters.");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("license", "MIT");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "BrassMIDI");
		m.declare("oscillators.lib/name", "Faust Oscillator Library");
		m.declare("oscillators.lib/version", "0.0");
		m.declare("routes.lib/name", "Faust Signal Routing Library");
		m.declare("routes.lib/version", "0.0");
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
		this.fConst1 = (1000 / this.fConst0);
		this.fConst2 = (6.28319 / this.fConst0);
		this.fConst3 = (0.00882353 * this.fConst0);
		this.fConst4 = (0.5 * this.fConst0);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 0.5;
		this.fHslider1 = 0.5;
		this.fButton0 = 0;
		this.fHslider2 = 0;
		this.fHslider3 = 0.5;
		this.fHslider4 = 1;
		this.fHslider5 = 0.5;
		this.fHslider6 = 5;
		this.fHslider7 = 440;
		this.fHslider8 = 1;
		this.fHslider9 = 0.5;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.iRec6[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.iVec0[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec14[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec13[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec15[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fVec1[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			this.fRec20[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			this.fRec21[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			this.fRec22[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			this.fRec23[l9] = 0;
			
		}
		for (var l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			this.fRec24[l10] = 0;
			
		}
		for (var l11 = 0; (l11 < 3); l11 = (l11 + 1)) {
			this.fRec19[l11] = 0;
			
		}
		for (var l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			this.fVec2[l12] = 0;
			
		}
		for (var l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			this.fRec18[l13] = 0;
			
		}
		this.IOTA = 0;
		for (var l14 = 0; (l14 < 2048); l14 = (l14 + 1)) {
			this.fRec16[l14] = 0;
			
		}
		for (var l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			this.fVec3[l15] = 0;
			
		}
		for (var l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			this.fRec11[l16] = 0;
			
		}
		for (var l17 = 0; (l17 < 2048); l17 = (l17 + 1)) {
			this.fRec2[l17] = 0;
			
		}
		for (var l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			this.fRec0[l18] = 0;
			
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
		ui_interface.openVerticalBox("brass");
		ui_interface.declare("0", "0", "");
		ui_interface.openHorizontalBox("midi");
		ui_interface.declare("fHslider7", "0", "");
		ui_interface.declare("fHslider7", "style", "knob");
		ui_interface.addHorizontalSlider("freq", function handler(obj) { function setval(val) { obj.fHslider7 = val; } return setval; }(this), 440, 50, 1000, 0.01);
		ui_interface.declare("fHslider8", "1", "");
		ui_interface.declare("fHslider8", "hidden", "1");
		ui_interface.declare("fHslider8", "midi", "pitchwheel");
		ui_interface.declare("fHslider8", "style", "knob");
		ui_interface.addHorizontalSlider("bend", function handler(obj) { function setval(val) { obj.fHslider8 = val; } return setval; }(this), 1, 0, 10, 0.01);
		ui_interface.declare("fHslider3", "2", "");
		ui_interface.declare("fHslider3", "style", "knob");
		ui_interface.addHorizontalSlider("gain", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.declare("fHslider4", "3", "");
		ui_interface.declare("fHslider4", "style", "knob");
		ui_interface.addHorizontalSlider("envAttack", function handler(obj) { function setval(val) { obj.fHslider4 = val; } return setval; }(this), 1, 0, 30, 0.01);
		ui_interface.declare("fHslider2", "4", "");
		ui_interface.declare("fHslider2", "hidden", "1");
		ui_interface.declare("fHslider2", "midi", "ctrl 64");
		ui_interface.declare("fHslider2", "style", "knob");
		ui_interface.addHorizontalSlider("sustain", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 0, 0, 1, 1);
		ui_interface.closeBox();
		ui_interface.declare("0", "1", "");
		ui_interface.openHorizontalBox("otherParams");
		ui_interface.declare("fHslider9", "0", "");
		ui_interface.declare("fHslider9", "midi", "ctrl 1");
		ui_interface.declare("fHslider9", "style", "knob");
		ui_interface.addHorizontalSlider("lipsTension", function handler(obj) { function setval(val) { obj.fHslider9 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.declare("fHslider1", "1", "");
		ui_interface.declare("fHslider1", "style", "knob");
		ui_interface.addHorizontalSlider("mute", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.declare("fHslider6", "2", "");
		ui_interface.declare("fHslider6", "style", "knob");
		ui_interface.addHorizontalSlider("vibratoFreq", function handler(obj) { function setval(val) { obj.fHslider6 = val; } return setval; }(this), 5, 1, 10, 0.01);
		ui_interface.declare("fHslider5", "3", "");
		ui_interface.declare("fHslider5", "style", "knob");
		ui_interface.addHorizontalSlider("vibratoGain", function handler(obj) { function setval(val) { obj.fHslider5 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.declare("fHslider0", "4", "");
		ui_interface.declare("fHslider0", "style", "knob");
		ui_interface.addHorizontalSlider("outGain", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.closeBox();
		ui_interface.declare("fButton0", "2", "");
		ui_interface.addButton("gate", function handler(obj) { function setval(val) { obj.fButton0 = val; } return setval; }(this));
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = this.fHslider0;
		var fSlow1 = (0.001 * this.fHslider1);
		var fSlow2 = min_f(1, (this.fButton0 + this.fHslider2));
		var fSlow3 = Math.exp((0 - (this.fConst1 / this.fHslider4)));
		var fSlow4 = ((fSlow2 * this.fHslider3) * (1 - fSlow3));
		var fSlow5 = (0.04 * this.fHslider5);
		var fSlow6 = (this.fConst2 * this.fHslider6);
		var fSlow7 = Math.sin(fSlow6);
		var fSlow8 = Math.cos(fSlow6);
		var fSlow9 = (0 - fSlow7);
		var fSlow10 = this.fHslider7;
		var fSlow11 = (this.fConst2 * fSlow10);
		var fSlow12 = this.fHslider8;
		var iSlow13 = (fSlow2 == 0);
		var fSlow14 = (0.001 * this.fHslider9);
		var fSlow15 = (this.fConst4 / fSlow10);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iRec6[0] = 0;
			this.iVec0[0] = 1;
			this.fRec14[0] = (fSlow1 + (0.999 * this.fRec14[1]));
			this.fRec13[0] = ((this.fRec14[0] * this.fRec13[1]) + ((1 - this.fRec14[0]) * this.fRec11[1]));
			var fRec10 = (this.fRec13[0] + this.iRec6[1]);
			this.fRec15[0] = this.fRec0[1];
			this.fVec1[0] = fSlow2;
			this.fRec20[0] = (fSlow4 + (fSlow3 * this.fRec20[1]));
			this.fRec21[0] = ((fSlow7 * this.fRec22[1]) + (fSlow8 * this.fRec21[1]));
			this.fRec22[0] = (((fSlow8 * this.fRec22[1]) + (fSlow9 * this.fRec21[1])) + (1 - this.iVec0[1]));
			var fTemp0 = (this.fRec20[0] * ((fSlow5 * (this.fRec20[0] * this.fRec21[0])) + 1));
			var iTemp1 = ((fSlow2 == this.fVec1[1]) | iSlow13);
			this.fRec23[0] = ((fSlow12 * (1 - (0.999 * iTemp1))) + (0.999 * (iTemp1 * this.fRec23[1])));
			this.fRec24[0] = (fSlow14 + (0.999 * this.fRec24[1]));
			this.fRec19[0] = ((0.03 * ((0.3 * fTemp0) - (0.85 * this.fRec15[1]))) - ((this.fRec19[1] * (0 - (1.994 * Math.cos((fSlow11 * (this.fRec23[0] * Math.pow(4, ((2 * this.fRec24[0]) + -1)))))))) + (0.994009 * this.fRec19[2])));
			var fTemp2 = max_f(-1, min_f(1, mydsp_faustpower2_f(this.fRec19[0])));
			var fTemp3 = (0.85 * (this.fRec15[1] * (1 - fTemp2)));
			var fTemp4 = (0.3 * (fTemp0 * fTemp2));
			this.fVec2[0] = (fTemp4 + fTemp3);
			this.fRec18[0] = ((fTemp3 + ((0.995 * this.fRec18[1]) + fTemp4)) - this.fVec2[1]);
			this.fRec16[(this.IOTA & 2047)] = this.fRec18[0];
			var iRec17 = 0;
			var fTemp5 = (fSlow15 / this.fRec23[0]);
			var fTemp6 = (fTemp5 + -1.49999);
			var iTemp7 = fTemp6;
			var iTemp8 = (min_f(this.fConst3, max_i(0, iTemp7)) + 1);
			var fTemp9 = Math.floor(fTemp6);
			var fTemp10 = (fTemp5 + (-1 - fTemp9));
			var fTemp11 = (0 - fTemp10);
			var fTemp12 = (fTemp5 + (-2 - fTemp9));
			var fTemp13 = (0 - (0.5 * fTemp12));
			var fTemp14 = (fTemp5 + (-3 - fTemp9));
			var fTemp15 = (0 - (0.333333 * fTemp14));
			var fTemp16 = (fTemp5 + (-4 - fTemp9));
			var fTemp17 = (0 - (0.25 * fTemp16));
			var fTemp18 = (fTemp5 - fTemp9);
			var iTemp19 = (min_f(this.fConst3, max_i(0, (iTemp7 + 2))) + 1);
			var fTemp20 = (0 - fTemp14);
			var fTemp21 = (0 - (0.5 * fTemp16));
			var iTemp22 = (min_f(this.fConst3, max_i(0, (iTemp7 + 1))) + 1);
			var fTemp23 = (0 - fTemp12);
			var fTemp24 = (0 - (0.5 * fTemp14));
			var fTemp25 = (0 - (0.333333 * fTemp16));
			var fTemp26 = (fTemp10 * fTemp12);
			var iTemp27 = (min_f(this.fConst3, max_i(0, (iTemp7 + 3))) + 1);
			var fTemp28 = (0 - fTemp16);
			var fTemp29 = (fTemp26 * fTemp14);
			var iTemp30 = (min_f(this.fConst3, max_i(0, (iTemp7 + 4))) + 1);
			this.fVec3[0] = (((((this.fRec16[((this.IOTA - iTemp8) & 2047)] * fTemp11) * fTemp13) * fTemp15) * fTemp17) + (fTemp18 * ((((0.5 * (((fTemp10 * this.fRec16[((this.IOTA - iTemp19) & 2047)]) * fTemp20) * fTemp21)) + (((this.fRec16[((this.IOTA - iTemp22) & 2047)] * fTemp23) * fTemp24) * fTemp25)) + (0.166667 * ((fTemp26 * this.fRec16[((this.IOTA - iTemp27) & 2047)]) * fTemp28))) + (0.0416667 * (fTemp29 * this.fRec16[((this.IOTA - iTemp30) & 2047)])))));
			this.fRec11[0] = this.fVec3[1];
			var iRec12 = iRec17;
			var fRec7 = fRec10;
			var fRec8 = this.fRec11[0];
			var fRec9 = (this.fRec11[0] + iRec12);
			this.fRec2[(this.IOTA & 2047)] = fRec7;
			var fRec3 = (((((fTemp11 * fTemp13) * fTemp15) * fTemp17) * this.fRec2[((this.IOTA - iTemp8) & 2047)]) + (fTemp18 * (((0.166667 * ((fTemp26 * fTemp28) * this.fRec2[((this.IOTA - iTemp27) & 2047)])) + ((((fTemp23 * fTemp24) * fTemp25) * this.fRec2[((this.IOTA - iTemp22) & 2047)]) + (0.5 * (((fTemp10 * fTemp20) * fTemp21) * this.fRec2[((this.IOTA - iTemp19) & 2047)])))) + (0.0416667 * (fTemp29 * this.fRec2[((this.IOTA - iTemp30) & 2047)])))));
			var fRec4 = fRec8;
			var fRec5 = fRec9;
			this.fRec0[0] = fRec3;
			var fRec1 = fRec5;
			var fTemp31 = (fSlow0 * fRec1);
			output0[i] = fTemp31;
			output1[i] = fTemp31;
			this.iRec6[1] = this.iRec6[0];
			this.iVec0[1] = this.iVec0[0];
			this.fRec14[1] = this.fRec14[0];
			this.fRec13[1] = this.fRec13[0];
			this.fRec15[1] = this.fRec15[0];
			this.fVec1[1] = this.fVec1[0];
			this.fRec20[1] = this.fRec20[0];
			this.fRec21[1] = this.fRec21[0];
			this.fRec22[1] = this.fRec22[0];
			this.fRec23[1] = this.fRec23[0];
			this.fRec24[1] = this.fRec24[0];
			this.fRec19[2] = this.fRec19[1];
			this.fRec19[1] = this.fRec19[0];
			this.fVec2[1] = this.fVec2[0];
			this.fRec18[1] = this.fRec18[0];
			this.IOTA = (this.IOTA + 1);
			this.fVec3[1] = this.fVec3[0];
			this.fRec11[1] = this.fRec11[0];
			this.fRec0[1] = this.fRec0[0];
			
		}
		
	}
	
}

