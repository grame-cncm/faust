

function mydspSIG0() {
	
	this.iRec11 = new Int32Array(2);
	
	this.getNumInputsmydspSIG0 = function() {
		return 0;
		
	}
	this.getNumOutputsmydspSIG0 = function() {
		return 1;
		
	}
	this.getInputRatemydspSIG0 = function(channel) {
		var rate;
		switch (channel) {
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	this.getOutputRatemydspSIG0 = function(channel) {
		var rate;
		switch (channel) {
			case 0: {
				rate = 0;
				break;
			}
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	
	this.instanceInitmydspSIG0 = function(samplingFreq) {
		for (var l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			this.iRec11[l15] = 0;
			
		}
		
	}
	
	this.fillmydspSIG0 = function(count, output) {
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iRec11[0] = (this.iRec11[1] + 1);
			output[i] = Math.sin((9.58738e-05 * (this.iRec11[0] + -1)));
			this.iRec11[1] = this.iRec11[0];
			
		}
		
	}
}

newmydspSIG0 = function() { return new mydspSIG0(); }
deletemydspSIG0= function(dsp) {}

this.min_f = function(dummy0, dummy1);
this.max_f = function(dummy0, dummy1);
var ftbl0mydspSIG0 = new Float32Array(65536);

function mydsp() {
	
	this.fHslider0;
	this.iVec0 = new Int32Array(2);
	this.fButton0;
	this.fHslider1;
	this.fVec1 = new Float32Array(2);
	this.fHslider2;
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fHslider3;
	this.fRec0 = new Float32Array(2);
	this.fConst2;
	this.fHslider4;
	this.fHslider5;
	this.fRec3 = new Float32Array(2);
	this.fHslider6;
	this.fConst3;
	this.fHslider7;
	this.fRec4 = new Float32Array(2);
	this.fRec5 = new Float32Array(2);
	this.fVec2 = new Float32Array(2);
	this.fRec2 = new Float32Array(2);
	this.iVec3 = new Int32Array(2);
	this.fConst4;
	this.fConst5;
	this.fConst6;
	this.fHslider8;
	this.fHslider9;
	this.fRec7 = new Float32Array(2);
	this.fRec8 = new Float32Array(2);
	this.fRec9 = new Float32Array(2);
	this.fRec6 = new Float32Array(2);
	this.fRec10 = new Float32Array(2);
	this.fRec1 = new Float32Array(3);
	this.fConst7;
	this.fRec13 = new Float32Array(2);
	this.fRec12 = new Float32Array(2);
	this.fRec15 = new Float32Array(2);
	this.fRec16 = new Float32Array(2);
	this.fRec14 = new Float32Array(3);
	this.fRec17 = new Float32Array(2);
	this.fRec19 = new Float32Array(2);
	this.fRec20 = new Float32Array(2);
	this.fRec18 = new Float32Array(3);
	this.fRec21 = new Float32Array(2);
	this.fRec23 = new Float32Array(2);
	this.fRec24 = new Float32Array(2);
	this.fRec22 = new Float32Array(3);
	this.fRec25 = new Float32Array(2);
	this.fRec27 = new Float32Array(2);
	this.fRec28 = new Float32Array(2);
	this.fRec26 = new Float32Array(3);
	this.fRec29 = new Float32Array(2);
	
	this.metadata = function(m) { 
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("copyright", "(c)Mike Olsen, CCRMA (Stanford University)");
		m.declare("description", "MIDI-controllable FOF vocal synthesizer.");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("license", "MIT");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "Vocal FOF MIDI");
		m.declare("noises.lib/name", "Faust Noise Generator Library");
		m.declare("noises.lib/version", "0.0");
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
		var sig0 = newmydspSIG0();
		sig0.instanceInitmydspSIG0(samplingFreq);
		sig0.fillmydspSIG0(65536, ftbl0mydspSIG0);
		deletemydspSIG0(sig0);
		
	}
	
	this.instanceConstants = function(samplingFreq) {
		this.fSamplingFreq = samplingFreq;
		this.fConst0 = min_f(192000, max_f(1, this.fSamplingFreq));
		this.fConst1 = (1000 / this.fConst0);
		this.fConst2 = (1 / this.fConst0);
		this.fConst3 = (6.28319 / this.fConst0);
		this.fConst4 = (3.14159 / this.fConst0);
		this.fConst5 = Math.exp((0 - this.fConst1));
		this.fConst6 = (1 - this.fConst5);
		this.fConst7 = (1 / this.fConst0);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 0.5;
		this.fButton0 = 0;
		this.fHslider1 = 0;
		this.fHslider2 = 0.9;
		this.fHslider3 = 10;
		this.fHslider4 = 440;
		this.fHslider5 = 1;
		this.fHslider6 = 0.5;
		this.fHslider7 = 6;
		this.fHslider8 = 0;
		this.fHslider9 = 0;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.iVec0[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fVec1[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec0[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec3[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec4[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fRec5[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			this.fVec2[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			this.fRec2[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			this.iVec3[l8] = 0;
			
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
			this.fRec6[l12] = 0;
			
		}
		for (var l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			this.fRec10[l13] = 0;
			
		}
		for (var l14 = 0; (l14 < 3); l14 = (l14 + 1)) {
			this.fRec1[l14] = 0;
			
		}
		for (var l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			this.fRec13[l16] = 0;
			
		}
		for (var l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			this.fRec12[l17] = 0;
			
		}
		for (var l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			this.fRec15[l18] = 0;
			
		}
		for (var l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			this.fRec16[l19] = 0;
			
		}
		for (var l20 = 0; (l20 < 3); l20 = (l20 + 1)) {
			this.fRec14[l20] = 0;
			
		}
		for (var l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			this.fRec17[l21] = 0;
			
		}
		for (var l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			this.fRec19[l22] = 0;
			
		}
		for (var l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			this.fRec20[l23] = 0;
			
		}
		for (var l24 = 0; (l24 < 3); l24 = (l24 + 1)) {
			this.fRec18[l24] = 0;
			
		}
		for (var l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			this.fRec21[l25] = 0;
			
		}
		for (var l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			this.fRec23[l26] = 0;
			
		}
		for (var l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			this.fRec24[l27] = 0;
			
		}
		for (var l28 = 0; (l28 < 3); l28 = (l28 + 1)) {
			this.fRec22[l28] = 0;
			
		}
		for (var l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			this.fRec25[l29] = 0;
			
		}
		for (var l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			this.fRec27[l30] = 0;
			
		}
		for (var l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			this.fRec28[l31] = 0;
			
		}
		for (var l32 = 0; (l32 < 3); l32 = (l32 + 1)) {
			this.fRec26[l32] = 0;
			
		}
		for (var l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			this.fRec29[l33] = 0;
			
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
		ui_interface.openVerticalBox("vocal");
		ui_interface.declare("0", "0", "");
		ui_interface.openHorizontalBox("midi");
		ui_interface.declare("fHslider4", "0", "");
		ui_interface.declare("fHslider4", "style", "knob");
		ui_interface.addHorizontalSlider("freq", function handler(obj) { function setval(val) { obj.fHslider4 = val; } return setval; }(this), 440, 50, 1000, 0.01);
		ui_interface.declare("fHslider5", "1", "");
		ui_interface.declare("fHslider5", "hidden", "1");
		ui_interface.declare("fHslider5", "midi", "pitchwheel");
		ui_interface.declare("fHslider5", "style", "knob");
		ui_interface.addHorizontalSlider("bend", function handler(obj) { function setval(val) { obj.fHslider5 = val; } return setval; }(this), 1, 0, 10, 0.01);
		ui_interface.declare("fHslider2", "2", "");
		ui_interface.declare("fHslider2", "style", "knob");
		ui_interface.addHorizontalSlider("gain", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 0.9, 0, 1, 0.01);
		ui_interface.declare("fHslider3", "3", "");
		ui_interface.declare("fHslider3", "style", "knob");
		ui_interface.addHorizontalSlider("envAttack", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 10, 0, 30, 0.01);
		ui_interface.declare("fHslider1", "4", "");
		ui_interface.declare("fHslider1", "hidden", "1");
		ui_interface.declare("fHslider1", "midi", "ctrl 64");
		ui_interface.declare("fHslider1", "style", "knob");
		ui_interface.addHorizontalSlider("sustain", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 0, 0, 1, 1);
		ui_interface.closeBox();
		ui_interface.declare("0", "1", "");
		ui_interface.openHorizontalBox("otherParams");
		ui_interface.declare("fHslider8", "0", "");
		ui_interface.declare("fHslider8", "style", "knob");
		ui_interface.addHorizontalSlider("voiceType", function handler(obj) { function setval(val) { obj.fHslider8 = val; } return setval; }(this), 0, 0, 4, 1);
		ui_interface.declare("fHslider9", "1", "");
		ui_interface.declare("fHslider9", "midi", "ctrl 1");
		ui_interface.declare("fHslider9", "style", "knob");
		ui_interface.addHorizontalSlider("vowel", function handler(obj) { function setval(val) { obj.fHslider9 = val; } return setval; }(this), 0, 0, 4, 0.01);
		ui_interface.declare("fHslider7", "3", "");
		ui_interface.declare("fHslider7", "style", "knob");
		ui_interface.addHorizontalSlider("vibratoFreq", function handler(obj) { function setval(val) { obj.fHslider7 = val; } return setval; }(this), 6, 1, 10, 0.01);
		ui_interface.declare("fHslider6", "4", "");
		ui_interface.declare("fHslider6", "style", "knob");
		ui_interface.addHorizontalSlider("vibratoGain", function handler(obj) { function setval(val) { obj.fHslider6 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.declare("fHslider0", "5", "");
		ui_interface.declare("fHslider0", "style", "knob");
		ui_interface.addHorizontalSlider("outGain", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.closeBox();
		ui_interface.declare("fButton0", "2", "");
		ui_interface.addButton("gate", function handler(obj) { function setval(val) { obj.fButton0 = val; } return setval; }(this));
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = this.fHslider0;
		var fSlow1 = min_f(1, (this.fButton0 + this.fHslider1));
		var fSlow2 = Math.exp((0 - (this.fConst1 / this.fHslider3)));
		var fSlow3 = (25 * ((fSlow1 * this.fHslider2) * (1 - fSlow2)));
		var fSlow4 = this.fHslider4;
		var iSlow5 = (fSlow1 == 0);
		var fSlow6 = this.fHslider5;
		var fSlow7 = (0.1 * this.fHslider6);
		var fSlow8 = (this.fConst3 * this.fHslider7);
		var fSlow9 = Math.sin(fSlow8);
		var fSlow10 = Math.cos(fSlow8);
		var fSlow11 = (0 - fSlow9);
		var fSlow12 = this.fHslider8;
		var fSlow13 = (5 * fSlow12);
		var fSlow14 = (0.001 * this.fHslider9);
		var fSlow15 = (5 * (1 - fSlow12));
		var iSlow16 = ((fSlow12 == 0)?1:((fSlow12 == 3)?1:0));
		var iSlow17 = (5 * iSlow16);
		var iSlow18 = (iSlow16 >= 1);
		var fSlow19 = (iSlow18?174.61:82.41);
		var fSlow20 = (iSlow18?1046.5:523.25);
		var fSlow21 = (fSlow20 - fSlow19);
		var iSlow22 = (iSlow16 == 0);
		var iSlow23 = (fSlow12 != 2);
		var fSlow24 = (2 * fSlow4);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iVec0[0] = 1;
			this.fVec1[0] = fSlow1;
			this.fRec0[0] = (fSlow3 + (fSlow2 * this.fRec0[1]));
			var iTemp0 = ((fSlow1 == this.fVec1[1]) | iSlow5);
			this.fRec3[0] = ((0.999 * (this.fRec3[1] * iTemp0)) + (fSlow6 * (1 - (0.999 * iTemp0))));
			this.fRec4[0] = ((fSlow9 * this.fRec5[1]) + (fSlow10 * this.fRec4[1]));
			var iTemp1 = (1 - this.iVec0[1]);
			this.fRec5[0] = (((fSlow10 * this.fRec5[1]) + (fSlow11 * this.fRec4[1])) + iTemp1);
			var fTemp2 = (this.fRec3[0] * ((fSlow7 * this.fRec4[0]) + 1));
			var fTemp3 = (fSlow4 * fTemp2);
			this.fVec2[0] = fTemp3;
			var fTemp4 = (this.fRec2[1] + (this.fConst2 * this.fVec2[1]));
			this.fRec2[0] = (fTemp4 - Math.floor(fTemp4));
			var iTemp5 = ((this.fRec2[0] - this.fRec2[1]) < 0);
			this.iVec3[0] = iTemp5;
			this.fRec7[0] = (fSlow14 + (0.999 * this.fRec7[1]));
			var fTemp6 = (fSlow13 + this.fRec7[0]);
			var iTemp7 = (fTemp6 < 23);
			var iTemp8 = (fTemp6 < 24);
			var fTemp9 = (fSlow13 + (this.fRec7[0] + -23));
			var iTemp10 = (fTemp6 < 22);
			var fTemp11 = (fSlow13 + (this.fRec7[0] + -22));
			var iTemp12 = (fTemp6 < 21);
			var fTemp13 = (fSlow13 + (this.fRec7[0] + -21));
			var iTemp14 = (fTemp6 < 20);
			var fTemp15 = (fSlow13 + (this.fRec7[0] + -20));
			var fTemp16 = (20 * fTemp15);
			var iTemp17 = (fTemp6 < 19);
			var iTemp18 = (fTemp6 < 18);
			var fTemp19 = (fSlow13 + (this.fRec7[0] + -18));
			var iTemp20 = (fTemp6 < 17);
			var fTemp21 = (fSlow13 + (this.fRec7[0] + -17));
			var iTemp22 = (fTemp6 < 16);
			var iTemp23 = (fTemp6 < 15);
			var fTemp24 = (fSlow13 + (this.fRec7[0] + -15));
			var fTemp25 = (20 * fTemp24);
			var iTemp26 = (fTemp6 < 14);
			var fTemp27 = (fSlow13 + (this.fRec7[0] + -14));
			var iTemp28 = (fTemp6 < 13);
			var iTemp29 = (fTemp6 < 12);
			var iTemp30 = (fTemp6 < 11);
			var fTemp31 = (fSlow13 + (this.fRec7[0] + -11));
			var iTemp32 = (fTemp6 < 10);
			var fTemp33 = (fSlow13 + (this.fRec7[0] + -10));
			var fTemp34 = (10 * fTemp33);
			var iTemp35 = (fTemp6 < 9);
			var fTemp36 = (fSlow13 + (this.fRec7[0] + -9));
			var iTemp37 = (fTemp6 < 8);
			var iTemp38 = (fTemp6 < 7);
			var fTemp39 = (fSlow13 + (this.fRec7[0] + -7));
			var iTemp40 = (fTemp6 < 6);
			var fTemp41 = (fSlow13 + (this.fRec7[0] + -6));
			var iTemp42 = (fTemp6 < 5);
			var fTemp43 = (this.fRec7[0] - fSlow15);
			var iTemp44 = (fTemp6 < 4);
			var fTemp45 = (fSlow13 + (this.fRec7[0] + -4));
			var fTemp46 = (10 * fTemp45);
			var iTemp47 = (fTemp6 < 3);
			var fTemp48 = (fSlow13 + (this.fRec7[0] + -3));
			var fTemp49 = (20 * fTemp48);
			var iTemp50 = (fTemp6 < 2);
			var fTemp51 = (fSlow13 + (this.fRec7[0] + -2));
			var fTemp52 = (20 * fTemp51);
			var iTemp53 = (fTemp6 < 1);
			var fTemp54 = (fSlow13 + (this.fRec7[0] + -1));
			var iTemp55 = (fTemp6 < 0);
			var fTemp56 = (20 * fTemp6);
			var fTemp57 = (iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp17?(iTemp18?(iTemp20?(iTemp22?(iTemp23?(iTemp26?(iTemp28?(iTemp29?(iTemp30?(iTemp32?(iTemp35?(iTemp37?(iTemp38?(iTemp40?(iTemp42?(iTemp44?(iTemp47?(iTemp50?(iTemp53?(iTemp55?80:(iTemp53?(80 - fTemp56):60)):(iTemp50?(60 - (10 * fTemp54)):50)):(iTemp47?(fTemp52 + 50):70)):(iTemp44?(70 - fTemp49):50)):(iTemp42?(fTemp46 + 50):60)):(iTemp40?(60 - (20 * fTemp43)):40)):(iTemp38?((20 * fTemp41) + 40):60)):(iTemp37?(60 - (20 * fTemp39)):40)):40):(iTemp32?(40 * (fTemp36 + 1)):80)):(iTemp30?(80 - fTemp34):70)):(iTemp29?(70 - (30 * fTemp31)):40)):40):40):(iTemp23?(40 * (fTemp27 + 1)):80)):(iTemp22?(80 - fTemp25):60)):60):(iTemp18?(60 - (20 * fTemp21)):40)):(iTemp17?((10 * fTemp19) + 40):50)):50):(iTemp12?(fTemp16 + 50):70)):(iTemp10?(70 - (30 * fTemp13)):40)):(iTemp7?((30 * fTemp11) + 40):70)):(iTemp8?(70 - (30 * fTemp9)):40));
			var fTemp58 = (this.fRec7[0] + iSlow17);
			var iTemp59 = (fTemp58 >= 5);
			var iTemp60 = (fTemp58 >= 3);
			var iTemp61 = (fTemp58 >= 2);
			var iTemp62 = (fTemp58 >= 1);
			var iTemp63 = (fTemp58 >= 4);
			var iTemp64 = (fTemp58 >= 8);
			var iTemp65 = (fTemp58 >= 7);
			var iTemp66 = (fTemp58 >= 6);
			var fTemp67 = (iTemp59?(iTemp64?2:(iTemp65?3:(iTemp66?3:2))):(iTemp60?(iTemp63?1.5:1):(iTemp61?1.25:(iTemp62?1.25:1))));
			this.fRec8[0] = ((fSlow9 * this.fRec9[1]) + (fSlow10 * this.fRec8[1]));
			this.fRec9[0] = (((fSlow10 * this.fRec9[1]) + (fSlow11 * this.fRec8[1])) + iTemp1);
			var fTemp68 = (fSlow4 * (this.fRec3[0] * ((fSlow7 * this.fRec8[0]) + 1)));
			var fTemp69 = (fTemp67 + (((iTemp59?(iTemp64?12:(iTemp65?12:(iTemp66?12:15))):(iTemp60?(iTemp63?4:10):(iTemp61?2.5:(iTemp62?2.5:10)))) - fTemp67) * ((fTemp68 <= fSlow19)?0:((fTemp68 >= fSlow20)?1:((fTemp68 - fSlow19) / fSlow21)))));
			this.fRec6[0] = ((this.fConst5 * this.fRec6[1]) + (this.fConst6 * (fTemp57 * fTemp69)));
			var fTemp70 = Math.exp((this.fConst4 * (0 - this.fRec6[0])));
			this.fRec10[0] = ((this.fConst5 * this.fRec10[1]) + (this.fConst6 * fTemp57));
			var fTemp71 = Math.exp((this.fConst4 * (0 - this.fRec10[0])));
			this.fRec1[0] = (this.iVec3[1] - ((this.fRec1[1] * (0 - (fTemp70 + fTemp71))) + ((fTemp70 * fTemp71) * this.fRec1[2])));
			var fTemp72 = ((0.00084 * (1000 - fTemp68)) + 0.8);
			var fTemp73 = ((0.00366667 * (400 - fTemp68)) + 3);
			var iTemp74 = (1 - (iTemp5 > 0));
			this.fRec13[0] = (fSlow14 + (0.999 * this.fRec13[1]));
			var fTemp75 = (fSlow13 + this.fRec13[0]);
			var iTemp76 = (fTemp75 < 23);
			var iTemp77 = (fTemp75 < 24);
			var fTemp78 = (fSlow13 + (this.fRec13[0] + -23));
			var iTemp79 = (fTemp75 < 22);
			var fTemp80 = (fSlow13 + (this.fRec13[0] + -22));
			var iTemp81 = (fTemp75 < 21);
			var fTemp82 = (fSlow13 + (this.fRec13[0] + -21));
			var iTemp83 = (fTemp75 < 20);
			var fTemp84 = (fSlow13 + (this.fRec13[0] + -20));
			var iTemp85 = (fTemp75 < 19);
			var fTemp86 = (fSlow13 + (this.fRec13[0] + -19));
			var iTemp87 = (fTemp75 < 18);
			var fTemp88 = (fSlow13 + (this.fRec13[0] + -18));
			var iTemp89 = (fTemp75 < 17);
			var fTemp90 = (fSlow13 + (this.fRec13[0] + -17));
			var iTemp91 = (fTemp75 < 16);
			var fTemp92 = (fSlow13 + (this.fRec13[0] + -16));
			var iTemp93 = (fTemp75 < 15);
			var fTemp94 = (fSlow13 + (this.fRec13[0] + -15));
			var iTemp95 = (fTemp75 < 14);
			var fTemp96 = (fSlow13 + (this.fRec13[0] + -14));
			var iTemp97 = (fTemp75 < 13);
			var fTemp98 = (fSlow13 + (this.fRec13[0] + -13));
			var iTemp99 = (fTemp75 < 12);
			var fTemp100 = (fSlow13 + (this.fRec13[0] + -12));
			var iTemp101 = (fTemp75 < 11);
			var fTemp102 = (fSlow13 + (this.fRec13[0] + -11));
			var iTemp103 = (fTemp75 < 10);
			var fTemp104 = (fSlow13 + (this.fRec13[0] + -10));
			var iTemp105 = (fTemp75 < 9);
			var fTemp106 = (fSlow13 + (this.fRec13[0] + -9));
			var iTemp107 = (fTemp75 < 8);
			var fTemp108 = (fSlow13 + (this.fRec13[0] + -8));
			var fTemp109 = (50 * fTemp108);
			var iTemp110 = (fTemp75 < 7);
			var fTemp111 = (fSlow13 + (this.fRec13[0] + -7));
			var iTemp112 = (fTemp75 < 6);
			var fTemp113 = (fSlow13 + (this.fRec13[0] + -6));
			var iTemp114 = (fTemp75 < 5);
			var fTemp115 = (this.fRec13[0] - fSlow15);
			var iTemp116 = (fTemp75 < 4);
			var fTemp117 = (fSlow13 + (this.fRec13[0] + -4));
			var iTemp118 = (fTemp75 < 3);
			var fTemp119 = (fSlow13 + (this.fRec13[0] + -3));
			var iTemp120 = (fTemp75 < 2);
			var fTemp121 = (fSlow13 + (this.fRec13[0] + -2));
			var iTemp122 = (fTemp75 < 1);
			var fTemp123 = (fSlow13 + (this.fRec13[0] + -1));
			var iTemp124 = (fTemp75 < 0);
			var fTemp125 = (iTemp76?(iTemp79?(iTemp81?(iTemp83?(iTemp85?(iTemp87?(iTemp89?(iTemp91?(iTemp93?(iTemp95?(iTemp97?(iTemp99?(iTemp101?(iTemp103?(iTemp105?(iTemp107?(iTemp110?(iTemp112?(iTemp114?(iTemp116?(iTemp118?(iTemp120?(iTemp122?(iTemp124?800:(iTemp122?(800 - (400 * fTemp75)):400)):(iTemp120?(400 - (50 * fTemp123)):350)):(iTemp118?((100 * fTemp121) + 350):450)):(iTemp116?(450 - (125 * fTemp119)):325)):(iTemp114?((275 * fTemp117) + 325):600)):(iTemp112?(600 - (200 * fTemp115)):400)):(iTemp110?(400 - (150 * fTemp113)):250)):(iTemp107?((150 * fTemp111) + 250):400)):(iTemp105?(400 - fTemp109):350)):(iTemp103?((310 * fTemp106) + 350):660)):(iTemp101?(660 - (220 * fTemp104)):440)):(iTemp99?(440 - (170 * fTemp102)):270)):(iTemp97?((160 * fTemp100) + 270):430)):(iTemp95?(430 - (60 * fTemp98)):370)):(iTemp93?((430 * fTemp96) + 370):800)):(iTemp91?(800 - (450 * fTemp94)):350)):(iTemp89?(350 - (80 * fTemp92)):270)):(iTemp87?((180 * fTemp90) + 270):450)):(iTemp85?(450 - (125 * fTemp88)):325)):(iTemp83?(325 * (fTemp86 + 1)):650)):(iTemp81?(650 - (250 * fTemp84)):400)):(iTemp79?(400 - (110 * fTemp82)):290)):(iTemp76?((110 * fTemp80) + 290):400)):(iTemp77?(400 - (50 * fTemp78)):350));
			var fTemp126 = ((this.fRec12[1] * iTemp74) + (this.fConst7 * ((fTemp125 <= fTemp3)?fTemp3:fTemp125)));
			this.fRec12[0] = (fTemp126 - Math.floor(fTemp126));
			var fTemp127 = (10 * fTemp11);
			var fTemp128 = (10 * fTemp15);
			var fTemp129 = (fSlow13 + (this.fRec7[0] + -19));
			var fTemp130 = (fSlow13 + (this.fRec7[0] + -16));
			var fTemp131 = (fSlow13 + (this.fRec7[0] + -13));
			var fTemp132 = (fSlow13 + (this.fRec7[0] + -12));
			var fTemp133 = (10 * fTemp36);
			var fTemp134 = (10 * fTemp43);
			var fTemp135 = (iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp17?(iTemp18?(iTemp20?(iTemp22?(iTemp23?(iTemp26?(iTemp28?(iTemp29?(iTemp30?(iTemp32?(iTemp35?(iTemp37?(iTemp38?(iTemp40?(iTemp42?(iTemp44?(iTemp47?(iTemp50?(iTemp53?(iTemp55?90:(iTemp53?(90 - (10 * fTemp6)):80)):(iTemp50?((20 * fTemp54) + 80):100)):(iTemp47?(100 - fTemp52):80)):(iTemp44?(80 - fTemp49):60)):(iTemp42?(fTemp46 + 60):70)):(iTemp40?(fTemp134 + 70):80)):(iTemp38?((10 * fTemp41) + 80):90)):(iTemp37?(90 - (10 * fTemp39)):80)):80):(iTemp32?(fTemp133 + 80):90)):(iTemp30?(90 - fTemp34):80)):(iTemp29?((10 * fTemp31) + 80):90)):(iTemp28?(90 - (10 * fTemp132)):80)):(iTemp26?(80 - (20 * fTemp131)):60)):(iTemp23?((30 * fTemp27) + 60):90)):(iTemp22?((10 * fTemp24) + 90):100)):(iTemp20?(100 - (10 * fTemp130)):90)):(iTemp18?(90 - (10 * fTemp21)):80)):(iTemp17?(80 - (20 * fTemp19)):60)):(iTemp14?((30 * fTemp129) + 60):90)):(iTemp12?(90 - fTemp128):80)):(iTemp10?((10 * fTemp13) + 80):90)):(iTemp7?(90 - fTemp127):80)):(iTemp8?(80 - (20 * fTemp9)):60));
			this.fRec15[0] = ((this.fConst5 * this.fRec15[1]) + (this.fConst6 * (fTemp135 * fTemp69)));
			var fTemp136 = Math.exp((this.fConst4 * (0 - this.fRec15[0])));
			this.fRec16[0] = ((this.fConst5 * this.fRec16[1]) + (this.fConst6 * fTemp135));
			var fTemp137 = Math.exp((this.fConst4 * (0 - this.fRec16[0])));
			this.fRec14[0] = (this.iVec3[1] - ((this.fRec14[1] * (0 - (fTemp136 + fTemp137))) + ((fTemp136 * fTemp137) * this.fRec14[2])));
			var fTemp138 = (fSlow13 + (this.fRec7[0] + -8));
			var fTemp139 = (iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp17?(iTemp18?(iTemp20?(iTemp22?(iTemp23?(iTemp26?(iTemp28?(iTemp29?(iTemp30?(iTemp32?(iTemp35?(iTemp37?(iTemp38?(iTemp40?(iTemp42?(iTemp44?(iTemp47?(iTemp50?(iTemp53?(iTemp55?0.630957:(iTemp53?(0.630957 - (0.567861 * fTemp6)):0.063096)):(iTemp50?((0.036904 * fTemp54) + 0.063096):0.1)):(iTemp47?((0.254813 * fTemp51) + 0.1):0.354813)):(iTemp44?(0.354813 - (0.103624 * fTemp48)):0.251189)):(iTemp42?((0.195495 * fTemp45) + 0.251189):0.446684)):(iTemp40?(0.446684 - (0.195495 * fTemp43)):0.251189)):(iTemp38?(0.251189 - (0.219566 * fTemp41)):0.031623)):(iTemp37?((0.250215 * fTemp39) + 0.031623):0.281838)):(iTemp35?(0.281838 - (0.181838 * fTemp138)):0.1)):(iTemp32?((0.401187 * fTemp36) + 0.1):0.501187)):(iTemp30?(0.501187 - (0.301661 * fTemp33)):0.199526)):(iTemp29?(0.199526 - (0.13643 * fTemp31)):0.063096)):(iTemp28?((0.253132 * fTemp132) + 0.063096):0.316228)):(iTemp26?(0.316228 - (0.216228 * fTemp131)):0.1)):(iTemp23?((0.401187 * fTemp27) + 0.1):0.501187)):(iTemp22?(0.501187 - (0.401187 * fTemp24)):0.1)):(iTemp20?((0.151189 * fTemp130) + 0.1):0.251189)):(iTemp18?((0.030649 * fTemp21) + 0.251189):0.281838)):(iTemp17?(0.281838 - (0.123349 * fTemp19)):0.158489)):(iTemp14?((0.342698 * fTemp129) + 0.158489):0.501187)):(iTemp12?(0.501187 - (0.301661 * fTemp15)):0.199526)):(iTemp10?(0.199526 - (0.021698 * fTemp13)):0.177828)):(iTemp7?((0.1384 * fTemp11) + 0.177828):0.316228)):(iTemp8?(0.316228 - (0.216228 * fTemp9)):0.1));
			var fTemp140 = (iTemp76?(iTemp79?(iTemp81?(iTemp83?(iTemp85?(iTemp87?(iTemp89?(iTemp91?(iTemp93?(iTemp95?(iTemp97?(iTemp99?(iTemp101?(iTemp103?(iTemp105?(iTemp107?(iTemp110?(iTemp112?(iTemp114?(iTemp116?(iTemp118?(iTemp120?(iTemp122?(iTemp124?1150:(iTemp122?((450 * fTemp75) + 1150):1600)):(iTemp120?((100 * fTemp123) + 1600):1700)):(iTemp118?(1700 - (900 * fTemp121)):800)):(iTemp116?(800 - (100 * fTemp119)):700)):(iTemp114?((340 * fTemp117) + 700):1040)):(iTemp112?((580 * fTemp115) + 1040):1620)):(iTemp110?((130 * fTemp113) + 1620):1750)):(iTemp107?(1750 - (1000 * fTemp111)):750)):(iTemp105?(750 - (150 * fTemp108)):600)):(iTemp103?((520 * fTemp106) + 600):1120)):(iTemp101?((680 * fTemp104) + 1120):1800)):(iTemp99?((50 * fTemp102) + 1800):1850)):(iTemp97?(1850 - (1030 * fTemp100)):820)):(iTemp95?(820 - (190 * fTemp98)):630)):(iTemp93?((520 * fTemp96) + 630):1150)):(iTemp91?((850 * fTemp94) + 1150):2000)):(iTemp89?((140 * fTemp92) + 2000):2140)):(iTemp87?(2140 - (1340 * fTemp90)):800)):(iTemp85?(800 - (100 * fTemp88)):700)):(iTemp83?((380 * fTemp86) + 700):1080)):(iTemp81?((620 * fTemp84) + 1080):1700)):(iTemp79?((170 * fTemp82) + 1700):1870)):(iTemp76?(1870 - (1070 * fTemp80)):800)):(iTemp77?(800 - (200 * fTemp78)):600));
			var fTemp141 = ((fSlow24 * fTemp2) + 30);
			var fTemp142 = ((iTemp74 * this.fRec17[1]) + (this.fConst7 * (iSlow23?(((fTemp140 >= 1300) & (fTemp3 >= 200))?(fTemp140 - (0.000952381 * ((fTemp3 + -200) * (fTemp140 + -1300)))):((fTemp140 <= fTemp141)?fTemp141:fTemp140)):fTemp140)));
			this.fRec17[0] = (fTemp142 - Math.floor(fTemp142));
			var fTemp143 = (50 * fTemp129);
			var fTemp144 = (20 * fTemp27);
			var fTemp145 = (20 * fTemp33);
			var fTemp146 = (20 * fTemp36);
			var fTemp147 = (60 * fTemp45);
			var fTemp148 = (iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp17?(iTemp18?(iTemp20?(iTemp22?(iTemp23?(iTemp26?(iTemp28?(iTemp29?(iTemp30?(iTemp32?(iTemp35?(iTemp37?(iTemp38?(iTemp40?(iTemp42?(iTemp44?(iTemp47?(iTemp50?120:(iTemp47?(120 - fTemp52):100)):(iTemp44?((70 * fTemp48) + 100):170)):(iTemp42?(170 - fTemp147):110)):(iTemp40?(110 - fTemp134):100)):100):100):100):(iTemp32?(fTemp146 + 100):120)):(iTemp30?(120 - fTemp145):100)):100):100):100):(iTemp23?(fTemp144 + 100):120)):120):(iTemp20?(120 - (20 * fTemp130)):100)):100):(iTemp17?((70 * fTemp19) + 100):170)):(iTemp14?(170 - fTemp143):120)):(iTemp12?(120 - fTemp16):100)):100):100):100);
			this.fRec19[0] = ((this.fConst5 * this.fRec19[1]) + (this.fConst6 * (fTemp148 * fTemp69)));
			var fTemp149 = Math.exp((this.fConst4 * (0 - this.fRec19[0])));
			this.fRec20[0] = ((this.fConst5 * this.fRec20[1]) + (this.fConst6 * fTemp148));
			var fTemp150 = Math.exp((this.fConst4 * (0 - this.fRec20[0])));
			this.fRec18[0] = (this.iVec3[1] - ((this.fRec18[1] * (0 - (fTemp149 + fTemp150))) + ((fTemp149 * fTemp150) * this.fRec18[2])));
			var fTemp151 = (iTemp18?((0.029314 * fTemp21) + 0.050119):0.079433);
			var fTemp152 = (iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp17?(iTemp18?(iTemp20?(iTemp22?(iTemp23?(iTemp26?(iTemp28?(iTemp29?(iTemp30?(iTemp32?(iTemp35?(iTemp37?(iTemp38?(iTemp40?(iTemp42?(iTemp44?(iTemp47?(iTemp50?(iTemp53?(iTemp55?0.1:(iTemp53?(0.1 - (0.068377 * fTemp6)):0.031623)):0.031623):(iTemp47?((0.126866 * fTemp51) + 0.031623):0.158489)):(iTemp44?(0.158489 - (0.126866 * fTemp48)):0.031623)):(iTemp42?((0.32319 * fTemp45) + 0.031623):0.354813)):0.354813):(iTemp38?(0.354813 - (0.196324 * fTemp41)):0.158489)):(iTemp37?(0.158489 - (0.069364 * fTemp39)):0.089125)):(iTemp35?(0.089125 - (0.064006 * fTemp138)):0.025119)):(iTemp32?((0.045676 * fTemp36) + 0.025119):0.070795)):(iTemp30?((0.055098 * fTemp33) + 0.070795):0.125893)):(iTemp29?(0.125893 - (0.062797 * fTemp31)):0.063096)):(iTemp28?(0.063096 - (0.012977 * fTemp132)):0.050119)):(iTemp26?((0.020676 * fTemp131) + 0.050119):0.070795)):(iTemp23?(0.070795 - (0.045676 * fTemp27)):0.025119)):(iTemp22?((0.152709 * fTemp24) + 0.025119):0.177828)):(iTemp20?(0.177828 - (0.127709 * fTemp130)):0.050119)):fTemp151):(iTemp17?(0.079433 - (0.06165 * fTemp19)):0.017783)):(iTemp14?((0.428901 * fTemp129) + 0.017783):0.446684)):(iTemp12?(0.446684 - (0.195495 * fTemp15)):0.251189)):(iTemp10?(0.251189 - (0.125296 * fTemp13)):0.125893)):(iTemp7?((0.125296 * fTemp11) + 0.125893):0.251189)):(iTemp8?(0.251189 - (0.109935 * fTemp9)):0.141254));
			var fTemp153 = (100 * fTemp78);
			var fTemp154 = (50 * fTemp104);
			var fTemp155 = ((iTemp74 * this.fRec21[1]) + (this.fConst7 * (iTemp76?(iTemp79?(iTemp81?(iTemp83?(iTemp85?(iTemp87?(iTemp89?(iTemp91?(iTemp93?(iTemp95?(iTemp97?(iTemp99?(iTemp101?(iTemp103?(iTemp105?(iTemp107?(iTemp110?(iTemp112?(iTemp114?(iTemp116?(iTemp118?(iTemp120?(iTemp122?(iTemp124?2800:(iTemp122?(2800 - (100 * fTemp75)):2700)):2700):(iTemp118?((130 * fTemp121) + 2700):2830)):(iTemp116?(2830 - (300 * fTemp119)):2530)):(iTemp114?(2530 - (280 * fTemp117)):2250)):(iTemp112?((150 * fTemp115) + 2250):2400)):(iTemp110?((200 * fTemp113) + 2400):2600)):(iTemp107?(2600 - (200 * fTemp111)):2400)):2400):(iTemp103?((350 * fTemp106) + 2400):2750)):(iTemp101?(2750 - fTemp154):2700)):(iTemp99?((200 * fTemp102) + 2700):2900)):(iTemp97?(2900 - (200 * fTemp100)):2700)):(iTemp95?((50 * fTemp98) + 2700):2750)):(iTemp93?((150 * fTemp96) + 2750):2900)):(iTemp91?(2900 - (100 * fTemp94)):2800)):(iTemp89?((150 * fTemp92) + 2800):2950)):(iTemp87?(2950 - (120 * fTemp90)):2830)):(iTemp85?(2830 - (130 * fTemp88)):2700)):(iTemp83?(2700 - (50 * fTemp86)):2650)):(iTemp81?(2650 - (50 * fTemp84)):2600)):(iTemp79?((200 * fTemp82) + 2600):2800)):(iTemp76?(2800 - (200 * fTemp80)):2600)):(iTemp77?(fTemp153 + 2600):2700))));
			this.fRec21[0] = (fTemp155 - Math.floor(fTemp155));
			var fTemp156 = (iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp17?(iTemp18?(iTemp20?(iTemp22?(iTemp23?(iTemp26?(iTemp28?(iTemp29?(iTemp30?(iTemp32?(iTemp35?(iTemp37?(iTemp38?(iTemp40?(iTemp42?(iTemp44?(iTemp47?(iTemp50?(iTemp53?(iTemp55?130:(iTemp53?(fTemp56 + 130):150)):150):(iTemp47?(150 - fTemp52):130)):(iTemp44?((50 * fTemp48) + 130):180)):(iTemp42?(180 - fTemp147):120)):120):120):120):120):(iTemp32?(fTemp133 + 120):130)):(iTemp30?(130 - fTemp34):120)):120):120):120):(iTemp23?((10 * fTemp27) + 120):130)):(iTemp22?(fTemp25 + 130):150)):(iTemp20?(150 - (30 * fTemp130)):120)):120):(iTemp17?((60 * fTemp19) + 120):180)):(iTemp14?(180 - fTemp143):130)):(iTemp12?(130 - fTemp128):120)):120):(iTemp7?(fTemp127 + 120):130)):(iTemp8?(130 - (10 * fTemp9)):120));
			this.fRec23[0] = ((this.fConst5 * this.fRec23[1]) + (this.fConst6 * (fTemp156 * fTemp69)));
			var fTemp157 = Math.exp((this.fConst4 * (0 - this.fRec23[0])));
			this.fRec24[0] = ((this.fConst5 * this.fRec24[1]) + (this.fConst6 * fTemp156));
			var fTemp158 = Math.exp((this.fConst4 * (0 - this.fRec24[0])));
			this.fRec22[0] = (this.iVec3[1] - ((this.fRec22[1] * (0 - (fTemp157 + fTemp158))) + ((fTemp157 * fTemp158) * this.fRec22[2])));
			var fTemp159 = (iTemp29?(0.1 - (0.084151 * fTemp31)):0.015849);
			var fTemp160 = (iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp17?(iTemp18?(iTemp20?(iTemp22?(iTemp23?(iTemp26?(iTemp28?(iTemp29?(iTemp30?(iTemp32?(iTemp35?(iTemp37?(iTemp38?(iTemp40?(iTemp42?(iTemp44?(iTemp47?(iTemp50?(iTemp53?(iTemp55?0.015849:(iTemp53?((0.001934 * fTemp6) + 0.015849):0.017783)):(iTemp50?(0.017783 - (0.001934 * fTemp54)):0.015849)):(iTemp47?((0.023962 * fTemp51) + 0.015849):0.039811)):(iTemp44?(0.039811 - (0.029811 * fTemp48)):0.01)):(iTemp42?((0.344813 * fTemp45) + 0.01):0.354813)):(iTemp40?(0.354813 - (0.103624 * fTemp43)):0.251189)):(iTemp38?(0.251189 - (0.171756 * fTemp41)):0.079433)):(iTemp37?((0.020567 * fTemp39) + 0.079433):0.1)):(iTemp35?(0.1 - (0.060189 * fTemp138)):0.039811)):(iTemp32?((0.023285 * fTemp36) + 0.039811):0.063096)):(iTemp30?((0.036904 * fTemp33) + 0.063096):0.1)):fTemp159):(iTemp28?((0.063584 * fTemp132) + 0.015849):0.079433)):(iTemp26?(0.079433 - (0.04781 * fTemp131)):0.031623)):(iTemp23?((0.068377 * fTemp27) + 0.031623):0.1)):(iTemp22?(0.1 - (0.09 * fTemp24)):0.01)):(iTemp20?((0.040119 * fTemp130) + 0.01):0.050119)):fTemp151):(iTemp17?(0.079433 - (0.069433 * fTemp19)):0.01)):(iTemp14?((0.388107 * fTemp129) + 0.01):0.398107)):(iTemp12?(0.398107 - (0.198581 * fTemp15)):0.199526)):(iTemp10?(0.199526 - (0.099526 * fTemp13)):0.1)):(iTemp7?((0.151189 * fTemp11) + 0.1):0.251189)):(iTemp8?(0.251189 - (0.051663 * fTemp9)):0.199526));
			var fTemp161 = (350 * fTemp115);
			var fTemp162 = ((iTemp74 * this.fRec25[1]) + (this.fConst7 * (iTemp76?(iTemp79?(iTemp81?(iTemp83?(iTemp85?(iTemp87?(iTemp89?(iTemp91?(iTemp93?(iTemp95?(iTemp97?(iTemp99?(iTemp101?(iTemp103?(iTemp105?(iTemp107?(iTemp110?(iTemp112?(iTemp114?(iTemp116?(iTemp118?(iTemp120?(iTemp122?(iTemp124?3500:(iTemp122?(3500 - (200 * fTemp75)):3300)):(iTemp120?((400 * fTemp123) + 3300):3700)):(iTemp118?(3700 - (200 * fTemp121)):3500)):3500):(iTemp114?(3500 - (1050 * fTemp117)):2450)):(iTemp112?(fTemp161 + 2450):2800)):(iTemp110?((250 * fTemp113) + 2800):3050)):(iTemp107?(3050 - (450 * fTemp111)):2600)):(iTemp105?((75 * fTemp108) + 2600):2675)):(iTemp103?((325 * fTemp106) + 2675):3000)):3000):(iTemp99?((350 * fTemp102) + 3000):3350)):(iTemp97?(3350 - (350 * fTemp100)):3000)):3000):(iTemp93?((900 * fTemp96) + 3000):3900)):(iTemp91?(3900 - (300 * fTemp94)):3600)):(iTemp89?((300 * fTemp92) + 3600):3900)):(iTemp87?(3900 - (100 * fTemp90)):3800)):3800):(iTemp83?(3800 - (900 * fTemp86)):2900)):(iTemp81?((300 * fTemp84) + 2900):3200)):(iTemp79?((50 * fTemp82) + 3200):3250)):(iTemp76?(3250 - (450 * fTemp80)):2800)):(iTemp77?(fTemp153 + 2800):2900))));
			this.fRec25[0] = (fTemp162 - Math.floor(fTemp162));
			var fTemp163 = (iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp17?(iTemp18?(iTemp20?(iTemp22?(iTemp23?(iTemp26?(iTemp28?(iTemp29?(iTemp30?(iTemp32?(iTemp35?(iTemp37?(iTemp38?(iTemp40?(iTemp42?(iTemp44?(iTemp47?(iTemp50?(iTemp53?(iTemp55?140:(iTemp53?((60 * fTemp6) + 140):200)):200):(iTemp47?(200 - (65 * fTemp51)):135)):(iTemp44?((65 * fTemp48) + 135):200)):(iTemp42?(200 - (70 * fTemp45)):130)):(iTemp40?(130 - fTemp134):120)):120):120):120):(iTemp32?(fTemp146 + 120):140)):(iTemp30?(140 - fTemp145):120)):120):120):120):(iTemp23?(fTemp144 + 120):140)):(iTemp22?((60 * fTemp24) + 140):200)):(iTemp20?(200 - (80 * fTemp130)):120)):120):(iTemp17?((80 * fTemp19) + 120):200)):(iTemp14?(200 - (60 * fTemp129)):140)):(iTemp12?(140 - fTemp16):120)):120):(iTemp7?((15 * fTemp11) + 120):135)):(iTemp8?(135 - (15 * fTemp9)):120));
			this.fRec27[0] = ((this.fConst5 * this.fRec27[1]) + (this.fConst6 * (fTemp163 * fTemp69)));
			var fTemp164 = Math.exp((this.fConst4 * (0 - this.fRec27[0])));
			this.fRec28[0] = ((this.fConst5 * this.fRec28[1]) + (this.fConst6 * fTemp163));
			var fTemp165 = Math.exp((this.fConst4 * (0 - this.fRec28[0])));
			this.fRec26[0] = (this.iVec3[1] - ((this.fRec26[1] * (0 - (fTemp164 + fTemp165))) + ((fTemp164 * fTemp165) * this.fRec26[2])));
			var fTemp166 = (iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp17?(iTemp18?(iTemp20?(iTemp22?(iTemp23?(iTemp26?(iTemp28?(iTemp29?(iTemp30?(iTemp32?(iTemp35?(iTemp37?(iTemp38?(iTemp40?(iTemp42?(iTemp44?(iTemp47?(iTemp50?0.001:(iTemp47?((0.000778 * fTemp51) + 0.001):0.001778)):(iTemp44?(0.001778 - (0.001147 * fTemp48)):0.000631)):(iTemp42?((0.099369 * fTemp45) + 0.000631):0.1)):(iTemp40?((0.025893 * fTemp43) + 0.1):0.125893)):(iTemp38?(0.125893 - (0.086082 * fTemp41)):0.039811)):(iTemp37?(0.039811 - (0.029811 * fTemp39)):0.01)):(iTemp35?((0.005849 * fTemp138) + 0.01):0.015849)):(iTemp32?(0.015849 - (0.00326 * fTemp36)):0.012589)):(iTemp30?((0.087411 * fTemp33) + 0.012589):0.1)):fTemp159):(iTemp28?((0.004104 * fTemp132) + 0.015849):0.019953)):0.019953):(iTemp23?(0.019953 - (0.016791 * fTemp27)):0.003162)):(iTemp22?(0.003162 - (0.001577 * fTemp24)):0.001585)):(iTemp20?((0.004725 * fTemp130) + 0.001585):0.00631)):(iTemp18?(0.00631 - (0.003148 * fTemp21)):0.003162)):(iTemp17?(0.003162 - (0.002162 * fTemp19)):0.001)):(iTemp14?((0.078433 * fTemp129) + 0.001):0.079433)):(iTemp12?((0.020567 * fTemp15) + 0.079433):0.1)):(iTemp10?(0.1 - (0.068377 * fTemp13)):0.031623)):(iTemp7?((0.018496 * fTemp11) + 0.031623):0.050119)):0.050119);
			var fTemp167 = ((iTemp74 * this.fRec29[1]) + (this.fConst7 * (iTemp76?(iTemp79?(iTemp81?(iTemp83?(iTemp85?(iTemp87?(iTemp89?(iTemp91?(iTemp93?(iTemp95?(iTemp97?(iTemp99?(iTemp101?(iTemp103?(iTemp105?(iTemp107?(iTemp110?(iTemp112?(iTemp114?(iTemp116?4950:(iTemp114?(4950 - (2200 * fTemp117)):2750)):(iTemp112?(fTemp161 + 2750):3100)):(iTemp110?((240 * fTemp113) + 3100):3340)):(iTemp107?(3340 - (440 * fTemp111)):2900)):(iTemp105?(fTemp109 + 2900):2950)):(iTemp103?((400 * fTemp106) + 2950):3350)):(iTemp101?(3350 - fTemp154):3300)):(iTemp99?((290 * fTemp102) + 3300):3590)):(iTemp97?(3590 - (290 * fTemp100)):3300)):(iTemp95?((100 * fTemp98) + 3300):3400)):(iTemp93?((1550 * fTemp96) + 3400):4950)):4950):4950):4950):4950):(iTemp83?(4950 - (1700 * fTemp86)):3250)):(iTemp81?((330 * fTemp84) + 3250):3580)):(iTemp79?(3580 - (40 * fTemp82)):3540)):(iTemp76?(3540 - (540 * fTemp80)):3000)):(iTemp77?((300 * fTemp78) + 3000):3300))));
			this.fRec29[0] = (fTemp167 - Math.floor(fTemp167));
			var fTemp168 = (fSlow0 * (this.fRec0[0] * (((((((this.fRec1[0] * (iSlow22?fTemp73:fTemp72)) * (1 - (fTemp71 + (fTemp70 * (1 - fTemp71))))) * ftbl0mydspSIG0[(65536 * this.fRec12[0])]) + (((this.fRec14[0] * (iSlow22?(fTemp73 * fTemp139):(fTemp72 * fTemp139))) * (1 - (fTemp137 + (fTemp136 * (1 - fTemp137))))) * ftbl0mydspSIG0[(65536 * this.fRec17[0])])) + (((this.fRec18[0] * (iSlow22?(fTemp73 * fTemp152):(fTemp72 * fTemp152))) * (1 - (fTemp150 + (fTemp149 * (1 - fTemp150))))) * ftbl0mydspSIG0[(65536 * this.fRec21[0])])) + (((this.fRec22[0] * (iSlow22?(fTemp73 * fTemp160):(fTemp72 * fTemp160))) * (1 - (fTemp158 + (fTemp157 * (1 - fTemp158))))) * ftbl0mydspSIG0[(65536 * this.fRec25[0])])) + (((this.fRec26[0] * (iSlow22?(fTemp73 * fTemp166):(fTemp72 * fTemp166))) * (1 - (fTemp165 + (fTemp164 * (1 - fTemp165))))) * ftbl0mydspSIG0[(65536 * this.fRec29[0])]))));
			output0[i] = fTemp168;
			output1[i] = fTemp168;
			this.iVec0[1] = this.iVec0[0];
			this.fVec1[1] = this.fVec1[0];
			this.fRec0[1] = this.fRec0[0];
			this.fRec3[1] = this.fRec3[0];
			this.fRec4[1] = this.fRec4[0];
			this.fRec5[1] = this.fRec5[0];
			this.fVec2[1] = this.fVec2[0];
			this.fRec2[1] = this.fRec2[0];
			this.iVec3[1] = this.iVec3[0];
			this.fRec7[1] = this.fRec7[0];
			this.fRec8[1] = this.fRec8[0];
			this.fRec9[1] = this.fRec9[0];
			this.fRec6[1] = this.fRec6[0];
			this.fRec10[1] = this.fRec10[0];
			this.fRec1[2] = this.fRec1[1];
			this.fRec1[1] = this.fRec1[0];
			this.fRec13[1] = this.fRec13[0];
			this.fRec12[1] = this.fRec12[0];
			this.fRec15[1] = this.fRec15[0];
			this.fRec16[1] = this.fRec16[0];
			this.fRec14[2] = this.fRec14[1];
			this.fRec14[1] = this.fRec14[0];
			this.fRec17[1] = this.fRec17[0];
			this.fRec19[1] = this.fRec19[0];
			this.fRec20[1] = this.fRec20[0];
			this.fRec18[2] = this.fRec18[1];
			this.fRec18[1] = this.fRec18[0];
			this.fRec21[1] = this.fRec21[0];
			this.fRec23[1] = this.fRec23[0];
			this.fRec24[1] = this.fRec24[0];
			this.fRec22[2] = this.fRec22[1];
			this.fRec22[1] = this.fRec22[0];
			this.fRec25[1] = this.fRec25[0];
			this.fRec27[1] = this.fRec27[0];
			this.fRec28[1] = this.fRec28[0];
			this.fRec26[2] = this.fRec26[1];
			this.fRec26[1] = this.fRec26[0];
			this.fRec29[1] = this.fRec29[0];
			
		}
		
	}
	
}

