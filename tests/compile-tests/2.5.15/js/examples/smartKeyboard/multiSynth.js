
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.mydsp_faustpower2_f = function(value) {
	return (value * value);
	
}

function mydsp() {
	
	this.fHslider0;
	this.iVec0 = new Int32Array(2);
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fHslider1;
	this.fHslider2;
	this.fButton0;
	this.fHslider3;
	this.fVec1 = new Float32Array(2);
	this.fRec2 = new Float32Array(2);
	this.fConst2;
	this.fConst3;
	this.fVec2 = new Float32Array(2);
	this.fRec4 = new Float32Array(2);
	this.fVec3 = new Float32Array(2);
	this.IOTA;
	this.fVec4 = new Float32Array(4096);
	this.fConst4;
	this.fRec3 = new Float32Array(2);
	this.fConst5;
	this.fRec5 = new Float32Array(2);
	this.fRec6 = new Float32Array(2);
	this.fConst6;
	this.fRec7 = new Float32Array(2);
	this.fVec5 = new Float32Array(2);
	this.fConst7;
	this.fHslider4;
	this.fRec9 = new Float32Array(2);
	this.fRec1 = new Float32Array(2);
	this.fRec0 = new Float32Array(3);
	this.fHslider5;
	this.fRec10 = new Float32Array(2);
	
	this.metadata = function(m) { 
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("interface", "SmartKeyboard{  'Number of Keyboards':'4',  'Rounding Mode':'2',  'Inter-Keyboard Slide':'0',  'Keyboard 0 - Number of Keys':'13',  'Keyboard 1 - Number of Keys':'13',  'Keyboard 2 - Number of Keys':'13',  'Keyboard 3 - Number of Keys':'13',  'Keyboard 0 - Lowest Key':'60',  'Keyboard 1 - Lowest Key':'60',  'Keyboard 2 - Lowest Key':'60',  'Keyboard 3 - Lowest Key':'60',  'Keyboard 0 - Send Y':'1',  'Keyboard 1 - Send Y':'1',  'Keyboard 2 - Send Y':'1',  'Keyboard 3 - Send Y':'1' }");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "multiSynth");
		m.declare("oscillators.lib/name", "Faust Oscillator Library");
		m.declare("oscillators.lib/version", "0.0");
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
		this.fConst1 = (4 / this.fConst0);
		this.fConst2 = (0.25 * this.fConst0);
		this.fConst3 = (1 / this.fConst0);
		this.fConst4 = (0.5 * this.fConst0);
		this.fConst5 = (6.28319 / this.fConst0);
		this.fConst6 = (1 / this.fConst0);
		this.fConst7 = (3.14159 / this.fConst0);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 0;
		this.fHslider1 = 300;
		this.fHslider2 = 1;
		this.fButton0 = 0;
		this.fHslider3 = 0;
		this.fHslider4 = 1;
		this.fHslider5 = 1;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.iVec0[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fVec1[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec2[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fVec2[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec4[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fVec3[l5] = 0;
			
		}
		this.IOTA = 0;
		for (var l6 = 0; (l6 < 4096); l6 = (l6 + 1)) {
			this.fVec4[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			this.fRec3[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			this.fRec5[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			this.fRec6[l9] = 0;
			
		}
		for (var l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			this.fRec7[l10] = 0;
			
		}
		for (var l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			this.fVec5[l11] = 0;
			
		}
		for (var l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			this.fRec9[l12] = 0;
			
		}
		for (var l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			this.fRec1[l13] = 0;
			
		}
		for (var l14 = 0; (l14 < 3); l14 = (l14 + 1)) {
			this.fRec0[l14] = 0;
			
		}
		for (var l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			this.fRec10[l15] = 0;
			
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
		ui_interface.openVerticalBox("multiSynth");
		ui_interface.declare("fHslider2", "midi", "pitchwheel");
		ui_interface.addHorizontalSlider("bend", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 1, 0, 10, 0.01);
		ui_interface.addHorizontalSlider("freq", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 300, 50, 2000, 0.01);
		ui_interface.addHorizontalSlider("gain", function handler(obj) { function setval(val) { obj.fHslider5 = val; } return setval; }(this), 1, 0, 1, 0.01);
		ui_interface.addButton("gate", function handler(obj) { function setval(val) { obj.fButton0 = val; } return setval; }(this));
		ui_interface.addHorizontalSlider("keyboard", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0, 0, 3, 1);
		ui_interface.declare("fHslider3", "midi", "ctrl 64");
		ui_interface.addHorizontalSlider("sustain", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 0, 0, 1, 1);
		ui_interface.declare("fHslider4", "midi", "ctrl 1");
		ui_interface.addHorizontalSlider("y", function handler(obj) { function setval(val) { obj.fHslider4 = val; } return setval; }(this), 1, 0, 1, 0.001);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var output0 = outputs[0];
		var output1 = outputs[1];
		var iSlow0 = this.fHslider0;
		var iSlow1 = (iSlow0 == 1);
		var fSlow2 = this.fHslider1;
		var fSlow3 = (this.fConst1 * fSlow2);
		var fSlow4 = this.fHslider2;
		var fSlow5 = min_f(1, (this.fButton0 + this.fHslider3));
		var iSlow6 = (fSlow5 == 0);
		var iSlow7 = (iSlow0 == 2);
		var iSlow8 = (iSlow0 == 3);
		var fSlow9 = (this.fConst5 * fSlow2);
		var iSlow10 = (iSlow0 == 0);
		var fSlow11 = (0.001 * this.fHslider4);
		var fSlow12 = (0.001 * (fSlow5 * this.fHslider5));
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iVec0[0] = 1;
			this.fVec1[0] = fSlow5;
			var iTemp0 = ((fSlow5 == this.fVec1[1]) | iSlow6);
			this.fRec2[0] = ((fSlow4 * (1 - (0.999 * iTemp0))) + (0.999 * (iTemp0 * this.fRec2[1])));
			var fTemp1 = (fSlow2 * this.fRec2[0]);
			var fTemp2 = max_f(fTemp1, 23.4489);
			var fTemp3 = max_f(20, Math.abs(fTemp2));
			this.fVec2[0] = fTemp3;
			var fTemp4 = (this.fRec4[1] + (this.fConst3 * this.fVec2[1]));
			this.fRec4[0] = (fTemp4 - Math.floor(fTemp4));
			var fTemp5 = mydsp_faustpower2_f(((2 * this.fRec4[0]) + -1));
			this.fVec3[0] = fTemp5;
			var fTemp6 = ((this.iVec0[1] * (fTemp5 - this.fVec3[1])) / fTemp3);
			this.fVec4[(this.IOTA & 4095)] = fTemp6;
			var fTemp7 = max_f(0, min_f(2047, (this.fConst4 / fTemp2)));
			var iTemp8 = fTemp7;
			var fTemp9 = Math.floor(fTemp7);
			var fTemp10 = (this.fConst2 * ((fTemp6 - (this.fVec4[((this.IOTA - iTemp8) & 4095)] * (fTemp9 + (1 - fTemp7)))) - ((fTemp7 - fTemp9) * this.fVec4[((this.IOTA - (iTemp8 + 1)) & 4095)])));
			this.fRec3[0] = ((0.999 * this.fRec3[1]) + fTemp10);
			var fTemp11 = (fSlow9 * this.fRec2[0]);
			var fTemp12 = Math.sin(fTemp11);
			var fTemp13 = Math.cos(fTemp11);
			this.fRec5[0] = ((this.fRec6[1] * fTemp12) + (this.fRec5[1] * fTemp13));
			this.fRec6[0] = (((this.fRec6[1] * fTemp13) + (this.fRec5[1] * (0 - fTemp12))) + (1 - this.iVec0[1]));
			var fTemp14 = max_f(1e-07, Math.abs(fTemp1));
			var fTemp15 = (this.fRec7[1] + (this.fConst6 * fTemp14));
			var fTemp16 = (fTemp15 + -1);
			var iTemp17 = (fTemp16 < 0);
			this.fRec7[0] = (iTemp17?fTemp15:fTemp16);
			var fRec8 = (iTemp17?fTemp15:(fTemp15 + ((1 - (this.fConst0 / fTemp14)) * fTemp16)));
			var fTemp18 = ((((iSlow1?(fSlow3 * (this.fRec2[0] * this.fRec3[0])):0) + (iSlow7?fTemp10:0)) + (iSlow8?this.fRec5[0]:0)) + (iSlow10?((2 * fRec8) + -1):0));
			this.fVec5[0] = fTemp18;
			this.fRec9[0] = (fSlow11 + (0.999 * this.fRec9[1]));
			var fTemp19 = Math.tan((this.fConst7 * ((4000 * this.fRec9[0]) + 50)));
			var fTemp20 = (1 / fTemp19);
			var fTemp21 = (fTemp20 + 1);
			this.fRec1[0] = (((fTemp18 + this.fVec5[1]) / fTemp21) + (this.fRec1[1] * (0 - ((1 - fTemp20) / fTemp21))));
			var fTemp22 = (((fTemp20 + 1) / fTemp19) + 1);
			this.fRec0[0] = (this.fRec1[0] - (((this.fRec0[2] * (((fTemp20 + -1) / fTemp19) + 1)) + (2 * (this.fRec0[1] * (1 - (1 / mydsp_faustpower2_f(fTemp19)))))) / fTemp22));
			this.fRec10[0] = (fSlow12 + (0.999 * this.fRec10[1]));
			var fTemp23 = (((this.fRec0[2] + ((2 * this.fRec0[1]) + this.fRec0[0])) * this.fRec10[0]) / fTemp22);
			output0[i] = fTemp23;
			output1[i] = fTemp23;
			this.iVec0[1] = this.iVec0[0];
			this.fVec1[1] = this.fVec1[0];
			this.fRec2[1] = this.fRec2[0];
			this.fVec2[1] = this.fVec2[0];
			this.fRec4[1] = this.fRec4[0];
			this.fVec3[1] = this.fVec3[0];
			this.IOTA = (this.IOTA + 1);
			this.fRec3[1] = this.fRec3[0];
			this.fRec5[1] = this.fRec5[0];
			this.fRec6[1] = this.fRec6[0];
			this.fRec7[1] = this.fRec7[0];
			this.fVec5[1] = this.fVec5[0];
			this.fRec9[1] = this.fRec9[0];
			this.fRec1[1] = this.fRec1[0];
			this.fRec0[2] = this.fRec0[1];
			this.fRec0[1] = this.fRec0[0];
			this.fRec10[1] = this.fRec10[0];
			
		}
		
	}
	
}

