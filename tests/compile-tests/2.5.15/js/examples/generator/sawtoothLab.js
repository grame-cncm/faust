
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
	this.iVec0 = new Int32Array(4);
	this.fRec0 = new Float32Array(2);
	this.fCheckbox0;
	this.fCheckbox1;
	this.fEntry0;
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fVslider1;
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
	this.fCheckbox2;
	this.iRec5 = new Int32Array(2);
	this.fRec6 = new Float32Array(4);
	
	this.metadata = function(m) { 
		m.declare("author", "JOS, revised by RM");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("description", "An application demonstrating the different sawtooth oscillators of Faust.");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "sawtoothLab");
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
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fVslider0 = -20;
		this.fCheckbox0 = 0;
		this.fCheckbox1 = 0;
		this.fEntry0 = 2;
		this.fVslider1 = 49;
		this.fVslider2 = 0.1;
		this.fVslider3 = -0.1;
		this.fVslider4 = 0.1;
		this.fCheckbox2 = 0;
		
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
			this.iRec5[l27] = 0;
			
		}
		for (var l28 = 0; (l28 < 4); l28 = (l28 + 1)) {
			this.fRec6[l28] = 0;
			
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
		ui_interface.declare("0", "tooltip", "See Faust's oscillators.lib   for documentation and references");
		ui_interface.openVerticalBox("SAWTOOTH OSCILLATOR");
		ui_interface.declare("0", "1", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fVslider0", "1", "");
		ui_interface.declare("fVslider0", "style", "knob");
		ui_interface.declare("fVslider0", "tooltip", "Sawtooth   waveform amplitude");
		ui_interface.declare("fVslider0", "unit", "dB");
		ui_interface.addVerticalSlider("Amplitude", function handler(obj) { function setval(val) { obj.fVslider0 = val; } return setval; }(this), -20, -120, 10, 0.1);
		ui_interface.declare("fVslider1", "2", "");
		ui_interface.declare("fVslider1", "style", "knob");
		ui_interface.declare("fVslider1", "tooltip", "Sawtooth   frequency as a Piano Key (PK) number (A440 = key 49)");
		ui_interface.declare("fVslider1", "unit", "PK");
		ui_interface.addVerticalSlider("Frequency", function handler(obj) { function setval(val) { obj.fVslider1 = val; } return setval; }(this), 49, 1, 88, 0.01);
		ui_interface.declare("fVslider3", "3", "");
		ui_interface.declare("fVslider3", "style", "knob");
		ui_interface.declare("fVslider3", "tooltip", "Percentange frequency-shift  up or down for second oscillator");
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
		ui_interface.declare("fEntry0", "tooltip", "Order of sawtootn aliasing   suppression");
		ui_interface.addNumEntry("Saw Order", function handler(obj) { function setval(val) { obj.fEntry0 = val; } return setval; }(this), 2, 1, 4, 1);
		ui_interface.declare("0", "7", "");
		ui_interface.openVerticalBox("Alternate Signals");
		ui_interface.declare("fCheckbox1", "0", "");
		ui_interface.addCheckButton("Noise (White or Pink - uses only Amplitude control on   the left)", function handler(obj) { function setval(val) { obj.fCheckbox1 = val; } return setval; }(this));
		ui_interface.declare("fCheckbox2", "1", "");
		ui_interface.declare("fCheckbox2", "tooltip", "Pink Noise (or 1/f noise) is Constant-Q Noise, meaning that it has the   same total power in every octave");
		ui_interface.addCheckButton("Pink instead of White Noise (also called 1/f Noise)", function handler(obj) { function setval(val) { obj.fCheckbox2 = val; } return setval; }(this));
		ui_interface.declare("fCheckbox0", "2", "");
		ui_interface.addCheckButton("External Signal Input (overrides Sawtooth/Noise   selection above)", function handler(obj) { function setval(val) { obj.fCheckbox0 = val; } return setval; }(this));
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var output0 = outputs[0];
		var fSlow0 = (0.001 * Math.pow(10, (0.05 * this.fVslider0)));
		var iSlow1 = this.fCheckbox0;
		var iSlow2 = this.fCheckbox1;
		var iSlow3 = (this.fEntry0 + -1);
		var iSlow4 = (iSlow3 >= 2);
		var iSlow5 = (iSlow3 >= 1);
		var fSlow6 = Math.exp((0 - (this.fConst1 / this.fVslider2)));
		var fSlow7 = (440 * (Math.pow(2, (0.0833333 * (this.fVslider1 + -49))) * (1 - fSlow6)));
		var iSlow8 = (iSlow3 >= 3);
		var fSlow9 = ((0.01 * this.fVslider3) + 1);
		var fSlow10 = ((0.01 * this.fVslider4) + 1);
		var iSlow11 = this.fCheckbox2;
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iVec0[0] = 1;
			this.fRec0[0] = (fSlow0 + (0.999 * this.fRec0[1]));
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
			var fTemp10 = max_f(20, Math.abs((fSlow9 * this.fRec2[0])));
			this.fVec8[0] = fTemp10;
			var fTemp11 = (this.fRec3[1] + (this.fConst1 * this.fVec8[1]));
			this.fRec3[0] = (fTemp11 - Math.floor(fTemp11));
			var fTemp12 = (2 * this.fRec3[0]);
			var fTemp13 = (fTemp12 + -1);
			var fTemp14 = mydsp_faustpower2_f(fTemp13);
			this.fVec9[0] = fTemp14;
			var fTemp15 = mydsp_faustpower3_f(fTemp13);
			this.fVec10[0] = (fTemp15 + (1 - fTemp12));
			var fTemp16 = ((fTemp15 + (1 - (fTemp12 + this.fVec10[1]))) / fTemp10);
			this.fVec11[0] = fTemp16;
			var fTemp17 = (fTemp14 * (fTemp14 + -2));
			this.fVec12[0] = fTemp17;
			var fTemp18 = ((fTemp17 - this.fVec12[1]) / fTemp10);
			this.fVec13[0] = fTemp18;
			var fTemp19 = ((fTemp18 - this.fVec13[1]) / fTemp10);
			this.fVec14[0] = fTemp19;
			var fTemp20 = max_f(20, Math.abs((fSlow10 * this.fRec2[0])));
			this.fVec15[0] = fTemp20;
			var fTemp21 = (this.fRec4[1] + (this.fConst1 * this.fVec15[1]));
			this.fRec4[0] = (fTemp21 - Math.floor(fTemp21));
			var fTemp22 = (2 * this.fRec4[0]);
			var fTemp23 = (fTemp22 + -1);
			var fTemp24 = mydsp_faustpower2_f(fTemp23);
			this.fVec16[0] = fTemp24;
			var fTemp25 = mydsp_faustpower3_f(fTemp23);
			this.fVec17[0] = (fTemp25 + (1 - fTemp22));
			var fTemp26 = ((fTemp25 + (1 - (fTemp22 + this.fVec17[1]))) / fTemp20);
			this.fVec18[0] = fTemp26;
			var fTemp27 = (fTemp24 * (fTemp24 + -2));
			this.fVec19[0] = fTemp27;
			var fTemp28 = ((fTemp27 - this.fVec19[1]) / fTemp20);
			this.fVec20[0] = fTemp28;
			var fTemp29 = ((fTemp28 - this.fVec20[1]) / fTemp20);
			this.fVec21[0] = fTemp29;
			this.iRec5[0] = ((1103515245 * this.iRec5[1]) + 12345);
			var fTemp30 = (4.65661e-10 * this.iRec5[0]);
			this.fRec6[0] = (((0.522189 * this.fRec6[3]) + (fTemp30 + (2.49496 * this.fRec6[1]))) - (2.01727 * this.fRec6[2]));
			output0[i] = (this.fRec0[0] * (iSlow1?input0[i]:(iSlow2?(iSlow11?(((0.049922 * this.fRec6[0]) + (0.0506127 * this.fRec6[2])) - ((0.0959935 * this.fRec6[1]) + (0.00440879 * this.fRec6[3]))):fTemp30):(0.333333 * (this.fRec0[0] * (((iSlow4?(iSlow8?(this.fConst4 * ((this.iVec0[3] * (fTemp9 - this.fVec7[1])) / fTemp0)):(this.fConst3 * ((this.iVec0[2] * (fTemp6 - this.fVec4[1])) / fTemp0))):(iSlow5?(this.fConst2 * ((this.iVec0[1] * (fTemp4 - this.fVec2[1])) / fTemp0)):fTemp3)) + (iSlow4?(iSlow8?(this.fConst4 * ((this.iVec0[3] * (fTemp19 - this.fVec14[1])) / fTemp10)):(this.fConst3 * ((this.iVec0[2] * (fTemp16 - this.fVec11[1])) / fTemp10))):(iSlow5?(this.fConst2 * ((this.iVec0[1] * (fTemp14 - this.fVec9[1])) / fTemp10)):fTemp13))) + (iSlow4?(iSlow8?(this.fConst4 * ((this.iVec0[3] * (fTemp29 - this.fVec21[1])) / fTemp20)):(this.fConst3 * ((this.iVec0[2] * (fTemp26 - this.fVec18[1])) / fTemp20))):(iSlow5?(this.fConst2 * ((this.iVec0[1] * (fTemp24 - this.fVec16[1])) / fTemp20)):fTemp23))))))));
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
			this.iRec5[1] = this.iRec5[0];
			for (var j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				this.fRec6[j1] = this.fRec6[(j1 - 1)];
				
			}
			
		}
		
	}
	
}

