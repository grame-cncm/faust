
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);

function mydsp() {
	
	this.fSamplingFreq;
	this.fConst0;
	this.IOTA;
	this.fVec0 = new Float32Array(512);
	this.fVec1 = new Float32Array(512);
	this.fVec2 = new Float32Array(512);
	this.fVec3 = new Float32Array(512);
	this.fVec4 = new Float32Array(512);
	this.fVec5 = new Float32Array(512);
	this.fRec0 = new Float32Array(2);
	this.fVbargraph0;
	this.fRec1 = new Float32Array(2);
	this.fVbargraph1;
	this.fRec2 = new Float32Array(2);
	this.fVbargraph2;
	this.fRec3 = new Float32Array(2);
	this.fVbargraph3;
	this.fRec4 = new Float32Array(2);
	this.fVbargraph4;
	this.fRec5 = new Float32Array(2);
	this.fVbargraph5;
	this.fRec6 = new Float32Array(2);
	this.fVbargraph6;
	this.fRec7 = new Float32Array(2);
	this.fVbargraph7;
	this.fRec8 = new Float32Array(2);
	this.fVbargraph8;
	this.fRec9 = new Float32Array(2);
	this.fVbargraph9;
	this.fRec10 = new Float32Array(2);
	this.fVbargraph10;
	this.fRec11 = new Float32Array(2);
	this.fVbargraph11;
	this.fRec12 = new Float32Array(2);
	this.fVbargraph12;
	this.fRec13 = new Float32Array(2);
	this.fVbargraph13;
	this.fRec14 = new Float32Array(2);
	this.fVbargraph14;
	this.fRec15 = new Float32Array(2);
	this.fVbargraph15;
	this.fRec16 = new Float32Array(2);
	this.fVbargraph16;
	this.fRec17 = new Float32Array(2);
	this.fVbargraph17;
	this.fRec18 = new Float32Array(2);
	this.fVbargraph18;
	this.fRec19 = new Float32Array(2);
	this.fVbargraph19;
	this.fRec20 = new Float32Array(2);
	this.fVbargraph20;
	this.fRec21 = new Float32Array(2);
	this.fVbargraph21;
	this.fRec22 = new Float32Array(2);
	this.fVbargraph22;
	this.fRec23 = new Float32Array(2);
	this.fVbargraph23;
	this.fRec24 = new Float32Array(2);
	this.fVbargraph24;
	this.fRec25 = new Float32Array(2);
	this.fVbargraph25;
	this.fRec26 = new Float32Array(2);
	this.fVbargraph26;
	this.fRec27 = new Float32Array(2);
	this.fVbargraph27;
	this.fRec28 = new Float32Array(2);
	this.fVbargraph28;
	this.fRec29 = new Float32Array(2);
	this.fVbargraph29;
	this.fRec30 = new Float32Array(2);
	this.fVbargraph30;
	this.fRec31 = new Float32Array(2);
	this.fVbargraph31;
	this.fRec32 = new Float32Array(2);
	this.fVbargraph32;
	this.fRec33 = new Float32Array(2);
	this.fVbargraph33;
	this.fRec34 = new Float32Array(2);
	this.fVbargraph34;
	this.fRec35 = new Float32Array(2);
	this.fVbargraph35;
	
	this.metadata = function(m) { 
		m.declare("math.lib/author", "GRAME");
		m.declare("math.lib/copyright", "GRAME");
		m.declare("math.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m.declare("math.lib/license", "LGPL with exception");
		m.declare("math.lib/name", "Math Library");
		m.declare("math.lib/version", "1.0");
		m.declare("music.lib/author", "GRAME");
		m.declare("music.lib/copyright", "GRAME");
		m.declare("music.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m.declare("music.lib/license", "LGPL with exception");
		m.declare("music.lib/name", "Music Library");
		m.declare("music.lib/version", "1.0");
		m.declare("name", "felix2");
	}

	this.getNumInputs = function() {
		return 6;
		
	}
	this.getNumOutputs = function() {
		return 36;
		
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
			case 2: {
				rate = 1;
				break;
			}
			case 3: {
				rate = 1;
				break;
			}
			case 4: {
				rate = 1;
				break;
			}
			case 5: {
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
			case 2: {
				rate = 1;
				break;
			}
			case 3: {
				rate = 1;
				break;
			}
			case 4: {
				rate = 1;
				break;
			}
			case 5: {
				rate = 1;
				break;
			}
			case 6: {
				rate = 1;
				break;
			}
			case 7: {
				rate = 1;
				break;
			}
			case 8: {
				rate = 1;
				break;
			}
			case 9: {
				rate = 1;
				break;
			}
			case 10: {
				rate = 1;
				break;
			}
			case 11: {
				rate = 1;
				break;
			}
			case 12: {
				rate = 1;
				break;
			}
			case 13: {
				rate = 1;
				break;
			}
			case 14: {
				rate = 1;
				break;
			}
			case 15: {
				rate = 1;
				break;
			}
			case 16: {
				rate = 1;
				break;
			}
			case 17: {
				rate = 1;
				break;
			}
			case 18: {
				rate = 1;
				break;
			}
			case 19: {
				rate = 1;
				break;
			}
			case 20: {
				rate = 1;
				break;
			}
			case 21: {
				rate = 1;
				break;
			}
			case 22: {
				rate = 1;
				break;
			}
			case 23: {
				rate = 1;
				break;
			}
			case 24: {
				rate = 1;
				break;
			}
			case 25: {
				rate = 1;
				break;
			}
			case 26: {
				rate = 1;
				break;
			}
			case 27: {
				rate = 1;
				break;
			}
			case 28: {
				rate = 1;
				break;
			}
			case 29: {
				rate = 1;
				break;
			}
			case 30: {
				rate = 1;
				break;
			}
			case 31: {
				rate = 1;
				break;
			}
			case 32: {
				rate = 1;
				break;
			}
			case 33: {
				rate = 1;
				break;
			}
			case 34: {
				rate = 1;
				break;
			}
			case 35: {
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
		this.fConst0 = (96 / min_f(192000, max_f(1, this.fSamplingFreq)));
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		
	}
	
	this.instanceClear = function() {
		this.IOTA = 0;
		for (var l0 = 0; (l0 < 512); l0 = (l0 + 1)) {
			this.fVec0[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 512); l1 = (l1 + 1)) {
			this.fVec1[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 512); l2 = (l2 + 1)) {
			this.fVec2[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 512); l3 = (l3 + 1)) {
			this.fVec3[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 512); l4 = (l4 + 1)) {
			this.fVec4[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 512); l5 = (l5 + 1)) {
			this.fVec5[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			this.fRec0[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			this.fRec1[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			this.fRec2[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			this.fRec3[l9] = 0;
			
		}
		for (var l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			this.fRec4[l10] = 0;
			
		}
		for (var l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			this.fRec5[l11] = 0;
			
		}
		for (var l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			this.fRec6[l12] = 0;
			
		}
		for (var l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			this.fRec7[l13] = 0;
			
		}
		for (var l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			this.fRec8[l14] = 0;
			
		}
		for (var l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			this.fRec9[l15] = 0;
			
		}
		for (var l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			this.fRec10[l16] = 0;
			
		}
		for (var l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			this.fRec11[l17] = 0;
			
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
			this.fRec15[l21] = 0;
			
		}
		for (var l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			this.fRec16[l22] = 0;
			
		}
		for (var l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			this.fRec17[l23] = 0;
			
		}
		for (var l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			this.fRec18[l24] = 0;
			
		}
		for (var l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			this.fRec19[l25] = 0;
			
		}
		for (var l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			this.fRec20[l26] = 0;
			
		}
		for (var l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			this.fRec21[l27] = 0;
			
		}
		for (var l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			this.fRec22[l28] = 0;
			
		}
		for (var l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			this.fRec23[l29] = 0;
			
		}
		for (var l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			this.fRec24[l30] = 0;
			
		}
		for (var l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			this.fRec25[l31] = 0;
			
		}
		for (var l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			this.fRec26[l32] = 0;
			
		}
		for (var l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			this.fRec27[l33] = 0;
			
		}
		for (var l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			this.fRec28[l34] = 0;
			
		}
		for (var l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			this.fRec29[l35] = 0;
			
		}
		for (var l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			this.fRec30[l36] = 0;
			
		}
		for (var l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			this.fRec31[l37] = 0;
			
		}
		for (var l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			this.fRec32[l38] = 0;
			
		}
		for (var l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			this.fRec33[l39] = 0;
			
		}
		for (var l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			this.fRec34[l40] = 0;
			
		}
		for (var l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			this.fRec35[l41] = 0;
			
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
		ui_interface.openVerticalBox("felix2");
		ui_interface.openHorizontalBox("ctrl   0");
		ui_interface.addVerticalBargraph("ctrl  0", function handler(obj) { function setval(val) { obj.fVbargraph0 = val; } return setval; }(this), 0, 1);
		ui_interface.addVerticalBargraph("ctrl  1", function handler(obj) { function setval(val) { obj.fVbargraph1 = val; } return setval; }(this), 0, 1);
		ui_interface.addVerticalBargraph("ctrl  2", function handler(obj) { function setval(val) { obj.fVbargraph2 = val; } return setval; }(this), 0, 1);
		ui_interface.addVerticalBargraph("ctrl  3", function handler(obj) { function setval(val) { obj.fVbargraph3 = val; } return setval; }(this), 0, 1);
		ui_interface.addVerticalBargraph("ctrl  4", function handler(obj) { function setval(val) { obj.fVbargraph4 = val; } return setval; }(this), 0, 1);
		ui_interface.addVerticalBargraph("ctrl  5", function handler(obj) { function setval(val) { obj.fVbargraph5 = val; } return setval; }(this), 0, 1);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("ctrl   1");
		ui_interface.addVerticalBargraph("ctrl 10", function handler(obj) { function setval(val) { obj.fVbargraph6 = val; } return setval; }(this), 0, 1);
		ui_interface.addVerticalBargraph("ctrl 11", function handler(obj) { function setval(val) { obj.fVbargraph7 = val; } return setval; }(this), 0, 1);
		ui_interface.addVerticalBargraph("ctrl 12", function handler(obj) { function setval(val) { obj.fVbargraph8 = val; } return setval; }(this), 0, 1);
		ui_interface.addVerticalBargraph("ctrl 13", function handler(obj) { function setval(val) { obj.fVbargraph9 = val; } return setval; }(this), 0, 1);
		ui_interface.addVerticalBargraph("ctrl 14", function handler(obj) { function setval(val) { obj.fVbargraph10 = val; } return setval; }(this), 0, 1);
		ui_interface.addVerticalBargraph("ctrl 15", function handler(obj) { function setval(val) { obj.fVbargraph11 = val; } return setval; }(this), 0, 1);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("ctrl   2");
		ui_interface.addVerticalBargraph("ctrl 20", function handler(obj) { function setval(val) { obj.fVbargraph12 = val; } return setval; }(this), 0, 1);
		ui_interface.addVerticalBargraph("ctrl 21", function handler(obj) { function setval(val) { obj.fVbargraph13 = val; } return setval; }(this), 0, 1);
		ui_interface.addVerticalBargraph("ctrl 22", function handler(obj) { function setval(val) { obj.fVbargraph14 = val; } return setval; }(this), 0, 1);
		ui_interface.addVerticalBargraph("ctrl 23", function handler(obj) { function setval(val) { obj.fVbargraph15 = val; } return setval; }(this), 0, 1);
		ui_interface.addVerticalBargraph("ctrl 24", function handler(obj) { function setval(val) { obj.fVbargraph16 = val; } return setval; }(this), 0, 1);
		ui_interface.addVerticalBargraph("ctrl 25", function handler(obj) { function setval(val) { obj.fVbargraph17 = val; } return setval; }(this), 0, 1);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("ctrl   3");
		ui_interface.addVerticalBargraph("ctrl 30", function handler(obj) { function setval(val) { obj.fVbargraph18 = val; } return setval; }(this), 0, 1);
		ui_interface.addVerticalBargraph("ctrl 31", function handler(obj) { function setval(val) { obj.fVbargraph19 = val; } return setval; }(this), 0, 1);
		ui_interface.addVerticalBargraph("ctrl 32", function handler(obj) { function setval(val) { obj.fVbargraph20 = val; } return setval; }(this), 0, 1);
		ui_interface.addVerticalBargraph("ctrl 33", function handler(obj) { function setval(val) { obj.fVbargraph21 = val; } return setval; }(this), 0, 1);
		ui_interface.addVerticalBargraph("ctrl 34", function handler(obj) { function setval(val) { obj.fVbargraph22 = val; } return setval; }(this), 0, 1);
		ui_interface.addVerticalBargraph("ctrl 35", function handler(obj) { function setval(val) { obj.fVbargraph23 = val; } return setval; }(this), 0, 1);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("ctrl   4");
		ui_interface.addVerticalBargraph("ctrl 40", function handler(obj) { function setval(val) { obj.fVbargraph24 = val; } return setval; }(this), 0, 1);
		ui_interface.addVerticalBargraph("ctrl 41", function handler(obj) { function setval(val) { obj.fVbargraph25 = val; } return setval; }(this), 0, 1);
		ui_interface.addVerticalBargraph("ctrl 42", function handler(obj) { function setval(val) { obj.fVbargraph26 = val; } return setval; }(this), 0, 1);
		ui_interface.addVerticalBargraph("ctrl 43", function handler(obj) { function setval(val) { obj.fVbargraph27 = val; } return setval; }(this), 0, 1);
		ui_interface.addVerticalBargraph("ctrl 44", function handler(obj) { function setval(val) { obj.fVbargraph28 = val; } return setval; }(this), 0, 1);
		ui_interface.addVerticalBargraph("ctrl 45", function handler(obj) { function setval(val) { obj.fVbargraph29 = val; } return setval; }(this), 0, 1);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("ctrl   5");
		ui_interface.addVerticalBargraph("ctrl 50", function handler(obj) { function setval(val) { obj.fVbargraph30 = val; } return setval; }(this), 0, 1);
		ui_interface.addVerticalBargraph("ctrl 51", function handler(obj) { function setval(val) { obj.fVbargraph31 = val; } return setval; }(this), 0, 1);
		ui_interface.addVerticalBargraph("ctrl 52", function handler(obj) { function setval(val) { obj.fVbargraph32 = val; } return setval; }(this), 0, 1);
		ui_interface.addVerticalBargraph("ctrl 53", function handler(obj) { function setval(val) { obj.fVbargraph33 = val; } return setval; }(this), 0, 1);
		ui_interface.addVerticalBargraph("ctrl 54", function handler(obj) { function setval(val) { obj.fVbargraph34 = val; } return setval; }(this), 0, 1);
		ui_interface.addVerticalBargraph("ctrl 55", function handler(obj) { function setval(val) { obj.fVbargraph35 = val; } return setval; }(this), 0, 1);
		ui_interface.closeBox();
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var input1 = inputs[1];
		var input2 = inputs[2];
		var input3 = inputs[3];
		var input4 = inputs[4];
		var input5 = inputs[5];
		var output0 = outputs[0];
		var output1 = outputs[1];
		var output2 = outputs[2];
		var output3 = outputs[3];
		var output4 = outputs[4];
		var output5 = outputs[5];
		var output6 = outputs[6];
		var output7 = outputs[7];
		var output8 = outputs[8];
		var output9 = outputs[9];
		var output10 = outputs[10];
		var output11 = outputs[11];
		var output12 = outputs[12];
		var output13 = outputs[13];
		var output14 = outputs[14];
		var output15 = outputs[15];
		var output16 = outputs[16];
		var output17 = outputs[17];
		var output18 = outputs[18];
		var output19 = outputs[19];
		var output20 = outputs[20];
		var output21 = outputs[21];
		var output22 = outputs[22];
		var output23 = outputs[23];
		var output24 = outputs[24];
		var output25 = outputs[25];
		var output26 = outputs[26];
		var output27 = outputs[27];
		var output28 = outputs[28];
		var output29 = outputs[29];
		var output30 = outputs[30];
		var output31 = outputs[31];
		var output32 = outputs[32];
		var output33 = outputs[33];
		var output34 = outputs[34];
		var output35 = outputs[35];
		for (var i = 0; (i < count); i = (i + 1)) {
			this.fVec0[(this.IOTA & 511)] = input0[i];
			var fTemp0 = input1[i];
			this.fVec1[(this.IOTA & 511)] = fTemp0;
			var fTemp1 = input2[i];
			this.fVec2[(this.IOTA & 511)] = fTemp1;
			var fTemp2 = input3[i];
			this.fVec3[(this.IOTA & 511)] = fTemp2;
			var fTemp3 = input4[i];
			this.fVec4[(this.IOTA & 511)] = fTemp3;
			var fTemp4 = input5[i];
			this.fVec5[(this.IOTA & 511)] = fTemp4;
			this.fRec0[0] = max_f((this.fRec0[1] - this.fConst0), Math.abs((((((this.fVec0[((this.IOTA - 256) & 511)] + this.fVec1[((this.IOTA - 244) & 511)]) + this.fVec2[((this.IOTA - 233) & 511)]) + this.fVec3[((this.IOTA - 221) & 511)]) + this.fVec4[((this.IOTA - 209) & 511)]) + this.fVec5[((this.IOTA - 197) & 511)])));
			this.fVbargraph0 = this.fRec0[0];
			output0[i] = this.fVbargraph0;
			var fTemp5 = (this.fVec0[((this.IOTA - 256) & 511)] + this.fVec1[((this.IOTA - 246) & 511)]);
			this.fRec1[0] = max_f((this.fRec1[1] - this.fConst0), Math.abs(((((fTemp5 + this.fVec2[((this.IOTA - 236) & 511)]) + this.fVec3[((this.IOTA - 225) & 511)]) + this.fVec4[((this.IOTA - 215) & 511)]) + this.fVec5[((this.IOTA - 204) & 511)])));
			this.fVbargraph1 = this.fRec1[0];
			output1[i] = this.fVbargraph1;
			this.fRec2[0] = max_f((this.fRec2[1] - this.fConst0), Math.abs((((((this.fVec0[((this.IOTA - 256) & 511)] + this.fVec1[((this.IOTA - 247) & 511)]) + this.fVec2[((this.IOTA - 239) & 511)]) + this.fVec3[((this.IOTA - 230) & 511)]) + this.fVec4[((this.IOTA - 220) & 511)]) + this.fVec5[((this.IOTA - 211) & 511)])));
			this.fVbargraph2 = this.fRec2[0];
			output2[i] = this.fVbargraph2;
			var fTemp6 = (this.fVec0[((this.IOTA - 256) & 511)] + this.fVec1[((this.IOTA - 249) & 511)]);
			var fTemp7 = (fTemp6 + this.fVec2[((this.IOTA - 241) & 511)]);
			this.fRec3[0] = max_f((this.fRec3[1] - this.fConst0), Math.abs((((fTemp7 + this.fVec3[((this.IOTA - 233) & 511)]) + this.fVec4[((this.IOTA - 225) & 511)]) + this.fVec5[((this.IOTA - 217) & 511)])));
			this.fVbargraph3 = this.fRec3[0];
			output3[i] = this.fVbargraph3;
			var fTemp8 = (this.fVec0[((this.IOTA - 256) & 511)] + this.fVec1[((this.IOTA - 250) & 511)]);
			this.fRec4[0] = max_f((this.fRec4[1] - this.fConst0), Math.abs(((((fTemp8 + this.fVec2[((this.IOTA - 243) & 511)]) + this.fVec3[((this.IOTA - 236) & 511)]) + this.fVec4[((this.IOTA - 229) & 511)]) + this.fVec5[((this.IOTA - 222) & 511)])));
			this.fVbargraph4 = this.fRec4[0];
			output4[i] = this.fVbargraph4;
			this.fRec5[0] = max_f((this.fRec5[1] - this.fConst0), Math.abs(((((fTemp8 + this.fVec2[((this.IOTA - 245) & 511)]) + this.fVec3[((this.IOTA - 239) & 511)]) + this.fVec4[((this.IOTA - 232) & 511)]) + this.fVec5[((this.IOTA - 225) & 511)])));
			this.fVbargraph5 = this.fRec5[0];
			output5[i] = this.fVbargraph5;
			this.fRec6[0] = max_f((this.fRec6[1] - this.fConst0), Math.abs(((((fTemp5 + this.fVec2[((this.IOTA - 235) & 511)]) + this.fVec3[((this.IOTA - 224) & 511)]) + this.fVec4[((this.IOTA - 213) & 511)]) + this.fVec5[((this.IOTA - 201) & 511)])));
			this.fVbargraph6 = this.fRec6[0];
			output6[i] = this.fVbargraph6;
			this.fRec7[0] = max_f((this.fRec7[1] - this.fConst0), Math.abs((this.fVec4[((this.IOTA - 221) & 511)] + (this.fVec1[((this.IOTA - 248) & 511)] + (this.fVec5[((this.IOTA - 211) & 511)] + (this.fVec3[((this.IOTA - 230) & 511)] + (this.fVec0[((this.IOTA - 256) & 511)] + this.fVec2[((this.IOTA - 239) & 511)])))))));
			this.fVbargraph7 = this.fRec7[0];
			output7[i] = this.fVbargraph7;
			this.fRec8[0] = max_f((this.fRec8[1] - this.fConst0), Math.abs(((((fTemp6 + this.fVec2[((this.IOTA - 243) & 511)]) + this.fVec3[((this.IOTA - 235) & 511)]) + this.fVec4[((this.IOTA - 227) & 511)]) + this.fVec5[((this.IOTA - 219) & 511)])));
			this.fVbargraph8 = this.fRec8[0];
			output8[i] = this.fVbargraph8;
			this.fRec9[0] = max_f((this.fRec9[1] - this.fConst0), Math.abs((this.fVec1[((this.IOTA - 251) & 511)] + (this.fVec5[((this.IOTA - 225) & 511)] + (this.fVec4[((this.IOTA - 232) & 511)] + (this.fVec3[((this.IOTA - 239) & 511)] + (this.fVec0[((this.IOTA - 256) & 511)] + this.fVec2[((this.IOTA - 245) & 511)])))))));
			this.fVbargraph9 = this.fRec9[0];
			output9[i] = this.fVbargraph9;
			this.fRec10[0] = max_f((this.fRec10[1] - this.fConst0), Math.abs((((((this.fVec0[((this.IOTA - 256) & 511)] + this.fVec1[((this.IOTA - 251) & 511)]) + this.fVec2[((this.IOTA - 247) & 511)]) + this.fVec3[((this.IOTA - 241) & 511)]) + this.fVec4[((this.IOTA - 236) & 511)]) + this.fVec5[((this.IOTA - 230) & 511)])));
			this.fVbargraph10 = this.fRec10[0];
			output10[i] = this.fVbargraph10;
			var fTemp9 = ((this.fVec0[((this.IOTA - 256) & 511)] + this.fVec1[((this.IOTA - 252) & 511)]) + this.fVec2[((this.IOTA - 248) & 511)]);
			this.fRec11[0] = max_f((this.fRec11[1] - this.fConst0), Math.abs((((fTemp9 + this.fVec3[((this.IOTA - 243) & 511)]) + this.fVec4[((this.IOTA - 238) & 511)]) + this.fVec5[((this.IOTA - 233) & 511)])));
			this.fVbargraph11 = this.fRec11[0];
			output11[i] = this.fVbargraph11;
			this.fRec12[0] = max_f((this.fRec12[1] - this.fConst0), Math.abs((((fTemp7 + this.fVec3[((this.IOTA - 232) & 511)]) + this.fVec4[((this.IOTA - 223) & 511)]) + this.fVec5[((this.IOTA - 212) & 511)])));
			this.fVbargraph12 = this.fRec12[0];
			output12[i] = this.fVbargraph12;
			this.fRec13[0] = max_f((this.fRec13[1] - this.fConst0), Math.abs((this.fVec5[((this.IOTA - 224) & 511)] + (this.fVec3[((this.IOTA - 240) & 511)] + (this.fVec2[((this.IOTA - 246) & 511)] + (this.fVec1[((this.IOTA - 251) & 511)] + (this.fVec0[((this.IOTA - 256) & 511)] + this.fVec4[((this.IOTA - 232) & 511)])))))));
			this.fVbargraph13 = this.fRec13[0];
			output13[i] = this.fVbargraph13;
			this.fRec14[0] = max_f((this.fRec14[1] - this.fConst0), Math.abs((this.fVec5[((this.IOTA - 231) & 511)] + (this.fVec3[((this.IOTA - 244) & 511)] + (fTemp9 + this.fVec4[((this.IOTA - 238) & 511)])))));
			this.fVbargraph14 = this.fRec14[0];
			output14[i] = this.fVbargraph14;
			this.fRec15[0] = max_f((this.fRec15[1] - this.fConst0), Math.abs((((((this.fVec0[((this.IOTA - 256) & 511)] + this.fVec1[((this.IOTA - 253) & 511)]) + this.fVec2[((this.IOTA - 250) & 511)]) + this.fVec3[((this.IOTA - 246) & 511)]) + this.fVec4[((this.IOTA - 241) & 511)]) + this.fVec5[((this.IOTA - 236) & 511)])));
			this.fVbargraph15 = this.fRec15[0];
			output15[i] = this.fVbargraph15;
			var fTemp10 = (this.fVec0[((this.IOTA - 256) & 511)] + this.fVec1[((this.IOTA - 254) & 511)]);
			this.fRec16[0] = max_f((this.fRec16[1] - this.fConst0), Math.abs(((((fTemp10 + this.fVec2[((this.IOTA - 251) & 511)]) + this.fVec3[((this.IOTA - 248) & 511)]) + this.fVec4[((this.IOTA - 244) & 511)]) + this.fVec5[((this.IOTA - 239) & 511)])));
			this.fVbargraph16 = this.fRec16[0];
			output16[i] = this.fVbargraph16;
			this.fRec17[0] = max_f((this.fRec17[1] - this.fConst0), Math.abs(((((fTemp10 + this.fVec2[((this.IOTA - 252) & 511)]) + this.fVec3[((this.IOTA - 249) & 511)]) + this.fVec4[((this.IOTA - 245) & 511)]) + this.fVec5[((this.IOTA - 242) & 511)])));
			this.fVbargraph17 = this.fRec17[0];
			output17[i] = this.fVbargraph17;
			this.fRec18[0] = max_f((this.fRec18[1] - this.fConst0), Math.abs((this.fVec4[((this.IOTA - 246) & 511)] + (this.fVec3[((this.IOTA - 252) & 511)] + (this.fVec2[((this.IOTA - 256) & 511)] + (this.fVec1[((this.IOTA - 257) & 511)] + (this.fVec0[((this.IOTA - 256) & 511)] + this.fVec5[((this.IOTA - 239) & 511)])))))));
			this.fVbargraph18 = this.fRec18[0];
			output18[i] = this.fVbargraph18;
			var fTemp11 = (this.fVec1[((this.IOTA - 256) & 511)] + (this.fVec0[((this.IOTA - 256) & 511)] + this.fVec2[((this.IOTA - 256) & 511)]));
			this.fRec19[0] = max_f((this.fRec19[1] - this.fConst0), Math.abs((this.fVec5[((this.IOTA - 245) & 511)] + (this.fVec4[((this.IOTA - 250) & 511)] + (this.fVec3[((this.IOTA - 253) & 511)] + fTemp11)))));
			this.fVbargraph19 = this.fRec19[0];
			output19[i] = this.fVbargraph19;
			var fTemp12 = (fTemp11 + this.fVec3[((this.IOTA - 254) & 511)]);
			this.fRec20[0] = max_f((this.fRec20[1] - this.fConst0), Math.abs(((fTemp12 + this.fVec4[((this.IOTA - 251) & 511)]) + this.fVec5[((this.IOTA - 247) & 511)])));
			this.fVbargraph20 = this.fRec20[0];
			output20[i] = this.fVbargraph20;
			this.fRec21[0] = max_f((this.fRec21[1] - this.fConst0), Math.abs(((fTemp12 + this.fVec4[((this.IOTA - 252) & 511)]) + this.fVec5[((this.IOTA - 249) & 511)])));
			this.fVbargraph21 = this.fRec21[0];
			output21[i] = this.fVbargraph21;
			this.fRec22[0] = max_f((this.fRec22[1] - this.fConst0), Math.abs(((fTemp12 + this.fVec4[((this.IOTA - 253) & 511)]) + this.fVec5[((this.IOTA - 250) & 511)])));
			this.fVbargraph22 = this.fRec22[0];
			output22[i] = this.fVbargraph22;
			this.fRec23[0] = max_f((this.fRec23[1] - this.fConst0), Math.abs((this.fVec5[((this.IOTA - 251) & 511)] + (this.fVec3[((this.IOTA - 255) & 511)] + (fTemp11 + this.fVec4[((this.IOTA - 253) & 511)])))));
			this.fVbargraph23 = this.fRec23[0];
			output23[i] = this.fVbargraph23;
			this.fRec24[0] = max_f((this.fRec24[1] - this.fConst0), Math.abs((((((this.fVec0[((this.IOTA - 256) & 511)] + this.fVec1[((this.IOTA - 263) & 511)]) + this.fVec2[((this.IOTA - 270) & 511)]) + this.fVec3[((this.IOTA - 274) & 511)]) + this.fVec4[((this.IOTA - 276) & 511)]) + this.fVec5[((this.IOTA - 276) & 511)])));
			this.fVbargraph24 = this.fRec24[0];
			output24[i] = this.fVbargraph24;
			this.fRec25[0] = max_f((this.fRec25[1] - this.fConst0), Math.abs((((((this.fVec0[((this.IOTA - 256) & 511)] + this.fVec1[((this.IOTA - 261) & 511)]) + this.fVec2[((this.IOTA - 265) & 511)]) + this.fVec3[((this.IOTA - 268) & 511)]) + this.fVec4[((this.IOTA - 269) & 511)]) + this.fVec5[((this.IOTA - 269) & 511)])));
			this.fVbargraph25 = this.fRec25[0];
			output25[i] = this.fVbargraph25;
			var fTemp13 = ((this.fVec0[((this.IOTA - 256) & 511)] + this.fVec1[((this.IOTA - 260) & 511)]) + this.fVec2[((this.IOTA - 263) & 511)]);
			this.fRec26[0] = max_f((this.fRec26[1] - this.fConst0), Math.abs((((fTemp13 + this.fVec3[((this.IOTA - 265) & 511)]) + this.fVec4[((this.IOTA - 265) & 511)]) + this.fVec5[((this.IOTA - 265) & 511)])));
			this.fVbargraph26 = this.fRec26[0];
			output26[i] = this.fVbargraph26;
			this.fRec27[0] = max_f((this.fRec27[1] - this.fConst0), Math.abs((((((this.fVec0[((this.IOTA - 256) & 511)] + this.fVec1[((this.IOTA - 259) & 511)]) + this.fVec2[((this.IOTA - 261) & 511)]) + this.fVec3[((this.IOTA - 263) & 511)]) + this.fVec4[((this.IOTA - 263) & 511)]) + this.fVec5[((this.IOTA - 263) & 511)])));
			this.fVbargraph27 = this.fRec27[0];
			output27[i] = this.fVbargraph27;
			var fTemp14 = (this.fVec0[((this.IOTA - 256) & 511)] + this.fVec1[((this.IOTA - 258) & 511)]);
			this.fRec28[0] = max_f((this.fRec28[1] - this.fConst0), Math.abs(((((fTemp14 + this.fVec2[((this.IOTA - 260) & 511)]) + this.fVec3[((this.IOTA - 261) & 511)]) + this.fVec4[((this.IOTA - 262) & 511)]) + this.fVec5[((this.IOTA - 262) & 511)])));
			this.fVbargraph28 = this.fRec28[0];
			output28[i] = this.fVbargraph28;
			this.fRec29[0] = max_f((this.fRec29[1] - this.fConst0), Math.abs(((((fTemp14 + this.fVec2[((this.IOTA - 259) & 511)]) + this.fVec3[((this.IOTA - 260) & 511)]) + this.fVec4[((this.IOTA - 261) & 511)]) + this.fVec5[((this.IOTA - 261) & 511)])));
			this.fVbargraph29 = this.fRec29[0];
			output29[i] = this.fVbargraph29;
			this.fRec30[0] = max_f((this.fRec30[1] - this.fConst0), Math.abs((((((this.fVec0[((this.IOTA - 256) & 511)] + this.fVec1[((this.IOTA - 266) & 511)]) + this.fVec2[((this.IOTA - 276) & 511)]) + this.fVec3[((this.IOTA - 285) & 511)]) + this.fVec4[((this.IOTA - 293) & 511)]) + this.fVec5[((this.IOTA - 300) & 511)])));
			this.fVbargraph30 = this.fRec30[0];
			output30[i] = this.fVbargraph30;
			this.fRec31[0] = max_f((this.fRec31[1] - this.fConst0), Math.abs((((((this.fVec0[((this.IOTA - 256) & 511)] + this.fVec1[((this.IOTA - 264) & 511)]) + this.fVec2[((this.IOTA - 272) & 511)]) + this.fVec3[((this.IOTA - 278) & 511)]) + this.fVec4[((this.IOTA - 284) & 511)]) + this.fVec5[((this.IOTA - 289) & 511)])));
			this.fVbargraph31 = this.fRec31[0];
			output31[i] = this.fVbargraph31;
			this.fRec32[0] = max_f((this.fRec32[1] - this.fConst0), Math.abs((((((this.fVec0[((this.IOTA - 256) & 511)] + this.fVec1[((this.IOTA - 262) & 511)]) + this.fVec2[((this.IOTA - 268) & 511)]) + this.fVec3[((this.IOTA - 273) & 511)]) + this.fVec4[((this.IOTA - 278) & 511)]) + this.fVec5[((this.IOTA - 281) & 511)])));
			this.fVbargraph32 = this.fRec32[0];
			output32[i] = this.fVbargraph32;
			this.fRec33[0] = max_f((this.fRec33[1] - this.fConst0), Math.abs((this.fVec4[((this.IOTA - 274) & 511)] + (this.fVec3[((this.IOTA - 270) & 511)] + (this.fVec2[((this.IOTA - 266) & 511)] + (this.fVec1[((this.IOTA - 261) & 511)] + (this.fVec0[((this.IOTA - 256) & 511)] + this.fVec5[((this.IOTA - 276) & 511)])))))));
			this.fVbargraph33 = this.fRec33[0];
			output33[i] = this.fVbargraph33;
			this.fRec34[0] = max_f((this.fRec34[1] - this.fConst0), Math.abs((((this.fVec2[((this.IOTA - 264) & 511)] + (this.fVec1[((this.IOTA - 260) & 511)] + (this.fVec0[((this.IOTA - 256) & 511)] + this.fVec3[((this.IOTA - 268) & 511)]))) + this.fVec4[((this.IOTA - 271) & 511)]) + this.fVec5[((this.IOTA - 273) & 511)])));
			this.fVbargraph34 = this.fRec34[0];
			output34[i] = this.fVbargraph34;
			this.fRec35[0] = max_f((this.fRec35[1] - this.fConst0), Math.abs((((fTemp13 + this.fVec3[((this.IOTA - 266) & 511)]) + this.fVec4[((this.IOTA - 268) & 511)]) + this.fVec5[((this.IOTA - 270) & 511)])));
			this.fVbargraph35 = this.fRec35[0];
			output35[i] = this.fVbargraph35;
			this.IOTA = (this.IOTA + 1);
			this.fRec0[1] = this.fRec0[0];
			this.fRec1[1] = this.fRec1[0];
			this.fRec2[1] = this.fRec2[0];
			this.fRec3[1] = this.fRec3[0];
			this.fRec4[1] = this.fRec4[0];
			this.fRec5[1] = this.fRec5[0];
			this.fRec6[1] = this.fRec6[0];
			this.fRec7[1] = this.fRec7[0];
			this.fRec8[1] = this.fRec8[0];
			this.fRec9[1] = this.fRec9[0];
			this.fRec10[1] = this.fRec10[0];
			this.fRec11[1] = this.fRec11[0];
			this.fRec12[1] = this.fRec12[0];
			this.fRec13[1] = this.fRec13[0];
			this.fRec14[1] = this.fRec14[0];
			this.fRec15[1] = this.fRec15[0];
			this.fRec16[1] = this.fRec16[0];
			this.fRec17[1] = this.fRec17[0];
			this.fRec18[1] = this.fRec18[0];
			this.fRec19[1] = this.fRec19[0];
			this.fRec20[1] = this.fRec20[0];
			this.fRec21[1] = this.fRec21[0];
			this.fRec22[1] = this.fRec22[0];
			this.fRec23[1] = this.fRec23[0];
			this.fRec24[1] = this.fRec24[0];
			this.fRec25[1] = this.fRec25[0];
			this.fRec26[1] = this.fRec26[0];
			this.fRec27[1] = this.fRec27[0];
			this.fRec28[1] = this.fRec28[0];
			this.fRec29[1] = this.fRec29[0];
			this.fRec30[1] = this.fRec30[0];
			this.fRec31[1] = this.fRec31[0];
			this.fRec32[1] = this.fRec32[0];
			this.fRec33[1] = this.fRec33[0];
			this.fRec34[1] = this.fRec34[0];
			this.fRec35[1] = this.fRec35[0];
			
		}
		
	}
	
}

