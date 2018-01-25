
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.mydsp_faustpower2_f = function(value) {
	return (value * value);
	
}

function mydsp() {
	
	this.fHslider0;
	this.fSamplingFreq;
	this.fConst0;
	this.fHslider1;
	this.iVec0 = new Int32Array(2);
	this.fHslider2;
	this.fHslider3;
	this.fHbargraph0;
	this.fRec1 = new Float32Array(2);
	this.fRec2 = new Float32Array(2);
	this.iRec3 = new Int32Array(2);
	this.IOTA;
	this.fVec1 = new Float32Array(32);
	this.fRec0 = new Float32Array(2);
	this.fVbargraph0;
	this.fRec4 = new Float32Array(2);
	this.fVbargraph1;
	this.fRec5 = new Float32Array(2);
	this.fVbargraph2;
	this.fRec6 = new Float32Array(2);
	this.fVbargraph3;
	this.fRec7 = new Float32Array(2);
	this.fVbargraph4;
	this.fRec8 = new Float32Array(2);
	this.fVbargraph5;
	this.fRec9 = new Float32Array(2);
	this.fVbargraph6;
	this.fRec10 = new Float32Array(2);
	this.fVbargraph7;
	this.fRec11 = new Float32Array(2);
	this.fVbargraph8;
	this.fRec12 = new Float32Array(2);
	this.fVbargraph9;
	this.fRec13 = new Float32Array(2);
	this.fVbargraph10;
	this.fRec14 = new Float32Array(2);
	this.fVbargraph11;
	this.fRec15 = new Float32Array(2);
	this.fVbargraph12;
	this.fRec16 = new Float32Array(2);
	this.fVbargraph13;
	this.fRec17 = new Float32Array(2);
	this.fVbargraph14;
	this.fRec18 = new Float32Array(2);
	this.fVbargraph15;
	this.fRec19 = new Float32Array(2);
	this.fVbargraph16;
	
	this.metadata = function(m) { 
		m.declare("analyzers.lib/name", "Faust Analyzer Library");
		m.declare("analyzers.lib/version", "0.0");
		m.declare("author", "JOS");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("license", "STK-4.3");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "FFT");
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
		this.fConst0 = (1000 / min_f(192000, max_f(1, this.fSamplingFreq)));
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 50;
		this.fHslider1 = 100;
		this.fHslider2 = 0.1;
		this.fHslider3 = 8;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.iVec0[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec1[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec2[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.iRec3[l3] = 0;
			
		}
		this.IOTA = 0;
		for (var l4 = 0; (l4 < 32); l4 = (l4 + 1)) {
			this.fVec1[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fRec0[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			this.fRec4[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			this.fRec5[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			this.fRec6[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			this.fRec7[l9] = 0;
			
		}
		for (var l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			this.fRec8[l10] = 0;
			
		}
		for (var l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			this.fRec9[l11] = 0;
			
		}
		for (var l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			this.fRec10[l12] = 0;
			
		}
		for (var l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			this.fRec11[l13] = 0;
			
		}
		for (var l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			this.fRec12[l14] = 0;
			
		}
		for (var l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			this.fRec13[l15] = 0;
			
		}
		for (var l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			this.fRec14[l16] = 0;
			
		}
		for (var l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			this.fRec15[l17] = 0;
			
		}
		for (var l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			this.fRec16[l18] = 0;
			
		}
		for (var l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			this.fRec17[l19] = 0;
			
		}
		for (var l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			this.fRec18[l20] = 0;
			
		}
		for (var l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			this.fRec19[l21] = 0;
			
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
		ui_interface.openVerticalBox("FFT");
		ui_interface.declare("0", "0", "");
		ui_interface.declare("0", "tooltip", "fft_spectral_level in Faust's analyzers.lib");
		ui_interface.openHorizontalBox("FFT SPECTRUM ANALYZER, 32 bands");
		ui_interface.declare("fVbargraph0", "0", "");
		ui_interface.declare("fVbargraph0", "tooltip", "FFT Spectral Band Level in dB");
		ui_interface.declare("fVbargraph0", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7feec0dfb8d0", function handler(obj) { function setval(val) { obj.fVbargraph0 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph1", "1", "");
		ui_interface.declare("fVbargraph1", "tooltip", "FFT Spectral Band Level in dB");
		ui_interface.declare("fVbargraph1", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7feec3b10040", function handler(obj) { function setval(val) { obj.fVbargraph1 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph2", "2", "");
		ui_interface.declare("fVbargraph2", "tooltip", "FFT Spectral Band Level in dB");
		ui_interface.declare("fVbargraph2", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7feec3b1bbf0", function handler(obj) { function setval(val) { obj.fVbargraph2 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph3", "3", "");
		ui_interface.declare("fVbargraph3", "tooltip", "FFT Spectral Band Level in dB");
		ui_interface.declare("fVbargraph3", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7feec3b275a0", function handler(obj) { function setval(val) { obj.fVbargraph3 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph4", "4", "");
		ui_interface.declare("fVbargraph4", "tooltip", "FFT Spectral Band Level in dB");
		ui_interface.declare("fVbargraph4", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7feec3b2f540", function handler(obj) { function setval(val) { obj.fVbargraph4 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph5", "5", "");
		ui_interface.declare("fVbargraph5", "tooltip", "FFT Spectral Band Level in dB");
		ui_interface.declare("fVbargraph5", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7feec3b3b1c0", function handler(obj) { function setval(val) { obj.fVbargraph5 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph6", "6", "");
		ui_interface.declare("fVbargraph6", "tooltip", "FFT Spectral Band Level in dB");
		ui_interface.declare("fVbargraph6", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7feec3b422b0", function handler(obj) { function setval(val) { obj.fVbargraph6 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph7", "7", "");
		ui_interface.declare("fVbargraph7", "tooltip", "FFT Spectral Band Level in dB");
		ui_interface.declare("fVbargraph7", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7feec3b4cec0", function handler(obj) { function setval(val) { obj.fVbargraph7 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph8", "8", "");
		ui_interface.declare("fVbargraph8", "tooltip", "FFT Spectral Band Level in dB");
		ui_interface.declare("fVbargraph8", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7feec3b52e40", function handler(obj) { function setval(val) { obj.fVbargraph8 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph9", "9", "");
		ui_interface.declare("fVbargraph9", "tooltip", "FFT Spectral Band Level in dB");
		ui_interface.declare("fVbargraph9", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7feec3b5a060", function handler(obj) { function setval(val) { obj.fVbargraph9 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph10", "10", "");
		ui_interface.declare("fVbargraph10", "tooltip", "FFT Spectral Band Level in dB");
		ui_interface.declare("fVbargraph10", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7feec3b61410", function handler(obj) { function setval(val) { obj.fVbargraph10 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph11", "11", "");
		ui_interface.declare("fVbargraph11", "tooltip", "FFT Spectral Band Level in dB");
		ui_interface.declare("fVbargraph11", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7feec3b69070", function handler(obj) { function setval(val) { obj.fVbargraph11 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph12", "12", "");
		ui_interface.declare("fVbargraph12", "tooltip", "FFT Spectral Band Level in dB");
		ui_interface.declare("fVbargraph12", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7feec3b6e600", function handler(obj) { function setval(val) { obj.fVbargraph12 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph13", "13", "");
		ui_interface.declare("fVbargraph13", "tooltip", "FFT Spectral Band Level in dB");
		ui_interface.declare("fVbargraph13", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7feec3b76250", function handler(obj) { function setval(val) { obj.fVbargraph13 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph14", "14", "");
		ui_interface.declare("fVbargraph14", "tooltip", "FFT Spectral Band Level in dB");
		ui_interface.declare("fVbargraph14", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7feec3b7d200", function handler(obj) { function setval(val) { obj.fVbargraph14 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph15", "15", "");
		ui_interface.declare("fVbargraph15", "tooltip", "FFT Spectral Band Level in dB");
		ui_interface.declare("fVbargraph15", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7feec3b84e40", function handler(obj) { function setval(val) { obj.fVbargraph15 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph16", "16", "");
		ui_interface.declare("fVbargraph16", "tooltip", "FFT Spectral Band Level in dB");
		ui_interface.declare("fVbargraph16", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7feec3b89ce0", function handler(obj) { function setval(val) { obj.fVbargraph16 = val; } return setval; }(this), -50, 10);
		ui_interface.closeBox();
		ui_interface.declare("0", "1", "");
		ui_interface.openHorizontalBox("FFT SPECTRUM ANALYZER CONTROLS");
		ui_interface.declare("fHslider1", "0", "");
		ui_interface.declare("fHslider1", "scale", "log");
		ui_interface.declare("fHslider1", "tooltip", "band-level averaging time in milliseconds");
		ui_interface.declare("fHslider1", "unit", "ms");
		ui_interface.addHorizontalSlider("Level Averaging Time", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 100, 1, 10000, 1);
		ui_interface.declare("fHslider0", "1", "");
		ui_interface.declare("fHslider0", "tooltip", "Level offset in decibels");
		ui_interface.declare("fHslider0", "unit", "dB");
		ui_interface.addHorizontalSlider("Level dB Offset", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 50, -50, 100, 1);
		ui_interface.closeBox();
		ui_interface.declare("fHslider3", "2", "");
		ui_interface.addHorizontalSlider("FFT Bin Number", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 8, 0, 16, 0.001);
		ui_interface.declare("fHbargraph0", "3", "");
		ui_interface.addHorizontalBargraph("Measured FFT Bin Number", function handler(obj) { function setval(val) { obj.fHbargraph0 = val; } return setval; }(this), 0, 16);
		ui_interface.declare("fHslider2", "4", "");
		ui_interface.addHorizontalSlider("Amplitude", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 0.1, 0, 1, 0.001);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = this.fHslider0;
		var fSlow1 = Math.exp((0 - (this.fConst0 / this.fHslider1)));
		var fSlow2 = (10 * (1 - fSlow1));
		var fSlow3 = this.fHslider2;
		var iSlow4 = this.fHslider3;
		this.fHbargraph0 = iSlow4;
		var iSlow5 = (iSlow4 == 0);
		var iSlow6 = (iSlow4 == 16);
		var fSlow7 = (0.19635 * iSlow4);
		var fSlow8 = Math.sin(fSlow7);
		var fSlow9 = Math.cos(fSlow7);
		var fSlow10 = (0 - fSlow8);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iVec0[0] = 1;
			this.fRec1[0] = ((fSlow8 * this.fRec2[1]) + (fSlow9 * this.fRec1[1]));
			this.fRec2[0] = (((fSlow9 * this.fRec2[1]) + (fSlow10 * this.fRec1[1])) + (1 - this.iVec0[1]));
			this.iRec3[0] = (1 - (this.iVec0[1] + this.iRec3[1]));
			var fTemp0 = (fSlow3 * (iSlow5?1:(iSlow6?this.iRec3[0]:(2 * this.fRec2[0]))));
			this.fVec1[(this.IOTA & 31)] = fTemp0;
			var fTemp1 = (fTemp0 + this.fVec1[((this.IOTA - 16) & 31)]);
			var fTemp2 = (this.fVec1[((this.IOTA - 24) & 31)] + (fTemp1 + this.fVec1[((this.IOTA - 8) & 31)]));
			var fTemp3 = (this.fVec1[((this.IOTA - 28) & 31)] + (this.fVec1[((this.IOTA - 12) & 31)] + (this.fVec1[((this.IOTA - 20) & 31)] + (this.fVec1[((this.IOTA - 4) & 31)] + fTemp2))));
			var fTemp4 = (this.fVec1[((this.IOTA - 30) & 31)] + (this.fVec1[((this.IOTA - 14) & 31)] + (this.fVec1[((this.IOTA - 22) & 31)] + (this.fVec1[((this.IOTA - 6) & 31)] + (this.fVec1[((this.IOTA - 26) & 31)] + (this.fVec1[((this.IOTA - 10) & 31)] + (this.fVec1[((this.IOTA - 18) & 31)] + (this.fVec1[((this.IOTA - 2) & 31)] + fTemp3))))))));
			this.fRec0[0] = ((fSlow1 * this.fRec0[1]) + (fSlow2 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, mydsp_faustpower2_f(Math.abs((this.fVec1[((this.IOTA - 31) & 31)] + (this.fVec1[((this.IOTA - 15) & 31)] + (this.fVec1[((this.IOTA - 23) & 31)] + (this.fVec1[((this.IOTA - 7) & 31)] + (this.fVec1[((this.IOTA - 27) & 31)] + (this.fVec1[((this.IOTA - 11) & 31)] + (this.fVec1[((this.IOTA - 19) & 31)] + (this.fVec1[((this.IOTA - 3) & 31)] + (this.fVec1[((this.IOTA - 29) & 31)] + (this.fVec1[((this.IOTA - 13) & 31)] + (this.fVec1[((this.IOTA - 21) & 31)] + (this.fVec1[((this.IOTA - 5) & 31)] + (this.fVec1[((this.IOTA - 25) & 31)] + (this.fVec1[((this.IOTA - 9) & 31)] + (this.fVec1[((this.IOTA - 17) & 31)] + (this.fVec1[((this.IOTA - 1) & 31)] + fTemp4))))))))))))))))))))));
			this.fVbargraph0 = (fSlow0 + this.fRec0[0]);
			var fTemp5 = (this.fVec1[((this.IOTA - 15) & 31)] - this.fVec1[((this.IOTA - 31) & 31)]);
			var fTemp6 = (0 - fTemp5);
			var fTemp7 = (this.fVec1[((this.IOTA - 7) & 31)] - this.fVec1[((this.IOTA - 23) & 31)]);
			var fTemp8 = (0.707107 * fTemp7);
			var fTemp9 = ((this.fVec1[((this.IOTA - 27) & 31)] + (0.707107 * fTemp6)) - (this.fVec1[((this.IOTA - 11) & 31)] + fTemp8));
			var fTemp10 = (0.92388 * fTemp9);
			var fTemp11 = (this.fVec1[((this.IOTA - 13) & 31)] - this.fVec1[((this.IOTA - 29) & 31)]);
			var fTemp12 = (0 - fTemp11);
			var fTemp13 = (this.fVec1[((this.IOTA - 25) & 31)] + (0.707107 * fTemp12));
			var fTemp14 = (this.fVec1[((this.IOTA - 5) & 31)] - this.fVec1[((this.IOTA - 21) & 31)]);
			var fTemp15 = (0.707107 * fTemp14);
			var fTemp16 = (this.fVec1[((this.IOTA - 9) & 31)] + fTemp15);
			var fTemp17 = (0.707107 * fTemp6);
			var fTemp18 = (0.707107 * fTemp7);
			var fTemp19 = ((fTemp17 + (this.fVec1[((this.IOTA - 3) & 31)] + fTemp18)) - this.fVec1[((this.IOTA - 19) & 31)]);
			var fTemp20 = ((fTemp10 + fTemp13) - (fTemp16 + (0.382683 * fTemp19)));
			var fTemp21 = (this.fVec1[((this.IOTA - 14) & 31)] - this.fVec1[((this.IOTA - 30) & 31)]);
			var fTemp22 = (0 - fTemp21);
			var fTemp23 = (this.fVec1[((this.IOTA - 6) & 31)] - this.fVec1[((this.IOTA - 22) & 31)]);
			var fTemp24 = (0.707107 * fTemp23);
			var fTemp25 = ((this.fVec1[((this.IOTA - 26) & 31)] + (0.707107 * fTemp22)) - (this.fVec1[((this.IOTA - 10) & 31)] + fTemp24));
			var fTemp26 = (this.fVec1[((this.IOTA - 12) & 31)] - this.fVec1[((this.IOTA - 28) & 31)]);
			var fTemp27 = (0 - fTemp26);
			var fTemp28 = (0.707107 * fTemp27);
			var fTemp29 = (this.fVec1[((this.IOTA - 4) & 31)] - this.fVec1[((this.IOTA - 20) & 31)]);
			var fTemp30 = (0.707107 * fTemp29);
			var fTemp31 = (fTemp28 + (fTemp0 + fTemp30));
			var fTemp32 = (0.707107 * fTemp22);
			var fTemp33 = (0.707107 * fTemp23);
			var fTemp34 = ((fTemp32 + (this.fVec1[((this.IOTA - 2) & 31)] + fTemp33)) - this.fVec1[((this.IOTA - 18) & 31)]);
			var fTemp35 = (0.92388 * fTemp34);
			var fTemp36 = (0.707107 * fTemp12);
			var fTemp37 = (0.707107 * fTemp14);
			var fTemp38 = (fTemp36 + (this.fVec1[((this.IOTA - 1) & 31)] + fTemp37));
			var fTemp39 = (0.92388 * fTemp19);
			var fTemp40 = (((0.382683 * fTemp9) + (fTemp38 + fTemp39)) - this.fVec1[((this.IOTA - 17) & 31)]);
			var fTemp41 = (0.92388 * fTemp25);
			var fTemp42 = (this.fVec1[((this.IOTA - 24) & 31)] + (0.707107 * fTemp27));
			var fTemp43 = (0.707107 * fTemp29);
			var fTemp44 = (this.fVec1[((this.IOTA - 8) & 31)] + fTemp43);
			this.fRec4[0] = ((fSlow1 * this.fRec4[1]) + (fSlow2 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, (mydsp_faustpower2_f(Math.abs((((0.19509 * fTemp20) + (((0.382683 * fTemp25) + (fTemp31 + fTemp35)) + (0.980785 * fTemp40))) - this.fVec1[((this.IOTA - 16) & 31)]))) + mydsp_faustpower2_f(Math.abs((((0.980785 * fTemp20) + (fTemp41 + fTemp42)) - ((fTemp44 + (0.382683 * fTemp34)) + (0.19509 * fTemp40))))))))));
			this.fVbargraph1 = (fSlow0 + this.fRec4[0]);
			var fTemp45 = (this.fVec1[((this.IOTA - 13) & 31)] + this.fVec1[((this.IOTA - 29) & 31)]);
			var fTemp46 = (this.fVec1[((this.IOTA - 7) & 31)] + this.fVec1[((this.IOTA - 23) & 31)]);
			var fTemp47 = (fTemp46 - (this.fVec1[((this.IOTA - 15) & 31)] + this.fVec1[((this.IOTA - 31) & 31)]));
			var fTemp48 = (0 - fTemp47);
			var fTemp49 = (this.fVec1[((this.IOTA - 5) & 31)] + this.fVec1[((this.IOTA - 21) & 31)]);
			var fTemp50 = (this.fVec1[((this.IOTA - 3) & 31)] + this.fVec1[((this.IOTA - 19) & 31)]);
			var fTemp51 = (fTemp50 - (this.fVec1[((this.IOTA - 11) & 31)] + this.fVec1[((this.IOTA - 27) & 31)]));
			var fTemp52 = (0.707107 * fTemp51);
			var fTemp53 = ((fTemp45 + (0.707107 * fTemp48)) - (fTemp49 + fTemp52));
			var fTemp54 = (this.fVec1[((this.IOTA - 6) & 31)] + this.fVec1[((this.IOTA - 22) & 31)]);
			var fTemp55 = (fTemp54 - (this.fVec1[((this.IOTA - 14) & 31)] + this.fVec1[((this.IOTA - 30) & 31)]));
			var fTemp56 = (0 - fTemp55);
			var fTemp57 = (0.707107 * fTemp56);
			var fTemp58 = (this.fVec1[((this.IOTA - 2) & 31)] + this.fVec1[((this.IOTA - 18) & 31)]);
			var fTemp59 = (fTemp58 - (this.fVec1[((this.IOTA - 10) & 31)] + this.fVec1[((this.IOTA - 26) & 31)]));
			var fTemp60 = (0.707107 * fTemp59);
			var fTemp61 = (0.707107 * fTemp48);
			var fTemp62 = (this.fVec1[((this.IOTA - 1) & 31)] + this.fVec1[((this.IOTA - 17) & 31)]);
			var fTemp63 = (0.707107 * fTemp51);
			var fTemp64 = (this.fVec1[((this.IOTA - 9) & 31)] + this.fVec1[((this.IOTA - 25) & 31)]);
			var fTemp65 = ((fTemp61 + (fTemp62 + fTemp63)) - fTemp64);
			var fTemp66 = (this.fVec1[((this.IOTA - 8) & 31)] + this.fVec1[((this.IOTA - 24) & 31)]);
			var fTemp67 = (this.fVec1[((this.IOTA - 12) & 31)] + this.fVec1[((this.IOTA - 28) & 31)]);
			var fTemp68 = (this.fVec1[((this.IOTA - 4) & 31)] + this.fVec1[((this.IOTA - 20) & 31)]);
			var fTemp69 = (0.707107 * fTemp59);
			this.fRec5[0] = ((fSlow1 * this.fRec5[1]) + (fSlow2 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, (mydsp_faustpower2_f(Math.abs((((0.382683 * fTemp53) + ((fTemp57 + (fTemp1 + fTemp60)) + (0.92388 * fTemp65))) - fTemp66))) + mydsp_faustpower2_f(Math.abs((((0.92388 * fTemp53) + (fTemp67 + (0.707107 * fTemp56))) - ((0.382683 * fTemp65) + (fTemp68 + fTemp69))))))))));
			this.fVbargraph2 = (fSlow0 + this.fRec5[0]);
			var fTemp70 = (0.707107 * fTemp5);
			var fTemp71 = (this.fVec1[((this.IOTA - 11) & 31)] - (fTemp70 + (this.fVec1[((this.IOTA - 27) & 31)] + fTemp18)));
			var fTemp72 = (0.707107 * fTemp11);
			var fTemp73 = (fTemp72 + (this.fVec1[((this.IOTA - 25) & 31)] + fTemp37));
			var fTemp74 = ((this.fVec1[((this.IOTA - 3) & 31)] + (0.707107 * fTemp5)) - (this.fVec1[((this.IOTA - 19) & 31)] + fTemp8));
			var fTemp75 = ((this.fVec1[((this.IOTA - 9) & 31)] + (0.382683 * fTemp71)) - (fTemp73 + (0.92388 * fTemp74)));
			var fTemp76 = (0.707107 * fTemp21);
			var fTemp77 = (this.fVec1[((this.IOTA - 10) & 31)] - (fTemp76 + (this.fVec1[((this.IOTA - 26) & 31)] + fTemp33)));
			var fTemp78 = (fTemp0 + (0.707107 * fTemp26));
			var fTemp79 = ((this.fVec1[((this.IOTA - 2) & 31)] + (0.707107 * fTemp21)) - (this.fVec1[((this.IOTA - 18) & 31)] + fTemp24));
			var fTemp80 = (this.fVec1[((this.IOTA - 1) & 31)] + (0.707107 * fTemp11));
			var fTemp81 = (this.fVec1[((this.IOTA - 17) & 31)] + fTemp15);
			var fTemp82 = (((0.92388 * fTemp71) + (fTemp80 + (0.382683 * fTemp74))) - fTemp81);
			var fTemp83 = (this.fVec1[((this.IOTA - 16) & 31)] + fTemp43);
			var fTemp84 = (0.707107 * fTemp26);
			var fTemp85 = (fTemp84 + (this.fVec1[((this.IOTA - 24) & 31)] + fTemp30));
			this.fRec6[0] = ((fSlow1 * this.fRec6[1]) + (fSlow2 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, (mydsp_faustpower2_f(Math.abs((((0.55557 * fTemp75) + (((0.92388 * fTemp77) + (fTemp78 + (0.382683 * fTemp79))) + (0.83147 * fTemp82))) - fTemp83))) + mydsp_faustpower2_f(Math.abs((((0.83147 * fTemp75) + (this.fVec1[((this.IOTA - 8) & 31)] + (0.382683 * fTemp77))) - ((fTemp85 + (0.92388 * fTemp79)) + (0.55557 * fTemp82))))))))));
			this.fVbargraph3 = (fSlow0 + this.fRec6[0]);
			var fTemp86 = (this.fVec1[((this.IOTA - 27) & 31)] + (fTemp50 + this.fVec1[((this.IOTA - 11) & 31)]));
			var fTemp87 = (fTemp86 - (this.fVec1[((this.IOTA - 31) & 31)] + (fTemp46 + this.fVec1[((this.IOTA - 15) & 31)])));
			var fTemp88 = (0 - fTemp87);
			var fTemp89 = (this.fVec1[((this.IOTA - 25) & 31)] + (fTemp62 + this.fVec1[((this.IOTA - 9) & 31)]));
			var fTemp90 = (fTemp89 - (this.fVec1[((this.IOTA - 29) & 31)] + (fTemp49 + this.fVec1[((this.IOTA - 13) & 31)])));
			var fTemp91 = (0.707107 * fTemp90);
			var fTemp92 = (this.fVec1[((this.IOTA - 28) & 31)] + (fTemp68 + this.fVec1[((this.IOTA - 12) & 31)]));
			var fTemp93 = (this.fVec1[((this.IOTA - 30) & 31)] + (fTemp54 + this.fVec1[((this.IOTA - 14) & 31)]));
			var fTemp94 = (this.fVec1[((this.IOTA - 26) & 31)] + (fTemp58 + this.fVec1[((this.IOTA - 10) & 31)]));
			var fTemp95 = (0.707107 * fTemp90);
			this.fRec7[0] = ((fSlow1 * this.fRec7[1]) + (fSlow2 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, (mydsp_faustpower2_f(Math.abs((((0.707107 * fTemp88) + (fTemp2 + fTemp91)) - fTemp92))) + mydsp_faustpower2_f(Math.abs(((fTemp93 + (0.707107 * fTemp88)) - (fTemp94 + fTemp95)))))))));
			this.fVbargraph4 = (fSlow0 + this.fRec7[0]);
			var fTemp96 = (this.fVec1[((this.IOTA - 25) & 31)] + fTemp15);
			var fTemp97 = ((this.fVec1[((this.IOTA - 27) & 31)] + fTemp8) - (this.fVec1[((this.IOTA - 11) & 31)] + (0.707107 * fTemp6)));
			var fTemp98 = (this.fVec1[((this.IOTA - 9) & 31)] + (0.707107 * fTemp12));
			var fTemp99 = (0.707107 * fTemp7);
			var fTemp100 = (this.fVec1[((this.IOTA - 3) & 31)] - (fTemp17 + (this.fVec1[((this.IOTA - 19) & 31)] + fTemp99)));
			var fTemp101 = (fTemp96 - ((0.382683 * fTemp97) + (fTemp98 + (0.92388 * fTemp100))));
			var fTemp102 = ((this.fVec1[((this.IOTA - 26) & 31)] + fTemp24) - (this.fVec1[((this.IOTA - 10) & 31)] + (0.707107 * fTemp22)));
			var fTemp103 = (0.707107 * fTemp14);
			var fTemp104 = (fTemp36 + (this.fVec1[((this.IOTA - 17) & 31)] + fTemp103));
			var fTemp105 = ((this.fVec1[((this.IOTA - 1) & 31)] + (0.92388 * fTemp97)) - (fTemp104 + (0.382683 * fTemp100)));
			var fTemp106 = (0.707107 * fTemp29);
			var fTemp107 = (fTemp28 + (this.fVec1[((this.IOTA - 16) & 31)] + fTemp106));
			var fTemp108 = (0.707107 * fTemp23);
			var fTemp109 = (this.fVec1[((this.IOTA - 2) & 31)] - (fTemp32 + (this.fVec1[((this.IOTA - 18) & 31)] + fTemp108)));
			var fTemp110 = (this.fVec1[((this.IOTA - 24) & 31)] + fTemp43);
			var fTemp111 = (this.fVec1[((this.IOTA - 8) & 31)] + (0.707107 * fTemp27));
			this.fRec8[0] = ((fSlow1 * this.fRec8[1]) + (fSlow2 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, (mydsp_faustpower2_f(Math.abs((((0.83147 * fTemp101) + ((fTemp0 + (0.92388 * fTemp102)) + (0.55557 * fTemp105))) - (fTemp107 + (0.382683 * fTemp109))))) + mydsp_faustpower2_f(Math.abs(((fTemp110 + (0.55557 * fTemp101)) - ((0.83147 * fTemp105) + ((0.382683 * fTemp102) + (fTemp111 + (0.92388 * fTemp109))))))))))));
			this.fVbargraph5 = (fSlow0 + this.fRec8[0]);
			var fTemp112 = (0.707107 * fTemp47);
			var fTemp113 = (fTemp49 - (fTemp112 + (fTemp45 + fTemp63)));
			var fTemp114 = ((fTemp62 + (0.707107 * fTemp47)) - (fTemp64 + fTemp52));
			var fTemp115 = (0.707107 * fTemp55);
			this.fRec9[0] = ((fSlow1 * this.fRec9[1]) + (fSlow2 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, (mydsp_faustpower2_f(Math.abs((((0.92388 * fTemp113) + ((fTemp1 + (0.707107 * fTemp55)) + (0.382683 * fTemp114))) - (fTemp66 + fTemp69)))) + mydsp_faustpower2_f(Math.abs(((fTemp68 + (0.382683 * fTemp113)) - ((0.92388 * fTemp114) + (fTemp115 + (fTemp67 + fTemp60)))))))))));
			this.fVbargraph6 = (fSlow0 + this.fRec9[0]);
			var fTemp116 = (fTemp72 + (this.fVec1[((this.IOTA - 9) & 31)] + fTemp103));
			var fTemp117 = ((fTemp70 + (this.fVec1[((this.IOTA - 11) & 31)] + fTemp99)) - this.fVec1[((this.IOTA - 27) & 31)]);
			var fTemp118 = ((this.fVec1[((this.IOTA - 3) & 31)] + fTemp8) - (this.fVec1[((this.IOTA - 19) & 31)] + (0.707107 * fTemp5)));
			var fTemp119 = (fTemp116 - ((0.92388 * fTemp117) + (this.fVec1[((this.IOTA - 25) & 31)] + (0.382683 * fTemp118))));
			var fTemp120 = (fTemp0 + fTemp43);
			var fTemp121 = ((fTemp76 + (this.fVec1[((this.IOTA - 10) & 31)] + fTemp108)) - this.fVec1[((this.IOTA - 26) & 31)]);
			var fTemp122 = (this.fVec1[((this.IOTA - 1) & 31)] + fTemp15);
			var fTemp123 = (this.fVec1[((this.IOTA - 17) & 31)] + (0.707107 * fTemp11));
			var fTemp124 = ((fTemp122 + (0.382683 * fTemp117)) - (fTemp123 + (0.92388 * fTemp118)));
			var fTemp125 = (this.fVec1[((this.IOTA - 16) & 31)] + (0.707107 * fTemp26));
			var fTemp126 = ((this.fVec1[((this.IOTA - 2) & 31)] + fTemp24) - (this.fVec1[((this.IOTA - 18) & 31)] + (0.707107 * fTemp21)));
			var fTemp127 = (fTemp84 + (this.fVec1[((this.IOTA - 8) & 31)] + fTemp106));
			this.fRec10[0] = ((fSlow1 * this.fRec10[1]) + (fSlow2 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, (mydsp_faustpower2_f(Math.abs((((0.980785 * fTemp119) + ((fTemp120 + (0.382683 * fTemp121)) + (0.19509 * fTemp124))) - (fTemp125 + (0.92388 * fTemp126))))) + mydsp_faustpower2_f(Math.abs(((fTemp127 + (0.19509 * fTemp119)) - ((0.980785 * fTemp124) + ((0.92388 * fTemp121) + (this.fVec1[((this.IOTA - 24) & 31)] + (0.382683 * fTemp126))))))))))));
			this.fVbargraph7 = (fSlow0 + this.fRec10[0]);
			var fTemp128 = (this.fVec1[((this.IOTA - 29) & 31)] + (this.fVec1[((this.IOTA - 13) & 31)] + (this.fVec1[((this.IOTA - 21) & 31)] + (this.fVec1[((this.IOTA - 5) & 31)] + fTemp89))));
			this.fRec11[0] = ((fSlow1 * this.fRec11[1]) + (fSlow2 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, (mydsp_faustpower2_f(Math.abs((fTemp3 - (this.fVec1[((this.IOTA - 30) & 31)] + (this.fVec1[((this.IOTA - 14) & 31)] + (this.fVec1[((this.IOTA - 22) & 31)] + (this.fVec1[((this.IOTA - 6) & 31)] + fTemp94))))))) + mydsp_faustpower2_f(Math.abs((0 - (fTemp128 - (this.fVec1[((this.IOTA - 31) & 31)] + (this.fVec1[((this.IOTA - 15) & 31)] + (this.fVec1[((this.IOTA - 23) & 31)] + (this.fVec1[((this.IOTA - 7) & 31)] + fTemp86)))))))))))));
			this.fVbargraph8 = (fSlow0 + this.fRec11[0]);
			var fTemp129 = ((fTemp13 + (0.382683 * fTemp19)) - (fTemp10 + fTemp16));
			var fTemp130 = (fTemp38 - ((0.382683 * fTemp9) + (this.fVec1[((this.IOTA - 17) & 31)] + fTemp39)));
			this.fRec12[0] = ((fSlow1 * this.fRec12[1]) + (fSlow2 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, (mydsp_faustpower2_f(Math.abs(((fTemp31 + (0.980785 * fTemp129)) - (((0.382683 * fTemp25) + (this.fVec1[((this.IOTA - 16) & 31)] + fTemp35)) + (0.19509 * fTemp130))))) + mydsp_faustpower2_f(Math.abs(((fTemp42 + (0.382683 * fTemp34)) - ((0.19509 * fTemp129) + ((fTemp41 + fTemp44) + (0.980785 * fTemp130)))))))))));
			this.fVbargraph9 = (fSlow0 + this.fRec12[0]);
			var fTemp131 = ((fTemp45 + fTemp52) - (fTemp49 + (0.707107 * fTemp48)));
			var fTemp132 = (0.707107 * fTemp59);
			var fTemp133 = (0.707107 * fTemp51);
			var fTemp134 = (fTemp62 - (fTemp61 + (fTemp64 + fTemp133)));
			this.fRec13[0] = ((fSlow1 * this.fRec13[1]) + (fSlow2 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, (mydsp_faustpower2_f(Math.abs(((fTemp1 + (0.92388 * fTemp131)) - ((fTemp57 + (fTemp66 + fTemp132)) + (0.382683 * fTemp134))))) + mydsp_faustpower2_f(Math.abs(((fTemp67 + fTemp69) - ((0.382683 * fTemp131) + ((fTemp68 + (0.707107 * fTemp56)) + (0.92388 * fTemp134)))))))))));
			this.fVbargraph10 = (fSlow0 + this.fRec13[0]);
			var fTemp135 = ((this.fVec1[((this.IOTA - 9) & 31)] + (0.92388 * fTemp74)) - (fTemp73 + (0.382683 * fTemp71)));
			var fTemp136 = (fTemp80 - ((0.92388 * fTemp71) + (fTemp81 + (0.382683 * fTemp74))));
			this.fRec14[0] = ((fSlow1 * this.fRec14[1]) + (fSlow2 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, (mydsp_faustpower2_f(Math.abs(((fTemp78 + (0.83147 * fTemp135)) - (((0.92388 * fTemp77) + (fTemp83 + (0.382683 * fTemp79))) + (0.55557 * fTemp136))))) + mydsp_faustpower2_f(Math.abs(((this.fVec1[((this.IOTA - 8) & 31)] + (0.92388 * fTemp79)) - ((0.55557 * fTemp135) + ((fTemp85 + (0.382683 * fTemp77)) + (0.83147 * fTemp136)))))))))));
			this.fVbargraph11 = (fSlow0 + this.fRec14[0]);
			this.fRec15[0] = ((fSlow1 * this.fRec15[1]) + (fSlow2 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, (mydsp_faustpower2_f(Math.abs(((fTemp2 + (0.707107 * fTemp87)) - (fTemp92 + fTemp95)))) + mydsp_faustpower2_f(Math.abs((fTemp94 - ((0.707107 * fTemp87) + (fTemp93 + fTemp91))))))))));
			this.fVbargraph12 = (fSlow0 + this.fRec15[0]);
			var fTemp137 = (((0.382683 * fTemp97) + (fTemp96 + (0.92388 * fTemp100))) - fTemp98);
			var fTemp138 = ((this.fVec1[((this.IOTA - 1) & 31)] + (0.382683 * fTemp100)) - (fTemp104 + (0.92388 * fTemp97)));
			this.fRec16[0] = ((fSlow1 * this.fRec16[1]) + (fSlow2 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, (mydsp_faustpower2_f(Math.abs((((fTemp0 + (0.382683 * fTemp109)) + (0.55557 * fTemp137)) - ((fTemp107 + (0.92388 * fTemp102)) + (0.83147 * fTemp138))))) + mydsp_faustpower2_f(Math.abs((((0.382683 * fTemp102) + (fTemp110 + (0.92388 * fTemp109))) - ((0.83147 * fTemp137) + (fTemp111 + (0.55557 * fTemp138)))))))))));
			this.fVbargraph13 = (fSlow0 + this.fRec16[0]);
			var fTemp139 = ((fTemp112 + (fTemp49 + fTemp133)) - fTemp45);
			var fTemp140 = ((fTemp62 + fTemp52) - (fTemp64 + (0.707107 * fTemp47)));
			this.fRec17[0] = ((fSlow1 * this.fRec17[1]) + (fSlow2 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, (mydsp_faustpower2_f(Math.abs((((fTemp1 + fTemp69) + (0.382683 * fTemp139)) - ((fTemp66 + (0.707107 * fTemp55)) + (0.92388 * fTemp140))))) + mydsp_faustpower2_f(Math.abs(((fTemp115 + (fTemp68 + fTemp132)) - ((0.92388 * fTemp139) + (fTemp67 + (0.382683 * fTemp140)))))))))));
			this.fVbargraph14 = (fSlow0 + this.fRec17[0]);
			var fTemp141 = (((0.92388 * fTemp117) + (fTemp116 + (0.382683 * fTemp118))) - this.fVec1[((this.IOTA - 25) & 31)]);
			var fTemp142 = ((fTemp122 + (0.92388 * fTemp118)) - (fTemp123 + (0.382683 * fTemp117)));
			this.fRec18[0] = ((fSlow1 * this.fRec18[1]) + (fSlow2 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, (mydsp_faustpower2_f(Math.abs((((fTemp120 + (0.92388 * fTemp126)) + (0.19509 * fTemp141)) - ((fTemp125 + (0.382683 * fTemp121)) + (0.980785 * fTemp142))))) + mydsp_faustpower2_f(Math.abs((((0.92388 * fTemp121) + (fTemp127 + (0.382683 * fTemp126))) - ((0.980785 * fTemp141) + (this.fVec1[((this.IOTA - 24) & 31)] + (0.19509 * fTemp142)))))))))));
			this.fVbargraph15 = (fSlow0 + this.fRec18[0]);
			this.fRec19[0] = ((fSlow1 * this.fRec19[1]) + (fSlow2 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, mydsp_faustpower2_f(Math.abs((fTemp4 - (this.fVec1[((this.IOTA - 31) & 31)] + (this.fVec1[((this.IOTA - 15) & 31)] + (this.fVec1[((this.IOTA - 23) & 31)] + (this.fVec1[((this.IOTA - 7) & 31)] + (this.fVec1[((this.IOTA - 27) & 31)] + (this.fVec1[((this.IOTA - 11) & 31)] + (this.fVec1[((this.IOTA - 19) & 31)] + (this.fVec1[((this.IOTA - 3) & 31)] + fTemp128)))))))))))))));
			this.fVbargraph16 = (fSlow0 + this.fRec19[0]);
			output0[i] = fTemp0;
			output1[i] = fTemp0;
			this.iVec0[1] = this.iVec0[0];
			this.fRec1[1] = this.fRec1[0];
			this.fRec2[1] = this.fRec2[0];
			this.iRec3[1] = this.iRec3[0];
			this.IOTA = (this.IOTA + 1);
			this.fRec0[1] = this.fRec0[0];
			this.fRec4[1] = this.fRec4[0];
			this.fRec5[1] = this.fRec5[0];
			this.fRec6[1] = this.fRec6[0];
			this.fRec7[1] = this.fRec7[0];
			this.fRec8[1] = this.fRec8[0];
			this.fRec9[1] = this.fRec9[0];
			this.fRec10[1] = this.fRec10[0];
			this.fRec11[1] = this.fRec11[0];
			this.fRec12[1] = this.fRec12[0];
			this.fRec13[1] = this.fRec13[0];
			this.fRec14[1] = this.fRec14[0];
			this.fRec15[1] = this.fRec15[0];
			this.fRec16[1] = this.fRec16[0];
			this.fRec17[1] = this.fRec17[0];
			this.fRec18[1] = this.fRec18[0];
			this.fRec19[1] = this.fRec19[0];
			
		}
		
	}
	
}

