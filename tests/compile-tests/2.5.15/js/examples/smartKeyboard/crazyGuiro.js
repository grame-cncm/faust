
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.mydsp_faustpower2_f = function(value) {
	return (value * value);
	
}
this.max_i = function(dummy0, dummy1);
this.min_i = function(dummy0, dummy1);

function mydsp() {
	
	this.fHslider0;
	this.fRec9 = new Float32Array(2);
	this.fHslider1;
	this.fSamplingFreq;
	this.fConst0;
	this.fVec0 = new Float32Array(2);
	this.fConst1;
	this.fHslider2;
	this.fHslider3;
	this.iRec11 = new Int32Array(2);
	this.fButton0;
	this.fVec1 = new Float32Array(2);
	this.fConst2;
	this.fRec12 = new Float32Array(2);
	this.fConst3;
	this.fConst4;
	this.fRec10 = new Float32Array(3);
	this.IOTA;
	this.fVec2 = new Float32Array(8192);
	this.iConst5;
	this.fRec8 = new Float32Array(2);
	this.fRec14 = new Float32Array(2);
	this.fVec3 = new Float32Array(8192);
	this.iConst6;
	this.fRec13 = new Float32Array(2);
	this.fRec16 = new Float32Array(2);
	this.fVec4 = new Float32Array(8192);
	this.iConst7;
	this.fRec15 = new Float32Array(2);
	this.fRec18 = new Float32Array(2);
	this.fVec5 = new Float32Array(8192);
	this.iConst8;
	this.fRec17 = new Float32Array(2);
	this.fRec20 = new Float32Array(2);
	this.fVec6 = new Float32Array(8192);
	this.iConst9;
	this.fRec19 = new Float32Array(2);
	this.fRec22 = new Float32Array(2);
	this.fVec7 = new Float32Array(8192);
	this.iConst10;
	this.fRec21 = new Float32Array(2);
	this.fRec24 = new Float32Array(2);
	this.fVec8 = new Float32Array(8192);
	this.iConst11;
	this.fRec23 = new Float32Array(2);
	this.fRec26 = new Float32Array(2);
	this.fVec9 = new Float32Array(8192);
	this.iConst12;
	this.fRec25 = new Float32Array(2);
	this.fVec10 = new Float32Array(2048);
	this.iConst13;
	this.fRec6 = new Float32Array(2);
	this.fVec11 = new Float32Array(2048);
	this.iConst14;
	this.fRec4 = new Float32Array(2);
	this.fVec12 = new Float32Array(2048);
	this.iConst15;
	this.fRec2 = new Float32Array(2);
	this.fVec13 = new Float32Array(1024);
	this.iConst16;
	this.fRec0 = new Float32Array(2);
	
	this.metadata = function(m) { 
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("envelopes.lib/author", "GRAME");
		m.declare("envelopes.lib/copyright", "GRAME");
		m.declare("envelopes.lib/license", "LGPL with exception");
		m.declare("envelopes.lib/name", "Faust Envelope Library");
		m.declare("envelopes.lib/version", "0.0");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("interface", "SmartKeyboard{  'Number of Keyboards':'8',  'Keyboard 0 - Number of Keys':'16',  'Keyboard 1 - Number of Keys':'16',  'Keyboard 2 - Number of Keys':'16',  'Keyboard 3 - Number of Keys':'16',  'Keyboard 4 - Number of Keys':'16',  'Keyboard 5 - Number of Keys':'16',  'Keyboard 6 - Number of Keys':'16',  'Keyboard 7 - Number of Keys':'16',  'Keyboard 0 - Piano Keyboard':'0',  'Keyboard 1 - Piano Keyboard':'0',  'Keyboard 2 - Piano Keyboard':'0',  'Keyboard 3 - Piano Keyboard':'0',  'Keyboard 4 - Piano Keyboard':'0',  'Keyboard 5 - Piano Keyboard':'0',  'Keyboard 6 - Piano Keyboard':'0',  'Keyboard 7 - Piano Keyboard':'0' }");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "crazyGuiro");
		m.declare("noises.lib/name", "Faust Noise Generator Library");
		m.declare("noises.lib/version", "0.0");
		m.declare("reverbs.lib/name", "Faust Reverb Library");
		m.declare("reverbs.lib/version", "0.0");
		m.declare("synths.lib/name", "Faust Synthesizer Library");
		m.declare("synths.lib/version", "0.0");
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
		this.fConst1 = (1382.3 / this.fConst0);
		this.fConst2 = (0.002 * this.fConst0);
		this.fConst3 = (0.001 * this.fConst0);
		this.fConst4 = (1000 / this.fConst0);
		this.iConst5 = (0.0253061 * this.fConst0);
		this.iConst6 = (0.0269388 * this.fConst0);
		this.iConst7 = (0.0289569 * this.fConst0);
		this.iConst8 = (0.0307483 * this.fConst0);
		this.iConst9 = (0.0322449 * this.fConst0);
		this.iConst10 = (0.0338095 * this.fConst0);
		this.iConst11 = (0.0353061 * this.fConst0);
		this.iConst12 = (0.0366667 * this.fConst0);
		this.iConst13 = min_i(1024, max_i(0, ((0.0126077 * this.fConst0) + -1)));
		this.iConst14 = min_i(1024, max_i(0, ((0.01 * this.fConst0) + -1)));
		this.iConst15 = min_i(1024, max_i(0, ((0.00773243 * this.fConst0) + -1)));
		this.iConst16 = min_i(1024, max_i(0, ((0.00510204 * this.fConst0) + -1)));
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 0.5;
		this.fHslider1 = 0;
		this.fHslider2 = 0;
		this.fHslider3 = 0;
		this.fButton0 = 0;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.fRec9[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fVec0[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.iRec11[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fVec1[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec12[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 3); l5 = (l5 + 1)) {
			this.fRec10[l5] = 0;
			
		}
		this.IOTA = 0;
		for (var l6 = 0; (l6 < 8192); l6 = (l6 + 1)) {
			this.fVec2[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			this.fRec8[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			this.fRec14[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 8192); l9 = (l9 + 1)) {
			this.fVec3[l9] = 0;
			
		}
		for (var l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			this.fRec13[l10] = 0;
			
		}
		for (var l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			this.fRec16[l11] = 0;
			
		}
		for (var l12 = 0; (l12 < 8192); l12 = (l12 + 1)) {
			this.fVec4[l12] = 0;
			
		}
		for (var l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			this.fRec15[l13] = 0;
			
		}
		for (var l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			this.fRec18[l14] = 0;
			
		}
		for (var l15 = 0; (l15 < 8192); l15 = (l15 + 1)) {
			this.fVec5[l15] = 0;
			
		}
		for (var l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			this.fRec17[l16] = 0;
			
		}
		for (var l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			this.fRec20[l17] = 0;
			
		}
		for (var l18 = 0; (l18 < 8192); l18 = (l18 + 1)) {
			this.fVec6[l18] = 0;
			
		}
		for (var l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			this.fRec19[l19] = 0;
			
		}
		for (var l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			this.fRec22[l20] = 0;
			
		}
		for (var l21 = 0; (l21 < 8192); l21 = (l21 + 1)) {
			this.fVec7[l21] = 0;
			
		}
		for (var l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			this.fRec21[l22] = 0;
			
		}
		for (var l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			this.fRec24[l23] = 0;
			
		}
		for (var l24 = 0; (l24 < 8192); l24 = (l24 + 1)) {
			this.fVec8[l24] = 0;
			
		}
		for (var l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			this.fRec23[l25] = 0;
			
		}
		for (var l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			this.fRec26[l26] = 0;
			
		}
		for (var l27 = 0; (l27 < 8192); l27 = (l27 + 1)) {
			this.fVec9[l27] = 0;
			
		}
		for (var l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			this.fRec25[l28] = 0;
			
		}
		for (var l29 = 0; (l29 < 2048); l29 = (l29 + 1)) {
			this.fVec10[l29] = 0;
			
		}
		for (var l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			this.fRec6[l30] = 0;
			
		}
		for (var l31 = 0; (l31 < 2048); l31 = (l31 + 1)) {
			this.fVec11[l31] = 0;
			
		}
		for (var l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			this.fRec4[l32] = 0;
			
		}
		for (var l33 = 0; (l33 < 2048); l33 = (l33 + 1)) {
			this.fVec12[l33] = 0;
			
		}
		for (var l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			this.fRec2[l34] = 0;
			
		}
		for (var l35 = 0; (l35 < 1024); l35 = (l35 + 1)) {
			this.fVec13[l35] = 0;
			
		}
		for (var l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			this.fRec0[l36] = 0;
			
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
		ui_interface.openVerticalBox("crazyGuiro");
		ui_interface.addButton("gate", function handler(obj) { function setval(val) { obj.fButton0 = val; } return setval; }(this));
		ui_interface.addHorizontalSlider("key", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 0, 0, 2, 1);
		ui_interface.addHorizontalSlider("keyboard", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 0, 0, 2, 1);
		ui_interface.declare("fHslider0", "acc", "1 0 -10 0 10");
		ui_interface.addHorizontalSlider("res", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.declare("fHslider1", "acc", "0 0 -10 0 10");
		ui_interface.addHorizontalSlider("wet", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 0, 0, 1, 0.01);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = this.fHslider0;
		var fSlow1 = this.fHslider1;
		var fSlow2 = Math.tan((this.fConst1 * Math.pow(2, (0.0833333 * ((this.fHslider2 + (8 * this.fHslider3)) + -19)))));
		var fSlow3 = (1 / fSlow2);
		var fSlow4 = (((fSlow3 + 0.125) / fSlow2) + 1);
		var fSlow5 = (fSlow1 / fSlow4);
		var fSlow6 = this.fButton0;
		var fSlow7 = (1 / fSlow4);
		var fSlow8 = (((fSlow3 + -0.125) / fSlow2) + 1);
		var fSlow9 = (2 * (1 - (1 / mydsp_faustpower2_f(fSlow2))));
		var fSlow10 = (0 - fSlow3);
		var fSlow11 = ((1 - fSlow1) / fSlow4);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.fRec9[0] = (0.5 * (this.fRec9[1] + this.fRec8[1]));
			this.fVec0[0] = this.fConst0;
			this.iRec11[0] = ((1103515245 * this.iRec11[1]) + 12345);
			this.fVec1[0] = fSlow6;
			this.fRec12[0] = ((((fSlow6 - this.fVec1[1]) > 0) > 0)?0:min_f(this.fConst2, ((this.fRec12[1] + (0.002 * (this.fConst0 - this.fVec0[1]))) + 1)));
			var iTemp0 = (this.fRec12[0] < this.fConst3);
			this.fRec10[0] = ((4.65661e-10 * (this.iRec11[0] * (iTemp0?((this.fRec12[0] < 0)?0:(iTemp0?(this.fConst4 * this.fRec12[0]):1)):((this.fRec12[0] < this.fConst2)?((this.fConst4 * (0 - (this.fRec12[0] - this.fConst3))) + 1):0)))) - (fSlow7 * ((fSlow8 * this.fRec10[2]) + (fSlow9 * this.fRec10[1]))));
			var fTemp1 = ((fSlow3 * this.fRec10[0]) + (fSlow10 * this.fRec10[2]));
			var fTemp2 = (fSlow5 * fTemp1);
			this.fVec2[(this.IOTA & 8191)] = ((fSlow0 * this.fRec9[0]) + fTemp2);
			this.fRec8[0] = this.fVec2[((this.IOTA - this.iConst5) & 8191)];
			this.fRec14[0] = (0.5 * (this.fRec14[1] + this.fRec13[1]));
			this.fVec3[(this.IOTA & 8191)] = (fTemp2 + (fSlow0 * this.fRec14[0]));
			this.fRec13[0] = this.fVec3[((this.IOTA - this.iConst6) & 8191)];
			this.fRec16[0] = (0.5 * (this.fRec16[1] + this.fRec15[1]));
			this.fVec4[(this.IOTA & 8191)] = (fTemp2 + (fSlow0 * this.fRec16[0]));
			this.fRec15[0] = this.fVec4[((this.IOTA - this.iConst7) & 8191)];
			this.fRec18[0] = (0.5 * (this.fRec18[1] + this.fRec17[1]));
			this.fVec5[(this.IOTA & 8191)] = (fTemp2 + (fSlow0 * this.fRec18[0]));
			this.fRec17[0] = this.fVec5[((this.IOTA - this.iConst8) & 8191)];
			this.fRec20[0] = (0.5 * (this.fRec20[1] + this.fRec19[1]));
			this.fVec6[(this.IOTA & 8191)] = (fTemp2 + (fSlow0 * this.fRec20[0]));
			this.fRec19[0] = this.fVec6[((this.IOTA - this.iConst9) & 8191)];
			this.fRec22[0] = (0.5 * (this.fRec22[1] + this.fRec21[1]));
			this.fVec7[(this.IOTA & 8191)] = (fTemp2 + (fSlow0 * this.fRec22[0]));
			this.fRec21[0] = this.fVec7[((this.IOTA - this.iConst10) & 8191)];
			this.fRec24[0] = (0.5 * (this.fRec24[1] + this.fRec23[1]));
			this.fVec8[(this.IOTA & 8191)] = (fTemp2 + (fSlow0 * this.fRec24[0]));
			this.fRec23[0] = this.fVec8[((this.IOTA - this.iConst11) & 8191)];
			this.fRec26[0] = (0.5 * (this.fRec26[1] + this.fRec25[1]));
			this.fVec9[(this.IOTA & 8191)] = (fTemp2 + (fSlow0 * this.fRec26[0]));
			this.fRec25[0] = this.fVec9[((this.IOTA - this.iConst12) & 8191)];
			var fTemp3 = ((((((((this.fRec8[0] + this.fRec13[0]) + this.fRec15[0]) + this.fRec17[0]) + this.fRec19[0]) + this.fRec21[0]) + this.fRec23[0]) + this.fRec25[0]) + (0.5 * this.fRec6[1]));
			this.fVec10[(this.IOTA & 2047)] = fTemp3;
			this.fRec6[0] = this.fVec10[((this.IOTA - this.iConst13) & 2047)];
			var fRec7 = (0 - (0.5 * fTemp3));
			var fTemp4 = (this.fRec6[1] + (fRec7 + (0.5 * this.fRec4[1])));
			this.fVec11[(this.IOTA & 2047)] = fTemp4;
			this.fRec4[0] = this.fVec11[((this.IOTA - this.iConst14) & 2047)];
			var fRec5 = (0 - (0.5 * fTemp4));
			var fTemp5 = (this.fRec4[1] + (fRec5 + (0.5 * this.fRec2[1])));
			this.fVec12[(this.IOTA & 2047)] = fTemp5;
			this.fRec2[0] = this.fVec12[((this.IOTA - this.iConst15) & 2047)];
			var fRec3 = (0 - (0.5 * fTemp5));
			var fTemp6 = (this.fRec2[1] + (fRec3 + (0.5 * this.fRec0[1])));
			this.fVec13[(this.IOTA & 1023)] = fTemp6;
			this.fRec0[0] = this.fVec13[((this.IOTA - this.iConst16) & 1023)];
			var fRec1 = (0 - (0.5 * fTemp6));
			var fTemp7 = (this.fRec0[1] + (fRec1 + (fSlow11 * fTemp1)));
			output0[i] = fTemp7;
			output1[i] = fTemp7;
			this.fRec9[1] = this.fRec9[0];
			this.fVec0[1] = this.fVec0[0];
			this.iRec11[1] = this.iRec11[0];
			this.fVec1[1] = this.fVec1[0];
			this.fRec12[1] = this.fRec12[0];
			this.fRec10[2] = this.fRec10[1];
			this.fRec10[1] = this.fRec10[0];
			this.IOTA = (this.IOTA + 1);
			this.fRec8[1] = this.fRec8[0];
			this.fRec14[1] = this.fRec14[0];
			this.fRec13[1] = this.fRec13[0];
			this.fRec16[1] = this.fRec16[0];
			this.fRec15[1] = this.fRec15[0];
			this.fRec18[1] = this.fRec18[0];
			this.fRec17[1] = this.fRec17[0];
			this.fRec20[1] = this.fRec20[0];
			this.fRec19[1] = this.fRec19[0];
			this.fRec22[1] = this.fRec22[0];
			this.fRec21[1] = this.fRec21[0];
			this.fRec24[1] = this.fRec24[0];
			this.fRec23[1] = this.fRec23[0];
			this.fRec26[1] = this.fRec26[0];
			this.fRec25[1] = this.fRec25[0];
			this.fRec6[1] = this.fRec6[0];
			this.fRec4[1] = this.fRec4[0];
			this.fRec2[1] = this.fRec2[0];
			this.fRec0[1] = this.fRec0[0];
			
		}
		
	}
	
}

