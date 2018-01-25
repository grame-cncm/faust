
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.mydsp_faustpower2_f = function(value) {
	return (value * value);
	
}

function mydsp() {
	
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fHslider0;
	this.fHslider1;
	this.fVec0 = new Float32Array(2);
	this.fRec4 = new Float32Array(2);
	this.fRec3 = new Float32Array(3);
	this.fHslider2;
	this.fRec6 = new Float32Array(2);
	this.fRec5 = new Float32Array(3);
	this.fConst2;
	this.fHslider3;
	this.fRec7 = new Float32Array(2);
	this.fHslider4;
	this.fConst3;
	this.fConst4;
	this.fHslider5;
	this.fConst5;
	this.fRec2 = new Float32Array(3);
	this.fVec1 = new Float32Array(2);
	this.fRec1 = new Float32Array(2);
	this.fRec0 = new Float32Array(3);
	this.fHslider6;
	this.fRec9 = new Float32Array(2);
	this.fRec8 = new Float32Array(3);
	
	this.metadata = function(m) { 
		m.declare("analyzers.lib/name", "Faust Analyzer Library");
		m.declare("analyzers.lib/version", "0.0");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("description", "Exercise and compare Parametric Equalizer sections on test signals");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "parametricEqualizer");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
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
		this.fConst1 = (3.14159 / this.fConst0);
		this.fConst2 = (1382.3 / this.fConst0);
		this.fConst3 = (1 / this.fConst0);
		this.fConst4 = (1382.3 * this.fConst3);
		this.fConst5 = (2764.6 * this.fConst3);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 8000;
		this.fHslider1 = 200;
		this.fHslider2 = 0;
		this.fHslider3 = 49;
		this.fHslider4 = 0;
		this.fHslider5 = 40;
		this.fHslider6 = 0;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.fVec0[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec4[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 3); l2 = (l2 + 1)) {
			this.fRec3[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec6[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 3); l4 = (l4 + 1)) {
			this.fRec5[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fRec7[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 3); l6 = (l6 + 1)) {
			this.fRec2[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			this.fVec1[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			this.fRec1[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 3); l9 = (l9 + 1)) {
			this.fRec0[l9] = 0;
			
		}
		for (var l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			this.fRec9[l10] = 0;
			
		}
		for (var l11 = 0; (l11 < 3); l11 = (l11 + 1)) {
			this.fRec8[l11] = 0;
			
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
		ui_interface.declare("0", "tooltip", "See Faust's filters.lib   for info and pointers");
		ui_interface.openHorizontalBox("PARAMETRIC EQ SECTIONS");
		ui_interface.declare("0", "1", "");
		ui_interface.openVerticalBox("Low Shelf");
		ui_interface.declare("fHslider2", "0", "");
		ui_interface.declare("fHslider2", "style", "knob");
		ui_interface.declare("fHslider2", "tooltip", "Amount of low-frequency boost or cut in decibels");
		ui_interface.declare("fHslider2", "unit", "dB");
		ui_interface.addHorizontalSlider("Low Boost|Cut", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 0, -40, 40, 0.1);
		ui_interface.declare("fHslider1", "1", "");
		ui_interface.declare("fHslider1", "scale", "log");
		ui_interface.declare("fHslider1", "style", "knob");
		ui_interface.declare("fHslider1", "tooltip", "Transition-frequency from boost (cut) to unity gain");
		ui_interface.declare("fHslider1", "unit", "Hz");
		ui_interface.addHorizontalSlider("Transition Frequency", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 200, 1, 5000, 1);
		ui_interface.closeBox();
		ui_interface.declare("0", "2", "");
		ui_interface.declare("0", "tooltip", "Parametric Equalizer   sections from filters.lib");
		ui_interface.openVerticalBox("Peaking Equalizer");
		ui_interface.declare("fHslider4", "0", "");
		ui_interface.declare("fHslider4", "style", "knob");
		ui_interface.declare("fHslider4", "tooltip", "Amount of   local boost or cut in decibels");
		ui_interface.declare("fHslider4", "unit", "dB");
		ui_interface.addHorizontalSlider("Peak Boost|Cut", function handler(obj) { function setval(val) { obj.fHslider4 = val; } return setval; }(this), 0, -40, 40, 0.1);
		ui_interface.declare("fHslider3", "1", "");
		ui_interface.declare("fHslider3", "style", "knob");
		ui_interface.declare("fHslider3", "tooltip", "Peak   Frequency in Piano Key (PK) units (A440 = 49PK)");
		ui_interface.declare("fHslider3", "unit", "PK");
		ui_interface.addHorizontalSlider("Peak Frequency", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 49, 1, 100, 1);
		ui_interface.declare("fHslider5", "2", "");
		ui_interface.declare("fHslider5", "scale", "log");
		ui_interface.declare("fHslider5", "style", "knob");
		ui_interface.declare("fHslider5", "tooltip", "Quality factor   (Q) of the peak = center-frequency/bandwidth");
		ui_interface.addHorizontalSlider("Peak Q", function handler(obj) { function setval(val) { obj.fHslider5 = val; } return setval; }(this), 40, 1, 1000, 0.1);
		ui_interface.closeBox();
		ui_interface.declare("0", "3", "");
		ui_interface.declare("0", "tooltip", "A high shelf provides a boost   or cut above some frequency");
		ui_interface.openVerticalBox("High Shelf");
		ui_interface.declare("fHslider6", "0", "");
		ui_interface.declare("fHslider6", "style", "knob");
		ui_interface.declare("fHslider6", "tooltip", "Amount of   high-frequency boost or cut in decibels");
		ui_interface.declare("fHslider6", "unit", "dB");
		ui_interface.addHorizontalSlider("High Boost|Cut", function handler(obj) { function setval(val) { obj.fHslider6 = val; } return setval; }(this), 0, -40, 40, 0.1);
		ui_interface.declare("fHslider0", "1", "");
		ui_interface.declare("fHslider0", "scale", "log");
		ui_interface.declare("fHslider0", "style", "knob");
		ui_interface.declare("fHslider0", "tooltip", "Transition-frequency from boost (cut) to unity gain");
		ui_interface.declare("fHslider0", "unit", "Hz");
		ui_interface.addHorizontalSlider("Transition Frequency", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 8000, 20, 10000, 1);
		ui_interface.closeBox();
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var output0 = outputs[0];
		var fSlow0 = Math.tan((this.fConst1 * this.fHslider0));
		var fSlow1 = (1 / fSlow0);
		var fSlow2 = (1 / (((fSlow1 + 1) / fSlow0) + 1));
		var fSlow3 = (fSlow1 + 1);
		var fSlow4 = (0 - ((1 - fSlow1) / fSlow3));
		var fSlow5 = (1 / fSlow3);
		var fSlow6 = Math.tan((this.fConst1 * this.fHslider1));
		var fSlow7 = (1 / fSlow6);
		var fSlow8 = (1 / (((fSlow7 + 1) / fSlow6) + 1));
		var fSlow9 = (1 / mydsp_faustpower2_f(fSlow6));
		var fSlow10 = (fSlow7 + 1);
		var fSlow11 = (0 - ((1 - fSlow7) / fSlow10));
		var fSlow12 = (1 / fSlow10);
		var fSlow13 = (0 - fSlow7);
		var fSlow14 = (2 * (1 - fSlow9));
		var fSlow15 = (((fSlow7 + -1) / fSlow6) + 1);
		var fSlow16 = (2 * (0 - fSlow9));
		var fSlow17 = Math.pow(10, (0.05 * this.fHslider2));
		var fSlow18 = (0.001 * this.fHslider3);
		var fSlow19 = this.fHslider4;
		var iSlow20 = (fSlow19 > 0);
		var fSlow21 = this.fHslider5;
		var fSlow22 = (this.fConst4 * (Math.pow(10, (0.05 * Math.abs(fSlow19))) / fSlow21));
		var fSlow23 = (this.fConst4 / fSlow21);
		var fSlow24 = (1 / mydsp_faustpower2_f(fSlow0));
		var fSlow25 = (2 * (1 - fSlow24));
		var fSlow26 = (((fSlow1 + -1) / fSlow0) + 1);
		var fSlow27 = Math.pow(10, (0.05 * this.fHslider6));
		var fSlow28 = (0 - fSlow1);
		var fSlow29 = (2 * (0 - fSlow24));
		for (var i = 0; (i < count); i = (i + 1)) {
			var fTemp0 = input0[i];
			this.fVec0[0] = fTemp0;
			this.fRec4[0] = ((fSlow11 * this.fRec4[1]) + (fSlow12 * ((fSlow7 * fTemp0) + (fSlow13 * this.fVec0[1]))));
			this.fRec3[0] = (this.fRec4[0] - (fSlow8 * ((fSlow14 * this.fRec3[1]) + (fSlow15 * this.fRec3[2]))));
			this.fRec6[0] = ((fSlow11 * this.fRec6[1]) + (fSlow12 * (fTemp0 + this.fVec0[1])));
			this.fRec5[0] = (this.fRec6[0] - (fSlow8 * ((fSlow14 * this.fRec5[1]) + (fSlow15 * this.fRec5[2]))));
			this.fRec7[0] = (fSlow18 + (0.999 * this.fRec7[1]));
			var fTemp1 = Math.pow(2, (0.0833333 * (this.fRec7[0] + -49)));
			var fTemp2 = Math.tan((this.fConst2 * fTemp1));
			var fTemp3 = (1 / fTemp2);
			var fTemp4 = (fTemp1 / Math.sin((this.fConst5 * fTemp1)));
			var fTemp5 = (fSlow22 * fTemp4);
			var fTemp6 = (fSlow23 * fTemp4);
			var fTemp7 = (iSlow20?fTemp6:fTemp5);
			var fTemp8 = (2 * (this.fRec2[1] * (1 - (1 / mydsp_faustpower2_f(fTemp2)))));
			var fTemp9 = (((fTemp3 + fTemp7) / fTemp2) + 1);
			this.fRec2[0] = ((fSlow8 * ((((fSlow9 * this.fRec3[0]) + (fSlow16 * this.fRec3[1])) + (fSlow9 * this.fRec3[2])) + (fSlow17 * (this.fRec5[2] + (this.fRec5[0] + (2 * this.fRec5[1])))))) - (((this.fRec2[2] * (((fTemp3 - fTemp7) / fTemp2) + 1)) + fTemp8) / fTemp9));
			var fTemp10 = (iSlow20?fTemp5:fTemp6);
			var fTemp11 = (((fTemp8 + (this.fRec2[0] * (((fTemp3 + fTemp10) / fTemp2) + 1))) + (this.fRec2[2] * (((fTemp3 - fTemp10) / fTemp2) + 1))) / fTemp9);
			this.fVec1[0] = fTemp11;
			this.fRec1[0] = ((fSlow4 * this.fRec1[1]) + (fSlow5 * (this.fVec1[1] + fTemp11)));
			this.fRec0[0] = (this.fRec1[0] - (fSlow2 * ((fSlow25 * this.fRec0[1]) + (fSlow26 * this.fRec0[2]))));
			this.fRec9[0] = ((fSlow4 * this.fRec9[1]) + (fSlow5 * ((fSlow28 * this.fVec1[1]) + (fSlow1 * fTemp11))));
			this.fRec8[0] = (this.fRec9[0] - (fSlow2 * ((fSlow25 * this.fRec8[1]) + (fSlow26 * this.fRec8[2]))));
			output0[i] = (fSlow2 * ((this.fRec0[2] + (this.fRec0[0] + (2 * this.fRec0[1]))) + (fSlow27 * (((fSlow24 * this.fRec8[0]) + (fSlow29 * this.fRec8[1])) + (fSlow24 * this.fRec8[2])))));
			this.fVec0[1] = this.fVec0[0];
			this.fRec4[1] = this.fRec4[0];
			this.fRec3[2] = this.fRec3[1];
			this.fRec3[1] = this.fRec3[0];
			this.fRec6[1] = this.fRec6[0];
			this.fRec5[2] = this.fRec5[1];
			this.fRec5[1] = this.fRec5[0];
			this.fRec7[1] = this.fRec7[0];
			this.fRec2[2] = this.fRec2[1];
			this.fRec2[1] = this.fRec2[0];
			this.fVec1[1] = this.fVec1[0];
			this.fRec1[1] = this.fRec1[0];
			this.fRec0[2] = this.fRec0[1];
			this.fRec0[1] = this.fRec0[0];
			this.fRec9[1] = this.fRec9[0];
			this.fRec8[2] = this.fRec8[1];
			this.fRec8[1] = this.fRec8[0];
			
		}
		
	}
	
}

