
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
	this.fHslider4;
	this.fRec32 = new Float32Array(2);
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
	this.iRec43 = new Int32Array(2);
	this.fHslider5;
	this.fHslider6;
	this.fRec59 = new Float32Array(2);
	this.fRec55 = new Float32Array(2);
	this.fHslider7;
	this.fRec60 = new Float32Array(4);
	this.fRec61 = new Float32Array(2048);
	this.fVec2 = new Float32Array(2);
	this.fVec3 = new Float32Array(2048);
	this.fRec51 = new Float32Array(2048);
	this.fRec53 = new Float32Array(2);
	this.fRec49 = new Float32Array(4);
	this.fRec47 = new Float32Array(3);
	this.iRec39 = new Int32Array(2);
	this.fRec35 = new Float32Array(2048);
	this.fRec33 = new Float32Array(2);
	this.iRec73 = new Int32Array(2);
	this.fHslider8;
	this.fHslider9;
	this.fRec89 = new Float32Array(2);
	this.fRec85 = new Float32Array(2);
	this.fHslider10;
	this.fRec90 = new Float32Array(4);
	this.fRec91 = new Float32Array(2048);
	this.fVec4 = new Float32Array(2);
	this.fVec5 = new Float32Array(2048);
	this.fRec81 = new Float32Array(2048);
	this.fRec83 = new Float32Array(2);
	this.fRec79 = new Float32Array(4);
	this.fRec77 = new Float32Array(3);
	this.iRec69 = new Int32Array(2);
	this.fRec65 = new Float32Array(2048);
	this.fRec63 = new Float32Array(2);
	this.iRec103 = new Int32Array(2);
	this.fHslider11;
	this.fHslider12;
	this.fRec119 = new Float32Array(2);
	this.fRec115 = new Float32Array(2);
	this.fHslider13;
	this.fRec120 = new Float32Array(4);
	this.fRec121 = new Float32Array(2048);
	this.fVec6 = new Float32Array(2);
	this.fVec7 = new Float32Array(2048);
	this.fRec111 = new Float32Array(2048);
	this.fRec113 = new Float32Array(2);
	this.fRec109 = new Float32Array(4);
	this.fRec107 = new Float32Array(3);
	this.iRec99 = new Int32Array(2);
	this.fRec95 = new Float32Array(2048);
	this.fRec93 = new Float32Array(2);
	
	this.metadata = function(m) { 
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("interface", "SmartKeyboard{  'Number of Keyboards':'5',  'Max Keyboard Polyphony':'0',  'Rounding Mode':'2',  'Send Fingers Count':'1',  'Keyboard 0 - Number of Keys':'19',  'Keyboard 1 - Number of Keys':'19',  'Keyboard 2 - Number of Keys':'19',  'Keyboard 3 - Number of Keys':'19',  'Keyboard 4 - Number of Keys':'1',  'Keyboard 0 - Lowest Key':'55',  'Keyboard 1 - Lowest Key':'62',  'Keyboard 2 - Lowest Key':'69',  'Keyboard 3 - Lowest Key':'76',  'Keyboard 0 - Send Keyboard Freq':'1',  'Keyboard 1 - Send Keyboard Freq':'1',  'Keyboard 2 - Send Keyboard Freq':'1',  'Keyboard 3 - Send Keyboard Freq':'1',  'Keyboard 4 - Send Freq':'0',  'Keyboard 4 - Send Key X':'1',  'Keyboard 4 - Send Key Y':'1',  'Keyboard 4 - Key 0 - Label':'Bow',  'Keyboard 4 - Static Mode':'1' }");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "violin");
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
		this.fHslider4 = 0;
		this.fHslider5 = 330;
		this.fHslider6 = 1;
		this.fHslider7 = 0;
		this.fHslider8 = 440;
		this.fHslider9 = 1;
		this.fHslider10 = 0;
		this.fHslider11 = 550;
		this.fHslider12 = 1;
		this.fHslider13 = 0;
		
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
		for (var l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			this.iRec43[l17] = 0;
			
		}
		for (var l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			this.fRec59[l18] = 0;
			
		}
		for (var l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			this.fRec55[l19] = 0;
			
		}
		for (var l20 = 0; (l20 < 4); l20 = (l20 + 1)) {
			this.fRec60[l20] = 0;
			
		}
		for (var l21 = 0; (l21 < 2048); l21 = (l21 + 1)) {
			this.fRec61[l21] = 0;
			
		}
		for (var l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			this.fVec2[l22] = 0;
			
		}
		for (var l23 = 0; (l23 < 2048); l23 = (l23 + 1)) {
			this.fVec3[l23] = 0;
			
		}
		for (var l24 = 0; (l24 < 2048); l24 = (l24 + 1)) {
			this.fRec51[l24] = 0;
			
		}
		for (var l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			this.fRec53[l25] = 0;
			
		}
		for (var l26 = 0; (l26 < 4); l26 = (l26 + 1)) {
			this.fRec49[l26] = 0;
			
		}
		for (var l27 = 0; (l27 < 3); l27 = (l27 + 1)) {
			this.fRec47[l27] = 0;
			
		}
		for (var l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			this.iRec39[l28] = 0;
			
		}
		for (var l29 = 0; (l29 < 2048); l29 = (l29 + 1)) {
			this.fRec35[l29] = 0;
			
		}
		for (var l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			this.fRec33[l30] = 0;
			
		}
		for (var l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			this.iRec73[l31] = 0;
			
		}
		for (var l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			this.fRec89[l32] = 0;
			
		}
		for (var l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			this.fRec85[l33] = 0;
			
		}
		for (var l34 = 0; (l34 < 4); l34 = (l34 + 1)) {
			this.fRec90[l34] = 0;
			
		}
		for (var l35 = 0; (l35 < 2048); l35 = (l35 + 1)) {
			this.fRec91[l35] = 0;
			
		}
		for (var l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			this.fVec4[l36] = 0;
			
		}
		for (var l37 = 0; (l37 < 2048); l37 = (l37 + 1)) {
			this.fVec5[l37] = 0;
			
		}
		for (var l38 = 0; (l38 < 2048); l38 = (l38 + 1)) {
			this.fRec81[l38] = 0;
			
		}
		for (var l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			this.fRec83[l39] = 0;
			
		}
		for (var l40 = 0; (l40 < 4); l40 = (l40 + 1)) {
			this.fRec79[l40] = 0;
			
		}
		for (var l41 = 0; (l41 < 3); l41 = (l41 + 1)) {
			this.fRec77[l41] = 0;
			
		}
		for (var l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			this.iRec69[l42] = 0;
			
		}
		for (var l43 = 0; (l43 < 2048); l43 = (l43 + 1)) {
			this.fRec65[l43] = 0;
			
		}
		for (var l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			this.fRec63[l44] = 0;
			
		}
		for (var l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			this.iRec103[l45] = 0;
			
		}
		for (var l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			this.fRec119[l46] = 0;
			
		}
		for (var l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			this.fRec115[l47] = 0;
			
		}
		for (var l48 = 0; (l48 < 4); l48 = (l48 + 1)) {
			this.fRec120[l48] = 0;
			
		}
		for (var l49 = 0; (l49 < 2048); l49 = (l49 + 1)) {
			this.fRec121[l49] = 0;
			
		}
		for (var l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			this.fVec6[l50] = 0;
			
		}
		for (var l51 = 0; (l51 < 2048); l51 = (l51 + 1)) {
			this.fVec7[l51] = 0;
			
		}
		for (var l52 = 0; (l52 < 2048); l52 = (l52 + 1)) {
			this.fRec111[l52] = 0;
			
		}
		for (var l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			this.fRec113[l53] = 0;
			
		}
		for (var l54 = 0; (l54 < 4); l54 = (l54 + 1)) {
			this.fRec109[l54] = 0;
			
		}
		for (var l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			this.fRec107[l55] = 0;
			
		}
		for (var l56 = 0; (l56 < 2); l56 = (l56 + 1)) {
			this.iRec99[l56] = 0;
			
		}
		for (var l57 = 0; (l57 < 2048); l57 = (l57 + 1)) {
			this.fRec95[l57] = 0;
			
		}
		for (var l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			this.fRec93[l58] = 0;
			
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
		ui_interface.addHorizontalSlider("kb0bend", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 1, 0, 10, 0.01);
		ui_interface.addHorizontalSlider("kb0fingers", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 0, 0, 10, 1);
		ui_interface.addHorizontalSlider("kb0freq", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 220, 20, 10000, 0.01);
		ui_interface.addHorizontalSlider("kb1bend", function handler(obj) { function setval(val) { obj.fHslider6 = val; } return setval; }(this), 1, 0, 10, 0.01);
		ui_interface.addHorizontalSlider("kb1fingers", function handler(obj) { function setval(val) { obj.fHslider7 = val; } return setval; }(this), 0, 0, 10, 1);
		ui_interface.addHorizontalSlider("kb1freq", function handler(obj) { function setval(val) { obj.fHslider5 = val; } return setval; }(this), 330, 20, 10000, 0.01);
		ui_interface.addHorizontalSlider("kb2bend", function handler(obj) { function setval(val) { obj.fHslider9 = val; } return setval; }(this), 1, 0, 10, 0.01);
		ui_interface.addHorizontalSlider("kb2fingers", function handler(obj) { function setval(val) { obj.fHslider10 = val; } return setval; }(this), 0, 0, 10, 1);
		ui_interface.addHorizontalSlider("kb2freq", function handler(obj) { function setval(val) { obj.fHslider8 = val; } return setval; }(this), 440, 20, 10000, 0.01);
		ui_interface.addHorizontalSlider("kb3bend", function handler(obj) { function setval(val) { obj.fHslider12 = val; } return setval; }(this), 1, 0, 10, 0.01);
		ui_interface.addHorizontalSlider("kb3fingers", function handler(obj) { function setval(val) { obj.fHslider13 = val; } return setval; }(this), 0, 0, 10, 1);
		ui_interface.addHorizontalSlider("kb3freq", function handler(obj) { function setval(val) { obj.fHslider11 = val; } return setval; }(this), 550, 20, 10000, 0.01);
		ui_interface.addHorizontalSlider("kb4k0x", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 0, 0, 1, 1);
		ui_interface.addHorizontalSlider("kb4k0y", function handler(obj) { function setval(val) { obj.fHslider4 = val; } return setval; }(this), 0, 0, 1, 1);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = (0.34 / (this.fHslider0 * this.fHslider1));
		var iSlow1 = (this.fHslider2 > 0);
		var fSlow2 = (0.001 * this.fHslider3);
		var fSlow3 = (0.001 * this.fHslider4);
		var fSlow4 = (0.34 / (this.fHslider5 * this.fHslider6));
		var iSlow5 = (this.fHslider7 > 0);
		var fSlow6 = (0.34 / (this.fHslider8 * this.fHslider9));
		var iSlow7 = (this.fHslider10 > 0);
		var fSlow8 = (0.34 / (this.fHslider11 * this.fHslider12));
		var iSlow9 = (this.fHslider13 > 0);
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
			this.fRec27[0] = ((0.999 * this.fRec27[1]) + (0.001 * min_f(1, (8000 * Math.abs((this.fRec28[0] - this.fRec28[1]))))));
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
			this.fRec32[0] = (fSlow3 + (0.999 * this.fRec32[1]));
			var fTemp54 = (5 - (4 * this.fRec32[0]));
			var fTemp55 = (fTemp53 * min_f(1, (1 / mydsp_faustpower4_f((Math.abs((fTemp54 * fTemp53)) + 0.75)))));
			var fRec23 = (this.fRec22[1] + fTemp55);
			var fTemp56 = (this.fVec0[1] + fTemp55);
			this.fVec1[(this.IOTA & 2047)] = fTemp56;
			var fRec24 = (((((fTemp7 * fTemp9) * fTemp11) * fTemp13) * this.fVec1[((this.IOTA - iTemp4) & 2047)]) + (fTemp14 * ((0.0416667 * (fTemp25 * this.fVec1[((this.IOTA - iTemp26) & 2047)])) + (((((fTemp19 * fTemp20) * fTemp21) * this.fVec1[((this.IOTA - iTemp18) & 2047)]) + (0.5 * (((fTemp6 * fTemp16) * fTemp17) * this.fVec1[((this.IOTA - iTemp15) & 2047)]))) + (0.166667 * ((fTemp22 * fTemp24) * this.fVec1[((this.IOTA - iTemp23) & 2047)]))))));
			var iRec25 = iRec31;
			this.fRec18[(this.IOTA & 2047)] = fRec23;
			var fRec19 = (((((fTemp33 * fTemp35) * fTemp37) * fTemp39) * this.fRec18[((this.IOTA - (iTemp30 + 1)) & 2047)]) + (fTemp40 * (((0.166667 * ((fTemp48 * fTemp50) * this.fRec18[((this.IOTA - (iTemp49 + 1)) & 2047)])) + ((((fTemp45 * fTemp46) * fTemp47) * this.fRec18[((this.IOTA - (iTemp44 + 1)) & 2047)]) + (0.5 * (((fTemp32 * fTemp42) * fTemp43) * this.fRec18[((this.IOTA - (iTemp41 + 1)) & 2047)])))) + (0.0416667 * (fTemp51 * this.fRec18[((this.IOTA - (iTemp52 + 1)) & 2047)])))));
			this.fRec20[0] = fRec24;
			var iRec21 = iRec25;
			this.fRec16[0] = this.fRec20[1];
			var iRec17 = iRec21;
			this.fRec14[0] = (this.fRec16[1] - (this.fConst3 * ((this.fConst7 * this.fRec14[2]) + (this.fConst8 * this.fRec14[1]))));
			var fTemp57 = (this.fConst3 * ((this.fConst2 * this.fRec14[0]) + (this.fConst9 * this.fRec14[2])));
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
			this.iRec43[0] = 0;
			var iRec44 = this.iRec43[1];
			var fRec48 = (this.iRec39[1] - (0.989265 * ((0.6 * this.fRec49[2]) + (0.2 * (this.fRec49[1] + this.fRec49[3])))));
			this.fRec59[0] = (fSlow4 + (0.999 * this.fRec59[1]));
			var fTemp58 = (this.fRec59[0] + -0.08);
			var fTemp59 = (this.fConst5 * fTemp58);
			var fTemp60 = (fTemp59 + -1.49999);
			var iTemp61 = fTemp60;
			var iTemp62 = min_f(this.fConst4, max_i(0, iTemp61));
			var fTemp63 = Math.floor(fTemp60);
			var fTemp64 = (fTemp59 + (-1 - fTemp63));
			var fTemp65 = (0 - fTemp64);
			var fTemp66 = (fTemp59 + (-2 - fTemp63));
			var fTemp67 = (0 - (0.5 * fTemp66));
			var fTemp68 = (fTemp59 + (-3 - fTemp63));
			var fTemp69 = (0 - (0.333333 * fTemp68));
			var fTemp70 = (fTemp59 + (-4 - fTemp63));
			var fTemp71 = (0 - (0.25 * fTemp70));
			var fTemp72 = (fTemp59 - fTemp63);
			var iTemp73 = min_f(this.fConst4, max_i(0, (iTemp61 + 2)));
			var fTemp74 = (0 - fTemp68);
			var fTemp75 = (0 - (0.5 * fTemp70));
			var iTemp76 = min_f(this.fConst4, max_i(0, (iTemp61 + 1)));
			var fTemp77 = (0 - fTemp66);
			var fTemp78 = (0 - (0.5 * fTemp68));
			var fTemp79 = (0 - (0.333333 * fTemp70));
			var fTemp80 = (fTemp64 * fTemp66);
			var iTemp81 = min_f(this.fConst4, max_i(0, (iTemp61 + 3)));
			var fTemp82 = (0 - fTemp70);
			var fTemp83 = (fTemp80 * fTemp68);
			var iTemp84 = min_f(this.fConst4, max_i(0, (iTemp61 + 4)));
			this.fRec55[0] = (((((this.fRec35[((this.IOTA - (iTemp62 + 1)) & 2047)] * fTemp65) * fTemp67) * fTemp69) * fTemp71) + (fTemp72 * ((((0.5 * (((fTemp64 * this.fRec35[((this.IOTA - (iTemp73 + 1)) & 2047)]) * fTemp74) * fTemp75)) + (((this.fRec35[((this.IOTA - (iTemp76 + 1)) & 2047)] * fTemp77) * fTemp78) * fTemp79)) + (0.166667 * ((fTemp80 * this.fRec35[((this.IOTA - (iTemp81 + 1)) & 2047)]) * fTemp82))) + (0.0416667 * (fTemp83 * this.fRec35[((this.IOTA - (iTemp84 + 1)) & 2047)])))));
			this.fRec60[0] = this.fRec33[1];
			this.fRec61[(this.IOTA & 2047)] = (0 - (0.998801 * ((0.8 * this.fRec60[2]) + (0.1 * (this.fRec60[1] + this.fRec60[3])))));
			var iRec62 = 0;
			var fTemp85 = (this.fConst6 * fTemp58);
			var fTemp86 = (fTemp85 + -1.49999);
			var iTemp87 = fTemp86;
			var iTemp88 = min_f(this.fConst4, max_i(0, iTemp87));
			var fTemp89 = Math.floor(fTemp86);
			var fTemp90 = (fTemp85 + (-1 - fTemp89));
			var fTemp91 = (0 - fTemp90);
			var fTemp92 = (fTemp85 + (-2 - fTemp89));
			var fTemp93 = (0 - (0.5 * fTemp92));
			var fTemp94 = (fTemp85 + (-3 - fTemp89));
			var fTemp95 = (0 - (0.333333 * fTemp94));
			var fTemp96 = (fTemp85 + (-4 - fTemp89));
			var fTemp97 = (0 - (0.25 * fTemp96));
			var fTemp98 = (fTemp85 - fTemp89);
			var iTemp99 = min_f(this.fConst4, max_i(0, (iTemp87 + 2)));
			var fTemp100 = (0 - fTemp94);
			var fTemp101 = (0 - (0.5 * fTemp96));
			var iTemp102 = min_f(this.fConst4, max_i(0, (iTemp87 + 1)));
			var fTemp103 = (0 - fTemp92);
			var fTemp104 = (0 - (0.5 * fTemp94));
			var fTemp105 = (0 - (0.333333 * fTemp96));
			var fTemp106 = (fTemp90 * fTemp92);
			var iTemp107 = min_f(this.fConst4, max_i(0, (iTemp87 + 3)));
			var fTemp108 = (0 - fTemp96);
			var fTemp109 = (fTemp106 * fTemp94);
			var iTemp110 = min_f(this.fConst4, max_i(0, (iTemp87 + 4)));
			this.fVec2[0] = (((((this.fRec61[((this.IOTA - (iTemp88 + 2)) & 2047)] * fTemp91) * fTemp93) * fTemp95) * fTemp97) + (fTemp98 * ((((0.5 * (((fTemp90 * this.fRec61[((this.IOTA - (iTemp99 + 2)) & 2047)]) * fTemp100) * fTemp101)) + (((this.fRec61[((this.IOTA - (iTemp102 + 2)) & 2047)] * fTemp103) * fTemp104) * fTemp105)) + (0.166667 * ((fTemp106 * this.fRec61[((this.IOTA - (iTemp107 + 2)) & 2047)]) * fTemp108))) + (0.0416667 * (fTemp109 * this.fRec61[((this.IOTA - (iTemp110 + 2)) & 2047)])))));
			var fTemp111 = ((iSlow5 * this.fRec27[0]) - (this.fRec55[1] + this.fVec2[1]));
			var fTemp112 = (fTemp111 * min_f(1, (1 / mydsp_faustpower4_f((Math.abs((fTemp54 * fTemp111)) + 0.75)))));
			var fRec56 = (this.fRec55[1] + fTemp112);
			var fTemp113 = (this.fVec2[1] + fTemp112);
			this.fVec3[(this.IOTA & 2047)] = fTemp113;
			var fRec57 = (((((fTemp65 * fTemp67) * fTemp69) * fTemp71) * this.fVec3[((this.IOTA - iTemp62) & 2047)]) + (fTemp72 * ((0.0416667 * (fTemp83 * this.fVec3[((this.IOTA - iTemp84) & 2047)])) + (((((fTemp77 * fTemp78) * fTemp79) * this.fVec3[((this.IOTA - iTemp76) & 2047)]) + (0.5 * (((fTemp64 * fTemp74) * fTemp75) * this.fVec3[((this.IOTA - iTemp73) & 2047)]))) + (0.166667 * ((fTemp80 * fTemp82) * this.fVec3[((this.IOTA - iTemp81) & 2047)]))))));
			var iRec58 = iRec62;
			this.fRec51[(this.IOTA & 2047)] = fRec56;
			var fRec52 = (((((fTemp91 * fTemp93) * fTemp95) * fTemp97) * this.fRec51[((this.IOTA - (iTemp88 + 1)) & 2047)]) + (fTemp98 * (((0.166667 * ((fTemp106 * fTemp108) * this.fRec51[((this.IOTA - (iTemp107 + 1)) & 2047)])) + ((((fTemp103 * fTemp104) * fTemp105) * this.fRec51[((this.IOTA - (iTemp102 + 1)) & 2047)]) + (0.5 * (((fTemp90 * fTemp100) * fTemp101) * this.fRec51[((this.IOTA - (iTemp99 + 1)) & 2047)])))) + (0.0416667 * (fTemp109 * this.fRec51[((this.IOTA - (iTemp110 + 1)) & 2047)])))));
			this.fRec53[0] = fRec57;
			var iRec54 = iRec58;
			this.fRec49[0] = this.fRec53[1];
			var iRec50 = iRec54;
			this.fRec47[0] = (this.fRec49[1] - (this.fConst3 * ((this.fConst8 * this.fRec47[1]) + (this.fConst7 * this.fRec47[2]))));
			var fTemp114 = (this.fConst3 * ((this.fConst2 * this.fRec47[0]) + (this.fConst9 * this.fRec47[2])));
			var fRec45 = fTemp114;
			var fRec46 = (iRec50 + fTemp114);
			this.iRec39[0] = iRec44;
			var fRec40 = fRec48;
			var fRec41 = fRec45;
			var fRec42 = fRec46;
			this.fRec35[(this.IOTA & 2047)] = fRec40;
			var fRec36 = fRec52;
			var fRec37 = fRec41;
			var fRec38 = fRec42;
			this.fRec33[0] = fRec36;
			var fRec34 = fRec38;
			this.iRec73[0] = 0;
			var iRec74 = this.iRec73[1];
			var fRec78 = (this.iRec69[1] - (0.989265 * ((0.6 * this.fRec79[2]) + (0.2 * (this.fRec79[1] + this.fRec79[3])))));
			this.fRec89[0] = (fSlow6 + (0.999 * this.fRec89[1]));
			var fTemp115 = (this.fRec89[0] + -0.08);
			var fTemp116 = (this.fConst5 * fTemp115);
			var fTemp117 = (fTemp116 + -1.49999);
			var iTemp118 = fTemp117;
			var iTemp119 = min_f(this.fConst4, max_i(0, iTemp118));
			var fTemp120 = Math.floor(fTemp117);
			var fTemp121 = (fTemp116 + (-1 - fTemp120));
			var fTemp122 = (0 - fTemp121);
			var fTemp123 = (fTemp116 + (-2 - fTemp120));
			var fTemp124 = (0 - (0.5 * fTemp123));
			var fTemp125 = (fTemp116 + (-3 - fTemp120));
			var fTemp126 = (0 - (0.333333 * fTemp125));
			var fTemp127 = (fTemp116 + (-4 - fTemp120));
			var fTemp128 = (0 - (0.25 * fTemp127));
			var fTemp129 = (fTemp116 - fTemp120);
			var iTemp130 = min_f(this.fConst4, max_i(0, (iTemp118 + 2)));
			var fTemp131 = (0 - fTemp125);
			var fTemp132 = (0 - (0.5 * fTemp127));
			var iTemp133 = min_f(this.fConst4, max_i(0, (iTemp118 + 1)));
			var fTemp134 = (0 - fTemp123);
			var fTemp135 = (0 - (0.5 * fTemp125));
			var fTemp136 = (0 - (0.333333 * fTemp127));
			var fTemp137 = (fTemp121 * fTemp123);
			var iTemp138 = min_f(this.fConst4, max_i(0, (iTemp118 + 3)));
			var fTemp139 = (0 - fTemp127);
			var fTemp140 = (fTemp137 * fTemp125);
			var iTemp141 = min_f(this.fConst4, max_i(0, (iTemp118 + 4)));
			this.fRec85[0] = (((((this.fRec65[((this.IOTA - (iTemp119 + 1)) & 2047)] * fTemp122) * fTemp124) * fTemp126) * fTemp128) + (fTemp129 * ((((0.5 * (((fTemp121 * this.fRec65[((this.IOTA - (iTemp130 + 1)) & 2047)]) * fTemp131) * fTemp132)) + (((this.fRec65[((this.IOTA - (iTemp133 + 1)) & 2047)] * fTemp134) * fTemp135) * fTemp136)) + (0.166667 * ((fTemp137 * this.fRec65[((this.IOTA - (iTemp138 + 1)) & 2047)]) * fTemp139))) + (0.0416667 * (fTemp140 * this.fRec65[((this.IOTA - (iTemp141 + 1)) & 2047)])))));
			this.fRec90[0] = this.fRec63[1];
			this.fRec91[(this.IOTA & 2047)] = (0 - (0.998801 * ((0.8 * this.fRec90[2]) + (0.1 * (this.fRec90[1] + this.fRec90[3])))));
			var iRec92 = 0;
			var fTemp142 = (this.fConst6 * fTemp115);
			var fTemp143 = (fTemp142 + -1.49999);
			var iTemp144 = fTemp143;
			var iTemp145 = min_f(this.fConst4, max_i(0, iTemp144));
			var fTemp146 = Math.floor(fTemp143);
			var fTemp147 = (fTemp142 + (-1 - fTemp146));
			var fTemp148 = (0 - fTemp147);
			var fTemp149 = (fTemp142 + (-2 - fTemp146));
			var fTemp150 = (0 - (0.5 * fTemp149));
			var fTemp151 = (fTemp142 + (-3 - fTemp146));
			var fTemp152 = (0 - (0.333333 * fTemp151));
			var fTemp153 = (fTemp142 + (-4 - fTemp146));
			var fTemp154 = (0 - (0.25 * fTemp153));
			var fTemp155 = (fTemp142 - fTemp146);
			var iTemp156 = min_f(this.fConst4, max_i(0, (iTemp144 + 2)));
			var fTemp157 = (0 - fTemp151);
			var fTemp158 = (0 - (0.5 * fTemp153));
			var iTemp159 = min_f(this.fConst4, max_i(0, (iTemp144 + 1)));
			var fTemp160 = (0 - fTemp149);
			var fTemp161 = (0 - (0.5 * fTemp151));
			var fTemp162 = (0 - (0.333333 * fTemp153));
			var fTemp163 = (fTemp147 * fTemp149);
			var iTemp164 = min_f(this.fConst4, max_i(0, (iTemp144 + 3)));
			var fTemp165 = (0 - fTemp153);
			var fTemp166 = (fTemp163 * fTemp151);
			var iTemp167 = min_f(this.fConst4, max_i(0, (iTemp144 + 4)));
			this.fVec4[0] = (((((this.fRec91[((this.IOTA - (iTemp145 + 2)) & 2047)] * fTemp148) * fTemp150) * fTemp152) * fTemp154) + (fTemp155 * ((((0.5 * (((fTemp147 * this.fRec91[((this.IOTA - (iTemp156 + 2)) & 2047)]) * fTemp157) * fTemp158)) + (((this.fRec91[((this.IOTA - (iTemp159 + 2)) & 2047)] * fTemp160) * fTemp161) * fTemp162)) + (0.166667 * ((fTemp163 * this.fRec91[((this.IOTA - (iTemp164 + 2)) & 2047)]) * fTemp165))) + (0.0416667 * (fTemp166 * this.fRec91[((this.IOTA - (iTemp167 + 2)) & 2047)])))));
			var fTemp168 = ((iSlow7 * this.fRec27[0]) - (this.fRec85[1] + this.fVec4[1]));
			var fTemp169 = (fTemp168 * min_f(1, (1 / mydsp_faustpower4_f((Math.abs((fTemp54 * fTemp168)) + 0.75)))));
			var fRec86 = (this.fRec85[1] + fTemp169);
			var fTemp170 = (this.fVec4[1] + fTemp169);
			this.fVec5[(this.IOTA & 2047)] = fTemp170;
			var fRec87 = (((((fTemp122 * fTemp124) * fTemp126) * fTemp128) * this.fVec5[((this.IOTA - iTemp119) & 2047)]) + (fTemp129 * ((0.0416667 * (fTemp140 * this.fVec5[((this.IOTA - iTemp141) & 2047)])) + (((((fTemp134 * fTemp135) * fTemp136) * this.fVec5[((this.IOTA - iTemp133) & 2047)]) + (0.5 * (((fTemp121 * fTemp131) * fTemp132) * this.fVec5[((this.IOTA - iTemp130) & 2047)]))) + (0.166667 * ((fTemp137 * fTemp139) * this.fVec5[((this.IOTA - iTemp138) & 2047)]))))));
			var iRec88 = iRec92;
			this.fRec81[(this.IOTA & 2047)] = fRec86;
			var fRec82 = (((((fTemp148 * fTemp150) * fTemp152) * fTemp154) * this.fRec81[((this.IOTA - (iTemp145 + 1)) & 2047)]) + (fTemp155 * (((0.166667 * ((fTemp163 * fTemp165) * this.fRec81[((this.IOTA - (iTemp164 + 1)) & 2047)])) + ((((fTemp160 * fTemp161) * fTemp162) * this.fRec81[((this.IOTA - (iTemp159 + 1)) & 2047)]) + (0.5 * (((fTemp147 * fTemp157) * fTemp158) * this.fRec81[((this.IOTA - (iTemp156 + 1)) & 2047)])))) + (0.0416667 * (fTemp166 * this.fRec81[((this.IOTA - (iTemp167 + 1)) & 2047)])))));
			this.fRec83[0] = fRec87;
			var iRec84 = iRec88;
			this.fRec79[0] = this.fRec83[1];
			var iRec80 = iRec84;
			this.fRec77[0] = (this.fRec79[1] - (this.fConst3 * ((this.fConst8 * this.fRec77[1]) + (this.fConst7 * this.fRec77[2]))));
			var fTemp171 = (this.fConst3 * ((this.fConst2 * this.fRec77[0]) + (this.fConst9 * this.fRec77[2])));
			var fRec75 = fTemp171;
			var fRec76 = (iRec80 + fTemp171);
			this.iRec69[0] = iRec74;
			var fRec70 = fRec78;
			var fRec71 = fRec75;
			var fRec72 = fRec76;
			this.fRec65[(this.IOTA & 2047)] = fRec70;
			var fRec66 = fRec82;
			var fRec67 = fRec71;
			var fRec68 = fRec72;
			this.fRec63[0] = fRec66;
			var fRec64 = fRec68;
			this.iRec103[0] = 0;
			var iRec104 = this.iRec103[1];
			var fRec108 = (this.iRec99[1] - (0.989265 * ((0.6 * this.fRec109[2]) + (0.2 * (this.fRec109[1] + this.fRec109[3])))));
			this.fRec119[0] = (fSlow8 + (0.999 * this.fRec119[1]));
			var fTemp172 = (this.fRec119[0] + -0.08);
			var fTemp173 = (this.fConst5 * fTemp172);
			var fTemp174 = (fTemp173 + -1.49999);
			var iTemp175 = fTemp174;
			var iTemp176 = min_f(this.fConst4, max_i(0, iTemp175));
			var fTemp177 = Math.floor(fTemp174);
			var fTemp178 = (fTemp173 + (-1 - fTemp177));
			var fTemp179 = (0 - fTemp178);
			var fTemp180 = (fTemp173 + (-2 - fTemp177));
			var fTemp181 = (0 - (0.5 * fTemp180));
			var fTemp182 = (fTemp173 + (-3 - fTemp177));
			var fTemp183 = (0 - (0.333333 * fTemp182));
			var fTemp184 = (fTemp173 + (-4 - fTemp177));
			var fTemp185 = (0 - (0.25 * fTemp184));
			var fTemp186 = (fTemp173 - fTemp177);
			var iTemp187 = min_f(this.fConst4, max_i(0, (iTemp175 + 2)));
			var fTemp188 = (0 - fTemp182);
			var fTemp189 = (0 - (0.5 * fTemp184));
			var iTemp190 = min_f(this.fConst4, max_i(0, (iTemp175 + 1)));
			var fTemp191 = (0 - fTemp180);
			var fTemp192 = (0 - (0.5 * fTemp182));
			var fTemp193 = (0 - (0.333333 * fTemp184));
			var fTemp194 = (fTemp178 * fTemp180);
			var iTemp195 = min_f(this.fConst4, max_i(0, (iTemp175 + 3)));
			var fTemp196 = (0 - fTemp184);
			var fTemp197 = (fTemp194 * fTemp182);
			var iTemp198 = min_f(this.fConst4, max_i(0, (iTemp175 + 4)));
			this.fRec115[0] = (((((this.fRec95[((this.IOTA - (iTemp176 + 1)) & 2047)] * fTemp179) * fTemp181) * fTemp183) * fTemp185) + (fTemp186 * ((((0.5 * (((fTemp178 * this.fRec95[((this.IOTA - (iTemp187 + 1)) & 2047)]) * fTemp188) * fTemp189)) + (((this.fRec95[((this.IOTA - (iTemp190 + 1)) & 2047)] * fTemp191) * fTemp192) * fTemp193)) + (0.166667 * ((fTemp194 * this.fRec95[((this.IOTA - (iTemp195 + 1)) & 2047)]) * fTemp196))) + (0.0416667 * (fTemp197 * this.fRec95[((this.IOTA - (iTemp198 + 1)) & 2047)])))));
			this.fRec120[0] = this.fRec93[1];
			this.fRec121[(this.IOTA & 2047)] = (0 - (0.998801 * ((0.8 * this.fRec120[2]) + (0.1 * (this.fRec120[1] + this.fRec120[3])))));
			var iRec122 = 0;
			var fTemp199 = (this.fConst6 * fTemp172);
			var fTemp200 = (fTemp199 + -1.49999);
			var iTemp201 = fTemp200;
			var iTemp202 = min_f(this.fConst4, max_i(0, iTemp201));
			var fTemp203 = Math.floor(fTemp200);
			var fTemp204 = (fTemp199 + (-1 - fTemp203));
			var fTemp205 = (0 - fTemp204);
			var fTemp206 = (fTemp199 + (-2 - fTemp203));
			var fTemp207 = (0 - (0.5 * fTemp206));
			var fTemp208 = (fTemp199 + (-3 - fTemp203));
			var fTemp209 = (0 - (0.333333 * fTemp208));
			var fTemp210 = (fTemp199 + (-4 - fTemp203));
			var fTemp211 = (0 - (0.25 * fTemp210));
			var fTemp212 = (fTemp199 - fTemp203);
			var iTemp213 = min_f(this.fConst4, max_i(0, (iTemp201 + 2)));
			var fTemp214 = (0 - fTemp208);
			var fTemp215 = (0 - (0.5 * fTemp210));
			var iTemp216 = min_f(this.fConst4, max_i(0, (iTemp201 + 1)));
			var fTemp217 = (0 - fTemp206);
			var fTemp218 = (0 - (0.5 * fTemp208));
			var fTemp219 = (0 - (0.333333 * fTemp210));
			var fTemp220 = (fTemp204 * fTemp206);
			var iTemp221 = min_f(this.fConst4, max_i(0, (iTemp201 + 3)));
			var fTemp222 = (0 - fTemp210);
			var fTemp223 = (fTemp220 * fTemp208);
			var iTemp224 = min_f(this.fConst4, max_i(0, (iTemp201 + 4)));
			this.fVec6[0] = (((((this.fRec121[((this.IOTA - (iTemp202 + 2)) & 2047)] * fTemp205) * fTemp207) * fTemp209) * fTemp211) + (fTemp212 * ((((0.5 * (((fTemp204 * this.fRec121[((this.IOTA - (iTemp213 + 2)) & 2047)]) * fTemp214) * fTemp215)) + (((this.fRec121[((this.IOTA - (iTemp216 + 2)) & 2047)] * fTemp217) * fTemp218) * fTemp219)) + (0.166667 * ((fTemp220 * this.fRec121[((this.IOTA - (iTemp221 + 2)) & 2047)]) * fTemp222))) + (0.0416667 * (fTemp223 * this.fRec121[((this.IOTA - (iTemp224 + 2)) & 2047)])))));
			var fTemp225 = ((iSlow9 * this.fRec27[0]) - (this.fRec115[1] + this.fVec6[1]));
			var fTemp226 = (fTemp225 * min_f(1, (1 / mydsp_faustpower4_f((Math.abs((fTemp54 * fTemp225)) + 0.75)))));
			var fRec116 = (this.fRec115[1] + fTemp226);
			var fTemp227 = (this.fVec6[1] + fTemp226);
			this.fVec7[(this.IOTA & 2047)] = fTemp227;
			var fRec117 = (((((fTemp179 * fTemp181) * fTemp183) * fTemp185) * this.fVec7[((this.IOTA - iTemp176) & 2047)]) + (fTemp186 * ((0.0416667 * (fTemp197 * this.fVec7[((this.IOTA - iTemp198) & 2047)])) + (((((fTemp191 * fTemp192) * fTemp193) * this.fVec7[((this.IOTA - iTemp190) & 2047)]) + (0.5 * (((fTemp178 * fTemp188) * fTemp189) * this.fVec7[((this.IOTA - iTemp187) & 2047)]))) + (0.166667 * ((fTemp194 * fTemp196) * this.fVec7[((this.IOTA - iTemp195) & 2047)]))))));
			var iRec118 = iRec122;
			this.fRec111[(this.IOTA & 2047)] = fRec116;
			var fRec112 = (((((fTemp205 * fTemp207) * fTemp209) * fTemp211) * this.fRec111[((this.IOTA - (iTemp202 + 1)) & 2047)]) + (fTemp212 * (((0.166667 * ((fTemp220 * fTemp222) * this.fRec111[((this.IOTA - (iTemp221 + 1)) & 2047)])) + ((((fTemp217 * fTemp218) * fTemp219) * this.fRec111[((this.IOTA - (iTemp216 + 1)) & 2047)]) + (0.5 * (((fTemp204 * fTemp214) * fTemp215) * this.fRec111[((this.IOTA - (iTemp213 + 1)) & 2047)])))) + (0.0416667 * (fTemp223 * this.fRec111[((this.IOTA - (iTemp224 + 1)) & 2047)])))));
			this.fRec113[0] = fRec117;
			var iRec114 = iRec118;
			this.fRec109[0] = this.fRec113[1];
			var iRec110 = iRec114;
			this.fRec107[0] = (this.fRec109[1] - (this.fConst3 * ((this.fConst8 * this.fRec107[1]) + (this.fConst7 * this.fRec107[2]))));
			var fTemp228 = (this.fConst3 * ((this.fConst2 * this.fRec107[0]) + (this.fConst9 * this.fRec107[2])));
			var fRec105 = fTemp228;
			var fRec106 = (iRec110 + fTemp228);
			this.iRec99[0] = iRec104;
			var fRec100 = fRec108;
			var fRec101 = fRec105;
			var fRec102 = fRec106;
			this.fRec95[(this.IOTA & 2047)] = fRec100;
			var fRec96 = fRec112;
			var fRec97 = fRec101;
			var fRec98 = fRec102;
			this.fRec93[0] = fRec96;
			var fRec94 = fRec98;
			var fTemp229 = (((fRec1 + fRec34) + fRec64) + fRec94);
			output0[i] = fTemp229;
			output1[i] = fTemp229;
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
			this.fRec32[1] = this.fRec32[0];
			this.fRec20[1] = this.fRec20[0];
			for (var j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				this.fRec16[j1] = this.fRec16[(j1 - 1)];
				
			}
			this.fRec14[2] = this.fRec14[1];
			this.fRec14[1] = this.fRec14[0];
			this.iRec6[1] = this.iRec6[0];
			this.fRec0[1] = this.fRec0[0];
			this.iRec43[1] = this.iRec43[0];
			this.fRec59[1] = this.fRec59[0];
			this.fRec55[1] = this.fRec55[0];
			for (var j2 = 3; (j2 > 0); j2 = (j2 - 1)) {
				this.fRec60[j2] = this.fRec60[(j2 - 1)];
				
			}
			this.fVec2[1] = this.fVec2[0];
			this.fRec53[1] = this.fRec53[0];
			for (var j3 = 3; (j3 > 0); j3 = (j3 - 1)) {
				this.fRec49[j3] = this.fRec49[(j3 - 1)];
				
			}
			this.fRec47[2] = this.fRec47[1];
			this.fRec47[1] = this.fRec47[0];
			this.iRec39[1] = this.iRec39[0];
			this.fRec33[1] = this.fRec33[0];
			this.iRec73[1] = this.iRec73[0];
			this.fRec89[1] = this.fRec89[0];
			this.fRec85[1] = this.fRec85[0];
			for (var j4 = 3; (j4 > 0); j4 = (j4 - 1)) {
				this.fRec90[j4] = this.fRec90[(j4 - 1)];
				
			}
			this.fVec4[1] = this.fVec4[0];
			this.fRec83[1] = this.fRec83[0];
			for (var j5 = 3; (j5 > 0); j5 = (j5 - 1)) {
				this.fRec79[j5] = this.fRec79[(j5 - 1)];
				
			}
			this.fRec77[2] = this.fRec77[1];
			this.fRec77[1] = this.fRec77[0];
			this.iRec69[1] = this.iRec69[0];
			this.fRec63[1] = this.fRec63[0];
			this.iRec103[1] = this.iRec103[0];
			this.fRec119[1] = this.fRec119[0];
			this.fRec115[1] = this.fRec115[0];
			for (var j6 = 3; (j6 > 0); j6 = (j6 - 1)) {
				this.fRec120[j6] = this.fRec120[(j6 - 1)];
				
			}
			this.fVec6[1] = this.fVec6[0];
			this.fRec113[1] = this.fRec113[0];
			for (var j7 = 3; (j7 > 0); j7 = (j7 - 1)) {
				this.fRec109[j7] = this.fRec109[(j7 - 1)];
				
			}
			this.fRec107[2] = this.fRec107[1];
			this.fRec107[1] = this.fRec107[0];
			this.iRec99[1] = this.iRec99[0];
			this.fRec93[1] = this.fRec93[0];
			
		}
		
	}
	
}

