
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
	
	this.iRec10 = new Int32Array(2);
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fConst2;
	this.fConst3;
	this.fConst4;
	this.fConst5;
	this.fHslider0;
	this.fHslider1;
	this.fRec26 = new Float32Array(2);
	this.fRec22 = new Float32Array(2);
	this.fHslider2;
	this.fHslider3;
	this.fRec28 = new Float32Array(2);
	this.fRec27 = new Float32Array(2);
	this.fRec29 = new Float32Array(4);
	this.IOTA;
	this.fRec30 = new Float32Array(2048);
	this.fConst6;
	this.fVec0 = new Float32Array(2);
	this.fVec1 = new Float32Array(2048);
	this.fRec18 = new Float32Array(2048);
	this.fRec20 = new Float32Array(2);
	this.fRec16 = new Float32Array(4);
	this.fConst7;
	this.fConst8;
	this.fRec14 = new Float32Array(3);
	this.fConst9;
	this.iRec6 = new Int32Array(2);
	this.fRec2 = new Float32Array(2048);
	this.fRec0 = new Float32Array(2);
	this.iRec42 = new Int32Array(2);
	this.fHslider4;
	this.fHslider5;
	this.fRec58 = new Float32Array(2);
	this.fRec54 = new Float32Array(2);
	this.fHslider6;
	this.fRec59 = new Float32Array(4);
	this.fRec60 = new Float32Array(2048);
	this.fVec2 = new Float32Array(2);
	this.fVec3 = new Float32Array(2048);
	this.fRec50 = new Float32Array(2048);
	this.fRec52 = new Float32Array(2);
	this.fRec48 = new Float32Array(4);
	this.fRec46 = new Float32Array(3);
	this.iRec38 = new Int32Array(2);
	this.fRec34 = new Float32Array(2048);
	this.fRec32 = new Float32Array(2);
	this.iRec72 = new Int32Array(2);
	this.fHslider7;
	this.fHslider8;
	this.fRec88 = new Float32Array(2);
	this.fRec84 = new Float32Array(2);
	this.fHslider9;
	this.fRec89 = new Float32Array(4);
	this.fRec90 = new Float32Array(2048);
	this.fVec4 = new Float32Array(2);
	this.fVec5 = new Float32Array(2048);
	this.fRec80 = new Float32Array(2048);
	this.fRec82 = new Float32Array(2);
	this.fRec78 = new Float32Array(4);
	this.fRec76 = new Float32Array(3);
	this.iRec68 = new Int32Array(2);
	this.fRec64 = new Float32Array(2048);
	this.fRec62 = new Float32Array(2);
	this.iRec102 = new Int32Array(2);
	this.fHslider10;
	this.fHslider11;
	this.fRec118 = new Float32Array(2);
	this.fRec114 = new Float32Array(2);
	this.fHslider12;
	this.fRec119 = new Float32Array(4);
	this.fRec120 = new Float32Array(2048);
	this.fVec6 = new Float32Array(2);
	this.fVec7 = new Float32Array(2048);
	this.fRec110 = new Float32Array(2048);
	this.fRec112 = new Float32Array(2);
	this.fRec108 = new Float32Array(4);
	this.fRec106 = new Float32Array(3);
	this.iRec98 = new Int32Array(2);
	this.fRec94 = new Float32Array(2048);
	this.fRec92 = new Float32Array(2);
	
	this.metadata = function(m) { 
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("interface", "SmartKeyboard{  'Number of Keyboards':'4',  'Max Keyboard Polyphony':'0',  'Rounding Mode':'2',  'Send Fingers Count':'1',  'Keyboard 0 - Number of Keys':'12',  'Keyboard 1 - Number of Keys':'12',  'Keyboard 2 - Number of Keys':'12',  'Keyboard 3 - Number of Keys':'12',  'Keyboard 0 - Lowest Key':'55',  'Keyboard 1 - Lowest Key':'62',  'Keyboard 2 - Lowest Key':'69',  'Keyboard 3 - Lowest Key':'76',  'Keyboard 0 - Send Keyboard Freq':'1',  'Keyboard 1 - Send Keyboard Freq':'1',  'Keyboard 2 - Send Keyboard Freq':'1',  'Keyboard 3 - Send Keyboard Freq':'1',  'Keyboard 0 - Send Y':'1',  'Keyboard 1 - Send Y':'1',  'Keyboard 2 - Send Y':'1',  'Keyboard 3 - Send Y':'1' }");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "violin2");
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
		this.fConst5 = (0.000441176 * this.fConst0);
		this.fConst6 = (0.00102941 * this.fConst0);
		this.fConst7 = (((this.fConst2 + -0.5) / this.fConst1) + 1);
		this.fConst8 = (2 * (1 - (1 / mydsp_faustpower2_f(this.fConst1))));
		this.fConst9 = (0 - this.fConst2);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 220;
		this.fHslider1 = 1;
		this.fHslider2 = 0;
		this.fHslider3 = 0;
		this.fHslider4 = 330;
		this.fHslider5 = 1;
		this.fHslider6 = 0;
		this.fHslider7 = 440;
		this.fHslider8 = 1;
		this.fHslider9 = 0;
		this.fHslider10 = 550;
		this.fHslider11 = 1;
		this.fHslider12 = 0;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.iRec10[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec26[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec22[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec28[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec27[l4] = 0;
			
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
		for (var l8 = 0; (l8 < 2048); l8 = (l8 + 1)) {
			this.fVec1[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 2048); l9 = (l9 + 1)) {
			this.fRec18[l9] = 0;
			
		}
		for (var l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			this.fRec20[l10] = 0;
			
		}
		for (var l11 = 0; (l11 < 4); l11 = (l11 + 1)) {
			this.fRec16[l11] = 0;
			
		}
		for (var l12 = 0; (l12 < 3); l12 = (l12 + 1)) {
			this.fRec14[l12] = 0;
			
		}
		for (var l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			this.iRec6[l13] = 0;
			
		}
		for (var l14 = 0; (l14 < 2048); l14 = (l14 + 1)) {
			this.fRec2[l14] = 0;
			
		}
		for (var l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			this.fRec0[l15] = 0;
			
		}
		for (var l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			this.iRec42[l16] = 0;
			
		}
		for (var l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			this.fRec58[l17] = 0;
			
		}
		for (var l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			this.fRec54[l18] = 0;
			
		}
		for (var l19 = 0; (l19 < 4); l19 = (l19 + 1)) {
			this.fRec59[l19] = 0;
			
		}
		for (var l20 = 0; (l20 < 2048); l20 = (l20 + 1)) {
			this.fRec60[l20] = 0;
			
		}
		for (var l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			this.fVec2[l21] = 0;
			
		}
		for (var l22 = 0; (l22 < 2048); l22 = (l22 + 1)) {
			this.fVec3[l22] = 0;
			
		}
		for (var l23 = 0; (l23 < 2048); l23 = (l23 + 1)) {
			this.fRec50[l23] = 0;
			
		}
		for (var l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			this.fRec52[l24] = 0;
			
		}
		for (var l25 = 0; (l25 < 4); l25 = (l25 + 1)) {
			this.fRec48[l25] = 0;
			
		}
		for (var l26 = 0; (l26 < 3); l26 = (l26 + 1)) {
			this.fRec46[l26] = 0;
			
		}
		for (var l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			this.iRec38[l27] = 0;
			
		}
		for (var l28 = 0; (l28 < 2048); l28 = (l28 + 1)) {
			this.fRec34[l28] = 0;
			
		}
		for (var l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			this.fRec32[l29] = 0;
			
		}
		for (var l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			this.iRec72[l30] = 0;
			
		}
		for (var l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			this.fRec88[l31] = 0;
			
		}
		for (var l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			this.fRec84[l32] = 0;
			
		}
		for (var l33 = 0; (l33 < 4); l33 = (l33 + 1)) {
			this.fRec89[l33] = 0;
			
		}
		for (var l34 = 0; (l34 < 2048); l34 = (l34 + 1)) {
			this.fRec90[l34] = 0;
			
		}
		for (var l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			this.fVec4[l35] = 0;
			
		}
		for (var l36 = 0; (l36 < 2048); l36 = (l36 + 1)) {
			this.fVec5[l36] = 0;
			
		}
		for (var l37 = 0; (l37 < 2048); l37 = (l37 + 1)) {
			this.fRec80[l37] = 0;
			
		}
		for (var l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			this.fRec82[l38] = 0;
			
		}
		for (var l39 = 0; (l39 < 4); l39 = (l39 + 1)) {
			this.fRec78[l39] = 0;
			
		}
		for (var l40 = 0; (l40 < 3); l40 = (l40 + 1)) {
			this.fRec76[l40] = 0;
			
		}
		for (var l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			this.iRec68[l41] = 0;
			
		}
		for (var l42 = 0; (l42 < 2048); l42 = (l42 + 1)) {
			this.fRec64[l42] = 0;
			
		}
		for (var l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			this.fRec62[l43] = 0;
			
		}
		for (var l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			this.iRec102[l44] = 0;
			
		}
		for (var l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			this.fRec118[l45] = 0;
			
		}
		for (var l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			this.fRec114[l46] = 0;
			
		}
		for (var l47 = 0; (l47 < 4); l47 = (l47 + 1)) {
			this.fRec119[l47] = 0;
			
		}
		for (var l48 = 0; (l48 < 2048); l48 = (l48 + 1)) {
			this.fRec120[l48] = 0;
			
		}
		for (var l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			this.fVec6[l49] = 0;
			
		}
		for (var l50 = 0; (l50 < 2048); l50 = (l50 + 1)) {
			this.fVec7[l50] = 0;
			
		}
		for (var l51 = 0; (l51 < 2048); l51 = (l51 + 1)) {
			this.fRec110[l51] = 0;
			
		}
		for (var l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			this.fRec112[l52] = 0;
			
		}
		for (var l53 = 0; (l53 < 4); l53 = (l53 + 1)) {
			this.fRec108[l53] = 0;
			
		}
		for (var l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			this.fRec106[l54] = 0;
			
		}
		for (var l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			this.iRec98[l55] = 0;
			
		}
		for (var l56 = 0; (l56 < 2048); l56 = (l56 + 1)) {
			this.fRec94[l56] = 0;
			
		}
		for (var l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			this.fRec92[l57] = 0;
			
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
		ui_interface.openVerticalBox("violin2");
		ui_interface.addHorizontalSlider("kb0bend", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 1, 0, 10, 0.01);
		ui_interface.addHorizontalSlider("kb0fingers", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 0, 0, 10, 1);
		ui_interface.addHorizontalSlider("kb0freq", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 220, 20, 10000, 0.01);
		ui_interface.addHorizontalSlider("kb1bend", function handler(obj) { function setval(val) { obj.fHslider5 = val; } return setval; }(this), 1, 0, 10, 0.01);
		ui_interface.addHorizontalSlider("kb1fingers", function handler(obj) { function setval(val) { obj.fHslider6 = val; } return setval; }(this), 0, 0, 10, 1);
		ui_interface.addHorizontalSlider("kb1freq", function handler(obj) { function setval(val) { obj.fHslider4 = val; } return setval; }(this), 330, 20, 10000, 0.01);
		ui_interface.addHorizontalSlider("kb2bend", function handler(obj) { function setval(val) { obj.fHslider8 = val; } return setval; }(this), 1, 0, 10, 0.01);
		ui_interface.addHorizontalSlider("kb2fingers", function handler(obj) { function setval(val) { obj.fHslider9 = val; } return setval; }(this), 0, 0, 10, 1);
		ui_interface.addHorizontalSlider("kb2freq", function handler(obj) { function setval(val) { obj.fHslider7 = val; } return setval; }(this), 440, 20, 10000, 0.01);
		ui_interface.addHorizontalSlider("kb3bend", function handler(obj) { function setval(val) { obj.fHslider11 = val; } return setval; }(this), 1, 0, 10, 0.01);
		ui_interface.addHorizontalSlider("kb3fingers", function handler(obj) { function setval(val) { obj.fHslider12 = val; } return setval; }(this), 0, 0, 10, 1);
		ui_interface.addHorizontalSlider("kb3freq", function handler(obj) { function setval(val) { obj.fHslider10 = val; } return setval; }(this), 550, 20, 10000, 0.01);
		ui_interface.addHorizontalSlider("y", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 0, 0, 1, 1);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = (0.34 / (this.fHslider0 * this.fHslider1));
		var iSlow1 = (this.fHslider2 > 0);
		var fSlow2 = (0.001 * this.fHslider3);
		var fSlow3 = (0.34 / (this.fHslider4 * this.fHslider5));
		var iSlow4 = (this.fHslider6 > 0);
		var fSlow5 = (0.34 / (this.fHslider7 * this.fHslider8));
		var iSlow6 = (this.fHslider9 > 0);
		var fSlow7 = (0.34 / (this.fHslider10 * this.fHslider11));
		var iSlow8 = (this.fHslider12 > 0);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iRec10[0] = 0;
			var iRec11 = this.iRec10[1];
			var fRec15 = (this.iRec6[1] - (0.989265 * ((0.6 * this.fRec16[2]) + (0.2 * (this.fRec16[1] + this.fRec16[3])))));
			this.fRec26[0] = (fSlow0 + (0.999 * this.fRec26[1]));
			var fTemp0 = (this.fRec26[0] + -0.08);
			var fTemp1 = (this.fConst5 * fTemp0);
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
			this.fRec28[0] = (fSlow2 + (0.999 * this.fRec28[1]));
			this.fRec27[0] = ((0.999 * this.fRec27[1]) + (0.001 * min_f(1, (3000 * Math.abs((this.fRec28[0] - this.fRec28[1]))))));
			this.fRec29[0] = this.fRec0[1];
			this.fRec30[(this.IOTA & 2047)] = (0 - (0.998801 * ((0.8 * this.fRec29[2]) + (0.1 * (this.fRec29[1] + this.fRec29[3])))));
			var iRec31 = 0;
			var fTemp27 = (this.fConst6 * fTemp0);
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
			var fTemp53 = ((iSlow1 * this.fRec27[0]) - (this.fRec22[1] + this.fVec0[1]));
			var fTemp54 = (fTemp53 * min_f(1, (1 / mydsp_faustpower4_f((Math.abs((3 * fTemp53)) + 0.75)))));
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
			this.fRec14[0] = (this.fRec16[1] - (this.fConst3 * ((this.fConst7 * this.fRec14[2]) + (this.fConst8 * this.fRec14[1]))));
			var fTemp56 = (this.fConst3 * ((this.fConst2 * this.fRec14[0]) + (this.fConst9 * this.fRec14[2])));
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
			this.iRec42[0] = 0;
			var iRec43 = this.iRec42[1];
			var fRec47 = (this.iRec38[1] - (0.989265 * ((0.6 * this.fRec48[2]) + (0.2 * (this.fRec48[1] + this.fRec48[3])))));
			this.fRec58[0] = (fSlow3 + (0.999 * this.fRec58[1]));
			var fTemp57 = (this.fRec58[0] + -0.08);
			var fTemp58 = (this.fConst5 * fTemp57);
			var fTemp59 = (fTemp58 + -1.49999);
			var iTemp60 = fTemp59;
			var iTemp61 = min_f(this.fConst4, max_i(0, iTemp60));
			var fTemp62 = Math.floor(fTemp59);
			var fTemp63 = (fTemp58 + (-1 - fTemp62));
			var fTemp64 = (0 - fTemp63);
			var fTemp65 = (fTemp58 + (-2 - fTemp62));
			var fTemp66 = (0 - (0.5 * fTemp65));
			var fTemp67 = (fTemp58 + (-3 - fTemp62));
			var fTemp68 = (0 - (0.333333 * fTemp67));
			var fTemp69 = (fTemp58 + (-4 - fTemp62));
			var fTemp70 = (0 - (0.25 * fTemp69));
			var fTemp71 = (fTemp58 - fTemp62);
			var iTemp72 = min_f(this.fConst4, max_i(0, (iTemp60 + 2)));
			var fTemp73 = (0 - fTemp67);
			var fTemp74 = (0 - (0.5 * fTemp69));
			var iTemp75 = min_f(this.fConst4, max_i(0, (iTemp60 + 1)));
			var fTemp76 = (0 - fTemp65);
			var fTemp77 = (0 - (0.5 * fTemp67));
			var fTemp78 = (0 - (0.333333 * fTemp69));
			var fTemp79 = (fTemp63 * fTemp65);
			var iTemp80 = min_f(this.fConst4, max_i(0, (iTemp60 + 3)));
			var fTemp81 = (0 - fTemp69);
			var fTemp82 = (fTemp79 * fTemp67);
			var iTemp83 = min_f(this.fConst4, max_i(0, (iTemp60 + 4)));
			this.fRec54[0] = (((((this.fRec34[((this.IOTA - (iTemp61 + 1)) & 2047)] * fTemp64) * fTemp66) * fTemp68) * fTemp70) + (fTemp71 * ((((0.5 * (((fTemp63 * this.fRec34[((this.IOTA - (iTemp72 + 1)) & 2047)]) * fTemp73) * fTemp74)) + (((this.fRec34[((this.IOTA - (iTemp75 + 1)) & 2047)] * fTemp76) * fTemp77) * fTemp78)) + (0.166667 * ((fTemp79 * this.fRec34[((this.IOTA - (iTemp80 + 1)) & 2047)]) * fTemp81))) + (0.0416667 * (fTemp82 * this.fRec34[((this.IOTA - (iTemp83 + 1)) & 2047)])))));
			this.fRec59[0] = this.fRec32[1];
			this.fRec60[(this.IOTA & 2047)] = (0 - (0.998801 * ((0.8 * this.fRec59[2]) + (0.1 * (this.fRec59[1] + this.fRec59[3])))));
			var iRec61 = 0;
			var fTemp84 = (this.fConst6 * fTemp57);
			var fTemp85 = (fTemp84 + -1.49999);
			var iTemp86 = fTemp85;
			var iTemp87 = min_f(this.fConst4, max_i(0, iTemp86));
			var fTemp88 = Math.floor(fTemp85);
			var fTemp89 = (fTemp84 + (-1 - fTemp88));
			var fTemp90 = (0 - fTemp89);
			var fTemp91 = (fTemp84 + (-2 - fTemp88));
			var fTemp92 = (0 - (0.5 * fTemp91));
			var fTemp93 = (fTemp84 + (-3 - fTemp88));
			var fTemp94 = (0 - (0.333333 * fTemp93));
			var fTemp95 = (fTemp84 + (-4 - fTemp88));
			var fTemp96 = (0 - (0.25 * fTemp95));
			var fTemp97 = (fTemp84 - fTemp88);
			var iTemp98 = min_f(this.fConst4, max_i(0, (iTemp86 + 2)));
			var fTemp99 = (0 - fTemp93);
			var fTemp100 = (0 - (0.5 * fTemp95));
			var iTemp101 = min_f(this.fConst4, max_i(0, (iTemp86 + 1)));
			var fTemp102 = (0 - fTemp91);
			var fTemp103 = (0 - (0.5 * fTemp93));
			var fTemp104 = (0 - (0.333333 * fTemp95));
			var fTemp105 = (fTemp89 * fTemp91);
			var iTemp106 = min_f(this.fConst4, max_i(0, (iTemp86 + 3)));
			var fTemp107 = (0 - fTemp95);
			var fTemp108 = (fTemp105 * fTemp93);
			var iTemp109 = min_f(this.fConst4, max_i(0, (iTemp86 + 4)));
			this.fVec2[0] = (((((this.fRec60[((this.IOTA - (iTemp87 + 2)) & 2047)] * fTemp90) * fTemp92) * fTemp94) * fTemp96) + (fTemp97 * ((((0.5 * (((fTemp89 * this.fRec60[((this.IOTA - (iTemp98 + 2)) & 2047)]) * fTemp99) * fTemp100)) + (((this.fRec60[((this.IOTA - (iTemp101 + 2)) & 2047)] * fTemp102) * fTemp103) * fTemp104)) + (0.166667 * ((fTemp105 * this.fRec60[((this.IOTA - (iTemp106 + 2)) & 2047)]) * fTemp107))) + (0.0416667 * (fTemp108 * this.fRec60[((this.IOTA - (iTemp109 + 2)) & 2047)])))));
			var fTemp110 = ((iSlow4 * this.fRec27[0]) - (this.fRec54[1] + this.fVec2[1]));
			var fTemp111 = (fTemp110 * min_f(1, (1 / mydsp_faustpower4_f((Math.abs((3 * fTemp110)) + 0.75)))));
			var fRec55 = (this.fRec54[1] + fTemp111);
			var fTemp112 = (this.fVec2[1] + fTemp111);
			this.fVec3[(this.IOTA & 2047)] = fTemp112;
			var fRec56 = (((((fTemp64 * fTemp66) * fTemp68) * fTemp70) * this.fVec3[((this.IOTA - iTemp61) & 2047)]) + (fTemp71 * ((0.0416667 * (fTemp82 * this.fVec3[((this.IOTA - iTemp83) & 2047)])) + (((((fTemp76 * fTemp77) * fTemp78) * this.fVec3[((this.IOTA - iTemp75) & 2047)]) + (0.5 * (((fTemp63 * fTemp73) * fTemp74) * this.fVec3[((this.IOTA - iTemp72) & 2047)]))) + (0.166667 * ((fTemp79 * fTemp81) * this.fVec3[((this.IOTA - iTemp80) & 2047)]))))));
			var iRec57 = iRec61;
			this.fRec50[(this.IOTA & 2047)] = fRec55;
			var fRec51 = (((((fTemp90 * fTemp92) * fTemp94) * fTemp96) * this.fRec50[((this.IOTA - (iTemp87 + 1)) & 2047)]) + (fTemp97 * (((0.166667 * ((fTemp105 * fTemp107) * this.fRec50[((this.IOTA - (iTemp106 + 1)) & 2047)])) + ((((fTemp102 * fTemp103) * fTemp104) * this.fRec50[((this.IOTA - (iTemp101 + 1)) & 2047)]) + (0.5 * (((fTemp89 * fTemp99) * fTemp100) * this.fRec50[((this.IOTA - (iTemp98 + 1)) & 2047)])))) + (0.0416667 * (fTemp108 * this.fRec50[((this.IOTA - (iTemp109 + 1)) & 2047)])))));
			this.fRec52[0] = fRec56;
			var iRec53 = iRec57;
			this.fRec48[0] = this.fRec52[1];
			var iRec49 = iRec53;
			this.fRec46[0] = (this.fRec48[1] - (this.fConst3 * ((this.fConst8 * this.fRec46[1]) + (this.fConst7 * this.fRec46[2]))));
			var fTemp113 = (this.fConst3 * ((this.fConst2 * this.fRec46[0]) + (this.fConst9 * this.fRec46[2])));
			var fRec44 = fTemp113;
			var fRec45 = (iRec49 + fTemp113);
			this.iRec38[0] = iRec43;
			var fRec39 = fRec47;
			var fRec40 = fRec44;
			var fRec41 = fRec45;
			this.fRec34[(this.IOTA & 2047)] = fRec39;
			var fRec35 = fRec51;
			var fRec36 = fRec40;
			var fRec37 = fRec41;
			this.fRec32[0] = fRec35;
			var fRec33 = fRec37;
			this.iRec72[0] = 0;
			var iRec73 = this.iRec72[1];
			var fRec77 = (this.iRec68[1] - (0.989265 * ((0.6 * this.fRec78[2]) + (0.2 * (this.fRec78[1] + this.fRec78[3])))));
			this.fRec88[0] = (fSlow5 + (0.999 * this.fRec88[1]));
			var fTemp114 = (this.fRec88[0] + -0.08);
			var fTemp115 = (this.fConst5 * fTemp114);
			var fTemp116 = (fTemp115 + -1.49999);
			var iTemp117 = fTemp116;
			var iTemp118 = min_f(this.fConst4, max_i(0, iTemp117));
			var fTemp119 = Math.floor(fTemp116);
			var fTemp120 = (fTemp115 + (-1 - fTemp119));
			var fTemp121 = (0 - fTemp120);
			var fTemp122 = (fTemp115 + (-2 - fTemp119));
			var fTemp123 = (0 - (0.5 * fTemp122));
			var fTemp124 = (fTemp115 + (-3 - fTemp119));
			var fTemp125 = (0 - (0.333333 * fTemp124));
			var fTemp126 = (fTemp115 + (-4 - fTemp119));
			var fTemp127 = (0 - (0.25 * fTemp126));
			var fTemp128 = (fTemp115 - fTemp119);
			var iTemp129 = min_f(this.fConst4, max_i(0, (iTemp117 + 2)));
			var fTemp130 = (0 - fTemp124);
			var fTemp131 = (0 - (0.5 * fTemp126));
			var iTemp132 = min_f(this.fConst4, max_i(0, (iTemp117 + 1)));
			var fTemp133 = (0 - fTemp122);
			var fTemp134 = (0 - (0.5 * fTemp124));
			var fTemp135 = (0 - (0.333333 * fTemp126));
			var fTemp136 = (fTemp120 * fTemp122);
			var iTemp137 = min_f(this.fConst4, max_i(0, (iTemp117 + 3)));
			var fTemp138 = (0 - fTemp126);
			var fTemp139 = (fTemp136 * fTemp124);
			var iTemp140 = min_f(this.fConst4, max_i(0, (iTemp117 + 4)));
			this.fRec84[0] = (((((this.fRec64[((this.IOTA - (iTemp118 + 1)) & 2047)] * fTemp121) * fTemp123) * fTemp125) * fTemp127) + (fTemp128 * ((((0.5 * (((fTemp120 * this.fRec64[((this.IOTA - (iTemp129 + 1)) & 2047)]) * fTemp130) * fTemp131)) + (((this.fRec64[((this.IOTA - (iTemp132 + 1)) & 2047)] * fTemp133) * fTemp134) * fTemp135)) + (0.166667 * ((fTemp136 * this.fRec64[((this.IOTA - (iTemp137 + 1)) & 2047)]) * fTemp138))) + (0.0416667 * (fTemp139 * this.fRec64[((this.IOTA - (iTemp140 + 1)) & 2047)])))));
			this.fRec89[0] = this.fRec62[1];
			this.fRec90[(this.IOTA & 2047)] = (0 - (0.998801 * ((0.8 * this.fRec89[2]) + (0.1 * (this.fRec89[1] + this.fRec89[3])))));
			var iRec91 = 0;
			var fTemp141 = (this.fConst6 * fTemp114);
			var fTemp142 = (fTemp141 + -1.49999);
			var iTemp143 = fTemp142;
			var iTemp144 = min_f(this.fConst4, max_i(0, iTemp143));
			var fTemp145 = Math.floor(fTemp142);
			var fTemp146 = (fTemp141 + (-1 - fTemp145));
			var fTemp147 = (0 - fTemp146);
			var fTemp148 = (fTemp141 + (-2 - fTemp145));
			var fTemp149 = (0 - (0.5 * fTemp148));
			var fTemp150 = (fTemp141 + (-3 - fTemp145));
			var fTemp151 = (0 - (0.333333 * fTemp150));
			var fTemp152 = (fTemp141 + (-4 - fTemp145));
			var fTemp153 = (0 - (0.25 * fTemp152));
			var fTemp154 = (fTemp141 - fTemp145);
			var iTemp155 = min_f(this.fConst4, max_i(0, (iTemp143 + 2)));
			var fTemp156 = (0 - fTemp150);
			var fTemp157 = (0 - (0.5 * fTemp152));
			var iTemp158 = min_f(this.fConst4, max_i(0, (iTemp143 + 1)));
			var fTemp159 = (0 - fTemp148);
			var fTemp160 = (0 - (0.5 * fTemp150));
			var fTemp161 = (0 - (0.333333 * fTemp152));
			var fTemp162 = (fTemp146 * fTemp148);
			var iTemp163 = min_f(this.fConst4, max_i(0, (iTemp143 + 3)));
			var fTemp164 = (0 - fTemp152);
			var fTemp165 = (fTemp162 * fTemp150);
			var iTemp166 = min_f(this.fConst4, max_i(0, (iTemp143 + 4)));
			this.fVec4[0] = (((((this.fRec90[((this.IOTA - (iTemp144 + 2)) & 2047)] * fTemp147) * fTemp149) * fTemp151) * fTemp153) + (fTemp154 * ((((0.5 * (((fTemp146 * this.fRec90[((this.IOTA - (iTemp155 + 2)) & 2047)]) * fTemp156) * fTemp157)) + (((this.fRec90[((this.IOTA - (iTemp158 + 2)) & 2047)] * fTemp159) * fTemp160) * fTemp161)) + (0.166667 * ((fTemp162 * this.fRec90[((this.IOTA - (iTemp163 + 2)) & 2047)]) * fTemp164))) + (0.0416667 * (fTemp165 * this.fRec90[((this.IOTA - (iTemp166 + 2)) & 2047)])))));
			var fTemp167 = ((iSlow6 * this.fRec27[0]) - (this.fRec84[1] + this.fVec4[1]));
			var fTemp168 = (fTemp167 * min_f(1, (1 / mydsp_faustpower4_f((Math.abs((3 * fTemp167)) + 0.75)))));
			var fRec85 = (this.fRec84[1] + fTemp168);
			var fTemp169 = (this.fVec4[1] + fTemp168);
			this.fVec5[(this.IOTA & 2047)] = fTemp169;
			var fRec86 = (((((fTemp121 * fTemp123) * fTemp125) * fTemp127) * this.fVec5[((this.IOTA - iTemp118) & 2047)]) + (fTemp128 * ((0.0416667 * (fTemp139 * this.fVec5[((this.IOTA - iTemp140) & 2047)])) + (((((fTemp133 * fTemp134) * fTemp135) * this.fVec5[((this.IOTA - iTemp132) & 2047)]) + (0.5 * (((fTemp120 * fTemp130) * fTemp131) * this.fVec5[((this.IOTA - iTemp129) & 2047)]))) + (0.166667 * ((fTemp136 * fTemp138) * this.fVec5[((this.IOTA - iTemp137) & 2047)]))))));
			var iRec87 = iRec91;
			this.fRec80[(this.IOTA & 2047)] = fRec85;
			var fRec81 = (((((fTemp147 * fTemp149) * fTemp151) * fTemp153) * this.fRec80[((this.IOTA - (iTemp144 + 1)) & 2047)]) + (fTemp154 * (((0.166667 * ((fTemp162 * fTemp164) * this.fRec80[((this.IOTA - (iTemp163 + 1)) & 2047)])) + ((((fTemp159 * fTemp160) * fTemp161) * this.fRec80[((this.IOTA - (iTemp158 + 1)) & 2047)]) + (0.5 * (((fTemp146 * fTemp156) * fTemp157) * this.fRec80[((this.IOTA - (iTemp155 + 1)) & 2047)])))) + (0.0416667 * (fTemp165 * this.fRec80[((this.IOTA - (iTemp166 + 1)) & 2047)])))));
			this.fRec82[0] = fRec86;
			var iRec83 = iRec87;
			this.fRec78[0] = this.fRec82[1];
			var iRec79 = iRec83;
			this.fRec76[0] = (this.fRec78[1] - (this.fConst3 * ((this.fConst8 * this.fRec76[1]) + (this.fConst7 * this.fRec76[2]))));
			var fTemp170 = (this.fConst3 * ((this.fConst2 * this.fRec76[0]) + (this.fConst9 * this.fRec76[2])));
			var fRec74 = fTemp170;
			var fRec75 = (iRec79 + fTemp170);
			this.iRec68[0] = iRec73;
			var fRec69 = fRec77;
			var fRec70 = fRec74;
			var fRec71 = fRec75;
			this.fRec64[(this.IOTA & 2047)] = fRec69;
			var fRec65 = fRec81;
			var fRec66 = fRec70;
			var fRec67 = fRec71;
			this.fRec62[0] = fRec65;
			var fRec63 = fRec67;
			this.iRec102[0] = 0;
			var iRec103 = this.iRec102[1];
			var fRec107 = (this.iRec98[1] - (0.989265 * ((0.6 * this.fRec108[2]) + (0.2 * (this.fRec108[1] + this.fRec108[3])))));
			this.fRec118[0] = (fSlow7 + (0.999 * this.fRec118[1]));
			var fTemp171 = (this.fRec118[0] + -0.08);
			var fTemp172 = (this.fConst5 * fTemp171);
			var fTemp173 = (fTemp172 + -1.49999);
			var iTemp174 = fTemp173;
			var iTemp175 = min_f(this.fConst4, max_i(0, iTemp174));
			var fTemp176 = Math.floor(fTemp173);
			var fTemp177 = (fTemp172 + (-1 - fTemp176));
			var fTemp178 = (0 - fTemp177);
			var fTemp179 = (fTemp172 + (-2 - fTemp176));
			var fTemp180 = (0 - (0.5 * fTemp179));
			var fTemp181 = (fTemp172 + (-3 - fTemp176));
			var fTemp182 = (0 - (0.333333 * fTemp181));
			var fTemp183 = (fTemp172 + (-4 - fTemp176));
			var fTemp184 = (0 - (0.25 * fTemp183));
			var fTemp185 = (fTemp172 - fTemp176);
			var iTemp186 = min_f(this.fConst4, max_i(0, (iTemp174 + 2)));
			var fTemp187 = (0 - fTemp181);
			var fTemp188 = (0 - (0.5 * fTemp183));
			var iTemp189 = min_f(this.fConst4, max_i(0, (iTemp174 + 1)));
			var fTemp190 = (0 - fTemp179);
			var fTemp191 = (0 - (0.5 * fTemp181));
			var fTemp192 = (0 - (0.333333 * fTemp183));
			var fTemp193 = (fTemp177 * fTemp179);
			var iTemp194 = min_f(this.fConst4, max_i(0, (iTemp174 + 3)));
			var fTemp195 = (0 - fTemp183);
			var fTemp196 = (fTemp193 * fTemp181);
			var iTemp197 = min_f(this.fConst4, max_i(0, (iTemp174 + 4)));
			this.fRec114[0] = (((((this.fRec94[((this.IOTA - (iTemp175 + 1)) & 2047)] * fTemp178) * fTemp180) * fTemp182) * fTemp184) + (fTemp185 * ((((0.5 * (((fTemp177 * this.fRec94[((this.IOTA - (iTemp186 + 1)) & 2047)]) * fTemp187) * fTemp188)) + (((this.fRec94[((this.IOTA - (iTemp189 + 1)) & 2047)] * fTemp190) * fTemp191) * fTemp192)) + (0.166667 * ((fTemp193 * this.fRec94[((this.IOTA - (iTemp194 + 1)) & 2047)]) * fTemp195))) + (0.0416667 * (fTemp196 * this.fRec94[((this.IOTA - (iTemp197 + 1)) & 2047)])))));
			this.fRec119[0] = this.fRec92[1];
			this.fRec120[(this.IOTA & 2047)] = (0 - (0.998801 * ((0.8 * this.fRec119[2]) + (0.1 * (this.fRec119[1] + this.fRec119[3])))));
			var iRec121 = 0;
			var fTemp198 = (this.fConst6 * fTemp171);
			var fTemp199 = (fTemp198 + -1.49999);
			var iTemp200 = fTemp199;
			var iTemp201 = min_f(this.fConst4, max_i(0, iTemp200));
			var fTemp202 = Math.floor(fTemp199);
			var fTemp203 = (fTemp198 + (-1 - fTemp202));
			var fTemp204 = (0 - fTemp203);
			var fTemp205 = (fTemp198 + (-2 - fTemp202));
			var fTemp206 = (0 - (0.5 * fTemp205));
			var fTemp207 = (fTemp198 + (-3 - fTemp202));
			var fTemp208 = (0 - (0.333333 * fTemp207));
			var fTemp209 = (fTemp198 + (-4 - fTemp202));
			var fTemp210 = (0 - (0.25 * fTemp209));
			var fTemp211 = (fTemp198 - fTemp202);
			var iTemp212 = min_f(this.fConst4, max_i(0, (iTemp200 + 2)));
			var fTemp213 = (0 - fTemp207);
			var fTemp214 = (0 - (0.5 * fTemp209));
			var iTemp215 = min_f(this.fConst4, max_i(0, (iTemp200 + 1)));
			var fTemp216 = (0 - fTemp205);
			var fTemp217 = (0 - (0.5 * fTemp207));
			var fTemp218 = (0 - (0.333333 * fTemp209));
			var fTemp219 = (fTemp203 * fTemp205);
			var iTemp220 = min_f(this.fConst4, max_i(0, (iTemp200 + 3)));
			var fTemp221 = (0 - fTemp209);
			var fTemp222 = (fTemp219 * fTemp207);
			var iTemp223 = min_f(this.fConst4, max_i(0, (iTemp200 + 4)));
			this.fVec6[0] = (((((this.fRec120[((this.IOTA - (iTemp201 + 2)) & 2047)] * fTemp204) * fTemp206) * fTemp208) * fTemp210) + (fTemp211 * ((((0.5 * (((fTemp203 * this.fRec120[((this.IOTA - (iTemp212 + 2)) & 2047)]) * fTemp213) * fTemp214)) + (((this.fRec120[((this.IOTA - (iTemp215 + 2)) & 2047)] * fTemp216) * fTemp217) * fTemp218)) + (0.166667 * ((fTemp219 * this.fRec120[((this.IOTA - (iTemp220 + 2)) & 2047)]) * fTemp221))) + (0.0416667 * (fTemp222 * this.fRec120[((this.IOTA - (iTemp223 + 2)) & 2047)])))));
			var fTemp224 = ((iSlow8 * this.fRec27[0]) - (this.fRec114[1] + this.fVec6[1]));
			var fTemp225 = (fTemp224 * min_f(1, (1 / mydsp_faustpower4_f((Math.abs((3 * fTemp224)) + 0.75)))));
			var fRec115 = (this.fRec114[1] + fTemp225);
			var fTemp226 = (this.fVec6[1] + fTemp225);
			this.fVec7[(this.IOTA & 2047)] = fTemp226;
			var fRec116 = (((((fTemp178 * fTemp180) * fTemp182) * fTemp184) * this.fVec7[((this.IOTA - iTemp175) & 2047)]) + (fTemp185 * ((0.0416667 * (fTemp196 * this.fVec7[((this.IOTA - iTemp197) & 2047)])) + (((((fTemp190 * fTemp191) * fTemp192) * this.fVec7[((this.IOTA - iTemp189) & 2047)]) + (0.5 * (((fTemp177 * fTemp187) * fTemp188) * this.fVec7[((this.IOTA - iTemp186) & 2047)]))) + (0.166667 * ((fTemp193 * fTemp195) * this.fVec7[((this.IOTA - iTemp194) & 2047)]))))));
			var iRec117 = iRec121;
			this.fRec110[(this.IOTA & 2047)] = fRec115;
			var fRec111 = (((((fTemp204 * fTemp206) * fTemp208) * fTemp210) * this.fRec110[((this.IOTA - (iTemp201 + 1)) & 2047)]) + (fTemp211 * (((0.166667 * ((fTemp219 * fTemp221) * this.fRec110[((this.IOTA - (iTemp220 + 1)) & 2047)])) + ((((fTemp216 * fTemp217) * fTemp218) * this.fRec110[((this.IOTA - (iTemp215 + 1)) & 2047)]) + (0.5 * (((fTemp203 * fTemp213) * fTemp214) * this.fRec110[((this.IOTA - (iTemp212 + 1)) & 2047)])))) + (0.0416667 * (fTemp222 * this.fRec110[((this.IOTA - (iTemp223 + 1)) & 2047)])))));
			this.fRec112[0] = fRec116;
			var iRec113 = iRec117;
			this.fRec108[0] = this.fRec112[1];
			var iRec109 = iRec113;
			this.fRec106[0] = (this.fRec108[1] - (this.fConst3 * ((this.fConst8 * this.fRec106[1]) + (this.fConst7 * this.fRec106[2]))));
			var fTemp227 = (this.fConst3 * ((this.fConst2 * this.fRec106[0]) + (this.fConst9 * this.fRec106[2])));
			var fRec104 = fTemp227;
			var fRec105 = (iRec109 + fTemp227);
			this.iRec98[0] = iRec103;
			var fRec99 = fRec107;
			var fRec100 = fRec104;
			var fRec101 = fRec105;
			this.fRec94[(this.IOTA & 2047)] = fRec99;
			var fRec95 = fRec111;
			var fRec96 = fRec100;
			var fRec97 = fRec101;
			this.fRec92[0] = fRec95;
			var fRec93 = fRec97;
			var fTemp228 = (((fRec1 + fRec33) + fRec63) + fRec93);
			output0[i] = fTemp228;
			output1[i] = fTemp228;
			this.iRec10[1] = this.iRec10[0];
			this.fRec26[1] = this.fRec26[0];
			this.fRec22[1] = this.fRec22[0];
			this.fRec28[1] = this.fRec28[0];
			this.fRec27[1] = this.fRec27[0];
			for (var j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				this.fRec29[j0] = this.fRec29[(j0 - 1)];
				
			}
			this.IOTA = (this.IOTA + 1);
			this.fVec0[1] = this.fVec0[0];
			this.fRec20[1] = this.fRec20[0];
			for (var j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				this.fRec16[j1] = this.fRec16[(j1 - 1)];
				
			}
			this.fRec14[2] = this.fRec14[1];
			this.fRec14[1] = this.fRec14[0];
			this.iRec6[1] = this.iRec6[0];
			this.fRec0[1] = this.fRec0[0];
			this.iRec42[1] = this.iRec42[0];
			this.fRec58[1] = this.fRec58[0];
			this.fRec54[1] = this.fRec54[0];
			for (var j2 = 3; (j2 > 0); j2 = (j2 - 1)) {
				this.fRec59[j2] = this.fRec59[(j2 - 1)];
				
			}
			this.fVec2[1] = this.fVec2[0];
			this.fRec52[1] = this.fRec52[0];
			for (var j3 = 3; (j3 > 0); j3 = (j3 - 1)) {
				this.fRec48[j3] = this.fRec48[(j3 - 1)];
				
			}
			this.fRec46[2] = this.fRec46[1];
			this.fRec46[1] = this.fRec46[0];
			this.iRec38[1] = this.iRec38[0];
			this.fRec32[1] = this.fRec32[0];
			this.iRec72[1] = this.iRec72[0];
			this.fRec88[1] = this.fRec88[0];
			this.fRec84[1] = this.fRec84[0];
			for (var j4 = 3; (j4 > 0); j4 = (j4 - 1)) {
				this.fRec89[j4] = this.fRec89[(j4 - 1)];
				
			}
			this.fVec4[1] = this.fVec4[0];
			this.fRec82[1] = this.fRec82[0];
			for (var j5 = 3; (j5 > 0); j5 = (j5 - 1)) {
				this.fRec78[j5] = this.fRec78[(j5 - 1)];
				
			}
			this.fRec76[2] = this.fRec76[1];
			this.fRec76[1] = this.fRec76[0];
			this.iRec68[1] = this.iRec68[0];
			this.fRec62[1] = this.fRec62[0];
			this.iRec102[1] = this.iRec102[0];
			this.fRec118[1] = this.fRec118[0];
			this.fRec114[1] = this.fRec114[0];
			for (var j6 = 3; (j6 > 0); j6 = (j6 - 1)) {
				this.fRec119[j6] = this.fRec119[(j6 - 1)];
				
			}
			this.fVec6[1] = this.fVec6[0];
			this.fRec112[1] = this.fRec112[0];
			for (var j7 = 3; (j7 > 0); j7 = (j7 - 1)) {
				this.fRec108[j7] = this.fRec108[(j7 - 1)];
				
			}
			this.fRec106[2] = this.fRec106[1];
			this.fRec106[1] = this.fRec106[0];
			this.iRec98[1] = this.iRec98[0];
			this.fRec92[1] = this.fRec92[0];
			
		}
		
	}
	
}

