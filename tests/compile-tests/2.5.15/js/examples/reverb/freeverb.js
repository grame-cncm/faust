
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.max_i = function(dummy0, dummy1);
this.min_i = function(dummy0, dummy1);

function mydsp() {
	
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fVslider0;
	this.fConst2;
	this.fVslider1;
	this.fRec9 = new Float32Array(2);
	this.fVslider2;
	this.IOTA;
	this.fVec0 = new Float32Array(8192);
	this.iConst3;
	this.fRec8 = new Float32Array(2);
	this.fRec11 = new Float32Array(2);
	this.fVec1 = new Float32Array(8192);
	this.iConst4;
	this.fRec10 = new Float32Array(2);
	this.fRec13 = new Float32Array(2);
	this.fVec2 = new Float32Array(8192);
	this.iConst5;
	this.fRec12 = new Float32Array(2);
	this.fRec15 = new Float32Array(2);
	this.fVec3 = new Float32Array(8192);
	this.iConst6;
	this.fRec14 = new Float32Array(2);
	this.fRec17 = new Float32Array(2);
	this.fVec4 = new Float32Array(8192);
	this.iConst7;
	this.fRec16 = new Float32Array(2);
	this.fRec19 = new Float32Array(2);
	this.fVec5 = new Float32Array(8192);
	this.iConst8;
	this.fRec18 = new Float32Array(2);
	this.fRec21 = new Float32Array(2);
	this.fVec6 = new Float32Array(8192);
	this.iConst9;
	this.fRec20 = new Float32Array(2);
	this.fRec23 = new Float32Array(2);
	this.fVec7 = new Float32Array(8192);
	this.iConst10;
	this.fRec22 = new Float32Array(2);
	this.fVec8 = new Float32Array(2048);
	this.iConst11;
	this.iConst12;
	this.fRec6 = new Float32Array(2);
	this.fVec9 = new Float32Array(2048);
	this.iConst13;
	this.iConst14;
	this.fRec4 = new Float32Array(2);
	this.fVec10 = new Float32Array(2048);
	this.iConst15;
	this.iConst16;
	this.fRec2 = new Float32Array(2);
	this.fVec11 = new Float32Array(1024);
	this.iConst17;
	this.iConst18;
	this.fRec0 = new Float32Array(2);
	this.fRec33 = new Float32Array(2);
	this.fVec12 = new Float32Array(8192);
	this.fConst19;
	this.fVslider3;
	this.fRec32 = new Float32Array(2);
	this.fRec35 = new Float32Array(2);
	this.fVec13 = new Float32Array(8192);
	this.fRec34 = new Float32Array(2);
	this.fRec37 = new Float32Array(2);
	this.fVec14 = new Float32Array(8192);
	this.fRec36 = new Float32Array(2);
	this.fRec39 = new Float32Array(2);
	this.fVec15 = new Float32Array(8192);
	this.fRec38 = new Float32Array(2);
	this.fRec41 = new Float32Array(2);
	this.fVec16 = new Float32Array(8192);
	this.fRec40 = new Float32Array(2);
	this.fRec43 = new Float32Array(2);
	this.fVec17 = new Float32Array(8192);
	this.fRec42 = new Float32Array(2);
	this.fRec45 = new Float32Array(2);
	this.fVec18 = new Float32Array(8192);
	this.fRec44 = new Float32Array(2);
	this.fRec47 = new Float32Array(2);
	this.fVec19 = new Float32Array(8192);
	this.fRec46 = new Float32Array(2);
	this.fVec20 = new Float32Array(2048);
	this.fRec30 = new Float32Array(2);
	this.fVec21 = new Float32Array(2048);
	this.fRec28 = new Float32Array(2);
	this.fVec22 = new Float32Array(2048);
	this.fRec26 = new Float32Array(2);
	this.fVec23 = new Float32Array(2048);
	this.fRec24 = new Float32Array(2);
	
	this.metadata = function(m) { 
		m.declare("author", "RM");
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("description", "Freeverb demo application.");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "freeverb");
		m.declare("reverbs.lib/name", "Faust Reverb Library");
		m.declare("reverbs.lib/version", "0.0");
		m.declare("version", "0.0");
	}

	this.getNumInputs = function() {
		return 2;
		
	}
	this.getNumOutputs = function() {
		return 2;
		
	}
	this.getInputRate = function(channel) {
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
		this.fConst1 = (12348 / this.fConst0);
		this.fConst2 = (17640 / this.fConst0);
		this.iConst3 = (0.0253061 * this.fConst0);
		this.iConst4 = (0.0269388 * this.fConst0);
		this.iConst5 = (0.0289569 * this.fConst0);
		this.iConst6 = (0.0307483 * this.fConst0);
		this.iConst7 = (0.0322449 * this.fConst0);
		this.iConst8 = (0.0338095 * this.fConst0);
		this.iConst9 = (0.0353061 * this.fConst0);
		this.iConst10 = (0.0366667 * this.fConst0);
		this.iConst11 = (0.0126077 * this.fConst0);
		this.iConst12 = min_i(1024, max_i(0, (this.iConst11 + -1)));
		this.iConst13 = (0.01 * this.fConst0);
		this.iConst14 = min_i(1024, max_i(0, (this.iConst13 + -1)));
		this.iConst15 = (0.00773243 * this.fConst0);
		this.iConst16 = min_i(1024, max_i(0, (this.iConst15 + -1)));
		this.iConst17 = (0.00510204 * this.fConst0);
		this.iConst18 = min_i(1024, max_i(0, (this.iConst17 + -1)));
		this.fConst19 = (0.00104308 * this.fConst0);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fVslider0 = 0.5;
		this.fVslider1 = 0.5;
		this.fVslider2 = 0.3333;
		this.fVslider3 = 0.5;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.fRec9[l0] = 0;
			
		}
		this.IOTA = 0;
		for (var l1 = 0; (l1 < 8192); l1 = (l1 + 1)) {
			this.fVec0[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec8[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec11[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 8192); l4 = (l4 + 1)) {
			this.fVec1[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fRec10[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			this.fRec13[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 8192); l7 = (l7 + 1)) {
			this.fVec2[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			this.fRec12[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			this.fRec15[l9] = 0;
			
		}
		for (var l10 = 0; (l10 < 8192); l10 = (l10 + 1)) {
			this.fVec3[l10] = 0;
			
		}
		for (var l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			this.fRec14[l11] = 0;
			
		}
		for (var l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			this.fRec17[l12] = 0;
			
		}
		for (var l13 = 0; (l13 < 8192); l13 = (l13 + 1)) {
			this.fVec4[l13] = 0;
			
		}
		for (var l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			this.fRec16[l14] = 0;
			
		}
		for (var l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			this.fRec19[l15] = 0;
			
		}
		for (var l16 = 0; (l16 < 8192); l16 = (l16 + 1)) {
			this.fVec5[l16] = 0;
			
		}
		for (var l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			this.fRec18[l17] = 0;
			
		}
		for (var l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			this.fRec21[l18] = 0;
			
		}
		for (var l19 = 0; (l19 < 8192); l19 = (l19 + 1)) {
			this.fVec6[l19] = 0;
			
		}
		for (var l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			this.fRec20[l20] = 0;
			
		}
		for (var l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			this.fRec23[l21] = 0;
			
		}
		for (var l22 = 0; (l22 < 8192); l22 = (l22 + 1)) {
			this.fVec7[l22] = 0;
			
		}
		for (var l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			this.fRec22[l23] = 0;
			
		}
		for (var l24 = 0; (l24 < 2048); l24 = (l24 + 1)) {
			this.fVec8[l24] = 0;
			
		}
		for (var l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			this.fRec6[l25] = 0;
			
		}
		for (var l26 = 0; (l26 < 2048); l26 = (l26 + 1)) {
			this.fVec9[l26] = 0;
			
		}
		for (var l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			this.fRec4[l27] = 0;
			
		}
		for (var l28 = 0; (l28 < 2048); l28 = (l28 + 1)) {
			this.fVec10[l28] = 0;
			
		}
		for (var l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			this.fRec2[l29] = 0;
			
		}
		for (var l30 = 0; (l30 < 1024); l30 = (l30 + 1)) {
			this.fVec11[l30] = 0;
			
		}
		for (var l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			this.fRec0[l31] = 0;
			
		}
		for (var l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			this.fRec33[l32] = 0;
			
		}
		for (var l33 = 0; (l33 < 8192); l33 = (l33 + 1)) {
			this.fVec12[l33] = 0;
			
		}
		for (var l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			this.fRec32[l34] = 0;
			
		}
		for (var l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			this.fRec35[l35] = 0;
			
		}
		for (var l36 = 0; (l36 < 8192); l36 = (l36 + 1)) {
			this.fVec13[l36] = 0;
			
		}
		for (var l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			this.fRec34[l37] = 0;
			
		}
		for (var l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			this.fRec37[l38] = 0;
			
		}
		for (var l39 = 0; (l39 < 8192); l39 = (l39 + 1)) {
			this.fVec14[l39] = 0;
			
		}
		for (var l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			this.fRec36[l40] = 0;
			
		}
		for (var l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			this.fRec39[l41] = 0;
			
		}
		for (var l42 = 0; (l42 < 8192); l42 = (l42 + 1)) {
			this.fVec15[l42] = 0;
			
		}
		for (var l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			this.fRec38[l43] = 0;
			
		}
		for (var l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			this.fRec41[l44] = 0;
			
		}
		for (var l45 = 0; (l45 < 8192); l45 = (l45 + 1)) {
			this.fVec16[l45] = 0;
			
		}
		for (var l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			this.fRec40[l46] = 0;
			
		}
		for (var l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			this.fRec43[l47] = 0;
			
		}
		for (var l48 = 0; (l48 < 8192); l48 = (l48 + 1)) {
			this.fVec17[l48] = 0;
			
		}
		for (var l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			this.fRec42[l49] = 0;
			
		}
		for (var l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			this.fRec45[l50] = 0;
			
		}
		for (var l51 = 0; (l51 < 8192); l51 = (l51 + 1)) {
			this.fVec18[l51] = 0;
			
		}
		for (var l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			this.fRec44[l52] = 0;
			
		}
		for (var l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			this.fRec47[l53] = 0;
			
		}
		for (var l54 = 0; (l54 < 8192); l54 = (l54 + 1)) {
			this.fVec19[l54] = 0;
			
		}
		for (var l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			this.fRec46[l55] = 0;
			
		}
		for (var l56 = 0; (l56 < 2048); l56 = (l56 + 1)) {
			this.fVec20[l56] = 0;
			
		}
		for (var l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			this.fRec30[l57] = 0;
			
		}
		for (var l58 = 0; (l58 < 2048); l58 = (l58 + 1)) {
			this.fVec21[l58] = 0;
			
		}
		for (var l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			this.fRec28[l59] = 0;
			
		}
		for (var l60 = 0; (l60 < 2048); l60 = (l60 + 1)) {
			this.fVec22[l60] = 0;
			
		}
		for (var l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			this.fRec26[l61] = 0;
			
		}
		for (var l62 = 0; (l62 < 2048); l62 = (l62 + 1)) {
			this.fVec23[l62] = 0;
			
		}
		for (var l63 = 0; (l63 < 2); l63 = (l63 + 1)) {
			this.fRec24[l63] = 0;
			
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
		ui_interface.openHorizontalBox("Freeverb");
		ui_interface.declare("0", "0", "");
		ui_interface.openVerticalBox("0x00");
		ui_interface.declare("fVslider1", "0", "");
		ui_interface.declare("fVslider1", "style", "knob");
		ui_interface.declare("fVslider1", "tooltip", "Somehow control the   density of the reverb.");
		ui_interface.addVerticalSlider("Damp", function handler(obj) { function setval(val) { obj.fVslider1 = val; } return setval; }(this), 0.5, 0, 1, 0.025);
		ui_interface.declare("fVslider0", "1", "");
		ui_interface.declare("fVslider0", "style", "knob");
		ui_interface.declare("fVslider0", "tooltip", "The room size   between 0 and 1 with 1 for the largest room.");
		ui_interface.addVerticalSlider("RoomSize", function handler(obj) { function setval(val) { obj.fVslider0 = val; } return setval; }(this), 0.5, 0, 1, 0.025);
		ui_interface.declare("fVslider3", "2", "");
		ui_interface.declare("fVslider3", "style", "knob");
		ui_interface.declare("fVslider3", "tooltip", "Spatial   spread between 0 and 1 with 1 for maximum spread.");
		ui_interface.addVerticalSlider("Stereo Spread", function handler(obj) { function setval(val) { obj.fVslider3 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.closeBox();
		ui_interface.declare("fVslider2", "1", "");
		ui_interface.declare("fVslider2", "tooltip", "The amount of reverb applied to the signal   between 0 and 1 with 1 for the maximum amount of reverb.");
		ui_interface.addVerticalSlider("Wet", function handler(obj) { function setval(val) { obj.fVslider2 = val; } return setval; }(this), 0.3333, 0, 1, 0.025);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var input1 = inputs[1];
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = ((this.fConst1 * this.fVslider0) + 0.7);
		var fSlow1 = (this.fConst2 * this.fVslider1);
		var fSlow2 = (1 - fSlow1);
		var fSlow3 = this.fVslider2;
		var fSlow4 = (0.1 * fSlow3);
		var fSlow5 = (1 - fSlow3);
		var iSlow6 = (this.fConst19 * this.fVslider3);
		var iSlow7 = (this.iConst3 + iSlow6);
		var iSlow8 = (this.iConst4 + iSlow6);
		var iSlow9 = (this.iConst5 + iSlow6);
		var iSlow10 = (this.iConst6 + iSlow6);
		var iSlow11 = (this.iConst7 + iSlow6);
		var iSlow12 = (this.iConst8 + iSlow6);
		var iSlow13 = (this.iConst9 + iSlow6);
		var iSlow14 = (this.iConst10 + iSlow6);
		var iSlow15 = (iSlow6 + -1);
		var iSlow16 = min_i(1024, max_i(0, (this.iConst11 + iSlow15)));
		var iSlow17 = min_i(1024, max_i(0, (this.iConst13 + iSlow15)));
		var iSlow18 = min_i(1024, max_i(0, (this.iConst15 + iSlow15)));
		var iSlow19 = min_i(1024, max_i(0, (this.iConst17 + iSlow15)));
		for (var i = 0; (i < count); i = (i + 1)) {
			this.fRec9[0] = ((fSlow1 * this.fRec9[1]) + (fSlow2 * this.fRec8[1]));
			var fTemp0 = input0[i];
			var fTemp1 = input1[i];
			var fTemp2 = (fSlow4 * (fTemp0 + fTemp1));
			this.fVec0[(this.IOTA & 8191)] = ((fSlow0 * this.fRec9[0]) + fTemp2);
			this.fRec8[0] = this.fVec0[((this.IOTA - this.iConst3) & 8191)];
			this.fRec11[0] = ((fSlow1 * this.fRec11[1]) + (fSlow2 * this.fRec10[1]));
			this.fVec1[(this.IOTA & 8191)] = (fTemp2 + (fSlow0 * this.fRec11[0]));
			this.fRec10[0] = this.fVec1[((this.IOTA - this.iConst4) & 8191)];
			this.fRec13[0] = ((fSlow1 * this.fRec13[1]) + (fSlow2 * this.fRec12[1]));
			this.fVec2[(this.IOTA & 8191)] = (fTemp2 + (fSlow0 * this.fRec13[0]));
			this.fRec12[0] = this.fVec2[((this.IOTA - this.iConst5) & 8191)];
			this.fRec15[0] = ((fSlow1 * this.fRec15[1]) + (fSlow2 * this.fRec14[1]));
			this.fVec3[(this.IOTA & 8191)] = (fTemp2 + (fSlow0 * this.fRec15[0]));
			this.fRec14[0] = this.fVec3[((this.IOTA - this.iConst6) & 8191)];
			this.fRec17[0] = ((fSlow1 * this.fRec17[1]) + (fSlow2 * this.fRec16[1]));
			this.fVec4[(this.IOTA & 8191)] = (fTemp2 + (fSlow0 * this.fRec17[0]));
			this.fRec16[0] = this.fVec4[((this.IOTA - this.iConst7) & 8191)];
			this.fRec19[0] = ((fSlow1 * this.fRec19[1]) + (fSlow2 * this.fRec18[1]));
			this.fVec5[(this.IOTA & 8191)] = (fTemp2 + (fSlow0 * this.fRec19[0]));
			this.fRec18[0] = this.fVec5[((this.IOTA - this.iConst8) & 8191)];
			this.fRec21[0] = ((fSlow1 * this.fRec21[1]) + (fSlow2 * this.fRec20[1]));
			this.fVec6[(this.IOTA & 8191)] = (fTemp2 + (fSlow0 * this.fRec21[0]));
			this.fRec20[0] = this.fVec6[((this.IOTA - this.iConst9) & 8191)];
			this.fRec23[0] = ((fSlow1 * this.fRec23[1]) + (fSlow2 * this.fRec22[1]));
			this.fVec7[(this.IOTA & 8191)] = (fTemp2 + (fSlow0 * this.fRec23[0]));
			this.fRec22[0] = this.fVec7[((this.IOTA - this.iConst10) & 8191)];
			var fTemp3 = ((((((((this.fRec8[0] + this.fRec10[0]) + this.fRec12[0]) + this.fRec14[0]) + this.fRec16[0]) + this.fRec18[0]) + this.fRec20[0]) + this.fRec22[0]) + (0.5 * this.fRec6[1]));
			this.fVec8[(this.IOTA & 2047)] = fTemp3;
			this.fRec6[0] = this.fVec8[((this.IOTA - this.iConst12) & 2047)];
			var fRec7 = (0 - (0.5 * fTemp3));
			var fTemp4 = (this.fRec6[1] + (fRec7 + (0.5 * this.fRec4[1])));
			this.fVec9[(this.IOTA & 2047)] = fTemp4;
			this.fRec4[0] = this.fVec9[((this.IOTA - this.iConst14) & 2047)];
			var fRec5 = (0 - (0.5 * fTemp4));
			var fTemp5 = (this.fRec4[1] + (fRec5 + (0.5 * this.fRec2[1])));
			this.fVec10[(this.IOTA & 2047)] = fTemp5;
			this.fRec2[0] = this.fVec10[((this.IOTA - this.iConst16) & 2047)];
			var fRec3 = (0 - (0.5 * fTemp5));
			var fTemp6 = (this.fRec2[1] + (fRec3 + (0.5 * this.fRec0[1])));
			this.fVec11[(this.IOTA & 1023)] = fTemp6;
			this.fRec0[0] = this.fVec11[((this.IOTA - this.iConst18) & 1023)];
			var fRec1 = (0 - (0.5 * fTemp6));
			output0[i] = ((fRec1 + this.fRec0[1]) + (fSlow5 * fTemp0));
			this.fRec33[0] = ((fSlow1 * this.fRec33[1]) + (fSlow2 * this.fRec32[1]));
			this.fVec12[(this.IOTA & 8191)] = (fTemp2 + (fSlow0 * this.fRec33[0]));
			this.fRec32[0] = this.fVec12[((this.IOTA - iSlow7) & 8191)];
			this.fRec35[0] = ((fSlow1 * this.fRec35[1]) + (fSlow2 * this.fRec34[1]));
			this.fVec13[(this.IOTA & 8191)] = (fTemp2 + (fSlow0 * this.fRec35[0]));
			this.fRec34[0] = this.fVec13[((this.IOTA - iSlow8) & 8191)];
			this.fRec37[0] = ((fSlow1 * this.fRec37[1]) + (fSlow2 * this.fRec36[1]));
			this.fVec14[(this.IOTA & 8191)] = (fTemp2 + (fSlow0 * this.fRec37[0]));
			this.fRec36[0] = this.fVec14[((this.IOTA - iSlow9) & 8191)];
			this.fRec39[0] = ((fSlow1 * this.fRec39[1]) + (fSlow2 * this.fRec38[1]));
			this.fVec15[(this.IOTA & 8191)] = (fTemp2 + (fSlow0 * this.fRec39[0]));
			this.fRec38[0] = this.fVec15[((this.IOTA - iSlow10) & 8191)];
			this.fRec41[0] = ((fSlow1 * this.fRec41[1]) + (fSlow2 * this.fRec40[1]));
			this.fVec16[(this.IOTA & 8191)] = (fTemp2 + (fSlow0 * this.fRec41[0]));
			this.fRec40[0] = this.fVec16[((this.IOTA - iSlow11) & 8191)];
			this.fRec43[0] = ((fSlow1 * this.fRec43[1]) + (fSlow2 * this.fRec42[1]));
			this.fVec17[(this.IOTA & 8191)] = (fTemp2 + (fSlow0 * this.fRec43[0]));
			this.fRec42[0] = this.fVec17[((this.IOTA - iSlow12) & 8191)];
			this.fRec45[0] = ((fSlow1 * this.fRec45[1]) + (fSlow2 * this.fRec44[1]));
			this.fVec18[(this.IOTA & 8191)] = (fTemp2 + (fSlow0 * this.fRec45[0]));
			this.fRec44[0] = this.fVec18[((this.IOTA - iSlow13) & 8191)];
			this.fRec47[0] = ((fSlow1 * this.fRec47[1]) + (fSlow2 * this.fRec46[1]));
			this.fVec19[(this.IOTA & 8191)] = (fTemp2 + (fSlow0 * this.fRec47[0]));
			this.fRec46[0] = this.fVec19[((this.IOTA - iSlow14) & 8191)];
			var fTemp7 = ((((((((this.fRec32[0] + this.fRec34[0]) + this.fRec36[0]) + this.fRec38[0]) + this.fRec40[0]) + this.fRec42[0]) + this.fRec44[0]) + this.fRec46[0]) + (0.5 * this.fRec30[1]));
			this.fVec20[(this.IOTA & 2047)] = fTemp7;
			this.fRec30[0] = this.fVec20[((this.IOTA - iSlow16) & 2047)];
			var fRec31 = (0 - (0.5 * fTemp7));
			var fTemp8 = (this.fRec30[1] + (fRec31 + (0.5 * this.fRec28[1])));
			this.fVec21[(this.IOTA & 2047)] = fTemp8;
			this.fRec28[0] = this.fVec21[((this.IOTA - iSlow17) & 2047)];
			var fRec29 = (0 - (0.5 * fTemp8));
			var fTemp9 = (this.fRec28[1] + (fRec29 + (0.5 * this.fRec26[1])));
			this.fVec22[(this.IOTA & 2047)] = fTemp9;
			this.fRec26[0] = this.fVec22[((this.IOTA - iSlow18) & 2047)];
			var fRec27 = (0 - (0.5 * fTemp9));
			var fTemp10 = (this.fRec26[1] + (fRec27 + (0.5 * this.fRec24[1])));
			this.fVec23[(this.IOTA & 2047)] = fTemp10;
			this.fRec24[0] = this.fVec23[((this.IOTA - iSlow19) & 2047)];
			var fRec25 = (0 - (0.5 * fTemp10));
			output1[i] = ((fSlow5 * fTemp1) + (fRec25 + this.fRec24[1]));
			this.fRec9[1] = this.fRec9[0];
			this.IOTA = (this.IOTA + 1);
			this.fRec8[1] = this.fRec8[0];
			this.fRec11[1] = this.fRec11[0];
			this.fRec10[1] = this.fRec10[0];
			this.fRec13[1] = this.fRec13[0];
			this.fRec12[1] = this.fRec12[0];
			this.fRec15[1] = this.fRec15[0];
			this.fRec14[1] = this.fRec14[0];
			this.fRec17[1] = this.fRec17[0];
			this.fRec16[1] = this.fRec16[0];
			this.fRec19[1] = this.fRec19[0];
			this.fRec18[1] = this.fRec18[0];
			this.fRec21[1] = this.fRec21[0];
			this.fRec20[1] = this.fRec20[0];
			this.fRec23[1] = this.fRec23[0];
			this.fRec22[1] = this.fRec22[0];
			this.fRec6[1] = this.fRec6[0];
			this.fRec4[1] = this.fRec4[0];
			this.fRec2[1] = this.fRec2[0];
			this.fRec0[1] = this.fRec0[0];
			this.fRec33[1] = this.fRec33[0];
			this.fRec32[1] = this.fRec32[0];
			this.fRec35[1] = this.fRec35[0];
			this.fRec34[1] = this.fRec34[0];
			this.fRec37[1] = this.fRec37[0];
			this.fRec36[1] = this.fRec36[0];
			this.fRec39[1] = this.fRec39[0];
			this.fRec38[1] = this.fRec38[0];
			this.fRec41[1] = this.fRec41[0];
			this.fRec40[1] = this.fRec40[0];
			this.fRec43[1] = this.fRec43[0];
			this.fRec42[1] = this.fRec42[0];
			this.fRec45[1] = this.fRec45[0];
			this.fRec44[1] = this.fRec44[0];
			this.fRec47[1] = this.fRec47[0];
			this.fRec46[1] = this.fRec46[0];
			this.fRec30[1] = this.fRec30[0];
			this.fRec28[1] = this.fRec28[0];
			this.fRec26[1] = this.fRec26[0];
			this.fRec24[1] = this.fRec24[0];
			
		}
		
	}
	
}

