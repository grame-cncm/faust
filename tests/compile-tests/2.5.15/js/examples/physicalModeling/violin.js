
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
	this.fRec27 = new Float32Array(2);
	this.fRec22 = new Float32Array(2);
	this.fHslider3;
	this.fRec28 = new Float32Array(2);
	this.fRec29 = new Float32Array(4);
	this.IOTA;
	this.fRec30 = new Float32Array(2048);
	this.fVec0 = new Float32Array(2);
	this.fHslider4;
	this.fRec32 = new Float32Array(2);
	this.fVec1 = new Float32Array(2048);
	this.fRec18 = new Float32Array(2048);
	this.fRec20 = new Float32Array(2);
	this.fRec16 = new Float32Array(4);
	this.fConst6;
	this.fConst7;
	this.fRec14 = new Float32Array(3);
	this.fConst8;
	this.iRec6 = new Int32Array(2);
	this.fRec2 = new Float32Array(2048);
	this.fRec0 = new Float32Array(2);
	
	this.metadata = function(m) { 
		m.declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("description", "Simple violin physical model controlled with continuous parameters.");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("license", "MIT");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "Violin");
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
		this.fConst6 = (((this.fConst2 + -0.5) / this.fConst1) + 1);
		this.fConst7 = (2 * (1 - (1 / mydsp_faustpower2_f(this.fConst1))));
		this.fConst8 = (0 - this.fConst2);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 0.5;
		this.fHslider1 = 0.7;
		this.fHslider2 = 0.75;
		this.fHslider3 = 0;
		this.fHslider4 = 0.5;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.iRec10[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec26[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec27[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec22[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec28[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 4); l5 = (l5 + 1)) {
			this.fRec29[l5] = 0;
			
		}
		this.IOTA = 0;
		for (var l6 = 0; (l6 < 2048); l6 = (l6 + 1)) {
			this.fRec30[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			this.fVec0[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			this.fRec32[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 2048); l9 = (l9 + 1)) {
			this.fVec1[l9] = 0;
			
		}
		for (var l10 = 0; (l10 < 2048); l10 = (l10 + 1)) {
			this.fRec18[l10] = 0;
			
		}
		for (var l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			this.fRec20[l11] = 0;
			
		}
		for (var l12 = 0; (l12 < 4); l12 = (l12 + 1)) {
			this.fRec16[l12] = 0;
			
		}
		for (var l13 = 0; (l13 < 3); l13 = (l13 + 1)) {
			this.fRec14[l13] = 0;
			
		}
		for (var l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			this.iRec6[l14] = 0;
			
		}
		for (var l15 = 0; (l15 < 2048); l15 = (l15 + 1)) {
			this.fRec2[l15] = 0;
			
		}
		for (var l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			this.fRec0[l16] = 0;
			
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
		ui_interface.openVerticalBox("string");
		ui_interface.declare("fHslider2", "0", "");
		ui_interface.addHorizontalSlider("length", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 0.75, 0, 2, 0.01);
		ui_interface.closeBox();
		ui_interface.declare("0", "1", "");
		ui_interface.openVerticalBox("bow");
		ui_interface.declare("fHslider3", "0", "");
		ui_interface.addHorizontalSlider("velocity", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 0, 0, 1, 0.01);
		ui_interface.declare("fHslider4", "1", "");
		ui_interface.addHorizontalSlider("pressure", function handler(obj) { function setval(val) { obj.fHslider4 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.declare("fHslider1", "2", "");
		ui_interface.addHorizontalSlider("position", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 0.7, 0, 1, 0.01);
		ui_interface.closeBox();
		ui_interface.addHorizontalSlider("outGain", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = this.fHslider0;
		var fSlow1 = (0.001 * this.fHslider1);
		var fSlow2 = (0.001 * this.fHslider2);
		var fSlow3 = (0.001 * this.fHslider3);
		var fSlow4 = (0.001 * this.fHslider4);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iRec10[0] = 0;
			var iRec11 = this.iRec10[1];
			var fRec15 = (this.iRec6[1] - (0.989265 * ((0.6 * this.fRec16[2]) + (0.2 * (this.fRec16[1] + this.fRec16[3])))));
			this.fRec26[0] = (fSlow1 + (0.999 * this.fRec26[1]));
			this.fRec27[0] = (fSlow2 + (0.999 * this.fRec27[1]));
			var fTemp0 = (this.fRec27[0] + -0.08);
			var fTemp1 = (this.fConst5 * ((1 - this.fRec26[0]) * fTemp0));
			var fTemp2 = (fTemp1 + -1.49999);
			var iTemp3 = fTemp2;
			var iTemp4 = min_f(this.fConst4, max_i(0, iTemp3));
			var fTemp5 = Math.floor(fTemp2);
			var fTemp6 = (fTemp1 + (-1 - fTemp5));
			var fTemp7 = (0 - fTemp6);
			var fTemp8 = (fTemp1 + (-2 - fTemp5));
			var fTemp9 = (0 - (0.5 * fTemp8));
			var fTemp10 = (fTemp1 + (-3 - fTemp5));
			var fTemp11 = (0 - (0.333333 * fTemp10));
			var fTemp12 = (fTemp1 + (-4 - fTemp5));
			var fTemp13 = (0 - (0.25 * fTemp12));
			var fTemp14 = (fTemp1 - fTemp5);
			var iTemp15 = min_f(this.fConst4, max_i(0, (iTemp3 + 2)));
			var fTemp16 = (0 - fTemp10);
			var fTemp17 = (0 - (0.5 * fTemp12));
			var iTemp18 = min_f(this.fConst4, max_i(0, (iTemp3 + 1)));
			var fTemp19 = (0 - fTemp8);
			var fTemp20 = (0 - (0.5 * fTemp10));
			var fTemp21 = (0 - (0.333333 * fTemp12));
			var fTemp22 = (fTemp6 * fTemp8);
			var iTemp23 = min_f(this.fConst4, max_i(0, (iTemp3 + 3)));
			var fTemp24 = (0 - fTemp12);
			var fTemp25 = (fTemp22 * fTemp10);
			var iTemp26 = min_f(this.fConst4, max_i(0, (iTemp3 + 4)));
			this.fRec22[0] = (((((this.fRec2[((this.IOTA - (iTemp4 + 1)) & 2047)] * fTemp7) * fTemp9) * fTemp11) * fTemp13) + (fTemp14 * ((((0.5 * (((fTemp6 * this.fRec2[((this.IOTA - (iTemp15 + 1)) & 2047)]) * fTemp16) * fTemp17)) + (((this.fRec2[((this.IOTA - (iTemp18 + 1)) & 2047)] * fTemp19) * fTemp20) * fTemp21)) + (0.166667 * ((fTemp22 * this.fRec2[((this.IOTA - (iTemp23 + 1)) & 2047)]) * fTemp24))) + (0.0416667 * (fTemp25 * this.fRec2[((this.IOTA - (iTemp26 + 1)) & 2047)])))));
			this.fRec28[0] = (fSlow3 + (0.999 * this.fRec28[1]));
			this.fRec29[0] = this.fRec0[1];
			this.fRec30[(this.IOTA & 2047)] = (0 - (0.998801 * ((0.8 * this.fRec29[2]) + (0.1 * (this.fRec29[1] + this.fRec29[3])))));
			var iRec31 = 0;
			var fTemp27 = (this.fConst5 * (this.fRec26[0] * fTemp0));
			var fTemp28 = (fTemp27 + -1.49999);
			var iTemp29 = fTemp28;
			var iTemp30 = min_f(this.fConst4, max_i(0, iTemp29));
			var fTemp31 = Math.floor(fTemp28);
			var fTemp32 = (fTemp27 + (-1 - fTemp31));
			var fTemp33 = (0 - fTemp32);
			var fTemp34 = (fTemp27 + (-2 - fTemp31));
			var fTemp35 = (0 - (0.5 * fTemp34));
			var fTemp36 = (fTemp27 + (-3 - fTemp31));
			var fTemp37 = (0 - (0.333333 * fTemp36));
			var fTemp38 = (fTemp27 + (-4 - fTemp31));
			var fTemp39 = (0 - (0.25 * fTemp38));
			var fTemp40 = (fTemp27 - fTemp31);
			var iTemp41 = min_f(this.fConst4, max_i(0, (iTemp29 + 2)));
			var fTemp42 = (0 - fTemp36);
			var fTemp43 = (0 - (0.5 * fTemp38));
			var iTemp44 = min_f(this.fConst4, max_i(0, (iTemp29 + 1)));
			var fTemp45 = (0 - fTemp34);
			var fTemp46 = (0 - (0.5 * fTemp36));
			var fTemp47 = (0 - (0.333333 * fTemp38));
			var fTemp48 = (fTemp32 * fTemp34);
			var iTemp49 = min_f(this.fConst4, max_i(0, (iTemp29 + 3)));
			var fTemp50 = (0 - fTemp38);
			var fTemp51 = (fTemp48 * fTemp36);
			var iTemp52 = min_f(this.fConst4, max_i(0, (iTemp29 + 4)));
			this.fVec0[0] = (((((this.fRec30[((this.IOTA - (iTemp30 + 2)) & 2047)] * fTemp33) * fTemp35) * fTemp37) * fTemp39) + (fTemp40 * ((((0.5 * (((fTemp32 * this.fRec30[((this.IOTA - (iTemp41 + 2)) & 2047)]) * fTemp42) * fTemp43)) + (((this.fRec30[((this.IOTA - (iTemp44 + 2)) & 2047)] * fTemp45) * fTemp46) * fTemp47)) + (0.166667 * ((fTemp48 * this.fRec30[((this.IOTA - (iTemp49 + 2)) & 2047)]) * fTemp50))) + (0.0416667 * (fTemp51 * this.fRec30[((this.IOTA - (iTemp52 + 2)) & 2047)])))));
			var fTemp53 = (this.fRec28[0] - (this.fRec22[1] + this.fVec0[1]));
			this.fRec32[0] = (fSlow4 + (0.999 * this.fRec32[1]));
			var fTemp54 = (fTemp53 * min_f(1, (1 / mydsp_faustpower4_f((Math.abs(((5 - (4 * this.fRec32[0])) * fTemp53)) + 0.75)))));
			var fRec23 = (this.fRec22[1] + fTemp54);
			var fTemp55 = (this.fVec0[1] + fTemp54);
			this.fVec1[(this.IOTA & 2047)] = fTemp55;
			var fRec24 = (((((fTemp7 * fTemp9) * fTemp11) * fTemp13) * this.fVec1[((this.IOTA - iTemp4) & 2047)]) + (fTemp14 * ((0.0416667 * (fTemp25 * this.fVec1[((this.IOTA - iTemp26) & 2047)])) + (((((fTemp19 * fTemp20) * fTemp21) * this.fVec1[((this.IOTA - iTemp18) & 2047)]) + (0.5 * (((fTemp6 * fTemp16) * fTemp17) * this.fVec1[((this.IOTA - iTemp15) & 2047)]))) + (0.166667 * ((fTemp22 * fTemp24) * this.fVec1[((this.IOTA - iTemp23) & 2047)]))))));
			var iRec25 = iRec31;
			this.fRec18[(this.IOTA & 2047)] = fRec23;
			var fRec19 = (((((fTemp33 * fTemp35) * fTemp37) * fTemp39) * this.fRec18[((this.IOTA - (iTemp30 + 1)) & 2047)]) + (fTemp40 * (((0.166667 * ((fTemp48 * fTemp50) * this.fRec18[((this.IOTA - (iTemp49 + 1)) & 2047)])) + ((((fTemp45 * fTemp46) * fTemp47) * this.fRec18[((this.IOTA - (iTemp44 + 1)) & 2047)]) + (0.5 * (((fTemp32 * fTemp42) * fTemp43) * this.fRec18[((this.IOTA - (iTemp41 + 1)) & 2047)])))) + (0.0416667 * (fTemp51 * this.fRec18[((this.IOTA - (iTemp52 + 1)) & 2047)])))));
			this.fRec20[0] = fRec24;
			var iRec21 = iRec25;
			this.fRec16[0] = this.fRec20[1];
			var iRec17 = iRec21;
			this.fRec14[0] = (this.fRec16[1] - (this.fConst3 * ((this.fConst6 * this.fRec14[2]) + (this.fConst7 * this.fRec14[1]))));
			var fTemp56 = (this.fConst3 * ((this.fConst2 * this.fRec14[0]) + (this.fConst8 * this.fRec14[2])));
			var fRec12 = fTemp56;
			var fRec13 = (iRec17 + fTemp56);
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
			var fTemp57 = (fSlow0 * fRec1);
			output0[i] = fTemp57;
			output1[i] = fTemp57;
			this.iRec10[1] = this.iRec10[0];
			this.fRec26[1] = this.fRec26[0];
			this.fRec27[1] = this.fRec27[0];
			this.fRec22[1] = this.fRec22[0];
			this.fRec28[1] = this.fRec28[0];
			for (var j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				this.fRec29[j0] = this.fRec29[(j0 - 1)];
				
			}
			this.IOTA = (this.IOTA + 1);
			this.fVec0[1] = this.fVec0[0];
			this.fRec32[1] = this.fRec32[0];
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

