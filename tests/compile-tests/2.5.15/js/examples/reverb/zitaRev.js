
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.mydsp_faustpower2_f = function(value) {
	return (value * value);
	
}

function mydsp() {
	
	this.fVslider0;
	this.fRec0 = new Float32Array(2);
	this.IOTA;
	this.fVec0 = new Float32Array(16384);
	this.fVslider1;
	this.fRec1 = new Float32Array(2);
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fVslider2;
	this.fVslider3;
	this.fVslider4;
	this.fVslider5;
	this.fConst2;
	this.fConst3;
	this.fVslider6;
	this.fConst4;
	this.fVslider7;
	this.fVslider8;
	this.fConst5;
	this.fVslider9;
	this.fRec15 = new Float32Array(2);
	this.fRec14 = new Float32Array(2);
	this.fVec1 = new Float32Array(32768);
	this.fConst6;
	this.iConst7;
	this.fVec2 = new Float32Array(16384);
	this.fConst8;
	this.fVslider10;
	this.fVec3 = new Float32Array(2048);
	this.iConst9;
	this.fRec12 = new Float32Array(2);
	this.fConst10;
	this.fConst11;
	this.fRec19 = new Float32Array(2);
	this.fRec18 = new Float32Array(2);
	this.fVec4 = new Float32Array(32768);
	this.fConst12;
	this.iConst13;
	this.fVec5 = new Float32Array(4096);
	this.iConst14;
	this.fRec16 = new Float32Array(2);
	this.fConst15;
	this.fConst16;
	this.fRec23 = new Float32Array(2);
	this.fRec22 = new Float32Array(2);
	this.fVec6 = new Float32Array(16384);
	this.fConst17;
	this.iConst18;
	this.fVec7 = new Float32Array(4096);
	this.iConst19;
	this.fRec20 = new Float32Array(2);
	this.fConst20;
	this.fConst21;
	this.fRec27 = new Float32Array(2);
	this.fRec26 = new Float32Array(2);
	this.fVec8 = new Float32Array(32768);
	this.fConst22;
	this.iConst23;
	this.fVec9 = new Float32Array(4096);
	this.iConst24;
	this.fRec24 = new Float32Array(2);
	this.fConst25;
	this.fConst26;
	this.fRec31 = new Float32Array(2);
	this.fRec30 = new Float32Array(2);
	this.fVec10 = new Float32Array(16384);
	this.fConst27;
	this.iConst28;
	this.fVec11 = new Float32Array(2048);
	this.iConst29;
	this.fRec28 = new Float32Array(2);
	this.fConst30;
	this.fConst31;
	this.fRec35 = new Float32Array(2);
	this.fRec34 = new Float32Array(2);
	this.fVec12 = new Float32Array(16384);
	this.fConst32;
	this.iConst33;
	this.fVec13 = new Float32Array(4096);
	this.iConst34;
	this.fRec32 = new Float32Array(2);
	this.fConst35;
	this.fConst36;
	this.fRec39 = new Float32Array(2);
	this.fRec38 = new Float32Array(2);
	this.fVec14 = new Float32Array(16384);
	this.fConst37;
	this.iConst38;
	this.fVec15 = new Float32Array(4096);
	this.iConst39;
	this.fRec36 = new Float32Array(2);
	this.fConst40;
	this.fConst41;
	this.fRec43 = new Float32Array(2);
	this.fRec42 = new Float32Array(2);
	this.fVec16 = new Float32Array(16384);
	this.fConst42;
	this.iConst43;
	this.fVec17 = new Float32Array(2048);
	this.iConst44;
	this.fRec40 = new Float32Array(2);
	this.fRec4 = new Float32Array(3);
	this.fRec5 = new Float32Array(3);
	this.fRec6 = new Float32Array(3);
	this.fRec7 = new Float32Array(3);
	this.fRec8 = new Float32Array(3);
	this.fRec9 = new Float32Array(3);
	this.fRec10 = new Float32Array(3);
	this.fRec11 = new Float32Array(3);
	this.fRec3 = new Float32Array(3);
	this.fRec2 = new Float32Array(3);
	this.fRec45 = new Float32Array(3);
	this.fRec44 = new Float32Array(3);
	
	this.metadata = function(m) { 
		m.declare("author", "JOS, Revised by RM");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("description", "Example GUI for `zita_rev1_stereo` (mostly following the Linux `zita-rev1` GUI).");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "zitaRev");
		m.declare("reverbs.lib/name", "Faust Reverb Library");
		m.declare("reverbs.lib/version", "0.0");
		m.declare("routes.lib/name", "Faust Signal Routing Library");
		m.declare("routes.lib/version", "0.0");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
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
		this.fConst1 = (6.28319 / this.fConst0);
		this.fConst2 = Math.floor(((0.219991 * this.fConst0) + 0.5));
		this.fConst3 = ((0 - (6.90776 * this.fConst2)) / this.fConst0);
		this.fConst4 = (6.28319 / this.fConst0);
		this.fConst5 = (3.14159 / this.fConst0);
		this.fConst6 = Math.floor(((0.019123 * this.fConst0) + 0.5));
		this.iConst7 = min_f(16384, max_f(0, (this.fConst2 - this.fConst6)));
		this.fConst8 = (0.001 * this.fConst0);
		this.iConst9 = min_f(1024, max_f(0, (this.fConst6 + -1)));
		this.fConst10 = Math.floor(((0.256891 * this.fConst0) + 0.5));
		this.fConst11 = ((0 - (6.90776 * this.fConst10)) / this.fConst0);
		this.fConst12 = Math.floor(((0.027333 * this.fConst0) + 0.5));
		this.iConst13 = min_f(16384, max_f(0, (this.fConst10 - this.fConst12)));
		this.iConst14 = min_f(2048, max_f(0, (this.fConst12 + -1)));
		this.fConst15 = Math.floor(((0.192303 * this.fConst0) + 0.5));
		this.fConst16 = ((0 - (6.90776 * this.fConst15)) / this.fConst0);
		this.fConst17 = Math.floor(((0.029291 * this.fConst0) + 0.5));
		this.iConst18 = min_f(8192, max_f(0, (this.fConst15 - this.fConst17)));
		this.iConst19 = min_f(2048, max_f(0, (this.fConst17 + -1)));
		this.fConst20 = Math.floor(((0.210389 * this.fConst0) + 0.5));
		this.fConst21 = ((0 - (6.90776 * this.fConst20)) / this.fConst0);
		this.fConst22 = Math.floor(((0.024421 * this.fConst0) + 0.5));
		this.iConst23 = min_f(16384, max_f(0, (this.fConst20 - this.fConst22)));
		this.iConst24 = min_f(2048, max_f(0, (this.fConst22 + -1)));
		this.fConst25 = Math.floor(((0.125 * this.fConst0) + 0.5));
		this.fConst26 = ((0 - (6.90776 * this.fConst25)) / this.fConst0);
		this.fConst27 = Math.floor(((0.013458 * this.fConst0) + 0.5));
		this.iConst28 = min_f(8192, max_f(0, (this.fConst25 - this.fConst27)));
		this.iConst29 = min_f(1024, max_f(0, (this.fConst27 + -1)));
		this.fConst30 = Math.floor(((0.127837 * this.fConst0) + 0.5));
		this.fConst31 = ((0 - (6.90776 * this.fConst30)) / this.fConst0);
		this.fConst32 = Math.floor(((0.031604 * this.fConst0) + 0.5));
		this.iConst33 = min_f(8192, max_f(0, (this.fConst30 - this.fConst32)));
		this.iConst34 = min_f(2048, max_f(0, (this.fConst32 + -1)));
		this.fConst35 = Math.floor(((0.174713 * this.fConst0) + 0.5));
		this.fConst36 = ((0 - (6.90776 * this.fConst35)) / this.fConst0);
		this.fConst37 = Math.floor(((0.022904 * this.fConst0) + 0.5));
		this.iConst38 = min_f(8192, max_f(0, (this.fConst35 - this.fConst37)));
		this.iConst39 = min_f(2048, max_f(0, (this.fConst37 + -1)));
		this.fConst40 = Math.floor(((0.153129 * this.fConst0) + 0.5));
		this.fConst41 = ((0 - (6.90776 * this.fConst40)) / this.fConst0);
		this.fConst42 = Math.floor(((0.020346 * this.fConst0) + 0.5));
		this.iConst43 = min_f(8192, max_f(0, (this.fConst40 - this.fConst42)));
		this.iConst44 = min_f(1024, max_f(0, (this.fConst42 + -1)));
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fVslider0 = -20;
		this.fVslider1 = 0;
		this.fVslider2 = 1500;
		this.fVslider3 = 0;
		this.fVslider4 = 315;
		this.fVslider5 = 0;
		this.fVslider6 = 2;
		this.fVslider7 = 6000;
		this.fVslider8 = 3;
		this.fVslider9 = 200;
		this.fVslider10 = 60;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.fRec0[l0] = 0;
			
		}
		this.IOTA = 0;
		for (var l1 = 0; (l1 < 16384); l1 = (l1 + 1)) {
			this.fVec0[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec1[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec15[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec14[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 32768); l5 = (l5 + 1)) {
			this.fVec1[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 16384); l6 = (l6 + 1)) {
			this.fVec2[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 2048); l7 = (l7 + 1)) {
			this.fVec3[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			this.fRec12[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			this.fRec19[l9] = 0;
			
		}
		for (var l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			this.fRec18[l10] = 0;
			
		}
		for (var l11 = 0; (l11 < 32768); l11 = (l11 + 1)) {
			this.fVec4[l11] = 0;
			
		}
		for (var l12 = 0; (l12 < 4096); l12 = (l12 + 1)) {
			this.fVec5[l12] = 0;
			
		}
		for (var l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			this.fRec16[l13] = 0;
			
		}
		for (var l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			this.fRec23[l14] = 0;
			
		}
		for (var l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			this.fRec22[l15] = 0;
			
		}
		for (var l16 = 0; (l16 < 16384); l16 = (l16 + 1)) {
			this.fVec6[l16] = 0;
			
		}
		for (var l17 = 0; (l17 < 4096); l17 = (l17 + 1)) {
			this.fVec7[l17] = 0;
			
		}
		for (var l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			this.fRec20[l18] = 0;
			
		}
		for (var l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			this.fRec27[l19] = 0;
			
		}
		for (var l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			this.fRec26[l20] = 0;
			
		}
		for (var l21 = 0; (l21 < 32768); l21 = (l21 + 1)) {
			this.fVec8[l21] = 0;
			
		}
		for (var l22 = 0; (l22 < 4096); l22 = (l22 + 1)) {
			this.fVec9[l22] = 0;
			
		}
		for (var l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			this.fRec24[l23] = 0;
			
		}
		for (var l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			this.fRec31[l24] = 0;
			
		}
		for (var l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			this.fRec30[l25] = 0;
			
		}
		for (var l26 = 0; (l26 < 16384); l26 = (l26 + 1)) {
			this.fVec10[l26] = 0;
			
		}
		for (var l27 = 0; (l27 < 2048); l27 = (l27 + 1)) {
			this.fVec11[l27] = 0;
			
		}
		for (var l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			this.fRec28[l28] = 0;
			
		}
		for (var l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			this.fRec35[l29] = 0;
			
		}
		for (var l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			this.fRec34[l30] = 0;
			
		}
		for (var l31 = 0; (l31 < 16384); l31 = (l31 + 1)) {
			this.fVec12[l31] = 0;
			
		}
		for (var l32 = 0; (l32 < 4096); l32 = (l32 + 1)) {
			this.fVec13[l32] = 0;
			
		}
		for (var l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			this.fRec32[l33] = 0;
			
		}
		for (var l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			this.fRec39[l34] = 0;
			
		}
		for (var l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			this.fRec38[l35] = 0;
			
		}
		for (var l36 = 0; (l36 < 16384); l36 = (l36 + 1)) {
			this.fVec14[l36] = 0;
			
		}
		for (var l37 = 0; (l37 < 4096); l37 = (l37 + 1)) {
			this.fVec15[l37] = 0;
			
		}
		for (var l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			this.fRec36[l38] = 0;
			
		}
		for (var l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			this.fRec43[l39] = 0;
			
		}
		for (var l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			this.fRec42[l40] = 0;
			
		}
		for (var l41 = 0; (l41 < 16384); l41 = (l41 + 1)) {
			this.fVec16[l41] = 0;
			
		}
		for (var l42 = 0; (l42 < 2048); l42 = (l42 + 1)) {
			this.fVec17[l42] = 0;
			
		}
		for (var l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			this.fRec40[l43] = 0;
			
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
		for (var l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			this.fRec8[l48] = 0;
			
		}
		for (var l49 = 0; (l49 < 3); l49 = (l49 + 1)) {
			this.fRec9[l49] = 0;
			
		}
		for (var l50 = 0; (l50 < 3); l50 = (l50 + 1)) {
			this.fRec10[l50] = 0;
			
		}
		for (var l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			this.fRec11[l51] = 0;
			
		}
		for (var l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			this.fRec3[l52] = 0;
			
		}
		for (var l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			this.fRec2[l53] = 0;
			
		}
		for (var l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			this.fRec45[l54] = 0;
			
		}
		for (var l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			this.fRec44[l55] = 0;
			
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
		ui_interface.declare("0", "0", "");
		ui_interface.declare("0", "tooltip", "~ ZITA REV1 FEEDBACK DELAY NETWORK (FDN) & SCHROEDER  ALLPASS-COMB REVERBERATOR (8x8). See Faust's reverbs.lib for documentation and  references");
		ui_interface.openHorizontalBox("Zita_Rev1");
		ui_interface.declare("0", "1", "");
		ui_interface.openHorizontalBox("Input");
		ui_interface.declare("fVslider10", "1", "");
		ui_interface.declare("fVslider10", "style", "knob");
		ui_interface.declare("fVslider10", "tooltip", "Delay in ms   before reverberation begins");
		ui_interface.declare("fVslider10", "unit", "ms");
		ui_interface.addVerticalSlider("In Delay", function handler(obj) { function setval(val) { obj.fVslider10 = val; } return setval; }(this), 60, 20, 100, 1);
		ui_interface.closeBox();
		ui_interface.declare("0", "2", "");
		ui_interface.openHorizontalBox("Decay Times in Bands (see tooltips)");
		ui_interface.declare("fVslider9", "1", "");
		ui_interface.declare("fVslider9", "scale", "log");
		ui_interface.declare("fVslider9", "style", "knob");
		ui_interface.declare("fVslider9", "tooltip", "Crossover frequency (Hz) separating low and middle frequencies");
		ui_interface.declare("fVslider9", "unit", "Hz");
		ui_interface.addVerticalSlider("LF X", function handler(obj) { function setval(val) { obj.fVslider9 = val; } return setval; }(this), 200, 50, 1000, 1);
		ui_interface.declare("fVslider8", "2", "");
		ui_interface.declare("fVslider8", "scale", "log");
		ui_interface.declare("fVslider8", "style", "knob");
		ui_interface.declare("fVslider8", "tooltip", "T60 = time (in seconds) to decay 60dB in low-frequency band");
		ui_interface.declare("fVslider8", "unit", "s");
		ui_interface.addVerticalSlider("Low RT60", function handler(obj) { function setval(val) { obj.fVslider8 = val; } return setval; }(this), 3, 1, 8, 0.1);
		ui_interface.declare("fVslider6", "3", "");
		ui_interface.declare("fVslider6", "scale", "log");
		ui_interface.declare("fVslider6", "style", "knob");
		ui_interface.declare("fVslider6", "tooltip", "T60 = time (in seconds) to decay 60dB in middle band");
		ui_interface.declare("fVslider6", "unit", "s");
		ui_interface.addVerticalSlider("Mid RT60", function handler(obj) { function setval(val) { obj.fVslider6 = val; } return setval; }(this), 2, 1, 8, 0.1);
		ui_interface.declare("fVslider7", "4", "");
		ui_interface.declare("fVslider7", "scale", "log");
		ui_interface.declare("fVslider7", "style", "knob");
		ui_interface.declare("fVslider7", "tooltip", "Frequency (Hz) at which the high-frequency T60 is half the middle-band's T60");
		ui_interface.declare("fVslider7", "unit", "Hz");
		ui_interface.addVerticalSlider("HF Damping", function handler(obj) { function setval(val) { obj.fVslider7 = val; } return setval; }(this), 6000, 1500, 23520, 1);
		ui_interface.closeBox();
		ui_interface.declare("0", "3", "");
		ui_interface.openHorizontalBox("RM Peaking Equalizer 1");
		ui_interface.declare("fVslider4", "1", "");
		ui_interface.declare("fVslider4", "scale", "log");
		ui_interface.declare("fVslider4", "style", "knob");
		ui_interface.declare("fVslider4", "tooltip", "Center-frequency of second-order Regalia-Mitra peaking equalizer section 1");
		ui_interface.declare("fVslider4", "unit", "Hz");
		ui_interface.addVerticalSlider("Eq1 Freq", function handler(obj) { function setval(val) { obj.fVslider4 = val; } return setval; }(this), 315, 40, 2500, 1);
		ui_interface.declare("fVslider5", "2", "");
		ui_interface.declare("fVslider5", "style", "knob");
		ui_interface.declare("fVslider5", "tooltip", "Peak level   in dB of second-order Regalia-Mitra peaking equalizer section 1");
		ui_interface.declare("fVslider5", "unit", "dB");
		ui_interface.addVerticalSlider("Eq1 Level", function handler(obj) { function setval(val) { obj.fVslider5 = val; } return setval; }(this), 0, -15, 15, 0.1);
		ui_interface.closeBox();
		ui_interface.declare("0", "4", "");
		ui_interface.openHorizontalBox("RM Peaking Equalizer 2");
		ui_interface.declare("fVslider2", "1", "");
		ui_interface.declare("fVslider2", "scale", "log");
		ui_interface.declare("fVslider2", "style", "knob");
		ui_interface.declare("fVslider2", "tooltip", "Center-frequency of second-order Regalia-Mitra peaking equalizer section 2");
		ui_interface.declare("fVslider2", "unit", "Hz");
		ui_interface.addVerticalSlider("Eq2 Freq", function handler(obj) { function setval(val) { obj.fVslider2 = val; } return setval; }(this), 1500, 160, 10000, 1);
		ui_interface.declare("fVslider3", "2", "");
		ui_interface.declare("fVslider3", "style", "knob");
		ui_interface.declare("fVslider3", "tooltip", "Peak level   in dB of second-order Regalia-Mitra peaking equalizer section 2");
		ui_interface.declare("fVslider3", "unit", "dB");
		ui_interface.addVerticalSlider("Eq2 Level", function handler(obj) { function setval(val) { obj.fVslider3 = val; } return setval; }(this), 0, -15, 15, 0.1);
		ui_interface.closeBox();
		ui_interface.declare("0", "5", "");
		ui_interface.openHorizontalBox("Output");
		ui_interface.declare("fVslider1", "1", "");
		ui_interface.declare("fVslider1", "style", "knob");
		ui_interface.declare("fVslider1", "tooltip", "-1 = dry, 1 = wet");
		ui_interface.addVerticalSlider("Dry/Wet Mix", function handler(obj) { function setval(val) { obj.fVslider1 = val; } return setval; }(this), 0, -1, 1, 0.01);
		ui_interface.declare("fVslider0", "2", "");
		ui_interface.declare("fVslider0", "style", "knob");
		ui_interface.declare("fVslider0", "tooltip", "Output scale   factor");
		ui_interface.declare("fVslider0", "unit", "dB");
		ui_interface.addVerticalSlider("Level", function handler(obj) { function setval(val) { obj.fVslider0 = val; } return setval; }(this), -20, -70, 40, 0.1);
		ui_interface.closeBox();
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var input1 = inputs[1];
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = (0.001 * Math.pow(10, (0.05 * this.fVslider0)));
		var fSlow1 = (0.001 * this.fVslider1);
		var fSlow2 = this.fVslider2;
		var fSlow3 = Math.pow(10, (0.05 * this.fVslider3));
		var fSlow4 = (this.fConst1 * (fSlow2 / Math.sqrt(max_f(0, fSlow3))));
		var fSlow5 = ((1 - fSlow4) / (fSlow4 + 1));
		var fSlow6 = this.fVslider4;
		var fSlow7 = Math.pow(10, (0.05 * this.fVslider5));
		var fSlow8 = (this.fConst1 * (fSlow6 / Math.sqrt(max_f(0, fSlow7))));
		var fSlow9 = ((1 - fSlow8) / (fSlow8 + 1));
		var fSlow10 = this.fVslider6;
		var fSlow11 = Math.exp((this.fConst3 / fSlow10));
		var fSlow12 = mydsp_faustpower2_f(fSlow11);
		var fSlow13 = Math.cos((this.fConst4 * this.fVslider7));
		var fSlow14 = (1 - (fSlow12 * fSlow13));
		var fSlow15 = (1 - fSlow12);
		var fSlow16 = (fSlow14 / fSlow15);
		var fSlow17 = Math.sqrt(max_f(0, ((mydsp_faustpower2_f(fSlow14) / mydsp_faustpower2_f(fSlow15)) + -1)));
		var fSlow18 = (fSlow16 - fSlow17);
		var fSlow19 = (fSlow11 * (fSlow17 + (1 - fSlow16)));
		var fSlow20 = this.fVslider8;
		var fSlow21 = ((Math.exp((this.fConst3 / fSlow20)) / fSlow11) + -1);
		var fSlow22 = (1 / Math.tan((this.fConst5 * this.fVslider9)));
		var fSlow23 = (fSlow22 + 1);
		var fSlow24 = (0 - ((1 - fSlow22) / fSlow23));
		var fSlow25 = (1 / fSlow23);
		var iSlow26 = min_f(8192, max_f(0, (this.fConst8 * this.fVslider10)));
		var fSlow27 = Math.exp((this.fConst11 / fSlow10));
		var fSlow28 = mydsp_faustpower2_f(fSlow27);
		var fSlow29 = (1 - (fSlow13 * fSlow28));
		var fSlow30 = (1 - fSlow28);
		var fSlow31 = (fSlow29 / fSlow30);
		var fSlow32 = Math.sqrt(max_f(0, ((mydsp_faustpower2_f(fSlow29) / mydsp_faustpower2_f(fSlow30)) + -1)));
		var fSlow33 = (fSlow31 - fSlow32);
		var fSlow34 = (fSlow27 * (fSlow32 + (1 - fSlow31)));
		var fSlow35 = ((Math.exp((this.fConst11 / fSlow20)) / fSlow27) + -1);
		var fSlow36 = Math.exp((this.fConst16 / fSlow10));
		var fSlow37 = mydsp_faustpower2_f(fSlow36);
		var fSlow38 = (1 - (fSlow13 * fSlow37));
		var fSlow39 = (1 - fSlow37);
		var fSlow40 = (fSlow38 / fSlow39);
		var fSlow41 = Math.sqrt(max_f(0, ((mydsp_faustpower2_f(fSlow38) / mydsp_faustpower2_f(fSlow39)) + -1)));
		var fSlow42 = (fSlow40 - fSlow41);
		var fSlow43 = (fSlow36 * (fSlow41 + (1 - fSlow40)));
		var fSlow44 = ((Math.exp((this.fConst16 / fSlow20)) / fSlow36) + -1);
		var fSlow45 = Math.exp((this.fConst21 / fSlow10));
		var fSlow46 = mydsp_faustpower2_f(fSlow45);
		var fSlow47 = (1 - (fSlow13 * fSlow46));
		var fSlow48 = (1 - fSlow46);
		var fSlow49 = (fSlow47 / fSlow48);
		var fSlow50 = Math.sqrt(max_f(0, ((mydsp_faustpower2_f(fSlow47) / mydsp_faustpower2_f(fSlow48)) + -1)));
		var fSlow51 = (fSlow49 - fSlow50);
		var fSlow52 = (fSlow45 * (fSlow50 + (1 - fSlow49)));
		var fSlow53 = ((Math.exp((this.fConst21 / fSlow20)) / fSlow45) + -1);
		var fSlow54 = Math.exp((this.fConst26 / fSlow10));
		var fSlow55 = mydsp_faustpower2_f(fSlow54);
		var fSlow56 = (1 - (fSlow13 * fSlow55));
		var fSlow57 = (1 - fSlow55);
		var fSlow58 = (fSlow56 / fSlow57);
		var fSlow59 = Math.sqrt(max_f(0, ((mydsp_faustpower2_f(fSlow56) / mydsp_faustpower2_f(fSlow57)) + -1)));
		var fSlow60 = (fSlow58 - fSlow59);
		var fSlow61 = (fSlow54 * (fSlow59 + (1 - fSlow58)));
		var fSlow62 = ((Math.exp((this.fConst26 / fSlow20)) / fSlow54) + -1);
		var fSlow63 = Math.exp((this.fConst31 / fSlow10));
		var fSlow64 = mydsp_faustpower2_f(fSlow63);
		var fSlow65 = (1 - (fSlow13 * fSlow64));
		var fSlow66 = (1 - fSlow64);
		var fSlow67 = (fSlow65 / fSlow66);
		var fSlow68 = Math.sqrt(max_f(0, ((mydsp_faustpower2_f(fSlow65) / mydsp_faustpower2_f(fSlow66)) + -1)));
		var fSlow69 = (fSlow67 - fSlow68);
		var fSlow70 = (fSlow63 * (fSlow68 + (1 - fSlow67)));
		var fSlow71 = ((Math.exp((this.fConst31 / fSlow20)) / fSlow63) + -1);
		var fSlow72 = Math.exp((this.fConst36 / fSlow10));
		var fSlow73 = mydsp_faustpower2_f(fSlow72);
		var fSlow74 = (1 - (fSlow13 * fSlow73));
		var fSlow75 = (1 - fSlow73);
		var fSlow76 = (fSlow74 / fSlow75);
		var fSlow77 = Math.sqrt(max_f(0, ((mydsp_faustpower2_f(fSlow74) / mydsp_faustpower2_f(fSlow75)) + -1)));
		var fSlow78 = (fSlow76 - fSlow77);
		var fSlow79 = (fSlow72 * (fSlow77 + (1 - fSlow76)));
		var fSlow80 = ((Math.exp((this.fConst36 / fSlow20)) / fSlow72) + -1);
		var fSlow81 = Math.exp((this.fConst41 / fSlow10));
		var fSlow82 = mydsp_faustpower2_f(fSlow81);
		var fSlow83 = (1 - (fSlow13 * fSlow82));
		var fSlow84 = (1 - fSlow82);
		var fSlow85 = (fSlow83 / fSlow84);
		var fSlow86 = Math.sqrt(max_f(0, ((mydsp_faustpower2_f(fSlow83) / mydsp_faustpower2_f(fSlow84)) + -1)));
		var fSlow87 = (fSlow85 - fSlow86);
		var fSlow88 = (fSlow81 * (fSlow86 + (1 - fSlow85)));
		var fSlow89 = ((Math.exp((this.fConst41 / fSlow20)) / fSlow81) + -1);
		var fSlow90 = ((0 - Math.cos((this.fConst1 * fSlow6))) * (fSlow9 + 1));
		var fSlow91 = ((0 - Math.cos((this.fConst1 * fSlow2))) * (fSlow5 + 1));
		for (var i = 0; (i < count); i = (i + 1)) {
			this.fRec0[0] = (fSlow0 + (0.999 * this.fRec0[1]));
			var fTemp0 = input0[i];
			this.fVec0[(this.IOTA & 16383)] = fTemp0;
			this.fRec1[0] = (fSlow1 + (0.999 * this.fRec1[1]));
			var fTemp1 = (this.fRec1[0] + 1);
			var fTemp2 = (1 - (0.5 * fTemp1));
			this.fRec15[0] = ((fSlow24 * this.fRec15[1]) + (fSlow25 * (this.fRec11[1] + this.fRec11[2])));
			this.fRec14[0] = ((fSlow18 * this.fRec14[1]) + (fSlow19 * (this.fRec11[1] + (fSlow21 * this.fRec15[0]))));
			this.fVec1[(this.IOTA & 32767)] = ((0.353553 * this.fRec14[0]) + 1e-20);
			var fTemp3 = input1[i];
			this.fVec2[(this.IOTA & 16383)] = fTemp3;
			var fTemp4 = (0.3 * this.fVec2[((this.IOTA - iSlow26) & 16383)]);
			var fTemp5 = (((0.6 * this.fRec12[1]) + this.fVec1[((this.IOTA - this.iConst7) & 32767)]) - fTemp4);
			this.fVec3[(this.IOTA & 2047)] = fTemp5;
			this.fRec12[0] = this.fVec3[((this.IOTA - this.iConst9) & 2047)];
			var fRec13 = (0 - (0.6 * fTemp5));
			this.fRec19[0] = ((fSlow24 * this.fRec19[1]) + (fSlow25 * (this.fRec7[1] + this.fRec7[2])));
			this.fRec18[0] = ((fSlow33 * this.fRec18[1]) + (fSlow34 * (this.fRec7[1] + (fSlow35 * this.fRec19[0]))));
			this.fVec4[(this.IOTA & 32767)] = ((0.353553 * this.fRec18[0]) + 1e-20);
			var fTemp6 = (((0.6 * this.fRec16[1]) + this.fVec4[((this.IOTA - this.iConst13) & 32767)]) - fTemp4);
			this.fVec5[(this.IOTA & 4095)] = fTemp6;
			this.fRec16[0] = this.fVec5[((this.IOTA - this.iConst14) & 4095)];
			var fRec17 = (0 - (0.6 * fTemp6));
			this.fRec23[0] = ((fSlow24 * this.fRec23[1]) + (fSlow25 * (this.fRec9[1] + this.fRec9[2])));
			this.fRec22[0] = ((fSlow42 * this.fRec22[1]) + (fSlow43 * (this.fRec9[1] + (fSlow44 * this.fRec23[0]))));
			this.fVec6[(this.IOTA & 16383)] = ((0.353553 * this.fRec22[0]) + 1e-20);
			var fTemp7 = (this.fVec6[((this.IOTA - this.iConst18) & 16383)] + (fTemp4 + (0.6 * this.fRec20[1])));
			this.fVec7[(this.IOTA & 4095)] = fTemp7;
			this.fRec20[0] = this.fVec7[((this.IOTA - this.iConst19) & 4095)];
			var fRec21 = (0 - (0.6 * fTemp7));
			this.fRec27[0] = ((fSlow24 * this.fRec27[1]) + (fSlow25 * (this.fRec5[1] + this.fRec5[2])));
			this.fRec26[0] = ((fSlow51 * this.fRec26[1]) + (fSlow52 * (this.fRec5[1] + (fSlow53 * this.fRec27[0]))));
			this.fVec8[(this.IOTA & 32767)] = ((0.353553 * this.fRec26[0]) + 1e-20);
			var fTemp8 = (fTemp4 + ((0.6 * this.fRec24[1]) + this.fVec8[((this.IOTA - this.iConst23) & 32767)]));
			this.fVec9[(this.IOTA & 4095)] = fTemp8;
			this.fRec24[0] = this.fVec9[((this.IOTA - this.iConst24) & 4095)];
			var fRec25 = (0 - (0.6 * fTemp8));
			this.fRec31[0] = ((fSlow24 * this.fRec31[1]) + (fSlow25 * (this.fRec10[1] + this.fRec10[2])));
			this.fRec30[0] = ((fSlow60 * this.fRec30[1]) + (fSlow61 * (this.fRec10[1] + (fSlow62 * this.fRec31[0]))));
			this.fVec10[(this.IOTA & 16383)] = ((0.353553 * this.fRec30[0]) + 1e-20);
			var fTemp9 = (0.3 * this.fVec0[((this.IOTA - iSlow26) & 16383)]);
			var fTemp10 = (this.fVec10[((this.IOTA - this.iConst28) & 16383)] - (fTemp9 + (0.6 * this.fRec28[1])));
			this.fVec11[(this.IOTA & 2047)] = fTemp10;
			this.fRec28[0] = this.fVec11[((this.IOTA - this.iConst29) & 2047)];
			var fRec29 = (0.6 * fTemp10);
			this.fRec35[0] = ((fSlow24 * this.fRec35[1]) + (fSlow25 * (this.fRec6[1] + this.fRec6[2])));
			this.fRec34[0] = ((fSlow69 * this.fRec34[1]) + (fSlow70 * (this.fRec6[1] + (fSlow71 * this.fRec35[0]))));
			this.fVec12[(this.IOTA & 16383)] = ((0.353553 * this.fRec34[0]) + 1e-20);
			var fTemp11 = (this.fVec12[((this.IOTA - this.iConst33) & 16383)] - (fTemp9 + (0.6 * this.fRec32[1])));
			this.fVec13[(this.IOTA & 4095)] = fTemp11;
			this.fRec32[0] = this.fVec13[((this.IOTA - this.iConst34) & 4095)];
			var fRec33 = (0.6 * fTemp11);
			this.fRec39[0] = ((fSlow24 * this.fRec39[1]) + (fSlow25 * (this.fRec8[1] + this.fRec8[2])));
			this.fRec38[0] = ((fSlow78 * this.fRec38[1]) + (fSlow79 * (this.fRec8[1] + (fSlow80 * this.fRec39[0]))));
			this.fVec14[(this.IOTA & 16383)] = ((0.353553 * this.fRec38[0]) + 1e-20);
			var fTemp12 = ((fTemp9 + this.fVec14[((this.IOTA - this.iConst38) & 16383)]) - (0.6 * this.fRec36[1]));
			this.fVec15[(this.IOTA & 4095)] = fTemp12;
			this.fRec36[0] = this.fVec15[((this.IOTA - this.iConst39) & 4095)];
			var fRec37 = (0.6 * fTemp12);
			this.fRec43[0] = ((fSlow24 * this.fRec43[1]) + (fSlow25 * (this.fRec4[1] + this.fRec4[2])));
			this.fRec42[0] = ((fSlow87 * this.fRec42[1]) + (fSlow88 * (this.fRec4[1] + (fSlow89 * this.fRec43[0]))));
			this.fVec16[(this.IOTA & 16383)] = ((0.353553 * this.fRec42[0]) + 1e-20);
			var fTemp13 = ((this.fVec16[((this.IOTA - this.iConst43) & 16383)] + fTemp9) - (0.6 * this.fRec40[1]));
			this.fVec17[(this.IOTA & 2047)] = fTemp13;
			this.fRec40[0] = this.fVec17[((this.IOTA - this.iConst44) & 2047)];
			var fRec41 = (0.6 * fTemp13);
			var fTemp14 = (fRec41 + fRec37);
			var fTemp15 = (fRec29 + (fRec33 + fTemp14));
			this.fRec4[0] = (this.fRec12[1] + (this.fRec16[1] + (this.fRec20[1] + (this.fRec24[1] + (this.fRec28[1] + (this.fRec32[1] + (this.fRec36[1] + (this.fRec40[1] + (fRec13 + (fRec17 + (fRec21 + (fRec25 + fTemp15))))))))))));
			this.fRec5[0] = ((this.fRec28[1] + (this.fRec32[1] + (this.fRec36[1] + (this.fRec40[1] + fTemp15)))) - (this.fRec12[1] + (this.fRec16[1] + (this.fRec20[1] + (this.fRec24[1] + (fRec13 + (fRec17 + (fRec25 + fRec21))))))));
			var fTemp16 = (fRec33 + fRec29);
			this.fRec6[0] = ((this.fRec20[1] + (this.fRec24[1] + (this.fRec36[1] + (this.fRec40[1] + (fRec21 + (fRec25 + fTemp14)))))) - (this.fRec12[1] + (this.fRec16[1] + (this.fRec28[1] + (this.fRec32[1] + (fRec13 + (fRec17 + fTemp16)))))));
			this.fRec7[0] = ((this.fRec12[1] + (this.fRec16[1] + (this.fRec36[1] + (this.fRec40[1] + (fRec13 + (fRec17 + fTemp14)))))) - (this.fRec20[1] + (this.fRec24[1] + (this.fRec28[1] + (this.fRec32[1] + (fRec21 + (fRec25 + fTemp16)))))));
			var fTemp17 = (fRec41 + fRec33);
			var fTemp18 = (fRec37 + fRec29);
			this.fRec8[0] = ((this.fRec16[1] + (this.fRec24[1] + (this.fRec32[1] + (this.fRec40[1] + (fRec17 + (fRec25 + fTemp17)))))) - (this.fRec12[1] + (this.fRec20[1] + (this.fRec28[1] + (this.fRec36[1] + (fRec13 + (fRec21 + fTemp18)))))));
			this.fRec9[0] = ((this.fRec12[1] + (this.fRec20[1] + (this.fRec32[1] + (this.fRec40[1] + (fRec13 + (fRec21 + fTemp17)))))) - (this.fRec16[1] + (this.fRec24[1] + (this.fRec28[1] + (this.fRec36[1] + (fRec17 + (fRec25 + fTemp18)))))));
			var fTemp19 = (fRec41 + fRec29);
			var fTemp20 = (fRec37 + fRec33);
			this.fRec10[0] = ((this.fRec12[1] + (this.fRec24[1] + (this.fRec28[1] + (this.fRec40[1] + (fRec13 + (fRec25 + fTemp19)))))) - (this.fRec16[1] + (this.fRec20[1] + (this.fRec32[1] + (this.fRec36[1] + (fRec17 + (fRec21 + fTemp20)))))));
			this.fRec11[0] = ((this.fRec16[1] + (this.fRec20[1] + (this.fRec28[1] + (this.fRec40[1] + (fRec17 + (fRec21 + fTemp19)))))) - (this.fRec12[1] + (this.fRec24[1] + (this.fRec32[1] + (this.fRec36[1] + (fRec13 + (fRec25 + fTemp20)))))));
			var fTemp21 = (0.37 * (this.fRec5[0] + this.fRec6[0]));
			var fTemp22 = (fSlow90 * this.fRec3[1]);
			this.fRec3[0] = (fTemp21 - (fTemp22 + (fSlow9 * this.fRec3[2])));
			var fTemp23 = (fSlow9 * this.fRec3[0]);
			var fTemp24 = (0.5 * ((fTemp23 + (this.fRec3[2] + (fTemp21 + fTemp22))) + (fSlow7 * ((fTemp23 + (fTemp22 + this.fRec3[2])) - fTemp21))));
			var fTemp25 = (fSlow91 * this.fRec2[1]);
			this.fRec2[0] = (fTemp24 - (fTemp25 + (fSlow5 * this.fRec2[2])));
			var fTemp26 = (fSlow5 * this.fRec2[0]);
			output0[i] = (0.5 * (this.fRec0[0] * ((fTemp0 * fTemp1) + (fTemp2 * ((fTemp26 + (this.fRec2[2] + (fTemp24 + fTemp25))) + (fSlow3 * ((fTemp26 + (fTemp25 + this.fRec2[2])) - fTemp24)))))));
			var fTemp27 = (0.37 * (this.fRec5[0] - this.fRec6[0]));
			var fTemp28 = (fSlow90 * this.fRec45[1]);
			this.fRec45[0] = (fTemp27 - (fTemp28 + (fSlow9 * this.fRec45[2])));
			var fTemp29 = (fSlow9 * this.fRec45[0]);
			var fTemp30 = (0.5 * ((fTemp29 + (this.fRec45[2] + (fTemp27 + fTemp28))) + (fSlow7 * ((fTemp29 + (fTemp28 + this.fRec45[2])) - fTemp27))));
			var fTemp31 = (fSlow91 * this.fRec44[1]);
			this.fRec44[0] = (fTemp30 - (fTemp31 + (fSlow5 * this.fRec44[2])));
			var fTemp32 = (fSlow5 * this.fRec44[0]);
			output1[i] = (0.5 * (this.fRec0[0] * ((fTemp3 * fTemp1) + (fTemp2 * ((fTemp32 + (this.fRec44[2] + (fTemp30 + fTemp31))) + (fSlow3 * ((fTemp32 + (fTemp31 + this.fRec44[2])) - fTemp30)))))));
			this.fRec0[1] = this.fRec0[0];
			this.IOTA = (this.IOTA + 1);
			this.fRec1[1] = this.fRec1[0];
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
			this.fRec43[1] = this.fRec43[0];
			this.fRec42[1] = this.fRec42[0];
			this.fRec40[1] = this.fRec40[0];
			this.fRec4[2] = this.fRec4[1];
			this.fRec4[1] = this.fRec4[0];
			this.fRec5[2] = this.fRec5[1];
			this.fRec5[1] = this.fRec5[0];
			this.fRec6[2] = this.fRec6[1];
			this.fRec6[1] = this.fRec6[0];
			this.fRec7[2] = this.fRec7[1];
			this.fRec7[1] = this.fRec7[0];
			this.fRec8[2] = this.fRec8[1];
			this.fRec8[1] = this.fRec8[0];
			this.fRec9[2] = this.fRec9[1];
			this.fRec9[1] = this.fRec9[0];
			this.fRec10[2] = this.fRec10[1];
			this.fRec10[1] = this.fRec10[0];
			this.fRec11[2] = this.fRec11[1];
			this.fRec11[1] = this.fRec11[0];
			this.fRec3[2] = this.fRec3[1];
			this.fRec3[1] = this.fRec3[0];
			this.fRec2[2] = this.fRec2[1];
			this.fRec2[1] = this.fRec2[0];
			this.fRec45[2] = this.fRec45[1];
			this.fRec45[1] = this.fRec45[0];
			this.fRec44[2] = this.fRec44[1];
			this.fRec44[1] = this.fRec44[0];
			
		}
		
	}
	
}

