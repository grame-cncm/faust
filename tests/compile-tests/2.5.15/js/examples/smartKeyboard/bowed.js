
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);

function mydsp() {
	
	this.iVec0 = new Int32Array(2);
	this.fHslider0;
	this.fRec2 = new Float32Array(2);
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fConst2;
	this.fRec1 = new Float32Array(2);
	this.fRec0 = new Float32Array(2);
	this.fConst3;
	this.fHslider1;
	this.fHslider2;
	this.fHslider3;
	this.fRec6 = new Float32Array(2);
	this.fRec5 = new Float32Array(2);
	this.fHslider4;
	this.fRec9 = new Float32Array(2);
	this.fRec7 = new Float32Array(2);
	this.fRec8 = new Float32Array(2);
	this.fRec12 = new Float32Array(2);
	this.fRec11 = new Float32Array(2);
	this.fRec10 = new Float32Array(2);
	this.fRec3 = new Float32Array(2);
	this.fRec4 = new Float32Array(2);
	this.fRec16 = new Float32Array(2);
	this.fRec15 = new Float32Array(2);
	this.fRec17 = new Float32Array(2);
	this.fRec18 = new Float32Array(2);
	this.fRec13 = new Float32Array(2);
	this.fRec14 = new Float32Array(2);
	this.fRec22 = new Float32Array(2);
	this.fRec21 = new Float32Array(2);
	this.fRec23 = new Float32Array(2);
	this.fRec24 = new Float32Array(2);
	this.fRec19 = new Float32Array(2);
	this.fRec20 = new Float32Array(2);
	this.fRec28 = new Float32Array(2);
	this.fRec27 = new Float32Array(2);
	this.fRec29 = new Float32Array(2);
	this.fRec30 = new Float32Array(2);
	this.fRec25 = new Float32Array(2);
	this.fRec26 = new Float32Array(2);
	
	this.metadata = function(m) { 
		m.declare("analyzers.lib/name", "Faust Analyzer Library");
		m.declare("analyzers.lib/version", "0.0");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("interface", "SmartKeyboard{  'Number of Keyboards':'5',  'Max Keyboard Polyphony':'0',  'Rounding Mode':'1',  'Keyboard 0 - Number of Keys':'19',  'Keyboard 1 - Number of Keys':'19',  'Keyboard 2 - Number of Keys':'19',  'Keyboard 3 - Number of Keys':'19',  'Keyboard 4 - Number of Keys':'1',  'Keyboard 4 - Send Freq':'0',  'Keyboard 0 - Send X':'0',  'Keyboard 1 - Send X':'0',  'Keyboard 2 - Send X':'0',  'Keyboard 3 - Send X':'0',  'Keyboard 0 - Send Y':'0',  'Keyboard 1 - Send Y':'0',  'Keyboard 2 - Send Y':'0',  'Keyboard 3 - Send Y':'0',  'Keyboard 0 - Lowest Key':'55',  'Keyboard 1 - Lowest Key':'62',  'Keyboard 2 - Lowest Key':'69',  'Keyboard 3 - Lowest Key':'76',  'Keyboard 4 - Piano Keyboard':'0',  'Keyboard 4 - Key 0 - Label':'Bow' }");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "bowed");
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
		this.fConst1 = Math.exp((0 - (10 / this.fConst0)));
		this.fConst2 = Math.exp((0 - (1 / this.fConst0)));
		this.fConst3 = (6.28319 / this.fConst0);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 0.5;
		this.fHslider1 = 0;
		this.fHslider2 = 400;
		this.fHslider3 = 1;
		this.fHslider4 = 0;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.iVec0[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec2[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec1[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec0[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec6[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fRec5[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			this.fRec9[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			this.fRec7[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			this.fRec8[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			this.fRec12[l9] = 0;
			
		}
		for (var l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			this.fRec11[l10] = 0;
			
		}
		for (var l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			this.fRec10[l11] = 0;
			
		}
		for (var l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			this.fRec3[l12] = 0;
			
		}
		for (var l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			this.fRec4[l13] = 0;
			
		}
		for (var l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			this.fRec16[l14] = 0;
			
		}
		for (var l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			this.fRec15[l15] = 0;
			
		}
		for (var l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			this.fRec17[l16] = 0;
			
		}
		for (var l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			this.fRec18[l17] = 0;
			
		}
		for (var l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			this.fRec13[l18] = 0;
			
		}
		for (var l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			this.fRec14[l19] = 0;
			
		}
		for (var l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			this.fRec22[l20] = 0;
			
		}
		for (var l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			this.fRec21[l21] = 0;
			
		}
		for (var l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			this.fRec23[l22] = 0;
			
		}
		for (var l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			this.fRec24[l23] = 0;
			
		}
		for (var l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			this.fRec19[l24] = 0;
			
		}
		for (var l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			this.fRec20[l25] = 0;
			
		}
		for (var l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			this.fRec28[l26] = 0;
			
		}
		for (var l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			this.fRec27[l27] = 0;
			
		}
		for (var l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			this.fRec29[l28] = 0;
			
		}
		for (var l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			this.fRec30[l29] = 0;
			
		}
		for (var l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			this.fRec25[l30] = 0;
			
		}
		for (var l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			this.fRec26[l31] = 0;
			
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
		ui_interface.openVerticalBox("bowed");
		ui_interface.addHorizontalSlider("bend", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 1, 0, 10, 0.01);
		ui_interface.addHorizontalSlider("freq", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 400, 50, 2000, 0.01);
		ui_interface.addHorizontalSlider("keyboard", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 0, 0, 5, 1);
		ui_interface.addHorizontalSlider("x", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.addHorizontalSlider("y", function handler(obj) { function setval(val) { obj.fHslider4 = val; } return setval; }(this), 0, 0, 1, 0.01);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = (0.001 * this.fHslider0);
		var iSlow1 = this.fHslider1;
		var iSlow2 = (iSlow1 == 3);
		var fSlow3 = (this.fHslider2 * this.fHslider3);
		var fSlow4 = (0.001 * this.fHslider4);
		var iSlow5 = (iSlow1 == 2);
		var iSlow6 = (iSlow1 == 0);
		var iSlow7 = (iSlow1 == 1);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iVec0[0] = 1;
			this.fRec2[0] = (fSlow0 + (0.999 * this.fRec2[1]));
			var fTemp0 = Math.abs(Math.abs((this.fRec2[0] - this.fRec2[1])));
			var fTemp1 = ((this.fRec0[1] > fTemp0)?this.fConst2:this.fConst1);
			this.fRec1[0] = ((this.fRec1[1] * fTemp1) + (fTemp0 * (1 - fTemp1)));
			this.fRec0[0] = this.fRec1[0];
			this.fRec6[0] = (iSlow2?fSlow3:this.fRec6[1]);
			this.fRec5[0] = ((0.999 * this.fRec5[1]) + (0.001 * this.fRec6[0]));
			this.fRec9[0] = (fSlow4 + (0.999 * this.fRec9[1]));
			var fTemp2 = ((0.3 * this.fRec9[0]) + 1);
			var fTemp3 = (this.fConst3 * (this.fRec5[0] * fTemp2));
			var fTemp4 = Math.sin(fTemp3);
			var fTemp5 = Math.cos(fTemp3);
			this.fRec7[0] = ((this.fRec8[1] * fTemp4) + (this.fRec7[1] * fTemp5));
			var iTemp6 = (1 - this.iVec0[1]);
			this.fRec8[0] = (((this.fRec8[1] * fTemp5) + (this.fRec7[1] * (0 - fTemp4))) + iTemp6);
			this.fRec12[0] = (fSlow0 + (0.999 * this.fRec12[1]));
			var fTemp7 = Math.abs(Math.abs((this.fRec12[0] - this.fRec12[1])));
			var fTemp8 = ((this.fRec10[1] > fTemp7)?this.fConst2:this.fConst1);
			this.fRec11[0] = ((this.fRec11[1] * fTemp8) + (fTemp7 * (1 - fTemp8)));
			this.fRec10[0] = this.fRec11[0];
			var fTemp9 = min_f(1, (8000 * this.fRec10[0]));
			var fTemp10 = (this.fConst3 * (this.fRec5[0] + (1000 * (this.fRec7[0] * fTemp9))));
			var fTemp11 = Math.sin(fTemp10);
			var fTemp12 = Math.cos(fTemp10);
			this.fRec3[0] = ((this.fRec4[1] * fTemp11) + (this.fRec3[1] * fTemp12));
			this.fRec4[0] = (((this.fRec4[1] * fTemp12) + (this.fRec3[1] * (0 - fTemp11))) + iTemp6);
			this.fRec16[0] = (iSlow5?fSlow3:this.fRec16[1]);
			this.fRec15[0] = ((0.999 * this.fRec15[1]) + (0.001 * this.fRec16[0]));
			var fTemp13 = (this.fConst3 * (this.fRec15[0] * fTemp2));
			var fTemp14 = Math.sin(fTemp13);
			var fTemp15 = Math.cos(fTemp13);
			this.fRec17[0] = ((this.fRec18[1] * fTemp14) + (this.fRec17[1] * fTemp15));
			this.fRec18[0] = (((this.fRec18[1] * fTemp15) + (this.fRec17[1] * (0 - fTemp14))) + iTemp6);
			var fTemp16 = (this.fConst3 * (this.fRec15[0] + (1000 * (this.fRec17[0] * fTemp9))));
			var fTemp17 = Math.sin(fTemp16);
			var fTemp18 = Math.cos(fTemp16);
			this.fRec13[0] = ((this.fRec14[1] * fTemp17) + (this.fRec13[1] * fTemp18));
			this.fRec14[0] = (((this.fRec14[1] * fTemp18) + (this.fRec13[1] * (0 - fTemp17))) + iTemp6);
			this.fRec22[0] = (iSlow6?fSlow3:this.fRec22[1]);
			this.fRec21[0] = ((0.999 * this.fRec21[1]) + (0.001 * this.fRec22[0]));
			var fTemp19 = (this.fConst3 * (this.fRec21[0] * fTemp2));
			var fTemp20 = Math.sin(fTemp19);
			var fTemp21 = Math.cos(fTemp19);
			this.fRec23[0] = ((this.fRec24[1] * fTemp20) + (this.fRec23[1] * fTemp21));
			this.fRec24[0] = (((this.fRec24[1] * fTemp21) + (this.fRec23[1] * (0 - fTemp20))) + iTemp6);
			var fTemp22 = (this.fConst3 * (this.fRec21[0] + (1000 * (this.fRec23[0] * fTemp9))));
			var fTemp23 = Math.sin(fTemp22);
			var fTemp24 = Math.cos(fTemp22);
			this.fRec19[0] = ((this.fRec20[1] * fTemp23) + (this.fRec19[1] * fTemp24));
			this.fRec20[0] = (((this.fRec20[1] * fTemp24) + (this.fRec19[1] * (0 - fTemp23))) + iTemp6);
			this.fRec28[0] = (iSlow7?fSlow3:this.fRec28[1]);
			this.fRec27[0] = ((0.999 * this.fRec27[1]) + (0.001 * this.fRec28[0]));
			var fTemp25 = (this.fConst3 * (this.fRec27[0] * fTemp2));
			var fTemp26 = Math.sin(fTemp25);
			var fTemp27 = Math.cos(fTemp25);
			this.fRec29[0] = ((this.fRec30[1] * fTemp26) + (this.fRec29[1] * fTemp27));
			this.fRec30[0] = (((this.fRec30[1] * fTemp27) + (this.fRec29[1] * (0 - fTemp26))) + iTemp6);
			var fTemp28 = (this.fConst3 * (this.fRec27[0] + (1000 * (this.fRec29[0] * fTemp9))));
			var fTemp29 = Math.sin(fTemp28);
			var fTemp30 = Math.cos(fTemp28);
			this.fRec25[0] = ((this.fRec26[1] * fTemp29) + (this.fRec25[1] * fTemp30));
			this.fRec26[0] = (((this.fRec26[1] * fTemp30) + (this.fRec25[1] * (0 - fTemp29))) + iTemp6);
			var fTemp31 = (min_f(1, (8000 * this.fRec0[0])) * (this.fRec3[0] + (this.fRec13[0] + (this.fRec19[0] + this.fRec25[0]))));
			output0[i] = fTemp31;
			output1[i] = fTemp31;
			this.iVec0[1] = this.iVec0[0];
			this.fRec2[1] = this.fRec2[0];
			this.fRec1[1] = this.fRec1[0];
			this.fRec0[1] = this.fRec0[0];
			this.fRec6[1] = this.fRec6[0];
			this.fRec5[1] = this.fRec5[0];
			this.fRec9[1] = this.fRec9[0];
			this.fRec7[1] = this.fRec7[0];
			this.fRec8[1] = this.fRec8[0];
			this.fRec12[1] = this.fRec12[0];
			this.fRec11[1] = this.fRec11[0];
			this.fRec10[1] = this.fRec10[0];
			this.fRec3[1] = this.fRec3[0];
			this.fRec4[1] = this.fRec4[0];
			this.fRec16[1] = this.fRec16[0];
			this.fRec15[1] = this.fRec15[0];
			this.fRec17[1] = this.fRec17[0];
			this.fRec18[1] = this.fRec18[0];
			this.fRec13[1] = this.fRec13[0];
			this.fRec14[1] = this.fRec14[0];
			this.fRec22[1] = this.fRec22[0];
			this.fRec21[1] = this.fRec21[0];
			this.fRec23[1] = this.fRec23[0];
			this.fRec24[1] = this.fRec24[0];
			this.fRec19[1] = this.fRec19[0];
			this.fRec20[1] = this.fRec20[0];
			this.fRec28[1] = this.fRec28[0];
			this.fRec27[1] = this.fRec27[0];
			this.fRec29[1] = this.fRec29[0];
			this.fRec30[1] = this.fRec30[0];
			this.fRec25[1] = this.fRec25[0];
			this.fRec26[1] = this.fRec26[0];
			
		}
		
	}
	
}

