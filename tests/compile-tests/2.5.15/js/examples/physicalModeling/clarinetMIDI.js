
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.mydsp_faustpower2_f = function(value) {
	return (value * value);
	
}
this.max_i = function(dummy0, dummy1);

function mydsp() {
	
	this.fHslider0;
	this.iRec6 = new Int32Array(2);
	this.fHslider1;
	this.iVec0 = new Int32Array(2);
	this.fRec13 = new Float32Array(2);
	this.fHslider2;
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fHslider3;
	this.fRec17 = new Float32Array(2);
	this.fRec18 = new Float32Array(2);
	this.fButton0;
	this.fHslider4;
	this.fVec1 = new Float32Array(2);
	this.fHslider5;
	this.fConst2;
	this.fHslider6;
	this.fRec19 = new Float32Array(2);
	this.fConst3;
	this.fConst4;
	this.fConst5;
	this.fConst6;
	this.iRec21 = new Int32Array(2);
	this.fConst7;
	this.fConst8;
	this.fConst9;
	this.fRec20 = new Float32Array(3);
	this.fRec14 = new Float32Array(2);
	this.fHslider7;
	this.IOTA;
	this.fRec15 = new Float32Array(2048);
	this.fConst10;
	this.fConst11;
	this.fHslider8;
	this.fHslider9;
	this.fRec22 = new Float32Array(2);
	this.fVec2 = new Float32Array(2);
	this.fRec11 = new Float32Array(2);
	this.fRec2 = new Float32Array(2048);
	this.fRec0 = new Float32Array(2);
	
	this.metadata = function(m) { 
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("description", "Simple MIDI-controllable clarinet physical model with physical parameters.");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("license", "MIT");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "ClarinetMIDI");
		m.declare("noises.lib/name", "Faust Noise Generator Library");
		m.declare("noises.lib/version", "0.0");
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
		this.fConst1 = (6.28319 / this.fConst0);
		this.fConst2 = (1000 / this.fConst0);
		this.fConst3 = Math.tan((6283.19 / this.fConst0));
		this.fConst4 = (1 / this.fConst3);
		this.fConst5 = (((this.fConst4 + 1.41421) / this.fConst3) + 1);
		this.fConst6 = (0.05 / this.fConst5);
		this.fConst7 = (1 / this.fConst5);
		this.fConst8 = (2 * (1 - (1 / mydsp_faustpower2_f(this.fConst3))));
		this.fConst9 = (((this.fConst4 + -1.41421) / this.fConst3) + 1);
		this.fConst10 = (0.00882353 * this.fConst0);
		this.fConst11 = (0.00147059 * this.fConst0);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 0.5;
		this.fHslider1 = 0.5;
		this.fHslider2 = 0.25;
		this.fHslider3 = 5;
		this.fButton0 = 0;
		this.fHslider4 = 0;
		this.fHslider5 = 0.6;
		this.fHslider6 = 1;
		this.fHslider7 = 0.5;
		this.fHslider8 = 440;
		this.fHslider9 = 1;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.iRec6[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.iVec0[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec13[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec17[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec18[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fVec1[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			this.fRec19[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			this.iRec21[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
			this.fRec20[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			this.fRec14[l9] = 0;
			
		}
		this.IOTA = 0;
		for (var l10 = 0; (l10 < 2048); l10 = (l10 + 1)) {
			this.fRec15[l10] = 0;
			
		}
		for (var l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			this.fRec22[l11] = 0;
			
		}
		for (var l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			this.fVec2[l12] = 0;
			
		}
		for (var l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			this.fRec11[l13] = 0;
			
		}
		for (var l14 = 0; (l14 < 2048); l14 = (l14 + 1)) {
			this.fRec2[l14] = 0;
			
		}
		for (var l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			this.fRec0[l15] = 0;
			
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
		ui_interface.openVerticalBox("clarinet");
		ui_interface.declare("0", "0", "");
		ui_interface.openHorizontalBox("midi");
		ui_interface.declare("fHslider8", "0", "");
		ui_interface.declare("fHslider8", "style", "knob");
		ui_interface.addHorizontalSlider("freq", function handler(obj) { function setval(val) { obj.fHslider8 = val; } return setval; }(this), 440, 50, 1000, 0.01);
		ui_interface.declare("fHslider9", "1", "");
		ui_interface.declare("fHslider9", "hidden", "1");
		ui_interface.declare("fHslider9", "midi", "pitchwheel");
		ui_interface.declare("fHslider9", "style", "knob");
		ui_interface.addHorizontalSlider("bend", function handler(obj) { function setval(val) { obj.fHslider9 = val; } return setval; }(this), 1, 0, 10, 0.01);
		ui_interface.declare("fHslider5", "2", "");
		ui_interface.declare("fHslider5", "style", "knob");
		ui_interface.addHorizontalSlider("gain", function handler(obj) { function setval(val) { obj.fHslider5 = val; } return setval; }(this), 0.6, 0, 1, 0.01);
		ui_interface.declare("fHslider6", "3", "");
		ui_interface.declare("fHslider6", "style", "knob");
		ui_interface.addHorizontalSlider("envAttack", function handler(obj) { function setval(val) { obj.fHslider6 = val; } return setval; }(this), 1, 0, 30, 0.01);
		ui_interface.declare("fHslider4", "4", "");
		ui_interface.declare("fHslider4", "hidden", "1");
		ui_interface.declare("fHslider4", "midi", "ctrl 64");
		ui_interface.declare("fHslider4", "style", "knob");
		ui_interface.addHorizontalSlider("sustain", function handler(obj) { function setval(val) { obj.fHslider4 = val; } return setval; }(this), 0, 0, 1, 1);
		ui_interface.closeBox();
		ui_interface.declare("0", "1", "");
		ui_interface.openHorizontalBox("otherParams");
		ui_interface.declare("fHslider7", "0", "");
		ui_interface.declare("fHslider7", "midi", "ctrl 1");
		ui_interface.declare("fHslider7", "style", "knob");
		ui_interface.addHorizontalSlider("reedStiffness", function handler(obj) { function setval(val) { obj.fHslider7 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.declare("fHslider1", "1", "");
		ui_interface.declare("fHslider1", "midi", "ctrl 3");
		ui_interface.declare("fHslider1", "style", "knob");
		ui_interface.addHorizontalSlider("bellOpening", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.declare("fHslider3", "2", "");
		ui_interface.declare("fHslider3", "style", "knob");
		ui_interface.addHorizontalSlider("vibratoFreq", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 5, 1, 10, 0.01);
		ui_interface.declare("fHslider2", "3", "");
		ui_interface.declare("fHslider2", "style", "knob");
		ui_interface.addHorizontalSlider("vibratoGain", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 0.25, 0, 1, 0.01);
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
		var fSlow1 = this.fHslider1;
		var fSlow2 = (1 - fSlow1);
		var fSlow3 = (0.01 * this.fHslider2);
		var fSlow4 = (this.fConst1 * this.fHslider3);
		var fSlow5 = Math.sin(fSlow4);
		var fSlow6 = Math.cos(fSlow4);
		var fSlow7 = (0 - fSlow5);
		var fSlow8 = min_f(1, (this.fButton0 + this.fHslider4));
		var fSlow9 = Math.exp((0 - (this.fConst2 / this.fHslider6)));
		var fSlow10 = ((fSlow8 * this.fHslider5) * (1 - fSlow9));
		var fSlow11 = ((0.26 * this.fHslider7) + -0.44);
		var fSlow12 = (170 / this.fHslider8);
		var fSlow13 = this.fHslider9;
		var iSlow14 = (fSlow8 == 0);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iRec6[0] = 0;
			this.iVec0[0] = 1;
			this.fRec13[0] = ((fSlow1 * this.fRec13[1]) + (fSlow2 * this.fRec11[1]));
			var fRec10 = (this.fRec13[0] + this.iRec6[1]);
			this.fRec17[0] = ((fSlow5 * this.fRec18[1]) + (fSlow6 * this.fRec17[1]));
			this.fRec18[0] = (((fSlow6 * this.fRec18[1]) + (fSlow7 * this.fRec17[1])) + (1 - this.iVec0[1]));
			var fTemp0 = (fSlow3 * this.fRec17[0]);
			this.fVec1[0] = fSlow8;
			this.fRec19[0] = (fSlow10 + (fSlow9 * this.fRec19[1]));
			this.iRec21[0] = ((1103515245 * this.iRec21[1]) + 12345);
			this.fRec20[0] = ((4.65661e-10 * this.iRec21[0]) - (this.fConst7 * ((this.fConst8 * this.fRec20[1]) + (this.fConst9 * this.fRec20[2]))));
			var fTemp1 = (this.fRec19[0] * ((this.fConst6 * (this.fRec20[2] + (this.fRec20[0] + (2 * this.fRec20[1])))) + 1));
			this.fRec14[0] = ((this.fRec0[1] + fTemp0) + fTemp1);
			var fTemp2 = (0 - this.fRec14[1]);
			this.fRec15[(this.IOTA & 2047)] = ((fTemp0 + fTemp1) + (fTemp2 * max_f(-1, min_f(1, ((fSlow11 * fTemp2) + 0.7)))));
			var iRec16 = 0;
			var iTemp3 = ((fSlow8 == this.fVec1[1]) | iSlow14);
			this.fRec22[0] = ((fSlow13 * (1 - (0.999 * iTemp3))) + (0.999 * (iTemp3 * this.fRec22[1])));
			var fTemp4 = (this.fConst11 * ((fSlow12 / (this.fRec22[0] * ((fSlow3 * (this.fRec19[0] * this.fRec17[0])) + 1))) + -0.05));
			var fTemp5 = (fTemp4 + -1.49999);
			var iTemp6 = fTemp5;
			var iTemp7 = (min_f(this.fConst10, max_i(0, iTemp6)) + 1);
			var fTemp8 = Math.floor(fTemp5);
			var fTemp9 = (fTemp4 + (-1 - fTemp8));
			var fTemp10 = (0 - fTemp9);
			var fTemp11 = (fTemp4 + (-2 - fTemp8));
			var fTemp12 = (0 - (0.5 * fTemp11));
			var fTemp13 = (fTemp4 + (-3 - fTemp8));
			var fTemp14 = (0 - (0.333333 * fTemp13));
			var fTemp15 = (fTemp4 + (-4 - fTemp8));
			var fTemp16 = (0 - (0.25 * fTemp15));
			var fTemp17 = (fTemp4 - fTemp8);
			var iTemp18 = (min_f(this.fConst10, max_i(0, (iTemp6 + 2))) + 1);
			var fTemp19 = (0 - fTemp13);
			var fTemp20 = (0 - (0.5 * fTemp15));
			var iTemp21 = (min_f(this.fConst10, max_i(0, (iTemp6 + 1))) + 1);
			var fTemp22 = (0 - fTemp11);
			var fTemp23 = (0 - (0.5 * fTemp13));
			var fTemp24 = (0 - (0.333333 * fTemp15));
			var fTemp25 = (fTemp9 * fTemp11);
			var iTemp26 = (min_f(this.fConst10, max_i(0, (iTemp6 + 3))) + 1);
			var fTemp27 = (0 - fTemp15);
			var fTemp28 = (fTemp25 * fTemp13);
			var iTemp29 = (min_f(this.fConst10, max_i(0, (iTemp6 + 4))) + 1);
			this.fVec2[0] = (((((this.fRec15[((this.IOTA - iTemp7) & 2047)] * fTemp10) * fTemp12) * fTemp14) * fTemp16) + (fTemp17 * ((((0.5 * (((fTemp9 * this.fRec15[((this.IOTA - iTemp18) & 2047)]) * fTemp19) * fTemp20)) + (((this.fRec15[((this.IOTA - iTemp21) & 2047)] * fTemp22) * fTemp23) * fTemp24)) + (0.166667 * ((fTemp25 * this.fRec15[((this.IOTA - iTemp26) & 2047)]) * fTemp27))) + (0.0416667 * (fTemp28 * this.fRec15[((this.IOTA - iTemp29) & 2047)])))));
			this.fRec11[0] = this.fVec2[1];
			var iRec12 = iRec16;
			var fRec7 = fRec10;
			var fRec8 = this.fRec11[0];
			var fRec9 = (this.fRec11[0] + iRec12);
			this.fRec2[(this.IOTA & 2047)] = fRec7;
			var fRec3 = (((((fTemp10 * fTemp12) * fTemp14) * fTemp16) * this.fRec2[((this.IOTA - iTemp7) & 2047)]) + (fTemp17 * (((0.166667 * ((fTemp25 * fTemp27) * this.fRec2[((this.IOTA - iTemp26) & 2047)])) + ((((fTemp22 * fTemp23) * fTemp24) * this.fRec2[((this.IOTA - iTemp21) & 2047)]) + (0.5 * (((fTemp9 * fTemp19) * fTemp20) * this.fRec2[((this.IOTA - iTemp18) & 2047)])))) + (0.0416667 * (fTemp28 * this.fRec2[((this.IOTA - iTemp29) & 2047)])))));
			var fRec4 = fRec8;
			var fRec5 = fRec9;
			this.fRec0[0] = fRec3;
			var fRec1 = fRec5;
			var fTemp30 = (fSlow0 * fRec1);
			output0[i] = fTemp30;
			output1[i] = fTemp30;
			this.iRec6[1] = this.iRec6[0];
			this.iVec0[1] = this.iVec0[0];
			this.fRec13[1] = this.fRec13[0];
			this.fRec17[1] = this.fRec17[0];
			this.fRec18[1] = this.fRec18[0];
			this.fVec1[1] = this.fVec1[0];
			this.fRec19[1] = this.fRec19[0];
			this.iRec21[1] = this.iRec21[0];
			this.fRec20[2] = this.fRec20[1];
			this.fRec20[1] = this.fRec20[0];
			this.fRec14[1] = this.fRec14[0];
			this.IOTA = (this.IOTA + 1);
			this.fRec22[1] = this.fRec22[0];
			this.fVec2[1] = this.fVec2[0];
			this.fRec11[1] = this.fRec11[0];
			this.fRec0[1] = this.fRec0[0];
			
		}
		
	}
	
}

