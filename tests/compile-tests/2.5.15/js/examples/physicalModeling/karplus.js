
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.max_i = function(dummy0, dummy1);

function mydsp() {
	
	this.fHslider0;
	this.fRec11 = new Float32Array(2);
	this.IOTA;
	this.fRec7 = new Float32Array(2048);
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fConst2;
	this.fHslider1;
	this.fHslider2;
	this.fButton0;
	this.fHslider3;
	this.fVec0 = new Float32Array(2);
	this.fRec12 = new Float32Array(2);
	this.fHslider4;
	this.fVec1 = new Float32Array(2048);
	this.fRec3 = new Float32Array(2);
	this.fRec0 = new Float32Array(3);
	this.fRec1 = new Float32Array(3);
	
	this.metadata = function(m) { 
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("description", "Simple call of the Karplus-Strong model for the Faust physical modeling library");
		m.declare("license", "MIT");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "KarplusStrong");
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
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 0.01;
		this.fHslider1 = 440;
		this.fHslider2 = 1;
		this.fButton0 = 0;
		this.fHslider3 = 0;
		this.fHslider4 = 0.8;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.fRec11[l0] = 0;
			
		}
		this.IOTA = 0;
		for (var l1 = 0; (l1 < 2048); l1 = (l1 + 1)) {
			this.fRec7[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fVec0[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec12[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2048); l4 = (l4 + 1)) {
			this.fVec1[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fRec3[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 3); l6 = (l6 + 1)) {
			this.fRec0[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			this.fRec1[l7] = 0;
			
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
		ui_interface.openVerticalBox("karplus");
		ui_interface.declare("0", "0", "");
		ui_interface.openHorizontalBox("params");
		ui_interface.declare("fHslider1", "0", "");
		ui_interface.declare("fHslider1", "style", "knob");
		ui_interface.addHorizontalSlider("freq", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 440, 50, 1000, 0.01);
		ui_interface.declare("fHslider2", "1", "");
		ui_interface.declare("fHslider2", "hidden", "1");
		ui_interface.declare("fHslider2", "midi", "pitchwheel");
		ui_interface.declare("fHslider2", "style", "knob");
		ui_interface.addHorizontalSlider("bend", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 1, 0, 10, 0.01);
		ui_interface.declare("fHslider0", "1", "");
		ui_interface.declare("fHslider0", "midi", "ctrl 1");
		ui_interface.declare("fHslider0", "style", "knob");
		ui_interface.addHorizontalSlider("damping", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0.01, 0, 1, 0.01);
		ui_interface.declare("fHslider4", "2", "");
		ui_interface.declare("fHslider4", "style", "knob");
		ui_interface.addHorizontalSlider("gain", function handler(obj) { function setval(val) { obj.fHslider4 = val; } return setval; }(this), 0.8, 0, 1, 0.01);
		ui_interface.declare("fHslider3", "3", "");
		ui_interface.declare("fHslider3", "hidden", "1");
		ui_interface.declare("fHslider3", "midi", "ctrl 64");
		ui_interface.declare("fHslider3", "style", "knob");
		ui_interface.addHorizontalSlider("sustain", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 0, 0, 1, 1);
		ui_interface.closeBox();
		ui_interface.declare("fButton0", "1", "");
		ui_interface.addButton("gate", function handler(obj) { function setval(val) { obj.fButton0 = val; } return setval; }(this));
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = (0.001 * this.fHslider0);
		var fSlow1 = (340 / this.fHslider1);
		var fSlow2 = this.fHslider2;
		var fSlow3 = min_f(1, (this.fButton0 + this.fHslider3));
		var iSlow4 = (fSlow3 == 0);
		var fSlow5 = this.fHslider4;
		for (var i = 0; (i < count); i = (i + 1)) {
			this.fRec11[0] = (fSlow0 + (0.999 * this.fRec11[1]));
			var fTemp0 = (0.5 * ((this.fRec1[1] + this.fRec1[2]) * ((0.2 * (1 - this.fRec11[0])) + 0.8)));
			this.fRec7[(this.IOTA & 2047)] = fTemp0;
			this.fVec0[0] = fSlow3;
			var iTemp1 = ((fSlow3 == this.fVec0[1]) | iSlow4);
			this.fRec12[0] = ((fSlow2 * (1 - (0.999 * iTemp1))) + (0.999 * (iTemp1 * this.fRec12[1])));
			var fTemp2 = (this.fConst2 * ((fSlow1 / this.fRec12[0]) + -0.05));
			var fTemp3 = (fTemp2 + -1.49999);
			var iTemp4 = fTemp3;
			var iTemp5 = (min_f(this.fConst1, max_i(0, iTemp4)) + 1);
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
			var iTemp16 = (min_f(this.fConst1, max_i(0, (iTemp4 + 2))) + 1);
			var fTemp17 = (0 - fTemp11);
			var fTemp18 = (0 - (0.5 * fTemp13));
			var iTemp19 = (min_f(this.fConst1, max_i(0, (iTemp4 + 1))) + 1);
			var fTemp20 = (0 - fTemp9);
			var fTemp21 = (0 - (0.5 * fTemp11));
			var fTemp22 = (0 - (0.333333 * fTemp13));
			var fTemp23 = (fTemp7 * fTemp9);
			var iTemp24 = (min_f(this.fConst1, max_i(0, (iTemp4 + 3))) + 1);
			var fTemp25 = (0 - fTemp13);
			var fTemp26 = (fTemp23 * fTemp11);
			var iTemp27 = (min_f(this.fConst1, max_i(0, (iTemp4 + 4))) + 1);
			var fRec8 = (((((this.fRec7[((this.IOTA - iTemp5) & 2047)] * fTemp8) * fTemp10) * fTemp12) * fTemp14) + (fTemp15 * ((((0.5 * (((fTemp7 * this.fRec7[((this.IOTA - iTemp16) & 2047)]) * fTemp17) * fTemp18)) + (((this.fRec7[((this.IOTA - iTemp19) & 2047)] * fTemp20) * fTemp21) * fTemp22)) + (0.166667 * ((fTemp23 * this.fRec7[((this.IOTA - iTemp24) & 2047)]) * fTemp25))) + (0.0416667 * (fTemp26 * this.fRec7[((this.IOTA - iTemp27) & 2047)])))));
			var fTemp28 = (fSlow5 * ((fSlow3 - this.fVec0[1]) > 0));
			var fTemp29 = (this.fRec0[2] + fTemp28);
			this.fVec1[(this.IOTA & 2047)] = fTemp29;
			var fTemp30 = ((((fTemp8 * fTemp10) * fTemp12) * fTemp14) * this.fVec1[((this.IOTA - iTemp5) & 2047)]);
			var fTemp31 = (fTemp15 * (((0.166667 * ((fTemp23 * fTemp25) * this.fVec1[((this.IOTA - iTemp24) & 2047)])) + ((((fTemp20 * fTemp21) * fTemp22) * this.fVec1[((this.IOTA - iTemp19) & 2047)]) + (0.5 * (((fTemp7 * fTemp17) * fTemp18) * this.fVec1[((this.IOTA - iTemp16) & 2047)])))) + (0.0416667 * (fTemp26 * this.fVec1[((this.IOTA - iTemp27) & 2047)]))));
			var fRec9 = (fTemp30 + fTemp31);
			var fRec10 = ((fTemp0 + fTemp30) + fTemp31);
			this.fRec3[0] = fRec8;
			var fRec4 = (fTemp28 + this.fRec3[1]);
			var fRec5 = fRec9;
			var fRec6 = fRec10;
			this.fRec0[0] = fRec4;
			this.fRec1[0] = fRec5;
			var fRec2 = fRec6;
			output0[i] = fRec2;
			output1[i] = fRec2;
			this.fRec11[1] = this.fRec11[0];
			this.IOTA = (this.IOTA + 1);
			this.fVec0[1] = this.fVec0[0];
			this.fRec12[1] = this.fRec12[0];
			this.fRec3[1] = this.fRec3[0];
			this.fRec0[2] = this.fRec0[1];
			this.fRec0[1] = this.fRec0[0];
			this.fRec1[2] = this.fRec1[1];
			this.fRec1[1] = this.fRec1[0];
			
		}
		
	}
	
}

