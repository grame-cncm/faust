
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.max_i = function(dummy0, dummy1);

function mydsp() {
	
	this.iRec6 = new Int32Array(2);
	this.fRec13 = new Float32Array(2);
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fConst2;
	this.fRec18 = new Float32Array(2);
	this.fRec17 = new Float32Array(2);
	this.fRec14 = new Float32Array(2);
	this.fHslider0;
	this.fRec19 = new Float32Array(2);
	this.IOTA;
	this.fRec15 = new Float32Array(2048);
	this.fConst3;
	this.fConst4;
	this.fHslider1;
	this.fHslider2;
	this.fHslider3;
	this.fHslider4;
	this.fHslider5;
	this.fHslider6;
	this.fHslider7;
	this.fHslider8;
	this.iVec0 = new Int32Array(2);
	this.iRec21 = new Int32Array(2);
	this.fHslider9;
	this.iVec1 = new Int32Array(2);
	this.iRec22 = new Int32Array(2);
	this.fRec20 = new Float32Array(2);
	this.fVec2 = new Float32Array(2);
	this.fRec11 = new Float32Array(2);
	this.fRec2 = new Float32Array(2048);
	this.fRec0 = new Float32Array(2);
	
	this.metadata = function(m) { 
		m.declare("analyzers.lib/name", "Faust Analyzer Library");
		m.declare("analyzers.lib/version", "0.0");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("interface", "SmartKeyboard{  'Number of Keyboards':'2',  'Max Keyboard Polyphony':'0',  'Keyboard 0 - Number of Keys':'4',   'Keyboard 1 - Number of Keys':'5',  'Keyboard 0 - Send Freq':'0',   'Keyboard 1 - Send Freq':'0',  'Keyboard 0 - Piano Keyboard':'0',   'Keyboard 1 - Piano Keyboard':'0',  'Keyboard 0 - Send Key Status':'1',  'Keyboard 1 - Send Key Status':'1',  'Keyboard 0 - Key 3 - Label':'O+',  'Keyboard 1 - Key 4 - Label':'O-' }");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "clarinet");
		m.declare("routes.lib/name", "Faust Signal Routing Library");
		m.declare("routes.lib/version", "0.0");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
	}

	this.getNumInputs = function() {
		return 1;
		
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
		this.fConst1 = Math.exp((0 - (50 / this.fConst0)));
		this.fConst2 = (1 - this.fConst1);
		this.fConst3 = (0.00882353 * this.fConst0);
		this.fConst4 = (0.00147059 * this.fConst0);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 0;
		this.fHslider1 = 0;
		this.fHslider2 = 0;
		this.fHslider3 = 0;
		this.fHslider4 = 0;
		this.fHslider5 = 0;
		this.fHslider6 = 0;
		this.fHslider7 = 0;
		this.fHslider8 = 0;
		this.fHslider9 = 0;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.iRec6[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec13[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec18[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec17[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec14[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fRec19[l5] = 0;
			
		}
		this.IOTA = 0;
		for (var l6 = 0; (l6 < 2048); l6 = (l6 + 1)) {
			this.fRec15[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			this.iVec0[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			this.iRec21[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			this.iVec1[l9] = 0;
			
		}
		for (var l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			this.iRec22[l10] = 0;
			
		}
		for (var l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			this.fRec20[l11] = 0;
			
		}
		for (var l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			this.fVec2[l12] = 0;
			
		}
		for (var l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			this.fRec11[l13] = 0;
			
		}
		for (var l14 = 0; (l14 < 2048); l14 = (l14 + 1)) {
			this.fRec2[l14] = 0;
			
		}
		for (var l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			this.fRec0[l15] = 0;
			
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
		ui_interface.openVerticalBox("clarinet");
		ui_interface.addHorizontalSlider("kb0k0status", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 0, 0, 1, 1);
		ui_interface.addHorizontalSlider("kb0k1status", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 0, 0, 1, 1);
		ui_interface.addHorizontalSlider("kb0k2status", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 0, 0, 1, 1);
		ui_interface.addHorizontalSlider("kb0k3status", function handler(obj) { function setval(val) { obj.fHslider8 = val; } return setval; }(this), 0, 0, 1, 1);
		ui_interface.addHorizontalSlider("kb1k0status", function handler(obj) { function setval(val) { obj.fHslider4 = val; } return setval; }(this), 0, 0, 1, 1);
		ui_interface.addHorizontalSlider("kb1k1status", function handler(obj) { function setval(val) { obj.fHslider5 = val; } return setval; }(this), 0, 0, 1, 1);
		ui_interface.addHorizontalSlider("kb1k2status", function handler(obj) { function setval(val) { obj.fHslider6 = val; } return setval; }(this), 0, 0, 1, 1);
		ui_interface.addHorizontalSlider("kb1k3status", function handler(obj) { function setval(val) { obj.fHslider7 = val; } return setval; }(this), 0, 0, 1, 1);
		ui_interface.addHorizontalSlider("kb1k4status", function handler(obj) { function setval(val) { obj.fHslider9 = val; } return setval; }(this), 0, 0, 1, 1);
		ui_interface.declare("fHslider0", "acc", "1 1 -10 0 10");
		ui_interface.addHorizontalSlider("reedStiffness", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0, 0, 1, 0.01);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = (0.001 * this.fHslider0);
		var iSlow1 = min_f(1, this.fHslider1);
		var iSlow2 = (iSlow1 == 1);
		var iSlow3 = min_f(1, this.fHslider2);
		var iSlow4 = (iSlow3 == 1);
		var iSlow5 = (iSlow2 & iSlow4);
		var iSlow6 = min_f(1, this.fHslider3);
		var iSlow7 = (iSlow6 == 0);
		var iSlow8 = (iSlow5 & iSlow7);
		var iSlow9 = min_f(1, this.fHslider4);
		var iSlow10 = (iSlow9 == 0);
		var iSlow11 = min_f(1, this.fHslider5);
		var iSlow12 = (iSlow11 == 0);
		var iSlow13 = min_f(1, this.fHslider6);
		var iSlow14 = (iSlow13 == 0);
		var iSlow15 = min_f(1, this.fHslider7);
		var iSlow16 = (iSlow15 == 0);
		var fSlow17 = (4 * (1 - ((((iSlow8 & iSlow10) & iSlow12) & iSlow14) & iSlow16)));
		var iSlow18 = (iSlow6 == 1);
		var iSlow19 = (iSlow5 & iSlow18);
		var iSlow20 = (iSlow9 == 1);
		var iSlow21 = (iSlow19 & iSlow20);
		var iSlow22 = (iSlow11 == 1);
		var iSlow23 = (iSlow21 & iSlow22);
		var iSlow24 = (iSlow23 & (iSlow13 == 1));
		var iSlow25 = (iSlow15 == 1);
		var iSlow26 = (iSlow23 & iSlow14);
		var iSlow27 = (iSlow19 & iSlow10);
		var iSlow28 = (iSlow1 == 0);
		var iSlow29 = (iSlow3 == 0);
		var iSlow30 = (iSlow2 & iSlow29);
		var iSlow31 = ((13 * (iSlow24 & iSlow25)) + ((11 * (iSlow24 & iSlow16)) + ((10 * (iSlow26 & iSlow25)) + ((9 * (iSlow26 & iSlow16)) + ((8 * (((iSlow21 & iSlow12) & iSlow14) & iSlow16)) + ((7 * (((iSlow27 & iSlow22) & iSlow14) & iSlow16)) + ((6 * (((iSlow27 & iSlow12) & iSlow14) & iSlow16)) + (((((((((iSlow28 & iSlow4) & iSlow7) & iSlow10) & iSlow12) & iSlow14) & iSlow16) + (2 * (((((iSlow30 & iSlow7) & iSlow10) & iSlow12) & iSlow14) & iSlow16))) + (3 * (((((iSlow30 & iSlow18) & iSlow10) & iSlow12) & iSlow14) & iSlow16))) + (5 * ((((iSlow8 & iSlow20) & iSlow12) & iSlow14) & iSlow16))))))))));
		var iSlow32 = ((((((iSlow28 & iSlow29) & iSlow7) & iSlow10) & iSlow12) & iSlow14) & iSlow25);
		var iSlow33 = min_f(1, this.fHslider8);
		var iSlow34 = min_f(1, this.fHslider9);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iRec6[0] = 0;
			this.fRec13[0] = (0.5 * (this.fRec13[1] + this.fRec11[1]));
			var fRec10 = (this.fRec13[0] + this.iRec6[1]);
			var fTemp0 = Math.abs(input0[i]);
			this.fRec18[0] = max_f(fTemp0, ((this.fConst1 * this.fRec18[1]) + (this.fConst2 * fTemp0)));
			this.fRec17[0] = ((this.fConst1 * this.fRec17[1]) + (this.fConst2 * this.fRec18[0]));
			var fTemp1 = (0.7 * this.fRec17[0]);
			this.fRec14[0] = (this.fRec0[1] + fTemp1);
			var fTemp2 = (0 - this.fRec14[1]);
			this.fRec19[0] = (fSlow0 + (0.999 * this.fRec19[1]));
			this.fRec15[(this.IOTA & 2047)] = (fTemp1 + (fTemp2 * max_f(-1, min_f(1, ((fTemp2 * ((0.26 * this.fRec19[0]) + -0.44)) + 0.7)))));
			var iRec16 = 0;
			this.iVec0[0] = iSlow33;
			this.iRec21[0] = (((iSlow33 - this.iVec0[1]) > 0) + this.iRec21[1]);
			this.iVec1[0] = iSlow34;
			this.iRec22[0] = (((iSlow34 - this.iVec1[1]) > 0) + this.iRec22[1]);
			this.fRec20[0] = ((0.999 * this.fRec20[1]) + (0.000772727 / Math.pow(2, (0.0833333 * (fSlow17 - (iSlow31 + (12 * (iSlow32 - (this.iRec21[0] - this.iRec22[0])))))))));
			var fTemp3 = (this.fConst4 * ((0.5 * this.fRec20[0]) + -0.05));
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
			this.fVec2[0] = (((((this.fRec15[((this.IOTA - iTemp6) & 2047)] * fTemp9) * fTemp11) * fTemp13) * fTemp15) + (fTemp16 * ((((0.5 * (((fTemp8 * this.fRec15[((this.IOTA - iTemp17) & 2047)]) * fTemp18) * fTemp19)) + (((this.fRec15[((this.IOTA - iTemp20) & 2047)] * fTemp21) * fTemp22) * fTemp23)) + (0.166667 * ((fTemp24 * this.fRec15[((this.IOTA - iTemp25) & 2047)]) * fTemp26))) + (0.0416667 * (fTemp27 * this.fRec15[((this.IOTA - iTemp28) & 2047)])))));
			this.fRec11[0] = this.fVec2[1];
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
			output0[i] = fRec1;
			output1[i] = fRec1;
			this.iRec6[1] = this.iRec6[0];
			this.fRec13[1] = this.fRec13[0];
			this.fRec18[1] = this.fRec18[0];
			this.fRec17[1] = this.fRec17[0];
			this.fRec14[1] = this.fRec14[0];
			this.fRec19[1] = this.fRec19[0];
			this.IOTA = (this.IOTA + 1);
			this.iVec0[1] = this.iVec0[0];
			this.iRec21[1] = this.iRec21[0];
			this.iVec1[1] = this.iVec1[0];
			this.iRec22[1] = this.iRec22[0];
			this.fRec20[1] = this.fRec20[0];
			this.fVec2[1] = this.fVec2[0];
			this.fRec11[1] = this.fRec11[0];
			this.fRec0[1] = this.fRec0[0];
			
		}
		
	}
	
}

