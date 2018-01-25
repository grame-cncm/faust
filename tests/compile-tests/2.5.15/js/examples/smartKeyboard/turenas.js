
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);

function mydsp() {
	
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fHslider0;
	this.fHslider1;
	this.iVec0 = new Int32Array(2);
	this.fRec0 = new Float32Array(2);
	this.fRec1 = new Float32Array(2);
	this.fButton0;
	this.fVec1 = new Float32Array(2);
	this.fHslider2;
	this.fRec3 = new Float32Array(2);
	this.fVec2 = new Float32Array(2);
	this.fRec2 = new Float32Array(2);
	this.fConst2;
	this.fConst3;
	this.fConst4;
	this.fRec4 = new Float32Array(2);
	this.fRec5 = new Float32Array(2);
	this.fVec3 = new Float32Array(2);
	this.fRec6 = new Float32Array(2);
	this.fRec7 = new Float32Array(2);
	this.fRec8 = new Float32Array(2);
	this.fVec4 = new Float32Array(2);
	this.fRec9 = new Float32Array(2);
	this.fRec10 = new Float32Array(2);
	this.fRec11 = new Float32Array(2);
	this.fVec5 = new Float32Array(2);
	this.fRec12 = new Float32Array(2);
	this.fRec13 = new Float32Array(2);
	this.fRec14 = new Float32Array(2);
	this.fVec6 = new Float32Array(2);
	this.fRec15 = new Float32Array(2);
	this.fRec16 = new Float32Array(2);
	this.fRec17 = new Float32Array(2);
	this.fVec7 = new Float32Array(2);
	this.fRec18 = new Float32Array(2);
	
	this.metadata = function(m) { 
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("envelopes.lib/author", "GRAME");
		m.declare("envelopes.lib/copyright", "GRAME");
		m.declare("envelopes.lib/license", "LGPL with exception");
		m.declare("envelopes.lib/name", "Faust Envelope Library");
		m.declare("envelopes.lib/version", "0.0");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("interface", "SmartKeyboard{  'Number of Keyboards':'10',  'Keyboard 0 - Number of Keys':'18',  'Keyboard 1 - Number of Keys':'18',  'Keyboard 2 - Number of Keys':'18',  'Keyboard 3 - Number of Keys':'18',  'Keyboard 4 - Number of Keys':'18',  'Keyboard 5 - Number of Keys':'18',  'Keyboard 6 - Number of Keys':'18',  'Keyboard 7 - Number of Keys':'18',  'Keyboard 8 - Number of Keys':'18',  'Keyboard 9 - Number of Keys':'18',  'Keyboard 0 - Lowest Key':'50',  'Keyboard 1 - Lowest Key':'55',  'Keyboard 2 - Lowest Key':'60',  'Keyboard 3 - Lowest Key':'65',  'Keyboard 4 - Lowest Key':'70',  'Keyboard 5 - Lowest Key':'75',  'Keyboard 6 - Lowest Key':'80',  'Keyboard 7 - Lowest Key':'85',  'Keyboard 8 - Lowest Key':'90',  'Keyboard 9 - Lowest Key':'95',  'Keyboard 0 - Piano Keyboard':'0',  'Keyboard 1 - Piano Keyboard':'0',  'Keyboard 2 - Piano Keyboard':'0',  'Keyboard 3 - Piano Keyboard':'0',  'Keyboard 4 - Piano Keyboard':'0',  'Keyboard 5 - Piano Keyboard':'0',  'Keyboard 6 - Piano Keyboard':'0',  'Keyboard 7 - Piano Keyboard':'0',  'Keyboard 8 - Piano Keyboard':'0',  'Keyboard 9 - Piano Keyboard':'0',  'Keyboard 0 - Send X':'0',  'Keyboard 1 - Send X':'0',  'Keyboard 2 - Send X':'0',  'Keyboard 3 - Send X':'0',  'Keyboard 4 - Send X':'0',  'Keyboard 5 - Send X':'0',  'Keyboard 6 - Send X':'0',  'Keyboard 7 - Send X':'0',  'Keyboard 8 - Send X':'0',  'Keyboard 9 - Send X':'0' }");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "turenas");
		m.declare("oscillators.lib/name", "Faust Oscillator Library");
		m.declare("oscillators.lib/version", "0.0");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
		m.declare("synths.lib/name", "Faust Synthesizer Library");
		m.declare("synths.lib/version", "0.0");
	}

	this.getNumInputs = function() {
		return 0;
		
	}
	this.getNumOutputs = function() {
		return 1;
		
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
		this.fConst2 = (0.001 * this.fConst0);
		this.fConst3 = (1 / this.fConst0);
		this.fConst4 = (1000 / this.fConst0);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 400;
		this.fHslider1 = 0;
		this.fButton0 = 0;
		this.fHslider2 = 2.5;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.iVec0[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec0[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec1[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fVec1[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec3[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fVec2[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			this.fRec2[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			this.fRec4[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			this.fRec5[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			this.fVec3[l9] = 0;
			
		}
		for (var l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			this.fRec6[l10] = 0;
			
		}
		for (var l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			this.fRec7[l11] = 0;
			
		}
		for (var l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			this.fRec8[l12] = 0;
			
		}
		for (var l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			this.fVec4[l13] = 0;
			
		}
		for (var l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			this.fRec9[l14] = 0;
			
		}
		for (var l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			this.fRec10[l15] = 0;
			
		}
		for (var l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			this.fRec11[l16] = 0;
			
		}
		for (var l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			this.fVec5[l17] = 0;
			
		}
		for (var l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			this.fRec12[l18] = 0;
			
		}
		for (var l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			this.fRec13[l19] = 0;
			
		}
		for (var l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			this.fRec14[l20] = 0;
			
		}
		for (var l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			this.fVec6[l21] = 0;
			
		}
		for (var l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			this.fRec15[l22] = 0;
			
		}
		for (var l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			this.fRec16[l23] = 0;
			
		}
		for (var l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			this.fRec17[l24] = 0;
			
		}
		for (var l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			this.fVec7[l25] = 0;
			
		}
		for (var l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			this.fRec18[l26] = 0;
			
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
		ui_interface.openVerticalBox("turenas");
		ui_interface.addHorizontalSlider("freq", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 400, 50, 2000, 0.01);
		ui_interface.addButton("gate", function handler(obj) { function setval(val) { obj.fButton0 = val; } return setval; }(this));
		ui_interface.declare("fHslider2", "acc", "0 0 -10 0 10");
		ui_interface.addHorizontalSlider("res", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 2.5, 0.01, 5, 0.01);
		ui_interface.addHorizontalSlider("y", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 0, 0, 1, 0.01);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var output0 = outputs[0];
		var fSlow0 = this.fHslider0;
		var fSlow1 = this.fHslider1;
		var fSlow2 = (this.fConst1 * (fSlow0 * ((0.833333 * fSlow1) + 1)));
		var fSlow3 = Math.sin(fSlow2);
		var fSlow4 = Math.cos(fSlow2);
		var fSlow5 = (0 - fSlow3);
		var fSlow6 = this.fButton0;
		var fSlow7 = (0.001 * this.fHslider2);
		var fSlow8 = (this.fConst1 * (fSlow0 * ((1.66667 * fSlow1) + 1)));
		var fSlow9 = Math.sin(fSlow8);
		var fSlow10 = Math.cos(fSlow8);
		var fSlow11 = (0 - fSlow9);
		var fSlow12 = (this.fConst1 * (fSlow0 * ((2.5 * fSlow1) + 1)));
		var fSlow13 = Math.sin(fSlow12);
		var fSlow14 = Math.cos(fSlow12);
		var fSlow15 = (0 - fSlow13);
		var fSlow16 = (this.fConst1 * (fSlow0 * ((3.33333 * fSlow1) + 1)));
		var fSlow17 = Math.sin(fSlow16);
		var fSlow18 = Math.cos(fSlow16);
		var fSlow19 = (0 - fSlow17);
		var fSlow20 = (this.fConst1 * (fSlow0 * ((4.16667 * fSlow1) + 1)));
		var fSlow21 = Math.sin(fSlow20);
		var fSlow22 = Math.cos(fSlow20);
		var fSlow23 = (0 - fSlow21);
		var fSlow24 = (this.fConst1 * (fSlow0 * ((5 * fSlow1) + 1)));
		var fSlow25 = Math.sin(fSlow24);
		var fSlow26 = Math.cos(fSlow24);
		var fSlow27 = (0 - fSlow25);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iVec0[0] = 1;
			this.fRec0[0] = ((fSlow3 * this.fRec1[1]) + (fSlow4 * this.fRec0[1]));
			var iTemp0 = (1 - this.iVec0[1]);
			this.fRec1[0] = (((fSlow4 * this.fRec1[1]) + (fSlow5 * this.fRec0[1])) + iTemp0);
			this.fVec1[0] = fSlow6;
			var iTemp1 = (((fSlow6 - this.fVec1[1]) > 0) > 0);
			this.fRec3[0] = (fSlow7 + (0.999 * this.fRec3[1]));
			var fTemp2 = (this.fRec3[0] + 0.001);
			this.fVec2[0] = fTemp2;
			var fTemp3 = (this.fConst0 * fTemp2);
			this.fRec2[0] = (iTemp1?0:min_f(fTemp3, (this.fRec2[1] + (1 - (this.fConst0 * (this.fVec2[1] - fTemp2))))));
			var iTemp4 = (this.fRec2[0] < this.fConst2);
			this.fRec4[0] = ((fSlow9 * this.fRec5[1]) + (fSlow10 * this.fRec4[1]));
			this.fRec5[0] = (((fSlow10 * this.fRec5[1]) + (fSlow11 * this.fRec4[1])) + iTemp0);
			var fTemp5 = ((0.866667 * this.fRec3[0]) + 0.001);
			this.fVec3[0] = fTemp5;
			var fTemp6 = (this.fConst0 * fTemp5);
			this.fRec6[0] = (iTemp1?0:min_f(fTemp6, (this.fRec6[1] + (1 - (this.fConst0 * (this.fVec3[1] - fTemp5))))));
			var iTemp7 = (this.fRec6[0] < this.fConst2);
			this.fRec7[0] = ((fSlow13 * this.fRec8[1]) + (fSlow14 * this.fRec7[1]));
			this.fRec8[0] = (((fSlow14 * this.fRec8[1]) + (fSlow15 * this.fRec7[1])) + iTemp0);
			var fTemp8 = ((0.733333 * this.fRec3[0]) + 0.001);
			this.fVec4[0] = fTemp8;
			var fTemp9 = (this.fConst0 * fTemp8);
			this.fRec9[0] = (iTemp1?0:min_f(fTemp9, (this.fRec9[1] + (1 - (this.fConst0 * (this.fVec4[1] - fTemp8))))));
			var iTemp10 = (this.fRec9[0] < this.fConst2);
			this.fRec10[0] = ((fSlow17 * this.fRec11[1]) + (fSlow18 * this.fRec10[1]));
			this.fRec11[0] = (((fSlow18 * this.fRec11[1]) + (fSlow19 * this.fRec10[1])) + iTemp0);
			var fTemp11 = ((0.6 * this.fRec3[0]) + 0.001);
			this.fVec5[0] = fTemp11;
			var fTemp12 = (this.fConst0 * fTemp11);
			this.fRec12[0] = (iTemp1?0:min_f(fTemp12, (this.fRec12[1] + (1 - (this.fConst0 * (this.fVec5[1] - fTemp11))))));
			var iTemp13 = (this.fRec12[0] < this.fConst2);
			this.fRec13[0] = ((fSlow21 * this.fRec14[1]) + (fSlow22 * this.fRec13[1]));
			this.fRec14[0] = (((fSlow22 * this.fRec14[1]) + (fSlow23 * this.fRec13[1])) + iTemp0);
			var fTemp14 = ((0.466667 * this.fRec3[0]) + 0.001);
			this.fVec6[0] = fTemp14;
			var fTemp15 = (this.fConst0 * fTemp14);
			this.fRec15[0] = (iTemp1?0:min_f(fTemp15, (this.fRec15[1] + (1 - (this.fConst0 * (this.fVec6[1] - fTemp14))))));
			var iTemp16 = (this.fRec15[0] < this.fConst2);
			this.fRec16[0] = ((fSlow25 * this.fRec17[1]) + (fSlow26 * this.fRec16[1]));
			this.fRec17[0] = (((fSlow26 * this.fRec17[1]) + (fSlow27 * this.fRec16[1])) + iTemp0);
			var fTemp17 = ((0.333333 * this.fRec3[0]) + 0.001);
			this.fVec7[0] = fTemp17;
			var fTemp18 = (this.fConst0 * fTemp17);
			this.fRec18[0] = (iTemp1?0:min_f(fTemp18, (this.fRec18[1] + (1 - (this.fConst0 * (this.fVec7[1] - fTemp17))))));
			var iTemp19 = (this.fRec18[0] < this.fConst2);
			output0[i] = (0.05 * ((((((0.444444 * (this.fRec0[0] * (iTemp4?((this.fRec2[0] < 0)?0:(iTemp4?(this.fConst4 * this.fRec2[0]):1)):((this.fRec2[0] < fTemp3)?((this.fConst3 * ((0 - (this.fRec2[0] - this.fConst2)) / (fTemp2 + -0.001))) + 1):0)))) + (this.fRec4[0] * (0 - (0.111111 * (iTemp7?((this.fRec6[0] < 0)?0:(iTemp7?(this.fConst4 * this.fRec6[0]):1)):((this.fRec6[0] < fTemp6)?((this.fConst3 * ((0 - (this.fRec6[0] - this.fConst2)) / (fTemp5 + -0.001))) + 1):0)))))) + (this.fRec7[0] * (0 - (0.666667 * (iTemp10?((this.fRec9[0] < 0)?0:(iTemp10?(this.fConst4 * this.fRec9[0]):1)):((this.fRec9[0] < fTemp9)?((this.fConst3 * ((0 - (this.fRec9[0] - this.fConst2)) / (fTemp8 + -0.001))) + 1):0)))))) + (this.fRec10[0] * (0 - (1.22222 * (iTemp13?((this.fRec12[0] < 0)?0:(iTemp13?(this.fConst4 * this.fRec12[0]):1)):((this.fRec12[0] < fTemp12)?((this.fConst3 * ((0 - (this.fRec12[0] - this.fConst2)) / (fTemp11 + -0.001))) + 1):0)))))) + (this.fRec13[0] * (0 - (1.77778 * (iTemp16?((this.fRec15[0] < 0)?0:(iTemp16?(this.fConst4 * this.fRec15[0]):1)):((this.fRec15[0] < fTemp15)?((this.fConst3 * ((0 - (this.fRec15[0] - this.fConst2)) / (fTemp14 + -0.001))) + 1):0)))))) + (this.fRec16[0] * (0 - (2.33333 * (iTemp19?((this.fRec18[0] < 0)?0:(iTemp19?(this.fConst4 * this.fRec18[0]):1)):((this.fRec18[0] < fTemp18)?((this.fConst3 * ((0 - (this.fRec18[0] - this.fConst2)) / (fTemp17 + -0.001))) + 1):0)))))));
			this.iVec0[1] = this.iVec0[0];
			this.fRec0[1] = this.fRec0[0];
			this.fRec1[1] = this.fRec1[0];
			this.fVec1[1] = this.fVec1[0];
			this.fRec3[1] = this.fRec3[0];
			this.fVec2[1] = this.fVec2[0];
			this.fRec2[1] = this.fRec2[0];
			this.fRec4[1] = this.fRec4[0];
			this.fRec5[1] = this.fRec5[0];
			this.fVec3[1] = this.fVec3[0];
			this.fRec6[1] = this.fRec6[0];
			this.fRec7[1] = this.fRec7[0];
			this.fRec8[1] = this.fRec8[0];
			this.fVec4[1] = this.fVec4[0];
			this.fRec9[1] = this.fRec9[0];
			this.fRec10[1] = this.fRec10[0];
			this.fRec11[1] = this.fRec11[0];
			this.fVec5[1] = this.fVec5[0];
			this.fRec12[1] = this.fRec12[0];
			this.fRec13[1] = this.fRec13[0];
			this.fRec14[1] = this.fRec14[0];
			this.fVec6[1] = this.fVec6[0];
			this.fRec15[1] = this.fRec15[0];
			this.fRec16[1] = this.fRec16[0];
			this.fRec17[1] = this.fRec17[0];
			this.fVec7[1] = this.fVec7[0];
			this.fRec18[1] = this.fRec18[0];
			
		}
		
	}
	
}

