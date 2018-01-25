
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.max_i = function(dummy0, dummy1);
this.mydsp_faustpower2_f = function(value) {
	return (value * value);
	
}

function mydsp() {
	
	this.fHslider0;
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fConst2;
	this.fHslider1;
	this.fRec29 = new Float32Array(2);
	this.fHslider2;
	this.fHslider3;
	this.fButton0;
	this.fHslider4;
	this.fVec0 = new Float32Array(2);
	this.fRec30 = new Float32Array(2);
	this.fRec25 = new Float32Array(2);
	this.fRec31 = new Float32Array(2);
	this.fRec33 = new Float32Array(4);
	this.IOTA;
	this.fRec34 = new Float32Array(2048);
	this.fVec1 = new Float32Array(2);
	this.fHslider5;
	this.iRec37 = new Int32Array(2);
	this.fConst3;
	this.fRec36 = new Float32Array(3);
	this.fConst4;
	this.fVec2 = new Float32Array(2);
	this.fRec38 = new Float32Array(2);
	this.fConst5;
	this.fConst6;
	this.fVec3 = new Float32Array(3);
	this.fRec32 = new Float32Array(2048);
	this.fRec21 = new Float32Array(2);
	this.fRec17 = new Float32Array(2);
	this.fRec13 = new Float32Array(2048);
	this.fRec15 = new Float32Array(2);
	this.fRec11 = new Float32Array(4);
	this.fRec6 = new Float32Array(2);
	this.fRec2 = new Float32Array(2048);
	this.fRec0 = new Float32Array(2);
	
	this.metadata = function(m) { 
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("description", "Simple electric guitar model without effect chain.");
		m.declare("envelopes.lib/author", "GRAME");
		m.declare("envelopes.lib/copyright", "GRAME");
		m.declare("envelopes.lib/license", "LGPL with exception");
		m.declare("envelopes.lib/name", "Faust Envelope Library");
		m.declare("envelopes.lib/version", "0.0");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("license", "MIT");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "ElecGuitarMidi");
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
		this.fConst2 = (0.00147059 * this.fConst0);
		this.fConst3 = (15.708 / this.fConst0);
		this.fConst4 = (0.004 * this.fConst0);
		this.fConst5 = (0.002 * this.fConst0);
		this.fConst6 = (500 / this.fConst0);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 0.5;
		this.fHslider1 = 0.8;
		this.fHslider2 = 440;
		this.fHslider3 = 1;
		this.fButton0 = 0;
		this.fHslider4 = 0;
		this.fHslider5 = 0.8;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.fRec29[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fVec0[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec30[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec25[l3] = 0;
			
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
		for (var l13 = 0; (l13 < 2048); l13 = (l13 + 1)) {
			this.fRec32[l13] = 0;
			
		}
		for (var l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			this.fRec21[l14] = 0;
			
		}
		for (var l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			this.fRec17[l15] = 0;
			
		}
		for (var l16 = 0; (l16 < 2048); l16 = (l16 + 1)) {
			this.fRec13[l16] = 0;
			
		}
		for (var l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			this.fRec15[l17] = 0;
			
		}
		for (var l18 = 0; (l18 < 4); l18 = (l18 + 1)) {
			this.fRec11[l18] = 0;
			
		}
		for (var l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			this.fRec6[l19] = 0;
			
		}
		for (var l20 = 0; (l20 < 2048); l20 = (l20 + 1)) {
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
		ui_interface.declare("0", "0", "");
		ui_interface.openHorizontalBox("midi");
		ui_interface.declare("fHslider2", "0", "");
		ui_interface.declare("fHslider2", "style", "knob");
		ui_interface.addHorizontalSlider("freq", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 440, 50, 1000, 0.01);
		ui_interface.declare("fHslider3", "1", "");
		ui_interface.declare("fHslider3", "hidden", "1");
		ui_interface.declare("fHslider3", "midi", "pitchwheel");
		ui_interface.declare("fHslider3", "style", "knob");
		ui_interface.addHorizontalSlider("bend", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 1, 0, 10, 0.01);
		ui_interface.declare("fHslider5", "2", "");
		ui_interface.declare("fHslider5", "style", "knob");
		ui_interface.addHorizontalSlider("gain", function handler(obj) { function setval(val) { obj.fHslider5 = val; } return setval; }(this), 0.8, 0, 1, 0.01);
		ui_interface.declare("fHslider4", "3", "");
		ui_interface.declare("fHslider4", "hidden", "1");
		ui_interface.declare("fHslider4", "midi", "ctrl 64");
		ui_interface.declare("fHslider4", "style", "knob");
		ui_interface.addHorizontalSlider("sustain", function handler(obj) { function setval(val) { obj.fHslider4 = val; } return setval; }(this), 0, 0, 1, 1);
		ui_interface.closeBox();
		ui_interface.declare("fHslider1", "1", "");
		ui_interface.declare("fHslider1", "midi", "ctrl 1");
		ui_interface.addHorizontalSlider("pluckPosition", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 0.8, 0, 1, 0.01);
		ui_interface.declare("fHslider0", "2", "");
		ui_interface.addHorizontalSlider("outGain", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.declare("fButton0", "3", "");
		ui_interface.addButton("gate", function handler(obj) { function setval(val) { obj.fButton0 = val; } return setval; }(this));
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = this.fHslider0;
		var fSlow1 = (0.001 * this.fHslider1);
		var fSlow2 = this.fHslider2;
		var fSlow3 = (340 / fSlow2);
		var fSlow4 = this.fHslider3;
		var fSlow5 = min_f(1, (this.fButton0 + this.fHslider4));
		var iSlow6 = (fSlow5 == 0);
		var fSlow7 = this.fHslider5;
		var fSlow8 = (this.fConst3 * fSlow2);
		var fSlow9 = (0.0005 * fSlow2);
		for (var i = 0; (i < count); i = (i + 1)) {
			var fRec10 = (0 - (0.997305 * ((0.9 * this.fRec11[2]) + (0.05 * (this.fRec11[1] + this.fRec11[3])))));
			this.fRec29[0] = (fSlow1 + (0.999 * this.fRec29[1]));
			this.fVec0[0] = fSlow5;
			var iTemp0 = ((fSlow5 == this.fVec0[1]) | iSlow6);
			this.fRec30[0] = ((fSlow4 * (1 - (0.999 * iTemp0))) + (0.999 * (iTemp0 * this.fRec30[1])));
			var fTemp1 = ((fSlow3 / this.fRec30[0]) + -0.11);
			var fTemp2 = (this.fConst2 * ((1 - this.fRec29[0]) * fTemp1));
			var fTemp3 = (fTemp2 + -1.49999);
			var iTemp4 = fTemp3;
			var iTemp5 = min_f(this.fConst1, max_i(0, iTemp4));
			var fTemp6 = Math.floor(fTemp3);
			var fTemp7 = (fTemp2 + (-1 - fTemp6));
			var fTemp8 = (0 - fTemp7);
			var fTemp9 = (fTemp2 + (-2 - fTemp6));
			var fTemp10 = (0 - (0.5 * fTemp9));
			var fTemp11 = (fTemp2 + (-3 - fTemp6));
			var fTemp12 = (0 - (0.333333 * fTemp11));
			var fTemp13 = (fTemp2 + (-4 - fTemp6));
			var fTemp14 = (0 - (0.25 * fTemp13));
			var fTemp15 = (fTemp2 - fTemp6);
			var iTemp16 = min_f(this.fConst1, max_i(0, (iTemp4 + 2)));
			var fTemp17 = (0 - fTemp11);
			var fTemp18 = (0 - (0.5 * fTemp13));
			var iTemp19 = min_f(this.fConst1, max_i(0, (iTemp4 + 1)));
			var fTemp20 = (0 - fTemp9);
			var fTemp21 = (0 - (0.5 * fTemp11));
			var fTemp22 = (0 - (0.333333 * fTemp13));
			var fTemp23 = (fTemp7 * fTemp9);
			var iTemp24 = min_f(this.fConst1, max_i(0, (iTemp4 + 3)));
			var fTemp25 = (0 - fTemp13);
			var fTemp26 = (fTemp23 * fTemp11);
			var iTemp27 = min_f(this.fConst1, max_i(0, (iTemp4 + 4)));
			this.fRec25[0] = (((((this.fRec2[((this.IOTA - (iTemp5 + 1)) & 2047)] * fTemp8) * fTemp10) * fTemp12) * fTemp14) + (fTemp15 * ((((0.5 * (((fTemp7 * this.fRec2[((this.IOTA - (iTemp16 + 1)) & 2047)]) * fTemp17) * fTemp18)) + (((this.fRec2[((this.IOTA - (iTemp19 + 1)) & 2047)] * fTemp20) * fTemp21) * fTemp22)) + (0.166667 * ((fTemp23 * this.fRec2[((this.IOTA - (iTemp24 + 1)) & 2047)]) * fTemp25))) + (0.0416667 * (fTemp26 * this.fRec2[((this.IOTA - (iTemp27 + 1)) & 2047)])))));
			this.fRec31[0] = ((0.05 * this.fRec31[1]) + (0.95 * this.fRec25[1]));
			var fRec26 = this.fRec31[0];
			this.fRec33[0] = this.fRec0[1];
			this.fRec34[(this.IOTA & 2047)] = (0 - (0.997305 * ((0.9 * this.fRec33[2]) + (0.05 * (this.fRec33[1] + this.fRec33[3])))));
			var iRec35 = 0;
			var fTemp28 = (this.fConst2 * (this.fRec29[0] * fTemp1));
			var fTemp29 = (fTemp28 + -1.49999);
			var iTemp30 = fTemp29;
			var iTemp31 = min_f(this.fConst1, max_i(0, iTemp30));
			var fTemp32 = Math.floor(fTemp29);
			var fTemp33 = (fTemp28 + (-1 - fTemp32));
			var fTemp34 = (0 - fTemp33);
			var fTemp35 = (fTemp28 + (-2 - fTemp32));
			var fTemp36 = (0 - (0.5 * fTemp35));
			var fTemp37 = (fTemp28 + (-3 - fTemp32));
			var fTemp38 = (0 - (0.333333 * fTemp37));
			var fTemp39 = (fTemp28 + (-4 - fTemp32));
			var fTemp40 = (0 - (0.25 * fTemp39));
			var fTemp41 = (fTemp28 - fTemp32);
			var iTemp42 = min_f(this.fConst1, max_i(0, (iTemp30 + 2)));
			var fTemp43 = (0 - fTemp37);
			var fTemp44 = (0 - (0.5 * fTemp39));
			var iTemp45 = min_f(this.fConst1, max_i(0, (iTemp30 + 1)));
			var fTemp46 = (0 - fTemp35);
			var fTemp47 = (0 - (0.5 * fTemp37));
			var fTemp48 = (0 - (0.333333 * fTemp39));
			var fTemp49 = (fTemp33 * fTemp35);
			var iTemp50 = min_f(this.fConst1, max_i(0, (iTemp30 + 3)));
			var fTemp51 = (0 - fTemp39);
			var fTemp52 = (fTemp49 * fTemp37);
			var iTemp53 = min_f(this.fConst1, max_i(0, (iTemp30 + 4)));
			this.fVec1[0] = (((((this.fRec34[((this.IOTA - (iTemp31 + 2)) & 2047)] * fTemp34) * fTemp36) * fTemp38) * fTemp40) + (fTemp41 * ((((0.5 * (((fTemp33 * this.fRec34[((this.IOTA - (iTemp42 + 2)) & 2047)]) * fTemp43) * fTemp44)) + (((this.fRec34[((this.IOTA - (iTemp45 + 2)) & 2047)] * fTemp46) * fTemp47) * fTemp48)) + (0.166667 * ((fTemp49 * this.fRec34[((this.IOTA - (iTemp50 + 2)) & 2047)]) * fTemp51))) + (0.0416667 * (fTemp52 * this.fRec34[((this.IOTA - (iTemp53 + 2)) & 2047)])))));
			this.iRec37[0] = ((1103515245 * this.iRec37[1]) + 12345);
			var fTemp54 = Math.tan((fSlow8 * this.fRec30[0]));
			var fTemp55 = (1 / fTemp54);
			var fTemp56 = (((fTemp55 + 1.41421) / fTemp54) + 1);
			this.fRec36[0] = ((4.65661e-10 * this.iRec37[0]) - (((this.fRec36[2] * (((fTemp55 + -1.41421) / fTemp54) + 1)) + (2 * (this.fRec36[1] * (1 - (1 / mydsp_faustpower2_f(fTemp54)))))) / fTemp56));
			var fTemp57 = mydsp_faustpower2_f((1 - (fSlow9 * this.fRec30[0])));
			this.fVec2[0] = fTemp57;
			var fTemp58 = (this.fConst4 * fTemp57);
			this.fRec38[0] = ((((fSlow5 - this.fVec0[1]) > 0) > 0)?0:min_f(fTemp58, ((this.fRec38[1] + (this.fConst4 * (fTemp57 - this.fVec2[1]))) + 1)));
			var fTemp59 = (this.fConst5 * fTemp57);
			var iTemp60 = (this.fRec38[0] < fTemp59);
			var fTemp61 = (fSlow7 * (((this.fRec36[2] + (this.fRec36[0] + (2 * this.fRec36[1]))) * (iTemp60?((this.fRec38[0] < 0)?0:(iTemp60?(this.fConst6 * (this.fRec38[0] / fTemp57)):1)):((this.fRec38[0] < fTemp58)?((this.fConst6 * ((0 - (this.fRec38[0] - fTemp59)) / fTemp57)) + 1):0))) / fTemp56));
			var fTemp62 = (this.fVec1[1] + fTemp61);
			this.fVec3[0] = fTemp62;
			this.fRec32[(this.IOTA & 2047)] = ((0.05 * this.fRec32[((this.IOTA - 1) & 2047)]) + (0.95 * this.fVec3[2]));
			var fRec27 = (((((fTemp8 * fTemp10) * fTemp12) * fTemp14) * this.fRec32[((this.IOTA - iTemp5) & 2047)]) + (fTemp15 * ((0.0416667 * (fTemp26 * this.fRec32[((this.IOTA - iTemp27) & 2047)])) + (((((fTemp20 * fTemp21) * fTemp22) * this.fRec32[((this.IOTA - iTemp19) & 2047)]) + (0.5 * (((fTemp7 * fTemp17) * fTemp18) * this.fRec32[((this.IOTA - iTemp16) & 2047)]))) + (0.166667 * ((fTemp23 * fTemp25) * this.fRec32[((this.IOTA - iTemp24) & 2047)]))))));
			var fRec28 = (this.fRec21[1] + (iRec35 + this.fVec3[1]));
			this.fRec21[0] = fRec26;
			var fRec22 = this.fRec21[1];
			var fRec23 = fRec27;
			var fRec24 = fRec28;
			this.fRec17[0] = fRec22;
			var fRec18 = (fTemp61 + this.fRec17[1]);
			var fRec19 = fRec23;
			var fRec20 = fRec24;
			this.fRec13[(this.IOTA & 2047)] = fRec18;
			var fRec14 = (((((fTemp34 * fTemp36) * fTemp38) * fTemp40) * this.fRec13[((this.IOTA - (iTemp31 + 1)) & 2047)]) + (fTemp41 * (((0.166667 * ((fTemp49 * fTemp51) * this.fRec13[((this.IOTA - (iTemp50 + 1)) & 2047)])) + ((((fTemp46 * fTemp47) * fTemp48) * this.fRec13[((this.IOTA - (iTemp45 + 1)) & 2047)]) + (0.5 * (((fTemp33 * fTemp43) * fTemp44) * this.fRec13[((this.IOTA - (iTemp42 + 1)) & 2047)])))) + (0.0416667 * (fTemp52 * this.fRec13[((this.IOTA - (iTemp53 + 1)) & 2047)])))));
			this.fRec15[0] = fRec19;
			var fRec16 = fRec20;
			this.fRec11[0] = this.fRec15[1];
			var fRec12 = fRec16;
			this.fRec6[0] = fRec10;
			var fRec7 = this.fRec6[1];
			var fRec8 = this.fRec11[0];
			var fRec9 = fRec12;
			this.fRec2[(this.IOTA & 2047)] = fRec7;
			var fRec3 = fRec14;
			var fRec4 = fRec8;
			var fRec5 = fRec9;
			this.fRec0[0] = fRec3;
			var fRec1 = fRec5;
			var fTemp63 = (fSlow0 * fRec1);
			output0[i] = fTemp63;
			output1[i] = fTemp63;
			this.fRec29[1] = this.fRec29[0];
			this.fVec0[1] = this.fVec0[0];
			this.fRec30[1] = this.fRec30[0];
			this.fRec25[1] = this.fRec25[0];
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
			this.fRec21[1] = this.fRec21[0];
			this.fRec17[1] = this.fRec17[0];
			this.fRec15[1] = this.fRec15[0];
			for (var j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				this.fRec11[j1] = this.fRec11[(j1 - 1)];
				
			}
			this.fRec6[1] = this.fRec6[0];
			this.fRec0[1] = this.fRec0[0];
			
		}
		
	}
	
}

