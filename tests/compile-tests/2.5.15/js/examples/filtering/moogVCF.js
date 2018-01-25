
this.mydsp_faustpower4_f = function(value) {
	return (((value * value) * value) * value);
	
}
this.min_f = function(dummy0, dummy1);
this.max_f = function(dummy0, dummy1);
this.mydsp_faustpower2_f = function(value) {
	return (value * value);
	
}

function mydsp() {
	
	this.fCheckbox0;
	this.fHslider0;
	this.fRec0 = new Float32Array(2);
	this.fCheckbox1;
	this.fHslider1;
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fHslider2;
	this.fRec6 = new Float32Array(2);
	this.fRec5 = new Float32Array(2);
	this.fRec4 = new Float32Array(2);
	this.fRec3 = new Float32Array(2);
	this.fRec2 = new Float32Array(2);
	this.fRec1 = new Float32Array(2);
	this.fCheckbox2;
	this.fConst2;
	this.fRec9 = new Float32Array(2);
	this.fRec8 = new Float32Array(3);
	this.fRec7 = new Float32Array(3);
	this.fRec12 = new Float32Array(2);
	this.fRec10 = new Float32Array(2);
	this.fRec15 = new Float32Array(2);
	this.fRec13 = new Float32Array(2);
	
	this.metadata = function(m) { 
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("description", "Exercise and compare three Moog VCF implementations");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "moogVCF");
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
		this.fConst0 = min_f(192000, max_f(1, this.fSamplingFreq));
		this.fConst1 = (6.28319 / this.fConst0);
		this.fConst2 = (3.14159 / this.fConst0);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fCheckbox0 = 0;
		this.fHslider0 = 5;
		this.fCheckbox1 = 0;
		this.fHslider1 = 0.9;
		this.fHslider2 = 25;
		this.fCheckbox2 = 0;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.fRec0[l0] = 0;
			
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
			this.fRec3[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fRec2[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			this.fRec1[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			this.fRec9[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
			this.fRec8[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 3); l9 = (l9 + 1)) {
			this.fRec7[l9] = 0;
			
		}
		for (var l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			this.fRec12[l10] = 0;
			
		}
		for (var l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			this.fRec10[l11] = 0;
			
		}
		for (var l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			this.fRec15[l12] = 0;
			
		}
		for (var l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			this.fRec13[l13] = 0;
			
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
		ui_interface.declare("0", "tooltip", "See Faust's   vaeffects.lib for info and references");
		ui_interface.openHorizontalBox("MOOG VCF (Voltage Controlled Filter)");
		ui_interface.declare("0", "0", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fCheckbox0", "0", "");
		ui_interface.declare("fCheckbox0", "tooltip", "When this is checked, the Moog VCF   has no effect");
		ui_interface.addCheckButton("Bypass", function handler(obj) { function setval(val) { obj.fCheckbox0 = val; } return setval; }(this));
		ui_interface.declare("fCheckbox1", "1", "");
		ui_interface.declare("fCheckbox1", "tooltip", "Select moog_vcf_2b (two-biquad)   implementation, instead of the default moog_vcf (analog style) implementation");
		ui_interface.addCheckButton("Use Biquads", function handler(obj) { function setval(val) { obj.fCheckbox1 = val; } return setval; }(this));
		ui_interface.declare("fCheckbox2", "2", "");
		ui_interface.declare("fCheckbox2", "tooltip", "If using biquads, make   them normalized ladders (moog_vcf_2bn)");
		ui_interface.addCheckButton("Normalized Ladders", function handler(obj) { function setval(val) { obj.fCheckbox2 = val; } return setval; }(this));
		ui_interface.closeBox();
		ui_interface.declare("fHslider2", "1", "");
		ui_interface.declare("fHslider2", "tooltip", "The VCF resonates   at the corner frequency (specified in PianoKey (PK) units, with A440 = 49 PK).   The VCF response is flat below the corner frequency, and rolls off -24 dB per   octave above.");
		ui_interface.declare("fHslider2", "unit", "PK");
		ui_interface.addHorizontalSlider("Corner Frequency", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 25, 1, 88, 0.01);
		ui_interface.declare("fHslider1", "2", "");
		ui_interface.declare("fHslider1", "style", "knob");
		ui_interface.declare("fHslider1", "tooltip", "Amount of   resonance near VCF corner frequency (specified between 0 and 1)");
		ui_interface.addHorizontalSlider("Corner Resonance", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 0.9, 0, 1, 0.01);
		ui_interface.declare("fHslider0", "3", "");
		ui_interface.declare("fHslider0", "style", "knob");
		ui_interface.declare("fHslider0", "tooltip", "output level in decibels");
		ui_interface.declare("fHslider0", "unit", "dB");
		ui_interface.addHorizontalSlider("VCF Output Level", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 5, -60, 20, 0.1);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var output0 = outputs[0];
		var iSlow0 = this.fCheckbox0;
		var fSlow1 = (0.001 * Math.pow(10, (0.05 * this.fHslider0)));
		var iSlow2 = this.fCheckbox1;
		var fSlow3 = this.fHslider1;
		var fSlow4 = (0 - (4 * max_f(0, min_f(mydsp_faustpower4_f(fSlow3), 0.999999))));
		var fSlow5 = (0.44 * Math.pow(2, (0.0833333 * (this.fHslider2 + -49))));
		var iSlow6 = this.fCheckbox2;
		var fSlow7 = min_f(1.4142, (1.41421 * fSlow3));
		var fSlow8 = (fSlow7 * (fSlow7 + 1.41421));
		var fSlow9 = (1.41421 * fSlow7);
		var fSlow10 = (fSlow9 + 2);
		var fSlow11 = (fSlow7 * (fSlow7 + -1.41421));
		var fSlow12 = (2 - fSlow9);
		var fSlow13 = (1.99998 * fSlow3);
		var fSlow14 = mydsp_faustpower2_f((1.4142 * fSlow3));
		var fSlow15 = (fSlow13 + fSlow14);
		var fSlow16 = (fSlow13 + 2);
		var fSlow17 = (2 - fSlow13);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.fRec0[0] = (fSlow1 + (0.999 * this.fRec0[1]));
			var fTemp0 = input0[i];
			var fTemp1 = (iSlow0?0:fTemp0);
			this.fRec6[0] = (fSlow5 + (0.999 * this.fRec6[1]));
			var fTemp2 = (this.fConst1 * this.fRec6[0]);
			var fTemp3 = (1 - fTemp2);
			this.fRec5[0] = ((fSlow4 * this.fRec1[1]) + (fTemp1 + (fTemp3 * this.fRec5[1])));
			this.fRec4[0] = (this.fRec5[0] + (fTemp3 * this.fRec4[1]));
			this.fRec3[0] = (this.fRec4[0] + (fTemp3 * this.fRec3[1]));
			this.fRec2[0] = (this.fRec3[0] + (this.fRec2[1] * fTemp3));
			this.fRec1[0] = (this.fRec2[0] * Math.pow(fTemp2, 4));
			this.fRec9[0] = (fSlow5 + (0.999 * this.fRec9[1]));
			var fTemp4 = Math.tan((this.fConst2 * max_f(20, min_f(10000, this.fRec9[0]))));
			var fTemp5 = (1 / fTemp4);
			var fTemp6 = (1 - (1 / mydsp_faustpower2_f(fTemp4)));
			var fTemp7 = (fSlow8 + (((fSlow10 + fTemp5) / fTemp4) + 1));
			this.fRec8[0] = (fTemp1 - (((this.fRec8[2] * (fSlow8 + (((fTemp5 - fSlow10) / fTemp4) + 1))) + (2 * (this.fRec8[1] * (fSlow8 + fTemp6)))) / fTemp7));
			var fTemp8 = (fSlow11 + (((fSlow12 + fTemp5) / fTemp4) + 1));
			this.fRec7[0] = (((this.fRec8[2] + (this.fRec8[0] + (2 * this.fRec8[1]))) / fTemp7) - (((this.fRec7[2] * (fSlow11 + (((fTemp5 - fSlow12) / fTemp4) + 1))) + (2 * ((fSlow11 + fTemp6) * this.fRec7[1]))) / fTemp8));
			var fTemp9 = Math.tan((this.fConst2 * max_f(this.fRec9[0], 20)));
			var fTemp10 = (1 / fTemp9);
			var fTemp11 = (fSlow15 + (((fSlow16 + fTemp10) / fTemp9) + 1));
			var fTemp12 = ((fSlow15 + (1 - ((fSlow16 - fTemp10) / fTemp9))) / fTemp11);
			var fTemp13 = max_f(-0.9999, min_f(0.9999, fTemp12));
			var fTemp14 = (1 - mydsp_faustpower2_f(fTemp13));
			var fTemp15 = Math.sqrt(max_f(0, fTemp14));
			var fTemp16 = ((this.fRec10[1] * (0 - fTemp13)) + (fTemp1 * fTemp15));
			var fTemp17 = (1 - (1 / mydsp_faustpower2_f(fTemp9)));
			var fTemp18 = (fSlow15 + fTemp17);
			var fTemp19 = max_f(-0.9999, min_f(0.9999, (2 * (fTemp18 / (fTemp11 * (fTemp12 + 1))))));
			var fTemp20 = (1 - mydsp_faustpower2_f(fTemp19));
			var fTemp21 = Math.sqrt(max_f(0, fTemp20));
			this.fRec12[0] = ((this.fRec12[1] * (0 - fTemp19)) + (fTemp16 * fTemp21));
			this.fRec10[0] = ((fTemp16 * fTemp19) + (this.fRec12[1] * fTemp21));
			var fRec11 = this.fRec12[0];
			var fTemp22 = (1 - (fTemp18 / fTemp11));
			var fTemp23 = Math.sqrt(fTemp14);
			var fTemp24 = ((((fTemp1 * fTemp13) + (this.fRec10[1] * fTemp15)) + (2 * ((this.fRec10[0] * fTemp22) / fTemp23))) + ((fRec11 * ((1 - fTemp12) - (2 * (fTemp19 * fTemp22)))) / (fTemp23 * Math.sqrt(fTemp20))));
			var fTemp25 = (fSlow14 + ((((fSlow17 + fTemp10) / fTemp9) + 1) - fSlow13));
			var fTemp26 = ((fSlow14 + ((((fTemp10 - fSlow17) / fTemp9) + 1) - fSlow13)) / fTemp25);
			var fTemp27 = max_f(-0.9999, min_f(0.9999, fTemp26));
			var fTemp28 = (1 - mydsp_faustpower2_f(fTemp27));
			var fTemp29 = Math.sqrt(max_f(0, fTemp28));
			var fTemp30 = ((this.fRec13[1] * (0 - fTemp27)) + ((fTemp24 * fTemp29) / fTemp11));
			var fTemp31 = (fSlow14 + (fTemp17 - fSlow13));
			var fTemp32 = max_f(-0.9999, min_f(0.9999, (2 * (fTemp31 / (fTemp25 * (fTemp26 + 1))))));
			var fTemp33 = (1 - mydsp_faustpower2_f(fTemp32));
			var fTemp34 = Math.sqrt(max_f(0, fTemp33));
			this.fRec15[0] = ((this.fRec15[1] * (0 - fTemp32)) + (fTemp30 * fTemp34));
			this.fRec13[0] = ((fTemp30 * fTemp32) + (this.fRec15[1] * fTemp34));
			var fRec14 = this.fRec15[0];
			var fTemp35 = (1 - (fTemp31 / fTemp25));
			var fTemp36 = Math.sqrt(fTemp28);
			output0[i] = (iSlow0?fTemp0:(this.fRec0[0] * (iSlow2?(iSlow6?((((((fTemp24 * fTemp27) / fTemp11) + (this.fRec13[1] * fTemp29)) + (2 * ((this.fRec13[0] * fTemp35) / fTemp36))) + ((fRec14 * ((1 - fTemp26) - (2 * (fTemp32 * fTemp35)))) / (fTemp36 * Math.sqrt(fTemp33)))) / fTemp25):((this.fRec7[2] + (this.fRec7[0] + (2 * this.fRec7[1]))) / fTemp8)):this.fRec1[0])));
			this.fRec0[1] = this.fRec0[0];
			this.fRec6[1] = this.fRec6[0];
			this.fRec5[1] = this.fRec5[0];
			this.fRec4[1] = this.fRec4[0];
			this.fRec3[1] = this.fRec3[0];
			this.fRec2[1] = this.fRec2[0];
			this.fRec1[1] = this.fRec1[0];
			this.fRec9[1] = this.fRec9[0];
			this.fRec8[2] = this.fRec8[1];
			this.fRec8[1] = this.fRec8[0];
			this.fRec7[2] = this.fRec7[1];
			this.fRec7[1] = this.fRec7[0];
			this.fRec12[1] = this.fRec12[0];
			this.fRec10[1] = this.fRec10[0];
			this.fRec15[1] = this.fRec15[0];
			this.fRec13[1] = this.fRec13[0];
			
		}
		
	}
	
}

