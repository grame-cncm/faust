
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
	this.fHslider3;
	this.fRec25 = new Float32Array(2);
	this.fHslider4;
	this.fConst2;
	this.fHslider5;
	this.iRec27 = new Int32Array(2);
	this.fRec26 = new Float32Array(3);
	this.fRec28 = new Float32Array(2);
	this.IOTA;
	this.fRec29 = new Float32Array(2048);
	this.fConst3;
	this.fConst4;
	this.fHslider6;
	this.fRec31 = new Float32Array(2);
	this.fHslider7;
	this.fRec32 = new Float32Array(2);
	this.fVec1 = new Float32Array(2);
	this.fVec2 = new Float32Array(2048);
	this.fVec3 = new Float32Array(2);
	this.fRec20 = new Float32Array(2);
	this.fRec11 = new Float32Array(2048);
	this.fRec7 = new Float32Array(2);
	this.fRec3 = new Float32Array(2048);
	this.fRec1 = new Float32Array(2);
	this.fRec2 = new Float32Array(2);
	this.fRec0 = new Float32Array(2);
	
	this.metadata = function(m) { 
		m.declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("description", "Simple flute physical model with physical parameters.");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("license", "MIT");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "Flute");
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
		this.fConst2 = (3.14159 / this.fConst0);
		this.fConst3 = (0.00882353 * this.fConst0);
		this.fConst4 = (0.00147059 * this.fConst0);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 0.5;
		this.fHslider1 = 0.25;
		this.fHslider2 = 5;
		this.fHslider3 = 0;
		this.fHslider4 = 0.1;
		this.fHslider5 = 2000;
		this.fHslider6 = 0.8;
		this.fHslider7 = 0.5;
		
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
			this.fRec25[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			this.iRec27[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			this.fRec26[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			this.fRec28[l8] = 0;
			
		}
		this.IOTA = 0;
		for (var l9 = 0; (l9 < 2048); l9 = (l9 + 1)) {
			this.fRec29[l9] = 0;
			
		}
		for (var l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			this.fRec31[l10] = 0;
			
		}
		for (var l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			this.fRec32[l11] = 0;
			
		}
		for (var l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			this.fVec1[l12] = 0;
			
		}
		for (var l13 = 0; (l13 < 2048); l13 = (l13 + 1)) {
			this.fVec2[l13] = 0;
			
		}
		for (var l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			this.fVec3[l14] = 0;
			
		}
		for (var l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			this.fRec20[l15] = 0;
			
		}
		for (var l16 = 0; (l16 < 2048); l16 = (l16 + 1)) {
			this.fRec11[l16] = 0;
			
		}
		for (var l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			this.fRec7[l17] = 0;
			
		}
		for (var l18 = 0; (l18 < 2048); l18 = (l18 + 1)) {
			this.fRec3[l18] = 0;
			
		}
		for (var l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			this.fRec1[l19] = 0;
			
		}
		for (var l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			this.fRec2[l20] = 0;
			
		}
		for (var l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			this.fRec0[l21] = 0;
			
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
		ui_interface.openHorizontalBox("flute");
		ui_interface.openVerticalBox("blower");
		ui_interface.declare("fHslider3", "0", "");
		ui_interface.addHorizontalSlider("pressure", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 0, 0, 1, 0.01);
		ui_interface.declare("fHslider4", "1", "");
		ui_interface.addHorizontalSlider("breathGain", function handler(obj) { function setval(val) { obj.fHslider4 = val; } return setval; }(this), 0.1, 0, 1, 0.01);
		ui_interface.declare("fHslider5", "2", "");
		ui_interface.addHorizontalSlider("breathCutoff", function handler(obj) { function setval(val) { obj.fHslider5 = val; } return setval; }(this), 2000, 20, 20000, 0.1);
		ui_interface.declare("fHslider2", "3", "");
		ui_interface.addHorizontalSlider("vibratoFreq", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 5, 0.1, 10, 0.1);
		ui_interface.declare("fHslider1", "4", "");
		ui_interface.addHorizontalSlider("vibratoGain", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 0.25, 0, 1, 0.01);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("fluteModel");
		ui_interface.declare("fHslider6", "0", "");
		ui_interface.addHorizontalSlider("tubeLength", function handler(obj) { function setval(val) { obj.fHslider6 = val; } return setval; }(this), 0.8, 0.01, 3, 0.01);
		ui_interface.declare("fHslider7", "1", "");
		ui_interface.addHorizontalSlider("mouthPosition", function handler(obj) { function setval(val) { obj.fHslider7 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.declare("fHslider0", "2", "");
		ui_interface.addHorizontalSlider("outGain", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.closeBox();
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = this.fHslider0;
		var fSlow1 = (0.03 * this.fHslider1);
		var fSlow2 = (this.fConst1 * this.fHslider2);
		var fSlow3 = Math.sin(fSlow2);
		var fSlow4 = Math.cos(fSlow2);
		var fSlow5 = (0 - fSlow3);
		var fSlow6 = (0.001 * this.fHslider3);
		var fSlow7 = Math.tan((this.fConst2 * this.fHslider5));
		var fSlow8 = (1 / fSlow7);
		var fSlow9 = (((fSlow8 + 1.41421) / fSlow7) + 1);
		var fSlow10 = (0.05 * (this.fHslider4 / fSlow9));
		var fSlow11 = (1 / fSlow9);
		var fSlow12 = (((fSlow8 + -1.41421) / fSlow7) + 1);
		var fSlow13 = (2 * (1 - (1 / mydsp_faustpower2_f(fSlow7))));
		var fSlow14 = (0.001 * this.fHslider6);
		var fSlow15 = (0.001 * this.fHslider7);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iRec15[0] = 0;
			this.iVec0[0] = 1;
			this.fRec22[0] = ((0.7 * this.fRec22[1]) + (0.285 * this.fRec20[1]));
			var fRec19 = (this.fRec22[0] + this.iRec15[1]);
			this.fRec23[0] = ((fSlow3 * this.fRec24[1]) + (fSlow4 * this.fRec23[1]));
			this.fRec24[0] = (((fSlow4 * this.fRec24[1]) + (fSlow5 * this.fRec23[1])) + (1 - this.iVec0[1]));
			this.fRec25[0] = (fSlow6 + (0.999 * this.fRec25[1]));
			this.iRec27[0] = ((1103515245 * this.iRec27[1]) + 12345);
			this.fRec26[0] = ((4.65661e-10 * this.iRec27[0]) - (fSlow11 * ((fSlow12 * this.fRec26[2]) + (fSlow13 * this.fRec26[1]))));
			this.fRec28[0] = this.fRec1[1];
			this.fRec29[(this.IOTA & 2047)] = (0.95 * this.fRec28[1]);
			var iRec30 = 0;
			this.fRec31[0] = (fSlow14 + (0.999 * this.fRec31[1]));
			var fTemp0 = (this.fRec31[0] + 0.27);
			this.fRec32[0] = (fSlow15 + (0.999 * this.fRec32[1]));
			var fTemp1 = (0.4 * (this.fRec32[0] + -0.5));
			var fTemp2 = (this.fConst4 * (fTemp0 * (fTemp1 + 0.27)));
			var fTemp3 = (fTemp2 + -1.49999);
			var iTemp4 = fTemp3;
			var iTemp5 = (min_f(this.fConst3, max_i(0, iTemp4)) + 1);
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
			var iTemp16 = (min_f(this.fConst3, max_i(0, (iTemp4 + 2))) + 1);
			var fTemp17 = (0 - fTemp11);
			var fTemp18 = (0 - (0.5 * fTemp13));
			var iTemp19 = (min_f(this.fConst3, max_i(0, (iTemp4 + 1))) + 1);
			var fTemp20 = (0 - fTemp9);
			var fTemp21 = (0 - (0.5 * fTemp11));
			var fTemp22 = (0 - (0.333333 * fTemp13));
			var fTemp23 = (fTemp7 * fTemp9);
			var iTemp24 = (min_f(this.fConst3, max_i(0, (iTemp4 + 3))) + 1);
			var fTemp25 = (0 - fTemp13);
			var fTemp26 = (fTemp23 * fTemp11);
			var iTemp27 = (min_f(this.fConst3, max_i(0, (iTemp4 + 4))) + 1);
			this.fVec1[0] = (((((this.fRec29[((this.IOTA - iTemp5) & 2047)] * fTemp8) * fTemp10) * fTemp12) * fTemp14) + (fTemp15 * ((((0.5 * (((fTemp7 * this.fRec29[((this.IOTA - iTemp16) & 2047)]) * fTemp17) * fTemp18)) + (((this.fRec29[((this.IOTA - iTemp19) & 2047)] * fTemp20) * fTemp21) * fTemp22)) + (0.166667 * ((fTemp23 * this.fRec29[((this.IOTA - iTemp24) & 2047)]) * fTemp25))) + (0.0416667 * (fTemp26 * this.fRec29[((this.IOTA - iTemp27) & 2047)])))));
			var fTemp28 = (((fSlow1 * this.fRec23[0]) + (this.fRec25[0] * ((fSlow10 * (this.fRec26[2] + (this.fRec26[0] + (2 * this.fRec26[1])))) + 1))) - (0.5 * this.fVec1[1]));
			var fTemp29 = ((0.5 * this.fRec7[1]) + max_f(-1, min_f(1, (fTemp28 * (mydsp_faustpower2_f(fTemp28) + -1)))));
			this.fVec2[(this.IOTA & 2047)] = fTemp29;
			var fTemp30 = (this.fConst4 * (fTemp0 * (0.73 - fTemp1)));
			var fTemp31 = (fTemp30 + -1.49999);
			var iTemp32 = fTemp31;
			var iTemp33 = (min_f(this.fConst3, max_i(0, iTemp32)) + 1);
			var fTemp34 = Math.floor(fTemp31);
			var fTemp35 = (fTemp30 + (-1 - fTemp34));
			var fTemp36 = (0 - fTemp35);
			var fTemp37 = (fTemp30 + (-2 - fTemp34));
			var fTemp38 = (0 - (0.5 * fTemp37));
			var fTemp39 = (fTemp30 + (-3 - fTemp34));
			var fTemp40 = (0 - (0.333333 * fTemp39));
			var fTemp41 = (fTemp30 + (-4 - fTemp34));
			var fTemp42 = (0 - (0.25 * fTemp41));
			var fTemp43 = (fTemp30 - fTemp34);
			var iTemp44 = (min_f(this.fConst3, max_i(0, (iTemp32 + 2))) + 1);
			var fTemp45 = (0 - fTemp39);
			var fTemp46 = (0 - (0.5 * fTemp41));
			var iTemp47 = (min_f(this.fConst3, max_i(0, (iTemp32 + 1))) + 1);
			var fTemp48 = (0 - fTemp37);
			var fTemp49 = (0 - (0.5 * fTemp39));
			var fTemp50 = (0 - (0.333333 * fTemp41));
			var fTemp51 = (fTemp35 * fTemp37);
			var iTemp52 = (min_f(this.fConst3, max_i(0, (iTemp32 + 3))) + 1);
			var fTemp53 = (0 - fTemp41);
			var fTemp54 = (fTemp51 * fTemp39);
			var iTemp55 = (min_f(this.fConst3, max_i(0, (iTemp32 + 4))) + 1);
			this.fVec3[0] = (((((this.fVec2[((this.IOTA - iTemp33) & 2047)] * fTemp36) * fTemp38) * fTemp40) * fTemp42) + (fTemp43 * ((((0.5 * (((fTemp35 * this.fVec2[((this.IOTA - iTemp44) & 2047)]) * fTemp45) * fTemp46)) + (((this.fVec2[((this.IOTA - iTemp47) & 2047)] * fTemp48) * fTemp49) * fTemp50)) + (0.166667 * ((fTemp51 * this.fVec2[((this.IOTA - iTemp52) & 2047)]) * fTemp53))) + (0.0416667 * (fTemp54 * this.fVec2[((this.IOTA - iTemp55) & 2047)])))));
			this.fRec20[0] = this.fVec3[1];
			var iRec21 = iRec30;
			var fRec16 = fRec19;
			var fRec17 = this.fRec20[0];
			var fRec18 = (this.fRec20[0] + iRec21);
			this.fRec11[(this.IOTA & 2047)] = fRec16;
			var fRec12 = (((((fTemp36 * fTemp38) * fTemp40) * fTemp42) * this.fRec11[((this.IOTA - iTemp33) & 2047)]) + (fTemp43 * (((0.166667 * ((fTemp51 * fTemp53) * this.fRec11[((this.IOTA - iTemp52) & 2047)])) + ((((fTemp48 * fTemp49) * fTemp50) * this.fRec11[((this.IOTA - iTemp47) & 2047)]) + (0.5 * (((fTemp35 * fTemp45) * fTemp46) * this.fRec11[((this.IOTA - iTemp44) & 2047)])))) + (0.0416667 * (fTemp54 * this.fRec11[((this.IOTA - iTemp55) & 2047)])))));
			var fRec13 = fRec17;
			var fRec14 = fRec18;
			this.fRec7[0] = fRec12;
			var fRec8 = this.fRec7[1];
			var fRec9 = fRec13;
			var fRec10 = fRec14;
			this.fRec3[(this.IOTA & 2047)] = fRec8;
			var fRec4 = (((((fTemp8 * fTemp10) * fTemp12) * fTemp14) * this.fRec3[((this.IOTA - iTemp5) & 2047)]) + (fTemp15 * (((0.166667 * ((fTemp23 * fTemp25) * this.fRec3[((this.IOTA - iTemp24) & 2047)])) + ((((fTemp20 * fTemp21) * fTemp22) * this.fRec3[((this.IOTA - iTemp19) & 2047)]) + (0.5 * (((fTemp7 * fTemp17) * fTemp18) * this.fRec3[((this.IOTA - iTemp16) & 2047)])))) + (0.0416667 * (fTemp26 * this.fRec3[((this.IOTA - iTemp27) & 2047)])))));
			var fRec5 = fRec9;
			var fRec6 = fRec10;
			this.fRec1[0] = fRec4;
			this.fRec2[0] = fRec6;
			this.fRec0[0] = ((this.fRec2[0] + (0.995 * this.fRec0[1])) - this.fRec2[1]);
			var fTemp56 = (fSlow0 * this.fRec0[0]);
			output0[i] = fTemp56;
			output1[i] = fTemp56;
			this.iRec15[1] = this.iRec15[0];
			this.iVec0[1] = this.iVec0[0];
			this.fRec22[1] = this.fRec22[0];
			this.fRec23[1] = this.fRec23[0];
			this.fRec24[1] = this.fRec24[0];
			this.fRec25[1] = this.fRec25[0];
			this.iRec27[1] = this.iRec27[0];
			this.fRec26[2] = this.fRec26[1];
			this.fRec26[1] = this.fRec26[0];
			this.fRec28[1] = this.fRec28[0];
			this.IOTA = (this.IOTA + 1);
			this.fRec31[1] = this.fRec31[0];
			this.fRec32[1] = this.fRec32[0];
			this.fVec1[1] = this.fVec1[0];
			this.fVec3[1] = this.fVec3[0];
			this.fRec20[1] = this.fRec20[0];
			this.fRec7[1] = this.fRec7[0];
			this.fRec1[1] = this.fRec1[0];
			this.fRec2[1] = this.fRec2[0];
			this.fRec0[1] = this.fRec0[0];
			
		}
		
	}
	
}

