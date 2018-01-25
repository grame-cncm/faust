

function mydsp() {
	
	this.fHslider0;
	this.fHslider1;
	this.fHslider2;
	this.fRec9 = new Float32Array(2);
	this.IOTA;
	this.fVec0 = new Float32Array(2048);
	this.fRec8 = new Float32Array(2);
	this.fRec11 = new Float32Array(2);
	this.fVec1 = new Float32Array(2048);
	this.fRec10 = new Float32Array(2);
	this.fRec13 = new Float32Array(2);
	this.fVec2 = new Float32Array(2048);
	this.fRec12 = new Float32Array(2);
	this.fRec15 = new Float32Array(2);
	this.fVec3 = new Float32Array(2048);
	this.fRec14 = new Float32Array(2);
	this.fRec17 = new Float32Array(2);
	this.fVec4 = new Float32Array(2048);
	this.fRec16 = new Float32Array(2);
	this.fRec19 = new Float32Array(2);
	this.fVec5 = new Float32Array(2048);
	this.fRec18 = new Float32Array(2);
	this.fRec21 = new Float32Array(2);
	this.fVec6 = new Float32Array(2048);
	this.fRec20 = new Float32Array(2);
	this.fRec23 = new Float32Array(2);
	this.fVec7 = new Float32Array(2048);
	this.fRec22 = new Float32Array(2);
	this.fVec8 = new Float32Array(1024);
	this.fRec6 = new Float32Array(2);
	this.fVec9 = new Float32Array(512);
	this.fRec4 = new Float32Array(2);
	this.fVec10 = new Float32Array(512);
	this.fRec2 = new Float32Array(2);
	this.fVec11 = new Float32Array(256);
	this.fRec0 = new Float32Array(2);
	this.fRec33 = new Float32Array(2);
	this.fVec12 = new Float32Array(2048);
	this.fRec32 = new Float32Array(2);
	this.fRec35 = new Float32Array(2);
	this.fVec13 = new Float32Array(2048);
	this.fRec34 = new Float32Array(2);
	this.fRec37 = new Float32Array(2);
	this.fVec14 = new Float32Array(2048);
	this.fRec36 = new Float32Array(2);
	this.fRec39 = new Float32Array(2);
	this.fVec15 = new Float32Array(2048);
	this.fRec38 = new Float32Array(2);
	this.fRec41 = new Float32Array(2);
	this.fVec16 = new Float32Array(2048);
	this.fRec40 = new Float32Array(2);
	this.fRec43 = new Float32Array(2);
	this.fVec17 = new Float32Array(2048);
	this.fRec42 = new Float32Array(2);
	this.fRec45 = new Float32Array(2);
	this.fVec18 = new Float32Array(2048);
	this.fRec44 = new Float32Array(2);
	this.fRec47 = new Float32Array(2);
	this.fVec19 = new Float32Array(2048);
	this.fRec46 = new Float32Array(2);
	this.fVec20 = new Float32Array(1024);
	this.fRec30 = new Float32Array(2);
	this.fVec21 = new Float32Array(512);
	this.fRec28 = new Float32Array(2);
	this.fVec22 = new Float32Array(512);
	this.fRec26 = new Float32Array(2);
	this.fVec23 = new Float32Array(256);
	this.fRec24 = new Float32Array(2);
	this.fSamplingFreq;
	
	this.metadata = function(m) { 
		m.declare("name", "freeverb");
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
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 0.3333;
		this.fHslider1 = 0.5;
		this.fHslider2 = 0.5;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.fRec9[l0] = 0;
			
		}
		this.IOTA = 0;
		for (var l1 = 0; (l1 < 2048); l1 = (l1 + 1)) {
			this.fVec0[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec8[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec11[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2048); l4 = (l4 + 1)) {
			this.fVec1[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fRec10[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			this.fRec13[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 2048); l7 = (l7 + 1)) {
			this.fVec2[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			this.fRec12[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			this.fRec15[l9] = 0;
			
		}
		for (var l10 = 0; (l10 < 2048); l10 = (l10 + 1)) {
			this.fVec3[l10] = 0;
			
		}
		for (var l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			this.fRec14[l11] = 0;
			
		}
		for (var l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			this.fRec17[l12] = 0;
			
		}
		for (var l13 = 0; (l13 < 2048); l13 = (l13 + 1)) {
			this.fVec4[l13] = 0;
			
		}
		for (var l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			this.fRec16[l14] = 0;
			
		}
		for (var l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			this.fRec19[l15] = 0;
			
		}
		for (var l16 = 0; (l16 < 2048); l16 = (l16 + 1)) {
			this.fVec5[l16] = 0;
			
		}
		for (var l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			this.fRec18[l17] = 0;
			
		}
		for (var l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			this.fRec21[l18] = 0;
			
		}
		for (var l19 = 0; (l19 < 2048); l19 = (l19 + 1)) {
			this.fVec6[l19] = 0;
			
		}
		for (var l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			this.fRec20[l20] = 0;
			
		}
		for (var l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			this.fRec23[l21] = 0;
			
		}
		for (var l22 = 0; (l22 < 2048); l22 = (l22 + 1)) {
			this.fVec7[l22] = 0;
			
		}
		for (var l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			this.fRec22[l23] = 0;
			
		}
		for (var l24 = 0; (l24 < 1024); l24 = (l24 + 1)) {
			this.fVec8[l24] = 0;
			
		}
		for (var l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			this.fRec6[l25] = 0;
			
		}
		for (var l26 = 0; (l26 < 512); l26 = (l26 + 1)) {
			this.fVec9[l26] = 0;
			
		}
		for (var l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			this.fRec4[l27] = 0;
			
		}
		for (var l28 = 0; (l28 < 512); l28 = (l28 + 1)) {
			this.fVec10[l28] = 0;
			
		}
		for (var l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			this.fRec2[l29] = 0;
			
		}
		for (var l30 = 0; (l30 < 256); l30 = (l30 + 1)) {
			this.fVec11[l30] = 0;
			
		}
		for (var l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			this.fRec0[l31] = 0;
			
		}
		for (var l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			this.fRec33[l32] = 0;
			
		}
		for (var l33 = 0; (l33 < 2048); l33 = (l33 + 1)) {
			this.fVec12[l33] = 0;
			
		}
		for (var l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			this.fRec32[l34] = 0;
			
		}
		for (var l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			this.fRec35[l35] = 0;
			
		}
		for (var l36 = 0; (l36 < 2048); l36 = (l36 + 1)) {
			this.fVec13[l36] = 0;
			
		}
		for (var l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			this.fRec34[l37] = 0;
			
		}
		for (var l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			this.fRec37[l38] = 0;
			
		}
		for (var l39 = 0; (l39 < 2048); l39 = (l39 + 1)) {
			this.fVec14[l39] = 0;
			
		}
		for (var l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			this.fRec36[l40] = 0;
			
		}
		for (var l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			this.fRec39[l41] = 0;
			
		}
		for (var l42 = 0; (l42 < 2048); l42 = (l42 + 1)) {
			this.fVec15[l42] = 0;
			
		}
		for (var l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			this.fRec38[l43] = 0;
			
		}
		for (var l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			this.fRec41[l44] = 0;
			
		}
		for (var l45 = 0; (l45 < 2048); l45 = (l45 + 1)) {
			this.fVec16[l45] = 0;
			
		}
		for (var l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			this.fRec40[l46] = 0;
			
		}
		for (var l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			this.fRec43[l47] = 0;
			
		}
		for (var l48 = 0; (l48 < 2048); l48 = (l48 + 1)) {
			this.fVec17[l48] = 0;
			
		}
		for (var l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			this.fRec42[l49] = 0;
			
		}
		for (var l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			this.fRec45[l50] = 0;
			
		}
		for (var l51 = 0; (l51 < 2048); l51 = (l51 + 1)) {
			this.fVec18[l51] = 0;
			
		}
		for (var l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			this.fRec44[l52] = 0;
			
		}
		for (var l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			this.fRec47[l53] = 0;
			
		}
		for (var l54 = 0; (l54 < 2048); l54 = (l54 + 1)) {
			this.fVec19[l54] = 0;
			
		}
		for (var l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			this.fRec46[l55] = 0;
			
		}
		for (var l56 = 0; (l56 < 1024); l56 = (l56 + 1)) {
			this.fVec20[l56] = 0;
			
		}
		for (var l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			this.fRec30[l57] = 0;
			
		}
		for (var l58 = 0; (l58 < 512); l58 = (l58 + 1)) {
			this.fVec21[l58] = 0;
			
		}
		for (var l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			this.fRec28[l59] = 0;
			
		}
		for (var l60 = 0; (l60 < 512); l60 = (l60 + 1)) {
			this.fVec22[l60] = 0;
			
		}
		for (var l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			this.fRec26[l61] = 0;
			
		}
		for (var l62 = 0; (l62 < 256); l62 = (l62 + 1)) {
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
		ui_interface.openVerticalBox("Freeverb");
		ui_interface.addHorizontalSlider("Damp", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 0.5, 0, 1, 0.025);
		ui_interface.addHorizontalSlider("RoomSize", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 0.5, 0, 1, 0.025);
		ui_interface.addHorizontalSlider("Wet", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0.3333, 0, 1, 0.025);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var input1 = inputs[1];
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = this.fHslider0;
		var fSlow1 = ((0.28 * this.fHslider1) + 0.7);
		var fSlow2 = (0.4 * this.fHslider2);
		var fSlow3 = (1 - fSlow2);
		var fSlow4 = (1 - fSlow0);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.fRec9[0] = ((fSlow2 * this.fRec9[1]) + (fSlow3 * this.fRec8[1]));
			var fTemp0 = input0[i];
			var fTemp1 = input1[i];
			var fTemp2 = (0.015 * (fTemp0 + fTemp1));
			this.fVec0[(this.IOTA & 2047)] = ((fSlow1 * this.fRec9[0]) + fTemp2);
			this.fRec8[0] = this.fVec0[((this.IOTA - 1116) & 2047)];
			this.fRec11[0] = ((fSlow2 * this.fRec11[1]) + (fSlow3 * this.fRec10[1]));
			this.fVec1[(this.IOTA & 2047)] = (fTemp2 + (fSlow1 * this.fRec11[0]));
			this.fRec10[0] = this.fVec1[((this.IOTA - 1188) & 2047)];
			this.fRec13[0] = ((fSlow2 * this.fRec13[1]) + (fSlow3 * this.fRec12[1]));
			this.fVec2[(this.IOTA & 2047)] = (fTemp2 + (fSlow1 * this.fRec13[0]));
			this.fRec12[0] = this.fVec2[((this.IOTA - 1277) & 2047)];
			this.fRec15[0] = ((fSlow2 * this.fRec15[1]) + (fSlow3 * this.fRec14[1]));
			this.fVec3[(this.IOTA & 2047)] = (fTemp2 + (fSlow1 * this.fRec15[0]));
			this.fRec14[0] = this.fVec3[((this.IOTA - 1356) & 2047)];
			this.fRec17[0] = ((fSlow2 * this.fRec17[1]) + (fSlow3 * this.fRec16[1]));
			this.fVec4[(this.IOTA & 2047)] = (fTemp2 + (fSlow1 * this.fRec17[0]));
			this.fRec16[0] = this.fVec4[((this.IOTA - 1422) & 2047)];
			this.fRec19[0] = ((fSlow2 * this.fRec19[1]) + (fSlow3 * this.fRec18[1]));
			this.fVec5[(this.IOTA & 2047)] = (fTemp2 + (fSlow1 * this.fRec19[0]));
			this.fRec18[0] = this.fVec5[((this.IOTA - 1491) & 2047)];
			this.fRec21[0] = ((fSlow2 * this.fRec21[1]) + (fSlow3 * this.fRec20[1]));
			this.fVec6[(this.IOTA & 2047)] = (fTemp2 + (fSlow1 * this.fRec21[0]));
			this.fRec20[0] = this.fVec6[((this.IOTA - 1557) & 2047)];
			this.fRec23[0] = ((fSlow2 * this.fRec23[1]) + (fSlow3 * this.fRec22[1]));
			this.fVec7[(this.IOTA & 2047)] = (fTemp2 + (fSlow1 * this.fRec23[0]));
			this.fRec22[0] = this.fVec7[((this.IOTA - 1617) & 2047)];
			var fTemp3 = (((((((this.fRec8[0] + this.fRec10[0]) + this.fRec12[0]) + this.fRec14[0]) + this.fRec16[0]) + this.fRec18[0]) + this.fRec20[0]) + this.fRec22[0]);
			this.fVec8[(this.IOTA & 1023)] = (fTemp3 + (0.5 * this.fRec6[1]));
			this.fRec6[0] = this.fVec8[((this.IOTA - 556) & 1023)];
			var fRec7 = (this.fRec6[1] - fTemp3);
			this.fVec9[(this.IOTA & 511)] = (fRec7 + (0.5 * this.fRec4[1]));
			this.fRec4[0] = this.fVec9[((this.IOTA - 441) & 511)];
			var fRec5 = (this.fRec4[1] - fRec7);
			this.fVec10[(this.IOTA & 511)] = (fRec5 + (0.5 * this.fRec2[1]));
			this.fRec2[0] = this.fVec10[((this.IOTA - 341) & 511)];
			var fRec3 = (this.fRec2[1] - fRec5);
			this.fVec11[(this.IOTA & 255)] = (fRec3 + (0.5 * this.fRec0[1]));
			this.fRec0[0] = this.fVec11[((this.IOTA - 225) & 255)];
			var fRec1 = (this.fRec0[1] - fRec3);
			output0[i] = ((fSlow0 * fRec1) + (fSlow4 * fTemp0));
			this.fRec33[0] = ((fSlow2 * this.fRec33[1]) + (fSlow3 * this.fRec32[1]));
			this.fVec12[(this.IOTA & 2047)] = (fTemp2 + (fSlow1 * this.fRec33[0]));
			this.fRec32[0] = this.fVec12[((this.IOTA - 1139) & 2047)];
			this.fRec35[0] = ((fSlow2 * this.fRec35[1]) + (fSlow3 * this.fRec34[1]));
			this.fVec13[(this.IOTA & 2047)] = (fTemp2 + (fSlow1 * this.fRec35[0]));
			this.fRec34[0] = this.fVec13[((this.IOTA - 1211) & 2047)];
			this.fRec37[0] = ((fSlow2 * this.fRec37[1]) + (fSlow3 * this.fRec36[1]));
			this.fVec14[(this.IOTA & 2047)] = (fTemp2 + (fSlow1 * this.fRec37[0]));
			this.fRec36[0] = this.fVec14[((this.IOTA - 1300) & 2047)];
			this.fRec39[0] = ((fSlow2 * this.fRec39[1]) + (fSlow3 * this.fRec38[1]));
			this.fVec15[(this.IOTA & 2047)] = (fTemp2 + (fSlow1 * this.fRec39[0]));
			this.fRec38[0] = this.fVec15[((this.IOTA - 1379) & 2047)];
			this.fRec41[0] = ((fSlow2 * this.fRec41[1]) + (fSlow3 * this.fRec40[1]));
			this.fVec16[(this.IOTA & 2047)] = (fTemp2 + (fSlow1 * this.fRec41[0]));
			this.fRec40[0] = this.fVec16[((this.IOTA - 1445) & 2047)];
			this.fRec43[0] = ((fSlow2 * this.fRec43[1]) + (fSlow3 * this.fRec42[1]));
			this.fVec17[(this.IOTA & 2047)] = (fTemp2 + (fSlow1 * this.fRec43[0]));
			this.fRec42[0] = this.fVec17[((this.IOTA - 1514) & 2047)];
			this.fRec45[0] = ((fSlow2 * this.fRec45[1]) + (fSlow3 * this.fRec44[1]));
			this.fVec18[(this.IOTA & 2047)] = (fTemp2 + (fSlow1 * this.fRec45[0]));
			this.fRec44[0] = this.fVec18[((this.IOTA - 1580) & 2047)];
			this.fRec47[0] = ((fSlow2 * this.fRec47[1]) + (fSlow3 * this.fRec46[1]));
			this.fVec19[(this.IOTA & 2047)] = (fTemp2 + (fSlow1 * this.fRec47[0]));
			this.fRec46[0] = this.fVec19[((this.IOTA - 1640) & 2047)];
			var fTemp4 = (((((((this.fRec32[0] + this.fRec34[0]) + this.fRec36[0]) + this.fRec38[0]) + this.fRec40[0]) + this.fRec42[0]) + this.fRec44[0]) + this.fRec46[0]);
			this.fVec20[(this.IOTA & 1023)] = (fTemp4 + (0.5 * this.fRec30[1]));
			this.fRec30[0] = this.fVec20[((this.IOTA - 579) & 1023)];
			var fRec31 = (this.fRec30[1] - fTemp4);
			this.fVec21[(this.IOTA & 511)] = (fRec31 + (0.5 * this.fRec28[1]));
			this.fRec28[0] = this.fVec21[((this.IOTA - 464) & 511)];
			var fRec29 = (this.fRec28[1] - fRec31);
			this.fVec22[(this.IOTA & 511)] = (fRec29 + (0.5 * this.fRec26[1]));
			this.fRec26[0] = this.fVec22[((this.IOTA - 364) & 511)];
			var fRec27 = (this.fRec26[1] - fRec29);
			this.fVec23[(this.IOTA & 255)] = (fRec27 + (0.5 * this.fRec24[1]));
			this.fRec24[0] = this.fVec23[((this.IOTA - 248) & 255)];
			var fRec25 = (this.fRec24[1] - fRec27);
			output1[i] = ((fSlow0 * fRec25) + (fSlow4 * fTemp1));
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

