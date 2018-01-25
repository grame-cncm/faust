
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.mydsp_faustpower2_f = function(value) {
	return (value * value);
	
}
this.max_i = function(dummy0, dummy1);

function mydsp() {
	
	this.fHslider0;
	this.iRec6 = new Int32Array(2);
	this.fHslider1;
	this.iVec0 = new Int32Array(2);
	this.fRec13 = new Float32Array(2);
	this.fHslider2;
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fHslider3;
	this.fRec17 = new Float32Array(2);
	this.fRec18 = new Float32Array(2);
	this.fHslider4;
	this.fRec19 = new Float32Array(2);
	this.fHslider5;
	this.fConst2;
	this.fHslider6;
	this.iRec21 = new Int32Array(2);
	this.fRec20 = new Float32Array(3);
	this.fRec14 = new Float32Array(2);
	this.fHslider7;
	this.IOTA;
	this.fRec15 = new Float32Array(2048);
	this.fConst3;
	this.fConst4;
	this.fHslider8;
	this.fRec22 = new Float32Array(2);
	this.fVec1 = new Float32Array(2);
	this.fRec11 = new Float32Array(2);
	this.fRec2 = new Float32Array(2048);
	this.fRec0 = new Float32Array(2);
	
	this.metadata = function(m) { 
		m.declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("description", "Simple clarinet physical model with physical parameters.");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("license", "MIT");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "Clarinet");
		m.declare("noises.lib/name", "Faust Noise Generator Library");
		m.declare("noises.lib/version", "0.0");
		m.declare("oscillators.lib/name", "Faust Oscillator Library");
		m.declare("oscillators.lib/version", "0.0");
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
		this.fConst1 = (6.28319 / this.fConst0);
		this.fConst2 = (3.14159 / this.fConst0);
		this.fConst3 = (0.00882353 * this.fConst0);
		this.fConst4 = (0.00147059 * this.fConst0);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 0.5;
		this.fHslider1 = 0.5;
		this.fHslider2 = 0.25;
		this.fHslider3 = 5;
		this.fHslider4 = 0;
		this.fHslider5 = 0.1;
		this.fHslider6 = 2000;
		this.fHslider7 = 0.5;
		this.fHslider8 = 0.8;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.iRec6[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.iVec0[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec13[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec17[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec18[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fRec19[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			this.iRec21[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			this.fRec20[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			this.fRec14[l8] = 0;
			
		}
		this.IOTA = 0;
		for (var l9 = 0; (l9 < 2048); l9 = (l9 + 1)) {
			this.fRec15[l9] = 0;
			
		}
		for (var l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			this.fRec22[l10] = 0;
			
		}
		for (var l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			this.fVec1[l11] = 0;
			
		}
		for (var l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			this.fRec11[l12] = 0;
			
		}
		for (var l13 = 0; (l13 < 2048); l13 = (l13 + 1)) {
			this.fRec2[l13] = 0;
			
		}
		for (var l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			this.fRec0[l14] = 0;
			
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
		ui_interface.openHorizontalBox("clarinet");
		ui_interface.openVerticalBox("blower");
		ui_interface.declare("fHslider4", "0", "");
		ui_interface.addHorizontalSlider("pressure", function handler(obj) { function setval(val) { obj.fHslider4 = val; } return setval; }(this), 0, 0, 1, 0.01);
		ui_interface.declare("fHslider5", "1", "");
		ui_interface.addHorizontalSlider("breathGain", function handler(obj) { function setval(val) { obj.fHslider5 = val; } return setval; }(this), 0.1, 0, 1, 0.01);
		ui_interface.declare("fHslider6", "2", "");
		ui_interface.addHorizontalSlider("breathCutoff", function handler(obj) { function setval(val) { obj.fHslider6 = val; } return setval; }(this), 2000, 20, 20000, 0.1);
		ui_interface.declare("fHslider3", "3", "");
		ui_interface.addHorizontalSlider("vibratoFreq", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 5, 0.1, 10, 0.1);
		ui_interface.declare("fHslider2", "4", "");
		ui_interface.addHorizontalSlider("vibratoGain", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 0.25, 0, 1, 0.01);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("clarinetModel");
		ui_interface.declare("fHslider8", "0", "");
		ui_interface.addHorizontalSlider("tubeLength", function handler(obj) { function setval(val) { obj.fHslider8 = val; } return setval; }(this), 0.8, 0.01, 3, 0.01);
		ui_interface.declare("fHslider7", "1", "");
		ui_interface.addHorizontalSlider("reedStiffness", function handler(obj) { function setval(val) { obj.fHslider7 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.declare("fHslider1", "2", "");
		ui_interface.addHorizontalSlider("bellOpening", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.declare("fHslider0", "3", "");
		ui_interface.addHorizontalSlider("outGain", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.closeBox();
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = this.fHslider0;
		var fSlow1 = this.fHslider1;
		var fSlow2 = (1 - fSlow1);
		var fSlow3 = (0.03 * this.fHslider2);
		var fSlow4 = (this.fConst1 * this.fHslider3);
		var fSlow5 = Math.sin(fSlow4);
		var fSlow6 = Math.cos(fSlow4);
		var fSlow7 = (0 - fSlow5);
		var fSlow8 = (0.001 * this.fHslider4);
		var fSlow9 = Math.tan((this.fConst2 * this.fHslider6));
		var fSlow10 = (1 / fSlow9);
		var fSlow11 = (((fSlow10 + 1.41421) / fSlow9) + 1);
		var fSlow12 = (0.05 * (this.fHslider5 / fSlow11));
		var fSlow13 = (1 / fSlow11);
		var fSlow14 = (((fSlow10 + -1.41421) / fSlow9) + 1);
		var fSlow15 = (2 * (1 - (1 / mydsp_faustpower2_f(fSlow9))));
		var fSlow16 = ((0.26 * this.fHslider7) + -0.44);
		var fSlow17 = (0.001 * this.fHslider8);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iRec6[0] = 0;
			this.iVec0[0] = 1;
			this.fRec13[0] = ((fSlow1 * this.fRec13[1]) + (fSlow2 * this.fRec11[1]));
			var fRec10 = (this.fRec13[0] + this.iRec6[1]);
			this.fRec17[0] = ((fSlow5 * this.fRec18[1]) + (fSlow6 * this.fRec17[1]));
			this.fRec18[0] = (((fSlow6 * this.fRec18[1]) + (fSlow7 * this.fRec17[1])) + (1 - this.iVec0[1]));
			var fTemp0 = (fSlow3 * this.fRec17[0]);
			this.fRec19[0] = (fSlow8 + (0.999 * this.fRec19[1]));
			this.iRec21[0] = ((1103515245 * this.iRec21[1]) + 12345);
			this.fRec20[0] = ((4.65661e-10 * this.iRec21[0]) - (fSlow13 * ((fSlow14 * this.fRec20[2]) + (fSlow15 * this.fRec20[1]))));
			var fTemp1 = (this.fRec19[0] * ((fSlow12 * (this.fRec20[2] + (this.fRec20[0] + (2 * this.fRec20[1])))) + 1));
			this.fRec14[0] = ((this.fRec0[1] + fTemp0) + fTemp1);
			var fTemp2 = (0 - this.fRec14[1]);
			this.fRec15[(this.IOTA & 2047)] = ((fTemp0 + fTemp1) + (fTemp2 * max_f(-1, min_f(1, ((fSlow16 * fTemp2) + 0.7)))));
			var iRec16 = 0;
			this.fRec22[0] = (fSlow17 + (0.999 * this.fRec22[1]));
			var fTemp3 = (this.fConst4 * ((0.5 * this.fRec22[0]) + -0.05));
			var fTemp4 = (fTemp3 + -1.49999);
			var iTemp5 = fTemp4;
			var iTemp6 = (min_f(this.fConst3, max_i(0, iTemp5)) + 1);
			var fTemp7 = Math.floor(fTemp4);
			var fTemp8 = (fTemp3 + (-1 - fTemp7));
			var fTemp9 = (0 - fTemp8);
			var fTemp10 = (fTemp3 + (-2 - fTemp7));
			var fTemp11 = (0 - (0.5 * fTemp10));
			var fTemp12 = (fTemp3 + (-3 - fTemp7));
			var fTemp13 = (0 - (0.333333 * fTemp12));
			var fTemp14 = (fTemp3 + (-4 - fTemp7));
			var fTemp15 = (0 - (0.25 * fTemp14));
			var fTemp16 = (fTemp3 - fTemp7);
			var iTemp17 = (min_f(this.fConst3, max_i(0, (iTemp5 + 2))) + 1);
			var fTemp18 = (0 - fTemp12);
			var fTemp19 = (0 - (0.5 * fTemp14));
			var iTemp20 = (min_f(this.fConst3, max_i(0, (iTemp5 + 1))) + 1);
			var fTemp21 = (0 - fTemp10);
			var fTemp22 = (0 - (0.5 * fTemp12));
			var fTemp23 = (0 - (0.333333 * fTemp14));
			var fTemp24 = (fTemp8 * fTemp10);
			var iTemp25 = (min_f(this.fConst3, max_i(0, (iTemp5 + 3))) + 1);
			var fTemp26 = (0 - fTemp14);
			var fTemp27 = (fTemp24 * fTemp12);
			var iTemp28 = (min_f(this.fConst3, max_i(0, (iTemp5 + 4))) + 1);
			this.fVec1[0] = (((((this.fRec15[((this.IOTA - iTemp6) & 2047)] * fTemp9) * fTemp11) * fTemp13) * fTemp15) + (fTemp16 * ((((0.5 * (((fTemp8 * this.fRec15[((this.IOTA - iTemp17) & 2047)]) * fTemp18) * fTemp19)) + (((this.fRec15[((this.IOTA - iTemp20) & 2047)] * fTemp21) * fTemp22) * fTemp23)) + (0.166667 * ((fTemp24 * this.fRec15[((this.IOTA - iTemp25) & 2047)]) * fTemp26))) + (0.0416667 * (fTemp27 * this.fRec15[((this.IOTA - iTemp28) & 2047)])))));
			this.fRec11[0] = this.fVec1[1];
			var iRec12 = iRec16;
			var fRec7 = fRec10;
			var fRec8 = this.fRec11[0];
			var fRec9 = (this.fRec11[0] + iRec12);
			this.fRec2[(this.IOTA & 2047)] = fRec7;
			var fRec3 = (((((fTemp9 * fTemp11) * fTemp13) * fTemp15) * this.fRec2[((this.IOTA - iTemp6) & 2047)]) + (fTemp16 * (((0.166667 * ((fTemp24 * fTemp26) * this.fRec2[((this.IOTA - iTemp25) & 2047)])) + ((((fTemp21 * fTemp22) * fTemp23) * this.fRec2[((this.IOTA - iTemp20) & 2047)]) + (0.5 * (((fTemp8 * fTemp18) * fTemp19) * this.fRec2[((this.IOTA - iTemp17) & 2047)])))) + (0.0416667 * (fTemp27 * this.fRec2[((this.IOTA - iTemp28) & 2047)])))));
			var fRec4 = fRec8;
			var fRec5 = fRec9;
			this.fRec0[0] = fRec3;
			var fRec1 = fRec5;
			var fTemp29 = (fSlow0 * fRec1);
			output0[i] = fTemp29;
			output1[i] = fTemp29;
			this.iRec6[1] = this.iRec6[0];
			this.iVec0[1] = this.iVec0[0];
			this.fRec13[1] = this.fRec13[0];
			this.fRec17[1] = this.fRec17[0];
			this.fRec18[1] = this.fRec18[0];
			this.fRec19[1] = this.fRec19[0];
			this.iRec21[1] = this.iRec21[0];
			this.fRec20[2] = this.fRec20[1];
			this.fRec20[1] = this.fRec20[0];
			this.fRec14[1] = this.fRec14[0];
			this.IOTA = (this.IOTA + 1);
			this.fRec22[1] = this.fRec22[0];
			this.fVec1[1] = this.fVec1[0];
			this.fRec11[1] = this.fRec11[0];
			this.fRec0[1] = this.fRec0[0];
			
		}
		
	}
	
}

