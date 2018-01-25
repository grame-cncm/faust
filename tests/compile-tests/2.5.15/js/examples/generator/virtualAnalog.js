
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.mydsp_faustpower2_f = function(value) {
	return (value * value);
	
}
this.mydsp_faustpower3_f = function(value) {
	return ((value * value) * value);
	
}

function mydsp() {
	
	this.fVslider0;
	this.fHslider0;
	this.iVec0 = new Int32Array(4);
	this.fRec0 = new Float32Array(2);
	this.fVslider1;
	this.fEntry0;
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fHslider1;
	this.fVslider2;
	this.fRec2 = new Float32Array(2);
	this.fVec1 = new Float32Array(2);
	this.fRec1 = new Float32Array(2);
	this.fConst2;
	this.fVec2 = new Float32Array(2);
	this.fConst3;
	this.fVec3 = new Float32Array(2);
	this.fVec4 = new Float32Array(2);
	this.fConst4;
	this.fVec5 = new Float32Array(2);
	this.fVec6 = new Float32Array(2);
	this.fVec7 = new Float32Array(2);
	this.fVslider3;
	this.fVec8 = new Float32Array(2);
	this.fRec3 = new Float32Array(2);
	this.fVec9 = new Float32Array(2);
	this.fVec10 = new Float32Array(2);
	this.fVec11 = new Float32Array(2);
	this.fVec12 = new Float32Array(2);
	this.fVec13 = new Float32Array(2);
	this.fVec14 = new Float32Array(2);
	this.fVslider4;
	this.fVec15 = new Float32Array(2);
	this.fRec4 = new Float32Array(2);
	this.fVec16 = new Float32Array(2);
	this.fVec17 = new Float32Array(2);
	this.fVec18 = new Float32Array(2);
	this.fVec19 = new Float32Array(2);
	this.fVec20 = new Float32Array(2);
	this.fVec21 = new Float32Array(2);
	this.fConst5;
	this.fVslider5;
	this.fVec22 = new Float32Array(2);
	this.fRec5 = new Float32Array(2);
	this.fVec23 = new Float32Array(2);
	this.IOTA;
	this.fVec24 = new Float32Array(4096);
	this.fConst6;
	this.fVec25 = new Float32Array(2);
	this.fRec6 = new Float32Array(2);
	this.fVec26 = new Float32Array(2);
	this.fVec27 = new Float32Array(4096);
	this.fVec28 = new Float32Array(2);
	this.fRec7 = new Float32Array(2);
	this.fVec29 = new Float32Array(2);
	this.fVec30 = new Float32Array(4096);
	this.fConst7;
	this.fVslider6;
	this.fRec8 = new Float32Array(2);
	this.fRec9 = new Float32Array(2);
	this.fRec10 = new Float32Array(2);
	this.fVslider7;
	this.fCheckbox0;
	this.fVslider8;
	this.fRec11 = new Float32Array(2);
	this.fConst8;
	this.fVec31 = new Float32Array(2);
	this.fVec32 = new Float32Array(2);
	this.fVec33 = new Float32Array(4096);
	this.fVec34 = new Float32Array(2);
	this.fVec35 = new Float32Array(2);
	this.fVec36 = new Float32Array(4096);
	this.fVec37 = new Float32Array(2);
	this.fVec38 = new Float32Array(2);
	this.fVec39 = new Float32Array(4096);
	this.fVslider9;
	this.iRec13 = new Int32Array(2);
	this.fRec12 = new Float32Array(4);
	
	this.metadata = function(m) { 
		m.declare("author", "JOS, revised by RM");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("description", "Virtual analog oscillator demo application.");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "VirtualAnalog");
		m.declare("noises.lib/name", "Faust Noise Generator Library");
		m.declare("noises.lib/version", "0.0");
		m.declare("oscillators.lib/name", "Faust Oscillator Library");
		m.declare("oscillators.lib/version", "0.0");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
		m.declare("version", "0.0");
	}

	this.getNumInputs = function() {
		return 1;
		
	}
	this.getNumOutputs = function() {
		return 1;
		
	}
	this.getInputRate = function(channel) {
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
		this.fConst1 = (1 / this.fConst0);
		this.fConst2 = (0.25 * this.fConst0);
		this.fConst3 = (0.0416667 * mydsp_faustpower2_f(this.fConst0));
		this.fConst4 = (0.00520833 * mydsp_faustpower3_f(this.fConst0));
		this.fConst5 = (0.0833333 * this.fConst0);
		this.fConst6 = (0.5 * this.fConst0);
		this.fConst7 = (1.33333 / this.fConst0);
		this.fConst8 = (0.0138889 * this.fConst0);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fVslider0 = 0;
		this.fHslider0 = -20;
		this.fVslider1 = 1;
		this.fEntry0 = 2;
		this.fHslider1 = 49;
		this.fVslider2 = 0.1;
		this.fVslider3 = -0.1;
		this.fVslider4 = 0.1;
		this.fVslider5 = 0;
		this.fVslider6 = 0;
		this.fVslider7 = 0;
		this.fCheckbox0 = 0;
		this.fVslider8 = 0.5;
		this.fVslider9 = 0;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 4); l0 = (l0 + 1)) {
			this.iVec0[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec0[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec2[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fVec1[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec1[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fVec2[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			this.fVec3[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			this.fVec4[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			this.fVec5[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			this.fVec6[l9] = 0;
			
		}
		for (var l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			this.fVec7[l10] = 0;
			
		}
		for (var l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			this.fVec8[l11] = 0;
			
		}
		for (var l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			this.fRec3[l12] = 0;
			
		}
		for (var l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			this.fVec9[l13] = 0;
			
		}
		for (var l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			this.fVec10[l14] = 0;
			
		}
		for (var l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			this.fVec11[l15] = 0;
			
		}
		for (var l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			this.fVec12[l16] = 0;
			
		}
		for (var l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			this.fVec13[l17] = 0;
			
		}
		for (var l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			this.fVec14[l18] = 0;
			
		}
		for (var l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			this.fVec15[l19] = 0;
			
		}
		for (var l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			this.fRec4[l20] = 0;
			
		}
		for (var l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			this.fVec16[l21] = 0;
			
		}
		for (var l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			this.fVec17[l22] = 0;
			
		}
		for (var l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			this.fVec18[l23] = 0;
			
		}
		for (var l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			this.fVec19[l24] = 0;
			
		}
		for (var l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			this.fVec20[l25] = 0;
			
		}
		for (var l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			this.fVec21[l26] = 0;
			
		}
		for (var l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			this.fVec22[l27] = 0;
			
		}
		for (var l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			this.fRec5[l28] = 0;
			
		}
		for (var l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			this.fVec23[l29] = 0;
			
		}
		this.IOTA = 0;
		for (var l30 = 0; (l30 < 4096); l30 = (l30 + 1)) {
			this.fVec24[l30] = 0;
			
		}
		for (var l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			this.fVec25[l31] = 0;
			
		}
		for (var l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			this.fRec6[l32] = 0;
			
		}
		for (var l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			this.fVec26[l33] = 0;
			
		}
		for (var l34 = 0; (l34 < 4096); l34 = (l34 + 1)) {
			this.fVec27[l34] = 0;
			
		}
		for (var l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			this.fVec28[l35] = 0;
			
		}
		for (var l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			this.fRec7[l36] = 0;
			
		}
		for (var l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			this.fVec29[l37] = 0;
			
		}
		for (var l38 = 0; (l38 < 4096); l38 = (l38 + 1)) {
			this.fVec30[l38] = 0;
			
		}
		for (var l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			this.fRec8[l39] = 0;
			
		}
		for (var l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			this.fRec9[l40] = 0;
			
		}
		for (var l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			this.fRec10[l41] = 0;
			
		}
		for (var l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			this.fRec11[l42] = 0;
			
		}
		for (var l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			this.fVec31[l43] = 0;
			
		}
		for (var l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			this.fVec32[l44] = 0;
			
		}
		for (var l45 = 0; (l45 < 4096); l45 = (l45 + 1)) {
			this.fVec33[l45] = 0;
			
		}
		for (var l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			this.fVec34[l46] = 0;
			
		}
		for (var l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			this.fVec35[l47] = 0;
			
		}
		for (var l48 = 0; (l48 < 4096); l48 = (l48 + 1)) {
			this.fVec36[l48] = 0;
			
		}
		for (var l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			this.fVec37[l49] = 0;
			
		}
		for (var l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			this.fVec38[l50] = 0;
			
		}
		for (var l51 = 0; (l51 < 4096); l51 = (l51 + 1)) {
			this.fVec39[l51] = 0;
			
		}
		for (var l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			this.iRec13[l52] = 0;
			
		}
		for (var l53 = 0; (l53 < 4); l53 = (l53 + 1)) {
			this.fRec12[l53] = 0;
			
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
		ui_interface.declare("0", "tooltip", "See Faust's oscillators.lib for documentation and references");
		ui_interface.openVerticalBox("VIRTUAL ANALOG OSCILLATORS");
		ui_interface.declare("0", "0", "");
		ui_interface.openHorizontalBox("Signal Levels");
		ui_interface.declare("fVslider1", "0", "");
		ui_interface.declare("fVslider1", "style", "vslider");
		ui_interface.addVerticalSlider("Sawtooth", function handler(obj) { function setval(val) { obj.fVslider1 = val; } return setval; }(this), 1, 0, 1, 0.01);
		ui_interface.declare("0", "1", "");
		ui_interface.openVerticalBox("Pulse Train");
		ui_interface.declare("fCheckbox0", "0", "");
		ui_interface.declare("fCheckbox0", "tooltip", "When checked, use 3rd-order aliasing suppression (up from 2)  See if you can hear a difference with the freq high and swept");
		ui_interface.addCheckButton("Order 3", function handler(obj) { function setval(val) { obj.fCheckbox0 = val; } return setval; }(this));
		ui_interface.declare("fVslider7", "1", "");
		ui_interface.declare("fVslider7", "style", "vslider");
		ui_interface.addVerticalSlider("0x00", function handler(obj) { function setval(val) { obj.fVslider7 = val; } return setval; }(this), 0, 0, 1, 0.01);
		ui_interface.declare("fVslider8", "2", "");
		ui_interface.declare("fVslider8", "style", "knob");
		ui_interface.addVerticalSlider("Duty Cycle", function handler(obj) { function setval(val) { obj.fVslider8 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.closeBox();
		ui_interface.declare("fVslider5", "2", "");
		ui_interface.declare("fVslider5", "style", "vslider");
		ui_interface.addVerticalSlider("Square", function handler(obj) { function setval(val) { obj.fVslider5 = val; } return setval; }(this), 0, 0, 1, 0.01);
		ui_interface.declare("fVslider6", "3", "");
		ui_interface.declare("fVslider6", "style", "vslider");
		ui_interface.addVerticalSlider("Triangle", function handler(obj) { function setval(val) { obj.fVslider6 = val; } return setval; }(this), 0, 0, 1, 0.01);
		ui_interface.declare("fVslider9", "4", "");
		ui_interface.declare("fVslider9", "style", "vslider");
		ui_interface.declare("fVslider9", "tooltip", "Pink Noise (or 1/f noise) is   Constant-Q Noise, meaning that it has the same total power in every octave   (uses only amplitude controls)");
		ui_interface.addVerticalSlider("Pink Noise", function handler(obj) { function setval(val) { obj.fVslider9 = val; } return setval; }(this), 0, 0, 1, 0.01);
		ui_interface.declare("fVslider0", "5", "");
		ui_interface.declare("fVslider0", "style", "vslider");
		ui_interface.addVerticalSlider("Ext Input", function handler(obj) { function setval(val) { obj.fVslider0 = val; } return setval; }(this), 0, 0, 1, 0.01);
		ui_interface.closeBox();
		ui_interface.declare("0", "1", "");
		ui_interface.openHorizontalBox("Signal Parameters");
		ui_interface.declare("0", "0", "");
		ui_interface.openVerticalBox("0x00");
		ui_interface.declare("fHslider0", "1", "");
		ui_interface.declare("fHslider0", "style", "hslider");
		ui_interface.declare("fHslider0", "tooltip", "Sawtooth waveform amplitude");
		ui_interface.declare("fHslider0", "unit", "dB");
		ui_interface.addHorizontalSlider("Mix Amplitude", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), -20, -120, 10, 0.1);
		ui_interface.declare("fHslider1", "2", "");
		ui_interface.declare("fHslider1", "style", "hslider");
		ui_interface.declare("fHslider1", "tooltip", "Sawtooth   frequency as a Piano Key (PK) number (A440 = key 49)");
		ui_interface.declare("fHslider1", "unit", "PK");
		ui_interface.addHorizontalSlider("Frequency", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 49, 1, 88, 0.01);
		ui_interface.closeBox();
		ui_interface.declare("fVslider3", "3", "");
		ui_interface.declare("fVslider3", "style", "knob");
		ui_interface.declare("fVslider3", "tooltip", "Percentange frequency-shift up or down for second oscillator");
		ui_interface.declare("fVslider3", "unit", "%%");
		ui_interface.addVerticalSlider("Detuning 1", function handler(obj) { function setval(val) { obj.fVslider3 = val; } return setval; }(this), -0.1, -10, 10, 0.01);
		ui_interface.declare("fVslider4", "4", "");
		ui_interface.declare("fVslider4", "style", "knob");
		ui_interface.declare("fVslider4", "tooltip", "Percentange frequency-shift up or down for third detuned oscillator");
		ui_interface.declare("fVslider4", "unit", "%%");
		ui_interface.addVerticalSlider("Detuning 2", function handler(obj) { function setval(val) { obj.fVslider4 = val; } return setval; }(this), 0.1, -10, 10, 0.01);
		ui_interface.declare("fVslider2", "5", "");
		ui_interface.declare("fVslider2", "scale", "log");
		ui_interface.declare("fVslider2", "style", "knob");
		ui_interface.declare("fVslider2", "tooltip", "Portamento (frequency-glide) time-constant in seconds");
		ui_interface.declare("fVslider2", "unit", "sec");
		ui_interface.addVerticalSlider("Portamento", function handler(obj) { function setval(val) { obj.fVslider2 = val; } return setval; }(this), 0.1, 0.001, 10, 0.001);
		ui_interface.declare("fEntry0", "6", "");
		ui_interface.declare("fEntry0", "tooltip", "Order of sawtooth aliasing  suppression");
		ui_interface.addNumEntry("Saw Order", function handler(obj) { function setval(val) { obj.fEntry0 = val; } return setval; }(this), 2, 1, 4, 1);
		ui_interface.closeBox();
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var output0 = outputs[0];
		var fSlow0 = this.fVslider0;
		var fSlow1 = (0.001 * Math.pow(10, (0.05 * this.fHslider0)));
		var fSlow2 = (0.333333 * this.fVslider1);
		var iSlow3 = (this.fEntry0 + -1);
		var iSlow4 = (iSlow3 >= 2);
		var iSlow5 = (iSlow3 >= 1);
		var fSlow6 = Math.exp((0 - (this.fConst1 / this.fVslider2)));
		var fSlow7 = (440 * (Math.pow(2, (0.0833333 * (this.fHslider1 + -49))) * (1 - fSlow6)));
		var iSlow8 = (iSlow3 >= 3);
		var fSlow9 = (1 - (0.01 * this.fVslider3));
		var fSlow10 = ((0.01 * this.fVslider4) + 1);
		var fSlow11 = (this.fConst5 * this.fVslider5);
		var fSlow12 = (this.fConst7 * this.fVslider6);
		var fSlow13 = (this.fConst0 * this.fVslider7);
		var fSlow14 = this.fCheckbox0;
		var fSlow15 = (0.0833333 * (1 - fSlow14));
		var fSlow16 = (0.01 * this.fVslider8);
		var fSlow17 = (this.fConst8 * fSlow14);
		var fSlow18 = this.fVslider9;
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iVec0[0] = 1;
			this.fRec0[0] = (fSlow1 + (0.999 * this.fRec0[1]));
			this.fRec2[0] = (fSlow7 + (fSlow6 * this.fRec2[1]));
			var fTemp0 = max_f(20, Math.abs(this.fRec2[0]));
			this.fVec1[0] = fTemp0;
			var fTemp1 = (this.fRec1[1] + (this.fConst1 * this.fVec1[1]));
			this.fRec1[0] = (fTemp1 - Math.floor(fTemp1));
			var fTemp2 = (2 * this.fRec1[0]);
			var fTemp3 = (fTemp2 + -1);
			var fTemp4 = mydsp_faustpower2_f(fTemp3);
			this.fVec2[0] = fTemp4;
			var fTemp5 = mydsp_faustpower3_f(fTemp3);
			this.fVec3[0] = (fTemp5 + (1 - fTemp2));
			var fTemp6 = ((fTemp5 + (1 - (fTemp2 + this.fVec3[1]))) / fTemp0);
			this.fVec4[0] = fTemp6;
			var fTemp7 = (fTemp4 * (fTemp4 + -2));
			this.fVec5[0] = fTemp7;
			var fTemp8 = ((fTemp7 - this.fVec5[1]) / fTemp0);
			this.fVec6[0] = fTemp8;
			var fTemp9 = ((fTemp8 - this.fVec6[1]) / fTemp0);
			this.fVec7[0] = fTemp9;
			var fTemp10 = (fSlow9 * this.fRec2[0]);
			var fTemp11 = max_f(20, Math.abs(fTemp10));
			this.fVec8[0] = fTemp11;
			var fTemp12 = (this.fRec3[1] + (this.fConst1 * this.fVec8[1]));
			this.fRec3[0] = (fTemp12 - Math.floor(fTemp12));
			var fTemp13 = (2 * this.fRec3[0]);
			var fTemp14 = (fTemp13 + -1);
			var fTemp15 = mydsp_faustpower2_f(fTemp14);
			this.fVec9[0] = fTemp15;
			var fTemp16 = mydsp_faustpower3_f(fTemp14);
			this.fVec10[0] = (fTemp16 + (1 - fTemp13));
			var fTemp17 = ((fTemp16 + (1 - (fTemp13 + this.fVec10[1]))) / fTemp11);
			this.fVec11[0] = fTemp17;
			var fTemp18 = (fTemp15 * (fTemp15 + -2));
			this.fVec12[0] = fTemp18;
			var fTemp19 = ((fTemp18 - this.fVec12[1]) / fTemp11);
			this.fVec13[0] = fTemp19;
			var fTemp20 = ((fTemp19 - this.fVec13[1]) / fTemp11);
			this.fVec14[0] = fTemp20;
			var fTemp21 = (fSlow10 * this.fRec2[0]);
			var fTemp22 = max_f(20, Math.abs(fTemp21));
			this.fVec15[0] = fTemp22;
			var fTemp23 = (this.fRec4[1] + (this.fConst1 * this.fVec15[1]));
			this.fRec4[0] = (fTemp23 - Math.floor(fTemp23));
			var fTemp24 = (2 * this.fRec4[0]);
			var fTemp25 = (fTemp24 + -1);
			var fTemp26 = mydsp_faustpower2_f(fTemp25);
			this.fVec16[0] = fTemp26;
			var fTemp27 = mydsp_faustpower3_f(fTemp25);
			this.fVec17[0] = (fTemp27 + (1 - fTemp24));
			var fTemp28 = ((fTemp27 + (1 - (fTemp24 + this.fVec17[1]))) / fTemp22);
			this.fVec18[0] = fTemp28;
			var fTemp29 = (fTemp26 * (fTemp26 + -2));
			this.fVec19[0] = fTemp29;
			var fTemp30 = ((fTemp29 - this.fVec19[1]) / fTemp22);
			this.fVec20[0] = fTemp30;
			var fTemp31 = ((fTemp30 - this.fVec20[1]) / fTemp22);
			this.fVec21[0] = fTemp31;
			var fTemp32 = max_f(this.fRec2[0], 23.4489);
			var fTemp33 = max_f(20, Math.abs(fTemp32));
			this.fVec22[0] = fTemp33;
			var fTemp34 = (this.fRec5[1] + (this.fConst1 * this.fVec22[1]));
			this.fRec5[0] = (fTemp34 - Math.floor(fTemp34));
			var fTemp35 = (2 * this.fRec5[0]);
			var fTemp36 = (fTemp35 + -1);
			var fTemp37 = mydsp_faustpower2_f(fTemp36);
			this.fVec23[0] = fTemp37;
			var fTemp38 = ((this.iVec0[1] * (fTemp37 - this.fVec23[1])) / fTemp33);
			this.fVec24[(this.IOTA & 4095)] = fTemp38;
			var fTemp39 = max_f(0, min_f(2047, (this.fConst6 / fTemp32)));
			var iTemp40 = fTemp39;
			var fTemp41 = Math.floor(fTemp39);
			var fTemp42 = ((fTemp38 - (this.fVec24[((this.IOTA - iTemp40) & 4095)] * (fTemp41 + (1 - fTemp39)))) - ((fTemp39 - fTemp41) * this.fVec24[((this.IOTA - (iTemp40 + 1)) & 4095)]));
			var fTemp43 = max_f(fTemp10, 23.4489);
			var fTemp44 = max_f(20, Math.abs(fTemp43));
			this.fVec25[0] = fTemp44;
			var fTemp45 = (this.fRec6[1] + (this.fConst1 * this.fVec25[1]));
			this.fRec6[0] = (fTemp45 - Math.floor(fTemp45));
			var fTemp46 = (2 * this.fRec6[0]);
			var fTemp47 = (fTemp46 + -1);
			var fTemp48 = mydsp_faustpower2_f(fTemp47);
			this.fVec26[0] = fTemp48;
			var fTemp49 = ((this.iVec0[1] * (fTemp48 - this.fVec26[1])) / fTemp44);
			this.fVec27[(this.IOTA & 4095)] = fTemp49;
			var fTemp50 = max_f(0, min_f(2047, (this.fConst6 / fTemp43)));
			var iTemp51 = fTemp50;
			var fTemp52 = Math.floor(fTemp50);
			var fTemp53 = ((fTemp49 - (this.fVec27[((this.IOTA - iTemp51) & 4095)] * (fTemp52 + (1 - fTemp50)))) - ((fTemp50 - fTemp52) * this.fVec27[((this.IOTA - (iTemp51 + 1)) & 4095)]));
			var fTemp54 = max_f(fTemp21, 23.4489);
			var fTemp55 = max_f(20, Math.abs(fTemp54));
			this.fVec28[0] = fTemp55;
			var fTemp56 = (this.fRec7[1] + (this.fConst1 * this.fVec28[1]));
			this.fRec7[0] = (fTemp56 - Math.floor(fTemp56));
			var fTemp57 = (2 * this.fRec7[0]);
			var fTemp58 = (fTemp57 + -1);
			var fTemp59 = mydsp_faustpower2_f(fTemp58);
			this.fVec29[0] = fTemp59;
			var fTemp60 = ((this.iVec0[1] * (fTemp59 - this.fVec29[1])) / fTemp55);
			this.fVec30[(this.IOTA & 4095)] = fTemp60;
			var fTemp61 = max_f(0, min_f(2047, (this.fConst6 / fTemp54)));
			var iTemp62 = fTemp61;
			var fTemp63 = Math.floor(fTemp61);
			var fTemp64 = ((fTemp60 - (this.fVec30[((this.IOTA - iTemp62) & 4095)] * (fTemp63 + (1 - fTemp61)))) - ((fTemp61 - fTemp63) * this.fVec30[((this.IOTA - (iTemp62 + 1)) & 4095)]));
			this.fRec8[0] = ((this.fConst2 * fTemp42) + (0.999 * this.fRec8[1]));
			this.fRec9[0] = ((this.fConst2 * fTemp53) + (0.999 * this.fRec9[1]));
			this.fRec10[0] = ((this.fConst2 * fTemp64) + (0.999 * this.fRec10[1]));
			this.fRec11[0] = (fSlow16 + (0.99 * this.fRec11[1]));
			var fTemp65 = max_f(0, min_f(2047, (this.fConst0 * (this.fRec11[0] / fTemp32))));
			var fTemp66 = Math.floor(fTemp65);
			var fTemp67 = (fTemp66 + (1 - fTemp65));
			var iTemp68 = fTemp65;
			var fTemp69 = (fTemp65 - fTemp66);
			var iTemp70 = (iTemp68 + 1);
			var fTemp71 = max_f(0, min_f(2047, (this.fConst0 * (this.fRec11[0] / fTemp43))));
			var fTemp72 = Math.floor(fTemp71);
			var fTemp73 = (fTemp72 + (1 - fTemp71));
			var iTemp74 = fTemp71;
			var fTemp75 = (fTemp71 - fTemp72);
			var iTemp76 = (iTemp74 + 1);
			var fTemp77 = max_f(0, min_f(2047, (this.fConst0 * (this.fRec11[0] / fTemp54))));
			var fTemp78 = Math.floor(fTemp77);
			var fTemp79 = (fTemp78 + (1 - fTemp77));
			var iTemp80 = fTemp77;
			var fTemp81 = (fTemp77 - fTemp78);
			var iTemp82 = (iTemp80 + 1);
			var fTemp83 = mydsp_faustpower3_f(fTemp36);
			this.fVec31[0] = (fTemp83 + (1 - fTemp35));
			var fTemp84 = ((fTemp83 + (1 - (fTemp35 + this.fVec31[1]))) / fTemp33);
			this.fVec32[0] = fTemp84;
			var fTemp85 = ((this.iVec0[2] * (fTemp84 - this.fVec32[1])) / fTemp33);
			this.fVec33[(this.IOTA & 4095)] = fTemp85;
			var fTemp86 = mydsp_faustpower3_f(fTemp47);
			this.fVec34[0] = (fTemp86 + (1 - fTemp46));
			var fTemp87 = ((fTemp86 + (1 - (fTemp46 + this.fVec34[1]))) / fTemp44);
			this.fVec35[0] = fTemp87;
			var fTemp88 = ((this.iVec0[2] * (fTemp87 - this.fVec35[1])) / fTemp44);
			this.fVec36[(this.IOTA & 4095)] = fTemp88;
			var fTemp89 = mydsp_faustpower3_f(fTemp58);
			this.fVec37[0] = (fTemp89 + (1 - fTemp57));
			var fTemp90 = ((fTemp89 + (1 - (fTemp57 + this.fVec37[1]))) / fTemp55);
			this.fVec38[0] = fTemp90;
			var fTemp91 = ((this.iVec0[2] * (fTemp90 - this.fVec38[1])) / fTemp55);
			this.fVec39[(this.IOTA & 4095)] = fTemp91;
			this.iRec13[0] = ((1103515245 * this.iRec13[1]) + 12345);
			this.fRec12[0] = (((0.522189 * this.fRec12[3]) + ((4.65661e-10 * this.iRec13[0]) + (2.49496 * this.fRec12[1]))) - (2.01727 * this.fRec12[2]));
			output0[i] = ((fSlow0 * input0[i]) + (this.fRec0[0] * (((((fSlow2 * (((iSlow4?(iSlow8?(this.fConst4 * ((this.iVec0[3] * (fTemp9 - this.fVec7[1])) / fTemp0)):(this.fConst3 * ((this.iVec0[2] * (fTemp6 - this.fVec4[1])) / fTemp0))):(iSlow5?(this.fConst2 * ((this.iVec0[1] * (fTemp4 - this.fVec2[1])) / fTemp0)):fTemp3)) + (iSlow4?(iSlow8?(this.fConst4 * ((this.iVec0[3] * (fTemp20 - this.fVec14[1])) / fTemp11)):(this.fConst3 * ((this.iVec0[2] * (fTemp17 - this.fVec11[1])) / fTemp11))):(iSlow5?(this.fConst2 * ((this.iVec0[1] * (fTemp15 - this.fVec9[1])) / fTemp11)):fTemp14))) + (iSlow4?(iSlow8?(this.fConst4 * ((this.iVec0[3] * (fTemp31 - this.fVec21[1])) / fTemp22)):(this.fConst3 * ((this.iVec0[2] * (fTemp28 - this.fVec18[1])) / fTemp22))):(iSlow5?(this.fConst2 * ((this.iVec0[1] * (fTemp26 - this.fVec16[1])) / fTemp22)):fTemp25)))) + (fSlow11 * ((fTemp42 + fTemp53) + fTemp64))) + (fSlow12 * (this.fRec2[0] * ((this.fRec8[0] + (fSlow9 * this.fRec9[0])) + (fSlow10 * this.fRec10[0]))))) + (fSlow13 * ((fSlow15 * ((((fTemp38 - (fTemp67 * this.fVec24[((this.IOTA - iTemp68) & 4095)])) - (fTemp69 * this.fVec24[((this.IOTA - iTemp70) & 4095)])) + ((fTemp49 - (fTemp73 * this.fVec27[((this.IOTA - iTemp74) & 4095)])) - (fTemp75 * this.fVec27[((this.IOTA - iTemp76) & 4095)]))) + ((fTemp60 - (fTemp79 * this.fVec30[((this.IOTA - iTemp80) & 4095)])) - (fTemp81 * this.fVec30[((this.IOTA - iTemp82) & 4095)])))) + (fSlow17 * ((((fTemp85 - (this.fVec33[((this.IOTA - iTemp68) & 4095)] * fTemp67)) - (fTemp69 * this.fVec33[((this.IOTA - iTemp70) & 4095)])) + ((fTemp88 - (this.fVec36[((this.IOTA - iTemp74) & 4095)] * fTemp73)) - (fTemp75 * this.fVec36[((this.IOTA - iTemp76) & 4095)]))) + ((fTemp91 - (this.fVec39[((this.IOTA - iTemp80) & 4095)] * fTemp79)) - (fTemp81 * this.fVec39[((this.IOTA - iTemp82) & 4095)]))))))) + (fSlow18 * (((0.049922 * this.fRec12[0]) + (0.0506127 * this.fRec12[2])) - ((0.0959935 * this.fRec12[1]) + (0.00440879 * this.fRec12[3])))))));
			for (var j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				this.iVec0[j0] = this.iVec0[(j0 - 1)];
				
			}
			this.fRec0[1] = this.fRec0[0];
			this.fRec2[1] = this.fRec2[0];
			this.fVec1[1] = this.fVec1[0];
			this.fRec1[1] = this.fRec1[0];
			this.fVec2[1] = this.fVec2[0];
			this.fVec3[1] = this.fVec3[0];
			this.fVec4[1] = this.fVec4[0];
			this.fVec5[1] = this.fVec5[0];
			this.fVec6[1] = this.fVec6[0];
			this.fVec7[1] = this.fVec7[0];
			this.fVec8[1] = this.fVec8[0];
			this.fRec3[1] = this.fRec3[0];
			this.fVec9[1] = this.fVec9[0];
			this.fVec10[1] = this.fVec10[0];
			this.fVec11[1] = this.fVec11[0];
			this.fVec12[1] = this.fVec12[0];
			this.fVec13[1] = this.fVec13[0];
			this.fVec14[1] = this.fVec14[0];
			this.fVec15[1] = this.fVec15[0];
			this.fRec4[1] = this.fRec4[0];
			this.fVec16[1] = this.fVec16[0];
			this.fVec17[1] = this.fVec17[0];
			this.fVec18[1] = this.fVec18[0];
			this.fVec19[1] = this.fVec19[0];
			this.fVec20[1] = this.fVec20[0];
			this.fVec21[1] = this.fVec21[0];
			this.fVec22[1] = this.fVec22[0];
			this.fRec5[1] = this.fRec5[0];
			this.fVec23[1] = this.fVec23[0];
			this.IOTA = (this.IOTA + 1);
			this.fVec25[1] = this.fVec25[0];
			this.fRec6[1] = this.fRec6[0];
			this.fVec26[1] = this.fVec26[0];
			this.fVec28[1] = this.fVec28[0];
			this.fRec7[1] = this.fRec7[0];
			this.fVec29[1] = this.fVec29[0];
			this.fRec8[1] = this.fRec8[0];
			this.fRec9[1] = this.fRec9[0];
			this.fRec10[1] = this.fRec10[0];
			this.fRec11[1] = this.fRec11[0];
			this.fVec31[1] = this.fVec31[0];
			this.fVec32[1] = this.fVec32[0];
			this.fVec34[1] = this.fVec34[0];
			this.fVec35[1] = this.fVec35[0];
			this.fVec37[1] = this.fVec37[0];
			this.fVec38[1] = this.fVec38[0];
			this.iRec13[1] = this.iRec13[0];
			for (var j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				this.fRec12[j1] = this.fRec12[(j1 - 1)];
				
			}
			
		}
		
	}
	
}

