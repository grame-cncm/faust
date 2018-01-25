
this.min_f = function(dummy0, dummy1);
this.max_f = function(dummy0, dummy1);
this.mydsp_faustpower2_f = function(value) {
	return (value * value);
	
}

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
	this.fRec1 = new Float32Array(2);
	this.fHslider4;
	this.fRec2 = new Float32Array(2);
	this.fConst2;
	this.fHslider5;
	this.fHslider6;
	this.fRec5 = new Float32Array(2);
	this.fHslider7;
	this.fConst3;
	this.fHslider8;
	this.fRec6 = new Float32Array(2);
	this.fRec7 = new Float32Array(2);
	this.fRec3 = new Float32Array(2);
	this.iRec8 = new Int32Array(2);
	this.fConst4;
	this.fHslider9;
	this.fHslider10;
	this.fRec9 = new Float32Array(2);
	this.fRec10 = new Float32Array(2);
	this.fRec11 = new Float32Array(2);
	this.fRec0 = new Float32Array(3);
	this.fRec12 = new Float32Array(3);
	this.fRec13 = new Float32Array(3);
	this.fRec14 = new Float32Array(3);
	this.fRec15 = new Float32Array(3);
	
	this.metadata = function(m) { 
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
		m.declare("description", "Simple MIDI-controllable source-filter vocal synthesizer.");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("license", "MIT");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "Vocal BandPass MIDI");
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
		
	}
	
	this.instanceConstants = function(samplingFreq) {
		this.fSamplingFreq = samplingFreq;
		this.fConst0 = min_f(192000, max_f(1, this.fSamplingFreq));
		this.fConst1 = (1000 / this.fConst0);
		this.fConst2 = (1 / this.fConst0);
		this.fConst3 = (6.28319 / this.fConst0);
		this.fConst4 = (3.14159 / this.fConst0);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 0.5;
		this.fButton0 = 0;
		this.fHslider1 = 0;
		this.fHslider2 = 0.9;
		this.fHslider3 = 10;
		this.fHslider4 = 0;
		this.fHslider5 = 440;
		this.fHslider6 = 1;
		this.fHslider7 = 0.5;
		this.fHslider8 = 6;
		this.fHslider9 = 0;
		this.fHslider10 = 0;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.iVec0[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fVec1[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec1[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec2[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec5[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fRec6[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			this.fRec7[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			this.fRec3[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			this.iRec8[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			this.fRec9[l9] = 0;
			
		}
		for (var l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			this.fRec10[l10] = 0;
			
		}
		for (var l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			this.fRec11[l11] = 0;
			
		}
		for (var l12 = 0; (l12 < 3); l12 = (l12 + 1)) {
			this.fRec0[l12] = 0;
			
		}
		for (var l13 = 0; (l13 < 3); l13 = (l13 + 1)) {
			this.fRec12[l13] = 0;
			
		}
		for (var l14 = 0; (l14 < 3); l14 = (l14 + 1)) {
			this.fRec13[l14] = 0;
			
		}
		for (var l15 = 0; (l15 < 3); l15 = (l15 + 1)) {
			this.fRec14[l15] = 0;
			
		}
		for (var l16 = 0; (l16 < 3); l16 = (l16 + 1)) {
			this.fRec15[l16] = 0;
			
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
		ui_interface.declare("fHslider5", "0", "");
		ui_interface.declare("fHslider5", "style", "knob");
		ui_interface.addHorizontalSlider("freq", function handler(obj) { function setval(val) { obj.fHslider5 = val; } return setval; }(this), 440, 50, 1000, 0.01);
		ui_interface.declare("fHslider6", "1", "");
		ui_interface.declare("fHslider6", "hidden", "1");
		ui_interface.declare("fHslider6", "midi", "pitchwheel");
		ui_interface.declare("fHslider6", "style", "knob");
		ui_interface.addHorizontalSlider("bend", function handler(obj) { function setval(val) { obj.fHslider6 = val; } return setval; }(this), 1, 0, 10, 0.01);
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
		ui_interface.declare("fHslider9", "0", "");
		ui_interface.declare("fHslider9", "style", "knob");
		ui_interface.addHorizontalSlider("voiceType", function handler(obj) { function setval(val) { obj.fHslider9 = val; } return setval; }(this), 0, 0, 4, 1);
		ui_interface.declare("fHslider10", "1", "");
		ui_interface.declare("fHslider10", "midi", "ctrl 1");
		ui_interface.declare("fHslider10", "style", "knob");
		ui_interface.addHorizontalSlider("vowel", function handler(obj) { function setval(val) { obj.fHslider10 = val; } return setval; }(this), 0, 0, 4, 0.01);
		ui_interface.declare("fHslider4", "2", "");
		ui_interface.declare("fHslider4", "style", "knob");
		ui_interface.addHorizontalSlider("fricative", function handler(obj) { function setval(val) { obj.fHslider4 = val; } return setval; }(this), 0, 0, 1, 0.01);
		ui_interface.declare("fHslider8", "3", "");
		ui_interface.declare("fHslider8", "style", "knob");
		ui_interface.addHorizontalSlider("vibratoFreq", function handler(obj) { function setval(val) { obj.fHslider8 = val; } return setval; }(this), 6, 1, 10, 0.01);
		ui_interface.declare("fHslider7", "4", "");
		ui_interface.declare("fHslider7", "style", "knob");
		ui_interface.addHorizontalSlider("vibratoGain", function handler(obj) { function setval(val) { obj.fHslider7 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
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
		var fSlow3 = ((fSlow1 * this.fHslider2) * (1 - fSlow2));
		var fSlow4 = (0.001 * this.fHslider4);
		var fSlow5 = this.fHslider5;
		var iSlow6 = (fSlow1 == 0);
		var fSlow7 = this.fHslider6;
		var fSlow8 = (0.1 * this.fHslider7);
		var fSlow9 = (this.fConst3 * this.fHslider8);
		var fSlow10 = Math.sin(fSlow9);
		var fSlow11 = Math.cos(fSlow9);
		var fSlow12 = (0 - fSlow10);
		var fSlow13 = this.fHslider9;
		var fSlow14 = (5 * fSlow13);
		var fSlow15 = (0.001 * this.fHslider10);
		var fSlow16 = (5 * (1 - fSlow13));
		var iSlow17 = (((fSlow13 == 0)?1:((fSlow13 == 3)?1:0)) == 0);
		var iSlow18 = (fSlow13 != 2);
		var fSlow19 = (2 * fSlow5);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iVec0[0] = 1;
			this.fVec1[0] = fSlow1;
			this.fRec1[0] = (fSlow3 + (fSlow2 * this.fRec1[1]));
			this.fRec2[0] = (fSlow4 + (0.999 * this.fRec2[1]));
			var iTemp0 = ((fSlow1 == this.fVec1[1]) | iSlow6);
			this.fRec5[0] = ((0.999 * (this.fRec5[1] * iTemp0)) + (fSlow7 * (1 - (0.999 * iTemp0))));
			this.fRec6[0] = ((fSlow10 * this.fRec7[1]) + (fSlow11 * this.fRec6[1]));
			var iTemp1 = (1 - this.iVec0[1]);
			this.fRec7[0] = (((fSlow11 * this.fRec7[1]) + (fSlow12 * this.fRec6[1])) + iTemp1);
			var fTemp2 = max_f(1e-07, Math.abs((fSlow5 * (this.fRec5[0] * ((fSlow8 * this.fRec6[0]) + 1)))));
			var fTemp3 = (this.fRec3[1] + (this.fConst2 * fTemp2));
			var fTemp4 = (fTemp3 + -1);
			var iTemp5 = (fTemp4 < 0);
			this.fRec3[0] = (iTemp5?fTemp3:fTemp4);
			var fRec4 = (iTemp5?fTemp3:(fTemp3 + (fTemp4 * (1 - (this.fConst0 / fTemp2)))));
			this.iRec8[0] = ((1103515245 * this.iRec8[1]) + 12345);
			var fTemp6 = (this.fRec1[0] * (((1 - this.fRec2[0]) * ((2 * fRec4) + -1)) + (4.65661e-10 * (this.fRec2[0] * this.iRec8[0]))));
			this.fRec9[0] = (fSlow15 + (0.999 * this.fRec9[1]));
			var fTemp7 = (fSlow14 + this.fRec9[0]);
			var iTemp8 = (fTemp7 < 23);
			var iTemp9 = (fTemp7 < 24);
			var fTemp10 = (fSlow14 + (this.fRec9[0] + -23));
			var iTemp11 = (fTemp7 < 22);
			var fTemp12 = (fSlow14 + (this.fRec9[0] + -22));
			var iTemp13 = (fTemp7 < 21);
			var fTemp14 = (fSlow14 + (this.fRec9[0] + -21));
			var iTemp15 = (fTemp7 < 20);
			var fTemp16 = (fSlow14 + (this.fRec9[0] + -20));
			var iTemp17 = (fTemp7 < 19);
			var fTemp18 = (fSlow14 + (this.fRec9[0] + -19));
			var iTemp19 = (fTemp7 < 18);
			var fTemp20 = (fSlow14 + (this.fRec9[0] + -18));
			var iTemp21 = (fTemp7 < 17);
			var fTemp22 = (fSlow14 + (this.fRec9[0] + -17));
			var iTemp23 = (fTemp7 < 16);
			var fTemp24 = (fSlow14 + (this.fRec9[0] + -16));
			var fTemp25 = (80 * fTemp24);
			var iTemp26 = (fTemp7 < 15);
			var fTemp27 = (fSlow14 + (this.fRec9[0] + -15));
			var iTemp28 = (fTemp7 < 14);
			var fTemp29 = (fSlow14 + (this.fRec9[0] + -14));
			var iTemp30 = (fTemp7 < 13);
			var fTemp31 = (fSlow14 + (this.fRec9[0] + -13));
			var iTemp32 = (fTemp7 < 12);
			var fTemp33 = (fSlow14 + (this.fRec9[0] + -12));
			var iTemp34 = (fTemp7 < 11);
			var fTemp35 = (fSlow14 + (this.fRec9[0] + -11));
			var iTemp36 = (fTemp7 < 10);
			var fTemp37 = (fSlow14 + (this.fRec9[0] + -10));
			var iTemp38 = (fTemp7 < 9);
			var fTemp39 = (fSlow14 + (this.fRec9[0] + -9));
			var iTemp40 = (fTemp7 < 8);
			var fTemp41 = (fSlow14 + (this.fRec9[0] + -8));
			var fTemp42 = (50 * fTemp41);
			var iTemp43 = (fTemp7 < 7);
			var fTemp44 = (fSlow14 + (this.fRec9[0] + -7));
			var iTemp45 = (fTemp7 < 6);
			var fTemp46 = (fSlow14 + (this.fRec9[0] + -6));
			var iTemp47 = (fTemp7 < 5);
			var fTemp48 = (this.fRec9[0] - fSlow16);
			var iTemp49 = (fTemp7 < 4);
			var fTemp50 = (fSlow14 + (this.fRec9[0] + -4));
			var iTemp51 = (fTemp7 < 3);
			var fTemp52 = (fSlow14 + (this.fRec9[0] + -3));
			var iTemp53 = (fTemp7 < 2);
			var fTemp54 = (fSlow14 + (this.fRec9[0] + -2));
			var iTemp55 = (fTemp7 < 1);
			var fTemp56 = (fSlow14 + (this.fRec9[0] + -1));
			var iTemp57 = (fTemp7 < 0);
			var fTemp58 = (iTemp8?(iTemp11?(iTemp13?(iTemp15?(iTemp17?(iTemp19?(iTemp21?(iTemp23?(iTemp26?(iTemp28?(iTemp30?(iTemp32?(iTemp34?(iTemp36?(iTemp38?(iTemp40?(iTemp43?(iTemp45?(iTemp47?(iTemp49?(iTemp51?(iTemp53?(iTemp55?(iTemp57?800:(iTemp55?(800 - (400 * fTemp7)):400)):(iTemp53?(400 - (50 * fTemp56)):350)):(iTemp51?((100 * fTemp54) + 350):450)):(iTemp49?(450 - (125 * fTemp52)):325)):(iTemp47?((275 * fTemp50) + 325):600)):(iTemp45?(600 - (200 * fTemp48)):400)):(iTemp43?(400 - (150 * fTemp46)):250)):(iTemp40?((150 * fTemp44) + 250):400)):(iTemp38?(400 - fTemp42):350)):(iTemp36?((310 * fTemp39) + 350):660)):(iTemp34?(660 - (220 * fTemp37)):440)):(iTemp32?(440 - (170 * fTemp35)):270)):(iTemp30?((160 * fTemp33) + 270):430)):(iTemp28?(430 - (60 * fTemp31)):370)):(iTemp26?((430 * fTemp29) + 370):800)):(iTemp23?(800 - (450 * fTemp27)):350)):(iTemp21?(350 - fTemp25):270)):(iTemp19?((180 * fTemp22) + 270):450)):(iTemp17?(450 - (125 * fTemp20)):325)):(iTemp15?(325 * (fTemp18 + 1)):650)):(iTemp13?(650 - (250 * fTemp16)):400)):(iTemp11?(400 - (110 * fTemp14)):290)):(iTemp8?((110 * fTemp12) + 290):400)):(iTemp9?(400 - (50 * fTemp10)):350));
			this.fRec10[0] = ((fSlow10 * this.fRec11[1]) + (fSlow11 * this.fRec10[1]));
			this.fRec11[0] = (((fSlow11 * this.fRec11[1]) + (fSlow12 * this.fRec10[1])) + iTemp1);
			var fTemp59 = (this.fRec5[0] * ((fSlow8 * this.fRec10[0]) + 1));
			var fTemp60 = (fSlow5 * fTemp59);
			var fTemp61 = ((fTemp58 <= fTemp60)?fTemp60:fTemp58);
			var fTemp62 = Math.tan((this.fConst4 * fTemp61));
			var fTemp63 = (1 / fTemp62);
			var fTemp64 = (20 * fTemp16);
			var fTemp65 = (20 * fTemp27);
			var fTemp66 = (10 * fTemp37);
			var fTemp67 = (10 * fTemp50);
			var fTemp68 = (20 * fTemp52);
			var fTemp69 = (20 * fTemp54);
			var fTemp70 = (20 * fTemp7);
			var fTemp71 = ((iTemp8?(iTemp11?(iTemp13?(iTemp15?(iTemp17?(iTemp19?(iTemp21?(iTemp23?(iTemp26?(iTemp28?(iTemp30?(iTemp32?(iTemp34?(iTemp36?(iTemp38?(iTemp40?(iTemp43?(iTemp45?(iTemp47?(iTemp49?(iTemp51?(iTemp53?(iTemp55?(iTemp57?80:(iTemp55?(80 - fTemp70):60)):(iTemp53?(60 - (10 * fTemp56)):50)):(iTemp51?(fTemp69 + 50):70)):(iTemp49?(70 - fTemp68):50)):(iTemp47?(fTemp67 + 50):60)):(iTemp45?(60 - (20 * fTemp48)):40)):(iTemp43?((20 * fTemp46) + 40):60)):(iTemp40?(60 - (20 * fTemp44)):40)):40):(iTemp36?(40 * (fTemp39 + 1)):80)):(iTemp34?(80 - fTemp66):70)):(iTemp32?(70 - (30 * fTemp35)):40)):40):40):(iTemp26?(40 * (fTemp29 + 1)):80)):(iTemp23?(80 - fTemp65):60)):60):(iTemp19?(60 - (20 * fTemp22)):40)):(iTemp17?((10 * fTemp20) + 40):50)):50):(iTemp13?(fTemp64 + 50):70)):(iTemp11?(70 - (30 * fTemp14)):40)):(iTemp8?((30 * fTemp12) + 40):70)):(iTemp9?(70 - (30 * fTemp10)):40)) / fTemp61);
			var fTemp72 = (((fTemp63 + fTemp71) / fTemp62) + 1);
			this.fRec0[0] = (fTemp6 - (((this.fRec0[2] * (((fTemp63 - fTemp71) / fTemp62) + 1)) + (2 * (this.fRec0[1] * (1 - (1 / mydsp_faustpower2_f(fTemp62)))))) / fTemp72));
			var fTemp73 = ((0.00084 * (1000 - fTemp60)) + 0.8);
			var fTemp74 = ((0.00366667 * (400 - fTemp60)) + 3);
			var fTemp75 = (iSlow17?fTemp74:fTemp73);
			var fTemp76 = (iTemp8?(iTemp11?(iTemp13?(iTemp15?(iTemp17?(iTemp19?(iTemp21?(iTemp23?(iTemp26?(iTemp28?(iTemp30?(iTemp32?(iTemp34?(iTemp36?(iTemp38?(iTemp40?(iTemp43?(iTemp45?(iTemp47?(iTemp49?(iTemp51?(iTemp53?(iTemp55?(iTemp57?1150:(iTemp55?((450 * fTemp7) + 1150):1600)):(iTemp53?((100 * fTemp56) + 1600):1700)):(iTemp51?(1700 - (900 * fTemp54)):800)):(iTemp49?(800 - (100 * fTemp52)):700)):(iTemp47?((340 * fTemp50) + 700):1040)):(iTemp45?((580 * fTemp48) + 1040):1620)):(iTemp43?((130 * fTemp46) + 1620):1750)):(iTemp40?(1750 - (1000 * fTemp44)):750)):(iTemp38?(750 - (150 * fTemp41)):600)):(iTemp36?((520 * fTemp39) + 600):1120)):(iTemp34?((680 * fTemp37) + 1120):1800)):(iTemp32?((50 * fTemp35) + 1800):1850)):(iTemp30?(1850 - (1030 * fTemp33)):820)):(iTemp28?(820 - (190 * fTemp31)):630)):(iTemp26?((520 * fTemp29) + 630):1150)):(iTemp23?((850 * fTemp27) + 1150):2000)):(iTemp21?((140 * fTemp24) + 2000):2140)):(iTemp19?(2140 - (1340 * fTemp22)):800)):(iTemp17?(800 - (100 * fTemp20)):700)):(iTemp15?((380 * fTemp18) + 700):1080)):(iTemp13?((620 * fTemp16) + 1080):1700)):(iTemp11?((170 * fTemp14) + 1700):1870)):(iTemp8?(1870 - (1070 * fTemp12)):800)):(iTemp9?(800 - (200 * fTemp10)):600));
			var fTemp77 = ((fSlow19 * fTemp59) + 30);
			var fTemp78 = (iSlow18?(((fTemp76 >= 1300) & (fTemp60 >= 200))?(fTemp76 - (0.000952381 * ((fTemp60 + -200) * (fTemp76 + -1300)))):((fTemp76 <= fTemp77)?fTemp77:fTemp76)):fTemp76);
			var fTemp79 = Math.tan((this.fConst4 * fTemp78));
			var fTemp80 = (1 / fTemp79);
			var fTemp81 = (10 * fTemp12);
			var fTemp82 = (10 * fTemp16);
			var fTemp83 = (10 * fTemp39);
			var fTemp84 = (10 * fTemp48);
			var fTemp85 = ((iTemp8?(iTemp11?(iTemp13?(iTemp15?(iTemp17?(iTemp19?(iTemp21?(iTemp23?(iTemp26?(iTemp28?(iTemp30?(iTemp32?(iTemp34?(iTemp36?(iTemp38?(iTemp40?(iTemp43?(iTemp45?(iTemp47?(iTemp49?(iTemp51?(iTemp53?(iTemp55?(iTemp57?90:(iTemp55?(90 - (10 * fTemp7)):80)):(iTemp53?((20 * fTemp56) + 80):100)):(iTemp51?(100 - fTemp69):80)):(iTemp49?(80 - fTemp68):60)):(iTemp47?(fTemp67 + 60):70)):(iTemp45?(fTemp84 + 70):80)):(iTemp43?((10 * fTemp46) + 80):90)):(iTemp40?(90 - (10 * fTemp44)):80)):80):(iTemp36?(fTemp83 + 80):90)):(iTemp34?(90 - fTemp66):80)):(iTemp32?((10 * fTemp35) + 80):90)):(iTemp30?(90 - (10 * fTemp33)):80)):(iTemp28?(80 - (20 * fTemp31)):60)):(iTemp26?((30 * fTemp29) + 60):90)):(iTemp23?((10 * fTemp27) + 90):100)):(iTemp21?(100 - (10 * fTemp24)):90)):(iTemp19?(90 - (10 * fTemp22)):80)):(iTemp17?(80 - (20 * fTemp20)):60)):(iTemp15?((30 * fTemp18) + 60):90)):(iTemp13?(90 - fTemp82):80)):(iTemp11?((10 * fTemp14) + 80):90)):(iTemp8?(90 - fTemp81):80)):(iTemp9?(80 - (20 * fTemp10)):60)) / fTemp78);
			var fTemp86 = (((fTemp80 + fTemp85) / fTemp79) + 1);
			this.fRec12[0] = (fTemp6 - (((this.fRec12[2] * (((fTemp80 - fTemp85) / fTemp79) + 1)) + (2 * (this.fRec12[1] * (1 - (1 / mydsp_faustpower2_f(fTemp79)))))) / fTemp86));
			var fTemp87 = (iTemp8?(iTemp11?(iTemp13?(iTemp15?(iTemp17?(iTemp19?(iTemp21?(iTemp23?(iTemp26?(iTemp28?(iTemp30?(iTemp32?(iTemp34?(iTemp36?(iTemp38?(iTemp40?(iTemp43?(iTemp45?(iTemp47?(iTemp49?(iTemp51?(iTemp53?(iTemp55?(iTemp57?0.630957:(iTemp55?(0.630957 - (0.567861 * fTemp7)):0.063096)):(iTemp53?((0.036904 * fTemp56) + 0.063096):0.1)):(iTemp51?((0.254813 * fTemp54) + 0.1):0.354813)):(iTemp49?(0.354813 - (0.103624 * fTemp52)):0.251189)):(iTemp47?((0.195495 * fTemp50) + 0.251189):0.446684)):(iTemp45?(0.446684 - (0.195495 * fTemp48)):0.251189)):(iTemp43?(0.251189 - (0.219566 * fTemp46)):0.031623)):(iTemp40?((0.250215 * fTemp44) + 0.031623):0.281838)):(iTemp38?(0.281838 - (0.181838 * fTemp41)):0.1)):(iTemp36?((0.401187 * fTemp39) + 0.1):0.501187)):(iTemp34?(0.501187 - (0.301661 * fTemp37)):0.199526)):(iTemp32?(0.199526 - (0.13643 * fTemp35)):0.063096)):(iTemp30?((0.253132 * fTemp33) + 0.063096):0.316228)):(iTemp28?(0.316228 - (0.216228 * fTemp31)):0.1)):(iTemp26?((0.401187 * fTemp29) + 0.1):0.501187)):(iTemp23?(0.501187 - (0.401187 * fTemp27)):0.1)):(iTemp21?((0.151189 * fTemp24) + 0.1):0.251189)):(iTemp19?((0.030649 * fTemp22) + 0.251189):0.281838)):(iTemp17?(0.281838 - (0.123349 * fTemp20)):0.158489)):(iTemp15?((0.342698 * fTemp18) + 0.158489):0.501187)):(iTemp13?(0.501187 - (0.301661 * fTemp16)):0.199526)):(iTemp11?(0.199526 - (0.021698 * fTemp14)):0.177828)):(iTemp8?((0.1384 * fTemp12) + 0.177828):0.316228)):(iTemp9?(0.316228 - (0.216228 * fTemp10)):0.1));
			var fTemp88 = (iSlow17?(fTemp74 * fTemp87):(fTemp73 * fTemp87));
			var fTemp89 = (100 * fTemp10);
			var fTemp90 = (50 * fTemp18);
			var fTemp91 = (50 * fTemp37);
			var fTemp92 = (iTemp8?(iTemp11?(iTemp13?(iTemp15?(iTemp17?(iTemp19?(iTemp21?(iTemp23?(iTemp26?(iTemp28?(iTemp30?(iTemp32?(iTemp34?(iTemp36?(iTemp38?(iTemp40?(iTemp43?(iTemp45?(iTemp47?(iTemp49?(iTemp51?(iTemp53?(iTemp55?(iTemp57?2800:(iTemp55?(2800 - (100 * fTemp7)):2700)):2700):(iTemp51?((130 * fTemp54) + 2700):2830)):(iTemp49?(2830 - (300 * fTemp52)):2530)):(iTemp47?(2530 - (280 * fTemp50)):2250)):(iTemp45?((150 * fTemp48) + 2250):2400)):(iTemp43?((200 * fTemp46) + 2400):2600)):(iTemp40?(2600 - (200 * fTemp44)):2400)):2400):(iTemp36?((350 * fTemp39) + 2400):2750)):(iTemp34?(2750 - fTemp91):2700)):(iTemp32?((200 * fTemp35) + 2700):2900)):(iTemp30?(2900 - (200 * fTemp33)):2700)):(iTemp28?((50 * fTemp31) + 2700):2750)):(iTemp26?((150 * fTemp29) + 2750):2900)):(iTemp23?(2900 - (100 * fTemp27)):2800)):(iTemp21?((150 * fTemp24) + 2800):2950)):(iTemp19?(2950 - (120 * fTemp22)):2830)):(iTemp17?(2830 - (130 * fTemp20)):2700)):(iTemp15?(2700 - fTemp90):2650)):(iTemp13?(2650 - (50 * fTemp16)):2600)):(iTemp11?((200 * fTemp14) + 2600):2800)):(iTemp8?(2800 - (200 * fTemp12)):2600)):(iTemp9?(fTemp89 + 2600):2700));
			var fTemp93 = Math.tan((this.fConst4 * fTemp92));
			var fTemp94 = (1 / fTemp93);
			var fTemp95 = (20 * fTemp29);
			var fTemp96 = (20 * fTemp37);
			var fTemp97 = (20 * fTemp39);
			var fTemp98 = (60 * fTemp50);
			var fTemp99 = ((iTemp8?(iTemp11?(iTemp13?(iTemp15?(iTemp17?(iTemp19?(iTemp21?(iTemp23?(iTemp26?(iTemp28?(iTemp30?(iTemp32?(iTemp34?(iTemp36?(iTemp38?(iTemp40?(iTemp43?(iTemp45?(iTemp47?(iTemp49?(iTemp51?(iTemp53?120:(iTemp51?(120 - fTemp69):100)):(iTemp49?((70 * fTemp52) + 100):170)):(iTemp47?(170 - fTemp98):110)):(iTemp45?(110 - fTemp84):100)):100):100):100):(iTemp36?(fTemp97 + 100):120)):(iTemp34?(120 - fTemp96):100)):100):100):100):(iTemp26?(fTemp95 + 100):120)):120):(iTemp21?(120 - (20 * fTemp24)):100)):100):(iTemp17?((70 * fTemp20) + 100):170)):(iTemp15?(170 - fTemp90):120)):(iTemp13?(120 - fTemp64):100)):100):100):100) / fTemp92);
			var fTemp100 = (((fTemp94 + fTemp99) / fTemp93) + 1);
			this.fRec13[0] = (fTemp6 - (((this.fRec13[2] * (((fTemp94 - fTemp99) / fTemp93) + 1)) + (2 * (this.fRec13[1] * (1 - (1 / mydsp_faustpower2_f(fTemp93)))))) / fTemp100));
			var fTemp101 = (iTemp19?((0.029314 * fTemp22) + 0.050119):0.079433);
			var fTemp102 = (iTemp8?(iTemp11?(iTemp13?(iTemp15?(iTemp17?(iTemp19?(iTemp21?(iTemp23?(iTemp26?(iTemp28?(iTemp30?(iTemp32?(iTemp34?(iTemp36?(iTemp38?(iTemp40?(iTemp43?(iTemp45?(iTemp47?(iTemp49?(iTemp51?(iTemp53?(iTemp55?(iTemp57?0.1:(iTemp55?(0.1 - (0.068377 * fTemp7)):0.031623)):0.031623):(iTemp51?((0.126866 * fTemp54) + 0.031623):0.158489)):(iTemp49?(0.158489 - (0.126866 * fTemp52)):0.031623)):(iTemp47?((0.32319 * fTemp50) + 0.031623):0.354813)):0.354813):(iTemp43?(0.354813 - (0.196324 * fTemp46)):0.158489)):(iTemp40?(0.158489 - (0.069364 * fTemp44)):0.089125)):(iTemp38?(0.089125 - (0.064006 * fTemp41)):0.025119)):(iTemp36?((0.045676 * fTemp39) + 0.025119):0.070795)):(iTemp34?((0.055098 * fTemp37) + 0.070795):0.125893)):(iTemp32?(0.125893 - (0.062797 * fTemp35)):0.063096)):(iTemp30?(0.063096 - (0.012977 * fTemp33)):0.050119)):(iTemp28?((0.020676 * fTemp31) + 0.050119):0.070795)):(iTemp26?(0.070795 - (0.045676 * fTemp29)):0.025119)):(iTemp23?((0.152709 * fTemp27) + 0.025119):0.177828)):(iTemp21?(0.177828 - (0.127709 * fTemp24)):0.050119)):fTemp101):(iTemp17?(0.079433 - (0.06165 * fTemp20)):0.017783)):(iTemp15?((0.428901 * fTemp18) + 0.017783):0.446684)):(iTemp13?(0.446684 - (0.195495 * fTemp16)):0.251189)):(iTemp11?(0.251189 - (0.125296 * fTemp14)):0.125893)):(iTemp8?((0.125296 * fTemp12) + 0.125893):0.251189)):(iTemp9?(0.251189 - (0.109935 * fTemp10)):0.141254));
			var fTemp103 = (iSlow17?(fTemp74 * fTemp102):(fTemp73 * fTemp102));
			var fTemp104 = (350 * fTemp48);
			var fTemp105 = (iTemp8?(iTemp11?(iTemp13?(iTemp15?(iTemp17?(iTemp19?(iTemp21?(iTemp23?(iTemp26?(iTemp28?(iTemp30?(iTemp32?(iTemp34?(iTemp36?(iTemp38?(iTemp40?(iTemp43?(iTemp45?(iTemp47?(iTemp49?(iTemp51?(iTemp53?(iTemp55?(iTemp57?3500:(iTemp55?(3500 - (200 * fTemp7)):3300)):(iTemp53?((400 * fTemp56) + 3300):3700)):(iTemp51?(3700 - (200 * fTemp54)):3500)):3500):(iTemp47?(3500 - (1050 * fTemp50)):2450)):(iTemp45?(fTemp104 + 2450):2800)):(iTemp43?((250 * fTemp46) + 2800):3050)):(iTemp40?(3050 - (450 * fTemp44)):2600)):(iTemp38?((75 * fTemp41) + 2600):2675)):(iTemp36?((325 * fTemp39) + 2675):3000)):3000):(iTemp32?((350 * fTemp35) + 3000):3350)):(iTemp30?(3350 - (350 * fTemp33)):3000)):3000):(iTemp26?((900 * fTemp29) + 3000):3900)):(iTemp23?(3900 - (300 * fTemp27)):3600)):(iTemp21?((300 * fTemp24) + 3600):3900)):(iTemp19?(3900 - (100 * fTemp22)):3800)):3800):(iTemp15?(3800 - (900 * fTemp18)):2900)):(iTemp13?((300 * fTemp16) + 2900):3200)):(iTemp11?((50 * fTemp14) + 3200):3250)):(iTemp8?(3250 - (450 * fTemp12)):2800)):(iTemp9?(fTemp89 + 2800):2900));
			var fTemp106 = Math.tan((this.fConst4 * fTemp105));
			var fTemp107 = (1 / fTemp106);
			var fTemp108 = ((iTemp8?(iTemp11?(iTemp13?(iTemp15?(iTemp17?(iTemp19?(iTemp21?(iTemp23?(iTemp26?(iTemp28?(iTemp30?(iTemp32?(iTemp34?(iTemp36?(iTemp38?(iTemp40?(iTemp43?(iTemp45?(iTemp47?(iTemp49?(iTemp51?(iTemp53?(iTemp55?(iTemp57?130:(iTemp55?(fTemp70 + 130):150)):150):(iTemp51?(150 - fTemp69):130)):(iTemp49?((50 * fTemp52) + 130):180)):(iTemp47?(180 - fTemp98):120)):120):120):120):120):(iTemp36?(fTemp83 + 120):130)):(iTemp34?(130 - fTemp66):120)):120):120):120):(iTemp26?((10 * fTemp29) + 120):130)):(iTemp23?(fTemp65 + 130):150)):(iTemp21?(150 - (30 * fTemp24)):120)):120):(iTemp17?((60 * fTemp20) + 120):180)):(iTemp15?(180 - fTemp90):130)):(iTemp13?(130 - fTemp82):120)):120):(iTemp8?(fTemp81 + 120):130)):(iTemp9?(130 - (10 * fTemp10)):120)) / fTemp105);
			var fTemp109 = (((fTemp107 + fTemp108) / fTemp106) + 1);
			this.fRec14[0] = (fTemp6 - (((this.fRec14[2] * (((fTemp107 - fTemp108) / fTemp106) + 1)) + (2 * (this.fRec14[1] * (1 - (1 / mydsp_faustpower2_f(fTemp106)))))) / fTemp109));
			var fTemp110 = (iTemp32?(0.1 - (0.084151 * fTemp35)):0.015849);
			var fTemp111 = (iTemp8?(iTemp11?(iTemp13?(iTemp15?(iTemp17?(iTemp19?(iTemp21?(iTemp23?(iTemp26?(iTemp28?(iTemp30?(iTemp32?(iTemp34?(iTemp36?(iTemp38?(iTemp40?(iTemp43?(iTemp45?(iTemp47?(iTemp49?(iTemp51?(iTemp53?(iTemp55?(iTemp57?0.015849:(iTemp55?((0.001934 * fTemp7) + 0.015849):0.017783)):(iTemp53?(0.017783 - (0.001934 * fTemp56)):0.015849)):(iTemp51?((0.023962 * fTemp54) + 0.015849):0.039811)):(iTemp49?(0.039811 - (0.029811 * fTemp52)):0.01)):(iTemp47?((0.344813 * fTemp50) + 0.01):0.354813)):(iTemp45?(0.354813 - (0.103624 * fTemp48)):0.251189)):(iTemp43?(0.251189 - (0.171756 * fTemp46)):0.079433)):(iTemp40?((0.020567 * fTemp44) + 0.079433):0.1)):(iTemp38?(0.1 - (0.060189 * fTemp41)):0.039811)):(iTemp36?((0.023285 * fTemp39) + 0.039811):0.063096)):(iTemp34?((0.036904 * fTemp37) + 0.063096):0.1)):fTemp110):(iTemp30?((0.063584 * fTemp33) + 0.015849):0.079433)):(iTemp28?(0.079433 - (0.04781 * fTemp31)):0.031623)):(iTemp26?((0.068377 * fTemp29) + 0.031623):0.1)):(iTemp23?(0.1 - (0.09 * fTemp27)):0.01)):(iTemp21?((0.040119 * fTemp24) + 0.01):0.050119)):fTemp101):(iTemp17?(0.079433 - (0.069433 * fTemp20)):0.01)):(iTemp15?((0.388107 * fTemp18) + 0.01):0.398107)):(iTemp13?(0.398107 - (0.198581 * fTemp16)):0.199526)):(iTemp11?(0.199526 - (0.099526 * fTemp14)):0.1)):(iTemp8?((0.151189 * fTemp12) + 0.1):0.251189)):(iTemp9?(0.251189 - (0.051663 * fTemp10)):0.199526));
			var fTemp112 = (iSlow17?(fTemp74 * fTemp111):(fTemp73 * fTemp111));
			var fTemp113 = (iTemp8?(iTemp11?(iTemp13?(iTemp15?(iTemp17?(iTemp19?(iTemp21?(iTemp23?(iTemp26?(iTemp28?(iTemp30?(iTemp32?(iTemp34?(iTemp36?(iTemp38?(iTemp40?(iTemp43?(iTemp45?(iTemp47?(iTemp49?4950:(iTemp47?(4950 - (2200 * fTemp50)):2750)):(iTemp45?(fTemp104 + 2750):3100)):(iTemp43?((240 * fTemp46) + 3100):3340)):(iTemp40?(3340 - (440 * fTemp44)):2900)):(iTemp38?(fTemp42 + 2900):2950)):(iTemp36?((400 * fTemp39) + 2950):3350)):(iTemp34?(3350 - fTemp91):3300)):(iTemp32?((290 * fTemp35) + 3300):3590)):(iTemp30?(3590 - (290 * fTemp33)):3300)):(iTemp28?((100 * fTemp31) + 3300):3400)):(iTemp26?((1550 * fTemp29) + 3400):4950)):4950):4950):4950):4950):(iTemp15?(4950 - (1700 * fTemp18)):3250)):(iTemp13?((330 * fTemp16) + 3250):3580)):(iTemp11?(3580 - (40 * fTemp14)):3540)):(iTemp8?(3540 - (540 * fTemp12)):3000)):(iTemp9?((300 * fTemp10) + 3000):3300));
			var fTemp114 = Math.tan((this.fConst4 * fTemp113));
			var fTemp115 = (1 / fTemp114);
			var fTemp116 = ((iTemp8?(iTemp11?(iTemp13?(iTemp15?(iTemp17?(iTemp19?(iTemp21?(iTemp23?(iTemp26?(iTemp28?(iTemp30?(iTemp32?(iTemp34?(iTemp36?(iTemp38?(iTemp40?(iTemp43?(iTemp45?(iTemp47?(iTemp49?(iTemp51?(iTemp53?(iTemp55?(iTemp57?140:(iTemp55?((60 * fTemp7) + 140):200)):200):(iTemp51?(200 - (65 * fTemp54)):135)):(iTemp49?((65 * fTemp52) + 135):200)):(iTemp47?(200 - (70 * fTemp50)):130)):(iTemp45?(130 - fTemp84):120)):120):120):120):(iTemp36?(fTemp97 + 120):140)):(iTemp34?(140 - fTemp96):120)):120):120):120):(iTemp26?(fTemp95 + 120):140)):(iTemp23?((60 * fTemp27) + 140):200)):(iTemp21?(200 - fTemp25):120)):120):(iTemp17?((80 * fTemp20) + 120):200)):(iTemp15?(200 - (60 * fTemp18)):140)):(iTemp13?(140 - fTemp64):120)):120):(iTemp8?((15 * fTemp12) + 120):135)):(iTemp9?(135 - (15 * fTemp10)):120)) / fTemp113);
			var fTemp117 = (((fTemp115 + fTemp116) / fTemp114) + 1);
			this.fRec15[0] = (fTemp6 - (((this.fRec15[2] * (((fTemp115 - fTemp116) / fTemp114) + 1)) + (2 * (this.fRec15[1] * (1 - (1 / mydsp_faustpower2_f(fTemp114)))))) / fTemp117));
			var fTemp118 = (iTemp8?(iTemp11?(iTemp13?(iTemp15?(iTemp17?(iTemp19?(iTemp21?(iTemp23?(iTemp26?(iTemp28?(iTemp30?(iTemp32?(iTemp34?(iTemp36?(iTemp38?(iTemp40?(iTemp43?(iTemp45?(iTemp47?(iTemp49?(iTemp51?(iTemp53?0.001:(iTemp51?((0.000778 * fTemp54) + 0.001):0.001778)):(iTemp49?(0.001778 - (0.001147 * fTemp52)):0.000631)):(iTemp47?((0.099369 * fTemp50) + 0.000631):0.1)):(iTemp45?((0.025893 * fTemp48) + 0.1):0.125893)):(iTemp43?(0.125893 - (0.086082 * fTemp46)):0.039811)):(iTemp40?(0.039811 - (0.029811 * fTemp44)):0.01)):(iTemp38?((0.005849 * fTemp41) + 0.01):0.015849)):(iTemp36?(0.015849 - (0.00326 * fTemp39)):0.012589)):(iTemp34?((0.087411 * fTemp37) + 0.012589):0.1)):fTemp110):(iTemp30?((0.004104 * fTemp33) + 0.015849):0.019953)):0.019953):(iTemp26?(0.019953 - (0.016791 * fTemp29)):0.003162)):(iTemp23?(0.003162 - (0.001577 * fTemp27)):0.001585)):(iTemp21?((0.004725 * fTemp24) + 0.001585):0.00631)):(iTemp19?(0.00631 - (0.003148 * fTemp22)):0.003162)):(iTemp17?(0.003162 - (0.002162 * fTemp20)):0.001)):(iTemp15?((0.078433 * fTemp18) + 0.001):0.079433)):(iTemp13?((0.020567 * fTemp16) + 0.079433):0.1)):(iTemp11?(0.1 - (0.068377 * fTemp14)):0.031623)):(iTemp8?((0.018496 * fTemp12) + 0.031623):0.050119)):0.050119);
			var fTemp119 = (iSlow17?(fTemp74 * fTemp118):(fTemp73 * fTemp118));
			var fTemp120 = (fSlow0 * (((((((this.fRec0[2] * (0 - (fTemp75 / fTemp62))) + ((this.fRec0[0] * fTemp75) / fTemp62)) / fTemp72) + (((this.fRec12[2] * (0 - (fTemp88 / fTemp79))) + ((this.fRec12[0] * fTemp88) / fTemp79)) / fTemp86)) + (((this.fRec13[2] * (0 - (fTemp103 / fTemp93))) + ((this.fRec13[0] * fTemp103) / fTemp93)) / fTemp100)) + (((this.fRec14[2] * (0 - (fTemp112 / fTemp106))) + ((this.fRec14[0] * fTemp112) / fTemp106)) / fTemp109)) + (((this.fRec15[2] * (0 - (fTemp119 / fTemp114))) + ((this.fRec15[0] * fTemp119) / fTemp114)) / fTemp117)));
			output0[i] = fTemp120;
			output1[i] = fTemp120;
			this.iVec0[1] = this.iVec0[0];
			this.fVec1[1] = this.fVec1[0];
			this.fRec1[1] = this.fRec1[0];
			this.fRec2[1] = this.fRec2[0];
			this.fRec5[1] = this.fRec5[0];
			this.fRec6[1] = this.fRec6[0];
			this.fRec7[1] = this.fRec7[0];
			this.fRec3[1] = this.fRec3[0];
			this.iRec8[1] = this.iRec8[0];
			this.fRec9[1] = this.fRec9[0];
			this.fRec10[1] = this.fRec10[0];
			this.fRec11[1] = this.fRec11[0];
			this.fRec0[2] = this.fRec0[1];
			this.fRec0[1] = this.fRec0[0];
			this.fRec12[2] = this.fRec12[1];
			this.fRec12[1] = this.fRec12[0];
			this.fRec13[2] = this.fRec13[1];
			this.fRec13[1] = this.fRec13[0];
			this.fRec14[2] = this.fRec14[1];
			this.fRec14[1] = this.fRec14[0];
			this.fRec15[2] = this.fRec15[1];
			this.fRec15[1] = this.fRec15[0];
			
		}
		
	}
	
}

