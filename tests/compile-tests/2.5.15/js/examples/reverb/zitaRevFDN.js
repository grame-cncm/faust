
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.mydsp_faustpower2_f = function(value) {
	return (value * value);
	
}

function mydsp() {
	
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fConst2;
	this.fVslider0;
	this.fConst3;
	this.fVslider1;
	this.fVslider2;
	this.fConst4;
	this.fVslider3;
	this.fRec11 = new Float32Array(2);
	this.fRec10 = new Float32Array(2);
	this.IOTA;
	this.fVec0 = new Float32Array(32768);
	this.fConst5;
	this.iConst6;
	this.fVec1 = new Float32Array(2048);
	this.iConst7;
	this.fRec8 = new Float32Array(2);
	this.fConst8;
	this.fConst9;
	this.fRec15 = new Float32Array(2);
	this.fRec14 = new Float32Array(2);
	this.fVec2 = new Float32Array(32768);
	this.fConst10;
	this.iConst11;
	this.fVec3 = new Float32Array(4096);
	this.iConst12;
	this.fRec12 = new Float32Array(2);
	this.fConst13;
	this.fConst14;
	this.fRec19 = new Float32Array(2);
	this.fRec18 = new Float32Array(2);
	this.fVec4 = new Float32Array(16384);
	this.fConst15;
	this.iConst16;
	this.fVec5 = new Float32Array(4096);
	this.iConst17;
	this.fRec16 = new Float32Array(2);
	this.fConst18;
	this.fConst19;
	this.fRec23 = new Float32Array(2);
	this.fRec22 = new Float32Array(2);
	this.fVec6 = new Float32Array(32768);
	this.fConst20;
	this.iConst21;
	this.fVec7 = new Float32Array(4096);
	this.iConst22;
	this.fRec20 = new Float32Array(2);
	this.fConst23;
	this.fConst24;
	this.fRec27 = new Float32Array(2);
	this.fRec26 = new Float32Array(2);
	this.fVec8 = new Float32Array(16384);
	this.fConst25;
	this.iConst26;
	this.fVec9 = new Float32Array(2048);
	this.iConst27;
	this.fRec24 = new Float32Array(2);
	this.fConst28;
	this.fConst29;
	this.fRec31 = new Float32Array(2);
	this.fRec30 = new Float32Array(2);
	this.fVec10 = new Float32Array(16384);
	this.fConst30;
	this.iConst31;
	this.fVec11 = new Float32Array(4096);
	this.iConst32;
	this.fRec28 = new Float32Array(2);
	this.fConst33;
	this.fConst34;
	this.fRec35 = new Float32Array(2);
	this.fRec34 = new Float32Array(2);
	this.fVec12 = new Float32Array(16384);
	this.fConst35;
	this.iConst36;
	this.fVec13 = new Float32Array(4096);
	this.iConst37;
	this.fRec32 = new Float32Array(2);
	this.fConst38;
	this.fConst39;
	this.fRec39 = new Float32Array(2);
	this.fRec38 = new Float32Array(2);
	this.fVec14 = new Float32Array(16384);
	this.fConst40;
	this.iConst41;
	this.fVec15 = new Float32Array(2048);
	this.iConst42;
	this.fRec36 = new Float32Array(2);
	this.fRec0 = new Float32Array(3);
	this.fRec1 = new Float32Array(3);
	this.fRec2 = new Float32Array(3);
	this.fRec3 = new Float32Array(3);
	this.fRec4 = new Float32Array(3);
	this.fRec5 = new Float32Array(3);
	this.fRec6 = new Float32Array(3);
	this.fRec7 = new Float32Array(3);
	
	this.metadata = function(m) { 
		m.declare("author", "JOS, Revised by RM");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("description", "Reverb demo application based on `zita_rev_fdn`.");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "zitaRevFDN");
		m.declare("reverbs.lib/name", "Faust Reverb Library");
		m.declare("reverbs.lib/version", "0.0");
		m.declare("routes.lib/name", "Faust Signal Routing Library");
		m.declare("routes.lib/version", "0.0");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
		m.declare("version", "0.0");
	}

	this.getNumInputs = function() {
		return 8;
		
	}
	this.getNumOutputs = function() {
		return 8;
		
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
			case 6: {
				rate = 1;
				break;
			}
			case 7: {
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
		this.fConst1 = Math.floor(((0.219991 * this.fConst0) + 0.5));
		this.fConst2 = ((0 - (6.90776 * this.fConst1)) / this.fConst0);
		this.fConst3 = (6.28319 / this.fConst0);
		this.fConst4 = (3.14159 / this.fConst0);
		this.fConst5 = Math.floor(((0.019123 * this.fConst0) + 0.5));
		this.iConst6 = min_f(16384, max_f(0, (this.fConst1 - this.fConst5)));
		this.iConst7 = min_f(1024, max_f(0, (this.fConst5 + -1)));
		this.fConst8 = Math.floor(((0.256891 * this.fConst0) + 0.5));
		this.fConst9 = ((0 - (6.90776 * this.fConst8)) / this.fConst0);
		this.fConst10 = Math.floor(((0.027333 * this.fConst0) + 0.5));
		this.iConst11 = min_f(16384, max_f(0, (this.fConst8 - this.fConst10)));
		this.iConst12 = min_f(2048, max_f(0, (this.fConst10 + -1)));
		this.fConst13 = Math.floor(((0.192303 * this.fConst0) + 0.5));
		this.fConst14 = ((0 - (6.90776 * this.fConst13)) / this.fConst0);
		this.fConst15 = Math.floor(((0.029291 * this.fConst0) + 0.5));
		this.iConst16 = min_f(8192, max_f(0, (this.fConst13 - this.fConst15)));
		this.iConst17 = min_f(2048, max_f(0, (this.fConst15 + -1)));
		this.fConst18 = Math.floor(((0.210389 * this.fConst0) + 0.5));
		this.fConst19 = ((0 - (6.90776 * this.fConst18)) / this.fConst0);
		this.fConst20 = Math.floor(((0.024421 * this.fConst0) + 0.5));
		this.iConst21 = min_f(16384, max_f(0, (this.fConst18 - this.fConst20)));
		this.iConst22 = min_f(2048, max_f(0, (this.fConst20 + -1)));
		this.fConst23 = Math.floor(((0.125 * this.fConst0) + 0.5));
		this.fConst24 = ((0 - (6.90776 * this.fConst23)) / this.fConst0);
		this.fConst25 = Math.floor(((0.013458 * this.fConst0) + 0.5));
		this.iConst26 = min_f(8192, max_f(0, (this.fConst23 - this.fConst25)));
		this.iConst27 = min_f(1024, max_f(0, (this.fConst25 + -1)));
		this.fConst28 = Math.floor(((0.127837 * this.fConst0) + 0.5));
		this.fConst29 = ((0 - (6.90776 * this.fConst28)) / this.fConst0);
		this.fConst30 = Math.floor(((0.031604 * this.fConst0) + 0.5));
		this.iConst31 = min_f(8192, max_f(0, (this.fConst28 - this.fConst30)));
		this.iConst32 = min_f(2048, max_f(0, (this.fConst30 + -1)));
		this.fConst33 = Math.floor(((0.174713 * this.fConst0) + 0.5));
		this.fConst34 = ((0 - (6.90776 * this.fConst33)) / this.fConst0);
		this.fConst35 = Math.floor(((0.022904 * this.fConst0) + 0.5));
		this.iConst36 = min_f(8192, max_f(0, (this.fConst33 - this.fConst35)));
		this.iConst37 = min_f(2048, max_f(0, (this.fConst35 + -1)));
		this.fConst38 = Math.floor(((0.153129 * this.fConst0) + 0.5));
		this.fConst39 = ((0 - (6.90776 * this.fConst38)) / this.fConst0);
		this.fConst40 = Math.floor(((0.020346 * this.fConst0) + 0.5));
		this.iConst41 = min_f(8192, max_f(0, (this.fConst38 - this.fConst40)));
		this.iConst42 = min_f(1024, max_f(0, (this.fConst40 + -1)));
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fVslider0 = 2;
		this.fVslider1 = 6000;
		this.fVslider2 = 3;
		this.fVslider3 = 200;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.fRec11[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec10[l1] = 0;
			
		}
		this.IOTA = 0;
		for (var l2 = 0; (l2 < 32768); l2 = (l2 + 1)) {
			this.fVec0[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2048); l3 = (l3 + 1)) {
			this.fVec1[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec8[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fRec15[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			this.fRec14[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 32768); l7 = (l7 + 1)) {
			this.fVec2[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 4096); l8 = (l8 + 1)) {
			this.fVec3[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			this.fRec12[l9] = 0;
			
		}
		for (var l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			this.fRec19[l10] = 0;
			
		}
		for (var l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			this.fRec18[l11] = 0;
			
		}
		for (var l12 = 0; (l12 < 16384); l12 = (l12 + 1)) {
			this.fVec4[l12] = 0;
			
		}
		for (var l13 = 0; (l13 < 4096); l13 = (l13 + 1)) {
			this.fVec5[l13] = 0;
			
		}
		for (var l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			this.fRec16[l14] = 0;
			
		}
		for (var l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			this.fRec23[l15] = 0;
			
		}
		for (var l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			this.fRec22[l16] = 0;
			
		}
		for (var l17 = 0; (l17 < 32768); l17 = (l17 + 1)) {
			this.fVec6[l17] = 0;
			
		}
		for (var l18 = 0; (l18 < 4096); l18 = (l18 + 1)) {
			this.fVec7[l18] = 0;
			
		}
		for (var l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			this.fRec20[l19] = 0;
			
		}
		for (var l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			this.fRec27[l20] = 0;
			
		}
		for (var l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			this.fRec26[l21] = 0;
			
		}
		for (var l22 = 0; (l22 < 16384); l22 = (l22 + 1)) {
			this.fVec8[l22] = 0;
			
		}
		for (var l23 = 0; (l23 < 2048); l23 = (l23 + 1)) {
			this.fVec9[l23] = 0;
			
		}
		for (var l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			this.fRec24[l24] = 0;
			
		}
		for (var l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			this.fRec31[l25] = 0;
			
		}
		for (var l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			this.fRec30[l26] = 0;
			
		}
		for (var l27 = 0; (l27 < 16384); l27 = (l27 + 1)) {
			this.fVec10[l27] = 0;
			
		}
		for (var l28 = 0; (l28 < 4096); l28 = (l28 + 1)) {
			this.fVec11[l28] = 0;
			
		}
		for (var l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			this.fRec28[l29] = 0;
			
		}
		for (var l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			this.fRec35[l30] = 0;
			
		}
		for (var l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			this.fRec34[l31] = 0;
			
		}
		for (var l32 = 0; (l32 < 16384); l32 = (l32 + 1)) {
			this.fVec12[l32] = 0;
			
		}
		for (var l33 = 0; (l33 < 4096); l33 = (l33 + 1)) {
			this.fVec13[l33] = 0;
			
		}
		for (var l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			this.fRec32[l34] = 0;
			
		}
		for (var l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			this.fRec39[l35] = 0;
			
		}
		for (var l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			this.fRec38[l36] = 0;
			
		}
		for (var l37 = 0; (l37 < 16384); l37 = (l37 + 1)) {
			this.fVec14[l37] = 0;
			
		}
		for (var l38 = 0; (l38 < 2048); l38 = (l38 + 1)) {
			this.fVec15[l38] = 0;
			
		}
		for (var l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			this.fRec36[l39] = 0;
			
		}
		for (var l40 = 0; (l40 < 3); l40 = (l40 + 1)) {
			this.fRec0[l40] = 0;
			
		}
		for (var l41 = 0; (l41 < 3); l41 = (l41 + 1)) {
			this.fRec1[l41] = 0;
			
		}
		for (var l42 = 0; (l42 < 3); l42 = (l42 + 1)) {
			this.fRec2[l42] = 0;
			
		}
		for (var l43 = 0; (l43 < 3); l43 = (l43 + 1)) {
			this.fRec3[l43] = 0;
			
		}
		for (var l44 = 0; (l44 < 3); l44 = (l44 + 1)) {
			this.fRec4[l44] = 0;
			
		}
		for (var l45 = 0; (l45 < 3); l45 = (l45 + 1)) {
			this.fRec5[l45] = 0;
			
		}
		for (var l46 = 0; (l46 < 3); l46 = (l46 + 1)) {
			this.fRec6[l46] = 0;
			
		}
		for (var l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			this.fRec7[l47] = 0;
			
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
		ui_interface.declare("0", "tooltip", "~ Zita_Rev's internal   8x8 Feedback Delay Network (FDN) & Schroeder allpass-comb reverberator.  See   Faust's reverbs.lib for documentation and references");
		ui_interface.openHorizontalBox("Zita_Rev Internal FDN Reverb");
		ui_interface.declare("fVslider2", "1", "");
		ui_interface.declare("fVslider2", "style", "knob");
		ui_interface.declare("fVslider2", "tooltip", "T60 = time (in seconds) to decay 60dB in low-frequency band");
		ui_interface.declare("fVslider2", "unit", "s");
		ui_interface.addVerticalSlider("Low RT60", function handler(obj) { function setval(val) { obj.fVslider2 = val; } return setval; }(this), 3, 1, 8, 0.1);
		ui_interface.declare("fVslider3", "2", "");
		ui_interface.declare("fVslider3", "scale", "log");
		ui_interface.declare("fVslider3", "style", "knob");
		ui_interface.declare("fVslider3", "tooltip", "Crossover frequency (Hz) separating low and middle frequencies");
		ui_interface.declare("fVslider3", "unit", "Hz");
		ui_interface.addVerticalSlider("LF X", function handler(obj) { function setval(val) { obj.fVslider3 = val; } return setval; }(this), 200, 50, 1000, 1);
		ui_interface.declare("fVslider0", "3", "");
		ui_interface.declare("fVslider0", "scale", "log");
		ui_interface.declare("fVslider0", "style", "knob");
		ui_interface.declare("fVslider0", "tooltip", "T60 = time (in seconds) to decay 60dB in middle band");
		ui_interface.declare("fVslider0", "unit", "s");
		ui_interface.addVerticalSlider("Mid RT60", function handler(obj) { function setval(val) { obj.fVslider0 = val; } return setval; }(this), 2, 1, 8, 0.1);
		ui_interface.declare("fVslider1", "4", "");
		ui_interface.declare("fVslider1", "scale", "log");
		ui_interface.declare("fVslider1", "style", "knob");
		ui_interface.declare("fVslider1", "tooltip", "Frequency (Hz) at which the high-frequency T60 is half the middle-band's T60");
		ui_interface.declare("fVslider1", "unit", "Hz");
		ui_interface.addVerticalSlider("HF Damping", function handler(obj) { function setval(val) { obj.fVslider1 = val; } return setval; }(this), 6000, 1500, 23520, 1);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var input1 = inputs[1];
		var input2 = inputs[2];
		var input3 = inputs[3];
		var input4 = inputs[4];
		var input5 = inputs[5];
		var input6 = inputs[6];
		var input7 = inputs[7];
		var output0 = outputs[0];
		var output1 = outputs[1];
		var output2 = outputs[2];
		var output3 = outputs[3];
		var output4 = outputs[4];
		var output5 = outputs[5];
		var output6 = outputs[6];
		var output7 = outputs[7];
		var fSlow0 = this.fVslider0;
		var fSlow1 = Math.exp((this.fConst2 / fSlow0));
		var fSlow2 = mydsp_faustpower2_f(fSlow1);
		var fSlow3 = Math.cos((this.fConst3 * this.fVslider1));
		var fSlow4 = (1 - (fSlow2 * fSlow3));
		var fSlow5 = (1 - fSlow2);
		var fSlow6 = (fSlow4 / fSlow5);
		var fSlow7 = Math.sqrt(max_f(0, ((mydsp_faustpower2_f(fSlow4) / mydsp_faustpower2_f(fSlow5)) + -1)));
		var fSlow8 = (fSlow6 - fSlow7);
		var fSlow9 = (fSlow1 * (fSlow7 + (1 - fSlow6)));
		var fSlow10 = this.fVslider2;
		var fSlow11 = ((Math.exp((this.fConst2 / fSlow10)) / fSlow1) + -1);
		var fSlow12 = (1 / Math.tan((this.fConst4 * this.fVslider3)));
		var fSlow13 = (fSlow12 + 1);
		var fSlow14 = (0 - ((1 - fSlow12) / fSlow13));
		var fSlow15 = (1 / fSlow13);
		var fSlow16 = Math.exp((this.fConst9 / fSlow0));
		var fSlow17 = mydsp_faustpower2_f(fSlow16);
		var fSlow18 = (1 - (fSlow3 * fSlow17));
		var fSlow19 = (1 - fSlow17);
		var fSlow20 = (fSlow18 / fSlow19);
		var fSlow21 = Math.sqrt(max_f(0, ((mydsp_faustpower2_f(fSlow18) / mydsp_faustpower2_f(fSlow19)) + -1)));
		var fSlow22 = (fSlow20 - fSlow21);
		var fSlow23 = (fSlow16 * (fSlow21 + (1 - fSlow20)));
		var fSlow24 = ((Math.exp((this.fConst9 / fSlow10)) / fSlow16) + -1);
		var fSlow25 = Math.exp((this.fConst14 / fSlow0));
		var fSlow26 = mydsp_faustpower2_f(fSlow25);
		var fSlow27 = (1 - (fSlow3 * fSlow26));
		var fSlow28 = (1 - fSlow26);
		var fSlow29 = (fSlow27 / fSlow28);
		var fSlow30 = Math.sqrt(max_f(0, ((mydsp_faustpower2_f(fSlow27) / mydsp_faustpower2_f(fSlow28)) + -1)));
		var fSlow31 = (fSlow29 - fSlow30);
		var fSlow32 = (fSlow25 * (fSlow30 + (1 - fSlow29)));
		var fSlow33 = ((Math.exp((this.fConst14 / fSlow10)) / fSlow25) + -1);
		var fSlow34 = Math.exp((this.fConst19 / fSlow0));
		var fSlow35 = mydsp_faustpower2_f(fSlow34);
		var fSlow36 = (1 - (fSlow3 * fSlow35));
		var fSlow37 = (1 - fSlow35);
		var fSlow38 = (fSlow36 / fSlow37);
		var fSlow39 = Math.sqrt(max_f(0, ((mydsp_faustpower2_f(fSlow36) / mydsp_faustpower2_f(fSlow37)) + -1)));
		var fSlow40 = (fSlow38 - fSlow39);
		var fSlow41 = (fSlow34 * (fSlow39 + (1 - fSlow38)));
		var fSlow42 = ((Math.exp((this.fConst19 / fSlow10)) / fSlow34) + -1);
		var fSlow43 = Math.exp((this.fConst24 / fSlow0));
		var fSlow44 = mydsp_faustpower2_f(fSlow43);
		var fSlow45 = (1 - (fSlow3 * fSlow44));
		var fSlow46 = (1 - fSlow44);
		var fSlow47 = (fSlow45 / fSlow46);
		var fSlow48 = Math.sqrt(max_f(0, ((mydsp_faustpower2_f(fSlow45) / mydsp_faustpower2_f(fSlow46)) + -1)));
		var fSlow49 = (fSlow47 - fSlow48);
		var fSlow50 = (fSlow43 * (fSlow48 + (1 - fSlow47)));
		var fSlow51 = ((Math.exp((this.fConst24 / fSlow10)) / fSlow43) + -1);
		var fSlow52 = Math.exp((this.fConst29 / fSlow0));
		var fSlow53 = mydsp_faustpower2_f(fSlow52);
		var fSlow54 = (1 - (fSlow3 * fSlow53));
		var fSlow55 = (1 - fSlow53);
		var fSlow56 = (fSlow54 / fSlow55);
		var fSlow57 = Math.sqrt(max_f(0, ((mydsp_faustpower2_f(fSlow54) / mydsp_faustpower2_f(fSlow55)) + -1)));
		var fSlow58 = (fSlow56 - fSlow57);
		var fSlow59 = (fSlow52 * (fSlow57 + (1 - fSlow56)));
		var fSlow60 = ((Math.exp((this.fConst29 / fSlow10)) / fSlow52) + -1);
		var fSlow61 = Math.exp((this.fConst34 / fSlow0));
		var fSlow62 = mydsp_faustpower2_f(fSlow61);
		var fSlow63 = (1 - (fSlow3 * fSlow62));
		var fSlow64 = (1 - fSlow62);
		var fSlow65 = (fSlow63 / fSlow64);
		var fSlow66 = Math.sqrt(max_f(0, ((mydsp_faustpower2_f(fSlow63) / mydsp_faustpower2_f(fSlow64)) + -1)));
		var fSlow67 = (fSlow65 - fSlow66);
		var fSlow68 = (fSlow61 * (fSlow66 + (1 - fSlow65)));
		var fSlow69 = ((Math.exp((this.fConst34 / fSlow10)) / fSlow61) + -1);
		var fSlow70 = Math.exp((this.fConst39 / fSlow0));
		var fSlow71 = mydsp_faustpower2_f(fSlow70);
		var fSlow72 = (1 - (fSlow3 * fSlow71));
		var fSlow73 = (1 - fSlow71);
		var fSlow74 = (fSlow72 / fSlow73);
		var fSlow75 = Math.sqrt(max_f(0, ((mydsp_faustpower2_f(fSlow72) / mydsp_faustpower2_f(fSlow73)) + -1)));
		var fSlow76 = (fSlow74 - fSlow75);
		var fSlow77 = (fSlow70 * (fSlow75 + (1 - fSlow74)));
		var fSlow78 = ((Math.exp((this.fConst39 / fSlow10)) / fSlow70) + -1);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.fRec11[0] = ((fSlow14 * this.fRec11[1]) + (fSlow15 * (this.fRec7[1] + this.fRec7[2])));
			this.fRec10[0] = ((fSlow8 * this.fRec10[1]) + (fSlow9 * (this.fRec7[1] + (fSlow11 * this.fRec11[0]))));
			this.fVec0[(this.IOTA & 32767)] = ((0.353553 * this.fRec10[0]) + 1e-20);
			var fTemp0 = (this.fVec0[((this.IOTA - this.iConst6) & 32767)] + (input7[i] + (0.6 * this.fRec8[1])));
			this.fVec1[(this.IOTA & 2047)] = fTemp0;
			this.fRec8[0] = this.fVec1[((this.IOTA - this.iConst7) & 2047)];
			var fRec9 = (0 - (0.6 * fTemp0));
			this.fRec15[0] = ((fSlow14 * this.fRec15[1]) + (fSlow15 * (this.fRec3[1] + this.fRec3[2])));
			this.fRec14[0] = ((fSlow22 * this.fRec14[1]) + (fSlow23 * (this.fRec3[1] + (fSlow24 * this.fRec15[0]))));
			this.fVec2[(this.IOTA & 32767)] = ((0.353553 * this.fRec14[0]) + 1e-20);
			var fTemp1 = (this.fVec2[((this.IOTA - this.iConst11) & 32767)] + (input3[i] + (0.6 * this.fRec12[1])));
			this.fVec3[(this.IOTA & 4095)] = fTemp1;
			this.fRec12[0] = this.fVec3[((this.IOTA - this.iConst12) & 4095)];
			var fRec13 = (0 - (0.6 * fTemp1));
			this.fRec19[0] = ((fSlow14 * this.fRec19[1]) + (fSlow15 * (this.fRec5[1] + this.fRec5[2])));
			this.fRec18[0] = ((fSlow31 * this.fRec18[1]) + (fSlow32 * (this.fRec5[1] + (fSlow33 * this.fRec19[0]))));
			this.fVec4[(this.IOTA & 16383)] = ((0.353553 * this.fRec18[0]) + 1e-20);
			var fTemp2 = (this.fVec4[((this.IOTA - this.iConst16) & 16383)] + (input5[i] + (0.6 * this.fRec16[1])));
			this.fVec5[(this.IOTA & 4095)] = fTemp2;
			this.fRec16[0] = this.fVec5[((this.IOTA - this.iConst17) & 4095)];
			var fRec17 = (0 - (0.6 * fTemp2));
			this.fRec23[0] = ((fSlow14 * this.fRec23[1]) + (fSlow15 * (this.fRec1[1] + this.fRec1[2])));
			this.fRec22[0] = ((fSlow40 * this.fRec22[1]) + (fSlow41 * (this.fRec1[1] + (fSlow42 * this.fRec23[0]))));
			this.fVec6[(this.IOTA & 32767)] = ((0.353553 * this.fRec22[0]) + 1e-20);
			var fTemp3 = (this.fVec6[((this.IOTA - this.iConst21) & 32767)] + (input1[i] + (0.6 * this.fRec20[1])));
			this.fVec7[(this.IOTA & 4095)] = fTemp3;
			this.fRec20[0] = this.fVec7[((this.IOTA - this.iConst22) & 4095)];
			var fRec21 = (0 - (0.6 * fTemp3));
			this.fRec27[0] = ((fSlow14 * this.fRec27[1]) + (fSlow15 * (this.fRec6[1] + this.fRec6[2])));
			this.fRec26[0] = ((fSlow49 * this.fRec26[1]) + (fSlow50 * (this.fRec6[1] + (fSlow51 * this.fRec27[0]))));
			this.fVec8[(this.IOTA & 16383)] = ((0.353553 * this.fRec26[0]) + 1e-20);
			var fTemp4 = ((input6[i] + this.fVec8[((this.IOTA - this.iConst26) & 16383)]) - (0.6 * this.fRec24[1]));
			this.fVec9[(this.IOTA & 2047)] = fTemp4;
			this.fRec24[0] = this.fVec9[((this.IOTA - this.iConst27) & 2047)];
			var fRec25 = (0.6 * fTemp4);
			this.fRec31[0] = ((fSlow14 * this.fRec31[1]) + (fSlow15 * (this.fRec2[1] + this.fRec2[2])));
			this.fRec30[0] = ((fSlow58 * this.fRec30[1]) + (fSlow59 * (this.fRec2[1] + (fSlow60 * this.fRec31[0]))));
			this.fVec10[(this.IOTA & 16383)] = ((0.353553 * this.fRec30[0]) + 1e-20);
			var fTemp5 = ((input2[i] + this.fVec10[((this.IOTA - this.iConst31) & 16383)]) - (0.6 * this.fRec28[1]));
			this.fVec11[(this.IOTA & 4095)] = fTemp5;
			this.fRec28[0] = this.fVec11[((this.IOTA - this.iConst32) & 4095)];
			var fRec29 = (0.6 * fTemp5);
			this.fRec35[0] = ((fSlow14 * this.fRec35[1]) + (fSlow15 * (this.fRec4[1] + this.fRec4[2])));
			this.fRec34[0] = ((fSlow67 * this.fRec34[1]) + (fSlow68 * (this.fRec4[1] + (fSlow69 * this.fRec35[0]))));
			this.fVec12[(this.IOTA & 16383)] = ((0.353553 * this.fRec34[0]) + 1e-20);
			var fTemp6 = ((input4[i] + this.fVec12[((this.IOTA - this.iConst36) & 16383)]) - (0.6 * this.fRec32[1]));
			this.fVec13[(this.IOTA & 4095)] = fTemp6;
			this.fRec32[0] = this.fVec13[((this.IOTA - this.iConst37) & 4095)];
			var fRec33 = (0.6 * fTemp6);
			this.fRec39[0] = ((fSlow14 * this.fRec39[1]) + (fSlow15 * (this.fRec0[1] + this.fRec0[2])));
			this.fRec38[0] = ((fSlow76 * this.fRec38[1]) + (fSlow77 * (this.fRec0[1] + (fSlow78 * this.fRec39[0]))));
			this.fVec14[(this.IOTA & 16383)] = ((0.353553 * this.fRec38[0]) + 1e-20);
			var fTemp7 = ((input0[i] + this.fVec14[((this.IOTA - this.iConst41) & 16383)]) - (0.6 * this.fRec36[1]));
			this.fVec15[(this.IOTA & 2047)] = fTemp7;
			this.fRec36[0] = this.fVec15[((this.IOTA - this.iConst42) & 2047)];
			var fRec37 = (0.6 * fTemp7);
			var fTemp8 = (fRec37 + fRec33);
			var fTemp9 = (fRec25 + (fRec29 + fTemp8));
			this.fRec0[0] = (this.fRec8[1] + (this.fRec12[1] + (this.fRec16[1] + (this.fRec20[1] + (this.fRec24[1] + (this.fRec28[1] + (this.fRec32[1] + (this.fRec36[1] + (fRec9 + (fRec13 + (fRec17 + (fRec21 + fTemp9))))))))))));
			this.fRec1[0] = ((this.fRec24[1] + (this.fRec28[1] + (this.fRec32[1] + (this.fRec36[1] + fTemp9)))) - (this.fRec8[1] + (this.fRec12[1] + (this.fRec16[1] + (this.fRec20[1] + (fRec9 + (fRec13 + (fRec21 + fRec17))))))));
			var fTemp10 = (fRec29 + fRec25);
			this.fRec2[0] = ((this.fRec16[1] + (this.fRec20[1] + (this.fRec32[1] + (this.fRec36[1] + (fRec17 + (fRec21 + fTemp8)))))) - (this.fRec8[1] + (this.fRec12[1] + (this.fRec24[1] + (this.fRec28[1] + (fRec9 + (fRec13 + fTemp10)))))));
			this.fRec3[0] = ((this.fRec8[1] + (this.fRec12[1] + (this.fRec32[1] + (this.fRec36[1] + (fRec9 + (fRec13 + fTemp8)))))) - (this.fRec16[1] + (this.fRec20[1] + (this.fRec24[1] + (this.fRec28[1] + (fRec17 + (fRec21 + fTemp10)))))));
			var fTemp11 = (fRec37 + fRec29);
			var fTemp12 = (fRec33 + fRec25);
			this.fRec4[0] = ((this.fRec12[1] + (this.fRec20[1] + (this.fRec28[1] + (this.fRec36[1] + (fRec13 + (fRec21 + fTemp11)))))) - (this.fRec8[1] + (this.fRec16[1] + (this.fRec24[1] + (this.fRec32[1] + (fRec9 + (fRec17 + fTemp12)))))));
			this.fRec5[0] = ((this.fRec8[1] + (this.fRec16[1] + (this.fRec28[1] + (this.fRec36[1] + (fRec9 + (fRec17 + fTemp11)))))) - (this.fRec12[1] + (this.fRec20[1] + (this.fRec24[1] + (this.fRec32[1] + (fRec13 + (fRec21 + fTemp12)))))));
			var fTemp13 = (fRec37 + fRec25);
			var fTemp14 = (fRec33 + fRec29);
			this.fRec6[0] = ((this.fRec8[1] + (this.fRec20[1] + (this.fRec24[1] + (this.fRec36[1] + (fRec9 + (fRec21 + fTemp13)))))) - (this.fRec12[1] + (this.fRec16[1] + (this.fRec28[1] + (this.fRec32[1] + (fRec13 + (fRec17 + fTemp14)))))));
			this.fRec7[0] = ((this.fRec12[1] + (this.fRec16[1] + (this.fRec24[1] + (this.fRec36[1] + (fRec13 + (fRec17 + fTemp13)))))) - (this.fRec8[1] + (this.fRec20[1] + (this.fRec28[1] + (this.fRec32[1] + (fRec9 + (fRec21 + fTemp14)))))));
			output0[i] = this.fRec0[0];
			output1[i] = this.fRec1[0];
			output2[i] = this.fRec2[0];
			output3[i] = this.fRec3[0];
			output4[i] = this.fRec4[0];
			output5[i] = this.fRec5[0];
			output6[i] = this.fRec6[0];
			output7[i] = this.fRec7[0];
			this.fRec11[1] = this.fRec11[0];
			this.fRec10[1] = this.fRec10[0];
			this.IOTA = (this.IOTA + 1);
			this.fRec8[1] = this.fRec8[0];
			this.fRec15[1] = this.fRec15[0];
			this.fRec14[1] = this.fRec14[0];
			this.fRec12[1] = this.fRec12[0];
			this.fRec19[1] = this.fRec19[0];
			this.fRec18[1] = this.fRec18[0];
			this.fRec16[1] = this.fRec16[0];
			this.fRec23[1] = this.fRec23[0];
			this.fRec22[1] = this.fRec22[0];
			this.fRec20[1] = this.fRec20[0];
			this.fRec27[1] = this.fRec27[0];
			this.fRec26[1] = this.fRec26[0];
			this.fRec24[1] = this.fRec24[0];
			this.fRec31[1] = this.fRec31[0];
			this.fRec30[1] = this.fRec30[0];
			this.fRec28[1] = this.fRec28[0];
			this.fRec35[1] = this.fRec35[0];
			this.fRec34[1] = this.fRec34[0];
			this.fRec32[1] = this.fRec32[0];
			this.fRec39[1] = this.fRec39[0];
			this.fRec38[1] = this.fRec38[0];
			this.fRec36[1] = this.fRec36[0];
			this.fRec0[2] = this.fRec0[1];
			this.fRec0[1] = this.fRec0[0];
			this.fRec1[2] = this.fRec1[1];
			this.fRec1[1] = this.fRec1[0];
			this.fRec2[2] = this.fRec2[1];
			this.fRec2[1] = this.fRec2[0];
			this.fRec3[2] = this.fRec3[1];
			this.fRec3[1] = this.fRec3[0];
			this.fRec4[2] = this.fRec4[1];
			this.fRec4[1] = this.fRec4[0];
			this.fRec5[2] = this.fRec5[1];
			this.fRec5[1] = this.fRec5[0];
			this.fRec6[2] = this.fRec6[1];
			this.fRec6[1] = this.fRec6[0];
			this.fRec7[2] = this.fRec7[1];
			this.fRec7[1] = this.fRec7[0];
			
		}
		
	}
	
}

