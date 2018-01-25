
this.mydsp_faustpower2_f = function(value) {
	return (value * value);
	
}
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);

function mydsp() {
	
	this.fHslider0;
	this.fRec0 = new Float32Array(2);
	this.iRec1 = new Int32Array(2);
	this.fRec3 = new Float32Array(2);
	this.fSamplingFreq;
	this.fConst0;
	this.fRec6 = new Float32Array(2);
	this.fRec4 = new Float32Array(2);
	this.fRec9 = new Float32Array(2);
	this.fRec7 = new Float32Array(2);
	this.fRec12 = new Float32Array(2);
	this.fRec10 = new Float32Array(2);
	this.fRec15 = new Float32Array(2);
	this.fRec13 = new Float32Array(2);
	
	this.metadata = function(m) { 
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "wind");
		m.declare("noises.lib/name", "Faust Noise Generator Library");
		m.declare("noises.lib/version", "0.0");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
		m.declare("vaeffects.lib/name", "Faust Virtual Analog Filter Effect Library");
		m.declare("vaeffects.lib/version", "0.0");
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
		this.fConst0 = (3.14159 / min_f(192000, max_f(1, this.fSamplingFreq)));
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 0.66;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.fRec0[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.iRec1[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec3[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec6[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec4[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fRec9[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			this.fRec7[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			this.fRec12[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			this.fRec10[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			this.fRec15[l9] = 0;
			
		}
		for (var l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			this.fRec13[l10] = 0;
			
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
		ui_interface.openVerticalBox("wind");
		ui_interface.addHorizontalSlider("force", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0.66, 0, 1, 0.01);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = (0.003 * this.fHslider0);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.fRec0[0] = (fSlow0 + (0.997 * this.fRec0[1]));
			var iTemp0 = (1103515245 * (this.iRec1[1] + 12345));
			this.iRec1[0] = (1103515245 * (iTemp0 + 12345));
			var iRec2 = iTemp0;
			var fTemp1 = (4.65661e-10 * this.iRec1[0]);
			this.fRec3[0] = (fSlow0 + (0.997 * this.fRec3[1]));
			var fTemp2 = mydsp_faustpower2_f((1.4142 * this.fRec3[0]));
			var fTemp3 = (1.99998 * this.fRec3[0]);
			var fTemp4 = (fTemp2 + fTemp3);
			var fTemp5 = (fTemp3 + 2);
			var fTemp6 = Math.tan((this.fConst0 * max_f((440 * Math.pow(2, (0.0833333 * ((87 * this.fRec3[0]) + -48)))), 20)));
			var fTemp7 = (1 / fTemp6);
			var fTemp8 = ((fTemp4 + ((fTemp5 + fTemp7) / fTemp6)) + 1);
			var fTemp9 = ((fTemp4 + (1 - ((fTemp5 - fTemp7) / fTemp6))) / fTemp8);
			var fTemp10 = max_f(-0.9999, min_f(0.9999, fTemp9));
			var fTemp11 = (0 - fTemp10);
			var fTemp12 = (1 - mydsp_faustpower2_f(fTemp10));
			var fTemp13 = Math.sqrt(max_f(0, fTemp12));
			var fTemp14 = ((this.fRec4[1] * fTemp11) + (fTemp1 * fTemp13));
			var fTemp15 = (1 / mydsp_faustpower2_f(fTemp6));
			var fTemp16 = (fTemp4 + (1 - fTemp15));
			var fTemp17 = max_f(-0.9999, min_f(0.9999, (2 * (fTemp16 / (fTemp8 * (fTemp9 + 1))))));
			var fTemp18 = (0 - fTemp17);
			var fTemp19 = (1 - mydsp_faustpower2_f(fTemp17));
			var fTemp20 = Math.sqrt(max_f(0, fTemp19));
			this.fRec6[0] = ((this.fRec6[1] * fTemp18) + (fTemp14 * fTemp20));
			this.fRec4[0] = ((fTemp14 * fTemp17) + (this.fRec6[1] * fTemp20));
			var fRec5 = this.fRec6[0];
			var fTemp21 = (1 - (fTemp16 / fTemp8));
			var fTemp22 = Math.sqrt(fTemp12);
			var fTemp23 = ((1 - fTemp9) - (2 * (fTemp17 * fTemp21)));
			var fTemp24 = (fTemp22 * Math.sqrt(fTemp19));
			var fTemp25 = ((((fTemp1 * fTemp10) + (this.fRec4[1] * fTemp13)) + (2 * ((this.fRec4[0] * fTemp21) / fTemp22))) + ((fRec5 * fTemp23) / fTemp24));
			var fTemp26 = (2 - fTemp3);
			var fTemp27 = (1 - fTemp3);
			var fTemp28 = ((fTemp2 + ((fTemp7 + fTemp26) / fTemp6)) + fTemp27);
			var fTemp29 = (((fTemp2 + ((fTemp7 - fTemp26) / fTemp6)) + fTemp27) / fTemp28);
			var fTemp30 = max_f(-0.9999, min_f(0.9999, fTemp29));
			var fTemp31 = (0 - fTemp30);
			var fTemp32 = (1 - mydsp_faustpower2_f(fTemp30));
			var fTemp33 = Math.sqrt(max_f(0, fTemp32));
			var fTemp34 = ((this.fRec7[1] * fTemp31) + ((fTemp25 * fTemp33) / fTemp8));
			var fTemp35 = (fTemp2 + (1 - (fTemp3 + fTemp15)));
			var fTemp36 = max_f(-0.9999, min_f(0.9999, (2 * (fTemp35 / (fTemp28 * (fTemp29 + 1))))));
			var fTemp37 = (0 - fTemp36);
			var fTemp38 = (1 - mydsp_faustpower2_f(fTemp36));
			var fTemp39 = Math.sqrt(max_f(0, fTemp38));
			this.fRec9[0] = ((this.fRec9[1] * fTemp37) + (fTemp34 * fTemp39));
			this.fRec7[0] = ((fTemp34 * fTemp36) + (this.fRec9[1] * fTemp39));
			var fRec8 = this.fRec9[0];
			var fTemp40 = (1 - (fTemp35 / fTemp28));
			var fTemp41 = Math.sqrt(fTemp32);
			var fTemp42 = ((1 - fTemp29) - (2 * (fTemp36 * fTemp40)));
			var fTemp43 = (fTemp41 * Math.sqrt(fTemp38));
			output0[i] = ((this.fRec0[0] * (((((fTemp25 * fTemp30) / fTemp8) + (this.fRec7[1] * fTemp33)) + (2 * ((this.fRec7[0] * fTemp40) / fTemp41))) + ((fRec8 * fTemp42) / fTemp43))) / fTemp28);
			var fTemp44 = (4.65661e-10 * iRec2);
			var fTemp45 = ((fTemp11 * this.fRec10[1]) + (fTemp13 * fTemp44));
			this.fRec12[0] = ((fTemp18 * this.fRec12[1]) + (fTemp20 * fTemp45));
			this.fRec10[0] = ((fTemp17 * fTemp45) + (fTemp20 * this.fRec12[1]));
			var fRec11 = this.fRec12[0];
			var fTemp46 = ((((fTemp10 * fTemp44) + (fTemp13 * this.fRec10[1])) + (2 * ((this.fRec10[0] * fTemp21) / fTemp22))) + ((fRec11 * fTemp23) / fTemp24));
			var fTemp47 = ((fTemp31 * this.fRec13[1]) + ((fTemp33 * fTemp46) / fTemp8));
			this.fRec15[0] = ((fTemp37 * this.fRec15[1]) + (fTemp39 * fTemp47));
			this.fRec13[0] = ((fTemp36 * fTemp47) + (fTemp39 * this.fRec15[1]));
			var fRec14 = this.fRec15[0];
			output1[i] = ((this.fRec0[0] * (((((fTemp30 * fTemp46) / fTemp8) + (fTemp33 * this.fRec13[1])) + (2 * ((this.fRec13[0] * fTemp40) / fTemp41))) + ((fRec14 * fTemp42) / fTemp43))) / fTemp28);
			this.fRec0[1] = this.fRec0[0];
			this.iRec1[1] = this.iRec1[0];
			this.fRec3[1] = this.fRec3[0];
			this.fRec6[1] = this.fRec6[0];
			this.fRec4[1] = this.fRec4[0];
			this.fRec9[1] = this.fRec9[0];
			this.fRec7[1] = this.fRec7[0];
			this.fRec12[1] = this.fRec12[0];
			this.fRec10[1] = this.fRec10[0];
			this.fRec15[1] = this.fRec15[0];
			this.fRec13[1] = this.fRec13[0];
			
		}
		
	}
	
}

