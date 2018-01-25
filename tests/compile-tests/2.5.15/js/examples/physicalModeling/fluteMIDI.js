
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.mydsp_faustpower2_f = function(value) {
	return (value * value);
	
}
this.max_i = function(dummy0, dummy1);

function mydsp() {
	
	this.fHslider0;
	this.iRec15 = new Int32Array(2);
	this.iVec0 = new Int32Array(2);
	this.fRec22 = new Float32Array(2);
	this.fHslider1;
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fHslider2;
	this.fRec23 = new Float32Array(2);
	this.fRec24 = new Float32Array(2);
	this.fButton0;
	this.fHslider3;
	this.fVec1 = new Float32Array(2);
	this.fHslider4;
	this.fConst2;
	this.fHslider5;
	this.fRec25 = new Float32Array(2);
	this.fConst3;
	this.fConst4;
	this.fConst5;
	this.fConst6;
	this.iRec27 = new Int32Array(2);
	this.fConst7;
	this.fConst8;
	this.fConst9;
	this.fRec26 = new Float32Array(3);
	this.fRec28 = new Float32Array(2);
	this.IOTA;
	this.fRec29 = new Float32Array(2048);
	this.fConst10;
	this.fConst11;
	this.fHslider6;
	this.fHslider7;
	this.fRec31 = new Float32Array(2);
	this.fHslider8;
	this.fRec32 = new Float32Array(2);
	this.fVec2 = new Float32Array(2);
	this.fVec3 = new Float32Array(2048);
	this.fVec4 = new Float32Array(2);
	this.fRec20 = new Float32Array(2);
	this.fRec11 = new Float32Array(2048);
	this.fRec7 = new Float32Array(2);
	this.fRec3 = new Float32Array(2048);
	this.fRec1 = new Float32Array(2);
	this.fRec2 = new Float32Array(2);
	this.fRec0 = new Float32Array(2);
	
	this.metadata = function(m) { 
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("description", "Simple MIDI-controllable flute physical model with physical parameters.");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("license", "MIT");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "FluteMIDI");
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
		this.fHslider2 = 5;
		this.fButton0 = 0;
		this.fHslider3 = 0;
		this.fHslider4 = 0.9;
		this.fHslider5 = 1;
		this.fHslider6 = 440;
		this.fHslider7 = 1;
		this.fHslider8 = 0.5;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.iRec15[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.iVec0[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec22[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec23[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec24[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fVec1[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			this.fRec25[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			this.iRec27[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
			this.fRec26[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			this.fRec28[l9] = 0;
			
		}
		this.IOTA = 0;
		for (var l10 = 0; (l10 < 2048); l10 = (l10 + 1)) {
			this.fRec29[l10] = 0;
			
		}
		for (var l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			this.fRec31[l11] = 0;
			
		}
		for (var l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			this.fRec32[l12] = 0;
			
		}
		for (var l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			this.fVec2[l13] = 0;
			
		}
		for (var l14 = 0; (l14 < 2048); l14 = (l14 + 1)) {
			this.fVec3[l14] = 0;
			
		}
		for (var l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			this.fVec4[l15] = 0;
			
		}
		for (var l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			this.fRec20[l16] = 0;
			
		}
		for (var l17 = 0; (l17 < 2048); l17 = (l17 + 1)) {
			this.fRec11[l17] = 0;
			
		}
		for (var l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			this.fRec7[l18] = 0;
			
		}
		for (var l19 = 0; (l19 < 2048); l19 = (l19 + 1)) {
			this.fRec3[l19] = 0;
			
		}
		for (var l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			this.fRec1[l20] = 0;
			
		}
		for (var l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			this.fRec2[l21] = 0;
			
		}
		for (var l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			this.fRec0[l22] = 0;
			
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
		ui_interface.openVerticalBox("flute");
		ui_interface.declare("0", "0", "");
		ui_interface.openHorizontalBox("midi");
		ui_interface.declare("fHslider6", "0", "");
		ui_interface.declare("fHslider6", "style", "knob");
		ui_interface.addHorizontalSlider("freq", function handler(obj) { function setval(val) { obj.fHslider6 = val; } return setval; }(this), 440, 50, 1000, 0.01);
		ui_interface.declare("fHslider7", "1", "");
		ui_interface.declare("fHslider7", "hidden", "1");
		ui_interface.declare("fHslider7", "midi", "pitchwheel");
		ui_interface.declare("fHslider7", "style", "knob");
		ui_interface.addHorizontalSlider("bend", function handler(obj) { function setval(val) { obj.fHslider7 = val; } return setval; }(this), 1, 0, 10, 0.01);
		ui_interface.declare("fHslider4", "2", "");
		ui_interface.declare("fHslider4", "style", "knob");
		ui_interface.addHorizontalSlider("gain", function handler(obj) { function setval(val) { obj.fHslider4 = val; } return setval; }(this), 0.9, 0, 1, 0.01);
		ui_interface.declare("fHslider5", "3", "");
		ui_interface.declare("fHslider5", "style", "knob");
		ui_interface.addHorizontalSlider("envAttack", function handler(obj) { function setval(val) { obj.fHslider5 = val; } return setval; }(this), 1, 0, 30, 0.01);
		ui_interface.declare("fHslider3", "4", "");
		ui_interface.declare("fHslider3", "hidden", "1");
		ui_interface.declare("fHslider3", "midi", "ctrl 64");
		ui_interface.declare("fHslider3", "style", "knob");
		ui_interface.addHorizontalSlider("sustain", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 0, 0, 1, 1);
		ui_interface.closeBox();
		ui_interface.declare("0", "1", "");
		ui_interface.openHorizontalBox("otherParams");
		ui_interface.declare("fHslider8", "0", "");
		ui_interface.declare("fHslider8", "midi", "ctrl 1");
		ui_interface.declare("fHslider8", "style", "knob");
		ui_interface.addHorizontalSlider("mouthPosition", function handler(obj) { function setval(val) { obj.fHslider8 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.declare("fHslider2", "1", "");
		ui_interface.declare("fHslider2", "style", "knob");
		ui_interface.addHorizontalSlider("vibratoFreq", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 5, 1, 10, 0.01);
		ui_interface.declare("fHslider1", "2", "");
		ui_interface.declare("fHslider1", "style", "knob");
		ui_interface.addHorizontalSlider("vibratoGain", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.declare("fHslider0", "3", "");
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
		var fSlow1 = (0.04 * this.fHslider1);
		var fSlow2 = (this.fConst1 * this.fHslider2);
		var fSlow3 = Math.sin(fSlow2);
		var fSlow4 = Math.cos(fSlow2);
		var fSlow5 = (0 - fSlow3);
		var fSlow6 = min_f(1, (this.fButton0 + this.fHslider3));
		var fSlow7 = Math.exp((0 - (this.fConst2 / this.fHslider5)));
		var fSlow8 = ((fSlow6 * this.fHslider4) * (1 - fSlow7));
		var fSlow9 = (340 / this.fHslider6);
		var fSlow10 = this.fHslider7;
		var iSlow11 = (fSlow6 == 0);
		var fSlow12 = (0.001 * this.fHslider8);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iRec15[0] = 0;
			this.iVec0[0] = 1;
			this.fRec22[0] = ((0.7 * this.fRec22[1]) + (0.285 * this.fRec20[1]));
			var fRec19 = (this.fRec22[0] + this.iRec15[1]);
			this.fRec23[0] = ((fSlow3 * this.fRec24[1]) + (fSlow4 * this.fRec23[1]));
			this.fRec24[0] = (((fSlow4 * this.fRec24[1]) + (fSlow5 * this.fRec23[1])) + (1 - this.iVec0[1]));
			this.fVec1[0] = fSlow6;
			this.fRec25[0] = (fSlow8 + (fSlow7 * this.fRec25[1]));
			this.iRec27[0] = ((1103515245 * this.iRec27[1]) + 12345);
			this.fRec26[0] = ((4.65661e-10 * this.iRec27[0]) - (this.fConst7 * ((this.fConst8 * this.fRec26[1]) + (this.fConst9 * this.fRec26[2]))));
			this.fRec28[0] = this.fRec1[1];
			this.fRec29[(this.IOTA & 2047)] = (0.95 * this.fRec28[1]);
			var iRec30 = 0;
			var iTemp0 = ((fSlow6 == this.fVec1[1]) | iSlow11);
			this.fRec31[0] = ((fSlow10 * (1 - (0.999 * iTemp0))) + (0.999 * (iTemp0 * this.fRec31[1])));
			var fTemp1 = ((fSlow9 / this.fRec31[0]) + 0.27);
			this.fRec32[0] = (fSlow12 + (0.999 * this.fRec32[1]));
			var fTemp2 = (0.4 * (this.fRec32[0] + -0.5));
			var fTemp3 = (this.fConst11 * (fTemp1 * (fTemp2 + 0.27)));
			var fTemp4 = (fTemp3 + -1.49999);
			var iTemp5 = fTemp4;
			var iTemp6 = (min_f(this.fConst10, max_i(0, iTemp5)) + 1);
			var fTemp7 = Math.floor(fTemp4);
			var fTemp8 = (fTemp3 + (-1 - fTemp7));
			var fTemp9 = (0 - fTemp8);
			var fTemp10 = (fTemp3 + (-2 - fTemp7));
			var fTemp11 = (0 - (0.5 * fTemp10));
			var fTemp12 = (fTemp3 + (-3 - fTemp7));
			var fTemp13 = (0 - (0.333333 * fTemp12));
			var fTemp14 = (fTemp3 + (-4 - fTemp7));
			var fTemp15 = (0 - (0.25 * fTemp14));
			var fTemp16 = (fTemp3 - fTemp7);
			var iTemp17 = (min_f(this.fConst10, max_i(0, (iTemp5 + 2))) + 1);
			var fTemp18 = (0 - fTemp12);
			var fTemp19 = (0 - (0.5 * fTemp14));
			var iTemp20 = (min_f(this.fConst10, max_i(0, (iTemp5 + 1))) + 1);
			var fTemp21 = (0 - fTemp10);
			var fTemp22 = (0 - (0.5 * fTemp12));
			var fTemp23 = (0 - (0.333333 * fTemp14));
			var fTemp24 = (fTemp8 * fTemp10);
			var iTemp25 = (min_f(this.fConst10, max_i(0, (iTemp5 + 3))) + 1);
			var fTemp26 = (0 - fTemp14);
			var fTemp27 = (fTemp24 * fTemp12);
			var iTemp28 = (min_f(this.fConst10, max_i(0, (iTemp5 + 4))) + 1);
			this.fVec2[0] = (((((this.fRec29[((this.IOTA - iTemp6) & 2047)] * fTemp9) * fTemp11) * fTemp13) * fTemp15) + (fTemp16 * ((((0.5 * (((fTemp8 * this.fRec29[((this.IOTA - iTemp17) & 2047)]) * fTemp18) * fTemp19)) + (((this.fRec29[((this.IOTA - iTemp20) & 2047)] * fTemp21) * fTemp22) * fTemp23)) + (0.166667 * ((fTemp24 * this.fRec29[((this.IOTA - iTemp25) & 2047)]) * fTemp26))) + (0.0416667 * (fTemp27 * this.fRec29[((this.IOTA - iTemp28) & 2047)])))));
			var fTemp29 = (((fSlow1 * this.fRec23[0]) + (this.fRec25[0] * ((this.fConst6 * (this.fRec26[2] + (this.fRec26[0] + (2 * this.fRec26[1])))) + 1))) - (0.5 * this.fVec2[1]));
			var fTemp30 = ((0.5 * this.fRec7[1]) + max_f(-1, min_f(1, (fTemp29 * (mydsp_faustpower2_f(fTemp29) + -1)))));
			this.fVec3[(this.IOTA & 2047)] = fTemp30;
			var fTemp31 = (this.fConst11 * (fTemp1 * (0.73 - fTemp2)));
			var fTemp32 = (fTemp31 + -1.49999);
			var iTemp33 = fTemp32;
			var iTemp34 = (min_f(this.fConst10, max_i(0, iTemp33)) + 1);
			var fTemp35 = Math.floor(fTemp32);
			var fTemp36 = (fTemp31 + (-1 - fTemp35));
			var fTemp37 = (0 - fTemp36);
			var fTemp38 = (fTemp31 + (-2 - fTemp35));
			var fTemp39 = (0 - (0.5 * fTemp38));
			var fTemp40 = (fTemp31 + (-3 - fTemp35));
			var fTemp41 = (0 - (0.333333 * fTemp40));
			var fTemp42 = (fTemp31 + (-4 - fTemp35));
			var fTemp43 = (0 - (0.25 * fTemp42));
			var fTemp44 = (fTemp31 - fTemp35);
			var iTemp45 = (min_f(this.fConst10, max_i(0, (iTemp33 + 2))) + 1);
			var fTemp46 = (0 - fTemp40);
			var fTemp47 = (0 - (0.5 * fTemp42));
			var iTemp48 = (min_f(this.fConst10, max_i(0, (iTemp33 + 1))) + 1);
			var fTemp49 = (0 - fTemp38);
			var fTemp50 = (0 - (0.5 * fTemp40));
			var fTemp51 = (0 - (0.333333 * fTemp42));
			var fTemp52 = (fTemp36 * fTemp38);
			var iTemp53 = (min_f(this.fConst10, max_i(0, (iTemp33 + 3))) + 1);
			var fTemp54 = (0 - fTemp42);
			var fTemp55 = (fTemp52 * fTemp40);
			var iTemp56 = (min_f(this.fConst10, max_i(0, (iTemp33 + 4))) + 1);
			this.fVec4[0] = (((((this.fVec3[((this.IOTA - iTemp34) & 2047)] * fTemp37) * fTemp39) * fTemp41) * fTemp43) + (fTemp44 * ((((0.5 * (((fTemp36 * this.fVec3[((this.IOTA - iTemp45) & 2047)]) * fTemp46) * fTemp47)) + (((this.fVec3[((this.IOTA - iTemp48) & 2047)] * fTemp49) * fTemp50) * fTemp51)) + (0.166667 * ((fTemp52 * this.fVec3[((this.IOTA - iTemp53) & 2047)]) * fTemp54))) + (0.0416667 * (fTemp55 * this.fVec3[((this.IOTA - iTemp56) & 2047)])))));
			this.fRec20[0] = this.fVec4[1];
			var iRec21 = iRec30;
			var fRec16 = fRec19;
			var fRec17 = this.fRec20[0];
			var fRec18 = (this.fRec20[0] + iRec21);
			this.fRec11[(this.IOTA & 2047)] = fRec16;
			var fRec12 = (((((fTemp37 * fTemp39) * fTemp41) * fTemp43) * this.fRec11[((this.IOTA - iTemp34) & 2047)]) + (fTemp44 * (((0.166667 * ((fTemp52 * fTemp54) * this.fRec11[((this.IOTA - iTemp53) & 2047)])) + ((((fTemp49 * fTemp50) * fTemp51) * this.fRec11[((this.IOTA - iTemp48) & 2047)]) + (0.5 * (((fTemp36 * fTemp46) * fTemp47) * this.fRec11[((this.IOTA - iTemp45) & 2047)])))) + (0.0416667 * (fTemp55 * this.fRec11[((this.IOTA - iTemp56) & 2047)])))));
			var fRec13 = fRec17;
			var fRec14 = fRec18;
			this.fRec7[0] = fRec12;
			var fRec8 = this.fRec7[1];
			var fRec9 = fRec13;
			var fRec10 = fRec14;
			this.fRec3[(this.IOTA & 2047)] = fRec8;
			var fRec4 = (((((fTemp9 * fTemp11) * fTemp13) * fTemp15) * this.fRec3[((this.IOTA - iTemp6) & 2047)]) + (fTemp16 * (((0.166667 * ((fTemp24 * fTemp26) * this.fRec3[((this.IOTA - iTemp25) & 2047)])) + ((((fTemp21 * fTemp22) * fTemp23) * this.fRec3[((this.IOTA - iTemp20) & 2047)]) + (0.5 * (((fTemp8 * fTemp18) * fTemp19) * this.fRec3[((this.IOTA - iTemp17) & 2047)])))) + (0.0416667 * (fTemp27 * this.fRec3[((this.IOTA - iTemp28) & 2047)])))));
			var fRec5 = fRec9;
			var fRec6 = fRec10;
			this.fRec1[0] = fRec4;
			this.fRec2[0] = fRec6;
			this.fRec0[0] = ((this.fRec2[0] + (0.995 * this.fRec0[1])) - this.fRec2[1]);
			var fTemp57 = (fSlow0 * this.fRec0[0]);
			output0[i] = fTemp57;
			output1[i] = fTemp57;
			this.iRec15[1] = this.iRec15[0];
			this.iVec0[1] = this.iVec0[0];
			this.fRec22[1] = this.fRec22[0];
			this.fRec23[1] = this.fRec23[0];
			this.fRec24[1] = this.fRec24[0];
			this.fVec1[1] = this.fVec1[0];
			this.fRec25[1] = this.fRec25[0];
			this.iRec27[1] = this.iRec27[0];
			this.fRec26[2] = this.fRec26[1];
			this.fRec26[1] = this.fRec26[0];
			this.fRec28[1] = this.fRec28[0];
			this.IOTA = (this.IOTA + 1);
			this.fRec31[1] = this.fRec31[0];
			this.fRec32[1] = this.fRec32[0];
			this.fVec2[1] = this.fVec2[0];
			this.fVec4[1] = this.fVec4[0];
			this.fRec20[1] = this.fRec20[0];
			this.fRec7[1] = this.fRec7[0];
			this.fRec1[1] = this.fRec1[0];
			this.fRec2[1] = this.fRec2[0];
			this.fRec0[1] = this.fRec0[0];
			
		}
		
	}
	
}

