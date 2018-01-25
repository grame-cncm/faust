
this.min_f = function(dummy0, dummy1);
this.max_f = function(dummy0, dummy1);
this.max_i = function(dummy0, dummy1);
this.mydsp_faustpower2_f = function(value) {
	return (value * value);
	
}

function mydsp() {
	
	this.fButton0;
	this.fHslider0;
	this.fVec0 = new Float32Array(2);
	this.fRec13 = new Float32Array(2);
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fConst2;
	this.fHslider1;
	this.fHslider2;
	this.fRec30 = new Float32Array(2);
	this.fRec26 = new Float32Array(2);
	this.fRec31 = new Float32Array(2);
	this.fRec33 = new Float32Array(4);
	this.IOTA;
	this.fRec34 = new Float32Array(2048);
	this.fConst3;
	this.fVec1 = new Float32Array(2);
	this.fHslider3;
	this.iRec37 = new Int32Array(2);
	this.fConst4;
	this.fRec36 = new Float32Array(3);
	this.fConst5;
	this.fVec2 = new Float32Array(2);
	this.fRec38 = new Float32Array(2);
	this.fConst6;
	this.fConst7;
	this.fVec3 = new Float32Array(3);
	this.fRec32 = new Float32Array(512);
	this.fRec22 = new Float32Array(2);
	this.fRec18 = new Float32Array(2);
	this.fRec14 = new Float32Array(2048);
	this.fRec16 = new Float32Array(2);
	this.fRec11 = new Float32Array(4);
	this.fRec6 = new Float32Array(2);
	this.fRec2 = new Float32Array(512);
	this.fRec0 = new Float32Array(2);
	
	this.metadata = function(m) { 
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("envelopes.lib/author", "GRAME");
		m.declare("envelopes.lib/copyright", "GRAME");
		m.declare("envelopes.lib/license", "LGPL with exception");
		m.declare("envelopes.lib/name", "Faust Envelope Library");
		m.declare("envelopes.lib/version", "0.0");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("interface", "SmartKeyboard{  'Number of Keyboards':'6',  'Max Keyboard Polyphony':'1',  'Keyboard 0 - Number of Keys':'13',  'Keyboard 1 - Number of Keys':'13',  'Keyboard 2 - Number of Keys':'13',  'Keyboard 3 - Number of Keys':'13',  'Keyboard 4 - Number of Keys':'13',  'Keyboard 5 - Number of Keys':'13',  'Keyboard 0 - Lowest Key':'72',  'Keyboard 1 - Lowest Key':'67',  'Keyboard 2 - Lowest Key':'62',  'Keyboard 3 - Lowest Key':'57',  'Keyboard 4 - Lowest Key':'52',  'Keyboard 5 - Lowest Key':'47',  'Rounding Mode':'2' }");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "elecGuitar");
		m.declare("noises.lib/name", "Faust Noise Generator Library");
		m.declare("noises.lib/version", "0.0");
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
		this.fConst1 = (0.00882353 * this.fConst0);
		this.fConst2 = (0.000294118 * this.fConst0);
		this.fConst3 = (0.00117647 * this.fConst0);
		this.fConst4 = (15.708 / this.fConst0);
		this.fConst5 = (0.004 * this.fConst0);
		this.fConst6 = (0.002 * this.fConst0);
		this.fConst7 = (500 / this.fConst0);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fButton0 = 0;
		this.fHslider0 = 0;
		this.fHslider1 = 300;
		this.fHslider2 = 1;
		this.fHslider3 = 1;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.fVec0[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec13[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec30[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec26[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec31[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 4); l5 = (l5 + 1)) {
			this.fRec33[l5] = 0;
			
		}
		this.IOTA = 0;
		for (var l6 = 0; (l6 < 2048); l6 = (l6 + 1)) {
			this.fRec34[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			this.fVec1[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			this.iRec37[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 3); l9 = (l9 + 1)) {
			this.fRec36[l9] = 0;
			
		}
		for (var l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			this.fVec2[l10] = 0;
			
		}
		for (var l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			this.fRec38[l11] = 0;
			
		}
		for (var l12 = 0; (l12 < 3); l12 = (l12 + 1)) {
			this.fVec3[l12] = 0;
			
		}
		for (var l13 = 0; (l13 < 512); l13 = (l13 + 1)) {
			this.fRec32[l13] = 0;
			
		}
		for (var l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			this.fRec22[l14] = 0;
			
		}
		for (var l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			this.fRec18[l15] = 0;
			
		}
		for (var l16 = 0; (l16 < 2048); l16 = (l16 + 1)) {
			this.fRec14[l16] = 0;
			
		}
		for (var l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			this.fRec16[l17] = 0;
			
		}
		for (var l18 = 0; (l18 < 4); l18 = (l18 + 1)) {
			this.fRec11[l18] = 0;
			
		}
		for (var l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			this.fRec6[l19] = 0;
			
		}
		for (var l20 = 0; (l20 < 512); l20 = (l20 + 1)) {
			this.fRec2[l20] = 0;
			
		}
		for (var l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			this.fRec0[l21] = 0;
			
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
		ui_interface.openVerticalBox("elecGuitar");
		ui_interface.declare("fHslider2", "midi", "pitchwheel");
		ui_interface.addHorizontalSlider("bend", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 1, 0, 10, 0.01);
		ui_interface.addHorizontalSlider("freq", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 300, 50, 2000, 0.01);
		ui_interface.addHorizontalSlider("gain", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 1, 0, 1, 0.01);
		ui_interface.addButton("gate", function handler(obj) { function setval(val) { obj.fButton0 = val; } return setval; }(this));
		ui_interface.declare("fHslider0", "midi", "ctrl 64");
		ui_interface.addHorizontalSlider("sustain", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0, 0, 1, 1);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = min_f(1, (this.fButton0 + this.fHslider0));
		var iSlow1 = (fSlow0 == 0);
		var fSlow2 = this.fHslider1;
		var fSlow3 = this.fHslider2;
		var fSlow4 = this.fHslider3;
		for (var i = 0; (i < count); i = (i + 1)) {
			var fRec10 = (0 - (0.997305 * ((0.9 * this.fRec11[2]) + (0.05 * (this.fRec11[1] + this.fRec11[3])))));
			this.fVec0[0] = fSlow0;
			var iTemp0 = ((fSlow0 == this.fVec0[1]) | iSlow1);
			var fTemp1 = (1 - (0.999 * iTemp0));
			this.fRec13[0] = ((fSlow0 * fTemp1) + (0.999 * (iTemp0 * this.fRec13[1])));
			this.fRec30[0] = ((fSlow3 * fTemp1) + (0.999 * (iTemp0 * this.fRec30[1])));
			var fTemp2 = max_f(60, (fSlow2 * this.fRec30[0]));
			var fTemp3 = ((340 / fTemp2) + -0.11);
			var fTemp4 = (this.fConst2 * fTemp3);
			var fTemp5 = (fTemp4 + -1.49999);
			var iTemp6 = fTemp5;
			var iTemp7 = min_f(this.fConst1, max_i(0, iTemp6));
			var fTemp8 = Math.floor(fTemp5);
			var fTemp9 = (fTemp4 + (-1 - fTemp8));
			var fTemp10 = (0 - fTemp9);
			var fTemp11 = (fTemp4 + (-2 - fTemp8));
			var fTemp12 = (0 - (0.5 * fTemp11));
			var fTemp13 = (fTemp4 + (-3 - fTemp8));
			var fTemp14 = (0 - (0.333333 * fTemp13));
			var fTemp15 = (fTemp4 + (-4 - fTemp8));
			var fTemp16 = (0 - (0.25 * fTemp15));
			var fTemp17 = (fTemp4 - fTemp8);
			var iTemp18 = min_f(this.fConst1, max_i(0, (iTemp6 + 2)));
			var fTemp19 = (0 - fTemp13);
			var fTemp20 = (0 - (0.5 * fTemp15));
			var iTemp21 = min_f(this.fConst1, max_i(0, (iTemp6 + 1)));
			var fTemp22 = (0 - fTemp11);
			var fTemp23 = (0 - (0.5 * fTemp13));
			var fTemp24 = (0 - (0.333333 * fTemp15));
			var fTemp25 = (fTemp9 * fTemp11);
			var iTemp26 = min_f(this.fConst1, max_i(0, (iTemp6 + 3)));
			var fTemp27 = (0 - fTemp15);
			var fTemp28 = (fTemp25 * fTemp13);
			var iTemp29 = min_f(this.fConst1, max_i(0, (iTemp6 + 4)));
			this.fRec26[0] = (((((this.fRec2[((this.IOTA - (iTemp7 + 1)) & 511)] * fTemp10) * fTemp12) * fTemp14) * fTemp16) + (fTemp17 * ((((0.5 * (((fTemp9 * this.fRec2[((this.IOTA - (iTemp18 + 1)) & 511)]) * fTemp19) * fTemp20)) + (((this.fRec2[((this.IOTA - (iTemp21 + 1)) & 511)] * fTemp22) * fTemp23) * fTemp24)) + (0.166667 * ((fTemp25 * this.fRec2[((this.IOTA - (iTemp26 + 1)) & 511)]) * fTemp27))) + (0.0416667 * (fTemp28 * this.fRec2[((this.IOTA - (iTemp29 + 1)) & 511)])))));
			this.fRec31[0] = ((0.05 * this.fRec31[1]) + (0.95 * this.fRec26[1]));
			var fRec27 = this.fRec31[0];
			this.fRec33[0] = this.fRec0[1];
			this.fRec34[(this.IOTA & 2047)] = (0 - (0.997305 * ((0.9 * this.fRec33[2]) + (0.05 * (this.fRec33[1] + this.fRec33[3])))));
			var iRec35 = 0;
			var fTemp30 = (this.fConst3 * fTemp3);
			var fTemp31 = (fTemp30 + -1.49999);
			var iTemp32 = fTemp31;
			var iTemp33 = min_f(this.fConst1, max_i(0, iTemp32));
			var fTemp34 = Math.floor(fTemp31);
			var fTemp35 = (fTemp30 + (-1 - fTemp34));
			var fTemp36 = (0 - fTemp35);
			var fTemp37 = (fTemp30 + (-2 - fTemp34));
			var fTemp38 = (0 - (0.5 * fTemp37));
			var fTemp39 = (fTemp30 + (-3 - fTemp34));
			var fTemp40 = (0 - (0.333333 * fTemp39));
			var fTemp41 = (fTemp30 + (-4 - fTemp34));
			var fTemp42 = (0 - (0.25 * fTemp41));
			var fTemp43 = (fTemp30 - fTemp34);
			var iTemp44 = min_f(this.fConst1, max_i(0, (iTemp32 + 2)));
			var fTemp45 = (0 - fTemp39);
			var fTemp46 = (0 - (0.5 * fTemp41));
			var iTemp47 = min_f(this.fConst1, max_i(0, (iTemp32 + 1)));
			var fTemp48 = (0 - fTemp37);
			var fTemp49 = (0 - (0.5 * fTemp39));
			var fTemp50 = (0 - (0.333333 * fTemp41));
			var fTemp51 = (fTemp35 * fTemp37);
			var iTemp52 = min_f(this.fConst1, max_i(0, (iTemp32 + 3)));
			var fTemp53 = (0 - fTemp41);
			var fTemp54 = (fTemp51 * fTemp39);
			var iTemp55 = min_f(this.fConst1, max_i(0, (iTemp32 + 4)));
			this.fVec1[0] = (((((this.fRec34[((this.IOTA - (iTemp33 + 2)) & 2047)] * fTemp36) * fTemp38) * fTemp40) * fTemp42) + (fTemp43 * ((((0.5 * (((fTemp35 * this.fRec34[((this.IOTA - (iTemp44 + 2)) & 2047)]) * fTemp45) * fTemp46)) + (((this.fRec34[((this.IOTA - (iTemp47 + 2)) & 2047)] * fTemp48) * fTemp49) * fTemp50)) + (0.166667 * ((fTemp51 * this.fRec34[((this.IOTA - (iTemp52 + 2)) & 2047)]) * fTemp53))) + (0.0416667 * (fTemp54 * this.fRec34[((this.IOTA - (iTemp55 + 2)) & 2047)])))));
			this.iRec37[0] = ((1103515245 * this.iRec37[1]) + 12345);
			var fTemp56 = Math.tan((this.fConst4 * fTemp2));
			var fTemp57 = (1 / fTemp56);
			var fTemp58 = (((fTemp57 + 1.41421) / fTemp56) + 1);
			this.fRec36[0] = ((4.65661e-10 * this.iRec37[0]) - (((this.fRec36[2] * (((fTemp57 + -1.41421) / fTemp56) + 1)) + (2 * (this.fRec36[1] * (1 - (1 / mydsp_faustpower2_f(fTemp56)))))) / fTemp58));
			var fTemp59 = mydsp_faustpower2_f((1 - (0.0005 * fTemp2)));
			this.fVec2[0] = fTemp59;
			var fTemp60 = (this.fConst5 * fTemp59);
			this.fRec38[0] = ((((fSlow0 - this.fVec0[1]) > 0) > 0)?0:min_f(fTemp60, ((this.fRec38[1] + (this.fConst5 * (fTemp59 - this.fVec2[1]))) + 1)));
			var fTemp61 = (this.fConst6 * fTemp59);
			var iTemp62 = (this.fRec38[0] < fTemp61);
			var fTemp63 = (fSlow4 * (((this.fRec36[2] + (this.fRec36[0] + (2 * this.fRec36[1]))) * (iTemp62?((this.fRec38[0] < 0)?0:(iTemp62?(this.fConst7 * (this.fRec38[0] / fTemp59)):1)):((this.fRec38[0] < fTemp60)?((this.fConst7 * ((0 - (this.fRec38[0] - fTemp61)) / fTemp59)) + 1):0))) / fTemp58));
			var fTemp64 = (this.fVec1[1] + fTemp63);
			this.fVec3[0] = fTemp64;
			this.fRec32[(this.IOTA & 511)] = ((0.05 * this.fRec32[((this.IOTA - 1) & 511)]) + (0.95 * this.fVec3[2]));
			var fRec28 = (((((fTemp10 * fTemp12) * fTemp14) * fTemp16) * this.fRec32[((this.IOTA - iTemp7) & 511)]) + (fTemp17 * ((0.0416667 * (fTemp28 * this.fRec32[((this.IOTA - iTemp29) & 511)])) + (((((fTemp22 * fTemp23) * fTemp24) * this.fRec32[((this.IOTA - iTemp21) & 511)]) + (0.5 * (((fTemp9 * fTemp19) * fTemp20) * this.fRec32[((this.IOTA - iTemp18) & 511)]))) + (0.166667 * ((fTemp25 * fTemp27) * this.fRec32[((this.IOTA - iTemp26) & 511)]))))));
			var fRec29 = (this.fRec22[1] + (iRec35 + this.fVec3[1]));
			this.fRec22[0] = fRec27;
			var fRec23 = this.fRec22[1];
			var fRec24 = fRec28;
			var fRec25 = fRec29;
			this.fRec18[0] = fRec23;
			var fRec19 = (fTemp63 + this.fRec18[1]);
			var fRec20 = fRec24;
			var fRec21 = fRec25;
			this.fRec14[(this.IOTA & 2047)] = fRec19;
			var fRec15 = (((((fTemp36 * fTemp38) * fTemp40) * fTemp42) * this.fRec14[((this.IOTA - (iTemp33 + 1)) & 2047)]) + (fTemp43 * (((0.166667 * ((fTemp51 * fTemp53) * this.fRec14[((this.IOTA - (iTemp52 + 1)) & 2047)])) + ((((fTemp48 * fTemp49) * fTemp50) * this.fRec14[((this.IOTA - (iTemp47 + 1)) & 2047)]) + (0.5 * (((fTemp35 * fTemp45) * fTemp46) * this.fRec14[((this.IOTA - (iTemp44 + 1)) & 2047)])))) + (0.0416667 * (fTemp54 * this.fRec14[((this.IOTA - (iTemp55 + 1)) & 2047)])))));
			this.fRec16[0] = fRec20;
			var fRec17 = fRec21;
			this.fRec11[0] = (this.fRec13[0] * this.fRec16[1]);
			var fRec12 = fRec17;
			this.fRec6[0] = fRec10;
			var fRec7 = (this.fRec13[0] * this.fRec6[1]);
			var fRec8 = this.fRec11[0];
			var fRec9 = fRec12;
			this.fRec2[(this.IOTA & 511)] = fRec7;
			var fRec3 = fRec15;
			var fRec4 = fRec8;
			var fRec5 = fRec9;
			this.fRec0[0] = fRec3;
			var fRec1 = fRec5;
			output0[i] = fRec1;
			output1[i] = fRec1;
			this.fVec0[1] = this.fVec0[0];
			this.fRec13[1] = this.fRec13[0];
			this.fRec30[1] = this.fRec30[0];
			this.fRec26[1] = this.fRec26[0];
			this.fRec31[1] = this.fRec31[0];
			for (var j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				this.fRec33[j0] = this.fRec33[(j0 - 1)];
				
			}
			this.IOTA = (this.IOTA + 1);
			this.fVec1[1] = this.fVec1[0];
			this.iRec37[1] = this.iRec37[0];
			this.fRec36[2] = this.fRec36[1];
			this.fRec36[1] = this.fRec36[0];
			this.fVec2[1] = this.fVec2[0];
			this.fRec38[1] = this.fRec38[0];
			this.fVec3[2] = this.fVec3[1];
			this.fVec3[1] = this.fVec3[0];
			this.fRec22[1] = this.fRec22[0];
			this.fRec18[1] = this.fRec18[0];
			this.fRec16[1] = this.fRec16[0];
			for (var j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				this.fRec11[j1] = this.fRec11[(j1 - 1)];
				
			}
			this.fRec6[1] = this.fRec6[0];
			this.fRec0[1] = this.fRec0[0];
			
		}
		
	}
	
}

