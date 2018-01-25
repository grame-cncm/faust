

function mydspSIG0() {
	
	this.iRec9 = new Int32Array(2);
	
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
		for (var l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			this.iRec9[l12] = 0;
			
		}
		
	}
	
	this.fillmydspSIG0 = function(count, output) {
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iRec9[0] = (this.iRec9[1] + 1);
			output[i] = Math.sin((9.58738e-05 * (this.iRec9[0] + -1)));
			this.iRec9[1] = this.iRec9[0];
			
		}
		
	}
}

newmydspSIG0 = function() { return new mydspSIG0(); }
deletemydspSIG0= function(dsp) {}

this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
var ftbl0mydspSIG0 = new Float32Array(65536);

function mydsp() {
	
	this.fHslider0;
	this.iVec0 = new Int32Array(2);
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fHslider1;
	this.fHslider2;
	this.fConst2;
	this.fHslider3;
	this.fRec2 = new Float32Array(2);
	this.fRec3 = new Float32Array(2);
	this.fVec1 = new Float32Array(2);
	this.fRec1 = new Float32Array(2);
	this.iVec2 = new Int32Array(2);
	this.fConst3;
	this.fConst4;
	this.fConst5;
	this.fHslider4;
	this.fRec5 = new Float32Array(2);
	this.fHslider5;
	this.fRec6 = new Float32Array(2);
	this.fRec7 = new Float32Array(2);
	this.fRec4 = new Float32Array(2);
	this.fRec8 = new Float32Array(2);
	this.fRec0 = new Float32Array(3);
	this.fConst6;
	this.fRec11 = new Float32Array(2);
	this.fRec10 = new Float32Array(2);
	this.fRec13 = new Float32Array(2);
	this.fRec14 = new Float32Array(2);
	this.fRec12 = new Float32Array(3);
	this.fRec15 = new Float32Array(2);
	this.fRec17 = new Float32Array(2);
	this.fRec18 = new Float32Array(2);
	this.fRec16 = new Float32Array(3);
	this.fRec19 = new Float32Array(2);
	this.fRec21 = new Float32Array(2);
	this.fRec22 = new Float32Array(2);
	this.fRec20 = new Float32Array(3);
	this.fRec23 = new Float32Array(2);
	this.fRec25 = new Float32Array(2);
	this.fRec26 = new Float32Array(2);
	this.fRec24 = new Float32Array(3);
	this.fRec27 = new Float32Array(2);
	
	this.metadata = function(m) { 
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("copyright", "(c)Mike Olsen, CCRMA (Stanford University)");
		m.declare("description", "FOF vocal synthesizer.");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("license", "MIT");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "Vocal FOF");
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
		this.fConst1 = (1 / this.fConst0);
		this.fConst2 = (6.28319 / this.fConst0);
		this.fConst3 = (3.14159 / this.fConst0);
		this.fConst4 = Math.exp((0 - (1000 / this.fConst0)));
		this.fConst5 = (1 - this.fConst4);
		this.fConst6 = (1 / this.fConst0);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 0.9;
		this.fHslider1 = 440;
		this.fHslider2 = 0.5;
		this.fHslider3 = 6;
		this.fHslider4 = 0;
		this.fHslider5 = 0;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.iVec0[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec2[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec3[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fVec1[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec1[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.iVec2[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			this.fRec5[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			this.fRec6[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			this.fRec7[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			this.fRec4[l9] = 0;
			
		}
		for (var l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			this.fRec8[l10] = 0;
			
		}
		for (var l11 = 0; (l11 < 3); l11 = (l11 + 1)) {
			this.fRec0[l11] = 0;
			
		}
		for (var l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			this.fRec11[l13] = 0;
			
		}
		for (var l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			this.fRec10[l14] = 0;
			
		}
		for (var l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			this.fRec13[l15] = 0;
			
		}
		for (var l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			this.fRec14[l16] = 0;
			
		}
		for (var l17 = 0; (l17 < 3); l17 = (l17 + 1)) {
			this.fRec12[l17] = 0;
			
		}
		for (var l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			this.fRec15[l18] = 0;
			
		}
		for (var l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			this.fRec17[l19] = 0;
			
		}
		for (var l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			this.fRec18[l20] = 0;
			
		}
		for (var l21 = 0; (l21 < 3); l21 = (l21 + 1)) {
			this.fRec16[l21] = 0;
			
		}
		for (var l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			this.fRec19[l22] = 0;
			
		}
		for (var l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			this.fRec21[l23] = 0;
			
		}
		for (var l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			this.fRec22[l24] = 0;
			
		}
		for (var l25 = 0; (l25 < 3); l25 = (l25 + 1)) {
			this.fRec20[l25] = 0;
			
		}
		for (var l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			this.fRec23[l26] = 0;
			
		}
		for (var l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			this.fRec25[l27] = 0;
			
		}
		for (var l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			this.fRec26[l28] = 0;
			
		}
		for (var l29 = 0; (l29 < 3); l29 = (l29 + 1)) {
			this.fRec24[l29] = 0;
			
		}
		for (var l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			this.fRec27[l30] = 0;
			
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
		ui_interface.declare("fHslider1", "0", "");
		ui_interface.addHorizontalSlider("freq", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 440, 50, 1000, 0.01);
		ui_interface.declare("fHslider0", "1", "");
		ui_interface.addHorizontalSlider("gain", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0.9, 0, 1, 0.01);
		ui_interface.declare("fHslider5", "2", "");
		ui_interface.addHorizontalSlider("voiceType", function handler(obj) { function setval(val) { obj.fHslider5 = val; } return setval; }(this), 0, 0, 4, 1);
		ui_interface.declare("fHslider4", "3", "");
		ui_interface.addHorizontalSlider("vowel", function handler(obj) { function setval(val) { obj.fHslider4 = val; } return setval; }(this), 0, 0, 4, 0.01);
		ui_interface.declare("fHslider3", "5", "");
		ui_interface.addHorizontalSlider("vibratoFreq", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 6, 1, 10, 0.01);
		ui_interface.declare("fHslider2", "6", "");
		ui_interface.addHorizontalSlider("vibratoGain", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = (25 * this.fHslider0);
		var fSlow1 = this.fHslider1;
		var fSlow2 = (0.1 * this.fHslider2);
		var fSlow3 = (this.fConst2 * this.fHslider3);
		var fSlow4 = Math.sin(fSlow3);
		var fSlow5 = Math.cos(fSlow3);
		var fSlow6 = (0 - fSlow4);
		var fSlow7 = (0.001 * this.fHslider4);
		var fSlow8 = this.fHslider5;
		var iSlow9 = ((fSlow8 == 0)?1:((fSlow8 == 3)?1:0));
		var iSlow10 = (5 * iSlow9);
		var iSlow11 = (iSlow9 >= 1);
		var fSlow12 = (iSlow11?174.61:82.41);
		var fSlow13 = (iSlow11?1046.5:523.25);
		var fSlow14 = (fSlow13 - fSlow12);
		var fSlow15 = (5 * fSlow8);
		var fSlow16 = (5 * (1 - fSlow8));
		var iSlow17 = (iSlow9 == 0);
		var iSlow18 = (fSlow8 != 2);
		var fSlow19 = (2 * fSlow1);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iVec0[0] = 1;
			this.fRec2[0] = ((fSlow4 * this.fRec3[1]) + (fSlow5 * this.fRec2[1]));
			var iTemp0 = (1 - this.iVec0[1]);
			this.fRec3[0] = (((fSlow5 * this.fRec3[1]) + (fSlow6 * this.fRec2[1])) + iTemp0);
			var fTemp1 = ((fSlow2 * this.fRec2[0]) + 1);
			var fTemp2 = (fSlow1 * fTemp1);
			this.fVec1[0] = fTemp2;
			var fTemp3 = (this.fRec1[1] + (this.fConst1 * this.fVec1[1]));
			this.fRec1[0] = (fTemp3 - Math.floor(fTemp3));
			var iTemp4 = ((this.fRec1[0] - this.fRec1[1]) < 0);
			this.iVec2[0] = iTemp4;
			this.fRec5[0] = (fSlow7 + (0.999 * this.fRec5[1]));
			var fTemp5 = (this.fRec5[0] + iSlow10);
			var iTemp6 = (fTemp5 >= 5);
			var iTemp7 = (fTemp5 >= 3);
			var iTemp8 = (fTemp5 >= 2);
			var iTemp9 = (fTemp5 >= 1);
			var iTemp10 = (fTemp5 >= 4);
			var iTemp11 = (fTemp5 >= 8);
			var iTemp12 = (fTemp5 >= 7);
			var iTemp13 = (fTemp5 >= 6);
			var fTemp14 = (iTemp6?(iTemp11?2:(iTemp12?3:(iTemp13?3:2))):(iTemp7?(iTemp10?1.5:1):(iTemp8?1.25:(iTemp9?1.25:1))));
			this.fRec6[0] = ((fSlow4 * this.fRec7[1]) + (fSlow5 * this.fRec6[1]));
			this.fRec7[0] = (((fSlow5 * this.fRec7[1]) + (fSlow6 * this.fRec6[1])) + iTemp0);
			var fTemp15 = (fSlow1 * ((fSlow2 * this.fRec6[0]) + 1));
			var fTemp16 = (fTemp14 + (((iTemp6?(iTemp11?12:(iTemp12?12:(iTemp13?12:15))):(iTemp7?(iTemp10?4:10):(iTemp8?2.5:(iTemp9?2.5:10)))) - fTemp14) * ((fTemp15 <= fSlow12)?0:((fTemp15 >= fSlow13)?1:((fTemp15 - fSlow12) / fSlow14)))));
			var fTemp17 = (fSlow15 + this.fRec5[0]);
			var iTemp18 = (fTemp17 < 23);
			var iTemp19 = (fTemp17 < 24);
			var fTemp20 = (fSlow15 + (this.fRec5[0] + -23));
			var iTemp21 = (fTemp17 < 22);
			var fTemp22 = (fSlow15 + (this.fRec5[0] + -22));
			var iTemp23 = (fTemp17 < 21);
			var fTemp24 = (fSlow15 + (this.fRec5[0] + -21));
			var iTemp25 = (fTemp17 < 20);
			var fTemp26 = (fSlow15 + (this.fRec5[0] + -20));
			var fTemp27 = (20 * fTemp26);
			var iTemp28 = (fTemp17 < 19);
			var iTemp29 = (fTemp17 < 18);
			var fTemp30 = (fSlow15 + (this.fRec5[0] + -18));
			var iTemp31 = (fTemp17 < 17);
			var fTemp32 = (fSlow15 + (this.fRec5[0] + -17));
			var iTemp33 = (fTemp17 < 16);
			var iTemp34 = (fTemp17 < 15);
			var fTemp35 = (fSlow15 + (this.fRec5[0] + -15));
			var fTemp36 = (20 * fTemp35);
			var iTemp37 = (fTemp17 < 14);
			var fTemp38 = (fSlow15 + (this.fRec5[0] + -14));
			var iTemp39 = (fTemp17 < 13);
			var iTemp40 = (fTemp17 < 12);
			var iTemp41 = (fTemp17 < 11);
			var fTemp42 = (fSlow15 + (this.fRec5[0] + -11));
			var iTemp43 = (fTemp17 < 10);
			var fTemp44 = (fSlow15 + (this.fRec5[0] + -10));
			var fTemp45 = (10 * fTemp44);
			var iTemp46 = (fTemp17 < 9);
			var fTemp47 = (fSlow15 + (this.fRec5[0] + -9));
			var iTemp48 = (fTemp17 < 8);
			var iTemp49 = (fTemp17 < 7);
			var fTemp50 = (fSlow15 + (this.fRec5[0] + -7));
			var iTemp51 = (fTemp17 < 6);
			var fTemp52 = (fSlow15 + (this.fRec5[0] + -6));
			var iTemp53 = (fTemp17 < 5);
			var fTemp54 = (this.fRec5[0] - fSlow16);
			var iTemp55 = (fTemp17 < 4);
			var fTemp56 = (fSlow15 + (this.fRec5[0] + -4));
			var fTemp57 = (10 * fTemp56);
			var iTemp58 = (fTemp17 < 3);
			var fTemp59 = (fSlow15 + (this.fRec5[0] + -3));
			var fTemp60 = (20 * fTemp59);
			var iTemp61 = (fTemp17 < 2);
			var fTemp62 = (fSlow15 + (this.fRec5[0] + -2));
			var fTemp63 = (20 * fTemp62);
			var iTemp64 = (fTemp17 < 1);
			var fTemp65 = (fSlow15 + (this.fRec5[0] + -1));
			var iTemp66 = (fTemp17 < 0);
			var fTemp67 = (20 * fTemp17);
			var fTemp68 = (iTemp18?(iTemp21?(iTemp23?(iTemp25?(iTemp28?(iTemp29?(iTemp31?(iTemp33?(iTemp34?(iTemp37?(iTemp39?(iTemp40?(iTemp41?(iTemp43?(iTemp46?(iTemp48?(iTemp49?(iTemp51?(iTemp53?(iTemp55?(iTemp58?(iTemp61?(iTemp64?(iTemp66?80:(iTemp64?(80 - fTemp67):60)):(iTemp61?(60 - (10 * fTemp65)):50)):(iTemp58?(fTemp63 + 50):70)):(iTemp55?(70 - fTemp60):50)):(iTemp53?(fTemp57 + 50):60)):(iTemp51?(60 - (20 * fTemp54)):40)):(iTemp49?((20 * fTemp52) + 40):60)):(iTemp48?(60 - (20 * fTemp50)):40)):40):(iTemp43?(40 * (fTemp47 + 1)):80)):(iTemp41?(80 - fTemp45):70)):(iTemp40?(70 - (30 * fTemp42)):40)):40):40):(iTemp34?(40 * (fTemp38 + 1)):80)):(iTemp33?(80 - fTemp36):60)):60):(iTemp29?(60 - (20 * fTemp32)):40)):(iTemp28?((10 * fTemp30) + 40):50)):50):(iTemp23?(fTemp27 + 50):70)):(iTemp21?(70 - (30 * fTemp24)):40)):(iTemp18?((30 * fTemp22) + 40):70)):(iTemp19?(70 - (30 * fTemp20)):40));
			this.fRec4[0] = ((this.fConst4 * this.fRec4[1]) + (this.fConst5 * (fTemp16 * fTemp68)));
			var fTemp69 = Math.exp((this.fConst3 * (0 - this.fRec4[0])));
			this.fRec8[0] = ((this.fConst4 * this.fRec8[1]) + (this.fConst5 * fTemp68));
			var fTemp70 = Math.exp((this.fConst3 * (0 - this.fRec8[0])));
			this.fRec0[0] = (this.iVec2[1] - ((this.fRec0[1] * (0 - (fTemp69 + fTemp70))) + ((fTemp69 * fTemp70) * this.fRec0[2])));
			var fTemp71 = ((0.00084 * (1000 - fTemp15)) + 0.8);
			var fTemp72 = ((0.00366667 * (400 - fTemp15)) + 3);
			var iTemp73 = (1 - (iTemp4 > 0));
			this.fRec11[0] = (fSlow7 + (0.999 * this.fRec11[1]));
			var fTemp74 = (fSlow15 + this.fRec11[0]);
			var iTemp75 = (fTemp74 < 23);
			var iTemp76 = (fTemp74 < 24);
			var fTemp77 = (fSlow15 + (this.fRec11[0] + -23));
			var iTemp78 = (fTemp74 < 22);
			var fTemp79 = (fSlow15 + (this.fRec11[0] + -22));
			var iTemp80 = (fTemp74 < 21);
			var fTemp81 = (fSlow15 + (this.fRec11[0] + -21));
			var iTemp82 = (fTemp74 < 20);
			var fTemp83 = (fSlow15 + (this.fRec11[0] + -20));
			var iTemp84 = (fTemp74 < 19);
			var fTemp85 = (fSlow15 + (this.fRec11[0] + -19));
			var iTemp86 = (fTemp74 < 18);
			var fTemp87 = (fSlow15 + (this.fRec11[0] + -18));
			var iTemp88 = (fTemp74 < 17);
			var fTemp89 = (fSlow15 + (this.fRec11[0] + -17));
			var iTemp90 = (fTemp74 < 16);
			var fTemp91 = (fSlow15 + (this.fRec11[0] + -16));
			var iTemp92 = (fTemp74 < 15);
			var fTemp93 = (fSlow15 + (this.fRec11[0] + -15));
			var iTemp94 = (fTemp74 < 14);
			var fTemp95 = (fSlow15 + (this.fRec11[0] + -14));
			var iTemp96 = (fTemp74 < 13);
			var fTemp97 = (fSlow15 + (this.fRec11[0] + -13));
			var iTemp98 = (fTemp74 < 12);
			var fTemp99 = (fSlow15 + (this.fRec11[0] + -12));
			var iTemp100 = (fTemp74 < 11);
			var fTemp101 = (fSlow15 + (this.fRec11[0] + -11));
			var iTemp102 = (fTemp74 < 10);
			var fTemp103 = (fSlow15 + (this.fRec11[0] + -10));
			var iTemp104 = (fTemp74 < 9);
			var fTemp105 = (fSlow15 + (this.fRec11[0] + -9));
			var iTemp106 = (fTemp74 < 8);
			var fTemp107 = (fSlow15 + (this.fRec11[0] + -8));
			var fTemp108 = (50 * fTemp107);
			var iTemp109 = (fTemp74 < 7);
			var fTemp110 = (fSlow15 + (this.fRec11[0] + -7));
			var iTemp111 = (fTemp74 < 6);
			var fTemp112 = (fSlow15 + (this.fRec11[0] + -6));
			var iTemp113 = (fTemp74 < 5);
			var fTemp114 = (this.fRec11[0] - fSlow16);
			var iTemp115 = (fTemp74 < 4);
			var fTemp116 = (fSlow15 + (this.fRec11[0] + -4));
			var iTemp117 = (fTemp74 < 3);
			var fTemp118 = (fSlow15 + (this.fRec11[0] + -3));
			var iTemp119 = (fTemp74 < 2);
			var fTemp120 = (fSlow15 + (this.fRec11[0] + -2));
			var iTemp121 = (fTemp74 < 1);
			var fTemp122 = (fSlow15 + (this.fRec11[0] + -1));
			var iTemp123 = (fTemp74 < 0);
			var fTemp124 = (iTemp75?(iTemp78?(iTemp80?(iTemp82?(iTemp84?(iTemp86?(iTemp88?(iTemp90?(iTemp92?(iTemp94?(iTemp96?(iTemp98?(iTemp100?(iTemp102?(iTemp104?(iTemp106?(iTemp109?(iTemp111?(iTemp113?(iTemp115?(iTemp117?(iTemp119?(iTemp121?(iTemp123?800:(iTemp121?(800 - (400 * fTemp74)):400)):(iTemp119?(400 - (50 * fTemp122)):350)):(iTemp117?((100 * fTemp120) + 350):450)):(iTemp115?(450 - (125 * fTemp118)):325)):(iTemp113?((275 * fTemp116) + 325):600)):(iTemp111?(600 - (200 * fTemp114)):400)):(iTemp109?(400 - (150 * fTemp112)):250)):(iTemp106?((150 * fTemp110) + 250):400)):(iTemp104?(400 - fTemp108):350)):(iTemp102?((310 * fTemp105) + 350):660)):(iTemp100?(660 - (220 * fTemp103)):440)):(iTemp98?(440 - (170 * fTemp101)):270)):(iTemp96?((160 * fTemp99) + 270):430)):(iTemp94?(430 - (60 * fTemp97)):370)):(iTemp92?((430 * fTemp95) + 370):800)):(iTemp90?(800 - (450 * fTemp93)):350)):(iTemp88?(350 - (80 * fTemp91)):270)):(iTemp86?((180 * fTemp89) + 270):450)):(iTemp84?(450 - (125 * fTemp87)):325)):(iTemp82?(325 * (fTemp85 + 1)):650)):(iTemp80?(650 - (250 * fTemp83)):400)):(iTemp78?(400 - (110 * fTemp81)):290)):(iTemp75?((110 * fTemp79) + 290):400)):(iTemp76?(400 - (50 * fTemp77)):350));
			var fTemp125 = ((this.fRec10[1] * iTemp73) + (this.fConst6 * ((fTemp124 <= fTemp2)?fTemp2:fTemp124)));
			this.fRec10[0] = (fTemp125 - Math.floor(fTemp125));
			var fTemp126 = (10 * fTemp22);
			var fTemp127 = (10 * fTemp26);
			var fTemp128 = (fSlow15 + (this.fRec5[0] + -19));
			var fTemp129 = (fSlow15 + (this.fRec5[0] + -16));
			var fTemp130 = (fSlow15 + (this.fRec5[0] + -13));
			var fTemp131 = (fSlow15 + (this.fRec5[0] + -12));
			var fTemp132 = (10 * fTemp47);
			var fTemp133 = (10 * fTemp54);
			var fTemp134 = (iTemp18?(iTemp21?(iTemp23?(iTemp25?(iTemp28?(iTemp29?(iTemp31?(iTemp33?(iTemp34?(iTemp37?(iTemp39?(iTemp40?(iTemp41?(iTemp43?(iTemp46?(iTemp48?(iTemp49?(iTemp51?(iTemp53?(iTemp55?(iTemp58?(iTemp61?(iTemp64?(iTemp66?90:(iTemp64?(90 - (10 * fTemp17)):80)):(iTemp61?((20 * fTemp65) + 80):100)):(iTemp58?(100 - fTemp63):80)):(iTemp55?(80 - fTemp60):60)):(iTemp53?(fTemp57 + 60):70)):(iTemp51?(fTemp133 + 70):80)):(iTemp49?((10 * fTemp52) + 80):90)):(iTemp48?(90 - (10 * fTemp50)):80)):80):(iTemp43?(fTemp132 + 80):90)):(iTemp41?(90 - fTemp45):80)):(iTemp40?((10 * fTemp42) + 80):90)):(iTemp39?(90 - (10 * fTemp131)):80)):(iTemp37?(80 - (20 * fTemp130)):60)):(iTemp34?((30 * fTemp38) + 60):90)):(iTemp33?((10 * fTemp35) + 90):100)):(iTemp31?(100 - (10 * fTemp129)):90)):(iTemp29?(90 - (10 * fTemp32)):80)):(iTemp28?(80 - (20 * fTemp30)):60)):(iTemp25?((30 * fTemp128) + 60):90)):(iTemp23?(90 - fTemp127):80)):(iTemp21?((10 * fTemp24) + 80):90)):(iTemp18?(90 - fTemp126):80)):(iTemp19?(80 - (20 * fTemp20)):60));
			this.fRec13[0] = ((this.fConst4 * this.fRec13[1]) + (this.fConst5 * (fTemp16 * fTemp134)));
			var fTemp135 = Math.exp((this.fConst3 * (0 - this.fRec13[0])));
			this.fRec14[0] = ((this.fConst4 * this.fRec14[1]) + (this.fConst5 * fTemp134));
			var fTemp136 = Math.exp((this.fConst3 * (0 - this.fRec14[0])));
			this.fRec12[0] = (this.iVec2[1] - ((this.fRec12[1] * (0 - (fTemp135 + fTemp136))) + ((fTemp135 * fTemp136) * this.fRec12[2])));
			var fTemp137 = (fSlow15 + (this.fRec5[0] + -8));
			var fTemp138 = (iTemp18?(iTemp21?(iTemp23?(iTemp25?(iTemp28?(iTemp29?(iTemp31?(iTemp33?(iTemp34?(iTemp37?(iTemp39?(iTemp40?(iTemp41?(iTemp43?(iTemp46?(iTemp48?(iTemp49?(iTemp51?(iTemp53?(iTemp55?(iTemp58?(iTemp61?(iTemp64?(iTemp66?0.630957:(iTemp64?(0.630957 - (0.567861 * fTemp17)):0.063096)):(iTemp61?((0.036904 * fTemp65) + 0.063096):0.1)):(iTemp58?((0.254813 * fTemp62) + 0.1):0.354813)):(iTemp55?(0.354813 - (0.103624 * fTemp59)):0.251189)):(iTemp53?((0.195495 * fTemp56) + 0.251189):0.446684)):(iTemp51?(0.446684 - (0.195495 * fTemp54)):0.251189)):(iTemp49?(0.251189 - (0.219566 * fTemp52)):0.031623)):(iTemp48?((0.250215 * fTemp50) + 0.031623):0.281838)):(iTemp46?(0.281838 - (0.181838 * fTemp137)):0.1)):(iTemp43?((0.401187 * fTemp47) + 0.1):0.501187)):(iTemp41?(0.501187 - (0.301661 * fTemp44)):0.199526)):(iTemp40?(0.199526 - (0.13643 * fTemp42)):0.063096)):(iTemp39?((0.253132 * fTemp131) + 0.063096):0.316228)):(iTemp37?(0.316228 - (0.216228 * fTemp130)):0.1)):(iTemp34?((0.401187 * fTemp38) + 0.1):0.501187)):(iTemp33?(0.501187 - (0.401187 * fTemp35)):0.1)):(iTemp31?((0.151189 * fTemp129) + 0.1):0.251189)):(iTemp29?((0.030649 * fTemp32) + 0.251189):0.281838)):(iTemp28?(0.281838 - (0.123349 * fTemp30)):0.158489)):(iTemp25?((0.342698 * fTemp128) + 0.158489):0.501187)):(iTemp23?(0.501187 - (0.301661 * fTemp26)):0.199526)):(iTemp21?(0.199526 - (0.021698 * fTemp24)):0.177828)):(iTemp18?((0.1384 * fTemp22) + 0.177828):0.316228)):(iTemp19?(0.316228 - (0.216228 * fTemp20)):0.1));
			var fTemp139 = (iTemp75?(iTemp78?(iTemp80?(iTemp82?(iTemp84?(iTemp86?(iTemp88?(iTemp90?(iTemp92?(iTemp94?(iTemp96?(iTemp98?(iTemp100?(iTemp102?(iTemp104?(iTemp106?(iTemp109?(iTemp111?(iTemp113?(iTemp115?(iTemp117?(iTemp119?(iTemp121?(iTemp123?1150:(iTemp121?((450 * fTemp74) + 1150):1600)):(iTemp119?((100 * fTemp122) + 1600):1700)):(iTemp117?(1700 - (900 * fTemp120)):800)):(iTemp115?(800 - (100 * fTemp118)):700)):(iTemp113?((340 * fTemp116) + 700):1040)):(iTemp111?((580 * fTemp114) + 1040):1620)):(iTemp109?((130 * fTemp112) + 1620):1750)):(iTemp106?(1750 - (1000 * fTemp110)):750)):(iTemp104?(750 - (150 * fTemp107)):600)):(iTemp102?((520 * fTemp105) + 600):1120)):(iTemp100?((680 * fTemp103) + 1120):1800)):(iTemp98?((50 * fTemp101) + 1800):1850)):(iTemp96?(1850 - (1030 * fTemp99)):820)):(iTemp94?(820 - (190 * fTemp97)):630)):(iTemp92?((520 * fTemp95) + 630):1150)):(iTemp90?((850 * fTemp93) + 1150):2000)):(iTemp88?((140 * fTemp91) + 2000):2140)):(iTemp86?(2140 - (1340 * fTemp89)):800)):(iTemp84?(800 - (100 * fTemp87)):700)):(iTemp82?((380 * fTemp85) + 700):1080)):(iTemp80?((620 * fTemp83) + 1080):1700)):(iTemp78?((170 * fTemp81) + 1700):1870)):(iTemp75?(1870 - (1070 * fTemp79)):800)):(iTemp76?(800 - (200 * fTemp77)):600));
			var fTemp140 = ((fSlow19 * fTemp1) + 30);
			var fTemp141 = ((iTemp73 * this.fRec15[1]) + (this.fConst6 * (iSlow18?(((fTemp139 >= 1300) & (fTemp2 >= 200))?(fTemp139 - (0.000952381 * ((fTemp2 + -200) * (fTemp139 + -1300)))):((fTemp139 <= fTemp140)?fTemp140:fTemp139)):fTemp139)));
			this.fRec15[0] = (fTemp141 - Math.floor(fTemp141));
			var fTemp142 = (50 * fTemp128);
			var fTemp143 = (20 * fTemp38);
			var fTemp144 = (20 * fTemp44);
			var fTemp145 = (20 * fTemp47);
			var fTemp146 = (60 * fTemp56);
			var fTemp147 = (iTemp18?(iTemp21?(iTemp23?(iTemp25?(iTemp28?(iTemp29?(iTemp31?(iTemp33?(iTemp34?(iTemp37?(iTemp39?(iTemp40?(iTemp41?(iTemp43?(iTemp46?(iTemp48?(iTemp49?(iTemp51?(iTemp53?(iTemp55?(iTemp58?(iTemp61?120:(iTemp58?(120 - fTemp63):100)):(iTemp55?((70 * fTemp59) + 100):170)):(iTemp53?(170 - fTemp146):110)):(iTemp51?(110 - fTemp133):100)):100):100):100):(iTemp43?(fTemp145 + 100):120)):(iTemp41?(120 - fTemp144):100)):100):100):100):(iTemp34?(fTemp143 + 100):120)):120):(iTemp31?(120 - (20 * fTemp129)):100)):100):(iTemp28?((70 * fTemp30) + 100):170)):(iTemp25?(170 - fTemp142):120)):(iTemp23?(120 - fTemp27):100)):100):100):100);
			this.fRec17[0] = ((this.fConst4 * this.fRec17[1]) + (this.fConst5 * (fTemp16 * fTemp147)));
			var fTemp148 = Math.exp((this.fConst3 * (0 - this.fRec17[0])));
			this.fRec18[0] = ((this.fConst4 * this.fRec18[1]) + (this.fConst5 * fTemp147));
			var fTemp149 = Math.exp((this.fConst3 * (0 - this.fRec18[0])));
			this.fRec16[0] = (this.iVec2[1] - ((this.fRec16[1] * (0 - (fTemp148 + fTemp149))) + ((fTemp148 * fTemp149) * this.fRec16[2])));
			var fTemp150 = (iTemp29?((0.029314 * fTemp32) + 0.050119):0.079433);
			var fTemp151 = (iTemp18?(iTemp21?(iTemp23?(iTemp25?(iTemp28?(iTemp29?(iTemp31?(iTemp33?(iTemp34?(iTemp37?(iTemp39?(iTemp40?(iTemp41?(iTemp43?(iTemp46?(iTemp48?(iTemp49?(iTemp51?(iTemp53?(iTemp55?(iTemp58?(iTemp61?(iTemp64?(iTemp66?0.1:(iTemp64?(0.1 - (0.068377 * fTemp17)):0.031623)):0.031623):(iTemp58?((0.126866 * fTemp62) + 0.031623):0.158489)):(iTemp55?(0.158489 - (0.126866 * fTemp59)):0.031623)):(iTemp53?((0.32319 * fTemp56) + 0.031623):0.354813)):0.354813):(iTemp49?(0.354813 - (0.196324 * fTemp52)):0.158489)):(iTemp48?(0.158489 - (0.069364 * fTemp50)):0.089125)):(iTemp46?(0.089125 - (0.064006 * fTemp137)):0.025119)):(iTemp43?((0.045676 * fTemp47) + 0.025119):0.070795)):(iTemp41?((0.055098 * fTemp44) + 0.070795):0.125893)):(iTemp40?(0.125893 - (0.062797 * fTemp42)):0.063096)):(iTemp39?(0.063096 - (0.012977 * fTemp131)):0.050119)):(iTemp37?((0.020676 * fTemp130) + 0.050119):0.070795)):(iTemp34?(0.070795 - (0.045676 * fTemp38)):0.025119)):(iTemp33?((0.152709 * fTemp35) + 0.025119):0.177828)):(iTemp31?(0.177828 - (0.127709 * fTemp129)):0.050119)):fTemp150):(iTemp28?(0.079433 - (0.06165 * fTemp30)):0.017783)):(iTemp25?((0.428901 * fTemp128) + 0.017783):0.446684)):(iTemp23?(0.446684 - (0.195495 * fTemp26)):0.251189)):(iTemp21?(0.251189 - (0.125296 * fTemp24)):0.125893)):(iTemp18?((0.125296 * fTemp22) + 0.125893):0.251189)):(iTemp19?(0.251189 - (0.109935 * fTemp20)):0.141254));
			var fTemp152 = (100 * fTemp77);
			var fTemp153 = (50 * fTemp103);
			var fTemp154 = ((iTemp73 * this.fRec19[1]) + (this.fConst6 * (iTemp75?(iTemp78?(iTemp80?(iTemp82?(iTemp84?(iTemp86?(iTemp88?(iTemp90?(iTemp92?(iTemp94?(iTemp96?(iTemp98?(iTemp100?(iTemp102?(iTemp104?(iTemp106?(iTemp109?(iTemp111?(iTemp113?(iTemp115?(iTemp117?(iTemp119?(iTemp121?(iTemp123?2800:(iTemp121?(2800 - (100 * fTemp74)):2700)):2700):(iTemp117?((130 * fTemp120) + 2700):2830)):(iTemp115?(2830 - (300 * fTemp118)):2530)):(iTemp113?(2530 - (280 * fTemp116)):2250)):(iTemp111?((150 * fTemp114) + 2250):2400)):(iTemp109?((200 * fTemp112) + 2400):2600)):(iTemp106?(2600 - (200 * fTemp110)):2400)):2400):(iTemp102?((350 * fTemp105) + 2400):2750)):(iTemp100?(2750 - fTemp153):2700)):(iTemp98?((200 * fTemp101) + 2700):2900)):(iTemp96?(2900 - (200 * fTemp99)):2700)):(iTemp94?((50 * fTemp97) + 2700):2750)):(iTemp92?((150 * fTemp95) + 2750):2900)):(iTemp90?(2900 - (100 * fTemp93)):2800)):(iTemp88?((150 * fTemp91) + 2800):2950)):(iTemp86?(2950 - (120 * fTemp89)):2830)):(iTemp84?(2830 - (130 * fTemp87)):2700)):(iTemp82?(2700 - (50 * fTemp85)):2650)):(iTemp80?(2650 - (50 * fTemp83)):2600)):(iTemp78?((200 * fTemp81) + 2600):2800)):(iTemp75?(2800 - (200 * fTemp79)):2600)):(iTemp76?(fTemp152 + 2600):2700))));
			this.fRec19[0] = (fTemp154 - Math.floor(fTemp154));
			var fTemp155 = (iTemp18?(iTemp21?(iTemp23?(iTemp25?(iTemp28?(iTemp29?(iTemp31?(iTemp33?(iTemp34?(iTemp37?(iTemp39?(iTemp40?(iTemp41?(iTemp43?(iTemp46?(iTemp48?(iTemp49?(iTemp51?(iTemp53?(iTemp55?(iTemp58?(iTemp61?(iTemp64?(iTemp66?130:(iTemp64?(fTemp67 + 130):150)):150):(iTemp58?(150 - fTemp63):130)):(iTemp55?((50 * fTemp59) + 130):180)):(iTemp53?(180 - fTemp146):120)):120):120):120):120):(iTemp43?(fTemp132 + 120):130)):(iTemp41?(130 - fTemp45):120)):120):120):120):(iTemp34?((10 * fTemp38) + 120):130)):(iTemp33?(fTemp36 + 130):150)):(iTemp31?(150 - (30 * fTemp129)):120)):120):(iTemp28?((60 * fTemp30) + 120):180)):(iTemp25?(180 - fTemp142):130)):(iTemp23?(130 - fTemp127):120)):120):(iTemp18?(fTemp126 + 120):130)):(iTemp19?(130 - (10 * fTemp20)):120));
			this.fRec21[0] = ((this.fConst4 * this.fRec21[1]) + (this.fConst5 * (fTemp16 * fTemp155)));
			var fTemp156 = Math.exp((this.fConst3 * (0 - this.fRec21[0])));
			this.fRec22[0] = ((this.fConst4 * this.fRec22[1]) + (this.fConst5 * fTemp155));
			var fTemp157 = Math.exp((this.fConst3 * (0 - this.fRec22[0])));
			this.fRec20[0] = (this.iVec2[1] - ((this.fRec20[1] * (0 - (fTemp156 + fTemp157))) + ((fTemp156 * fTemp157) * this.fRec20[2])));
			var fTemp158 = (iTemp40?(0.1 - (0.084151 * fTemp42)):0.015849);
			var fTemp159 = (iTemp18?(iTemp21?(iTemp23?(iTemp25?(iTemp28?(iTemp29?(iTemp31?(iTemp33?(iTemp34?(iTemp37?(iTemp39?(iTemp40?(iTemp41?(iTemp43?(iTemp46?(iTemp48?(iTemp49?(iTemp51?(iTemp53?(iTemp55?(iTemp58?(iTemp61?(iTemp64?(iTemp66?0.015849:(iTemp64?((0.001934 * fTemp17) + 0.015849):0.017783)):(iTemp61?(0.017783 - (0.001934 * fTemp65)):0.015849)):(iTemp58?((0.023962 * fTemp62) + 0.015849):0.039811)):(iTemp55?(0.039811 - (0.029811 * fTemp59)):0.01)):(iTemp53?((0.344813 * fTemp56) + 0.01):0.354813)):(iTemp51?(0.354813 - (0.103624 * fTemp54)):0.251189)):(iTemp49?(0.251189 - (0.171756 * fTemp52)):0.079433)):(iTemp48?((0.020567 * fTemp50) + 0.079433):0.1)):(iTemp46?(0.1 - (0.060189 * fTemp137)):0.039811)):(iTemp43?((0.023285 * fTemp47) + 0.039811):0.063096)):(iTemp41?((0.036904 * fTemp44) + 0.063096):0.1)):fTemp158):(iTemp39?((0.063584 * fTemp131) + 0.015849):0.079433)):(iTemp37?(0.079433 - (0.04781 * fTemp130)):0.031623)):(iTemp34?((0.068377 * fTemp38) + 0.031623):0.1)):(iTemp33?(0.1 - (0.09 * fTemp35)):0.01)):(iTemp31?((0.040119 * fTemp129) + 0.01):0.050119)):fTemp150):(iTemp28?(0.079433 - (0.069433 * fTemp30)):0.01)):(iTemp25?((0.388107 * fTemp128) + 0.01):0.398107)):(iTemp23?(0.398107 - (0.198581 * fTemp26)):0.199526)):(iTemp21?(0.199526 - (0.099526 * fTemp24)):0.1)):(iTemp18?((0.151189 * fTemp22) + 0.1):0.251189)):(iTemp19?(0.251189 - (0.051663 * fTemp20)):0.199526));
			var fTemp160 = (350 * fTemp114);
			var fTemp161 = ((iTemp73 * this.fRec23[1]) + (this.fConst6 * (iTemp75?(iTemp78?(iTemp80?(iTemp82?(iTemp84?(iTemp86?(iTemp88?(iTemp90?(iTemp92?(iTemp94?(iTemp96?(iTemp98?(iTemp100?(iTemp102?(iTemp104?(iTemp106?(iTemp109?(iTemp111?(iTemp113?(iTemp115?(iTemp117?(iTemp119?(iTemp121?(iTemp123?3500:(iTemp121?(3500 - (200 * fTemp74)):3300)):(iTemp119?((400 * fTemp122) + 3300):3700)):(iTemp117?(3700 - (200 * fTemp120)):3500)):3500):(iTemp113?(3500 - (1050 * fTemp116)):2450)):(iTemp111?(fTemp160 + 2450):2800)):(iTemp109?((250 * fTemp112) + 2800):3050)):(iTemp106?(3050 - (450 * fTemp110)):2600)):(iTemp104?((75 * fTemp107) + 2600):2675)):(iTemp102?((325 * fTemp105) + 2675):3000)):3000):(iTemp98?((350 * fTemp101) + 3000):3350)):(iTemp96?(3350 - (350 * fTemp99)):3000)):3000):(iTemp92?((900 * fTemp95) + 3000):3900)):(iTemp90?(3900 - (300 * fTemp93)):3600)):(iTemp88?((300 * fTemp91) + 3600):3900)):(iTemp86?(3900 - (100 * fTemp89)):3800)):3800):(iTemp82?(3800 - (900 * fTemp85)):2900)):(iTemp80?((300 * fTemp83) + 2900):3200)):(iTemp78?((50 * fTemp81) + 3200):3250)):(iTemp75?(3250 - (450 * fTemp79)):2800)):(iTemp76?(fTemp152 + 2800):2900))));
			this.fRec23[0] = (fTemp161 - Math.floor(fTemp161));
			var fTemp162 = (iTemp18?(iTemp21?(iTemp23?(iTemp25?(iTemp28?(iTemp29?(iTemp31?(iTemp33?(iTemp34?(iTemp37?(iTemp39?(iTemp40?(iTemp41?(iTemp43?(iTemp46?(iTemp48?(iTemp49?(iTemp51?(iTemp53?(iTemp55?(iTemp58?(iTemp61?(iTemp64?(iTemp66?140:(iTemp64?((60 * fTemp17) + 140):200)):200):(iTemp58?(200 - (65 * fTemp62)):135)):(iTemp55?((65 * fTemp59) + 135):200)):(iTemp53?(200 - (70 * fTemp56)):130)):(iTemp51?(130 - fTemp133):120)):120):120):120):(iTemp43?(fTemp145 + 120):140)):(iTemp41?(140 - fTemp144):120)):120):120):120):(iTemp34?(fTemp143 + 120):140)):(iTemp33?((60 * fTemp35) + 140):200)):(iTemp31?(200 - (80 * fTemp129)):120)):120):(iTemp28?((80 * fTemp30) + 120):200)):(iTemp25?(200 - (60 * fTemp128)):140)):(iTemp23?(140 - fTemp27):120)):120):(iTemp18?((15 * fTemp22) + 120):135)):(iTemp19?(135 - (15 * fTemp20)):120));
			this.fRec25[0] = ((this.fConst4 * this.fRec25[1]) + (this.fConst5 * (fTemp16 * fTemp162)));
			var fTemp163 = Math.exp((this.fConst3 * (0 - this.fRec25[0])));
			this.fRec26[0] = ((this.fConst4 * this.fRec26[1]) + (this.fConst5 * fTemp162));
			var fTemp164 = Math.exp((this.fConst3 * (0 - this.fRec26[0])));
			this.fRec24[0] = (this.iVec2[1] - ((this.fRec24[1] * (0 - (fTemp163 + fTemp164))) + ((fTemp163 * fTemp164) * this.fRec24[2])));
			var fTemp165 = (iTemp18?(iTemp21?(iTemp23?(iTemp25?(iTemp28?(iTemp29?(iTemp31?(iTemp33?(iTemp34?(iTemp37?(iTemp39?(iTemp40?(iTemp41?(iTemp43?(iTemp46?(iTemp48?(iTemp49?(iTemp51?(iTemp53?(iTemp55?(iTemp58?(iTemp61?0.001:(iTemp58?((0.000778 * fTemp62) + 0.001):0.001778)):(iTemp55?(0.001778 - (0.001147 * fTemp59)):0.000631)):(iTemp53?((0.099369 * fTemp56) + 0.000631):0.1)):(iTemp51?((0.025893 * fTemp54) + 0.1):0.125893)):(iTemp49?(0.125893 - (0.086082 * fTemp52)):0.039811)):(iTemp48?(0.039811 - (0.029811 * fTemp50)):0.01)):(iTemp46?((0.005849 * fTemp137) + 0.01):0.015849)):(iTemp43?(0.015849 - (0.00326 * fTemp47)):0.012589)):(iTemp41?((0.087411 * fTemp44) + 0.012589):0.1)):fTemp158):(iTemp39?((0.004104 * fTemp131) + 0.015849):0.019953)):0.019953):(iTemp34?(0.019953 - (0.016791 * fTemp38)):0.003162)):(iTemp33?(0.003162 - (0.001577 * fTemp35)):0.001585)):(iTemp31?((0.004725 * fTemp129) + 0.001585):0.00631)):(iTemp29?(0.00631 - (0.003148 * fTemp32)):0.003162)):(iTemp28?(0.003162 - (0.002162 * fTemp30)):0.001)):(iTemp25?((0.078433 * fTemp128) + 0.001):0.079433)):(iTemp23?((0.020567 * fTemp26) + 0.079433):0.1)):(iTemp21?(0.1 - (0.068377 * fTemp24)):0.031623)):(iTemp18?((0.018496 * fTemp22) + 0.031623):0.050119)):0.050119);
			var fTemp166 = ((iTemp73 * this.fRec27[1]) + (this.fConst6 * (iTemp75?(iTemp78?(iTemp80?(iTemp82?(iTemp84?(iTemp86?(iTemp88?(iTemp90?(iTemp92?(iTemp94?(iTemp96?(iTemp98?(iTemp100?(iTemp102?(iTemp104?(iTemp106?(iTemp109?(iTemp111?(iTemp113?(iTemp115?4950:(iTemp113?(4950 - (2200 * fTemp116)):2750)):(iTemp111?(fTemp160 + 2750):3100)):(iTemp109?((240 * fTemp112) + 3100):3340)):(iTemp106?(3340 - (440 * fTemp110)):2900)):(iTemp104?(fTemp108 + 2900):2950)):(iTemp102?((400 * fTemp105) + 2950):3350)):(iTemp100?(3350 - fTemp153):3300)):(iTemp98?((290 * fTemp101) + 3300):3590)):(iTemp96?(3590 - (290 * fTemp99)):3300)):(iTemp94?((100 * fTemp97) + 3300):3400)):(iTemp92?((1550 * fTemp95) + 3400):4950)):4950):4950):4950):4950):(iTemp82?(4950 - (1700 * fTemp85)):3250)):(iTemp80?((330 * fTemp83) + 3250):3580)):(iTemp78?(3580 - (40 * fTemp81)):3540)):(iTemp75?(3540 - (540 * fTemp79)):3000)):(iTemp76?((300 * fTemp77) + 3000):3300))));
			this.fRec27[0] = (fTemp166 - Math.floor(fTemp166));
			var fTemp167 = (fSlow0 * (((((((this.fRec0[0] * (iSlow17?fTemp72:fTemp71)) * (1 - (fTemp70 + (fTemp69 * (1 - fTemp70))))) * ftbl0mydspSIG0[(65536 * this.fRec10[0])]) + (((this.fRec12[0] * (iSlow17?(fTemp72 * fTemp138):(fTemp71 * fTemp138))) * (1 - (fTemp136 + (fTemp135 * (1 - fTemp136))))) * ftbl0mydspSIG0[(65536 * this.fRec15[0])])) + (((this.fRec16[0] * (iSlow17?(fTemp72 * fTemp151):(fTemp71 * fTemp151))) * (1 - (fTemp149 + (fTemp148 * (1 - fTemp149))))) * ftbl0mydspSIG0[(65536 * this.fRec19[0])])) + (((this.fRec20[0] * (iSlow17?(fTemp72 * fTemp159):(fTemp71 * fTemp159))) * (1 - (fTemp157 + (fTemp156 * (1 - fTemp157))))) * ftbl0mydspSIG0[(65536 * this.fRec23[0])])) + (((this.fRec24[0] * (iSlow17?(fTemp72 * fTemp165):(fTemp71 * fTemp165))) * (1 - (fTemp164 + (fTemp163 * (1 - fTemp164))))) * ftbl0mydspSIG0[(65536 * this.fRec27[0])])));
			output0[i] = fTemp167;
			output1[i] = fTemp167;
			this.iVec0[1] = this.iVec0[0];
			this.fRec2[1] = this.fRec2[0];
			this.fRec3[1] = this.fRec3[0];
			this.fVec1[1] = this.fVec1[0];
			this.fRec1[1] = this.fRec1[0];
			this.iVec2[1] = this.iVec2[0];
			this.fRec5[1] = this.fRec5[0];
			this.fRec6[1] = this.fRec6[0];
			this.fRec7[1] = this.fRec7[0];
			this.fRec4[1] = this.fRec4[0];
			this.fRec8[1] = this.fRec8[0];
			this.fRec0[2] = this.fRec0[1];
			this.fRec0[1] = this.fRec0[0];
			this.fRec11[1] = this.fRec11[0];
			this.fRec10[1] = this.fRec10[0];
			this.fRec13[1] = this.fRec13[0];
			this.fRec14[1] = this.fRec14[0];
			this.fRec12[2] = this.fRec12[1];
			this.fRec12[1] = this.fRec12[0];
			this.fRec15[1] = this.fRec15[0];
			this.fRec17[1] = this.fRec17[0];
			this.fRec18[1] = this.fRec18[0];
			this.fRec16[2] = this.fRec16[1];
			this.fRec16[1] = this.fRec16[0];
			this.fRec19[1] = this.fRec19[0];
			this.fRec21[1] = this.fRec21[0];
			this.fRec22[1] = this.fRec22[0];
			this.fRec20[2] = this.fRec20[1];
			this.fRec20[1] = this.fRec20[0];
			this.fRec23[1] = this.fRec23[0];
			this.fRec25[1] = this.fRec25[0];
			this.fRec26[1] = this.fRec26[0];
			this.fRec24[2] = this.fRec24[1];
			this.fRec24[1] = this.fRec24[0];
			this.fRec27[1] = this.fRec27[0];
			
		}
		
	}
	
}

