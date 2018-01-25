
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.max_i = function(dummy0, dummy1);
this.mydsp_faustpower4_f = function(value) {
	return (((value * value) * value) * value);
	
}
this.mydsp_faustpower2_f = function(value) {
	return (value * value);
	
}

function mydsp() {
	
	this.fHslider0;
	this.iRec10 = new Int32Array(2);
	this.iVec0 = new Int32Array(2);
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fConst2;
	this.fConst3;
	this.fConst4;
	this.fConst5;
	this.fHslider1;
	this.fRec26 = new Float32Array(2);
	this.fHslider2;
	this.fHslider3;
	this.fButton0;
	this.fHslider4;
	this.fVec1 = new Float32Array(2);
	this.fRec27 = new Float32Array(2);
	this.fHslider5;
	this.fConst6;
	this.fHslider6;
	this.fRec28 = new Float32Array(2);
	this.fRec29 = new Float32Array(2);
	this.fHslider7;
	this.fConst7;
	this.fHslider8;
	this.fRec30 = new Float32Array(2);
	this.fRec22 = new Float32Array(2);
	this.fRec31 = new Float32Array(4);
	this.IOTA;
	this.fRec32 = new Float32Array(2048);
	this.fVec2 = new Float32Array(2);
	this.fHslider9;
	this.fRec34 = new Float32Array(2);
	this.fVec3 = new Float32Array(2048);
	this.fRec18 = new Float32Array(2048);
	this.fRec20 = new Float32Array(2);
	this.fRec16 = new Float32Array(4);
	this.fConst8;
	this.fConst9;
	this.fRec14 = new Float32Array(3);
	this.fConst10;
	this.iRec6 = new Int32Array(2);
	this.fRec2 = new Float32Array(2048);
	this.fRec0 = new Float32Array(2);
	
	this.metadata = function(m) { 
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("description", "Simple MIDI-controllable violin physical model.");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("license", "MIT");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "ViolinMidi");
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
		this.fConst1 = Math.tan((1570.8 / this.fConst0));
		this.fConst2 = (1 / this.fConst1);
		this.fConst3 = (1 / (((this.fConst2 + 0.5) / this.fConst1) + 1));
		this.fConst4 = (0.00882353 * this.fConst0);
		this.fConst5 = (0.00147059 * this.fConst0);
		this.fConst6 = (6.28319 / this.fConst0);
		this.fConst7 = (1000 / this.fConst0);
		this.fConst8 = (((this.fConst2 + -0.5) / this.fConst1) + 1);
		this.fConst9 = (2 * (1 - (1 / mydsp_faustpower2_f(this.fConst1))));
		this.fConst10 = (0 - this.fConst2);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 0.5;
		this.fHslider1 = 0.7;
		this.fHslider2 = 440;
		this.fHslider3 = 1;
		this.fButton0 = 0;
		this.fHslider4 = 0;
		this.fHslider5 = 0.5;
		this.fHslider6 = 6;
		this.fHslider7 = 0.6;
		this.fHslider8 = 1;
		this.fHslider9 = 0.5;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.iRec10[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.iVec0[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec26[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fVec1[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec27[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fRec28[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			this.fRec29[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			this.fRec30[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			this.fRec22[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 4); l9 = (l9 + 1)) {
			this.fRec31[l9] = 0;
			
		}
		this.IOTA = 0;
		for (var l10 = 0; (l10 < 2048); l10 = (l10 + 1)) {
			this.fRec32[l10] = 0;
			
		}
		for (var l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			this.fVec2[l11] = 0;
			
		}
		for (var l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			this.fRec34[l12] = 0;
			
		}
		for (var l13 = 0; (l13 < 2048); l13 = (l13 + 1)) {
			this.fVec3[l13] = 0;
			
		}
		for (var l14 = 0; (l14 < 2048); l14 = (l14 + 1)) {
			this.fRec18[l14] = 0;
			
		}
		for (var l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			this.fRec20[l15] = 0;
			
		}
		for (var l16 = 0; (l16 < 4); l16 = (l16 + 1)) {
			this.fRec16[l16] = 0;
			
		}
		for (var l17 = 0; (l17 < 3); l17 = (l17 + 1)) {
			this.fRec14[l17] = 0;
			
		}
		for (var l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			this.iRec6[l18] = 0;
			
		}
		for (var l19 = 0; (l19 < 2048); l19 = (l19 + 1)) {
			this.fRec2[l19] = 0;
			
		}
		for (var l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			this.fRec0[l20] = 0;
			
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
		ui_interface.openVerticalBox("violin");
		ui_interface.declare("0", "0", "");
		ui_interface.openHorizontalBox("midi");
		ui_interface.declare("fHslider2", "0", "");
		ui_interface.declare("fHslider2", "style", "knob");
		ui_interface.addHorizontalSlider("freq", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 440, 50, 1000, 0.01);
		ui_interface.declare("fHslider3", "1", "");
		ui_interface.declare("fHslider3", "hidden", "1");
		ui_interface.declare("fHslider3", "midi", "pitchwheel");
		ui_interface.declare("fHslider3", "style", "knob");
		ui_interface.addHorizontalSlider("bend", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 1, 0, 10, 0.01);
		ui_interface.declare("fHslider7", "2", "");
		ui_interface.declare("fHslider7", "style", "knob");
		ui_interface.addHorizontalSlider("gain", function handler(obj) { function setval(val) { obj.fHslider7 = val; } return setval; }(this), 0.6, 0, 1, 0.01);
		ui_interface.declare("fHslider8", "3", "");
		ui_interface.declare("fHslider8", "style", "knob");
		ui_interface.addHorizontalSlider("envAttack", function handler(obj) { function setval(val) { obj.fHslider8 = val; } return setval; }(this), 1, 0, 30, 0.01);
		ui_interface.declare("fHslider4", "4", "");
		ui_interface.declare("fHslider4", "hidden", "1");
		ui_interface.declare("fHslider4", "midi", "ctrl 64");
		ui_interface.declare("fHslider4", "style", "knob");
		ui_interface.addHorizontalSlider("sustain", function handler(obj) { function setval(val) { obj.fHslider4 = val; } return setval; }(this), 0, 0, 1, 1);
		ui_interface.closeBox();
		ui_interface.declare("0", "1", "");
		ui_interface.openHorizontalBox("bow");
		ui_interface.declare("fHslider9", "0", "");
		ui_interface.declare("fHslider9", "midi", "ctrl 1");
		ui_interface.declare("fHslider9", "style", "knob");
		ui_interface.addHorizontalSlider("pressure", function handler(obj) { function setval(val) { obj.fHslider9 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.declare("fHslider1", "1", "");
		ui_interface.declare("fHslider1", "style", "knob");
		ui_interface.addHorizontalSlider("position", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 0.7, 0, 1, 0.01);
		ui_interface.closeBox();
		ui_interface.declare("0", "2", "");
		ui_interface.openHorizontalBox("otherParams");
		ui_interface.declare("fHslider6", "0", "");
		ui_interface.declare("fHslider6", "style", "knob");
		ui_interface.addHorizontalSlider("vibratoFrequency", function handler(obj) { function setval(val) { obj.fHslider6 = val; } return setval; }(this), 6, 1, 10, 0.01);
		ui_interface.declare("fHslider5", "1", "");
		ui_interface.declare("fHslider5", "style", "knob");
		ui_interface.addHorizontalSlider("vibratoGain", function handler(obj) { function setval(val) { obj.fHslider5 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.declare("fHslider0", "2", "");
		ui_interface.declare("fHslider0", "style", "knob");
		ui_interface.addHorizontalSlider("outGain", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.closeBox();
		ui_interface.declare("fButton0", "3", "");
		ui_interface.addButton("gate", function handler(obj) { function setval(val) { obj.fButton0 = val; } return setval; }(this));
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = this.fHslider0;
		var fSlow1 = (0.001 * this.fHslider1);
		var fSlow2 = (340 / this.fHslider2);
		var fSlow3 = this.fHslider3;
		var fSlow4 = min_f(1, (this.fButton0 + this.fHslider4));
		var iSlow5 = (fSlow4 == 0);
		var fSlow6 = (0.01 * this.fHslider5);
		var fSlow7 = (this.fConst6 * this.fHslider6);
		var fSlow8 = Math.sin(fSlow7);
		var fSlow9 = Math.cos(fSlow7);
		var fSlow10 = (0 - fSlow8);
		var fSlow11 = Math.exp((0 - (this.fConst7 / this.fHslider8)));
		var fSlow12 = ((fSlow4 * this.fHslider7) * (1 - fSlow11));
		var fSlow13 = (0.001 * this.fHslider9);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iRec10[0] = 0;
			this.iVec0[0] = 1;
			var iRec11 = this.iRec10[1];
			var fRec15 = (this.iRec6[1] - (0.989265 * ((0.6 * this.fRec16[2]) + (0.2 * (this.fRec16[1] + this.fRec16[3])))));
			this.fRec26[0] = (fSlow1 + (0.999 * this.fRec26[1]));
			this.fVec1[0] = fSlow4;
			var iTemp0 = ((fSlow4 == this.fVec1[1]) | iSlow5);
			this.fRec27[0] = ((fSlow3 * (1 - (0.999 * iTemp0))) + (0.999 * (iTemp0 * this.fRec27[1])));
			this.fRec28[0] = ((fSlow8 * this.fRec29[1]) + (fSlow9 * this.fRec28[1]));
			this.fRec29[0] = (((fSlow9 * this.fRec29[1]) + (fSlow10 * this.fRec28[1])) + (1 - this.iVec0[1]));
			this.fRec30[0] = (fSlow12 + (fSlow11 * this.fRec30[1]));
			var fTemp1 = ((fSlow2 / (this.fRec27[0] * ((fSlow6 * (this.fRec28[0] * this.fRec30[0])) + 1))) + -0.08);
			var fTemp2 = (this.fConst5 * ((1 - this.fRec26[0]) * fTemp1));
			var fTemp3 = (fTemp2 + -1.49999);
			var iTemp4 = fTemp3;
			var iTemp5 = min_f(this.fConst4, max_i(0, iTemp4));
			var fTemp6 = Math.floor(fTemp3);
			var fTemp7 = (fTemp2 + (-1 - fTemp6));
			var fTemp8 = (0 - fTemp7);
			var fTemp9 = (fTemp2 + (-2 - fTemp6));
			var fTemp10 = (0 - (0.5 * fTemp9));
			var fTemp11 = (fTemp2 + (-3 - fTemp6));
			var fTemp12 = (0 - (0.333333 * fTemp11));
			var fTemp13 = (fTemp2 + (-4 - fTemp6));
			var fTemp14 = (0 - (0.25 * fTemp13));
			var fTemp15 = (fTemp2 - fTemp6);
			var iTemp16 = min_f(this.fConst4, max_i(0, (iTemp4 + 2)));
			var fTemp17 = (0 - fTemp11);
			var fTemp18 = (0 - (0.5 * fTemp13));
			var iTemp19 = min_f(this.fConst4, max_i(0, (iTemp4 + 1)));
			var fTemp20 = (0 - fTemp9);
			var fTemp21 = (0 - (0.5 * fTemp11));
			var fTemp22 = (0 - (0.333333 * fTemp13));
			var fTemp23 = (fTemp7 * fTemp9);
			var iTemp24 = min_f(this.fConst4, max_i(0, (iTemp4 + 3)));
			var fTemp25 = (0 - fTemp13);
			var fTemp26 = (fTemp23 * fTemp11);
			var iTemp27 = min_f(this.fConst4, max_i(0, (iTemp4 + 4)));
			this.fRec22[0] = (((((this.fRec2[((this.IOTA - (iTemp5 + 1)) & 2047)] * fTemp8) * fTemp10) * fTemp12) * fTemp14) + (fTemp15 * ((((0.5 * (((fTemp7 * this.fRec2[((this.IOTA - (iTemp16 + 1)) & 2047)]) * fTemp17) * fTemp18)) + (((this.fRec2[((this.IOTA - (iTemp19 + 1)) & 2047)] * fTemp20) * fTemp21) * fTemp22)) + (0.166667 * ((fTemp23 * this.fRec2[((this.IOTA - (iTemp24 + 1)) & 2047)]) * fTemp25))) + (0.0416667 * (fTemp26 * this.fRec2[((this.IOTA - (iTemp27 + 1)) & 2047)])))));
			this.fRec31[0] = this.fRec0[1];
			this.fRec32[(this.IOTA & 2047)] = (0 - (0.998801 * ((0.8 * this.fRec31[2]) + (0.1 * (this.fRec31[1] + this.fRec31[3])))));
			var iRec33 = 0;
			var fTemp28 = (this.fConst5 * (this.fRec26[0] * fTemp1));
			var fTemp29 = (fTemp28 + -1.49999);
			var iTemp30 = fTemp29;
			var iTemp31 = min_f(this.fConst4, max_i(0, iTemp30));
			var fTemp32 = Math.floor(fTemp29);
			var fTemp33 = (fTemp28 + (-1 - fTemp32));
			var fTemp34 = (0 - fTemp33);
			var fTemp35 = (fTemp28 + (-2 - fTemp32));
			var fTemp36 = (0 - (0.5 * fTemp35));
			var fTemp37 = (fTemp28 + (-3 - fTemp32));
			var fTemp38 = (0 - (0.333333 * fTemp37));
			var fTemp39 = (fTemp28 + (-4 - fTemp32));
			var fTemp40 = (0 - (0.25 * fTemp39));
			var fTemp41 = (fTemp28 - fTemp32);
			var iTemp42 = min_f(this.fConst4, max_i(0, (iTemp30 + 2)));
			var fTemp43 = (0 - fTemp37);
			var fTemp44 = (0 - (0.5 * fTemp39));
			var iTemp45 = min_f(this.fConst4, max_i(0, (iTemp30 + 1)));
			var fTemp46 = (0 - fTemp35);
			var fTemp47 = (0 - (0.5 * fTemp37));
			var fTemp48 = (0 - (0.333333 * fTemp39));
			var fTemp49 = (fTemp33 * fTemp35);
			var iTemp50 = min_f(this.fConst4, max_i(0, (iTemp30 + 3)));
			var fTemp51 = (0 - fTemp39);
			var fTemp52 = (fTemp49 * fTemp37);
			var iTemp53 = min_f(this.fConst4, max_i(0, (iTemp30 + 4)));
			this.fVec2[0] = (((((this.fRec32[((this.IOTA - (iTemp31 + 2)) & 2047)] * fTemp34) * fTemp36) * fTemp38) * fTemp40) + (fTemp41 * ((((0.5 * (((fTemp33 * this.fRec32[((this.IOTA - (iTemp42 + 2)) & 2047)]) * fTemp43) * fTemp44)) + (((this.fRec32[((this.IOTA - (iTemp45 + 2)) & 2047)] * fTemp46) * fTemp47) * fTemp48)) + (0.166667 * ((fTemp49 * this.fRec32[((this.IOTA - (iTemp50 + 2)) & 2047)]) * fTemp51))) + (0.0416667 * (fTemp52 * this.fRec32[((this.IOTA - (iTemp53 + 2)) & 2047)])))));
			var fTemp54 = (this.fRec30[0] - (this.fRec22[1] + this.fVec2[1]));
			this.fRec34[0] = (fSlow13 + (0.999 * this.fRec34[1]));
			var fTemp55 = (fTemp54 * min_f(1, (1 / mydsp_faustpower4_f((Math.abs(((5 - (4 * this.fRec34[0])) * fTemp54)) + 0.75)))));
			var fRec23 = (this.fRec22[1] + fTemp55);
			var fTemp56 = (this.fVec2[1] + fTemp55);
			this.fVec3[(this.IOTA & 2047)] = fTemp56;
			var fRec24 = (((((fTemp8 * fTemp10) * fTemp12) * fTemp14) * this.fVec3[((this.IOTA - iTemp5) & 2047)]) + (fTemp15 * ((0.0416667 * (fTemp26 * this.fVec3[((this.IOTA - iTemp27) & 2047)])) + (((((fTemp20 * fTemp21) * fTemp22) * this.fVec3[((this.IOTA - iTemp19) & 2047)]) + (0.5 * (((fTemp7 * fTemp17) * fTemp18) * this.fVec3[((this.IOTA - iTemp16) & 2047)]))) + (0.166667 * ((fTemp23 * fTemp25) * this.fVec3[((this.IOTA - iTemp24) & 2047)]))))));
			var iRec25 = iRec33;
			this.fRec18[(this.IOTA & 2047)] = fRec23;
			var fRec19 = (((((fTemp34 * fTemp36) * fTemp38) * fTemp40) * this.fRec18[((this.IOTA - (iTemp31 + 1)) & 2047)]) + (fTemp41 * (((0.166667 * ((fTemp49 * fTemp51) * this.fRec18[((this.IOTA - (iTemp50 + 1)) & 2047)])) + ((((fTemp46 * fTemp47) * fTemp48) * this.fRec18[((this.IOTA - (iTemp45 + 1)) & 2047)]) + (0.5 * (((fTemp33 * fTemp43) * fTemp44) * this.fRec18[((this.IOTA - (iTemp42 + 1)) & 2047)])))) + (0.0416667 * (fTemp52 * this.fRec18[((this.IOTA - (iTemp53 + 1)) & 2047)])))));
			this.fRec20[0] = fRec24;
			var iRec21 = iRec25;
			this.fRec16[0] = this.fRec20[1];
			var iRec17 = iRec21;
			this.fRec14[0] = (this.fRec16[1] - (this.fConst3 * ((this.fConst8 * this.fRec14[2]) + (this.fConst9 * this.fRec14[1]))));
			var fTemp57 = (this.fConst3 * ((this.fConst2 * this.fRec14[0]) + (this.fConst10 * this.fRec14[2])));
			var fRec12 = fTemp57;
			var fRec13 = (iRec17 + fTemp57);
			this.iRec6[0] = iRec11;
			var fRec7 = fRec15;
			var fRec8 = fRec12;
			var fRec9 = fRec13;
			this.fRec2[(this.IOTA & 2047)] = fRec7;
			var fRec3 = fRec19;
			var fRec4 = fRec8;
			var fRec5 = fRec9;
			this.fRec0[0] = fRec3;
			var fRec1 = fRec5;
			var fTemp58 = (fSlow0 * fRec1);
			output0[i] = fTemp58;
			output1[i] = fTemp58;
			this.iRec10[1] = this.iRec10[0];
			this.iVec0[1] = this.iVec0[0];
			this.fRec26[1] = this.fRec26[0];
			this.fVec1[1] = this.fVec1[0];
			this.fRec27[1] = this.fRec27[0];
			this.fRec28[1] = this.fRec28[0];
			this.fRec29[1] = this.fRec29[0];
			this.fRec30[1] = this.fRec30[0];
			this.fRec22[1] = this.fRec22[0];
			for (var j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				this.fRec31[j0] = this.fRec31[(j0 - 1)];
				
			}
			this.IOTA = (this.IOTA + 1);
			this.fVec2[1] = this.fVec2[0];
			this.fRec34[1] = this.fRec34[0];
			this.fRec20[1] = this.fRec20[0];
			for (var j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				this.fRec16[j1] = this.fRec16[(j1 - 1)];
				
			}
			this.fRec14[2] = this.fRec14[1];
			this.fRec14[1] = this.fRec14[0];
			this.iRec6[1] = this.iRec6[0];
			this.fRec0[1] = this.fRec0[0];
			
		}
		
	}
	
}

